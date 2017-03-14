#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;

Rect gButtonFirst, gButtonSecond, gButtonThird;

Rect DrawString(Mat _image, string _text, Point _coordinate, Scalar _color, float _fontScale = 0.6f, int _thickness = 1, int _fontFace = FONT_HERSHEY_COMPLEX)
{
    int baseline=0;
    Size textsize = getTextSize(_text, _fontFace, _fontScale, _thickness, &baseline);
    baseline += _thickness;
	if (_coordinate.y >= 0)
	{
		_coordinate.y += textsize.height;
    }
    else 
	{
		_coordinate.y += _image.rows - baseline + 1;
    }
	if (_coordinate.x < 0)
	{
		_coordinate.x += _image.cols - textsize.width + 1;
    }
	Rect boundingrect = Rect(_coordinate.x, _coordinate.y - textsize.height, textsize.width, baseline + textsize.height);
	putText(_image, _text, _coordinate, _fontFace, _fontScale, _color, _thickness, CV_AA);
    return boundingrect;
}

Rect DrawButton(Mat _image, string _text, Point _coordinate, int _minwidth = 0)
{
    int border = 20;
	Point textcoordinate = Point(_coordinate.x + border, _coordinate.y + border);
	Rect recttext = DrawString(_image, _text, textcoordinate, CV_RGB(0, 0, 0));
    Rect rectbutton = Rect(recttext.x - border, recttext.y - border, recttext.width + 2*border, recttext.height + 2*border);
    if (rectbutton.width < _minwidth)
        rectbutton.width = _minwidth;
    Mat matButton = _image(rectbutton);
    matButton += CV_RGB(90, 90, 90);
    rectangle(_image, rectbutton, CV_RGB(200,200,200), 1, CV_AA);
	DrawString(_image, _text, textcoordinate, CV_RGB(10, 55, 20));
    return rectbutton;
}

bool IsPointInRect(const Point _point, const Rect _rect)
{
	if (_point.x >= _rect.x && _point.x <= (_rect.x + _rect.width - 1))
		if (_point.y >= _rect.y && _point.y <= (_rect.y + _rect.height - 1))
            return true;
    return false;
}

void OnMouse(int event, int x, int y, int, void*)
{
    if (event != CV_EVENT_LBUTTONDOWN)
        return;
    Point point = Point(x,y);
    if (IsPointInRect(point, gButtonFirst)) 
	{
        cout << "用户点击了第一个按钮." << endl;
    }
    else if (IsPointInRect(point, gButtonSecond)) 
	{
        cout << "用户点击了第二个按钮." << endl;
    }
    else if (IsPointInRect(point, gButtonThird)) 
	{
        cout << "用户点击了第三个按钮." << endl;
    }
    else 
	{
		cout << "用户点击了按钮外区域." << endl;
    }
}


//int main()
//{
//	Mat sourceimage = imread("image.jpg");
//	gButtonFirst = DrawButton(sourceimage, "HELLO", Point(10, 10),80);
//	gButtonSecond = DrawButton(sourceimage, "HELLO", Point(gButtonFirst.x, gButtonFirst.y + gButtonFirst.height), gButtonFirst.width);
//	gButtonThird = DrawButton(sourceimage, "HELLO", Point(gButtonSecond.x, gButtonSecond.y + gButtonSecond.height), gButtonSecond.width);
//	imshow("window", sourceimage);
//    setMouseCallback("window", OnMouse, &sourceimage);
//	waitKey(0);
//    return 0;
//}