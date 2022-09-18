/*
 * $Id: ospf_txpkt.c,v 1.23.2.8 1995/03/07 17:29:40 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"


void
send_hello __PF3(intf, struct INTF *,
		 nbrptr, struct NBR *,
		 goingdown, int) 
{
    struct OSPF_HDR *pkt = task_get_send_buffer(struct OSPF_HDR *);
    struct HELLO_HDR *hello = &pkt->ospfh_un.hello;
    u_int32 to = 0;
    struct NBR *nbr;
    struct RHF *rhf = &hello->rhf;
    struct AREA *area = intf->area;

#define	ADD_NBR(rhf, nbr) \
    do { \
	if ((nbr) && (nbr)->nbr_id) { \
	    ((rhf)++)->rtr = NBR_ID(nbr); \
	} \
    } while (0)

    if (intf->type == VIRTUAL_LINK) {
      hello->netmask = (u_int32) 0;
    } else {
      hello->netmask = INTF_MASK(intf);
    }
    hello->DeadInt = htonl((u_short) intf->dead_timer);
    hello->HelloInt = htons(intf->hello_timer);
    hello->rtr_priority = intf->pri;	/* if priority	 */
    hello->options = BIT_TEST(area->area_flags, OSPF_AREAF_STUB) ? 0 : OPT_E_bit;

    /* build rtrs heard from stuff  and dr and bdr only if not shutting down */
    if (!goingdown) {
	hello->dr = (intf->dr != NBRNULL) ? NBR_ADDR(intf->dr) : 0;
	hello->bdr = (intf->bdr != NBRNULL) ? NBR_ADDR(intf->bdr) : 0;
    }

    switch (intf->type) {
    case NONBROADCAST:
	if (nbrptr) {
	    /* If provided with a neighbor pointer, just send to that neighbor */

	    to = NBR_ADDR(nbrptr);
	    if (!goingdown) {
		ADD_NBR(rhf, nbrptr);
	    }
	    break;
	}

	/* Figure out which group to send to and include the smallest */
	/* subset of neighbors possible.  Ideally we would only */
	/* include the neighbor we are sending the packet to, but the */
	/* overhead of sending the packet is potentially too great */
	switch (intf->state) {

	case IDrOTHER:
	    to = DR_and_BDR;
	    if (!goingdown) {
		ADD_NBR(rhf, intf->dr);
		ADD_NBR(rhf, intf->bdr);
	    }
	    break;

	case IWAITING:
	    to = ALL_ELIG_NBRS;
	    if (!goingdown) {
		for (nbr = intf->nbr.next; nbr != NBRNULL; nbr = nbr->next) {
		    if (nbr->pri) {
			ADD_NBR(rhf, nbr);
		    }
		}
	    }
	    break;
	    
	case IDr:
	case IBACKUP:
	    /* if (!nbrptr) - Send to all up nbrs */
	    to = ALL_UP_NBRS;
	    if (!goingdown) {
		size_t len;

		/* There is less processing overhead for us in sending one */
		/* packet with all neighbors listed.  With a large */
		/* number of neighbors that could require more buffer */
		/* space than is allowed on a socket.  First we build */
		/* a packet with all neighbors listed.  If this packet */
		/* replicated by the number of neighbors is greater */
		/* than the available buffer space, or the packet is */
		/* greater than the interface MTU, we will make a */
		/* packet for each neighbor with only it's ID listed. */

		for (nbr = intf->nbr.next; nbr != NBRNULL; nbr = nbr->next) {
		    if (nbr->state != NDOWN) {
			ADD_NBR(rhf, nbr);
		    }
		}
		len = (caddr_t) rhf - (caddr_t) pkt;
		if (len > INTF_MTU(intf)
		    || (IP_MAXHDRLEN + len) * (rhf - &hello->rhf) > task_maxpacket) {
		    /* Better to absorb the overhead of sending an */
		    /* individual packet to each neighbor */

		    for (nbr = intf->nbr.next;
			 rhf = &hello->rhf, nbr != NBRNULL;
			 nbr = nbr->next) {
			if (nbr->state != NDOWN) {
			    ADD_NBR(rhf, nbr);
			    ospf_txpkt(pkt,
				       intf,
				       OSPF_PKT_HELLO,
				       (size_t) ((caddr_t) rhf - (caddr_t) pkt),
				       to, 
				       NOT_RETRANS);
			}
		    }
		return;
	    }
	    }
	    break;
	}
	break;

#ifdef	IP_MULTICAST
    case BROADCAST:
	/* On a multicast interface we need to include all neighbors */
	/* since they can all see this packet */

	to = sock2ip(ospf_addr_allspf);
	if (!goingdown) {
	    for (nbr = intf->nbr.next; nbr != NBRNULL; nbr = nbr->next) {
		if (nbr->state > NATTEMPT) {
		    ADD_NBR(rhf, nbr);
		}
	    }
	}
	break;
#endif	/* IP_MULTICAST */

    case POINT_TO_POINT:
#ifdef	IP_MULTICAST

	/* If possible we are supposed to use the IP multicast */
	/* address on serial interfaces, else just the neighbor's */
	/* address */
	if (BIT_TEST(intf->flags, OSPF_INTFF_MULTICAST)) {
	    to = sock2ip(ospf_addr_allspf);
	} else
#endif	/* IP_MULTICAST */
    case VIRTUAL_LINK:
	    to = NBR_ADDR(&intf->nbr);

	if (!goingdown
	    && intf->nbr.state > NATTEMPT) {
	    ADD_NBR(rhf, &intf->nbr);
	}
	break;

    default:
	assert(FALSE);
	break;
    }

    ospf_txpkt(pkt,
	       intf,
	       OSPF_PKT_HELLO,
	       (size_t) ((caddr_t) rhf - (caddr_t) pkt),
	       to, 
	       NOT_RETRANS);
#undef	ADD_NBR
}


void
send_exstart __PF3(intf, struct INTF *,
		   nbr, struct NBR *,
		   rt, int)	/* retrans flag */
{
    struct DB_HDR *dbh;
    struct OSPF_HDR *pkt = task_get_send_buffer(struct OSPF_HDR *);
    struct AREA *area = intf->area;

    dbh = (struct DB_HDR *) ((long) pkt + OSPF_HDR_SIZE);
    /* set bits */
    dbh->phill2 = 0;
    dbh->I_M_MS = nbr->I_M_MS;
    dbh->options = BIT_TEST(area->area_flags, OSPF_AREAF_STUB) ? 0 : OPT_E_bit;
    dbh->seq = htonl(nbr->seq);
    ospf_txpkt(pkt,
	       intf,
	       OSPF_PKT_DD,
	       (size_t) (DB_HDR_SIZE + OSPF_HDR_SIZE),
#ifdef	IP_MULTICAST
	       (intf->type == POINT_TO_POINT && BIT_TEST(intf->flags, OSPF_INTFF_MULTICAST)) ?
	       sock2ip(ospf_addr_allspf) :
#endif	/* IP_MULTICAST */
	       NBR_ADDR(nbr),
	       rt);
}


/*
 *	Send first on nbr list - don't free until ack has been received
 */
void
send_dbsum __PF3(intf, struct INTF *,
		 nbr, struct NBR *,
		 rt, int)	/* retrans flag */
{
    size_t len;
    struct DB_HDR *dbh;
    struct LSDB_SUM *ds;
    struct OSPF_HDR *pkt;
    struct AREA *area = intf->area;

    if (nbr->dbsum == LSDB_SUM_NULL) {
	ds = dbsum_alloc(intf, (size_t) (OSPF_HDR_SIZE + DB_HDR_SIZE));
	if (ds == LSDB_SUM_NULL)
	    return;
	ds->len = OSPF_HDR_SIZE + DB_HDR_SIZE;
	nbr->dbsum = ds;
    } else {
	ds = nbr->dbsum;
    }

    pkt = (struct OSPF_HDR *) ds->dbpkt;
    dbh = (struct DB_HDR *) &pkt->ospfh_un.database;
    len = ds->len;
    dbh->phill2 = 0;
    dbh->I_M_MS |= nbr->I_M_MS;
    dbh->options = BIT_TEST(area->area_flags, OSPF_AREAF_STUB) ? 0 : OPT_E_bit;
    dbh->seq = htonl(nbr->seq);

    ospf_txpkt(pkt,
	       intf,
	       OSPF_PKT_DD,
	       len,
#ifdef	IP_MULTICAST
	       (intf->type == POINT_TO_POINT && BIT_TEST(intf->flags, OSPF_INTFF_MULTICAST)) ?
	       sock2ip(ospf_addr_allspf) :
#endif	/* IP_MULTICAST */
	       NBR_ADDR(nbr),
	       rt);
}


/*
 *  send_req - build and send a db req packet
 *	     - called by exstart and retrans time; in both cases
 *		we'll just send what hasn't been taken off the req list
 */
void
send_req __PF3(intf, struct INTF *,
	       nbr, struct NBR *,
	       rt, int)	/* retrans flag */
{
    struct LS_REQ *r;
    struct OSPF_HDR *pkt = task_get_send_buffer(struct OSPF_HDR *);
    struct LS_REQ_HDR *req_hdr = &pkt->ospfh_un.ls_req;
    struct LS_REQ_PIECE *req = &req_hdr->req;
    size_t len = OSPF_HDR_SIZE;	/* max len of pkt is INTF_MTU(intf) */
    size_t intf_mtu = INTF_MTU(intf);
    int type;

    if (NO_REQ(nbr)) {
	return;
    }

    for (type = LS_RTR; type <= LS_ASE; type++) {
	for (r = nbr->ls_req[type]; r != LS_REQ_NULL; r = r->ptr[NEXT]) {
	    req->phill1 = req->phill2 = 0;
	    req->ls_type = type;
	    req->ls_id = r->ls_id;
	    req->adv_rtr = r->adv_rtr;
	    len += LS_REQ_PIECE_SIZE;
	    if (len + LS_REQ_PIECE_SIZE > intf_mtu) {
		goto send;
	    }
	    req++;
	}
    }

 send:
    ospf_txpkt(pkt,
	       intf,
	       OSPF_PKT_LSR,
	       len,
#ifdef	IP_MULTICAST
	       (intf->type == POINT_TO_POINT && BIT_TEST(intf->flags, OSPF_INTFF_MULTICAST)) ?
	       sock2ip(ospf_addr_allspf) :
#endif	/* IP_MULTICAST */
	       NBR_ADDR(nbr),
	       rt);
}


/*
 *  send_ack - build an ack packet from ack list, pass it to send ack
 */
int
send_ack __PF3(intf, struct INTF *,
	       nbr, struct NBR *,
	       qhp, struct LS_HDRQ *)
{
    struct OSPF_HDR *pkt = task_get_send_buffer(struct OSPF_HDR *);
    struct LS_HDRQ *al = qhp->ptr[NEXT];
    struct LS_ACK_HDR *ahdr;
    struct LS_HDR *ap;
    u_int32 to = 0;
    size_t len = OSPF_HDR_SIZE;
    size_t intf_mtu = INTF_MTU(intf);

    /* First get 'to' handled */
    if (nbr) {
	to = 
#ifdef	IP_MULTICAST
	    (intf->type == POINT_TO_POINT && BIT_TEST(intf->flags, OSPF_INTFF_MULTICAST)) ?
		sock2ip(ospf_addr_allspf) :
#endif	/* IP_MULTICAST */
		    NBR_ADDR(nbr);	/* direct ack */
    } else {
	switch (intf->type) {
#ifdef	IP_MULTICAST
	case BROADCAST:
	    switch (intf->state) {
	    case IDr:
	    case IBACKUP:
		to = sock2ip(ospf_addr_allspf);
		break;

	    default:
		to = sock2ip(ospf_addr_alldr);
		break;
	    }
	    break;
#endif	/* IP_MULTICAST */

	case NONBROADCAST:
	    to = ALL_EXCH_NBRS;
	    break;

	case POINT_TO_POINT:
#ifdef	IP_MULTICAST
	    if (BIT_TEST(intf->flags, OSPF_INTFF_MULTICAST)) {
		to = sock2ip(ospf_addr_allspf);
		break;
	    }
#endif	/* IP_MULTICAST */
	    /* Fall through */

	case VIRTUAL_LINK:
	    to = NBR_ADDR(&intf->nbr);
	    break;

	default:
	    assert(FALSE);
	    break;
	}
    }


    ahdr = (struct LS_ACK_HDR *) & pkt->ospfh_un.ls_ack;
    ap = &ahdr->ack_piece;

    while (al) {
	if (len + ACK_PIECE_SIZE >= intf_mtu) {
	    ospf_txpkt(pkt,
		       intf,
		       OSPF_PKT_ACK,
		       len,
		       to,
		       NOT_RETRANS);

	    if (!nbr && !ACK_QUEUE_FULL(intf)) {
		/* Since we had a full packet we know that we were not being called */
		/* by the Ack timer.  There are not enough acks left to fill a packet */
		/* so return with an indication that the timer should be started */

		return TRUE;
	    }

	    len = OSPF_HDR_SIZE;
	    ahdr = (struct LS_ACK_HDR *) & pkt->ospfh_un.ls_ack;
	    ap = &ahdr->ack_piece;
	}

	*ap = al->ls_hdr;	/* struct copy */
	len += ACK_PIECE_SIZE;
	ap++;

	qhp->ptr[NEXT] = al->ptr[NEXT];
	task_block_free(ospf_hdrq_index, (void_t) al);
	if (!nbr) {
	    intf->ack_cnt--;
	    /* XXX - stop if not a full packet */
	}
	al = qhp->ptr[NEXT];
    }

    if (len > OSPF_HDR_SIZE) {
	ospf_txpkt(pkt,
		   intf,
		   OSPF_PKT_ACK,
		   len,
		   to,
		   NOT_RETRANS);
    }

    return FALSE;
}


/*
 * send_lsu - go through db_list and send ls update pkt
 */
int
send_lsu __PF5(db_list, struct ospf_lsdb_list *,
	       hash, int,
	       nbr, struct NBR *,
	       intf, struct INTF *,
	       rt, int)		/* retrans flag */
{
    struct OSPF_HDR *pkt;
    struct ospf_lsdb_list *dbl;
    union ADV *adv;
    u_int32 to = 0;
    u_int32 *adv_cnt;
    size_t len = OSPF_HDR_SIZE + LS_UPDATE_HDR_SIZE;
    size_t intf_mtu = INTF_MTU(intf);
    struct ospf_lsdb_list *ll;
    struct ospf_lsdb_list lsdb_list;

    if (intf->state == IDOWN)
	return 0;

    NEW_LSU(pkt, adv_cnt, adv);
    if (nbr != NBRNULL) {
	to = NBR_ADDR(nbr);
    } else {
	switch (intf->type) {
#ifdef	IP_MULTICAST
	case BROADCAST:
	    switch (intf->state) {
	    case IDr:
	    case IBACKUP:
		to = sock2ip(ospf_addr_allspf);
		break;

	    default:
		to = sock2ip(ospf_addr_alldr);
		break;
	    }
	    break;
#endif	/* IP_MULTICAST */

	case POINT_TO_POINT:
#ifdef	IP_MULTICAST
	    if (BIT_TEST(intf->flags, OSPF_INTFF_MULTICAST)) {
		to = sock2ip(ospf_addr_allspf);
		break;
	    }
#endif	/* IP_MULTICAST */
	    /* Fall through */

	case VIRTUAL_LINK:
	    to = NBR_ADDR(&intf->nbr);
	    break;

	case NONBROADCAST:
	    to = ALL_EXCH_NBRS;
	    break;

	default:
	    assert(FALSE);
	    break;
	}
    }

    if (hash > 1) {
	ll = db_list;
    } else {
	lsdb_list.ptr[NEXT] = db_list;
	ll = &lsdb_list;
    }

    while (hash--) {
	/* For each hash bucket (only one unless a retrans) */

	for (dbl = ll[hash].ptr[NEXT]; dbl != LLNULL; dbl = dbl->ptr[NEXT]) {
	    u_int adv_age;

	    assert(dbl->lsdb);
	    if (rt) {
		if ((time_sec - dbl->lsdb->lsdb_time) < intf->retrans_timer)
		    continue;
	    } else {		/* !rt */
		if (dbl->flood != FLOOD) {
		    continue;
		}
	    }
	    if (len + ntohs(LS_LEN(dbl->lsdb)) >= intf_mtu) {
		if (*adv_cnt == 0) {
		    /* we've got a big'un */
		    
		    NEW_LSU(pkt, adv_cnt, adv);
		    goto big_un;
		}
		GHTONL(*adv_cnt);

		ospf_txpkt(pkt,
			   intf,
			   OSPF_PKT_LSU,
			   len,
			   to,
			   rt);

		/* if rt (retrans flag) is true just send one */
		if (rt)
		    return 0;

		NEW_LSU(pkt, adv_cnt, adv);
		len = OSPF_HDR_SIZE + LS_UPDATE_HDR_SIZE;
	    }

	big_un:
	    ADV_COPY(DB_RTR(dbl->lsdb), adv, ntohs(LS_LEN(dbl->lsdb)));
	    adv_age = ADV_AGE(dbl->lsdb) + intf->transdly;
	    adv->rtr.ls_hdr.ls_age = htons((u_int16) MIN(adv_age, MaxAge));
	    adv = (union ADV *) ((long) adv + ntohs(LS_LEN(dbl->lsdb)));
    	    len += ntohs(LS_LEN(dbl->lsdb));
	    (*adv_cnt)++;
	}
    }

    if (*adv_cnt) {		/* any left to send? */
	GHTONL(*adv_cnt);
	ospf_txpkt(pkt,
		   intf,
		   OSPF_PKT_LSU,
		   len,
		   to,
		   rt);
    }
    return 0;
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
