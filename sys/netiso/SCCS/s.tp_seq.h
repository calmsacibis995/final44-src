h02460
s 00002/00002/00096
d D 8.1 93/06/10 23:20:56 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00097
d D 7.6 93/05/25 11:52:05 bostic 6 5
c trailing comment after #else or #endif
e
s 00009/00001/00089
d D 7.5 91/05/06 19:24:33 bostic 5 4
c new copyright; att/bsd/shared
e
s 00004/00000/00086
d D 7.4 90/01/16 21:39:42 sklower 4 3
c mitre additions for cong. control
e
s 00001/00000/00085
d D 7.3 89/08/29 13:45:28 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00000/00085
d D 7.2 89/04/22 11:55:25 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00085/00000/00000
d D 7.1 88/12/14 15:30:10 sklower 1 0
c date and time created 88/12/14 15:30:10 by sklower
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
		Copyright IBM Corporation 1987

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
/* 
 * ARGO TP
 *
 * $Header: tp_seq.h,v 5.1 88/10/12 12:20:59 root Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_seq.h,v $
I 3
D 5
 *	%W% (Berkeley) %G% *
E 5
E 3
 *
 * These macros perform sequence number arithmetic modulo (2**7 or 2**31).
 * The relevant fields in the tpcb are:
 *  	tp_seqmask : the mask of bits that define the sequence space.
 *  	tp_seqbit  : 1 + tp_seqmask
 *  	tp_seqhalf : tp_seqbit / 2 or half the sequence space (rounded up)
 * Not exactly fast, but at least it's maintainable.
 */

#ifndef __TP_SEQ__
#define __TP_SEQ__

#define SEQ(tpcb,x) \
	((x) & (tpcb)->tp_seqmask)

#define SEQ_GT(tpcb, seq, operand ) \
( ((int)((seq)-(operand)) > 0)\
? ((int)((seq)-(operand)) < (int)(tpcb)->tp_seqhalf)\
: !(-((int)(seq)-(operand)) < (int)(tpcb)->tp_seqhalf))

#define SEQ_GEQ(tpcb, seq, operand ) \
( ((int)((seq)-(operand)) >= 0)\
? ((int)((seq)-(operand)) < (int)(tpcb)->tp_seqhalf)\
: !((-((int)(seq)-(operand))) < (int)(tpcb)->tp_seqhalf))

#define SEQ_LEQ(tpcb, seq, operand ) \
( ((int)((seq)-(operand)) <= 0)\
? ((-(int)((seq)-(operand))) < (int)(tpcb)->tp_seqhalf)\
: !(((int)(seq)-(operand)) < (int)(tpcb)->tp_seqhalf))

#define SEQ_LT(tpcb, seq, operand ) \
( ((int)((seq)-(operand)) < 0)\
? ((-(int)((seq)-(operand))) < (int)(tpcb)->tp_seqhalf)\
: !(((int)(seq)-(operand)) < (int)(tpcb)->tp_seqhalf))
	
I 4
#define SEQ_MIN(tpcb, a, b) ( SEQ_GT(tpcb, a, b) ? b : a)

#define SEQ_MAX(tpcb, a, b) ( SEQ_GT(tpcb, a, b) ? a : b)

E 4
#define SEQ_INC(tpcb, Seq) ((++Seq), ((Seq) &= (tpcb)->tp_seqmask))

#define SEQ_DEC(tpcb, Seq)\
	((Seq) = (((Seq)+(unsigned)((int)(tpcb)->tp_seqbit - 1))&(tpcb)->tp_seqmask))

/* (amt) had better be less than the seq bit ! */

#define SEQ_SUB(tpcb, Seq, amt)\
	(((Seq) + (unsigned)((int)(tpcb)->tp_seqbit - amt)) & (tpcb)->tp_seqmask)
#define SEQ_ADD(tpcb, Seq, amt) (((Seq) + (unsigned)amt) & (tpcb)->tp_seqmask)


#define IN_RWINDOW(tpcb, seq, lwe, uwe)\
	( SEQ_GEQ(tpcb, seq, lwe) && SEQ_LT(tpcb, seq, uwe) )

#define IN_SWINDOW(tpcb, seq, lwe, uwe)\
	( SEQ_GT(tpcb, seq, lwe) && SEQ_LEQ(tpcb, seq, uwe) )

D 6
#endif __TP_SEQ__
E 6
I 6
#endif /* __TP_SEQ__ */
E 6
E 1
