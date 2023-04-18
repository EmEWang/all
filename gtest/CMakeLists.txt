cmake_minimum_required(VERSION 3.10)

# set the project name
project(gmock1)     # <---  ${PROJECT_NAME}

# 指定c++标准 确保将CMAKE_CXX_STANDARD声明添加到add_executable的上面
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(gmock1 gmock1.cpp)
message("DESTDIR:${DESTDIR}")
message("CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX:${CMAKE_INSTALL_PREFIX}")
# add link library
#target_link_libraries(gmock1 pthread gtest gmock)
target_link_libraries(gmock1 -pthread -lgtest -lgmock)


# Set a default C++ compile flag
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)



target_compile_definitions(gmock1
    PRIVATE EX3
)
