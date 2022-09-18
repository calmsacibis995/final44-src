h64130
s 00002/00002/00170
d D 8.1 93/06/10 21:23:58 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00010/00157
d D 7.6 92/12/27 09:11:26 hibler 6 5
c hardwire values for troublesome ioctls
e
s 00011/00006/00156
d D 7.5 92/06/05 15:23:21 hibler 5 4
c merge latest Utah hp300 code including 68040 support
e
s 00009/00002/00153
d D 7.4 92/05/01 13:55:43 bostic 4 3
c Older versions of gcc padded odd byte-count structures that didn't
c contain anything but chars to even boundaries.  Newer versions don't, so these
c values were changed.  Hard-code them in place
e
s 00003/00001/00152
d D 7.3 92/03/19 17:33:37 marc 3 2
c add commented hardcoded values for two ioctls -- WHY?  (ask sklower)
e
s 00001/00001/00152
d D 7.2 90/11/04 19:31:17 mckusick 2 1
c update identifier from Utah
e
s 00153/00000/00000
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
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: hilioctl.h 1.9 89/01/18$
E 2
I 2
D 5
 * from: Utah $Hdr: hilioctl.h 1.1 90/07/09$
E 5
I 5
 * from: Utah $Hdr: hilioctl.h 1.10 92/01/21$
E 5
E 2
 *
 *	%W% (Berkeley) %G%
 */

struct _hilbell {
	u_char	duration;
	u_char	frequency;
};

struct _hilbuf16 {
	u_char	string[16];
};

struct _hilbuf11 {
	u_char	string[11];
};

struct _hilbuf5 {
  	u_char  string[5];
};

struct _hilbuf4 {
  	u_char  string[4];
};

struct _hilbuf2 {
	u_char	string[2];
};

struct hilqinfo {
	int	qid;
	char	*addr;
};

/*
 * HPUX ioctls (here for the benefit of the HIL driver).
 * Named as they are under HPUX.
 * The first set are loop device ioctls.
 * The second set are ioctls for the 8042.
 * Note that some are not defined as in HPUX
 * due to the difference in the definitions of IOC_VOID.
 */
I 5
#ifdef hp800
#define _IOHpux(x,y)	_IO(x,y)
#else
E 5
#define _IOHpux(x,y)	(IOC_IN|((x)<<8)|y)	/* IOC_IN is IOC_VOID */
I 5
#endif
E 5

I 4
D 6
#ifdef ORIGINAL_HP_CODE_ASSUMES_COMPILER_PADS_TO_EVEN
E 4
#define HILID	_IOR('h',0x03, struct _hilbuf11) /* Identify & describe */
I 3
D 4
/*#define HILID   0x400c6803*/
E 4
I 4
#else
#define HILID   0x400c6803
#endif
E 6
I 6
/*
 * The HP compiler (at least as of HP-UX 7.X) pads odd sized structures
 * to a short boundary.  To avoid issues of whether our compiler pads
 * and, if so to what boundary, we explicitly state the values for
 * troublesome ioctls:
 *
 *	HILID (HILIOCID)	_IOR('h',0x03, struct _hilbuf11),
 *	EFTRRT (HILIOCRRT)	_IOR('H',0x31, struct _hilbuf5).
 */
#define HILID	0x400C6803			/* Identify & describe */
E 6
D 5

E 5
E 4
E 3
#define HILSC	_IOR('h',0x33, struct _hilbuf16) /* Security code */
#define HILRN	_IOR('h',0x30, struct _hilbuf16) /* Report name */
#define HILRS	_IOR('h',0x31, struct _hilbuf16) /* Report status */
#define HILED	_IOR('h',0x32, struct _hilbuf16) /* Extended describe*/
#define HILDKR  _IOHpux('h',0x3D)		/* Disable autorepeat */
#define HILER1  _IOHpux('h',0x3E)		/* Autorepeat 1/30 */
#define HILER2  _IOHpux('h',0x3F)		/* Autorepeat 1/60 */
#define HILP1	_IOHpux('h',0x40)		/* Prompt 1 */
#define HILP2	_IOHpux('h',0x41)		/* Prompt 2 */
#define HILP3	_IOHpux('h',0x42)		/* Prompt 3 */
#define HILP4	_IOHpux('h',0x43)		/* Prompt 4 */
#define HILP5	_IOHpux('h',0x44)		/* Prompt 5 */
#define HILP6	_IOHpux('h',0x45)		/* Prompt 6 */
#define HILP7	_IOHpux('h',0x46)		/* Prompt 7 */
#define HILP	_IOHpux('h',0x47)		/* Prompt */
#define HILA1	_IOHpux('h',0x48)		/* Acknowledge 1 */
#define HILA2	_IOHpux('h',0x49)		/* Acknowledge 2 */
#define HILA3	_IOHpux('h',0x4A)		/* Acknowledge 3 */
#define HILA4	_IOHpux('h',0x4B)		/* Acknowledge 4 */
#define HILA5	_IOHpux('h',0x4C)		/* Acknowledge 5 */
#define HILA6	_IOHpux('h',0x4D)		/* Acknowledge 6 */
#define HILA7	_IOHpux('h',0x4E)		/* Acknowledge 7 */
#define HILA	_IOHpux('h',0x4F)		/* Acknowledge */

#define EFTSRD  _IOW('H',0xa0,char)		/* Set the repeat delay. */
#define EFTSRR  _IOW('H',0xa2,char)		/* Set the repeat rate. */
#define EFTSRPG _IOW('H',0xa6,char)		/* Set RPG interrupt rate. */
#define EFTSBP  _IOW('H',0xc4,struct _hilbuf4)	/* Send data to the beeper. */
#define EFTRLC  _IOR('H',0x12,char)		/* Read the language code. */
#define EFTRCC  _IOR('H',0x11,char)		/* Read configuration code. */
I 4
D 5
#ifdef ORIGINAL_HP_CODE_ASSUMES_COMPILER_PADS_TO_EVEN
E 4
D 3
#define EFTRRT  _IOR('H',0x31,struct _hilbuf5)	/* Read the real time. */
E 3
I 3
#define EFTRRT  _IOR('H',0x31,struct _hilbuf5)/* Read the real time. */
D 4
/*#define EFTRRT	0x40064831*/
E 4
I 4
#else
E 5
I 5
D 6
/*#define EFTRRT  _IOR('H',0x31,struct _hilbuf5)/* Read the real time. */
E 5
#define EFTRRT	0x40064831
E 6
I 6
#define EFTRRT  0x40064831			/* Read the real time. */
E 6
D 5
#endif
E 5
E 4
E 3
#define EFTRT   _IOR('H',0xf4,struct _hilbuf4)	/* Read the timers for the
	                                              four voices. */
I 5
#ifdef hp800
#define EFTSBI  _IOW('H',0xa3,char)		/* Do the beep thing. */
#else
E 5
#define EFTSBI  _IOW('H',0xa3,struct _hilbuf2)	/* Set the bell information. */
I 5
#endif
E 5

/*
 * BSD ioctls.
 * Mostly the same as the HPUX versions except for shared-queue ioctls.
 */
D 6
#define HILIOCID	_IOR('h',0x03, struct _hilbuf11)
I 5
#define OHILIOCID	HILID
E 6
I 6
#define OHILIOCID	0x400B6803		/* XXX compat */
#define HILIOCID	HILID
E 6
E 5
#define HILIOCSC	_IOR('h',0x33, struct _hilbuf16)
#define HILIOCRN	_IOR('h',0x30, struct _hilbuf16)
#define HILIOCRS	_IOR('h',0x31, struct _hilbuf16)
#define HILIOCED	_IOR('h',0x32, struct _hilbuf16)
#define HILIOCAROFF	_IO('h',0x3D)
#define HILIOCAR1	_IO('h',0x3E)
#define HILIOCAR2	_IO('h',0x3F)
#define HILIOCSBP	_IOW('H',0xc4,struct _hilbuf4)
D 6
#define HILIOCRRT	_IOR('H',0x31,struct _hilbuf5)
E 6
I 6
#define OHILIOCRRT	0x40054831		/* XXX compat */
#define HILIOCRRT	EFTRRT
E 6
#define HILIOCRT	_IOR('H',0xf4,struct _hilbuf4)
#define HILIOCBEEP	_IOW('H',0xA3,struct _hilbell)
#	define	BELLDUR		80	/* tone duration in msec (10 - 2560) */
#	define	BELLFREQ	8	/* tone frequency (0 - 63) */

#define HILIOCALLOCQ	_IOWR('H',0x72, struct hilqinfo)	/* allocate queue */
#define HILIOCFREEQ	_IOW('H',0x73, struct hilqinfo)	/* deallocate queue */
#define HILIOCMAPQ	_IOW('H',0x74, int)	/* map device to queue */
#define HILIOCUNMAPQ	_IOW('H',0x75, int)	/* unmap device from dev */
#define HILIOCTEST      _IOW('H',0x76, int)	/* Toggle debugging mode */
#define HILIOCHPUX	_IO('H',0x77)		/* use HPUX (read) semantics */
#define HILIOCRESET	_IO('H',0x78)		/* Reset the HIL loop. */

/*
 * HIL input queue.
 * This is the circular queue (allocated by HILIOCALLOC) shared by kernel
 * and user.  It consists of a sixteen byte header followed by space for
 * 255 input data packets (a total of 4096 bytes).  The kernel adds packets
 * at tail.  The user is expected to remove packets from head.  This is the
 * only field in the header that the user should modify.
 */
typedef struct hil_packet {
	u_char	size;		/* total packet size */
	u_char	dev;		/* loop device packet was generated by */
	long	tstamp;		/* time stamp */
	u_char	data[10];	/* device data */
} hil_packet;

typedef struct hil_eventqueue {
	int	size;
	int	head;
	int	tail;
	int	pad;
} hil_eventqueue;

typedef union hilqueue {
	char	hqu_size[0x1000];
	struct	q_data {
		hil_eventqueue	h_eventqueue;
		hil_packet	h_event[1];
	} q_data;
#define hil_evqueue	q_data.h_eventqueue
#define hil_event	q_data.h_event
} HILQ;

#define HEVQSIZE	\
	((sizeof(HILQ) - sizeof(struct q_data)) / sizeof(hil_packet) + 1)
E 1
