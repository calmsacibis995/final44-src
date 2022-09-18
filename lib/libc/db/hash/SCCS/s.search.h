h19393
s 00002/00002/00023
d D 8.1 93/06/04 15:22:26 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00005/00014
d D 5.2 91/09/04 12:56:47 bostic 2 1
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00019/00000/00000
d D 5.1 91/02/12 20:28:12 bostic 1 0
c date and time created 91/02/12 20:28:12 by bostic
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
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
/* Backward compatibility to hsearch interface */
typedef struct entry { 
	char	*key; 
	char	*data; 
E 2
I 2
/* Backward compatibility to hsearch interface. */
typedef struct entry {
	char *key;
	char *data;
E 2
} ENTRY;

D 2
typedef enum { FIND, ENTER } ACTION;
E 2
I 2
typedef enum {
	FIND, ENTER
} ACTION;

int	 hcreate __P((unsigned int));
void	 hdestroy __P((void));
ENTRY	*hsearch __P((ENTRY, ACTION));
E 2
E 1
