h48674
s 00003/00000/00100
d D 8.2 93/08/15 13:13:25 mckusick 6 5
c final update from Akito Fujita
e
s 00002/00002/00098
d D 8.1 93/06/10 22:25:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00000/00080
d D 7.4 93/05/12 04:11:14 akito 4 3
c LUNA-II (68040 based LUNA) support
e
s 00001/00003/00079
d D 7.3 93/01/03 12:48:43 akito 3 2
c remaked from field
e
s 00001/00001/00081
d D 7.2 92/10/11 11:07:45 bostic 2 1
c make kernel includes standard
e
s 00082/00000/00000
d D 7.1 92/06/15 06:38:30 fujita 1 0
c date and time created 92/06/15 06:38:30 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 5
 * Copyright (c) 1982, 1990, 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: clockreg.h 1.14 91/01/18$
D 3
 * OMRON: $Id: clockreg.h,v 1.1 92/05/27 14:24:52 moti Exp $
 *
 * from: hp300/hp300/clockreg.h	7.3 (Berkeley) 5/7/91
E 3
I 3
 * from: hp300/hp300/clockreg.h	7.4 (Berkeley) 12/27/92
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
 *  LUNA system clock defines
 */
#define	CLOCK_REG	0x63000000	/* system clock address */

#define	CLK_INT		0x7		/* system clock intr flag */
#define	CLK_CLR		0x1		/* system clock intr clear */

/*
 * LUNA battery-backed clock
 */

/* only use software */
struct bbc_tm {
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
};

#define FEBRUARY	2
#define	STARTOFTIME	1970
#define SECDAY		86400L
#define SECYR		(SECDAY * 365)

#define	leapyear(year)		((year) % 4 == 0)
#define	range_test(n, l, h)	if ((n) < (l) || (n) > (h)) return(0)
#define	days_in_year(a) 	(leapyear(a) ? 366 : 365)
#define	days_in_month(a) 	(month_days[(a) - 1])

/*
 * TIME KEEPER RAM -- (MK48T02/12(B)-12/15/20/25)
 */

D 2
#include "../dev/nvram.h"
E 2
I 2
#include <luna68k/dev/nvram.h>
E 2

struct bbc {
    struct nvram 	nvram;	       	/* non-volatile RAM area */
    unsigned char    	cal_ctl;       	/* calender control resistor */
    unsigned char	cal_sec;       	/* secons resistor */
    unsigned char	cal_min;       	/* minutes resistor */
    unsigned char	cal_hour;      	/* hours resitor */
    unsigned char	cal_dow;       	/* day of the weeks */
    unsigned char	cal_day;       	/* days resistor */
    unsigned char	cal_mon;       	/* months resistor */
    unsigned char	cal_year;      	/* years resistor */
};

#define	BBC_ADDR	0x45000000	/* battery backuped clock address */

#define	BBC_FRQ		0x40		/* Frequency test (in day) */
#define	BBC_KICK	0x80		/* Kick start (in hour) */
#define	BBC_STOP	0x80		/* Stop bit (in seconds) */
#define	BBC_WRT		0x80		/* Write bit (in control) */
#define	BBC_RD		0x40		/* Read bit (in control) */
#define	BBC_SGN		0x20		/* Sign bit (in control) */
#define	BBC_DELAY	180		/* delay time */

#define	binary_to_bcd(i)	(((i) / 10) << 4 | ((i) % 10))
#define	bcd_to_binary(i)	(((i) >> 4) *10 + ((i) & 0x0F))
I 4

#ifdef LUNA2
struct bbc2 {
    unsigned char	cal_sec;	/* secons resistor */
    unsigned char	cal_sec_alarm;	/* secons alarm resistor */
    unsigned char	cal_min;	/* minutes resistor */
    unsigned char	cal_min_alarm;	/* minutes alarm resistor */
    unsigned char	cal_hour;	/* hours resitor */
    unsigned char	cal_hour_alarm;	/* hours alarm resitor */
    unsigned char	cal_dow;	/* day of the weeks */
    unsigned char	cal_day;	/* days resistor */
    unsigned char	cal_mon;	/* months resistor */
    unsigned char	cal_year;	/* years resistor */
    unsigned char    	cal_ctl_a;	/* calender control resistor */
    unsigned char    	cal_ctl_b;	/* calender control resistor */
    unsigned char    	cal_ctl_c;	/* calender control resistor */
    unsigned char    	cal_ctl_d;	/* calender control resistor */
    unsigned char    	nvram[50];	/* non-volatile RAM area */
};
I 6

#define	BBC2_A_UIP	0x80
#define	BBC2_B_SET	0x80
E 6
#endif
E 4
E 1
