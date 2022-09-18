/*
 *  $Id: hello.c,v 1.68.2.16 1995/05/25 01:48:35 jch Exp $
 */

/* %(Copyright.header) */


/*
 *	Hello output routines were taken from Mike Petry (petry@trantor.umd.edu)
 *	Also, hello input routines were written by Bill Nesheim, Cornell
 *	CS Dept,  Currently at nesheim@think.com
 */

#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "targets.h"
#include "hello.h"

flag_t hello_flags;			/* Options */
trace *hello_trace_options;		/* Trace flags from parser */
metric_t hello_default_metric = HELLO_UNREACHABLE;	/* Default metric to use when propogating */
pref_t hello_preference = RTPREF_HELLO;	/* Preference for HELLO routes */

static task_timer *hello_timer_update;		/* To send updates */
static task_timer *hello_timer_flash;		/* To send flash updates */
static task_timer *hello_timer_age;		/* To age routes */

static task_job *hello_target_list_job;		/* To rebuild target list after interface changes */
static target hello_targets = { &hello_targets, &hello_targets };	/* Target list */

static block_t hello_win_block_index;	/* Allocation index for hello window */

int hello_n_trusted;			/* Number of trusted gateways */
int hello_n_source;			/* Number of source gateways */
gw_entry *hello_gw_list;		/* List of HELLO gateways */
adv_entry *hello_import_list;		/* List of nets to import from HELLO */
adv_entry *hello_export_list;		/* LIst of sources to exports routes to HELLO */
adv_entry *hello_int_policy;		/* List of interface policy */


static const bits hello_flag_bits[] = {
{ HELLOF_ON,		"ON" },
{ HELLOF_BROADCAST,	"Broadcast" },
{ HELLOF_SOURCE,	"Source" },
{ HELLOF_CHOOSE,	"Choose" },
{ HELLOF_FLASHDUE,	"FlashDue" },
{ HELLOF_NOFLASH,	"NoFlash" },    
{ HELLOF_RECONFIG,	"ReConfig" },
{ 0 }
} ;

static const flag_t hello_trace_masks[1] = {
	TR_HELLO_DETAIL
} ;

const bits hello_trace_types[] = {
    { TR_DETAIL,		"detail packets" },
    { TR_DETAIL_SEND,	"detail send packets" },
    { TR_DETAIL_RECV,	"detail recv packets" },
    { TR_PACKET,		"packets" },
    { TR_PACKET_SEND,	"send packets" },
    { TR_PACKET_RECV,	"recv packets" },
    { TR_DETAIL_1,	"detail packets" },
    { TR_DETAIL_SEND_1,	"detail send packets" },
    { TR_DETAIL_RECV_1,	"detail recv packets" },
    { TR_PACKET_1,	"packets" },
    { TR_PACKET_SEND_1,	"send packets" },
    { TR_PACKET_RECV_1,	"recv packets" },
    { 0, NULL }
};

metric_t hop_to_hello[] =
{					/* Translate interface metric to hello metric */
    0,					/* 0 */
    100,				/* 1 */
    148,				/* 2 */
    219,				/* 3 */
    325,				/* 4 */
    481,				/* 5 */
    713,				/* 6 */
    1057,				/* 7 */
    1567,				/* 8 */
    2322,				/* 9 */
    3440,				/* 10 */
    5097,				/* 11 */
    7552,				/* 12 */
    11190,				/* 13 */
    16579,				/* 14 */
    24564,				/* 15 */
    30000				/* 16 */
};


/* Routines for support of the hello window system */

/*
 * initialize the sliding HELLO history window.
 */
static void
hello_win_init __PF2(vp, void_t,
		     tdelay, metric_t)
{
    struct hello_win *hwp = (struct hello_win *) vp;
    int msf = 0;

    while (msf < HWINSIZE) {
	hwp->h_win[msf++] = HELLO_UNREACHABLE;
    }
    hwp->h_index = 0;
    hwp->h_min = tdelay;
    hwp->h_min_ttl = 0;
    hwp->h_win[0] = tdelay;
}


/*
 * add a HELLO derived time delay to the route entries HELLO window.
 */
static void
hello_win_add __PF2(vp, void_t,
		    tdelay, metric_t)
{
    struct hello_win *hwp = (struct hello_win *) vp;
    int msf, t_index = 0;

    hwp->h_index++;
    if (hwp->h_index >= HWINSIZE) {
	hwp->h_index = 0;
    }
    hwp->h_win[hwp->h_index] = tdelay;
    if (tdelay > hwp->h_min) {
	hwp->h_min_ttl++;
    } else {
	hwp->h_min = tdelay;
	hwp->h_min_ttl = 0;
    }
    if (hwp->h_min_ttl >= HWINSIZE) {
	hwp->h_min = HELLO_UNREACHABLE;
	for (msf = 0; msf < HWINSIZE; msf++) {
	    if (hwp->h_win[msf] <= hwp->h_min) {
		hwp->h_min = hwp->h_win[msf];
		t_index = msf;
	    }
	}
	hwp->h_min_ttl = 0;
	if (t_index < hwp->h_index) {
	    hwp->h_min_ttl = hwp->h_index - t_index;
	} else if (t_index > hwp->h_index) {
	    hwp->h_min_ttl = HWINSIZE - (t_index - hwp->h_index);
	}
    }
}


/*
 *	Dump info about a HELLO route
 */
static void
hello_rt_dump __PF2(fd, FILE *,
		    rt, rt_entry *)
{
    int cnt, ind;
    struct hello_win *hwp = (struct hello_win *) rt->rt_data;

    (void) fprintf(fd, "\t\t\tMinimum HELLO time delay in last %d updates: %d\n",
		   HWINSIZE,
		   hwp->h_min);
    (void) fprintf(fd, "\t\t\tLast %d HELLO time delays:\n\t\t",
		   HELLO_REPORT);
    ind = hwp->h_index;
    for (cnt = HELLO_REPORT; cnt; cnt--) {
	(void) fprintf(fd, "%d ",
		       hwp->h_win[ind]);
	if (++ind >= HWINSIZE) {
	    ind = 0;
	}
    }
    (void) fprintf(fd, "\n");
}


/*
 *	Dump protocol specific info
 */
static void
hello_rt_free __PF2(rt, rt_entry *,
		    rtd, void_t)
{
    task_block_free(hello_win_block_index, rtd);
}


/*
 *	Trace a HELLO packet
 */
/*ARGSUSED*/
static void
hello_trace __PF8(tp, task *,
		  comment, const char *,
		  src, sockaddr_un *,
		  dst, sockaddr_un *,
		  packet, void_t,
		  length, size_t,
		  nets, int,
		  detail, int)
{
    u_int i;
    const char *cp;
    byte *hello = (byte *) packet;
    byte *end = hello + length;
    struct hm_hdr hm_hdr;
    struct hellohdr hellohdr;
    struct type0pair type0pair;
    struct type1pair type1pair;

    tracef("HELLO %s %A -> %A  %d bytes",
	   comment,
	   src,
	   dst,
	   length);
    if (nets >= 0) {
	tracef("  %d nets",
	       nets);
    }

    /* Calculate the checksum of this packet */
    if (inet_cksum(packet, length)) {
	tracef(" *checksum bad*");
    }	
    trace_only_tp(tp,
		  0,
		  (NULL));

    PickUp_hellohdr(hello, hellohdr);

    if (detail) {
	switch (hellohdr.h_date & H_DATE_BITS) {
	    case H_DATE_LEAPADD:
		cp = "add_leap_second ";
		break;
	    case H_DATE_LEAPDEL:
		cp = "del_leap_second ";
		break;
	    case H_DATE_UNSYNC:
		cp = "unsync ";
		break;
	    default:
		cp = "";
	}
	BIT_RESET(hellohdr.h_date, H_DATE_BITS);
	trace_only_tp(tp,
		      TRC_NOSTAMP,
		      ("HELLO %s %s%d/%d/%d %02d:%02d:%02d.%03d GMT  tstp %d",
		       comment,
		       cp,
		       (hellohdr.h_date >> H_DATE_MON_SHIFT) & H_DATE_MON_MASK,
		       (hellohdr.h_date >> H_DATE_DAY_SHIFT) & H_DATE_DAY_MASK,
		       ((hellohdr.h_date >> H_DATE_YEAR_SHIFT) & H_DATE_YEAR_MASK) + H_DATE_YEAR_BASE,
		       hellohdr.h_time / (60 * 60 * 1000),
		       (hellohdr.h_time / (60 * 1000)) % 60,
		       (hellohdr.h_time / (1000)) % 60,
		       hellohdr.h_time % 1000,
		       hellohdr.h_tstp));

	while (hello < end) {
	    PickUp_hm_hdr(hello, hm_hdr);
	    trace_only_tp(tp,
			  TRC_NOSTAMP,
			  ("%s\ttype %d  count %d",
			   comment,
			   hm_hdr.hm_type,
			   hm_hdr.hm_count));
	    for (i = 0; i < hm_hdr.hm_count; i++) {
		switch (hm_hdr.hm_type) {
		    case 0:
			PickUp_type0pair(hello, type0pair);
			trace_only_tp(tp,
				      TRC_NOSTAMP,
				      ("%s\t\tdelay %d  offset %d",
				       comment,
				       type0pair.d0_delay,
				       type0pair.d0_offset));
			break;
		    case 1:
			PickUp_type1pair(hello, type1pair);
			trace_only_tp(tp,
				      TRC_NOSTAMP,
				      ("%s\t\t%-15A  delay %5d  offset %d",
				       comment,
				       sockbuild_in(0, type1pair.d1_dst),
				       type1pair.d1_delay,
				       type1pair.d1_offset));
			break;
		    default:
			trace_only_tp(tp,
				      TRC_NOSTAMP,
				      ("%s\t\tInvalid type - giving up!",
				       comment));
			return;
		}
	    }
	}
	trace_only_tp(tp,
		      0,
		      (NULL));
    }
}


/*
 * hello_send():
 * 	Fill in the hello header and checksum, then send the packet.
 */
static void
hello_send __PF4(tlp, target *,
		 packet, byte *,
		 fillp, byte *,
		 maxsize, size_t *)
{
    byte *hello;
    struct hellohdr hellohdr;
    struct hm_hdr hm_hdr;
    utime_t hello_time;
    struct tm *gmt;
    int error = FALSE;
    size_t length = fillp - packet;

    /*
     * All packets in an update must be the same size, padding should be used
     * if necessary to insure this.  This is for timing that we don't do, but
     * lets be consistent.
     */
    if (length > *maxsize) {
	/* Remember the largest packet */
	*maxsize = length;
    } else {
	/* Pad this packet out to the size of the largest sent */
	bzero ((caddr_t) fillp, *maxsize - length);
	length = *maxsize;
    }

    TIMER_PEEK();
    hello_time.ut_sec = utime_current.ut_sec + utime_boot.ut_sec;
    hello_time.ut_usec = utime_current.ut_usec + utime_boot.ut_usec;
    if (hello_time.ut_usec >= 1000000) {
	hello_time.ut_usec -= 1000000;
	hello_time.ut_sec += 1;
    }
    gmt = (struct tm *) gmtime(&hello_time.ut_sec);

    /*
     * set the date field in the HELLO header.  Be very careful here as
     * the last two bits (14&15) should be set so the Fuzzware doesn't use
     * this packet to synchronize its Master Clock.  Using bitwise OR's
     * instead of addition just to be safe when dealing with h_date which
     * is an unsigned short.
     */
    hellohdr.h_date = ((gmt->tm_year - H_DATE_YEAR_BASE) & H_DATE_YEAR_MASK) |
	((gmt->tm_mday & H_DATE_DAY_MASK) << H_DATE_DAY_SHIFT) |
	    (((gmt->tm_mon + 1) & H_DATE_MON_MASK) << H_DATE_MON_SHIFT) |
		H_DATE_UNSYNC;
    /*
     * milliseconds since midnight UT of current day
     */
#define	MULBY60(X)	(((X) << 6) - ((X) << 2))
#define	MULBY1000(X)	(((X) << 10) - ((X) << 4) - ((X) << 3))
    hello_time.ut_sec = (time_t) (MULBY60(gmt->tm_hour) + gmt->tm_min);
    hello_time.ut_sec = MULBY60(hello_time.ut_sec) + (time_t) gmt->tm_sec;
    hellohdr.h_time = MULBY1000(hello_time.ut_sec) + hello_time.ut_usec / 1000;
#undef	MULBY1000
#undef	MULBY60

    /*
     * 16 bit field used in rt calculation,  0 for ethernets
     */
    hellohdr.h_tstp = 0;
    hellohdr.h_cksum = 0;
    hello = packet;
    PutDown_hellohdr(hello, hellohdr);

    /* Build the hm header */
    hm_hdr.hm_type = 1;
    hm_hdr.hm_count = (length - Size_hellohdr - Size_hm_hdr) / Size_type1pair;

    /* Check for packet size skew */
    assert((hm_hdr.hm_count * Size_type1pair) == (length - Size_hellohdr - Size_hm_hdr));

    PutDown_hm_hdr(hello, hm_hdr);

    /* Calculate the checksum and put it into the packet */
    hellohdr.h_cksum = inet_cksum((void_t) packet, length);
    hello = packet;
    PutDown(hello, hellohdr.h_cksum);

    if (task_send_packet(tlp->target_task,
			 (void_t) packet,
			 length,
			 0,
			 *tlp->target_dst) < 0) {
	error = TRUE;
    }

    if (TRACE_PACKET_SEND_TP(tlp->target_task,
			     0,
			     0,
			     hello_trace_masks)) {
	hello_trace(tlp->target_task,
		    error ? "*NOT* SENT" : "SENT",
		    *tlp->target_src,
		    *tlp->target_dst,
		    packet,
		    length,
		    (int) hm_hdr.hm_count,
		    TRACE_DETAIL_SEND_TP(tlp->target_task,
					 0,
					 0,
					 hello_trace_masks));
    }
    return;
}


/*
 *	Process an incomming HELLO packet
 */
static void
hello_recv __PF1(tp, task *)
{
    int n_packets = TASK_PACKET_LIMIT;
    size_t count;

    while (n_packets-- && !task_receive_packet(tp, &count)) {
	u_int i;
	struct ip *ip;
	register byte *hello;
	byte *end;
	size_t hello_len;
	struct hm_hdr hm_hdr;
	if_addr *ifap;
	rt_parms rtparms;

	task_parse_ip(ip, hello, byte *);

	hello_len = ip->ip_len;
	end = hello + hello_len;

	if (TRACE_PACKET_RECV_TP(tp,
				 0,
				 0,
				 hello_trace_masks)) {
	    hello_trace(tp,
			"RECV",
			task_recv_srcaddr,
			sockbuild_in(0, ip->ip_dst.s_addr),
			(void_t) hello,
			hello_len,
			-1,
			TRACE_DETAIL_RECV_TP(tp,
					     0,
					     0,
					     hello_trace_masks));
	}

	bzero((caddr_t) &rtparms, sizeof (rtparms));
	rtparms.rtp_n_gw = 1;
	rtparms.rtp_router = task_recv_srcaddr;
	rtparms.rtp_gwp = gw_timestamp(&hello_gw_list,
				       tp->task_rtproto,
				       tp,
				       (as_t) 0,
				       (as_t) 0,
				       rtparms.rtp_router,
				       GWF_NEEDHOLD);
	rtparms.rtp_gwp->gw_rtd_dump = hello_rt_dump;
	rtparms.rtp_gwp->gw_rtd_free = hello_rt_free;

	rtparms.rtp_state = (flag_t) 0;

	/* If we have a list of trusted gateways, verify that this gateway is trusted */
	if (hello_n_trusted && !BIT_TEST(rtparms.rtp_gwp->gw_flags, GWF_TRUSTED)) {
	    BIT_SET(rtparms.rtp_gwp->gw_flags, GWF_REJECT);
	    continue;
	}

	/* Do we share a net with the sender? */
	if (!(ifap = if_withdst(rtparms.rtp_router))) {
	    trace_log_tp(tp,
			 0,
			 LOG_WARNING,
			 ("hello_recv: gw %A no shared net?",
			  rtparms.rtp_router));
	    BIT_SET(rtparms.rtp_gwp->gw_flags, GWF_REJECT);
	    continue;
	}

	if (sockaddrcmp_in(rtparms.rtp_router, ifap->ifa_addr_local)) {
	    /* A packet from us */

	    if (!BIT_TEST(ifap->ifa_state, IFS_SIMPLEX)) {
		/* If this interface is not simplex, indicate that the media */
		/* is functioning */
		if_rtupdate(ifap);
	    }

	    /* Ignore the packet */
	    continue;
	}

	/* update the interface timer on interface the packet came in on. */
	if_rtupdate(ifap);

	/* Ignore this packet */
	if (BIT_TEST(ifap->ifa_ps[tp->task_rtproto].ips_state, IFPS_NOIN)) {
	    continue;
	}

	/* check the hello checksum */
	if (inet_cksum((void_t) hello, hello_len)) {
	    trace_log_tp(tp,
			 0,
			 LOG_WARNING,
			 ("hello_recv: bad HELLO checksum from %A",
			  rtparms.rtp_router));
	    BIT_SET(rtparms.rtp_gwp->gw_flags, GWF_CHECKSUM);
	    continue;
	}

	rt_open(tp);

	/* message is made up of one or more sub messages */
	hello += Size_hellohdr;
	while (hello < end) {
	    PickUp_hm_hdr(hello, hm_hdr);
	    switch (hm_hdr.hm_type) {
	    case 0:
		hello += Size_type0pair * hm_hdr.hm_count;
		/* not interested in type 0 messages */
		break;

	    case 1:
		for (i = 0; i < hm_hdr.hm_count; i++) {
		    register rt_entry *rt;
		    struct type1pair type1pair;

		    PickUp_type1pair(hello, type1pair);
		    rtparms.rtp_dest = sockbuild_in(0, type1pair.d1_dst);
		    if (!inet_class_valid(rtparms.rtp_dest)) {
			continue;
		    }

		    rtparms.rtp_preference = hello_preference;
		    rtparms.rtp_metric = type1pair.d1_delay;
		
		    /* Force delay to be valid */
		    if (rtparms.rtp_metric > HELLO_UNREACHABLE) {
			rtparms.rtp_metric = HELLO_UNREACHABLE;
		    }
		    /*
		     *	Add the interface metric converted to a HELLO delay.
		     */
		    rtparms.rtp_metric += ifap->ifa_ps[tp->task_rtproto].ips_metric_in;

		    rtparms.rtp_state = RTS_INTERIOR;
		    
		    rtparms.rtp_dest_mask = inet_mask_withif(rtparms.rtp_dest, ifap, &rtparms.rtp_state);
		    if (!rtparms.rtp_dest_mask) {
			/* Ignore zero subnet */

			continue;
		    }

		    if (if_myaddr(ifap, rtparms.rtp_dest, rtparms.rtp_dest_mask)) {
			/* Ignore route to interface or whole network */
			continue;
		    }

		    rt = rt_locate(rtparms.rtp_state,
				   rtparms.rtp_dest,
				   rtparms.rtp_dest_mask,
				   RTPROTO_BIT(tp->task_rtproto));
		    if (!rt) {
			rt_head *rth;
	    
			/* No route installed.  See if we are announcing another route */
			rt = rt_locate(RTS_NETROUTE,
				       rtparms.rtp_dest,
				       rtparms.rtp_dest_mask,
				       RTPROTO_BIT_ANY);
			if (rt &&
			    (rth = rt->rt_head) &&
			    rth->rth_n_announce &&
			    (rt == rth->rth_active || rt == rth->rth_holddown)) {
			    /* We are announcing this route */
			    register target *tlp;

			    /* HELLO won't announce an active route if one in holddown */
			    /* so check the holddown route first */
			    rt = rth->rth_holddown;
			    if (!rt) {
				rt = rth->rth_active;
			    }

			    TARGET_LIST(tlp, &hello_targets) {
				if (BIT_TEST(tlp->target_flags, TARGETF_SUPPLY) &&
				    rtbit_isset(rt, tlp->target_rtbit)) {
				    /* We are sending to this target */
				    td_entry *tdp;

				    TD_TSI_GET(tlp, rth, tdp);

				    if (BIT_TEST(tdp->td_flags, TDF_HOLDDOWN|TDF_POISON) ||
					tdp->td_metric < rtparms.rtp_metric) {
					/* We are announcing this route from another protocol */

					break;
				    }
				}
			    } TARGET_LIST_END(tlp, &hello_targets) ;

			    if (tlp) {
				/* Announced via another protocol, ignore this route */
				continue;
			    }
			}
	    
			/* New route */
			if (rtparms.rtp_metric < HELLO_UNREACHABLE &&
			    import(rtparms.rtp_dest,
				   rtparms.rtp_dest_mask,
				   hello_import_list,
				   ifap->ifa_ps[tp->task_rtproto].ips_import,
				   rtparms.rtp_gwp->gw_import,
				   &rtparms.rtp_preference,
				   ifap,
				   (void_t) 0)) {
			    /* Allocate space for the hysterisis */
			    rtparms.rtp_rtd = task_block_alloc(hello_win_block_index);
			    
			    hello_win_init(rtparms.rtp_rtd, rtparms.rtp_metric);

			    /* Add new route */
			    rt = rt_add(&rtparms);
			    if (!rt) {
				task_block_free(hello_win_block_index, rtparms.rtp_rtd);
				rtparms.rtp_rtd = (void_t) 0;
			    }
			} else {
			    BIT_SET(rtparms.rtp_gwp->gw_flags, GWF_IMPORT);
			}
		    } else if (sockaddrcmp_in(RT_ROUTER(rt), rtparms.rtp_router)) {
			/* same route */

			if (rtparms.rtp_metric >= HELLO_UNREACHABLE) {
			    /* Now unreachable -  Delete route */
			    hello_win_add(rt->rt_data, HELLO_UNREACHABLE);
			    rt_delete(rt);
			} else if (METRIC_DIFF(rt->rt_metric, rtparms.rtp_metric) >= HELLO_HYST(rt->rt_metric)) {
			    /* Better metric */
			    if ((rt = rt_change(rt,
						rtparms.rtp_metric,
						rtparms.rtp_metric2,
						rtparms.rtp_tag,
						rt->rt_preference,
						rt->rt_preference2,
						rt->rt_n_gw, rt->rt_routers))) {
				hello_win_add(rt->rt_data, (metric_t) rtparms.rtp_metric);
				rt_refresh(rt);
			    }
			} else {
			    /* No change */
			    rt_refresh(rt);
			}
		    } else if (((rtparms.rtp_metric < rt->rt_metric
				 && METRIC_DIFF(rtparms.rtp_metric, rt->rt_metric) >= HELLO_HYST(rt->rt_metric))
				|| (rt_age(rt) > (HELLO_T_EXPIRE / 2)
				    && rt->rt_metric == rtparms.rtp_metric))
			       && import(rtparms.rtp_dest,
					 rtparms.rtp_dest_mask,
					 hello_import_list,
					 ifap->ifa_ps[tp->task_rtproto].ips_import,
					 rtparms.rtp_gwp->gw_import,
					 &rtparms.rtp_preference,
					 ifap,
					 (void_t) 0)) {
			/* Better metric or same metric and old route has */
			/* not been refreshed */

			hello_win_add(rt->rt_data, HELLO_UNREACHABLE);
			rt_delete(rt);

			/* Allocate space for the hysterisis */
			rtparms.rtp_rtd = task_block_alloc(hello_win_block_index);
			    
			hello_win_init(rtparms.rtp_rtd, rtparms.rtp_metric);

			/* Add new route */
			rt = rt_add(&rtparms);
			if (!rt) {
			    task_block_free(hello_win_block_index, rtparms.rtp_rtd);
			    rtparms.rtp_rtd = (void_t) 0;
			}
		    }
		}			/* for each advertized net */
		break;

	    default:
		trace_log_tp(tp,
			     0,
			     LOG_ERR,
			     ("hello_recv: invalid type %d",
			      hm_hdr.hm_type));
		BIT_SET(rtparms.rtp_gwp->gw_flags, GWF_FORMAT);
		/* Force end of packet */
		hello = end;
	    } /* switch (mh->hm_type) */
	} 	/* while not end of packet */

	rt_close(tp, rtparms.rtp_gwp, (int) hm_hdr.hm_count, NULL);
    }
}


/* Send HELLO updates to all targets on the list */
/*ARGSUSED*/
static void
hello_supply __PF2(tlp, target *,
		   flash_update, int)
{
    byte *packet = task_get_send_buffer(byte *);
    byte *start = packet + Size_hellohdr + Size_hm_hdr;
    byte *fillp = start;
    register td_entry *tdp;
    size_t maxsize = 0;
    int changes = 0;
	
    /* Open the routing table in case a holddown is over */
    rt_open(tlp->target_task);

    TD_LIST(tdp, &tlp->target_td) {
	int cleanup = 0;
	struct type1pair type1pair;

	if (flash_update) {
	    if (!BIT_TEST(tdp->td_flags, TDF_CHANGED)) {
		/* End of changes for this target */
		    
		break;
	    }
	} else {
	    if (BIT_TEST(tdp->td_flags, TDF_HOLDDOWN|TDF_POISON)
		&& !--tdp->td_metric) {
		/* Holddown is over - queue it to be released */

		cleanup++;
	    }
	}

	if (BIT_TEST(tdp->td_flags, TDF_CHANGED)) {
	    BIT_RESET(tdp->td_flags, TDF_CHANGED);
	}
	
	if (fillp > Size_type1pair + packet + tlp->target_ifap->ifa_mtu) {
	    hello_send(tlp,
		       packet,
		       fillp,
		       &maxsize);
	    fillp = start;
	}

	/* Put this entry in the packet */
	type1pair.d1_delay = BIT_TEST(tdp->td_flags, TDF_HOLDDOWN|TDF_POISON) ? HELLO_UNREACHABLE : tdp->td_metric;
	type1pair.d1_offset = 0;	/* should be signed clock offset */
	type1pair.d1_dst = sock2ip(tdp->td_rt->rt_dest);	/* struct copy */
	PutDown_type1pair(fillp, type1pair);

	if (cleanup) {
	    if (TRACE_TP(tlp->target_task, TR_POLICY)) {
		if (!changes) {
		    trace_only_tp(tlp->target_task,
				  TRC_NL_BEFORE,
				  ("hello_supply: Policy for target %A",
				   *tlp->target_dst));
		}
		trace_only_tp(tlp->target_task,
			      0,
			      ("\t%A/%A %s ended",
			       tdp->td_rt->rt_dest,
			       tdp->td_rt->rt_dest_mask,
			       BIT_TEST(tdp->td_flags, TDF_POISON) ? "poison" : "holddown"));
	    }
	    changes++;
	    TD_CLEANUP(tlp, tdp, TRUE);
	}
    } TD_LIST_END(tdp, &tlp->target_td) ;

    /* Send any packets with data remaining in them */
    if (fillp > start) {
	hello_send(tlp,
		   packet,
		   fillp,
		   &maxsize);
	fillp = start;
    }

    if (TRACE_TP(tlp->target_task, TR_POLICY)
	|| changes) {
	trace_only_tp(tlp->target_task,
		      0,
		      (NULL));
    }
    
    rt_close(tlp->target_task, (gw_entry *) 0, 0, NULL);
}


/*
 *	send HELLO packets
 */
/*ARGSUSED*/
static void
hello_job __PF2(tip, task_timer *,
		interval, time_t)
{
    target *tlp;
    
    TARGET_LIST(tlp, &hello_targets) {
	if (BIT_TEST(tlp->target_flags, TARGETF_SUPPLY)) {
	    hello_supply(tlp, FALSE);
	}
    } TARGET_LIST_END(tlp, &hello_targets);

    /* Indicate that flash updates are possible as soon as the timer fires */
    task_timer_set(hello_timer_flash, HELLO_T_FLASH, (time_t) 0);
    BIT_RESET(hello_flags, HELLOF_NOFLASH|HELLOF_FLASHDUE);
}


/*
 *	send a flash update packet
 */
/*ARGSUSED*/
static void
hello_do_flash __PF2(tip, task_timer *,
		     interval, time_t)
{
    task *tp = tip->task_timer_task;
    
    if (BIT_TEST(hello_flags, HELLOF_FLASHDUE)) {
	target *tlp;

	/* Do a flash update */

	trace_tp(tp,
		 TR_TASK,
		 0,
		 ("hello_do_flash: Doing flash update for HELLO"));

	TARGET_LIST(tlp, &hello_targets) {
	    if (BIT_TEST(tlp->target_flags, TARGETF_SUPPLY)) {
		hello_supply(tlp, TRUE);
	    }
	} TARGET_LIST_END(tlp, &hello_targets);

	trace_tp(tp,
		 TR_TASK,
		 0,
		 ("hello_do_flash: Flash update done"));

	/* Indicate no flash update is due */
	BIT_RESET(hello_flags, HELLOF_FLASHDUE);

	/* Schedule the next flash update */
	if (time_sec + HELLO_T_MIN + HELLO_T_MAX < hello_timer_update->task_timer_next_time) {
	    /* We can squeeze another flash update in before the full update */

	    task_timer_set(tip, HELLO_T_FLASH, (time_t) 0);
	} else {
	    /* The next flash update will be scheduled after the full update */

	    task_timer_reset(tip);
	    BIT_SET(hello_flags, HELLOF_NOFLASH);
	}
    } else {
	/* The next flash update can happen immediately */

	task_timer_reset(tip);
    }
}


/*
 *	Schedule or do a flash update
 */
static void
hello_need_flash __PF1(tp, task *)
{
    task_timer *tip = hello_timer_flash;

    if (!tip) {
	BIT_RESET(hello_flags, HELLOF_FLASHDUE);
	return;
    }

    /* Indicate we need a flash update */
    BIT_SET(hello_flags, HELLOF_FLASHDUE);

    /* And see if we can do it now */
    if (!tip->task_timer_next_time
	&& !BIT_TEST(hello_flags, HELLOF_NOFLASH)) {
	/* Do it now */

	hello_do_flash(tip, (time_t) 0);
    }
}


/*
 *	Evaluate policy for changed routes.
 */
static int
hello_policy __PF3(tp, task *,
		   tlp, target *,
		   change_list, rt_list *)
{
    if_addr *ifap = tlp->target_ifap;
    u_long if_net = inet_net_natural(ifap->ifa_addr);
    int same_net = if_net == inet_net_natural(ifap->ifa_addr_local);
    int changes = 0;
    int logged = 0;
    rt_head *rth;

    RT_LIST(rth, change_list, rt_head) {
	register rt_entry *new_rt = rth->rth_active;
	adv_results result;
	td_entry *tdp;
	int exportable = FALSE;
	int changed = 0;
	int move_bit = 0;
	int holddown = 0;
	int poison = 0;
	int set_metric = 0;

	TD_TSI_GET(tlp, rth, tdp);

	/* See if there is a new route and if it can be announced */
	if ((new_rt = rth->rth_active)) {
	    
	    if (socktype(new_rt->rt_dest) != AF_INET) {
		goto no_export;
	    }
	    
	    if (BIT_TEST(new_rt->rt_state, RTS_NOADVISE|RTS_PENDING|RTS_GROUP)) {
		/* Absolutely not */
		goto no_export;
	    }

	    if (RT_IFAP(new_rt) == ifap &&
		new_rt->rt_gwp->gw_proto == RTPROTO_DIRECT) {
		/* Do not send interface routes back to the same interface */
		goto no_export;
	    }

	    /* Host routes go everywhere, subnets and nets may need to be restricted */
	    if (new_rt->rt_dest_mask != inet_mask_host) {
		sockaddr_un *natural_mask = inet_mask_natural(new_rt->rt_dest);

		if (new_rt->rt_dest_mask > natural_mask) {
		    /* This is a subnet */

		    if (!same_net
			|| (sock2ip(rth->rth_dest) & sock2ip(natural_mask)) != if_net) {
			/* Only send subnets to interfaces of the same network */

			goto no_export;
		    }
		    if (rth->rth_dest_mask != ifap->ifa_netmask) {
			/* Only send subnets that have the same mask */

			goto no_export;
		    }
		} else if (sock2ip(rth->rth_dest) == if_net) {
		    /* Do not send the whole net to a subnet */

		    goto no_export;
		}
	    }

	    if ((new_rt->rt_gwp->gw_proto == tp->task_rtproto) && (ifap == RT_IFAP(new_rt))) {
		/* Split horizon */
		goto no_export;
	    }

	    if (RT_IFAP(new_rt)
		&& !BIT_TEST(RT_IFAP(new_rt)->ifa_state, IFS_UP)) {
		/* The interface is down */
		goto no_export;
	    }

	    /* Assign default metric */
	    if (new_rt->rt_gwp->gw_proto == RTPROTO_AGGREGATE) {
		/* Originate aggregates a metric of one */

		result.res_metric = HELLO_HOP;
	    } else if (!RT_IFAP(new_rt)
		|| BIT_TEST(RT_IFAP(new_rt)->ifa_state, IFS_LOOPBACK)) {
		/* Routes via the loopback interface must have an explicit metric */ 

		result.res_metric = HELLO_UNREACHABLE;
	    } else if (new_rt->rt_gwp->gw_proto == RTPROTO_DIRECT) {
		/* Interface routes */

		if (BIT_TEST(RT_IFAP(new_rt)->ifa_state, IFS_POINTOPOINT)) {
		    /* Add a hop for the P2P link */

		    result.res_metric = HELLO_HOP * 2;
		} else {
		    /* Default to one hop */

		    result.res_metric = HELLO_HOP;
		}
	    } else {
		/* Use configured default metric */

		result.res_metric = hello_default_metric;
	    }

		
	    if (!export(new_rt,
			tp->task_rtproto,
			hello_export_list,
			ifap->ifa_ps[tp->task_rtproto].ips_export,
			tlp->target_gwp ? tlp->target_gwp->gw_export : (adv_entry *) 0,
			&result)) {
		/* Policy prohibits announcement */

		goto no_export;
	    } else {
		/* Add the interface metric */

		result.res_metric += ifap->ifa_ps[tp->task_rtproto].ips_metric_out;
	    }

	    if (result.res_metric < HELLO_UNREACHABLE) {
		exportable = TRUE;
	    }
	    
	no_export: ;
	}

	/* Now that we have determined the exportablility of the new */
	/* route we decide what changed need to be made.  The */
	/* complexity is required to surpress routing loops both */
	/* within HELLO and between HELLO and other protocols. */

	/* There are two types of holddowns used, the first one is */
	/* called HOLDDOWN and is used when a route goes away or is */
	/* overridden by a route that is not suspected to be an echo */
	/* of a route we are announcing.  The second is called POISON */
	/* and is used when a route is overridden by a route suspected */
	/* to be an echo of a route we are announcing. */

	if (!tdp) {
	    /* New route */

	    if (exportable) {
		/* and it is exportable */
		
		/* Allocate new entry and fill it in */
		TD_ALLOC(tdp);
		TD_TSI_SET(tlp, rth, tdp);
		tdp->td_rt = new_rt;
		rtbit_set(tdp->td_rt, tlp->target_rtbit);
		TD_ENQUE(tlp, tdp);
		set_metric++;
		changes++;
	    }
	} else if (!new_rt) {
	    /* No new route, just an old one */
	
	    if (!BIT_TEST(tdp->td_flags, TDF_POISON|TDF_HOLDDOWN)) {
		if (BIT_TEST(tdp->td_rt->rt_state, RTS_DELETE|RTS_HIDDEN)) {
		    /* Put into holddown */

		    holddown++;
		    changed++;
		} else {
		    /* Poison the old route */

		    poison++;
		    changed++;
		}
	    }
	} else if (new_rt == tdp->td_rt) {
	    /* Something has changed with the route we are announcing */

	    if (BIT_TEST(tdp->td_flags, TDF_POISON|TDF_HOLDDOWN)) {
		if (exportable) {
		    set_metric++;
		    changed++;
		}
	    } else {
		if (!exportable) {
		    poison++;
		    changed++;
		} else if (tdp->td_metric != result.res_metric) {
		    set_metric++;
		    changed++;
		}
	    }
	} else if (!BIT_TEST(new_rt->rt_state, RTS_PENDING)) {
	    /* The new route is not from a holddown protocol */
	    
	    if (exportable
		&& (BIT_TEST(new_rt->rt_gwp->gw_flags, GWF_NOHOLD)
		    || BIT_TEST(tdp->td_rt->rt_gwp->gw_flags, GWF_NOHOLD))) {
		    /* The new route is a ``static'' route or the old route */
		    /* is a ``static'' route, override immediately */
		    
		set_metric++;
		changed++;
		move_bit++;
	    } else if (BIT_TEST(tdp->td_flags, TDF_HOLDDOWN)
		&& !BIT_TEST(tdp->td_rt->rt_gwp->gw_flags, GWF_NEEDHOLD)
		&& !BIT_TEST(new_rt->rt_gwp->gw_flags, GWF_NEEDHOLD)) {
		/* No changes necessary */

		changed = move_bit = 0;
	    } else if (!BIT_TEST(tdp->td_flags, TDF_POISON|TDF_HOLDDOWN)) {
		/* Previously active, has been deleted */

		holddown++;
		changed++;
	    } else {
		if (exportable) {
		    set_metric++;
		    changed++;
		} else {
		    if (!BIT_TEST(tdp->td_flags, TDF_POISON)) {
			poison++;
			changed++;
		    }
		}
		move_bit++;
	    }
	} else {
	    /* New route is just better */

	    if (BIT_TEST(tdp->td_rt->rt_state, RTS_DELETE|RTS_HIDDEN)) {
		if (!BIT_TEST(tdp->td_flags, TDF_HOLDDOWN)) {
		    holddown++;
		    changed++;
		}
	    } else {
		if (!BIT_TEST(tdp->td_flags, TDF_POISON)) {
		    poison++;
		    changed++;
		}

		move_bit++;
	    }
	}

	if ((changed || set_metric)
	    && TRACE_TP(tp, TR_POLICY)) {
	    if (!logged) {
		logged++;
		trace_only_tp(tp,
			      TRC_NL_BEFORE,
			      ("hello_policy: Policy for target %A",
			       *tlp->target_dst));
	    }
	    tracef("\t%A/%A ",
		   rth->rth_dest,
		   rth->rth_dest_mask);
	}
	if (set_metric) {
	    target_set_metric(tdp, result.res_metric);
	    trace_tp(tp,
		     TR_POLICY,
		     0,
		     ("metric %u",
		      tdp->td_metric));
	} else if (holddown) {
	    target_set_holddown(tdp, HELLO_HOLDCOUNT);
	    trace_tp(tp,
		     TR_POLICY,
		     0,
		     ("starting holddown"));
	} else if (poison) {
	    target_set_poison(tdp, HELLO_HOLDCOUNT);
	    trace_tp(tp,
		     TR_POLICY,
		     0,
		     ("starting poison"));
	} else if (TRACE_TP(tp, TR_POLICY)) {
	    trace_clear();
	}
	
	if (changed) {
	    /* Changed entries need to be at the head of the queue to */
	    /* make triggered updates quick */

	    TD_DEQUE(tdp);
	    TD_ENQUE(tlp, tdp);
	    changes++;
	}

	if (move_bit) {
	    /* Move lock to new route */

	    rtbit_set(new_rt, tlp->target_rtbit);
	    (void) rtbit_reset(tdp->td_rt, tlp->target_rtbit);
	    tdp->td_rt = new_rt;
	}
    } RT_LIST_END(rth, change_list, rt_head) ;

    return changes;
}


/*
 *	Process changes in the routing table.
 */
static void
hello_flash __PF2(tp, task *,
		  change_list, rt_list *)
{
    int changes = 0;
    target *tlp;

    rt_open(tp);
    
    /* Re-evaluate policy */
    TARGET_LIST(tlp, &hello_targets) {
	if (BIT_TEST(tlp->target_flags, TARGETF_SUPPLY)) {
	    changes += hello_policy(tp, tlp, change_list);
	}
    } TARGET_LIST_END(tlp, &hello_targets) ;
    
    /* Close the table */
    rt_close(tp, (gw_entry *)0, 0, NULL);

    if (changes) {
	/* Schedule a flash update */

	hello_need_flash(tp);
    }
}


/*
 *	Re-evaluate routing table
 */
static void
hello_newpolicy __PF2(tp, task *,
		    change_list, rt_list *)
{
    /* Indicate reconfig done */
    BIT_RESET(hello_flags, HELLOF_RECONFIG);

    /* And evaluate policy */
    hello_flash(tp, change_list);
}


/*
 *  Age out HELLO routes
 */
static void
hello_age __PF2(tip, task_timer *,
		interval, time_t)
{
    time_t expire_to = time_sec - HELLO_T_EXPIRE;
    time_t nexttime = time_sec + 1;

    if (expire_to > 0) {
	gw_entry *gwp;

	rt_open(tip->task_timer_task);
    
	GW_LIST(hello_gw_list, gwp) {
	    rt_entry *rt;

	    if (!gwp->gw_n_routes) {
		/* No routes for this gateway */

		if (!gwp->gw_import
		    && !gwp->gw_export
		    && !BIT_TEST(gwp->gw_flags, GWF_SOURCE|GWF_TRUSTED)) {
		    /* No routes, delete this gateway */

		    /* XXX */
		}
		continue;
	    }

	    /* Age any routes for this gateway */
	    RTQ_LIST(&gwp->gw_rtq, rt) {
		if (rt->rt_time <= expire_to) {
		    /* This route has expired */
		
		    rt_delete(rt);
		} else {
		    /* This is the next route to expire */
		    if (rt->rt_time < nexttime) {
			nexttime = rt->rt_time;
		    }
		    break;
		}
	    } RTQ_LIST_END(&gwp->gw_rtq, rt) ;
	} GW_LIST_END(hello_gw_list, gwp) ;

	rt_close(tip->task_timer_task, (gw_entry *) 0, 0, NULL);
    }

    if (nexttime > time_sec) {
	/* No routes to expire */

	nexttime = time_sec;
    }

    task_timer_set(tip, (time_t) 0, nexttime + HELLO_T_EXPIRE - time_sec);
}


/*
 *	Initialize static variables
 */
void
hello_var_init __PF0(void)
{
    hello_flags = HELLOF_CHOOSE;

    hello_default_metric = HELLO_UNREACHABLE;
    hello_preference = RTPREF_HELLO;
}


/*
 *	Cleanup before re-init
 */
/*ARGSUSED*/
static void
hello_cleanup __PF1(tp, task *)
{
    adv_cleanup(RTPROTO_HELLO,
		&hello_n_trusted,
		&hello_n_source,
		hello_gw_list,
		&hello_int_policy,
		&hello_import_list,
		&hello_export_list);

    if (tp) {
	trace_freeup(tp->task_trace);
    }
    trace_freeup(hello_trace_options);
}


static void
hello_tsi_dump __PF4(fp, FILE *,
		     rth, rt_head *,
		     data, void_t,
		     pfx, const char *)
{
    target *tlp = (target *) data;
    td_entry *tdp;

    TD_TSI_GET(tlp, rth, tdp);

    if (tdp) {
	if (BIT_TEST(tdp->td_flags, TDF_HOLDDOWN|TDF_POISON)) {
	    (void) fprintf(fp,
			   "%sHELLO %A <%s> remaining %#T\n",
			   pfx,
			   *tlp->target_dst,
			   trace_bits(target_entry_bits, tdp->td_flags),
			   tdp->td_metric * HELLO_T_UPDATE);
	} else {
	    (void) fprintf(fp,
			   "%sHELLO %A <%s> metric %u\n",
			   pfx,
			   *tlp->target_dst,
			   trace_bits(target_entry_bits, tdp->td_flags),
			   tdp->td_metric);
	}
    }
    
    return;
}


/*
 *	Update the target list
 */
static void
hello_target_list __PF1(jp, task_job *)
{
    register task *tp = jp->task_job_task;
    int targets;
    flag_t target_flags = 0;
    static int n_targets, n_source;

    /* If broadcast/nobroadcast not specified, figure out if we */
    /* need to broadcast packets */
    if (BIT_TEST(hello_flags, HELLOF_CHOOSE)) {
	if (if_n_addr[AF_INET].up > 1
	    && inet_ipforwarding) {

	    BIT_SET(hello_flags, HELLOF_BROADCAST);
	} else {

	    BIT_RESET(hello_flags, HELLOF_BROADCAST);
	}
    }

    if (!hello_timer_age) {
	/* Create route age timer */

	hello_timer_age = task_timer_create(tp,
					    "Age",
					    (flag_t) 0,
					    (time_t) 0,
					    HELLO_T_EXPIRE,
					    hello_age,
					    (void_t) 0);
    }

    if (BIT_TEST(hello_flags, HELLOF_SOURCE|HELLOF_BROADCAST)) {
	/* We are supplying updates */

	/* Gateways do not listen to redirects */
	redirect_disable(tp->task_rtproto);

	/* Make sure the timers are active */
	if (!hello_timer_update) {
	    /* Create the update timer */

	    hello_timer_update = task_timer_create(tp,
						   "Update",
						   0,
						   (time_t) HELLO_T_UPDATE,
						   (time_t) HELLO_T_MAX,
						   hello_job,
						   (void_t) 0);
	}

	if (!hello_timer_flash) {
	    /* Create flash update timer */

	    hello_timer_flash = task_timer_create(tp,
						  "Flash",
						  (flag_t) 0,
						  (time_t) HELLO_T_FLASH,
						  (time_t) HELLO_T_MAX,
						  hello_do_flash,
						  (void_t) 0);
	}
    } else {
	/* We are just listening */

	/* Hosts do listen to redirects */
	redirect_enable(tp->task_rtproto);

	/* Make sure the timers do not exist */
	if (hello_timer_update) {
	    task_timer_delete(hello_timer_update);
	    hello_timer_update = (task_timer *) 0;
	}

	if (hello_timer_flash) {
	    task_timer_delete(hello_timer_flash);
	    hello_timer_flash = (task_timer *) 0;
	}
    }


    /* Set flags for target list build */
    if (BIT_TEST(hello_flags, HELLOF_BROADCAST)) {
	BIT_SET(target_flags, TARGETF_BROADCAST);
    }
    if (BIT_TEST(hello_flags, HELLOF_SOURCE)) {
	BIT_SET(target_flags, TARGETF_SOURCE);
    }

    /* Build or update target list */
    targets = target_build(tp,
			   &hello_targets,
			   hello_gw_list,
			   target_flags,
			   hello_tsi_dump);

    /* Allocate the send and receive buffers */
    {
	mtu_t mtu_max = 0;
	target *tlp;
	
	TARGET_LIST(tlp, &hello_targets) {
	    if (tlp->target_ifap->ifa_mtu > mtu_max) {
		mtu_max = tlp->target_ifap->ifa_mtu;
	    }
	} TARGET_LIST_END(tlp, &hello_targets) ;

	task_alloc_send(tp, (size_t) mtu_max);
	task_alloc_recv(tp, (size_t) mtu_max + IP_MAXHDRLEN);
    }


    /* Evaluate policy for new targets */
    {
	int changes = 0;
	int have_list = 0;
	rt_list *rthl = (rt_list *) 0;
	target *tlp;

	rt_open(tp);
	
	TARGET_LIST(tlp, &hello_targets) {
	    if (BIT_TEST(tlp->target_flags, TARGETF_BROADCAST)) {
		if (BIT_TEST(tlp->target_ifap->ifa_ps[tp->task_rtproto].ips_state, IFPS_NOIN)) {
		    register rt_entry *rt;
		    register gw_entry *gwp;

		    GW_LIST(hello_gw_list, gwp) {
			RTQ_LIST(&gwp->gw_rtq, rt) {
			    if (RT_IFAP(rt) == tlp->target_ifap) {
				rt_delete(rt);
				changes++;
			    }
			} RTQ_LIST_END(&gwp->gw_rtq, rt) ;
		    } GW_LIST(hello_gw_list, gwp) ;
		}
	    }
	    switch (BIT_TEST(tlp->target_flags, TARGETF_POLICY|TARGETF_SUPPLY)) {
	    case TARGETF_SUPPLY:
		/* Need to run policy for this target */

		if (!have_list) {
		    /* Get target list */
		    rthl = rthlist_active(AF_INET);
		    have_list++;
		}

		if (rthl) {
		    /* and run policy */
		    changes += hello_policy(tp, tlp, rthl);
		}

		/* Indicate policy has been run */
		BIT_SET(tlp->target_flags, TARGETF_POLICY);
		break;

	    case TARGETF_POLICY:
		/* Indicate policy run on this target */

		BIT_RESET(tlp->target_flags, TARGETF_POLICY);
		break;

	    default:
		break;
	    }
	} TARGET_LIST_END(tlp, &hello_targets) ;

	if (rthl) {
	    RTLIST_RESET(rthl);
	}

	rt_close(tp, (gw_entry *) 0, 0, NULL);
	
	if (changes
	    && !BIT_TEST(hello_flags, HELLOF_RECONFIG)) {
	    hello_need_flash(tp);
	}
    }

    if (targets != n_targets
	|| hello_n_source != n_source) {

	tracef("hello_target_list: ");
	if (targets) {
	    tracef("supplying updates to");
	    if (targets - hello_n_source) {
		tracef(" %d interface%s",
		       targets - hello_n_source,
		       (targets - hello_n_source) > 1 ? "s" : "");
	    }
	    if (hello_n_source) {
		tracef(" %d gateways",
		       hello_n_source);
	    }
	} else {
	    tracef("just listening");
	}	
	n_targets = targets;
	n_source = hello_n_source;
	trace_log_tp(tp,
		     TRC_NL_AFTER,
		     LOG_INFO,
		     (NULL));
    }

    hello_target_list_job = (task_job *) 0;
}


/*
 *	Reinit after parse
 */
/*ARGSUSED*/
static void
hello_reinit __PF1(tp, task *)
{
    int entries = 0;
    gw_entry *gwp;

    trace_inherit_global(hello_trace_options, hello_trace_types, (flag_t) 0);
    trace_set(tp->task_trace, hello_trace_options);

    /* Open the routing table */
    rt_open(tp);

    GW_LIST(hello_gw_list, gwp) {
	rt_entry *rt;

	RTQ_LIST(&gwp->gw_rtq, rt) {
	    pref_t preference = hello_preference;

	    /* Calculate preference of this route */
	    if (import(rt->rt_dest,
		       rt->rt_dest_mask,
		       hello_import_list,
		       RT_IFAP(rt)->ifa_ps[tp->task_rtproto].ips_import,
		       rt->rt_gwp->gw_import,
		       &preference,
		       RT_IFAP(rt),
		       (void_t) 0)) {
		if (rt->rt_preference != preference) {
		    /* The preference has changed, change the route */
		    (void) rt_change(rt,
				     rt->rt_metric,
				     rt->rt_metric2,
				     rt->rt_tag,
				     preference,
				     rt->rt_preference2,
				     rt->rt_n_gw, rt->rt_routers);
		}
		entries++;
	    } else {
		/* This route is now restricted */
		rt_delete(rt);
	    }
	} RTQ_LIST_END(&gwp->gw_rtq, rt) ;
    } GW_LIST(hello_gw_list, gwp) ;
    
    /* Close the routing table */
    rt_close(tp, (gw_entry *) 0, entries, NULL);

    /* Indicate a reconfig in process */
    BIT_SET(hello_flags, HELLOF_RECONFIG);
}


/*
 *	Deal with interface policy
 */
static void
hello_control_reset __PF2(tp, task *,
			  ifap, if_addr *)
{
    struct ifa_ps *ips = &ifap->ifa_ps[tp->task_rtproto];

    BIT_RESET(ips->ips_state, IFPS_RESET);
    ips->ips_metric_in = hop_to_hello[ifap->ifa_metric] + HELLO_HOP;
    ips->ips_metric_out = (metric_t) 0;
}


static void
hello_control_set __PF2(tp, task *,
			ifap, if_addr *)
{
    struct ifa_ps *ips = &ifap->ifa_ps[tp->task_rtproto];
    config_entry **list = config_resolv_ifa(hello_int_policy,
					    ifap,
					    HELLO_CONFIG_MAX);

    /* Reset */
    hello_control_reset(tp, ifap);

    /* Set defaults */
    switch (BIT_TEST(ifap->ifa_state, IFS_POINTOPOINT|IFS_LOOPBACK|IFS_BROADCAST)) {
    case IFS_LOOPBACK:
	/* By default we do not send or listen on the loopback */
	/* interface. */
	BIT_SET(ips->ips_state, IFPS_NOIN|IFPS_NOOUT);
	break;

    case IFS_POINTOPOINT:
	/* By default we do not send HELLO out a P2P interface. */
	BIT_SET(ips->ips_state, IFPS_NOOUT);
	break;

    case IFS_BROADCAST:
    default:
	/* On broadcast and NBMA interfaces we default to sending and */
	/* receiving. */
	break;
    }

    /* Process configuration info */
    if (list) {
	int type = HELLO_CONFIG_MAX;
	config_entry *cp;

	/* Fill in the parameters */
	while (--type) {
	    if ((cp = list[type])) {
		switch (type) {
		case HELLO_CONFIG_IN:
		    if (cp->config_data) {
			BIT_RESET(ips->ips_state, IFPS_NOIN);
		    } else {
			BIT_SET(ips->ips_state, IFPS_NOIN);
		    }
		    break;

		case HELLO_CONFIG_OUT:
		    if (cp->config_data) {
			BIT_RESET(ips->ips_state, IFPS_NOOUT);
		    } else {
			BIT_SET(ips->ips_state, IFPS_NOOUT);
		    }
		    break;

		case HELLO_CONFIG_METRICIN:
		    BIT_SET(ips->ips_state, IFPS_METRICIN);
		    ips->ips_metric_in = (metric_t) cp->config_data;
		    break;

		case HELLO_CONFIG_METRICOUT:
		    BIT_SET(ips->ips_state, IFPS_METRICOUT);
		    ips->ips_metric_out = (metric_t) cp->config_data;
		    break;
		}
	    }
	}

	config_resolv_free(list, HELLO_CONFIG_MAX);
    }
}


/*
 *	Terminating - clean up
 */
static void
hello_terminate __PF1(tp, task *)
{
    if_addr *ifap;
	
    /* Release the target list, bit assignments, and buffers */
    target_free_list(tp, &hello_targets);

    /* Reset the policy */
    IF_ADDR(ifap) {
	if (socktype(ifap->ifa_addr) == AF_INET) {
	    hello_control_reset(tp, ifap);
	}
    } IF_ADDR_END(ifap) ;

    {
	gw_entry *gwp;
	
	rt_open(tp);

	GW_LIST(hello_gw_list, gwp) {
	    rt_entry *rt = (rt_entry *) 0;

	    RTQ_LIST(&gwp->gw_rtq, rt) {
		rt_delete(rt);
	    } RTQ_LIST_END(&gwp->gw_rtq, rt) ;
	} GW_LIST(hello_gw_list, gwp) ;

	rt_close(tp, (gw_entry *) 0, 0, NULL);
    }

    hello_cleanup(tp);
    
    task_delete(tp);
    hello_timer_update = hello_timer_flash = hello_timer_age = (task_timer *) 0;
}


/*
 *	Deal with an interface status change
 */
static void
hello_ifachange __PF2(tp, task *,
		      ifap, if_addr *)
{
    int changes = 0;
    gw_entry *gwp;

    if (socktype(ifap->ifa_addr) != AF_INET) {
	return;
    }
    
    rt_open(tp);
    
    switch (ifap->ifa_change) {
    case IFC_NOCHANGE:
    case IFC_ADD:
	if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
	    hello_control_set(tp, ifap);
	}
	break;

    case IFC_DELETE:
    case IFC_DELETE|IFC_UPDOWN:
    Delete:
	GW_LIST(hello_gw_list, gwp) {
	    rt_entry *rt = (rt_entry *) 0;

	    RTQ_LIST(&gwp->gw_rtq, rt) {
		if (RT_IFAP(rt) == ifap) {
		    rt_delete(rt);
		    changes++;
		}
	    } RTQ_LIST_END(&gwp->gw_rtq, rt) ;
	} GW_LIST(hello_gw_list, gwp) ;

	hello_control_reset(tp, ifap);
	break;

    default:
	/* Something has changed */

	if (BIT_TEST(ifap->ifa_change, IFC_UPDOWN)) {
	    if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
		/* Down to Up transition */

		hello_control_set(tp, ifap);
	    } else {
		/* UP to DOWN transition */

		goto Delete;
	    }
	}
	if (BIT_TEST(ifap->ifa_change, IFC_NETMASK)) {
	    /* The netmask has changed, delete any routes that */
	    /* point at gateways that are no longer reachable */

	    target *tlp;
	    
	    GW_LIST(hello_gw_list, gwp) {
		rt_entry *rt = (rt_entry *) 0;

		RTQ_LIST(&gwp->gw_rtq, rt) {
		    if (RT_IFAP(rt) == ifap
			&& (if_withdstaddr(RT_ROUTER(rt)) != ifap
			    || BIT_TEST(rt->rt_state, RTS_IFSUBNETMASK))) {
			/* Interface for this route has changed or we derived the subnet mask */

			rt_delete(rt);
			changes++;
		    }
		} RTQ_LIST_END(&gwp->gw_rtq, rt) ;
	    } GW_LIST(hello_gw_list, gwp) ;

	    TARGET_LIST(tlp, &hello_targets) {
		if (tlp->target_ifap == ifap
		    && BIT_TEST(tlp->target_flags, TARGETF_SUPPLY)) {
		    /* Some subnet masks may have been derrived, indicate that policy needs to be rerun */

		    BIT_RESET(tlp->target_flags, TARGETF_POLICY);
		}
	    } TARGET_LIST_END(tlp, &hello_targets) ;
	}
	if (BIT_TEST(ifap->ifa_change, IFC_METRIC)) {
	    struct ifa_ps *ips = &ifap->ifa_ps[tp->task_rtproto];
	    
	    if (!BIT_TEST(ips->ips_state, IFPS_METRICIN)) {
		ips->ips_metric_in = hop_to_hello[ifap->ifa_metric] + HELLO_HOP;
	    }
	}
	/* A METRIC change will take effect in 15 seconds with the next update received */
	/* A BROADCAST change is automatic since we have a pointer to the pointer to */
	/* 	the broadcast address */
	/* An ADDR change will take effect when the peers notice that the */
	/* 	old address is no longer sending */
	/* An MTU change will take effect when we get around to sending packets */
	/* A SEL change is of no interest to us */
	break;
    }

    rt_close(tp, (gw_entry *) 0, changes, NULL);

    /* Schedule a target list rebuild if necessary */
    if (!hello_target_list_job) {
	hello_target_list_job = task_job_create(tp,
						TASK_JOB_FG,
						"Target_Build",
						hello_target_list,
						(void_t) 0);
    }
}


static void
hello_int_dump __PF2(fd, FILE *,
		     list, config_entry *)
{
    register config_entry *cp;

    CONFIG_LIST(cp, list) {
	switch (cp->config_type) {
	case HELLO_CONFIG_IN:
	    (void) fprintf(fd, " %shelloin",
			   cp->config_data ? "" : "no");
	    break;

	case HELLO_CONFIG_OUT:
	    (void) fprintf(fd, " %shelloout",
			   cp->config_data ? "" : "no");
	    break;

	case HELLO_CONFIG_METRICIN:
	    (void) fprintf(fd, " metricin %u",
			   (metric_t) cp->config_data);
	    break;

	case HELLO_CONFIG_METRICOUT:
	    (void) fprintf(fd, " metricout %u",
			   (metric_t) cp->config_data);
	    break;

	default:
	    assert(FALSE);
	    break;
	}
    } CONFIG_LIST_END(cp, list) ;
}

/*
 *	Dump info about HELLO
 */
static void
hello_dump __PF2(tp, task *,
		 fd, FILE *)
{
    (void) fprintf(fd, "\tFlags: %s\tDefault metric: %d\t\tDefault preference: %d\n",
		   trace_bits(hello_flag_bits, hello_flags),
		   hello_default_metric,
		   hello_preference);
    target_dump(fd, &hello_targets, (bits *) 0);
    if (hello_gw_list) {
	(void) fprintf(fd, "\tActive gateways:\n");
	gw_dump(fd,
		"\t\t",
		hello_gw_list,
		tp->task_rtproto);
	(void) fprintf(fd, "\n");
    }
    if (hello_int_policy) {
	(void) fprintf(fd, "\tInterface policy:\n");
	control_interface_dump(fd, 2, hello_int_policy, hello_int_dump);
    }
    control_import_dump(fd, 1, RTPROTO_HELLO, hello_import_list, hello_gw_list);
    control_export_dump(fd, 1, RTPROTO_HELLO, hello_export_list, hello_gw_list);
    (void) fprintf(fd, "\n");
}


/*
 *	Initialize HELLO socket and task
 */
/*ARGSUSED*/
void
hello_init __PF0(void)
{
    _PROTOTYPE(flash,
	       void,
	       (task *,
		rt_list *)) = hello_flash;	/* Hack for UTX/32 and Ultrix */
    _PROTOTYPE(newpolicy,
	       void,
	       (task *,
		rt_list *)) = hello_newpolicy;	/* ditto */
    static task *hello_task;


    if (!hello_win_block_index) {
	hello_win_block_index = task_block_init(sizeof (struct hello_win), "hello_win");
    }

    if (BIT_TEST(hello_flags, HELLOF_ON)) {
	if (!hello_task) {
	    trace_inherit_global(hello_trace_options, hello_trace_types, (flag_t) 0);
	    hello_task = task_alloc("HELLO",
				    TASKPRI_PROTO,
				    hello_trace_options);
	    hello_task->task_proto = IPPROTO_HELLO;
	    hello_task->task_rtproto = RTPROTO_HELLO;
	    task_set_recv(hello_task, hello_recv);
	    task_set_cleanup(hello_task, hello_cleanup);
	    task_set_reinit(hello_task, hello_reinit);
	    task_set_dump(hello_task, hello_dump);
	    task_set_terminate(hello_task, hello_terminate);
	    task_set_ifachange(hello_task, hello_ifachange);
	    task_set_flash(hello_task, flash);
	    task_set_newpolicy(hello_task, newpolicy);

	    if ((hello_task->task_socket = task_get_socket(hello_task, AF_INET, SOCK_RAW, IPPROTO_HELLO)) < 0) {
		task_quit(errno);
	    }
	    if (task_set_option(hello_task,
				TASKOPTION_RECVBUF,
				task_maxpacket) < 0) {
		task_quit(errno);
	    }
	    if (task_set_option(hello_task,
				TASKOPTION_DONTROUTE,
				TRUE) < 0) {
		task_quit(errno);
	    }
	    if (task_set_option(hello_task,
				TASKOPTION_NONBLOCKING,
				(caddr_t) TRUE) < 0) {
		task_quit(errno);
	    }
	    (void) task_set_option(hello_task,
				   TASKOPTION_TTL,
				   1);
	    if (!task_create(hello_task)) {
		task_quit(EINVAL);
	    }
	}
    } else {
	hello_cleanup((task *) 0);

	if (hello_task) {
	    hello_terminate(hello_task);
	    hello_task = (task *) 0;
	}
    }
}


/*
 * %(Copyright)
 */
