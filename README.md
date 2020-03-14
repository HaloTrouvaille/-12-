# 实验题目：构建主机端开发环境(上)
小组名称：第12组  
小组成员：孙文宇 陈玮乾 李放  
## 实验目的
(1)在建立交叉编译开发平台之前，首先需要建立主机(虚拟机/PC,或双系统)开发环境  
(2)学会使用本地gcc编译应用环境  
(3)学会使用Makefile管理应用程序  
(4)学会通过autotools生成Makefile,学会常用的make操作  
(5)学会通过git/github管理团队软件和工作文件  
## 实验内容
(1)安装主机(虚拟机或PC)Linux开发环境，Fedora，Ubuntu，Debian均可  
(2)编写C应用程序，通过本地gcc编译应用程序，如果是基于x86的主机，gcc输出的执行文件运行的是x86指令集  
(3)编写Makefile管理应用程序，为更好体现Makefile的作用，需编写多个c程序，给出所创建的Makefile的内容  
(4)通过autotools生成Makefile，完成常用的make操作(make, make install, make uninstall, make dist)  
(5)创建小组git仓库，github账号，用来存储小组工作文件以及小组报告；学习如何构建github文件，如何上传和下载github文件等  
## 实验过程与结果
### 实验过程描述
(1)下载安装Ubuntu虚拟机  
(2)编写C程序文件，主要是整数的四则运算，详细代码见实验源码  
(3)利用gcc编译执行，结果见实验结果分析部分  
(4)编写Makefile管理应用程序并运行，结果见实验结果分析部分  
(5)实验通过autotools自动生成Makefile，并完成常用的make操作，具体步骤如下，结果见实验结果分析部分  
①扫描目录，运行autoscan命令生成configure.scan文件，此文件夹会多出configure.scan和autoscan.log文件，如下图所示  
![autoscan](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/autoscan.png)  
②创建configure.ac文件，将configure.scan文件重新命名为configure.ac，并修改configure.ac文件，如下图所示  
![configure.ac](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/configure.ac.png)  
③运行aclocal指令生成aclocal.m4文件，获取autoconf创建configure所需的宏定义，并用autoconf命令生成configure脚本，并用autoheader命令生成config.h.in文件，如下图所示  
![aclocal](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/aclocal.png)  
④手工创建Makefile.am文件，如下图所示  
![Makefile.am]
⑤运行automake命令生成Makefile.in文件，其中--add-missing选项可让automake自动添加必要的模板文件，生成Makefile.in文件  
![automake]
⑥使用configure命令把Makefile.in变成最终的Makefile文件  
![configure](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/configure.png)  
⑦运行make指令，生成可执行的目标文件
![make](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/make.png)  
⑧运行生成的目标文件，并尝试make install、make uninstall、make dist指令，结果见实验结果分析部分  
### 实验结果分析
(1)gcc编译后生成可执行文件main，运行main即可得到四则运算结果  
![gcc结果](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/gcc结果.png)  
(2)  
(3)














