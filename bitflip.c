/*This program does various bitwise functions through command line arguments.
 * I, William Lopez worked on this project alone and without any help from other sources.
 * William Lopez, 6252767
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int debug = 0;

int main(int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int c, err = 0; 
	//flags for each of the tags in the usage
	int eflag=0, fflag=0, aflag = 0, sflag=0, oflag=0;
	char *oname;
	static char usage[] = "usage: bitflip [-e] [-f] [-a] [-s] [-o outputfilename] intval";

	while ((c = getopt(argc, argv, "efaso:")) != -1)
		switch (c) {
		case 'e':
			eflag = 1;
			break;
		case 'f':
			fflag = 1;
			break;
		case 'a':
			aflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'o':
			oflag = 1;
			//name of file given to oname pointer
         		oname = optarg;
			break;
		case '?':
			err = 1;
			break;
		}
	//all temporary uint16_t for the print statements, count for for loop, *outFile to store File
	uint16_t num;
       	uint16_t temp1;
	uint16_t temp2;
	uint16_t temp3;
	uint16_t temp4 = 0;
	int count = 0; 
	FILE *outFile;

	//convert the input into a uint16_t
	num = atoi(argv[optind]);
	
	//if eflag is 1 then flip all even bits
	if(eflag == 1){
		temp1 = num ^ 0x55555555;
	}
	//if fflag is 1 then flip all odd bits
	if(fflag == 1){
		temp2 = num ^ 0xAAAAAAAA;
	}
	//if aflag is 1 then flip all bits
	if(aflag == 1){
		temp3 = ~num;
	}
	//if sflag is 1 then switch the bits from right to left
	//check if bit at position is 1 or 0, if 1 then flip the bit in temp4 which is all 0
	if(sflag == 1){
		for(int i = 16; i > 0; i--){
			if(num & (1 << (i - 1))){
				temp4 ^= 1 << count;
			}
			count++;
		}
	}
	//if oflag is 1 then print to a file of name oname, if not then print to console
	if(oflag == 1){
		outFile = fopen(oname, "w");
		if(outFile == NULL){
			exit(1);
		}
		fprintf(outFile, "Value: %d\nEven bits flipped: %d\nOdd bits flipped:  %d\nAll bits flipped: %d\nSwitched all bits: %d\n", num, temp1, temp2, temp3, temp4);
		fclose(outFile);
	}else{
		printf("Value: %d\nEven bits flipped: %d\nOdd bits flipped:  %d\nAll bits flipped: %d\nSwitched all bits: %d\n", num, temp1, temp2, temp3, temp4);
	}
	
	exit(0);
}
