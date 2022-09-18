/*
 * $Id: ospf_lsdb.c,v 1.17.2.4 1994/09/15 21:38:05 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"

/*
 * 		Link State Db stuff
 */


/*
 * addLSA 		Add lsa to the linked list
 */
int
addLSA __PF5(db, struct LSDB **,
	     area, struct AREA *,
	     ls_id, u_int32,
	     key1, u_int32,
	     type, u_int)
{
    int hash = XHASH(ls_id, ls_id);
    struct LSDB_HEAD *hp = &area->htbl[type][hash];
    register struct LSDB **e;

    assert(type <= LS_ASE);

    /* First key */
    for (e = &DBH_LIST(hp); *e; e = &(*e)->lsdb_next) {
	if (ls_id == LS_ID(*e)) {
	    if (type == LS_NET || type == LS_RTR) {
		/* Just one key for these types */
		*db = *e;
		return TRUE;
	    }

	    /* Second key */
	    for (; *e && ls_id == LS_ID(*e); e = &(*e)->lsdb_next) {
		if (key1 == ADV_RTR(*e)) {
		    /* Found it */
		    *db = *e;
		    return TRUE;
		} else if (key1 > ADV_RTR(*e)) {
		    /* Install here */

		    break;
		}
	    }
	    break;
	} else if (ls_id > LS_ID(*e)) {
	    /* Install here */

	    break;
	}
    }

    *db = (struct LSDB *) task_block_alloc(ospf_lsdb_index);
    if (!(*db))
	return FALSE;
    (*db)->lsdb_next = *e;
    *e = *db;
    DB_FREEME(*db) = FALSE;
    (*db)->lsdb_dist = (type < LS_SUM_NET) ? RTRLSInfinity : SUMLSInfinity;
    (*db)->lsdb_hash = hash;
    (*db)->lsdb_area = area;

    switch(type) {
    case LS_STUB:
	assert(FALSE);
	break;

    case LS_RTR:
    case LS_NET:
    case LS_SUM_NET:
    case LS_SUM_ASB:
	ospf.db_cnt++;
	area->db_cnts[type]++;
	area->db_int_cnt++;
	break;

    case LS_ASE:
	ospf.db_cnt++;
	ospf.db_ase_cnt++;
	break;
    }

    /* 
     * successful add, not found 
     */
    return FALSE;
}


/*
 * findLSA 		Add sum lsa or ase lsa to the linked list
 */
struct LSDB *
findLSA __PF4(hp, struct LSDB_HEAD *,
	      ls_id, u_int32,
	      key1, u_int32,
	      type, u_int)
{
    register struct LSDB *e;

    assert(type <= LS_ASE);

    LSDB_LIST(hp, e) {
	if (ls_id == LS_ID(e)) {
	    if (type == LS_NET || type == LS_RTR) {
		/* These types use only one key */

		return e;
	    }
	    
	    for (; e && ls_id == LS_ID(e); e = e->lsdb_next) {
		if (key1 == ADV_RTR(e)) {
		    /* Found the one we are looking for */

		    return e;
		} else if (key1 > ADV_RTR(e)) {
		    /* Does not exist */
		    
		    break;
		}
	    }

	    /* Can not find the second key */

	    break;
	} else if (ls_id > LS_ID(e)) {
	    /* Can not find the first key */

	    break;
	}
    } LSDB_LIST_END(hp, e) ;

    return (struct LSDB *)  0;
}


/*
 *	Add a stub network lsa
 */
int
ospf_add_stub_lsa __PF5(db, struct LSDB **,
			area, struct AREA *,
			net, u_int32,
			advrtr, u_int32,
			mask, u_int32)
{
    struct LSDB **e;
    int hash = XHASH(advrtr, advrtr);
    struct LSDB_HEAD *hp = &area->htbl[LS_STUB][hash];

    for (e = &DBH_LIST(hp); *e; e = &(*e)->lsdb_next) {
	if (advrtr > ADV_RTR(*e)) {
	    /* Insert here */

	    break;
	} else if (advrtr == ADV_RTR(*e)
		   && net == DB_NETNUM(*e)) {
	    if (mask == DB_MASK(*e)) {
		*db = *e;
		return TRUE;
	    }
	} 
    }
    
    *db = (struct LSDB *) task_block_alloc(ospf_lsdb_index);
    if (!(*db)) {
	return FALSE;
    }
    (*db)->lsdb_next = *e;
    *e = *db;
    DB_RTR(*db) = (struct RTR_LA_HDR *) 0;
    DB_FREEME(*db) = FALSE;
    (*db)->lsdb_dist = RTRLSInfinity;
    (*db)->lsdb_hash = hash;
    (*db)->lsdb_area = area;

    area->db_cnts[LS_STUB]++;

    /* 
     * successful add, not found 
     */
    return FALSE;
}


/**/

/*
 * free a db entry
 *	- called by RxLsAck, RxLinkUp or tq_dbage
 *	- spf will have just been run so parent list and routes will have
 * 	  been freed
 *	- leave entry around db age will free the rest for
 *	  LS_ASE and LS_SUM_NET else since most other entries may be back
 *	  just free structure
 */
void
db_free __PF2(db, struct LSDB *, 
	      type, int)
{
    struct AREA *area = db->lsdb_area;
    u_int16 chksum;
    struct LSDB_HEAD *hp = (struct LSDB_HEAD *) 0;
    register struct LSDB *sp;

    if (DB_RTR(db)) {
	if (TRACE_TF(ospf.trace_options, TR_OSPF_LSA_BLD)) {
	    ospf_trace_build(area, area, db->lsdb_adv, TRUE);
	}
	type = LS_TYPE(db);
	chksum = LS_CKS(db);
	DBADV_FREE(db);
    } else {
	assert(type);
	chksum = 0;
    }

    switch(type) {
    case LS_STUB:
	area->db_cnts[LS_STUB]--;
	hp = &area->htbl[type][db->lsdb_hash];
	break;

    case LS_RTR:
    case LS_NET:
    case LS_SUM_NET:
    case LS_SUM_ASB:
	ospf.db_cnt--;
	area->db_cnts[type]--;
	area->db_int_cnt--;
	area->db_chksumsum -= chksum;
	hp = &area->htbl[type][db->lsdb_hash];
	break;

    case LS_ASE:
	ospf.db_cnt--;
	ospf.db_ase_cnt--;
	ospf.db_chksumsum -= chksum;
	hp = &ospf.ase[db->lsdb_hash];
	break;

    default:
	assert(FALSE);
    }

    /* Remove from LSDB */
    LSDB_LIST(hp, sp) {
	if (sp == db) {
	    LSDB_LIST_DELETE(hp, db);
	}
    } LSDB_LIST_END(hp, sp);

    ospf_nh_free_list(db->lsdb_nhcnt, db->lsdb_nh);

    DB_REMQUE(db);

    task_block_free(ospf_lsdb_index, (void_t) db);
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
