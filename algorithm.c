#include "stdafx.h"
#include "algorithm.h"


/**
* @brief							Initializes single cycle structure.
*
* @param[out]	cycle				Pointer to Cycle_t element.
*
* @return		void				
*/
void initCycle(Cycle_t * cycle);


/**
* @brief							Adds single node to simple cycle.
*
* @param[in/out]	cycle			Pointer to Cycle_t element.
* @param[in]		node_number		Number of node to add.
* @param[in]		node_mass		Mass of node.
*
* @return			void
*/
void addNodeToCycle(Cycle_t * cycle, int32_t node_number, int16_t node_mass);


/**
* @brief							Calculates output value for single cycle.
*
* @param[in]		cycle			Pointer to Cycle_t element.
* @param[in]		min				Minimum mass in the entire graph.
*
* @return			int64_t			Partitive result for input cycle.
*/
int64_t calculateCycle(Cycle_t * cycle, int16_t min);



void findPermutationArray(int32_t p[], int32_t input_setting[], int32_t output_setting[], int32_t size)
{
	int32_t   node_number;
	int32_t   p_index, tmp_index;

	int32_t * index_table = calloc(size, sizeof(int32_t));
	int32_t * input_place = calloc(size, sizeof(int32_t));
	int32_t * output_place = calloc(size, sizeof(int32_t));

	int32_t ** ptr_matrix = calloc(3, sizeof(int32_t*));

	for (int32_t i = 0; i < size; i++)
	{
		node_number = input_setting[i];
		input_place[node_number] = i;

		node_number = output_setting[i];
		output_place[node_number] = i;

		index_table[i] = i;
	}

	ptr_matrix[0] = index_table;
	ptr_matrix[1] = input_place;
	ptr_matrix[2] = output_place;
	quicksort_2d(ptr_matrix, size, 3, 1, 0);

	for (int32_t i = 0; i < size; i++)
	{
		p_index = index_table[i];
		tmp_index = output_place[i];
		p[p_index] = index_table[tmp_index];
	}

	free(ptr_matrix);
	free(index_table);
	free(input_place);
	free(output_place);
}


void initCycle(Cycle_t * cycle)
{
	cycle->NumOfNodes = 0;
	cycle->Min = INT16_MAX;
	cycle->Sum = 0;
}


void addNodeToCycle(Cycle_t * cycle, int32_t node_number, int16_t node_mass)
{
	if (cycle->Min > node_mass)
		cycle->Min = node_mass;

	cycle->Sum = cycle->Sum + node_mass;
	cycle->NumOfNodes++;
}


int64_t calculateCycle(Cycle_t * cycle, int16_t min)
{
	int64_t method_1 = 0;
	int64_t method_2 = 0;

	method_1 = cycle->Sum + ((cycle->NumOfNodes - 2) * (cycle->Min));

	method_2 = cycle->Sum + cycle->Min + ((cycle->NumOfNodes + 1) * min);

	return ((method_1 < method_2) ? method_1 : method_2);
}


int64_t calculateResult(int32_t p[], int16_t mass[],  int32_t size)
{
	Cycle_t cycle;
	int16_t min;
	int64_t result = 0;
	bool * odw = calloc(size, sizeof(bool));

	min = findMinValue_16(mass, size);

	for (int32_t k = 0; k < size; k++)
		odw[k] = false;

	for (int32_t i = 0; i < size; i++)
	{
		if (odw[i] == false)
		{
			initCycle(&cycle);
			
			int32_t x = i;

			while (odw[x] == false)
			{
				odw[x] = true;
				addNodeToCycle(&cycle, x, mass[x]);
				x = p[x];
			}

			result += calculateCycle(&cycle, min);
		}
	}

	free(odw);

	return result;
}