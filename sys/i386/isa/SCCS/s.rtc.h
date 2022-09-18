h00329
s 00002/00002/00051
d D 8.1 93/06/11 15:54:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00052
d D 7.1 91/05/12 19:39:42 william 3 2
c cleaning pass, removed dead code, updated comments, found boners
e
s 00033/00001/00020
d D 1.2 91/05/09 20:35:56 william 2 1
c interim version, changes for net2 tape
e
s 00021/00000/00000
d D 1.1 90/11/08 20:02:59 bill 1 0
c date and time created 90/11/08 20:02:59 by bill
e
u
U
t
T
I 2
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
D 2
 * %W% (Berkeley) %G%
E 2
 * RTC Register locations
 */

#define RTC_SEC		0x00	/* seconds */
#define RTC_SECALRM	0x01	/* seconds alarm */
#define RTC_MIN		0x02	/* minutes */
#define RTC_MINALRM	0x03	/* minutes alarm */
#define RTC_HRS		0x04	/* hours */
#define RTC_HRSALRM	0x05	/* hours alarm */
#define RTC_WDAY	0x06	/* week day */
#define RTC_DAY		0x07	/* day of month */
#define RTC_MONTH	0x08	/* month of year */
#define RTC_YEAR	0x09	/* month of year */
#define RTC_STATUSA	0x0a	/* status register A */
I 2
#define  RTCSA_TUP	 0x80	/* time update, don't look now */
E 2

I 2
#define RTC_STATUSB	0x0b	/* status register B */

#define RTC_INTR	0x0c	/* status register C (R) interrupt source */
#define  RTCIR_UPDATE	 0x10	/* update intr */
#define  RTCIR_ALARM	 0x20	/* alarm intr */
#define  RTCIR_PERIOD	 0x40	/* periodic intr */
#define  RTCIR_INT	 0x80	/* interrupt output signal */

#define RTC_STATUSD	0x0d	/* status register D (R) Lost Power */
#define  RTCSD_PWR	 0x80	/* clock lost power */

#define RTC_DIAG	0x0e	/* status register E - bios diagnostic */
D 3
#define RTCDG_BITS	"\020\010clock battery\007ROM cksum\006config unit\005memory size\004fixed disk\003invalid time"
E 3
I 3
#define RTCDG_BITS	"\020\010clock_battery\007ROM_cksum\006config_unit\005memory_size\004fixed_disk\003invalid_time"
E 3

#define RTC_RESET	0x0f	/* status register F - reset code byte */
#define	 RTCRS_RST	 0x00		/* normal reset */
#define	 RTCRS_LOAD	 0x04		/* load system */

E 2
#define RTC_BASELO	0x15	/* low byte of basemem size */
#define RTC_BASEHI	0x16	/* high byte of basemem size */
#define RTC_EXTLO	0x17	/* low byte of extended mem size */
#define RTC_EXTHI	0x18	/* low byte of extended mem size */
I 2

#define RTC_CENTURY	0x32	/* current century - please increment in Dec99*/
E 2
E 1
