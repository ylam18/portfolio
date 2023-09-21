/*
	William Lopez 6252767
	I affirm that I wrote this program myself without any help from any other people or sources from the internet.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int
main(int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int c, err = 0; 
	int dflag, sflag, rflag;
	float *rate, *downpayment;
	float rateVal, downpaymentVal;
	int years;

	static char usage[] = "Usage: mortgagepmt [-s] -r rate [-d downpayment] price\n";
/*
 * Checks for flag s r and d and assigns each flag with 1 if they are included. r is a required parameter and s and d are optional.
 */
	while ((c = getopt(argc, argv, "sr:d:")) != -1)
		switch (c) {
		case 's':
			sflag = 1;
			break;
		case 'r':
			rflag = 1;
			rateVal = atof(optarg);
			rate = &rateVal;
			break;
		case 'd':
                        dflag = 1;
                        downpaymentVal = atof(optarg);
                        downpayment = &downpaymentVal;
                        break;
		case '?':
			err = 1;
			break;
		}
/*
 * check if dflag is 1 to assign value, rflag to print an error because it is required, and sflag to adjust the years accordingly.
 */	
	if (dflag != 1){
		downpaymentVal = 0;
		downpayment = &downpaymentVal;
	}

	if (rflag != 1){
		printf("Error: input an r argument\n");
		exit(0);
	}

	if (sflag == 1){
		years = 15;
	}else{
		years = 30;
	}
//ALL THE MATH TO CALCULATE MORTGAGE PAYMENT
	float price = atof(argv[optind]);
	float mortgagePayment;
	float limit = 0.2 * price;
	float borrow = price - *downpayment;
	float monthlyRate = (*rate / 100) / 12;
	float monthlyRateTwo = monthlyRate + 1;
	float monthlyPayments = years * 12;
	mortgagePayment = (1 - 1/(pow(monthlyRateTwo, monthlyPayments)));
	mortgagePayment = monthlyRate / mortgagePayment;
	mortgagePayment = mortgagePayment * borrow;
	
	if ( *downpayment < limit){
		mortgagePayment = mortgagePayment + ((borrow / 12) * 0.01);
	}
	
	printf("The payment on a loan of $%.2lf with an interest rate of %.3lf%% for a term of %d years will be $%.2lf\n", price, *rate, years, mortgagePayment);

}
