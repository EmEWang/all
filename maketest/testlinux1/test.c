#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>
#include <float.h>

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <bits/stat.h>
#include <sys/sysmacros.h>

#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <pthread.h>

#include <dirent.h>


//C语言不支持默认参数
void printerr(const char* str);
void testtype();
void testdir(const char* dir);
void testconf();
void testFile(const char* name);
void teststdFile(const char* name);
void testmemFile();
void testsysname();
void testsigal1();
void testthread();
void testthread2();
void testthread_barrier();
void testsyslog();
void testlock();
void testmmap();
void testprocess();
void testprocess2();

// test
int main()
{
    printf("this is test program!\n");

    // testtype();
    // testdir("./");
    // testconf();
    // testFile("/home/lixiang/wjg/1");
    // teststdFile("/home/lixiang/wjg/1");
    // testmemFile();
    // testsysname();
    // testsigal1();
    // testthread();
    // testthread2();
    // testthread_barrier();
    //testsyslog();
    // testlock();
    // testmmap();
    // testprocess();
    testprocess2();

    printf("test end!\n");
}

void printerr(const char* str)
{
    printf("%s %d %s\n", str, errno, strerror(errno));
}
void testtype()
{
    int ia = 1;
    char ca = 's';
    char sza[100] = "abcd";
    void *pv = (void*)12;
    int bb[10];
    printf("int[10] %lu\n",sizeof(bb));   //40
    printf("addr sza %p\n", sza);
    printf("addr ca %p\n", &ca);
    printf("addr pv %p\n", pv);
    printf("size: long %lu\n", sizeof(long));

    struct timespec times;
    //times.tv_nsec = UTIME_NOW;
}

void testdir(const char* strdir)
{
    printf("cur dir:%s\n", strdir);
    DIR *dir;
    struct dirent *di;

    if ((dir=opendir(strdir)) == NULL)
    {
        printf("open dir error %d %s\n", errno, strerror(errno));
        return;
    }

    while ((di=readdir(dir)) != NULL)
    {
        printf("%s\n", di->d_name);
    }

    closedir(dir);
}

void testconf()
{
    printf("_SC_CLK_TCK:%ld\n", sysconf(_SC_CLK_TCK));
    printf("_SC_NZERO:%ld\n", sysconf(_SC_NZERO));
}

void testFile(const char* name)
{
    struct stat buf;
    if(stat(name, &buf ) == -1)
    {
        printf("stat error %s\n", name);
        return;
    }

    printf("file %s\n", name);
    printf("st_mode %x\n", buf.st_mode);
    printf("st_size %ld\n", buf.st_size);
    printf("st_blocks %ld st_blksize %ld\n", buf.st_blocks, buf.st_blksize);
    printf("st_nlink %lu st_inod %lu\n", buf.st_nlink, buf.st_ino);
    printf("st_dev %d/%d\n", major(buf.st_dev), minor(buf.st_dev));
    if(S_ISCHR(buf.st_mode)|| S_ISBLK(buf.st_mode))
    {
        printf("st_rdev %s %d/%d", (S_ISCHR(buf.st_dev)?"charcater":"block"),
            major(buf.st_rdev), minor(buf.st_rdev));
    }

    int fd = open(name, O_RDONLY);
    if(fd == -1)
    {
        printf("open file error %d %s\n", errno, strerror(errno));
        return;
    }
    int val;
    val = fcntl(fd, F_GETFD,0);
    fcntl(fd, F_SETFD, val);
}


void teststdFile(const char* name)
{
    FILE* pf = fopen(name,"r+");
    if (pf == NULL)
    {
        printf("fopen error %s\n", name);
        return;
    }
    fclose(pf);
}


// #include <stdio.h>
void testmemFile()  // 内存流
{
    const static int bufsize = 8;
    char buf[8] = {0};

    FILE *memfile = fmemopen(buf, bufsize, "w+");
    if(memfile == NULL)
    {
        printf("fmemopen error\n");
        return;
    }

    // 缓冲区数据 在调用 fflush fseek 之后会在当前位置写入一个null字节 fclose不会写入null字节
    memset(buf, 'a', bufsize-2);
    buf[bufsize-2] = '\0';
    buf[bufsize-1] = 'X';
    fprintf(memfile, "12");
    printf("before flush:%s\n", buf);  // before flush:aaaaaa
    fflush(memfile);
    printf("after flush:%s -> %ld %ld\n", buf, strlen(buf), ftell(memfile));  // after flush:12 -> 2 2

    memset(buf, 'b', bufsize-2);
    buf[bufsize-2] = '\0';
    buf[bufsize-1] = 'X';
    fprintf(memfile, "12");
    printf("before fseek:%s\n", buf);  // before fseek:bbbbbb
    fseek(memfile,0,SEEK_SET);
    printf("after fseek:%s -> %ld %ld\n", buf, strlen(buf), ftell(memfile));  // after fseek:bb12 -> 4 0

    memset(buf, 'c', bufsize-2);
    buf[bufsize-2] = '\0';
    buf[bufsize-1] = 'X';
    fprintf(memfile, "12");
    printf("before fclose:%s\n", buf);  // before fclose:cccccc
    fclose(memfile);
    printf("after fclose:%s -> %ld %ld\n", buf, strlen(buf), ftell(memfile)); // after fclose:12cccc -> 6 2
}


#include <sys/utsname.h>
void testsysname()
{
    char buf[1024] = {0};
    if(gethostname(buf,1024) == -1)
    {
        printf("gethostname error\n");
        return;
    }
    printf("hostname:%s\n", buf);

    struct utsname name;
    if(uname(&name) == -1)
    {
        printf("uname error\n");
        return;
    }
    printf("uname.sysname:%s\n", name.sysname);
    printf("uname.nodename:%s\n", name.nodename);
    printf("uname.release:%s\n", name.release);
    printf("uname.version:%s\n", name.version);
    printf("uname.machine:%s\n", name.machine);
    printf("uname.__domainname:%s\n", name.__domainname);

    // hostname:lixiang-ThinkCentre-M730e-N010
    // uname.sysname:Linux
    // uname.nodename:lixiang-ThinkCentre-M730e-N010
    // uname.release:5.15.0-88-generic
    // uname.version:#98~20.04.1-Ubuntu SMP Mon Oct 9 16:43:45 UTC 2023
    // uname.machine:x86_64
    // uname.__domainname:(none)
}


void sig_hup(int signal)
{
    printf("XXX-SIGHUP reveive pid=%d\n", getpid());
}
void sig_cont(int signal)
{
    printf("YYY-SIGCONT reveive pid=%d\n", getpid());
}
void print_pids(char* str)
{
    printf("%s pid=%d ppid=%d pgid=%d tpgid=%d sid=%d\n",
        str, getpid(), getppid(),getpgrp(),tcgetpgrp(STDIN_FILENO),getsid(0));
}
// https://www.cnblogs.com/klb561/p/12051027.html SIGHUP系统信号
void testsigal1()
{
    char c;
    pid_t pid;

    print_pids("parents");
    if((pid=fork())<0)
    {
        printf("fork error %d  %s\n",errno, strerror(errno));
        return;
    }

    if(pid > 0)
    {
        sleep(3);
        printf("parent exit\n");
    }
    else
    {
        print_pids("child");

        pid_t cpid;
        if((cpid = fork()) < 0)
        {
            printf("fork error %d  %s\n",errno, strerror(errno));
            return;
        }
        else if(cpid == 0)
        {
            print_pids("child of child");
            return;
        }

        // 进程组变成孤儿进程组时 每个进程会接收到 SIGCONT信号 紧接着又会收到 SIGHUP 挂断信号
        SIG_DFL,SIG_ERR,SIG_IGN;  // 信号的 默认处理方法 返回出错 忽略
        signal(SIGHUP, sig_hup);
        signal(SIGCONT, sig_cont);
        kill(getpid(), SIGTSTP);  // 给自己停止信号
        //kill(getpid(), SIGHUP);
        print_pids("child");

        if(read(STDIN_FILENO, &c, 1) != 1)
            printf("read error %d %s\n", errno, strerror(errno));

        // print_pids("child");
        printf("child exit\n");
    }

    // parents pid=317600 ppid=39756 pgid=317600 tpgid=317600 sid=39756
    // child pid=317601 ppid=317600 pgid=317600 tpgid=317600 sid=39756
    // child of child pid=317602 ppid=317601 pgid=317600 tpgid=317600 sid=39756
    // test end!
    // parent exit
    // YYY-SIGCONT reveive pid=317601
    // XXX-SIGHUP reveive pid=317601
    // child pid=317601 ppid=1 pgid=317600 tpgid=39756 sid=39756
    // read error 5 Input/output error
    // child exit

    exit(0);
}

void* tfunc1(void *arg)
{
    int *pi = (int*)arg;
    printf("thread id !!! %lu pid %d arg %d\n", pthread_self(), getpid(), *pi);
    pthread_exit((void*)234);
}
void testthread()
{
    pthread_t tid;

    int i = 123;
    void *pv = NULL;
    pthread_create(&tid, NULL, tfunc1, &i);

    pthread_join(tid, &pv);
    printf("thread id ~~~ %lu pid %d return %ld\n", pthread_self(), getpid(), (long)pv); //两者一样
    printf("thread id ~~~ %lu pid %d return %ld\n", pthread_self(), getpid(), (long)(long*)pv);

    // thread id !!! 140459472058112 pid 318797 arg 123
    // thread id ~~~ 140459472062272 pid 318797 return 234
    // thread id ~~~ 140459472062272 pid 318797 return 234
}


pthread_once_t ponce = PTHREAD_ONCE_INIT;
void tfunc_once()
{
    printf("tfunc_once\n");
}
// void tfunc2()
void* tfunc2(void* v)
{
    // 执行一次方法
    pthread_once(&ponce,tfunc_once);
    printf("thread id %lu pid %d\n", pthread_self(), getpid());
    sleep(5);
    return (void*)0;
}
void testthread2()
{
    int count = 5;
    pthread_t *tid = malloc(sizeof(pthread_t) * count);

    for (int i = 0; i < count; i++)
    {
       pthread_create(tid+i, NULL, tfunc2, NULL);
    }

    for (int i = 0; i < count; i++)
    {
        pthread_join(*(tid+i), NULL);
    }

    printf("main thread\n");
    free(tid);
}

pthread_barrier_t b;
void* tfunc_barrier(void* v)
{
    printf("int tid %lu\n", pthread_self());
    sleep(1);
    pthread_barrier_wait(&b);
    return (void*)0;
}
void testthread_barrier()
{
    int count = 3;
    pthread_barrier_init(&b, NULL, count+1);
    for (int i = 0; i < count; i++)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, tfunc_barrier, NULL);
    }
    pthread_barrier_wait(&b);
    printf("come to barrier\n");
}

#include <syslog.h>
void testsyslog()
{
    // https://zhuanlan.zhihu.com/p/62793386
    // /var/log/syslog 或 /var/log/messages
    // <34>Oct 10 20:13:14 mymachine myprogram: To be, or not to be, that is the question.
    // priority number: <34>，由 facility 和 severity 计算而来
    // timestampe: Oct 10 20:13:14
    // hostname: mymachine
    // tag: myprogram 这个通常是 program name，当其拥有 PID 时，会显示 myprogram[1234]:
    // message: To be, or not to be, that is the question.
    // facility
    // 用于表示日志的来源，人们约定用 program name 来表示日志来自哪里。具体包括：

    // LOG_USER A miscellaneous user process
    // LOG_MAIL Mail
    // LOG_DAEMON A miscellaneous system daemon
    // LOG_AUTH Security (authorization)
    // LOG_SYSLOG Syslog
    // LOG_LPR Central printer
    // LOG_NEWS Network news (e.g. Usenet)
    // LOG_UUCP UUCP
    // LOG_CRON Cron and At
    // LOG_AUTHPRIV Private security (authorization)
    // LOG_FTP Ftp server
    // LOG_LOCAL0～LOG_LOCAL7
    // 以上定义均由数字表示，如 LOG_LOCAL0 是 16，具体可以参见 RFC5424。

    // priority
    // 定义了日志的严重程度，priority 也可以用 level 来表示。包括：

    // LOG_EMERG The message says the system is unusable.
    // LOG_ALERT Action on the message must be taken immediately.
    // LOG_CRIT The message states a critical condition.
    // LOG_ERR The message describes an error.
    // LOG_WARNING The message is a warning.
    // LOG_NOTICE The message describes a normal but important event.
    // LOG_INFO The message is purely informational.
    // LOG_DEBUG The message is only for debugging purposes.
    // 以上定义均由数字表示，如 LOG_DEBUG 是 7，具体可以参见 RFC5424。

    if(0)
    {
    // setlogmask (LOG_UPTO (LOG_NOTICE));  //设置日志级别
    // setlogmask (0);
    // 参数1是个 char * 类型，为program name，若为空，会被设置成可执行文件名，也就是 argv[0]。注意"" 或 NULL，二者的意思不同。
    // ""，不包含 program name  -> Apr 16 11:21:53 10.0.0.101 [30325]: started by User 1000
    // NULL，program name 会被设置成可执行文件名 -> Apr 16 11:30:40 10.0.0.101 my_exe[31170]: started by User 1000
    openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    syslog (LOG_NOTICE, "Program started by User %d", getuid ());
    syslog (LOG_INFO, "A tree falls in a forest %m");
    closelog ();
    }

    if(1)
    {
        syslog(LOG_INFO, "test log ww");
    }
}


int lockfile(int fd, int cmd, int type, int where, off_t off, off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_whence = where;
    lock.l_start = off;
    lock.l_len = len;

    int ret = fcntl(fd, cmd, &lock);
    if (ret < 0)
    {
        printf("error fcntl %d %s\n", errno, strerror(errno));
        return ret;
    }

    if (cmd == F_GETLK)
    {
        if (lock.l_type == F_UNLCK)
        {
            return 0;
        }
        return lock.l_pid;
    }

    return ret;
}
int lockfile_rd(int fd, int where, off_t off, off_t len)
{
    return lockfile(fd, F_SETLK, F_RDLCK, where, off, len);
}
int lockfilew_rd(int fd, int where, off_t off, off_t len)
{
    return lockfile(fd, F_SETLKW, F_RDLCK, where, off, len);
}
int lockfile_wr(int fd, int where, off_t off, off_t len)
{
    return lockfile(fd, F_SETLK, F_WRLCK, where, off, len);
}
int lockfilew_wr(int fd, int where, off_t off, off_t len)
{
    return lockfile(fd, F_SETLKW, F_WRLCK, where, off, len);
}
int lockfile_un(int fd, int where, off_t off, off_t len)
{
    return lockfile(fd, F_SETLK, F_UNLCK, where, off, len);
}
int testfile_rd(int fd, int where, off_t off, off_t len)
{
    return lockfile(fd, F_GETLK, F_RDLCK, where, off, len);
}
int testfile_wr(int fd, int where, off_t off, off_t len)
{
    return lockfile(fd, F_GETLK, F_WRLCK, where, off, len);
}
void testlock()
{
    int fd = open("lockfile", O_RDWR|O_CREAT, 0666);
    if (fd < 0)
    {
        printerr("open lockfile error");
        return;
    }

    int ret;
    if((ret = testfile_wr(fd, SEEK_SET, 0, 0)) != 0)
    {
        printf("locked pid %d\n", ret);
    }

    if (lockfile_wr(fd, SEEK_SET, 0, 0) < 0)
    {
        printerr("lockfile_wr error");
        return;
    }

    ftruncate(fd, 0);

    char buf[100] = {0};
    snprintf(buf, sizeof(buf), "pid:%d\n", getpid());
    write(fd, buf, strlen(buf));
    close(fd);
}


#include <sys/mman.h>
void testmmap()
{
    const char file[] = "./mman.file";
    int fd = open(file, O_RDWR|O_CREAT, 0666);
    if (fd == -1)
    {
        printf("open file error %d %s\n", errno, strerror(errno));
        return;
    }

    const char str[] = "12345678";
    // truncate(file, 0);
    ftruncate(fd, 0);
    write(fd, str, strlen(str));

    void *mm = mmap(0, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
    {
        printf("mmap error %d\n", errno);
        return;
    }

    close(fd);

    printf("mm:%s\n", (char*)mm);
    sprintf(mm, "abc");
    printf("MM:%s\n",(char*)mm);

    munmap(mm, 0x1000);
}


// 如何确保父进程退出的同时，子进程也退出
// prctl函数可以帮助我们 第一个参数中，有一个选项，叫做PR_GET_PDEATHSIG:
// PR_SET_PDEATHSIG (since Linux 2.1.57)
//  Set the parent death signal of the calling process to arg2 (either a signal value in the range 1..maxsig,
//  or 0 to clear).
//  This is the signal that the calling process will get when its parent dies.
//  This value is cleared for the child of a fork(2) and (since Linux 2.4.36 / 2.6.23)
//  when executing a set-user-ID or set-group-ID binary, or a binary that has associated capa‐bilities
//  (see capabilities(7)).  This value is preserved across execve(2).
// 主要意思为：设置一个信号，当父进程退出的时候，子进程将会收到该信号。
#include <sys/prctl.h>
void testprocess()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork error:");
        exit(1);
    }
    if (pid == 0)
    {
        prctl(PR_SET_PDEATHSIG,SIGKILL);   //父进程退出时，会收到SIGKILL信号
        printf("child process.\n");
        printf("child  pid:%d,parent pid:%d\n",getpid(),getppid());
        printf("sleep 10 seconds.\n");
        sleep(10); //sleep一段时间，让父进程先退出，为了便于观察，sleep 10s
        printf("now child pid: %d parent pid:%d\n",getpid(),getppid());
    }
    else  //父进程
    {
        printf("parent process.\n");
        sleep(1);
    }

    // parent process.
    // child process.
    // child  pid:353270,parent pid:353269
    // sleep 10 seconds.
}


#include <sys/types.h>
#include <sys/wait.h>
void sigchild(int signo)
{
    pid_t p;
    //while(waitpid(-1,NULL,0)>0) NULL;
    int i = 0;
    waitpid(-1, &i, 0);
    //这里取得的退出状态也为2
    printf("%d\n",WEXITSTATUS(i));
}
// 子进程退出 通知父进程 信号 SIGCHLD 17
void testprocess2()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork error:");
        exit(1);
    }
    if (pid == 0)
    {
        printf("child process.\n");
        sleep(1);
        printf("child process exit.\n");
        exit(2);
    }
    else  //父进程
    {
        signal(SIGCHLD, sigchild);
        printf("parent process.\n");
        sleep(30);
        printf("parent process exit.\n");
    }
}


