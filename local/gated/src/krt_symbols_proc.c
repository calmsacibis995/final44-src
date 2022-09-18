/*
 *  $Id: krt_symbols_proc.c,v 1.2.2.1 1995/01/10 17:30:13 jch Exp $
 */

/* %(Copyright.header) */

#define	INCLUDE_FILE
#define	INCLUDE_IOCTL
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#include "krt.h"
#include "krt_var.h"
#include <stdio.h>


int
krt_symbols __PF1(tp, task *)
{
    char *resp;
    char buf[240];
    FILE *fp;

#ifdef	PROTO_INET
    resp = (char *) fp = fopen("/proc/net/snmp","r");
    if (fp) {
	resp = fgets(buf, 240, fp);      /* skip header */
	resp = fgets(buf, 6, fp);
	resp += 4;                    /* point at IP Forwarding value */
	fclose (fp);
    }
    if (resp) {
	inet_ipforwarding = atoi(resp) > 0;
	trace_tp(tp,
		 TR_KRT_SYMBOLS,
		 0,
		 ("krt_symbols: IP forwarding: %u using %u\n",
		  atoi(resp),
		  inet_ipforwarding));
    }
#endif	/* PROTO_INET */

    fp = fopen("/proc/version","r");                   
    if (fp) {                                                  
        krt_version_kernel = task_mem_strdup(tp, fgets(buf, 80, fp));
        fclose (fp);                                                      
    }                                                                   

    trace_tp(tp,
	     TR_KRT_SYMBOLS,
	     0,
	     ("krt_symbols: krt_version_kernel = %s",
	      krt_version_kernel));
    return 0;
}


/*
 * %(Copyright)
 */
