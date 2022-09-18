h28390
s 00001/00001/00582
d D 8.2 95/01/09 17:51:57 cgd 25 24
c 64-bit changes
e
s 00002/00002/00581
d D 8.1 93/06/10 23:19:26 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00582
d D 7.21 93/06/05 15:58:00 sklower 23 22
c ip_output takes 5 args now; other miscelleny due to prototypes in header files
e
s 00002/00001/00582
d D 7.20 93/04/06 15:21:35 sklower 22 21
c eonrtrequest should return void
e
s 00028/00028/00555
d D 7.19 92/10/11 12:21:48 bostic 21 20
c make kernel includes standard
e
s 00001/00001/00582
d D 7.18 92/02/14 14:15:45 sklower 20 19
c fix bug
e
s 00000/00001/00583
d D 7.17 91/12/19 17:43:13 sklower 19 18
c reference count ifaddrs to make them safe for deletion
e
s 00001/00001/00583
d D 7.16 91/06/27 23:02:18 sklower 18 17
c make compile under new and old vm system
e
s 00001/00001/00583
d D 7.15 91/05/09 23:31:49 sklower 17 16
c fix stupid fix
e
s 00002/00001/00582
d D 7.14 91/05/09 20:35:02 sklower 16 15
c fix incomplete reference to previous mtu.
e
s 00009/00005/00574
d D 7.13 91/05/06 19:23:59 bostic 15 14
c new copyright; att/bsd/shared
e
s 00022/00001/00557
d D 7.12 91/04/26 15:23:12 sklower 14 13
c mostly make EON route mtu reflect size of underlying IP route mtu
c when known; requires validating cached routes more frequently.
e
s 00017/00011/00541
d D 7.11 91/01/09 15:41:27 sklower 13 12
c changes to support esis and isis over eon
e
s 00015/00015/00537
d D 7.10 90/06/20 19:02:41 sklower 12 11
c changed esis to make use of routing table; mostly works;
c checkpoint before UW merge
e
s 00020/00010/00532
d D 7.9 90/05/24 17:57:39 sklower 11 9
c try to keep up with Dave Katz and his prefix table . . . (compiles at least0
e
s 00019/00004/00538
d R 7.9 90/05/24 17:40:00 sklower 10 9
c try to keep up with Dave Katz and his prefix table . . .
e
s 00001/00001/00541
d D 7.8 90/05/14 16:06:14 sklower 9 8
c inconsistent arg order in calls to eoniphdr
e
s 00004/00002/00538
d D 7.7 90/05/04 18:48:28 sklower 8 6
c use generic machinery for llifaddrs to replace themeselves by protocol
c specific ifaddrs by not stomping on ifa_rtrequest in the ll ifaddr.
e
s 00000/00001/00539
d R 7.7 90/05/04 13:14:33 sklower 7 6
c use generic machinery for llifaddrs to replace themeselves by protocol
c specific ifaddrs by not stomping on ifa_rtrequest in the ll ifaddr.
e
s 00161/00543/00379
d D 7.6 90/04/05 11:20:20 sklower 6 5
c rewrite if_eon.c to allow arbitrary nsaps routed via IP; use new rt_change mechnism to maintain list of routes\;
e
s 00016/00004/00906
d D 7.5 89/09/22 00:15:43 sklower 5 4
c make changes for SNMP
e
s 00001/00000/00909
d D 7.4 89/08/29 13:44:15 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00002/00002/00907
d D 7.3 89/04/25 14:28:18 mckusick 3 2
c ../machine => machine
e
s 00151/00142/00758
d D 7.2 89/04/22 11:53:57 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00900/00000/00000
d D 7.1 88/12/14 15:29:37 sklower 1 0
c date and time created 88/12/14 15:29:37 by sklower
e
u
U
t
T
I 15
/*-
D 24
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 15
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
 * $Header: if_eon.c,v 1.4 88/07/19 15:53:59 hagens Exp $ 
 * $Source: /usr/argo/sys/netiso/RCS/if_eon.c,v $ 
I 4
D 15
 *	%W% (Berkeley) %G% *
E 15
E 4
 *
 *	EON rfc 
 *  Layer between IP and CLNL
 *
 * TODO:
 * Put together a current rfc986 address format and get the right offset
 * for the nsel
 */
D 2
#define RFC986_NSEL_OFFSET 5
E 2
D 15

#ifndef lint
static char *rcsid = "$Header: if_eon.c,v 1.4 88/07/19 15:53:59 hagens Exp $";
#endif lint
E 15

D 2
#include "eon.h"
#if NEON>0
E 2
I 2
#ifdef EON
#define NEON 1
E 2

I 2

E 2
D 21
#include "param.h"
#include "systm.h"
#include "types.h"
#include "mbuf.h"
#include "buf.h"
#include "protosw.h"
#include "socket.h"
#include "ioctl.h"
#include "errno.h"
#include "types.h"
E 21
I 21
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/types.h>
E 21

D 2
#include "../machine/io.h"
#include "../machineio/ioccvar.h"

E 2
D 21
#include "../net/if.h"
I 2
D 5
#include "../net/iftypes.h"
E 5
I 5
#include "../net/if_types.h"
I 6
#include "../net/if_dl.h"
E 6
E 5
E 2
#include "../net/netisr.h"
#include "../net/route.h"
I 2
D 3
#include "../machine/mtpr.h"
E 3
I 3
#include "machine/mtpr.h"
E 21
I 21
#include <net/if.h>
#include <net/if_types.h>
#include <net/if_dl.h>
#include <net/netisr.h>
#include <net/route.h>
#include <machine/mtpr.h>
E 21
E 3
E 2

D 21
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
I 6
#include "../netinet/in_var.h"
E 6
#include "../netinet/ip.h"
#include "../netinet/ip_var.h"
#include "../netinet/if_ether.h"
E 21
I 21
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/if_ether.h>
E 21

D 2
#include "../netiso/iso.h"
#include "../netiso/argo_debug.h"
#include "../netiso/iso_errno.h"
#include "../netiso/eonvar.h"
E 2
I 2
D 21
#include "iso.h"
#include "iso_var.h"
#include "iso_snpac.h"
D 12
extern struct snpa_cache all_es, all_is;
E 12
#include "argo_debug.h"
#include "iso_errno.h"
#include "eonvar.h"
E 21
I 21
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_snpac.h>
#include <netiso/argo_debug.h>
#include <netiso/iso_errno.h>
#include <netiso/eonvar.h>

E 21
I 5
extern struct timeval time;
I 18
extern struct ifnet loif;
E 18
E 5
E 2

#define EOK 0

int						eoninput();
D 6
int						eonint();
E 6
int						eonoutput();
int						eonioctl();
D 6
int						eonprobe();
E 6
int						eonattach();
int						eoninit();
I 6
D 22
int						eonrtrequest();
E 22
I 22
void						eonrtrequest();
E 22
E 6
D 23
extern 	int				ip_output();
E 23
D 6
struct ifnet			eonif[NEON];
E 6
I 6
struct ifnet			eonif[1];
E 6

I 2
D 6
#ifdef FAKEIOCCDEV
D 3
#include "../machine/io.h"
E 3
I 3
#include "machine/io.h"
E 3
#include "../machineio/ioccvar.h"

E 2
#define EON_FAKE_CSR 0
int eon_fakeautoconf[2]; /* need at least 2 ints */

caddr_t eonstd[] = { (caddr_t) eon_fakeautoconf, 0 };
struct	iocc_device *eoninfo[NEON];

struct	iocc_driver eondriver = {
	eonprobe, 	/* idr_probe */ 
	0,			/* idr_slave */ 
	eonattach,	/* idr_attach */
	0,			/* idr_dgo */
	eonstd,		/* idr_addr - list of standard addresses for device */
	"eon",		/* idr_dname */
	eoninfo,	/* idr_dinfo - backptrs to iodinit structs */
	0,			/* idr_mname - controller name */
	0,			/* idr_minfo -- backptrs to iominit structs */
	eonint,		/* idr_intr - interrupt rtn */
	0,  		/* idr_csr - offset to read/write csr */
	EON_FAKE_CSR,	 /* idr_chanrelse */
	0, 			/* idr_flags */
};
I 2
#else
struct iocc_device {
	int iod_unit;
} bsd_iocc_fakeout;
E 2

E 6
I 2
eonprotoinit() {
D 6
	(void) eonprobe();
	(void) eonattach(&bsd_iocc_fakeout);
E 6
I 6
	(void) eonattach();
E 6
}
I 6

struct eon_llinfo eon_llinfo;
E 6
#define PROBE_OK 0;
D 6
#endif
E 6
E 2

I 2

E 2
D 6
/* 
 * entry in the EON address cache (list)
 * (or pt-pt links list, however you view it)
 */

struct eon_centry {
	struct qhdr eonc_q_LINK;
#define eonc_nextLINK eonc_q_LINK.link
#define eonc_prevLINK eonc_q_LINK.flink

	struct qhdr eonc_q_IS;
#define eonc_nextIS eonc_q_IS.link
#define eonc_prevIS eonc_q_IS.flink

	struct qhdr eonc_q_ES;
#define eonc_nextES eonc_q_ES.link
#define eonc_prevES eonc_q_ES.flink

	struct in_addr	eonc_addr;
	u_short		eonc_status;
};

/* kinda like mtod() but for eon_centries */
#define qtocentry(q, off)  ((struct eon_centry *)  (((caddr_t)(q)) - off))
#define centrytoq(c, off)  ((struct qhdr *)  (((caddr_t)(c)) + off))

struct qhdr 			eon_LINK_hdr = {
	(struct qhdr *)0,
	(struct qhdr *)0,
};
static struct qhdr 		eon_IS_hdr = {
	(struct qhdr *)0,
	(struct qhdr *)0,
};
static struct qhdr 		eon_ES_hdr = {
	(struct qhdr *)0,
	(struct qhdr *)0,
};
static struct qhdr 		eon_FREE_hdr = {
	(struct qhdr *)0,
	(struct qhdr *)0,
};

#define INITQ(q)  (q)->rlink = (q)->link = (q)

E 6
/*
D 6
 * FUNCTION:		eon_dumpcache
 *
 * PURPOSE:			dump the cache beginning with the argument given
 *
 * RETURNS:			0
 */

eon_dumpcache(which)
	int 						which;
{
	register int 				off;
	register struct eon_centry 	*ent;
	struct	qhdr				*hdr;

	switch (which) {
		case E_FREE:
			printf("FREE LIST\n");
			off = _offsetof( struct eon_centry, eonc_q_LINK);
			hdr = &eon_FREE_hdr;
			ent = qtocentry( hdr->link, 
				_offsetof( struct eon_centry, eonc_q_LINK));
			break;
		case E_ES:
			printf("ES LIST\n");
			off = _offsetof( struct eon_centry, eonc_q_ES);
			hdr = &eon_ES_hdr;
			ent = qtocentry( hdr->link, 
				_offsetof( struct eon_centry, eonc_q_ES));
			break;
		case E_IS:
			printf("IS LIST\n");
			off = _offsetof( struct eon_centry, eonc_q_IS);
			hdr = &eon_IS_hdr;
			ent = qtocentry( hdr->link, 
				_offsetof( struct eon_centry, eonc_q_IS));
			break;
		case E_LINK:
			printf("LINK LIST\n");
			off = _offsetof( struct eon_centry, eonc_q_LINK);
			hdr = &eon_LINK_hdr;
			ent = qtocentry( hdr->link, 
				_offsetof( struct eon_centry, eonc_q_LINK));
			break;
	}
	if(hdr == centrytoq(ent, off)->link )
		printf("EMPTY\n");
	else while(1) {
		printf("0x%x: %d.%d.%d.%d, %s %s\n", ent,
			(ent->eonc_addr.s_addr>>24)&0xff,
			(ent->eonc_addr.s_addr>>16)&0xff,
			(ent->eonc_addr.s_addr>>8)&0xff,
			(ent->eonc_addr.s_addr)&0xff,
			((ent->eonc_status & EON_ESLINK_UP)?"ES^":
				(ent->eonc_status & EON_ESLINK_DOWN)?"es*": "   "),
			((ent->eonc_status & EON_ISLINK_UP)?"IS^":
				(ent->eonc_status & EON_ISLINK_DOWN)?"is*": "   ")
			);
		dump_buf(ent, sizeof(struct eon_centry) );

		{ 	/* ent = ent.next: */
			register struct qhdr 	*q;

			q = centrytoq(ent, off)->link;
			if( q == hdr)
				break;
			if( q == (struct qhdr *)0) /* panic */ {
				printf("eon0: BAD Q HDR or CENTRY! q 0x%x ent 0x%x off 0x%x\n",
					q, ent, off);
				break;
			}
			ent = qtocentry( q,  off );
		}
	}
}
/*
 * FUNCTION:		eon_initcache
 *
 * PURPOSE:			allocs a bunch of free cache entries
 *
 * RETURNS:			0
 */

eon_initcache()
{
	static struct eon_centry	eoncache[EON_CACHESIZE];
	register int 				i;
	register struct eon_centry 	*ent;

	bzero( eoncache, EON_CACHESIZE*sizeof(struct eon_centry));
	INITQ( &eon_FREE_hdr );
	INITQ( &eon_LINK_hdr );
	INITQ( &eon_IS_hdr );
	INITQ( &eon_ES_hdr );

	ent = eoncache;

	for(i=0; i< EON_CACHESIZE; i++,ent++) {
		_insque( centrytoq(ent, _offsetof( struct eon_centry, eonc_q_LINK)),
			&eon_FREE_hdr);
	}
	printf("eon0: cache initialized\n");
}

/*
 * FUNCTION:		eonprobe
 *
 * PURPOSE:			filler for device configuration
 *
 * RETURNS:			PROBE_OK
 */

I 2
int int_level, int_irq;
E 2
eonprobe()
{
	extern int	int_level, int_irq;

	printf("eonprobe() \n");
	int_level = int_irq = 0x3; /* pick something - anything but -1 */
	return PROBE_OK;
}

/*
E 6
 * FUNCTION:		eonattach
 *
 * PURPOSE:			autoconf attach routine
 *
 * RETURNS:			void
 */

D 6
eonattach(iod)
	register struct iocc_device *iod;
E 6
I 6
eonattach()
E 6
{
D 6
	register struct ifnet *ifp = &eonif[iod->iod_unit];
E 6
I 6
	register struct ifnet *ifp = eonif;
E 6

	IFDEBUG(D_EON)
		printf("eonattach()\n");
	ENDDEBUG
D 6
	ifp->if_unit = iod->iod_unit;
E 6
I 6
	ifp->if_unit = 0;
E 6
	ifp->if_name = "eon";
	ifp->if_mtu = ETHERMTU; 
		/* since everything will go out over ether or token ring */

	ifp->if_init = eoninit;
D 2
	ifp->if_ioctl = eonioctl; /* needed? */
E 2
I 2
	ifp->if_ioctl = eonioctl;
E 2
	ifp->if_output = eonoutput;
D 2
	ifp->if_reset = 0;
E 2
I 2
	ifp->if_type = IFT_EON;
	ifp->if_addrlen = 5;
	ifp->if_hdrlen = EONIPLEN;
E 2
	ifp->if_flags = IFF_BROADCAST;
	if_attach(ifp);
I 6
	eonioctl(ifp, SIOCSIFADDR, (caddr_t)ifp->if_addrlist);
	eon_llinfo.el_qhdr.link = 
		eon_llinfo.el_qhdr.rlink = &(eon_llinfo.el_qhdr);
E 6

	IFDEBUG(D_EON)
		printf("eonattach()\n");
	ENDDEBUG
D 6
	eon_initcache();
	IFDEBUG(D_EON)
		printf("eon%d: attached\n", iod->iod_unit);
	ENDDEBUG
E 6
}

D 6
static struct eon_centry *
find_oldent( ea ) 
	struct sockaddr_eon *ea;
{
	register	int				offset = 
						_offsetof( struct eon_centry, eonc_q_LINK);
D 2
	register struct eon_centry 	*ent = qtocentry(eon_LINK_hdr.link, offset); 
E 2
I 2
	register struct eon_centry 	*ent, *oent; 
E 6
E 2

I 2
D 6
	oent = ent = qtocentry(eon_LINK_hdr.link, offset); 
E 2
	IFDEBUG(D_EON)
		printf("eon: find_oldent() ipaddr: %d.%d.%d.%d\n",
			(ea->seon_ipaddr>>24)&0xff,
			(ea->seon_ipaddr>>16)&0xff,
			(ea->seon_ipaddr>>8)&0xff,
			(ea->seon_ipaddr)&0xff );
	ENDDEBUG
D 2
	for (; ent; ent = qtocentry(ent->eonc_nextLINK, offset) ) {
E 2
I 2
	do {
E 2
		if( ent->eonc_addr.s_addr == ea->seon_ipaddr ) 
			return ent;
D 2
	}
E 2
I 2
		ent = qtocentry(ent->eonc_nextLINK, offset);
	} while (ent != oent);
E 2
	return (struct eon_centry *)0;
}

E 6
/*
 * FUNCTION:		eonioctl
 *
 * PURPOSE:			io controls - ifconfig
 *				need commands to 
 *					link-UP (core addr) (flags: ES, IS)
 *					link-DOWN (core addr) (flags: ES, IS)
 *				must be callable from kernel or user
 *
 * RETURNS:			nothing
 */
eonioctl(ifp, cmd, data)
	register struct ifnet *ifp;
D 6
	register int cmd;
E 6
I 6
D 25
	int cmd;
E 25
I 25
	u_long cmd;
E 25
E 6
	register caddr_t data;
{
D 2
	struct ifreq *ifr = (struct ifreq *)data;
E 2
I 2
D 6
	struct iso_ifreq *ifr = (struct iso_ifreq *)data;
E 2
	register struct sockaddr_eon *eoa = 
D 2
				(struct sockaddr_eon *)&(ifr->ifr_addr);
E 2
I 2
				(struct sockaddr_eon *)&(ifr->ifr_Addr);
E 2
	register int s = splimp();
E 6
I 6
	int s = splimp();
E 6
	register int error = 0;

	IFDEBUG(D_EON)
		printf("eonioctl (cmd 0x%x) \n", cmd);
	ENDDEBUG

D 6
	switch (cmd){
D 2
	case SIOCSIFDSTADDR: {
E 2
I 2
	case SIOCSEONCORE: {
E 2
			/* add pt-pt link to the set of core addrs */
			register 	struct eon_centry *ent, *oldent;
			register	u_short			  which;
E 6
I 6
	switch (cmd) {
		register struct ifaddr *ifa;
I 8
D 12
		extern link_rtrequest();
E 12
E 8
E 6

D 6
			/* "which" tells which lists to put these guys in - don't 
			 * want to insert something in a list if it's already there
			 */
#define LEGIT_EONADDR(a)\
D 2
	((a->seon_family == AF_ISO) && (a->seon_afi == 0x47) &&\
E 2
I 2
	((a->seon_family == AF_ISO) && (a->seon_afi == AFI_RFC986) &&\
E 2
	(a->seon_idi[0] == 0) && (a->seon_idi[1] == 6) \
D 2
	)
#ifdef notdef
	/* GET THESE RIGHT AND ADD THEM */
	&& (a->seon_vers == 3) && (a->seon_adrlen == 0xa)
#endif notdef
E 2
I 2
	&& (a->seon_vers == EON_986_VERSION) && (a->seon_adrlen == 0x14))
E 2

			if( ! LEGIT_EONADDR(eoa) ) {
				error = EADDRNOTAVAIL;
				break;
			}

			oldent = find_oldent( eoa );
			IFDEBUG(D_EON)
				printf("eonioctl legit seon_status 0x%x oldent %s\n",
					eoa->seon_status, oldent?"found":"not found");
			ENDDEBUG

			if( eoa->seon_status & UPBITS ) {
				if (!oldent) {
					/* doesn't exist - need to create one */
D 2
					/* TODO : check for null free list */
E 2
I 2
					if (eon_FREE_hdr.link == eon_FREE_hdr.rlink)
						return ENOBUFS;
E 2
					ent = qtocentry(eon_FREE_hdr.link, 
								_offsetof( struct eon_centry, eonc_q_LINK));
					remque( &(ent->eonc_q_LINK) );
					ent->eonc_addr.s_addr = eoa->seon_ipaddr;
D 2
					insque( &oldent->eonc_q_LINK, (&eon_LINK_hdr));
E 2
I 2
					insque( &(ent->eonc_q_LINK), (&eon_LINK_hdr));
E 2
					oldent = ent;
				}
				
				which = (eoa->seon_status ^ oldent->eonc_status) &
					eoa->seon_status & UPBITS;

				oldent->eonc_status |= (eoa->seon_status & UPBITS);

				if( which & EON_ESLINK_UP )
					insque( &oldent->eonc_q_ES, (&eon_ES_hdr));
				if( which & EON_ISLINK_UP )
					insque( &oldent->eonc_q_IS, (&eon_IS_hdr));
			}

			if( eoa->seon_status & DOWNBITS ) {
				if(!oldent) {
					return ENOENT; /* no such entry */
				}
				which = (eoa->seon_status ^ oldent->eonc_status) &
					eoa->seon_status & DOWNBITS;

				oldent->eonc_status |= (eoa->seon_status & DOWNBITS);

				if( which & EON_ESLINK_DOWN )
					remque( &(oldent->eonc_q_ES) );
				if( which & EON_ISLINK_DOWN )
					remque( &(oldent->eonc_q_IS) );
			}

		IFDEBUG(D_EON)
			printf("at end status 0x%x\n", oldent->eonc_status);
		ENDDEBUG
		break;
		}

D 2
	case SIOCGIFDSTADDR: 
E 2
I 2
	case SIOCGEONCORE: 
E 2
		{
			register 	struct eon_centry *oldent;

			oldent = find_oldent( eoa );
			if( oldent == (struct eon_centry *)0 )
				error = EADDRNOTAVAIL;
			else
				eoa->seon_status = oldent->eonc_status;
		}
		break;

E 6
	case SIOCSIFADDR:
D 6
		ifp->if_flags |= IFF_UP;
E 6
I 6
		if (ifa = (struct ifaddr *)data) {
			ifp->if_flags |= IFF_UP;
D 8
			ifa->ifa_rtrequest = eonrtrequest;
E 8
I 8
			if (ifa->ifa_addr->sa_family != AF_LINK)
				ifa->ifa_rtrequest = eonrtrequest;
E 8
D 19
			ifa->ifa_llinfolen = sizeof(struct eon_llinfo);
E 19
D 8
	    }
E 8
I 8
		}
E 8
E 6
		break;
D 6

	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 && ifp->if_flags &
		  IFF_RUNNING){
			ifp->if_flags &= ~IFF_RUNNING;
		} else if (ifp->if_flags & IFF_UP && (ifp->if_flags &
		  IFF_RUNNING) == 0)
			eoninit(ifp->if_unit);
		break;
	default:
		error = EINVAL;
E 6
	}
	splx(s);
	return(error);
}

I 6

eoniphdr(hdr, loc, ro, class, zero)
struct route *ro;
register struct eon_iphdr *hdr;
caddr_t loc;
{
	struct mbuf mhead;
I 14
D 18
	extern struct ifnet loif;
E 18
E 14
	register struct sockaddr_in *sin = (struct sockaddr_in *)&ro->ro_dst;
	if (zero) {
		bzero((caddr_t)hdr, sizeof (*hdr));
		bzero((caddr_t)ro, sizeof (*ro));
	}
	sin->sin_family = AF_INET;
	sin->sin_len = sizeof (*sin);
	bcopy(loc, (caddr_t)&sin->sin_addr, sizeof(struct in_addr));
I 14
	/*
	 * If there is a cached route,
	 * check that it is to the same destination
	 * and is still up.  If not, free it and try again.
	 */
	if (ro->ro_rt) {
		struct sockaddr_in *dst =
			(struct sockaddr_in *)rt_key(ro->ro_rt);
		if ((ro->ro_rt->rt_flags & RTF_UP) == 0 ||
		   sin->sin_addr.s_addr != dst->sin_addr.s_addr) {
			RTFREE(ro->ro_rt);
			ro->ro_rt = (struct rtentry *)0;
		}
	}
	rtalloc(ro);
	if (ro->ro_rt)
		ro->ro_rt->rt_use++;
E 14
	hdr->ei_ip.ip_dst = sin->sin_addr;
	hdr->ei_ip.ip_p = IPPROTO_EON;
	hdr->ei_ip.ip_ttl = MAXTTL;	
	hdr->ei_eh.eonh_class = class;
	hdr->ei_eh.eonh_vers = EON_VERSION;
	hdr->ei_eh.eonh_csum = 0;
	mhead.m_data = (caddr_t) &hdr->ei_eh;
	mhead.m_len = sizeof(struct eon_hdr);
	mhead.m_next = 0;
	IFDEBUG(D_EON)
		printf("eonoutput : gen csum (0x%x, offset %d, datalen %d)\n", 
			&mhead,
			_offsetof(struct eon_hdr, eonh_csum), sizeof(struct eon_hdr)); 
	ENDDEBUG
	iso_gen_csum(&mhead, 
		_offsetof(struct eon_hdr, eonh_csum), sizeof(struct eon_hdr)); 
}
E 6
/*
D 6
 * FUNCTION:		eoninit
E 6
I 6
 * FUNCTION:		eonrtrequest
E 6
 *
D 6
 * PURPOSE:			initialization
E 6
I 6
 * PURPOSE:			maintains list of direct eon recipients.
 *					sets up IP route for rest.
E 6
 *
 * RETURNS:			nothing
 */
I 22
void
E 22
D 6

eoninit(unit)
	int unit;
E 6
I 6
eonrtrequest(cmd, rt, gate)
register struct rtentry *rt;
D 11
struct sockaddr *gate;
E 11
I 11
register struct sockaddr *gate;
E 11
E 6
{
D 2
	printf("eoninit ecn%d\n", unit);
E 2
I 2
D 6
	printf("eon driver-init eon%d\n", unit);
E 2
}
E 6
I 6
D 11
	caddr_t	ipaddrloc = 0;
E 11
I 11
	unsigned long zerodst = 0;
	caddr_t	ipaddrloc = (caddr_t) &zerodst;
E 11
	register struct eon_llinfo *el = (struct eon_llinfo *)rt->rt_llinfo;
D 11
	register struct rtentry *iprt;
	register struct sockaddr_in sin;
E 11
E 6

I 6
D 12
	if (el == 0)
		panic("eonrtrequest");
E 12
D 11
	iprt = el->el_iproute.ro_rt;
E 11
	/*
	 * Common Housekeeping
	 */
	switch (cmd) {
I 12
	case RTM_DELETE:
		if (el) {
			remque(&(el->el_qhdr));
			if (el->el_iproute.ro_rt)
				RTFREE(el->el_iproute.ro_rt);
			Free(el);
			rt->rt_llinfo = 0;
		}
		return;
E 12
E 6

I 12
D 14
	case RTM_RESOLVE:
E 14
E 12
I 6
	case RTM_ADD:
I 14
	case RTM_RESOLVE:
		rt->rt_rmx.rmx_mtu = loif.if_mtu; /* unless better below */
E 14
I 12
		R_Malloc(el, struct eon_llinfo *, sizeof(*el));
		rt->rt_llinfo = (caddr_t)el;
		if (el == 0)
			return;
		Bzero(el, sizeof(*el));
E 12
		insque(&(el->el_qhdr), &eon_llinfo.el_qhdr);
		el->el_rt = rt;
		break;
D 12

	case RTM_DELETE:
		remque(&(el->el_qhdr));
		/* FALLTHROUGH */
	case RTM_CHANGE:
		el->el_flags &= ~RTF_UP;
D 11
		if (iprt)
			RTFREE(iprt);
E 11
I 11
		el->el_snpaoffset = 0;
		if (el->el_iproute.ro_rt)
			RTFREE(el->el_iproute.ro_rt);
E 11
		if (cmd = RTM_DELETE)
			return;
E 12
	}
	if (gate || (gate = rt->rt_gateway)) switch (gate->sa_family) {
		case AF_LINK:
D 11
			ipaddrloc = LLADDR((struct sockaddr_dl *)gate);
E 11
I 11
#define SDL(x) ((struct sockaddr_dl *)x)
D 20
			if (SDL(gate)->sdl_alen = 1)
E 20
I 20
			if (SDL(gate)->sdl_alen == 1)
E 20
				el->el_snpaoffset = *(u_char *)LLADDR(SDL(gate));
			else
				ipaddrloc = LLADDR(SDL(gate));
E 11
			break;
		case AF_INET:
D 11
			ipaddrloc = (caddr_t) &((struct sockaddr_in *)gate)->sin_addr;
E 11
I 11
#define SIN(x) ((struct sockaddr_in *)x)
			ipaddrloc = (caddr_t) &SIN(gate)->sin_addr;
E 11
			break;
		default:
			return;
	}
	el->el_flags |= RTF_UP;
D 9
	eoniphdr(&el->el_ei, &el->el_iproute, ipaddrloc, EON_NORMAL_ADDR, 0);
E 9
I 9
	eoniphdr(&el->el_ei, ipaddrloc, &el->el_iproute, EON_NORMAL_ADDR, 0);
I 14
	if (el->el_iproute.ro_rt)
D 16
		rt->rt_rmx.rmx_mtu = el->el_iproute.ro_rt - sizeof(el->el_ei);
E 16
I 16
D 17
		rt->rt_rmx.rmx_mtu = el->el_iproute.ro_rt->rt_rmx_mtu
E 17
I 17
		rt->rt_rmx.rmx_mtu = el->el_iproute.ro_rt->rt_rmx.rmx_mtu
E 17
							- sizeof(el->el_ei);
E 16
E 14
E 9
}

E 6
/*
D 6
 * FUNCTION:		eonint
E 6
I 6
 * FUNCTION:		eoninit
E 6
 *
D 6
 * PURPOSE:			filler for device configuration
E 6
I 6
 * PURPOSE:			initialization
E 6
 *
 * RETURNS:			nothing
D 6
 *
 * NOTES:			*should* never get called - for debugging it's here
E 6
 */

D 6
eonint()
E 6
I 6
eoninit(unit)
	int unit;
E 6
{
D 6
	/* silent - so no more stray interrupt messages from the aed! yay
	printf("eonint() called - BOGUS INTERRUPT\n");
	*/
E 6
I 6
	printf("eon driver-init eon%d\n", unit);
E 6
}


/*
 * FUNCTION:		eonoutput
 *
 * PURPOSE:			prepend an eon header and hand to IP
 * ARGUMENTS:	 	(ifp) is points to the ifnet structure for this unit/device
 *					(m)  is an mbuf *, *m is a CLNL packet
 *					(dst) is a destination address - have to interp. as
 *					multicast or broadcast or real address.
 *
 * RETURNS:			unix error code
 *
 * NOTES:			
 *
 */
D 6
eonoutput(ifp, morig, dst)
E 6
I 6
eonoutput(ifp, m, dst, rt)
E 6
D 2
	register struct ifnet 	*ifp;
E 2
I 2
	struct ifnet 	*ifp;
E 2
D 6
	register struct mbuf	*morig;		/* packet */
E 6
I 6
	register struct mbuf	*m;		/* packet */
E 6
	struct sockaddr_iso		*dst;		/* destination addr */
I 6
	struct rtentry *rt;
E 6
{
D 6
	int						s;
	struct eon_hdr			*eonhdr;
	struct ip				*iphdr;
	struct mbuf				*mh;
	int						error = 0;
	register int			datalen;
	caddr_t					dstipaddrloc;
D 2
	int						single=0;
	int						qoffset=0;
E 2
I 2
	int						single = 0, class, qoffset = 0, snpalen;
E 2
	register struct eon_centry	*ent;
I 2
	register struct sockaddr_eon *eoa;
E 2
	struct qhdr				*q;
I 2
	char edst[6];
E 6
I 6
	register struct eon_llinfo *el;
	register struct eon_iphdr *ei;
	struct route *ro;
	int	datalen;
	struct mbuf *mh;
D 13
	int	error = 0;
	caddr_t ippaddrloc;
E 13
I 13
	int	error = 0, class = 0, alen = 0;
	caddr_t ipaddrloc;
E 13
	static struct eon_iphdr eon_iphdr;
	static struct route route;
E 6
E 2

	IFDEBUG(D_EON)
		printf("eonoutput \n" );
	ENDDEBUG

I 5
	ifp->if_lastchange = time;
	ifp->if_opackets++;
E 5
D 2
	if( dst->siso_family != AF_ISO )
		return EINVAL;
	if( dst->siso_addr.isoa_afi != AFI_RFC986 ) 
		return EINVAL;

	s = splnet();

	/* Nsel tells what type of multicast address, if multicast */
	switch( dst->siso_addr.rfc986_dsp[RFC986_NSEL_OFFSET]) {
E 2
I 2
D 6
	if( dst->siso_family != AF_ISO ) {
	einval:
E 6
I 6
	if (rt == 0 || (el = (struct eon_llinfo *)rt->rt_llinfo) == 0) {
		if (dst->siso_family == AF_LINK) {
			register struct sockaddr_dl *sdl = (struct sockaddr_dl *)dst;
D 13
			caddr_t ipaddrloc = LLADDR(sdl);
			int class = (sdl->sdl_alen == 5) ? 4[(u_char *)ipaddrloc] : 0;
E 13

D 13
			if (sdl->sdl_alen == 4 || sdl->sdl_alen == 5) {
D 11
				ipaddrloc = LLADDR(sdl);
E 11
				ro = &route;
				ei = &eon_iphdr;
				eoniphdr(ei, ipaddrloc, ro, class, 1);
				goto send;
			}
E 13
I 13
			ipaddrloc = LLADDR(sdl);
			alen = sdl->sdl_alen;
		} else if (dst->siso_family == AF_ISO && dst->siso_data[0] == AFI_SNA) {
			alen = dst->siso_nlen - 1;
			ipaddrloc = (caddr_t) dst->siso_data + 1;
E 13
		}
I 13
		switch (alen) {
		case 5:
			class =  4[(u_char *)ipaddrloc];
		case 4:
			ro = &route;
			ei = &eon_iphdr;
			eoniphdr(ei, ipaddrloc, ro, class, 1);
			goto send;
		}
E 13
einval:
E 6
		error =  EINVAL;
		goto flush;
	}
D 6
	if ((morig->m_flags & M_PKTHDR) == 0) {
E 6
I 6
	if ((el->el_flags & RTF_UP) == 0) {
		eonrtrequest(RTM_CHANGE, rt, (struct sockaddr *)0);
		if ((el->el_flags & RTF_UP) == 0) {
			error = EHOSTUNREACH;
			goto flush;
		}
	}
	if ((m->m_flags & M_PKTHDR) == 0) {
E 6
		printf("eon: got non headered packet\n");
		goto einval;
	}
D 6
	eoa = (struct sockaddr_eon *)dst;
	if (LEGIT_EONADDR(eoa)) {
		class = eoa->seon_protoid;
		dstipaddrloc = (caddr_t)&(eoa->seon_ipaddr);
	} else if (eoa->seon_afi == AFI_SNA) {
		dstipaddrloc = (caddr_t)&(dst->siso_data[1]);
		if (dst->siso_nlen == 6) {
			class = dst->siso_data[5];
		} else if (dst->siso_nlen == 7) {
			if (bcmp(dstipaddrloc, all_is.sc_snpa, 6))
				class = EON_MULTICAST_ES;
			else if (bcmp(dstipaddrloc, all_es.sc_snpa, 6))
				class = EON_MULTICAST_IS;
			else
				goto einval;
		} else
				goto einval;
	} else if (0 == iso_snparesolve(ifp, dst, edst, &snpalen)) {
		dstipaddrloc = (caddr_t)edst;
		class = edst[4];
	} else {
		error = EINVAL;
		goto flush;
	}
	switch (class) {
E 2
		case EON_NORMAL_ADDR:
			IncStat(es_out_normal);
D 2
			dstipaddrloc = (caddr_t)&(dst->siso_addr.rfc986_dsp[1]);
E 2
			single = 1;
			break;

		case EON_BROADCAST:
			IncStat(es_out_broad);
D 2
			if( eon_LINK_hdr.link == (struct qhdr *)0 ) {
E 2
I 2
			if(eon_LINK_hdr.link == eon_LINK_hdr.rlink) {
E 2
				error = EADDRNOTAVAIL;
			} else {
				qoffset = _offsetof( struct eon_centry, eonc_q_LINK);
				ent = qtocentry(eon_LINK_hdr.link, qoffset); 
				dstipaddrloc = (caddr_t) &(ent->eonc_addr);
			}
			break;
		case EON_MULTICAST_ES:
			IncStat(es_out_multi_es);
D 2
			if( eon_ES_hdr.link == (struct qhdr *)0 ) {
E 2
I 2
			if (eon_ES_hdr.link == eon_ES_hdr.rlink) {
E 2
				error = EADDRNOTAVAIL;
			} else {
				qoffset = _offsetof( struct eon_centry, eonc_q_ES);
				ent = qtocentry(eon_ES_hdr.link, qoffset); 
				dstipaddrloc = (caddr_t) &(ent->eonc_addr);
			}
			break;
		case EON_MULTICAST_IS:
			IncStat(es_out_multi_is);
D 2
			if( eon_IS_hdr.link == (struct qhdr *)0 ) {
E 2
I 2
			if (eon_IS_hdr.link == eon_IS_hdr.rlink) {
E 2
				error = EADDRNOTAVAIL;
			} else {
				qoffset = _offsetof( struct eon_centry, eonc_q_LINK);
				ent = qtocentry(eon_IS_hdr.link, qoffset); 
				dstipaddrloc = (caddr_t) &(ent->eonc_addr);
			}
			break;
		default:
D 2
			printf("NSEL bad value; treated as EON_NORMAL_ADDR\n");
			dst->siso_addr.rfc986_dsp[RFC986_NSEL_OFFSET] = EON_NORMAL_ADDR;
E 2
I 2
			printf("bad class value; treated as EON_NORMAL_ADDR\n");
			class = EON_NORMAL_ADDR;
E 2
			single = 1;
			break;
	}
	if( error )
		goto done;

	/* get data length -- needed later */
D 2
	datalen = m_datalen( morig );
E 2
I 2
	datalen = morig->m_pkthdr.len;
E 2
	IFDEBUG(D_EON)
		printf("eonoutput : m_datalen returns %d\n", datalen);
	ENDDEBUG

E 6
I 6
	ei = &el->el_ei;
	ro = &el->el_iproute;
I 11
	if (el->el_snpaoffset) {
		if (dst->siso_family == AF_ISO) {
			bcopy((caddr_t) &dst->siso_data[el->el_snpaoffset],
					(caddr_t) &ei->ei_ip.ip_dst, sizeof(ei->ei_ip.ip_dst));
		} else
			goto einval;
	}
E 11
send:
	/* put an eon_hdr in the buffer, prepended by an ip header */
	datalen = m->m_pkthdr.len + EONIPLEN;
E 6
D 2
	mh = m_getclr( M_DONTWAIT, MT_HEADER);
	if(mh == (struct mbuf *)0) {
E 2
I 2
	MGETHDR(mh, M_DONTWAIT, MT_HEADER);
	if(mh == (struct mbuf *)0)
E 2
D 6
		goto done;
D 2
	}
E 2

	/* put an eon_hdr in the buffer, prepended by an ip header */
D 2
	mh->m_act = (struct mbuf *)0;
E 2
	mh->m_len = sizeof(struct eon_hdr);
D 2
	mh->m_off = MMAXOFF - sizeof(struct eon_hdr);
E 2
I 2
	MH_ALIGN(mh, sizeof(struct eon_hdr));
E 2
	mh->m_next = morig;
	eonhdr = mtod(mh, struct eon_hdr *);
D 2
	eonhdr->eonh_class = 
		dst->siso_addr.rfc986_dsp[RFC986_NSEL_OFFSET];
E 2
I 2
	eonhdr->eonh_class = class;
E 2
	eonhdr->eonh_vers = EON_VERSION;
I 2
	eonhdr->eonh_csum = 0;
E 2

	IFDEBUG(D_EON)
		printf("eonoutput : gen csum (0x%x, offset %d, datalen %d)\n", 
			mh, _offsetof(struct eon_hdr, eonh_csum), sizeof(struct eon_hdr)); 
	ENDDEBUG
	iso_gen_csum(mh, 
		_offsetof(struct eon_hdr, eonh_csum), sizeof(struct eon_hdr)); 

D 2
	mh->m_len += sizeof(struct ip);
	mh->m_off -= sizeof(struct ip);
E 2
I 2
	mh->m_data -= sizeof(*iphdr);
	mh->m_len += sizeof(*iphdr);
E 2
	iphdr = mtod(mh, struct ip *);
I 2
	bzero((caddr_t)iphdr, sizeof (*iphdr));
E 2

	iphdr->ip_p = IPPROTO_EON;
E 6
I 6
		goto flush;
	mh->m_next = m;
	m = mh;
	MH_ALIGN(m, sizeof(struct eon_iphdr));
	m->m_len = sizeof(struct eon_iphdr);
E 6
D 2
	iphdr->ip_len = (sizeof(struct eon_hdr) + sizeof(struct ip) + datalen);
E 2
I 2
D 5
	iphdr->ip_len = (u_short)(mh->m_pkthdr.len = EONIPLEN + datalen);
E 5
I 5
	ifp->if_obytes +=
D 6
		(iphdr->ip_len = (u_short)(mh->m_pkthdr.len = EONIPLEN + datalen));
E 5
E 2
	iphdr->ip_ttl = MAXTTL;	
	iphdr->ip_src.s_addr = INADDR_ANY;
E 6
I 6
		(ei->ei_ip.ip_len = (u_short)(m->m_pkthdr.len = datalen));
	*mtod(m, struct eon_iphdr *) = *ei;
E 6

	IFDEBUG(D_EON)
D 6
		printf("eonoutput : after gen csum: ip_len %d/0x%x\n",
D 2
			(sizeof(struct eon_hdr) + sizeof(struct ip) + datalen),
			(sizeof(struct eon_hdr) + sizeof(struct ip) + datalen)
			);
E 2
I 2
						mh->m_pkthdr.len, mh->m_pkthdr.len);
E 6
I 6
		printf("eonoutput dst ip addr : %x\n",  ei->ei_ip.ip_dst.s_addr);
		printf("eonoutput ip_output : eonip header:\n");
		dump_buf(ei, sizeof(struct eon_iphdr));
E 6
E 2
	ENDDEBUG

D 6
	morig = mh;

	for(;;) {

		if( !single ) {
			/* make a copy to send */
			IFDEBUG(D_EON)
				printf("eonoutput : m_copy (0x%x, 0, 0x%x)\n", 
					morig, iphdr->ip_len);
			ENDDEBUG
D 2
			mh = m_copy(morig, 0, iphdr->ip_len);
			mh = m_pullup(mh, sizeof(struct ip));
E 2
I 2
			if (((mh = m_copy(morig, 0, morig->m_pkthdr.len)) == 0) ||
			    ((mh = m_pullup(mh, sizeof(struct ip))) == 0)) {
				error = ENOBUFS;
				goto done;
			}
E 2
			iphdr = mtod(mh, struct ip *);
		}
		IFDEBUG(D_EON)
			printf("eonoutput : bcopy 0x%x to 0x%x length %d\n",
				dstipaddrloc,
				(caddr_t)&(iphdr->ip_dst.s_addr), 
				sizeof(iphdr->ip_dst.s_addr));
		ENDDEBUG
D 2
		bcopy(
			dstipaddrloc,
			(caddr_t)&(iphdr->ip_dst.s_addr), sizeof(iphdr->ip_dst.s_addr));
E 2
I 2
		bcopy(dstipaddrloc, (caddr_t)&(iphdr->ip_dst.s_addr),
										sizeof(iphdr->ip_dst.s_addr));
E 2
		IFDEBUG(D_EON)
			printf("eonoutput : dst ip addr : %d.%d.%d.%d", 
				(iphdr->ip_dst.s_addr>>24)&0xff,
				(iphdr->ip_dst.s_addr>>16)&0xff,
				(iphdr->ip_dst.s_addr>>8)&0xff,
				(iphdr->ip_dst.s_addr)&0xff );
		ENDDEBUG

		IFDEBUG(D_EON)
			printf("eonoutput ip_output : eon header:\n");
			dump_buf(eonhdr, sizeof(struct eon_hdr));
			printf("ip header:\n");
			dump_buf(iphdr, sizeof(struct ip));
		ENDDEBUG

		IncStat(es_ipout);
		if( error = ip_output(mh, (struct mbuf *)0, (struct route *)0, 0) )
				break;

		IFDEBUG(D_EON)
			printf("eonoutput ip_output returns 0x%x; single %d\n", 
				error, single);
		ENDDEBUG

		if(single)
			break;

		q = centrytoq(ent, qoffset)->link;
		if( q == (struct qhdr *)0)
			break;
		ent = qtocentry( q,  qoffset );
		IFDEBUG(D_EON)
			printf("eonoutput : get next entry: 0x%x\n", ent);
		ENDDEBUG
		dstipaddrloc = (caddr_t) &(ent->eonc_addr);
		IFDEBUG(D_EON)
			printf("eonoutput : dump of eon_centry 0x%x:\n", ent );
			dump_buf(ent, sizeof(struct eon_centry) );
		ENDDEBUG
	}
done:
	if( !single ) {
		IFDEBUG(D_EON)
			printf("eonoutput : freeing morig 0x%x\n", morig);
		ENDDEBUG
I 2
flush:
E 2
		m_freem(morig);
	}
E 6
I 6
D 23
	error = ip_output(m, (struct mbuf *)0, ro, 0);
E 23
I 23
	error = ip_output(m, (struct mbuf *)0, ro, 0, NULL);
E 23
	m = 0;
E 6
I 5
	if (error) {
		ifp->if_oerrors++;
		ifp->if_opackets--;
D 6
		ifp->if_obytes -= datalen + EONIPLEN;
E 6
I 6
		ifp->if_obytes -= datalen;
E 6
	}
I 6
flush:
	if (m)
		m_freem(m);
E 6
E 5
D 2
	splx(s);
E 2
	return error;
}

D 2
eoninput(m, ifp)
E 2
I 2
eoninput(m, iphlen)
E 2
	register struct mbuf	*m;
D 2
	struct ifnet 			*ifp; /* real ifp */
E 2
I 2
	int iphlen;
E 2
{
D 2
	int						s;
E 2
	register struct eon_hdr	*eonhdr;
	register struct ip		*iphdr;
	struct ifnet 			*eonifp;
D 2
	register	int			datalen;
E 2
I 2
	int						s;
E 2

D 2
	s = splnet();

E 2
	eonifp = &eonif[0]; /* kludge - really want to give CLNP
						* the ifp for eon, not for the real device
						*/

	IFDEBUG(D_EON)
D 2
		printf("eoninput() 0x%x m_off 0x%x m_len 0x%x dequeued\n",
			m, m?m->m_off:0, m?m->m_len:0);
E 2
I 2
		printf("eoninput() 0x%x m_data 0x%x m_len 0x%x dequeued\n",
			m, m?m->m_data:0, m?m->m_len:0);
E 2
	ENDDEBUG

D 2
	if (m == 0) {
		goto drop;
E 2
I 2
	if (m == 0)
		return;
	if (iphlen > sizeof (struct ip))
		ip_stripoptions(m, (struct mbuf *)0);
	if (m->m_len < EONIPLEN) {
		if ((m = m_pullup(m, EONIPLEN)) == 0) {
			IncStat(es_badhdr);
drop:
			IFDEBUG(D_EON)
				printf("eoninput: DROP \n" );
			ENDDEBUG
			eonifp->if_ierrors ++;
			m_freem(m);
			return;
		}
E 2
	}
I 5
	eonif->if_ibytes += m->m_pkthdr.len;
	eonif->if_lastchange = time;
E 5
D 2
	m = m_pullup(m, (sizeof(struct eon_hdr)+sizeof(struct ip)));
	if (m == 0) {
		IncStat(es_badhdr);
		goto drop;
	}

E 2
	iphdr = mtod(m, struct ip *);
D 2

E 2
	/* do a few checks for debugging */
	if( iphdr->ip_p != IPPROTO_EON ) {
		IncStat(es_badhdr);
		goto drop;
	}
D 2

	/* drop ip header from the mbuf */
	m->m_len -= sizeof(struct ip);
	m->m_off += sizeof(struct ip);

E 2
I 2
	/* temporarily drop ip header from the mbuf */
	m->m_data += sizeof(struct ip);
E 2
	eonhdr = mtod(m, struct eon_hdr *);
D 2

E 2
I 2
	if( iso_check_csum( m, sizeof(struct eon_hdr) )   != EOK ) {
		IncStat(es_badcsum);
		goto drop;
	}
	m->m_data -= sizeof(struct ip);
		
E 2
	IFDEBUG(D_EON)
I 2
		printf("eoninput csum ok class 0x%x\n", eonhdr->eonh_class );
E 2
		printf("eoninput: eon header:\n");
		dump_buf(eonhdr, sizeof(struct eon_hdr));
	ENDDEBUG

	/* checks for debugging */
	if( eonhdr->eonh_vers != EON_VERSION) {
		IncStat(es_badhdr);
		goto drop;
	}
D 2

	datalen = m_datalen( m );
	if( iso_check_csum( m, sizeof(struct eon_hdr) )   != EOK ) {
		IncStat(es_badcsum);
		goto drop;
	}
		
	IFDEBUG(D_EON)
		printf("eoninput csum ok class 0x%x\n", eonhdr->eonh_class );
	ENDDEBUG
E 2
I 2
	m->m_flags &= ~(M_BCAST|M_MCAST);
E 2
	switch( eonhdr->eonh_class) {
		case EON_BROADCAST:
			IncStat(es_in_broad);
I 2
			m->m_flags |= M_BCAST;
E 2
			break;
		case EON_NORMAL_ADDR:
			IncStat(es_in_normal);
			break;
		case EON_MULTICAST_ES:
D 2
			if( ( eonifp->if_flags & IFF_ES) == 0 )
				goto drop;
E 2
			IncStat(es_in_multi_es);
I 2
			m->m_flags |= M_MCAST;
E 2
			break;
		case EON_MULTICAST_IS:
D 2
			if( ( eonifp->if_flags & IFF_IS) == 0 )
				goto drop;
E 2
			IncStat(es_in_multi_is);
I 2
			m->m_flags |= M_MCAST;
E 2
			break;
	}
D 5
	eonifp->if_ipackets ++;
E 5
I 5
	eonifp->if_ipackets++;
E 5

D 2
	/* drop eonhdr from the mbuf */
	m->m_len -= sizeof(struct eon_hdr);
	m->m_off += sizeof(struct eon_hdr);

E 2
	{
		/* put it on the CLNP queue and set soft interrupt */
		struct ifqueue 			*ifq;
		extern struct ifqueue 	clnlintrq;
D 2
		int						len;
E 2

D 2
		/* when acting as a subnet service, have to prepend a
		 * pointer to the ifnet before handing this to clnp (GAG)
		 */
		len = sizeof(struct snpa_hdr);
		if( ( m->m_off > MMINOFF + len) &&
			( m->m_off <= MMAXOFF )) {
			m->m_off -= len;
			m->m_len += len;
		} 
		( mtod(m, struct snpa_hdr *) )->snh_ifp = eonifp; /* KLUDGE */

		/* this is cutting it close */
		bcopy( &iphdr->ip_src, ( mtod(m, struct snpa_hdr *))->snh_shost, 
			sizeof(struct in_addr));
		bcopy( &iphdr->ip_dst, ( mtod(m, struct snpa_hdr *))->snh_dhost, 
			sizeof(struct in_addr));

E 2
I 2
		m->m_pkthdr.rcvif = eonifp; /* KLUDGE */
E 2
		IFDEBUG(D_EON)
			printf("eoninput to clnl IFQ\n");
		ENDDEBUG
		ifq = &clnlintrq;
D 2
		splimp();
E 2
I 2
		s = splimp();
E 2
		if (IF_QFULL(ifq)) {
			IF_DROP(ifq);
			m_freem(m);
D 2
			splx(s);
E 2
D 5
			eonifp->if_ierrors ++;
E 5
I 5
			eonifp->if_iqdrops++;
			eonifp->if_ipackets--;
E 5
I 2
			splx(s);
E 2
			return;
		}
		IF_ENQUEUE(ifq, m);
		IFDEBUG(D_EON) 
			printf(
D 2
	"0x%x enqueued on clnp Q: m_len 0x%x m_type 0x%x m_off 0x%x\n", 
				m, m->m_len, m->m_type, m->m_off);
E 2
I 2
	"0x%x enqueued on clnp Q: m_len 0x%x m_type 0x%x m_data 0x%x\n", 
				m, m->m_len, m->m_type, m->m_data);
E 2
			dump_buf(mtod(m, caddr_t), m->m_len);
		ENDDEBUG
D 2
		schednetisr(NETISR_CLNP);
E 2
I 2
		schednetisr(NETISR_ISO);
		splx(s);
E 2
	}
D 2
done:
	splx(s);
	return 0;
drop:
	IFDEBUG(D_EON)
		printf("eoninput: DROP \n" );
	ENDDEBUG
	eonifp->if_ierrors ++;
	m_freem(m);
	goto done;
E 2
}

int
eonctlinput(cmd, sin)
	int cmd;
	struct sockaddr_in *sin;
{
	extern u_char inetctlerrmap[];

	IFDEBUG(D_EON)
		printf("eonctlinput: cmd 0x%x addr: ", cmd);
		dump_isoaddr(sin);
		printf("\n");
	ENDDEBUG

	if (cmd < 0 || cmd > PRC_NCMDS)
		return 0;

	IncStat(es_icmp[cmd]);
	switch (cmd) {

D 2
		case	PRC_QUENCH2:
E 2
		case	PRC_QUENCH:
I 2
		case	PRC_QUENCH2:
E 2
			/* TODO: set the dec bit */
			break;
		case	PRC_TIMXCEED_REASS:
		case	PRC_ROUTEDEAD:
		case	PRC_HOSTUNREACH:
		case	PRC_UNREACH_NET:
		case	PRC_IFDOWN:
		case	PRC_UNREACH_HOST:
		case	PRC_HOSTDEAD:
		case	PRC_TIMXCEED_INTRANS:
			/* TODO: mark the link down */
			break;

		case	PRC_UNREACH_PROTOCOL:
		case	PRC_UNREACH_PORT:
D 6
		case	PRC_UNREACH_NEEDFRAG:
E 6
		case	PRC_UNREACH_SRCFAIL:
		case	PRC_REDIRECT_NET:
		case	PRC_REDIRECT_HOST:
		case	PRC_REDIRECT_TOSNET:
		case	PRC_REDIRECT_TOSHOST:
		case	PRC_MSGSIZE:
		case	PRC_PARAMPROB:
D 13
			printf("eonctlinput: ICMP cmd 0x%x\n", cmd );
E 13
I 13
			/* printf("eonctlinput: ICMP cmd 0x%x\n", cmd );*/
E 13
		break;
	}
	return 0;
}

D 2
#endif NEON>0
E 2
I 2
#endif
E 2
E 1
