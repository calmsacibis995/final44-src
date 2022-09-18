h51562
s 00012/00006/00105
d D 8.5 95/01/09 18:16:20 cgd 40 39
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00015/00001/00096
d D 8.4 95/01/03 00:12:41 mckusick 39 38
c add device type field
e
s 00005/00000/00092
d D 8.3 94/01/21 17:25:05 bostic 38 37
c add USL's copyright notice
e
s 00004/00001/00088
d D 8.2 93/11/14 13:45:50 hibler 37 36
c convert sw_freed to sw_flags for SEQSWAP support
e
s 00000/00000/00089
d D 8.1 93/06/04 16:47:47 bostic 36 35
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00087
d D 7.13 93/06/04 16:32:56 sklower 35 33
c mistakenly thought that forward structure definitions required being
c hidden from pcc; backout change but put 1993 copyright date.
e
s 00002/00002/00087
d R 8.1 93/06/02 19:52:52 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00084
d D 7.12 92/07/20 13:51:20 bostic 33 32
c prettiness police
e
s 00012/00011/00075
d D 7.11 92/02/05 21:57:35 torek 32 31
c d_dump parameters vary; parametric routines for linesw;
c get rid of l_rend, l_meta
e
s 00004/00004/00082
d D 7.10 91/09/06 17:09:19 ralph 31 30
c add extern to zero dimention arrays.
e
s 00002/00004/00084
d D 7.9 91/05/05 08:29:32 karels 30 29
c remove proc param from cdev d_read/write, it's in the uio
e
s 00048/00036/00040
d D 7.8 91/04/20 12:49:03 karels 29 28
c add prototypes, fix formats
e
s 00020/00016/00056
d D 7.7 91/03/17 15:33:58 karels 28 27
c more-or-less working with new proc & user structs
e
s 00050/00067/00022
d D 7.6 91/02/15 14:27:19 bostic 27 26
c add Berkeley specific copyright notice
e
s 00005/00001/00084
d D 7.5 90/04/04 22:21:54 karels 26 25
c add strings for sleep messages; increase ttyhog to 1K
e
s 00001/00000/00084
d D 7.4 89/05/09 16:13:20 mckusick 25 24
c merge in vnodes
e
s 00001/00000/00083
d D 7.3 88/05/14 11:25:47 karels 24 23
c raw read/write support from torek: add strategy to cdevsw, B_RAW flag
e
s 00001/00000/00082
d D 7.2 87/04/02 15:36:22 karels 23 21
c working again
e
s 00005/00000/00082
d D 7.1.1.1 87/04/02 15:17:34 karels 22 21
c ifdef for dev_bsize
e
s 00001/00001/00081
d D 7.1 86/06/04 23:20:49 mckusick 21 20
c 4.3BSD release version
e
s 00007/00001/00075
d D 6.2 85/06/08 14:55:24 mckusick 20 19
c Add copyright
e
s 00000/00000/00076
d D 6.1 83/07/29 06:11:56 sam 19 18
c 4.2 distribution
e
s 00002/00000/00074
d D 4.11 83/05/18 02:11:29 sam 18 17
c stuff for variable sized swap partitions (note addition to bdevsw)
e
s 00001/00000/00073
d D 4.10 82/10/31 15:53:00 root 17 16
c add d_mmap (from 68k)
e
s 00001/00001/00072
d D 4.9 82/10/17 12:03:51 root 16 15
c l_write routine returns error not a char *
e
s 00001/00000/00072
d D 4.8 81/10/17 16:14:03 wnj 15 14
c cleanup (mpx removal, old tty removal, beginnings of select)
e
s 00001/00001/00071
d D 4.7 81/04/03 14:52:30 root 14 13
c cosmetics for pstats sake
e
s 00018/00010/00054
d D 4.6 81/03/09 00:26:50 wnj 13 12
c lint
e
s 00001/00001/00063
d D 4.5 81/02/19 21:39:40 wnj 12 11
c %G%->%E%
e
s 00001/00001/00063
d D 4.4 81/02/15 12:15:13 kre 11 10
c d_tab ->d_flags
e
s 00001/00000/00063
d D 4.3 81/02/03 23:42:42 wnj 10 9
c added d_dump
e
s 00004/00000/00059
d D 4.2 81/01/26 20:42:24 wnj 9 8
c chaos
e
s 00000/00000/00059
d D 4.1 80/11/09 17:00:44 bill 8 7
c stamp for 4bsd
e
s 00009/00000/00050
d D 3.7 80/07/01 08:17:04 bill 7 6
c various minor fixups pre-split to dev dir
e
s 00001/00000/00049
d D 3.6 80/06/22 12:39:08 bill 6 5
c added d_reset
e
s 00001/00001/00048
d D 3.5 80/06/07 02:56:47 bill 5 4
c %H%->%G%
e
s 00000/00004/00049
d D 3.4 80/05/15 17:17:05 bill 4 3
c new tty discipline
e
s 00001/00001/00052
d D 3.3 80/05/08 10:41:34 bill 3 2
c BNELDIS=>NETLDISC
e
s 00004/00000/00049
d D 3.2 80/05/08 10:15:38 bill 2 1
c addition for netldis
e
s 00049/00000/00000
d D 3.1 80/04/09 16:23:35 bill 1 0
c date and time created 80/04/09 16:23:35 by bill
e
u
U
f b 
t
T
I 1
D 5
/*	%M%	%I%	%H%	*/
E 5
I 5
D 12
/*	%M%	%I%	%G%	*/
E 12
I 12
D 20
/*	%M%	%I%	%E%	*/
E 20
I 20
D 27
/*
D 21
 * Copyright (c) 1982 Regents of the University of California.
E 21
I 21
D 26
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 26
I 26
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
E 26
E 21
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 27
I 27
/*-
D 35
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 35
I 35
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 38
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 38
E 35
E 27
 *
I 27
 * %sccs.include.redist.c%
 *
E 27
 *	%W% (Berkeley) %G%
 */
E 20
E 12
E 5

I 29
/*
 * Definitions of device driver entry switches
 */

D 33
#ifdef __STDC__
E 33
I 33
struct buf;
struct proc;
E 33
struct tty;
D 33
#endif
E 33
I 33
struct uio;
struct vnode;
E 33

I 39
/*
 * Types for d_type.
 */
#define	D_TAPE	1
#define	D_DISK	2
#define	D_TTY	3

/*
 * Block device switch table
 */
E 39
E 29
D 27
/*
 * Declaration of block device
 * switch. Each entry (row) is
 * the only link between the
 * main unix code and the driver.
 * The initialization of the
 * device switches is in the
 * file conf.c.
 */
D 13
extern struct bdevsw
E 13
I 13
struct bdevsw
E 13
{
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_strategy)();
I 23
	int	(*d_ioctl)();
E 23
I 22
	int	(*d_ioctl)();
E 22
I 10
	int	(*d_dump)();
I 18
	int	(*d_psize)();
E 18
E 10
D 11
	struct buf *d_tab;
E 11
I 11
	int	d_flags;
E 27
I 27
struct bdevsw {
D 28
	int (*d_open)();
	int (*d_close)();
	int (*d_strategy)();
	int (*d_ioctl)();
	int (*d_dump)();
	int (*d_psize)();
E 28
I 28
D 29
	int (*d_open)	__P((dev_t dev, int mode, int devtype, struct proc *p));
	int (*d_close)	__P((dev_t dev, int fflag, int devtype, struct proc *));
	int (*d_strategy) __P((struct buf *bp));
	int (*d_ioctl)	__P((dev_t dev, int cmd, caddr_t data, int fflag,
				struct proc *p));
	int (*d_dump)	__P((dev_t dev));
	int (*d_psize)	__P((dev_t dev));
E 28
	int d_flags;
E 29
I 29
	int	(*d_open)	__P((dev_t dev, int oflags, int devtype,
				     struct proc *p));
	int	(*d_close)	__P((dev_t dev, int fflag, int devtype,
D 33
				     struct proc *));
E 33
I 33
				     struct proc *p));
E 33
D 40
	int	(*d_strategy)	__P((struct buf *bp));
	int	(*d_ioctl)	__P((dev_t dev, int cmd, caddr_t data,
E 40
I 40
	void	(*d_strategy)	__P((struct buf *bp));
	int	(*d_ioctl)	__P((dev_t dev, u_long cmd, caddr_t data,
E 40
				     int fflag, struct proc *p));
D 32
	int	(*d_dump)	__P((dev_t dev));
E 32
I 32
	int	(*d_dump)	();	/* parameters vary by architecture */
E 32
	int	(*d_psize)	__P((dev_t dev));
D 39
	int	d_flags;
E 39
I 39
	int	d_type;
E 39
E 29
E 27
E 11
D 13
} bdevsw[];
E 13
I 13
};
I 27

E 27
#ifdef KERNEL
D 27
struct	bdevsw bdevsw[];
E 27
I 27
D 31
struct bdevsw bdevsw[];
E 31
I 31
extern struct bdevsw bdevsw[];
E 31
E 27
#endif
E 13

I 39
/*
 * Character device switch table
 */
E 39
D 27
/*
 * Character device switch.
 */
D 13
extern struct cdevsw
E 13
I 13
struct cdevsw
E 13
{
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_read)();
	int	(*d_write)();
	int	(*d_ioctl)();
	int	(*d_stop)();
I 6
	int	(*d_reset)();
E 27
I 27
struct cdevsw {
D 28
	int (*d_open)();
	int (*d_close)();
	int (*d_read)();
	int (*d_write)();
	int (*d_ioctl)();
	int (*d_stop)();
	int (*d_reset)();
E 28
I 28
D 29
	int (*d_open)	__P((dev_t dev, int mode, int devtype, struct proc *p));
	int (*d_close)	__P((dev_t dev, int fflag, int devtype, struct proc *));
	int (*d_read)	__P((dev_t dev, struct uio *uio, int ioflag,
				struct proc *p));
	int (*d_write)	__P((dev_t dev, struct uio *uio, int ioflag,
				struct proc *p));
	int (*d_ioctl)	__P((dev_t dev, int cmd, caddr_t data, int fflag,
				struct proc *p));
	int (*d_stop)	__P((struct tty *tp, int rw));
	int (*d_reset)	__P((int uban));	/* XXX */
E 28
E 27
E 6
	struct tty *d_ttys;
I 15
D 27
	int	(*d_select)();
I 17
	int	(*d_mmap)();
I 24
	int	(*d_strategy)();
E 24
E 17
E 15
D 13
} cdevsw[];
E 13
I 13
};
E 27
I 27
D 28
	int (*d_select)();
	int (*d_mmap)();
	int (*d_strategy)();
E 28
I 28
	int (*d_select)	__P((dev_t dev, int which, struct proc *p));
	int (*d_mmap)	__P((dev_t dev, ...));
	int (*d_strategy) __P((struct buf *bp));
E 29
I 29
	int	(*d_open)	__P((dev_t dev, int oflags, int devtype,
				     struct proc *p));
	int	(*d_close)	__P((dev_t dev, int fflag, int devtype,
				     struct proc *));
D 30
	int	(*d_read)	__P((dev_t dev, struct uio *uio, int ioflag,
				     struct proc *p));
	int	(*d_write)	__P((dev_t dev, struct uio *uio, int ioflag,
				     struct proc *p));
E 30
I 30
	int	(*d_read)	__P((dev_t dev, struct uio *uio, int ioflag));
	int	(*d_write)	__P((dev_t dev, struct uio *uio, int ioflag));
E 30
D 40
	int	(*d_ioctl)	__P((dev_t dev, int cmd, caddr_t data,
E 40
I 40
	int	(*d_ioctl)	__P((dev_t dev, u_long cmd, caddr_t data,
E 40
				     int fflag, struct proc *p));
	int	(*d_stop)	__P((struct tty *tp, int rw));
	int	(*d_reset)	__P((int uban));	/* XXX */
	struct	tty *d_ttys;
	int	(*d_select)	__P((dev_t dev, int which, struct proc *p));
	int	(*d_mmap)	__P(());
D 40
	int	(*d_strategy)	__P((struct buf *bp));
E 40
I 40
	void	(*d_strategy)	__P((struct buf *bp));
E 40
I 39
	int	d_type;
E 39
E 29
E 28
};

E 27
#ifdef KERNEL
D 27
struct	cdevsw cdevsw[];
E 27
I 27
D 31
struct cdevsw cdevsw[];
E 31
I 31
extern struct cdevsw cdevsw[];
E 31
E 27
I 26

/* symbolic sleep message strings */
D 27
extern	 char devopn[], devio[], devwait[];
extern	 char devin[], devout[], devioc[], devcls[];
E 27
I 27
extern char devopn[], devio[], devwait[], devin[], devout[];
extern char devioc[], devcls[];
E 27
E 26
#endif
E 13

I 40
/*
 * Line discipline switch table
 */
E 40
D 27
/*
 * tty line control switch.
 */
D 13
extern struct linesw
E 13
I 13
struct linesw
E 13
{
	int	(*l_open)();
	int	(*l_close)();
	int	(*l_read)();
D 16
	char	*(*l_write)();
E 16
I 16
	int	(*l_write)();
E 16
	int	(*l_ioctl)();
	int	(*l_rint)();
	int	(*l_rend)();
	int	(*l_meta)();
	int	(*l_start)();
	int	(*l_modem)();
E 27
I 27
struct linesw {
D 29
	int (*l_open)();
	int (*l_close)();
	int (*l_read)();
	int (*l_write)();
	int (*l_ioctl)();
	int (*l_rint)();
	int (*l_rend)();
	int (*l_meta)();
	int (*l_start)();
	int (*l_modem)();
E 29
I 29
D 32
	int	(*l_open)();
	int	(*l_close)();
	int	(*l_read)();
	int	(*l_write)();
	int	(*l_ioctl)();
	int	(*l_rint)();
	int	(*l_rend)();
	int	(*l_meta)();
	int	(*l_start)();
	int	(*l_modem)();
E 32
I 32
	int	(*l_open)	__P((dev_t dev, struct tty *tp));
	int	(*l_close)	__P((struct tty *tp, int flag));
	int	(*l_read)	__P((struct tty *tp, struct uio *uio,
				     int flag));
	int	(*l_write)	__P((struct tty *tp, struct uio *uio,
				     int flag));
D 40
	int	(*l_ioctl)	__P((struct tty *tp, int cmd, caddr_t data,
E 40
I 40
	int	(*l_ioctl)	__P((struct tty *tp, u_long cmd, caddr_t data,
E 40
				     int flag, struct proc *p));
	int	(*l_rint)	__P((int c, struct tty *tp));
	int	(*l_start)	__P((struct tty *tp));
	int	(*l_modem)	__P((struct tty *tp, int flag));
E 32
E 29
E 27
D 13
} linesw[];
E 13
I 13
};
I 27

E 27
#ifdef KERNEL
D 27
struct	linesw linesw[];
E 27
I 27
D 31
struct linesw linesw[];
E 31
I 31
extern struct linesw linesw[];
E 31
E 27
#endif
E 13
I 7

I 40
/*
 * Swap device table
 */
E 40
D 27
/*
 * Swap device information
 */
D 13
extern struct swdevt
E 13
I 13
struct swdevt
E 13
{
	dev_t	sw_dev;
	int	sw_freed;
I 18
	int	sw_nblks;
E 27
I 27
struct swdevt {
D 29
	dev_t sw_dev;
	int sw_freed;
	int sw_nblks;
E 27
I 25
	struct vnode *sw_vp;
E 29
I 29
	dev_t	sw_dev;
D 37
	int	sw_freed;
E 37
I 37
	int	sw_flags;
E 37
	int	sw_nblks;
	struct	vnode *sw_vp;
E 29
E 25
I 22
#ifdef SECSIZE
	int	sw_blksize;
	int	sw_bshift;
#endif SECSIZE
E 22
E 18
D 14
} swdevt[];
E 14
I 14
};
I 37
#define	SW_FREED	0x01
#define	SW_SEQUENTIAL	0x02
D 40
#define sw_freed	sw_flags	/* XXX compat */
E 40
I 40
#define	sw_freed	sw_flags	/* XXX compat */
E 40
E 37
I 27

E 27
E 14
I 9
D 13

#ifdef	CHAOS
extern int cdevpath;
E 13
I 13
#ifdef KERNEL
D 27
struct	swdevt swdevt[];
E 27
I 27
D 31
struct swdevt swdevt[];
E 31
I 31
extern struct swdevt swdevt[];
E 31
E 27
E 13
#endif
E 9
E 7
I 2
D 4

#ifdef BERKNET
D 3
#define	BNETLDIS	1		/* line discip for berk net */
E 3
I 3
#define	NETLDISC	1		/* line discip for berk net */
E 3
#endif
E 4
E 2
E 1
