h46049
s 00009/00004/00180
d D 8.4 95/02/14 10:31:52 cgd 22 21
c new argument passing conventions.  minor type size cleanup.
e
s 00005/00000/00179
d D 8.3 94/01/21 17:17:49 bostic 21 20
c add USL's copyright notice
e
s 00006/00003/00173
d D 8.2 93/12/30 16:22:19 mckusick 20 19
c new queue structure
e
s 00002/00002/00174
d D 8.1 93/06/10 21:57:57 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00174
d D 7.12 93/01/25 18:24:31 mckusick 18 17
c rationalize behavior of ureadc in the face of unreasonable data
e
s 00004/00004/00172
d D 7.11 92/10/11 10:38:11 bostic 17 16
c make kernel includes standard
e
s 00023/00000/00153
d D 7.10 92/07/19 23:45:42 mckusick 16 15
c add hashinit to size and allocate hash tables
e
s 00000/00028/00153
d D 7.9 92/06/20 16:13:15 bostic 15 14
c break out library functions
e
s 00008/00009/00173
d D 7.8 92/02/14 17:20:10 torek 14 13
c lint; uwritec is defined only for the vax
e
s 00006/00000/00176
d D 7.7 91/04/15 23:43:56 mckusick 13 12
c add DIAGNOSTIC to verify presence of uip_procp pointer in uiomove
e
s 00000/00001/00176
d D 7.6 91/04/12 16:04:41 karels 12 11
c delete user.h
e
s 00011/00010/00166
d D 7.5 91/03/17 15:41:35 karels 11 10
c more-or-less working with new proc & user structs
e
s 00001/00001/00175
d D 7.4 90/09/05 18:20:58 karels 10 9
c need uwritec for datakit too
e
s 00030/00002/00146
d D 7.3 90/04/05 15:01:18 marc 9 8
c strcat, strcpy, strncpy
e
s 00007/00006/00141
d D 7.2 89/05/09 17:02:31 mckusick 8 7
c merge in vnodes
e
s 00001/00001/00146
d D 7.1 86/06/05 00:04:38 mckusick 7 6
c 4.3BSD release version
e
s 00005/00004/00142
d D 6.5 86/04/21 12:13:35 karels 6 5
c fixes to uwritec from dlw; include it for ct driver
e
s 00007/00001/00139
d D 6.4 85/06/08 14:38:09 mckusick 5 4
c Add copyright
e
s 00005/00005/00135
d D 6.3 84/08/29 20:20:24 bloom 4 3
c Change to includes.  no more ../h
e
s 00009/00009/00131
d D 6.2 84/07/08 22:32:28 mckusick 3 2
c use proper definition of UIO flags
e
s 00000/00000/00140
d D 6.1 83/07/29 06:34:18 sam 2 1
c 4.2 distribution
e
s 00140/00000/00000
d D 4.1 83/05/27 14:02:47 sam 1 0
c date and time created 83/05/27 14:02:47 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 7
 * Copyright (c) 1982 Regents of the University of California.
E 7
I 7
D 11
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 19
 * Copyright (c) 1982, 1986, 1991 Regents of the University of California.
D 14
 * All rights reserved. 
E 14
I 14
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 21
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 21
E 19
E 14
E 11
 *
I 11
 * %sccs.include.redist.c%
 *
E 11
 *	%W% (Berkeley) %G%
 */
E 5

D 4
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/uio.h"
E 4
I 4
D 17
#include "param.h"
#include "systm.h"
I 13
#include "proc.h"
I 16
#include "malloc.h"
E 17
I 17
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/malloc.h>
I 20
#include <sys/queue.h>
E 20
E 17
E 16
E 13
D 8
#include "dir.h"
E 8
D 12
#include "user.h"
E 12
D 8
#include "uio.h"
E 8
E 4

I 22
int
E 22
D 8
uiomove(cp, n, rw, uio)
E 8
I 8
uiomove(cp, n, uio)
E 8
	register caddr_t cp;
	register int n;
D 8
	enum uio_rw rw;
E 8
	register struct uio *uio;
{
	register struct iovec *iov;
	u_int cnt;
	int error = 0;

I 13
D 14

E 14
#ifdef DIAGNOSTIC
E 13
I 8
	if (uio->uio_rw != UIO_READ && uio->uio_rw != UIO_WRITE)
		panic("uiomove: mode");
I 13
	if (uio->uio_segflg == UIO_USERSPACE && uio->uio_procp != curproc)
		panic("uiomove proc");
#endif
E 13
E 8
	while (n > 0 && uio->uio_resid) {
		iov = uio->uio_iov;
		cnt = iov->iov_len;
		if (cnt == 0) {
			uio->uio_iov++;
			uio->uio_iovcnt--;
			continue;
		}
		if (cnt > n)
			cnt = n;
		switch (uio->uio_segflg) {

D 3
		case 0:
		case 2:
E 3
I 3
		case UIO_USERSPACE:
		case UIO_USERISPACE:
E 3
D 8
			if (rw == UIO_READ)
E 8
I 8
			if (uio->uio_rw == UIO_READ)
E 8
				error = copyout(cp, iov->iov_base, cnt);
			else
				error = copyin(iov->iov_base, cp, cnt);
			if (error)
				return (error);
			break;

D 3
		case 1:
E 3
I 3
		case UIO_SYSSPACE:
E 3
D 8
			if (rw == UIO_READ)
E 8
I 8
			if (uio->uio_rw == UIO_READ)
E 8
				bcopy((caddr_t)cp, iov->iov_base, cnt);
			else
				bcopy(iov->iov_base, (caddr_t)cp, cnt);
			break;
		}
		iov->iov_base += cnt;
		iov->iov_len -= cnt;
		uio->uio_resid -= cnt;
		uio->uio_offset += cnt;
		cp += cnt;
		n -= cnt;
	}
	return (error);
}

/*
 * Give next character to user as result of read.
 */
I 22
int
E 22
ureadc(c, uio)
	register int c;
	register struct uio *uio;
{
	register struct iovec *iov;

I 22
	if (uio->uio_resid <= 0)
		panic("ureadc: non-positive resid");
E 22
again:
D 18
	if (uio->uio_iovcnt == 0)
E 18
I 18
D 22
	if (uio->uio_iovcnt == 0 || uio->uio_resid == 0)
E 18
		panic("ureadc");
E 22
I 22
	if (uio->uio_iovcnt <= 0)
		panic("ureadc: non-positive iovcnt");
E 22
	iov = uio->uio_iov;
D 18
	if (iov->iov_len <= 0 || uio->uio_resid <= 0) {
E 18
I 18
D 22
	if (iov->iov_len == 0) {
E 22
I 22
	if (iov->iov_len <= 0) {
E 22
E 18
		uio->uio_iovcnt--;
		uio->uio_iov++;
		goto again;
	}
	switch (uio->uio_segflg) {

D 3
	case 0:
E 3
I 3
	case UIO_USERSPACE:
E 3
		if (subyte(iov->iov_base, c) < 0)
			return (EFAULT);
		break;

D 3
	case 1:
E 3
I 3
	case UIO_SYSSPACE:
E 3
		*iov->iov_base = c;
		break;

D 3
	case 2:
E 3
I 3
	case UIO_USERISPACE:
E 3
		if (suibyte(iov->iov_base, c) < 0)
			return (EFAULT);
		break;
	}
	iov->iov_base++;
	iov->iov_len--;
	uio->uio_resid--;
	uio->uio_offset++;
	return (0);
}

I 8
D 9
#ifdef unused
E 9
I 9
D 15
strcat(src, append)
	register char *src, *append;
{

	for (; *src; ++src)
D 11
		/* void */;
E 11
I 11
D 14
		;
E 14
I 14
		continue;
E 14
E 11
	while (*src++ = *append++)
D 11
		/* void */;
E 11
I 11
D 14
		;
E 14
I 14
		continue;
E 14
E 11
}

strcpy(to, from)
	register char *to, *from;
{

D 14
	for (; *from = *to; ++from, ++to)
D 11
		/* void */;
E 11
I 11
		;
E 14
I 14
	for (; *to = *from; ++from, ++to)
		continue;
E 14
E 11
}

strncpy(to, from, cnt)
	register char *to, *from;
	register int cnt;
{

	for (; cnt && (*to = *from); --cnt, ++from, ++to)
D 11
		/* void */;
E 11
I 11
D 14
		;
E 14
I 14
		continue;
E 14
E 11
	*to = '\0';
}

E 15
D 10
#ifdef notdef	/* unused */
E 10
I 10
D 11
#ifndef lint	/* unused except by ct.c, other oddities */
E 11
I 11
D 14
#ifndef lint	/* unused except by ct.c, other oddities XXX */
E 14
I 14
#ifdef vax	/* unused except by ct.c, other oddities XXX */
E 14
E 11
E 10
E 9
E 8
D 6
#ifdef notdef
E 6
/*
 * Get next character written in by user from uio.
 */
I 22
int
E 22
uwritec(uio)
	struct uio *uio;
{
	register struct iovec *iov;
	register int c;

I 6
	if (uio->uio_resid <= 0)
		return (-1);
E 6
again:
D 6
	if (uio->uio_iovcnt <= 0 || uio->uio_resid <= 0)
E 6
I 6
	if (uio->uio_iovcnt <= 0)
E 6
D 22
		panic("uwritec");
E 22
I 22
		panic("uwritec: non-positive iovcnt");
E 22
	iov = uio->uio_iov;
	if (iov->iov_len == 0) {
D 6
		uio->uio_iovcnt--;
E 6
		uio->uio_iov++;
I 6
		if (--uio->uio_iovcnt == 0)
			return (-1);
E 6
		goto again;
	}
	switch (uio->uio_segflg) {

D 3
	case 0:
E 3
I 3
	case UIO_USERSPACE:
E 3
		c = fubyte(iov->iov_base);
		break;

D 3
	case 1:
E 3
I 3
	case UIO_SYSSPACE:
E 3
D 11
		c = *iov->iov_base & 0377;
E 11
I 11
		c = *(u_char *) iov->iov_base;
E 11
		break;

D 3
	case 2:
E 3
I 3
	case UIO_USERISPACE:
E 3
		c = fuibyte(iov->iov_base);
		break;
	}
	if (c < 0)
		return (-1);
	iov->iov_base++;
	iov->iov_len--;
	uio->uio_resid--;
	uio->uio_offset++;
D 11
	return (c & 0377);
E 11
I 11
	return (c);
E 11
}
I 8
D 9
#endif /* unused */
E 9
I 9
D 14
#endif /* notdef */
E 14
I 14
#endif /* vax */
I 16

/*
 * General routine to allocate a hash table.
 */
void *
hashinit(elements, type, hashmask)
	int elements, type;
	u_long *hashmask;
{
	long hashsize;
D 20
	void *hashtbl;
E 20
I 20
	LIST_HEAD(generic, generic) *hashtbl;
	int i;
E 20

	if (elements <= 0)
		panic("hashinit: bad cnt");
	for (hashsize = 1; hashsize <= elements; hashsize <<= 1)
		continue;
	hashsize >>= 1;
D 20
	hashtbl = malloc((u_long)hashsize * sizeof(void *), type, M_WAITOK);
	bzero(hashtbl, hashsize * sizeof(void *));
E 20
I 20
	hashtbl = malloc((u_long)hashsize * sizeof(*hashtbl), type, M_WAITOK);
	for (i = 0; i < hashsize; i++)
		LIST_INIT(&hashtbl[i]);
E 20
	*hashmask = hashsize - 1;
	return (hashtbl);
}
E 16
E 14
E 9
E 8
D 6
#endif
E 6
E 1
