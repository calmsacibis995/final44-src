/*
 *  $Id: krt.c,v 1.67 1993/03/17 03:52:38 jch Exp $
 */

/* %(Copyright.header) */


#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#include "krt.h"
#include "krt_var.h"


int
krt_symbols __PF0(void)
{
    /* XXX - ip_forwarding */
    /* XXX - udp_checksums */
    /* XXX - kernel_version */
}
