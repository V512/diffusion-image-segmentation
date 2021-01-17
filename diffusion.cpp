#include "diffusion.h"
#include <iostream>
#include <utility>
#include <cmath>
#include "neighborStruct.h"
#include "phi.h"
#include <float.h>
#include "timeMeasurement.h"


struct EdgeCost {
private:
    float costs[4];
public:
    EdgeCost(float alpha) {
        this->costs[0] = alpha;
        this->costs[1] = 0.0;
        this->costs[2] = 0.0;
        this->costs[3] = alpha;
    }

    float operator()(int k1, int k2) {
        return this->costs[k1 * 2 + k2];
    }

    ~EdgeCost() = default;
};

struct NodeCost {
public:
    NodeCost(const cv::Mat &image, const std::vector<cv::Vec3b> &colours) {
        this->height = image.size().height;
        this->width = image.size().width;
        this->ks = colours.size();
        costs = std::vector<float>(height * width * ks);
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                for(int k = 0; k < ks; ++k) {
                    float c = cv::norm(colours[k], image.at<cv::Vec3b>(i,j));
                    float ci = cv::norm(colours[k ^ 1], image.at<cv::Vec3b>(i,j));
                    costs[k  + j * ks + ks * width * i] = c < ci ? 1.0 : 0.0;
                }
            }
        }
    }

    float operator()(int i, int j, int k) {
        return costs[k  + j * ks + ks * width * i];
    }

private:
    std::vector<float> costs;
    int width;
    int height;
    int ks;
};


int getK(int k, Phi &phi, int i, int j, int ni, int nj, int neighbor, int neighborIndex, EdgeCost& edgeCostTable);

cv::Mat diffusionAlgorithm(const cv::Mat &image, float alpha, const std::vector<cv::Vec3b> &colorSegments, int iters) {
    int neihborsQ = 4;
    int ks = 2;
    long long fullIterTime = 0;
    auto imageSize = image.size();
    Phi phi(ks, imageSize.width, imageSize.height, neihborsQ);
    EdgeCost edgeCostTable(alpha);
    NodeCost nodeCostTable(image, colorSegments);
    auto neighbors = NeighborStruct(imageSize);
    TimeMeasurement time;
    for(int it = 0; it < iters; ++it) {
        time.updateTime();
        for(int i = 0; i < imageSize.height; ++i) {
            for(int j = 0; j < imageSize.width; ++j) {
                neighbors.findNeighbors(i, j); 
                for(int k1 = 0; k1 < 2; ++k1) {
                    float C = 0.0;
                    int kMax[4];
                    for(int n = 0; n < neihborsQ; n++) {
                        auto neighbor = neighbors[n];
                        if(neighbors.isAllowedNeighbor(neighbor[0], neighbor[1])) {
                            int neighborIndex = neighbors.getIndex(i, j, neighbor);
                            kMax[n] = getK(k1, phi,  i, j, neighbor[0], neighbor[1], n, neighborIndex, edgeCostTable);
                            C += edgeCostTable(k1, kMax[n]) - phi(kMax[n], neighbor[0], neighbor[1], neighborIndex);
                        }
                        
                    }
                    C = (C + nodeCostTable(i, j, k1)) / neighbors.getNT();
                    for(int n = 0; n < neihborsQ; ++n) {
                        auto neighbor = neighbors[n];
                        if(neighbors.isAllowedNeighbor(neighbor[0], neighbor[1])) {
                            int neighborIndex = neighbors.getIndex(i, j, neighbor);
                            phi(k1, i, j, n) = edgeCostTable(k1, kMax[n]) - phi(kMax[n], neighbor[0], neighbor[1], neighborIndex) - C;
                        }
                    }
                }
            }
        }
        long long iterTime = time.getTime();
        printf("Iter %d. Time %lld ms\n", it + 1, iterTime);
        fullIterTime += iterTime;
    }
    printf("Average iter time %lld ms\n", fullIterTime / iters);
    cv::Mat segmentedImage = cv::Mat(imageSize, CV_8UC3);
    for(int i = 0; i < imageSize.height; ++i) {
        for(int j = 0; j < imageSize.width; ++j) {
            neighbors.findNeighbors(i, j); 
            float maxCost = -FLT_MAX;
            int maxK = 0;
            for(int n = 0; n < neihborsQ; n++) {
                auto neighbor = neighbors[n];
                if(neighbors.isAllowedNeighbor(neighbor[0], neighbor[1])) {
                    int neighborIndex = neighbors.getIndex(i, j, neighbor);
                    for(int k1 = 0; k1 < 2; ++k1) {
                        for(int k2 = 0; k2 < 2; ++k2) {
                            float cost = edgeCostTable(k1, k2) - phi(k1, i,j, n) - phi(k2, neighbor[0], neighbor[1], neighborIndex);
                            if(cost > maxCost) {
                                maxCost = cost;
                                maxK = k2;
                            }
                        }
                    }
                }
            }
            segmentedImage.at<cv::Vec3b>(i, j) = colorSegments[maxK];
        }
    }
    return segmentedImage;
}

int getK(int k, Phi &phi, int i, int j, int ni, int nj, int neighbor, int neighborIndex, EdgeCost& edgeCostTable) {
    int k2max = 0;
    float maxCost = -FLT_MAX;
    for(int k2 = 0; k2 < 2; k2++) {
        float cost = edgeCostTable(k, k2) - phi(k, i, j, neighbor) - phi(k2, ni, nj, neighborIndex);
        if(cost > maxCost) {
            k2max = k2;
            maxCost = cost;
        }
    }   
    return k2max;   
}