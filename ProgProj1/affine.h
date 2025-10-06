#ifndef AFFINE_H
#define AFFINE_H

#include <vector>
#include <utility>
#include <string>
#include <cstddef>

struct AffineTransform {
    double a11, a12, a21, a22;
    double b1, b2;

    AffineTransform() = default;
    AffineTransform(double a11_, double a12_, double a21_, double a22_, double b1_, double b2_);

    std::pair<double, double> apply(const std::pair<double, double>& p) const;
};

struct AffineSystem {
    std::size_t N = 0;
    std::pair<double, double> start{ 0.0, 0.0 };
    std::vector<AffineTransform> transforms;

    void loadFromFile(const std::string& filename);
};

#endif 