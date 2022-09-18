/*
 * $Id: hello.h,v 1.21.2.1 1994/03/04 01:46:39 jch Exp $
 */

/* %(Copyright.header) */


#ifdef	PROTO_HELLO

#ifndef IPPROTO_HELLO
#define	IPPROTO_HELLO		63
#endif	/* IPPROTO_HELLO */
#define	HELLO_UNREACHABLE	30000			/* in ms */
#define	HELLO_HOP		100			/* minimum delay */
#define	HELLO_T_UPDATE		(time_t) 15		/* in seconds */
#define	HELLO_T_HOLDDOWN	(time_t) 120		/* in seconds */
#define	HELLO_T_EXPIRE		(time_t) 180		/* in seconds */
#define	HELLO_T_FLASH	(time_t) (grand((u_int32) (HELLO_T_MAX - HELLO_T_MIN + 1)) + HELLO_T_MIN)
#define	HELLO_T_MAX	(time_t) 5
#define	HELLO_T_MIN	(time_t) 1
#define	HELLO_HYST(s)	(s >> 2)	/* 25% of old route, in ms */

/* For parser */
#define	HELLO_LIMIT_DELAY	HELLO_HOP, HELLO_UNREACHABLE

#define	HELLO_CONFIG_IN			1
#define	HELLO_CONFIG_OUT		2
#define	HELLO_CONFIG_METRICIN		3
#define	HELLO_CONFIG_METRICOUT		4
#define	HELLO_CONFIG_MAX		5


#define	HELLO_DEFAULT	0		/* net 0 as default */

#define	METRIC_DIFF(x,y)	(x > y ? x - y : y - x)

/* Task specific info */
#define	HELLO_HOLDCOUNT		(HELLO_T_HOLDDOWN/HELLO_T_UPDATE)	/* Number of updates per holddown */

/*	Define the DCN HELLO protocol packet			*/

struct hellohdr {
    u_int16 h_cksum;			/* Ip checksum of this header and data ares */
    u_int16 h_date;			/* Julian days since 1 January 1972 */
    u_int32 h_time;			/* Local time (milliseconds since midnight UT) */
    u_int16 h_tstp;			/* (used to calculate delay/offset) */
};

#define	Size_hellohdr	10
#define	PickUp_hellohdr(s, hellohdr) \
  PickUp(s, hellohdr.h_cksum); \
  PickUp(s, hellohdr.h_date); GNTOHS(hellohdr.h_date); \
  PickUp(s, hellohdr.h_time); GNTOHL(hellohdr.h_time); \
  PickUp(s, hellohdr.h_tstp); GNTOHS(hellohdr.h_tstp);
#define	PutDown_hellohdr(s, hellohdr) \
  PutDown(s, hellohdr.h_cksum);\
  GHTONS(hellohdr.h_date); PutDown(s, hellohdr.h_date);\
  GHTONL(hellohdr.h_time); PutDown(s, hellohdr.h_time);\
  GHTONS(hellohdr.h_tstp); PutDown(s, hellohdr.h_tstp);

#define	H_DATE_BITS	0xC000		/* Flag bits */
#define	H_DATE_LEAPADD	0x4000		/* Insert leap second at end of current day */
#define	H_DATE_LEAPDEL	0x8000		/* Delete leap second at end of current day */
#define	H_DATE_UNSYNC	0xC000		/* Clock is unsynchronized */

#define	H_DATE_MON_SHIFT	10
#define	H_DATE_MON_MASK		0x0f
#define	H_DATE_DAY_SHIFT	5
#define	H_DATE_DAY_MASK		0x1f
#define	H_DATE_YEAR_SHIFT	0
#define	H_DATE_YEAR_MASK	0x1f
#define	H_DATE_YEAR_BASE	72


struct hm_hdr {
    u_int8 hm_count;			/* Number of elements that follow */
    u_int8 hm_type;			/* Type of elements */
};

#define	Size_hm_hdr	2
#define	PickUp_hm_hdr(s, hm_hdr) \
  PickUp(s, hm_hdr.hm_count);\
  PickUp(s, hm_hdr.hm_type);
#define	PutDown_hm_hdr(s, hm_hdr) \
  PutDown(s, hm_hdr.hm_count);\
  PutDown(s, hm_hdr.hm_type);


struct type0pair {
    u_int16 d0_delay;			/* Delay to peer (milliseconds) */
    u_int16 d0_offset;			/* Clock offset of peer (milliseconds) */
};

#define	Size_type0pair	4
#define	PickUp_type0pair(s, type0pair) \
  PickUp(s, type0pair.d0_delay);  GNTOHS(type0pair.d0_delay);\
  PickUp(s, type0pair.d0_offset); GNTOHS(type0pair.d0_offset);
#define	PutDown_type0pair(s, type0pair) \
  GHTONS(type0pair.d0_delay); PutDown(s, type0pair.d0_delay);\
  GHTONS(type0pair.d0_offset); PutDown(s, type0pair.d0_offset);


struct type1pair {
    u_int32 d1_dst;			/* IP host/network address */
    u_int16 d1_delay;			/* Delay to peer (milliseconds) */
    s_int16 d1_offset;			/* CLock offset of peer (milliseconds) */
};

#define	Size_type1pair	8
#define	PickUp_type1pair(s, type1pair) \
  PickUp(s, type1pair.d1_dst);\
  PickUp(s, type1pair.d1_delay); GNTOHS(type1pair.d1_delay);\
  PickUp(s, type1pair.d1_offset); GNTOHS(type1pair.d1_offset);
#define	PutDown_type1pair(s, type1pair) \
  PutDown(s, type1pair.d1_dst);\
  GHTONS(type1pair.d1_delay); PutDown(s, type1pair.d1_delay);\
  GHTONS(type1pair.d1_offset); PutDown(s, type1pair.d1_offset);


#define	WINDOW_INTERVAL		6	/* in minutes */
#define HELLO_INTERVAL		15	/* HELLO rate coming in, in secs */
#define HWINSIZE		(WINDOW_INTERVAL * (60 / HELLO_INTERVAL))
#define HELLO_REPORT	8		/* how far back we will report */

struct hello_win {
    metric_t h_win[HWINSIZE];
    int h_index;
    metric_t h_min;
    int h_min_ttl;
};

extern flag_t hello_flags;		/* Options */
extern trace *hello_trace_options;	/* Trace flags from parser */
extern metric_t hello_default_metric;	/* Default metric to use when propogating */
extern pref_t hello_preference;		/* Preference for HELLO routes */
extern int hello_n_trusted;		/* Number of trusted gateways */
extern int hello_n_source;		/* Number of gateways to receive explicit HELLO packets */
extern gw_entry *hello_gw_list;		/* List of defined and learned HELLO gateways */
extern adv_entry *hello_import_list;
extern adv_entry *hello_export_list;
extern adv_entry *hello_int_policy;	/* List of interface policy */
extern const bits hello_trace_types[];	/* HELLO specific trace flags */

/* Values for hello_flags */
#define	HELLOF_ON		BIT(0x01)		/* HELLO is enabled */
#define	HELLOF_BROADCAST	BIT(0x02)		/* Broadcast to all interfaces */
#define	HELLOF_SOURCE		BIT(0x04)		/* Source packets to our peers */
#define	HELLOF_CHOOSE		BIT(0x08)		/* Broadcast if more than one interface */
#define	HELLOF_FLASHDUE		BIT(0x10)		/* A Flash update is due when flash time expires */
#define	HELLOF_NOFLASH		BIT(0x20)		/* No flash update until normal update */
#define	HELLOF_RECONFIG		BIT(0x40)		/* In the process of reconfiguration */

/* Tracing */
#define	TR_HELLO_INDEX_PACKETS	0	/* All packets */

#define	TR_HELLO_DETAIL		TR_DETAIL_1

#define	HELLO_TARGET_VALID(tlp)	((BIT_TEST(hello_flags, HELLOF_SOURCE) && BIT_TEST(tlp->flag, TARGETF_SOURCE)) || \
				 (BIT_TEST(hello_flags, HELLOF_BROADCAST) && BIT_TEST(tlp->flag, TARGETF_BROADCAST)))

PROTOTYPE(hello_init, extern void, (void));
PROTOTYPE(hello_var_init, extern void, (void));

#endif	/* PROTO_HELLO */


/*
 * %(Copyright)
 */
