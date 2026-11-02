#include "KepToRV.hpp"
#include <cmath>

std::tuple<Vector_3D, Vector_3D> KeperovToRV(const KeplerElements& kep, const double mu) {
    const double cos_nu = std::cos(kep.nu);
    const double sin_nu = std::sin(kep.nu);

    const double p = kep.a * (1 - kep.e * kep.e);                     
    const double r_cmas = p / (1.0 + kep.e * cos_nu);

    const double cos_RAAN = std::cos(kep.RAAN);
    const double sin_RAAN = std::sin(kep.RAAN);
    const double cos_w = std::cos(kep.w);
    const double sin_w = std::sin(kep.w);
    const double cos_i = std::cos(kep.i);
    const double sin_i = std::sin(kep.i);

    const Matrix_3D rot{
        {cos_RAAN * cos_w - sin_RAAN * sin_w * cos_i, -cos_RAAN * sin_w - sin_RAAN * cos_w * cos_i, sin_RAAN * sin_i},
        {sin_RAAN * cos_w + cos_RAAN * sin_w * cos_i, -sin_RAAN * sin_w + cos_RAAN * cos_w * cos_i, -cos_RAAN * sin_i},
        {sin_w * sin_i, cos_w * sin_i, cos_i}
    };

    const Vector_3D r_orb(r_cmas * cos_nu, r_cmas * sin_nu, 0.0);

    const double V = std::sqrt(mu / p); 
    const Vector_3D v_orb(-V * sin_nu, V * (kep.e + cos_nu), 0.0);

    const Vector_3D r = rot * r_orb;
    const Vector_3D v = rot * v_orb;
    
    return {r, v};
}
