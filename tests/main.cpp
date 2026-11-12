#include <iostream>
#include <cmath>
#include <KepToRV.hpp>
#include <RVToKep.hpp>

int main() {
    const double mu = 398600.4415;   // км^3/с^2

    KeplerElements kep0;
    kep0.a    = 7000.0;   // км
    kep0.e    = 0.001;
    kep0.i    = 0.9006;   // рад
    kep0.RAAN = 1.2566;   // рад
    kep0.w    = 0.3;      // рад
    kep0.nu   = 0.7854;   // рад

    auto [r, v] = KeperovToRV(kep0, mu);

    std::cout << "--- kep -> (r, v) ---\n";
    std::cout << "r = [" << r(0) << ", " << r(1) << ", " << r(2) << "]\n";
    std::cout << "v = [" << v(0) << ", " << v(1) << ", " << v(2) << "]\n\n";

    KeplerElements kep1 = RVToKeplerov(r, v, mu);

    std::cout << "--- (r, v) -> kep ---\n";
    std::cout << "a    = " << kep1.a    << "  (было " << kep0.a    << ")\n";
    std::cout << "e    = " << kep1.e    << "  (было " << kep0.e    << ")\n";
    std::cout << "i    = " << kep1.i    << "  (было " << kep0.i    << ")\n";
    std::cout << "RAAN = " << kep1.RAAN << "  (было " << kep0.RAAN << ")\n";
    std::cout << "w    = " << kep1.w    << "  (было " << kep0.w    << ")\n";
    std::cout << "nu   = " << kep1.nu   << "  (было " << kep0.nu   << ")\n\n";

    // проверка: повторный переход должен вернуть те же r, v
    auto [r2, v2] = KeperovToRV(kep1, mu);
    std::cout << "|r2 - r| = " << (r2 - r).norm() << "\n";
    std::cout << "|v2 - v| = " << (v2 - v).norm() << "\n";

    return 0;
}