#include "stdafx.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define NUM_OF_ELEPHANTS_MIN		2
#define NUM_OF_ELEPHANTS_MAX		1000000
#define MASS_MIN					100
#define MASS_MAX					6500
#define SETTING_NUM_MIN				1
#define SETTING_NUM_MAX				Num_Of_Nodes


extern int32_t   Num_Of_Nodes;
extern int16_t * Mass;
extern int32_t * Input_Setting;
extern int32_t * Output_Setting;


/**
* @brief Type contains exit code for parseInputData function.
*/
typedef enum 
{ 
	  PARSER_SUCCESS                        = 0
	, PARSER_INCORRECT_NUM_OF_NODES			// 1
	, PARSER_INCORRECT_MASS					// 2
	, PARSER_INCORRECT_INPUT_SETTING		// 3
	, PARSER_INCORRECT_OUTPUT_SETTING		// 4
	, PARSER_INCORRECT_ENDING_OF_FILE		// 5
} Parser_Error_Code_T;


/**
* @brief Set of possible states of parseInputData function.
*/
typedef enum
{
	  PARSER_NUM_OF_NODES_STATE      = 0
	, PARSER_MASS_STATE				// 1
	, PARSER_INPUT_SETTING_STATE	// 2
	, PARSER_OUTPUT_SETTING_STATE	// 3
	, PARSER_DONE					// 4
} Parser_State_T;


/**
* @brief								Reads input data from standard input and initialize data.
*
* @param[out]	parser_error_index		If there is an error of uncorrect value of mass, input or output setting, returns index of this value.
*
* @return		Parser_Error_Code_T		Error code or success.
*/
Parser_Error_Code_T parseInputData(int32_t * err_index);