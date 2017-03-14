//#include "opencvlib.h"
//#include <opencv2/core/utility.hpp>
//#include <opencv2/tracking.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <iostream>
//#include <cstring>
//
//using namespace std;
//using namespace cv;
//
//static Mat image;
//static Rect2d boundingBox;
//static bool paused;
//static bool selectObject = false;
//static bool startSelection = false;
//
//static void onMouse(int event, int x, int y, int, void*)
//{
//	if (!selectObject)
//	{
//		switch (event)
//		{
//		case EVENT_LBUTTONDOWN:
//			//set origin of the bounding box
//			startSelection = true;
//			boundingBox.x = x;
//			boundingBox.y = y;
//			boundingBox.width = boundingBox.height = 0;
//			break;
//		case EVENT_LBUTTONUP:
//			//sei with and height of the bounding box
//			boundingBox.width = std::abs(x - boundingBox.x);
//			boundingBox.height = std::abs(y - boundingBox.y);
//			paused = false;
//			selectObject = true;
//			break;
//		case EVENT_MOUSEMOVE:
//
//			if (startSelection && !selectObject)
//			{
//				//draw the bounding box
//				Mat currentFrame;
//				image.copyTo(currentFrame);
//				rectangle(currentFrame, Point((int)boundingBox.x, (int)boundingBox.y), Point(x, y), Scalar(255, 0, 0), 2, 1);
//				imshow("Tracking API", currentFrame);
//			}
//			break;
//		}
//	}
//}
//
////
////  Hot keys: 
////   q - quit the program
////   p - pause video
////
//
//int main(int argc, char** argv)
//{
//	//open the capture
//	VideoCapture cap("video_1.avi");
//    //VideoCapture cap(0);
//	if (!cap.isOpened())
//	{
//		return -1;
//	}
//
//	//
//	//  "MIL", "BOOSTING", "MEDIANFLOW", "TLD"
//	//
//	string tracker_algorithm = "KCF";
//	if (argc > 1) tracker_algorithm = argv[1];
//
//	Mat frame;
//	Mat preframe;
//	paused = false;
//	namedWindow("Tracking API", 0);
//	setMouseCallback("Tracking API", onMouse, 0);
//
//	Ptr<Tracker> tracker = Tracker::create(tracker_algorithm);
//	if (tracker == NULL)
//	{
//		cout << "***Error in the instantiation of the tracker...***\n";
//		return -1;
//	}
//
//	//get the first frame
//	  
//	cap >> preframe;
//	preframe.copyTo(image);
//	imshow("Tracking API", image);
//
//	bool initialized = false;
//	int frameCounter = 0;
//
//	for (;;)
//	{
//		char c = (char)waitKey(2);
//		if (c == 'q' || c == 27)
//			break;
//		if (c == 'p')   
//			paused = !paused;
//
//		if (!paused)
//		{
//			cap >> preframe;
//			if (preframe.empty())
//			{
//				break;
//			}
//			preframe.copyTo(image);
//
//			if (selectObject)
//			{
//				if (!initialized)
//				{
//					//initializes the tracker
//					//cvtColor(preframe,frame,CV_RGB2GRAY);
//					if (!tracker->init(preframe, boundingBox))
//					{
//						cout << "***Could not initialize tracker...***\n";
//						return -1;
//					}
//					initialized = true;
//				}
//				else
//				{
//					//updates the tracker
//					//cvtColor(preframe, frame, CV_RGB2GRAY);
//					if (tracker->update(preframe, boundingBox))
//					{
//						rectangle(image, boundingBox, Scalar(255, 0, 0), 2, 1);
//					}
//				}
//			}
//			imshow("Tracking API", image);
//			frameCounter++;
//		}
//	}
//
//	return 0;
//}