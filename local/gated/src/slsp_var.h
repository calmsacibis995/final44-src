/*
 * $Id: slsp_var.h,v 1.8.2.1 1994/05/08 15:52:42 jch Exp $
 */

/*%Copyright%*/


/*
 * SLSP private implementation definitions
 */

/*
 * Maximum amount of a broken packet we dump, and the amount to dump to a line.
 */
#define	SLSP_PKTDUMP_LINE	16
#define	SLSP_PKTDUMP_MAX	(SLSP_PKTDUMP_LINE * 6)

/*
 * Macros to deal with LSP AS payload lists.
 */

/*
 * Insert a new AS entry after the current entry
 */
#define	SLSP_ASL_APPEND(current, new) \
    do { \
	register slsp_db_as *Xn = (new); \
	register slsp_db_as *Xc = (current); \
	Xn->slspdb_as_prev = Xc; \
	Xn->slspdb_as_next = Xc->slspdb_as_next; \
	Xc->slspdb_as_next->slspdb_as_prev = Xn; \
	Xc->slspdb_as_next = Xn; \
    } while (0)

/*
 * Insert a new AS entry before the current entry
 */
#define SLSP_ASL_PREPEND(current, new) \
    do { \
	register slsp_db_as *Xn = (new); \
	register slsp_db_as *Xc = (current); \
	Xn->slspdb_as_next = Xc; \
	Xn->slspdb_as_prev = Xc->slspdb_as_prev; \
	Xc->slspdb_as_prev->slspdb_as_next = Xn; \
	Xc->slspdb_as_prev = Xn; \
    } while (0)

/*
 * Remove an AS entry from its list.
 */
#define	SLSP_ASL_REMOVE(current) \
    do { \
	register slsp_db_as *Xc = (current); \
	Xc->slspdb_as_prev->slspdb_as_next = Xc->slspdb_as_next; \
	Xc->slspdb_as_next->slspdb_as_prev = Xc->slspdb_as_prev; \
    } while (0)

/*
 * For received AS lists, rather than the local one, we don't bother
 * maintaining the back pointer.  This adds an AS to a list and bumps
 * the count.
 */
#define	SLSP_ASL_ADD(list, new) \
    do { \
	register slsp_db_as *Xl = (list); \
	register slsp_db_as *Xn = (new); \
	Xn->slspdb_as_next = Xl; \
	Xl->slspdb_as_prev->slspdb_as_next = Xn; \
	Xl->slspdb_as_prev = Xn; \
	Xl->slspdb_as_count++; \
    } while (0)

/*
 * Macro to initialize the head of a list
 */
#define	SLSP_ASL_INIT(list) \
    do { \
	register slsp_db_as *Xl = (list); \
	Xl->slspdb_as_prev = Xl->slspdb_as_next = Xl; \
	Xl->slspdb_as_nextlist = (slsp_db_as *)0; \
	Xl->slspdb_as = Xl->slspdb_as_count = 0; \
    } while (0)

/*
 * The local set of ASes is hashed so we can find individual AS entries
 * quickly.  The hash is a simple power-of-two hash.
 */
#define	SLSP_ASL_HASHSIZE	32
#define	SLSP_ASL_HASHMASK	(SLSP_ASL_HASHSIZE-1)
#define	SLSP_ASL_HASH(as)	((as) & SLSP_ASL_HASHMASK)


/*
 * Macros to deal with the links payload lists
 */

/*
 * Insert a new link entry after the current entry
 */
#define	SLSP_LINK_APPEND(current, new) \
    do { \
	register slsp_db_link *Xn = (new); \
	register slsp_db_link *Xc = (current); \
	Xn->slspdb_link_prev = Xc; \
	Xn->slspdb_link_next = Xc->slspdb_link_next; \
	Xc->slspdb_link_next->slspdb_link_prev = Xn; \
	Xc->slspdb_link_next = Xn; \
    } while (0)

/*
 * Insert a new link entry before the current entry
 */
#define SLSP_LINK_PREPEND(current, new) \
    do { \
	register slsp_db_link *Xn = (new); \
	register slsp_db_link *Xc = (current); \
	Xn->slspdb_link_next = Xc; \
	Xn->slspdb_link_prev = Xc->slspdb_link_prev; \
	Xc->slspdb_link_prev->slspdb_link_next = Xn; \
	Xc->slspdb_link_prev = Xn; \
    } while (0)

/*
 * Remove a link entry from its list.
 */
#define	SLSP_LINK_REMOVE(current) \
    do { \
	register slsp_db_link *Xc = (current); \
	Xc->slspdb_link_prev->slspdb_link_next = Xc->slspdb_link_next; \
	Xc->slspdb_link_next->slspdb_link_prev = Xc->slspdb_link_prev; \
    } while (0)

/*
 * For received linked lists, rather than the local one, we don't bother
 * maintaining the back pointer.  This adds a link to the end of the list.
 */
#define	SLSP_LINK_ADD(list, new) \
    do { \
	register slsp_db_link *Xl = (list); \
	register slsp_db_link *Xn = (new); \
	Xn->slspdb_link_next = Xl; \
	Xl->slspdb_link_prev->slspdb_link_next = Xn; \
	Xl->slspdb_link_prev = Xn; \
    } while (0)

/*
 * Initialize the first link added to the list.
 */
#define	SLSP_LINK_INIT(new) \
    do { \
	register slsp_db_link *Xn = (new); \
	Xn->slspdb_link_next = Xn->slspdb_link_prev = Xn; \
    } while (0)


/*
 * Macros to manipulate LSP lists
 */

/*
 * Insert a node in a route list after the current entry
 */
#define	SLSP_RT_APPEND(current, new) \
    do { \
	register slsp_rtlist *Xn = (slsp_rtlist *)(new); \
	register slsp_rtlist *Xc = (slsp_rtlist *)(current); \
	Xn->slsp_rtprev = Xc; \
	Xn->slsp_rtnext = Xc->slsp_rtnext; \
	Xc->slsp_rtnext->slsp_rtprev = Xn; \
	Xc->slsp_rtnext = Xn; \
    } while (0)

/*
 * Insert a node in a route list before the current entry
 */
#define SLSP_RT_PREPEND(current, new) \
    do { \
	register slsp_rtlist *Xn = (slsp_rtlist *)(new); \
	register slsp_rtlist *Xc = (slsp_rtlist *)(current); \
	Xn->slsp_rtnext = Xc; \
	Xn->slsp_rtprev = Xc->slsp_rtprev; \
	Xc->slsp_rtprev->slsp_rtnext = Xn; \
	Xc->slsp_rtprev = Xn; \
    } while (0)

/*
 * Remove a node from its route list.
 */
#define	SLSP_RT_REMOVE(current) \
    do { \
	register slsp_rtlist *Xc = (slsp_rtlist *)(current); \
	Xc->slsp_rtprev->slsp_rtnext = Xc->slsp_rtnext; \
	Xc->slsp_rtnext->slsp_rtprev = Xc->slsp_rtprev; \
    } while (0)

/*
 * Initialize the head of a route list
 */
#define	SLSP_RT_INIT(head) \
    do { \
	register slsp_rtlist *Xh = (slsp_rtlist *)(head); \
	Xh->slsp_rtnext = Xh->slsp_rtprev = Xh; \
    } while (0)

/*
 * Find the next node in a route list.
 */
#define	SLSP_RT_NEXT(head, current) \
    ((((slsp_rtlist *)(current))->slsp_rtnext == (slsp_rtlist *)(head)) ? \
      (slsp_db_node *)0 : ((slsp_db_node *)(((slsp_rtlist *)(current))->slsp_rtnext)))

/*
 * Find the previous node in a route list
 */
#define	SLSP_RT_PREV(head, current) \
    ((((slsp_rtlist *)(current))->slsp_rtprev == (slsp_rtlist *)(head)) ? \
      (slsp_db_node *)0 : ((slsp_db_node *)(((slsp_rtlist *)(current))->slsp_rtprev)))

/*
 * Determine if a route list is empty or not.
 */
#define	SLSP_RT_EMPTY(head) \
    (((slsp_rtlist *)(head))->slsp_rtprev == ((slsp_rtlist *)(head)))

/*
 * Insert a node in the transmit list after the current entry
 */
#define	SLSP_XMT_APPEND(current, new) \
    do { \
	register slsp_list *Xn = (slsp_list *)(new); \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xn->slsp_xmt_prev = Xc; \
	Xn->slsp_xmt_next = Xc->slsp_xmt_next; \
	Xc->slsp_xmt_next->slsp_xmt_prev = Xn; \
	Xc->slsp_xmt_next = Xn; \
    } while (0)

/*
 * Insert a node in the transmit list before the current entry
 */
#define SLSP_XMT_PREPEND(current, new) \
    do { \
	register slsp_list *Xn = (slsp_list *)(new); \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xn->slsp_xmt_next = Xc; \
	Xn->slsp_xmt_prev = Xc->slsp_xmt_prev; \
	Xc->slsp_xmt_prev->slsp_xmt_next = Xn; \
	Xc->slsp_xmt_prev = Xn; \
    } while (0)

/*
 * Remove a node from its transmit list.
 */
#define	SLSP_XMT_REMOVE(current) \
    do { \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xc->slsp_xmt_prev->slsp_xmt_next = Xc->slsp_xmt_next; \
	Xc->slsp_xmt_next->slsp_xmt_prev = Xc->slsp_xmt_prev; \
    } while (0)

/*
 * Initialize the head of the transmit list
 */
#define	SLSP_XMT_INIT(head) \
    do { \
	register slsp_list *Xh = (slsp_list *)(head); \
	Xh->slsp_xmt_next = Xh->slsp_xmt_prev = Xh; \
    } while (0)

/*
 * Find the next node in the transmit list.
 */
#define	SLSP_XMT_NEXT(head, current) \
    ((((slsp_list *)(current))->slsp_xmt_next == (slsp_list *)(head)) ? \
      (slsp_db_node *)0 : ((slsp_db_node *)(((slsp_list *)(current))->slsp_xmt_next)))

/*
 * Find the previous node in the transmit list
 */
#define	SLSP_XMT_PREV(head, current) \
    ((((slsp_list *)(current))->slsp_xmt_prev == (slsp_list *)(head)) ? \
      (slsp_db_node *)0 : ((slsp_db_node *)(((slsp_list *)(current))->slsp_xmt_prev)))

/*
 * Insert a node in the lifetime list after the current entry
 */
#define	SLSP_LIFE_APPEND(current, new) \
    do { \
	register slsp_list *Xn = (slsp_list *)(new); \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xn->slsp_life_prev = Xc; \
	Xn->slsp_life_next = Xc->slsp_life_next; \
	Xc->slsp_life_next->slsp_life_prev = Xn; \
	Xc->slsp_life_next = Xn; \
    } while (0)

/*
 * Insert a node in the lifetime list before the current entry
 */
#define SLSP_LIFE_PREPEND(current, new) \
    do { \
	register slsp_list *Xn = (slsp_list *)(new); \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xn->slsp_life_next = Xc; \
	Xn->slsp_life_prev = Xc->slsp_life_prev; \
	Xc->slsp_life_prev->slsp_life_next = Xn; \
	Xc->slsp_life_prev = Xn; \
    } while (0)

/*
 * Remove a node from the lifetime list.
 */
#define	SLSP_LIFE_REMOVE(current) \
    do { \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xc->slsp_life_prev->slsp_life_next = Xc->slsp_life_next; \
	Xc->slsp_life_next->slsp_life_prev = Xc->slsp_life_prev; \
    } while (0)

/*
 * Initialize the head of the lifetime list
 */
#define	SLSP_LIFE_INIT(head) \
    do { \
	register slsp_list *Xh = (slsp_list *)(head); \
	Xh->slsp_life_next = Xh->slsp_life_prev = Xh; \
    } while (0)

/*
 * Find the next node in the lifetime list.
 */
#define	SLSP_LIFE_NEXT(head, current) \
    ((((slsp_list *)(current))->slsp_life_next == (slsp_list *)(head)) ? \
     (slsp_db_node *)0 : ((slsp_db_node *)(((slsp_list *)(current))->slsp_life_next)))

/*
 * Find the previous node in the lifetime list
 */
#define	SLSP_LIFE_PREV(head, current) \
    ((((slsp_list *)(current))->slsp_life_prev == (slsp_list *)(head)) ? \
     (slsp_db_node *)0 : ((slsp_db_node *)(((slsp_list *)(current))->slsp_life_prev)))


/*
 * Insert a node in the full list after the current entry
 */
#define	SLSP_FULL_APPEND(current, new) \
    do { \
	register slsp_list *Xn = (slsp_list *)(new); \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xn->slsp_full_prev = Xc; \
	Xn->slsp_full_next = Xc->slsp_full_next; \
	Xc->slsp_full_next->slsp_full_prev = Xn; \
	Xc->slsp_full_next = Xn; \
    } while (0)

/*
 * Insert a node in the full list before the current entry
 */
#define SLSP_FULL_PREPEND(current, new) \
    do { \
	register slsp_list *Xn = (slsp_list *)(new); \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xn->slsp_full_next = Xc; \
	Xn->slsp_full_prev = Xc->slsp_full_prev; \
	Xc->slsp_full_prev->slsp_full_next = Xn; \
	Xc->slsp_full_prev = Xn; \
    } while (0)

/*
 * Remove a node from the full list.
 */
#define	SLSP_FULL_REMOVE(current) \
    do { \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xc->slsp_full_prev->slsp_full_next = Xc->slsp_full_next; \
	Xc->slsp_full_next->slsp_full_prev = Xc->slsp_full_prev; \
    } while (0)

/*
 * Initialize the head of the lifetime list
 */
#define	SLSP_FULL_INIT(head) \
    do { \
	register slsp_list *Xh = (slsp_list *)(head); \
	Xh->slsp_full_next = Xh->slsp_full_prev = Xh; \
    } while (0)

/*
 * Clear the full pointers in the current node to mark it not on
 * the list.
 */
#define	SLSP_FULL_CLEAR(current) \
    do { \
	register slsp_list *Xc = (slsp_list *)(current); \
	Xc->slsp_full_prev = Xc->slsp_full_next = (slsp_list *) 0; \
    } while (0)

/*
 * Find the next node in the full list.
 */
#define	SLSP_FULL_NEXT(head, current) \
    ((((slsp_list *)(current))->slsp_full_next == (slsp_list *)(head)) ? \
     (slsp_db_node *)0 : ((slsp_db_node *)(((slsp_list *)(current))->slsp_full_next)))

/*
 * Find the previous node in the full list
 */
#define	SLSP_FULL_PREV(head, current) \
    ((((slsp_list *)(current))->slsp_full_prev == (slsp_list *)(head)) ? \
     (slsp_db_node *)0 : ((slsp_db_node *)(((slsp_list *)(current))->slsp_full_prev)))

/*
 * Macros to deal with the full sequence numbers transmission list
 */

/*
 * Insert a new full sequence queue entry after the current entry
 */
#define	SLSP_FSQ_APPEND(current, new) \
    do { \
	register slsp_full_seq_q *Xn = (new); \
	register slsp_full_seq_q *Xc = (current); \
	Xn->slsp_fq_prev = Xc; \
	Xn->slsp_fq_next = Xc->slsp_fq_next; \
	Xc->slsp_fq_next->slsp_fq_prev = Xn; \
	Xc->slsp_fq_next = Xn; \
    } while (0)

/*
 * Insert a new full sequence queue entry before the current entry
 */
#define SLSP_FSQ_PREPEND(current, new) \
    do { \
	register slsp_full_seq_q *Xn = (new); \
	register slsp_full_seq_q *Xc = (current); \
	Xn->slsp_fq_next = Xc; \
	Xn->slsp_fq_prev = Xc->slsp_fq_prev; \
	Xc->slsp_fq_prev->slsp_fq_next = Xn; \
	Xc->slsp_fq_prev = Xn; \
    } while (0)

/*
 * Remove a full sequence queue entry from the list
 */
#define	SLSP_FSQ_REMOVE(current) \
    do { \
	register slsp_full_seq_q *Xc = (current); \
	Xc->slsp_fq_prev->slsp_fq_next = Xc->slsp_fq_next; \
	Xc->slsp_fq_next->slsp_fq_prev = Xc->slsp_fq_prev; \
    } while (0)

/*
 * Initialize the full sequence queue head
 */
#define	SLSP_FSQ_INIT(new) \
    do { \
	register slsp_full_seq_q *Xn = (new); \
	Xn->slsp_fq_next = Xn->slsp_fq_prev = Xn; \
    } while (0)


/*
 * Full sequence numbers packets on point-to-point links go out
 * several times to make sure they got though.  This is not in
 * the standard so it goes here.  On broadcast interfaces we wait
 * a small time before sending them.
 */
#define	SLSP_FULL_SEQ_MIN_TIME	6	/* minimum interval to send FSQ pkts */
#define	SLSP_FULL_SEQ_COUNT	3	/* send them three times */
#define	SLSP_FULL_SEQ_BCAST_INIT_TIME	1	/* time before sending bcast */


/*
 * The slsp bits structure is used to indicate the list of interfaces
 * an LSP needs to be transmitted from.  It is a fixed size, from
 * which derives the limitation on the number of local interfaces
 * a machine may have.
 *
 * The bits are numbered from 1 to SLSP_MAXINTERFACES
 */
#define	SLSP_BITMASK	(SLSP_BITSIZE-1)
#define	SLSP_WORDINDEX(x)	((x) >> SLSP_BITSHIFT)
#define	SLSP_BITINDEX(x)	((x) & SLSP_BITMASK)
#define	SLSP_BITINMASK(x)	(((slsp_bit_t)1) << SLSP_BITINDEX((x)))

/*
 * Test a nbr bit in the bit mask
 */
#define	SLSP_BIT_TEST(bits, nbr) \
    (((bits)->slsp_bit_set[(nbr)->slsp_nbr_offset] \
      & (nbr)->slsp_nbr_bitmask) != 0)
/*
 * Set a nbr bit in the bit mask.
 */
#define	SLSP_BIT_SET(bits, nbr) \
    do { \
	register slsp_bits *Xbits = (bits); \
	register slsp_neighbour *Xnbr = (nbr); \
	if (!SLSP_BIT_TEST(Xbits, Xnbr)) { \
	    Xbits->slsp_bit_set[Xnbr->slsp_nbr_offset] \
	      |= Xnbr->slsp_nbr_bitmask; \
	    Xbits->slsp_bit_n_set++; \
	} \
    } while (0)

/*
 * Clear a bit in the bit mask.
 */
#define	SLSP_BIT_CLR(bits, nbr) \
    do { \
	register slsp_bits *Xbits = (bits); \
	register slsp_neighbour *Xnbr = (nbr); \
	if (SLSP_BIT_TEST(Xbits, Xnbr)) { \
	    Xbits->slsp_bit_set[Xnbr->slsp_nbr_offset] \
	      &= ~(Xnbr->slsp_nbr_bitmask); \
	    Xbits->slsp_bit_n_set--; \
	} \
    } while (0)


/*
 * Mask value to use when the node contains no internal linkage information
 * (there is one node like this in every tree).
 */
#define	SLSP_NOMASK	0xffffffff

/*
 * Locate the candidate node in the node tree.
 */
#define	SLSP_NODE_LOCATE(slsp, addr, node) \
    do { \
	register slsp_db_node *Xnp = (slsp)->slsp_nodes; \
	register u_long Xmask = SLSP_NOMASK; \
	register u_long Xkey = ntohl(sock2ip((addr))); \
	if (Xnp != NULL) { \
	    while (Xmask > Xnp->slsp_node_mask) { \
		Xmask = Xnp->slsp_node_mask; \
		if (Xmask & Xkey) { \
		    Xnp = Xnp->slsp_node_right; \
		} else { \
		    Xnp = Xnp->slsp_node_left; \
		} \
	    } \
	} \
	(node) = Xnp; \
    } while (0)


/*
 * SPF scheduling.  We wait a minimum of 1 second from the time an SPF
 * run is first requested.  We try to wait until we've had a full second
 * without a change to the database, but defer no more than 5 seconds total.
 */
#define	SLSP_SPF_WAIT		(1)
#define	SLSP_SPF_LONG_WAIT	(2)
#define	SLSP_SPF_MAX_DEFER	(5)

#define	SLSP_SPF_SCHEDULE(inp) \
    do { \
	register slsp_instance *Xinp = (inp); \
	if (BIT_TEST(Xinp->slsp_flags, SLSPF_SPF)) { \
	    Xinp->slsp_spf_requested = time_sec; \
	} else { \
	    slsp_spf_schedule(inp); \
	} \
    } while (0)

/*
 * Function and variable declarations
 */

/*
 * From slsp_rt.c
 */
PROTOTYPE(slsp_spf_schedule,
	  extern void,
	  (slsp_instance *));
PROTOTYPE(slsp_rt_reinit,
	  extern void,
	  (task *));
PROTOTYPE(slsp_rt_terminate,
	  extern void,
	  (slsp_instance *));
PROTOTYPE(slsp_rt_dump,
	  extern void,
	  (FILE *,
	   slsp_instance *));

/*
 * From slsp_nbr.c
 */
PROTOTYPE(slsp_nbr_terminate,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_nbr_terminate_all,
	  extern void,
	  (slsp_instance *));
PROTOTYPE(slsp_nbr_ptp_hello,
	  extern void,
	  (slsp_neighbour *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_nbr_ptp_ihu,
	  extern void,
	  (slsp_neighbour *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_nbr_bcast_ihu,
	  extern void,
	  (slsp_neighbour *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_nbr_new_bcast_ihu,
	  extern void,
	  (slsp_neighbour *,
	   sockaddr_un *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_ifachange,
	  extern void,
	  (task *,
	   if_addr *));
PROTOTYPE(slsp_nbr_dump,
	  extern void,
	  (FILE *,
	   slsp_instance *));

/*
 * From slsp_db.c
 */
extern const byte slsp_bit_table[];
extern slsp_neighbour *slsp_db_ack_nbr;

#define	SLSP_DB_ACK_FLUSH() \
    do { \
	if (slsp_db_ack_nbr) { \
	    slsp_db_ack_flush((slsp_neighbour *) 0); \
	} \
    } while (0)

PROTOTYPE(slsp_db_bit_alloc,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_db_bit_free,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_db_ack_flush,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_db_dr_inform,
	  extern void,
	  (slsp_neighbour *,
	   slsp_neighbour *));
PROTOTYPE(slsp_db_down,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_db_ptp_up,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_db_bcast_up,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_db_lsp,
	  extern void,
	  (slsp_neighbour *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_db_seq,
	  extern void,
	  (slsp_neighbour *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_db_lsp_useless,
	  extern void,
	  (slsp_neighbour *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_db_dump,
	  extern void,
	  (FILE *,
	   slsp_instance *));
PROTOTYPE(slsp_db_init,
	  extern void,
	  (slsp_instance *));
PROTOTYPE(slsp_db_terminate,
	  extern void,
	  (slsp_instance *));
PROTOTYPE(slsp_db_link_changed,
	  extern void,
	  (slsp_neighbour *));

/*
 * From slsp_io.c
 */
PROTOTYPE(slsp_pktdump,
	  extern void,
	  (trace *,
	   const char *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_send,
	  extern void,
	  (slsp_neighbour *,
	   byte *,
	   size_t));
PROTOTYPE(slsp_io_add,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_io_remove,
	  extern void,
	  (slsp_neighbour *));
PROTOTYPE(slsp_io_start,
	  extern void,
	  (void));
PROTOTYPE(slsp_io_stop,
	  extern void,
	  (void));

/*
 * From slsp_init.c
 */
extern const bits slsp_nbr_types[];
extern const bits slsp_nbr_states[];
extern const bits slsp_node_types[];
extern const bits slsp_route_lists[];
extern const bits slsp_instance_flags[];
extern slsp_instance *slsp_instance_list;


#ifdef	PROTO_SNMP
/*
 * From slsp_mib.c
 */
PROTOTYPE(slsp_init_mib,
	  extern void,
	  (int));
PROTOTYPE(slsp_mib_remove_nbr,
	  extern void,
	  (slsp_neighbour *));
#endif	/* PROTO_SNMP */

/*
 * %(Copyright)
 */
