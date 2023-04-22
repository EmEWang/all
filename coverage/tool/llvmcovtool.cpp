#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

void printerror(const char* str);
bool isdir(const char* str);
bool isexefile(const char* str);
void help0();
void help1();
void help();

int main(int argc, char**  argv)
{
    string htmldir = "llvmcov_html";
    vector<string> inputdir;
    vector<string> exefile;
    string llvm_merge = "llvm-profdata merge -o \%s/llvmcov_html.profdata  \%s/default.profraw";
    string llvm_cov = "llvm-cov show \
        \%s/\%s \
         \
		--show-line-counts-or-regions  \
		--show-branches=count  \
		-instr-profile=\%s/llvmcov_html.profdata -format=html -output-dir=\%s/llvmcov_html";

    if (argc == 1)
    {
        help0();
        return 0;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-h") || strcmp(argv[1], "--help"))
        {
            help();
            return 0;
        }
        else
        {
            help0();
            return 0;
        }

    }
    else
    {
        if (argc %2 != 1)
        {
            help1();
            help0();
            return 0;
        }

        int index = 0;
        for (int i = 1; i < argc; index++,i+=2)
        {
            printf("%d dir:%s exefile:%s\n",index, argv[i], argv[i+1]);
            inputdir.push_back(argv[i]);
            exefile.push_back(argv[i+1]);

            if(!isdir(argv[i]))
            {
                return 0;
            }

            if(!isexefile((inputdir[index]+"/"+exefile[index]).c_str()))
            {
                return 0;
            }
        }
    }

    char dir[1024] = {0};
    int index = 0;
    for (auto i : inputdir)
    {
        char tmp[10240] = {0};
        snprintf(tmp, sizeof(tmp), llvm_merge.c_str(), i.c_str(), i.c_str());
        // printf("llvm_merge:%s\n", tmp);
        system(tmp);

        snprintf(tmp, sizeof(tmp), llvm_cov.c_str(), i.c_str(), exefile[index++].c_str(), i.c_str(), i.c_str());
        // printf("llvmcov:%s\n", tmp);
        system(tmp);
    }

    printf("生成成功\n");
    return 0;
}

void printerror(const char* str)
{
    printf("error:%s %d %s\n", str, errno, strerror(errno));
}

bool isdir(const char* str)
{
    struct stat st;
    int ret = stat(str, &st);
    if( ret < 0)
    {
        printerror(str);
        return false;
    }

    bool b = S_ISDIR(st.st_mode);

    if (!b)
    {
        printf("%s is not a directory\n", str);
    }

    return b;
}

bool isexefile(const char* str)
{
    struct stat st;
    int ret = stat(str, &st);
    if( ret < 0)
    {
        printerror(str);
        return false;
    }

    bool b = S_ISREG(st.st_mode);
    // printf("file:%s %d\n", str, b);
    if (!b)
    {
        printf("%s is not a normal file\n", str);
        return b;
    }

    b = S_IXUSR &st.st_mode;
    if (!b)
    {
        printf("%s is not a executable file\n", str);
    }

    return b;
}

void help0()
{
    printf("使用 -h or --help 获取更多信息\n");
}
void help1()
{
    printf("参数错误\n");
}
void help()
{
    printf("说明: llvmcovtool 在指定的目录下 输出 html格式的覆盖率信息\n");
    printf("格式: llvmcovtool dir1 exe1 [dir2 exe2] ....\n");
    printf("参数: dirX 目标目录\n");
    printf("格式: exeX 执行文件\n");
    printf("备注: dirX exeX 需要成对出现\n");
    printf("示例: llvmcovtool ~/coverage1 tar101 ~/coverage2 tar102\n");
}
