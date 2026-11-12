# Тестовые программы
add_executable(kepler_test        main.cpp)
add_executable(first_prediction   first_prediction.cpp)

foreach(test_target kepler_test first_prediction)
    target_compile_features(${test_target} PRIVATE cxx_std_20)
    target_link_libraries(${test_target} PRIVATE OrbitLib)
endforeach()