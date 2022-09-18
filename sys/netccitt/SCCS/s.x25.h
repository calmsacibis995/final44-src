h57219
s 00002/00002/00129
d D 8.1 93/06/10 22:54:16 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00130
d D 7.10 92/12/08 16:54:46 sklower 12 11
c restore original UBC Copyright
e
s 00017/00012/00114
d D 7.9 92/12/08 16:19:24 sklower 11 10
c contributions from Dirk Husemann
e
s 00003/00000/00123
d D 7.8 91/05/29 19:12:26 sklower 10 9
c 2 new sockopts: attach x25 vc to route, and turn on incoming dg listening
e
s 00003/00001/00120
d D 7.7 91/05/01 18:11:25 sklower 9 8
c borrow two flags from isode (nodnic & prepnd0) for convering AFI37 to  X.121
e
s 00004/00000/00117
d D 7.6 91/01/09 15:32:36 sklower 8 7
c additional flags useful for kernel proto <-> X.25 operation
e
s 00001/00000/00116
d D 7.5 90/11/13 18:26:57 sklower 7 6
c add socket option/ control type for user defined connect facilities
e
s 00004/00001/00112
d D 7.4 90/08/30 18:48:44 sklower 6 3
c this version compiles; completely untested
e
s 00000/00000/00113
d R 7.4 90/06/21 12:29:20 sklower 5 3
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00000/00000/00113
d R 7.4 90/05/22 15:46:31 sklower 4 3
c checkpoint before changing pq structure to be a sockbuf for downq 
c and only retaining up method
e
s 00039/00032/00074
d D 7.3 90/05/16 15:46:08 sklower 3 2
c periodic checkpoint against catastrophic loss
e
s 00020/00003/00086
d D 7.2 90/05/11 15:22:23 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00089/00000/00000
d D 7.1 90/05/11 11:19:44 sklower 1 0
c date and time created 90/05/11 11:19:44 by sklower
e
u
U
t
T
I 2
/*
D 11
 * Copyright (c) University of British Columbia, 1984
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
D 12
 * Copyright (c) Computing Centre, University of British Columbia, 1985 
E 12
I 12
 * Copyright (c) University of British Columbia, 1984
E 12
D 13
 * Copyright (c) 1990, 1992 The Regents of the University of California.
 * Copyright (C) Computer Science Department IV, 
E 13
I 13
 * Copyright (c) 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 * 		 University of Erlangen-Nuremberg, Germany, 1992
 * 
 * This code is derived from software contributed to Berkeley by the
 * Laboratory for Computation Vision and the Computer Science Department
 * of the the University of British Columbia and the Computer Science
 * Department (IV) of the University of Erlangen-Nuremberg, Germany.
E 11
 *
D 11
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
E 11
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
#ifdef KERNEL
#define PRC_IFUP	3
#define PRC_LINKUP	4
#define PRC_LINKDOWN	5
#define PRC_LINKRESET	6
#define PRC_LINKDONTCOPY	7
I 11
#ifndef PRC_DISCONNECT_REQUEST  
#define PRC_DISCONNECT_REQUEST 10
E 11
#endif
I 11
#endif
E 11

#define CCITTPROTO_HDLC		1
#define CCITTPROTO_X25		2	/* packet level protocol */
#define IEEEPROTO_802LLC	3	/* doesn't belong here */

#define HDLCPROTO_LAP		1
#define HDLCPROTO_LAPB		2
#define HDLCPROTO_UNSET		3
#define HDLCPROTO_LAPD		4

I 6
/* socket options */
#define PK_ACCTFILE		1	/* use level = CCITTPROTO_X25 */
I 7
#define PK_FACILITIES		2	/* use level = CCITTPROTO_X25 */
I 10
#define PK_RTATTACH		3	/* use level = CCITTPROTO_X25 */
#define PK_PRLISTEN		4	/* use level = CCITTPROTO_X25 */

E 10
I 8
#define MAX_FACILITIES		109     /* maximum size for facilities */
E 8
E 7

E 6
/*
 *  X.25 Socket address structure.  It contains the  X.121 or variation of
 *  X.121, facilities information, higher level protocol value (first four
 *  bytes of the User Data field), and the last  12 characters of the User
 *  Data field.
 */

struct x25_sockaddr {		/* obsolete - use sockaddr_x25 */
    short  xaddr_len;		/* Length of xaddr_addr.		*/
    u_char xaddr_addr[15];	/* Network dependent or X.121 address.	*/
    u_char xaddr_facilities;	/* Facilities information.		*/
#define XS_REVERSE_CHARGE	0x01
#define XS_HIPRIO		0x02
    u_char xaddr_proto[4];	/* Protocol ID (4 bytes of user data).	*/
    u_char xaddr_userdata[12];	/* Remaining User data field.		*/
};

/*
D 3
 * network configuration info
 * this structure must be 16 bytes long
 */

struct	x25config {
	u_short	xc_family;	/* always AF_CCITT */
	u_short	xc_net;		/* network id (usually a dnic) */
	char	xc_ntnlen;
	char	xc_ntn[5];	/* network specific address (in bcd) */
	/* link level parameters */
	u_short	xc_lproto:4,	/* link level protocol eg. CCITTPROTO_HDLC */
		xc_lptype:4,	/* protocol type eg. HDLCPROTO_LAPB */
		xc_lwsize:5,	/* link level window size */
		xc_ltrace:1,	/* link level tracing flag */
		xc_rsvd1:2;	/* for use by other link-level protocols */
	/* packet level parameters */
	u_short	xc_pwsize:3,	/* default window size */
		xc_psize:4,	/* default packet size 7=128, 8=256, ... */
D 2
		xc_type:2,	/* network type */
E 2
I 2
		xc_type:3,	/* network type */
E 2
#define X25_1976	0
#define X25_1980	1
#define X25_1984	2
I 2
#define X25_DDN		3
#define X25_BASIC	4
E 2
		xc_ptrace:1,	/* packet level tracing flag */
D 2
		xc_rsvd2:6;
E 2
I 2
		xc_rsvd2:5;
E 2
	u_char	xc_maxlcn;	/* max logical channels */
	u_char	xc_rsvd3;
};

/*
E 3
 *  X.25 Socket address structure.  It contains the network id, X.121
 *  address, facilities information, higher level protocol value (first four
 *  bytes of the User Data field), and up to 12 characters of User Data.
 */

struct	sockaddr_x25 {
D 2
	short	x25_family;	/* must be AF_CCITT */
E 2
I 2
	u_char	x25_len;
	u_char	x25_family;	/* must be AF_CCITT */
E 2
	short	x25_net;	/* network id code (usually a dnic) */
I 3
	char	x25_addr[16];	/* X.121 address (null terminated) */
E 3
	struct	x25opts {
		char	op_flags;	/* miscellaneous options */
I 3
					/* pk_var.h defines other lcd_flags */
E 3
#define X25_REVERSE_CHARGE	0x01	/* remote DTE pays for call */
#define X25_DBIT		0x02	/* not yet supported */
#define X25_MQBIT		0x04	/* prepend M&Q bit status byte to packet data */
#define X25_OLDSOCKADDR		0x08	/* uses old sockaddr structure */
I 8
#define X25_DG_CIRCUIT		0x10	/* lcd_flag: used for datagrams */
#define X25_DG_ROUTING		0x20	/* lcd_flag: peer addr not yet known */
#define X25_MBS_HOLD		0x40	/* lcd_flag: collect m-bit sequences */
E 8
		char	op_psize;	/* requested packet size */
#define X25_PS128		7
#define X25_PS256		8
#define X25_PS512		9
		char	op_wsize;	/* window size (1 .. 7) */
		char	op_speed;	/* throughput class */
	} x25_opts;
D 3
	char	x25_addr[16];	/* X.121 address (null terminated) */
E 3
	short	x25_udlen;	/* user data field length */
	char	x25_udata[16];	/* user data field */
};
I 3

/*
 * network configuration info
 * this structure must be 16 bytes long
 */

struct	x25config {
	struct	sockaddr_x25 xc_addr;
	/* link level parameters */
	u_short	xc_lproto:4,	/* link level protocol eg. CCITTPROTO_HDLC */
		xc_lptype:4,	/* protocol type eg. HDLCPROTO_LAPB */
D 11
		xc_lwsize:5,	/* link level window size */
E 11
		xc_ltrace:1,	/* link level tracing flag */
D 11
		xc_rsvd1:2;	/* for use by other link-level protocols */
E 11
I 11
		xc_lwsize:7;	/* link level window size */
	u_short	xc_lxidxchg:1,  /* link level XID exchange flag - NOT YET */
E 11
	/* packet level parameters */
D 11
	u_short	xc_pwsize:3,	/* default window size */
E 11
I 11
	        xc_rsvd1:2,
                xc_pwsize:3,	/* default window size */
E 11
		xc_psize:4,	/* default packet size 7=128, 8=256, ... */
		xc_type:3,	/* network type */
#define X25_1976	0
#define X25_1980	1
#define X25_1984	2
#define X25_DDN		3
#define X25_BASIC	4
		xc_ptrace:1,	/* packet level tracing flag */
D 9
		xc_rsvd2:5;
E 9
I 9
		xc_nodnic:1,	/* remove our dnic when calling on net */
D 11
		xc_prepnd0:1,	/* prepend 0 when making offnet calls */
		xc_rsvd2:3;
E 11
I 11
		xc_prepnd0:1;	/* prepend 0 when making offnet calls */
E 11
E 9
	u_short	xc_maxlcn;	/* max logical channels */
D 6
	u_short	xc_dg_idletimo;	/* timeout for idle datagram circuits.
E 6
I 6
	u_short	xc_dg_idletimo;	/* timeout for idle datagram circuits. */
E 6
};

#ifdef IFNAMSIZ
struct ifreq_x25 {
	char	ifr_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	x25config ifr_xc;
};
#define	SIOCSIFCONF_X25	_IOW('i', 12, struct ifreq_x25)	/* set ifnet config */
#define	SIOCGIFCONF_X25	_IOWR('i',13, struct ifreq_x25)	/* get ifnet config */
#endif
E 3
E 1
