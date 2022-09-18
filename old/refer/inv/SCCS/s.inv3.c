h42633
s 00006/00002/00022
d D 4.2 91/04/18 16:39:59 bostic 2 1
c new copyright; att/bsd/shared
e
s 00024/00000/00000
d D 4.1 83/05/06 23:47:30 tut 1 0
c date and time created 83/05/06 23:47:30 by tut
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

getargs(s, arps)
char *s, *arps[];
{
	int i = 0;

	while (1)
	{
		arps[i++] = s;
		while (*s != 0 && *s!=' '&& *s != '\t')
			s++;
		if (*s == 0)
			break;
		*s++ = 0;
		while (*s==' ' || *s=='\t')
			s++;
		if (*s==0)
			break;
	}
	return(i);
}
E 1
