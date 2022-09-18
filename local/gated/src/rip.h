/*
 * $Id: rip.h,v 1.28.2.2 1994/08/15 20:25:25 jch Exp $
 */

/* %(Copyright.header) */


#ifdef	PROTO_RIP
/*
 * Routing Information Protocol
 *  
 * Originally derived from Xerox NS Routing Information Protocol by
 * changing 32-bit net numbers to sockaddr's and padding stuff to 32-bit
 * boundaries.
 */

#define	RIP_VERSION_0	0
#define	RIP_VERSION_1	1
#define	RIP_VERSION_2	2

struct rip_sockaddr {
    u_int16	rip_family;
    u_int16	rip_zero;
    u_int32	rip_addr;
    u_int32	rip_zero1[2];
} ;

struct rip_netinfo {
    u_int16	rip_family;
    u_int16	rip_tag;
    u_int32	rip_dest;
    u_int32	rip_dest_mask;
    u_int32	rip_router;
    u_int32	rip_metric;			/* cost of route */
};

#define RIP_METRIC_UNREACHABLE	16
#define	RIP_METRIC_SHUTDOWN	(RIP_METRIC_UNREACHABLE - 1)

#define	RIP_AUTH_SIZE	16

struct rip_authinfo {
    u_int16	auth_family;			/* RIP_AF_AUTH */
    u_int16	auth_type;
    u_int32	auth_data[RIP_AUTH_SIZE / sizeof (u_int32)];
};

struct rip_trailer {
    u_int32	auth_sequence;
} ;

#define	RIP_AF_UNSPEC	0
#define	RIP_AF_INET	2
#define	RIP_AF_AUTH	0xffff

#define	RIP_AUTH_NONE	0
#define	RIP_AUTH_SIMPLE	2
#define	RIP_AUTH_MD5	3

struct rip {
    /* XXX - using bytes causes alignment problems */
    byte	rip_cmd;		/* request/response */
    byte	rip_vers;		/* protocol version # */
    u_int16	rip_zero2;		/* unused */
};

struct entryinfo {
    struct rip_sockaddr rtu_dst;
    struct rip_sockaddr rtu_router;
    u_int16	rtu_flags;
    s_int16	rtu_state;
    s_int32	rtu_timer;
    s_int32		rtu_metric;
    u_int32	rtu_int_flags;
    char rtu_int_name[IFL_NAMELEN];
};

/*
 * Packet types.
 */
#define	RIPCMD_REQUEST		1	/* want info */
#define	RIPCMD_RESPONSE		2	/* responding to request */
#define	RIPCMD_TRACEON		3	/* turn tracing on */
#define	RIPCMD_TRACEOFF		4	/* turn it off */
#define	RIPCMD_POLL		5	/* like request, but anyone answers */
#define	RIPCMD_POLLENTRY	6	/* like poll, but for entire entry */
#define	RIPCMD_MAX		7

#ifdef RIPCMDS
static const bits rip_cmd_bits[] = {
    { 0,		"Invalid" },
    { RIPCMD_REQUEST,	"Request" } ,
    { RIPCMD_RESPONSE,	"Response" },
    { RIPCMD_TRACEON,	"TraceOn" },
    { RIPCMD_TRACEOFF,	"TraceOff" },
    { RIPCMD_POLL,	"Poll" },
    { RIPCMD_POLLENTRY,	"PollEntry" },
    { 0 }
};    
#endif	/* RIPCMDS */

#define RIP_PKTSIZE	512
#define	RIP_MAXSIZE(ifap)	MIN(RIP_PKTSIZE, ifap->ifa_mtu - sizeof (struct udphdr))

#define	RIP_ADDR_MC	0xe0000009	/* 224.0.0.9 */

#define RIP_T_UPDATE	(time_t) 30
#define	RIP_T_HOLDDOWN	(time_t) 120
#define	RIP_T_FLASH	(time_t) (grand((u_int32) (RIP_T_MAX - RIP_T_MIN + 1)) + RIP_T_MIN)
#define	RIP_T_MAX	(time_t) 5
#define	RIP_T_MIN	(time_t) 1
#define	RIP_T_EXPIRE	(time_t) 180

#define RIP_PORT	520
#define	RIP_HOP		1	/* Minimum hop count when passing through */
#define	RIP_LIMIT_METRIC	RIP_HOP, RIP_METRIC_UNREACHABLE	/* For parser */

#define	RIP_CONFIG_IN			1
#define	RIP_CONFIG_OUT			2
#define	RIP_CONFIG_METRICIN		3
#define	RIP_CONFIG_METRICOUT		4
#define	RIP_CONFIG_FLAG			5
#define	RIP_CONFIG_AUTH			6
#define	RIP_CONFIG_AUTH2		7
#define	RIP_CONFIG_MAX			8

extern flag_t rip_flags;		/* Option flags */
extern trace *rip_trace_options;	/* RIP tracing configuration */
extern metric_t rip_default_metric;	/* Default metric to use when propogating */
extern pref_t rip_preference;		/* Preference for RIP routes */
extern int rip_n_trusted;		/* Number of Trusted RIP gateways */
extern int rip_n_source;		/* Number of gateways to receive explicate RIP info */
extern adv_entry *rip_import_list;	/* List of nets to import and not import */
extern adv_entry *rip_export_list;	/* List of nets to export */
extern adv_entry *rip_int_policy;	/* List of interface policy */
extern gw_entry *rip_gw_list;		/* List of RIP gateways */
extern block_t rip_auth_block_index;
extern const bits rip_trace_types[];	/* List of RIP specific trace flags */
extern struct rip_authinfo *rip_auth_query;	/* Password for user queries */
extern struct rip_authinfo rip_auth_none;	/* Control block for no authentication */

/* Values for rip_flags */
#define	RIPF_ON			BIT(0x01)		/* RIP is enabled */
#define	RIPF_BROADCAST		BIT(0x02)		/* Broadcast to all interfaces */
#define	RIPF_SOURCE		BIT(0x04)		/* Source packets to our peers */
#define	RIPF_CHOOSE		BIT(0x08)		/* Broadcast if more than one interface */
#define	RIPF_NOCHECK		BIT(0x10)		/* Don't check zero fields */
#define	RIPF_FLASHDUE		BIT(0x20)		/* Flash update is due */
#define	RIPF_NOFLASH		BIT(0x40)		/* Can not do a flash update until after the next normal update */
#define	RIPF_RECONFIG		BIT(0x80)		/* Initial processing or reconfiguration */
#define	RIPF_TERMINATE		BIT(0x0100)		/* RIP is terminating */

#define	RIP_HOLDCOUNT		(RIP_T_HOLDDOWN/RIP_T_UPDATE)	/* Number of updates per holddown */

#define	RIPTF_POLL		TARGETF_USER1	/* Target has been polled */
#define	RIPTF_V2MC		TARGETF_USER2	/* Use v2 MC for this target */
#define	RIPTF_V2BC		TARGETF_USER3	/* Use v1 compatible v2 features */
#define	RIPTF_V2		(RIPTF_V2MC|RIPTF_V2BC)
#define	RIPTF_MCSET		TARGETF_USER4	/* MC has been enabled on this interface */

#define	RIP_IFPS_V2MC	IFPS_POLICY1	/* Should send V2 MC packets */
#define	RIP_IFPS_V2BC	IFPS_POLICY2	/* Should send V1 compatible V2 BC packets */
#define	RIP_IFPS_V2	(RIP_IFPS_V2MC|RIP_IFPS_V2BC)
#define	RIP_IFPS_V1	0

#define	ifa_rip_mccount	ifa_ps[RTPROTO_RIP].ips_datas[0]
#define	ifa_rip_auth	ifa_ps[RTPROTO_RIP].ips_datas[1]
#define	ifa_rip_auth2	ifa_ps[RTPROTO_RIP].ips_datas[2]

#define	RIP_IFPS_NOMC	IFPS_KEEP1	/* Unable to enable MC on this IF */

/* Tracing */
#define	TR_RIP_INDEX_PACKETS	0	/* All packets */
#define	TR_RIP_INDEX_REQUEST	1	/* Request packets (REQUEST, POLL, POLLENTRY) */
#define	TR_RIP_INDEX_RESPONSE	2	/* Response packets (RESPONSE) */
#define	TR_RIP_INDEX_OTHER	3	/* Other packets (TRACE_ON, TRACE_OFF) */

#define	TR_RIP_DETAIL_REQUEST	TR_DETAIL_1
#define	TR_RIP_DETAIL_RESPONSE	TR_DETAIL_2
#define	TR_RIP_DETAIL_OTHER	TR_DETAIL_3

/**/
PROTOTYPE(rip_init,
	  extern void,
	  (void));
PROTOTYPE(rip_var_init,
	  extern void,
	  (void));
PROTOTYPE(rip_config_free,
	  extern void,
	  (config_entry *));
#if	defined(PROTO_SNMP) && defined(MIB_RIP)

u_int rip_global_changes;
u_int rip_global_responses;

PROTOTYPE(rip_init_mib,
	  extern void,
	  (int));
#endif	/* defined(PROTO_SNMP) && defined(MIB_RIP) */

#endif	/* PROTO_RIP */

/*
 * %(Copyright)
 */
