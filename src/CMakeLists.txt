add_library(${PROJECT_NAME} STATIC 
    KepToRV.cpp 
    KepToRV.hpp 
    RVToKep.cpp 
    RVToKep.hpp 
    KeplerElements.hpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
