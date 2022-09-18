h16302
s 00002/00002/00044
d D 8.1 93/06/06 22:22:07 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00046
d D 5.1 91/04/18 18:41:29 bostic 2 1
c yank to 5.1, new copyright; att/bsd/shared
e
s 00046/00000/00000
d D 1.1 90/05/23 16:44:39 marc 1 0
c date and time created 90/05/23 16:44:39 by marc
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

foldit(chunk, col, max)
	char *chunk;
{
	register char *cp;

	/*
	 * Keep track of column position. Insert hidden newline
	 * if this chunk puts us over the limit.
	 */
again:
	cp = chunk;
	while (*cp) {
		switch(*cp) {
		case '\n':
		case '\r':
			col = 0;
			break;
		case '\t':
			col = col + 8 &~ 07;
			break;
		case '\b':
			col = col ? col - 1 : 0;
			break;
		default:
			col++;
		}
		if (col > (max - 2)) {
			printf("\\\n");
			col = 0;
			goto again;
		} 
		cp++;
	}
	return (col);
}
E 1
