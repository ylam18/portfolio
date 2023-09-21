/*
    William Lopez PID: 6252767 
    This program creates three threads that simultaneously count up to 2000000 through 2000000 updates. The first thread will count up by 1 but will also update 100 times at once if the total count is divisible by 
    100. The second and third thread only count up by 1 2000000 times. In total the threads should each count up to 2000000 and combine to 6000000 updates/counts.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

struct shared_data
   {
   int value;     /* shared variable to store result*/
   };

struct shared_data  *counter;

//@bonus describes the amount of times bonus happens, @semCount is the semaphore being used 
int bonus = 0;
sem_t semCount;

//count is the function being used by all the threads in order to count up to 2000000 each and utilize the bonus system for one of the threads
void* count(void* arg){
    int updates; 
    for(updates = 0; updates < 2000000; updates++){ /* Entry section */
        sem_wait(&semCount);
        if((*counter).value % 100 == 0 && updates <= 1999900 && *(int*)arg == 0) { /* checks if value is divisible by 100 and if it is underneath 1999900 so that the bonus does not make updates exceed 2000000*/ /* Critical Section */
            bonus++;
            updates += 100;
            (*counter).value += 100;
            counter->value += 1;
        }else{
            counter->value += 1;
        }
        sem_post(&semCount);
    } /* Exit Section */
    if(*(int*)arg == 0){ /* Remainder Section */
        printf("I am Thread %d, I did %d updates and I got the bonus for %d times, counter = %d\n", *(int*)arg + 1, updates, bonus, counter->value);
    }else{
        printf("I am Thread %d, I did %d updates, counter = %d\n", *(int*)arg + 1, updates, counter->value);
    }
}

int main(int argc, char* argv[])
{
    int thread_Num;
    if(argc != 2){
        thread_Num = argv[1];
    }else{
        printf("Too many arguments");
        return 0;
    }

    counter = malloc(sizeof(struct shared_data));
    (*counter).value = 0;
    pthread_t thread[thread_Num];
    
    sem_init(&semCount, 0, 1);

    //pthread_create and pthread_join start and end both the threads @thread1 and @thread2 and @thread3
    int i;
    for(i = 0; i < thread_Num; i++){
        int* arg = malloc(sizeof(int));
        *arg = i;
        if(pthread_create(&thread[i], NULL, &count, arg) != 0){
            perror("Failed to create thread");
        }
    }

    for(i = 0; i < thread_Num; i++){
        if(pthread_join(thread[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }

    sem_destroy(&semCount);

    printf("from parent counter = %d", counter->value);

    return 0;
}
