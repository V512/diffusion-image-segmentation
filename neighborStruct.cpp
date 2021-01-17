#include "neighborStruct.h"

void NeighborStruct::findNeighbors(int i, int j) {
    mNeighbors.at<cv::Vec2i>(0, 0) = cv::Vec2i(i, j + 1);
    mNeighbors.at<cv::Vec2i>(0, 1) = cv::Vec2i(i + 1, j);
    mNeighbors.at<cv::Vec2i>(0, 2) = cv::Vec2i(i, j - 1);
    mNeighbors.at<cv::Vec2i>(0, 3) = cv::Vec2i(i - 1, j);
}

void NeighborStruct::print() const {
    for(int i = 0; i < mN; i++) {
        printf("(%d, %d) ", mNeighbors.at<cv::Vec2i>(0, i)[0], mNeighbors.at<cv::Vec2i>(0, i)[1]);
    }
    printf("\n");
}

int NeighborStruct::getN() const {
    return mN;
}

cv::Vec2i NeighborStruct::operator[](const int i) const {
    return mNeighbors.at<cv::Vec2i>(0, i);
}

int NeighborStruct::getIndex(int i, int j, const cv::Vec2i &neighbor) {
    if ((i == neighbor[0]) && (j - 1 == neighbor[1])) {
        return 0;
    }
    if ((i - 1 == neighbor[0]) && (j == neighbor[1])) {
        return 1;
    }
    if ((i == neighbor[0]) && (j + 1 == neighbor[1])) {
        return 2;
    }
    if((i + 1 == neighbor[0]) && (j == neighbor[1])) {
        return 3;
    }
    return -1;
}

bool NeighborStruct::isAllowedNeighbor(int i, int j) const {
    if ((i >= 0) && (i < mImageSize.height) && (j >= 0) && (j < mImageSize.width)) {
        return true;
    }
    return false; 
} 

int NeighborStruct::getNT() const {
    int nt = 0;
    for(int i = 0; i < getN(); i++) {
        cv::Vec2i neighbor = mNeighbors.at<cv::Vec2i>(0, i);
        if(isAllowedNeighbor(neighbor[0], neighbor[1])) {
            nt++;
        };
    }
    return nt;
}

NeighborStruct::NeighborStruct(cv::Size imageSize) {
    mImageSize = imageSize;
}