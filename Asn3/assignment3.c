/*  Program by: Samuel Gebretsion
    Student Number: 251173970
    CS3305 Assignment 3
    October 24th, 2023 */

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
#include <pthread.h>


int input_array[4]; //gloobal input array

void *sum(void *thread_id){ //sum function
    
    int *id = (int *)thread_id; //read thread_id
    
    //read X and Y
    int X = input_array[0]; 
    int Y = input_array[1];
    
    printf("thread_1 (TID %d) reads X = %d and Y = %d from input_array\n", *id,X,Y);
    
    //calculate and write sum
    int S = X + Y;
    input_array[2] = S;

    printf("thread_1 (TID %d) writes X + Y = %d to the input_array[2]\n", *id, S);
    return NULL;
}

void *even_odd(void *thread_id){
    
    int *id = (int *)thread_id; //read thread_id
    
    int S = input_array[2]; //read sum
    
    printf("thread_2 (TID %d) reads %d from the input_array[2]\n", *id, input_array[2]); 
    
    if((S%2)==0)
        printf("thread_2 (TID %d) identifies that %d is an even number\n", *id, input_array[2]);
    else
        printf("thread_2 (TID %d) identifies that %d is an odd number\n", *id, input_array[2]);

    return NULL;
}

void *multiplication(void *thread_id){

    int *id = (int *)thread_id; //read thread_id
    
    int M = input_array[0] * input_array[1]; //multiplication
    input_array[3] = M; //write to input_array
    
    printf("thread_2 (TID %d) reads X and Y from input_array[],writes X * Y = %d to input_array[3]\n", *id, input_array[3]);

    return NULL;
}

void *reverse_num(void *thread_id){

    int *id = (int *)thread_id; //read thread_id
    
    int M = input_array[3]; //read in M
    
    printf("thread_3 (TID %d) reads %d from input_array[3]\n", *id, input_array[3]);


    int reversedNumber = 0, remainder, n = input_array[3];
    
    //reversee and store number
    while (n != 0) {
        remainder = n % 10;
        reversedNumber = reversedNumber * 10 + remainder;
        n /= 10;
    }
    
    printf("thread_3 (TID %d) reverses the number %d -> %d\n", *id, input_array[3], reversedNumber);
    
    return NULL;
}

int main(int argc, char *argv[])
{
    int X = atoi(argv[1]);
    int Y = atoi(argv[2]);
    
    printf("parent (PID %d) receives X = %d and Y = %d from the user\n", getpid(), X, Y);
    
    
    input_array[0] = X;
    input_array[1] = Y;
    
    printf("parent (PID %d) writes X = %d and Y = %d to input_array[]\n", getpid(), X, Y);
    
    pthread_t thread1, thread2, thread2_1, thread3;
    int thread_1_ID = 100, thread_2_ID = 101, thread_3_ID = 102;

    // Create thread_1
    pthread_create(&thread1, NULL, sum, &thread_1_ID);
    pthread_join(thread1, NULL);

    // Create thread_2 for even_odd
    pthread_create(&thread2, NULL, even_odd, &thread_2_ID); 
    pthread_join(thread2, NULL);

    // Create thread_2 for multiplication
    pthread_create(&thread2, NULL, multiplication,&thread_2_ID); 
    pthread_join(thread2, NULL);

    // Create thread_3
    pthread_create(&thread3, NULL, reverse_num, &thread_3_ID);
    pthread_join(thread3, NULL);

    return 0;
}

