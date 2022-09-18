h00086
s 00001/00001/00312
d D 8.6 95/05/03 17:01:43 mckusick 67 66
c unix domain => local domain
e
s 00001/00001/00312
d D 8.5 95/05/02 11:34:42 mckusick 66 65
c document linger time as being in seconds
e
s 00007/00007/00306
d D 8.4 94/02/21 09:38:25 bostic 65 64
c recv, recvfrom, recvmsg, send, sendto, and sendmsg now return a ssize_t
c recv, recvfrom, send and sendto now take a size_t as a length
e
s 00006/00004/00307
d D 8.3 94/02/17 08:50:58 bostic 64 63
c include AF_LOCAL and PF_LOCAL (the posix replacements for
c AF_UNIX/PF_UNIX); fix the copyright notice
c From: Mike Karels <karels@BSDI.COM>
e
s 00003/00003/00308
d D 8.2 94/01/04 16:16:48 bostic 63 62
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00305
d D 8.1 93/06/02 19:55:22 bostic 62 61
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00305
d D 7.23 93/05/14 18:38:32 andrew 61 60
c use correct name in comments for cmsghdr
e
s 00004/00000/00303
d D 7.22 93/04/27 23:52:18 mckusick 60 59
c protect against multiple inclusion
e
s 00027/00026/00276
d D 7.21 93/04/18 00:22:10 mckusick 59 58
c specify types for sysctl names
e
s 00009/00001/00293
d D 7.20 93/04/08 19:21:05 sklower 58 57
c add SIP, IPX, RTIP
e
s 00027/00000/00267
d D 7.19 93/03/31 15:44:26 mckusick 57 56
c add sysctl names array
e
s 00027/00000/00240
d D 7.18 93/02/04 00:58:29 mckusick 56 55
c add initial definitions for CTL_NET
e
s 00001/00000/00239
d D 7.17 92/07/18 16:47:56 sklower 55 54
c needed for multicast bug fix
e
s 00003/00001/00236
d D 7.16 92/05/19 09:50:34 sklower 54 53
c proprietary protocol request for RIP.
e
s 00001/00000/00236
d D 7.15 91/11/19 15:58:03 mckusick 53 52
c add MSG_DONTWAIT for NFS (from Rick Macklem)
e
s 00003/00001/00233
d D 7.14 91/09/05 18:02:37 karels 52 51
c add COIP
e
s 00001/00001/00233
d D 7.13 91/04/20 10:55:01 karels 51 50
c fix recvmsg prototype
e
s 00001/00002/00233
d D 7.12 91/03/04 11:20:16 bostic 50 49
c sendto: int * -> int
e
s 00028/00000/00207
d D 7.11 91/02/23 11:06:53 donn 49 48
c Prototype declarations.
e
s 00001/00011/00206
d D 7.10 90/06/28 22:00:30 bostic 48 47
c new copyright notice
e
s 00005/00005/00212
d D 7.9 90/05/30 11:35:19 sklower 47 46
c uniform convention about ints vs. unsigned in msghdr and cmsghdr
e
s 00000/00002/00217
d D 7.8 90/05/07 15:34:33 marc 46 45
c remove MSG_MAXIOVLEN -- use UIO_{MAX|SMALL}IOV from uio.h
e
s 00049/00020/00170
d D 7.7 90/04/04 22:17:48 karels 45 44
c add OSI alias for ISO; add XTP, LINK; define cmsghdr structure
c for ancillary data, with new format; move access rights into ancillary data;
c add MSG_WAITALL
e
s 00000/00000/00190
d D 7.6 89/09/04 18:08:51 sklower 44 43
c add sockaddr length; change PF_NBS to PF_ISO; add PF_ROUTE
e
s 00010/00008/00180
d D 7.5 88/12/13 13:28:39 sklower 43 42
c add AF_ISO
e
s 00033/00001/00155
d D 7.4 88/10/12 14:45:18 sklower 42 41
c checkpoint state before var length sockaddr's
e
s 00010/00005/00146
d D 7.3 88/06/27 18:54:36 bostic 41 40
c install approved copyright notice
e
s 00009/00003/00142
d D 7.2 87/12/30 12:04:49 bostic 40 39
c add Berkeley header
e
s 00001/00001/00144
d D 7.1 86/06/04 23:27:53 mckusick 39 38
c 4.3BSD release version
e
s 00004/00002/00141
d D 6.11 86/05/29 17:17:38 karels 38 37
c apple talk for them as speaks it
e
s 00009/00008/00134
d D 6.10 86/04/19 20:45:25 karels 37 36
c option for receiving OOB data in-line
e
s 00001/00000/00141
d D 6.9 85/11/19 19:45:56 karels 36 35
c add SO_TYPE
e
s 00001/00000/00140
d D 6.8 85/09/16 23:33:27 karels 35 34
c socket option for collecting error status
e
s 00010/00002/00130
d D 6.7 85/06/25 11:43:09 karels 34 33
c add decnet crap, raw hyperchannel
e
s 00007/00001/00125
d D 6.6 85/06/08 15:07:23 mckusick 33 32
c Add copyright
e
s 00010/00000/00116
d D 6.5 84/12/20 15:39:54 karels 32 31
c add socket options for changing buffer sizes, also unused fields
e
s 00010/00013/00106
d D 6.4 84/09/04 21:47:18 sam 31 30
c don't need pseudo-flags because SOL_SOCKET options now need a parameter which 
c specifies if option is on/off; add linger structure for handling SOL_LINGER
e
s 00001/00001/00118
d D 6.3 84/09/01 14:26:18 sam 30 29
c correct SO_DONTUSELOOPBACK
e
s 00012/00002/00107
d D 6.2 84/08/29 15:03:27 karels 29 28
c add SO_BROADCAST flag, SO_DONT* pseudo-flags
e
s 00000/00000/00109
d D 6.1 83/07/29 06:13:57 sam 28 27
c 4.2 distribution
e
s 00070/00059/00039
d D 4.27 83/05/27 13:58:58 sam 27 26
c wnj'ify for rights passing
e
s 00003/00003/00095
d D 4.26 83/05/18 02:42:18 sam 26 25
c sun changes
e
s 00003/00002/00095
d D 4.25 83/01/22 22:56:53 sam 25 24
c add hack option for FTP; this fills options, so move 
c pseudo option out of range for reuse
e
s 00000/00032/00097
d D 4.24 83/01/13 17:35:14 sam 24 23
c easy come, easy go
e
s 00036/00004/00093
d D 4.23 83/01/08 20:56:36 sam 23 22
c add socket option stuff & SOF_DONTROUTE
e
s 00001/00001/00096
d D 4.22 82/11/13 23:08:43 sam 22 21
c merge 4.1b and 4.1c
e
s 00003/00000/00094
d D 4.21 82/10/05 22:09:27 root 21 20
c oob and preview flags
e
s 00005/00000/00089
d D 4.20 82/09/27 02:43:15 root 20 19
c first working version
e
s 00001/00001/00088
d D 4.19 82/07/24 18:20:24 root 19 18
c restore sccs ids
e
s 00000/00000/00089
d D 4.18 82/07/24 18:19:07 root 18 17
c from calder
e
s 00002/00001/00087
d D 4.17 82/07/24 18:09:12 root 17 16
c merge with calder
e
s 00001/00000/00087
d D 4.16 82/06/08 22:03:59 wnj 16 15
c add SO_DONTROUTE
e
s 00002/00000/00085
d D 4.15 82/05/04 20:27:20 sam 15 14
c bound on address family for array index check
e
s 00002/00003/00083
d D 4.14 82/03/15 04:48:48 wnj 14 13
c name changes; get/sethostname
e
s 00001/00001/00085
d D 4.13 82/01/24 18:46:59 wnj 13 12
c sp_protocol is short, not u_short
e
s 00004/00004/00082
d D 4.12 82/01/13 10:51:53 wnj 12 11
c change option names
e
s 00001/00000/00085
d D 4.11 81/12/21 12:02:27 root 11 10
c added SO_LETDATADRAIN
e
s 00001/00001/00084
d D 4.10 81/12/02 17:26:14 wnj 10 9
c more cleanup
e
s 00018/00016/00067
d D 4.9 81/11/29 22:14:29 wnj 9 8
c lint & wkend editing
e
s 00000/00000/00083
d D 4.8 81/11/26 11:54:12 wnj 8 7
c before carry to arpavax
e
s 00000/00006/00083
d D 4.7 81/11/21 21:35:25 wnj 7 6
c get rid of sockaddri declaration
e
s 00068/00005/00021
d D 4.6 81/11/18 15:47:03 wnj 6 5
c more cleanup
e
s 00012/00006/00014
d D 4.5 81/11/14 16:51:16 wnj 5 4
c just before overlay of ip
e
s 00016/00054/00004
d D 4.4 81/11/08 16:40:08 wnj 4 3
c first listing
e
s 00017/00017/00041
d D 4.3 81/11/07 10:48:59 wnj 3 2
c last pre new interface cleanup
e
s 00000/00000/00058
d D 4.2 81/10/29 20:51:51 wnj 2 1
c misc changes
e
s 00058/00000/00000
d D 4.1 81/10/29 16:59:14 wnj 1 0
c date and time created 81/10/29 16:59:14 by wnj
e
u
U
t
T
I 1
D 4
/* %M% %I% %E% */
E 4
I 4
D 17
/*	%M%	%I%	%E%	*/
E 17
I 17
D 19
/*	socket.h	4.17	82/07/21	*/
E 19
I 19
D 33
/*	%M%	%I%	%E%	*/
E 33
I 33
/*
D 38
 * Copyright (c) 1982 Regents of the University of California.
E 38
I 38
D 39
 * Copyright (c) 1982,1985 Regents of the University of California.
E 39
I 39
D 40
 * Copyright (c) 1982,1985, 1986 Regents of the University of California.
E 39
E 38
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 40
I 40
D 42
 * Copyright (c) 1982, 1985, 1986 Regents of the University of California.
E 42
I 42
D 62
 * Copyright (c) 1982,1985,1986,1988 Regents of the University of California.
E 42
 * All rights reserved.
E 62
I 62
D 64
 * Copyright (c) 1993, 1982198519861988
E 64
I 64
 * Copyright (c) 1982, 1985, 1986, 1988, 1993, 1994
E 64
 *	The Regents of the University of California.  All rights reserved.
E 62
 *
D 48
 * Redistribution and use in source and binary forms are permitted
D 41
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 41
I 41
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
E 48
I 48
 * %sccs.include.redist.c%
E 48
E 41
E 40
 *
 *	%W% (Berkeley) %G%
 */
E 33
E 19
E 17
E 4

I 60
D 63
#ifndef _SOCKET_H_
#define	_SOCKET_H_
E 63
I 63
#ifndef _SYS_SOCKET_H_
#define	_SYS_SOCKET_H_
E 63

E 60
/*
D 4
 * User connection block
E 4
I 4
D 5
 * Externally visible attributes of sockets:
 * types and options.
E 5
I 5
D 27
 * Externally visible attributes of sockets.
E 27
I 27
 * Definitions related to sockets: types, address families, options.
E 27
E 5
E 4
 */
I 5

/*
D 27
 * Socket types.
 *
 * The kernel implement these abstract (session-layer) socket
 * services, with extra protocol on top of network services
 * if necessary.
E 27
I 27
 * Types
E 27
 */
E 5
D 4
struct ucb {
	struct	host *uc_host;		/* foreign host table entry */
	struct	proc *uc_proc;		/* user proc */
D 3
	union {				/* protocol control block */
		char *unull;			/* general */
		struct tcb *utcb;		/* for tcp */
	} U_cp;
#define	uc_tcb	U_cp.utcb
E 3
I 3
	caddr_t	uc_pcb;			/* protocol control block */
	struct	protosw *uc_proto;	/* protocol handle */
/* sbuf and rbuf should be uc_s and uc_r which are structures with */
/* fields: s_buf, s_mbmax, s_mbcnt, s_cc, s_ccmax */
E 3
	struct	mbuf *uc_sbuf;		/* user send buffer */
D 3
	struct	mbuf *uc_rbuf;		/* user receive buffer */
	u_char	uc_lolink;		/* lowest link no. in range (raw) */
	u_char	uc_hilink;		/* highest link no. in range (raw) */
E 3
	u_char	uc_snd;			/* # send bufs allocated */
	u_char	uc_ssize;		/* # bufs on send buffer */
D 3
#define	uc_timeo uc_ssize		/* user timeout parameter */
	short	uc_rhiwat;
E 3
I 3
	short	uc_scc;		/* not used yet */
	short	uc_shiwat;	/* not used yet */
	struct	mbuf *uc_rbuf;		/* user receive buffer */
	u_char	uc_rcv;		/* not used now */
	u_char	uc_rsize;	/* not used now */
E 3
	short	uc_rcc;
I 3
	short	uc_rhiwat;
	short	uc_timeo;		/* open timeout */
E 3
	u_char	uc_state;		/* state of this connection */
	u_short	uc_flags;		/* misc. flags (see below) */
	struct	proc *uc_rsel;		/* read selecting proc */
D 3
	struct	th *uc_template;
E 3
};
E 4
I 4
D 6
#define	SOCK_STREAM	0		/* stream socket */
#define	SOCK_DGRAM	1		/* datagram socket */
#define	SOCK_RAW	2		/* raw-protocol interface */
#define	SOCK_RDM	3		/* reliably-delivered message */
E 6
I 6
#define	SOCK_STREAM	1		/* stream socket */
#define	SOCK_DGRAM	2		/* datagram socket */
#define	SOCK_RAW	3		/* raw-protocol interface */
#define	SOCK_RDM	4		/* reliably-delivered message */
I 27
#define	SOCK_SEQPACKET	5		/* sequenced packet stream */
E 27
E 6
D 5
/* ... */
E 5
E 4
D 3
struct	th *tcp_template();
E 3

D 4
/* uc_flags field definitions */
I 3

/* these belong within TCP */
E 3
#define	UEOL		00001		/* EOL sent */
#define	UURG		00002		/* urgent data sent */
I 3
/* end belong in TCP */
E 3
#define	UDEBUG		00004		/* turn on debugging info recording */
D 3
#define	UTCP		00020		/* this is a TCP connection */
#define	UIP		00040		/* this is a raw IP connection */
#define	URAW		00100		/* this is a raw 1822 connection */
E 3
I 3
#define	UTCP		00020		/* SHOULD BE IMPLIED BY uc_proto */

E 3
#define	ULISTEN		00200		/* awaiting a connection */
D 3
#define	UCTL		00400		/* this is a control port only */
#define	URMSK		00560
E 3
I 3

E 3
#define	URCOLL		01000		/* someone collided on read select */
#define	URLOCK		02000		/* for uc_rbuf */
#define	URWANT		04000

/* connection state field */
#define	UCLOSED		0000		/* connection closed */
#define	UCLSERR		0001		/* error -- connection closing */
#define	UABORT		0002		/* connection aborted */
#define	UINTIMO		0004		/* open failed -- init timeout */
#define	URXTIMO		0010		/* retransmit too long timeout */
#define	URESET		0020		/* connection aborted due to reset */
#define	UOPERR		0040		/* open failed -- not enough buffers */
#define	UURGENT		0100		/* urgent data received */
#define	UNETDWN		0200		/* connection aborted due to net */

#ifdef KERNEL
struct	ucb *contab, *conNCON;
int	nnetcon;
#endif
E 4
I 4
/*
 * Option flags per-socket.
 */
D 37
#define	SO_DEBUG	0x01		/* turn on debugging info recording */
D 5
#define	SO_ACCEPT	0x02		/* willing to accept connection */
E 5
I 5
D 12
#define	SO_ACCEPTCONN	0x02		/* willing to accept connection */
E 5
#define	SO_NBIO		0x04		/* don't block on this socket */
D 5
#define	SO_INTR		0x08		/* interrupt when data available */
#define	SO_NEWFD	0x10		/* give new fd's for each connect */
E 5
I 5
#define	SO_INTNOTIFY	0x08		/* interrupt when data available */
I 11
#define	SO_LETDATADRAIN	0x10		/* let data drain on close */
E 12
I 12
D 27
#define	SO_ACCEPTCONN	0x02		/* willing to accept connections */
D 14
#define	SO_NONBLOCKING	0x04		/* don't block when i/o not possible */
#define	SO_NOKEEPALIVE	0x08		/* don't keep connections alive */
#define	SO_DONTLINGER	0x10		/* don't linger on close */
E 14
I 14
D 25
#define	SO_DONTLINGER	0x04		/* don't linger on close */
E 25
I 25
#define	SO_REUSEADDR	0x04		/* allow local address reuse (gag) */
E 27
I 27
#define	SO_ACCEPTCONN	0x02		/* socket has had listen() */
#define	SO_REUSEADDR	0x04		/* allow local address reuse */
E 27
E 25
#define	SO_KEEPALIVE	0x08		/* keep connections alive */
I 16
#define	SO_DONTROUTE	0x10		/* just use interface addresses */
I 17
D 27
#define	SO_NEWFDONCONN	0x20		/* give new fd on connection */
E 27
I 27
D 29
				/* 0x20 was SO_NEWFDONCONN */
E 29
I 29
#define	SO_BROADCAST	0x20		/* permit sending of broadcast msgs */
E 29
E 27
I 23
#define	SO_USELOOPBACK	0x40		/* bypass hardware when possible */
D 25
#define	SO_LINGER	0x80		/* ~SO_DONTLINGER */
E 25
I 25
#define	SO_LINGER	0x80		/* linger on close if data present */
E 37
I 37
#define	SO_DEBUG	0x0001		/* turn on debugging info recording */
#define	SO_ACCEPTCONN	0x0002		/* socket has had listen() */
#define	SO_REUSEADDR	0x0004		/* allow local address reuse */
#define	SO_KEEPALIVE	0x0008		/* keep connections alive */
#define	SO_DONTROUTE	0x0010		/* just use interface addresses */
#define	SO_BROADCAST	0x0020		/* permit sending of broadcast msgs */
#define	SO_USELOOPBACK	0x0040		/* bypass hardware when possible */
#define	SO_LINGER	0x0080		/* linger on close if data present */
#define	SO_OOBINLINE	0x0100		/* leave received OOB data in line */
I 55
#define	SO_REUSEPORT	0x0200		/* allow local address & port reuse */
E 55
E 37
D 29
#define	SO_DONTLINGER	(~SO_LINGER)	/* ~SO_LINGER */
E 29
I 29

/*
I 32
 * Additional options, not kept in so_options.
 */
#define SO_SNDBUF	0x1001		/* send buffer size */
#define SO_RCVBUF	0x1002		/* receive buffer size */
#define SO_SNDLOWAT	0x1003		/* send low-water mark */
#define SO_RCVLOWAT	0x1004		/* receive low-water mark */
#define SO_SNDTIMEO	0x1005		/* send timeout */
#define SO_RCVTIMEO	0x1006		/* receive timeout */
I 35
#define	SO_ERROR	0x1007		/* get error status and clear */
I 36
#define	SO_TYPE		0x1008		/* get socket type */
E 36
E 35

/*
E 32
D 31
 * Pseudo flags for disabling options.
E 31
I 31
 * Structure used for manipulating linger option.
E 31
 */
D 31
#define	SO_DONTDEBUG		(~SO_DEBUG)
#define	SO_DONTREUSEADDR	(~SO_REUSEADDR)
#define	SO_DONTKEEPALIVE	(~SO_KEEPALIVE)
#define	SO_ROUTE		(~SO_DONTROUTE)
#define	SO_DONTBROADCAST	(~SO_BROADCAST)
D 30
#define	SO_DONTUSELOOPBACK	(~SO_LOOPBACK)
E 30
I 30
#define	SO_DONTUSELOOPBACK	(~SO_USELOOPBACK)
E 30
#define	SO_DONTLINGER		(~SO_LINGER)
E 31
I 31
struct	linger {
	int	l_onoff;		/* option on/off */
D 66
	int	l_linger;		/* linger time */
E 66
I 66
	int	l_linger;		/* linger time in seconds */
E 66
};
E 31
E 29
E 25
E 23
E 17
E 16
E 14
E 12
E 11
D 6
#define	SO_NEWFDONCONN	0x10		/* give new fd's for each connect */
E 6
I 6

/*
I 31
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define	SOL_SOCKET	0xffff		/* options for socket level */

/*
E 31
D 27
 * Generic socket protocol format.
 *
 * Each process is normally operating in a protocol family,
 * whose protocols are used unless the process specifies otherwise.
 * Most families supply protocols to the basic socket types.  When
 * protocols are not present in the family, the higher level (roughly
 * ISO session layer) code in the system layers on the protocols
 * to support the socket types.
E 27
I 27
 * Address families.
E 27
 */
D 27
struct sockproto {
D 26
	short	sp_family;		/* protocol family */
D 9
	short	sp_protocol;		/* protocol within family */
E 9
I 9
D 13
	u_short	sp_protocol;		/* protocol within family */
E 13
I 13
	short	sp_protocol;		/* protocol within family */
E 26
I 26
	u_short	sp_family;		/* protocol family */
	u_short	sp_protocol;		/* protocol within family */
E 26
E 13
E 9
};
E 27
I 27
#define	AF_UNSPEC	0		/* unspecified */
D 64
#define	AF_UNIX		1		/* local to host (pipes, portals) */
E 64
I 64
#define	AF_LOCAL	1		/* local to host (pipes, portals) */
#define	AF_UNIX		AF_LOCAL	/* backward compatibility */
E 64
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
#define	AF_IMPLINK	3		/* arpanet imp addresses */
#define	AF_PUP		4		/* pup protocols: e.g. BSP */
#define	AF_CHAOS	5		/* mit CHAOS protocols */
#define	AF_NS		6		/* XEROX NS protocols */
D 43
#define	AF_NBS		7		/* nbs protocols */
E 43
I 43
#define	AF_ISO		7		/* ISO protocols */
I 45
#define	AF_OSI		AF_ISO
E 45
E 43
#define	AF_ECMA		8		/* european computer manufacturers */
#define	AF_DATAKIT	9		/* datakit protocols */
#define	AF_CCITT	10		/* CCITT protocols, X.25 etc */
#define	AF_SNA		11		/* IBM SNA */
I 34
#define AF_DECnet	12		/* DECnet */
D 45
#define AF_DLI		13		/* Direct data link interface */
E 45
I 45
#define AF_DLI		13		/* DEC Direct data link interface */
E 45
#define AF_LAT		14		/* LAT */
#define	AF_HYLINK	15		/* NSC Hyperchannel */
I 38
#define	AF_APPLETALK	16		/* Apple Talk */
I 43
#define	AF_ROUTE	17		/* Internal Routing Protocol */
I 45
#define	AF_LINK		18		/* Link layer interface */
#define	pseudo_AF_XTP	19		/* eXpress Transfer Protocol (no AF) */
I 52
#define	AF_COIP		20		/* connection-oriented IP, aka ST II */
I 54
#define	AF_CNT		21		/* Computer Network Technology */
I 58
#define pseudo_AF_RTIP	22		/* Help Identify RTIP packets */
#define	AF_IPX		23		/* Novell Internet Protocol */
#define	AF_SIP		24		/* Simple Internet Protocol */
#define pseudo_AF_PIP	25		/* Help Identify PIP packets */
E 58
E 54
E 52
E 45
E 43
E 38
E 34
E 27

D 27
#define	PF_UNSPEC	0		/* unspecified */
D 9
#define	PF_LOCAL	1		/* local to host (pipes, portals) */
E 9
I 9
#define	PF_UNIX		1		/* UNIX internal protocol */
E 9
#define	PF_INET		2		/* internetwork: UDP, TCP, etc. */
D 9
#define	PF_PUP		3		/* pup protocols: e.g. BSP */
#define	PF_CHAOS	4		/* mit CHAOS protocols */
#define	PF_OISCP	5		/* ois communication protocols */
#define	PF_NBS		6		/* nbs protocols */
#define	PF_ECMA		7		/* european computer manufacturers */
#define	PF_DATAKIT	8		/* datakit protocols */
#define	PF_CCITT	9		/* CCITT protocols, X.25 etc */
E 9
I 9
#define	PF_IMPLINK	3		/* imp link protocols */
#define	PF_PUP		4		/* pup protocols: e.g. BSP */
#define	PF_CHAOS	5		/* mit CHAOS protocols */
#define	PF_OISCP	6		/* ois communication protocols */
#define	PF_NBS		7		/* nbs protocols */
#define	PF_ECMA		8		/* european computer manufacturers */
#define	PF_DATAKIT	9		/* datakit protocols */
#define	PF_CCITT	10		/* CCITT protocols, X.25 etc */
E 27
I 27
D 34
#define	AF_MAX		12
E 34
I 34
D 38
#define	AF_MAX		16
E 38
I 38
D 43
#define	AF_MAX		17
E 43
I 43
D 45
#define	AF_MAX		18
E 45
I 45
D 52
#define	AF_MAX		20
E 52
I 52
D 54
#define	AF_MAX		21
E 54
I 54
D 58
#define	AF_MAX		22
E 58
I 58
#define	AF_MAX		26
E 58
E 54
E 52
E 45
E 43
E 38
E 34
E 27
E 9

/*
D 27
 * Generic socket address format.
 *
 * Each process is also operating in an address family, whose
 * addresses are assigned unless otherwise requested.  The address
 * family used affects address properties: whether addresses are
 * externalized or internalized, location dependent or independent, etc.
 * The address can be defined directly if it fits in 14 bytes, or
 * a pointer and length can be given to variable length data.
 * We give these as two different structures to allow initialization.
E 27
I 27
 * Structure used by kernel to store most
 * addresses.
E 27
 */
I 42
D 43
#ifdef notyet
E 43
E 42
struct sockaddr {
I 42
	u_char	sa_len;			/* total length */
	u_char	sa_family;		/* address family */
D 43
	char	sa_addr[1];		/* actually longer; address value */
E 43
I 43
	char	sa_data[14];		/* actually longer; address value */
E 43
};
D 43
#else
struct sockaddr {
E 43
I 43
D 45
/*
 * 4.3 compat sockaddr, move to compat file later
 */
struct osockaddr {
E 43
E 42
D 26
	short	sa_family;		/* address family */
E 26
I 26
	u_short	sa_family;		/* address family */
E 26
	char	sa_data[14];		/* up to 14 bytes of direct address */
};
E 45
I 42
D 43
#endif
E 43
E 42
D 7
struct sockaddri {
	short	sai_family;
	short	sai_length;
	caddr_t	sai_addr;
	char	sai_ddata[8];
};
E 7

/*
D 27
 * The first few address families correspond to protocol
 * families.  Address families unrelated to protocol families
 * are also possible.
E 27
I 27
 * Structure used by kernel to pass protocol
 * information in raw sockets.
E 27
 */
D 27
#define	AF_UNSPEC	0		/* unspecified */
D 10
#define	AF_LOCAL	1		/* local to host (pipes, portals) */
E 10
I 10
#define	AF_UNIX		1		/* local to host (pipes, portals) */
E 10
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
D 9
#define	AF_PUP		3		/* pup protocols: e.g. BSP */
#define	AF_CHAOS	4		/* mit CHAOS protocols */
#define	AF_OISCP	5		/* ois communication protocols */
#define	AF_NBS		6		/* nbs protocols */
#define	AF_ECMA		7		/* european computer manufacturers */
#define	AF_DATAKIT	8		/* datakit protocols */
#define	AF_CCITT	9		/* CCITT protocols, X.25 etc */
E 9
I 9
#define	AF_IMPLINK	3		/* arpanet imp addresses */
#define	AF_PUP		4		/* pup protocols: e.g. BSP */
#define	AF_CHAOS	5		/* mit CHAOS protocols */
#define	AF_OISCP	6		/* ois communication protocols */
#define	AF_NBS		7		/* nbs protocols */
#define	AF_ECMA		8		/* european computer manufacturers */
#define	AF_DATAKIT	9		/* datakit protocols */
#define	AF_CCITT	10		/* CCITT protocols, X.25 etc */
E 27
I 27
struct sockproto {
	u_short	sp_family;		/* address family */
	u_short	sp_protocol;		/* protocol */
};
E 27
I 15

D 27
#define	AF_MAX		11
E 27
I 27
/*
 * Protocol families, same as address families for now.
 */
#define	PF_UNSPEC	AF_UNSPEC
D 64
#define	PF_UNIX		AF_UNIX
E 64
I 64
#define	PF_LOCAL	AF_LOCAL
#define	PF_UNIX		PF_LOCAL	/* backward compatibility */
E 64
#define	PF_INET		AF_INET
#define	PF_IMPLINK	AF_IMPLINK
#define	PF_PUP		AF_PUP
#define	PF_CHAOS	AF_CHAOS
#define	PF_NS		AF_NS
D 43
#define	PF_NBS		AF_NBS
E 43
I 43
#define	PF_ISO		AF_ISO
I 45
#define	PF_OSI		AF_ISO
E 45
E 43
#define	PF_ECMA		AF_ECMA
#define	PF_DATAKIT	AF_DATAKIT
#define	PF_CCITT	AF_CCITT
#define	PF_SNA		AF_SNA
I 34
#define PF_DECnet	AF_DECnet
#define PF_DLI		AF_DLI
#define PF_LAT		AF_LAT
#define	PF_HYLINK	AF_HYLINK
I 38
#define	PF_APPLETALK	AF_APPLETALK
I 43
#define	PF_ROUTE	AF_ROUTE
I 45
#define	PF_LINK		AF_LINK
#define	PF_XTP		pseudo_AF_XTP	/* really just proto family, no AF */
I 52
#define	PF_COIP		AF_COIP
I 54
#define	PF_CNT		AF_CNT
I 58
#define	PF_SIP		AF_SIP
#define	PF_IPX		AF_IPX		/* same format as AF_NS */
#define PF_RTIP		pseudo_AF_FTIP	/* same format as AF_INET */
#define PF_PIP		pseudo_AF_PIP
E 58
E 54
E 52
E 45
E 43
E 38
E 34
E 27
I 20

I 27
D 34
#define	PF_MAX		12
E 34
I 34
#define	PF_MAX		AF_MAX
E 34
D 31

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
E 27
I 23
D 24
/*
 * Structure passed in at system call level.
 */
E 23
struct	socketopt {
D 23
	int	so_optlen;
D 22
	caddr_t	so_optdata;
E 22
I 22
	char	*so_optdata;
E 23
I 23
	int	so_optlen;		/* total size of options */
	struct	sotemplate *so_optdata;	/* option records */
E 23
E 22
};
I 21

D 23
#define	SOF_OOB		0x1
#define	SOF_PREVIEW	0x2
E 23
I 23
/*
 * Options are specified as an array of records,
 * each of the following structure.  opt_level
 * indicates who's options are being specified.
 * Only SOL_SOCKET is globally known, other levels
 * use protocol numbers to tag options.  The 
 * opt_size field does not include the space
 * occupied by opt_level and opt_size.  opt_data
 * is usually structured differently at each level.
 */
struct	sotemplate {
	u_short	opt_level;		/* level for which options are for */
E 24
#define	SOL_SOCKET	0xffff		/* options for socket level */
E 31
D 24
	u_short	opt_size;		/* amount of data in opt_data */
	u_char	opt_data[1];		/* acutally longer */
};

/*
 * Structure used in specifying socket
 * level (SOL_SOCKET) options.
 */
struct	sooptions {
	int	sop_name;		/* defined above */
	int	sop_val;		/* optional value */
};
E 24

D 27
#define	SOF_OOB		0x1		/* send/recv out-of-band data */
#define	SOF_PREVIEW	0x2		/* look at data, but don't read */
#define	SOF_DONTROUTE	0x4		/* send without routing data */
E 27
I 27
/*
I 56
 * Definitions for network related sysctl, CTL_NET.
 *
 * Second level is protocol family.
 * Third level is protocol number.
 *
 * Further levels are defined by the individual families below.
 */
I 57
#define NET_MAXID	AF_MAX

#define CTL_NET_NAMES { \
D 59
	"unspec", \
	"unix", \
	"inet", \
	"implink", \
	"pup", \
	"chaos", \
	"xerox_ns", \
	"iso", \
	"emca", \
	"datakit", \
	"ccitt", \
	"ibm_sna", \
	"decnet", \
	"dec_dli", \
	"lat", \
	"hylink", \
	"appletalk", \
	"route", \
	"link_layer", \
	"xtp", \
	"coip", \
	"cnt", \
E 59
I 59
	{ 0, 0 }, \
D 67
	{ "unix", CTLTYPE_NODE }, \
E 67
I 67
	{ "local", CTLTYPE_NODE }, \
E 67
	{ "inet", CTLTYPE_NODE }, \
	{ "implink", CTLTYPE_NODE }, \
	{ "pup", CTLTYPE_NODE }, \
	{ "chaos", CTLTYPE_NODE }, \
	{ "xerox_ns", CTLTYPE_NODE }, \
	{ "iso", CTLTYPE_NODE }, \
	{ "emca", CTLTYPE_NODE }, \
	{ "datakit", CTLTYPE_NODE }, \
	{ "ccitt", CTLTYPE_NODE }, \
	{ "ibm_sna", CTLTYPE_NODE }, \
	{ "decnet", CTLTYPE_NODE }, \
	{ "dec_dli", CTLTYPE_NODE }, \
	{ "lat", CTLTYPE_NODE }, \
	{ "hylink", CTLTYPE_NODE }, \
	{ "appletalk", CTLTYPE_NODE }, \
	{ "route", CTLTYPE_NODE }, \
	{ "link_layer", CTLTYPE_NODE }, \
	{ "xtp", CTLTYPE_NODE }, \
	{ "coip", CTLTYPE_NODE }, \
	{ "cnt", CTLTYPE_NODE }, \
	{ "rtip", CTLTYPE_NODE }, \
	{ "ipx", CTLTYPE_NODE }, \
	{ "sip", CTLTYPE_NODE }, \
	{ "pip", CTLTYPE_NODE }, \
E 59
}

E 57
/*
 * PF_ROUTE - Routing table
 *
 * Three additional levels are defined:
 *	Fourth: address family, 0 is wildcard
 *	Fifth: type of info, defined below
 *	Sixth: flag(s) to mask with for NET_RT_FLAGS
 */
#define NET_RT_DUMP	1		/* dump; may limit to a.f. */
#define NET_RT_FLAGS	2		/* by flags, e.g. RESOLVING */
#define NET_RT_IFLIST	3		/* survey interface list */
I 59
#define	NET_RT_MAXID	4
E 59

#define CTL_NET_RT_NAMES { \
D 59
	"unspec", \
	"dump", \
	"flags", \
	"iflist", \
E 59
I 59
	{ 0, 0 }, \
	{ "dump", CTLTYPE_STRUCT }, \
	{ "flags", CTLTYPE_STRUCT }, \
	{ "iflist", CTLTYPE_STRUCT }, \
E 59
}

/*
E 56
 * Maximum queue length specifiable by listen.
 */
#define	SOMAXCONN	5

/*
 * Message header for recvmsg and sendmsg calls.
I 42
 * Used value-result for recvmsg, value only for sendmsg.
E 42
 */
struct msghdr {
	caddr_t	msg_name;		/* optional address */
D 47
	int	msg_namelen;		/* size of address */
E 47
I 47
	u_int	msg_namelen;		/* size of address */
E 47
	struct	iovec *msg_iov;		/* scatter/gather array */
D 47
	int	msg_iovlen;		/* # elements in msg_iov */
E 47
I 47
	u_int	msg_iovlen;		/* # elements in msg_iov */
E 47
D 45
	caddr_t	msg_accrights;		/* access rights sent/received */
	int	msg_accrightslen;
I 42
	caddr_t	msg_control;		/* ancillary data not conveyable
					 * by flags; msgs of the form
					 *	u_short type;
					 *	u_short count;
					 *	u_char  data[count];
					 */
	int	msg_controllen;
E 45
I 45
	caddr_t	msg_control;		/* ancillary data, see below */
D 47
	int	msg_controllen;		/* ancillary data buffer len */
E 47
I 47
	u_int	msg_controllen;		/* ancillary data buffer len */
E 47
E 45
	int	msg_flags;		/* flags on received message */
E 42
};

#define	MSG_OOB		0x1		/* process out-of-band data */
#define	MSG_PEEK	0x2		/* peek at incoming message */
#define	MSG_DONTROUTE	0x4		/* send without using routing tables */
I 42
#define	MSG_EOR		0x8		/* data completes record */
#define	MSG_TRUNC	0x10		/* data discarded before delivery */
#define	MSG_CTRUNC	0x20		/* control data lost before delivery */
I 45
#define	MSG_WAITALL	0x40		/* wait for full request or error */
I 53
#define	MSG_DONTWAIT	0x80		/* this message should be nonblocking */
E 53
E 45

I 45
D 46
#define	MSG_MAXIOVLEN	16

E 46
E 45
/*
I 45
 * Header for ancillary data objects in msg_control buffer.
 * Used for additional information with/about a datagram
 * not expressible by flags.  The format is a sequence
 * of message elements headed by cmsghdr structures.
 */
struct cmsghdr {
	u_int	cmsg_len;		/* data byte count, including hdr */
D 47
	u_int	cmsg_level;		/* originating protocol */
	u_int	cmsg_type;		/* protocol-specific type */
E 47
I 47
	int	cmsg_level;		/* originating protocol */
	int	cmsg_type;		/* protocol-specific type */
E 47
/* followed by	u_char  cmsg_data[]; */
};

D 61
/* given pointer to struct adatahdr, return pointer to data */
E 61
I 61
/* given pointer to struct cmsghdr, return pointer to data */
E 61
#define	CMSG_DATA(cmsg)		((u_char *)((cmsg) + 1))

D 61
/* given pointer to struct adatahdr, return pointer to next adatahdr */
E 61
I 61
/* given pointer to struct cmsghdr, return pointer to next cmsghdr */
E 61
#define	CMSG_NXTHDR(mhdr, cmsg)	\
	(((caddr_t)(cmsg) + (cmsg)->cmsg_len + sizeof(struct cmsghdr) > \
	    (mhdr)->msg_control + (mhdr)->msg_controllen) ? \
	    (struct cmsghdr *)NULL : \
	    (struct cmsghdr *)((caddr_t)(cmsg) + ALIGN((cmsg)->cmsg_len)))

#define	CMSG_FIRSTHDR(mhdr)	((struct cmsghdr *)(mhdr)->msg_control)

/* "Socket"-level control message types: */
#define	SCM_RIGHTS	0x01		/* access rights (array of int) */

/*
 * 4.3 compat sockaddr, move to compat file later
 */
struct osockaddr {
	u_short	sa_family;		/* address family */
	char	sa_data[14];		/* up to 14 bytes of direct address */
};

/*
E 45
 * 4.3-compat message header (move to compat file later).
 */
struct omsghdr {
	caddr_t	msg_name;		/* optional address */
	int	msg_namelen;		/* size of address */
	struct	iovec *msg_iov;		/* scatter/gather array */
	int	msg_iovlen;		/* # elements in msg_iov */
	caddr_t	msg_accrights;		/* access rights sent/received */
	int	msg_accrightslen;
};
I 49

#ifndef	KERNEL

#include <sys/cdefs.h>

__BEGIN_DECLS
int	accept __P((int, struct sockaddr *, int *));
int	bind __P((int, const struct sockaddr *, int));
int	connect __P((int, const struct sockaddr *, int));
int	getpeername __P((int, struct sockaddr *, int *));
int	getsockname __P((int, struct sockaddr *, int *));
int	getsockopt __P((int, int, int, void *, int *));
int	listen __P((int, int));
D 65
int	recv __P((int, void *, int, int));
int	recvfrom __P((int, void *, int, int,
		struct sockaddr *, int *));
D 51
int	recvmsg __P((int, const struct msghdr *, int));
E 51
I 51
int	recvmsg __P((int, struct msghdr *, int));
E 51
int	send __P((int, const void *, int, int));
D 50
int	sendto __P((int, const void *, int, int,
		const struct sockaddr *, int *));
E 50
I 50
int	sendto __P((int, const void *, int, int, const struct sockaddr *, int));
E 50
int	sendmsg __P((int, const struct msghdr *, int));
E 65
I 65
ssize_t	recv __P((int, void *, size_t, int));
ssize_t	recvfrom __P((int, void *, size_t, int, struct sockaddr *, int *));
ssize_t	recvmsg __P((int, struct msghdr *, int));
ssize_t	send __P((int, const void *, size_t, int));
ssize_t	sendto __P((int, const void *,
	    size_t, int, const struct sockaddr *, int));
ssize_t	sendmsg __P((int, const struct msghdr *, int));
E 65
int	setsockopt __P((int, int, int, const void *, int));
int	shutdown __P((int, int));
int	socket __P((int, int, int));
int	socketpair __P((int, int, int, int *));
__END_DECLS

D 64
#endif	/* !KERNEL */
E 64
I 64
#endif /* !KERNEL */
E 64
I 60
D 63
#endif /* !_SOCKET_H_ */
E 63
I 63
#endif /* !_SYS_SOCKET_H_ */
E 63
E 60
E 49
E 42
D 45

#define	MSG_MAXIOVLEN	16
E 45
E 27
E 23
E 21
E 20
E 15
E 9
E 6
E 5
E 4
E 1
