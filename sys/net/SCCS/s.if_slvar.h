h37244
s 00002/00002/00052
d D 8.4 95/01/09 17:54:28 cgd 14 13
c 64-bit changes: casts, and ioctl cmds are u_longs
e
s 00000/00018/00054
d D 8.3 94/02/01 22:08:14 cgd 13 12
c get SLIP ioctl and BPF info from <net/slip.h>
e
s 00028/00009/00044
d D 8.2 94/01/07 18:19:40 cgd 12 11
c add BPF support. compress all packets. stabilize error-prone lines.
e
s 00002/00002/00051
d D 8.1 93/06/10 22:44:58 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00000/00041
d D 7.10 93/06/04 17:31:45 bostic 10 9
c prototype everything
e
s 00004/00010/00037
d D 7.9 92/01/14 17:35:12 karels 9 8
c remove compat crap, other cleanups; remove old port-number peek
c for fast queue (use IP TOS instead)
e
s 00003/00003/00044
d D 7.8 91/10/16 15:52:55 william 8 7
c added link level control bits so we can pass mode info to a given 
c link layer protocol. for example, to enable slip compression.
e
s 00011/00004/00036
d D 7.7 91/05/07 09:18:37 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00001/00039
d D 7.6 91/02/22 12:33:19 karels 6 5
c fix GUNIT ioctl
e
s 00001/00001/00039
d D 7.5 91/02/08 09:55:20 karels 5 4
c consistent naming
e
s 00004/00002/00036
d D 7.4 90/01/20 17:34:03 sam 4 3
c rearrange flags; add "auto enable" of compression
e
s 00003/00000/00035
d D 7.3 89/06/30 18:15:59 karels 3 2
c merge new code from van, sundry cleanups
e
s 00018/00015/00017
d D 7.2 89/06/29 09:08:24 karels 2 1
c new version from van
e
s 00032/00000/00000
d D 7.1 89/06/29 09:07:22 karels 1 0
c initial working version
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 7
/*	%W% (Berkeley) %G% */
E 7
I 7
/*-
D 11
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Header: if_slvar.h,v 1.3 89/05/31 02:25:18 van Exp $
 */
E 7
E 2

/*
D 2
 * Definitions for SLIP "interface" data structure.
E 2
I 2
 * Definitions for SLIP interface data structures
 * 
D 7
 * (this exists so programs like slstats can get at the definition
E 7
I 7
 * (This exists so programs like slstats can get at the definition
E 7
 *  of sl_softc.)
E 2
D 7
 *
D 2
 * (This exists so that programs can interpret the kernel data structures.)
E 2
I 2
 * $Header: if_slvar.h,v 1.3 89/05/31 02:25:18 van Exp $
E 7
E 2
 */
struct sl_softc {
	struct	ifnet sc_if;		/* network-visible interface */
D 2
	short	sc_flags;		/* see below */
	short	sc_ilen;		/* length of input-packet-so-far */
E 2
I 2
	struct	ifqueue sc_fastq;	/* interactive output queue */
E 2
	struct	tty *sc_ttyp;		/* pointer to tty structure */
D 2
	char	*sc_mp;			/* pointer to next available buf char */
	char	*sc_buf;		/* input buffer */
	long	sc_lasttime;	/* last time a char arrived - seconds */
	long	sc_starttime;	/* last time a char arrived - seconds */
	long	sc_abortcount;	/* number of abort esacpe chars */
#ifdef INET
	struct	slcompress sc_comp;	/* tcp compression state */
#endif
E 2
I 2
	u_char	*sc_mp;			/* pointer to next available buf char */
	u_char	*sc_ep;			/* pointer to last available buf char */
	u_char	*sc_buf;		/* input buffer */
	u_int	sc_flags;		/* see below */
	u_int	sc_escape;	/* =1 if last char input was FRAME_ESCAPE */
D 9
	u_int	sc_bytessent;
	u_int	sc_bytesrcvd;
E 9
	long	sc_lasttime;		/* last time a char arrived */
D 9
	long	sc_starttime;		/* last time a char arrived */
E 9
	long	sc_abortcount;		/* number of abort esacpe chars */
I 9
	long	sc_starttime;		/* time of first abort in window */
E 9
I 3
#ifdef INET				/* XXX */
E 3
	struct	slcompress sc_comp;	/* tcp compression data */
I 3
#endif
I 12
	caddr_t	sc_bpf;			/* BPF data */
E 12
E 3
E 2
};

I 12
/* internal flags */
#define	SC_ERROR	0x0001		/* had an input error */

E 12
D 4
/* flags */
E 4
I 4
/* visible flags */
E 4
D 2
#define	SC_ESCAPED	0x0001		/* saw a FRAME_ESCAPE */
E 2
D 8
#define	SC_COMPRESS	0x0002		/* compress TCP traffic */
#define	SC_NOICMP	0x0004		/* supress ICMP traffic */
D 4
#define	SC_ABORT	0x0008		/* have been sent an abort request */
E 4
I 4
#define	SC_AUTOCOMP	0x0008		/* auto-enable TCP compression */
E 8
I 8
D 9
#define	SC_COMPRESS	IFF_LLC0	/* compress TCP traffic */
#define	SC_NOICMP	IFF_LLC1	/* supress ICMP traffic */
#define	SC_AUTOCOMP	IFF_LLC2	/* auto-enable TCP compression */
E 8
/* internal flags (should be separate) */
#define	SC_ABORT	0x10000		/* have been sent an abort request */
E 9
I 9
#define	SC_COMPRESS	IFF_LINK0	/* compress TCP traffic */
#define	SC_NOICMP	IFF_LINK1	/* supress ICMP traffic */
#define	SC_AUTOCOMP	IFF_LINK2	/* auto-enable TCP compression */
E 9
E 4
D 2
#define	SC_OACTIVE	0x0010		/* output is active */
E 2

D 13
/* this stuff doesn't belong here... */
D 9
#define	SLIOCGFLAGS	_IOR('t', 90, int)	/* get configuration flags */
#define	SLIOCSFLAGS	_IOW('t', 89, int)	/* set configuration flags */
E 9
I 3
D 5
#define	SLIOGUNIT	_IOW('t', 88, int)	/* get slip unit number */
E 5
I 5
D 6
#define	SLIOCGUNIT	_IOW('t', 88, int)	/* get slip unit number */
E 6
I 6
#define	SLIOCGUNIT	_IOR('t', 88, int)	/* get slip unit number */
I 10

I 12
/*
 * definitions of the pseudo- link-level header attached to slip
 * packets grabbed by the packet filter (bpf) traffic monitor.
 * These definitions pulled from BPF's "slip.h" by cgd.
 */
#define	SLIP_HDRLEN	16		/* BPF SLIP header length */

/* offsets into BPF SLIP header */
#define	SLX_DIR		0		/* direction; see below */
#define	SLX_CHDR	1		/* compressed header data */
#define	CHDR_LEN	15		/* length of compressed header data */

#define	SLIPDIR_IN	0		/* incoming */
#define	SLIPDIR_OUT	1		/* outgoing */

E 13
E 12
#ifdef KERNEL
D 12
void	 slattach __P((void));
void	 slclose __P((struct tty *));
void	 slinput __P((int, struct tty *));
int	 slioctl __P((struct ifnet *, int, caddr_t));
int	 slopen __P((dev_t, struct tty *));
int	 sloutput __P((struct ifnet *,
E 12
I 12
void	slattach __P((void));
void	slclose __P((struct tty *));
void	slinput __P((int, struct tty *));
D 14
int	slioctl __P((struct ifnet *, int, caddr_t));
E 14
I 14
int	slioctl __P((struct ifnet *, u_long, caddr_t));
E 14
int	slopen __P((dev_t, struct tty *));
int	sloutput __P((struct ifnet *,
E 12
	    struct mbuf *, struct sockaddr *, struct rtentry *));
D 12
void	 slstart __P((struct tty *));
int	 sltioctl __P((struct tty *, int, caddr_t, int));
#endif
E 12
I 12
void	slstart __P((struct tty *));
D 14
int	sltioctl __P((struct tty *, int, caddr_t, int));
E 14
I 14
int	sltioctl __P((struct tty *, u_long, caddr_t, int));
E 14
#endif /* KERNEL */
E 12
E 10
E 6
E 5
E 3
E 1
