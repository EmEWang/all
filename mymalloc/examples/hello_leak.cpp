#include <iostream>


int func()
{
    int *pi = new int(11);            // new 不显示泄露
    char *pc = (char*)malloc(1);
    return 0;
}

int main()
{
    std::cout << "memery leak test" << std::endl;
    func();

    // int *pi = new int(11);
    // char *pc = (char*)malloc(1);

    return 0;
}