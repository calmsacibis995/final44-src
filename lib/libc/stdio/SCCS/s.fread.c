h20647
s 00006/00001/00049
d D 8.2 93/12/11 19:11:03 torek 11 10
c insert ANSI-mandated bogosity
e
s 00002/00002/00048
d D 8.1 93/06/04 13:06:14 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00048
d D 5.6 93/03/04 15:36:33 torek 9 8
c bcopy => memcpy (safe in all these cases) for ANSI (sigh)
e
s 00001/00000/00049
d D 5.5 91/09/03 12:02:39 bostic 8 7
c fread/fwrite return size_t
e
s 00002/00002/00047
d D 5.4 91/05/04 16:40:48 bostic 7 6
c the C library should only use bcopy, so programs don't load both!
e
s 00038/00035/00011
d D 5.3 91/01/20 21:21:34 bostic 6 5
c new stdio
e
s 00002/00002/00044
d D 5.2 86/03/09 20:51:12 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00036
d D 5.1 85/05/30 14:28:48 dist 4 3
c Add copyright
e
s 00001/00001/00036
d D 4.3 85/05/14 21:16:18 sam 3 2
c beware of divide by 0
e
s 00003/00001/00034
d D 4.2 84/09/05 14:17:37 ralph 2 1
c don't save EOF in buffer, don't sign-extend 0xff to match EOF.
e
s 00035/00000/00000
d D 4.1 84/05/29 13:51:03 karels 1 0
c date and time created 84/05/29 13:51:03 by karels
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
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
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
#include <string.h>
E 6

I 8
size_t
E 8
D 6
fread(ptr, size, count, iop)
	register char *ptr;
	unsigned size, count;
	register FILE *iop;
E 6
I 6
fread(buf, size, count, fp)
	void *buf;
	size_t size, count;
	register FILE *fp;
E 6
{
D 6
	register int s;
I 2
	int c;
E 6
I 6
	register size_t resid;
	register char *p;
	register int r;
	size_t total;
E 6
E 2

I 11
	/*
	 * The ANSI standard requires a return value of 0 for a count
	 * or a size of 0.  Peculiarily, it imposes no such requirements
	 * on fwrite; it only requires fread to be broken.
	 */
E 11
D 6
	s = size * count;
	while (s > 0) {
		if (iop->_cnt < s) {
			if (iop->_cnt > 0) {
				bcopy(iop->_ptr, ptr, iop->_cnt);
				ptr += iop->_cnt;
				s -= iop->_cnt;
			}
			/*
			 * filbuf clobbers _cnt & _ptr,
			 * so don't waste time setting them.
			 */
D 2
			if ((*ptr++ = _filbuf(iop)) == EOF)
E 2
I 2
			if ((c = _filbuf(iop)) == EOF)
E 2
				break;
I 2
			*ptr++ = c;
E 2
			s--;
E 6
I 6
	if ((resid = count * size) == 0)
D 11
		return (count);
E 11
I 11
		return (0);
E 11
	if (fp->_r < 0)
		fp->_r = 0;
	total = resid;
	p = buf;
	while (resid > (r = fp->_r)) {
D 7
		(void) memcpy((void *)p, (void *)fp->_p, (size_t)r);
E 7
I 7
D 9
		(void) bcopy((void *)fp->_p, (void *)p, (size_t)r);
E 9
I 9
		(void)memcpy((void *)p, (void *)fp->_p, (size_t)r);
E 9
E 7
		fp->_p += r;
		/* fp->_r = 0 ... done in __srefill */
		p += r;
		resid -= r;
		if (__srefill(fp)) {
			/* no more input: return partial result */
			return ((total - resid) / size);
E 6
		}
D 6
		if (iop->_cnt >= s) {
			bcopy(iop->_ptr, ptr, s);
			iop->_ptr += s;
			iop->_cnt -= s;
			return (count);
		}
E 6
	}
D 3
	return (count - ((s + size - 1) / size));
E 3
I 3
D 6
	return (size != 0 ? count - ((s + size - 1) / size) : 0);
E 6
I 6
D 7
	(void) memcpy((void *)p, (void *)fp->_p, resid);
E 7
I 7
D 9
	(void) bcopy((void *)fp->_p, (void *)p, resid);
E 9
I 9
	(void)memcpy((void *)p, (void *)fp->_p, resid);
E 9
E 7
	fp->_r -= resid;
	fp->_p += resid;
	return (count);
E 6
E 3
}
E 1
