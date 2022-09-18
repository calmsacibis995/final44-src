h24234
s 00002/00002/00081
d D 8.1 93/06/04 12:50:14 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00001/00054
d D 6.7 93/06/02 17:04:49 karels 9 8
c integrate changes from bind 4.9 (most of them); continue to use address
c INADDR_ANY rather than 127.1; convert u_short to u_int16_t as appropriate
e
s 00007/00003/00048
d D 6.6 91/02/24 12:40:08 bostic 8 7
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00050
d D 6.5 90/06/01 14:14:45 bostic 7 6
c new copyright notice
e
s 00002/00001/00059
d D 6.4 88/10/30 13:43:42 bostic 6 5
c check for h_errno < 0
e
s 00010/00005/00050
d D 6.3 88/06/27 17:13:06 bostic 5 4
c install approved copyright notice
e
s 00009/00003/00046
d D 6.2 88/03/07 21:17:14 bostic 4 3
c added Berkeley specific header
e
s 00002/00008/00047
d D 6.1 87/12/04 09:43:14 karels 3 1
c can't use copyright string in libc, use std. LIBC_SCCS
e
s 00000/00006/00049
d R 1.2 87/12/04 09:41:08 karels 2 1
c can't have copyright var in libc!
e
s 00055/00000/00000
d D 1.1 87/11/17 19:18:49 bostic 1 0
c date and time created 87/11/17 19:18:49 by bostic
e
u
U
t
T
I 1
D 9
/*
E 9
I 9
/*-
E 9
D 10
 * Copyright (c) 1987 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 7
I 7
 * %sccs.include.redist.c%
I 9
 * -
 * Portions Copyright (c) 1993 by Digital Equipment Corporation.
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies, and that
 * the name of Digital Equipment Corporation not be used in advertising or
 * publicity pertaining to distribution of the document or software without
 * specific, written prior permission.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND DIGITAL EQUIPMENT CORP. DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL DIGITAL EQUIPMENT
 * CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * -
 * --Copyright--
E 9
E 7
E 5
E 4
 */

D 3
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* !lint */

#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
I 9
static char rcsid[] = "$Id: herror.c,v 4.9.1.1 1993/05/02 23:14:35 vixie Rel $";
E 9
D 3
#endif /* !lint */
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3

#include <sys/types.h>
#include <sys/uio.h>
I 8
#include <netdb.h>
#include <unistd.h>
#include <string.h>
E 8

char	*h_errlist[] = {
	"Error 0",
	"Unknown host",				/* 1 HOST_NOT_FOUND */
	"Host name lookup failure",		/* 2 TRY_AGAIN */
	"Unknown server error",			/* 3 NO_RECOVERY */
	"No address associated with name",	/* 4 NO_ADDRESS */
};
int	h_nerr = { sizeof(h_errlist)/sizeof(h_errlist[0]) };

extern int	h_errno;

/*
 * herror --
 *	print the error indicated by the h_errno value.
 */
I 8
void
E 8
herror(s)
D 8
	char *s;
E 8
I 8
	const char *s;
E 8
{
	struct iovec iov[4];
	register struct iovec *v = iov;

	if (s && *s) {
D 8
		v->iov_base = s;
E 8
I 8
		v->iov_base = (char *)s;
E 8
		v->iov_len = strlen(s);
		v++;
		v->iov_base = ": ";
		v->iov_len = 2;
		v++;
	}
D 6
	v->iov_base = h_errno < h_nerr ? h_errlist[h_errno] : "Unknown error";
E 6
I 6
	v->iov_base = (u_int)h_errno < h_nerr ?
	    h_errlist[h_errno] : "Unknown error";
E 6
	v->iov_len = strlen(v->iov_base);
	v++;
	v->iov_base = "\n";
	v->iov_len = 1;
D 8
	writev(2, iov, (v - iov) + 1);
E 8
I 8
	writev(STDERR_FILENO, iov, (v - iov) + 1);
I 9
}

char *
hstrerror(err)
	int err;
{
	return (u_int)err < h_nerr ? h_errlist[err] : "Unknown resolver error";
E 9
E 8
}
E 1
