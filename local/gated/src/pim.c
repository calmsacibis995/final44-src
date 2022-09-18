/*
 *  $Id: pim.c,v 2.9 1995/03/10 04:32:42 pusateri Exp pusateri $
 */

/*%Copyright%*/

#define	INCLUDE_IF

#include "include.h"
#include "inet.h"
#include "inet_multi.h"
#include "krt_ipmulti.h"
#include "targets.h"
#include "igmp.h"
#include "pim.h"

PROTOTYPE(pim_dr_election, static void, (if_addr *));
PROTOTYPE(pim_router_refresh, static void, (if_addr *, sockaddr_un *, int, time_t));
PROTOTYPE(pim_router_purge, static void, (if_addr *));
PROTOTYPE(pim_router_timeout, static void, (task_timer *, time_t));
PROTOTYPE(pim_graft_timeout, static void, (task_timer *, time_t));
PROTOTYPE(pim_join_timeout, static void, (task_timer *, time_t));
PROTOTYPE(pim_assert_timeout, static void, (task_timer *, time_t));
PROTOTYPE(pim_refresh_router_timer, static void, (if_addr *, time_t));
PROTOTYPE(pim_group_change, void, (int, if_addr *, u_int32));
PROTOTYPE(pim_send_graft, static void, (if_addr *, u_int32));
PROTOTYPE(pim_send_join_prune_graft, static void, (int, u_int32));
PROTOTYPE(pim_send_prune, static int, (mfc *));
PROTOTYPE(pim_queue_prune, static void, (mfc *, prune_list *));
PROTOTYPE(pim_clean_mfc, static void, (mfc *));
PROTOTYPE(pim_set_mfc_timer, static void, (mfc *, time_t));
PROTOTYPE(pim_reset_mfc_timer, static void, (mfc *));
PROTOTYPE(pim_mfc_add_ifap, static void, (mfc *, caddr_t));
PROTOTYPE(pim_mfc_delete_ifap, static void, (mfc *, caddr_t));
PROTOTYPE(pim_recv_join_prune, static void, (if_addr *, struct pimhdr *, int));
PROTOTYPE(pim_recv_graft, static void, (if_addr *, struct pimhdr *, int));
PROTOTYPE(pim_recv_graft_ack, static void, (if_addr *, struct pimhdr *, int));
PROTOTYPE(pim_recv_assert, static void, (if_addr *, struct pimhdr *, int));
PROTOTYPE(pim_recv_query, static void, (if_addr *, struct pimhdr *, int));

static task *pim_task = (task *) 0;
static task_timer *pim_timer_query;	/* to send Router Queries */
#define	PIM_QUERY_OFFSET	1	/* don't send initial query for 1 sec */

int pim_current_status = 0;		/* whether PIM is currently on */
int pim_config_status = 0;		/* whether PIM is on in new config */

sockaddr_un *igmp_all_routers = 0;	/* All Routers Group - 224.0.0.2 */

/*
 * distinguish different message types for pim_send_join_prune_graft()
 */

#define	PIM_MSG_JOIN	0
#define	PIM_MSG_PRUNE	1
#define	PIM_MSG_GRAFT	2

/*
 * PIM Router list (per interface)
 */

static block_t pim_router_block_index;

typedef struct _router_list {
    struct _router_list *dr_forw, *dr_back;	/* DR list */
    struct _router_list *tq_forw, *tq_back;	/* timer queue list */
    sockaddr_un *router_addr;		/* Router address */
    int mode;				/* Sparse or dense */
    time_t hold_time;			/* time to keep router active */
    time_t refresh_time;		/* Time of last refresh */
} router_list;

#define IFPS_NOT_LEAF		IFPS_KEEP1
#define IFPS_PIM_MODE		IFPS_POLICY1
						/* PIM router list (per intf) */
#define pim_if_router_list	ifa_ps[RTPROTO_PIM].ips_datas[0]
#define pim_if_timer_timeout	ifa_ps[RTPROTO_PIM].ips_datas[1]
/*
 * Used to scan the pim router list
 */

#define	ROUTER_DR_LIST(gp, list)	{ for (gp = (list)->dr_forw; gp != list; gp = gp->dr_forw)
#define ROUTER_DR_LIST_END(gp, list)	if (gp == list) gp = (router_list *) 0; }
#define	ROUTER_TQ_LIST(gp, list)	{ for (gp = (list)->tq_forw; gp != list; gp = gp->tq_forw)
#define ROUTER_TQ_LIST_END(gp, list)	if (gp == list) gp = (router_list *) 0; }

#define ROUTER_TQ_ENQ(elem, pred) { \
    register router_list *Xe = elem; \
    register router_list *Xp = pred; \
    Xp->tq_forw = (Xe->tq_forw = (Xe->tq_back = Xp)->tq_forw)->tq_back = Xe; \
}

#define ROUTER_TQ_DEQ(elem) { \
    register router_list *Xe = elem; \
    (Xe->tq_back->tq_forw = Xe->tq_forw)->tq_back = Xe->tq_back; \
}

#define ROUTER_DR_ENQ(elem, pred) { \
    register router_list *Xe = elem; \
    register router_list *Xp = pred; \
    Xp->dr_forw = (Xe->dr_forw = (Xe->dr_back = Xp)->dr_forw)->dr_back = Xe; \
}

#define ROUTER_DR_DEQ(elem) { \
    register router_list *Xe = elem; \
    (Xe->dr_back->dr_forw = Xe->dr_forw)->dr_back = Xe->dr_back; \
}

/*
 * Reverse Path Forwarding Lists for forming join/prune/graft messages
 */

typedef struct _rpf_list {
    struct	_rpf_list *forw, *back;
    u_int32	rpf_addr;
    u_int32	src_addr;
    if_addr	*ifap;
} rpf_list;

static rpf_list rpf_head =
	{ &rpf_head, &rpf_head };

static block_t pim_rpf_block_index;

#define	RPF_LIST(gp, list)	{ for (gp = (list)->forw; gp != list; gp = gp->forw)
#define RPF_LIST_END(gp, list)	if (gp == list) gp = (rpf_list *) 0; }

/*
 * Graft Ack List for timing out graft acks and retransmitting graft msgs
 */

typedef struct _graft_list {
    struct	_graft_list *forw, *back;
    u_int32	graft_group;
    time_t	graft_time;
    if_addr	*graft_ifap;
    sockaddr_un	*graft_dst;
} graft_list;

static graft_list graft_head =
	{ &graft_head, &graft_head };

static block_t pim_graft_block_index;

static task_timer *pim_timer_graft;	/* for timing out graft acks */

#define	GRAFT_LIST(gp, list)	{ for (gp = (list)->forw; gp != list; gp = gp->forw)
#define GRAFT_LIST_END(gp, list)	if (gp == list) gp = (graft_list *) 0; }

/*
 * Prune List for sending and timing out prunes
 */

static prune_list prune_head =
	{ &prune_head, &prune_head };

static block_t pim_prune_block_index;

static task_timer *pim_timer_prune;	/* for timing out prunes */

/*
 * Join List for the join delay timer
 */

typedef struct _join_list {
    struct	_join_list *forw, *back;
    mfc		*mfcp;
    if_addr	*ifap;
    time_t	join_time;
} join_list;

static join_list join_head =
	{ &join_head, &join_head };

static block_t pim_join_block_index;

static task_timer *pim_timer_join;	/* for timing out join requests */

#define	JOIN_LIST(gp, list)	{ for (gp = (list)->forw; gp != list; gp = gp->forw)
#define JOIN_LIST_END(gp, list)	if (gp == list) gp = (join_list *) 0; }

/*
 *  Assert message queue
 */

static assert_list assert_head =
	{ &assert_head, &assert_head };

static block_t pim_assert_block_index;

static task_timer *pim_timer_assert;

/*
 * MFC timer queue
 */

typedef struct _mfc_list {
    struct	_mfc_list *forw, *back;
    time_t	mfc_timeout;
    mfc		*mfcp;
} mfc_list;

static mfc_list mfc_head =
	{ &mfc_head, &mfc_head };

static block_t pim_mfc_block_index;

static task_timer *pim_timer_mfc;	/* for purging inactive mfc entries */

#define	PIM_MFC_LIST(gp, list)	{ for (gp = (list)->forw; gp != list; gp = gp->forw)
#define PIM_MFC_LIST_END(gp, list)	if (gp == list) gp = (mfc_list *) 0; }


/*
 * protocol defaults
 */

time_t pim_default_queryinterval;
time_t pim_default_routertimeout;
time_t pim_default_prunetimeout;
time_t pim_default_inactivitytimeout;
time_t pim_default_graftacktimeout;

/*
 * array of preferences for pim asserts
 */

static pref_t pim_preference[RTPROTO_MAX];

/*
 * configuration interface lists
 */

adv_entry *pim_int_policy = 0;		/* PIM control info */

/*
 * tracing details
 */

trace *pim_trace_options = { 0 };	/* Trace flags */

static const flag_t pim_trace_masks[] = {
    TR_PIM_DETAIL_ROUTER_QUERY,		/* 0 - Router Query */
    TR_PIM_DETAIL_REGISTER,		/* 1 - REGISTER */
    TR_PIM_DETAIL_REGISTER_STOP,	/* 2 - REGISTER_STOP */
    TR_PIM_DETAIL_JOIN_PRUNE,		/* 3 - JOIN_PRUNE */
    TR_PIM_DETAIL_RP_REACHABILITY,	/* 4 - RP_REACHABILITY */
    TR_PIM_DETAIL_ASSERT,		/* 5 - ASSERT */
    TR_PIM_DETAIL_GRAFT,		/* 6 - GRAFT */
    TR_PIM_DETAIL_GRAFT_ACK,		/* 7 - GRAFT_ACK */
    0
} ;

const bits pim_trace_types[] = {
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
    { TR_DETAIL_2,	"detail register" },
    { TR_DETAIL_SEND_2,	"detail send register" },
    { TR_DETAIL_RECV_2,	"detail recv register" },
    { TR_PACKET_2,	"register" },
    { TR_PACKET_SEND_2,	"send register" },
    { TR_PACKET_RECV_2,	"recv register" },
    { TR_DETAIL_3,	"detail join" },
    { TR_DETAIL_SEND_3,	"detail send join" },
    { TR_DETAIL_RECV_3,	"detail recv join" },
    { TR_PACKET_3,	"join" },
    { TR_PACKET_SEND_3,	"send join" },
    { TR_PACKET_RECV_3,	"recv join" },
    { TR_DETAIL_4,	"detail assert" },
    { TR_DETAIL_SEND_4,	"detail send assert" },
    { TR_DETAIL_RECV_4,	"detail recv assert" },
    { TR_PACKET_4,	"assert" },
    { TR_PACKET_SEND_4,	"send assert" },
    { TR_PACKET_RECV_4,	"recv assert" },
    { TR_DETAIL_5,	"detail graft" },
    { TR_DETAIL_SEND_5,	"detail send graft" },
    { TR_DETAIL_RECV_5,	"detail recv graft" },
    { TR_PACKET_5,	"graft" },
    { TR_PACKET_SEND_5,	"send graft" },
    { TR_PACKET_RECV_5,	"recv graft" },
    { 0, NULL }
};

/*
 *	Trace PIM packets
 */
static void
pim_trace __PF7(trp, trace *,
		dir, int,
    		ifap, if_addr *,
		who, sockaddr_un *,
		msg, register struct pimhdr *,
		size, register size_t,
    		detail, int)
{
    u_int32 src_addr;

    if (dir) {
	/* Trace packet transmission */

	tracef("PIM %sSENT %A -> %#A ",
	       dir > 0 ? "" : "*NOT* ",
	       ifap ? ifap->ifa_addr_local : sockbuild_str(""),
	       who);
    } else {
	/* Trace packet reception */
	tracef("PIM RECV %#A ",
	       who);
	if (task_recv_dstaddr) {
	    /* Some systems report the destination address */
	    tracef("-> %A ", task_recv_dstaddr);
	}
    }
    switch (msg->igmp_code) {
	case PIM_ROUTER_QUERY:
	{
		struct pimquery *pq = (struct pimquery *) (msg + 1);

		tracef("Router Query: %s Mode ",
		       ntohs(pq->pim_mode) ? "Sparse" : "Dense");
		if (detail) {
		    tracef("Vers %d Holdtime %d Len %d",
			   ntohl(msg->pim_version) >> 28,
			   ntohs(pq->pim_holdtime),
			   size);
		}
	}
		break;
	case PIM_REGISTER:
		tracef("Register: ");
		break;
	case PIM_REGISTER_STOP:
		tracef("Register-Stop: ");
		break;
	case PIM_RP_REACHABILITY:
		tracef("RP-Reachability: ");
		break;
	case PIM_ASSERT:
	{
		struct pimassert *pas = (struct pimassert *) (msg + 1);
		tracef("Assert: Group %A Mask %A Source %A ",
		       sockbuild_in(0, pas->group_addr),
		       sockbuild_in(0, pas->group_mask),
		       sockbuild_in(0, pas->src_addr));
		if (detail) {
		    tracef("Vers %d RP %d Pref %u Metric %u Len %d",
			   ntohl(msg->pim_version) >> 28,
			   BIT_TEST(ntohl(pas->preference), PIM_ASSERT_RPBIT),
			   ntohl(pas->preference) & 0x7fffffff,
			   ntohl(pas->metric),
			   size);
		}
		break;
	}
	case PIM_JOIN_PRUNE:
	case PIM_GRAFT:
	case PIM_GRAFT_ACK:
	{
		int i, j;
		struct pimjoinhdr *pjh = (struct pimjoinhdr *) (msg + 1);
		struct pimgroup *pg = (struct pimgroup *) (pjh + 1);

		switch(msg->igmp_code) {
		    case PIM_JOIN_PRUNE:
			tracef("Join/Prune: ");
			break;
		    case PIM_GRAFT:
			tracef("Graft: ");
			break;
		    case PIM_GRAFT_ACK:
			tracef("Graft-Ack: ");
			break;
		}
		if (detail) {
		    tracef("Vers %d Upstream %A Holdtime %u MLen %d ALen %d Groups %d ",
			   ntohl(msg->pim_version) >> 28,
			   sockbuild_in(0, pjh->rpf_addr),
			   ntohs(pjh->holdtime),
			   pjh->maddr_len,
			   pjh->addr_len,
			   pjh->num_groups);

		    trace_only_tf(trp,
				  0,
				  (NULL));
		    for (i = 0; i < pjh->num_groups; i++) {
			caddr_t cp = (caddr_t) &pg->source_data[0];

			tracef("Group %A Mask %A ",
			       sockbuild_in(0, pg->group_addr),
			       sockbuild_in(0, pg->group_mask));
			trace_only_tf(trp,
				      0,
				      (NULL));
			if (pg->num_join) {
			    tracef("Join Sources: %d", ntohs(pg->num_join));
			    trace_only_tf(trp,
					  0,
					  (NULL));
			    for (j = 0; j < ntohs(pg->num_join); j++) {
				u_int8 high_flags = (u_int8) *cp++;
				u_int8 low_flags = (u_int8) *cp++;
				bcopy(cp, (caddr_t) &src_addr, sizeof(u_int32));
				tracef("Source %A Masklen %d flags (",
				   sockbuild_in(0, src_addr),
				   low_flags & 0x3f);
				if (BIT_TEST(high_flags, PIM_SOURCE_S_BIT))
				    tracef("S");
				if (BIT_TEST(high_flags, PIM_SOURCE_W_BIT))
				    tracef("W");
				if (BIT_TEST(high_flags, PIM_SOURCE_R_BIT))
				    tracef("R");
				cp += sizeof(u_int32);
				tracef(")");
				trace_only_tf(trp,
					      0,
					      (NULL));
			    }
			}
			if (pg->num_prune) {
			    tracef("Prune Sources: %d", ntohs(pg->num_prune));
			    trace_only_tf(trp,
					  0,
					  (NULL));
			    for (j = 0; j < ntohs(pg->num_prune); j++) {
				u_int8 high_flags = (u_int8) *cp++;
				u_int8 low_flags = (u_int8) *cp++;

				bcopy(cp, (caddr_t) &src_addr, sizeof(u_int32));
				tracef("Source %A Masklen %d flags (",
				   sockbuild_in(0, src_addr),
				   low_flags & 0x3f);
				if (BIT_TEST(high_flags, PIM_SOURCE_S_BIT))
				    tracef("S");
				if (BIT_TEST(high_flags, PIM_SOURCE_W_BIT))
				    tracef("W");
				if (BIT_TEST(high_flags, PIM_SOURCE_R_BIT))
				    tracef("R");
				cp += sizeof(u_int32);
				tracef(")");
				trace_only_tf(trp,
					      0,
					      (NULL));
			    }
			}
			pg = (struct pimgroup *) cp;
		    }
		} else {
		    tracef("Vers %d Upstream %A Groups %d",
			   ntohl(msg->pim_version) >> 28,
			   sockbuild_in(0, pjh->rpf_addr),
			   pjh->num_groups);
		}
		break;
	}
    }

    trace_only_tf(trp, 0, (NULL));
}

/*
 * Send a PIM Router Query to the specified interface.
 *
 */

static void
pim_send_query	 __PF1(ifap, if_addr *)
{
    int rc;
    size_t len;
    struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_PIM];
    struct ip *ip = task_get_send_buffer(struct ip *);
    struct pimhdr *pkt = (struct pimhdr *) (ip+1);
    struct pimquery *pq = (struct pimquery *) (pkt + 1);

    pkt->igmp_type = IGMP_PROTO_PIM;
    pkt->igmp_code = PIM_ROUTER_QUERY;
    pkt->pim_version = htonl(PIM_VERSION);

	/*
	 * Bit set for Sparse Mode, Otherwise Dense Mode
	 */
    if (BIT_TEST(ips->ips_state,IFPS_PIM_MODE)) {
	pq->pim_mode = htons(PIM_MODE_SPARSE << 12);
    } else {
	pq->pim_mode = htons(PIM_MODE_DENSE << 12);
    }
    pq->pim_holdtime = htons(pim_default_routertimeout);

    /* Calculate packet checksum */
    len = sizeof(struct pimhdr) + sizeof(struct pimquery);
    pkt->igmp_cksum = 0;
    pkt->igmp_cksum = inet_cksum((void_t) pkt, len);

    rc = igmp_send(ifap, ip, len + sizeof(struct ip), igmp_all_routers, TRUE);

    /* Should we trace this packet? */

    if (TRACE_PACKET_SEND_TP(pim_task,
			     pkt->igmp_code,
			     PIM_MAX_TYPE,
			     pim_trace_masks)) {

	pim_trace(pim_task->task_trace,
		  rc,
		  ifap,
		  igmp_all_routers,
		  pkt,
		  len,
		  TRACE_DETAIL_SEND_TP(pim_task,
				       pkt->igmp_code,
				       PIM_MAX_TYPE,
				       pim_trace_masks));
    }
}

/*ARGSUSED*/
static void
pim_graft_timeout  __PF2(tip, task_timer *,
			 interval, time_t)
{
    graft_list	*lp, *aged;
    group_node	*gp;

    lp = graft_head.forw;
    while(lp != &graft_head &&
	   lp->graft_time <= time_sec) {

	trace_tp(pim_task,
		 TR_TIMER,
		 0,
		 ("pim_graft_timeout: Graft sent Upstream to %A for Group %A timed out before acknowledged",
		  lp->graft_dst,
		  sockbuild_in(0, lp->graft_group)));

	gp = mfc_locate_group(lp->graft_group);
	assert(gp);
	gp->graft_pending = 0;
	pim_send_graft(lp->graft_ifap, lp->graft_group);

	aged = lp;
	lp = lp->forw;
	REMQUE(aged);
	task_block_free(pim_graft_block_index, (void_t) aged);
    }
    if (graft_head.forw != &graft_head) {
	task_timer_set(pim_timer_graft,
		       (time_t) 0,
		       graft_head.forw->graft_time - time_sec);
    }
}

static void
pim_graft_add  __PF3(ifap, if_addr *,
		     group, u_int32,
		     dst, sockaddr_un *)
{
    graft_list *new = (graft_list *) task_block_alloc(pim_graft_block_index);
	/*
	 * Insert at end of timer queue
	 */
    new->graft_group = group;
    new->graft_ifap = ifap;
    new->graft_time = time_sec + pim_default_graftacktimeout;
    new->graft_dst = dst;

    INSQUE(new, graft_head.back);

	    /* if no timer running, create one */
    if (!pim_timer_graft) {
	pim_timer_graft = task_timer_create(pim_task,
					     "GraftAck",
					     (flag_t) 0,
					     (time_t) 0,
					     pim_default_graftacktimeout,
					     pim_graft_timeout,
					     (void_t) 0);
    }
	    /* if timer currently inactive, reactivate */
    else if (BIT_TEST(pim_timer_graft->task_timer_flags, TIMERF_INACTIVE)) {
	task_timer_set(pim_timer_graft,
		       (time_t) 0,
		       pim_default_graftacktimeout);
    }
}

/* ARGSUSED */
static void
pim_scan_mfc_rpf  __PF2(mfcp, mfc *,
			data, caddr_t)
{
    router_list *list = (router_list *) mfcp->upstream_ifap->pim_if_router_list;
    router_list *lp;
    rpf_list *rp, *new;
    upstream *up;

    new = (rpf_list *) task_block_alloc(pim_rpf_block_index);
    new->src_addr = mfcp->mfc_src;
    new->ifap = mfcp->upstream_ifap;
	/*
	 * Check if we received an assert,
	 * if so, grafts, prunes, and joins go to the winner.
	 */
    if (mfcp->rpf_addr) {
	new->rpf_addr = mfcp->rpf_addr;
    } else {
	    /*
	     * Could check to make sure upstream interfaces still
	     * match, but we'll do this later.
	     */
	up = krt_locate_upstream(sockbuild_in(0, mfcp->mfc_src),
				 IPMULTI_PROTO_PIM);
	new->rpf_addr = up->nbr->in.gin_addr.s_addr;
    }

	/*
	 * Next look in the pim router list to see if this upstream
	 * neighbor is configured for Dense or Sparse Mode.
	 * If Dense mode, insert it in the list,
	 * If Sparse mode, ignore it for now.
	 */
    ROUTER_DR_LIST(lp, list) {
	if (sock2ip(lp->router_addr) == new->rpf_addr) {
	    if(lp->mode == PIM_MODE_DENSE) {
		rp = rpf_head.forw;
		while(rp != &rpf_head &&
		      new->rpf_addr < rp->rpf_addr) {
		    rp = rp->forw;
		}
		if (rp == &rpf_head) {
		    INSQUE(new, rp->back);
		} else {
		    INSQUE(new, rp);
		}
	    }
	    return;
	}
    } ROUTER_DR_LIST_END(lp, list);
	/*
	 * if we got this far, then we never found the upstream
	 * pim router. This means the upstream router is not
	 * sending pim queries. Log it and continue.
	 */
    trace_log_tf(pim_trace_options,
		 0,
		 LOG_WARNING,
		 ("pim_scan_mfc_rpf: Upstream router %A not running PIM",
		  sockbuild_in(0, new->rpf_addr)));

    task_block_free(pim_rpf_block_index, (void_t) new);
}

static void
pim_rpf_free  __PF0(void)
{
    rpf_list	*rp, *old_rp;

	/*
	 * Free up rpf list elements
	 */

    rp = rpf_head.forw;
    while(rp != &rpf_head) {
	old_rp = rp;
	rp = rp->forw;
	REMQUE(old_rp);
	task_block_free(pim_rpf_block_index, (void_t) old_rp);
    }
}

/*
 * Send a PIM Assert out the specified interface
 */

static void
pim_send_assert	 __PF3(ifap, if_addr *,
		       group, u_int32,
		       source, u_int32)
{
    int rc;
    size_t len;
    upstream *up = krt_locate_upstream(sockbuild_in(0, source),
				       IPMULTI_PROTO_PIM);
    struct ip *ip = task_get_send_buffer(struct ip *);
    struct pimhdr *pkt = (struct pimhdr *) (ip+1);
    struct pimassert *pas = (struct pimassert *) (pkt + 1);

    pkt->igmp_type = IGMP_PROTO_PIM;
    pkt->igmp_code = PIM_ASSERT;
    pkt->pim_version = htonl(PIM_VERSION);

    pas->group_addr = group;
    pas->group_mask = INADDR_HOSTMASK;
    pas->src_addr = source;
    pas->preference = htonl(pim_preference[up->protocol] & 0x7fffffff);
    pas->metric = htonl(up->metric);

    /* Calculate packet checksum */
    len = sizeof(struct pimhdr) + sizeof(struct pimassert);
    pkt->igmp_cksum = 0;
    pkt->igmp_cksum = inet_cksum((void_t) pkt, len);

    rc = igmp_send(ifap, ip, len + sizeof(struct ip), igmp_all_routers, FALSE);

    /* Should we trace this packet? */

    if (TRACE_PACKET_SEND_TP(pim_task,
			     pkt->igmp_code,
			     PIM_MAX_TYPE,
			     pim_trace_masks)) {

	pim_trace(pim_task->task_trace,
		  rc,
		  ifap,
		  igmp_all_routers,
		  pkt,
		  len,
		  TRACE_DETAIL_SEND_TP(pim_task,
				       pkt->igmp_code,
				       PIM_MAX_TYPE,
				       pim_trace_masks));
    }
}

/*ARGSUSED*/
static void
pim_assert_timeout  __PF2(tip, task_timer *,
			  interval, time_t)
{
    assert_list	*pas, *aged;

    pas = assert_head.forw;
    while(pas != &assert_head && (time_sec >= pas->assert_time)) {
	aged = pas;
	pas = pas->forw;
	REMQUE(aged);

	    /*
	     * If no other asserts received before this timeout,
	     * set the RPF address to be the first assert we
	     * received.
	     */
	    
	aged->mfcp->rpf_addr = aged->rpf_addr;
	aged->mfcp->pim_assert = (assert_list *) 0;
	task_block_free(pim_assert_block_index, (void_t) aged);
    }
    if (assert_head.forw != &assert_head) {
	task_timer_set(pim_timer_assert,
		       (time_t) 0,
		       assert_head.forw->assert_time - time_sec);
    }
}


/*
 * Send a PIM Graft for specified group to the specified interface.
 */

static void
pim_send_graft	 __PF2(join_ifap, if_addr *,
		       group, u_int32)
{
    u_int32	last_rpf;
    rpf_list	*rp;
    group_node	*gp = mfc_locate_group(group);

	/*
	 * Don't want to flood the network with graft messages
	 */
    if (gp->graft_pending) {
	return;
    }

	/*
	 * Only need to send grafts for sources which we already have state
	 * Loop through existing sources and coallate rpf neighbors
	 * This builds the rpf list.
	 */
    
    mfc_source_visit(gp, pim_scan_mfc_rpf, (caddr_t) 0);

    if (rpf_head.forw != &rpf_head) {

	pim_send_join_prune_graft(PIM_MSG_GRAFT, group);
	    /*
	     * Insert each rpf_addr in Graft Ack List and reset timer
	     * if necessary. Only done once per rpf_addr.
	     */
	last_rpf = 0;
	RPF_LIST(rp, &rpf_head) {
		if (rp->rpf_addr != last_rpf) {

		    pim_graft_add(join_ifap, group, sockbuild_in(0, last_rpf));

		    last_rpf = rp->rpf_addr;
		}
	} RPF_LIST_END(rp, &rpf_head);

	    /*
	     * Free up rpf list elements
	     */

	pim_rpf_free();

	gp->graft_pending++;
    }
}

static void
pim_send_join_prune_graft  __PF2(msgtype, int,
				 group, u_int32)
{
    int		rc;
    u_int32	last_rpf;
    size_t	len;
    struct	ip *ip = task_get_send_buffer(struct ip *);
    struct	pimhdr *pkt = (struct pimhdr *) (ip+1);
    struct	pimjoinhdr *pjh = (struct pimjoinhdr *) (pkt + 1);
    struct	pimgroup *pg = (struct pimgroup *) (pjh + 1);
    caddr_t	cp = (caddr_t) &pg->source_data[0];
    if_addr	*ifap = 0;
    rpf_list	*rp;
    sockaddr_un	*dst = 0;

    pkt->igmp_type = IGMP_PROTO_PIM;
    pkt->pim_version = htonl(PIM_VERSION);
    switch (msgtype) {
    case PIM_MSG_JOIN:
    case PIM_MSG_PRUNE:
	pkt->igmp_code = PIM_JOIN_PRUNE;
	break;
    case PIM_MSG_GRAFT:
	pkt->igmp_code = PIM_GRAFT;
	break;
    }

    pjh->reserved = 0;
    pjh->holdtime = htons(pim_default_prunetimeout);
    pjh->reserved2 = 0;
    pjh->maddr_len = sizeof(u_int32);
    pjh->addr_len = sizeof(u_int32);
    pjh->num_groups = 1;

    pg->group_addr = group;
    pg->group_mask = INADDR_HOSTMASK;
    pg->num_join = pg->num_prune = 0;

	/*
	 * Should be at least one rpf entry in the list
	 */
    assert(rpf_head.forw != &rpf_head);

    last_rpf = rpf_head.forw->rpf_addr;
    RPF_LIST(rp, &rpf_head) {

	if (last_rpf == rp->rpf_addr) {
		/*
		 * add source to this message
		 */
	    switch (msgtype) {
	    case PIM_MSG_JOIN:
	    case PIM_MSG_GRAFT:
		pg->num_join++;
		break;
	    case PIM_MSG_PRUNE:
		pg->num_prune++;
		break;
	    }
	    ifap = rp->ifap;

		/*
		 * set high flags in source
		 */
	    *cp = 0;
	    BIT_RESET(*cp++, PIM_SOURCE_S_BIT);

		/*
		 * mask len is lowest 6 bits
		 */
	    *cp = (sizeof(u_int32) * NBBY) & 0x3f;

		/*
		 * set low flags in source
		 */
	    BIT_RESET(*cp, PIM_SOURCE_W_BIT);
	    BIT_RESET(*cp++, PIM_SOURCE_R_BIT);

	    bcopy((caddr_t) &rp->src_addr, cp, sizeof(u_int32));

	    cp += sizeof(u_int32);


	} else {
		/*
		 * send this message and begin new one
		 */
	    pjh->rpf_addr = last_rpf;
	    pg->num_join = htons(pg->num_join);
	    pg->num_prune = htons(pg->num_prune);

	    /* Calculate packet checksum */
	    len = cp - (caddr_t) pkt;
	    pkt->igmp_cksum = 0;
	    pkt->igmp_cksum = inet_cksum((void_t) pkt, len);

	    switch (msgtype) {
	    case PIM_MSG_JOIN:
	    case PIM_MSG_PRUNE:
		dst = igmp_all_routers;
		break;
	    case PIM_MSG_GRAFT:
		dst = sockbuild_in(0, last_rpf);
		break;
	    default:
		assert(0);
	    }
	    if (ifap) {
		rc = igmp_send(ifap, ip, len + sizeof(struct ip), dst, FALSE);

		/* Should we trace this packet? */

		if (TRACE_PACKET_SEND_TP(pim_task,
					 pkt->igmp_code,
					 PIM_MAX_TYPE,
					 pim_trace_masks)) {

		    pim_trace(pim_task->task_trace,
			      rc,
			      ifap,
			      dst,
			      pkt,
			      len,
			      TRACE_DETAIL_SEND_TP(pim_task,
						   pkt->igmp_code,
						   PIM_MAX_TYPE,
						   pim_trace_masks));
		}
	    }
		/*
		 *  now start the next message
		 */
	    switch (msgtype) {
	    case PIM_MSG_JOIN:
	    case PIM_MSG_GRAFT:
		pg->num_join = 1;
		break;
	    case PIM_MSG_PRUNE:
		pg->num_prune = 1;
		break;
	    }
	    last_rpf = rp->rpf_addr;

	    cp = (caddr_t) &pg->source_data[0];
		/*
		 * set high flags in source
		 */
	    *cp = 0;
	    BIT_RESET(*cp++, PIM_SOURCE_S_BIT);

		/*
		 * mask len is lowest 6 bits
		 */
	    *cp = (sizeof(u_int32) * NBBY) & 0x3f;

		/*
		 * set low flags in source
		 */
	    BIT_RESET(*cp, PIM_SOURCE_W_BIT);
	    BIT_RESET(*cp++, PIM_SOURCE_R_BIT);

	    bcopy((caddr_t) &rp->src_addr, cp, sizeof(u_int32));
	    cp += sizeof(u_int32);


	}
    } RPF_LIST_END(rp, &rpf_head);

	/*
	 * send this last (maybe only) graft message
	 */
    pjh->rpf_addr = last_rpf;
    pg->num_join = htons(pg->num_join);
    pg->num_prune = htons(pg->num_prune);

    /* Calculate packet checksum */
    len = cp - (caddr_t) pkt;
    pkt->igmp_cksum = 0;
    pkt->igmp_cksum = inet_cksum((void_t) pkt, len);

    if (ifap) {
	switch (msgtype) {
	case PIM_MSG_JOIN:
	case PIM_MSG_PRUNE:
	    dst = igmp_all_routers;
	    break;
	case PIM_MSG_GRAFT:
	    dst = sockbuild_in(0, last_rpf);
	    break;
	default:
	    assert(0);
	}
	rc = igmp_send(ifap, ip, len + sizeof(struct ip), dst, FALSE);

	/* Should we trace this packet? */

	if (TRACE_PACKET_SEND_TP(pim_task,
				 pkt->igmp_code,
				 PIM_MAX_TYPE,
				 pim_trace_masks)) {

	    pim_trace(pim_task->task_trace,
		      rc,
		      ifap,
		      dst,
		      pkt,
		      len,
		      TRACE_DETAIL_SEND_TP(pim_task,
					   pkt->igmp_code,
					   PIM_MAX_TYPE,
					   pim_trace_masks));
	}
    }
}

static void
pim_router_detect  __PF1(ifap, if_addr *)
{
    int rc = 0;
    struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_PIM];
    router_list *list = (router_list *) ifap->pim_if_router_list;
    router_list *gp;

	/*
	 * List will contain at least our own address. If there is
	 * more than one, other routers exist and it is not a leaf.
	 */
    if (list) {
	gp = list->dr_forw;
	while(gp != list && rc < 2) {
	    rc++;
	    gp = gp->dr_forw;
	}
	rc--;
    }
    if (rc) {
	    /*
	     * If no longer a leaf network, then add interface
	     * to existing forwarding cache entries
	     */
	if (!BIT_TEST(ips->ips_state, IFPS_NOT_LEAF)) {
	    mfc_visit(pim_mfc_add_ifap, (caddr_t) ifap);
	    BIT_SET(ips->ips_state, IFPS_NOT_LEAF);
	}
    } else {
	BIT_RESET(ips->ips_state, IFPS_NOT_LEAF);
    }
}

/*ARGSUSED*/
static void
pim_query_job  __PF2(tip, task_timer *,
		     interval, time_t)
{
    register if_addr *ifap;

    IF_ADDR(ifap) {
	struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_PIM];

	if (BIT_TEST(ifap->ifa_state, IFS_MULTICAST) &&
	    BIT_TEST(ifap->ifa_state, IFS_UP) &&
	    BIT_TEST(ifap->ifa_state, IFS_BROADCAST) &&
	    !BIT_TEST(ips->ips_state, IFPS_NOOUT)) {
	    pim_send_query(ifap);
	}
    } IF_ADDR_END(ifap) ;
}

/*ARGSUSED*/
static void
pim_router_timeout  __PF2(tip, task_timer *,
			  interval, time_t)
{
    if_addr *ifap = (if_addr *)(tip->task_timer_data);
    router_list *gp, *aged;
    router_list *list =  (router_list *) ifap->pim_if_router_list;

	/*
	 * search for routers that aged out
	 * will all be at beginning of list
	 */

    gp = list->tq_forw;
    while(gp != list &&
	   (time_sec - gp->refresh_time) >= gp->hold_time) {
	aged = gp;
	gp = gp->tq_forw;
	ROUTER_TQ_DEQ(aged);
	ROUTER_DR_DEQ(aged);
	trace_tp(pim_task,
		 TR_TIMER,
		 0,
		 ("pim_router_timeout: PIM Router %A on interface %A(%s) timed out.",
		  aged->router_addr,
		  ifap->ifa_addr,
		  ifap->ifa_link->ifl_name));
	task_block_free(pim_router_block_index, (void_t) aged);
    }

    pim_refresh_router_timer(ifap,
	list->tq_forw->hold_time - (time_sec - list->tq_forw->refresh_time));

    pim_dr_election(ifap);
}

static void
pim_commence_query	 __PF1(ifap, if_addr *)
{
    router_list **listp = (router_list **) &ifap->pim_if_router_list;
    router_list *list;

    if (!*listp) {
	list = (router_list *) task_block_alloc(pim_router_block_index);
	list->dr_forw = list;
	list->dr_back = list;
	list->tq_forw = list;
	list->tq_back = list;

	*listp = list;
    }
	    /* if no timer running, create one */
    if (!pim_timer_query) {
	pim_timer_query = task_timer_create(pim_task,
					     "Query",
					     (flag_t) 0,
					     pim_default_queryinterval,
					     PIM_QUERY_OFFSET,
					     pim_query_job,
					     (void_t) 0);
    }
	    /* if timer currently inactive, reactivate */
    else if (BIT_TEST(pim_timer_query->task_timer_flags, TIMERF_INACTIVE)) {
	task_timer_set(pim_timer_query,
		       pim_default_queryinterval,
		       PIM_QUERY_OFFSET);
    }
}

static void
pim_mfc_check_use  __PF1(mfcp, mfc *)
{
    prune_list *new;

    if (mfcp->mfc_lastuse == mfcp->mfc_use) {
	int count = mfcp->ds_count;
	downstream *delete, *dsp = mfcp->ds->forw;

	trace_tp(pim_task,
		 TR_TIMER,
		 0,
		 ("pim_mfc_check_use: MFC inactivity timeout: group %A source %A",
		  sockbuild_in(0, mfcp->mfc_group->group_key),
		  sockbuild_in(0, mfcp->mfc_src)));
	    /*
	     * If there are no downstream interfaces already, just delete it.
	     */

	if (!count) {
	    pim_clean_mfc(mfcp);
	    pim_reset_mfc_timer(mfcp);
	    mfc_source_unlink_unicast(pim_task, mfcp);
	    (void) krt_delete_cache(
			    sockbuild_in(0, mfcp->mfc_group->group_key),
			    sockbuild_in(0, mfcp->mfc_src));
	    mfc_delete_node(mfcp);
	    return;
	}

	    /*
	     * If no longer active, remove all downstream interfaces
	     * from the forwarding cache, and prune the mfc.
	     */

	while (dsp != mfcp->ds) {
	    if (dsp->ds_proto == RTPROTO_PIM) {
		trace_tp(pim_task,
			 TR_ROUTE,
			 0,
			 ("pim_mfc_check_use: PIM removing downstream %A for group %A source %A",
			  dsp->ds_addr,
			  sockbuild_in(0, mfcp->mfc_group->group_key),
			  sockbuild_in(0, mfcp->mfc_src)));
		delete = dsp;
		dsp = dsp->forw;
		REMQUE(delete);
		mfc_free_downstream(delete);
		mfcp->ds_count--;
	    }
	}

	if (count != mfcp->ds_count) {

		/*
		 * If we can send a prune to the upstream rpf neighbor, do so.
		 * Be sure to update the kernel with pruned downstream
		 * interface list.
		 *
		 * If we didn't find anyone to send a prune to, then just
		 * blow the cache entry away. Be sure to take the mfc
		 * out of the mfc timeout queue first.
		 */
	    if (pim_send_prune(mfcp)) {
		new = (prune_list *) task_block_alloc(pim_prune_block_index);
		new->ifap = mfcp->upstream_ifap;
		new->mfcp = mfcp;
		new->pending = FALSE;
		new->holdtime = pim_default_prunetimeout;
		new->prune_time = time_sec + pim_default_prunetimeout;

		krt_update_mfc(mfcp);
		pim_queue_prune(mfcp, new);
	    }
	    else {
		pim_reset_mfc_timer(mfcp);
		mfc_source_unlink_unicast(pim_task, mfcp);
		(void) krt_delete_cache(
				sockbuild_in(0, mfcp->mfc_group->group_key),
				sockbuild_in(0, mfcp->mfc_src));
		mfc_delete_node(mfcp);
	    }
	}
    } else {
	if (BIT_TEST(mfcp->mfc_proto, IPMULTI_BIT(IPMULTI_PROTO_PIM))) {
	    pim_set_mfc_timer(mfcp, pim_default_inactivitytimeout);
	}
    }
}

/*ARGSUSED*/
static void
pim_mfc_timeout  __PF2(tip, task_timer *,
		       interval, time_t)
{
    mfc_list *aged, *mp = mfc_head.forw;

    while(mp != &mfc_head && mp->mfc_timeout <= time_sec) {
	aged = mp;
	mp = mp->forw;
	REMQUE(aged);
	if (krt_request_cache(aged->mfcp, pim_mfc_check_use)) {
	    trace_log_tf(pim_trace_options,
			 0,
			 LOG_WARNING,
			 ("pim_mfc_timeout: check use count failed group %A source %A",
			  sockbuild_in(0, aged->mfcp->mfc_group->group_key),
			  sockbuild_in(0, aged->mfcp->mfc_src)));
	}

	trace_tp(pim_task,
		 TR_TIMER,
		 0,
		 ("pim_mfc_timeout: refreshing MFC: group %A source %A",
		  sockbuild_in(0, aged->mfcp->mfc_group->group_key),
		  sockbuild_in(0, aged->mfcp->mfc_src)));
	task_block_free(pim_mfc_block_index, (void_t) aged);
    }

    if (mfc_head.forw != &mfc_head) {
	task_timer_set(pim_timer_mfc,
		       (time_t) 0,
		       mfc_head.forw->mfc_timeout - time_sec);
    }
}

static void
pim_set_mfc_timer  __PF2(mfcp, mfc *,
			 timeout, time_t)
{
    mfc_list *mp, *new;

    trace_tp(pim_task,
	     TR_TIMER,
	     0,
	     ("pim_set_mfc_timer: adding %d sec timer for MFC: group %A source %A",
	      timeout,
	      sockbuild_in(0, mfcp->mfc_group->group_key),
	      sockbuild_in(0, mfcp->mfc_src)));

    new = (mfc_list *) task_block_alloc(pim_mfc_block_index);
    new->mfc_timeout = time_sec + timeout;
    new->mfcp = mfcp;

    mp = mfc_head.back;
    while (mp != &mfc_head && new->mfc_timeout < mp->mfc_timeout) {
	mp = mp->back;
    }

    INSQUE(new, mp);

    timeout = mfc_head.forw->mfc_timeout - time_sec;
		/*
		 * If no timer running, create one
		 */
    if (!pim_timer_mfc) {
	pim_timer_mfc = task_timer_create(pim_task,
					  "MFCTimeout",
					  (flag_t) 0,
					  (time_t) 0,
					  timeout,
					  pim_mfc_timeout,
					  (void_t) 0);
    } else {
		/*
		 * If new entry now at head of list, restart timer
		 */
	if (mfc_head.forw == new) {
	    task_timer_reset(pim_timer_mfc);
	}
		/*
		 * Or if timer isn't running
		 */
	if (BIT_TEST(pim_timer_mfc->task_timer_flags, TIMERF_INACTIVE)) {
	    task_timer_set(pim_timer_mfc,
			   (time_t) 0,
			   timeout);
	}
    }
}

static void
pim_reset_mfc_timer  __PF1(mfcp, mfc *)
{
    mfc_list *mp;

    trace_tp(pim_task,
	     TR_TIMER,
	     0,
	     ("pim_reset_mfc_timer: removing MFC: group %A source %A",
	      sockbuild_in(0, mfcp->mfc_group->group_key),
	      sockbuild_in(0, mfcp->mfc_src)));

    mp = mfc_head.forw;
    while (mp != &mfc_head && mfcp != mp->mfcp) {
	mp = mp->forw;
    }

    if (mfcp == mp->mfcp) {
	if (mp == mfc_head.forw) {
	    task_timer_reset(pim_timer_mfc);
	}
	REMQUE(mp);
	task_block_free(pim_mfc_block_index, (void_t) mp);
    }

	/*
	 * If timer has been stopped, see if it needs restarted
	 */
    if (mfc_head.forw != &mfc_head &&
	BIT_TEST(pim_timer_mfc->task_timer_flags, TIMERF_INACTIVE)) {

	task_timer_set(pim_timer_mfc,
		       (time_t) 0,
		       mfc_head.forw->mfc_timeout - time_sec);
    }
}


/*
 *	Fill in Multicast Forwarding Cache entry
 */
static void
pim_mfc_request  __PF3(msgtype, int,
		       in_ifap, if_addr *,
		       mfcp, mfc *)
{
    register if_addr *ifap;

    trace_tp(pim_task,
	     TR_ROUTE,
	     0,
	     ("pim_mfc_request: Request for group %A source %A",
	      sockbuild_in(0, mfcp->mfc_group->group_key),
	      sockbuild_in(0, mfcp->mfc_src)));
    if (in_ifap) {
	trace_tp(pim_task,
		 TR_ROUTE,
		 0,
		 ("pim_mfc_request: interface %A(%s)",
		  in_ifap->ifa_addr,
		  in_ifap->ifa_link->ifl_name));
    }

    switch (msgtype) {

    case EADDRNOTAVAIL:

	/*
	 * form outgoing interface list
	 * if not a leaf network, add to list
	 * if is a leaf, then check group membership
	 */

	IF_ADDR(ifap) {
	    int add = 0;
	    struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_PIM];
	    struct group_list *gp;
	    struct group_list *glist = (struct group_list *)
					ifap->igmp_if_group_list;

		    /*
		     * Don't send it out a non-multicast interface,
		     * a sparse mode interface, the loopback,
		     * or the incoming interface
		     */
	    if (!BIT_TEST(ifap->ifa_state, IFS_MULTICAST) ||
		BIT_TEST(ips->ips_state,IFPS_PIM_MODE) ||
		BIT_TEST(ifap->ifa_state, IFS_LOOPBACK) ||
	    	ifap == mfcp->upstream_ifap) 
		    continue;
	    if (!BIT_TEST(ips->ips_state, IFPS_NOT_LEAF)) {
		if (glist) {
		    GROUP_LIST(gp, glist) {
			/*
			 * Has someone requested this group ?
			 */
			if (mfcp->mfc_group->group_key == gp->group_addr.s_addr) {
			    add++;
			    break;
			}
		    } GROUP_LIST_END(gp, glist);
		}
	    } else {
		    /*
		     * There are other routers downstream
		     * Let them decide when to prune
		     */
		add++;
	    }
	    if (add) {
		downstream *dpos, *dp;

		dpos = mfcp->ds->forw;
		while (dpos != mfcp->ds) {
			if (sock2ip(dpos->ds_addr) < sock2ip(ifap->ifa_addr))
				dpos = dpos->forw;
		}

		dp = mfc_alloc_downstream();

		dp->ds_addr = ifap->ifa_addr;
		dp->ds_proto = RTPROTO_PIM;
		dp->ds_ttl = 0;
		dp->ds_flags = 0;
#ifdef	KRT_IPMULTI_TTL0
		dp->ds_ifindex = ifap->ifa_vif;
#else	/* KRT_IPMULTI_TTL0 */
		dp->ds_ifindex = 0;
#endif	/* KRT_IPMULTI_TTL0 */

		    /*
		     * insert in the mfc downstream list
		     */
		INSQUE(dp, dpos->back);

		mfcp->ds_count++;

		    /*
		     * if Sparse Mode, set inactivity timer
		     */

		trace_tp(pim_task,
			 TR_ROUTE,
			 0,
			 ("pim_mfc_request: PIM adding downstream interface %A(%s)",
			  ifap->ifa_addr,
			  ifap->ifa_link->ifl_name));
	    }
	} IF_ADDR_END(ifap) ;
	    /*
	     * flag this mfc as needed by PIM
	     */
	BIT_SET(mfcp->mfc_proto, IPMULTI_BIT(IPMULTI_PROTO_PIM));

	pim_set_mfc_timer(mfcp, pim_default_inactivitytimeout);
	    /*
	     * link mfc to source unicast route to handle
	     * changes to unicast routing in the future
	     */
	mfc_source_link_unicast(pim_task, mfcp);

	break;

    case EADDRINUSE:
	    /*
	     * Duplicate packet on incorrect interface, try and stop it.
	     */
	pim_send_assert(in_ifap, mfcp->mfc_group->group_key, mfcp->mfc_src);
	break;
    }
}

/*
 *	Receive PIM Packets
 */
static void
pim_recv __PF3(ifap, if_addr *,
	       igmp, struct igmp *,
	       pimlen, int)
{
    struct pimhdr *pimhdr = (struct pimhdr *) igmp;

    if (pimlen < sizeof(struct pimhdr)) {
	trace_log_tf(pim_trace_options,
		     0,
		     LOG_WARNING,
		     ("pim_recv: ignoring pim msg: short packet from %A",
		      task_recv_srcaddr));
	return;
    }

    /* Should we trace this packet? */

    if (TRACE_PACKET_RECV_TP(pim_task,
			     pimhdr->igmp_code,
			     PIM_MAX_TYPE,
			     pim_trace_masks)) {

	pim_trace(pim_task->task_trace,
		  FALSE,
		  ifap,
		  task_recv_srcaddr,
		  pimhdr,
		  pimlen,
		  TRACE_DETAIL_RECV_TP(pim_task,
				       pimhdr->igmp_code,
				       PIM_MAX_TYPE,
				       pim_trace_masks));
    }
    pimhdr->pim_version = ntohl(pimhdr->pim_version);

    if (pimhdr->pim_version != PIM_VERSION) {
	trace_log_tf(pim_trace_options,
		     0,
		     LOG_WARNING,
		     ("pim_recv: ignoring pim msg: Bad Version: %d",
		      pimhdr->pim_version >> 28));
	return;
    }
    switch (pimhdr->igmp_code) {
	case PIM_ROUTER_QUERY:

		pim_recv_query(ifap, pimhdr, pimlen);
		break;

	case PIM_REGISTER:
		break;
	case PIM_REGISTER_STOP:
		break;
	case PIM_JOIN_PRUNE:
	
		pim_recv_join_prune(ifap, pimhdr, pimlen);
		break;

	case PIM_RP_REACHABILITY:
		break;
	case PIM_ASSERT:

		pim_recv_assert(ifap, pimhdr, pimlen);
		break;

	case PIM_GRAFT:

		pim_recv_graft(ifap, pimhdr, pimlen);
		break;

	case PIM_GRAFT_ACK:

		pim_recv_graft_ack(ifap, pimhdr, pimlen);
		break;
    }
}


static void
pim_recv_query  __PF3(ifap, if_addr *,
		      pimhdr, struct pimhdr *,
		      pimlen, int)
{
    int mode;
    struct pimquery *pq = (struct pimquery *) (pimhdr + 1);

    if (pimlen < (sizeof(struct pimhdr) + sizeof(struct pimquery))) {
	trace_log_tf(pim_trace_options,
		     0,
		     LOG_WARNING,
		     ("pim_recv: ignoring pim msg: short packet from %A",
		      task_recv_srcaddr));
	return;
    }

    mode = ntohs(pq->pim_mode) >> 12;
	/*
	 * add to router list on this interface
	 * or refresh if it already exists
	 */

    pim_router_refresh(ifap,
		       task_recv_srcaddr,
		       mode,
		       ntohs(pq->pim_holdtime));

	 /*
	  * update leaf status
	  */
    pim_router_detect(ifap);

	 /*
	  * perform Designated Router Election
	  * and update interface status if necessary
	  */
    pim_dr_election(ifap);
}


static void
pim_recv_join_prune  __PF3(ifap, if_addr *,
			   pimhdr, struct pimhdr *,
			   pimlen, int)
{
    int i, j;
    int ours = 0;
    u_int32 src_addr;
    mfc *mfcp;
    prune_list *pp, *new;
    struct pimjoinhdr *pjh = (struct pimjoinhdr *) (pimhdr + 1);
    struct pimgroup *pg = (struct pimgroup *) (pjh + 1);

    pimlen -= sizeof(struct pimjoinhdr);
    if (pimlen < 0) {
	trace_log_tf(pim_trace_options,
		     0,
		     LOG_WARNING,
		     ("pim_recv_join_prune: ignoring pim msg: short packet from %A",
		      task_recv_srcaddr));
	return;
    }

    if (ntohl(pjh->rpf_addr) == sock2ip(ifap->ifa_addr) ||
	ntohl(pjh->rpf_addr) == 0) {
	ours++;
    }
    assert(pjh->maddr_len == sizeof(u_int32));
    assert(pjh->addr_len == sizeof(u_int32));

    for (i = 0; i < pjh->num_groups; i++) {
	caddr_t	cp = (caddr_t) &pg->source_data[0];

	pimlen -= sizeof(u_int32) + 2 * sizeof(u_int16);
	if (pimlen < 0) {
	    trace_log_tf(pim_trace_options,
			 0,
			 LOG_WARNING,
			 ("pim_recv_join_prune: ignoring pim msg: short packet from %A",
			  task_recv_srcaddr));
	    return;
	}

	if (pg->group_mask != INADDR_HOSTMASK) {
	    trace_log_tf(pim_trace_options,
			 0,
			 LOG_WARNING,
			 ("pim_recv_join_prune: aggregation in Join/Prune messages unsupported: Group %A, Mask %A",
			  sockbuild_in(0, pg->group_addr),
			  sockbuild_in(0, pg->group_mask)));
	} else {
	    for (j = 0; j < ntohs(pg->num_join); j++) {

		pimlen -= sizeof(u_int32) + 2 * sizeof(u_int8);
		if (pimlen < 0) {
		    trace_log_tf(pim_trace_options,
				 0,
				 LOG_WARNING,
				 ("pim_recv_join_prune: ignoring pim msg: short packet from %A",
				  task_recv_srcaddr));
		    return;
		}

		    /*
		     * skip over high and low flags in source
		     */
		cp += 2*sizeof(u_int8);

		bcopy(cp, (caddr_t) &src_addr, sizeof(u_int32));

		mfcp = mfc_locate_mfc(sockbuild_in(0, pg->group_addr),
				      sockbuild_in(0, src_addr));
		cp += sizeof(u_int32);

			/* In sparse mode, we would propagate this
			 * join upstream when we didn't have any state
			 * on the (S,G) entry. For now, just ignore.
			 *
			 * If this happens in dense mode, then either
			 * 1. Something is seriously wrong with the
			 *    unicast routing convergence so we can
			 *    just ignore this one and wait for things
			 *    to converge, or
			 * 2. This router was reset and lost state.
			 *    in which case we can just ignore the
			 *    join since all subsequent packets will
			 *    be forwarded until a prune is received.
			 */
		if (!mfcp) {
		    return;
		}
		     /*
		      * if join arrives on the upstream interface
		      * and we have one pending, suppress our join
		      */
		if (mfcp->upstream_ifap == ifap) {
		    join_list *jp;

		    JOIN_LIST(jp, &join_head) {
			if (jp->mfcp == mfcp && jp->ifap == ifap) {
				/*
				 * if at head of list, restart timer
				 */
			    if (jp == join_head.forw) {
				task_timer_reset(pim_timer_join);
			    }
			    REMQUE(jp);
			    if (join_head.forw != &join_head &&
				BIT_TEST(pim_timer_join->task_timer_flags,
					 TIMERF_INACTIVE)) {
				task_timer_set(pim_timer_join,
					       (time_t) 0,
					       join_head.forw->join_time-time_sec);
			    }
			    task_block_free(pim_join_block_index, (void_t) jp);
			    break;
			}
		    } JOIN_LIST_END (jp, &join_head);
		} else if (ours) {
			/*
			 * if join overrides received prune
			 * on downstream interface, then process it.
			 * Otherwise, until we do Sparse Mode,
			 * just ignore it
			 */
		    pp = mfcp->prune_down.if_forw;
		    while(pp != &mfcp->prune_down) {
			if (pp->mfcp == mfcp && pp->ifap == ifap) {
				/*
				 * If at head of timer queue,
				 * restart timer
				 */
			    if (pp == prune_head.tq_forw &&
				!BIT_TEST(pim_timer_prune->task_timer_flags,
					  TIMERF_INACTIVE)) {
				task_timer_reset(pim_timer_prune);
			    }
			    PRUNE_TQ_DEQ(pp);
			    PRUNE_IF_DEQ(pp);
				/*
				 * if timer currently inactive,
				 * reactivate
				 */
			    if (BIT_TEST(pim_timer_prune->task_timer_flags,
					 TIMERF_INACTIVE)) {
				task_timer_set(pim_timer_prune,
					       (time_t) 0,
					       prune_head.tq_forw->prune_time - time_sec);
			    }
			    break;
			}
			pp = pp->if_forw;
		    }
		}
	    }
	    for (j = 0; j < ntohs(pg->num_prune); j++) {

		pimlen -= sizeof(u_int32) + 2 * sizeof(u_int8);
		if (pimlen < 0) {
		    trace_log_tf(pim_trace_options,
				 0,
				 LOG_WARNING,
				 ("pim_recv_join_prune: ignoring pim msg: short packet from %A",
				  task_recv_srcaddr));
		    return;
		}
		    /*
		     * skip over high and low flags in source
		     */
		cp += 2 * sizeof(u_int8);

		bcopy(cp, (caddr_t) &src_addr, sizeof(u_int32));

		mfcp = mfc_locate_mfc(sockbuild_in(0, pg->group_addr),
				      sockbuild_in(0, src_addr));
		cp += sizeof(u_int32);

		    /*
		     * If we receive a prune for a (S,G) that we have no
		     * state, then we probably have just been restarted.
		     * Create state for the group and continue since
		     * we shouldn't ignore the prune.
		     */
		if (!mfcp) {
			/* XXX */
		}
		    /*
		     * if prune arrived on upstream interface,
		     * see if we need to counteract with a join
		     */
		if (mfcp->upstream_ifap == ifap) {
		    int join = 0;
		    downstream *dsp;

		    DOWNSTREAM_LIST(dsp, mfcp->ds) {
			if (dsp->ds_proto == RTPROTO_PIM) {
			    join++;
			    break;
			}
		    } DOWNSTREAM_LIST_END(dsp, mfcp->ds);
		    if (join) {
			int offset;
			join_list *jp;

			jp = (join_list *) task_block_alloc(pim_join_block_index);
			jp->ifap = ifap;
			jp->mfcp = mfcp;
			offset = PIM_JOIN_DELAY_MIN +
				 grand((u_int32) (PIM_JOIN_DELAY_MAX -
						  PIM_JOIN_DELAY_MIN));
			jp->join_time = time_sec + offset;
			INSQUE(jp, join_head.back);

			if (!pim_timer_join) {
			    pim_timer_join = task_timer_create(pim_task,
							       "Join",
							       (flag_t) 0,
							       (time_t) 0,
							       offset,
							       pim_join_timeout,
							       (void_t) 0);
			}
			    /*
			     * if new head of list, reset timer
			     */
			else if (jp == join_head.forw &&
				 !BIT_TEST(pim_timer_join->task_timer_flags,
					   TIMERF_INACTIVE)) {
			    task_timer_reset(pim_timer_join);
			}
			    /*
			     * if timer currently inactive,
			     * reactivate
			     */
			if (BIT_TEST(pim_timer_join->task_timer_flags,
				     TIMERF_INACTIVE)) {
			    task_timer_set(pim_timer_join,
					   (time_t) 0,
					   join_head.forw->join_time - time_sec);
			}
		    }
		} else if (ours) {
			/*
			 * otherwise, if on downstream interface,
			 * queue up prune waiting for any joins
			 * to arrive before we really prune it.
			 */
		    new = (prune_list *)
			  task_block_alloc(pim_prune_block_index);
		    new->ifap = ifap;
		    new->mfcp = mfcp;
		    new->holdtime = pjh->holdtime;

			/*
			 * Don't need to wait for join on p2p link
			 */
		    if (BIT_TEST(ifap->ifa_state, IFS_POINTOPOINT)) {
			new->pending = FALSE;
			new->prune_time = time_sec + pjh->holdtime;
			    /*
			     * If send ok, add prune to timeout queue,
			     * else free it
			     */
			if (pim_send_prune(mfcp))
			    pim_queue_prune(mfcp, new);
			else
			    task_block_free(pim_prune_block_index, new);
		    } else {
			new->pending = TRUE;
			new->prune_time = time_sec + PIM_JOIN_DELAY_MAX;
			pim_queue_prune(mfcp, new);
		    }
		}
	    }
	}
	pg = (struct pimgroup *) cp;
    }
    return;
}


static void
pim_recv_assert  __PF3(ifap, if_addr *,
		       pimhdr, struct pimhdr *,
		       pimlen, int)
{
    mfc *mfcp;
    int rpbit;
    struct pimassert *pas = (struct pimassert *) (pimhdr + 1);

    if (pas->group_mask != INADDR_HOSTMASK) {
	trace_log_tf(pim_trace_options,
		     0,
		     LOG_WARNING,
		     ("pim_recv_assert: aggregation in Assert messages unsupported: Group %A, Mask %A",
		      sockbuild_in(0, pas->group_addr),
		      sockbuild_in(0, pas->group_mask)));
    }
    mfcp = mfc_locate_mfc(sockbuild_in(0, pas->group_addr),
			  sockbuild_in(0, pas->src_addr));
    if (!mfcp) {
	return;
    }

    rpbit = BIT_TEST(pas->preference, PIM_ASSERT_RPBIT);
    pas->preference &= 0x7fffffff;

	 /*
	  * if assert arrives on the upstream interface
	  */
    if (mfcp->upstream_ifap == ifap) {
	    /*
	     * If assert already received, now we have to decide upon the two.
	     * But if this is the first just queue it and time it out while
	     * waiting for the possible second.
	     */
	if (mfcp->pim_assert) {
	    if (mfcp->pim_assert->preference < pas->preference ||
	        (mfcp->pim_assert->preference == pas->preference &&
		 mfcp->pim_assert->metric < pas->metric) ||
		 (mfcp->pim_assert->preference == pas->preference &&
		  mfcp->pim_assert->metric == pas->metric &&
		  mfcp->pim_assert->rpf_addr > sock2ip(task_recv_srcaddr))) {
		mfcp->rpf_addr = mfcp->pim_assert->rpf_addr;
	    } else {
		mfcp->rpf_addr = sock2ip(task_recv_srcaddr);
	    }
	    task_block_free(pim_assert_block_index, (void_t) mfcp->pim_assert);
	    mfcp->pim_assert = (assert_list *) 0;
	} else {
	    /*
	     * This is the first assert we have received. Queue it up
	     * and see if we get another one. If not, then we have
	     * a winner!
	     */
	    assert_list *new = (assert_list *)
				task_block_alloc(pim_assert_block_index);
	    new->mfcp = mfcp;
	    new->ifap = ifap;
	    new->rpf_addr = sock2ip(task_recv_srcaddr);
	    new->assert_time = time_sec + PIM_ASSERT_TIMEOUT;
	    new->preference = pas->preference;
	    new->metric = pas->metric;
	    new->rpbit = rpbit;

	    mfcp->pim_assert = new;
	    INSQUE(new, assert_head.back);

	    if (!pim_timer_assert) {
		pim_timer_assert = task_timer_create(pim_task,
						     "Assert",
						     (flag_t) 0,
						     (time_t) 0,
						     PIM_ASSERT_TIMEOUT,
						     pim_assert_timeout,
						     (void_t) 0);
	    }
		/*
		 * if new head of list, reset timer
		 */
	    else if (new == assert_head.forw &&
		     !BIT_TEST(pim_timer_assert->task_timer_flags, TIMERF_INACTIVE)) {
		task_timer_reset(pim_timer_assert);
	    }
		/*
		 * if timer currently inactive,
		 * reactivate
		 */
	    if (BIT_TEST(pim_timer_assert->task_timer_flags, TIMERF_INACTIVE)) {
		task_timer_set(pim_timer_assert,
			       (time_t) 0,
			       assert_head.forw->assert_time - time_sec);
	    }
	}
    } else {
	    /*
	     * Else assert arrived on a downstream interface.
	     * Compare assert metric with our metric
	     */
	int keep = 0;
	upstream *up = krt_locate_upstream(sockbuild_in(0, mfcp->mfc_src),
					   IPMULTI_PROTO_PIM);

	pref_t preference = pim_preference[up->protocol] & 0x7fffffff;

	if (preference < pas->preference ||
	    (preference == pas->preference &&
	     up->metric < pas->metric) ||
	     (preference == pas->preference &&
	      up->metric == pas->metric &&
	      sock2ip(ifap->ifa_addr) > sock2ip(task_recv_srcaddr))) {

	    router_list *list = (router_list *) ifap->pim_if_router_list;
	    router_list *lp;
	    struct group_list *glist = (struct group_list *)
					ifap->igmp_if_group_list;
	    struct group_list *gp;

		/*
		 * We have won the election.
		 * Send assert back so other router knows we win.
		 */

	    pim_send_assert(ifap, mfcp->mfc_group->group_key, mfcp->mfc_src);

		/*
		 * If no directly connected group members or ...
		 */
	    if (glist) {
		GROUP_LIST(gp, glist) {
			/*
			 * Has someone requested this group ?
			 */
		    if (mfcp->mfc_group->group_key == gp->group_addr.s_addr) {
			keep++;
			break;
		    }
		} GROUP_LIST_END(gp, glist);
	    }

		/*
		 * ... no other downstream routers besides us and the
		 * router that sent the assert, prune interface.
		 */
	    if (!keep) {
		keep = -2;
		ROUTER_DR_LIST(lp, list) {
		    keep++;
		} ROUTER_DR_LIST_END(lp, list);
	    }
	}
	if (!keep) {
	    pim_mfc_delete_ifap(mfcp, (caddr_t) ifap);
	}
    }
}


static void
pim_recv_graft  __PF3(ifap, if_addr *,
		      pimhdr, struct pimhdr *,
		      pimlen, int)
{
    int rc, i, j;
    int len = pimlen - sizeof(struct pimhdr);
    u_int32 src_addr;
    struct ip *ip = (struct ip *) (pimhdr - sizeof(struct ip));
    mfc *mfcp;
    struct pimjoinhdr *pjh = (struct pimjoinhdr *) (pimhdr + 1);
    struct pimgroup *pg = (struct pimgroup *) (pjh + 1);

    len -= sizeof(struct pimjoinhdr);
    if (len < 0) {
	trace_log_tf(pim_trace_options,
		     0,
		     LOG_WARNING,
		     ("pim_recv_graft: pimjoinhdr: short packet from %A",
		      task_recv_srcaddr));
	return;
    }

    if (!sockaddrcmp(ifap->ifa_addr, sockbuild_in(0, pjh->rpf_addr))) {
	return;
    }
    assert(pjh->maddr_len == sizeof(u_int32));
    assert(pjh->addr_len == sizeof(u_int32));

    for (i = 0; i < pjh->num_groups; i++) {
	caddr_t	cp = (caddr_t) &pg->source_data[0];

	len -= sizeof(u_int32) + 2 * sizeof(u_int16);
	if (len < 0) {
	    trace_log_tf(pim_trace_options,
			 0,
			 LOG_WARNING,
			 ("pim_recv_graft: pimgroup: short packet from %A",
			  task_recv_srcaddr));
	    return;
	}

	if (pg->group_mask != INADDR_HOSTMASK) {
	    trace_log_tf(pim_trace_options,
			 0,
			 LOG_WARNING,
			 ("pim_recv_graft: aggregation in Graft messages unsupported: Group %A, Mask %A",
			  sockbuild_in(0, pg->group_addr),
			  sockbuild_in(0, pg->group_mask)));
	} else {
	    for (j = 0; j < ntohs(pg->num_join); j++) {

		len -= sizeof(u_int32) + 2 * sizeof(u_int8);
		if (len < 0) {
		    trace_log_tf(pim_trace_options,
				 0,
				 LOG_WARNING,
				 ("pim_recv_graft: source: short packet from %A",
				  task_recv_srcaddr));
		    return;
		}
		    /*
		     * skip over high and low flags in source
		     */
		cp += 2 * sizeof(u_int8);

		bcopy(cp, (caddr_t) &src_addr, sizeof(u_int32));

		mfcp = mfc_locate_mfc(sockbuild_in(0, pg->group_addr),
				      sockbuild_in(0, src_addr));
		cp += sizeof(u_int32);

		if (!mfcp) {
		    trace_tp(pim_task,
			     TR_NORMAL,
			     0,
			     ("pim_recv_graft: no Forwarding Cache entry for Group %A Source %A",
			      sockbuild_in(0, pg->group_addr),
			      sockbuild_in(0, pg->group_mask)));
		}
		     /*
		      * if graft doesn't arrive on downstream interface,
		      * ignore it
		      */
		if (mfcp->upstream_ifap != ifap) {
			/*
			 * add the downstream interface 
			 * and send back a Graft Ack.
			 */
		    pim_mfc_add_ifap(mfcp, (caddr_t) ifap);

		    pimhdr->igmp_code = PIM_GRAFT_ACK;
		    rc = igmp_send(ifap, ip, pimlen + sizeof(struct ip), task_recv_srcaddr, FALSE);
		    /* Should we trace this packet? */

		    if (TRACE_PACKET_SEND_TP(pim_task,
					     pimhdr->igmp_code,
					     PIM_MAX_TYPE,
					     pim_trace_masks)) {

			pim_trace(pim_task->task_trace,
				  rc,
				  ifap,
				  task_recv_srcaddr,
				  pimhdr,
				  pimlen,
				  TRACE_DETAIL_SEND_TP(pim_task,
						       pimhdr->igmp_code,
						       PIM_MAX_TYPE,
						       pim_trace_masks));
		    }
		}
	    }
	    if (ntohs(pg->num_prune) != 0) {

		    /*
		     * skip over high and low flags in source
		     */
		cp += 2 * sizeof(u_int8);

		trace_log_tf(pim_trace_options,
			     0,
			     LOG_WARNING,
			     ("pim_recv_graft: graft message for Group %A Source %A from %A contains prune sources!",
			      sockbuild_in(0, pg->group_addr),
			      sockbuild_in(0, *((u_int32 *) cp)),
			      task_recv_srcaddr));

		cp += sizeof(u_int32);
	    }
	}
	pg = (struct pimgroup *) cp;
    }
    return;
}


static void
pim_recv_graft_ack  __PF3(ifap, if_addr *,
			  pimhdr, struct pimhdr *,
			  pimlen, int)
{
    int i, j;
    int len = pimlen - sizeof(struct pimhdr);
    u_int32 src_addr;
    mfc *mfcp;
    struct pimjoinhdr *pjh = (struct pimjoinhdr *) (pimhdr + 1);
    struct pimgroup *pg = (struct pimgroup *) (pjh + 1);

    len -= sizeof(struct pimjoinhdr);
    if (len < 0) {
	trace_log_tf(pim_trace_options,
		     0,
		     LOG_WARNING,
		     ("pim_recv_graft_ack: ignoring pim msg: short packet from %A",
		      task_recv_srcaddr));
	return;
    }

    if (!sockaddrcmp(ifap->ifa_addr, sockbuild_in(0, pjh->rpf_addr))) {
	return;
    }
    assert(pjh->maddr_len == sizeof(u_int32));
    assert(pjh->addr_len == sizeof(u_int32));

    for (i = 0; i < pjh->num_groups; i++) {
	caddr_t	cp = (caddr_t) &pg->source_data[0];

	len -= 2 * sizeof(u_int16) + 2 * sizeof(u_int32);
	if (len < 0) {
	    trace_log_tf(pim_trace_options,
			 0,
			 LOG_WARNING,
			 ("pim_recv_graft_ack: ignoring pim msg: short packet from %A",
			  task_recv_srcaddr));
	    return;
	}

	if (pg->group_mask != INADDR_HOSTMASK) {
	    trace_log_tf(pim_trace_options,
			 0,
			 LOG_WARNING,
			 ("pim_recv_graft_ack: aggregation in Graft Ack messages unsupported: Group %A, Mask %A",
			  sockbuild_in(0, pg->group_addr),
			  sockbuild_in(0, pg->group_mask)));
	} else {
	    for (j = 0; j < ntohs(pg->num_join); j++) {

		len -= sizeof(u_int32) + 2 * sizeof(u_int8);
		if (len < 0) {
		    trace_log_tf(pim_trace_options,
				 0,
				 LOG_WARNING,
				 ("pim_recv_graft_ack: ignoring pim msg: short packet from %A",
				  task_recv_srcaddr));
		    return;
		}
		    /*
		     * skip over high and low flags in source
		     */
		cp += 2 * sizeof(u_int8);

		bcopy(cp, (caddr_t) &src_addr, sizeof(u_int32));

		mfcp = mfc_locate_mfc(sockbuild_in(0, pg->group_addr),
				      sockbuild_in(0, src_addr));
		cp += sizeof(u_int32);

		if (!mfcp) {
		    trace_tp(pim_task,
			     TR_NORMAL,
			     0,
			     ("pim_recv_graft: no Forwarding Cache entry for Group %A Source %A",
			      sockbuild_in(0, pg->group_addr),
			      sockbuild_in(0, pg->group_mask)));
		}
		     /*
		      * if graft ack doesn't arrive on upstream interface,
		      * or graft not pending, ignore it, otherwise
		      * take it off the graft retransmission queue.
		      */
		if (mfcp->upstream_ifap == ifap &&
		    mfcp->mfc_group->graft_pending) {
		    graft_list	*gp;

		    GRAFT_LIST(gp, &graft_head) {
			if (sockaddrcmp(gp->graft_dst, task_recv_srcaddr) &&
			    gp->graft_group == mfcp->mfc_group->group_key) {
			    if (gp == graft_head.forw) {
				task_timer_reset(pim_timer_graft);
			    }
			    REMQUE(gp);
			    task_block_free(pim_graft_block_index, (void_t) gp);
				    /*
				     * if timer currently inactive, reactivate
				     */
			    if (BIT_TEST(pim_timer_graft->task_timer_flags,
					 TIMERF_INACTIVE)) {
				task_timer_set(pim_timer_graft,
					       (time_t) 0,
					       gp->graft_time - time_sec);
			    }
			    break;
			}
		    } GRAFT_LIST_END(gp, &graft_head);
		}
	    }
	    if (ntohs(pg->num_prune) != 0) {

		    /*
		     * skip over high and low flags in source
		     */
		cp += 2 * sizeof(u_int8);

		trace_log_tf(pim_trace_options,
			     0,
			     LOG_WARNING,
			     ("pim_recv_graft_ack: graft ack message for Group %A Source %A from %A contains prune sources!",
			      sockbuild_in(0, pg->group_addr),
			      sockbuild_in(0, *((u_int32 *) cp)),
			      task_recv_srcaddr));
		cp += sizeof(u_int32);
	    }
	}
	pg = (struct pimgroup *) cp;
    }
    return;
}


static void
pim_router_purge __PF1(ifap, if_addr *)
{
    router_list *list = (router_list *) ifap->pim_if_router_list;
    router_list *gp, *delete;

    if (list) {
	/*
	 * If we think we should be DR on this interface,
	 * disable it before we go away
	 */

	task_timer_reset((task_timer *)ifap->pim_if_timer_timeout);

	if (sockaddrcmp(ifap->ifa_addr, list->dr_forw->router_addr)) {
	    igmp_disable_dr_status(ifap);
	}

	/*
	 *  Remove all the routers from the list
	 */
	gp = list->dr_forw;
	while(gp != list ) {
	    delete = gp;
	    gp = gp->dr_forw;
	    ROUTER_TQ_DEQ(delete);
	    ROUTER_DR_DEQ(delete);
	    task_block_free(pim_router_block_index, (void_t) delete);
	}
	task_block_free(pim_router_block_index, (void_t) list);
	ifap->pim_if_router_list = (void_t) 0;
    }
}

static void
pim_router_refresh __PF4(ifap, if_addr *,
			 src_addr, sockaddr_un *,
			 mode, int,
			 holdtime, time_t)
{
    time_t expire;
    router_list *list = (router_list *) ifap->pim_if_router_list;
    router_list *rlp, *rtr = list->dr_forw;

    while(rtr != list &&
	  rtr->router_addr->in.gin_addr.s_addr > src_addr->in.gin_addr.s_addr) {
	rtr = rtr->dr_forw;
    }
    if (rtr == list) {
	/*
	 * not found, insert at end of list
	 */
	rtr = (router_list *) task_block_alloc(pim_router_block_index);
	rtr->router_addr = sockdup(src_addr);
	ROUTER_DR_ENQ(rtr, list->dr_back);
    } else {
	/*
	 * if match, remove from old position in timer list
	 */
	if (sockaddrcmp(rtr->router_addr, src_addr)) {
	    ROUTER_TQ_DEQ(rtr);
	} else {
		/*
		 * got a new pim router in the middle of the list
		 */
	    router_list *new = (router_list *)
				task_block_alloc(pim_router_block_index);
	    ROUTER_DR_ENQ(new, rtr->dr_back);
	    rtr = new;
	    rtr->router_addr = sockdup(src_addr);
	}
    }
	/*
	 * update refresh time and insert it in the list
	 */
    rtr->hold_time = holdtime;
    rtr->mode = mode;
    rtr->refresh_time = time_sec;
    expire = rtr->refresh_time + rtr->hold_time;

    rlp = list->tq_back;
    while(rlp != list && (expire < (rlp->refresh_time + rlp->hold_time))) {
	rlp = rlp->tq_back;
    }
    ROUTER_TQ_ENQ(rtr, rlp);

    pim_refresh_router_timer(ifap,
	list->tq_forw->hold_time - (time_sec - list->tq_forw->refresh_time));
}


static void
pim_refresh_router_timer  __PF2(ifap, if_addr *,
				timeout, time_t)
{

	    /* if no timer running, create one */
    if (!ifap->pim_if_timer_timeout) {
	char name[IFNAMSIZ+9];

	(void) sprintf(name, "Router.%s", ifap->ifa_link->ifl_name); 

	ifap->pim_if_timer_timeout =
				(void_t) task_timer_create(pim_task,
							   name,
							   (flag_t) 0,
							   (time_t) 0,
							   timeout,
							   pim_router_timeout,
							   (void_t) ifap);
    }
	    /* set existing timer to new time */
    else {
	if (!BIT_TEST(((task_timer *)ifap->pim_if_timer_timeout)->task_timer_flags,
		      TIMERF_INACTIVE)) {
	    task_timer_reset((task_timer *)ifap->pim_if_timer_timeout);
	}
	    /*
	     * No way to reset data without deleting timer and
	     * re-creating it. So for now, just cheat
	     */
	((task_timer *)ifap->pim_if_timer_timeout)->task_timer_data = (void_t) ifap;

	task_timer_set((task_timer *)ifap->pim_if_timer_timeout,
		       (time_t) 0,
		       timeout);
    }
}


static void
pim_dr_election  __PF1(ifap, if_addr *)
{
    router_list *list = (router_list *) ifap->pim_if_router_list;

	/*
	 * check if I am the DR for this interface
	 * If so, let igmp check the interface status
	 */

    assert(list->dr_forw->router_addr);

    if (sockaddrcmp(ifap->ifa_addr, list->dr_forw->router_addr)) {
	igmp_enable_dr_status(ifap);
    } else {
	igmp_disable_dr_status(ifap);
    }
}

/*
 * A join delay timer has expired, time to send a join
 * This means we don't want this (S,G) entry pruned and noone else
 * has responded yet so we will.
 */

/*ARGSUSED*/
static void
pim_join_timeout  __PF2(tip, task_timer *,
			interval, time_t)
{
    join_list	*jp, *aged;

    jp = join_head.forw;
    while(jp != &join_head && (time_sec >= jp->join_time)) {

	trace_tp(pim_task,
		 TR_TIMER,
		 0,
		 ("pim_join_timeout: join delay timer expired for Group %A Source %A Interface %A(%s)",
		   sockbuild_in(0, jp->mfcp->mfc_group->group_key),
		   sockbuild_in(0, jp->mfcp->mfc_src),
		   jp->ifap->ifa_addr,
		   jp->ifap->ifa_link->ifl_name));
	
	    /*
	     * put this group,source pair in the rpf list
	     */
	pim_scan_mfc_rpf(jp->mfcp, (caddr_t) 0);

	if (rpf_head.forw != &rpf_head) {
		/*
		 * send a prune upstream for this group,source pair
		 */
	    pim_send_join_prune_graft(PIM_MSG_JOIN,
				      jp->mfcp->mfc_group->group_key);

		/*
		 * clean up the rpf list
		 */
	    pim_rpf_free();

	    aged = jp;
	    jp = jp->forw;
	    REMQUE(aged);
	    task_block_free(pim_join_block_index, (void_t) aged);
	}
    }
    if (join_head.forw != &join_head) {
	task_timer_set(pim_timer_join,
		       (time_t) 0,
		       join_head.forw->join_time - time_sec);
    }
}

static void
pim_clean_mfc  __PF1(mfcp, mfc *)
{
    prune_list *next, *down, *pp = prune_head.tq_forw;

    if (mfcp->prune_up) {
	while(pp != &prune_head) {
	    if (mfcp->prune_up == pp) {
		if (pp == prune_head.tq_forw &&
		    !BIT_TEST(pim_timer_prune->task_timer_flags, TIMERF_INACTIVE)) {
		    task_timer_reset(pim_timer_prune);
		}
		next = pp->tq_forw;
		PRUNE_TQ_DEQ(pp);
		task_block_free(pim_prune_block_index, pp);
		pp = next;
	    } else {
		pp = pp->tq_forw;
	    }
	}
    }
    if (&mfcp->prune_down != mfcp->prune_down.if_forw) {
	down = mfcp->prune_down.if_forw;
	while (down != &mfcp->prune_down) {
	    pp = prune_head.tq_forw;
	    while(pp != &prune_head) {
		if (pp == down) {
		    if (pp == prune_head.tq_forw &&
			!BIT_TEST(pim_timer_prune->task_timer_flags, TIMERF_INACTIVE)) {
			task_timer_reset(pim_timer_prune);
		    }
		    next = pp->tq_forw;
		    PRUNE_TQ_DEQ(pp);
		    PRUNE_IF_DEQ(pp);
		    task_block_free(pim_prune_block_index, pp);
		    pp = next;
		} else {
		    pp = pp->tq_forw;
		}
	    }
	    down = down->if_forw;
	}
    }
    if (prune_head.tq_forw != &prune_head &&
	BIT_TEST(pim_timer_prune->task_timer_flags, TIMERF_INACTIVE)) {
	task_timer_set(pim_timer_prune,
		       (time_t) 0,
		       prune_head.tq_forw->prune_time - time_sec);
    }
    if (mfcp->pim_assert) {
	    /*
	     * If we are the top of the assert queue, then we must stop
	     * the timer and possibly restart it.
	     */
	if (mfcp->pim_assert == assert_head.forw) {
	    task_timer_reset(pim_timer_assert);
	    REMQUE(mfcp->pim_assert);
	    if (assert_head.forw != &assert_head) {
		task_timer_set(pim_timer_assert,
			       (time_t) 0,
			       assert_head.forw->assert_time - time_sec);
	    }
	} else {
		/*
		 * Otherwise, just take it out of the timer queue.
		 */
	    REMQUE(mfcp->pim_assert);
	}
	task_block_free(pim_assert_block_index, (void_t) mfcp->pim_assert);
	mfcp->pim_assert = (assert_list *) 0;
    }
}

/*ARGSUSED*/
static void
pim_prune_timeout  __PF2(tip, task_timer *,
	 		 interval, time_t)
{
    prune_list *aged, *pp = prune_head.tq_forw;

    while(pp != &prune_head && pp->prune_time <= time_sec) {
	aged = pp;
	pp = pp->tq_forw;
	PRUNE_TQ_DEQ(aged);
	if (aged == aged->mfcp->prune_up) {
	    aged->mfcp->prune_up = (prune_list *) 0;
	} else {
	    PRUNE_IF_DEQ(aged);
	}

	    /*
	     * If this is a pending prune, go ahead and send prune
	     * since noone sent a join to stop it.
	     */
	if (aged->pending) {

	    aged->pending = FALSE;
	    aged->prune_time = time_sec + aged->holdtime;
		/*
		 * If send ok, add prune to timeout queue, else free it
		 */
	    if (pim_send_prune(aged->mfcp))
		pim_queue_prune(aged->mfcp, aged);
	    else
		task_block_free(pim_prune_block_index, aged);
	
	    /*
	     * Determine if this prune was received from downstream
	     * or was sent upstream
	     */
	} else if (aged->mfcp->upstream_ifap == aged->ifap) {

		/*
		 * pretend we don't know anything about this (S,G)
		 * anymore and build up new state.
		 */
	    BIT_RESET(aged->mfcp->mfc_proto, IPMULTI_BIT(IPMULTI_PROTO_PIM));

		/*
		 * If this is the last protocol to want this cache entry,
		 * time to blow it away
		 */
	    if (!aged->mfcp->mfc_proto) {
		pim_reset_mfc_timer(aged->mfcp);
		mfc_source_unlink_unicast(pim_task, aged->mfcp);
		(void) krt_delete_cache(sockbuild_in(0, aged->mfcp->mfc_group->group_key),
					sockbuild_in(0, aged->mfcp->mfc_src));
		mfc_delete_node(aged->mfcp);
	    }

	    task_block_free(pim_prune_block_index, aged);
	} else {
		/*
		 * Time to start sending traffic down this interface again
		 * and wait for the next prune
		 */
	    pim_mfc_add_ifap(aged->mfcp, (caddr_t) aged->ifap);

	    task_block_free(pim_prune_block_index, aged);
	}
    }
    if (prune_head.tq_forw != &prune_head) {
	task_timer_set(pim_timer_prune,
		       (time_t) 0,
		       prune_head.tq_forw->prune_time - time_sec);
    }
}

static void
pim_queue_prune  __PF2(mfcp, mfc *,
		       new, prune_list *)
{
    prune_list *pp = prune_head.tq_forw;

    while(pp != &prune_head &&
	  pp->prune_time < new->prune_time) {
	pp = pp->tq_forw;
    }
    PRUNE_TQ_ENQ(new, pp->tq_back);
	/*
	 * We insert an upstream prune in a separate pointer.
	 * A dowstream prune gets put at the end of the list.
	 */
    if (new->ifap == mfcp->upstream_ifap) {
	mfcp->prune_up = new;
    } else {
	PRUNE_IF_ENQ(new, mfcp->prune_down.if_back);
    }

    if (!pim_timer_prune) {
	pim_timer_prune = task_timer_create(pim_task,
					    "Prune",
					    (flag_t) 0,
					    (time_t) 0,
					    new->prune_time - time_sec,
					    pim_prune_timeout,
					    (void_t) 0);
    }
	/*
	 * if new head of list, reset timer
	 */
    else if (new == prune_head.tq_forw &&
	     !BIT_TEST(pim_timer_prune->task_timer_flags, TIMERF_INACTIVE)) {
	task_timer_reset(pim_timer_prune);
    }
	/*
	 * if timer currently inactive,
	 * reactivate
	 */
    if (BIT_TEST(pim_timer_prune->task_timer_flags, TIMERF_INACTIVE)) {
	task_timer_set(pim_timer_prune,
		       (time_t) 0,
		       prune_head.tq_forw->prune_time - time_sec);
    }
}

static int
pim_send_prune  __PF1(mfcp, mfc *)
{

	/*
	 * put this group,source pair in the rpf list
	 * returns non-zero on error
	 */
    pim_scan_mfc_rpf(mfcp, (caddr_t) 0);

    if (rpf_head.forw == &rpf_head)
	return(0);

	/*
	 * send a prune upstream for this group,source pair
	 */
    pim_send_join_prune_graft(PIM_MSG_PRUNE, mfcp->mfc_group->group_key);

	/*
	 * clean up the rpf list
	 */
    pim_rpf_free();

    return(1);
}


static void
pim_mfc_add_ifap  __PF2(mfcp, mfc *,
			data, caddr_t)
{
    prune_list *pp;
    downstream *dsp, *dpos;
    if_addr *ifap = (if_addr *) data;

	/*
	 * Don't want to add interface if it is the expecting incoming intf
	 */
    if (ifap == mfcp->upstream_ifap)
	return;
	/*
	 * Look to see if interface is already in downstream list
	 */
    DOWNSTREAM_LIST(dsp, mfcp->ds) {
        if (dsp->ds_proto == RTPROTO_PIM) {
	    if (sockaddrcmp_in(dsp->ds_addr, ifap->ifa_addr)) {
		return;
	    }
	}
    } DOWNSTREAM_LIST_END(dsp, mfcp->ds);

	/*
	 * This interface is not part of the downstream interface list
	 * Add it.
	 */
    dpos = mfcp->ds->forw;
    while (dpos != mfcp->ds) {
	    if (sock2ip(dpos->ds_addr) < sock2ip(ifap->ifa_addr))
		    dpos = dpos->forw;
    }

    dsp = mfc_alloc_downstream();

    dsp->ds_proto = RTPROTO_PIM;
    dsp->ds_addr = ifap->ifa_addr;
    dsp->ds_ttl = dsp->ds_flags = dsp->ds_ifindex = 0;

	/*
	 * stick at the end of the list
	 */
    INSQUE(dsp, dpos->back);

    mfcp->ds_count++;

    trace_tp(pim_task,
	     TR_ROUTE,
	     0,
	     ("pim_mfc_add_ifap: PIM adding downstream interface %A(%s)",
	      ifap->ifa_addr,
	      ifap->ifa_link->ifl_name));

    krt_update_mfc(mfcp);

	/*
	 * If there is a prune upstream, we may need to send a graft.
	 */

    if ((pp=mfcp->prune_up)) {
	if (pp == prune_head.tq_forw &&
	    !BIT_TEST(pim_timer_prune->task_timer_flags,
		      TIMERF_INACTIVE)) {
	    task_timer_reset(pim_timer_prune);
	}

	PRUNE_TQ_DEQ(pp);

	task_block_free(pim_prune_block_index, pp);

	mfcp->prune_up = (prune_list *) 0;

	    /*
	     * If source is on a directly attached subnet,
	     * no need to send a graft. We will automatically get the packets.
	     */
	if (mfcp->upstream_ifap !=
	    if_withsubnet(sockbuild_in (0, mfcp->mfc_src))) {
	    pim_send_graft(mfcp->upstream_ifap, mfcp->mfc_group->group_key);
	}
    }

    pp = mfcp->prune_down.if_forw;
    while (pp != &mfcp->prune_down) {
	if (pp->ifap == ifap) {
		/*
		 * if this prune is at the head of the timer queue,
		 * we must refresh the timer queue after deleting it.
		 */
	    if (pp == prune_head.tq_forw &&
		!BIT_TEST(pim_timer_prune->task_timer_flags,
			  TIMERF_INACTIVE)) {
		task_timer_reset(pim_timer_prune);
	    }
	    PRUNE_TQ_DEQ(pp);
	    PRUNE_IF_DEQ(pp);
	    task_block_free(pim_prune_block_index, pp);
	    break;
	}
	pp = pp->if_forw;
    }
	/*
	 * if timer currently inactive,
	 * reactivate
	 */
    if (prune_head.tq_forw != &prune_head &&
	BIT_TEST(pim_timer_prune->task_timer_flags,
		 TIMERF_INACTIVE)) {
	task_timer_set(pim_timer_prune,
		       (time_t) 0,
		       prune_head.tq_forw->prune_time - time_sec);
    }
}

static void
pim_mfc_delete_ifap  __PF2(mfcp, mfc *,
			   data, caddr_t)
{
    int count = 0;
    prune_list *new;
    downstream *dsp, *delete = 0;
    if_addr *ifap = (if_addr *) data;

    DOWNSTREAM_LIST(dsp, mfcp->ds) {
        if (dsp->ds_proto == RTPROTO_PIM) {
	    if (sockaddrcmp_in(dsp->ds_addr, ifap->ifa_addr)) {
		    /*
		     * should never happen more than once!
		     */
		delete = dsp;
	    } else {
		count++;
	    }
	}
    } DOWNSTREAM_LIST_END(dsp, mfcp->ds);

    if (delete) {
	trace_tp(pim_task,
		 TR_ROUTE,
		 0,
		 ("pim_mfc_delete_ifap: PIM removing downstream interface %A(%s) for group %A source %A",
		  ifap->ifa_addr,
		  ifap->ifa_link->ifl_name,
		  sockbuild_in(0, mfcp->mfc_group->group_key),
		  sockbuild_in(0, mfcp->mfc_src)));
	REMQUE(delete);
	mfc_free_downstream(delete);

	assert(mfcp->ds_count);

	mfcp->ds_count--;


	krt_update_mfc(mfcp);
	    /*
	     * If no more downstream interfaces, time to prune upstream
	     */
	if (!count) {
	    new = (prune_list *) task_block_alloc(pim_prune_block_index);
	    new->ifap = mfcp->upstream_ifap;
	    new->mfcp = mfcp;
	    new->pending = FALSE;
	    new->holdtime = pim_default_prunetimeout;
	    new->prune_time = time_sec + pim_default_prunetimeout;

		/*
		 * If send ok, add prune to timeout queue, else free it
		 */
	    if (pim_send_prune(mfcp))
		pim_queue_prune(mfcp, new);
	    else
		task_block_free(pim_prune_block_index, new);
	}
    }
}

/*
 * There are some cases when you only want to delete the interface
 * and not send a prune yet because you are in the process of changing
 * the upstream interface and will be adding another interface shortly.
 * Also, you only want to update the kernel once. Therefore, this routine
 * is the same as above except it only deletes the downstream interface
 * and nothing else.
 */

static void
pim_mfc_delete_only_ifap  __PF2(mfcp, mfc *,
				ifap, if_addr *)
{
    downstream *dsp, *delete = 0;

    DOWNSTREAM_LIST(dsp, mfcp->ds) {
        if (dsp->ds_proto == RTPROTO_PIM) {
	    if (sockaddrcmp_in(dsp->ds_addr, ifap->ifa_addr)) {
		    /*
		     * should never happen more than once!
		     */
		delete = dsp;
	    }
	}
    } DOWNSTREAM_LIST_END(dsp, mfcp->ds);

    if (delete) {
	trace_tp(pim_task,
		 TR_ROUTE,
		 0,
		 ("pim_mfc_delete_only_ifap: PIM removing downstream interface %A(%s) for group %A source %A",
		  ifap->ifa_addr,
		  ifap->ifa_link->ifl_name,
		  sockbuild_in(0, mfcp->mfc_group->group_key),
		  sockbuild_in(0, mfcp->mfc_src)));
	REMQUE(delete);
	mfc_free_downstream(delete);

	assert(mfcp->ds_count);

	mfcp->ds_count--;
    }
}

void
pim_group_change  __PF3(change, int,
			ifap, if_addr *,
			group, u_int32)
{
    group_node *gp = mfc_locate_group(group);

    switch(change) {
    case IGMP_GROUP_ADDED:
	trace_tp(pim_task,
		 TR_NORMAL,
		 0,
		 ("pim_group_change: group %A ADDED",
		  sockbuild_in(0, group)));
	if (gp) {
		/*
		 * Visit each mfc entry for all sources in this group
		 * Check for pruned off leaf networks
		 * If found, update downstream interface list with
		 * joining interface.
		 *
		 * Look for existing prunes as well.
		 * If found, must send graft
		 */
	    mfc_source_visit(gp, pim_mfc_add_ifap, (caddr_t) ifap);
	}
	break;

    case IGMP_GROUP_REMOVED:
	trace_tp(pim_task,
		 TR_NORMAL,
		 0,
		 ("pim_group_change: group %A REMOVED",
		  sockbuild_in(0, group)));
	if (gp) {
		/*
		 * Visit each mfc entry for all sources in this group
		 * Look to see if dropping interface can be pruned.
		 *
		 * If downstream interface becomes null as a result,
		 * can send prune upstream for particular source.
		 */
	    mfc_source_visit(gp, pim_mfc_delete_ifap, (caddr_t) ifap);
	}
	break;
    }
}


/*
 *	Cleanup before re-init
 */
/*ARGSUSED*/
static void
pim_cleanup __PF1(tp, task *)
{
	/* Release policy list */

    adv_free_list(pim_int_policy);
    pim_int_policy = (adv_entry *) 0;


    if (tp) {
	trace_freeup(tp->task_trace);
    }
    trace_freeup(pim_trace_options);
}

/*
 *	re-init routine
 */
/*ARGSUSED*/
static void
pim_reinit __PF1(tp, task *)
{
    trace_set(pim_task->task_trace, pim_trace_options);
}


/*
 *	Terminating - clean up
 */
static void
pim_terminate __PF1(tp, task *)
{
    register if_addr *ifap;

	/* Disable kernel socket options */
    igmp_disable_mrouting();
    igmp_disable_asserts();

	/* Remove receive routine */
    igmp_unregister_recv( IGMP_PROTO_PIM );
    igmp_unregister_group_change( pim_group_change );
    krt_unregister_mfc( EADDRNOTAVAIL, pim_mfc_request );
    krt_unregister_mfc( EADDRINUSE, pim_mfc_request );

	/*
	 * Remove list of routers on each interface
	 */

    IF_ADDR(ifap) {
	pim_router_purge(ifap);

        if (ifap->pim_if_timer_timeout) {
	    task_timer_delete((task_timer *) ifap->pim_if_timer_timeout);
            ifap->pim_if_timer_timeout = (void_t) 0;
	}
	(void) igmp_group_drop(ifap, igmp_all_routers);
	krt_del_vif(ifap);
    } IF_ADDR_END(ifap) ;

    pim_cleanup(tp);

    /* And exit */
    task_delete(tp);

    pim_timer_query = (task_timer *) 0;
    pim_timer_graft = (task_timer *) 0;
    pim_timer_prune = (task_timer *) 0;
    pim_timer_mfc = (task_timer *) 0;
}

/*
 *	Deal with interface policy
 */
static void
pim_control_reset __PF2(tp, task *,
			  ifap, if_addr *)
{
    struct ifa_ps *ips = &ifap->ifa_ps[tp->task_rtproto];

    BIT_RESET(ips->ips_state, IFPS_RESET);
}


static void
pim_control_set __PF2(tp, task *,
			ifap, if_addr *)
{
    struct ifa_ps *ips = &ifap->ifa_ps[tp->task_rtproto];
    config_entry **list = config_resolv_ifa(pim_int_policy,
					    ifap,
					    PIM_CONFIG_MAX);

    /* Init */
    pim_control_reset(tp, ifap);

    if (list) {
	int type = PIM_CONFIG_MAX;
	config_entry *cp;

	/* Fill in the parameters */
	while (--type) {
	    if ((cp = list[type])) {
		switch (type) {
		case PIM_CONFIG_ENABLE:
		    if (BIT_TEST(ifap->ifa_state, IFS_LOOPBACK)) {
			trace_only_tf(pim_trace_options,
			 0,
			 ("pim_control_set: can't enable pim on loopback"));
		    }
		    if (BIT_TEST(ifap->ifa_state, IFS_MULTICAST)) {

			BIT_RESET(ips->ips_state, IFPS_NOIN);
			BIT_RESET(ips->ips_state, IFPS_NOOUT);
		    } else {
			trace_only_tf(pim_trace_options,
			 0,
			 ("control_set: interface %A(%s) not multicast capable",
			  ifap->ifa_addr,
			  ifap->ifa_link->ifl_name));
		    }

		    break;

		case PIM_CONFIG_DISABLE:

		    BIT_SET(ips->ips_state, IFPS_NOIN);
		    BIT_SET(ips->ips_state, IFPS_NOOUT);
		    igmp_reset_ifproto(ifap, IPMULTI_PROTO_PIM);
		    break;

		case PIM_CONFIG_MODE:
		    if (cp->config_data)
			BIT_SET(ips->ips_state,IFPS_PIM_MODE);
		    else
			BIT_RESET(ips->ips_state,IFPS_PIM_MODE);
		    break;

		case PIM_CONFIG_PRUNETIMEOUT:
		    break;

		case PIM_CONFIG_INACTIVITYTIMEOUT:
		    break;
		}
	    }
	}

	config_resolv_free(list, PIM_CONFIG_MAX);
    }
}

/*
 *	Process changes in the routing table.
 */
static void
pim_flash __PF2(tp, task *,
		change_list, rt_list *)
{
    rt_head *rth;

    rt_open(tp);

    RT_LIST(rth, change_list, rt_head) {
	mfc_src_list *msl = 0, *head = 0, *up_head = 0;
	rt_entry *new_rt = rth->rth_active;
	rt_entry *old_rt = (rt_entry *) 0;

	if (rth->rth_last_active
	    && rtbit_isset(rth->rth_last_active, tp->task_rtbit)) {
	    /* There was an MFC off the last active route */

	    old_rt = rth->rth_last_active;
	    rttsi_get(rth, tp->task_rtbit, (byte *) &head);
	    assert(head);
	}

	if (!old_rt && !new_rt) {
		/* Close the table */
	    rt_close(tp, (gw_entry *) 0, 0, NULL);
	    return;
	}


		/*
		 * We have ADDED a new route. Look to see if there are
		 * any MFC's above that would benefit from this better route.
		 */
	if (!old_rt) {
	    rt_head *parent = rt_table_locate_parent(rth);
	    if (parent && rtbit_isset(parent->rth_active, tp->task_rtbit)) {
		rttsi_get(rth, tp->task_rtbit, (byte *) &up_head);
		if (up_head) {
		    msl = up_head->forw;
		    while(msl != up_head) {
			trace_tp(pim_task,
				 TR_ROUTE,
				 0,
				 ("pim_flash: checking group %A source %A for new route %A mask %A",
				  sockbuild_in(0, msl->mfcp->mfc_group->group_key),
				  sockbuild_in(0, msl->mfcp->mfc_src),
				  rth->rth_dest,
				  rth->rth_dest_mask));
			if (sockaddrcmp_mask(rth->rth_dest,
					    sockbuild_in(0, msl->mfcp->mfc_src),
					    rth->rth_dest_mask)) {

			    mfc_src_list *next = msl->forw;
			    REMQUE(msl);
				/*
				 * If this route is better, alloc a new head
				 * and move the MFC to the new route
				 */
			    head = task_block_alloc(mfc_unicast_block_index);
			    head->forw = head;
			    head->back = head;

				/*
				 * Check incoming interface for change.
				 */
			    if (RT_IFAP(new_rt) != msl->mfcp->upstream_ifap) {
				if_addr *save_ifap = msl->mfcp->upstream_ifap;
				pim_mfc_delete_only_ifap(msl->mfcp,
							 RT_IFAP(new_rt));
				msl->mfcp->upstream_ifap = RT_IFAP(new_rt);
				pim_mfc_add_ifap(msl->mfcp, (caddr_t) save_ifap);
			    }
			    trace_tp(pim_task,
				     TR_ROUTE,
				     0,
				     ("pim_flash: moving group %A source %A to new route %A mask %A",
				      sockbuild_in(0, msl->mfcp->mfc_group->group_key),
				      sockbuild_in(0, msl->mfcp->mfc_src),
				      rth->rth_dest,
				      rth->rth_dest_mask));
			    rttsi_set(rth, tp->task_rtbit, (byte *) &head);
			    rtbit_set(new_rt, tp->task_rtbit);
			    INSQUE(msl, head->forw);
			    msl = next;
			} else {
			    msl = msl->forw;
			}
		    }
			/*
			 * If all of the MFC's got moved off parent,
			 * clean up parent and reset bits
			 */
		    if (up_head == up_head->forw) {
			task_block_free(mfc_unicast_block_index, (void_t) up_head);
			rtbit_reset(parent->rth_active, tp->task_rtbit);
			rttsi_reset(parent, tp->task_rtbit);

		    }
		}
	    }
	    continue;
	}

		/*
		 * We have DELETED a route. See if we can move these MFC's
		 * to a less specific route above.
		 */
	if (!new_rt) {
	    mfc_src_list *next;
	    rt_head *parent = rt_table_locate_parent(rth);

	    if (parent) {
		msl = head->forw;
		while (msl != head) {
		    next = msl->forw;
		    REMQUE(msl);
			/*
			 * If parent subsumes this route, move MFC's to parent.
			 * Also, perform upstream interface check.
			 */
		    if (sockaddrcmp_mask(parent->rth_dest,
					 sockbuild_in(0, msl->mfcp->mfc_src),
					 parent->rth_dest_mask)) {
			if (RT_IFAP(parent->rth_active) !=
						msl->mfcp->upstream_ifap) {
			    if_addr *save_ifap = msl->mfcp->upstream_ifap;
			    pim_mfc_delete_only_ifap(msl->mfcp,
						RT_IFAP(parent->rth_active));
			    msl->mfcp->upstream_ifap = RT_IFAP(parent->rth_active);
			    pim_mfc_add_ifap(msl->mfcp, (caddr_t) save_ifap);
			}
			trace_tp(pim_task,
				 TR_ROUTE,
				 0,
				 ("pim_flash: moving group %A source %A to new route %A mask %A",
				  sockbuild_in(0, msl->mfcp->mfc_group->group_key),
				  sockbuild_in(0, msl->mfcp->mfc_src),
				  parent->rth_dest,
				  parent->rth_dest_mask));
			if (rtbit_isset(parent->rth_active, tp->task_rtbit)) {
			    rttsi_get(rth, tp->task_rtbit, (byte *) &up_head);
			} else {
			    up_head = task_block_alloc(mfc_unicast_block_index);
			    up_head->forw = up_head;
			    up_head->back = up_head;
			}
			INSQUE(msl, up_head->forw);
		    } else {
			    /*
			     * No route back to source. Must delete MFC.
			     */
			BIT_RESET(msl->mfcp->mfc_proto,
				  IPMULTI_BIT(IPMULTI_PROTO_PIM));
			if (!msl->mfcp->mfc_proto) {
			    pim_clean_mfc(msl->mfcp);
			    pim_reset_mfc_timer(msl->mfcp);
			    (void) krt_delete_cache(sockbuild_in(0, msl->mfcp->mfc_group->group_key),
						    sockbuild_in(0, msl->mfcp->mfc_src));
			    mfc_delete_node(msl->mfcp);
			}
			task_block_free(mfc_unicast_block_index, (void_t) msl);
		    }
		    msl = next;
		}
	    } else {
		    /*
		     * No route back to source. Must delete MFCs.
		     */
		msl = head->forw;
		while (msl != head) {
		    next = msl->forw;
		    REMQUE(msl);

		    BIT_RESET(msl->mfcp->mfc_proto,
			      IPMULTI_BIT(IPMULTI_PROTO_PIM));
		    if (!msl->mfcp->mfc_proto) {
			pim_clean_mfc(msl->mfcp);
			pim_reset_mfc_timer(msl->mfcp);
			(void) krt_delete_cache(sockbuild_in(0, msl->mfcp->mfc_group->group_key),
						sockbuild_in(0, msl->mfcp->mfc_src));
			mfc_delete_node(msl->mfcp);
		    }
		    task_block_free(mfc_unicast_block_index, (void_t) msl);
		    msl = next;
		}
	    }
	    rtbit_reset(old_rt, tp->task_rtbit);
	    rttsi_reset(rth, tp->task_rtbit);
	    task_block_free(mfc_unicast_block_index, head);
	    continue;
	}
		/*
		 * We have CHANGED a route. Perform upstream interface check.
		 */
	if (old_rt && new_rt) {
		/* If the upstream interface has changed,
		 * delete the new one from the downstream interface list
		 * and add it as the new upstream interface. Then add the
		 * old upstream interface list and a new downstream interface.
		 */
	    if (RT_IFAP(old_rt) != RT_IFAP(new_rt)) {
		pim_mfc_delete_only_ifap(msl->mfcp, RT_IFAP(new_rt));

		msl->mfcp->upstream_ifap = RT_IFAP(new_rt);

		pim_mfc_add_ifap(msl->mfcp, (caddr_t) RT_IFAP(old_rt));
	    }
	    trace_tp(pim_task,
		     TR_ROUTE,
		     0,
		     ("pim_flash: route change %A mask %A",
		      rth->rth_dest,
		      rth->rth_dest_mask));
	    if (old_rt != new_rt)
		    /*
		     * Reset old MFC indication
		     */
		rtbit_reset(old_rt, tp->task_rtbit);
	    continue;
	}
    } RT_LIST_END(rth, change_list, rt_head) ;

    /* Close the table */
    rt_close(tp, (gw_entry *) 0, 0, NULL);
}


/*
 *	Deal with an interface status change
 */
static void
pim_ifachange __PF2(tp, task *,
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
	    pim_control_set(tp, ifap);

	    if (BIT_TEST(ifap->ifa_state, IFS_LOOPBACK)) {
		BIT_SET(ips->ips_state, IFPS_NOIN);
		BIT_SET(ips->ips_state, IFPS_NOOUT);
	    }
	    if (!BIT_TEST(ips->ips_state, IFPS_NOOUT)) {
		    /*
		     * If we can lock this interface for PIM,
		     * do so, otherwise, another multicast protocol has it
		     */
		if (igmp_set_ifproto(ifap, IPMULTI_PROTO_PIM) == TRUE) {
		    if (BIT_TEST(ifap->ifa_state, IFS_MULTICAST)) {
                        krt_add_vif(ifap, (sockaddr_un *) 0, 1, 0);

			if (BIT_TEST(ifap->ifa_state, IFS_BROADCAST)) {
			    (void) igmp_group_add(ifap, igmp_all_routers);
			    pim_commence_query(ifap);
			}
		    }
		} else {
		    BIT_SET(ips->ips_state, IFPS_NOIN);
		    BIT_SET(ips->ips_state, IFPS_NOOUT);
		}
	    }
	}
	break;

    case IFC_DELETE:
    case IFC_DELETE|IFC_UPDOWN:

	if (BIT_TEST(ifap->ifa_state, IFS_MULTICAST) &&
	    !BIT_TEST(ips->ips_state, IFPS_NOOUT)) {
	    krt_del_vif(ifap);
	    if (BIT_TEST(ifap->ifa_state, IFS_BROADCAST)) {
		(void) igmp_group_drop(ifap, igmp_all_routers);
	    }
	}
	pim_router_purge(ifap);
	pim_control_reset(tp, ifap);
	break;

    default:
	/* Something has changed */

	if (BIT_TEST(ifap->ifa_change, IFC_UPDOWN)) {
	    if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
		/* Down to Up transition */

		pim_control_set(tp, ifap);
		if (BIT_TEST(ifap->ifa_state, IFS_LOOPBACK)) {
		    BIT_SET(ips->ips_state, IFPS_NOIN);
		    BIT_SET(ips->ips_state, IFPS_NOOUT);
		}
		if (!BIT_TEST(ips->ips_state, IFPS_NOOUT)) {
			/*
			 * If we can lock this interface for PIM,
			 * do so, otherwise, another multicast protocol has it
			 */
		    if (igmp_set_ifproto(ifap, IPMULTI_PROTO_PIM) == TRUE) {
			if (BIT_TEST(ifap->ifa_state, IFS_MULTICAST)) {
			    krt_add_vif(ifap, (sockaddr_un *) 0, 1, 0);

			    if (BIT_TEST(ifap->ifa_state, IFS_BROADCAST)) {
				(void) igmp_group_add(ifap, igmp_all_routers);
				pim_commence_query(ifap);
				if (pim_timer_query) {
				    pim_send_query(ifap);
				}
			    }
			}
		    } else {
			BIT_SET(ips->ips_state, IFPS_NOIN);
			BIT_SET(ips->ips_state, IFPS_NOOUT);
		    }
		}
	    } else {
		/* UP to DOWN transition */

		if (BIT_TEST(ifap->ifa_state, IFS_MULTICAST) && 
		    !BIT_TEST(ips->ips_state, IFPS_NOOUT)) {
		    krt_del_vif(ifap);
		    if (BIT_TEST(ifap->ifa_state, IFS_BROADCAST)) {
			(void) igmp_group_drop(ifap, igmp_all_routers);
		    }
		}
		pim_router_purge(ifap);
		pim_control_reset(tp, ifap);
	    }
	}
	break;
    }
}

/*
 * Here we initialize the protocol preferences for sending and receiving
 * Assert Messages. We have defined these to match the Cisco implementation.
 * Its not pretty but it will enhance the interoperability.
 */

static void
pim_pref_init __PF0(void)
{
    pim_preference[RTPROTO_DIRECT] = PIM_DIRECT_PREFERENCE;
    pim_preference[RTPROTO_KERNEL] = PIM_KERNEL_PREFERENCE;
    pim_preference[RTPROTO_STATIC] = PIM_STATIC_PREFERENCE;
    pim_preference[RTPROTO_OSPF] = PIM_OSPF_PREFERENCE;
    pim_preference[RTPROTO_OSPF_ASE] = PIM_OSPF_PREFERENCE;
    pim_preference[RTPROTO_RIP] = PIM_RIP_PREFERENCE;
    pim_preference[RTPROTO_HELLO] = PIM_HELLO_PREFERENCE;
    pim_preference[RTPROTO_BGP] = PIM_BGP_PREFERENCE;
    pim_preference[RTPROTO_EGP] = PIM_EGP_PREFERENCE;
    pim_preference[RTPROTO_IDRP] = PIM_IDRP_PREFERENCE;
    pim_preference[RTPROTO_ISIS] = PIM_ISIS_PREFERENCE;
    pim_preference[RTPROTO_SLSP] = PIM_SLSP_PREFERENCE;
}


void
pim_set_pref __PF2(rtproto, int,
		   pref, pref_t)
{
    pim_preference[rtproto] = pref;
}


static void
pim_int_dump __PF2(fd, FILE *,
		   list, config_entry *)
{
    register config_entry *cp;

    CONFIG_LIST(cp, list) {
	switch (cp->config_type) {
	case PIM_CONFIG_ENABLE:
	    (void) fprintf(fd, " %s enabled",
			   cp->config_data ? "" : "not");
	    break;

	case PIM_CONFIG_DISABLE:
	    (void) fprintf(fd, " %s disabled",
			   cp->config_data ? "" : "not");
	    break;

	case PIM_CONFIG_MODE:
	    break;

	case PIM_CONFIG_PRUNETIMEOUT:
	    (void) fprintf(fd, " prune-timeout %u secs", cp->config_data);
	    break;

	case PIM_CONFIG_INACTIVITYTIMEOUT:
	    (void) fprintf(fd, " inactivity-timeout %u secs", cp->config_data);
	    break;
	default:
	    assert(FALSE);
	    break;
	}
    } CONFIG_LIST_END(cp, list) ;
}

/* ARGSUSED */
static void
pim_tsi_dump __PF4(fp, FILE *,
		   rth, rt_head *,
		   data, void_t,
		   pfx, const char *)
{
    mfc_src_list *head, *msl;

    rttsi_get(rth, pim_task->task_rtbit, (byte *) &head);

    if (head) {
	msl = head->forw;
	while (msl != head) {
	    mfc *mfcp = msl->mfcp;

	    (void) fprintf(fp, "%sPIM %A, %A\n",
			   pfx,
			   sockbuild_in(0, mfcp->mfc_group->group_key),
			   sockbuild_in(0, mfcp->mfc_src));
	    msl = msl->forw;
	}
    }
}

static void
pim_dump __PF2(tp, task *,
	       fd, FILE *)
{
    if_addr	*ifap;
    mfc_list	*mp;
    join_list	*jp;
    prune_list	*pp;
    graft_list	*gp;

    if (pim_int_policy) {
	(void) fprintf(fd, "\tInterface policy:\n");
	control_interface_dump(fd, 2, pim_int_policy, pim_int_dump);
    }

	/*
	 * Dump list of routers on each interface
	 */
    IF_ADDR(ifap) {
	struct ifa_ps *ips = &ifap->ifa_ps[RTPROTO_PIM];
	router_list *list = (router_list *) ifap->pim_if_router_list;
	router_list *rp;

	if (!BIT_TEST(ips->ips_state, IFPS_NOIN)) {
	    (void) fprintf(fd, "\tInterface %A(%s):  Leaf Status: %s   Mode: %s\n",
		    ifap->ifa_addr,
		    ifap->ifa_link->ifl_name,
		    BIT_TEST(ips->ips_state,IFPS_NOT_LEAF) ? "False":"True",
		    BIT_TEST(ips->ips_state,IFPS_PIM_MODE) ? "Sparse":"Dense");
	    if (list && BIT_TEST(ifap->ifa_state, IFS_BROADCAST)) {
		(void) fprintf(fd, "\t\t PIM Router        Last Refresh\n");

		(void) fprintf(fd, "\tDR");
		ROUTER_DR_LIST(rp, list) {
		    (void) fprintf(fd, "\t%-15A %5u secs ago\n\t",
				   rp->router_addr,
				   time_sec - rp->refresh_time);
		} ROUTER_DR_LIST_END(rp, list);
	    }
	    (void) fprintf(fd, "\n");
	}
    } IF_ADDR_END(ifap) ;

    (void) fprintf(fd, "\n\tCurrent Prune List:\n");
    (void) fprintf(fd, "\t\t   Group           Source       Times Out\n");
    PRUNE_LIST(pp, &prune_head) {
	(void) fprintf(fd, "\t\t%-15A %-15A  %4u secs\n",
			sockbuild_in(0, pp->mfcp->mfc_group->group_key),
			sockbuild_in(0, pp->mfcp->mfc_src),
			pp->prune_time - time_sec);
    } PRUNE_LIST_END(pp, &prune_head);

    (void) fprintf(fd, "\n\tCurrent Join Delay List:\n");
    JOIN_LIST(jp, &join_head) {
	(void) fprintf(fd,
		       "\t\tWaiting %d more second(s) to send Join for Group %A Source %A out Interface %A(%s)\n",
		       jp->join_time - time_sec,
		       sockbuild_in(0, jp->mfcp->mfc_group->group_key),
		       sockbuild_in(0, jp->mfcp->mfc_src),
		       jp->ifap->ifa_addr,
		       jp->ifap->ifa_link->ifl_name);
    } JOIN_LIST_END(jp, &join_head);

    (void) fprintf(fd, "\n\tCurrent Unacknowleged Grafts:\n");
    GRAFT_LIST(gp, &graft_head) {
	(void) fprintf(fd,
		        "\t\tGroup %A added on interface %A(%s) sent to %A, %3d seconds ago\n",
			sockbuild_in(0, gp->graft_group),
			gp->graft_ifap->ifa_addr,
			gp->graft_ifap->ifa_link->ifl_name,
			gp->graft_dst,
			time_sec - gp->graft_time);
    } GRAFT_LIST_END(gp, &graft_head);

    (void) fprintf(fd, "\n\tMFC Timeout Queue:\n");
    (void) fprintf(fd, "\t\t   Group           Source       Times Out\n");
    PIM_MFC_LIST(mp, &mfc_head) {
	(void) fprintf(fd, "\t\t%-15A %-15A  %4u secs\n",
		       sockbuild_in(0, mp->mfcp->mfc_group->group_key),
		       sockbuild_in(0, mp->mfcp->mfc_src),
		       mp->mfc_timeout - time_sec);
    } PIM_MFC_LIST_END(mp, &mfc_head);

    (void) fprintf(fd, "\n");
}


/*
 *	Initialize static variables
 */
void
pim_var_init()
{
    BIT_RESET(pim_config_status, PIM_ENABLED);

    pim_default_queryinterval = 30;
    pim_default_routertimeout = 3 * pim_default_queryinterval;
    pim_default_prunetimeout = 180;
    pim_default_inactivitytimeout = 180;
    pim_default_graftacktimeout = 60;

	/*
	 * initialize preference values
	 */
    pim_pref_init();

    if (!igmp_all_routers)
	igmp_all_routers = sockdup(sockbuild_in(0, htonl(IGMP_ALL_ROUTERS)));
}


/*
 * initialize PIM socket and PIM task
 */

/*ARGSUSED*/
void
pim_init()
{
    if (BIT_TEST(pim_current_status, PIM_ENABLED)) {
	if (BIT_TEST(pim_config_status, PIM_ENABLED)) {
	/*
	 * was enabled before and still is now
	 *  - reconfig handled above
	 */

	    trace_inherit_global(pim_trace_options, pim_trace_types, (flag_t) 0);
	} else {
	/*
	 * was enabled before but isn't anymore
	 *  - cleanup and terminate pim task
	 */

	    if (pim_task) {
		pim_terminate(pim_task);

		pim_task = (task *) 0;
	    }
	}
    } else {
	if (BIT_TEST(pim_config_status, PIM_ENABLED)) {
	/*
	 * wasn't enabled before but is now
	 *  - start pim task
	 */

	    trace_inherit_global(pim_trace_options, pim_trace_types, (flag_t) 0);
	    if (!pim_task) {
		pim_timer_query = (task_timer *) 0;
		pim_timer_graft = (task_timer *) 0;
		pim_timer_prune = (task_timer *) 0;
		pim_timer_mfc = (task_timer *) 0;
		pim_task = task_alloc("PIM",
				      TASKPRI_PROTO,
				      pim_trace_options);

		pim_task->task_rtproto = RTPROTO_PIM;
		task_set_cleanup(pim_task, pim_cleanup);
		task_set_dump(pim_task, pim_dump);
		task_set_ifachange(pim_task, pim_ifachange);
		task_set_reinit(pim_task, pim_reinit);
		task_set_terminate(pim_task, pim_terminate);
		task_set_flash(pim_task, pim_flash);
		pim_task->task_rtbit = rtbit_alloc(pim_task,
						   FALSE,
						   sizeof (mfc_src_list *),
						   (void_t) 0,
						   pim_tsi_dump);

		if (!task_create(pim_task)) {
		    task_quit(EINVAL);
		}

		igmp_register_recv( IGMP_PROTO_PIM, pim_recv );
		igmp_register_group_change( pim_group_change );
		krt_register_mfc( EADDRNOTAVAIL, pim_mfc_request );
		krt_register_mfc( EADDRINUSE, pim_mfc_request );

		    /*
		     * Set kernel options for turning on Multicast Routing
		     * and duplicate packet detection.
		     */
		igmp_enable_mrouting();
		igmp_enable_asserts();

		pim_router_block_index =
			task_block_init(sizeof (router_list),
			"pim_router_list");
		pim_rpf_block_index =
			task_block_init(sizeof (rpf_list),
			"pim_rpf_list");
		pim_graft_block_index =
			task_block_init(sizeof (graft_list),
			"pim_graft_list");
		pim_prune_block_index =
			task_block_init(sizeof (prune_list),
			"pim_prune_list");
		pim_join_block_index =
			task_block_init(sizeof (join_list),
			"pim_join_list");
		pim_assert_block_index =
			task_block_init(sizeof (assert_list),
			"pim_assert_list");
		pim_mfc_block_index =
			task_block_init(sizeof (mfc_list),
			"pim_mfc_list");

	    }
    	}
    }
    pim_current_status = pim_config_status;
}

