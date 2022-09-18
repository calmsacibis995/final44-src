h17785
s 00002/00002/00152
d D 8.1 93/06/10 23:18:52 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00013/00141
d D 7.6 92/10/11 12:21:40 bostic 6 5
c make kernel includes standard
e
s 00009/00005/00145
d D 7.5 91/05/06 18:58:56 bostic 5 4
c new copyright; att/bsd/shared
e
s 00003/00005/00147
d D 7.4 89/09/22 00:15:41 sklower 4 3
c make changes for SNMP
e
s 00001/00000/00151
d D 7.3 89/08/29 13:44:06 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00012/00012/00139
d D 7.2 89/04/22 11:53:39 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00151/00000/00000
d D 7.1 88/12/14 15:29:30 sklower 1 0
c date and time created 88/12/14 15:29:30 by sklower
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
/* $Header: clnp_timer.c,v 4.2 88/06/29 14:59:05 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_timer.c,v $ */
I 3
D 5
/*	%W% (Berkeley) %G% */
E 3

#ifndef lint
static char *rcsid = "$Header: clnp_timer.c,v 4.2 88/06/29 14:59:05 hagens Exp $";
#endif lint
E 5

D 4
#ifdef ISO

D 2
#include "../h/types.h"
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
E 2
I 2
#include "types.h"
E 4
D 6
#include "param.h"
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
E 6
I 6
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 6
E 2

D 6
#include "../net/if.h"
#include "../net/route.h"
E 6
I 6
#include <net/if.h>
#include <net/route.h>
E 6

D 2
#include "../netiso/iso.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
E 2
I 2
D 6
#include "iso.h"
#include "clnp.h"
#include "clnp_stat.h"
#include "argo_debug.h"
E 6
I 6
#include <netiso/iso.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 6
E 2

extern struct clnp_fragl *clnp_frags;

/*
 * FUNCTION:		clnp_freefrags
 *
 * PURPOSE:			Free the resources associated with a fragment
 *
 * RETURNS:			pointer to next fragment in list of fragments
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 *			TODO: send ER back to source
 */
struct clnp_fragl *
clnp_freefrags(cfh)
register struct clnp_fragl	*cfh;	/* fragment header to delete */
{
	struct clnp_fragl	*next = cfh->cfl_next;
	struct clnp_frag	*cf;

	/* free any frags hanging around */
	cf = cfh->cfl_frags;
	while (cf != NULL) {
		struct clnp_frag	*cf_next = cf->cfr_next;
I 4
		INCSTAT(cns_fragdropped);
E 4
		m_freem(cf->cfr_data);
		cf = cf_next;
	}

	/* free the copy of the header */
I 4
	INCSTAT(cns_fragdropped);
E 4
	m_freem(cfh->cfl_orighdr);

	if (clnp_frags == cfh) {
		clnp_frags = cfh->cfl_next;
	} else {
		struct clnp_fragl	*scan;

		for (scan = clnp_frags; scan != NULL; scan = scan->cfl_next) {
			if (scan->cfl_next == cfh) {
				scan->cfl_next = cfh->cfl_next;
				break;
			}
		}
	}

	/* free the fragment header */
	m_freem(dtom(cfh));

	return(next);
}

/*
 * FUNCTION:		clnp_slowtimo
 *
 * PURPOSE:			clnp timer processing; if the ttl expires on a 
 *					packet on the reassembly queue, discard it.
 *
 * RETURNS:			none
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
clnp_slowtimo()
{
	register struct clnp_fragl	*cfh = clnp_frags;
	int s = splnet();

	while (cfh != NULL) {
		if (--cfh->cfl_ttl == 0) {
			cfh = clnp_freefrags(cfh);
I 4
			INCSTAT(cns_fragtimeout);
E 4
		} else {
			cfh = cfh->cfl_next;
		}
	}
	splx(s);
}

/*
 * FUNCTION:		clnp_drain
 *
 * PURPOSE:			drain off all datagram fragments
 *
 * RETURNS:			none
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 *	TODO: should send back ER
 */
clnp_drain()
{
	register struct clnp_fragl	*cfh = clnp_frags;

	while (cfh != NULL)
		cfh = clnp_freefrags(cfh);
}
D 4

#endif ISO
E 4
E 1
