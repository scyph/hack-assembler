#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

/** TODO: 
	    ~ branch out command line args
	        $ ./assembler -help
	        OVERVIEW: hack assembler

	        USAGE: ./assembler file [options]...

	        OPTIONS:
	        	-o <file>  Write output to <file>
	        	...
*/

char c;

void parse(FILE *program, FILE *temp);
void assemble();

int main(int argc, char *argv[])
{
	FILE *program;
	FILE *hackfile;
	
	switch(argc)
	{
		/** if given file arg, open file */
		case 2:
			program = fopen(argv[1], "r");
			break;
		default:
			printf("\nUSAGE: ./assembler FILE\n\n");
			return 1;
	}

	if (program == NULL)
	{
		printf("\nerror: %s could not be read/found..\n\n", argv[1]);
		return 2;
	}
	hackfile = fopen("out.hack", "w");
	parse(program, hackfile);
	
	//assemble(temp, hackfile);
	
	fclose(program);

	fclose(hackfile);

	return 0;
}

void parse(FILE *program, FILE *hackfile)
{
	/** comment recognition */
	int slash = 0;
	/** character recognition */
	int chars = 0;

	/** position in value/instruction array */
	int position = 0;

	/** array of values after @ */
	char value_arr[5] = {'!', '!', '!', '!', '!'};

	/** binary representation of given value */
	char *bin_representation;

	/** A Instruction */
	char a_instruction = 0;

	/** C Instruction */
	char c_instruction = 0;

	/**  */
	char instruction_arr[10] = {'!', '!', '!', '!', '!',  '!', '!', '!', '!', '!'}; 

	while ((c = fgetc(program)) != EOF)
	{
		if (a_instruction)
			goto A_INSTRUCTION;

		if (c_instruction)
			goto C_INSTRUCTION;

		/** ignore comments */
		if (slash == 2)
		{
			/** (inline comment)if end of current 
				line reset slash and chars then
				move on to next line */
			if (c == '\n' && chars > 0)
			{
				slash = 0;
				chars = 0;
				continue;
			}
			/** if end of current line reset slash 
			    then move on to next line */
			else if (c == '\n')
			{
				slash = 0;
				continue;
			}
			/** else ignore current character */
			continue;
		}
		if (c == '/')
		{
			slash++;
			continue;
		}

		/** ignore whitespace */
		if (c == ' ')
		{
			continue;
		}

		/** increment if c is a character.
			  - useful for recognizing and ignoring
			  	inline comments  */
		if (c > 32 && c < 127)
		{
			chars++;
		}

		/** ignore lonely newlines */
		if (c == '\n')
		{
			/** if newline is lonely move 
				to next line */
			if (chars == 0)
			{
				continue;
			}
			chars = 0;
		}
		if (c == '@')
		{
			fputc('0', hackfile);
			a_instruction = 1;
			continue;
		}
		else
		{
			fputs("111", hackfile);
			c_instruction = 1;
			continue;
		}
		continue;

		A_INSTRUCTION:
			if (c == '\n' || c == ' ')
			{
				/** convert value array into actual value */
				int value = to_num(value_arr);

				/** convert value into its binary equivalent */
				bin_representation = to_binary(value);

				/** put binary number into hack file and a newline*/
				fputs(bin_representation, hackfile);
				fputc('\n', hackfile);

				/**reinitialize value array for next value*/
				for (int k = 0; k < 5; k++)
				{
					value_arr[k] = '!';
				}
				
				/**reset position variable and A Instruction flag*/
				position = 0;
				a_instruction = 0;

				continue;
			}
			/** populate value array */
			value_arr[position] = c;
			position++;

		C_INSTRUCTION:
			if (c == '\n' || c == ' ')
			{
				/** parse instruction */
			}
			instruction_arr[position] = c;
			position++;

	}
}

