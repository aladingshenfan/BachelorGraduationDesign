/*

�����ں�����˲�����KCF�����ں�ѭ���ṹ��CSK���ĸ�����.
CSKͨ��ʹ��ԭʼ�Ҷȼ�������ʵ�֣���Ϊ���ǵ�ͨ���˲�����
KCFͨ��ʹ��HOG���ܣ�Ĭ�ϣ�ʵ�֣���Ϊ����CSK��չ�����ͨ����

���캯��������ȫ��Ϊ�������ͣ�
    hog: ʹ��HOG���ܣ�Ĭ�ϣ�������ʹ��ԭʼ����
    fixed_window: �̶����ڴ�С��Ĭ�ϣ�������ʹ��ROI��С����������׼ȷ��
    multiscale: ʹ�ö�߶ȸ��٣�Ĭ��;������fixed_window = trueһ��ʹ�ã�

	��������ѡ��Ϊ��������������������Ĭ��ֵ��
	���ǵ�ֵ�����ڵ���init����֮ǰ��һ�����ƣ�
    interp_factor: ���Բ�ֵ����
    sigma:��˹�˴���
    lambda: ����ϵ��
    cell_size: HOG���ڴ�С
    padding: Χ��Ŀ���ˮƽ������������С
    output_sigma_factor: ��˹Ŀ��Ĵ���
    template_size: ģ���С��������Ϊ��λ����0��ʾʹ��ROI��С
    scale_step: ���ڶ�߶ȹ��Ƶı���������1������
    scale_weight: to downweight detection scores of other scales for added stability

For speed, the value (template_size/cell_size) should be a power of 2 or a product of small prime numbers.

Inputs to init():
   image is the initial frame.
   roi is a cv::Rect with the target positions in the initial frame

Inputs to update():
   image is the current frame.

Outputs of update():
   cv::Rect with target positions for the current frame
 */

#pragma once

#include "tracker.h"

#ifndef _OPENCV_KCFTRACKER_HPP_
#define _OPENCV_KCFTRACKER_HPP_
#endif

class KCFTracker : public Tracker
{
public:
    // ���캯��
    KCFTracker(bool hog = true, bool fixed_window = true, bool multiscale = true, bool lab = true);

    // ��ʼ��������
    virtual void init(const cv::Rect &roi, cv::Mat image);
    
    //�����µ���Ƶ֡���¸��ٿ��λ��
    virtual cv::Rect update(cv::Mat image);

    float interp_factor; // linear interpolation factor for adaptation
    float sigma; // gaussian kernel bandwidth
    float lambda; // regularization
    int cell_size; // HOG cell size
    int cell_sizeQ; // cell size^2, to avoid repeated operations
    float padding; // extra area surrounding the target
    float output_sigma_factor; // bandwidth of gaussian target
    int template_size; // template size
    float scale_step; // scale step for multi-scale estimation
    float scale_weight;  // to downweight detection scores of other scales for added stability

protected:
    // �ڵ�ǰ֡���Ŀ��.
    cv::Point2f detect(cv::Mat z, cv::Mat x, float &peak_value);

    //�õ�֡ͼ��ѵ��������
    void train(cv::Mat x, float train_interp_factor);

    // Evaluates a Gaussian kernel with bandwidth SIGMA for all relative shifts between input images X and Y, which must both be MxN. They must    also be periodic (ie., pre-processed with a cosine window).
	//�������ͼ��X��Y֮������������λ�������д���SIGMA�ĸ�˹�ںˣ�����붼��M��N�� ����Ҳ�����������Եģ����������Ҵ���Ԥ������
    cv::Mat gaussianCorrelation(cv::Mat x1, cv::Mat x2);

    // Create Gaussian Peak. Function called only in the first frame.
	//������˹�塣 ���ڵ�һ֡�е��õĺ�����

    cv::Mat createGaussianPeak(int sizey, int sizex);

    // Obtain sub-window from image, with replication-padding and extract features
	//��ͼ���ȡ�Ӵ��ڣ�ʹ�ø���������ȡ����
    cv::Mat getFeatures(const cv::Mat & image, bool inithann, float scale_adjust = 1.0f);

    // Initialize Hanning window. Function called only in the first frame.
    void createHanningMats();

    // Calculate sub-pixel peak for one dimension
	//����һ��ά�ȵ������ط�ֵ
    float subPixelPeak(float left, float center, float right);

    cv::Mat _alphaf;
    cv::Mat _prob;
    cv::Mat _tmpl;
    cv::Mat _num;
    cv::Mat _den;
    cv::Mat _labCentroids;

private:
    int size_patch[3];
    cv::Mat hann;
    cv::Size _tmpl_sz;
    float _scale;
    int _gaussian_size;
    bool _hogfeatures;
    bool _labfeatures;
};
