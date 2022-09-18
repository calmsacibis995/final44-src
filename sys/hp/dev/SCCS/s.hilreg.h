h43691
s 00002/00002/00156
d D 8.1 93/06/10 21:24:02 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00005/00157
d D 7.5 92/10/11 08:55:11 bostic 5 4
c make kernel includes standard
e
s 00103/00052/00059
d D 7.4 92/06/05 15:23:23 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00004/00004/00107
d D 7.3 91/05/07 09:52:06 hibler 3 2
c 
e
s 00001/00001/00110
d D 7.2 90/11/04 19:31:46 mckusick 2 1
c update identifier from Utah
e
s 00111/00000/00000
d D 7.1 90/05/08 22:06:41 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: hilreg.h 1.8 89/08/24$
E 2
I 2
D 3
 * from: Utah $Hdr: hilreg.h 1.1 90/07/09$
E 3
I 3
D 4
 * from: Utah $Hdr: hilreg.h 1.9 91/01/21$
E 4
I 4
 * from: Utah $Hdr: hilreg.h 1.10 92/01/21$
E 4
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

I 4
D 5
#ifdef KERNEL
#include "hp/dev/iotypes.h"	/* XXX */
#else
#include <hp/dev/iotypes.h>	/* XXX */
#endif
E 5
I 5
#include <hp/dev/iotypes.h>		/* XXX */
E 5

#ifdef hp300
E 4
struct	hil_dev {
	char	hil_pad0;
D 4
	volatile char	hil_data;
E 4
I 4
	vu_char	hil_data;
E 4
	char	hil_pad1;
D 4
	volatile char	hil_cmd;
#define hil_stat hil_cmd
E 4
I 4
	vu_char	hil_cmd;
E 4
};

D 3
#define	HILADDR			((struct hil_dev *)IOV(0x428000))
#define BBCADDR			((struct hil_dev *)IOV(0x420000))  
E 3
I 3
#define	HILADDR			((struct hil_dev *)IIOV(0x428000))
D 4
#define BBCADDR			((struct hil_dev *)IIOV(0x420000))
E 4
I 4
#define	BBCADDR			((struct hil_dev *)IIOV(0x420000))
#endif
E 4
E 3

D 4
#define splhil			spl1
E 4
I 4
#ifdef hp800
#ifdef hp700
struct hil_dev {
	vu_char	hil_rsthold;	/* (WO) reset hold (and Serial #3) */
	vu_char	hil_resv1[2047];
	vu_char	hil_data;	/* send/receive data to/from 8042 */
	vu_char	hil_cmd;	/* status/control to/from 8042 */
	vu_char	hil_resv2[1022];
	vu_char	hil_rstrel;	/* (WO) reset release (and Serial #3) */
E 4

I 4
};
#else
struct	hil_dev {
	vu_int hil_data;
	vu_int hil_pad;
	vu_int hil_cmd;
};
#endif
#endif
#define hil_stat hil_cmd

#if defined(hp300) || defined(hp700)
#define READHILDATA(x)		((x)->hil_data)
#define READHILSTAT(x)		((x)->hil_stat)
#define READHILCMD(x)		((x)->hil_cmd)
#define WRITEHILDATA(x, y)	((x)->hil_data = (y))
#define WRITEHILSTAT(x, y)	((x)->hil_stat = (y))
#define WRITEHILCMD(x, y)	((x)->hil_cmd  = (y))
#else
#define READHILDATA(x)		((x)->hil_data >> 24)
#define READHILSTAT(x)		((x)->hil_stat >> 24)
#define READHILCMD(x)		((x)->hil_cmd  >> 24)
#define WRITEHILDATA(x, y)	((x)->hil_data = ((y) << 24))
#define WRITEHILSTAT(x, y)	((x)->hil_stat = ((y) << 24))
#define WRITEHILCMD(x, y)	((x)->hil_cmd  = ((y) << 24))
#endif

#ifdef hp300
#define splhil()		spl1()
#else
extern int hilspl;
#define splhil()		splx(hilspl)
#endif

E 4
#define	HIL_BUSY		0x02
D 4
#define HIL_DATA_RDY		0x01
E 4
I 4
#define	HIL_DATA_RDY		0x01
E 4

D 4
#define HILWAIT(hil_dev)	while ((hil_dev->hil_stat & HIL_BUSY))
#define HILDATAWAIT(hil_dev)	while ((hil_dev->hil_stat & HIL_DATA_RDY) == 0)
E 4
I 4
#define HILWAIT(hil_dev)	while ((READHILSTAT(hil_dev) & HIL_BUSY))
#define HILDATAWAIT(hil_dev)	while (!(READHILSTAT(hil_dev) & HIL_DATA_RDY))
E 4

/* HIL status bits */
#define	HIL_POLLDATA	0x10		/* HIL poll data follows */
D 4
#define HIL_COMMAND	0x08		/* Start of original command */
#define HIL_ERROR	0x080		/* HIL error */
#define HIL_RECONFIG	0x080		/* HIL has reconfigured */
E 4
I 4
#define	HIL_COMMAND	0x08		/* Start of original command */
#define	HIL_ERROR	0x080		/* HIL error */
#define	HIL_RECONFIG	0x080		/* HIL has reconfigured */
E 4
#define	HIL_STATMASK	(HIL_DATA | HIL_COMMAND)

D 4
#define HIL_SSHIFT		4	/* Bits to shift status over */
#define HIL_SMASK		0xF	/* Service request status mask */
#define HIL_DEVMASK		0x07
E 4
I 4
#define	HIL_SSHIFT	4		/* Bits to shift status over */
#define	HIL_SMASK	0xF		/* Service request status mask */
#define	HIL_DEVMASK	0x07
E 4

/* HIL status types */
#define	HIL_STATUS	0x5		/* HIL status in data register */
#define	HIL_DATA	0x6		/* HIL data in data register */
#define	HIL_CTRLSHIFT	0x8		/* key + CTRL + SHIFT */
#define	HIL_CTRL	0x9		/* key + CTRL */
#define	HIL_SHIFT	0xA		/* key + SHIFT */
#define	HIL_KEY		0xB		/* key only */
D 4
#define HIL_68K		0x4		/* Data from the 68k is ready */
E 4
I 4
#define	HIL_68K		0x4		/* Data from the 68k is ready */
E 4

/* HIL commands */
#define	HIL_SETARD	0xA0		/* set auto-repeat delay */
#define	HIL_SETARR	0xA2		/* set auto-repeat rate */
#define	HIL_SETTONE	0xA3		/* set tone generator */
D 4
#define HIL_CNMT	0xB2		/* clear nmi */
#define HIL_INTON	0x5C		/* Turn on interrupts. */
#define HIL_INTOFF	0x5D		/* Turn off interrupts. */
#define HIL_TRIGGER	0xC5		/* trigger command */
#define HIL_STARTCMD	0xE0		/* start loop command */
#define HIL_TIMEOUT	0xFE		/* timeout */
#define HIL_READTIME	0x13		/* Read real time register */
E 4
I 4
#define	HIL_CNMT	0xB2		/* clear nmi */
#define	HIL_INTON	0x5C		/* Turn on interrupts. */
#define	HIL_INTOFF	0x5D		/* Turn off interrupts. */
#define	HIL_TRIGGER	0xC5		/* trigger command */
#define	HIL_STARTCMD	0xE0		/* start loop command */
#define	HIL_TIMEOUT	0xFE		/* timeout */
#define	HIL_READTIME	0x13		/* Read real time register */
E 4

/* Read/write various registers on the 8042. */
#define	HIL_READBUSY		0x02	/* internal "busy" register */
D 4
#define HIL_READKBDLANG		0x12	/* read keyboard language code */
E 4
I 4
#define	HIL_READKBDLANG		0x12	/* read keyboard language code */
E 4
#define	HIL_READKBDSADR	 	0xF9
#define	HIL_WRITEKBDSADR 	0xE9
D 4
#define HIL_READLPSTAT  	0xFA
#define HIL_WRITELPSTAT 	0xEA
#define HIL_READLPCTRL  	0xFB
#define HIL_WRITELPCTRL 	0xEB
E 4
I 4
#define	HIL_READLPSTAT  	0xFA
#define	HIL_WRITELPSTAT 	0xEA
#define	HIL_READLPCTRL  	0xFB
#define	HIL_WRITELPCTRL 	0xEB
E 4

/* BUSY bits */
D 4
#define BSY_LOOPBUSY	0x04
E 4
I 4
#define	BSY_LOOPBUSY	0x04
E 4

/* LPCTRL bits */
D 4
#define LPC_AUTOPOLL	0x01	/* enable auto-polling */
#define LPC_NOERROR	0x02	/* don't report errors */
#define LPC_NORECONF	0x04	/* don't report reconfigure */
#define LPC_KBDCOOK	0x10	/* cook all keyboards */
#define LPC_RECONF	0x80	/* reconfigure the loop */
E 4
I 4
#define	LPC_AUTOPOLL	0x01	/* enable auto-polling */
#define	LPC_NOERROR	0x02	/* don't report errors */
#define	LPC_NORECONF	0x04	/* don't report reconfigure */
#define	LPC_KBDCOOK	0x10	/* cook all keyboards */
#define	LPC_RECONF	0x80	/* reconfigure the loop */
E 4

/* LPSTAT bits */
D 4
#define LPS_DEVMASK	0x07	/* number of loop devices */
#define LPS_CONFGOOD	0x08	/* reconfiguration worked */
#define LPS_CONFFAIL	0x80	/* reconfiguration failed */
E 4
I 4
#define	LPS_DEVMASK	0x07	/* number of loop devices */
#define	LPS_CONFGOOD	0x08	/* reconfiguration worked */
#define	LPS_CONFFAIL	0x80	/* reconfiguration failed */
E 4

/* HIL packet headers */
D 4
#define HIL_MOUSEDATA   0x2
#define HIL_KBDDATA     0x40
E 4
I 4
#define	HIL_MOUSEDATA   0x2
#define	HIL_KBDDATA     0x40
E 4
  
D 4
#define	HIL_MOUSEMOTION	0x02		/* mouse movement event */
#define	HIL_KBDBUTTON	0x40		/* keyboard button event */
#define HIL_MOUSEBUTTON 0x40            /* mouse button event */
#define HIL_BUTTONBOX   0x60            /* button box event */
#define HIL_TABLET      0x02            /* tablet motion event */
#define HIL_KNOBBOX     0x03            /* knob box motion data */
E 4
I 4
#define	HIL_MOUSEMOTION	0x02	/* mouse movement event */
#define	HIL_KBDBUTTON	0x40	/* keyboard button event */
#define	HIL_MOUSEBUTTON 0x40	/* mouse button event */
#define	HIL_BUTTONBOX   0x60	/* button box event */
#define	HIL_TABLET      0x02	/* tablet motion event */
#define	HIL_KNOBBOX     0x03	/* knob box motion data */
E 4

D 4
/* Magic */
D 3
#define KBDNMISTAT		((volatile char *)IOV(0x478005))
E 3
I 3
#define KBDNMISTAT		((volatile char *)IIOV(0x478005))
E 3
#define	KBDNMI			0x04

E 4
/* For setting auto repeat on the keyboard */
D 4
#define ar_format(x)	~((x - 10) / 10)
#define KBD_ARD		400		/* initial delay in msec (10 - 2560) */
#define KBD_ARR		60		/* rate (10 - 2550 msec, 2551 == off)*/
E 4
I 4
#define	ar_format(x)	~((x - 10) / 10)
#define	KBD_ARD		400	/* initial delay in msec (10 - 2560) */
#define	KBD_ARR		60	/* rate (10 - 2550 msec, 2551 == off) */

#ifdef hp300
/* Magic */
#define	KBDNMISTAT	((volatile char *)IIOV(0x478005))
#define	KBDNMI		0x04
#endif
E 4
E 1
