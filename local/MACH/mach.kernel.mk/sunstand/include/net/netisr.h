/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	netisr.h,v $
 * Revision 2.2  89/07/11  23:25:33  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)netisr.h 1.9 88/02/08 SMI; from UCB 7.1 6/4/86
 */

/*
 * The networking code runs off software interrupts.
 *
 * You can switch into the network by doing splnet() and return by splx().
 * The software interrupt level for the network is higher than the software
 * level for the clock (so you can enter the network in routines called
 * at timeout time).
 */

/*
 * These definitions are only to provide compatibility
 * with old code; new stuff should use softcall directly.
 */
#define	schednetisr(isrname)	softcall(isrname, (caddr_t)0)

#define	NETISR_RAW	rawintr		/* raw net intr */
#define	NETISR_IP	ipintr		/* IP net intr */
#define	NETISR_NS	nsintr		/* NS net intr */
#define	NETISR_IMP	impintr		/* IMP-host protocol interrupts */

int rawintr();

#ifdef INET
int ipintr();
#endif INET

#ifdef NS
int nsintr();
#endif NS

#if NIMP>0
int impintr();
#endif NIMP
