/*

基于内核相关滤波器（KCF）和内核循环结构（CSK）的跟踪器.
CSK通过使用原始灰度级特征来实现，因为它是单通道滤波器。
KCF通过使用HOG功能（默认）实现，因为它将CSK扩展到多个通道。

构造函数参数，全部为布尔类型：
    hog: 使用HOG功能（默认），否则使用原始像素
    fixed_window: 固定窗口大小（默认），否则使用ROI大小（较慢但更准确）
    multiscale: 使用多尺度跟踪（默认;不能与fixed_window = true一起使用）

	根据上述选项为跟踪器的所有属性设置默认值。
	它们的值可以在调用init（）之前进一步定制：
    interp_factor: 线性插值因子
    sigma:高斯核带宽
    lambda: 正则化系数
    cell_size: HOG窗口大小
    padding: 围绕目标的水平区域，相对于其大小
    output_sigma_factor: 高斯目标的带宽
    template_size: 模板大小（以像素为单位），0表示使用ROI大小
    scale_step: 用于多尺度估计的比例步长，1禁用它
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
    // 构造函数
    KCFTracker(bool hog = true, bool fixed_window = true, bool multiscale = true, bool lab = true);

    // 初始化跟踪器
    virtual void init(const cv::Rect &roi, cv::Mat image);
    
    //对于新的视频帧更新跟踪框的位置
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
    // 在当前帧检测目标.
    cv::Point2f detect(cv::Mat z, cv::Mat x, float &peak_value);

    //用单帧图像训练跟踪器
    void train(cv::Mat x, float train_interp_factor);

    // Evaluates a Gaussian kernel with bandwidth SIGMA for all relative shifts between input images X and Y, which must both be MxN. They must    also be periodic (ie., pre-processed with a cosine window).
	//针对输入图像X和Y之间的所有相对移位评估具有带宽SIGMA的高斯内核，其必须都是M×N。 它们也必须是周期性的（即，用余弦窗口预处理）。
    cv::Mat gaussianCorrelation(cv::Mat x1, cv::Mat x2);

    // Create Gaussian Peak. Function called only in the first frame.
	//创建高斯峰。 仅在第一帧中调用的函数。

    cv::Mat createGaussianPeak(int sizey, int sizex);

    // Obtain sub-window from image, with replication-padding and extract features
	//从图像获取子窗口，使用复制填充和提取功能
    cv::Mat getFeatures(const cv::Mat & image, bool inithann, float scale_adjust = 1.0f);

    // Initialize Hanning window. Function called only in the first frame.
    void createHanningMats();

    // Calculate sub-pixel peak for one dimension
	//计算一个维度的子像素峰值
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
