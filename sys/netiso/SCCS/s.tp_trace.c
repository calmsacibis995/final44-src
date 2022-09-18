h00215
s 00002/00002/00147
d D 8.1 93/06/10 23:21:22 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00148
d D 7.6 93/05/25 11:52:16 bostic 6 5
c trailing comment after #else or #endif
e
s 00014/00015/00135
d D 7.5 92/10/11 12:22:13 bostic 5 4
c make kernel includes standard
e
s 00009/00005/00141
d D 7.4 91/05/06 19:24:41 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00145
d D 7.3 89/08/29 13:45:49 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00013/00013/00132
d D 7.2 89/04/22 11:55:46 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00145/00000/00000
d D 7.1 88/12/14 15:30:19 sklower 1 0
c date and time created 88/12/14 15:30:19 by sklower
e
u
U
t
T
I 4
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 4
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
 * $Header: tp_trace.c,v 5.3 88/11/18 17:29:14 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_trace.c,v $
I 3
D 4
 *	%W% (Berkeley) %G% *
E 4
E 3
 *
 * The whole protocol trace module.
 * We keep a circular buffer of trace structures, which are big
 * unions of different structures we might want to see.
 * Unfortunately this gets too big pretty easily. Pcbs were removed
 * from the tracing when the kernel got too big to boot.
 */
D 4

#ifndef lint
static char *rcsid = "$Header: tp_trace.c,v 5.3 88/11/18 17:29:14 nhall Exp $";
#endif lint
E 4

#define TP_TRACEFILE

D 5
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
#include "types.h"
#include "time.h"
E 5
I 5
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/time.h>
E 5

D 2
#include "../netiso/tp_param.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_param.h"
#include "../netiso/tp_ip.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_trace.h"
E 2
I 2
D 5
#include "tp_param.h"
#include "tp_timer.h"
#include "tp_stat.h"
#include "tp_param.h"
#include "tp_ip.h"
#include "tp_pcb.h"
#include "tp_tpdu.h"
#include "argo_debug.h"
#include "tp_trace.h"
E 5
I 5
#include <netiso/tp_param.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_param.h>
#include <netiso/tp_ip.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_tpdu.h>
#include <netiso/argo_debug.h>
#include <netiso/tp_trace.h>
E 5
E 2

#ifdef TPPT
static tp_seq = 0;
u_char tp_traceflags[128];

/*
 * The argument tpcb is the obvious.
 * event here is just the type of trace event - TPPTmisc, etc.
 * The rest of the arguments have different uses depending
 * on the type of trace event.
 */
/*ARGSUSED*/
/*VARARGS*/

void
tpTrace(tpcb, event, arg, src, len, arg4, arg5)
	struct tp_pcb	*tpcb;
	u_int 			event, arg;
	u_int	 		src;
	u_int	 		len; 
	u_int	 		arg4;
	u_int	 		arg5;
{
	register struct tp_Trace *tp;

	tp = &tp_Trace[tp_Tracen++];
	tp_Tracen %= TPTRACEN;

	tp->tpt_event = event;
	tp->tpt_tseq = tp_seq++;
	tp->tpt_arg = arg;
	if(tpcb)
		tp->tpt_arg2 = tpcb->tp_lref;
	bcopy( (caddr_t)&time, (caddr_t)&tp->tpt_time, sizeof(struct timeval) );

	switch(event) {

	case TPPTertpdu:
		bcopy((caddr_t)src, (caddr_t)&tp->tpt_ertpdu,
D 2
			MIN((int)len, sizeof(struct tp_Trace)));
E 2
I 2
			(unsigned)MIN((int)len, sizeof(struct tp_Trace)));
E 2
		break;

	case TPPTusrreq:
	case TPPTmisc:

		/* arg is a string */
		bcopy((caddr_t)arg, (caddr_t)tp->tpt_str, 
D 2
			MIN(1+strlen((caddr_t) arg), TPTRACE_STRLEN));
E 2
I 2
			(unsigned)MIN(1+strlen((caddr_t) arg), TPTRACE_STRLEN));
E 2
		tp->tpt_m2 = src; 
		tp->tpt_m3 = len;
		tp->tpt_m4 = arg4;
		tp->tpt_m1 = arg5;
		break;

	case TPPTgotXack: 
	case TPPTXack: 
	case TPPTsendack: 
	case TPPTgotack: 
	case TPPTack: 
	case TPPTindicate: 
	default:
	case TPPTdriver: 
		tp->tpt_m2 = arg; 
		tp->tpt_m3 = src;
		tp->tpt_m4 = len;
		tp->tpt_m5 = arg4;
		tp->tpt_m1 = arg5; 
		break;
	case TPPTparam:
		bcopy((caddr_t)src, (caddr_t)&tp->tpt_param, sizeof(struct tp_param));
		break;
	case TPPTref:
		bcopy((caddr_t)src, (caddr_t)&tp->tpt_ref, sizeof(struct tp_ref));
		break;

	case TPPTtpduin:
	case TPPTtpduout:
		tp->tpt_arg2 = arg4;
D 2
		bcopy((caddr_t)src, (caddr_t)&tp->tpt_tpdu, MIN((int)len, 
			sizeof(struct tp_Trace)));
E 2
I 2
		bcopy((caddr_t)src, (caddr_t)&tp->tpt_tpdu,
		      (unsigned)MIN((int)len, sizeof(struct tp_Trace)));
E 2
		break;
	}
}
D 6
#endif TPPT
E 6
I 6
#endif /* TPPT */
E 6
E 1
