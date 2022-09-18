/*
 *  krt_ipmulticast.c,v 1.6 1993/12/02 03:23:04 jch Exp
 */

/* Gated Release 3.5 */
/* Copyright (c) 1990,1991,1992,1993,1994,1995 by Cornell University.  All */
/* rights reserved.  Refer to Particulars and other Copyright notices at */
/* the end of this file.  */
/*  */


#define	INCLUDE_IOCTL
#define	INCLUDE_ROUTE
#define	INCLUDE_MROUTE
#define	INCLUDE_IF
#include "include.h"

#ifdef	IP_MULTICAST

#include "inet.h"
#include "inet_multi.h"
#include "krt.h"
#include "krt_var.h"
#include "krt_ipmulti.h"
#include "igmp.h"

typedef struct _krt_multicast_entry {
    struct _krt_multicast_entry *kme_forw;
    struct _krt_multicast_entry *kme_back;
    flag_t kme_flags;
#define	KMEF_INSTALLED	0x01		/* We installed it in the kernel */
#define	KMEF_EXISTS	0x02		/* Not installed by us */
    flag_t kme_refcount;
    sockaddr_un *kme_group;
    sockaddr_un *kme_router;		/* Router it is installed with */
} krt_multicast_entry;

static krt_multicast_entry krt_multicast_entries = { &krt_multicast_entries, &krt_multicast_entries } ;

#define	KRT_MC(p)	{ for (p = krt_multicast_entries.kme_forw; p != & krt_multicast_entries; p = p->kme_forw)
#define	KRT_MC_END(p)	if (p == &krt_multicast_entries) p = (krt_multicast_entry *) 0; }


static const bits krt_multicast_bits[] = {
    { KMEF_INSTALLED,	"Installed" },
    { KMEF_EXISTS,	"Exists" },
    { 0,		NULL }
} ;


/**/

/* The Deering multicast mods for the kernel require the existence of */
/* a default route (0.0.0.0), a default multicast route (224.0.0.0) or */
/* a specific multicast route to determine the default interface. */
/* This information is ignored since we explicitly set our interface */
/* when sending the packets, but lack of this information would prevent */
/* us from sending to the multicast address.  To work around this we */
/* add our two multicast addresses to the routing table pointing at the */
/* loopback interface.  If these were ever actually used we would get */
/* an error because the loopback interface does not support multicast, */
/* but since we do specify the interface before sending packets this */
/* should *never* happen.  */
	
block_t krt_mc_block = 0;


static krt_multicast_entry *
krt_multicast_create __PF1(group, sockaddr_un *)
{
    krt_multicast_entry *kp;

    if (!krt_mc_block) {
	krt_mc_block = task_block_init(sizeof (*kp), "krt_multicast_entry");
    }

    kp = (krt_multicast_entry *) task_block_alloc(krt_mc_block);
    INSQUE(kp, krt_multicast_entries.kme_back);

    kp->kme_group = sockdup(group);

    return kp;
}


static void
krt_multicast_request __PF2(type, u_int,
			    kp, krt_multicast_entry *)
{
    krt_parms parms;
    if_addr *ifap = (if_addr *) 0;
    sockaddr_un *router;

    parms.krtp_n_gw = 1;
    parms.krtp_state = 0;
    parms.krtp_protocol = RTPROTO_ANY;
    parms.krtp_ifaps = &ifap;
    parms.krtp_routers = &router;
    
    switch (type) {
    case RTM_ADD:
	router = inet_addr_loopback;
	(void) krt_change(krt_task,
			  kp->kme_group,
			  inet_mask_host,
			  (krt_parms *) 0,
			  &parms);

	BIT_SET(kp->kme_flags, KMEF_INSTALLED);
	BIT_RESET(kp->kme_flags, KMEF_EXISTS);
	break;

    case RTM_DELETE:
	router = kp->kme_router ? kp->kme_router : inet_addr_loopback;
	(void) krt_change(krt_task,
			  kp->kme_group,
			  inet_mask_host,
			  &parms,
			  (krt_parms *) 0);

	BIT_RESET(kp->kme_flags, KMEF_INSTALLED|KMEF_EXISTS);
	break;

    default:
	assert(FALSE);
    }

    if (kp->kme_router) {
	sockfree(kp->kme_router);
	kp->kme_router = (sockaddr_un *) 0;
    }
}


static void
krt_multicast_free __PF1(kp, krt_multicast_entry *)
{
    if (BIT_TEST(kp->kme_flags, KMEF_INSTALLED)) {
	krt_multicast_request(RTM_DELETE, kp);
    }
		
    REMQUE(kp);

    sockfree(kp->kme_group);
    task_block_free(krt_mc_block, (void_t) kp);
}


void
krt_multicast_add __PF1(group, sockaddr_un *)
{
    krt_multicast_entry *kp;

    KRT_MC(kp) {
	if (sockaddrcmp(group, kp->kme_group)) {
	    break;
	}
    } KRT_MC_END(kp);

    if (kp) {
	/* Exists */

	if (BIT_TEST(kp->kme_flags, KMEF_EXISTS)) {
	    /* Already exists in kernel */

	    /* Delete and reinstall the way we want it */
	    krt_multicast_request(RTM_DELETE, kp);
	    krt_multicast_request(RTM_ADD, kp);
	}
    } else {
	/* Allocate a new one */
	kp = krt_multicast_create(group);

	/* Install it in kernel */
	krt_multicast_request(RTM_ADD, kp);
    }

    kp->kme_refcount++;
}


void
krt_multicast_delete __PF1(group, sockaddr_un *)
{
    krt_multicast_entry *kp;

    KRT_MC(kp) {
	if (sockaddrcmp(group, kp->kme_group)) {
	    /* Found it */

	    if (!--kp->kme_refcount) {
		/* Last reference, remove it */

		krt_multicast_free(kp);
	    }
	    break;
	}
    } KRT_MC_END(kp);
}


int
krt_multicast_install __PF2(group, sockaddr_un *,
			    router, sockaddr_un *)
{
    krt_multicast_entry *kp;

    KRT_MC(kp) {
	if (sockaddrcmp(group, kp->kme_group)) {
	    if (BIT_TEST(kp->kme_flags, KMEF_EXISTS)) {
		/* Delete duplicate entries */

		return TRUE;
	    }

	    kp->kme_router = sockdup(router);
	    if (kp->kme_refcount) {
		/* One of ours, fix the router */

		krt_multicast_request(RTM_DELETE, kp);
		krt_multicast_request(RTM_ADD, kp);
	    }

	    return FALSE;
	}
    } KRT_MC_END(kp);

    kp = krt_multicast_create(group);

    kp->kme_router = sockdup(router);
    BIT_SET(kp->kme_flags, KMEF_EXISTS);

    return FALSE;
}


#ifdef	RTM_CHANGE
void
krt_multicast_change __PF2(type, int,
			   rtp, rt_parms *)
{
    krt_multicast_entry *kp;
    
    KRT_MC(kp) {
	if (sockaddrcmp(rtp->rtp_dest, kp->kme_group)) {
	    break;
	}
    } KRT_MC_END(kp);

    switch (type) {
    case RTM_DELETE:
    case RTM_OLDDEL:
	if (kp->kme_refcount) {
	    /* We are using this, force it to be reinstalled */

	    krt_multicast_request(RTM_ADD, kp);
	} else {
	    /* We are not using it, release it */

	    krt_multicast_free(kp);
	}
	break;

    case RTM_ADD:
    case RTM_OLDADD:
	krt_multicast_install(rtp->rtp_dest, rtp->rtp_router);
	break;

    case RTM_CHANGE:
	if (kp) {
	    if (kp->kme_refcount > 1) {
		/* We are using this, don't let it change */
		
		krt_multicast_request(RTM_DELETE, kp);
		krt_multicast_request(RTM_ADD, kp);
	    }
	} else {
	    /* We don't yet know about it */

	    krt_multicast_install(rtp->rtp_dest, rtp->rtp_router);
	}
	break;

    default:
	/* Ignore */
	break;
    }
}
#endif	/* RTM_CHANGE */


void
krt_multicast_dump __PF2(tp, task *,
			 fd, FILE *)
{
    if (krt_multicast_entries.kme_forw != &krt_multicast_entries) {
	krt_multicast_entry *kp;
	
	(void) fprintf(fd, "\tIP Multicast default interfaces:\n");

	KRT_MC(kp) {
	    (void) fprintf(fd, "\t\t%-15A\trefcount %d  flags <%s>\n",
			   kp->kme_group,
			   kp->kme_refcount,
			   trace_bits(krt_multicast_bits, kp->kme_flags));
	} KRT_MC_END(kp) ;

	(void) fprintf(fd, "\n");
    }
}

/*
 * This routine will request the kernel version of the multicast
 * forwarding cache entry. It is useful when getting the use count
 * from the kernel.
 */

/*
 * krt_generate_mfc()
 *
 * Process a request to generate a Multicast Forwarding Cache entry.
 * Each multicast routing protocol that has registered a receive routine
 * will be asked to contribute to the outgoing interface list.
 *
 */

void
krt_generate_mfc __PF4(error, int,
		       dst, sockaddr_un *,
		       ifap, if_addr *,
		       src, sockaddr_un *)
{
    int		call = 0;
    mfc		*mfcp = (mfc *) 0;
    struct	krt_mfc_recv *recv_list;
    upstream	*up;

    switch (error) {
	case EADDRINUSE:

	    mfcp = mfc_locate_mfc(dst, src);
	    if (!mfcp) {
		trace_tp(krt_task,
		     TR_KRT_REQUEST,
		     0,
		     ("krt_generate_mfc: Can't locate mfc entry for group %A source %A",
		      dst,
		      src));
	    }
	    break;

	case EADDRNOTAVAIL:

	    trace_tp(krt_task,
		     TR_KRT_REQUEST,
		     0,
		     ("krt_generate_mfc: Multicast Forwarding Cache entry requested for group %A source %A",
		      dst,
		      src));
	    up = krt_locate_upstream(src, igmp_get_ifproto(ifap));
	    if (!up) {
		trace_tp(krt_task,
			 TR_KRT_REQUEST,
			 0,
			 ("krt_generate_mfc: No Multicast routing protocol configured on interface %A(%s). Deleting forwarding cache entry for group %A source %A",
			  ifap->ifa_addr,
			  ifap->ifa_link->ifl_name,
			  dst,
			  src));
		(void) krt_delete_cache(dst, src);

	    } else if (up->ifap) {
		mfcp = mfc_alloc_node();
		mfcp->upstream_ifap = up->ifap;
		mfcp->mfc_src = src->in.gin_addr.s_addr;
		mfcp->mfc_ctime = time_sec;
		mfcp->mfc_rtime = time_sec;
		mfcp->mfc_use = 1;
		mfcp->mfc_lastuse = 0;
		mfcp->mfc_proto = 0;
		mfcp->mfc_callback = (void *) 0;
		mfcp->prune_up = (prune_list *) 0;
		mfcp->prune_down.if_forw = &mfcp->prune_down;
		mfcp->prune_down.if_back = &mfcp->prune_down;
		mfcp->pim_assert = (assert_list *) 0;
		mfcp->msl = (mfc_src_list *) 0;
		mfcp->rpf_addr = 0;
		mfcp->ds_count = 0;
		mfcp->ds = mfc_alloc_downstream();
		mfcp->ds->forw = mfcp->ds->back = mfcp->ds;
		    /*
		     * Fill in the downstream interface list by merging
		     * the list from all multicast routing protocols below
		     */

		call++;
	    } else {
		trace_tp(krt_task,
			 TR_KRT_REQUEST,
			 0,
			 ("krt_generate_mfc: No unicast route back to source. Deleting forwarding cache entry for group %A source %A",
			  dst,
			  src));
		(void) krt_delete_cache(dst, src);
	    }
	    break;
	default:
	    trace_tp(krt_task,
		     TR_KRT_REQUEST,
		     0,
		     ("krt_generate_mfc: Unknown error type: %s",
		      strerror(error)));
	    break;
    }

    if (call) {

	if (error == EADDRNOTAVAIL) {
		/*
		 * insert cache entry in multicast tree of trees
		 */
	    if (mfc_add_node(dst, mfcp))
		return;

	}

	MFC_RECV_SCAN(recv_list, &krt_mfc_recv_head) {
	    if (recv_list->errno == error) {
		(*recv_list->recv_routine)(error, ifap, mfcp);
	    }
	} MFC_RECV_SCAN_END(recv_list, &krt_mfc_recv_head);
	if (error == EADDRNOTAVAIL) {
		/*
		 * resolve kernel forwarding cache entry
		 */
	    krt_resolve_cache(dst, src, mfcp);
	}
    }
}

    /*
     * This structure element changed names between the
     * Xerox IP Multicast 3.3 release and the 3.5 release.
     * If running 3.3, make it backward compatible.
     */
#ifndef	MRT_ASSERT
#define pktcnt	count
#endif	/* MRT_ASSERT */

int
krt_request_cache(mfcp, callback)
mfc *mfcp;
_PROTOTYPE(callback,
	   void,
	   (mfc *));
{
    int error = 0;
    static struct sioc_sg_req req;
    task *tp = igmp_lookup_task();

    req.grp.s_addr = mfcp->mfc_group->group_key;
    req.src.s_addr = mfcp->mfc_src;

    error = task_ioctl(tp->task_socket,
		       SIOCGETSGCNT,
		       (void_t) &req,
		       sizeof(struct sioc_sg_req));

    if (req.pktcnt == 0xffffffff) {
	error++;
    } else {
	    /*
	     * update use counts in cache entry
	     */
	mfcp->mfc_lastuse = mfcp->mfc_use;
	mfcp->mfc_use = req.pktcnt;
	    /*
	     * notify the calling protocol
	     */
	(*callback)(mfcp);
    }

    return(error);
}


int
krt_delete_cache  __PF2(dst, sockaddr_un *,
			src, sockaddr_un *)
{
    int error = 0;
    task *tp = igmp_lookup_task();
#ifdef	MRT_ASSERT
    struct mfcctl mc;
#else	/* MRT_ASSERT */
    struct delmfcctl mc;
#endif	/* MRT_ASSERT */

    if (TRACE_TP(krt_task, TR_KRT_REQUEST)) {
	trace_tp(krt_task,
		 TR_KRT_REQUEST,
		 0,
		 ("KRT SEND DELETE group %-15A source %-15A", dst, src));
    }

    mc.mfcc_origin.s_addr = sock2ip(src);
    mc.mfcc_mcastgrp.s_addr = sock2ip(dst);

    if ((error = task_set_option(tp, TASKOPTION_DEL_MFC, &mc)) < 0) {
	trace_tp(krt_task,
		 TR_KRT_REQUEST,
		 0,
		 ("krt_delete_cache: %s", strerror(errno)));
    }

    return(error);
}

void
krt_resolve_cache  __PF3(dst, sockaddr_un *,
			 src, sockaddr_un *,
			 mfcp, mfc *)
{
    int i;
    u_long last_addr = 0;
    downstream *dsp;
    struct mfcctl mc;
    task *tp = igmp_lookup_task();

    if (!mfcp->upstream_ifap) {
	trace_tp(krt_task,
		 TR_KRT_REQUEST,
		 0,
		 ("krt_resolve_cache: upstream interface not specified"));
	return;
    }

    if (TRACE_TP(krt_task, TR_KRT_REQUEST)) {
	trace_tp(krt_task,
		 TR_KRT_REQUEST,
		 0,
		 ("KRT SEND ADD    group %-15A source %-15A", dst, src));
    }

    mc.mfcc_origin.s_addr = sock2ip(src);
#ifndef	MRT_ASSERT
	/*
	 * If we are using the Xerox IP Multicast 3.5 distribution,
	 * there is no originmask since it is already assumed to be
	 * host specific.
	 */
    mc.mfcc_originmask.s_addr = sock2ip(inet_mask_host);
#endif	/* MRT_ASSERT */
    mc.mfcc_mcastgrp.s_addr = sock2ip(dst);
    mc.mfcc_parent = mfcp->upstream_ifap->ifa_vif;

    for (i = 0; i < MAXVIFS; i++)
	mc.mfcc_ttls[i] = 0;
    last_addr = 0;
    DOWNSTREAM_LIST(dsp, mfcp->ds) {
	if (sock2ip(dsp->ds_addr) != last_addr) {
	    mc.mfcc_ttls[dsp->ds_ifindex] = 1;
	}
	last_addr = sock2ip(dsp->ds_addr);
    } DOWNSTREAM_LIST_END(dsp, mfcp->ds);

    if (task_set_option(tp, TASKOPTION_ADD_MFC, &mc) < 0) {
	trace_tp(krt_task,
		 TR_KRT_REQUEST,
		 0,
		 ("krt_resolve_cache: %s", strerror(errno)));
    }
}

void
krt_add_vif  __PF4(ifap, if_addr *,
		   remote, sockaddr_un *,
		   threshold, u_int32,
		   ratelimit, u_int32)
{
    igmp_add_vif(ifap, remote, threshold, ratelimit);
}

void
krt_del_vif  __PF1(ifap, if_addr *)
{
    igmp_del_vif(ifap);
}

#endif	/* IP_MULTICAST */
