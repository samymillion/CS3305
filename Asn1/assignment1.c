/*  Program by: Samuel Gebretsion
    Student Number: 251173970
    CS3305 Assignment 1
    September 27th, 2023 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    pid_t pid;
    
    printf("parent (PID %d): process started\n\n", getpid());
    
    printf("parent (PID %d): forking child_1\n", getpid());
    
    pid = fork();                                                                                           //child_1 call
    wait(NULL);                                                                                             //make parent wait for child_1
    
    
    if (pid == 0){                                                                                          //check that we are in child_1
        
        printf("parent (PID %d): fork successful for child_1 (PID %d)\n", getppid(), getpid());
        
        printf("parent (PID %d): waiting for child_1 (PID %d) to complete \n", getppid(), getpid());
        
        printf("child_1 (PID %d): process started from parent (PID %d)\n\n",getpid(), getppid());

        printf("child_1 (PID %d): forking child_1.1\n",getpid());
        
        pid = fork();                                                                                       //child_1.1 call
        wait(NULL);                                                                                         //make child_1 wait for child_1.1
       
        if(pid==0){                                                                                         //check that we are in child_1.1
            
            printf("child_1.1 (PID %d): process started from child_1 (PID %d)\n",getpid(), getppid());
            
            printf("child_1.1 (PID %d): calling an external program [./external_program1.out]\n",getpid());
            
            execl("./external_program1.out", argv[1], NULL);                                                //external_program1 call
        }
        
        printf("child_1 (PID %d): completed child_1.1\n\n",getpid());
        
        pid = fork();                                                                                       //child_1.2 call
        wait(NULL);                                                                                         //make child_1 wait for child_1.2
        
        if(pid==0){                                                                                         //check that we are in child_1.2
        
            printf("child_1 (PID %d): forking child_1.2\n",getppid());
            
            printf("child_1.2 (PID %d): process started from child_1 (PID %d)\n",getpid(), getppid());
            
            printf("child_1.2 (PID %d): calling an external program [./external_program1.out]\n",getpid());
        
            execl("./external_program1.out", argv[2], NULL);                                                //external_program1 call
        }
        
        printf("child_1 (PID %d): completed child_1.2\n\n",getpid());
        
    }
    
    else{                                                                                                   //prevent child_2 from forking during child_1's process block
        
        printf("parent (PID %d): forking child_2\n", getpid());
        
        pid = fork();                                                                                       //child_2 call
        wait(NULL);                                                                                         //make parent wait for child_2
        
        if(pid == 0){                                                                                       //make sure we are in child_2
        
            printf("parent (PID %d): fork successful for child_2 (PID %d)\n", getppid(), getpid());
            
            printf("child_2 (PID %d): process started from parent (PID %d)\n",getpid(), getppid());
            
            printf("child_2 (PID %d): calling an external program [./external_program2.out]\n",getpid());
            
            execl("./external_program2.out", argv[3], NULL);                                                //external_program2 call
        }
        
        printf("parent (PID %d): completed parent\n\n", getpid());
    }
    
    


}
