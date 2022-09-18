/*
 * $Id: ospf_conf.c,v 1.27.2.7 1995/01/23 12:40:34 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"

/*
 * Add a net to an area
 *   - nets are used to build summary links
 *   - calling routine has checked for duplicates
 */
void
ospf_parse_add_net __PF4(a, struct AREA *,
			 net, sockaddr_un *,
			 mask, sockaddr_un *,
			 status, u_int)
{
    struct NET_RANGE *range;

    a->nrcnt++;
    range = (struct NET_RANGE *) task_block_alloc(ospf_netrange_index);
    range->net = sock2ip(net);
    range->mask = sock2ip(mask);
    range->status = status;
    range_enq(a, range);
}


/*
 * Add host to be advertised by this router
 */
void
ospf_parse_add_host __PF3(a, struct AREA *,
			  if_address, u_int32,	/* XXX - Why not ifap or intf? */
			  cost, metric_t)
{
    struct OSPF_HOSTS *newhost;

    a->hostcnt++;
    newhost = (struct OSPF_HOSTS *) task_block_alloc(ospf_hosts_index);
    newhost->host_if_addr = if_address;
    newhost->host_cost = cost;
    host_enq(a,newhost);
}


/*
 * Allocate a new area
 */
struct AREA *
ospf_parse_area_alloc __PF2(area_id, u_int32,
			    parse_error, char *)
{
    int i;
    struct AREA *area;

    if (area_id == OSPF_BACKBONE) {
	/* This is the backbone, put it at the head of the list */

	area = &ospf.backbone;
	INSQUE(area, &ospf.area);
    } else {
	/* Not the backbone.  Put on list in area order */

	AREA_LIST(area) {
	    if (area_id == area->area_id) {
		/* Duplicate area */

		sprintf(parse_error, "duplicate area");
		return (struct AREA *) 0;
	    } else if (area_id < area->area_id) {
		/* Insert here before this element */

		break;
	    }
	} AREA_LIST_END(area) ;

	INSQUE(task_block_alloc(ospf_area_index), area->area_back);
	area = area->area_back;
    }
    ospf.acnt++;

    /* Init interface list */
    area->intf.intf_forw = area->intf.intf_back = &area->intf;
    
    /* How to check for 0 but invalid id? */
    area->area_id = area_id;

    /* set up hash table for lsdb */
    for(i = LS_STUB; i < LS_ASE; i++) {
	area->htbl[i] = area->htbls[i];
    }

    /* set ase to global */
    area->htbl[LS_ASE] = ospf.ase;

    /* Init all the lists */
    DB_INITQ(area->spf);
    DB_INITQ(area->candidates);
    DB_INITQ(area->asblst);
    DB_INITQ(area->sumnetlst);
    DB_INITQ(area->interlst);

    return area;
}


int
ospf_parse_area_check  __PF2(a, struct AREA *,
			     parse_error, char *)
{
    if (a->area_id) {
	/* Not the backbone */

	if (!a->intf_policy) {
	    sprintf(parse_error, "no interfaces for area %A",
		    sockbuild_in(0, a->area_id));

	    return TRUE;
	}	
    } else {
	/* The backbone */

	if (!a->intf_policy && !ospf.vcnt) {
	    sprintf(parse_error, "no interfaces for backbone area");

	    return TRUE;
	}
    }

    return FALSE;
}


#ifdef	notyet
/*
 *  Create a non-virtual interface
 */
struct INTF *
ospf_intf_create __PF3(a, struct AREA *,
		       ifap, if_addr *,
		       ifcp, ospf_intf_conf *)
{
    int i;
    struct INTF *intf;
	 
    /* Check for duplicate interface */
    INTF_LIST(intf, a) {
	if (intf->ifap == ifap) {
	    sprintf(parse_error, "Duplicate interface specified");
	    return (struct INTF *) 0;
	}
    } INTF_LIST_END(intf, a) ;

    intf = (struct INTF *) task_block_alloc(ospf_intf_index);
    INSQUE(intf, a->intf.intf_back);
    a->ifcnt++;

    IFA_ALLOC(intf->ifap = ifap);
    intf->area = a;
    intf->type = type;
    intf->state = IDOWN;
    intf->transdly = OSPF_DFLT_TRANSDLY;
    intf->pri = 0;
    intf->retrans_timer = OSPF_DFT_RETRANS;
    intf->cost = OSPF_DFLT_COST;
    BIT_SET(intf->flags, OSPF_INTFF_ENABLE);

#ifdef	IP_MULTICAST
    if (BIT_TEST(intf->ifap->ifa_state, IFS_MULTICAST)) {
	/* Assume we want multicast */
	BIT_SET(intf->flags, OSPF_INTFF_MULTICAST);
    }
#endif	/* IP_MULTICAST */

    switch (BIT_TEST(ifcp->ifc_flags, OSPF_IFC_P2P|OSPF_IFC_BROADCAST|OSPF_IFC_NBMA)) {
#ifdef	IP_MULTICAST
    case OSPF_IFC_BROADCAST:
	intf->type = BROADCAST;
	intf->hello_timer = BIT_TEST(ifpc->ifc_flags, OSPF_IFC_HELLO) ? ifpc->ifc_hello : OSPF_BC_DFLT_HELLO;
	goto common;

#endif	/* IP_MULTICAST */
    case OSPF_IFC_NBMA:
	inff->type = NONBROADCAST;
	if (BIT_TEST(ifap->ifa_state, IFS_BROADCAST)) {
	    intf->poll_timer = OSPF_DFLT_POLL_INT;
	    intf->hello_timer = OSPF_BC_DFLT_HELLO;
	} else {
	    intf->poll_timer = OSPF_DFLT_POLL_INT;		/* XXX - different default? */
	    intf->hello_timer = OSPF_NBMA_DFLT_HELLO;
	}
	intf->pollmod = 1;
#ifdef	IP_MULTICAST
	BIT_RESET(intf->flags, OSPF_INTFF_MULTICAST);
	/* Fall through */

    common:
#endif	/* IP_MULTICAST */
	/* Common to broadcast and nbma */
	intf->nbr.nbr_id = sockdup(ospf.router_id);
	intf->nbr.nbr_addr = sockdup(intf->ifap->ifa_addr);
	intf->nbr.pri = intf->pri;
	intf->nbr.state = N2WAY;
	intf->dead_timer = intf->hello_timer * 4;
	break;

    case OSPF_IFC_P2P:
	intf->type = POINT_TO_POINT;
	intf->hello_timer = OSPF_PTP_DFLT_HELLO;
	intf->dead_timer = intf->hello_timer * 4;
	intf->nbr.nbr_addr = sockdup(intf->ifap->ifa_addr);
	IFA_ALLOC(intf->nbr.ifap = ifap);
	break;
    }
    ospf.nintf++;

    return intf;
}
#endif	/* notyet */


/*
 * Alloc an non-virtual interface and set default values
 */
struct INTF *
ospf_parse_intf_alloc __PF3(a, struct AREA *,
			    type, int,
			    ifap, if_addr *)
{
    struct INTF *intf;
	 
    intf = (struct INTF *) task_block_alloc(ospf_intf_index);
    INSQUE(intf, a->intf.intf_back);
    a->ifcnt++;

    IFA_ALLOC(intf->ifap = ifap);
    intf->area = a;
    intf->type = type;
    intf->state = IDOWN;
    intf->transdly = OSPF_DFLT_TRANSDLY;
    intf->pri = 0;
    intf->retrans_timer = OSPF_DFT_RETRANS;
    intf->cost = OSPF_DFLT_COST;
    BIT_SET(intf->flags, OSPF_INTFF_ENABLE);
    if (BIT_TEST(intf->ifap->ifa_state, IFS_MULTICAST)) {
	/* Assume we want multicast */
	BIT_SET(intf->flags, OSPF_INTFF_MULTICAST);
    }

    switch (type) {
    case BROADCAST:
	intf->hello_timer = OSPF_BC_DFLT_HELLO;
	goto common;

    case NONBROADCAST:
	if (BIT_TEST(ifap->ifa_state, IFS_BROADCAST)) {
	    intf->poll_timer = OSPF_DFLT_POLL_INT;
	    intf->hello_timer = OSPF_BC_DFLT_HELLO;
	} else {
	    intf->poll_timer = OSPF_DFLT_POLL_INT;		/* XXX - different default? */
	    intf->hello_timer = OSPF_NBMA_DFLT_HELLO;
	}
	intf->pollmod = 1;
	BIT_RESET(intf->flags, OSPF_INTFF_MULTICAST);
	/* Fall through */

    common:
	/* Common to broadcast and nbma */
	intf->nbr.nbr_id = sockdup(ospf.router_id);
	intf->nbr.nbr_addr = sockdup(intf->ifap->ifa_addr);
	intf->nbr.pri = intf->pri;
	intf->nbr.state = N2WAY;
	intf->dead_timer = intf->hello_timer * 4;
	break;

    case POINT_TO_POINT:
	intf->hello_timer = OSPF_PTP_DFLT_HELLO;
	intf->dead_timer = intf->hello_timer * 4;
	intf->nbr.nbr_addr = sockdup(intf->ifap->ifa_addr);
#ifdef	notdef
	IFA_ALLOC(intf->nbr.ifap = ifap);
#endif	/* notdef */
	intf->nbr.intf = intf;
	break;
    }
    ospf.nintf++;

    return intf;
}


/*
 * virtual link allocate and set default metrics
 */
struct INTF *
ospf_parse_virt_parse __PF5(a, struct AREA *,
			    addr, sockaddr_un *,
			    trans_area_id, u_int32,
			    list, config_list *,
			    parse_error, char *)
{
    struct INTF *intf;

    /* Check address */
    if (socktype(addr) != AF_INET) {
	sprintf(parse_error, "neighbor-id must be an IP address");
	return (struct INTF *) 0;
    }

    /* Check area */
    if (a->area_id != OSPF_BACKBONE) {
	sprintf(parse_error, "virtual links only allowed in `backbone' area");
	return (struct INTF *) 0;
    }

    /* Check transit area */
    if (trans_area_id == OSPF_BACKBONE) {
	sprintf(parse_error, "transit-area can not be the `backbone' area");
	return (struct INTF *) 0;
    }

    /* Allocate the interface */
    intf = (struct INTF *) task_block_alloc(ospf_intf_index);
    INSQUE(intf, ospf.vl.intf_back);
    ospf.vcnt++;

    intf->area = a;
    intf->hello_timer = OSPF_VIRT_DFLT_HELLO;
    intf->dead_timer = intf->hello_timer * 4;
    intf->type = VIRTUAL_LINK;
    intf->state = IDOWN;
    intf->transdly = OSPF_VIRT_DFLT_TRANSDLY;
    intf->pri = 0;
    intf->retrans_timer = OSPF_VIRT_DFT_RETRANS;
    intf->nbr.nbr_id = addr;
    intf->trans_area_id = trans_area_id;
    intf->auth.auth_type = a->authtype;

    if (list && list->conflist_list) {
	register config_entry *cp;

	CONFIG_LIST(cp, list->conflist_list) {

	    switch (cp->config_type) {
	    case OSPF_CONFIG_ENABLE:
		if ((int) GA2S(cp->config_data)) {
		    BIT_SET(intf->flags, OSPF_INTFF_ENABLE);
		} else {
		    BIT_RESET(intf->flags, OSPF_INTFF_ENABLE);
		}
		break;
		    
	    case OSPF_CONFIG_RETRANSMIT:
		intf->retrans_timer = (time_t) GA2S(cp->config_data);
		break;

	    case OSPF_CONFIG_TRANSIT:
		intf->transdly = (time_t) GA2S(cp->config_data);
		break;

	    case OSPF_CONFIG_PRIORITY:
		trace_log_tf(ospf.trace_options,
			     0,
			     LOG_INFO,
			     ("ospf_parse_virt_parse: priority option ignored for virtual link to %A",
			      addr));
		break;

	    case OSPF_CONFIG_HELLO:
		intf->hello_timer = (time_t) GA2S(cp->config_data);
		break;
		    
	    case OSPF_CONFIG_ROUTERDEAD:
		intf->dead_timer = (time_t) GA2S(cp->config_data);
		break;

	    case OSPF_CONFIG_AUTH:
		bcopy((caddr_t) cp->config_data, (caddr_t) &intf->auth, sizeof (ospf_auth));
		break;

	    case OSPF_CONFIG_AUTH2:
		bcopy((caddr_t) cp->config_data, (caddr_t) &intf->auth2, sizeof (ospf_auth));
		BIT_SET(intf->flags, OSPF_INTFF_SECAUTH);
		break;

	    default:
		assert(FALSE);

	    }
	} CONFIG_LIST_END(cp, list->conflist_list) ;
    }

    return intf;
}


void
ospf_parse_intf_check __PF1(intf, struct INTF *)
{
    /* if wait and dead tmr aren't set default to 4 times hello tmr */
    if (intf->dead_timer == 0)
	intf->dead_timer = intf->hello_timer * 4;
}


/*
 * Check configuration for valid params
 */
int
ospf_parse_valid_check __PF1(parse_error, char *)
{

    /* recheck configuration */
    if (!ospf.acnt) {
	sprintf(parse_error, "ospf_conf: No Areas defined");
	return TRUE;
    }

    if (ospf.acnt < 2 && ospf.vcnt) {
	sprintf(parse_error, "ospf_conf: virtual link configured < 2 areas");
	return TRUE;
    }
    
    if ((ospf.acnt > 2) && !(GOTBACKBONE)) {
	sprintf(parse_error, "ospf_conf: 2 or more areas have been defined: need to configure backbone ");
	return TRUE;
    }

    /* Resolve transit areas */
    if (ospf.vcnt) {
	struct INTF *intf;

	VINTF_LIST(intf) {
	    struct AREA *area;
	    u_int32 trans_area_id = intf->trans_area_id;

	    AREA_LIST(area) {
		if (area->area_id == trans_area_id) {
		    /* Found it */

		    BIT_SET(area->area_flags, OSPF_AREAF_TRANSIT);
		    intf->trans_area = area;
		    goto found_area;
		} else if (area->area_id > trans_area_id) {
		    /* No such luck */

		    area = (struct AREA *) 0;
		}
	    } AREA_LIST_END(area) ;

	    /* No area */
	    sprintf(parse_error, "could not find transit-area %A for virtual link to %A",
		    sockbuild_in(0, trans_area_id),
		    intf->nbr.nbr_id);
	    return TRUE;

	found_area: ;
	} VINTF_LIST_END(intf) ;
    }

    return FALSE;
}


ospf_config_router *
ospf_parse_router_alloc __PF2(router, struct in_addr,
			      priority, u_int)
{
    ospf_config_router *ocr = (ospf_config_router *) task_block_alloc(ospf_router_index);

    ocr->ocr_router = router;
    ocr->ocr_priority = priority;

    return ocr;
}


void
ospf_config_free __PF1(cp, config_entry *)
{
    switch (cp->config_type) {
    case OSPF_CONFIG_AUTH:
    case OSPF_CONFIG_AUTH2:
	task_block_free(ospf_auth_index, cp->config_data);
	break;
	
    case OSPF_CONFIG_ROUTERS:
        {
	    ospf_config_router *ocr = (ospf_config_router *) cp->config_data;

	    do {
		ospf_config_router *next = ocr->ocr_next;

		task_block_free(ospf_router_index, (void_t) ocr);

		ocr = next;
	    } while (ocr) ;
	}
	break;
	
    default:
	/* Not allocated */
	break;
    }
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
