#include "stdafx.h"
#include "lib.h"


/**
* @brief							Partition function for quicksort algorithm.
*
* @param[in/out]	array			Two dimensional array to sort.
* @param[in]		size_x			Number of columns.
* @param[in]		size_y			Number of rows.
* @param[in]		key				Index of row used as the key for sorting algorithm. It is counted from 0.
* @param[in]		p				Index for partitioning given array.
*
* @return			int32_t			Number of columns for next call of quicksort_2d function.
*/
int32_t partition(int32_t * array[], int32_t size_x, int32_t size_y, int32_t key, int32_t p);



void decrementArray_32(int32_t array[], size_t size)
{
	for (size_t i = 0; i < size; i++)
		array[i]--;
}


int16_t findMinValue_16(int16_t array[], size_t size)
{
	int16_t min = INT16_MAX;

	for (size_t i = 0; i < size; i++)
	{
		if (min > array[i])
			min = array[i];
	}

	return min;
}


void swap_32(int32_t * x, int32_t * y)
{
	int32_t temp = *x;
	*x = *y;
	*y = temp;
}


int32_t partition(int32_t * array[], int32_t size_x, int32_t size_y, int32_t key, int32_t p)
{
	int32_t x = array[key][p];
	int32_t i = p;
	int32_t j = size_x;

	while (1)
	{
		while (array[key][j] > x)
			j--;
		while (array[key][i] < x)
			i++;
		if (i < j)
		{
			for (int32_t r = 0; r < size_y; r++)
				swap_32(&array[r][i], &array[r][j]);

			i++;
			j--;
		}
		else
			return j;
	}
}


void quicksort_2d(int32_t * array[], int32_t size_x, int32_t size_y, int32_t key, int32_t p)
{
	static int32_t call_num = 0;
	int32_t q;

	if (call_num == 0)
		size_x--;

	call_num++;

	if (p < size_x)
	{
		q = partition(array, size_x, size_y, key, p);

		quicksort_2d(array, q, size_y, key, p);
		quicksort_2d(array, size_x, size_y, key, q + 1);
	}

	call_num--;
}


bool checkPermutationCorrectness(int32_t array[], int32_t size)
{
	bool is_correct = true;
	int32_t * temp_array = calloc(size, sizeof(int32_t));

	for (int32_t i = 0; i < size; i++)
		temp_array[i] = array[i];

	quicksort_2d(&temp_array, size, 1, 0, 0);

	for (int32_t i = 0; i < size; i++)
	{
		if (temp_array[i] != i)
		{
			is_correct = false;
			break;
		}
	}

	free(temp_array);

	return is_correct;
}
