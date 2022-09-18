h22728
s 00010/00010/00069
d D 8.2 95/05/30 20:13:21 dab 3 2
c Code cleanup, use mem*() instead of b*()
e
s 00002/00002/00077
d D 8.1 93/06/04 17:35:40 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00079/00000/00000
d D 5.1 91/02/28 22:01:29 dab 1 0
c date and time created 91/02/28 22:01:29 by dab
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */


#include <ctype.h>

#define	LOWER(x) (isupper(x) ? tolower(x) : (x))
/*
 * The prefix function returns 0 if *s1 is not a prefix
 * of *s2.  If *s1 exactly matches *s2, the negative of
 * the length is returned.  If *s1 is a prefix of *s2,
 * the length of *s1 is returned.
 */
	int
isprefix(s1, s2)
	register char *s1, *s2;
{
D 3
        register int n = 0;
        char *os1;
E 3
I 3
	register int n = 0;
	char *os1;
E 3
	register char c1, c2;

D 3
        if (*s1 == '\0')
                return(-1);
        os1 = s1;
E 3
I 3
	if (*s1 == '\0')
		return(-1);
	os1 = s1;
E 3
	c1 = *s1;
	c2 = *s2;
D 3
        while (LOWER(c1) == LOWER(c2)) {
E 3
I 3
	while (LOWER(c1) == LOWER(c2)) {
E 3
		if (c1 == '\0')
			break;
D 3
                c1 = *++s1;
                c2 = *++s2;
        }
        return(*s1 ? 0 : (*s2 ? (s1 - os1) : (os1 - s1)));
E 3
I 3
		c1 = *++s1;
		c2 = *++s2;
	}
	return(*s1 ? 0 : (*s2 ? (s1 - os1) : (os1 - s1)));
E 3
}

static char *ambiguous;		/* special return value for command routines */

	char **
genget(name, table, stlen)
	char	*name;		/* name to match */
	char	**table;	/* name entry in table */
	int	stlen;
{
	register char **c, **found;
	register int n;

	if (name == 0)
	    return 0;

	found = 0;
	for (c = table; *c != 0; c = (char **)((char *)c + stlen)) {
		if ((n = isprefix(name, *c)) == 0)
			continue;
		if (n < 0)		/* exact match */
			return(c);
		if (found)
			return(&ambiguous);
		found = c;
	}
	return(found);
}

/*
 * Function call version of Ambiguous()
 */
	int
Ambiguous(s)
	char *s;
{
	return((char **)s == &ambiguous);
}
E 1
