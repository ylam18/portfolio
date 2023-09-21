/*
    William Lopez PID: 6252767 
    This program determines how many page faults will occur with a FIFO replacement policy given a memory size and file with pages.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    /*
        Get the file and memory size from the command line through argv[]
    */
    FILE *sample;
    int memSize;
    if(argc == 3){
        sample = fopen(argv[1],  "r");
        memSize = atoi(argv[2]);
    }
    /*
        Check the size of the memory to ensure it is between 1 and 10.
    */
    if(!(memSize <= 10 && memSize >= 1)){
        exit(-1);
    }

    int pages[memSize];
    int temp;
    char tempChar;
    int pflag;
    int pageFaults = memSize;
    /*
        Create the original array of memory dependent on memory size given
    */
    for(int i = 0; i < memSize; i++){
        fscanf(sample, "%d%c", &temp, &tempChar);
        pages[i] = temp;
    }
    /*
        Scan the line of integers with spaces inbetween while checking if the array changes by applying the FIFO replacement policy
    */
    while(!feof(sample)){
        fscanf(sample, "%d%c", &temp, &tempChar);
        pflag = 0;
        for(int i = 0; i < memSize; i++){
            if(pages[i] != temp){
                pflag++;
            }else{
                pflag = 0;
            }
        }
        if(pflag == memSize){
            for(int j = 0; j < memSize - 1; ++j){
                pages[j] = pages[j+1];
            }
            pages[memSize - 1] = temp;
            pageFaults++;
        } 
}

    printf("FIFO: %d page faults\n", pageFaults);
    printf("Final state of memory: ");
    for(int i = 0; i < memSize; i++){
        printf("%d ", pages[i]);
    }

}