cmake_minimum_required(VERSION 3.15)
project(OrbitLib LANGUAGES CXX)

cmake_minimum_required(VERSION 3.10)
project(OrbitLib)

# Ищем Python
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)

# Подключаем локальную папку nanobind
add_subdirectory(nanobind)

find_package(Eigen3 REQUIRED)

# Собираем вашу библиотеку и тесты
add_subdirectory(src)
add_subdirectory(tests)

# Собираем Python-модуль
nanobind_add_module(orbit_py python/bindings.cpp)
target_link_libraries(orbit_py PRIVATE OrbitLib)