#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <string.h>

void lockfile1();
void openfile1();

int main()
{
	printf("test file lock\n");

	lockfile1();
	lockfile1();
	
	return 0;	
}

void lockfile1()
{
  #define LOCKFILE	"/var/run/file_lock.pid"
	#define LOCKMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
	
	int fd;
	char buf[16];
	fd=open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if(fd < 0)
	{
		printf("open .pid file failed");
		return;
	}

  struct flock f1;
  f1.l_type = F_WRLCK;
  f1.l_start = 0;
  f1.l_whence = SEEK_SET;
  f1.l_len = 0;
  int ret = fcntl(fd, F_SETLK, &f1);
  printf("%d\n", ret);
	if(ret < 0)
	{
		if(errno == EACCES || errno == EAGAIN)
		{
			close(fd);
			printf("error [%d]\n", errno);
			return;
		}
		else
		{
		  close(fd);
			printf("error in IsRunning [%d]\n", errno);
			return;
		}
	}
	ftruncate(fd,0);
	sprintf(buf,"%ld",(long)getpid());
	write(fd,buf,strlen(buf)+1);
	printf("locked %d\n", getpid());
	close(fd);
	sleep(7);
	//close(fd);
}

void openfile1()
{
	#define LOCKFILE	"/var/run/file_lock.nonefile"
	#define LOCKMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
	
	int fd;
	char buf[16];
	fd=open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if(fd < 0)
	{
		printf("open .pid file failed");
		return;
	}
}
