#include <nanobind/nanobind.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/eigen/dense.h>

#include <KepToRV.hpp>
#include <RVToKep.hpp>
#include <OrbitPredict.hpp>
#include <KeplerSolver.hpp>

namespace nb = nanobind;

using namespace nb::literals; 

NB_MODULE(orbit_py, m) {
    m.doc() = "Биндинги для библиотеки OrbitLib";

    nb::class_<KeplerElements>(m, "KeplerElements")
        .def(nb::init<>())
        .def_rw("a", &KeplerElements::a)
        .def_rw("e", &KeplerElements::e)
        .def_rw("i", &KeplerElements::i)
        .def_rw("RAAN", &KeplerElements::RAAN)
        .def_rw("w", &KeplerElements::w)
        .def_rw("nu", &KeplerElements::nu);

    m.def("kep_to_rv", &KeperovToRV, "kep"_a, "mu"_a,
          "Перевод элементов Кеплера в радиус-вектор и скорость");
          
    m.def("rv_to_kep", &RVToKeplerov, "r"_a, "v"_a, "mu"_a,
          "Перевод радиус-вектора и скорости в элементы Кеплера");

    m.def("predict_orbit", &predictOrbit, "r0"_a, "v0"_a, "dt"_a, "mu"_a,
          "Прогноз орбиты на время dt");
}