#pragma once
#include <Eigen/Dense>

using Vector_3D = Eigen::Vector3d;
using Matrix_3D = Eigen::Matrix3d;

struct KeplerElements {
    double a;
    double e;
    double i;     
    double RAAN; 
    double w; 
    double nu;    
};
