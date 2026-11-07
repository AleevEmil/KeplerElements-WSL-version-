#include <KeplerSolver.hpp>
#include <cmath>
#include <numbers>
#include <limits>

double solveKeplerNewton(double M, double e) {
    M = std::remainder(M, 2.0 * std::numbers::pi);

    double E = (M > std::numbers::pi) ? (M - e) : (M + e);  // начальное приближение

    const int max_iterations = 100;

    for (int i = 0; i < max_iterations; ++i) {
        const double sin_E = std::sin(E);
        const double cos_E = std::cos(E);
        double f = E - e * sin_E - M;
        double df = 1.0 - e * cos_E;

        double delta = f / df;

        if (std::abs(delta) < 100 * std::numeric_limits<double>::epsilon()) {
            return E - delta;
        }

        E -= delta;

    }
    return E;
}