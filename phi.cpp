#include "phi.h"

Phi::Phi(int ks, int width, int height, int neighbors) {
    this->ks = ks;
    this->width = width;
    this->height = height;
    this->neighbors = neighbors;
    this->phi = new float[ks * width * height * neighbors];
    for(int i = 0; i < ks * width * height * neighbors; ++i) {
        this->phi[i] = 0;
    }
}

float& Phi::operator()(int k, int i, int j, int n) {
    return this->phi[k + n * ks + j * (neighbors * ks) + i * width * neighbors * ks];
}

Phi::~Phi() {
    delete [] this->phi;
}