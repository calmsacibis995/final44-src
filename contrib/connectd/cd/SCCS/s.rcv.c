h60952
s 00003/00013/00057
d D 5.2 93/05/29 11:17:14 bostic 2 1
c new copyright notices
e
s 00067/00000/00000
d D 5.1 89/05/16 08:51:23 bostic 1 0
c date and time created 89/05/16 08:51:23 by bostic
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
 * Recieve a message from a customer,
 * put in data structures and return message request type
 */
int 
rcvrequest(sock, cp, opts, optlen, rfdp) 
	int sock ;
	struct conversation *cp ;
	char **opts;
	int *optlen, *rfdp ;
	
{
	int rv ;
	struct iovec iov[4];
	int rqstfmt;
	struct msghdr msg ;
	struct connectdomain *cdp;

	cdp = &cp->co_cd ;
	msg.msg_name = "";		/* optional address */
	msg.msg_namelen = 0 ;		/* size of address */
	iov[0].iov_base = (caddr_t) &rqstfmt ;
	iov[0].iov_len = sizeof (rqstfmt) ;
	iov[1].iov_base = (caddr_t) cdp ;
	iov[1].iov_len = sizeof(cp->co_optionsbuf) + sizeof (cp->co_cd) ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	msg.msg_accrights = (caddr_t) rfdp ;
	msg.msg_accrightslen = 4;

	if ((rv = recvmsg (sock, &msg, 0)) <= 0 ) {
		perror("connection request message recieve") ;
		return (-1) ;
	}

	if (iov[1].iov_len > CDSIZE(cdp))  {
		*optlen = iov[1].iov_len - CDSIZE(cdp) ;
		*opts = iov[1].iov_base + CDSIZE(cdp);
	} else	*optlen = 0 ;

	if (msg.msg_accrightslen != 4) *rfdp = -1 ;

	return (rqstfmt) ;
}
E 1
