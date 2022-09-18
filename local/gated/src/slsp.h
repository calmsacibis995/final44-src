/*
 * $Id: slsp.h,v 1.8.2.2 1994/05/08 15:52:16 jch Exp $
 */

/*%Copyright%*/


/*
 * Implementation definitions for slsp.
 */

/*
 * Number of input octets we read at a time before returning.
 */
#define	SLSP_RECV_OCTETS	12000

/*
 * Maximum number of neighbours we allow, compiled in for now
 */
#define	SLSP_MAX_NEIGHBOURS	48

/*
 * Bit mask processing.  No matter what the size of your bytes the
 * code only puts 8 bits in them
 */
typedef	byte slsp_bit_t;
#define	SLSP_BITSIZE	8	/* i.e. sizeof(slsp_bit_t) */
#define	SLSP_BITSHIFT	3	/* i.e. log2(SLSP_BITSIZE) */

#define	SLSP_BITLEN	((SLSP_MAX_NEIGHBOURS+SLSP_BITSIZE-1) >> SLSP_BITSHIFT)

/*
 * SLSP-specific trace flags.
 */
#define	TR_SLSP_HELLO		TR_PACKET_1
#define	TR_SLSP_SEND_HELLO	TR_PACKET_SEND_1
#define	TR_SLSP_RECV_HELLO	TR_PACKET_RECV_1
#define	TR_SLSP_LSP		TR_PACKET_2
#define	TR_SLSP_SEND_LSP	TR_PACKET_SEND_2
#define	TR_SLSP_RECV_LSP	TR_PACKET_RECV_2
#define	TR_SLSP_SPF		TR_USER_1

#define	TR_SLSP_SEND		(TR_SLSP_SEND_HELLO|TR_SLSP_SEND_LSP)
#define	TR_SLSP_RECV		(TR_SLSP_RECV_HELLO|TR_SLSP_RECV_LSP)
#define	TR_SLSP_DETAIL_HELLO	(TR_DETAIL_1 & (~TR_SLSP_HELLO))
#define	TR_SLSP_DETAIL_LSP	(TR_DETAIL_2 & (~TR_SLSP_LSP))

#define	TR_SLSP_INDEX_PACKETS	0
#define	TR_SLSP_INDEX_HELLO	1
#define	TR_SLSP_INDEX_LSP	2

/*
 * Parameter definitions.  There are four parameters associated with
 * each interface and/or neighbour.
 *
 * hellointerval -  the time between sending hellos
 * routerdeadinterval - the amount of time between hearing the last hello
 *			from a neighbour and declaring him dead.
 * cost - the cost of this circuit/interface
 * priority - used for choosing the designated router on broadcast
 *	      circuits.  I think lower is better.
 */
typedef struct _slsp_link_parms {
    trace *slsp_lp_trace_options;
    time_t slsp_lp_hellointerval;
    time_t slsp_lp_routerdeadinterval;
    u_short slsp_lp_cost;
    u_short slsp_lp_priority;
} slsp_link_parms;

/*
 * Default parameters
 */
#define	SLSP_DEFAULT_HELLOINTERVAL	10
#define	SLSP_DEFAULT_ROUTERDEADINTERVAL	60
#define	SLSP_DEFAULT_COST		1
#define	SLSP_DEFAULT_PRIORITY		1
#define	SLSP_DEFAULT_PREFERENCE		20

/*
 * For the parser
 */
#define	SLSP_MIN_HELLOINTERVAL		2
#define	SLSP_MAX_HELLOINTERVAL		600

#define	SLSP_MIN_ROUTERDEADINTERVAL	5
#define	SLSP_MAX_ROUTERDEADINTERVAL	2400

#define	SLSP_MIN_COST			1
#define	SLSP_MAX_COST			255

#define	SLSP_MIN_PRIORITY		0
#define	SLSP_MAX_PRIORITY		127

#define	SLSP_LIMIT_HELLOINTERVAL \
	SLSP_MIN_HELLOINTERVAL,SLSP_MAX_HELLOINTERVAL

#define	SLSP_LIMIT_ROUTERDEADINTERVAL \
	SLSP_MIN_ROUTERDEADINTERVAL,SLSP_MAX_ROUTERDEADINTERVAL

#define	SLSP_LIMIT_COST		SLSP_MIN_COST,SLSP_MAX_COST
#define	SLSP_LIMIT_PRIORITY	SLSP_MIN_PRIORITY,SLSP_MAX_PRIORITY

/*
 * Configuration codes
 */
#define	SLSP_CONFIG_HELLO	1
#define	SLSP_CONFIG_ROUTER	2
#define	SLSP_CONFIG_COST	3
#define	SLSP_CONFIG_PRIORITY	4
#define	SLSP_CONFIG_TRACE	5
#define	SLSP_CONFIG_MAX		6

/*
 * Value for metrics we don't use XXX dump this
 */
#define	SLSP_METRIC_NONE	((metric_t) 0)


/*
 * The AS payload in the LSP is stored in the database in sets of doubly
 * linked lists.  The head of the list keeps track of the number of ASes
 * in the list, plus a chain pointer to additional lists.
 *
 * There is, in addition, a hash chain pointer and a reference count for
 * use in maintaining the local node AS list.  These overlay the chain
 * to additional lists and the count of the number of ASes.
 */
typedef struct _slsp_db_as {
    struct _slsp_db_as *slspdb_as_prev;		/* previous AS in chain */
    struct _slsp_db_as *slspdb_as_next;		/* next AS in chain */
    u_long slspdb_as_refcount;			/* count of ASes in list */
#define	slspdb_as_count	slspdb_as_refcount
    as_t slspdb_as;				/* the AS in question */
    byte slspdb_as_newbucket;			/* 1 for new bucket */
} slsp_db_as;

/*
 * The links payload is also stored in a doubly linked list.  Each
 * link points at the node to which the link connects (dummy nodes are
 * created if we don't yet have an lsdb entry for the real node).
 * For nodes other than our own, only the forward pointers are maintained.
 * Associated with each link is a cost and a flag to tell you if you
 * should create another cost bucket in the outgoing packet.
 *
 * The current implementation assumes the number of links to each node
 * is small, and so does linear searches to locate them.  Should this
 * prove to be unwise the links should probably be hashed.
 */
typedef struct _slsp_db_link {
    struct _slsp_db_link *slspdb_link_prev;	/* back pointer */
    struct _slsp_db_link *slspdb_link_next;	/* forward pointer */
    struct _slsp_db_node *slspdb_link_node;	/* pointer to node */
    struct _slsp_neighbour *slspdb_link_nbr;	/* link to direct neighbour */
    as_t slspdb_link_as;			/* AS associated with node */
    byte slspdb_link_cost;			/* cost of this link */
    byte slspdb_link_newbucket;			/* set to 1 for new bucket */
} slsp_db_link;


/*
 * The slsp node list structure.  There are four doubly linked lists
 * an slsp node can live on, the (re)transmit list, the lifetime expiry
 * list, the route list and the "full" list.  This structure lives at the
 * front of every slsp node.
 */
typedef struct _slsp_rtlist {
    struct _slsp_rtlist *slsp_rtprev;
    struct _slsp_rtlist *slsp_rtnext;
} slsp_rtlist;

typedef struct _slsp_list {
    slsp_rtlist slsp_rt_list;
#define	slsp_rt_prev	slsp_rt_list.slsp_rtprev
#define	slsp_rt_next	slsp_rt_list.slsp_rtnext
    struct _slsp_list *slsp_full_prev;
    struct _slsp_list *slsp_full_next;
    struct _slsp_list *slsp_xmt_prev;
    struct _slsp_list *slsp_xmt_next;
    struct _slsp_list *slsp_life_prev;
    struct _slsp_list *slsp_life_next;
} slsp_list;


/*
 * The full sequence numbers transmit queue.  We transmit a full
 * sequence numbers packet 4 times after an adjacency comes up,
 * or until we get some indication that he got the packet.
 */
typedef struct _slsp_full_seq_q {
    struct _slsp_full_seq_q *slsp_fq_prev;
    struct _slsp_full_seq_q *slsp_fq_next;
    struct _slsp_neighbour *slsp_fq_nbr;
    time_t slsp_fq_time;
    u_long slsp_fq_count;		/* count of times sent */
#define	slsp_fq_n_entries	slsp_fq_count
} slsp_full_seq_q;


/*
 * The slsp bits structure is used to indicate the list of interfaces
 * an LSP needs to be transmitted from.  It has a variable-sized
 * byte array attached, which we use to keep track of various guys.
 *
 * The bits are numbered from 1.
 */
typedef struct _slsp_bits {
    u_short slsp_bit_n_set;
    slsp_bit_t slsp_bit_set[SLSP_BITLEN];
} slsp_bits;

/*
 * Data types for sequence numbers and the checksum
 */
typedef long	slsp_seqnum_t;
typedef	u_short	slsp_cksum_t;


/*
 * The slsp node structure.  One of these exists for each node in
 * the network which we have either received an LSP for, or for
 * which we have received an LSP which mentioned a link to the node.
 * These live in several lists.  There is a (re)transmit queue, on
 * which nodes whose LSPs need to be transmitted to adjacent speakers
 * sometime in the future live.  There is a lifetime expiry list
 * which is used to find LSPs whose lifetime has expired.  There are
 * several route lists (each node is on one of them) which are used by
 * the SPF code when sorting entries.  There is a node Patricia tree into
 * which every known node is inserted for searches by ID and for pretty
 * printing.  In addition to this there are the set of links this node
 * has advertised, the set of ASes, and lots of bookkeeping junk.
 */
typedef struct _slsp_db_node {
    /* list maintenance data of various sorts */
    slsp_list slsp_node_list;			/* list pointers first */
    struct _slsp_db_node *slsp_node_left;	/* zero node in patricia tree */
    struct _slsp_db_node *slsp_node_right;	/* one node in patricia tree */
    u_long slsp_node_mask;			/* bit to test in patricia */

    /* ID for this node */
    sockaddr_un *slsp_node_addr;		/* node address */
    sockaddr_un *slsp_node_rtmask;		/* mask corresponding to net */

    /* State information */
    flag_t slsp_node_flags;			/* state bits */
    u_short slsp_node_refcount;			/* holders of node */
    byte slsp_node_type;			/* type of node */
    byte slsp_node_onlist;			/* route list node is on */
    struct _slsp_neighbour *slsp_node_nbr;	/* pointer to bcast nbr */

    /* Back pointer to instance */
    struct _slsp_instance *slsp_node_instance;

    /* Other stuff derived from the LSP */
    time_t slsp_node_life;			/* time when lifetime expires */
    size_t slsp_node_len;			/* total length of LSP */
    slsp_seqnum_t slsp_node_seqnum;		/* sequence number for node */
    slsp_cksum_t slsp_node_cksum;		/* LSP checksum (0 if none) */

    /* Lifetime time out time.  Usually a copy of slsp_node_life */
    time_t slsp_node_life_timeout;

    /* LSP data */
    slsp_db_as slsp_node_aslist;		/* head of the AS list */
    slsp_db_link slsp_node_linklist;		/* head of the links list */

    /* Transmit data */
    time_t slsp_node_xmt_time;			/* time to reflood this node */
    slsp_bits slsp_node_xmt_bits;		/* who to flood to */
#define	slsp_node_xmt_nbits	slsp_node_xmt_bits.slsp_bit_n_set

    /* computed next hops for node */
    int slsp_node_n_nexthops;
    sockaddr_un *slsp_node_nexthops[RT_N_MULTIPATH];
    metric_t slsp_node_cost;			/* SPF computed cost to node */

    /* Routing table entry for the node */
    rt_entry *slsp_node_rt;
} slsp_db_node;

/*
 * Node flags
 */
#define	SLSP_NODEF_RTTYPE_ALT	0x1		/* using alt router */
#define	SLSP_NODEF_LOCAL_LINK	0x2		/* local net node */

/*
 * Types of nodes.
 */
#define	SLSP_LSP_PLACEHOLDER	0	/* mentioned in other LSP's only */
#define	SLSP_LSP_TIMEDOUT	1	/* node is zeroed, in final timeout */
#define	SLSP_LSP_ROUTER		2	/* router LSP */
#define	SLSP_LSP_LOCALRTR	3	/* local router LSP */
#define	SLSP_LSP_NET		4	/* next LSP */
#define	SLSP_LSP_NBRNET		5	/* local net LSP originated by nbr */
#define	SLSP_LSP_LOCALNET	6	/* node is local broadcast interface */

#define	SLSP_IS_NET_LSP(np)	((np)->slsp_node_type >= SLSP_LSP_NET)

#define	SLSP_IS_LOCAL_LSP(np) \
    ((np)->slsp_node_type == SLSP_LSP_LOCALRTR \
      || (np)->slsp_node_type == SLSP_LSP_LOCALNET)

#define	SLSP_IS_ACTIVE_LSP(np) \
    ((np)->slsp_node_type >= SLSP_LSP_ROUTER)

/*
 * Types of route lists.
 */
#define	SLSP_NRT_NONE		0	/* not on a route list */
#define	SLSP_NRT_UNCONNECTED	1	/* on the unconnected list */
#define	SLSP_NRT_CANDIDATE	2	/* on the candidate list (TENT) */
#define	SLSP_NRT_CONNECTED	3	/* on the connected list (PATHS) */

/*
 * The length of a timer name.  Could be Expire.xxx.xxx.xxx.xxx or
 * Hello.xxx.xxx.xxx.xxx
 */
#define	SLSP_TIMER_NAME_LEN	24

/*
 * This structure is used for placeholders in the I/O tree.  It
 * also forms the start of the slsp_neighbour structure.
 */
typedef struct _slsp_neighbour_head {
    struct _slsp_neighbour *slsp_nbr_head_left;		/* zero tree node */
    struct _slsp_neighbour *slsp_nbr_head_right;	/* one tree node */
    u_long slsp_nbr_head_mask;				/* bit to test */
    sockaddr_un *slsp_nbr_head_addr;	/* nbr address */
    u_short slsp_nbr_head_index;	/* neighbour index */
    byte slsp_nbr_head_offset;		/* offset into bit array */
    byte slsp_nbr_head_bitmask;		/* bit in byte */
    byte slsp_nbr_head_type;		/* nbr type (p2p, bcast, bcast nbr) */
    byte slsp_nbr_head_state;		/* neighbour state */
} slsp_neighbour_head;

/*
 * The slsp neighbour structure.  One of these exists for
 * each interface over which we are running the protocol, for
 * each known neighbour on a broadcast interface, and for p2p
 * neighbours on multiaccess networks.
 */
typedef struct _slsp_neighbour {
    slsp_neighbour_head slsp_nbr_head;
#define	slsp_nbr_left	slsp_nbr_head.slsp_nbr_head_left
#define	slsp_nbr_right	slsp_nbr_head.slsp_nbr_head_right
#define	slsp_nbr_mask	slsp_nbr_head.slsp_nbr_head_mask
#define	slsp_nbr_addr	slsp_nbr_head.slsp_nbr_head_addr
#define	slsp_nbr_index	slsp_nbr_head.slsp_nbr_head_index
#define	slsp_nbr_offset	slsp_nbr_head.slsp_nbr_head_offset
#define	slsp_nbr_bitmask	slsp_nbr_head.slsp_nbr_head_bitmask
#define	slsp_nbr_type	slsp_nbr_head.slsp_nbr_head_type
#define	slsp_nbr_state	slsp_nbr_head.slsp_nbr_head_state

    /* Interface this is running over */
    if_addr *slsp_nbr_if;			/* interface of neighbour */

    /* Chain pointers and a pointer to our instance */
    struct _slsp_instance *slsp_nbr_instance;	/* instance he belongs to */
    struct _slsp_neighbour *slsp_nbr_parent;	/* parent nbr (bcast only) */
#define	slsp_nbr_list	slsp_nbr_parent		/* child nbr (bcast only) */
    u_int slsp_nbr_n_hello;			/* # of adj. nbrs on bcast if */
    struct _slsp_neighbour *slsp_nbr_next;	/* sibling nbr */
    struct _slsp_neighbour *slsp_nbr_io_next;	/* next nbr in I/O tree */

    slsp_link_parms slsp_nbr_parms;		/* configured parameters */
#define	slsp_nbr_trace_options	slsp_nbr_parms.slsp_lp_trace_options
#define	slsp_nbr_hellointerval	slsp_nbr_parms.slsp_lp_hellointerval
#define slsp_nbr_routerdeadinterval slsp_nbr_parms.slsp_lp_routerdeadinterval
#define	slsp_nbr_cost		slsp_nbr_parms.slsp_lp_cost
#define	slsp_nbr_priority	slsp_nbr_parms.slsp_lp_priority

    /* Stuff worth knowing from incoming hello's */
    time_t slsp_nbr_holdtime;		/* hold time received in hello */
    u_int slsp_nbr_his_priority;	/* Priority from broadcast hello */
#define	slsp_nbr_as	slsp_nbr_his_priority	/* AS received in ptp hello */

    /* Holdtime expiry support */
    time_t slsp_nbr_last_hello;		/* Time we got last hello */
    time_t slsp_nbr_last_ihu;		/* Time we got last IHU */
    time_t slsp_nbr_expire_time;	/* Next time we expire */
    task_timer *slsp_nbr_expire_timer;	/* Timer for holdtime expiry's */
    char slsp_nbr_expire_timer_name[SLSP_TIMER_NAME_LEN];

    /* Hello packets.  We store a copy of the hello's we send and receive */
    task_timer *slsp_nbr_hello_timer;	/* Hello timer */
    char slsp_nbr_hello_timer_name[SLSP_TIMER_NAME_LEN];
    byte *slsp_nbr_send_hello;		/* Hello we send to him */
    size_t slsp_nbr_send_hello_len;	/* Length of the sent hello */
    byte *slsp_nbr_recv_hello;		/* Hello we heard from him */
    size_t slsp_nbr_recv_hello_len;	/* Length of the received hello */

    sockaddr_un *slsp_nbr_id;		/* neighbour ID */
    sockaddr_un *slsp_nbr_dr_addr;	/* his/our idea of DR address */
    struct _slsp_neighbour *slsp_nbr_dr;	/* the designated router */
    slsp_db_link *slsp_nbr_link;	/* the associated local node link */
    slsp_db_node *slsp_nbr_node;	/* the local node for the interface */
    slsp_full_seq_q *slsp_nbr_fsq;	/* full sequence numbers queue entry */
    u_int slsp_nbr_n_adjacent;		/* # of nbrs adjacent to DR */
} slsp_neighbour;

/*
 * Neighbour types
 */
#define	SLSP_NTYPE_PLACEHOLDER	0	/* placeholder for shitty packets */
#define	SLSP_NTYPE_PTP		1	/* ptp neighbour */
#define	SLSP_NTYPE_PTP_PEER	2	/* ptp neighbour on multiaccess LAN */
#define	SLSP_NTYPE_BCAST	3	/* broadcast LAN */
#define	SLSP_NTYPE_BCAST_NBR	4	/* neighbour on broadcast LAN */

#define	SLSP_NBR_PTP_TYPE(nbr)	((nbr)->slsp_nbr_type <= SLSP_NTYPE_PTP_PEER)

/*
 * Neighbour state
 */
#define	SLSP_NBR_STATE_DOWN	0	/* neighbour not heard from */
#define	SLSP_NBR_STATE_HELLO	1	/* heard hello from this guy */
#define	SLSP_NBR_STATE_IHU	2	/* heard IHU from this guy */
#define	SLSP_NBR_STATE_ADJACENT	3	/* neighbour is fully adjacent */

#define	SLSP_NBR_GOT_HELLO(nbr) \
    ((nbr)->slsp_nbr_state && (nbr)->slsp_nbr_state != SLSP_NBR_STATE_IHU)

#define	SLSP_NBR_GOT_IHU(nbr)	((nbr)->slsp_nbr_state >= SLSP_NBR_STATE_IHU)

#define	SLSP_NBR_NSTATE_HELLO(nbr)	((nbr)->slsp_nbr_state + 1)

#define	SLSP_NBR_NSTATE_IHU(nbr)	((nbr)->slsp_nbr_state + 2)

/*
 * The slsp gateway structure.  Used for configuring psuedo-ptp peers
 */
typedef struct _slsp_gateway {
    struct _slsp_gateway *slsp_gw_next;
    sockaddr_un *slsp_gw_addr;		/* address of neighbour */
    slsp_neighbour *slsp_gw_nbr;	/* pointer to neighbour struct */
    slsp_link_parms slsp_gw_parms;	/* link parms for neighbour */
#define	slsp_gw_trace_options	slsp_gw_parms.slsp_lp_trace_options
#define	slsp_gw_hellointerval	slsp_gw_parms.slsp_lp_hellointerval
#define slsp_gw_routerdeadinterval slsp_gw_parms.slsp_lp_routerdeadinterval
#define	slsp_gw_cost		slsp_gw_parms.slsp_lp_cost
#define	slsp_gw_priority	slsp_gw_parms.slsp_lp_priority
} slsp_gateway;

/*
 * SLSP stats structure, used to keep random numbers.
 */
typedef struct _slsp_statistics {
    u_long slsp_st_in_lsps;		/* received LSPs */
    u_long slsp_st_out_lsps;		/* sent LSPs */
    u_long slsp_st_in_seqs;		/* received sequence number packets */
    u_long slsp_st_out_seqs;		/* sent sequence number packets */
    u_long slsp_st_fucked_lsps;		/* screwed up LSPs */
    u_long slsp_st_in_hellos;		/* received ptp hellos */
    u_long slsp_st_out_hellos;		/* sent ptp hellos */
    u_long slsp_st_in_ihus;		/* received ptp ihus */
    u_long slsp_st_out_ihus;		/* sent ptp ihus */
} slsp_statistics;

/*
 * The SLSP instance structure.  There exists one of these for each
 * configured slsp instance.  This includes the policy by which we
 * tell if a neighbour qualifies for this instance, the neighbour
 * list, the heads of all the timer queues and the head of the
 * database list.
 */
typedef struct _slsp_instance {
    slsp_list slsp_lists;		/* head of node db timer lists */
#define	slsp_connected		slsp_lists.slsp_rt_list
    struct _slsp_instance *slsp_next;	/* next instance in list */
    u_int slsp_n_connected;		/* number of nodes on connected list */
    slsp_neighbour *slsp_nbrs;		/* list of neighbours for this node */
    slsp_link_parms slsp_def_parms;	/* default link parameters */
#define	slsp_trace_options	slsp_def_parms.slsp_lp_trace_options
#define	slsp_def_hellointerval	slsp_def_parms.slsp_lp_hellointerval
#define	slsp_def_routerdeadinterval	slsp_def_parms.slsp_lp_routerdeadinterval
#define	slsp_def_cost		slsp_def_parms.slsp_lp_cost
#define	slsp_def_priority	slsp_def_parms.slsp_lp_priority
    slsp_db_node *slsp_local_node;	/* local node for this instance */
    slsp_db_node *slsp_nodes;		/* node database tree root */
    slsp_gateway *slsp_gateways;	/* p2p pseudo-neighbours */
    adv_entry *slsp_policy;		/* policy for interfaces to run on */
    pref_t slsp_preference;		/* preference for this instance */
    gw_entry slsp_gw;			/* GW block for the instance */
#define	slsp_task	slsp_gw.gw_task
#define	slsp_addr	slsp_gw.gw_addr
    sockaddr_un *slsp_mask;		/* mask for this instance */
    sockaddr_un *slsp_rtmask;		/* route mask for this instance */

    /* Head of full sequence numbers init queue */
    slsp_full_seq_q slsp_full_queue;
#define	slsp_full_seq_entries	slsp_full_queue.slsp_fq_n_entries
    byte *slsp_full_seq_pkt;		/* full sequence numbers packet */
    size_t slsp_full_seq_pkt_len;	/* length of sequence numbers packet */
    time_t slsp_full_seq_pkt_time;	/* time packet formatted */
    u_int slsp_needs_full_seq;		/* number of guys needing fsp */

    /* Neighbour bit maintenance */
    slsp_neighbour *slsp_bit_nbrs[SLSP_MAX_NEIGHBOURS];
    slsp_bits slsp_flood_bits;		/* array of bits of guys we flood to */
#define	slsp_n_flood	slsp_flood_bits.slsp_bits_n_set

    /* Instance timers */
    task_timer *slsp_timer_xmt;		/* (Re)Transmit timer */
    task_timer *slsp_timer_life;	/* LSP lifetime expiry timer */
    task_timer *slsp_timer_spf;		/* SPF timer, next time to run SPF */

    /*
     * Lifetime stuff
     */
    time_t slsp_next_life_timeout;	/* When we expect timeout to occur */

    /* Xmt queue time/job */
    task_job *slsp_job_xmt;
    time_t slsp_next_xmt_time;

    /* SPF times */
    time_t slsp_spf_lastdone;		/* Last time SPF was run */
    time_t slsp_spf_scheduled;		/* Time next SPF was scheduled */
    time_t slsp_spf_requested;		/* Last time SPF was requested */

    flag_t slsp_flags;
    slsp_statistics slsp_stats;		/* statistics */
} slsp_instance;

#define	SLSPF_SPF_JOB		0x01	/* SPF job has been scheduled */
#define	SLSPF_SPF_TIMER		0x02	/* SPF timer is running */
#define	SLSPF_SPF		(SLSPF_SPF_JOB|SLSPF_SPF_TIMER)
#define	SLSPF_DELETED		0x04	/* Instance tentatively deleted */
#define	SLSPF_XMT_JOB		0x08	/* Xmt job has been scheduled */
#define	SLSPF_XMT_TIMER		0x10	/* Xmt timer is running */
#define	SLSPF_XMT_THROTTLE	0x20	/* Throttling */

/*
 * Check if an ID belongs to this instance
 */
#define	SLSP_INSTANCE_ID(inp, addr) \
    ((sock2ip((inp)->slsp_mask) & sock2ip(addr)) \
      == (sock2ip((inp)->slsp_addr) & sock2ip((inp)->slsp_mask)))


/*
 * Declarations for functions and variables the parser needs to see.
 * All of these are in slsp_init.c
 */
extern trace *slsp_global_trace_options;

extern const bits slsp_trace_types[];

extern int doing_slsp;

PROTOTYPE(slsp_parse_instance_alloc,
	  extern slsp_instance *,
	  (sockaddr_un *,
	   sockaddr_un *,
	   sockaddr_un *));
PROTOTYPE(slsp_parse_instance_check,
	  extern int,
	  (slsp_instance **,
	   char *));
PROTOTYPE(slsp_parse_gateway_alloc,
	  extern slsp_gateway *,
	  (slsp_instance *,
	   sockaddr_un *));
PROTOTYPE(slsp_parse_gateway_check,
	  extern int,
	  (slsp_instance *,
	   slsp_gateway **,
	   char *));
PROTOTYPE(slsp_config_free,
	  extern void,
	  (config_entry *));
PROTOTYPE(slsp_init,
	  extern void,
	  (void));
PROTOTYPE(slsp_var_init,
	  extern void,
	  (void));

/*
 * %(Copyright)
 */
