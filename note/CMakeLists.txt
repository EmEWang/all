


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



cmake 调用格式
1 cmake -DCMAKE_CXX_COMPILER="clang++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++" ../source # -D 配置或编译参数
  c++编译器为clang c++编译参数为-std=c++11 -stdlib=libc++  CMakeLists.txt 位置在 ../source
2 cmake -i 或 ccmake           # 交互式界面
3 cmake ctest 在CMakeLists.txt # 增加了add_test 执行单元测试
4 cmake --trace / --trace-expand  # 详细记录调用过程和处理

set(CMAKE_VERBOSE_MAKEFILE TRUE)  # 在 CMakeLists.txt 中 CMAKE_VERBOSE_MAKEFILE 设为 TRUE
  CMAKE_VERBOSE_MAKEFILE 为 True，make 在执行时是 verbose output。


内置变量
https://www.cnblogs.com/Braveliu/p/15827857.html
https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#variables-for-languages

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
if(DEFINED string1)  或  if(string1)
else()
endif()




CMakeLists.txt 中的格式与命令
https://www.hahack.com/codes/cmake/

cmake_minimum_required(VERSION 3.5)     # 设置cmake的最低版本
project (hello_cmake)                   # 设置项目名 还可指定 版本号 项目描述 项目主页 项目编程语言 C++标准  C标准为 C_STANDARD
  project(myproject VERSION 1.0 DESCRIPTION "My project" HOMEPAGE_URL "https://example.com" LANGUAGES CXX CXX_STANDARD 11)
add_executable(TARGET_NAME SOURCES)     # 生成可执行程序  如 add_executable(example main.cpp main.h)
add_library(TARGET_NAME [STATIC | SHARED | MODULE] SOURCES)   # 生成库
aux_source_directory(. DIR_SRCS)        # 查找当前目录下的所有源文件 并将名称保存到 DIR_SRCS 变量
add_subdirectory(math)                  # 添加 math 子目录 也就是math下有 子 CMakeLists.txt
set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)  # 设置变量  普通变量，相当于一个局部变量  缓存变量，相当于一个全局变量
  set(MY_GLOBAL_VAR1 "abcdef" CACHE STRING "STRING缓存变量")  # 定义一个STRIING类型缓存变量(不加FORCE选项)
  set(MY_GLOBAL_VAR2 "abc" CACHE STRING "STRING缓存变量" FORCE) # 定义一个STRIING类型缓存变量(加FORCE选项)
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

OPTION(OPTION_NAME HELP_MESSAGE DEFAULT_VALUE)  # 建立使用者选项参数
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

