/*
 *  $Header: /users/jch/src/gated/src/RCS/krt.c,v 2.0 90/04/16 16:52:47 jch Exp Locker: jch $
 */

/********************************************************************************
*										*
*	GateD, Release 2							*
*										*
*	Copyright (c) 1990 by Cornell University				*
*	    All rights reserved.						*
*										*
*	    Royalty-free licenses to redistribute GateD Release 2 in		*
*	    whole or in part may be obtained by writing to:			*
*										*
*	    Center for Theory and Simulation in Science and Engineering		*
*	    Cornell University							*
*	    Ithaca, NY 14853-5201.						*
*										*
*	THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR		*
*	IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED		*
*	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.	*
*										*
*	GateD is based on Kirton's EGP, UC Berkeley's routing daemon		*
*	(routed), and DCN's HELLO routing Protocol.  Development of Release	*
*	2 has been supported by the National Science Foundation.		*
*										*
*		Jeffrey C Honig <jch@gated.cornell.edu>				*
*		Scott W Brim <swb@gated.cornell.edu>				*
*										*
*	The following acknowledgements and thanks apply:			*
*										*
*		Mark Fedor <fedor@psi.com> for the development and		*
*		maintenance up to release 1.3.1 and his continuing		*
*		advice.								*
*										*
*		Dennis Ferguson <dennis@canet.ca>				*
*										*
*********************************************************************************
*      Portions of this software may fall under the following			*
*      copyrights: 								*
*										*
*	Copyright (c) 1988 Regents of the University of California.		*
*	All rights reserved.							*
*										*
*	Redistribution and use in source and binary forms are permitted		*
*	provided that the above copyright notice and this paragraph are		*
*	duplicated in all such forms and that any documentation,		*
*	advertising materials, and other materials related to such		*
*	distribution and use acknowledge that the software was developed	*
*	by the University of California, Berkeley.  The name of the		*
*	University may not be used to endorse or promote products derived	*
*	from this software without specific prior written permission.		*
*	THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR		*
*	IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED		*
*	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.	*
********************************************************************************/



/* krt.c
 *
 * Kernel routing table interface routines
 */

#define	INCLUDE_NLIST
#define	INCLUDE_IOCTL
#define	INCLUDE_FILE
#define	INCLUDE_MBUF
#define	INCLUDE_KINFO
#define	INCLUDE_KVM_SUNOS

#define ROUTE_KERNEL

#include "include.h"
#include "krt.h"

#define	KRT_TIMER_TIMEOUT	0	/* For routing socket retries */
#define	KRT_TIMER_IFCHECK	1	/* For checking interfaces */
#define	KRT_TIMER_MAX		2

#if	RT_N_MULTIPATH != 1
Fatal error - the BSD Unix kernel can only support one next hop !
#endif

int krt_install = TRUE;			/* if TRUE install route in kernel */
char *krt_version_kernel;		/* OS version of the kernel */

static task *krt_task;			/* Task for kernel routing table */

gw_entry *krt_gw_list;			/* List of gateways for static routes */

/* KVM emulation */
#ifdef	SUNOS
kvm_t	*kd;
#define	KVM_OPENFILES(namelist, corefile, swapfile) ((kd = kvm_open(namelist, corefile, swapfile, O_RDONLY, NULL)) ? 0 : -1)
#define	KVM_NLIST(nl)	kvm_nlist(kd, nl)
#define	KVM_READ(addr, buf, nbytes)	kvm_read(kd, addr, buf, nbytes)
#define	KVM_CLOSE()	kvm_close(kd)
#define	KVM_GETERR(string)	string
#else	/* SUNOS */
#if	!defined(BSD4_4)
PROTOTYPE(kvm_openfiles,
	  extern int,
	  (char *,
	   char *,
	   char *));
PROTOTYPE(kvm_nlist,
	  extern int,
	  (struct nlist *));
PROTOTYPE(kvm_read,
	  extern int,
	  (off_t,
	   caddr_t,
	   unsigned int));
PROTOTYPE(kvm_close,
	  extern int,
	  (void));
PROTOTYPE(kvm_geterr,
	  extern char *,
	  (void));
#endif	/* !defined(BSD4_4) */
#define	KVM_OPENFILES(namelist, corefile, swapfile)	kvm_openfiles(namelist, corefile, swapfile)
#define	KVM_NLIST(nl)	kvm_nlist(nl)
#define	KVM_READ(addr, buf, nbytes)	kvm_read(addr, buf, nbytes)
#define	KVM_CLOSE()	kvm_close()
#define	KVM_GETERR(string)	kvm_geterr()
#endif	/* SUNOS */

#ifndef	USE_KERNINFO
static struct nlist *krt_rt[2];

#define	KRT_RTHOST	0
#define	KRT_RTNET	1
static struct nlist *krt_rthashsize;

#endif				/* USE_KERNINFO */
#ifndef	vax11c
static struct nlist *krt_version;

#else				/* vax11c */
static struct nlist *krt_multinet_version;
static struct nlist *krt_multinet_product_name;

#endif				/* vax11c */

static struct nlist *krt_ifnet;

static struct {
    const char *nl_name;
    struct nlist **nl_ptr;
} nl_names[] = {
#ifndef	USE_KERNINFO
    {"_rthost", &krt_rt[KRT_RTHOST]},
    {"_rtnet", &krt_rt[KRT_RTNET]},
    {"_rthashsize", &krt_rthashsize},
#endif	/* USE_KERNINFO */
    {"_ifnet", &krt_ifnet},
#ifndef	vax11c
    {"_version", &krt_version},
#else	/* vax11c */
    {"_multinet_version", &krt_multinet_version},
    {"_multinet_product_name", &krt_multinet_product_name},
#endif	/* vax11c */
    {NULL, NULL}
};

#define	NL_SIZE	(sizeof (nl_names)/sizeof (nl_names[0]))

PROTOTYPE(krt_change,
	  static int,
	  (rt_entry *old_rt,
	   sockaddr_un *old_router,
	   rt_entry *new_rt));


#if	defined(ULTRIX3_X)
typedef struct rtentry krt_type;

#define	krt_next	rt_next
#define	krt_size	sizeof(krt_type)
#define	krt_conv(ptr)	(struct rtentry *) &ptr
#endif				/* defined(ULTRIX3_X) */

#if	!defined(krt_next) && !defined(USE_KERNINFO)
typedef struct mbuf krt_type;

#define	krt_next	m_next
#define	krt_size	(MMINOFF + sizeof(struct rtentry))
#define krt_conv(ptr)	mtod(&ptr, struct rtentry *)
#endif				/* !defined(krt_next) && !defined(ROUTING_SOCKET) */

/* A route has been installed that is already in the kernel.  Flag it as */
/* being announced and remember this gateway */
inline void
krt_installed(installed_rt)
rt_entry *installed_rt;
{
    sockaddr_un *router;

    rtbit_set(installed_rt, krt_task->task_rtbit);

    /* Remember this route */
    sockdup(installed_rt->rt_router, router);
    rttsi_set(installed_rt->rt_head, krt_task->task_rtbit, (byte *) &router);
}


#if	defined(krt_next)
 /*  Read the kernel's routing table.			*/
static void
krt_rtread(skip)
int skip;
{
    int i, hashsize = 0, rtbufsize, krt_table;
    flag_t table;
    proto_t proto;
    pref_t preference;
    struct rtentry *krt;
    krt_type *next, m_buf, **base;

    if (skip) {
	return;
    }
    
    trace(TR_RT, 0, "krt_rtread: Initial routes read from kernel:");

    if ((krt_rt[KRT_RTHOST]->n_value == 0) || (krt_rt[KRT_RTNET]->n_value == 0)) {
	trace(TR_ALL, LOG_ERR, "krt_rtread: rthost and/or rtnet not in namelist");
	task_quit(errno);
    }
    if (krt_rthashsize->n_value != 0) {
	if (KVM_READ(krt_rthashsize->n_value, (caddr_t) &hashsize, sizeof(hashsize)) < 0) {
	    trace(TR_ALL, LOG_ERR, "krt_rtread: %s",
		  KVM_GETERR("kvm_read error"));
	    task_quit(errno);
	}
    }
    if (!hashsize) {
#ifdef	RTHASHSIZ
	trace(TR_ALL, 0, "krt_rtread: defaulting rthashsize to RTHASHSIZ(%d)",
	      hashsize = RTHASHSIZ);
#else				/* RTHASHSIZ */
	trace(TR_ALL, LOG_ERR, "krt_rtread: rthashsize not in namelist");
	task_quit(ENOENT);
#endif				/* RTHASHSIZ */
    }
    /* set up to read table of net hash chains */

    rtbufsize = hashsize * sizeof(krt_type *);
    base = (krt_type **) task_mem_malloc(krt_task, (unsigned int) rtbufsize);
    for (krt_table = KRT_RTHOST; krt_table <= KRT_RTNET; krt_table++) {
#ifdef	_IBMR2
	off_t root;

	if (KVM_READ(krt_rt[krt_table]->n_value, (caddr_t) &root, sizeof (root)) < 0) {
	    trace(TR_ALL, LOG_ERR, "krt_rtread: %s",
		  KVM_GETERR("kvm_read error"));
	    task_quit(errno);
	}
#else	/* _IBMR2 */
#define	root	krt_rt[krt_table]->n_value
#endif	/* _IBMR2 */

	if (KVM_READ(root, (caddr_t) base, rtbufsize) < 0) {
	    trace(TR_ALL, LOG_ERR, "krt_rtread: %s",
		  KVM_GETERR("kvm_read error"));
	    task_quit(errno);
	}
	for (i = 0; i < hashsize; i++) {
	    rt_entry *rt;
	    if_entry *ifp;
	    sockaddr_un *netmask = (sockaddr_un *) 0;
	    sockaddr_un *dst;
	    sockaddr_un *gateway;
	    
	    for (next = base[i]; next != NULL; next = m_buf.krt_next) {
		if (KVM_READ((off_t) next, (caddr_t) &m_buf, krt_size) < 0) {
		    trace(TR_ALL, LOG_ERR, "krt_rtread: %s",
			  KVM_GETERR("kvm_read error"));
		    task_quit(errno);
		}
		krt = krt_conv(m_buf);

		dst = sock2gated(&krt->rt_dst);
		gateway = sock2gated(&krt->rt_gateway);

		switch (socktype(dst)) {
		case AF_INET:
		    switch (inet_class((byte *) &dst->in.sin_addr.s_addr)) {
		    case IN_CLASS_A:
		    case IN_CLASS_B:
		    case IN_CLASS_C:
			break;

#ifdef	HAVE_MULTICAST
		    case IN_CLASS_D:
			/* Ignore multicast addresses for now */
			continue;
#endif	/* HAVE_MULTICAST */

		    default:
			goto Delete;
		    }
		    break;

#ifdef	ISOPROTO_RAW
		case AF_ISO:
		    break;
#endif	/* ISOPROTO_RAW */

		default:
		    /* Unknown address family */
		    continue;
		}

		if (BIT_TEST(krt->rt_flags, RTF_HOST)) {
		    table = RTS_HOSTROUTE;
		    netmask = (sockaddr_un *) 0;
		} else if (ifp = if_withnet(dst)) {
		    table = RTS_INTERIOR;
		    netmask = ifp->int_subnetmask;
		} else {
		    /* Route is interior if we have an interface to it or a subnet of it */
		    table = RTS_EXTERIOR;
		    netmask = mask_inet_natural(dst);
		}

#ifdef	RTF_MODIFIED
#define	RTFLAGS	(RTF_DYNAMIC|RTF_MODIFIED)
#else	/* RTF_MODIFIED */
#define	RTFLAGS	RTF_DYNAMIC
#endif	/* RTF_MODIFIED */
		if (BIT_TEST(krt->rt_flags, RTFLAGS)) {
#undef	RTFLAGS
		    proto = RTPROTO_REDIRECT;
		    preference = RTPREF_REDIRECT;
		} else {
		    proto = RTPROTO_KERNEL;
		    preference = RTPREF_KERNEL;
		}

		/*
	         *	If Kernel route already exists, delete this one, the kernel uses the
	         *	first one
	         */
		if (rt_locate(table, dst, netmask, proto)) {
		    goto Delete;
		}
		/*
	         *	If there was a problem adding the route, delete the kernel route
	         */
		if (rt = rt_add(dst,
				netmask,
				gateway,
				(gw_entry *) 0,
				0,
				table,
				krt->rt_flags,
				proto,
				(as_t) 0,
				(time_t) 0,
				preference)) {
		    krt_installed(rt);
		} else {
		Delete:
		    krt_delete_dst(krt_task,
				   (rt_entry *) 0,
				   dst,
				   netmask,
				   gateway,
				   (flag_t) krt->rt_flags);
		}
	    }
	}
    }
    task_mem_free(krt_task, (caddr_t) base);

    return;
}

#endif				/* defined(krt_next) */


#if	defined(ROUTING_SOCKET) || defined(USE_KERNINFO)
/*
 *	Support code for use with the getkerninfo() call and the routing socket.
 */

#define ROUNDUP(a) (1 + (((a) - 1) | (sizeof(long) - 1)))
#define	RTM_ADDR(ap)	ap = (struct sockaddr *) ((caddr_t) ap + (ap->sa_len ? ROUNDUP(ap->sa_len) : sizeof(u_long)))
    

static bits rtm_type_bits[] =
{
    {RTM_ADD, "ADD"},
    {RTM_DELETE, "DELETE"},
    {RTM_CHANGE, "CHANGE"},
    {RTM_GET, "GET"},
    {RTM_LOSING, "LOSING"},
    {RTM_REDIRECT, "REDIRECT"},
    {RTM_MISS, "MISS"},
    {RTM_LOCK, "LOCK"},
    {RTM_OLDADD, "OLDADD"},
    {RTM_OLDDEL, "OLDDEL"},
    {RTM_RESOLVE, "RESOLVE"},
    {0, NULL}
};

static bits rtm_lock_bits[] =
{
    {RTV_MTU, "MTU"},
    {RTV_HOPCOUNT, "HOPCOUNT"},
    {RTV_EXPIRE, "EXPIRE"},
    {RTV_RPIPE, "RPIPE"},
    {RTV_SPIPE, "SPIPE"},
    {RTV_SSTHRESH, "SSTHRESH"},
    {RTV_RTT, "RTT"},
    {RTV_RTTVAR, "RTTVAR"},
    {0, NULL}
};

static bits rtm_sock_bits[] =
{
    {RTA_DST, "DST"},
    {RTA_GATEWAY, "GATEWAY"},
    {RTA_NETMASK, "NETMASK"},
    {RTA_GENMASK, "GENMASK"},
    {RTA_IFP, "IFP"},
    {RTA_IFA, "IFA"},
    {RTA_AUTHOR, "AUTHOR"},
    {0, NULL}
};


inline static void
krt_not_installed(installed_rt)
rt_entry *installed_rt;
{
    sockaddr_un *router;
    
    rtbit_reset(installed_rt, krt_task->task_rtbit);

    /* Remember this route */
    rttsi_get(installed_rt->rt_head, krt_task->task_rtbit, (byte *) &router);
    sockfree(router);
    router = (sockaddr_un *) 0;
    rttsi_set(installed_rt->rt_head, krt_task->task_rtbit, (byte *) &router);
}


/* Trace a route socket packet */
/*ARGSUSED*/
static void
krt_trace(tp, direction, rtp, pri)
task *tp;
char *direction;
struct rt_msghdr *rtp;
int pri;
{
    struct sockaddr *ap;
    sockaddr_un *dest;

    ap = (struct sockaddr *) (rtp + 1);

    if (BIT_TEST(trace_flags, TR_UPDATE)) {
	/* Long form */
	tracef("KRT %s len %d ver %d type %s(%d) addrs %s(%x) pid %d seq %d",
	       direction,
	       rtp->rtm_msglen,
	       rtp->rtm_version,
	       trace_state(rtm_type_bits, rtp->rtm_type - 1),
	       rtp->rtm_type,
	       trace_bits(rtm_sock_bits, rtp->rtm_addrs),
	       rtp->rtm_addrs,
	       rtp->rtm_pid,
	       rtp->rtm_seq);
	if (rtp->rtm_errno) {
	    errno = rtp->rtm_errno;
	    trace(TR_KRT, pri, " error %d: %m",
		  rtp->rtm_errno);
	} else {
	    trace(TR_KRT, pri, NULL);
	}

	tracef("KRT %s flags %s(%x)",
	       direction,
	       trace_bits(rt_flag_bits, rtp->rtm_flags),
	       rtp->rtm_flags & 0xffff);
	tracef("  locks %s(%x)",
	       trace_bits(rtm_lock_bits, rtp->rtm_rmx.rmx_locks),
	       rtp->rtm_rmx.rmx_locks);
	trace(TR_KRT, pri, " inits %s(%x)",
	      trace_bits(rtm_lock_bits, rtp->rtm_inits),
	      rtp->rtm_inits);

	/* Display metrics */
	switch (rtp->rtm_type) {
	    case RTM_ADD:
	    case RTM_CHANGE:
	    case RTM_GET:
	    /* XXX - Only print metrics which are locked or inited */
	        trace(TR_KRT, pri, "KRT %s mtu %d hopcount %d expire %#T ssthresh %d",
		      direction,
		      rtp->rtm_rmx.rmx_mtu,
		      rtp->rtm_rmx.rmx_hopcount,
		      rtp->rtm_rmx.rmx_expire,
		      rtp->rtm_rmx.rmx_ssthresh);
		trace(TR_KRT, pri, "KRT %s recvpipe %d sendpipe %d rtt %d rttvar %d",
		      direction,
		      rtp->rtm_rmx.rmx_recvpipe,
		      rtp->rtm_rmx.rmx_sendpipe,
		      rtp->rtm_rmx.rmx_rtt,
		      rtp->rtm_rmx.rmx_rttvar);
		break;
	}
    } else {
	/* Short form */
	tracef("KRT %s type %s(%d) flags %s(%x) error %d",
	       direction,
	       trace_state(rtm_type_bits, rtp->rtm_type - 1),
	       rtp->rtm_type,
	       trace_bits(rt_flag_bits, rtp->rtm_flags),
	       rtp->rtm_flags & 0xffff,
	       rtp->rtm_errno);
	if (rtp->rtm_errno) {
	    errno = rtp->rtm_errno;
	    trace(TR_KRT, pri, ": %m");
	} else {
	    trace(TR_KRT, pri, NULL);
	}
    }

    /* Display addresses */
    if (rtp->rtm_addrs) {
	tracef("KRT %s", direction);
	if (BIT_TEST(rtp->rtm_addrs, RTA_DST)) {
	    dest = sock2gated(ap);
	    tracef(" dst %A",
		   dest);
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_GATEWAY)) {
	    tracef(" gateway %A",
		   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_NETMASK)) {
	    struct sockaddr addr;

	    bzero((caddr_t) &addr, sizeof (addr));
	    bcopy((caddr_t) ap, (caddr_t) &addr, ap->sa_len);
	    if (addr.sa_len < 2) {
		addr.sa_len = 2;	/* Length and family */
	    }
	    addr.sa_family = socktype(dest);
	    tracef(" netmask %A",
		   sock2gated(&addr));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_GENMASK)) {
	    tracef(" genmask %A",
		   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_IFP)) {
	    tracef(" ifp %A",
		   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_IFA)) {
	    tracef(" ifa %A",
		   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_AUTHOR)) {
	    tracef(" author %A",
		   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	trace(TR_KRT, pri, NULL);
    }

    trace(TR_KRT, pri, NULL);
}
#endif	/* defined(ROUTING_SOCKET) || defined(USE_KERNINFO) */


#ifdef	USE_KERNINFO
/* Use the getkinfo() system call to read the routing table(s) */
/*ARGSUSED*/
static void
krt_rtread(skip)
int skip;
{
    int size;
    caddr_t kbuf, cp, limit;
    struct rt_msghdr *rtp;
    flag_t table;
    proto_t proto;
    pref_t preference;
    struct sockaddr *ap;
    sockaddr_un *dest, *mask, *gate;

    trace(TR_RT, 0, "krt_rtread: Initial routes read from kernel:");

    if ((size = getkerninfo(KINFO_RT_DUMP, (caddr_t) 0, (int *) 0, 0)) < 0) {
	trace(TR_ALL, LOG_ERR, "krt_rtread: getkerninfo(KINFO_RT_DUMP) estimate: %m");
	task_quit(errno);
    }
    if (BIT_TEST(trace_flags, TR_PROTOCOL)) {
	trace(TR_KRT, 0, "krt_rtread: getkerninfo(KINFO_RT_DUMP) estimates %d bytes needed",
	      size);
    }
    kbuf = (caddr_t) task_mem_malloc(krt_task, size);
    if (getkerninfo(KINFO_RT_DUMP, kbuf, &size, 0) < 0) {
	trace(TR_ALL, LOG_ERR, "krt_rtread: getkerninfo(KINFO_RT_DUMP): %m");
	task_quit(errno);
    }
    limit = kbuf + size;

    for (cp = kbuf; cp < limit; cp += rtp->rtm_msglen) {
	rt_entry *rt;

	rtp = (struct rt_msghdr *) cp;

	if (rtp->rtm_version != RTM_VERSION) {
	    trace(TR_ALL, LOG_ERR, "krt_rtread: version mismatch!  Expected %d, received %d",
		  RTM_VERSION,
		  rtp->rtm_version);
	    task_quit(EPROTONOSUPPORT);
	}
	krt_trace(krt_task, "KINFO", rtp, 0);

	if (BIT_TEST(rtp->rtm_flags, RTF_CLONING|RTF_LLINFO)) {
	    /* Skip cloning masks */
	    continue;
	}

	ap = (struct sockaddr *) (rtp + 1);

	if (BIT_TEST(rtp->rtm_addrs, RTA_DST)) {
	    dest = sock2gated(ap);
	    RTM_ADDR(ap);
	} else {
	    dest = (sockaddr_un *) 0;
	}

	if (!dest || socktype(dest) != AF_INET) {
	    continue;
	}

	if (BIT_TEST(rtp->rtm_addrs, RTA_GATEWAY)) {
	    gate = sock2gated(ap);
	    RTM_ADDR(ap);
	} else {
	    gate = (sockaddr_un *) 0;
	}

	if (BIT_TEST(rtp->rtm_addrs, RTA_NETMASK)) {
	    struct sockaddr addr;

	    bzero((caddr_t) &addr, sizeof (addr));
	    bcopy((caddr_t) ap, (caddr_t) &addr, ap->sa_len);
	    if (addr.sa_len < 2) {
		addr.sa_len = 2;	/* Length and family */
	    }
	    addr.sa_family = socktype(dest);
	    mask = mask_locate(sock2gated(&addr));
	    RTM_ADDR(ap);
	} else if (BIT_TEST(rtp->rtm_flags, RTF_HOST)) {
	    mask = (sockaddr_un *) 0;
	} else {
	    mask = mask_inet_natural(dest);
	}

	if (BIT_TEST(rtp->rtm_addrs, RTA_GENMASK)) {
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_IFP)) {
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_IFA)) {
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->rtm_addrs, RTA_AUTHOR)) {
	    RTM_ADDR(ap);
	}

	switch (socktype(dest)) {
	case AF_INET:
	    switch (inet_class((byte *) &dest->in.sin_addr.s_addr)) {
	    case IN_CLASS_A:
	    case IN_CLASS_B:
	    case IN_CLASS_C:
		break;

#ifdef	HAVE_MULTICAST
	    case IN_CLASS_D:
		/* Ignore multicast addresses for now */
		continue;
#endif	/* HAVE_MULTICAST */

	    default:
		goto Delete;
	    }
	    break;

#ifdef	ISOPROTO_RAW
	case AF_ISO:
	    break;
#endif	/* ISOPROTO_RAW */

	default:
	    /* Unknown address family */
	    continue;
	}
		
	if (BIT_TEST(rtp->rtm_flags, RTF_HOST)) {
	    table = RTS_HOSTROUTE;
	} else if (if_withnet(dest)) {
	    table = RTS_INTERIOR;
	} else {
	    table = RTS_EXTERIOR;
	}

	if (BIT_TEST(rtp->rtm_flags, RTF_DYNAMIC|RTF_MODIFIED)) {
	    proto = RTPROTO_REDIRECT;
	    preference = RTPREF_REDIRECT;
#ifdef	RTF_STATIC
	} else if (BIT_TEST(rtp->rtm_flags, RTF_STATIC)) {
	    proto = RTPROTO_KRT;
	    preference = RTPREF_KRT;
	    table |= RTS_NOAGE|RTS_RETAIN;	/* Don't age static routes */
#endif	RTF_STATIC
	} else {
	    proto = RTPROTO_KERNEL;
	    preference = RTPREF_KERNEL;
	}

	/*
	 *	If Kernel route already exists, delete this one, the kernel uses the
	 *	first one
	 */
	if (rt_locate(table, dest, mask, proto)) {
	    goto Delete;
	}

	/*
	 *	If there was a problem adding the route, delete the kernel route
	 */
	if (rt = rt_add(dest,
			mask,
			gate,
			(gw_entry *) 0,
			0,
			table,
			rtp->rtm_flags,
			proto,
			(as_t) 0,
			(time_t) 0,
			preference)) {
	    krt_installed(rt);
	} else {
	    goto Delete;
	}
	continue;

      Delete:
	krt_delete_dst(krt_task,
		       (rt_entry *) 0,
		       dest,
		       mask,
		       gate,
		       (flag_t) rtp->rtm_flags);

    }

    task_mem_free(krt_task, kbuf);
}
#endif	/* USE_KERNINFO */


#ifdef	ROUTING_SOCKET

/* Support for BSD4.4 route socket. */

#define	KRT_TIMEOUT	2				/* Default initial timeout on a failure */
#define	KRT_TIMER(tp)	TASK_TIMER(tp, 0)
#define	KRT_BUMP(value)	value = value * 2		/* Action to take on sucessive failures */
#define	KRT_RESET(value)	value = KRT_TIMEOUT	/* Reset timer */
static time_t krt_waittime = KRT_TIMEOUT;		/* Length of time before a response is overdue */

struct rtm_msg {
    struct rtm_msg *rtm_forw;
    struct rtm_msg *rtm_back;
    /* How about some statistics */
    struct rt_msghdr msghdr;
};

static struct rtm_msg rtm_head = {&rtm_head, &rtm_head};	/* Head of message queue */


/* Issue a request */
static inline int
krt_send(ki_tp, ki_rtp)
task *ki_tp;
struct rtm_msg *ki_rtp;
{
    int pri = 0;
    int retry_type = 0;
    const char *sent = "SENT";

    if (!ki_rtp->msghdr.rtm_seq) {
	ki_rtp->msghdr.rtm_seq = ++rtm_head.msghdr.rtm_seq;
	ki_rtp->msghdr.rtm_version = RTM_VERSION;
    }
    ki_rtp->msghdr.rtm_pid = task_pid;
    ki_rtp->msghdr.rtm_errno = 0;

 retry:
    if (!BIT_TEST(task_state, TASKS_TEST) && krt_install) {
	errno = 0;
	if (write(ki_tp->task_socket, (caddr_t) &ki_rtp->msghdr, ki_rtp->msghdr.rtm_msglen) < 0) {
	    ki_rtp->msghdr.rtm_errno = errno;
	    trace(TR_ALL, LOG_ERR, "krt_send: write: %m");
	    sent = "*NOT SENT*";
	    pri = LOG_ERR;
	}
    }

    if (pri || BIT_TEST(trace_flags, TR_KRT)) {
	krt_trace(ki_tp, sent, &ki_rtp->msghdr, pri);
    }

    switch (ki_rtp->msghdr.rtm_errno) {
        case ENOBUFS:
	    /* Indicate request should be retried if the error is not fatal */
	    ki_rtp->msghdr.rtm_pid = 0;
	    break;

	case EEXIST:
	    /* What!  We must have missed a routing message. */
	    switch (ki_rtp->msghdr.rtm_type) {
	    case RTM_ADD:
		/* Try to make it look the way we want it to */
		ki_rtp->msghdr.rtm_type = RTM_CHANGE;
		goto retry;
	    }
	    ki_rtp->msghdr.rtm_errno = 0;
	    break;

	case ESRCH:
	    /* Asked to process a route that does not exist */
	    switch (ki_rtp->msghdr.rtm_type) {
	    case RTM_CHANGE:
		/* Change a change into an add */
		ki_rtp->msghdr.rtm_type = RTM_ADD;
		goto retry;

	    case RTM_DELETE:
		/* Same result, do we really care how it happened? */
		break;
	    }
	    ki_rtp->msghdr.rtm_errno = 0;
	    break;
	    
	case EDQUOT:
	    /* The new gateway address is longer than the old one. This */
	    /* can only happen when we changed an RTM_ADD into an RTM_CHANGE */
	    switch (ki_rtp->msghdr.rtm_type) {
	    case RTM_CHANGE:
		/* Do an ADD later */
		retry_type = RTM_ADD;

		/* But a delete now */
		ki_rtp->msghdr.rtm_type = RTM_DELETE;
		goto retry;
	    }
	    /* Fall-Through */

	default:
	    task_quit(ki_rtp->msghdr.rtm_errno);
	    break;
		
	case 0:
	    break;
    }

    if (!ki_rtp->msghdr.rtm_errno && retry_type) {
	ki_rtp->msghdr.rtm_type = retry_type;
	retry_type = 0;
	goto retry;
    }
    
    return ki_rtp->msghdr.rtm_errno;
}


/* Process as many requests on the queue as possible */
static inline int
krt_runqueue(tp)
task *tp;
{
    int error = 0;
    struct rtm_msg *rtp, *rtpn;

    for (rtp = rtm_head.rtm_forw; rtp != &rtm_head; rtp = rtpn) {
	if (error = krt_send(tp, rtp)) {
	    timer_set(KRT_TIMER(tp),
		      krt_waittime,
		      (time_t) 0);
	    KRT_BUMP(krt_waittime);		/* Increase timeout value if it fails again */
	    break;
	}

	/* Remove this element from the queue and free it */
	remque((struct qelem *) rtp);
	rtpn = rtp->rtm_forw;
	task_mem_free(krt_task, (caddr_t) rtp);

	timer_reset(KRT_TIMER(tp));		
	KRT_RESET(krt_waittime);		/* Reset delay timer */
    }

    return error;
}


/* Fill in a request and enqueue it */
static int
krt_request(type, rt, router)
int type;
rt_entry *rt;
sockaddr_un *router;
{
    int size;
    int netmask = FALSE;
    int error = 0;
    struct rtm_msg *rtp;
    struct sockaddr *ap;
    struct sockaddr *dest = sock2unix(rt->rt_dest);
    struct sockaddr *mask = sock2unix(rt->rt_dest_mask);
    struct sockaddr *gateway = sock2unix(router);

    tracef("KERNEL %-6s %-15A",
	   trace_state(rtm_type_bits, type - 1),
	   rt->rt_dest);

    if (!BIT_TEST(rt->rt_flags, RTF_HOST)) {
	tracef(" mask %-15A",
	   rt->rt_dest_mask);
    }

    tracef(" gateway %-15A %s <%s>",
	   router,
	   trace_state(rt_proto_bits, rt->rt_proto),
	   trace_bits(rt_flag_bits, rt->rt_flags));

    if (krt_install) {
	size = sizeof(struct rt_msghdr) + dest->sa_len;
	if (!BIT_TEST(rt->rt_state, RTS_HOSTROUTE)) {
	    netmask = TRUE;
	    size += mask->sa_len ? mask->sa_len : sizeof(u_long);
	}
	switch (type) {
	case RTM_ADD:
	case RTM_CHANGE:
	    size += gateway->sa_len;
	    break;

	default:
	    gateway = (struct sockaddr *) 0;
	}

	rtp = (struct rtm_msg *) task_mem_calloc(krt_task, 1, size);
	rtp->msghdr.rtm_type = type;
	rtp->msghdr.rtm_flags = rt->rt_flags;
	if (rt->rt_ifp && BIT_TEST(rt->rt_ifp->int_state, IFS_UP)) {
	    BIT_SET(rtp->msghdr.rtm_flags, RTF_UP);
	}
	rtp->msghdr.rtm_msglen = size;

	/* XXX - set metrics */

	ap = (struct sockaddr *) (rtp + 1);

	bcopy((caddr_t) dest, (caddr_t) ap, dest->sa_len);
	RTM_ADDR(ap);
	BIT_SET(rtp->msghdr.rtm_addrs, RTA_DST);

	if (router) {
	    bcopy((caddr_t) gateway, (caddr_t) ap, gateway->sa_len);
	    RTM_ADDR(ap);
	    BIT_SET(rtp->msghdr.rtm_addrs, RTA_GATEWAY);
	}

	/* Provide a mask if this is not a host route */
	if (netmask) {
	    int len = mask->sa_len;
	    caddr_t cp;
	    
	    /* Convert our netmask format into the kernel's netmask format. */
	    /* The kernel does not want the address family nor trailing zeros. */
	    if (len) {
		bcopy((caddr_t) mask, (caddr_t) ap, mask->sa_len);
		ap->sa_family = AF_UNSPEC;
		ap->sa_len = 0;
		for (cp = (caddr_t) ap + len - 1; !*cp && cp > (caddr_t) ap; cp--) {
		    len--;
		}
		ap->sa_len = len;
	    }

	    /* If the netmask is zero length, make sure there is at least a */
	    /* long word of zeros present */
	    if (!len) {
		len = sizeof(u_long);
		bzero((caddr_t) ap, len);
	    }

	    RTM_ADDR(ap);
	    BIT_SET(rtp->msghdr.rtm_addrs, RTA_NETMASK);
	}

	rtp->msghdr.rtm_msglen = (caddr_t)ap - (caddr_t) &rtp->msghdr;

	/* Insert at the end of the queue */
	insque((struct qelem *) rtp, (struct qelem *) rtm_head.rtm_back);

	/* If this is the first entry on the queue, run the queue */
	if (rtm_head.rtm_forw == rtp) {
	    trace(TR_KRT, 0, NULL);
	    error = krt_runqueue(krt_task);
	} else {
	    trace(TR_KRT, 0, ": defered");
	}
    } else {
	trace(TR_KRT, 0, NULL);
    }

    return error;
}


/* Process a route socket response from the kernel */
static void
krt_recv(tp)
task *tp;
{
    int size;
    int delete = FALSE;
    flag_t table;
    struct rt_msghdr *rtp = (struct rt_msghdr *) task_recv_buffer;
    struct sockaddr *ap;
    sockaddr_un *dst = (sockaddr_un *) 0;
    sockaddr_un *gateway = (sockaddr_un *) 0;
    sockaddr_un *netmask = (sockaddr_un *) 0;
    sockaddr_un *author = (sockaddr_un *) 0;
    rt_entry *rt;

    if (task_receive_packet(tp, &size)) {
	return;
    }
    if (BIT_TEST(trace_flags, TR_KRT)) {
	krt_trace(tp, "RECV", rtp, 0);
    }

    if (BIT_TEST(rtp->rtm_flags, RTF_CLONING|RTF_LLINFO)) {
	/* Skip cloning masks and link level addresses */
	return;
    }

    ap = (struct sockaddr *) (rtp + 1);

    if (BIT_TEST(rtp->rtm_addrs, RTA_DST)) {
	dst = sock2gated(ap);
	RTM_ADDR(ap);
	if (socktype(dst) != AF_INET) {
	    return;
	}
    }
    if (BIT_TEST(rtp->rtm_addrs, RTA_GATEWAY)) {
	gateway = sock2gated(ap);
	RTM_ADDR(ap);
    }
    if (BIT_TEST(rtp->rtm_addrs, RTA_NETMASK)) {
	struct sockaddr addr;

	bzero((caddr_t) &addr, sizeof (addr));
	bcopy((caddr_t) ap, (caddr_t) &addr, ap->sa_len);
	if (addr.sa_len < 2) {
	    addr.sa_len = 2;	/* Length and family */
	}
	addr.sa_family = socktype(dst);
	netmask = mask_locate(sock2gated(&addr));
	RTM_ADDR(ap);
    } else if (BIT_TEST(rtp->rtm_flags, RTF_HOST)) {
	netmask = (sockaddr_un *) 0;
    } else {
	netmask = mask_inet_natural(dst);
    }
    if (BIT_TEST(rtp->rtm_addrs, RTA_GENMASK)) {
	RTM_ADDR(ap);
    }
    if (BIT_TEST(rtp->rtm_addrs, RTA_IFP)) {
	RTM_ADDR(ap);
    }
    if (BIT_TEST(rtp->rtm_addrs, RTA_IFA)) {
	RTM_ADDR(ap);
    }
    if (BIT_TEST(rtp->rtm_addrs, RTA_AUTHOR)) {
	author = sock2gated(ap);
	RTM_ADDR(ap);
    }
    if (rtp->rtm_pid == task_pid) {
	trace(TR_ALL, LOG_ERR, "krt_recv: received a response to my own request");
	return;
    }
    
    /* Ignore incomplete messages and responses in error */
    if (!BIT_TEST(rtp->rtm_flags, RTF_DONE) || rtp->rtm_errno) {
	return;
    }

    /* XXX - should protocol be different for interface routes? */

    switch (rtp->rtm_type) {
    case RTM_CHANGE:
	rt_open(krt_task);
	if (rt = rt_locate(RTS_HOSTROUTE | RTS_NETROUTE,
			   dst,
			   netmask,
			   RTPROTO_KRT)) {
	    if (!(rt = rt_change(rt,
				 gateway,
				 (metric_t) 0,
				 (time_t) 0,	/* XXX - rtm_expire?? */
				 RTPREF_KRT))) {
		trace(TR_ALL, LOG_ERR, "krt_recv: error changing route to %A/%A via %A",
		      dst,
		      netmask,
		      gateway);
	    }
	} else {
	    /* Route did not exist, add new one */
	    goto add;
	}
	rt_close(krt_task, (gw_entry *) 0, 1, NULL);
	break;

    case RTM_DELETE:
    case RTM_OLDDEL:
	/* XXX - Deletion of a non-kernel route should cause it to be put back! */
	delete = TRUE;
	/* Fall Thru */

    case RTM_ADD:
    case RTM_OLDADD:
	rt_open(krt_task);
	if (!rtp->rtm_pid && !BIT_TEST(rtp->rtm_flags, RTF_GATEWAY)) {
	    /* Interface being added or deleted */
	    /* XXX - need to do an explicit add or delete, passing network, mask and any flags, rtbit_set */
	    /* XXX - needs to be called for this route so we don't get an error adding it to the kernel */
	    if_check(tp);
	    break;
	}
	    
	/* Delete existing route */
	if (rt = rt_locate(RTS_HOSTROUTE | RTS_NETROUTE,
			   dst,
			   netmask,
			   RTPROTO_KRT)) {
	    if (rt == rt->rt_active) {
		/* Indicate it is not installed in the kernel */
		krt_not_installed(rt);
	    }
	    (void) rt_delete(rt);
	} else if ((rt = rt_locate(RTS_HOSTROUTE | RTS_NETROUTE,
				   dst,
				   netmask,
				   RTPROTO_ANY)) &&
		   rt == rt->rt_active &&
		   !BIT_TEST(rt->rt_state, RTS_NOTINSTALL)) {
	    /* Someone is fucking with an installed active route, put it back */
	    krt_change((rt_entry *) 0, (sockaddr_un *) 0, rt);
	}
	    

	if (delete) {
	    goto close;
	}
	    
    add:
	/* Add new route */
	if (BIT_TEST(rtp->rtm_flags, RTF_HOST)) {
	    table = RTS_HOSTROUTE;
	} else if (if_withnet(dst)) {
	    table = RTS_INTERIOR;
	} else {
	    table = RTS_EXTERIOR;
	}
	    
	if (rt = rt_add(dst,
			netmask,
			gateway,
			(gw_entry *) 0,
			(metric_t) 0,
			RTS_NOAGE|RTS_RETAIN|table,
			rtp->rtm_flags,
			BIT_TEST(rtp->rtm_flags, RTF_GATEWAY) ? RTPROTO_KRT : RTPROTO_DIRECT,
			(as_t) 0,
			(time_t) 0,	/* XXX - rtm_expire?? */
			RTPREF_KRT)) {
	    if (rt == rt->rt_active) {
		krt_installed(rt);
		goto close;
	    } else {
		trace(TR_ALL, LOG_ERR, "krt_recv: kernel route not active %A/%A via %A - %s",
		      rt->rt_active ? "changing" : "deleting");		      
	    }
	} else {
	    /* Could not install route */
	    trace(TR_ALL, LOG_ERR, "krt_recv: error adding route to %A/%A via %A - deleting",
		  dst,
		  netmask,
		  gateway);
	    if (netmask) {
		/* Zero address bits without corresponding mask bits. */
		/* A route added with an improper mask needs this to be removed */
		sockmask(dst, netmask);
	    }
	}

	/* Delete bogus route */
	krt_delete_dst(krt_task,
		       rt ? rt->rt_active : (rt_entry *) 0,
		       dst,
		       netmask,
		       gateway,
		       rtp->rtm_flags);

    close:
	rt_close(krt_task, (gw_entry *) 0, 1, NULL);
	break;

    case RTM_LOSING:
	trace(TR_KRT, 0, "krt_recv: kernel reports TCP lossage on route to %A/%A via %A",
	      dst,
	      netmask,
	      gateway);
	break;

    case RTM_REDIRECT:
	trace("krt_recv: redirect to %A",
	      dst);
	if (netmask) {
	    tracef("/%A ",
		   netmask);
	}
	trace(TR_KRT, 0, "via %A from %A",
	      gateway,
	      author);
	rt_redirect(tp,
		    dst,
		    netmask,
		    gateway,
		    author,
		    BIT_TEST(rtp->rtm_flags, RTF_HOST) ? TRUE : FALSE);
	break;

    case RTM_MISS:
	trace(TR_KRT, 0, "krt_recv: kernel can not find route to %A/%A via %A",
	      dst,
	      netmask,
	      gateway);
	break;
	
    case RTM_GET:
    case RTM_LOCK:
    case RTM_RESOLVE:
    default:
	/* ignore */
	break;
    }
}


/* Retry a kernel socket request, it failed the first time */
/*ARGSUSED*/
static void
krt_timeout(tip, interval)
timer *tip;
time_t interval;
{
    krt_runqueue(tip->timer_task);
}


/*
 *	Dump the routing socket queue
 */
static void
krt_dump(tp, fd)
task *tp;
FILE *fd;
{
    struct rtm_msg *rtp;
    struct sockaddr *ap;
    sockaddr_un *dest;

    /*
     * Dump the static gateways
     */
    if (rt_gw_list) {
	(void) fprintf(fd, "\tGateways referenced by static routes:\n");

	gw_dump(fd,
		"\t\t",
		rt_gw_list);

	(void) fprintf(fd, "\n");
    }

    (void) fprintf(fd, "\tRoute socket queue:\n");

    (void) fprintf(fd, "\t\tSequence:\t%d\n",
		   rtm_head.msghdr.rtm_seq);

    for (rtp = rtm_head.rtm_forw; rtp != &rtm_head; rtp = rtp->rtm_forw) {
	(void) fprintf(fd, "\t\t\tlength %u  version %u  type %s(%u)  addrs %s(%x)  pid %d  seq %d  error %d",
		       rtp->msghdr.rtm_msglen,
		       rtp->msghdr.rtm_version,
		       trace_state(rtm_type_bits, rtp->msghdr.rtm_type - 1),
		       rtp->msghdr.rtm_type,
		       trace_bits(rtm_sock_bits, rtp->msghdr.rtm_addrs),
		       rtp->msghdr.rtm_addrs,
		       rtp->msghdr.rtm_pid,
		       rtp->msghdr.rtm_seq,
		       rtp->msghdr.rtm_errno);
	if (rtp->msghdr.rtm_errno) {
	    errno = rtp->msghdr.rtm_errno;
	    (void) fprintf(fd, ": %m\n");
	} else {
	    (void) fprintf(fd, "\n");
	}

	(void) fprintf(fd, "\t\t\tflags %s(%x)",
		       trace_bits(rt_flag_bits, rtp->msghdr.rtm_flags),
		       rtp->msghdr.rtm_flags & 0xffff);
	(void) fprintf(fd, "  locks %s(%x)",
		trace_bits(rtm_lock_bits, rtp->msghdr.rtm_rmx.rmx_locks),
		       rtp->msghdr.rtm_rmx.rmx_locks);
	(void) fprintf(fd, "  inits %s(%x)\n",
		       trace_bits(rtm_lock_bits, rtp->msghdr.rtm_inits),
		       rtp->msghdr.rtm_inits);

	/* Display metrics */
	switch (rtp->msghdr.rtm_type) {
	    case RTM_ADD:
	    case RTM_CHANGE:
	    case RTM_GET:
	    /* XXX - Only print metrics which are locked or inited */
		(void) fprintf(fd, "\t\t\tmtu %u  hopcount %u  expire %u  ssthresh %u\n",
			       rtp->msghdr.rtm_rmx.rmx_mtu,
			       rtp->msghdr.rtm_rmx.rmx_hopcount,
			       rtp->msghdr.rtm_rmx.rmx_expire,
			       rtp->msghdr.rtm_rmx.rmx_ssthresh);
		(void) fprintf(fd, "\t\t\trecvpipe %u  sendpipe %u  rtt %u  rttvar %u\n",
			       rtp->msghdr.rtm_rmx.rmx_recvpipe,
			       rtp->msghdr.rtm_rmx.rmx_sendpipe,
			       rtp->msghdr.rtm_rmx.rmx_rtt,
			       rtp->msghdr.rtm_rmx.rmx_rttvar);
		break;
	}
	ap = (struct sockaddr *) (rtp + 1);

	/* Display addresses */
	if (BIT_TEST(rtp->msghdr.rtm_addrs, RTA_DST)) {
	    (void) fprintf(fd, "\t\t\tdest %A",
			   dest = sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->msghdr.rtm_addrs, RTA_GATEWAY)) {
	    (void) fprintf(fd, "  next hop %A",
			   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->msghdr.rtm_addrs, RTA_NETMASK)) {
	    struct sockaddr addr;

	    bzero((caddr_t) &addr, sizeof (addr));
	    bcopy((caddr_t) ap, (caddr_t) &addr, ap->sa_len);
	    if (addr.sa_len < 2) {
		addr.sa_len = 2;	/* Length and family */
	    }
	    addr.sa_family = socktype(dest);
	    (void) fprintf(fd, "  mask %A",
			   sock2gated(&addr));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->msghdr.rtm_addrs, RTA_GENMASK)) {
	    (void) fprintf(fd, "  genmask %A",
			   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->msghdr.rtm_addrs, RTA_IFP)) {
	    (void) fprintf(fd, "  ifp %A",
			   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->msghdr.rtm_addrs, RTA_IFA)) {
	    (void) fprintf(fd, "  ifa %A",
			   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	if (BIT_TEST(rtp->msghdr.rtm_addrs, RTA_AUTHOR)) {
	    (void) fprintf(fd, "  author %A",
			   sock2gated(ap));
	    RTM_ADDR(ap);
	}
	(void) fprintf(fd, "\n\n");
    }
}


/*
 *	Deal with an interface state change
 */
static void
krt_ifchange(tp, ifp, code)
task *tp;
if_entry *ifp;
int code;
{
    int changes = 0;
    
    rt_entry *rt;

    rt_open(tp);
    
    switch (code) {
        case IFC_UP:
	    RT_WHOLE(rt) {
		if (rt->rt_ifp == ifp && rt->rt_proto == tp->task_rtproto) {
		    /* Restore static routes by making their preference positive again */
		    if (rt->rt_preference < 0) {
			(void) rt_change(rt,
					 (sockaddr_un *) 0,
					 rt->rt_metric,
					 rt->rt_timer_max,
					 -rt->rt_preference);
		    }
		}
	    } RT_WHOLE_END(rt) ;
	    break;

        case IFC_ADD:
	    /* Don't believe the interface is up until we see packets from it */
	    break;

	case IFC_DOWN:
	    RT_WHOLE(rt) {
		if (rt->rt_ifp == ifp && rt->rt_proto == tp->task_rtproto) {
		    /* Hide any static routes by giving them negative preferences */
		    if (rt->rt_preference > 0) {
			(void) rt_change(rt,
					 (sockaddr_un *) 0,
					 rt->rt_metric,
					 rt->rt_timer_max,
					 -rt->rt_preference);
		    }
		}
	    } RT_WHOLE_END(rt) ;
	    break;

	case IFC_DELETE:
	    RT_WHOLE(rt) {
		if (rt->rt_ifp == ifp &&
		    rt->rt_proto == tp->task_rtproto &&
		    !BIT_TEST(rt->rt_state, RTS_DELETE)) {
		    /* Delete any static routes we learned via this interface */
		    rt = rt_delete(rt);
		}
	    } RT_WHOLE_END(rt) ;
	    break;
    }

    rt_close(tp, (gw_entry *) 0, changes, NULL);

}


#else	/* ROUTING_SOCKET */

#define	RTM_ADD		SIOCADDRT
#define	RTM_DELETE	SIOCDELRT

static inline int
krt_request(type, rt, router)
int type;
rt_entry *rt;
sockaddr_un *router;
{
    int request_error = 0;
    int do_ioctl = !BIT_TEST(task_state, TASKS_TEST) && krt_install;
    struct rtentry krt;

    tracef("KERNEL %-6s %-15A",
	   (type == RTM_ADD) ? "ADD" : "DELETE",
	   rt->rt_dest);

    if (!BIT_TEST(rt->rt_flags, RTF_HOST)) {
	tracef(" mask %-15A",
	       rt->rt_dest_mask);
    }

    tracef(" gateway %-15A %s <%s>",
	   router,
	   trace_state(rt_proto_bits, rt->rt_proto),
	   trace_bits(rt_flag_bits, rt->rt_flags));

    bzero((caddr_t) & krt, sizeof(krt));
    krt.rt_dst = *sock2unix(rt->rt_dest);	/* struct copy */
    krt.rt_gateway = *sock2unix(router);	/* struct copy */
    krt.rt_flags = rt->rt_flags;
    if (rt->rt_ifp && BIT_TEST(rt->rt_ifp->int_state, IFS_UP)) {
	BIT_SET(krt.rt_flags, RTF_UP);
    }
    if (do_ioctl && (ioctl(krt_task->task_socket, type, (caddr_t) & krt) < 0)) {
	request_error = errno;
	trace(TR_ALL | TR_NOSTAMP, LOG_ERR, " SIOC%sRT: %m",
	      (type == RTM_ADD) ? "ADD" : "DEL");
    } else {
	trace(TR_KRT | TR_NOSTAMP, 0, NULL);
    }

    return request_error;
}

#endif	/* ROUTING_SOCKET */


static int
krt_change(old_rt, old_router, new_rt)
rt_entry *old_rt;
sockaddr_un *old_router;
rt_entry *new_rt;
{
    int error = 0;
    sockaddr_un *new_router = (sockaddr_un *) 0;

    if (new_rt) {
#ifdef	RTF_REJECT
	if (BIT_TEST(new_rt->rt_flags, RTF_REJECT)) {
	    /* Reject routes need to be installed via the loopback interface */
	    new_router = inet_addr_loopback;
	} else {
	    new_router = new_rt->rt_router;
	}
#else	/* RTF_REJECT */
	new_router = new_rt->rt_router;
#endif	/* RTF_REJECT */
    }

    if (old_rt && new_rt) {
	if (sockaddrcmp(old_router, new_router) &&
	    (old_rt->rt_flags == new_rt->rt_flags)) {
	    /* If nothing has changed, there isn't anything to do */
	    
	    return error;
#ifdef	ROUTING_SOCKET
	} else if (socksize(new_router) <= socksize(old_router)) {
	    /* With the routing socket we can do a change, but only if the */
	    /* length of the new gateway is equal to or less than the */
	    /* length of the old one */
	    error = krt_request(RTM_CHANGE, new_rt, new_router);
	    return error;
#endif	/* ROUTING_SOCKET */
	}
    }

    if (new_rt) {
	error = krt_request(RTM_ADD, new_rt, new_router);
    }

    if (!error && old_rt) {
	error = krt_request(RTM_DELETE, old_rt, old_router);
    }

    return error;
}



 /*	Delete a route given dest, gateway and flags	*/
/* XXX - This is a hack, is there a better way? */
/*ARGSUSED*/
int
krt_delete_dst(tp, rt, dest, mask, gate, flags)
task *tp;
rt_entry *rt;
sockaddr_un *dest;
sockaddr_un *mask;
sockaddr_un *gate;
flag_t flags;
{
    rt_entry my_rt;
    rt_head my_rth;

    bzero((caddr_t) &my_rt, sizeof (my_rt));
    bzero((caddr_t) &my_rth, sizeof (my_rth));
    my_rt.rt_head = &my_rth;
    my_rt.rt_dest = dest;
    my_rt.rt_dest_mask = mask;
    my_rt.rt_router = gate;
    my_rt.rt_flags = flags | RTF_UP | RTF_GATEWAY;
#ifdef	RTF_DYNAMIC
    /* XXX - don't set it all the time */
    my_rt.rt_flags |= RTF_DYNAMIC;
#endif	/* RTF_DYNAMIC */
    my_rt.rt_proto = RTPROTO_REDIRECT;

    (void) krt_change(&my_rt, gate, rt);
    
    return 0;
}


/* Process the change list generated by routing table changes. */
void
krt_flash(rtl)
rt_list *rtl;
{
    rt_head *rth;

    /* Open the routing table in case we make a change */
    rt_open(krt_task);
    
    RT_LIST(rth, rtl) {
	rt_entry *new_rt;
	rt_entry *old_rt = (rt_entry *) 0;

	if (new_rt = rth->rth_active) {
	    /* There is an active route */

	    if (rtbit_isset(new_rt, krt_task->task_rtbit)) {
		if (new_rt->rt_task == krt_task) {
		    /* Routes that I installed don't change */
		    continue;
		}

		/* We are already announcing it, it must be a metric or gateway change */
		old_rt = new_rt;
	    } else if (!BIT_TEST(new_rt->rt_state, RTS_NOTINSTALL)) {
		/* We are not announcing it, this will be our new route */
		
		rtbit_set(new_rt, krt_task->task_rtbit);
	    } else {
		/* Not allowed to announce it */
		
		new_rt = (rt_entry *) 0;
	    }
	}

	if (!old_rt) {
	    /* This was not just a change on the active route */
	    
	    RT_ALLRT(old_rt, rth) {
		/* Search for a route we were announcing */
	    
		if ((old_rt != new_rt) && rtbit_isset(old_rt, krt_task->task_rtbit)) {
		    /* This is the one we were announcing */

		    break;
		}
	    } RT_ALLRT_END(old_rt, rth) ;
	}

	if (new_rt || old_rt) {
	    sockaddr_un *new_router;
	    sockaddr_un *old_router;
	    /* Something has changed */

	    if (old_rt) {
		/* Get the old router address */
		rttsi_get(rth, krt_task->task_rtbit, (byte *) &old_router);
	    } else {
		/* Indicate no old router */
		old_router = (sockaddr_un *) 0;
	    }

	    /* Change the kernel */
	    (void) krt_change(old_rt, old_router, new_rt);

	    /* Set TSI to remember the current router */
	    if (new_rt) {
		/* See if we can make use of the old sockaddr */
		if (old_router && sockaddrcmp(old_router, new_rt->rt_router)) {
		    /* Use old router */
		    new_router = old_router;
		} else {
		    /* Set new router */
		    sockdup(new_rt->rt_router, new_router);
		}
	    } else {
		/* Indicate no old router */
		new_router = (sockaddr_un *) 0;
	    }

	    if (new_router != old_router) {
		/* Change the TSI to point at new router */
		rttsi_set(rth, krt_task->task_rtbit, (byte *) &new_router);
		if (old_router) {
		    /* Free old router */
		    sockfree(old_router);
		}
	    }

	    if (old_rt && old_rt != new_rt) {
		/* Reset the announcement bit on the old route */
		(void) rtbit_reset(old_rt, krt_task->task_rtbit);
	    }
	}
    } RT_LIST_END(rth, rtl) ;

    /* Close the routing table */
    rt_close(krt_task, (gw_entry *) 0, 0, NULL);
}



/*
 *	If we support the routing socket, remove any static routes we
 *	installed. 
 *
 *	Reset the announcement bits on any routes installed in the kernel.
 *	If they don't have RTS_RETAIN set they get removed from the kernel.
 */
static void
krt_terminate(tp)
task *tp;
{
    int changes = 0;
    rt_entry *rt;

    rt_open(tp);
    
    RT_WHOLE(rt) {
	int change = FALSE;
	
#ifdef	ROUTING_SOCKET
	if (rt->rt_proto == tp->task_rtproto &&
#ifdef	RTF_STATIC
	    !BIT_TEST(rt->rt_flags, RTF_STATIC) &&
#endif	/* RTF_STATIC */
	    !BIT_TEST(rt->rt_state, RTS_DELETE)) {
	    rt = rt_delete(rt);
	    change = TRUE;
	}
#endif	/* ROUTING_SOCKET */

	if (rtbit_isset(rt, tp->task_rtbit)) {
	    sockaddr_un *router = (sockaddr_un *) 0;

	    /* Get the old router */
	    rttsi_get(rt->rt_head, tp->task_rtbit, (byte *) &router);


	    if (!BIT_TEST(rt->rt_state, RTS_RETAIN)) {
		/* Remove it from the kernel */
		(void) krt_change(rt, router, (rt_entry *)0);
	    }

	    /* Reset router and free the socket */
	    sockfree(router);
	    router = (sockaddr_un *) 0;
	    rttsi_set(rt->rt_head, tp->task_rtbit, (byte *) &router);
	    change = TRUE;

	    /* Reset the bit */
	    rt = rtbit_reset(rt, tp->task_rtbit);
	}

	if (change) {
	    changes++;
	}
    } RT_WHOLE_END(rt) ;

    rt_close(tp, (gw_entry *) 0, changes, NULL);
    
    rtbit_free(tp, tp->task_rtbit);

    task_delete(tp);
}


#ifdef	notdef
typedef union {
    struct ifaddr a;
    struct in_ifaddr in;
#ifdef	AF_LINK
    struct iso_ifaddr iso;
#endif	/* AF_LINK */
} ifaddr_un;

/* Read interfaces from kernel */
void
krt_ifread(skip)
int skip;
{
    char if_name[IFNAMSIZ+1];
    struct ifnet ifn;
    off_t ifnet_p;
    int if_index = 0;

    if (skip) {
	return;
    }

    trace(TR_INT, 0, "krt_ifread: Read kernel interface list");

    if (!krt_ifnet->n_value) {
	trace(TR_ALL, LOG_ERR, "krt_rtread: ifnet not in namelist");
	task_quit(errno);
    }

    /* Get ifnet pointer */
    if (KVM_READ((off_t) krt_ifnet->n_value,
		 (caddr_t) &ifnet_p,
		 sizeof (ifnet_p)) < 0) {
	trace(TR_ALL, LOG_ERR, "krt_ifread: %s",
	      KVM_GETERR("kvm_read error"));
	task_quit(errno);
    }
    if (!ifnet_p) {
	trace(TR_ALL, LOG_ERR, "krt_ifread: no interfaces!");
	task_quit(errno);
    }
    
    /* Scan physical interface list */
    do {
	ifaddr_un ifa;
	flag_t flags;
	off_t ifaddr_p;

	if (KVM_READ(ifnet_p, (caddr_t) &ifn, sizeof (struct ifnet)) < 0) {
	    trace(TR_ALL, LOG_ERR, "krt_ifread: %s",
		  KVM_GETERR("kvm_read error"));
	    task_quit(errno);
	}
	if (KVM_READ((off_t) ifn.if_name, if_name, IFNAMSIZ) < 0) {
	    trace(TR_ALL, LOG_ERR, "krt_ifread: %s",
		  KVM_GETERR("kvm_read error"));
	    task_quit(errno);
	}
	ifn.if_name = if_name;
	if_name[IFNAMSIZ] = (char) 0;
#ifdef	AF_LINK
	if_index = ifn.if_index;
#else	/* AF_LINK */
	if_index++;
#endif	/* AF_LINK */
	flags = if_flags(ifn.if_flags);
	trace(TR_ALL, 0, "krt_ifread: %s%d: index: %d mtu %d metric %d flags %x",
	      ifn.if_name,
	      ifn.if_unit,
	      if_index,
	      ifn.if_mtu,
	      ifn.if_metric,
	      flags);

	/* Scan the protocol address list for this interface */
	for (ifaddr_p = (off_t) ifn.if_addrlist;
	     ifaddr_p;
	     ifaddr_p = (off_t) ifa.a.ifa_next) {
	    struct sockaddr *ifa_addr, *ifa_daddr, *ifa_netmask = (struct sockaddr *) 0;
#ifdef	AF_LINK
	    byte addr_buf[BUFSIZ], *ap = addr_buf;
#endif	/* AF_LINK */

	    if (KVM_READ(ifaddr_p, (caddr_t) &ifa, sizeof (ifa)) < 0) {
		trace(TR_ALL, LOG_ERR, "krt_ifread: %s",
		      KVM_GETERR("kvm_read error"));
		task_quit(errno);
	    }
#ifdef	AF_LINK
	    if (ifa.a.ifa_addr) {
		if (KVM_READ((off_t) ifa.a.ifa_addr,
			     (caddr_t) ap,
			     BUFSIZ - (ap - addr_buf)) < 0) {
		    trace(TR_ALL, LOG_ERR, "krt_ifread: %s",
			  KVM_GETERR("kvm_read error"));
		    task_quit(errno);
		}
		ifa_addr = (struct sockaddr *) ap;
		ap += ifa_addr->sa_len;
	    }
	    if (BIT_TEST(flags, IFS_POINTOPOINT|IFS_BROADCAST) && ifa.a.ifa_dstaddr) {
		if (KVM_READ((off_t) ifa.a.ifa_dstaddr,
			     (caddr_t) ap,
			     BUFSIZ - (ap - addr_buf)) < 0) {
		    trace(TR_ALL, LOG_ERR, "krt_ifread: %s",
			  KVM_GETERR("kvm_read error"));
		    task_quit(errno);
		}
		ifa_daddr = (struct sockaddr *) ap;
		ap += ifa_daddr->sa_len;
	    }    
	    if (ifa.a.ifa_netmask) {
		if (KVM_READ((off_t) ifa.a.ifa_netmask,
			     (caddr_t) ap,
			     BUFSIZ - (ap - addr_buf)) < 0) {
		    trace(TR_ALL, LOG_ERR, "krt_ifread: %s",
			  KVM_GETERR("kvm_read error"));
		    task_quit(errno);
		}
		ifa_netmask = (struct sockaddr *) ap;
		ap += ifa_netmask->sa_len;
	    }

#else	/* AF_LINK */
	    ifa_addr = &ifa.a.ifa_addr;
	    ifa_daddr = &ifa.a.ifa_dstaddr;

	    switch (ifa_addr->sa_family) {
	    case AF_INET:
		ifa_netmask = sock2unix(sockbuild_in(0, ifa.in.ia_subnetmask));
		break;
	    }
#endif	/* AF_LINK */
	    tracef("krt_ifread: %s%d: address %A netmask %A",
		   ifn.if_name,
		   ifn.if_unit,
		   ifa_addr,
		   ifa_netmask);
	    if (BIT_TEST(flags, IFS_BROADCAST)) {
		tracef(" broadcast %A",
		       ifa_daddr);
	    } else if (BIT_TEST(flags, IFS_POINTOPOINT)) {
		tracef(" destaddr %A",
		       ifa_daddr);
	    }

	    trace(TR_ALL, 0, NULL);
	    switch (ifa_addr->sa_family) {
	    case AF_INET:
		trace(TR_ALL, 0, "krt_ifread: %s%d: inet: net %x netmask %x subnet %x subnetmask %x broadcast %x",
		      ifn.if_name,
		      ifn.if_unit,
		      ifa.in.ia_net,
		      ifa.in.ia_netmask,
		      ifa.in.ia_subnet,
		      ifa.in.ia_subnetmask,
		      ifa.in.ia_netbroadcast.s_addr);
		break;
#ifdef	ISOPROTO_RAW
	    case AF_ISO:
		trace(TR_ALL, 0, "krt_ifread: %s%d: iso: address %A netmask %A",
		      ifn.if_name,
		      ifn.if_unit,
		      ifa_addr,
		      ifa_netmask);
		break;
#endif	/* ISOPROTO_RAW */
	    }
	}
	trace(TR_ALL, 0, NULL);
    } while (ifnet_p = (off_t) ifn.if_next) ;
}
#endif	/* notdef */


static void
krt_tsi_dump(rth, data, buf)
rt_head *rth;
caddr_t *data;
char *buf;
{
    sockaddr_un *gw;

    rttsi_get(rth, krt_task->task_rtbit, (byte *) &gw);

    if (gw) {
	(void) sprintf(buf, "KERNEL gateway %-15A",
		       gw);
    }
		   
    return;
}


 /*  Initilize the kernel routing table function.  First, create a	*/
 /*  task to hold the socket used in manipulating the kernel routing	*/
 /*  table.  Second, read the initial kernel routing table into		*/
 /*  gated's routing table.						*/
void
krt_init()
{
    int saveinstall = krt_install;
    int i, skip = FALSE;
    int krt_socket;
    struct nlist *nl = (struct nlist *) 0;

#ifndef	PF_ROUTE
#define	PF_ROUTE	PF_INET
#endif				/* AF_ROUTE */
    if ((krt_socket = task_get_socket(PF_ROUTE, SOCK_RAW, AF_UNSPEC)) < 0) {
	task_quit(errno);
    }
    krt_task = task_alloc("KRT");
    krt_task->task_flags = TASKF_LAST;
    krt_task->task_proto = IPPROTO_RAW;
    krt_task->task_socket = krt_socket;
#ifdef	ROUTING_SOCKET
    krt_task->task_dump = krt_dump;
    krt_task->task_recv = krt_recv;
    krt_task->task_ifchange = krt_ifchange;
    krt_task->task_n_timers = KRT_TIMER_MAX;
#endif				/* ROUTING_SOCKET */
    krt_task->task_terminate = krt_terminate;
    krt_task->task_rtproto = RTPROTO_KERNEL;
    krt_task->task_priority = TASKPRI_KERNEL;
    krt_task->task_rtbit = rtbit_alloc(krt_task,
				       sizeof(sockaddr_un *),
				       (caddr_t) 0,
				       krt_tsi_dump);	/* Allocate a bit */
    if (!task_create(krt_task)) {
	task_quit(EINVAL);
    }
#ifdef	ROUTING_SOCKET
    /* Allocate buffer space */
    task_alloc_recv(krt_task, BUFSIZ);
    task_alloc_send(krt_task, BUFSIZ);

    if (task_set_option(krt_task, TASKOPTION_NONBLOCKING, TRUE) < 0) {
	task_quit(errno);
    }
    /* Indicate we do not want to see our packets */
    if (task_set_option(krt_task, TASKOPTION_USELOOPBACK, FALSE) < 0) {
	task_quit(errno);
    }
    
    (void) timer_create(krt_task,
			KRT_TIMER_TIMEOUT,
			"Timeout",
			TIMERF_ABSOLUTE,
			(time_t) 0,
			(time_t) 0,
			krt_timeout,
			(caddr_t) 0);
#endif				/* ROUTING_SOCKET */


    /* Build nlist from symbol names */
    nl = (struct nlist *) task_mem_calloc(krt_task, NL_SIZE, sizeof(struct nlist));
    for (i = NL_SIZE; i--;) {
	/* Use bcopy to avoid warning about const char * */
	bcopy((caddr_t) & nl_names[i].nl_name, (caddr_t) & nl[i].n_name, sizeof(char *));
#ifdef	NLIST_NOUNDER
	if (nl[i].n_name) {
	    nl[i].n_name++;
	}
#endif				/* NLIST_NOUNDER */
	if (nl_names[i].nl_ptr) {
	    *nl_names[i].nl_ptr = &nl[i];
	}
    }

    if (KVM_OPENFILES(NULL, NULL, NULL) == -1) {
	trace(TR_ALL, LOG_ERR, "krt_init: %s",
	      KVM_GETERR("kvm_open error"));

	if (BIT_TEST(task_state, TASKS_TEST)) {
	    skip = TRUE;
	} else {
	    task_quit(errno);
	}
    }
    if (!skip && (KVM_NLIST(nl) == -1)) {
	trace(TR_ALL, LOG_ERR, "krt_init: %s",
	      KVM_GETERR("kvm_nlist error"));

	if (BIT_TEST(task_state, TASKS_TEST)) {
	    skip = TRUE;
	} else {
	    task_quit(errno);
	}
    }
#ifndef vax11c
    if (krt_version->n_value && !skip) {
	char *p;

	krt_version_kernel = (char *) task_mem_calloc(krt_task, 1, BUFSIZ);
	if (KVM_READ(krt_version->n_value, krt_version_kernel, BUFSIZ - 1) < 0) {
	    trace(TR_ALL, LOG_ERR, "krt_init: %s",
		  KVM_GETERR("kvm_read error"));
	    task_quit(errno);
	}
	if (p = (char *) index(krt_version_kernel, '\n')) {
	    *p = NULL;
	}
	p = task_mem_strdup(krt_task, krt_version_kernel);
	task_mem_free(krt_task, krt_version_kernel);
	krt_version_kernel = p;
	trace(TR_INT, 0, NULL);
	trace(TR_INT, 0, "krt_init: %s = %s",
	      krt_version->n_name,
	      krt_version_kernel);
    } else {
	krt_version_kernel = NULL;
    }
#else				/* vax11c */
    if (krt_multinet_version->n_value && krt_multinet_product_name->n_value && !skip) {
	char *p;

	krt_version_kernel = task_mem_calloc(krt_task, 1, BUFSIZ);
	if (KVM_READ(krt_multinet_product_name->n_value, krt_version_kernel, BUFSIZ - 2) < 0) {
	    trace(TR_ALL, LOG_ERR, "krt_init: %s",
		  KVM_GETERR("kvm_read error"));
	    task_quit(errno);
	}
	(void) strcat(krt_version_kernel, " ");
	if (KVM_READ(krt_multinet_version->n_value,
		     krt_version_kernel + strlen(krt_version_kernel),
		     BUFSIZ - 1 - strlen(krt_version_kernel)) < 0) {
	    trace(TR_ALL, LOG_ERR, "krt_init: %s",
		  KVM_GETERR("kvm_read error"));
	    task_quit(errno);
	}
	p = task_mem_strdup(krt_task, krt_version_kernel);
	task_mem_free(krt_task, krt_version_kernel);
	krt_version_kernel = p;
	trace(TR_INT, 0, "krt_init: %s %s = %s",
	      krt_multinet_product_name->n_name,
	      krt_multinet_version->n_name,
	      krt_version_kernel);
    } else {
	krt_version_kernel = NULL;
    }
#endif				/* vax11c */

    rt_open(krt_task);

#ifdef	notdef
    /* Read the interface configuration */
    krt_ifread(skip);
#endif	/* notdef */

    /* Read the kernel's routing table */
    krt_rtread(skip);

    rt_close(krt_task, (gw_entry *) 0, 0, NULL);

    krt_install = saveinstall;

    if (nl) {
	task_mem_free(krt_task, (caddr_t) nl);
    }
    if (!skip && (KVM_CLOSE() == -1)) {
	trace(TR_ALL, LOG_ERR, "kvm_init: %s",
	      KVM_GETERR("kvm_close error"));
    }
}
