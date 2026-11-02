#include <KeplerSolver.hpp>
#include <cmath>

double solveKeplerNewton(double M, double e) {
    M = std::fmod(M, 2.0 * M_PI);
    if (M < 0.0) M += 2.0 * M_PI;

    double E = (M > M_PI) ? (M - e) : (M + e);  // начальное приближение

    const double tolerance = 1e-12;
    const int max_iterations = 100;

    for (int i = 0; i < max_iterations; ++i) {
        double f = E - e * std::sin(E) - M;
        double df = 1.0 - e * std::cos(E);

        double delta = f / df;
        E -= delta;

        if (std::abs(delta) < tolerance) {
            return E;
        }
    }
    return E;
}