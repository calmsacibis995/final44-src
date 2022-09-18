/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	ka630.c,v $
 * Revision 2.5  89/03/09  22:16:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  20:20:14  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/24  02:58:29  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:07:02  mwyoung]
 * 
 *
 * 13-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Export ka630ROM (in case anyone wants to look at it).
 *
 *  9-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made cldevice a pointer for MACH.
 *
 * 22-Jul-86  UNIX Kernel Software (uk) at Carnegie-Mellon University
 *	CS_GENERIC:  moved memory parity enable to the standard place.
 *
 * 16-Jul-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  Changed to set a "Restart/boot" rather than just
 *	"Boot" action into cpmbx at initialization time.
 *
 */ 
/*
 *	@(#)ka630.c	7.1 (Berkeley) 6/5/86
 */
 
#include <cputypes.h>

#if	defined(VAX630)
/* ka630.c routines for the ka630 clock chip... */
#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/vmmac.h>

#include <vax/mtpr.h>
#include <vax/cpu.h>
#include <vax/clock.h>
#include <vax/pte.h>
#include <vax/ka630.h>

/*
 * These two functions handle the tod clock
 * This code is defunct at the end of the century.
 * Will Unix still be here then??
 */

struct cldevice	*cldevice;
struct ka630cpu	*ka630cpu;
char	*ka630ROM;

#if	0
short dayyr[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, };
/* Starts the tod clock. Called from clkstart... */
ka630tod(base)
	time_t base;
{
	register int tmp1, tmp2;
	register struct cldevice *claddr = cldevice;
 
	/*
	 * Clear restart and boot in progress flags in the CPMBX. This has
	 * nothing to do with the clock except that it the CPMBX reg. is a
	 * byte in the clock's ram.
	 */
	set_cpmbx(KA630CLK_RSBOOT);
	/*
	 *  ULTRIX also clears RAM location numbers 40-43 when it sets this.
	 *  Should we?
	 */
	claddr->csr1 = KA630CLK_SET;
	while ((claddr->csr0 & KA630CLK_UIP) != 0)
		;
	/* If the clock is valid, use it. */
	if ((claddr->csr3 & KA630CLK_VRT) != 0 &&
	    (claddr->csr1 & KA630CLK_ENABLE) == KA630CLK_ENABLE) {
		/* Convert yr,mon,day,hr,min,sec to sec past Jan.1, 1970. */
		tmp2 = 0;
		for (tmp1 = 70; tmp1 < claddr->yr; tmp1++) {
			tmp2 += 365;
			/* I just luv leap years... */
			if (LEAPYEAR(tmp1))
				tmp2++;
		}
		tmp2 += (dayyr[claddr->mon-1]+claddr->day-1);
		if (LEAPYEAR(claddr->yr) && claddr->mon > 2)
			tmp2++;
		/* Finally got days past Jan. 1,1970. the rest is easy.. */
		time.tv_sec = tmp2*SECDAY+claddr->hr*HRSEC+
			claddr->min*MINSEC+claddr->sec;
		tmp1 = claddr->csr2;
		claddr->csr0 = KA630CLK_RATE;
		claddr->csr1 = KA630CLK_ENABLE;
	} else if (base < 5*SECYR) {
		printf("WARNING: preposterous time in file system\n");
		time.tv_sec = 6*SECYR+186*SECDAY+SECDAY/2;
		ka630stod();
	} else {
		printf("WARNING: Time set via file system\n");
		time.tv_sec = base;
		ka630stod();
	}
}
/* Set the time of day clock, called via. stime system call.. */
ka630stod()
{
	register int tmp1, tmp3;
	register struct cldevice *claddr = cldevice;
	long tmp2, tmp4;

	claddr->csr1 = KA630CLK_SET;
	while ((claddr->csr0 & KA630CLK_UIP) != 0)
		;
	/* The reverse of above, sec. past Jan. 1,1970 to yr, mon... */
	tmp2 = time.tv_sec/HRSEC;
	tmp4 = tmp2 = tmp2/24;
	tmp1 = 69;
	while (tmp2 >= 0) {
		tmp3 = tmp2;
		tmp2 -= 365;
		tmp1++;
		if (LEAPYEAR(tmp1))
			tmp2--;
	}
	/* Got the year... */
	claddr->yr = tmp1;
	tmp1 = -1;
	do {
		tmp2 = tmp3-dayyr[++tmp1];
		if (LEAPYEAR(claddr->yr) && tmp1 > 1)
			tmp2--;
	} while (tmp2 >= 0);
	/* Finally, got the rest... */
	claddr->mon = tmp1;
	claddr->day = tmp3-dayyr[tmp1-1]+1;
	if (LEAPYEAR(claddr->yr) && tmp1 > 2)
		claddr->day--;
	tmp2 = time.tv_sec-(tmp4*SECDAY);
	claddr->hr = tmp2/HRSEC;
	tmp2 = tmp2%HRSEC;
	claddr->min = tmp2/MINSEC;
	tmp2 = tmp2%MINSEC;
	claddr->sec = tmp2;
	tmp1 = claddr->csr2;
	tmp1 = claddr->csr3;
	claddr->csr0 = KA630CLK_RATE;
	claddr->csr1 = KA630CLK_ENABLE;
}
#endif
#endif	0
