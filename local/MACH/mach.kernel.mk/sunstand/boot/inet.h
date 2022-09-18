/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	inet.h,v $
 * Revision 2.2  89/07/12  00:11:09  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)inet.h 1.3 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Following defn stolen from nd structure.
 */

#define NO_NDBASE  (struct no_nd *)(sip->si_devdata)


/* standalone RAM variables */
struct no_nd {
        int     no_nd_seq;                 /* current sequence number */
        struct ether_header no_nd_xh;      /* xmit header and packet */
        int     no_nd_block;               /* block number of data in "cache" */
        char    no_nd_buf[1600];           /* temp buf for packets */
        struct  sainet no_nd_inet;         /* INET state */
};

