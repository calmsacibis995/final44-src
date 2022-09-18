#include <stdio.h>
#include <strings.h>
#include "format.h"

#define DELIM		'/'
#define INDENT_SIZE	4

int
Format(char *curr_line, char *output[])
{
	int	indent = 0, i = 0, n = 0;
	char	*bpt, *la, *head, *c;

	bpt = curr_line;
	la = curr_line;
	head = curr_line;

	while (1) {
		if (la - head >= MAXLINE - indent) {
			head = bpt;
			i++;
			indent += INDENT_SIZE;
			for (n = 0; n < INDENT_SIZE; n++)
				output[i][n] = ' ';
		} 
		if (*la == NULL) {
			sprintf(&output[i][n],"%s", bpt);
			break;
		} else if (*la == DELIM) {
			for (c = bpt; c <= la; c++)
				output[i][n++] = *c;
			output[i][n] = '\0';
			la++;
			bpt = la;
		} else
			la++;
	}
	return i + 1;
}
		
