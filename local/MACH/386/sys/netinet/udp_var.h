/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	udp_var.h,v $
 * Revision 2.3  89/03/09  20:47:38  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:02:44  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)udp_var.h	7.1 (Berkeley) 6/5/86
 */

/*
 * UDP kernel structures and variables.
 */
struct	udpiphdr {
	struct 	ipovly ui_i;		/* overlaid ip structure */
	struct	udphdr ui_u;		/* udp header */
};
#define ui_next		ui_i.ih_next
#define ui_prev		ui_i.ih_prev
#define ui_x1		ui_i.ih_x1
#define ui_pr		ui_i.ih_pr
#define ui_len		ui_i.ih_len
#define ui_src		ui_i.ih_src
#define ui_dst		ui_i.ih_dst
#define ui_sport	ui_u.uh_sport
#define ui_dport	ui_u.uh_dport
#define ui_ulen		ui_u.uh_ulen
#define ui_sum		ui_u.uh_sum

struct	udpstat {
	int	udps_hdrops;
	int	udps_badsum;
	int	udps_badlen;
};

#define UDP_TTL		30		/* time to live for UDP packets */

#ifdef	KERNEL
struct	inpcb udb;
struct	udpstat udpstat;
#endif
