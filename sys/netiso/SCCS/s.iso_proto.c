h56953
s 00017/00011/00160
d D 8.2 95/02/09 10:43:19 cgd 15 14
c correct return types to match protos.
e
s 00002/00002/00169
d D 8.1 93/06/10 23:19:49 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00170
d D 7.13 93/06/04 17:02:38 sklower 13 12
c fix #endif something to #endif /* something */
e
s 00025/00007/00146
d D 7.12 92/11/25 20:11:29 sklower 12 11
c changes sufficient for IDRP and TUBA/TCP
e
s 00008/00008/00145
d D 7.11 92/10/11 12:21:53 bostic 11 10
c make kernel includes standard
e
s 00007/00003/00146
d D 7.10 92/07/09 00:01:54 sklower 10 9
c changes to add routing tables via the domain switch
e
s 00002/00002/00147
d D 7.9 91/09/06 17:15:19 sklower 9 8
c adopt TCP's policies concerning acks & (among others) use the fast
c timeout mechanism and delayed acks.
e
s 00009/00005/00140
d D 7.8 91/05/06 19:24:09 bostic 8 7
c new copyright; att/bsd/shared
e
s 00014/00004/00131
d D 7.7 91/04/26 15:16:29 sklower 7 6
c allow someone to open a tp0 socket
e
s 00009/00001/00126
d D 7.6 90/06/22 15:39:35 sklower 6 5
c merge in UW isis changes; my merge is untested, but SCCS id's
c must be assigned before I leave today :-(
e
s 00001/00001/00126
d D 7.5 90/05/03 17:39:11 sklower 5 4
c fix minor bugs for raw access
e
s 00007/00007/00120
d D 7.4 90/01/17 00:08:36 sklower 4 3
c changes for cltp
e
s 00001/00000/00126
d D 7.3 89/08/29 13:44:35 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00007/00007/00119
d D 7.2 89/04/22 11:54:24 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00126/00000/00000
d D 7.1 88/12/14 15:29:48 sklower 1 0
c date and time created 88/12/14 15:29:48 by sklower
e
u
U
t
T
I 8
/*-
D 14
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 8
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
/* $Header: iso_proto.c,v 4.4 88/09/08 08:38:42 hagens Exp $ 
 * $Source: /usr/argo/sys/netiso/RCS/iso_proto.c,v $ 
I 3
D 8
 *	%W% (Berkeley) %G% *
E 8
E 3
 *
 * iso_proto.c : protocol switch tables in the ISO domain
 *
 * ISO protocol family includes TP, CLTP, CLNP, 8208
 * TP and CLNP are implemented here.
 */
D 8

#ifndef lint
static char *rcsid = "$Header: iso_proto.c,v 4.4 88/09/08 08:38:42 hagens Exp $";
#endif
E 8

#ifdef	ISO
D 2
#include "../h/types.h"
#include "../h/param.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/domain.h"
#include "../h/mbuf.h"
E 2
I 2
D 11
#include "types.h"
#include "param.h"
#include "socket.h"
#include "protosw.h"
#include "domain.h"
#include "mbuf.h"
I 10
#include "net/radix.h"
E 11
I 11
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/domain.h>
#include <sys/mbuf.h>
E 11
E 10
E 2

D 2
#include "../netiso/iso.h"
E 2
I 2
D 11
#include "iso.h"
E 11
I 11
#include <net/radix.h>

#include <netiso/iso.h>
E 11
E 2

D 15
int clnp_output(), clnp_init(),clnp_slowtimo(),clnp_drain();
int rclnp_input(), rclnp_output(), rclnp_ctloutput(), raw_usrreq();
E 15
I 15
void	clnp_init(),clnp_slowtimo(),clnp_drain();
int	clnp_output();
void	rclnp_input();
int	rclnp_output(), rclnp_ctloutput(), raw_usrreq();
E 15
int	clnp_usrreq();
D 4
int	iso_usrreq();
E 4

D 12
int	tp_ctloutput();
int	tpclnp_ctlinput();
int	tpclnp_input();
int	tp_usrreq();
E 12
I 12
D 15
int	tp_ctloutput(), tpclnp_ctlinput(), tpclnp_input(), tp_usrreq();
E 12
D 7
int	tp_init(),tp_slowtimo(),tp_drain();
E 7
I 7
D 9
int	tp_init(), tp_slowtimo(), tp_drain();
E 9
I 9
int	tp_init(), tp_fasttimo(), tp_slowtimo(), tp_drain();
E 9
int	cons_init(), tpcons_input();
E 15
I 15
int	tp_ctloutput(), tp_usrreq();
void	tp_init(), tp_fasttimo(), tp_slowtimo(), tp_drain();
void	tpclnp_ctlinput(), tpclnp_input();
void	cons_init(), tpcons_input();
E 15
E 7

I 12
D 15
int isis_input();
E 12
int	esis_input(), esis_ctlinput(), esis_init(), esis_usrreq();
I 12
int	idrp_input(), idrp_init(), idrp_usrreq();
E 12
I 4
int	cltp_input(), cltp_ctlinput(), cltp_init(), cltp_usrreq(), cltp_output();
E 15
I 15
void	isis_input();
void	esis_init(), esis_input(), esis_ctlinput();
int	esis_usrreq();
void	idrp_init(), idrp_input();
int	idrp_usrreq();
void	cltp_init(), cltp_input(), cltp_ctlinput();
int	cltp_usrreq(), cltp_output();
E 15
I 6
D 12
int isis_input();
E 12
E 6
E 4

I 12
#ifdef TUBA
D 15
int	tuba_usrreq(), tuba_ctloutput(), tuba_init(), tuba_tcpinput(); 
int	tuba_slowtimo(), tuba_fasttimo(); 
E 15
I 15
int	tuba_usrreq(), tuba_ctloutput();
void	tuba_init(), tuba_slowtimo(), tuba_fasttimo(), tuba_tcpinput();
E 15
#endif

E 12
struct protosw isosw[] = {
/*
 *  We need a datagram entry through which net mgmt programs can get
 *	to the iso_control procedure (iso ioctls). Thus, a minimal
 *	SOCK_DGRAM interface is provided here.
 *  THIS ONE MUST BE FIRST: Kludge city : socket() says if(!proto) call
 *  pffindtype, which gets the first entry that matches the type.
 *  sigh.
 */
D 4
{ SOCK_DGRAM,	&isodomain,		0,					PR_ATOMIC|PR_ADDR,
	0,			0,				0,					0,
	iso_usrreq,
	0,			0, 				0,					0
E 4
I 4
{ SOCK_DGRAM,	&isodomain,		ISOPROTO_CLTP,		PR_ATOMIC|PR_ADDR,
	0,			cltp_output,	0,					0,
	cltp_usrreq,
	cltp_init,	0, 				0,					0
E 4
},

/*
 *	A datagram interface for clnp cannot co-exist with TP/CLNP
 *  because CLNP has no way to discriminate incoming TP packets from
 *  packets coming in for any other higher layer protocol.
 *  Old way: set it up so that pffindproto(... dgm, clnp) fails.
 *  New way: let pffindproto work (for x.25, thank you) but create
 *  	a clnp_usrreq() that returns error on PRU_ATTACH.
 */
{SOCK_DGRAM,	&isodomain,		ISOPROTO_CLNP,		0,
D 4
 clnp_usrreq,	clnp_output,	0,					0,
 0,
E 4
I 4
 0,				clnp_output,	0,					0,
 clnp_usrreq,
E 4
 clnp_init,		0,				clnp_slowtimo, 		clnp_drain,
},

/* raw clnp */
{ SOCK_RAW,		&isodomain,		ISOPROTO_RAW,		PR_ATOMIC|PR_ADDR,
  rclnp_input,	rclnp_output,	0,					rclnp_ctloutput,
D 5
  raw_usrreq,
E 5
I 5
  clnp_usrreq,
E 5
  0,			0,				0,					0
},

/* ES-IS protocol */
{ SOCK_DGRAM,	&isodomain,		ISOPROTO_ESIS,		PR_ATOMIC|PR_ADDR,
D 7
  esis_input,	0,				esis_ctlinput,				0,
E 7
I 7
  esis_input,	0,				esis_ctlinput,		0,
E 7
  esis_usrreq,
D 6
  esis_init,			0,				0,					0
E 6
I 6
  esis_init,	0,				0,					0
},

/* ISOPROTO_INTRAISIS */
{ SOCK_DGRAM,	&isodomain,		ISOPROTO_INTRAISIS,	PR_ATOMIC|PR_ADDR,
  isis_input,	0,				0,					0,
  esis_usrreq,
  0,			0,				0,					0
E 6
},

I 12
/* ISOPROTO_IDRP */
{ SOCK_DGRAM,	&isodomain,		ISOPROTO_IDRP,		PR_ATOMIC|PR_ADDR,
  idrp_input,	0,				0,					0,
  idrp_usrreq,
  idrp_init,	0,				0,					0
},

E 12
/* ISOPROTO_TP */
D 7
{ SOCK_SEQPACKET,	&isodomain,	ISOPROTO_TP,	PR_CONNREQUIRED|PR_WANTRCVD,
E 7
I 7
{ SOCK_SEQPACKET,	&isodomain,	ISOPROTO_TP,		PR_CONNREQUIRED|PR_WANTRCVD,
E 7
D 12
  tpclnp_input,		0,			tpclnp_ctlinput,	tp_ctloutput,
E 12
I 12
  tpclnp_input,	0,				tpclnp_ctlinput,	tp_ctloutput,
E 12
  tp_usrreq,
D 7
  tp_init,			0,			tp_slowtimo,	tp_drain,
E 7
I 7
D 9
  tp_init,			0,			tp_slowtimo,		tp_drain,
E 9
I 9
D 12
  tp_init,			tp_fasttimo,			tp_slowtimo,		tp_drain,
E 12
I 12
  tp_init,		tp_fasttimo,	tp_slowtimo,		tp_drain,
E 12
E 9
E 7
},
I 12

#ifdef TUBA
{ SOCK_STREAM,	&isodomain,		ISOPROTO_TCP,		PR_CONNREQUIRED|PR_WANTRCVD,
  tuba_tcpinput,	0,			0,					tuba_ctloutput,
  tuba_usrreq,
  tuba_init,	tuba_fasttimo,	tuba_fasttimo,		0
},
#endif
E 12
I 7

#ifdef TPCONS
/* ISOPROTO_TP */
{ SOCK_SEQPACKET,	&isodomain,	ISOPROTO_TP0,		PR_CONNREQUIRED|PR_WANTRCVD,
  tpcons_input,		0,			0,					tp_ctloutput,
  tp_usrreq,
  cons_init,		0,			0,					0,
},
#endif
E 7

};

D 10
int	iso_init();
E 10

struct domain isodomain = {
    AF_ISO, 			/* family */
	"iso-domain", 		/* name */
D 10
	iso_init,			/* initialize routine */
E 10
I 10
	0,					/* initialize routine */
E 10
	0,					/* externalize access rights */
	0,					/* dispose of internalized rights */
	isosw,				/* protosw */
D 10
	&isosw[sizeof(isosw)/sizeof(isosw[0])] /* NPROTOSW */
E 10
I 10
	&isosw[sizeof(isosw)/sizeof(isosw[0])], /* NPROTOSW */
	0,					/* next */
	rn_inithead,		/* rtattach */
	48,					/* rtoffset */
	sizeof(struct sockaddr_iso) /* maxkeylen */
E 10
};
D 13
#endif	ISO
E 13
I 13
#endif	/* ISO */
E 13
E 1
