h64423
s 00002/00002/00057
d D 8.1 93/07/19 13:45:39 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00058
d D 7.3 93/07/19 13:45:15 mckusick 4 2
c fix prototype for igmp_input (from mccanne@horse.ee.lbl.gov)
e
s 00002/00002/00057
d R 8.1 93/06/10 23:04:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00010/00050
d D 7.2 93/01/08 18:42:53 andrew 2 1
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00060/00000/00000
d D 7.1 92/07/08 23:16:02 sklower 1 0
c date and time created 92/07/08 23:16:02 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Stephen Deering.
D 5
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Internet Group Management Protocol (IGMP),
 * implementation-specific definitions.
 *
 * Written by Steve Deering, Stanford, May 1988.
 *
 * MULTICAST 1.1
 */

struct igmpstat {
D 2
	u_int	igps_rcv_total;		/* total IGMP messages received */
	u_int	igps_rcv_tooshort;	/* received with too few bytes */
	u_int	igps_rcv_badsum;	/* received with bad checksum */
	u_int	igps_rcv_queries;	/* received membership queries */
	u_int	igps_rcv_badqueries;	/* received invalid queries */
	u_int	igps_rcv_reports;	/* received membership reports */
	u_int	igps_rcv_badreports;	/* received invalid reports */
	u_int	igps_rcv_ourreports;	/* received reports for our groups */
	u_int	igps_snd_reports;	/* sent membership reports */
E 2
I 2
	u_long	igps_rcv_total;		/* total IGMP messages received */
	u_long	igps_rcv_tooshort;	/* received with too few bytes */
	u_long	igps_rcv_badsum;	/* received with bad checksum */
	u_long	igps_rcv_queries;	/* received membership queries */
	u_long	igps_rcv_badqueries;	/* received invalid queries */
	u_long	igps_rcv_reports;	/* received membership reports */
	u_long	igps_rcv_badreports;	/* received invalid reports */
	u_long	igps_rcv_ourreports;	/* received reports for our groups */
	u_long	igps_snd_reports;	/* sent membership reports */
E 2
};

#ifdef KERNEL
struct igmpstat igmpstat;

/*
 * Macro to compute a random timer value between 1 and (IGMP_MAX_REPORTING_
 * DELAY * countdown frequency).  We generate a "random" number by adding
 * the total number of IP packets received, our primary IP address, and the
 * multicast address being timed-out.  The 4.3 random() routine really
 * ought to be available in the kernel!
 */
#define IGMP_RANDOM_DELAY(multiaddr) \
	/* struct in_addr multiaddr; */ \
	( (ipstat.ips_total + \
	   ntohl(IA_SIN(in_ifaddr)->sin_addr.s_addr) + \
	   ntohl((multiaddr).s_addr) \
	  ) \
	  % (IGMP_MAX_HOST_REPORT_DELAY * PR_FASTHZ) + 1 \
	)

void	igmp_init __P(());
D 4
void	igmp_input __P((struct mbuf *, struct ifnet *));
E 4
I 4
void	igmp_input __P((struct mbuf *, int));
E 4
void	igmp_joingroup __P((struct in_multi *));
void	igmp_leavegroup __P((struct in_multi *));
void	igmp_fasttimo __P(());
#endif
D 2

E 2
E 1
