#include <OrbitPredict.hpp>
#include <RVToKep.hpp>
#include <KepToRV.hpp>
#include <KeplerSolver.hpp>
#include <cmath>

std::tuple<Vector_3D, Vector_3D> predictOrbit(const Vector_3D& r0, const Vector_3D& v0, double dt, double mu) {

    KeplerElements kep = RVToKeplerov(r0, v0, mu);

    // Перевод nu0 -> E0
    double sqrt_1_e2 = std::sqrt(1.0 - kep.e * kep.e);
    double denom_nu = 1.0 + kep.e * std::cos(kep.nu);

    double sin_E0 = (std::sin(kep.nu) * sqrt_1_e2) / denom_nu;
    double cos_E0 = (kep.e + std::cos(kep.nu)) / denom_nu;
    double E0 = std::atan2(sin_E0, cos_E0);

    // средняя аномалия M0
    double M0 = E0 - kep.e * std::sin(E0);

    // Прогноз средней аномалии: M = M0 + M'
    double M_dot = std::sqrt(mu / (kep.a * kep.a * kep.a));
    double M = M0 + M_dot * dt;

    double E = solveKeplerNewton(M, kep.e);

    // E -> nu
    double denom_E = 1.0 - kep.e * std::cos(E);

    double sin_nu = (std::sin(E) * sqrt_1_e2) / denom_E;
    double cos_nu = (std::cos(E) - kep.e) / denom_E;
    kep.nu = std::atan2(sin_nu, cos_nu);

    return KeperovToRV(kep, mu);
}