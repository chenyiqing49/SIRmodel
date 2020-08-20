cmake_minimum_required(VERSION 3.16)

project(sir-sfml CXX)
enable_testing()

list(APPEND CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules)
find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(sir-sfml main.cpp)
target_compile_options(sir-sfml PRIVATE -Wall -Wextra)
target_link_libraries(sir-sfml PRIVATE sfml-window sfml-graphics sfml-system)
target_link_options(sir-sfml PRIVATE -fsanitize=address)

add_executable(run_board_test board.test.cpp)
add_test(NAME board_test COMMAND run_board_test)

add_executable(run_point_test point.test.cpp)
add_test(NAME point_test COMMAND run_point_test)

