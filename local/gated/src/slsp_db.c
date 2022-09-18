/*
 * $Id: slsp_db.c,v 1.12.2.3 1994/07/22 17:52:59 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"
#include "inet.h"
#include "slsp_proto.h"
#include "slsp.h"
#include "slsp_var.h"


/*
 * Number of LSPs we send per second.
 */
#define	SLSP_DB_MAX_XMT		20

/*
 * Memory allocation.  We allocate AS and link structures and
 * the database node structures themselves.
 */
static block_t slsp_db_as_block = (block_t) 0;
static block_t slsp_db_link_block = (block_t) 0;
static block_t slsp_db_node_block = (block_t) 0;
static block_t slsp_db_fsq_block = (block_t) 0;
static block_t slsp_db_fsp_block = (block_t) 0;

/*
 * Size of a full sequence packet
 */
#define	SLSP_DB_FSP_SIZE	task_pagesize

/*
 * Allocate them.
 */
#define	SLSP_DB_AS_ALLOC() \
    ((slsp_db_as *) task_block_alloc(slsp_db_as_block))

#define	SLSP_DB_LINK_ALLOC() \
    ((slsp_db_link *) task_block_alloc(slsp_db_link_block))

#define	SLSP_DB_NODE_ALLOC() \
    ((slsp_db_node *) task_block_alloc(slsp_db_node_block))

#define	SLSP_DB_FSQ_ALLOC() \
    ((slsp_full_seq_q *) task_block_alloc(slsp_db_fsq_block))

#define	SLSP_DB_FSP_ALLOC() \
    ((byte *) task_block_alloc(slsp_db_fsp_block))

/*
 * Initialize them
 */
#define	SLSP_DB_AS_INIT() \
    (slsp_db_as_block = task_block_init(sizeof(slsp_db_as), "slsp_db_as"))

#define	SLSP_DB_LINK_INIT() \
    (slsp_db_link_block = task_block_init(sizeof(slsp_db_link), "slsp_db_link"))

#define	SLSP_DB_NODE_INIT() \
    (slsp_db_node_block = task_block_init(sizeof(slsp_db_node), "slsp_db_node"))

#define	SLSP_DB_FSQ_INIT() \
    (slsp_db_fsq_block = task_block_init(sizeof(slsp_full_seq_q), "slsp_full_seq_q"))

#define	SLSP_DB_FSP_INIT() \
    (slsp_db_fsp_block = task_block_init(SLSP_DB_FSP_SIZE, "slsp_full_seq_pkt"))

/*
 * Free them
 */
#define	SLSP_DB_AS_FREE(dbas) \
    task_block_free(slsp_db_as_block, (void_t)(dbas))

#define	SLSP_DB_LINK_FREE(dblink) \
    task_block_free(slsp_db_link_block, (void_t)(dblink))

#define	SLSP_DB_NODE_FREE(dbnp) \
    task_block_free(slsp_db_node_block, (void_t)(dbnp))

#define	SLSP_DB_FSQ_FREE(fsqp) \
    task_block_free(slsp_db_fsq_block, (void_t)(fsqp))

#define	SLSP_DB_FSP_FREE(fspp) \
    task_block_free(slsp_db_fsp_block, (void_t)(fspp))

/*
 * Lazy initialization/alloc's
 */
#define	SLSP_DB_AS_GET(dbas) \
    do { \
	if (!slsp_db_as_block) { \
	    SLSP_DB_AS_INIT(); \
	} \
	(dbas) = SLSP_DB_AS_ALLOC(); \
    } while (0)

#define	SLSP_DB_LINK_GET(dblink) \
    do { \
	if (!slsp_db_link_block) { \
	    SLSP_DB_LINK_INIT(); \
	} \
	(dblink) = SLSP_DB_LINK_ALLOC(); \
    } while (0)

#define	SLSP_DB_NODE_GET(dbnp) \
    do { \
	if (!slsp_db_node_block) { \
	    SLSP_DB_NODE_INIT(); \
	} \
	(dbnp) = SLSP_DB_NODE_ALLOC(); \
    } while (0)

#define	SLSP_DB_FSQ_GET(fsqp) \
    do { \
	if (!slsp_db_fsq_block) { \
	    SLSP_DB_FSQ_INIT(); \
	} \
	(fsqp) = SLSP_DB_FSQ_ALLOC(); \
    } while (0)

#define	SLSP_DB_FSP_GET(fspp) \
    do { \
	if (!slsp_db_fsp_block) { \
	    SLSP_DB_FSP_INIT(); \
	} \
	(fspp) = SLSP_DB_FSP_ALLOC(); \
    } while (0)

/*
 * Reference/dereference nodes, used when links which reference
 * the nodes are added/deleted.
 */
#define	SLSP_NODE_REFERENCE(np)	((np)->slsp_node_refcount++)

#define	SLSP_NODE_DEREFERENCE(np) \
    do { \
	assert((np)->slsp_node_refcount); \
	if ((np)->slsp_node_refcount == 1 \
	  && (np)->slsp_node_type == SLSP_LSP_PLACEHOLDER) { \
	    slsp_db_dereference(np); \
	} else { \
	    (np)->slsp_node_refcount--; \
	} \
    } while (0)

/*
 * Support for building/sending partial sequence number packets.
 * We do sort of a lazy build here, collecting everything to send
 * to a neighbour until either we need to send to another neighbour,
 * or input completes.  We currently build this in the send packet.
 */
#define	SLSP_DB_MAXENTRIES	100

#define	slsp_db_ack_pkt		((byte *) task_send_buffer)

slsp_neighbour *slsp_db_ack_nbr = (slsp_neighbour *) 0;
static byte *slsp_db_ack_pkt_start;
static byte *slsp_db_ack_pkt_end;

#define	SLSP_DB_ADD_ACK(nbr, enttype, addr, seqnum, lifetime, cksum) \
    do { \
	register slsp_neighbour *Xnbr = (nbr); \
	if (slsp_db_ack_nbr != Xnbr \
	  || slsp_db_ack_pkt_start >= slsp_db_ack_pkt_end) { \
	    slsp_db_ack_flush(Xnbr); \
	} \
	SLSP_PUT_SEQ_ENT((enttype), \
			 (addr), \
			 (seqnum), \
			 (lifetime), \
			 (cksum), \
			 slsp_db_ack_pkt_start); \
    } while (0)


/*
 * Schedule the transmit queue
 */
#define	SLSP_DB_XMT_SCHEDULE(inp) \
    do { \
	if (!BIT_TEST((inp)->slsp_flags, SLSPF_XMT_JOB|SLSPF_XMT_THROTTLE)) { \
	    slsp_db_xmt_schedule((inp)); \
	} \
    } while (0)

/*
 * Schedule the lifetime queue
 */
#define	SLSP_DB_LIFE_SCHEDULE(inp) \
    do { \
	register slsp_instance *Xinp = (inp); \
	if (Xinp->slsp_next_life_timeout) { \
	    register slsp_db_node *Xnp = SLSP_LIFE_NEXT(Xinp, Xinp); \
	    if (!Xnp || \
	      Xinp->slsp_next_life_timeout <= Xnp->slsp_node_life_timeout) { \
		break; \
	    } \
	} \
	slsp_db_life_schedule(Xinp); \
    } while (0)

/*
 * Forward declarations
 */
PROTOTYPE(slsp_db_xmt_timer_create,
	  static void,
	  (slsp_instance *,
	   time_t));
PROTOTYPE(slsp_db_life_schedule,
	  static void,
	  (slsp_instance *));
	  


/*
 * Lookup table to do an ffs() from the high order end (the ffs() routine
 * runs from the other end), on a byte.  This is useful to find the first
 * differing bit for the patricia tree.
 */
const byte slsp_bit_table[256] = {
    0x00, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
};


/*
 * Find the lowest order bit set in a byte
 */
static const slsp_bit_t slsp_db_first_set[256] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};


/*
 * slsp_node_insert - add a node to the node tree for this instance.  Note that
 *		   found_np points to the node that was "found" when the
 *		   database was searched for the node we are adding.
 *		   If it is NULL we do the search on our own.
 */
static void
slsp_node_insert __PF2(new_np, slsp_db_node *,
		       found_np, slsp_db_node *)
{
    register slsp_db_node *np = new_np;
    register slsp_db_node *nprev, *ncurr;
    register u_long key;
    register u_long mask, omask;
    slsp_instance *slsp;

    /*
     * Check to make sure this guy isn't in the tree already.  Also
     * check that the instance pointer is set in the node.
     */
    assert(np->slsp_node_mask == 0);
    slsp = np->slsp_node_instance;
    assert(slsp != NULL);

    /*
     * Fetch his key.  This is the node address in host byte order.
     */
    key = ntohl(sock2ip(np->slsp_node_addr));

    /*
     * If he didn't include a "found" node, but there are nodes
     * to "find", "find" it.  If there are no nodes to find then
     * this is the first node in the tree and just needs to get
     * initialized appropriately.
     */
    if (found_np == NULL) {
	if ((ncurr = slsp->slsp_nodes) == NULL) {
	    slsp->slsp_nodes = np->slsp_node_right = np->slsp_node_left = np;
	    np->slsp_node_mask = SLSP_NOMASK;
	    return;
        }
	mask = SLSP_NOMASK;
	while (mask > ncurr->slsp_node_mask) {
	    mask = ncurr->slsp_node_mask;
	    if (key & mask) {
		ncurr = np->slsp_node_right;
	    } else {
		ncurr = np->slsp_node_left;
	    }
	}
	found_np = ncurr;
    }

    /*
     * Here we have an insertion to do.  Figure out the first
     * (most significant) bit which differs from the "found" node.  This
     * tells us the bit we need to test in the node we insert.
     *
     * Do a binary search to find the byte the first bit is in, then use
     * the table to form the mask.
     */
    mask = key ^ ntohl(sock2ip(found_np->slsp_node_addr));
    if (mask >= 0x10000) {
	if (mask >= 0x1000000) {
	    mask = ((u_long)(slsp_bit_table[mask >> 24])) << 24;
	} else {
	    mask = ((u_long)(slsp_bit_table[mask >> 16])) << 16;
	}
    } else {
	if (mask >= 0x100) {
	    mask = ((u_long)(slsp_bit_table[mask >> 8])) << 8;
	} else {
	    mask = (u_long)(slsp_bit_table[mask]);
	}
    }
    /*
     * XXX Sanity.  This could only happen if a node with the same key
     * is in the tree already, which should never happen.
     */
    assert(mask != 0);
    np->slsp_node_mask = mask;

    /*
     * Now we locate where this guy needs to be inserted.  Search down
     * the tree until we find either an end node (i.e. an upward link)
     * or a node with a mask smaller than ours.  We insert our node
     * above this (watch for the case where the node we find is the
     * current root node), making one of the pointers an uplink pointing
     * at the node itself.
     */
    nprev = NULL;
    ncurr = slsp->slsp_nodes;
    omask = SLSP_NOMASK;
    while (omask > ncurr->slsp_node_mask) {
	omask = ncurr->slsp_node_mask;
	if (mask >= omask) {
	    break;
	}
	nprev = ncurr;
	if (key & omask) {
	    ncurr = ncurr->slsp_node_right;
	} else {
	    ncurr = ncurr->slsp_node_left;
	}
    }
    assert(mask != ncurr->slsp_node_mask);

    /*
     * Point the new node at the current node, and at itself.  The
     * pointer to the current node in the previous node is changed to
     * point at the new node.  Simple(?).
     */
    if (key & mask) {
	np->slsp_node_right = np;
	np->slsp_node_left = ncurr;
    } else {
	np->slsp_node_right = ncurr;
	np->slsp_node_left = np;
    }

    if (nprev == NULL) {
	/* New root node */
	slsp->slsp_nodes = np;
    } else if (nprev->slsp_node_right == ncurr) {
	nprev->slsp_node_right = np;
    } else {
	nprev->slsp_node_left = np;
    }
    /* done */
}


/*
 * slsp_node_remove - remove a node from the node tree for this instance.
 */
static void
slsp_node_remove __PF1(remove_np, slsp_db_node *)
{
    register slsp_db_node *np = remove_np;
    register slsp_db_node *tmp;
    register slsp_db_node *nprev, *ncurr;
    register u_long key;
    slsp_db_node *intprev;
    slsp_instance *slsp;

    /*
     * Check to make sure this guy is in the tree already.
     */
    assert(np->slsp_node_mask != 0);

    /*
     * Detect the trivial case, that there is only one guy in the tree,
     * and fix this up.
     */
    slsp = np->slsp_node_instance;
    ncurr = slsp->slsp_nodes;
    if (ncurr->slsp_node_mask == SLSP_NOMASK) {
	assert(ncurr == np);
	np->slsp_node_mask = 0;
	slsp->slsp_nodes = NULL;
	return;
    }

    /*
     * We will be in the tree twice, once as an internal node and once
     * as an external (or up-)node.  Find the guy who points to our man
     * in the tree in both cases, and the guy who points to him in the
     * latter.
     */
    nprev = NULL;
    intprev = NULL;
    key = ntohl(sock2ip(np->slsp_node_addr));
    for (;;) {
	if (key & ncurr->slsp_node_mask) {
	    tmp = ncurr->slsp_node_right;
	} else {
	    tmp = ncurr->slsp_node_left;
	}
	if (tmp == np) {
	    if (np->slsp_node_mask >= ncurr->slsp_node_mask) {
		break;		/* got it */
	    }
	    intprev = ncurr;	/* current is in front of internal */
	} else {
	    assert(tmp->slsp_node_mask < ncurr->slsp_node_mask);
	}
	nprev = ncurr;
	ncurr = tmp;
    }

    /*
     * Now we have ncurr pointing at the node which contains the up-link
     * to our deleted node, nprev pointing at the node which points to
     * ncurr and intprev pointing at the guy who precedes our node in its
     * internal incarnation.
     *
     * There are several cases here.  We know the information in ncurr
     * is no longer needed, and that the sibling pointer in ncurr will
     * be moved to nprev (replacing ncurr).  If our node is the special
     * one with no internal information, we make ncurr the special.
     * If ncurr is our node (i.e. intprev == nprev) then we simply
     * point nprev at our sibling and we're done.  Otherwise we
     * additionally copy our information to ncurr, and point intprev
     * at ncurr.
     *
     * There is probably a better way to do this, but I'm an engineer,
     * not a (mere) programmer.
     */
    if (ncurr->slsp_node_right == np) {
	tmp = ncurr->slsp_node_left;
    } else {
	tmp = ncurr->slsp_node_right;
    }

    if (nprev == NULL) {
	slsp->slsp_nodes = tmp;
    } else if (nprev->slsp_node_right == ncurr) {
	nprev->slsp_node_right = tmp;
    } else {
	nprev->slsp_node_left = tmp;
    }
    if (ncurr != np) {
	if (np->slsp_node_mask == SLSP_NOMASK) {
	    ncurr->slsp_node_mask = SLSP_NOMASK;
	    ncurr->slsp_node_left = ncurr->slsp_node_right = ncurr;
	} else {
	    ncurr->slsp_node_mask = np->slsp_node_mask;
	    ncurr->slsp_node_left = np->slsp_node_left;
	    ncurr->slsp_node_right = np->slsp_node_right;
	    if (intprev == NULL) {
		slsp->slsp_nodes = ncurr;
	    } else if (intprev->slsp_node_right == np) {
		intprev->slsp_node_right = ncurr;
	    } else {
		intprev->slsp_node_left = ncurr;
	    }
	}
    }

    /*
     * Set the bit to 0 so we know it is deleted.
     */
    np->slsp_node_mask = 0;
}


/*
 * slsp_db_ack_flush - flush the pending partial sequence numbers
 *		       packet if we have one, because we want to
 *		       build one for a different neighbour or
 *		       because we're done with input for now
 */
void
slsp_db_ack_flush __PF1(nbr, slsp_neighbour *)
{
    register size_t entries, len;

    if (slsp_db_ack_nbr) {
	entries = slsp_db_ack_pkt_end - slsp_db_ack_pkt_start;
	assert(!(entries % SLSP_SEQ_ENT_LEN));
	entries = SLSP_DB_MAXENTRIES - (entries / SLSP_SEQ_ENT_LEN);
	if (entries) {
	    len = slsp_db_ack_pkt_start - slsp_db_ack_pkt;
	    assert(len == SLSP_SEQ_LENGTH(entries));
	    SLSP_SET_SEQ_LEN(len, entries, slsp_db_ack_pkt);
	    slsp_send(slsp_db_ack_nbr, slsp_db_ack_pkt, len);
	}
	if (nbr) {
	    slsp_db_ack_pkt_start = slsp_db_ack_pkt + SLSP_SEQ_FIXED_LEN;
	    if (nbr != slsp_db_ack_nbr) {
		register byte *cp = slsp_db_ack_pkt + 7;

		SLSP_PUT_IPADDR(nbr->slsp_nbr_instance->slsp_addr, cp);
	    }
	}
    } else if (nbr) {
	SLSP_INIT_SEQ(nbr->slsp_nbr_instance->slsp_addr,
		      SLSP_SEQ_PARTIAL,
		      slsp_db_ack_pkt);
	slsp_db_ack_pkt_start = slsp_db_ack_pkt + SLSP_SEQ_FIXED_LEN;
	slsp_db_ack_pkt_end = slsp_db_ack_pkt
	  + SLSP_SEQ_LENGTH(SLSP_DB_MAXENTRIES);
    }
    slsp_db_ack_nbr = nbr;
}


/*
 * slsp_db_full_seq_format - format a full sequence numbers packet from
 *			     the data on this instance's full list.
 */
static size_t
slsp_db_full_seq_format __PF2(inp, slsp_instance *,
			      his_pkt, byte **)
{
    register slsp_db_node *np;
    register byte *pkt;
    register byte *cp;
    register size_t entries = inp->slsp_full_seq_entries;
    size_t len;

    /*
     * Figure out how long the packet needs to be.  If we're
     * operating on a saved buffer and it'll fit, do it, otherwise
     * format it into the send buffer.
     */
    len = SLSP_SEQ_LENGTH(entries);
    if (inp->slsp_needs_full_seq && len <= SLSP_DB_FSP_SIZE) {
	pkt = inp->slsp_full_seq_pkt;
	if (pkt) {
	    if (inp->slsp_full_seq_pkt_time &&
	      (inp->slsp_full_seq_pkt_time + SLSP_MIN_SEND_INTERVAL)
		>= time_sec) {
		assert(len == inp->slsp_full_seq_pkt_len);
		return len;
	    }
	} else {
	    SLSP_DB_FSP_GET(pkt);
	    SLSP_INIT_SEQ(inp->slsp_addr, SLSP_SEQ_FULL, pkt);
	    inp->slsp_full_seq_pkt = pkt;
	}
	if (len != inp->slsp_full_seq_pkt_len) {
	    inp->slsp_full_seq_pkt_len = len;
	    SLSP_SET_SEQ_LEN(len, entries, pkt);
	}
	cp = pkt + SLSP_SEQ_FIXED_LEN;
    } else {
	if (inp->slsp_full_seq_pkt) {
	    SLSP_DB_FSP_FREE(inp->slsp_full_seq_pkt);
	    inp->slsp_full_seq_pkt = (byte *) 0;
	    inp->slsp_full_seq_pkt_len = (size_t) 0;
	    inp->slsp_full_seq_pkt_time = (time_t) 0;
	}
	cp = pkt = (byte *) task_send_buffer;
	SLSP_PUT_SEQ(inp->slsp_addr, SLSP_SEQ_FULL, len, entries, cp);
    }
    *his_pkt = pkt;

    /*
     * Now walk the full list adding them to the packet
     * XXX note that sometimes we won't know a cksum for the
     * local node.  I think this is okay. XXX
     */
    for (np = SLSP_FULL_NEXT(inp, inp);
	 np;
	 np = SLSP_FULL_NEXT(inp, np)) {
	SLSP_PUT_SEQ_ENT(SLSP_SEQ_ENT_TYPE_ROUTER,
			 np->slsp_node_addr,
			 np->slsp_node_seqnum,
			 ((np->slsp_node_life > time_sec) ?
			  (np->slsp_node_life - time_sec) : (time_t) 4),
			 (np->slsp_node_cksum ? np->slsp_node_cksum : 0xffff),
			 cp);
    }

    assert(len == (cp - pkt));
    return len;
}


/*
 * slsp_db_full_seq_remove - remove an unneeded full sequence numbers
 *			     packet from this instance.
 */
static void
slsp_db_full_seq_remove __PF1(inp, slsp_instance *)
{
    assert(!(inp->slsp_needs_full_seq));
    if (inp->slsp_full_seq_pkt) {
	SLSP_DB_FSP_FREE(inp->slsp_full_seq_pkt);
	inp->slsp_full_seq_pkt = (byte *) 0;
	inp->slsp_full_seq_pkt_len = (size_t) 0;
	inp->slsp_full_seq_pkt_time = (time_t) 0;
    }
}


/*
 * slsp_db_bit_alloc - allocate a bit for a neighbour
 */
void
slsp_db_bit_alloc __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp;
    register u_short i;

    assert(nbr->slsp_nbr_index == 0);

    inp = nbr->slsp_nbr_instance;
    for (i = 0; i < SLSP_MAX_NEIGHBOURS; i++) {
	if (!(inp->slsp_bit_nbrs[i])) {
	    break;
	}
    }

    assert(i < SLSP_MAX_NEIGHBOURS);
    nbr->slsp_nbr_index = i + 1;
    nbr->slsp_nbr_offset = SLSP_WORDINDEX(i);
    nbr->slsp_nbr_bitmask = SLSP_BITINMASK(i);
    inp->slsp_bit_nbrs[i] = nbr;
}


/*
 * slsp_db_bit_free - dump a neighbour's bit
 */
void
slsp_db_bit_free __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp;
    register u_short i;

    inp = nbr->slsp_nbr_instance;
    i = nbr->slsp_nbr_index;
    assert(i);
    assert(inp->slsp_bit_nbrs[i - 1] == nbr);
    inp->slsp_bit_nbrs[i - 1] = (slsp_neighbour *) 0;
    nbr->slsp_nbr_index = 0;
    nbr->slsp_nbr_offset = 0;
    nbr->slsp_nbr_bitmask = 0;
}


/*
 * slsp_db_xmt_flush - flush the transmit queue for this instance,
 *		       sending ready LSP's from the front of the
 *		       queue.
 */
static void
slsp_db_xmt_flush __PF1(inp, slsp_instance *)
{
    register byte *cp;
    register slsp_db_link *lp;
    register int i;
    int tosend;
    byte *cpstart;
    slsp_db_node *np, *np_next;
    slsp_full_seq_q *fsp, *fsp_next;
    size_t length;
    byte *send_fsp;
    time_t lifetime;
    int sent = 0;

    np_next = SLSP_XMT_NEXT(inp, inp);
    while ((np = np_next)
      && sent < SLSP_DB_MAX_XMT
      && np->slsp_node_xmt_time <= time_sec) {
	sent++;
	np_next = SLSP_XMT_NEXT(inp, np_next);
	assert(np->slsp_node_xmt_nbits);

	/*
	 * We have a guy to send.  Work on formatting the packet.  AS payload
	 * goes in first.
	 */
	cp = ((byte *) task_send_buffer) + SLSP_LSP_FIXED_LEN;
	if (np->slsp_node_aslist.slspdb_as_count) {
	    register slsp_db_as *asp;

	    cpstart = (byte *) 0;
	    if (np->slsp_node_type != SLSP_LSP_LOCALRTR) {
		asp = np->slsp_node_aslist.slspdb_as_next;

		do {
		    if (asp->slspdb_as_newbucket) {
			if (cpstart) {
			    *(cpstart - 1) = (byte)(cp - cpstart);
			}
			*cp++ = SLSP_LSP_CODE_AS;
			cpstart = ++cp;
		    }
		    SLSP_PUT_LSP_AS(asp->slspdb_as, cp);
		} while ((asp = asp->slspdb_as_next));
	    } else {
		int in_bucket = 0;

		for (asp = np->slsp_node_aslist.slspdb_as_next;
		     asp != &(np->slsp_node_aslist);
		     asp = asp->slspdb_as_next) {
		    if (!in_bucket) {
			if (cpstart) {
			    *(cpstart - 1) = (byte)(cp - cpstart);
			}
			*cp++ = SLSP_LSP_CODE_AS;
			cpstart = ++cp;
			in_bucket = 255 / SLSP_LSP_AS_LEN;
		    }
		    in_bucket--;
		    SLSP_PUT_LSP_AS(asp->slspdb_as, cp);
		}
	    }
	    if (cpstart) {
		*(cpstart - 1) = (byte)(cp - cpstart);
	    }
	}

	/*
	 * Now the links payload.  See if we have any
	 */
	cpstart = (byte *) 0;
	for (lp = np->slsp_node_linklist.slspdb_link_next;
	     lp && lp != &(np->slsp_node_linklist);
	     lp = lp->slspdb_link_next) {
	    if (lp->slspdb_link_newbucket) {
		if (cpstart) {
		    *(cpstart - 1) = (byte)(cp - cpstart);
		}
		*cp++ = SLSP_LSP_CODE_LINKS;
		cpstart = ++cp;
		SLSP_PUT_LINK_COST(lp->slspdb_link_cost, cp);
	    }
	    SLSP_PUT_LINK_ID(lp->slspdb_link_node->slsp_node_addr, cp);
	}
	if (cpstart) {
	    *(cpstart - 1) = (byte)(cp - cpstart);
	}

	/*
	 * Compute the length while we're here.  Then restart at the
	 * front of the packet.
	 */
	length = cp - ((byte *) task_send_buffer);
	cp = (byte *) task_send_buffer;
	assert(!(np->slsp_node_cksum) || np->slsp_node_len == length);

	/*
	 * Compute the lifetime
	 */
	if (np->slsp_node_type == SLSP_LSP_TIMEDOUT) {
	    assert(length == SLSP_LSP_FIXED_LEN);
	    lifetime = 0;
	} else if (np->slsp_node_life <= (time_sec + (time_t) 4)) {
	    lifetime = (time_t) 4;
	} else {
	    lifetime = np->slsp_node_life - time_sec;
	}

	/*
	 * If we need to compute the checksum, set the lifetime
	 * to zero in the header.  Then compute the checksum and
	 * put the real time back in
	 */
	SLSP_PUT_LSP(length,
		     ((np->slsp_node_cksum) ? lifetime : 0),
		     np->slsp_node_addr,
		     (BIT_TEST(np->slsp_node_flags, SLSP_NODEF_RTTYPE_ALT)
		       ? SLSP_LSP_RTTYPE_ALT : SLSP_LSP_RTTYPE),
		     np->slsp_node_seqnum,
		     np->slsp_node_cksum,
		     cp);

	if (!(np->slsp_node_cksum)) {
	    cp = (byte *) task_send_buffer;
	    np->slsp_node_cksum = SLSP_SET_LSP_CKSUM(cp, length);
	    np->slsp_node_len = length;
	    SLSP_PUT_LSP_LIFETIME(lifetime, cp);
	}

	/*
	 * Okdk.  Here we have a complete packet, and we know its
	 * length.  Send it to everyone who is waiting with baited
	 * breath for this.  We do this by walking his transmit
	 * bit array looking for guys with their bit set.
	 */
	tosend = np->slsp_node_xmt_nbits;
	cp = np->slsp_node_xmt_bits.slsp_bit_set;
	for (i = 0; tosend && i < SLSP_MAX_NEIGHBOURS; i += SLSP_BITSIZE) {
	    register slsp_bit_t tbit = *cp;
	    while (tbit) {
		register slsp_bit_t ibit = slsp_db_first_set[tbit];
		register slsp_neighbour *nbr = inp->slsp_bit_nbrs[i + ibit];

		assert(nbr);
		slsp_send(nbr, (byte *) task_send_buffer, length);
		tosend--;
		ibit = ~(nbr->slsp_nbr_bitmask);
		tbit &= ibit;
		if (!SLSP_NBR_PTP_TYPE(nbr)) {
		    *cp &= ibit;
		    np->slsp_node_xmt_nbits--;
		}
	    }
	    cp++;
	}

	/*
	 * All sent.  Mark this node so we don't send it again for
	 * a while.  Then pull it off the queue.  If it still has
	 * bits set put it at the end.
	 */
	np->slsp_node_xmt_time = time_sec + SLSP_MIN_SEND_INTERVAL;
	SLSP_XMT_REMOVE(np);
	if (np->slsp_node_xmt_nbits) {
	    register slsp_db_node *np_prev = SLSP_XMT_PREV(inp, inp);

	    while (np_prev
	      && np_prev->slsp_node_xmt_time > np->slsp_node_xmt_time) {
		np_prev = SLSP_XMT_PREV(inp, np_prev);
	    }
	    if (np_prev) {
		SLSP_XMT_APPEND(np_prev, np);
	    } else {
		SLSP_XMT_APPEND(inp, np);
	    }
	}
    }


    /*
     * Same thing for the sequence numbers queue.
     */
    length = 0;
    fsp = inp->slsp_full_queue.slsp_fq_next;
    while (fsp != &(inp->slsp_full_queue)) {
	register slsp_neighbour *nbr;

	if (fsp->slsp_fq_time > time_sec) {
	    break;
	}
	fsp_next = fsp->slsp_fq_next;
	if (!length) {
	    length = slsp_db_full_seq_format(inp, &send_fsp);
	}
	nbr = fsp->slsp_fq_nbr;
	slsp_send(nbr, send_fsp, length);
	fsp->slsp_fq_count++;
	if (nbr->slsp_nbr_type != SLSP_NTYPE_BCAST
	  && fsp->slsp_fq_count >= SLSP_FULL_SEQ_COUNT) {
	    SLSP_FSQ_REMOVE(fsp);
	    nbr->slsp_nbr_fsq = (slsp_full_seq_q *) 0;
	    SLSP_DB_FSQ_FREE(fsp);
	} else {
	    register slsp_full_seq_q *fsp_prev;

	    SLSP_FSQ_REMOVE(fsp);
	    fsp->slsp_fq_time = time_sec + MAX(nbr->slsp_nbr_hellointerval,
					       SLSP_FULL_SEQ_MIN_TIME);
	    fsp_prev = inp->slsp_full_queue.slsp_fq_prev;
	    while (fsp_prev->slsp_fq_time > fsp->slsp_fq_time) {
		fsp_prev = fsp_prev->slsp_fq_prev;
	    }
	    SLSP_FSQ_APPEND(fsp_prev, fsp);
	}
	fsp = fsp_next;
    }


    /*
     * Done for now.  Figure out when we should do this next.  Terminate
     * any task job.  If the queue is now empty reset the timer.  If
     * we broadcast our share don't send anything for a second.  Otherwise
     * set the timer for the next expiry.
     */
    if (BIT_TEST(inp->slsp_flags, SLSPF_XMT_JOB)) {
	task_job_delete(inp->slsp_job_xmt);
	BIT_RESET(inp->slsp_flags, SLSPF_XMT_JOB);
	inp->slsp_job_xmt = (task_job *) 0;
    }
    np = SLSP_XMT_NEXT(inp, inp);
    fsp = inp->slsp_full_queue.slsp_fq_next;
    if (fsp == &(inp->slsp_full_queue)) {
	fsp = (slsp_full_seq_q *) 0;
    }
    if (!np && !fsp) {
	if (BIT_TEST(inp->slsp_flags, SLSPF_XMT_TIMER)) {
	    task_timer_reset(inp->slsp_timer_xmt);
	    BIT_RESET(inp->slsp_flags, SLSPF_XMT_TIMER);
	    inp->slsp_next_xmt_time = (time_t) 0;
	}
	lifetime = (time_t) 0;
    } else if (sent >= SLSP_DB_MAX_XMT) {
	BIT_SET(inp->slsp_flags, SLSPF_XMT_THROTTLE);
	if (!(inp->slsp_next_xmt_time)
	  || inp->slsp_next_xmt_time != (time_sec + 1)) {
	    lifetime = (time_t) 1;
	} else {
	    lifetime = (time_t) 0;
	}
    } else {
	lifetime = (time_t) 0;
	if (np && np->slsp_node_xmt_time > time_sec) {
	    lifetime = np->slsp_node_xmt_time;
	}
	if (fsp && fsp->slsp_fq_time > time_sec) {
	    if (!lifetime || lifetime > fsp->slsp_fq_time) {
		lifetime = fsp->slsp_fq_time;
	    }
	}
	if (lifetime) {
	    lifetime -= time_sec;
	} else {
	    lifetime = (time_t) 1;
	}
    }

    if (lifetime) {
	if (!(inp->slsp_timer_xmt)) {
	    slsp_db_xmt_timer_create(inp, lifetime);
	} else if (lifetime == (time_t) 1
	  || !(inp->slsp_next_xmt_time)
	  || inp->slsp_next_xmt_time > (time_sec + lifetime)) {
	    task_timer_set(inp->slsp_timer_xmt,
			   (time_t) 0,
			   lifetime);
	    inp->slsp_next_xmt_time = time_sec + lifetime;
	    BIT_SET(inp->slsp_flags, SLSPF_XMT_TIMER);
	}
    }
}


/*
 * slsp_db_xmt_timeout - process a transmit timer expiry.  Basically
 *			 we blow out any competing task job, then
 *			 call the flush routine to flush out some routes.
 */
static void
slsp_db_xmt_timeout __PF2(tip, task_timer *,
			  interval, time_t)
{
    slsp_instance *inp = (slsp_instance *)(tip->task_timer_data);

    if (BIT_TEST(inp->slsp_flags, SLSPF_XMT_JOB)) {
	task_job_delete(inp->slsp_job_xmt);
	inp->slsp_job_xmt = (task_job *) 0;
    }

    BIT_RESET(inp->slsp_flags,
	      SLSPF_XMT_JOB|SLSPF_XMT_TIMER|SLSPF_XMT_THROTTLE);
    inp->slsp_next_xmt_time = (time_t) 0;
    slsp_db_xmt_flush(inp);
}


/*
 * slsp_db_xmt_timer_create - create and set the transmit timer
 */
static void
slsp_db_xmt_timer_create __PF2(inp, slsp_instance *,
			       offset, time_t)
{
    if (!(inp->slsp_timer_xmt)) {
	inp->slsp_timer_xmt = task_timer_create(inp->slsp_task,
						"Transmit",
						(flag_t) 0,
						(time_t) 0,
						offset,
						slsp_db_xmt_timeout,
						(void_t) inp);
    } else {
	task_timer_set(inp->slsp_timer_xmt, (time_t) 0, offset);
    }

    inp->slsp_next_xmt_time = time_sec + offset;
    BIT_SET(inp->slsp_flags, SLSPF_XMT_TIMER);
}


/*
 * slsp_db_xmt_shutdown - shut down the transmission jobs
 */
static void
slsp_db_xmt_shutdown __PF1(inp, slsp_instance *)
{
    if (inp->slsp_timer_xmt) {
	task_timer_delete(inp->slsp_timer_xmt);
	inp->slsp_timer_xmt = (task_timer *) 0;
	inp->slsp_next_xmt_time = (time_t) 0;
	BIT_RESET(inp->slsp_flags, SLSPF_XMT_TIMER|SLSPF_XMT_THROTTLE);
    }
    if (inp->slsp_job_xmt) {
	task_job_delete(inp->slsp_job_xmt);
	inp->slsp_job_xmt = (task_job *) 0;
	BIT_RESET(inp->slsp_flags, SLSPF_XMT_JOB);
    }
}


/*
 * slsp_db_xmt_job_run - transmit job run as a task job
 */
static void
slsp_db_xmt_job_run __PF1(tjp, task_job *)
{
    slsp_instance *inp = (slsp_instance *)(tjp->task_job_data);

    BIT_RESET(inp->slsp_flags, SLSPF_XMT_JOB);
    inp->slsp_job_xmt = (task_job *) 0;
    if (BIT_TEST(inp->slsp_flags, SLSPF_XMT_THROTTLE)) {
	/*
	 * Don't bother, wait for the timer.
	 */
	assert(BIT_TEST(inp->slsp_flags, SLSPF_XMT_TIMER));
    } else {
	slsp_db_xmt_flush(inp);
    }
}


/*
 * slsp_db_xmt_schedule - (re)schedule a run of the transmit queue
 */
static void
slsp_db_xmt_schedule __PF1(inp, slsp_instance *)
{
    slsp_db_node *np;
    slsp_full_seq_q *fsp;
    time_t nexttime;

    if (BIT_TEST(inp->slsp_flags, SLSPF_XMT_THROTTLE|SLSPF_XMT_JOB)
      || (inp->slsp_next_xmt_time && inp->slsp_next_xmt_time <= time_sec)) {
	return;
    }

    np = SLSP_XMT_NEXT(inp, inp);
    fsp = inp->slsp_full_queue.slsp_fq_next;
    if (fsp == &(inp->slsp_full_queue)) {
	fsp = (slsp_full_seq_q *) 0;
    }
    if (!np && !fsp) {
	return;
    }
    if (np) {
	nexttime = np->slsp_node_xmt_time;
    } else {
	nexttime = (time_t) 0;
    }
    if (fsp) {
	if (!nexttime || nexttime > fsp->slsp_fq_time) {
	    nexttime = fsp->slsp_fq_time;
	}
    }

    if (nexttime <= time_sec) {
	inp->slsp_job_xmt = task_job_create(inp->slsp_task,
					    TASK_JOB_FG,
					    "LSP Transmit",
					    slsp_db_xmt_job_run,
					    (void_t) inp);
	BIT_SET(inp->slsp_flags, SLSPF_XMT_JOB);
    } else if (!(inp->slsp_next_xmt_time)) {
	if (inp->slsp_timer_xmt) {
	    inp->slsp_next_xmt_time = nexttime;
	    task_timer_set(inp->slsp_timer_xmt,
			   (time_t) 0,
			   (nexttime - time_sec));
	    BIT_SET(inp->slsp_flags, SLSPF_XMT_TIMER);
	} else {
	    slsp_db_xmt_timer_create(inp, (nexttime - time_sec));
	}
    } else if (inp->slsp_next_xmt_time > (nexttime + 1)) {
	inp->slsp_next_xmt_time = nexttime;
	task_timer_set(inp->slsp_timer_xmt,
		       (time_t) 0,
		       (nexttime - time_sec));
    }
}


/*
 * slsp_db_sendto - send an LSP to a particular neighbour
 */
static void
slsp_db_sendto __PF2(nbr, slsp_neighbour *,
		     np, slsp_db_node *)
{
    /*
     * Don't send to a broadcast neighbour if we're the
     * designated router and we're going to broadcast the
     * thing anyway.
     */
    if (np->slsp_node_xmt_nbits) {
	if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST_NBR) {
	    register slsp_neighbour *nbr_dr = nbr->slsp_nbr_parent;

	    if (nbr_dr->slsp_nbr_dr == nbr_dr
	      && SLSP_BIT_TEST(&(np->slsp_node_xmt_bits), nbr_dr)) {
		return;
	    }
	}
	SLSP_BIT_SET(&(np->slsp_node_xmt_bits), nbr);
    } else {
	register slsp_instance *inp = nbr->slsp_nbr_instance;

	if (np->slsp_node_xmt_time > time_sec) {
	    register slsp_db_node *np_prev = SLSP_XMT_PREV(inp, inp);

	    while (np_prev) {
		if (np_prev->slsp_node_xmt_time <= np->slsp_node_xmt_time) {
		    break;
		}
		np_prev = SLSP_XMT_PREV(inp, np_prev);
	    }
	    if (np_prev) {
		SLSP_XMT_APPEND(np_prev, np);
	    } else {
		SLSP_XMT_APPEND(inp, np);
	    }
	} else {
	    np->slsp_node_xmt_time = time_sec;
	    SLSP_XMT_APPEND(inp, np);
	}
	np->slsp_node_xmt_bits.slsp_bit_set[nbr->slsp_nbr_offset]
	  = nbr->slsp_nbr_bitmask;
	np->slsp_node_xmt_nbits = 1;
	SLSP_DB_XMT_SCHEDULE(inp);
    }
}


#ifdef	notdef
/*
 * slsp_db_sendall - send all the LSP's we know to a particular neighbour
 */
static void
slsp_db_sendall __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp;
    register int bword = nbr->slsp_nbr_offset;
    register byte bmask = nbr->slsp_nbr_bitmask;
    register slsp_db_node *np, *np_prev;
    int added = 0;

    inp = nbr->slsp_nbr_instance;
    np = SLSP_FULL_NEXT(inp, inp);
    while (np) {
	if (np->slsp_node_xmt_nbits) {
	    if (!(np->slsp_node_xmt_bits.slsp_bit_set[bword] & bmask)) {
		np->slsp_node_xmt_bits.slsp_bit_set[bword] |= bmask;
		np->slsp_node_xmt_nbits++;
	    }
	} else {
	    added++;
	    np->slsp_node_xmt_bits.slsp_bit_set[bword] = bmask;
	    np->slsp_node_xmt_nbits = 1;
	    if (np->slsp_node_xmt_time <= time_sec) {
		np->slsp_node_xmt_time = time_sec;
		SLSP_XMT_APPEND(inp, np);
	    } else {
		np_prev = SLSP_XMT_PREV(inp, inp);

		while (np_prev) {
		    if (np_prev->slsp_node_xmt_time <= np->slsp_node_xmt_time) {
			break;
		    }
		    np_prev = SLSP_XMT_PREV(inp, np_prev);
		}
		if (np_prev) {
		    SLSP_XMT_APPEND(np_prev, np);
		} else {
		    SLSP_XMT_APPEND(inp, np);
		}
	    }
	}
	np = SLSP_FULL_NEXT(inp, np);
    }

    if (added) {
	SLSP_DB_XMT_SCHEDULE(inp);
    }
}
#endif	/* notdef */


/*
 * slsp_db_flood - flood this LSP to all our up neighbours except (maybe)
 *		   the guy who sent it to us.
 */
static void
slsp_db_flood __PF2(np, slsp_db_node *,
		    nbr_nosend, slsp_neighbour *)
{
    register slsp_instance *inp;
    register slsp_neighbour *nbr;
    register slsp_bits *sbits;
    int on_list = 0;

    inp = np->slsp_node_instance;
    if (np->slsp_node_xmt_nbits) {
	on_list = 1;
    }
    sbits = &(np->slsp_node_xmt_bits);

    for (nbr = inp->slsp_nbrs; nbr; nbr = nbr->slsp_nbr_next) {
	if (nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT) {
	    register slsp_neighbour *send_nbr;
	    if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST) {
		send_nbr = nbr->slsp_nbr_dr;
		if (!send_nbr) {
		    continue;
		}
		if (send_nbr == nbr) {
		    if (!(nbr->slsp_nbr_n_adjacent)) {
			continue;
		    }
		    if (on_list && !SLSP_BIT_TEST(sbits, send_nbr)) {
			register slsp_neighbour *bnbr = send_nbr->slsp_nbr_list;

			while (bnbr && SLSP_NBR_GOT_HELLO(bnbr)) {
			    if (SLSP_BIT_TEST(sbits, bnbr)) {
				sbits->slsp_bit_set[bnbr->slsp_nbr_offset]
				  &= ~(bnbr->slsp_nbr_bitmask);
				if (!(--sbits->slsp_bit_n_set)) {
				    break;
				}
			    }
			    bnbr = bnbr->slsp_nbr_next;
			}
		    }
		}
	    } else {
		send_nbr = nbr;
	    }
	    if (send_nbr != nbr_nosend) {
		SLSP_BIT_SET(sbits, send_nbr);
	    } else {
		SLSP_BIT_CLR(sbits, send_nbr);
	    }
	}
    }

    if (!on_list && np->slsp_node_xmt_nbits) {
	if (np->slsp_node_xmt_time <= time_sec) {
	    np->slsp_node_xmt_time = time_sec;
	    SLSP_XMT_APPEND(inp, np);
	} else {
	    register slsp_db_node *np_prev = SLSP_XMT_PREV(inp, inp);

	    while (np_prev) {
		if (np_prev->slsp_node_xmt_time <= np->slsp_node_xmt_time) {
		    break;
		}
		np_prev = SLSP_XMT_PREV(inp, np_prev);
	    }
	    if (np_prev) {
		SLSP_XMT_APPEND(np_prev, np);
	    } else {
		SLSP_XMT_APPEND(inp, np);
	    }
	}
	SLSP_DB_XMT_SCHEDULE(inp);
    } else if (on_list && !(np->slsp_node_xmt_nbits)) {
	SLSP_XMT_REMOVE(np);
    }
}


/*
 * slsp_db_reoriginate - originate a local LSP with an updated sequence number
 */
static void
slsp_db_reoriginate __PF2(np, slsp_db_node *,
			  seqnum, slsp_seqnum_t)
{
    slsp_seqnum_t nseqnum;
    slsp_instance *inp = np->slsp_node_instance;
    register slsp_db_node *np_next;

    assert(SLSP_IS_LOCAL_LSP(np));

    inp->slsp_full_seq_pkt_time = (time_t) 0;
    nseqnum = SLSP_SEQNUM_NEXT(seqnum);
    np->slsp_node_seqnum = nseqnum;
    np->slsp_node_cksum = 0;
    np->slsp_node_len = 0;
    np->slsp_node_life = time_sec + SLSP_LIFE_MAX;
    if (np->slsp_node_life_timeout) {
	np_next = SLSP_LIFE_NEXT(inp, np);
	SLSP_LIFE_REMOVE(np);
    } else {
	np_next = SLSP_LIFE_NEXT(inp, inp);
    }
    np->slsp_node_life_timeout = time_sec + SLSP_LIFE_REORIGINATE;

    while (np_next
      && np_next->slsp_node_life_timeout < np->slsp_node_life_timeout) {
	np_next = SLSP_LIFE_NEXT(inp, np_next);
    }
    SLSP_LIFE_PREPEND((np_next ? np_next : ((slsp_db_node *) inp)), np);

    if (((slsp_db_node *)(inp->slsp_lists.slsp_life_next)) == np) {
	SLSP_DB_LIFE_SCHEDULE(inp);
    }

    slsp_db_flood(np, (slsp_neighbour *) 0);
}


/*
 * slsp_db_dereference - dereference a node, deleting it if it is
 *			 a placeholder and the refcount is zero.
 */
static void
slsp_db_dereference __PF1(np, slsp_db_node *)
{
    assert(np->slsp_node_refcount);

    if (--(np->slsp_node_refcount) == 0
      && np->slsp_node_type == SLSP_LSP_PLACEHOLDER) {
	slsp_node_remove(np);
	if (np->slsp_node_addr) {
	    sockfree(np->slsp_node_addr);
	}
	SLSP_DB_NODE_FREE(np);
    }
}


/*
 * slsp_db_expire - expire an LSP.  Blow off all the links and AS numbers,
 *		    move it around on the lifetime queue and flood it
 *		    out to our neighbours.
 */
static void
slsp_db_expire __PF3(np, slsp_db_node *,
		     seqnum, slsp_seqnum_t,
		     nbr, slsp_neighbour *)
{
    slsp_instance *inp = np->slsp_node_instance;
    slsp_db_link *lp;
    slsp_db_node *lnp;

    /*
     * First blow off the AS number queue.  Local and remote nodes
     * do this differently.
     */
    if (np->slsp_node_aslist.slspdb_as_count) {
	register slsp_db_as *asp = np->slsp_node_aslist.slspdb_as_next;

	do {
	    register slsp_db_as *as_next = asp->slspdb_as_next;

	    SLSP_DB_AS_FREE(asp);
	    asp = as_next;
	} while (asp && asp != &(np->slsp_node_aslist));
	np->slsp_node_aslist.slspdb_as_count = 0;
	np->slsp_node_aslist.slspdb_as_next = (slsp_db_as *) 0;
    }
    np->slsp_node_aslist.slspdb_as_next
      = np->slsp_node_aslist.slspdb_as_prev = (slsp_db_as *) 0;

    /*
     * Now the links
     */
    lp = np->slsp_node_linklist.slspdb_link_next;
    while (lp && lp != &(np->slsp_node_linklist)) {
	register slsp_db_link *lp_next = lp->slspdb_link_next;

	if (lp->slspdb_link_node) {
	    SLSP_NODE_DEREFERENCE(lp->slspdb_link_node);
	}
	if (lp->slspdb_link_nbr) {
	    lp->slspdb_link_nbr->slsp_nbr_link = (slsp_db_link *) 0;
	}
	SLSP_DB_LINK_FREE(lp);
	lp = lp_next;
    }
    np->slsp_node_linklist.slspdb_link_prev
      = np->slsp_node_linklist.slspdb_link_next = (slsp_db_link *) 0;
    np->slsp_node_n_nexthops = 0;

    /*
     * If he is on the route list take him off.  If there is a route,
     * blow it out now.  Schedule an SPF since he was previously
     * reachable.
     */
    if (np->slsp_node_onlist) {
	if (np->slsp_node_rt) {
	    rt_open(inp->slsp_task);
	    (void) rt_delete(np->slsp_node_rt);
	    rt_close(inp->slsp_task, &(inp->slsp_gw), 1, NULL);
	    np->slsp_node_rt = (rt_entry *) 0;
	}
	SLSP_RT_REMOVE(np);
	np->slsp_node_onlist = SLSP_NRT_NONE;
	SLSP_SPF_SCHEDULE(inp);
    }

    /*
     * Remove him from the full list and the lifetime queue if he's on either.
     * Note that he is timed out.
     */
    if (np->slsp_node_type != SLSP_LSP_PLACEHOLDER) {
	np->slsp_node_cksum = 0;
	np->slsp_node_len = 0;
	np->slsp_node_life = (time_t) 0;
	SLSP_LIFE_REMOVE(np);
	if (np->slsp_node_type != SLSP_LSP_TIMEDOUT) {
	    SLSP_FULL_REMOVE(np);
	    inp->slsp_full_seq_entries--;
	}
	inp->slsp_full_seq_pkt_time = (time_t) 0;
    }
    np->slsp_node_type = SLSP_LSP_TIMEDOUT;

    /*
     * Set the sequence number as requested, then put this back on
     * the lifetime list.  Search the list from the front since the
     * timeout time is relatively short.
     */
    np->slsp_node_seqnum = seqnum;
    np->slsp_node_life_timeout = time_sec + SLSP_LIFE_EXPIRED;
    lnp = SLSP_LIFE_NEXT(inp, inp);
    while (lnp) {
	if (lnp->slsp_node_life_timeout >= np->slsp_node_life_timeout) {
	    break;
	}
	lnp = SLSP_LIFE_NEXT(inp, lnp);
    }
    SLSP_LIFE_PREPEND((lnp ? lnp : ((slsp_db_node *) inp)), np);

    if (((slsp_db_node *)(inp->slsp_lists.slsp_life_next)) == np) {
	SLSP_DB_LIFE_SCHEDULE(inp);
    }

    /*
     * Finally, flood this out to all our guys except maybe the
     * neighbour who sent it to us.
     */
    slsp_db_flood(np, nbr);
}


/*
 * slsp_db_life_timeout - process a lifetime timer time out.  
 */
static void
slsp_db_life_timeout __PF2(tip, task_timer *,
			   interval, time_t)
{
    slsp_instance *inp = (slsp_instance *)(tip->task_timer_data);
    slsp_db_node *np, *np_next;

    np_next = SLSP_LIFE_NEXT(inp, inp);
    while ((np = np_next)) {
	np_next = SLSP_LIFE_NEXT(inp, np);
	if (np->slsp_node_life_timeout > time_sec) {
	    break;
	}
	/*
	 * Got one.  If this is a local node, reoriginate it.
	 * If this is an expired node, remove it from the tree.
	 * Otherwise expire the node.
	 */
	if (SLSP_IS_LOCAL_LSP(np)) {
	    if (!(np->slsp_node_cksum)) {
		SLSP_LIFE_REMOVE(np);
		if (!(np->slsp_node_life_timeout)) {
		    trace_tf(inp->slsp_trace_options,
			     TR_ALL,
			     LOG_WARNING,
			     ("slsp_db_life_timeout: local node ID %A not being timed out!!?",
			      np->slsp_node_addr));
		} else {
		    register slsp_db_node *np_prev;

		    trace_tf(inp->slsp_trace_options,
			     TR_ALL,
			     LOG_WARNING,
			     ("slsp_db_life_timeout: local node ID %A has no checksum!! Why?",

			      np->slsp_node_addr));
		    np->slsp_node_life_timeout = time_sec
		      + SLSP_LIFE_REORIGINATE;
		    np_prev = SLSP_LIFE_PREV(inp, inp);
		    while (np_prev && np_prev->slsp_node_life_timeout
		      > np->slsp_node_life_timeout) {
			np_prev = SLSP_LIFE_PREV(inp, np_prev);
		    }
		    SLSP_LIFE_APPEND((np_prev ? np_prev : (slsp_db_node *)inp),
				     np);
		}
	    } else {
		trace_tf(inp->slsp_trace_options,
			 TR_NORMAL|TR_STATE,
			 0,
			("slsp_db_life_timeout: reoriginating local node ID %A",
			 np->slsp_node_addr));
		slsp_db_reoriginate(np, np->slsp_node_seqnum);
	    }
	} else if (SLSP_IS_ACTIVE_LSP(np)) {
	    trace_tf(inp->slsp_trace_options,
		     TR_NORMAL|TR_STATE,
		     0,
		     ("slsp_db_life_timeout: node ID %A expired",
		      np->slsp_node_addr));
	    slsp_db_expire(np, np->slsp_node_seqnum, (slsp_neighbour *) 0);
	} else {
	    assert(np->slsp_node_type == SLSP_LSP_TIMEDOUT);
	    SLSP_LIFE_REMOVE(np);
	    if (np->slsp_node_xmt_nbits) {
		SLSP_XMT_REMOVE(np);
		bzero((caddr_t)&(np->slsp_node_xmt_bits), sizeof(slsp_bits));
	    }
	    if (np->slsp_node_refcount) {
		trace_tf(inp->slsp_trace_options,
			 TR_NORMAL|TR_STATE,
			 0,
			 ("slsp_db_life_timeout: node ID %A remnant timed out with refcount %u, becoming placeholder",
			  np->slsp_node_addr,
			  np->slsp_node_refcount));
		np->slsp_node_type = SLSP_LSP_PLACEHOLDER;
		np->slsp_node_cksum = 0;
		np->slsp_node_life = (time_t) 0;
		np->slsp_node_life_timeout = (time_t) 0;
	   } else {
		trace_tf(inp->slsp_trace_options,
			 TR_NORMAL|TR_STATE,
			 0,
			 ("slsp_db_life_timeout: node ID %A remnant timed out and removed",
			  np->slsp_node_addr));
		slsp_node_remove(np);
		if (np->slsp_node_addr) {
		    sockfree(np->slsp_node_addr);
		}
		SLSP_DB_NODE_FREE(np);
	    }
	}
    }

    np = SLSP_LIFE_NEXT(inp, inp);
    if (!np) {
	inp->slsp_next_life_timeout = (time_t) 0;
    } else {
	task_timer_set(inp->slsp_timer_life,
		       (time_t) 0,
		       (np->slsp_node_life_timeout - time_sec));
	inp->slsp_next_life_timeout = np->slsp_node_life_timeout;
    }
}


/*
 * slsp_db_life_schedule - (re)schedule the lifetime expiry
 */
static void
slsp_db_life_schedule __PF1(inp, slsp_instance *)
{
    slsp_db_node *np;

    np = SLSP_LIFE_NEXT(inp, inp);
    if (np) {
	if (inp->slsp_timer_life) {
	    if (!(inp->slsp_next_life_timeout)
	      || inp->slsp_next_life_timeout > np->slsp_node_life_timeout) {
		time_t offset = (np->slsp_node_life_timeout > time_sec)
		  ? (np->slsp_node_life_timeout - time_sec) : ((time_t) 1);
		task_timer_set(inp->slsp_timer_life, (time_t) 0, offset);
		inp->slsp_next_life_timeout = time_sec + offset;
	    }
	} else {
	    time_t offset = (np->slsp_node_life_timeout > time_sec)
	      ? (np->slsp_node_life_timeout - time_sec) : ((time_t) 1);
	    inp->slsp_timer_life = task_timer_create(inp->slsp_task,
						     "Lifetime",
						     (flag_t) 0,
						     (time_t) 0,
						     offset,
						     slsp_db_life_timeout,
						     (void_t) inp);
	    inp->slsp_next_life_timeout = time_sec + offset;
	}
    }
}



/*
 * slsp_db_send_stop - stop sending to this neighbour.  Remove his bit
 *		       from all nodes on the transmit queue, removing
 *		       any nodes which end up with no bit set.
 */
static void
slsp_db_send_stop __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp = nbr->slsp_nbr_instance;
    register int bword = nbr->slsp_nbr_offset;
    register byte bmask = nbr->slsp_nbr_bitmask;
    register slsp_db_node *np, *np_next;
    register int do_bcast = 0;

    if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST) {
	do_bcast = 1;
    }

    np = SLSP_XMT_NEXT(inp, inp);
    while (np) {
	np_next = SLSP_XMT_NEXT(inp, np);
	if ((np->slsp_node_xmt_bits.slsp_bit_set[bword] & bmask)) {
	    np->slsp_node_xmt_bits.slsp_bit_set[bword] &= ~bmask;
	    np->slsp_node_xmt_nbits--;
	    if (do_bcast && np->slsp_node_xmt_nbits) {
		register slsp_neighbour *bnbr = nbr->slsp_nbr_list;

		while (bnbr && SLSP_NBR_GOT_HELLO(bnbr)) {
		    if (SLSP_BIT_TEST(&(np->slsp_node_xmt_bits), bnbr)) {
		      np->slsp_node_xmt_bits.slsp_bit_set[bnbr->slsp_nbr_offset]
			  &= ~(bnbr->slsp_nbr_bitmask);
			np->slsp_node_xmt_nbits--;
			if (!(np->slsp_node_xmt_nbits)) {
			    break;
			}
		    }
		    bnbr = bnbr->slsp_nbr_next;
		}
	    }
	    if (!(np->slsp_node_xmt_nbits)) {
		SLSP_XMT_REMOVE(np);
	    }
	}
	np = np_next;
    }

    if (nbr->slsp_nbr_fsq) {
	SLSP_FSQ_REMOVE(nbr->slsp_nbr_fsq);
	SLSP_DB_FSQ_FREE(nbr->slsp_nbr_fsq);
	nbr->slsp_nbr_fsq = (slsp_full_seq_q *) 0;
    }
}


#ifdef	notdef
/*
 * slsp_db_send_change - all stuff queued to be sent to an old neighbour,
 *			 should be sent to a new neighbour instead.
 */
static void
slsp_db_send_change __PF2(onbr, slsp_neighbour *,
			  nnbr, slsp_neighbour *)
{
    slsp_instance *inp;
    register int obword, nbword;
    register byte obmask, nbmask;
    register slsp_db_node *np, *np_next;

    if (!onbr) {
	return;
    }
    if (!nnbr) {
	slsp_db_send_stop(nnbr);
	return;
    }

    inp = onbr->slsp_nbr_instance;
    assert(inp == nnbr->slsp_nbr_instance);
    np = SLSP_XMT_NEXT(inp, inp);
    if (np) {
	obword = onbr->slsp_nbr_offset;
	obmask = onbr->slsp_nbr_bitmask;
	nbword = nnbr->slsp_nbr_offset;
	nbmask = nnbr->slsp_nbr_bitmask;

	do {
	    if ((np->slsp_node_xmt_bits.slsp_bit_set[obword] & obmask)) {
		np->slsp_node_xmt_bits.slsp_bit_set[obword] &= ~obmask;
		if ((np->slsp_node_xmt_bits.slsp_bit_set[nbword] & nbmask)) {
		    np->slsp_node_xmt_nbits--;
		} else {
		    np->slsp_node_xmt_bits.slsp_bit_set[nbword] |= nbmask;
		}
	    }
	} while ((np = SLSP_XMT_NEXT(inp, np)));
    }
}
#endif	/* notdef */


/*
 * slsp_db_add_placeholder - add a placeholder node to the tree
 *			     for reference by other nodes.  This is actually
 *			     the only way we add nodes, things that
 *			     want other than a placeholder convert it
 *			     to something else.
 */
static slsp_db_node *
slsp_db_add_placeholder __PF3(inp, slsp_instance *,
			      addr, sockaddr_un *,
			      found_np, slsp_db_node *)
{
    slsp_db_node *np;
    sockaddr_un *mask;

    /*
     * Decide what the mask should be.  Either the route mask, if the
     * address is "local" to the instance, or the natural network mask.
     */
    if ((sock2ip(addr) & sock2ip(inp->slsp_mask))
      == (sock2ip(inp->slsp_addr) & sock2ip(inp->slsp_mask))) {
	mask = inp->slsp_rtmask;
    } else {
	mask = inet_mask_natural(addr);
    }


    /*
     * Fetch a node.  Initialize what we can, then stick it in the tree.
     */
    np = SLSP_DB_NODE_ALLOC();
    np->slsp_node_addr = sockdup(addr);
    np->slsp_node_rtmask = mask;
    np->slsp_node_type = SLSP_LSP_PLACEHOLDER;
    np->slsp_node_onlist = SLSP_NRT_NONE;
    np->slsp_node_instance = inp;

    slsp_node_insert(np, found_np);

    /*
     * Return the result, let the caller refcount it if he wants
     */
    return np;
}


/*
 * slsp_db_init - initialize this instance's SLSP database.  What we
 *		  mostly do is create our local node and add it to the
 *		  tree.
 */
void
slsp_db_init __PF1(inp, slsp_instance *)
{
    slsp_db_node *np;

    assert(!(inp->slsp_local_node) && !(inp->slsp_nodes));

    /*
     * Fetch a node structure
     */
    SLSP_DB_NODE_GET(np);

    /*
     * Fill it in with stuff about ourselves.  At this point we
     * have no links in the node, and no AS numbers.
     */
    np->slsp_node_instance = inp;
    np->slsp_node_addr = sockdup(inp->slsp_addr);
    np->slsp_node_rtmask = inp->slsp_rtmask;
    np->slsp_node_type = SLSP_LSP_LOCALRTR;
    np->slsp_node_onlist = SLSP_NRT_NONE;
    np->slsp_node_seqnum = SLSP_SEQNUM_MIN;
    np->slsp_node_aslist.slspdb_as_prev
      = np->slsp_node_aslist.slspdb_as_next = &(np->slsp_node_aslist);
    np->slsp_node_linklist.slspdb_link_prev
      = np->slsp_node_linklist.slspdb_link_next = &(np->slsp_node_linklist);
    inp->slsp_local_node = np;

    /*
     * Put it in the tree, and on the full list.  This'll do for now.
     */
    slsp_node_insert(np, (slsp_db_node *) 0);
    SLSP_FULL_APPEND(inp, np);
    inp->slsp_full_seq_entries++;
}

/*
 * slsp_db_down - a neighbour went down
 */
void
slsp_db_down __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp;
    slsp_db_node *np;
    slsp_db_link *lp;
    slsp_neighbour *pn_nbr;
    int changed_local = 0;
    int need_spf = 0;

    assert(nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT);
    nbr->slsp_nbr_state = SLSP_NBR_STATE_DOWN;
    inp = nbr->slsp_nbr_instance;

    switch (nbr->slsp_nbr_type) {
    case SLSP_NTYPE_PTP:
    case SLSP_NTYPE_PTP_PEER:
	/*
	 * Make sure we don't send him any more stuff.
	 */
	slsp_db_send_stop(nbr);

	/*
	 * Deference his node and pull the link out of the
	 * local node.  Make the local node changed.  Blow away
	 * the link structure.
	 */
	np = inp->slsp_local_node;
	lp = nbr->slsp_nbr_link;
	if (lp->slspdb_link_newbucket
	  && (lp->slspdb_link_next->slspdb_link_cost == lp->slspdb_link_cost)) {
	    assert(!(lp->slspdb_link_next->slspdb_link_newbucket));
	    lp->slspdb_link_next->slspdb_link_newbucket = 1;
	}
	if (SLSP_IS_ACTIVE_LSP(lp->slspdb_link_node)) {
	    need_spf = 1;
	}
	SLSP_LINK_REMOVE(lp);
	SLSP_NODE_DEREFERENCE(lp->slspdb_link_node);
	SLSP_DB_LINK_FREE(lp);
	nbr->slsp_nbr_link = (slsp_db_link *) 0;

	/*
	 * If we removed the last link, just pull this guy off the
	 * lifetime list.  We'll re-originate when we get a new
	 * node.
	 */
	if (np->slsp_node_linklist.slspdb_link_next
	  == &(np->slsp_node_linklist)) {
	    SLSP_LIFE_REMOVE(np);
	    np->slsp_node_life_timeout = (time_t) 0;
	    np->slsp_node_cksum = 0;
	} else {
	    changed_local = 1;
	}

	/*
	 * All done, all that remains is to flood the local node.  Done below.
	 */
	break;

    case SLSP_NTYPE_BCAST_NBR:
	/*
	 * Don't send him any more stuff.
	 */
	slsp_db_send_stop(nbr);

	/*
	 * If we are the designated router we'll need to pull his link
	 * out of the pseudo-node and reoriginate.  Otherwise just
	 * remove his neighbour reference from the pseudo-node if
	 * he has one.
	 */
	pn_nbr = nbr->slsp_nbr_parent;
	np = pn_nbr->slsp_nbr_node;
	lp = nbr->slsp_nbr_link;
	if (lp) {
	    if (SLSP_IS_ACTIVE_LSP(lp->slspdb_link_node)) {
		need_spf = 1;
	    }
	    if (pn_nbr->slsp_nbr_dr == pn_nbr) {
		changed_local = 1;
		SLSP_LINK_REMOVE(lp);
		SLSP_NODE_DEREFERENCE(lp->slspdb_link_node);
		SLSP_DB_LINK_FREE(lp);
		assert(pn_nbr->slsp_nbr_n_adjacent);
		if (!(--pn_nbr->slsp_nbr_n_adjacent)) {
		    /*
		     * No one to send to any more, just stop this.  Remove
		     * his full sequence queue entry while we're at it.
		     */
	    	    slsp_db_send_stop(pn_nbr);

		    assert(inp->slsp_needs_full_seq && !(pn_nbr->slsp_nbr_fsq));
		    if (!(--inp->slsp_needs_full_seq)) {
			slsp_db_full_seq_remove(inp);
		    }
		}
	    } else {
		lp->slspdb_link_nbr = (slsp_neighbour *) 0;
	    }
	    nbr->slsp_nbr_link = (slsp_db_link *) 0;
	} else {
	    assert(pn_nbr->slsp_nbr_dr != pn_nbr);
	}
	break;

    default:
	np = (slsp_db_node *) 0;
	break;
    }

    /*
     * If we changed the local node and we aren't already trying to
     * resend it, reoriginate.
     */
    if (changed_local && np->slsp_node_cksum) {
	slsp_db_reoriginate(np, np->slsp_node_seqnum);
    }
    if (need_spf) {
	SLSP_SPF_SCHEDULE(inp);
    }
}


/*
 * slsp_db_ptp_up - a PTP neighbour came up
 */
void
slsp_db_ptp_up __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp;
    slsp_db_node *np, *lcl_np;
    slsp_db_link *lp, *lp_prev;
    slsp_full_seq_q *fsp;

    assert(!(nbr->slsp_nbr_link));

    /*
     * First find him in the tree.  If he isn't there
     * add a placeholder.
     */
    inp = nbr->slsp_nbr_instance;
    SLSP_NODE_LOCATE(inp, nbr->slsp_nbr_id, np);

    if (!np || sock2ip(np->slsp_node_addr) != sock2ip(nbr->slsp_nbr_id)) {
	np = slsp_db_add_placeholder(inp,
				     nbr->slsp_nbr_id,
				     np);
    }
    SLSP_NODE_REFERENCE(np);

    /*
     * Fetch a link structure and fill it in.  Attach this to
     * the local node.
     */
    SLSP_DB_LINK_GET(lp);
    nbr->slsp_nbr_link = lp;
    lp->slspdb_link_cost = nbr->slsp_nbr_cost;
    lp->slspdb_link_node = np;
    lp->slspdb_link_nbr = nbr;
    lcl_np = inp->slsp_local_node;
    lp_prev = lcl_np->slsp_node_linklist.slspdb_link_prev;

    while (lp_prev != &(lcl_np->slsp_node_linklist)) {
	if (lp_prev->slspdb_link_cost <= lp->slspdb_link_cost) {
	    break;
	}
	lp_prev = lp_prev->slspdb_link_prev;
    }
    if (lp_prev->slspdb_link_cost != lp->slspdb_link_cost) {
	lp->slspdb_link_newbucket = 1;
    }
    SLSP_LINK_APPEND(lp_prev, lp);

    /*
     * Okay, so far so good.  Bump the sequence number on the
     * local node and mark it changed.  Then flood the local
     * node and send the full database to the guy who just came
     * up.
     */
    if (lcl_np->slsp_node_cksum || !lcl_np->slsp_node_life_timeout) {
	slsp_db_reoriginate(lcl_np, lcl_np->slsp_node_seqnum);
    }
#ifdef	notdef
    slsp_db_sendall(nbr);
#endif	/* notdef */
    SLSP_DB_FSQ_GET(fsp);
    nbr->slsp_nbr_fsq = fsp;
    fsp->slsp_fq_time = time_sec;
    fsp->slsp_fq_nbr = nbr;
    SLSP_FSQ_APPEND(&(inp->slsp_full_queue), fsp);

    /*
     * Finally, decide whether we should run the SPF or not.  If none
     * is currently scheduled, see if we have a back link or not.
     */
    if (BIT_TEST(inp->slsp_flags, SLSPF_SPF)) {
	inp->slsp_spf_requested = time_sec;
    } else if (np->slsp_node_type == SLSP_LSP_ROUTER) {
	lp = np->slsp_node_linklist.slspdb_link_next;
	while (lp) {
	    if (lp->slspdb_link_node == lcl_np) {
		break;
	    }
	    lp = lp->slspdb_link_next;
	}
	if (lp) {
	    slsp_spf_schedule(inp);
	}
    }
}


/*
 * slsp_db_bcast_up - a broadcast neighbour came up
 */
void
slsp_db_bcast_up __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp;
    slsp_db_node *np, *lcl_np;
    slsp_db_link *lp;
    slsp_neighbour *bcast_nbr;
    int need_spf = 0;

    /*
     * Better be a broadcast neighbour.  Better not have a link already.
     */
    assert(nbr->slsp_nbr_type == SLSP_NTYPE_BCAST_NBR);
    assert(!(nbr->slsp_nbr_link));

    /*
     * We don't care much about the coming's and going's of
     * broadcast neighbours if there is no designated router,
     * so check this now.
     */
    bcast_nbr = nbr->slsp_nbr_parent;
    if (!(bcast_nbr->slsp_nbr_dr)) {
	return;
    }

    /*
     * Okay, more serious now.  If someone else is the designated
     * router we'll need to look for a link to our guy in his LSP.
     * Otherwise we'll need to add a link to our LSP.
     */
    inp = nbr->slsp_nbr_instance;
    if (bcast_nbr->slsp_nbr_dr != bcast_nbr) {
	lcl_np = bcast_nbr->slsp_nbr_node;
	if (lcl_np->slsp_node_type != SLSP_LSP_NBRNET) {
	    return;
	}
	lp = lcl_np->slsp_node_linklist.slspdb_link_next;
	while (lp) {
	    if (!(lp->slspdb_link_nbr)
	      && sock2ip(lp->slspdb_link_node->slsp_node_addr)
		== sock2ip(nbr->slsp_nbr_id)) {
		lp->slspdb_link_nbr = nbr;
		nbr->slsp_nbr_link = lp;
		need_spf = 1;
		break;
	    }
	    lp = lp->slspdb_link_next;
	}
    } else {
	/*
	 * Find him in the tree.  If he isn't there add a placeholder.
	 */
	SLSP_NODE_LOCATE(inp, nbr->slsp_nbr_id, np);
	if (!np || sock2ip(np->slsp_node_addr) != sock2ip(nbr->slsp_nbr_id)) {
	    np = slsp_db_add_placeholder(inp,
					 nbr->slsp_nbr_id,
					 np);
	}
	SLSP_NODE_REFERENCE(np);
	if (SLSP_IS_ACTIVE_LSP(np)) {
	    need_spf = 1;
	}

	/*
	 * Fetch a link structure and fill it in.  Attach this to
	 * the local node.
	 */
	SLSP_DB_LINK_GET(lp);
	nbr->slsp_nbr_link = lp;
	lp->slspdb_link_cost = 0;
	lp->slspdb_link_node = np;
	lp->slspdb_link_nbr = nbr;
	lcl_np = bcast_nbr->slsp_nbr_node;
	SLSP_LINK_PREPEND(&(lcl_np->slsp_node_linklist), lp);
	inp->slsp_full_seq_pkt_time = (time_t) 0;
	bcast_nbr->slsp_nbr_n_adjacent++;

	/*
	 * Okay, so far so good.  Reoriginate the local node if
	 * we need to.
	 */
	if (lcl_np->slsp_node_cksum) {
	    slsp_db_reoriginate(lcl_np, lcl_np->slsp_node_seqnum);
	}

	/*
	 * Note that we have a new neighbour on the wire, and that
	 * we'll need to send out full sequence packets if we haven't
	 * been.
	 */
	if (bcast_nbr->slsp_nbr_n_adjacent == 1) {
	    register slsp_full_seq_q *fsp, *fsp_next;

	    inp->slsp_needs_full_seq++;
	    SLSP_DB_FSQ_GET(fsp);
	    nbr->slsp_nbr_fsq = fsp;
	    fsp->slsp_fq_time = time_sec + SLSP_FULL_SEQ_BCAST_INIT_TIME;
	    fsp->slsp_fq_nbr = bcast_nbr;
	    fsp_next = inp->slsp_full_queue.slsp_fq_next;
	    while (fsp_next->slsp_fq_time
	      && fsp_next->slsp_fq_time <= fsp->slsp_fq_time) {
		fsp_next = fsp_next->slsp_fq_next;
	    }
	    SLSP_FSQ_PREPEND(fsp_next, fsp);
	    if (inp->slsp_full_queue.slsp_fq_next == fsp) {
		SLSP_DB_XMT_SCHEDULE(inp);
	    }
	}
    }

    /*
     * Finally, schedule an SPF run if we need it
     */
    if (need_spf) {
	SLSP_SPF_SCHEDULE(inp);
    }
}


/*
 * slsp_db_dr_inform - we have a new designated router on one of our if's
 */
void
slsp_db_dr_inform  __PF2(nbr, slsp_neighbour *,
			 nbr_dr, slsp_neighbour *)
{
    slsp_instance *inp;
    slsp_db_node *np, *lcl_np, *old_np;
    slsp_db_link *lp, *lp_prev;
    slsp_neighbour *bcast_nbr;
    int need_spf = 0;

    /*
     * Better be a broadcast interface
     */
    assert(nbr->slsp_nbr_type == SLSP_NTYPE_BCAST);

    /*
     * If the designated router didn't actually change, ignore this.
     */
    if (nbr->slsp_nbr_dr == nbr_dr) {
	return;
    }

    /*
     * Process changes to the local router node first.  If we already
     * have a designated router, dereference that node.  Otherwise
     * (since we will have a new designated router) add a link to the
     * local node with an appropriate cost.
     */
    inp = nbr->slsp_nbr_instance;
    if (nbr->slsp_nbr_dr) {
	/*
	 * Remove all neighbour references from the
	 * links in this node.
	 */
	lp = nbr->slsp_nbr_link;
	assert(lp);
	old_np = lp->slspdb_link_node;
	if (SLSP_IS_ACTIVE_LSP(old_np)) {
	    need_spf = 1;
	}
	assert(old_np->slsp_node_nbr == nbr);
	if (old_np->slsp_node_type == SLSP_LSP_NBRNET) {
	    for (lp_prev = old_np->slsp_node_linklist.slspdb_link_next;
		 lp_prev && lp_prev != &(old_np->slsp_node_linklist);
		 lp_prev = lp_prev->slspdb_link_next) {
		if (lp_prev->slspdb_link_nbr) {
		    lp_prev->slspdb_link_nbr->slsp_nbr_link = (slsp_db_link *)0;
		    lp_prev->slspdb_link_nbr = (slsp_neighbour *) 0;
		}
	    }
	    old_np->slsp_node_type = SLSP_LSP_NET;
	}
	BIT_RESET(old_np->slsp_node_flags, SLSP_NODEF_LOCAL_LINK);
	old_np->slsp_node_nbr = (slsp_neighbour *) 0;
	SLSP_NODE_DEREFERENCE(old_np);
	slsp_db_send_stop(nbr->slsp_nbr_dr);
    } else {
	np = inp->slsp_local_node;
	SLSP_DB_LINK_GET(lp);
	nbr->slsp_nbr_link = lp;
	lp->slspdb_link_cost = nbr->slsp_nbr_cost;
	lp->slspdb_link_nbr = nbr;
	nbr->slsp_nbr_link = lp;
	lp_prev = np->slsp_node_linklist.slspdb_link_prev;
	while (lp_prev != &(np->slsp_node_linklist)) {
	    if (lp_prev->slspdb_link_cost <= lp->slspdb_link_cost) {
		break;
	    }
	    lp_prev = lp_prev->slspdb_link_prev;
	}
	if (lp_prev->slspdb_link_cost != lp->slspdb_link_cost) {
	    lp->slspdb_link_newbucket = 1;
	}
	SLSP_LINK_APPEND(lp_prev, lp);
	old_np = (slsp_db_node *) 0;
    }

    /*
     * If we have a new designated router, point the link at his
     * node.  Create the node if we haven't got one already.
     */
    if (nbr_dr) {
	/*
	 * Set the designated router address
	 */
	if (nbr->slsp_nbr_id) {
	    sock2ip(nbr->slsp_nbr_id) = sock2ip(nbr_dr->slsp_nbr_addr);
	} else {
	    nbr->slsp_nbr_id = sockdup(nbr_dr->slsp_nbr_addr);
	}
	SLSP_NODE_LOCATE(inp, nbr->slsp_nbr_id, np);
	if (!np || sock2ip(np->slsp_node_addr) != sock2ip(nbr->slsp_nbr_id)) {
	    np = slsp_db_add_placeholder(inp,
					 nbr->slsp_nbr_id,
					 np);
	}
	SLSP_NODE_REFERENCE(np);
	lp->slspdb_link_node = np;
	if (SLSP_IS_ACTIVE_LSP(np)) {
	    need_spf = 1;
	}
	nbr->slsp_nbr_node = np;
	np->slsp_node_nbr = nbr;
	BIT_SET(np->slsp_node_flags, SLSP_NODEF_LOCAL_LINK);
    } else {
	if (lp->slspdb_link_newbucket
	  && lp->slspdb_link_next->slspdb_link_cost == lp->slspdb_link_cost) {
	    assert(!lp->slspdb_link_next->slspdb_link_newbucket);
	    lp->slspdb_link_next->slspdb_link_newbucket = 1;
	}
	SLSP_LINK_REMOVE(lp);
	SLSP_DB_LINK_FREE(lp);
	nbr->slsp_nbr_link = (slsp_db_link *) 0;
	nbr->slsp_nbr_node = np = (slsp_db_node *) 0;
	sockfree(nbr->slsp_nbr_id);
	nbr->slsp_nbr_id = (sockaddr_un *) 0;
    }

    /*
     * Okay, now worry about the pseudonode.  If we were the
     * designated router, but no longer are, remove the links
     * from the node and reoriginate.  We then allow the node
     * to time itself out.
     *
     * If we weren't the designated router, but are now, we'll
     * need to update the pseudonode and originate it.
     */
    if (nbr->slsp_nbr_dr == nbr) {
	assert(old_np->slsp_node_type == SLSP_LSP_LOCALNET);
	lp = old_np->slsp_node_linklist.slspdb_link_next;
	while (lp && lp != &(old_np->slsp_node_linklist)) {
	    lp_prev = lp->slspdb_link_next;	/* misnomer ... */
	    if (lp->slspdb_link_nbr) {
	        lp->slspdb_link_nbr->slsp_nbr_link = (slsp_db_link *) 0;
	    }
	    SLSP_NODE_DEREFERENCE(lp->slspdb_link_node);
	    SLSP_DB_LINK_FREE(lp);
	    lp = lp_prev;
	}
	old_np->slsp_node_linklist.slspdb_link_prev
	  = old_np->slsp_node_linklist.slspdb_link_next = (slsp_db_link *) 0;
	old_np->slsp_node_n_nexthops = 0;

	/*
	 * Turn this back into a router node, and reoriginate it once more.
	 * We then let it time out.
	 */
	old_np->slsp_node_type = SLSP_LSP_ROUTER;
	if (old_np->slsp_node_cksum) {
	    old_np->slsp_node_seqnum
	      = SLSP_SEQNUM_NEXT(old_np->slsp_node_seqnum);
	    old_np->slsp_node_cksum = 0;
	    old_np->slsp_node_len = 0;
	    old_np->slsp_node_life = time_sec + SLSP_LIFE_MAX;
	}
	if (old_np->slsp_node_life_timeout) {
	    SLSP_LIFE_REMOVE(old_np);
	}
	old_np->slsp_node_life_timeout = time_sec + SLSP_LIFE_MAX;
	SLSP_LIFE_PREPEND((slsp_db_node *) inp, old_np);
	if (((slsp_db_node *)(inp->slsp_lists.slsp_life_next)) == old_np) {
	    SLSP_DB_LIFE_SCHEDULE(inp);
	}
	if (nbr->slsp_nbr_n_adjacent) {
	    assert(inp->slsp_needs_full_seq);
	    if (!(--inp->slsp_needs_full_seq)) {
		slsp_db_full_seq_remove(inp);
	    }
	    nbr->slsp_nbr_n_adjacent = 0;
	}
	/*
	 * Can't happen, we should have stopped sending above
	 */
	assert(!(nbr->slsp_nbr_fsq));
    } else {
	old_np = (slsp_db_node *) 0;
    }

    lcl_np = (slsp_db_node *) 0;
    if (nbr_dr == nbr) {
	/*
	 * We just located/created a new node for this
	 * guy above.  Remove any attached links, then convert
	 * into a local net node and list links to our current
	 * neighbours.  Then (re)originate the LSP.
	 */
	need_spf = 1;
	lp_prev = np->slsp_node_linklist.slspdb_link_next;
	while (lp_prev && lp_prev != &(np->slsp_node_linklist)) {
	    lp = lp_prev->slspdb_link_next;
	    SLSP_NODE_DEREFERENCE(lp_prev->slspdb_link_node);
	    SLSP_DB_LINK_FREE(lp_prev);
	    lp_prev = lp;
	}
	np->slsp_node_linklist.slspdb_link_prev
	  = np->slsp_node_linklist.slspdb_link_next = &(np->slsp_node_linklist);

	if (np->slsp_node_type == SLSP_LSP_PLACEHOLDER
	  || np->slsp_node_type == SLSP_LSP_TIMEDOUT) {
	    np->slsp_node_seqnum = SLSP_SEQNUM_MIN;
	    SLSP_FULL_PREPEND(inp, np);
	    inp->slsp_full_seq_entries++;
	}
	np->slsp_node_type = SLSP_LSP_LOCALNET;

	/*
	 * Add a link for the local node first
	 */
	SLSP_DB_LINK_GET(lp);
	lp->slspdb_link_cost = 0;
	lp->slspdb_link_node = inp->slsp_local_node;
	lp->slspdb_link_nbr = (slsp_neighbour *) 0;
	lp->slspdb_link_newbucket = 1;
	SLSP_NODE_REFERENCE(inp->slsp_local_node);
	SLSP_LINK_APPEND(&(np->slsp_node_linklist), lp);

	/*
	 * Now for each neighbour we find up, add a link to his
	 * node.
	 */
	lcl_np = np;
	assert(nbr->slsp_nbr_n_adjacent == 0);
	for (bcast_nbr = nbr->slsp_nbr_list;
	     bcast_nbr;
	     bcast_nbr = bcast_nbr->slsp_nbr_next) {
	    if (bcast_nbr->slsp_nbr_state != SLSP_NBR_STATE_ADJACENT) {
		if (bcast_nbr->slsp_nbr_state != SLSP_NBR_STATE_HELLO) {
		    break;
		}
		continue;
	    }
	    assert(!(bcast_nbr->slsp_nbr_link));
	    bcast_nbr->slsp_nbr_link = lp = SLSP_DB_LINK_ALLOC();
	    SLSP_NODE_LOCATE(inp, bcast_nbr->slsp_nbr_id, np);
	    if (!np || sock2ip(np->slsp_node_addr)
	      != sock2ip(bcast_nbr->slsp_nbr_id)) {
		np = slsp_db_add_placeholder(inp,
					     bcast_nbr->slsp_nbr_id,
					     np);
	    }
	    SLSP_NODE_REFERENCE(np);
	    lp->slspdb_link_node = np;
	    lp->slspdb_link_nbr = bcast_nbr;
	    SLSP_LINK_PREPEND(&(lcl_np->slsp_node_linklist), lp);
	    nbr->slsp_nbr_n_adjacent++;
	}

	if (nbr->slsp_nbr_n_adjacent) {
	    register slsp_full_seq_q *fsp, *fsp_next;

	    inp->slsp_needs_full_seq++;
	    SLSP_DB_FSQ_GET(fsp);
	    nbr->slsp_nbr_fsq = fsp;
	    fsp->slsp_fq_time = time_sec + MAX(nbr->slsp_nbr_hellointerval,
					       SLSP_FULL_SEQ_MIN_TIME);
	    fsp->slsp_fq_nbr = nbr;
	    fsp_next = inp->slsp_full_queue.slsp_fq_next;
	    while (fsp_next->slsp_fq_time
	      && fsp_next->slsp_fq_time <= fsp->slsp_fq_time) {
		fsp_next = fsp_next->slsp_fq_next;
	    }
	    SLSP_FSQ_PREPEND(fsp_next, fsp);
	    if (inp->slsp_full_queue.slsp_fq_next == fsp) {
		SLSP_DB_XMT_SCHEDULE(inp);
	    }
	}
    } else if (nbr_dr) {
	/*
	 * Here we need to add neighbour references to the
	 * pseudo-node's links.
	 */
	if (np->slsp_node_type == SLSP_LSP_NET) {
	    np->slsp_node_type = SLSP_LSP_NBRNET;
	    for (lp = np->slsp_node_linklist.slspdb_link_next;
		 lp;
		 lp = lp->slspdb_link_next) {
		register u_int32 addr
		  = sock2ip(lp->slspdb_link_node->slsp_node_addr);
		for (bcast_nbr = nbr->slsp_nbr_list;
		     bcast_nbr;
		     bcast_nbr = bcast_nbr->slsp_nbr_next) {
		    if (bcast_nbr->slsp_nbr_state != SLSP_NBR_STATE_ADJACENT) {
			break;
		    }
		    if (sock2ip(bcast_nbr->slsp_nbr_id) == addr) {
			lp->slspdb_link_nbr = bcast_nbr;
			bcast_nbr->slsp_nbr_link = lp;
			break;
		    }
		}
	    }
	}
    }
    nbr->slsp_nbr_dr = nbr_dr;
    slsp_db_reoriginate(inp->slsp_local_node,
			inp->slsp_local_node->slsp_node_seqnum);
    if (old_np) {
	slsp_db_flood(old_np, (slsp_neighbour *) 0);
    }
    if (lcl_np) {
	slsp_db_reoriginate(lcl_np, lcl_np->slsp_node_seqnum);
    }
    if (need_spf) {
	SLSP_SPF_SCHEDULE(inp);
    }
}


/*
 * slsp_db_link_changed - the cost of a neighbour's link changed,
 *			  update the local lsp and arrange to reflood
 *			  it.
 */
void
slsp_db_link_changed __PF1(nbr, slsp_neighbour *)
{
    register slsp_db_link *lp, *lp_next;
    register slsp_instance *inp;
    register slsp_db_node *np;

    assert(nbr->slsp_nbr_link);
    lp = nbr->slsp_nbr_link;
    if (lp->slspdb_link_cost == nbr->slsp_nbr_cost) {
	return;
    }

    /*
     * First update the link in the local node
     */
    inp = nbr->slsp_nbr_instance;
    np = inp->slsp_local_node;
    lp_next = lp->slspdb_link_next;
    SLSP_LINK_REMOVE(lp);
    if (lp->slspdb_link_cost == lp_next->slspdb_link_cost) {
	lp_next->slspdb_link_newbucket = lp->slspdb_link_newbucket;
    }

    lp->slspdb_link_cost = nbr->slsp_nbr_cost;
    for (lp_next = np->slsp_node_linklist.slspdb_link_prev;
	 lp_next != &(np->slsp_node_linklist);
	 lp_next = lp_next->slspdb_link_prev) {
	if (lp_next->slspdb_link_cost <= lp->slspdb_link_cost) {
	    break;
	}
    }
    SLSP_LINK_APPEND(lp_next, lp);
    if (lp_next->slspdb_link_cost != lp->slspdb_link_cost) {
	lp->slspdb_link_newbucket = 1;
    } else {
	lp->slspdb_link_newbucket = 0;
    }

    /*
     * Now arrange for the node to be updated and reflooded, unless
     * it is already in the process of being reflooded.
     */
    if (np->slsp_node_cksum) {
	slsp_db_reoriginate(np, np->slsp_node_seqnum);
    }

    /*
     * And, schedule an SPF to compute the new routes
     */
    SLSP_SPF_SCHEDULE(inp);
}


/*
 * slsp_db_lsp - receive an LSP from a neighbour
 */
void
slsp_db_lsp __PF3(nbr, slsp_neighbour *,
		  pkt, byte *,
		  pktlen, size_t)
{
    register byte *cp = pkt;
    register size_t length;
    byte *cptmp;
    slsp_db_node *np, *fnp;
    slsp_instance *inp;
    slsp_db_link *lp, *lplist, *lplast;
    slsp_db_as *aslist, *asp;
    slsp_neighbour *bnbr;
    int lifetime;
    sockaddr_un addr;
    slsp_seqnum_t seqnum;
    slsp_cksum_t cksum;
    size_t len, plen;
    time_t his_life, my_life;
    int rttype;
    int pcode;
    int last_pcode;
    int last_cost;
    int changes = 0;
    int links = 0;
    int ntype;

    inp = nbr->slsp_nbr_instance;

    /*
     * Sanity check the beginning of the LSP
     */
    if (pktlen < SLSP_LSP_MIN_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp: truncated LSP from %A: length %u (< %u)",
		  nbr->slsp_nbr_addr,
		  pktlen,
		  SLSP_LSP_MIN_LEN));
	goto dumppkt;
    }

    if (SLSP_GET_LEADER_LENGTH(cp) != SLSP_LSP_FIXED_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp: LSP from %A: fixed length screwed (%u != %u)",
		  nbr->slsp_nbr_addr,
		  SLSP_GET_LEADER_LENGTH(cp),
		  SLSP_LSP_FIXED_LEN));
	goto dumppkt;
    }

    if (!SLSP_CHK_LSP(cp)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp: LSP from %A failed fixed fields check",
		  nbr->slsp_nbr_addr));
	goto dumppkt;
    }

    /*
     * Okay.  Fetch the guts from the packet header.
     */
    sockclear_in(&addr);
    SLSP_GET_LSP(length, lifetime, &addr, rttype, seqnum, cksum, cp);

    /*
     * Check to make sure the total length doesn't exceed what we have,
     * and is greater than or equal to the fixed length of the packet.
     * Make sure the lifetime is sensible.
     */
    if (length > pktlen) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp: LSP from %A: LSP length %u greater than packet length %u",
		  nbr->slsp_nbr_addr,
		  length,
		  pktlen));
	goto dumppkt;
    }

    if (length < SLSP_LSP_MIN_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp: LSP from %A: LSP length %u less than minimum length %u (packet %u)",
		  nbr->slsp_nbr_addr,
		  length,
		  SLSP_LSP_MIN_LEN,
		  pktlen));
	goto dumppkt;
    }

    if (lifetime > SLSP_LIFE_MAX) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp: LSP from %A has lifetime %u greater than protocol maximum %u",
		  nbr->slsp_nbr_addr,
		  lifetime,
		  SLSP_LIFE_MAX));
	goto dumppkt;
    }

    /*
     * Check the checksum using the length found in the packet.  Zero the
     * lifetime to do this right.
     */
    SLSP_PUT_LSP_LIFETIME(0, pkt);
    if (!SLSP_CHK_LSP_CKSUM(length, pkt)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp: LSP from %A checksum failed",
		  nbr->slsp_nbr_addr));
	goto dumppkt;
    }

    /*
     * Finally, check the payload for fixed field sensibility.  The
     * AS payloads should come before the link payloads.
     */
    len = length - SLSP_LSP_FIXED_LEN;
    last_pcode = 0;
    last_cost = 256;
    cptmp = cp;
    while (len) {
	if (len == 1) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_ALL,
		     LOG_WARNING,
		     ("slsp_db_lsp: LSP from %A ID %A one byte remaining in payload",
		      nbr->slsp_nbr_addr,
		      &addr));
	    goto dumppkt;
	}
	pcode = (int) *cp++;
	plen = (size_t) *cp++;
	len -= 2;

	if (plen > len) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_ALL,
		     LOG_WARNING,
		     ("slsp_db_lsp: LSP from %A ID %A payload length %u but %u byte%s left in packet",
		      nbr->slsp_nbr_addr,
		      &addr,
		      plen,
		      len,
		      ((len == 1) ? "" : "s")));
		goto dumppkt;
	}
	len -= plen;
	if (plen == 0) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_ALL,
		     LOG_WARNING,
		     ("slsp_db_lsp: LSP from %A ID %A payload type %u zero length",
		      nbr->slsp_nbr_addr,
		      &addr,
		      pcode));
	    goto dumppkt;
	}
	if (pcode == SLSP_LSP_CODE_AS) {
	    if (last_pcode == SLSP_LSP_CODE_LINKS) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_ALL,
			 LOG_WARNING,
			 ("slsp_db_lsp: LSP from %A ID %A has AS links after router links!",
			  nbr->slsp_nbr_addr,
			  &addr));
		goto dumppkt;
	    }
	    last_pcode = SLSP_LSP_CODE_AS;
	    if ((plen % SLSP_LSP_AS_LEN)) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_ALL,
			 LOG_WARNING,
			 ("slsp_db_lsp: LSP from %A ID %A AS links payload length %u should be multiple of %u",
			  nbr->slsp_nbr_addr,
			  &addr,
			  plen,
			  SLSP_LSP_AS_LEN));
		goto dumppkt;
	    }
	    do {
		if (!SLSP_CHK_LSP_AS(cp)) {
		    trace_tf(nbr->slsp_nbr_trace_options,
			     TR_ALL,
			     LOG_WARNING,
			     ("slsp_db_lsp: LSP from %A ID %A AS fixed field check failed",
			      nbr->slsp_nbr_addr,
			      &addr));
		    goto dumppkt;
		}
		cp += SLSP_LSP_AS_LEN;
		plen -= SLSP_LSP_AS_LEN;
	    } while (plen);
	} else if (pcode == SLSP_LSP_CODE_LINKS) {
	    if (plen < (SLSP_LSP_LINK_MIN_LEN + SLSP_LSP_LINK_ID_LEN)) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_ALL,
			 LOG_WARNING,
			 ("slsp_db_lsp: LSP from %A ID %A link payload length %u too small (< %u)",
			  nbr->slsp_nbr_addr,
			  &addr,
			  plen,
			  (SLSP_LSP_LINK_MIN_LEN + SLSP_LSP_LINK_ID_LEN)));
		goto dumppkt;
	    }
	    plen -= SLSP_LSP_LINK_MIN_LEN;
	    if ((plen % SLSP_LSP_LINK_ID_LEN)) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_ALL,
			 LOG_WARNING,
			 ("slsp_db_lsp: LSP from %A ID %A link payload length %u improper",
			  nbr->slsp_nbr_addr,
			  &addr,
			  (plen + SLSP_LSP_MIN_LEN)));
		goto dumppkt;
	    }
	    if (*cp++ != 0) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_ALL,
			 LOG_WARNING,
			 ("slsp_db_lsp: LSP from %A ID %A link leader byte value %u should be zero",
			  nbr->slsp_nbr_addr,
			  &addr,
			  *(--cp)));
		goto dumppkt;
	    }
	    if (last_pcode != SLSP_LSP_CODE_LINKS) {
		last_cost = (int) *cp;
	    } else if ((last_cost == 0 || *cp == 0)
	      && (int)(*cp) != last_cost) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_ALL,
			 LOG_WARNING,
			 ("slsp_db_lsp: LSP from %A ID %A has both zero cost and non-zero cost links",
			  nbr->slsp_nbr_addr,
			  &addr));
		goto dumppkt;
	    }
	    cp++;
	    last_pcode = SLSP_LSP_CODE_LINKS;

	    do {
		if (!SLSP_CHK_LINK_ID(cp)) {
		    trace_tf(nbr->slsp_nbr_trace_options,
			     TR_ALL,
			     LOG_WARNING,
			     ("slsp_db_lsp: LSP from %A ID %A router link entry failed fixed field checks",
			      nbr->slsp_nbr_addr,
			      &addr));
		    goto dumppkt;
		}
		cp += SLSP_LSP_LINK_ID_LEN;
		plen -= SLSP_LSP_LINK_ID_LEN;
	    } while (plen);
	} else {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_ALL,
		     LOG_WARNING,
		     ("slsp_db_lsp: LSP from %A ID %A unknown payload type %u",
		      nbr->slsp_nbr_addr,
		      &addr,
		      pcode));
	    goto dumppkt;
	}
    }
    cp = cptmp;

    /*
     * Okay, this packet is what the guy sent, and seems to be one
     * we can rebuild.  See if we have an existing node for this guy.
     * If so, see if his is older than ours, if so we can send him ours
     * and forget about it.
     */
    fnp = (slsp_db_node *) 0;
    SLSP_NODE_LOCATE(inp, &addr, np);
    if (sock2ip(np->slsp_node_addr) != sock2ip(&addr)) {
	fnp = np;
	np = (slsp_db_node *) 0;
    }

    if (lifetime == 0) {
	if (np && np->slsp_node_type != SLSP_LSP_PLACEHOLDER) {
	    /*
	     * If his sequence number is older than ours, or our
	     * LSP is relatively new, send him ours instead.
	     */
	    if ((np->slsp_node_type != SLSP_LSP_TIMEDOUT
		&& np->slsp_node_life > (time_sec + SLSP_LIFE_MAXDIFF))
	      || SLSP_SEQNUM_OLDER(seqnum, np->slsp_node_seqnum)) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_lsp: expired LSP from %A for node %A his sequence %08x ours %08x sending him ours%s",
			  nbr->slsp_nbr_addr,
			  np->slsp_node_addr,
			  seqnum,
		 	  np->slsp_node_seqnum,
			  ((np->slsp_node_type == SLSP_LSP_TIMEDOUT) ?
			    "" : " (unexpired)")));
		slsp_db_sendto(nbr, np);
		return;
	    }

	    /*
	     * If this is a local LSP, reoriginate it
	     */
	    if (SLSP_IS_LOCAL_LSP(np)) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_lsp: expired LSP from %A local ID %A, reoriginating",
			  nbr->slsp_nbr_addr,
			  np->slsp_node_addr,
			  np->slsp_node_seqnum,
			  seqnum));
		slsp_db_reoriginate(np, seqnum);
		return;
	    }

	    /*
	     * If his sequence number is newer, or if it is the
	     * same but we are unexpired, (re)expire it.  Otherwise
	     * treat this as an ack.
	     */
	    if (seqnum != np->slsp_node_seqnum
	      || np->slsp_node_type != SLSP_LSP_TIMEDOUT) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_lsp: expired LSP from %A for node %A %sexpiring ours too",
			  nbr->slsp_nbr_addr,
			  np->slsp_node_addr,
			  ((np->slsp_node_type == SLSP_LSP_TIMEDOUT)
			   ? "re" : "")));
		slsp_db_expire(np, seqnum, nbr);
	    } else {
		/*
		 * Treat this as an ack for the zero age LSP.  This
		 * may cause us to remove it from the database or
		 * turn it into a placeholder.
		 */
		SLSP_BIT_CLR(&(np->slsp_node_xmt_bits), nbr);
		if (np->slsp_node_xmt_nbits == 0) {
		    trace_tf(nbr->slsp_nbr_trace_options,
			     TR_NORMAL,
			     0,
			     ("slsp_db_lsp: expired LSP from %A for node %A completely acks our LSP",
			      nbr->slsp_nbr_addr,
			      np->slsp_node_addr));
		    SLSP_XMT_REMOVE(np);
		    if (np->slsp_node_type == SLSP_LSP_TIMEDOUT) {
			SLSP_LIFE_REMOVE(np);
			if (np->slsp_node_refcount) {
			    np->slsp_node_type = SLSP_LSP_PLACEHOLDER;
			    np->slsp_node_cksum = 0;
			    np->slsp_node_life = (time_t) 0;
			    np->slsp_node_life_timeout = (time_t) 0;
			} else {
			    slsp_node_remove(np);
			    if (np->slsp_node_addr) {
				sockfree(np->slsp_node_addr);
			    }
			    SLSP_DB_NODE_FREE(np);
			}
		    }
		} else {
		    trace_tf(nbr->slsp_nbr_trace_options,
			     TR_NORMAL,
			     0,
			     ("slsp_db_lsp: expired LSP from %A for node %A acks ours, %u remaining",
			      nbr->slsp_nbr_addr,
			      np->slsp_node_addr,
			      np->slsp_node_xmt_nbits));
		}
	    }
	} else {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_db_lsp: expired LSP from %A for node %A unknown to us, just acking/ignoring",
		      nbr->slsp_nbr_addr,
		      &addr));
	}

	/*
	 * Send an ack to shut him up
	 */
	if (SLSP_NBR_PTP_TYPE(nbr)) {
	    SLSP_DB_ADD_ACK(nbr,
			    SLSP_SEQ_ENT_TYPE_ROUTER,
			    &addr,
			    seqnum,
			    lifetime,
			    cksum);
	}
	return;
    }

    his_life = (time_t) lifetime + time_sec;
    if (np->slsp_node_type == SLSP_LSP_TIMEDOUT) {
	my_life = time_sec;
    } else {
	my_life = np->slsp_node_life;
    }
    if (np && np->slsp_node_type != SLSP_LSP_PLACEHOLDER
      && his_life < (my_life + SLSP_LIFE_MAXDIFF)) {
	if (my_life > (his_life + SLSP_LIFE_MAXDIFF)
	  || SLSP_SEQNUM_OLDER(seqnum, np->slsp_node_seqnum)) {
	    /*
	     * His is older than ours, send him
	     * our node instead and forget about it.
	     */
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_db_lsp: LSP from %A for node %A his is older sending him ours",
		      nbr->slsp_nbr_addr,
		      np->slsp_node_addr));
	    slsp_db_sendto(nbr, np);
	    return;
	}
	if (seqnum == np->slsp_node_seqnum) {
	    /*
	     * Same sequence number, and he has some life left.
	     * Check the checksums.  If they match the only thing we'll
	     * do is use his lifetime if it is smaller than ours.
	     */
	    if (np->slsp_node_type != SLSP_LSP_TIMEDOUT
	      && cksum == np->slsp_node_cksum) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_lsp: LSP from %A for node %A same as ours, his lifetime %s",
			  nbr->slsp_nbr_addr,
			  np->slsp_node_addr,
			  ((his_life < np->slsp_node_life)
			    ? "shorter" : "same or longer")));
		if (his_life < np->slsp_node_life && !SLSP_IS_LOCAL_LSP(np)) {
		    np->slsp_node_life = his_life;
		    np->slsp_node_life_timeout = his_life;
		    fnp = SLSP_LIFE_PREV(inp, np);
		    if (fnp && fnp->slsp_node_life_timeout > his_life) {
			SLSP_LIFE_REMOVE(np);
			while ((fnp = SLSP_LIFE_PREV(inp, fnp))) {
			    if (fnp->slsp_node_life_timeout <= his_life) {
				break;
			    }
			}
			if (fnp) {
			    SLSP_LIFE_APPEND(fnp, np);
			} else {
			    SLSP_LIFE_APPEND(inp, np);
			}
		    }
		    if (!fnp) {
			SLSP_DB_LIFE_SCHEDULE(inp);
		    }
		}

		/*
		 * If he is a point-to-point neighbour, we'll need to
		 * ack to shut him up.  Do it now.
		 */
		if (SLSP_NBR_PTP_TYPE(nbr)) {
		    SLSP_DB_ADD_ACK(nbr,
				    SLSP_SEQ_ENT_TYPE_ROUTER,
				    &addr,
				    seqnum,
				    lifetime,
				    cksum);
		}

		if (np->slsp_node_xmt_nbits) {
		    SLSP_BIT_CLR(&(np->slsp_node_xmt_bits), nbr);
		    if (np->slsp_node_xmt_nbits == 0) {
			SLSP_XMT_REMOVE(np);
		    }
		}
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_lsp: LSP from %A ID %A one we know already",
			  nbr->slsp_nbr_addr,
			  np->slsp_node_addr));
		return;
	    }

	    /*
	     * Here we have the same sequence numbers but a mismatched
	     * checksum.  Expire this node, unless it is local or
	     * already expired.
	     */
	    if (np->slsp_node_type == SLSP_LSP_TIMEDOUT) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_lsp: LSP from %A for node %A ours expired, sending him ours",
			  nbr->slsp_nbr_addr,
			  np->slsp_node_addr));
		slsp_db_sendto(nbr, np);
		return;
	    }
	    if (!SLSP_IS_LOCAL_LSP(np)) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_lsp: LSP from %A for node %A same sequence number but mismatched checksum: expired",
			  nbr->slsp_nbr_addr,
			  np->slsp_node_addr));
		slsp_db_expire(np, seqnum, (slsp_neighbour *) 0);
		return;
	    }
	}

    }

    /*
     * Okay, here we have a situation where his LSP is better than
     * the one we know already.  If this is a locally-originated
     * LSP then re-originate it with a better sequence number.
     */
    if (SLSP_IS_LOCAL_LSP(np)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_db_lsp: LSP from %A local ID %A our sequence %08x his %08x, reoriginating",
		  nbr->slsp_nbr_addr,
		  np->slsp_node_addr,
		  np->slsp_node_seqnum,
		  seqnum));
	slsp_db_reoriginate(np, seqnum);
	return;
    }

    /*
     * Okay, we need to dig the useful data out of this packet.  By now
     * we know this is not a local LSP.  Just record the AS list as
     * it comes out of the packet, but check through the links list so
     * we can tell if it changed.
     */
    if (np) {
	aslist = np->slsp_node_aslist.slspdb_as_next;
	np->slsp_node_aslist.slspdb_as_next = (slsp_db_as *) 0;
	np->slsp_node_aslist.slspdb_as_count = 0;
	lplist = np->slsp_node_linklist.slspdb_link_next;
	lplast = np->slsp_node_linklist.slspdb_link_next = (slsp_db_link *) 0;
    } else {
	aslist = (slsp_db_as *) 0;
	lplast = lplist = (slsp_db_link *) 0;
	np = slsp_db_add_placeholder(inp, &addr, fnp);
    }
    np->slsp_node_seqnum = seqnum;
    np->slsp_node_cksum = cksum;
    np->slsp_node_len = length;
    np->slsp_node_life = time_sec + lifetime;
    if (rttype == SLSP_LSP_RTTYPE_ALT) {
	BIT_SET(np->slsp_node_flags, SLSP_NODEF_RTTYPE_ALT);
    } else {
	BIT_RESET(np->slsp_node_flags, SLSP_NODEF_RTTYPE_ALT);
    }
    ntype = SLSP_LSP_ROUTER;
    bnbr = np->slsp_node_nbr;

    len = length - SLSP_LSP_FIXED_LEN;
    asp = (slsp_db_as *) 0;
    while (len) {
	pcode = (int)(*cp++);
	plen = (size_t)(*cp++);
	last_pcode = 1;
	len -= (2 + plen);
	if (pcode == SLSP_LSP_CODE_AS) {
	    do {
		if (!aslist) {
		    SLSP_DB_AS_GET(aslist);
		}
		if (asp) {
		    asp->slspdb_as_next = aslist;
		} else {
		    np->slsp_node_aslist.slspdb_as_next = aslist;
		}
		asp = aslist;
		aslist = asp->slspdb_as_next;
		asp->slspdb_as_next = (slsp_db_as *) 0;
		asp->slspdb_as_newbucket = last_pcode;
		last_pcode = 0;
		SLSP_GET_LSP_AS(asp->slspdb_as, cp);
		np->slsp_node_aslist.slspdb_as_count++;
	    } while ((plen -= SLSP_LSP_AS_LEN));
	} else {
	    register byte cost;

	    SLSP_GET_LINK_COST(cost, cp);
	    if (cost == 0) {
		ntype = SLSP_LSP_NET;
	    }
	    plen -= 2;
	    do {
		SLSP_GET_LINK_ID(&addr, cp);

		if (lplist) {
		    register slsp_db_link *lp_prev = (slsp_db_link *) 0;

		    lp = lplist;
		    do {
			if (lp->slspdb_link_cost == cost
			  && sock2ip(lp->slspdb_link_node->slsp_node_addr)
			  == sock2ip(&addr)) {
			    break;
			}
			lp_prev = lp;
			lp = lp->slspdb_link_next;
		    } while (lp);

		    if (lp) {
			if (!lp_prev) {
			    lplist = lp->slspdb_link_next;
			} else {
			    lp_prev->slspdb_link_next = lp->slspdb_link_next;
			}
			lp->slspdb_link_next = (slsp_db_link *) 0;
		    }
		} else {
		    lp = (slsp_db_link *) 0;
		}

		if (!lp) {
		    register slsp_db_node *link_np;

		    SLSP_DB_LINK_GET(lp);
		    lp->slspdb_link_cost = cost;
		    SLSP_NODE_LOCATE(inp, &addr, link_np);
		    if (!link_np
		      || sock2ip(link_np->slsp_node_addr) != sock2ip(&addr)) {
			link_np = slsp_db_add_placeholder(inp, &addr, link_np);
		    } else if (np->slsp_node_refcount) {
			changes++;	/* assume changed */
		    }
		    SLSP_NODE_REFERENCE(link_np);
		    lp->slspdb_link_node = link_np;
		    if (bnbr) {
			register slsp_neighbour *cnbr = bnbr->slsp_nbr_list;

			while (cnbr) {
			    if (sock2ip(&addr) == sock2ip(cnbr->slsp_nbr_id)) {
				if (cnbr->slsp_nbr_state
				  == SLSP_NBR_STATE_ADJACENT) {
				    if (cnbr->slsp_nbr_link) {
					cnbr->slsp_nbr_link->slspdb_link_nbr
					  = (slsp_neighbour *) 0;
				    }
				    lp->slspdb_link_nbr = cnbr;
				    cnbr->slsp_nbr_link = lp;
				}
				break;
			    }
			    cnbr = cnbr->slsp_nbr_next;
			}
		    }
		}

		lp->slspdb_link_newbucket = last_pcode;
		last_pcode = 0;
		if (lplast) {
		    lplast->slspdb_link_next = lp;
		} else {
		    np->slsp_node_linklist.slspdb_link_next = lp;
		}
		lplast = lp;
		links++;
	    } while ((plen -= SLSP_LSP_LINK_ID_LEN));
	}
    }

    /*
     * Any links remaining on the list were links he didn't include.
     * Dereference the guys they point to and free the structures.
     * Note if this may have caused changes to our routing.
     */
    while (lplist) {
	lp = lplist;
	lplist = lp->slspdb_link_next;
	if (SLSP_IS_ACTIVE_LSP(lp->slspdb_link_node)) {
	    changes++;
	}
	if (lp->slspdb_link_nbr) {
	    lp->slspdb_link_nbr->slsp_nbr_link = (slsp_db_link *) 0;
	}
	SLSP_NODE_DEREFERENCE(lp->slspdb_link_node);
	SLSP_DB_LINK_FREE(lp);
    }

    /*
     * Record the type of the node.  If it is a network
     * node we'll need to determine whether it is one to
     * which we are locally attached or not.
     */
    if (ntype == SLSP_LSP_NET) {
	if (BIT_TEST(np->slsp_node_flags, SLSP_NODEF_LOCAL_LINK)) {
	    ntype = SLSP_LSP_NBRNET;
	}
    }

    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL,
	     0,
	     ("slsp_db_lsp: LSP from %A ID %A type %s received: ases %u links %u",
	      nbr->slsp_nbr_addr,
	      np->slsp_node_addr,
	      trace_state(slsp_node_types, ntype),
	      np->slsp_node_aslist.slspdb_as_count,
	      links));

    /*
     * Okay, got a new LSP.  Flood it to everyone except the guy
     * who sent it.  Send him an ACK if he's a point-to-point man.
     * Make sure an SPF is scheduled if something changed.
     */
    if (np->slsp_node_life_timeout) {
	SLSP_LIFE_REMOVE(np);
    }
    np->slsp_node_life_timeout = np->slsp_node_life;
    fnp = SLSP_LIFE_PREV(inp, inp);
    while (fnp) {
	if (fnp->slsp_node_life_timeout <= np->slsp_node_life_timeout) {
	    break;
	}
	fnp = SLSP_LIFE_PREV(inp, fnp);
    }
    SLSP_LIFE_APPEND((fnp ? fnp : ((slsp_db_node *) inp)), np);
    if (!fnp) {
	SLSP_DB_LIFE_SCHEDULE(inp);
    }
    if (!SLSP_IS_ACTIVE_LSP(np)) {
	SLSP_FULL_PREPEND(inp, np);
	inp->slsp_full_seq_entries++;
    }
    np->slsp_node_type = ntype;
    inp->slsp_full_seq_pkt_time = (time_t) 0;
    slsp_db_flood(np, nbr);
    if (SLSP_NBR_PTP_TYPE(nbr)) {
	SLSP_DB_ADD_ACK(nbr,
			SLSP_SEQ_ENT_TYPE_ROUTER,
			np->slsp_node_addr,
			seqnum,
			lifetime,
			cksum);
    }
    if (changes) {
	SLSP_SPF_SCHEDULE(inp);
    }
    return;

dumppkt:
    if (nbr->slsp_nbr_trace_options) {
	slsp_pktdump(nbr->slsp_nbr_trace_options,
		     "SLSP ERR ",
		     pkt,
		     pktlen);
    }
}


/*
 * slsp_db_seq - receive a neighbour's sequence number packet
 */
void
slsp_db_seq __PF3(nbr, slsp_neighbour *,
		  pkt, byte *,
		  pktlen, size_t)
{
    register byte *cp;    
    register slsp_db_node *np;
    size_t length;
    sockaddr_un addr, naddr;
    slsp_list list;
    slsp_seqnum_t seqnum;
    slsp_cksum_t cksum;
    time_t lifetime;
    slsp_instance *inp;
    int stype, etype;
    int count;
    int ours_newer;
    int acks = 0;
    int requests = 0;
    int sends = 0;
    int ignores = 0;

    /*
     * Sanity check, then fetch the parameters out of the fixed part.
     */
    if (pktlen < SLSP_SEQ_FIXED_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_seq: sequence numbers packet from %A length %u less than minimum of %u",
		  nbr->slsp_nbr_addr,
		  pktlen,
		  SLSP_SEQ_FIXED_LEN));
	goto dumppkt;
    }
    cp = pkt;
    if (!SLSP_CHK_SEQ(cp)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_seq: sequence numbers packet from %A failed fixed field check",
		  nbr->slsp_nbr_addr));
	goto dumppkt;
    }

    sockclear_in(&addr);
    SLSP_GET_SEQ(&addr, stype, length, count, cp);
    if (stype != SLSP_SEQ_FULL && stype != SLSP_SEQ_PARTIAL) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_seq: sequence numbers packet from %A ID %A has unknown type %u",
		  nbr->slsp_nbr_addr,
		  &addr,
		  stype));
	goto dumppkt;
    }
    stype -= SLSP_SEQ_PARTIAL;

    if (length > pktlen) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_seq: sequence numbers packet from %A ID %A indicated length %u exceeds packet length %u",
		  nbr->slsp_nbr_addr,
		  &addr,
		  length,
		  pktlen));
	goto dumppkt;
    }
    if (SLSP_SEQ_LENGTH(count) != length) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_seq: sequence numbers packet from %A ID %A indicated length %u inconsistent with %u entr%s (expect %u)",
		  nbr->slsp_nbr_addr,
		  &addr,
		  length,
		  count,
		  ((count == 1) ? "y" : "ies"),
		  SLSP_SEQ_LENGTH(count)));
	goto dumppkt;
    }
    /* XXX do something with ID? */

    /*
     * Okay, we seem to have a sane packet.  If this is a full sequence
     * numbers packet we need to compare it to our full database, otherwise
     * just worry about the stuff he actually sent.
     *
     * For every entry we look up the node in our database.  If we don't
     * have the node, or if we have an older one than he does, we request
     * he send it in an ACK (i.e. our own sequence numbers packet).  If
     * his is the same as ours, we pull this node from the retransmit
     * queue if it is there.  If his is older than ours we send him ours.
     *
     * Don't bother checking the fixed fields, not sure what this could
     * help anyway.  If the packet is mangled we'll send a bit of extra
     * stuff, but it'll work itself out.
     */
    inp = nbr->slsp_nbr_instance;
    if (stype) {
	list.slsp_full_prev = inp->slsp_lists.slsp_full_prev;
	list.slsp_full_prev->slsp_full_next = &list;
	list.slsp_full_next = inp->slsp_lists.slsp_full_next;
	list.slsp_full_next->slsp_full_prev = &list;
	SLSP_FULL_INIT(&(inp->slsp_lists));
    }
    sockclear_in(&naddr);

    while (count--) {
	SLSP_GET_SEQ_ENT(etype, &naddr, seqnum, lifetime, cksum, cp);
	if (etype) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_db_seq: sequence numbers packet from %A ID %A entry %A type %s ignored",
		      nbr->slsp_nbr_addr,
		      &addr,
		      &naddr,
		      ((etype == SLSP_SEQ_ENT_TYPE_EXT)
			? "useless ext" : "unknown")));
	    continue;
	}

	SLSP_NODE_LOCATE(inp, &naddr, np);
	if (!np
	  || sock2ip(np->slsp_node_addr) != sock2ip(&naddr)
	  || np->slsp_node_type == SLSP_LSP_PLACEHOLDER) {
	    /*
	     * One we don't know, ask him for it if it appears that
	     * he knows it.
	     */
	    if (seqnum == SLSP_SEQNUM_MIN || lifetime == 0 || cksum == 0) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_seq: sequence numbers from %A ID %A not know to us, ignoring it",
			  &addr,
			  &naddr));
		ignores++;
	    } else {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_seq: sequence numbers from %A ID %A not known to us, requesting it",
			  &addr,
		 	  &naddr));
		SLSP_DB_ADD_ACK(nbr,
				SLSP_SEQ_ENT_TYPE_ROUTER,
				&naddr,
				SLSP_SEQNUM_MIN,
				0,
				0);
		requests++;
	    }
	    continue;
	}

	if (stype && np->slsp_node_type != SLSP_LSP_TIMEDOUT) {
	    SLSP_FULL_REMOVE(np);
	    SLSP_FULL_PREPEND(inp, np);
	}
	ours_newer = 0;
	if (np->slsp_node_type == SLSP_LSP_TIMEDOUT) {
	    if (lifetime > SLSP_LIFE_MAXDIFF) {
		ours_newer = (-1);
	    }
	} else {
	    if ((np->slsp_node_life + SLSP_LIFE_MAXDIFF) <
	      (lifetime + time_sec)) {
		ours_newer = (-1);
	    } else if (np->slsp_node_life
	      > (lifetime + time_sec + SLSP_LIFE_MAXDIFF)) {
		ours_newer = 1;
	    }
	}
	if (!ours_newer) {
	    if (SLSP_SEQNUM_OLDER(np->slsp_node_seqnum, seqnum)) {
		ours_newer = (-1);
	    } else if (np->slsp_node_seqnum != seqnum) {
		ours_newer = 1;
	    }
	}

	if (ours_newer < 0) {
	    /*
	     * Our's is older, ask him for his unless this is
	     * a local packet in which case we reoriginate.
	     */
	    if (SLSP_IS_LOCAL_LSP(np)) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_seq: sequence numbers from %A ID %A is local and better, jumping his sequence",
			  &addr,
			  &naddr));
		sends++;
		slsp_db_reoriginate(np, seqnum);
	    } else {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_seq: sequence numbers from %A ID %A better than ours, requesting it",
			  &addr,
			  &naddr));
		requests++;
		SLSP_DB_ADD_ACK(nbr,
				SLSP_SEQ_ENT_TYPE_ROUTER,
				&naddr,
				SLSP_SEQNUM_MIN,
				0,
				0);
	    }
	    continue;
	}

	if (!ours_newer) {
	    /*
	     * Sequence number match.  If his lifetime is zero and
	     * so is ours, or if the cksums match, remove his transmit
	     * bit from the LSP if set.  We're in agreement.
	     */
	    if ((lifetime == 0
	      && (np->slsp_node_type == SLSP_LSP_TIMEDOUT
		|| np->slsp_node_life <= (time_sec + 10)))
	      || cksum == np->slsp_node_cksum) {
		acks++;
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_db_seq: sequence numbers from %A ID %A matches ours",
			  &addr,
			  &naddr));
		if (np->slsp_node_xmt_nbits) {
		    SLSP_BIT_CLR(&(np->slsp_node_xmt_bits), nbr);
		    if (np->slsp_node_xmt_nbits == 0) {
			SLSP_XMT_REMOVE(np);
			if (np->slsp_node_type == SLSP_LSP_TIMEDOUT) {
			    SLSP_LIFE_REMOVE(np);
			    if (np->slsp_node_refcount) {
				np->slsp_node_type = SLSP_LSP_PLACEHOLDER;
				np->slsp_node_cksum = 0;
			 	np->slsp_node_life = (time_t) 0;
				np->slsp_node_life_timeout = (time_t) 0;
			    } else {
				slsp_node_remove(np);
				if (np->slsp_node_addr) {
				    sockfree(np->slsp_node_addr);
				}
				SLSP_DB_NODE_FREE(np);
			    }
			}
		    }
		}
		continue;
	    }
	}

	/*
	 * About the only thing left to us is to send him ours.  Do so now.
	 */
	sends++;
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_db_seq: sequence numbers from %A ID %A worse/mismatched with ours, sending ours",
		  &addr,
		  &naddr));
	slsp_db_sendto(nbr, np);
    }

    /*
     * Done with that.  If this was a full sequence numbers packet it
     * remains to walk the remainder of the full list processing the
     * guys who weren't included in the packet.  Send each of these
     * to him.  If there were no requests in there and we're sending
     * a full sequence numbers packet, stop it.  We're synchronized.
     */
    if (stype) {
	register slsp_db_node *np_next;

	np_next = SLSP_FULL_NEXT(&list, &list);
	while ((np = np_next)) {
	    np_next = SLSP_FULL_NEXT(&list, np);
	    sends++;
	    slsp_db_sendto(nbr, np);
	    SLSP_FULL_REMOVE(np);
	    SLSP_FULL_PREPEND(inp, np);
	}

	if (!requests && nbr->slsp_nbr_fsq) {
	    SLSP_FSQ_REMOVE(nbr->slsp_nbr_fsq);
	    SLSP_DB_FSQ_FREE(nbr->slsp_nbr_fsq);
	    nbr->slsp_nbr_fsq = (slsp_full_seq_q *) 0;
	}
    }

    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL,
	     0,
	     ("slsp_db_seq: sequence numbers packet from %A ID %A acks %d sends %d requests %d ignores %d",
	      &addr,
	      &naddr,
	      acks,
	      sends,
	      requests,
	      ignores));
    return;

dumppkt:
    if (nbr->slsp_nbr_trace_options) {
	slsp_pktdump(nbr->slsp_nbr_trace_options,
		     "SLSP ERR ",
		     pkt,
		     pktlen);
    }
}


/*
 * slsp_db_lsp_useless - receive and ACK the useless ext LSPs that
 *			 rcp_routed sends for some unknown reason.
 */
void
slsp_db_lsp_useless __PF3(nbr, slsp_neighbour *,
			  pkt, byte *,
			  pktlen, size_t)
{
    register byte *cp = pkt;
    register size_t length;
    int lifetime;
    sockaddr_un addr;
    slsp_seqnum_t seqnum;
    slsp_cksum_t cksum;
    int rttype;

    /*
     * Sanity check the beginning of the LSP
     */
    if (pktlen < SLSP_EXT_FIXED_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp_useless: truncated ext LSP from %A: length %u (< %u)",
		  nbr->slsp_nbr_addr,
		  pktlen,
		  SLSP_EXT_FIXED_LEN));
	goto dumppkt;
    }

    if (SLSP_GET_LEADER_LENGTH(cp) != SLSP_EXT_FIXED_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp_useless: ext LSP from %A: fixed length screwed (%u != %u)",
		  nbr->slsp_nbr_addr,
		  SLSP_GET_LEADER_LENGTH(cp),
		  SLSP_EXT_FIXED_LEN));
	goto dumppkt;
    }

    if (!SLSP_CHK_EXT(cp)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp_useless: ext LSP from %A failed fixed fields check",
		  nbr->slsp_nbr_addr));
	goto dumppkt;
    }

    /*
     * Okay.  Fetch the guts from the packet header.
     */
    sockclear_in(&addr);
    SLSP_GET_LSP(length, lifetime, &addr, rttype, seqnum, cksum, cp);

    /*
     * Check to make sure the total length doesn't exceed what we have,
     * and is greater than or equal to the fixed length of the packet.
     * Make sure the lifetime is sensible.
     */
    if (length > pktlen) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp_useless: ext LSP from %A ID %A: LSP length %u greater than packet length %u",
		  nbr->slsp_nbr_addr,
		  &addr,
		  length,
		  pktlen));
	goto dumppkt;
    }

    if (length < SLSP_EXT_FIXED_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp_useless: ext LSP from %A ID %A: LSP length %u less than minimum length %u (packet %u)",
		  nbr->slsp_nbr_addr,
		  &addr,
		  length,
		  SLSP_EXT_FIXED_LEN,
		  pktlen));
	goto dumppkt;
    }

    if (lifetime > SLSP_LIFE_MAX) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp_useless: ext LSP from %A has lifetime %u greater than protocol maximum %u",
		  nbr->slsp_nbr_addr,
		  lifetime,
		  SLSP_LIFE_MAX));
	goto dumppkt;
    }

    /*
     * Check the checksum using the length found in the packet.  Zero the
     * lifetime to do this right.
     */
    SLSP_PUT_EXT_LIFETIME(0, pkt);
    if (!SLSP_CHK_EXT_CKSUM(length, pkt)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp_useless: ext LSP from %A ID %A: checksum failed",
		  nbr->slsp_nbr_addr,
		  &addr));
	goto dumppkt;
    }

    /*
     * If the length is other than the fixed length, emit a warning
     * that rcp_routed has done something unexpected.
     */
    if (length != SLSP_EXT_FIXED_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_db_lsp_useless: ext LSP from %A ID %A has %u bytes of payload (don't ask me what)!",
		  nbr->slsp_nbr_addr,
		  &addr,
		  (length - SLSP_EXT_FIXED_LEN)));
    }

    /*
     * Just ack the stupid thing, it doesn't matter anyway.
     */
    SLSP_DB_ADD_ACK(nbr,
		    SLSP_SEQ_ENT_TYPE_EXT,
		    &addr,
		    seqnum,
		    lifetime,
		    cksum);
    return;

dumppkt:
    if (nbr->slsp_nbr_trace_options) {
	slsp_pktdump(nbr->slsp_nbr_trace_options,
		     "SLSP ERR ",
		     pkt,
		     pktlen);
    }
}


/*
 * slsp_db_terminate - shut down this instance's SLSP database
 */
void
slsp_db_terminate __PF1(inp, slsp_instance *)
{
    /* TBD */
}


/*
 * slsp_db_dump - dump the database for this instance
 */
void
slsp_db_dump __PF2(fd, FILE *,
		   inp, slsp_instance *)
{
    /* TBD */
}

/*
 * %(Copyright)
 */
