/*
 *  $Id$
 */

/*%Copyright%*/

#ifdef	PROTO_IGMP
/*
 * Internet Group Management Protocol
 *  
 */
struct igmp {
        u_int8          igmp_type;      /* version, type info  */
        u_int8          igmp_code;      /* used in dvmrp and pim */
        u_int16         igmp_cksum;     /* checksum */
        u_int32		igmp_group;     /* group address */
};

#define IGMP_UNDEFINED		0x10	/* not defined */
#define IGMP_MEMBERSHIP_QUERY	0x11	/* version, type */
#define IGMP_MEMBERSHIP_REPORT	0x12
#define IGMP_PROTO_DVMRP	0x13
#define IGMP_PROTO_PIM		0x14
#define	IGMP_CISCO_TRACE	0x15
#define IGMP_NEW_MEMBERSHIP_REPORT	0x16
#define IGMP_MEMBERSHIP_LEAVE	0x17
#define IGMP_MTRACE_RESPONSE	0x1e
#define IGMP_MTRACE_REQUEST	0x1f
#define	IGMP_MAX_TYPE		0x20
#define	IGMP_BASE_TYPE		IGMP_UNDEFINED

#define IGMP_MIN_PACKET_LENGTH		8
#define	IGMP_MAX_HOST_REPORT_DELAY	10

#define	IGMP_ENABLED		0x01	/* IGMP protocol status bit */

extern int igmp_config_status;		/* if IGMP is enabled in new config */

#define	IGMP_ALL_HOSTS		0xe0000001	/* 224.0.0.1 */
#define	IGMP_ALL_ROUTERS	0xe0000002	/* 224.0.0.2 */

/*
 * local group database
 */

struct group_list {
    struct group_list *forw, *back;
    struct in_addr group_addr;		/* Group address */
    struct in_addr last_addr;		/* Last host to report group */
#define	IGMP_NEW_NEIGHBORS	0x1
    flag_t group_flags;			/* status info about group */
    time_t refresh_time;		/* Time of last refresh */
};

/*
 * Used to scan the local group database
 */

#define	GROUP_LIST(gp, list)	{ for (gp = (list)->forw; gp != list; gp = gp->forw)
#define GROUP_LIST_END(gp, list)	if (gp == list) gp = (struct group_list *) 0; }

/*
 * defines used by parser
 */

#define	IGMP_LIMIT_QUERYINTERVAL	1, 0xffff
#define	IGMP_LIMIT_TIMEOUTINTERVAL	1, 0xffff

#define	IGMP_CONFIG_ENABLE		1
#define	IGMP_CONFIG_DISABLE		2
#define	IGMP_CONFIG_MAX			3

extern adv_entry *igmp_int_policy;		/* IGMP control info */

#define IFPS_DR_STATUS		IFPS_KEEP1
						/* IGMP group database/intf */
#define igmp_if_group_list	ifa_ps[RTPROTO_IGMP].ips_datas[0]
#define igmp_if_timer_timeout	ifa_ps[RTPROTO_IGMP].ips_datas[1]
#define igmp_if_proto		ifa_ps[RTPROTO_IGMP].ips_datas[2]

/*
 * tracing declarations
 */

extern trace *igmp_trace_options;	/* IGMP tracing configuration */
extern const bits igmp_trace_types[];	/* List of IGMP specific trace flags */

#define	TR_IGMP_INDEX_PACKETS	0	/* All packets */
#define	TR_IGMP_INDEX_QUERY	1	/* Query packets */
#define	TR_IGMP_INDEX_REPORT	2	/* New and old Report packets */
#define	TR_IGMP_INDEX_LEAVE	3	/* Leave packets */
#define	TR_IGMP_INDEX_MTRACE	4	/* Cisco & traceroute mcast packets */

#define	TR_IGMP_DETAIL_QUERY	TR_DETAIL_1
#define	TR_IGMP_DETAIL_REPORT	TR_DETAIL_2
#define	TR_IGMP_DETAIL_LEAVE	TR_DETAIL_3
#define	TR_IGMP_DETAIL_MTRACE	TR_DETAIL_4


/*
 * protocol defaults
 */

extern int igmp_default_queryinterval;		/* default query interval */
extern int igmp_default_timeoutinterval;	/* default timeout interval */


/*
 * Group Change defines
 */

#define	IGMP_GROUP_ADDED	1
#define	IGMP_GROUP_REMOVED	2

/**/
PROTOTYPE(igmp_init,
	  extern void,
	  (void));
PROTOTYPE(igmp_var_init,
	  extern void,
	  (void));
PROTOTYPE(igmp_enable_dr_status,
	  extern void,
	  (if_addr *));
PROTOTYPE(igmp_disable_dr_status,
	  extern void,
	  (if_addr *));
PROTOTYPE(igmp_enable_mrouting,
	  extern void,
	  (void));
PROTOTYPE(igmp_disable_mrouting,
	  extern void,
	  (void));
PROTOTYPE(igmp_enable_asserts,
	  extern void,
	  (void));
PROTOTYPE(igmp_disable_asserts,
	  extern void,
	  (void));
#ifdef	KRT_IPMULTI_TTL0
PROTOTYPE(igmp_add_vif,
	  extern void,
	  (if_addr *,
	   sockaddr_un *,
	   u_int32,
	   u_int32));
PROTOTYPE(igmp_del_vif,
	  extern void,
	  (if_addr *));
PROTOTYPE(igmp_lookup_task,
	  extern task *,
	  (void));
#endif	/* KRT_IPMULTI_TTL0 */
PROTOTYPE(igmp_unregister_recv,
	  extern int,
	  (int));
PROTOTYPE(igmp_register_recv,
	  extern int,
	  (int,
	  _PROTOTYPE(func,
		     void,
		     (if_addr *,
		      struct igmp *,
		      int))));
PROTOTYPE(igmp_register_group_change,
	  extern int,
	  (_PROTOTYPE(func,
		     void,
		     (int,
		      if_addr *,
		      u_int32))));
PROTOTYPE(igmp_unregister_group_change,
	  extern int,
	  (_PROTOTYPE(func,
		     void,
		     (int,
		      if_addr *,
		      u_int32))));
PROTOTYPE(igmp_group_add,
	  extern int,
	  (if_addr *,
	   sockaddr_un *));
PROTOTYPE(igmp_group_drop,
	  extern int,
	  (if_addr *,
	   sockaddr_un *));
PROTOTYPE(igmp_send,
	  extern int,
	  (if_addr *,
	   struct ip *,
	   int,
	   sockaddr_un *,
	   int));
PROTOTYPE(igmp_get_ifproto,
	  extern int,
	  (if_addr *));
PROTOTYPE(igmp_set_ifproto,
	  extern int,
	  (if_addr *,
	   int));
PROTOTYPE(igmp_reset_ifproto,
	  extern void,
	  (if_addr *,
	   int));

#endif	/* PROTO_IGMP */

