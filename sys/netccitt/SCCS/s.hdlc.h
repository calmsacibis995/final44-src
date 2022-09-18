h25699
s 00002/00002/00128
d D 8.1 93/06/10 22:53:11 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00017/00124
d D 7.4 91/05/06 18:40:30 bostic 5 4
c new copyright; att/bsd/shared
e
s 00039/00068/00102
d D 7.3 90/05/25 17:20:01 sklower 4 2
c ordering of bit fields needs better descrimination than #ifdef vax or su n
e
s 00020/00062/00108
d R 7.3 90/05/25 17:11:39 sklower 3 2
c there are other entities besides #ifdef sun and #ifdef vax
e
s 00013/00001/00157
d D 7.2 90/05/11 15:22:01 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00158/00000/00000
d D 7.1 90/05/11 11:19:37 sklower 1 0
c date and time created 90/05/11 11:19:37 by sklower
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
D 5
/*
E 5
I 5
/*-
E 5
 * Copyright (c) University of British Columbia, 1984
D 5
 * Copyright (c) 1990 The Regents of the University of California.
E 5
I 5
D 6
 * Copyright (c) 1991 The Regents of the University of California.
E 5
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 5
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
E 5
I 5
 * This code is derived from software contributed to Berkeley by the
 * Laboratory for Computation Vision and the Computer Science Department
E 5
 * of the University of British Columbia.
 *
D 4
 * %sccs.include.redist.c%
E 4
I 4
D 5
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the University of California, Berkeley and its contributors''
 * in the documentation or other materials provided with the distribution
 * and in all advertising materials mentioning features or use of this
 * software. Neither the name of the University nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 *
 *	%W% (Berkeley) %G%
 */
I 5

E 5
E 2
D 4

typedef char    bool;
E 4
I 4
#ifndef ORDER4
E 4
#define FALSE   0
#define TRUE    1
D 4

E 4
typedef u_char octet;
I 4
typedef char    bool;
E 4

I 4
/*
 *  HDLC Packet format definitions
 *  This will eventually have to be rewritten without reference
 *  to bit fields, to be compliant with ANSI C and alignment safe.
 */

#if BYTE_ORDER == BIG_ENDIAN
#define ORDER4(a, b, c, d) a , b , c , d
#define ORDER5(a, b, c, d, e) a , b , c , d , e
#endif

#if BYTE_ORDER == LITTLE_ENDIAN
#define ORDER4(a, b, c, d) d , c , b , a
#define ORDER5(a, b, c, d, e) e , d , c , b , a
#endif
#endif

E 4
#define MAX_INFO_LEN    4096+3+4
#define ADDRESS_A       3	/* B'00000011' */
#define ADDRESS_B       1	/* B'00000001' */

struct Hdlc_iframe {
	octet	address;
D 4
#ifdef vax
	unsigned hdlc_0:1;
	unsigned ns:3;
	unsigned pf:1;
	unsigned nr:3;
#endif
#ifdef sun
	unsigned nr:3;
	unsigned pf:1;
	unsigned ns:3;
	unsigned hdlc_0:1;
#endif
	char    i_field[MAX_INFO_LEN];
E 4
I 4
	octet	ORDER4(nr:3, pf:1, ns:3, hdlc_0:1);
	octet    i_field[MAX_INFO_LEN];
E 4
};

struct Hdlc_sframe {
	octet	address;
D 4
#ifdef vax
	unsigned hdlc_01:2;
	unsigned s2:2;
	unsigned pf:1;
	unsigned nr:3;
#endif
#ifdef sun
	unsigned nr:3;
	unsigned pf:1;
	unsigned s2:2;
	unsigned hdlc_01:2;
#endif
E 4
I 4
	octet	ORDER4(nr:3, pf:1, s2:2, hdlc_01:2);
E 4
};

struct	Hdlc_uframe {
	octet	address;
D 4
#ifdef vax
	unsigned hdlc_11:2;
	unsigned m2:2;
	unsigned pf:1;
	unsigned m3:3;
#endif
#ifdef sun
	unsigned m3:3;
	unsigned pf:1;
	unsigned m2:2;
	unsigned hdlc_11:2;
#endif
E 4
I 4
	octet	ORDER4(m3:3, pf:1, m2:2, hdlc_11:2);
E 4
};

struct	Frmr_frame {
	octet	address;
	octet	control;
	octet	frmr_control;
D 4
#ifdef vax
	unsigned frmr_f2_0:1;
	unsigned frmr_ns:3;
	unsigned frmr_f1_0:1;
	unsigned frmr_nr:3;
#endif
#ifdef sun
	unsigned frmr_nr:3;
	unsigned frmr_f1_0:1;
	unsigned frmr_ns:3;
	unsigned frmr_f2_0:1;
#endif
#ifdef vax
	unsigned frmr_w:1;
	unsigned frmr_x:1;
	unsigned frmr_y:1;
	unsigned frmr_z:1;
	unsigned frmr_0000:4;
#endif
#ifdef sun
	unsigned frmr_0000:4;
	unsigned frmr_z:1;
	unsigned frmr_y:1;
	unsigned frmr_x:1;
	unsigned frmr_w:1;
#endif
E 4
I 4
	octet	ORDER4(frmr_nr:3, frmr_f1_0:1, frmr_ns:3, frmr_f2_0:1);
	octet	ORDER5(frmr_0000:4, frmr_z:1, frmr_y:1, frmr_x:1, frmr_w:1);
E 4
};

#define HDHEADERLN	2
#define MINFRLN		2		/* Minimum frame length. */

struct	Hdlc_frame {
	octet	address;
	octet	control;
D 4
	char	info[3];	/* min for FRMR */
E 4
I 4
	octet	info[3];	/* min for FRMR */
E 4
};

#define SABM_CONTROL 057	/* B'00101111' */
#define UA_CONTROL   0143	/* B'01100011' */
#define DISC_CONTROL 0103	/* B'01000011' */
#define DM_CONTROL   017	/* B'00001111' */
#define FRMR_CONTROL 0207	/* B'10000111' */
#define RR_CONTROL   01		/* B'00000001' */
#define RNR_CONTROL  05		/* B'00000101' */
#define REJ_CONTROL  011	/* B'00001001' */

#define POLLOFF  0
#define POLLON   1

/* Define Link State constants. */

#define INIT		0
#define DM_SENT		1
#define SABM_SENT	2
#define ABM		3
#define WAIT_SABM	4
#define WAIT_UA		5
#define DISC_SENT	6
#define DISCONNECTED	7
#define MAXSTATE	8

/* The following constants are used in a switch statement to process
   frames read from the communications line. */

#define SABM     0 * MAXSTATE
#define DM       1 * MAXSTATE
#define DISC     2 * MAXSTATE
#define UA       3 * MAXSTATE
#define FRMR     4 * MAXSTATE
#define RR       5 * MAXSTATE
#define RNR      6 * MAXSTATE
#define REJ      7 * MAXSTATE
#define IFRAME   8 * MAXSTATE
#define ILLEGAL  9 * MAXSTATE

#define T1	(3 * PR_SLOWHZ)		/*  IFRAME TIMEOUT - 3 seconds */
#define T3	(T1 / 2)		/*  RR generate timeout - 1.5 seconds */
#define N2	10
#define MODULUS 8
#define MAX_WINDOW_SIZE 7

#define Z  0
#define Y  1
#define X  2
#define W  3
#define A  4

#define TX 0
#define RX 1

bool	range_check ();
bool	valid_nr ();
struct	mbuf *hd_remove ();
E 1
