#include <OrbitPredict.hpp>
#include <RVToKep.hpp>
#include <KepToRV.hpp>
#include <KeplerSolver.hpp>
#include <cmath>

std::tuple<Vector_3D, Vector_3D> predictOrbit(const Vector_3D& r0, const Vector_3D& v0, double dt, double mu) {

    KeplerElements kep = RVToKeplerov(r0, v0, mu);

    // nu0 -> E0
    const double sqrt_1_e2 = std::sqrt(1.0 - kep.e * kep.e);
    const double denom_nu = 1.0 + kep.e * std::cos(kep.nu);

    const double sin_E0 = (std::sin(kep.nu) * sqrt_1_e2) / denom_nu;
    const double cos_E0 = (kep.e + std::cos(kep.nu)) / denom_nu;
    const double E0 = std::atan2(sin_E0, cos_E0);

    // средняя аномалия M0
    const double M0 = E0 - kep.e * std::sin(E0);

    // Прогноз средней аномалии: M = M0 + M'
    const double n = std::sqrt(mu / (kep.a * kep.a * kep.a));
    const double M = M0 + n * dt;

    const double E = solveKeplerNewton(M, kep.e);

    // E -> nu
    const double denom_E = 1.0 - kep.e * std::cos(E);

    const double sin_nu = (std::sin(E) * sqrt_1_e2) / denom_E;
    const double cos_nu = (std::cos(E) - kep.e) / denom_E;
    kep.nu = std::atan2(sin_nu, cos_nu);

    return KeperovToRV(kep, mu);
}