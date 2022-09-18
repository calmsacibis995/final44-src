h25576
s 00003/00001/00063
d D 1.3 83/05/05 20:29:08 slatteng 3 2
c fixed lookup routine for "displays" to ignore terminal types.
e
s 00002/00003/00062
d D 1.2 83/04/18 14:43:19 slatteng 2 1
c DLS takeover
e
s 00065/00000/00000
d D 1.1 83/04/18 13:45:25 slatteng 1 0
c date and time created 83/04/18 13:45:25 by slatteng
e
u
U
t
T
I 1
D 2

/* findaed.c -
E 2
I 2
/* %W%	%G%
E 2
 *
 * Copyright -C- 1982 Barry S. Roitblat
 *
 * This file contains a single routine which will find the correct
 * AED display to use from the current terminal.  
 *
 * (Modified from software written by John Ousterhout for the caesar
 *  program)
 */

#include "gremlin.h"

/* Imports from library routines: */

extern FILE *fopen();
extern char *ttyname();

/* imports from config.c */

extern char GDisplays[];
D 2

E 2
I 2

E 2
char *
FindAED()

/*---------------------------------------------------------
 *	This routine reads out the name of the terminal associated
 *	with the standard input, then selects an AED display to be
 *	used, based on that terminal name.
 *
 *	Results:
 *	The return value is a pointer to a string that is the device
 *	name of the AED display to use.  This name is found by searching
 *	in the file "displays" in the current search path.  The file
 *	consists of pairs of strings.  If the first string of a pair
 *	matches the name of our input terminal, then the second string
 *	of the pair is used as the AED device name.  If no match occurs
 *	then /dev/null is used.
 *
 *	Side Effects:	None.
 *---------------------------------------------------------
 */

{
D 3
    char name1[100], name2[100], *tty;
E 3
I 3
    char name1[100], *tty;
    static char name2[100];
E 3
    FILE *f;
    tty = ttyname(fileno(stderr));
    if (tty == NULL) return NULL;
    f = fopen(GDisplays, "r");
    if (f == NULL) return NULL;
    while (TRUE)
    {
	if (fscanf(f, "%99s %99s", name1, name2) < 2)
	{
	    (void) fclose(f);
	    return NULL;
	}
	if (strcmp(name1, tty) == 0)
	{
	    (void) fclose(f);
	    return name2;
	}
I 3
	while (getc (f) > 10);		/* ignore extra characters on a line */
E 3
    }
}
E 1
