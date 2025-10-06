#ifndef AFFINE_OPERATOR_H
#define AFFINE_OPERATOR_H

#include "affine.h"
#include <utility>
#include <string>
#include <vector>

class AffineOperator {
public:
    explicit AffineOperator(const std::vector<AffineTransform>& transforms);

    std::pair<double, double> operator()(const std::pair<double, double>& p);

private:
    const std::vector<AffineTransform>& transforms_ref;
};

void generateSequenceAndWrite(const AffineSystem& sys, const std::string& outFile);

#endif 