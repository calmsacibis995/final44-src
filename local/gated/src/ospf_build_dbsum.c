/*
 * $Id: ospf_build_dbsum.c,v 1.13.2.4 1994/08/15 21:18:03 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"

/*
 * dbsum_alloc() - allocate a link up whose data portion is a db_hdr
 *			called by build_dbsum
 */
void
dbsum_free __PF1(ds, struct LSDB_SUM *)
{
    if (ds->dbpkt) {
	task_mem_free(ospf.task, (void_t) ds->dbpkt);
    }
    task_block_free(ospf_dbsum_index, (void_t) ds);
}


struct LSDB_SUM *
dbsum_alloc __PF2(intf, struct INTF *,
		  len, size_t)
{
    struct LSDB_SUM *ds = (struct LSDB_SUM *) task_block_alloc(ospf_dbsum_index);

    ds->dbpkt = (struct OSPF_HDR *) task_mem_calloc(ospf.task,
						    1,
						    len + OSPF_TRL_SIZE(intf));

    return ds;
}


/*
 * build_dbsum - build dbsum packets which includes the lsdb for this rtr
 *			put packets on the nbrs dbsum list
 *	       - called by RxDbDescr going into next state
 */
int
build_dbsum __PF2(intf, struct INTF *,
		  nbr, struct NBR *)
{
    struct DB_HDR *dbh;
    struct LS_HDR *dbp;
    struct AREA *a = intf->area;
    struct LSDB_SUM *ds = LSDB_SUM_NULL;
    struct LSDB_SUM *lastds = LSDB_SUM_NULL;
    int len = OSPF_HDR_SIZE + DB_HDR_SIZE;
    int type;
    size_t intf_mtu = INTF_MTU(intf);
    int hi_type = LS_ASE;

    if (BIT_TEST(a->area_flags, OSPF_AREAF_STUB) ||
	intf->type == VIRTUAL_LINK) {
	/* Don't include LS_ASE if stub area also it's a bozo no-no to send LS_ASE over virtual links */
	hi_type = LS_SUM_ASB;
    }

    freeDbSum(nbr);		/* summary of area db */
    freeLsReq(nbr);		/* request list for this nbr */

    ds = (struct LSDB_SUM *) dbsum_alloc(intf, intf_mtu);
    if (ds == LSDB_SUM_NULL)
	return FLAG_NO_BUFS;
    dbh = &ds->dbpkt->ospfh_un.database;
    dbp = &dbh->dbp;
    nbr->dbsum = ds;

    /* grab all of the links */
    for (type = LS_RTR; type <= hi_type; type++) {
	register struct LSDB_HEAD *hp;
	
	LSDB_HEAD_LIST(a->htbl[type], hp, 0, HTBLSIZE) {
	    register struct LSDB *e;

	    LSDB_LIST(hp, e) {
		if (ADV_AGE(e) >= MaxAge) {
		    add_nbr_retrans(nbr, e);
		    add_db_retrans(e, nbr);
		    continue;
		}
		if (len + DB_PIECE_SIZE >= intf_mtu) {
		    /* finish off this pkt */
		    /* assume more for now */
		    dbh->I_M_MS = bit_M;
		    ds->len = len;
		    lastds = ds;
		    /* alloc another */
		    lastds->next = (ds = dbsum_alloc(intf, intf_mtu));
		    if (ds == LSDB_SUM_NULL) {
			freeDbSum(nbr);
			REM_NBR_RETRANS(nbr);
			return FLAG_NO_BUFS;
		    }
		    len = OSPF_HDR_SIZE + DB_HDR_SIZE;
		    dbh = &ds->dbpkt->ospfh_un.database;
		    dbp = &dbh->dbp;
		}
		(*dbp) = DB_LS_HDR(e);
		dbp->ls_age = htons((ADV_AGE(e)));
		len += DB_PIECE_SIZE;
		nbr->dbcnt++;
		ds->cnt++;
		dbp++;
	    } LSDB_LIST_END(hp, e) ;
	} LSDB_HEAD_LIST_END(a->htbl[type], hp, 0, HTBLSIZE) ;
    }

    /* slave transitions first so master is first to have M bit off */
    if (len == OSPF_HDR_SIZE + DB_HDR_SIZE) {	/* check for empty pkt */
	/* will always have at one sum with least this rtrs lsa in pkt */
	if (ds == nbr->dbsum)
	    nbr->dbsum = LSDB_SUM_NULL;
	dbsum_free(ds);
	if (lastds) {
	    lastds->next = LSDB_SUM_NULL;
	    /* turn off more */
	    lastds->dbpkt->ospfh_un.database.I_M_MS = 0;
	}
    } else {
	/* leave on more bit if MASTER */
	if (nbr->mode == SLAVE)
	    ds->dbpkt->ospfh_un.database.I_M_MS = 0;	/* turn off more */
	ds->next = LSDB_SUM_NULL;
	ds->len = len;
    }

    return FLAG_NO_PROBLEM;		/* BufChecks went OK */
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
