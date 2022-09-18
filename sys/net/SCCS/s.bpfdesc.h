h59966
s 00002/00002/00070
d D 8.1 93/06/10 22:44:24 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00068
d D 7.6 93/06/04 17:31:46 bostic 9 8
c prototype everything
e
s 00005/00001/00063
d D 7.5 92/06/07 19:33:10 mccanne 8 7
c update from helios -- don't break sunos compat
e
s 00001/00002/00063
d D 7.4 92/02/15 18:05:19 mckusick 7 6
c use selrecord and selwakeup to implement selecting
e
s 00005/00031/00060
d D 7.3 91/10/29 19:58:55 mccanne 6 5
c restore sccs keywords
e
s 00034/00004/00057
d D 7.2 91/10/27 21:29:09 mccanne 5 4
c added bd_timedout
e
s 00009/00020/00052
d D 7.1 91/05/07 09:18:37 bostic 4 3
c new copyright; att/bsd/shared
e
s 00006/00014/00066
d D 1.3 91/05/05 22:52:37 mccanne 3 2
c added next field to bpf_if for dynamic allocation
e
s 00010/00007/00070
d D 1.2 91/05/02 11:05:58 mccanne 2 1
c checkpoint before porting new insn format from horse
e
s 00077/00000/00000
d D 1.1 91/03/22 16:05:35 mccanne 1 0
c date and time created 91/03/22 16:05:35 by mccanne
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1990 The Regents of the University of California.
E 4
I 4
D 6
/*-
 * Copyright (c) 1991 The Regents of the University of California.
E 6
I 6
/*
D 10
 * Copyright (c) 1990, 1991 Regents of the University of California.
E 6
E 4
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 4
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * This code is derived from the Stanford/CMU enet packet filter,
 * (net/enet.c) distributed as part of 4.3BSD, and code contributed
D 5
 * to Berkeley by Steven McCanne of Lawrence Berkeley Laboratory.
E 5
I 5
D 6
 * to Berkeley by Steven McCanne and Van Jacobson both of Lawrence 
E 6
I 6
 * to Berkeley by Steven McCanne and Van Jacobson both of Lawrence
E 6
 * Berkeley Laboratory.
E 5
E 4
 *
D 4
 * @(#) $Header: bpfdesc.h,v 1.7 90/12/04 01:05:01 mccanne Exp $ (LBL)
E 4
I 4
D 5
 * %sccs.include.redist.c%
E 5
I 5
D 6
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 *
D 4
 * This code is derived from the Stanford/CMU enet packet filter,
 * (net/enetdefs.h) distributed in 4.3BSD Unix.
E 4
I 4
D 5
 *	%W% (Berkeley) %G%
E 5
I 5
D 6
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 5
 *
D 5
 * @(#) $Header: bpfdesc.h,v 1.7 90/12/04 01:05:01 mccanne Exp $ (LBL)
E 5
I 5
 *	@(#)bpfdesc.h	7.1 (Berkeley) 5/7/91
E 6
I 6
 *      %W% (Berkeley) %G%
E 6
 *
 * @(#) $Header: bpfdesc.h,v 1.9 91/10/27 21:22:38 mccanne Exp $ (LBL)
E 5
E 4
 */

/*
 * Descriptor associated with each open bpf file.
 */
struct bpf_d {
	struct bpf_d	*bd_next;	/* Linked list of descriptors */
	/*
	 * Buffer slots: two mbuf clusters buffer the incoming packets.
	 *   The model has three slots.  Sbuf is always occupied.
	 *   sbuf (store) - Receive interrupt puts packets here.
	 *   hbuf (hold) - When sbuf is full, put cluster here and
	 *                 wakeup read (replace sbuf with fbuf).
	 *   fbuf (free) - When read is done, put cluster here.
	 * On receiving, if sbuf is full and fbuf is 0, packet is dropped.
	 */
D 2
	struct mbuf *	bd_sbuf;	/* store slot */
	struct mbuf *	bd_hbuf;	/* hold slot */
	struct mbuf *	bd_fbuf;	/* free slot */
E 2
I 2
	caddr_t		bd_sbuf;	/* store slot */
	caddr_t		bd_hbuf;	/* hold slot */
	caddr_t		bd_fbuf;	/* free slot */
	int 		bd_slen;	/* current length of store buffer */
	int 		bd_hlen;	/* current length of hold buffer */
E 2

I 2
	int		bd_bufsize;	/* absolute length of buffers */

E 2
	struct bpf_if *	bd_bif;		/* interface descriptor */
	u_long		bd_rtout;	/* Read timeout in 'ticks' */
D 2
	struct mbuf *	bd_filterm;	/* Packet filter mbuf */
	struct bpf_insn *bd_filter; 	/* precomputed pointer to fcode */
E 2
I 2
	struct bpf_insn *bd_filter; 	/* filter code */
E 2
	u_long		bd_rcount;	/* number of packets received */
	u_long		bd_dcount;	/* number of packets dropped */
D 2
	struct proc *	bd_SelProc;	/* process that last selected us */
E 2
I 2
D 7
	struct proc *	bd_selproc;	/* process that last selected us */
E 7
I 7
D 8
	struct selinfo	bd_selproc;	/* process that last selected us */
E 8
E 7
E 2

	u_char		bd_promisc;	/* true if listening promiscuously */
	u_char		bd_state;	/* idle, waiting, or timed out */
D 2
	u_char		bd_SelColl;	/* true if selects collide */
E 2
I 2
D 7
	u_char		bd_selcoll;	/* true if selects collide */
E 7
E 2
	u_char		bd_immediate;	/* true to return on packet arrival */
I 5
#if BSD < 199103
I 8
	u_char		bd_selcoll;	/* true if selects collide */
E 8
	int		bd_timedout;
I 8
	struct proc *	bd_selproc;	/* process that last selected us */
#else
	u_char		bd_pad;		/* explicit alignment */
	struct selinfo	bd_sel;		/* bsd select info */
E 8
#endif
E 5
};

/*
 * Descriptor associated with each attached hardware interface.
 */
struct bpf_if {
D 3
	/* List of descriptors listening on this interface. */
	struct bpf_d *bif_dlist;

	/* Pointer to the device driver's softc bpf field. */
	struct bpf_if **bif_driverp;

	/* Device parameters, see bpf.h. */
	struct bpf_devp bif_devp;

	/* Length of bpf header (bpf_hdr + padding). */
	u_int bif_hdrlen;

	/* 'ifnet' of associated interface. */
	struct ifnet *bif_ifp;
E 3
I 3
	struct bpf_if *bif_next;	/* list of all interfaces */
	struct bpf_d *bif_dlist;	/* descriptor list */
	struct bpf_if **bif_driverp;	/* pointer into softc */
	u_int bif_dlt;			/* link layer type */
	u_int bif_hdrlen;		/* length of header (with padding) */
	struct ifnet *bif_ifp;		/* correspoding interface */
E 3
};
I 9

#ifdef KERNEL
int	 bpf_setf __P((struct bpf_d *, struct bpf_program *));
#endif
E 9
E 1
