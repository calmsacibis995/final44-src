/*
 *  $Id: krt_ipmulti_rtsock.c,v 1.1 1995/01/26 07:52:05 pusateri Exp $
 */

/*%Copyright%*/


#define	INCLUDE_IF
#define	INCLUDE_IOCTL
#define	INCLUDE_ROUTE
#include "include.h"

#ifdef	IP_MULTICAST

#include "inet.h"
#include "inet_multi.h"
#include "krt.h"
#include "krt_var.h"
#include "krt_ipmulti.h"


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
	    if (mfcp) {
		    /*
		     * This should never happen
		     */
		if (mfcp->upstream_ifap == ifap) {
		    trace_tp(krt_task,
			TR_KRT_REQUEST,
			0,
			("krt_generate_mfc: Kernel and Gated disagree on correct interface for packet from %A to group %A arriving on interface %A",
			  dst,
			  src,
			  ifap->ifa_addr));
		} else {
		    trace_tp(krt_task,
			 TR_KRT_REQUEST,
			 0,
			 ("krt_generate_mfc: Duplicate packet arrived for group %A source %A via interface %A. Correct Interface was %A",
			  dst,
			  src,
			  ifap->ifa_addr,
			  mfcp->upstream_ifap->ifa_addr));
		    call++;
		}
	    } else {
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
			/*
			 * need to check for point to point case
			 */
		if (up->ifap != ifap) {
		    trace_tp(krt_task,
			TR_KRT_REQUEST,
			0,
			("krt_generate_mfc: Ignoring packet from %A to group %A arriving on incorrect interface %A expected interface %A(%s)",
			  dst,
			  src,
			  ifap->ifa_addr,
			  up->ifap->ifa_addr,
			  up->ifap->ifa_link->ifl_name));
		} else {
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
		}
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
 * This routine will request the kernel version of the multicast
 * forwarding cache entry. It is useful when getting the use count
 * from the kernel.
 */

int
krt_request_cache(mfcp, callback)
mfc *mfcp;
_PROTOTYPE(callback,
	   void,
	   (mfc *));
{
    int rc = 0;
    struct sockaddr *ap;
    struct sockaddr_dl ifpaddr;
    sockaddr_un dst, src;
    struct rt_msghdr *rtp;
    size_t size = sizeof *rtp;

    sockcopy(sockbuild_in(0, mfcp->mfc_group->group_key), &dst);
    sockcopy(sockbuild_in(0, mfcp->mfc_src), &src);
    bzero((caddr_t) &ifpaddr, sizeof(ifpaddr));
    ifpaddr.sdl_len = sizeof(ifpaddr);
    ifpaddr.sdl_family = AF_LINK;

    if (TRACE_TP(krt_task, TR_KRT_REQUEST)) {
	tracef("KERNEL %-6s group %-15A source %-15A",
	       trace_state(rtm_type_bits, RTM_GET - 1),
	       &dst,
	       &src);
    }

    rtp = (struct rt_msghdr *) task_mem_malloc(krt_task, size);
    bzero((caddr_t) rtp, size);

    rtp->rtm_addrs = 0;
    rtp->rtm_type = RTM_GET;
    rtp->rtm_version = RTM_VERSION;
    rtp->rtm_flags = RTF_MULTICAST | RTF_HOST;

    size += dst.in.gin_len;
    size += ifpaddr.sdl_len;
    size += src.in.gin_len;
    ap = (struct sockaddr *) (rtp + 1);

    bcopy((caddr_t) &dst, (caddr_t) ap, (size_t) dst.in.gin_len);
    RTM_ADDR(ap);
    BIT_SET(rtp->rtm_addrs, RTA_DST);

    bcopy((caddr_t) &ifpaddr, (caddr_t) ap, (size_t) ifpaddr.sdl_len);
    RTM_ADDR(ap);
    BIT_SET(rtp->rtm_addrs, RTA_IFP);

    bcopy((caddr_t) &src, (caddr_t) ap, (size_t) src.in.gin_len);
    RTM_ADDR(ap);
    BIT_SET(rtp->rtm_addrs, RTA_AUTHOR);

    rtp->rtm_msglen = (caddr_t) ap - (caddr_t) rtp;

    mfcp->mfc_callback = callback;

    /* If this is the first entry on the queue, run the queue */
    trace_tp(krt_task,
	     TR_KRT_REQUEST,
	     0,
	     (NULL));
    if (task_set_option(krt_task,
			TASKOPTION_USELOOPBACK,
			TRUE) < 0) {
	task_quit(errno);
    }
    rc =  krt_action(krt_task, rtp);
    if (task_set_option(krt_task,
			TASKOPTION_USELOOPBACK,
			FALSE) < 0) {
	task_quit(errno);
    }
    task_mem_free(krt_task, rtp);

    return (rc);
}

void
krt_resolve_cache  __PF3(dst, sockaddr_un *,
			 src, sockaddr_un *,
			 mfcp, mfc *)
{
    int count = 0;
    struct sockaddr *ap;
    struct rt_msghdr *rtp;
    flag_t flags = 0;
    size_t size = sizeof *rtp;
    sockaddr_un *handle = mfcp->upstream_ifap->ifa_link->ifl_handle;
    u_long last_addr = 0;
    downstream *dsp;
    caddr_t cp;

    if (!mfcp->upstream_ifap) {
	trace_tp(krt_task,
		 TR_KRT_REQUEST,
		 0,
		 ("krt_resolve_cache: upstream interface not specified"));
	return;
    }

    if (TRACE_TP(krt_task, TR_KRT_REQUEST)) {
	tracef("KERNEL %-6s group %-15A source %-15A",
	       trace_state(rtm_type_bits, RTM_CHANGE - 1),
	       dst,
	       src);
    }

    if (BIT_TEST(krt_options, KRT_OPT_NOINSTALL)) {
	trace_tp(krt_task,
		 TR_KRT_REQUEST,
		 0,
		 (NULL));

	return;
    }
    BIT_SET(flags, RTF_MULTICAST);
    BIT_SET(flags, RTF_HOST);

	/*
	 * count number of unique downstream interfaces
	 */
    DOWNSTREAM_LIST(dsp, mfcp->ds) {
	if (sock2ip(dsp->ds_addr) != last_addr)
	    count++;
    } DOWNSTREAM_LIST_END(dsp, mfcp->ds);

    if (count) {
	size += count * sizeof(struct ds_inaddr) +
		sizeof(struct sockaddr_inds);
    }

    size += dst->in.gin_len;
    size += ->sdl_len;
    size += src->in.gin_len;
    
    rtp = (struct rt_msghdr *) task_mem_malloc(krt_task, size);
    bzero((caddr_t) rtp, size);

    rtp->rtm_addrs = 0;
    rtp->rtm_type = RTM_CHANGE;
    rtp->rtm_version = RTM_VERSION;
    rtp->rtm_flags = flags;
    if (BIT_TEST(mfcp->upstream_ifap->ifa_state, IFS_UP)) {
	BIT_SET(rtp->rtm_flags, RTF_UP);
    }

    ap = (struct sockaddr *) (rtp + 1);

    bcopy((caddr_t) dst, (caddr_t) ap, (size_t) dst->in.gin_len);
    RTM_ADDR(ap);
    BIT_SET(rtp->rtm_addrs, RTA_DST);

    bcopy((caddr_t) handle, (caddr_t) ap, (size_t) handle->sdl_len);
    RTM_ADDR(ap);
    BIT_SET(rtp->rtm_addrs, RTA_IFP);

    bcopy((caddr_t) src, (caddr_t) ap, (size_t) src->in.gin_len);
    RTM_ADDR(ap);
    BIT_SET(rtp->rtm_addrs, RTA_AUTHOR);

    if (count) {
	struct sockaddr_inds *inds = (struct sockaddr_inds *) ap;
	struct ds_inaddr *ds_ia = (struct ds_inaddr *) inds->sin_data;

	inds->sin_len = count * sizeof(struct ds_inaddr) +
			 2 * sizeof(u_char) + sizeof(u_short);
	inds->sin_family = AF_INET;
	inds->sin_num = count;

	last_addr = 0;
	DOWNSTREAM_LIST(dsp, mfcp->ds) {
	    if (sock2ip(dsp->ds_addr) != last_addr) {
		ds_ia->sin_addr.s_addr = sock2ip(dsp->ds_addr);
		ds_ia->ttl = dsp->ds_ttl;
		ds_ia->flags = 0;
		ds_ia++;
	    }
	} DOWNSTREAM_LIST_END(dsp, mfcp->ds);

	RTM_ADDR(ap);
	BIT_SET(rtp->rtm_addrs, RTA_DOWNSTREAM);
    }

    rtp->rtm_msglen = (caddr_t) ap - (caddr_t) rtp;

    /* If this is the first entry on the queue, run the queue */
    trace_tp(krt_task,
	     TR_KRT_REQUEST,
	     0,
	     (NULL));
    (void) krt_action(krt_task, rtp);
    task_mem_free(krt_task, rtp);

    return;
}

int
krt_delete_cache  __PF2(dst, sockaddr_un *,
			src, sockaddr_un *)
{
    int rc = 0;
    struct sockaddr *ap;
    static union {
	struct rt_msghdr msg;
	u_char buf[sizeof (struct rt_msghdr) + 8 * 32];
    } u;
    struct rt_msghdr *rtp = &u.msg;
    flag_t flags = 0;
    size_t size = sizeof *rtp;

    if (TRACE_TP(krt_task, TR_KRT_REQUEST)) {
	tracef("KERNEL %-6s group %-15A source %-15A",
	       trace_state(rtm_type_bits, RTM_DELETE - 1),
	       dst,
	       src);
    }

    if (BIT_TEST(krt_options, KRT_OPT_NOINSTALL)) {
	trace_tp(krt_task,
		 TR_KRT_REQUEST,
		 0,
		 (NULL));

	return rc;
    }
    BIT_SET(flags, RTF_MULTICAST);
    BIT_SET(flags, RTF_HOST);

    size += dst->in.gin_len;
    size += src->in.gin_len;
    
    /* Allocate a block and clear it */
    assert(size < sizeof u);

    rtp->rtm_addrs = 0;
    rtp->rtm_type = RTM_DELETE;
    rtp->rtm_version = RTM_VERSION;
    rtp->rtm_flags = flags;

    ap = (struct sockaddr *) (rtp + 1);

    bcopy((caddr_t) dst, (caddr_t) ap, (size_t) dst->in.gin_len);
    RTM_ADDR(ap);
    BIT_SET(rtp->rtm_addrs, RTA_DST);

    bcopy((caddr_t) src, (caddr_t) ap, (size_t) src->in.gin_len);
    RTM_ADDR(ap);
    BIT_SET(rtp->rtm_addrs, RTA_AUTHOR);

    rtp->rtm_msglen = (caddr_t) ap - (caddr_t) rtp;

    /* If this is the first entry on the queue, run the queue */
    trace_tp(krt_task,
	     TR_KRT_REQUEST,
	     0,
	     (NULL));
    return krt_action(krt_task, rtp);
}

void
krt_add_vif  __PF4(ifap, if_addr *,
		   remote, sockaddr_un *,
		   threshold, u_int32,
		   ratelimit, u_int32)
{
	/*
	 * This kernel only needs to add a vif if its a tunnel
	 */
    if (remote) {
    }

	/*
	 * Warn that this kernel doesn't support rate limiting
	 */
    if (ratelimit) {
	trace_tp(krt_task,
	    TR_KRT_IFLIST,
	    0,
	    ("krt_add_vif: Kernel doesn't support rate limiting"));
    }

    return;
}

void
krt_del_vif  __PF1(ifap, if_addr *)
{
}

/* ARGSUSED */
void
krt_multicast_add __PF1(group, sockaddr_un *)
{
}

/* ARGSUSED */
void
krt_multicast_delete __PF1(group, sockaddr_un *)
{
}

#endif	/* IP_MULTICAST */
