/*
 *  $Id: krt_symbols_sunos5.c,v 1.3.2.2 1995/01/23 12:40:25 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_FILE
#define	INCLUDE_IOCTL
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#include <inet/nd.h>
#endif	/* PROTO_INET */
#include "krt.h"
#include "krt_var.h"
#include <sys/systeminfo.h>

static char *
krt_symbols_ndd __PF3(tp, task *,
		      module, const char *,
		      name, const char *)
{
    int sd;
    int rc;
    static char buf[64];

    NON_INTR(sd, open(module, O_RDWR));
    if (sd == -1) {
	trace_log_tp(tp,
		     0,
		     LOG_ERR,
		     ("krt_symbols_ndd: open %s: %m",
		      module));
	return (char *) 0;
    }

    strcpy(buf, name);

    rc = task_ioctl(sd,
		    (u_long) ND_GET,
		    buf,
		    sizeof buf);
    if (rc == -1) {
	trace_log_tp(tp,
		     0,
		     LOG_ERR,
		     ("krt_symbols_ndd: ioctl(ND_GET, %s): %m",
		      name));
	(void) close(sd);
	return (char *) 0;
    }

    (void) close(sd);
    return buf;
}


int
krt_symbols __PF1(tp, task *)
{
    char *resp;
    char buf[BUFSIZ], *bp = buf;
    int len = sizeof buf;
    static long infos[] = {
	SI_SYSNAME,
	SI_RELEASE,
	SI_VERSION,
	SI_HOSTNAME,
	SI_MACHINE,
	SI_ARCHITECTURE,
	0
    };
    long *info = infos;

#ifdef	PROTO_INET
    resp = krt_symbols_ndd(tp, "/dev/ip", "ip_forwarding");
    if (resp) {
	inet_ipforwarding = atoi(resp) > 0;
	trace_tp(tp,
		 TR_KRT_SYMBOLS,
		 0,
		 ("krt_symbols: IP forwarding: %u using %u\n",
		  atoi(resp),
		  inet_ipforwarding));
    }
    resp = krt_symbols_ndd(tp, "/dev/udp", "udp_do_checksum");
    if (resp) {
	inet_udpcksum = atoi(resp) != 0;
	trace_tp(tp,
		 TR_KRT_SYMBOLS,
		 0,
		 ("krt_symbols: UDP checksums: %u using %u\n",
		  atoi(resp),
		  inet_udpcksum));
    }
#endif	/* PROTO_INET */

    do {
	int rc;
	
	*bp = (char) 0;
	rc = sysinfo(*info, bp, len);
	if (rc == -1) {
	    trace_log_tp(tp,
			 0,
			 LOG_ERR,
			 ("krt_symbols: sysinfo(): %m"));
	    continue;
	}
	bp += rc;
	len -= rc;
	bp[-1] = ' ';
    } while (*++info) ;
    *bp = (char) 0;

    krt_version_kernel = task_mem_strdup(tp, buf);

    trace_tp(tp,
	     TR_KRT_SYMBOLS,
	     0,
	     ("krt_symbols: krt_version_kernel = %s",
	      krt_version_kernel));

    return 0;
}
