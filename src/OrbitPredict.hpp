#pragma once
#include <KeplerElements.hpp>

std::tuple<Vector_3D, Vector_3D> predictOrbit(const Vector_3D& r0, const Vector_3D& v0, double dt, double mu);