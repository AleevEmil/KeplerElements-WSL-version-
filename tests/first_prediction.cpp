#include <iostream>
#include <cmath>
#include <numbers>
#include <tuple>
#include <KepToRV.hpp>
#include <OrbitPredict.hpp>

int main() {
    const double mu = 398600.4418;   // км^3/с^2

    // Начальное состояние: круговая орбита радиуса r0_mag в плоскости Oxy
    const double r0_mag = 7000.0;                       // км
    const Vector_3D r0(r0_mag, 0.0, 0.0);               // км
    const Vector_3D v0(0.0, std::sqrt(mu / r0_mag), 0.0); // км/с

    // Период круговой орбиты: T = 2*pi*sqrt(a^3/mu), a = r0_mag
    const double T = 2.0 * std::numbers::pi
                   * std::sqrt(r0_mag * r0_mag * r0_mag / mu);

    // Через один полный период состояние должно совпасть с начальным
    const std::tuple<Vector_3D, Vector_3D> result_full = predictOrbit(r0, v0, T, mu);
    const Vector_3D r1 = std::get<0>(result_full);
    const Vector_3D v1 = std::get<1>(result_full);

    const double dr = (r1 - r0).norm();
    const double dv = (v1 - v0).norm();

    std::cout << "--- predictOrbit: полный период ---\n";
    std::cout << "r0 = [" << r0(0) << ", " << r0(1) << ", " << r0(2) << "]\n";
    std::cout << "r1 = [" << r1(0) << ", " << r1(1) << ", " << r1(2) << "]\n";
    std::cout << "v0 = [" << v0(0) << ", " << v0(1) << ", " << v0(2) << "]\n";
    std::cout << "v1 = [" << v1(0) << ", " << v1(1) << ", " << v1(2) << "]\n";
    std::cout << "|r1 - r0| = " << dr << "\n";
    std::cout << "|v1 - v0| = " << dv << "\n\n";

    // Через половину периода тело должно оказаться в противоположной точке 
    const std::tuple<Vector_3D, Vector_3D> result_half = predictOrbit(r0, v0, T / 2.0, mu);
    const Vector_3D r_half = std::get<0>(result_half);
    const Vector_3D v_half = std::get<1>(result_half);

    std::cout << "--- predictOrbit: полпериода ---\n";
    std::cout << "r(T/2) = [" << r_half(0) << ", " << r_half(1) << ", " << r_half(2) << "]\n";
    std::cout << "v(T/2) = [" << v_half(0) << ", " << v_half(1) << ", " << v_half(2) << "]\n";
    std::cout << "ожидалось r ≈ [" << -r0_mag << ", 0, 0]\n";
    std::cout << "ожидалось v ≈ [0, " << -std::sqrt(mu / r0_mag) << ", 0]\n";

    return 0;
}