h04775
s 00000/00000/00038
d D 7.2 89/04/22 11:53:50 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00038/00000/00000
d D 7.1 88/12/14 15:29:34 sklower 1 0
c date and time created 88/12/14 15:29:34 by sklower
e
u
U
t
T
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
/* $Header: if_clnp.h,v 4.2 88/06/29 14:59:15 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/if_clnp.h,v $ */

/*
 * Values for the protocol identifier field in the LAN header
 */
#define	ETHERTYPE_CLNP		0x0802		/* clnp protocol from the
									     * assigned numbers RFC
										 */
/*
 *	For LAN case, see ../caif/if_lanvar.h
 */
E 1
