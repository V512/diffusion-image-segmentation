#include "phi.h"

Phi::Phi(int ks, int width, int height, int neighbors) {
    this->ks = ks;
    this->width = width;
    this->height = height;
    this->neighbors = neighbors;
    this->phi = std::vector<float>(ks * width * height * neighbors);
}

float& Phi::operator()(int k, int i, int j, int n) {
    return this->phi[k + n * ks + j * (neighbors * ks) + i * width * neighbors * ks];
}