h25255
s 00003/00013/00045
d D 5.2 93/05/29 11:20:57 bostic 2 1
c new copyright notice
e
s 00058/00000/00000
d D 5.1 89/05/16 08:59:31 bostic 1 0
c date and time created 89/05/16 08:59:31 by bostic
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
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Unix Connection daemon
 * 
 * service request structures and subroutine definitions
 * for connection requests.
 */

#define	MAXCONNECTS	10	/* maximum number of simultaineous
					connects per process */
struct connectdomain {
	short	cd_family ;
	short	cd_alen ;
	char	cd_address[100] ;
} ;

#define	CDSIZE(s)	(sizeof(s->cd_family) + sizeof (s->cd_alen) + (s->cd_alen))

int	externalconnect(), externalabort(), externalfinish(), externaloption() ;

#define	CDNEWREQUEST	  1	/* request a new connection from client */
#define	CDNEWRESPONSE	  2	/* response from server daemon */
#define	CDCANCELREQUEST	  3	/* cancellation message from client */
#define	CDFINISHREQUEST	  5	/* finshed, pass back file descriptor to srvr */
#define	CDFINISHRESPONSE  6	/* finish acked from server to client */
#define	CDOPTIONREQUEST	  7	/* pass option request to be performed
					on descriptor by srvr */
#define	CDOPTIONRESPONSE  8	/* option acked from server to client */
#define	CDRESOFFEREQUEST  9	/* other daemon offers resources of a given type
					to srvr */
#define	CDRESOFFERESPONSE 10	/* offer acked from server to client */
#define	CDWITHDRNREQUEST  11	/* other daemon withdraws resources frm srvr */
#define	CDWITHDRNRESPONSE 12	/* resp to withdraw resources frm srvr */
#define	CDSGRANTREQUEST   13	/* connect daemon demand resource frm srvr */
#define	CDSGRANTRESPONSE  14	/* resp to demand resource frm srvr */

#define	ISCDREQUEST(s)	(s&1)	/* is this a request or response */
E 1
