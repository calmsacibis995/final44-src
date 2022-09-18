/*
 * $Id: rip_mib.c,v 1.9.2.1 1994/07/12 20:29:47 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_ISODE_SNMP
#include "include.h"

#if	defined(PROTO_RIP) && defined(PROTO_SNMP)
#include "inet.h"
#include "rip.h"
#include "snmp_isode.h"


PROTOTYPE(o_rip,
	  static int,
	  (OI,
	   struct type_SNMP_VarBind *,
	   int));
PROTOTYPE(o_rip_ifstat,
	  static int,
	  (OI,
	   struct type_SNMP_VarBind *,
	   int));
PROTOTYPE(o_rip_ifconf,
	  static int,
	  (OI,
	   struct type_SNMP_VarBind *,
	   int));
PROTOTYPE(o_rip_peer,
	  static int,
	  (OI,
	   struct type_SNMP_VarBind *,
	   int));

#define	DOMAIN_LENGTH	2

static struct object_table rip_objects[] = {
#define	Irip2GlobalRouteChanges		0
#define	Irip2GlobalQueries		1
    OTE(rip2GlobalRouteChanges, o_rip, NULL),
    OTE(rip2GlobalQueries, o_rip, NULL),

#define	Irip2IfStatAddress		2
#define	Irip2IfStatRcvBadPackets	3
#define	Irip2IfStatRcvBadRoutes		4
#define	Irip2IfStatSentUpdates		5
#define	Irip2IfStatStatus		6
    OTE(rip2IfStatAddress, o_rip_ifstat, NULL),
    OTE(rip2IfStatRcvBadPackets, o_rip_ifstat, NULL),
    OTE(rip2IfStatRcvBadRoutes, o_rip_ifstat, NULL),
    OTE(rip2IfStatSentUpdates, o_rip_ifstat, NULL),
    OTE(rip2IfStatStatus, o_rip_ifstat, NULL),
#define	STATUS_Valid		1
#define	STATUS_Invalid		2

#define	Irip2IfConfAddress		7
#define	Irip2IfConfDomain		8
#define	Irip2IfConfAuthType		9
#define	Irip2IfConfAuthKey		10
#define	Irip2IfConfSend			11
#define	Irip2IfConfReceive		12
#define	Irip2IfConfDefaultMetric	13
#define	Irip2IfConfStatus		14
    OTE(rip2IfConfAddress, o_rip_ifconf, NULL),
    OTE(rip2IfConfDomain, o_rip_ifconf, NULL),
    OTE(rip2IfConfAuthType, o_rip_ifconf, NULL),
#define	AUTHTYPE_NoAuthentication	1
#define	AUTHTYPE_SimplePassword		2
    OTE(rip2IfConfAuthKey, o_rip_ifconf, NULL),
    OTE(rip2IfConfSend, o_rip_ifconf, NULL),
#define	SEND_DoNotSend		1
#define	SEND_RipVersion1	2
#define	SEND_Rip1Compatible	3
#define	SEND_RipVersion2	4    
    OTE(rip2IfConfReceive, o_rip_ifconf, NULL),
#define	RECEIVE_Rip1	1
#define	RECEIVE_Rip2	2
#define	RECEIVE_Rip1OrRip2	3    
    OTE(rip2IfConfDefaultMetric, o_rip_ifconf, NULL),
    OTE(rip2IfConfStatus, o_rip_ifconf, NULL),

#define	Irip2PeerAddress	15
#define	Irip2PeerDomain		16
#define	Irip2PeerLastUpdate	17
#define	Irip2PeerVersion	18
#define	Irip2PeerRcvBadPackets	19
#define	Irip2PeerRcvBadRoutes	20
    OTE(rip2PeerAddress, o_rip_peer, NULL),
    OTE(rip2PeerDomain, o_rip_peer, NULL),
    OTE(rip2PeerLastUpdate, o_rip_peer, NULL),
    OTE(rip2PeerVersion, o_rip_peer, NULL),
    OTE(rip2PeerRcvBadPackets, o_rip_peer, NULL),
    OTE(rip2PeerRcvBadRoutes, o_rip_peer, NULL),

    { NULL }
};


static struct snmp_tree rip_mib_tree = {
    NULL, NULL,
    "rip2",
    NULLOID,
    readWrite,
    rip_objects,
    0
};


static int
o_rip __PF3(oi, OI,
	    v, register struct type_SNMP_VarBind *,
	    offset, int)
{
    register OID    oid = oi->oi_name;
    register OT	    ot = oi->oi_type;

    switch (offset) {
    case type_SNMP_SMUX__PDUs_get__request:
	if (oid->oid_nelem != ot->ot_name->oid_nelem + 1
	    || oid->oid_elements[oid->oid_nelem - 1]) {
	    return int_SNMP_error__status_noSuchName;
	}
	break;

    case type_SNMP_SMUX__PDUs_get__next__request:
	if (oid->oid_nelem == ot->ot_name->oid_nelem) {
	    OID new;

	    if ((new = oid_extend(oid, 1)) == NULLOID) {
		return int_SNMP_error__status_genErr;
	    }
	    new->oid_elements[new->oid_nelem - 1] = 0;

	    if (v->name) {
		free_SNMP_ObjectName(v->name);
	    }
	    v->name = new;
	} else {
	    return NOTOK;
	}
	break;

    default:
	return int_SNMP_error__status_genErr;
    }

    switch (ot2object(ot)->ot_info) {
    case Irip2GlobalRouteChanges:
	return o_integer(oi, v, rip_global_changes);

    case Irip2GlobalQueries:
	return o_integer(oi, v, rip_global_responses);
    }

    return int_SNMP_error__status_noSuchName;
}

/**/


static int
o_rip_ifstat __PF3(oi, OI,
		  v, register struct type_SNMP_VarBind *,
		  offset, int)
{
    register int    i;
    register unsigned int *ip,
			  *jp;
    register OID    oid = oi->oi_name;
    register OT	    ot = oi->oi_type;
    OID		    new;

    switch (ot2object(ot)->ot_info) {
    case Irip2IfStatAddress:
	return o_ipaddr(oi,
			v,
			sock2unix((sockaddr_un *) 0,
				  (int *) 0));

    case Irip2IfStatRcvBadPackets:
	return o_integer(oi, v, 0);

    case Irip2IfStatRcvBadRoutes:
	return o_integer(oi, v, 0);

    case Irip2IfStatSentUpdates:
	return o_integer(oi, v, 0);

    case Irip2IfStatStatus:
	return o_integer(oi, v, STATUS_Valid);
    }

    return int_SNMP_error__status_noSuchName;
}

/**/


static int
o_rip_ifconf __PF3(oi, OI,
		  v, register struct type_SNMP_VarBind *,
		  offset, int)
{
    register int    i;
    register unsigned int *ip,
			  *jp;
    as_t domain = 0;
    register OID    oid = oi->oi_name;
    register OT	    ot = oi->oi_type;
    OID		    new;

    switch (ot2object(ot)->ot_info) {
    case Irip2IfConfAddress:
	return o_ipaddr(oi,
			v,
			sock2unix((sockaddr_un *) 0,
				  (int *) 0));

    case Irip2IfConfDomain:
	return o_string(oi, v, &domain, DOMAIN_LENGTH);

    case Irip2IfConfAuthType:
	return o_integer(oi, v, 0);

    case Irip2IfConfAuthKey:
	return o_string(oi, v, (caddr_t) 0, 0);

    case Irip2IfConfSend:
	return o_integer(oi, v, 0);

    case Irip2IfConfReceive:
	return o_integer(oi, v, RECEIVE_Rip1OrRip2);

    case Irip2IfConfDefaultMetric:
	return o_integer(oi, v, 0);

    case Irip2IfConfStatus:
	return o_integer(oi, v, STATUS_Valid);
    }

    return int_SNMP_error__status_noSuchName;
}

/**/


static gw_entry *
o_rip_get_peer __PF3(ip, register unsigned int *,
		     len, u_int,
		     isnext, int)
{
    static gw_entry *last_gwp;
    static unsigned int *last;
    static int last_quantum;

    if (last_quantum != snmp_quantum) {
	last_quantum = snmp_quantum;

	if (last) {
	    task_mem_free((task *) 0, (caddr_t) last);
	    last = (unsigned int *) 0;
	}
    }

    if (snmp_last_match(&last, ip, len, isnext)) {
	return last_gwp;
    }

#ifdef	notdef
    if (len) {
	u_int32 bnp_addr;
	register gw_entry *p;

	oid2ipaddr(ip, &bnp_addr);

	GNTOHL(bnp_addr);

	if (isnext) {
	    register gw_entry *new = (gw_entry *) 0;
	    register u_int32 new_addr = 0;

	    BGP_SORT_LIST(p) {
		register u_int32 cur_addr = ntohl(sock2ip(p->bgp_addr));

		if (cur_addr > bnp_addr &&
		    (!new || cur_addr < new_addr)) {
		    new = p;
		    new_addr = cur_addr;
		}
	    } BGP_SORT_LIST_END(p) ;

	    last_bnp = new;
	} else {
	    last_bnp = (bgpPeer *) 0;
	    

	    BGP_SORT_LIST(p) {
		register u_int32 cur_addr = ntohl(sock2ip(p->bgp_addr));
		
		if (cur_addr == bnp_addr) {
		    last_bnp = p;
		    break;
		} else if (cur_addr > bnp_addr) {
		    break;
		}
	    } BGP_SORT_LIST_END(p) ;
	}
    } else {
	last_bnp = bgp_n_peers ? bgp_sort_list : (bgpPeer *) 0;
    }
#endif	/* notdef */

    return last_gwp;
}


static int
o_rip_peer __PF3(oi, OI,
		  v, register struct type_SNMP_VarBind *,
		  offset, int)
{
    register int    i;
    register unsigned int *ip,
			  *jp;
    gw_entry *gwp;
    as_t domain = 0;
    register OID    oid = oi->oi_name;
    register OT	    ot = oi->oi_type;
    OID		    new;

    /* INDEX { rip2PeerAddress rip2PeerDomain } */
#define	NDX_SIZE	(sizeof (struct in_addr) + 2)

    switch (offset) {
    case type_SNMP_SMUX__PDUs_get__request:
	if (oid->oid_nelem != ot->ot_name->oid_nelem + NDX_SIZE) {
		return int_SNMP_error__status_noSuchName;
	    }
	gwp = o_rip_get_peer(oid->oid_elements + oid->oid_nelem - NDX_SIZE,
			     NDX_SIZE,
			     0);
	if (!gwp) {
	    return int_SNMP_error__status_noSuchName;
	}
	break;

    case type_SNMP_SMUX__PDUs_get__next__request:
	/* next request with incomplete instance? */
	if ((i = oid->oid_nelem - ot->ot_name->oid_nelem) != 0 && i < NDX_SIZE) {
	    for (jp = (ip = oid->oid_elements + 
		       ot->ot_name->oid_nelem - 1) + i;
		 jp > ip;
		 jp--) {
		if (*jp != 0) {
		    break;
		}
	    }
	    if (jp == ip) {
		oid->oid_nelem = ot->ot_name->oid_nelem;
	    } else {
		if ((new = oid_normalize(oid, NDX_SIZE - i, 256)) == NULLOID) {
			return NOTOK;
		    }
		if (v->name) {
		    free_SNMP_ObjectName(v->name);
		}
		v->name = oid = new;
	    }
	}

	/* next request with no instance? */
	if (oid->oid_nelem == ot->ot_name->oid_nelem) {
	    gwp = o_rip_get_peer((unsigned int *) 0,
				 0,
				 TRUE);
	    if (!gwp) {
		return NOTOK;
	    }

	    if ((new = oid_extend(oid, NDX_SIZE)) == NULLOID) {
		return int_SNMP_error__status_genErr;
	    }

	    ip = new->oid_elements + new->oid_nelem - NDX_SIZE;
	    STR_OID(ip, &sock2ip(gwp->gw_addr), sizeof (sock2ip(gwp->gw_addr)));
	    STR_OID(ip, &domain, DOMAIN_LENGTH);
		
	    if (v->name) {
		free_SNMP_ObjectName(v->name);
	    }
	    v->name = new;
	} else {
	    int j;

	    gwp = o_rip_get_peer(ip = oid->oid_elements + ot->ot_name->oid_nelem,
				 (u_int) (j = oid->oid_nelem - ot->ot_name->oid_nelem),
				 TRUE);
	    if (!gwp) {
		return NOTOK;
	    }

	    if ((i = j - NDX_SIZE) < 0) {
		if ((new = oid_extend(oid, -i)) == NULLOID) {
		    return int_SNMP_error__status_genErr;
		}
		if (v->name) {
		    free_SNMP_ObjectName(v->name);
		}
		v->name = oid = new;
	    } else if (i > 0) {
		oid->oid_nelem -= i;
	    }
		
	    ip = oid->oid_elements + ot->ot_name->oid_nelem;
	    STR_OID(ip, &sock2ip(gwp->gw_addr), sizeof (sock2ip(gwp->gw_addr)));
	    STR_OID(ip, &domain, DOMAIN_LENGTH);
	}
	break;

    default:
	return int_SNMP_error__status_genErr;
    }
#undef	NDX_SIZE

    switch (ot2object(ot)->ot_info) {
    case Irip2PeerAddress:
	return o_ipaddr(oi,
			v,
			sock2unix((sockaddr_un *) 0,
				  (int *) 0));

    case Irip2PeerDomain:
	return o_string(oi, v, &domain, DOMAIN_LENGTH);

    case Irip2PeerLastUpdate:
	return o_integer(oi, v, 0);

    case Irip2PeerVersion:
	return o_integer(oi, v, 0);

    case Irip2PeerRcvBadPackets:
	return o_integer(oi, v, 0);

    case Irip2PeerRcvBadRoutes:
	return o_integer(oi, v, 0);
    }

    return int_SNMP_error__status_noSuchName;
}

/**/
void
rip_init_mib __PF1(enabled, int)
{
    if (enabled) {
	snmp_tree_register(&rip_mib_tree);
    } else {
	snmp_tree_unregister(&rip_mib_tree);
    }
}

#endif	/* defined(PROTO_RIP) && defined(PROTO_SNMP) */


/*
 * %(Copyright)
 */
