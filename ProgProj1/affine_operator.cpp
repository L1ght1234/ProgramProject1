#include "affine_operator.h"
#include <random>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <cassert>

AffineOperator::AffineOperator(const std::vector<AffineTransform>& transforms)
    : transforms_ref(transforms),
    rng(std::random_device{}()),
    dist(0, transforms.empty() ? 0 : static_cast<int>(transforms.size() - 1))
{
    if (transforms.empty()) throw std::invalid_argument("AffineOperator: empty transformation list.");
}

AffineOperator::AffineOperator(const std::vector<AffineTransform>& transforms, std::mt19937_64 rng_in, std::uniform_int_distribution<int> dist_in)
    : transforms_ref(transforms), rng(std::move(rng_in)), dist(std::move(dist_in))
{
}

std::pair<double, double> AffineOperator::operator()(const std::pair<double, double>& p) {
    static thread_local std::mt19937_64 local_rng(std::random_device{}());
    std::uniform_int_distribution<int> local_dist(0, static_cast<int>(transforms_ref.size() - 1));
    int idx = local_dist(local_rng);
    return transforms_ref[static_cast<std::size_t>(idx)].apply(p);
}

void generateSequenceAndWrite(const AffineSystem& sys, const std::string& outFile) {
    std::ofstream ofs(outFile);
    if (!ofs) throw std::runtime_error("Failed to open output file for writing: " + outFile);

    std::pair<double, double> p = sys.start;
    ofs << std::setprecision(10) << std::fixed;
    ofs << p.first << ' ' << p.second << '\n';

    AffineOperator op(sys.transforms);
    for (std::size_t i = 1; i < sys.N; ++i) {
        p = op(p);
        ofs << p.first << ' ' << p.second << '\n';
    }
}