/*
 *  isis_spf.c,v 1.11 1993/01/07 22:39:57 jch Exp
 */

/* %(Copyright.header) */


#define	INCLUDE_ROUTE
#include "include.h"
#include "isis_includes.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */

PROTOTYPE(add_pending, static void, (GRAPH_PT));
PROTOTYPE(delete_pending, static void, (GRAPH_PT));
PROTOTYPE(spf_check_pending, static void, (GRAPH_PT, int, int, GRAPH_PT, AdjacencyEntry *, as_path *));
PROTOTYPE(spf_expire_route, static void, (GRAPH_PT));
PROTOTYPE(summarize_all_ip_reachables, static void, (void));
PROTOTYPE(print_paths, static void, (void));
PROTOTYPE(MakeL2IPlist, static void, (void));
PROTOTYPE(merge_routes, static void, (GRAPH_PT, GRAPH_PT, AdjacencyEntry *, as_path *));

/* 
 * To run both level 1 and level 2 routing, we use a pointer for the
 * hash table, and have 2 separate arrays for the 2 hash tables.  We
 * then set the level by switching the hash table pointer.  When the
 * pending database is empty, we're done with the spf computation.
 */
static GRAPH_PT *spf_tab;
static GRAPH_PT spf_tab_l1[SPF_HASHTAB_SIZE];			/* level 1 shortest path database */
static GRAPH_PT spf_tab_l2[SPF_HASHTAB_SIZE];			/* level 2 shortest path database */
static GRAPH_PT spf_pending_queues[MAX_COST+1]; 		/* pending database */
static struct sumlist *noSummary; 				/* list of level 1 unsummarized IP reachables */
static GRAPH_PT L2DesigSystem; 
static GRAPH_PT OldL2DesigSystem;

static block_t isis_spfnode_block;
static block_t isis_spfaa_block;
static block_t isis_intnode_block;
static block_t isis_ipleaf_block;
static block_t isis_isoleaf_block;
static block_t isis_sumlist_block;

static int cur_min_cost; 				/* save how far we got */
int spf_level = 1; 					/* 1 or 2 ; maybe should use an enum? */
SystemType spfType; 					/* L1IS/L2IS */
static u_long curr_generation = 0;  			/* # of the algorithm run */
static int ip_addr_change = 0; 				/* used to check for ip reachable stuff */
static int iso_addr_change = 0; 			/* number of changes made to gated's ISO tables */
static int gated_changes = 0; 				/* number of changes made to gated's tables */
static int set_l2_ip = 1; 				/* make sure it gets set at least once */
int chainlen = 0; 					/* tuning statistic */
AdjacencyEntry  *OldL2DesigAdj = 0;

/*
 * Some of the route parameter structure doesn't change, and
 * because we use this for every route, we'll just keep one
 * global for now.  
 */
static rt_parms rtparms;

/*
 * Gateway structure used here only to identify protocol
 * as RTPROTO_ISIS and level as L1 or L2.  Every route we 
 * install will point to the appropriate gw_entry as its 
 * gateway.  
 */
gw_entry *isis_gwp[3];
 

/* 
 * STEVE - ick.
 */
unsigned int 
sysid_hash __PF2(sysid, char *,
	   	 addr_type, enum addr_types)
{
	int i;
	unsigned int hashval = 0;

	switch(addr_type) {
		case inet_net: {
			INET_NET *inet_pt = (INET_NET *) sysid;
			/* 
			hashval = inet_pt->addr[0] + (inet_pt->addr[1]<<8) 
				+ (inet_pt->addr[2] <<16) + (inet_pt->addr[3]<<24);
			hashval &= inet_pt->mask[0] + (inet_pt->mask[1]<<8) + 
				(inet_pt->mask[2] <<16) + (inet_pt->mask[3]<<24);
			*/
			hashval = (*((u_long *) inet_pt->addr)) & (*((u_long *) inet_pt->mask));
		}
		break;
		case is_id: {		
			IS_ID *ispt = (IS_ID *) sysid;
			/* 6 mod: unroll comparison */
			hashval =  ispt->addr[0];
			hashval += ispt->addr[1] << 8;
			hashval += ispt->addr[2] << 16;
			hashval += ispt->addr[3] << 24;
			hashval += ispt->addr[4];
			hashval += ispt->addr[5] << 8;
			hashval += ispt->addr[6] << 16;
		}
		break;
		case addr_pref: {	/* level 2 routing: address prefix */
			ADDR_PREF *prpt = (ADDR_PREF *)sysid;
			for (i = 0; i < (prpt->pref_len>>1); i++)
				hashval += prpt->addr[i]<<((i<<3)&0x1f);
			if ( prpt->pref_len % 2 )
				/* length is odd - add in the odd digit */
				hashval += prpt->addr[(prpt->pref_len>>1)] & 0xf0;
		}
		break;
		case es_id: {	
			ES_ID *espt = (ES_ID *)sysid;
			for (i = 0; i < SYSID_SIZE; i++)
				hashval += espt->addr[i]<< ((i<<3)&0x1f);;
		}
		break;
		case area_addr: {	/* level 2 routing: area address */
			AREA_ADDR *prpt = (AREA_ADDR *)sysid;
			for (i = 0; i < prpt->area_len; i++)
				hashval += prpt->addr[i]<< ((i<<3)&0x1f);;
		}
		break;
	}
	hashval %= SPF_HASHTAB_SIZE;
	return hashval;
}

/* 
 * Compare the address pointed to by sysid, of type addr_type,
 * with the address in the graph node pointed to by hashpt.
 * Return 0 if ==, -1 if not, in the style of strcmp.
 */
int 
spf_cmp_addr __PF3(sysid, char *,
		   addr_type, enum addr_types,
		   hashpt, GRAPH_PT)
{
	int i;

	switch(addr_type) {
		case inet_net: {
			INET_NET *inet_pt = (INET_NET *) sysid;
			INET_NET *in2 = &hashpt->ipleaf.Addr;
			long n1,n2; /* nets */
			long m1,m2; /* masks */
			/*
			n1 = inet_pt->addr[0] + (inet_pt->addr[1]<<8) 
				+ (inet_pt->addr[2] <<16) + (inet_pt->addr[3]<<24);
			m1 = inet_pt->mask[0] + (inet_pt->mask[1]<<8) + 
				(inet_pt->mask[2] <<16) + (inet_pt->mask[3]<<24);
			n2 = in2->addr[0] + (in2->addr[1]<<8) 
				+ (in2->addr[2] <<16) + (in2->addr[3]<<24);
			m2 = in2->mask[0] + (in2->mask[1]<<8) + 
				(in2->mask[2] <<16) + (in2->mask[3]<<24);
			*/
			n1 = *((u_long *) inet_pt->addr); 
			m1 = *((u_long *) inet_pt->mask);
			n1 &= m1;
			n2 = *((u_long *) in2->addr); 
			m2 = *((u_long *) in2->mask);
			n2 &= m2;
			return (!((n1==n2) && (m1 == m2)));
			/* note: we are returning 0 for == and 1 for !=, strcmp style */
		}
		break;
		case is_id: {
			IS_ID *ispt = (IS_ID *) sysid;
			return !(
				(hashpt->interior.Addr.addr_t == is_id) &&
				hashpt->interior.Addr.au.is_addr.addr[0] == ispt->addr[0] &&
				hashpt->interior.Addr.au.is_addr.addr[1] == ispt->addr[1] &&
				hashpt->interior.Addr.au.is_addr.addr[2] == ispt->addr[2] &&
				hashpt->interior.Addr.au.is_addr.addr[3] == ispt->addr[3] &&
				hashpt->interior.Addr.au.is_addr.addr[4] == ispt->addr[4] &&
				hashpt->interior.Addr.au.is_addr.addr[5] == ispt->addr[5] &&
				hashpt->interior.Addr.au.is_addr.addr[6] == ispt->addr[6]);
		}
		break;
		case es_id: {
			ES_ID *espt = (ES_ID *) sysid;
			if (hashpt->isoleaf.Addr.addr_t != es_id)
				return -1;
			for (i = 0; i < ES_NID_SIZE; i++)
				if (espt->addr[i] != hashpt->isoleaf.Addr.au.es_addr.addr[i])
					return -1;
			return 0;
		}
		break;
		case area_addr: {	/* level 2 routing: area address */
			AREA_ADDR *prpt = (AREA_ADDR *) sysid;
			if (hashpt->isoleaf.Addr.addr_t != area_addr)
				return -1;
			for (i = 0; i < prpt->area_len; i++)
				if (prpt->addr[i] != hashpt->isoleaf.Addr.au.area_addr.addr[i])
					return -1;
			return 0;

		}
		case addr_pref: {	/* level 2 routing: address prefix */
			ADDR_PREF *prpt = (ADDR_PREF *) sysid;
			if (hashpt->isoleaf.Addr.addr_t != addr_pref)
				return -1;
			for (i = 0; i < prpt->pref_len/2; i++)
				if(  prpt->addr[i] != hashpt->isoleaf.Addr.au.addr_prefix.addr[i])
					return -1;
			if ( prpt->pref_len % 2 )
				/* length is odd - add in the odd digit */
				if ( (prpt->addr[prpt->pref_len/2] & 0xf0) != 
				     (hashpt->isoleaf.Addr.au.addr_prefix.addr[prpt->pref_len/2] & 0xf0) )
					return -1;
			return 0;

		}
		break;
	}
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_INFO,
		     ("unexpected addr_type %d",
		      addr_type));
	return -1;	/* XXX */
}

/* 
 * Copy the address pointed to by sysid, of type addr_type, into
 * the graph node pointed to by hashpt.
 */
static void
spf_copy_addr __PF3(sysid, char *,
		    addr_type, enum addr_types,
		    hashpt, GRAPH_PT)
{
	int i;

	switch(addr_type) {
		case inet_net: {
			INET_NET *ipt = (INET_NET *)sysid;
			INET_NET *ipt2 = &hashpt->ipleaf.Addr;
			*((u_long *) ipt2->addr) = *((u_long *) ipt->addr);
			*((u_long *) ipt2->mask) = *((u_long *) ipt->mask);
		}
		break;
		case is_id: {
			IS_ID *ispt = (IS_ID *)sysid;
			hashpt->interior.Addr.addr_t = addr_type;
			hashpt->interior.Addr.au.is_addr.addr[0] = ispt->addr[0];
			hashpt->interior.Addr.au.is_addr.addr[1] = ispt->addr[1];
			hashpt->interior.Addr.au.is_addr.addr[2] = ispt->addr[2];
			hashpt->interior.Addr.au.is_addr.addr[3] = ispt->addr[3];
			hashpt->interior.Addr.au.is_addr.addr[4] = ispt->addr[4];
			hashpt->interior.Addr.au.is_addr.addr[5] = ispt->addr[5];
			hashpt->interior.Addr.au.is_addr.addr[6] = ispt->addr[6];
		}
		break;
		case es_id: {
			ES_ID *espt = (ES_ID *)sysid;
			hashpt->isoleaf.Addr.addr_t = addr_type;
			for (i = 0; i < ES_NID_SIZE; i++)
				hashpt->isoleaf.Addr.au.es_addr.addr[i] = espt->addr[i];
		}
		break;
		case area_addr: {
			AREA_ADDR *prpt = (AREA_ADDR *) sysid;
			hashpt->isoleaf.Addr.addr_t = addr_type;
			hashpt->isoleaf.Addr.au.area_addr.area_len = prpt->area_len;
			if (prpt->area_len > sizeof(prpt->addr)) {
				char buf[200];
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_INFO,
					     ("area len too long: %s  reset to max",
					      spf_print_addr(buf,(char *) prpt,area_addr)));
				prpt->area_len = sizeof(prpt->addr);
			}
			for (i = 0; i < prpt->area_len; i++)
				hashpt->isoleaf.Addr.au.area_addr.addr[i] = prpt->addr[i];
		}
		break;
		case addr_pref: {	/* level 2 routing: address prefix */
			ADDR_PREF *prpt = (ADDR_PREF *) sysid;
			hashpt->isoleaf.Addr.addr_t = addr_type;
			hashpt->isoleaf.Addr.au.addr_prefix.pref_len = prpt->pref_len;
			if (prpt->pref_len/2 > sizeof(prpt->addr)) {
				char buf[200];
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_INFO,
					     ("pref len too long: %s  reset to max",
					      spf_print_addr(buf,(char *) prpt,addr_pref)));
				prpt->pref_len = sizeof(prpt->addr) *2;
			}
			for (i = 0; i < prpt->pref_len/2; i++)
				hashpt->isoleaf.Addr.au.addr_prefix.addr[i] = prpt->addr[i];
			if (prpt->pref_len % 2)
				/* length is odd - add in the odd digit */
				hashpt->isoleaf.Addr.au.addr_prefix.addr[prpt->pref_len/2] = prpt->addr[prpt->pref_len/2] & 0xf0;
		}
		break;
		default:
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_INFO,
				     ("unexpected addr_type %d",
				      addr_type));
	}
}


/* 
 * Initialize me.
 */
void
isis_spf_init()
{
	int i;

	isis_spfnode_block = task_block_init(sizeof(struct graph_node), "isis_graph_node");
	isis_intnode_block = task_block_init(sizeof(struct interior_node), "isis_interior_node");
	isis_ipleaf_block = task_block_init(sizeof(struct ip_leaf), "isis_ip_leaf");
	isis_isoleaf_block = task_block_init(sizeof(struct iso_leaf), "isis_iso_leaf");
	isis_spfaa_block = task_block_init(sizeof(struct isis_spf_aa), "isis_spf_aa");
	isis_sumlist_block = task_block_init(sizeof(struct sumlist), "isis_sumlist");

	for (i=0; i < SPF_HASHTAB_SIZE; i++) spf_tab_l1[i] = spf_tab_l2[i] = 0;
	for (i=0; i < MAX_COST;i++) spf_pending_queues[i] = 0;

	cur_min_cost = 0;
	L2DesigSystem = 0;
	OldL2DesigSystem = 0;

	bzero((caddr_t) &rtparms, sizeof(rtparms));

	/* create the L1 and L2 gateway structures */
	isis_gwp[1] = gw_init((gw_entry *) 0,
			      RTPROTO_ISIS,
			      isis_task,
			      (as_t) 0, (as_t) 0, (sockaddr_un *) 0, (flag_t) 0);
	isis_gwp[2] = gw_init((gw_entry *) 0,
			      RTPROTO_ISIS,
			      isis_task,
			      (as_t) 0, (as_t) 0, (sockaddr_un *) 0, (flag_t) 0);
}
	
/* 
 * Allocate and initialize a new graph node.
 */
GRAPH_PT  
spf_alloc_init __PF2(sysid, char *,
		     addr_type, enum addr_types)
{
	GRAPH_PT new_pt;

	if (addr_type == inet_net) {
		new_pt = (GRAPH_PT) task_block_alloc(isis_ipleaf_block);
		bzero(new_pt, sizeof(new_pt));
		new_pt->ipleaf.gtype = IPLEAF;
		isisCounters.ipleaf++;
	} else if (addr_type == is_id) {
		new_pt = (GRAPH_PT) task_block_alloc(isis_intnode_block);
		bzero(new_pt, sizeof(new_pt));
		bzero(&new_pt->interior.aa, sizeof(struct isis_spf_aa));
		new_pt->interior.gtype = INTERIOR;
		isisCounters.intnode++;
	} else {
		new_pt = (GRAPH_PT) task_block_alloc(isis_isoleaf_block);
		bzero(new_pt, sizeof(new_pt));
		new_pt->isoleaf.gtype = ISOLEAF;
		isisCounters.isoleaf++;
	}
	spf_copy_addr((char *) sysid, addr_type, new_pt);
	new_pt->g.internal_cost = -1;
/*
	if (addr_type == is_id) {
		new_pt->interior.aa = (struct isis_spf_aa *) task_block_alloc(isis_spfaa_block);
		bzero(new_pt->interior.aa, sizeof(struct isis_spf_aa));
		isisCounters.spfAA++;
	}
*/

	return new_pt;
}

/* 
 * Get the database entry for the given system id.  If the sysid isn't
 * found and allocNew is 1, allocate a new node and initialize it.  If
 * allocNew is 0, just return NULL.
 */
GRAPH_PT 
get_graph_entry __PF3(sysid, char *,
		      addr_type, enum addr_types,
		      allocNew, int)
{
	GRAPH_PT gpt;
	int hindex;

	gpt = spf_tab[hindex = sysid_hash(sysid, addr_type)];

	while (gpt) {
		chainlen++;
		if (!spf_cmp_addr(sysid, addr_type, gpt)) return gpt;
		gpt = gpt->g.hash_chain;
	}

	/* sysid wasn't found */
	if (!allocNew) return (GRAPH_PT) 0;

	/* allocate a new one. */
	gpt = spf_alloc_init(sysid, addr_type);
	gpt->g.hash_chain = spf_tab[hindex];
	spf_tab[hindex] = gpt;

	return gpt;
}

/* 
 * Check for a route to some node's (upstream's) neighbor in the 
 * pending queue. If a worse route is already pending, 
 * delete it and add the new route (the one through upstream).  If
 * a route of equal cost is pending, select the best set of
 * routes and merge them into the pending database (currently 
 * |set| == 1).  If no route is pending, add this new one to
 * the pending database.  This routine only supports the 
 * default metric for now.
 */ 
static void
spf_check_pending __PF6(dbEntry, GRAPH_PT, 		/* the route we had for dest (could be freshly initialized) */
		  	internal_cost, int,		/* internal cost for the new route */
		  	external_cost, int, 		/* external cost for the new route (or 0 if only internal) */
		  	upstream, GRAPH_PT, 		/* the destination's upstream neighbor */
		  	adj_pt, AdjacencyEntry *,	/* and its corresponding adjacency if direct (one of our */
							/* neighbors, added by init_paths) */
		  	asp, as_path *)
{
	static void print_route();
	int destType = dbEntry->g.gtype;

#define	UseNewRoute \
	dbEntry->g.internal_cost = internal_cost; \
	dbEntry->g.extern_cost = external_cost; \
	if (destType == IPLEAF) dbEntry->ipleaf.asp = asp; \
	else if (destType == ISOLEAF) dbEntry->isoleaf.asp = asp; \
	if (destType == INTERIOR) { \
		if (adj_pt)  \
			dbEntry->interior.adj = adj_pt; \
		else if (upstream) \
			/* upstream neighbors must be interior */ \
			dbEntry->interior.adj = upstream->interior.adj; \
	} \
	dbEntry->g.parent = upstream; \
	if (dbEntry->g.pend_q != (GRAPH_PT) 0) \
		delete_pending(dbEntry); \
	add_pending(dbEntry)

	if (dbEntry->g.generation < curr_generation) {
		/* no existing route - use the new one (C.2.6.e) */
		dbEntry->g.generation = curr_generation;
		switch (destType) {
		case IPLEAF:
			/* save the old exit point */
			dbEntry->ipleaf.oldparent = dbEntry->g.parent;
			break;
		case INTERIOR:
			/* save the old adjacency */
			dbEntry->interior.oldadj = dbEntry->interior.adj; 
			break;
		case ISOLEAF:
			dbEntry->isoleaf.oldparent = dbEntry->g.parent;
			break;
		}
/*
if (dbEntry->g.pend_q != (GRAPH_PT) 0) {
	trace(TR_ISIS, 0, "newgen: following node already in pending database:");
	(static void) print_route(dbEntry, 0, 0);
}
*/
		UseNewRoute;
		return;
	}

	if ((dbEntry->g.extern_cost == 0) && (external_cost != 0)) {
		/* 
		 * Existing route is internal and new route is
		 * external - use the existing one.
		 */
		return;
	}

	if ((dbEntry->g.extern_cost != 0) && (external_cost == 0)) {
		/* 
		 * Existing route is external and new route is
		 * internal - use the new one.
		 */
		UseNewRoute;
		return;
	}

	if (dbEntry->g.extern_cost == external_cost) {
		/* 
		 * Either both are internal (external cost is 0) or 
		 * both have same external cost - choose route with 
		 * best internal cost.
		 */
		if (dbEntry->g.internal_cost > internal_cost) {
			/* new route is less costly - see C.2.6.d.4 */
			/* delete_pending(dbEntry);*/ /* delete the old route */
			UseNewRoute;
		} else if (dbEntry->g.internal_cost == internal_cost) {
			/* equal cost route - add to list - see C.2.6.d.1.  XXX - inelegant; needs work */
			if (!adj_pt) {
				/* trace(TR_ISIS, LOG_INFO, "IS-IS preferring existing route of equal cost"); */
				if (upstream == dbEntry->g.parent) {
					/* same upstream neighbor, so probably just an AS path change */
					if (destType != INTERIOR) {
						if (destType == IPLEAF) 
							dbEntry->ipleaf.asp = asp;
						else if (destType == ISOLEAF) 	
							dbEntry->isoleaf.asp = asp;
						trace_tf(isis_trace_options,
							 TR_NORMAL,
							 0,
							 ("as path change in SPF"));
					} else {
					    trace_log_tf(isis_trace_options,
							 0,
							 LOG_ERR,
							 ("refresh on interior neighbor?"));
					}
				}
			} else {
				if (upstream == dbEntry->g.parent) {
					/* same upstream neighbor, so probably just an AS path change */
					if (destType != INTERIOR) {
						if (destType == IPLEAF) 
							dbEntry->ipleaf.asp = asp;
						else if (destType == ISOLEAF) 	
							dbEntry->isoleaf.asp = asp;
						trace_tf(isis_trace_options,
							 TR_NORMAL,
							 0,
							 ("as path change in SPF"));
					} else {
					    trace_log_tf(isis_trace_options,
							 0,
							 LOG_ERR,
							 ("refresh on interior neighbor?"));
					}
				} else if (destType == INTERIOR) merge_routes(dbEntry, upstream, adj_pt, asp);
			}
		}
		return;
	}

	if (dbEntry->g.extern_cost > external_cost) {
		/* 
		 * By now we know that both routes are external with
		 * different external costs, so we choose the new one 
		 * iff it has a lower external cost.
		 */
		UseNewRoute;
	}
}

/*
 * Check for two way connectivity between node and its neighbor.
 */
int
isis_2way_check __PF4(node, octet *, 		/* who we should look for */
		      neighbor, octet *, 	/* in whose LSPs we should look */
		      neighborType, int,	/* ISN or INN */
		      addrLen, int)	
{
	octet *addr_pt;				/* who we found in the LSP */
	struct subfield_iter_state subf_iter;	/* internal LSP parsing placekeeper */

	addr_pt = get_first_nodeaddr(&subf_iter, (IS_ID *) neighbor);
	while (addr_pt) {
		if ((neighborType == subf_iter.lsp_iter.selector) &&
		    equalID(node, addr_pt, addrLen)) {
			/* we found node listed in neighbor's LSPs */
			return(1);
		}
		addr_pt = get_next_nodeaddr(&subf_iter);
	}
	return(0);
}

/* 
 * Add a destination to the PATHS database.  The node should be
 * the least cost path from the pending queue (as returned by
 * get_first_pending() ).  Add all of its neighbors (excluding
 * those ISNs and INNs which fail the two-way connectivity check).
 */
static void
add_node __PF1(nodept, GRAPH_PT) 	/* the destination to add */
{
	int costToNode;		/* cost to get to this destination */
	octet *addr_pt;		/* this destination's neighbor */
	GRAPH_PT dbEntry;	/* pending database entry (may be new) for this destination's neighbor */
	int costToNeighbor;	/* internal cost from this destination to its neighbor */
	struct subfield_iter_state subf_iter;	/* internal LSP parsing placekeeper */
	int externCost;		/* external cost from this destination to its neighbor (e.g., prefix) */
	int neighborType;	/* type of neighbor (e.g., ESN, ISN, INN, ...) */
	isis_asp asp;		/* attributes of current reachables */
	if_addr *ifap;

	nodept->g.generation = curr_generation;
	if (nodept->g.gtype != INTERIOR) {
		/* not an IS - no need for further processing */
		return;
	}

	/* 
	 * IS node - add its neighbors (from its LSP) to pending queue.
	 * we need to iterate through the lsp for nodept.
	 */
	costToNode = nodept->interior.internal_cost; 
	addr_pt = get_first_nodeaddr(&subf_iter, (IS_ID *) &nodept->interior.Addr.au);

	/* this sets the LSP thing so we can check it - STEVE XXX - huh? */
	if (systemType == L1IS && !L2DesigSystem && addr_pt) {
		if (subf_iter.lsp_iter.cur_lsp && 
		   ((((struct is_lsp_header *)subf_iter.lsp_iter.cur_lsp)->flags &0x3) == 0x3)) {
			L2DesigSystem = nodept;
		}
	}
	while (addr_pt) {
		neighborType = subf_iter.lsp_iter.selector;
		if (neighborType == IPInterDomInfo) {
			/* IDRPi - save the attributes for the reachables which follow */
			bcopy(&subf_iter.attributes, &asp, sizeof(isis_asp));
			/* trace(TR_NORMAL, 0, "found attribute v.%d ID %d", asp.version, * (u_long *) &asp.data); */
			goto nextNeighbor;
		}
		/* 2 way connectivity check - 10589 7.2.8.2 */
		if ((neighborType == IS_NEIGHBOR_SELECTOR) &&
		    (!isis_2way_check((octet *) &nodept->interior.Addr.au, addr_pt, neighborType, sizeof(IS_ID)))) {
			if (!is_pseudonode(&nodept->interior.Addr.au, nodept->interior.Addr.addr_t) &&
			    !is_pseudonode(addr_pt, nodept->interior.Addr.addr_t)) {
				/* 
				 * Suppress messages about pseudonodes.  A node's pseudonode might be advertised
				 * as reachable by the node, but if it in turn has nothing to advertise, there
				 * won't be any LSPs for that pseudonode, which is just fine.  We won't calculate
				 * reachability to the pseudonode until it has something to advertise.
				 */
				char s1[40], s2[40];
				spf_print_addr(s1, (char *) &nodept->interior.Addr.au, nodept->interior.Addr.addr_t);
				spf_print_addr(s2, addr_pt, nodept->interior.Addr.addr_t);
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("IS-IS two way connectivity check failed - assuming link transient"));
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("  (L%d %s -> %s UP, %s -> %s DOWN)",
					      spf_level,
					      s1,
					      s2,
					      s2,
					      s1));
			}
			goto nextNeighbor;
		}
		costToNeighbor = subf_iter.metrics[0]; 
		externCost = 0;
		dbEntry = get_graph_entry((char *) addr_pt,subf_iter.addr_type, 1);
		switch (neighborType) {
		case ES_NEIGHBOR_SELECTOR:
			if (equalID(systemID, addr_pt, sizeof(systemID))) {
				/* don't add ourselves as ES */
				break;	
			}
		case IN_EXTERN_SELECTOR:
		case PREFIX_NEIGHBOR_SELECTOR:
			if (costToNeighbor & 0x40) {
				/* this is an external metric */
				externCost = costToNeighbor & 0xBF;
				costToNeighbor = 0;
			}
		case IS_NEIGHBOR_SELECTOR:
		case AREA_ADDR_SELECTOR:
			if (neighborType == AREA_ADDR_SELECTOR) {
				/* remember this IS's areas for route table updates (to its advertised ESs) later */
				struct isis_spf_aa *aa = &nodept->interior.aa;
				aa->areas[aa->numAAs].area_len = ((AREA_ADDR *) addr_pt)->area_len;
				bcopy(((AREA_ADDR *) addr_pt)->addr, aa->areas[aa->numAAs].addr, 
				      ((AREA_ADDR *) addr_pt)->area_len);
				aa->numAAs++;
			}
			spf_check_pending(dbEntry, costToNode+costToNeighbor, externCost, nodept, 
					  (AdjacencyEntry *) NULL, (as_path *) NULL);
			break;
		case IN_INTERN_SELECTOR:
			/* don't add one of my subnets as reachable */	
			IF_ADDR(ifap) {
				if (BIT_TEST(ifap->ifa_state, IFS_UP)
				    && (socktype(ifap->ifa_addr) == AF_INET) && 
				    (* (u_long *)addr_pt == (u_long) sock2ip(ifap->ifa_net)))
					break;
			} IF_ADDR_END(ifap);
			if (!ifap) 
				spf_check_pending(dbEntry, costToNode+costToNeighbor, externCost, nodept, 
						  (AdjacencyEntry *) NULL, (as_path *) NULL);
			break;
		}
		nextNeighbor:
		addr_pt = get_next_nodeaddr(&subf_iter);
	}
}

/*
 * This implements C.2.6.d.(1,2) for maximumPathSplits = 1 and
 * removal of excess paths as specified in section 7.2.7.  This
 * is only called for interior nodes.
 * STEVE XXX - needs support for maximumPathSplits > 1.
 */
#define	replace_rt(oldrt, newrt, newadj, asp) \
		oldrt->interior.adj = newadj; \
		/* oldrt->g.asp = asp; */ \
		oldrt->g.parent = newrt; 
		
static void
merge_routes __PF4(node, GRAPH_PT, 
	     	   newroute, GRAPH_PT, 
	     	   adj, AdjacencyEntry *,
	     	   asp, as_path *)
{
	int cmp_val = 0;
	CircuitEntry *currCirc, *newCirc;
	u_char *currCid, *newCid;

	if (!adj || !node->interior.adj) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("refusing to merge route without adjacency"));
		isisDie(); 
	}

	/* 
	 * Compare adjacency types - ES preferred over others.
	 * STEVE - need to prefer reachable address prefix adjacencies
	 * for level 2 - same sort of check required.
	 */
	if (node->interior.adj->adjacencyType == ES && adj->adjacencyType != ES)
		/* prefer the existing route (with ES adjacency) */
		return; 
	if (adj->adjacencyType == ES && node->interior.adj->adjacencyType != ES) {
		/* prefer the new route (with ES adjacency) */
		replace_rt(node, newroute, adj, asp);
		return;
	}
	/* 
	 * Compare the neighbor IDs - lowest ID preferred.
	 */
	cmp_val = compareID(node->interior.adj->neighborSysID, adj->neighborSysID, sizeof(SystemID6));
	if ( cmp_val < 0)
		/* prefer existing route, with lower neighbor ID */
		return;
	if (cmp_val > 0) {
		/* prefer the new route (with lower neighbor ID) */
		replace_rt(node, newroute, adj, asp);
		return;
	}
		
	/* 
	 * Compare circuit ID - lowest circuit ID preferred.
	 */
	currCirc = node->interior.adj->circuit;
	newCirc = adj->circuit;
	if (spf_level == 1) {
		currCid = currCirc->circuitId;
		newCid = newCirc->circuitId;
	} else {
		currCid = (currCirc->circuitType==Pt2Pt) ? currCirc->circuitId : currCirc->l2CircuitId;
		newCid = (newCirc->circuitType==Pt2Pt) ? newCirc->circuitId : newCirc->l2CircuitId;
	}
	cmp_val = compareID(currCid,newCid,sizeof(SystemID7));
	if ( cmp_val < 0) 
		/* prefer existing route, with lower circuit ID */
		return;
	if (cmp_val > 0) {
		/* prefer new route (with lower circuit ID) */
		replace_rt(node, newroute, adj, asp);
		return;
	}

	/* 
	 * Compare LAN addresses - prefer lower SNPA address. 
	 * STEVE - need this one eventually - use adjacencies' 
	 * neighborMAC fields.
	 */

}

/*
 * Returns true if destination is a pseudonode, false otherwise.
 */
int 
is_pseudonode __PF2(node, octet *,
		    nodeType, int)
{
	if ((nodeType==is_id) && (node[6] != 0)) 
		return 1;
	else 
		return 0;
}

/* 
 * Add node to pending database (priority queue).
 */
static void
add_pending __PF1(node, GRAPH_PT)
{
	int indx;

	indx = node->g.internal_cost;
	node->g.pend_q = spf_pending_queues[indx];
	spf_pending_queues[indx] = node;
}
	
/* 
 * Delete node from pending database; this is done before a 
 * lower cost route is about to be added.
 */
static void
delete_pending __PF1(pn, GRAPH_PT)
{
	int indx = pn->g.internal_cost;
	GRAPH_PT prev = spf_pending_queues[indx];

	if (prev == pn) {
		/* pn is at head; just set head to next */
		spf_pending_queues[indx] = pn->g.pend_q;
	} else { 
		/* find the element */
		while (prev && prev->g.pend_q != pn) {
			prev = prev->g.pend_q;
		}
		if (prev) prev->g.pend_q = prev->g.pend_q->g.pend_q;
		else {
			/* inet external reach hack: we may try to delete from an empty
			queue- in which case, don't report an error */
			if (pn->g.internal_cost > cur_min_cost) /* should be there regardless */
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_INFO,
					     ("error: element %x not found on pend queue",
					      pn));
		}
	}
}
	
/* 
 * Extract the shortest path route from the pending queue.
 * XXX - this should return pseudonodes before non-pseudonodes.
 */
GRAPH_PT
get_first_pending()
{
	GRAPH_PT min_node;

	while (spf_pending_queues[cur_min_cost] == 0) {
		cur_min_cost++;
		if (cur_min_cost >= MAX_COST) return (GRAPH_PT) 0;
	}
	min_node = spf_pending_queues[cur_min_cost];
	spf_pending_queues[cur_min_cost] = min_node->g.pend_q;

	return min_node;
}

/*
 * Initialize the PATHS database (put me in it) and the
 * pending database (put my neighbors in it).  For the
 * pending database, we'll just suck everything needed out
 * of the circuit and adjacency databases.
 */
static void
init_paths __PF1(home, GRAPH_PT)
{
	CircuitEntry *c;
	GRAPH_PT gpt;
	int cost;
	struct isis_ipr *ipreach;		/* manually configured IP reachable addresses (including summary addresses) */
	INET_NET ipNeighbor;			/* used to add host routes to myself and my IP neighbors */
	int i, k;

	* (u_long *) ipNeighbor.mask = 0xffffffff;

	home->g.internal_cost = 0;
	home->g.parent = 0;			/* this is the root node, so no parent */
	home->g.generation = curr_generation;	/* stick it in there */

	/* iterate through each of my circuits */
	for (i=0; i < MaximumCircuits; i++) {
		AdjacencyEntry *adj;
		GRAPH_PT DRnode;
		AdjacencyEntry *DRAdj = NULL;		/* the adjacency with the DR (if it exists) */
		u_char *DRLanID = NULL;			/* the LAN ID of the DR (if it exists) */
		IS_ID is_addr;

		if ((c = circuitList[i]) == NULL) continue;

		/* 
		 * Add home IP addresses with cost 0.  This prevents me from 
		 * calculating routes to myself through my neighbors.
		 */
		if (ip_supported) {
			for (k=1; k<=c->ipAddrs.cnt; k++) {
				* (u_long *) ipNeighbor.addr = c->ipAddrs.addrs[k-1].s_addr;
				gpt = get_graph_entry((char *) &ipNeighbor, inet_net, 1);
				gpt->g.internal_cost = 0;
				gpt->g.parent = 0;				
				gpt->g.generation = curr_generation;
			}
		}

		if (spf_level == 1 && c->manualL2Only) continue;	/* skip level 2 only on level 1 */
		
		cost = (spf_level == 2) ? c->l2Metric.defalt : c->l1Metric.defalt;
		if (c->circuitType == Broadcast) {
			/* get the DR's ID */
			DRLanID = (spf_level == 1) ? c->circuitId : c->l2CircuitId;
		}

		if ( c->isAdjs && !(DLListEmpty(&c->isAdjs->links)) ) {
			IterateDLListForw(adj,&c->isAdjs->links, AdjacencyEntry *) {
				/* examine each of my adjacencies, building the pending database */
				bcopy((caddr_t) adj->neighborSysID, (caddr_t) is_addr.addr, 6);
				is_addr.addr[6] = 0;
				/* avoid expired adjacencies */
				if (adj->state != AdjUp) 
					continue;
				/* avoid crosstalk */
				switch(adj->adjacencyType) {
				case L1IS:
					if (spfType != L1IS) continue;
					break;
				case L2IS:
					/* STEVE - >really< avoid crosstalk */
					/* if ((spfType == L1IS) && (adj->level2Only)) continue; */
					if ((spfType == L1IS) && 
					    ((c->circuitType == Broadcast) || adj->level2Only)) continue;
					break;
				default:
					continue;	
				}
				if ((c->circuitType == Broadcast) && equalID(adj->neighborSysID, DRLanID, 6)) {
					/* we found the DR's adjacency */
					char scratch[40];
					DRAdj = adj;
					strcpy(scratch, IDToStr(DRAdj->neighborSysID,6));
					/* trace(TR_NORMAL, LOG_INFO, "found DR adj neighSysID %s/LAN ID %s",
					      scratch, IDToStr(DRAdj->desigLANID, 7)); */
				}
				gpt = get_graph_entry((char *) is_addr.addr,is_id, 1);	/* find/allocate neighbor's node */
				spf_check_pending(gpt,cost,0,home,adj,(as_path *) NULL);/* throw it into the pending database */

				/* add neighbor's IP interface addresses if appropriate */
				if (ip_supported) {
					for (k=1; k<=adj->ipaddrs.cnt; k++) {
						* (u_long *) ipNeighbor.addr = adj->ipaddrs.addrs[k-1].s_addr;
						gpt = get_graph_entry((char *) &ipNeighbor, inet_net, 1);
						spf_check_pending(gpt, cost, 0, home, adj, (as_path *) NULL);
					}
				}
			}
		}

		/* add designated router (if one is elected) to the pending database too */
		if (c->circuitType == Broadcast) {
			if ((spf_level == 1) ? c->l1DR : c->l2DR) {
				/* we're the DR for this circuit */
				DRnode = get_graph_entry((char *) DRLanID, is_id, 1);	
				DRnode->g.internal_cost = 0;
				DRnode->g.generation = curr_generation;
				DRnode->g.parent = 0;
			} else if (!equalID(systemID, (spf_level == 1) ? c->circuitId : c->l2CircuitId, 6)) {
				/* 
				 * Another IS is the DR for this circuit - add the mother if 
				 * we're not isolated.
				 */
				if (!isolated(c)) {
					bcopy((caddr_t) DRLanID, (caddr_t) is_addr.addr, 7);
					gpt = get_graph_entry((char *) is_addr.addr,is_id, 1);	
					spf_check_pending(gpt,cost,0,home,DRAdj, (as_path *) NULL);
				}
			} else {
				/* no DR elected yet */
				/* trace(TR_NORMAL, 0, "No DR elected for circuit %s", c->name); */
			}
		}

		/* 
		 * Add ES also, but don't add ES's for lan circuits.
		 * That info comes from pseudonode's LSP, and we just
		 * added the pseudonode to the pending database.
		 */
		if (spfType==L1IS && c->circuitType != Broadcast && c->esAdjs && !(DLListEmpty(&c->esAdjs->links)) ) {
			IterateDLListForw(adj,&c->esAdjs->links, AdjacencyEntry *) {
				ES_ID es_addr;
				int m;
				assert(adj->adjacencyType == ES);
				/* add each of the ES neighbors */
				for (m=0; m<adj->numIds; m++) {
					bcopy((caddr_t) &adj->neighborInfo[m*ES_NID_SIZE], (caddr_t) es_addr.addr, ES_NID_SIZE);
					gpt = get_graph_entry((char *) es_addr.addr, es_id, 1);
					spf_check_pending(gpt, cost, 0, home, adj, (as_path *) NULL);
				}
			}		
			/* need to check for level 2 enabled reachable addresses */
		}
	}

	/* add addresses on manually configured ip reachable list */
	for (ipreach = IPRList; ipreach; ipreach = ipreach->next) {
		int internCost = 0;
		int externCost = 0;
		if (ipreach->level != spf_level)
			continue;
		if (ipreach->type == IPSumReachCode) {	
			/* remember this summary address for SPF later */
			ipreach->inUse = FALSE;
			continue; 		
		}
		gpt = get_graph_entry((char *)&ipreach->addr,inet_net, 1);
		if (ipreach->type == IPExtReachCode) 
			externCost = ipreach->metric.defalt;
		else 
			internCost = ipreach->metric.defalt;
		spf_check_pending(gpt, internCost, externCost, home, (AdjacencyEntry *) NULL, (as_path *) NULL);
	}

	/* 
	 * Install local areas for level 2 with 0 cost and no route,
	 * so no route gets installed.
	 * STEVE XXX - do this for level 1 as well.
	 */
#ifdef	notdef
	if (spf_level==2) {
#endif
		for (i = 0; i < systemAreaAddrs.count; i++) {
			AreaAddr *Apt;
			Apt = retrieveAreaAddr(systemAreaAddrs.areaAddr[i]);
			gpt = get_graph_entry((char *) Apt, area_addr, 1);
			spf_check_pending(gpt, 0, 0, home, 0, (as_path *) NULL);
		}
#ifdef	notdef
	}
#endif
}

/* 
 * Run the SPF algorithm.
 */
static void
run_isis_spf __PF1(home_node, GRAPH_PT)
{
	GRAPH_PT node;
	int numIS, numES, numPref, numAA, numIP;
        utime_t startTime, endTime;
	int totalms;

	IFTRACE(T_TRSPF)
		TIMER_PEEK();
		startTime = utime_current;	/* struct copy */
	ENDTRACE

	chainlen = numIS = numES = numPref = numAA = numIP = 0;
	curr_generation++;
	cur_min_cost = 0;
	if (systemType == L1IS) {
		OldL2DesigSystem = L2DesigSystem;
		if (L2DesigSystem) OldL2DesigAdj = L2DesigSystem->interior.adj;
		L2DesigSystem = 0;
	}
	init_paths(home_node);
	while ((node=get_first_pending()) != 0) {
		if (node->g.gtype == IPLEAF) numIP++;
		else if (node->g.gtype == INTERIOR) numIS++;
		else {
			switch (node->isoleaf.Addr.addr_t) {
			case es_id: numES++; break;
			case area_addr: numAA++; break;
			case addr_pref: numPref++; break;
			default: ;
			}
		}
		add_node(node);
	}
	IFTRACE(T_TRSPF)
	    TIMER_PEEK();
	    endTime = utime_current;	/* struct copy */
	    totalms = (endTime.ut_sec - startTime.ut_sec) * 1000 + (endTime.ut_usec - startTime.ut_usec) / 1000;
	    trace_only_tf(isis_trace_options,
			  0,
			  ("IS-IS SPF L%d complete - %d ms, %d chain len, %d IS, %d ES, %d ISO prefixes, %d areas, %d IP reachables", 
			   spf_level,
			   totalms,
			   chainlen/(numIS+numES+numPref+numAA+numIP), 
			   numIS,
			   numES,
			   numPref,
			   numAA,
			   numIP));
	ENDTRACE
}

static void
print_route __PF3(gpt, GRAPH_PT,
		  logPri, int,
		  printOld, int)
{
	char pbuf[100], pbuf2[100];
	GRAPH_PT route_pt;
	GRAPH_PT exitpoint = (GRAPH_PT) NULL; 
	char *addr, *mask;
	enum addr_types atype;
	AdjacencyEntry *adj;
	int ecost = 0;

	/* make gcc happy */
	addr = mask = (char *) 0;
	adj = (AdjacencyEntry *) 0;
	atype = inet_net;

	switch (gpt->g.gtype) {
	case IPLEAF:
		addr = (char *) gpt->ipleaf.Addr.addr;
		mask = (char *) gpt->ipleaf.Addr.mask;
		/* atype = inet_net; */
		ecost = gpt->ipleaf.extern_cost;
		if (!printOld) {
			if (ecost) exitpoint = gpt->ipleaf.parent;
			adj = (gpt->ipleaf.parent) ? gpt->ipleaf.parent->interior.adj : (AdjacencyEntry *) NULL;
		} else {
			if (ecost) exitpoint = gpt->ipleaf.oldparent;
			adj = (gpt->ipleaf.oldparent) ? gpt->ipleaf.oldparent->interior.oldadj : (AdjacencyEntry *) NULL;
		}
		break;
	case ISOLEAF:
		addr = (char *) &gpt->isoleaf.Addr.au;
		mask = (char *) NULL;
		atype = gpt->isoleaf.Addr.addr_t;
		ecost = gpt->isoleaf.extern_cost;
		if (!printOld) {
			if (ecost) exitpoint = gpt->isoleaf.parent;
			adj = (gpt->isoleaf.parent) ? gpt->isoleaf.parent->interior.adj : (AdjacencyEntry *) NULL;
		} else {
			if (ecost) exitpoint = gpt->isoleaf.oldparent;
			adj = (gpt->isoleaf.oldparent) ? gpt->isoleaf.oldparent->interior.oldadj : (AdjacencyEntry *) NULL;
		}
		break;
	case INTERIOR:
		addr = (char *) &gpt->interior.Addr.au;
		mask = (char *) NULL;
		atype = is_id;
		if (!printOld)
			adj = gpt->interior.adj;
		else
			adj = gpt->interior.oldadj;
		break;
	}
		
	if (mask) 
		tracef("  %s/%s (I.%d", spf_print_addr(pbuf,addr,atype), spf_print_addr(pbuf2,mask,atype), gpt->g.internal_cost);
	else
		tracef("  %s (I.%d", spf_print_addr(pbuf, addr, atype), gpt->g.internal_cost);
	if (ecost) tracef("/E.%d)", ecost);
	else tracef(")");
	if (exitpoint) tracef(" B%s", spf_print_addr(pbuf, (char *) &exitpoint->interior.Addr.au, is_id));
	if (atype == inet_net && adj && adj->ipaddrs.cnt) {
		spf_print_addr(pbuf, (char *) &adj->ipaddrs.addrs[0], inet_net);
		tracef(" via %s %s", adj->circuit->name, pbuf);
	} else if (adj && adj->circuit) {
		tracef(" via %s.",adj->circuit->name);
		if (adj->adjacencyType == ES)
			tracef("P2P");
		else 
			tracef("%s", IDToStr(adj->neighborSysID, 6));
		if (adj->circuit->circuitType == Broadcast) {
			tracef(" - (SNPA %s)",IDToStr(adj->neighborMAC, 6));
		} 
	} else if (gpt->g.internal_cost != 0) {
		if (!adj) {
			if (gpt->g.gtype == INTERIOR) tracef("no adjacency present");
		} else if (adj && !adj->circuit) {
			logPri = LOG_ERR;
			tracef("IS-IS ERROR: - no circuit associated with adjacency");
		} else  {
			logPri = LOG_ERR;
			tracef("IS-IS ERROR: - I'm aghast with confusion");
		}
		trace_log_tf(isis_trace_options,
			     0,
			     logPri,
			     (NULL));
		return;
	}
	trace_log_tf(isis_trace_options,
		     0,
		     logPri,
		     (NULL));
			
	IFTRACE(T_ROUTE3)
	route_pt = gpt->g.parent;
	if (route_pt) tracef("    path = ");
	else tracef("    path = (home node)");
	while (route_pt) {
		tracef("%s ", spf_print_addr(pbuf, (char *) &route_pt->interior.Addr.au, route_pt->interior.Addr.addr_t));
		route_pt = route_pt->interior.parent;
	}
	trace_log_tf(isis_trace_options,
		     0,
		     logPri,
		     (NULL));
	ENDTRACE
}

/* 
 * Update the kernel route for the es/is/network indicated by gpt.
 */
static void
isis_update_route __PF1(gpt, GRAPH_PT)
{
	sockaddr_un *maskp;		/* the mask */
	sockaddr_un *dest;		/* the destination */
	sockaddr_un *nexthops[RT_N_MULTIPATH];	/* the next hops */
	int numNexthop = 0;		/* number of next hops */
	byte scratch[ISO_MAXADDRLEN];	/* some scratch space for concatenating AA and system ID */
	byte scratch2[ISO_MAXADDRLEN];	/* some more scratch space for concatenating AA and system ID */
	AreaAddrList *nAAlist;		/* list of neighbor's area addresses from gpt->adj */
	AreaAddr *nAA, *AA;		/* area address for neighbor and for me */
	int iso_len = 0;		/* ISO destination length in semi-octets */
	GRAPH_PT is;			/* IS which is advertising an ES */
	AdjacencyEntry *adj;
	int isHostRoute = 0;		
	int i, j, k;
#define	nexthop	nexthops[0]		

	/* make gcc happy */
	maskp = dest = (sockaddr_un *) 0;

	/* if this is a leaf node, take the adjacency from its parent */
	if (gpt->g.gtype != INTERIOR) {
		/* check the following because this node might just be me (not that I really should be in there) */
		adj = (gpt->g.parent) ? gpt->g.parent->interior.adj : (AdjacencyEntry *) NULL;
	} else adj = gpt->interior.adj;
	if (!adj) {
		/* there's no new route, so just toss the old one */
		spf_expire_route(gpt);
	} else {
		bzero(nexthops, sizeof nexthops);
		switch (gpt->g.gtype) {
		case IPLEAF:
			if (adj->ipaddrs.cnt) {
				/* IP route with existing next hop */
				dest = sockbuild_in(0, * (u_long *) gpt->ipleaf.Addr.addr);
				if (* (u_long *) gpt->ipleaf.Addr.mask == INADDR_HOSTMASK) {
					/* maskp = (sockaddr_un *) 0; */
					maskp = inet_mask_host;
					isHostRoute = 1;
				} else 
					maskp = inet_mask_locate(* (u_long *) gpt->ipleaf.Addr.mask);
				for (i=0; i<adj->ipaddrs.cnt; i++) {
					sockaddr_un *tmp;
					tmp = sockbuild_in(0, * (u_long *) &(adj->ipaddrs.addrs[i]));
					if (if_withdst(tmp)) {
						/* we have an interface over which we can send stuff */
						nexthops[numNexthop++] = tmp;
					}
				}
				/* trim off any extra next hops */
				numNexthop = min(numNexthop, RT_N_MULTIPATH);
				ip_addr_change++;
			} else {
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("IS-IS update: following L%d route uses adjacency with missing IP neighbor - not installed:", 
					      spf_level));
				print_route(gpt, LOG_ERR, 0);
			}
			break;
		case ISOLEAF:
			if (gpt->isoleaf.Addr.addr_t == addr_pref) {
				iso_len = gpt->isoleaf.Addr.au.addr_prefix.pref_len;
				dest = sockbuild_iso((byte *) gpt->isoleaf.Addr.au.addr_prefix.addr, (iso_len+1) >> 1);
			} else if (gpt->isoleaf.Addr.addr_t == area_addr) {
				iso_len = gpt->isoleaf.Addr.au.area_addr.area_len << 1;
				dest = sockbuild_iso((byte *) gpt->isoleaf.Addr.au.area_addr.addr, iso_len);
			} else {
				/* 
				 * It's an ES, so generate routes for each of its IS's areas.  The
				 * IS is available from gpt->parent.  STEVE XXX - just take first area
				 * for now.
				 */
				for (k=0; k < MaximumCircuits; k++) {
					/* don't add a route to a neighboring IS because ES-IS already took care of it */
					CircuitEntry *c;
					AdjacencyEntry *isadj;
					if ((c = circuitList[k]) == NULL) continue;
					if (c->isAdjs && !(DLListEmpty(&c->isAdjs->links)) ) {
						IterateDLListForw(isadj,&c->isAdjs->links, AdjacencyEntry *) {
							if (equalID(&isadj->neighborSysID,
							    gpt->isoleaf.Addr.au.es_addr.addr,ES_NID_SIZE) 
							   && (isadj->state == AdjUp)) {
									IFTRACE(T_ROUTE1)
										trace_only_tf(isis_trace_options,
											      0,
											      ("  ES-IS duplicate ignored"));
									ENDTRACE
									return;
							}
						}		
					}
				}
				if ((is = gpt->isoleaf.parent) && (is->interior.aa.numAAs)) {
					/* suck out the areas and build the destinations */
					iso_len = is->interior.aa.areas[0].area_len;
					bcopy(is->interior.aa.areas[0].addr, scratch2, iso_len);
					bcopy(gpt->isoleaf.Addr.au.es_addr.addr, scratch2+iso_len, ES_NID_SIZE);
					dest = sockbuild_iso(scratch2, iso_len + ES_NID_SIZE);
					iso_len = (iso_len + ES_NID_SIZE) << 1;
					/* isHostRoute = 1; */ /* STEVE XXX - gated asserts if I set this :-( */
				} else {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("IS-IS update: following L1 route is missing advertising IS - not installed:" ));
					print_route(gpt, LOG_ERR, 0);
					break;
				}
			}
			if (isHostRoute) maskp = (sockaddr_un *) 0;
			else maskp = iso_mask_prefix(iso_len << 2);
			/* 
			 * For level two routes, we should be able to send to any of 
			 * the areas to which the nexthop system belongs.  For level one routes,
			 * we should restrict ourselves to sending only to those areas
			 * which we have in common with the nexthop system.
			 */
			nAAlist = (AreaAddrList *) adj->neighborInfo;
			if (!nAAlist->count) {
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("IS-IS update: following L%d route uses adjacency with missing area - not installed:", 
					      spf_level));
				print_route(gpt, LOG_ERR, 0);
				break;
			}
			for (i=0; i<nAAlist->count; i++) {
				/* nAA = (AreaAddr *) &gpt->g.adj->neighborInfo[i*sizeof(AreaAddr)]; */
				nAA = retrieveAreaAddr(nAAlist->areaAddr[i]);
				if ((nAA) && (spf_level == 1)) {
					for (j=0; j<systemAreaAddrs.count; j++) {
						AA = retrieveAreaAddr(systemAreaAddrs.areaAddr[j]);
						if ((AA) && (AA->len == nAA->len) && equalID(nAA->addr, AA->addr, AA->len)) {
							/* we have a match */
							break;
						}
					}
					if (j == systemAreaAddrs.count) {
						/* there was no match */
						nAA = (AreaAddr *) 0;
					}
				}
				if (nAA) {
					bcopy(nAA->addr, scratch, nAA->len);
					bcopy(adj->neighborSysID, scratch+nAA->len, sizeof(SystemID6));
					nexthops[numNexthop++] = sockbuild_iso(scratch, nAA->len+sizeof(SystemID6));
				}
			}
			/* trim off any extra next hops */
			numNexthop = min(numNexthop, RT_N_MULTIPATH);
			iso_addr_change++;
		}
		if (nexthop) {
			if (gpt->g.gated_route) {
				/* change old route for this level */
				pref_t pref;
				pref = isis_preference[spf_level];
				if (gpt->g.extern_cost) {
					BIT_RESET(gpt->g.gated_route->rt_state, RTS_INTERIOR);
					BIT_SET(gpt->g.gated_route->rt_state, RTS_EXTERIOR);
					import( dest,
						maskp,
						(gpt->g.gtype == IPLEAF) ? isis_import_list_ip : isis_import_list_iso,
						(adv_entry *) 0,
						(adv_entry *) 0,
						&pref,
						(if_addr *) 0,		
						(void_t) 0);
				} else {
					BIT_RESET(gpt->g.gated_route->rt_state, RTS_EXTERIOR);
					BIT_SET(gpt->g.gated_route->rt_state, RTS_INTERIOR);
				}
				IFTRACE(T_ROUTE1)
					if (gpt->g.parent) {
						trace_only_tf(isis_trace_options,
							      0,
							      ("ISIS updating following level %d route:",
							       spf_level));
						print_route(gpt, LOG_INFO, 0);
					}
				ENDTRACE
				rt_change(gpt->g.gated_route,
					  (metric_t) gpt->g.internal_cost,
					  (metric_t) 0,
					  (metric_t) 0,	/* STEVE XXX - rt_change now expects a "tag" */
					  pref,
					  (pref_t) 0,
					  numNexthop, &nexthop);
			} else {
				rtparms.rtp_dest = dest;
				rtparms.rtp_dest_mask = maskp;
				rtparms.rtp_n_gw = numNexthop;				/* multipath */
				for (i=0; i<numNexthop; i++)
					rtparms.rtp_routers[i] = nexthops[i];		/* multipath */
				rtparms.rtp_gwp = isis_gwp[spf_level];
				rtparms.rtp_metric = (metric_t) gpt->g.internal_cost;	/* gated wants interior metric */
				rtparms.rtp_preference = isis_preference[spf_level];
				if (gpt->g.extern_cost) {
					rtparms.rtp_state = RTS_EXTERIOR;
					import( dest,
						maskp,
						(gpt->g.gtype == IPLEAF) ? isis_import_list_ip : isis_import_list_iso,
						(adv_entry *) 0,
						(adv_entry *) 0,
						&rtparms.rtp_preference,
						(if_addr *) 0,		
						(void_t) 0);
				} else {
					rtparms.rtp_state = RTS_INTERIOR;
				}
				IFTRACE(T_ROUTE1)
					if (gpt->g.parent) {
						trace_only_tf(isis_trace_options,
							      0,
							      ("IS-IS adding L%d:",
							       spf_level));
						print_route(gpt, LOG_INFO, 0);
					}
				ENDTRACE
				gpt->g.gated_route = rt_add(&rtparms);
			}
			gated_changes++;
		}
	} 
}

/* 
 * Delete an existing route for a node which is no longer reachable.
 */
static void
spf_expire_route __PF1(gpt, GRAPH_PT)
{
	IFTRACE(T_ROUTE1)
		if (gpt->g.parent) {
			trace_only_tf(isis_trace_options,
				      0,
				      ("IS-IS deleting L%d:",
				       spf_level));
			print_route(gpt, LOG_INFO, 1);
		}
	ENDTRACE

	if (gpt->g.gtype != INTERIOR) {
		if (gpt->g.gated_route) {
			rt_delete(gpt->g.gated_route);
			gated_changes++;
			gpt->g.gated_route = (rt_entry *) 0;
			/*
			IFTRACE(T_ROUTE1)
				trace(TR_NORMAL, LOG_INFO, "  deleted");
			ENDTRACE
			*/
		} else {
			/* This isn't necessarily an error; it could be an ignored ES-IS duplicate. */
			IFTRACE(T_ROUTE1)
				trace_only_tf(isis_trace_options,
					      0,
					      ("  no route in gated's tables - ignored",
					       spf_level));
			ENDTRACE
		}
		gpt->g.parent = (GRAPH_PT) NULL;
		if (gpt->g.gtype == IPLEAF) {
			gpt->ipleaf.oldparent = (GRAPH_PT) NULL;
			ip_addr_change++;
		} else {
			gpt->isoleaf.oldparent = (GRAPH_PT) NULL;
			iso_addr_change++;
		}
	} else {
		/* deletion of these duikers is covered by their corresponding ISOLEAF (es_id) node */
		gpt->interior.adj = 0;
		gpt->interior.oldadj = 0; 
	}	

	gpt->g.generation = 0; 
}

/* 
 * For level 1 only system, update the default route with the
 * L2 designated system. 
 */
static void
isis_update_default_route()
{
#ifdef notdef
	/* STEVE XXX - fix this up for gated */
	struct graph_node r_dummy_ip;
#ifdef RTM_ADD
	struct graph_node r_dummy; /* for iso part, dummy up a graph node for a 0 len area addr. */
	r_dummy = *L2DesigSystem;
	r_dummy.Addr.addr_t = area_addr;
	r_dummy.Addr.au.area_addr.area_len = 0;
	send_iso_route(RTM_ADD,&r_dummy);
#endif
	/* for ip part, do kernel update */
	if (L2DesigSystem->adj->ipaddrs.cnt) {
		/* there needs to be a better test for this */
		r_dummy_ip = *L2DesigSystem;
		r_dummy_ip.Addr.addr_t = inet_net;
		bzero((caddr_t) &r_dummy_ip.Addr.au.in2,sizeof(INET_N2));
		/* default route has all zero mask?? */
		isis_update_route(&r_dummy_ip);
	}
	/* thats it except we should probably delete the old route first */
#endif	/* notdef */
}


/* 
 * Update the routing table based on changes to the SPF database.
 * If level 2 system and running level one, also collect area 
 * addresses.
 */
static void 
isis_update_gated_routes()
{
	int i;
	GRAPH_PT gpt;
	GRAPH_PT gptn;
	AdjacencyEntry *adj, *oldadj;
        utime_t startTime, endTime;
	int totalms;

	IFTRACE(T_TRSPF)
	    TIMER_PEEK();
	    startTime = utime_current;
	ENDTRACE

	/* make gcc happy */
	adj = oldadj = (AdjacencyEntry *) 0;

	rt_open(isis_task);
	gated_changes = 0;
	ip_addr_change = 0;
	iso_addr_change = 0;

	/* run through the table */
	for (gptn = spf_tab[i=0]; i < SPF_HASHTAB_SIZE; gptn = spf_tab[i++])
		/* it's a little inefficient to scan the 4k hash entries... */
		for (gpt = gptn; gpt; gpt = gpt->g.hash_chain) {
			if (gpt->g.generation == curr_generation) {
				switch (gpt->g.gtype) {
				case IPLEAF:
					adj = (gpt->g.parent) ? gpt->g.parent->interior.adj : (AdjacencyEntry *) NULL;
					oldadj = (gpt->ipleaf.oldparent) ? 
						  gpt->ipleaf.oldparent->interior.oldadj : (AdjacencyEntry *) NULL;
					break;
				case INTERIOR:
					adj = gpt->interior.adj;
					oldadj = gpt->interior.oldadj;
					break;
				case ISOLEAF:
					adj = (gpt->g.parent) ? gpt->g.parent->interior.adj : (AdjacencyEntry *) NULL;
					oldadj = (gpt->isoleaf.oldparent) ? 
						  gpt->isoleaf.oldparent->interior.oldadj : (AdjacencyEntry *) NULL;
					break;
				}
				if (adj != oldadj) 
				/* addition conditions- is systems only, no pseudonodes 
				&& gpt->Addr.addr_t == is_id && gpt->Addr.au.is_addr.addr[6]==0)
				*/
					isis_update_route(gpt);
			} else if (gpt->g.generation) {
				/* a previous route is no longer usable */ 
				spf_expire_route(gpt);
			}
		}

	if (spf_level == 1 && systemType == L2IS && (ip_addr_change || set_l2_ip)) {
		summarize_all_ip_reachables();
	}
	if (systemType == L1IS && L2DesigSystem && 
			(OldL2DesigSystem != L2DesigSystem || OldL2DesigAdj != L2DesigSystem->interior.adj))
		/* new default route */
		isis_update_default_route();

	IFTRACE(T_TRSPF)
	if (gated_changes) {
	    TIMER_PEEK();
	    endTime = utime_current;
	    totalms = (endTime.ut_sec - startTime.ut_sec) * 1000 + (endTime.ut_usec - startTime.ut_usec) / 1000;
	    trace_only_tf(isis_trace_options,
			  0,
			  ("IS-IS SPF L%d processed %d IP and %d ISO changes in %d ms", 
			   spf_level,
			   ip_addr_change,
			   iso_addr_change,
			   totalms));
	}
	ENDTRACE

	for (gptn = spf_tab[i=0]; i < SPF_HASHTAB_SIZE; gptn = spf_tab[i++]) {
		/* it's really inefficient to do it twice */
		for (gpt = gptn; gpt; gpt = gpt->g.hash_chain) {
			gpt->g.pend_q = (GRAPH_PT) 0;
			if (gpt->g.gtype == INTERIOR) {
				gpt->interior.aa.numAAs = 0;
			}
		}
	}

	rt_close(isis_task,0,gated_changes,NULL);
}

/* 
 * Check if the subnet specifed by the addr a2 and mask m2 is 
 * contained within the subnet specified by a1 & m1.
 */
int 
in_subnet(a1, m1, a2, m2)
u_long *a1,*m1,*a2,*m2;
/* pass by address for 4.4 compatibility. don't ask. */
{
	if ((*m1 & ~*m2) == 0) {
		/* m1 is more general (it has fewer bits) */
		if ((*a1 & *m1) == (*a2 & *m1)) return 1;
	}
	return 0;
}

/*
 * Set up for level 1 spf check against summary addresses.
 * Just clear the in use marker and unsummarized address list.
 */
static void
clear_summary_inuse()
{
	struct isis_ipr *ipreach;
	CircuitEntry *c;
	if_addr *ifap;
	struct sumlist *tmp;
	int i;
	
	/* add summary addresses for each of our IFF_UP broadcast AF_INET circuits */
        for (i=0; i < MaximumCircuits; i++) {
                if (((c=circuitList[i]) == NULL) || (c->circuitType == Pt2Pt) || c->summarized) continue;
		IF_ADDR(ifap) {
			if ((ifap->ifa_link->ifl_index == c->kernindex) && 
			    (BIT_TEST(ifap->ifa_state, IFS_UP)) && 
			    (socktype(ifap->ifa_addr) == AF_INET)) {
				save_ipreach(2, ISIS_AUTOSUMMARY, ifap->ifa_net, ifap->ifa_netmask, c->l1Metric.defalt);
				c->summarized = 1;
			}
		} IF_ADDR_END(ifap);
	}
	for (ipreach = IPRList; ipreach; ipreach = ipreach->next) {
		if (ipreach->type == IPSumReachCode) ipreach->inUse = FALSE;
	}

	while (noSummary) {
		tmp = noSummary->next;
		task_block_free(isis_sumlist_block, noSummary);
		isisCounters.sumnodes--;
		noSummary = tmp;
	}
	noSummary = (struct sumlist *) 0; 
}
	
/* 
 * Check the given destination for inclusion in summary.  Return 1 if
 * gpt was summarized.
 */
int
check_for_summary __PF1(gpt, GRAPH_PT)
{
	int in_sum = 0;
	struct isis_ipr *ipreach;
	struct sumlist *tmp;

	for (ipreach = IPRList; ipreach; ipreach = ipreach->next) {
		if (ipreach->type == IPSumReachCode) {
			if (in_subnet((u_long *) &ipreach->addr,(u_long *) &ipreach->mask, 
				      (u_long *) &gpt->ipleaf.Addr.addr,(u_long *) &gpt->ipleaf.Addr.mask)) {
				/* mark this summary as used */
				ipreach->inUse = TRUE;
				in_sum = 1;
			}
		} else if (ipreach->type == IPIntReachCode) {
			/* manual info supercedes Dijkstra, so check. */
			if (!spf_cmp_addr((char *) &ipreach->addr,inet_net,gpt))
				in_sum = 1;
		}
	}
	if (!in_sum) {
		tmp = (struct sumlist *) task_block_alloc(isis_sumlist_block);
		isisCounters.sumnodes++;
		tmp->next = noSummary;
		tmp->node = gpt;
		noSummary = tmp;
		/* 
		gpt->ipleaf.ip_list = noSummary; 
		noSummary = gpt;
		*/
		return(0);
	}
	return(1);
}

/* 
 * Check SPF table, collapsing individual IP reachables into
 * summary addresses when appropriate.
 */
static void
summarize_all_ip_reachables()
{
	int i;
	GRAPH_PT gpt, gptn;

	clear_summary_inuse();
	for (gptn = spf_tab[i=0]; i < SPF_HASHTAB_SIZE; gptn = spf_tab[i++])
		for (gpt = gptn; gpt; gpt = gpt->g.hash_chain) {
			if (gpt->g.gtype == IPLEAF) {
				if (gpt->ipleaf.generation==curr_generation) {
					if (check_for_summary(gpt) && gpt->ipleaf.p) {
						/* this was unsummarized before but is summarized now - delete it */
						clearIPReachable(2, gpt->ipleaf.p->opt->type, gpt->ipleaf.p);
						gpt->ipleaf.p = (prefIP *) NULL;
					}
				} else if (gpt->ipleaf.p) {
					/* this was an unsummarized L2 prefix before but is no longer reachable - delete it */
					clearIPReachable(2, gpt->ipleaf.p->opt->type, gpt->ipleaf.p);
					gpt->ipleaf.p = (prefIP *) NULL;
				}
			}
		}
	MakeL2IPlist();
}

static void
update_ipreach_lsp()
{
}

void
isis_spf __PF1(level, int)
{
	IS_ID home_is;
	GRAPH_PT hn;

	if (level==1) {
		spf_tab = spf_tab_l1;
		spfType = L1IS;
	} else if (level==2) {
		spf_tab = spf_tab_l2;
		spfType = L2IS;
	} else {
		trace_tf(isis_trace_options,
			 TR_NORMAL,
			 0,
			 ("bad spf level request: %d",
			  level));
	}
	spf_level = level;
	bcopy((caddr_t) systemID, (caddr_t) home_is.addr, 6);

	home_is.addr[6] = 0;
	hn = get_graph_entry((char *) home_is.addr, is_id, 1);
	run_isis_spf(hn);
	isis_update_gated_routes();
	IFTRACE(T_ROUTE2) 
		print_paths();
	ENDTRACE
	deleteOldAdjacencies(level);
}


/* 
 * Print all routes except those to ourself.
 */
static void
print_paths()
{
	int i;
	GRAPH_PT gpt, gptn;
	char pbuf[200];

	trace_only_tf(isis_trace_options,
		      0,
		      ("Level %d routes (from %s)",
		       (spf_level == 1) ? 1 : 2,
		       spf_print_addr(pbuf,systemID,is_id)));

	for (gptn = spf_tab[i=0]; i < SPF_HASHTAB_SIZE; gptn = spf_tab[i++])
		for (gpt = gptn; gpt; gpt = gpt->g.hash_chain) {
			if ((gpt->g.generation == curr_generation) && gpt->g.parent && gpt->g.parent->interior.adj) 
				print_route(gpt, LOG_INFO, 0);
		}
	trace_only_tf(isis_trace_options,
		      0,
		      (NULL));
}

/* 
 * Call this baby if an IP routing change is detected during a 
 * level 1 spf computation.  This function rebuilds the L2 LSP
 * IP internally reachable option field using the new information
 * from level 1.  
 *
 * STEVE XXX - this scheme blows.
 */
static void
MakeL2IPlist()
{
	struct isis_ipr *Ipt = IPRList;
	struct sumlist *ipg = (struct sumlist *) 0;

	set_l2_ip = 0; /*just make sure it's done once */
#ifdef	notdef
	/* 
	 * STEVE XXX - the following line causes problems for exporting
	 * routes as IPIntReach.
	 */
	removeAllOptions(L2LSP,IPIntReachCode); /* delete all old options */
#endif	/* notdef */
	/* for the time being, we ignore external reachability */
	/* note that both level 1 and level 2 get added here;  note
		also that we are ignoring external reachability for now.
	*/
	/* add manually configured and summarized addresses first */
	while (Ipt) {
		if (Ipt->type == IPSumReachCode) {
			if ((Ipt->inUse) && (!Ipt->p)) {
				/* new summary address - install as internally reachable in L2 */
				Ipt->p = setIPReachable(2,IPIntReachCode, Ipt->metric,Ipt->addr,Ipt->mask, (as_path *) 0);
			} else if ((!Ipt->inUse) && (Ipt->p)) {
				/* old summary info no longer valid */
				clearIPReachable(2, Ipt->p->opt->type, Ipt->p);
				Ipt->p = (prefIP *) NULL;
			}
		} else if (Ipt->type == IPIntReachCode)
			Ipt->p = setIPReachable(2,IPIntReachCode,Ipt->metric,Ipt->addr,Ipt->mask, (as_path *) 0);
		Ipt = Ipt->next;
	}
	/* include the level 1 unsummarized reachable subnets */
	for (ipg = noSummary; ipg; ipg = ipg->next) {
		MetricList ip_ml;
		struct in_addr addr, mask;
		ip_ml.defalt = ip_ml.delay = ip_ml.expense = ip_ml.error = 0xff;
		addr.s_addr = * ((u_long *) ipg->node->ipleaf.Addr.addr);
		mask.s_addr = * ((u_long *) ipg->node->ipleaf.Addr.mask);
		if (ipg->node->ipleaf.internal_cost < 0xff)
			ip_ml.defalt = ipg->node->ipleaf.internal_cost;
		ipg->node->ipleaf.p = setIPReachable(2, IPIntReachCode, ip_ml, addr, mask, (as_path *) 0);
	}
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
