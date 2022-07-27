// made by  .. fe
#pragma once
#include <opencv2/opencv.hpp>

#define RED   0
#define GREEN 1
#define BLUE  2


void turnToGrayByAverage(cv::Mat& mat);

cv::Mat sharpness(cv::Mat& mat);
void masking(cv::Mat &mat, cv::Mat& newMat, int row, int col, double* mask, int color);
cv::Mat blending(const cv::Mat &mat1, const cv::Mat &mat2, float alpha);
cv::Mat gaussian(const cv::Mat &mat);
cv::Mat gaussian2(const cv::Mat &mat);

double keepBetween(double sum, int max, int min);
uchar keepItUCharValue(double sum);
std::vector<cv::Vec3b*> cellNeighborAsArray(cv::Mat &mat, int row, int col);
cv::Vec3b calcBlending(cv::Vec3b& px1, cv::Vec3b& px2, float alpha);
uchar calcBlendingForColor(uchar& px1, uchar& px2, float alpha);
cv::Vec3b calcAveraveOfPixels(const cv::Vec3b &px1, const cv::Vec3b &px2, const cv::Vec3b &px3, const cv::Vec3b &px4);
