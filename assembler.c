#include <stdio.h>


/** TODO: 
		~ command line arg
			$ ./assembler mult.asm -o mult
		
		*/

void strip(FILE *program, FILE *temp, char c);

int main()
{
	FILE *program;
	FILE *temp;
	char c;

	program = fopen("mult.asm", "r");
	temp   = fopen("temp.asm", "w");

	if (program == NULL)
	{
		printf("error..");
		return 1;
	}

	strip(program, temp, c);

	fclose(program);
	fclose(temp);

	return 0;
}

void strip(FILE *program, FILE *temp, char c)
{
	int slash = 0;
	int chars = 0;
	while (1)
	{
		c = fgetc(program);

		/** strip comments */
		if (slash == 2)
		{
			/** (inline comment)if end of current 
				line reset slash and chars then
				move on to next line */
			if (c == '\n' && chars > 0)
			{
				slash = 0;
				chars = 0;
				fprintf(temp, "\n");
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

		/** strip whitespace */
		if (c == ' ')
		{
			continue;
		}

		/** inc if c is a character.
			  - useful for recognizing and ignoring
			  	inline comments  */
		if (c > 32 && c < 127)
		{
			chars++;
		}

		/** strip lonely newlines */
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

		/** if end of file exit out of loop */
		if (feof(program))
		{
			break;
		}
		/** write relevant characters into temp file */ 
		fprintf(temp, "%c", c);
	}
}

