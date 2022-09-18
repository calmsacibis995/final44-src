/*
 * $Id: ospf_choose_dr.c,v 1.16.2.3 1994/08/15 21:18:07 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"


#define MaxNbr(MAX,N){\
	 if ((N->pri > MAX->pri) ||\
	    ((N->pri == MAX->pri) && (ntohl(NBR_ID(N)) > ntohl(NBR_ID(MAX)))))\
			MAX = N;}

/*
 *	Choose bdr for intf
 *	- Event: nbr change or wait timer
 */
static void
bdr_bakeoff  __PF1(intf, struct INTF *)
{
    struct NBR *n = NBRNULL;
    struct NBR *BestBDr = NBRNULL;

    /* Hi is for nbrs who haven't declaired themselves bdr or dr */
    struct NBR *BestBDrHi = NBRNULL;

    /* 
     * choose bdr 
     */
    for (n = &intf->nbr; n != NBRNULL; n = n->next) {
	/* if we can't see ourself, n isn't elig or n is dr... */
	if ((n->state < N2WAY) ||
	    (!n->pri) ||
	    (n->dr == NBR_ADDR(n)) ||
	    (intf->dr == n))
	    continue;

	if (n->bdr == NBR_ADDR(n)) {	
	    /* 
	     * nbr has declaired himself bdr 
	     */
	    if (BestBDr == NBRNULL) {
		BestBDr = n;
	    } else {
		MaxNbr(BestBDr, n);
	    }
	} else {			/* keep track of the highest priority choice */
	    /* exclude nbrs that are think they are dr */
	    if (BestBDrHi == NBRNULL) {
		BestBDrHi = n;
	    } else {
		MaxNbr(BestBDrHi, n);
	    }
	}
    }

    if (BestBDr != NBRNULL) {
	intf->bdr = BestBDr;
    } else if (BestBDrHi != NBRNULL) {
	intf->bdr = BestBDrHi;
    }

    /* 
     * set this rtr's nbr structure to correct bdr 
     */
    if (intf->bdr != NBRNULL) {
	intf->nbr.bdr = NBR_ADDR(intf->bdr);
    }
}


/*
 *	Choose dr for intf
 *	- Event: nbr change or wait timer
 *	  Return 1 if DR = BDR else return 0
 */
static void
dr_bakeoff __PF1(intf, struct INTF *)
{

    struct NBR *n = NBRNULL;
    struct NBR *BestDr = NBRNULL;

    /* choose dr */
    for (n = &intf->nbr; n != NBRNULL; n = n->next) {
	/*
	 * can see ourself in nbrs hello && nbr
	 *  has declaired himself dr
	 */
	if ((n->state >= N2WAY) &&
	    (n->pri) &&
	    (n->dr == NBR_ADDR(n))) {
	    if (BestDr == NBRNULL) {
		BestDr = n;
	    } else {
		MaxNbr(BestDr, n);
	    }
	}
    }

    if (BestDr != NBRNULL) {
	intf->dr = BestDr;
	intf->nbr.dr = NBR_ADDR(intf->dr);
    } else if (intf->bdr != NBRNULL) {
	/* promote backup */
	intf->dr = intf->bdr;
	intf->nbr.dr = NBR_ADDR(intf->bdr);
	/* This rtr can't be DR and BDr */
	if (intf->dr == &intf->nbr) {
	    intf->nbr.bdr = 0;
	    intf->bdr = NBRNULL;
	}
    }
}

void
ospf_choose_dr __PF1(intf, struct INTF *)
{
#ifdef	IP_MULTICAST
    int old_state = intf->state;
#endif	/* IP_MULTICAST */
    struct NBR *olddr = intf->dr;
    struct NBR *oldbdr = intf->bdr;
    struct NBR *n;

    intf->bdr = intf->dr = NBRNULL;
    bdr_bakeoff(intf);
    dr_bakeoff(intf);

    /* 
     * rerun backup if bdr or dr and this rtr is either or used to be 
     */
    if ((olddr != intf->dr
	 && (olddr == &intf->nbr || intf->dr == &intf->nbr))
	|| (oldbdr != intf->bdr &&
	    (oldbdr == &intf->nbr || intf->bdr == &intf->nbr))) {
	bdr_bakeoff(intf);
    }

    /* 
     * set to correct state 
     */
    if (intf->dr == &intf->nbr) {
	/* I am dr */
	intf->state = IDr;
    } else if (intf->bdr == &intf->nbr) {
	/* I am bdr */
	intf->state = IBACKUP;
    } else {
	intf->state = IDrOTHER;
    }

#ifdef	IP_MULTICAST
    if (old_state != intf->state
	&& BIT_TEST(intf->flags, OSPF_INTFF_MULTICAST)) {
	if ((old_state != IDr && old_state != IBACKUP)
	    && intf->state != IDrOTHER) {
	    /* Join All-SPF group */

	    ospf_multicast_alldr(intf, TRUE);
	} else if ((old_state == IDr || old_state == IBACKUP)
		   && intf->state == IDrOTHER) {
	    /* Leave All-SPF group */

	    ospf_multicast_alldr(intf, FALSE);
	}
    }
#endif	/* IP_MULTICAST */

    trace_tf(ospf.trace_options,
	     TR_STATE,
	     TRC_NL_AFTER,
	     ("OSPF DR ELECTION Interface %A:  DR: %A  BDR: %A",
	      intf->ifap->ifa_addr,
	      intf->dr ? intf->dr->nbr_id : sockbuild_str("none"),
	      intf->bdr ? intf->bdr->nbr_id : sockbuild_str("none")));

    /* handle adjacency madness */
    if (intf->state == IDr || intf->state == IBACKUP) {
	/* 
	 * if we weren't dr or bdr do the adj_ok thing to nbrs 
	 */
	if ((olddr != &intf->nbr && oldbdr != &intf->nbr)) {
	    for (n = intf->nbr.next; n != NBRNULL; n = n->next) {
		if (n->state == N2WAY) {
		    (*(nbr_trans[ADJ_OK][n->state])) (intf, n);
		} else if (intf->type == NONBROADCAST && n->state < N2WAY) {
		    (*(nbr_trans[START][n->state])) (intf, n);
		}
	    }
	}
	/* 
	 * flag build_net 
   	 */
	if (intf->state == IDr) {
	    BIT_SET(intf->flags, OSPF_INTFF_BUILDNET);
	}
    } else {
	if (olddr == &intf->nbr || oldbdr == &intf->nbr) {
	    /* 
	     * usedta be but no more so rst adj and adj with new dr 
	     */
	    for (n = intf->nbr.next; n != NBRNULL; n = n->next) {
		if ((n != intf->dr && n != intf->bdr)
		    && (n->state > N2WAY)) {
		    (*(nbr_trans[RST_ADJ][n->state])) (intf, n);
		}
	    }
	    if (intf->dr != NBRNULL && intf->dr->state <= N2WAY) {
		(*(nbr_trans[ADJ_OK][intf->dr->state])) (intf,
							 intf->dr);
	    }
	    if (intf->bdr != NBRNULL && intf->bdr->state <= N2WAY) {
		(*(nbr_trans[ADJ_OK][intf->bdr->state])) (intf,
							  intf->bdr);
	    }
	} else {
	    /* 
	     * we weren't dr or bdr but the current one has changed 
	     */
	    if (intf->dr != NBRNULL &&
		intf->dr != olddr &&
		intf->dr != oldbdr) {
		/* establish adj with new dr */
		(*(nbr_trans[ADJ_OK][intf->dr->state])) (intf, intf->dr);
	    }
	    if (intf->bdr != NBRNULL &&
		intf->bdr != olddr &&
		intf->dr != oldbdr &&
		intf->dr != intf->bdr) {
		/* establish adj with new bdr */
		(*(nbr_trans[ADJ_OK][intf->bdr->state])) (intf, intf->bdr);
	    }
	    /* 
	     * reset the old ones if necessary 
	     */
	    if (olddr != NBRNULL &&
		(olddr != intf->dr && olddr != intf->bdr) &&
		(olddr->state > N2WAY)) {
		(*(nbr_trans[RST_ADJ][olddr->state])) (intf, olddr);
	    }
	    if (oldbdr != NBRNULL &&
		(oldbdr != intf->dr && oldbdr != intf->bdr) &&
		(oldbdr->state > N2WAY)) {
		(*(nbr_trans[RST_ADJ][oldbdr->state])) (intf, oldbdr);
	    }
	}
    }
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
