#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_DIGITS 5
#define MAX_INSTR  10

char* to_binary (int num)
{
	int bit[16];
	char *bin = malloc(16 * sizeof(char));
	int place = 15;

	for (int i = 0; i < 16; i++)
	{
		bit[i] = (int)pow((double)2, (double)place);
		place--;
	}
	
	for (int i = 0; i < 16; i++)
	{
		if (num == 1 && bit[i] == 1)
		{
			 bin[i] = '1';
			 break;
		}
		else if (bit[i] <= num)
		{
			num %= bit[i];
			bin[i] = '1';
		}
		else
		{
			bin[i] = '0';
		}
	}
	return bin;
}

int to_num (char value[])
{
	int d_place[5] = {1, 10, 100, 1000, 10000};
	int size = 0;
	int result = 0;
	int temp;

	for (int i = 0; i < MAX_DIGITS; i++)
	{
		if (value[i] != '!')
		{
			++size;
		}
	}
	temp = size;
	for (int j = 0; j < size; j++)
	{
		result += (value[j] - '0') * d_place[temp-1];
		temp--;
	}
	
	return result;

}

char* parse_instruction (char instruction[], int position)
{
	char jump = dest = comp = a = 0;
	char *bin_instruction = malloc(13 * sizeof(char));

	for (int i = 0; i < position; i++)
	{
		if (instruction[i] == 'M')
		{
			a = 1;
			bin_instruction[0] = '1';
		}
		else if (instruction[i] == '=')
		{
			dest = 1;
		} 
		else if (instruction[i] == ';')
		{
			jump = 1;
		}
	}
	if (dest == 0)
	{
		for (int k = 7; k <= 9; k++)
		{
			bin_instruction[k] == 
		}
	}
	if (jump == 0)
	{

	}
	return bin_instruction;
}