

system("pause") 相当于从程序里调用"pause"命令，继而暂停。必须添加"stdlib.h" 或 "cstdlib"头文件。
但只适合DOS或Windows，不合适合Linux，这就是出现"sh: PAUSE: command not found" 的原因，在Linux可直接调用pause()。
调用系统命令system()去实现暂停程序，耗费系统资源。
C中推荐使用getchar(); C++中使用cin.get();
#include <unistd.h>
	int pause(void);
pause() 库函数使调用进程（或线程）睡眠状态，直到接收到信号，要么终止，或导致它调用一个信号捕获函数。
The pause() function only returns when a signal was caught and the signal-catching function returned. In this case pause() returns -1, and errno is set to EINTR.





c++ sizeof和alignof区别
sizeof ： 获取内存存储的大小。
alignof : 获取地址对其的大小，POD里面最大的内存对其的大小。

例子：
struct A{ //non-POD type
    int avg;
    int avg2;
    double c;
    A(int a,int b):avg((a+b)/2){

    }
};

struct B{
    int avg;
    int avg2;
    char c;
};
using namespace std;
int main() {

    cout<<"sizeof(A):"<<sizeof(A)<<endl;
    cout<<"alignof(A):"<< alignof(A)<<endl;

    cout<<"sizeof(B):"<<sizeof(B)<<endl;
    cout<<"alignof(B):"<< alignof(B)<<endl;
}
输出：
sizeof(A):16
alignof(A):8
sizeof(B):12
alignof(B):4
