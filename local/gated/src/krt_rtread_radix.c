/*
 *  $Id: krt_rtread_radix.c,v 1.7.2.8 1995/05/01 16:24:56 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_ROUTE
#define	INCLUDE_KVM
#define	INCLUDE_FILE
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#ifdef	PROTO_ISO
#include "iso.h"
#endif	/* PROTO_ISO */
#include "krt.h"
#include "krt_var.h"

u_long krt_radix_head;

/*
 * OSF/1 supports the BSD routing socket (the good news), but does not
 * support the getkerninfo system call (the bad news).  The radix tree
 * IS available, however, by groping through kernel memory (YUCK!).
 *
 */

/*
 * Read a socket from kernel memory
 */
static sockaddr_un *
krt_getaddr __PF2(tp, task *,
		  dst, struct sockaddr *)
{
    u_long data[32];
    struct sockaddr *sa = (struct sockaddr *) data;

    if (!dst) {
	return	(sockaddr_un *) 0;
    }

    if (KVM_READ(kd,
		 dst,
		 sa,
		 sizeof *sa) < 0) {
	trace_log_tp(tp,
		     0,
		     LOG_ERR,
		     ("krt_getaddr: reading address: %s",
		      KVM_GETERR(kd, "kvm_read error")));
	return (sockaddr_un *) 0;
    }

    if (sa->sa_len > sizeof *sa) {
	if (KVM_READ(kd,
		     dst,
		     (u_char *) sa + sizeof *sa,
		     sa->sa_len - sizeof *sa) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_getaddr: reading address: %s",
			  KVM_GETERR(kd, "kvm_read error")));
	    return (sockaddr_un *) 0;
	}
    } else if (sa->sa_len < 2) {
	/* We have a null address */

	return (sockaddr_un *) 0;
    }

    /*
     * OK, now we have the sockaddr, copy it, and return it!
     */
    return sock2gated(sa, unix_socksize(sa));
}

struct krt_mask {
    struct sockaddr *km_addr;		/* Kernel address of mask */
    sockaddr_un *km_mask;		/* Gated's mask */
} ;

struct krt_mask_list {
    struct krt_mask_list *kml_next;
    struct krt_mask *kml_fill;
    struct krt_mask kml_masks[1];
} ;

struct krt_mask_list *krt_mask_list = (struct krt_mask_list *) 0;

/*
 * Read a mask from kernel memory
 */
static sockaddr_un *
krt_getmask __PF3(tp, task *,
		  mask, struct sockaddr *,
		  af, int)
{
    u_long data[32];
    struct sockaddr *sa = (struct sockaddr *) data;
    register struct krt_mask_list *kmlp;
    register struct krt_mask *kmp;
    sockaddr_un *mp;

    if (!mask) {
	/* This should not happen */
	
	return	(sockaddr_un *) 0;
    }

    /* See if we have already found this mask */
    for (kmlp = krt_mask_list; kmlp; kmlp = kmlp->kml_next) {
	for (kmp = kmlp->kml_masks; kmp < kmlp->kml_fill; kmp++) {
	    if (kmp->km_addr == mask) {
		return kmp->km_mask;
	    }
	}
    }

    if (KVM_READ(kd,
		 mask,
		 sa,
		 sizeof *sa) < 0) {
	trace_log_tp(tp,
		     0,
		     LOG_ERR,
		     ("krt_getmask: reading mask: %s",
		      KVM_GETERR(kd, "kvm_read error")));
	return (sockaddr_un *) 0;
    }

    if (sa->sa_len > sizeof *sa) {
	/* Get the rest of the mask */
	
	if (KVM_READ(kd,
		     mask,
		     (u_char *) sa + sizeof *sa,
		     sa->sa_len - sizeof *sa) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_getmask: reading mask: %s",
			  KVM_GETERR(kd, "kvm_read error")));
	    return (sockaddr_un *) 0;
	}
    } else if (sa->sa_len < 2) {
	/* We have a null address, must be a zero length mask */

	sa->sa_len = 2;
    }
    sa->sa_family = af;

    mp = sock2gated(sa, unix_socksize(sa));
    if (!mask_contig(mp)) {
	/* Bogus mask */
	
	trace_log_tp(tp,
		     0,
		     LOG_ERR,
		     ("krt_getmask: non-contiguous mask: %A (len %u family %u data %A)",
		      mp,
		      sa->sa_len,
		      sa->sa_family,
		      sockbuild_ll(0, (byte *) sa->sa_data, (byte *) sa + sa->sa_len - (byte *) sa->sa_data)));
	return (sockaddr_un *) 0;
    }

    /* Find our version of it */
    mp = mask_locate(mp);

    if (!(kmlp = krt_mask_list)
	|| (byte *) kmlp->kml_fill == (byte *) kmlp + task_pagesize) {
	/* Get a new page */
	
	kmlp = (struct krt_mask_list *) task_block_malloc(task_pagesize);
	kmlp->kml_next = krt_mask_list;
	krt_mask_list = kmlp;
	kmlp->kml_fill = kmlp->kml_masks;
    }

    /* Put it on our list */
    kmp = kmlp->kml_fill++;
    kmp->km_addr = mask;
    kmp->km_mask = mp;

    return mp;
}


/*
 * Read a radix tree from kernel memory
 */
static void
krt_rtread_getnode __PF3(tp, task *,
			 rn, struct radix_node *,
			 rtp, rt_parms *)
{
    struct radix_node rnode, *dupedkey = (struct radix_node *) 0;
    struct rtentry krt;

    do {
	if (KVM_READ(kd,
		     rn,
		     &rnode,
		     sizeof(rnode)) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_rtread_getnode: reading radix node: %s",
			  KVM_GETERR(kd, "kvm_read error")));
	    return;
	}
	if (rnode.rn_b < 0) {
	    /* This is a leaf node */

	    /* Remember if there is more than one mask */
	    dupedkey = rnode.rn_dupedkey;
	    
	    if (!BIT_TEST(rnode.rn_flags, RNF_ROOT)) {
		/* This a data node, not a root node */
		
		if (KVM_READ(kd,
			     rn,
			     &krt,
			     sizeof(krt)) < 0) {
		    trace_log_tp(tp,
				 0,
				 LOG_ERR,
				 ("krt_rtread_getnode: reading rtentry: %s",
				  KVM_GETERR(kd, "kvm_read error")));
		    return;
		}

		/* OK, now get the relevant fields */
		/* Get the address (key) */
		rtp->rtp_dest = krt_getaddr(tp, rt_key(&krt));

		/* Get the mask */
		if (BIT_TEST(krt.rt_flags, RTF_HOST)) {
		    rtp->rtp_dest_mask = sockhostmask(rtp->rtp_dest);
		} else {
		    rtp->rtp_dest_mask = krt_getmask(tp, rt_mask(&krt), socktype(rtp->rtp_dest));
		}

		/* Get the gateway */
		rtp->rtp_router = krt_getaddr(tp, krt.rt_gateway);

		/* Get the state flags */
		rtp->rtp_state = krt_flags_to_state((flag_t) krt.rt_flags);

		krt_rtread_add(tp,
			       rtp,
			       (flag_t) krt.rt_flags,
			       FALSE,
			       "REMNANT");
	    }
	} else {
	    /* This is an internal node */

	    /* Go left first */
	    krt_rtread_getnode(tp, rnode.rn_l, rtp);

	    /* Then go right */
	    krt_rtread_getnode(tp, rnode.rn_r, rtp);
	}

	/* Repeat for each node with this key */
    } while (rn = dupedkey) ;

    return;
}


/*  Read the kernel's routing table */
/*ARGSUSED*/
int
krt_rtread __PF1(tp, task *)
{
    struct radix_node_head *rnh, head;
    rt_parms rtparms;
    int	errval = 0;

    bzero((caddr_t) &rtparms, sizeof (rtparms));
    rtparms.rtp_n_gw = 1;

    if (!kd) {
	errval = EBADF;
	goto Return;
    }

    trace_only_tp(tp,
		  TRC_NL_BEFORE,
		  ("krt_rtread: Initial routes read from kernel (radix tree via kmem):"));

    if (krt_radix_head) {
	if (KVM_READ(kd,
		     krt_radix_head,
		     &rnh,
		     sizeof(rnh)) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_rtread: reading radix_head: %s",
			  KVM_GETERR(kd, "kvm_read error")));
	    errval = EINVAL;
	    goto Return;
	}
    }

    /* The main loop */

    for (; rnh; rnh = head.rnh_next) {
	struct krt_mask_list *kmlp;
	
	if (KVM_READ(kd,
		     rnh,
		     &head,
		     sizeof(head)) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_rtread: readint radix head: %s",
			  KVM_GETERR(kd, "kvm_read error")));
	    errval = EINVAL;
	    goto Return;
	}

	switch (head.rnh_af) {
#ifdef	PROTO_INET
	case AF_INET:
#endif	/* PROTO_INET */
	    krt_rtread_getnode(tp, head.rnh_treetop, &rtparms);
	    break;

	default:
	    break;
	}

	while ((kmlp = krt_mask_list)) {
	    krt_mask_list = kmlp->kml_next;
	    task_block_reclaim(task_pagesize, (void_t) kmlp);
	}
    }

Return:
    return errval;
}
