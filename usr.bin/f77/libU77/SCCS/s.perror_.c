h23388
s 00008/00005/00047
d D 5.3 91/04/12 15:33:17 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00050
d D 5.2 90/05/28 12:36:20 bostic 4 3
c sys_errlist -> strerror(3)
e
s 00007/00001/00045
d D 5.1 85/06/07 23:26:54 kre 3 2
c Add copyright
e
s 00008/00004/00038
d D 1.2 81/06/15 21:58:42 dlw 2 1
c added 'nowwriting(lu)'. DLW
e
s 00042/00000/00000
d D 1.1 81/02/18 21:57:32 dlw 1 0
c date and time created 81/02/18 21:57:32 by dlw
e
u
U
t
T
I 1
D 5
/*
D 3
char id_perror[] = "%W%";
E 3
I 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
E 3
 *
I 3
D 5
 *	%W%	%G%
E 5
I 5
 * %sccs.include.proprietary.c%
E 5
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

/*
E 3
 * write a standard error message to the standard error output
 *
 * calling sequence:
 *	call perror(string)
 * where:
 *	string will be written preceeding the standard error message
 */

#include	<stdio.h>
#include	"../libI77/fiodefs.h"
#include	"../libI77/f_errno.h"

D 4
extern char *sys_errlist[];
E 4
extern int sys_nerr;
extern char *f_errlist[];
extern int f_nerr;
extern unit units[];

perror_(s, len)
char *s; long len;
{
D 2
	char buf[40];
	char *mesg = s + len;
E 2
I 2
	unit	*lu;
	char	buf[40];
	char	*mesg = s + len;
I 4
	char	*strerror();
E 4
E 2

	while (len > 0 && *--mesg == ' ')
		len--;
	if (errno >=0 && errno < sys_nerr)
D 4
		mesg = sys_errlist[errno];
E 4
I 4
		mesg = strerror(errno);
E 4
	else if (errno >= F_ER && errno < (F_ER + f_nerr))
		mesg = f_errlist[errno - F_ER];
	else
	{
		sprintf(buf, "%d: unknown error number", errno);
		mesg = buf;
	}
I 2
	lu = &units[STDERR];
	if (!lu->uwrt)
		nowwriting(lu);
E 2
	while (len-- > 0)
D 2
		putc(*s++, units[STDERR].ufd);
	fprintf(units[STDERR].ufd, ": %s\n", mesg);
E 2
I 2
		putc(*s++, lu->ufd);
	fprintf(lu->ufd, ": %s\n", mesg);
E 2
}
E 1
