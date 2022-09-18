h45750
s 00002/00002/00039
d D 8.1 93/06/04 13:08:12 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00036
d D 5.11 91/02/24 13:30:15 bostic 13 12
c Add include files to get prototype declarations, and fix bugs found.
e
s 00004/00003/00035
d D 5.10 90/11/28 00:13:16 bostic 12 11
c make error messages a little better, use constants in unistd.h
e
s 00001/00011/00037
d D 5.9 90/06/01 14:12:55 bostic 11 10
c new copyright notice
e
s 00005/00023/00043
d D 5.8 89/04/09 17:45:36 bostic 10 9
c separate strerror() and make perror() call it.
e
s 00012/00004/00054
d D 5.7 88/12/16 18:04:30 bostic 9 8
c on unknown error, at least print out the errno
e
s 00011/00003/00046
d D 5.6 88/11/16 12:58:08 bostic 8 7
c add strerror function; ANSI 4.11.6.2
e
s 00002/00001/00047
d D 5.5 88/10/30 13:44:33 bostic 7 6
c check for errno < 0
e
s 00016/00009/00032
d D 5.4 88/08/02 18:07:15 bostic 6 5
c rewritten to use writev by Sam; add Berkeley specific header
e
s 00002/00002/00039
d D 5.3 87/09/30 10:04:44 bostic 5 4
c sys_nerr and sys_errlist are externs
e
s 00002/00002/00039
d D 5.2 86/03/09 19:52:09 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00031
d D 5.1 85/05/30 10:47:20 dist 3 2
c Add copyright
e
s 00018/00012/00014
d D 4.2 83/06/30 14:46:40 sam 2 1
c use writev to avoid small net writes
e
s 00026/00000/00000
d D 4.1 80/12/21 16:39:58 wnj 1 0
c date and time created 80/12/21 16:39:58 by wnj
e
u
U
t
T
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
/*
D 6
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 14
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 6
 */

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
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 4

E 3
D 6
/*
 * Print the error indicated
 * in the cerror cell.
 */
E 6
I 2
#include <sys/types.h>
I 12
D 13
#include <sys/errno.h>
E 13
E 12
#include <sys/uio.h>
I 12
#include <unistd.h>
I 13
#include <errno.h>
#include <stdio.h>
E 13
#include <string.h>
E 12
E 2

I 13
void
E 13
D 8
int	errno;
D 5
int	sys_nerr;
char	*sys_errlist[];
E 5
I 5
extern int	sys_nerr;
extern char	*sys_errlist[];
E 8
I 8
D 10
int errno;
extern int sys_nerr;
extern char *sys_errlist[];

I 9
static char ebuf[20];

E 10
E 9
E 8
E 5
perror(s)
D 2
char *s;
E 2
I 2
D 13
	char *s;
E 13
I 13
	const char *s;
E 13
E 2
{
I 10
D 12
	extern int errno;
E 12
	register struct iovec *v;
E 10
D 2
	register char *c;
	register n;
E 2
I 2
	struct iovec iov[4];
D 10
	register struct iovec *v = iov;
E 10
I 10
D 12
	char *strerror();
E 12
E 10
E 2

I 10
	v = iov;
E 10
D 2
	c = "Unknown error";
	if(errno < sys_nerr)
		c = sys_errlist[errno];
	n = strlen(s);
	if(n) {
		write(2, s, n);
		write(2, ": ", 2);
E 2
I 2
	if (s && *s) {
D 13
		v->iov_base = s;
E 13
I 13
		v->iov_base = (char *)s;
E 13
		v->iov_len = strlen(s);
		v++;
		v->iov_base = ": ";
		v->iov_len = 2;
		v++;
E 2
	}
D 2
	write(2, c, strlen(c));
	write(2, "\n", 1);
E 2
I 2
D 7
	v->iov_base = errno < sys_nerr ? sys_errlist[errno] : "Unknown error";
E 7
I 7
D 9
	v->iov_base = (u_int)errno < sys_nerr ?
	    sys_errlist[errno] : "Unknown error";
E 9
I 9
D 10
	if ((u_int)errno < sys_nerr)
		v->iov_base = sys_errlist[errno];
	else {
		(void)sprintf(ebuf, "Unknown error: %d", errno);
		v->iov_base = ebuf;
	}
E 10
I 10
	v->iov_base = strerror(errno);
E 10
E 9
E 7
	v->iov_len = strlen(v->iov_base);
	v++;
	v->iov_base = "\n";
	v->iov_len = 1;
D 6
	writev(2, iov, (v - iov) + 1);
E 6
I 6
D 12
	(void)writev(2, iov, (v - iov) + 1);
E 12
I 12
	(void)writev(STDERR_FILENO, iov, (v - iov) + 1);
E 12
I 8
D 10
}

char *
strerror(errnum)
	int errnum;
{
D 9
	return((u_int)errnum < sys_nerr ?
	    sys_errlist[errnum] : "Unknown error");
E 9
I 9
	if ((u_int)errnum < sys_nerr)
		return(sys_errlist[errnum]);
	(void)sprintf(ebuf, "Unknown error: %d", errnum);
	return(ebuf);
E 10
E 9
E 8
E 6
E 2
}
E 1
