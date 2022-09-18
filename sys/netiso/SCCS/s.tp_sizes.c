h13443
s 00000/00001/00121
d D 7.4 91/05/07 12:18:11 sklower 4 3
c no more refs to argoxtwentyfive.c
e
s 00020/00021/00102
d D 7.3 89/08/29 13:45:30 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00040/00094/00083
d D 7.2 89/04/22 11:55:26 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00177/00000/00000
d D 7.1 88/12/14 15:30:11 sklower 1 0
c date and time created 88/12/14 15:30:11 by sklower
e
u
U
t
T
I 1
D 2
/***********************************************************
E 2
I 2
/************************************************************
E 2
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

#define KERNEL
#define MERGED
#define IBMRTPC
#define CLNPECHO
D 2
#define TP_PERF_MEAS
E 2
I 2
/* #define TP_PERF_MEAS */
E 2
#define CONS
#define TPPT
#define ARGO_TP
#define ARGO_DEBUG
#define ISO
#define RDB
#define SHOW_LOAD
#define DEBUG
#define INET
#define MAXUSERS 32
#define DST 1
#define TIMEZONE 360

/* 
 * ARGO TP
 *
 * $Header: tp_sizes.c,v 5.1 88/10/12 12:21:03 root Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_sizes.c,v $
I 3
 *	%W% (Berkeley) %G% *
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

#ifndef lint
static char *rcsid = "$Header: tp_sizes.c,v 5.1 88/10/12 12:21:03 root Exp $";
#endif lint

D 4
#include "argoxtwentyfive.h"
E 4
#include "types.h"
#include "param.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "protosw.h"
#include "errno.h"
#include "time.h"
D 2
#include "../netiso/tp_param.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_ip.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_meas.h"
#include "../netiso/tp_seq.h"
#include "../netiso/tp_clnp.h"
E 2
I 2
#include "tp_param.h"
D 3
#include "tp_timer.h"
#include "tp_ip.h"
E 3
#include "tp_stat.h"
#include "tp_pcb.h"
#include "tp_tpdu.h"
#include "tp_trace.h"
#include "tp_meas.h"
#include "tp_seq.h"
#include "tp_clnp.h"
E 2

D 2
#include "../netiso/iso_errno.h"
#include "../netiso/cons.h"
#include "../netiso/cons_pcb.h"
E 2
I 2
#include "iso_errno.h"
#include "cons.h"
#undef IncStat
#include "cons_pcb.h"
E 2

I 2
#define DUP(x) x, x
D 3
#define SIZE(P) printf("Size of %s: 0x%x %d\n", "P", DUP(sizeof(struct P)))
E 3
I 3
#define SIZE(P) printf("  Size of %s: 0x%x %d\n", "P", DUP(sizeof(struct P)))
E 3
#define OFF(P, Q) printf("\toffset of %s in %s: 0x%x %d\n", "P", "Q", \
		DUP(_offsetof(struct Q, P)))
E 2
main()
{
	printf( "TP struct sizes:\n");
D 2
	printf( "tpcb 0x%x %d\n", sizeof(struct tp_pcb), sizeof(struct tp_pcb));
	printf( "aux 0x%x %d\n",
		sizeof(struct tp_pcb_aux), sizeof(struct tp_pcb_aux));
	printf( "ref 0x%x %d\n", sizeof(struct tp_ref), sizeof(struct tp_ref));
	printf( "tp_stat  0x%x %d\n", 
		sizeof(struct tp_stat), sizeof(struct tp_stat));
	printf( "tp_param  0x%x %d\n", 
		sizeof(struct tp_param), sizeof(struct tp_param));
	printf( "tp_conn_param  0x%x %d\n", 
		sizeof(struct tp_conn_param), sizeof(struct tp_conn_param));
	printf( "tp_rtc  0x%x %d\n", 
		sizeof(struct tp_rtc), sizeof(struct tp_rtc));
	printf( "nl_protosw  0x%x %d\n", 
		sizeof(struct nl_protosw), sizeof(struct nl_protosw));

E 2
I 2
	SIZE(tp_pcb);
#define O(y) OFF(tp_/**/y,tp_pcb);
D 3
	O(state) O(retrans) O(snduna)
	O(lref) O(fref) O(fsuffix)
	O(fsuffixlen) O(lsuffix) O(lsuffixlen)
	O(Xsnd) O(Xuna)
	SIZE(tp_ref); OFF(tpr_pcb,tp_ref);OFF(tpr_calltodo,tp_ref);
	SIZE(tp_stat); SIZE(tp_param);
	SIZE(tp_conn_param); SIZE(tp_rtc); SIZE(nl_protosw);
E 2
#ifdef TP_PERF_MEAS
D 2
		printf( "\tpmeas 0x%x %d\n", sizeof(struct tp_pmeas),
			sizeof(struct tp_pmeas));
#else
		printf("perf meas NOT configured\n");
#endif TP_PERF_MEAS

E 2
I 2
	SIZE(tp_Meas);
#endif
E 2
	printf( "ISO struct sizes:\n");
E 3
I 3
	O(state) O(retrans) O(snduna) O(lref) O(fref)
	O(fsuffix) O(fsuffixlen) O(lsuffix) O(lsuffixlen) O(Xsnd) O(Xuna)
	SIZE(tp_ref);
#undef O
#define O(y) OFF(tpr_/**/y,tp_ref);
	O(pcb) O(calltodo)
	SIZE(tp_stat);
	SIZE(tp_param); SIZE(tp_conn_param);
	SIZE(tp_rtc); SIZE(nl_protosw);
#undef O
#define O(y) OFF(so_/**/y,socket);
	printf( "socket struct sizes:\n");
E 3
D 2
	printf( "socket  0x%x %d\n",  
		sizeof(struct socket), sizeof(struct socket));
	printf( "\t offset of so_timeo 0x%x %d\n",  
		_offsetof( struct socket, so_timeo ),
		_offsetof( struct socket, so_timeo ));
	printf( "\t offset of so_rcv 0x%x %d\n",  
		_offsetof(  struct socket, so_rcv ),
		_offsetof(  struct socket, so_rcv ));
	printf( "\t offset of so_snd 0x%x %d\n",  
		_offsetof(  struct socket, so_snd ),
		_offsetof( struct socket, so_snd ));
	printf( "\t offset of sb_flags in sockbuf 0x%x %d\n",  
		_offsetof( struct sockbuf, sb_flags ),
		_offsetof( struct sockbuf, sb_flags ));
	printf( "\t offset of sb_cc in sockbuf 0x%x %d\n",  
		_offsetof( struct sockbuf, sb_cc ),
		_offsetof( struct sockbuf, sb_cc ));
	printf( "\t offset of so_qlen in sockbuf 0x%x %d\n",  
		_offsetof( struct socket, so_qlen ),
		_offsetof( struct socket, so_qlen ));
	printf( "\t offset of so_error in sockbuf 0x%x %d\n",  
		_offsetof( struct socket, so_error ),
		_offsetof( struct socket, so_error ));
	printf( "\t offset of so_state in sockbuf 0x%x %d\n",  
		_offsetof( struct socket, so_state ),
		_offsetof( struct socket, so_state ));

	printf( "SIZE OF isopcb  0x%x %d\n", 
		sizeof(struct isopcb), sizeof(struct isopcb));
	printf( "SIZE OF cons_pcb  0x%x %d\n", 
		sizeof(struct cons_pcb), sizeof(struct cons_pcb));
	printf( "\t offset of co_state in cons_pcb 0x%x %d\n",  
		_offsetof( struct cons_pcb, co_state ),
		_offsetof( struct cons_pcb, co_state ));

#include "../h/types.h"
#include "../h/ioctl.h"
#include "../h/tty.h"
	printf( "SIZE OF tty  0x%x %d\n", 
		sizeof(struct tty), sizeof(struct tty));
	printf( "\t offset of t_outq in tty 0x%x %d\n",  
		_offsetof( struct tty, t_outq ),
		_offsetof( struct tty, t_outq ));
	printf( "\t offset of t_canq in tty 0 0\n");
	printf( "\t offset of t_rawq in tty 0 0\n");
	printf( "SIZE OF clist  0x%x %d\n", 
		sizeof(struct clist), sizeof(struct clist));
	printf( "\t offset of c_cf in clist 0x%x %d\n",  
		_offsetof( struct clist, c_cf ),
		_offsetof( struct clist, c_cf ));

	{
		unsigned x;

		if( x<0 ) {
			printf("x");
		}
	}
E 2
I 2
	SIZE(socket);
D 3
	OFF(so_timeo,socket); OFF(so_rcv,socket); OFF(so_snd,socket);
	OFF(so_tpcb,socket); OFF(so_pcb,socket); OFF(so_qlen,socket);
	OFF(so_error,socket); OFF(so_state,socket);
E 3
I 3
	O(timeo) O(rcv) O(snd) O(tpcb) O(pcb) O(qlen) O(error) O(state)
E 3
	SIZE(sockbuf);
D 3
	OFF(sb_flags,sockbuf); OFF(sb_cc,sockbuf);
	OFF(sb_mb,sockbuf); OFF(sb_mbcnt,sockbuf);
	SIZE(isopcb);
	 SIZE(cons_pcb); OFF(co_state,cons_pcb);
E 3
I 3
#undef O
#define O(y) OFF(sb_/**/y,sockbuf);
	O(flags) O(cc) O(mb) O(mbcnt)
	SIZE(isopcb); SIZE(cons_pcb);
	OFF(co_state,cons_pcb);
E 3
E 2
}
E 1
