h50239
s 00001/00001/00049
d D 8.3 95/06/21 15:59:03 karels 14 13
c fix typo in tcp_random18 ifdef
e
s 00017/00003/00033
d D 8.2 95/05/24 06:00:24 karels 13 12
c changes to randomize iss (somewhat); use a random component in the increment.
c Increase rate of periodic increment, but leave the per-connection increment
c about the same.  Small cleanup in code to handle bad (e.g. spoofed) SYN:
c remove redundant code, add counter (perhaps should count only if SYN is set),
c and simplify slightly for RST.
e
s 00002/00002/00034
d D 8.1 93/06/10 23:05:48 bostic 12 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00036
d R 7.5 93/06/04 17:08:23 bostic 11 10
c prototype everything
e
s 00001/00011/00035
d D 7.4 90/06/28 21:40:34 bostic 10 9
c new copyright notice
e
s 00010/00005/00036
d D 7.3 88/06/29 17:07:34 bostic 9 8
c install approved copyright notice
e
s 00008/00002/00033
d D 7.2 87/12/07 17:46:37 bostic 8 7
c use Berkeley specific header
e
s 00001/00001/00034
d D 7.1 86/06/05 00:31:40 mckusick 7 6
c 4.3BSD release version
e
s 00001/00001/00034
d D 6.4 85/10/15 08:57:25 karels 6 5
c faster ISS change
e
s 00002/00002/00033
d D 6.3 85/10/15 08:56:56 karels 5 3
c keep rcv_adv in synch with rcv_nxt
e
s 00002/00002/00033
d R 6.3 85/10/14 17:20:58 karels 4 3
c keep rcv_adv in synch with rcv_nxt
e
s 00007/00001/00028
d D 6.2 85/06/08 12:44:10 mckusick 3 2
c Add copyright
e
s 00000/00000/00029
d D 6.1 83/07/29 07:12:48 sam 2 1
c 4.2 distribution
e
s 00029/00000/00000
d D 4.1 81/11/29 22:19:49 wnj 1 0
c date and time created 81/11/29 22:19:49 by wnj
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
D 7
 * Copyright (c) 1982 Regents of the University of California.
E 7
I 7
D 12
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 7
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 12
I 12
D 13
 * Copyright (c) 1982, 1986, 1993
E 13
I 13
 * Copyright (c) 1982, 1986, 1993, 1995
E 13
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 3

/*
 * TCP sequence numbers are 32 bit integers operated
 * on with modular arithmetic.  These macros can be
 * used to compare such integers.
 */
#define	SEQ_LT(a,b)	((int)((a)-(b)) < 0)
#define	SEQ_LEQ(a,b)	((int)((a)-(b)) <= 0)
#define	SEQ_GT(a,b)	((int)((a)-(b)) > 0)
#define	SEQ_GEQ(a,b)	((int)((a)-(b)) >= 0)

/*
 * Macros to initialize tcp sequence numbers for
 * send and receive from initial send and receive
 * sequence numbers.
 */
#define	tcp_rcvseqinit(tp) \
D 5
	(tp)->rcv_nxt = (tp)->irs + 1
E 5
I 5
	(tp)->rcv_adv = (tp)->rcv_nxt = (tp)->irs + 1
E 5

#define	tcp_sendseqinit(tp) \
	(tp)->snd_una = (tp)->snd_nxt = (tp)->snd_max = (tp)->snd_up = \
	    (tp)->iss

D 5
#define	TCP_ISSINCR	128		/* increment for tcp_iss each second */
E 5
I 5
D 6
#define	TCP_ISSINCR	128	/* increment for tcp_iss each second */
E 6
I 6
D 13
#define	TCP_ISSINCR	(125*1024)	/* increment for tcp_iss each second */
E 6
E 5

E 13
#ifdef KERNEL
I 13
/*
 * Increment for tcp_iss each second.
 * This is designed to increment at the standard 250 KB/s,
 * but with a random component averaging 128 KB.
 * We also increment tcp_iss by a quarter of this amount
 * each time we use the value for a new connection.
 * If defined, the tcp_random18() macro should produce a
 * number in the range [0-0x3ffff] that is hard to predict.
 */
D 14
#ifndef tcp_tandom18
E 14
I 14
#ifndef tcp_random18
E 14
#define	tcp_random18()	((random() >> 14) & 0x3ffff)
#endif
#define	TCP_ISSINCR	(122*1024 + tcp_random18())

E 13
tcp_seq	tcp_iss;		/* tcp initial send seq # */
I 13
#else
#define	TCP_ISSINCR	(250*1024)	/* increment for tcp_iss each second */
E 13
#endif
E 1
