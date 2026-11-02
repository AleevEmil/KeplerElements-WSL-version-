#pragma once
#include "KeplerElements.hpp"

KeplerElements RVToKeplerov(const Vector_3D& r, const Vector_3D& v, const double mu);
