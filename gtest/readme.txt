
单文件测试
testall.cpp
直接连接源文件进行测试 所有的测试文件都在一个文件中
g++ testall.cpp -o testall -lgtest -pthread    编译指令


组合测试
testmain.cpp              gtest 主文件
testsrc.cpp               gttst 测试src.o的文件
src.h src.cpp             src.o 的源文件
src.o                     src.o 链接文件

编译指令 顺序如下
g++ -o src.o -c src.cpp
g++ -o testsrc.o -c testsrc.cpp
g++ -o testmain.o -c testmain.cpp
g++ -o main *.o  -lgtest -pthread