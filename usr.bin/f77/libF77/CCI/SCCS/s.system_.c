h57695
s 00012/00002/00018
d D 5.2 91/04/12 15:16:06 bostic 2 1
c new copyright; att/bsd/shared
e
s 00020/00000/00000
d D 5.1 86/11/03 20:00:12 mckusick 1 0
c from CCI
e
u
U
t
T
I 1
D 2
/*
 *	%W% (Berkeley) %G%
E 2
I 2
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.proprietary.c%
E 2
 */
I 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

/* f77 interface to system routine */

system_(s, n)
register char *s;
long int n;
{
char buff[1001];
register char *bp, *blast;

blast = buff + (n<1000 ? n : 1000L);

for(bp = buff ; bp<blast && *s!='\0' ; )
	*bp++ = *s++;
*bp = '\0';
system(buff);
}
E 1
