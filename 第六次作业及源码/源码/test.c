#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fcntl.h>

int main()
{
    int fd;
    char buf_write[5] = "12345";
    char buf_read[5];
    if((fd=open("/dev/myscull_0", O_RDWR)) == -1){
        printf("open error\n");
        return 0;
    }
    printf("open ok\n");
    write(fd, buf_write, sizeof(buf_write));
    //llseek(fd, 0, SEEK_SET);
    lseek(fd, 0, SEEK_SET);
    read(fd, buf_read, 5);
    printf("buf_read is %s\n", buf_read);
	ioctl("/dev/myscull_0", fd);
	//release("/dev/myscull_0", fd);
    return 0;
}
