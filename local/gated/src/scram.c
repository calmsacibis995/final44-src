/*
 *  $Id: scram.c,v 1.26 1994/01/17 18:49:10 jch Exp $
 */

/* %(Copyright.header) */

#define	INCLUDE_ROUTE
#include "include.h"
#include "krt.h"
#include "scram.h"

#ifndef	_IBMR2
Fatal Error - This code is only valid for IBM 6611 Network Processors
#endif

#define	SCRAM_MSG_SIZE	(sizeof (struct rtm_msg) + 3 * sizeof (sockaddr_un))

#define	RTM_ADDR(ap)	ap = (struct sockaddr *) \
    ((caddr_t) ap + (ap->sa_len ? ROUNDUP(ap->sa_len, sizeof (u_long)) : sizeof(u_long)))

static task *scram_task;
static task_timer *scram_timer_open;

static block_t	scram_block_index;
static u_int	scram_queued;		/* Number of messages in the queue */
static int	scram_shutdown;		/* Go away when finished */
static int	scram_active;		/* Connection is active */
static int	scram_disabled;		/* Don't do scram */

struct rtm_msg {
    struct rtm_msg *rtm_forw;
    struct rtm_msg *rtm_back;
    byte	*rtm_ptr;	/* Where to start next write */
    size_t	rtm_len;	/* How much left to write */
    struct rt_msghdr msghdr;
};

static struct rtm_msg scram_head = {&scram_head, &scram_head};	/* Head of message queue */

trace *scram_trace_options = (trace *) 0;

/* Called to close the socket and set the timer to try to open again */
static void
scram_close __PF2(tp, task *,
		  restart, int)
{
    struct rtm_msg *rtp = scram_head.rtm_forw;

    if (rtp != &scram_head) {
	/* Reset write pointer and length on the first message */
	rtp->rtm_ptr = (byte *) &rtp->msghdr;
	rtp->rtm_len = rtp->msghdr.rtm_msglen;
    }

    tp->task_connect = 0;
    tp->task_write = 0;
    BIT_RESET(tp->task_flags, TASKF_CONNECT);
    task_close(tp);
    if (restart) {
	task_timer_set(scram_timer_open, SCRAM_T_OPEN, (time_t) 0);
    }
    scram_active = TRUE;
}


/* We don't expect to receive any data, this routine is just here to check for errors */
static void
scram_recv __PF1(tp, task *)
{
    int rc;
    size_t size;

    rc = task_receive_packet(tp, &size);

    switch (rc) {
    case TASKRC_OK:
	trace_log_tp(tp,
		     0,
		     LOG_INFO,
		     ("scram_recv: %d bytes of unexpected data",
		      size));
	break;

    case TASKRC_EOF:
	trace_log_tp(tp,
		     0,
		     LOG_WARNING,
		     ("scram_recv: end-of-file notification"));
	break;

    case TASKRC_TRUNC:
	trace_log_tp(tp,
		     0,
		     LOG_WARNING,
		     ("scram_recv: unexpected truncated packet");)
	break;

    default:
	errno = rc;
	trace_log_tp(tp,
		     0,
		     LOG_WARNING,
		     ("scram_recv: %m"));
	break;
    }

    /* We are not expecting anything so consider this a fatal error */
    scram_close(tp, TRUE);
}


/* Write as many messages on the queue as possible */
static void
scram_write __PF1(tp, task *)
{
    struct rtm_msg *rtp, *rtpn;

    for (rtp = scram_head.rtm_forw; rtp != &scram_head; rtp = rtpn) {
	/* For each packet on the queue */

	while (rtp->rtm_len > 0) {
	    /* While there is still data in this packet */

	    int rc = task_send_packet(tp,
				      rtp->rtm_ptr,
				      rtp->rtm_len,
				      (flag_t) 0,
				      (sockaddr_un *) 0);

	    if (!rc) {
		/* Connection closed */

		scram_close(tp, TRUE);
		return;
	    } else if (rc < 0) {
		/* Error */

		switch (errno) {
		case EWOULDBLOCK:
#if	defined(EAGAIN) && EAGAIN != EWOULDBLOCK
		case EAGAIN:		/* System V style */
#endif	/* EAGAIN */
		    /* Set up to get notification when ready for write */
		    tp->task_write = scram_write;
		    task_set_socket(tp, tp->task_socket);
		    return;
		    
		case EINTR:
		    /* Retry */
		    break;

		default:
		    scram_close(tp, TRUE);
		}
	    } else {
		/* Successful write of at least some data */
		rtp->rtm_ptr += rc;
		rtp->rtm_len -= rc;
	    }
	} /* Data to send */

	/* Remove this element from the queue and free it */
	REMQUE(rtp);
	scram_queued--;
	rtpn = rtp->rtm_forw;
	task_block_free(scram_block_index, (caddr_t) rtp);

    } /* Packet to send */

    /* Are we shutting down */
    if (scram_shutdown) {
	scram_close(tp, FALSE);
	scram_timer_open = (task_timer *) 0;
	task_delete(tp);
    }

    /* Nothing else to write */
    if (tp->task_write) {
	tp->task_write = 0;
	task_set_socket(tp, tp->task_socket);
    }
}


/* Called when a connect succeeds or fails */
static void
scram_connect __PF1(tp, task *)
{
    sockaddr_un *addr;

    addr = task_get_addr_remote(tp);
    if (!addr) {
	/* Connect failed */
	scram_close(tp, TRUE);
	return;
    }

    /* Connect succeeded */
    tp->task_connect = 0;
    BIT_RESET(tp->task_flags, TASKF_CONNECT);
    task_set_socket(tp, tp->task_socket);

    /* We need a large buffer */
    if (task_set_option(scram_task,
			TASKOPTION_SENDBUF,
			task_maxpacket) < 0) {
	task_quit(errno);
    }

    scram_active = TRUE;
    
    /* See if there is any work to do */
    if (scram_head.rtm_forw != &scram_head) {
	scram_write(tp);
    }
}


/* Called to by timer to get a socket and try to connect */
static void
scram_open __PF2(tip, timer *,
		 interval, time_t)
{
    int s;
    task *tp = tip->timer_task;
    
    s = task_get_socket(tp, AF_UNIX, SOCK_STREAM, AF_UNSPEC);

    /* Insure we have a socket */
    assert(s >= 0);

    /* Set up the task */
    tp->task_connect = scram_connect;
    BIT_SET(tp->task_flags, TASKF_CONNECT);
    task_set_socket(tp, s);

    /* Set non-blocking */
    if (task_set_option(scram_task,
			TASKOPTION_NONBLOCKING,
			TRUE) < 0) {
	task_quit(errno);
    }

    if (task_connect(tp)) {
	switch (errno) {
	case EWOULDBLOCK:
#if	defined(EAGAIN) && EAGAIN != EWOULDBLOCK
	case EAGAIN:		/* System V style */
#endif	/* EAGAIN */
	    /* Set timer to connect */
	    break;

	default:
	    scram_close(tp, TRUE);
	    return;
	}
    } else {
	/* Open succeeded */

	scram_connect(tp);
    }

    /* Either we connected or we are waiting for a response to the connect */
    task_timer_reset(tip);
}


/* Fill in a request and enqueue it */
void
scram_request __PF2(type, int,
		    rt, rt_entry *)
{
    int route, routes;
    const char *ctype;
    size_t size;
    struct rtm_msg *rtp;
    struct sockaddr *ap;
    struct sockaddr *dest = sock2unix(rt->rt_dest, (int *) 0);
    struct sockaddr *mask = (struct sockaddr *) 0;

    if (scram_disabled) {
	return;
    }
    
    switch (type) {
    case RTM_ADD:
	routes = rt->rt_n_gw;
	ctype = "ADD";
	break;

    case RTM_DELETE:
	routes = 1;
	ctype = "DELETE";
	break;

    default:
	assert(FALSE);
    }

    for (route = 0; route < routes; route++) {
	struct sockaddr *gateway = sock2unix(rt->rt_routers[route], (int *) 0);

	if (TRACE_TP(scram_task, TR_KRT_REQUEST)) {
	    tracef("SCRAM %-6s %-15A",
		   ctype,
		   rt->rt_dest);

	    if (!BIT_TEST(rt->rt_state, RTS_GROUP)) {
		tracef(" mask %-15A",
		       rt->rt_dest_mask);
	    }

	    if (type == RTM_ADD) {
		tracef(" gateway %-15A",
		       rt->rt_routers[route]);
	    }
	    tracef(" %s <%s>",
		   trace_state(rt_proto_bits, rt->rt_gwp->gw_proto),
		   trace_bits(rt_state_bits, rt->rt_state));
	}

	if (krt_install && !BIT_TEST(task_state, TASKS_TEST)) {
	    flag_t flags = 0;
	
	    size = sizeof(struct rt_msghdr) + dest->sa_len;

	    if (sockishost(rt->rt_dest, rt->rt_dest_mask)) {
		BIT_SET(flags, RTF_HOST);
	    } else if (rt->rt_dest_mask) {
		mask = sock2unix(rt->rt_dest_mask, (int *) 0);
		size += mask->sa_len;
	    }
	
	    switch (type) {
	    case RTM_ADD:
		size += gateway->sa_len;
		break;

	    default:
		gateway = (struct sockaddr *) 0;
	    }

	    /* Allocate a block and clear it */
	    assert(size <= SCRAM_MSG_SIZE);
	    rtp = (struct rtm_msg *) task_block_alloc(scram_block_index);

	    rtp->msghdr.rtm_type = type;
	    rtp->msghdr.rtm_pid = task_pid;
	    rtp->msghdr.rtm_flags = RTF_DONE | flags | krt_state_to_flags(rt->rt_state);
	    if (RT_IFAP(rt) && BIT_TEST(RT_IFAP(rt)->ifa_state, IFS_UP)) {
		BIT_SET(rtp->msghdr.rtm_flags, RTF_UP);
	    }
#ifdef	RTF_DYNAMIC
	    if (rt->rt_gwp->gw_proto == RTPROTO_REDIRECT) {
		BIT_SET(rtp->msghdr.rtm_flags, RTF_DYNAMIC);
	    }
#endif	/* RTF_DYNAMIC */
#ifdef	IP_MULTICAST
	    if (BIT_TEST(rt->rt_state, RTS_GROUP)) {
		BIT_SET(rtp->msghdr.rtm_flags, RTF_HOST);
	    }
#endif	/* IP_MULTICAST */

	    rtp->msghdr.rtm_msglen = size;

	    /* XXX - set metrics */

	    ap = (struct sockaddr *) (rtp + 1);

	    bcopy((caddr_t) dest, (caddr_t) ap, dest->sa_len);
	    RTM_ADDR(ap);
	    BIT_SET(rtp->msghdr.rtm_addrs, RTA_DST);

	    if (gateway) {
		bcopy((caddr_t) gateway, (caddr_t) ap, gateway->sa_len);
		RTM_ADDR(ap);
		BIT_SET(rtp->msghdr.rtm_addrs, RTA_GATEWAY);
	    }

	    /* Provide a mask if this is not a host route */
	    if (mask) {
		/* Convert our netmask format into the kernel's netmask format. */
		/* The kernel does not want the address family nor trailing zeros. */
		register byte *sp = (byte *) mask;
		register byte *lp = (byte *) mask + mask->sa_len;
		register byte *dp = (byte *) ap;
		register byte *cp = (byte *) 0;

		mask->sa_len = mask->sa_family = 0;	/* OK to write here, it's a scratch buffer */
		
		/* Copy mask and keep track of last non-zero byte */
		while (sp < lp) {
		    if (*dp++ = *sp++) {
			/* We actually point to the first byte after last zero byte */
			cp = dp;
		    }
		}

		if (cp <= (byte *) &ap->sa_family) {
		    /* If the netmask is zero length, make sure there is at least a */
		    /* long word of zeros present */
		    *((u_long *) ap) = 0;
		} else {
		    ap->sa_len = cp - (byte *) ap;
		}
		
		RTM_ADDR(ap);
		BIT_SET(rtp->msghdr.rtm_addrs, RTA_NETMASK);
	    }

	    rtp->rtm_ptr = (byte *) &rtp->msghdr;
	    rtp->rtm_len = rtp->msghdr.rtm_msglen = (byte *) ap - rtp->rtm_ptr;

	    rtp->msghdr.rtm_seq = ++scram_head.msghdr.rtm_seq;
	    rtp->msghdr.rtm_version = RTM_VERSION;

	    /* Insert at the end of the queue */
	    INSQUE(rtp, scram_head.rtm_back);
	    scram_queued++;

	    /* If this is the first entry on the queue, run the queue */
	    if (scram_active &&
		scram_head.rtm_forw == rtp) {
		trace_tp(scram_task,
			 TR_KRT_REQUEST,
			 0,
			 (NULL));
		scram_write(scram_task);
	    } else {
		trace_log_tp(scram_task,
			     0,
			     LOG_WARNING,
			     (": deferred"));
	    }
	} else {
	    trace_tp(scram_task,
		     TR_KRT_REQUEST,
		     0,
		     (NULL));
	}
    }
}


static void
scram_terminate __PF1(tp, task *)
{
    if (!scram_queued) {
	scram_close(tp, FALSE);
	scram_timer_open = (task_timer *) 0;
	task_delete(tp);
    } else {
	scram_shutdown = TRUE;
    }
}


static void
scram_dump __PF2(tp, task *,
		 fp, FILE *)
{
    if (!scram_queued) {
	fprintf(fp, "\tSCRAM message queue empty\n");
    } else {
	fprintf(fp, "\tSCRAM message queue size: %d\n",
		scram_queued);
    }
    
    /* XXX - display the queue? */
}


static void
scram_cleanup __PF1(tp, task *)
{
    trace_freeup(tp->task_trace);
    trace_freeup(scram_trace_options);
}


void
scram_reinit __PF1(krt_tp, task *)
{
    trace_inherit(scram_trace_options, kernel_trace_options);
    trace_set(scram_task->task_trace, scram_trace_options);
}


void
scram_init __PF0(void)
{
    if (!scram_task && !scram_disabled) {
	scram_trace_options = trace_alloc(kernel_trace_options);
	scram_task = task_alloc("SCRAM",
				TASKPRI_SCRAM,
				scram_trace_options);
	scram_task->task_flags = TASKF_LAST;
	task_set_terminate(scram_task, scram_terminate);
	task_set_dump(scram_task, scram_dump);
	scram_task->task_addr = sockdup(sockbuild_un(SCRAM_NAME));
	task_set_recv(scram_task, scram_recv);

	if (!task_create(scram_task)) {
	    task_quit(EINVAL);
	}

	scram_timer_open = task_timer_create(scram_task,
					     "Timeout",
					     (flag_t) 0,
					     (time_t) SCRAM_T_OPEN,
					     (time_t) 0,
					     scram_open,
					     (void_t) 0);

	if (!BIT_TEST(task_state, TASKS_TEST)) {
	    scram_open(scram_timer_open, 0);
	}

	scram_block_index = task_block_init(SCRAM_MSG_SIZE, "scram_msg");
    }
}


/*
 * %(Copyright)
 */
