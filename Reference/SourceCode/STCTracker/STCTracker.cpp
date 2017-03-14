#include "STCTracker.h"  

STCTracker::STCTracker()
{

}

STCTracker::~STCTracker()
{

}

/************ ���������� ********************/
void STCTracker::createHammingWin()
{
	for (int i = 0; i < hammingWin.rows; i++)
	{
		for (int j = 0; j < hammingWin.cols; j++)
		{
			hammingWin.at<double>(i, j) = (0.54 - 0.46 * cos(2 * CV_PI * i / hammingWin.rows))
				* (0.54 - 0.46 * cos(2 * CV_PI * j / hammingWin.cols));
		}
	}
}

/************ ����������ֵ���� *****************/
void STCTracker::complexOperation(const Mat src1, const Mat src2, Mat &dst, int flag)
{
	CV_Assert(src1.size == src2.size);
	CV_Assert(src1.channels() == 2);

	Mat A_Real, A_Imag, B_Real, B_Imag, R_Real, R_Imag;
	vector<Mat> planes;
	split(src1, planes);
	planes[0].copyTo(A_Real);
	planes[1].copyTo(A_Imag);

	split(src2, planes);
	planes[0].copyTo(B_Real);
	planes[1].copyTo(B_Imag);

	dst.create(src1.rows, src1.cols, CV_64FC2);
	split(dst, planes);
	R_Real = planes[0];
	R_Imag = planes[1];

	for (int i = 0; i < A_Real.rows; i++)
	{
		for (int j = 0; j < A_Real.cols; j++)
		{
			double a = A_Real.at<double>(i, j);
			double b = A_Imag.at<double>(i, j);
			double c = B_Real.at<double>(i, j);
			double d = B_Imag.at<double>(i, j);

			if (flag)
			{
				//��������: (a+bj) / (c+dj)  
				R_Real.at<double>(i, j) = (a * c + b * d) / (c * c + d * d + 0.000001);
				R_Imag.at<double>(i, j) = (b * c - a * d) / (c * c + d * d + 0.000001);
			}
			else
			{
				//�����˷�: (a+bj) * (c+dj)  
				R_Real.at<double>(i, j) = a * c - b * d;
				R_Imag.at<double>(i, j) = b * c + a * d;
			}
		}
	}
	merge(planes, dst);
}

/************�õ������ĵ�������ʺͺ������ ***********/
void STCTracker::getCxtPriorPosteriorModel(const Mat image)
{
	CV_Assert(image.size == cxtPriorPro.size);

	double sum_prior(0), sum_post(0);
	for (int i = 0; i < cxtRegion.height; i++)
	{
		for (int j = 0; j < cxtRegion.width; j++)
		{
			double x = j + cxtRegion.x;
			double y = i + cxtRegion.y;
			double dist = sqrt((center.x - x) * (center.x - x) + (center.y - y) * (center.y - y));

			//�����еĹ�ʽ5  
			cxtPriorPro.at<double>(i, j) = exp(-dist * dist / (2 * sigma * sigma));
			sum_prior += cxtPriorPro.at<double>(i, j);

			//�����еĹ�ʽ6 
			cxtPosteriorPro.at<double>(i, j) = exp(-pow(dist / sqrt(alpha), beta));
			sum_post += cxtPosteriorPro.at<double>(i, j);
		}
	}
	cxtPriorPro.convertTo(cxtPriorPro, -1, 1.0 / sum_prior);
	cxtPriorPro = cxtPriorPro.mul(image);
	cxtPosteriorPro.convertTo(cxtPosteriorPro, -1, 1.0 / sum_post);
}

/************ Learn Spatio-Temporal Context Model ***********/
void STCTracker::learnSTCModel(const Mat image)
{
	//�õ������ĵ�����ͺ������ 
	getCxtPriorPosteriorModel(image);

	//���������ִ�ж�άDFT 
	Mat priorFourier;
	Mat planes1[] = { cxtPriorPro, Mat::zeros(cxtPriorPro.size(), CV_64F) };
	merge(planes1, 2, priorFourier);
	dft(priorFourier, priorFourier);

	//�Ժ������ִ�ж�άDFT  
	Mat postFourier;
	Mat planes2[] = { cxtPosteriorPro, Mat::zeros(cxtPosteriorPro.size(), CV_64F) };
	merge(planes2, 2, postFourier);
	dft(postFourier, postFourier);

	//������� 
	Mat conditionalFourier;
	complexOperation(postFourier, priorFourier, conditionalFourier, 1);

	//����������ִ��2D��DFT�����ǻ��STModel 
	dft(conditionalFourier, STModel, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

	//ʹ��ѧϰ�Ŀռ�������ģ��������ʱ��������ģ�� 
	addWeighted(STCModel, 1.0 - rho, STModel, rho, 0.0, STCModel);
}

/************ Initialize the hyper parameters and models ***********/
void STCTracker::init(const Mat frame, const Rect box)
{
	//��ʼ������ 
	alpha = 10.25;
	beta = 1;
	rho = 0.075;
	sigma = 0.5 * (box.width + box.height);

	//Ŀ������  
	center.x = box.x + 0.5 * box.width;//��ȡĿ�������ĵ������
	center.y = box.y + 0.5 * box.height;//��ȡĿ�������ĵ�������

	//����������
	cxtRegion.width = 2 * box.width;
	cxtRegion.height = 2 * box.height;
	cxtRegion.x = center.x - cxtRegion.width * 0.5;
	cxtRegion.y = center.y - cxtRegion.height * 0.5;
	cxtRegion &= Rect(0, 0, frame.cols, frame.rows);

	//������ʣ�������ʣ��������ʺ�ʱ��������ģ�� 
	cxtPriorPro = Mat::zeros(cxtRegion.height, cxtRegion.width, CV_64FC1);
	cxtPosteriorPro = Mat::zeros(cxtRegion.height, cxtRegion.width, CV_64FC1);
	STModel = Mat::zeros(cxtRegion.height, cxtRegion.width, CV_64FC1);
	STCModel = Mat::zeros(cxtRegion.height, cxtRegion.width, CV_64FC1);

	//����һ�������� 
	hammingWin = Mat::zeros(cxtRegion.height, cxtRegion.width, CV_64FC1);
	createHammingWin();

	Mat gray;
	cvtColor(frame, gray, CV_RGB2GRAY);

	//ͨ����ȥ�������ƽ��ǿ������׼��  
	Scalar average = mean(gray(cxtRegion));
	Mat context;
	gray(cxtRegion).convertTo(context, CV_64FC1, 1.0, -average[0]);

	//���Ժ������Լ�Сͼ��߽��Ƶ��ЧӦ 
	context = context.mul(hammingWin);

	//�ӵ�һ֡ѧϰʱ��������ģ�� 
	learnSTCModel(context);
}

/********��������ͼ���ҵ����λ��*******/
void STCTracker::tracking(const Mat frame, Rect &trackBox)
{
	Mat gray;
	cvtColor(frame, gray, CV_RGB2GRAY);

	//ͨ����ȥ�������ƽ��ǿ������׼�� 
	Scalar average = mean(gray(cxtRegion));
	Mat context;
	gray(cxtRegion).convertTo(context, CV_64FC1, 1.0, -average[0]);

	//���Ժ������Լ�Сͼ��߽��Ƶ��ЧӦ 
	context = context.mul(hammingWin);

	//��ȡ�������������
	getCxtPriorPosteriorModel(context);

	//���������ִ�ж�άDFT���� 
	Mat priorFourier;
	Mat planes1[] = { cxtPriorPro, Mat::zeros(cxtPriorPro.size(), CV_64F) };
	merge(planes1, 2, priorFourier);
	dft(priorFourier, priorFourier);

	//����������ִ�ж�άDFT����  
	Mat STCModelFourier;
	Mat planes2[] = { STCModel, Mat::zeros(STCModel.size(), CV_64F) };
	merge(planes2, 2, STCModelFourier);
	dft(STCModelFourier, STCModelFourier);

	//����˷�  
	Mat postFourier;
	complexOperation(STCModelFourier, priorFourier, postFourier, 0);

	//ִ�к�����ʵĶ�ά��DFT��������ͼ 
	Mat confidenceMap;
	dft(postFourier, confidenceMap, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

	//�ҵ����λ��  
	Point point;
	minMaxLoc(confidenceMap, 0, 0, 0, &point);

	//�������ģ�trackBox������������ 
	center.x = cxtRegion.x + point.x;
	center.y = cxtRegion.y + point.y;
	trackBox.x = center.x - 0.5 * trackBox.width;
	trackBox.y = center.y - 0.5 * trackBox.height;
	trackBox &= Rect(0, 0, frame.cols, frame.rows);

	cxtRegion.x = center.x - cxtRegion.width * 0.5;
	cxtRegion.y = center.y - cxtRegion.height * 0.5;
	cxtRegion &= Rect(0, 0, frame.cols, frame.rows);

	//�Ӹ�֡ѧϰʱ��������ģ���Ը�����һ֡  
	average = mean(gray(cxtRegion));
	gray(cxtRegion).convertTo(context, CV_64FC1, 1.0, -average[0]);
	context = context.mul(hammingWin);
	learnSTCModel(context);
}