#include <vector>


struct Phi {
private:
    int ks;
    int width;
    int height;
    int neighbors;
    std::vector<float> phi;

public:
    Phi(int kSize, int width, int height, int neighbors);

    float& operator()(int k, int i, int j, int n);

    ~Phi() = default;
};
