/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	tcp_debug.h,v $
 * Revision 2.3  89/03/09  20:46:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:01:16  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)tcp_debug.h	7.1 (Berkeley) 6/5/86
 */

struct	tcp_debug {
	n_time	td_time;
	short	td_act;
	short	td_ostate;
	caddr_t	td_tcb;
	struct	tcpiphdr td_ti;
	short	td_req;
	struct	tcpcb td_cb;
};

#define TA_INPUT 	0
#define TA_OUTPUT	1
#define TA_USER		2
#define TA_RESPOND	3
#define TA_DROP		4

#ifdef	TANAMES
char	*tanames[] =
    { "input", "output", "user", "respond", "drop" };
#endif

#define TCP_NDEBUG 100
struct	tcp_debug tcp_debug[TCP_NDEBUG];
int	tcp_debx;
