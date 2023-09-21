// William Lopez 6252767 
// I William Lopez affirm that I wrote this program by myself without any help from other people or sources from the internet.


#include <stdio.h>
#include <string.h>

#define SLENGTH 12

// function prototype for firstClass and economy in order to call them in main

int firstClass(int seats[]);
int economy(int seats[]);

// SLENGTH is defined as 12 for the size of the int array seats which is defined
// this main class does all the interaction with the input and prints
// x is the input (1 for firstClass, 2 for economy, 0 for quit)
// run1 holds the result of a run of either function
// run2 holds the result of a run of either function
// char response is for when the input is asked if they want a seat in the other part of the plane 
// while the input is not zero

int main(){

	int seats[SLENGTH];
	for (int i = 0; i < SLENGTH; i++) {
		seats[i] = 0;
	}
        printf("Please type 1 for first class\nPlease type 2 for economy\nPlease type 0 to quit\n");
	int x;
	int run1;
	int run2;
	char response[50];

	// while the input is not 0, in order to fill up the plane or get more than one seat at a time
	// if 0 quit, if 1 first class, if 2 economy
	// return 0 exits program

	while (scanf("%d", &x) != 0){
	
	if (x == 0){
		return 0;
	}
	
	if (x == 1) {
		run1 = firstClass(seats);
		if (run1 != 13) {
			printf("You have been assigned seat F%d in first class\n", run1);
		}else{
			run2 = economy(seats);
				if (run2 != 13) {
					printf("There are no more available seats in first class. Would you like a seat in economy?\n");
					
					// if response is "no" then program quits if response is anything else then a seat is assigned in the opposite side

					scanf("%s", &response);
						if (strcmp(response,"no") == 0) {
							printf("The next flight will be tomorrow\n");
						} else { 
							printf("You have been assigned seat E%d in economy.\n", run2);
						}
				} else {
					printf("The next flight will be tomorrow\n");
					return 0;
				}
		}				
		
	}	
	if (x == 2) {
		run1 = economy(seats);
		if (run1 != 13) {
			printf("You have been assigned seat E%d in economy.\n", run1);
		} else {
			run2 = firstClass(seats);
			if (run2 != 13) {
				printf("There are no more available seats in economy. Would you like a seat in first class?\n");

				// if response is "no" then program quits if response is anything else then a seat is assigned in the opposite side

				scanf("%s", &response);
					if (strcmp(response,"no") == 0) {
						printf("The next flight will be tomorrow\n");
					} else {
						printf("You have been assigned seat F%d in first class.\n", run2);
					}
			} else {
				printf("The next flight will be tomorrow\n");
				return 0;
			}
		}
	}
	}
	
	return 0;


}

// firstClass searches through the first 4 values of seats[] and checks if the seat is taken (represented by a 1) or if it is empty (represented by a 0)
// return 13 if all the seats are taken

int firstClass(int seats[]){
	
	for (int i = 0; i < 4; i++) {
		if (seats[i] == 0) {
			seats[i] = 1;
			return (i+1);
		}
	}
	return 13;
}

// economy searches through seats[] from value 4 to 12 and check if the seat is taken (represented by a 1) or if it is empty (represented by a 0)
// return 13 if all the seats are taken

int economy(int seats[]){

	for (int i = 4; i < SLENGTH; i++) {
		if (seats[i] == 0) {
			seats[i] = 1;
			return (i+1);
		}
	}
	return 13;
}
			
	
	

