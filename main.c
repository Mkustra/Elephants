#include "stdafx.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "lib.h"
#include "parser.h"
#include "algorithm.h"


int32_t   Num_Of_Nodes;	
int16_t * Mass;
int32_t * Input_Setting;
int32_t * Output_Setting;



int main()
{
	int32_t parser_error_index;
	int32_t * p;
	int64_t result;

	
	/* Reading input data */
	if (parseInputData(&parser_error_index) != PARSER_SUCCESS)
	{
		return 1;
	}
	

	/* Decrementing all numbers of nodes so they can be used as indexes for arrays */
	decrementArray_32(Input_Setting, Num_Of_Nodes);
	decrementArray_32(Output_Setting, Num_Of_Nodes);


	/* Checking correctness of input and output permutations */
	if (checkPermutationCorrectness(Input_Setting, Num_Of_Nodes) == false)
	{
		return 2;
	}
	if (checkPermutationCorrectness(Output_Setting, Num_Of_Nodes) == false)
	{
		return 3;
	}
	

	/* Allocating memory for p array */
	p = calloc(Num_Of_Nodes, sizeof(int32_t));

	
	/* Executing algorithm */
	findPermutationArray(p, Input_Setting, Output_Setting, Num_Of_Nodes);
	result = calculateResult(p, Mass, Num_Of_Nodes);
	

	/* Printing result */
	printf("%lld", result);


	/* Free allocated memory */
	free(p);
	free(Mass);
	free(Input_Setting);
	free(Output_Setting);


	return 0;
}