/*
 * $Id: slsp_io.c,v 1.9.2.2 1994/05/23 20:48:26 jch Exp $
 */

/* %(Copyright.header) */

/*
 * slsp_io.c - routines dealing with slsp input and output
 */

#include "include.h"
#include "inet.h"
#include "slsp_proto.h"
#include "slsp.h"
#include "slsp_var.h"

/*
 * We only open one socket to receive SLSP packets since there doesn't
 * seem to be a way to bind multiple sockets which would be useful.
 * We demultiplex incoming packets to their corresponding neighbour
 * structures based on the address they came from and deliver this
 * to the packet processing code.
 *
 * To do the demultiplexing we build a patricia tree of the addresses
 * we expect to hear from (or have heard from), with pointers to the
 * appropriate neighbour structure.  A lookup is done on each incoming
 * packet to find the appropriate neighbour structure.  If no structure
 * is found we search the configuration to find the instance/interface
 * this guy might belong.  If no configuration information is found
 * we note this in the patricia tree so that future packets from this
 * neighbour can be ignored.
 */
typedef struct _slsp_demux {
    struct _slsp_demux *slsp_demux_left;
    struct _slsp_demux *slsp_demux_right;
    union {
	slsp_neighbour *slsp_demux_X_nbr;
	struct _slsp_demux *slsp_demux_X_next;
    } slsp_demux_X;
#define	slsp_demux_nbr	slsp_demux_X.slsp_demux_X_nbr
#define	slsp_demux_next	slsp_demux_X.slsp_demux_X_next
    u_int32 slsp_demux_mask;		/* Bit to test */
    u_int32 slsp_demux_key;		/* Address, in host byte order */
} slsp_demux;


/*
 * Macro to find nodes in the demux tree
 */
#define	SLSP_DEMUX_FIND(addr, dp) \
    do { \
	register u_int32 Xkey = ntohl(sock2ip((addr))); \
	register slsp_demux *Xdp = slsp_io_demux; \
	register u_int32 Xmask = SLSP_NOMASK; \
	if (Xdp) { \
	    do { \
		Xmask = Xdp->slsp_demux_mask; \
		if (Xkey & Xmask) { \
		    Xdp = Xdp->slsp_demux_right; \
		} else { \
		    Xdp = Xdp->slsp_demux_left; \
		} \
	    } while (Xmask > Xdp->slsp_demux_mask); \
	    if (Xdp->slsp_demux_key != Xkey) { \
		Xdp = (slsp_demux *) 0; \
	    } \
	} \
	(dp) = Xdp; \
    } while (0)


/*
 * Demux allocation
 */
static block_t slsp_io_demux_index = (block_t) 0;

#define	SLSP_DEMUX_ALLOC()	(task_block_alloc(slsp_io_demux_index))

#define	SLSP_DEMUX_FREE(dp) \
    task_block_free(slsp_io_demux_index, (void_t)(dp))

#define	SLSP_DEMUX_INIT() \
    (slsp_io_demux_index = task_block_init(sizeof(slsp_demux), "slsp_demux"))

#define	SLSP_DEMUX_GET(dp) \
    do { \
	if (!slsp_io_demux_index) { \
	    SLSP_DEMUX_INIT(); \
	} \
	(dp) = SLSP_DEMUX_ALLOC(); \
    } while (0)

static slsp_demux *slsp_io_demux = (slsp_demux *) 0;
static int slsp_io_n_demux = 0;		/* total number of nodes in tree */
static int slsp_io_n_demux_ignore= 0;	/* number of "ignore" nodes in tree */

static task *slsp_io_task = (task *) 0;	/* initialized when I/O is initiated */
static int slsp_io_maxpacket;		/* maximum packet size we can receive */
static int slsp_io_terminated = 0;	/* set to 1 when termination called */
static task_timer *slsp_io_reconfig_timer = (task_timer *) 0;

#define	SLSP_IO_RECONFIG_INTERVAL	((time_t) 14)

/*
 * Used for packet classification
 */
#define	SLSP_CLASS_PTP		0
#define	SLSP_CLASS_BCAST	1
#define	SLSP_CLASS_DB		2

#define	SLSP_IO_NONBR		0
#define	SLSP_IO_NBR		1
#define	SLSP_IO_NEWNBR		2
#define	SLSP_IO_OUROWN		3


/*
 * slsp_pktdump - print the raw contents of an SLSP packet to the trace file.
 */
void
slsp_pktdump __PF4(trp, trace *,
		   comment, const char *,
		   pkt, byte *,
		   pktlen, size_t)
{
    register byte *cp;
    register size_t maxdump;
    register size_t l;
    register size_t i;

    cp = pkt;
    maxdump = MIN(pktlen, SLSP_PKTDUMP_MAX);

    if (maxdump == 0) {
	trace_only_tf(trp,
		      0,
		      ("%szero length packet!",
		       comment));
    } else {
        l = 0;
	do {
	    i = maxdump - l;
	    if (i > SLSP_PKTDUMP_LINE) {
		i = SLSP_PKTDUMP_LINE;
	    }
            tracef("%soctets %d-%d of %d:",
		   comment,
		   l,
		   l + i - 1,
		   pktlen);
	    l += i;
	    while (i-- > 0) {
		tracef(" %02x",
		       (unsigned int)*cp++);
	    }
	    trace_only_tf(trp,
			  0,
			  (NULL));
	} while (l < maxdump);
    }
}


/*
 * slsp_trace - print the contents of an SLSP packet to the trace file
 */
static void
slsp_trace __PF6(trp, trace *,
		 comment, const char *,
		 fromaddr, sockaddr_un *,
		 toaddr, sockaddr_un *,
		 pkt, byte *,
		 pktlen, size_t)
{
    register byte *cp;

    /*
     * Catch the trivial case, a zero length packet.
     */
    if (pktlen == 0) {
	trace_only_tf(trp,
		      TRC_NL_AFTER,
		      ("%s%A->%A: zero length packet",
		       comment,
		       fromaddr,
		       toaddr));
	return;
    }

    /*
     * Fetch the start of the packet.  If it is a p2p hello process this
     * now.
     */
    cp = pkt;
    if (*cp == SLSP_HELLO_PROTOCOL) {
	time_t holdtime;
	as_t as;
	sockaddr_un tmp_addr;

	if (!TRACE_TF(trp, TR_SLSP_HELLO)) {
	    return;
	}

	trace_only_tf(trp,
		      TRC_NL_BEFORE,
		      ("%sPoint-to-Point Hello %A->%A",
		       comment,
		       fromaddr,
		       toaddr));
	if (pktlen != SLSP_HELLO_LEN) {
	    trace_only_tf(trp,
			  0,
			  ("%s***Length error in Point-to-Point Hello, %d should be %d",
			   comment,
			   pktlen,
			   SLSP_HELLO_LEN));
	    goto pktdump;
	}

	if (!SLSP_CHK_HELLO(cp)) {
	    trace_only_tf(trp,
			  0,
			  ("%s***Constant field check failed for Point-to-Point Hello",
			   comment));
	    goto pktdump;
	}

	sockclear_in(&tmp_addr);
	SLSP_GET_HELLO(holdtime, as, &tmp_addr, cp);
	trace_only_tf(trp,
		      0,
		      ("%sPoint-to-Point Hello holdtime %lu as %u node ID %#A",
		       comment,
		       holdtime,
		       as,
		       &tmp_addr));
    } else if (*cp == SLSP_LEADER_PROTOCOL) {
	int type;
	int fixedlen;

	/*
	 * It is one of the packet types with a leader.  Do basic sanity
	 * checking.
	 */
	if (pktlen < SLSP_SHORT_LEADER_LEN) {
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%s***%A->%A: packet length (%d) less than leader minimum (%d)",
			   comment,
			   fromaddr,
			   toaddr,
			   pktlen,
			   SLSP_LEADER_LEN));
	    goto pktdump;
	}
	if (!SLSP_CHK_SHORT_LEADER(cp)) {
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%s***%A->%A: packet leader constant field check failed",
			   comment,
			   fromaddr,
			   toaddr));
	    goto pktdump;
	}

	type = SLSP_GET_LEADER_TYPE(cp);
	fixedlen = SLSP_GET_LEADER_LENGTH(cp);
	if (fixedlen > pktlen) {
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%s***%A->%A: received packet length (%d) less than indicated (%d)",
			   comment,
			   fromaddr,
			   toaddr,
			   pktlen,
			   fixedlen));
	    goto pktdump;
	}

	/*
	 * This should probably be a switch, but the number of types
	 * is few and sparse
	 */
	if (type == SLSP_PTP_IHU_TYPE) {
	    if (!TRACE_TF(trp, TR_SLSP_HELLO)) {
		return;
	    }

	    if (fixedlen != SLSP_PTP_IHU_LEN) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***Point-to-Point IHU %A->%A: length %d incorrect (should be %d, packet %d)",
			       comment,
			       fromaddr,
			       toaddr,
			       fixedlen,
			       SLSP_PTP_IHU_LEN,
			       pktlen));
		goto pktdump;
	    }
	    if (pktlen != SLSP_PTP_IHU_LEN) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***Point-to-Point IHU %A->%A: packet length (%d) too long (> %d)",
			       comment,
			       fromaddr,
			       toaddr,
			       pktlen,
			       SLSP_PTP_IHU_LEN));
		goto pktdump;
	    }
	    if (!SLSP_CHK_PTP_IHU(cp)) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***Point-to-Point IHU %A->%A: router type incorrect",
			       comment,
			       fromaddr,
			       toaddr));
		goto pktdump;
	    }
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%sPoint-to-Point IHU %A->%A",
			   comment,
			   fromaddr,
			   toaddr));
	} else if (type == SLSP_BCAST_IHU_TYPE) {
	    time_t holdtime;
	    int priority;
	    int tmp, nrtrs;
	    sockaddr_un node_id;
	    sockaddr_un lan_id;

	    if (!TRACE_TF(trp, TR_SLSP_HELLO)) {
		return;
	    }

	    if (fixedlen != SLSP_BCAST_IHU_FIXED_LEN) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***Broadcast IHU %A->%A: fixed length %d incorrect (should be %d, packet %d)",
			       comment,
			       fromaddr,
			       toaddr,
			       fixedlen,
			       SLSP_BCAST_IHU_FIXED_LEN,
			       pktlen));
		goto pktdump;
	    }
	    if (pktlen < SLSP_BCAST_IHU_MIN_LEN) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***Broadcast IHU %A->%A: packet length %d too short, minimum is %d",
			       comment,
			       fromaddr,
			       toaddr,
			       pktlen,
			       SLSP_BCAST_IHU_MIN_LEN));
		goto pktdump;
	    }
	    if (!SLSP_CHK_BCAST_IHU(cp)) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***Broadcast IHU %A->%A: fixed field value check failed",
			       comment,
			       fromaddr,
			       toaddr));
		goto pktdump;
	    }
	    sockclear_in(&node_id);
	    sockclear_in(&lan_id);
	    SLSP_GET_BCAST_IHU(priority, holdtime, &node_id, &lan_id, cp);

	    SLSP_GET_BCAST_N_AREAS(tmp, cp);
	    if (tmp != 0) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***Broadcast IHU %A->%A: area count %d is nonzero!",
			       comment,
			       fromaddr,
			       toaddr,
			       tmp));
		goto pktdump;
	    }

	    SLSP_GET_BCAST_N_RTRS(nrtrs, cp);
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%sBroadcast IHU %A->%A priority %d holdtime %d node ID %#A lan ID %#A rtrs %d",
			   comment,
			   fromaddr,
			   toaddr,
			   priority,
			   holdtime,
			   &node_id,
			   &lan_id,
			   nrtrs));

	    if ((nrtrs * SLSP_BCAST_IHU_RTR_LEN)
	      > (pktlen - SLSP_BCAST_IHU_MIN_LEN)) {
		trace_only_tf(trp,
			      0,
			      ("%s***Broadcast IHU %A->%A: packet length %d too small for %d routers",
			       comment,
			       fromaddr,
			       toaddr,
			       pktlen,
			       nrtrs));
		goto pktdump;
	    }

	    if (TRACE_TF(trp, TR_SLSP_DETAIL_HELLO)) {
		register int i;
		for (i = 0; i < nrtrs; i++) {
		    holdtime = ((*cp) << 8) + (*(cp + 1));
		    SLSP_GET_BCAST_RTR(&node_id, tmp, cp);
		    if ((i & 0x3) == 0) {
			if (holdtime != 0) {
			    tracef("%s    !%04x! ",
				comment,
				holdtime);
			} else {
			    tracef("%s    ",
				comment);
			}
			tracef("%#A (%c %d)",
			    &node_id,
			    ((tmp & SLSP_BCAST_CONFIG_FLAG) ? 'C' : 'U'),
			    (tmp & SLSP_BCAST_PRIORITY_MASK));
		    } else if (holdtime != 0) {
			tracef(" !%04x! %#A (%c %d)",
			    holdtime,
			    &node_id,
			    ((tmp & SLSP_BCAST_CONFIG_FLAG) ? 'C' : 'U'),
			    (tmp & SLSP_BCAST_PRIORITY_MASK));
		    } else {
			tracef("%#A (%c %d)",
			    &node_id,
			    ((tmp & SLSP_BCAST_CONFIG_FLAG) ? 'C' : 'U'),
			    (tmp & SLSP_BCAST_PRIORITY_MASK));
		    }
		    if ((i & 0x3) == 0x3) {
			trace_only_tf(trp,
				      0,
				      (NULL));
		    }
		}
		if ((i & 0x3) != 0) {
		    trace_only_tf(trp,
				  0,
				  (NULL));
		}

		if (cp < (pkt + pktlen)) {
		    trace_only_tf(trp,
				  0,
				  ("%s***Broadcast IHU %A->%A: %d bytes remain at end of packet",
				   comment,
				   fromaddr,
				   toaddr,
				   (pktlen - (cp - pkt))));
		}
	    }
	} else if (type == SLSP_LSP_TYPE) {
	    byte *pp;
	    int i;
	    int nas, nlink, nasp, nlinkp, u;
	    int rttype;
	    u_int32 length = 0;
	    int lifetime;
	    sockaddr_un tmp_addr;
	    u_int32 seqnum;
	    u_int16 cksum;
	    char buf2[36];

	    if (!TRACE_TF(trp, TR_SLSP_LSP)) {
		return;
	    }

	    if (fixedlen != SLSP_LSP_FIXED_LEN) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***LSP %A->%A: fixed length %d incorrect (should be %d, packet %d)",
			       comment,
			       fromaddr,
			       toaddr,
			       fixedlen,
			       SLSP_LSP_FIXED_LEN,
			       pktlen));
		goto pktdump;
	    }
	    if (pktlen < SLSP_LSP_MIN_LEN) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***LSP %A->%A: packet length %d too short, minimum is %d",
			       comment,
			       fromaddr,
			       toaddr,
			       pktlen,
			       SLSP_LSP_MIN_LEN));
		goto pktdump;
	    }
	    if (!SLSP_CHK_LSP(cp)) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***LSP %A->%A: fixed field value check failed",
			       comment,
			       fromaddr,
			       toaddr));
		goto pktdump;
	    }

	    sockclear_in(&tmp_addr);
	    SLSP_GET_LSP(length, lifetime, &tmp_addr, rttype, seqnum, cksum, cp);

	    if (length > (u_int32)pktlen) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***LSP %A->%A: packet length %u exceeds received packet length %d",
			       comment,
			       fromaddr,
			       toaddr,
			       length,
			       pktlen));
		goto pktdump;
	    }
	    buf2[0] = 0;
	    if (length != (u_int32)pktlen) {
		(void) sprintf(buf2, " pktlen %d", pktlen);
	    }
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%sLSP %A->%A node %#A length %u lifetime %u rttype %d seqnum %08x cksum %04x%s",
			   comment,
			   fromaddr,
			   toaddr,
			   &tmp_addr,
			   length,
			   lifetime,
			   rttype,
			   seqnum,
			   cksum,
			   buf2));

	    /*
	     * Scan through and count the as's and links.
	     */
	    i = (int)(length - SLSP_LSP_FIXED_LEN);
	    pp = cp;
	    u = nas = nasp = nlink = nlinkp = 0;
	    while (i >= 2) {
		i -= 2;
		if (*pp == SLSP_LSP_CODE_AS) {
		    int aslen = (int)*(++pp);
		    pp++;
		    if (aslen > i) {
			trace_only_tf(trp,
				      0,
				      ("%s***LSP %A->%A: AS length %d exceeds remaining packet length %d",
				       comment,
				       fromaddr,
				       toaddr,
				       aslen,
				       i));
			goto pktdump;
		    }
		    pp += aslen;
		    i -= aslen;
		    nasp++;
		    nas += aslen / SLSP_LSP_AS_LEN;
		    if ((aslen % SLSP_LSP_AS_LEN) != 0) {
			trace_only_tf(trp,
				      0,
				      ("%s***LSP %A->%A: AS length %d not even multple of packet AS size %d",
				       comment,
				       fromaddr,
				       toaddr,
				       aslen,
				       SLSP_LSP_AS_LEN));
		    }
		} else if (*pp == SLSP_LSP_CODE_LINKS) {
		    int lnklen = (int)*(++pp);
		    pp++;
		    if (lnklen > i) {
			trace_only_tf(trp,
				      0,
				      ("%s***LSP %A->%A: links length %d exceeds remaining packet length %d",
				       comment,
				       fromaddr,
				       toaddr,
				       lnklen,
				       i));
			goto pktdump;
		    }
		    pp += lnklen;
		    i -= lnklen;
		    nlinkp++;
		    lnklen -= 2;
		    nlink += lnklen / SLSP_LSP_LINK_ID_LEN;
		    if ((lnklen % SLSP_LSP_LINK_ID_LEN) != 0) {
			trace_only_tf(trp,
				      0,
				      ("%s***LSP %A->%A: links length %d not even multple of packet link ID size %d",
				       comment,
				       fromaddr,
				       toaddr,
				       lnklen,
				       SLSP_LSP_LINK_ID_LEN));
		    }
		} else {
		    trace_only_tf(trp,
				  0,
				  ("%s***LSP %A->%A: unknown LSP payload code %d length %d",
				   comment,
				   fromaddr,
				   toaddr,
				   *pp,
				   *(pp + 1)));
		    if (*(pp + 1) > i) {
			trace_only_tf(trp,
				      0,
				      ("%s***LSP %A->%A: unknown LSP payload size %d exceeds remaining packet size %d",
				       comment,
				       fromaddr,
				       toaddr,
				       *(pp + 1),
				       i));
			goto pktdump;
		    }
		    u++;
		    i -= *(pp + 1);
		    pp += *(pp + 1) + 2;
		}
	    }
	    if (i > 0) {
		trace_only_tf(trp,
			      0,
			      ("%s***LSP %A->%A: one byte of slop found in payload",
			       comment,
			       fromaddr,
			       toaddr));
	    }

	    trace_only_tf(trp,
			  0,
			  ("%sLSP %A->%A AS payloads %d ASes %d link payloads %d links %d",
			   comment,
			   fromaddr,
			   toaddr,
			   nasp,
			   nas,
			   nlinkp,
			   nlink));

	    if (TRACE_TF(trp, TR_SLSP_DETAIL_LSP)) {
		length -= SLSP_LSP_FIXED_LEN;
		while (length >= 2) {
		    i = *(cp + 1);
		    length -= 2 + (u_int32)i;
		    if (*cp == SLSP_LSP_CODE_AS) {
			u = i % SLSP_LSP_AS_LEN;
			if (u == 0) {
			    buf2[0] = 0;
			} else {
			    (void) sprintf(buf2,
				", %d byte%s slop",
				u,
				((u > 1) ? "s" : ""));
			}
			u = i / SLSP_LSP_AS_LEN;
			trace_only_tf(trp,
				      0,
				      ("%s    AS list length %d (%d AS%s%s)",
				       comment,
				       (i + 2),
				       u,
				       ((u == 1) ? "" : "es"),
				       buf2));
			cp += 2;

			for (u = 0; i >= SLSP_LSP_AS_LEN;
			  u++, i -= SLSP_LSP_AS_LEN) {
			    if ((u & 0x7) == 0) {
				if (u != 0) {
				    trace_only_tf(trp,
						  0,
						  (NULL));
				}
				tracef("%s        ", comment);
			    } else {
				tracef(", ");
			    }
			    nlinkp = !SLSP_CHK_LSP_AS(cp);
			    SLSP_GET_LSP_AS(nasp, cp);
			    tracef("%u%s", nasp, (nlinkp ? "!" : ""));
			}
			if (u > 0) {
			    trace_only_tf(trp,
					  0,
					  (NULL));
			}
			cp += i;
		    } else if (*cp == SLSP_LSP_CODE_LINKS) {
			int cost;

			cp += 2;
			if (i < 2) {
			    trace_only_tf(trp,
					  0,
					  ("%s    Null links list%s",
					   comment,
					   (i ? " (one slop byte)" : "")));
			    cp += i;
			    continue;
			}

			i -= 2;
			nasp = !SLSP_CHK_LINK_LEADER(cp);
			SLSP_GET_LINK_COST(cost, cp);
			u = i % SLSP_LSP_LINK_ID_LEN;
			if (u == 0) {
			    buf2[0] = 0;
			} else {
			    (void) sprintf(buf2,
				", %d byte%s slop",
				u,
				((u > 1) ? "s" : ""));
			}
			u = i / SLSP_LSP_LINK_ID_LEN;
			trace_only_tf(trp,
				      0,
				      ("%s    Links list cost %d length %d (%d link%s%s)",
				       comment,
				       cost,
				       (i + 4),
				       u,
				       ((u == 1) ? "" : "s"),
				       buf2));

			for (u = 0; i >= SLSP_LSP_LINK_ID_LEN;
			  u++, i -= SLSP_LSP_LINK_ID_LEN) {
			    if ((u & 0x7) == 0) {
				if (u != 0) {
				    trace_only_tf(trp,
						  0,
						  (NULL));
				}
				tracef("%s        ", comment);
			    } else {
				tracef(", ");
			    }
			    nlinkp = !SLSP_CHK_LINK_ID(cp);
			    SLSP_GET_LINK_ID(&tmp_addr, cp);
			    tracef("%#A%s",
				&tmp_addr,
				(nlinkp ? "!" : ""));
			}
			if (u > 0) {
			    trace_only_tf(trp,
					  0,
					  (NULL));
			}
			cp += i;
		    } else {
			trace_only_tf(trp,
				      0,
				      ("%s    Unknown payload code %d length %d",
				       comment,
				       *cp,
				       *(cp + 1)));
			cp += (2 + i);
		    }
		}
		if (length > 0) {
		    trace_only_tf(trp,
				  0,
				  ("%s    One slop byte",
				   comment));
		}
	    }
	} else if (type == SLSP_SEQ_TYPE) {
	    sockaddr_un tmp_addr;
	    int stype;
	    u_int32 length;
	    u_int32 seqnum;
	    u_int16 cksum;
	    int age;
	    int entries;
	    char buf1[30];
	    char buf2[30];

	    if (!TRACE_TF(trp, TR_SLSP_LSP)) {
		return;
	    }

	    if (fixedlen != SLSP_SEQ_FIXED_LEN) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***SeqNumPkt %A->%A: fixed length %d incorrect (should be %d, packet %d)",
			       comment,
			       fromaddr,
			       toaddr,
			       fixedlen,
			       SLSP_SEQ_FIXED_LEN,
			       pktlen));
		goto pktdump;
	    }
	    if (pktlen < SLSP_SEQ_FIXED_LEN) {
		    trace_only_tf(trp,
				  TRC_NL_BEFORE,
				  ("%s***SeqNumPkt %A->%A: packet length %d too short, minimum is %d",
				   comment,
				   fromaddr,
				   toaddr,
				   pktlen,
				   SLSP_SEQ_FIXED_LEN));
		goto pktdump;
	    }
	    if (!SLSP_CHK_SEQ(cp)) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***SeqNumPkt %A->%A: fixed field value check failed",
			       comment,
			       fromaddr,
			       toaddr));
		goto pktdump;
	    }

	    sockclear_in(&tmp_addr);
	    SLSP_GET_SEQ(&tmp_addr, stype, length, entries, cp);

	    if (length > (u_int32) pktlen) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***SeqNumPkt %A->%A: packet length %u exceeds received packet length %d",
			       comment,
			       fromaddr,
			       toaddr,
			       length,
			       pktlen));
		goto pktdump;
	    }
	    buf1[0] = 0;
	    if (length != (u_int32)pktlen) {
		(void) sprintf(buf1, " pktlen %d", pktlen);
	    }
	    switch (stype) {
	    case SLSP_SEQ_FULL:
		(void) strcpy(buf2, "full");
		break;
	    case SLSP_SEQ_PARTIAL:
		(void) strcpy(buf2, "partial");
		break;
	    default:
		(void) sprintf(buf2, "unknown type 0x%02x", stype);
		break;
	    }
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%sSeqNumPkt %A->%A node %#A %s length %u%s entries %u",
			   comment,
			   fromaddr,
			   toaddr,
			   &tmp_addr,
			   buf2,
			   length,
			   buf1,
			   entries));
	    /*
	     * Do the entries now
	     */
	    if (TRACE_TF(trp, TR_SLSP_DETAIL_LSP)) {
		length -= SLSP_SEQ_FIXED_LEN;
		while (length && entries) {
		    byte *cptmp = cp;

		    if (length < SLSP_SEQ_ENT_LEN) {
			trace_only_tf(trp,
				      0,
				      ("%s***SeqNumPkt %A->%A remaining length %u too small, %u entr%s to go",
				       comment,
				       fromaddr,
				       toaddr,
				       length,
				       entries,
				       ((entries == 1) ? "y" : "ies")));
			goto pktdump;
		    }
		    SLSP_GET_SEQ_ENT(stype, &tmp_addr, seqnum, age, cksum, cp);
		    switch (stype) {
		    case SLSP_SEQ_ENT_TYPE_ROUTER:
			(void) strcpy(buf1, "router");
			break;

		    case SLSP_SEQ_ENT_TYPE_EXT:
			(void) strcpy(buf1, "external");
			break;

		    default:
			(void) sprintf(buf1, "unknown node type 0x%02x", stype);
			break;
		    }
		    trace_only_tf(trp,
				  0,
				  ("%s    %s node %A seqnum %08x age %u cksum %04x%s",
				   comment,
				   buf1,
				   &tmp_addr,
				   seqnum,
				   age,
				   cksum,
				   (SLSP_CHK_SEQ_ENT(cptmp)
				     ? "" : " (fixed fields screwed)")));
		    length -= SLSP_SEQ_ENT_LEN;
		    entries--;
		}
		if (length) {
		    trace_only_tf(trp,
				  0,
				  ("%s***SeqNumPkt %A->%A all entries processed, %u octet%s left",
				   comment,
				   fromaddr,
				   toaddr,
				   length,
				   ((length == 1) ? "" : "s")));
		} else if (entries) {
		    trace_only_tf(trp,
				  0,
				  ("%s***SeqNumPkt %A->%A processed entire packet, %u entr%s left",
				   comment,
				   fromaddr,
				   toaddr,
				   entries,
				   ((entries == 1) ? "y" : "ies")));
		}
	    }
	} else if (type == SLSP_EXT_TYPE) {
	    sockaddr_un tmp_addr;
	    int rttype;
	    u_int32 length;
	    u_int32 seqnum;
	    u_int16 cksum;
	    int life;
	    char buf1[30];

	    if (!TRACE_TF(trp, TR_SLSP_LSP)) {
		return;
	    }

	    if (fixedlen != SLSP_EXT_FIXED_LEN) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***ExtLSP %A->%A: fixed length %d incorrect (should be %d, packet %d)",
			       comment,
			       fromaddr,
			       toaddr,
			       fixedlen,
			       SLSP_EXT_FIXED_LEN,
			       pktlen));
		goto pktdump;
	    }
	    if (pktlen < SLSP_EXT_FIXED_LEN) {
		    trace_only_tf(trp,
				  TRC_NL_BEFORE,
				  ("%s***ExtLSP %A->%A: packet length %d too short, minimum is %d",
				   comment,
				   fromaddr,
				   toaddr,
				   pktlen,
				   SLSP_EXT_FIXED_LEN));
		goto pktdump;
	    }
	    if (!SLSP_CHK_EXT(cp)) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***ExtLSP %A->%A: fixed field value check failed",
			       comment,
			       fromaddr,
			       toaddr));
		goto pktdump;
	    }

	    sockclear_in(&tmp_addr);
	    SLSP_GET_EXT(length, life, &tmp_addr, rttype, seqnum, cksum, cp);

	    if (length > (u_int32) pktlen) {
		trace_only_tf(trp,
			      TRC_NL_BEFORE,
			      ("%s***ExtLSP %A->%A: packet length %u exceeds received packet length %d",
			       comment,
			       fromaddr,
			       toaddr,
			       length,
			       pktlen));
		goto pktdump;
	    }
	    buf1[0] = 0;
	    if (length != (u_int32)pktlen) {
		(void) sprintf(buf1, " pktlen %d", pktlen);
	    }
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%sExtLSP %A->%A node %#A length %u lifetime %u rttype %d seqnum %08x cksum %04x%s",
			   comment,
			   fromaddr,
			   toaddr,
			   &tmp_addr,
			   length,
			   life,
			   rttype,
			   seqnum,
			   cksum,
			   buf1));
	    /*
	     * If there is payload data, mention this.
	     */
	    if (length != SLSP_EXT_FIXED_LEN) {
		trace_only_tf(trp,
			      0,
			      ("%sExtLSP %A->%A node %#A has %u octet%s of payload which I can't print!",
			       comment,
			       fromaddr,
			       toaddr,
			       &tmp_addr,
			       (length - SLSP_EXT_FIXED_LEN),
			       (((length - SLSP_EXT_FIXED_LEN) == 1)
				 ? "" : "s")));
	    }
	} else {
	    trace_only_tf(trp,
			  TRC_NL_BEFORE,
			  ("%s***%A->%A: Unknown SLSP packet type %d fixed length %d packet length %d",
			   comment,
			   fromaddr,
			   toaddr,
			   type,
			   fixedlen,
			   pktlen));
	    goto pktdump;
	}
    } else {
	trace_only_tf(trp,
		      TRC_NL_BEFORE,
		      ("%s***%A->%A: Unknown SLSP protocol type %u packet length %d",
		       comment,
		       fromaddr,
		       toaddr,
		       *cp,
		       pktlen));
	goto pktdump;
    }

    /*
     * All done, return
     */
    trace_only_tf(trp,
		  0,
		  (NULL));
    return;

pktdump:
    slsp_pktdump(trp, comment, pkt, pktlen);
    trace_only_tf(trp,
		  0,
		  (NULL));
    return;
}


/*
 * slsp_io_stop - close the SLSP socket and delete the I/O task
 */
void
slsp_io_stop __PF0(void)
{
    if (!slsp_io_task) {
	return;
    }
    assert(!slsp_io_demux);
    task_close(slsp_io_task);
    task_delete(slsp_io_task);
    slsp_io_task = (task *) 0;
#ifdef	PROTO_SNMP
    slsp_init_mib(FALSE);
#endif	/* PROTO_SNMP */
}


/*
 * slsp_io_terminate - terminate slsp I/O for gated shutdown
 */
static void
slsp_io_terminate __PF1(tp, task *)
{
    if (slsp_io_demux) {
	slsp_io_terminated = 1;
    } else {
	slsp_io_stop();
    }
}


/*
 * slsp_demux_insert - add an address to the demux tree.  Note that
 *		   found_dp points to the node that was "found" when the
 *		   tree was searched for the address/neighbour we are adding.
 *		   If it is NULL we do the search on our own.
 */
static void
slsp_demux_insert __PF3(found_dp, slsp_demux *,
			demux_addr, sockaddr_un *,
			demux_nbr, slsp_neighbour *)
{
    register slsp_demux *dp;
    register slsp_demux *dprev, *dcurr;
    register u_int32 key;
    register u_int32 mask, omask;

    /*
     * Fetch the key.  This is the demux address in host byte order.
     */
    key = ntohl(sock2ip(demux_addr));

    /*
     * Fetch a new demux structure and initialize it
     */
    SLSP_DEMUX_GET(dp);
    dp->slsp_demux_key = key;
    dp->slsp_demux_nbr = demux_nbr;
    slsp_io_n_demux++;
    if (!demux_nbr) {
        slsp_io_n_demux_ignore++;
    }

    /*
     * If he didn't include a "found" demux node, but there are nodes
     * to "find", "find" it.  If there are no nodes to find then
     * this is the first node in the tree and just needs to get
     * initialized appropriately.
     */
    if (!found_dp) {
	if (!(dcurr = slsp_io_demux)) {
	    slsp_io_demux = dp->slsp_demux_right = dp->slsp_demux_left = dp;
	    dp->slsp_demux_mask = SLSP_NOMASK;
	    return;
        }
	mask = SLSP_NOMASK;
	while (mask > dcurr->slsp_demux_mask) {
	    mask = dcurr->slsp_demux_mask;
	    if (key & mask) {
		dcurr = dcurr->slsp_demux_right;
	    } else {
		dcurr = dcurr->slsp_demux_left;
	    }
	}
	found_dp = dcurr;
    }

    /*
     * Here we have an insertion to do.  Figure out the first
     * (most significant) bit which differs from the "found" node.  This
     * tells us the bit we need to test in the node we insert.
     *
     * Do a binary search to find the byte the first bit is in, then use
     * the table to form the mask.
     */
    mask = key ^ found_dp->slsp_demux_key;
    if (mask >= 0x10000) {
	if (mask >= 0x1000000) {
	    mask = ((u_int32)(slsp_bit_table[mask >> 24])) << 24;
	} else {
	    mask = ((u_int32)(slsp_bit_table[mask >> 16])) << 16;
	}
    } else {
	if (mask >= 0x100) {
	    mask = ((u_int32)(slsp_bit_table[mask >> 8])) << 8;
	} else {
	    mask = (u_int32)(slsp_bit_table[mask]);
	}
    }

    /*
     * XXX Sanity.  This could only happen if a node with the same key
     * is in the tree already, which should never happen.
     */
    assert(mask != 0);
    dp->slsp_demux_mask = mask;

    /*
     * Now we locate where this guy needs to be inserted.  Search down
     * the tree until we find either an end node (i.e. an upward link)
     * or a node with a mask smaller than ours.  We insert our node
     * above this (watch for the case where the node we find is the
     * current root node), making one of the pointers an uplink pointing
     * at the node itself.
     */
    dprev = (slsp_demux *) 0;
    dcurr = slsp_io_demux;
    omask = SLSP_NOMASK;
    while (omask > dcurr->slsp_demux_mask) {
	omask = dcurr->slsp_demux_mask;
	if (mask >= omask) {
	    break;
	}
	dprev = dcurr;
	if (key & omask) {
	    dcurr = dcurr->slsp_demux_right;
	} else {
	    dcurr = dcurr->slsp_demux_left;
	}
    }
    assert(mask != dcurr->slsp_demux_mask);

    /*
     * Point the new node at the current node, and at itself.  The
     * pointer to the current node in the previous node is changed to
     * point at the new node.  Simple(?).
     */
    if (key & mask) {
	dp->slsp_demux_right = dp;
	dp->slsp_demux_left = dcurr;
    } else {
	dp->slsp_demux_right = dcurr;
	dp->slsp_demux_left = dp;
    }

    if (!dprev) {
	/* New root node */
	slsp_io_demux = dp;
    } else if (dprev->slsp_demux_right == dcurr) {
	dprev->slsp_demux_right = dp;
    } else {
	dprev->slsp_demux_left = dp;
    }
    /* done */
}


/*
 * slsp_demux_remove - remove a node from the demux tree.
 */
static void
slsp_demux_remove __PF1(remove_dp, slsp_demux *)
{
    register slsp_demux *dp = remove_dp;
    register slsp_demux *tmp;
    register slsp_demux *dprev, *dcurr;
    register u_int32 key;
    slsp_demux *intprev;

    /*
     * Detect the trivial case, that there is only one guy in the tree,
     * and fix this up.
     */
    dcurr = slsp_io_demux;
    if (dcurr->slsp_demux_mask == SLSP_NOMASK) {
	assert(dcurr == dp);
	task_block_free(slsp_io_demux_index, (void *)dp);
	slsp_io_demux = (slsp_demux *) 0;
	if (slsp_io_terminated) {
	    slsp_io_stop();
	}
	return;
    }

    /*
     * We will be in the tree twice, once as an internal node and once
     * as an external (or up-)node.  Find the guy who points to our man
     * in the tree in both cases, and the guy who points to him in the
     * latter.
     */
    dprev = (slsp_demux *) 0;
    intprev = (slsp_demux *) 0;
    key = dp->slsp_demux_key;
    for (;;) {
	if (key & dcurr->slsp_demux_mask) {
	    tmp = dcurr->slsp_demux_right;
	} else {
	    tmp = dcurr->slsp_demux_left;
	}
	if (tmp == dp) {
	    if (dp->slsp_demux_mask >= dcurr->slsp_demux_mask) {
		break;		/* got it */
	    }
	    intprev = dcurr;	/* current is in front of internal */
	} else {
	    assert(tmp->slsp_demux_mask < dcurr->slsp_demux_mask);
	}
	dprev = dcurr;
	dcurr = tmp;
    }

    /*
     * Now we have dcurr pointing at the node which contains the up-link
     * to our deleted node, nprev pointing at the node which points to
     * ncurr and intprev pointing at the guy who precedes our node in its
     * internal incarnation.
     *
     * There are several cases here.  We know the information in dcurr
     * is no longer needed, and that the sibling pointer in dcurr will
     * be moved to dprev (replacing dcurr).  If our node is the special
     * one with no internal information, we make dcurr the special.
     * If dcurr is our node (i.e. intprev == dprev) then we simply
     * point nprev at our sibling and we're done.  Otherwise we
     * additionally copy our information to dcurr, and point intprev
     * at dcurr.
     *
     * There is probably a better way to do this, but I'm an engineer,
     * not a (mere) programmer.
     */
    if (dcurr->slsp_demux_right == dp) {
	tmp = dcurr->slsp_demux_left;
    } else {
	tmp = dcurr->slsp_demux_right;
    }
    if (!dprev) {
	slsp_io_demux = tmp;
    } else if (dprev->slsp_demux_right == dcurr) {
	dprev->slsp_demux_right = tmp;
    } else {
	dprev->slsp_demux_left = tmp;
    }
    if (dcurr != dp) {
	if (dp->slsp_demux_mask == SLSP_NOMASK) {
	    dcurr->slsp_demux_mask = SLSP_NOMASK;
	    dcurr->slsp_demux_left = dcurr->slsp_demux_right = dcurr;
	} else {
	    dcurr->slsp_demux_mask = dp->slsp_demux_mask;
	    dcurr->slsp_demux_left = dp->slsp_demux_left;
	    dcurr->slsp_demux_right = dp->slsp_demux_right;
	    if (!intprev) {
		slsp_io_demux = dcurr;
	    } else if (intprev->slsp_demux_right == dp) {
		intprev->slsp_demux_right = dcurr;
	    } else {
		intprev->slsp_demux_left = dcurr;
	    }
	}
    }

    /*
     * Set the bit to 0 so we know it is deleted.
     */
    if (!(dp->slsp_demux_nbr)) {
	slsp_io_n_demux_ignore--;
    }
    slsp_io_n_demux--;
    SLSP_DEMUX_FREE(dp);
}


/*
 * slsp_demux_flush - flush all ignore entries out of the demux tree.
 *		      This is done when the interface/policy
 *		      configuration changes so we get a chance to
 *		      reevaluate whether we should be listenning to the
 *		      ignored guys or not.
 */
static void
slsp_demux_flush __PF0(void)
{
    slsp_demux *stack[sizeof(u_int32) * NBBY];
    register int i;
    register slsp_demux *dp, *dprev;
    register slsp_demux *dplist;
    register int n;
    register int doing_right;

    /*
     * If nothing to do, return
     */
    if (slsp_io_n_demux == 0) {
	return;
    }

    /*
     * Catch the case where there's only one node in the
     * tree.  Handle this separately, it's quick and simple.
     */
    dprev = slsp_io_demux;
    if (dprev->slsp_demux_mask == SLSP_NOMASK) {
	assert(!(dprev->slsp_demux_nbr));
	task_block_free(slsp_io_demux_index, (void *)dprev);
	slsp_io_demux = (slsp_demux *) 0;
	return;
    }

    /*
     * Walk the list looking for ignore entries.  Go left when possible,
     * right when not.
     */
    dplist = (slsp_demux *) 0;
    doing_right = 0;
    i = n = 0;
    for (;;) {
	if (doing_right) {
	    dp = dprev->slsp_demux_right;
	} else {
	    dp = dprev->slsp_demux_left;
	}

	if (dp->slsp_demux_mask >= dprev->slsp_demux_mask) {
	    /*
	     * End node here.  If it hasn't got a neighbour it's an
	     * ignore and we add it to the list.
	     */
	    if (!(dp->slsp_demux_nbr)) {
		dp->slsp_demux_next = dplist;
		dplist = dp;
		if (++n >= slsp_io_n_demux) {
		    /* All found */
		    break;
		}
	    }

	    if (doing_right) {
		/*
		 * Finished right hand, back up stack for another
		 * node to be checked on the right.
		 */
		assert(i != 0);
		dprev = stack[--i];
	    } else {
		/*
		 * Finished left, try right on next pass
		 */
		doing_right = 1;
	    }
	} else {
	    if (doing_right) {
		/*
		 * Node on right has children.  Step down the tree,
		 * starting on the left.  No need to stack the previous,
		 * we've already checked both children
		 */
		doing_right = 0;
	    } else {
		/*
		 * Node on left has children, stack the previous node
		 * so we check its right child later.
		 */
		stack[i++] = dprev;
	    }
	    dprev = dp;
	}
    }

    /*
     * dplist now points to the list of nodes to be flushed.  Walk
     * through removing them.  Zero the nbr pointer before calling
     * slsp_demux_remove() to get the bookkeeping right.
     */
    while (dplist) {
	dp = dplist;
	dplist = dp->slsp_demux_next;
	dp->slsp_demux_nbr = (slsp_neighbour *) 0;
	slsp_demux_remove(dp);
    }

    /*
     * All done!
     */
}


/*
 * slsp_io_add - add a neighbour structure to the demux tree so
 *		 we can catch packets to it.
 */
void
slsp_io_add __PF1(nbr, slsp_neighbour *)
{
    register slsp_demux *dp = slsp_io_demux;
    register u_int32 key = ntohl(sock2ip(nbr->slsp_nbr_addr));

    /*
     * Try to find the address in the tree
     */
    if (dp) {
	register u_int32 mask;
	do {
	    mask = dp->slsp_demux_mask;
	    if (key & mask) {
		dp = dp->slsp_demux_right;
	    } else {
		dp = dp->slsp_demux_left;
	    }
	} while (mask > dp->slsp_demux_mask);
    }

    /*
     * Put the neighbour in the tree.  He may attach to an
     * existing node, or may require a new node inserted.
     */
    if (dp && dp->slsp_demux_key == key) {
	if (dp->slsp_demux_nbr) {
	    register slsp_neighbour *tnbr = dp->slsp_demux_nbr;

	    /*
	     * Put point-to-point stuff first
	     */
	    if (SLSP_NBR_PTP_TYPE(nbr) || !SLSP_NBR_PTP_TYPE(tnbr)) {
		nbr->slsp_nbr_io_next = tnbr;
		dp->slsp_demux_nbr = nbr;
	    } else {
		while (tnbr->slsp_nbr_io_next
		  && SLSP_NBR_PTP_TYPE(tnbr->slsp_nbr_io_next)) {
		    tnbr = tnbr->slsp_nbr_io_next;
		}
		nbr->slsp_nbr_io_next = tnbr->slsp_nbr_io_next;
		tnbr->slsp_nbr_io_next = nbr;
	    }
	} else {
	    /*
	     * Node was an ignore previously, just add the
	     * neighbour structure.
	     */
	    dp->slsp_demux_nbr = nbr;
	    assert(slsp_io_n_demux_ignore);
	    slsp_io_n_demux_ignore--;
	}
    } else {
	nbr->slsp_nbr_io_next = (slsp_neighbour *) 0;
	slsp_demux_insert(dp, nbr->slsp_nbr_addr, nbr);
    }

    /*
     * If we just inserted a new broadcast interface neighbour,
     * flush the tree.  This'll ensure we get packets from guys
     * we were ignoring previously.
     */
    if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST && slsp_io_n_demux_ignore) {
	slsp_demux_flush();
    }
}


/*
 * slsp_io_remove - delete a neighbour from the demux tree
 */
void
slsp_io_remove __PF1(nbr, slsp_neighbour *)
{
    register slsp_demux *dp = slsp_io_demux;
    register u_int32 key = ntohl(sock2ip(nbr->slsp_nbr_addr));
    register u_int32 mask;

    /*
     * Find the address in the tree.  It must be there.
     */
    assert(dp);
    do {
	mask = dp->slsp_demux_mask;
	if (key & mask) {
	    dp = dp->slsp_demux_right;
	} else {
	    dp = dp->slsp_demux_left;
	}
    } while (mask > dp->slsp_demux_mask);
    assert(key == dp->slsp_demux_key && dp->slsp_demux_nbr);

    /*
     * If he is the only guy attached to this, the node goes.
     * Otherwise pull him out of the list.
     */
    if (dp->slsp_demux_nbr == nbr) {
	if (nbr->slsp_nbr_io_next) {
	    dp->slsp_demux_nbr = nbr->slsp_nbr_io_next;
	    nbr->slsp_nbr_io_next = (slsp_neighbour *) 0;
	} else {
	    slsp_demux_remove(dp);
	}
    } else {
	register slsp_neighbour *tnbr = dp->slsp_demux_nbr;

	while (tnbr->slsp_nbr_io_next != nbr) {
	    tnbr = tnbr->slsp_nbr_io_next;
	}
	tnbr->slsp_nbr_io_next = nbr->slsp_nbr_io_next;
	nbr->slsp_nbr_io_next = (slsp_neighbour *) 0;
    }
}


/*
 * slsp_send - send a packet to the specified neighbour.  If the
 *	       "neighbour" is a broadcast interface, send the packet
 *	       to the broadcast address.
 */
void
slsp_send __PF3(nbr, slsp_neighbour *,
		pkt, byte *,
		pktlen, size_t)
{
    trace *trp;
    sockaddr_un *to_addr;

    /*
     * Figure out who to send this to.  It is to the neighbour address,
     * unless the node is a broadcast interface in which case we
     * send it to the interface broadcast address.
     */
    if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST) {
	to_addr = nbr->slsp_nbr_if->ifa_addr_broadcast;
    } else {
	to_addr = nbr->slsp_nbr_addr;
    }

    /*
     * Fetch the trace options.  Figure out if we should trace this.
     */
    trp = nbr->slsp_nbr_trace_options;
    if (!trp) {
	trp = nbr->slsp_nbr_instance->slsp_trace_options;
    }

    if (TRACE_TF(trp, TR_SLSP_SEND)) {
	slsp_trace(trp,
		   "SLSP SEND ",
		   nbr->slsp_nbr_if->ifa_addr_local,
		   to_addr,
		   pkt,
		   pktlen);
    }

    /*
     * Now send the packet.  We don't necessarily care about the return code.
     */
    (void) task_send_packet(slsp_io_task,
			    (void_t) pkt,
			    pktlen,
			    (flag_t) 0,
			    to_addr);
}


/*
 * slsp_io_recv - one or more packets has arrived, read them and
 *		  process to find the neighbour they belong to.
 */
static void
slsp_io_recv __PF1(tp, task *)
{
    register slsp_demux *dp;
    register u_int32 src;
    int res;
    int n_bytes = SLSP_RECV_OCTETS;	/* Number of bytes to read at once */
    u_int n_pkts = 0;
    int pktproto;
    int pktclass;
    int ignore_it = 0;
    struct ip *ip;
    byte *pkt;
    size_t count;
    size_t pktlen;
    sockaddr_un dest;
    trace *trp;
    slsp_neighbour *nbr;
    slsp_instance *inp;
    _PROTOTYPE(pktprocess,
	       void,
	       (slsp_neighbour *,
		byte *,
		size_t));

    sockclear_in(&dest);
    do {
	/*
	 * Fetch a packet
	 */
	res = task_receive_packet(tp, &count);
	if (res != TASKRC_OK && res != TASKRC_TRUNC) {
	    /*
	     * System error, hope it fixes itself.
	     */
	    break;
	}

	n_pkts++;
	task_parse_ip(ip, pkt, byte *);
	sock2ip(&dest) = ip->ip_dst.s_addr;

	/*
	 * Make sure we've got at least something in the IP packet data
	 */
	pktlen = pkt - (byte *) ip;
	if (count <= pktlen) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("slsp_io_recv: %A->%A: total packet length %u ip header length %u: no data",
			  task_recv_srcaddr,
			  &dest,
			  count,
			  pktlen));
	    continue;
	}
	pktlen = count - pktlen;

	/*
	 * Okay, find this neighbour in the tree.
	 */
	src = ntohl(sock2ip(task_recv_srcaddr));
	nbr = (slsp_neighbour *) 0;
	if ((dp = slsp_io_demux)) {
	    register u_int32 mask;

	    do {
		mask = dp->slsp_demux_mask;
		if (src & mask) {
		    dp = dp->slsp_demux_right;
		} else {
		    dp = dp->slsp_demux_left;
		}
	    } while (mask > dp->slsp_demux_mask);

	    if (src == dp->slsp_demux_key) {
		nbr = dp->slsp_demux_nbr;
		if (!nbr) {
		    assert(FALSE);
		    ignore_it = 1;
		}
	    }
	}

	if (ignore_it) {
	    ignore_it = 0;
	    if (TRACE_TP(tp, TR_SLSP_RECV)) {
		slsp_trace(tp->task_trace,
			   "SLSP RECV ",
			   task_recv_srcaddr,
			   &dest,
			   pkt,
			   pktlen);
	    }
	    trace_tp(tp,
		     TR_NORMAL,
		     0,
		     ("slsp_io_recv: %A->%A packet discarded",
		      task_recv_srcaddr,
		      &dest));
	    continue;
	}

	/*
	 * Fetch the packet protocol.  The packet will have at least
	 * one byte in it.  Determine who should process the packet.
	 */
	pktproto = SLSP_GET_PROTOCOL(pkt);
	if (pktproto == SLSP_HELLO_PROTOCOL) {
	    pktprocess = slsp_nbr_ptp_hello;
	    pktclass = SLSP_CLASS_PTP;
	} else if (pktproto == SLSP_LEADER_PROTOCOL) {
	    /*
	     * Check the fixed fields in the short leader, complain
	     * if broken.
	     */
	    if (pktlen < SLSP_SHORT_LEADER_LEN) {
		trace_log_tp(tp,
			     0,
			     LOG_ERR,
			     ("slsp_io_recv: %A->%A packet length %u too short for leader",
			      task_recv_srcaddr,
			      &dest,
			      pktlen));
		slsp_pktdump(tp->task_trace,
			     "SLSP ERR ",
			     pkt,
			     pktlen);
		continue;
	    }

	    pktproto = SLSP_GET_LEADER_TYPE(pkt);
	    if (!SLSP_CHK_SHORT_LEADER(pkt)) {
		/* XXX stupid rcp_routed XXX */
		if (*(pkt+2) == SLSP_LEADER_VERSION_ID
		  && pktproto == SLSP_SEQ_TYPE) {
		    trace_tp(tp,
			     TR_NORMAL,
			     0,
			     ("slsp_io_recv: %A->%A length %u SN packet has fucked up byte %02x",
			      task_recv_srcaddr,
			      &dest,
			      pktlen,
			      *(pkt+3)));
		/* XXX rcp_routed stinks XXX */
		} else {
		    trace_log_tp(tp,
				 0,
				 LOG_ERR,
			 	 ("slsp_io_recv: %A->%A length %u leader fixed field check failed",
				  task_recv_srcaddr,
				  &dest,
				  pktlen));
		    slsp_pktdump(tp->task_trace,
				 "SLSP ERR ",
				 pkt,
				 pktlen);
		    continue;
		}
	    }

	    switch (pktproto) {
	    case SLSP_PTP_IHU_TYPE:
		pktprocess = slsp_nbr_ptp_ihu;
		pktclass = SLSP_CLASS_PTP;
		break;

	    case SLSP_BCAST_IHU_TYPE:
		pktprocess = slsp_nbr_bcast_ihu;
		pktclass = SLSP_CLASS_BCAST;
		break;

	    case SLSP_LSP_TYPE:
		pktprocess = slsp_db_lsp;
		pktclass = SLSP_CLASS_DB;
		break;

	    case SLSP_SEQ_TYPE:
		pktprocess = slsp_db_seq;
		pktclass = SLSP_CLASS_DB;
		break;

	    case SLSP_EXT_TYPE:
		pktprocess = slsp_db_lsp_useless;
		pktclass = SLSP_CLASS_DB;
		break;

	    default:
		trace_tp(tp,
			 TR_ALL,
			 LOG_WARNING,
			 ("slsp_io_recv: %A->%A received illegal packet type %u",
			  task_recv_srcaddr,
			  &dest,
			  pktproto));
		slsp_pktdump(tp->task_trace,
			     "SLSP ERR ",
			     pkt,
			     pktlen);
		continue;
	    }
	} else {
	    trace_tp(tp,
		     TR_ALL,
		     LOG_WARNING,
		     ("slsp_io_recv: %A->%A unknown packet protocol %u",
		      task_recv_srcaddr,
		      &dest,
		      pktproto));
	    slsp_pktdump(tp->task_trace,
			 "SLSP ERR ",
			 pkt,
			 pktlen);
	    continue;
	}

	res = SLSP_IO_NONBR;
	if (nbr) {
	    do {
		if_addr *ifap = nbr->slsp_nbr_if;

		switch (nbr->slsp_nbr_type) {
		default:
		    assert(FALSE);

		case SLSP_NTYPE_PTP:
		case SLSP_NTYPE_PTP_PEER:
		    if (pktclass != SLSP_CLASS_BCAST
		      && sock2ip(&dest) == sock2ip(ifap->ifa_addr_local)) {
			res = SLSP_IO_NBR;
		    }
		    break;

		case SLSP_NTYPE_BCAST:
		    if (pktclass != SLSP_CLASS_PTP
		      && sock2ip(&dest) == sock2ip(ifap->ifa_addr_broadcast)) {
			res = SLSP_IO_OUROWN;
		    }
		    break;

		case SLSP_NTYPE_BCAST_NBR:
		    if (pktclass != SLSP_CLASS_PTP
		      && (sock2ip(&dest) == sock2ip(ifap->ifa_addr_broadcast)
			|| sock2ip(&dest) == sock2ip(ifap->ifa_addr_local))) {
			res = SLSP_IO_NBR;
		    }
		    break;
		}
	    } while (res == SLSP_IO_NONBR && (nbr = nbr->slsp_nbr_io_next));
	} else if (pktclass == SLSP_CLASS_BCAST) {
	    /*
	     * Here we have no neighbour, but we have a broadcast hello
	     * packet which might be one of ours.  Search for the broadcast
	     * LAN neighbour this might be related to.
	     */
	    for (inp = slsp_instance_list; inp && !nbr; inp = inp->slsp_next) {
		for (nbr = inp->slsp_nbrs; nbr; nbr = nbr->slsp_nbr_next) {
		    if (nbr->slsp_nbr_type == SLSP_NTYPE_BCAST) {
			if_addr *ifap = nbr->slsp_nbr_if;

			if (sock2ip(&dest) == sock2ip(ifap->ifa_addr_broadcast)
			  && (sock2ip(task_recv_srcaddr)
			    & sock2ip(ifap->ifa_netmask))
			      == sock2ip(ifap->ifa_net)) {
			    break;
			}
		    }
		}
	    }

	    if (nbr) {
		res = SLSP_IO_NEWNBR;
	    }
	}

	if (nbr) {
	    trp = nbr->slsp_nbr_trace_options;
	} else {
	    trp = tp->task_trace;
	}

	if (TRACE_TF(trp, TR_SLSP_RECV)) {
	    if ((pktclass == SLSP_CLASS_DB && TRACE_TF(trp, TR_SLSP_RECV_LSP))
	      || (pktclass != SLSP_CLASS_DB
		&& TRACE_TF(trp, TR_SLSP_RECV_HELLO))) {
		slsp_trace(trp,
			   "SLSP RECV ",
			   task_recv_srcaddr,
			   &dest,
			   pkt,
			   pktlen);
	    }
	}

	if (nbr
	  && pktclass == SLSP_CLASS_DB
	  && nbr->slsp_nbr_state != SLSP_NBR_STATE_ADJACENT) {
	    trace_tf(trp,
		     TR_NORMAL,
		     0,
		     ("slsp_io_recv: %A->%A ignoring link state packet from non-adjacent neighbour",
		      task_recv_srcaddr,
		      &dest));
	    continue;
	}

	switch (res) {
	case SLSP_IO_NONBR:
	    trace_tf(trp,
		     TR_NORMAL,
		     0,
		     ("slsp_io_recv: %A->%A not for us",
		      task_recv_srcaddr,
		      &dest));
	    break;

	case SLSP_IO_NBR:
	    pktprocess(nbr, pkt, pktlen);
	    n_bytes -= (int) pktlen;
	    break;

	case SLSP_IO_NEWNBR:
	    slsp_nbr_new_bcast_ihu(nbr, task_recv_srcaddr, pkt, pktlen);
	    n_bytes -= (int) pktlen;
	    break;

	case SLSP_IO_OUROWN:
	    trace_tf(trp,
		     TR_NORMAL,
		     0,
		     ("slsp_io_recv: %A->%A received our own broadcast",
		      task_recv_srcaddr,
		      &dest));
	    break;
	}
    } while (n_bytes > 0);

    trace_tp(tp,
	     TR_NORMAL,
	     0,
	     ("slsp_io_recv: %u packet%s received, %d byte%s processed",
	      n_pkts,
	      ((n_pkts == 1) ? "" : "s"),
	      (SLSP_RECV_OCTETS - n_bytes),
	      (((SLSP_RECV_OCTETS - n_bytes) == 1) ? "" : "s")));

    SLSP_DB_ACK_FLUSH();
}


/*
 * slsp_io_reconfig_timeout - process a timeout during reconfiguration
 */
static void
slsp_io_reconfig_timeout __PF2(tip, task_timer *,
			       interval, time_t)
{
    /*
     * If no longer doing reconfiguration, delete ourselves
     */
    if (!BIT_TEST(task_state, TASKS_RECONFIG)) {
	task_timer_delete(tip);
	slsp_io_reconfig_timer = (task_timer *) 0;
	return;
    }

    /*
     * Run the receive routine to clear the socket, then reset for
     * another go-around.
     */
    slsp_io_recv(tip->task_timer_task);
    task_timer_set(tip, (time_t) 0, SLSP_IO_RECONFIG_INTERVAL);
}


/*
 * slsp_io_cleanup - start our reconfiguration procedure.  We run a high
 *		     priority timer during reconfiguration to allow us
 *		     to poll our socket from time to time while
 *		     reconfiguration is going on.  This lets us send
 *		     acks for LSPs and responses to hellos without fooling
 *		     around much.
 */
static void
slsp_io_cleanup __PF1(tp, task *)
{
    /*
     * Don't remove the tracing from the task, we'll do that
     * after the reconfig is complete.  Just return if a timer
     * is already running, this might happen if someone reconfigures
     * again before the previous timer terminates.
     */
    if (slsp_io_reconfig_timer) {
	task_timer_set(slsp_io_reconfig_timer,
		       (time_t) 0, 
		       SLSP_IO_RECONFIG_INTERVAL);
    } else {
	slsp_io_reconfig_timer = task_timer_create(slsp_io_task,
						   "Reconfig_Recv",
						   TIMERF_HIPRIO,
						   (time_t) 0,
						   SLSP_IO_RECONFIG_INTERVAL,
						   slsp_io_reconfig_timeout,
						   (void_t) 0);
    }
}


/*
 * slsp_io_reinit - reinitialization processing.  Mostly to correct the
 *		    trace options on the task
 */
static void
slsp_io_reinit __PF1(tp, task *)
{
    trace_set(tp->task_trace, slsp_global_trace_options);
}


/*
 * slsp_io_dump - placeholder for now
 */
static void
slsp_io_dump __PF2(tp, task *,
		   fd, FILE *)
{
    /* nothing */
}


/*
 * slsp_io_start - create a task and condition a socket to receive
 *		   SLSP packets.  
 */
void
slsp_io_start __PF0(void)
{
    task *tp;
    int s;

    if (slsp_io_task) {
	return;
    }

    tp = task_alloc("SLSP_IO", (TASKPRI_PROTO-1), slsp_global_trace_options);
    tp->task_proto = SLSP_IP_PROTO;
    tp->task_rtproto = RTPROTO_SLSP;
    task_set_cleanup(tp, slsp_io_cleanup);
    task_set_reinit(tp, slsp_io_reinit);
    task_set_terminate(tp, slsp_io_terminate);
    task_set_dump(tp, slsp_io_dump);

    if (!task_create(tp)) {
	task_quit(EINVAL);
    }
    slsp_io_task = tp;

    /*
     * Get the socket for this guy
     */
    if ((s = task_get_socket(tp, AF_INET, SOCK_RAW, SLSP_IP_PROTO)) < 0) {
	task_quit(errno);
    }

    /*
     * Bind the socket to the task
     */
    task_set_recv(tp, slsp_io_recv);
    task_set_socket(tp, s);

    /*
     * Set the kernel receive buffer size to be able to receive as big
     * a packet as possible.  Set the send buffering to match.
     */
    slsp_io_maxpacket = MIN(task_maxpacket, IP_MAXPACKET);
    if (task_set_option(tp,
			TASKOPTION_RECVBUF,
			slsp_io_maxpacket) < 0) {
	task_quit(errno);
    }
    if (task_set_option(tp,
			TASKOPTION_SENDBUF,
			slsp_io_maxpacket) < 0) {
	task_quit(errno);
    }
		
    /*
     * Set the socket non-blocking so we don't get caught.  Set
     * the don't route flag to make sure the packets go where we
     * expect, and set the ttl to 1 for the heck of it
     */
    if (task_set_option(tp,
			TASKOPTION_NONBLOCKING,
			(caddr_t) TRUE) < 0) {
	task_quit(errno);
    }

    (void) task_set_option(tp,
			   TASKOPTION_DONTROUTE,
			   1);

    (void) task_set_option(tp,
			   TASKOPTION_TTL,
			   1);

#ifdef	IPTOS_PREC_INTERNETCONTROL
    (void) task_set_option(tp,
			   TASKOPTION_TOS,
			   IPTOS_PREC_INTERNETCONTROL);
#endif	/* IPTOS_PREC_INTERNETCONTROL */

#ifdef	PROTO_SNMP
    /*
     * Start the stupid MIB
     */
    slsp_init_mib(TRUE);
#endif	/* PROTO_SNMP */
}

/*
 * %(Copyright)
 */
