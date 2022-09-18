h14324
s 00003/00001/00099
d D 8.2 94/01/12 09:37:11 bostic 6 5
c don't put comments inside comments
e
s 00002/00002/00098
d D 8.1 93/06/10 21:40:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00100
d D 7.4 92/12/27 09:44:47 hibler 4 3
c get rid of PRF_INTERVAL
e
s 00002/00002/00102
d D 7.3 91/05/07 09:59:33 hibler 3 2
c DIO-II support
e
s 00008/00006/00096
d D 7.2 90/12/05 18:53:21 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00102/00000/00000
d D 7.1 90/05/08 17:51:13 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 3
 * from: Utah $Hdr: clockreg.h 1.13 89/11/30$
E 3
I 3
 * from: Utah $Hdr: clockreg.h 1.14 91/01/18$
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
 * HP300 "real time clock" (MC6840) registers
 */

struct clkreg {
	u_char	clk_dummy1;
	u_char	clk_cr3;
#define	clk_cr1	clk_cr3
	u_char	clk_dummy2;
	u_char	clk_cr2;
#define	clk_sr	clk_cr2
	u_char	clk_dummy3;
	u_char	clk_msb1;
	u_char	clk_dummy4;
	u_char	clk_lsb1;
	u_char	clk_dummy5;
	u_char	clk_msb2;
	u_char	clk_dummy6;
	u_char	clk_lsb2;
	u_char	clk_dummy7;
	u_char	clk_msb3;
	u_char	clk_dummy8;
	u_char	clk_lsb3;
};

D 2
#define CLKCR1		IOP(0x5F8001)
#define CLKCR2		IOP(0x5F8003)
#define CLKCR3		CLKCR1
E 2
I 2
/* base/offsets for register access (for locore.s) */
D 3
#define	CLKBASE		IOP(0x5F8000)
E 3
I 3
#define	CLKBASE		IIOPOFF(0x5F8000)
E 3
#define	CLKCR1		0x1
#define	CLKCR2		0x3
#define	CLKCR3		CLKCR1
E 2
#define	CLKSR		CLKCR2
D 2
#define	CLKMSB1		IOP(0x5F8005)
#define	CLKMSB2		IOP(0x5F8009)
#define	CLKMSB3		IOP(0x5F800D)
E 2
I 2
#define	CLKMSB1		0x5
#define	CLKMSB2		0x9
#define	CLKMSB3		0xD
E 2

/* output of counter 3 clocks counter 2 */

#define	CLK_OENAB	0x80	/* output enable */
#define	CLK_IENAB	0x40	/* interrupt enable */
#define	CLK_8BIT	0x04	/* 8 bit mode */
#define	CLK_RESET	0x01	/* chip reset (CR1 only) */
#define	CLK_CR1		0x01	/* select CR1 (CR2 only) */
#define	CLK_CR3		0x00	/* select CR3 (CR2 only) */
#define CLK_INT1	0x01	/* interrupt flag for timer 1 (SR only) */
#define CLK_INT2	0x02	/* interrupt flag for timer 2 (SR only) */
#define CLK_INT3	0x04	/* interrupt flag for timer 3 (SR only) */
#define	CLK_INTR	0x80	/* composite interrupt flag (SR only) */

#define CLK_RESOLUTION	4	/* 4 usec resolution (250Khz) */
#define	CLK_INTERVAL	2500	/* 10msec interval at 250KHz */
D 6
/* #define CLK_INTERVAL	5000	/* 20msec interval at 250Khz */
E 6
I 6
#ifdef NOTDEF
#define CLK_INTERVAL	5000	/* 20msec interval at 250Khz */
#endif
E 6

D 4
#ifndef PRF_INTERVAL
#define PRF_INTERVAL    CLK_INTERVAL
#endif

E 4
/*
 * HP300 battery-backed clock
 */

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

#define BBC_SET_REG 	0xe0
#define BBC_WRITE_REG	0xc2
#define BBC_READ_REG	0xc3
#define NUM_BBC_REGS	12

#define	leapyear(year)		((year) % 4 == 0)
#define	range_test(n, l, h)	if ((n) < (l) || (n) > (h)) return(0)
#define	days_in_year(a) 	(leapyear(a) ? 366 : 365)
#define	days_in_month(a) 	(month_days[(a) - 1])
#define	bbc_to_decimal(a,b) 	(bbc_registers[a] * 10 + bbc_registers[b])
#define	decimal_to_bbc(a,b,n) 	{ \
	bbc_registers[a] = (n) % 10; \
	bbc_registers[b] = (n) / 10; \
}
E 1
