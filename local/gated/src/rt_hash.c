/*
 *  $Header: /users/jch/src/gated/src/RCS/rt_table.c,v 2.0 90/04/16 16:53:42 jch Exp Locker: jch $
 */

/*%Copyright%*/


#define	INCLUDE_RT_VAR
#include "include.h"


/* Defines for use by the various tables following */

/* Scan all buckets in a table */
#define	RT_SCTBL(rtb)	{\
			   rt_head **rtb;\
			   for (rtb = rt_inet_hash; *rtb != (rt_head *) (-1); rtb++)
#define	RT_SCTBL_END(rtb)	}

/* Scan all entries in this bucket */
#define	RT_BUCKET(rth, rtb)	{\
			   rt_head *rths = (rt_head *) 0;\
			   for (rth = *rtb; rth != rths; rth = rth->rth_forw, rths = *rtb)
#define	RT_BUCKET_END(rth, rtb)	if (rth == rths) rth = (rt_head *) 0; }

/*
 *	Macro to scan through entire active routing table
 */
#define RT_WHOLE(rt)	{ rt_head *rth; RT_SCTBL(rtb) RT_BUCKET(rth, rtb) RT_ALLRT(rt, rth)

#define	RT_WHOLE_END(rt)	RT_ALLRT_END(rt, rth) RT_BUCKET_END(rth, rtb) RT_SCTBL_END(rtb) }

/*
 *	Macro to scan through entire active routing table
 */
#define RT_TABLE(rt, rth)	{ rt_head *rth; RT_SCTBL(rtb) RT_BUCKET(rth, rtb) RT_IFRT(rt, rth)

#define	RT_TABLE_END(rt, rth)	RT_IFRT_END RT_BUCKET_END(rth, rtb) RT_SCTBL_END(rtb) }

/* Hash into a table */
#define	RT_HASH(dst, rtb)	rt_head **rtb;\
    			u_long hash = rt_hash(dst) & ROUTEHASHMASK; \
    				rtb = &rt_inet_hash[hash]


/* Define the size of the routing hash table in number of buckets.	*/
/* The larger the number the more buckets there are and the less	*/
/* compares needed to find a particular route.  The more buckets	*/
/* used, the more memory used.						*/
#define	ROUTEHASHSIZ	64
#define	ROUTEHASHMASK	(ROUTEHASHSIZ - 1)
    
static rt_head *rt_inet_hash[ROUTEHASHSIZ + 1];

/*
 * hash routine for the route table.
 */

static u_long
rt_hash(sin)
register sockaddr_un *sin;
{
    register u_long n = ntohl(sock2ip(sin));

    if (n) {
	while (!(n & 0xff)) {
	    n >>= NBBY;
	}
    }

    return n;
}


/**/

/*
 *	Locate the rt_head for the given destination
 */
rt_head *
rt_table_locate(dst, mask)
sockaddr_un *dst;
sockaddr_un *mask;
{
    register rt_head *rth = 0;
    
    RT_HASH(dst, rtb);

    RT_BUCKET(rth, rtb) {
	if ((rth->rth_hash == hash) &&
	    sockaddrcmp(rth->rth_dest, dst) &&
	    (!mask || mask == rth->rth_dest_mask)) {
	    break;
	}
    } RT_BUCKET_END(rth, rtb);

    return rth;
}


#ifdef	notdef
/* Look up a destination the way the kernel would */
/* XXX - This needs to be a generic best match function */
rt_entry *
rt_lookup __PF3(state, flag_t,
		dst, sockaddr_un *,
		proto_mask, flag_t)
{
    sockaddr_un *dest;
    sockaddr_un *mask;
    rt_entry *rt;

    dest = sockdup(dst);

    if (BIT_TEST(state, RTS_HOSTROUTE)) {
	/* Lookup host route */
	rt = rt_locate(RTS_HOSTROUTE,
		       dest,
		       (sockaddr_un *) 0,
		       RTPROTO_BIT(proto));
	if (rt &&
	    !BIT_TEST(rt->rt_state, RTS_DELETE|RTS_HIDDEN) &&
	    (proto != RTPROTO_ANY || rt == rt->rt_active)) {
	    sockfree(dest);
	    return rt;
	}
    }

    if (BIT_TEST(state, RTS_NETROUTE)) {
	/* If a subnet, lookup subnet route */
	if (mask = if_subnetmask(sock2in(dest))) {
	    sockmask(dest, mask);
	    rt = rt_locate(RTS_NETROUTE, dest, mask, RTPROTO_BIT(proto));
	    if (rt &&
		!BIT_TEST(rt->rt_state, RTS_DELETE|RTS_HIDDEN) &&
		(proto != RTPROTO_ANY || rt == rt->rt_active)) {
		sockfree(dest);
		return rt;
	    }
	}

	switch (socktype(dest)) {
	case AF_INET:
	    /* Lookup network route */
	    mask = inet_mask_natural(dest);
	    sock2ip(dest) &= sock2ip(mask);
	    rt = rt_locate(RTS_NETROUTE, dest, mask, RTPROTO_BIT(proto));
	    sockfree(dest);
	    if (rt &&
		!BIT_TEST(rt->rt_state, RTS_DELETE|RTS_HIDDEN) &&
		(proto != RTPROTO_ANY || rt == rt->rt_active)) {
		return rt;
	    }

	    /* Finally lookup default route */
	    rt = rt_locate(RTS_NETROUTE, inet_addr_default, inet_mask_default, RTPROTO_BIT(proto));
	    if (rt &&
		!BIT_TEST(rt->rt_state, RTS_DELETE|RTS_HIDDEN) &&
		(proto != RTPROTO_ANY || rt == rt->rt_active)) {
		return rt;
	    }
	    break;
	}
    }

    /* No luck */
    return (rt_entry *) 0;
}
#endif	/* notdef */


/*
 *	Insert this head into the tree
 */
void
rt_table_add(rth)
rt_head *rth;
{
    RT_HASH(rth->rth_dest, rtb);

    rth->rth_hash = hash;

    /* Insert this rt_head structure at end of doubly linked list */
    if (*rtb) {
	insque((struct qelem *) rth, (struct qelem *) (*rtb)->rth_back);
    } else {
	*rtb = rth;
	rth->rth_forw = rth->rth_back = rth;
    }
}


/*
 *	Remove this head from table
 */
void
rt_table_delete(rth)
rt_head *rth;
{

    if (rt_inet_hash[rth->rth_hash] == rth) {
	/* Removing first element in the hash chain */
	
	if (rth == rth->rth_forw) {
	    /* Removing only element in the hash chain */

	    rt_inet_hash[rth->rth_hash] = (rt_head *) 0;
	} else {
	    rt_inet_hash[rth->rth_hash] = rth->rth_forw;
	}
    }

    remque((struct qelem *) rth);
}


/**/

int rtlist_block_index;
rt_list *rt_change_list;			/* Number of the active list */

	    
/* Build a change list of all active routes */
/* 	Routes not to be advised and hidden routes are not located */
rt_list *
rthlist_active(af)
int af;
{
    rt_entry *rt;
    rt_list *rtl = (rt_list *) 0;

    RT_TABLE(rt, rth) {
	if (BIT_TEST(rt->rt_state, RTS_NOADVISE)) {
	    /* Not to be announced */
	    continue;
	}
	if (BIT_TEST(rt->rt_state, RTS_HIDDEN|RTS_DELETE) && !BIT_TEST(rt->rt_state, RTS_HOLDDOWN)) {
	    /* Deleted or hidden, unless in holddown */
	    continue;
	}
	RTLIST_ADD(rtl, rt->rt_head);
    } RT_TABLE_END(rt, rth) ;

    return rtl ? rtl->rtl_root : rtl;
}


/* Build a change list of all active routes */
/* 	Routes not to be advised and hidden routes are not located */
rt_list *
rtlist_active(af)
int af;
{
    rt_entry *rt;
    rt_list *rtl = (rt_list *) 0;

    RT_TABLE(rt, rth) {
	if (BIT_TEST(rt->rt_state, RTS_NOADVISE)) {
	    /* Not to be announced */
	    continue;
	}
	if (BIT_TEST(rt->rt_state, RTS_HIDDEN|RTS_DELETE) && !BIT_TEST(rt->rt_state, RTS_HOLDDOWN)) {
	    /* Deleted or hidden, unless in holddown */
	    continue;
	}
	RTLIST_ADD(rtl, rt);
    } RT_TABLE_END(rt, rth) ;

    return rtl ? rtl->rtl_root : rtl;
}


rt_list *
rtlist_all(af)
int af;
{
    register rt_entry *rt;
    register rt_list *rtl = (rt_list *) 0;

    RT_WHOLE(rt) {
	RTLIST_ADD(rtl, rt);
    } RT_WHOLE_END(rt) ;

    return rtl ? rtl->rtl_root : rtl;
}


rt_list *
rthlist_all(af)
int af;
{
    register rt_head *rth;
    register rt_list *rtl = (rt_list *) 0;

    RT_SCTBL(rtb) RT_BUCKET(rth, rtb) {
	RTLIST_ADD(rtl, rth);
    } RT_BUCKET_END(rth, rtb) RT_SCTBL_END(rtb) ;

    return rtl ? rtl->rtl_root : rtl;
}


/* Build a change list for a specific protocol */
rt_list *
rtlist_proto(af, protos)
int af;
flag_t protos;
{
    rt_entry *rt = (rt_entry *) 0;
    rt_list *rtl = (rt_list *) 0;

    RT_WHOLE(rt) {
	if (RTPROTO_BIT(rt->rt_gwp->gw_proto) & protos) {
	    RTLIST_ADD(rtl, rt);
	    break;
	}
    } RT_WHOLE_END(rt) ;

    return rtl ? rtl->rtl_root : rtl;
}


/* Build a change list based on the gateway pointer */
rt_list *
rtlist_gw(gwp)
gw_entry *gwp;
{
    rt_entry *rt = (rt_entry *) 0;
    rt_list *rtl = (rt_list *) 0;

    if (gwp)  {
	RT_WHOLE(rt) {
	    if (rt->rt_gwp == gwp) {
		RTLIST_ADD(rtl, rt);
	    }
	} RT_WHOLE_END(rt) ;
    } 

    return rtl ? rtl->rtl_root : rtl;
}


#ifdef	RT_SANITY
/*
 *	Check the integrity of the routing table
 */
void
rt_sanity()
{
    rt_head *rth;
    rt_entry *rt;
    int bucket = 0;
    int bounds_error = FALSE;
    caddr_t high = (caddr_t) sbrk(0);
    extern caddr_t end;

#define	BOUNDS(p)	((caddr_t) (p) < end || (caddr_t) (p) > high)

    assert(rt_inet_hash[ROUTEHASHSIZ] == (rt_head *) (-1));

    RT_SCTBL(rtb) {
	int head = 0;

	RT_BUCKET(rth, rtb) {
	    int route = 0;
	    int head_error = FALSE;

	    /* First check for bounds check on pointers */
	    if (BOUNDS(rth)) {
		trace(TR_ALL, 0, "rt_sanity: bounds check on head pointer (%X)",
		      rth);
		head_error = TRUE;
		bounds_error = TRUE;
	    } else {
		if (BOUNDS(rth->rth_forw)) {
		    trace(TR_ALL, 0, "rt_sanity: bounds check on forward head pointer (%X)",
			  rth->rth_forw);
		    head_error = TRUE;
		    bounds_error = TRUE;
		} else if (rth->rth_forw->rth_back != rth) {
		    trace(TR_ALL, 0, "rt_sanity: forward head pointer (%X != %X)",
			  rth->rth_forw->rth_back,
			  rth);
		    head_error = TRUE;
		}

		if (BOUNDS(rth->rth_back)) {
		    trace(TR_ALL, 0, "rt_sanity: bounds check on backward head pointer (%X)",
			  rth->rth_back);
		    head_error = TRUE;
		    bounds_error = TRUE;
		} else if (rth->rth_back->rth_forw != rth) {
		    trace(TR_ALL, 0, "rt_sanity: backward head pointer (%X != %X)",
			  rth->rth_back->rth_forw,
			  rth);
		    head_error = TRUE;
		}

		/* If there is an active route, it had better be the first one */
		if (rth->rth_active && rth->rth_active != rth->rt_forw) {
		    trace(TR_ALL, 0, "rt_sanity: active route (%X != %X)",
			  rth->rth_active,
			  rth->rt_forw);
		    head_error = TRUE;
		}

		/* Then check the routes */
		RT_ALLRT(rt, rth) {
		    int route_error = FALSE;
		
		    /* First check for bounds check on pointers */
		    if (BOUNDS(rt)) {
			trace(TR_ALL, 0, "rt_sanity: bounds check on route pointer (%X)",
			      rt);
			route_error = TRUE;
			bounds_error = TRUE;
		    } else {
			if (rt->rt_head != rth) {
			    trace(TR_ALL, 0, "rt_sanity: upward pointer (%X != %X)",
				  rt->rt_head,
				  rth);
			    route_error = TRUE;
			}

			if (BOUNDS(rt->rt_forw)) {
			    trace(TR_ALL, 0, "rt_sanity: bounds check on forward route pointer (%X)",
				  rt->rt_forw);
			    route_error = TRUE;
			    bounds_error = TRUE;
			} else if (rt->rt_forw->rt_back != rt) {
			    trace(TR_ALL, 0, "rt_sanity: forward route pointer (%X != %X)",
				  rt->rt_forw->rt_back,
				  rt);
			    route_error = TRUE;
			}
			
			if (BOUNDS(rt->rt_back)) {
			    trace(TR_ALL, 0, "rt_sanity: bounds check on backward route pointer (%X)",
				  rt->rt_back);
			    route_error = TRUE;
			    bounds_error = TRUE;
			} else if (rt->rt_back->rt_forw != rt) {
			    trace(TR_ALL, 0, "rt_sanity: backward route pointer (%X != %X)",
				  rt->rt_back->rt_forw,
				  rt);
			    route_error = TRUE;
			}
		    }
		    
		    if (route_error) {
			trace(TR_ALL, 0, "rt_sanity: route %d",
			      route);
			break;
		    }
		
		    route++;
		} RT_ALLRT_END(rt, rth) ;

		if (head_error) {
		    trace(TR_ALL, 0, "rt_sanity: dest %A mask %A",
			  rth->rth_dest,
			  rth->rth_dest_mask);
		}
	    }

	    if (head_error) {
		trace(TR_ALL, 0, "rt_sanity: bucket %d head %d",
		      bucket,
		      head);
		/* XXX - need to figure out if we can continue on from here */
		break;
	    }

	    head++;
	} RT_BUCKET_END(rth, rtb) ;

	bucket++;
    } RT_SCTBL_END(rtb) ;

    if (bounds_error) {
	trace(TR_ALL, 0, "rt_sanity: bounds: low %#X high %#X",
	      end,
	      high);
    }
}
#endif	/* RT_SANITY */


void
rt_table_init_family(af, offset)
int af;
int offset;
{
    /* Nothing to do for a hash table */
}


void
rt_table_dump(tp, fd)
task *tp;
FILE *fd;
{
    (void) fprintf(fd,
		   "\tHashsize: %d\t\tHashmask: %04x\n",
		   ROUTEHASHSIZ,
		   ROUTEHASHMASK);
}


void
rt_table_init()
{
    /* Init the routing table */
    rt_inet_hash[ROUTEHASHSIZ] = (rt_head *) (-1);
}
