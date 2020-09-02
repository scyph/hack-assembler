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
void assemble(FILE *temp, FILE *bin);

int main(int argc, char *argv[])
{
	FILE *program;
	FILE *temp;
	FILE *bin;
	
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

	temp = fopen("temp.asm", "w+");

	parse(program, temp);
	rewind(temp);
	bin = fopen("out.hack", "w");
	assemble(temp, bin);
	
	fclose(program);
	fclose(temp);
	fclose(bin);

	return 0;
}

void parse(FILE *program, FILE *temp)
{
	int slash = 0;
	int chars = 0;
	/** while we're not at the end of the file*/ 
	while ((c=fgetc(program)) != EOF)
	{
		/** ignore comment */
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

		else if (c == '/')
		{
			slash++;
			continue;
		}

		/** ignore whitespace */
		else if (c == ' ')
		{
			continue;
		}

		/** increment if c is a character.
			  - useful for recognizing and ignoring
			  	inline comments  */
		else if (c > 32 && c < 127)
		{
			chars++;
		}

		/** ignore lonely newlines */
		else if (c == '\n')
		{
			/** if newline is lonely move 
				to next line */
			if (chars == 0)
			{
				continue;
			}
			chars = 0;
		}
		/** write relevant characters into temp file */ 
		fprintf(temp, "%c", c);
	}
}

void assemble(FILE *temp, FILE *bin)
{
	int i = 0;
	char value[10] = {0,0,0,0,0,0,0,0,0,0};
	int actual;
	char *bin_r;
	char vflag = 0;

	while ((c=fgetc(temp)) != EOF)
	{
		if (vflag)
		{
			if (c == '\n')
			{
				switch(i)
				{
					case 1:
						bin_r = to_binary(value[0]);
						break;
					case 2:
						actual = (value[0] * 10) + value[1];
						bin_r = to_binary(actual);
						break;
					case 3:
						actual = (value[0] * 100) + (value[1] * 10) + value[2];
						bin_r = to_binary(actual);
						break;
					default:
						// TODO maybe go to variable path
						printf("Idk wtf happened tbh..\n");
				}
				fputs(bin_r, bin);
				i = 0;
				for (int k = 0; k < 10; k++)
				{
					value[k] = 0;
				}
				free(bin_r);
				fputc('\n', bin);
				vflag = 0;
				continue;
			}
			value[i] = c - '0';

			i++;
		}
		if (c == '@')
		{
			fputc('0', bin);
			vflag = 1;
		}
	}
}