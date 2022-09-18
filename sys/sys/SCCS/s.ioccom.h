h64178
s 00010/00005/00033
d D 8.3 95/01/09 18:16:30 cgd 3 2
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00000/00005/00038
d D 8.2 94/03/28 10:00:49 bostic 2 1
c This is all stuff first added in 4.2BSD, according to Mike Karels.
e
s 00043/00000/00000
d D 8.1 94/03/28 07:34:06 bostic 1 0
c break termios.h, ioctl.h up into filio.h, sockio.h, ttycom.h
c termios.h, ioccom.h and ioctl.h, a la SunOS
c date and time created 94/03/28 07:34:06 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1982, 1986, 1990, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
D 2
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_SYS_IOCCOM_H_
#define	_SYS_IOCCOM_H_

/*
 * Ioctl's have the command encoded in the lower word, and the size of
 * any in or out parameters in the upper word.  The high 3 bits of the
 * upper word are used to encode the in/out status of the parameter.
 */
#define	IOCPARM_MASK	0x1fff		/* parameter length, at most 13 bits */
#define	IOCPARM_LEN(x)	(((x) >> 16) & IOCPARM_MASK)
#define	IOCBASECMD(x)	((x) & ~(IOCPARM_MASK << 16))
#define	IOCGROUP(x)	(((x) >> 8) & 0xff)

D 3
#define	IOCPARM_MAX	NBPG		/* max size of ioctl, mult. of NBPG */
#define	IOC_VOID	0x20000000	/* no parameters */
#define	IOC_OUT		0x40000000	/* copy out parameters */
#define	IOC_IN		0x80000000	/* copy in parameters */
E 3
I 3
#define	IOCPARM_MAX	NBPG	/* max size of ioctl args, mult. of NBPG */
				/* no parameters */
#define	IOC_VOID	(unsigned long)0x20000000
				/* copy parameters out */
#define	IOC_OUT		(unsigned long)0x40000000
				/* copy parameters in */
#define	IOC_IN		(unsigned long)0x80000000
				/* copy paramters in and out */
E 3
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
D 3
#define	IOC_DIRMASK	0xe0000000	/* mask for IN/OUT/VOID */
E 3
I 3
				/* mask for IN/OUT/VOID */
#define	IOC_DIRMASK	(unsigned long)0xe0000000
E 3

#define	_IOC(inout,group,num,len) \
	(inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))
/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))

#endif /* !_SYS_IOCCOM_H_ */
E 1
