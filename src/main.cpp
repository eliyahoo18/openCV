#include <iostream>
#include <opencv2/opencv.hpp>
#include "mission1.h"

#define SRC_IMAGE1_PATH "/Users/peach/programming/cpp/openCV/image/butterfly.jpeg"
#define SRC_IMAGE2_PATH "/Users/peach/programming/cpp/openCV/image/butterfly2.webp"

int main() {
    cv::Mat srcImage1 = cv::imread(SRC_IMAGE1_PATH);
    cv::Mat srcImage2 = cv::imread(SRC_IMAGE2_PATH);

    // turnToGrayAverage(srcImage);
    // cv::Mat srcImage2 = sharpness(srcImage);
    cv::Mat srcImage3 = gaussian2(gaussian2(gaussian(gaussian(srcImage1)))); // , srcImage1, 0.5); //sharpness(srcImage);

    cv::namedWindow(SRC_IMAGE1_PATH, cv::WINDOW_AUTOSIZE);
    cv::imshow(SRC_IMAGE1_PATH, srcImage1);

    cv::namedWindow(SRC_IMAGE2_PATH, cv::WINDOW_AUTOSIZE);
    cv::imshow(SRC_IMAGE2_PATH, srcImage2);

    cv::namedWindow("dest", cv::WINDOW_AUTOSIZE);
    cv::imshow("dest", srcImage3);
    cv::waitKey(0);

    return 0;
}
