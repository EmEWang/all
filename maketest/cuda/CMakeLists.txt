
cmake_minimum_required(VERSION 3.5)
project (hello_cmake)
add_executable(example test.cpp)
# add_executable(testnv testnv.cpp)
target_link_libraries(example PUBLIC cuda cudart)
# target_link_libraries(testnv PUBLIC cuda cudart)
# add_library(TARGET_NAME [STATIC | SHARED | MODULE] SOURCES)   #生成库
# aux_source_directory(. DIR_SRCS)        #查找当前目录下的所有源文件 并将名称保存到 DIR_SRCS 变量
# add_subdirectory(math)                  #添加 math 子目录 也就是math下有 子 CMakeLists.txt
# set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)  #设置变量


