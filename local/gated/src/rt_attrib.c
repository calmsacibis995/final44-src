/*
 *  $Id: rt_attrib.c,v 1.1 1994/05/09 16:50:16 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_RT_VAR

#include "include.h"

/*
 * Contained in here are routines which deal with the maintenance
 * of structures containing route metrics and, separately, route
 * next hops.  We conserve on memory, and simplify operations such
 * as tracking route changes, by maintaining common structures for
 * each unique set of metrics and (again, separately) next hops.
 *
 * Stuff in here deals with allocating, deleting and sorting attribute
 * structures.
 */

/*
 * Memory allocation for metrics.  We allocate rt_metrics_node and
 * rt_metrics_ext structures.  Macros for allocating and freeing these.
 */
static block_t	rt_metrics_node_block = (block_t) 0;
static block_t	rt_metrics_ext_block = (block_t) 0;

#define	RT_METRICS_NODE_ALLOC()	\
    ((rt_metrics_node *) task_block_alloc(rt_metrics_node_block))
#define	RT_METRICS_EXT_ALLOC() \
    ((rt_metrics_ext *) task_block_alloc(rt_metrics_ext_block))
#define	RT_METRICS_EXT_GET(rtmxp) \
    do { \
	if (!rt_metrics_ext_block) { \
	    RT_METRICS_EXT_INIT(); \
	} \
	(rtmxp) = RT_METRICS_EXT_ALLOC(); \
    } while (0)

#define	RT_METRICS_NODE_FREE(rtmp) \
    task_block_free(rt_metrics_node_block, (void_t)(rtmp))
#define	RT_METRICS_EXT_FREE(rtmxp) \
    task_block_free(rt_metrics_ext_block, (void_t)(rtmxp))

#define	RT_METRICS_NODE_INIT()	(rt_metrics_node_block \
    = task_block_init(sizeof(rt_metrics_node), "rt_metrics_node"))
#define	RT_METRICS_EXT_INIT()	(rt_metrics_ext_block \
    = task_block_init(sizeof(rt_metrics_ext), "rt_metrics_ext"))

/*
 * The `bit' in the metrics node structure is encoded rather strangely.
 * One of the low order eight bits is set, this is the bit to be tested
 * in the target byte.  Bits are ordered from the the low order end so
 * that rtmn_bit increases as we move down the tree.  The next 23 bits
 * are the byte offset into the structure, used to find the byte we are
 * testing in.  The high order bit indicates whether we are testing in
 * the rt_metrics structure (if clear) or the rt_metrics_ext structure
 * (if set).
 */
#define	RTMN_BIT_NONE	0		/* Node with external info only */

#define	RTMN_EXT		0x80000000	/* Bit set when in rt_.._ext */
#define	RTMN_OFFSET_MASK	0x007fffff	/* Offset mask */

#define	RTMN_BIT(bit)		((byte)(bit))	/* Fetch bit from rtmn_bit */
#define	RTMN_OFFSET(bit)	((bit) >> 8)	/* Offset into rt_metrics */
#define	RTMN_EXT_OFFSET(bit)	(((bit) >> 8) & RTMN_OFFSET_MASK)

#define	RTMN_TEST(cp, bit) \
    (BIT_TEST((cp)[RTMN_OFFSET((bit))], RTMN_BIT((bit))) != ((byte) 0))

#define	RTMN_EXT_TEST(cp, bit) \
    (BIT_TEST((cp)[RTMN_EXT_OFFSET((bit))], RTMN_BIT((bit))) != ((byte) 0))

/*
 * Bit array for finding the lowest order bit set in a byte
 */
static const byte rt_metrics_bit[256] = {
    0x00, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x20, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x40, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x20, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x80, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x20, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x40, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x20, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
    0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01
};


/*
 * A "special" metrics node, with no metrics.
 */
rt_metrics_node rt_metrics_none_node = {
    { 0 },			/* rtmn_metrics */
    0,				/* rtmn_refcount */
    &rt_metrics_none_node,	/* rtmn_left */
    &rt_metrics_none_node,	/* rtmn_right */
    RTMN_BIT_NONE		/* rtmn_bit */
} ;

/*
 * Root of the metrics tree and count of items on the tree.  The tree
 * is initialized with the no-metrics node.
 */
static rt_metrics_node *rt_metrics_tree = &rt_metrics_none_node;
static u_int32 rt_metrics_count = 1;
static u_int32 rt_metrics_ext_count = 0;
static u_int32 rt_metrics_finds = 0;
static u_int32 rt_metrics_added = 0;
u_int32 rt_metrics_allocs = 0;
u_int32 rt_metrics_frees = 0;
static u_int32 rt_metrics_freed = 0;

/*
 * Nexthop protocol addresses are kept in per-address-family
 * radix tries.  This is the internal node structure used for
 * tracking them.
 */
typedef struct _rt_nhaddr_node {
    struct _rt_nhaddr_node *rtnhn_left;		/* bit 0 child */
    struct _rt_nhaddr_node *rtnhn_right;	/* bit 1 child */
    struct _rt_nhaddr_node *rtnhn_parent;	/* node parent */
    rt_nexthop_addr *rtnhn_addr;		/* external node */
    u_int16 rtnhn_bit;				/* bit number */
    u_int8 rtnhn_tbyte;				/* byte to test */
    u_int8 rtnhn_tbit;				/* bit to test */
} rt_nhaddr_node;


/*
 * Radix trie stuff.  This assumes NBBY is 8.  If it isn't we're in trouble.
 */
#define	NHBBY	8
#define	NHSHIFT	3
#define	NHTBIT(x)	(0x80 >> ((x) & (NHBBY - 1)))
#define	NHTBYTE(x)	((x) >> NHSHIFT)
#define	NHBIT(len)	((len) << NHSHIFT)

#define	NH_SETBIT(nh, bitlen, maxlen) \
    do { \
	register rt_nhaddr_node *Xnh = (nh); \
	register u_int16 Xlen = (u_int16)(bitlen); \
	Xnh->rtnhn_bit = Xlen; \
	Xnh->rtnhn_tbyte = NHTBYTE(Xlen); \
	if ((maxlen)) { \
	    Xnh->rtnhn_tbit = 0; \
	} else { \
	    Xnh->rtnhn_tbit = NHTBIT(Xlen); \
	} \
    } while (0)

#define	NH_ADDR(sun, offset)	(((byte *)(sun)) + ((size_t)(offset)))

/*
 * Minimum, maximum and initial orders.  We give the first node
 * we put in the tree the initial order, and set orders in subsequent
 * nodes with respect to their neighbours.
 */
#define	NHORDER_MIN	((u_int32) 0)
#define	NHORDER_MAX	((u_int32) 0xffffffff)
#define	NHORDER_INIT	((u_int32) 0x7fffffff)

/*
 * Array to make finding the first bit set in a byte easy.
 */
static const byte rtnha_first_bit_set[256] = {
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * Memory allocation for rt_nhaddr_node's and rt_nexthops_entry's.
 */
static block_t	rt_nhaddr_node_block = (block_t) 0;
static block_t	rt_nexthops_entry_block = (block_t) 0;
static block_t	rt_nexthop_addr_block = (block_t) 0;

#define	RT_NHADDR_NODE_ALLOC() \
    ((rt_nhaddr_node *) task_block_alloc(rt_nhaddr_node_block))
#define RT_NEXTHOPS_ENTRY_ALLOC() \
    ((rt_nexthops_entry *) task_block_alloc(rt_nexthops_entry_block))
#define	RT_NEXTHOP_ADDR_ALLOC() \
    ((rt_nexthop_addr *) task_block_alloc(rt_nexthop_addr_block))

#define	RT_NHADDR_NODE_FREE(rtnhnp) \
    task_block_free(rt_nhaddr_node_block, (void_t)(rtnhnp))
#define	RT_NEXTHOPS_ENTRY_FREE(rtnhp) \
    task_block_free(rt_nexthops_entry_block, (void_t)(rtnhp))
#define	RT_NEXTHOPS_ADDR_FREE(rtnhap) \
    task_block_free(rt_nexthop_addr_block, (void_t)(rtnhap))

#define	RT_NHADDR_NODE_INIT()	(rt_nhaddr_node_block \
    = task_block_init(sizeof(rt_nhaddr_node), "rt_nhaddr_node"))
#define	RT_NEXTHOPS_ENTRY_INIT()	(rt_nexthops_entry_block \
    = task_block_init(sizeof(rt_nexthops_entry), "rt_nexthops_entry"))
#define	RT_NEXTHOP_ADDR_INIT()	(rt_nexthop_addr_block \
    = task_block_init(sizeof(rt_nexthop_addr), "rt_nexthop_addr"))

/*
 * Per-address-family address tree roots.  Just an array of pointers
 * to the first node.  Also some statistics counters.
 */
static rt_nhaddr_node *rt_nhaddr_roots[GF_MAX] = { 0 };
static u_int32 rt_nhaddr_counts[GF_MAX] = { 0 };
static u_int32 rt_nhaddr_inodes[GF_MAX] = { 0 };

/*
 * Other statistics counters for tracking nexthop address performance
 */
static u_int32 rt_nhaddr_finds = 0;
static u_int32 rt_nhaddr_adds = 0;
static u_int32 rt_nhaddr_shifts_up = 0;
static u_int32 rt_nhaddr_shifts_down = 0;
u_int32 rt_nhaddr_allocs = 0;
u_int32 rt_nhaddr_frees = 0;
static u_int32 rt_nhaddr_freed = 0;

/*
 * We hash next hop entries by simply exclusive-or'ing in all relevant
 * data and dividing by the hash size.  Simple(?).
 */
#define	RT_NH_HASH_SIZE		251
static rt_nexthops_entry *rt_nexthops_hash[RT_NH_HASH_SIZE] = { 0 };

#define	RT_NH_HASH(rtnhp, hash) \
    do { \
	register rt_nexthops Xrtnhp = (rt_nexthops *)(rtnhp); \
	register int Xi; \
	register u_long Xhash; \
	Xhash = ((u_long)(Xrtnhp->rtn_type) << 8)|((u_long)Xrtnhp->rtn_n_gw); \
	for (Xi = 0; Xi < Xrtnhp->rtn_n_gw; Xi++) { \
	    Xhash ^= (u_long)(Xrtnhp->rtn_gateway[Xi].rtg_addr); \
	    Xhash ^= (u_long)(Xrtnhp->rtn_gateway[Xi].rtg_ifap); \
	} \
	(hash) = Xhash / RT_NH_HASH_SIZE; \
    } while (0)

/*
 * Stats counters of various sorts
 */
static u_int32 rt_nh_count = 0;
static u_int32 rt_nh_finds = 0;
u_int32 rt_nh_frees = 0;
u_int32 rt_nh_allocs = 0;
static u_int32 rt_nh_freed = 0;
static u_int32 rt_nh_found_fast = 0;
static u_int32 rt_nh_found_slow = 0;
static u_int32 rt_nh_added = 0;
static u_int32 rt_nh_merges = 0;

/*
 * Well-known next hops.  Reject and blackhole next hops at present
 */
rt_nexthops_entry rt_nh_reject_entry = { { RT_NH_REJECT, 0, 0 }, 0 } ;
rt_nexthops_entry rt_nh_blackhole_entry = { { RT_NH_BLACKHOLE, 0, 0 }, 0 };
rt_nexthops_entry rt_nh_none_entry = { { RT_NH_UNUSABLE, 0, 0 }, 0 } ;

/*
 * rt_metrics_find - returns a pointer to an rt_metrics structure
 *		     containing the metrics specified in the calling
 *		     argument.  The returned structure is refcount'd,
 *		     and will need to be freed by the caller after
 *		     use.
 */
rt_metrics *
rt_metrics_find __PF1(rtmp, rt_metrics *)
{
    register byte *cp, *ncp;
    register rt_metrics_node *rtmnp, *rtmnp_new;
    register u_int32 bit_to_test = RTMN_BIT_NONE;
    register u_int32 nbit;
    register u_int32 i;
    register rt_metrics_node *rtmnp_prev;

    rt_metrics_finds++;
    rtmnp = rt_metrics_tree;

    /*
     * Search the patricia tree for a match.  There is
     * complexity in the middle of the loop when we get
     * to offsets in the extended metrics.  If there are
     * no extended metrics, pretend these are all zeros.
     */
    cp = (byte *) rtmp;
    while (bit_to_test < rtmnp->rtmn_bit) {
	bit_to_test = rtmnp->rtmn_bit;
	if (BIT_TEST(bit_to_test, RTMN_EXT)) {
	    cp = (byte *) (rtmp->rtm_metrics_ext);
	    if (cp) {
		if (RTMN_EXT_TEST(cp, bit_to_test)) {
		    rtmnp = rtmnp->rtmn_right;
		} else {
		    rtmnp = rtmnp->rtmn_left;
		}
		while (bit_to_test < rtmnp->rtmn_bit) {
		    bit_to_test = rtmnp->rtmn_bit;
		    if (RTMN_EXT_TEST(cp, bit_to_test)) {
			rtmnp = rtmnp->rtmn_right;
		    } else {
			rtmnp = rtmnp->rtmn_left;
		    }
		}
	    } else {
		rtmnp = rtmnp->rtmn_left;
		while (bit_to_test < rtmnp->rtmn_bit) {
		    bit_to_test = rtmnp->rtmn_bit;
		    rtmnp = rtmnp->rtmn_left;
		}
	    }
	    break;
	}
	if (RTMN_TEST(cp, bit_to_test)) {
	    rtmnp = rtmnp->rtmn_right;
	} else {
	    rtmnp = rtmnp->rtmn_left;
	}
    }

    /*
     * Here we have a pointer to the only potential
     * match in the tree.  Do the comparison, goto no_match
     * at the first sign of trouble.
     */
    if (rtmp->rtm_metrics_ext) {
	if (!(rtmnp->rtmn_metrics.rtm_metrics_ext)
	  || bcmp((caddr_t) rtmp->rtm_metrics_ext,
		  (caddr_t) rtmnp->rtmn_metrics.rtm_metrics_ext,
		  sizeof(rt_metrics_ext))) {
	    goto no_match;
	}
    } else {
	if (rtmnp->rtmn_metrics.rtm_metrics_ext) {
	    goto no_match;
	}
    }

    /*
     * Extended metrics match, compare the regular metrics.  If
     * they are the same increment the reference count and return the
     * node.
     */
    if (!bcmp((caddr_t) rtmp,
	      (caddr_t) &(rtmnp->rtmn_metrics),
	      offsetof(rt_metrics, rtm_metrics_ext))) {
	RT_METRICS_ALLOC(rtmnp);
	return (rt_metrics *) rtmnp;
    }

no_match:
    /*
     * We end up here when there is no match for these metrics in
     * the tree.  Allocate structures for the new set and copy them
     * over.
     *
     * XXX should do sanity checks to ensure that the metrics we
     * were given are in canonical form.
     */
    rt_metrics_added++;
    rt_metrics_count++;
    rtmnp_new = RT_METRICS_NODE_ALLOC();
    rtmnp_new->rtmn_metrics = *rtmp;		/* struct copy */
    if (rtmp->rtm_metrics_ext) {
	register rt_metrics_ext *rtmxp;

	RT_METRICS_EXT_GET(rtmxp);
	*rtmxp = *(rtmp->rtm_metrics_ext);	/* struct copy */
	rtmnp_new->rtmn_metrics.rtm_metrics_ext = rtmxp;
	rt_metrics_ext_count++;
    }
    rtmnp_new->rtmn_refcount = 1;

    /*
     * Find the bit number where the new guy differs from the
     * old guy.  This is more trouble if the difference is in
     * the extended metrics.
     */
    nbit = RTMN_BIT_NONE;
    ncp = (byte *) rtmnp_new;
    cp = (byte *) rtmnp;
    for (i = 0; i < offsetof(rt_metrics, rtm_metrics_ext); i++) {
	if (*cp != *ncp) {
	    nbit = (u_int32) rt_metrics_bit[*cp ^ *ncp] | (i << 8);
	    break;
	}
	cp++, ncp++;
    }

    if (nbit == RTMN_BIT_NONE) {
	ncp = (byte *) (rtmnp_new->rtmn_metrics.rtm_metrics_ext);
	cp = (byte *) (rtmnp->rtmn_metrics.rtm_metrics_ext);
	if (!ncp || !cp) {
	    assert(ncp || cp);
	    if (ncp) {
		cp = ncp;
	    }
	    for (i = 0; i < sizeof(rt_metrics_ext); i++) {
		if (*cp) {
		    nbit = (u_int32) rt_metrics_bit[*cp]
			 | (i << 8) | RTMN_EXT;
		    break;
		}
		cp++;
	    }
	} else {
	    for (i = 0; i < sizeof(rt_metrics_ext); i++) {
		if (*cp != *ncp) {
		    nbit = (u_int32) rt_metrics_bit[*cp ^ *ncp]
			 | (i << 8) | RTMN_EXT;
		    break;
		}
		cp++, ncp++;
	    }
	}
	assert(nbit != RTMN_BIT_NONE);
    }
    rtmnp_new->rtmn_bit = nbit;

    /*
     * Okay, nbit is set to the bit on the node we need to insert.
     * Search down until we find this guy.
     */
    cp = (byte *) rtmnp_new;
    rtmnp_prev = (rt_metrics_node *) 0;
    rtmnp = rt_metrics_tree;
    i = RTMN_BIT_NONE;
    while (i < rtmnp->rtmn_bit) {
        i = rtmnp->rtmn_bit;
	if (nbit <= i) {
	    break;
	}
	rtmnp_prev = rtmnp;
	if (BIT_TEST(i, RTMN_EXT)) {
	    cp = (byte *) (rtmnp_new->rtmn_metrics.rtm_metrics_ext);
	    if (cp) {
		if (RTMN_EXT_TEST(cp, i)) {
		    rtmnp = rtmnp->rtmn_right;
		} else {
		    rtmnp = rtmnp->rtmn_left;
		}
		while (i < rtmnp->rtmn_bit) {
		    i = rtmnp->rtmn_bit;
		    if (nbit <= i) {
			break;
		    }
		    rtmnp_prev = rtmnp;
		    if (RTMN_EXT_TEST(cp, i)) {
			rtmnp = rtmnp->rtmn_right;
		    } else {
			rtmnp = rtmnp->rtmn_left;
		    }
		}
	    } else {
		rtmnp = rtmnp->rtmn_left;
		while (i < rtmnp->rtmn_bit) {
		    i = rtmnp->rtmn_bit;
		    if (nbit <= i) {
			break;
		    }
		    rtmnp_prev = rtmnp;
		    rtmnp = rtmnp->rtmn_left;
		}
	    }
	    break;
	}
	if (RTMN_TEST(cp, i)) {
	    rtmnp = rtmnp->rtmn_right;
	} else {
	    rtmnp = rtmnp->rtmn_left;
	}
    }

    /*
     * Got our guy.  Point the new node at the current node and at the
     * new node.  Find the pointer in the previous node which points
     * at the current node and point it at the new node instead.
     */
    if (cp && RTMN_EXT_TEST(cp, nbit)) {
	rtmnp_new->rtmn_right = rtmnp_new;
	rtmnp_new->rtmn_left = rtmnp;
    } else {
	rtmnp_new->rtmn_right = rtmnp;
	rtmnp_new->rtmn_left = rtmnp_new;
    }

    if (!rtmnp_prev) {
	rt_metrics_tree = rtmnp;
    } else if (rtmnp_prev->rtmn_right == rtmnp) {
	rtmnp_prev->rtmn_right = rtmnp_new;
    } else {
	rtmnp_prev->rtmn_left = rtmnp_new;
    }

    /*
     * Done.  Return the guy we just inserted.
     */
    return (rt_metrics *) rtmnp_new;
}


/*
 * rt_metrics_free - decrement the refcount on a set of metrics, free them
 *		     if they're no longer referenced.
 */
void
rt_metrics_free __PF1(rtmp, rt_metrics *)
{
    register byte *cp;
    register rt_metrics_node *rtmnp_free = (rt_metrics_node *) rtmp;
    register u_int32 tbit;
    register rt_metrics_node *tmp;
    register rt_metrics_node *rtmnp_prev, *rtmnp;
    register rt_metrics_node *rtmnp_int;

    /*
     * Decrement the refcount if it isn't down to 1 already.
     */
    if (rtmnp_free->rtmn_refcount > 1) {
	rt_metrics_frees++;
	rtmnp_free->rtmn_refcount--;
	return;
    }
    assert(rtmnp_free->rtmn_refcount);
    if (rtmnp_free == &rt_metrics_none_node) {
	rt_metrics_frees++;
	rtmnp_free->rtmn_refcount--;
	return;
    }

    /*
     * This node has to come out of the tree.  Find it in there.
     */
    rt_metrics_freed++;
    rt_metrics_count--;
    rtmnp = rt_metrics_tree;
    rtmnp_prev = rtmnp_int = (rt_metrics_node *) 0;
    cp = (byte *) rtmnp_free;

    for (;;) {
	tbit = rtmnp->rtmn_bit;
	if (BIT_TEST(tbit, RTMN_EXT)) {
	    cp = (byte *) (rtmnp_free->rtmn_metrics.rtm_metrics_ext);

	    if (cp) {
		for (;;) {
		    if (RTMN_EXT_TEST(cp, tbit)) {
			tmp = rtmnp->rtmn_right;
		    } else {
			tmp = rtmnp->rtmn_left;
		    }
		    if (tmp == rtmnp_free) {
			if (tmp->rtmn_bit <= tbit) {
			    break;
			}
			rtmnp_int = rtmnp;
		    } else {
			assert(tmp->rtmn_bit > tbit);
		    }
		    rtmnp_prev = rtmnp;
		    rtmnp = tmp;
		    tbit = tmp->rtmn_bit;
		}
	    } else {
		for (;;) {
		    tmp = rtmnp->rtmn_left;
		    if (tmp == rtmnp_free) {
			if (tmp->rtmn_bit > tbit) {
			    break;
			}
			rtmnp_int = rtmnp;
		    } else {
			assert(tmp->rtmn_bit > tbit);
		    }
		    rtmnp_prev = rtmnp;
		    rtmnp = tmp;
		    tbit = tmp->rtmn_bit;
		}
	    }
	    break;
	}
	if (RTMN_TEST(cp, tbit)) {
	    tmp = rtmnp->rtmn_right;
	} else {
	    tmp = rtmnp->rtmn_left;
	}
	if (tmp == rtmnp_free) {
	    if (tmp->rtmn_bit <= tbit) {
		break;
	    }
	    rtmnp_int = rtmnp;
	} else {
	    assert(tmp->rtmn_bit > tbit);
	}
	rtmnp_prev = rtmnp;
	rtmnp = tmp;
    }

    /*
     * Found everything we need to know.  Pull the node out of the tree.
     */
    if (rtmnp->rtmn_right == rtmnp_free) {
	tmp = rtmnp->rtmn_left;
    } else {
	tmp = rtmnp->rtmn_right;
    }

    if (!rtmnp_prev) {
	rt_metrics_tree = tmp;
    } else if (rtmnp_prev->rtmn_right == rtmnp) {
	rtmnp_prev->rtmn_right = tmp;
    } else {
	rtmnp_prev->rtmn_left = tmp;
    }
    if (rtmnp != rtmnp_free) {
	assert(rtmnp_free->rtmn_bit != RTMN_BIT_NONE);
	rtmnp->rtmn_bit = rtmnp_free->rtmn_bit;
	rtmnp->rtmn_left = rtmnp_free->rtmn_left;
	rtmnp->rtmn_right = rtmnp_free->rtmn_right;
	if (!rtmnp_int) {
	    rt_metrics_tree = rtmnp;
	} else if (rtmnp_int->rtmn_right == rtmnp_free) {
	    rtmnp_int->rtmn_right = rtmnp;
	} else {
	    rtmnp_int->rtmn_left = rtmnp;
	}
    }

    /*
     * Here we have detached the node from the tree.  Free it up.
     */
    if (rtmnp_free->rtmn_metrics.rtm_metrics_ext) {
	RT_METRICS_EXT_FREE(rtmnp_free->rtmn_metrics.rtm_metrics_ext);
	rt_metrics_ext_count--;
    }
    RT_METRICS_NODE_FREE(rtmnp_free);
}


/*
 * rt_nhaddr_find - return the rt_nexthop_addr structure for
 *		    the specified next hop address, with the refcount
 *		    incremented.
 */
rt_nexthop_addr *
rt_nhaddr_find __PF1(nhaddr, sockaddr_un *)
{
    register rt_nhaddr_node *nh_prev, *nh_add;
    register u_int32 bitlen;
    rt_nexthop_addr *nha;
    struct sock_info *si;
    int family;

    rt_nhaddr_finds++;
    family = socktype(nhaddr);
    si = &sock_info[family];
    bitlen = NH_BIT(socksize(nhaddr) - si->si_offset);
    nh_prev = rt_nhaddr_roots[family];
    if (!nh_prev) {
	nh_add = RT_NHADDR_NODE_ALLOC();
	rt_nhaddr_inodes[family]++;
	NH_SETBIT(nh_add, bitlen, (socksize(nhaddr) == si->si_size));
	rt_nhaddr_roots[family] = nh_add;
	bitlen = NHORDER_INIT;
    } else {
	register byte *addr = NH_ADDR(nhaddr, si->si_offset);
	register byte *his_addr;
	register rt_nhaddr_node *nh, *nh_new;
	register u_int32 bits2chk, dbit;

	nh = nh_prev;
	while (nh->rtnhn_bit < bitlen) {
	    if (BIT_TEST(addr[nh->rtnhn_tbyte], nh->rtnhn_bit)) {
		if (!(nh->rtnhn_right)) {
		    break;
		}
		nh = nh->rtnhn_right;
	    } else {
		if (!(nh->rtnhn_left)) {
		    break;
		}
		nh = nh->rtnhn_left;
	    }
	}

	bits2chk = bitlen;
	if (!(nh->rtnhn_addr)) {
	    do {
		nh = nh->rtnhn_left;
	    } while (!(nh->rtnhn_addr));
	} else if (nh->rtnhn_bit < bitlen) {
	    bits2chk = nh->rtnhn_bit;
	}

	his_addr = NH_ADDR(nh->rtnhn_addr->rtnha_addr, si->si_offset);
	for (dbit = 0; dbit < bits2chk; dbit += NHBBY) {
	    register u_int32 j = dbit >> NHSHIFT;
	    if (addr[j] != his_addr[j]) { 
		dbit += rtnha_first_bit_set[addr[j] ^ his_addr[j]];
		break;
	    }
	}

	if (dbit == bitlen && nh->rtnhn_bit == (u_int16) bitlen) {
	    /*
	     * Matched it.  Allocate and return this one.
	     */
	    RT_NHADDR_ALLOC(nh->rtnhn_addr);
	    return nh->rtnhn_addr;
	}

	/*
	 * No match here.  Walk back up the tree until we find
	 * where an internal node with a bit number equal to dbit
	 * might sit.
	 */
	nh_prev = nh->rtnhn_parent;
	while (nh_prev && nh_prev->rtnhn_bit >= (u_int16) dbit) {
	    nh = nh_prev;
	    nh_prev = nh->rtnhn_parent;
	}

	/*
	 * If the node nh points to has our bit number we may be able
	 * to just attach our address to this guy.  Check this out.
	 */
	if (dbit == bitlen && nh->rtnhn_bit == (u_int16) bitlen) {
	    nh_add = nh;
	    goto new_node;
	}

	/*
	 * No luck, we'll need at least one new node.
	 */
	rt_nhaddr_inodes[family]++;
	nh_add = RT_NHADDR_NODE_ALLOC();
	NH_SETBIT(nh_add, bitlen, (socksize(nhaddr) == si->si_size));

	/*
	 * There are a couple of possibilities.  The first is that
	 * we attach directly to the guy pointed to by nh.  This
	 * will be the case if his bit number is equal to dbit.
	 */
	if (nh->rtnhn_bit == (u_int16) dbit) {
	    assert(dbit < bitlen);
	    nh_add->rtnhn_parent = nh;
	    if (BIT_TEST(addr[nh->rtnhn_tbyte], nh->rtnhn_tbit)) {
		assert(!(nh->rtnhn_right));
		nh->rtnhn_right = nh_add;
	    } else {
		assert(!(nh->rtnhn_left));
		nh->rtnhn_left = nh_add;
	    }
	    goto new_node;
	}

	/*
	 * The other case where we don't need to add a split is
	 * when we're on the same branch as the guy we found.  In this
	 * case we insert nh_add into the tree between nh_prev and nh.
	 * Otherwise we allocate and insert a split bit.
	 */
	if (dbit == bitlen) {
	    if (BIT_TEST(his_addr[nh_add->rtnhn_tbyte], nh_add->rtnhn_tbit)) {
		nh_add->rtnhn_right = nh;
	    } else {
		nh_add->rtnhn_left = nh;
	    }
	    nh_new = nh_add;
	} else {
	    rt_nhaddr_inodes[family]++;
	    nh_new = RT_NHADDR_NODE_ALLOC();
	    NH_SETBIT(nh_new, dbit, FALSE);
	    nh_add->rtnhn_parent = nh_new;
	    if (BIT_TEST(addr[nh_new->rtnhn_tbyte], nh_new->rtnhn_tbit)) {
		nh_new->rtnhn_right = nh_add;
		nh_new->rtnhn_left = nh;
	    } else {
		nh_new->rtnhn_left = nh_add;
		nh_new->rtnhn_right = nh;
	    }
	}
	nh->rtnhn_parent = nh_new;
	nh_new->rtnhn_parent = nh_prev;

	/*
	 * If nh_prev is NULL this is a new root node.  Otherwise
	 * replace the pointer to nh above with a pointer to nh_new
	 */
	if (!nh_prev) {
	    rt_nhaddr_roots[family] = nh;
	} else if (nh_prev->rtnhn_right == nh) {
	    nh_prev->rtnhn_right = nh_new;
	} else {
	    nh_prev->rtnhn_left = nh_new;
	}

new_node:
	/*
	 * Here we added a new node, pointed to by nh_add.  We need to
	 * set the order on the nhaddr_node.  We do so by finding the
	 * previous and the next nodes in the tree with attached addresses
	 * and setting the new node order half way in between.
	 */
	bits2chk = NHORDER_MIN;		/* previous order */
	dbit = NHORDER_MAX;		/* next order */

	/*
	 * Find the previous node in the tree.  Go up, then to
	 * the left, then as far right as we can.
	 */
	nh = nh_add;
	while ((nh_prev = nh->rtnhn_parent)) {
	    if (nh_prev->rtnhn_left == nh) {
		if (nh_prev->rtnhn_addr) {
		    break;
		}
	    } else if (!(nh_prev->rtnhn_left)) {
		break;
	    } else {
		nh_prev = nh_prev->rtnhn_left;
		for (;;) {
		    if (nh_prev->rtnhn_right) {
			nh_prev = nh_prev->rtnhn_right;
		    } else if (nh_prev->rtnhn_left) {
			nh_prev = nh_prev->rtnhn_left;
		    } else {
			break;
		    }
		}
		break;
	    }
	    nh = nh_prev;
	}
	if (nh_prev) {
	    bits2chk = nh_prev->rtnhn_addr->rtnha_order;
	}

	/*
	 * Now find the next node in the tree.  It will be the
	 * first guy below us as far left as possible, unless we're a
	 * leaf in which case we'll need to walk up until we can go right.
	 */
	if (nh_add->rtnhn_left) {
	    nh_new = nh_add->rtnhn_left;
	} else if (nh_add->rtnhn_right) {
	    nh_new = nh_add->rtnhn_right;
	} else {
	    nh = nh_add;
	    while ((nh_new = nh->rtnhn_parent)) {
		if (nh_new->rtnhn_right && nh_new->rtnhn_right != nh) {
		    nh_new = nh_new->rtnhn_right;
		    break;
		}
		nh = nh_new;
	    }
	}
	if (nh_new) {
	    while (!(nh_new->rtnhn_addr)) {
		nh_new = nh_new->rtnhn_left;
	    }
	    dbit = nh_new->rtnhn_addr->rtnha_order;
	}
	assert(bits2chk < dbit);

	/*
	 * Compute the new order to be half way between the previous
	 * and next orders.  In the (hopefully rare) event that there
	 * is no space between them we'll need to do a bit more work
	 * to space them out.
	 */
	bitlen = dbit - bits2chk;
	if (bitlen > 1) {
	    bitlen >>= 1;
	    bitlen += bits2chk;
	} else if (bits2chk <= NHORDER_MIN) {
	    /*
	     * Shift the order of subsequent addresses
	     */
	    bitlen = dbit;
	    dbit += 1;
	    for (;;) {
		rt_nhaddr_shifts_up++;
		if (nh_new->rtnhn_left) {
		    nh_prev = nh_new->rtnhn_left;
		} else if (nh_new->rtnhn_right) {
		    nh_prev = nh_new->rtnhn_right;
		} else {
		    nh = nh_new;
		    while ((nh_prev = nh->rtnhn_parent)) {
			if (nh_prev->rtnhn_right
			  && nh_prev->rtnhn_right != nh) {
			    nh_prev = nh_prev->rtnhn_right;
			    break;
			}
			nh = nh_prev;
		    }
		    assert(nh_prev);
		}
		while (!(nh_prev->rtnhn_addr)) {
		    nh_prev = nh_prev->rtnhn_left;
		}
		bits2chk = nh_prev->rtnhn_addr->rtnha_order;
		if (bits2chk == dbit) {
		    nh_new->rtnhn_addr->rtnha_order = dbit;
		    dbit += 1;
		    nh_new = nh_prev;
		} else {
		    assert(bits2chk > dbit);
		    nh_new->rtnhn_addr->rtnha_order = (bits2chk-dbit)/2 + dbit;
		    break;
		}
	    }
	} else {
	    /*
	     * Shift the order of previous addresses
	     */
	    bitlen = bits2chk;
	    bits2chk -= 1;
	    for (;;) {
		rt_nhaddr_shifts_down++;
		nh = nh_prev;
		while ((nh_new = nh->rtnhn_parent)) {
		    if (nh_new->rtnhn_left == nh) {
			if (nh_prev->rtnhn_addr) {
			    break;
			}
		    } else if (!(nh_new->rtnhn_left)) {
			break;
		    } else {
			nh_new = nh_new->rtnhn_left;
			for (;;) {
			    if (nh_new->rtnhn_right) {
				nh_new = nh_new->rtnhn_right;
			    } else if (nh_new->rtnhn_left) {
				nh_new = nh_new->rtnhn_left;
			    } else {
				break;
			    }
			}
			break;
		    }
		    nh = nh_new;
		}
		assert(nh_new);
		dbit = nh_new->rtnhn_addr->rtnha_order;
		if (dbit == bits2chk) {
		    nh_prev->rtnhn_addr->rtnha_order = bits2chk;
		    bits2chk -= 1;
		    nh_prev = nh_new;
		} else {
		    assert(dbit < bits2chk);
		    nh_prev->rtnhn_addr->rtnha_order
		      = bits2chk - (bits2chk - dbit) / 2;
		    break;
		}
	    }
	}
    }

    /*
     * By the time we get here we have an internal node on
     * which to hang the next hop address structure, pointed
     * to by nh_add, and an order, indicated by bitlen.  Allocate
     * and fill the structure, then add it in.
     */
    rt_nhaddr_adds++;
    rt_nhaddr_counts[family]++;
    nha = RT_NEXTHOP_ADDR_ALLOC();
    nha->rtnha_inode = (void_t) nh_add;
    nh_add->rtnhn_addr = nha;
    nha->rtnha_refcount = 1;
    nha->rtnha_order = bitlen;
    nha->rtnha_addr = sockdup(nhaddr);
    if (si->si_offset != 2*sizeof(byte)) {	/* XXX cleanup assumptions */
	register byte *addr = (byte *) nha->rtnha_addr;
	register u_int i;

	for (i = 2 * sizeof(byte); i < si->si_offset; i++) {
	    addr[i] = (byte) 0;
	}
    }
    return nha;
}


/*
 * rt_nhaddr_free - free a next hop address, delete it from the
 *		    radix tree if the refcount has dropped to zero.
 */
void
rt_nhaddr_free __PF1(nha, rt_nexthop_addr *)
{
    register rt_nhaddr_node *nh, *nh_prev, *nh_next;
    register int family;

    /*
     * If the address is still referenced just decrement the
     * reference count and return.
     */
    rt_nhaddr_frees++;
    if (nha->rtnha_refcount > 1) {
	nha->rtnha_refcount--;
	return;
    }
    assert(nha->rtnha_refcount);

    /*
     * This address is a goner.  Free it up, then see if we can
     * delete the node.  If the node has two children we can't, so
     * clean up the node and continue in this case.
     */
    rt_nhaddr_freed++;
    family = socktype(nha->rtnha_addr);
    rt_nhaddr_counts[family]--;
    sockfree(nha->rtnha_addr);
    nh = (rt_nhaddr_node *) (nha->rtnha_inode);
    RT_NEXTHOP_ADDR_FREE(nha);

    if (nh->rtnhn_left && nh->rtnhn_right) {
	nh->rtnhn_addr = (rt_nexthop_addr *) 0;
	return;
    }

    /*
     * This node needs to be pulled.  If it has no children the node
     * above may need to be pulled as well, so catch this case first.
     */
    if (!(nh->rtnhn_left) && !(nh->rtnhn_right)) {
	nh_prev = nh->rtnhn_parent;
	RT_NHADDR_NODE_FREE(nh);
	rt_nhaddr_inodes[family]--;

	if (!nh_prev) {
	    rt_nhaddr_roots[family] = (rt_nhaddr_node *) 0;
	    return;
	}

	if (nh_prev->rtnhn_left == nh) {
	    nh_prev->rtnhn_left = (rt_nhaddr_node *) 0;
	} else {
	    assert(nh_prev->rtnhn_right == nh);
	    nh_prev->rtnhn_right = (rt_nhaddr_node *) 0;
	}

	if (nh_prev->rtnhn_addr) {
	    return;		/* parent stays */
	}
	nh = nh_prev;
    }

    /*
     * Here we're left with a one-way brancher with no external
     * stuff attached.  Remove him, promoting his one remaining
     * child.
     */
    nh_prev = nh->rtnhn_parent;
    if (nh->rtnhn_left) {
	nh_next = nh->rtnhn_left;
    } else {
	nh_next = nh->rtnhn_right;
    }
    nh_next->rtnhn_parent = nh_prev;

    if (!nh_prev) {
	/*
	 * New root node
	 */
	rt_nhaddr_roots[family] = nh_next;
    } else {
	/*
	 * Find pointer to nh, point it at nh_next instead.
	 */
	if (nh_prev->rtnhn_left == nh) {
	    nh_prev->rtnhn_left = nh_next;
	} else {
	    assert(nh_prev->rtnhn_right == nh);
	    nh_prev->rtnhn_right = nh_next;
	}
    }

    /*
     * This one is disconnected, get rid of it too.
     */
    RT_NHADDR_NODE_FREE(nh);
    rt_nhaddr_inodes[family]--;
}


/*
 * rt_nexthops_find - return the canonical version of the specified next
 *		      hops, with the reference count incremented.
 */
rt_nexthops *
rt_nexthops_find __PF1(nhp, rt_nexthops *)
{
    register rt_nexthop_addr *nha;
#if	RT_N_MULTIPATH > 1
    register u_int i;
#endif	/* RT_N_MULTIPATH > 1 */ 
    register rt_nexthops_entry *nhep;
    u_long hash;
    static rt_nexthops_entry nhe = { 0 };
    int no_check_for_old = 0;

    rt_nh_finds++;

    /*
     * Some types of next hops are easy.  Return the easy ones quick.
     */
    switch (nhp->rtn_type) {
    default:
	assert(FALSE);

    case RT_NH_REJECT:
	assert(nhp->rtn_n_gw == 0);
	RT_NH_ALLOC(rt_nh_reject);
	return rt_nh_reject;

    case RT_NH_BLACKHOLE:
	assert(nhp->rtn_n_gw == 0);
	RT_NH_ALLOC(rt_nh_blackhole);
	return rt_nh_blackhole;

    case RT_NH_INTERFACE:
	assert(nhp->rtn_n_gw == 1 && !(nhp->rtn_gateway[0].rtg_addr));
	assert(nhp->rtn_gateway[0].rtg_ifap);
	hash = ((u_long)((RT_NH_INTERFACE << 8) | 1)
	  ^ (u_long)(nhp->rtn_gateway[0].rtg_ifap)) / RT_NH_HASH_SIZE;
	nhep = rt_nexthops_hash[hash];
	while (nhep) {
	    if (nhep->rtnh_type == RT_NH_INTERFACE
	      && nhep->rtnh_gateway[0].rtg_ifap
		== nhp->rtn_gateway[0].rtg_ifap) {
		RT_NH_ALLOC(nhep);
		return &(nhep->rtnh_nexthop);
	    }
	    nhep = nhep->rtnh_next;
	}
	rt_nh_added++;
	rt_nh_count++;
	rt_nh_allocs++;
	nhep = RT_NEXTHOPS_ENTRY_ALLOC();
	nhep->rtnh_type = RT_NH_INTERFACE;
	nhep->rtnh_n_gw = 1;
	nhep->rtnh_gateway[0].rtg_ifap = nhp->rtn_gateway[0].rtg_ifap;
	IF_ALLOC(nhep->rtnh_gateway[0].rtg_ifap);
	nhep->rtnh_hash = hash;
	nhep->rtnh_refcount = 1;
	nhep->rtnh_next = rt_nexthops_hash[hash];
	rt_nexthops_hash[hash] = nhep;
	return &(nhep->rtnh_nexthop);

    case RT_NH_UNUSABLE:
	if (nhp->rtn_n_gw == 0) {
	    RT_NH_ALLOC(rt_nh_none);
	    return rt_nh_none;
	}
	break;

    case RT_NH_ROUTER:
	break;
    }

    /*
     * If we get here we've filtered out everything easy, and
     * are left with next hop types which have protocol addresses.
     * Find and/or insert each protocol address into the tree.
     */
    assert(nhp->rtn_n_gw && nhp->rtn_n_gw <= RT_N_MULTIPATH);
    hash = (u_long) 0;
    nhe.rtnh_type = nhp->rtn_type;
    nhe.rtnh_n_gw = nhp->rtn_n_gw;

#if	RT_N_MULTIPATH > 1
    i = 0;
    do {
#else	/* RT_N_MULTIPATH > 1 */
#define	i 0
    do {
#endif	/* RT_N_MULTIPATH > 1 */
	if (i > 0) {
	    assert(socktype(nhp->rtn_gateway[0].rtg_addr)
	      == socktype(nhp->rtn_gateway[i].rtg_addr));
	}
	nha = rt_nhaddr_find(nhp->rtn_gateway[i].rtg_addr);
	if (nha->rtnha_refcount == 1) {
	    no_check_for_old = 1;
	} else if (nhp->rtn_type == RT_NH_ROUTER
#if	RT_N_MULTIPATH > 1
	  && nhp->rtn_n_gw == 1
#endif	/* RT_N_MULTIPATH > 1 */
	  && (nhep = nha->rtnha_entry)
	  && nhep->rtnh_gateway[0].rtg_ifap == nhp->rtn_gateway[0].rtg_ifap) {
	    /*
	     * Found it already.
	     */
	    rt_nh_found_fast++;
	    RT_NHADDR_FREE(nha);
	    RT_NH_ALLOC(nhep);
	    return &(nhep->rtnh_nexthop);
	}
	nhe.rtnh_addr[i] = nha;
	hash ^= ((u_long)(nha->rtnha_addr));
	if (nhp->rtn_type == RT_NH_ROUTER) {
	    nhe.rtnh_gateway[i].rtg_ifap = nhp->rtn_gateway[i].rtg_ifap;
	    hash ^= ((u_long)(nhp->rtn_gateway[i].rtg_ifap));
	} else {
	    nhe.rtnh_gateway[i].rtg_ifap = (if_addr *) 0;
	}
#if	RT_N_MULTIPATH > 1
    } while ((++i) < nhe.rtnh_n_gw);
#else	/* RT_N_MULTIPATH > 1 */
    } while (0);
#undef	i
#endif	/* RT_N_MULTIPATH > 1 */

#if	RT_N_MULTIPATH > 1
    /*
     * Okay.  At this point we've collected pointers to the nexthop
     * address structures for each of our next hop addresses.  If there
     * was more than one of these we'll need to sort them into ascending
     * order.
     */
    if (nhe.rtnh_n_gw > 1) {
	register u_int j;

	hash = (u_long) 0;
	for (j = 0; j < (nhp->rtn_n_gw - 1); j++) {
	    for (i = j + 1; i < nhp->rtn_n_gw; i++) {
		if (nhe.rtnh_addr[j]->rtnha_order
		  > nhe.rtnh_addr[i]->rtnha_order) {
		    nha = nhe.rtnh_addr[i];
		    nhe.rtnh_addr[i] = nhe.rtnh_addr[j];
		    nhe.rtnh_addr[j] = nha;
		    if (nhe.rtnh_type == RT_NH_ROUTER) {
			register if_addr *tmp = nhe.rtnh_gateway[i].rtg_ifap;
			nhe.rtnh_gateway[i].rtg_ifap
			  = nhe.rtnh_gateway[j].rtg_ifap;
			nhe.rtnh_gateway[j].rtg_ifap = tmp;
		    }
		}
	    }
	    nhe.rtnh_gateway[j].rtg_addr = nhe.rtnh_addr[j]->rtnha_addr;
	}
	nhe.rtnh_gateway[j].rtg_addr = nhe.rtnh_addr[j]->rtnha_addr;
    } else {
#endif	/* RT_N_MULTIPATH > 1 */
	nhe.rtnh_gateway[0].rtg_addr = nhe.rtnh_addr[0]->rtnha_addr;
#if	RT_N_MULTIPATH > 1
    }
#endif	/* RT_N_MULTIPATH > 1 */

    hash ^= ((u_long)(nhe.rtnh_type) << 8)|((u_long)(nhe.rtnh_n_gw));
    nhe.rtnh_hash = hash;

    /*
     * Check to see if we have one like this in the table already.
     */
    if (!no_check_for_old) {
	for (nhep = rt_nexthops_hash[hash]; nhep; nhep = nhep->rtnh_next) {
	    if (nhep->rtnh_type == nhe.rtnh_type
	      && nhep->rtnh_n_gw == nhe.rtnh_n_gw
	      && !bcmp((caddr_t) nhep->rtnh_gateway,
		       (caddr_t) nhe.rtnh_gateway,
		       ((size_t) nhe.rtnh_n_gw) * sizeof(rt_gateway))) {
		/*
		 * Matched it.  Bump the refcount on this and return
		 */
#if	RT_N_MULTIPATH > 1
		i = 0;
		do {
#else	/* RT_N_MULTIPATH > 1 */
#define	i 0
		do {
#endif	/* RT_N_MULTIPATH > 1 */
		    RT_NHADDR_FREE(nhe.rtnh_addr[i]);
#if	RT_N_MULTIPATH > 1
		} while ((++i) < nhe.rtnh_n_gw);
#else	/* RT_N_MULTIPATH > 1 */
		} while (0);
#undef	i
#endif	/* RT_N_MULTIPATH > 1 */
		RT_NH_ALLOC(nhep);
		rt_nh_found_slow++;
		goto got_entry;
	    }
	}
    }

    /*
     * None in the table like this, allocate memory and store it.
     */
    nhep = RT_NEXTHOPS_ENTRY_ALLOC();
    nhep->rtnh_type = nhe.rtnh_type;
    nhep->rtnh_n_gw = nhe.rtnh_n_gw;
    nhep->rtnh_hash = hash;
    nhep->rtnh_refcount = 1;
    rt_nh_allocs++;
#if	RT_N_MULTIPATH > 1
    i = 0;
    do {
#else	/* RT_N_MULTIPATH > 1 */
#define	i 0
    do {
#endif	/* RT_N_MULTIPATH > 1 */
	nhep->rtnh_gateway[i] = nhe.rtnh_gateway[i];	/* struct copy */
	nhep->rtnh_addr[i] = nhe.rtnh_addr[i];
	if (nhe.rtnh_gateway[i].rtg_ifap) {
	    IFA_ALLOC(nhe.rtnh_gateway[i].rtg_ifap);
	}
#if	RT_N_MULTIPATH > 1
    } while ((++i) < nhe.rtnh_n_gw);
#else	/* RT_N_MULTIPATH > 1 */
    } while (0);
#undef	i
#endif	/* RT_N_MULTIPATH > 1 */
    nhep->rtnh_next = rt_nexthops_hash[hash];
    rt_nexthops_hash[hash] = nhep;
    rt_nh_added++;
    rt_nh_count++;

    /*
     * That's it, mostly done.  If this is a router next hop with
     * only one gateway, record it in the next hop address entry for
     * quick future access.
     */
got_entry:
    if (nhe.rtnh_type == RT_NH_ROUTER
#if	RT_N_MULTIPATH > 1
      && nhe.rtnh_n_gw == 1
#endif	/* RT_N_MULTIPATH > 1 */
			) {
	nhep->rtnh_addr[0]->rtnha_entry = nhep;
    }
    return &(nhep->rtnh_nexthop);
}


/*
 * rt_nexthops_free - decrement the reference count on a nexthops
 *		      entry.  If it drops to zero, free it.
 */
void
rt_nexthops_free __PF1(nhp, rt_nexthops *)
{
    register rt_nexthops_entry *nhep = (rt_nexthops_entry *) nhp;
#if	RT_N_MULTIPATH > 1
    register int i;
#endif	/* RT_N_MULTIPATH > 1 */
    int interface_nexthop;

    rt_nh_frees++;
    /*
     * See if it is refcount'd out.  If not, decrement and return.
     */
    if (nhep->rtnh_refcount > 1) {
	nhep->rtnh_refcount--;
	return;
    }
    assert(nhep->rtnh_refcount);

    /*
     * Some types are easier to dispatch then others. 
     */
    switch (nhp->rtn_type) {
    default:
	assert(FALSE);

    case RT_NH_REJECT:
	assert(nhep == &rt_nh_reject_entry);
	rt_nh_reject_entry.rtnh_refcount = 0;
	return;

    case RT_NH_BLACKHOLE:
	assert(nhep == &rt_nh_blackhole_entry);
	rt_nh_blackhole_entry.rtnh_refcount = 0;
	return;

    case RT_NH_INTERFACE:
	interface_nexthop = 1;
	break;

    case RT_NH_UNUSABLE:
	if (nhep->rtnh_n_gw == 0) {
	    rt_nh_none_entry.rtnh_refcount = 0;
	    return;
	}
	/*FALLSTHROUGH*/

    case RT_NH_ROUTER:
	interface_nexthop = 0;
	break;
    }


    /*
     * This guy's a goner.  Get him out of the hash table first
     */
    rt_nh_freed++;
    rt_nh_count--;
    if (rt_nexthops_hash[nhep->rtnh_hash] == nhep) {
	rt_nexthops_hash[nhep->rtnh_hash] = nhep->rtnh_next;
    } else {
	register rt_nexthops_entry *nhep_prev;
	
	nhep_prev = rt_nexthops_hash[nhep->rtnh_hash];
	while (nhep_prev) {
	    if (nhep_prev->rtnh_next == nhep) {
		nhep_prev->rtnh_next = nhep->rtnh_next;
		break;
	    }
	    nhep_prev = nhep_prev->rtnh_next;
	}
	assert(nhep_prev);		/* wasn't in hash table */
    }

    /*
     * If this is an interface nexthop, just free the interface,
     * blow out the structure and return.
     */
    if (interface_nexthop) {
	IFA_FREE(nhep->rtnh_gateway[0].rtg_ifap);
	RT_NEXTHOPS_ENTRY_FREE(nhep);
	return;
    }

    /*
     * Harder here.  Free all if_addr's and nexthop address entries
     * associated with the nexthop entry.
     */
#if	RT_N_MULTIPATH > 1
    i = 0;
    do {
#else	/* RT_N_MULTIPATH > 1 */
#define	i 0
    do {
#endif	/* RT_N_MULTIPATH > 1 */

	/*
	 * Decrement the reference count.  If the address is
	 * still referenced, continue after making sure we don't
	 * leave a dangling entry pointer.
	 */
	if (nhep->rtnh_gateway[i].rtg_ifap) {
	    IFA_FREE(nhep->rtnh_gateway[i].rtg_ifap);
	}
	RT_NHADDR_FREE(nhep->rtnh_addr[i]);

#if	RT_N_MULTIPATH > 1
    } while ((++i) < nhep->rtnh_n_gw);
#else	/* RT_N_MULTIPATH > 1 */
    } while (0);
#undef	i
#endif	/* RT_N_MULTIPATH > 1 */

    /*
     * Get rid of the next hops entry too.  Then we're done.
     */
    RT_NEXTHOPS_ENTRY_FREE(nhep);
}


/*
 * rt_nexthops_merge - merge a pair of nexthops structures into a
 *		       single new structure.  This is useful for
 *		       routing protocols which compute multipath
 *		       routes.
 */
rt_nexthops *
rt_nexthops_merge __PF2(nhp1, rt_nexthops *,
			nhp2, rt_nexthops *)
{
    register rt_nexthops_entry *nhep1 = (rt_nexthops_entry *) nhp1;
    register rt_nexthops_entry *nhep2 = (rt_nexthops_entry *) nhp2;
#if	RT_N_MULTIPATH > 1
    register int j, j1, j2;
    static rt_gateway gws[RT_N_MULTIPATH] = { 0 };
    rt_nexthop_addr *paddrs[RT_N_MULTIPATH];
    u_long hash;
#endif	/* RT_N_MULTIPATH > 1 */

    assert(nhep1->rtnh_type==RT_NH_UNUSABLE || nhep1->rtnh_type==RT_NH_ROUTER);
    assert(nhep1->rtnh_type==RT_NH_UNUSABLE || nhep1->rtnh_type==RT_NH_ROUTER);
    rt_nh_merges++;

    /*
     * Catch an easy case
     */
    if (nhep1 == nhep2) {
	RT_NH_ALLOC(nhep1);
	return &(nhep1->rtnh_nexthop);
    }

    /*
     * If we have a mix of normal and unusable routes, try to return
     * the usable next hops
     */
    if (nhep1->rtnh_type == RT_NH_UNUSABLE) {
	if (nhep2->rtnh_type != RT_NH_UNUSABLE
	  || nhep1->rtnh_n_gw == 0) {
	    RT_NH_ALLOC(nhep2);
	    return &(nhep2->rtnh_nexthop);
	}
    } else {
	if (nhep2->rtnh_type == RT_NH_UNUSABLE) {
	    RT_NH_ALLOC(nhep1);
	    return &(nhep1->rtnh_nexthop);
	}
    }

#if	RT_N_MULTIPATH == 1
    /*
     * We need to return one or the other.  Return the one with
     * the numerically highest next hop address, so determine which
     * that is.
     */
    if (nhep1->rtnh_addr[0]->rtnha_order
      <= nhep2->rtnh_addr[0]->rtnha_order) {
	if (nhep1->rtnh_addr[0]->rtnha_order
	    < nhep2->rtnh_addr[0]->rtnha_order
	  || ((u_long)(nhep1->rtnh_gateway[0].rtg_ifap))
	    < ((u_long)(nhep1->rtnh_gateway[0].rtg_ifap))) {
	    nhep1 = nhep2;
	}
    }

    RT_NH_ALLOC(nhep1);
    return &(nhep1->rtnh_nexthop);
#else	/* RT_N_MULTIPATH == 1 */
    j1 = nhep1->rtnh_n_gw - 1;
    j2 = nhep2->rtnh_n_gw - 1;
    j = RT_N_MULTIPATH;
    hash = 0;
    do {
	register int which = 0;

	j--;
	if (j1 < 0) {
	    which = 1;
	} else if (j2 >= 0) {
	    register rt_nexthop_addr *a1 = nhep1->rtnh_addr[j1];
	    register rt_nexthop_addr *a2 = nhep2->rtnh_addr[j2];

	    if (a1 == a2) {
		which = 2;
	    } else if (a1->rtnha_order < a2->rtnha_order) {
		which = 1;
	    }
	}

	switch (which) {
	case 2:
	    j1--;
	    /* FALLSTHROUGH */
	case 1:
	    gws[j] = nhep2->rtnh_gateway[j2];
	    paddrs[j] = nhep2->rtnh_addr[j2];
	    j2--;
	    break;
	case 0:
	    gws[j] = nhep1->rtnh_gateway[j1];
	    paddrs[j] = nhep1->rtnh_addr[j1];
	    j1--;
	    break;
	}

	hash ^= (u_long) gws[j].rtg_addr;
	hash ^= (u_long) gws[j].rtg_ifap;
    } while (j && (j1 >= 0 || j2 >= 0));

    /*
     * At this point we've collected all the addresses we have (room
     * for).  Complete the hash and see if we already have a set of
     * next hops like this.
     */
    j1 = RT_N_MULTIPATH - j;
    hash ^= (((u_long)nhep2->rtnh_type) << 8) | ((u_long) j1);
    hash %= RT_NH_HASH_SIZE;

    for (nhep1 = rt_nexthops_hash[hash]; nhep1; nhep1 = nhep1->rtnh_next) {
	if (nhep1->rtnh_type == nhep2->rtnh_type
	  && nhep1->rtnh_n_gw == ((byte) j1)
	  && !bcmp((caddr_t) &nhep1->rtnh_gateway,
		   (caddr_t) &gws[j],
		   ((size_t) j1) * sizeof(rt_gateway))) {
	    break;
	}
    }

    if (nhep1) {
	RT_NH_ALLOC(nhep1);
    } else {
	/*
	 * No match for this, create a new entry.
	 */
	rt_nh_added++;
	rt_nh_count++;
	nhep1 = RT_NEXTHOPS_ENTRY_ALLOC();
	nhep1->rtnh_type = nhep2->rtnh_type;
	nhep1->rtnh_n_gw = (byte) j1;
	nhep1->rtnh_hash = (u_int32) hash;
	nhep1->rtnh_refcount = 1;
	rt_nh_allocs++;
	j = RT_N_MULTIPATH;
	while (j1--) {
	    j--;
	    nhep1->rtnh_gateway[j1] = gws[j];	/* struct copy */
	    if (gws[j].rtg_ifap) {
		IFA_ALLOC(gws[j].rtg_ifap);
	    }
	    nhep1->rtnh_addr[j] = (void_t) paddrs[j];
	    paddrs[j]->rtnha_refcount++;
	}
	nhep1->rtnh_next = rt_nexthops_hash[hash];
	rt_nexthops_hash[hash] = nhep1;
    }

    return &(nhep1->rtnh_nexthop);
#endif	/* RT_N_MULTIPATH == 1 */
}


/*
 * %(Copyright)
 */
