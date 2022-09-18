/*
 *  $Id: krt_netopts.c,v 1.5.2.2 1995/05/01 16:15:37 jch Exp $
 */

/* %(Copyright.header) */


/* krt.c
 *
 * Kernel routing table interface routines
 */

#define	INCLUDE_IOCTL
#define	INCLUDE_NETOPT_IBMR2
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#include "krt.h"
#include "krt_var.h"

#ifndef	MAXOPTLEN
#define	MAXOPTLEN	128

struct optreq {
    char name[MAXOPTLEN];
    char data[MAXOPTLEN];
    char getnext;
} ;

#endif	/* MAXOPTLEN */


static struct optreq net_opts[] = {
#define	NOPTS_IPFORWARDING	0
    { "ipforwarding" },
#define	NOPTS_COMPAT43		1
    { "compat_43" },
    { "" }
} ;


int
krt_netopts __PF1(tp, task *)
{
    int rc, s;
    struct optreq *op;

    NON_INTR(s, socket(AF_UNIX, SOCK_STREAM, 0));
    if (s < 0) {
	int error = errno;

	trace_log_tp(tp,
		     0,
		     LOG_WARNING,
		     ("krt_netopts: socket(AF_UNIX, SOCK_STREAM, 0): %m"));

	return error;
    }
    
    for (op = net_opts; *op->name; op++) {
	op->getnext = 0;
	
	if (task_ioctl(s, 
		       (u_long) SIOCGNETOPT, 
		       (caddr_t) op, 
		       sizeof (*op)) < 0) {
	    trace_log_tp(tp,
			 0,
			 LOG_WARNING,
			 ("krt_netopts: ioctl(SIOCGNETOPT, %s): %m",
			  op->name,
			  errno));
	    continue;
	}
	trace_tp(tp,
		 TR_KRT_SYMBOLS,
		 0,
		 ("krt_netops: request %s response %s",
		  op->name,
		  op->data));

	switch (op - net_opts) {
	case NOPTS_IPFORWARDING:
#ifdef	PROTO_INET
	    inet_ipforwarding = atoi(op->data) > 0;
	    trace_tp(tp,
		     TR_KRT_SYMBOLS,
		     0,
		     ("krt_netops: IP forwarding: %u using %u",
		      atoi(op->data),
		      inet_udpcksum));
#endif	/* PROTO_INET */
	    break;

	case NOPTS_COMPAT43:
	    trace_tp(tp,
		     TR_KRT_SYMBOLS,
		     0,
		     ("krt_netops: 4.3 compatibility: %u",
		      atoi(op->data)));
	    if (atoi(op->data)) {
		trace_log_tp(tp,
			     0,
			     LOG_INFO,
			     ("krt_netops: running with %s=%d(%s) results in slightly reduced functionality!",
			      op->name,
			      atoi(op->data),
			      op->data));
	    }
	    break;
	    
	default:
	    assert(FALSE);
	}
    }

    NON_INTR(rc, close(s));
    if (rc < 0) {
	trace_log_tp(tp,
		     0,
		     LOG_WARNING,
		     ("krt_netopts: close(socket): %m"));
    }
    
    return 0;
}
