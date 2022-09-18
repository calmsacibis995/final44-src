/*
 * $Id: slsp_proto.h,v 1.8 1994/02/21 03:06:10 jch Exp $
 */

/*%Copyright%*/


/*
 * Protocol-related definitions for SLSP.  This is about all the
 * documentation there is.
 * 
 * SLSP (Simple Link State Protocol, this is the "kind" name) is an
 * Interior Gateway Protocol for IP.  SLSP is a link-state protocol,
 * though it doesn't do area routing.  This version of SLSP may handle
 * broadcast subnets, and non-broadcast multiaccess media, but previous
 * implementations operated on point-to-point circuits only.
 *
 * SLSP doesn't do variable length subnet mask routing, in fact
 * SLSP only propagates subnets of a single network, with a fixed
 * subnet mask, as internal routing.  In fact SLSP installs exactly
 * one subnet route per node, plus an additional subnet route per
 * broadcast network, which means that your interfaces had either
 * better be on broadcast subnets or numbered using numbers from the
 * node's "subnet" (actually, either a SLSP subnet or a whole network
 * number will do it) if you want to be able to route to the addresses
 * via internal routing.
 *
 * SLSP deals with exterior routes as whole networks only, and tags
 * each exterior route with a neighbour AS number.  Normally this doesn't
 * actually constrain SLSP, since SLSP normally uses BGP to propagate
 * external routing information instead.  SLSP also propagates
 * routes to neighbour ASes (whatever these are), but ignores these
 * on reception (since SLSP doesn't understand them either).  Basically,
 * then, SLSP's primary function is to compute and install subnet routes,
 * so you'd better number your routers to make it happy.
 *
 * If you really want more information, try RFC1074 and a draft of the
 * ANSI version of ISO IS-IS circa 1987 or so.
 */

#define	SLSP_IP_PROTO		85		/* IP protocol ID for SLSP */
#define	SLSP_IP_PROTO_NAME	"nsfnet-igp"	/* no comment */

/*
 * Lifetime constants, sort from from the standard.
 */
#define	SLSP_LIFE_MAX		7200		/* 7200 is standard */
#define	SLSP_LIFE_REORIGINATE	1800		/* originate every half hour */
#define	SLSP_LIFE_MAXDIFF	1800		/* his is better if newer */
#define	SLSP_LIFE_EXPIRED	90		/* retain old for 1.5 minutes */

#define	SLSP_MIN_SEND_INTERVAL	5		/* send every 5 seconds */

/*
 * Sequence number constants
 */
#define	SLSP_SEQNUM_MIN		((slsp_seqnum_t)(0x80000000))
#define	SLSP_SEQNUM_INIT	((slsp_seqnum_t)(0x80000001))
#define	SLSP_SEQNUM_MAX		((slsp_seqnum_t)(0x7fffffff))
#define	SLSP_SEQNUM_MID		((slsp_seqnum_t)(0))

#define	SLSP_SEQNUM_DIFF	((slsp_seqnum_t)(0x40000000))

#define	SLSP_SEQNUM_OLDER(s1, s2) \
    (((s1) == (s2)) ? 0 : \
      (((s1) < SLSP_SEQNUM_MID) ? ((s1) < (s2)) : \
      (((s2) < SLSP_SEQNUM_MID) ? 0 : \
      (((s1) < (s2)) ? (((s2) - (s1)) < SLSP_SEQNUM_DIFF) : \
      (((s1) - (s2)) >= SLSP_SEQNUM_DIFF)))))

#define	SLSP_SEQNUM_NEXT(s) \
    (((s) == SLSP_SEQNUM_MAX) ? SLSP_SEQNUM_MID : ((s) + 1))

/*
 * Generic macro definitions for getting stuff out of a non-byte-aligned
 * packet and putting it back in.
 */
#define	SLSP_GET_SHORT(val, cp) \
    do { \
	register u_int16 Xtmp; \
	Xtmp = ((u_int16)(*(cp)++)) << 8; \
	Xtmp |= (u_int16)(*(cp)++); \
	(val) = Xtmp; \
    } while (0)

#define	SLSP_GET_LONG(val, cp) \
    do { \
	register u_int32 Xtmp; \
	Xtmp = ((u_int32)(*(cp)++)) << 24; \
	Xtmp |= ((u_int32)(*(cp)++)) << 16; \
	Xtmp |= ((u_int32)(*(cp)++)) <<  8; \
	Xtmp |= (u_int32)(*(cp)++); \
	(val) = Xtmp; \
    } while (0)

#define	SLSP_GET_IPADDR(addr, cp) \
    do { \
	register byte *Xap = (byte *)&(sock2ip(addr)); \
	*Xap++ = *(cp)++; \
	*Xap++ = *(cp)++; \
	*Xap++ = *(cp)++; \
	*Xap++ = *(cp)++; \
    } while (0)

#define	SLSP_PUT_SHORT(val, cp) \
    do { \
	register u_int16 Xtmp = (val); \
	*(cp)++ = (byte)((Xtmp >> 8) & 0xff); \
	*(cp)++ = (byte)(Xtmp & 0xff); \
    } while (0)

#define	SLSP_PUT_LONG(val, cp) \
    do { \
	register u_int32 Xtmp = (val); \
	*(cp)++ = (byte)((Xtmp >> 24) & 0xff); \
	*(cp)++ = (byte)((Xtmp >> 16) & 0xff); \
	*(cp)++ = (byte)((Xtmp >>  8) & 0xff); \
	*(cp)++ = (byte)(Xtmp & 0xff); \
    } while (0)

#define	SLSP_PUT_IPADDR(addr, cp) \
    do { \
	register byte *Xap = (byte *)&(sock2ip(addr)); \
	*(cp)++ = *Xap++; \
	*(cp)++ = *Xap++; \
	*(cp)++ = *Xap++; \
	*(cp)++ = *Xap++; \
    } while (0)


/*
 * Format of a generic SLSP address.  This holds (from time to time)
 * an IP address (either a network number or a number on the SLSP subnet)
 * and an AS.  A variant of the SLSP address holds just the AS.
 */
#define	SLSP_ADDR_LEN		((size_t)12)	/* length of entire SLSP addr */
#define	SLSP_NET_LEN		((size_t)11)	/* length of a SLSP "NET" */
#define	SLSP_ASADDR_LEN		((size_t)5)	/* length of a SLSP "AS address" */
#define	SLSP_IPADDR_LEN		((size_t)4)	/* 4 bytes for address */
#define	SLSP_AS_LEN		((size_t)2)	/* 2 bytes for the AS */

#define	SLSP_ADDR_IDP_LEN	((size_t)3)	/* length of the IDP */
#define	SLSP_ADDR_IDP_0		47	/* first byte of IDP n.b. not 0x47 */
#define	SLSP_ADDR_IDP_1		0	/* second byte of IDP */
#define	SLSP_ADDR_IDP_2		6	/* third byte of IDP */

typedef struct _slsp_addr {
    byte slspa_idp[SLSP_ADDR_IDP_LEN];	/* 47, 0, 6, in that order */
    byte slspa_as[SLSP_AS_LEN];		/* AS number */
    byte slspa_mbz[2];			/* two Must-Be-Zero bytes */
    byte slspa_ipaddr[SLSP_ADDR_LEN];	/* IP address */
    byte slspa_sel;			/* selector.  Not used much */
} slsp_addr;

typedef struct _slsp_net {
    byte slspn_idp[SLSP_ADDR_IDP_LEN];	/* 47, 0, 6, in that order */
    byte slspn_as[SLSP_AS_LEN];		/* AS number */
    byte slspn_mbz[2];			/* two Must-Be-Zero bytes */
    byte slspn_ipaddr[SLSP_ADDR_LEN];	/* IP address */
} slsp_net;

typedef struct _slsp_as {
    byte slsps_idp[SLSP_ADDR_IDP_LEN];	/* 47, 0, 6 in that order */
    byte slsps_as[SLSP_AS_LEN];		/* AS number */
} slsp_as;

/*
 * Checks the fixed part of a SLSP address, given a pointer to the start
 * of the address.  Returns true if all okay.
 */
#define	SLSP_CHK_AS(cp) \
    (*(cp) == SLSP_ADDR_IDP_0 && *((cp)+1) == SLSP_ADDR_IDP_1 \
      && *((cp)+2) == SLSP_ADDR_IDP_2)

#define	SLSP_CHK_NET(cp) \
    (SLSP_CHK_AS((cp)) && *((cp)+5) == 0 && *((cp)+6) == 0)

#define	SLSP_CHK_ADDR(cp) \
    (SLSP_CHK_NET((cp)) && *((cp)+11) == 0)

/*
 * Fetches the AS from a SLSP AS address.  The pointer is advanced past
 * the end of the AS address when done.
 */
#define	SLSP_GET_AS(as, cp) \
    do { \
	(cp) += SLSP_ADDR_IDP_LEN; \
	SLSP_GET_SHORT((as), (cp)); \
    } while (0)

/*
 * Fetches the AS and address from a SLSP NET.  The pointer is advanced
 * past the end of the NET when done.
 */
#define	SLSP_GET_NET(as, addr, cp) \
    do { \
	SLSP_GET_AS((as), (cp)); \
	(cp) += 2; \
	SLSP_GET_IPADDR((addr), (cp)); \
    } while (0)

/*
 * Same as above except for a extra byte to skip
 */
#define	SLSP_GET_ADDR(as, addr, cp) \
    do { \
	SLSP_GET_NET((as), (addr), (cp); \
	(cp)++; \
    } while (0)

/*
 * Formats an AS into a SLSP AS address.  The pointer is advanced past
 * the end of the AS address when done.
 */
#define	SLSP_PUT_ASADDR(as, cp) \
    do { \
	*(cp)++ = SLSP_ADDR_IDP_0; \
	*(cp)++ = SLSP_ADDR_IDP_1; \
	*(cp)++ = SLSP_ADDR_IDP_2; \
	SLSP_PUT_SHORT((as), (cp)); \
    } while (0)

/*
 * Formats an AS and IP address into a SLSP NET.  The pointer
 * is advanced past the end of the NET when done.
 */
#define	SLSP_PUT_NET(as, addr, cp) \
    do { \
	SLSP_PUT_ASADDR((as), (cp)); \
	*cp++ = 0; \
	*cp++ = 0; \
	SLSP_PUT_IPADDR((addr), (cp)); \
    } while (0)

/*
 * As above but for a SLSP address, with an extra byte.
 */
#define	SLSP_PUT_ADDR(as, addr, cp) \
    do { \
	SLSP_PUT_NET((as), (addr), (cp)); \
	*(cp)++ = 0; \
    } while (0)


/*
 * A couple of other commonly used constants.
 */
#define	SLSP_CKSUM_LEN	((size_t)2)	/* length of a checksum */
#define	SLSP_LIFETIME_LEN ((size_t)2)	/* length of lifetime/holdtime */
#define	SLSP_PKT_LEN	((size_t)4)	/* pkt length length for large pkts */
#define	SLSP_SEQNUM_LEN	((size_t)4)	/* length of a sequence number */

typedef s_int32 slsp_seqnum; /*XXX type for sequence #, Must be 32-bit signed */


/*
 * The first byte in the packet is the protocol type.  Fetch it.
 */
#define	SLSP_GET_PROTOCOL(cp)	(*(cp))

/*
 * The SLSP hello.  This is sent down each point-to-point circuit from
 * time to time to indicate we are alive.  It includes the subnet number
 * the router wishes to be known by (in the NET) and the hold time
 * for timing the adjacency out.
 *
 * This approximately corresponds to an ES-IS Hello.
 */
#define	SLSP_HELLO_PROTOCOL	2		/* tells us this is hello */
#define	SLSP_HELLO_LEN		((size_t) 21)	/* length of the hello PDU */
#define	SLSP_HELLO_VERSION_ID	1		/* constant goop */
#define	SLSP_HELLO_TYPE		4		/* more constant goop */

typedef struct _slsp_hello {
    byte slsph_protocol;		/* see SLSP_HELLO_PROTOCOL */
    byte slsph_length;			/* see SLSP_HELLO_LEN */
    byte slsph_version_id;		/* see SLSP_HELLO_VERSION_ID */
    byte slsph_mbz;			/* must be zero */
    byte slsph_type;			/* see SLSP_HELLO_TYPE */
    byte slsph_holdtime[SLSP_LIFETIME_LEN];	/* hold time for adjacency */
    byte slsph_cksum[SLSP_CKSUM_LEN];	/* packet checksum */
    byte slsph_net_length;		/* see SLSP_NET_LEN */
    byte slsph_net[SLSP_NET_LEN];	/* where the NET goes */
} slsp_hello;


/*
 * Check the fixed fields in a SLSP hello, return true if okay.  This
 * assumes the protocol and length have been checked already.
 */
#define	SLSP_CHK_HELLO(cp) \
    (*((cp)+1) == SLSP_HELLO_LEN && *((cp)+2) == SLSP_HELLO_VERSION_ID \
     && *((cp)+3) == 0  && *((cp)+4) == SLSP_HELLO_TYPE \
     && *((cp)+9) == SLSP_NET_LEN && SLSP_CHK_NET((cp)+10))

/*
 * Check the checksum in a SLSP hello.  Returns true if the checksum was okay.
 */
#define	SLSP_CHK_HELLO_CKSUM(cp) \
    (iso_cksum((cp), SLSP_HELLO_LEN, (byte *)0) == 0)

/*
 * Fetch the useful data from a SLSP hello.  The pointer is advanced
 * past the end of the packet.
 */
#define	SLSP_GET_HELLO(holdtime, as, addr, cp) \
    do { \
	(cp) += 5; \
	SLSP_GET_SHORT((holdtime), (cp)); \
	(cp) += 3; \
	SLSP_GET_NET((as), (addr), (cp)); \
    } while (0)

/*
 * Format the fixed fields in an outgoing SLSP hello.  The pointer
 * remains pointed at the start of the packet.
 */
#define	SLSP_PUT_HELLO_FIXED(cp) \
    do { \
	register byte *Xcp = (cp); \
	*Xcp++ = SLSP_HELLO_PROTOCOL; \
	*Xcp++ = SLSP_HELLO_LEN; \
	*Xcp++ = SLSP_HELLO_VERSION_ID; \
	*Xcp++ = 0; \
	*Xcp++ = SLSP_HELLO_TYPE; \
	Xcp += 4; \
	*Xcp++ = SLSP_NET_LEN; \
	*Xcp++ = SLSP_ADDR_IDP_0; \
	*Xcp++ = SLSP_ADDR_IDP_1; \
	*Xcp++ = SLSP_ADDR_IDP_2; \
	Xcp += 2; \
	*Xcp++ = 0; \
	*Xcp++ = 0; \
    } while (0)

/*
 * Insert the variable fields into an SLSP hello packet.  The pointer
 * remains pointed at the start of the packet.
 */
#define	SLSP_PUT_HELLO_VAR(holdtime, as, addr, cp) \
    do { \
	register byte *Xcp = ((byte *)(cp)) + 5; \
	SLSP_PUT_SHORT((holdtime), Xcp); \
	Xcp += 6; \
	SLSP_PUT_SHORT((as), Xcp); \
	Xcp += 2; \
	SLSP_PUT_IPADDR((addr), Xcp); \
	(void) iso_cksum((void_t)(Xcp-SLSP_HELLO_LEN), \
	    SLSP_HELLO_LEN, ((Xcp-SLSP_HELLO_LEN)+7)); \
    } while (0)


/*
 * Format an outgoing SLSP hello.  The checksum field is computed last.
 * The pointer is advanced past the end of the packet.
 */
#define	SLSP_PUT_HELLO(holdtime, as, addr, cp) \
    do { \
	*(cp)++ = SLSP_HELLO_PROTOCOL; \
	*(cp)++ = SLSP_HELLO_LEN; \
	*(cp)++ = SLSP_HELLO_VERSION_ID; \
	*(cp)++ = 0; \
	*(cp)++ = SLSP_HELLO_TYPE; \
	SLSP_PUT_SHORT((holdtime), (cp)); \
	(cp) += 2; \
	*(cp)++ = SLSP_NET_LEN; \
	SLSP_PUT_NET((as), (addr), (cp)); \
	(void) iso_cksum((void *)((cp)-SLSP_HELLO_LEN), \
	    SLSP_HELLO_LEN, (((cp)-SLSP_HELLO_LEN)+7)); \
    } while (0)


/*
 * The remaining packets (which are all derived from the IS-IS protocol)
 * all have a fixed leader format.  This follows.  We actually maintain
 * two separate leader formats, the "normal" format and the "short" format.
 */
#define	SLSP_LEADER_LEN	((size_t) 8)	/* length of the common leader */
#define	SLSP_L		SLSP_LEADER_LEN	/* short form of above */
#define	SLSP_LEADER_PROTOCOL	8	/* "protocol" for packets with leader */
#define	SLSP_LEADER_VERSION_ID	1	/* fixed version/ID */
#define	SLSP_LEADER_VERSION	3	/* version (constant grot) */

typedef struct _slsp_leader {
    byte slspx_protocol;		/* see SLSP_LEADER_PROTOCOL */
    byte slspx_length;			/* length of fixed part, varies */
    byte slspx_version_id;		/* see SLSP_LEADER_VERSION_ID */
    byte slspx_reserved;		/* constant 0 */
    byte slspx_type;			/* type of packet, varies */
    byte slspx_version;			/* see SLSP_LEADER_VERSION */
    byte slspx_mbz[2];			/* constant 0's */
} slsp_leader;

/*
 * The "short" leader is just the first 5 bytes of the above.
 */
#define	SLSP_SHORT_LEADER_LEN	((size_t) 5)	/* length of short header */
#define	SLSP_SL		SLSP_SHORT_LEADER_LEN	/* short form of above */

typedef struct _slsp_short_leader {
    byte slspz_protocol;		/* see SLSP_LEADER_PROTOCOL */
    byte slspz_length;			/* length of fixed part, varies */
    byte slspz_version_id;		/* see SLSP_LEADER_VERSION_ID */
    byte slspz_reserved;		/* constant 0 */
    byte slspz_type;			/* type of packet, varies */
} slsp_short_leader;

typedef byte slsp_short_leader_bytes[SLSP_SL];	/* byte version of above */

/*
 * Check the fixed fields in the leader.  Assumes protocol and length
 * have already been examined.
 */
#define	SLSP_CHK_LEADER(cp) \
    (*((cp)+2) == SLSP_LEADER_VERSION_ID && *((cp)+3) == 0 \
     && *((cp)+5) == SLSP_LEADER_VERSION && *((cp)+6) == 0 \
     && *((cp)+7) == 0)

/*
 * Check the fixed fields in a short leader.  As above.
 */
#define	SLSP_CHK_SHORT_LEADER(cp) \
    (*((cp)+2) == SLSP_LEADER_VERSION_ID && *((cp)+3) == 0)

/*
 * Check the fixed fields in a long leader, assuming the short leader
 * fields have already been checked.
 */
#define	SLSP_CHK_LEADER_EXT(cp) \
     (*((cp)+5) == SLSP_LEADER_VERSION && *((cp)+6) == 0 \
     && *((cp)+7) == 0)


/*
 * Find the type field in the leader.
 */
#define	SLSP_GET_LEADER_TYPE(cp)	(*((cp)+4))

/*
 * Find the length field in the leader.
 */
#define	SLSP_GET_LEADER_LENGTH(cp)	(*((cp)+1))

/*
 * Format a leader.  The pointer ends up pointing past the end of the leader.
 */
#define	SLSP_PUT_LEADER(length, type, cp) \
    do { \
	*(cp)++ = SLSP_LEADER_PROTOCOL; \
	*(cp)++ = (byte)(length); \
	*(cp)++ = SLSP_LEADER_VERSION_ID; \
	*(cp)++ = 0; \
	*(cp)++ = (byte)(type); \
	*(cp)++ = SLSP_LEADER_VERSION; \
	*(cp)++ = 0; \
	*(cp)++ = 0; \
    } while (0)

/*
 * Format a short leader.  Same as above.
 */
#define	SLSP_PUT_SHORT_LEADER(length, type, cp) \
    do { \
	*(cp)++ = SLSP_LEADER_PROTOCOL; \
	*(cp)++ = (byte)(length); \
	*(cp)++ = SLSP_LEADER_VERSION_ID; \
	*(cp)++ = 0; \
	*(cp)++ = (byte)(type); \
    } while (0)


/*
 * The SLSP point-to-point I-Hear-You.  This is sent in response to the
 * receipt of a Hello, I think to indicate that an adjacency has been
 * accepted.  Look at the IS-IS router Hello for something similar.
 */
#define	SLSP_PTP_IHU_TYPE	17	/* type field for leader */
#define	SLSP_PTP_IHU_LEN	(SLSP_LEADER_LEN + (size_t) 1)
#define	SLSP_PTP_IHU_RTR_TYPE	2	/* fixed payload data */

typedef struct _slsp_ptp_ihu {
    slsp_leader slspi_leader;
#define	slspi_length	slspi_leader.slspx_length
#define	slspi_type	slspi_leader.slspx_type
    byte slspi_rtr_type;
} slsp_ptp_ihu;

/*
 * Notice the IHU packet is entirely fixed data.  The following
 * initializes a byte buffer with static data for the IHU, using
 *
 * byte slsp_ptp_ihu_pkt[SLSP_PTP_IHU_LEN] = SLSP_PTP_IHU_PKT;
 */
#define	SLSP_PTP_IHU_PKT \
    { \
	SLSP_LEADER_PROTOCOL, \
	(byte) SLSP_PTP_IHU_LEN, \
	SLSP_LEADER_VERSION_ID, \
	0, \
	SLSP_PTP_IHU_TYPE, \
	SLSP_LEADER_VERSION, \
	0, \
	0, \
	SLSP_PTP_IHU_RTR_TYPE \
    }

/*
 * Check that this looks like a SLSP IHU.  Assumes the short leader, type
 * and length have already been checked, which doesn't leave much.
 */
#define	SLSP_CHK_PTP_IHU(cp) \
    (SLSP_CHK_LEADER_EXT((cp)) && *((cp)+SLSP_LEADER_LEN) == SLSP_PTP_IHU_RTR_TYPE)

/*
 * Format a PTP IHU packet.  Probably better to use a static version,
 * since nothing ever changes in here.
 */
#define	SLSP_PUT_PTP_IHU(cp) \
    do { \
	SLSP_PUT_LEADER(SLSP_PTP_IHU_LEN, SLSP_PTP_IHU_TYPE, (cp)); \
	*(cp)++ = SLSP_PTP_IHU_RTR_TYPE; \
    } while (0)


/*
 * The SLSP broadcast IHU.  Sent from time to time on broadcast
 * networks to acknowledge the fact that we are here and have been
 * hearing our neighbours.
 */
#define	SLSP_BCAST_IHU_TYPE		16	/* type for packet */
#define	SLSP_BCAST_IHU_FIXED_LEN	(SLSP_LEADER_LEN+(size_t)17)
#define SLSP_BCAST_IHU_TORTRS_LEN	(SLSP_BCAST_IHU_FIXED_LEN + (size_t)1)
#define	SLSP_BCAST_IHU_MIN_LEN		(SLSP_BCAST_IHU_FIXED_LEN + (size_t)2)
#define	SLSP_BCAST_IHU_MAX_PRIORITY	255	/* maximum priority value */
#define	SLSP_BCAST_IHU_RTR_TYPE		SLSP_PTP_IHU_RTR_TYPE

#define	SLSP_BCAST_PRIORITY_MASK	0x7f
#define	SLSP_BCAST_CONFIG_FLAG		0x80

#define	SLSP_BCAST_N_AREAS_LEN		((size_t)1)
#define	SLSP_BCAST_N_RTRS_LEN		((size_t)1)

typedef struct _slsp_bcast_ihu {
    slsp_leader slspb_leader;
#define	slspb_length	slspb_leader.slspx_length
#define	slspb_type	slspb_leader.slspx_type
    byte slspb_rtr_type;		/* see SLSP_BCAST_IHU_RTR_TYPE */
    byte slspb_priority;	/* priority (designated router election) */
    byte slspb_holdtime[SLSP_LIFETIME_LEN];	/* how long to maintain adj */
    byte slspb_mbz1[2];				/* 2 bytes of 0 */
    byte slspb_node_id[SLSP_IPADDR_LEN];	/* my node subnet ID */
    byte slspb_mbz2[2];				/* another 2 bytes of 0 */
    byte slspb_lan_id[SLSP_IPADDR_LEN];		/* ID of lan */
    byte slspb_mbz3;				/* must be zero for us */
} slsp_bcast_ihu;

/*
 * The variable part of the broadcast IHU contains a list of areas (always
 * zero for us) and a list of neighbour routers.  A neighbour router
 * entry looks as follows.
 */
#define	SLSP_BCAST_IHU_RTR_LEN		((size_t) 7)	/* 7 byte entries */

typedef struct _slsp_bcast_ihu_rtr {
    byte slspb_rtr_mbz[2];			/* 2 bytes of 0 */
    byte slspb_rtr_id[SLSP_IPADDR_LEN];		/* node ID of router */
    byte slspb_rtr_priority;			/* priority of router */
} slsp_bcast_ihu_rtr;

/*
 * Check the fixed fields in the broadcast IHU.  This assumes the leader
 * has already been checked.
 */
#define	SLSP_CHK_BCAST_IHU(cp) \
    (SLSP_CHK_LEADER_EXT((cp)) \
     && *((cp)+SLSP_L) == SLSP_BCAST_IHU_RTR_TYPE \
     && *((cp)+SLSP_L+4) == 0 && *((cp)+SLSP_L+5) == 0 \
     && *((cp)+SLSP_L+10) == 0 && *((cp)+SLSP_L+11) == 0)

/*
 * Macros for fetching the areas and routers lengths.  The routers
 * macro assumes the areas length was zero.
 */
#define	SLSP_FETCH_BCAST_N_AREAS(cp) \
    ((size_t)*((cp) + SLSP_BCAST_IHU_FIXED_LEN))

#define	SLSP_FETCH_BCAST_N_RTRS(cp) \
    ((size_t)*((cp) + SLSP_BCAST_IHU_FIXED_LEN + SLSP_BCAST_N_AREAS_LEN))

/*
 * Fetch the interesting fields in the broadcast IHU.  The pointer is
 * spaced past the IHU when done.
 */
#define	SLSP_GET_BCAST_IHU(priority, holdtime, node_addr, lan_addr, cp) \
    do { \
	(cp) += (SLSP_LEADER_LEN + 1); \
	(priority) = (*(cp)++) & SLSP_BCAST_PRIORITY_MASK; \
	SLSP_GET_SHORT((holdtime), (cp)); \
	(cp) += 2; \
	SLSP_GET_IPADDR((node_addr), (cp)); \
	(cp) += 2; \
	SLSP_GET_IPADDR((lan_addr), (cp)); \
	(cp)++; \
    } while (0)


/*
 * Put the fields not written above into the bcast IHU.  Leave the pointer
 * pointing at the place to output the number of routers.
 */
#define SLSP_PUT_BCAST_IHU_VAR(priority, holdtime, node_addr, lan_addr, cp) \
    do { \
	register sockaddr_un *Xaddr = (lan_addr); \
	(cp) += (SLSP_LEADER_LEN + 1); \
	*(cp)++ = (priority) & SLSP_BCAST_PRIORITY_MASK; \
	SLSP_PUT_SHORT((holdtime), (cp)); \
	(cp) += 2; \
	SLSP_PUT_IPADDR((node_addr), (cp)); \
	(cp) += 2; \
	if (Xaddr) { \
	    SLSP_PUT_IPADDR(Xaddr, (cp)); \
	} else { \
	    *(cp)++ = 0; *(cp)++ = 0; *(cp)++ = 0; *(cp)++ = 0; \
	} \
	(cp) += 2; \
    } while (0)

/*
 * Put the fixed part of a broadcast IHU into the packet.
 */
#define	SLSP_PUT_BCAST_IHU(priority, holdtime, node_addr, lan_addr, cp) \
    do { \
	SLSP_PUT_LEADER(SLSP_BCAST_IHU_FIXED_LEN, SLSP_BCAST_IHU_TYPE, (cp)); \
	*(cp)++ = SLSP_BCAST_IHU_RTR_TYPE; \
	*(cp)++ = (priority) & SLSP_BCAST_PRIORITY_MASK; \
	SLSP_PUT_SHORT((holdtime), (cp)); \
	*(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_IPADDR((node_addr), (cp)); \
	*(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_IPADDR((lan_addr), (cp)); \
	*(cp)++ = 0; \
    } while (0)

/*
 * We don't support area addresses, really, since they don't make sense
 * when you aren't doing level one.  The get macro is expected to return
 * zero, while the put macro writes a zero.
 */
#define	SLSP_GET_BCAST_N_AREAS(nareas, cp) 	((nareas) = *(cp)++)

#define	SLSP_PUT_BCAST_N_AREAS(cp)	(*(cp)++ = 0)

/*
 * Initialize the constant parts of a broadcast IHU, including the
 * number of areas.
 */
#define	SLSP_INIT_BCAST_IHU(pkt) \
    do { \
	register byte *Xcp = (pkt); \
	SLSP_PUT_LEADER(SLSP_BCAST_IHU_FIXED_LEN, SLSP_BCAST_IHU_TYPE, Xcp); \
	*Xcp++ = SLSP_BCAST_IHU_RTR_TYPE; \
	Xcp += (1 + SLSP_LIFETIME_LEN); \
	*Xcp++ = 0; *Xcp++ = 0; \
	Xcp += SLSP_IPADDR_LEN; \
	*Xcp++ = 0; *Xcp++ = 0; \
	Xcp += SLSP_IPADDR_LEN; \
	*Xcp++ = 0; *Xcp++ = 0; \
    } while (0)

/*
 * Set the priority from the start address of the packet
 */
#define	SLSP_SET_BCAST_IHU_PRIORITY(priority, pkt) \
    (*((pkt) + SLSP_LEADER_LEN + 1) = (byte)(priority))
/*
 * Set the lifetime from the start address of the packet
 */
#define	SLSP_SET_BCAST_IHU_HOLDTIME(holdtime, pkt) \
    do { \
	register byte *Xcp = (pkt) + SLSP_LEADER_LEN + 2; \
	SLSP_PUT_SHORT((holdtime), Xcp); \
    } while (0)

/*
 * Set the node address given the start address of the packet
 */
#define	SLSP_SET_BCAST_IHU_NODE_ADDR(node_addr, pkt) \
    do { \
	register byte *Xcp = (pkt)+SLSP_LEADER_LEN+2+SLSP_LIFETIME_LEN+2; \
	SLSP_PUT_IPADDR((node_addr), Xcp); \
    } while (0)

/*
 * Set the lan ID given the start address of the packet
 */
#define	SLSP_SET_BCAST_IHU_LAN_ADDR(lan_addr, pkt) \
    do { \
	register byte *Xcp = \
	    (pkt)+SLSP_LEADER_LEN+2+SLSP_LIFETIME_LEN+2+SLSP_IPADDR_LEN+2; \
	SLSP_PUT_IPADDR((lan_addr), Xcp); \
    } while (0)

/*
 * Zero the lan ID given the start address of the packet
 */
#define	SLSP_ZERO_BCAST_IHU_LAN_ADDR(pkt) \
    do { \
	register byte *Xcp = \
	    (pkt)+SLSP_LEADER_LEN+2+SLSP_LIFETIME_LEN+2+SLSP_IPADDR_LEN+2; \
	*Xcp++ = 0; *Xcp++ = 0; \
	*Xcp++ = 0; *Xcp++ = 0; \
    } while (0)


/*
 * Get/put the number of neighbour routers.  Easy, it's only a byte.
 */
#define	SLSP_GET_BCAST_N_RTRS(nrtrs, cp)	((nrtrs) = *(cp)++)

#define	SLSP_PUT_BCAST_N_RTRS(nrtrs, cp)	(*(cp)++ = (nrtrs))

/*
 * Check the fixed fields in a router entry.
 */
#define	SLSP_CHK_BCAST_RTR(cp)	(*(cp) == 0 && *((cp)+1) == 0)

/*
 * Fetch the interesting parts of a broadcast router field
 */
#define	SLSP_GET_BCAST_RTR(rtr_id, priority, cp) \
    do { \
	(cp) += 2; \
	SLSP_GET_IPADDR((rtr_id), (cp)); \
	(priority) = *(cp)++; \
    } while (0)

/*
 * Put a broadcast router field into the packet
 */
#define	SLSP_PUT_BCAST_RTR(rtr_id, priority, cp) \
    do { \
	*(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_IPADDR((rtr_id), (cp)); \
	*(cp)++ = (priority); \
    } while (0)

/*
 * Set the broadcast router field in a packet without advancing the
 * pointer.
 */
#define	SLSP_SET_BCAST_RTR(rtr_id, priority, cp) \
    do { \
	register byte *Xcp = (cp); \
	SLSP_PUT_BCAST_RTR((rtr_id), (priority), Xcp); \
    } while (0)

/*
 * Set the number of broadcast routers based on a pointer to the beginning
 * of the packet.
 */
#define	SLSP_SET_BCAST_N_RTRS(nrtrs, pkt) \
    (*((pkt) + SLSP_BCAST_IHU_FIXED_LEN + SLSP_BCAST_N_AREAS_LEN) = (nrtrs))

/*
 * The SLSP link state packet.  The fixed part is followed by a list
 * of external ASes which we are exporting routes for (in the external
 * packet below) (this list isn't used for anything) followed by a list
 * of neighbour ID's and associated costs.
 */
#define	SLSP_LSP_TYPE		20	/* link state packet type */
#define	SLSP_LSP_FIXED_LEN	((size_t)36)	/* length of fixed part */
#define	SLSP_LSP_RTTYPE		3	/* means "attached level 2 router" */
#define	SLSP_LSP_RTTYPE_ALT	0	/* we might get this value too */

#define	SLSP_LSP_MIN_LEN	SLSP_LSP_FIXED_LEN

/*
 * The fixed part of the link state packet.  The variable part follows.
 */
typedef struct _slsp_lsp {
    slsp_leader slspl_leader;
#define	slspl_fixed_len	slspl_leader.slspx_length
#define	slspl_type	slspl_leader.slspx_type
    byte slspl_length[SLSP_PKT_LEN];	/* total length of packet */
    byte slspl_alt_length[SLSP_PKT_LEN]; /* also total length of packet */
    byte slspl_mbz[4];			/* constant 0's */
    byte slspl_lifetime[SLSP_LIFETIME_LEN];	/* remaining lifetime of data */
    byte slspl_mbz_also[2];		/* more constant 0's */
    byte slspl_id[SLSP_IPADDR_LEN];	/* node ID.  This is a subnet address */
    byte slspl_selector;		/* selector.  Used as part of node ID */
    byte slspl_rttype;			/* either 0 or 3.  I don't care */
    byte slspl_seqnum[SLSP_SEQNUM_LEN];	/* LSP sequence number */
    byte slspl_cksum[SLSP_CKSUM_LEN];	/* checksum for LSP */
} slsp_lsp;

/*
 * Check the basics in the fixed part.  Assumes the leader has
 * already been dealt with.  Returns true if everything is okay.
 */
#define	SLSP_CHK_LSP(cp) \
    (SLSP_CHK_LEADER_EXT((cp)) \
     && *((cp)+SLSP_L) == *((cp)+SLSP_L+4) \
     && *((cp)+SLSP_L+1) == *((cp)+SLSP_L+5) \
     && *((cp)+SLSP_L+2) == *((cp)+SLSP_L+6) \
     && *((cp)+SLSP_L+3) == *((cp)+SLSP_L+7) \
     && *((cp)+SLSP_L+8) == 0 && *((cp)+SLSP_L+9) == 0 \
     && *((cp)+SLSP_L+10) == 0 && *((cp)+SLSP_L+11) == 0 \
     && *((cp)+SLSP_L+14) == 0 && *((cp)+SLSP_L+15) == 0 \
     && *((cp)+SLSP_L+20) == 0 \
     && (*((cp)+SLSP_L+21) == SLSP_LSP_RTTYPE \
       || *((cp)+SLSP_L+21) == SLSP_LSP_RTTYPE_ALT))

/*
 * Fetch interesting stuff from the SLSP LSP.  We ignore the leader.
 * Pointer ends up pointing past end of LSP fixed part.
 */
#define	SLSP_GET_LSP(length, lifetime, addr, rttype, seqnum, cksum, cp) \
    do { \
	(cp) += SLSP_LEADER_LEN; \
	SLSP_GET_LONG((length), (cp)); \
	(cp) += 8; \
	SLSP_GET_SHORT((lifetime), (cp)); \
	(cp) += 2; \
	SLSP_GET_IPADDR((addr), (cp)); \
	(cp) += 1; \
	(rttype) = *(cp)++; \
	SLSP_GET_LONG((seqnum), (cp)); \
	SLSP_GET_SHORT((cksum), (cp)); \
    } while (0)

/*
 * Check the checksum in an LSP packet.  This assumes that the lifetime
 * field has already been zero'd.  Returns true if the checksum is okay.
 */
#define	SLSP_CHK_LSP_CKSUM(length, pkt) \
    (iso_cksum((void *)(pkt), (size_t)(length), (byte *)0) == 0)

/*
 * Set the lifetime in an LSP packet.  This is useful when checking the LSP
 * checksum.
 */
#define	SLSP_PUT_LSP_LIFETIME(lifetime, pkt) \
    do { \
	register u_int16 Xtmplife = (u_int16)(lifetime); \
	*((pkt)+SLSP_L+12) = (byte)(Xtmplife >> 8); \
	*((pkt)+SLSP_L+13) = (byte)Xtmplife; \
    } while (0)

/*
 * Set the length field in an LSP packet.  This might be useful if the
 * fixed part gets written first but the length is only determined later.
 */
#define	SLSP_PUT_LSP_LENGTH(length, pkt) \
    do { \
	register u_int32 Xtmplen = (u_int32)(length); \
	*((pkt)+SLSP_L  ) = *((pkt)+SLSP_L+4) = (byte)(Xtmplen >> 24); \
	*((pkt)+SLSP_L+1) = *((pkt)+SLSP_L+5) = (byte)(Xtmplen >> 16); \
	*((pkt)+SLSP_L+2) = *((pkt)+SLSP_L+6) = (byte)(Xtmplen >>  8); \
	*((pkt)+SLSP_L+3) = *((pkt)+SLSP_L+7) = (byte)(Xtmplen      ); \
    } while (0)

/*
 * Set the cksum in an LSP packet.
 */
#define	SLSP_PUT_LSP_CKSUM(cksum, pkt) \
    do { \
	register u_int16 Xtmpcksum = (u_int16)(cksum); \
	*((pkt)+SLSP_L+26) = (byte)(Xtmpcksum >> 8); \
	*((pkt)+SLSP_L+27) = (byte)Xtmpcksum; \
    } while (0)

/*
 * Write the fixed part of an LSP.  The pointer is left immediately
 * after the stuff written.
 */
#define	SLSP_PUT_LSP(length, lifetime, addr, rttype, seqnum, cksum, cp) \
    do { \
	SLSP_PUT_LEADER(SLSP_LSP_FIXED_LEN, SLSP_LSP_TYPE, (cp)); \
	do { \
	    register u_int32 Xtmplen = (u_int32)(length); \
	    *(cp) = *((cp)+4) = (byte)(Xtmplen >> 24); (cp) += 1; \
	    *(cp) = *((cp)+4) = (byte)(Xtmplen >> 16); (cp) += 1; \
	    *(cp) = *((cp)+4) = (byte)(Xtmplen >>  8); (cp) += 1; \
	    *(cp) = *((cp)+4) = (byte)(Xtmplen      ); (cp) += 5; \
	} while (0); \
	*(cp)++ = 0; *(cp)++ = 0; *(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_SHORT((lifetime), (cp)); \
	*(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_IPADDR((addr), (cp)); \
	*(cp)++ = 0; \
	*(cp)++ = (rttype); \
	SLSP_PUT_LONG((seqnum), (cp)); \
	SLSP_PUT_SHORT((cksum), (cp)); \
    } while (0)

/*
 * Compute the checksum for an LSP, putting it in the packet.
 */
#define	SLSP_SET_LSP_CKSUM(pkt, pktlen) \
    (iso_cksum((pkt), (pktlen), ((pkt)+SLSP_L+26)))


/*
 * The variable part of the LSP holds a couple of types of data, each
 * preceded by a (byte-long) code and a (byte-long) length for the data.
 * The first of these is a list of ASes which the router is advertising
 * external routes for.  The second is a list of the ID's of neighbour
 * systems to which we have direct links.
 */
#define	SLSP_LSP_CODE_AS	1	/* list of ASes which are attached */
#define	SLSP_LSP_CODE_LINKS	2	/* list of neighbour links */

typedef struct _slsp_lsp_payload {
    byte slspl_pay_code;		/* payload type code */
    byte slspl_pay_length;		/* total length of payload segment */
} slsp_lsp_payload;

/*
 * The AS payload is a SLSP ASADDR preceeded by a byte "length".
 */
#define	SLSP_LSP_AS_LEN		((size_t)1+SLSP_ASADDR_LEN)
#define	SLSP_LSP_AS_MAX_BUCKET	(((size_t)255) - SLSP_LSP_AS_LEN)

typedef struct _slsp_lsp_as {
    byte slspl_as_length;		/* 5 fixed, length of an AS "address" */
    byte slspl_as_idp[SLSP_ADDR_IDP_LEN];	/* 47, 0, 6 */
    byte slspl_as_as[SLSP_AS_LEN];	/* the AS number itself */
} slsp_lsp_as;

/*
 * Check the fixed fields in the SLSP lsp AS payload.  Returns true if
 * everything looks good.
 */
#define	SLSP_CHK_LSP_AS(cp) \
    (*(cp) == SLSP_ASADDR_LEN && SLSP_CHK_AS((cp) + 1))

/*
 * Fetch the AS from a SLSP lsp AS payload.  Leaves the pointer past the
 * end of the AS address.
 */
#define	SLSP_GET_LSP_AS(as, cp) \
    do { \
	(cp) += 1 + SLSP_ADDR_IDP_LEN; \
	SLSP_GET_SHORT((as), (cp)); \
    } while (0)

/*
 * Write an AS into the lsp payload.  Leaves the pointer past the end of
 * the data just written.
 */
#define	SLSP_PUT_LSP_AS(as, cp) \
    do { \
	*(cp)++ = SLSP_ASADDR_LEN; \
	SLSP_PUT_ASADDR((as), (cp)); \
    } while (0)

/*
 * The neighbour links payload is not so pretty.  After the payload is
 * a reserved byte, followed by a cost (which applies to all neighbours
 * in the packet), followed by an array of (2 byte mbz)+(4 byte node addr)
 * +(1 byte selector).  We dig out the cost and all the address+selector
 * fields.
 */
#define	SLSP_LSP_LINK_MIN_LEN	((size_t)2)	/* minimum length of payload data */
#define	SLSP_LSP_LINK_ID_LEN	((size_t)7)	/* 2 mbz + 4 address + 1 sel */

typedef struct _slsp_lsp_link_leader {
    byte slspl_link_mbz;		/* must be zero */
    byte slspl_link_cost;		/* cost of these links */
} slsp_lsp_link_leader;

typedef struct _slsp_lsp_linkid {
    byte slspl_linkid_mbz[2];			/* 2 bytes of mbz */
    byte slspl_linkid_addr[SLSP_IPADDR_LEN];	/* 4 byte IP address */
    byte slspl_linkid_sel;			/* 1 byte selector */
} slsp_lsp_linkid;

/*
 * Check that the link leader has a leading zero.  Returns true if all is okay.
 */
#define	SLSP_CHK_LINK_LEADER(cp)	(*(cp) == 0)

/*
 * Check that the two leading zeros exist in a link ID.  Returns true if okay.
 */
#define	SLSP_CHK_LINK_ID(cp) \
    (*(cp) == 0 && *((cp)+1) == 0 && *((cp)+6) == 0)

/*
 * Fetch the cost from the leader
 */
#define	SLSP_GET_LINK_COST(cost, cp) \
    do { \
	(cp)++; \
	(cost) = *(cp)++; \
    } while (0)

/*
 * Fetch a link ID/address and selector from the packet.
 */
#define	SLSP_GET_LINK_ID(addr, cp) \
    do { \
	(cp) += 2; \
	SLSP_GET_IPADDR((addr), (cp)); \
	(cp) += 1; \
    } while (0)

/*
 * Write the link leader into the packet.
 */
#define	SLSP_PUT_LINK_COST(cost, cp) \
    do { \
	*(cp)++ = 0; \
	*(cp)++ = (cost); \
    } while (0)

/*
 * Write a link ID into the packet.
 */
#define	SLSP_PUT_LINK_ID(addr, cp) \
    do { \
	*(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_IPADDR((addr), (cp)); \
	*(cp)++ = 0; \
    } while (0)


/*
 * The SLSP Sequence Numbers packet is used for acknowlegements.  This
 * is distinguished in that it uses the short leader format.  The fixed
 * part of the format is shown below.
 */
#define	SLSP_SEQ_TYPE		22	/* sequence numbers packet type */
#define	SLSP_SEQ_FIXED_LEN	((size_t) 26)	/* fixed length portion of packet */

typedef struct _slsp_seq {
    slsp_short_leader_bytes slspq_leader;	/* short leader */
    byte slspq_mbz1[2];				/* two zero bytes */
    byte slspq_id[SLSP_IPADDR_LEN];		/* node ID/address */
    byte slspq_flags;				/* flags byte */
    byte slspq_length[SLSP_PKT_LEN];		/* total length of packet */
    byte slspq_alt_length[SLSP_PKT_LEN];	/* same as above */
    byte slspq_mbz2[4];				/* four zero bytes */
    byte slspq_entry_count[2];			/* number of sequence entries */
} slsp_seq;

/*
 * The slspq_flags byte indicates whether the Sequence Numbers packet
 * contains full or partial information.
 */
#define	SLSP_SEQ_FULL		0x3
#define	SLSP_SEQ_PARTIAL	0x2

/*
 * The variable part of the SLSP Sequence Numbers packet contains zero
 * or more sequence number entries, appended to the above.
 */
#define	SLSP_SEQ_ENT_LEN	((size_t) 15)		/* length of a sequence entry */

typedef struct _slsp_seq_entry {
    byte slspq_ent_type;			/* type of entry router/ext */
    byte slspq_ent_mbz1;			/* zero byte */
    byte slspq_ent_id[SLSP_IPADDR_LEN];		/* node ID this applies to */
    byte slspq_ent_mbz2;			/* another zero byte */
    byte slspq_ent_seqnum[SLSP_SEQNUM_LEN];	/* sequence number of LSP */
    byte slspq_ent_age[SLSP_LIFETIME_LEN];	/* age of LSP */
    byte slspq_ent_cksum[SLSP_CKSUM_LEN];	/* checksum of LSP */
} slsp_seq_entry;

/*
 * For slspq_ent_type above
 */
#define	SLSP_SEQ_ENT_TYPE_ROUTER	0	/* router LSP */
#define	SLSP_SEQ_ENT_TYPE_EXT		1	/* external LSP */

/*
 * Check the fixed fields in a sequence number packet
 */
#define	SLSP_CHK_SEQ(cp) \
    (*((cp)+SLSP_SL) == 0 && *((cp)+SLSP_SL+1) == 0 \
    && *((cp)+SLSP_SL+7) == *((cp)+SLSP_SL+11) \
    && *((cp)+SLSP_SL+8) == *((cp)+SLSP_SL+12) \
    && *((cp)+SLSP_SL+9) == *((cp)+SLSP_SL+13) \
    && *((cp)+SLSP_SL+10) == *((cp)+SLSP_SL+14) \
    && *((cp)+SLSP_SL+15) == 0 && *((cp)+SLSP_SL+16) == 0 \
    && *((cp)+SLSP_SL+17) == 0 && *((cp)+SLSP_SL+18) == 0)

/*
 * Check the fixed fields in a sequence number entry
 */
#define	SLSP_CHK_SEQ_ENT(cp)	(*((cp)+0) == 0 && *((cp)+1) == 0)

/*
 * Given a number of entries, compute the total length of a sequence
 * numbers packet.  Multiply the number of entries by the length
 * of an entry and add the fixed length.
 */
#define	SLSP_SEQ_LENGTH(nent)	(((nent)*SLSP_SEQ_ENT_LEN) + SLSP_SEQ_FIXED_LEN)

/*
 * Given the length of a sequence numbers packet, compute the number of
 * entries in the packet.
 */
#define	SLSP_SEQ_N_ENTRIES(len)	(((len)-SLSP_SEQ_FIXED_LEN) / SLSP_SEQ_ENT_LEN)

/*
 * Given an entry number (0..(nument-1)) and the start of a sequence numbers
 * packet, compute the address of the sequence number entry.
 */
#define	SLSP_SEQ_ENTRY(entnum, pkt) \
    (((byte *)(pkt)) + SLSP_SEQ_FIXED_LEN + (SLSP_SEQ_ENT_LEN * (entnum)))

/*
 * Fetch the interesting stuff from the fixed part of the sequence number pkt.
 */
#define	SLSP_GET_SEQ(node_addr, type, length, ent_count, cp) \
    do { \
	(cp) += SLSP_SHORT_LEADER_LEN + 2; \
	SLSP_GET_IPADDR((node_addr), (cp)); \
	(type) = *(cp)++; \
	SLSP_GET_LONG((length), (cp)); \
	(cp) += SLSP_PKT_LEN + 4; \
	SLSP_GET_SHORT((ent_count), (cp)); \
    } while (0)

/*
 * Get the interesting stuff from a sequence number entry
 */
#define	SLSP_GET_SEQ_ENT(type, node_addr, seqnum, age, cksum, cp) \
    do { \
	(cp) += 2; \
	SLSP_GET_IPADDR((node_addr), (cp)); \
	(type) = *(cp)++; \
	SLSP_GET_LONG((seqnum), (cp)); \
	SLSP_GET_SHORT((age), (cp)); \
	SLSP_GET_SHORT((cksum), (cp)); \
    } while (0)

/*
 * Format the fixed part of a sequence numbers packet
 */
#define	SLSP_PUT_SEQ(node_addr, type, length, ent_count, cp) \
    do { \
	SLSP_PUT_SHORT_LEADER(SLSP_SEQ_FIXED_LEN, SLSP_SEQ_TYPE, (cp)); \
	*(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_IPADDR((node_addr), (cp)); \
	*(cp)++ = (byte)(type); \
	do { \
	    register u_int32 Xlen = (u_int32)(length); \
	    register byte *Xcp = (cp); \
	    (cp) += SLSP_PKT_LEN; \
	    *(cp)++ = *Xcp++ = (byte)(Xlen >> 24); \
	    *(cp)++ = *Xcp++ = (byte)(Xlen >> 16); \
	    *(cp)++ = *Xcp++ = (byte)(Xlen >>  8); \
	    *(cp)++ = *Xcp++ = (byte)(Xlen      ); \
	} while (0); \
	*(cp)++ = 0; *(cp)++ = 0; \
	*(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_SHORT((ent_count), (cp)); \
    } while (0)

/*
 * Initialize the fixed part of a sequence numbers packet, skipping
 * the length and number of entries fields, based on the start address
 * of the packet.
 */
#define	SLSP_INIT_SEQ(node_addr, type, pkt) \
    do { \
	register byte *Xpkt = (pkt); \
	SLSP_PUT_SHORT_LEADER(SLSP_SEQ_FIXED_LEN, SLSP_SEQ_TYPE, Xpkt); \
	*Xpkt++ = 0; *Xpkt++ = 0; \
	SLSP_PUT_IPADDR((node_addr), Xpkt); \
	*Xpkt++ = (byte)(type); \
	Xpkt += (SLSP_PKT_LEN + SLSP_PKT_LEN); \
	*Xpkt++ = 0; *Xpkt++ = 0; \
	*Xpkt++ = 0; *Xpkt++ = 0; \
    } while (0)

/*
 * Set the length and number of entries into a sequence numbers packet
 * given the start of the packet.
 */
#define	SLSP_SET_SEQ_LEN(length, ent_count, pkt) \
    do { \
	register u_int32 Xtmp = (u_int32)(length); \
	register byte *Xpkt2 = (pkt) + SLSP_SHORT_LEADER_LEN + 7; \
	register byte *Xpkt = Xpkt2 + SLSP_PKT_LEN; \
	*Xpkt++ = *Xpkt2++ = (byte)(Xtmp >> 24); \
	*Xpkt++ = *Xpkt2++ = (byte)(Xtmp >> 16); \
	*Xpkt++ = *Xpkt2++ = (byte)(Xtmp >>  8); \
	*Xpkt++ = *Xpkt2++ = (byte)(Xtmp      ); \
	Xpkt += 4; Xtmp = (u_int32)(ent_count); \
	*Xpkt++ = (byte)(Xtmp >> 8); \
	*Xpkt++ = (byte)(Xtmp     ); \
    } while (0)

/*
 * Put a sequence number entry into the packet.
 */
#define	SLSP_PUT_SEQ_ENT(type, node_addr, seqnum, age, cksum, cp) \
    do { \
	*(cp)++ = 0; \
	*(cp)++ = 0; \
	SLSP_PUT_IPADDR((node_addr), (cp)); \
	*(cp)++ = (type); \
	SLSP_PUT_LONG((seqnum), (cp)); \
	SLSP_PUT_SHORT((age), (cp)); \
	SLSP_PUT_SHORT((cksum), (cp)); \
    } while (0)

/*
 * Set the age field in a sequence number packet
 */
#define	SLSP_SET_SEQ_ENT_AGE(age, ent) \
    do { \
	register byte *Xent = (ent) + 11; \
	SLSP_PUT_SHORT((age), (Xent)); \
    } while (0)

/*
 * Set the "changeable" fields in a sequence number entry
 */
#define	SLSP_SET_SEQ_ENT_CHANGE(seqnum, age, cksum, ent) \
    do { \
	register byte *Xent = (ent) + 7; \
	SLSP_PUT_LONG((seqnum), Xent); \
	SLSP_PUT_SHORT((age), Xent); \
	SLSP_PUT_SHORT((cksum), Xent); \
    } while (0)


/*
 * The last item is the SLSP External routes packet (formerly an
 * IS-IS ES links PDU).  The fixed part looks a lot like the SLSP
 * LSP above, but is reproduced here since copying with the editor
 * is cheap.
 *
 * Note that this PDU is not sent by some current implementations of the
 * SLSP protocol, and may not be supported here.  The stuff about BGP
 * info below is an experimental idea which may never be implemented.
 */
#define	SLSP_EXT_TYPE		21	/* external routes packet type */
#define	SLSP_EXT_FIXED_LEN	((size_t)36)	/* length of fixed part */
#define	SLSP_EXT_RTTYPE		3	/* means "attached level 2 router" */
#define	SLSP_EXT_RTTYPE_ALT	0	/* we might get this value too */

/*
 * The fixed part of the link state packet.  The variable part follows.
 */
typedef struct _slsp_external {
    slsp_leader slspe_leader;
#define	slspe_fixed_len	slspe_leader.slspx_length
#define	slspe_type	slspe_leader.slspx_type
    byte slspe_length[4];		/* total length of packet */
    byte slspe_alt_length[4];		/* also total length of packet */
    byte slspe_mbz[4];			/* constant 0's */
    byte slspe_lifetime[SLSP_LIFETIME_LEN];	/* remaining lifetime of data */
    byte slspe_mbz_also[2];		/* more constant 0's */
    byte slspe_id[SLSP_IPADDR_LEN];	/* node ID.  This is a subnet address */
    byte slspe_selector;		/* selector.  Used as part of node ID */
    byte slspe_rttype;			/* either 0 or 3.  I don't care */
    byte slspe_seqnum[SLSP_SEQNUM_LEN];	/* LSP sequence number */
    byte slspe_cksum[SLSP_CKSUM_LEN];	/* checksum for LSP */
} slsp_external;

/*
 * Check the basics in the fixed part.  Assumes the leader has
 * already been dealt with.  Returns true if everything is okay.
 */
#define	SLSP_CHK_EXT(cp) \
    (*((cp)+SLSP_L) == *((cp)+SLSP_L+4) \
     && *((cp)+SLSP_L+1) == *((cp)+SLSP_L+5) \
     && *((cp)+SLSP_L+2) == *((cp)+SLSP_L+6) \
     && *((cp)+SLSP_L+3) == *((cp)+SLSP_L+7) \
     && *((cp)+SLSP_L+8) == 0 && *((cp)+SLSP_L+9) == 0 \
     && *((cp)+SLSP_L+10) == 0 && *((cp)+SLSP_L+11) == 0 \
     && *((cp)+SLSP_L+14) == 0 && *((cp)+SLSP_L+15) == 0 \
     && *((cp)+SLSP_L+20) == 0 \
     && (*((cp)+SLSP_L+21) == SLSP_EXT_RTTYPE \
       || *((cp)+SLSP_L+21) == SLSP_EXT_RTTYPE_ALT))

/*
 * Fetch interesting stuff from the SLSP external packet.  We ignore the leader.
 * Pointer ends up pointing past end of EXT fixed part.
 */
#define	SLSP_GET_EXT(length, lifetime, addr, rttype, seqnum, cksum, cp) \
    do { \
	(cp) += SLSP_LEADER_LEN; \
	SLSP_GET_LONG((length), (cp)); \
	(cp) += 8; \
	SLSP_GET_SHORT((lifetime), (cp)); \
	(cp) += 2; \
	SLSP_GET_IPADDR((addr), (cp)); \
	(cp) += 1; \
	(rttype) = *(cp)++; \
	SLSP_GET_LONG((seqnum), (cp)); \
	SLSP_GET_SHORT((cksum), (cp)); \
    } while (0)

/*
 * Check the checksum in an external routes packet.  This assumes that the
 * lifetime field has already been zero'd.  Returns true if the checksum is
 * okay.
 */
#define	SLSP_CHK_EXT_CKSUM(length, pkt) \
    (iso_cksum((void *)(pkt), length, (byte *)0) == 0)

/*
 * Set the lifetime in an external routes packet.  This is useful when
 * checking the checksum.
 */
#define	SLSP_PUT_EXT_LIFETIME(lifetime, pkt) \
    do { \
	register u_int16 Xtmplife = (u_int16)(lifetime); \
	*((pkt)+SLSP_L+12) = (byte)(Xtmplife >> 8); \
	*((pkt)+SLSP_L+13) = (byte)Xtmplife; \
    } while (0)

/*
 * Set the length field in an external routes packet.  This might be useful
 * if the fixed part gets written first but the length is only determined later.
 */
#define	SLSP_PUT_EXT_LENGTH(length, pkt) \
    do { \
	register u_int32 Xtmplen = (u_int32)(length); \
	*((pkt)+SLSP_L  ) = *((pkt)+SLSP_L+4) = (byte)(Xtmplen >> 24); \
	*((pkt)+SLSP_L+1) = *((pkt)+SLSP_L+5) = (byte)(Xtmplen >> 16); \
	*((pkt)+SLSP_L+2) = *((pkt)+SLSP_L+6) = (byte)(Xtmplen >>  8); \
	*((pkt)+SLSP_L+3) = *((pkt)+SLSP_L+7) = (byte)(Xtmplen      ); \
    } while (0)

/*
 * Set the cksum in an external routes packet.
 */
#define	SLSP_PUT_EXT_CKSUM(cksum, pkt) \
    do { \
	register u_int16 Xtmpcksum = (u_int16)(cksum); \
	*((pkt)+SLSP_L+26) = (byte)(Xtmpcksum >> 8); \
	*((pkt)+SLSP_L+27) = (byte)Xtmpcksum; \
    } while (0)

/*
 * Write the fixed part of an external routes packet.  The pointer is left
 * immediately after the stuff written.
 */
#define	SLSP_PUT_EXT(length, lifetime, addr, rttype, seqnum, cksum, cp) \
    do { \
	SLSP_PUT_LEADER(SLSP_EXT_FIXED_LEN, SLSP_EXT_TYPE, (cp)); \
	do { \
	    register u_int32 Xtmplen = (u_int32)(length); \
	    *(cp) = *((cp)+4) = (byte)(Xtmplen >> 24); (cp) += 1; \
	    *(cp) = *((cp)+4) = (byte)(Xtmplen >> 16); (cp) += 1; \
	    *(cp) = *((cp)+4) = (byte)(Xtmplen >>  8); (cp) += 1; \
	    *(cp) = *((cp)+4) = (byte)(Xtmplen      ); (cp) += 5; \
	} while (0); \
	*(cp)++ = 0; *(cp)++ = 0; *(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_SHORT((lifetime), (cp)); \
	*(cp)++ = 0; *(cp)++ = 0; \
	SLSP_PUT_IPADDR((addr), (cp)); \
	*(cp)++ = 0; \
	*(cp)++ = (byte)(rttype); \
	SLSP_PUT_LONG((seqnum), (cp)); \
	SLSP_PUT_SHORT((cksum), (cp)); \
    } while (0)

/*
 * The variable part of the external routes packet holds a couple of types
 * of data, each preceded by a (byte-long) code and a (byte-long) length for
 * the data.  The first type is the ASRT data, which includes a simple list
 * of network routes (e.g. routes to whole networks) tagged by the AS of the
 * advertising external neighbour.  The second is an experimental type
 * to allow carrying internal BGP data directly in the link state flooding
 * protocol.
 */
#define	SLSP_EXT_CODE_ROUTES	2	/* list of external network routes */
#define	SLSP_EXT_CODE_BGP	99	/* experimental BGP-style routes */

typedef struct _slsp_exp_payload {
    byte slspe_pay_code;		/* payload type code */
    byte slspe_pay_length;		/* total length of payload segment */
} slsp_exp_payload;

/*
 * The ROUTES payload consists of a (byte-long) cost followed by one or
 * more entries which hold an AS and address.  Do not mistake these for
 * SLSP addresses, there is an extra MBZ byte between the initial part
 * and the AS.
 */
#define	SLSP_EXP_RT_LEN		14	/* length of an external route */
#define	SLSP_EXP_RT_NIBBLELEN	26	/* length of address, in nibbles */
/* number of SLSP externals which fit in bucket.  254 is max, 1 is cost */
#define	SLSP_MAX_PER_BUCKET	((254 - 1) / SLSP_EXP_RT_LEN)

typedef struct _slsp_exp_route_cost {
    byte slspe_rt_cost;				/* cost for following routes */
} slsp_exp_route_cost;

typedef struct _slsp_exp_route {
    byte slspe_rt_nibble_len;			/* see SLSP_EXP_RT_NIBBLELEN */
    byte slspe_rt_idp[SLSP_ADDR_IDP_LEN];	/* 47, 0, 6 */
    byte slspe_rt_mbz_also;			/* 0 byte */
    byte slspe_rt_as[SLSP_AS_LEN];		/* the AS number itself */
    byte slspe_rt_mbz[2];			/* 2 bytes of zero */
    byte slspe_rt_addr[SLSP_IPADDR_LEN];	/* route network address */
    byte slspe_rt_selector;			/* an mbz byte too */
} slsp_exp_route;

/*
 * Check the fixed fields in the SLSP external route.  Returns true if
 * everything looks good.
 */
#define	SLSP_CHK_EXP_ROUTE(cp) \
    (*(cp) == SLSP_EXP_RT_NIBBLELEN && *((cp)+1) == SLSP_ADDR_IDP_0 \
     && *((cp)+2) == SLSP_ADDR_IDP_1 && *((cp)+3) == SLSP_ADDR_IDP_2 \
     && *((cp)+4) == 0 && *((cp)+7) == 0 && *((cp)+8) == 0 && *((cp)+13) == 0)

/*
 * Fetch the SLSP external route cost.  Leaves pointer past end of cost.
 */
#define	SLSP_GET_EXT_RT_COST(cost, cp) 	((cost) = *(cp)++)

/*
 * Fetch the useful contents (6 of 14 bytes) of a SLSP external route.
 * Leaves the pointer past the end of the route.
 */
#define	SLSP_GET_EXT_RT(as, addr, cp) \
    do { \
	(cp) += 5; \
	SLSP_GET_SHORT((as), (cp)); \
	(cp) += 2; \
	SLSP_GET_IPADDR((addr), (cp)); \
	(cp) += 1; \
    } while (0)

/*
 * Write the SLSP external route cost into a packet.
 */
#define	SLSP_PUT_EXT_RT_COST(cost, cp)	(*(cp)++ = (cost))

/*
 * Write a SLSP external route into a packet.
 */
#define	SLSP_PUT_EXT_RT(as, addr, cp) \
    do { \
	*(cp)++ = SLSP_EXP_RT_NIBBLELEN; \
	*(cp)++ = SLSP_ADDR_IDP_0; \
	*(cp)++ = SLSP_ADDR_IDP_1; \
	*(cp)++ = SLSP_ADDR_IDP_2; \
	*(cp)++ = 0; \
	SLSP_PUT_SHORT((as), (cp)); \
	*(cp)++ = 0; \
	*(cp)++ = 0; \
	SLSP_PUT_IPADDR((addr), (cp)); \
	*(cp)++ = 0; \
    } while (0)

/*
 * XXX Leave BGP stuff for later.
 */

/*
 * %(Copyright)
 */
