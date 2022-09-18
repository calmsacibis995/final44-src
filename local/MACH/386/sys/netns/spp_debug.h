/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	spp_debug.h,v $
 * Revision 2.3  89/03/09  20:53:32  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:08:40  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * Copyright (c) 1984, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)spp_debug.h	7.1 (Berkeley) 6/5/86
 */

struct	spp_debug {
	u_long	sd_time;
	short	sd_act;
	short	sd_ostate;
	caddr_t	sd_cb;
	short	sd_req;
	struct	spidp sd_si;
	struct	sppcb sd_sp;
};

#define SA_INPUT 	0
#define SA_OUTPUT	1
#define SA_USER		2
#define SA_RESPOND	3
#define SA_DROP		4

#ifdef	SANAMES
char	*sanames[] =
    { "input", "output", "user", "respond", "drop" };
#endif

#define SPP_NDEBUG 100
struct	spp_debug spp_debug[SPP_NDEBUG];
int	spp_debx;
