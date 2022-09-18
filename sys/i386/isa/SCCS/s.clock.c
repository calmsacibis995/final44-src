h03475
s 00002/00002/00252
d D 8.1 93/06/11 15:53:30 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00085/00011/00169
d D 7.4 93/06/10 21:58:37 cgd 9 8
c many changes from NetBSD; better clock reading code
e
s 00007/00007/00173
d D 7.3 92/10/11 10:20:01 bostic 8 7
c make kernel includes standard
e
s 00004/00049/00176
d D 7.2 91/05/12 19:39:37 william 7 6
c cleaning pass, removed dead code, updated comments, found boners
e
s 00002/00004/00223
d D 7.1 91/05/09 23:32:47 bostic 6 5
c new copyright; att/bsd/shared
e
s 00082/00018/00145
d D 5.5 91/05/09 20:35:46 william 5 4
c interim version, changes for net2 tape
e
s 00009/00005/00154
d D 5.4 90/11/18 11:31:53 bill 4 3
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00036/00034/00123
d D 5.3 90/11/08 18:35:40 bill 3 2
c fix resched clock bug, tod, reliably read rtc
e
s 00103/00000/00054
d D 5.2 90/06/23 18:43:43 donahn 2 1
c Added stuff to read the cmos clock on startup.
e
s 00054/00000/00000
d D 5.1 90/04/24 12:59:13 william 1 0
c date and time created 90/04/24 12:59:13 by william
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
D 6
 * William Jolitz.
E 6
I 6
 * William Jolitz and Don Ahn.
E 6
 *
I 2
D 6
 * Added stuff to read the cmos clock on startup - Don Ahn
 *
E 2
 * %sccs.include.386.c%
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
I 9
 *	from: @(#)clock.c	7.2 (Berkeley) 5/12/91
 *	from NetBSD: Id: clock.c,v 1.6 1993/05/22 08:01:07 cgd Exp 
 *
E 9
 *	%W% (Berkeley) %G%
I 9
 *
E 9
 */

/*
 * Primitive clock interrupt routines.
 */
D 8
#include "param.h"
#include "time.h"
#include "kernel.h"
D 4
#include "icu.h"
I 3
#include "isa.h"
E 4
I 4
#include "machine/segments.h"
D 5
#include "machine/isa/icu.h"
#include "machine/isa/isa.h"
E 5
I 5
#include "i386/isa/icu.h"
#include "i386/isa/isa.h"
#include "i386/isa/rtc.h"
E 8
I 8
#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <machine/segments.h>
#include <i386/isa/icu.h>
#include <i386/isa/isa.h>
#include <i386/isa/rtc.h>
E 8
E 5
E 4
E 3

I 9
/* these should go elsewere (timerreg.h) but to avoid admin overhead... */
/*
 * Macros for specifying values to be written into a mode register.
 */
#define TIMER_CNTR0     (IO_TIMER1 + 0) /* timer 0 counter port */
#define TIMER_CNTR1     (IO_TIMER1 + 1) /* timer 1 counter port */
#define TIMER_CNTR2     (IO_TIMER1 + 2) /* timer 2 counter port */
#define TIMER_MODE      (IO_TIMER1 + 3) /* timer mode port */
#define         TIMER_SEL0      0x00    /* select counter 0 */
#define         TIMER_SEL1      0x40    /* select counter 1 */
#define         TIMER_SEL2      0x80    /* select counter 2 */
#define         TIMER_INTTC     0x00    /* mode 0, intr on terminal cnt */
#define         TIMER_ONESHOT   0x02    /* mode 1, one shot */
#define         TIMER_RATEGEN   0x04    /* mode 2, rate generator */
#define         TIMER_SQWAVE    0x06    /* mode 3, square wave */
#define         TIMER_SWSTROBE  0x08    /* mode 4, s/w triggered strobe */
#define         TIMER_HWSTROBE  0x0a    /* mode 5, h/w triggered strobe */
#define         TIMER_LATCH     0x00    /* latch counter for reading */
#define         TIMER_LSB       0x10    /* r/w counter LSB */
#define         TIMER_MSB       0x20    /* r/w counter MSB */
#define         TIMER_16BIT     0x30    /* r/w counter 16 bits, LSB first */
#define         TIMER_BCD       0x01    /* count in BCD */

E 9
I 2
#define DAYST 119
#define DAYEN 303

I 9
#ifndef	XTALSPEED
#define XTALSPEED 1193182
#endif

E 9
E 2
startrtclock() {
I 5
	int s;
E 5

I 9
	findcpuspeed();		/* use the clock (while it's free)
					to find the cpu speed */
E 9
	/* initialize 8253 clock */
D 3
	outb (0x43, 0x36);
	outb (0x40, 1193182/60);
	outb (0x40, (1193182/60)/256);
E 3
I 3
D 4
	outb (IO_TIMER0+3, 0x36);
	outb (IO_TIMER0, 1193182/hz);
	outb (IO_TIMER0, (1193182/hz)/256);
E 4
I 4
D 9
	outb (IO_TIMER1+3, 0x36);
	outb (IO_TIMER1, 1193182/hz);
	outb (IO_TIMER1, (1193182/hz)/256);
E 9
I 9
	outb(TIMER_MODE, TIMER_SEL0|TIMER_RATEGEN|TIMER_16BIT);
E 9
I 5

I 9
	/* Correct rounding will buy us a better precision in timekeeping */
	outb (IO_TIMER1, (XTALSPEED+hz/2)/hz);
	outb (IO_TIMER1, ((XTALSPEED+hz/2)/hz)/256);

E 9
D 7
#ifdef notdef
	/* NMI fail safe 1/4 sec  */
	/* initialize 8253 clock */
	outb(0x461,0);
	outb (IO_TIMER2+3, 0x30);
	outb (IO_TIMER2, 298300*40);
	outb (IO_TIMER2, (298300*40)/256);
	outb(0x461,4);
printf("armed ");
#endif

E 7
	/* initialize brain-dead battery powered clock */
	outb (IO_RTC, RTC_STATUSA);
	outb (IO_RTC+1, 0x26);
	outb (IO_RTC, RTC_STATUSB);
	outb (IO_RTC+1, 2);

D 7
	/*outb (IO_RTC, RTC_STATUSD);
	if((inb(IO_RTC+1) & 0x80) == 0)
		printf("rtc lost power\n");
	outb (IO_RTC, RTC_STATUSD);
	outb (IO_RTC+1, 0x80);*/

E 7
	outb (IO_RTC, RTC_DIAG);
	if (s = inb (IO_RTC+1))
		printf("RTC BIOS diagnostic error %b\n", s, RTCDG_BITS);
	outb (IO_RTC, RTC_DIAG);
	outb (IO_RTC+1, 0);
E 5
E 4
E 3
}

I 9
unsigned int delaycount;	/* calibrated loop variable (1 millisecond) */

#define FIRST_GUESS	0x2000
findcpuspeed()
{
	unsigned char low;
	unsigned int remainder;

	/* Put counter in count down mode */
	outb(IO_TIMER1+3, 0x34);
	outb(IO_TIMER1, 0xff);
	outb(IO_TIMER1, 0xff);
	delaycount = FIRST_GUESS;
	spinwait(1);
	/* Read the value left in the counter */
	low 	= inb(IO_TIMER1);	/* least siginifcant */
	remainder = inb(IO_TIMER1);	/* most significant */
	remainder = (remainder<<8) + low ;
	/* Formula for delaycount is :
	 *  (loopcount * timer clock speed)/ (counter ticks * 1000)
	 */
	delaycount = (FIRST_GUESS * (XTALSPEED/1000)) / (0xffff-remainder);
}



E 9
I 5
D 7
#ifdef ARGOx
reprimefailsafe(){
	outb(0x461,0);
	outb (IO_TIMER2+3, 0x30);
	outb (IO_TIMER2, 298300*40);
	outb (IO_TIMER2, (298300*40)/256);
	outb(0x461,4);
}
#endif

E 7
E 5
D 3
clkreld() {
pg("clkreld");
}

E 3
I 2
/* convert 2 digit BCD number */
bcd(i)
int i;
{
	return ((i/16)*10 + (i%16));
}

/* convert years to seconds (from 1970) */
unsigned long
ytos(y)
int y;
{
	int i;
	unsigned long ret;

D 9
	ret = 0; y = y - 70;
	for(i=0;i<y;i++) {
E 9
I 9
	ret = 0;
	for(i = 1970; i < y; i++) {
E 9
D 5
		if (i % 4) ret += 31536000;
		else ret += 31622400;
E 5
I 5
		if (i % 4) ret += 365*24*60*60;
		else ret += 366*24*60*60;
E 5
	}
	return ret;
}

/* convert months to seconds */
unsigned long
mtos(m,leap)
int m,leap;
{
	int i;
	unsigned long ret;

	ret = 0;
	for(i=1;i<m;i++) {
		switch(i){
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
D 5
			ret += 2678400; break;
E 5
I 5
			ret += 31*24*60*60; break;
E 5
		case 4: case 6: case 9: case 11:
D 5
			ret += 2592000; break;
E 5
I 5
			ret += 30*24*60*60; break;
E 5
		case 2:
D 5
			if (leap) ret += 2505600;
			else ret += 2419200;
E 5
I 5
			if (leap) ret += 29*24*60*60;
			else ret += 28*24*60*60;
E 5
		}
	}
	return ret;
}


E 2
/*
D 3
 * Initialze the time of day register, based on the time base which is, e.g.
E 3
I 3
 * Initialize the time of day register, based on the time base which is, e.g.
E 3
 * from a filesystem.
 */
inittodr(base)
	time_t base;
{
I 2
	unsigned long sec;
	int leap,day_week,t,yd;
I 5
D 7
int sa,s;
E 7
I 7
	int sa,s;
E 7
E 5
E 2

I 2
D 3
	outb(0x70,9); /* year    */
	sec = bcd(inb(0x71)); leap = !(sec % 4); sec += ytos(sec);
	outb(0x70,8); /* month   */
	yd = mtos(bcd(inb(0x71)),leap); sec += yd;
	outb(0x70,7); /* date    */
	t = (bcd(inb(0x71))-1) * 86400; sec += t; yd += t;
	outb(0x70,6); /* day     */
	day_week = inb(0x71);
	outb(0x70,4); /* hour    */
	sec += bcd(inb(0x71)) * 3600;
	outb(0x70,2); /* minutes */
	sec += bcd(inb(0x71)) * 60;
	outb(0x70,0); /* seconds */
	sec += bcd(inb(0x71));
E 3
I 3
D 5
	sec = bcd(rtcin(9)); leap = !(sec % 4); sec += ytos(sec); /* year    */
	yd = mtos(bcd(rtcin(8)),leap); sec += yd;		/* month   */
	t = (bcd(rtcin(7))-1) * 86400; sec += t; yd += t;	/* date    */
	day_week = rtcin(6);					/* day     */
	sec += bcd(rtcin(4)) * 3600;				/* hour    */
	sec += bcd(rtcin(2)) * 60;				/* minutes */
	sec += bcd(rtcin(0));					/* seconds */
E 5
I 5
	/* do we have a realtime clock present? (otherwise we loop below) */
	sa = rtcin(RTC_STATUSA);
	if (sa == 0xff || sa == 0) return;
E 5
E 3

I 5
	/* ready for a read? */
	while ((sa&RTCSA_TUP) == RTCSA_TUP)
		sa = rtcin(RTC_STATUSA);

D 9
	sec = bcd(rtcin(RTC_YEAR));
	leap = !(sec % 4); sec += ytos(sec); /* year    */
E 9
I 9
	sec = bcd(rtcin(RTC_YEAR)) + 1900;
	if (sec < 1970)
		sec += 100;
	leap = !(sec % 4); sec = ytos(sec); /* year    */
E 9
	yd = mtos(bcd(rtcin(RTC_MONTH)),leap); sec += yd;	/* month   */
	t = (bcd(rtcin(RTC_DAY))-1) * 24*60*60; sec += t; yd += t; /* date    */
	day_week = rtcin(RTC_WDAY);				/* day     */
	sec += bcd(rtcin(RTC_HRS)) * 60*60;			/* hour    */
	sec += bcd(rtcin(RTC_MIN)) * 60;			/* minutes */
	sec += bcd(rtcin(RTC_SEC));				/* seconds */
D 9
	sec -= 24*60*60; /* XXX why ??? */
E 9

D 9
#ifdef notdef
E 9
E 5
	/* XXX off by one? Need to calculate DST on SUNDAY */
	/* Perhaps we should have the RTC hold GMT time to save */
	/* us the bother of converting. */
D 5
	yd = yd / 86400;
E 5
I 5
D 9
	yd = yd / 24*60*60;
E 9
I 9
	yd = yd / (24*60*60);
E 9
E 5
	if ((yd >= DAYST) && ( yd <= DAYEN)) {
D 5
		sec -= 3600;
E 5
I 5
		sec -= 60*60;
E 5
	}
I 5
D 9
#endif
E 9
E 5
	sec += tz.tz_minuteswest * 60;

	time.tv_sec = sec;
}

I 3
#ifdef garbage
E 3
/*
 * Initialze the time of day register, based on the time base which is, e.g.
 * from a filesystem.
 */
test_inittodr(base)
	time_t base;
{

D 3
	outb(0x70,9); /* year    */
	printf("%d ",bcd(inb(0x71)));
	outb(0x70,8); /* month   */
	printf("%d ",bcd(inb(0x71)));
	outb(0x70,7); /* day     */
	printf("%d ",bcd(inb(0x71)));
	outb(0x70,4); /* hour    */
	printf("%d ",bcd(inb(0x71)));
	outb(0x70,2); /* minutes */
	printf("%d ",bcd(inb(0x71)));
	outb(0x70,0); /* seconds */
	printf("%d\n",bcd(inb(0x71)));
E 3
I 3
	outb(IO_RTC,9); /* year    */
	printf("%d ",bcd(inb(IO_RTC+1)));
	outb(IO_RTC,8); /* month   */
	printf("%d ",bcd(inb(IO_RTC+1)));
	outb(IO_RTC,7); /* day     */
	printf("%d ",bcd(inb(IO_RTC+1)));
	outb(IO_RTC,4); /* hour    */
	printf("%d ",bcd(inb(IO_RTC+1)));
	outb(IO_RTC,2); /* minutes */
	printf("%d ",bcd(inb(IO_RTC+1)));
	outb(IO_RTC,0); /* seconds */
	printf("%d\n",bcd(inb(IO_RTC+1)));
E 3

E 2
	time.tv_sec = base;
}
I 3
#endif
E 3
I 2

I 5
D 7
#ifdef notdef
E 7
E 5
I 3
/*
D 7
 * retreve a value from realtime clock
 */
u_char rtcin(n) {
	u_char val;

I 5
	/*outb(IO_RTC, RTC_STATUSA);
	do val = inb(IO_RTC+1) ; while (val&0x80);*/

E 5
	outb(IO_RTC,n);
I 5
	DELAY(100);
	if (inb(IO_RTC) != n) {
		outb(IO_RTC,n);
		DELAY(100);
	}
E 5
	do val = inb(IO_RTC+1) ; while (val != inb(IO_RTC+1));
	return (val);
}
I 5
#endif
E 5
E 3
E 2

/*
E 7
 * Restart the clock.
 */
resettodr()
{
}

I 7
/*
 * Wire clock interrupt in.
 */
E 7
I 4
D 5
#define V(s)	V/**/s
E 5
I 5
#define V(s)	__CONCAT(V, s)
E 5
extern V(clk)();
E 4
enablertclock() {
	INTREN(IRQ0);
I 4
	setidt(ICU_OFFSET+0, &V(clk), SDT_SYS386IGT, SEL_KPL);
E 4
	splnone();
}
I 9




spinwait(millisecs)
int millisecs;		/* number of milliseconds to delay */
{
	int i, j;

	for (i=0;i<millisecs;i++)
		for (j=0;j<delaycount;j++)
			;
}

E 9
E 1
