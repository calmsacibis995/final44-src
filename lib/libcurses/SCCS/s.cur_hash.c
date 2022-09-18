h15846
s 00002/00002/00034
d D 8.1 93/06/04 16:48:10 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00004/00026
d D 5.2 92/09/21 15:24:29 elan 2 1
c Changed insterface to take length of string.
e
s 00030/00000/00000
d D 5.1 92/09/14 11:01:16 elan 1 0
c date and time created 92/09/14 11:01:16 by elan
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif	/* not lint */

I 2
#include <sys/types.h>


E 2
/*
 * __hash() is "hashpjw" from the Dragon Book, Aho, Sethi & Ullman, p.436.
 */
u_int
D 2
__hash(s)
E 2
I 2
__hash(s, len)
E 2
	char *s;
I 2
	int len;
E 2
{
D 2
        register u_int	h, g;
E 2
I 2
        register u_int	h, g, i;
E 2

	h = 0;
D 2
        while (*s) {
                h = (h << 4) + *s++;
E 2
I 2
	i = 0;
        while (i < len) {
                h = (h << 4) + s[i];
E 2
                if (g = h & 0xf0000000) {
                        h = h ^ (g >> 24);
                        h = h ^ g;
                }
I 2
		i++;
E 2
	}
        return h;
}
E 1
