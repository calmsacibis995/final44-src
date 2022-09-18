/*
 * $Id: pim.h,v 1.2 1995/01/10 03:12:19 pusateri Exp $
 */

/*%Copyright%*/


#ifdef	PROTO_PIM

/*
 * Protocol Independent Multicast Assert Preferences
 */

#define	PIM_DIRECT_PREFERENCE	0
#define	PIM_STATIC_PREFERENCE	1
#define	PIM_OSPF_PREFERENCE	110
#define	PIM_ISIS_PREFERENCE	115
#define	PIM_RIP_PREFERENCE	120
#define	PIM_SLSP_PREFERENCE	130
#define	PIM_EGP_PREFERENCE	140
#define	PIM_BGP_PREFERENCE	200
#define	PIM_IDRP_PREFERENCE	210
#define	PIM_KERNEL_PREFERENCE	220
#define	PIM_HELLO_PREFERENCE	255


/*
 * Protocol Independent Multicast
 */
#define	PIM_ROUTER_QUERY	0
#define	PIM_REGISTER		1
#define	PIM_REGISTER_STOP	2
#define	PIM_JOIN_PRUNE		3
#define	PIM_RP_REACHABILITY	4
#define	PIM_ASSERT		5
#define	PIM_GRAFT		6
#define	PIM_GRAFT_ACK		7
#define	PIM_MAX_TYPE		8

#define	PIM_ENABLED		0x01	/* PIM protocol status bit */

extern int pim_config_status;		/* if PIM is enabled in new config */

extern time_t pim_default_queryinterval;
extern time_t pim_default_routertimeout;
extern time_t pim_default_prunetimeout;
extern time_t pim_default_inactivitytimeout;
extern time_t pim_default_graftacktimeout;

/*
 * protocol message formats
 */

struct pimhdr {
    u_int8	igmp_type;		/* version & type of IGMP message */
    u_int8	igmp_code;		/* unused, should be zero */
    u_int16	igmp_cksum;		/* IP-style checksum */
    u_int32	pim_version;		/* highest 4 bits */
};

struct pimquery {
    u_int16	pim_mode;		/* highest 4 bits */
    u_int16	pim_holdtime;		/* time to keep neighbor reachable */
};

struct pimjoinhdr {
    u_int32	rpf_addr;
    u_int16	reserved;
    u_int16	holdtime;
    u_int8	reserved2;
    u_int8	maddr_len;
    u_int8	addr_len;
    u_int8	num_groups;
};

struct pimgroup {
    u_int32	group_addr;
    u_int32	group_mask;
    u_int16	num_join;
    u_int16	num_prune;
    char	source_data[1];
};

/*
 * This structure is not used in the code. It is only for reference.
 * Most compilers would pad it to 8 bytes which causes problems.
 * Therefore, we just take it a byte at a time in the real code.
 */
struct pimjoinsrc {
#define	PIM_SOURCE_S_BIT	0x01		/* Sparse Bit */
    u_int8	high_flags;
#define	PIM_SOURCE_W_BIT	0x80		/* Wildcard Bit */
#define	PIM_SOURCE_R_BIT	0x40		/* RP Bit */
    u_int8	low_flags;
    u_int32	src_addr;
};

#define	PIM_ASSERT_TIMEOUT	5		/* timeout assert in seconds */
#define	PIM_ASSERT_RPBIT	0x80000000	/* MSB in preference */


struct pimassert {
    u_int32	group_addr;	/* Group triggering mask */
    u_int32	group_mask;	/* Group mask */
    u_int32	src_addr;	/* Source in msg triggering assert */
    u_int32	preference;		/* pref. of unicast routing protocol */
					/* includes high order RP bit */
    u_int32	metric;			/* unicast routing metric */
};

#define	PIM_VERSION	0x10000000	/* 1 << 28 */
#define	PIM_MODE_DENSE	0x0
#define	PIM_MODE_SPARSE	0x1

/*
 * Join delay timer range in seconds
 */

#define	PIM_JOIN_DELAY_MIN	1
#define	PIM_JOIN_DELAY_MAX	3

/*
 * defines used by parser
 */

#define	PIM_LIMIT_QUERYINTERVAL		1, 3600		/* 1 hour */
#define	PIM_LIMIT_ROUTERTIMEOUT		1, 10800	/* 3 * 1 hour */
#define	PIM_LIMIT_PRUNETIMEOUT		1, 3600		/* 1 hour */
#define	PIM_LIMIT_INACTIVITYTIMEOUT	1, 3600		/* 1 hour */
#define	PIM_LIMIT_GRAFTACKTIMEOUT	1, 300		/* 5 minutes */

#define	PIM_CONFIG_ENABLE		1
#define	PIM_CONFIG_DISABLE		2
#define	PIM_CONFIG_MODE			3
#define	PIM_CONFIG_PRUNETIMEOUT		4
#define	PIM_CONFIG_INACTIVITYTIMEOUT	5
#define	PIM_CONFIG_MAX			6

extern adv_entry *pim_int_policy;		/* PIM control info */


/*
 * tracing declarations
 */

extern trace *pim_trace_options;	/* PIM tracing configuration */
extern const bits pim_trace_types[];	/* List of PIM specific trace flags */

#define	TR_PIM_DETAIL_ROUTER_QUERY	TR_DETAIL_1	/* query */
#define	TR_PIM_DETAIL_REGISTER		TR_DETAIL_2	/* register, rp */
#define	TR_PIM_DETAIL_REGISTER_STOP	TR_DETAIL_2	/* register, rp */
#define	TR_PIM_DETAIL_JOIN_PRUNE	TR_DETAIL_3	/* join, prune */
#define	TR_PIM_DETAIL_RP_REACHABILITY	TR_DETAIL_2	/* register, rp */
#define	TR_PIM_DETAIL_ASSERT		TR_DETAIL_4	/* assert */
#define	TR_PIM_DETAIL_GRAFT		TR_DETAIL_5	/* graft */
#define	TR_PIM_DETAIL_GRAFT_ACK		TR_DETAIL_5	/* graft */

#define	TR_PIM_INDEX_PACKETS	0	/* All packets */
#define	TR_PIM_INDEX_QUERY	1	/* Router Query packets */
#define	TR_PIM_INDEX_REGISTER	2	/* Register packets */
#define	TR_PIM_INDEX_RP		2	/* RP related packets */
#define	TR_PIM_INDEX_JOIN	3	/* Join/Prune packets */
#define	TR_PIM_INDEX_PRUNE	3	/* Join/Prune Other packets */
#define	TR_PIM_INDEX_ASSERT	4	/* Assert packets */
#define	TR_PIM_INDEX_GRAFT	5	/* Graft/Graft Ack packets */

/**/
PROTOTYPE(pim_init,
	  extern void,
	  (void));
PROTOTYPE(pim_var_init,
	  extern void,
	  (void));
PROTOTYPE(pim_set_pref,
	  extern void,
	  (int,
	   pref_t));

#endif	/* PROTO_PIM */
