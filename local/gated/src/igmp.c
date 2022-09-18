/*
 *  $Id: igmp.c,v 1.6 1995/01/26 07:51:24 pusateri Exp $
 */

/*%Copyright%*/

#define	INCLUDE_IOCTL
#define	INCLUDE_IF
#define	INCLUDE_IF_TYPES
#define	INCLUDE_MROUTE

#include "include.h"
#include "inet.h"
#include "inet_multi.h"
#include "krt_ipmulti.h"
#include "igmp.h"

PROTOTYPE(igmp_job, static void, (task_timer *, time_t));
PROTOTYPE(igmp_timeout, static void, (task_timer *, time_t));

static task *igmp_task = (task *) 0;
static task_timer *igmp_timer_query;	/* to send Host Membership Queries */

#define	IGMP_QUERY_OFFSET	1	/* don't send initial query for 1 sec */

int igmp_current_status = 0;		/* whether IGMP is currently on */
int igmp_config_status = 0;		/* whether IGMP is on in new config */

sockaddr_un *igmp_all_hosts = 0;	/* All Hosts Group - 224.0.0.1 */

const bits igmp_proto_bits[] =
{
    {IPMULTI_PROTO_MOSPF, "MOSPF"},
    {IPMULTI_PROTO_DVMRP, "DVMRP"},
    {IPMULTI_PROTO_PIM, "PIM"},
    {IPMULTI_PROTO_CBT, "CBT"},
    {0}
};

/*
 * protocol defaults
 */

int igmp_default_queryinterval;		/* default query interval */
int igmp_default_timeoutinterval;	/* default timeout interval */

/*
 * local group database
 */

static block_t group_block_index;

/*
 * configuration interface lists
 */

adv_entry *igmp_int_policy = 0;		/* IGMP control info */

/*
 * tracing details
 */

trace *igmp_trace_options = { 0 };	/* Trace flags */

static const flag_t igmp_trace_masks[] = {
    TR_ALL,			/* 0 - ALL types */
    TR_IGMP_DETAIL_QUERY,	/* 1 - QUERY */
    TR_IGMP_DETAIL_REPORT,	/* 2 - REPORT */
    0,				/* 3 - DVMRP */
    0,				/* 4 - PIM */
    TR_IGMP_DETAIL_MTRACE,	/* 5 - Cisco Multicast Trace */
    TR_IGMP_DETAIL_REPORT,	/* 6 - New REPORT */
    TR_IGMP_DETAIL_LEAVE,	/* 7 - LEAVE */
    0,				/* 8 - unassigned */
    0,				/* 9 - unassigned */
    0,				/* a - unassigned */
    0,				/* b - unassigned */
    0,				/* c - unassigned */
    0,				/* d - unassigned */
    TR_IGMP_DETAIL_MTRACE,	/* e - Traceroute Response */
    TR_IGMP_DETAIL_MTRACE,	/* f - Traceroute Request */
    0
} ;

const bits igmp_trace_types[] = {
    { TR_DETAIL,	"detail packets" },
    { TR_DETAIL_SEND,	"detail send packets" },
    { TR_DETAIL_RECV,	"detail recv packets" },
    { TR_PACKET,	"packets" },
    { TR_PACKET_SEND,	"send packets" },
    { TR_PACKET_RECV,	"recv packets" },
    { TR_DETAIL_1,	"detail query" },
    { TR_DETAIL_SEND_1,	"detail send query" },
    { TR_DETAIL_RECV_1,	"detail recv query" },
    { TR_PACKET_1,	"query" },
    { TR_PACKET_SEND_1,	"send query" },
    { TR_PACKET_RECV_1,	"recv query" },
    { TR_DETAIL_2,	"detail report" },
    { TR_DETAIL_SEND_2,	"detail send report" },
    { TR_DETAIL_RECV_2,	"detail recv report" },
    { TR_PACKET_2,	"report" },
    { TR_PACKET_SEND_2,	"send report" },
    { TR_PACKET_RECV_2,	"recv report" },
    { TR_DETAIL_3,	"detail leave" },
    { TR_DETAIL_SEND_3,	"detail send leave" },
    { TR_DETAIL_RECV_3,	"detail recv leave" },
    { TR_PACKET_3,	"leave" },
    { TR_PACKET_SEND_3,	"send leave" },
    { TR_PACKET_RECV_3,	"recv leave" },
    { TR_DETAIL_4,	"detail mtrace" },
    { TR_DETAIL_SEND_4,	"detail send mtrace" },
    { TR_DETAIL_RECV_4,	"detail recv mtrace" },
    { TR_PACKET_4,	"mtrace" },
    { TR_PACKET_SEND_4,	"send mtrace" },
    { TR_PACKET_RECV_4,	"recv mtrace" },
    { 0, NULL }
};


/*
 * Create callback list of routines to be called when
 * an IGMP packet of a particular type is requested.
 * Useful since DVMRP and PIM piggy back on IGMP messages.
 */

struct _igmp_recv_types {
    void (*recv_routine)();
};

static struct _igmp_recv_types igmp_recv_types[] = {
    { 0 },		/* IGMP_UNDEFINED */
    { 0 },		/* IGMP_MEMBERSHIP_QUERY */
    { 0 },		/* IGMP_MEMBERSHIP_REPORT */
    { 0 },		/* IGMP_PROTO_DVMRP */
    { 0 },		/* IGMP_PROTO_PIM */
    { 0 },		/* IGMP_CISCO_TRACE */
    { 0 },		/* IGMP_NEW_MEMBERSHIP_REPORT */
    { 0 },		/* IGMP_MEMBERSHIP_LEAVE */
    { 0 },		/* UNUSED */
    { 0 },		/* UNUSED */
    { 0 },		/* UNUSED */
    { 0 },		/* UNUSED */
    { 0 },		/* UNUSED */
    { 0 },		/* UNUSED */
    { 0 },		/* IGMP_MTRACE_RESPONSE */
    { 0 },		/* IGMP_MTRACE_REQUEST */
    { 0 }
};


/*
 *	Request IGMP packet types.
 *	This routine registers a callback function to receive an IGMP
 *	packet of a particular type. The type should match the
 *	group_type field in the packet header. The common group_type's
 *	are enumerated above.
 *
 *	Assumptions: Only one routing protocol needs a particular
 *	group_type. May not be true for IGMP_MEMBERSHIP_QUERY
 *	messages which are used by multicast routing protocols
 *	for router discovery.
 */
int
igmp_register_recv(code, callback)
int code;
_PROTOTYPE(callback,
	   void,
	   (if_addr *,
	    struct igmp *,
	    int));
{
	/*
	 * IGMP must be running before any protocol can
	 * register receive routines
	 */

    assert(igmp_task);

    trace_tp(igmp_task,
	     TR_NORMAL,
	     0,
	     ("igmp_register_recv: registering 0x%0x for packet type 0x%0x",
	      callback,
	      code));

    if (igmp_recv_types[code - IGMP_BASE_TYPE].recv_routine) {
	trace_only_tf(igmp_trace_options,
	 0,
	 ("igmp_register_recv: packet type 0x%0x already being received",
	 code));
	 return -1;
    } else {
	igmp_recv_types[code - IGMP_BASE_TYPE].recv_routine = callback;
	return 0;
    }
}

/*
 *	No longer need IGMP packet types.
 *	The routing protocol no longer wished to receive packets of
 *	this particular type. Protocol may have been disabled on this
 *	interface.
 */
int
igmp_unregister_recv	 __PF1(code, int)
{
	/*
	 * IGMP must be running before any protocol can
	 * register receive routines
	 */

    assert(igmp_task);

    trace_tp(igmp_task,
	     TR_NORMAL,
	     0,
	     ("igmp_unregister_recv: removing receive routine for type 0x%0x",
	      code));

    if (igmp_recv_types[code - IGMP_BASE_TYPE].recv_routine) {
	igmp_recv_types[code - IGMP_BASE_TYPE].recv_routine = (void_t) 0;
	return 0;
    } else {
	trace_only_tf(igmp_trace_options,
	 0,
	 ("igmp_unregister_recv: packet type 0x%0x not being received",
	 code));
	 return -1;
    }
}

/*
 * Create callback list of routines to be called when
 * a new group is added or an existing group is timed out.
 */

typedef struct _igmp_change_notify {
    struct _igmp_change_notify *forw, *back;
    void (*change_routine)();
} igmp_change_notify;

static igmp_change_notify igmp_change_head =
	{ &igmp_change_head, &igmp_change_head };

static block_t change_block_index;
/*
 * Caller requests notification when a new group is added or
 * an existing group times out.
 */

#define	CHANGE_LIST(cp, list)	{ for (cp = (list)->forw; cp != list; cp = cp->forw)
#define CHANGE_LIST_END(cp, list)	if (cp == list) cp = (igmp_change_notify *) 0; }

int
igmp_register_group_change(callback)
_PROTOTYPE(callback,
	   void,
	   (int,
	    if_addr *,
	    u_int32));
{
    igmp_change_notify *cp;

	/*
	 * IGMP must be running before any protocol can
	 * register group change routines
	 */

    assert(igmp_task);

    trace_tp(igmp_task,
	     TR_NORMAL,
	     0,
	     ("igmp_register_group_change: registering address 0x%0x",
	      callback));

    CHANGE_LIST(cp, &igmp_change_head) {
	if (cp->change_routine == callback) {
	    /*
	     * already registered
	     */
	    trace_tp(igmp_task,
		TR_NORMAL,
		0,
		("igmp_register_group_change: address 0x%0x already registered",
		 callback));
	    return 1;
	}
    } CHANGE_LIST_END(cp, &igmp_change_head);

    cp = (igmp_change_notify *) task_block_alloc(change_block_index);
    cp->change_routine = callback;

    INSQUE(cp, igmp_change_head.back);
    return 0;
}

/*
 *	The routing protocol no longer want notified of changes to
 *	group membership. Protocol may have been disabled on this
 *	interface.
 */
int
igmp_unregister_group_change(callback)
_PROTOTYPE(callback,
	   void,
	   (int,
	    if_addr *,
	    u_int32));
{
    igmp_change_notify *cp;

	/*
	 * IGMP must be running before any protocol can
	 * register group change routines
	 */

    assert(igmp_task);
    trace_tp(igmp_task,
	     TR_NORMAL,
	     0,
	     ("igmp_unregister_group_change: unregistering address 0x%0x",
	      callback));

    CHANGE_LIST(cp, &igmp_change_head) {
	if (cp->change_routine == callback) {
	    /* Found it! */

	    REMQUE(cp);

	    return 0;
	}
    } CHANGE_LIST_END(cp, &igmp_change_head);

    trace_tp(igmp_task,
	TR_NORMAL,
	0,
	("igmp_unregister_group_change: address 0x%0x not registered",
	 callback));
    return 1;
}
/*
 *	Trace IGMP packets
 */
static void
igmp_trace __PF7(trp, trace *,
		dir, int,
    		ifap, if_addr *,
		who, sockaddr_un *,
		msg, register struct igmp *,
		size, register size_t,
    		detail, int)
{
    if (dir) {
	/* Trace packet transmission */

	tracef("IGMP %sSENT %A -> %#A ",
	       dir > 0 ? "" : "*NOT* ",
	       ifap ? ifap->ifa_addr_local : sockbuild_str(""),
	       who);
    } else {
	/* Trace packet reception */
	tracef("IGMP RECV %#A ",
	       who);
	if (task_recv_dstaddr) {
	    /* Some systems report the destination address */
	    tracef("-> %A ",
		   task_recv_dstaddr);
	}
    }
    switch (msg->igmp_type) {
	case IGMP_MEMBERSHIP_QUERY:
		tracef("Host Membership Query: ");
		break;
	case IGMP_MEMBERSHIP_REPORT:
		tracef("Host Membership Report: group %A ",
			sockbuild_in(0, msg->igmp_group));
		break;
	case IGMP_NEW_MEMBERSHIP_REPORT:
		tracef("New Host Membership Report: group %A ",
			sockbuild_in(0, msg->igmp_group));
		break;
	case IGMP_MEMBERSHIP_LEAVE:
		tracef("Host Membership Leave: group %A ",
			sockbuild_in(0, msg->igmp_group));
		break;
	case IGMP_CISCO_TRACE:
		tracef("Cisco Multicast Trace: ");
		break;
	case IGMP_MTRACE_REQUEST:
		tracef("Multicast Trace Request: ");
		break;
	case IGMP_MTRACE_RESPONSE:
		tracef("Multicast Trace Response: ");
		break;
    }

    if (detail) {
	tracef("vers %d, type %d, code %d, length %d",
	       (msg->igmp_type >> 4) & 0x0f,
	       msg->igmp_type & 0x0f,
	       msg->igmp_code,
	       size);

    }

    trace_only_tf(trp,
		  0,
		  (NULL));
}

/*
 * Send an IGMP message to the specified interface.
 * Generic IGMP send routine for all piggybacked protocols (DVMRP, PIM)
 */

int
igmp_send __PF5(ifap, if_addr *,
		ip, struct ip *,
		iplen, int,
		dst, sockaddr_un *,
		loop, int)
{
    int rc;
    static if_addr *last_ifap;

	/*
	 * Include the IP header for the 3.3 kernel's sake
	 */

    ip->ip_v = IPVERSION;
    ip->ip_hl = sizeof(struct ip) >> 2;
    ip->ip_tos = 0;
    ip->ip_off = 0;
    ip->ip_p = IPPROTO_IGMP;
    ip->ip_len = iplen;
    ip->ip_src.s_addr = sock2ip(ifap->ifa_addr);
    ip->ip_dst.s_addr = sock2ip(dst);
    ip->ip_ttl = 1;

    if (last_ifap != ifap) {
	(void) task_set_option(igmp_task, TASKOPTION_MULTI_IF, last_ifap = ifap);
    }

    if (loop) {
	/* send a copy to our loopback */
	if (task_set_option(igmp_task,
			    TASKOPTION_MULTI_LOOP,
			    TRUE) < 0) {
	    task_quit(errno);
	}
    }

    rc = task_send_packet(igmp_task, (void_t) ip, iplen, 0, dst);

    if (loop) {
	/* disable sending to our loopback */
	if (task_set_option(igmp_task,
			    TASKOPTION_MULTI_LOOP,
			    FALSE) < 0) {
	    task_quit(errno);
	}
    }
    return rc;
}

/*
 * Send an IGMP Query to the specified interface.
 *
 * Called when the query timer expires for all interfaces that
 * this router is the DR for.
 */

static void
igmp_send_query	 __PF2(ifap, if_addr *,
		       dst, sockaddr_un *)
{
    int rc;
    struct ip *ip = task_get_send_buffer(struct ip *);
    struct igmp *pkt = (struct igmp *) (ip+1);

    pkt->igmp_type = IGMP_MEMBERSHIP_QUERY;
	/*
	 * the igmp_code ends up meaning the maximum report delay
	 * if this is a group specific query.
	 * Talk about overloading a field!
	 */
    if (sockaddrcmp_in(dst, igmp_all_hosts)) {
	pkt->igmp_code = 0;
    } else {
	pkt->igmp_code = IGMP_MAX_HOST_REPORT_DELAY;
    }
    pkt->igmp_group = 0;

    /* Calculate packet checksum */
    pkt->igmp_cksum = 0;
    pkt->igmp_cksum = inet_cksum((void_t) pkt, sizeof(struct igmp));

    rc = igmp_send(ifap,
		   ip,
		   sizeof(struct ip) + sizeof(struct igmp),
		   dst,
		   TRUE);


    /* Should we trace this packet? */

    if (TRACE_PACKET_SEND_TP(igmp_task,
			     (pkt->igmp_type - IGMP_BASE_TYPE),
			     (IGMP_MAX_TYPE - IGMP_BASE_TYPE),
			     igmp_trace_masks)) {

	igmp_trace(igmp_task->task_trace,
		   rc,
		   ifap,
		   igmp_all_hosts,
		   pkt,
		   sizeof(struct igmp),
		   TRACE_DETAIL_SEND_TP(igmp_task,
				        (pkt->igmp_type - IGMP_BASE_TYPE),
				        (IGMP_MAX_TYPE - IGMP_BASE_TYPE),
				        igmp_trace_masks));
    }
}

/*ARGSUSED*/
static void
igmp_timeout  __PF2(tip, task_timer *,
		    interval, time_t)
{
    if_addr *ifap = (if_addr *)(tip->task_timer_data);
    struct group_list *gp, *aged;
    struct group_list *list =  (struct group_list *) ifap->igmp_if_group_list;
    igmp_change_notify *cp;

	/*
	 * search for groups that aged out
	 * will all be at beginning of list
	 */

    gp = list->forw;
    while(gp != list &&
	   (time_sec - gp->refresh_time) >= igmp_default_timeoutinterval) {
	aged = gp;
	gp = gp->forw;
	REMQUE(aged);
	trace_tp(igmp_task,
		 TR_NORMAL,
		 0,
		 ("igmp_timeout: Group %A on interface %A(%s) timed out.",
		  sockbuild_in(0, aged->group_addr.s_addr),
		  ifap->ifa_addr,
		  ifap->ifa_link->ifl_name));
	    /*
	     * Notify other protocols of removed group for pruning
	     */
	if (ntohl(aged->group_addr.s_addr) > INADDR_MAX_LOCAL_GROUP) {
	    CHANGE_LIST(cp, &igmp_change_head) {
		if (cp->change_routine)
		    (*cp->change_routine)(IGMP_GROUP_REMOVED,
					  ifap,
					  aged->group_addr.s_addr);
	    } CHANGE_LIST_END(cp, &igmp_change_head);
	}
	task_block_free(group_block_index, (void_t) aged);
    }
	/*
	 * if there's more entries in the list, reset the timer
	 */
    if (list != list->forw) {
	task_timer_set((task_timer *)ifap->igmp_if_timer_timeout,
		       (time_t) 0,
		       igmp_default_timeoutinterval -
		       (time_sec - list->forw->refresh_time));
    }
}

/*ARGSUSED*/
static void
igmp_job  __PF2(tip, task_timer *,
	        interval, time_t)
{
    int stop_timer = 1;
    register if_addr *ifap;

    IF_ADDR(ifap) {
	struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_IGMP];
	if (BIT_TEST(ips->ips_state, IFPS_DR_STATUS)) {

	    stop_timer = 0;
	    igmp_send_query(ifap, igmp_all_hosts);

	}
    } IF_ADDR_END(ifap) ;

    if (stop_timer) {
	task_timer_reset(igmp_timer_query);
    }
}


/*
 * 	Called when an IGMP packet is available for reading.
 */
static void
igmp_recv __PF1(tp, task *)
{
    size_t igmplen;
    int n_packets = TASK_PACKET_LIMIT;

    while (n_packets-- && !task_receive_packet(tp, &igmplen)) {
	register struct igmp *igmp;
	register struct ip *ip;
	if_addr *ifap;

	ip = task_get_recv_buffer(struct ip *);

#ifdef	KRT_IPMULTI_TTL0
	    /*
	     * This section interprets requests from an IP Multicast 3.5
	     * Kernel. Requests come in on the IGMP socket instead of
	     * the routing socket. We redirect them to the kernel code.
	     */
	if (ip->ip_p == 0) {
#ifdef IGMPMSG_NOCACHE
	    ifaddr *vif_ifap = 0;
	    struct igmpmsg *msg = ip;

	    IF_ADDR(ifap) {
		if (ifap->ifa_vif == msg->im_vif) {
		    vif_ifap = ifap;
		    break;
		}
	    } IF_ADDR_END(ifap) ;

	    switch(msg->im_msgtype) {
	    case IGMPMSG_NOCACHE:
#endif	/* IGMPMSG_NOCACHE */

		    krt_generate_mfc(EADDRNOTAVAIL,
				     sockbuild_in(0, ip->ip_dst.s_addr),
				     NULL,
				     sockbuild_in(0, ip->ip_src.s_addr));
#ifdef IGMPMSG_NOCACHE
		    break;

	    case IGMPMSG_WRONGVIF:

		    krt_generate_mfc(EADDRINUSE,
				     sockbuild_in(0, msg->im_dst.s_addr),
				     vif_ifap,
				     sockbuild_in(0, msg->im_src.s_addr));
		    break;
	    }
#endif	/* IGMPMSG_NOCACHE */
	    return;
	}
#endif	/* KRT_IPMULTI_TTL0 */

	igmp = (struct igmp *) ((caddr_t) ip + task_parse_ip_hl(ip));

		/* Remove IP header from length */
	igmplen -= task_parse_ip_hl(ip);

	if (igmplen != ip->ip_len) {
	    trace_log_tf(igmp_trace_options,
			 0,
			 LOG_ERR,
			 ("igmp_recv: length mismatch: read: %u, ip_len: %u",
			  igmplen,
			  ip->ip_len));
	    continue;
	}
	
		/* make sure IGMP length is sensible */
	if (igmplen < IGMP_MIN_PACKET_LENGTH) {
	    trace_log_tf(igmp_trace_options,
			 0,
			 LOG_ERR,
			 ("igmp_recv: igmp length too short: %u from %A",
			  igmplen,
			  task_recv_srcaddr));
	    continue;
	}
		/* verify checksum */
	if (inet_cksum((void_t) igmp, igmplen)) {
	    trace_log_tf(igmp_trace_options,
			 0,
			 LOG_WARNING,
			 ("igmp_recv: bad IGMP checksum from %A",
			  task_recv_srcaddr));
	    continue;
	}
	ifap = if_withdst(task_recv_srcaddr);
	if (ifap == 0)
	    ifap = if_withlcladdr(task_recv_srcaddr, FALSE);

	if (!ifap) {
	    trace_log_tf(igmp_trace_options,
			 0,
			 LOG_WARNING,
			 ("igmp_recv: ignoring igmp msg from remote source: %A",
			  task_recv_srcaddr));
	    continue;
	}

	if (igmp->igmp_type >> 4 != 1) {
	    trace_log_tf(igmp_trace_options,
			 0,
			 LOG_WARNING,
			 ("igmp_recv: Unsupported Version %d from %A",  
			  igmp->igmp_type >> 4,
			  task_recv_srcaddr));
	    continue;
	}
	if (igmp->igmp_type == IGMP_BASE_TYPE ||
	    igmp->igmp_type >= IGMP_MAX_TYPE) {
	    trace_log_tf(igmp_trace_options,
			 0,
			 LOG_WARNING,
			 ("igmp_recv: Unsupported Code %d from %A",  
			  igmp->igmp_type & 0x0f,
			  task_recv_srcaddr));
	    continue;
	}

	/*
	 * If someone has registered for this packet type,
	 * call their receive routine.
	 */
	if (igmp_recv_types[igmp->igmp_type - IGMP_BASE_TYPE].recv_routine)
	    (*igmp_recv_types[igmp->igmp_type - IGMP_BASE_TYPE].recv_routine)(ifap, igmp, igmplen);
    }
}

/*
 *	Receive Membership Query Packets
 */
static void
igmp_recv_membership_query __PF3(ifap, if_addr *,
				 igmp, struct igmp *,
				 igmplen, int)
{
    /* Should we trace this packet? */
    if (TRACE_PACKET_RECV_TP(igmp_task,
			     (igmp->igmp_type - IGMP_BASE_TYPE),
			     (IGMP_MAX_TYPE - IGMP_BASE_TYPE),
			     igmp_trace_masks)) {

	igmp_trace(igmp_task->task_trace,
		   FALSE,
		   ifap,
		   task_recv_srcaddr,
		   igmp,
		   igmplen,
		   TRACE_DETAIL_RECV_TP(igmp_task,
					(igmp->igmp_type - IGMP_BASE_TYPE),
					(IGMP_MAX_TYPE - IGMP_BASE_TYPE),
					igmp_trace_masks));
    }
}

/*
 *	Receive Trace Packets
 */
static void
igmp_recv_trace __PF3(ifap, if_addr *,
		      igmp, struct igmp *,
		      igmplen, int)
{
    /* Should we trace this packet? */
    if (TRACE_PACKET_RECV_TP(igmp_task,
			     (igmp->igmp_type - IGMP_BASE_TYPE),
			     (IGMP_MAX_TYPE - IGMP_BASE_TYPE),
			     igmp_trace_masks)) {

	igmp_trace(igmp_task->task_trace,
		   FALSE,
		   ifap,
		   task_recv_srcaddr,
		   igmp,
		   igmplen,
		   TRACE_DETAIL_RECV_TP(igmp_task,
					(igmp->igmp_type - IGMP_BASE_TYPE),
					(IGMP_MAX_TYPE - IGMP_BASE_TYPE),
					igmp_trace_masks));
    }
}


/*
 *	Receive Membership Report Packets
 */
static void
igmp_recv_membership_report __PF3(ifap, if_addr *,
				  igmp, struct igmp *,
				  igmplen, int)
{
    time_t timeout;
    struct group_list *gp;
    struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_IGMP];
    struct group_list *list =  (struct group_list *) ifap->igmp_if_group_list;
    igmp_change_notify *cp;

    /* Should we trace this packet? */
    if (TRACE_PACKET_RECV_TP(igmp_task,
			     (igmp->igmp_type - IGMP_BASE_TYPE),
			     (IGMP_MAX_TYPE - IGMP_BASE_TYPE),
			     igmp_trace_masks)) {

	igmp_trace(igmp_task->task_trace,
		   FALSE,
		   ifap,
		   task_recv_srcaddr,
		   igmp,
		   igmplen,
		   TRACE_DETAIL_RECV_TP(igmp_task,
					(igmp->igmp_type - IGMP_BASE_TYPE),
					(IGMP_MAX_TYPE - IGMP_BASE_TYPE),
					igmp_trace_masks));
    }

    if (task_recv_dstaddr && sock2ip(task_recv_dstaddr) != igmp->igmp_group) {
	trace_log_tf(igmp_trace_options,
	     0,
	     LOG_WARNING,
	     ("igmp_recv_membership_report: group %A doesn't match dest ip %A",
	      sockbuild_in(0, igmp->igmp_group),
	      task_recv_dstaddr));
    }

    /*
     * If we are DR on this interface (set by the multicast routing
     * protocol running on this interface) then we will listen to
     * Host Membership Reports. Otherwise, we ignore them.
     */

    if (BIT_TEST(ips->ips_state, IFPS_DR_STATUS)) {

	    /* Search if group is already in database */

	GROUP_LIST(gp, list) {
	    if (gp->group_addr.s_addr == igmp->igmp_group) {
		/* Found it! */

		REMQUE(gp);
		goto Found;
	    }
	} GROUP_LIST_END(gp, list);

	    /* If not, Allocate a block to store this packet */
	gp = (struct group_list *) task_block_alloc(group_block_index);
	gp->group_addr.s_addr = igmp->igmp_group;

	    /*
	     * Notify other protocols of new group for grafting
	     */
	if (ntohl(gp->group_addr.s_addr) > INADDR_MAX_LOCAL_GROUP) {
	    CHANGE_LIST(cp, &igmp_change_head) {
		if (cp->change_routine)
		    (*cp->change_routine)(IGMP_GROUP_ADDED,
					  ifap,
					  gp->group_addr.s_addr);
	    } CHANGE_LIST_END(cp, &igmp_change_head);
	}

    Found:
	    /* Store as sorted list with oldest first */
	INSQUE(gp, list->back);

	gp->last_addr.s_addr = sock2ip(task_recv_srcaddr);
	gp->refresh_time = time_sec;
	    /*
	     * If we receive a report from new neighbors, then remember this
	     * so we can leave group immediately later. If both new and
	     * old neighbors exist, we will either get only an old
	     * membership report or we will get a new membership report
	     * followed by a old membership report.
	     */
	if (igmp->igmp_type == IGMP_NEW_MEMBERSHIP_REPORT) {
	    BIT_SET(gp->group_flags, IGMP_NEW_NEIGHBORS);
	} else {
	    BIT_RESET(gp->group_flags, IGMP_NEW_NEIGHBORS);
	}

	timeout = igmp_default_timeoutinterval - (time_sec - list->forw->refresh_time);
		/* if no timer running, create one */
	if (!ifap->igmp_if_timer_timeout) {
	    char name[IFNAMSIZ+9];
	    sprintf(name, "Timeout.%s", ifap->ifa_link->ifl_name); 
	    ifap->igmp_if_timer_timeout =
				(void_t) task_timer_create(igmp_task,
							   name,
							   (flag_t) 0,
							   (time_t) 0,
							   timeout,
							   igmp_timeout,
							   (void_t) ifap);
	}
		/* set existing timer to new time */
	else {
		/*
		 * No way to reset data without deleting timer and
		 * re-creating it. So for now, just cheat
		 */
	    ((task_timer *)ifap->igmp_if_timer_timeout)->task_timer_data = (void_t) ifap;
	    task_timer_set((task_timer *)ifap->igmp_if_timer_timeout,
			   (time_t) 0,
			   timeout);
	}
    }
}

/*
 *	Receive Membership Leave Packets
 */
static void
igmp_recv_membership_leave __PF3(ifap, if_addr *,
				 igmp, struct igmp *,
				 igmplen, int)
{
    struct group_list *gp, *ggp;
    struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_IGMP];
    struct group_list *list =  (struct group_list *) ifap->igmp_if_group_list;

    /* Should we trace this packet? */
    if (TRACE_PACKET_RECV_TP(igmp_task,
			     (igmp->igmp_type - IGMP_BASE_TYPE),
			     (IGMP_MAX_TYPE - IGMP_BASE_TYPE),
			     igmp_trace_masks)) {

	igmp_trace(igmp_task->task_trace,
		   FALSE,
		   ifap,
		   task_recv_srcaddr,
		   igmp,
		   igmplen,
		   TRACE_DETAIL_RECV_TP(igmp_task,
					(igmp->igmp_type - IGMP_BASE_TYPE),
					(IGMP_MAX_TYPE - IGMP_BASE_TYPE),
					igmp_trace_masks));
    }
    if (BIT_TEST(ips->ips_state, IFPS_DR_STATUS)) {

	    /* Search if group is already in database */

	GROUP_LIST(gp, list) {
	    if (gp->group_addr.s_addr == igmp->igmp_group) {
		/* Found it! */

		goto Found;
	    }
	} GROUP_LIST_END(gp, list);

	return;
Found:

	if (BIT_TEST(gp->group_flags, IGMP_NEW_NEIGHBORS)) {

	    REMQUE(gp);

		/*
		 * set timer to go off in IGMP_MAX_HOST_REPORT_DELAY seconds
		 * to delete group unless we receive another membership
		 * report before that.
		 */

	    gp->refresh_time = time_sec - igmp_default_timeoutinterval +
			       IGMP_MAX_HOST_REPORT_DELAY;
	    ggp = list->forw;
	    while(ggp != list) {
		if (gp->refresh_time < ggp->refresh_time) {
		    INSQUE(gp, ggp->back);
		    break;
		}
		ggp = ggp->forw;
	    }
		/*
		 * reached end without inserting group, stick it at end
		 */
	    if (ggp == list) {
		INSQUE(gp, list->back);
	    }

		/*
		 * send a group specific query
		 */
	    igmp_send_query(ifap, sockbuild_in(0, gp->group_addr.s_addr));

		/*
		 * reset the timer
		 */
	    task_timer_set((task_timer *)ifap->igmp_if_timer_timeout,
			   (time_t) 0,
			   list->forw->refresh_time +
			   igmp_default_timeoutinterval - time_sec);

	}
    }
}


/*
 * Enable a group to be received on the specified interface
 */

int
igmp_group_add  __PF2(ifap, if_addr *,
		      group, sockaddr_un *)
{
    krt_multicast_add(group);
    return task_set_option(igmp_task, TASKOPTION_GROUP_ADD, ifap, group);
}

/*
 * Disable a group being received on the specified interface
 */

int
igmp_group_drop  __PF2(ifap, if_addr *,
		       group, sockaddr_un *)
{
    krt_multicast_delete(group);
    return task_set_option(igmp_task, TASKOPTION_GROUP_DROP, ifap, group);
}


/*
 *	Enable DR status on interface.
 *	This routine is called by the multicast routing protocol running
 *	on this interface. A DR election is performed with other multicast
 *	routers on shared lans and if elected, this routine is called
 *	to begin sending Host Membership Queries. It also starts
 *	maintaining a Local Group Database of Host Membership Reports.
 */
void
igmp_enable_dr_status	 __PF1(ifap, if_addr *)
{
    struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_IGMP];
    struct group_list **listp = (struct group_list **) &ifap->igmp_if_group_list;
    struct group_list *list;

    if (!BIT_TEST(ips->ips_state, IFPS_DR_STATUS)) {

	trace_tp(igmp_task,
		 TR_STATE,
		 0,
		 ("igmp_enable_dr_status: Elected DR on interface %A(%s)",
		  ifap->ifa_addr,
		  ifap->ifa_link->ifl_name));
	BIT_SET(ips->ips_state, IFPS_DR_STATUS);
	list = (struct group_list *) task_block_alloc(group_block_index);
	list->forw = list;
	list->back = list;

	*listp = list;

		/* if no timer running, create one */
	if (!igmp_timer_query) {
	    igmp_timer_query = task_timer_create(igmp_task,
						 "Query",
						 (flag_t) 0,
						 igmp_default_queryinterval,
						 IGMP_QUERY_OFFSET,
						 igmp_job,
						 (void_t) 0);
	}
		/* if timer currently inactive, reactivate */
	else if (BIT_TEST(igmp_timer_query->task_timer_flags, TIMERF_INACTIVE)) {
	    task_timer_set(igmp_timer_query,
			   igmp_default_queryinterval,
			   IGMP_QUERY_OFFSET);
	}
	krt_multicast_add(igmp_all_hosts);
    }
}

/*
 *	Disable DR status on interface.
 *	If the routing protocol determines this multicast router is no
 *	longer DR on this interface, it disables DR status and stops
 *	sending Host Membership Queries on this interface.
 */
void
igmp_disable_dr_status	 __PF1(ifap, if_addr *)
{
    struct group_list *gp, *delete;
    struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_IGMP];
    struct group_list *list =  (struct group_list *) ifap->igmp_if_group_list;

    if (BIT_TEST(ips->ips_state, IFPS_DR_STATUS)) {

	trace_tp(igmp_task,
		 TR_STATE,
		 0,
		 ("igmp_disable_dr_status: Relinquishing DR status on interface %A(%s)",
		  ifap->ifa_addr,
		  ifap->ifa_link->ifl_name));

	BIT_RESET(ips->ips_state, IFPS_DR_STATUS);

		/*
		 * stop timer from running
		 */
	if (ifap->igmp_if_timer_timeout) {
	    task_timer_reset((task_timer *)ifap->igmp_if_timer_timeout);
	}

	assert(list);

	gp = list->forw;
	while(gp != list ) {
	    delete = gp;
	    gp = gp->forw;
	    REMQUE(delete);
	    task_block_free(group_block_index, (void_t) delete);
	}
	task_block_free(group_block_index, (void_t) list);
	ifap->igmp_if_group_list = (void_t) 0;

	krt_multicast_delete(igmp_all_hosts);
    }
}


/*
 * Since IP Multicast is based on RPF, it is difficult
 * to have more than a single multicast routing protocol
 * running on the same interface at the same time.
 * Therefore, the first protocol to grab the interface wins.
 */

int
igmp_set_ifproto  __PF2(ifap, if_addr *,
			proto, int)
{
    if (!ifap->igmp_if_proto) {
	ifap->igmp_if_proto = (void_t) proto;
	return TRUE;
    }

    trace_log_tf(igmp_trace_options,
		 0,
		 LOG_WARNING,
		 ("igmp_set_ifproto: can't enable proto %s, %s already configured",
		  igmp_proto_bits[proto].t_name,
		  igmp_proto_bits[(int) ifap->igmp_if_proto].t_name));
    return FALSE;
}

void
igmp_reset_ifproto  __PF2(ifap, if_addr *,
			  proto, int)
{
    if ((int) ifap->igmp_if_proto == proto) {
	ifap->igmp_if_proto = (void_t) 0;
    }
}

int
igmp_get_ifproto  __PF1(ifap, if_addr *)
{
    return (int) ifap->igmp_if_proto;
}

/*
 *	Cleanup before re-init
 */
/*ARGSUSED*/
static void
igmp_cleanup __PF1(tp, task *)
{
	/* Release policy list */

    adv_free_list(igmp_int_policy);
    igmp_int_policy = (adv_entry *) 0;


    if (tp) {
	trace_freeup(tp->task_trace);
    }
    trace_freeup(igmp_trace_options);
}

/*
 *	re-init routine
 */
/*ARGSUSED*/
static void
igmp_reinit __PF1(tp, task *)
{
    trace_set(igmp_task->task_trace, igmp_trace_options);
}


/*
 *	Terminating - clean up
 */
static void
igmp_terminate __PF1(tp, task *)
{
    register if_addr *ifap;


	/* Remove receive routines */
    igmp_unregister_recv( IGMP_MEMBERSHIP_QUERY );
    igmp_unregister_recv( IGMP_MEMBERSHIP_REPORT );
    igmp_unregister_recv( IGMP_NEW_MEMBERSHIP_REPORT );
    igmp_unregister_recv( IGMP_MEMBERSHIP_LEAVE );
    igmp_unregister_recv( IGMP_CISCO_TRACE );
    igmp_unregister_recv( IGMP_MTRACE_REQUEST );
    igmp_unregister_recv( IGMP_MTRACE_RESPONSE );


	/* Clean up tracing */
    igmp_cleanup(tp);

	/* free local group database and delete timer on each interface */
    IF_ADDR(ifap) {
	igmp_disable_dr_status(ifap);

        if (ifap->igmp_if_timer_timeout) {
	    task_timer_delete((task_timer *) ifap->igmp_if_timer_timeout);
            ifap->igmp_if_timer_timeout = (void_t) 0;
	}
    } IF_ADDR_END(ifap) ;

    if (igmp_timer_query) {
	task_timer_delete(igmp_timer_query);
	igmp_timer_query = (task_timer *) 0;
    }

    /* And exit */
	task_delete(tp);
}

/*
 *	Deal with interface policy
 */
static void
igmp_control_reset __PF2(tp, task *,
			  ifap, if_addr *)
{
    struct ifa_ps *ips = &ifap->ifa_ps[tp->task_rtproto];

    BIT_RESET(ips->ips_state, IFPS_RESET);
}


static void
igmp_control_set __PF2(tp, task *,
			ifap, if_addr *)
{
    struct ifa_ps *ips = &ifap->ifa_ps[tp->task_rtproto];
    config_entry **list = config_resolv_ifa(igmp_int_policy,
					    ifap,
					    IGMP_CONFIG_MAX);

    /* Init */
    igmp_control_reset(tp, ifap);

    if (list) {
	int type = IGMP_CONFIG_MAX;
	config_entry *cp;

	/* Fill in the parameters */
	while (--type) {
	    if ((cp = list[type])) {
		switch (type) {
		case IGMP_CONFIG_ENABLE:
		    if (BIT_TEST(ifap->ifa_state, IFS_LOOPBACK)) {
			trace_only_tf(igmp_trace_options,
			 0,
			 ("igmp_control_set: can't enable igmp on loopback"));
		    }
		    if (BIT_TEST(ifap->ifa_state, IFS_MULTICAST)) {
			BIT_RESET(ips->ips_state, IFPS_NOIN);
			BIT_RESET(ips->ips_state, IFPS_NOOUT);
		    } else {
			trace_only_tf(igmp_trace_options,
			 0,
			 ("igmp_control_set: interface %A(%s) not multicast capable",
			  ifap->ifa_addr,
			  ifap->ifa_link->ifl_name));
		    }

		    break;

		case IGMP_CONFIG_DISABLE:
		    BIT_SET(ips->ips_state, IFPS_NOIN);
		    BIT_SET(ips->ips_state, IFPS_NOOUT);
		    break;
		}
	    }
	}

	config_resolv_free(list, IGMP_CONFIG_MAX);
    }
}


/*
 *	Deal with an interface status change
 */
static void
igmp_ifachange __PF2(tp, task *,
		      ifap, if_addr *)
{
    struct ifa_ps *ips = &ifap->ifa_ps[tp->task_rtproto];

    if (socktype(ifap->ifa_addr) != AF_INET) {
	return;
    }
    
    switch (ifap->ifa_change) {
    case IFC_NOCHANGE:
    case IFC_ADD:
	if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
	    igmp_control_set(tp, ifap);
	    if (BIT_TEST(ifap->ifa_state, IFS_LOOPBACK) ||
	        BIT_TEST(ifap->ifa_state, IFS_POINTOPOINT)) {
		BIT_SET(ips->ips_state, IFPS_NOIN);
		BIT_SET(ips->ips_state, IFPS_NOOUT);
	    }
	}
	break;

    case IFC_DELETE:
    case IFC_DELETE|IFC_UPDOWN:

	igmp_control_reset(tp, ifap);
	igmp_disable_dr_status(ifap);
	break;

    default:
	/* Something has changed */

	if (BIT_TEST(ifap->ifa_change, IFC_UPDOWN)) {
	    if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
		/* Down to Up transition */

		igmp_control_set(tp, ifap);
		if (BIT_TEST(ifap->ifa_state, IFS_LOOPBACK)) {
		    BIT_SET(ips->ips_state, IFPS_NOIN);
		    BIT_SET(ips->ips_state, IFPS_NOOUT);
		}
	    } else {
		/* UP to DOWN transition */

		igmp_control_reset(tp, ifap);
		igmp_disable_dr_status(ifap);
	    }
	}
	break;
    }
}

static void
igmp_int_dump __PF2(fd, FILE *,
		    list, config_entry *)
{
    register config_entry *cp;

    CONFIG_LIST(cp, list) {
	switch (cp->config_type) {
	case IGMP_CONFIG_ENABLE:
	    (void) fprintf(fd, " %s enabled",
			   cp->config_data ? "" : "not");
	    break;

	case IGMP_CONFIG_DISABLE:
	    (void) fprintf(fd, " %s disabled",
			   cp->config_data ? "" : "not");
	    break;

	default:
	    assert(FALSE);
	    break;
	}
    } CONFIG_LIST_END(cp, list) ;
}

static void
igmp_dump __PF2(tp, task *,
	        fd, FILE *)
{
    register if_addr *ifap;

    if (igmp_int_policy) {
	(void) fprintf(fd, "\tInterface policy:\n");
	control_interface_dump(fd, 2, igmp_int_policy, igmp_int_dump);
    }

    IF_ADDR(ifap) {
	struct group_list *gp;
	struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_IGMP];
	struct group_list *list =  (struct group_list *) ifap->igmp_if_group_list;
	if (BIT_TEST(ips->ips_state, IFPS_DR_STATUS)) {
	    (void) fprintf(fd, "\n\tLocal Group Database for Interface %A(%s)\n",
			   ifap->ifa_addr,
			   ifap->ifa_link->ifl_name);
		fprintf(fd, "\t\tGroup           Last Reported By  Refreshed\n");
	    GROUP_LIST(gp, list) {
		fprintf(fd, "\t\t%-15A %-15A   %u seconds ago\n",
			sockbuild_in(0, gp->group_addr.s_addr),
			sockbuild_in(0, gp->last_addr.s_addr),
			time_sec - gp->refresh_time);
	    } GROUP_LIST_END(gp, list) ;
	}
    } IF_ADDR_END(ifap) ;

    (void) fprintf(fd, "\n");
}


/*
 *	Initialize static variables
 */
void
igmp_var_init()
{
	BIT_RESET(igmp_config_status, IGMP_ENABLED);
	igmp_default_queryinterval = 125;
	igmp_default_timeoutinterval = 270;	/* 2*(query + 10) */

	if (!igmp_all_hosts)
	    igmp_all_hosts = sockdup(sockbuild_in(0, htonl(IGMP_ALL_HOSTS)));
}


/*
 * initialize IGMP socket and IGMP task
 */

static int igmp_mrouting_protos = 0;
static int igmp_assert_count = 0;

/*ARGSUSED*/
void
igmp_init()
{
    if (BIT_TEST(igmp_current_status, IGMP_ENABLED)) {
	if (BIT_TEST(igmp_config_status, IGMP_ENABLED)) {
	/*
	 * was enabled before and still is now
	 *  - reconfig handled above
	 */

	    trace_inherit_global(igmp_trace_options, igmp_trace_types, (flag_t) 0);
	} else {
	/*
	 * was enabled before but isn't anymore
	 *  - cleanup and terminate igmp task
	 */

	    if (igmp_task) {
		igmp_terminate(igmp_task);

		igmp_task = (task *) 0;
	    }
	}
    } else {
	if (BIT_TEST(igmp_config_status, IGMP_ENABLED)) {
	/*
	 * wasn't enabled before but is now
	 *  - start igmp task
	 */

	    igmp_mrouting_protos = 0;
	    igmp_assert_count = 0;
	    trace_inherit_global(igmp_trace_options, igmp_trace_types, (flag_t) 0);
	    if (!igmp_task) {
		igmp_timer_query = (task_timer *) 0;
		igmp_task = task_alloc("IGMP",
				      TASKPRI_IGMP,
				      igmp_trace_options);

		igmp_task->task_proto = IPPROTO_IGMP;
		igmp_task->task_rtproto = RTPROTO_IGMP;
		task_set_cleanup(igmp_task, igmp_cleanup);
		task_set_dump(igmp_task, igmp_dump);
		task_set_ifachange(igmp_task, igmp_ifachange);
		task_set_recv(igmp_task, igmp_recv);
		task_set_reinit(igmp_task, igmp_reinit);
		task_set_terminate(igmp_task, igmp_terminate);

		if ((igmp_task->task_socket = task_get_socket(igmp_task, AF_INET, SOCK_RAW, IPPROTO_IGMP)) < 0) {
		    task_quit(errno);
		}
		if (!task_create(igmp_task)) {
		    task_quit(EINVAL);
		}

		if (task_set_option(igmp_task,
				    TASKOPTION_RECVBUF,
				    task_maxpacket) < 0) {
		    task_quit(errno);
		}

		if (task_set_option(igmp_task,
				    TASKOPTION_NONBLOCKING,
				    (caddr_t) TRUE) < 0) {
		    task_quit(errno);
		}

		/* Disable reception of our own packets */
		if (task_set_option(igmp_task,
				    TASKOPTION_MULTI_LOOP,
				    FALSE) < 0) {
		    task_quit(errno);
		}

#ifdef	KRT_IPMULTI_RTSOCK
		    /*
		     * Since the 3.3 release assumes we will include the
		     * IP header, we include it for the gated kernel as
		     * well so the code is more similar.
		     */
		if (task_set_option(igmp_task,
				    TASKOPTION_IPHEADER_INC,
				    (caddr_t) TRUE) < 0) {
		    task_quit(errno);
		}
#endif	/* KRT_IPMULTI_RTSOCK */

		igmp_register_recv( IGMP_MEMBERSHIP_QUERY,
			igmp_recv_membership_query );

		igmp_register_recv( IGMP_MEMBERSHIP_REPORT,
			igmp_recv_membership_report ); 

		igmp_register_recv( IGMP_NEW_MEMBERSHIP_REPORT,
			igmp_recv_membership_report ); 

		igmp_register_recv( IGMP_MEMBERSHIP_LEAVE,
			igmp_recv_membership_leave ); 

		igmp_register_recv( IGMP_CISCO_TRACE,
			igmp_recv_trace ); 

		igmp_register_recv( IGMP_MTRACE_REQUEST,
			igmp_recv_trace ); 

		igmp_register_recv( IGMP_MTRACE_RESPONSE,
			igmp_recv_trace ); 

		group_block_index = task_block_init(sizeof (struct group_list),
			"igmp_group_list");
		change_block_index = task_block_init(sizeof(igmp_change_notify),
			"igmp_change_notify");

	    }
    	}
    }
    igmp_current_status = igmp_config_status;
}

void
igmp_enable_asserts  __PF0(void)
{
#ifdef	MRT_ASSERT
    if (igmp_assert_count++ == 0 &&
	igmp_task->task_socket != -1) {
	trace_tp(igmp_task,
		 TR_TASK,
		 0,
		 ("igmp_enable_asserts: Enabling Assert Processing in the kernel"));
	if (task_set_option(igmp_task, TASKOPTION_ASSERT, TRUE) < 0) {
	    task_quit(errno);
	}
    }
#endif	/* MRT_ASSERT */
}

void
igmp_disable_asserts  __PF0(void)
{
#ifdef	MRT_ASSERT
    if (--igmp_assert_count == 0 &&
	igmp_task->task_socket != -1) {
	trace_tp(igmp_task,
		 TR_TASK,
		 0,
		 ("igmp_disable_asserts: Disabling Assert Processing in the kernel"));
	if (task_set_option(igmp_task, TASKOPTION_ASSERT, FALSE) < 0) {
	    task_quit(errno);
	}
    }
#endif	/* MRT_ASSERT */
}

void
igmp_enable_mrouting __PF0(void)
{
    if (igmp_mrouting_protos++ == 0 && igmp_task->task_socket != -1) {
	trace_tp(igmp_task,
		 TR_TASK,
		 0,
		 ("igmp_enable_mrouting: Enabling Multicast Routing in the kernel"));
	if (task_set_option(igmp_task, TASKOPTION_MULTI_ROUTE, 1) < 0) {
	    trace_log_tf(igmp_trace_options,
			 0,
			 LOG_WARNING,
			 ("igmp_enable_mrouting: %s", strerror(errno)));
	}
    }
}

void
igmp_disable_mrouting __PF0(void)
{
    if (--igmp_mrouting_protos == 0 && igmp_task->task_socket != -1) {
	trace_tp(igmp_task,
		 TR_TASK,
		 0,
		 ("igmp_disable_mrouting: Disabling Multicast Routing in the kernel"));
	if (task_set_option(igmp_task, TASKOPTION_MULTI_ROUTE, 0) < 0) {
	    trace_log_tf(igmp_trace_options,
			 0,
			 LOG_WARNING,
			 ("igmp_disable_mrouting: %s", strerror(errno)));
	}
    }
}

#ifdef	KRT_IPMULTI_TTL0

static vifi_t vifnum = 0;

void
igmp_add_vif  __PF4(ifap, if_addr *,
		    remote, sockaddr_un *,
		    threshold, u_int32,
		    rate, u_int32)
{
    struct vifctl vc;

    trace_tp(igmp_task,
	     TR_STATE,
	     0,
	     ("igmp_add_vif: Adding Virtual Interface %A(%s)",
	      ifap->ifa_addr,
	      ifap->ifa_link->ifl_name));

    vc.vifc_vifi = (vifi_t) vifnum++;
    vc.vifc_flags = remote ? VIFF_TUNNEL : (u_int8) 0;
    vc.vifc_threshold = (u_int8) threshold;
    vc.vifc_rate_limit = rate;
    vc.vifc_lcl_addr.s_addr = sock2ip(ifap->ifa_addr_local);
    vc.vifc_rmt_addr.s_addr = remote ? sock2ip(remote) : 0;

    ifap->ifa_vif = vc.vifc_vifi;

    if (task_set_option(igmp_task, TASKOPTION_ADD_VIF, &vc) < 0) {
	trace_log_tf(igmp_trace_options,
		     0,
		     LOG_WARNING,
		     ("igmp_add_vif: %s", strerror(errno)));
    }
}

void
igmp_del_vif  __PF1(ifap, if_addr *)
{
    trace_tp(igmp_task,
	     TR_STATE,
	     0,
	     ("igmp_del_vif: Deleting Virtual Interface %A(%s)",
	      ifap->ifa_addr,
	      ifap->ifa_link->ifl_name));

    if (task_set_option(igmp_task, TASKOPTION_DEL_VIF, ifap) < 0) {
	trace_log_tf(igmp_trace_options,
		     0,
		     LOG_WARNING,
		     ("igmp_del_vif: %s", strerror(errno)));
    }
}

task *
igmp_lookup_task  __PF0(void)
{
    return igmp_task;
}

#endif	/* KRT_IPMULTI_TTL0 */

