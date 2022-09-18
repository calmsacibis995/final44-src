h30745
s 00002/00002/00022
d D 8.1 93/06/04 13:09:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00020/00008
d D 5.3 91/01/20 21:29:56 bostic 6 5
c new stdio
e
s 00002/00002/00026
d D 5.2 86/03/09 20:53:40 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00018
d D 5.1 85/05/30 14:30:02 dist 4 3
c Add copyright
e
s 00001/00001/00018
d D 4.3 85/02/13 15:49:11 serge 3 2
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00005/00002/00014
d D 4.2 82/10/05 22:44:09 mckusick 2 1
c utilize st_blksize field to optimize size of reads and writes
e
s 00016/00000/00000
d D 4.1 80/12/21 16:50:56 wnj 1 0
c date and time created 80/12/21 16:50:56 by wnj
e
u
U
t
T
I 1
D 4
/* %W% (Berkeley) %G% */
E 4
I 4
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 6
 */

D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5

E 4
D 6
#include	<stdio.h>
E 6
I 6
#include <stdio.h>
#include "local.h"
E 6

D 6
setbuf(iop, buf)
D 3
register struct _iobuf *iop;
E 3
I 3
register FILE *iop;
E 3
char *buf;
E 6
I 6
void
setbuf(fp, buf)
	FILE *fp;
	char *buf;
E 6
{
D 6
	if (iop->_base != NULL && iop->_flag&_IOMYBUF)
		free(iop->_base);
	iop->_flag &= ~(_IOMYBUF|_IONBF|_IOLBF);
D 2
	if ((iop->_base = buf) == NULL)
E 2
I 2
	if ((iop->_base = buf) == NULL) {
E 2
		iop->_flag |= _IONBF;
D 2
	else
E 2
I 2
		iop->_bufsiz = NULL;
	} else {
E 2
		iop->_ptr = iop->_base;
I 2
		iop->_bufsiz = BUFSIZ;
	}
E 2
	iop->_cnt = 0;
E 6
I 6
	(void) setvbuf(fp, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
E 6
}
E 1
