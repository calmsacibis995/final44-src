h64768
s 00002/00000/00196
d D 8.2 95/04/28 14:37:59 bostic 4 3
c wrong interface printf
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00194
d D 8.1 93/06/06 15:44:01 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00009/00187
d D 7.2 92/07/07 16:57:21 sklower 2 1
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00196/00000/00000
d D 7.1 92/07/06 15:35:03 sklower 1 0
c date and time created 92/07/06 15:35:03 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 Stephen Deering
D 3
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Print DVMRP multicast routing structures and statistics.
 *
 * MROUTING 1.0
 */

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>

#include <netinet/in.h>
#include <netinet/igmp.h>
#define KERNEL 1
#include <netinet/ip_mroute.h>
#undef KERNEL

#include <stdio.h>
#include <stdlib.h>
#include "netstat.h"

void
mroutepr(mrpaddr, mrtaddr, vifaddr)
D 2
	off_t mrpaddr, mrtaddr, vifaddr;
E 2
I 2
	u_long mrpaddr, mrtaddr, vifaddr;
E 2
{
	u_int mrtproto;
	struct mrt *mrttable[MRTHASHSIZ];
	struct vif viftable[MAXVIFS];
	register struct mrt *mrt;
	struct mrt smrt;
	register struct vif *v;
	register vifi_t vifi;
	register struct in_addr *grp;
	register int i, n;
	register int banner_printed;
	register int saved_nflag;

	if (mrpaddr == 0) {
		printf("ip_mrtproto: symbol not in namelist\n");
		return;
	}

D 2
	kread((off_t)mrpaddr, (char *)&mrtproto, sizeof(mrtproto));
E 2
I 2
	kread(mrpaddr, (char *)&mrtproto, sizeof(mrtproto));
E 2
	switch (mrtproto) {

	case 0:
		printf("no multicast routing compiled into this system\n");
		return;

	case IGMP_DVMRP:
		break;

	default:
		printf("multicast routing protocol %u, unknown\n", mrtproto);
		return;
	}

	if (mrtaddr == 0) {
		printf("mrttable: symbol not in namelist\n");
		return;
	}
	if (vifaddr == 0) {
		printf("viftable: symbol not in namelist\n");
		return;
	}

	saved_nflag = nflag;
	nflag = 1;

D 2
	kread((off_t)vifaddr, (char *)&viftable, sizeof(viftable));
E 2
I 2
	kread(vifaddr, (char *)&viftable, sizeof(viftable));
E 2
	banner_printed = 0;
	for (vifi = 0, v = viftable; vifi < MAXVIFS; ++vifi, ++v) {
		if (v->v_lcl_addr.s_addr == 0)
			continue;

		if (!banner_printed) {
			printf("\nVirtual Interface Table\n%s%s",
			    " Vif   Threshold   Local-Address   ",
			    "Remote-Address   Groups\n");
			banner_printed = 1;
		}

		printf(" %2u       %3u      %-15.15s",
		    vifi, v->v_threshold, routename(v->v_lcl_addr.s_addr));
		printf(" %-15.15s\n", (v->v_flags & VIFF_TUNNEL) ?
		    routename(v->v_rmt_addr.s_addr) : "");

		n = v->v_lcl_grps_n;
		grp = (struct in_addr *)malloc(n * sizeof(*grp));
		if (grp == NULL) {
			printf("v_lcl_grps_n: malloc failed\n");
			return;
		}
D 2
		kread((off_t)v->v_lcl_grps, (caddr_t)grp, n * sizeof(*grp));
E 2
I 2
		kread((u_long)v->v_lcl_grps, (caddr_t)grp, n * sizeof(*grp));
E 2
		for (i = 0; i < n; ++i)
			printf("%51s %-15.15s\n",
			    "", routename((grp++)->s_addr));
		free(grp);
	}
	if (!banner_printed)
		printf("\nVirtual Interface Table is empty\n");

D 2
	kread((off_t)mrtaddr, (char *)&mrttable, sizeof(mrttable));
E 2
I 2
	kread(mrtaddr, (char *)&mrttable, sizeof(mrttable));
E 2
	banner_printed = 0;
	for (i = 0; i < MRTHASHSIZ; ++i) {
		for (mrt = mrttable[i]; mrt != NULL; mrt = mrt->mrt_next) {
			if (!banner_printed) {
				printf("\nMulticast Routing Table\n%s",
				    " Hash  Origin-Subnet  In-Vif  Out-Vifs\n");
				banner_printed = 1;
			}

D 2
			kread((off_t)mrt, (char *)&smrt, sizeof(*mrt));
E 2
I 2
			kread((u_long)mrt, (char *)&smrt, sizeof(*mrt));
E 2
			mrt = &smrt;
			printf(" %3u   %-15.15s  %2u   ",
			    i, netname(mrt->mrt_origin.s_addr,
			    ntohl(mrt->mrt_originmask.s_addr)),
			    mrt->mrt_parent);
			for (vifi = 0; vifi < MAXVIFS; ++vifi)
				if (VIFM_ISSET(vifi, mrt->mrt_children))
					printf(" %u%c",
					    vifi,
					    VIFM_ISSET(vifi, mrt->mrt_leaves) ?
					    '*' : ' ');
			printf("\n");
		}
	}
	if (!banner_printed)
		printf("\nMulticast Routing Table is empty\n");

	printf("\n");
	nflag = saved_nflag;
}


void
mrt_stats(mrpaddr, mstaddr)
D 2
	off_t mrpaddr, mstaddr;
E 2
I 2
	u_long mrpaddr, mstaddr;
E 2
{
	u_int mrtproto;
	struct mrtstat mrtstat;

	if(mrpaddr == 0) {
		printf("ip_mrtproto: symbol not in namelist\n");
		return;
	}

D 2
	kread((off_t)mrpaddr, (char *)&mrtproto, sizeof(mrtproto));
E 2
I 2
	kread(mrpaddr, (char *)&mrtproto, sizeof(mrtproto));
E 2
	switch (mrtproto) {
	    case 0:
		printf("no multicast routing compiled into this system\n");
		return;

	    case IGMP_DVMRP:
		break;

	    default:
		printf("multicast routing protocol %u, unknown\n", mrtproto);
		return;
	}

	if (mstaddr == 0) {
		printf("mrtstat: symbol not in namelist\n");
		return;
	}

D 2
	kread((off_t)mstaddr, (char *)&mrtstat, sizeof(mrtstat));
E 2
I 2
	kread(mstaddr, (char *)&mrtstat, sizeof(mrtstat));
E 2
	printf("multicast routing:\n");
	printf(" %10u multicast route lookup%s\n",
	  mrtstat.mrts_mrt_lookups, plural(mrtstat.mrts_mrt_lookups));
	printf(" %10u multicast route cache miss%s\n",
	  mrtstat.mrts_mrt_misses, plurales(mrtstat.mrts_mrt_misses));
	printf(" %10u group address lookup%s\n",
	  mrtstat.mrts_grp_lookups, plural(mrtstat.mrts_grp_lookups));
	printf(" %10u group address cache miss%s\n",
	  mrtstat.mrts_grp_misses, plurales(mrtstat.mrts_grp_misses));
	printf(" %10u datagram%s with no route for origin\n",
	  mrtstat.mrts_no_route, plural(mrtstat.mrts_no_route));
	printf(" %10u datagram%s with malformed tunnel options\n",
	  mrtstat.mrts_bad_tunnel, plural(mrtstat.mrts_bad_tunnel));
	printf(" %10u datagram%s with no room for tunnel options\n",
	  mrtstat.mrts_cant_tunnel, plural(mrtstat.mrts_cant_tunnel));
I 4
	printf(" %10u datagram%s arrived on the wrong interface\n",
	  mrtstat.mrts_wrong_if, plural(mrtstat.mrts_wrong_if));
E 4
}
E 1
