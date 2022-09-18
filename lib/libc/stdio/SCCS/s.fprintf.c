h59230
s 00002/00002/00040
d D 8.1 93/06/04 13:05:43 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00020/00015
d D 5.6 91/01/20 21:20:30 bostic 10 9
c new stdio
e
s 00001/00011/00034
d D 5.5 90/06/01 14:43:10 bostic 9 8
c new copyright notice
e
s 00010/00005/00035
d D 5.4 88/06/27 17:50:03 bostic 8 7
c install approved copyright notice
e
s 00017/00009/00023
d D 5.3 87/12/12 12:49:17 bostic 7 6
c fprintf returns number of chars processed; attach Berkeley header
e
s 00002/00002/00030
d D 5.2 86/03/09 20:50:27 donn 6 5
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00022
d D 5.1 85/05/30 14:28:31 dist 5 4
c Add copyright
e
s 00001/00001/00022
d D 4.4 85/02/13 15:48:35 serge 4 3
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00001/00000/00022
d D 4.3 84/06/04 15:40:45 ralph 3 2
c don't forget to clear _cnt.
e
s 00013/00001/00009
d D 4.2 84/05/04 13:52:37 ralph 2 1
c don't do 1 byte writes, buffer and flush unbuffered I/O (stderr).
e
s 00010/00000/00000
d D 4.1 80/12/21 16:50:20 wnj 1 0
c date and time created 80/12/21 16:50:20 by wnj
e
u
U
t
T
I 1
D 5
/* %W% (Berkeley) %G% */
E 5
I 5
D 10
/*
 * Copyright (c) 1980 Regents of the University of California.
E 10
I 10
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
E 10
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
I 10
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
E 10
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
E 7
 */

D 6
#ifndef lint
E 6
I 6
#if defined(LIBC_SCCS) && !defined(lint)
E 6
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 6

E 5
D 7
#include	<stdio.h>
E 7
I 7
#include <stdio.h>
I 10
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 10
E 7

D 10
fprintf(iop, fmt, args)
D 4
FILE *iop;
E 4
I 4
D 7
register FILE *iop;
E 4
char *fmt;
E 7
I 7
	register FILE *iop;
E 10
I 10
#if __STDC__
fprintf(FILE *fp, const char *fmt, ...)
#else
fprintf(fp, fmt, va_alist)
	FILE *fp;
E 10
	char *fmt;
D 10
	int args;
E 10
I 10
	va_dcl
#endif
E 10
E 7
{
I 7
D 10
	int len;
E 7
D 2
	_doprnt(fmt, &args, iop);
E 2
I 2
	char localbuf[BUFSIZ];
E 10
I 10
	int ret;
	va_list ap;
E 10

D 10
	if (iop->_flag & _IONBF) {
		iop->_flag &= ~_IONBF;
		iop->_ptr = iop->_base = localbuf;
		iop->_bufsiz = BUFSIZ;
D 7
		_doprnt(fmt, &args, iop);
E 7
I 7
		len = _doprnt(fmt, &args, iop);
E 7
		fflush(iop);
		iop->_flag |= _IONBF;
		iop->_base = NULL;
		iop->_bufsiz = NULL;
I 3
		iop->_cnt = 0;
E 3
	} else
D 7
		_doprnt(fmt, &args, iop);
E 2
	return(ferror(iop)? EOF: 0);
E 7
I 7
		len = _doprnt(fmt, &args, iop);
	return(ferror(iop) ? EOF : len);
E 10
I 10
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	ret = vfprintf(fp, fmt, ap);
	va_end(ap);
	return (ret);
E 10
E 7
}
E 1
