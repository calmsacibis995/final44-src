h46736
s 00002/00002/00102
d D 8.1 93/06/04 15:10:59 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00030/00090
d D 5.9 93/05/12 22:57:59 bostic 9 8
c clean up the #ifdef's, courtesy of Chris T.
e
s 00038/00006/00082
d D 5.8 93/05/12 11:00:29 bostic 8 7
c build bzero(3) out of the same sources
e
s 00067/00012/00021
d D 5.7 93/05/12 10:16:36 bostic 7 6
c word-at-a-time version of memset, from Mike Hibler
e
s 00001/00001/00032
d D 5.6 91/01/26 15:31:52 bostic 6 5
c stdc.h -> cdefs.h
e
s 00021/00021/00012
d D 5.5 90/05/15 14:39:22 bostic 5 4
c ANSI C version from Chris Torek
e
s 00010/00005/00023
d D 5.4 88/06/27 18:25:38 bostic 4 3
c install approved copyright notice
e
s 00010/00008/00018
d D 5.3 88/05/25 14:23:57 bostic 3 2
c written by Robert Elz; add Berkeley specific header
e
s 00001/00001/00025
d D 5.2 86/03/09 19:34:41 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00026/00000/00000
d D 5.1 85/08/05 21:43:15 kre 1 0
c date and time created 85/08/05 21:43:15 by kre
e
u
U
t
T
I 1
D 5
/*
 * Copyright (c) 1985 Regents of the University of California.
E 5
I 5
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
E 5
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * This code is derived from software contributed to Berkeley by
D 7
 * Chris Torek.
E 7
I 7
 * Mike Hibler and Chris Torek.
E 7
 *
 * %sccs.include.redist.c%
E 5
E 4
E 3
 */

D 3
/*
 * Sys5 compat routine
 */

E 3
D 2
#ifndef lint
E 2
I 2
#if defined(LIBC_SCCS) && !defined(lint)
E 2
D 3
static char sccsid[] = "%W% (Berkeley) %E%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */
E 3

I 6
D 7
#include <sys/cdefs.h>
E 7
I 7
#include <sys/types.h>

#include <limits.h>
E 7
E 6
D 5
char *
memset(s, c, n)
	register char *s;
	register c, n;
E 5
I 5
#include <string.h>
D 6
#include <sys/stdc.h>
E 6

I 7
#define	wsize	sizeof(u_int)
#define	wmask	(wsize - 1)

I 8
#ifdef BZERO
I 9
#define	RETURN	return
#define	VAL	0
#define	WIDEVAL	0

E 9
void
bzero(dst0, length)
	void *dst0;
	register size_t length;
#else
I 9
#define	RETURN	return (dst0)
#define	VAL	c0
#define	WIDEVAL	c

E 9
E 8
E 7
void *
D 7
memset(dst, c, n)
	void *dst;
	register int c;
	register size_t n;
E 7
I 7
memset(dst0, c0, length)
	void *dst0;
	register int c0;
	register size_t length;
I 8
#endif
E 8
E 7
E 5
{
I 7
	register size_t t;
	register u_int c;
D 8
	register char *dst;
E 8
I 8
	register u_char *dst;
E 8
E 7
D 5
	register char *p = s;
E 5

D 5
	while (--n >= 0)
		*s++ = c;
E 5
I 5
D 7
	if (n != 0) {
		register char *d = dst;
E 7
I 7
D 8
	dst = (char *)dst0;
E 8
I 8
	dst = dst0;
E 8
	/*
	 * If not enough words, just fill bytes.  A length >= 2 words
	 * guarantees that at least one of them is `complete' after
	 * any necessary alignment.  For instance:
	 *
	 *	|-----------|-----------|-----------|
	 *	|00|01|02|03|04|05|06|07|08|09|0A|00|
	 *	          ^---------------------^
	 *		 dst		 dst+length-1
	 *
	 * but we use a minimum of 3 here since the overhead of the code
	 * to do word writes is substantial.
	 */ 
	if (length < 3 * wsize) {
		while (length != 0) {
I 8
D 9
#ifdef BZERO
			*dst++ = 0;
#else
E 8
			*dst++ = c0;
I 8
#endif
E 9
I 9
			*dst++ = VAL;
E 9
E 8
			--length;
		}
I 8
D 9
#ifdef BZERO
		return;
#else
E 8
		return (dst0);
I 8
#endif
E 9
I 9
		RETURN;
E 9
E 8
	}
E 7
E 5

D 5
	return (p);
E 5
I 5
D 7
		do
			*d++ = c;
		while (--n != 0);
E 7
I 7
D 8
	if ((c = (u_char)c0) != 0) {	/* Copy value into the word. */
E 8
I 8
#ifndef BZERO
	if ((c = (u_char)c0) != 0) {	/* Fill the word. */
E 8
		c = (c << 8) | c;	/* u_int is 16 bits. */
D 8
#if UINT_MAX > 65535
E 8
I 8
#if UINT_MAX > 0xffff
E 8
		c = (c << 16) | c;	/* u_int is 32 bits. */
#endif
D 8
#if UINT_MAX > 0xffffffff		/* GCC will bitch, otherwise. */
E 8
I 8
#if UINT_MAX > 0xffffffff
E 8
		c = (c << 32) | c;	/* u_int is 64 bits. */
#endif
E 7
	}
D 7
	return (dst);
E 7
I 7
D 8

E 8
I 8
#endif
E 8
	/* Align destination by filling in bytes. */
	if ((t = (int)dst & wmask) != 0) {
		t = wsize - t;
		length -= t;
		do {
I 8
D 9
#ifdef BZERO
			*dst++ = 0;
#else
E 8
			*dst++ = c0;
I 8
#endif
E 9
I 9
			*dst++ = VAL;
E 9
E 8
		} while (--t != 0);
	}

	/* Fill words.  Length was >= 2*words so we know t >= 1 here. */
	t = length / wsize;
	do {
I 8
D 9
#ifdef	BZERO
		*(u_int *)dst = 0;
#else
E 8
		*(u_int *)dst = c;
I 8
#endif
E 9
I 9
		*(u_int *)dst = WIDEVAL;
E 9
E 8
		dst += wsize;
	} while (--t != 0);

	/* Mop up trailing bytes, if any. */
	t = length & wmask;
	if (t != 0)
		do {
I 8
D 9
#ifdef BZERO
			*dst++ = 0;
#else
E 8
			*dst++ = c0;
I 8
#endif
E 9
I 9
			*dst++ = VAL;
E 9
E 8
		} while (--t != 0);
I 8
D 9
#ifdef BZERO
	return;
#else
E 8
	return (dst0);
I 8
#endif
E 9
I 9
	RETURN;
E 9
E 8
E 7
E 5
}
E 1
