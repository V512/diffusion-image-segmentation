#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "diffusion.h"
#include "timeMeasurement.h"

int main() {
    TimeMeasurement time;
    cv::Mat image = cv::imread("C:\\vlad\\Development\\Diffusion\\diffusion-image-segmentation\\map_hsv.png", 1);
    cv::Mat resizedImage;
    std::vector<cv::Vec3b> segments = {cv::Vec3b(0, 190, 0), cv::Vec3b(190, 0, 0)};
    time.updateTime();
    cv::Mat segmentedImage = diffusionAlgorithm(image, 1.0, segments, 100);
    long long elapsedTime = time.getTime();
    printf("Elapsed Time %lld ms", elapsedTime);
    cv::Mat dst;
    cv::hconcat(image, segmentedImage, dst);
    cv::imshow("image", dst);
    cv::waitKey(0);
    return 0;
}


