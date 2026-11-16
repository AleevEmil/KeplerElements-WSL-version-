#include <nanobind/nanobind.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/eigen/dense.h>

#include <KepToRV.hpp>
#include <RVToKep.hpp>
#include <OrbitPredict.hpp>
#include <KeplerSolver.hpp>

namespace nb = nanobind;
using namespace nb::literals;

// Локальная структура для Python-интерфейса
struct Cartesian {
    Vector_3D r;
    Vector_3D v;
};

NB_MODULE(orbit_py, m) {
    nb::class_<KeplerElements>(m, "KeplerElements")
        .def(nb::init<>()) 
        .def_rw("a", &KeplerElements::a)
        .def_rw("e", &KeplerElements::e)
        .def_rw("i", &KeplerElements::i)
        .def_rw("RAAN", &KeplerElements::RAAN)
        .def_rw("w", &KeplerElements::w)
        .def_rw("nu", &KeplerElements::nu);

    // Регистрируем Cartesian с конструктором
    nb::class_<Cartesian>(m, "Cartesian")
        .def(nb::init<>())
        .def_rw("r", &Cartesian::r)
        .def_rw("v", &Cartesian::v);

    // функции возвращают Cartesian
    m.def("kep_to_rv", [](const KeplerElements& kep, double mu) {
        auto [r, v] = KeplerToRV(kep, mu);
        return Cartesian{r, v};
    }, "kep"_a, "mu"_a, "Перевод элементов Кеплера в радиус-вектор и скорость");

    m.def("rv_to_kep", &RVToKepler, "r"_a, "v"_a, "mu"_a,
          "Перевод радиус-вектора и скорости в элементы Кеплера");

    m.def("predict_orbit", [](const Vector_3D& r0, const Vector_3D& v0, double dt, double mu) {
        auto [r, v] = predictOrbit(r0, v0, dt, mu);
        return Cartesian{r, v};
    }, "r0"_a, "v0"_a, "dt"_a, "mu"_a, "Прогноз орбиты на время dt");
}