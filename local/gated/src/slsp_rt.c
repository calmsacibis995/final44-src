/*
 * $Id: slsp_rt.c,v 1.6.2.2 1994/09/08 16:36:42 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"
#include "inet.h"
#include "slsp_proto.h"
#include "slsp.h"
#include "slsp_var.h"

/*
 * Routines to compute routes and manage entries in the gated routing table
 * for SLSP.  The scheduling of the SPF computation, as well as the SPF
 * itself, is done in here.  The end result is a set of routes in the
 * gated routing table.
 */

/*
 * slsp_do_spf - run the SPF on the current link state database
 */
static void
slsp_do_spf __PF1(inp, slsp_instance *)
{
    register slsp_db_node *np;
    register slsp_db_link *lp;
    register u_int32 cost, newcost;
    slsp_rtlist candidate, unconnected;
    rt_parms rtparms;
    int n_gw;
    sockaddr_un **gws;
    sockaddr_un addr;
    int rtp_initialized = 0;
    int disconnected = 0;
    int additions = 0;
    int deletions = 0;
    int changes = 0;

    /*
     * To start, move all routes onto the unconnected list.  We start
     * by walking the connected list to reset the next hops and indicate
     * that the routes are now on the unconnected list.  We then move
     * the whole block over to the head of the unconnected list.  Before
     * doing this remove the local node from any list it might be on.
     */
    np = inp->slsp_local_node;
    if (np->slsp_node_onlist) {
	SLSP_RT_REMOVE(np);
    }
    if (!SLSP_RT_EMPTY(&(inp->slsp_connected))) {
	assert(inp->slsp_n_connected);
	unconnected = inp->slsp_connected;
	unconnected.slsp_rtprev->slsp_rtnext
	  = unconnected.slsp_rtnext->slsp_rtprev = &unconnected;
	SLSP_RT_INIT(&(inp->slsp_connected));
    } else {
	SLSP_RT_INIT(&unconnected);
    }

    /*
     * Log what we're doing
     */
    trace_tf(inp->slsp_trace_options,
	     TR_SLSP_SPF|TR_NORMAL,
	     0,
	     ("slsp_do_spf: running SPF, %d node%s previously connected",
	      inp->slsp_n_connected,
	      ((inp->slsp_n_connected == 1) ? "" : "s")));

    /*
     * Okay, initialize the candidate list with the local node.
     * This'll start us off.
     */
    sockclear_in(&addr);
    candidate.slsp_rtnext = candidate.slsp_rtprev = (slsp_rtlist *) np;
    np->slsp_node_list.slsp_rt_prev = np->slsp_node_list.slsp_rt_next
      = &candidate;
    np->slsp_node_onlist = SLSP_NRT_CANDIDATE;

    /*
     * Loop processing nodes off the candidate list.
     */
    do {
	/*
	 * Fetch the cost from this node
	 */
	cost = np->slsp_node_cost;

	/*
	 * np points at the top of the candidate list.  Scan his links
	 * looking for guys to add to the candidate list.
	 */
	for (lp = np->slsp_node_linklist.slspdb_link_next;
	     lp && lp != &(np->slsp_node_linklist);
	     lp = lp->slspdb_link_next) {
	    register slsp_db_node *nplink = lp->slspdb_link_node;
	    register slsp_db_node *npsort;
	    register slsp_db_link *lplink;

	    /*
	     * Check to see if the node is sensible.  Continue at the
	     * first sign of trouble.
	     */
	    if (!SLSP_IS_ACTIVE_LSP(nplink)) {
		continue;
	    }

	    if (nplink == np) {
		trace_tf(inp->slsp_trace_options,
			 TR_ALL,
			 LOG_WARNING,
			 ("slsp_do_spf: node %#A has cost %u link to itself!",
			  np->slsp_node_addr,
			  lp->slspdb_link_cost));
		continue;
	    }

	    /*
	     * Compute the cost to this node.  If the node is on the
	     * candidate/connected list and the cost is higher than
	     * the node's cost, forget it.
	     */
	    newcost = cost + lp->slspdb_link_cost;
	    if (nplink->slsp_node_onlist
	      && nplink->slsp_node_onlist != SLSP_NRT_UNCONNECTED
	      && nplink->slsp_node_cost < newcost) {
		continue;
	    }
	    assert(nplink->slsp_node_onlist != SLSP_NRT_CONNECTED);

	    /*
	     * So far so good.  Determine if there is a back link.
	     */
	    for (lplink = nplink->slsp_node_linklist.slspdb_link_next;
		 lplink && lplink != &(nplink->slsp_node_linklist);
		 lplink = lplink->slspdb_link_next) {
		if (lplink->slspdb_link_node == np) {
		    break;
		}
	    }

	    if (!lplink || lplink == &(nplink->slsp_node_linklist)) {
		trace_tf(inp->slsp_trace_options,
			 TR_SLSP_SPF|TR_NORMAL,
			 0,
			 ("slsp_do_spf: node %#A has no back link to node %#A",
			  nplink->slsp_node_addr,
			  np->slsp_node_addr));
		continue;
	    }

	    /*
	     * This guy is a keeper.  Compute what to do with him.  If
	     * he's on the connected list we will get to add our next hop(s)
	     * to his.  If he's on the candidate list we will add our next
	     * hop(s) to his if the cost is equal, or replace his route if
	     * our cost is better.  Otherwise he gets moved to the candidate
	     * list unconditionally.
	     */
	    switch (nplink->slsp_node_onlist) {
	    case SLSP_NRT_CANDIDATE:
		if (newcost < nplink->slsp_node_cost) {
		    npsort = (slsp_db_node *)
		      (nplink->slsp_node_list.slsp_rt_prev);
		    nplink->slsp_node_n_nexthops = 0;
		    SLSP_RT_REMOVE(nplink);
		    break;
		}
		npsort = (slsp_db_node *) 0;
		break;

	    case SLSP_NRT_UNCONNECTED:
		SLSP_RT_REMOVE(nplink);
		/*FALLSTHROUGH*/

	    default:
		npsort = (slsp_db_node *)(candidate.slsp_rtprev);
		nplink->slsp_node_n_nexthops = 0;
		break;
	    }

	    /*
	     * Figure out what next hop(s) this guy should have.  We
	     * copy the next hops from np, unless np doesn't have any
	     * in which case this had better be a direct neighbour.
	     *
	     * There is a funny case here when we find that there
	     * is a gateway'd equal cost route to a directly connected
	     * broadcast interface.  We prefer the direct route in
	     * this case since there is no way to install a multipath
	     * route like that.
	     *
	     * XXX This is broken since routes beyond the direct subnet
	     * could use the multipath routes but won't know them.
	     */
	    n_gw = np->slsp_node_n_nexthops;
	    if (n_gw) {
		if (!npsort && nplink->slsp_node_n_nexthops == 0) {
		    n_gw = 0;
		    gws = (sockaddr_un **) 0;
		} else {
		    gws = np->slsp_node_nexthops;
		}
	    } else {
		if (nplink->slsp_node_type == SLSP_LSP_NBRNET
		  || nplink->slsp_node_type == SLSP_LSP_LOCALNET) {
		    if (nplink->slsp_node_n_nexthops) {
			nplink->slsp_node_n_nexthops = 0;
		    }
		    gws = (sockaddr_un **) 0;
		} else if (lp->slspdb_link_nbr) {
		    n_gw = 1;
		    gws = &(lp->slspdb_link_nbr->slsp_nbr_addr);
		} else {
		    assert(np->slsp_node_type == SLSP_LSP_NBRNET);
		    /* send through designated router */
		    n_gw = 1;
		    gws = &(np->slsp_node_nbr->slsp_nbr_id);
		}
	    }

	    if (n_gw) {
		register int i;

		if (nplink->slsp_node_n_nexthops == 0) {
		    /*
		     * Easy.  Copy the next hops over
		     */
		    nplink->slsp_node_n_nexthops = n_gw;
		    for (i = 0; i < n_gw; i++) {
			nplink->slsp_node_nexthops[i] = *gws++;
		    }
		} else {
		    /*
		     * Not so easy.  Merge the new next hops with
		     * those already on the route.  We prefer the
		     * numerically lowest next hops.  We also
		     * keep them sorted to make comparisons with
		     * the routing table easy.
		     */
		    i = 0;
		    do {
			if (i == nplink->slsp_node_n_nexthops) {
			    nplink->slsp_node_nexthops[i++] = *gws++;
			    nplink->slsp_node_n_nexthops++;
			    n_gw--;
			} else if (ntohl(sock2ip(*gws))
			  < ntohl(sock2ip(nplink->slsp_node_nexthops[i]))) {
			    register int k = nplink->slsp_node_n_nexthops;

			    if (k == RT_N_MULTIPATH) {
				k--;
			    } else {
				nplink->slsp_node_n_nexthops++;
			    }
			    while (k > i) {
				nplink->slsp_node_nexthops[k]
				  = nplink->slsp_node_nexthops[k-1];
				k--;
			    }
			    nplink->slsp_node_nexthops[i++] = *gws++;
			    n_gw--;
			} else if (sock2ip(nplink->slsp_node_nexthops[i])
			      == sock2ip(*gws)) {
			    n_gw--;
			    gws++;
			    i++;
			} else {
			    i++;
			}
		    } while (i < RT_N_MULTIPATH && n_gw);
		}
	    }

	    /*
	     * If we need to sort him on the candidate list, do it now.
	     */
	    if (npsort) {
		nplink->slsp_node_onlist = SLSP_NRT_CANDIDATE;
		nplink->slsp_node_cost = newcost;
		if (SLSP_IS_NET_LSP(nplink)) {
		    /*
		     * Broadcast subnet LSP's must be added to the
		     * candidate list at the head of their priority
		     * to make sure we detect equal cost paths while
		     * the nodes are still on the candidate list.
		     */
		    npsort = np;
		    while ((npsort = SLSP_RT_NEXT(&candidate, npsort))) {
			if (npsort->slsp_node_cost >= newcost) {
			    break;
			}
		    }
		    if (npsort) {
			SLSP_RT_PREPEND(npsort, nplink);
		    } else {
			SLSP_RT_PREPEND(&candidate, nplink);
		    }
		} else {
		    /*
		     * Work up the list from npsort.  Stop when
		     * we find a node whose cost is less than
		     * or equal to this guy's
		     */
		    while (newcost < npsort->slsp_node_cost) {
			npsort = (slsp_db_node *)
			  (npsort->slsp_node_list.slsp_rt_prev);
		    }
		    SLSP_RT_APPEND(npsort, nplink);
		}
	    }
	}	/* for (each link on this node) */

	/*
	 * Got all this guy's links on the candidate list.  Put him
	 * on the connected list.
	 */
	SLSP_RT_REMOVE(np);
	SLSP_RT_PREPEND(&(inp->slsp_connected), np);
	np->slsp_node_onlist = SLSP_NRT_CONNECTED;
	if (TRACE_TF(inp->slsp_trace_options, TR_SLSP_SPF)) {
	    register int i;

	    sock2ip(&addr)
	      = sock2ip(np->slsp_node_addr) & sock2ip(np->slsp_node_rtmask);
	    tracef("slsp_do_spf: %s node %#A route %A/%A nexthop%s",
		   trace_state(slsp_node_types, np->slsp_node_type),
		   np->slsp_node_addr,
		   &addr,
		   np->slsp_node_rtmask,
		   ((np->slsp_node_n_nexthops == 1) ? "" : "s"));
	    for (i = 0; i < np->slsp_node_n_nexthops; i++) {
		tracef(" %#A", np->slsp_node_nexthops[i]);
	    }
	    trace_only_tf(inp->slsp_trace_options,
			  0,
			  (" cost %u %sconnected",
			   np->slsp_node_cost,
			   (np->slsp_node_rt ? "re" : "")));
	}
    } while ((np = SLSP_RT_NEXT(&candidate, &candidate)));

    /*
     * At this point we've discovered routes to all the guys we're going
     * to find.  The candidate list is empty.  We will have connected
     * guys on the connected list and will need to install/adjust gated
     * routes to match their current state.  We will also have previously
     * connected but now unreachable guys on the unconnected list, we
     * will need to delete their routes.
     *
     * There are a couple of imperfections here involving network nodes.
     * If the designated router for a network node changes we will
     * delete/add the route to the subnet even if there was no change
     * to the route.  If we have two routes to a network node (i.e. the
     * subnet has partitioned) we will install them both, even if the
     * computed costs are different.  For the latter we depend on gated
     * to pick the right route.
     *
     * Scan the connected list first.
     */
    inp->slsp_n_connected = 0;
    rt_open(inp->slsp_task);
    for (np = SLSP_RT_NEXT(&(inp->slsp_connected), &(inp->slsp_connected));
	 np;
	 np = SLSP_RT_NEXT(&(inp->slsp_connected), np)) {
	np->slsp_node_onlist = SLSP_NRT_UNCONNECTED;
	inp->slsp_n_connected++;
	sock2ip(&addr) = sock2ip(np->slsp_node_addr)
	  & sock2ip(np->slsp_node_rtmask);
	if (!(np->slsp_node_rt)) {
	    if (np->slsp_node_n_nexthops) {
		register int i;

		/*
		 * Need to add it.  Set up the rtparms.
		 */
		if (!rtp_initialized) {
		    rtparms.rtp_dest = &addr;
		    rtparms.rtp_gwp = &(inp->slsp_gw);
		    rtparms.rtp_metric2 = SLSP_METRIC_NONE;
		    rtparms.rtp_tag = 0;
		    rtparms.rtp_state = RTS_INTERIOR|RTS_GATEWAY;
		    rtparms.rtp_preference = inp->slsp_preference;
		    rtparms.rtp_asp = (as_path *) 0;
		    rtp_initialized = 1;
		}
		rtparms.rtp_dest_mask = np->slsp_node_rtmask;
		rtparms.rtp_n_gw = i = np->slsp_node_n_nexthops;
		rtparms.rtp_metric = np->slsp_node_cost;
		while (i-- > 0) {
		    rtparms.rtp_routers[i] = np->slsp_node_nexthops[i];
		}
		rtparms.rtp_rtd = (void_t) np;
		np->slsp_node_rt = rt_add(&rtparms);
		trace_tf(inp->slsp_trace_options,
			 TR_SLSP_SPF,
			 0,
			 ("slsp_do_spf: added route to %A/%A",
			  &addr,
			  np->slsp_node_rtmask));
		additions++;
	    }
	} else if (!(np->slsp_node_n_nexthops)) {
	    (void) rt_delete(np->slsp_node_rt);
	    np->slsp_node_rt = (rt_entry *) 0;
	    trace_tf(inp->slsp_trace_options,
		     TR_SLSP_SPF,
		     0,
		     ("slsp_do_spf: deleted route to %A/%A in favour of direct",
		      &addr,
		      np->slsp_node_rtmask));
	    deletions++;
	} else {
	    register rt_entry *rt;
	    register int i;

	    rt = np->slsp_node_rt;
	    if (rt->rt_n_gw != np->slsp_node_n_nexthops) {
		n_gw = np->slsp_node_n_nexthops;
		gws = np->slsp_node_nexthops;
	    } else {
		n_gw = rt->rt_n_gw;
		for (i = 0; i < n_gw; i++) {
		    if (sock2ip(rt->rt_routers[i])
		      != sock2ip(np->slsp_node_nexthops[i])) {
			break;
		    }
		}
		if (i < n_gw) {
		    gws = np->slsp_node_nexthops;
		} else {
		    gws = rt->rt_routers;
		}
	    }

	    if (np->slsp_node_cost != rt->rt_metric
	      || gws != rt->rt_routers) {
		(void) rt_change(rt,
				 (metric_t)np->slsp_node_cost,
				 rt->rt_metric2,
				 rt->rt_tag,
				 rt->rt_preference,
				 rt->rt_preference2,
				 n_gw,
				 gws);
		rt_refresh(rt);
		trace_tf(inp->slsp_trace_options,
			 TR_SLSP_SPF,
			 0,
			 ("slsp_do_spf: changed route %s for %A/%A",
			  ((np->slsp_node_cost != rt->rt_metric) ?
			   ((gws != rt->rt_routers) ? "metric/next hops"
			    : "metric") : "next hops"),
			&addr,
			np->slsp_node_rtmask));
		changes++;
	    }
	}
    }

    /*
     * Now run through the unconnected list, deleting anyone who is
     * currently in the routing table.
     */
    for (np = SLSP_RT_NEXT(&unconnected, &unconnected);
	 np;
	 np = SLSP_RT_NEXT(&unconnected, np)) {
	np->slsp_node_onlist = SLSP_NRT_NONE;
	disconnected++;
	if (np->slsp_node_rt) {
	    rt_delete(np->slsp_node_rt);
	    np->slsp_node_rt = (rt_entry *) 0;
	    deletions++;
	    trace_tf(inp->slsp_trace_options,
		     TR_SLSP_SPF,
		     0,
		     ("slsp_do_spf: deleted route %A/%A, no longer connected",
		      np->slsp_node_addr,
		      np->slsp_node_rtmask));
	}
    }
    rt_close(inp->slsp_task,
	     &(inp->slsp_gw),
	     (additions+changes+deletions),
	     NULL);

    /*
     * Done, log the results
     */
    trace_tf(inp->slsp_trace_options,
	     TR_SLSP_SPF|TR_NORMAL,
	     0,
	     ("slsp_do_spf: nodes connected %d disconnected %d routes added %d modified %d deleted %d",
	      inp->slsp_n_connected,
	      disconnected,
	      additions,
	      changes,
	      deletions));
}


/*
 * slsp_run_spf - the task job from which the SPF is run
 */
static void
slsp_run_spf __PF1(jp, task_job *)
{
    slsp_instance *inp = (slsp_instance *)(jp->task_job_data);

    if (TRACE_TF(inp->slsp_trace_options, TR_SLSP_SPF)) {
	if (inp->slsp_spf_lastdone) {
	    trace_only_tf(inp->slsp_trace_options,
			  0,
			  ("slsp_run_spf: running SPF, deferred %d second%s, last done %#T",
			  (time_sec - inp->slsp_spf_scheduled),
			  (((time_sec - inp->slsp_spf_scheduled) == 1) ? "" : "s"),
			  (time_sec - inp->slsp_spf_lastdone)));
	} else {
	    trace_only_tf(inp->slsp_trace_options,
			  0,
			  ("slsp_run_spf: running first SPF, deferred %d second%s",
			   (time_sec - inp->slsp_spf_scheduled),
			   (((time_sec - inp->slsp_spf_scheduled) == 1) ? "" : "s")));
	}
    }
    slsp_do_spf(inp);
    inp->slsp_spf_lastdone = time_sec;
    inp->slsp_spf_scheduled = inp->slsp_spf_requested = (time_t) 0;
    BIT_RESET(inp->slsp_flags, SLSPF_SPF);
    task_job_delete(jp);
}


/*
 * slsp_spf_timeout - the SPF timer expired, either schedule a background
 *		      job to do the work, or wait a bit longer if we are
 *		      still receiving updates.
 */
static void
slsp_spf_timeout __PF2(tip, task_timer *,
		       interval, time_t)
{
    slsp_instance *inp = (slsp_instance *)(tip->task_timer_data);

    if (!(inp->slsp_spf_requested)
      || (time_sec - inp->slsp_spf_scheduled) >= SLSP_SPF_MAX_DEFER
      || (time_sec - inp->slsp_spf_requested) >= SLSP_SPF_LONG_WAIT) {
	/*
	 * Time to schedule the SPF.  Set up the task job to run it and
	 * set the flags so we know we've done this.
	 */
	trace_tf(inp->slsp_trace_options,
		 TR_SLSP_SPF,
		 0,
		 ("slsp_spf_timeout: scheduling SPF run %d second%s after first request",
		  (time_sec - inp->slsp_spf_scheduled),
		  (((time_sec - inp->slsp_spf_scheduled) == 1) ? "" : "s")));
	BIT_RESET(inp->slsp_flags, SLSPF_SPF_TIMER);
	BIT_SET(inp->slsp_flags, SLSPF_SPF_JOB);
	(void) task_job_create(inp->slsp_task,
			       TASK_JOB_PRIO_SPF,
			       "SLSP SPF Run",
			       slsp_run_spf,
			       (void_t) inp);
    } else {
	/*
	 * Reset the request time so we'll know if we get more requests.
	 * Then re-set the timer for another short wait.
	 */
	trace_tf(inp->slsp_trace_options,
		 TR_SLSP_SPF,
		 0,
		 ("slsp_spf_timeout: deferring SPF for another second, delayed %d second%s so far",
		  (time_sec - inp->slsp_spf_scheduled),
		  (((time_sec - inp->slsp_spf_scheduled) == 1) ? "" : "s")));
	inp->slsp_spf_requested = (time_t) 0;
	task_timer_set(tip,
		       (time_t) 0,
		       (time_t) SLSP_SPF_WAIT);
    }
}


/*
 * slsp_spf_schedule - schedule an SPF run some time in the future
 */
void
slsp_spf_schedule __PF1(inp, slsp_instance *)
{
    if (BIT_TEST(inp->slsp_flags, SLSPF_SPF)) {
	/*
	 * Already scheduled, just update the request time so
	 * the timer will know we're still busy.
	 */
	inp->slsp_spf_requested = time_sec;
    } else {
	/*
	 * (Re)start the timer, to expire in a second.
	 */
	trace_tf(inp->slsp_trace_options,
		 TR_SLSP_SPF,
		 0,
		 ("slsp_spf_schedule: deferring SPF for a second"));
	inp->slsp_spf_scheduled = time_sec;
	inp->slsp_spf_requested = (time_t) 0;
	BIT_SET(inp->slsp_flags, SLSPF_SPF_TIMER);
	if (!(inp->slsp_timer_spf)) {
	    inp->slsp_timer_spf = task_timer_create(inp->slsp_task,
						    "SPF",
						    (flag_t) 0,
						    (time_t) 0,
						    (time_t) SLSP_SPF_WAIT,
						    slsp_spf_timeout,
						    (void_t) inp);
	} else {
	    task_timer_set(inp->slsp_timer_spf,
			   (time_t) 0,
			   (time_t) SLSP_SPF_WAIT);
	}
    }
}


/*
 * slsp_rt_reinit - recheck policy after a reconfig.  Currently just a
 *		    placeholder until SLSP does import policy.
 */
void
slsp_rt_reinit __PF1(tp, task *)
{
    /* nothing */
}


/*
 * slsp_rt_dump - dump routing state into the dump file
 */
void
slsp_rt_dump __PF2(fd, FILE *,
		   inp, slsp_instance *)
{
    /* later */
}


/*
 * slsp_rt_terminate - blow away all the routes this instance has installed
 */
void
slsp_rt_terminate __PF1(inp, slsp_instance *)
{
    register rtq_entry *rtq = &(inp->slsp_gw.gw_rtq);
    register rt_entry *rt;
    int changes = 0;

    if (inp->slsp_gw.gw_n_routes) {
	rt_open(inp->slsp_task);

	RTQ_LIST(rtq, rt) {
	    rt_delete(rt);
	    changes++;
	} RTQ_LIST_END(rtq, rt);

	rt_close(inp->slsp_task, &(inp->slsp_gw), changes, NULL);
    }
}

/*
 * %(Copyright)
 */
