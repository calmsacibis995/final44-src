h27105
s 00002/00002/00971
d D 8.1 93/06/10 23:20:47 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00966
d D 7.26 93/05/25 11:52:01 bostic 26 25
c trailing comment after #else or #endif
e
s 00021/00020/00952
d D 7.25 92/10/11 12:22:06 bostic 25 24
c make kernel includes standard
e
s 00001/00000/00971
d D 7.24 92/05/27 16:14:55 sklower 24 23
c remember initial so_rcv space for later
e
s 00023/00008/00948
d D 7.23 92/04/17 15:53:16 sklower 23 22
c fix bug with specifying specific network address but defaulting tsel
e
s 00001/00001/00955
d D 7.22 91/10/02 21:57:22 sklower 22 21
c fix typo
e
s 00006/00002/00950
d D 7.21 91/10/02 21:45:20 sklower 21 20
c don't stomp on sockbuff sizes if already set
e
s 00000/00008/00952
d D 7.20 91/10/02 19:49:16 sklower 20 19
c get rid of useless tp_param global structure.
e
s 00020/00019/00940
d D 7.19 91/09/30 17:54:14 sklower 19 18
c remove back pointer to entry in tp_ref table; use tp_lref instead.
e
s 00007/00007/00952
d D 7.18 91/09/26 17:02:31 sklower 18 17
c These changes represent a rewrite of retransmission policies to
c imitate the TCP algorithms more closely.  More tuning and testing need to
c be done, but the code runs at least somewhat, and these represent a checkpoint
e
s 00045/00029/00914
d D 7.17 91/09/05 18:02:15 sklower 17 16
c effectively merge tp_ref structure with rest of tp_pcb;
c this version doesn't crash, but does exhibit lumpy behavior;
c ack & retrans policies need to be fixed
e
s 00017/00000/00926
d D 7.16 91/08/30 12:12:39 sklower 16 15
c paranoia about freeing a tpcb while still in the list of bound tcb's
c or list of children of a given TSEL
e
s 00008/00023/00918
d D 7.15 91/08/28 12:55:56 sklower 15 14
c changes to get rid of RTC structure
e
s 00048/00054/00893
d D 7.14 91/07/29 14:55:17 sklower 14 13
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00102/00000/00845
d D 7.13 91/07/23 17:05:47 sklower 13 12
c note semi-working version with only listen and bind changes
e
s 00005/00006/00840
d D 7.12 91/07/18 20:33:20 sklower 12 11
c this changes reflect getting rid of so_tpcb.
e
s 00009/00005/00837
d D 7.11 91/05/06 19:24:30 bostic 11 10
c new copyright; att/bsd/shared
e
s 00002/00002/00840
d D 7.10 91/05/06 18:22:37 sklower 10 9
c tpclnp_mtu should do work for tpcons_mtu.
e
s 00003/00011/00839
d D 7.9 91/04/26 14:52:50 sklower 9 8
c off by one error in allocating ref structures
e
s 00016/00036/00834
d D 7.8 91/03/12 15:56:26 sklower 8 7
c fixes from mostek@cray
e
s 00006/00008/00864
d D 7.7 91/01/09 15:45:09 sklower 7 6
c Checkpoint integration of tp_cons with UBC X.25; compiles only;
c not tested, probably not complete.
e
s 00006/00003/00866
d D 7.6 90/06/28 19:40:03 sklower 6 5
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00002/00000/00867
d D 7.5 90/01/16 23:01:20 sklower 5 4
c mitre decbit changes
e
s 00002/00002/00865
d D 7.4 89/09/22 00:44:18 sklower 4 3
c fixes to tracing and avoiding silly window between
c socket layer and transport; more changes to come to usrreq and tp_send.
e
s 00007/00021/00860
d D 7.3 89/08/29 13:45:15 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00062/00094/00819
d D 7.2 89/04/22 11:55:18 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00913/00000/00000
d D 7.1 88/12/14 15:30:08 sklower 1 0
c date and time created 88/12/14 15:30:08 by sklower
e
u
U
t
T
I 11
/*-
D 27
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 11
I 1
/***********************************************************
D 4
		Copyright IBM Corporation 1987
E 4
I 4
				Copyright IBM Corporation 1987
E 4

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
 * $Header: tp_pcb.c,v 5.4 88/11/18 17:28:24 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_pcb.c,v $
I 3
D 11
 *	%W% (Berkeley) %G% *
E 11
E 3
 *
 *
 * This is the initialization and cleanup stuff - 
 * for the tp machine in general as well as  for the individual pcbs.
 * tp_init() is called at system startup.  tp_attach() and tp_getref() are
 * called when a socket is created.  tp_detach() and tp_freeref()
 * are called during the closing stage and/or when the reference timer 
 * goes off. 
 * tp_soisdisconnecting() and tp_soisdisconnected() are tp-specific 
 * versions of soisconnect*
 * and are called (obviously) during the closing phase.
 *
 */
D 11

#ifndef lint
static char *rcsid = "$Header: tp_pcb.c,v 5.4 88/11/18 17:28:24 nhall Exp $";
#endif lint
E 11

D 7
#include "argoxtwentyfive.h"
E 7
D 14
#include "types.h"
E 14
D 25
#include "param.h"
I 14
#include "systm.h"
E 14
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
I 14
#include "domain.h"
E 14
#include "protosw.h"
#include "errno.h"
#include "time.h"
D 2
#include "../netiso/tp_param.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_ip.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_meas.h"
#include "../netiso/tp_seq.h"
#include "../netiso/tp_clnp.h"
E 2
I 2
#include "argo_debug.h"
#include "tp_param.h"
#include "tp_timer.h"
#include "tp_ip.h"
#include "tp_stat.h"
#include "tp_pcb.h"
#include "tp_tpdu.h"
#include "tp_trace.h"
#include "tp_meas.h"
#include "tp_seq.h"
#include "tp_clnp.h"
E 25
I 25
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>

#include <netiso/argo_debug.h>
#include <netiso/tp_param.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_ip.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_tpdu.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_meas.h>
#include <netiso/tp_seq.h>
#include <netiso/tp_clnp.h>
E 25
E 2

D 9
/* list of reference structures */
struct tp_ref tp_ref[N_TPREF];

E 9
D 20
struct tp_param tp_param = {
	1,				/*  configured 		*/
};

E 20
/* ticks are in units of: 
 * 500 nano-fortnights ;-) or
 * 500 ms or 
 * 1/2 second 
 */

struct tp_conn_param tp_conn_param[] = {
	/* ISO_CLNS: TP4 CONNECTION LESS */
	{
		TP_NRETRANS, 	/* short p_Nretrans;  */
		20,		/* 10 sec */ 	/* short p_dr_ticks;  */

		20,		/* 10 sec */ 	/* short p_cc_ticks; */
		20,		/* 10 sec */ 	/* short p_dt_ticks; */

		40,		/* 20 sec */ 	/* short p_x_ticks;	 */
		80,		/* 40 sec */ 	/* short p_cr_ticks;*/

		240,	/* 2 min */ 	/* short p_keepalive_ticks;*/
		10,		/* 5 sec */ 	/* short p_sendack_ticks;  */

		600,	/* 5 min */ 	/* short p_ref_ticks;	*/
		360,	/* 3 min */ 	/* short p_inact_ticks;	*/

		(short) 100, 			/* short p_lcdtfract */
		(short) TP_SOCKBUFSIZE,	/* short p_winsize */
		TP_TPDUSIZE, 			/* u_char p_tpdusize */

		TPACK_WINDOW, 			/* 4 bits p_ack_strat */
		TPRX_USE_CW | TPRX_FASTSTART, 
								/* 4 bits p_rx_strat*/
		TP_CLASS_4 | TP_CLASS_0,/* 5 bits p_class */
		1,						/* 1 bit xtd format */
		1,						/* 1 bit xpd service */
		1,						/* 1 bit use_checksum */
		0,						/* 1 bit use net xpd */
		0,						/* 1 bit use rcc */
		0,						/* 1 bit use efc */
D 3
		0,						/* no disc indications */
E 3
I 3
		1,						/* no disc indications */
E 3
		0,						/* don't change params */
		ISO_CLNS,				/* p_netservice */
	},
	/* IN_CLNS: TP4 CONNECTION LESS */
	{
		TP_NRETRANS, 	/* short p_Nretrans;  */
		20,		/* 10 sec */ 	/* short p_dr_ticks;  */

		20,		/* 10 sec */ 	/* short p_cc_ticks; */
		20,		/* 10 sec */ 	/* short p_dt_ticks; */

		40,		/* 20 sec */ 	/* short p_x_ticks;	 */
		80,		/* 40 sec */ 	/* short p_cr_ticks;*/

		240,	/* 2 min */ 	/* short p_keepalive_ticks;*/
		10,		/* 5 sec */ 	/* short p_sendack_ticks;  */

		600,	/* 5 min */ 	/* short p_ref_ticks;	*/
		360,	/* 3 min */ 	/* short p_inact_ticks;	*/

		(short) 100, 			/* short p_lcdtfract */
		(short) TP_SOCKBUFSIZE,	/* short p_winsize */
		TP_TPDUSIZE, 			/* u_char p_tpdusize */

		TPACK_WINDOW, 			/* 4 bits p_ack_strat */
		TPRX_USE_CW | TPRX_FASTSTART, 
								/* 4 bits p_rx_strat*/
		TP_CLASS_4,				/* 5 bits p_class */
		1,						/* 1 bit xtd format */
		1,						/* 1 bit xpd service */
		1,						/* 1 bit use_checksum */
		0,						/* 1 bit use net xpd */
		0,						/* 1 bit use rcc */
		0,						/* 1 bit use efc */
D 3
		0,						/* no disc indications */
E 3
I 3
		1,						/* no disc indications */
E 3
		0,						/* don't change params */
		IN_CLNS,				/* p_netservice */
	},
	/* ISO_CONS: TP0 CONNECTION MODE */
	{
		TP_NRETRANS, 			/* short p_Nretrans;  */
		0,		/* n/a */		/* short p_dr_ticks; */

		40,		/* 20 sec */	/* short p_cc_ticks; */
		0,		/* n/a */		/* short p_dt_ticks; */

		0,		/* n/a */		/* short p_x_ticks;	*/
		360,	/* 3  min */	/* short p_cr_ticks;*/

		0,		/* n/a */		/* short p_keepalive_ticks;*/
		0,		/* n/a */		/* short p_sendack_ticks; */

		600,	/* for cr/cc to clear *//* short p_ref_ticks;	*/
		0,		/* n/a */		/* short p_inact_ticks;	*/

		/* Use tp4 defaults just in case the user changes ONLY
		 * the class 
		 */
		(short) 100, 			/* short p_lcdtfract */
		(short) TP0_SOCKBUFSIZE,	/* short p_winsize */
		TP0_TPDUSIZE, 			/* 8 bits p_tpdusize */

		0, 						/* 4 bits p_ack_strat */
		0, 						/* 4 bits p_rx_strat*/
		TP_CLASS_0,				/* 5 bits p_class */
		0,						/* 1 bit xtd format */
		0,						/* 1 bit xpd service */
		0,						/* 1 bit use_checksum */
		0,						/* 1 bit use net xpd */
		0,						/* 1 bit use rcc */
		0,						/* 1 bit use efc */
		0,						/* no disc indications */
		0,						/* don't change params */
		ISO_CONS,				/* p_netservice */
	},
	/* ISO_COSNS: TP4 CONNECTION LESS SERVICE over CONSNS */
	{
		TP_NRETRANS, 	/* short p_Nretrans;  */
		40,		/* 20 sec */ 	/* short p_dr_ticks;  */

		40,		/* 20 sec */ 	/* short p_cc_ticks; */
		80,		/* 40 sec */ 	/* short p_dt_ticks; */

		120,		/* 1 min */ 	/* short p_x_ticks;	 */
		360,		/* 3 min */ 	/* short p_cr_ticks;*/

		360,	/* 3 min */ 	/* short p_keepalive_ticks;*/
		20,		/* 10 sec */ 	/* short p_sendack_ticks;  */

		600,	/* 5 min */ 	/* short p_ref_ticks;	*/
		480,	/* 4 min */ 	/* short p_inact_ticks;	*/

		(short) 100, 			/* short p_lcdtfract */
		(short) TP0_SOCKBUFSIZE,	/* short p_winsize */
		TP0_TPDUSIZE, 			/* u_char p_tpdusize */

		TPACK_WINDOW, 			/* 4 bits p_ack_strat */
		TPRX_USE_CW ,			/* No fast start */ 
								/* 4 bits p_rx_strat*/
		TP_CLASS_4 | TP_CLASS_0,/* 5 bits p_class */
		0,						/* 1 bit xtd format */
		1,						/* 1 bit xpd service */
		1,						/* 1 bit use_checksum */
		0,						/* 1 bit use net xpd */
		0,						/* 1 bit use rcc */
		0,						/* 1 bit use efc */
		0,						/* no disc indications */
		0,						/* don't change params */
		ISO_COSNS,				/* p_netservice */
	},
};

#ifdef INET
int		in_putnetaddr();
int		in_getnetaddr();
I 6
int		in_cmpnetaddr();
E 6
int 	in_putsufx(); 
int 	in_getsufx(); 
int 	in_recycle_tsuffix(); 
int 	tpip_mtu(); 
int 	in_pcbbind(); 
int 	in_pcbconnect(); 
int 	in_pcbdisconnect(); 
int 	in_pcbdetach(); 
int 	in_pcballoc(); 
int 	tpip_output(); 
int 	tpip_output_dg(); 
struct inpcb	tp_inpcb;
D 26
#endif INET
E 26
I 26
#endif /* INET */
E 26
#ifdef ISO
int		iso_putnetaddr();
int		iso_getnetaddr();
I 6
int		iso_cmpnetaddr();
E 6
int 	iso_putsufx(); 
int 	iso_getsufx(); 
int 	iso_recycle_tsuffix(); 
int		tpclnp_mtu(); 
int		iso_pcbbind(); 
int		iso_pcbconnect(); 
int		iso_pcbdisconnect(); 
int 	iso_pcbdetach(); 
int 	iso_pcballoc(); 
int 	tpclnp_output(); 
int 	tpclnp_output_dg(); 
int		iso_nlctloutput();
struct isopcb	tp_isopcb;
D 26
#endif ISO
E 26
I 26
#endif /* ISO */
E 26
D 7
#if NARGOXTWENTYFIVE > 0
E 7
I 7
#ifdef TPCONS
E 7
int		iso_putnetaddr();
int		iso_getnetaddr();
I 6
int		iso_cmpnetaddr();
E 6
int 	iso_putsufx(); 
int 	iso_getsufx(); 
int 	iso_recycle_tsuffix(); 
D 10
int		tpcons_mtu(); 
E 10
int		iso_pcbbind(); 
D 7
int		iso_pcbconnect(); 
E 7
I 7
int		tpcons_pcbconnect(); 
I 10
int		tpclnp_mtu();
E 10
E 7
int		iso_pcbdisconnect(); 
int 	iso_pcbdetach(); 
int 	iso_pcballoc(); 
int 	tpcons_output(); 
D 7
int 	tpcons_output_dg(); 
E 7
struct isopcb	tp_isopcb;
D 7
#endif NARGOXTWENTYFIVE
E 7
I 7
D 26
#endif TPCONS
E 26
I 26
#endif /* TPCONS */
E 26
E 7

I 2

E 2
struct nl_protosw nl_protosw[] = {
	/* ISO_CLNS */
#ifdef ISO
D 6
	{ AF_ISO, iso_putnetaddr, iso_getnetaddr,
E 6
I 6
	{ AF_ISO, iso_putnetaddr, iso_getnetaddr, iso_cmpnetaddr,
E 6
		iso_putsufx, iso_getsufx,
		iso_recycle_tsuffix,
		tpclnp_mtu, iso_pcbbind, iso_pcbconnect,
		iso_pcbdisconnect,	iso_pcbdetach,
		iso_pcballoc,
		tpclnp_output, tpclnp_output_dg, iso_nlctloutput,
		(caddr_t) &tp_isopcb,
		},
I 2
#else
	{ 0 },
E 2
D 26
#endif ISO
E 26
I 26
#endif /* ISO */
E 26
	/* IN_CLNS */
#ifdef INET
D 6
	{ AF_INET, in_putnetaddr, in_getnetaddr,
E 6
I 6
	{ AF_INET, in_putnetaddr, in_getnetaddr, in_cmpnetaddr,
E 6
		in_putsufx, in_getsufx,
		in_recycle_tsuffix,
		tpip_mtu, in_pcbbind, in_pcbconnect,
		in_pcbdisconnect,	in_pcbdetach,
		in_pcballoc,
		tpip_output, tpip_output_dg, /* nl_ctloutput */ NULL,
		(caddr_t) &tp_inpcb,
		},
I 2
#else
	{ 0 },
E 2
D 26
#endif INET
E 26
I 26
#endif /* INET */
E 26
	/* ISO_CONS */
D 2
#ifdef ISO
#if	NARGOXTWENTYFIVE > 0
E 2
I 2
D 7
#if defined(ISO) && (NARGOXTWENTYFIVE > 0)
E 7
I 7
#if defined(ISO) && defined(TPCONS)
E 7
E 2
D 6
	{ AF_ISO, iso_putnetaddr, iso_getnetaddr,
E 6
I 6
	{ AF_ISO, iso_putnetaddr, iso_getnetaddr, iso_cmpnetaddr,
E 6
		iso_putsufx, iso_getsufx,
		iso_recycle_tsuffix,
D 7
		tpcons_mtu, iso_pcbbind, iso_pcbconnect,
E 7
I 7
D 10
		tpcons_mtu, iso_pcbbind, tpcons_pcbconnect,
E 10
I 10
		tpclnp_mtu, iso_pcbbind, tpcons_pcbconnect,
E 10
E 7
		iso_pcbdisconnect,	iso_pcbdetach,
		iso_pcballoc,
D 7
		tpcons_output, tpcons_output_dg, iso_nlctloutput,
E 7
I 7
		tpcons_output, tpcons_output, iso_nlctloutput,
E 7
		(caddr_t) &tp_isopcb,
		},
D 2
#endif NARGOXTWENTYFIVE
#endif ISO
	{ 0, 0, 0,
		0, 0,
		0,
		0, 0, 0,
		0,	0,
		0,
		0, 0, 0,
		(caddr_t) 0,
		}
E 2
I 2
#else
	{ 0 },
D 26
#endif ISO_CONS
E 26
I 26
#endif /* ISO_CONS */
E 26
	/* End of protosw marker */
	{ 0 }
E 2
};

I 21
u_long tp_sendspace = 1024 * 4;
u_long tp_recvspace = 1024 * 4;

E 21
/*
 * NAME:  tp_init()
 *
 * CALLED FROM:
 *  autoconf through the protosw structure
 *
 * FUNCTION:
 *  initialize tp machine
 *
 * RETURNS:  Nada
 *
 * SIDE EFFECTS:
 * 
 * NOTES:
 */
D 2
void
E 2
I 2
int
E 2
tp_init()
{
	static int 	init_done=0;
	void	 	tp_timerinit();

	if (init_done++)
D 2
		return;
E 2
I 2
		return 0;
E 2

D 2
#ifndef lint
	if ( (sizeof(struct tp_pcb) >= MLEN)  || (sizeof(struct tp_pcb_aux) >= MLEN)  ){
		tp_param.tpp_configed = 0;
		printf(
			"TP not configured !!! pcb (0x%x, %d) or aux (0x%x, %d) too big!\n",
			sizeof(struct tp_pcb), sizeof(struct tp_pcb), 
			sizeof(struct tp_pcb_aux), sizeof(struct tp_pcb_aux));
		printf("MLEN (0x%x, %d)\n", MLEN, MLEN);
	}
#endif lint
E 2

	/* FOR INET */
	tp_inpcb.inp_next = tp_inpcb.inp_prev = &tp_inpcb;
	/* FOR ISO */
	tp_isopcb.isop_next = tp_isopcb.isop_prev = &tp_isopcb;

I 5
    tp_start_win = 2;

E 5
	tp_timerinit();
	bzero((caddr_t)&tp_stat, sizeof(struct tp_stat));
I 2
	return 0;
E 2
}

/*
 * NAME: 	tp_soisdisconnecting()
 *
 * CALLED FROM:
 *  tp.trans
 *
 * FUNCTION and ARGUMENTS:
 *  Set state of the socket (so) to reflect that fact that we're disconnectING
 *
 * RETURNS: 	Nada
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 *  This differs from the regular soisdisconnecting() in that the latter
 *  also sets the SS_CANTRECVMORE and SS_CANTSENDMORE flags.
 *  We don't want to set those flags because those flags will cause
 *  a SIGPIPE to be delivered in sosend() and we don't like that.
 *  If anyone else is sleeping on this socket, wake 'em up.
 */
void
tp_soisdisconnecting(so)
	register struct socket *so;
{
D 3
	so->so_state &= ~SS_ISCONNECTING;
	so->so_state |= SS_ISDISCONNECTING;
	if (so->so_head) {
		if (!soqremque(so, 0) && !soqremque(so, 1))
			panic("tp_soisdisconnecting");
		so->so_head = 0;
	}
	wakeup((caddr_t)&so->so_timeo);
	sowwakeup(so);
	sorwakeup(so);
E 3
I 3
	soisdisconnecting(so);
	so->so_state &= ~SS_CANTSENDMORE;
E 3
	IFPERF(sototpcb(so))
		register struct tp_pcb *tpcb = sototpcb(so);
		u_int 	fsufx, lsufx;

D 2
		bcopy ( tpcb->tp_fsuffix, &fsufx, sizeof(u_int) );
		bcopy ( tpcb->tp_lsuffix, &lsufx, sizeof(u_int) );
E 2
I 2
		bcopy ((caddr_t)tpcb->tp_fsuffix, (caddr_t)&fsufx, sizeof(u_int) );
		bcopy ((caddr_t)tpcb->tp_lsuffix, (caddr_t)&lsufx, sizeof(u_int) );
E 2

D 2
		tpmeas( tpcb->tp_lref, TPtime_close, 
			&time, fsufx, lsufx, tpcb->tp_fref);
E 2
I 2
		tpmeas(tpcb->tp_lref, TPtime_close, &time, fsufx, lsufx, tpcb->tp_fref);
E 2
		tpcb->tp_perf_on = 0; /* turn perf off */
	ENDPERF
}


/*
 * NAME: tp_soisdisconnected()
 *
 * CALLED FROM:
 *	tp.trans	
 *
 * FUNCTION and ARGUMENTS:
 *  Set state of the socket (so) to reflect that fact that we're disconnectED
 *  Set the state of the reference structure to closed, and
 *  recycle the suffix.
 *  Start a reference timer.
 *
 * RETURNS:	Nada
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 *  This differs from the regular soisdisconnected() in that the latter
 *  also sets the SS_CANTRECVMORE and SS_CANTSENDMORE flags.
 *  We don't want to set those flags because those flags will cause
 *  a SIGPIPE to be delivered in sosend() and we don't like that.
 *  If anyone else is sleeping on this socket, wake 'em up.
 */
void
tp_soisdisconnected(tpcb)
	register struct tp_pcb	*tpcb;
{
	register struct socket	*so = tpcb->tp_sock;

D 3
	so->so_state &= ~(SS_ISCONNECTING|SS_ISCONNECTED|SS_ISDISCONNECTING);
	if (so->so_head) {
		if (!soqremque(so, 0) && !soqremque(so, 1))
			panic("tp_soisdisconnected");
		so->so_head = 0;
	}
	wakeup((caddr_t)&so->so_timeo);
	sowwakeup(so);
	sorwakeup(so);
E 3
I 3
	soisdisconnecting(so);
	so->so_state &= ~SS_CANTSENDMORE;
E 3
D 17
	IFPERF(sototpcb(so))
E 17
I 17
	IFPERF(tpcb)
E 17
D 2
		register struct tp_pcb *tpcb = sototpcb(so);
E 2
I 2
		register struct tp_pcb *ttpcb = sototpcb(so);
E 2
		u_int 	fsufx, lsufx;

		/* CHOKE */
D 2
		bcopy ( tpcb->tp_fsuffix, &fsufx, sizeof(u_int) );
		bcopy ( tpcb->tp_lsuffix, &lsufx, sizeof(u_int) );
E 2
I 2
		bcopy ((caddr_t)ttpcb->tp_fsuffix, (caddr_t)&fsufx, sizeof(u_int) );
		bcopy ((caddr_t)ttpcb->tp_lsuffix, (caddr_t)&lsufx, sizeof(u_int) );
E 2

D 2
		tpmeas( tpcb->tp_lref, TPtime_close, 
			&time, &lsufx, &fsufx, tpcb->tp_fref);
E 2
I 2
		tpmeas(ttpcb->tp_lref, TPtime_close, 
		   &time, &lsufx, &fsufx, ttpcb->tp_fref);
E 2
		tpcb->tp_perf_on = 0; /* turn perf off */
	ENDPERF

D 17
	tpcb->tp_refp->tpr_state = REF_FROZEN;
	tp_recycle_tsuffix( tpcb );
E 17
I 17
	tpcb->tp_refstate = REF_FROZEN;
	tp_recycle_tsuffix(tpcb);
E 17
D 18
	tp_etimeout(tpcb->tp_refp, TM_reference, 0,0,0, (int)tpcb->tp_refer_ticks);
E 18
I 18
	tp_etimeout(tpcb, TM_reference, (int)tpcb->tp_refer_ticks);
E 18
}

D 17
int tp_maxrefopen;  /* highest reference # of the set of open tp connections */

E 17
/*
 * NAME:	tp_freeref()
 *
 * CALLED FROM:
 *  tp.trans when the reference timer goes off, and
 *  from tp_attach() and tp_detach() when a tpcb is partially set up but not
 *  set up enough to have a ref timer set for it, and it's discarded
 *  due to some sort of error or an early close()
 *
 * FUNCTION and ARGUMENTS:
 *  Frees the reference represented by (r) for re-use.
 *
 * RETURNS: Nothing
 * 
 * SIDE EFFECTS:
 *
 * NOTES:	better be called at clock priority !!!!!
 */
void
D 19
tp_freeref(r)
	register struct tp_ref *r;
E 19
I 19
tp_freeref(n)
RefNum n;
E 19
{
I 17
D 19
	register struct tp_pcb *tpcb = r->tpr_pcb;
E 19
I 19
	register struct tp_ref *r = tp_ref + n;
	register struct tp_pcb *tpcb;

	tpcb = r->tpr_pcb;
E 19
E 17
	IFDEBUG(D_TIMER)
D 19
		printf("tp_freeref called for ref %d maxrefopen %d\n", 
D 17
		r - tp_ref, tp_maxrefopen);
E 17
I 17
		r - tp_ref, tp_refinfo.tpr_maxopen);
E 19
I 19
		printf("tp_freeref called for ref %d pcb %x maxrefopen %d\n", 
		n, tpcb, tp_refinfo.tpr_maxopen);
E 19
E 17
	ENDDEBUG
	IFTRACE(D_TIMER)
D 17
		tptrace(TPPTmisc, "tp_freeref ref tp_maxrefopen",
		r - tp_ref, tp_maxrefopen, 0, 0);
E 17
I 17
D 19
		tptrace(TPPTmisc, "tp_freeref ref maxrefopen",
		r - tp_ref, tp_refinfo.tpr_maxopen, 0, 0);
E 19
I 19
		tptrace(TPPTmisc, "tp_freeref ref maxrefopen pcb",
		n, tp_refinfo.tpr_maxopen, tpcb, 0);
E 19
E 17
	ENDTRACE
D 19
	r->tpr_state = REF_FREE;
E 19
I 19
	if (tpcb == 0)
		return;
E 19
	IFDEBUG(D_CONN)
D 19
		printf("tp_freeref: CLEARING tpr_pcb 0x%x\n", r->tpr_pcb);
E 19
I 19
		printf("tp_freeref: CLEARING tpr_pcb 0x%x\n", tpcb);
E 19
	ENDDEBUG
	r->tpr_pcb = (struct tp_pcb *)0;
I 17
D 19
	if (tpcb)
		tpcb->tp_refp = 0;
E 19
I 19
	tpcb->tp_refstate = REF_FREE;
E 19
E 17

D 17
	r = &tp_ref[tp_maxrefopen];

	while( tp_maxrefopen > 0 ) {
		if(r->tpr_state )
E 17
I 17
	for (r = tp_ref + tp_refinfo.tpr_maxopen; r > tp_ref; r--)
		if (r->tpr_pcb)
E 17
			break;
D 17
		tp_maxrefopen--;
		r--;
	}
E 17
I 17
	tp_refinfo.tpr_maxopen = r - tp_ref;
	tp_refinfo.tpr_numopen--;

E 17
	IFDEBUG(D_TIMER)
D 17
		printf("tp_freeref ends w/ maxrefopen %d\n", tp_maxrefopen);
E 17
I 17
		printf("tp_freeref ends w/ maxrefopen %d\n", tp_refinfo.tpr_maxopen);
E 17
	ENDDEBUG
}

/*
 * NAME:  tp_getref()
 *
 * CALLED FROM:
 *  tp_attach()
 *
 * FUNCTION and ARGUMENTS:
 *  obtains the next free reference and allocates the appropriate
 *  ref structure, links that structure to (tpcb) 
 *
 * RETURN VALUE:
 *	a reference number
 *  or TP_ENOREF
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 */
D 17
static RefNum
E 17
I 17
D 18
RefNum
E 18
I 18
u_long
E 18
E 17
tp_getref(tpcb) 
	register struct tp_pcb *tpcb;
{
D 9
	register struct tp_ref	*r = tp_ref; 
E 9
I 9
D 17
	register struct tp_ref	*r = tp_ref; /* tp_ref[0] is never used */
E 9
	register int 			i=1;
E 17
I 17
	register struct tp_ref	*r, *rlim;
	register int 			i;
	caddr_t obase;
	unsigned size;
E 17

I 17
	if (++tp_refinfo.tpr_numopen < tp_refinfo.tpr_size)
		for (r = tp_refinfo.tpr_base, rlim = r + tp_refinfo.tpr_size;
								++r < rlim; ) 	/* tp_ref[0] is never used */
			if (r->tpr_pcb == 0)
				goto got_one;
	/* else have to allocate more space */
E 17
D 9
	r++; /* tp_ref[0] is never used */
E 9

D 9
	/* REF_FREE is zero */
	while( r->tpr_state ) {
		r++; 
		if ( i == N_TPREF ) {
E 9
I 9
D 17
	while ((++r)->tpr_state != REF_FREE) {
		if (++i == N_TPREF)
E 9
			return TP_ENOREF;
D 9
		}
		i++;
E 9
	}
	r->tpr_state = REF_OPENING;
	if (tp_maxrefopen < i) 
		tp_maxrefopen = i;
E 17
I 17
	obase = (caddr_t)tp_refinfo.tpr_base;
	size = tp_refinfo.tpr_size * sizeof(struct tp_ref);
	r = (struct tp_ref *) malloc(size + size, M_PCB, M_NOWAIT);
	if (r == 0)
		return (--tp_refinfo.tpr_numopen, TP_ENOREF);
	tp_refinfo.tpr_base = tp_ref = r;
	tp_refinfo.tpr_size *= 2;
	bcopy(obase, (caddr_t)r, size);
	free(obase, M_PCB);
	r = (struct tp_ref *)(size + (caddr_t)r);
	bzero((caddr_t)r, size);

got_one:
E 17
	r->tpr_pcb = tpcb;
I 17
D 19
	r->tpr_state = REF_OPENING;
E 17
	tpcb->tp_refp = r;
E 19
I 19
	tpcb->tp_refstate = REF_OPENING;
E 19
D 17

E 17
I 17
	i = r - tp_refinfo.tpr_base;
	if (tp_refinfo.tpr_maxopen < i) 
		tp_refinfo.tpr_maxopen = i;
E 17
D 19
	return i;
E 19
I 19
	return (u_long)i;
E 19
}

/*
I 14
 * NAME: tp_set_npcb()
 *
 * CALLED FROM:
 *	tp_attach(), tp_route_to()
 *
 * FUNCTION and ARGUMENTS:
 *  given a tpcb, allocate an appropriate lower-lever npcb, freeing
 *  any old ones that might need re-assigning.
 */
tp_set_npcb(tpcb)
register struct tp_pcb *tpcb;
{
	register struct socket *so = tpcb->tp_sock;
	int error;

	if (tpcb->tp_nlproto && tpcb->tp_npcb) {
		short so_state = so->so_state;
		so->so_state &= ~SS_NOFDREF;
		tpcb->tp_nlproto->nlp_pcbdetach(tpcb->tp_npcb);
		so->so_state = so_state;
	}
	tpcb->tp_nlproto = &nl_protosw[tpcb->tp_netservice];
	/* xx_pcballoc sets so_pcb */
	error = tpcb->tp_nlproto->nlp_pcballoc(so, tpcb->tp_nlproto->nlp_pcblist);
	tpcb->tp_npcb = so->so_pcb;
	so->so_pcb = (caddr_t)tpcb;
	return (error);
}
/*
E 14
 * NAME: tp_attach()
 *
 * CALLED FROM:
 *	tp_usrreq, PRU_ATTACH
 *
 * FUNCTION and ARGUMENTS:
 *  given a socket (so) and a protocol family (dom), allocate a tpcb
 *  and ref structure, initialize everything in the structures that
 *  needs to be initialized.
 *
 * RETURN VALUE:
 *  0 ok
 *  EINVAL if DEBUG(X) in is on and a disaster has occurred
 *  ENOPROTOOPT if TP hasn't been configured or if the
 *   socket wasn't created with tp as its protocol
 *  EISCONN if this socket is already part of a connection
 *  ETOOMANYREFS if ran out of tp reference numbers.
 *  E* whatever error is returned from soreserve()
 *    for from the network-layer pcb allocation routine
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 */
D 2
int
tp_attach(so,dom)
E 2
I 2
D 14
tp_attach(so, dom)
E 2
	struct socket 	*so;
	int 			dom;
E 14
I 14
tp_attach(so, protocol)
	struct socket 			*so;
	int 					protocol;
E 14
{
	register struct tp_pcb	*tpcb;
D 2
	register struct mbuf 	*m;
	register struct mbuf	*p;
E 2
D 21
	int 					error;
E 21
I 21
	int 					error = 0;
E 21
D 14
	int 					protocol = so->so_proto->pr_protocol;
E 14
I 14
	int 					dom = so->so_proto->pr_domain->dom_family;
I 18
	u_long					lref;
E 18
E 14
	extern struct tp_conn_param tp_conn_param[];

	IFDEBUG(D_CONN)
		printf("tp_attach:dom 0x%x so 0x%x ", dom, so);
	ENDDEBUG
	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "tp_attach:dom so", dom, so, 0, 0);
	ENDTRACE
D 20
	if ( ! tp_param.tpp_configed ) {
		error = ENOPROTOOPT; /* protocol not available */
		goto bad2;
	}
E 20

	if (so->so_pcb != NULL) { 
		return EISCONN;	/* socket already part of a connection*/
	}

D 17
	error = soreserve(so, TP_SOCKBUFSIZE, TP_SOCKBUFSIZE);
E 17
I 17
D 21
	error = soreserve(so, 2 * TP_SOCKBUFSIZE, TP_SOCKBUFSIZE);
E 21
I 21
	if (so->so_snd.sb_hiwat == 0 || so->so_rcv.sb_hiwat == 0)
D 22
		error = soreserve(so, tp_sendsize, tp_recvsize);
E 22
I 22
		error = soreserve(so, tp_sendspace, tp_recvspace);
E 22
E 21
E 17
		/* later an ioctl will allow reallocation IF still in closed state */

	if (error)
		goto bad2;

D 2
	MGET(m, M_DONTWAIT, TPMT_PCB);	/* for tpcb, main half */
	if (m == NULL) {
E 2
I 2
	MALLOC(tpcb, struct tp_pcb *, sizeof(*tpcb), M_PCB, M_NOWAIT);
	if (tpcb == NULL) {
E 2
		error = ENOBUFS;
		goto bad2;
	}
D 2

	tpcb = mtod( m, struct tp_pcb * );
E 2
	bzero( (caddr_t)tpcb, sizeof (struct tp_pcb) );

D 2
	MGET(p, M_DONTWAIT, TPMT_PCB);	/* for the tpcb, auxilliary half */
	if (p == NULL) {
		error = ENOBUFS;
		m_free(m); /* which is tpcb */
		goto bad2;
	} else {
		p->m_len = sizeof(struct tp_pcb_aux);
		p->m_act = MNULL;
		tpcb->tp_aux = mtod(p, struct tp_pcb_aux *);
		bzero( (caddr_t)tpcb->tp_aux, sizeof (struct tp_pcb_aux) );
	}

E 2
D 18
	if ( ((tpcb->tp_lref = tp_getref(tpcb)) &  TP_ENOREF) != 0 ) { 
E 18
I 18
	if ( ((lref = tp_getref(tpcb)) &  TP_ENOREF) != 0 ) { 
E 18
		error = ETOOMANYREFS; 
		goto bad3;
	}
I 18
	tpcb->tp_lref = lref;
E 18
	tpcb->tp_sock =  so;
	tpcb->tp_domain = dom;
I 24
	tpcb->tp_rhiwat = so->so_rcv.sb_hiwat;
E 24
D 14
	if (protocol<ISOPROTO_TP4) {
E 14
I 14
	/* tpcb->tp_proto = protocol; someday maybe? */
	if (protocol && protocol<ISOPROTO_TP4) {
E 14
		tpcb->tp_netservice = ISO_CONS;
		tpcb->tp_snduna = (SeqNum) -1;/* kludge so the pseudo-ack from the CR/CC
								 * will generate correct fake-ack values
								 */
	} else {
		tpcb->tp_netservice = (dom== AF_INET)?IN_CLNS:ISO_CLNS;
		/* the default */
	}
	tpcb->_tp_param = tp_conn_param[tpcb->tp_netservice];

D 18
	tpcb->tp_cong_win = 1;	
E 18
	tpcb->tp_state = TP_CLOSED;
	tpcb->tp_vers  = TP_VERSION;
I 16
	tpcb->tp_notdetached = 1;
E 16

		   /* Spec says default is 128 octets,
			* that is, if the tpdusize argument never appears, use 128.
			* As the initiator, we will always "propose" the 2048
			* size, that is, we will put this argument in the CR 
			* always, but accept what the other side sends on the CC.
			* If the initiator sends us something larger on a CR,
			* we'll respond w/ this.
			* Our maximum is 4096.  See tp_chksum.c comments.
			*/
D 18
	tpcb->tp_l_tpdusize = 1 << tpcb->tp_tpdusize;
E 18
I 18
	tpcb->tp_cong_win = 
		tpcb->tp_l_tpdusize = 1 << tpcb->tp_tpdusize;
E 18

	tpcb->tp_seqmask  = TP_NML_FMT_MASK;
	tpcb->tp_seqbit  =  TP_NML_FMT_BIT;
	tpcb->tp_seqhalf  =  tpcb->tp_seqbit >> 1;
D 18
	tpcb->tp_sndhiwat = (SeqNum) - 1; /* a kludge but it works */
	tpcb->tp_s_subseq = 0;
E 18

	/* attach to a network-layer protoswitch */
D 14
	/* new way */
	tpcb->tp_nlproto = & nl_protosw[tpcb->tp_netservice];
E 14
I 14
	if ( error =  tp_set_npcb(tpcb))
		goto bad4;
E 14
	ASSERT( tpcb->tp_nlproto->nlp_afamily == tpcb->tp_domain);
D 14
#ifdef notdef
	/* OLD WAY */
	/* TODO: properly, this search would be on the basis of 
	* domain,netservice or just netservice only (if you have
	* IN_CLNS, ISO_CLNS, and ISO_CONS)
	*/
	tpcb->tp_nlproto = nl_protosw;
	while(tpcb->tp_nlproto->nlp_afamily != tpcb->tp_domain )  {
		if( tpcb->tp_nlproto->nlp_afamily == 0 ) {
			error = EAFNOSUPPORT;
			goto bad4;
		}
		tpcb->tp_nlproto ++;
	}
#endif notdef
E 14

D 14
	/* xx_pcballoc sets so_pcb */
	if ( error =  (tpcb->tp_nlproto->nlp_pcballoc) ( 
							so, tpcb->tp_nlproto->nlp_pcblist ) ) {
		goto bad4;
	}

E 14
I 14
	/* nothing to do for iso case */
E 14
	if( dom == AF_INET )
		sotoinpcb(so)->inp_ppcb = (caddr_t) tpcb;
D 14
		/* nothing to do for iso case */
E 14

D 12
	tpcb->tp_npcb = (caddr_t) so->so_pcb;
	so->so_tpcb = (caddr_t) tpcb;
E 12
I 12
D 14
	tpcb->tp_npcb = so->so_pcb;
	so->so_pcb = (caddr_t) tpcb;
E 12

E 14
	return 0;

bad4:
	IFDEBUG(D_CONN)
		printf("BAD4 in tp_attach, so 0x%x\n", so);
	ENDDEBUG
D 19
	tp_freeref(tpcb->tp_refp);
E 19
I 19
	tp_freeref(tpcb->tp_lref);
E 19

bad3:
	IFDEBUG(D_CONN)
		printf("BAD3 in tp_attach, so 0x%x\n", so);
	ENDDEBUG

D 2
	m_free(dtom(tpcb)); /* never a cluster  */
	m_free(dtom(tpcb->tp_aux)); /* never a cluster */
E 2
I 2
	free((caddr_t)tpcb, M_PCB); /* never a cluster  */
E 2

bad2:
	IFDEBUG(D_CONN)
		printf("BAD2 in tp_attach, so 0x%x\n", so);
	ENDDEBUG
	so->so_pcb = 0;
D 12
	so->so_tpcb = 0;
E 12
D 8
	sofree(so);
E 8

D 2
bad:
E 2
I 2
/*bad:*/
E 2
	IFDEBUG(D_CONN)
		printf("BAD in tp_attach, so 0x%x\n", so);
	ENDDEBUG
	return error;
}

/*
 * NAME:  tp_detach()
 *
 * CALLED FROM:
 *	tp.trans, on behalf of a user close request
 *  and when the reference timer goes off
 * (if the disconnect  was initiated by the protocol entity 
 * rather than by the user)
 *
 * FUNCTION and ARGUMENTS:
 *  remove the tpcb structure from the list of active or
 *  partially active connections, recycle all the mbufs
 *  associated with the pcb, ref structure, sockbufs, etc.
 *  Only free the ref structure if you know that a ref timer
 *  wasn't set for this tpcb.
 *
 * RETURNS:  Nada
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 *  tp_soisdisconnected() was already when this is called
 */
void
tp_detach(tpcb)
	register struct tp_pcb 	*tpcb;
{
D 15
	void					tp_freeref();
E 15
I 15
	void					tp_freeref(), tp_rsyflush();
E 15
	register struct socket	 *so = tpcb->tp_sock;

	IFDEBUG(D_CONN)
D 2
		printf("tp_detach(tpcb 0x%x, so 0x%x) freelist 0%x\n",
			tpcb,so, mfree);
E 2
I 2
		printf("tp_detach(tpcb 0x%x, so 0x%x)\n",
			tpcb,so);
E 2
	ENDDEBUG
	IFTRACE(D_CONN)
		tptraceTPCB(TPPTmisc, "tp_detach tpcb so lsufx", 
D 4
			tpcb, so, *(int *)(tpcb->tp_lsuffix), 0);
E 4
I 4
			tpcb, so, *(u_short *)(tpcb->tp_lsuffix), 0);
E 4
	ENDTRACE

D 14
	if (so->so_head) {
		if (!soqremque(so, 0) && !soqremque(so, 1))
			panic("sofree dq");
		so->so_head = 0;
	}

E 14
	IFDEBUG(D_CONN)
D 15
		printf("tp_detach(freeing RTC list snduna 0x%x rcvnxt 0x%x)\n",
		tpcb->tp_snduna_rtc,
		tpcb->tp_rcvnxt_rtc);
	ENDDEBUG

#define FREE_RTC_LIST(XXX)\
	{ register struct tp_rtc *xxr = XXX, *xxs; while (xxr) {\
		xxs = xxr->tprt_next;\
		m_freem( xxr->tprt_data );\
		m_free( dtom(xxr) ); xxr = xxs; }\
		XXX = (struct tp_rtc *)0;\
	}

	FREE_RTC_LIST( tpcb->tp_snduna_rtc );
	tpcb->tp_sndhiwat_rtc = (struct tp_rtc *)0;

	FREE_RTC_LIST( tpcb->tp_rcvnxt_rtc );

#undef FREE_RTC_LIST

	IFDEBUG(D_CONN)
E 15
I 8
		printf("so_snd at 0x%x so_rcv at 0x%x\n", &so->so_snd, &so->so_rcv);
		dump_mbuf(so->so_snd.sb_mb, "so_snd at detach ");
		printf("about to call LL detach, nlproto 0x%x, nl_detach 0x%x\n",
				tpcb->tp_nlproto, tpcb->tp_nlproto->nlp_pcbdetach);
	ENDDEBUG

D 14
	if (so->so_snd.sb_cc != 0)
		sbflush(&so->so_snd);
	if (tpcb->tp_Xrcv.sb_cc != 0)
		sbdrop(&tpcb->tp_Xrcv, (int)tpcb->tp_Xrcv.sb_cc);
E 14
I 14
	if (tpcb->tp_Xsnd.sb_mb) {
		printf("Unsent Xdata on detach; would panic");
		sbflush(&tpcb->tp_Xsnd);
	}
E 14
	if (tpcb->tp_ucddata)
		m_freem(tpcb->tp_ucddata);

	IFDEBUG(D_CONN)
I 15
		printf("reassembly info cnt %d rsyq 0x%x\n",
		    tpcb->tp_rsycnt, tpcb->tp_rsyq);
	ENDDEBUG
	if (tpcb->tp_rsyq)
		tp_rsyflush(tpcb);

I 16
	if (tpcb->tp_next) {
		remque(tpcb);
		tpcb->tp_next = tpcb->tp_prev = 0;
	}
	tpcb->tp_notdetached = 0;

E 16
	IFDEBUG(D_CONN)
E 15
E 8
		printf("calling (...nlproto->...)(0x%x, so 0x%x)\n", 
D 12
			so->so_pcb, so);
E 12
I 12
			tpcb->tp_npcb, so);
E 12
		printf("so 0x%x so_head 0x%x,  qlen %d q0len %d qlimit %d\n", 
		so,  so->so_head,
		so->so_q0len, so->so_qlen, so->so_qlimit);
	ENDDEBUG
D 15

E 15
D 2
	if ( tpcb->tp_flags & (TPF_CONN_DATA_OUT | TPF_DISC_DATA_OUT ) ) {
E 2
I 2
D 8
	if ( tpcb->tp_flags & (TPF_DISC_DATA_OUT | TPF_CONN_DATA_OUT ) )  {
E 2
		ASSERT( so->so_snd.sb_cc != 0 );
		IFDEBUG(D_CONN)
			printf(
			"detach, flags 0x%x doing sbdrop on so_snd, mb 0x%x cc 0x%x\n", 
				tpcb->tp_flags, so->so_snd.sb_mb, so->so_snd.sb_cc);
			dump_mbuf( so->so_snd.sb_mb, "detach so snd: \n");
		ENDDEBUG
		if ( so->so_snd.sb_cc != 0 )
D 2
			sbdrop( &so->so_snd, so->so_snd.sb_cc);
E 2
I 2
			sbflush(&so->so_snd);
E 2
		tpcb->tp_flags &= ~(TPF_CONN_DATA_OUT | TPF_DISC_DATA_OUT); 
	}
	if ( tpcb->tp_flags & (TPF_DISC_DATA_IN | TPF_CONN_DATA_IN ) ) {
		ASSERT( tpcb->tp_Xrcv.sb_cc != 0 );
		IFDEBUG(D_CONN)
			printf(
			"detach, flags 0x%x doing sbdrop on tp_Xrcv, mb 0x%x cc 0x%x\n", 
				tpcb->tp_flags, tpcb->tp_Xrcv.sb_mb, tpcb->tp_Xrcv.sb_cc);
			dump_mbuf( tpcb->tp_Xrcv.sb_mb, "detach Xrcv: \n");
		ENDDEBUG
		if( tpcb->tp_Xrcv.sb_cc != 0 )
D 2
			sbdrop( &tpcb->tp_Xrcv, tpcb->tp_Xrcv.sb_cc);
E 2
I 2
			sbdrop(&tpcb->tp_Xrcv, (int)tpcb->tp_Xrcv.sb_cc);
E 2
		tpcb->tp_flags &= ~(TPF_CONN_DATA_IN | TPF_DISC_DATA_IN); 
	}
E 8

D 8
	IFDEBUG(D_CONN)
		printf("so_snd at 0x%x so_rcv at 0x%x\n", &so->so_snd, &so->so_rcv);
		dump_mbuf(so->so_snd.sb_mb, "so_snd at detach ");
		printf("about to call LL detach, nlproto 0x%x, nl_detach 0x%x\n",
				tpcb->tp_nlproto, tpcb->tp_nlproto->nlp_pcbdetach);
	ENDDEBUG

D 2
	if ((tpcb->tp_nlproto->nlp_pcbdetach) (
				(struct inpcb *)so->so_pcb) /* does an sofree(so) */ < 0 ) {
#ifdef 	ARGO_DEBUG
		printf("tp: nl_detach failed: tpcb 0x%x so 0x%x\n", tpcb, so);
#endif 	ARGO_DEBUG
	}
E 2
		
I 2
		
	(tpcb->tp_nlproto->nlp_pcbdetach)((struct inpcb *)so->so_pcb);
E 8
I 8
D 12
	(tpcb->tp_nlproto->nlp_pcbdetach)(so->so_pcb);
E 12
I 12
	(tpcb->tp_nlproto->nlp_pcbdetach)(tpcb->tp_npcb);
E 12
E 8
D 14
				/* does an sofree(so) */
E 14
I 14
				/* does an so->so_pcb = 0; sofree(so) */
E 14

E 2
	IFDEBUG(D_CONN)
		printf("after xxx_pcbdetach\n");
	ENDDEBUG

I 16
	if (tpcb->tp_state == TP_LISTENING) {
		register struct tp_pcb **tt;
		for (tt = &tp_listeners; *tt; tt = &((*tt)->tp_nextlisten))
			if (*tt == tpcb)
				break;
		if (*tt)
			*tt = tpcb->tp_nextlisten;
		else
			printf("tp_detach from listen: should panic\n");
	}
E 16
D 17
	if( tpcb->tp_refp->tpr_state == REF_OPENING ) {
E 17
I 17
D 19
	if (tpcb->tp_refp && tpcb->tp_refp->tpr_state == REF_OPENING ) {
E 19
I 19
	if (tpcb->tp_refstate == REF_OPENING ) {
E 19
E 17
		/* no connection existed here so no reference timer will be called */
		IFDEBUG(D_CONN)
D 19
			printf("SETTING ref %d, 0x%x to REF_FREE\n", tpcb->tp_lref,
			tpcb->tp_refp - &tp_ref[0]);
E 19
I 19
			printf("SETTING ref %d to REF_FREE\n", tpcb->tp_lref);
E 19
		ENDDEBUG

D 19
		tp_freeref(tpcb->tp_refp);
E 19
I 19
		tp_freeref(tpcb->tp_lref);
E 19
	}
D 14

I 2
	if (tpcb->tp_Xsnd.sb_mb) {
		printf("Unsent Xdata on detach; would panic");
		sbflush(&tpcb->tp_Xsnd);
	}
E 2
D 12
	so->so_tpcb = (caddr_t)0;
E 12
I 12
	so->so_pcb = 0;
E 12

E 14
I 14
#ifdef TP_PERF_MEAS
E 14
	/* 
	 * Get rid of the cluster mbuf allocated for performance measurements, if
	 * there is one.  Note that tpcb->tp_perf_on says nothing about whether or 
	 * not a cluster mbuf was allocated, so you have to check for a pointer 
	 * to one (that is, we need the TP_PERF_MEASs around the following section 
	 * of code, not the IFPERFs)
	 */
D 14
#ifdef TP_PERF_MEAS
E 14
D 2
	if( tpcb->tp_p_meas != (struct tp_pmeas *)0 ) {
		register struct mbuf *n;

		n = MTOCL((struct mbuf *)(tpcb->tp_p_meas));
E 2
I 2
D 8
	if(tpcb->tp_p_mbuf) {
E 8
I 8
	if (tpcb->tp_p_mbuf) {
E 8
		register struct mbuf *m = tpcb->tp_p_mbuf;
		struct mbuf *n;
E 2
		IFDEBUG(D_PERF_MEAS)
			printf("freeing tp_p_meas 0x%x  ", tpcb->tp_p_meas);
D 2
			printf("n = 0x%x\n", n);
E 2
		ENDDEBUG
D 2
		if (--mclrefcnt[mtocl(n)] == 0) { 
			n->m_next = mclfree;
			mclfree = n;
			mbstat.m_clfree++;
		} 
E 2
I 2
		do {
		    MFREE(m, n);
		    m = n;
		} while (n);
		tpcb->tp_p_meas = 0;
		tpcb->tp_p_mbuf = 0;
E 2
	}
D 26
#endif TP_PERF_MEAS
E 26
I 26
#endif /* TP_PERF_MEAS */
E 26

	IFDEBUG(D_CONN)
D 2
		printf(
"end of detach, NOT single, tpcb 0x%x, dtom(tpcb) 0x%x tp_aux 0x%x dtom(aux) 0x%x\n",
		 tpcb, dtom(tpcb), tpcb->tp_aux, dtom(tpcb->tp_aux));
E 2
I 2
		printf( "end of detach, NOT single, tpcb 0x%x\n", tpcb);
E 2
	ENDDEBUG
D 2
	m_free(dtom(tpcb->tp_aux)); 
	m_free(dtom(tpcb)); 
E 2
I 2
	/* free((caddr_t)tpcb, M_PCB); WHere to put this ? */
E 2
}
I 13

struct que {
	struct tp_pcb *next;
	struct tp_pcb *prev;
} tp_bound_pcbs =
{(struct tp_pcb *)&tp_bound_pcbs, (struct tp_pcb *)&tp_bound_pcbs};

u_short tp_unique;

tp_tselinuse(tlen, tsel, siso, reuseaddr)
caddr_t tsel;
register struct sockaddr_iso *siso;
{
	struct tp_pcb *b = tp_bound_pcbs.next, *l = tp_listeners;
	register struct tp_pcb *t;

	for (;;) {
		if (b != (struct tp_pcb *)&tp_bound_pcbs) {
			t = b; b = t->tp_next;
		} else if (l) {
			t = l; l = t->tp_nextlisten;
		} else
			break;
		if (tlen == t->tp_lsuffixlen && bcmp(tsel, t->tp_lsuffix, tlen) == 0) {
			if (t->tp_flags & TPF_GENERAL_ADDR) {
				if (siso == 0 || reuseaddr == 0)
					return 1;
			} else if (siso) {
				if (siso->siso_family == t->tp_domain &&
					t->tp_nlproto->nlp_cmpnetaddr(t->tp_npcb, siso, TP_LOCAL))
						return 1;
			} else if (reuseaddr == 0)
						return 1;
		}
	}
	return 0;

}


tp_pcbbind(tpcb, nam)
register struct tp_pcb *tpcb;
register struct mbuf *nam;
{
	register struct sockaddr_iso *siso = 0;
	int tlen = 0, wrapped = 0;
	caddr_t tsel;
	u_short tutil;

	if (tpcb->tp_state != TP_CLOSED)
		return (EINVAL);
	if (nam) {
		siso = mtod(nam, struct sockaddr_iso *);
		switch (siso->siso_family) {
		default:
			return (EAFNOSUPPORT);
#ifdef ISO
		case AF_ISO:
			tlen = siso->siso_tlen;
			tsel = TSEL(siso);
			if (siso->siso_nlen == 0)
				siso = 0;
			break;
#endif
#ifdef INET
		case AF_INET:
			tsel = (caddr_t)&tutil;
			if (tutil =  ((struct sockaddr_in *)siso)->sin_port) {
				tlen = 2;
			}
			if (((struct sockaddr_in *)siso)->sin_addr.s_addr == 0)
				siso = 0;
		}
#endif
	}
	if (tpcb->tp_lsuffixlen == 0) {
		if (tlen) {
D 14
			if (tp_tselinuse(tsel, tlen, siso,
E 14
I 14
			if (tp_tselinuse(tlen, tsel, siso,
E 14
								tpcb->tp_sock->so_options & SO_REUSEADDR))
				return (EINVAL);
D 23
		} else for (tsel = (caddr_t)&tp_unique, tlen = 2;;){
			if (tp_unique++ < ISO_PORT_RESERVED ||
				tp_unique > ISO_PORT_USERRESERVED) {
					if (wrapped++)
						return ESRCH;
					tp_unique = ISO_PORT_RESERVED;
E 23
I 23
		} else {
			for (tsel = (caddr_t)&tutil, tlen = 2;;){
				if (tp_unique++ < ISO_PORT_RESERVED ||
					tp_unique > ISO_PORT_USERRESERVED) {
						if (wrapped++)
							return ESRCH;
						tp_unique = ISO_PORT_RESERVED;
				}
				tutil = htons(tp_unique);
				if (tp_tselinuse(tlen, tsel, siso, 0) == 0)
					break;
E 23
			}
D 14
			if (tp_tselinuse(tsel, tlen, siso, 0) == 0)
E 14
I 14
D 23
			if (tp_tselinuse(tlen, tsel, siso, 0) == 0)
E 14
				break;
E 23
I 23
			if (siso) switch (siso->siso_family) {
#ifdef ISO
				case AF_ISO:
					bcopy(tsel, TSEL(siso), tlen);
					siso->siso_tlen = tlen;
					break;
#endif
#ifdef INET
				case AF_INET:
					((struct sockaddr_in *)siso)->sin_port = tutil;
#endif
				}
E 23
		}
		bcopy(tsel, tpcb->tp_lsuffix, (tpcb->tp_lsuffixlen = tlen));
		insque(tpcb, &tp_bound_pcbs);
	} else {
		if (tlen || siso == 0)
			return (EINVAL);
	}
	if (siso == 0) {
		tpcb->tp_flags |= TPF_GENERAL_ADDR;
		return (0);
	}
	return tpcb->tp_nlproto->nlp_pcbbind(tpcb->tp_npcb, nam);
}
E 13
E 1
