/*
 *  $Id: krt_rt_ioctl.c,v 1.6.2.2 1995/01/23 12:40:17 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_IOCTL
#define	INCLUDE_ROUTE
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#ifdef	PROTO_ISO
#include "iso.h"
#endif	/* PROTO_ISO */
#include "krt.h"
#include "krt_var.h"


flag_t krt_rt_support = KRTS_HOST
#ifdef	VARIABLE_MASKS
	| KRTS_VAR_MASK
#endif	/* VARIABLE_MASKS */
	;

static struct rtentry krt;

static inline int
krt_action __PF2(tp, task *,
		 type, u_long)
{
    int request_error = 0;

    if ((!BIT_TEST(task_state, TASKS_TEST)
	 && !BIT_TEST(krt_options, KRT_OPT_NOINSTALL))
	 && (task_ioctl(krt_task->task_socket,
			type,
			(caddr_t) &krt, 
			sizeof (krt)) < 0)) {
	request_error = errno;
    }

    return request_error;
}


static void
krt_build __PF5(tp, task *,
		dest, sockaddr_un *,
		mask, sockaddr_un *,
		krtp, krt_parms *,
		router, sockaddr_un *)
{

    bzero((caddr_t) & krt, sizeof(krt));
    krt.rt_dst = *sock2unix(dest, (int *) 0);		/* struct copy */
    krt.rt_gateway = *sock2unix(router, (int *) 0);	/* struct copy */
    krt.rt_flags = krt_state_to_flags(krtp->krtp_state);
    if (sockishost(dest, mask)) {
	BIT_SET(krt.rt_flags, RTF_HOST);
    }
    if (krtp->krtp_n_gw
	&& krtp->krtp_ifaps
	&& krtp->krtp_ifap
	&& BIT_TEST(krtp->krtp_ifap->ifa_state, IFS_UP)) {
	BIT_SET(krt.rt_flags, RTF_UP);
    }
#ifdef	RTF_DYNAMIC
    if (krtp->krtp_protocol == RTPROTO_REDIRECT) {
	BIT_SET(krt.rt_flags, RTF_DYNAMIC);
    }
#endif	/* RTF_DYNAMIC */
}


int
krt_change_start __PF1(tp, task *)
{
    return KRT_OP_SUCCESS;
}


int
krt_change_end __PF1(tp, task *)
{
    return KRT_OP_SUCCESS;
}


int
krt_change __PF5(tp, task *,
		 dest, sockaddr_un *,
		 mask, sockaddr_un *,
		 old_krtp, krt_parms *,
		 new_krtp, krt_parms *)
{
    int pri = 0;
    int rc = KRT_OP_SUCCESS;
    sockaddr_un *new_router = (sockaddr_un *) 0;
    sockaddr_un *old_router = (sockaddr_un *) 0;

    if (new_krtp) {
	if (!new_krtp->krtp_n_gw) {
	    new_router = krt_make_router(socktype(dest), new_krtp->krtp_state);
	    assert(new_router);
	} else {
	    new_router = new_krtp->krtp_router;
	}
    }

    if (old_krtp) {
	if (!old_krtp->krtp_n_gw) {
	    old_router = krt_make_router(socktype(dest), old_krtp->krtp_state);
	    assert(old_router);
	} else {
	    old_router = old_krtp->krtp_router;
	}
    }
    
    if (old_krtp && new_krtp && (!old_krtp->krtp_n_gw || old_krtp->krtp_ifap)
	&& old_krtp->krtp_state == new_krtp->krtp_state
	&& (BIT_TEST(new_krtp->krtp_state, RTS_REJECT|RTS_BLACKHOLE)
	    || (sockaddrcmp(old_router, new_router)
		&& new_krtp->krtp_ifap == old_krtp->krtp_ifap))) {
	/* If nothing has changed, there isn't anything to do */

	return rc;
    }

    if (old_krtp) {
	
	krt_build(tp, dest, mask, old_krtp, old_router);

	switch (krt_action(tp, RTM_DELETE)) {
	case ENOBUFS:
	    /* Not enough resources to perform the action */
	    return KRT_OP_FULL;

	case ENETUNREACH:
	case EEXIST:
	default:
	    /* Should not happen */
	    pri = LOG_CRIT;
	    goto log_delete;

	case ESRCH:
	    /* Route not found. */
	    if (BIT_TEST(old_krtp->krtp_state, RTS_GATEWAY)) {
		/* Not really a problem, but lets complain */

		pri = LOG_CRIT;
		goto log_delete;
	    }

	    /* Probably an interface route deleted by ifconfig */
	    pri = LOG_NOTICE;
	    /* Fall through */

	case 0:
	    krt_n_routes--;
	    
	    if (TRACE_TP(tp, TR_KRT_REQUEST)) {
	    log_delete:
		krt_trace(tp,
			  "SEND",
			  "DELETE",
			  dest,
			  mask,
			  old_router,
			  (flag_t) krt.rt_flags,
			  pri ? (const char *) strerror(errno) : (char *) 0,
			  pri);
		pri = 0;
	    }
	    break;
	}
    }
    
    if (new_krtp) {
	int retry = 5;

	if (krt_n_routes > krt_limit_routes) {
	    /* Too many routes */

	    return KRT_OP_FULL;
	}
	
	krt_build(tp, dest, mask, new_krtp, new_router);
	
    retry_add:
	if (!--retry) {
	    /* Give up */
	    return KRT_OP_NOCANDO;
	}

	switch (krt_action(tp, RTM_ADD)) {
	case ENOBUFS:
	    /* No resources */
	    rc = KRT_OP_FULL;
	    break;

	case ENETUNREACH:
	    /* Probably an interface down. */
	    /* If we defer this the higher levels will remove this from the queue */
	    rc = KRT_OP_DEFER;
	    break;

	default:
	    pri = LOG_CRIT;
	    goto log_add;

	case EEXIST:
	    if (BIT_TEST(new_krtp->krtp_state, RTS_GATEWAY)) {
		/* Route already exists - delete and re-install */

		switch (krt_action(tp, RTM_DELETE)) {
		case ENOBUFS:
		    /* Not enough resources to perform the action */
		    rc = KRT_OP_FULL;
		    break;

		default:
		case EEXIST:
		case ENETUNREACH:
		case ESRCH:
		    pri = LOG_CRIT;
		    goto log_add_delete;

		case 0:
		    if (TRACE_TP(tp, TR_KRT_REQUEST)) {
		    log_add_delete:
			krt_trace(tp,
				  "SEND",
				  "DELETE",
				  dest,
				  mask,
				  new_router,
				  (flag_t) krt.rt_flags,
				  pri ? (const char *) strerror(errno) : (char *) 0,
				  pri);
			pri = 0;
		    }
		    goto retry_add;
		}
		break;
	    }
	    /* An interface route - assume it is correct */
	    pri = LOG_NOTICE;
	    /* Fall through */

	case 0:
	    krt_n_routes++;
	    
	    if (TRACE_TP(tp, TR_KRT_REQUEST)) {
	    log_add:
		krt_trace(tp,
			  "SEND",
			  "ADD",
			  dest,
			  mask,
			  new_router,
			  (flag_t) krt.rt_flags,
			  pri ? (const char *) strerror(errno) : (char *) 0,
			  pri);
		pri = 0;
	    }
	}

	if (rc != KRT_OP_SUCCESS && old_krtp) {
	    rc |= KRT_OP_PARTIAL;
	}
    }

    return rc;
}


void
krt_delete_dst __PF8(tp, task *,
		     dest, sockaddr_un *,
		     mask, sockaddr_un *,
		     proto, proto_t,
		     state, flag_t,
		     n_gw, int,
		     routers, sockaddr_un **,
		     ifaps, if_addr **)
{
    krt_parms krtp;

    krtp.krtp_protocol = proto;
    krtp.krtp_state = state | RTS_GATEWAY;
    krtp.krtp_n_gw = n_gw;
    krtp.krtp_routers = routers;
    krtp.krtp_ifaps = ifaps;

    (void) krt_change(tp,
		      dest,
		      mask,
		      &krtp,
		      (krt_parms *) 0);
}
