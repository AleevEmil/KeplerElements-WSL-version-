#include <gtest/gtest.h>
#include <OrbitPredict.hpp>
#include <RVToKep.hpp>
#include <KepToRV.hpp>
#include <cmath>

const double mu = 398600.4418;

// 1. Тест на прямую и обратную конвертацию
TEST(KeplerTests, RoundTrip) {
    KeplerElements kep;
    kep.a = 7000.0;
    kep.e = 0.01;
    kep.i = 0.5;
    kep.RAAN = 0.3;
    kep.w = 0.4;
    kep.nu = 0.5;

    auto [r1, v1] = KeplerToRV(kep, mu);
    KeplerElements kep_out = RVToKepler(r1, v1, mu);
    
    auto [r2, v2] = KeplerToRV(kep_out, mu);
    
    EXPECT_NEAR((r1 - r2).norm(), 0.0, 1e-9);
    EXPECT_NEAR((v1 - v2).norm(), 0.0, 1e-9);
}

// 2. Тест на сохранение энергии
TEST(ConservationTests, EnergyConservation) {
    Vector_3D r0(7000.0, 0.0, 0.0);
    Vector_3D v0(0.0, std::sqrt(mu / 7000.0), 2.0);
    
    double E0 = 0.5 * v0.squaredNorm() - mu / r0.norm();
    
    double dt = 3600.0;
    for (int i = 1; i <= 10; ++i) {
        auto [r, v] = predictOrbit(r0, v0, dt * i, mu);
        double E = 0.5 * v.squaredNorm() - mu / r.norm();
        EXPECT_NEAR(E, E0, 1e-9);
    }
}

// 3. Тест на сохранение момента импульса
TEST(ConservationTests, AngularMomentumConservation) {
    Vector_3D r0(7000.0, 0.0, 0.0);
    Vector_3D v0(0.0, std::sqrt(mu / 7000.0), 2.0);
    
    Vector_3D h0 = r0.cross(v0);
    
    double dt = 3600.0;
    for (int i = 1; i <= 10; ++i) {
        auto [r, v] = predictOrbit(r0, v0, dt * i, mu);
        Vector_3D h = r.cross(v);
        
        EXPECT_NEAR(h(0), h0(0), 1e-9);
        EXPECT_NEAR(h(1), h0(1), 1e-9);
        EXPECT_NEAR(h(2), h0(2), 1e-9);
    }
}