/*
 * $Id: slsp_nbr.c,v 1.7.2.2 1994/07/22 17:53:04 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"
#include "inet.h"
#include "slsp_proto.h"
#include "slsp.h"
#include "slsp_var.h"

/*
 * Routines to deal with the management of neighbour adjacencies, both
 * broadcast and point-to-point.  Stuff in here sends and receives hello's,
 * maintains adjacency timers and builds local router and network database
 * nodes.
 */

/*
 * Memory which we allocate.  We allocate neighbour blocks and memory to
 * to store PTP hellos and broadcast IHU's.
 */
static block_t slsp_nbr_block = (block_t) 0;
static block_t slsp_ptp_hello_block = (block_t) 0;
static block_t slsp_bcast_ihu_small_block = (block_t) 0;
static block_t slsp_bcast_ihu_large_block = (block_t) 0;

/*
 * Macros to allocate said structures
 */
#define	SLSP_NBR_ALLOC() \
    ((slsp_neighbour *) task_block_alloc(slsp_nbr_block))

#define	SLSP_PTP_HELLO_ALLOC() \
    ((byte *) task_block_alloc(slsp_ptp_hello_block))

#define	SLSP_BCAST_IHU_SMALL_ALLOC() \
    ((byte *) task_block_alloc(slsp_bcast_ihu_small_block))

#define	SLSP_BCAST_IHU_LARGE_ALLOC() \
    ((byte *) task_block_alloc(slsp_bcast_ihu_large_block))

/*
 * Macros to free the structures
 */
#define	SLSP_NBR_FREE(nbr) \
    task_block_free(slsp_nbr_block, (void_t)(nbr))

#define	SLSP_PTP_HELLO_FREE(phello) \
    task_block_free(slsp_ptp_hello_block, (void_t)(phello))

#define	SLSP_BCAST_IHU_SMALL_FREE(bihu) \
    task_block_free(slsp_bcast_ihu_small_block, (void_t)(bihu));

#define	SLSP_BCAST_IHU_LARGE_FREE(bihu) \
    task_block_free(slsp_bcast_ihu_large_block, (void_t)(bihu));

/*
 * Macros to initialize task blocks for the easy-sized structures.
 */
#define	SLSP_NBR_INIT() \
    (slsp_nbr_block = task_block_init(sizeof(slsp_neighbour), "slsp_neighbour"))

#define	SLSP_PTP_HELLO_INIT() \
    (slsp_ptp_hello_block = task_block_init(SLSP_HELLO_LEN, "slsp_ptp_hello"))

/*
 * Sizes of BCAST_IHU blocks.
 */
#define	SLSP_N_BCAST_RTRS_SMALL		8	/* covers all our needs */
#define	SLSP_N_BCAST_RTRS_FULL		32	/* really big */

#define	SLSP_BCAST_IHU_SIZE(nrtrs) \
    (SLSP_BCAST_IHU_MIN_LEN + (SLSP_BCAST_IHU_RTR_LEN * (nrtrs)))

#define	SLSP_BCAST_IHU_SMALL_SIZE  SLSP_BCAST_IHU_SIZE(SLSP_N_BCAST_RTRS_SMALL)
#define	SLSP_BCAST_IHU_FULL_SIZE   SLSP_BCAST_IHU_SIZE(SLSP_N_BCAST_RTRS_FULL)

#define	SLSP_BCAST_IHU_SMALL_INIT()	(slsp_bcast_ihu_small_block = \
    task_block_init(SLSP_BCAST_IHU_SMALL_SIZE, "slsp_bcast_ihu_small"))
#define	SLSP_BCAST_IHU_LARGE_INIT()	(slsp_bcast_ihu_large_block = \
    task_block_init(SLSP_BCAST_IHU_FULL_SIZE, "slsp_bcast_ihu_large"))

/*
 * Test-and-get macros
 */
#define	SLSP_NBR_GET(nbr) \
    do { \
	if (!slsp_nbr_block) { \
	    SLSP_NBR_INIT(); \
	} \
	(nbr) = SLSP_NBR_ALLOC(); \
    } while (0)

#define	SLSP_PTP_HELLO_GET(phello) \
    do { \
	if (!slsp_ptp_hello_block) { \
	    SLSP_PTP_HELLO_INIT(); \
	} \
	(phello) = SLSP_PTP_HELLO_ALLOC(); \
    } while (0)

#define	SLSP_BCAST_IHU_SMALL_GET(bihu) \
    do { \
	if (!slsp_bcast_ihu_small_block) { \
	    SLSP_BCAST_IHU_SMALL_INIT(); \
	} \
	(bihu) = SLSP_BCAST_IHU_SMALL_ALLOC(); \
    } while (0)

#define	SLSP_BCAST_IHU_LARGE_GET(bihu) \
    do { \
	if (!slsp_bcast_ihu_large_block) { \
	    SLSP_BCAST_IHU_LARGE_INIT(); \
	} \
	(bihu) = SLSP_BCAST_IHU_LARGE_ALLOC(); \
    } while (0)

/*
 * A point-to-point IHU packet.  This is entirely fixed, so we just own one.
 * We use a macro to format and send this.
 */
static byte slsp_ptp_ihu_pkt[SLSP_PTP_IHU_LEN] = SLSP_PTP_IHU_PKT;

#define SLSP_SEND_PTP_IHU(nbr) \
    slsp_send((nbr), slsp_ptp_ihu_pkt, SLSP_PTP_IHU_LEN)

/*
 * Macro to send the hello attached to a neighbour's packet
 */
#define	SLSP_SEND_HELLO(nbr) \
    do { \
	slsp_neighbour *Xnbr = (nbr); \
	if (Xnbr->slsp_nbr_send_hello) { \
	    slsp_send(Xnbr, \
		      Xnbr->slsp_nbr_send_hello, \
		      Xnbr->slsp_nbr_send_hello_len); \
	} else { \
	    slsp_nbr_send_hello(Xnbr); \
	} \
    } while (0)

/*
 * Add a hello packet for this neighbour
 */
#define	SLSP_NBR_ADD_HELLO(nbr) \
    ((void) slsp_nbr_hello_format((nbr), (byte *) 0))


/*
 * Determine if a neighbour is on a subnet or not
 */
#define	SLSP_NBR_ON_SUBNET(ifap, addr) \
    ((sock2ip((addr)) & sock2ip((ifap)->ifa_netmask)) \
      == sock2ip((ifap)->ifa_net))


/*
 * Forward declarations
 */
PROTOTYPE(slsp_nbr_delete,
	  static void,
	  (slsp_neighbour *));


/*
 * slsp_nbr_pktdump - dump a packet that the packet processing code
 *		      has found it doesn't like.
 */
static void
slsp_nbr_pktdump __PF3(nbr, slsp_neighbour *,
		       pkt, byte *,
		       pktlen, size_t)
{
    slsp_pktdump(nbr->slsp_nbr_trace_options,
		 "SLSP ERR ",
		 pkt,
		 pktlen);
}

/*
 * slsp_nbr_hello_format - format a hello packet for this neighbour to send
 */
static size_t
slsp_nbr_hello_format __PF2(nbr, slsp_neighbour *,
			    pkt, byte *)
{
    slsp_instance *inp = nbr->slsp_nbr_instance;
    slsp_neighbour *bnbr;
    register byte *cp = pkt;
    int i;
    int init_it = 0;
    size_t len = (size_t) 0;

    switch (nbr->slsp_nbr_type) {
    case SLSP_NTYPE_PTP:
    case SLSP_NTYPE_PTP_PEER:
	/*
	 * Easy.  A point-to-point hello.
	 */
	if (cp) {
	    init_it = 1;
	} else if (!(cp = nbr->slsp_nbr_send_hello)) {
	    SLSP_PTP_HELLO_GET(cp);
	    nbr->slsp_nbr_send_hello = cp;
	    nbr->slsp_nbr_send_hello_len = SLSP_HELLO_LEN;
	    init_it = 1;
	}
	if (init_it) {
	    SLSP_PUT_HELLO_FIXED(cp);
	}
	SLSP_PUT_HELLO_VAR(nbr->slsp_nbr_routerdeadinterval,
			   inet_autonomous_system,
			   inp->slsp_addr,
			   cp);
	len = SLSP_HELLO_LEN;
	break;

    case SLSP_NTYPE_BCAST:
	/*
	 * Not so easy.  If we have a packet already, determine if the
	 * new one will fit in the space we have.
	 */
	if (cp) {
	    init_it = 1;
	} else if ((cp = nbr->slsp_nbr_send_hello)) {
	    if (nbr->slsp_nbr_n_hello <= SLSP_N_BCAST_RTRS_SMALL) {
		if (nbr->slsp_nbr_send_hello_len > SLSP_BCAST_IHU_SMALL_SIZE) {
		    SLSP_BCAST_IHU_LARGE_FREE(cp);
		    cp = (byte *) 0;
		}
	    } else {
		if (nbr->slsp_nbr_send_hello_len <= SLSP_BCAST_IHU_SMALL_SIZE) {
		    SLSP_BCAST_IHU_SMALL_FREE(cp);
		    cp = (byte *) 0;
		} else if (nbr->slsp_nbr_n_hello > SLSP_N_BCAST_RTRS_FULL) {
		    SLSP_BCAST_IHU_LARGE_FREE(cp);
		    cp = (byte *) 0;
		}
	    }
	}

	/*
	 * If there is no packet currently, see if we can fetch one which
	 * will fit.  Fill in the fixed portions.
	 */
	if (!cp) {
	    if (nbr->slsp_nbr_n_hello > SLSP_N_BCAST_RTRS_FULL) {
		nbr->slsp_nbr_send_hello = (byte *) 0;
		nbr->slsp_nbr_send_hello_len = 0;
		break;
	    }
	    if (nbr->slsp_nbr_n_hello <= SLSP_N_BCAST_RTRS_SMALL) {
		SLSP_BCAST_IHU_SMALL_GET(cp);
	    } else {
		SLSP_BCAST_IHU_LARGE_GET(cp);
	    }
	    nbr->slsp_nbr_send_hello = cp;
	    init_it = 1;
	}

	if (init_it) {
	    SLSP_INIT_BCAST_IHU(cp);
	}

	/*
	 * We have a packet.  Output the variable fields.
	 */
	SLSP_PUT_BCAST_IHU_VAR(nbr->slsp_nbr_his_priority,
			       (nbr->slsp_nbr_state
				 ? nbr->slsp_nbr_routerdeadinterval : 0),
			       inp->slsp_addr,
			       (nbr->slsp_nbr_dr
				 ? nbr->slsp_nbr_dr->slsp_nbr_addr
				 : (sockaddr_un *) 0),
			       cp);

	/*
	 * Put the routers.  First put the number of routers, then each
	 * router entry.
	 */
	i = nbr->slsp_nbr_n_hello;
	bnbr = nbr->slsp_nbr_list;
	SLSP_PUT_BCAST_N_RTRS(i, cp);
	while (i--) {
	    assert(SLSP_NBR_GOT_HELLO(bnbr));
	    SLSP_PUT_BCAST_RTR(bnbr->slsp_nbr_id,
			       bnbr->slsp_nbr_his_priority,
			       cp);
	    bnbr = bnbr->slsp_nbr_next;
	}

	/*
	 * Save the length.
	 */
	if (pkt) {
	    len = (cp - pkt);
	} else {
	    nbr->slsp_nbr_send_hello_len = len
	      = (cp - nbr->slsp_nbr_send_hello);
	}
	assert(len == SLSP_BCAST_IHU_SIZE(nbr->slsp_nbr_n_hello));
	break;

    default:
	assert(nbr->slsp_nbr_send_hello == (byte *) 0);
	break;
    }

    return len;
}


/*
 * slsp_nbr_send_hello - format and send a hello packet.  Used only when
 *			 the number of routers on a LAN is so large the
 *			 advertisement won't fit in one of our standard
 *			 packets.
 */
static void
slsp_nbr_send_hello __PF1(nbr, slsp_neighbour *)
{
    size_t len;

    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL,
	     0,
	     ("slsp_nbr_send_hello: formatting and sending hello to %A, # of routers %u",
	      nbr->slsp_nbr_addr,
	      nbr->slsp_nbr_n_hello));

    len = slsp_nbr_hello_format(nbr, (byte *) task_send_buffer);
    slsp_send(nbr, (byte *) task_send_buffer, len);
}


/*
 * slsp_nbr_bcast_rtrs_update - update the list of broadcast routers on this
 *				guy's hello packet.
 */
static void
slsp_nbr_bcast_rtrs_update __PF1(nbr, slsp_neighbour *)
{
    size_t size = nbr->slsp_nbr_send_hello_len;
    int nrtrs = (nbr->slsp_nbr_state ? nbr->slsp_nbr_n_hello : 0);
    int init_it = 0;
    register byte *cp;

    /*
     * If there are too many routers we build the packet every
     * time it is sent.  Make sure we don't have a hello packet attached.
     */
    cp = nbr->slsp_nbr_send_hello;
    if (nrtrs > SLSP_N_BCAST_RTRS_FULL) {
	if (cp) {
	    if (size > SLSP_BCAST_IHU_SMALL_SIZE) {
		SLSP_BCAST_IHU_LARGE_FREE(nbr->slsp_nbr_send_hello);
	    } else {
		SLSP_BCAST_IHU_SMALL_FREE(nbr->slsp_nbr_send_hello);
	    }
	    nbr->slsp_nbr_send_hello = (byte *) 0;
	    nbr->slsp_nbr_send_hello_len = 0;
	}
	return;
    }

    if (nrtrs > SLSP_N_BCAST_RTRS_SMALL) {
	if (!cp || size <= SLSP_BCAST_IHU_SMALL_SIZE) {
	    SLSP_BCAST_IHU_LARGE_GET(cp);
	    if (nbr->slsp_nbr_send_hello) {
		bcopy((void_t) nbr->slsp_nbr_send_hello,
		      (void_t) cp,
		      SLSP_BCAST_IHU_TORTRS_LEN);
		SLSP_BCAST_IHU_SMALL_FREE(nbr->slsp_nbr_send_hello);
	    } else {
		init_it = 1;
	    }
	    nbr->slsp_nbr_send_hello = cp;
	}
    } else {
	if (!cp || size > SLSP_BCAST_IHU_SMALL_SIZE) {
	    SLSP_BCAST_IHU_SMALL_GET(cp);
	    if (nbr->slsp_nbr_send_hello) {
		bcopy((void_t) nbr->slsp_nbr_send_hello,
		      (void_t) cp,
		      SLSP_BCAST_IHU_TORTRS_LEN);
		SLSP_BCAST_IHU_LARGE_FREE(nbr->slsp_nbr_send_hello);
	    } else {
		init_it = 1;
	    }
	    nbr->slsp_nbr_send_hello = cp;
	}
    }

    if (init_it) {
	SLSP_INIT_BCAST_IHU(cp);
	SLSP_PUT_BCAST_IHU_VAR(nbr->slsp_nbr_his_priority,
			       ((nbr->slsp_nbr_state != SLSP_NBR_STATE_DOWN)
				 ? nbr->slsp_nbr_routerdeadinterval : 0),
			       nbr->slsp_nbr_instance->slsp_addr,
			       (nbr->slsp_nbr_dr
				 ? nbr->slsp_nbr_dr->slsp_nbr_addr
				 : (sockaddr_un *) 0),
			       cp);
    } else {
	cp += SLSP_BCAST_IHU_TORTRS_LEN;
    }

    /*
     * Okay, we have a packet to work on.  Put the number of routers the
     * guy has into the packet.  If there are some, copy them in.
     */
    SLSP_PUT_BCAST_N_RTRS(nrtrs, cp);
    if (nrtrs) {
	register slsp_neighbour *bnbr = nbr->slsp_nbr_list;

	while (bnbr && nrtrs) {
	    nrtrs--;
	    assert(SLSP_NBR_GOT_HELLO(bnbr));
	    SLSP_PUT_BCAST_RTR(bnbr->slsp_nbr_id,
			       bnbr->slsp_nbr_his_priority,
			       cp);
	    bnbr = bnbr->slsp_nbr_next;
	}
	assert(!nrtrs && (!bnbr || !SLSP_NBR_GOT_HELLO(bnbr)));
    }
    nbr->slsp_nbr_send_hello_len = (cp - nbr->slsp_nbr_send_hello);
}


/*
 * slsp_nbr_dr - re-evaluate the designated router for a broadcast lan
 */
static void
slsp_nbr_dr __PF1(xnbr, slsp_neighbour *)
{
    register slsp_neighbour *nbr;
    register slsp_neighbour *nbr_dr;
    u_int best_prio;

    if (xnbr->slsp_nbr_type == SLSP_NTYPE_BCAST) {
	nbr = xnbr;
    } else {
	assert(xnbr->slsp_nbr_type == SLSP_NTYPE_BCAST_NBR);
	nbr = xnbr->slsp_nbr_parent;
    }

    /*
     * If we're not ready to become DR, make sure we haven't got
     * one already.
     */
    if (nbr->slsp_nbr_state == SLSP_NBR_STATE_DOWN) {
	if (nbr->slsp_nbr_dr) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		TR_NORMAL|TR_STATE,
		0,
	 	("slsp_nbr_dr: LAN interface %A going down, removing designated router %A",
		 nbr->slsp_nbr_addr,
		 nbr->slsp_nbr_dr->slsp_nbr_addr));
	    slsp_db_dr_inform(nbr, (slsp_neighbour *) 0);
	}
	return;
    }

    /*
     * Determine the priority of our best guy.  He'll be first on the
     * list.
     */
    nbr_dr = nbr->slsp_nbr_list;
    if (nbr_dr && SLSP_NBR_GOT_HELLO(nbr_dr)) {
	best_prio = nbr_dr->slsp_nbr_his_priority;
    } else {
	best_prio = 0;
	nbr_dr = (slsp_neighbour *) 0;
    }

    /*
     * Determine if we are eligible to become the designated router.
     * If so see how we compare.
     */
    if (nbr->slsp_nbr_his_priority) {
	if (nbr->slsp_nbr_his_priority > best_prio) {
	    nbr_dr = nbr;
	} else if (nbr->slsp_nbr_his_priority == best_prio) {
	    if (ntohl(sock2ip(nbr->slsp_nbr_addr)) >
	      ntohl(sock2ip(nbr_dr->slsp_nbr_addr))) {
		nbr_dr = nbr;
	    }
	}
    }

    /*
     * If someone else is best, determine whether he is eligible
     * to become the designated router.
     */
    if (nbr_dr && nbr_dr != nbr) {
	if (nbr_dr->slsp_nbr_state != SLSP_NBR_STATE_ADJACENT) {
	    nbr_dr = (slsp_neighbour *) 0;
	}
    }

    /*
     * If the designated router has changed, inform the database
     * and update our hello packet.
     */
    if (nbr->slsp_nbr_dr != nbr_dr) {
	if (nbr_dr) {
	    nbr->slsp_nbr_state = SLSP_NBR_STATE_ADJACENT;
	} else {
	    nbr->slsp_nbr_state = SLSP_NBR_STATE_HELLO;
	}
	if (TRACE_TF(nbr->slsp_nbr_trace_options, TR_NORMAL|TR_STATE)) {
	    if (!nbr_dr) {
		trace_only_tf(nbr->slsp_nbr_trace_options,
			      0,
	 		      ("slsp_nbr_dr: LAN interface %A designated router %A going down (no replacement)",
			       nbr->slsp_nbr_addr,
			       nbr->slsp_nbr_dr->slsp_nbr_addr));
	    } else if (!(nbr->slsp_nbr_dr)) {
		trace_only_tf(nbr->slsp_nbr_trace_options,
			      0,
	 		      ("slsp_nbr_dr: LAN interface %A designated router %A chosen (none previously)",
			       nbr->slsp_nbr_addr,
			       nbr_dr->slsp_nbr_addr));
	    } else {
		trace_only_tf(nbr->slsp_nbr_trace_options,
			      0,
	 		      ("slsp_nbr_dr: LAN interface %A designated router transition %A->%A",
			       nbr->slsp_nbr_addr,
			       nbr->slsp_nbr_dr->slsp_nbr_addr,
			       nbr_dr->slsp_nbr_addr));
	    }
	}
	slsp_db_dr_inform(nbr, nbr_dr);
	if (nbr->slsp_nbr_send_hello) {
	    if (nbr_dr) {
		SLSP_SET_BCAST_IHU_LAN_ADDR(nbr_dr->slsp_nbr_addr,
					    nbr->slsp_nbr_send_hello);
	    } else {
		SLSP_ZERO_BCAST_IHU_LAN_ADDR(nbr->slsp_nbr_send_hello);
	    }
	}

	/*
	 * If we're now the designated router, send a couple of hello's
	 * quickly to make sure everyone is brought up-to-date with any
	 * changes.
	 */
	if (nbr_dr == nbr) {
	    SLSP_SEND_HELLO(nbr);
	    if (nbr->slsp_nbr_hello_timer) {
	        register time_t f_interval;
		
		f_interval = (nbr->slsp_nbr_hellointerval / 2) + 1;
		task_timer_set(nbr->slsp_nbr_hello_timer,
			       f_interval,
			       (time_t)(grand((u_int32) f_interval) + 1));
	    }
	}
    }
}


/*
 * slsp_nbr_bcast_down - a broadcast neighbour has gone down because
 *			 of a timeout.  Move him to the end of the
 *			 list and remake the routers in the broadcast
 *			 hello packet.
 */
static void
slsp_nbr_bcast_down __PF1(nbr, slsp_neighbour *)
{
    slsp_neighbour *bnbr, *nbr_prev;

    assert(nbr->slsp_nbr_type == SLSP_NTYPE_BCAST_NBR);
    bnbr = nbr->slsp_nbr_parent;

    /*
     * Blow off his information
     */
    if (nbr->slsp_nbr_id) {
	sockfree(nbr->slsp_nbr_id);
	nbr->slsp_nbr_id = (sockaddr_un *) 0;
    }
    if (nbr->slsp_nbr_dr_addr) {
	sockfree(nbr->slsp_nbr_dr_addr);
	nbr->slsp_nbr_dr_addr = (sockaddr_un *) 0;
    }

    /*
     * Make sure he ends up with the guys in his state.  You can
     * tell them since they won't know the neighbour's ID.
     */
    if (nbr->slsp_nbr_next && nbr->slsp_nbr_next->slsp_nbr_id) {
	if ((nbr_prev = bnbr->slsp_nbr_list) == nbr) {
	    bnbr->slsp_nbr_list = nbr->slsp_nbr_next;
	} else {
	    while (nbr_prev && nbr_prev->slsp_nbr_next != nbr) {
		nbr_prev = nbr_prev->slsp_nbr_next;
	    }
	    assert(nbr_prev);
	    nbr_prev->slsp_nbr_next = nbr->slsp_nbr_next;
	}
	nbr_prev = nbr->slsp_nbr_next;
	while (nbr_prev->slsp_nbr_next
	  && nbr_prev->slsp_nbr_next->slsp_nbr_id) {
	    nbr_prev = nbr_prev->slsp_nbr_next;
	}
	nbr->slsp_nbr_next = nbr_prev->slsp_nbr_next;
	nbr_prev->slsp_nbr_next = nbr;
    }

    assert(bnbr->slsp_nbr_n_hello);
    bnbr->slsp_nbr_n_hello--;
    nbr->slsp_nbr_state = SLSP_NBR_STATE_DOWN;
    slsp_nbr_bcast_rtrs_update(bnbr);
    slsp_nbr_dr(bnbr);
}


/*
 * slsp_nbr_down - a neighbour has gone down, either because of a
 *		   time out or by explicit advertisement of his
 *		   impending demise.  Do the right thing to get the
 *		   adjacency shut down.
 */
static void
slsp_nbr_down __PF1(nbr, slsp_neighbour *)
{
    /*
     * Log that we're doing this
     */
    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL|TR_STATE,
	     0,
	     ("slsp_nbr_down: neighbour %A type %s ID %#A state %s->%s",
	      nbr->slsp_nbr_addr,
	      trace_state(slsp_nbr_types, nbr->slsp_nbr_type),
	      nbr->slsp_nbr_id,
	      trace_state(slsp_nbr_states, nbr->slsp_nbr_state),
	      trace_state(slsp_nbr_states, SLSP_NBR_STATE_DOWN)));

    /*
     * First pull the guy out of the database.  The db routine will
     * handle this.
     */
    if (nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT) {
	slsp_db_down(nbr);
    }

    /*
     * Reset his expiry timer, there is little to expire.
     */
    if (nbr->slsp_nbr_expire_timer) {
	task_timer_reset(nbr->slsp_nbr_expire_timer);
	nbr->slsp_nbr_expire_time = (time_t) 0;
    }

    /*
     * Blow away any received hello packet
     */
    if (nbr->slsp_nbr_recv_hello) {
	if (SLSP_NBR_PTP_TYPE(nbr)) {
	    SLSP_PTP_HELLO_FREE(nbr->slsp_nbr_recv_hello);
	} else if (nbr->slsp_nbr_recv_hello_len <= SLSP_BCAST_IHU_SMALL_SIZE) {
	    SLSP_BCAST_IHU_SMALL_FREE(nbr->slsp_nbr_recv_hello);
	} else {
	    SLSP_BCAST_IHU_LARGE_FREE(nbr->slsp_nbr_recv_hello);
	}
	nbr->slsp_nbr_recv_hello = (byte *) 0;
	nbr->slsp_nbr_recv_hello_len = 0;
    }

    /*
     * If this is a broadcast neighbour, move him to the end of the
     * broadcast neighbour list and remake the routers field of the
     * hello packet we send.
     */
    if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST_NBR) {
	slsp_nbr_bcast_down(nbr);
    } else {
	if (nbr->slsp_nbr_id) {
	    sockfree(nbr->slsp_nbr_id);
	    nbr->slsp_nbr_id = (sockaddr_un *) 0;
	}
	nbr->slsp_nbr_state = SLSP_NBR_STATE_DOWN;
    }
}


/*
 * slsp_nbr_hello_timeout - time to send a hello to a neighbour.  Do it quick,
 *			    this is running at priority.
 */
static void
slsp_nbr_hello_timeout __PF2(tip, task_timer *,
			     interval, time_t)
{
    SLSP_SEND_HELLO((slsp_neighbour *)(tip->task_timer_data));
}

/*
 * slsp_nbr_schedule_hello - create/set the hello timer for a peer
 */
static void
slsp_nbr_schedule_hello __PF1(nbr, slsp_neighbour *)
{
    time_t interval;
    time_t first_interval;

    assert(nbr->slsp_nbr_type != SLSP_NTYPE_BCAST_NBR);

    interval = nbr->slsp_nbr_hellointerval;
    if (nbr->slsp_nbr_hello_timer) {
	register task_timer *tip;

	/*
	 * Check to see if the interval has changed.  If so, reset it.
	 */
	tip = nbr->slsp_nbr_hello_timer;
	if (tip->task_timer_interval != interval) {
	    first_interval = (time_t) (grand((u_int32) interval) + 1);
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_nbr_schedule_hello: neighbour %A old interval %u new interval %u offset %u",
		      nbr->slsp_nbr_addr,
		      tip->task_timer_interval,
		      interval,
		      first_interval));
	    task_timer_set(tip, interval, first_interval);
	} else {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_nbr_schedule_hello: neighbour %A interval %u unchanged",
		      nbr->slsp_nbr_addr,
		      interval));
	}
    } else {
	first_interval = (time_t) (grand((u_int32) interval) + 1);
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_nbr_schedule_hello: neighbour %A creating timer interval %u offset %u",
		  nbr->slsp_nbr_addr,
		  interval,
		  first_interval));
	(void) sprintf(nbr->slsp_nbr_hello_timer_name,
		       "Hello.%#A",
		       nbr->slsp_nbr_addr);
	nbr->slsp_nbr_hello_timer
	  = task_timer_create(nbr->slsp_nbr_instance->slsp_task,
			      nbr->slsp_nbr_hello_timer_name,
			      TIMERF_HIPRIO,
			      interval,
			      first_interval,
			      slsp_nbr_hello_timeout,
			      (void_t) nbr);
    }
}


/*
 * slsp_nbr_delete_hello - delete a neighbour's hello timer
 */
static void
slsp_nbr_delete_hello __PF1(nbr, slsp_neighbour *)
{
    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL,
	     0,
	     ("slsp_nbr_delete_hello: neighbour %A delete hello timer requested%s",
	      nbr->slsp_nbr_addr,
	      (nbr->slsp_nbr_hello_timer ? "" : " but unnecessary")));
    if (nbr->slsp_nbr_hello_timer) {
	task_timer_delete(nbr->slsp_nbr_hello_timer);
	nbr->slsp_nbr_hello_timer = (task_timer *) 0;
    }
}

/*
 * slsp_nbr_expire_timeout - process an expire timeout for a neighbour.
 *			     This is mostly used to time out adjacencies,
 *			     though it is also used to time when we should
 *			     try to make ourselves the designated router
 *			     on the LAN.
 */
static void
slsp_nbr_expire_timeout __PF2(tip, task_timer *,
			      interval, time_t)
{
    slsp_neighbour *nbr = (slsp_neighbour *)(tip->task_timer_data);
    time_t expire_next;
    int expire_it;

    nbr->slsp_nbr_expire_time = (time_t) 0;

    switch (nbr->slsp_nbr_type) {
    default:
	assert(FALSE);

    case SLSP_NTYPE_PTP:
    case SLSP_NTYPE_PTP_PEER:
	assert(nbr->slsp_nbr_state);

	if (SLSP_NBR_GOT_HELLO(nbr)) {
	    expire_next = nbr->slsp_nbr_last_hello + nbr->slsp_nbr_holdtime;
	} else {
	    expire_next = (time_t) 0;
	}
	if (SLSP_NBR_GOT_IHU(nbr)) {
	    register time_t exp = nbr->slsp_nbr_last_ihu
	      + nbr->slsp_nbr_routerdeadinterval;

	    if (expire_next == (time_t) 0 || expire_next > exp) {
		expire_next = exp;
	    }
	}

	/*
	 * If we're expired, declare us down.  This'll reset the timer
	 */
	if (expire_next <= time_sec) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL|TR_STATE,
		     0,
		     ("slsp_nbr_expire_timeout: neighbour %A state %s timed out: last hello %u last ihu %u",
		      nbr->slsp_nbr_addr,
		      trace_state(slsp_nbr_states, nbr->slsp_nbr_state),
		      (nbr->slsp_nbr_last_hello
			? (time_sec - nbr->slsp_nbr_last_hello) : 0),
		      (nbr->slsp_nbr_last_ihu
			? (time_sec - nbr->slsp_nbr_last_ihu) : 0)));
	    slsp_nbr_down(nbr);
	    return;
	}
	break;

    case SLSP_NTYPE_BCAST_NBR:
	assert(nbr->slsp_nbr_state);

	expire_it = 0;
	if (SLSP_NBR_GOT_HELLO(nbr)) {
	    expire_next = nbr->slsp_nbr_last_hello + nbr->slsp_nbr_holdtime;
	    if (expire_next <= time_sec) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL|TR_STATE,
			 0,
			 ("slsp_nbr_expire_timeout: neighbour %A state %s timed out: last hello %u%s",
			  nbr->slsp_nbr_addr,
			  trace_state(slsp_nbr_states, nbr->slsp_nbr_state),
			  time_sec - nbr->slsp_nbr_last_hello,
			  (((time_sec - nbr->slsp_nbr_last_ihu)
			    >= nbr->slsp_nbr_routerdeadinterval)
			    ? " (removed)" : "")));
		slsp_nbr_down(nbr);
		nbr->slsp_nbr_state = SLSP_NBR_STATE_IHU;
		expire_it = 1;
	    } else {
		break;
	    }
	}

	expire_next = nbr->slsp_nbr_routerdeadinterval + nbr->slsp_nbr_last_ihu;
	if (expire_next <= time_sec) {
	    if (!expire_it) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_nbr_expire_timeout: neighbour %A timed out in IHU, removed",
			  nbr->slsp_nbr_addr));
	    }
	    slsp_nbr_delete(nbr);
	    return;
	}
	break;

    case SLSP_NTYPE_BCAST:
	/*
	 * Here we begin to advertise our true priority on a broadcast
	 * circuit.  Set the priority correctly in the broadcast hello,
	 * and inform the database that we may now have become a
	 * designated router.
	 */
	assert(nbr->slsp_nbr_his_priority == 0);
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL|TR_STATE,
		 0,
		 ("slsp_nbr_expire_timeout: setting priority to %u on LAN interface %A",
		  nbr->slsp_nbr_priority,
		  nbr->slsp_nbr_addr));
	nbr->slsp_nbr_his_priority = nbr->slsp_nbr_priority;
	if (nbr->slsp_nbr_send_hello) {
	    SLSP_SET_BCAST_IHU_PRIORITY(nbr->slsp_nbr_priority,
					nbr->slsp_nbr_send_hello);
	}
	nbr->slsp_nbr_state = SLSP_NBR_STATE_ADJACENT;
	slsp_nbr_dr(nbr);
	task_timer_delete(tip);
	nbr->slsp_nbr_expire_timer = (task_timer *) 0;
	return;
    }

    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL,
	     0,
	     ("slsp_nbr_expire_timeout: neighbour %A last HELLO %u last IHU %u timeout %u",
	      nbr->slsp_nbr_addr,
	      (nbr->slsp_nbr_last_hello
		? (time_sec - nbr->slsp_nbr_last_hello) : 0),
	      (nbr->slsp_nbr_last_ihu
		? (time_sec - nbr->slsp_nbr_last_ihu) : 0),
	      expire_next - time_sec));
    task_timer_set(tip,
		   (time_t) 0,
		   (expire_next - time_sec));
    nbr->slsp_nbr_expire_time = expire_next;
}


/*
 * slsp_nbr_schedule_expiry - determine the time of the next expiry event for a
 *			      neighbour and start/create/reset the timers
 */
static void
slsp_nbr_schedule_expiry __PF1(nbr, slsp_neighbour *)
{
    time_t expire_next = (time_t) 0;
    time_t exp;

    /*
     * What we do depends on the type of neighbour and the state
     * of the neighbour.
     */
    switch (nbr->slsp_nbr_type) {
    default:
	assert(FALSE);

    case SLSP_NTYPE_PTP:
    case SLSP_NTYPE_PTP_PEER:
	if (SLSP_NBR_GOT_HELLO(nbr)) {
	    expire_next = nbr->slsp_nbr_last_hello + nbr->slsp_nbr_holdtime;
	}
	if (SLSP_NBR_GOT_IHU(nbr)) {
	    exp = nbr->slsp_nbr_last_ihu + nbr->slsp_nbr_routerdeadinterval;

	    if (expire_next == (time_t) 0 || expire_next > exp) {
		expire_next = exp;
	    }
	}
	break;

    case SLSP_NTYPE_BCAST_NBR:
	if (SLSP_NBR_GOT_HELLO(nbr)) {
	    expire_next = nbr->slsp_nbr_last_hello + nbr->slsp_nbr_holdtime;
	} else if (nbr->slsp_nbr_state == SLSP_NBR_STATE_IHU) {
	    expire_next = nbr->slsp_nbr_last_ihu
	      + nbr->slsp_nbr_routerdeadinterval;
	}
	break;

    case SLSP_NTYPE_BCAST:
	if (nbr->slsp_nbr_state == SLSP_NBR_STATE_HELLO) {
	    expire_next = time_sec + (nbr->slsp_nbr_hellointerval * 2);
	}
	break;
    }

    /*
     * If there an expiry is needed make sure the timer gets set.
     * If the currently set timer is within a couple of seconds of
     * the desired time, don't bother.
     */
    if (expire_next) {
	if (expire_next < time_sec) {
	    expire_next = time_sec;
	}
	if (!nbr->slsp_nbr_expire_time
	  || nbr->slsp_nbr_expire_time > (expire_next + 2)) {
	    if (expire_next == time_sec) {
		expire_next++;
	    }
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_nbr_schedule_expiry: neighbour %A timer %sset to %u second%s",
		      nbr->slsp_nbr_addr,
		      (nbr->slsp_nbr_expire_time ? "re" : ""),
		      (expire_next - time_sec),
		      (((expire_next - time_sec) == 1) ? "" : "s")));
	    if (!(nbr->slsp_nbr_expire_timer)) {
		(void) sprintf(nbr->slsp_nbr_expire_timer_name,
			       "Expire.%#A",
			       nbr->slsp_nbr_addr);
		nbr->slsp_nbr_expire_timer
		  = task_timer_create(nbr->slsp_nbr_instance->slsp_task,
				      nbr->slsp_nbr_expire_timer_name,
				      (flag_t) 0,
				      (time_t) 0,
				      (expire_next - time_sec),
				      slsp_nbr_expire_timeout,
				      (void_t) nbr);
	    } else {
		task_timer_set(nbr->slsp_nbr_expire_timer,
			       (time_t) 0,
			       (expire_next - time_sec));
	    }
	    nbr->slsp_nbr_expire_time = expire_next;
	} else {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_nbr_schedule_expiry: neighbour %A needs expiry in %u timer set to %u",
		      nbr->slsp_nbr_addr,
		      (expire_next - time_sec),
		      ((nbr->slsp_nbr_expire_time > time_sec) ?
			(nbr->slsp_nbr_expire_time - time_sec) : (time_t) 0)));
	}
    } else {
	if (nbr->slsp_nbr_expire_time) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_nbr_schedule_expiry: resetting timer for neighbour %A",
		      nbr->slsp_nbr_addr));
	    task_timer_reset(nbr->slsp_nbr_expire_timer);
	    nbr->slsp_nbr_expire_time = (time_t) 0;
	} else {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_nbr_schedule_expiry: neighbour %A no expiry needed no timer set",
		      nbr->slsp_nbr_addr));
	}
    }
}


/*
 * slsp_nbr_delete_expiry - delete the expiry timer, it is no longer needed
 */
static void
slsp_nbr_delete_expiry __PF1(nbr, slsp_neighbour *)
{
    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL,
	     0,
	     ("slsp_nbr_delete_expiry: neighbour %A delete expiry timer requested%s",
	      nbr->slsp_nbr_addr,
	      (nbr->slsp_nbr_expire_timer ? "" : " but unnecessary")));
    if (nbr->slsp_nbr_expire_timer) {
	task_timer_delete(nbr->slsp_nbr_expire_timer);
	nbr->slsp_nbr_expire_timer = (task_timer *) 0;
    }
}

/*
 * slsp_nbr_bcast_changed - we have heard a broadcast neighbour's hello,
 *			    move him up in the packet.
 */
static void
slsp_nbr_bcast_changed __PF3(nbr_parent, slsp_neighbour *,
			     nbr, slsp_neighbour *,
			     up, int)
{
    register slsp_neighbour *nbr_prev;
    register slsp_neighbour *nbr_next;

    assert(nbr->slsp_nbr_type == SLSP_NTYPE_BCAST_NBR
	&& nbr_parent->slsp_nbr_type == SLSP_NTYPE_BCAST);

    /*
     * Remove the guy from the list if he is on it, then sort him
     * where he should go.
     */
    nbr_prev = nbr_parent->slsp_nbr_list;
    if (nbr_prev == nbr) {
	nbr_parent->slsp_nbr_list = nbr->slsp_nbr_next;
    } else {
	while (nbr_prev) {
	    if (nbr_prev->slsp_nbr_next == nbr) {
		nbr_prev->slsp_nbr_next = nbr->slsp_nbr_next;
		break;
	    }
	    nbr_prev = nbr_prev->slsp_nbr_next;
	}
    }

    nbr_prev = (slsp_neighbour *) 0;
    nbr_next = nbr_parent->slsp_nbr_list;
    while (nbr_next && nbr_next->slsp_nbr_id) {
	if (nbr_next->slsp_nbr_his_priority < nbr->slsp_nbr_his_priority) {
	    break;
	}
	if (nbr_next->slsp_nbr_his_priority == nbr->slsp_nbr_his_priority) {
	    if (ntohl(sock2ip(nbr_next->slsp_nbr_addr))
	      < ntohl(sock2ip(nbr->slsp_nbr_addr))) {
		break;
	    }
	}
	nbr_prev = nbr_next;
	nbr_next = nbr_prev->slsp_nbr_next;
    }
    if (nbr_prev) {
	nbr->slsp_nbr_next = nbr_prev->slsp_nbr_next;
	nbr_prev->slsp_nbr_next = nbr;
    } else {
	nbr->slsp_nbr_next = nbr_parent->slsp_nbr_list;
	nbr_parent->slsp_nbr_list = nbr;
    }

    /*
     * If the guy just came up, note that we've got a new one.  Then
     * update the routers.
     */
    if (up) {
	nbr_parent->slsp_nbr_n_hello++;
    }
    slsp_nbr_bcast_rtrs_update(nbr_parent);
}


/*
 * slsp_nbr_up - a neighbour adjacency just came up, do whatever is
 *		 needed to fix this.
 */
static void
slsp_nbr_up __PF1(nbr, slsp_neighbour *)
{
    u_int ostate = nbr->slsp_nbr_state;

    /*
     * Log this for posterity
     */
    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL|TR_STATE,
	     0,
	     ("slsp_nbr_up: neighbour %A type %s ID %#A state %s->%s",
	      nbr->slsp_nbr_addr,
	      trace_state(slsp_nbr_types, nbr->slsp_nbr_type),
	      nbr->slsp_nbr_id,
	      trace_state(slsp_nbr_states, ostate),
	      trace_state(slsp_nbr_states, SLSP_NBR_STATE_ADJACENT)));

    /*
     * If this is a ptp neighbour this is fairly easy, just inform
     * the database of him so it can bring up the link.  If this
     * is a broadcast neighbour what we do depends on what his state
     * was before he got here.  If he isn't in hello state currently
     * we will need to reevaluate the designated router.
     */
    nbr->slsp_nbr_state = SLSP_NBR_STATE_ADJACENT;
    if (SLSP_NBR_PTP_TYPE(nbr)) {
	slsp_db_ptp_up(nbr);
    } else {
	nbr->slsp_nbr_state = SLSP_NBR_STATE_ADJACENT;
	if (ostate != SLSP_NBR_STATE_HELLO) {
	    slsp_nbr_bcast_changed(nbr->slsp_nbr_parent, nbr, 1);
	}
	slsp_db_bcast_up(nbr);
	slsp_nbr_dr(nbr);
    }
}


/*
 * slsp_nbr_delete - delete a neighbour structure and all associated
 *		     gunk.  Remove him from the list he is on.
 */
static void
slsp_nbr_delete __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp = nbr->slsp_nbr_instance;
    slsp_neighbour *nbr_prev;

    if (nbr->slsp_nbr_expire_timer) {
	slsp_nbr_delete_expiry(nbr);
    }
    if (nbr->slsp_nbr_hello_timer) {
	slsp_nbr_delete_hello(nbr);
    }
    if (nbr->slsp_nbr_if) {
	IFA_FREE(nbr->slsp_nbr_if);
    }
    if (nbr->slsp_nbr_trace_options) {
	(void) trace_free(nbr->slsp_nbr_trace_options);
    }
    if (nbr->slsp_nbr_id) {
	sockfree(nbr->slsp_nbr_id);
    }
    if (nbr->slsp_nbr_dr_addr) {
	sockfree(nbr->slsp_nbr_dr_addr);
    }
    if (nbr->slsp_nbr_index) {
	slsp_db_bit_free(nbr);
    }
    if (SLSP_NBR_PTP_TYPE(nbr)) {
	if (nbr->slsp_nbr_recv_hello) {
	    SLSP_PTP_HELLO_FREE(nbr->slsp_nbr_recv_hello);
	}
	if (nbr->slsp_nbr_send_hello) {
	    SLSP_PTP_HELLO_FREE(nbr->slsp_nbr_send_hello);
	}
    } else {
	register int i;
	register size_t len;
	register byte *pkt;

	for (i = 0; i < 2; i++) {
	    if (i) {
		pkt = nbr->slsp_nbr_send_hello;
		len = nbr->slsp_nbr_send_hello_len;
	    } else {
		pkt = nbr->slsp_nbr_recv_hello;
		len = nbr->slsp_nbr_recv_hello_len;
	    }
	    if (pkt) {
		if (len <= SLSP_BCAST_IHU_SMALL_SIZE) {
		    SLSP_BCAST_IHU_SMALL_FREE(pkt);
		} else {
		    SLSP_BCAST_IHU_LARGE_FREE(pkt);
		}
	    }
	}
    }

    slsp_io_remove(nbr);

#ifdef	PROTO_SNMP
    slsp_mib_remove_nbr(nbr);
#endif	/* PROTO_SNMP */

    if (nbr->slsp_nbr_addr) {
	sockfree(nbr->slsp_nbr_addr);
    }

    if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST_NBR) {
	nbr_prev = nbr->slsp_nbr_parent;
	if (nbr_prev->slsp_nbr_list == nbr) {
	    nbr_prev->slsp_nbr_list = nbr->slsp_nbr_next;
	    nbr_prev = (slsp_neighbour *) 0;
	} else {
	    nbr_prev = nbr_prev->slsp_nbr_list;
	}
    } else {
	if ((nbr_prev = inp->slsp_nbrs) == nbr) {
	    inp->slsp_nbrs = nbr->slsp_nbr_next;
	    nbr_prev = (slsp_neighbour *) 0;
	}
    }

    while (nbr_prev) {
	if (nbr_prev->slsp_nbr_next == nbr) {
	    nbr_prev->slsp_nbr_next = nbr->slsp_nbr_next;
	    break;
	}
	nbr_prev = nbr_prev->slsp_nbr_next;
    }

    SLSP_NBR_FREE(nbr);
}


/*
 * slsp_nbr_create - create a neighbour of the specified type
 *		     with the specified address on the specified
 *		     interface.
 */
static slsp_neighbour *
slsp_nbr_create __PF6(inp, slsp_instance *,
		      parent_nbr, slsp_neighbour *,
		      parms, slsp_link_parms *,
		      type, u_int,
		      addr, sockaddr_un *,
		      ifap, if_addr *)
{
    register slsp_neighbour *nbr;

    SLSP_NBR_GET(nbr);
    nbr->slsp_nbr_type = type;
    nbr->slsp_nbr_addr = sockdup(addr);
    nbr->slsp_nbr_if = ifap; IFA_ALLOC(ifap);
    nbr->slsp_nbr_parms = *parms;	/* struct copy */
    if (nbr->slsp_nbr_trace_options) {
	nbr->slsp_nbr_trace_options = trace_alloc(nbr->slsp_nbr_trace_options);
    }
    nbr->slsp_nbr_instance = inp;
    slsp_db_bit_alloc(nbr);

    if (type == SLSP_NTYPE_BCAST_NBR) {
	register slsp_neighbour *nbr_prev = parent_nbr->slsp_nbr_list;

	if (!nbr_prev) {
	    parent_nbr->slsp_nbr_list = nbr;
	} else {
	    while (nbr_prev->slsp_nbr_next) {
		nbr_prev = nbr_prev->slsp_nbr_next;
	    }
	    nbr_prev->slsp_nbr_next = nbr;
	}
	nbr->slsp_nbr_parent = parent_nbr;
    } else {
	register slsp_neighbour *nbr_prev = inp->slsp_nbrs;

	if (!nbr_prev) {
	    inp->slsp_nbrs = nbr;
	} else {
	    while (nbr_prev->slsp_nbr_next) {
		nbr_prev = nbr_prev->slsp_nbr_next;
	    }
	    nbr_prev->slsp_nbr_next = nbr;
	}
    }

    slsp_io_add(nbr);

    /*
     * See if we need to start the neighbour's hello timer.  Only
     * in the case of a broadcast neighbour will this be unnecessary.
     * For local broadcast sessions we'll also need to schedule an
     * expiry to make sure we start to compete as designated router.
     */
    if (type != SLSP_NTYPE_BCAST_NBR) {
	if (type == SLSP_NTYPE_BCAST) {
	    nbr->slsp_nbr_state = SLSP_NBR_STATE_HELLO;		/* XXX shit! */
	    nbr->slsp_nbr_his_priority = 0;
	    slsp_nbr_schedule_expiry(nbr);
	}
	slsp_nbr_hello_format(nbr, (byte *) 0);
	slsp_nbr_schedule_hello(nbr);
    }

    return nbr;
}



/*
 * slsp_nbr_terminate - terminate a neighbour.  (Attempt to) advertise
 *			a killer hello, then remove his state and drop
 *			him.
 */
void
slsp_nbr_terminate __PF1(nbr, slsp_neighbour *)
{
    slsp_instance *inp = nbr->slsp_nbr_instance;

    trace_tf(inp->slsp_trace_options,
	     TR_NORMAL|TR_STATE,
	     0,
	     ("slsp_nbr_terminate: neighbour %A type %s state %s->%s",
	      nbr->slsp_nbr_addr,
	      trace_state(slsp_nbr_types, nbr->slsp_nbr_type),
	      trace_state(slsp_nbr_states, nbr->slsp_nbr_state),
	      trace_state(slsp_nbr_states, SLSP_NBR_STATE_DOWN)));

    /*
     * If the guy is a point-to-point guy, just send a hello
     * and blow him off.  If it is a broadcast neighbour blow
     * off all his children, then send the killer hello.
     */
    if (SLSP_NBR_PTP_TYPE(nbr)) {
	register byte *cp = nbr->slsp_nbr_send_hello;
	if (nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT) {
	    slsp_nbr_down(nbr);
	}
	SLSP_PUT_HELLO(0, inet_autonomous_system, inp->slsp_addr, cp);
    } else {
	register slsp_neighbour *nnbr, *nnbr_next;

	slsp_db_dr_inform(nbr, (slsp_neighbour *) 0);
	nnbr_next = nbr->slsp_nbr_list;
	while ((nnbr = nnbr_next)) {
	    nnbr_next = nnbr->slsp_nbr_next;
	    if (nnbr->slsp_nbr_state != SLSP_NBR_STATE_DOWN) {
		trace_tf(nbr->slsp_nbr_trace_options,
			 TR_NORMAL|TR_STATE,
			 0,
			 ("slsp_nbr_terminate: broadcast neighbour %A state %s->%s",
			 nnbr->slsp_nbr_addr,
			 trace_state(slsp_nbr_states, nnbr->slsp_nbr_state),
			 trace_state(slsp_nbr_states, SLSP_NBR_STATE_DOWN)));

		nnbr->slsp_nbr_state = SLSP_NBR_STATE_DOWN;
	    }
	    slsp_nbr_delete(nnbr);
	}
	nbr->slsp_nbr_his_priority = 0;
	nbr->slsp_nbr_n_hello = 0;
	slsp_nbr_hello_format(nbr, (byte *) 0);
    }

    SLSP_SEND_HELLO(nbr);
    slsp_nbr_delete(nbr);
}


/*
 * slsp_nbr_terminate_all - terminate all neighbours running in this instance
 */
void
slsp_nbr_terminate_all __PF1(inp, slsp_instance *)
{
    slsp_neighbour *nbr, *nbr_next;

    nbr_next = inp->slsp_nbrs;
    while ((nbr = nbr_next)) {
	nbr_next = nbr->slsp_nbr_next;
	slsp_nbr_terminate(nbr);
    }
}


/*
 * slsp_nbr_ptp_hello - receive and process a ptp hello from an existing
 *			 neighbour
 */
void
slsp_nbr_ptp_hello __PF3(nbr, slsp_neighbour *,
			 pkt, register byte *,
			 pktlen, size_t)
{
    byte *pbuf;
    sockaddr_un addr;
    as_t as;
    time_t holdtime;

    /*
     * Sanity check the length, it is fixed
     */
    if (pktlen < SLSP_HELLO_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_ptp_hello: neighbour %A packet length %u needs to be %u",
		  nbr->slsp_nbr_addr,
		  pktlen,
		  SLSP_HELLO_LEN));
	return;
    }

    /*
     * If we have a recorded copy of this guy's previous hello, just do a
     * bcmp().  If it matches, short circuit this.  This is the normal case.
     */
    if (nbr->slsp_nbr_recv_hello
      && !bcmp(nbr->slsp_nbr_recv_hello, pkt, SLSP_HELLO_LEN)) {
	/*
	 * Mention we got this for posterity
	 */
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_nbr_ptp_hello: got hello from %A (ID %#A), sending IHU in response",
		  nbr->slsp_nbr_addr,
		  nbr->slsp_nbr_id));
	SLSP_SEND_PTP_IHU(nbr);
	nbr->slsp_nbr_last_hello = time_sec;
	return;
    }

    /*
     * Here we have it harder.  Check the packet for fixed-field validity.
     */
    if (!SLSP_CHK_HELLO(pkt)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_ptp_hello: neighbour %A ptp hello received with invalid fixed field",
		  nbr->slsp_nbr_addr));
	goto dumppkt;
    }

    /*
     * Make sure the checksum works.  If not then ignore this.
     */
    if (!SLSP_CHK_HELLO_CKSUM(pkt)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_ptp_hello: neighbour %A ptp hello checksum failure",
		  nbr->slsp_nbr_addr));
	goto dumppkt;
    }

    /*
     * Now fetch the guts out of the packet.
     */
    sockclear_in(&addr);
    pbuf = pkt;
    SLSP_GET_HELLO(holdtime, as, &addr, pbuf);

    /*
     * If we have heard other hello's from this neighbour, check to see
     * what has changed.  If the holdtime is different we may need to
     * readjust the holdtime expiry timer.  If the holdtime is zero he
     * is signalling that he is going down, so update the database.
     * If his node address has changed we also pull the adjacency and
     * start again from scratch.
     */
    if (SLSP_NBR_GOT_HELLO(nbr)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_nbr_ptp_hello: changed hello from %A: ID %#A->%#A holdtime %d->%d as %u->%u",
		  nbr->slsp_nbr_addr,
		  nbr->slsp_nbr_id,
		  &addr,
		  nbr->slsp_nbr_holdtime,
		  holdtime,
		  nbr->slsp_nbr_as,
		  as));
	nbr->slsp_nbr_as = as;
	if (sock2ip(nbr->slsp_nbr_id) == sock2ip(&addr)) {
	    nbr->slsp_nbr_last_hello = time_sec;
	    if (holdtime != nbr->slsp_nbr_holdtime) {
		if (!holdtime) {
		    trace_tf(nbr->slsp_nbr_trace_options,
			     TR_NORMAL|TR_STATE,
			     0,
			     ("slsp_nbr_ptp_hello: neighbour %A ID %#A holdtime zero, terminating adjacency",
			      nbr->slsp_nbr_addr,
			      nbr->slsp_nbr_id));
		    slsp_nbr_down(nbr);
		    return;
		}
		if (holdtime < nbr->slsp_nbr_holdtime) {
		    nbr->slsp_nbr_holdtime = holdtime;
		    slsp_nbr_schedule_expiry(nbr);
		} else {
		    nbr->slsp_nbr_holdtime = holdtime;
		}
	    }
	    bcopy((void_t) pkt,
		  (void_t)(nbr->slsp_nbr_recv_hello),
		  SLSP_HELLO_LEN);
	    SLSP_SEND_PTP_IHU(nbr);
	    return;
	}

	/*
	 * In case you haven't been following, here we have a situation
	 * where the guy at the far end of the circuit changed his router
	 * ID.  Drop the current adjacency and let him restart.
	 */
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL|TR_STATE,
		 0,
		 ("slsp_nbr_ptp_hello: neighbour %A router ID changed, restarting adjacency",
		  nbr->slsp_nbr_addr));
	slsp_nbr_down(nbr);
    }

    /*
     * Make sure this is vaguely sensible
     */
    if (sock2ip(&addr) == 0
      || !SLSP_INSTANCE_ID(nbr->slsp_nbr_instance, &addr)) {
	/*
	 * Ignore the fact we got this, it doesn't matter anyway.
	 */
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_nbr_ptp_hello: ignoring neighbour %A hello: ID %#A holdtime %d as %u",
		  nbr->slsp_nbr_addr,
		  &addr,
		  holdtime,
		  as));
	return;
    }

    /*
     * If his holdtime is zero set the neighbour state to down if it
     * isn't already.
     */
    if (holdtime == 0) {
	if (nbr->slsp_nbr_state != SLSP_NBR_STATE_DOWN) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL|TR_STATE,
		     0,
		     ("slsp_nbr_ptp_hello: neighbour %A ID %#A as %u first hello has zero holdtime, restarting",
		      nbr->slsp_nbr_addr,
		      &addr,
		      as));
	    slsp_nbr_down(nbr);
	} else {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL|TR_STATE,
		     0,
		     ("slsp_nbr_ptp_hello: neighbour %A ID %#A as %u has zero holdtime",
		      nbr->slsp_nbr_addr,
		      &addr,
		      as));
	}
	return;
    }

    /*
     * Here we have the first hello received from this guy for the current
     * adjacency.  Record his information from the packet.  If we've already
     * received an IHU from him bring up the adjacency.
     */
    nbr->slsp_nbr_id = sockdup(&addr);
    nbr->slsp_nbr_as = as;
    nbr->slsp_nbr_holdtime = holdtime;
    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL|TR_STATE,
	     0,
	     ("slsp_nbr_ptp_hello: hello from %A: ID %#A holdtime %d AS %u state %s->%s",
	      nbr->slsp_nbr_addr,
	      &addr,
	      holdtime,
	      as,
	      trace_state(slsp_nbr_states, nbr->slsp_nbr_state),
	      trace_state(slsp_nbr_states, SLSP_NBR_NSTATE_HELLO(nbr))));

    if (nbr->slsp_nbr_state) {
	/*
	 * Already got IHU, we are adjacent now.
	 */
	slsp_nbr_up(nbr);
    } else {
	/*
	 * First we heard from him, note that we got this.
	 */
	nbr->slsp_nbr_state = SLSP_NBR_STATE_HELLO;
    }
    SLSP_PTP_HELLO_GET(nbr->slsp_nbr_recv_hello);
    bcopy((void_t) pkt,
	  (void_t)(nbr->slsp_nbr_recv_hello),
	  SLSP_HELLO_LEN);
    SLSP_SEND_PTP_IHU(nbr);
    nbr->slsp_nbr_last_hello = time_sec;
    slsp_nbr_schedule_expiry(nbr);

    /*
     * If not fully adjacent send an extraneous hello to try to bring
     * the adjacency up faster.
     */
    if (nbr->slsp_nbr_state != SLSP_NBR_STATE_ADJACENT) {
	SLSP_SEND_HELLO(nbr);
    }
    return;

dumppkt:
    slsp_nbr_pktdump(nbr, pkt, pktlen);
    return;
}


/*
 * slsp_nbr_ptp_ihu - called when we receive an IHU from a neighbour
 */
void
slsp_nbr_ptp_ihu __PF3(nbr, slsp_neighbour *,
		       pkt, byte *,
		       pktlen, size_t)
{
    /*
     * Stupid PTP IHU's are fixed length, fixed data thingy's.  Make
     * sure we have enough packet for one, then do a bcmp() to make
     * sure the insides are correct.
     */
    if (pktlen < SLSP_PTP_IHU_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_ptp_ihu: neighbour %A sent IHU length %u too short (< %u)",
		  nbr->slsp_nbr_addr,
		  pktlen,
		  SLSP_PTP_IHU_LEN));
	goto dumppkt;
    }
    if (bcmp((void_t) pkt, (void_t) slsp_ptp_ihu_pkt, SLSP_PTP_IHU_LEN)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_ptp_ihu: neighbour %A sent IHU with mangled contents",
		  nbr->slsp_nbr_addr));
	goto dumppkt;
    }
    nbr->slsp_nbr_last_ihu = time_sec;

    /*
     * If we've already heard an IHU from this guy, we're done.
     */
    if (SLSP_NBR_GOT_IHU(nbr)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_nbr_ptp_ihu: received IHU from neighbour %A",
		  nbr->slsp_nbr_addr));
	return;
    }

    /*
     * No such luck.  We can advance this guy's state.  Note that
     * this has happened.
     */
    trace_tf(nbr->slsp_nbr_trace_options,
	     TR_NORMAL|TR_STATE,
	     0,
	     ("slsp_nbr_ptp_ihu: IHU from neighbour %A state %s->%s",
	      nbr->slsp_nbr_addr,
	      trace_state(slsp_nbr_states, nbr->slsp_nbr_state),
	      trace_state(slsp_nbr_states, SLSP_NBR_NSTATE_IHU(nbr))));
    if (nbr->slsp_nbr_state) {
	slsp_nbr_up(nbr);
    } else {
	nbr->slsp_nbr_state = SLSP_NBR_STATE_IHU;
    }
    slsp_nbr_schedule_expiry(nbr);
    return;

dumppkt:
    slsp_nbr_pktdump(nbr, pkt, pktlen);
    return;
}


/*
 * slsp_nbr_bcast_ihu - process an incoming broadcast IHU from a neighbour
 */
void
slsp_nbr_bcast_ihu __PF3(nbr, slsp_neighbour *,
			 pkt, byte *,
			 pktlen, size_t)
{
    size_t nrtrs;
    size_t len;
    register byte *cp;
    byte priority, our_priority = 0;
    time_t holdtime;
    sockaddr_un node_addr, lan_addr;
    sockaddr_un rtr_id;
    u_long our_id;
    int i, has_our_id, rtrs_shitty;
    byte nstate;
    int change_it = 0;
    int change_holdtime = 0;

    /*
     * If the packet is too short, ignore it.
     */
    cp = pkt;
    if (pktlen < SLSP_BCAST_IHU_MIN_LEN) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_bcast_ihu: truncated broadcast IHU from %A: length %d (< %d)",
		  nbr->slsp_nbr_addr,
		  pktlen,
		  SLSP_BCAST_IHU_MIN_LEN));
	goto dumppkt;
    }

    /*
     * Compute the length of the packet as quickly as we can.  Make
     * sure the lengths which are fixed are zero.  Make sure the
     * packet length makes sense.
     */
    if (SLSP_GET_LEADER_LENGTH(cp) != SLSP_BCAST_IHU_FIXED_LEN
      || SLSP_FETCH_BCAST_N_AREAS(cp) != 0) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_bcast_ihu: broadcast IHU from %A: fixed length %u n_areas %u screwed",
		  nbr->slsp_nbr_addr,
		  SLSP_GET_LEADER_LENGTH(cp),
		  SLSP_FETCH_BCAST_N_AREAS(cp)));
	goto dumppkt;
    }

    nrtrs = SLSP_FETCH_BCAST_N_RTRS(cp);
    len = SLSP_BCAST_IHU_MIN_LEN + nrtrs * SLSP_BCAST_IHU_RTR_LEN;
    if (len > pktlen) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_bcast_ihu: broadcast IHU from %A: routers %u packet len %u should be at least %u",
		  nbr->slsp_nbr_addr,
		  nrtrs,
		  pktlen,
		  len));
	goto dumppkt;
    }

    /*
     * If the packet is an exact match for the one he sent last, we're
     * done.
     */
    if (nbr->slsp_nbr_recv_hello
      && nbr->slsp_nbr_recv_hello_len == len
      && !bcmp((void_t) cp, (void_t) nbr->slsp_nbr_recv_hello, len)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_nbr_bcast_ihu: received broadcast IHU from %A",
		  nbr->slsp_nbr_addr));
	nbr->slsp_nbr_last_hello = nbr->slsp_nbr_last_ihu = time_sec;
	return;
    }

    /*
     * No easy way out.  Pick this one apart to make sure it is sensible.
     * Assume the leader has been checked.  We know the lengths are sensible
     * from the checks above.  Fixed field checks first.
     */
    if (!SLSP_CHK_BCAST_IHU(cp)) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_ALL,
		 LOG_WARNING,
		 ("slsp_nbr_bcast_ihu: broadcast IHU from %A failed fixed field checks",
		  nbr->slsp_nbr_addr));
	goto dumppkt;
    }

    sockclear_in(&node_addr);
    sockclear_in(&lan_addr);
    SLSP_GET_BCAST_IHU(priority, holdtime, &node_addr, &lan_addr, cp);

    /*
     * Check the routers for format and to see if we're in there.
     */
    cp += SLSP_BCAST_N_AREAS_LEN + SLSP_BCAST_N_RTRS_LEN;
    has_our_id = 0;
    rtrs_shitty = 0;
    if (nrtrs) {
	register byte his_priority;

	sockclear_in(&rtr_id);
	our_id = sock2ip(nbr->slsp_nbr_instance->slsp_addr);
	for (i = 0; i < nrtrs; i++) {
	    if (!SLSP_CHK_BCAST_RTR(cp)) {
		rtrs_shitty = 1;
		break;
	    }
	    SLSP_GET_BCAST_RTR(&rtr_id, his_priority, cp);
	    if (sock2ip(&rtr_id) == 0) {
		rtrs_shitty = 1;
		break;
	    }
	    if (sock2ip(&rtr_id) == our_id) {
		if (has_our_id) {
		    rtrs_shitty = 1;
		} else {
		    has_our_id = 1;
		    our_priority = his_priority;
		}
	    }
	}
    }


    /*
     * See if this seems sensible.
     */
    if (rtrs_shitty
      || sock2ip(&node_addr) == 0
      || !SLSP_INSTANCE_ID(nbr->slsp_nbr_instance, &node_addr)
      || (sock2ip(&lan_addr) != 0
	&& !SLSP_NBR_ON_SUBNET(nbr->slsp_nbr_if, &lan_addr))) {
	/*
	 * Insane.  What we do is transition him to state IHU, which
	 * we'll time out with our own hold time.  If he's already in
	 * that state just log a message and return.  Otherwise put him
	 * in that state.
	 */
	nbr->slsp_nbr_last_ihu = time_sec;
	if (nbr->slsp_nbr_state == SLSP_NBR_STATE_IHU) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_nbr_bcast_ihu: rejecting broadcast IHU from %A: node ID %#A lan ID %#A holdtime %u priority %u%s",
		      nbr->slsp_nbr_addr,
		      &node_addr,
		      &lan_addr,
		      holdtime,
		      priority,
		      (rtrs_shitty ? " shitty routers" : "")));
	} else {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_ALL,
		     LOG_WARNING,
		     ("slsp_nbr_bcast_ihu: rejecting broadcast IHU from %A: node ID %#A lan ID %#A holdtime %u priority %u%s state %s->%s",
		      nbr->slsp_nbr_addr,
		      &node_addr,
		      &lan_addr,
		      holdtime,
		      priority,
		      (rtrs_shitty ? " shitty routers" : ""),
		      trace_state(slsp_nbr_states, nbr->slsp_nbr_state),
		      trace_state(slsp_nbr_states, SLSP_NBR_STATE_IHU)));
	    if (nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT) {
		slsp_nbr_down(nbr);
	    } else if (nbr->slsp_nbr_state == SLSP_NBR_STATE_HELLO) {
		slsp_nbr_bcast_down(nbr);
	    }
	    nbr->slsp_nbr_state = SLSP_NBR_STATE_IHU;
	    slsp_nbr_schedule_expiry(nbr);
	}
	return;
    }


    /*
     * If the holdtime is zero, this guy is on his way down.  Transition
     * to state IHU for a final time out.
     */
    if (holdtime == 0) {
	nbr->slsp_nbr_last_ihu = time_sec;
	if (nbr->slsp_nbr_state == SLSP_NBR_STATE_IHU) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL,
		     0,
		     ("slsp_nbr_bcast_ihu: broadcast neighbour %A claims he's down",
		      nbr->slsp_nbr_addr));
	} else {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL|TR_STATE,
		     0,
		     ("slsp_nbr_bcast_ihu: broadcast neighbour %A %s down",
		      nbr->slsp_nbr_addr,
		      (nbr->slsp_nbr_state ? "going" : "is")));
	    if (nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT) {
		slsp_nbr_down(nbr);
	    } else if (nbr->slsp_nbr_state == SLSP_NBR_STATE_HELLO) {
		slsp_nbr_bcast_down(nbr);
	    }
	    nbr->slsp_nbr_state = SLSP_NBR_STATE_IHU;
	    slsp_nbr_schedule_expiry(nbr);
	}
	return;
    }

    /*
     * If he has changed his node address from the last time we heard from
     * him, or if his priority has changed, transition him to down.  We
     * may bring him right back up again.
     */
    if (SLSP_NBR_GOT_HELLO(nbr)) {
	int changed_big = 0;
	int changed_little = 0;

	if (holdtime < nbr->slsp_nbr_holdtime) {
	    change_holdtime = 1;
	}
	if (sock2ip(&node_addr) != sock2ip(nbr->slsp_nbr_id) || !has_our_id) {
	    changed_big = 1;
	}
	if (changed_big
	  || nbr->slsp_nbr_his_priority !=  priority
	  || sock2ip(&lan_addr) != sock2ip(nbr->slsp_nbr_dr_addr)) {
	    changed_little = 1;
	}

	if (changed_little) {
	    if (TRACE_TF(nbr->slsp_nbr_trace_options, TR_NORMAL|TR_STATE)) {
		tracef("slsp_nbr_bcast_ihu: broadcast neighbour %A changed%s ID %#A->%#A priority %u->%u DR %#A->%#A",
		       nbr->slsp_nbr_addr,
		       (changed_big ? " big" : ""),
		       nbr->slsp_nbr_id,
		       &node_addr,
		       nbr->slsp_nbr_his_priority,
		       priority,
		       nbr->slsp_nbr_dr_addr,
		       &lan_addr);
		if (has_our_id) {
		    trace_only_tf(nbr->slsp_nbr_trace_options,
				  0,
				  (" our priority %u",
				   our_priority));
		} else {
		    trace_only_tf(nbr->slsp_nbr_trace_options,
				  0,
				  (" doesn't know us"));
		}
	    }

	    if (changed_big
	      && nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT) {
		slsp_nbr_down(nbr);
	    } else {
		change_it = 1;
	    }
	}
    }

    /*
     * Okay, record his stuff while we're here.
     */
    nbr->slsp_nbr_his_priority = priority;
    if (nbr->slsp_nbr_id) {
	sock2ip(nbr->slsp_nbr_id) = sock2ip(&node_addr);
	sock2ip(nbr->slsp_nbr_dr_addr) = sock2ip(&lan_addr);
    } else {
	nbr->slsp_nbr_id = sockdup(&node_addr);
	nbr->slsp_nbr_dr_addr = sockdup(&lan_addr);
    }

    if (has_our_id) {
	nstate = SLSP_NBR_STATE_ADJACENT;
    } else {
	nstate = SLSP_NBR_STATE_HELLO;
    }

    nbr->slsp_nbr_holdtime = holdtime;
    nbr->slsp_nbr_last_hello = nbr->slsp_nbr_last_ihu = time_sec;

    if (nbr->slsp_nbr_state != nstate) {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL|TR_STATE,
		 0,
		 ("slsp_nbr_bcast_ihu: broadcast neighbour %A state %s->%s ID %#A DR %#A priority %u",
		  nbr->slsp_nbr_addr,
		  trace_state(slsp_nbr_states, nbr->slsp_nbr_state),
		  trace_state(slsp_nbr_states, nstate),
		  &node_addr,
		  &lan_addr,
		  priority));

	if (nstate == SLSP_NBR_STATE_HELLO) {
	    if (nbr->slsp_nbr_state != SLSP_NBR_STATE_ADJACENT) {
		nbr->slsp_nbr_state = SLSP_NBR_STATE_HELLO;
		slsp_nbr_bcast_changed(nbr->slsp_nbr_parent, nbr, TRUE);
		slsp_nbr_dr(nbr);
	    } else {
		nbr->slsp_nbr_state = SLSP_NBR_STATE_HELLO;
		slsp_db_down(nbr);
		if (change_it) {
		    slsp_nbr_bcast_changed(nbr->slsp_nbr_parent, nbr, FALSE);
		    slsp_nbr_dr(nbr);
		}
	    }
	} else {
	    slsp_nbr_up(nbr);
	}
	slsp_nbr_schedule_expiry(nbr);
    } else {
	trace_tf(nbr->slsp_nbr_trace_options,
		 TR_NORMAL,
		 0,
		 ("slsp_nbr_bcast_ihu: updated IHU from broadcast neighbour %A",
		  nbr->slsp_nbr_addr));
	if (change_it) {
	    slsp_nbr_bcast_changed(nbr->slsp_nbr_parent, nbr, FALSE);
	    slsp_nbr_dr(nbr);
	}
	if (change_holdtime) {
	    slsp_nbr_schedule_expiry(nbr);
	}
    }

    if (nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT) {
	/*
	 * Record this packet for posterity.
	 */
	if (nbr->slsp_nbr_recv_hello) {
	    if ((nbr->slsp_nbr_recv_hello_len <= SLSP_BCAST_IHU_SMALL_SIZE) ^
	      (len <= SLSP_BCAST_IHU_SMALL_SIZE)) {
		if (nbr->slsp_nbr_recv_hello_len <= SLSP_BCAST_IHU_SMALL_SIZE) {
		    SLSP_BCAST_IHU_SMALL_FREE(nbr->slsp_nbr_recv_hello);
		} else {
		    SLSP_BCAST_IHU_LARGE_FREE(nbr->slsp_nbr_recv_hello);
		}
		nbr->slsp_nbr_recv_hello = (byte *) 0;
	    }
	}

	if (!(nbr->slsp_nbr_recv_hello)) {
	    if (len <= SLSP_BCAST_IHU_SMALL_SIZE) {
		SLSP_BCAST_IHU_SMALL_GET(nbr->slsp_nbr_recv_hello);
	    } else if (len <= SLSP_BCAST_IHU_FULL_SIZE) {
		SLSP_BCAST_IHU_LARGE_GET(nbr->slsp_nbr_recv_hello);
	    } else {
		nbr->slsp_nbr_recv_hello_len = 0;
		return;
	    }
	}

	bcopy((void_t) pkt, (void_t) nbr->slsp_nbr_recv_hello, len);
	nbr->slsp_nbr_recv_hello_len = len;
    } else if (nbr->slsp_nbr_recv_hello) {
	if (nbr->slsp_nbr_recv_hello_len <= SLSP_BCAST_IHU_SMALL_SIZE) {
	    SLSP_BCAST_IHU_SMALL_FREE(nbr->slsp_nbr_recv_hello);
	} else {
	    SLSP_BCAST_IHU_LARGE_FREE(nbr->slsp_nbr_recv_hello);
	}
	nbr->slsp_nbr_recv_hello = (byte *) 0;
	nbr->slsp_nbr_recv_hello_len = 0;
    }
    return;

dumppkt:
    slsp_nbr_pktdump(nbr, pkt, pktlen);
    return;
}


/*
 * slsp_nbr_new_bcast_ihu - receive a bcast ihu from someone we haven't
 *			    heard from before.  We create a neighbour
 *			    structure for the guy and then process his
 *			    packet.
 */
void
slsp_nbr_new_bcast_ihu __PF4(netnbr, slsp_neighbour *,
			     addr, sockaddr_un *,
			     pkt, byte *,
			     pktlen, size_t)
{
    slsp_neighbour *nbr;

    /*
     * Create a neighbour structure for this guy.
     */
    nbr = slsp_nbr_create(netnbr->slsp_nbr_instance,
			  netnbr,
			  &(netnbr->slsp_nbr_parms),
			  SLSP_NTYPE_BCAST_NBR,
			  addr,
			  netnbr->slsp_nbr_if);

    /*
     * We have a neighbour, let the broadcast code deal with the packet.
     */
    slsp_nbr_bcast_ihu(nbr, pkt, pktlen);
}


/*
 * slsp_nbr_change - process a change to a neighbour's parameters
 */
static int
slsp_nbr_change __PF2(nbr, slsp_neighbour *,
		      lp, slsp_link_parms *)
{
    int changed = 0;
    int prio_changed = 0;
    int propagate = 0;

    /*
     * Copy over the trace options
     */
    if (nbr->slsp_nbr_trace_options != lp->slsp_lp_trace_options) {
	trace_set(nbr->slsp_nbr_trace_options, lp->slsp_lp_trace_options);
	propagate = 1;
    }

    /*
     * Walk through each of the parameters noting what changed
     * and dealing with it.  Most things only affect what we
     * send in hello's, but a change to the cost will change our
     * link state if we are are adjacent.
     */
    if (nbr->slsp_nbr_cost != lp->slsp_lp_cost) {
	nbr->slsp_nbr_cost = lp->slsp_lp_cost;
	if (nbr->slsp_nbr_state == SLSP_NBR_STATE_ADJACENT) {
	    slsp_db_link_changed(nbr);
	}
	changed = 1;
    }

    if (nbr->slsp_nbr_priority != lp->slsp_lp_priority) {
	nbr->slsp_nbr_priority = lp->slsp_lp_priority;
	if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST
	  && !(nbr->slsp_nbr_expire_timer)) {
	    nbr->slsp_nbr_his_priority = nbr->slsp_nbr_priority;
	    slsp_nbr_dr(nbr);
	    prio_changed = 1;
	}
    }

    if (prio_changed
      || nbr->slsp_nbr_hellointerval != lp->slsp_lp_hellointerval
      || nbr->slsp_nbr_routerdeadinterval != lp->slsp_lp_routerdeadinterval) {
	changed = 1;
	nbr->slsp_nbr_hellointerval = lp->slsp_lp_hellointerval;
	nbr->slsp_nbr_routerdeadinterval = lp->slsp_lp_routerdeadinterval;
	slsp_nbr_hello_format(nbr, (byte *) 0);
	slsp_nbr_schedule_hello(nbr);
	SLSP_SEND_HELLO(nbr);	/* send one so the changes take right away */
    }

    if ((propagate || changed) && nbr->slsp_nbr_type == SLSP_NTYPE_BCAST) {
	register slsp_neighbour *nnbr;

	for (nnbr = nbr->slsp_nbr_list; nnbr; nnbr = nnbr->slsp_nbr_next) {
	    trace_set(nnbr->slsp_nbr_trace_options, lp->slsp_lp_trace_options);
	    nnbr->slsp_nbr_parms = *lp;		/* struct copy */
	}
    }

    return changed;
}


/*
 * slsp_nbr_ifup - called when an interface is reported up.  See
 *		   if we are allowed to run on the interface.  If
 *		   so add/update neighbour(s) for the interface.
 *		   If not terminate anyone running over the interface.
 */
static void
slsp_nbr_ifup __PF2(inp, slsp_instance *,
		    ifap, if_addr *)
{
    slsp_neighbour *nbr;
    slsp_link_parms *lp, lparms;
    slsp_gateway *sgw;
    u_int ntype;
    config_entry **list;
    
    /*
     * We only run on broadcast and p2p interfaces, ignore everything else
     */
    if (BIT_TEST(ifap->ifa_state, IFS_LOOPBACK)) {
	return;
    }
    if (!BIT_TEST(ifap->ifa_state, IFS_BROADCAST|IFS_POINTOPOINT)) {
	ntype = SLSP_NTYPE_PTP_PEER;
    } else if (BIT_TEST(ifap->ifa_state, IFS_POINTOPOINT)) {
	ntype = SLSP_NTYPE_PTP;
    } else {
	ntype = SLSP_NTYPE_BCAST;
    }

    /*
     * First run through the list of peers to see if we can find
     * some on this interface.  For each one we find, either find
     * an existing neighbour structure for him and update it, or
     * create a new neighbour.
     *
     * XXX This is stinking expensive, fix later
     */
    if (ntype != SLSP_NTYPE_PTP && (sgw = inp->slsp_gateways)) {
	if_addr *gw_ifap;

	do {
	    nbr = sgw->slsp_gw_nbr;
	    gw_ifap = if_withdst(sgw->slsp_gw_addr);
	    if (nbr && nbr->slsp_nbr_if != gw_ifap) {
		/*
		 * Interface changed, terminate this guy.
		 */
		trace_tf(inp->slsp_trace_options,
			 TR_NORMAL|TR_STATE,
			 0,
			 ("slsp_nbr_ifup: neighbour %A interface changed from %A(%s) to %A(%s): taking him down",
			  nbr->slsp_nbr_addr,
			  nbr->slsp_nbr_if->ifa_addr,
			  nbr->slsp_nbr_if->ifa_link->ifl_name,
			  gw_ifap->ifa_addr,
			  gw_ifap->ifa_link->ifl_name));
		slsp_nbr_terminate(nbr);
		sgw->slsp_gw_nbr = nbr = (slsp_neighbour *) 0;
	    }
	    lp = &(sgw->slsp_gw_parms);
	    if (gw_ifap == ifap) {
		if (nbr) {
		    if (slsp_nbr_change(nbr, lp)) {
			trace_tf(inp->slsp_trace_options,
				 TR_NORMAL,
				 0,
				 ("slsp_nbr_ifup: peer neighbour %A configuration changed",
				  nbr->slsp_nbr_addr));
		    }
		} else {
		    trace_tf(inp->slsp_trace_options,
			     TR_NORMAL|TR_STATE,
			     0,
			     ("slsp_nbr_ifup: peer neighbour %A on interface %A(%s) starting",
			      sgw->slsp_gw_addr,
			      ifap->ifa_addr,
			      ifap->ifa_link->ifl_name));
		    (void) slsp_nbr_create(inp,
					   (slsp_neighbour *) 0,
					   lp,
					   SLSP_NTYPE_PTP_PEER,
					   sgw->slsp_gw_addr,
					   ifap);
		}
	    }
	} while ((sgw = sgw->slsp_gw_next));
    }


    /*
     * If this is a non-broadcast multiaccess interface, we're done
     */
    if (ntype == SLSP_NTYPE_PTP_PEER) {
	return;
    }

    /*
     * See if we have a guy for this interface already.
     */
    nbr = inp->slsp_nbrs;
    while (nbr) {
	if (nbr->slsp_nbr_type != SLSP_NTYPE_PTP_PEER
	  && nbr->slsp_nbr_if == ifap) {
	    break;
	}
	nbr = nbr->slsp_nbr_next;
    }

    /*
     * Fetch the link parameters if we are allowed to run on
     * this interface.
     */
    list = config_resolv_ifa(inp->slsp_policy, ifap, SLSP_CONFIG_MAX);
    if (list) {
	config_entry *cp;
	int type = SLSP_CONFIG_MAX;
	lparms = inp->slsp_def_parms;		/* struct copy */
	while (--type) {
	    if ((cp = list[type])) {
		switch (type) {
		case SLSP_CONFIG_HELLO:
		    lparms.slsp_lp_hellointerval = (time_t) cp->config_data;
		    break;

		case SLSP_CONFIG_ROUTER:
		    lparms.slsp_lp_routerdeadinterval = (time_t) cp->config_data;
		    break;

		case SLSP_CONFIG_COST:
		    lparms.slsp_lp_cost = (u_short)((u_int) cp->config_data);
		    break;

		case SLSP_CONFIG_PRIORITY:
		    lparms.slsp_lp_priority = (u_short)((u_int)cp->config_data);
		    break;

		case SLSP_CONFIG_TRACE:
		    if (cp->config_data) {
			lparms.slsp_lp_trace_options = (trace *) cp->config_data;
		    }
		    break;
		}
	    }
	}
	config_resolv_free(list, SLSP_CONFIG_MAX);
    }


    /*
     * If we aren't allowed to run here, but we have a guy, terminate
     * him.  If we're allowed to run here, either create a guy or check
     * the existing guy for changes.
     */
    if (!list) {
	if (nbr) {
	    trace_tf(inp->slsp_trace_options,
		     TR_NORMAL|TR_STATE,
		     0,
		     ("slsp_nbr_if_up: interface %A(%s) no longer configured, terminating protocol",
		      ifap->ifa_addr,
		      ifap->ifa_link->ifl_name));
	    slsp_nbr_terminate(nbr);
	}
    } else {
	if (nbr) {
	    if (slsp_nbr_change(nbr, &lparms)) {
		trace_tf(inp->slsp_trace_options,
			 TR_NORMAL,
			 0,
			 ("slsp_nbr_ifup: interface %A(%s) neighbour configuration changed",
			  ifap->ifa_addr,
			  ifap->ifa_link->ifl_name));
	    }
	} else {
	    trace_tf(inp->slsp_trace_options,
		     TR_NORMAL|TR_STATE,
		     0,
		     ("slsp_nbr_if_up: starting protocol on interface %A(%s)",
		      ifap->ifa_addr,
		      ifap->ifa_link->ifl_name));
	    (void) slsp_nbr_create(inp,
				   (slsp_neighbour *) 0,
				   &lparms,
				   ntype,
				   ifap->ifa_addr,
				   ifap);
	}
    }

    /* Done! */
}


/*
 * slsp_nbr_ifdown - process an interface down event
 */
static void
slsp_nbr_ifdown __PF2(inp, slsp_instance *,
		      ifap, if_addr *)
{
    slsp_neighbour *nbr;

    /*
     * Process the list of neighbours looking for guys using
     * this interface.  Terminate them all.
     */
    nbr = inp->slsp_nbrs;
    while (nbr) {
	register slsp_neighbour *nbr_next = nbr->slsp_nbr_next;

	if (nbr->slsp_nbr_if == ifap) {
	    trace_tf(nbr->slsp_nbr_trace_options,
		     TR_NORMAL|TR_STATE,
		     0,
		     ("slsp_nbr_ifdown: neighbour %A terminated, interface %A(%s) went down",
		      nbr->slsp_nbr_addr,
		      ifap->ifa_addr,
		      ifap->ifa_link->ifl_name));
	    slsp_nbr_terminate(nbr);
	}
	nbr = nbr_next;
    }
}


/*
 * slsp_ifachange - process an interface event for an instance,
 *		    adding/deleting/reevaluating peers as appropriate.
 */
void
slsp_ifachange __PF2(tp, task *,
		     ifap, if_addr *)
{
    slsp_instance *inp = (slsp_instance *)(tp->task_data);

    if (socktype(ifap->ifa_addr) != AF_INET) {
	return;
    }

    switch (ifap->ifa_change) {
    case IFC_NOCHANGE:
    case IFC_ADD:
	if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
	    slsp_nbr_ifup(inp, ifap);
	}
	break;

    case IFC_DELETE:
    case IFC_DELETE|IFC_UPDOWN:
	slsp_nbr_ifdown(inp, ifap);
	break;

    default:
	if (BIT_TEST(ifap->ifa_change, IFC_UPDOWN)) {
	    if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
		slsp_nbr_ifup(inp, ifap);
	    } else {
		slsp_nbr_ifdown(inp, ifap);
	    }
	}

	/* For us everything else is noise */
	break;
    }
}


/*
 * slsp_nbr_dump - dump what we know about neighbours
 */
void
slsp_nbr_dump __PF2(fd, FILE *,
		    inp, slsp_instance *)
{
    /* TBD */
}

/*
 * %(Copyright)
 */
