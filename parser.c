#include "stdafx.h"
#include "parser.h"



Parser_Error_Code_T parseInputData(int32_t * err_index)
{
	Parser_State_T parser_state = PARSER_NUM_OF_NODES_STATE;
	int     c;
	int     err = 0;
	int32_t temp;
	uint8_t buf[9];
	uint8_t buf_cnt = 0;
	bool    read_num_flag = false;
	
	*err_index = 0;

	while (1)
	{
		c = getchar();

		if (c >= '0' && c <= '9' && parser_state < PARSER_DONE)
		{
			read_num_flag = true;
			buf[buf_cnt++] = c;
			buf[buf_cnt] = 0;

			if (buf_cnt > 7)
			{
				err = 1;
				read_num_flag = false;
			}
			else
				continue;
		}
		else if (c != ' ' && c!= '\t' && c != '\n' && c != '\r' && c != EOF)
		{
			read_num_flag = false;
			err = 1;
		}


		if (read_num_flag == true)
		{
			if (parser_state == PARSER_NUM_OF_NODES_STATE && (*err_index >= 1) ||
				parser_state == PARSER_MASS_STATE && (*err_index >= Num_Of_Nodes) ||
				parser_state == PARSER_INPUT_SETTING_STATE && (*err_index >= Num_Of_Nodes) ||
				parser_state == PARSER_OUTPUT_SETTING_STATE && (*err_index >= Num_Of_Nodes))
			{
				err = 1;
				read_num_flag = false;
			}
		}


		if (read_num_flag == true)
		{
			switch (parser_state)
			{
				case PARSER_NUM_OF_NODES_STATE:

					Num_Of_Nodes = atoi(buf);

					if (Num_Of_Nodes >= NUM_OF_ELEPHANTS_MIN && Num_Of_Nodes <= NUM_OF_ELEPHANTS_MAX)
					{
						Mass = calloc(Num_Of_Nodes, sizeof(int16_t));
						Input_Setting = calloc(Num_Of_Nodes, sizeof(int32_t));
						Output_Setting = calloc(Num_Of_Nodes, sizeof(int32_t));
					}
					else
						err = 1;
				break;

				case PARSER_MASS_STATE:
					temp = atoi(buf);

					if (temp >= MASS_MIN && temp <= MASS_MAX)
						Mass[*err_index] = (int16_t)temp;
					else
						err = 1;
				break;

				case PARSER_INPUT_SETTING_STATE:
					Input_Setting[*err_index] = atoi(buf);

					if (Input_Setting[*err_index] < SETTING_NUM_MIN || Input_Setting[*err_index] > SETTING_NUM_MAX)
						err = 1;
				break;

				case PARSER_OUTPUT_SETTING_STATE:
					Output_Setting[*err_index] = atoi(buf);

					if (Output_Setting[*err_index] < SETTING_NUM_MIN || Output_Setting[*err_index] > SETTING_NUM_MAX)
						err = 1;
				break;

				default:
				break;
			}

			if (err == 0)
			{
				(*err_index)++;
				buf_cnt = 0;
				read_num_flag = false;
			}
		}


		if (c == '\n' && err == 0)
		{ 
			if ((parser_state == PARSER_NUM_OF_NODES_STATE   && *err_index == 1)                ||
				(parser_state == PARSER_MASS_STATE           && (*err_index == Num_Of_Nodes))   ||
				(parser_state == PARSER_INPUT_SETTING_STATE  && (*err_index == Num_Of_Nodes))   ||
				(parser_state == PARSER_OUTPUT_SETTING_STATE && (*err_index == Num_Of_Nodes))    )
			{
				parser_state++;
				*err_index = 0;
			}
			else if(parser_state != PARSER_DONE)
				err = 1;
		}
		else if (c == EOF && err == 0)
		{
			if ((parser_state == PARSER_OUTPUT_SETTING_STATE) && (*err_index == Num_Of_Nodes) || (parser_state == PARSER_DONE))
				return PARSER_SUCCESS;
			else
				err = 1;
		}


		if (err)
		{
			if (parser_state == PARSER_NUM_OF_NODES_STATE)
				return PARSER_INCORRECT_NUM_OF_NODES;
			else if (parser_state == PARSER_MASS_STATE)
				return PARSER_INCORRECT_MASS;
			else if (parser_state == PARSER_INPUT_SETTING_STATE)
				return PARSER_INCORRECT_INPUT_SETTING;
			else if (parser_state == PARSER_OUTPUT_SETTING_STATE)
				return PARSER_INCORRECT_OUTPUT_SETTING;
			else if (parser_state == PARSER_DONE)
				return PARSER_INCORRECT_ENDING_OF_FILE;
		}
	}
}