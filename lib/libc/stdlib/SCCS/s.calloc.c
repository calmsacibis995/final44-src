h14194
s 00002/00002/00024
d D 8.1 93/06/04 13:05:40 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00007/00026
d D 5.7 93/01/12 10:25:36 bostic 9 8
c move cfree into libcompat
e
s 00002/00002/00031
d D 5.6 91/02/23 22:56:35 donn 8 7
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00001/00000/00032
d D 5.5 90/05/17 14:26:22 bostic 7 6
c correctly declare cfree
e
s 00016/00026/00016
d D 5.4 90/05/16 11:39:38 bostic 6 5
c new version, using size_t's
e
s 00030/00015/00012
d D 5.3 88/09/22 19:33:28 bostic 5 4
c from scratch; add Berkeley header
e
s 00002/00002/00025
d D 5.2 86/03/09 19:44:43 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00024
d D 5.1 85/06/05 12:08:27 mckusick 3 2
c Add copyright
e
s 00013/00020/00012
d D 4.2 85/01/21 22:41:38 serge 2 1
c use bzero
e
s 00032/00000/00000
d D 4.1 80/12/21 16:39:29 wnj 1 0
c date and time created 80/12/21 16:39:29 by wnj
e
u
U
t
T
I 5
D 6
/*
 * Copyright (c) 1988 The Regents of the University of California.
E 6
I 6
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
E 6
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

E 5
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4
E 3
D 2
/*	calloc - allocate and clear memory block
*/
#define CHARPERINT (sizeof(int)/sizeof(char))
#define NULL 0
E 2

I 2
D 5
/*
 * Calloc - allocate and clear memory block
 */
E 5
I 5
D 6
#include <sys/types.h>
E 6
I 6
#include <stdlib.h>
I 8
#include <string.h>
E 8
E 6

E 5
E 2
D 6
char *
D 5
calloc(num, size)
D 2
unsigned num, size;
E 2
I 2
	register unsigned num, size;
E 5
I 5
calloc(nelem, elsize)
	u_int nelem, elsize;
E 6
I 6
void *
calloc(num, size)
	size_t num;
	register size_t size;
E 6
E 5
E 2
{
D 2
	register char *mp;
	char *malloc();
	register int *q;
	register m;
E 2
I 2
D 5
	extern char *malloc();
	register char *p;
E 5
I 5
D 6
	char *p, *malloc();
E 6
I 6
	register void *p;
E 6
E 5
E 2

D 2
	num *= size;
	mp = malloc(num);
	if(mp == NULL)
		return(NULL);
	q = (int *) mp;
	m = (num+CHARPERINT-1)/CHARPERINT;
	while(--m>=0)
		*q++ = 0;
	return(mp);
E 2
I 2
D 5
	size *= num;
	if (p = malloc(size))
		bzero(p, size);
	return (p);
E 5
I 5
D 6
	elsize *= nelem;
	if (p = malloc(elsize))
		bzero(p, elsize);
E 6
I 6
	size *= num;
	if (p = malloc(size))
		bzero(p, size);
E 6
	return(p);
E 5
E 2
}
D 9

I 7
void
E 7
D 5
cfree(p, num, size)
E 5
I 5
D 6
/* ARGSUSED */
cfree(p, nelem, elsize)
E 5
D 2
char *p;
unsigned num, size;
E 2
I 2
	char *p;
D 5
	unsigned num;
	unsigned size;
E 5
I 5
	u_int nelem, elsize;
E 6
I 6
D 8
cfree(p, num, size)
E 8
I 8
cfree(p)
E 8
	void *p;
D 8
	size_t num, size;
E 8
E 6
E 5
E 2
{
D 6
	free(p);
E 6
I 6
	(void)free(p);
E 6
}
E 9
E 1
