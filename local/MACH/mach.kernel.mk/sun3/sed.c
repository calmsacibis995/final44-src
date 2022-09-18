/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sed.c,v $
 * Revision 2.3  89/03/09  21:38:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:47:06  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * 19-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Purged all queue code and related history.
 *
 */

#include <sys/param.h>

/* routines done by SED	*/

#ifdef	INET
extern	softnet();

setsoftnet()
{
	softcall(softnet, (caddr_t) 0);
}
#endif	INET

/*
 * This is where the "soft network" interrupt comes to. The
 * hardware interrupt routine has pulled the packet off the
 * interface and now wants us to run (at lower priority) the
 * protocol family specific routine to munch the packet.
 */
softnet()
{
#ifdef	INET
#define LOCORE /* *sigh* */
#include <net/netisr.h>
#undef LOCORE /* unsigh */
	extern int netisr;
	if (netisr & (1<<NETISR_RAW)) {
		netisr &= ~(1<<NETISR_RAW);
		rawintr();
		return(0);
	}
	if (netisr & (1<<NETISR_IP)) {
		netisr &= ~(1<<NETISR_IP);
		ipintr();
		return(0);
	}
	netisr = 0;
#endif	INET
	return (1);
}

int bbssi(bit,address)
	int     bit;
	char 	*address;
{
	setbit((char *)address + 3,bit);
	return(0);
}
  
int bbcci(bit,address)
	int     bit;
	char	*address;
{
	clrbit((char *)address + 3,bit);
	return(0);
}
