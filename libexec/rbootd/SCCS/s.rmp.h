h05640
s 00002/00002/00067
d D 8.1 93/06/04 19:03:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00068
d D 5.2 93/06/04 19:02:18 bostic 3 1
c put the Regents copyright last so 44yank works
e
s 00002/00002/00067
d R 8.1 93/06/04 18:58:44 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00069/00000/00000
d D 5.1 92/07/23 15:45:40 bostic 1 0
c date and time created 92/07/23 15:45:40 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 Regents of the University of California.
E 3
 * Copyright (c) 1988, 1992 The University of Utah and the Center
 *	for Software Science (CSS).
I 3
D 4
 * Copyright (c) 1992 Regents of the University of California.
E 3
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Center for Software Science of the University of Utah Computer
 * Science Department.  CSS requests users of this software to return
 * to css-dist@cs.utah.edu any improvements that they make and grant
 * CSS redistribution rights.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * Utah $Hdr: rmp.h 3.1 92/07/06$
 * Author: Jeff Forys, University of Utah CSS
 */

/*
 *  Define MIN/MAX sizes of RMP (ethernet) packet.
 *  For ease of computation, the 4 octet CRC field is not included.
 *
 *  MCLBYTES is for bpfwrite(); it is adamant about using a cluster.
 */

#define	RMP_MAX_PACKET	MIN(1514,MCLBYTES)
#define	RMP_MIN_PACKET	60

/*
 *  Define RMP/Ethernet Multicast address (9:0:9:0:0:4) and its length.
 */
#define	RMP_ADDR	{ 0x9, 0x0, 0x9, 0x0, 0x0, 0x4 }
#define	RMP_ADDRLEN	6

/*
 *  Define IEEE802.2 (Logical Link Control) information.
 */
#define	IEEE_DSAP_HP	0xF8	/* Destination Service Access Point */
#define	IEEE_SSAP_HP	0xF8	/* Source Service Access Point */
#define	IEEE_CNTL_HP	0x0300	/* Type 1 / I format control information */

#define	HPEXT_DXSAP	0x608	/* HP Destination Service Access Point */
#define	HPEXT_SXSAP	0x609	/* HP Source Service Access Point */

/*
 *  802.3-style "Ethernet" header.
 */

struct hp_hdr {
	u_char	daddr[RMP_ADDRLEN];
	u_char	saddr[RMP_ADDRLEN];
	u_short	len;
};

/*
 * HP uses 802.2 LLC with their own local extensions.  This struct makes
 * sence out of this data (encapsulated in the above 802.3 packet).
 */

struct hp_llc {
	u_char	dsap;		/* 802.2 DSAP */
	u_char	ssap;		/* 802.2 SSAP */
	u_short	cntrl;		/* 802.2 control field */
	u_short	filler;		/* HP filler (must be zero) */
	u_short	dxsap;		/* HP extended DSAP */
	u_short	sxsap;		/* HP extended SSAP */
};
E 1
