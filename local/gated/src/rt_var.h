/*
 * $Id: rt_var.h,v 1.17.2.2 1995/02/14 22:08:46 jch Exp $
 */

/* %(Copyright.header) */


/* A number is allocated by each routing protocol per destination, one for */
/* link-state protocols, one per peer for peer/neighbor based protocols, */
/* and one per interface and sourcegateway for distance vector protocols. */

/* These bits index into the rt_bits structure in each rt_entry and into */
/* the rt_unreach array of unsigned chars in each rt_head.  The intended */
/* use is that a protocol will set it's bit when it decides to announce a */
/* route to a destination and reset it when it is nolonger announcing it. */
/* When a bit is reset the count of set bits in the rt_entry is */
/* decremented.  When this count reaches zero, the count of routes */
/* announcing a route to this destination is decremented.  If an rt_entry */
/* is scheduled for delete when it's count of announcement bits reaches */
/* zero it is released. */

/* The intended use of the rt_unreach array is that the protocol sets a */
/* value in it when a route to a destination goes into holddown and counts */
/* it down during periodic events (such as sending non-flash updates). */
/* When it's value reaches zero, the announcement bit in the held-down */
/* rt_entry is reset. */

/* Don't change this value here, change it in the config file */
#define	RTTSI_SIZE	16

typedef struct _rt_tsi {
    struct _rt_tsi *tsi_next;
    byte tsi_tsi[RTTSI_SIZE];
} rt_tsi;

typedef struct _rtbit_info {
    task	*rtb_task;	/* Task that owns this bit */
    void_t	rtb_data;	/* Task specific data */
    _PROTOTYPE(rtb_dump,
	       void,
	       (FILE *,
		rt_head *,
		void_t,
		const char *));	/* To display what it means */
    u_short	rtb_index;	/* Offset to bytes */
    u_short	rtb_length;	/* Number of bytes */
} rtbit_info;


struct rtaf_info {
    u_int	rtaf_routes;		/* Count of rt_entrys */
    u_int	rtaf_dests;	       	/* Count of rt_heads */
    u_int	rtaf_actives;		/* Count of active rt_entrys */
    u_int	rtaf_holddowns;		/* Count of holddown rt_entrys */
    u_int	rtaf_hiddens;		/* Count of hidden rt_entrys */
    u_int	rtaf_deletes;		/* Count of deleted rt_entrys */

    /* XXX - Should have all the family specific routines in it */
};
extern struct rtaf_info rtaf_info[AF_MAX];


PROTOTYPE(rt_table_delete,
	  extern void,
	  (rt_head *));
PROTOTYPE(rt_table_add,
	  extern void,
	  (rt_head *rth));
PROTOTYPE(rt_table_init,
	  extern void,
	  (void));
PROTOTYPE(rt_table_dump,
	  extern void,
	  (task *,
	   FILE *));
#if	RT_N_MULTIPATH > 1
PROTOTYPE(rt_routers_compare,
	  extern int,
	  (rt_entry *,
	   sockaddr_un **));
#else	/* RT_N_MULTIPATH > 1 */
#define	rt_routers_compare(rt, routers)	sockaddrcmp(RT_ROUTER(rt), routers[0])
#endif	/* RT_N_MULTIPATH */

/* Remove the current entry from the change list */
#define	RTLIST_REMOVE(rtl) \
	{ \
	    if (*Xrthp) { \
		*Xrthp = (void_t) 0; \
		(rtl)->rtl_root->rtl_count--; \
	    } \
	}

/* True if this is currently the last entry on the list */
#define	RTLIST_ATEND(rtl) (Xrthp == (rtl)->rtl_fillp && !(rtl)->rtl_next)

extern rt_list *rt_change_list;
extern int rt_n_changes;

#ifdef	PROTO_ISODE_SNMP
PROTOTYPE(rt_mib_init,
	  extern void,
	  (void));
#endif	/* PROTO_ISODE_SMUX */
#ifdef	PROTO_SNMP
PROTOTYPE(rt_mib_free_rt,
	  extern void,
	  (rt_entry *));
#endif	/* PROTO_SNMP */

/**/

/* Static routes */

PROTOTYPE(rt_static_cleanup,
	  extern void,
	  (task *));
PROTOTYPE(rt_static_reinit,
	  extern void,
	  (task *));
PROTOTYPE(rt_static_ifachange,
	  extern void,
	  (task *));
PROTOTYPE(rt_static_terminate,
	  extern void,
	  (task *));
PROTOTYPE(rt_static_dump,
	  extern void,
	  (task *,
	   FILE *));
PROTOTYPE(rt_static_init,
	  extern void,
	  (task *));

/**/

/* Aggregate routes */

#define	rt_aggregate_head(aggr_rt)	((rt_aggr_head *) aggr_rt->rt_data)

PROTOTYPE(rt_aggregate_init,
	  extern void,
	  (void));
PROTOTYPE(rt_aggregate_flash,
	  extern void,
	  (rt_list *,
	   u_int));
PROTOTYPE(rt_aggregate_rt_dump,
	  extern void,
	  (FILE *,
	   rt_entry *));
PROTOTYPE(rt_aggregate_rth_dump,
	  extern void,
	  (FILE *,
	   rt_head *));

/*
 * %(Copyright)
 */
