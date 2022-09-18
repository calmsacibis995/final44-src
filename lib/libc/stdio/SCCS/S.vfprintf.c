h49211
s 00002/00002/00035
d D 5.4 90/06/30 17:57:14 bostic 4 3
c set buffer size to avoid 1 character writes
e
s 00001/00011/00036
d D 5.3 90/06/01 14:43:46 bostic 3 2
c new copyright notice
e
s 00010/00005/00037
d D 5.2 88/06/27 17:50:08 bostic 2 1
c install approved copyright notice
e
s 00042/00000/00000
d D 5.1 88/05/24 18:59:02 bostic 1 0
c date and time created 88/05/24 18:59:02 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
D 3
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>
#include <varargs.h>

int
vfprintf(iop, fmt, ap)
	FILE *iop;
	char *fmt;
	va_list ap;
{
	int len;
	char localbuf[BUFSIZ];

	if (iop->_flag & _IONBF) {
		iop->_flag &= ~_IONBF;
		iop->_ptr = iop->_base = localbuf;
I 4
		iop->_bufsiz = BUFSIZ;
E 4
		len = _doprnt(fmt, ap, iop);
D 4
		(void) fflush(iop);
E 4
I 4
		(void)fflush(iop);
E 4
		iop->_flag |= _IONBF;
		iop->_base = NULL;
		iop->_bufsiz = 0;
		iop->_cnt = 0;
	} else
		len = _doprnt(fmt, ap, iop);
D 4

E 4
	return (ferror(iop) ? EOF : len);
}
E 1
