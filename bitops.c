/*
	I affirm originality of this program,
	Osman D morales.

	This program prompts a user to enter
	a value in the range of 0-1000, in order
	to set or clear a bit, from a user input
	that is prompted at the beggining of the
	program. Numbers can be between 0 and 31.
	Additionally, the user will be prompted
	if they want to continue or halt the program.

	example of command line parsing via getopt
	usage:  [-p]

	Paul Krzyzanowski
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//define all constants
#define BIT 32
#define OFFSET 31
#define BASE2 2
#define MOD10 10
#define ZERO 0
#define RANGMAX 1000
//int debug = 0;
//getopt
int main(int argc, char **argv)
{

	extern char *optarg;
	extern int optind;
	int c, err = 0;
	int pflag=0;
	char *sname = "default_sname", *fname;
	static char usage[] = "usage: %s [-p] \n";
	//here we declare tha value that will be
	//received by the user.
	unsigned int initialValue = 0;
	unsigned int decVal = 0;
	//Stores the bits as array
	int storeValues[BIT];
	//remainder after modulus operation
	int remainder;
	int base;
	//location of bit. Ex. 0 1 0, where
	// 1, is position 1 and == 2
	int bitPosition;
	int index;
	//stores the value to continue or not
	char prompt;
	int option;
	//mask value
	uint32_t mask = 0x80000000; //left most bit set to 1

	while ((c = getopt(argc, argv, ":p")) != -1)
		switch (c) {
		case 'p':
			pflag = 1;
			//condition to check that user input is withing range
			printf ("\nType a value from 0 - 1000\n");
			scanf("%u", &initialValue);
			int q;
			//checks that bits range is between 0 - 32
			if (initialValue >= ZERO && initialValue <= RANGMAX)
			{
				for (q = ZERO; q < BIT; q++)
					storeValues[q] = 0;

			}
			//sets index starting at 0
			index = ZERO;
			//bitwise operator
			while (mask > ZERO)
			{
				if((initialValue & mask) == ZERO)
					storeValues[index] = 0;
				else
					storeValues[index] = 1;
					mask = mask >> 1;
					index++;
			}

			break;
		case 'l':
			//lflag = 1;
			break;
		case '?':
			err = 1;
			break;}
	//check if flag was set by user,
	//throw usage option if flag not set.
	if (!pflag && (optind+1) > argc)
	{
		printf("optind = %d, argc=%d\n", optind, argc);
		fprintf(stderr, "%s: Missing p flag\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
	}
	//when p flag is set compute mask
	if(pflag)
	{

		printf ("\n**Options**\n");
		printf ("1. Press 0 to clear a bit\n");
		printf ("2. Press 1 to set a bit\n");
		scanf ("%d", &option);
		if (option == ZERO)
		{
			printf ("\n Enter bit to clear: ");
			scanf ("%d", &bitPosition);
			if (bitPosition >= ZERO && bitPosition <= OFFSET)
				storeValues[OFFSET-bitPosition] = 0;

		}else if (option == 1)
		{

			printf ("\n Enter bit to set: ");
			scanf ("%d", &bitPosition);
			if (bitPosition >= ZERO && bitPosition <= OFFSET)
				storeValues[OFFSET-bitPosition] = 1;
		}
		index = OFFSET;
		base = 1;

		while (index >= ZERO)
		{
			remainder = storeValues[index] % MOD10;
			decVal = decVal + remainder * base;
			index--;
			base = base * BASE2;
		}
		//print result
		if (option == ZERO)
			printf("\n Value after clear is %u \n\n", decVal);
		else
			printf("\n Value after set is %u \n\n", decVal);

	}
	//prompt user if continue or not
	printf("Would you like to continue?\n");
	printf("Press y to continue or n to halt\n");
	scanf("%c", &prompt);
	prompt = getchar();
	//repeat program to conduct bitwise operation and mask
	while(prompt == 'y' || prompt == 'Y')
	{
		if(prompt == 'n' || prompt == 'N')
		{	
			return 1;
		}else
		{
			decVal = 0;
			printf ("\nType a value from 0 - 1000\n");
			scanf("%u", &initialValue);
			int q;
			if (initialValue >= ZERO && initialValue <= RANGMAX)
			{
				for (q = ZERO; q < BIT; q++)
					storeValues[q] = ZERO;
			}
			index = ZERO;
			while (mask > ZERO)
			{
				if((initialValue & mask) == ZERO)
					storeValues[index] = ZERO;
				else
					storeValues[index] = 1;
					mask = mask >> 1;
					index++;
			}	

			printf ("\n**Options**\n");
			printf ("1. Press 0 to clear a bit\n");
			printf ("2. Press 1 to set a bit\n");
			scanf ("%d", &option);
			if (option == ZERO)
			{
				printf ("\n Enter bit to clear: ");
				scanf ("%d", &bitPosition);
				if (bitPosition >= ZERO && bitPosition <= OFFSET)
					storeValues[OFFSET-bitPosition] = 1;

			}else if (option)
			{

				printf ("\n Enter bit to set: ");
				scanf ("%d", &bitPosition);
				if (bitPosition >= ZERO && bitPosition <= OFFSET)
					storeValues[OFFSET-bitPosition] = 0;
			}
			index = OFFSET;
			base = 1;

			while (index >= ZERO)
			{
				remainder = storeValues[index] % MOD10;
				decVal = decVal + remainder * base;
				index--;
				base = base * BASE2;
			}
			if (option == ZERO)
			{	printf("\n Value after clear is %u\n\n", decVal);
				decVal = 0;
			}
			else
			{
				printf("\n Value after set is %u\n\n", decVal);
				decVal = 0;
			}
		}
		//print result
		printf ("Would you like to continue\n");
		printf ("Type y to continue or n to halt\n");
		scanf ("%c", &prompt);
		prompt = getchar();
	}
	//print if pflag is set	
	printf("pflag = %d\n", pflag);

	return 0;
}
