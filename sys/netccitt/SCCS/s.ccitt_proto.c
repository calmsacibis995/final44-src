h30010
s 00002/00002/00065
d D 8.1 93/06/10 22:52:46 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00061
d D 7.9 93/06/05 15:57:05 sklower 9 8
c various lintish things come to light by protoypes.
e
s 00016/00003/00049
d D 7.8 92/12/08 15:25:03 sklower 8 7
c changes to support x.25/llc2
e
s 00009/00007/00043
d D 7.7 92/12/08 13:43:30 bostic 7 6
c new conventions for header includes (by sklower)
e
s 00003/00022/00047
d D 7.6 92/07/09 00:12:41 sklower 6 5
c changes to add routing tables via the domain switch
e
s 00008/00007/00061
d D 7.5 90/08/30 18:48:18 sklower 5 4
c this version compiles; completely untested
e
s 00002/00002/00066
d D 7.4 90/06/21 12:28:27 sklower 4 3
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00006/00016/00062
d D 7.3 90/05/22 15:44:22 sklower 3 2
c cosmetic quickie
e
s 00013/00001/00065
d D 7.2 90/05/11 15:21:45 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00066/00000/00000
d D 7.1 90/05/11 11:19:33 sklower 1 0
c date and time created 90/05/11 11:19:33 by sklower
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
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
I 5
D 6
#define HDLC
E 6
D 7
#include "param.h"
#include "socket.h"
#include "protosw.h"
#include "domain.h"
E 7
E 5
E 2

D 5
#include "../h/param.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/domain.h"
#include "../netccitt/x25.h"
E 5
I 5
D 7
#include "x25.h"
E 7
I 7
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/domain.h>
E 7
E 5

I 6
D 7
#include "net/radix.h"
E 7
I 7
#include <netccitt/x25.h>

#include <net/radix.h>

E 7
E 6
/*
D 7
 *	Definitions of protocols supported in the CCITT domain.
E 7
I 7
 * Definitions of protocols supported in the CCITT domain.
E 7
 */

D 6
#ifdef BSD4_3
E 6
extern	struct domain ccittdomain;
I 3
#define DOMAIN &ccittdomain
D 6
#else
#define DOMAIN PF_CCITT
E 3
#endif
E 6

D 6
#ifdef XE
int	xe_output (), xe_ctlinput (), xe_init(), xe_timer();
#endif
#ifdef HDLC
E 6
D 8
int	hd_output (), hd_ctlinput (), hd_init (), hd_timer ();
D 6
#endif
E 6
D 4
int	pk_usrreq (), pk_timer ();
E 4
I 4
D 5
int	pk_usrreq (), pk_timer (), pk_init ();
E 5
I 5
int	pk_usrreq (), pk_timer (), pk_init (), pk_ctloutput ();
E 8
I 8
#ifdef LLC
D 9
int	llc_output(), llc_ctlinput(), llc_init(), llc_timer();
E 9
I 9
int	llc_output();
void	llc_ctlinput(), llc_init(), llc_timer();
E 9
#endif
#ifdef HDLC
D 9
int	hd_output(), hd_ctlinput(), hd_init(), hd_timer();
E 9
I 9
int	hd_output();
void	hd_ctlinput(), hd_init(), hd_timer();
E 9
#endif
D 9
int	pk_usrreq(), pk_timer(), pk_init(), pk_ctloutput();
int	pk_input(), pk_ctlinput();
E 9
I 9
int	pk_usrreq(), pk_ctloutput();
void	pk_timer(), pk_init(), pk_input(), pk_ctlinput();
E 9
E 8
E 5
E 4

struct protosw ccittsw[] = {
I 8
#ifdef LLC
 {	0,		DOMAIN,		IEEEPROTO_802LLC,0,
	0,		llc_output,	llc_ctlinput,	0,
	0,
	llc_init,	0,	 	llc_timer,	0,
 },
#endif
E 8
D 6
#ifdef XE
D 3
#ifdef BSD4_3
 {	0,		&ccittdomain,	IEEEPROTO_802LLC,0,
#else
 {	0,		PF_CCITT,	IEEEPROTO_802LLC,0,
#endif
E 3
I 3
 {	0,		DOMAIN,		IEEEPROTO_802LLC,0,
E 3
	0,		xe_output,	xe_ctlinput,	0,
	0,
	xe_init,	0,	 	xe_timer,	0,
 },
#endif
E 6
#ifdef HDLC
D 3
#ifdef BSD4_3
 {	0,		&ccittdomain,	CCITTPROTO_HDLC,0,
#else
 {	0,		PF_CCITT,	CCITTPROTO_HDLC,0,
#endif
E 3
I 3
 {	0,		DOMAIN,		CCITTPROTO_HDLC,0,
E 3
	0,		hd_output,	hd_ctlinput,	0,
	0,
	hd_init,	0,	 	hd_timer,	0,
 },
#endif
D 3
#ifdef BSD4_3
 {	SOCK_STREAM,	&ccittdomain,	CCITTPROTO_X25,	PR_CONNREQUIRED|PR_ATOMIC|PR_WANTRCVD,
#else
 {	SOCK_STREAM,	PF_CCITT,	CCITTPROTO_X25,	PR_CONNREQUIRED|PR_ATOMIC|PR_WANTRCVD,
#endif
E 3
I 3
 {	SOCK_STREAM,	DOMAIN,		CCITTPROTO_X25,	PR_CONNREQUIRED|PR_ATOMIC|PR_WANTRCVD,
E 3
D 5
	0,		0,		0,		0,
E 5
I 5
D 8
	0,		0,		0,		pk_ctloutput,
E 8
I 8
	pk_input,	0,		pk_ctlinput,	pk_ctloutput,
E 8
E 5
	pk_usrreq,
D 4
	0,		0,		pk_timer,	0,
E 4
I 4
	pk_init,	0,		pk_timer,	0,
E 4
 }
};

struct domain ccittdomain =
D 6
#ifdef BSD4_3
E 6
	{ AF_CCITT, "ccitt", 0, 0, 0, ccittsw,
D 6
		&ccittsw[sizeof(ccittsw)/sizeof(ccittsw[0])] };
#else
	{ AF_CCITT, "ccitt", ccittsw, &ccittsw[sizeof(ccittsw)/sizeof(ccittsw[0])] };
#endif
E 6
I 6
		&ccittsw[sizeof(ccittsw)/sizeof(ccittsw[0])], 0,
		rn_inithead, 32, sizeof (struct sockaddr_x25) };
E 6
D 3

E 3
E 1
