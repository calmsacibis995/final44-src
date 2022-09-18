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
 * $Log:	agent.c,v $
 * Revision 2.3  89/03/09  20:40:40  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:55:38  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */

#include "multicast_agent.h"

#if	MULTICAST_AGENT

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/route.h>

#include "in.h"
#include "in_pcb.h"
#include "in_systm.h"
#include "in_var.h"
#include "ip.h"
#include "ip_var.h"
#include "group.h"
#include "agent_var.h"

static u_long minalloc;
static u_long maxalloc;
static u_long lastalloc;
struct socket *agentsocket = NULL;
extern struct ifnet loif;
struct GroupDescriptor *InstallGroupDescriptor();
struct GroupDescriptor *FindGroupDescriptor();
struct GroupRecord *AddGroup();

InitMulticastAgent(so)
struct socket *so;
{
    struct ifnet *ifp;
    u_long key1;
    u_long key2;
    struct groupargs args;
    struct in_addr addr;
    struct GroupRecord *group;
    int s = splnet();

    if(agentsocket != NULL) {
	splx(s);
	return(EINVAL);
    }
    agentsocket = so;
    minalloc = maxalloc = lastalloc = 0;

    grouprecordhead.next = grouprecordhead.prev = &grouprecordhead;

    key1 = random();
    key2 = random() + random();
    addr.s_addr = INADDR_MA_GROUP;
    for(ifp = ifnet; ifp; ifp = ifp->if_next) {
	if(ifp != &loif)
           InstallGroupDescriptor(addr,key1,key2,(struct igmpcb *)NULL,ifp);    
    }

    args.groupaddr.s_addr = INADDR_MA_GROUP;
    args.key1 = key1;
    args.key2 = key2;
    group = AddGroup(&args);
    splx(s);
    return(0);
}

CleanUpAgent()
{
    struct ifnet *ifp;
    struct GroupRecord *group,*holdgroup;
    struct addrcell *hold, *mem;
    struct attachedcell *attachedhold, *attachedmem;
    struct in_addr addr;
    int s = splnet();

    agentsocket = NULL;
    minalloc = maxalloc = lastalloc = 0;
    addr.s_addr = INADDR_MA_GROUP;

    for(ifp = ifnet; ifp; ifp = ifp->if_next) {
	if(ifp != &loif)
           RemoveGroupDescriptor(FindGroupDescriptor(addr,ifp));    
    }

    group = grouprecordhead.next;
    while(group != &grouprecordhead) {
	attachedmem = group->attachednetlist;
	while (attachedmem != NULL) {
	    attachedhold = attachedmem;
	    attachedmem = attachedmem->next;
	    m_free(dtom(attachedhold));
	}
	mem = group->memberlist;
	while (mem != NULL) {
	    hold = mem;
	    mem = mem->next;
	    m_free(dtom(hold));
	}
	holdgroup = group;
	group = group->next;
	if (holdgroup != NULL) {
	    remque(holdgroup);
	    m_free(dtom(holdgroup));
	}
    }
    splx(s);
}




struct GroupRecord *GetGroup(groupaddr)
struct in_addr *groupaddr;
{
    struct GroupRecord *group;

    for (group = grouprecordhead.next; group != &grouprecordhead;
	 group = group->next) {
	    if (group->groupaddr.s_addr == groupaddr->s_addr) return(group);
    }
    return(NULL);
}


/* Note that AddGroup() works slightly differently than AddAgent() */
/* and AddAttachedNet() in that it doesn't check if the group exists */
/* before it adds it.  If it is necessary to do so, it is expected */
/* that this check will take place before the call to AddGroup() */



struct GroupRecord *AddGroup(groupargs)
struct groupargs *groupargs;
{
    register struct GroupRecord *group;
    struct mbuf *m;

#ifdef	AGENTDEBUG
    printf("AddGroup\n");
#endif	AGENTDEBUG

    m = m_get(M_DONTWAIT,MT_DATA);
    if (m == NULL) return(NULL);
    m->m_len = sizeof(struct GroupRecord);

    group = mtod(m, struct GroupRecord *);
    group->groupaddr.s_addr = groupargs->groupaddr.s_addr;
    group->key1 = groupargs->key1;
    group->key2 = groupargs->key2;
    group->attachednetlist = NULL;
    group->memberlist = NULL;
    group->flags = 0;

    insque(group,&grouprecordhead);
    return(group);
}





DelGroup(groupaddr)
struct in_addr *groupaddr;
{
    struct GroupRecord *group;
    struct addrcell *hold, *mem;
    struct attachedcell *attachedhold, *attachedmem;

#ifdef	AGENTDEBUG
    printf("DelGroup\n");
    printf("\tgroupaddr = 0x%x\n",groupaddr->s_addr);
#endif	AGENTDEBUG

    if ((group = GetGroup(groupaddr)) != NULL) {

		attachedmem = group->attachednetlist;

		while (attachedmem != NULL) {
		    attachedhold = attachedmem;
		    attachedmem = attachedmem->next;
		    m_free(dtom(attachedhold));
		}

		mem = group->memberlist;

		while (mem != NULL) {
		    hold = mem;
		    mem = mem->next;
		    m_free(dtom(hold));
		}
		remque(group);
		m_free(dtom(group));
    }
}





struct addrcell *GetAgent(group, agentaddr)
struct GroupRecord *group;
struct in_addr *agentaddr;
{
    struct addrcell *agent;

    for (agent = group->memberlist; agent; agent = agent->next) {
	if (agentaddr->s_addr == agent->agentaddr.s_addr) return(agent);
    }
    return(NULL);
}




AddAgent(group,agentaddr)
struct GroupRecord *group;
struct in_addr *agentaddr;
{
    struct mbuf *m;
    struct addrcell *newmember;
    struct addrcell *agent;

#ifdef	AGENTDEBUG
    printf("AddAgent\n");
    printf("\tgroupaddr = 0x%x, agentaddr = 0x%x\n",group->groupaddr.s_addr,
	agentaddr->s_addr);
#endif	AGENTDEBUG

	if ((agent = GetAgent(group,agentaddr)) != NULL) {
	    agent->confirmtimer = MULTICAST_AGENT_UPDATE_RESET;
	    return(IGMP_REQUEST_GRANTED);
	}

	m = m_get(M_DONTWAIT,MT_DATA);
	if (m == NULL) return(IGMP_NO_RESOURCES);
    	m->m_len = sizeof(struct addrcell);

	newmember = mtod(m,struct addrcell *);
	newmember->agentaddr.s_addr = agentaddr->s_addr;
	newmember->confirmtimer = MULTICAST_AGENT_UPDATE_RESET;
	newmember->next = group->memberlist;
	group->memberlist = newmember;


	return(IGMP_REQUEST_GRANTED);
}





DelAgent(group,agentaddr)
struct GroupRecord *group;
struct in_addr *agentaddr;
{
    struct addrcell *mem,*hold;

#ifdef	AGENTDEBUG
    printf("DelAgent\n");
    printf("\tgroupaddr = 0x%x, agentaddr = 0x%x\n",group->groupaddr.s_addr,
	agentaddr->s_addr);
#endif	AGENTDEBUG

    mem = group->memberlist; 
    if (mem == NULL) return(IGMP_REQUEST_GRANTED); /* No member agents */

    /* Try first one on list */
    hold = mem;
    if (mem->agentaddr.s_addr == agentaddr->s_addr) {
        group->memberlist = mem->next;
        if (hold) m_free(dtom(hold));
    }
    /* Wasn't first one, so try rest of list */
    else {
        while (mem != NULL) {
	    hold = mem;
	    mem = mem->next;
	    if(mem->agentaddr.s_addr == agentaddr->s_addr) {
	        hold->next = mem->next;
	        if (mem) m_free(dtom(mem));
	        break;
	    }
	}
    }
    return(IGMP_REQUEST_GRANTED);
}





struct attachedcell *GetAttachedNet(group,ifp)
struct GroupRecord *group;
struct ifnet *ifp;
{
    struct attachedcell *net;

    for (net = group->attachednetlist; net; net = net->next) {
        if (net->ifp == ifp) return(net);
    }
    return(NULL);
}


AddAttachedNet(group,ifp)
struct GroupRecord *group;
struct ifnet *ifp;
{
    struct mbuf *m;
    struct attachedcell *newmember;

#ifdef	AGENTDEBUG
    printf("AddAttachedNet\n");
#endif	AGENTDEBUG

	m = m_get(M_DONTWAIT,MT_DATA);
	if (m == NULL) return(IGMP_NO_RESOURCES);
    	m->m_len = sizeof(struct attachedcell);

	newmember = mtod(m,struct attachedcell *);

	newmember->ifp = ifp;
	newmember->confirmtimer = MULTICAST_AGENT_CONFIRM_RESET;
	newmember->next = group->attachednetlist;
	group->attachednetlist = newmember;
	return(IGMP_REQUEST_GRANTED);
}



DelAttachedNet(group,ifp)
struct GroupRecord *group;
struct ifnet *ifp;
{
    struct attachedcell *mem,*hold;
    struct sockaddr_in addr;
    struct ifaddr *ifaddress;

#ifdef	AGENTDEBUG
    printf("DelAttachedNet\n");
    printf("\tgroupaddr = 0x%x, ifp = 0x%x\n",group->groupaddr.s_addr,ifp);
#endif	AGENTDEBUG

	mem = group->attachednetlist; 
	if (mem == NULL) {
	    /* No attached net members */
	    return(0);
	}

	/* Try first one on list */
	hold = mem;
	if (mem->ifp == ifp) {
	    group->attachednetlist = mem->next;
	    if (hold) m_free(dtom(hold));
	}
	/* Wasn't first one, so try rest of list */
	else {
	    while (mem != NULL) {
		hold = mem;
	        mem = mem->next;
		if (mem->ifp == ifp) {
		    hold->next = mem->next;
		    if (mem) m_free(dtom(mem));
		    break;
		}
	    }
	}
        return(0);
}


UpdateMembership(buflen,bufptr,agentaddr)
int buflen;
caddr_t bufptr;
struct in_addr *agentaddr;
{

	struct memberentry *memptr;
	u_long *keyptr;
	struct groupargs fillinargs;
	struct GroupRecord *group;
#ifdef	AGENTDEBUG
printf("UpdateMembership()\n");
#endif	AGENTDEBUG
	while (buflen > 0) {
	    memptr = (struct memberentry *) bufptr;

	    fillinargs.key1 = ntohl(memptr->key1);
	    fillinargs.key2 = ntohl(memptr->key2);
	    fillinargs.groupaddr.s_addr = 0xe0000000 |
		(ntohl(memptr->groupaddr.s_addr) & IN_CLASSD_MASK);
#ifdef	AGENTDEBUG
printf("\taddr = 0x%x, key1 = %d, key2 = %d\n",
    fillinargs.groupaddr.s_addr, fillinargs.key1,fillinargs.key2);
#endif	AGENTDEBUG
	    buflen -= sizeof(struct memberentry);
	    memptr++;

	    /* See if we already know about this group */

	    group = GetGroup(&fillinargs.groupaddr);
	    if (group == NULL) {
#ifdef	AGENTDEBUG
printf("\tAdding group\n");
#endif	AGENTDEBUG

		/* If we didn't know about this group before, add it */

	        if ((group = AddGroup(&fillinargs)) == NULL) continue;
	    }

	    /* Associate agent with this group, if it passes all tests */

	    if (((fillinargs.key1 == 0 && fillinargs.key2 == 0)) ||
	        ((fillinargs.key1 >= group->key1) ||
	        ((fillinargs.key1 == group->key1) &&
	         (fillinargs.key2 >= group->key2)))) {

#ifdef	AGENTDEBUG
printf("\tAdding agent\n");
#endif	AGENTDEBUG
	        AddAgent(group,agentaddr);

	        if ((fillinargs.key1 != 0) || (fillinargs.key2 != 0)) {
		    group->key1 = fillinargs.key1;
		    group->key2 = fillinargs.key2;
		}
	    }
	}
}

#define INTEGRAL_COPYLEN	(MLEN - (MLEN % sizeof(struct memberentry)))

groupioctl(so,cmd, data)
struct socket *so;
int cmd;
caddr_t data;
{
    struct sockaddr_in addr;
    struct GroupRecord *group;
    struct groupargs *argsptr,fillinargs;
    struct attachedcell *net;
    struct ifaddr *ifaddress;
    struct in_ifaddr *inifaddr;
    struct in_addr agentgroup;
    struct memberupdate *updateptr;
    struct mbuf *m;
    caddr_t usrbufptr,bufptr;
    u_long flag32;
    u_char rc;
    int length;
    int s = splsoftclock();

    if (!suser()) {
	splx(s);
	return (u.u_error);
    }

    if ((data) && (cmd == SIOCMEMUPDATE)) {

#ifdef	AGENTDEBUG
printf("groupioctl:SIOCMEMUPDATE\n");
#endif	AGENTDEBUG

	updateptr = (struct memberupdate *) data;
	length = updateptr->length;
	usrbufptr = updateptr->bufferptr;

	agentgroup.s_addr = INADDR_MA_GROUP;
	group = GetGroup(&agentgroup);
	updateptr->agent.s_addr = ntohl(updateptr->agent.s_addr);

	/* If this agent is not in the multicast agents group, */
	/* don't believe this update message */

	if (GetAgent(group,&agentgroup) == NULL) return(0);

	m = m_get(M_DONTWAIT, MT_DATA);
	if (m == NULL) {
	    splx(s);
	    return(ENOBUFS);
	}

	m->m_len = INTEGRAL_COPYLEN;
	bufptr = mtod(m,caddr_t);

	/* While the update buffer > INTEGRAL_COPYLEN, */
	/* copy it in in INTEGRAL_COPYLEN chunks */

	while (length > INTEGRAL_COPYLEN) {
	    copyin(usrbufptr, bufptr, INTEGRAL_COPYLEN);
	    length -= INTEGRAL_COPYLEN;
	    usrbufptr += INTEGRAL_COPYLEN;

	    UpdateMembership(INTEGRAL_COPYLEN, bufptr, &updateptr->agent);
	}

	/* Copy the last chunk in */

	m->m_len = length;
	bufptr = mtod(m,caddr_t);

#ifdef	AGENTDEBUG
printf("groupioctl: copying in %d bytes\n",length);
#endif	AGENTDEBUG

	copyin(usrbufptr, bufptr, length);
	UpdateMembership(length, bufptr, &updateptr->agent);

	if (m) m_free(m);
	splx(s);
	return(0);
    }

    if ((data) && (cmd == SIOCGETMEMBERSHIP)) {
	updateptr = (struct memberupdate *) data;
	bufptr = (caddr_t) (updateptr->bufferptr);
	length = updateptr->length;

#ifdef	AGENTDEBUG
printf("groupioctl: SIOCGETMEMBERSHIP\n");
#endif	AGENTDEBUG

	/* Go through all the GroupRecords and copyout an entry */
	/* for each one that has either local members or that I */
	/* belong to */

	for (group = grouprecordhead.next; 
	     group != &grouprecordhead; group = group->next) {
#ifdef	AGENTDEBUG
printf("\tfor loop\n");
#endif	AGENTDEBUG

	    if (group->attachednetlist || (group->flags & I_BELONG)) {
#ifdef	AGENTDEBUG
printf("\t\tnetlist = 0x%x, flags = 0x%x\n",group->attachednetlist,group->flags);
#endif	AGENTDEBUG
		if ((group->key1 != 0) || (group->key2 != 0)) {
		    if (length < sizeof(struct memberentry)) {
		        /* Buffer is not big enough */
		        updateptr->length = -1;
#ifdef	AGENTDEBUG
printf("\t\tError: Buffer too small\n");
#endif	AGENTDEBUG
			splx(s);
		        return(0);
		    }
#ifdef	AGENTDEBUG
printf("\t\tNON-zero keys.  Copying out a struct memberentry\n");
#endif	AGENTDEBUG
		    group->groupaddr.s_addr = htonl(group->groupaddr.s_addr);
		    group->key1 = htonl(group->key1);
		    group->key2 = htonl(group->key2);

		    copyout(&group->groupaddr, bufptr, sizeof(struct memberentry));

		    group->groupaddr.s_addr = ntohl(group->groupaddr.s_addr);
		    group->key1 = ntohl(group->key1);
		    group->key2 = ntohl(group->key2);

		    length -= sizeof(struct memberentry);
		    bufptr += sizeof(struct memberentry);
		}
		else {
		    if (length < sizeof(struct in_addr)) {
		        /* Buffer is not big enough */
		        updateptr->length = -1;
#ifdef	AGENTDEBUG
printf("\t\tError: Buffer too small\n");
#endif	AGENTDEBUG
			splx(s);
		        return(0);
		    }
		    group->groupaddr.s_addr &= ~NON_ZERO_KEY;
		    group->groupaddr.s_addr = htonl(group->groupaddr.s_addr);
#ifdef	AGENTDEBUG
printf("\t\tZERO keys.  Copying out a struct in_addr\n");
#endif	AGENTDEBUG
		    copyout(&group->groupaddr, bufptr, sizeof(struct in_addr));

		    group->groupaddr.s_addr = ntohl(group->groupaddr.s_addr);
		    group->groupaddr.s_addr |= NON_ZERO_KEY;

		    length -= sizeof(struct in_addr);
		    bufptr += sizeof(struct in_addr);
		}
	    }
	}
	updateptr->length -= length;  /* Final length of update buffer, */
#ifdef	AGENTDEBUG
printf("\tout of for loop.  Length is %d\n",updateptr->length);
#endif	AGENTDEBUG
	splx(s);
	return(0);
    }

    if ((data) && ((cmd != SIOCMEMUPDATE) || (cmd != SIOCGETMEMBERSHIP))) {
	argsptr = (struct groupargs *) data;
	argsptr->groupaddr.s_addr = ntohl(argsptr->groupaddr.s_addr);
	argsptr->key1 = ntohl(argsptr->key1);
	argsptr->key2 = ntohl(argsptr->key2);
	argsptr->agentaddr.s_addr = ntohl(argsptr->agentaddr.s_addr);
	argsptr->returncode = IGMP_RC_UNSET;
    }

    switch(cmd) {
	case SIOCAGENTINIT:
	    rc = InitMulticastAgent(so);
	    splx(s);
	    return(rc);

	case SIOCSETGROUPRANGE:

	/* Set the range of transient group addresses */
	/* to be allocated by this agent.             */

	    if (IN_CLASSD(argsptr->groupaddr.s_addr) &&
		IN_CLASSD(argsptr->agentaddr.s_addr) &&
	        argsptr->groupaddr.s_addr < argsptr->agentaddr.s_addr) {

		minalloc = argsptr->groupaddr.s_addr;
		maxalloc = argsptr->agentaddr.s_addr;
		lastalloc = minalloc + (random() % (maxalloc - minalloc + 1));

		argsptr->returncode = IGMP_REQUEST_GRANTED;
	    }
	    else argsptr->returncode = IGMP_INVALID_GROUP_ADDRESS;
	    break;
		
	case SIOCADDGROUP:
#ifdef	AGENTDEBUG
	    printf("case SIOCADDGROUP\n");
#endif	AGENTDEBUG
	    if (lastalloc == 0) {
		argsptr->returncode = IGMP_NO_RESOURCES;
		break;
	    }

	    argsptr->groupaddr.s_addr = lastalloc;

	    do {
		if (++(argsptr->groupaddr.s_addr) > maxalloc)
		       argsptr->groupaddr.s_addr = minalloc;
	    } while ((group = GetGroup(&argsptr->groupaddr)) != NULL &&
		     argsptr->groupaddr.s_addr != lastalloc);

	    if (group != NULL || (group = AddGroup(argsptr)) == NULL) {
		argsptr->returncode = IGMP_NO_RESOURCES;
		break;
	    }

	    lastalloc = argsptr->groupaddr.s_addr;

	    addr.sin_family = AF_INET;
	    addr.sin_addr.s_addr = argsptr->netaddr.s_addr;

#ifdef	AGENTDEBUG
printf("groupioctl: source address is 0x%x\n",argsptr->netaddr.s_addr);
#endif	AGENTDEBUG

	    /* If source is from an attached net */
	    if (ifaddress = ifa_ifwithnet((struct sockaddr *)&addr)) {

#ifdef	AGENTDEBUG
printf("groupioctl: ADDGROUP: from local net\n");
#endif	AGENTDEBUG

		/* See if it's from me */

		for (inifaddr = in_ifaddr; inifaddr; 
		     inifaddr = inifaddr->ia_next) {
	    		if (argsptr->netaddr.s_addr == 
	    		    IA_SIN(inifaddr)->sin_addr.s_addr) {
#ifdef	AGENTDEBUG
printf("groupioctl: ADDGROUP: from me\n");
#endif	AGENTDEBUG
				group->flags |= I_BELONG;
	    			argsptr->returncode = IGMP_SEND_UPDATE;
				splx(s);
	    			return(0);
	    		}
		}
	        argsptr->returncode = AddAttachedNet(group,ifaddress->ifa_ifp);
	    	if (argsptr->returncode == IGMP_REQUEST_GRANTED)
	    	    argsptr->returncode = IGMP_SEND_UPDATE;
		break;
	    }
	    else argsptr->returncode = IGMP_NO_REPLY;
	    break;
	   
	case SIOCDELGROUP:

#ifdef	AGENTDEBUG
	    printf("case SIOCDELGROUP\n");
#endif	AGENTDEBUG
	    DelGroup(&argsptr->groupaddr);
	    break;

	case SIOCINCRGROUP:

#ifdef	AGENTDEBUG
	    printf("case SIOCINCRGROUP\n");
#endif	AGENTDEBUG
	    group = GetGroup(&argsptr->groupaddr);
	    if (group == NULL) {
		argsptr->returncode = IGMP_INVALID_GROUP_ADDRESS;
		break;
	    }
	    if ((group->key1 != argsptr->key1) ||
		(group->key2 != argsptr->key2)) {
		argsptr->returncode = IGMP_INVALID_ACCESS_KEY;
		break;
	    } 
	    addr.sin_family = AF_INET;
	    addr.sin_addr.s_addr = argsptr->netaddr.s_addr;
#ifdef	AGENTDEBUG
printf("groupioctl INCRGROUP: source address = 0x%x\n",argsptr->netaddr.s_addr);
#endif	AGENTDEBUG

	    /* If source is me */
	    for (inifaddr = in_ifaddr; inifaddr;inifaddr = inifaddr->ia_next) {
	    	if (argsptr->netaddr.s_addr == 
	    	    IA_SIN(inifaddr)->sin_addr.s_addr) {
#ifdef	AGENTDEBUG
printf("groupioctl: INCRGROUP: from me\n");
#endif	AGENTDEBUG
			/* See if it's from me */

			group->flags |= I_BELONG;
			if(group->attachednetlist == NULL)
	    		    argsptr->returncode = IGMP_SEND_UPDATE;
			else
	    		    argsptr->returncode = IGMP_REQUEST_GRANTED;
			splx(s);
	    		return(0);
	    	}
	    }

	    /* If source is from an attached net */
	    if (ifaddress = ifa_ifwithnet((struct sockaddr *)&addr)) {
#ifdef	AGENTDEBUG
printf("groupioctl: INCRGROUP: from attached net\n");
#endif	AGENTDEBUG
	        net = GetAttachedNet(group,ifaddress->ifa_ifp);
	        if (net == NULL) { 
	            argsptr->returncode = 
		        AddAttachedNet(group,ifaddress->ifa_ifp);
	            if (argsptr->returncode == IGMP_REQUEST_GRANTED)
	    	        argsptr->returncode = IGMP_SEND_UPDATE;
		    break;
		}
	        else {
		    net->confirmtimer = MULTICAST_AGENT_CONFIRM_RESET;
		}
	        argsptr->returncode = IGMP_REQUEST_GRANTED;
	    }
	    else argsptr->returncode = IGMP_NO_REPLY;
	    break;

	case SIOCDECRGROUP:

#ifdef	AGENTDEBUG
	    printf("case SIOCDECRGROUP\n");
#endif	AGENTDEBUG
	    group = GetGroup(&argsptr->groupaddr);
	    if (group == NULL) {
		argsptr->returncode = IGMP_INVALID_GROUP_ADDRESS;
		break;
	    }
	    if((group->key1 != argsptr->key1)||(group->key2 != argsptr->key2)) {
		argsptr->returncode = IGMP_INVALID_ACCESS_KEY;
		break;
	    }
	    addr.sin_family = AF_INET;
	    addr.sin_addr.s_addr = argsptr->netaddr.s_addr;

	    /* If source is me */
	    for (inifaddr = in_ifaddr; inifaddr;inifaddr = inifaddr->ia_next) {
	    	if (argsptr->netaddr.s_addr == 
	    	    IA_SIN(inifaddr)->sin_addr.s_addr) {
#ifdef	AGENTDEBUG
printf("groupioctl: DECRGROUP: from me\n");
#endif	AGENTDEBUG
			group->flags &= ~I_BELONG;
	    		argsptr->returncode = IGMP_REQUEST_GRANTED;
			splx(s);
	    		return(0);
	    	}
	    }

	    if (ifaddress = ifa_ifwithnet((struct sockaddr *)&addr))
	        argsptr->returncode = IGMP_REQUEST_GRANTED;
	    else 
	        argsptr->returncode = IGMP_NO_REPLY;
	    break;

	case SIOCADDAGENT:

#ifdef	AGENTDEBUG
	    printf("case SIOCADDAGENT\n");
printf("groupaddr = 0x%x, agentaddr = 0x%x\n",argsptr->groupaddr.s_addr,
	argsptr->agentaddr.s_addr);
#endif	AGENTDEBUG
	    /* If agent address is mine */
	    for (inifaddr = in_ifaddr; inifaddr; inifaddr = inifaddr->ia_next) {
	    	if (htonl(argsptr->agentaddr.s_addr) == 
	    	    IA_SIN(inifaddr)->sin_addr.s_addr) {
			argsptr->returncode = IGMP_NOT_REMOTE;
			splx(s);
			return(0);
		}
	    }
	    group = GetGroup(&argsptr->groupaddr);
	    if (group)
	        argsptr->returncode = AddAgent(group,&argsptr->agentaddr);
	    else
		argsptr->returncode = IGMP_INVALID_GROUP_ADDRESS;
	    break;

	case SIOCDELAGENT:

#ifdef	AGENTDEBUG
	    printf("case SIOCDELAGENT\n");
#endif	AGENTDEBUG
	    group = GetGroup(&argsptr->groupaddr);
	    if (group)
	        argsptr->returncode = DelAgent(group,&argsptr->agentaddr);
	    else
		argsptr->returncode = IGMP_INVALID_GROUP_ADDRESS;
	    break;

	case SIOCCONFIRMGROUP:

#ifdef	AGENTDEBUG
	    printf("case SIOCCONFIRMGROUP\n");
#endif	AGENTDEBUG
	    group = GetGroup(&argsptr->groupaddr);

	    if (group == NULL) {
		fillinargs.groupaddr.s_addr = argsptr->groupaddr.s_addr;
		fillinargs.key1 = fillinargs.key2 = 0;
		if ((group = AddGroup(&fillinargs)) == NULL) {
		    argsptr->returncode = IGMP_NO_RESOURCES;
		    break;
		}
		argsptr->returncode = IGMP_SEND_UPDATE;
	    }

	    if (((group->key1 == 0) && (group->key2 == 0)) ||
	        ((group->key1 == argsptr->key1) &&
		 (group->key2 == argsptr->key2))) {

	        addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = argsptr->netaddr.s_addr;
		ifaddress = ifa_ifwithnet((struct sockaddr *)&addr);

		if (net = GetAttachedNet(group,ifaddress->ifa_ifp)) {
	            net->confirmtimer = MULTICAST_AGENT_CONFIRM_RESET;
		    if (argsptr->returncode != IGMP_SEND_UPDATE)
	                argsptr->returncode = IGMP_REQUEST_GRANTED;
		}
		else {
	            rc = AddAttachedNet(group,ifaddress->ifa_ifp);

		    if (rc != IGMP_REQUEST_GRANTED) argsptr->returncode = rc;
		    else if (argsptr->returncode != IGMP_SEND_UPDATE)
			argsptr->returncode = IGMP_REQUEST_GRANTED;
		} 
	        ((struct igmpcb *) (agentsocket->so_pcb))->ifp = ifaddress->ifa_ifp;
	    }
	    else argsptr->returncode = IGMP_INVALID_ACCESS_KEY;
	    break;

	case SIOCADDPERMGROUP:

	    if ((group = GetGroup(&argsptr->groupaddr)) != NULL) {
	        group->flags |= PERMANENT_GROUP;
	    }
	    else {
	        group = AddGroup(argsptr);
	        group->flags = PERMANENT_GROUP;
	    }
	    argsptr->returncode = IGMP_REQUEST_GRANTED;
	    break;

	default:
#ifdef	AGENTDEBUG
	    printf("default\n");
#endif	AGENTDEBUG
	    splx(s);
	    return (EINVAL);
    }
    splx(s);
    return(0);
}

#endif	MULTICAST_AGENT
