h60384
s 00002/00002/00099
d D 8.1 93/06/10 23:20:34 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00100
d D 7.6 93/05/25 11:51:56 bostic 6 5
c trailing comment after #else or #endif
e
s 00005/00004/00096
d D 7.5 92/10/11 12:22:03 bostic 5 4
c make kernel includes standard
e
s 00009/00005/00091
d D 7.4 91/05/06 19:24:26 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00095
d D 7.3 89/08/29 13:45:11 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00003/00002/00092
d D 7.2 89/04/22 11:55:10 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00094/00000/00000
d D 7.1 88/12/14 15:30:04 sklower 1 0
c date and time created 88/12/14 15:30:04 by sklower
e
u
U
t
T
I 4
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

E 4
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
 * $Header: tp_meas.c,v 5.2 88/11/18 17:28:04 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_meas.c,v $
I 3
D 4
 *	%W% (Berkeley) %G% *
E 4
E 3
 * 
 * tp_meas.c : create a performance measurement event
 * in the circular buffer tp_Meas[]
 */
D 4

#ifndef lint
static char *rcsid = "$Header: tp_meas.c,v 5.2 88/11/18 17:28:04 nhall Exp $";
#endif lint
E 4

D 5
#include "types.h"
#include "time.h"
D 2
#include "../netiso/tp_meas.h"
E 2
I 2
#include "argo_debug.h"
#include "tp_meas.h"
E 5
I 5
#include <sys/types.h>
#include <sys/time.h>

#include <netiso/argo_debug.h>
#include <netiso/tp_meas.h>
E 5
E 2

extern struct timeval time;

#ifdef TP_PERF_MEAS
int		tp_Measn = 0;
struct tp_Meas tp_Meas[TPMEASN];

/*
 * NAME:	 tpmeas()
 *
 * CALLED FROM: tp_emit(), tp_soisdisconecting(), tp_soisdisconnected()
 *	tp0_stash(), tp_stash(), tp_send(), tp_goodack(), tp_usrreq()
 *
 * FUNCTION and ARGUMENTS:
 *  stashes a performance-measurement event for the given reference (ref)
 *  (kind) tells which kind of event, timev is the time to be stored
 *  with this event, (seq), (win), and (size) are integers that usually
 *  refer to the sequence number, window number (on send) and 
 *  size of tpdu or window.
 *
 * RETURNS:		Nada
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
void
D 2
tpmeas(ref, kind, timev, seq, win, size)
E 2
I 2
Tpmeas(ref, kind, timev, seq, win, size)
E 2
	u_int 	ref;
	u_int	kind;
	struct 	timeval *timev;
	u_int	seq, win, size;
{
	register struct tp_Meas *tpm;
	static int mseq;

	tpm = &tp_Meas[tp_Measn++];
	tp_Measn %= TPMEASN;

	tpm->tpm_kind = kind;
	tpm->tpm_tseq = mseq++;
	tpm->tpm_ref = ref;
	if(kind == TPtime_from_ll)
		bcopy((caddr_t)timev, (caddr_t)&tpm->tpm_time, sizeof(struct timeval));
	else
		bcopy( (caddr_t)&time, 
			(caddr_t)&tpm->tpm_time, sizeof(struct timeval) );
	tpm->tpm_seq = seq;
	tpm->tpm_window = win;
	tpm->tpm_size = size;
}

D 6
#endif TP_PERF_MEAS
E 6
I 6
#endif /* TP_PERF_MEAS */
E 6
E 1
