#ifndef AFFINE_OPERATOR_H
#define AFFINE_OPERATOR_H

#include "affine.h"
#include <utility>
#include <string>
#include <vector>
#include <random> 

class AffineOperator {
public:
    explicit AffineOperator(const std::vector<AffineTransform>& transforms);

    AffineOperator(const std::vector<AffineTransform>& transforms,
        std::mt19937_64 rng_in,
        std::uniform_int_distribution<int> dist_in);

    std::pair<double, double> operator()(const std::pair<double, double>& p);

private:
    const std::vector<AffineTransform>& transforms_ref;

    std::mt19937_64 rng;
    std::uniform_int_distribution<int> dist;
};

void generateSequenceAndWrite(const AffineSystem& sys, const std::string& outFile);

#endif