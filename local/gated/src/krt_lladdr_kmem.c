/*
 *  $Id: krt_lladdr_kmem.c,v 1.7.2.3 1995/05/01 16:24:50 jch Exp $
 */

/* %(Copyright.header) */

#define	INCLUDE_KVM
#define	INCLUDE_CTYPE
#define	INCLUDE_ETHER
#define	INCLUDE_IF
#include "include.h"
#include "krt.h"
#include "krt_var.h"


u_long krt_ifnet;

/*
 *	Default krt_lladdr, poke around in the kernel
 */

/*
 * Obtain physical address of the interface by peeking in the kernel.
 * This *hack* assumes that the interface uses an arpcom structure where
 * the physical address resides immediately after the ifnet structure.
 */
sockaddr_un *
krt_lladdr __PF1(ifr, struct ifreq *)
{
    struct ifnet *ifp, *ifnet;
    int unit = 0;
    size_t namelen;

    if (!kd) {
	return (sockaddr_un *) 0;
    }
    
    /* Get length of name and fetch unit */
    {
	register char *sp = ifr->ifr_name;
	char *lp = ifr->ifr_name + IFNAMSIZ;

	while (isalpha(*sp)) {
	    sp++;
	}

	namelen = sp - ifr->ifr_name;

	do {
	    unit = (unit * 10) + (*sp - '0');
	} while (*++sp && sp < lp) ;
    }

    if (KVM_READ(kd,
		 krt_ifnet,
		 &ifnet,
		 sizeof (ifnet)) < 0) {
	trace_log_tp(krt_task,
		     0,
		     LOG_ERR,
		     ("krt_lladdr: reading ifnet for %.*s: %s",
		      IFNAMSIZ, ifr->ifr_name,
		      KVM_GETERR(kd, "kvm_read error")));
	return (sockaddr_un *) 0;
    }

    for (ifp = ifnet; ifp; ifp = ifp->if_next) {
	struct arpcom arpcom;
	char name[IFNAMSIZ];

	/* Read ifnet */
	if (KVM_READ(kd,
		     ifp,
		     &arpcom,
		     sizeof (arpcom)) < 0) {
	    trace_log_tp(krt_task,
			 0,
			 LOG_ERR,
			 ("krt_lladdr: reading arpcom for %.*s: %s",
			  IFNAMSIZ, ifr->ifr_name,
			  KVM_GETERR(kd, "kvm_read error")));
	    break;
	}
	ifp = &arpcom.ac_if;

	if (!ifp->if_addrlist
	    || !ifp->if_name
	    || ifp->if_unit != unit) {
	    /* Not the one we want */

	    continue;
	}
	
	/* And interface name */
	if (KVM_READ(kd,
		     ifp->if_name,
		     name,
		     sizeof name) < 0) {
	    trace_log_tp(krt_task,
			 0,
			 LOG_ERR,
			 ("krt_lladdr: reading interface name for %.*s: %s",
			  IFNAMSIZ, ifr->ifr_name,
			  KVM_GETERR(kd, "kvm_read error")));
	    break;
	}
	ifp->if_name = name;	

	if (!isalpha(name[0])) {
	    /* Something is terribly wrong! */
	    break;
	}

	if (BIT_TEST(ifp->if_flags, IFF_BROADCAST)
#ifdef	IFT_OTHER
	    && krt_type_to_ll(ifp->if_type) == LL_8022
#endif	/* IFT_OTHER */
	    ) {
	    /* Assume broadcast nets have 802.2 addresses */

	    if (unit == ifp->if_unit
		&& !strncmp(ifp->if_name, ifr->ifr_name, namelen)) {
		/* This is the one we want */

		return sockbuild_ll(LL_8022,
				    (byte *) arpcom.ac_enaddr,
#ifdef	KRT_RT_SOCK
				    (size_t) ifp->if_addrlen
#else	/* KRT_RT_SOCK */
#ifndef	ETHER_ADDRLEN
#define	ETHER_ADDRLEN	6
#endif	/* ETHER_ADDRLEN */
				    ETHER_ADDRLEN
#endif	/* KRT_RT_SOCK */
				    );
	    }
	}
    }

    return (sockaddr_un *) 0;
}


/*
 * %(Copyright)
 */
