#include <RVToKep.hpp>
#include <cmath>

KeplerElements RVToKeplerov(const Vector_3D& r, const Vector_3D& v, const double mu) {
    const double r_cmas = r.norm();
    const double v_mag = v.norm();

    const Vector_3D h = r.cross(v);
    const double h_cmas = h.norm();

    const double a = 1.0 / (2.0 / r_cmas - (v_mag * v_mag) / mu);

    const double r_scal_v = r.dot(v);
    const Vector_3D e_vec = ((v_mag * v_mag - mu / r_cmas) * r - r_scal_v * v) / mu;
    const double e = e_vec.norm();

    const double i = std::atan2(std::sqrt(h(0)*h(0) + h(1)*h(1)), h(2));

    const Vector_3D z_axis(0.0, 0.0, 1.0);
    const bool z_parallel_h = (std::abs(h(0)) == 0.0 && std::abs(h(1)) == 0.0);
    
    const Vector_3D n = z_parallel_h ? Vector_3D(1.0, 0.0, 0.0) : Vector_3D(z_axis.cross(h).normalized());

    const double RAAN = std::atan2(n(1), n(0));

    const Vector_3D e1 = (e == 0.0) ? n : Vector_3D(e_vec.normalized());    

    const Vector_3D d1 = n;
    const Vector_3D d2 = (h / h_cmas).cross(n);

    const double w_cos = d1.dot(e1);
    const double w_sin = d2.dot(e1);
    const double w = std::atan2(w_sin, w_cos);

    const Vector_3D e2 = (h / h_cmas).cross(e1);

    const double nu_cos = e1.dot(r);
    const double nu_sin = e2.dot(r);
    const double nu = std::atan2(nu_sin, nu_cos);                           

    return {.a = a, .e = e, .i = i, .RAAN = RAAN, .w = w, .nu = nu};
}
