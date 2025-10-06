#include "affine.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>

AffineTransform::AffineTransform(double a11_, double a12_, double a21_, double a22_, double b1_, double b2_)
    : a11(a11_), a12(a12_), a21(a21_), a22(a22_), b1(b1_), b2(b2_) {
}

std::pair<double, double> AffineTransform::apply(const std::pair<double, double>& p) const {
    double x = p.first;
    double y = p.second;
    double nx = a11 * x + a12 * y + b1;
    double ny = a21 * x + a22 * y + b2;
    return { nx, ny };
}

static bool is_comment_or_empty(const std::string& s) {
    for (char c : s) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            if (c == '#') return true;
            return false;
        }
    }
    return true;
}

void AffineSystem::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) throw std::runtime_error("Failed to open input file: " + filename);

    auto next_noncomment_line = [&](std::string& out) -> bool {
        while (std::getline(ifs, out)) {
            if (is_comment_or_empty(out)) continue;
            return true;
        }
        return false;
        };

    std::string line;
    if (!next_noncomment_line(line)) throw std::runtime_error("File is empty or incorrectly formatted (expected N).");

    {
        std::istringstream iss(line);
        long long Ni;
        if (!(iss >> Ni)) throw std::runtime_error("Failed to read N (first value).");
        if (Ni <= 0) throw std::runtime_error("N must be a natural number (>0).");
        N = static_cast<std::size_t>(Ni);
    }

    if (!next_noncomment_line(line)) throw std::runtime_error("Expected starting point after N.");
    {
        std::istringstream iss(line);
        double x0, y0;
        if (!(iss >> x0 >> y0)) throw std::runtime_error("Failed to read starting point (two real numbers).");
        start = { x0, y0 };
    }

    transforms.clear();
    while (next_noncomment_line(line)) {
        std::istringstream iss(line);
        double a11, a12, a21, a22, b1, b2;
        if (!(iss >> a11 >> a12 >> a21 >> a22 >> b1 >> b2)) {
            throw std::runtime_error("Invalid transformation format. Expected 6 real numbers per line.");
        }
        transforms.emplace_back(a11, a12, a21, a22, b1, b2);
    }

    if (transforms.empty()) throw std::runtime_error("At least one affine transformation is required in the file.");
}
