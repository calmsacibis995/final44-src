h38963
s 00001/00001/00061
d D 8.2 95/05/04 07:21:42 bostic 9 8
c litn
e
s 00002/00002/00060
d D 8.1 93/06/04 13:06:45 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00061
d D 5.4 91/02/05 00:26:37 torek 7 6
c repair arguments (add const)
e
s 00054/00027/00008
d D 5.3 91/01/20 21:23:14 bostic 6 5
c new stdio
e
s 00002/00002/00033
d D 5.2 86/03/09 20:51:51 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00031
d D 5.1 85/06/05 13:36:39 mckusick 4 3
c Add copyright
e
s 00002/00002/00030
d D 4.3 85/02/13 15:48:49 serge 3 2
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00002/00002/00030
d D 4.2 81/03/09 20:59:24 toy 2 1
c Feldman's stdio changes
e
s 00032/00000/00000
d D 4.1 80/12/21 16:50:28 wnj 1 0
c date and time created 80/12/21 16:50:28 by wnj
e
u
U
t
T
I 6
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 6
I 1
D 4
/* %W% (Berkeley) %G% */
E 4
I 4
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

I 6
#include <stdio.h>
#include <errno.h>
#include "local.h"

E 6
E 4
/*
D 6
 * Return file offset.
 * Coordinates with buffering.
E 6
I 6
 * ftell: return current offset.
E 6
 */
D 6

#include	<stdio.h>
long	lseek();


long ftell(iop)
D 3
FILE *iop;
E 3
I 3
register FILE *iop;
E 6
I 6
long
ftell(fp)
D 7
	register FILE *fp;
E 7
I 7
D 9
	register const FILE *fp;
E 9
I 9
	register FILE *fp;
E 9
E 7
E 6
E 3
{
D 3
	long tres;
E 3
I 3
D 6
	register long tres;
E 3
	register adjust;
E 6
I 6
	register fpos_t pos;
E 6

D 6
	if (iop->_cnt < 0)
		iop->_cnt = 0;
	if (iop->_flag&_IOREAD)
		adjust = - iop->_cnt;
D 2
	else if (iop->_flag&_IOWRT) {
E 2
I 2
	else if (iop->_flag&(_IOWRT|_IORW)) {
E 2
		adjust = 0;
D 2
		if (iop->_base && (iop->_flag&_IONBF)==0)
E 2
I 2
		if (iop->_flag&_IOWRT && iop->_base && (iop->_flag&_IONBF)==0)
E 2
			adjust = iop->_ptr - iop->_base;
	} else
		return(-1);
	tres = lseek(fileno(iop), 0L, 1);
	if (tres<0)
		return(tres);
	tres += adjust;
	return(tres);
E 6
I 6
	if (fp->_seek == NULL) {
		errno = ESPIPE;			/* historic practice */
		return (-1L);
	}

	/*
	 * Find offset of underlying I/O object, then
	 * adjust for buffered bytes.
	 */
	if (fp->_flags & __SOFF)
		pos = fp->_offset;
	else {
		pos = (*fp->_seek)(fp->_cookie, (fpos_t)0, SEEK_CUR);
		if (pos == -1L)
			return (pos);
	}
	if (fp->_flags & __SRD) {
		/*
		 * Reading.  Any unread characters (including
		 * those from ungetc) cause the position to be
		 * smaller than that in the underlying object.
		 */
		pos -= fp->_r;
		if (HASUB(fp))
			pos -= fp->_ur;
	} else if (fp->_flags & __SWR && fp->_p != NULL) {
		/*
		 * Writing.  Any buffered characters cause the
		 * position to be greater than that in the
		 * underlying object.
		 */
		pos += fp->_p - fp->_bf._base;
	}
	return (pos);
E 6
}
E 1
