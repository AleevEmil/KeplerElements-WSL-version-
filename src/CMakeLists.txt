add_library(${KeplerElements} STATIC 
    KepToRV.cpp 
    KepToRV.hpp 
    RVToKep.cpp 
    RVToKep.hpp 
    KeplerElements.hpp
    KeplerSolver.cpp
    KeplerSolver.hpp
    OrbitPredict.cpp
    OrbitPredict.hpp
)

target_link_libraries(${KeplerElements} PUBLIC Eigen3::Eigen)
target_include_directories(${KeplerElements} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})