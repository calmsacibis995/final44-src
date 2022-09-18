/*
 * $Id: ospf_log.c,v 1.15 1993/12/22 03:57:32 jch Exp $
 */

/* %(Copyright.header) */

#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"

const bits ospf_logtype[] =
{
    { 0,		"Monitor request" },			/* OSPF_RECV_MON */
    { 0,		"Hello" },				/* OSPF_RECV_HELLO */
    { 0,		"DB Description" },			/* OSPF_RECV_DD */
    { 0,		"Link-State Req" },			/* OSPF_RECV_LSR */
    { 0,		"Link-State Update" },			/* OSPF_RECV_LSU */
    { 0,		"Link-State Ack" },			/* OSPF_RECV_LSA */

    { 0,		"Monitor response" },			/* OSPF_SEND_MON */
    { 0,		"Hello" },				/* OSPF_SEND_HELLO */
    { 0,		"DB Description" },			/* OSPF_SEND_DD */
    { 0,		"Link-State Req" },			/* OSPF_SEND_LSR */
    { 0,		"Link-State Update" },			/* OSPF_SEND_LSU */
    { 0,		"Link-State Ack" },			/* OSPF_SEND_LSA */
		     /* -------------------------------- */
    { OSPF_LOGF_ALWAYS,	"IP: bad destination" },		/* OSPF_ERR_IP_DEST */
    { OSPF_LOGF_ALWAYS,	"IP: bad protocol" },			/* OSPF_ERR_IP_PROTO */
    { OSPF_LOGF_ALWAYS,	"IP: received my own packet" },		/* OSPF_ERR_IP_ECHO */
    { OSPF_LOGF_ALWAYS,	"OSPF: bad packet type" },		/* OSPF_ERR_OSPF_TYPE */
    { OSPF_LOGF_ALWAYS,	"OSPF: bad version" },			/* OSPF_ERR_OSPF_VERSION */
    { OSPF_LOGF_ALWAYS,	"OSPF: bad checksum" },			/* OSPF_ERR_OSPF_CHKSUM */
    { OSPF_LOGF_ALWAYS,	"OSPF: bad area id" },			/* OSPF_ERR_OSPF_AREAID */
    { OSPF_LOGF_ALWAYS,	"OSPF: area mismatch" },		/* OSPF_ERR_OSPF_ABR */
    { OSPF_LOGF_ALWAYS,	"OSPF: bad virtual link" },		/* OSPF_ERR_OSPF_VL */
    { OSPF_LOGF_ALWAYS,	"OSPF: bad authentication type" },	/* OSPF_ERR_OSPF_AUTH_TYPE */
    { OSPF_LOGF_ALWAYS,	"OSPF: bad authentication key" },	/* OSPF_ERR_OSPF_AUTH_KEY */
    { OSPF_LOGF_ALWAYS,	"OSPF: packet too small" },		/* OSPF_ERR_OSPF_SHORT */
    { OSPF_LOGF_ALWAYS,	"OSPF: packet size > ip length" },	/* OSPF_ERR_OSPF_LONG */
    { OSPF_LOGF_ALWAYS,	"OSPF: transmit error" },		/* OSPF_ERR_OSPF_SEND */
    { OSPF_LOGF_ALWAYS,	"OSPF: interface down" },		/* OSPF_ERR_OSPF_IFDOWN */
    { OSPF_LOGF_ALWAYS,	"OSPF: unknown neighbor" },		/* OSPF_ERR_OSPF_NBR */
    { OSPF_LOGF_ALWAYS,	"HELLO: netmask mismatch" },		/* OSPF_ERR_HELLO_MASK */
    { OSPF_LOGF_ALWAYS,	"HELLO: hello timer mismatch" },	/* OSPF_ERR_HELLO_TIMER */
    { OSPF_LOGF_ALWAYS,	"HELLO: dead timer mismatch" },		/* OSPF_ERR_HELLO_DEAD */
    { OSPF_LOGF_ALWAYS,	"HELLO: extern option mismatch" },	/* OSPF_ERR_HELLO_E */
    { OSPF_LOGF_ALWAYS,	"HELLO: router id confusion" },		/* OSPF_ERR_HELLO_ID */
    { OSPF_LOGF_TIMER,	"HELLO: virtual neighbor unknown" },	/* OSPF_ERR_HELLO_VIRT */
    { OSPF_LOGF_ALWAYS,	"HELLO: NBMA neighbor unknown" },	/* OSPF_ERR_HELLO_NBMA */
    { OSPF_LOGF_TIMER,	"DD: neighbor state low" },		/* OSPF_ERR_DD_STATE */
    { OSPF_LOGF_ALWAYS,	"DD: router id confusion" },		/* OSPF_ERR_DD_RTRID */
    { OSPF_LOGF_ALWAYS,	"DD: extern option mismatch" },		/* OSPF_ERR_DD_E */
    { 0,		"DD: unknown LSA type" },		/* OSPF_ERR_DD_TYPE */
    { OSPF_LOGF_TIMER,	"LS ACK: neighbor state low" },		/* OSPF_ERR_ACK_STATE */
    { OSPF_LOGF_TIMER,	"LS ACK: bad ack" },			/* OSPF_ERR_ACK_BAD */
    { OSPF_LOGF_TIMER,	"LS ACK: duplicate ack" },		/* OSPF_ERR_ACK_DUP */
    { OSPF_LOGF_ALWAYS,	"LS ACK: Unknown LSA type" },		/* OSPF_ERR_ACK_TYPE */
    { OSPF_LOGF_TIMER,	"LS REQ: neighbor state low" },		/* OSPF_ERR_REQ_STATE */
    { OSPF_LOGF_ALWAYS,	"LS REQ: empty request" },		/* OSPF_ERR_REQ_EMPTY */
    { OSPF_LOGF_ALWAYS,	"LS REQ: bad request" },		/* OSPF_ERR_REQ_BOGUS */
    { OSPF_LOGF_TIMER,	"LS UPD: neighbor state low" },		/* OSPF_ERR_UPD_STATE */
    { OSPF_LOGF_TIMER,	"LS UPD: newer self-gen LSA" },		/* OSPF_ERR_UPD_NEWER */
    { OSPF_LOGF_ALWAYS,	"LS UPD: LSA checksum bad" },		/* OSPF_ERR_UPD_CHKSUM */
    { OSPF_LOGF_TIMER,	"LS UPD: received less recent LSA" },	/* OSPF_ERR_UPD_OLDER */
    { 0,		"LS UPD: unknown LSA type" },		/* OSPF_ERR_UPD_TYPE */
};

u_long ospf_cumlog[OSPF_ERR_LAST] = { 0 };

u_int ospf_log_last_lsa;

void
ospf_log_rx __PF4(type, int,
		  intf, struct INTF *,
		  src, sockaddr_un *,
		  dst, sockaddr_un *)
{
    int pri;

    if (BIT_TEST(ospf_logtype[type].t_bits, OSPF_LOGF_ALWAYS)) {
	pri = LOG_WARNING;
    } else if (BIT_TEST(ospf_logtype[type].t_bits, OSPF_LOGF_TIMER)
	       && (!intf || OSPF_LOG_TIME(intf))) {
	pri = LOG_INFO;
    } else {
	pri = 0;
    }
    /* Only log the first log_first messages per type.  Then spit out */
    /* only one every log_every messages per type. */
    if ((ospf.log_first
	 && ospf_cumlog[type] > ospf.log_first)
	&& (ospf.log_every
	    && ospf_cumlog[type] % ospf.log_every)) {
	pri = 0;
    }

    if (intf && intf->area) {
	trace_log_tf(ospf.trace_options,
		     0,
		     pri,
		     ("OSPF RECV Area %A %-15A -> %A: %s",
		      sockbuild_in(0, intf->area->area_id),
		      src,
		      dst,
		      trace_state(ospf_logtype, type)));
    } else {
	trace_log_tf(ospf.trace_options,
		     0,
		     pri,
		     ("OSPF RECV %-15A -> %A: %s",
		      src,
		      dst,
		      trace_state(ospf_logtype, type)));
    }
}


/*
 * Change dest addr to string
 */
sockaddr_un *
ospf_addr2str __PF1(to, sockaddr_un *)
{
    switch (sock2ip(to)) {
    case ALL_UP_NBRS:
	return sockbuild_str("All_up_nbrs");

    case ALL_ELIG_NBRS:
	return sockbuild_str("All_elig_nbrs");

    case ALL_EXCH_NBRS:
	return sockbuild_str("All_exch_nbrs");

    case DR_and_BDR:
	return sockbuild_str("Dr_and_Bdr");
    }

    return to;
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
