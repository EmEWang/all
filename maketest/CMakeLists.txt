cmake_minimum_required(VERSION 3.10)
project(maketest)     # <---  ${PROJECT_NAME}
# 指定c++标准 确保将CMAKE_CXX_STANDARD声明添加到add_executable的上面
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# message("DESTDIR:${DESTDIR}")
# message("CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
# message(PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR})
# message(STATUS "CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
# target_compile_definitions(maketest PRIVATE EX3)

# 方法1 直接编译
# file(GLOB SOURCES  module1/src/*.cpp module2/src/*.cpp module3/src/*.cpp module4/src/*.cpp main.cpp)
# add_executable(maketest ${SOURCES})
# target_include_directories(maketest PRIVATE  module1/inc  module2/inc module3/inc  module4/inc)

# 方法2 静态库编译  SHARED 动态库 STATIC 静态库
add_executable(maketest main.cpp)
# file(GLOB SOURCES_LIB  module1/src/*.cpp module2/src/*.cpp module3/src/*.cpp module4/src/*.cpp)
file(GLOB SOURCES_LIB  module*/src/*.cpp)   # 自动过滤文件
add_library(lib STATIC ${SOURCES_LIB})
# target_include_directories(lib PUBLIC ${PROJECT_SOURCE_DIR}/module1/inc ${PROJECT_SOURCE_DIR}/module2/inc ${PROJECT_SOURCE_DIR}/module3/inc ${PROJECT_SOURCE_DIR}/module4/inc)
file(GLOB SOURCES_INC  module*/inc)         # 自动过滤文件夹
target_include_directories(lib PUBLIC ${SOURCES_INC})
target_link_libraries(maketest PRIVATE lib -rdynamic -ldl -pthread )

add_subdirectory(testlinux1)          # 子目录
add_subdirectory(testlinux2)          # 子目录
