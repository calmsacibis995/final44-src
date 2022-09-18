/*
 *  $Header: /users/jch/src/gated/src/RCS/if_rt.c,v 2.0 90/04/16 16:52:33 jch Exp Locker: jch $
 */

/*%Copyright%*/


/*
 *  Routines for handling routes to interfaces
 */

#define	INCLUDE_ROUTE

#include "include.h"

flag_t if_rtactive;		/* Set to true if any protocol is broadcasting */

 /*******************************************************************************/
 /*  if_rtdown updates the routing table when an interface has transitioned	*/
 /*  down.  It is also used at init when an interface is found to be down	*/
 /*  by having init_flag be TRUE.						*/
 /*										*/
 /*  At init time, routes to direct interfaces are assumed to be		*/
 /*  RTPROTO_KERNEL as read from the kernel's routing table.  When an		*/
 /*  interface transitions down routes are assumed to be RTPROTO_DIRECT.	*/
 /*										*/
 /*  If the interface is point-to-point, the hostroute to the other side	*/
 /*  of the link is deleted.  If not, the route to the attached interface	*/
 /*  is deleted.  If the interface is subnetted, the internal route to		*/
 /*  the whole net is deleted if this interface is the gateway.			*/
 /*******************************************************************************/
void
if_rtdown(ifp)
if_entry *ifp;
{
    rt_entry *rt;

    /* Route pointer */
    assert(ifp->int_rt);
    
    switch (BIT_TEST(ifp->int_state, IFS_LOOPBACK|IFS_POINTOPOINT)) {
    case IFS_LOOPBACK:
    case IFS_POINTOPOINT:
	/*  Delete or declare unreachable route to loopback host */
	if (rt = rt_locate(RTS_HOSTROUTE,
			   ifp->int_addr,
			   (sockaddr_un *) 0,
			   RTPROTO_BIT(RTPROTO_DIRECT))) {
	    if (rt == ifp->int_rt) {
		ifp->int_rt = (rt_entry *) 0;
	    }
	    if (!BIT_TEST(rt->rt_state, RTS_DELETE)) {
		rt_delete(rt);
	    }
	}
	if (!ifp->int_subnet) {
	    break;
	}
	/* Fall through */

    default:
	/* Delete or declare unreachable route to subnet and full net */
	if (rt = rt_locate(RTS_INTERIOR,
			   ifp->int_subnet,
			   ifp->int_subnetmask,
			   RTPROTO_BIT(RTPROTO_DIRECT))) {
	    if (rt->rt_ifp == ifp) {
		if (rt == ifp->int_rt) {
		    ifp->int_rt = (rt_entry *) 0;
		}
		if (!BIT_TEST(rt->rt_state, RTS_DELETE)) {
		    rt_delete(rt);
		}
	    }
	}

	if (BIT_TEST(ifp->int_state, IFS_SUBNET)) {
	    if (rt = rt_locate(RTS_INTERIOR,
			       ifp->int_net,
			       ifp->int_netmask,
			       RTPROTO_BIT(RTPROTO_DIRECT))) {
		if (rt->rt_ifp == ifp &&
		    !BIT_TEST(rt->rt_state, RTS_DELETE)) {
		    rt_delete(rt);
		}
	    }
	}
    } /* switch */

}


 /*******************************************************************************/
 /*	if_rtbest() is used to make sure the route to an interface is the one	*/
 /*	with the best metric.							*/
 /*******************************************************************************/
PROTOTYPE(if_rtbest,
	  inline static rt_entry *,
	  (if_entry *));
inline static rt_entry *
if_rtbest(best_ifp)
if_entry *best_ifp;
{
    rt_entry *best_rt;

    if (best_rt = rt_locate(int_rtparms.rtp_state,
			    int_rtparms.rtp_dest,
			    int_rtparms.rtp_dest_mask,
			    RTPROTO_BIT(RTPROTO_DIRECT))) {
	/* Route exists */
	if (best_ifp->int_metric < best_rt->rt_ifp->int_metric ||
	    BIT_TEST(best_rt->rt_state, RTS_DELETE)) {
	    if (best_ifp == best_rt->rt_ifp) {
		/*  This interface is the most attractive route, update existing route  */
		best_rt = rt_change(best_rt,
				    best_ifp->int_metric,
				    best_ifp->int_preference,
				    1, &best_ifp->int_addr);
	    } else {
		/* Different interface */
		rt_delete(best_rt);
		best_rt = (rt_entry *) 0;
	    }
	}
    }

    /*  No route to the net exists, add an interface route to our tables only  */
    if (!best_rt) {
	best_rt = rt_add(&int_rtparms);
    }

    return best_rt;
}


 /*******************************************************************************/
 /*  if_rtup processes an interface transition to up or an interface that	*/
 /*  is up at init time.							*/
 /*										*/
 /*  If the interface is point-to-point, any host route to that interface	*/
 /*  is deleted and a host route to the interface with a protocol of		*/
 /*  RTPROTO_DIRECT is added to the routing table.				*/
 /*										*/
 /*  For non-point-to-point interfaces, the route to the attached network	*/
 /*  is deleted from the routing table and a RTPROTO_DIRECT route is		*/
 /*  added. 									*/
 /*										*/
 /*  If non-point-to-point subnetted interfaces, the routing table is		*/
 /*  searched for a direct route to this interface				*/
 /*******************************************************************************/
void
if_rtup(up_ifp)
if_entry *up_ifp;
{
    rt_entry *up_rt;

    int_rtparms.rtp_router = up_ifp->int_addr;
    int_rtparms.rtp_state = RTS_NOAGE|RTS_RETAIN;
    int_rtparms.rtp_metric = up_ifp->int_metric;
    int_rtparms.rtp_preference = up_ifp->int_preference;

    switch (BIT_TEST(up_ifp->int_state, IFS_LOOPBACK|IFS_POINTOPOINT)) {
    case IFS_LOOPBACK:
	BIT_SET(int_rtparms.rtp_state, RTS_NOADVISE);
	/* Fall through */

    case IFS_POINTOPOINT:
	/* Delete existing route to this interface */
	if (up_ifp->int_rt) {
	    rt_delete(up_ifp->int_rt);
	}

	/*
	 * Add a route to the interface.
	 * 4.2 based systems need the router to be the destination.
	 * 4.3 based systems like it to be the local address
	 */
	int_rtparms.rtp_dest = up_ifp->int_addr;
	int_rtparms.rtp_dest_mask = (sockaddr_un *) 0;
#ifdef	P2P_RT_LOCAL
	if (BIT_TEST(up_ifp->int_state, IFS_POINTOPOINT)) {
	    int_rtparms.rtp_router = up_ifp->int_lcladdr;
	}
#endif	/* P2P_RT_LOCAL */
	BIT_SET(int_rtparms.rtp_state, RTS_HOSTROUTE);

	up_ifp->int_rt = rt_add(&int_rtparms);
	if (!up_ifp->int_subnet ||
#ifdef	RTF_REJECT
	    !sockaddrcmp(up_ifp->int_addr, inet_addr_loopback)
#else	/* RTF_REJECT */
	    BIT_TEST(up_ifp->int_state, IFS_LOOPBACK)
#endif	/* RTF_REJECT */
	    ) {
	    break;
	}
	BIT_RESET(int_rtparms.rtp_state, RTS_HOSTROUTE);
	/* Fall through */

    default:
	/*  Delete any routes to this subnet and add an interface route to  */
	/*  it if we are the most attractive.                               */

	BIT_SET(int_rtparms.rtp_state, RTS_INTERIOR);

	int_rtparms.rtp_dest = up_ifp->int_subnet;
	int_rtparms.rtp_dest_mask = up_ifp->int_subnetmask;
	if (BIT_TEST(up_ifp->int_state, IFS_SUBNET)) {
	    BIT_SET(int_rtparms.rtp_state, RTS_SUBNET);
	}
#ifdef	RTF_REJECT
	if (BIT_TEST(up_ifp->int_state, IFS_LOOPBACK)) {
	    BIT_SET(int_rtparms.rtp_state, RTS_REJECT);
	}
#endif	/* RTF_REJECT */
	up_rt = if_rtbest(up_ifp);
	if (!BIT_TEST(up_ifp->int_state, IFS_LOOPBACK|IFS_POINTOPOINT)) {
	    /* Save pointer to this route */
	    up_ifp->int_rt = up_rt;
	}
	BIT_RESET(int_rtparms.rtp_state, RTS_SUBNET);
#ifdef	RTF_REJECT
	BIT_RESET(int_rtparms.rtp_state, RTS_REJECT);
#endif	/* RTF_REJECT */

	if (BIT_TEST(up_ifp->int_state, IFS_SUBNET)) {
	    /*  Interface is to a subnet.  Must update route to the main net  */
	    /*  if this is the most attractive interface to it.               */

	    int_rtparms.rtp_dest = up_ifp->int_net;
	    int_rtparms.rtp_dest_mask = up_ifp->int_netmask;
	    BIT_SET(int_rtparms.rtp_state, RTS_NOTINSTALL);
	    BIT_RESET(int_rtparms.rtp_state, RTS_RETAIN);
	    (void) if_rtbest(up_ifp);
	}
    } /* switch */
}


 /*******************************************************************************/
 /*  if_rtupdate() is used when a routing packet is received from an		*/
 /*  interface to make sure that a route to this interface exists.		*/
 /*										*/
 /*  If the route to this interface exists, it's metric is set to the		*/
 /*  interface metric of this interface and it's timer is reset.  If this	*/
 /*  is a subnet route, the internal route to the main net is also updated.	*/
 /*										*/
 /*  If the route to this interface does not exist, if_rtup is called to	*/
 /*  add it to the routing table.						*/
 /*******************************************************************************/

PROTOTYPE(if_rtupdate_sub,
	  static inline void,
	  (if_entry *,
	   rt_entry *,
	   int *));
static inline void
if_rtupdate_sub(sub_ifp, sub_rt, sub_open)
if_entry *sub_ifp;
rt_entry *sub_rt;
int *sub_open;
{
    if (BIT_TEST(sub_ifp->int_state, IFS_UP)) {
	if (!(*sub_open)++) {
	    rt_open(if_task);
	}

	if (sub_rt) {
	    /* Route exists */
		
	    if (sub_rt->rt_metric != sub_ifp->int_metric ||
		BIT_TEST(sub_rt->rt_state, RTS_DELETE)) {
		/* Metric is wrong */
		
		sub_rt = rt_change(sub_rt,
				   sub_ifp->int_metric,
				   sub_ifp->int_preference,
				   1, &sub_ifp->int_addr);
	    } else {
		/* Reset timer */
		    
		rt_refresh(sub_rt);
	    }
	} else {
	    /* Interface is up so we assume that route is just missing */
	    
	    if_rtup(sub_ifp);
	}
    } else {
	/* Interface is marked down, see if kernel thinks it's up */

	if_check(if_task);
    }
}


void
if_rtupdate(ifp)
if_entry *ifp;
{
    int opened = 0;
    rt_entry *rt = ifp->int_rt;

    switch (BIT_TEST(ifp->int_state, IFS_LOOPBACK|IFS_POINTOPOINT)) {
    case IFS_LOOPBACK:
    case IFS_POINTOPOINT:
	if_rtupdate_sub(ifp, rt, &opened);
	if (!ifp->int_subnet) {
	    break;
	}

	/* Look up subnet route */
	rt = rt_locate(RTS_NETROUTE,
		       ifp->int_subnet,
		       ifp->int_subnetmask,
		       RTPROTO_BIT(RTPROTO_DIRECT));
	/* Fall through */

    default:
	if_rtupdate_sub(ifp, rt, &opened);

	if (BIT_TEST(ifp->int_state, IFS_SUBNET)) {
	    /*  Interface is to a subnet.  Must update route to the main net  */
	    /*  if this is the most attractive interface to it.               */

	    if (!opened++) {
		rt_open(if_task);
	    }
	    if ((rt = rt_locate(RTS_NETROUTE,
				ifp->int_net,
				ifp->int_netmask,
				RTPROTO_BIT(RTPROTO_DIRECT))) &&
		(rt->rt_ifp == ifp)) {
		if (rt->rt_metric != ifp->int_metric ||
		    BIT_TEST(rt->rt_state, RTS_DELETE)) {
		    rt = rt_change(rt,
				   ifp->int_metric,
				   ifp->int_preference,
				   1, &ifp->int_addr);
		} else {
		    rt_refresh(rt);
		}
	    } else {
		if_rtup(ifp);
	    }
	}
    } /* switch */

    if (opened) {
	rt_close(if_task, (gw_entry *) 0, 0, NULL);
    }
}
