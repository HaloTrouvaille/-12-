#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
void child1_handler(int signum)
{
        if (signum == SIGINT) printf("child1 capture SIGINT!\n");
        if (signum == SIGTSTP) printf("child1 captue SIGTSTP!\n");
}


int main(void){
  
    pid_t child1, child2, child11, child21,flag;
    int bound = 0;
    while(1){
    if ((child1 = vfork()) == -1){
        perror("vfork");
        exit(EXIT_FAILURE);
    }
    else if (child1 == 0){
        puts("This is child1 process");
	flag = kill(child2,SIGINT);
        //signal(SIGINT, child1_handler);
        printf("pid= %d, ppid= %d\n", getpid(), getppid());
        
        if ((child11 = vfork()) == -1){
            perror("vfork");
            exit(EXIT_FAILURE);
        }
        else if (child11 == 0){
            puts("This is child11 process");
            bound += 1;
            printf("pid= %d, ppid= %d\n", getpid(), getppid());
            printf("bound= %d\n\n", bound);
            exit(EXIT_SUCCESS);
        }
        else{
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_SUCCESS);
    }
    if ((child2 = vfork()) == -1){
        perror("vfork");
        exit(EXIT_FAILURE);
    }
    else if (child2 == 0){
        puts("This is child2 process");
	//flag = kill(child1, SIGINT);
	signal(SIGINT, child1_handler);
        printf("pid= %d, ppid= %d\n\n", getpid(), getppid());
        if ((child21 = vfork()) == -1){
            perror("vfork");
            exit(EXIT_FAILURE);
        }
        else if (child21 == 0){
            puts("This is child21 process");
            printf("pid= %d, ppid= %d\n\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
        else{
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_SUCCESS);
    }
    else{
        bound += 3;
        puts("This is parent process");
        printf("pid= %d, ppid= %d\n", getpid(), getppid());
        printf("bound= %d\n\n", bound);
        exit(EXIT_SUCCESS);
    }}
}
