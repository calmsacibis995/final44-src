h61391
s 00002/00002/00129
d D 8.1 93/06/10 22:45:45 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00127
d D 7.5 93/06/04 17:31:15 bostic 5 4
c prototype everything
e
s 00001/00011/00130
d D 7.4 90/06/28 21:32:45 bostic 4 3
c new copyright notice
e
s 00025/00007/00116
d D 7.3 90/01/20 17:34:16 sam 3 2
c new version from van (beta release)
e
s 00016/00019/00107
d D 7.2 89/06/30 18:16:01 karels 2 1
c merge new code from van, sundry cleanups
e
s 00126/00000/00000
d D 7.1 89/06/29 09:31:16 karels 1 0
c initial version from van
e
u
U
t
T
I 3
/*	%M%	%I%	%E%	*/
E 3
I 1
/*
D 2
 *			THIS CODE IS NOT FOR DISTRIBUTION!
 *	KEEP YOUR GRUBBY HANDS OFF UNLESS AUTHORIZED BY VAN JACOBSON TO COPY!
 *			ASK SAM, MIKE, OR BILL ABOUT IT.
 */

/*
E 2
 * Definitions for tcp compression routines.
 *
D 3
 * Copyright (c) 1988, 1989 by Van Jacobson, Lawrence Berkeley Laboratory
E 3
I 3
 * $Header: slcompress.h,v 1.10 89/12/31 08:53:02 van Exp $
 *
D 6
 * Copyright (c) 1989 Regents of the University of California.
E 3
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 2
 * $Header: slcompress.h,v 1.3 89/03/19 18:10:38 van Locked $
E 2
I 2
D 3
 * $Header: slcompress.h,v 1.6 89/06/05 08:29:13 van Exp $
E 3
I 3
D 4
 * Redistribution and use in source and binary forms are permitted
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	Van Jacobson (van@helios.ee.lbl.gov), Dec 31, 1989:
 *	- Initial distribution.
E 3
E 2
 */

#define MAX_STATES 16		/* must be > 2 and < 256 */
#define MAX_HDR MLEN		/* XXX 4bsd-ism: should really be 128 */

/*
 * Compressed packet format:
 *
 * The first octet contains the packet type (top 3 bits), TCP
 * 'push' bit, and flags that indicate which of the 4 TCP sequence
 * numbers have changed (bottom 5 bits).  The next octet is a
 * conversation number that associates a saved IP/TCP header with
 * the compressed packet.  The next two octets are the TCP checksum
 * from the original datagram.  The next 0 to 15 octets are
 * sequence number changes, one change per bit set in the header
 * (there may be no changes and there are two special cases where
 * the receiver implicitly knows what changed -- see below).
D 2
 *
 * { Note that the ip version number field this overlays is 4 bits
 *   wide, and that we use type 4 to pass thru unaltered packets,
 *   type 5 to pass thru uncompressed packets that will be state
 *   information indexed by conversation. If msb (e.g type 8) is
 *   set, the other type bits are stolen to encode the difference
 *   information of a compressed TCP packet. -wfj }
E 2
 * 
 * There are 5 numbers which can change (they are always inserted
 * in the following order): TCP urgent pointer, window,
 * acknowlegement, sequence number and IP ID.  (The urgent pointer
 * is different from the others in that its value is sent, not the
 * change in value.)  Since typical use of SLIP links is biased
 * toward small packets (see comments on MTU/MSS below), changes
 * use a variable length coding with one octet for numbers in the
 * range 1 - 255 and 3 octets (0, MSB, LSB) for numbers in the
 * range 256 - 65535 or 0.  (If the change in sequence number or
 * ack is more than 65535, an uncompressed packet is sent.)
 */

/*
 * Packet types (must not conflict with IP protocol version)
 *
 * The top nibble of the first octet is the packet type.  There are
 * three possible types: IP (not proto TCP or tcp with one of the
 * control flags set); uncompressed TCP (a normal IP/TCP packet but
 * with the 8-bit protocol field replaced by an 8-bit connection id --
 * this type of packet syncs the sender & receiver); and compressed
 * TCP (described above).
 *
 * LSB of 4-bit field is TCP "PUSH" bit (a worthless anachronism) and
 * is logically part of the 4-bit "changes" field that follows.  Top
 * three bits are actual packet type.  For backward compatibility
 * and in the interest of conserving bits, numbers are chosen so the
 * IP protocol version number (4) which normally appears in this nibble
 * means "IP packet".
 */

/* packet types */
#define TYPE_IP 0x40
D 2
#define TYPE_UNCOMPRESSED_TCP 0x50
E 2
I 2
#define TYPE_UNCOMPRESSED_TCP 0x70
E 2
#define TYPE_COMPRESSED_TCP 0x80
#define TYPE_ERROR 0x00

/* Bits in first octet of compressed packet */
#define NEW_C	0x40	/* flag bits for what changed in a packet */
#define NEW_I	0x20
#define NEW_S	0x08
#define NEW_A	0x04
#define NEW_W	0x02
#define NEW_U	0x01

/* reserved, special-case values of above */
#define SPECIAL_I (NEW_S|NEW_W|NEW_U)		/* echoed interactive traffic */
#define SPECIAL_D (NEW_S|NEW_A|NEW_W|NEW_U)	/* unidirectional data */
#define SPECIALS_MASK (NEW_S|NEW_A|NEW_W|NEW_U)

#define TCP_PUSH_BIT 0x10


/*
 * "state" data for each active tcp conversation on the wire.  This is
 * basically a copy of the entire IP/TCP header from the last packet
 * we saw from the conversation together with a small identifier
 * the transmit & receive ends of the line use to locate saved header.
 */
struct cstate {
	struct cstate *cs_next;	/* next most recently used cstate (xmit only) */
	u_short cs_hlen;	/* size of hdr (receive only) */
	u_char cs_id;		/* connection # associated with this state */
	u_char cs_filler;
	union {
D 3
		char hdr[MAX_HDR];
E 3
I 3
		char csu_hdr[MAX_HDR];
E 3
		struct ip csu_ip;	/* ip/tcp hdr from most recent packet */
D 3
	} u;
E 3
I 3
	} slcs_u;
E 3
};
D 3
#define cs_ip u.csu_ip
E 3
I 3
#define cs_ip slcs_u.csu_ip
#define cs_hdr slcs_u.csu_hdr
E 3

/*
 * all the state data for one serial line (we need one of these
 * per line).
 */
struct slcompress {
D 2
	struct cstate *last_cs;			/* most recently used tstate */
	u_char last_recv;			/* last rcvd conn. id */
	u_char last_xmit;			/* last sent conn. id */
E 2
I 2
	struct cstate *last_cs;	/* most recently used tstate */
	u_char last_recv;	/* last rcvd conn. id */
	u_char last_xmit;	/* last sent conn. id */
E 2
	u_short flags;
I 2
D 3
#ifndef NO_SL_STATS
E 3
I 3
#ifndef SL_NO_STATS
E 3
	int sls_packets;	/* outbound packets */
	int sls_compressed;	/* outbound compressed packets */
	int sls_searches;	/* searches for connection state */
	int sls_misses;		/* times couldn't find conn. state */
	int sls_uncompressedin;	/* inbound uncompressed packets */
	int sls_compressedin;	/* inbound compressed packets */
	int sls_errorin;	/* inbound unknown type packets */
	int sls_tossed;		/* inbound packets tossed because of error */
#endif
E 2
	struct cstate tstate[MAX_STATES];	/* xmit connection states */
	struct cstate rstate[MAX_STATES];	/* receive connection states */
};
/* flag values */
#define SLF_TOSS 1		/* tossing rcvd frames because of input err */

D 5
extern void sl_compress_init(/* struct slcompress * */);
D 3
extern u_char sl_compress_tcp(/* struct mbuf *, struct ip *, struct slcompress * */);
E 3
I 3
extern u_char sl_compress_tcp(/* struct mbuf *, struct ip *,
				struct slcompress *, int compress_cid_flag */);
E 3
D 2
extern struct mbuf *sl_uncompress_tcp(/* struct mbuf *, u_char, struct slcompress * */);
E 2
I 2
extern int sl_uncompress_tcp(/* u_char **, int,  u_char, struct slcompress * */);
E 5
I 5
void	 sl_compress_init __P((struct slcompress *));
u_int	 sl_compress_tcp __P((struct mbuf *,
	    struct ip *, struct slcompress *, int));
int	 sl_uncompress_tcp __P((u_char **, int, u_int, struct slcompress *));
E 5
E 2
E 1
