/*
 * $Id: targets.h,v 1.13.2.4 1995/05/25 01:48:55 jch Exp $
 */

/* %(Copyright.header) */


/* Target definitions. */

typedef struct _td_entry {
    struct _td_entry *td_forw, *td_back;
    u_short	td_flags;
    u_short	td_metric;
    rt_entry	*td_rt;
} td_entry;

#define	TDF_HOLDDOWN	0x8000	/* This entry is in holddown */
#define	TDF_POISON	0x4000	/* This entry is in poison reverse */
#define	TDF_CHANGED	0x2000	/* This entry is changed */

#define	target_set_holddown(tdp, count) { \
	 (tdp)->td_flags = TDF_HOLDDOWN|TDF_CHANGED; \
	 (tdp)->td_metric = (count); \
     }

#define	target_set_poison(tdp, count) { \
	 (tdp)->td_flags = TDF_POISON|TDF_CHANGED; \
	 (tdp)->td_metric = (count); \
     }

#define	target_set_metric(tdp, metric) { \
	 (tdp)->td_flags = TDF_CHANGED; \
	 (tdp)->td_metric = (metric); \
     }

#define	TD_ALLOC(tdp)	tdp = (td_entry *) task_block_alloc(target_td_block)
#define	TD_FREE(tdp)	task_block_free(target_td_block, tdp)

#define	TD_TSI_GET(tlp, rth, tdp)	rttsi_get(rth, (tlp)->target_rtbit, (byte *) &tdp);
#define	TD_TSI_SET(tlp, rth, tdp)	rttsi_set(rth, (tlp)->target_rtbit, (byte *) &tdp);

#define	TD_ENQUE(tlp, tdp)	INSQUE(tdp, &(tlp)->target_td)
#define	TD_DEQUE(tdp)		REMQUE(tdp)

#define	TD_CLEANUP(tlp, tdp, pending) \
	{ \
	    rttsi_reset((tdp)->td_rt->rt_head, (tlp)->target_rtbit); \
	    if (pending) { \
		(void) rtbit_reset_pending((tdp)->td_rt, (tlp)->target_rtbit); \
	    } else { \
		(void) rtbit_reset((tdp)->td_rt, (tlp)->target_rtbit); \
	    } \
	    TD_DEQUE(tdp); \
	    TD_FREE(tdp); \
	}

#define	TD_LIST(tdp, list) \
	{ \
	    register td_entry *Xtdp_next = (list)->td_forw; \
	    while (Xtdp_next != (list)) { \
		(tdp) = Xtdp_next; \
		Xtdp_next = Xtdp_next->td_forw;
#define	TD_LIST_END(tdp, list) } }

typedef struct _target {
    struct _target *target_forw;	/* Pointer to the next one */
    struct _target *target_back;	/* Pointer to the last one */
    sockaddr_un	**target_dst;		/* Destination */
    sockaddr_un	**target_src;		/* Source */
    if_addr	*target_ifap;		/* Interface */
    gw_entry	*target_gwp;		/* Gateway if available */
    flag_t	target_rtbit;		/* Bit for this target */
    flag_t	target_flags;		/* Protocol dependent flags */
    task	*target_task;		/* Task that owns us */
    td_entry	target_td;		/* Head of list of routes to announce */
    _PROTOTYPE(target_reset,
	       void,
	       (task *,
		struct _target *));	/* Routine to clean up a target being freed */
    
} target;

#define	TARGETF_BROADCAST	0x01		/* This is a broadcast address */
#define	TARGETF_SOURCE		0x02		/* This is a P2P client */
#define	TARGETF_SUPPLY		0x04		/* We supply updates to this client */
#define	TARGETF_ALLINTF		0x08		/* We want to see all interfaces */
#define	TARGETF_POLICY		0x10		/* Initial policy has been run */

#define	TARGETF_USER4		0x1000
#define	TARGETF_USER3		0x2000
#define	TARGETF_USER2		0x4000
#define	TARGETF_USER1		0x8000		/* For protocol use */


#define	TARGET_LIST(tlp, list) \
	{ \
	    for ((tlp) = (list)->target_forw; (tlp) != (list); (tlp) = (tlp)->target_forw)
#define	TARGET_LIST_END(tlp, list) \
	    if ((tlp) == (list)) { \
		tlp = (target *) 0; \
	    } \
	}

PROTOTYPE(target_locate,
	  extern target *,
	  (target *,
	   if_addr *,
	   gw_entry *));
PROTOTYPE(target_free_list,
	  extern void,
	  (task *,
	   target *));
PROTOTYPE(target_build,
	  extern int,
	  (task *,
	   target *y,
	   gw_entry *,
	   flag_t,
	   _PROTOTYPE(dump,
		      void,
		      (FILE *,
		       rt_head *,
		       void_t,
		       const char *))));
PROTOTYPE(target_dump,
	  extern void,
	  (FILE *,
	   target *,
	   const bits *));

extern block_t target_td_block;
extern const bits target_entry_bits[];

/*
 * %(Copyright)
 */
