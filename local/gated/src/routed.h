/*
 * $Header: /users/jch/src/gated/src/RCS/routed.h,v 2.0 90/04/16 16:53:30 jch Exp $
 */

/*%Copyright%*/


/*
 * Routing Information Protocol
 *
 * Derived from Xerox NS Routing Information Protocol
 * by changing 32-bit net numbers to sockaddr's and
 * padding stuff to 32-bit boundaries.
 */
#define	RIP_VERSION_1	1
#define	RIP_VERSION_2	2

struct rip_sockaddr {
    u_int16	rip_family;
    u_int16	rip_zero;
    struct in_addr rip_addr;
    u_long	rip_zero1[2];
} ;

struct netinfo {
    u_int16	rip_family;
    u_int16	rip_tag;
    u_int32	rip_dest;
    u_int32	rip_dest_mask;
    u_int32	rip_router;
    u_int32	rip_metric;			/* cost of route */
};

struct rip {
    /* XXX - using bytes causes alignment problems */
    byte	rip_cmd;		/* request/response */
    byte	rip_vers;		/* protocol version # */
    u_int16	rip_domain;			/* pad to 32-bit boundary */
};

struct entryinfo {
    struct rip_sockaddr rtu_dst;
    struct rip_sockaddr rtu_router;
    u_short	rtu_flags;
    short	rtu_state;
    int		rtu_timer;
    int		rtu_metric;
    u_int	rtu_int_flags;
    char rtu_int_name[IFNAMSIZ];
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
static bits rip_cmd_bits[] = {
{ 0,			"#0" },
{ RIPCMD_REQUEST,	"Request" } ,
{ RIPCMD_RESPONSE,	"Response" },
{ RIPCMD_TRACEON,	"TraceOn" },
{ RIPCMD_TRACEOFF,	"TraceOff" },
{ RIPCMD_POLL,		"Poll" },
{ RIPCMD_POLLENTRY,	"PollEntry" },
{ 0 }
};    
#endif	/* RIPCMDS */

#ifndef HOPCNT_INFINITY
#define	HOPCNT_INFINITY		16	/* per Xerox NS */
#endif	/* HOPCNT_INFINITY */
#ifndef MAXPACKETSIZE
#define	MAXPACKETSIZE		512	/* max broadcast size */
#endif	/* MAXPACKETSIZE */

/*
 * Timer values used in managing the routing table.
 * Every update forces an entry's timer to be reset.  After
 * EXPIRE_TIME without updates, the entry is marked invalid,
 * but held onto until GARBAGE_TIME so that others may
 * see it "be deleted".
 */
#define	TIMER_RATE		30	/* alarm clocks every 30 seconds */

#define	SUPPLY_INTERVAL		30	/* time to supply tables */

#define	EXPIRE_TIME		180	/* time to mark entry invalid */
#define	GARBAGE_TIME		240	/* time to garbage collect */


#define	RIP_ADDR_MC	0xe0000009	/* 224.0.0.9 */
