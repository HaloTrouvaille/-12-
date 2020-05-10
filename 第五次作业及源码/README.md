# 构建目标系统
## 实验目的
(1) 掌握裁剪Linux内核的方法，理解内核选项的意义；  
(2) 熟悉编译内核并加载内核到目标系统的方法与过程；  
(3) 了解模块与内核的关系，掌握内核模块配置编译、安装与卸载流程，为进一步编程，如驱动编程打下基础；  
(4) 掌握创建、安装(卸载)并使用文件系统的方法。
## 实验内容
(1) 首先用默认配置重新编译一遍已安装到开发板的内核，将新的内核替换现有内核，检查是否通过！  
(2) 在原始版本基础上，重新配置Linux内核，构建一个嵌入式的Linux内核；  
(3) 编译安装重新配置后的内核、模块及dtbs设备树；  
(4) 针对默认配置中不少于10个kernel feature进行重新配置(裁剪为主、偶有增加)，并解释理由；(Y=>N，N=>Y)  
(5) 保留必要的模块安装，剩余(占多数)取消；(M=>N)  
(6) make后将新的内核安装到开发板运行测试；  
(7)选择至少二个模块加载与卸载，检查是否加载、卸载成功；  
(8)构建并安装至少一款不同于根文件系统、用于应用开发的其它文件系统。
## 实验过程与结果
(1) 将最新的aarch64交叉编译工具下载到虚拟机上，指令如下  
```
sudo apt-get install -y bc build-essential gcc-aarch64-linux-gnu git unzip
```
安装成功后结果如下图所示  
![aarch64](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第五次作业及源码/图片/aarch64.png)  
(2) 从github上将最新内核下载到虚拟机上，指令如下  
```
git clone git://github.com/raspberrypi/linux.git
git clone git://github.com/raspberrypi/tools.git
```
git clone后结果如下图所示  
![git](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第五次作业及源码/图片/git.png)  
(3) 按照作业要求，先生成默认的配置文件，指令如下  
```
cd linux
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcmrpi3_defconfig
```
运行后结果如下图所示，配置写入了.config文件中  
![make](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第五次作业及源码/图片/make.png)  
(4) 按照作业要求，使用默认配置编译内核，指令如下  
```
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-  -j 8
```
编译过程如下图所示，此处因为虚拟机分配处理器数量与核心数量较少，导致编译时间过长  
![makej8](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第五次作业及源码/图片/makej8.png)  
(5) 按默认配置编译通过后，尝试对内核进行裁剪，将不需要的功能裁剪掉，重新配置内核，所用指令如下  
```
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
```
运行指令后，会进入下图界面选择对内核功能的裁剪与保留  
![menucfg](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第五次作业及源码/图片/menucfg.png)  
通过资料查询，得到各选项对应功能含义如下：  
* analog devices ADXL34x Three-Axis Digital Accelerometer 三轴加速度计  
* ATI/Philips USB RF remote control USB射频远程控制  
* networking--->wireless--->cfg80211 用于对无线设备进行配置管理  
* amateur radio support 业余广播支持  
* WiMAX Wireless Broadband support 无线支持  
* NFC subsystem support NFC子系统支持  
* Bluetooth subsystem support 蓝牙子系统支持  
* Analog Devices AD714x Capacitance Touch Sensor 电容式触摸传感器  
* CAN bus subsystem support 使用CAN总线子系统支持  
* device drivers---> Input device support ---> Touchscreens 使用触摸屏  
* Namespaces support 命名空间  
本小组项目实现过程中不需要以上功能模块，故可对以上部分进行裁剪，得到更小的内核(***Y代表保留，N代表裁剪，回车进入文件目录，ESC退出文件目录***)，将修改后的配置文件保存为.config文件，结果图如下  
![chgcfg](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第五次作业及源码/图片/chgcfg.png)  
![savecfg](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第五次作业及源码/图片/savecfg.png)  

(6) 获得修改内核配置的配置文件后，重新对内核进行编译，指令如下  
```
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-  -j 8
```
(7)编译完成后，与步骤4类似，将生成的内核、设备树等划分到启动分区中，使用指令如下  
```
sudo mount /dev/sdb1 mnt/fat32  
sudo mount /dev/sdb2 mnt/ext4    #启动分区
sudo cp arch/arm64/boot/Image /mnt/boot/kernelchange.img #拷贝镜像
sudo make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- INSTALL_MOD_PATH=/mnt/ modules_install #安装内核
sudo echo kernel=kernelchange.img >> /mnt/boot/config.txt #配置镜像
```

### 实验过程描述
### 实验结果分析
## 实验总结
