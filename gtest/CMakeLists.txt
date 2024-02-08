cmake_minimum_required(VERSION 3.10)

# set the project name
project(gtest1)     # <---  ${PROJECT_NAME}

# 指定c++标准 确保将CMAKE_CXX_STANDARD声明添加到add_executable的上面
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(gtestdir gtestsrc)
set(noused_src ${gtestdir}/gtestall.cpp ${gtestdir}/gtestalldemo.cpp)
set(sub_src ${gtestdir}/gtestsub.cpp)
set(mock1_src ${gtestdir}/gmock1.cpp)

# main
# file(GLOB  src  *.cpp)   # 自动过滤文件 文件名格式为绝对路径
# list(REMOVE_ITEM src "/home/lixiang/code/all/gtest/samplem3.cpp")  # 排除文件
aux_source_directory(${gtestdir} main_src)   # 指定包含某个目录 文件名格式为相对路径
aux_source_directory(. main_src)   # 指定包含某个目录
list(REMOVE_ITEM main_src ${noused_src} ${sub_src} ${mock1_src})  # 排除文件
# message("main_src:${main_src}")
add_executable(main ${main_src})
target_link_libraries(main -pthread -lgtest)
target_include_directories(main PUBLIC .)

# gmock
add_executable(gmock1  ${mock1_src})
# add link library
#target_link_libraries(gmock1 pthread gtest gmock)
target_link_libraries(gmock1 -pthread -lgtest -lgmock)
# Set a default C++ compile flag
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
target_compile_definitions(gmock1 PRIVATE EX3)

# gtestsub 没有main函数 只有测试案例情况
# enable_testing()
add_executable(sub ${sub_src})
target_link_libraries(sub gtest_main -pthread -lgtest)
# include(GoogleTest)
# gtest_discover_tests(sub)


# message("DESTDIR:${DESTDIR}")
# message("CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
# message(STATUS "CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
# message(STATUS "CMAKE_INSTALL_PREFIX:${CMAKE_INSTALL_PREFIX}")

# # gtestsrc 以lib库的方式则运行有问题
# enable_testing()
# add_executable(main gtestsrc/gtestmain.cpp)
# file(GLOB SOURCES_test  gtestsrc/*.cpp)   # 自动过滤文件
# add_library(lib_test STATIC ${SOURCES_test})
# target_include_directories(lib_test PUBLIC ./)
# # file(GLOB SOURCES_origin  *.cpp *.c)   # 自动过滤文件
# aux_source_directory(. SOURCES_origin)   # 指定包含某个目录
# list(REMOVE_ITEM SOURCES_origin "./testall.cpp" "./testalldemo.cpp" "./gmock1.cpp")  # 排除文件
# add_library(lib_origin STATIC ${SOURCES_origin})
# target_link_libraries(main lib_test lib_origin -pthread -lgtest)
# include(GoogleTest)
# gtest_discover_tests(main)
