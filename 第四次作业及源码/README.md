# 实验题目：构建主机端开发环境(下)
## 实验目的
(1) 学会下载安装Linux及相关工具到目标机或目标机仿真环境;  
(2) 学会使用交叉编译器编译应用程序，并能够将可执行程序下载到目标机运行;  
(3) 学会使用交叉调试工具gdb-gdbserver调试应用程序。  
## 实验内容
(1) Host-Target方案1：下载安装Linux系统到开发板，其中包括bootloader、内核、模块、库、文件系 统等。建立host-target连接 ，常见连接有SSH， VNC，Putty; 
(2) Host-Target方案2：下载安装目标机仿真环境qemu，安装qemu树莓派系统;    
(3) 构建并测试开发板交叉编译器;  
(4) 建立gdb-gdbserver交叉调试环境并能够调试应用程序。   
## 实验过程与结果
(1) 本实验使用的是NVIDIA嵌入式设备Jetson Nano。经过查询资料且与老师探讨，Jetson Nano采用四核Cortex-A57处理器，符合本次实验要求。在其官方网站下载好系统镜像软件，使用相应软件将系统烧录至SD卡，插入SD卡实现Jetson Nano的系统安装。  
(2) 判断主机是否已安装ssh，运行'ps -e | grep ssh'指令后发现没有sshd，则采用如下指令在主机端安装ssh。  
```
sudo apt-get install ssh
```
![报错信息](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第四次作业及源码/图片/报错信息.png)  
运行此指令后提示上图报错，经过查询资料，可利用如下指令进行强制解锁。  
```
sudo rm /var/lib/dpkg/lock-frontend
```
至此可以在主机端安装ssh工具，并利用'service sshd start'指令开启主机端ssh功能。  
(3) 在target端利用'ifconfig'指令查询其IP地址，得到IP地址后在主机端利用ssh指令进行连接。  
```
ssh swy@192.168.1.5
```
运行上述指令后，即可完成主机端与客户端的连接。结果如下图。  
![连接结果](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第四次作业及源码/图片/连接结果.png)  
且可以通过上图结尾两条指令实现在主机端控制Jetson Nano风扇转速。至此，完成了主机端与目标板的ssh连接。  
(4) 安装gcc-arm-linux-gnueabihf编译工具，并利用如下指令添加到环境变量中  
```
export PATH=$PATH:/gcc-linaro-arm-linux/bin
```
(5) 编写test.c程序，计算有4个数字，能组成多少个互不相同且无重复数字的三位数。程序详见代码部分。通过如下指令生成在目标板端可以运行的可执行文件。  
```
arm-linux-gnueabihf-gcc test.c -o test
```
(6)利用scp指令将生成的可执行文件拷贝到目标端，如下图  
![scp](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第四次作业及源码/图片/scp.png)  
但在这步却提示:No such file。经过查找资料，Jetson Nano系统为aarch64，与树莓派等嵌入式设备不同，故生成的可执行文件无法在此系统上运行。权衡之后，小组改为用树莓派进行实验。  
(7) 改用树莓派后，运行test可执行文件，可得如下结果  
![运行结果](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第四次作业及源码/图片/运行结果.png)  
(8) 在http://ftp.gnu.org/gnu/gdb/ 下载gdb，通过源码在主机端安装gdb，目标端gdbserver。经过查询资料，发现gdb交叉调试过程中的常用指令有如下几种。  
① l : 列出程序源文件  
② r : 运行可执行文件  
③ b : 设置断点  
④ p : 将对应变量值打印出来  
(9) 对上述程序进行交叉编译并调试，通过如下指令开启对指定端口的监听，输出如图所示。  
```
./gdbserver 192.168.0.105:6666 ./test
```
![监听输出](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第四次作业及源码/图片/监听输出.png)  
尝试上述l调试指令，即打印出程序信息，结果如下图所示。  
![打印程序](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第四次作业及源码/图片/显示程序.png)  
尝试上述b调试指令，即设置断点，调试结果如下图所示。  
![断点](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第四次作业及源码/图片/断点.png)  
尝试利用clear清除断点，直接运行到程序结束，调试结果如下图所示。  
![清除断点](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第四次作业及源码/图片/清除断点.png)  
## 实验总结
通过以上实验，完成了主机端与目标端的交叉编译，且通过gdb与gdbserver实现了远程调试。




