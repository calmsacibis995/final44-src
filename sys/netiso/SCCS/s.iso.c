h46887
s 00001/00001/00892
d D 8.3 95/01/09 17:51:54 cgd 26 25
c 64-bit changes
e
s 00000/00001/00893
d D 8.2 93/11/15 13:35:41 sklower 25 24
c af.h has been retired
e
s 00002/00002/00892
d D 8.1 93/06/10 23:19:30 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00886
d D 7.23 93/05/25 11:51:36 bostic 23 22
c trailing comment after #else or #endif
e
s 00002/00002/00892
d D 7.22 93/03/09 17:41:19 sklower 22 21
c change printf in unused function for jch
e
s 00008/00000/00886
d D 7.21 92/11/25 20:10:54 sklower 21 20
c dubious change for TUBA
e
s 00019/00019/00867
d D 7.20 92/10/11 12:21:49 bostic 20 19
c make kernel includes standard
e
s 00001/00001/00885
d D 7.19 92/09/21 19:06:03 mckusick 19 18
c need to include systm.h to get min and max
e
s 00004/00022/00882
d D 7.18 92/07/09 00:01:53 sklower 18 17
c changes to add routing tables via the domain switch
e
s 00001/00002/00903
d D 7.17 91/12/19 17:43:12 sklower 17 16
c reference count ifaddrs to make them safe for deletion
e
s 00002/00001/00903
d D 7.16 91/09/03 21:15:47 sklower 16 15
c upper level protocols now call when setting socket level options
e
s 00002/00006/00902
d D 7.15 91/07/30 17:41:17 sklower 15 14
c change require by using routing vector instead of linked list
e
s 00003/00004/00905
d D 7.14 91/06/27 19:34:01 sklower 14 13
c minor change to work with both new and old vm systems
e
s 00005/00003/00904
d D 7.13 91/05/29 19:38:15 sklower 13 12
c offset for routing table for iso was wrong; set value for dstaddr.nlen
e
s 00009/00006/00898
d D 7.12 91/05/06 19:24:01 bostic 12 11
c new copyright; att/bsd/shared
e
s 00004/00005/00900
d D 7.11 91/03/12 15:21:07 sklower 11 10
c pseudodev argoxtwentyfive becomes option TPCONS
e
s 00001/00001/00904
d D 7.10 90/06/22 15:46:19 sklower 10 9
c remove stupid use of u.u_error.
e
s 00015/00004/00890
d D 7.9 90/06/20 19:02:47 sklower 9 8
c changed esis to make use of routing table; mostly works;
c checkpoint before UW merge
e
s 00006/00004/00888
d D 7.8 90/04/12 01:49:57 sklower 8 7
c for routes to interfaces, must generate destination
e
s 00001/00001/00891
d D 7.7 90/01/17 00:12:18 sklower 7 6
c fix from HP
e
s 00000/00044/00892
d D 7.6 89/09/26 23:51:15 sklower 6 5
c remove unneeded routine iso_routeifa
e
s 00001/00001/00935
d D 7.5 89/08/29 13:44:18 sklower 5 4
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00002/00936
d D 7.4 89/05/05 00:27:45 mckusick 4 3
c get rid of unneeded include's
e
s 00002/00002/00936
d D 7.3 89/04/26 18:51:51 mckusick 3 2
c use new form of suser()
e
s 00307/00331/00631
d D 7.2 89/04/22 11:54:04 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00962/00000/00000
d D 7.1 88/12/14 15:29:40 sklower 1 0
c date and time created 88/12/14 15:29:40 by sklower
e
u
U
t
T
I 12
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

E 12
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
 * $Header: iso.c,v 4.11 88/09/19 14:58:35 root Exp $ 
 * $Source: /usr/argo/sys/netiso/RCS/iso.c,v $ 
I 2
D 12
 *	%W% (Berkeley) %G%
E 12
E 2
 *
 * iso.c: miscellaneous routines to support the iso address family
 */
D 12

#ifndef lint
static char *rcsid = "$Header: iso.c,v 4.11 88/09/19 14:58:35 root Exp $";
#endif

E 12

D 2
#include "../h/types.h"
#include "../h/param.h"
#include "../h/ioctl.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/uio.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/errno.h"
E 2
I 2
D 19
#include "types.h"
E 19
D 20
#include "param.h"
I 19
#include "systm.h"
E 19
#include "ioctl.h"
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
D 4
#include "uio.h"
#include "dir.h"
E 4
D 14
#include "user.h"
E 14
#include "errno.h"
E 20
I 20
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 20
E 2

D 20
#include "../net/if.h"
#include "../net/route.h"
#include "../net/af.h"
E 20
I 20
#include <net/if.h>
#include <net/route.h>
D 25
#include <net/af.h>
E 25
E 20

D 2
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
#include "../netiso/iso_snpac.h"
#include "../netiso/iso_pcb.h"
#include "../netiso/clnp.h"
#include "../netiso/argo_debug.h"
E 2
I 2
D 20
#include "iso.h"
#include "iso_var.h"
#include "iso_snpac.h"
#include "iso_pcb.h"
#include "clnp.h"
#include "argo_debug.h"
E 20
I 20
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_snpac.h>
#include <netiso/iso_pcb.h>
#include <netiso/clnp.h>
#include <netiso/argo_debug.h>
I 21
#ifdef TUBA
#include <netiso/tuba_table.h>
#endif
E 21
E 20
E 2

#ifdef ISO
I 2
D 11
#include "argoxtwentyfive.h"
E 11
E 2

int	iso_interfaces = 0;		/* number of external interfaces */
extern	struct ifnet loif;	/* loopback interface */
I 9
D 18
int ether_output(), llc_rtrequest();
E 18
I 18
int	ether_output();
void	llc_rtrequest();
E 18
E 9

D 18

E 18
/*
D 18
 * FUNCTION:		iso_init
 *
 * PURPOSE:			initialize the iso address family
 *
 * RETURNS:			nothing
 *
D 13
 * SIDE EFFECTS:	1) zeros the maptab table.
I 2
 *					2) initializes the routing table.
E 13
I 13
 * SIDE EFFECTS:	1) initializes the routing table.
E 13
E 2
 *
I 13
 *
E 13
 * NOTES:			
 */
I 2
D 15
struct radix_node_head *iso_rnhead;
E 15
E 2
iso_init()
{
D 2
	extern struct maptab	iso_snpac[];
	extern int 				iso_snpac_size;
E 2
I 2
D 9
	extern struct spna_cache	iso_snpac[];
	extern u_int 				iso_snpac_size;
E 9
D 15
	static iso_init_done;
E 2

D 2
 	bzero((caddr_t)iso_snpac, iso_snpac_size * sizeof(struct snpa_cache));
E 2
I 2
	if (iso_init_done == 0) {
		iso_init_done++;
D 9
		bzero((caddr_t)iso_snpac, iso_snpac_size * sizeof(struct snpa_cache));
E 9
D 13
		rn_inithead(&iso_rnhead, 40, AF_ISO);
E 13
I 13
		rn_inithead(&iso_rnhead, 48, AF_ISO);
E 15
I 15
	if (rt_tables[AF_ISO] == 0) {
		rn_inithead(rt_tables + AF_ISO, 48);
E 15
E 13
	}
E 2
}

/*
E 18
 * FUNCTION:		iso_addrmatch1
 *
 * PURPOSE:			decide if the two iso_addrs passed are equal
 *
 * RETURNS:			true if the addrs match, false if they do not
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
iso_addrmatch1(isoaa, isoab)
D 2
struct iso_addr	*isoaa, *isoab;		/* addresses to check */
E 2
I 2
register struct iso_addr *isoaa, *isoab;		/* addresses to check */
E 2
{
D 2
	int	compare_len;
E 2
I 2
	u_int	compare_len;
E 2

	IFDEBUG(D_ROUTE)
		printf("iso_addrmatch1: comparing lengths: %d to %d\n", isoaa->isoa_len,
			isoab->isoa_len);
		printf("a:\n");
D 2
		dump_buf((caddr_t)isoaa, isoaa->isoa_len);
E 2
I 2
		dump_buf(isoaa->isoa_genaddr, isoaa->isoa_len);
E 2
		printf("b:\n");
D 2
		dump_buf((caddr_t)isoab, isoab->isoa_len);
E 2
I 2
		dump_buf(isoab->isoa_genaddr, isoab->isoa_len);
E 2
	ENDDEBUG

	if ((compare_len = isoaa->isoa_len) != isoab->isoa_len) {
		IFDEBUG(D_ROUTE)
			printf("iso_addrmatch1: returning false because of lengths\n");
		ENDDEBUG
		return 0;
	}
	
I 2
#ifdef notdef
E 2
	/* TODO : generalize this to all afis with masks */
	if(	isoaa->isoa_afi == AFI_37 ) {
		/* must not compare 2 least significant digits, or for
		 * that matter, the DSP
		 */
		compare_len = ADDR37_IDI_LEN - 1; 
	}
I 2
#endif
E 2

	IFDEBUG(D_ROUTE)
		int i;
		char *a, *b;

D 2
		a = (char *) isoaa;
		b = (char *) isoab;
E 2
I 2
		a = isoaa->isoa_genaddr;
		b = isoab->isoa_genaddr;
E 2

		for (i=0; i<compare_len; i++) {
			printf("<%x=%x>", a[i]&0xff, b[i]&0xff);
			if (a[i] != b[i]) {
				printf("\naddrs are not equal at byte %d\n", i);
				return(0);
			}
		}
		printf("\n");
		printf("addrs are equal\n");
		return (1);
	ENDDEBUG
D 2
	return (!bcmp((caddr_t)isoaa, (caddr_t)isoab, compare_len));
E 2
I 2
	return (!bcmp(isoaa->isoa_genaddr, isoab->isoa_genaddr, compare_len));
E 2
}

/*
 * FUNCTION:		iso_addrmatch
 *
 * PURPOSE:			decide if the two sockadrr_isos passed are equal
 *
 * RETURNS:			true if the addrs match, false if they do not
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
iso_addrmatch(sisoa, sisob)
struct sockaddr_iso	*sisoa, *sisob;		/* addresses to check */
{
	return(iso_addrmatch1(&sisoa->siso_addr, &sisob->siso_addr));
}
D 2

E 2
I 2
#ifdef notdef
E 2
/*
 * FUNCTION:		iso_netmatch
 *
 * PURPOSE:			similar to iso_addrmatch but takes sockaddr_iso
 *					as argument.
 *
 * RETURNS:			true if same net, false if not
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
iso_netmatch(sisoa, sisob)
struct sockaddr_iso *sisoa, *sisob;
{
	u_char			bufa[sizeof(struct sockaddr_iso)];
	u_char			bufb[sizeof(struct sockaddr_iso)];
	register int	lena, lenb;

	lena = iso_netof(&sisoa->siso_addr, bufa);
	lenb = iso_netof(&sisob->siso_addr, bufb);

	IFDEBUG(D_ROUTE)
		printf("iso_netmatch: comparing lengths: %d to %d\n", lena, lenb);
		printf("a:\n");
		dump_buf(bufa, lena);
		printf("b:\n");
		dump_buf(bufb, lenb);
	ENDDEBUG

	return ((lena == lenb) && (!bcmp(bufa, bufb, lena)));
}
I 2
D 23
#endif notdef
E 23
I 23
#endif /* notdef */
E 23
E 2

/*
 * FUNCTION:		iso_hashchar
 *
 * PURPOSE:			Hash all character in the buffer specified into
 *					a long. Return the long.
 *
 * RETURNS:			The hash value.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			The hash is achieved by exclusive ORing 4 byte
 *					quantities. 
 */
u_long
iso_hashchar(buf, len)
register caddr_t	buf;		/* buffer to pack from */
register int		len;		/* length of buffer */
{
	register u_long	h = 0;
	register int	i;

	for (i=0; i<len; i+=4) {
		register u_long	l = 0;

		if ((len - i) < 4) {
			/* buffer not multiple of 4 */
			switch (len - i) {
				case 3:
					l |= buf[i+2] << 8;
				case 2:
					l |= buf[i+1] << 16;
				case 1:
					l |= buf[i] << 24;
					break;
				default:
					printf("iso_hashchar: unexpected value x%x\n", len - i);
					break;
			}
		} else {
			l |= buf[i] << 24;
			l |= buf[i+1] << 16;
			l |= buf[i+2] << 8;
			l |= buf[i+3];
		}

		h ^= l;
	}
	
	h ^= (u_long) (len % 4);

	return(h);
}
D 2

E 2
I 2
#ifdef notdef
E 2
/*
 * FUNCTION:		iso_hash
 *
 * PURPOSE:			Fill in fields of afhash structure based upon addr passed.
 *
 * RETURNS:			none
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
iso_hash(siso, hp)
struct sockaddr_iso	*siso;		/* address to perform hash on */
struct afhash		*hp;		/* RETURN: hash info here */
{
	u_long			buf[sizeof(struct sockaddr_iso)+1/4];
	register int	bufsize;


	bzero(buf, sizeof(buf));

	bufsize = iso_netof(&siso->siso_addr, buf);
	hp->afh_nethash = iso_hashchar((caddr_t)buf, bufsize);

	IFDEBUG(D_ROUTE)
		printf("iso_hash: iso_netof: bufsize = %d\n", bufsize);
	ENDDEBUG

	hp->afh_hosthash = iso_hashchar((caddr_t)&siso->siso_addr, 
		siso->siso_addr.isoa_len);

	IFDEBUG(D_ROUTE)
		printf("iso_hash: %s: nethash = x%x, hosthash = x%x\n",
			clnp_iso_addrp(&siso->siso_addr), hp->afh_nethash, 
			hp->afh_hosthash);
	ENDDEBUG
}
D 2

E 2
/*
 * FUNCTION:		iso_netof
 *
 * PURPOSE:			Extract the network portion of the iso address.
 *					The network portion of the iso address varies depending
 *					on the type of address. The network portion of the
 *					address will include the IDP. The network portion is:
 *			
 *						TYPE			DESC
 *					t37					The AFI and x.121 (IDI)
 *					osinet				The AFI, orgid, snetid
 *					rfc986				The AFI, vers and network part of
 *										internet address.
 *
 * RETURNS:			number of bytes placed into buf.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Buf is assumed to be big enough
 */
iso_netof(isoa, buf)
struct iso_addr	*isoa;		/* address */
caddr_t			buf;		/* RESULT: network portion of address here */
{
	u_int		len = 1;	/* length of afi */

	switch (isoa->isoa_afi) {
		case AFI_37:
			/*
			 * Due to classic x.25 tunnel vision, there is no
			 * net portion of an x.121 address.  For our purposes
			 * the AFI will do, so that all x.25 -type addresses
			 * map to the single x.25 SNPA. (Cannot have more than
			 * one, obviously).
			 */

			break;

/* 		case AFI_OSINET:*/
		case AFI_RFC986: {
			u_short	idi;	/* value of idi */

			/* osinet and rfc986 have idi in the same place */
			CTOH(isoa->rfc986_idi[0], isoa->rfc986_idi[1], idi);

			if (idi == IDI_OSINET)
/*
 *	Network portion of OSINET address can only be the IDI. Clearly,
 *	with one x25 interface, one could get to several orgids, and
 *	several snetids.
				len += (ADDROSINET_IDI_LEN + OVLOSINET_ORGID_LEN + 
						OVLOSINET_SNETID_LEN);
 */
				len += ADDROSINET_IDI_LEN;
			else if (idi == IDI_RFC986) {
				u_long				inetaddr;
				struct ovl_rfc986	*o986 = (struct ovl_rfc986 *)isoa;

				/* bump len to include idi and version (1 byte) */
				len += ADDRRFC986_IDI_LEN + 1;

				/* get inet addr long aligned */
				bcopy(o986->o986_inetaddr, &inetaddr, sizeof(inetaddr));
				inetaddr = ntohl(inetaddr);	/* convert to host byte order */

				IFDEBUG(D_ROUTE)
					printf("iso_netof: isoa ");
					dump_buf(isoa, sizeof(*isoa));
					printf("iso_netof: inetaddr 0x%x ", inetaddr);
				ENDDEBUG

				/* bump len by size of network portion of inet address */
				if (IN_CLASSA(inetaddr)) {
					len += 4-IN_CLASSA_NSHIFT/8;
					IFDEBUG(D_ROUTE)
						printf("iso_netof: class A net len is now %d\n", len);
					ENDDEBUG
				} else if (IN_CLASSB(inetaddr)) {
					len += 4-IN_CLASSB_NSHIFT/8;
					IFDEBUG(D_ROUTE)
						printf("iso_netof: class B net len is now %d\n", len);
					ENDDEBUG
				} else {
					len += 4-IN_CLASSC_NSHIFT/8;
					IFDEBUG(D_ROUTE)
						printf("iso_netof: class C net len is now %d\n", len);
					ENDDEBUG
				}
			} else
				len = 0;
		} break;

		default:
			len = 0;
	}

	bcopy((caddr_t)isoa, buf, len);
	IFDEBUG(D_ROUTE)
D 22
		printf("in_netof: isoa ");
E 22
I 22
		printf("iso_netof: isoa ");
E 22
		dump_buf(isoa, len);
D 22
		printf("in_netof: net ");
E 22
I 22
		printf("iso_netof: net ");
E 22
		dump_buf(buf, len);
	ENDDEBUG
	return len;
}
D 2

E 2
I 2
D 23
#endif notdef
E 23
I 23
#endif /* notdef */
E 23
E 2
/*
D 2
 *	The following is a kludge until I figure something out. Since AFISO
 *	allows >1 addr/ifp, SIOCGIFADDR can possibly return more than one
 *	address. Rather than changing the ifreq structure, I have set up
 *	the ioctl so it will return the address in sequential calls. When
 *	all addresses have been read, EADDRNOTAVAIL will be returned.
 *
 *	A call to delete or set an addr will cause a subsequent get to
 *	retrieve the first addr, even if the first had already been read.
 *
 *	The static pointer iso_ia keeps track of which addrs have been read.
E 2
I 2
 * Generic iso control operations (ioctl's).
 * Ifp is 0 if not an interface-specific ioctl.
E 2
 */
D 2
static struct iso_ifaddr *iso_iap = NULL;

/*
 * FUNCTION:		iso_control
 *
 * PURPOSE:			Generic iso control operations (ioctl's).
 *					Ifp is 0 if this is not an interface-specific ioctl.
 *
 * RETURNS:			unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			The iso address family will allow more than one
 *					iso address per interface as long as they are different
 *					iso address types. The three types currently supported 
 *					are rfc986, t37, and osinet.
 */
E 2
I 2
/* ARGSUSED */
E 2
iso_control(so, cmd, data, ifp)
D 2
struct socket	*so;		/* socket ioctl arrived on */
int				cmd;		/* ioctl to perform */
caddr_t			data;		/* data for the ioctl */
struct ifnet	*ifp;		/* optional interface ptr */
E 2
I 2
	struct socket *so;
D 26
	int cmd;
E 26
I 26
	u_long cmd;
E 26
	caddr_t data;
	register struct ifnet *ifp;
E 2
{
D 2
	register struct ifreq		*ifr = (struct ifreq *)data;
	register struct iso_ifaddr	*ia = 0;
	struct ifaddr				*ifa;
	struct mbuf					*m;
E 2
I 2
	register struct iso_ifreq *ifr = (struct iso_ifreq *)data;
	register struct iso_ifaddr *ia = 0;
	register struct ifaddr *ifa;
	struct iso_ifaddr *oia;
	struct iso_aliasreq *ifra = (struct iso_aliasreq *)data;
	int error, hostIsNew, maskIsNew;
E 2

I 2
	/*
	 * Find address for this interface, if it exists.
	 */
	if (ifp)
		for (ia = iso_ifaddr; ia; ia = ia->ia_next)
			if (ia->ia_ifp == ifp)
				break;
E 2

	switch (cmd) {
D 2
	case SIOCSIFADDR:
E 2
I 2

	case SIOCAIFADDR_ISO:
	case SIOCDIFADDR_ISO:
		if (ifra->ifra_addr.siso_family == AF_ISO)
		    for (oia = ia; ia; ia = ia->ia_next) {
			if (ia->ia_ifp == ifp  &&
			    SAME_ISOADDR(&ia->ia_addr, &ifra->ifra_addr))
				break;
		}
E 2
D 3
		if (!suser())
			return (u.u_error);
E 3
I 3
D 14
		if (error = suser(u.u_cred, &u.u_acflag))
			return (error);
E 14
I 14
		if ((so->so_state & SS_PRIV) == 0)
			return (EPERM);
E 14
E 3
D 2

E 2
		if (ifp == 0)
D 2
			panic("iso_control: SIOCSIFADDR");
E 2
I 2
			panic("iso_control");
		if (ia == (struct iso_ifaddr *)0) {
			struct iso_ifaddr *nia;
			if (cmd == SIOCDIFADDR_ISO)
				return (EADDRNOTAVAIL);
I 21
#ifdef TUBA
			/* XXXXXX can't be done in the proto init routines */
			if (tuba_tree == 0)
				tuba_table_init();
#endif
E 21
			MALLOC(nia, struct iso_ifaddr *, sizeof(*nia),
				       M_IFADDR, M_WAITOK);
			if (nia == (struct iso_ifaddr *)0)
				return (ENOBUFS);
			bzero((caddr_t)nia, sizeof(*nia));
			if (ia = iso_ifaddr) {
				for ( ; ia->ia_next; ia = ia->ia_next)
					;
				ia->ia_next = nia;
			} else
				iso_ifaddr = nia;
			ia = nia;
			if (ifa = ifp->if_addrlist) {
				for ( ; ifa->ifa_next; ifa = ifa->ifa_next)
					;
				ifa->ifa_next = (struct ifaddr *) ia;
			} else
				ifp->if_addrlist = (struct ifaddr *) ia;
			ia->ia_ifa.ifa_addr = (struct sockaddr *)&ia->ia_addr;
			ia->ia_ifa.ifa_dstaddr
					= (struct sockaddr *)&ia->ia_dstaddr;
			ia->ia_ifa.ifa_netmask
					= (struct sockaddr *)&ia->ia_sockmask;
			ia->ia_ifp = ifp;
			if (ifp != &loif)
				iso_interfaces++;
		}
		break;
E 2

D 2
		/* 
		 *	Check if a iso address of same type exists for ifp 
		 *	If it does, then return an error.
		 */
		for (ia = iso_ifaddr; ia; ia = ia->ia_next) {
			if (ia->ia_ifp == ifp) {
				struct sockaddr_iso *siso; 
E 2
I 2
#define cmdbyte(x)	(((x) >> 8) & 0xff)
	default:
		if (cmdbyte(cmd) == 'a')
D 14
			return (snpac_ioctl(cmd, data));
E 14
I 14
			return (snpac_ioctl(so, cmd, data));
E 14
		if (ia == (struct iso_ifaddr *)0)
			return (EADDRNOTAVAIL);
		break;
	}
	switch (cmd) {
E 2

D 2
				siso = (struct sockaddr_iso *)&ifr->ifr_addr;
				if (iso_eqtype(&IA_SIS(ia)->siso_addr, &siso->siso_addr))
					return(EADDRNOTAVAIL);
			}
		}
E 2
I 2
	case SIOCGIFADDR_ISO:
		ifr->ifr_Addr = ia->ia_addr;
		break;
E 2

D 2
		/*
		 *	Go ahead and create new ifaddr
		 *
		 *	Link addr into list of iso addresses
		 */
		m = m_getclr(M_WAIT, MT_IFADDR);
		if (m == (struct mbuf *)NULL)
			return (ENOBUFS);
		if (ia = iso_ifaddr) {
			for ( ; ia->ia_next; ia = ia->ia_next)
				;
			ia->ia_next = mtod(m, struct iso_ifaddr *);
		} else
			iso_ifaddr = mtod(m, struct iso_ifaddr *);
		iso_iap = iso_ifaddr;
		
		/*
		 *	Link addr into list on interface
		 */
		ia = mtod(m, struct iso_ifaddr *);
		if (ifa = ifp->if_addrlist) {
			for ( ; ifa->ifa_next; ifa = ifa->ifa_next)
				;
			ifa->ifa_next = (struct ifaddr *) ia;
		} else
			ifp->if_addrlist = (struct ifaddr *) ia;
E 2
I 2
	case SIOCGIFDSTADDR_ISO:
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
		ifr->ifr_Addr = ia->ia_dstaddr;
		break;
E 2

D 2
		ia->ia_ifp = ifp;
		IA_SIS(ia)->siso_family = AF_ISO;
		if (ifp != &loif)
			iso_interfaces++;
		return (iso_ifinit(ifp, ia, &ifr->ifr_addr));
E 2
I 2
	case SIOCGIFNETMASK_ISO:
		ifr->ifr_Addr = ia->ia_sockmask;
		break;
E 2

D 2
	case SIOCGIFADDR:
		for (ia = iso_iap; ia; ia = ia->ia_next) {
			if (ia->ia_ifp == ifp) {
				ifr->ifr_addr = ia->ia_addr;
				iso_iap = ia->ia_next;
				return (0);
E 2
I 2
	case SIOCAIFADDR_ISO:
D 10
		maskIsNew = 0; hostIsNew = 1; error = u.u_error;
E 10
I 10
		maskIsNew = 0; hostIsNew = 1; error = 0;
E 10
		if (ia->ia_addr.siso_family == AF_ISO) {
			if (ifra->ifra_addr.siso_len == 0) {
				ifra->ifra_addr = ia->ia_addr;
				hostIsNew = 0;
			} else if (SAME_ISOADDR(&ia->ia_addr, &ifra->ifra_addr))
				hostIsNew = 0;
		}
		if (ifra->ifra_mask.siso_len) {
			iso_ifscrub(ifp, ia);
			ia->ia_sockmask = ifra->ifra_mask;
			maskIsNew = 1;
		}
		if ((ifp->if_flags & IFF_POINTOPOINT) &&
		    (ifra->ifra_dstaddr.siso_family == AF_ISO)) {
			iso_ifscrub(ifp, ia);
			ia->ia_dstaddr = ifra->ifra_dstaddr;
			maskIsNew  = 1; /* We lie; but the effect's the same */
		}
		if (ifra->ifra_addr.siso_family == AF_ISO &&
					    (hostIsNew || maskIsNew)) {
			error = iso_ifinit(ifp, ia, &ifra->ifra_addr, 0);
		}
		if (ifra->ifra_snpaoffset)
			ia->ia_snpaoffset = ifra->ifra_snpaoffset;
		return (error);

	case SIOCDIFADDR_ISO:
		iso_ifscrub(ifp, ia);
		if ((ifa = ifp->if_addrlist) == (struct ifaddr *)ia)
			ifp->if_addrlist = ifa->ifa_next;
		else {
			while (ifa->ifa_next &&
			       (ifa->ifa_next != (struct ifaddr *)ia))
				    ifa = ifa->ifa_next;
			if (ifa->ifa_next)
			    ifa->ifa_next = ((struct ifaddr *)ia)->ifa_next;
			else
				printf("Couldn't unlink isoifaddr from ifp\n");
		}
		oia = ia;
		if (oia == (ia = iso_ifaddr)) {
			iso_ifaddr = ia->ia_next;
		} else {
			while (ia->ia_next && (ia->ia_next != oia)) {
				ia = ia->ia_next;
E 2
			}
I 2
			if (ia->ia_next)
			    ia->ia_next = oia->ia_next;
			else
				printf("Didn't unlink isoifadr from list\n");
E 2
		}
D 2
		iso_iap = iso_ifaddr;
		return(EADDRNOTAVAIL);
E 2
I 2
D 17
		free((caddr_t)oia, M_IFADDR);
E 17
I 17
		IFAFREE((&oia->ia_ifa));
E 17
		break;
E 2

D 2
	case SIOCDIFADDR: /* TODO: what about this ioctl on other families */
		if (!suser())
			return (u.u_error);
		iso_iap = iso_ifaddr;

		if (ifp == 0)
			panic("iso_control: SIOCDIFADDR");

		return (iso_ifdelete(ifp, &ifr->ifr_addr));

E 2
	default:
		if (ifp == 0 || ifp->if_ioctl == 0)
			return (EOPNOTSUPP);
		return ((*ifp->if_ioctl)(ifp, cmd, data));
	}
I 2
	return (0);
E 2
}

I 2
/*
 * Delete any existing route for an interface.
 */
iso_ifscrub(ifp, ia)
	register struct ifnet *ifp;
	register struct iso_ifaddr *ia;
{
I 9
	int nsellength = ia->ia_addr.siso_tlen;
E 9
	if ((ia->ia_flags & IFA_ROUTE) == 0)
		return;
I 9
	ia->ia_addr.siso_tlen = 0;
E 9
	if (ifp->if_flags & IFF_LOOPBACK)
		rtinit(&(ia->ia_ifa), (int)RTM_DELETE, RTF_HOST);
	else if (ifp->if_flags & IFF_POINTOPOINT)
		rtinit(&(ia->ia_ifa), (int)RTM_DELETE, RTF_HOST);
	else {
		rtinit(&(ia->ia_ifa), (int)RTM_DELETE, 0);
	}
I 9
	ia->ia_addr.siso_tlen = nsellength;
E 9
	ia->ia_flags &= ~IFA_ROUTE;
}

/*
 * Initialize an interface's internet address
 * and routing table entry.
 */
iso_ifinit(ifp, ia, siso, scrub)
	register struct ifnet *ifp;
	register struct iso_ifaddr *ia;
	struct sockaddr_iso *siso;
{
	struct sockaddr_iso oldaddr;
D 9
	int s = splimp(), error;
E 9
I 9
	int s = splimp(), error, nsellength;
E 9

	oldaddr = ia->ia_addr;
	ia->ia_addr = *siso;
	/*
	 * Give the interface a chance to initialize
	 * if this is its first address,
	 * and to validate the address if necessary.
	 */
D 18
	if (ifp->if_ioctl && (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ia))) {
E 18
I 18
	if (ifp->if_ioctl &&
				(error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, (caddr_t)ia))) {
E 18
		splx(s);
		ia->ia_addr = oldaddr;
		return (error);
	}
	if (scrub) {
		ia->ia_ifa.ifa_addr = (struct sockaddr *)&oldaddr;
		iso_ifscrub(ifp, ia);
		ia->ia_ifa.ifa_addr = (struct sockaddr *)&ia->ia_addr;
	}
I 9
	/* XXX -- The following is here temporarily out of laziness
	   in not changing every ethernet driver's if_ioctl routine */
	if (ifp->if_output == ether_output) {
		ia->ia_ifa.ifa_rtrequest = llc_rtrequest;
		ia->ia_ifa.ifa_flags |= RTF_CLONING;
D 17
		ia->ia_ifa.ifa_llinfolen = sizeof(struct llinfo_llc);
E 17
	}
E 9
	/*
	 * Add route for the network.
	 */
I 9
	nsellength = ia->ia_addr.siso_tlen;
	ia->ia_addr.siso_tlen = 0;
E 9
	if (ifp->if_flags & IFF_LOOPBACK) {
		ia->ia_ifa.ifa_dstaddr = ia->ia_ifa.ifa_addr;
D 8
		rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_HOST|RTF_UP);
E 8
I 8
		error = rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_HOST|RTF_UP);
E 8
	} else if (ifp->if_flags & IFF_POINTOPOINT &&
		 ia->ia_dstaddr.siso_family == AF_ISO)
D 8
		rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_HOST|RTF_UP);
E 8
I 8
		error = rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_HOST|RTF_UP);
E 8
	else {
D 8
		rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_UP);
E 8
I 8
		rt_maskedcopy(ia->ia_ifa.ifa_addr, ia->ia_ifa.ifa_dstaddr,
			ia->ia_ifa.ifa_netmask);
I 13
		ia->ia_dstaddr.siso_nlen =
			min(ia->ia_addr.siso_nlen, (ia->ia_sockmask.siso_len - 6));
E 13
		error = rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_UP);
E 8
	}
I 9
	ia->ia_addr.siso_tlen = nsellength;
E 9
	ia->ia_flags |= IFA_ROUTE;
	splx(s);
D 8
	return (0);
E 8
I 8
	return (error);
E 8
}
#ifdef notdef

E 2
struct ifaddr *
iso_ifwithidi(addr)
	register struct sockaddr *addr;
{
	register struct ifnet *ifp;
	register struct ifaddr *ifa;
	register u_int af = addr->sa_family;

	if (af != AF_ISO)
		return (0);
	IFDEBUG(D_ROUTE)
		printf(">>> iso_ifwithidi addr\n");
		dump_isoaddr( (struct sockaddr_iso *)(addr));
		printf("\n");
	ENDDEBUG
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		IFDEBUG(D_ROUTE)
			printf("iso_ifwithidi ifnet %s\n", ifp->if_name);
		ENDDEBUG
		for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next) {
			IFDEBUG(D_ROUTE)
				printf("iso_ifwithidi address ");
D 2
				dump_isoaddr( (struct sockaddr_iso *)(&ifa->ifa_addr));
E 2
I 2
				dump_isoaddr( (struct sockaddr_iso *)(ifa->ifa_addr));
E 2
			ENDDEBUG
D 2
			if (ifa->ifa_addr.sa_family != addr->sa_family)
E 2
I 2
			if (ifa->ifa_addr->sa_family != addr->sa_family)
E 2
				continue;

#define	IFA_SIS(ifa)\
D 2
	((struct sockaddr_iso *)&((ifa)->ifa_addr))
E 2
I 2
	((struct sockaddr_iso *)((ifa)->ifa_addr))
E 2

			IFDEBUG(D_ROUTE)
				printf(" af same, args to iso_eqtype:\n");
				printf("0x%x ", IFA_SIS(ifa)->siso_addr);
				printf(" 0x%x\n",
				&(((struct sockaddr_iso *)addr)->siso_addr));
			ENDDEBUG

			if (iso_eqtype(&(IFA_SIS(ifa)->siso_addr), 
				&(((struct sockaddr_iso *)addr)->siso_addr))) {
				IFDEBUG(D_ROUTE)
					printf("ifa_ifwithidi: ifa found\n");
				ENDDEBUG
				return (ifa);
			}
			IFDEBUG(D_ROUTE)
				printf(" iso_eqtype failed\n");
			ENDDEBUG
		}
	}
	return ((struct ifaddr *)0);
}

I 2
D 23
#endif notdef
E 23
I 23
#endif /* notdef */
E 23
E 2
/*
D 2
 * FUNCTION:		iso_ifinit
 *
 * PURPOSE:			Initialize an interface's iso address and
 *					routing table entry.
 *
 * RETURNS:			unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
iso_ifinit(ifp, ia, siso)
register struct ifnet		*ifp;	/* interface to initialize */
register struct iso_ifaddr	*ia;	/* addr on ifnet list */
struct sockaddr_iso			*siso;	/* address to use */
{
	struct sockaddr oldaddr;
	struct sockaddr_iso netaddr;
	int s = splimp(), error;

	/*
	 *	Make sure the address make sense
	 */
	if (!iso_ck_addr(&siso->siso_addr))
		return(EINVAL);
	IFDEBUG(D_ROUTE)
		int i;
		char *ptr;

		ptr = (char *) siso;
		printf("The size of sockaddr_iso is %d\n", 
			sizeof(struct sockaddr_iso));
		for(i=0; i< sizeof(struct sockaddr_iso); i++) {
			printf("sockaddr[%d] = 0x%x\n", i, *ptr++ & 0xff);
		}
	ENDDEBUG

	oldaddr = ia->ia_addr;
	ia->ia_addr = *(struct sockaddr *)siso;
	bzero((caddr_t)&netaddr, sizeof (netaddr));
	netaddr.siso_family = AF_ISO;

	/*
	 * Give the interface a chance to initialize
	 */
	if (ifp->if_ioctl && (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ia))) {
		splx(s);
		ia->ia_addr = oldaddr;
		return (error);
	}
	splx(s);

	/*
	 * Add route for the network.
	 */
	if (ifp->if_flags & IFF_LOOPBACK)
		rtinit(&ia->ia_addr, &ia->ia_addr, (int)SIOCADDRT, RTF_HOST|RTF_UP);
	else {
		int len;

		len = iso_netof(&siso->siso_addr, (caddr_t)&netaddr.siso_addr);
		netaddr.siso_addr.isoa_len = len;
		rtinit((struct sockaddr *)&netaddr, &ia->ia_addr,
		    (int)SIOCADDRT, RTF_UP);
	}
	ia->ia_flags |= IFA_ROUTE;
	return (0);
}


/*
 * FUNCTION:		iso_ifdelete
 *
 * PURPOSE:			Delete an iso address from an interface.
 *
 * RETURNS:			0 or unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
iso_ifdelete(ifp, siso)
struct ifnet		*ifp;	/* interface to delete addr from */
struct sockaddr_iso	*siso;	/* address to delete */
{
	struct iso_addr 			*isoa = &siso->siso_addr;
	register struct iso_ifaddr	*ia, *prev = 0;
	register struct ifaddr		*ifa;
	int 						s;
	struct sockaddr_iso 		netaddr;

	/* 
	 *	Find the iso address of same type as specified and delete it.
	 */
	for (ia = iso_ifaddr; ia; prev = ia, ia = ia->ia_next) {
		if (ia->ia_ifp == ifp) {
			if (iso_eqtype(&IA_SIS(ia)->siso_addr, isoa)) {
				/*
				 * Delete any previous route for the address.
				 */
				IFDEBUG(D_IOCTL)
					printf("iso_ifdelete: delete %s\n", clnp_iso_addrp(isoa))
				ENDDEBUG
				s = splimp();
				bzero((caddr_t)&netaddr, sizeof (netaddr));
				netaddr.siso_family = AF_ISO;
				if (ia->ia_flags & IFA_ROUTE) {
					if (ifp->if_flags & IFF_LOOPBACK)
						rtinit(&ia->ia_addr, &ia->ia_addr, (int)SIOCDELRT, 
							RTF_HOST);
					else {
						(void) iso_netof(&siso->siso_addr, 
							(caddr_t)&netaddr.siso_addr);
						rtinit((struct sockaddr *)&netaddr, &ia->ia_addr, 
							(int)SIOCDELRT, 0);
					}
					ia->ia_flags &= ~IFA_ROUTE;
				}
				splx(s);

				/*
				 *	Remove from list of iso addresses
				 */
				if (prev == 0)
					iso_ifaddr = ia->ia_next;
				else
					prev->ia_next = ia->ia_next;
				if (ifp != &loif)
					iso_interfaces--;
				
				/*
				 *	Remove from list of addrs on ifnet structure
				 */
				if ((ifa = ifp->if_addrlist) == (struct ifaddr *)ia)
					ifp->if_addrlist = ia->ia_ifa.ifa_next;
				else {
					for (; ifa; ifa = ifa->ifa_next) {
						if (ifa->ifa_next == (struct ifaddr *)ia) {
							ifa->ifa_next = ia->ia_ifa.ifa_next;
							break;
						}
					}
				}

				/*
				 *	Free the iso_ifaddr mbuf
				 */
				m_free(dtom(ia));
				return (0);
			}
		}
	}
	return(EADDRNOTAVAIL);
}

/*
E 2
 * FUNCTION:		iso_ck_addr
 *
 * PURPOSE:			return true if the iso_addr passed is 
 *					within the legal size limit for an iso address.
 *
 * RETURNS:			true or false
 *
 * SIDE EFFECTS:	
 *
 */
iso_ck_addr(isoa)
struct iso_addr	*isoa;	/* address to check */
{
	return (isoa->isoa_len <= 20);

}

D 2

E 2
I 2
#ifdef notdef
E 2
/*
 * FUNCTION:		iso_eqtype
 *
 * PURPOSE:			Determine if two iso addresses are of the same type.
 *  This is flaky.  Really we should consider all type 47 addrs to be the
 *  same - but there do exist different structures for 47 addrs.
 *  Gosip adds a 3rd.
 *
 * RETURNS:			true if the addresses are the same type
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			By type, I mean rfc986, t37, or osinet
 *
 *					This will first compare afis. If they match, then
 *					if the addr is not t37, the idis must be compared.
 */
iso_eqtype(isoaa, isoab)
struct iso_addr	*isoaa;		/* first addr to check */
struct iso_addr	*isoab;		/* other addr to check */
{
	if (isoaa->isoa_afi == isoab->isoa_afi) {
		if (isoaa->isoa_afi == AFI_37)
			return(1);
		else 
			return (!bcmp(&isoaa->isoa_u, &isoab->isoa_u, 2));
	}
	return(0);
}
D 2

E 2
I 2
D 23
#endif notdef
E 23
I 23
#endif /* notdef */
E 23
E 2
/*
D 2
 * FUNCTION:		iso_iaonnetof()
E 2
I 2
 * FUNCTION:		iso_localifa()
E 2
 *
D 2
 * PURPOSE:			Find and interface addresss based on the network
 *					portion of an address.
E 2
I 2
 * PURPOSE:			Find an interface addresss having a given destination
 *					or at least matching the net.
E 2
 *
 * RETURNS:			ptr to an interface address 
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
struct iso_ifaddr *
D 2
iso_iaonnetof(siso)
	struct sockaddr_iso *siso;
E 2
I 2
iso_localifa(siso)
	register struct sockaddr_iso *siso;
E 2
{
	register struct iso_ifaddr *ia;
D 2

	for (ia = iso_ifaddr; ia; ia = ia->ia_next)
		if (iso_netmatch( (struct sockaddr_iso *)(&ia->ia_ifa.ifa_addr), siso) )
			return (ia);
	return ((struct iso_ifaddr *)0);
E 2
I 2
	register char *cp1, *cp2, *cp3;
	register struct ifnet *ifp;
	struct iso_ifaddr *ia_maybe = 0;
	/*
	 * We make one pass looking for both net matches and an exact
	 * dst addr.
	 */
	for (ia = iso_ifaddr; ia; ia = ia->ia_next) {
		if ((ifp = ia->ia_ifp) == 0 || ((ifp->if_flags & IFF_UP) == 0))
			continue;
		if (ifp->if_flags & IFF_POINTOPOINT) {
			if ((ia->ia_dstaddr.siso_family == AF_ISO) &&
				SAME_ISOADDR(&ia->ia_dstaddr, siso))
				return (ia);
			else
				if (SAME_ISOADDR(&ia->ia_addr, siso))
					ia_maybe = ia;
			continue;
		}
		if (ia->ia_sockmask.siso_len) {
			char *cplim = ia->ia_sockmask.siso_len + (char *)&ia->ia_sockmask;
			cp1 = ia->ia_sockmask.siso_data;
			cp2 = siso->siso_data;
			cp3 = ia->ia_addr.siso_data;
D 7
			while (cp2 < cplim)
E 7
I 7
			while (cp1 < cplim)
E 7
				if (*cp1++ & (*cp2++ ^ *cp3++))
					goto next;
			ia_maybe = ia;
		}
		if (SAME_ISOADDR(&ia->ia_addr, siso))
			return ia;
	next:;
	}
	return ia_maybe;
E 2
}

D 11
#ifdef	NARGOXTWENTYFIVE > 0
E 11
I 11
#ifdef	TPCONS
E 11
D 20
#include "cons.h"
E 20
I 20
#include <netiso/cons.h>
E 20
D 11
#endif	NARGOXTWENTYFIVE > 0
E 11
I 11
D 23
#endif	TPCONS
E 23
I 23
#endif	/* TPCONS */
E 23
E 11
/*
 * FUNCTION:		iso_nlctloutput
 *
 * PURPOSE:			Set options at the network level
 *
 * RETURNS:			E*
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			This could embody some of the functions of
 *					rclnp_ctloutput and cons_ctloutput.
 */
iso_nlctloutput(cmd, optname, pcb, m)
int			cmd;		/* command:set or get */
int			optname;	/* option of interest */
caddr_t		pcb;		/* nl pcb */
struct mbuf	*m;			/* data for set, buffer for get */
{
	struct isopcb	*isop = (struct isopcb *)pcb;
	int				error = 0;	/* return value */
	caddr_t			data;		/* data for option */
	int				data_len;	/* data's length */

	IFDEBUG(D_ISO)
		printf("iso_nlctloutput: cmd %x, opt %x, pcb %x, m %x\n",
			cmd, optname, pcb, m);
	ENDDEBUG

	if ((cmd != PRCO_GETOPT) && (cmd != PRCO_SETOPT))
		return(EOPNOTSUPP);

	data = mtod(m, caddr_t);
	data_len = (m)->m_len;

	IFDEBUG(D_ISO)
		printf("iso_nlctloutput: data is:\n");
		dump_buf(data, data_len);
	ENDDEBUG

	switch (optname) {

D 11
#ifdef	NARGOXTWENTYFIVE > 0
E 11
I 11
#ifdef	TPCONS
E 11
		case CONSOPT_X25CRUD:
			if (cmd == PRCO_GETOPT) {
				error = EOPNOTSUPP;
				break;
			}

			if (data_len > MAXX25CRUDLEN) {
				error = EINVAL;
				break;
			}

			IFDEBUG(D_ISO)
				printf("iso_nlctloutput: setting x25 crud\n");
			ENDDEBUG

D 2
			bcopy(data, (caddr_t)&isop->isop_x25crud, data_len);
E 2
I 2
			bcopy(data, (caddr_t)isop->isop_x25crud, (unsigned)data_len);
E 2
			isop->isop_x25crud_len = data_len;
			break;
D 11
#endif	NARGOXTWENTYFIVE > 0
E 11
I 11
D 23
#endif	TPCONS
E 23
I 23
#endif	/* TPCONS */
E 23
E 11

		default:
			error = EOPNOTSUPP;
	}
D 16

E 16
I 16
	if (cmd == PRCO_SETOPT)
		m_freem(m);
E 16
	return error;
}
D 6

/*
 * FUNCTION:		iso_routeifp
 *
 * PURPOSE:			Route on a sockaddr and return ifp
 *
 * RETURNS:			ifp of outgoing interface, or null
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
D 2
struct ifnet *
iso_routeifp(dst)
E 2
I 2
struct iso_ifaddr *
iso_routeifa(dst)
E 2
struct sockaddr	*dst;		/* destination to route to */
{
D 2
	struct route	ro;
	struct ifnet	*ifp = NULL;
E 2
I 2
	struct rtentry	*rt;
	struct ifaddr *ifa = 0;
	struct ifnet *ifp = 0;
E 2

D 2
	ro.ro_dst = *dst;
	ro.ro_rt = NULL;
E 2

	IFDEBUG(D_ROUTE)
		printf("iso_routeifp: dst:");
D 2
		dump_isoaddr(dst);
E 2
I 2
		dump_isoaddr((struct sockaddr_iso *)dst);
E 2
	ENDDEBUG

D 2
	rtalloc(&ro);
E 2
I 2
	rt = rtalloc1(dst, 0);
E 2

D 2
	if (ro.ro_rt) {
		ifp = ro.ro_rt->rt_ifp;
		RTFREE(ro.ro_rt);
E 2
I 2
	if (rt) {
		ifa = rt->rt_ifa;
		ifp = rt->rt_ifp;
		RTFREE(rt);
E 2
	}

	IFDEBUG(D_ROUTE)
D 2
		printf("iso_routeifp: ifp x%x", ifp);
E 2
I 2
		printf("iso_routeifp: ifa x%x", ifa);
E 2
		if (ifp)
			printf(" (%s%d)\n", ifp->if_name, ifp->if_unit);
		else
			printf("\n");
	ENDDEBUG

D 2
	return(ifp);
E 2
I 2
	return((struct iso_ifaddr *)ifa);
E 2
}
E 6
D 23
#endif ISO
E 23
I 23
#endif /* ISO */
E 23

#ifdef ARGO_DEBUG

/*
 * FUNCTION:		dump_isoaddr
 *
 * PURPOSE:			debugging
 *
 * RETURNS:			nada 
 *
 */
dump_isoaddr(s)
	struct sockaddr_iso *s;
{
D 2
	caddr_t c = (caddr_t)&(s->siso_addr.isoa_u);
E 2
I 2
	char *clnp_saddr_isop();
E 2
	register int i;

	if( s->siso_family == AF_ISO) {
D 2
		printf("len %d family: 0x%x  suffix 0x%x, afi 0x%x,",
			(int)s->siso_addr.isoa_len,
			(int)s->siso_family, 
			s->siso_tsuffix, (int)s->siso_addr.isoa_afi);
		if( s->siso_addr.isoa_len > sizeof(struct sockaddr) )
			printf("ERROR-ADDR TOO BIG %d\n", s->siso_addr.isoa_len);
		else  {
			if (s->siso_addr.isoa_len != 0) {
			/* -2 because we already skipped the afi */
					for (i=0; i<s->siso_addr.isoa_len-2; i++)
						printf("0x%x.", *(c+i)&0xff);
					printf("0x%x\n", *(c+i)&0xff);
			}
		}
E 2
I 2
		printf("ISO address: suffixlen %d, %s\n",
D 5
			s->siso_tsuffixlen, clnp_saddr_isop(s));
E 5
I 5
			s->siso_tlen, clnp_saddr_isop(s));
E 5
E 2
	} else if( s->siso_family == AF_INET) {
		/* hack */
		struct sockaddr_in *sin = (struct sockaddr_in *)s;

		printf("%d.%d.%d.%d: %d", 
			(sin->sin_addr.s_addr>>24)&0xff,
			(sin->sin_addr.s_addr>>16)&0xff,
			(sin->sin_addr.s_addr>>8)&0xff,
			(sin->sin_addr.s_addr)&0xff,
			sin->sin_port);
	}
}

D 23
#endif ARGO_DEBUG
E 23
I 23
#endif /* ARGO_DEBUG */
E 23
E 1
