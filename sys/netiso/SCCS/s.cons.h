h14191
s 00002/00002/00064
d D 8.1 93/06/10 23:19:00 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00064
d D 7.5 93/06/04 17:02:23 sklower 5 4
c fix #endif something to #endif /* something */
e
s 00001/00001/00065
d D 7.4 92/10/11 12:21:42 bostic 4 3
c make kernel includes standard
e
s 00009/00000/00057
d D 7.3 91/05/06 19:23:52 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00057
d D 7.2 89/04/22 11:53:40 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00057/00000/00000
d D 7.1 88/12/14 15:29:30 sklower 1 0
c date and time created 88/12/14 15:29:30 by sklower
e
u
U
t
T
I 3
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
/*
 * $Header: cons.h,v 4.4 88/09/09 19:01:28 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/cons.h,v $
 *
 * interface between TP and CONS
 */

#define	CONSOPT_X25CRUD	0x01		/* set x.25 call request user data */

struct dte_addr {
	u_char 	dtea_addr[7];
	u_char	dtea_niblen;
};

#ifdef	KERNEL

#define CONN_OPEN		0x33
#define CONN_CONFIRM	0x30
#define CONN_REFUSE		0x31
#define CONN_CLOSE		0x32

#define	CONS_IS_DGM		0x1
#define	CONS_NOT_DGM	0x0

#ifndef	PRC_NCMDS
D 4
#include "protosw.h"
E 4
I 4
#include <sys/protosw.h>
E 4
D 5
#endif	PRC_NCMDS
E 5
I 5
#endif	/* PRC_NCMDS */
E 5

#define PRC_CONS_SEND_DONE 2 /* something unused in protosw.h */

D 5
#endif	KERNEL
E 5
I 5
#endif	/* KERNEL */
E 5
E 1
