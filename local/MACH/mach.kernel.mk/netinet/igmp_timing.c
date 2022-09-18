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
 * $Log:	igmp_timing.c,v $
 * Revision 2.3  89/03/09  20:43:48  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:58:46  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * igmp_timing.c
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
#if	MULTICAST_AGENT
#include "agent_var.h"
#endif	MULTICAST_AGENT

igmp_slowtimeo()
{
    struct igmpcb *igmpcb;
    struct GroupDescriptor *ad;
    struct mbuf *copy;
    int i;
    int s = splnet();
#if	MULTICAST_AGENT
    struct GroupRecord *group;
    struct attachedcell *attachedmem;
    struct addrcell *agentmem;
#endif	MULTICAST_AGENT

    for (igmpcb = igmpcbhead.next; igmpcb != &igmpcbhead; igmpcb = igmpcb->next) {
        if (igmpcb->message == NULL) continue;
	if (igmpcb->countdown-- > 0) continue;
	igmpcb->countdown = IGMP_SLOWTIMEO_COUNTDOWN;
	if (igmpcb->num_rtx < IGMP_REQUEST_TRANS_LIMIT) {

	    /* Retransmit the request */
	    igmpcb->num_rtx++;
	    copy = m_copy(igmpcb->message,0,(int) M_COPYALL);
	    if (copy == NULL) continue;
	    (void) ip_output(copy, (struct mbuf *)NULL, (struct route *)0 , 0);
	}
	else {
	    igmpcb->rc = IGMP_NO_RESPONSE;
	    wakeup((caddr_t)&igmpcb->rc);
	}
    }

#if	MULTICAST_AGENT
	if (agentsocket) goto skip_to_here;
#endif	MULTICAST_AGENT

    for (i = 0; i < GROUP_POOL_SIZE; i++) {
	ad = &GroupDescriptorPool[i];
	if (!(ad->inuse)) continue;
	if (ad->confirm_timer-- > 0) continue;
	igmp_request((struct socket *)0,IGMP_CONFIRM_GROUP_REQUEST,0,
	    ad->pcb.groupaddr,ad->pcb.key1,ad->pcb.key2,ad->pcb.ifp,0);
	ad->confirm_timer = IGMP_RANDOM_CONFIRM_INTERVAL * SLOWTIMEO_FREQUENCY;
    }

#if	MULTICAST_AGENT
skip_to_here:
    if (agentsocket) {
	for (group = grouprecordhead.next; group != &grouprecordhead;
	     group = group->next) {

		if (group->groupaddr.s_addr == INADDR_MA_GROUP) continue;

		for (attachedmem = group->attachednetlist;
		     attachedmem != NULL; 
		     attachedmem = attachedmem->next) {

		       if (attachedmem->confirmtimer-- > 0) continue;
		       else DelAttachedNet(group,attachedmem->ifp);
		}

		for (agentmem = group->memberlist; 
		     agentmem; 
		     agentmem = agentmem->next) {

		       if (agentmem->confirmtimer-- > 0) continue;
		       else DelAgent(group,&agentmem->agentaddr);
		}

		/* The following is ordered as it is so that */
		/* FindGroupDescriptor() is only called if */
		/* absolutely necessary. If any of the preceding */
		/* conditions are true, we won't get that far and */
		/* waste all that time. As it is, it will only be */
		/* called if the agent claims to be the only member */
		/* of this group.  The reason that the I_BELONG flag */
		/* is not a sufficient condition is that this flag */
		/* will not be unset if the user process created or */
		/* joined the group dies without leaving the group */
		/* properly. Remember that the LEAVE GROUP REQUEST */
		/* that is generated when a member process dies */
		/* prematurely is only sent once, and not retransmitted */
		/* so its delivery is not reliable. Thus, the following */

		if ((group->attachednetlist != NULL) ||
		    (group->memberlist != NULL) ||
		    (group->flags & PERMANENT_GROUP) ||
		    ((group->flags & I_BELONG) && 
		    FindGroupDescriptor(group->groupaddr,NULL)))
			continue;

		else DelGroup(&group->groupaddr);
	}
    }
#endif	MULTICAST_AGENT
    splx(s);
}


/* Make this whatever you want */

random()
{
    return(ipstat.ips_total);
}

#endif	IGMPROTO
