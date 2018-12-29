#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


/**
* @brief							Decrements every element of given array.
*
* @param[in/out]	array			Array to decrement.
* @param[in]		size			Size of array.
*
* @return			void				
*/
void decrementArray_32(int32_t array[], size_t size);


/**
* @brief							Returns minimum value from array.
*
* @param[in]		array			Array to search.
* @param[in]		size			Size of array.
*
* @return			int16_t			Minimum value from array.
*/
int16_t findMinValue_16(int16_t array[], size_t size);


/**
* @brief							Swap two values given as arguments.
*
* @param[in/out]	x				Pointer to first value.
* @param[in/out]	y				Pointer to second value.
*
* @return			void
*/
void swap_32(int32_t * x, int32_t * y);


/**
* @brief							Sorts columns of given array based on chosen row which is used as a key. 
*									Function uses quicksort algorithm.
*
* @param[in/out]	array			Two dimensional array to sort.
* @param[in]		size_x			Number of columns.
* @param[in]		size_y			Number of rows.
* @param[in]		key				Index of row used as the key for sorting algorithm. It is counted from 0.
* @param[in]		p				Parameter needed by recursive callings. Should be set as 0.

* @return			void
*/
void quicksort_2d(int32_t * array[], int32_t size_x, int32_t size_y, int32_t key, int32_t p);


/**
* @brief							Checks correctness of permutation included in array. Range of values in this permutation 
*									is set of natural numbers from 0 to size. Function uses quicksort algorithm.
*									 
* @param[in]		array			Array containing permutation to check.
* @param[in]		size			Size of array.
*
* @return			bool			Returns true value if permutation is correct or false if not.
*/
bool checkPermutationCorrectness(int32_t array[], int32_t size);