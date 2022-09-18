h64400
s 00002/00002/00027
d D 8.1 93/06/11 15:02:29 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00017/00029
d D 7.2 92/06/25 18:31:02 utashiro 2 1
c struct chiptime is not necessary for sony
e
s 00046/00000/00000
d D 7.1 92/06/04 16:06:52 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department, Ralph Campbell, Sony Corp. and Kazumasa
 * Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: clockreg.h 1.14 91/01/18$
 *
 *	%W% (Berkeley) %G%
 */

#define	SECMIN	((unsigned)60)			/* seconds per minute */
#define	SECHOUR	((unsigned)(60*SECMIN))		/* seconds per hour */
#define	SECDAY	((unsigned)(24*SECHOUR))	/* seconds per day */
#define	SECYR	((unsigned)(365*SECDAY))	/* seconds per common year */

#define	YRREF		1970
#define	LEAPYEAR(year)	(((year) % 4) == 0)

D 2
/*
 * Definitions for real time clock
 */
struct chiptime {
	u_char	sec;		/* current seconds */
	u_char	min;		/* current minutes */
	u_char	hour;		/* current hours */
	u_char	dayw;		/* day of the week */
	u_char	day;		/* day of the month */
	u_char	mon;		/* month */
	u_char	year;		/* year */
};

#if defined(CPU_SINGLE) && !defined(news700)

E 2
#define MK48T02

#define SET_CLOCK       0x80
#define READ_CLOCK      0x40
D 2

#endif /* CPU_SINGLE && !news700 */
E 2
E 1
