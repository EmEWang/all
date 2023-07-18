
#include <bits/stdc++.h>

using namespace std;

void twonum();
void vectortime();

int main()
{
    vectortime();

    return 0;
}


void twonum()
{
    int a = 0;
    int b = 0;
    printf("input two integer\n");
    int i = scanf("%d%d",&a, &b);

    if(i != 2)
        printf("blease input two integer! your input is %d\n", i);
    else
        printf("result %d\n", a + b);
}

void vectortime()
{
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
    chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();

    vector<string> vctstr;
    {
        for(int i = 0; i < 1; ++i)
        {
            for (int j = 0; j < 10000; j++)
            {
                vctstr.push_back("aaa");
            }

            end = chrono::steady_clock::now();
            printf("push_back time:%lld\n", chrono::duration_cast<chrono::microseconds>(end-start).count());
            vctstr.clear();

            start = chrono::steady_clock::now();
            for (int j = 0; j < 10000; j++)
            {
                vctstr.emplace_back("aaa");
            }
            end = chrono::steady_clock::now();
            printf("emplace_back time:%lld\n", chrono::duration_cast<chrono::microseconds>(end-start).count());
            vctstr.clear();
        }
    }

    // push_back time:1217
    // emplace_back time:623
}


