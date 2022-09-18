h53941
s 00005/00005/00089
d D 8.1 93/05/31 16:45:42 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00093
d D 5.3 90/06/01 13:03:52 bostic 3 2
c new copyright notice
e
s 00000/00004/00104
d D 5.2 88/10/19 20:05:17 bostic 2 1
c don't bother logging anything
e
s 00108/00000/00000
d D 5.1 88/10/19 19:55:09 bostic 1 0
c date and time created 88/10/19 19:55:09 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Guy Harris.
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * cno - Read a question, cast a change, and output the line values to the
 * standard output for processing by "phx".
 */
#include <stdio.h>
#include "ching.h"

long	now;		/* current time */

unsigned seed;		/* seed for random number generator */
unsigned getrand();

char	*change();
char	string[6+1];	/* where the actual change string is put */

int	table[2][2][2] = {
	{ { OYIN,  YYANG,}, { YYANG, YYIN,} },
	{ { YYANG, YYIN,},  { YYIN,  OYANG,} },
};

main()
{
	FILE *logf;

	time(&now);
	seed = (int)now + getquest() + getgid() + getuid() + getpid();	/* randomize */
	printf("%s\n", change());
D 2
	if ((logf = fopen("log", "a")) != (FILE *)NULL) {
		fprintf(logf, "%s\t%s", string, ctime(&now));
		fclose(logf);
	}
E 2
}

/*
 * Hash the question by adding all the characters together.
 */
int
getquest()
{
	int result;
	register int c;

	result = 0;
	while ((c = getchar()) != EOF)
		result += c;
	return(result);
}

/*
 * Get a set of six lines making up a change.
 */
char *
change()
{
	register int i;

	for (i = 0; i < 6; i++)
		string[i] = table[getrnum()&01][getrnum()&01][getrnum()&01] + '0';
	string[i] = '\0';
	return(string);
}

/*
 * Get a number more random than what getrand() gives.
 */
getrnum()
{
	return((getrand())>>(getrand()%17));
}

/*
 * Get a random number.
 */
unsigned
getrand()
{
	return(seed = (seed*13077) + 6925);
}
E 1
