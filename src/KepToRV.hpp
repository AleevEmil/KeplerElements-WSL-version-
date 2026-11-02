#pragma once
#include <tuple>
#include "KeplerElements.hpp"

std::tuple<Vector_3D, Vector_3D> KeperovToRV(const KeplerElements& kep, const double mu);
