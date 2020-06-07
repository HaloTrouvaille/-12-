# 综合应用实验
## 实验目的
能够综合应用课程所学的技术与工具，包括:   
(1) Socket通信  
(2) 多进程、多线程编程  
(3) 交叉调试目标端程序  
(4) 磁盘分区与文件系统创建   
(5) 模块与驱动编程  
## 实验内容
(1) 将树莓派设为智能家居Linux服务器，可用来采集并维护环境数据，如PM2.5、温度、湿度、气味、电器状态数据等。在实际环境中数据来自相应的传感器，本次试验中用scull设备模拟。有条件的小组鼓励使用真实设备采集数据。   
(2) 要求创建2个以上的scull设备，设备驱动可选择从内核源码树外(Kbuild)编译安装，或加入到内核源码树内。驱动函数要求包括： open, release, read, write, llseek, ioctl。  
(3) 实验中的环境数据存储在特定文件系统中。该文件系统要求具备属性：在线写入、持久性、断电可靠性。  
(4) PC机、移动设备或另外一个树莓派用作远程客户端，随时请求获取环境数据，客户端和服务器之间采用Socket通信。  
(5) APP编译采用交叉编译，用gdb-gdbserver交叉调试APP。 
## 实验过程与结果
整体实验框架流程如下图所示，包含Scull设备(或传感器设备)采集当前环境数据、将数据写入文件系统、树莓派端与PC端进行Socket通信传输数据。  
![框架](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/框架.png)  
### Scull设备驱动安装  
(1) 编写scull.c程序，详细代码可见本仓库代码部分scull.c，其代码主要包括：  
① 编写scull设备结构体，封装设备相关的信息  
② 确定scull设备数目及主次设备号  
③ 编写read函数，读取设备数据至用户空间。编写write函数将用户空间的数据写入设备中  
④ 对scull设备建立字符设备结构体  
⑤ 编写初始化函数，获得内核试别的设备号并分配内存空间  
(2) 编写Makefile文件，编译上述scull.c文件。主要代码如下
```
ifneq ($(KERNELRELEASE),)
        obj-m:=scull.o
else
        KERNELDIR:=/home/cwq/raspberrypi/linux
        PWD:=$(shell pwd)
all:
        $(MAKE) -C $(KERNELDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
clean:
        rm -f *.ko *.o *.mod.o *.mod.c *.symvers modul*
endif
```
(3)编写test.c文件，使用open、read、write等内核驱动函数，主要代码如下  
```
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
```
(4) 采用交叉编译的方式编译驱动模块，结果如下图所示。  
![编译](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/编译.png)  
(5) 在树莓派安装scull设备驱动，首先把交叉编译的scull.ko模块传至树莓派，进行安装；之后创建3个设备节点的设备号。执行如下指令，结果如下图所示    
```
sudo insmod scull.ko
```
![安装1](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/安装1.png)  
![安装2](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/安装2.png)  
(6) 测试scull设备驱动。在树莓派使用gcc编译执行(3)步骤中的测试程序，结果图如下  
![test](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/test.png)  
### 数据存储至文件系统  
(1) 利用如下指令查询分区情况，结果图如下  
```
sudo fdisk -l
```
![分区](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/分区.png)  
之前实验中已经创建过新分区，本实验直接使用/dev/mmcblk0p5对应的Linux类型逻辑分区。  
(2) 格式化文件系统。根据本实验需求，实验中的环境数据存储在特定文件系统中，要求具备属性:在线写入、持久性、断电可靠性，故采用如下指令安装ext3文件系统，结果图如下所示    
```
sudo mkfs.ext3 /dev/mmcblk0p5
```
![安装](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/安装.png)  
(3) 将格式化后的分区mount到树莓派某挂载点，***注：这里需要先创建挂载点，否则会报错mount point does not exist***  
最后验证是否mount成功，结果图如下  
![挂载验证](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/挂载验证.png)  
(4) 为方便日后使用，利用如下指令设置开机挂载。  
```
sudo vim /etc/fstab
```
并在/etc/fstab文件中新增如下一行
```
/dev/mmcblk0p5 /mnt/ext3fs ext3 defaults 0 2
```
### Socket通信  
本实验中利用Socket通信方法实现PC与树莓派通信，其通过open—write/read—close方式实现，基本流程框架如下图所示  
![流程概况](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/流程概况.png)
由上图Socket通信流程框架可知，其主要包括***socket()函数、bind()函数、listen()函数、connect()函数、accept()函数、read()函数、write()函数、close()函数***，在实现Socket通信时需要合理使用这些函数，函数基本使用方法如下  
(1) socket函数  
使用形式：int socket(int domain, int type, int protocol)  
socket函数对应于普通文件的打开操作。普通文件的打开操作返回一个文件描述字，而socket()用于创建一个socket描述符，它唯一标识一个socket。这个socket描述字跟文件描述字一样，其作为参数来进行一些读写操作。  
![socket](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/socket.png)  
(2) bind函数  
使用形式：int bind(int sockfd, const struct sockaddr addr, socklen_t addrlen)  
bind把一个地址族中的特定地址赋给socket，如对应AF_INET、AF_INET6就是把一个ipv4或ipv6地址和端口号组合赋给socket。  
![bind](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/bind.png)  
(3) listen函数与connect函数  
使用形式：int listen(int sockfd, int backlog)  
使用形式：int connect(int sockfd, const struct sockaddr addr, socklen_t addrlen)  
服务器在调用socket()、bind()之后就会调用listen()来监听这个socket，如果客户端这时调用connect()发出连接请求，服务器端就会接收到这个请求  
![listen1](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/listen.png)
![connect](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/connect.png)  
(4) accept函数  
使用形式：int accept(int sockfd, struct sockaddr addr, socklen_t addrlen)  
TCP服务器端依次调用socket()、bind()、listen()函数后，就会监听指定的socket地址。TCP客户端依次调用socket()、connect()函数之后就想TCP服务器发送了一个连接请求。TCP服务器监听到这个请求之后，即调用accept()函数取接收请求，连接建立成功。之后就可以read/write等网络IO操作。  
![accept](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/accept.png)  
(5) read函数与write函数  
网络I/O操作包括如下组别：read()/write()、recv()/send()、readv()/writev()、recvmsg()/sendmsg()、recvfrom()/sendto()  
(6) close函数  
在服务器与客户端建立连接之后会进行读写操作，完成读写操作即关闭相应的socket描述字  
按上述函数编写Server端与Client端的Socket通信程序，利用PC与树莓派进行测试。本实验对环境中温度、湿度及气味进行实时检测，结果如下  
![socket1](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/socket1.jpg)  
![socket2](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/socket2.jpg)  
可见，PC与树莓派已可以进行Socket通信，并显示出环境值  
### 交叉调试
完成上述三个主要部分后，将如上部分整合，在树莓派端进行调试  
(1) 利用如下指令在pc端生成调试文件，结果如下图所示  
```
arm-linux-gnueabihf-gcc -g server.c -o server_g -lm
```
![pc结果](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/pc结果.png)  
(2) 将调试文件传至树莓派，放在gdbserver文件夹下，利用如下指令在目标端执行调试，结果如下图所示  
```
./gdbserver :1234 server_g
```
![拷贝](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/拷贝.png)  
(3) 利用在Host端执行远程调试，结果如下图所示  
```
arm-linux-gnueabihf-gdb server_g
(gdb)target remote 192.168.5.5:1234
```
![交叉调试](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/交叉调试.png)  
(4) 树莓派端接受远程调试，结果如下图所示  
![交叉调试](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/交叉调试.png)  
(5) list后，分别在server端和client端打印输出之前设置断点，结果如下图所示  
![设置断点](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/设置断点.png)  
开始调试后在Host端执行client程序，此时server程序停在第一个断点之前，结果如下图所示  
![断点结果1](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/断点结果1.png)  
continue之后，server程序打印server端输出，之后server程序停在第二个断点之前，结果如下  
![断点结果2](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/断点结果2.png)  
再continue之后，server程序打印client端输出（实现APP功能），之后server程序结束，结果如下。  
![断点结果3](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第六次作业及源码/图片/断点结果3.png)  
