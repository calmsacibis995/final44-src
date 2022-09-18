h08338
s 00004/00004/00096
d D 8.5 95/01/09 18:22:37 cgd 27 26
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00005/00000/00095
d D 8.4 94/01/21 17:18:02 bostic 26 25
c add USL's copyright notice
e
s 00001/00001/00094
d D 8.3 93/09/23 15:41:51 bostic 25 24
c changes for 4.4BSD-Lite requested by USL
e
s 00000/00008/00095
d D 8.2 93/09/05 09:39:25 bostic 24 23
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00101
d D 8.1 93/06/10 21:59:12 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00014/00089
d D 7.10 93/05/27 20:46:39 torek 22 21
c fully bracket those initializers, for gcc2 -W
e
s 00007/00007/00096
d D 7.9 92/10/11 10:38:38 bostic 21 20
c make kernel includes standard
e
s 00001/00000/00102
d D 7.8 92/02/15 17:32:34 mckusick 20 19
c must include proc before tty.h and socketvar.h
e
s 00045/00020/00057
d D 7.7 92/02/05 22:22:24 torek 19 18
c function prototypes; get rid of l_meta, l_rend
e
s 00005/00004/00072
d D 7.6 91/05/09 21:21:36 bostic 18 17
c new copyright; att/bsd/shared
e
s 00016/00018/00060
d D 7.5 91/02/28 13:17:48 mckusick 17 16
c nodev => enodev; nulldev => nullop
e
s 00003/00011/00075
d D 7.4 89/05/01 23:02:55 marc 16 15
c delete BK line discipline
e
s 00009/00006/00077
d D 7.3 88/10/18 15:16:41 marc 15 14
c new terminal driver
e
s 00001/00001/00082
d D 7.2 88/05/26 08:56:12 karels 14 13
c SLIP needs nullmodem (and then lint is happy, too)
e
s 00001/00001/00082
d D 7.1 86/06/05 00:09:49 mckusick 13 12
c 4.3BSD release version
e
s 00016/00004/00067
d D 6.9 86/02/10 08:39:15 karels 12 11
c serial IP
e
s 00000/00007/00071
d D 6.8 85/11/06 18:27:54 sam 11 10
c don't need extra line discpline slot for tablet now since ioctl 
c sets tablet type
e
s 00000/00011/00078
d D 6.7 85/11/06 10:11:10 karels 10 9
c move nullmodem to tty.c, maintain TS_CARR_ON
e
s 00020/00009/00069
d D 6.6 85/11/04 18:10:58 karels 9 8
c use modem entry in linesw to signal carrier change; split line-disc close
c from tty close
e
s 00007/00001/00071
d D 6.5 85/06/08 14:46:42 mckusick 8 7
c Add copyright
e
s 00001/00000/00071
d D 6.4 84/12/21 13:56:20 bloom 7 6
c include ioctl.h
e
s 00005/00005/00066
d D 6.3 84/08/29 20:23:03 bloom 6 5
c Change to includes.  no more ../h
e
s 00001/00001/00070
d D 6.2 83/09/25 12:47:19 karels 5 4
c ldisc 0 close is nulldev, not nodev
e
s 00000/00000/00071
d D 6.1 83/07/29 06:39:26 sam 4 3
c 4.2 distribution
e
s 00017/00000/00054
d D 4.3 83/05/27 12:48:41 sam 3 2
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00001/00003/00053
d D 4.2 82/10/17 11:33:26 root 2 1
c nldisp computed
e
s 00056/00000/00000
d D 4.1 82/10/17 00:15:21 root 1 0
c date and time created 82/10/17 00:15:21 by root
e
u
U
t
T
I 1
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
D 18
/*
D 13
 * Copyright (c) 1982 Regents of the University of California.
E 13
I 13
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 13
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
/*-
D 23
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 26
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 26
E 23
 *
 * %sccs.include.redist.c%
E 18
 *
 *	%W% (Berkeley) %G%
 */
E 8

D 6
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/buf.h"
#include "../h/tty.h"
#include "../h/conf.h"
E 6
I 6
D 21
#include "param.h"
#include "systm.h"
#include "buf.h"
I 7
#include "ioctl.h"
I 20
#include "proc.h"
E 20
E 7
#include "tty.h"
#include "conf.h"
E 21
I 21
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/conf.h>
E 21
E 6

D 17
int	nodev();
int	nulldev();
E 17
I 17
D 19
int	enodev();
int	nullop();
E 19
I 19
#define	ttynodisc ((int (*) __P((dev_t, struct tty *)))enodev)
#define	ttyerrclose ((int (*) __P((struct tty *, int flags)))enodev)
#define	ttyerrio ((int (*) __P((struct tty *, struct uio *, int)))enodev)
#define	ttyerrinput ((int (*) __P((int c, struct tty *)))enodev)
#define	ttyerrstart ((int (*) __P((struct tty *)))enodev)
E 19
E 17

D 9
int	ttyopen(),ttyclose(),ttread(),ttwrite(),nullioctl(),ttstart();
int	ttyinput();
E 9
I 9
D 19
int	ttyopen(),ttylclose(),ttread(),ttwrite(),nullioctl(),ttstart();
int	ttymodem(), nullmodem(), ttyinput();
E 19
I 19
D 24
int	ttyopen __P((dev_t dev, struct tty *tp));
int	ttylclose __P((struct tty *tp, int flags));
int	ttread __P((struct tty *, struct uio *, int flags));
int	ttwrite __P((struct tty *, struct uio *, int flags));
E 24
D 27
int	nullioctl __P((struct tty *tp, int cmd, caddr_t data,
E 27
I 27
int	nullioctl __P((struct tty *tp, u_long cmd, caddr_t data,
E 27
			int flag, struct proc *p));
D 24
int	ttyinput __P((int c, struct tty *tp));
int	ttstart __P((struct tty *tp));
int	ttymodem __P((struct tty *tp, int flags));
int	nullmodem __P((struct tty *tp, int flags));
E 24
E 19
E 9

I 15
D 17
int	ottyopen(), ottylclose(), ottread(), ottwrite();
int	ottyinput(), ottstart(), ottymodem();

E 17
E 15
D 16
#include "bk.h"
#if NBK > 0
int	bkopen(),bkclose(),bkread(),bkinput(),bkioctl();
#endif

E 16
#include "tb.h"
#if NTB > 0
D 19
int	tbopen(),tbclose(),tbread(),tbinput(),tbioctl();
E 19
I 19
int	tbopen __P((dev_t dev, struct tty *tp));
int	tbclose __P((struct tty *tp, int flags));
int	tbread __P((struct tty *, struct uio *, int flags));
D 27
int	tbioctl __P((struct tty *tp, int cmd, caddr_t data,
E 27
I 27
int	tbioctl __P((struct tty *tp, u_long cmd, caddr_t data,
E 27
			int flag, struct proc *p));
int	tbinput __P((int c, struct tty *tp));
E 19
#endif
I 17

E 17
I 12
#include "sl.h"
#if NSL > 0
D 19
int	slopen(),slclose(),slinput(),sltioctl(),slstart();
E 19
I 19
int	slopen __P((dev_t dev, struct tty *tp));
int	slclose __P((struct tty *tp, int flags));
D 27
int	sltioctl __P((struct tty *tp, int cmd, caddr_t data,
E 27
I 27
int	sltioctl __P((struct tty *tp, u_long cmd, caddr_t data,
E 27
			int flag, struct proc *p));
int	slinput __P((int c, struct tty *tp));
int	slstart __P((struct tty *tp));
E 19
#endif
E 12

I 12

E 12
struct	linesw linesw[] =
{
D 5
	ttyopen, nodev, ttread, ttwrite, nullioctl,
E 5
I 5
D 9
	ttyopen, nulldev, ttread, ttwrite, nullioctl,
E 5
	ttyinput, nodev, nulldev, ttstart, nulldev,
E 9
I 9
D 12
	ttyopen, ttylclose, ttread, ttwrite, nullioctl,
E 12
I 12
D 15
	ttyopen, ttylclose, ttread, ttwrite, nullioctl,	/* 0- OTTYDISC */
E 12
	ttyinput, nodev, nulldev, ttstart, ttymodem,
E 15
I 15
D 22
	ttyopen, ttylclose, ttread, ttwrite, nullioctl,
D 17
	ttyinput, nodev, nulldev, ttstart, ttymodem,	/* 0- termios */
E 17
I 17
D 19
	ttyinput, enodev, nullop, ttstart, ttymodem,	/* 0- termios */
E 19
I 19
	ttyinput, ttstart, ttymodem,			/* 0- termios */
E 22
I 22
	{ ttyopen, ttylclose, ttread, ttwrite, nullioctl,
	  ttyinput, ttstart, ttymodem },		/* 0- termios */
E 22
E 19
E 17
E 15
E 9
D 16
#if NBK > 0
D 12
	bkopen, bkclose, bkread, ttwrite, bkioctl,
E 12
I 12
D 15
	bkopen, bkclose, bkread, ttwrite, bkioctl,	/* 1- NETLDISC */
E 12
D 9
	bkinput, nodev, nulldev, ttstart, nulldev,
E 9
I 9
	bkinput, nodev, nulldev, ttstart, nullmodem,
E 15
I 15
	bkopen, bkclose, bkread, ttwrite, bkioctl,
	bkinput, nodev, nulldev, ttstart, nullmodem,	/* 1- NETLDISC */
E 15
E 9
#else
E 16
I 16

D 17
	nodev, nodev, nodev, nodev, nodev,		/* 1- defunct */
E 16
	nodev, nodev, nodev, nodev, nodev,
E 17
I 17
D 19
	enodev, enodev, enodev, enodev, enodev,		/* 1- defunct */
	enodev, enodev, enodev, enodev, enodev,
E 19
I 19
D 22
	ttynodisc, ttyerrclose, ttyerrio, ttyerrio, nullioctl,
	ttyerrinput, ttyerrstart, nullmodem,		/* 1- defunct */
E 22
I 22
	{ ttynodisc, ttyerrclose, ttyerrio, ttyerrio, nullioctl,
	  ttyerrinput, ttyerrstart, nullmodem },	/* 1- defunct */
E 22
E 19
E 17
D 16
	nodev, nodev, nodev, nodev, nodev,
#endif
E 16
I 16

E 16
D 9
	ttyopen, ttyclose, ttread, ttwrite, nullioctl,
	ttyinput, nodev, nulldev, ttstart, nulldev,
E 9
I 9
D 12
	ttyopen, ttylclose, ttread, ttwrite, nullioctl,
E 12
I 12
D 15
	ttyopen, ttylclose, ttread, ttwrite, nullioctl,	/* 2- NTTYDISC */
E 12
	ttyinput, nodev, nulldev, ttstart, ttymodem,
E 15
I 15
D 17
	nodev, nodev, nodev, nodev, nodev,		/* 2- defunct */
	nodev, nodev, nodev, nodev, nodev,
E 17
I 17
D 19
	enodev, enodev, enodev, enodev, enodev,		/* 2- defunct */
	enodev, enodev, enodev, enodev, enodev,
E 19
I 19
D 22
	ttynodisc, ttyerrclose, ttyerrio, ttyerrio, nullioctl,
	ttyerrinput, ttyerrstart, nullmodem,		/* 2- defunct */
E 22
I 22
	{ ttynodisc, ttyerrclose, ttyerrio, ttyerrio, nullioctl,
	  ttyerrinput, ttyerrstart, nullmodem },	/* 2- defunct */
E 22

E 19
E 17
E 15
E 9
#if NTB > 0
D 17
	tbopen, tbclose, tbread, nodev, tbioctl,
D 9
	tbinput, nodev, nulldev, ttstart, nulldev,		/* 3 */
E 9
I 9
D 12
	tbinput, nodev, nulldev, ttstart, nullmodem,		/* 3 */
E 12
I 12
	tbinput, nodev, nulldev, ttstart, nullmodem,	/* 3- TABLDISC */
E 17
I 17
D 22
	tbopen, tbclose, tbread, enodev, tbioctl,
D 19
	tbinput, enodev, nullop, ttstart, nullmodem,	/* 3- TABLDISC */
E 19
I 19
	tbinput, ttstart, nullmodem,			/* 3- TABLDISC */
E 22
I 22
	{ tbopen, tbclose, tbread, enodev, tbioctl,
	  tbinput, ttstart, nullmodem },		/* 3- TABLDISC */
E 22
E 19
E 17
#else
D 17
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
E 17
I 17
D 19
	enodev, enodev, enodev, enodev, enodev,
	enodev, enodev, enodev, enodev, enodev,
E 19
I 19
D 22
	ttynodisc, ttyerrclose, ttyerrio, ttyerrio, nullioctl,
	ttyerrinput, ttyerrstart, nullmodem,
E 22
I 22
	{ ttynodisc, ttyerrclose, ttyerrio, ttyerrio, nullioctl,
	  ttyerrinput, ttyerrstart, nullmodem },
E 22
E 19
E 17
#endif
I 19

E 19
#if NSL > 0
D 17
	slopen, slclose, nodev, nodev, sltioctl,
D 14
	slinput, nodev, nulldev, slstart, nulldev,	/* 4- SLIPDISC */
E 14
I 14
	slinput, nodev, nulldev, slstart, nullmodem,	/* 4- SLIPDISC */
E 17
I 17
D 19
	slopen, slclose, enodev, enodev, sltioctl,
	slinput, enodev, nullop, slstart, nullmodem,	/* 4- SLIPDISC */
E 19
I 19
D 22
	slopen, slclose, ttyerrio, ttyerrio, sltioctl,
	slinput, slstart, nullmodem,			/* 4- SLIPDISC */
E 22
I 22
	{ slopen, slclose, ttyerrio, ttyerrio, sltioctl,
	  slinput, slstart, nullmodem },		/* 4- SLIPDISC */
E 22
E 19
E 17
E 14
E 12
E 9
#else
D 17
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
E 17
I 17
D 19
	enodev, enodev, enodev, enodev, enodev,
	enodev, enodev, enodev, enodev, enodev,
E 19
I 19
D 22
	ttynodisc, ttyerrclose, ttyerrio, ttyerrio, nullioctl,
	ttyerrinput, ttyerrstart, nullmodem,
E 22
I 22
	{ ttynodisc, ttyerrclose, ttyerrio, ttyerrio, nullioctl,
	  ttyerrinput, ttyerrstart, nullmodem },
E 22
E 19
E 17
#endif
D 11
#if NTB > 0
	tbopen, tbclose, tbread, nodev, tbioctl,
D 9
	tbinput, nodev, nulldev, ttstart, nulldev,		/* 4 */
E 9
I 9
	tbinput, nodev, nulldev, ttstart, nullmodem,		/* 4 */
E 9
#else
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
#endif
E 11
D 2
	0		/* XXX */
E 2
};

D 2
int	nldisp = 5;

E 2
I 2
D 25
int	nldisp = sizeof (linesw) / sizeof (linesw[0]);
E 25
I 25
int	nlinesw = sizeof (linesw) / sizeof (linesw[0]);
E 25
I 3

/*
 * Do nothing specific version of line
 * discipline specific ioctl command.
 */
/*ARGSUSED*/
D 19
nullioctl(tp, cmd, data, flags)
E 19
I 19
nullioctl(tp, cmd, data, flags, p)
E 19
	struct tty *tp;
I 19
D 27
	int cmd;
E 27
I 27
	u_long cmd;
E 27
E 19
	char *data;
	int flags;
I 19
	struct proc *p;
E 19
{

#ifdef lint
D 19
	tp = tp; data = data; flags = flags;
E 19
I 19
	tp = tp; data = data; flags = flags; p = p;
E 19
#endif
	return (-1);
I 9
}
D 10

/*
 * Default modem control routine.
 * Return argument flag, to turn off device on carrier drop.
 */
nullmodem(flag)
	int flag;
{
	
	return (flag);
E 9
}
E 10
E 3
E 2
E 1
