/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	in_proto.c,v $
 * Revision 2.3  89/03/09  20:44:40  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:59:37  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 01-Jun-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Added support for VMTP.
 *
 * 16-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Merged in code for IP multicast.
 *
 */ 

#include "dli.h"
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)in_proto.c	7.1 (Berkeley) 6/5/86
 */

#include "dli.h"
#include "igmproto.h"

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/domain.h>
#include <sys/mbuf.h>

#include "in.h"
#include "in_systm.h"

#include <mach_vmtp.h>


/*
 * TCP/IP protocol family: IP, ICMP, UDP, TCP, IGMP, VMTP.
 */
int	ip_output(),ip_ctloutput();
int	ip_init(),ip_slowtimo(),ip_drain();
int	icmp_input();
int	udp_input(),udp_ctlinput();
int	udp_usrreq();
int	udp_init();
#if	IGMPROTO
int	igmp_input(),igmp_output(),igmp_ctloutput();
int	igmp_usrreq(),igmp_init(),igmp_slowtimeo();
#endif	IGMPROTO
int	tcp_input(),tcp_ctlinput();
int	tcp_usrreq(),tcp_ctloutput();
int	tcp_init(),tcp_fasttimo(),tcp_slowtimo(),tcp_drain();
int	rip_input(),rip_output(),rip_ctloutput();
#if	MACH_VMTP
int	vmtp_ipinput();
int	vmtp_usrreq();
int	vmtp_init();
int	vmtp_ctloutput();
#endif	MACH_VMTP
extern	int raw_usrreq();
/*
 * IMP protocol family: raw interface.
 * Using the raw interface entry to get the timer routine
 * in is a kludge.
 */
#include "imp.h"
#if	NIMP > 0
int	rimp_output(), hostslowtimo();
#endif

#ifdef	NSIP
int	idpip_input(), nsip_ctlinput();
#endif

extern	struct domain inetdomain;

struct protosw inetsw[] = {
{ 0,		&inetdomain,	0,		0,
  0,		ip_output,	0,		0,
  0,
  ip_init,	0,		ip_slowtimo,	ip_drain,
},
{ SOCK_DGRAM,	&inetdomain,	IPPROTO_UDP,	PR_ATOMIC|PR_ADDR,
  udp_input,	0,		udp_ctlinput,	ip_ctloutput,
  udp_usrreq,
  udp_init,	0,		0,		0,
},
{ SOCK_STREAM,	&inetdomain,	IPPROTO_TCP,	PR_CONNREQUIRED|PR_WANTRCVD,
  tcp_input,	0,		tcp_ctlinput,	tcp_ctloutput,
  tcp_usrreq,
  tcp_init,	tcp_fasttimo,	tcp_slowtimo,	tcp_drain,
},
{ SOCK_RAW,	&inetdomain,	IPPROTO_RAW,	PR_ATOMIC|PR_ADDR,
  rip_input,	rip_output,	0,		rip_ctloutput,
  raw_usrreq,
  0,		0,		0,		0,
},
{ SOCK_RAW,	&inetdomain,	IPPROTO_ICMP,	PR_ATOMIC|PR_ADDR,
  icmp_input,	rip_output,	0,		rip_ctloutput,
  raw_usrreq,
  0,		0,		0,		0,
},
#if	IGMPROTO
{ SOCK_DGRAM,	&inetdomain,	IPPROTO_IGMP,	PR_ATOMIC|PR_ADDR,
  igmp_input,	igmp_output,	0,		igmp_ctloutput,
  igmp_usrreq,
  igmp_init,		0,	igmp_slowtimeo,		0,
},
#endif	IGMPROTO
#if	MACH_VMTP
/* used by clients to reach vmtp */
{ SOCK_TRANSACT,&inetdomain,	IPPROTO_VMTP,	PR_ATOMIC|PR_ADDR,
  vmtp_ipinput,	0,		0,		vmtp_ctloutput,
  vmtp_usrreq,
  vmtp_init,	0,		0,		0,
},
/* necessery for ip to send incoming packets to the vmtp module */
{ SOCK_TRANSACT,&inetdomain,	IPPROTO_VMTP2,	PR_ATOMIC|PR_ADDR,
  vmtp_ipinput,	0,		0,		0,
  0,
  0,		0,		0,		0,
},
{ SOCK_TRANSACT,&inetdomain,	IPPROTO_VMTPS,	PR_ATOMIC|PR_ADDR,
  vmtp_ipinput,	0,		0,		vmtp_ctloutput,
  vmtp_usrreq,
  0,		0,		0,		0,
},
{ SOCK_TRANSACT,&inetdomain,	IPPROTO_VMTPS2,	PR_ATOMIC|PR_ADDR,
  vmtp_ipinput,	0,		0,		0,
  0,
  0,		0,		0,		0,
},
#endif	MACH_VMTP
#ifdef	NSIP
{ SOCK_RAW,	&inetdomain,	IPPROTO_IDP,	PR_ATOMIC|PR_ADDR,
  idpip_input,	rip_output,	nsip_ctlinput,	0,
  raw_usrreq,
  0,		0,		0,		0,
},
#endif
	/* raw wildcard */
{ SOCK_RAW,	&inetdomain,	0,		PR_ATOMIC|PR_ADDR,
  rip_input,	rip_output,	0,		rip_ctloutput,
  raw_usrreq,
  0,		0,		0,		0,
},
};

struct domain inetdomain =
    { AF_INET, "internet", 0, 0, 0, 
      inetsw, &inetsw[sizeof(inetsw)/sizeof(inetsw[0])] };

#if	NIMP > 0
extern	struct domain impdomain;

struct protosw impsw[] = {
{ SOCK_RAW,	&impdomain,	0,		PR_ATOMIC|PR_ADDR,
  0,		rimp_output,	0,		0,
  raw_usrreq,
  0,		0,		hostslowtimo,	0,
},
};

struct domain impdomain =
    { AF_IMPLINK, "imp", 0, 0, 0,
      impsw, &impsw[sizeof (impsw)/sizeof(impsw[0])] };
#endif

#ifdef	vax
#include "hy.h"
#else	vax
#define NHY	0
#endif	vax

#if	NHY > 0
/*
 * HYPERchannel protocol family: raw interface.
 */
int	rhy_output();
extern	struct domain hydomain;

struct protosw hysw[] = {
{ SOCK_RAW,	&hydomain,	0,		PR_ATOMIC|PR_ADDR,
  0,		rhy_output,	0,		0,
  raw_usrreq,
  0,		0,		0,		0,
},
};

struct domain hydomain =
    { AF_HYLINK, "hy", 0, 0, 0, hysw, &hysw[sizeof (hysw)/sizeof(hysw[0])] };
#endif
#if	DLI

/*
 *  Direct data-link interface protocol family.
 */

extern	struct domain dlidomain;
extern	int dli_output(), dli_usrreq();

struct protosw dlisw[] = {
{ SOCK_DGRAM,	&dlidomain,	0,		PR_ATOMIC|PR_ADDR,
  0,		0,		0,		0,
  dli_usrreq,
  0,		0,		0,		0,
},
{ SOCK_RAW,	&dlidomain,	0,		PR_ATOMIC|PR_ADDR,
  0,		dli_output,	0,		0,
  dli_usrreq,
  0,		0,		0,		0,
},
};

struct domain dlidomain =
    { AF_DLI, "data-link-interface", 0, 0, 0,
      dlisw, &dlisw[sizeof (dlisw)/sizeof(dlisw[0])] };
#endif	DLI
