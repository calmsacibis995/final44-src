/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
char*
rindex(s, c)
register char	*s;
register int	c;
{
	register char *r;

	r = (char*)0;
	do if (*s == c) r = s; while (*s++);
	return(r);
}
