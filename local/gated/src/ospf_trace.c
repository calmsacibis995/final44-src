/*
 * $Id: ospf_trace.c,v 1.25.2.3 1994/11/08 20:23:14 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "inet.h"
#include "ospf.h"


static const char *pkttype[] = {
    "Monitor",
    "Hello",
    "Database Description",
    "Link State Request",
    "Link State Update",
    "Link State Ack"
};


static const bits ospf_imms_bits[] = {
    { bit_I,	"I" },
    { bit_M,	"M" },
    { bit_MS,	"MS" },
    { 0, NULL }
};

static const bits ospf_option_bits[] = {
    { OPT_T_bit,	"TOS" },
    { OPT_E_bit,	"Externals" },
    { OPT_M_bit,	"Multicast" },
    { OPT_N_bit,	"NSSA" },
    { 0, NULL }
};

const bits ospf_ls_type_bits[] = {
    { LS_STUB,		"Stub" },
    { LS_RTR,		"Router" },
    { LS_NET,		"Net" },
    { LS_SUM_NET,	"SumNet" },
    { LS_SUM_ASB,	"SumASB" },
    { LS_ASE,		"ASE" },
    { LS_GM,		"Group" },
    { LS_NSSA,		"NSSA" },
    {0}
};

const bits ospf_sched_bits[] = {
    { ALLSCHED,		"All" },
    { RTRSCHED, 	"Router" },
    { NETSCHED, 	"Net" },
    { INTRASCHED, 	"Intra" },
    { SUMNETSCHED,	"SumNet" },
    { SUMASBSCHED,	"SumASB" },
    { ASESCHED, 	"ASE" },
    { 0, NULL }
};

const bits ospf_trace_types[] = {
    { TR_OSPF_LSA_BLD,	"lsa-build" },
    { TR_OSPF_SPF,	"spf" },
    { TR_OSPF_LSA_TX,	"lsa-transmit" },
    { TR_OSPF_LSA_RX,	"lsa-receive" },
    { TR_OSPF_TRAP,	"trap" },
#ifdef	DEBUG
    { TR_OSPF_DEBUG,	"debug" },
#endif	/* DEBUG */
    { TR_DETAIL,	"detail packets" },
    { TR_DETAIL_SEND,	"detail send packets" },
    { TR_DETAIL_RECV,	"detail recv packets" },
    { TR_PACKET,		"packets" },
    { TR_PACKET_SEND,	"send packets" },
    { TR_PACKET_RECV,	"recv packets" },
    { TR_DETAIL_1,	"detail hello" },
    { TR_DETAIL_SEND_1,	"detail send hello" },
    { TR_DETAIL_RECV_1,	"detail recv hello" },
    { TR_PACKET_1,	"hello" },
    { TR_PACKET_SEND_1,	"send hello" },
    { TR_PACKET_RECV_1,	"recv hello" },
    { TR_DETAIL_2,	"detail dd" },
    { TR_DETAIL_SEND_2,	"detail send dd" },
    { TR_DETAIL_RECV_2,	"detail recv dd" },
    { TR_PACKET_2,	"dd" },
    { TR_PACKET_SEND_2,	"send dd" },
    { TR_PACKET_RECV_2,	"recv dd" },
    { TR_DETAIL_3,	"detail request" },
    { TR_DETAIL_SEND_3,	"detail send request" },
    { TR_DETAIL_RECV_3,	"detail recv request" },
    { TR_PACKET_3,	"request" },
    { TR_PACKET_SEND_3,	"send request" },
    { TR_PACKET_RECV_3,	"recv request" },
    { TR_DETAIL_4,	"detail lsu" },
    { TR_DETAIL_SEND_4,	"detail send lsu" },
    { TR_DETAIL_RECV_4,	"detail recv lsu" },
    { TR_PACKET_4,	"lsu" },
    { TR_PACKET_SEND_4,	"send lsu" },
    { TR_PACKET_RECV_4,	"recv lsu" },
    { TR_DETAIL_5,	"detail ack" },
    { TR_DETAIL_SEND_5,	"detail send ack" },
    { TR_DETAIL_RECV_5,	"detail recv ack" },
    { TR_PACKET_5,	"ack" },
    { TR_PACKET_SEND_5,	"send ack" },
    { TR_PACKET_RECV_5,	"recv ack" },
    { 0, NULL }
};


static inline const char *
ospf_ls_hdr_type __PF1(ls_type, u_int8)
{
    if (ls_type >= LS_MAX) {
	static char msg[9];

	(void) sprintf(msg, "??%d??", ls_type);
	return msg;
    }

    return trace_state(ospf_ls_type_bits, ls_type);
}


/*
 * Print the LSA hdr
 */
void
ospf_log_ls_hdr __PF4(ls_hdr, struct LS_HDR *,
		      prefix, const char *,
		      age, time_t,
		      stored, time_t)
{
    int elapsed;
    
    tracef("%s\t%-6s\tId: %-15A  AdvRtr: %-15A  Age: ",
	   prefix,
	   ospf_ls_hdr_type(ls_hdr->ls_type),
	   sockbuild_in(0, ls_hdr->ls_id),
	   sockbuild_in(0, ls_hdr->adv_rtr),
	   age);
    if (stored
	&& (age < MaxAge)
	&& (elapsed = time_sec - stored)) {

	trace_only_tf(ospf.trace_options,
		      0,
		      ("%#T=(%#T+%#T)",
		       age + elapsed,
		       age,
		       elapsed));
    } else {
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%#T",
		       age));
    }
    trace_only_tf(ospf.trace_options,
		  0,
		  ("%s\t\tLen: %3d  Seq #: %8x  Checksum: %#4x",
		   prefix,
		   ntohs(ls_hdr->length),
		   ntohl(ls_hdr->ls_seq),
		   ntohs(ls_hdr->ls_chksum)));
}


static int
ospf_log_lsa __PF2(adv, union LSA_PTR,
		   prefix, const char *)
{
    int cnt, i;
    struct NET_LA_PIECES *att_rtr;
    struct RTR_LA_PIECES *linkp;

    ospf_log_ls_hdr(&adv.rtr->ls_hdr,
		    prefix,
		    ntohs(adv.rtr->ls_hdr.ls_age),
		    (time_t) 0);

    switch (adv.rtr->ls_hdr.ls_type) {
    case LS_RTR:
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s\t\tCapabilities: As Border: %s Area Border: %s",
		       prefix,
		       (ntohs(adv.rtr->E_B) & bit_E) ? "On" : "Off",
		       (ntohs(adv.rtr->E_B) & bit_B) ? "On" : "Off"));

	for (cnt = ntohs(adv.rtr->lnk_cnt),
	     i = 0,
	     linkp = (struct RTR_LA_PIECES *) &adv.rtr->link;
	     i < cnt;
	     linkp = (struct RTR_LA_PIECES *) ((long) linkp +
					      RTR_LA_PIECES_SIZE +
					      ((linkp->metric_cnt) * RTR_LA_METRIC_SIZE)),
	     i++) {
	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s\t\t%-8s  ID: %-15A  Data: %-15A metric: %-4d",
			   prefix,
			   ospf_con_types[linkp->con_type],
			   sockbuild_in(0, linkp->lnk_id),
			   sockbuild_in(0, linkp->lnk_data),
			   ntohs(linkp->tos0_metric)));
	}
	break;

    case LS_NET:
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s\t\tMask: %A",
		       prefix,
		       sockbuild_in(0, adv.net->net_mask)));

	cnt = ntohs(adv.net->ls_hdr.length) - NET_LA_HDR_SIZE;
	for (att_rtr = &adv.net->att_rtr, i = 0;
	     i < cnt;
	     att_rtr++, i += 4) {
	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s\t\tAttached router: %A",
			   prefix,
			   sockbuild_in(0, att_rtr->lnk_id)));
	}
	break;

    case LS_SUM_NET:
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s\t\tMask: %-15A",
		       prefix,
		       sockbuild_in(0, adv.sum->net_mask)));
	/* Fall through */

    case LS_SUM_ASB:
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s\t\tTos 0 metric: %-4d",
		       prefix,
		       ntohl(adv.sum->tos0.tos_metric)));
	break;

    case LS_ASE:
    case LS_NSSA:
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s\t\tMask: %-15A  Tos 0 metric: %-5d  Type: %-1d",
		       prefix,
		       sockbuild_in(0, adv.ase->net_mask),
		       ADV_BIG_METRIC(adv.ase),
		       ADV_ASE_TYPE2(adv.ase) ? 2 : 1));

	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s\t\tForwarding Address: %-15A Tag: %A",
		       prefix,
		       sockbuild_in(0, adv.ase->tos0.ForwardAddr),
		       ospf_path_tag_dump(inet_autonomous_system, adv.ase->tos0.ExtRtTag)));
	break;

    case LS_GM:
	switch (adv.gm->vertex.type) {
	case GM_TYPE_RTR:
	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s\t\tRouter ID: %-15A",
			   prefix,
			   sockbuild_in(0, adv.gm->vertex.id)));
	    break;

	case GM_TYPE_NET:
	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s\t\tDesignated Router: %-15A",
			   prefix,
			   sockbuild_in(0, adv.gm->vertex.id)));
	    break;
	}
	break;
    }

    return ntohs(adv.rtr->ls_hdr.length);
}


void
ospf_trace __PF8(pkt, struct OSPF_HDR *,
		 len, size_t,
		 type, u_int,
		 direction, int,
		 intf, struct INTF *,
		 src, sockaddr_un *,
		 dst, sockaddr_un *,
		 detail, int)
{
    const char *prefix = direction ? "OSPF RECV" : "OSPF SENT";

    len = ntohs(pkt->ospfh_length);
    
    trace_only_tf(ospf.trace_options,
		  0,
		  ("%s %A(%s) -> %A  %s  Vers: %d  Len: %d",
		   prefix,
		   src,
		   intf && intf->ifap ? intf->ifap->ifa_link->ifl_name : "n/a",
		   ospf_addr2str(dst),
		   pkttype[pkt->ospfh_type],
		   pkt->ospfh_version,
		   len));

    trace_only_tf(ospf.trace_options,
		  0,
		  ("%s RouterID: %A  Area: %A  Checksum: %#x",
		   prefix,
		   sockbuild_in(0, pkt->ospfh_rtr_id),
		   sockbuild_in(0, pkt->ospfh_area_id),
		   ntohs(pkt->ospfh_checksum)));

    switch (ntohs(pkt->ospfh_auth_type)) {
	register u_int32 *bp;

    case OSPF_AUTH_NONE:
    case OSPF_AUTH_SIMPLE:
	bp = pkt->ospfh_auth_key;
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s Auth: Type: %d Key: %08x.%08x",
		       prefix,
		       ntohs(pkt->ospfh_auth_type),
		       bp[0], bp[1]));
	break;

    case OSPF_AUTH_MD5:
	bp = (u_int32 *) ((void_t) ((byte *) pkt + ntohs(pkt->ospfh_md5_offset)));
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s Auth: Type: MD5 Instance: %u Sequence: %x Digest: %08x.%08x.%08x.%08x",
		       prefix,
		       ntohs(pkt->ospfh_md5_instance),
		       ntohl(pkt->ospfh_md5_sequence),
		       bp[0], bp[1], bp[2], bp[3]));
	break;
    }


    if (!detail) {
	return;
    }
    
    switch (type) {
    case OSPF_PKT_MON:
        {
	    struct MON_HDR *mon = &pkt->ospfh_un.mon;
	    
	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s type: %d req: '%c' more: %d param_cnt: %d",
			   prefix,
			   mon->type,
			   mon->req,
			   mon->more,
			   mon->param_cnt));
	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s port: %d local:%d p0: %08x p1: %08x p2: %08x p3: %08x",
			   prefix,
			   ntohs(mon->port),
			   ntohs(mon->local),
			   ntohl(mon->p[0]),
			   ntohl(mon->p[1]),
			   ntohl(mon->p[2]),
			   ntohl(mon->p[3])));
	}
	break;
	
    case OSPF_PKT_HELLO:
        {
	    struct HELLO_HDR *hello = &pkt->ospfh_un.hello;
	    struct RHF *rhf = &hello->rhf;
	    caddr_t limit = (caddr_t) rhf + len - OSPF_HDR_SIZE - HELLO_HDR_SIZE;

	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s Netmask: %-12A Hello Int: %-4d Options: <%s>",
			   prefix,
			   sockbuild_in(0, hello->netmask),
			   ntohs(hello->HelloInt),
			   trace_bits(ospf_option_bits, (flag_t) hello->options)));
	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s Pri: %-4d DeadInt: %-4d DR: %-15A BDR: %-15A",
			   prefix,
			   hello->rtr_priority,
			   ntohl(hello->DeadInt),
			   sockbuild_in(0, hello->dr),
			   sockbuild_in(0, hello->bdr)));

	    if ((caddr_t) rhf < limit) {
		int i = 1;
	    
		tracef("%s Attached routers:",
		       prefix);

		for (; (caddr_t) rhf < limit; rhf++) {
		    tracef("\t%-15A",
			   sockbuild_in(0, rhf->rtr));

		    if (++i > 3) {
			i = 0;
			trace_only_tf(ospf.trace_options,
				      0,
				      (NULL));
			tracef("%s\t",
			       prefix);
		    }
		}
		if (i > 0) {
		    trace_only_tf(ospf.trace_options,
				  0,
				  (NULL));
		}
	    }
	}
	break;
 
    case OSPF_PKT_DD:
	{
	    struct DB_HDR *dbh = &pkt->ospfh_un.database;
	    struct LS_HDR *dbp;
 
	    tracef("%s Flags <%s>",
		   prefix,
		   trace_bits(ospf_imms_bits, (flag_t) dbh->I_M_MS));
	    trace_only_tf(ospf.trace_options,
			  0,
			  (" Options: <%s> seq: %8x",
			   trace_bits(ospf_option_bits, (flag_t) dbh->options),
			   ntohl((u_long) dbh->seq)));

	    for ( dbp = &dbh->dbp, len -= (OSPF_HDR_SIZE + DB_HDR_SIZE);
		 len;
		 len -= DB_PIECE_SIZE, dbp++ ) {

		ospf_log_ls_hdr(dbp,
				prefix,
				ntohs(dbp->ls_age),
				(time_t) 0);
	    }
	}
	break;
 
    case OSPF_PKT_LSR:
	{
	    struct LS_REQ_HDR *ls_req = &pkt->ospfh_un.ls_req;
	    struct LS_REQ_PIECE *req;

	    for ( req = &ls_req->req, len -= OSPF_HDR_SIZE;
		 len; 
		 len -= LS_REQ_PIECE_SIZE, req++ ) {

		trace_only_tf(ospf.trace_options,
			      0,
			      ("%-6s\t%s\tId: %-15A  AdvRtr: %-15A",
			       prefix,
			       ospf_ls_hdr_type(req->ls_type),
			       sockbuild_in(0, req->ls_id),
			       sockbuild_in(0, req->adv_rtr)));
	    }
	}
	break;
	
    case OSPF_PKT_LSU:
        {
	    int adv_len = 0;
	    struct LS_UPDATE_HDR *lsup = &pkt->ospfh_un.ls_update;
	    union LSA_PTR adv;
	    u_int32 i = ntohl(lsup->adv_cnt);

	    trace_only_tf(ospf.trace_options,
			  0,
			  ("%s Advertisement count: %-4d",
			   prefix,
			   ntohl(lsup->adv_cnt)));
	    for (adv.rtr = (struct RTR_LA_HDR *) &lsup->adv.rtr;
		 i && len;
		 i--,
		 len -= adv_len,
		 adv.rtr = (struct RTR_LA_HDR *) ((long) adv.rtr + adv_len)) {
		adv_len = ospf_log_lsa(adv, prefix);
	    }
	}
	break;

    case OSPF_PKT_ACK:
        {
	    struct LS_ACK_HDR *ls_ack = &pkt->ospfh_un.ls_ack;
	    struct LS_HDR *ack;
 
	    for( ack = &ls_ack->ack_piece, len -= OSPF_HDR_SIZE;
		len > 0;
		len -= ACK_PIECE_SIZE, ack++ ) {

		ospf_log_ls_hdr(ack,
				prefix,
				ntohs(ack->ls_age),
				(time_t) 0);
	    }
	}
	break;
    }

    trace_only_tf(ospf.trace_options,
		  0,
		  (NULL));
}


void
ospf_trace_build  __PF4(from, struct AREA *,
			to, struct AREA *,
			lsa, union LSA_PTR,
			freed, int)
{
    const char *prefix = freed ? "OSPF LSA FREE" : "OSPF LSA BUILD";

    switch (lsa.rtr->ls_hdr.ls_type) {
    case LS_STUB:
    case LS_RTR:
    case LS_NET:
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s Area: %A",
		       prefix,
		       sockbuild_in(0, from->area_id)));
	break;

    case LS_SUM_NET:
    case LS_SUM_ASB:
	trace_only_tf(ospf.trace_options,
		      0,
		      ("%s From Area: %A  To Area: %A",
		       prefix,
		       sockbuild_in(0, from->area_id),
		       sockbuild_in(0, to->area_id)));
	break;
	
    case LS_ASE:
	break;

    case LS_GM:
	break;
	
    case LS_NSSA:
	break;
	
    default:
	assert(FALSE);
	break;
    }

    (void) ospf_log_lsa(lsa, prefix);

    trace_only_tf(ospf.trace_options,
		  0,
		  (NULL));
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
