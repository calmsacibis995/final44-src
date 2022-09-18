h42555
s 00002/00002/00064
d D 8.1 93/06/10 23:06:35 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00000/00057
d D 7.12 93/06/04 17:23:26 bostic 21 20
c prototype everything
e
s 00001/00001/00056
d D 7.11 93/05/03 02:52:10 torek 20 19
c fix comment (udp checksum has nothing to do with netmask req!)
e
s 00011/00000/00046
d D 7.10 93/04/26 23:46:20 mckusick 19 17
c add support for getting udp checksum
e
s 00011/00000/00046
d R 7.10 93/04/26 23:27:38 mckusick 18 17
c add support for getting udp checksum
e
s 00000/00002/00046
d D 7.9 93/04/18 00:16:05 mckusick 17 16
c UDP_TTL is replaced by ip_ttl setable by sysctl
e
s 00009/00009/00039
d D 7.8 93/01/08 18:42:42 andrew 16 15
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00001/00011/00047
d D 7.7 90/06/28 22:49:53 bostic 15 14
c new copyright notice
e
s 00012/00007/00046
d D 7.6 90/06/28 14:47:54 karels 14 13
c arrange stat block sensibly
e
s 00004/00001/00049
d D 7.5 89/09/20 14:22:38 sklower 13 11
c add variables for SNMP
e
s 00003/00000/00050
d R 7.5 89/09/20 13:06:45 sklower 12 11
c add stats for SNMP
e
s 00010/00005/00040
d D 7.4 88/06/29 17:07:59 bostic 11 10
c install approved copyright notice
e
s 00008/00002/00037
d D 7.3 87/12/07 17:47:18 bostic 10 9
c use Berkeley specific header
e
s 00001/00001/00038
d D 7.2 87/06/04 22:03:45 karels 9 8
c add patchable udp ttl
e
s 00001/00001/00038
d D 7.1 86/06/05 00:34:05 mckusick 8 7
c 4.3BSD release version
e
s 00001/00001/00038
d D 6.4 86/04/05 09:14:23 karels 7 6
c longer TTL's
e
s 00002/00000/00037
d D 6.3 86/02/05 16:51:58 karels 6 5
c smaller TTL
e
s 00007/00001/00030
d D 6.2 85/06/08 12:46:57 mckusick 5 4
c Add copyright
e
s 00000/00000/00031
d D 6.1 83/07/29 07:13:34 sam 4 3
c 4.2 distribution
e
s 00010/00000/00021
d D 4.3 81/11/18 15:38:50 wnj 3 2
c more cleanup
e
s 00018/00000/00003
d D 4.2 81/11/15 13:01:09 wnj 2 1
c listing
e
s 00003/00000/00000
d D 4.1 81/11/14 16:52:29 wnj 1 0
c date and time created 81/11/14 16:52:29 by wnj
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 8
 * Copyright (c) 1982 Regents of the University of California.
E 8
I 8
D 13
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 13
I 13
D 22
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 13
E 8
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
D 15
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 11
E 10
 *
 *	%W% (Berkeley) %G%
 */
E 5

I 3
/*
 * UDP kernel structures and variables.
 */
E 3
I 2
struct	udpiphdr {
	struct 	ipovly ui_i;		/* overlaid ip structure */
	struct	udphdr ui_u;		/* udp header */
};
#define	ui_next		ui_i.ih_next
#define	ui_prev		ui_i.ih_prev
#define	ui_x1		ui_i.ih_x1
#define	ui_pr		ui_i.ih_pr
#define	ui_len		ui_i.ih_len
#define	ui_src		ui_i.ih_src
#define	ui_dst		ui_i.ih_dst
#define	ui_sport	ui_u.uh_sport
#define	ui_dport	ui_u.uh_dport
#define	ui_ulen		ui_u.uh_ulen
#define	ui_sum		ui_u.uh_sum

I 3
struct	udpstat {
D 14
	int	udps_hdrops;
	int	udps_badsum;
	int	udps_badlen;
I 13
	int	udps_noport;
	int	udps_ipackets;
	int	udps_opackets;
E 14
I 14
				/* input statistics: */
D 16
	int	udps_ipackets;		/* total input packets */
	int	udps_hdrops;		/* packet shorter than header */
	int	udps_badsum;		/* checksum error */
	int	udps_badlen;		/* data length larger than packet */
	int	udps_noport;		/* no socket on port */
	int	udps_noportbcast;	/* of above, arrived as broadcast */
	int	udps_fullsock;		/* not delivered, input socket full */
	int	udpps_pcbcachemiss;	/* input packets missing pcb cache */
E 16
I 16
	u_long	udps_ipackets;		/* total input packets */
	u_long	udps_hdrops;		/* packet shorter than header */
	u_long	udps_badsum;		/* checksum error */
	u_long	udps_badlen;		/* data length larger than packet */
	u_long	udps_noport;		/* no socket on port */
	u_long	udps_noportbcast;	/* of above, arrived as broadcast */
	u_long	udps_fullsock;		/* not delivered, input socket full */
	u_long	udpps_pcbcachemiss;	/* input packets missing pcb cache */
E 16
				/* output statistics: */
D 16
	int	udps_opackets;		/* total output packets */
E 16
I 16
	u_long	udps_opackets;		/* total output packets */
E 16
E 14
E 13
};

I 19
/*
 * Names for UDP sysctl objects
 */
D 20
#define	UDPCTL_CHECKSUM		1	/* allow replies to netmask requests */
E 20
I 20
#define	UDPCTL_CHECKSUM		1	/* checksum UDP packets */
E 20
#define UDPCTL_MAXID		2

#define UDPCTL_NAMES { \
	{ 0, 0 }, \
	{ "checksum", CTLTYPE_INT }, \
}

E 19
I 6
D 7
#define	UDP_TTL		15		/* time to live for UDP packets */
E 7
I 7
D 9
#define	UDP_TTL		30		/* time to live for UDP packets */
E 9
I 9
D 14
#define	UDP_TTL		30		/* deflt time to live for UDP packets */
E 14
I 14
D 17
#define	UDP_TTL		30	/* default time to live for UDP packets */
E 14
E 9
E 7

E 17
E 6
E 3
#ifdef KERNEL
E 2
struct	inpcb udb;
I 3
struct	udpstat udpstat;
I 21

void	 udp_ctlinput __P((int, struct sockaddr *, struct ip *));
void	 udp_init __P((void));
void	 udp_input __P((struct mbuf *, int));
int	 udp_output __P((struct inpcb *,
	    struct mbuf *, struct mbuf *, struct mbuf *));
int	 udp_sysctl __P((int *, u_int, void *, size_t *, void *, size_t));
int	 udp_usrreq __P((struct socket *,
	    int, struct mbuf *, struct mbuf *, struct mbuf *));
E 21
E 3
I 2
#endif
E 2
E 1
