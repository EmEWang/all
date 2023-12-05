
cmake_minimum_required(VERSION 3.10)
project(testlinux2)
add_executable(main main.cpp)
file(GLOB SOURCES_LIB  *.cpp)
add_library(lib_linux2 STATIC ${SOURCES_LIB})
target_link_libraries(main PRIVATE lib_linux2)


