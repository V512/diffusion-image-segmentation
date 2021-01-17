#include <opencv2/opencv.hpp>

struct NeighborStruct {
private:
    cv::Mat mNeighbors = cv::Mat::zeros(1, 4, CV_32SC2);
    const int mN = 4;
    cv::Size mImageSize;

public:
    NeighborStruct(cv::Size imageSize);

    void findNeighbors(int i, int j);

    void print() const;

    int getN() const;

    cv::Vec2i operator[](const int i) const;

    int static getIndex(int i, int j, const cv::Vec2i &neighbor);

    bool isAllowedNeighbor(int i, int j) const;

    int getNT() const;

};
