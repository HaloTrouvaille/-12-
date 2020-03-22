#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#define BUF_SIZE 100

int main()
{
	int ret=mkfifo("service_fifo",0755);
	if(ret==-1)
	{
		perror("mkfifo error!\n");
		return -1;
	}
	char sendbuf[BUF_SIZE];
	char recvbuf1[BUF_SIZE];
	char recvbuf2[BUF_SIZE];
	char buff[BUF_SIZE];
	pid_t pid;
	int pfd[2];
	if(pipe(pfd)<0)
	{
		perror("pipe error!");
		return 0;
	}
	pid=fork();
	if(pid<0)
	{
		perror("fork error!");
		return 0;
	}
	else if(pid==0)
	{
		while(1)
		{
		close(pfd[1]);
		sleep(1);
		read(pfd[0],buff,BUF_SIZE);
		printf("%s\n",buff);
		}

	}else{
	while(1)
	{
		int write_fd=open("service_fifo",O_WRONLY);
		if(write_fd==-1)
		{
			perror("(s) open write error!\n");
			return -1;
		}
		printf("service: ");
		scanf("%s",sendbuf);
		write(write_fd,sendbuf,strlen(sendbuf)+1);
		sleep(0.5);
		write(write_fd,sendbuf,strlen(sendbuf)+1);
		close(write_fd);
		close(pfd[0]);
		int read_fd1=open("client1_fifo",O_RDONLY);
		if(read_fd1==-1)
		{
			continue;
		}
		if(read(read_fd1,recvbuf1,BUF_SIZE))
		{

			write(pfd[1],"client1: ",9);
			write(pfd[1],recvbuf1,strlen(recvbuf1)+1);
			close(read_fd1);
		}
		int read_fd2=open("client2_fifo",O_RDONLY);
		if(read_fd2==-1)
		{
			continue;
		}
		if(read(read_fd2,recvbuf2,BUF_SIZE))
		{

			write(pfd[1],"client2: ",9);
			write(pfd[1],recvbuf2,strlen(recvbuf2)+1);
			close(read_fd1);
		}
		sleep(1);

	}
}

	return 0;
}
