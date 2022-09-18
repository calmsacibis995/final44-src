h43724
s 00001/00001/00685
d D 8.2 95/02/09 10:45:00 cgd 20 19
c don't check for <0 on unsigneds.  (kill comp. warning.)
e
s 00002/00002/00684
d D 8.1 93/06/10 23:20:40 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00683
d D 7.18 93/05/25 11:51:58 bostic 18 17
c trailing comment after #else or #endif
e
s 00019/00018/00667
d D 7.17 92/10/11 12:22:04 bostic 17 16
c make kernel includes standard
e
s 00010/00002/00675
d D 7.16 92/05/27 16:16:26 sklower 16 15
c 1.) fix bug re:double freeing option mbuf in error case in ctlout;
c 2.) if you are increasing so_rcv buff size, may want to open window
e
s 00013/00003/00664
d D 7.15 91/12/17 16:19:33 sklower 15 14
c big-or-odd-size packet option. (n x 128 instead of 2^n only)
e
s 00001/00013/00666
d D 7.14 91/10/02 21:43:42 sklower 14 13
c interim version of tp_consistency before putting in ``big packets''
e
s 00019/00011/00660
d D 7.13 91/09/03 21:19:00 sklower 13 12
c upper level protocols now call when setting socket level options
e
s 00035/00039/00636
d D 7.12 91/07/29 14:55:29 sklower 12 11
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00001/00001/00674
d D 7.11 91/07/18 20:33:25 sklower 11 10
c this changes reflect getting rid of so_tpcb.
e
s 00004/00004/00671
d D 7.10 91/06/27 22:06:14 sklower 10 9
c minor changes to compile under both new and old vm systems
e
s 00009/00005/00666
d D 7.9 91/05/06 19:24:28 bostic 9 8
c new copyright; att/bsd/shared
e
s 00009/00004/00662
d D 7.8 91/03/12 16:04:19 sklower 8 7
c fixes from mostek@cray
e
s 00001/00001/00665
d D 7.7 90/06/29 11:14:49 sklower 7 6
c fix minor bugs in setting up cross-list of listeners, intercepters, and their descendents
e
s 00049/00003/00617
d D 7.6 90/06/28 19:40:14 sklower 6 5
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00005/00031/00615
d D 7.5 90/02/27 13:29:17 sklower 5 4
c fix bug preventing sending of user-confirm-data
e
s 00023/00003/00623
d D 7.4 89/08/29 13:45:20 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00002/00002/00624
d D 7.3 89/04/25 17:19:51 mckusick 3 2
c ../h => (implicitly) ../sys
e
s 00040/00072/00586
d D 7.2 89/04/22 11:55:13 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00658/00000/00000
d D 7.1 88/12/14 15:30:06 sklower 1 0
c date and time created 88/12/14 15:30:06 by sklower
e
u
U
t
T
I 9
/*-
D 19
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 9
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
 * $Header: tp_output.c,v 5.4 88/11/18 17:28:08 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_output.c,v $
I 4
D 9
 *	%W% (Berkeley) %G% *
E 9
E 4
 *
 * In here is tp_ctloutput(), the guy called by [sg]etsockopt(),
 */
D 9

#ifndef lint
static char *rcsid = "$Header: tp_output.c,v 5.4 88/11/18 17:28:08 nhall Exp $";
#endif lint
E 9

D 17
#include "param.h"
D 6
#include "systm.h"
E 6
#include "mbuf.h"
D 6
#include "protosw.h"
E 6
I 6
#include "systm.h"
E 6
#include "socket.h"
#include "socketvar.h"
I 6
#include "protosw.h"
D 10
#include "user.h"
#include "kernel.h"
E 10
E 6
#include "errno.h"
D 6
#include "types.h"
E 6
#include "time.h"
D 2
#include "../netiso/tp_param.h"
#include "../netiso/tp_user.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_ip.h"
#include "../netiso/tp_timer.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_trace.h"
E 2
I 2
#include "tp_param.h"
#include "tp_user.h"
#include "tp_stat.h"
#include "tp_ip.h"
I 6
#include "tp_clnp.h"
E 6
#include "tp_timer.h"
#include "argo_debug.h"
#include "tp_pcb.h"
#include "tp_trace.h"
I 10
#include "kernel.h"
E 17
I 17
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/systm.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <netiso/tp_param.h>
#include <netiso/tp_user.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_ip.h>
#include <netiso/tp_clnp.h>
#include <netiso/tp_timer.h>
#include <netiso/argo_debug.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_trace.h>
E 17
E 10
E 2

D 12
#define USERFLAGSMASK_G 0x0f00643b
#define USERFLAGSMASK_S 0x0f000432
E 12
#define TPDUSIZESHIFT 24
#define CLASSHIFT 16

/*
 * NAME: 	tp_consistency()
 *
 * CALLED FROM:
 * 	tp_ctloutput(), tp_input()
 *
 * FUNCTION and ARGUMENTS:
 * 	Checks the consistency of options and tpdusize with class,
 *	using the parameters passed in via (param).
 *	(cmd) may be TP_STRICT or TP_FORCE or both.
 *  Force means it will set all the values in (tpcb) to those in
 *  the input arguements iff no errors were encountered.
 *  Strict means that no inconsistency will be tolerated.  If it's
 *  not used, checksum and tpdusize inconsistencies will be tolerated.
 *  The reason for this is that in some cases, when we're negotiating down 
 *	from class  4, these options should be changed but should not 
 *  cause negotiation to fail.
 *
 * RETURNS
 *  E* or EOK
 *  E* if the various parms aren't ok for a given class
 *  EOK if they are ok for a given class
 */

int
tp_consistency( tpcb, cmd, param )
	u_int cmd;
	struct tp_conn_param *param;
	struct tp_pcb *tpcb;
{
	register int	error = EOK;
	int 			class_to_use  = tp_mask_to_num(param->p_class);

	IFTRACE(D_SETPARAMS)
		tptrace(TPPTmisc, 
		"tp_consist enter class_to_use dontchange param.class cmd", 
		class_to_use, param->p_dont_change_params, param->p_class, cmd);
	ENDTRACE
	IFDEBUG(D_SETPARAMS)
		printf("tp_consistency %s %s\n", 
			cmd& TP_FORCE?	"TP_FORCE":	"",
			cmd& TP_STRICT?	"TP_STRICT":"");
	ENDDEBUG
	if ((cmd & TP_FORCE) && (param->p_dont_change_params)) {
		cmd &= ~TP_FORCE;
	}
	/* can switch net services within a domain, but
	 * cannot switch domains 
	 */
	switch( param->p_netservice) {
	case ISO_CONS:
	case ISO_CLNS:
	case ISO_COSNS:
		/* param->p_netservice in ISO DOMAIN */
		if(tpcb->tp_domain != AF_ISO ) {
			error = EINVAL; goto done;
		}
		break;
	case IN_CLNS:
		/* param->p_netservice in INET DOMAIN */
		if( tpcb->tp_domain != AF_INET ) {
			error = EINVAL; goto done;
		}
		break;
		/* no others not possible-> netservice is a 2-bit field! */
	}

	IFDEBUG(D_SETPARAMS)
		printf("p_class 0x%x, class_to_use 0x%x\n",  param->p_class,
			class_to_use);
	ENDDEBUG
D 20
	if((param->p_netservice < 0) || (param->p_netservice > TP_MAX_NETSERVICES)){
E 20
I 20
	if(param->p_netservice > TP_MAX_NETSERVICES){
E 20
		error = EINVAL; goto done;
	}
	if( (param->p_class & TP_CLASSES_IMPLEMENTED) == 0 ) {
		error = EINVAL; goto done;
	} 
	IFDEBUG(D_SETPARAMS)
		printf("Nretrans 0x%x\n",  param->p_Nretrans );
	ENDDEBUG
	if( ( param->p_Nretrans < 1 ) ||
		  (param->p_cr_ticks < 1) || (param->p_cc_ticks < 1) ) {
			/* bad for any class because negot has to be done a la class 4 */
			error = EINVAL; goto done;
	}
	IFDEBUG(D_SETPARAMS)
D 14
		printf("winsize 0x%x\n",  param->p_winsize );
	ENDDEBUG
	if( (param->p_winsize < 128 ) || 
		(param->p_winsize < param->p_tpdusize ) ||
		(param->p_winsize > ((1+SB_MAX)>>2 /* 1/4 of the max */)) ) {
			error = EINVAL; goto done;
	} else {
		if( tpcb->tp_state == TP_CLOSED )
D 2
			soreserve(tpcb->tp_sock, param->p_winsize, param->p_winsize);
E 2
I 2
			soreserve(tpcb->tp_sock, (u_long)param->p_winsize,
						(u_long)param->p_winsize);
E 2
	}
	IFDEBUG(D_SETPARAMS)
E 14
		printf("use_csum 0x%x\n",  param->p_use_checksum );
		printf("xtd_format 0x%x\n",  param->p_xtd_format );
		printf("xpd_service 0x%x\n",  param->p_xpd_service );
		printf("tpdusize 0x%x\n",  param->p_tpdusize );
		printf("tpcb->flags 0x%x\n",  tpcb->tp_flags );
	ENDDEBUG
	switch( class_to_use ) {

	case 0:
		/* do not use checksums, xtd format, or XPD */

		if( param->p_use_checksum | param->p_xtd_format | param->p_xpd_service ) {
			if(cmd & TP_STRICT) {
				error = EINVAL;
			} else {
				param->p_use_checksum = 0;
				param->p_xtd_format = 0;
				param->p_xpd_service = 0;
			}
			break;
		}

		if (param->p_tpdusize < TP_MIN_TPDUSIZE) {
			if(cmd & TP_STRICT) {
				error = EINVAL;
			} else {
				param->p_tpdusize = TP_MIN_TPDUSIZE;
			}
			break;
		}
		if (param->p_tpdusize > TP0_TPDUSIZE)  {
			if (cmd & TP_STRICT) {
				error = EINVAL; 
			} else {
				param->p_tpdusize = TP0_TPDUSIZE;
			}
			break;
		} 

		/* connect/disc data not allowed for class 0 */
D 2
		if ( tpcb->tp_flags & 
			(TPF_CONN_DATA_OUT | TPF_DISC_DATA_OUT) ) {
E 2
I 2
		if (tpcb->tp_ucddata) {
E 2
			if(cmd & TP_STRICT) {
				error = EINVAL;
			} else if(cmd & TP_FORCE) {
D 2
				sbdrop(&tpcb->tp_sock->so_snd, tpcb->tp_sock->so_snd.sb_cc);
				tpcb->tp_flags &= 
					~(TPF_CONN_DATA_OUT | TPF_DISC_DATA_OUT);
E 2
I 2
				m_freem(tpcb->tp_ucddata);
				tpcb->tp_ucddata = 0;
E 2
			}
		}
		break;
		
	case 4:
		IFDEBUG(D_SETPARAMS)
			printf("dt_ticks 0x%x\n",  param->p_dt_ticks );
			printf("x_ticks 0x%x\n",  param->p_x_ticks );
			printf("dr_ticks 0x%x\n",  param->p_dr_ticks );
			printf("keepalive 0x%x\n",  param->p_keepalive_ticks );
			printf("sendack 0x%x\n",  param->p_sendack_ticks );
			printf("inact 0x%x\n",  param->p_inact_ticks );
			printf("ref 0x%x\n",  param->p_ref_ticks );
		ENDDEBUG
		if( (param->p_class & TP_CLASS_4 ) && (
			  (param->p_dt_ticks < 1) || (param->p_dr_ticks < 1) || 
			  (param->p_x_ticks < 1)	|| (param->p_keepalive_ticks < 1) ||
			  (param->p_sendack_ticks < 1) || (param->p_ref_ticks < 1) ||
			  (param->p_inact_ticks < 1) ) ) {
				error = EINVAL;
				break;
		}
		IFDEBUG(D_SETPARAMS)
			printf("rx_strat 0x%x\n",  param->p_rx_strat );
		ENDDEBUG
		if(param->p_rx_strat > 
			( TPRX_USE_CW | TPRX_EACH | TPRX_FASTSTART) ) {
				if(cmd & TP_STRICT) {
					error = EINVAL;
				} else {
					param->p_rx_strat = TPRX_USE_CW;
				}
				break;
		}
		IFDEBUG(D_SETPARAMS)
			printf("ack_strat 0x%x\n",  param->p_ack_strat );
		ENDDEBUG
		if((param->p_ack_strat != 0) && (param->p_ack_strat != 1)) {
			if(cmd & TP_STRICT) {
				error = EINVAL;
			} else {
				param->p_ack_strat = TPACK_WINDOW;
			}
			break;
		}
		if (param->p_tpdusize < TP_MIN_TPDUSIZE) {
			if(cmd & TP_STRICT) {
				error = EINVAL;
			} else {
				param->p_tpdusize = TP_MIN_TPDUSIZE;
			}
			break;
		}
		if (param->p_tpdusize > TP_TPDUSIZE)  {
			if(cmd & TP_STRICT) {
				error = EINVAL; 
			} else {
				param->p_tpdusize = TP_TPDUSIZE;
			}
			break;
		} 
		break;
	}

	if ((error==0) && (cmd & TP_FORCE)) {
I 15
		long dusize = ((long)param->p_ptpdusize) << 7;
E 15
D 8
		tpcb->tp_tpdusize = param->p_tpdusize;
E 8
I 8
		/* Enforce Negotation rules below */
D 15
		if (tpcb->tp_tpdusize > param->p_tpdusize)
			tpcb->tp_tpdusize = param->p_tpdusize;
E 15
E 8
		tpcb->tp_class = param->p_class;
D 8
		tpcb->tp_use_checksum = param->p_use_checksum;
		tpcb->tp_xpd_service = param->p_xpd_service;
		tpcb->tp_xtd_format = param->p_xtd_format;
E 8
I 8
		if (tpcb->tp_use_checksum || param->p_use_checksum)
			tpcb->tp_use_checksum = 1;
		if (!tpcb->tp_xpd_service || !param->p_xpd_service)
			tpcb->tp_xpd_service = 0;
		if (!tpcb->tp_xtd_format || !param->p_xtd_format)
			tpcb->tp_xtd_format = 0;
I 15
		if (dusize) {
			if (tpcb->tp_l_tpdusize > dusize)
				tpcb->tp_l_tpdusize = dusize;
			if (tpcb->tp_ptpdusize == 0 ||
				tpcb->tp_ptpdusize > param->p_ptpdusize)
				tpcb->tp_ptpdusize = param->p_ptpdusize;
		} else {
			if (param->p_tpdusize != 0 &&
				tpcb->tp_tpdusize > param->p_tpdusize)
				tpcb->tp_tpdusize = param->p_tpdusize;
			tpcb->tp_l_tpdusize = 1 << tpcb->tp_tpdusize;
		}
E 15
E 8
	}
D 14

E 14
I 14
D 15
	tpcb->tp_l_tpdusize = 1 << tpcb->tp_tpdusize;
E 15
E 14
done:

	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "tp_consist returns class xtdfmt cmd", 
			error, tpcb->tp_class, tpcb->tp_xtd_format, cmd);
	ENDTRACE
	IFDEBUG(D_CONN)
		printf(
		"tp_consist rtns 0x%x class 0x%x xtd_fmt 0x%x cmd 0x%x\n",
			error, tpcb->tp_class, tpcb->tp_xtd_format, cmd);
	ENDDEBUG
	return error;
}

/*
 * NAME: 	tp_ctloutput()
 *
 * CALLED FROM:
 * 	[sg]etsockopt(), via so[sg]etopt(). 
 *
 * FUNCTION and ARGUMENTS:
 * 	Implements the socket options at transport level.
D 3
 * 	(cmd) is either PRCO_SETOPT or PRCO_GETOPT (see ../h/protosw.h).
E 3
I 3
 * 	(cmd) is either PRCO_SETOPT or PRCO_GETOPT (see ../sys/protosw.h).
E 3
 * 	(so) is the socket.
D 3
 * 	(level) is SOL_TRANSPORT (see ../h/socket.h)
E 3
I 3
 * 	(level) is SOL_TRANSPORT (see ../sys/socket.h)
E 3
 * 	(optname) is the particular command or option to be set.
 * 	(**mp) is an mbuf structure.  
 *
 * RETURN VALUE:
 * 	ENOTSOCK if the socket hasn't got an associated tpcb
 *  EINVAL if 
 * 		trying to set window too big
 * 		trying to set illegal max tpdu size 
 * 		trying to set illegal credit fraction
 * 		trying to use unknown or unimplemented class of TP
 *		structure passed to set timer values is wrong size
 *  	illegal combination of command/GET-SET option, 
 *			e.g., GET w/ TPOPT_CDDATA_CLEAR: 
 *  EOPNOTSUPP if the level isn't transport, or command is neither GET nor SET
 *   or if the transport-specific command is not implemented
 *  EISCONN if trying a command that isn't allowed after a connection
 *   is established
 *  ENOTCONN if trying a command that is allowed only if a connection is
 *   established
 *  EMSGSIZE if trying to give too much data on connect/disconnect
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 */
ProtoHook 
tp_ctloutput(cmd, so, level, optname, mp)
	int 			cmd, level, optname;
	struct socket	*so;
	struct mbuf 	**mp;
{
	struct		tp_pcb	*tpcb = sototpcb(so);
	int 		s = splnet();
D 2
	u_char 		*value;
	int			val_len;
E 2
I 2
	caddr_t		value;
	unsigned	val_len;
E 2
	int			error = 0;

	IFTRACE(D_REQUEST)
		tptrace(TPPTmisc, "tp_ctloutput cmd so optname mp", 
			cmd, so, optname, mp);
	ENDTRACE
	IFDEBUG(D_REQUEST)
		printf(
	"tp_ctloutput so 0x%x cmd 0x%x optname 0x%x, mp 0x%x *mp 0x%x tpcb 0x%x\n", 
			so, cmd, optname, mp, mp?*mp:0, tpcb);
	ENDDEBUG
	if( tpcb == (struct tp_pcb *)0 ) {
		error = ENOTSOCK; goto done;
	}
	if(*mp == MNULL) {
		register struct mbuf *m;

		MGET(m, M_DONTWAIT, TPMT_SONAME); /* does off, type, next */
		if (m == NULL) {
			splx(s);
			return ENOBUFS;
		}
		m->m_len = 0;
		m->m_act = 0;
		*mp = m;
	}

	/*
	 *	Hook so one can set network options via a tp socket.
	 */
	if ( level == SOL_NETWORK ) {
		if ((tpcb->tp_nlproto == NULL) || (tpcb->tp_npcb == NULL))
			error = ENOTSOCK;
		else if (tpcb->tp_nlproto->nlp_ctloutput == NULL)
			error = EOPNOTSUPP;
		else
D 13
			error = (tpcb->tp_nlproto->nlp_ctloutput)(cmd, optname, 
				tpcb->tp_npcb, *mp);
E 13
I 13
			return ((tpcb->tp_nlproto->nlp_ctloutput)(cmd, optname, 
				tpcb->tp_npcb, *mp));
E 13
		goto done;
I 13
	} else if ( level == SOL_SOCKET) {
		if (optname == SO_RCVBUF && cmd == PRCO_SETOPT) {
I 16
			u_long old_credit = tpcb->tp_maxlcredit;
E 16
			tp_rsyset(tpcb);
I 16
			if (tpcb->tp_rhiwat != so->so_rcv.sb_hiwat &&
			    tpcb->tp_state == TP_OPEN &&
			    (old_credit < tpcb->tp_maxlcredit))
				tp_emit(AK_TPDU_type, tpcb,
					tpcb->tp_rcvnxt, 0, MNULL);
			tpcb->tp_rhiwat = so->so_rcv.sb_hiwat;
E 16
		}
		goto done;
E 13
	} else if ( level !=  SOL_TRANSPORT ) {
		error = EOPNOTSUPP; goto done;
	} 
	if (cmd != PRCO_GETOPT && cmd != PRCO_SETOPT) {
		error = EOPNOTSUPP; goto done;
	} 
	if ( so->so_error ) {
		error = so->so_error; goto done;
	}

	/* The only options allowed after connection is established
	 * are GET (anything) and SET DISC DATA and SET PERF MEAS
	 */
	if ( ((so->so_state & SS_ISCONNECTING)||(so->so_state & SS_ISCONNECTED))
		&&
		(cmd == PRCO_SETOPT  && 
			optname != TPOPT_DISC_DATA && 
I 4
			optname != TPOPT_CFRM_DATA && 
E 4
			optname != TPOPT_PERF_MEAS &&
			optname != TPOPT_CDDATA_CLEAR ) ) {
		error = EISCONN; goto done;
	} 
	/* The only options allowed after disconnection are GET DISC DATA,
	 * and TPOPT_PSTATISTICS
	 * and they're not allowed if the ref timer has gone off, because
	 * the tpcb is gone 
	 */
D 4
	if ((so->so_state & SS_ISCONNECTED) ==  0) {
E 4
I 4
	if ((so->so_state & (SS_ISCONNECTED | SS_ISCONFIRMING)) ==  0) {
E 4
D 11
		if ( so->so_tpcb == (caddr_t)0 ) {
E 11
I 11
		if ( so->so_pcb == (caddr_t)0 ) {
E 11
			error = ENOTCONN; goto done;
		}
		if ( (tpcb->tp_state == TP_REFWAIT || tpcb->tp_state == TP_CLOSING) &&
				(optname != TPOPT_DISC_DATA && optname != TPOPT_PSTATISTICS)) {
			error = ENOTCONN; goto done;
		}
	}

D 2
	value = (u_char *) mtod(*mp, u_char *);  /* it's aligned, don't worry,
											* but lint complains about it 
											*/
E 2
I 2
	value = mtod(*mp, caddr_t);  /* it's aligned, don't worry,
								  * but lint complains about it 
								  */
E 2
	val_len = (*mp)->m_len;

	switch (optname) {
I 6

	case TPOPT_INTERCEPT:
I 12
#define INA(t) (((struct inpcb *)(t->tp_npcb))->inp_laddr.s_addr)
#define ISOA(t) (((struct isopcb *)(t->tp_npcb))->isop_laddr->siso_addr)

E 12
D 10
		if (error = suser(u.u_cred, &u.u_acflag))
E 10
I 10
		if ((so->so_state & SS_PRIV) == 0) {
			error = EPERM;
E 10
D 12
			break;
D 10
		else if (cmd != PRCO_SETOPT || tpcb->tp_state != TP_LISTENING)
E 10
I 10
		} else if (cmd != PRCO_SETOPT || tpcb->tp_state != TP_LISTENING)
E 12
I 12
		} else if (cmd != PRCO_SETOPT || tpcb->tp_state != TP_CLOSED ||
					(tpcb->tp_flags & TPF_GENERAL_ADDR) ||
					tpcb->tp_next == 0)
E 12
E 10
			error = EINVAL;
		else {
D 12
			register struct tp_pcb *t = 0;
			struct mbuf *m = m_getclr(M_WAIT, MT_SONAME);
			struct sockaddr *sa = mtod(m, struct sockaddr *);
			(*tpcb->tp_nlproto->nlp_getnetaddr)(tpcb->tp_npcb, m, TP_LOCAL);
			switch (sa->sa_family) {
			case AF_ISO:
				if (((struct sockaddr_iso *)sa)->siso_nlen == 0)
					default: error = EINVAL;
				break;
			case AF_INET:
				if (((struct sockaddr_in *)sa)->sin_addr.s_addr == 0)
					error = EINVAL;
				break;
			}
			for (t = tp_intercepts; t; t = t->tp_nextlisten) {
				if (t->tp_nlproto->nlp_afamily != tpcb->tp_nlproto->nlp_afamily)
					continue;
				if ((*t->tp_nlproto->nlp_cmpnetaddr)(t->tp_npcb, sa, TP_LOCAL))
					error = EADDRINUSE;
			}
			m_freem(m);
			if (error)
				break;
E 12
I 12
			register struct tp_pcb *t;
			error = EADDRINUSE;
			for (t = tp_listeners; t; t = t->tp_nextlisten)
				if ((t->tp_flags & TPF_GENERAL_ADDR) == 0 &&
						t->tp_domain == tpcb->tp_domain)
					switch (tpcb->tp_domain) {
					default:
						goto done;
#ifdef	INET
					case AF_INET:
						if (INA(t) == INA(tpcb))
							goto done;
						continue;
#endif
#ifdef ISO
					case AF_ISO:
						if (bcmp(ISOA(t).isoa_genaddr, ISOA(tpcb).isoa_genaddr,
										ISOA(t).isoa_len) == 0)
							goto done;
						continue;
#endif
					}
			tpcb->tp_lsuffixlen = 0;
			tpcb->tp_state = TP_LISTENING;
			error = 0;
			remque(tpcb);
			tpcb->tp_next = tpcb->tp_prev = tpcb;
			tpcb->tp_nextlisten = tp_listeners;
			tp_listeners = tpcb;
E 12
		}
D 12
		{
			register struct tp_pcb **tt;
			for (tt = &tp_listeners; *tt; tt = &((*tt)->tp_nextlisten))
				if (*tt == tpcb)
					break;
			if (*tt)
				*tt = tpcb->tp_nextlisten;
			else
				{error = EHOSTUNREACH; goto done; }
		}
D 7
		tp_intercepts = tpcb;
E 7
		tpcb->tp_nextlisten = tp_intercepts;
I 7
		tp_intercepts = tpcb;
E 12
E 7
		break;
E 6

	case TPOPT_MY_TSEL:
		if ( cmd == PRCO_GETOPT ) {
			ASSERT( tpcb->tp_lsuffixlen <= MAX_TSAP_SEL_LEN );
D 2
			bcopy( tpcb->tp_lsuffix, value, tpcb->tp_lsuffixlen);
E 2
I 2
			bcopy((caddr_t)tpcb->tp_lsuffix, value, tpcb->tp_lsuffixlen);
E 2
			(*mp)->m_len = tpcb->tp_lsuffixlen;
		} else /* cmd == PRCO_SETOPT  */ {
			if( (val_len > MAX_TSAP_SEL_LEN) || (val_len <= 0 )) {
				printf("val_len 0x%x (*mp)->m_len 0x%x\n", val_len, (*mp));
				error = EINVAL;
			} else {
D 2
				bcopy( value, tpcb->tp_lsuffix, val_len );
E 2
I 2
				bcopy(value, (caddr_t)tpcb->tp_lsuffix, val_len);
E 2
				tpcb->tp_lsuffixlen = val_len;
			}
		}
		break;

	case TPOPT_PEER_TSEL:
		if ( cmd == PRCO_GETOPT ) {
			ASSERT( tpcb->tp_fsuffixlen <= MAX_TSAP_SEL_LEN );
D 2
			bcopy( tpcb->tp_fsuffix, value, tpcb->tp_fsuffixlen);
E 2
I 2
			bcopy((caddr_t)tpcb->tp_fsuffix, value, tpcb->tp_fsuffixlen);
E 2
			(*mp)->m_len = tpcb->tp_fsuffixlen;
		} else /* cmd == PRCO_SETOPT  */ {
			if( (val_len > MAX_TSAP_SEL_LEN) || (val_len <= 0 )) {
				printf("val_len 0x%x (*mp)->m_len 0x%x\n", val_len, (*mp));
				error = EINVAL; 
			} else {
D 2
				bcopy( value, tpcb->tp_fsuffix, val_len );
E 2
I 2
				bcopy(value, (caddr_t)tpcb->tp_fsuffix, val_len);
E 2
				tpcb->tp_fsuffixlen = val_len;
			}
		}
		break;

	case TPOPT_FLAGS:
		IFDEBUG(D_REQUEST)
			printf("%s TPOPT_FLAGS value 0x%x *value 0x%x, flags 0x%x \n", 
				cmd==PRCO_GETOPT?"GET":"SET", 
				value,
				*value, 
				tpcb->tp_flags);
		ENDDEBUG

		if ( cmd == PRCO_GETOPT ) {
			*(int *)value = (int)tpcb->tp_flags;
			(*mp)->m_len = sizeof(u_int);
		} else /* cmd == PRCO_SETOPT  */ {
			error = EINVAL; goto done;
		}
		break;

	case TPOPT_PARAMS:
		/* This handles:
		 * timer values,
		 * class, use of transport expedited data,
		 * max tpdu size, checksum, xtd format and
		 * disconnect indications, and may get rid of connect/disc data
		 */
		IFDEBUG(D_SETPARAMS)
			printf("TPOPT_PARAMS value 0x%x, cmd %s \n", value,
				cmd==PRCO_GETOPT?"GET":"SET");
		ENDDEBUG
		IFDEBUG(D_REQUEST)
			printf("TPOPT_PARAMS value 0x%x, cmd %s \n", value,
				cmd==PRCO_GETOPT?"GET":"SET");
		ENDDEBUG

		if ( cmd == PRCO_GETOPT ) {
			*(struct tp_conn_param *)value = tpcb->_tp_param;
			(*mp)->m_len = sizeof(tpcb->_tp_param);
		} else /* cmd == PRCO_SETOPT  */ {
			if( (error = 
				tp_consistency(tpcb, TP_STRICT | TP_FORCE, 
								(struct tp_conn_param *)value))==0) {
				/* 
				 * tp_consistency doesn't copy the whole set of params 
				 */
				tpcb->_tp_param = *(struct tp_conn_param *)value;
				(*mp)->m_len = sizeof(tpcb->_tp_param);
			}
		}
		break;

	case TPOPT_PSTATISTICS: 
#ifdef TP_PERF_MEAS
		if (cmd == PRCO_SETOPT) {
			error = EINVAL; goto done;
		} 
		IFPERF(tpcb)
D 2
			/* tp_p_meas is a cluster : "copy" it */
			mclrefcnt[mtocl( (tpcb->tp_p_meas) )]++;
			(*mp)->m_off = (u_long)((int)tpcb->tp_p_meas - (int)(*mp));
			(*mp)->m_len = sizeof(struct tp_pmeas);
E 2
I 2
			if (*mp) {
				struct mbuf * n;
				do {
					MFREE(*mp, n);
					*mp = n;
				} while (n);
			}
			*mp = m_copym(tpcb->tp_p_mbuf, (int)M_COPYALL, M_WAITOK);
E 2
		ENDPERF 
		else {
			error = EINVAL; goto done;
		} 
		break;
#else
		error = EOPNOTSUPP;
		goto done;
D 18
#endif TP_PERF_MEAS
E 18
I 18
#endif /* TP_PERF_MEAS */
E 18
		
	case TPOPT_CDDATA_CLEAR: 
		if (cmd == PRCO_GETOPT) {
			error = EINVAL;
		} else {
D 2
			if ( tpcb->tp_flags & (TPF_CONN_DATA_OUT | TPF_DISC_DATA_OUT) ) {
				sbdrop(&so->so_snd, so->so_snd.sb_cc);
				tpcb->tp_flags &= ~(TPF_CONN_DATA_OUT | TPF_DISC_DATA_OUT);
E 2
I 2
			if (tpcb->tp_ucddata) {
D 4
					m_freem(tpcb->tp_ucddata);
					tpcb->tp_ucddata = 0;
E 4
I 4
				m_freem(tpcb->tp_ucddata);
				tpcb->tp_ucddata = 0;
E 4
E 2
			}
		}
		break;

I 4
D 5
#ifdef TPOPT_NGC8_ACCEPT
	case TPOPT_NGC8_ACCEPT: 
		if ( cmd == PRCO_GETOPT ) {
			*(int *)value = (int)tpcb->tp_flags & TPFLAG_NGC8_ACCEPT;
			(*mp)->m_len = sizeof(u_int);
		} else  {
			if (*(int *)value)
				tpcb->tp_flags |= TPFLAG_NGC8_ACCEPT;
			else
				tpcb->tp_flags &= ~TPFLAG_NGC8_ACCEPT;
		}
		break;
#endif

E 5
	case TPOPT_CFRM_DATA:
D 5
		if (cmd == PRCO_SETOPT && (so->so_state & SS_ISCONFIRMING))
			(void) tp_confirm(tpcb);
		/* drop through */
E 5
E 4
	case TPOPT_DISC_DATA: 
D 5
		/* drop through */
	/* sending is for debugging purposes only -- we don't pretend 
	 * to support * data on connect or disconnect fully. It's a 
	 * kludge at best.
	 * This data-on-connect is only for the active side.  It's sort of
	 * meaningless on the passive side (because
	 * you can't reject a connect request based on the data 
	 * arriving w/ the CR, this, and because you'd have to 
	 * do this setsockopt system call for each accept).
	 * but you can use it if you want.
	 */
E 5
	case TPOPT_CONN_DATA: 
		if( tpcb->tp_class == TP_CLASS_0 ) {
			error = EOPNOTSUPP;
			break;
		}
		IFDEBUG(D_REQUEST)
			printf("%s\n", optname==TPOPT_DISC_DATA?"DISC data":"CONN data");
			printf("m_len 0x%x, vallen 0x%x so_snd.cc 0x%x\n", 
				(*mp)->m_len, val_len, so->so_snd.sb_cc);
			dump_mbuf(so->so_snd.sb_mb, "tp_ctloutput: sosnd ");
D 2
			dump_mbuf(tpcb->tp_Xrcv.sb_mb, "tp_ctlout: tpXrcv ");
E 2
		ENDDEBUG
		if (cmd == PRCO_SETOPT) {
I 2
			int len = tpcb->tp_ucddata ?  tpcb->tp_ucddata->m_len : 0;
E 2
			/* can append connect data in several calls */
D 2
			if (so->so_snd.sb_cc + val_len > 
E 2
I 2
			if (len + val_len > 
E 2
				(optname==TPOPT_CONN_DATA?TP_MAX_CR_DATA:TP_MAX_DR_DATA) ) {
				error = EMSGSIZE; goto done;
			} 
D 2
			tpcb->tp_flags |= 
			((optname==TPOPT_CONN_DATA)?TPF_CONN_DATA_OUT:TPF_DISC_DATA_OUT);
E 2
			(*mp)->m_next = MNULL;
			(*mp)->m_act = 0;
D 2
			sbappendrecord( &so->so_snd, *mp);
E 2
I 2
			if (tpcb->tp_ucddata)
				m_cat(tpcb->tp_ucddata, *mp);
			else
				tpcb->tp_ucddata = *mp;
E 2
D 5
		IFDEBUG(D_REQUEST)
D 2
			dump_mbuf(so->so_snd.sb_mb, "tp_ctloutput after sbappendrecord");
E 2
I 2
			dump_mbuf(tpcb->tp_ucddata, "tp_ctloutput after CONN_DATA");
E 2
		ENDDEBUG
E 5
I 5
			IFDEBUG(D_REQUEST)
				dump_mbuf(tpcb->tp_ucddata, "tp_ctloutput after CONN_DATA");
			ENDDEBUG
E 5
			IFTRACE(D_REQUEST)
				tptrace(TPPTmisc,"C/D DATA: flags snd.sbcc val_len",
					tpcb->tp_flags, so->so_snd.sb_cc,val_len,0);
			ENDTRACE
D 13
			*mp = MNULL; /* prevent sosetopt from freeing it! */
E 13
I 13
			*mp = MNULL;
E 13
I 5
			if (optname == TPOPT_CFRM_DATA && (so->so_state & SS_ISCONFIRMING))
				(void) tp_confirm(tpcb);
E 5
D 2
		} else /* cmd == PRCO_GETOPT */ {
			register int len = tpcb->tp_Xrcv.sb_cc;

			/* getsockopt() allocated an mbuf but it's a whole lot easier
			 * to do an m_copy than to explicitly copy from the socket buf
			 * into the buffer provided by getsockopt()
			 */
			IFDEBUG(D_REQUEST)
				dump_mbuf(tpcb->tp_Xrcv.sb_mb, 
					"tp_ctlout: tpXrcv before sbdrop");
			ENDDEBUG
			if(len) {
				(void) m_freem(*mp);
				*mp = m_copy( tpcb->tp_Xrcv.sb_mb, 0, len);
				if( *mp != MNULL ) {
					(*mp)->m_act = 0;
					sbdrop( &tpcb->tp_Xrcv, len);
				} else {
					error = ENOBUFS;
				}
			} else {
				(*mp)->m_len = 0;
			}
			IFDEBUG(D_REQUEST)
				dump_mbuf(tpcb->tp_Xrcv.sb_mb, 
					"tp_ctlout: tpXrcv after sbdrop");
			ENDDEBUG
			/* a potential problem here is that REAL expedited may have arrived
			 * after the data-on-connect 
			 * however, this presently works because incoming XPD_TPDUs are
			 * dropped if tp_Xrcv.sb_cc != 0
			 */

			if( tpcb->tp_Xrcv.sb_cc == 0)
				tpcb->tp_flags &= 
				optname == TPOPT_CONN_DATA?~TPF_CONN_DATA_IN:~TPF_DISC_DATA_IN;
E 2
		}
		break;

	case TPOPT_PERF_MEAS: 
#ifdef TP_PERF_MEAS
		if (cmd == PRCO_GETOPT) {
			*value = (u_int)tpcb->tp_perf_on;
			(*mp)->m_len = sizeof(u_int);
		} else if (cmd == PRCO_SETOPT) {
			(*mp)->m_len = 0;
			if ((*value) != 0 && (*value) != 1 )
				error = EINVAL;
			else  tpcb->tp_perf_on = (*value);
		}
		if( tpcb->tp_perf_on ) 
			error = tp_setup_perf(tpcb);
D 18
#else  TP_PERF_MEAS
E 18
I 18
#else  /* TP_PERF_MEAS */
E 18
		error = EOPNOTSUPP;
D 18
#endif TP_PERF_MEAS
E 18
I 18
#endif /* TP_PERF_MEAS */
E 18
		break;

	default:
		error = EOPNOTSUPP;
	}
	
done:
	IFDEBUG(D_REQUEST)
		dump_mbuf(so->so_snd.sb_mb, "tp_ctloutput sosnd at end");
		dump_mbuf(*mp, "tp_ctloutput *mp");
	ENDDEBUG
	/* 
	 * sigh: getsockopt looks only at m_len : all output data must 
	 * reside in the first mbuf 
	 */
D 13
	if ( error  && (*mp) != MNULL )
		(*mp)->m_len = 0;
	if( (*mp) != MNULL ) {
		ASSERT ( m_compress(*mp, mp) <= MLEN );
		IFDEBUG(D_REQUEST)
			dump_mbuf(*mp, "tp_ctloutput *mp after compress");
		ENDDEBUG
E 13
I 13
	if (*mp) {
D 16
		if (cmd == PRCO_SETOPT)
E 16
I 16
		if (cmd == PRCO_SETOPT) {
E 16
			m_freem(*mp);
D 16
		else {
E 16
I 16
			*mp = MNULL;
		} else {
E 16
			ASSERT ( m_compress(*mp, mp) <= MLEN );
			if (error)
				(*mp)->m_len = 0;
			IFDEBUG(D_REQUEST)
				dump_mbuf(*mp, "tp_ctloutput *mp after compress");
			ENDDEBUG
		}
E 13
	}
D 13
		
E 13
	splx(s);
	return error;
}
E 1
