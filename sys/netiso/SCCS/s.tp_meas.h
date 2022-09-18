h55391
s 00002/00002/00066
d D 8.1 93/06/10 23:20:37 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00067
d D 7.6 93/05/25 11:51:57 bostic 6 5
c trailing comment after #else or #endif
e
s 00009/00001/00059
d D 7.5 91/05/06 19:24:27 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00005/00058
d D 7.4 89/09/22 00:44:13 sklower 4 3
c fixes to tracing and avoiding silly window between
c socket layer and transport; more changes to come to usrreq and tp_send.
e
s 00001/00000/00062
d D 7.3 89/08/29 13:45:13 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00005/00000/00057
d D 7.2 89/04/22 11:55:11 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00057/00000/00000
d D 7.1 88/12/14 15:30:05 sklower 1 0
c date and time created 88/12/14 15:30:05 by sklower
e
u
U
t
T
I 5
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 5
I 1
/***********************************************************
D 4
		Copyright IBM Corporation 1987
E 4
I 4
				Copyright IBM Corporation 1987
E 4

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
I 3
D 5
/*	%W% (Berkeley) %G% */
E 5
E 3
I 2
D 4
#ifdef TPPT
#define TP_PERF_MEAS
#endif TPPT
E 4
I 4
#ifdef TP_PERF_MEAS
E 4
#define tpmeas(a, b, t, c, d, e) \
	Tpmeas((u_int)(a), (u_int)(b), t, (u_int)(c), (u_int)(d), (u_int)(e))
E 2
D 4
#ifdef TP_PERF_MEAS
E 4

struct tp_Meas {
	int			tpm_tseq;
	u_char		tpm_kind;
	u_short 	tpm_ref;
	u_short		tpm_size;
	u_short		tpm_window;
	u_int		tpm_seq;
	struct timeval	tpm_time;
};

#define TPMEASN 4000
extern int tp_Measn;
extern struct tp_Meas tp_Meas[];

/*
 * the kinds of events for packet tracing are:
 */
#define TPtime_from_session	0x01
#define TPtime_to_session	0x02
#define TPtime_ack_rcvd		0x03 
#define TPtime_ack_sent		0x04
#define TPtime_from_ll		0x05
#define TPtime_to_ll		0x06
#define TPsbsend			0x07 
#define TPtime_open			0x08
#define TPtime_open_X		0x28 /* xtd format */
#define TPtime_close		0x09

D 6
#endif TP_PERF_MEAS
E 6
I 6
#endif /* TP_PERF_MEAS */
E 6
E 1
