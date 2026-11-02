#include <iostream>
#include "KepToRV.hpp"
#include "RVToKep.hpp"

int main() {
    const double mu = 398600.4415;

    KeplerElements start_orbit;
    start_orbit.a = 7000.0;
    start_orbit.e = 0.001;
    start_orbit.i = 0.9006;  
    start_orbit.RAAN = 1.2566; 
    start_orbit.w = 0.0;
    start_orbit.nu = 0.7854;

    auto [r, v] = KeperovToRV(start_orbit, mu);

    std::cout << "--- POSITION & VELOCITY ---\n";
    std::cout << "r: [" << r(0) << ", " << r(1) << ", " << r(2) << "]\n";
    std::cout << "v: [" << v(0) << ", " << v(1) << ", " << v(2) << "]\n\n";

    KeplerElements final_orbit = RVToKeplerov(r, v, mu);

    std::cout << "--- RECONSTRUCTED ORBIT ---\n";
    std::cout << "a:    " << final_orbit.a << "\n";
    std::cout << "e:    " << final_orbit.e << "\n";
    std::cout << "i:    " << final_orbit.i << "\n";
    std::cout << "RAAN: " << final_orbit.RAAN << "\n";
    std::cout << "w:    " << final_orbit.w << "\n";
    std::cout << "nu:   " << final_orbit.nu << "\n";

    return 0;
}
