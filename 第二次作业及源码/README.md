# 实验题目：多进程编程
小组名称：第12组  
小组成员：孙文宇 陈玮乾 李放  
## 实验目的
(1) 学会创建多进程程序，理解fork(),vfork()创建的子进程的特点    
(2) 学会使用有名管道和无名管道实现进程间通信  
(3) 学会使用信号机制实现进程间通信     
## 实验内容
(1) 编写fork(),vfork()多进程程序，通过输出结果比较所创建的子进程的不同之处  
(2) 编写fork()多进程程序，进程间模拟信号通信，包括信号发送、捕捉与处理  
(3) 编写fork()多进程程序，进程间实现有名管道和无名管道通信。具体要求如下：  
* 编写1个服务器程序server.c和2个客户端程序client1.c，client2.c，服务器与客户端之间采用FIFO管道通信  
* 服务器和客户端各自创建自己的子程序，父进程负责完成FIFO管道通信，子进程负责输出接收到的信息，父子进程间采用无名管道通信    
## 实验过程与结果
### 实验过程描述
(1) 编写fork()多进程程序。通过课上知识，我们已经知道fork()和vfork()之间的主要区别：fork()父子进程不共享内存并且要注意避免出现孤儿进程；vfork()父子进程共享内存并且保证子进程先于父进程运行。本实验进程间关系如下图所示：首先创建两个子进程，之后每个子进程各自再创建一个子进程，并对左支进行数据运算操作。
![流程图](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/流程图.png)  
使用fork()创建子进程，需要注意在父进程中加入wait()函数等待子进程运行完成后才退出父进程，否则会出现孤儿进程现象。此外本例中，“孙子”进程是在创建“儿子”进程的内部创建的，因此理论上本实验所创建的“儿子”进程和“孙子”进程具有包含关系。fork主要代码结构见下图，具体代码见本仓库fork.c  
![fork代码结构](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/fork代码结构.png)  
(2) 编写vfork()多进程程序。使用vfork()创建子进程，由于其保证子进程先于父进程运行，因此不会出现孤儿进程现象。此外本程序中与fork()相同，“孙子”进程是在创建“儿子”进程的内部创建的，因此理论上本实验所创建的“儿子”进程和“孙子”进程具有包含关系。vfork主要代码结构如下图，具体代码见本仓库vfork.c  
![vfork代码结构](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/vfrok代码结构.png)  
(3) 在fork多进程程序的基础上，加入信号处理程序并在child1处加入signal函数接受信号并跳转处理([signal与kill使用方法](https://blog.csdn.net/qq_42152681/article/details/90261295))，处理部分程序如下  
![signal](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/signal.png)  
(4) 编写server.c、client1.c、client2.c程序，server与client采用FIFO有名管道进行通信，各自父子进程间采用无名管道通信,通过向管道中写入数据实现进程间通信。其中申请管道程序如下  
![pipe1](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/pipe1.png)  
![pipe2](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/pipe2.png)  
### 实验结果分析
(1)运行fork程序，结果如下  
![fork结果图](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/fork结果图.png)  
分析：实验结果表明，使用wait()函数可以避免fork()创建子进程时出现孤儿进程的现象，并且在子进程完成之后父进程才结束。另外，fork()创建的子进程与父进程不会共享内存，parent：bound=3与child1：bound=2中的bound并非同一块内存区域，但是由于本实验创建的“儿子”进程与“孙子”进程有包含关系，因此“孙子”进程会共享“儿子”进程的内存，即child11：bound=3是在child1：bound=2的基础上+1所得。  
(2)运行vfork程序，结果如下  
![vfork结果图](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/vfork结果图.png)  
分析：实验结果表明，vfork()创建的“儿子”进程先于“父亲”进程运行，因此不会出现孤儿进程的现象；但是由于“儿子”进程与“孙子”进程有包含关系，也就是有先后运行关系，所以会先运行“儿子”进程，后运行“孙子”进程。另外，由于本实验创建的“儿子”进程与“孙子”进程有包含关系，因此“孙子”进程会共享“儿子”进程的内存，即child11：bound=3是在child1：bound=2的基础上+1所得；而vfork()创建的子进程与父进程会共享内存，parent：bound=6与child1：bound=2中的bound是同一块内存区域，而child1与child11又有捆绑的包含关系，因此parent：bound=6是在child1：bound=2的基础上+1再在child11：bound=3的基础上+3所得。  
(3)运行信号通信程序，结果如下  
![signalresult](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/结果.png)  
分析：从上图可见，child11向child1发送SIGINT信号，child1接收捕捉到SIGINT信号后，跳转到child1_handler函数进行处理。即通过kill函数与signal函数实现了信号的发送、捕捉与处理。  
(4)运行server.c、client1.c、client2.c程序，得到结果如下  
![server](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/server.png)  
![client1](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/cilent1.png)  
![client2](https://github.com/HaloTrouvaille/Embedded-Software-Group-12/blob/master/第二次作业及源码/图片/client2.png)  
分析：从上图可见，server与client实现了通过有名管道通信，server与client中各自进程通过无名管道进行通信，实现了信号间通过管道通信。
## 实验总结
通过本次实验，我们小组对fork、vfork创建进程方法的区别有了更深的理解和认识，也通过实验实现了进程间通过信号、管道进行通讯的方法，期间也遇到了些许问题，如signal函数与kill函数知识点模糊，但通过查找资料逐一解决。通过这次实验，对进程的知识点与通信的知识点有了更深的认识，也意识到要更加全面的学习。  
## 实验源码
见本仓库代码部分。

