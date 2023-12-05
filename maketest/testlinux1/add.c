#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <setjmp.h>        // 长跳转 4.1

const int ilinemax = 1024;
jmp_buf jmpbuffer;        // 长跳转 4.2
int iend = 0;

void sig_int(int sig);
int writetofile(const char* msg);

int main()
{
    int i1,i2,n;
    char line[ilinemax];
    char *errorstr = "invalid input\n";
    if(signal(SIGINT, sig_int) == SIG_ERR)
    {
        printf("signal error %d %s\n", errno, strerror(errno));
        return 0;
    }
    while((n=read(STDIN_FILENO,line,ilinemax) ) > 0 && !iend)
    {
        line[n] = 0;
        time_t t = time(0);
        struct tm *tt = localtime(&t);
        fprintf(stdout,"[%d-%02d-%02d %02d:%02d:%02d]",
            tt->tm_year+1970, tt->tm_mon+1, tt->tm_mday, tt->tm_hour, tt->tm_min,tt->tm_sec);
        printf("add read line:%s", line);
        fflush(stdout);     //连接管道后 为全缓冲类型 需要冲洗 否则printf中的不显示

        if(sscanf(line, "%d%d", &i1, &i2) != 2)
        {
            n = strlen(errorstr);
            if (write(STDOUT_FILENO, errorstr, n) != n)
            {
                printf("write error %d\n", getpid());
            }
        }
        else
        {
            fflush(stdout);
            sprintf(line, "add %d %d is %d\n",i1, i2, i1+i2);
            n = strlen(line);
            if (write(STDOUT_FILENO, line, n) != n)
            {
                printf("write add error %d\n", getpid());
            }
        }
    }

    // 下边主要是为了验证本功能是否正常退出
    if (setjmp(jmpbuffer) != 0)           // 长跳转 4.4
         printf("jmpbuffer to here\n");

    writetofile("add exit normal.\n");
    // printf("%s : %d\n", "main", writetofile("add exit normal.\n"));

    return 0;
}

void sig_int(int sig)     // 截获^C中断
{
    printf("sig_int %d %s\n", sig, strsignal(sig));
    // longjmp(jmpbuffer, 1);         // 长跳转 4.3  暂时不用 因为是阻塞在read调用中
    writetofile("SIGINT.\n");
    // printf("%s : %d\n", "sig_int", writetofile("SIGINT.\n"));
    iend = 1;
}
int writetofile(const char* msg)
{
    int ofd = open("add.tmp", O_RDWR|O_CREAT|O_APPEND, 0666); // *** open默认从文件头开始 截断 O_TRUNC
    int ret = 0;
    if (ofd < 0)
    {
        printf("open error %d %s\n", errno, strerror(errno));
        return -1;
    }
    pid_t pid = getpid();
    // ftruncate(ofd, 0); // 截断
    time_t t = time(0);
    struct tm *ts= localtime(&t);
    char context[60];
    sprintf(context, "[%d-%02d-%02d %02d:%02d:%02d]%-9d :%s",
      ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, pid, msg);
    ret = 1;
    printf("write:%ld\n", write(ofd, context, strlen(context)));
    ret = 2;
    printf("close:%d\n", close(ofd));
    // fflush(stdout);
    return ret;
}
