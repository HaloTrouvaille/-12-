#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>


void child1_handler(int signum)
{
	if (signum == SIGINT) printf("child1 capture SIGINT!\n");
	if (signum == SIGTSTP) printf("child1 captue SIGTSTP!\n");
}

int main(void){

    pid_t child1, child2, child11, child21, flag;
    int bound = 0;
    while(1){
    if ((child1 = vfork()) == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child1 == 0){
        puts("This is child1 process");
        printf("pid= %d, ppid= %d\n", getpid(), getppid());
        signal(SIGINT, child1_handler);
	signal(SIGTSTP, child1_handler);
        if ((child11 = fork()) == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (child11 == 0){
            puts("This is child11 process");
            //bound += 1;
            printf("pid= %d, ppid= %d\n", getpid(), getppid());
            //printf("bound= %d\n\n", bound);
	    flag = kill(child1, SIGINT);
            exit(EXIT_SUCCESS);
        }
        else{
            wait(&child11);
            puts("Child11 process has finished");
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_SUCCESS);
    }
    if ((child2 = fork()) == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child2 == 0){
        puts("This is child2 process");
        printf("pid= %d, ppid= %d\n\n", getpid(), getppid());

	//flag = kill(child1, SIGINT);
	if (flag == 0){
		printf("kill to child1 OK\n");}
        if ((child21 = fork()) == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (child21 == 0){
            puts("This is child21 process");
            printf("pid= %d, ppid= %d\n\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
        else{
            wait(&child21);
            puts("Child21 process has finished");
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_SUCCESS);
    }
    else{
        bound += 3;
        puts("This is parent process");
        printf("pid= %d, ppid= %d\n", getpid(), getppid());
        printf("bound= %d\n\n", bound);
        wait(&child1);
        puts("Child1 process has finished");
        wait(&child2);
        puts("Child2 process has finished");
        exit(EXIT_SUCCESS);
    }
}}
