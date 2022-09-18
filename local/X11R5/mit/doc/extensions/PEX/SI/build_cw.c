/* $XConsortium: build_cw.c,v 5.1 91/02/16 09:46:01 rws Exp $ */

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


#include <ctype.h>
#include <stdio.h>
#include "xref.h"



/*  insert_codeword_entry inserts a new codeword entry at its correct place in
    the tree of codeword entries and returns the address of the node
    corresponding to the entry inserted.  */

struct codeword_entry *
insert_codeword_entry(node, entry)
	struct	codeword_entry	*node;
	struct	codeword_entry	*entry;
{

	int	result;
	int	level;

	if ((result = strcmp(node->codeword, entry->codeword)) == 0) {
		fprintf(stderr, "%s: Duplicate codeword %s at line %d in file %s\n",
			command_name, entry->codeword, line_number, current_filename);
			free (entry);
			return(node);
	}
	if (result > 0)		/*  node greater than new entry -- */
		 		/*  move to lesser nodes */
		if (node->lesser != NULL)
			insert_codeword_entry(node->lesser, entry);
		else {
			node->lesser = entry;
			return (node->lesser);
		}
	else			/*  node less than new entry -- */
				/*  move to greater nodes */
		if (node->greater != NULL)
			insert_codeword_entry(node->greater, entry);
		else {
			node->greater = entry;
			return (node->greater);
		}
}


/*  locate_codeword_entry locates a codeword entry in
    the tree of codeword entries and returns the address of the node
    corresponding to the entry located.  */

struct codeword_entry *
locate_codeword_entry(node, codeword)
	struct	codeword_entry	*node;
	char	*codeword;
{

	int	result;

	while (node != NULL) {
		if ((result = strcmp(node->codeword, codeword)) == 0)
			return(node);
		if (result > 0)
			node = node->lesser;
		else
			node = node->greater;
	}
	return(NULL);
}
