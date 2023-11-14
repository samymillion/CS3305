/*  Program by: Samuel Gebretsion
    Student Number: 251173970
    CS3305 Assignment 2
    October 11th, 2023 */
    
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int summation(int start, int end)
{
	int sum = 0;
	if (start < end)
	{
		sum = ((end * (end + 1)) - (start * (start - 1))) / 2;
	}
	return sum;
}

int ith_part_start(int i, int N, int M)
{
	int part_size = N / M;
	int start = i * part_size;
	return start;
}
int ith_part_end(int i, int N, int M)
{
	int part_size = N / M;
	int end = (i < M - 1) ? ((i + 1) * part_size - 1) : N;
	return end;
}
int main(int argc, char **argv)
{
    
    printf("parent(PID %d): process started\n\n", getpid());
    
    //take comand line arguments
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    int port[2]; //initialize pipe ports
    int totalSum = 0;
    int pid;
    
    pipe(port); //set up pipe
    
    printf("parent(PID %d): forking child_1\n", getpid());  
	pid = fork(); //fork child_1
	wait(NULL); //parent waits for child_1 to complete
	
	if(pid == 0){ //check we are in child_1
	
        printf("parent(PID %d): fork successful for child_1 (PID %d)\n", getppid(), getpid());
        
        printf("parent(PID %d): waiting for child_1 (PID %d) to complete \n", getppid(), getpid());
        
        printf("child_1(PID %d): process started from parent (PID %d)\n\n",getpid(), getppid());
        
        printf("child_1(PID %d): forking child_1.1....child1.%d\n\n",getpid(), M);
        
        for(int x = 0; x < M; x++){ //loop M times
            
            pid = fork(); //fork child_1.M processes
            wait(NULL);
            
            if (pid == 0) {
                printf("child_1.%d(PID %d): fork() successful\n",(x+1), getpid());
                int partialSum = summation(ith_part_start(x, N, M), ith_part_end(x, N, M)); // calculate partial sums
                printf("child_1.%d(PID %d): partial sum:[%d-%d] = %d\n", x + 1, getpid(), ith_part_start(x, N, M), ith_part_end(x, N, M), partialSum);
                write(port[1], &partialSum, sizeof(int)); //write partial sums to writing port
                exit(0); // Child should exit after calculating its part
            }
        }
	    
        if(pid!=0){
            for(int x=0; x<M; x++){ //loop to read and sum partial sums from pipe
                int readValue;
                read(port[0], &readValue, sizeof(int)); 
                totalSum += readValue;
            }
        }
    	    
        printf("\nchild_1(PID %d): total sum = %d\n", getpid(), totalSum);
        printf("child_1(PID %d): child_1 completed\n\n", getpid());
	    
	}
	
	else{
	    printf("parent(PID %d): parent completed\n", getpid());
	    return 0;
	}
}