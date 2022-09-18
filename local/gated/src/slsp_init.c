/*
 * $Id: slsp_init.c,v 1.7 1994/02/23 01:51:28 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"
#include "inet.h"
#include "slsp_proto.h"
#include "slsp.h"
#include "slsp_var.h"

/*
 * Various routines to deal with gated reconfiguration, instance creation
 * and deletion, and other miscellany.
 */

/*
 * Our current instance list
 */
slsp_instance *slsp_instance_list = (slsp_instance *) 0;

/*
 * Global trace options
 */
trace *slsp_global_trace_options;

/*
 * For the parser
 */
int doing_slsp;

/*
 * We allocate instances and gateway structures in here.  These
 * are the blocks and some macros to get/set them.
 */
static block_t slsp_instance_block = (block_t) 0;
static block_t slsp_gateway_block = (block_t) 0;

#define	SLSP_INSTANCE_ALLOC() \
    ((slsp_instance *) task_block_alloc(slsp_instance_block))

#define	SLSP_GATEWAY_ALLOC() \
    ((slsp_gateway *) task_block_alloc(slsp_gateway_block))

#define	SLSP_INSTANCE_FREE(inp) \
    task_block_free(slsp_instance_block, (void_t)(inp))

#define	SLSP_GATEWAY_FREE(sgw) \
    task_block_free(slsp_gateway_block, (void_t)(sgw))

#define	SLSP_INSTANCE_INIT() \
    (slsp_instance_block = task_block_init(sizeof(slsp_instance), "slsp_instance"))

#define	SLSP_GATEWAY_INIT() \
    (slsp_gateway_block = task_block_init(sizeof(slsp_gateway), "slsp_gateway"))

#define	SLSP_INSTANCE_GET(inp) \
    do { \
	if (!slsp_instance_block) { \
	    SLSP_INSTANCE_INIT(); \
	} \
	(inp) = SLSP_INSTANCE_ALLOC(); \
    } while (0)

#define	SLSP_GATEWAY_GET(sgw) \
    do { \
	if (!slsp_gateway_block) { \
	    SLSP_GATEWAY_INIT(); \
	} \
	(sgw) = SLSP_GATEWAY_ALLOC(); \
    } while (0)

/*
 * Neighbour types
 */
const bits slsp_nbr_types[] = {
    { SLSP_NTYPE_PLACEHOLDER,	"PlaceHolder" },
    { SLSP_NTYPE_PTP,		"PointToPoint" },
    { SLSP_NTYPE_PTP_PEER,	"PointToPointPeer" },
    { SLSP_NTYPE_BCAST,		"BroadcastIntf" },
    { SLSP_NTYPE_BCAST_NBR,	"BroadcastNbr" },
    { 0,			NULL }
};

/*
 * Link state node types
 */
const bits slsp_node_types[] = {
    { SLSP_LSP_PLACEHOLDER,	"PlaceHolder" },
    { SLSP_LSP_TIMEDOUT,	"TimedOut" },
    { SLSP_LSP_ROUTER,		"Router" },
    { SLSP_LSP_LOCALRTR,	"LocalRouter" },
    { SLSP_LSP_NET,		"Net" },
    { SLSP_LSP_NBRNET,		"AttachedNet" },
    { SLSP_LSP_LOCALNET,	"LocalNet" },
    { 0,			NULL }
};

/*
 * Route lists
 */
const bits slsp_route_lists[] = {
    { SLSP_NRT_NONE,		"NotOnList" },
    { SLSP_NRT_UNCONNECTED,	"Unconnected" },
    { SLSP_NRT_CANDIDATE,	"Candidate" },
    { SLSP_NRT_CONNECTED,	"Connected" },
    { 0,			NULL }
};

/*
 * Neighbour states
 */
const bits slsp_nbr_states[] = {
    { SLSP_NBR_STATE_DOWN,	"Down" },
    { SLSP_NBR_STATE_HELLO,	"Hello" },
    { SLSP_NBR_STATE_IHU,	"IHU" },
    { SLSP_NBR_STATE_ADJACENT,	"Adjacent" },
    { 0,			NULL }
};

/*
 * Instance flags
 */
const bits slsp_instance_flags[] = {
    { SLSPF_SPF_JOB,		"SpfPending" },
    { SLSPF_SPF_TIMER,		"SpfTimerSet" },
    { SLSPF_DELETED,		"Deleted" },
    { 0,			NULL }
};


/*
 * Trace types
 */
const bits slsp_trace_types[] = {
    { TR_DETAIL,	"detail packets" },
    { TR_DETAIL_SEND,	"detail send packets" },
    { TR_DETAIL_RECV,	"detail recv packets" },
    { TR_PACKET,	"packets" },
    { TR_PACKET_SEND,	"send packets" },
    { TR_PACKET_RECV,	"recv packets" },
    { TR_DETAIL_1,	"detail hello" },
    { TR_DETAIL_SEND_1,	"detail send hello" },
    { TR_DETAIL_RECV_1,	"detail recv hello" },
    { TR_PACKET_1,	"hello" },
    { TR_PACKET_SEND_1,	"send hello" },
    { TR_PACKET_RECV_1,	"recv hello" },
    { TR_DETAIL_2,	"detail lsp" },
    { TR_DETAIL_SEND_2,	"detail send lsp" },
    { TR_DETAIL_RECV_2,	"detail recv lsp" },
    { TR_PACKET_2,	"lsp" },
    { TR_PACKET_SEND_2,	"send lsp" },
    { TR_PACKET_RECV_2,	"recv lsp" },
    { 0, NULL }
};


/*
 * slsp_parse_instance_alloc - allocate an instance for the configuration
 */
slsp_instance *
slsp_parse_instance_alloc __PF3(addr, sockaddr_un *,
				mask, sockaddr_un *,
				nodemask, sockaddr_un *)
{
    slsp_instance *inp;

    /*
     * Fetch an instance, set the defaults and return it
     */
    SLSP_INSTANCE_GET(inp);

    inp->slsp_addr = sockdup(addr);
    inp->slsp_mask = nodemask;
    inp->slsp_rtmask = mask;
    inp->slsp_def_hellointerval = SLSP_DEFAULT_HELLOINTERVAL;
    inp->slsp_def_routerdeadinterval = SLSP_DEFAULT_ROUTERDEADINTERVAL;
    inp->slsp_def_cost = SLSP_DEFAULT_COST;
    inp->slsp_def_priority = SLSP_DEFAULT_PRIORITY;
    inp->slsp_preference = SLSP_DEFAULT_PREFERENCE;
    inp->slsp_gw.gw_proto = RTPROTO_SLSP;
    /* XXX grot XXX */
    inp->slsp_gw.gw_local_as = inet_autonomous_system;
    inp->slsp_gw.gw_rtq.rtq_forw = inp->slsp_gw.gw_rtq.rtq_back
      = &(inp->slsp_gw.gw_rtq);
    SLSP_RT_INIT(inp);
    SLSP_XMT_INIT(inp);
    SLSP_LIFE_INIT(inp);
    SLSP_FULL_INIT(inp);
    SLSP_FSQ_INIT(&(inp->slsp_full_queue));

    return inp;
}


/*
 * slsp_parse_instance_check - check that this instance is sensible
 */
int
slsp_parse_instance_check __PF2(inpp, slsp_instance **,
				errbuf, char *)
{
    slsp_instance *inp_prev, *inp_chk;
    slsp_instance *inp = *inpp;
    u_int mlen, rtmlen;
    u_long in_id;

    mlen = inet_prefix_mask(inp->slsp_mask);
    if (mlen == (u_int) -1) {
	(void) sprintf(errbuf,
		       "SLSP instance mask %#A must be contiguous",
		       inp->slsp_mask);
	return TRUE;
    }

    rtmlen = inet_prefix_mask(inp->slsp_rtmask);
    if (rtmlen == (u_int) -1) {
	(void) sprintf(errbuf,
		       "SLSP route mask %#A must be contiguous",
		       inp->slsp_rtmask);
	return TRUE;
    }

    if (rtmlen <= mlen) {
	(void) sprintf(errbuf,
		       "SLSP route mask %#A must be more specific than instance mask %#A",
		       inp->slsp_mask,
		       inp->slsp_rtmask);
	return TRUE;
    }

    if (sock2host(inp->slsp_addr, inp->slsp_mask) == 0) {
	(void) sprintf(errbuf,
		       "SLSP node %#A subnet part is zero with instance mask %#A",
		       inp->slsp_addr,
		       inp->slsp_mask);
	return TRUE;
    }

    if (sock2host(inp->slsp_addr, inp->slsp_rtmask) != 0) {
	(void) sprintf(errbuf,
		       "SLSP node %#A host part not zero with route mask %#A",
		       inp->slsp_addr,
		       inp->slsp_rtmask);
	return TRUE;
    }

    /*
     * This looks reasonable, see if it disagrees with an existing
     * instance.
     */
    inp_chk = slsp_instance_list;
    inp_prev = (slsp_instance *) 0;
    in_id = sock2ip(inp->slsp_addr) & sock2ip(inp->slsp_mask);
    while (inp_chk) {
	if ((sock2ip(inp_chk->slsp_addr) & sock2ip(inp_chk->slsp_mask)) == in_id) {
	    /*
	     * Same instance identifier.  See this guy isn't deleted, if
	     * so we've got duplicates.
	     */
	    if (!BIT_TEST(inp_chk->slsp_flags, SLSPF_DELETED)) {
		(void) sprintf(errbuf,
			       "SLSP node %#A has same instance identifier as node %#A",
				inp->slsp_addr,
				inp_chk->slsp_addr);
		return TRUE;
	    }

	    /*
	     * Deleted guy.  If the masks match undelete him and use him
	     * instead.  Otherwise leave him deleted.
	     */
	    if (sock2ip(inp->slsp_addr) == sock2ip(inp_chk->slsp_addr)
	      && inp->slsp_mask == inp_chk->slsp_mask
	      && inp->slsp_rtmask == inp_chk->slsp_rtmask) {
		BIT_RESET(inp_chk->slsp_flags, SLSPF_DELETED);
		inp_chk->slsp_def_parms = inp->slsp_def_parms;
		inp_chk->slsp_preference = inp->slsp_preference;
		inp_chk->slsp_gateways = inp->slsp_gateways;
		inp_chk->slsp_policy = inp->slsp_policy;
		sockfree(inp->slsp_addr);
		SLSP_INSTANCE_FREE(inp);
		inp = inp_chk;
		if (!inp_prev) {
		    slsp_instance_list = inp->slsp_next;
		} else {
		    inp_prev->slsp_next = inp->slsp_next;
		}
	    }
	    break;
	}
	inp_prev = inp_chk;
	inp_chk = inp_chk->slsp_next;
    }

    /*
     * Okay, insert this guy as the last undeleted instance.
     */
    if (!(inp_chk = slsp_instance_list)
      || BIT_TEST(inp_chk->slsp_flags, SLSPF_DELETED)) {
	inp->slsp_next = inp_chk;
	slsp_instance_list = inp;
    } else {
	while (inp_chk->slsp_next
	  && !BIT_TEST(inp_chk->slsp_next->slsp_flags, SLSPF_DELETED)) {
	    inp_chk = inp_chk->slsp_next;
	}
	inp->slsp_next = inp_chk->slsp_next;
	inp_chk->slsp_next = inp;
    }

    /*
     * Finally, return this instance
     */
    *inpp = inp;
    return FALSE;
}


/*
 * slsp_parse_gateway_alloc - allocate a gateway structure for the parser.
 */
slsp_gateway *
slsp_parse_gateway_alloc __PF2(inp, slsp_instance *,
			       addr, sockaddr_un *)
{
    slsp_gateway *sgw;

    SLSP_GATEWAY_GET(sgw);
    sgw->slsp_gw_addr = sockdup(addr);
    sgw->slsp_gw_parms = inp->slsp_def_parms;
    sgw->slsp_gw_trace_options = (trace *) 0;

    return sgw;
}


/*
 * slsp_parse_gateway_check - check a gateway structure for the parser.
 */
int
slsp_parse_gateway_check __PF3(inp, slsp_instance *,
			       sgwp, slsp_gateway **,
			       errbuf, char *)
{
    slsp_gateway *sgw_prev;
    slsp_gateway *sgw = *sgwp;

    /*
     * Make sure we have no duplicates for this guy.  Add him to the
     * list while we're at it.
     */
    if ((sgw_prev = inp->slsp_gateways)) {
	for (;;) {	/* Exits from middle */
	    if (sock2ip(sgw_prev->slsp_gw_addr) == sock2ip(sgw->slsp_gw_addr)) {
		(void) sprintf(errbuf,
			       "SLSP instance %#A duplicate gateway %A",
			       inp->slsp_addr,
			       sgw->slsp_gw_addr);
		return TRUE;
	    }
	    if (!(sgw_prev->slsp_gw_next)) {
		break;
	    }
	    sgw_prev = sgw_prev->slsp_gw_next;
	}
	sgw_prev->slsp_gw_next = sgw;
    } else {
	inp->slsp_gateways = sgw;
    }

    /*
     * That's it.
     */
    return FALSE;
}

/*
 * slsp_gateways_delete - delete the gateways from an instance
 */
static void
slsp_gateways_delete __PF1(inp, slsp_instance *)
{
    slsp_gateway *sgw, *sgw_next;

    sgw = inp->slsp_gateways;
    while (sgw) {
	sgw_next = sgw->slsp_gw_next;
	sockfree(sgw->slsp_gw_addr);
	if (sgw->slsp_gw_trace_options) {
	    (void) trace_free(sgw->slsp_gw_trace_options);
	}
	SLSP_GATEWAY_FREE(sgw);
	sgw = sgw_next;
    }
    inp->slsp_gateways = (slsp_gateway *) 0;
}


/*
 * slsp_config_free - used by the policy code when freeing slsp policy
 *		      structures.
 */
void
slsp_config_free __PF1(cp, config_entry *)
{
    switch (cp->config_type) {
    case SLSP_CONFIG_TRACE:
	if (cp->config_data) {
	    trace_free((trace *) cp->config_data);
	}
	break;

    default:
	/* Just a value */
	break;
    }
}


/*
 * slsp_terminate_instance - terminate an instance.  Take down the adjacencies,
 *			     delete the database and remove the routes, then
 *			     blow away the instance structure.
 */
static void
slsp_terminate_instance __PF1(inp, slsp_instance *)
{
    /* adjacencies first */
    slsp_nbr_terminate_all(inp);

    /* now the routes */
    slsp_rt_terminate(inp);

    /* finally the database */
    slsp_db_terminate(inp);

    /* clean out anything attached to the structure */
    if (inp->slsp_gateways) {
	slsp_gateways_delete(inp);
    }
    if (inp->slsp_policy) {
	adv_free_list(inp->slsp_policy);
    }
    if (inp->slsp_trace_options) {
	(void) trace_free(inp->slsp_trace_options);
    }
    if (inp->slsp_addr) {
	sockfree(inp->slsp_addr);
    }
    if (inp->slsp_task) {
	task_delete(inp->slsp_task);
    }

    /* Pull it off the instance list and free it */
    if (inp == slsp_instance_list) {
	slsp_instance_list = inp->slsp_next;
    } else {
	register slsp_instance *inp_prev = slsp_instance_list;

	while (inp_prev->slsp_next != inp) {
	    inp_prev = inp_prev->slsp_next;
	}
	inp_prev->slsp_next = inp->slsp_next;
    }
    SLSP_INSTANCE_FREE(inp);
}


/*
 * slsp_terminate - task termination routine.  Just calls the instance
 *		    termination routine.
 */
static void
slsp_terminate __PF1(tp, task *)
{
    slsp_instance *inp = (slsp_instance *)(tp->task_data);

    slsp_terminate_instance(inp);
}


/*
 * slsp_var_init - initialize default globals
 */
void
slsp_var_init()
{
    doing_slsp = FALSE;
}


/*
 * slsp_cleanup - task cleanup routine run before a reparse.
 */
static void
slsp_cleanup __PF1(tp, task *)
{
    slsp_instance *inp = (slsp_instance *)(tp->task_data);
    slsp_neighbour *nbr;

    /*
     * Blow away the policy and the gateways.
     */
    if (inp->slsp_policy) {
	adv_free_list(inp->slsp_policy);
	inp->slsp_policy = (adv_entry *) 0;
    }
    if (inp->slsp_gateways) {
	slsp_gateways_delete(inp);
    }
    BIT_SET(inp->slsp_flags, SLSPF_DELETED);

    /*
     * Now walk the structures looking for trace options to free up.
     * What a pain.
     */
    trace_freeup(inp->slsp_trace_options);
    trace_freeup(tp->task_trace);

    for (nbr = inp->slsp_nbrs; nbr; nbr = nbr->slsp_nbr_next) {
	trace_freeup(nbr->slsp_nbr_trace_options);
	if (nbr->slsp_nbr_list) {
	    register slsp_neighbour *child_nbr;

	    for (child_nbr = nbr->slsp_nbr_list;
		 child_nbr;
		 child_nbr = child_nbr->slsp_nbr_next) {
		trace_freeup(child_nbr->slsp_nbr_trace_options);
	    }
	}
    }

    /*
     * Blow out the global options.  Someone has to do it.
     */
    trace_freeup(slsp_global_trace_options);
}


/*
 * slsp_dump - the task dump routine for an instance task
 */
static void
slsp_dump __PF2(tp, task *,
		fd, FILE *)
{
    slsp_instance *inp = (slsp_instance *)(tp->task_data);

    /*
     * Call the module dump routines.
     */
    (void) fprintf(fd,
		   "\tInstance address: %#A\tInstance mask: %A\tRoute mask: %A\n\n",
		   inp->slsp_addr,
		   inp->slsp_mask,
		   inp->slsp_rtmask);
    slsp_nbr_dump(fd, inp);
    slsp_db_dump(fd, inp);
    slsp_rt_dump(fd, inp);
}


/*
 * slsp_init - initialize SLSP.  We add tasks to the instance structures,
 *	       distribute trace options around and delete instances which
 *	       have gone away.
 */
void
slsp_init __PF0(void)
{
    slsp_instance *inp, *inp_next;

    /*
     * If we have no instances we are done.  Not configured, not
     * running from last configuration.
     */
    inp = slsp_instance_list;
    if (!inp) {
	return;
    }

    /*
     * Something to do here.  For each undeleted instance fetch
     * trace options and add a task, if necessary.
     */
    if (!BIT_TEST(inp->slsp_flags, SLSPF_DELETED)) {
	trace_inherit_global(slsp_global_trace_options,
			     slsp_trace_types,
			     (flag_t)0);
	slsp_io_start();

	do {
	    slsp_neighbour *nbr, *nbr_next;
	    slsp_gateway *sgw;

	    trace_inherit(inp->slsp_trace_options,
			  slsp_global_trace_options);
	    if (inp->slsp_task) {
		trace_set(inp->slsp_task->task_trace,
			  inp->slsp_trace_options);
	    } else {
		task *tp;

		inp->slsp_task = tp = task_alloc("SLSP",
						 TASKPRI_PROTO,
						 inp->slsp_trace_options);
		tp->task_addr = sockdup(inp->slsp_addr);
		tp->task_rtproto = RTPROTO_SLSP;
		tp->task_data = (void_t) inp;
		task_set_cleanup(tp, slsp_cleanup);
		task_set_ifachange(tp, slsp_ifachange);
		task_set_terminate(tp, slsp_terminate);
		task_set_dump(tp, slsp_dump);
		if (!task_create(tp)) {
		    task_quit(EINVAL);
		}

		inp->slsp_gw.gw_proto = RTPROTO_SLSP;
		assert(!(inp->slsp_nbrs));
	    }

	    /*
	     * Walk down the gateway list inheriting trace options
	     */
	    sgw = inp->slsp_gateways;
	    while (sgw) {
		trace_inherit(sgw->slsp_gw_trace_options,
			      inp->slsp_trace_options);
		sgw = sgw->slsp_gw_next;
	    }

	    /*
	     * Now walk down the neighbour list.  For each gateway peer
	     * make sure there is still a gateway entry which corresponds
	     * to him.  If not, blow him off.
	     */
	    nbr = inp->slsp_nbrs;
	    while (nbr) {
		nbr_next = nbr->slsp_nbr_next;
		if (nbr->slsp_nbr_type == SLSP_NTYPE_PTP_PEER) {
		    for (sgw = inp->slsp_gateways; sgw; sgw = sgw->slsp_gw_next) {
			if (sock2ip(sgw->slsp_gw_addr)
			  == sock2ip(nbr->slsp_nbr_addr)) {
			    assert(!(sgw->slsp_gw_nbr));
			    sgw->slsp_gw_nbr = nbr;
			    break;
			}
		    }

		    if (!sgw) {
			slsp_nbr_terminate(nbr);
		    }
		}
		nbr = nbr_next;
	    }

	    /*
	     * Finally, initialize the database for the
	     * instance if not already.
	     */
	    if (!(inp->slsp_local_node)) {
		slsp_db_init(inp);
	    }
	} while ((inp = inp->slsp_next)
	  && !BIT_TEST(inp->slsp_flags, SLSPF_DELETED));
    }

    /*
     * If we have any instances left they are deleted.  Dump them.
     */
    while (inp) {
	inp_next = inp->slsp_next;
	assert(BIT_TEST(inp->slsp_flags, SLSPF_DELETED));
	slsp_terminate_instance(inp);
    }

    /*
     * If we have no instances left, terminate the I/O subsystem.
     */
    if (!slsp_instance_list) {
	slsp_io_stop();
    }

    /*
     * All done.  The slsp_ifachange() routine will bring neighbours
     * up and inform them of configuration changes later.
     */
}

/*
 * %(Copyright)
 */
