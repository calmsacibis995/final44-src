/*
 *  $Id: krt_ifread_ioctl.c,v 1.11.2.9 1995/04/13 02:53:06 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_IOCTL
#define	INCLUDE_IF
#define	INCLUDE_ISO_VAR
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

/* Make some assumptions about interface MTU */
static inline mtu_t
krt_mtu __PF1(state, flag_t)
{
    switch (BIT_TEST(state, IFS_POINTOPOINT|IFS_LOOPBACK|IFS_BROADCAST)) {
    case IFS_POINTOPOINT:
	/* Compressed SLIP interfaces use 256, it can't really hurt to specify it */
	/* too low. */
	return 256;

    case IFS_LOOPBACK:
	/* Loopback interfaces use more */
	return 1536;
	
    case IFS_BROADCAST:
	/* Assume an Ethernet */
	return 1500;
    }

    /* A safe assumption? */
    return 576;
}


int
krt_ifread __PF1(save_task_state, flag_t)
{
    u_int indx = 0;
    caddr_t limit;
    struct ifreq *ifrp;
    if_link *ifl = (if_link *) 0;
#ifdef	PROTO_ISO
    static struct iso_ifreq iso_ifreq;
    static struct ifreq *ifr = (struct ifreq *) &iso_ifreq;
#else	/* PROTO_ISO */
    static struct ifreq ifreq;
    static struct ifreq *ifr = &ifreq;
#endif	/* PROTO_ISO */
    register task *tp = krt_task;
    static int s_in = -1;
#ifdef	ISOPROTO_RAW
    static int s_iso = -1;
#endif	/* ISOPROTO_RAW */

    if (tp->task_socket < 0) {
	return EBADF;
    }

    if (!task_send_buffer) {
	/* We need a send buffer */

	task_alloc_send(tp, task_pagesize);
    }
    
    do {
	int rc;
	size_t size;

#if	defined(USE_STREAMIO) && !defined(SUNOS5_0)
	struct strioctl si;
 
	si.ic_cmd = SIOCGIFCONF;
	si.ic_timout = 0;
	si.ic_len = task_send_buffer_len;
	si.ic_dp = (caddr_t) task_send_buffer;
    
	NON_INTR(rc, ioctl(tp->task_socket, I_STR, &si));

	limit = si.ic_dp + (size = si.ic_len);

#else	/* defined(USE_STREAMIO) && !defined(SUNOS5_0) */
	static struct ifconf ifconf_req;

	ifconf_req.ifc_buf = (caddr_t) task_send_buffer;
	ifconf_req.ifc_len = task_send_buffer_len;

#ifdef	SUNOS5_0
	NON_INTR(rc, ioctl(tp->task_socket, 
			   SIOCGIFCONF, 
			   &ifconf_req));
#else	/* SUNOS5_0 */
	rc = task_ioctl(tp->task_socket,
			(u_long) SIOCGIFCONF,
			(void_t) &ifconf_req,
			ifconf_req.ifc_len);
#endif	/* SUNOS5_0 */

	limit = ifconf_req.ifc_buf + (size = ifconf_req.ifc_len);

#endif	/* defined(USE_STREAMIO) && !defined(SUNOS5_0) */
	if (rc != 0) {
	    /* Something is wrong */
	    
	    if (errno == EFAULT) {
		/* Hopefully this means that the buffer is not big enough */
		
		continue;
	    }

	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_ifread: ioctl SIOCGIFCONF: %m"));
	    return errno;
	} else if (size
		   && task_send_buffer_len - size > sizeof *ifr) {
	    /* It appears we have read the complete list */

	    break;
	}
    } while (task_alloc_send(tp, task_send_buffer_len << 1), TRUE) ;

    trace_tp(tp,
	     TR_KRT_IFLIST,
	     TRC_NL_BEFORE,
	     ("krt_iflist: SIOCGIFCONF returns %u bytes",
	      limit - (caddr_t) task_send_buffer));

    /* Tell the IF code that we are passing complete knowledge */
    if_conf_open(tp, TRUE);
    
#define	ifr_size(x) ((unix_socksize(&(x)->ifr_addr) > sizeof((x)->ifr_addr)) ? \
    	sizeof(*(x)) + unix_socksize(&(x)->ifr_addr) - sizeof((x)->ifr_addr) : sizeof(*(x)))
#define	ifr_bump(x) ((struct ifreq *) ((void_t) ((caddr_t) (x) + ifr_size(x))))

    for (ifrp = (struct ifreq *) task_send_buffer;
	 (caddr_t) ifrp < limit;
	 ifrp = ifr_bump(ifrp)) {
	if_info ifi;
	int s = -1;
	u_long siocgifdstaddr = 0;
#ifdef	SIOCGIFNETMASK
	u_long siocgifnetmask = 0;
#endif	/* SIOCGIFNETMASK */
	u_long siocgifbrdaddr = 0;
	char if_name[IFNAMSIZ+1];

	if (TRACE_TP(tp, TR_KRT_IFLIST)) {
	    int size = unix_socksize(&ifrp->ifr_addr);
	    const char *cp = trace_value(task_domain_bits, ifrp->ifr_addr.sa_family);
	    
	    tracef("krt_ifread: name %.*s  length %u  family %u",
		   IFNAMSIZ, ifrp->ifr_name,
		   size,
		   ifrp->ifr_addr.sa_family);
	    if (cp) {
		tracef("(%s)",
		       cp);
	    }

	    switch (ifrp->ifr_addr.sa_family) {
#ifdef	PROTO_INET
	    case AF_INET:
	    {
		struct sockaddr_in *sinp = (struct sockaddr_in *) ((void_t) &ifrp->ifr_addr);
		    
		tracef("  port %u  addr %A",
		       ntohs(sinp->sin_port),
		       sockbuild_in(0, sinp->sin_addr.s_addr));
	    }
		break;
#endif	/* PROTO_INET */

#ifdef	PROTO_ISO
	    case AF_ISO:
	    {
		struct sockaddr_iso *siso = (struct sockaddr_iso *) &ifrp->ifr_addr;
		byte *dp = (byte *) siso->siso_pad;

		tracef("  addr %A",
		       siso->siso_addr.isoa_genaddr,
		       siso->siso_addr.isoa_len);

		if (siso->siso_plen) {
		    tracef("  psel %A",
			   sockbuild_ll(0, dp, siso->siso_plen));
		    dp += siso->siso_plen;
		}
		if (siso->siso_slen) {
		    tracef("  ssel %A",
			   sockbuild_ll(0, dp, siso->siso_slen));
		    dp += siso->siso_slen;
		}
		if (siso->siso_tlen) {
		    tracef("  tsel %A",
			   sockbuild_ll(0, dp, siso->siso_tlen));
		}
	    }
		break;
#endif	/* PROTO_ISO */

#ifdef	SOCKADDR_DL
	    case AF_LINK:
	    {
		struct sockaddr_dl *sdl = (struct sockaddr_dl *) &ifrp->ifr_addr;
		byte *dp = (byte *) sdl->sdl_data;
		
		tracef("  index %u  type %u",
		       sdl->sdl_index,
		       sdl->sdl_type);
		if (sdl->sdl_nlen) {
		    tracef("  name %.*s",
			   sdl->sdl_nlen, dp);
		    dp += sdl->sdl_nlen;
		}
		if (sdl->sdl_alen) {
		    tracef("  addr %A",
			   sockbuild_ll(0, dp, sdl->sdl_alen));
		    dp += sdl->sdl_alen;
		}
		if (sdl->sdl_slen) {
		    tracef("  selector %A",
			   sockbuild_ll(0, dp, sdl->sdl_slen));
		}
	    }
		break;
#endif	/* SOCKADDR_DL */
		
	    default:
		tracef("  addr %A",
		       sockbuild_ll(0,
				    (byte *) ifrp->ifr_addr.sa_data,
				    (size_t) (size - ((byte *) ifrp->ifr_addr.sa_data - (byte *) &ifrp->ifr_addr))));
	    }
	    trace_only_tp(tp,
			  TRC_NL_BEFORE,
			  (NULL));
	}

	bzero((caddr_t) &ifi, sizeof (ifi));

	bcopy(ifrp->ifr_name, if_name, IFNAMSIZ);
	if_name[IFNAMSIZ] = (char) 0;
#ifdef	SUNOS5_0
        {
	    register char *cp = index(if_name, ':');

	    /* Remove the :n extension from the name */
	    if (cp) {
		*cp = (char) 0;
	    }
	}
#endif	/* SUNOS5_0 */

	if (!ifl
	    || strncmp(if_name, ifl->ifl_name, IFNAMSIZ)) {
	    flag_t state;
	    metric_t metric;
	    mtu_t mtu;

	    /* And save for ioctls */
	    (void) strncpy(ifr->ifr_name, ifrp->ifr_name, IFNAMSIZ);

#ifdef	SUNOS5_0
	    /* State, MTU and metric are associated with addresses, not the interface */
	    state = mtu = metric = 0;

#else	/* SUNOS5_0 */
	    /* Get interface flags */
	    bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	    if (task_ioctl(tp->task_socket,
			   (u_long) SIOCGIFFLAGS,
			   (char *) ifr, 
			   sizeof (*ifr)) < 0) {
		trace_log_tp(tp,
			     0,
			     LOG_ERR,
			     ("krt_ifread: %s: ioctl SIOCGIFFLAGS: %m",
			      ifr->ifr_name));
		goto Continue;
	    }
	    state = krt_if_flags(ifr->ifr_flags);

	    /* Get a resonable default */
	    mtu = krt_mtu(state);

#ifdef	SIOCGIFMTU
	    /* Get interface MTU */
	    bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	    if (task_ioctl(tp->task_socket,
			   (u_long) SIOCGIFMTU,
			   (char *) ifr,
			   sizeof (*ifr)) < 0) {
#ifdef	notdef
		trace_tp(tp,
			 TR_ALL,
			 ("krt_ifread: %s: ioctl SIOCGIFMTU: %m",
			  ifr->ifr_name));
#endif	/* notdef */
	    } else {
		mtu = ifr->KRT_IFR_MTU;
	    }
#endif	/* SIOCGIFMTU */

	    /* Get interface metric */
#if	defined(SIOCGIFMETRIC) && defined(ifr_metric)
	    bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	    if (task_ioctl(tp->task_socket,
			   (u_long) SIOCGIFMETRIC,
			   (caddr_t)
			   ifr,
			   sizeof (*ifr)) < 0) {
		trace_log_tp(tp,
			     0,
			     LOG_ERR,
			     ("krt_ifread: %s: ioctl SIOCGIFMETRIC: %m",
			      ifr->ifr_name));
		goto Continue;
	    }
	    metric = (ifr->ifr_metric >= 0) ? ifr->ifr_metric : 0;
#else	/* defined(SIOCGIFMETRIC) && defined(ifr_metric) */
	    metric = 0;
#endif	/* defined(SIOCGIFMETRIC) && defined(ifr_metric) */
#endif	/* SUNOS5_0 */


	    {
#ifdef	SOCKADDR_DL
		register struct ifreq *ifrl = ifrp;

		/* Search for an AF_LINK entry because it has */
		/* the index and sometimes the physical address. */
		/* On ``normal'' systems this is the first address, */
		/* but on DEC OSF/1 systems the AF_LINK has been */
		/* observed not to be. */
		for (ifrl = ifrp;
		     (caddr_t) ifrl < limit;
		     ifrl = ifr_bump(ifrl)) {
		    if (strncmp(ifrl->ifr_name, ifrp->ifr_name, IFNAMSIZ)) {
			/* Did not find one in the records for this interface */

			ifrl = (struct ifreq *) 0;
			break;
		    }

		    if (ifrl->ifr_addr.sa_family == AF_LINK) {
			/* Found the AF_LINK entry */
		    
			break;
		    }
		}

		if (ifrl) {
		    struct sockaddr_dl *sdl = (struct sockaddr_dl *) &ifrl->ifr_addr;
		    sockaddr_un *lladdr;

		    if (sdl->sdl_alen) {
			/* We have an address */

			lladdr = sockbuild_ll(krt_type_to_ll(sdl->sdl_type),
					      (byte *) (sdl->sdl_data + sdl->sdl_nlen),
					      (size_t) sdl->sdl_alen);
		    } else {
			/* This system may not supply link-level addresses, */
			/* or this interface may not have one.  Just to be sure */
			/* try to look one up */

			lladdr = krt_lladdr(ifr);
		    }

		    ifl = ifl_addup(tp,
				    ifl_locate_index(sdl->sdl_index),
				    (indx = sdl->sdl_index),
				    state,
				    metric,
				    mtu,
				    sdl->sdl_data,
				    (size_t) sdl->sdl_nlen,
				    lladdr,
				    sock2gated(&ifrp->ifr_addr, unix_socksize(&ifrp->ifr_addr)));
		} else {
#endif	/* SOCKADDR_DL */
		    size_t n_len = strlen(if_name);
		
		    ifl = ifl_addup(tp,
				    ifl_locate_name(if_name, n_len),
				    ++indx,
				    state,
				    metric,
				    mtu,
				    if_name,
				    n_len,
				    krt_lladdr(ifr),
				    (sockaddr_un *) 0);
		}
#ifdef	SOCKADDR_DL
	    }
#endif	/* SOCKADDR_DL */

	    if (TRACE_TP(tp, TR_KRT_IFLIST)) {
		trace_only_tp(tp,
			      0,
			      ("krt_ifread: %s index %d address %A",
			       ifl->ifl_name,
			       ifl->ifl_index,
			       ifl->ifl_addr));
		trace_only_tp(tp,
			      0,
			      ("krt_ifread: %s     metric %u mtu %u state <%s>",
			       ifl->ifl_name,
			       ifl->ifl_metric,
			       ifl->ifl_mtu,
			       trace_bits(if_state_bits, ifl->ifl_state)));
	    }
#ifdef	SUNOS5_0
	} else {
	    /* Always copy the interface name to get address selector */

	    (void) strncpy(ifr->ifr_name, ifrp->ifr_name, IFNAMSIZ);
#endif	/* SUNOS5_0 */
	}

	bzero((caddr_t) &ifi, sizeof (ifi));
	ifi.ifi_link = ifl;

	/* Reject unknown families */
	switch (ifrp->ifr_addr.sa_family) {
#ifdef	PROTO_INET
	case AF_INET:
	    break;
#endif	/* PROTO_INET */

#ifdef	PROTO_ISO
	case AF_ISO:
	    break;
#endif	/* PROTO_ISO */

	default:
	    /* Bogus address */
	    goto Continue;
	}
	    
	/* Copy the interface address */
	ifi.ifi_addr_local = ifi.ifi_addr = sockdup(sock2gated(&ifrp->ifr_addr, unix_socksize(&ifrp->ifr_addr)));

#ifdef	SUNOS5_0
	/* Get interface flags */
	bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	if (task_ioctl(tp->task_socket,
		       (u_long) SIOCGIFFLAGS,
		       (char *) ifr,
		       sizeof (*ifr)) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_ifread: %s: ioctl SIOCGIFFLAGS: %m",
			  ifr->ifr_name));
	    goto Continue;
	}
	ifi.ifi_state = krt_if_flags(ifr->ifr_flags);
	if (BIT_TEST(ifi.ifi_state, IFS_LOOPBACK)) {
	    /* Indicate this is a loopback interface */

	    BIT_SET(ifl->ifl_state, IFS_LOOPBACK);
	}

	/* Get interface MTU */
	bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	if (task_ioctl(tp->task_socket,
		       (u_long) SIOCGIFMTU,
		       (char *) ifr,
		       sizeof (*ifr)) < 0) {
#ifdef	notdef
	    trace_log_tp(tp,
			 0,
			 LOG_INFO,
			 ("krt_ifread: %s: ioctl SIOCGIFMTU: %m",
			  ifr->ifr_name));
#endif	/* notdef */

	    /* Figure out a default */
	    ifi.ifi_mtu = krt_mtu(ifi.ifi_state);
	} else {
	    ifi.ifi_mtu = ifr->KRT_IFR_MTU;
	}

	/* Get interface metric */
	bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	if (task_ioctl(tp->task_socket,
		       (u_long) SIOCGIFMETRIC,
		       (caddr_t) ifr,
		       sizeof (*ifr)) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_ifread: %s: ioctl SIOCGIFMETRIC: %m",
			  ifr->ifr_name));
	    goto Continue;
	}
	ifi.ifi_metric = (ifr->ifr_metric >= 0) ? ifr->ifr_metric : 0;
#else	/* SUNOS5_0 */
	/* Inherit parameters from physical interface */

	ifi.ifi_state = ifl->ifl_state;
	ifi.ifi_metric = ifl->ifl_metric;
	ifi.ifi_mtu = ifl->ifl_mtu;
#endif	/* SUNOS5_0 */

	/* What we do next depends on the family */
	switch (ifrp->ifr_addr.sa_family) {
#ifdef	PROTO_INET
	case AF_INET:
	    /* Specify the right socket for this family */
	    if (s_in < 0) {
		BIT_RESET(task_state, TASKS_INIT|TASKS_TEST);
		s_in = task_floating_socket(tp,
					    task_get_socket(tp, PF_INET, SOCK_DGRAM, 0),
					    "ifread.inet");
		task_state = save_task_state;
	    }
	    s = s_in;
	    if (BIT_TEST(ifi.ifi_state, IFS_POINTOPOINT)) {
		siocgifdstaddr = (u_long) SIOCGIFDSTADDR;
	    }
#ifdef	SIOCGIFNETMASK
	    if (!BIT_TEST(ifi.ifi_state, IFS_LOOPBACK)) {
		siocgifnetmask = (u_long) SIOCGIFNETMASK;
#endif	/* SIOCGIFNETMASK */
	    }
	    if (BIT_TEST(ifi.ifi_state, IFS_BROADCAST)) {
		siocgifbrdaddr = (u_long) SIOCGIFBRDADDR;
	    }
	    break;
#endif	/* PROTO_INET */

#ifdef	PROTO_ISO
	case AF_ISO:
	    /* Specify the right socket for this family */
	    if (s_iso < 0) {
		BIT_RESET(task_state, TASKS_INIT|TASKS_TEST);
		s_iso = task_floating_socket(tp,
					     task_get_socket(tp, PF_ISO, SOCK_DGRAM, 0),
					     "ifread.iso");
		task_state = save_task_state;
	    }
	    s = s_iso;
	    if (BIT_TEST(ifi.ifi_state, IFS_POINTOPOINT)) {
		siocgifdstaddr = SIOCGIFDSTADDR_ISO;
	    } else if (!BIT_TEST(ifi.ifi_state, IFS_LOOPBACK)) {
		siocgifnetmask = SIOCGIFNETMASK_ISO;
	    }
	    break;
#endif	/* PROTO_ISO */

	default:
	    goto Continue;
	}

	if (siocgifdstaddr) {
	    /* Get the destination address for point-to-point interfaces */

	    size_t a_len;

	    bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	    if (task_ioctl(s,
			   siocgifdstaddr,
			   (caddr_t) ifr,
			   sizeof (*ifr)) < 0) {
		trace_log_tp(tp,
			     0,
			     LOG_ERR,
			     ("krt_ifread: %s: ioctl SIOCGIFDSTADDR: %m",
			      ifr->ifr_name));
		goto Continue;
	    }
	    if ((a_len = unix_socksize(&ifr->ifr_dstaddr))
		&& (ifi.ifi_addr = sock2gated(&ifr->ifr_dstaddr, a_len))) {
		ifi.ifi_addr = sockdup(ifi.ifi_addr);
	    } else {
		ifi.ifi_addr = (sockaddr_un *) 0;
	    }
	}
#ifdef	SIOCGIFNETMASK
	if (siocgifnetmask) {
	    bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	    if (task_ioctl(s,
			   siocgifnetmask,
			   (caddr_t) ifr,
			   sizeof (*ifr)) < 0) {
		trace_log_tp(tp,
			     0,
			     LOG_ERR,
			     ("krt_ifread: %s: ioctl SIOCGIFNETMASK: %m",
			      ifr->ifr_name));
		goto Continue;
	    }
#ifdef	SOCKET_LENGTHS
	    /* A zero mask would have a length of zero */
	    if (ifr->ifr_addr.sa_len < 2) {
		ifr->ifr_addr.sa_len = 2;	/* Enough for address and family */
	    }
	    /* Masks don't have an address family specified */
	    if (ifr->ifr_addr.sa_family == AF_UNSPEC
		&& ifi.ifi_addr) {
		ifr->ifr_addr.sa_family = socktype(ifi.ifi_addr);
	    }
#endif	/* SOCKET_LENGTHS */
	    /* Convert the mask */
	    ifi.ifi_netmask = sock2gated(&ifr->ifr_addr, unix_socksize(&ifr->ifr_addr));

	    if (ifi.ifi_netmask) {
		/* We have a mask, get pointer to right one */
		ifi.ifi_netmask = mask_locate(ifi.ifi_netmask);
	    }
	}
#else	/* SIOCGIFNETMASK */
	ifi.ifi_netmask = (sockaddr_un *) 0;
#endif	/* SIOCGIFNETMASK */

	/* Get the broadcast address for broadcast interfaces */
	if (siocgifbrdaddr) {
#ifdef SIOCGIFBRDADDR
/* Some systems (SunOS 3.x where x > 2) do not define ifr_broadaddr */
#ifndef	ifr_broadaddr
#define	ifr_broadaddr	ifr_addr
#endif	/* ifr_broadaddr */
	    bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	    if (task_ioctl(s,
			   siocgifbrdaddr,
			   (caddr_t) ifr,
			   sizeof (*ifr)) < 0) {
		trace_log_tp(tp,
			     0,
			     LOG_ERR,
			     ("krt_ifread: %s: ioctl SIOGIFBRDADDR: %m",
			      ifr->ifr_name));
		goto Continue;
	    }
	    ifi.ifi_addr_broadcast = sock2gated(&ifr->ifr_broadaddr, unix_socksize(&ifr->ifr_broadaddr));
	    if (ifi.ifi_addr_broadcast) {
		ifi.ifi_addr_broadcast = sockdup(ifi.ifi_addr_broadcast);
	    } else {
		trace_log_tp(tp,
			     0,
			     LOG_ERR,
			     ("krt_ifread: no broadcast address for %A (%s)",
			      ifi.ifi_addr_local,
			      ifrp->ifr_name));
		goto Continue;
	    }
#else	/* !SIOCGIFBRDADDR */
	    /* Assume a 4.2 based system with a zeros broadcast */
	    ifi.ifi_addr_broadcast = (sockaddr_un *) 0;
#endif	/* SIOCGIFBRDADDR */
	}

	if (TRACE_TP(tp, TR_KRT_IFLIST)) {
	    tracef("krt_ifread: %s %A",
		   ifl->ifl_name,
		   ifi.ifi_addr_local);
	    if (ifi.ifi_netmask) {
		tracef("/%A",
		       ifi.ifi_netmask);
	    }
	    if (ifi.ifi_addr_broadcast) {
		tracef(" -> %A",
		       ifi.ifi_addr_broadcast);
	    } else if (ifi.ifi_addr != ifi.ifi_addr_local) {
		tracef(" -> %A",
		       ifi.ifi_addr);
	    }
	    trace_only_tp(tp,
			  0,
			  (NULL));
	    trace_only_tp(tp,
			  0,
			  ("krt_ifread: %s     metric %u mtu %u state <%s>",
			   ifl->ifl_name,
			   ifi.ifi_metric,
			   ifi.ifi_mtu,
			   trace_bits(if_state_bits, ifi.ifi_state)));
	}
	
	/* And add the interface */
	if_conf_addaddr(tp, &ifi);
	continue;

    Continue:
	/* Free any allocated addresses */
	ifi_addr_free(&ifi);
    }

    trace_tp(tp,
	     TR_KRT_IFLIST,
	     0,
	     (NULL));
    
    if_conf_close(tp, FALSE);

    return 0;
}
