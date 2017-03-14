#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "kcftracker.hpp"

using namespace std;
using namespace cv;

static Mat image;
static Rect2d boundingBox;
static bool paused;
static bool selectObject = false;
static bool startSelection = false;

static void onMouse(int event, int x, int y, int, void*)
{
	if (!selectObject)
	{
		switch (event)
		{
		case EVENT_LBUTTONDOWN:
			//set origin of the bounding box
			startSelection = true;
			boundingBox.x = x;
			boundingBox.y = y;
			boundingBox.width = boundingBox.height = 0;
			break;
		case EVENT_LBUTTONUP:
			//sei with and height of the bounding box
			boundingBox.width = std::abs(x - boundingBox.x);
			boundingBox.height = std::abs(y - boundingBox.y);
			paused = false;
			selectObject = true;
			break;
		case EVENT_MOUSEMOVE:

			if (startSelection && !selectObject)
			{
				//draw the bounding box
				Mat currentFrame;
				image.copyTo(currentFrame);
				rectangle(currentFrame, Point((int)boundingBox.x, (int)boundingBox.y), Point(x, y), Scalar(255, 0, 0), 2, 1);
				imshow("Tracking", currentFrame);
			}
			break;
		}
	}
}

int main()
{
	bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = true;
	bool LAB = false;
	VideoCapture cap("video_2.avi");
	if (!cap.isOpened())
	{
		return -1;
	}
	Mat frame;
	Mat preframe;
	paused = false;
	namedWindow("Tracking", 0);
	setMouseCallback("Tracking", onMouse, 0);
	KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);	  
	cap >> preframe;
	preframe.copyTo(image);
	imshow("Tracking", image);
	bool initialized = false;
	int frameCounter = 0;
	for (;;)
	{
		char c = (char)waitKey(2);
		if (c == 'q' || c == 27)
			break;
		if (c == 'p')
			paused = !paused;
		if (!paused)
		{
			cap >> preframe;
			if (preframe.empty())
			{
				break;
			}
			preframe.copyTo(image);
			if (selectObject)
			{
				if (!initialized)
				{
					tracker.init(boundingBox, preframe);
					initialized = true;
				}
				else
				{
					boundingBox = tracker.update(preframe);
					rectangle(image, boundingBox, Scalar(255, 0, 0), 2, 1);
				}
			}
			imshow("Tracking", image);
			frameCounter++;
		}
	}
	return 0;
}
