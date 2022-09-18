h46192
s 00002/00002/00031
d D 8.1 93/06/10 23:04:06 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00033
d D 7.2 93/06/04 17:24:25 sklower 2 1
c prototype everything
e
s 00034/00000/00000
d D 7.1 92/07/08 23:16:01 sklower 1 0
c date and time created 92/07/08 23:16:01 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Stephen Deering.
D 3
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* Internet Group Management Protocol (IGMP) definitions. */

/*
 * IGMP packet format.
 */
struct igmp {
	u_char		igmp_type;	/* version & type of IGMP message  */
	u_char		igmp_code;	/* unused, should be zero          */
	u_short		igmp_cksum;	/* IP-style checksum               */
	struct in_addr	igmp_group;	/* group address being reported    */
};					/*  (zero for queries)             */

#define IGMP_MINLEN		     8

#define IGMP_HOST_MEMBERSHIP_QUERY   0x11  /* message types, incl. version */
#define IGMP_HOST_MEMBERSHIP_REPORT  0x12
#define IGMP_DVMRP		     0x13  /* for experimental multicast   */
					   /*  routing protocol            */

#define IGMP_MAX_HOST_REPORT_DELAY   10    /* max delay for response to    */
D 2
					   /*  query (in seconds)          */
E 2
E 1
