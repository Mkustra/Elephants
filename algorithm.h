#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lib.h"


/**
* @brief Structure for parameters of single cycle.
*/
typedef struct{
	int32_t NumOfNodes;		//< Total number of nodes
	int16_t Min;			//< Minimum mass
	int64_t Sum;			//< Summary mass of all nodes
}Cycle_t;


/**
* @brief							Calculates p array.
*
* @param[out]	p					p array from algorithm.
* @param[in]	input_setting		Array with input permutation.
* @param[in]	output_setting		Array with output permutation.
* @param[in]	size				Number of nodes in graph.
*
* @return		void				
*/
void findPermutationArray(int32_t p[], int32_t input_setting[], int32_t output_setting[], int32_t size);


/**
* @brief							Calculates minimum effort to get output permutation.
*
* @param[in]	p					p array from algorithm.
* @param[in]	mass				Array of masses for every node.
* @param[in]	size				Number of nodes in graph.
*
* @return		int64_t				Output value of algorithm.
*/
int64_t calculateResult(int32_t p[], int16_t mass[], int32_t size);