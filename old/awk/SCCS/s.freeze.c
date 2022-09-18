h16282
s 00009/00002/00034
d D 4.3 91/04/17 16:54:59 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00001/00033
d D 4.2 83/08/11 20:09:35 sam 2 1
c standardize keyword lines
e
s 00034/00000/00000
d D 4.1 82/05/07 19:24:09 mckusick 1 0
c date and time created 82/05/07 19:24:09 by mckusick
e
u
U
t
T
I 3
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
D 3
static char sccsid[] = "%W% %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3
E 2

#include "stdio.h"
freeze(s) char *s;
{	int fd;
	unsigned int *len;
	len = (unsigned int *)sbrk(0);
	if((fd = creat(s, 0666)) < 0) {
		perror(s);
		return(1);
	}
	write(fd, &len, sizeof(len));
	write(fd, (char *)0, len);
	close(fd);
	return(0);
}

thaw(s) char *s;
{	int fd;
	unsigned int *len;
	if(*s == 0) {
		fprintf(stderr, "empty restore file\n");
		return(1);
	}
	if((fd = open(s, 0)) < 0) {
		perror(s);
		return(1);
	}
	read(fd, &len, sizeof(len));
	(void) brk(len);
	read(fd, (char *)0, len);
	close(fd);
	return(0);
}
E 1
