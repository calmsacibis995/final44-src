h22022
s 00002/00002/00044
d D 8.1 93/06/04 13:07:16 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00045
d D 5.6 91/09/03 12:02:41 bostic 11 10
c fread/fwrite return size_t
e
s 00000/00001/00045
d D 5.5 91/02/24 13:30:12 bostic 10 9
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00002/00044
d D 5.4 91/02/05 00:26:38 torek 9 8
c repair arguments (add const)
e
s 00037/00040/00009
d D 5.3 91/01/20 21:23:27 bostic 8 7
c new stdio
e
s 00002/00002/00047
d D 5.2 86/03/09 20:52:02 donn 7 6
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00039
d D 5.1 85/05/30 14:29:29 dist 6 5
c Add copyright
e
s 00001/00001/00039
d D 4.5 85/05/14 21:16:21 sam 5 4
c beware of divide by 0
e
s 00002/00001/00038
d D 4.4 85/01/23 16:58:33 ralph 4 3
c get return value right.
e
s 00009/00002/00030
d D 4.3 84/11/29 11:02:59 ralph 3 2
c don't call flsbuf for every char if line buffering.
e
s 00001/00001/00031
d D 4.2 84/08/03 16:48:18 ralph 2 1
c don't sign extend character otherwise flsbuf can return EOF falsely
e
s 00032/00000/00000
d D 4.1 84/05/29 13:51:09 karels 1 0
c date and time created 84/05/29 13:51:09 by karels
e
u
U
t
T
I 1
D 6
/* %W% (Berkeley) %G% */
E 6
I 6
D 8
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 8
 */

D 7
#ifndef lint
E 7
I 7
#if defined(LIBC_SCCS) && !defined(lint)
E 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
D 8
#endif LIBC_SCCS and not lint
E 8
I 8
#endif /* LIBC_SCCS and not lint */
E 8
E 7

E 6
D 8
#include	<stdio.h>
E 8
I 8
#include <stdio.h>
D 10
#include <string.h>
E 10
#include "local.h"
#include "fvwrite.h"
E 8

D 8
fwrite(ptr, size, count, iop)
	register char *ptr;
	unsigned size, count;
	register FILE *iop;
E 8
I 8
/*
 * Write `count' objects (each size `size') from memory to the given file.
 * Return the number of whole objects written.
 */
I 11
size_t
E 11
fwrite(buf, size, count, fp)
D 9
	void *buf;
E 9
I 9
	const void *buf;
E 9
	size_t size, count;
	FILE *fp;
E 8
{
D 8
	register int s;
E 8
I 8
	size_t n;
	struct __suio uio;
	struct __siov iov;
E 8

D 8
	s = size * count;
D 3
	while (s > 0) {
E 3
I 3
	if (iop->_flag & _IOLBF)
D 4
		while (--s >= 0) {
E 4
I 4
		while (s > 0) {
E 4
			if (--iop->_cnt > -iop->_bufsiz && *ptr != '\n')
				*iop->_ptr++ = *ptr++;
			else if (_flsbuf(*(unsigned char *)ptr++, iop) == EOF)
				break;
I 4
			s--;
E 4
		}
	else while (s > 0) {
E 3
		if (iop->_cnt < s) {
			if (iop->_cnt > 0) {
				bcopy(ptr, iop->_ptr, iop->_cnt);
				ptr += iop->_cnt;
				iop->_ptr += iop->_cnt;
				s -= iop->_cnt;
			}
D 2
			if (_flsbuf((unsigned)*ptr++, iop) == EOF)
E 2
I 2
D 3
			if (_flsbuf((unsigned)*ptr++ & 0377, iop) == EOF)
E 3
I 3
			if (_flsbuf(*(unsigned char *)ptr++, iop) == EOF)
E 3
E 2
				break;
			s--;
		}
		if (iop->_cnt >= s) {
			bcopy(ptr, iop->_ptr, s);
			iop->_ptr += s;
			iop->_cnt -= s;
			return (count);
		}
	}
D 5
	return (count - ((s + size - 1) / size));
E 5
I 5
	return (size != 0 ? count - ((s + size - 1) / size) : 0);
E 8
I 8
D 9
	iov.iov_base = buf;
E 9
I 9
	iov.iov_base = (void *)buf;
E 9
	uio.uio_resid = iov.iov_len = n = count * size;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;

	/*
	 * The usual case is success (__sfvwrite returns 0);
	 * skip the divide if this happens, since divides are
	 * generally slow and since this occurs whenever size==0.
	 */
	if (__sfvwrite(fp, &uio) == 0)
		return (count);
	return ((n - uio.uio_resid) / size);
E 8
E 5
}
E 1
