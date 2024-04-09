
https://cmake.org/                                           # 官网
https://blog.csdn.net/qq_28087491/article/details/127338068  # CMake 官方完整版
https://blog.csdn.net/irving512/article/details/108362861    # cmake Tutorial 摘要
https://gavinliu6.github.io/CMake-Practice-zh-CN/            # cmake
https://blog.csdn.net/irving512/article/details/108318416    # 《Cmake 实践》摘要

https://cmake.org/download/     # 下载cmake源码，如cmake-3.17.1.tar.gz
tar -zxv -f cmake-3.17.1.tar.gz # 解压
./bootstrap
  sudo apt-get install g++         # 更新g++ 若提示 cannot find a c++ compiler that supports
  sudo apt-get install libssl-dev  # 安装库  若提示 could not find openssl
make
sudo make install


sudo apt install cmake     # Ubuntu安装cmake 可能不是最新版本
sudo apt-get remove cmake  # 卸载cmake


cmake --version   # 验证安装版本


cmake的语法支持大小，只有系统指令是不区分大小写的，但是变量和字符串是区分大小写的。


cmake 命令行参数
cmake -DCMAKE_CXX_COMPILER="clang++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++" ../source # -D 设置CMake变量。定义变量并设置其值，例如：-DVAR_NAME=VALUE。定义布尔类型的变量，其值为ON，例如：-DVAR_NAME。定义路径类型的变量，例如：-DVAR_NAME:PATH=/path/to/dir。定义配置变量（缓存变量），例如：-DVAR_NAME:STRING=VALUE。c++编译器为clang c++编译参数为-std=c++11 -stdlib=libc++  CMakeLists.txt 位置在 ../source
cmake -S . -B build          # -S 指定源代码目录,项目根目录，包含CMakeLists.txt -B指定构建目录，即输出目录 若文件夹不存在则创建
cmake -G "Unix Makefiles" .. # -G 指定生成器，生成哪种类型的构建系统文件。"Unix Makefiles"，生成适用于Unix/Linux系统的Makefile文件。"Visual Studio 16",生成Visual Studio 2019项目文件。Ninja，Ninja构建系统的项目文件。"Xcode"，生成适用于Xcode IDE的项目文件。
cmake --build build          # --build 编译 即运行指定文件夹下的makefile
cmake --build build --config Release # 指定构建类型，如 Debug 或 Release。
cmake --build build --target install
cmake -i 或 ccmake           # 交互式界面
cmake ctest 在CMakeLists.txt # 增加了add_test 执行单元测试
cmake --trace / --trace-expand  # 详细记录调用过程和处理

-E 调用CMake内置命令。执行与构建无关的命令，如创建目录、复制/压缩文件等。这些命令不会生成Makefile或项目文件，而是在构建之外执行。
  cmake -E make_directory build     # 在当前目录下创建一个名为build的目录。
  cmake -E remove_directory build   # 递归删除build目录及其所有子目录和文件。
  cmake -E copy 1.txt build/1.txt   # 将1.txt文件从当前目录复制到build目录中。
  cmake -E tar my.tar 1.txt 2.txt   # 创建一个名为my.tar的归档文件，包含1.txt和2.txt。-E tar [...]：压缩指定文件为tar格式。

其他常用参数
  -DCMAKE_BUILD_TYPE     # 指定构建类型。使用该参数可以指定构建类型，例如Debug、Release等。
  -DCMAKE_C_COMPILER     # 指定C编译器。使用该参数可以指定使用的C编译器，例如gcc、clang等。
  -DCMAKE_CXX_COMPILER   # 指定C++编译器。使用该参数可以指定使用的C++编译器，例如g++、clang++等。
  -DCMAKE_TOOLCHAIN_FILE # 指定交叉编译工具链。使用该参数可以指定交叉编译工具链，例如Android NDK、iOS SDK等。
  -DCMAKE_SYSTEM_NAME    # 指定目标系统名称。使用该参数可以指定目标系统的名称，例如Linux、Windows、Android、iOS等。
  -DCMAKE_INSTALL_RPATH  # 指定运行时动态链接库搜索路径。使用该参数可以指定运行时动态链接库搜索路径，使得程序在运行时可以找到所需的动态链接库。
  -DCMAKE_C_FLAGS        # 指定C编译器选项。使用该参数可以指定C编译器的选项，例如-O0、-O2等。
  -DCMAKE_CXX_FLAGS      # 指定C++编译器选项。使用该参数可以指定C++编译器的选项，例如-std=c++11、-stdlib=libc++等。
  -DBUILD_SHARED_LIBS    # 指定是否构建共享库。使用该参数可以指定是否构建共享库，如果指定为ON，则生成共享库，否则生成静态库。
  -DCMAKE_VERBOSE_MAKEFILE  # 指定生成Makefile时是否显示详细信息。使用该参数可以指定是否显示详细的构建信息。
  -DCMAKE_MODULE_PATH    # 指定CMake模块路径。使用该参数可以指定CMake的模块路径，以便CMake可以找到所需的模块。
  -DCMAKE_EXPORT_COMPILE_COMMANDS  # 指定是否导出编译命令。使用该参数可以指定是否导出编译命令，以便其他工具可以使用编译命令。
  -DCMAKE_PREFIX_PATH    # 指定第三方库安装路径。使用该参数可以指定第三方库的安装路径，以便CMake可以找到所需的库文件。
  -DCMAKE_INSTALL_PREFIX # 指定安装目录。使用该参数可以指定安装目录，使得在执行make install命令时，生成的可执行文件、库文件、头文件等可以被安装到指定的目录下。




set(CMAKE_VERBOSE_MAKEFILE TRUE)  # 在 CMakeLists.txt 中 CMAKE_VERBOSE_MAKEFILE 设为 TRUE
  CMAKE_VERBOSE_MAKEFILE 为 True，make 在执行时是 verbose output。


return([PROPAGATE <var-name>...])  # 用于从文件、目录或函数返回

内置变量
https://www.cnblogs.com/Braveliu/p/15827857.html
https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#variables-for-languages
${val_x}                         # 使用变量

信息变量
CMAKE_SYSTEM                     # 系统名称，例如 Linux-2.6.22、FreeBSD-5.4-RELEASE、Windows 5.1
CAMKE_SYSTEM_NAME                # 系统名称，如 Linux、FreeBSD、Windows
CMAKE_SYSTEM_VERSION             # 系统版本，如 2.6.22
CMAKE_SYSTEM_PROCESSOR           # 处理器名称，如 i686
UNIX                             # bool，在所有的类 UNIX 平台为 TRUE，包括 OS X 和 cygwin
WIN32                            # bool，在所有的 win32 平台为 TRUE，包括 cygwin
CMAKE_MAJOR_VERSION              # cmake 主版本号，如 2.8.6 中的 2
CMAKE_MINOR_VERSION              # cmake 次版本号，如 2.8.6 中的 8
CMAKE_PATCH_VERSION              # cmake 补丁等级，如 2.8.6 中的 6

预定义变量
用 set 在 CMakeLists.txt 中设置，cmake 命令行中也使用，如 cmake -DBUILD_SHARED_LIBS=OFF
PROJECT_NAME                     # 返回通过 PROJECT 定义的项目名称
CMAKE_C_COMPILER                 # C 编译器，默认 /usr/bin/cc
CMAKE_CXX_COMPILER               # C++编译器，默认 /usr/bin/c++。 也可通过指令 ADD_DEFINITIONS() 添加
CMAKE_C_FLAGS                    # 编译 C 文件时的选项，默认为空，如 -g；也可以通过 add_definitions 添加编译选项
CMAKE_CXX_FLAGS                  # 编译 C++ 文件时的选项，默认为空
CMAKE_INCLUDE_PATH               # 添加头文件搜索路径. 默认为空。配合 FIND_FILE() 以及 FIND_PATH 使用
CMAKE_LIBRARY_PATH               # 添加库文件搜索路径. 默认为空。配合 FIND_LIBRARY() 使用
CMAKE_INSTALL_PREFIX             # 定义 cmake 安装的路径, 默认 /usr/local
PROJECT_BINARY_DIR               # 运行 cmake 命令的目录，当前项目的构建目录。通常是 ${PROJECT_SOURCE_DIR}/build，同 CMAKE_BINARY_DIR、<projectname>_BINARY_DIR
PROJECT_SOURCE_DIR               # 工程的根目录，同 CMAKE_SOURCE_DIR、<projectname>_SOURCE_DIR
CMAKE_SOURCE_DIR                 # 源码目录。
CMAKE_BINARY_DIR                 # 根二进制/构建目录。
CMAKE_CURRENT_SOURCE_DIR         # 当前处理的 CMakeLists.txt 所在的路径
CMAKE_CURRENT_BINARY_DIR         # target 编译目录;当前所在的构建目录。
  使用 ADD_SURDIRECTORY(src bin) 可以更改此变量的值;
  SET(EXECUTABLE_OUTPUT_PATH <新路径>) 并不会对此变量有影响,只是改变了最终目标文件的存储路径
CMAKE_PREFIX_PATH                # 默认为空。
  指定要搜索的安装前缀的目录 find_package()， find_program()， find_library()， find_file()，和 find_path() 命令。
  每个命令将添加相应的子目录（例如 bin，lib 或 include），作为其自己的文档中指定。默认空,由项目设定.
CMAKE_MODULE_PATH                # 默认为空。
  cmake 为上百个软件包提供了查找器 (finder):FindXXXX.cmake 当使用非 cmake 自带的 finder 时，需要指定 finder 的路径，这就是 CMAKE_MODULE_PATH，配合 FIND_PACKAGE() 使用
  SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)，然后可以用 INCLUDE 命令来调用自己的模块
CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS # 用来控制 IF ELSE 语句的书写方式，默认为空。
CMAKE_BUILD_TYPE                  # 控制构建类型。可选参数：
  None: default
  Debug: 生成调试信息
  Release: 发布版本，进行最佳化
  此值不会再 configure 的时候自动初始化，需手动设置
  命令行参数 cmake -DCMAKE_BUILD_TYPE=Debug
BUILD_SHARED_LIBS                # 将所有程序库的 target 设置为共享库。如果未设置，使用 ADD_LIBRARY 时又没有指定库类型，默认编译生成静态库
EXECUTABLE_OUTPUT_PATH           # 定义目标二进制可执行文件的存放位置，默认为空
LIBRARY_OUTPUT_PATH              # 定义目标链接库文件的存放位置，默认为空


字符串比较 https://zhuanlan.zhihu.com/p/661283261
string(COMPARE LESS string1 string2 result)
string(COMPARE EQUAL string1 string2 result)
string(COMPARE GREATER string1 string2 result)
string1和string2是要比较的两个字符串，result是一个变量，表示比较的结果。
string1小于string2，则result的值为真；string1等于string2，则result的值为真；string1大于string2，则result的值为真。

if(${string1} STREQUAL "ON")   或  if(string1 STREQUAL "ON")   # 相等
else()
endif()

if(${mainname} MATCHES "draw")   # 字符串匹配

字符串变量有无定义
if(DEFINED string1)  或  if(string1)           if(NOT DEFINED string1)
else()
endif()




CMakeLists.txt 中的格式与命令
https://www.hahack.com/codes/cmake/

cmake_minimum_required(VERSION 3.5)     # 设置cmake的最低版本
project (hello_cmake)                   # 设置项目名 还可指定 版本号 项目描述 项目主页 项目编程语言 C++标准  C标准为 C_STANDARD
  project(myproject VERSION 1.0 DESCRIPTION "My project" HOMEPAGE_URL "https://example.com" LANGUAGES CXX CXX_STANDARD 11)
add_executable(TARGET_NAME SOURCES)     # 生成可执行程序  如 add_executable(example main.cpp main.h)
add_library(TARGET_NAME [STATIC | SHARED | MODULE] SOURCES)   # 生成库
add_subdirectory(math)                  # 添加 math 子目录 也就是math下有 子 CMakeLists.txt
set(<variable> <value>... CACHE <type> <docstring> [FORCE]) # 格式 https://www.jianshu.com/p/c2c71d5a09e9
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)  # 设置变量  普通变量，相当于一个局部变量  缓存变量，相当于一个全局变量
  set(MY_GLOBAL_VAR1 "abcdef" CACHE STRING "STRING缓存变量")  # 定义一个STRIING类型缓存变量(不加FORCE选项)
  set(MY_GLOBAL_VAR2 "abc" CACHE STRING "STRING缓存变量" FORCE) # 定义一个STRIING类型缓存变量(加FORCE选项)  直接覆盖
  set(CMAKE_CXX_STANDARD 11)           # 设置C++版本
  set(CMAKE_CXX_STANDARD_REQUIRED True)
set_target_properties(mylib PROPERTIES POSITION_INDEPENDENT_CODE ON) # 表示生成位置无关代码 为目标设置编译选项 即-fPIC

target_compile_definitions(TARGET_NAME INTERFACE|PUBLIC|PRIVATE DEFINITION) # 编译 -D 选项
  target_compile_definitions(foo PUBLIC DEBUG)   # 定义 DEBUG 符号
target_compile_options(TARGET_NAME INTERFACE|PUBLIC|PRIVATE OPTION)   # 指定目标的编译选项。
  target_compile_options(o_util PUBLIC "-Wno-error=comment")  # 编译o_util时增加编译选项 "-Wno-error=comment"
target_link_libraries(TARGET_NAME PRIVATE|PUBLIC|INTERFACE LIBRARY)   # 对 TARGET_NAME 建立 LIBRARY 连接时。
  LIBRARY 一个/多个 library 的名字 绝对路径 LIBRARY 名称(libcomm.so comm -lcomm 均可)。
target_include_directories(TARGET_NAME INTERFACE|PUBLIC|PRIVATE DIR)  # 编译 TARGET_NAME 时，增加 DIR 目录到头文件搜索路径。

include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...]) # 添加头文件目录
  相当于g++的-I参数的作用，也相当于环境变量中增加路径到CPLUS_INCLUDE_PATH变量的作用。
  include_directories(../../../thirdparty/comm/include)
link_directories(dir1 dir2 ...) #  添加需要链接的库文件目录
  相当于g++的-L选项的作用，也相当于环境变量中增加LD_LIBRARY_PATH的路径的作用。
  link_directories("/home/server/third/lib")
link_libraries(lib1 <debug | optimized> lib2 ...) # 添加需要链接的库文件路径，注意是全路径 空格分隔
  link_libraries("/opt/libeng.so" "/opt/libmx.so")
find_library (<VAR> name1 [path1 path2 ...]) # 在路径中查找库name1
  find_library(mylib rt /usr/lib  /usr/local/lib NO_PATH) # 在目录中查找，若没有，mylib被赋为NO_PATH

option(OPTION_NAME HELP_MESSAGE DEFAULT_VALUE)  # 建立使用者选项参数
  option(DOWN_M "Download" ON)  # 建立DOWN_M，默认为 ON
message([MODE] "message to display")  # message 是 CMake 的 print MODE 必須填入 CMake 提供的常熟选项
execute_process(COMMAND cmd [args...] [ERROR_VARIABLE var])  # 执行子程序
  cmd要执行的程序 args要执行程序的参数 var程序执行时失败时将其设置为true的变量
  execute_process(COMMAND python ${CMAKE_CURRENT_LIST_DIR}/../tools/download_mnist.py -d ${CMAKE_BINARY_DIR}/data ERROR_VARIABLE DOWNLOAD_ERROR)
find_package(<package-name> [version] [EXACT] [QUIET] [MODULE] [REQUIRED] [[COMPONENTS] [component1 [component2 ...]]])
  # 查找外部库的依赖关系 <package-name> 是要查找的外部库的名称，version 是要查找的外部库的版本号，EXACT 表示要求精确匹配版本号，
  #QUIET 表示不输出查找信息，MODULE 表示从 CMake 模块路径中查找库，REQUIRED 表示如果找不到库则停止构建，
  #COMPONENTS 表示要查找的库的组件名称。
  find_package(Boost REQUIRED COMPONENTS filesystem system)  # 查找Boost库的依赖关系 要求filesystem和system组件都必须存在
aux_source_directory(. DIR_SRCS)         # 查找当前目录下的所有源文件 保存到 DIR_SRCS 变量  文件名格式为相对路径
  aux_source_directory(../src SRC_FILES) # 指定包含某个目录（不会包含指定目录中的子目录）
file(GLOB val_src module*/src/*.cpp)     # 过滤文件并将文件名保存在val_src 文件名格式为绝对路径
  file(GLOB_RECURSE val_src  *.cpp)      # 过滤文件并将文件名保存在val_src 迭代的方式进入所有子文件夹
  file(GLOB_RECURSE val_src  ./*.cpp)    # 只在指定的文件下查找 https://cmake.org/cmake/help/latest/command/file.html#file
  file(GLOB SOURCES_INC  module*/inc)    # 自动过滤文件夹
list(REMOVE_ITEM SRC_FILES "cpu3.cpp") # 排除指定的项
  list(APPEND EXTRA_LIBS MathFunctions)  # 添加


例如
LINK_DIRECTORIES("/opt/lib")
add_executable(myProject main.cpp)
target_link_libraries(myProject eng mx)
等价于
LINK_LIBRARIES("/opt/lib/libeng.so")
LINK_LIBRARIES("/opt/lib/libmx.so")
#LINK_LIBRARIES("/opt/lib/libeng.so" "/opt/lib/libmx.so")  可以写在一行
add_executable(myProject main.cpp)


include(CheckCXXCompilerFlag)    # 检查 CXX 编译器是否支持给定的标志 必须先包含
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)     # 检测是否支持c11 并将结果赋给 COMPILER_SUPPORTS_CXX11
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)     # 检测是否支持 c0x
CHECK_CXX_COMPILER_FLAG(-Wdate-time COMPILER_SUPPORTS_WDATE_TIME) # 检测是否支持 -Wdate-time 即 __DATE__, __TIME__, or __TIMESTAMP__这几个宏



定制安装规则 #CMakeLists.txt 文件里添加
install (TARGETS MathFunctions DESTINATION bin)      # libMathFunctions.o 文件会被复制到 /usr/local/bin 中
install (FILES MathFunctions.h DESTINATION include)  # MathFunctions.h 文件会被复制到 /usr/local/include 中
set(CMAKE_INSTALL_PREFIX "/path/to/subdir") # /usr/local/ 是默认安装根目录 修改 CMAKE_INSTALL_PREFIX 变量指定根目录

添加测试  #CMakeLists.txt 文件里添加
enable_testing()               # 启用测试
add_test (test_run Demo 5 2)   # 测试程序是否成功运行
make test                      # 运行测试案例

支持 gdb
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


编译选项设置
在CMakeLists.txt中可以通过修改CMake内置的环境变量来改变C或C++的编译选项.
编译选项相关的CMake 变量如下
CMAKE_C_FLAGS =
CMAKE_C_FLAGS_DEBUG = -g
CMAKE_C_FLAGS_MINSIZEREL = -Os -DNDEBUG
CMAKE_C_FLAGS_RELEASE = -O3 -DNDEBUG
CMAKE_C_FLAGS_RELWITHDEBINFO = -O2 -g -DNDEBUG

CMAKE_CXX_FLAGS =
CMAKE_CXX_FLAGS_DEBUG = -g
CMAKE_CXX_FLAGS_MINSIZEREL = -Os -DNDEBUG
CMAKE_CXX_FLAGS_RELEASE = -O3 -DNDEBUG
CMAKE_CXX_FLAGS_RELWITHDEBINFO = -O2 -g -DNDEBUG

CMAKE_C_FLAGS C设置参数，CMAKE_CXX_FLAGS C++设置参数。分为DEBUG，RELEASE，MINSIZEREL和RELWITHDEBINFO四种类型。

以C++语言编译选项为例
CMAKE_CXX_FLAGS_DEBUG           # 编译Debug版本的时候会采用的编译选项，默认只有一个-g选项，包含调试信息；
CMAKE_CXX_FLAGS_RELEASE         # 编译Release版本的时候采用的编译选项，默认包-O3选项，该选项表示优化等级；
CMAKE_CXX_FLAGS_MINSIZEREL      # 主要减小目标文件大小，选项-Os就是这个作用；
CMAKE_CXX_FLAGS_RELWITHDEBINFO  # 包含调试信息的Release版本，-O2和-g，优化的同时也包含了调试信息；
CMAKE_CXX_FLAGS                 # 这个选项没有默认值；

CMake在编译项目时，选项为Debug则会采用CMAKE_CXX_FLAGS_DEBUG选项

可以分别设置CMAKE_CXX_FLAGS_DEBUG和CMAKE_CXX_FLAGS_RELEASE
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wl,-rpath=../lib")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -g")

可以把公共的设置放在CMAKE_CXX_FLAGS变量里面(如上面的-std=c++11，不管是Release还是Debug都需要设置)。
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -Wl,-rpath=../lib")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")




message  # 打印消息
message([<mode>] "message to display" ...)   # 格式
message # 消息名字，可在CMakeLists.txt或者.cmake脚本文件中输入，且有提示，不区分大小写
mode    # 打印消息的类别，有FATAL_ERROR，SEND_ERROR，WARNING，AUTHOR_WARNING，DEPRECATION，
  (none) or NOTICE，STATUS，VERBOSE，DEBUG，TRACE共10种
“message to display” # 输出消息的内容，是字符串类型
…                    # 表示可变参数，可连接多个输出

mode说明  STATUS 输出到 stdout，其他到 stderr
FATAL_ERROR      # cmake出错，停止编译和生成(信息红色)
SEND_ERROR       # cmake出错，继续编译，但是停止生成(信息红色)
WARNING          # cmake警告，继续编译(信息红色)
AUTHOR_WARNING   # 开发者警告，继续编译(信息红色)
DEPRECATION      # 如果使用set方法设置CMAKE_ERROR_DEPRECATED为true(不区分大小写)，编译出错，否则继续编译
(none) or NOTICE # 不设置mode，默认是NOTICE模式，不影响编译和生成，用于打印消息(信息白色)
STATUS           # 编译时状态信息，左边以--开头(信息白色)
DEBUG            # 针对开发人员的调试信息(信息白色)
TRACE            # 日志级别的临时信息(信息白色)



CMake交叉编译Arm Linux程序
https://blog.csdn.net/whahu1989/article/details/104114515
https://zhuanlan.zhihu.com/p/100367053

CMakeLists.txt 同级目录下 新建文件 aarch_linux.cmake 内容如下
set(CMAKE_SYSTEM_NAME Linux)      # 即目标系统名 这里是Linux 该指令必须存在 1)
set(CMAKE_SYSTEM_PROCESSOR arm)   # 目标系统的处理器名，这里是arm

# set(tools /usr/)
# set(CMAKE_C_COMPILER ${tools}/bin/aarch64-linux-gnu-gcc)
# set(CMAKE_CXX_COMPILER ${tools}/bin/aarch64-linux-gnu-g++)

set(tools /usr/bin)
set(CMAKE_C_COMPILER ${tools}/aarch64-linux-gnu-gcc)   # C编译器的可执行文件名称 2)
set(CMAKE_CXX_COMPILER ${tools}/aarch64-linux-gnu-g++) # C++编译器的可执行文件名称

注:
1 支持Linux，QNX，WindowsCE，Android等。如果没有操作系统，那么就写 Generic。
  执行该指令后，cmake 变量 CMAKE_CROSSCOMPILING 会自动被设置为 TRUE，此时 cmake 就会“知道“现在执行的是交叉编译
2 由于 cmake 无法自动获取目标机器信息，因此需要显式指明编译工具。
3 上述命令必须写入脚本中，使用 -DCMAKE_TOOLCHAIN_FILE=xxx.cmake 的方式使用。
  不能直接写入 CMakeLists.txt 或使用 include(xx.cmake)

编译
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../aarch_linux.cmake ..     # 使用CMake的变量CMAKE_TOOLCHAIN_FILE来指定工具链文件
make






target_** 中的 PUBLIC，PRIVATE，INTERFACE
https://zhuanlan.zhihu.com/p/82244559

测试工程目录结构：
cmake-test/                 工程主目录，main.c 调用 libhello-world.so
├── CMakeLists.txt
├── hello-world             生成 libhello-world.so，调用 libhello.so 和 libworld.so
│   ├── CMakeLists.txt
│   ├── hello               生成 libhello.so
│   │   ├── CMakeLists.txt
│   │   ├── hello.c
│   │   └── hello.h         libhello.so 对外的头文件
│   ├── hello_world.c
│   ├── hello_world.h       libhello-world.so 对外的头文件
│   └── world               生成 libworld.so
│       ├── CMakeLists.txt
│       ├── world.c
│       └── world.h         libworld.so 对外的头文件
└── main.c

调用关系：
                                 ├────libhello.so
可执行文件────libhello-world.so
                                 ├────libworld.so
关键字用法说明：

1 PRIVATE：私有的。生成 libhello-world.so时，只在 hello_world.c 中包含了 hello.h，libhello-world.so 对外的头文件——hello_world.h 中不包含 hello.h。而且 main.c 不会调用 hello.c 中的函数，或者说 main.c 不知道 hello.c 的存在，那么在 hello-world/CMakeLists.txt 中应该写入：
target_link_libraries(hello-world PRIVATE hello)
target_include_directories(hello-world PRIVATE hello)

2 INTERFACE：接口。生成 libhello-world.so 时，只在libhello-world.so 对外的头文件——hello_world.h 中包含 了 hello.h， hello_world.c 中不包含 hello.h，即 libhello-world.so 不使用 libhello.so 提供的功能，只使用 hello.h 中的某些信息，比如结构体。但是 main.c 需要使用 libhello.so 中的功能。那么在 hello-world/CMakeLists.txt 中应该写入：
target_link_libraries(hello-world INTERFACE hello)
target_include_directories(hello-world INTERFACE hello)

3 PUBLIC：公开的。PUBLIC = PRIVATE + INTERFACE。生成 libhello-world.so 时，在 hello_world.c 和 hello_world.h 中都包含了 hello.h。并且 main.c 中也需要使用 libhello.so 提供的功能。那么在 hello-world/CMakeLists.txt 中应该写入：
target_link_libraries(hello-world PUBLIC hello)
target_include_directories(hello-world PUBLIC hello)

实际上，这三个关键字指定的是目标文件依赖项的使用范围（scope）或者一种传递（propagate）。
可执行文件依赖 libhello-world.so， libhello-world.so 依赖 libhello.so 和 libworld.so。
1 main.c 不使用 libhello.so 的任何功能，因此 libhello-world.so 不需要将其依赖—— libhello.so 传递给 main.c，hello-world/CMakeLists.txt 中使用 PRIVATE 关键字；
2 main.c 使用 libhello.so 的功能，但是libhello-world.so 不使用，hello-world/CMakeLists.txt 中使用 INTERFACE 关键字；
3 main.c 和 libhello-world.so 都使用 libhello.so 的功能，hello-world/CMakeLists.txt 中使用 PUBLIC 关键字；

include_directories(dir)
target_include_directories() 的功能完全可以使用 include_directories() 实现。还是建议使用 target_include_directories()。
include_directories(header-dir) 是一个全局包含，向下传递。什么意思呢？就是说如果某个目录的 CMakeLists.txt 中使用了该指令，其下所有的子目录默认也包含了header-dir 目录。

上述例子中，如果在顶层的 cmake-test/CMakeLists.txt 中加入：
include_directories(hello-world)
include_directories(hello-world/hello)
include_directories(hello-world/world)

那么整个工程的源文件在编译时都会增加：
-I hello-world -I hello-world/hello -I hello-world/world ...
各级子目录中无需使用 target_include_directories() 或者 include_directories()了。如果此时查看详细的编译过程（make VERBOSE=1）就会发现编译过程是一大坨，很不舒服。
当然了，在最终子目录的 CMakeLists.txt 文件中，使用 include_directories() 和 target_include_directories() 的效果是相同的。

4. 目录划分
每一个目录都是一个模块，目录内部应将对外和对内的头文件进行区分，由模块的调用者决定模块是否被传递（PRIVATE，INTERFACE，PUBLIC）。






get_filename_component  # 1 获取完整文件名的特定部分
DICECTORY   # 没有文件名的目录，路径返回时带有正斜杠，并且没有尾部斜杠。
NAME        # 不带名录的文件名
EXT         # 文件名的最长扩展名  (.b.c from d/a.b.c)
NAME_WE     # 不带目录或最长扩展名的文件名
LAST_EXT    # 文件名的最后扩展名  (.c from d/a.b.c)
NAME_WLE    # 文件目录或最后扩展名的文件名
PATH        # DIRECTORY的别名(cmake <= 2.8.11)

SET(filename /tmp/cmake.dat.log.tmp)
get_filename_component(d ${filename} DIRECTORY)             # /tmp
get_filename_component(n ${filename} NAME ABSOLUTE)         # cmake.dat.log.tmp
get_filename_component(nw ${filename} NAME_WE ABSOLUTE)     # cmake
get_filename_component(nwl ${filename} NAME_WLE ABSOLUTE)   # cmake.dat.log
get_filename_component(e ${filename} EXT ABSOLUTE)          # .dat.log.tmp
get_filename_component(le ${filename} LAST_EXT ABSOLUTE)    # .tmp


get_filename_component(<var> <FileName> <mode> [BASE_DIR <dir>] [CACHE]) # 2 指定路径与文件名进行拼接
ABSOLUTE    # 2.1 文件的完整路径
get_filename_component(absolute_file_name "cmake.dat" ABSOLUTE)
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}") # CMAKE_CURRENT_SOURCE_DIR: /tmp/test_cmake
message("absolute_file_name: ${absolute_file_name}")             # absolute_file_name: /tmp/test_cmake/cmake.dat

set(base_dir "/var/")
get_filename_component(absolute_file_name "cmake.dat" ABSOLUTE BASE_DIR ${base_dir})
message("absolute_file_name: ${absolute_file_name}")             # absolute_file_name: /var/cmake.dat

REALPATH    # 2.2 如果为链接文件，则显示完整路径
get_filename_component(relative_file_name "srs_tree" REALPATH)
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")  # CMAKE_CURRENT_SOURCE_DIR: /tmp/av_io
message("relative_file_name: ${relative_file_name}")              # relative_file_name: /test_tree

set(base_dir "/test_source/")
get_filename_component(relative_file_name "test_tree" REALPATH BASE_DIR ${base_dir})
message("relative_file_name: ${relative_file_name}")              # relative_file_name: /test_source/srs_tree


get_filename_component(<var> <FileNae> PROGRAM [PROGRAM_ARGS <arg_var>] [CACHE]) # 3 获取应用程序的名称和参数
get_filename_component(program "ls -l -h" PROGRAM PROGRAM_ARGS args)
message("program: ${program}")   # program: /usr/bin/ls     系统可识别程序
message("args: ${args}")         # args:  -l -h             系统可识别程序

get_filename_component(program "lm -l -h" PROGRAM PROGRAM_ARGS args)
message("program: ${program}")   # program:                 不可识别程序
message("args: ${args}")         # args:                    不可识别程序





流程控制

1 条件控制
if(condition)
elseif(condition)
else()
endif()

如
if(VAR1 MATCHES "Hello")
    message("this is hello")
    message("this is hello2")
elseif(VAR1 MATCHES "world")
    message("this is world")
    message("this is world2")
endif()

2 循环
2.1 foreach循环
在foreach循环中，支持break()和continue()。
foreach(loop_var arg1 arg2 ...)
  COMMAND1(ARGS ...)
  COMMAND2(ARGS ...)
  ...
endforeach(loop_var)

如
set(mylist "a" "b" c "d")
foreach(_var ${mylist})
     message("当前变量是：${_var}")
endforeach()

上面是最简单的用法，还有一个foreach(loop_var RANGE start stop [step]) 的用法。
set(result 0)
foreach(_var RANGE 0 100)
     math(EXPR result "${result}+${_var}")
endforeach()
message("from 0 plus to 100 is:${result}")

2.2 while循环
while(condition)
  COMMAND1(ARGS ...)
  COMMAND2(ARGS ...)
  ...
endwhile(condition)




find_package()
https://zhuanlan.zhihu.com/p/97369704
1 查找库路径的方式，先Module模式，再Config模式。
  1.1 Module模式
    cmake安装目录下的share/cmake-<version>/Modules/Find<LibraryName>.cmake
    另一个使我们指定的CMAKE_MODULE_PATH的所在目录
  1.2 Config模式
    /usr/local/lib/cmake/<LibraryName>/<LibraryName>Config.cmake or <lower-case-package-name>-config.cmake
2 使用
  2.1官方库，以curl库为例，假设需要引入这个库，已经定义好了FindCURL.cmake。
    find_package(CURL)
    add_executable(curltest curltest.cc)
    if(CURL_FOUND)
        target_include_directories(clib PRIVATE ${CURL_INCLUDE_DIR})
        target_link_libraries(curltest ${CURL_LIBRARY})
    else(CURL_FOUND)
        message(FATAL_ERROR ”CURL library not found”)
    endif(CURL_FOUND)
  2.2 非官方的库（该方式只对支持cmake编译安装的库有效）
  2.3每一个模块都会定义以下几个变量
    <LibaryName>_FOUND
    <LibaryName>_INCLUDE_DIR or <LibaryName>_INCLUDES
    <LibaryName>_LIBRARY     or <LibaryName>_LIBRARIES
3 编写自己的Find<LibraryName>.cmake模块
  3.1 当前目录下新建一个ModuleMode的文件夹，在里面编写自己的函数库。如add
    库函数以手写Makefile的方式进行安装，库文件安装在/usr/lib目录下，头文件放在/usr/include目录下
  3.2 cmake文件夹下新建一个FindAdd.cmake的文件。目标是找到库的头文件所在目录和共享库文件的所在位置。
    # 在指定目录下寻找头文件和动态库文件的位置，可以指定多个目标路径
    find_path(ADD_INCLUDE_DIR libadd.h /usr/include/ /usr/local/include ${CMAKE_SOURCE_DIR}/ModuleMode)
    find_library(ADD_LIBRARY NAMES add PATHS /usr/lib/add /usr/local/lib/add ${CMAKE_SOURCE_DIR}/ModuleMode)

    if (ADD_INCLUDE_DIR AND ADD_LIBRARY)
        set(ADD_FOUND TRUE)
    endif (ADD_INCLUDE_DIR AND ADD_LIBRARY)
  3.3 这时我们便可以像引用curl一样引入我们自定义的库了。
    find_package(ADD)

