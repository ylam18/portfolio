/*
    William Lopez PID: 6252767 
    This program creates n number of readers and 1 writer. The writer edits a value once at a time up to 25000. The readers, one at a time, read 2000000 times and print out
    the shared value that the writer edited. This solution is starvation free.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1

struct shared_data
   {
   int value;     /* shared variable to store result*/
   };

struct shared_data  *counter;


sem_t semReader, semWriter;

//reader is a function for the reader threads and counts up to 2000000 each and prints when the readers are done reading.
void* reader(void* arg){

        sleep(1);
        int updates; 
        int read_counter = 0;
        
        sem_wait(&semReader); //entry
        read_counter++;
        if(read_counter == 1 && counter -> value < 25000){
            sem_wait(&semWriter);
        }
        sem_post(&semReader);

        for(updates = 0; updates < 2000000; updates++){ //READING SECTION/CRITICAL SECTION

        }

        sem_wait(&semReader);
        read_counter--;
        if(read_counter == 0){
            sem_post(&semWriter);
        }
        sem_post(&semReader); //exit

        printf("I am Reader %d, and the shared value is %d \n", *(int*)arg + 1, counter -> value); //remainder

}

//writer is a function for the writer thread and edits a shared value to 25000 whenever reader signals
void* writer(void* arg){

        sem_wait(&semWriter); //entry
        
        while(counter -> value < 25000){ //WRITER SECTION/CRITICAL SECTION
            counter -> value += 1;
        }
        
        sem_post(&semWriter); //exit
        if(counter -> value == 25000){ //remainder
                printf("Writer has finished\n", counter->value);
            }

}



int main(int argc, char* argv[])
{
    int thread_Num;
    if(argc == 2){
        thread_Num = atoi(argv[1]);
    }else{
        printf("Too many arguments");
        return 0;
    }

    counter = malloc(sizeof(struct shared_data));
    (*counter).value = 0;
    pthread_t threadR[thread_Num], thread_Writer;
    
    sem_init(&semReader, 0, 1);
    sem_init(&semWriter, 0, 1);


    //pthread_create and pthread_join start and end both the reader and writer threads
    int i;
    for(i = 0; i < thread_Num; i++){
        int* arg = malloc(sizeof(int));
        *arg = i;
        if(pthread_create(&threadR[i], NULL, &reader, arg) != 0){
            perror("Failed to create thread");
        }
    }
    if(pthread_create(&thread_Writer, NULL, &writer, NULL) != 0){
        perror("Failed to create thread");
    }

    for(i = 0; i < thread_Num; i++){
        if(pthread_join(threadR[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }
    if(pthread_join(thread_Writer, NULL) != 0){
            perror("Failed to join thread");
        }


    sem_destroy(&semReader);
    sem_destroy(&semWriter);


    return 0;
}
