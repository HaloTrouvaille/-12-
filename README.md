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
(5)实验通过autotools自动生成Makefile，并完成常用的make操作，结果见实验结果分析部分 
### 实验结果分析
