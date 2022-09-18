/*
 *  $Id: krt_rtread_kinfo.c,v 1.8.2.3 1994/07/28 02:00:25 jch Exp $
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


/* Use the getkinfo() system call to read the routing table(s) */
/*ARGSUSED*/
int
krt_rtread __PF1(tp, task *)
{
    size_t size, alloc_size;
    caddr_t kbuf, cp, limit;
    rt_parms rtparms;
    struct rt_msghdr *rtp;
#ifdef	USE_SYSCTL
    static int mib[] = { CTL_NET, PF_ROUTE, 0, 0, NET_RT_DUMP, 0 };
#endif	/* USE_SYSCTL */

    trace_only_tp(tp,
		  TRC_NL_BEFORE,
		  ("krt_rtread: Initial routes read from kernel (via getkerninfo/sysctl):"));

    bzero((caddr_t) &rtparms, sizeof (rtparms));
    rtparms.rtp_n_gw = 1;

    if (
#ifdef	USE_SYSCTL
	sysctl(mib, sizeof mib / sizeof *mib, (caddr_t) 0, &alloc_size, NULL, 0)
#else	/* USE_SYSCTL */
	(int) (alloc_size = getkerninfo(KINFO_RT_DUMP, (caddr_t) 0, (int *) 0, 0))
#endif	/* USE_SYSCTL */
	< 0) {
	trace_log_tp(tp,
		     0,
		     LOG_ERR,
		     ("krt_rtread: getkerninfo/sysctl routing table estimate: %m"));
	return errno;
    }
    trace_tp(tp,
	     TR_STATE,
	     0,
	     ("krt_rtread: getkerninfo/sysctl estimates %d bytes needed",
	      alloc_size));
    size = alloc_size = ROUNDUP(alloc_size, task_pagesize);
    kbuf = (caddr_t) task_block_malloc(alloc_size);
    if (
#ifdef	USE_SYSCTL
	sysctl(mib, sizeof mib / sizeof *mib, kbuf, &size, NULL, 0)
#else	/* USE_SYSCTL */
	getkerninfo(KINFO_RT_DUMP, kbuf, (int *) &size, 0)
#endif	/* USE_SYSCTL */
	< 0) {
	trace_log_tp(tp,
		     0,
		     LOG_ERR,
		     ("krt_rtread: getkerninfo/sysctl routing table retrieve: %m"));
	return errno;
    }
    limit = kbuf + size;

    for (cp = kbuf; cp < limit; cp += rtp->rtm_msglen) {
	sockaddr_un *author;
	krt_addrinfo *adip;
	const char *errmsg = (char *) 0;
	int pri = 0;

	rtp = (struct rt_msghdr *) ((void_t) cp);

	adip = krt_xaddrs(rtp,
			  (size_t) rtp->rtm_msglen);
	if (!adip) {
	    continue;
	}

	if (TRACE_TP(tp, TR_KRT_REMNANTS)) {
	    /* Always trace in detail */
	    krt_trace_msg(tp,
			  "RTINFO",
			  rtp,
			  (size_t) rtp->rtm_msglen,
			  adip,
			  0,
			  TRUE);
	}

	switch (krt_rtaddrs(adip, &rtparms, &author, (flag_t) rtp->rtm_flags)) {
	case KRT_ADDR_OK:
	    break;

	case KRT_ADDR_IGNORE:
	    errmsg = "ignoring";
	    pri = LOG_INFO;
	    goto Trace;

	case KRT_ADDR_BOGUS:
	    errmsg = "deleting bogus";
	    pri = LOG_WARNING;
	    krt_delq_add(&rtparms);
	    goto Trace;

#ifdef	IP_MULTICAST
	case KRT_ADDR_MC:
#ifndef	KRT_IPMULTI_RTSOCK
	    if (krt_multicast_install(rtparms.rtp_dest, rtparms.rtp_router)) {
		errmsg = "deleting multicast";
		pri = LOG_WARNING;
		krt_delq_add(&rtparms);
		goto Trace;
	    }
#endif	/* KRT_IPMULTI_RTSOCK */
	    errmsg = "ignoring multicast";
	    pri = LOG_INFO;
	    goto Trace;
#endif	/* IP_MULTICAST */
	}

	errmsg = krt_rtadd(&rtparms, (flag_t) rtp->rtm_flags);
	if (errmsg) {
	    /* It has been deleted */

	    pri = LOG_WARNING;
	}

    Trace:
	if (errmsg) {
	    krt_trace(tp,
		      "READ",
		      "REMNANT",
		      adip->rti_info[RTAX_DST],
		      adip->rti_info[RTAX_NETMASK],
		      adip->rti_info[RTAX_GATEWAY],
		      (flag_t) rtp->rtm_flags,
		      errmsg,
		      pri);
	}
    }

    task_block_reclaim(alloc_size, kbuf);

    return 0;
}



