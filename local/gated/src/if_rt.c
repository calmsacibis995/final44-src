/*
 *  $Id: if_rt.c,v 1.25 1993/12/15 03:01:53 jch Exp $
 */

/* %(Copyright.header) */

/*
 *  Routines for handling routes to interfaces
 */

#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#ifdef	PROTO_ISO
#include "iso.h"
#endif	/* PROTO_ISO */
#include "krt.h"

/*
 *	Add routes for an interface.
 */
static void
if_rtadd __PF1(ifap, if_addr *)
{

    switch (socktype(ifap->ifa_addr)) {
#ifdef	PROTO_ISO
    case AF_ISO:
	return;
#endif	/* PROTO_ISO */

#ifdef	PROTO_INET
    case AF_INET:
#endif	/* PROTO_INET */
    default:
	assert(!ifap->ifa_rt);
	break;
    }

    trace_only_tp(if_task,
		  0,
		  ("if_rtadd: ADD route for interface %s %A/%A",
		   ifap->ifa_name,
		   ifap->ifa_addr,
		   ifap->ifa_netmask));

    int_rtparms.rtp_router = ifap->ifa_addr;
    int_rtparms.rtp_state = RTS_RETAIN;
    int_rtparms.rtp_preference = ifap->ifa_preference;
    int_rtparms.rtp_rtd = (void_t) ifap;

    switch (BIT_TEST(ifap->ifa_state, IFS_LOOPBACK|IFS_POINTOPOINT)) {
    case IFS_LOOPBACK:
	/* Add a host route to the loopback interface */

	BIT_SET(int_rtparms.rtp_state, RTS_NOADVISE);
	int_rtparms.rtp_dest = ifap->ifa_addr;
	int_rtparms.rtp_dest_mask = sockhostmask(ifap->ifa_addr);

	ifap->ifa_rt = rt_add(&int_rtparms);
	break;

    case IFS_POINTOPOINT:
	/*
	 * Add a route to the interface.
	 * 4.2 based systems need the router to be the destination.
	 * 4.3 (and later) based systems like it to be the local address
	 */
	int_rtparms.rtp_dest = ifap->ifa_addr;
	int_rtparms.rtp_dest_mask = sockhostmask(ifap->ifa_addr);
#ifndef	P2P_RT_REMOTE
	/* Interface routes need to point at the local address */
	int_rtparms.rtp_router = ifap->ifa_addr_local;
#endif	/* P2P_RT_REMOTE */

	ifap->ifa_rt = rt_add(&int_rtparms);
	break;

    default:
	/*  Delete any routes to this subnet and add an interface route to  */
	/*  it if we are the most attractive.                               */

	BIT_SET(int_rtparms.rtp_state, RTS_INTERIOR);

	int_rtparms.rtp_dest = ifap->ifa_net;
	int_rtparms.rtp_dest_mask = ifap->ifa_netmask;
	ifap->ifa_rt = rt_add(&int_rtparms);
	break;
    } /* switch */
}


/*
 *	Delete all routes for an interface
 */
void
if_rtdelete __PF1(ifap, if_addr *)
{

    switch (socktype(ifap->ifa_addr)) {
#ifdef	PROTO_ISO
    case AF_ISO:
	return;
#endif	/* PROTO_ISO */

#ifdef	PROTO_INET
    case AF_INET:
#endif	/* PROTO_INET */
    default:
	assert(ifap->ifa_rt);
	break;
    }

    trace_only_tp(if_task,
		  0,
		  ("if_rtdelete: DELETE route for interface %s %A/%A",
		   ifap->ifa_name,
		   ifap->ifa_addr,
		   ifap->ifa_netmask));

    rt_delete(ifap->ifa_rt);
}


/*
 *	Interface is up, make the preference attractive and reset the
 *	RTS_NOADVISE flag.  Also used to change the preference on an
 *	interface
 */
void
if_rtup __PF1(ifap, if_addr *)
{
    if (!ifap->ifa_rt) {
	/* Route not yet installed */

	if_rtadd(ifap);
    } else {
	int loopback = BIT_TEST(ifap->ifa_state, IFS_LOOPBACK);
	sockaddr_un *router =
#ifndef	P2P_RT_REMOTE
	    BIT_TEST(ifap->ifa_state, IFS_POINTOPOINT) ?
		ifap->ifa_addr_local :
#endif	/* P2P_RT_REMOTE */
		    ifap->ifa_addr;
	    

	if (ifap->ifa_rt->rt_preference == ifap->ifa_preference
	    && !BIT_TEST(ifap->ifa_rt->rt_state, RTS_DELETE)
	    && sockaddrcmp(router, RT_ROUTER(ifap->ifa_rt))
	    && (loopback ||
		!BIT_TEST(ifap->ifa_rt->rt_state, RTS_NOADVISE))) {
	    return;
	}

	/* XXX - only log message if it was down */
	trace_log_tp(if_task,
		     0,
		     LOG_WARNING,
		     ("if_rtup: UP route for interface %s %A/%A",
		      ifap->ifa_name,
		      ifap->ifa_addr,
		      ifap->ifa_netmask));

	    /* Make it advertisable */
	    if (!loopback) {
		BIT_RESET(ifap->ifa_rt->rt_state, RTS_NOADVISE);
	    }

	    /* And the preference normal */
	    (void) rt_change(ifap->ifa_rt,
			     ifap->ifa_rt->rt_metric,
			     (metric_t) 0,
			     (metric_t) 0,
			     ifap->ifa_preference,
			     1, &router);
    }
}


/*
 *	Change routes to signify an interface is down.  Set the preference to
 *	be less attractive and set the RTS_NOADVISE bit.
 */
void
if_rtdown __PF1(ifap, if_addr *)
{

    switch (socktype(ifap->ifa_addr)) {
#ifdef	PROTO_ISO
    case AF_ISO:
	return;
#endif	/* PROTO_ISO */

#ifdef	PROTO_INET
    case AF_INET:
#endif	/* PROTO_INET */
    default:
	assert(ifap->ifa_rt);
	break;
    }
    
    trace_log_tp(if_task,
		 0,
		 LOG_WARNING,
		 ("if_rtdown: DOWN route for interface %s %A/%A",
		  ifap->ifa_name,
		  ifap->ifa_addr,
		  ifap->ifa_netmask));

	/* Make it not advertisable */
	BIT_SET(ifap->ifa_rt->rt_state, RTS_NOADVISE);

	/* And the preference normal */
	(void) rt_change(ifap->ifa_rt,
			 ifap->ifa_rt->rt_metric,
			 (metric_t) 0,
			 (metric_t) 0,
			 ifap->ifa_preference_down,
			 ifap->ifa_rt->rt_n_gw, ifap->ifa_rt->rt_routers);
}


/*
 *	We just received a routing packet via an interface.  Make sure
 *	we consider the interface up and reset the timer.
 */
void
if_rtupdate __PF1(ifap, if_addr *)
{
    sockaddr_un *router =
#ifndef	P2P_RT_REMOTE
	BIT_TEST(ifap->ifa_state, IFS_POINTOPOINT) ?
	    ifap->ifa_addr_local :
#endif	/* P2P_RT_REMOTE */
		ifap->ifa_addr;

    if (ifap->ifa_rt->rt_preference != ifap->ifa_preference
	|| !sockaddrcmp(router, RT_ROUTER(ifap->ifa_rt))
	|| BIT_TEST(ifap->ifa_rt->rt_state, RTS_DELETE)) {
	/* We consider it down */

	trace_only_tp(if_task,
		      0,
		      ("if_rtupdate: UPDATE route for interface %s %A/%A",
		       ifap->ifa_name,
		       ifap->ifa_addr,
		       ifap->ifa_netmask));

	if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
	    /* Kernel thinks it's up */
	    if_rtup(ifap);
	} else {
	    /* Check what kernel thinks about it */
	    if_check();
	}
    } else {
	/* We consider it up, refresh it */
	
	rt_refresh(ifap->ifa_rt);
    }
}


/* Check for changes needed on interface routes */
void
if_rtifachange __PF1(ifap, if_addr *)
{
    register if_addr_entry *ifae = ifap->ifa_addrent_local;

    if (ifae) {
	switch (socktype(ifap->ifa_addr)) {
#ifdef	PROTO_INET
	case AF_INET:
	    if (ifae->ifae_n_p2p) {
		
		int_rtparms.rtp_state = RTS_RETAIN|RTS_GATEWAY|RTS_NOADVISE;

		if (ifae->ifae_n_p2p == ifae->ifae_n_if) {
		    /* Need a loopback route for a P2P interface */

		    int_rtparms.rtp_preference = RTPREF_DIRECT_AGGREGATE;
		} else {
		    /* Need a dummy route to prevent bogus routing */

		    int_rtparms.rtp_preference = RTPREF_DIRECT;
		    BIT_SET(int_rtparms.rtp_state, RTS_NOTINSTALL);
		}
		
		if (ifae->ifae_rt
		    && ifae->ifae_rt->rt_preference != int_rtparms.rtp_preference) {
		    /* Wrong type, delete it */

		    rt_delete(ifae->ifae_rt);
		    ifae->ifae_rt = (rt_entry *) 0;
		}

		if (!ifae->ifae_rt) {
		    int_rtparms.rtp_dest = ifap->ifa_addr_local;
		    int_rtparms.rtp_dest_mask = inet_mask_host;
		    int_rtparms.rtp_router = inet_addr_loopback;
		    ifae->ifae_rt = rt_add(&int_rtparms);
		}
	    }
	    break;
#endif	/* PROTO_INET */

	default:
	    break;
	}
    }
}


/* Called when an interface route is actually deleted */
void
if_rtfree __PF1(rtd, void_t)
{
    if_addr *ifap = (if_addr *) rtd;

    assert(rtd == ifap->ifa_rt->rt_data);

    ifap->ifa_rt = (rt_entry *) 0;
}


/*
 * %(Copyright)
 */
