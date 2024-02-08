#include <iostream>


int func()
{
    int *pi = new int(104);            // new 不显示泄露
    char *pc = (char*)malloc(1024);
    return 0;
}

int main()
{
    std::cout << "memery leak test" << std::endl;
    for (size_t i = 0; i < 100*100; i++)
    {
        func();
    }

    // int *pi = new int(11);
    // char *pc = (char*)malloc(1);

    return 0;
}