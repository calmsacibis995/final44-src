/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	igmp_var.h,v $
 * Revision 2.4  90/07/03  16:42:10  mrt
 * 	Added to Mach kernel -  multicast release 5
 * 	[90/06/28            jjk]
 * 
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
	u_int	igps_rcv_total;		/* total IGMP messages received    */
	u_int	igps_rcv_tooshort;	/* received with too few bytes     */
	u_int	igps_rcv_badsum;	/* received with bad checksum      */
	u_int	igps_rcv_queries;	/* received membership queries     */
	u_int	igps_rcv_badqueries;	/* received invalid queries        */
	u_int	igps_rcv_reports;	/* received membership reports     */
	u_int	igps_rcv_badreports;	/* received invalid reports        */
	u_int	igps_rcv_ourreports;	/* received reports for our groups */
	u_int	igps_snd_reports;	/* sent membership reports         */
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
#define IGMP_RANDOM_DELAY(multiaddr)					\
	/* struct in_addr multiaddr; */					\
	( (ipstat.ips_total +						\
	   ntohl(IA_SIN(in_ifaddr)->sin_addr.s_addr) +			\
	   ntohl((multiaddr).s_addr)					\
	  )								\
	  % (IGMP_MAX_HOST_REPORT_DELAY * PR_FASTHZ) + 1		\
	)

#endif KERNEL
