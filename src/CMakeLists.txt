add_library(${PROJECT_NAME} STATIC 
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

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})