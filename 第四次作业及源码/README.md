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
### 实验过程
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


