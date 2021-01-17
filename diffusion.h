#include <opencv2/opencv.hpp>
#include <utility>

cv::Mat diffusionAlgorithm(const cv::Mat &image, float alpha, const std::vector<cv::Vec3b> &colorSegments, int iter);

float nodeCost(int k, const cv::Vec3b &pixelValue, const std::vector<cv::Vec3b> &segmentsColour);

// int getK(int k, Phi &phi, int i, int j, int ni, int nj, int neighbor, int neighborIndex, EdgeCost& edgeCostTable);