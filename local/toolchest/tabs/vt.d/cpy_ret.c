/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
char   *
cpy_ret (cp, cp1)
register char  *cp;
register char  *cp1;
{
	while (*cp++ = *cp1++);
	return (cp - 1);
}
