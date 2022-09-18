/* $XConsortium: print_refs.c,v 5.1 91/02/16 09:45:51 rws Exp $ */

/***********************************************************
Copyright (c) 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/


#include <stdio.h>
#include <ctype.h>
#include "xref.h"


print_reference(node, reference_type)
	struct codeword_entry	*node;
	int	reference_type;
{
	char	out_string[MAXLINE];
	char	rest_string[MAXLINE];


	if (reference_type == TITLE) {
		printf("%s", node->title);
		return;
	}
			/*  Handle first level conversion specially */
	if (node->appendix)
		number_to_letters(node->h1_counter, out_string);
	else
		sprintf(out_string, "%d", node->h1_counter);

	strcpy(rest_string, "");
	if (node->entry_type == HEADING) {
		if (node->h5_counter != 0)
			sprintf(rest_string, ".%d.%d.%d.%d", node->h2_counter,
			node->h3_counter, node->h4_counter, node->h5_counter);
		else if (node->h4_counter != 0)
			sprintf(rest_string, ".%d.%d.%d", node->h2_counter,
			node->h3_counter, node->h4_counter);
		else if (node->h3_counter != 0)
			sprintf(rest_string, ".%d.%d", node->h2_counter,
			node->h3_counter);
		else if (node->h2_counter != 0)
			sprintf(rest_string, ".%d", node->h2_counter);
		strcat(out_string, rest_string);
		
	}
	else if (node->entry_type == TABLE) {
		if (document_type == MAJOR_SECTIONED) {
			sprintf(rest_string, "-%d", node->table_number);
			strcat(out_string, rest_string);
		}
		else
			sprintf(out_string, "%d", node->table_number);
	}
	else if (node->entry_type == FIGURE) {
		if (document_type == MAJOR_SECTIONED) {
			sprintf(rest_string, "-%d", node->figure_number);
			strcat(out_string, rest_string);
		}
		else
			sprintf(out_string, "%d", node->figure_number);
	}
	printf("%s", out_string);
}

number_to_letters(decimal, letters) /* convert number to string of letters */
	int  decimal;
	char  letters [];
{
	static  char  alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int  index = 0;

	letters [0] = '\0';
	if (decimal > 18278) {	/*  26**3 + 26**2 + 26  */
		strcpy(letters, "???");
		return;
	}
	if (decimal > 702) {	/*  26**2  + 26  */
		letters[index++] = alphabet[(decimal - 26 - 1) / 676 - 1];
		decimal = (decimal - 26 - 1) % 676 + 26 + 1;
	}
	if (decimal > 26) {
		letters[index++] = alphabet[(decimal - 1) / 26 - 1];
		decimal = (decimal - 1) % 26 + 1;
	}
	letters[index++] = alphabet[decimal - 1];
	letters[index++] = '\0';
	return;
}
