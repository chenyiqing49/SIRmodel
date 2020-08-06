# SPDX-FileCopyrightText: 2019-2020 INFN
# SPDX-License-Identifier: EUPL-1.2

cmake_minimum_required(VERSION 3.10)

project(sir CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

list(APPEND CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules)
find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(sir main.cpp)
target_compile_options(sir PRIVATE -Wall -Wextra -fsanitize=address)
target_include_directories(sir PRIVATE ${SFML_INCLUDE_DIR})
target_link_options(sir PRIVATE -fsanitize=address)
target_link_libraries(sir PRIVATE ${SFML_LIBRARIES})

