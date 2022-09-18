/*
 *  $Id: krt_rtread_proc.c,v 1.4.2.2 1995/05/01 16:24:55 jch Exp $
 */

/* %(Copyright.header) */

#define	INCLUDE_ROUTE
#define	INCLUDE_KVM
#include "include.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#ifdef	PROTO_ISO
#include "iso.h"
#endif	/* PROTO_ISO */
#include "krt.h"
#include "krt_var.h"
#include <stdio.h>

/*  Read the kernel's routing table.			*/

/*
    Iface Destination Gateway Flags RefCnt  Use Metric  Mask   MTU   Window
    lo     0100007F  00000000  05     0    6261    0  FFFFFFFF 1936    0
    eth0   00C702CB  00000000  01     0    2123    0  00FFFFFF 1476    0
 */

int
krt_rtread __PF1(tp, task *)
{
    int i;
    flag_t flags;
    char *if_name[IFL_NAMELEN+1];
    u_int32 addr_dest, addr_mask, addr_gw;
    rt_parms rtparms;
    FILE *DFile;
    if_addr *ifap;

    bzero((caddr_t) &rtparms, sizeof (rtparms));
    rtparms.rtp_n_gw = 1;

    DFile = fopen("/proc/net/route", "r");
    if(DFile == NULL)
	return EBADF;

    trace_only_tp(tp,
		  TRC_NL_BEFORE,
		  ("krt_rtread: Initial routes read from kernel (via /proc/net/route):"));

    /* read route data from /proc   */

/* skip over header line */
    i=fscanf(DFile,"%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\n");

    while(!feof(DFile)){
	i=fscanf(DFile,"%s\t%lx\t%lx\t%02x\t%*d\t%*d\t%*d\t%lx\t%*d\t%*d\n",
		 if_name,
		 &addr_dest,
		 &addr_gw,
		 &flags,
		 &addr_mask);
	
	rtparms.rtp_dest = sockbuild_in(0, addr_dest);
	rtparms.rtp_dest_mask = inet_mask_locate(addr_mask);
	rtparms.rtp_state = krt_flags_to_state(flags);

	if (addr_gw) {
	    /* Gateway was specified, use it */
	    
	    rtparms.rtp_router = sockbuild_in(0, addr_gw);
	} else {
	    /* Gateway was not specified - try to figure it out */
	    
	    if (BIT_TEST(flags, RTF_GATEWAY)) {
		/* Not an interface route - ignore it */

		continue;
	    }

	    ifap = if_withsubnet(rtparms.rtp_dest);

	    if (!ifap
		|| strcmp(ifap->ifa_link->ifl_name, if_name)) {
		/* We could not find the interface */

		continue;
	    }

	    rtparms.rtp_router = ifap->ifa_addr;
	}

	krt_rtread_add(tp,
		       &rtparms,
		       flags,
		       FALSE,
		       "REMNANT");
    }

    return 0;
}


/*
 * %(Copyright)
 */
