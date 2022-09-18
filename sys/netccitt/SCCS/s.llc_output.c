h00855
s 00002/00002/00276
d D 8.1 93/06/10 22:53:24 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00278/00000/00000
d D 7.1 92/12/08 17:36:05 sklower 1 0
c date and time created 92/12/08 17:36:05 by sklower
e
u
U
t
T
I 1
/* 
 * Copyright (C) Dirk Husemann, Computer Science Department IV, 
 * 		 University of Erlangen-Nuremberg, Germany, 1990, 1991, 1992
D 2
 * Copyright (c) 1992   Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 * 
 * This code is derived from software contributed to Berkeley by
 * Dirk Husemann and the Computer Science Department (IV) of
 * the University of Erlangen-Nuremberg, Germany.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_llc.h>
#include <net/route.h>

#include <netccitt/dll.h>
#include <netccitt/llc_var.h>

/*
 * llc_output() --- called by an upper layer (network layer) entity whenever
 *                  there is an INFO frame to be transmitted. We enqueue the
 *                  info frame and call llc_start() to do the actual sending.
 */

llc_output(struct llc_linkcb *linkp, struct mbuf *m)
{
	register int i;

	i = splimp();
	LLC_ENQUEUE(linkp, m);
	llc_start(linkp);
	splx(i);

}


/*
 * llc_start() --- We try to subsequently dequeue all the frames available and
 *                 send them out.
 */
void
llc_start(struct llc_linkcb *linkp)
{
	register int i;
	register struct mbuf *m;
	int action;

	while ((LLC_STATEEQ(linkp, NORMAL) || LLC_STATEEQ(linkp, BUSY) ||
		LLC_STATEEQ(linkp, REJECT)) && 
	       (linkp->llcl_slotsfree > 0) && 
	       (LLC_GETFLAG(linkp, REMOTE_BUSY) == 0)) {
		LLC_DEQUEUE(linkp, m);
		if (m == NULL)
			break;
		LLC_SETFRAME(linkp, m);
		(void)llc_statehandler(linkp, (struct llc *) 0, NL_DATA_REQUEST, 
				       0, 0);
	}
}


/*
 * llc_send() --- Handles single frames. If dealing with INFO frames we need to
 *                prepend the LLC header, otherwise we just allocate an mbuf.
 *                In both cases the actual send is done by llc_rawsend().
 */
llc_send(struct llc_linkcb *linkp, int frame_kind, int cmdrsp, int pollfinal)
{
	register struct mbuf *m = (struct mbuf *)0;
	register struct llc *frame;

	if (frame_kind == LLCFT_INFO)
		m = linkp->llcl_output_buffers[llc_seq2slot(linkp,
							    linkp->llcl_vs)];
	LLC_GETHDR(frame, m);

	/* pass it on to llc_rawsend() */
	llc_rawsend(linkp, m, frame, frame_kind, linkp->llcl_vs, cmdrsp, pollfinal);

	if (frame_kind == LLCFT_INFO)
		LLC_INC(linkp->llcl_vs);

	return 0;
}

/* 
 * llc_resend() --- llc_resend() retransmits all unacknowledged INFO frames.
 */
llc_resend(struct llc_linkcb *linkp, int cmdrsp, int pollfinal)
{
	register struct llc *frame;
	register struct mbuf *m;
	register int seq, slot;

	if (linkp->llcl_slotsfree < linkp->llcl_window)
		/* assert lock between nr_received & V(S) */
		if (linkp->llcl_nr_received != linkp->llcl_vs)
			panic("llc: V(S) != N(R) received\n");

		for (slot = llc_seq2slot(linkp, linkp->llcl_vs);
		     slot != linkp->llcl_freeslot; 
		     LLC_INC(linkp->llcl_vs), 
		     slot = llc_seq2slot(linkp, linkp->llcl_vs)) {
			m = linkp->llcl_output_buffers[slot];
			LLC_GETHDR(frame, m);
			llc_rawsend(linkp, m, frame, LLCFT_INFO, linkp->llcl_vs, 
				    cmdrsp, pollfinal);
			pollfinal = 0;
		}
	
	return 0;
}

/*
 * llc_rawsend() --- constructs an LLC frame and sends it out via the
 *                   associated interface of the link control block.
 *
 * We need to make sure that outgoing frames have the correct length,
 * in particular the 4 byte ones (RR, RNR, REJ) as LLC_GETHDR() will
 * set the mbuf len to 3 as default len for non INFO frames ...
 *
 * Frame kind             Length (w/o MAC header, {D,S}SAP incl.)
 * --------------------------------------------------------------
 * DISC, SABME, UA, DM    3 bytes  ({D,S}SAP + CONTROL)
 * RR, RNR, REJ           4 bytes  ({D,S}SAP + CONTROL0 + CONTROL1)
 * XID                    6 bytes  ({D,S}SAP + CONTROL0 + FI,CLASS,WINDOW)
 * FRMR                   7 bytes  ({D,S}SAP + CONTROL0 + REJ CONTROL,V(S),V(R),CAUSE)
 * INFO                   4 -- MTU
 * UI, TEST               3 -- MTU
 *
 */
#define LLC_SETLEN(m, l) (m)->m_pkthdr.len = (m)->m_len = (l)

llc_rawsend(struct llc_linkcb *linkp, struct mbuf *m, struct llc *frame,
	    int frame_kind, int vs, int cmdrsp, int pollfinal)
{
	register short adjust = LLC_UFRAMELEN;
	struct ifnet *ifp;

	switch (frame_kind) {
	/* supervisory and information frames */
	case LLCFT_INFO:
		frame->llc_control = LLC_INFO;
		LLCSBITS(frame->llc_control, i_ns, vs);
		LLCSBITS(frame->llc_control_ext, i_nr, linkp->llcl_vr);
		adjust = LLC_ISFRAMELEN;
		break;
	case LLCFT_RR:
		frame->llc_control = LLC_RR;
		LLC_SETLEN(m, LLC_ISFRAMELEN);
		LLCSBITS(frame->llc_control_ext, s_nr, linkp->llcl_vr);
		adjust = LLC_ISFRAMELEN;
		break;
	case LLCFT_RNR:
		frame->llc_control = LLC_RNR;
		LLC_SETLEN(m, LLC_ISFRAMELEN);
		LLCSBITS(frame->llc_control_ext, s_nr, linkp->llcl_vr);
		adjust = LLC_ISFRAMELEN;
		break;
	case LLCFT_REJ:
		frame->llc_control = LLC_REJ;
		LLC_SETLEN(m, LLC_ISFRAMELEN);
		LLCSBITS(frame->llc_control_ext, s_nr, linkp->llcl_vr);
		adjust = LLC_ISFRAMELEN;
		break;
	/* unnumbered frames */
	case LLCFT_DM:
		frame->llc_control = LLC_DM;
		break;
	case LLCFT_SABME:
		frame->llc_control = LLC_SABME;
		break;
	case LLCFT_DISC:
		frame->llc_control = LLC_DISC;
		break;
	case LLCFT_UA:
		frame->llc_control = LLC_UA;
		break;
	case LLCFT_UI:
		frame->llc_control = LLC_UI;
		break;
	case LLCFT_FRMR:
		frame->llc_control = LLC_FRMR;
		/* get more space --- FRMR frame are longer then usual */
		LLC_SETLEN(m, LLC_FRMRLEN);
		bcopy((caddr_t) &linkp->llcl_frmrinfo, 
		      (caddr_t) &frame->llc_frmrinfo,
		      sizeof(struct frmrinfo));
		break;
	default:
		/*
		 * We don't send {XID, TEST} frames
		 */
		if (m)
			m_freem(m);
		return;
	}
 
	/* 
	 * Fill in DSAP/SSAP
	 */
	frame->llc_dsap = frame->llc_ssap = LLSAPADDR(&linkp->llcl_addr);
	frame->llc_ssap |= cmdrsp;

	/*
	 * Check for delayed action pending. ISO 8802-2, 7.9.2 (5)
	 * and ISO 8802-2, 7.9.2.3 (32), (34), (36) pertain to this
	 * piece of code --- hopefully we got it right here (i.e.
	 * in the spirit of (32), (34), and (36) ...
	 */
	switch (frame_kind) {
	case LLCFT_RR:
	case LLCFT_RNR:
	case LLCFT_REJ:
	case LLCFT_INFO:
		switch (LLC_GETFLAG(linkp, DACTION)) {
		case LLC_DACKCMD:
		case LLC_DACKRSP:
			LLC_STOPTIMER(linkp, DACTION);
			break;
		case LLC_DACKCMDPOLL:
			if (cmdrsp == LLC_CMD) {
				pollfinal = 1;
				LLC_STOPTIMER(linkp, DACTION);
			}
			break;
		case LLC_DACKRSPFINAL:
			if (cmdrsp == LLC_RSP) {
				pollfinal = 1;
				LLC_STOPTIMER(linkp, DACTION);
			}
			break;
		}
		break;
	}
	 
	if (adjust == LLC_UFRAMELEN)
		LLCSBITS(frame->llc_control, u_pf, pollfinal);
	else LLCSBITS(frame->llc_control_ext, s_pf, pollfinal);

	/*
	 * Get interface to send frame onto
	 */
	ifp = linkp->llcl_if;
	if (frame_kind == LLCFT_INFO) {
		/* 
		 * send out a copy of the frame, retain the
		 * original
		 */
		(*ifp->if_output)(ifp, m_copy(m, 0, (int)M_COPYALL),
				  rt_key(linkp->llcl_nlrt),
				  linkp->llcl_nlrt);
		/*
		 * Account for the LLC header and let it ``disappear''
		 * as the raw info frame payload is what we hold in
		 * the output_buffers of the link.
		 */
		m_adj(m, LLC_ISFRAMELEN);
	} else (*ifp->if_output)(ifp, m, 
				 rt_key(linkp->llcl_nlrt),
				 linkp->llcl_nlrt);
}

E 1
