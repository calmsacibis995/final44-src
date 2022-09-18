/*
 *  $Id: inet_multi.h,v 1.2 1995/01/26 07:52:40 pusateri Exp $
 */

/*%Copyright%*/

#define	IPMULTI_PROTO_MOSPF	0	/* Multicast Extensions to OSPF */
#define	IPMULTI_PROTO_DVMRP	1	/* Distance Vector Multicast Routing */
#define	IPMULTI_PROTO_PIM	2	/* Protocol Independent Multicasting */
#define	IPMULTI_PROTO_CBT	3	/* Core Based Trees */
#define	IPMULTI_PROTO_MAX	4

#define IPMULTI_BIT(proto)      ((flag_t) (1 << (proto)))

/*
 * Prune List for sending and timing out prunes
 */

typedef struct _prune_list {
    struct	_prune_list *tq_forw, *tq_back;
    struct	_prune_list *if_forw, *if_back;
    if_addr	*ifap;
    struct	_mfc *mfcp;
    int		pending;
    int		holdtime;
    time_t	prune_time;
} prune_list;


#define PRUNE_TQ_ENQ(elem, pred) { \
    register prune_list *Xe = elem; \
    register prune_list *Xp = pred; \
    Xp->tq_forw = (Xe->tq_forw = (Xe->tq_back = Xp)->tq_forw)->tq_back = Xe; \
}

#define PRUNE_TQ_DEQ(elem) { \
    register prune_list *Xe = elem; \
    (Xe->tq_back->tq_forw = Xe->tq_forw)->tq_back = Xe->tq_back; \
}

#define PRUNE_IF_ENQ(elem, pred) { \
    register prune_list *Xe = elem; \
    register prune_list *Xp = pred; \
    Xp->if_forw = (Xe->if_forw = (Xe->if_back = Xp)->if_forw)->if_back = Xe; \
}

#define PRUNE_IF_DEQ(elem) { \
    register prune_list *Xe = elem; \
    (Xe->if_back->if_forw = Xe->if_forw)->if_back = Xe->if_back; \
}

#define	PRUNE_LIST(gp, list)	{ for (gp = (list)->tq_forw; gp != list; gp = gp->tq_forw)
#define PRUNE_LIST_END(gp, list)	if (gp == list) gp = (prune_list *) 0; }

/*
 * The MFC Source list structure is a linked list of MFC's that hang off
 * the unicast route back to the source. This is convenient when the
 * unicast routing table changes. PIM is notified via the flash routine
 * and decide if a new upstream interface is needed.
 */

typedef struct _mfc_src_list {
    struct _mfc_src_list *forw;
    struct _mfc_src_list *back;
    struct _mfc *mfcp;
} mfc_src_list;

extern block_t mfc_unicast_block_index;


/* A multicast forwarding cache entry */

typedef struct _mfc {
    struct	_mfc *left;		/* tree branches */
    struct	_mfc *right;		/* tree branches */
    u_long	mfc_src;		/* source */
    u_long	mfc_mask;		/* for use in building the tree */
    int		mfc_lastuse;		/* previous use count from the kernel */
    int		mfc_use;		/* most recent use count */
    time_t	mfc_ctime;		/* creation time */
    time_t	mfc_rtime;		/* last refresh time */
    if_addr	*upstream_ifap;		/* the upstream interface */
    int		ds_count;		/* the number of downstream intfs */
    struct	_downstream *ds;	/* the list of downstream interfaces */
    struct	_group_node *mfc_group;	/* backpointer to head of tree */
    u_long	mfc_proto;		/* current protocols using this mfc */
    void	(*mfc_callback)();	/* routine to call when RTM_GET rx'ed */
					/* PIM section */
    struct	_prune_list *prune_up;	/* pruned upstream */
    struct	_prune_list prune_down;	/* head of interface prune list */
    struct	_assert_list *pim_assert;/* store 1st assert received */
    struct	_mfc_src_list *msl;	/* ptr back to unicast route to src */
    u_long	rpf_addr;		/* addr to use when sending upstream */
} mfc;

typedef struct _group_node {
    struct	_group_node *left;	/* tree branches */
    struct	_group_node *right;	/* tree branches */
    u_long	group_key;		/* group address */
    u_long	group_mask;		/* for use in building the tree */
    u_short	src_node_count;		/* number sources in this source tree */
    u_short	graft_pending;		/* awaiting graft ack for this group */
    struct	_mfc *src_head;		/* this points to head of source tree */
} group_node;

typedef struct _downstream {
    struct	_downstream *forw;	/* linked list off mfc */
    struct	_downstream *back;	/* linked list off mfc */
    struct	_downstream *tq_forw;	/* linked list for timer queue */
    struct	_downstream *tq_back;	/* linked list for timer queue */
    sockaddr_un	*ds_addr;		/* address of downstream intf or nbr */
    u_short	ds_ttl;			/* minimum ttl - 0 disabled */
    u_short	ds_flags;		/* flags: nbr, age, grafts, etc. */
    u_long	ds_proto;		/* protocols in RTPROTO_BIT */
    int		ds_ifindex;		/* ifindex for tunnels */
    time_t	ds_timeout;		/* timeout value for this interface */
} downstream;

/*
 * Assert List for receiving and timeout out asserts
 */

typedef struct _assert_list {
    struct	_assert_list *forw, *back;
    mfc		*mfcp;
    if_addr	*ifap;
    u_long	rpf_addr;
    time_t	assert_time;
    u_long	preference;
    u_long	metric;
    int		rpbit;
} assert_list;


/*
 * Used to scan mfc entries when aging
 */

#define	MFC_TIMEOUT_LIST(gp, list)	{ for (gp = (list)->forw; gp != list; gp = gp->forw)
#define MFC_TIMEOUT_LIST_END(gp, list)	if (gp == list) gp = (mfc *) 0; }

/*
 * Used to scan the downstream interface list
 */

#define	DOWNSTREAM_LIST(gp, list)	{ for (gp = (list)->forw; gp != list; gp = gp->forw)
#define DOWNSTREAM_LIST_END(gp, list)	if (gp == list) gp = (downstream *) 0; }

/*
 * returned structure when locating upstream interfaces and neighbors
 */

typedef struct _upstream {
    if_addr	*ifap;
    sockaddr_un	*nbr;
    int		protocol;
    metric_t	metric;
} upstream;


PROTOTYPE(mfc_init,
	  extern void,
	  (void));

PROTOTYPE(mfc_alloc_node,
	  extern mfc *,
	  (void));

PROTOTYPE(mfc_alloc_downstream,
	  extern downstream *,
	  (void));

PROTOTYPE(mfc_free_downstream,
	  extern void,
	  (downstream *));

PROTOTYPE(mfc_add_node,
	  extern int,
	  (sockaddr_un *, mfc *));

PROTOTYPE(mfc_delete_node,
	  extern void,
	  (mfc *));

PROTOTYPE(mfc_dump,
	  extern void,
	  (task *,
	   FILE *));

PROTOTYPE(mfc_terminate,
	  extern void,
	  (void));

PROTOTYPE(mfc_visit,
	  extern void,
	  (_PROTOTYPE(func,
		      void,
		      (mfc *,
		       caddr_t)),
	  caddr_t));

PROTOTYPE(mfc_source_visit,
	  extern void,
	  (group_node *,
	  _PROTOTYPE(func,
		     void,
		     (mfc *,
		      caddr_t)),
	  caddr_t));

PROTOTYPE(mfc_locate_group,
	  extern group_node *,
	  (u_long));

PROTOTYPE(mfc_locate_mfc,
	  extern mfc *,
	  (sockaddr_un *,
	   sockaddr_un *));

PROTOTYPE(mfc_source_link_unicast,
	  extern void,
	  (task *,
	   mfc *));

PROTOTYPE(mfc_source_unlink_unicast,
	  extern void,
	  (task *,
	   mfc *));

