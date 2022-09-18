h52244
s 00003/00013/00056
d D 5.2 93/05/29 11:17:15 bostic 2 1
c new copyright notices
e
s 00066/00000/00000
d D 5.1 89/05/16 08:51:25 bostic 1 0
c date and time created 89/05/16 08:51:25 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 2
I 2
/*-
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Bill Jolitz.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "main.h"

/*
 * Send a message back to a customer,
 * from data structures and return error status 
 */
int 
sendrequest(sock, rqst, cp, opts, optlen, fd) 
	int sock, rqst ;
	struct conversation *cp ;
	char *opts;
	int optlen, fd ;
{
	int rv ;
	struct iovec iov[4];
	struct msghdr msg ;

	/* send message to user application containing fd */
	msg.msg_name = "" ;
	msg.msg_namelen = 0 ;		/* size of address */
	iov[0].iov_base = (caddr_t) &rqst ;
	iov[0].iov_len = sizeof (rqst) ;
	iov[1].iov_base = (caddr_t) &cp->co_constatus ;
	iov[1].iov_len = sizeof(int) ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	if (opts) {
		iov[2].iov_base = (caddr_t) opts;
		iov[2].iov_len = optlen ;
		msg.msg_iovlen = 3;
	}
	if (fd >= 0) {
		msg.msg_accrights = (caddr_t) &fd ;
		msg.msg_accrightslen = sizeof(int) ;
	} else	{
		msg.msg_accrightslen = 0 ;
		msg.msg_accrights = 0 ;
	}

	rv = sendmsg(sock, &msg, 0) ; 
	if (rv < 0) {
		perror("snd:") ;
	}
	return (rv) ;
}
E 1
