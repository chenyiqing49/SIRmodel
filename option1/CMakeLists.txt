cmake_minimum_required(VERSION 3.16)

project(sir-sfml CXX)
enable_testing()

list(APPEND CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules)
find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(sir-sfml main.cpp)
target_compile_options(sir-sfml PRIVATE -c -Wall -Wextra)
target_link_libraries(sir-sfml PRIVATE sfml-window sfml-graphics sfml-system)

add_executable(run_point_tests point.test.cpp)
add_test(NAME point_tests COMMAND run_point_tests)

add_executable(run_sir_tests sir.test.cpp)
add_test(NAME sir_tests COMMAND run_sir_tests)
