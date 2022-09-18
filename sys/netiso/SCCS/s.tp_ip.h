h27291
s 00002/00002/00063
d D 8.1 93/06/10 23:20:27 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00064
d D 7.5 93/05/25 11:51:54 bostic 5 4
c trailing comment after #else or #endif
e
s 00008/00008/00057
d D 7.4 92/10/11 12:22:02 bostic 4 3
c make kernel includes standard
e
s 00009/00000/00056
d D 7.3 91/05/06 19:24:24 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00056
d D 7.2 89/04/22 11:55:05 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00056/00000/00000
d D 7.1 88/12/14 15:30:02 sklower 1 0
c date and time created 88/12/14 15:30:02 by sklower
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
 * ARGO TP
 *
 * $Header: tp_ip.h,v 5.1 88/10/12 12:19:47 root Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_ip.h,v $
 *
 * internet IP-dependent structures and include files
 *
 */


#ifndef __TP_IP__
#define __TP_IP__

#ifndef SOCK_STREAM
D 4
#include "socket.h"
#endif SOCK_STREAM
E 4
I 4
#include <sys/socket.h>
#endif
E 4

D 4
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
#include "../netinet/ip.h"
#include "../net/route.h"
#include "../netinet/in_pcb.h"
#include "../netinet/ip_var.h"
E 4
I 4
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <net/route.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
E 4


struct inpcb tp_inpcb;	
	/* queue of active inpcbs for tp ; for tp with dod ip */

D 5
#endif __TP_IP__
E 5
I 5
#endif /* __TP_IP__ */
E 5
E 1
