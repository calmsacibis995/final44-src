h59156
s 00006/00002/00040
d D 4.2 91/04/18 16:44:14 bostic 2 1
c new copyright; att/bsd/shared
e
s 00042/00000/00000
d D 4.1 83/05/06 23:30:18 tut 1 0
c date and time created 83/05/06 23:30:18 by tut
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include "refer..c"

static char ahead[1024];
static int peeked = 0;
static char *noteof = (char *) 1;

char *
input(s)
char *s;
{
	if (peeked) {
		peeked = 0;
		if (noteof == 0)
			return(0);
		strcpy(s, ahead);
		return(s);
	}
	return(fgets(s, 1000, in));
}

char *
lookat()
{
	if (peeked)
		return(ahead);
	noteof = input(ahead);
	peeked = 1;
	return(noteof);
}

addch(s, c)
char *s;
{
	while (*s)
		s++;
	*s++ = c;
	*s = 0;
}
E 1
