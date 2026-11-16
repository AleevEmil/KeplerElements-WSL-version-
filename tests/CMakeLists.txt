find_package(GTest REQUIRED)
include(GoogleTest)

# GTest
add_executable(propagate_test test_propagate.cpp)
target_compile_features(propagate_test PRIVATE cxx_std_20)
target_link_libraries(propagate_test PRIVATE OrbitLib GTest::gtest_main)
gtest_discover_tests(propagate_test)

# Старые тесты
add_executable(kepler_test        main.cpp)
add_executable(first_prediction   first_prediction.cpp)

foreach(test_target kepler_test first_prediction)
    target_compile_features(${test_target} PRIVATE cxx_std_20)
    target_link_libraries(${test_target} PRIVATE OrbitLib)
endforeach()