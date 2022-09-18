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
 * $Log:	group.c,v $
 * Revision 2.3  89/03/09  20:42:42  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:57:41  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */

/*
 * group.c
 */

#include "igmproto.h"
#include "multicast_agent.h"

#if	IGMPROTO

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/route.h>

#include "in_systm.h"
#include "in.h"
#include "ip.h"
#include "ip_var.h"
#include "group.h"


struct GroupDescriptor GroupDescriptorPool[GROUP_POOL_SIZE];    /* array */

InitGroupDescriptorPool()
{
    register struct GroupDescriptor *ad;
    register u_long i;

    for( i = 0; i < GROUP_POOL_SIZE; ++i ) {
    /* init the group descs */
	ad = &GroupDescriptorPool[i];
	ad->inuse = 0;
	ad->pcb.ADnext = NULL;
	ad->pcb.ADprev = NULL;
	ad->pcb.socket = NULL;
	ad->pcb.options = NULL;
	ad->pcb.message = NULL;
	ad->pcb.next = NULL;
	ad->pcb.prev = NULL;
	ad->pcb.ifp = NULL;
	ad->pcb.countdown = 0;
	ad->pcb.num_rtx = 0;
	ad->pcb.type = 0;
	ad->pcb.code = IGMP_RC_UNSET;
	ad->pcb.identifier = 0;
	ad->pcb.key1 = 0;
	ad->pcb.key2 = 0;
	ad->pcb.groupaddr.s_addr = 0;
	ad->pcb.ad = ad;
	ad->pcb.rc = IGMP_RC_UNSET;
	ad->pcb.loopback = 0;
     }
}



struct GroupDescriptor *AllocGroupDescriptor()
{
    register u_long		i;

    for( i = 0; i < GROUP_POOL_SIZE; i++ )	{
	if (!(GroupDescriptorPool[i].inuse)) {
	    GroupDescriptorPool[i].inuse = 1;
	    return(&GroupDescriptorPool[i]);
	}
    }
    return(NULL);
}

struct GroupDescriptor *InstallGroupDescriptor(ipaddr,key1,key2,igmpcb,ifp)
struct in_addr ipaddr;
u_long key1,key2;
struct igmpcb *igmpcb;
struct ifnet *ifp;
{
    register struct GroupDescriptor	*ad;

    if( (ad = AllocGroupDescriptor()) != NULL ) {

	/* Initialize the dummy igmpcb */
	ad->pcb.groupaddr.s_addr = ipaddr.s_addr;
	ad->pcb.key1 = key1;
	ad->pcb.key2 = key2;
	ad->confirm_timer = IGMP_RANDOM_CONFIRM_INTERVAL * SLOWTIMEO_FREQUENCY;
	ad->pcb.ifp  = ifp;
#if	MULTICAST_AGENT
	/* InitMulticastAgent() will call this routine with igmpcb == NULL */
	/* when it is installing group INADDR_MA_GROUP, because it is joining */
	/* the same group on all interfaces, with only one socket/igmpcb */
	/* We don't want to AddToPCBList this igmpcb */

	if (igmpcb != NULL) {
#endif	MULTICAST_AGENT
	    ad->pcb.loopback  = igmpcb->loopback;
	    AddToPCBList(ad,igmpcb);
#if	MULTICAST_AGENT
	}
	if (ipaddr.s_addr == INADDR_MA_GROUP)
	    ad->pcb.loopback  = 1;
#endif	MULTICAST_AGENT
/*
	AcceptAddress(ipaddr,ifp->if_unit);
*/
    }
    return( ad );
}



RemoveGroupDescriptor(ad)
struct GroupDescriptor *ad;
{
    struct igmpcb *pcb,*holdpcb;

    if (ad == NULL) return;

    ad->confirm_timer = 0; 
    pcb = ad->pcb.ADnext;
    while (pcb != NULL) {
	holdpcb = pcb;
	pcb->ADprev = NULL;
	pcb = pcb->ADnext;
	igmpcb_clear(holdpcb);
    }
/*
    RejectAddress(ad->pcb.groupaddr,ad->pcb.ifp->if_unit);
*/
    ad->pcb.ADnext = NULL;
    ad->pcb.ADprev = NULL;
    ad->pcb.key1 = 0;
    ad->pcb.key2 = 0;
    ad->pcb.ifp = NULL;
    ad->pcb.groupaddr.s_addr = 0;
    ad->pcb.socket = NULL;
    ad->pcb.options = NULL;
    ad->pcb.message = NULL;
    ad->pcb.next = NULL;
    ad->pcb.prev = NULL;
    ad->pcb.ifp = NULL;
    ad->pcb.countdown = 0;
    ad->pcb.num_rtx = 0;
    ad->pcb.type = 0;
    ad->pcb.code = IGMP_RC_UNSET;
    ad->pcb.identifier = 0;
    ad->pcb.ad = ad;
    ad->pcb.rc = IGMP_RC_UNSET;
    ad->pcb.loopback = 0;
    ad->inuse = 0;
}



struct GroupDescriptor *FindGroupDescriptor(ipaddr,ifp)
struct in_addr ipaddr;
struct ifnet *ifp;
{
    int i;

    for(i = 0; i < GROUP_POOL_SIZE; i++) {

	if (!(GroupDescriptorPool[i].inuse)) continue;

	if (GroupDescriptorPool[i].pcb.groupaddr.s_addr == ipaddr.s_addr) {

	    if (ifp == NULL) return(&GroupDescriptorPool[i]);

	    else if(GroupDescriptorPool[i].pcb.ifp == ifp)
	        return(&GroupDescriptorPool[i]);
	}
    }
    return(NULL);
}

/* 
 * DeleteFromPCBList()
 *
 * Delete igmpcb from list associated with igmpcb's group descriptor.
 * If it's the very last one, leave it.  It will be cleaned up when the
 * successful LeaveGroupReply is received.
 * The reason to leave it is if the request fails, we should still
 * have the igmpcb.
 */

DeleteFromPCBList(igmpcb)
struct igmpcb *igmpcb;
{
    struct GroupDescriptor *ad;

    ad = igmpcb->ad;
    if ((ad == NULL) || (ad->pcb.ADnext == NULL)) return(-1); 
    if (ad->pcb.ADnext->ADnext == NULL) return (0); /* Only one left */

    igmpcb->ADprev->ADnext = igmpcb->ADnext;

    if (igmpcb->ADnext != NULL)
	igmpcb->ADnext->ADprev = igmpcb->ADprev;

    if (ad->pcb.ADnext == NULL) return(-1); /* Shouldn't happen */

    return(1);
}

/* 
 * AddToPCBList()
 *
 * Add igmpcb to list for this group descriptor.
 */


AddToPCBList(ad,igmpcb)
struct GroupDescriptor *ad;
struct igmpcb *igmpcb;
{
    if (ad->pcb.ADnext != NULL)
	ad->pcb.ADnext->ADprev = igmpcb;
    igmpcb->ADprev = &ad->pcb;
    igmpcb->ADnext = ad->pcb.ADnext;
    ad->pcb.ADnext = igmpcb;
    ad->pcb.loopback |= igmpcb->loopback;
    igmpcb->ad = ad;
}


#endif	IGMPROTO
