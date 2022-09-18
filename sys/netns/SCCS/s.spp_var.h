h13368
s 00002/00002/00187
d D 8.1 93/06/10 23:35:41 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00188
d D 7.7 90/06/28 21:50:05 bostic 11 10
c new copyright notice
e
s 00003/00000/00196
d D 7.6 89/04/22 12:13:47 sklower 10 9
c changes for var. length sockaddrs, routing lookup changes,
c checkpoint at first working tp4 connection, before gnodes
e
s 00011/00006/00185
d D 7.5 88/06/29 17:13:51 bostic 9 8
c install approved copyright notice
e
s 00001/00001/00190
d D 7.4 88/03/12 18:13:22 karels 8 7
c we get our own copy of xxx_timer.h (I don't want to debug TCP and SPP
c simultaneously!)
e
s 00009/00003/00182
d D 7.3 88/01/20 15:15:41 sklower 7 6
c Change licensing/use notice.
e
s 00110/00017/00075
d D 7.2 87/11/05 18:43:32 sklower 6 5
c This incorporates recent tcp strategies of Karels/Jacobson: 
c slow start, clamped rxmt, binary fixed point rtt smoothing.  Works on sun 3.X
e
s 00001/00001/00091
d D 7.1 86/06/05 00:39:25 mckusick 5 4
c 4.3BSD release version
e
s 00001/00001/00091
d D 6.4 86/02/03 17:41:02 sklower 4 3
c Correct erroneous copyright information.
e
s 00002/00000/00090
d D 6.3 85/07/19 18:40:17 sklower 3 2
c Want more detail on which retransmitted packets are ignored.
e
s 00007/00001/00083
d D 6.2 85/06/08 12:53:08 mckusick 2 1
c Add copyright
e
s 00084/00000/00000
d D 6.1 85/05/30 19:11:18 sklower 1 0
c date and time created 85/05/30 19:11:18 by sklower
e
u
U
t
T
I 1
D 2
/*      %M%     %I%     %E%     */
E 2
I 2
/*
D 4
 * Copyright (c) 1982 Regents of the University of California.
E 4
I 4
D 5
 * Copyright (c) 1984, 1985 Regents of the University of California.
E 5
I 5
D 6
 * Copyright (c) 1984, 1985, 1986 Regents of the University of California.
E 6
I 6
D 12
 * Copyright (c) 1984, 1985, 1986, 1987 Regents of the University of California.
E 6
E 5
E 4
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1984, 1985, 1986, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
E 7
 *
D 7
 *	%W% (Berkeley) %G%
E 7
I 7
D 11
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
 *
D 9
 *      %W% (Berkeley) %G%
E 9
I 9
 *	%W% (Berkeley) %G%
E 9
E 7
 */
E 2

/*
 * Sp control block, one per connection
 */
struct sppcb {
	struct	spidp_q	s_q;		/* queue for out-of-order receipt */
	struct	nspcb	*s_nspcb;	/* backpointer to internet pcb */
	u_char	s_state;
	u_char	s_flags;
D 6
#define SF_AK	0x01			/* Acknowledgement requested */
#define SF_DELACK 0x02			/* Ak, waiting to see if we xmit*/
#define SF_HI	0x04			/* Show headers on input */
#define SF_HO	0x08			/* Show headers on output */
#define SF_PI	0x10			/* Packet (datagram) interface */
E 6
I 6
#define	SF_ACKNOW	0x01		/* Ack peer immediately */
#define	SF_DELACK	0x02		/* Ack, but try to delay it */
#define	SF_HI	0x04			/* Show headers on input */
#define	SF_HO	0x08			/* Show headers on output */
#define	SF_PI	0x10			/* Packet (datagram) interface */
#define SF_WIN	0x20			/* Window info changed */
#define SF_RXT	0x40			/* Rxt info changed */
#define SF_RVD	0x80			/* Calling from read usrreq routine */
E 6
	u_short s_mtu;			/* Max packet size for this stream */
/* use sequence fields in headers to store sequence numbers for this
   connection */
D 6
	struct	spidp s_shdr;		/* prototype header to transmit */
#define s_cc s_shdr.si_cc		/* connection control (for EM bit) */
#define s_dt s_shdr.si_dt		/* datastream type */
#define s_sid s_shdr.si_sid		/* source connection identifier */
#define s_did s_shdr.si_did		/* destination connection identifier */
#define s_seq s_shdr.si_seq		/* sequence number */
#define s_ack s_shdr.si_ack		/* acknowledge number */
#define s_alo s_shdr.si_alo		/* allocation number */
#define s_dport s_shdr.si_dna.x_port	/* where we are sending */
E 6
I 6
	struct	idp	*s_idp;
	struct	sphdr	s_shdr;		/* prototype header to transmit */
#define s_cc s_shdr.sp_cc		/* connection control (for EM bit) */
#define s_dt s_shdr.sp_dt		/* datastream type */
#define s_sid s_shdr.sp_sid		/* source connection identifier */
#define s_did s_shdr.sp_did		/* destination connection identifier */
#define s_seq s_shdr.sp_seq		/* sequence number */
#define s_ack s_shdr.sp_ack		/* acknowledge number */
#define s_alo s_shdr.sp_alo		/* allocation number */
#define s_dport s_idp->idp_dna.x_port	/* where we are sending */
E 6
	struct sphdr s_rhdr;		/* last received header (in effect!)*/
	u_short s_rack;			/* their acknowledge number */
	u_short s_ralo;			/* their allocation number */
D 6
	u_short s_snt;			/* highest packet # we have sent */
E 6
I 6
	u_short s_smax;			/* highest packet # we have sent */
	u_short	s_snxt;			/* which packet to send next */
E 6

D 6
/* timeout stuff */
E 6
I 6
/* congestion control */
#define	CUNIT	1024			/* scaling for ... */
	int	s_cwnd;			/* Congestion-controlled window */
					/* in packets * CUNIT */
	short	s_swnd;			/* == tcp snd_wnd, in packets */
	short	s_smxw;			/* == tcp max_sndwnd */
					/* difference of two spp_seq's can be
					   no bigger than a short */
	u_short	s_swl1;			/* == tcp snd_wl1 */
	u_short	s_swl2;			/* == tcp snd_wl2 */
	int	s_cwmx;			/* max allowable cwnd */
	int	s_ssthresh;		/* s_cwnd size threshhold for
					 * slow start exponential-to-
					 * linear switch */
/* transmit timing stuff
 * srtt and rttvar are stored as fixed point, for convenience in smoothing.
 * srtt has 3 bits to the right of the binary point, rttvar has 2.
 */
E 6
	short	s_idle;			/* time idle */
D 8
	short	s_timer[TCPT_NTIMERS];	/* timers */
E 8
I 8
	short	s_timer[SPPT_NTIMERS];	/* timers */
E 8
	short	s_rxtshift;		/* log(2) of rexmt exp. backoff */
I 6
	short	s_rxtcur;		/* current retransmit value */
E 6
	u_short	s_rtseq;		/* packet being timed */
	short	s_rtt;			/* timer for round trips */
	short	s_srtt;			/* averaged timer */
I 6
	short	s_rttvar;		/* variance in round trip time */
E 6
	char	s_force;		/* which timer expired */
I 6
	char	s_dupacks;		/* counter to intuit xmt loss */
E 6

/* out of band data */
	char	s_oobflags;
#define SF_SOOB	0x08			/* sending out of band data */
#define SF_IOOB 0x10			/* receiving out of band data */
	char	s_iobc;			/* input characters */
/* debug stuff */
	u_short	s_want;			/* Last candidate for sending */
I 6
	char	s_outx;			/* exit taken from spp_output */
	char	s_inx;			/* exit taken from spp_input */
I 10
	u_short	s_flags2;		/* more flags for testing */
#define SF_NEWCALL	0x100		/* for new_recvmsg */
#define SO_NEWCALL	10		/* for new_recvmsg */
E 10
E 6
};

#define	nstosppcb(np)	((struct sppcb *)(np)->nsp_pcb)
#define	sotosppcb(so)	(nstosppcb(sotonspcb(so)))

I 6
struct	sppstat {
	long	spps_connattempt;	/* connections initiated */
	long	spps_accepts;		/* connections accepted */
	long	spps_connects;		/* connections established */
	long	spps_drops;		/* connections dropped */
	long	spps_conndrops;		/* embryonic connections dropped */
	long	spps_closed;		/* conn. closed (includes drops) */
	long	spps_segstimed;		/* segs where we tried to get rtt */
	long	spps_rttupdated;	/* times we succeeded */
	long	spps_delack;		/* delayed acks sent */
	long	spps_timeoutdrop;	/* conn. dropped in rxmt timeout */
	long	spps_rexmttimeo;	/* retransmit timeouts */
	long	spps_persisttimeo;	/* persist timeouts */
	long	spps_keeptimeo;		/* keepalive timeouts */
	long	spps_keepprobe;		/* keepalive probes sent */
	long	spps_keepdrops;		/* connections dropped in keepalive */

	long	spps_sndtotal;		/* total packets sent */
	long	spps_sndpack;		/* data packets sent */
	long	spps_sndbyte;		/* data bytes sent */
	long	spps_sndrexmitpack;	/* data packets retransmitted */
	long	spps_sndrexmitbyte;	/* data bytes retransmitted */
	long	spps_sndacks;		/* ack-only packets sent */
	long	spps_sndprobe;		/* window probes sent */
	long	spps_sndurg;		/* packets sent with URG only */
	long	spps_sndwinup;		/* window update-only packets sent */
	long	spps_sndctrl;		/* control (SYN|FIN|RST) packets sent */
	long	spps_sndvoid;		/* couldn't find requested packet*/

	long	spps_rcvtotal;		/* total packets received */
	long	spps_rcvpack;		/* packets received in sequence */
	long	spps_rcvbyte;		/* bytes received in sequence */
	long	spps_rcvbadsum;		/* packets received with ccksum errs */
	long	spps_rcvbadoff;		/* packets received with bad offset */
	long	spps_rcvshort;		/* packets received too short */
	long	spps_rcvduppack;	/* duplicate-only packets received */
	long	spps_rcvdupbyte;	/* duplicate-only bytes received */
	long	spps_rcvpartduppack;	/* packets with some duplicate data */
	long	spps_rcvpartdupbyte;	/* dup. bytes in part-dup. packets */
	long	spps_rcvoopack;		/* out-of-order packets received */
	long	spps_rcvoobyte;		/* out-of-order bytes received */
	long	spps_rcvpackafterwin;	/* packets with data after window */
	long	spps_rcvbyteafterwin;	/* bytes rcvd after window */
	long	spps_rcvafterclose;	/* packets rcvd after "close" */
	long	spps_rcvwinprobe;	/* rcvd window probe packets */
	long	spps_rcvdupack;		/* rcvd duplicate acks */
	long	spps_rcvacktoomuch;	/* rcvd acks for unsent data */
	long	spps_rcvackpack;	/* rcvd ack packets */
	long	spps_rcvackbyte;	/* bytes acked by rcvd acks */
	long	spps_rcvwinupd;		/* rcvd window update packets */
};
E 6
struct	spp_istat {
	short	hdrops;
	short	badsum;
	short	badlen;
	short	slotim;
	short	fastim;
	short	nonucn;
	short	noconn;
	short	notme;
	short	wrncon;
	short	bdreas;
	short	gonawy;
I 3
	short	notyet;
	short	lstdup;
I 6
	struct sppstat newstats;
E 6
E 3
};

#ifdef KERNEL
struct spp_istat spp_istat;
I 6

/* Following was struct sppstat sppstat; */
#ifndef sppstat
#define sppstat spp_istat.newstats
#endif

E 6
u_short spp_iss;
extern struct sppcb *spp_close(), *spp_disconnect(),
	*spp_usrclosed(), *spp_timers(), *spp_drop();
#endif

#define	SPP_ISSINCR	128
/*
 * SPP sequence numbers are 16 bit integers operated
 * on with modular arithmetic.  These macros can be
 * used to compare such integers.
 */
I 6
#ifdef sun
short xnsCbug;
#define	SSEQ_LT(a,b)	((xnsCbug = (short)((a)-(b))) < 0)
#define	SSEQ_LEQ(a,b)	((xnsCbug = (short)((a)-(b))) <= 0)
#define	SSEQ_GT(a,b)	((xnsCbug = (short)((a)-(b))) > 0)
#define	SSEQ_GEQ(a,b)	((xnsCbug = (short)((a)-(b))) >= 0)
#else
E 6
#define	SSEQ_LT(a,b)	(((short)((a)-(b))) < 0)
#define	SSEQ_LEQ(a,b)	(((short)((a)-(b))) <= 0)
#define	SSEQ_GT(a,b)	(((short)((a)-(b))) > 0)
#define	SSEQ_GEQ(a,b)	(((short)((a)-(b))) >= 0)
I 6
#endif
E 6
E 1
