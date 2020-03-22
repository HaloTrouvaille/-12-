#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#define BUF_SIZE 100

int main()
{
	int ret=mkfifo("client2_fifo",0755);
	if(ret==-1)
	{
		perror("mkfifo error!\n");
		return -1;
	}
	char sendbuf[BUF_SIZE];
	char recvbuf[BUF_SIZE];
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
	}else if(pid==0)
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
		close(pfd[0]);
		int read_fd=open("service_fifo",O_RDONLY);
		if(read_fd==-1)
		{
			perror("(c2) open read error!\n");
			return -1;
		}
		if(read(read_fd,recvbuf,100))
		{
		write(pfd[1],"service: ",9);
		write(pfd[1],recvbuf,strlen(recvbuf)+1);
		close(read_fd);
    }
		sleep(0.1);
		int write_fd=open("client2_fifo",O_WRONLY);
		if(write_fd==-1)
		{
			perror("(c2) open write errorr!\n");
			return -1;
		}
		printf("client2: ");
		scanf("%s",sendbuf);
		write(write_fd,sendbuf,strlen(sendbuf)+1);
		close(write_fd);
	}}
	return 0;
}
