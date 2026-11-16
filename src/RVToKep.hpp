#pragma once
#include <KeplerElements.hpp>

KeplerElements RVToKepler(const Vector_3D& r, const Vector_3D& v, const double mu);
