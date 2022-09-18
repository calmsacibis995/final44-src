/*
 * $Id: ospf_log.h,v 1.13.2.5 1994/09/15 21:38:01 jch Exp $
 */

/* %(Copyright.header) */


extern const char *ospf_con_types[];
extern const bits ospf_logtype[];
extern u_long ospf_cumlog[];
extern const char *ospf_intf_states[];
extern const char *ospf_nbr_states[];
extern const bits ospf_ls_type_bits[];
extern u_int ospf_log_last_lsa;
extern const bits ospf_nh_bits[];
extern const bits ospf_sched_bits[];
extern const bits ospf_router_type_bits[];

/**************************************************************************
	
			OLOG CODES

***************************************************************************/

#define	TR_OSPF_DETAIL_HELLO	TR_DETAIL_1
#define	TR_OSPF_DETAIL_DD	TR_DETAIL_2
#define	TR_OSPF_DETAIL_LSR	TR_DETAIL_3
#define	TR_OSPF_DETAIL_LSU	TR_DETAIL_4
#define	TR_OSPF_DETAIL_ACK	TR_DETAIL_5

#define	TR_OSPF_INDEX_PACKETS	0
#define	TR_OSPF_INDEX_HELLO	1
#define	TR_OSPF_INDEX_DD	2
#define	TR_OSPF_INDEX_LSR	3
#define	TR_OSPF_INDEX_LSU	4
#define	TR_OSPF_INDEX_ACK	5

#define	TR_OSPF_LSA_BLD	TR_USER_1
#define	TR_OSPF_SPF	TR_USER_2
#define	TR_OSPF_LSA_TX	TR_USER_3
#define	TR_OSPF_LSA_RX	TR_USER_4
#define	TR_OSPF_TRAP	TR_USER_5
#ifdef	DEBUG
#define	TR_OSPF_DEBUG	TR_USER_6
#endif	/* DEBUG */

extern const flag_t ospf_trace_masks[];

#define GOOD_RX			0

/* receive types */
#define	OSPF_RECV_MON		0
#define	OSPF_RECV_HELLO		1
#define	OSPF_RECV_DD		2
#define	OSPF_RECV_LSR		3
#define	OSPF_RECV_LSU		4
#define	OSPF_RECV_LSA		5

#define	OSPF_SEND_BASE		6
#define	OSPF_SEND_MON		6
#define	OSPF_SEND_HELLO		7
#define	OSPF_SEND_DD		8
#define	OSPF_SEND_LSR		9
#define	OSPF_SEND_LSU		10
#define	OSPF_SEND_LSA		11

#define	OSPF_ERR_BASE		12
#define OSPF_ERR_IP_DEST	12
#define OSPF_ERR_IP_PROTO	13
#define	OSPF_ERR_IP_ECHO	14
#define	OSPF_ERR_OSPF_TYPE	15
#define OSPF_ERR_OSPF_VERSION	16
#define	OSPF_ERR_OSPF_CHKSUM	17
#define OSPF_ERR_OSPF_AREAID	18
#define OSPF_ERR_OSPF_ABR	19
#define OSPF_ERR_OSPF_VL	20
#define	OSPF_ERR_OSPF_AUTH_TYPE	21
#define	OSPF_ERR_OSPF_AUTH_KEY	22
#define	OSPF_ERR_OSPF_SHORT	23
#define OSPF_ERR_OSPF_LONG	24
#define	OSPF_ERR_OSPF_SEND	25
#define	OSPF_ERR_OSPF_IFDOWN   	26
#define	OSPF_ERR_OSPF_NBR	27
#define OSPF_ERR_HELLO_MASK  	28
#define OSPF_ERR_HELLO_TIMER 	29
#define OSPF_ERR_HELLO_DEAD	30
#define OSPF_ERR_HELLO_E 	31
#define OSPF_ERR_HELLO_ID	32
#define OSPF_ERR_HELLO_VIRT	33
#define OSPF_ERR_HELLO_NBMA	34
#define OSPF_ERR_DD_STATE	35
#define OSPF_ERR_DD_RTRID	36
#define OSPF_ERR_DD_E		37
#define OSPF_ERR_DD_TYPE	38
#define OSPF_ERR_ACK_STATE	39
#define	OSPF_ERR_ACK_BAD	40
#define	OSPF_ERR_ACK_DUP	41
#define OSPF_ERR_ACK_TYPE	42
#define OSPF_ERR_REQ_STATE	43
#define OSPF_ERR_REQ_EMPTY	44
#define OSPF_ERR_REQ_BOGUS     	45
#define OSPF_ERR_UPD_STATE	46
#define OSPF_ERR_UPD_NEWER	47
#define OSPF_ERR_UPD_CHKSUM   	48
#define OSPF_ERR_UPD_OLDER	49
#define OSPF_ERR_UPD_TYPE	50
#define OSPF_ERR_LAST		51


/* Flags to indicate when we should log */

#define	OSPF_LOGF_NEVER		0x0	/* Never syslog */
#define	OSPF_LOGF_ALWAYS	0x01	/* Always log */
#define	OSPF_LOGF_TIMER		0x02	/* After startup */

/* */

#define	OSPF_LOG_TIME(intf)	(time_sec - (intf)->up_time > (intf)->dead_timer * 2)
#define	OSPF_LOG_RECORD(type)	{assert(type < OSPF_ERR_LAST); ospf_cumlog[type]++;}
#define	OSPF_LOG_RECORD_TX(type)	{assert(type < OSPF_SEND_BASE); ospf_cumlog[type + OSPF_SEND_BASE]++;}
#define	OSPF_LOG_RX(type, intf, src, dst) { OSPF_LOG_RECORD(type); if (type >= OSPF_ERR_BASE) ospf_log_rx(type, intf, src, dst); }
#define	OSPF_LOG_RX_LSA1(type, intf, src, dst, db, desc, age) { \
    OSPF_LOG_RECORD(type); \
    if (ospf_log_last_lsa != (type)) { \
	ospf_log_last_lsa = (type); \
	ospf_log_rx(type, intf, src, dst); \
    } \
    ospf_log_ls_hdr(db, desc, age, (time_t) 0); \
}
#define	OSPF_LOG_RX_LSA2(type, intf, src, dst, lsa, db) { \
    OSPF_LOG_RECORD(type); \
    if (ospf_log_last_lsa != (type)) { \
	ospf_log_last_lsa = (type); \
	ospf_log_rx(type, intf, src, dst); \
    } \
    ospf_log_ls_hdr(lsa, "	RECV", (lsa)->ls_age, (time_t) 0); \
    ospf_log_ls_hdr(&DB_RTR(db)->ls_hdr, "	HAVE", LS_AGE(db), db->lsdb_time); \
}

/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
