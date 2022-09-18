/*
 *  $Id: krt_ifread_kinfo.c,v 1.9.2.2 1995/01/13 19:19:24 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_KINFO
#define	INCLUDE_ROUTE
#define	INCLUDE_IF
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#ifdef	PROTO_ISO
#include "iso.h"
#endif	/* PROTO_ISO */
#include "krt.h"
#include "krt_var.h"

#if	IFNAMSIZ > IFL_NAMELEN
error - IFL_NAMELEN not compatible with IFNAMESIZ
#endif


int
krt_ifread __PF1(save_task_state, flag_t)
{
    size_t size;
    caddr_t kbuf, cp, limit;
    struct if_msghdr *ifap;
    if_link *ifl = (if_link *) 0;
    register task *tp = krt_task;
#ifdef	USE_SYSCTL
    static int mib[] = { CTL_NET, PF_ROUTE, 0, 0, NET_RT_IFLIST, 0 };
#endif	/* USE_SYSCTL */

    while (TRUE) {
	if (
#ifdef	USE_SYSCTL
	    sysctl(mib, sizeof mib / sizeof *mib, (caddr_t) 0, &size, NULL, 0)
#else	/* USE_SYSCTL */
	    (int) (size = getkerninfo(KINFO_RT_IFLIST, (caddr_t) 0, (size_t *) 0, 0))
#endif	/* USE_SYSCTL */
	    < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_ifread: getkerninfo/sysctl: %m"));
	    return errno;
	}
	if (size > task_send_buffer_len) {
	    /* Need more memory */

	    trace_tp(tp,
		     TR_NORMAL,
		     0,
		     ("krt_ifread: %s estimates %d bytes needed",
		      "getkerninfo/sysctl",
		      size));
	    task_alloc_send(tp, size);
	}
	kbuf = task_send_buffer;
	if (
#ifdef	USE_SYSCTL
	    sysctl(mib, sizeof mib / sizeof *mib, task_send_buffer, &size, NULL, 0)
#else	/* USE_SYSCTL */
	    getkerninfo(KINFO_RT_IFLIST, task_send_buffer, &size, 0)
#endif	/* USE_SYSCTL */
	    < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_ifread: interface table retrieval %m"));
	} else {
	    /* Should have the data */
	    
	    break;
	}
    }

    limit = kbuf + size;

    /* Tell the IF code that we are passing complete knowledge */
    if_conf_open(tp, TRUE);
    
    for (cp = kbuf; cp < limit; cp += ifap->ifm_msglen) {
	krt_addrinfo *adip;
	
	ifap = (struct if_msghdr *) cp;

	/* Pick out the addresses */
	adip = krt_xaddrs((struct rt_msghdr *) ifap, ifap->ifm_msglen);
	if (!adip) {
	    /* Try the next message */
	    continue;
	}

	/* Trace the message */
	if (TRACE_TP(tp, TR_KRT_IFLIST)) {
	    /* Always trace in detail */
	    
	    krt_trace_msg(tp,
			  "IFINFO",
			  (struct rt_msghdr *) ifap,
			  ifap->ifm_msglen,
			  adip,
			  0,
			  TRUE);
	}

	switch (ifap->ifm_type) {
	    sockaddr_un *ap;

	case RTM_IFINFO:
	    {
		/* New interface */

		if ((ap = adip->rti_info[RTAX_IFP])) {
		    /* Link level info */
		    sockaddr_un *lladdr;

		    if (ap->dl.gdl_alen) {
			lladdr = sockbuild_ll(krt_type_to_ll(ap->dl.gdl_type),
					      (byte *) ap->dl.gdl_data + ap->dl.gdl_nlen,
					      (size_t) ap->dl.gdl_alen);
		    } else {
			lladdr = (sockaddr_un *) 0;
		    }

		    ifl = ifl_addup(tp,
				    ifl_locate_index(ap->dl.gdl_index),
				    ap->dl.gdl_index,
				    krt_if_flags(ifap->ifm_flags),
				    ifap->ifm_data.ifi_metric,
				    (mtu_t) ifap->ifm_data.ifi_mtu,
				    ap->dl.gdl_data,
				    ap->dl.gdl_nlen,
				    lladdr,
				    ap);
		} else {
		    /* No link level info? */

		    ifl = (if_link *) 0;
		}
	    }
	    break;

	case RTM_NEWADDR:
	    krt_ifaddr(tp,
		       (struct ifa_msghdr *) ifap,
		       adip,
		       ifl);
	    break;

	default:
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_ifread: ignoring unknown message type: %s (%d)",
			  trace_state(rtm_type_bits, ifap->ifm_type),
			  ifap->ifm_type));
	    continue;
	}

	trace_tp(tp,
		 TR_NORMAL,
		 0,
		 (NULL));
    }

    if_conf_close(tp, FALSE);

    return 0;
}
