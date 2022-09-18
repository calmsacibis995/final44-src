/*
 *  $Id: krt_rtread_kmem.c,v 1.6.2.4 1995/05/01 16:24:53 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_ROUTE
#define	INCLUDE_KVM
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#ifdef	PROTO_ISO
#include "iso.h"
#endif	/* PROTO_ISO */
#include "krt.h"
#include "krt_var.h"

u_long krt_rthashsize;
u_long krt_rthash[2];

#ifdef	ROUTES_WO_MBUFS
typedef struct rtentry krt_type;

#define	krt_next	rt_next
#define	krt_size	sizeof(krt_type)
#define	krt_conv(ptr)	(&(ptr))
#endif	/* ROUTES_WO_MBUFS */

#ifdef	SYSVR4
typedef	mblk_t krt_type;
#define	krt_next	b_cont
#define	krt_size	sizeof (krt_type)
#endif	/* SYSVR4 */

#ifdef	SYSV
typedef struct msgb krt_type;
#define	krt_next	b_next
#define	krt_size	sizeof (krt_type)
#endif	/* SYSV */

#if	!defined(krt_next)
typedef struct mbuf krt_type;

#define	krt_next	m_next
#define	krt_size	(MMINOFF + sizeof(struct rtentry))
#define krt_conv(ptr)	mtod(&ptr, struct rtentry *)
#endif

 /*  Read the kernel's routing table.			*/
int
krt_rtread __PF1(tp, task *)
{
    int i, hashsize = 0, krt_table;
    size_t rtbufsize;
    struct rtentry *krt;
    krt_type *next, m_buf, **base;
    rt_parms rtparms;

    bzero((caddr_t) &rtparms, sizeof (rtparms));
    rtparms.rtp_n_gw = 1;

    if (!kd) {
	return EBADF;
    }

    trace_only_tp(tp,
		  TRC_NL_BEFORE,
		  ("krt_rtread: Initial routes read from kernel (via kmem):"));

    if (!krt_rthash[KRT_RTHOST]
	|| !krt_rthash[KRT_RTNET]) {
	trace_only_tp(tp,
		      0,
		      ("krt_rtread: rthost and/or rtnet not in namelist"));

	return ESRCH;
    }
    if (krt_rthashsize) {
	if (KVM_READ(kd,
		     krt_rthashsize,
		     &hashsize,
		     sizeof(hashsize)) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_rtread: reading hashsize: %s",
			  KVM_GETERR(kd, "kvm_read error")));
	    return EINVAL;
	}
    }
    if (!hashsize) {
	trace_log_tp(tp,
		     0,
		     LOG_ERR,
		     ("krt_rtread: rthashsize not in namelist"));
	return ESRCH;
    }
    /* set up to read table of net hash chains */

    rtbufsize = hashsize * sizeof(krt_type *);
    base = (krt_type **) task_block_malloc(rtbufsize);
    for (krt_table = KRT_RTHOST; krt_table <= KRT_RTNET; krt_table++) {
	if (KVM_READ(kd,
		     krt_rthash[krt_table],
		     base,
		     rtbufsize) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_rtread: readhing hash bucket: %s",
			  KVM_GETERR(kd, "kvm_read error")));
	    return EINVAL;
	}
	for (i = 0; i < hashsize; i++) {
	    if_addr *ifap;
	    
	    for (next = base[i]; next != NULL; next = m_buf.krt_next) {
#if	defined(SYSV) || defined(SYSVR4)
		struct rtentry krt_rtentry;
#endif

		if (KVM_READ(kd,
			     next,
			     &m_buf,
			     krt_size) < 0) {
		    trace_log_tp(tp,
				 0,
				 LOG_ERR,
				 ("krt_rtread: reading mbuf: %s",
				  KVM_GETERR(kd, "kvm_read error")));
		    return EINVAL;
		}
#if	defined(SYSV) || defined(SYSVR4)
		if (KVM_READ(kd,
			     m_buf.b_rptr,
			     &krt_rtentry,
			     sizeof (krt_rtentry)) < 0) {
		    trace_log_tp(tp,
				 0,
				 LOG_ERR,
				 ("krt_rtread: reading rtentry: %s",
				  KVM_GETERR(kd, "kvm_read error")));
		    return EINVAL;
		}
		krt = &krt_rtentry;
#else
		krt = krt_conv(m_buf);
#endif

#ifdef	SYSVR4
		/*
 		 * SVR4 has a serious bug in the routing tables.  The address
 		 * family for routes that are direct connections are invalid,
 		 * and the sin_zero field is not always zero.  For now, assume
 		 * that they are all IP addresses (when in Rome...).
 		 */
		{
		    struct sockaddr_in *addr;
		    
		    addr = (struct sockaddr_in *) &krt->rt_dst;
		    addr->sin_family = AF_INET;
		    addr->sin_port = 0;
		    bzero((caddr_t) addr->sin_zero, sizeof (addr->sin_zero));

		    addr = (struct sockaddr_in *) &krt->rt_gateway;
		    addr->sin_family = AF_INET;
		    addr->sin_port = 0;
		    bzero((caddr_t) addr->sin_zero, sizeof (addr->sin_zero));
		    
		}
#endif	/* SYSVR4 */

		/* Ignore unknown address families */
		switch (krt->rt_dst.sa_family) {
#ifdef	PROTO_INET
		case AF_INET:
		    break;
#endif	/* PROTO_INET */

		default:
		    continue;
		}

		rtparms.rtp_dest = sock2gated(&krt->rt_dst, unix_socksize(&krt->rt_dst));
		rtparms.rtp_router = sock2gated(&krt->rt_gateway, unix_socksize(&krt->rt_gateway));
		rtparms.rtp_state = krt_flags_to_state((flag_t) krt->rt_flags);

		/* Determine netmask */
		if (BIT_TEST(krt->rt_flags, RTF_HOST)) {
		    rtparms.rtp_dest_mask = sockhostmask(rtparms.rtp_dest);
		} else if ((ifap = if_withdstaddr(rtparms.rtp_dest))
			   || (ifap = inet_ifwithnet(rtparms.rtp_dest))) {
		    rtparms.rtp_dest_mask = ifap->ifa_netmask;
		} else {
		    rtparms.rtp_dest_mask = inet_mask_natural(rtparms.rtp_dest);
		}

		krt_rtread_add(tp,
			       &rtparms,
			       (flag_t) krt->rt_flags,
			       FALSE,
			       "REMNANT");
	    }
	}
    }
    task_block_reclaim(rtbufsize, (caddr_t) base);

    return 0;
}
