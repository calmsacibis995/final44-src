/*
 * $Id: ospf_rtab.c,v 1.18.2.3 1994/09/15 21:38:23 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"


/*
 * Is this route an active intra or inter area route?
 */
int
ospf_int_active __PF3(from, int,
		      area, struct AREA *,
		      r, rt_entry *)
{
    int ptype = PTYPE_BIT(ORT_PTYPE(r));

    if (ptype & PTYPE_INTER) {
        if (!(from & ptype)) {
            return TRUE;
	}
        return ORT_REV(r) == RTAB_REV;
    }

    if (ptype & PTYPE_INTRA) {
        if (!(from & ptype))
            return TRUE;
        if (ORT_AREA(r) == area) {
             return ORT_REV(r) == RTAB_REV;
        }
        return TRUE;
    }

    return FALSE;
}


/*
 * Is this route an active intra area route?
 */
static inline int
ospf_intra_active __PF3(from, int,
			area, struct AREA *,
			r, rt_entry *)
{
    int ptype = PTYPE_BIT(ORT_PTYPE(r));

    if (ptype & PTYPE_INTRA) {
        if (!(from & ptype)) {
            return TRUE;
	}
        if (ORT_AREA(r) == area) {
             return ORT_REV(r) == RTAB_REV;
        }
        return TRUE;
    }

    return FALSE;
}


/*
 * Enqueue r in order in this queue
 */
static void
enq_rtab __PF2(qhp, struct OSPF_ROUTE *,
	       r, struct OSPF_ROUTE *)
{
    struct OSPF_ROUTE *o;
    u_int32 id = RRT_DEST(r);

    for (o = qhp;
	 RRT_NEXT(o) && id < RRT_DEST(RRT_NEXT(o));
	 o = RRT_NEXT(o));

    /* insert r between o and o->next */
    ADD_Q(o, r);
}


/*
 * Search for id in this linked list
 */
static struct OSPF_ROUTE *
routescan __PF2(head, struct OSPF_ROUTE *,
		id, u_int32)
{
    struct OSPF_ROUTE *r = head;

    for (; (r && id < RRT_DEST(r)); r = RRT_NEXT(r)) ;

    if (r && id == RRT_DEST(r))
	return r;
    return (struct OSPF_ROUTE *) 0;
}


/*
 * Allocate route and install it in the routing table
 */
static int
rtr_build_route __PF3(a, struct AREA *,
		      v, struct LSDB *,
		      dtype, int)
{
    struct OSPF_ROUTE *r = (struct OSPF_ROUTE *) task_block_alloc(ospf_route_index);

    switch (dtype) {
    case DTYPE_ABR:
	v->lsdb_ab_rtr = r;
	break;

    case DTYPE_ASBR:
	v->lsdb_asb_rtr = r;
	break;
    }
    RRT_REV(r) = RTAB_REV;
    RRT_AREA(r) = a;
    RRT_DTYPE(r) = dtype;
    RRT_COST(r) = v->lsdb_dist;
    RRT_PTYPE(r) = LS_TYPE(v);
    ospf_nh_set(RRT_NH_CNT(r), RRT_NH(r),
		v->lsdb_nhcnt, v->lsdb_nh);
    RRT_ADVRTR(r) = ADV_RTR(v);
    /* set up back link */
    RRT_V(r) = v;
    RRT_DEST(r) = LS_ID(v);
    RRT_CHANGE(r) = E_NEW;

    /* Install on routing table */
    switch (LS_TYPE(v)) {
    case LS_SUM_ASB:
	enq_rtab(&ospf.sum_asb_rtab, r);
	break;
    case LS_RTR:
	if (dtype == DTYPE_ABR)
	    enq_rtab(&a->abrtab, r);
	if (dtype == DTYPE_ASBR)
	    enq_rtab(&a->asbrtab, r);
	break;
    }

    return TRUE;
}


/*
 * add v to the routing table
 */
int
addroute __PF4(a, struct AREA *,
	       v, struct LSDB *,
	       from, int,
	       from_area, struct AREA *)	/* associatiated area */
{
    rt_entry *rt;
    struct OSPF_ROUTE *rr = (struct OSPF_ROUTE *) 0;

    assert(DB_RTR(v));

    /*
     * The from parameter is the starting level of spf algorithm,
     * and is used to check for valid entry
     */

    switch (LS_TYPE(v)) {
    case LS_STUB:
    case LS_NET:
	/* if attached to this net, interface is the first hop */
	if (v->lsdb_route) {
	    /* had route, check for change */

	    rvbind(v->lsdb_route, v, a);
	    DB_WHERE(v) = ON_RTAB;
	} else {
	    /* check to see if anyone else was advertising this net */
	    /* This will also handle the case of inter becoming intra */

	    findroute(rt, DB_NETNUM(v), DB_MASK(v));
	    if (rt) {
		/*
		 * Bind route to this vertex
		 * There could be stub routes and net routes until
		 * things converge, so use the best route
		 */

		if (ORT_PTYPE(rt) > PTYPE_INTRA ||
		    ORT_REV(rt) != RTAB_REV ||
		    (ORT_REV(rt) == RTAB_REV &&
		     ORT_COST(rt) > v->lsdb_dist)) {
		    rvbind(rt, v, a);
		    DB_WHERE(v) = ON_RTAB;
		}
	    } else {
		/* no previous net adv */

		if (!ospf_build_route(a, v, (rt_entry *) 0, E_NEW))
		    return FLAG_NO_BUFS;
		DB_WHERE(v) = ON_RTAB;
	    }
	}
	break;

    case LS_RTR:
	/* only asbr and abr are added to rtab */
	/* AREA Border */

	if (ntohs(DB_RTR(v)->E_B) & bit_B) {
	    /* if this is this rtr, set accordingly */
	    if (DB_FIRSTQ(a->spf) == v) {
		v->lsdb_dist = 0;
	    }
	    if (v->lsdb_ab_rtr) {
		rr = v->lsdb_ab_rtr;
		RRT_REV(rr) = RTAB_REV;
		if (RRT_COST(rr) != v->lsdb_dist
		    || !ospf_nh_compare(v->lsdb_nhcnt, v->lsdb_nh,
				       RRT_NH_CNT(rr), RRT_NH(rr))) {
		    RRT_COST(rr) = v->lsdb_dist;
		    ospf_nh_set(RRT_NH_CNT(rr), RRT_NH(rr),
				v->lsdb_nhcnt, v->lsdb_nh);
		    RRT_CHANGE(rr) = E_NEXTHOP;
		} else
		    RRT_CHANGE(rr) = E_UNCHANGE;
	    } else {
		if (!rtr_build_route(a, v, DTYPE_ABR))
		    return FLAG_NO_BUFS;
	    }
	    DB_WHERE(v) = ON_RTAB;
	}
	/* AS Border router */
	if (ntohs(DB_RTR(v)->E_B) & bit_E) {
	    /* if this is this rtr, set accordingly */
	    if (DB_FIRSTQ(a->spf) == v) {
		v->lsdb_dist = 0;
	    }
	    if (v->lsdb_asb_rtr) {
		rr = v->lsdb_asb_rtr;
		RRT_REV(rr) = RTAB_REV;
		if (RRT_COST(rr) != v->lsdb_dist
		    || !ospf_nh_compare(v->lsdb_nhcnt, v->lsdb_nh,
				       RRT_NH_CNT(rr), RRT_NH(rr))) {
		    RRT_COST(rr) = v->lsdb_dist;
		    ospf_nh_set(RRT_NH_CNT(rr), RRT_NH(rr),
				v->lsdb_nhcnt, v->lsdb_nh);
		    RRT_CHANGE(rr) = E_NEXTHOP;
		} else
		    RRT_CHANGE(rr) = E_UNCHANGE;
	    } else {
		/* this node is ASBR */
		if (!rtr_build_route(a, v, DTYPE_ASBR))
		    return FLAG_NO_BUFS;
	    }
	    DB_WHERE(v) = ON_RTAB;
	}
	break;

    case LS_SUM_NET:
	if (!v->lsdb_route) {
	    /* see if one exists on current routing table */
	    findroute(rt, DB_NETNUM(v), DB_MASK(v));
	    if (rt) {
		/* check for possible intra-area route */
		if (ospf_intra_active(from, from_area, rt)) {
		    return FLAG_NO_PROBLEM;
		} else {
		    /* old or ase changing to inter so bind r to this v */

		    rvbind(rt, v, a);
		    return FLAG_NO_PROBLEM;
		}
	    } else {		/* route doesn't exist */
		if (!ospf_build_route(a, v, (rt_entry *) 0, E_NEW))
		    return FLAG_NO_BUFS;
	    }
	} else {		/* v->route != ROUTENULL */
	    /*
	     * v->route != ROUTENULL
	     * area border checked in netsum
	     */
	    rvbind(v->lsdb_route, v, a);
	}
	break;

    case LS_SUM_ASB:
	/* have route to as bdr rtr */
	if (!v->lsdb_asb_rtr) {
	    /* put on inter-area asb route tab */
	    if (!rtr_build_route(a, v, DTYPE_ASBR))
		return FLAG_NO_BUFS;
	} else {
	    rr = v->lsdb_asb_rtr;
	    RRT_REV(rr) = RTAB_REV;
	    if (v->lsdb_dist != RRT_COST(rr))
		RRT_COST(rr) = v->lsdb_dist;
	    if (!ospf_nh_compare(v->lsdb_nhcnt, v->lsdb_nh,
				 RRT_NH_CNT(rr), RRT_NH(rr))) {
		ospf_nh_set(RRT_NH_CNT(rr), RRT_NH(rr),
			    v->lsdb_nhcnt, v->lsdb_nh);
		RRT_CHANGE(rr) = E_NEXTHOP;
	    } else
		RRT_CHANGE(rr) = E_UNCHANGE;
	}
	break;

    case LS_ASE:
	if (!v->lsdb_route) {
	    /* see if one exists on current routing table */
	    findroute(rt, DB_NETNUM(v), DB_MASK(v));
	    if (rt) {
		/* may have already run intra and sum for single area */
		if (ospf_int_active(from, from_area, rt)) {
		    return FLAG_NO_PROBLEM;
		} else {
		    /* current route is invalid - bind route to this v */
		    rvbind(rt, v, a);
		    return FLAG_NO_PROBLEM;
		}
	    } else {		/* no existing route */
		if (!ospf_build_route(a, v, (rt_entry *) 0, E_NEW))
		    return FLAG_NO_BUFS;
	    }
	} else {		/* v->route != ROUTENULL */
	    /* GOT_A_BDR && BORDER_ACTIVE are true */
	    rvbind(v->lsdb_route, v, a);
	}
	break;
    }
    return FLAG_NO_PROBLEM;
}


struct OSPF_ROUTE *
rtr_findroute __PF4(area, struct AREA *,
		    id, u_int32,
		    dtype, int,
		    ptype, int)
{
    struct OSPF_ROUTE *r;
    struct AREA *a;


    if (ptype & PTYPE_INTRA) {
	/* search intra area tables */
	switch (dtype) {

	case DTYPE_ASBR:
	    if (area != AREANULL) {
		r = routescan(area->asbrtab.ptr[NEXT], id);
		if (ptype == PTYPE_INTRA)
		    return r;
		else
		    break;
	    }
	    AREA_LIST(a) {
		if ((r = routescan(a->asbrtab.ptr[NEXT], id)))
		    return r;
	    } AREA_LIST_END(a) ;
	    break;

	case DTYPE_ABR:
	    return routescan(area->abrtab.ptr[NEXT], id);

	default:
	    return (struct OSPF_ROUTE *) 0;
	}
    }

    if (ptype & PTYPE_INTER) {
	/* search inter area routing tables */
	return routescan(ospf.sum_asb_rtab.ptr[NEXT], id);
    }

    return (struct OSPF_ROUTE *) 0;
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
