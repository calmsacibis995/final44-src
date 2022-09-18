h23538
s 00008/00005/00041
d D 5.2 91/04/12 15:32:55 bostic 6 5
c new copyright; att/bsd/shared
e
s 00007/00001/00039
d D 5.1 85/06/07 23:15:36 kre 5 4
c Add copyright
e
s 00002/00002/00038
d D 1.4 81/08/11 19:42:58 dlw 4 3
c added test for return val of nowwriting(). DLW
e
s 00009/00005/00031
d D 1.3 81/06/15 21:59:14 dlw 3 2
c added 'nowwriting(lu)'. DLW
e
s 00001/00001/00035
d D 1.2 81/02/20 12:52:43 dlw 2 1
c fixed errno for bad unit to be F_ERUNIT. DLW
e
s 00036/00000/00000
d D 1.1 81/02/11 22:33:53 dlw 1 0
c date and time created 81/02/11 22:33:53 by dlw
e
u
U
t
T
I 1
D 6
/*
D 5
char id_fputc[] = %W%";
E 5
I 5
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
E 5
 *
I 5
D 6
 *	%W%	%G%
E 6
I 6
 * %sccs.include.proprietary.c%
E 6
 */
I 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

/*
E 5
 * write a character to a logical unit bypassing formatted I/O
 *
 * calling sequence:
 *	integer fputc
 *	ierror = fputc (unit, char)
 * where:
 *	char will be sent to the logical unit
 *	ierror will be 0 if successful; a system error code otherwise.
 */

#include	"../libI77/fiodefs.h"
#include	"../libI77/f_errno.h"

extern unit units[];	/* logical units table from iolib */

long fputc_(u, c, clen)
long *u; char *c; long clen;
{
D 3
	int i;
E 3
I 3
	int	i;
	unit	*lu;
E 3

	if (*u < 0 || *u >= MXUNIT)
D 2
		return((long)(errno=F_ERARG));
E 2
I 2
		return((long)(errno=F_ERUNIT));
E 2
D 3
	if (!units[*u].ufd)
E 3
I 3
	lu = &units[*u];
	if (!lu->ufd)
E 3
		return((long)(errno=F_ERNOPEN));
D 3
	putc (*c, units[*u].ufd);
	if (ferror(units[*u].ufd))
E 3
I 3
D 4
	if (!lu->uwrt)
		nowwriting(lu);
E 4
I 4
	if (!lu->uwrt && ! nowwriting(lu))
		return((long)errno);
E 4
	putc (*c, lu->ufd);
	if (ferror(lu->ufd))
E 3
	{
		i = errno;
D 3
		clearerr(units[*u].ufd);
E 3
I 3
		clearerr(lu->ufd);
E 3
		return((long)i);
	}
	return(0L);
}
E 1
