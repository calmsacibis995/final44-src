h37028
s 00002/00002/00968
d D 8.1 93/06/10 23:20:13 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00966
d D 7.17 93/05/25 11:51:47 bostic 17 16
c trailing comment after #else or #endif
e
s 00025/00025/00945
d D 7.16 92/10/11 12:21:57 bostic 16 15
c make kernel includes standard
e
s 00001/00000/00969
d D 7.15 92/09/21 19:06:06 mckusick 15 14
c need to include systm.h to get min and max
e
s 00003/00006/00966
d D 7.14 92/05/27 16:14:16 sklower 14 13
c make sure to calculate initial credit for both CE_bit options for CC and CR
e
s 00013/00000/00959
d D 7.13 91/12/17 16:19:36 sklower 13 12
c big-or-odd-size packet option. (n x 128 instead of 2^n only)
e
s 00073/00059/00886
d D 7.12 91/09/26 17:02:39 sklower 12 11
c These changes represent a rewrite of retransmission policies to
c imitate the TCP algorithms more closely.  More tuning and testing need to
c be done, but the code runs at least somewhat, and these represent a checkpoint
e
s 00027/00028/00918
d D 7.11 91/07/29 14:55:48 sklower 11 10
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00002/00001/00944
d D 7.10 91/07/25 10:31:55 sklower 10 9
c tp_error_emit doesn't set drefs; minor lint gotcha for cons
e
s 00005/00003/00940
d D 7.9 91/05/09 21:12:17 sklower 9 8
c emit should create a hdr type mbuf....
e
s 00009/00006/00934
d D 7.8 91/05/06 19:24:19 bostic 8 7
c new copyright; att/bsd/shared
e
s 00010/00003/00930
d D 7.7 91/04/26 15:17:58 sklower 7 6
c Bad Bug -- AK tpdu's incorrect swapped bytes before setting eot bit
e
s 00022/00010/00911
d D 7.6 91/01/09 15:45:00 sklower 6 5
c Checkpoint integration of tp_cons with UBC X.25; compiles only;
c not tested, probably not complete.
e
s 00018/00004/00903
d D 7.5 90/05/30 19:31:43 sklower 5 4
c some errors must be responded to by a DC rather than DR or ER.
e
s 00012/00001/00895
d D 7.4 90/01/16 23:10:06 sklower 4 3
c mitre decbit changes
e
s 00001/00000/00895
d D 7.3 89/08/29 13:44:53 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00052/00039/00843
d D 7.2 89/04/22 11:54:49 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00882/00000/00000
d D 7.1 88/12/14 15:29:58 sklower 1 0
c date and time created 88/12/14 15:29:58 by sklower
e
u
U
t
T
I 8
/*-
D 18
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 8
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
 * $Header: tp_emit.c,v 5.5 88/11/18 17:27:20 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_emit.c,v $
I 3
D 8
 *	%W% (Berkeley) %G% *
E 8
E 3
 *
 * This file contains tp_emit() and tp_error_emit(), which
 * form TPDUs and hand them to ip.
 * They take data in the form of mbuf chain, allocate mbufs as
 * necessary for headers, and set the fields as appropriate from
 * information found in the tpcb and net-level pcb.
 *
 * The worst thing about this code is adding the variable-length
 * options on a machine that requires alignment for any memory access
 * that isn't of size 1.  See the macro ADDOPTION() below.
 *
 * We don't do any concatenation. (There's a kludge to test the
 * basic mechanism of separation under the 'w' tpdebug option, that's all.)
 */
D 8

#ifndef lint
static char *rcsid = "$Header: tp_emit.c,v 5.5 88/11/18 17:27:20 nhall Exp $";
#endif lint

E 8

D 6
#include "argoxtwentyfive.h"
E 6
D 16
#include "param.h"
I 15
#include "systm.h"
E 15
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "protosw.h"
#include "errno.h"
#include "types.h"
#include "time.h"
D 2
#include "../netiso/iso.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_param.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_meas.h"
#include "../netiso/tp_seq.h"
#include "../netiso/iso_errno.h"
E 2
I 2
#include "iso.h"
I 6
#include "iso_pcb.h"
E 6
#include "argo_debug.h"
#include "tp_timer.h"
#include "tp_param.h"
#include "tp_stat.h"
#include "tp_pcb.h"
#include "tp_tpdu.h"
#include "tp_trace.h"
#include "tp_meas.h"
#include "tp_seq.h"
#include "iso_errno.h"
E 16
I 16
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
E 16
E 2

I 6
D 16
#include "../net/if.h"
E 16
I 16
#include <netiso/iso.h>
#include <netiso/iso_pcb.h>
#include <netiso/argo_debug.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_param.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_tpdu.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_meas.h>
#include <netiso/tp_seq.h>
#include <netiso/iso_errno.h>

#include <net/if.h>
E 16
#ifdef TRUE
#undef FALSE
#undef TRUE
#endif
D 16
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 16
I 16
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 16

E 6
void iso_gen_csum();


/* Here is a mighty kludge.  The token ring misorders packets if you
 * fire them at it too fast, and TP sans checksum is "too fast", so
 * we have introduced a delay when checksumming isn't used.
 */
char tp_delay = 0x00; /* delay to keep token ring from blowing it */

/*
 * NAME:	tp_emit()
 *
 * CALLED FROM: tp.trans and from tp_sbsend()
 *
 * FUNCTION and ARGUMENTS:
 * 	Emits one tpdu of the type (dutype), of the format appropriate
 * 	to the connection described by the pcb (tpcb), with sequence
 * 	number (seq) (where appropriate), end-of-tsdu bit (eot) where
 * 	appropriate, and with the data in the mbuf chain (data).
 * 	For DR and ER tpdus, the argument (eot) is
 * 	the reason for issuing the tpdu rather than an end-of-tsdu indicator.
 *
 * RETURNS:			
 * 	0  OK
 * 	ENOBUFS 
 * 	E* returned from net layer output rtn 
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 *  
 * 	WE ASSUME that the tp header + all options will fit in ONE mbuf.  
 *	If mbufs are 256 this will most likely be true, but if they are 128 it's
 *	possible that they won't. 
 *	If you used every option on the CR + max. user data you'd overrun 
 *	112 but unless you used > 115 bytes for the security
 *	parameter, it would fit in a 256-byte mbuf (240 bytes for the header)
 *	We don't support the security parameter, so this isn't a problem.
 *	If security is added, we ought to remove this assumption.
 *
 *  We do not implement the flow control confirmation "element of procedure".
 *  A) it should not affect interoperability,
 *  B) it should not be necessary - the protocol will eventually
 *   	straighten things out w/o FCC, as long as we don't have severely
 *		mismatched keepalive and inactivity timers, and
 *	C) it appears not to be REQUIRED, and
 *  D) it's incredibly grotesque, and no doubt will lengthen a few
 *   	critical paths.
 *  HOWEVER, we're thinking about putting it in anyway, for
 *  completeness, just like we did with ack subsequencing.
 */

int
tp_emit(dutype,	tpcb, seq, eot, data)
	int dutype;
	struct tp_pcb *tpcb;
	SeqNum	seq;
	u_int 	eot;
	struct mbuf *data;
{
	register struct tpdu *hdr; 
	register struct mbuf *m;
	int csum_offset=0;
	int datalen = 0;
	int error = 0;
I 12
 	SeqNum olduwe;
	int acking_ooo;
E 12

	/* NOTE:
	 * here we treat tpdu_li as if it DID include the li field, up until
	 * the end, at which time we subtract 1
	 * THis is because if we subtract 1 right away, we end up adding
	 * one every time we add an option.
	 */
	IFDEBUG(D_EMIT)
		printf(
D 2
	"tp_emit dutype 0x%x, tpcb 0x%x, eot 0x%x, seq 0x%x, data 0x%x mfree 0x%x",
		dutype, tpcb, eot, seq, data, mfree);
E 2
I 2
	"tp_emit dutype 0x%x, tpcb 0x%x, eot 0x%x, seq 0x%x, data 0x%x",
		dutype, tpcb, eot, seq, data);
E 2
	ENDDEBUG

D 2
	MGET(m, M_DONTWAIT, TPMT_TPHDR); 
E 2
I 2
	if (dutype == CR_TPDU || dutype == CC_TPDU) {
		m = (struct mbuf *) malloc((u_long)256, M_MBUF, M_DONTWAIT);
		if (m) {
			m->m_type = TPMT_TPHDR;
			mbstat.m_mtypes[TPMT_TPHDR]++;
			m->m_next = MNULL;
D 9
			m->m_data = m->m_dat;
			m->m_flags = 0;
E 9
I 9
			m->m_nextpkt = MNULL;
			m->m_data = m->m_pktdat;
			m->m_flags = M_PKTHDR;
E 9
		}
	} else {
D 9
		MGET(m, M_DONTWAIT, TPMT_TPHDR); 
E 9
I 9
		MGETHDR(m, M_DONTWAIT, TPMT_TPHDR); 
E 9
	}
I 9
	m->m_data += max_hdr;
E 9
E 2
	if (m == NULL) {
		if(data != (struct mbuf *)0)
			m_freem(data);
		error = ENOBUFS;
		goto done;
	}
	m->m_len = sizeof(struct tpdu);
	m->m_act = MNULL;

	hdr = mtod(m, struct tpdu *);
D 2
	bzero(hdr, sizeof(struct tpdu));
E 2
I 2
	bzero((caddr_t)hdr, sizeof(struct tpdu));
E 2

	{
		int 	tp_headersize();

		hdr->tpdu_type = dutype;
		hdr->tpdu_li = tp_headersize(dutype, tpcb);  
		/*
		 * class 0 doesn't use this for DT
		 * it'll just get overwritten below 
		 */
		hdr->tpdu_dref = htons(tpcb->tp_fref); 
		if( tpcb->tp_use_checksum || 
			(dutype == CR_TPDU_type && (tpcb->tp_class & TP_CLASS_4) )) {
			csum_offset =  hdr->tpdu_li + 2; /* DOESN'T include csum */
			ADDOPTION(TPP_checksum, hdr, 2, eot /* dummy arg */);
			IFDEBUG(D_CHKSUM)
				printf(
					"tp_emit: csum_offset 0x%x, hdr->tpdu_li 0x%x\n",
						csum_offset, hdr->tpdu_li);
			ENDDEBUG
		} 
		/*
		 * VARIABLE PARTS...
		 */
		switch( dutype ) {

		case CR_TPDU_type:
D 5
			hdr->tpdu_CRdref_0 = htons(0);	/* must be zero */
E 5
I 5
			hdr->tpdu_CRdref_0 = 0;	/* must be zero */
I 14
		case CC_TPDU_type: 
E 14
E 5
I 4
			if (!tpcb->tp_cebit_off) {
				tpcb->tp_win_recv = tp_start_win << 8;
				LOCAL_CREDIT(tpcb);
				CONG_INIT_SAMPLE(tpcb);
D 12
				tpcb->tp_ackrcvd = 0;
			}
			else
E 12
I 12
			} else
E 12
				LOCAL_CREDIT(tpcb);
E 4

I 4
D 14

E 4
		case CC_TPDU_type: 
				{
E 14
I 14
/* Case CC_TPDU_type used to be here */
		{
E 14
					u_char x;

				hdr->tpdu_CCsref =  htons(tpcb->tp_lref); /* same as CRsref */

				if( tpcb->tp_class > TP_CLASS_1 ) {
D 4
					LOCAL_CREDIT( tpcb ); 
E 4
I 4
D 14
/* ifdef CE_BIT, we did this in tp_input when the CR came in */
					if (tpcb->tp_cebit_off)
						LOCAL_CREDIT( tpcb );
E 14
E 4
					tpcb->tp_sent_uwe = tpcb->tp_lcredit -1;
					tpcb->tp_sent_rcvnxt = 1;
					tpcb->tp_sent_lcdt = tpcb->tp_lcredit;
					hdr->tpdu_cdt = tpcb->tp_lcredit;
				} else {
I 6
#ifdef TPCONS
					if (tpcb->tp_netservice == ISO_CONS) {
						struct isopcb *isop = (struct isopcb *)tpcb->tp_npcb;
						struct pklcd *lcp = (struct pklcd *)(isop->isop_chan);
						lcp->lcd_flags &= ~X25_DG_CIRCUIT;
					}
#endif
E 6
					hdr->tpdu_cdt = 0;
				}
				hdr->tpdu_CCclass = tp_mask_to_num(tpcb->tp_class);
				hdr->tpdu_CCoptions = 
					(tpcb->tp_xtd_format? TPO_XTD_FMT:0) |
					(tpcb->tp_use_efc? TPO_USE_EFC:0);

				IFPERF(tpcb)
					u_char perf_meas = tpcb->tp_perf_on;
					ADDOPTION(TPP_perf_meas, hdr, sizeof(perf_meas), perf_meas);
				ENDPERF

				if( dutype == CR_TPDU_type ) {
					IncStat(ts_CR_sent);

					ASSERT( tpcb->tp_lsuffixlen > 0 );
					ASSERT( tpcb->tp_fsuffixlen > 0 );

					ADDOPTION(TPP_calling_sufx, hdr,
D 2
						tpcb->tp_lsuffixlen, tpcb->tp_lsuffix);
E 2
I 2
						tpcb->tp_lsuffixlen, tpcb->tp_lsuffix[0]);
E 2
					ADDOPTION(TPP_called_sufx, hdr,
D 2
						tpcb->tp_fsuffixlen, tpcb->tp_fsuffix);
E 2
I 2
						tpcb->tp_fsuffixlen, tpcb->tp_fsuffix[0]);
E 2
				} else {
					IncStat(ts_CC_sent);
				}

				ADDOPTION(TPP_tpdu_size, hdr, 
					sizeof(tpcb->tp_tpdusize), tpcb->tp_tpdusize);

				if (tpcb->tp_class != TP_CLASS_0) {
					short millisec = 500*(tpcb->tp_sendack_ticks);

					millisec = htons(millisec);
					ADDOPTION(TPP_acktime, hdr, sizeof(short), millisec);

					x = (tpcb->tp_use_nxpd? TPAO_USE_NXPD: 0)
					 |	(tpcb->tp_use_rcc?  TPAO_USE_RCC : 0) 
					 |  (tpcb->tp_use_checksum?0: TPAO_NO_CSUM)
					 |	(tpcb->tp_xpd_service? TPAO_USE_TXPD: 0);
					ADDOPTION(TPP_addl_opt, hdr, 1, x);

I 13
					if ((tpcb->tp_l_tpdusize ^ (1 << tpcb->tp_tpdusize)) != 0) {
						u_short size_s = tpcb->tp_l_tpdusize >> 7;
						u_char size_c = size_s;
						ASSERT(tpcb->tp_l_tpdusize < 65536 * 128);
						if (dutype == CR_TPDU_type)
							tpcb->tp_ptpdusize = size_s;
						if (size_s < 256) {
							ADDOPTION(TPP_ptpdu_size, hdr, 1, size_c);
						} else {
							size_s = htons(size_s);
							ADDOPTION(TPP_ptpdu_size, hdr, 2, size_s);
						}
					}
E 13
				}
					
				if( (dutype == CR_TPDU_type) && (tpcb->tp_class != TP_CLASS_0)){

					ASSERT( 1 == sizeof(tpcb->tp_vers) );
					ADDOPTION(TPP_vers, hdr, 1, tpcb->tp_vers);

					/* for each alt protocol class x,
					 * 	x = x<<4;
					 *  option = concat(option, x);
					 * Well, for now we only have TP0 for an
					 * alternative so... this is easy.
					 *
					 * HOWEVER... There should be NO alt protocol
					 * class over CLNS.  Need to see if the route suggests
					 * CONS, and iff so add alt class.
					 */
					x = 0;
					ADDOPTION(TPP_alt_class, hdr, 1, x);
				}

				if( hdr->tpdu_li > MLEN) 
					panic("tp_emit CR/CC");
			}
			break;

		case DR_TPDU_type:
			if( hdr->tpdu_DRdref == 0 ) {
				/* don't issue the DR */
				goto done;
			}
			hdr->tpdu_cdt = 0;
			hdr->tpdu_DRsref = htons(tpcb->tp_lref);
			hdr->tpdu_DRreason = (u_char)eot; /* WHICH BYTE OF THIS??? */

			/* forget the add'l information variable part */
			IncStat(ts_DR_sent);
			break;

		case DC_TPDU_type: /* not used in class 0 */
			ASSERT( tpcb->tp_class != TP_CLASS_0);
			hdr->tpdu_DCsref =  htons(tpcb->tp_lref);
			hdr->tpdu_cdt = 0;
			data = (struct mbuf *)0;
			IncStat(ts_DC_sent);
			break;

		case XAK_TPDU_type: /* xak not used in class 0 */
			ASSERT( tpcb->tp_class != TP_CLASS_0); /* fall through */
			hdr->tpdu_cdt = 0;

			IFTRACE(D_XPD)
				tptraceTPCB(TPPTXack, seq, 0, 0, 0, 0);
			ENDTRACE
			data = (struct mbuf *)0;
			if (tpcb->tp_xtd_format) {
#ifdef BYTE_ORDER
D 7
				hdr->tpdu_XAKseqX = htonl(seq);
E 7
I 7
				union seq_type seqeotX;

				seqeotX.s_seq = seq;
				seqeotX.s_eot = 1;
				hdr->tpdu_seqeotX = htonl(seqeotX.s_seqeot);
E 7
#else
				hdr->tpdu_XAKseqX = seq;
D 17
#endif BYTE_ORDER
E 17
I 17
#endif /* BYTE_ORDER */
E 17
			} else {
				hdr->tpdu_XAKseq = seq;
			}
			IncStat(ts_XAK_sent);
			IncPStat(tpcb, tps_XAK_sent);
			break;

		case XPD_TPDU_type: /* xpd not used in class 0 */
			ASSERT( tpcb->tp_class != TP_CLASS_0); /* fall through */
			hdr->tpdu_cdt = 0;
			if (tpcb->tp_xtd_format) {
#ifdef BYTE_ORDER
				union seq_type seqeotX;

				seqeotX.s_seq = seq;
				seqeotX.s_eot = 1;
				hdr->tpdu_seqeotX = htonl(seqeotX.s_seqeot);
#else
				hdr->tpdu_XPDseqX = seq;
				hdr->tpdu_XPDeotX = 1; /* always 1 for XPD tpdu */
D 17
#endif BYTE_ORDER
E 17
I 17
#endif /* BYTE_ORDER */
E 17
			} else {
				hdr->tpdu_XPDseq = seq;
				hdr->tpdu_XPDeot = 1; /* always 1 for XPD tpdu */
			}
			IncStat(ts_XPD_sent);
			IncPStat(tpcb, tps_XPD_sent);

			/* kludge to test the input size checking */
			IFDEBUG(D_SIZE_CHECK)
D 2
				if(data->m_len <= 16 && data->m_off < (MLEN-18) ) {
E 2
I 2
				/*if(data->m_len <= 16 && data->m_off < (MLEN-18) ) {
E 2
					printf("Sending too much data on XPD: 18 bytes\n");
					data->m_len = 18;
D 2
				}
E 2
I 2
				}*/
E 2
			ENDDEBUG
			break;

		case DT_TPDU_type:
			hdr->tpdu_cdt = 0;
			IFTRACE(D_DATA)
				tptraceTPCB(TPPTmisc, "emit DT: eot seq tpdu_li", eot, seq, 
					hdr->tpdu_li, 0);
			ENDTRACE
			if (tpcb->tp_xtd_format) {
#ifdef BYTE_ORDER
				union seq_type seqeotX;

				seqeotX.s_seq = seq;
				seqeotX.s_eot = eot;
				hdr->tpdu_seqeotX = htonl(seqeotX.s_seqeot);
#else
				hdr->tpdu_DTseqX = seq;
				hdr->tpdu_DTeotX = eot;
D 17
#endif BYTE_ORDER
E 17
I 17
#endif /* BYTE_ORDER */
E 17
			} else if (tpcb->tp_class == TP_CLASS_0) {
				IFDEBUG(D_EMIT)
					printf("DT tpdu: class 0 m 0x%x hdr 0x%x\n", m, hdr);
					dump_buf( hdr, hdr->tpdu_li + 1 );
				ENDDEBUG
				((struct tp0du *)hdr)->tp0du_eot = eot;
				((struct tp0du *)hdr)->tp0du_mbz = 0;
				IFDEBUG(D_EMIT)
					printf("DT 2 tpdu: class 0 m 0x%x hdr 0x%x\n", m, hdr);
					dump_buf( hdr, hdr->tpdu_li + 1 );
				ENDDEBUG
			} else {
				hdr->tpdu_DTseq = seq;
				hdr->tpdu_DTeot = eot;
			}
			if(eot) {
				IncStat(ts_EOT_sent);
			}
			IncStat(ts_DT_sent);
			IncPStat(tpcb, tps_DT_sent);
			break;

		case AK_TPDU_type:/* ak not used in class 0 */
			ASSERT( tpcb->tp_class != TP_CLASS_0); 
			data = (struct mbuf *)0;
D 12
			{ 	SeqNum olduwe = tpcb->tp_sent_uwe;
E 12
I 12
			olduwe = tpcb->tp_sent_uwe;
E 12

I 12
			if (seq != tpcb->tp_sent_rcvnxt || tpcb->tp_rsycnt == 0) {
				LOCAL_CREDIT( tpcb ); 
E 12
				tpcb->tp_sent_uwe = 
					SEQ(tpcb,tpcb->tp_rcvnxt + tpcb->tp_lcredit -1);
D 12
				LOCAL_CREDIT( tpcb ); 
E 12
				tpcb->tp_sent_lcdt = tpcb->tp_lcredit;
I 12
				acking_ooo = 0;
			} else
				acking_ooo = 1;
E 12

D 12
				IFDEBUG(D_RENEG)
					/* occasionally fake a reneging so 
						you can test subsequencing */
					if( olduwe & 0x1 ) {
						tpcb->tp_reneged = 1;
						IncStat(ts_ldebug);
					}
				ENDDEBUG
				/* Are we about to reneg on credit? 
				 * When might we do so?
				 *	a) when using optimistic credit (which we no longer do).
				 *  b) when drain() gets implemented (not in the plans).
				 *  c) when D_RENEG is on.
D 2
				 *  d) when DEC BIT response (PRC_QUENCH2) is implemented.
E 2
I 2
				 *  d) when DEC BIT response is implemented.
E 2
				 *	(not- when we do this, we'll need to implement flow control
				 *	confirmation)
				 */
				if( SEQ_LT(tpcb, tpcb->tp_sent_uwe, olduwe) ) {
E 12
I 12
			IFDEBUG(D_RENEG)
				/* occasionally fake a reneging so 
					you can test subsequencing */
				if( olduwe & 0x1 ) {
E 12
					tpcb->tp_reneged = 1;
D 12
					IncStat(ts_lcdt_reduced);
					IFTRACE(D_CREDIT)
						tptraceTPCB(TPPTmisc, 
							"RENEG: olduwe newuwe lcredit rcvnxt",
							olduwe,
							tpcb->tp_sent_uwe, tpcb->tp_lcredit,
							tpcb->tp_rcvnxt);
					ENDTRACE
E 12
I 12
					IncStat(ts_ldebug);
E 12
				}
I 12
			ENDDEBUG
			/* Are we about to reneg on credit? 
			 * When might we do so?
			 *	a) when using optimistic credit (which we no longer do).
			 *  b) when drain() gets implemented (not in the plans).
			 *  c) when D_RENEG is on.
			 *  d) when DEC BIT response is implemented.
			 *	(not- when we do this, we'll need to implement flow control
			 *	confirmation)
			 */
			if( SEQ_LT(tpcb, tpcb->tp_sent_uwe, olduwe) ) {
				tpcb->tp_reneged = 1;
				IncStat(ts_lcdt_reduced);
				IFTRACE(D_CREDIT)
					tptraceTPCB(TPPTmisc, 
						"RENEG: olduwe newuwe lcredit rcvnxt",
						olduwe,
						tpcb->tp_sent_uwe, tpcb->tp_lcredit,
						tpcb->tp_rcvnxt);
				ENDTRACE
			}
			IFPERF(tpcb)
				/* new lwe is less than old uwe means we're
				 * acking before we received a whole window full
				 */
				if( SEQ_LT( tpcb, tpcb->tp_rcvnxt, olduwe) ) {
					/* tmp1 = number of pkts fewer than the full window */
					register int tmp1 = 
						(int) SEQ_SUB( tpcb, olduwe, tpcb->tp_rcvnxt);
E 12

D 12
				IFPERF(tpcb)
					/* new lwe is less than old uwe means we're
					 * acking before we received a whole window full
					 */
					if( SEQ_LT( tpcb, tpcb->tp_rcvnxt, olduwe) ) {
						/* tmp1 = number of pkts fewer than the full window */
						register int tmp1 = 
							(int) SEQ_SUB( tpcb, olduwe, tpcb->tp_rcvnxt);
E 12
I 12
					if(tmp1 > TP_PM_MAX)
						tmp1 = TP_PM_MAX;
					IncPStat( tpcb,  tps_ack_early[tmp1] );
E 12

D 12
						if(tmp1 > TP_PM_MAX)
							tmp1 = TP_PM_MAX;
						IncPStat( tpcb,  tps_ack_early[tmp1] );
E 12
I 12
					/* tmp1 = amt of new cdt we're advertising */
					tmp1 = SEQ_SUB( tpcb, seq, tpcb->tp_sent_rcvnxt);
					if(tmp1 > TP_PM_MAX )
						tmp1 = TP_PM_MAX;
E 12

D 12
						/* tmp1 = amt of new cdt we're advertising */
						tmp1 = SEQ_SUB( tpcb, seq, tpcb->tp_sent_rcvnxt);
						if(tmp1 > TP_PM_MAX )
							tmp1 = TP_PM_MAX;
E 12
I 12
					IncPStat( tpcb, 
							tps_cdt_acked [ tmp1 ]
							[ ((tpcb->tp_lcredit > TP_PM_MAX)?
								TP_PM_MAX:tpcb->tp_lcredit) ] );
E 12

D 12
						IncPStat( tpcb, 
								tps_cdt_acked [ tmp1 ]
								[ ((tpcb->tp_lcredit > TP_PM_MAX)?
									TP_PM_MAX:tpcb->tp_lcredit) ] );
E 12
I 12
				}
			ENDPERF
E 12

D 12
					}
				ENDPERF
			}
E 12
			IFTRACE(D_ACKSEND)
				tptraceTPCB(TPPTack, seq, tpcb->tp_lcredit, tpcb->tp_sent_uwe, 
					tpcb->tp_r_subseq, 0);
			ENDTRACE
			if (tpcb->tp_xtd_format) {
#ifdef BYTE_ORDER
D 7
				hdr->tpdu_cdt = 0; 
				hdr->tpdu_AKseqX = htonl(seq);
E 7
I 7
				union seq_type seqeotX;

				seqeotX.s_seq = seq;
				seqeotX.s_eot = 0;
				hdr->tpdu_seqeotX = htonl(seqeotX.s_seqeot);
E 7
				hdr->tpdu_AKcdtX = htons(tpcb->tp_lcredit);
#else
				hdr->tpdu_cdt = 0; 
				hdr->tpdu_AKseqX = seq;
				hdr->tpdu_AKcdtX = tpcb->tp_lcredit;
D 17
#endif BYTE_ORDER
E 17
I 17
#endif /* BYTE_ORDER */
E 17
			} else {
				hdr->tpdu_AKseq = seq;
				hdr->tpdu_AKcdt = tpcb->tp_lcredit;
			}
D 12
			if ((tpcb->tp_class == TP_CLASS_4) && tpcb->tp_reneged ) {
E 12
I 12
			if ((tpcb->tp_class == TP_CLASS_4) &&
				(tpcb->tp_reneged || acking_ooo)) {
E 12
				/* 
				 * Ack subsequence parameter req'd if WE reneged on 
				 * credit offered.  (ISO 8073, 12.2.3.8.2, p. 74)
				 */
				IFDEBUG(D_RENEG)
					printf("Adding subseq 0x%x\n", tpcb->tp_s_subseq);
				ENDDEBUG
				tpcb->tp_s_subseq++;
				/*
				 * add tmp subseq and do a htons on it.
				 */
				ADDOPTION(TPP_subseq, hdr, 
					sizeof(tpcb->tp_s_subseq), tpcb->tp_s_subseq);
			} else
				tpcb->tp_s_subseq = 0;

			if ( tpcb->tp_sendfcc || eot ) /* overloaded to mean SEND FCC */ {
				/* 
				 * Rules for sending FCC ("should" send when) :
				 * %a) received an ack from peer with NO NEWS whatsoever,
				 *  	and it did not contain an FCC
				 * 	b) received an ack from peer that opens its closed window.
				 * 	c) received an ack from peer after it reneged on its
				 *		offered credit, AND this ack raises UWE but LWE is same
				 *		and below UWE at time of reneging (reduction)
				 * Now, ISO 8073 12.2.3.8.3 says
				 * that a retransmitted AK shall not contain the FCC
				 * parameter.  Now, how the hell you tell the difference 
				 * between a retransmitted ack and an ack that's sent in 
				 * response to a received ack, I don't know, because without
				 * any local activity, and w/o any received DTs, they
				 * will contain exactly the same credit/seq# information.
				 * Anyway, given that the "retransmission of acks"
				 * procedure (ISO 8073 12.2.3.8.3) is optional, and we
				 * don't do it (although the peer can't tell that), we 
				 * ignore this last rule.
				 *
				 * We send FCC for reasons a) and b) only. 
				 * To add reason c) would require a ridiculous amount of state.
				 * 
				 */
				u_short 	bogus[4]; /* lwe(32), subseq(16), cdt(16) */
				SeqNum		lwe;
				u_short		subseq, fcredit;

				tpcb->tp_sendfcc = 0;

				lwe = (SeqNum) htonl(tpcb->tp_snduna);
				subseq = htons(tpcb->tp_r_subseq);
				fcredit = htons(tpcb->tp_fcredit);

D 2
				bcopy((caddr_t) &lwe, &bogus[0], sizeof(SeqNum));
				bcopy((caddr_t) &subseq, &bogus[2], sizeof(u_short));
				bcopy((caddr_t) &fcredit, &bogus[3], sizeof(u_short));
E 2
I 2
				bcopy((caddr_t) &lwe, (caddr_t)&bogus[0], sizeof(SeqNum));
				bcopy((caddr_t) &subseq, (caddr_t)&bogus[2], sizeof(u_short));
				bcopy((caddr_t) &fcredit, (caddr_t)&bogus[3], sizeof(u_short));
E 2

				IFTRACE(D_ACKSEND)
					tptraceTPCB(TPPTmisc, 
						"emit w/FCC: snduna r_subseq fcredit", 
						tpcb->tp_snduna, tpcb->tp_r_subseq,
						tpcb->tp_fcredit, 0);
				ENDTRACE

				IFDEBUG(D_ACKSEND)
					printf("Calling ADDOPTION 0x%x, 0x%x, 0x%x,0x%x\n",
						TPP_flow_cntl_conf, 
						hdr, sizeof(bogus), bogus[0]);
				ENDDEBUG
				ADDOPTION(TPP_flow_cntl_conf, hdr, sizeof(bogus), bogus[0]);
				IFDEBUG(D_ACKSEND)
					printf("after ADDOPTION hdr 0x%x hdr->tpdu_li 0x%x\n",
						hdr, hdr->tpdu_li);
					printf(
					"after ADDOPTION csum_offset 0x%x, hdr->tpdu_li 0x%x\n",
							csum_offset, hdr->tpdu_li);
				ENDDEBUG
					
			}
			tpcb->tp_reneged = 0;
			tpcb->tp_sent_rcvnxt = seq;
D 12
			tp_ctimeout(tpcb->tp_refp, TM_sendack, 
				(int)tpcb->tp_keepalive_ticks);
E 12
I 12
			if (tpcb->tp_fcredit == 0) {
				int timo = tpcb->tp_keepalive_ticks;
				if (tpcb->tp_rxtshift < TP_MAXRXTSHIFT)
					tpcb->tp_rxtshift++;
				timo = min(timo, ((int)tpcb->tp_dt_ticks) << tpcb->tp_rxtshift);
				tp_ctimeout(tpcb, TM_sendack, timo);
			} else
				tp_ctimeout(tpcb, TM_sendack, tpcb->tp_keepalive_ticks);
E 12
			IncStat(ts_AK_sent);
			IncPStat(tpcb, tps_AK_sent);
			IFDEBUG(D_ACKSEND)
				printf(
				"2 after rADDOPTION csum_offset 0x%x, hdr->tpdu_li 0x%x\n",
						csum_offset, hdr->tpdu_li);
			ENDDEBUG
			break;

		case ER_TPDU_type:
			hdr->tpdu_ERreason = eot; 
			hdr->tpdu_cdt = 0;
			/* no user data */
			data = (struct mbuf *)0;
			IncStat(ts_ER_sent);
			break;
		}

	}
	ASSERT( ((int)hdr->tpdu_li > 0) && ((int)hdr->tpdu_li < MLEN) );

	m->m_next = data;

D 2
	ASSERT( hdr->tpdu_li < MMAXOFF ); /* leave this in */
E 2
I 2
	ASSERT( hdr->tpdu_li < MLEN ); /* leave this in */
E 2
	ASSERT( hdr->tpdu_li != 0 ); /* leave this in */

	m->m_len = hdr->tpdu_li ; 
	hdr->tpdu_li --; /* doesn't include the li field */

	datalen = m_datalen( m ); /* total len */

	ASSERT( datalen <= tpcb->tp_l_tpdusize ); /* may become a problem
				when CLNP is used; leave in here for the time being */
		IFDEBUG(D_ACKSEND)
			printf(
			"4 after rADDOPTION csum_offset 0x%x, hdr->tpdu_li 0x%x\n",
					csum_offset, hdr->tpdu_li);
		ENDDEBUG
	if( datalen > tpcb->tp_l_tpdusize ) {
		printf("data len 0x%x tpcb->tp_l_tpdusize 0x%x\n", 
			datalen, tpcb->tp_l_tpdusize);
	}
	IFDEBUG(D_EMIT)
		printf(
		"tp_emit before gen_csum m_len 0x%x, csum_offset 0x%x, datalen 0x%x\n",
		m->m_len, csum_offset, datalen);
	ENDDEBUG
	if( tpcb->tp_use_checksum || 
		(dutype == CR_TPDU_type && (tpcb->tp_class & TP_CLASS_4)) ) {
		iso_gen_csum(m, csum_offset, datalen);
	}

	IFDEBUG(D_EMIT)
	printf("tp_emit before tpxxx_output tpcb 0x%x, dutype 0x%x, datalen 0x%x\n",
		tpcb, dutype, datalen);
D 2
		dump_buf( m, datalen+12);
E 2
I 2
		dump_buf(mtod(m, caddr_t), datalen);
E 2
	ENDDEBUG

	IFPERF(tpcb)
		if( dutype == DT_TPDU_type ) {
			PStat(tpcb, Nb_to_ll) += (datalen - m->m_len);
D 2
			tpmeas( tpcb->tp_lref, TPtime_to_ll,  0,
E 2
I 2
			tpmeas( tpcb->tp_lref, TPtime_to_ll,  (struct timeval *)0,
E 2
				seq, PStat(tpcb, Nb_to_ll), (datalen - m->m_len));
		}
	ENDPERF

	IFTRACE(D_EMIT)
		tptraceTPCB(TPPTtpduout, dutype, hdr, hdr->tpdu_li+1, datalen, 0);
	ENDTRACE
	IFDEBUG(D_EMIT)
		printf("OUTPUT: tpcb 0x%x, isop 0x%x, so 0x%x\n",
			tpcb,  tpcb->tp_npcb,  tpcb->tp_sock);
	ENDDEBUG

	{ extern char tp_delay;

		if( tp_delay )
			if( tpcb->tp_use_checksum == 0 ) {
				register u_int i  = tp_delay;
				for (; i!= 0; i--)
					(void) iso_check_csum(m, datalen);
			}
	}
	ASSERT( m->m_len > 0 );
	error = (tpcb->tp_nlproto->nlp_output)(tpcb->tp_npcb, m, datalen,
		!tpcb->tp_use_checksum);
	IFDEBUG(D_EMIT)
		printf("OUTPUT: returned 0x%x\n", error);
	ENDDEBUG
	IFTRACE(D_EMIT)
		tptraceTPCB(TPPTmisc, 
			"tp_emit nlproto->output netservice returns datalen", 
			tpcb->tp_nlproto->nlp_output, tpcb->tp_netservice, error, datalen); 
	ENDTRACE
done:
D 12
	if( error == E_CO_QFULL ) {
D 2
		tp_quench( tpcb );
E 2
I 2
		tp_quench(tpcb, PRC_QUENCH);
E 2
		return 0;
E 12
I 12
	if (error) {
		if (dutype == AK_TPDU_type)
			tp_ctimeout(tpcb, TM_sendack, 1);
		if (error == E_CO_QFULL) {
			tp_quench(tpcb, PRC_QUENCH);
			return 0;
		}
E 12
	}
	return error;
}
D 2

E 2
/*
 * NAME:		tp_error_emit()
 * CALLED FROM:	tp_input() when a DR or ER is to be issued in
 * 		response to an input error.
 * FUNCTION and ARGUMENTS:
 * 		The error type is the first argument.
 * 		The argument (sref) is the source reference on the bad incoming tpdu,
 * 		and is used for a destination reference on the outgoing packet.
 * 		(faddr) and (laddr) are the foreign and local addresses for this 
 *		connection.
 * 		(erdata) is a ptr to the errant incoming tpdu, and is copied into the
 * 		outgoing ER, if an ER is to be issued.
 * 		(erlen)  is the number of octets of the errant tpdu that we should
 * 		try to copy.
 * 		(tpcb) is the pcb that describes the connection for which the bad tpdu
 * 		arrived.
 * RETURN VALUES:
 * 		0 OK
 *  	ENOBUFS
 *  	E* from net layer datagram output routine
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */

int
tp_error_emit(error, sref, faddr, laddr, erdata, erlen, tpcb, cons_channel,
	dgout_routine)
	int				error;
	u_long			sref;
	struct sockaddr_iso *faddr, *laddr;
	struct mbuf 	*erdata;
	int 			erlen;
	struct tp_pcb 	*tpcb;
D 10
	int 			cons_channel;
E 10
I 10
	caddr_t			cons_channel;
E 10
	int				(*dgout_routine)();
{
	int						dutype;
	int 					datalen = 0;
	register struct tpdu	*hdr; 
	register struct mbuf	*m;
	int						csum_offset;

	IFTRACE(D_ERROR_EMIT)
		tptrace(TPPTmisc, "tp_error_emit error sref tpcb erlen", 
			error, sref, tpcb, erlen);
	ENDTRACE
	IFDEBUG(D_ERROR_EMIT)
		printf(
		"tp_error_emit error 0x%x sref 0x%x tpcb 0x%x erlen 0x%x chan 0x%x\n", 
			error, sref, tpcb, erlen, cons_channel);
	ENDDEBUG

	MGET(m, M_DONTWAIT, TPMT_TPHDR); 
	if (m == NULL) {
		return ENOBUFS;
	}
	m->m_len = sizeof(struct tpdu);
	m->m_act = MNULL;

	hdr = mtod(m, struct tpdu *);

	IFDEBUG(D_ERROR_EMIT)
		printf("[error 0x%x] [error&0xff  0x%x] [(char)error 0x%x]\n",
			error, error&0xff, (char)error);
	ENDDEBUG

D 5
	error &= 0xff;
E 5

D 5
	if( error & 0x40 ) {
E 5
I 5
	if (error & TP_ERROR_SNDC)
		dutype = DC_TPDU_type;
	else if (error & 0x40) {
E 5
		error &= ~0x40;
		dutype = ER_TPDU_type;
	} else
		dutype = DR_TPDU_type;
I 5
	error &= 0xff;
E 5

	hdr->tpdu_type = dutype;
	hdr->tpdu_cdt = 0;

	switch( dutype ) {

I 5
	case DC_TPDU_type:
		IncStat(ts_DC_sent);
		hdr->tpdu_li = 6;
		hdr->tpdu_DCdref = htons(sref);
		hdr->tpdu_DCsref = tpcb ? htons(tpcb->tp_lref) : 0;
		IFDEBUG(D_ERROR_EMIT)
			printf("DC case:\n");
			dump_buf( hdr, 6);
		ENDDEBUG
		/* forget the add'l information variable part */
		break;

E 5
	case DR_TPDU_type:
		IncStat(ts_DR_sent);
		hdr->tpdu_li = 7;
		hdr->tpdu_DRdref = htons(sref);
D 5
		hdr->tpdu_DRsref = htons(0);
E 5
I 5
		hdr->tpdu_DRsref = 0;
E 5
		hdr->tpdu_DRreason = (char)error;
		IFDEBUG(D_ERROR_EMIT)
			printf("DR case:\n");
			dump_buf( hdr, 7);
		ENDDEBUG
		/* forget the add'l information variable part */
		break;

	case ER_TPDU_type:
		IncStat(ts_ER_sent);
		hdr->tpdu_li = 5; 
		hdr->tpdu_ERreason = (char)error;
I 10
		hdr->tpdu_ERdref = htons(sref);
E 10
		break;

	default:
		ASSERT(0);
		printf("TP PANIC: bad dutype 0x%x\n", dutype);
	}

	if(tpcb)
		if( tpcb->tp_use_checksum ) {
			ADDOPTION(TPP_checksum, hdr, 2, csum_offset /* dummy argument */); 
			csum_offset =  hdr->tpdu_li - 2;
		}

D 2
	ASSERT( hdr->tpdu_li < MMAXOFF );
E 2
I 2
	ASSERT( hdr->tpdu_li < MLEN ); 
E 2

	if (dutype == ER_TPDU_type) {
		/* copy the errant tpdu into another 'variable part' */
		register caddr_t P;

		IFTRACE(D_ERROR_EMIT)
			tptrace(TPPTmisc, "error_emit ER len tpduli", erlen, hdr->tpdu_li,
				0,0);
		ENDTRACE
		IFDEBUG(D_ERROR_EMIT)
			printf("error_emit ER len 0x%x tpduli 0x%x\n", erlen, hdr->tpdu_li);
		ENDDEBUG

		/* copy at most as many octets for which you have room */
		if (erlen + hdr->tpdu_li + 2 > TP_MAX_HEADER_LEN)
			erlen = TP_MAX_HEADER_LEN - hdr->tpdu_li - 2;
			
		/* add the "invalid tpdu" parameter : required in class 0 */
		P = (caddr_t)hdr + (int)(hdr->tpdu_li);
		vbptr(P)->tpv_code =  TPP_invalid_tpdu; /* parameter code */
		vbptr(P)->tpv_len = erlen;	/* parameter length */
		m->m_len = hdr->tpdu_li + 2; /* 1 for code, 1 for length */

		/* tp_input very likely handed us an mbuf chain w/ nothing in
		 * the first mbuf and the data following the empty mbuf
		 */
		if(erdata->m_len == 0) {
			erdata = m_free(erdata); /* returns the next mbuf on the chain */
		}
D 2
		m->m_next = m_copy(erdata, 0, erlen); /* copy only up to the
					bad octet (or max that will fit in a header */
E 2
I 2
		/*
		 * copy only up to the bad octet
		 * (or max that will fit in a header
		 */
		m->m_next = m_copy(erdata, 0, erlen);
E 2
		hdr->tpdu_li += erlen + 2; 
		m_freem(erdata);
	} else {
		IFDEBUG(D_ERROR_EMIT)
			printf("error_emit DR error tpduli 0x%x\n", error, hdr->tpdu_li);
			dump_buf( (char *)hdr, hdr->tpdu_li );
		ENDDEBUG
		m->m_len = hdr->tpdu_li ;
		m_freem(erdata);
	}

	hdr->tpdu_li --;
	IFTRACE(D_ERROR_EMIT)
		tptrace(TPPTtpduout, 2, hdr, hdr->tpdu_li+1, 0, 0);
	ENDTRACE

	datalen = m_datalen( m);
D 11

	if(tpcb) {
E 11
I 11
	if (tpcb) {
E 11
		if( tpcb->tp_use_checksum ) {
			IFTRACE(D_ERROR_EMIT)
				tptrace(TPPTmisc, "before gen csum datalen", datalen,0,0,0);
			ENDTRACE
			IFDEBUG(D_ERROR_EMIT)
				printf("before gen csum datalen 0x%x, csum_offset 0x%x\n", 
					datalen, csum_offset);
			ENDDEBUG

			iso_gen_csum(m, csum_offset, datalen);
		}

		IFDEBUG(D_ERROR_EMIT)
			printf("OUTPUT: tpcb 0x%x, isop 0x%x, so 0x%x\n",
				tpcb,  tpcb->tp_npcb,  tpcb->tp_sock);
		ENDDEBUG
D 11
		/* Problem: if packet comes in on ISO but sock is listening
		 * in INET, this assertion will fail.
		 * Have to believe the argument, not the nlp_proto.
		ASSERT( tpcb->tp_nlproto->nlp_dgoutput == dgout_routine );
		 */
E 11
I 11
	}
	if (cons_channel) {
#ifdef TPCONS
		struct pklcd *lcp = (struct pklcd *)cons_channel;
		struct isopcb *isop = (struct isopcb *)lcp->lcd_upnext;
E 11

I 11
		tpcons_dg_output(cons_channel, m, datalen);
		/* was if (tpcb == 0) iso_pcbdetach(isop); */
		/* but other side may want to try again over same VC,
		   so, we'll depend on him closing it, but in case it gets forgotten
		   we'll mark it for garbage collection */
		lcp->lcd_flags |= X25_DG_CIRCUIT;
E 11
		IFDEBUG(D_ERROR_EMIT)
I 11
			printf("OUTPUT: dutype 0x%x channel 0x%x\n",
				dutype, cons_channel);
		ENDDEBUG
#else
		printf("TP panic! cons channel 0x%x but not cons configured\n",
			cons_channel);
#endif
	} else if (tpcb) {

		IFDEBUG(D_ERROR_EMIT)
E 11
			printf("tp_error_emit 1 sending DG: Laddr\n");
D 2
			dump_isoaddr( laddr );
E 2
I 2
			dump_addr((struct sockaddr *)laddr);
E 2
			printf("Faddr\n");
D 2
			dump_isoaddr( faddr );
E 2
I 2
			dump_addr((struct sockaddr *)faddr);
E 2
		ENDDEBUG
		return (tpcb->tp_nlproto->nlp_dgoutput)(
			&laddr->siso_addr, 
			&faddr->siso_addr, 
			m, datalen, 
					/* no route */	(caddr_t)0, !tpcb->tp_use_checksum); 
D 11
	} else  {
		if( cons_channel ) {
D 6
#if NARGOXTWENTYFIVE > 0
D 2
#include "../netiso/cons.h"
E 2
I 2
#include "cons.h"
E 2
			/* This is unfortunate...
				cons_send_on_vc(cons_channel, m, datalen);
			*/
			cons_netcmd( CONN_CLOSE, (struct isopcb *)0, 
				cons_channel, CONS_NOT_DGM);
E 6
I 6
#ifdef TPCONS
			tpcons_dg_output(cons_channel, m, datalen);
			pk_disconnect((struct pklcd *)cons_channel);
E 11
I 11
	} else if (dgout_routine) {
E 11
E 6
			IFDEBUG(D_ERROR_EMIT)
D 11
				printf("OUTPUT: dutype 0x%x channel 0x%x\n",
					dutype, cons_channel);
			ENDDEBUG
D 6
#else NARGOXTWENTYFIVE
E 6
I 6
#else
E 6
			printf("TP panic! cons channel 0x%x but not cons configured\n",
				cons_channel);
D 6
#endif NARGOXTWENTYFIVE > 0
E 6
I 6
#endif
E 6
		} else {
D 2
#ifndef nodef
E 2
I 2
#ifndef notdef
E 2
			IFDEBUG(D_ERROR_EMIT)
E 11
				printf("tp_error_emit sending DG: Laddr\n");
D 2
				dump_isoaddr( laddr );
E 2
I 2
				dump_addr((struct sockaddr *)laddr);
E 2
				printf("Faddr\n");
D 2
				dump_isoaddr( laddr );
E 2
I 2
				dump_addr((struct sockaddr *)faddr);
E 2
			ENDDEBUG
D 11
			return (*dgout_routine)( &laddr->siso_addr, &faddr->siso_addr, 
				m, datalen, /* no route */ 
				(caddr_t)0, /* nochecksum==false */0);
D 2
#else nodef
E 2
I 2
#else notdef
E 11
I 11
				return (*dgout_routine)( &laddr->siso_addr, &faddr->siso_addr, 
					m, datalen, /* no route */ 
					(caddr_t)0, /* nochecksum==false */0);
	} else {
E 11
E 2
			IFDEBUG(D_ERROR_EMIT)
				printf("tp_error_emit DROPPING \n", m);
			ENDDEBUG
			IncStat(ts_send_drop);
			m_freem(m);
			return 0;
D 2
#endif nodef
E 2
I 2
D 11
#endif notdef
E 2
		}
E 11
	}
}
E 1
