cmake_minimum_required(VERSION 3.7)

project(GeoPackageCpp)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
find_package(SQLiteCpp REQUIRED)
find_package(CLI11 REQUIRED)
find_package(GTest REQUIRED)
find_package(cpp-peglib REQUIRED)

enable_testing()
add_subdirectory(lib)
add_subdirectory(app)