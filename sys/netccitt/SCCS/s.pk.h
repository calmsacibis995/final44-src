h58012
s 00002/00002/00179
d D 8.1 93/06/10 22:53:40 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00020/00146
d D 7.10 92/12/08 16:19:26 sklower 10 9
c contributions from Dirk Husemann
e
s 00002/00002/00164
d D 7.9 91/11/13 10:48:39 sklower 9 8
c stupid bug in extracting LCN, fix by dkhusema@uni-erlangen.de
e
s 00001/00001/00165
d D 7.8 91/04/30 16:34:14 sklower 8 7
c DIAGNOSTIC is already defined for general error catching
e
s 00005/00001/00161
d D 7.7 91/03/12 15:05:58 sklower 7 6
c allow for two more packet types defined in iso 8208
c this version works with ISODE 6.7m
e
s 00001/00001/00161
d D 7.6 91/01/09 15:34:22 sklower 6 5
c change  pk_template to return mbuf to remove dtom from kernel
e
s 00004/00000/00158
d D 7.5 90/10/30 21:04:49 sklower 5 4
c allow for more than 255 connections on an interface; i.e.
c make macros for encoding and decoding lcn <-> logical_chanel and lc_group_numbers
e
s 00003/00005/00155
d D 7.4 90/10/03 15:38:57 sklower 4 3
c got x.25 bit field declarations backwards
e
s 00001/00001/00159
d D 7.3 90/08/30 18:48:28 sklower 3 2
c this version compiles; completely untested
e
s 00039/00039/00121
d D 7.2 90/05/15 19:26:30 sklower 2 1
c world has more than sun's and vaxes; 
c eventually, we must give up bit fields, due to potentially presumed 
c alignments.
e
s 00160/00000/00000
d D 7.1 90/05/11 11:19:38 sklower 1 0
c date and time created 90/05/11 11:19:38 by sklower
e
u
U
t
T
I 1
D 2
/* Copyright (c) University of British Columbia, 1984 */
E 2
I 2
/*
 * Copyright (c) University of British Columbia, 1984
D 10
 * Copyright (c) 1990 The Regents of the University of California.
E 10
I 10
D 11
 * Copyright (c) 1990, 1992 The Regents of the University of California.
E 10
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

/*
 *
 *  X.25 Packet Level Definitions:
 *
 */

/* Packet type identifier field defintions. */

#define X25_CALL                         11
#define X25_CALL_ACCEPTED                15   
#define X25_CLEAR                        19
#define X25_CLEAR_CONFIRM                23  
#define X25_DATA                          0   
#define X25_INTERRUPT                    35   
#define X25_INTERRUPT_CONFIRM            39   

#define X25_RR                            1   
#define X25_RNR                           5   
I 7
#define X25_REJECT			  9
E 7
#define X25_RESET                        27 
#define X25_RESET_CONFIRM                31   
I 7
#define X25_DIAGNOSTIC			241
E 7

#define X25_RESTART                     251     
#define X25_RESTART_CONFIRM		255 

/* Restart cause field definitions. */

I 10
#define X25_RESTART_DTE_ORIGINATED	  0
E 10
#define X25_RESTART_LOCAL_PROCEDURE_ERROR 1
#define X25_RESTART_NETWORK_CONGESTION	  3
#define X25_RESTART_NETWORK_OPERATIONAL	  7
I 10
#define X25_RESTART_DTE_ORIGINATED2	  128
E 10

I 10

E 10
/* Miscellaneous definitions. */

#define DATA_PACKET_DESIGNATOR		0x01
#define RR_OR_RNR_PACKET_DESIGNATOR	0x02
#define RR_PACKET_DESIGNATOR		0x04

#define DEFAULT_WINDOW_SIZE		2
#define MODULUS				8

#define ADDRLN				1
#define MAXADDRLN			15
#define FACILITIESLN			1
#define MAXFACILITIESLN			10
#define MAXUSERDATA			16
#define MAXCALLINFOLN			1+15+1+10+16

#define PACKET_OK			0
#define IGNORE_PACKET			1
#define ERROR_PACKET			2

typedef char    bool;
#define FALSE	0
#define TRUE	1

/*
 *  X.25 Packet format definitions
I 2
 *  This will eventually have to be rewritten without reference
 *  to bit fields, to be ansi C compliant and allignment safe.
E 2
 */

D 2
typedef u_char octet;
E 2
I 2
D 10
#if BYTE_ORDER == BIG_ENDIAN
#define ORDER2(a, b) a , b
D 4
#define ORDER3(a, b, c) a , b , c
E 4
#define ORDER4(a, b, c, d) a , b , c , d
#endif
E 2

D 2
struct x25_calladdr {
#ifdef vax
	unsigned called_addrlen:4;
	unsigned calling_addrlen:4;
#endif 
#ifdef sun
	unsigned calling_addrlen:4;
	unsigned called_addrlen:4;
E 2
I 2
#if BYTE_ORDER == LITTLE_ENDIAN
#define ORDER2(a, b) b , a
D 4
#define ORDER3(a, b, c) c , b , a
E 4
#define ORDER4(a, b, c, d) d , c , b , a
E 2
#endif
D 2
	char address_field[MAXADDRLN];
};
E 2

E 10
D 2
#define FACILITIES_REVERSE_CHARGE	0x1
#define FACILITIES_THROUGHPUT		0x2
#define FACILITIES_PACKETSIZE		0x42
#define FACILITIES_WINDOWSIZE		0x43
E 2
I 2
typedef u_char octet;
E 2

D 2
#define PKHEADERLN	3
E 2
I 2
struct x25_calladdr {
D 4
	octet ORDER2(called_addrlen:4, calling_addrlen:4);
E 4
I 4
D 10
	octet ORDER2(calling_addrlen:4, called_addrlen:4);
E 10
I 10
	octet addrlens;
E 10
E 4
	octet address_field[MAXADDRLN];
D 3
}
E 3
I 3
};
E 3
E 2

struct x25_packet {
D 2
#ifdef vax
	unsigned lc_group_number:4;
	unsigned fmt_identifier:3;
	unsigned q_bit:1;
#endif
#ifdef sun
	unsigned q_bit:1;
	unsigned fmt_identifier:3;
	unsigned lc_group_number:4;
#endif
E 2
I 2
D 4
	octet ORDER3(lc_group_number:4, fmt_identifier:3, q_bit:1);
E 4
I 4
D 10
	octet ORDER4(q_bit:1, d_bit:1, fmt_identifier:2, lc_group_number:4);
E 10
I 10
	octet bits;
E 10
E 4
E 2
	octet logical_channel_number;
	octet packet_type;
	octet packet_data;
};
I 10
#define packet_cause packet_data
E 10

struct data_packet {
D 2
#ifdef vax
	unsigned z:1;
	unsigned ps:3;
	unsigned m_bit:1;
	unsigned pr:3;
#endif
#ifdef sun
	unsigned pr:3;
	unsigned m_bit:1;
	unsigned ps:3;
	unsigned z:1;
#endif
E 2
I 2
D 4
	octet ORDER4(z:1, ps:3, m_bit:1, pr:3);
E 4
I 4
D 10
	octet ORDER4(pr:3, m_bit:1, ps:3, z:1);
E 10
I 10
	octet bits;
E 10
E 4
E 2
};
I 2

#define FACILITIES_REVERSE_CHARGE	0x1
#define FACILITIES_THROUGHPUT		0x2
#define FACILITIES_PACKETSIZE		0x42
#define FACILITIES_WINDOWSIZE		0x43

#define PKHEADERLN	3

I 10
#define DP(xp)          (((struct data_packet *)&(xp) -> packet_type) -> bits)
#define PS(xp)           X25GBITS(DP(xp), p_s)
#define PR(xp)           X25GBITS(DP(xp), p_r)
#define MBIT(xp)         X25GBITS(DP(xp), m_bit)
#define SPR(xp, v)       X25SBITS(DP(xp), p_r, (v))
#define SPS(xp, v)       X25SBITS(DP(xp), p_s, (v))
#define SMBIT(xp, v)     X25SBITS(DP(xp), m_bit, (v))
E 10
E 2

D 10
#define PR(xp)		(((struct data_packet *)&xp -> packet_type)->pr)
#define PS(xp)		(((struct data_packet *)&xp -> packet_type)->ps)
#define MBIT(xp)	(((struct data_packet *)&xp -> packet_type)->m_bit)
E 10
I 5
#define LCN(xp)		(xp -> logical_channel_number + \
D 9
	(xp -> lc_group_number ? (xp -> lc_group_number >> 8) : 0))
E 9
I 9
D 10
	(xp -> lc_group_number ? (xp -> lc_group_number << 8) : 0))
E 10
I 10
	(X25GBITS(xp -> bits, lc_group_number) ? (X25GBITS(xp -> bits, lc_group_number) << 8) : 0))
E 10
E 9
#define SET_LCN(xp, lcn) ((xp -> logical_channel_number = lcn), \
D 9
	(xp -> lc_group_number = lcn > 255 ? lcn >> 8 : 0))
E 9
I 9
D 10
	(xp -> lc_group_number = (lcn > 255 ? (lcn >> 8) : 0)))
E 10
I 10
	(X25SBITS(xp -> bits, lc_group_number, lcn > 255 ? lcn >> 8 : 0)))
E 10
E 9
E 5

D 6
struct x25_packet *pk_template ();
E 6
I 6
struct mbuf *pk_template ();
E 6

/* Define X.25 packet level states. */

/* Call setup and clearing substates.  */

#define LISTEN           0
#define READY            1
#define RECEIVED_CALL    2
#define SENT_CALL        3
#define DATA_TRANSFER    4
#define RECEIVED_CLEAR   5
#define SENT_CLEAR       6

/* DTE states. */

#define DTE_WAITING		7
#define DTE_RECEIVED_RESTART	8
#define DTE_SENT_RESTART	9
#define DTE_READY		0

D 10
#define MAXSTATES		10
E 10
I 10
/* Cleaning out ... */
E 10

I 10
#define LCN_ZOMBIE 		10

#define MAXSTATES		11

E 10
/*
 *  The following definitions are used in a switch statement after
 *  determining the packet type.  These values are returned by the
 *  pk_decode procedure. 
 */

#define CALL             0 * MAXSTATES
#define CALL_ACCEPTED    1 * MAXSTATES
#define CLEAR            2 * MAXSTATES
#define CLEAR_CONF       3 * MAXSTATES
#define DATA             4 * MAXSTATES
#define INTERRUPT        5 * MAXSTATES
#define INTERRUPT_CONF   6 * MAXSTATES
#define RR               7 * MAXSTATES
#define RNR              8 * MAXSTATES
#define RESET            9 * MAXSTATES
#define RESET_CONF      10 * MAXSTATES
#define RESTART         11 * MAXSTATES
#define RESTART_CONF    12 * MAXSTATES
D 7
#define INVALID_PACKET  13 * MAXSTATES
E 7
I 7
#define REJECT          13 * MAXSTATES
D 8
#define DIAGNOSTIC      14 * MAXSTATES
E 8
I 8
#define DIAG_TYPE       14 * MAXSTATES
E 8
#define INVALID_PACKET  15 * MAXSTATES
E 7
#define DELETE_PACKET	INVALID_PACKET
I 10

/*
 * The following definitions are used by the restart procedures
 * for noting wether the PLE is supposed to behave as DTE or DCE
 * (essentially necessary for operation over LLC2)
 */
#define	DTE_DXERESOLVING	0x0001
#define	DTE_PLAYDTE		0x0002
#define	DTE_PLAYDCE		0x0004
#define DTE_CONNECTPENDING	0x0010
#define	DTE_PRETENDDTE		0x0020

#define MAXRESTARTCOLLISIONS	10
E 10
E 1
