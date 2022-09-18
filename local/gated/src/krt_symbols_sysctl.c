/*
 *  $Id: krt_symbols_sysctl.c,v 1.4.2.1 1994/08/15 20:24:03 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_UDP
#define	INCLUDE_UDP_VAR
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#include "krt.h"
#include "krt_var.h"
#include <sys/sysctl.h>

int
krt_symbols __PF1(tp, task *)
{
    char buf[BUFSIZ];
    int name[CTL_MAXNAME];
    size_t len;
    int value;

    name[0] = CTL_KERN;
    name[1] = KERN_VERSION;
    len = sizeof buf;
    if (sysctl(name, 2, buf, &len, (void *) 0, 0) < 0) {
	trace_log_tp(tp,
		     0,
		     LOG_INFO,
		     ("krt_symbols: sysctl(CTL_KERN, KERN_VERSION): %m"));
    } else {
	/* Set version */

	krt_version_kernel = task_mem_strdup(tp, buf);
	trace_tp(tp,
		 TR_KRT_SYMBOLS,
		 0,
		 ("krt_symbols: kernel version: %s\n",
		  krt_version_kernel));
    }

#ifdef	PROTO_INET
    name[0] = CTL_NET;
    name[1] = AF_INET;

    name[2] = IPPROTO_IP;
    name[3] = IPCTL_FORWARDING;
    len = sizeof value;
    if (sysctl(name, 4, (void *) &value, &len, (void *) 0, 0) < 0) {
	trace_log_tp(tp,
		     0,
		     LOG_INFO,
		     ("krt_symbols: sysctl(CTL_NET, AF_INET, IPPROTO_IP, IPCTL_FORWARDING): %m"));
    } else {
	inet_ipforwarding = value >= 1;
	trace_tp(tp,
		 TR_KRT_SYMBOLS,
		 0,
		 ("krt_symbols: IP forwarding: %u using %u\n",
		  value,
		  inet_ipforwarding));
    }

    name[2] = IPPROTO_UDP;
    name[3] = UDPCTL_CHECKSUM;
    len = sizeof value;
    if (sysctl(name, 4, (void *) &value, &len, (void *) 0, 0) < 0) {
	trace_log_tp(tp,
		     0,
		     LOG_INFO,
		     ("krt_symbols: sysctl(CTL_NET, AF_INET, IPPROTO_UDP, UDP_CHECKSUM): %m"));
    } else {
	inet_udpcksum = value != 0;
	trace_tp(tp,
		 TR_KRT_SYMBOLS,
		 0,
		 ("krt_symbols: UDP checksum: %u using %u\n",
		  value,
		  inet_udpcksum));
    }
#endif	/* PROTO_INET */
    
    trace_tp(tp,
	     TR_KRT_SYMBOLS,
	     0,
	     (NULL));

    return 0;
}
