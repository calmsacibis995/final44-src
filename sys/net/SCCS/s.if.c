h27015
s 00001/00001/00644
d D 8.5 95/01/09 17:54:18 cgd 84 83
c 64-bit changes: casts, and ioctl cmds are u_longs
e
s 00002/00001/00643
d D 8.4 94/07/01 12:56:09 sklower 83 82
c bugfix from karels & husemann in ifwithdstaddr()
e
s 00001/00001/00643
d D 8.3 94/01/04 21:46:16 bostic 82 81
c lint
e
s 00000/00001/00644
d D 8.2 93/11/16 14:13:12 mckusick 81 80
c af.h is gone
e
s 00002/00002/00643
d D 8.1 93/06/29 14:58:42 bostic 80 79
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00642
d D 7.28 93/06/29 14:57:59 mckusick 79 77
c don't read past end of string if_name
e
s 00002/00002/00642
d R 8.1 93/06/10 22:44:28 bostic 78 77
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00016/00634
d D 7.27 93/06/04 17:30:36 bostic 77 76
c prototype everything
e
s 00001/00001/00649
d D 7.26 93/05/24 23:46:19 torek 76 75
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00002/00000/00648
d D 7.25 93/04/13 16:24:35 sklower 75 74
c potential bug in reference counting ifaddrs
e
s 00000/00002/00648
d D 7.24 93/02/25 16:45:46 sklower 74 73
c multicast is now standard
e
s 00001/00001/00649
d D 7.23 93/02/17 06:16:26 torek 73 72
c ADD/DEL MULTI should fail EOPNOTSUPP only if cannot, not only if can
c (bug report net2/sys/21)
e
s 00016/00014/00634
d D 7.22 92/10/11 11:48:55 bostic 72 71
c make kernel includes standard
e
s 00006/00003/00642
d D 7.21 92/07/07 18:38:59 torek 71 70
c lint
e
s 00013/00002/00632
d D 7.20 92/07/06 15:28:43 sklower 70 69
c multicast changes from lbl
e
s 00013/00012/00621
d D 7.19 92/05/12 16:48:06 sklower 69 68
c changes suggested by jch to ifa_ifwithnet()
e
s 00001/00001/00632
d D 7.18 92/03/11 21:39:50 torek 68 67
c gcc lint
e
s 00054/00031/00579
d D 7.17 92/02/18 15:40:44 sklower 67 66
c generate routing messages for interface state changes;
c move ethernet specific stuff to if_ethersubr.c
e
s 00001/00001/00609
d D 7.16 92/02/15 17:44:50 mckusick 66 65
c must include proc.h before socketvar.h
e
s 00004/00002/00606
d D 7.15 92/01/29 19:30:09 torek 65 64
c lint and formatting changes, checked in by KLS
e
s 00025/00025/00583
d D 7.14 91/04/20 16:35:28 karels 64 63
c new proc structure; rm user.h; pass proc to ifioctl; rework sprint_d
e
s 00001/00011/00607
d D 7.13 90/06/28 21:30:08 bostic 63 62
c new copyright notice
e
s 00074/00012/00544
d D 7.12 90/06/20 19:05:03 sklower 62 61
c changes designed so that ESIS and ARP may use routing table
c instead of private cache; allow RTM_CHANGE to specify new ifp.
e
s 00033/00004/00523
d D 7.11 90/05/14 15:53:59 sklower 61 60
c when adding a link level route from outside the kernel,
c insure that rt_ifa points to something in the same AF for use when connecting.
c (should eventually move to route.c)
e
s 00001/00001/00526
d D 7.10 90/05/10 16:20:35 mckusick 60 57
c lint
e
s 00033/00004/00523
d R 7.10 90/05/01 18:20:22 sklower 59 57
c when adding a link level route from outside the kernel,
c insure that rt_ifa points to something in the same AF for use when connecting.
e
s 00031/00003/00524
d R 7.10 90/05/01 18:09:56 sklower 58 57
c when adding a link level route from outside the kernel,
c insure that rt_ifa points to something in the same AF for use when connecting.
e
s 00057/00000/00470
d D 7.9 90/04/05 11:46:02 sklower 57 56
c add if_index (little) and generate AF_LINK sockaddr when attaching (big change).
e
s 00000/00001/00470
d D 7.8 89/05/05 00:24:08 mckusick 56 55
c get rid of unnedded include of dir.h
e
s 00007/00006/00464
d D 7.7 89/04/26 18:56:14 mckusick 55 53
c use new form of suser()
e
s 00000/00000/00380
d D 7.6.1.1 89/02/17 10:36:35 karels 54 53
x 52
c branch for net release, apply 7.6 to 7.4
e
s 00015/00002/00455
d D 7.6 89/02/17 10:34:35 karels 53 52
c fix if name recognition: initial (pos. null) prefix != name, allow > 1 digit
e
s 00109/00019/00348
d D 7.5 88/12/21 14:05:39 sklower 52 51
c checkpoint working version with variable size sockaddr changes
e
s 00010/00005/00357
d D 7.4 88/06/27 18:59:28 bostic 51 50
c install approved copyright notice
e
s 00020/00000/00342
d D 7.3 88/04/07 17:23:42 karels 50 49
c add if_qflush
e
s 00008/00002/00334
d D 7.2 87/12/30 11:57:23 bostic 49 48
c add Berkeley header
e
s 00001/00001/00335
d D 7.1 86/06/04 23:39:06 mckusick 48 47
c 4.3BSD release version
e
s 00002/00000/00334
d D 6.13 86/06/02 14:27:02 karels 47 46
c rm unused (for lint)
e
s 00010/00000/00324
d D 6.12 86/02/06 14:18:11 karels 46 45
c add LOOPBACK flag, interface metric
e
s 00001/00001/00323
d D 6.11 85/12/19 16:12:47 karels 45 44
c rm bbnnet; rm PUP
e
s 00002/00000/00322
d D 6.10 85/12/06 10:39:29 bloom 44 43
c can't let users take interfaces up and down
e
s 00006/00007/00316
d D 6.9 85/09/16 21:11:04 karels 43 42
c ctlinput takes a sockaddr; ifinit doesn't need to call per-if init yet;
c call if's ioctl when changing flags, so can notice down transition
e
s 00021/00000/00302
d D 6.8 85/07/18 22:34:14 sklower 42 41
c Changes to allow multiple pt to pt links to have the same local address.
e
s 00007/00001/00295
d D 6.7 85/06/08 12:25:59 mckusick 41 40
c Add copyright
e
s 00055/00066/00241
d D 6.6 85/04/01 13:49:51 karels 40 38
c move net addresses from interface layer into protocols;
c ifioctl calls proto PRU_CONTROL with addresses, etc.;
c watch out for magic bits in interface flags
e
s 00059/00053/00254
d R 6.6 85/03/19 15:58:59 karels 39 38
c move net addresses from interface layer into protocols;
c ifioctl calls proto PRU_CONTROL with addresses, etc.;
c watch out for magic bits in interface flags
e
s 00011/00011/00296
d D 6.5 84/08/28 17:38:54 bloom 38 35
c fix header includes.  no more ../h
e
s 00009/00009/00298
d R 6.5 84/08/28 17:13:17 bloom 37 35
c Change include paths.  No more ../h.
e
s 00006/00000/00307
d R 6.5 84/04/13 10:34:28 karels 36 35
c add ioctl to determine if broadcast address (for subnets)
e
s 00012/00000/00295
d D 6.4 84/03/22 15:10:16 karels 35 33
c new ioctls for ARP
e
s 00008/00000/00295
d R 6.4 84/03/20 15:23:11 karels 34 33
c new ARP
e
s 00001/00001/00294
d D 6.3 84/03/09 11:31:18 karels 33 32
c don't clobber unit number in ifreq on SIOCGIFxxx.
e
s 00001/00001/00294
d D 6.2 83/09/27 21:33:46 sam 32 31
c missing parameter to reset routines
e
s 00000/00000/00295
d D 6.1 83/07/29 07:08:33 sam 31 30
c 4.2 distribution
e
s 00010/00001/00285
d D 4.30 83/06/12 23:09:27 sam 30 29
c more parts to the ioctls
e
s 00046/00046/00240
d D 4.29 83/06/12 19:47:16 sam 29 28
c revamp network ioctls; add IFF_NOTRAILERS
e
s 00003/00001/00283
d D 4.28 83/05/27 13:56:29 sam 28 27
c lint and wnj changes
e
s 00009/00008/00275
d D 4.27 83/03/19 18:02:29 sam 27 26
c leave buffer pointer unchanged; null terminate interface names
e
s 00111/00000/00172
d D 4.26 83/03/15 18:24:28 sam 26 25
c socket ioctls
e
s 00003/00000/00169
d D 4.25 83/02/10 18:45:30 sam 25 24
c hz not in systm.h anymore
e
s 00006/00008/00163
d D 4.24 82/11/13 23:10:36 sam 24 23
c merge 4.1b and 4.1c
e
s 00002/00002/00169
d D 4.23 82/10/31 14:59:00 root 23 22
c s/ubareset/reset/
e
s 00001/00001/00170
d D 4.22 82/10/20 01:18:48 root 22 21
c lint
e
s 00000/00000/00171
d D 4.21 82/10/17 22:16:19 root 21 20
c lint
e
s 00003/00003/00168
d D 4.20 82/10/09 05:40:02 wnj 20 19
c header file dependencies fixed up and untested changes to raw interface
e
s 00003/00000/00168
d D 4.19 82/09/12 03:22:53 root 19 18
c if_slowtimo timeout driven
e
s 00020/00000/00148
d D 4.18 82/06/23 21:10:00 sam 18 17
c added watchdog routines
e
s 00000/00002/00148
d D 4.17 82/06/20 00:51:38 sam 17 16
c purge COUNT stuff now that we can use gprof
e
s 00000/00041/00150
d D 4.16 82/06/13 22:59:42 sam 16 15
c add class a/b/c net #'s and purge logical host kludge code
e
s 00004/00001/00187
d D 4.15 82/05/04 20:26:33 sam 15 14
c bounds check on afswitch array
e
s 00012/00000/00176
d D 4.14 82/04/24 20:37:37 sam 14 13
c icmp and ctlinput working -- missing protocol specific ctlinput's
e
s 00001/00001/00175
d D 4.13 82/03/30 19:57:17 sam 13 12
c routing code now operational
e
s 00019/00000/00157
d D 4.12 82/03/30 11:31:13 sam 12 11
c with routing, but not forwarding
e
s 00073/00018/00084
d D 4.11 82/03/28 14:20:46 sam 11 10
c convert interfaces to sockaddr's and add hooks for routing
e
s 00006/00001/00096
d D 4.10 82/03/15 04:43:05 wnj 10 9
c interfac queueing, restrictions on packets, tcp keep alives done 
c properly, bug fix to raw
e
s 00003/00001/00094
d D 4.9 82/03/09 17:39:23 root 9 8
c handle broadcast packets
e
s 00004/00002/00091
d D 4.8 82/02/03 20:07:17 wnj 8 7
c if_attach now puts interfaces on the end of the q
e
s 00002/00000/00091
d D 4.7 82/02/03 10:43:44 sam 7 6
c explicit vax dependecy indicated
e
s 00022/00003/00069
d D 4.6 81/12/07 21:55:10 wnj 6 5
c added routines and bug fixes
e
s 00009/00000/00063
d D 4.5 81/12/02 16:57:51 wnj 5 4
c yet more lint
e
s 00017/00000/00046
d D 4.4 81/11/29 21:58:23 wnj 4 3
c lint and interface cleanups
e
s 00011/00013/00035
d D 4.3 81/11/26 11:55:45 wnj 3 2
c before carry to ARPAVAX
e
s 00007/00001/00041
d D 4.2 81/11/20 00:46:28 wnj 2 1
c linted
e
s 00042/00000/00000
d D 4.1 81/11/18 16:51:49 wnj 1 0
c date and time created 81/11/18 16:51:49 by wnj
e
u
U
f b 
t
T
I 1
D 41
/*	%M%	%I%	%E%	*/
E 41
I 41
/*
D 48
 * Copyright (c) 1980 Regents of the University of California.
E 48
I 48
D 80
 * Copyright (c) 1980, 1986 Regents of the University of California.
E 48
D 49
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 49
I 49
 * All rights reserved.
E 80
I 80
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 80
 *
D 63
 * Redistribution and use in source and binary forms are permitted
D 51
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 51
I 51
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 63
I 63
 * %sccs.include.redist.c%
E 63
E 51
E 49
 *
 *	%W% (Berkeley) %G%
 */
E 41

D 38
#include "../h/param.h"
#include "../h/systm.h"
I 11
#include "../h/socket.h"
I 14
#include "../h/protosw.h"
I 25
D 29
#include "../h/time.h"
E 29
I 29
#include "../h/dir.h"
#include "../h/user.h"
E 29
#include "../h/kernel.h"
I 26
#include "../h/ioctl.h"
#include "../h/errno.h"
E 38
I 38
D 72
#include "param.h"
I 50
#include "mbuf.h"
E 50
#include "systm.h"
I 66
#include "proc.h"
E 66
#include "socket.h"
I 40
#include "socketvar.h"
E 40
#include "protosw.h"
D 56
#include "dir.h"
E 56
D 64
#include "user.h"
E 64
I 64
D 66
#include "proc.h"
E 66
E 64
#include "kernel.h"
#include "ioctl.h"
E 72
I 72
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/kernel.h>
#include <sys/ioctl.h>
E 72
D 64
#include "errno.h"
E 64
E 38
E 26

E 25
E 14
E 11
D 3
#include "../net/inet.h"
#include "../net/inet_systm.h"
E 3
I 3
D 20
#include "../net/in.h"
#include "../net/in_systm.h"
E 20
E 3
D 38
#include "../net/if.h"
I 11
#include "../net/af.h"
E 38
I 38
D 72
#include "if.h"
#include "af.h"
I 57
#include "if_dl.h"
I 62
#include "if_types.h"
E 72
I 72
#include <net/if.h>
D 81
#include <net/af.h>
E 81
#include <net/if_dl.h>
#include <net/if_types.h>
E 72
E 62
E 57
E 38
E 11

I 35
D 77
#include "ether.h"

E 77
E 35
I 10
int	ifqmaxlen = IFQ_MAXLEN;
I 71
void	if_slowtimo __P((void *arg));
E 71

I 11
/*
 * Network interface utility routines.
 *
D 40
 * Routines with if_ifwith* names take sockaddr *'s as
 * parameters.  Other routines take value parameters,
 * e.g. if_ifwithnet takes the network number.
E 40
I 40
 * Routines with ifa_ifwith* names take sockaddr *'s as
 * parameters.
E 40
 */
D 77

E 77
I 77
void
E 77
E 11
E 10
I 6
ifinit()
{
	register struct ifnet *ifp;

	for (ifp = ifnet; ifp; ifp = ifp->if_next)
D 10
		if (ifp->if_init)
E 10
I 10
D 43
		if (ifp->if_init) {
E 10
D 11
			(*ifp->if_init)();
E 11
I 11
			(*ifp->if_init)(ifp->if_unit);
E 11
I 10
			if (ifp->if_snd.ifq_maxlen == 0)
				ifp->if_snd.ifq_maxlen = ifqmaxlen;
		}
E 43
I 43
		if (ifp->if_snd.ifq_maxlen == 0)
			ifp->if_snd.ifq_maxlen = ifqmaxlen;
E 43
I 19
D 71
	if_slowtimo();
E 71
I 71
	if_slowtimo(0);
E 71
E 19
E 10
}

I 20
D 29
#if vax
E 29
I 29
#ifdef vax
E 29
E 20
I 11
/*
 * Call each interface on a Unibus reset.
 */
I 77
void
E 77
E 11
ifubareset(uban)
	int uban;
{
	register struct ifnet *ifp;

	for (ifp = ifnet; ifp; ifp = ifp->if_next)
D 23
		if (ifp->if_ubareset)
			(*ifp->if_ubareset)(uban);
E 23
I 23
		if (ifp->if_reset)
D 32
			(*ifp->if_reset)(uban);
E 32
I 32
			(*ifp->if_reset)(ifp->if_unit, uban);
E 32
E 23
}
I 20
#endif
E 20

I 57
int if_index = 0;
I 62
struct ifaddr **ifnet_addrs;
I 64
D 77
static char *sprint_d();
E 77
I 77
static char *sprint_d __P((u_int, char *, int));
E 77

E 64
E 62
E 57
I 11
/*
 * Attach an interface to the
 * list of "active" interfaces.
 */
I 65
void
E 65
E 11
E 6
I 5
if_attach(ifp)
	struct ifnet *ifp;
{
I 8
D 62
	register struct ifnet **p = &ifnet;
E 62
I 57
	unsigned socksize, ifasize;
D 67
	int namelen, unitlen;
E 67
I 67
D 70
	int namelen, unitlen, masklen;
E 70
I 70
	int namelen, unitlen, masklen, ether_output();
E 70
E 67
D 64
	char workbuf[16];
E 64
I 64
	char workbuf[12], *unitname;
E 64
I 62
	register struct ifnet **p = &ifnet;
E 62
	register struct sockaddr_dl *sdl;
	register struct ifaddr *ifa;
I 61
D 62
	extern link_rtrequest();
E 62
I 62
	static int if_indexlim = 8;
D 70
	extern link_rtrequest(), ether_output();
E 70
I 70
	extern void link_rtrequest();
E 70
E 62
E 61
E 57
E 8

D 17
COUNT(IF_ATTACH);
E 17
D 8
	ifp->if_next = ifnet;
	ifnet = ifp;
E 8
I 8
	while (*p)
		p = &((*p)->if_next);
	*p = ifp;
I 57
	ifp->if_index = ++if_index;
I 62
	if (ifnet_addrs == 0 || if_index >= if_indexlim) {
		unsigned n = (if_indexlim <<= 1) * sizeof(ifa);
		struct ifaddr **q = (struct ifaddr **)
					malloc(n, M_IFADDR, M_WAITOK);
		if (ifnet_addrs) {
			bcopy((caddr_t)ifnet_addrs, (caddr_t)q, n/2);
			free((caddr_t)ifnet_addrs, M_IFADDR);
		}
		ifnet_addrs = q;
	}
D 67
	/* XXX -- Temporary fix before changing 10 ethernet drivers */
	if (ifp->if_output == ether_output) {
		ifp->if_type = IFT_ETHER;
		ifp->if_addrlen = 6;
		ifp->if_hdrlen = 14;
	}
E 67
E 62
D 61
	/* create a link level name for this device */
E 61
I 61
	/*
	 * create a Link Level name for this device
	 */
E 61
D 64
	sprint_d(workbuf, ifp->if_unit);
E 64
I 64
	unitname = sprint_d((u_int)ifp->if_unit, workbuf, sizeof(workbuf));
E 64
	namelen = strlen(ifp->if_name);
D 64
	unitlen = strlen(workbuf);
E 64
I 64
	unitlen = strlen(unitname);
E 64
#define _offsetof(t, m) ((int)((caddr_t)&((t *)0)->m))
D 67
	socksize = _offsetof(struct sockaddr_dl, sdl_data[0]) +
			       unitlen + namelen + ifp->if_addrlen;
E 67
I 67
	masklen = _offsetof(struct sockaddr_dl, sdl_data[0]) +
			       unitlen + namelen;
	socksize = masklen + ifp->if_addrlen;
E 67
#define ROUNDUP(a) (1 + (((a) - 1) | (sizeof(long) - 1)))
	socksize = ROUNDUP(socksize);
I 62
	if (socksize < sizeof(*sdl))
		socksize = sizeof(*sdl);
E 62
	ifasize = sizeof(*ifa) + 2 * socksize;
D 67
	ifa = (struct ifaddr *)malloc(ifasize, M_IFADDR, M_WAITOK);
	if (ifa == 0)
		return;
I 62
	ifnet_addrs[if_index - 1] = ifa;
E 62
	bzero((caddr_t)ifa, ifasize);
	sdl = (struct sockaddr_dl *)(ifa + 1);
	ifa->ifa_addr = (struct sockaddr *)sdl;
	ifa->ifa_ifp = ifp;
	sdl->sdl_len = socksize;
	sdl->sdl_family = AF_LINK;
	bcopy(ifp->if_name, sdl->sdl_data, namelen);
D 64
	bcopy((caddr_t)workbuf, namelen + (caddr_t)sdl->sdl_data, unitlen);
E 64
I 64
	bcopy(unitname, namelen + (caddr_t)sdl->sdl_data, unitlen);
E 64
	sdl->sdl_nlen = (namelen += unitlen);
	sdl->sdl_index = ifp->if_index;
	sdl = (struct sockaddr_dl *)(socksize + (caddr_t)sdl);
	ifa->ifa_netmask = (struct sockaddr *)sdl;
	sdl->sdl_len = socksize - ifp->if_addrlen;
	while (namelen != 0)
		sdl->sdl_data[--namelen] = 0xff;
	ifa->ifa_next = ifp->if_addrlist;
I 61
	ifa->ifa_rtrequest = link_rtrequest;
E 61
	ifp->if_addrlist = ifa;
E 67
I 67
	if (ifa = (struct ifaddr *)malloc(ifasize, M_IFADDR, M_WAITOK)) {
		bzero((caddr_t)ifa, ifasize);
		sdl = (struct sockaddr_dl *)(ifa + 1);
		sdl->sdl_len = socksize;
		sdl->sdl_family = AF_LINK;
		bcopy(ifp->if_name, sdl->sdl_data, namelen);
		bcopy(unitname, namelen + (caddr_t)sdl->sdl_data, unitlen);
		sdl->sdl_nlen = (namelen += unitlen);
		sdl->sdl_index = ifp->if_index;
		sdl->sdl_type = ifp->if_type;
		ifnet_addrs[if_index - 1] = ifa;
		ifa->ifa_ifp = ifp;
		ifa->ifa_next = ifp->if_addrlist;
		ifa->ifa_rtrequest = link_rtrequest;
		ifp->if_addrlist = ifa;
		ifa->ifa_addr = (struct sockaddr *)sdl;
		sdl = (struct sockaddr_dl *)(socksize + (caddr_t)sdl);
		ifa->ifa_netmask = (struct sockaddr *)sdl;
		sdl->sdl_len = masklen;
		while (namelen != 0)
			sdl->sdl_data[--namelen] = 0xff;
	}
	/* XXX -- Temporary fix before changing 10 ethernet drivers */
	if (ifp->if_output == ether_output)
		ether_ifattach(ifp);
E 67
E 57
E 8
}
D 61

E 61
I 11
/*
 * Locate an interface based on a complete address.
 */
E 11
E 5
I 2
/*ARGSUSED*/
D 40
struct ifnet *
E 2
D 11
if_ifwithaddr(in)
	struct in_addr in;
E 11
I 11
if_ifwithaddr(addr)
E 40
I 40
struct ifaddr *
ifa_ifwithaddr(addr)
E 40
D 52
	struct sockaddr *addr;
E 52
I 52
	register struct sockaddr *addr;
E 52
E 11
{
	register struct ifnet *ifp;
I 40
	register struct ifaddr *ifa;
E 40

I 2
D 17
COUNT(IF_IFWITHADDR);
E 17
E 2
D 3
#if 0
E 3
D 11
	for (ifp = ifnet; ifp; ifp = ifp->if_next)
D 9
		if (ifp->if_addr.s_addr == in.s_addr)
E 9
I 9
		if (in.s_addr == ifp->if_addr.s_addr ||
		    (ifp->if_broadaddr.s_addr != 0 &&
		     in.s_addr == ifp->if_broadaddr.s_addr))
E 11
I 11
#define	equal(a1, a2) \
D 52
	(bcmp((caddr_t)((a1)->sa_data), (caddr_t)((a2)->sa_data), 14) == 0)
E 52
I 52
  (bcmp((caddr_t)(a1), (caddr_t)(a2), ((struct sockaddr *)(a1))->sa_len) == 0)
E 52
D 40
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		if (ifp->if_addr.sa_family != addr->sa_family)
E 40
I 40
	for (ifp = ifnet; ifp; ifp = ifp->if_next)
	    for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next) {
D 52
		if (ifa->ifa_addr.sa_family != addr->sa_family)
E 52
I 52
		if (ifa->ifa_addr->sa_family != addr->sa_family)
E 52
E 40
			continue;
D 40
		if (equal(&ifp->if_addr, addr))
E 11
E 9
			break;
E 40
I 40
D 52
		if (equal(&ifa->ifa_addr, addr))
E 52
I 52
		if (equal(addr, ifa->ifa_addr))
E 52
			return (ifa);
E 40
I 11
D 62
		if ((ifp->if_flags & IFF_BROADCAST) &&
D 40
		    equal(&ifp->if_broadaddr, addr))
			break;
E 40
I 40
		    equal(&ifa->ifa_broadaddr, addr))
E 62
I 62
		if ((ifp->if_flags & IFF_BROADCAST) && ifa->ifa_broadaddr &&
		    equal(ifa->ifa_broadaddr, addr))
E 62
			return (ifa);
E 40
	}
E 11
D 3
#else
	ifp = ifnet;
#endif
E 3
D 40
	return (ifp);
E 40
I 40
	return ((struct ifaddr *)0);
E 40
}
I 42
/*
 * Locate the point to point interface with a given destination address.
 */
/*ARGSUSED*/
struct ifaddr *
ifa_ifwithdstaddr(addr)
D 52
	struct sockaddr *addr;
E 52
I 52
	register struct sockaddr *addr;
E 52
{
	register struct ifnet *ifp;
	register struct ifaddr *ifa;

	for (ifp = ifnet; ifp; ifp = ifp->if_next) 
	    if (ifp->if_flags & IFF_POINTOPOINT)
		for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next) {
D 52
			if (ifa->ifa_addr.sa_family != addr->sa_family)
E 52
I 52
D 83
			if (ifa->ifa_addr->sa_family != addr->sa_family)
E 83
I 83
			if (ifa->ifa_addr->sa_family != addr->sa_family ||
			    ifa->ifa_dstaddr == NULL)
E 83
E 52
				continue;
D 52
			if (equal(&ifa->ifa_dstaddr, addr))
E 52
I 52
			if (equal(addr, ifa->ifa_dstaddr))
E 52
				return (ifa);
	}
	return ((struct ifaddr *)0);
}
E 42

I 2
D 11
/*ARGSUSED*/
E 11
I 11
/*
 * Find an interface on a specific network.  If many, choice
D 69
 * is first found.
E 69
I 69
 * is most specific found.
E 69
 */
E 11
D 40
struct ifnet *
E 2
D 11
if_ifonnetof(in)
	struct in_addr in;
E 11
I 11
if_ifwithnet(addr)
E 40
I 40
struct ifaddr *
ifa_ifwithnet(addr)
E 40
D 52
	register struct sockaddr *addr;
E 52
I 52
	struct sockaddr *addr;
E 52
E 11
{
	register struct ifnet *ifp;
I 40
	register struct ifaddr *ifa;
I 69
	struct ifaddr *ifa_maybe = (struct ifaddr *) 0;
E 69
E 40
D 3
#if 0
E 3
D 11
	int net;
E 11
I 11
D 20
	register int af = addr->sa_family;
E 20
I 20
D 52
	register u_int af = addr->sa_family;
E 20
D 15
	register int (*netmatch)() = afswitch[af].af_netmatch;
E 15
I 15
	register int (*netmatch)();
E 52
I 52
D 62
	register char *cp, *cp2, *cp3;
	register char *cplim;
E 62
	u_int af = addr->sa_family;
I 69
	char *addr_data = addr->sa_data, *cplim;
E 69
E 52
E 15
E 11

I 15
D 69
	if (af >= AF_MAX)
		return (0);
E 69
I 62
	if (af == AF_LINK) {
	    register struct sockaddr_dl *sdl = (struct sockaddr_dl *)addr;
	    if (sdl->sdl_index && sdl->sdl_index <= if_index)
		return (ifnet_addrs[sdl->sdl_index - 1]);
	}
E 62
D 52
	netmatch = afswitch[af].af_netmatch;
E 52
E 15
I 2
D 11
COUNT(IF_IFONNETOF);
E 2
D 3
	net = 0;			/* XXX */
E 3
I 3
	net = in.s_net;			/* XXX */
E 11
I 11
D 40
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		if (af != ifp->if_addr.sa_family)
E 40
I 40
	for (ifp = ifnet; ifp; ifp = ifp->if_next)
	    for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next) {
I 62
		register char *cp, *cp2, *cp3;
D 69
		register char *cplim;
E 69
I 69

E 69
E 62
D 52
		if (ifa->ifa_addr.sa_family != addr->sa_family)
E 52
I 52
		if (ifa->ifa_addr->sa_family != af || ifa->ifa_netmask == 0)
E 52
E 40
D 69
			continue;
D 40
		if ((*netmatch)(addr, &ifp->if_addr))
			break;
E 40
I 40
D 52
		if ((*netmatch)(&ifa->ifa_addr, addr))
E 52
I 52
		cp = addr->sa_data;
E 69
I 69
			next: continue;
		cp = addr_data;
E 69
		cp2 = ifa->ifa_addr->sa_data;
		cp3 = ifa->ifa_netmask->sa_data;
		cplim = ifa->ifa_netmask->sa_len + (char *)ifa->ifa_netmask;
D 69
		for (; cp3 < cplim; cp3++)
			if ((*cp++ ^ *cp2++) & *cp3)
				break;
		if (cp3 == cplim)
E 52
			return (ifa);
E 69
I 69
		while (cp3 < cplim)
			if ((*cp++ ^ *cp2++) & *cp3++)
				goto next;
		if (ifa_maybe == 0 ||
D 77
		    rn_refines(ifa->ifa_netmask, ifa_maybe->ifa_netmask))
E 77
I 77
		    rn_refines((caddr_t)ifa->ifa_netmask,
		    (caddr_t)ifa_maybe->ifa_netmask))
E 77
			ifa_maybe = ifa;
E 69
E 40
D 52
	}
E 52
I 52
	    }
E 52
D 40
	return (ifp);
E 40
I 40
D 69
	return ((struct ifaddr *)0);
E 69
I 69
	return (ifa_maybe);
E 69
E 40
}

I 47
D 61
#ifdef notdef
E 61
E 47
/*
D 40
 * As above, but parameter is network number.
 */
struct ifnet *
if_ifonnetof(net)
	register int net;
{
	register struct ifnet *ifp;

E 11
E 3
	for (ifp = ifnet; ifp; ifp = ifp->if_next)
		if (ifp->if_net == net)
			break;
D 3
#else
	ifp = ifnet;
#endif
E 3
	return (ifp);
}

I 4
D 11
/*ARGSUSED*/
E 11
I 11
/*
E 40
 * Find an interface using a specific address family
 */
E 11
E 4
D 2
struct	ifnet ifen = { 0, 0, 1024, 0, 0 };
E 2
I 2
D 3
struct	ifnet ifen;
E 2
struct	ifnet *ifnet = &ifen;
E 3
I 3
D 40
struct ifnet *
D 11
if_gatewayfor(addr)
	struct in_addr addr;
E 11
I 11
if_ifwithaf(af)
E 40
I 40
struct ifaddr *
ifa_ifwithaf(af)
E 40
	register int af;
E 11
{
I 11
	register struct ifnet *ifp;
I 40
	register struct ifaddr *ifa;
E 40
E 11

D 11
COUNT(IF_GATEWAYFOR);
	return (0);
E 11
I 11
	for (ifp = ifnet; ifp; ifp = ifp->if_next)
D 40
		if (ifp->if_addr.sa_family == af)
			break;
	return (ifp);
E 40
I 40
	    for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
D 52
		if (ifa->ifa_addr.sa_family == af)
E 52
I 52
		if (ifa->ifa_addr->sa_family == af)
E 52
			return (ifa);
	return ((struct ifaddr *)0);
E 40
I 14
}
I 47
D 61
#endif
E 61
I 61

I 62
/*
 * Find an interface address specific to an interface best matching
 * a given address.
 */
struct ifaddr *
ifaof_ifpforaddr(addr, ifp)
	struct sockaddr *addr;
	register struct ifnet *ifp;
{
	register struct ifaddr *ifa;
	register char *cp, *cp2, *cp3;
	register char *cplim;
	struct ifaddr *ifa_maybe = 0;
	u_int af = addr->sa_family;

	if (af >= AF_MAX)
		return (0);
	for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr->sa_family != af)
			continue;
		ifa_maybe = ifa;
		if (ifa->ifa_netmask == 0) {
			if (equal(addr, ifa->ifa_addr) ||
			    (ifa->ifa_dstaddr && equal(addr, ifa->ifa_dstaddr)))
				return (ifa);
			continue;
		}
		cp = addr->sa_data;
		cp2 = ifa->ifa_addr->sa_data;
		cp3 = ifa->ifa_netmask->sa_data;
		cplim = ifa->ifa_netmask->sa_len + (char *)ifa->ifa_netmask;
		for (; cp3 < cplim; cp3++)
			if ((*cp++ ^ *cp2++) & *cp3)
				break;
		if (cp3 == cplim)
			return (ifa);
	}
	return (ifa_maybe);
}
E 62
D 72
#include "route.h"
E 72
I 72

#include <net/route.h>

E 72
/*
 * Default action when installing a route with a Link Level gateway.
 * Lookup an appropriate real ifa to point to.
 * This should be moved to /sys/net/link.c eventually.
 */
I 70
void
E 70
link_rtrequest(cmd, rt, sa)
D 65
register struct rtentry *rt;
struct sockaddr *sa;
E 65
I 65
	int cmd;
	register struct rtentry *rt;
	struct sockaddr *sa;
E 65
{
	register struct ifaddr *ifa;
	struct sockaddr *dst;
D 82
	struct ifnet *ifp, *oldifnet = ifnet;
E 82
I 82
	struct ifnet *ifp;
E 82

	if (cmd != RTM_ADD || ((ifa = rt->rt_ifa) == 0) ||
	    ((ifp = ifa->ifa_ifp) == 0) || ((dst = rt_key(rt)) == 0))
		return;
D 62
	ifnet = ifp;
	if (((ifa = ifa_ifwithnet(dst)) && ifa->ifa_ifp == ifp) ||
	    ((ifa = ifa_ifwithaf(dst->sa_family)) && ifa->ifa_ifp == ifp)) {
		ifnet = oldifnet;
E 62
I 62
	if (ifa = ifaof_ifpforaddr(dst, ifp)) {
I 75
		IFAFREE(rt->rt_ifa);
E 75
E 62
		rt->rt_ifa = ifa;
I 75
		ifa->ifa_refcnt++;
E 75
		if (ifa->ifa_rtrequest && ifa->ifa_rtrequest != link_rtrequest)
			ifa->ifa_rtrequest(cmd, rt, sa);
D 62
	} else
		ifnet = oldifnet;
E 62
I 62
	}
E 62
}
E 61
E 47

/*
 * Mark an interface down and notify protocols of
 * the transition.
I 24
 * NOTE: must be called at splnet or eqivalent.
E 24
 */
I 77
void
E 77
if_down(ifp)
	register struct ifnet *ifp;
{
I 40
	register struct ifaddr *ifa;
E 40
I 19

E 19
	ifp->if_flags &= ~IFF_UP;
D 40
	pfctlinput(PRC_IFDOWN, (caddr_t)&ifp->if_addr);
E 40
I 40
	for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
D 43
		pfctlinput(PRC_IFDOWN, (caddr_t)&ifa->ifa_addr);
E 43
I 43
D 52
		pfctlinput(PRC_IFDOWN, &ifa->ifa_addr);
E 52
I 52
		pfctlinput(PRC_IFDOWN, ifa->ifa_addr);
E 52
I 50
	if_qflush(&ifp->if_snd);
I 67
	rt_ifmsg(ifp);
E 67
}

/*
I 67
 * Mark an interface up and notify protocols of
 * the transition.
 * NOTE: must be called at splnet or eqivalent.
 */
I 77
void
E 77
if_up(ifp)
	register struct ifnet *ifp;
{
	register struct ifaddr *ifa;

	ifp->if_flags |= IFF_UP;
#ifdef notyet
	/* this has no effect on IP, and will kill all iso connections XXX */
	for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
		pfctlinput(PRC_IFUP, ifa->ifa_addr);
D 76
#endif notyet
E 76
I 76
#endif
E 76
	rt_ifmsg(ifp);
}

/*
E 67
 * Flush an interface queue.
 */
I 77
void
E 77
if_qflush(ifq)
	register struct ifqueue *ifq;
{
	register struct mbuf *m, *n;

	n = ifq->ifq_head;
	while (m = n) {
		n = m->m_act;
		m_freem(m);
	}
	ifq->ifq_head = 0;
	ifq->ifq_tail = 0;
	ifq->ifq_len = 0;
E 50
E 43
E 40
E 14
E 11
I 4
}
I 18

/*
 * Handle interface watchdog timer routines.  Called
 * from softclock, we decrement timers (if set) and
 * call the appropriate interface routine on expiration.
 */
D 71
if_slowtimo()
E 71
I 71
void
if_slowtimo(arg)
	void *arg;
E 71
{
	register struct ifnet *ifp;
I 52
	int s = splimp();
E 52

D 24
	for (ifp = ifnet; ifp; ifp = ifp->if_next)
		if (ifp->if_timer && --ifp->if_timer == 0) {
			if (ifp->if_watchdog == 0) {
				printf("%s%d: no watchdog routine\n", 
					ifp->if_name, ifp->if_unit);
				continue;
			}
E 24
I 24
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		if (ifp->if_timer == 0 || --ifp->if_timer)
			continue;
		if (ifp->if_watchdog)
E 24
			(*ifp->if_watchdog)(ifp->if_unit);
D 24
		}
E 24
I 24
	}
I 52
	splx(s);
E 52
E 24
I 19
D 22
	timeout(if_slowtimo, 0, hz / IFNET_SLOWHZ);
E 22
I 22
D 71
	timeout(if_slowtimo, (caddr_t)0, hz / IFNET_SLOWHZ);
E 71
I 71
	timeout(if_slowtimo, (void *)0, hz / IFNET_SLOWHZ);
E 71
I 26
}

/*
D 29
 * Service a socket ioctl request directed
 * to an interface.
E 29
I 29
 * Map interface name to
 * interface structure pointer.
E 29
 */
D 29
ifrequest(cmd, data)
	int cmd;
	caddr_t data;
E 29
I 29
struct ifnet *
ifunit(name)
	register char *name;
E 29
{
D 29
	register struct ifnet *ifp;
	register struct ifreq *ifr;
E 29
	register char *cp;
D 29
	int unit, s;
E 29
I 29
	register struct ifnet *ifp;
	int unit;
I 53
	unsigned len;
	char *ep, c;
E 53
E 29

D 29
	ifr = (struct ifreq *)data;
	for (cp = ifr->ifr_name; *cp; cp++)
E 29
I 29
	for (cp = name; cp < name + IFNAMSIZ && *cp; cp++)
E 29
		if (*cp >= '0' && *cp <= '9')
			break;
D 29
	if (*cp == 0)
		return (ENXIO);		/* couldn't find unit */
E 29
I 29
	if (*cp == '\0' || cp == name + IFNAMSIZ)
		return ((struct ifnet *)0);
E 29
D 33
	unit = *cp - '0', *cp = 0;
E 33
I 33
D 53
	unit = *cp - '0';
E 53
I 53
	/*
	 * Save first char of unit, and pointer to it,
	 * so we can put a null there to avoid matching
	 * initial substrings of interface names.
	 */
	len = cp - name + 1;
	c = *cp;
	ep = cp;
	for (unit = 0; *cp >= '0' && *cp <= '9'; )
		unit = unit * 10 + *cp++ - '0';
	*ep = 0;
E 53
E 33
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
D 28
		if (bcmp(ifp->if_name, ifr->ifr_name, cp - ifr->ifr_name))
E 28
I 28
D 29
		if (bcmp(ifp->if_name, ifr->ifr_name,
		    (unsigned)(cp - ifr->ifr_name)))
E 29
I 29
D 53
		if (bcmp(ifp->if_name, name, (unsigned)(cp - name)))
E 53
I 53
		if (bcmp(ifp->if_name, name, len))
E 53
E 29
E 28
			continue;
		if (unit == ifp->if_unit)
D 29
			goto found;
E 29
I 29
			break;
E 29
	}
I 53
	*ep = c;
E 53
D 29
	return (ENXIO);
E 29
I 29
	return (ifp);
}
E 29

D 29
found:
E 29
I 29
/*
 * Interface ioctls.
 */
I 77
int
E 77
D 40
ifioctl(cmd, data)
E 40
I 40
D 64
ifioctl(so, cmd, data)
E 64
I 64
ifioctl(so, cmd, data, p)
E 64
	struct socket *so;
E 40
D 84
	int cmd;
E 84
I 84
	u_long cmd;
E 84
	caddr_t data;
I 64
	struct proc *p;
E 64
{
	register struct ifnet *ifp;
	register struct ifreq *ifr;
I 55
	int error;
E 55

E 29
	switch (cmd) {

D 29
	case SIOCGIFADDR:
		ifr->ifr_addr = ifp->if_addr;
		break;
E 29
I 29
	case SIOCGIFCONF:
I 52
	case OSIOCGIFCONF:
E 52
		return (ifconf(cmd, data));
I 35
D 77

D 43
#if defined(INET) && NETHER > 0
E 43
I 43
D 45
#if (defined(INET) || defined(BBNNET)) && NETHER > 0
E 45
I 45
#if defined(INET) && NETHER > 0
E 45
E 43
	case SIOCSARP:
	case SIOCDARP:
D 55
		if (!suser())
			return (u.u_error);
E 55
I 55
D 64
		if (error = suser(u.u_cred, &u.u_acflag))
E 64
I 64
		if (error = suser(p->p_ucred, &p->p_acflag))
E 64
			return (error);
E 55
		/* FALL THROUGH */
	case SIOCGARP:
I 52
	case OSIOCGARP:
E 52
		return (arpioctl(cmd, data));
#endif
E 77
E 35
E 29
D 40

	case SIOCSIFADDR:
D 29
		if_rtinit(ifp, -1);	/* delete previous route */
		s = splimp();
		ifp->if_addr = ifr->ifr_addr;
		(*ifp->if_init)(unit);
		splx(s);
E 29
I 29
	case SIOCSIFFLAGS:
	case SIOCSIFDSTADDR:
		if (!suser())
			return (u.u_error);
E 29
		break;
E 40
I 29
	}
	ifr = (struct ifreq *)data;
	ifp = ifunit(ifr->ifr_name);
	if (ifp == 0)
		return (ENXIO);
	switch (cmd) {
E 29

I 29
D 40
	case SIOCGIFADDR:
		ifr->ifr_addr = ifp->if_addr;
		break;

E 29
	case SIOCGIFDSTADDR:
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
		ifr->ifr_dstaddr = ifp->if_dstaddr;
		break;

E 40
D 29
	case SIOCSIFDSTADDR:
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
		s = splimp();
		ifp->if_dstaddr = ifr->ifr_dstaddr;
		splx(s);
		break;

E 29
	case SIOCGIFFLAGS:
		ifr->ifr_flags = ifp->if_flags;
		break;

I 46
	case SIOCGIFMETRIC:
		ifr->ifr_metric = ifp->if_metric;
		break;

E 46
I 30
	case SIOCSIFFLAGS:
I 44
D 55
		if (!suser())
			return (u.u_error);
E 55
I 55
D 64
		if (error = suser(u.u_cred, &u.u_acflag))
E 64
I 64
		if (error = suser(p->p_ucred, &p->p_acflag))
E 64
			return (error);
E 55
E 44
		if (ifp->if_flags & IFF_UP && (ifr->ifr_flags & IFF_UP) == 0) {
			int s = splimp();
			if_down(ifp);
I 67
			splx(s);
		}
		if (ifr->ifr_flags & IFF_UP && (ifp->if_flags & IFF_UP) == 0) {
			int s = splimp();
			if_up(ifp);
E 67
			splx(s);
		}
D 40
		ifp->if_flags = ifr->ifr_flags;
E 40
I 40
		ifp->if_flags = (ifp->if_flags & IFF_CANTCHANGE) |
			(ifr->ifr_flags &~ IFF_CANTCHANGE);
I 43
		if (ifp->if_ioctl)
			(void) (*ifp->if_ioctl)(ifp, cmd, data);
I 46
		break;

	case SIOCSIFMETRIC:
D 55
		if (!suser())
			return (u.u_error);
E 55
I 55
D 64
		if (error = suser(u.u_cred, &u.u_acflag))
E 64
I 64
		if (error = suser(p->p_ucred, &p->p_acflag))
E 64
			return (error);
E 55
		ifp->if_metric = ifr->ifr_metric;
E 46
E 43
E 40
		break;
I 70

D 74
#ifdef MULTICAST
E 74
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (error = suser(p->p_ucred, &p->p_acflag))
			return (error);
D 73
		if (ifp->if_ioctl)
E 73
I 73
		if (ifp->if_ioctl == NULL)
E 73
			return (EOPNOTSUPP);
		return ((*ifp->if_ioctl)(ifp, cmd, data));
D 74
#endif
E 74
E 70

E 30
D 29
	case SIOCSIFFLAGS:
		if ((ifr->ifr_flags & IFF_UP) == 0 &&
		    (ifp->if_flags & IFF_UP)) {
			s = splimp();
			if_down(ifp);
			splx(s);
		}
		ifp->if_flags = ifr->ifr_flags;
		break;

E 29
	default:
D 29
		return (EINVAL);
E 29
I 29
D 40
		if (ifp->if_ioctl == 0)
E 40
I 40
		if (so->so_proto == 0)
E 40
			return (EOPNOTSUPP);
I 52
#ifndef COMPAT_43
E 52
D 30
		return ((*ifp->if_ioctl)(cmd, data));
E 30
I 30
D 40
		return ((*ifp->if_ioctl)(ifp, cmd, data));
E 40
I 40
		return ((*so->so_proto->pr_usrreq)(so, PRU_CONTROL,
			cmd, data, ifp));
I 52
#else
	    {
D 60
		int error, ocmd = cmd;
E 60
I 60
		int ocmd = cmd;
E 60

		switch (cmd) {

		case SIOCSIFDSTADDR:
		case SIOCSIFADDR:
		case SIOCSIFBRDADDR:
		case SIOCSIFNETMASK:
#if BYTE_ORDER != BIG_ENDIAN
			if (ifr->ifr_addr.sa_family == 0 &&
			    ifr->ifr_addr.sa_len < 16) {
				ifr->ifr_addr.sa_family = ifr->ifr_addr.sa_len;
				ifr->ifr_addr.sa_len = 16;
			}
#else
			if (ifr->ifr_addr.sa_len == 0)
				ifr->ifr_addr.sa_len = 16;
#endif
			break;

		case OSIOCGIFADDR:
			cmd = SIOCGIFADDR;
			break;

		case OSIOCGIFDSTADDR:
			cmd = SIOCGIFDSTADDR;
			break;

		case OSIOCGIFBRDADDR:
			cmd = SIOCGIFBRDADDR;
			break;

		case OSIOCGIFNETMASK:
			cmd = SIOCGIFNETMASK;
		}
		error =  ((*so->so_proto->pr_usrreq)(so, PRU_CONTROL,
							    cmd, data, ifp));
		switch (ocmd) {

		case OSIOCGIFADDR:
		case OSIOCGIFDSTADDR:
		case OSIOCGIFBRDADDR:
		case OSIOCGIFNETMASK:
			*(u_short *)&ifr->ifr_addr = ifr->ifr_addr.sa_family;
		}
		return (error);

	    }
#endif
E 52
E 40
E 30
E 29
	}
	return (0);
}

/*
 * Return interface configuration
 * of system.  List may be used
 * in later ioctl's (above) to get
 * other information.
 */
I 28
/*ARGSUSED*/
I 77
int
E 77
E 28
ifconf(cmd, data)
	int cmd;
	caddr_t data;
{
	register struct ifconf *ifc = (struct ifconf *)data;
	register struct ifnet *ifp = ifnet;
I 40
	register struct ifaddr *ifa;
E 40
D 27
	register char *cp;
	struct ifreq ifr;
E 27
I 27
	register char *cp, *ep;
	struct ifreq ifr, *ifrp;
E 27
	int space = ifc->ifc_len, error = 0;

I 27
	ifrp = ifc->ifc_req;
	ep = ifr.ifr_name + sizeof (ifr.ifr_name) - 2;
E 27
	for (; space > sizeof (ifr) && ifp; ifp = ifp->if_next) {
D 27
		bcopy(ifp->if_name, ifr.ifr_name, sizeof (ifr.ifr_name));
		for (cp = ifr.ifr_name; *cp; cp++)
E 27
I 27
D 79
		bcopy(ifp->if_name, ifr.ifr_name, sizeof (ifr.ifr_name) - 2);
E 79
I 79
		strncpy(ifr.ifr_name, ifp->if_name, sizeof (ifr.ifr_name) - 2);
E 79
		for (cp = ifr.ifr_name; cp < ep && *cp; cp++)
E 27
D 68
			;
E 68
I 68
			continue;
E 68
D 27
		*cp = '0' + ifp->if_unit;
E 27
I 27
		*cp++ = '0' + ifp->if_unit; *cp = '\0';
E 27
D 40
		ifr.ifr_addr = ifp->if_addr;
D 27
		error = copyout((caddr_t)&ifr, ifc->ifc_buf, sizeof (ifr));
E 27
I 27
		error = copyout((caddr_t)&ifr, (caddr_t)ifrp, sizeof (ifr));
E 27
		if (error)
			break;
D 27
		space -= sizeof (ifr);
		ifc->ifc_req++;
E 27
I 27
		space -= sizeof (ifr), ifrp++;
E 40
I 40
		if ((ifa = ifp->if_addrlist) == 0) {
			bzero((caddr_t)&ifr.ifr_addr, sizeof(ifr.ifr_addr));
D 79
			error = copyout((caddr_t)&ifr, (caddr_t)ifrp, sizeof (ifr));
E 79
I 79
			error = copyout((caddr_t)&ifr, (caddr_t)ifrp,
			    sizeof (ifr));
E 79
			if (error)
				break;
			space -= sizeof (ifr), ifrp++;
		} else 
		    for ( ; space > sizeof (ifr) && ifa; ifa = ifa->ifa_next) {
D 52
			ifr.ifr_addr = ifa->ifa_addr;
			error = copyout((caddr_t)&ifr, (caddr_t)ifrp, sizeof (ifr));
E 52
I 52
			register struct sockaddr *sa = ifa->ifa_addr;
#ifdef COMPAT_43
			if (cmd == OSIOCGIFCONF) {
				struct osockaddr *osa =
					 (struct osockaddr *)&ifr.ifr_addr;
				ifr.ifr_addr = *sa;
				osa->sa_family = sa->sa_family;
				error = copyout((caddr_t)&ifr, (caddr_t)ifrp,
						sizeof (ifr));
				ifrp++;
			} else
#endif
			if (sa->sa_len <= sizeof(*sa)) {
				ifr.ifr_addr = *sa;
				error = copyout((caddr_t)&ifr, (caddr_t)ifrp,
						sizeof (ifr));
				ifrp++;
			} else {
				space -= sa->sa_len - sizeof(*sa);
				if (space < sizeof (ifr))
					break;
				error = copyout((caddr_t)&ifr, (caddr_t)ifrp,
						sizeof (ifr.ifr_name));
				if (error == 0)
				    error = copyout((caddr_t)sa,
				      (caddr_t)&ifrp->ifr_addr, sa->sa_len);
				ifrp = (struct ifreq *)
					(sa->sa_len + (caddr_t)&ifrp->ifr_addr);
			}
E 52
			if (error)
				break;
D 52
			space -= sizeof (ifr), ifrp++;
E 52
I 52
			space -= sizeof (ifr);
E 52
		}
E 40
E 27
	}
	ifc->ifc_len -= space;
	return (error);
I 57
}

D 64
static sprint_d(cp, n)
register char *cp;
u_short n;
E 64
I 64
static char *
sprint_d(n, buf, buflen)
	u_int n;
	char *buf;
	int buflen;
E 64
{
D 64
	register int q, m;
E 64
I 64
	register char *cp = buf + buflen - 1;

	*cp = 0;
E 64
	do {
D 64
	    if (n >= 10000) m = 10000;
		else if (n >= 1000) m = 1000;
		else if (n >= 100) m = 100;
		else if (n >= 10) m = 10;
		else m = 1;
	    q = n / m;
	    n -= m * q;
	    if (q > 9) q = 10; /* For crays with more than 100K interfaces */
	    *cp++ = "0123456789Z"[q];
	} while (n > 0);
	*cp++ = 0;
E 64
I 64
		cp--;
		*cp = "0123456789"[n % 10];
		n /= 10;
	} while (n != 0);
	return (cp);
E 64
E 57
E 26
E 22
E 19
}
E 18
D 16

I 11
/*
 * Formulate an Internet address from network + host.  Used in
 * building addresses stored in the ifnet structure.
 */
E 11
struct in_addr
if_makeaddr(net, host)
	int net, host;
{
	u_long addr;

	if (net < 128)
D 6
		addr = (host << 8) | net;
E 6
I 6
		addr = (net << 24) | host;
E 6
	else if (net < 65536)
D 6
		addr = (host << 16) | net;
E 6
I 6
		addr = (net << 16) | host;
E 6
	else
D 6
		addr = (host << 24) | net;
E 6
I 6
		addr = (net << 8) | host;
I 7
#ifdef vax
E 7
E 6
	addr = htonl(addr);
I 7
#endif
E 7
	return (*(struct in_addr *)&addr);
E 4
}
I 12

/*
 * Initialize an interface's routing
 * table entry according to the network.
 * INTERNET SPECIFIC.
 */
if_rtinit(ifp, flags)
	register struct ifnet *ifp;
	int flags;
{
	struct sockaddr_in sin;

	if (ifp->if_flags & IFF_ROUTE)
		return;
	bzero((caddr_t)&sin, sizeof (sin));
	sin.sin_family = AF_INET;
	sin.sin_addr = if_makeaddr(ifp->if_net, 0);
D 13
	rtinit(&sin, &sin, flags);
E 13
I 13
	rtinit(&sin, &ifp->if_addr, flags);
E 13
}
E 16
E 12
E 3
E 1
