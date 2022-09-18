h58497
s 00002/00002/00088
d D 8.1 93/06/10 21:24:06 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00005/00079
d D 7.4 92/06/05 15:23:24 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00001/00002/00083
d D 7.3 92/02/15 21:18:30 torek 3 2
c convert to use new select interface, selrecord/selwakeup
e
s 00001/00001/00084
d D 7.2 90/11/04 19:32:14 mckusick 2 1
c update identifier from Utah
e
s 00085/00000/00000
d D 7.1 90/05/08 22:06:42 mckusick 1 0
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
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: hilvar.h 1.1 89/08/22$
E 2
I 2
D 4
 * from: Utah $Hdr: hilvar.h 1.1 90/07/09$
E 4
I 4
 * from: Utah $Hdr: hilvar.h 1.3 92/01/21$
E 4
E 2
 *
 *	%W% (Berkeley) %G%
 */

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

#define NHILD		8		/* 7 actual + loop pseudo (dev 0) */
#define NHILQ		8		/* must be <= sizeof(int) */

#define HILBUFSIZE	40		/* size of interrupt poll buffer */
#define HILMAXCLIST	1024		/* max chars in clists for HPUX io */

#define HILLOOPDEV	0		/* loop device index */

/*
D 4
 * XXX: HPUX minor numbers are of the form "D0" where D is the device number
 * BSD uses "0D".  For compatibility we accept either.  Maybe we should just
 * use the HPUX numbering.
E 4
I 4
 * Minor device numbers.
 * HP-UX uses 12 bits of the form:
 *	LLLLDDDD0000
 * where L is 4 bits of loop number, D 4 bits of device and 4 bits of 0.
 * BSD uses 8 bits:
 *	LLLLDDDD
 * Device files are in BSD format, we map device numbers to HP-UX format
 * on stat calls.
E 4
 */
D 4
#define HILUNIT(d)	(((((d)>>4)&7)==0)?((d)&7):(((d)>>4)&7))
E 4
I 4
#define HILUNIT(d)	((d) & 0xF)
#define HILLOOP(d)	(((d)>>4) & 0xF)
E 4

#define	hildevmask(d)	(1 << (d))
#define	hilqmask(q)	(1 << (q))

struct hiliqueue {
	HILQ	*hq_eventqueue;		/* input queue shared with user */
	struct	proc *hq_procp;		/* process this queue belongs to */
	char	hq_devmask;		/* devices mapped to this queue */
};

struct hilloopdev {
	int	hd_flags;		/* device state */
	int	hd_qmask;		/* queues this device is mapped to */
	struct	clist hd_queue;		/* event queue for HPUX-style input */
D 3
	struct	proc *hd_selr;		/* process read selecting */
E 3
I 3
	struct	selinfo hd_selr;	/* process read selecting */
E 3
	uid_t	hd_uid;			/* uid of mapping process */
};

/* hd_flags */
#define	HIL_ALIVE	0x01	/* device is present */
#define HIL_PSEUDO	0x02	/* device is virtual */
#define HIL_READIN	0x04	/* device using read() input interface */
#define HIL_QUEUEIN	0x08	/* device using shared Q input interface */
D 3
#define HIL_SELCOLL	0x10	/* select collision on device */
E 3
#define HIL_NOBLOCK	0x20	/* device is in non-blocking read mode */
#define HIL_ASLEEP	0x40	/* process awaiting input on device */
#define HIL_DERROR	0x80	/* loop has reconfigured, reality altered */

struct hilloop {
	struct	hil_dev	*hl_addr;	/* base of hardware registers */
	u_char 	hl_cmddone;		/* */
	u_char 	hl_cmdending;		/* */
	u_char	hl_actdev;		/* current input device */
	u_char	hl_cmddev;		/* device to perform command on */
	u_char	hl_pollbuf[HILBUFSIZE];	/* interrupt time input buffer */
	u_char	hl_cmdbuf[HILBUFSIZE];	/* */
	u_char 	*hl_pollbp;		/* pointer into hl_pollbuf */
	u_char	*hl_cmdbp;		/* pointer into hl_cmdbuf */
	struct	hiliqueue hl_queue[NHILQ];	/* input queues */
	struct  hilloopdev hl_device[NHILD];	/* device data */
	u_char  hl_maxdev;		/* number of devices on loop */
	u_char	hl_kbddev;		/* keyboard device on loop */
	u_char	hl_kbdlang;		/* keyboard language */
	u_char	hl_kbdflags;		/* keyboard state */
};

/* hl_kbdflags */
#define KBD_RAW		0x01		/* keyboard is raw */
#define KBD_AR1		0x02		/* keyboard auto-repeat rate 1 */
#define KBD_AR2		0x04		/* keyboard auto-repeat rate 2 */
E 1
