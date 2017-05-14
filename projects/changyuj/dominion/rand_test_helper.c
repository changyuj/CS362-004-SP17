/******************************************************
 * Yu Ju Chang
 * rand_test_helper.c
 * Assignment 4
 *
 * a library with some helper functions for random test
 *******************************************************/
 
#include "rand_test_helper.h"
#include <stdio.h>
#include <string.h>
 
 // set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
 
int assertEqual(int value1, int value2)
{
	if(value1 == value2)
	{
#if (NOISY_TEST == 1)
            printf("\n----------------- Test Passed -----------------\n");
#endif
		return 0;
	}
	else
	{
#if (NOISY_TEST == 1)
            printf("\n----------------- Test Failed -----------------\n");
#endif
		return 1;
	}
	return 0;
}

int assertTreasure(int value1, int value2)
{
	if(value1+2 == value2)
	{
#if (NOISY_TEST == 1)
		printf("\n----------------- Test Passed -----------------\n");
#endif
		return 0;
	}
	else
	{
#if (NOISY_TEST == 1)
		printf("\n----------------- Test Failed-----------------\n");
#endif
		return 1;
	}
	
	return 0;
}
