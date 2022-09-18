h05213
s 00001/00001/00664
d D 8.4 95/02/20 14:06:16 dab 97 96
c When the EXTPROC bit is being turned off, and we
c check to see if it was on so that we can notify the user,
c we were looking at the t_state field instead of the t_lflag
c field, which is where it is kept.
e
s 00001/00001/00664
d D 8.3 95/01/09 18:22:20 cgd 96 95
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00001/00001/00664
d D 8.2 93/09/23 15:28:27 bostic 95 94
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00663
d D 8.1 93/06/30 15:13:01 bostic 94 93
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00662
d D 7.30 93/06/30 15:12:19 mckusick 93 91
c missing ptcwakeup needed for line-mode telnet
e
s 00002/00002/00662
d R 8.1 93/06/10 21:59:15 bostic 92 91
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00010/00632
d D 7.29 93/04/17 18:53:16 torek 91 90
c ptyattach (#ifdef notyet); don't need #if NPTY > 0
e
s 00010/00010/00632
d D 7.28 92/10/11 10:38:38 bostic 90 89
c make kernel includes standard
e
s 00002/00002/00640
d D 7.27 92/07/12 17:29:48 pendry 89 87
c MIN -> min, MAX -> max
e
s 00000/00000/00642
d R 7.27 92/07/12 17:20:19 pendry 88 87
c MIN -> min, MAX -> max
e
s 00005/00002/00637
d D 7.26 92/05/20 17:23:22 marc 87 86
c return codes for pt[sc]close (and exactly *what* if they fail???)
e
s 00002/00000/00637
d D 7.25 92/03/14 23:37:25 torek 86 85
c gcc lint
e
s 00007/00028/00630
d D 7.24 92/02/15 21:12:19 mckusick 85 84
c convert to use new select interface, selrecord/selwakeup
e
s 00024/00007/00634
d D 7.23 92/02/05 22:57:40 torek 84 83
c SunOS compatibility; misc cleanups
e
s 00000/00013/00641
d D 7.22 92/02/05 22:46:19 karels 83 82
c eliminate code to protect against berknet
e
s 00001/00001/00653
d D 7.21 91/05/30 14:51:29 mckusick 82 81
c make file flags consistent
e
s 00005/00003/00649
d D 7.20 91/05/16 17:53:21 marc 81 80
c pass flags through device close and l_close
e
s 00016/00015/00636
d D 7.19 91/04/20 16:14:07 karels 80 79
c rm user.h; new device calling conventions; ansify
e
s 00013/00016/00638
d D 7.18 91/03/17 15:42:29 karels 79 78
c more-or-less working with new proc & user structs
e
s 00024/00044/00630
d D 7.17 90/11/12 20:16:09 karels 78 77
c don't indirect thru uninit'ed iov in ptcwrite; change ptcwrite like ttwrite
c to avoid mucking in the iov's; switch to u_char so we don't have to mask
e
s 00004/00001/00670
d D 7.16 90/09/11 15:53:50 borman 77 76
c Fix for TIOCSIG: pgsignal() was being called with
c one too few arguments.  Add special case for SIGINFO to call
c ttyinfo().
e
s 00001/00011/00670
d D 7.15 90/06/28 21:23:00 bostic 76 75
c new copyright notice
e
s 00008/00000/00673
d D 7.14 90/06/26 19:30:58 marc 75 74
c duplicate TIOCGPGRP for controller - minus the check for controlling terminal
e
s 00005/00006/00668
d D 7.13 90/06/26 19:18:27 marc 74 73
c use ttysleep to catch revoked terminals
e
s 00061/00000/00613
d D 7.12 90/06/05 15:31:07 marc 73 72
c telnet line mode changes
e
s 00001/00001/00612
d D 7.11 90/05/17 15:56:08 marc 72 71
c pgsignal takes an extra arg
e
s 00016/00006/00597
d D 7.10 90/04/03 21:50:20 karels 71 70
c tsleep; unwind on interrupt
e
s 00002/00003/00601
d D 7.9 89/11/20 18:15:59 marc 70 69
c controlling terminal is a vnode
e
s 00004/00003/00600
d D 7.8 89/11/09 13:13:13 marc 69 68
c clear session on master close. also, temporary conversion stuff
e
s 00014/00003/00589
d D 7.7 89/05/15 08:37:14 bostic 68 67
c Berkeley copyright notice
e
s 00007/00007/00585
d D 7.6 89/05/09 17:02:53 mckusick 67 66
c merge in vnodes
e
s 00020/00013/00572
d D 7.5 89/05/01 23:07:55 marc 66 65
c ononblock and passing flag through
e
s 00026/00013/00559
d D 7.4 88/10/18 15:16:53 marc 65 62
c new terminal driver
e
s 00164/00023/00549
d D 7.3.1.1 88/01/13 14:14:32 mckusick 64 62
c new ioctl's from kre to support mux
e
s 00000/00000/00572
d R 7.3.1.1 88/01/13 14:13:13 mckusick 63 62
c new ioctl's from kre to support mux
e
s 00001/00001/00571
d D 7.3 87/12/26 14:14:33 bostic 62 61
c CTRL macro fix for ANSI C
e
s 00001/00001/00571
d D 7.2 87/10/03 11:05:12 karels 61 60
c clear carrier when master closes (even if LMDMBUF)
e
s 00001/00001/00571
d D 7.1 86/06/05 00:10:02 mckusick 60 59
c 4.3BSD release version
e
s 00001/00001/00571
d D 6.21 86/05/19 16:32:52 karels 59 58
c use UIOCCMD, as long as it's defined now
e
s 00002/00002/00570
d D 6.20 86/02/23 23:10:57 karels 58 57
c lint
e
s 00001/00001/00571
d D 6.19 86/02/19 17:46:15 karels 57 56
c lint
e
s 00019/00011/00553
d D 6.18 86/01/22 18:42:51 karels 56 54
c fixes from sun (sort of): select for write on ptc blocks
c if not at least minimal space (same as ptcwrite); fix ptcwrite test
c of canq.c_cc; cleanup spl's in ptcselect; rm unused
e
s 00019/00011/00553
d R 6.18 86/01/22 18:31:34 karels 55 54
c fixes from sun (sort of): select for write on ptc blocks
c if not at least minimal space (same as ptcwrite); fix ptcwrite test
c of canq.c_cc; cleanup spl's in ptcselect; rm unused
e
s 00001/00001/00563
d D 6.17 85/11/14 13:09:19 karels 54 53
c typo
e
s 00011/00002/00553
d D 6.16 85/11/08 19:12:26 karels 53 51
c allow select on exceptional to check control operations
e
s 00011/00002/00553
d R 6.16 85/11/08 19:02:46 karels 52 51
c select for exceptional cond. on ptc gets special operations
e
s 00021/00012/00534
d D 6.15 85/11/04 18:07:54 karels 51 50
c now using modem control entry in linesw; don't let pty's use
c nonstandard disciplines (we depend on the queue format)
e
s 00002/00000/00544
d D 6.14 85/09/04 09:46:24 bloom 50 49
c call line discipline close routine
e
s 00034/00023/00510
d D 6.13 85/06/21 17:07:21 bloom 49 48
c fix problems with NBIO and REMOTE in ptcwrite
e
s 00007/00001/00526
d D 6.12 85/06/08 14:46:58 mckusick 48 47
c Add copyright
e
s 00001/00002/00526
d D 6.11 85/06/07 17:35:06 karels 47 46
c what the hell was Edward up to?
e
s 00183/00125/00345
d D 6.10 85/04/17 17:20:14 bloom 46 45
c Performance rework by edward and add user ioctl
e
s 00002/00001/00468
d D 6.9 85/01/31 18:41:59 kre 45 44
c xon/xoff flow control should be off in raw mode.
c from net.bugs.4bsd newsitem by sun!gnu
e
s 00001/00001/00468
d D 6.8 84/12/20 14:56:05 karels 44 43
c missing parens
e
s 00001/00001/00468
d D 6.7 84/09/10 18:16:23 mckusick 43 42
c security fix from George Goble
e
s 00011/00011/00458
d D 6.6 84/08/29 20:23:06 bloom 42 41
c Change to includes.  no more ../h
e
s 00017/00006/00452
d D 6.5 84/07/29 18:40:29 sam 41 40
c bug fixes from mcvax!jim for slave side closing while master 
c side is in a read; fixes for sending EOF from dave rosenthal; performance 
c improvement from toronto
e
s 00002/00002/00456
d D 6.4 84/02/15 20:51:15 karels 40 39
c t_delct unused; use t_canq.c_cc instead
e
s 00004/00002/00454
d D 6.3 83/10/01 23:04:40 karels 39 37
c no more SIG_HOLD
e
s 00003/00002/00454
d R 6.3 83/10/01 18:09:41 karels 38 37
c no SIG_HOLD
e
s 00002/00001/00454
d D 6.2 83/09/26 08:26:11 karels 37 35
c don't lose input on large write to ptc (from thomas@utah-cs)
e
s 00002/00001/00454
d R 6.2 83/09/25 17:26:41 karels 36 35
c don't overflow doing long writes on ptc (from thomas@utah-cs)
e
s 00000/00000/00455
d D 6.1 83/07/29 06:39:31 sam 35 34
c 4.2 distribution
e
s 00002/00002/00453
d D 4.31 83/05/27 12:48:43 sam 34 33
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00001/00000/00454
d D 4.30 83/05/21 15:39:37 sam 33 32
c kre madness
e
s 00003/00002/00451
d D 4.29 82/12/05 22:01:12 sam 32 31
c include ioctl.h separate from tty.h
e
s 00001/00001/00452
d D 4.28 82/10/17 14:05:43 root 31 30
c fix lint
e
s 00018/00022/00435
d D 4.27 82/10/17 11:33:42 root 30 29
c ioctl/open return values
e
s 00032/00030/00425
d D 4.26 82/10/13 22:09:03 root 29 28
c return errors from ioctl routines and internal ldisc routines
e
s 00001/00000/00454
d D 4.25 82/09/12 02:59:28 root 28 27
c include kernel.h for lbolt
e
s 00046/00018/00408
d D 4.24 82/08/22 20:42:11 root 27 26
c uioing
e
s 00019/00030/00407
d D 4.23 82/08/01 19:21:56 sam 26 25
c new ioctl's
e
s 00002/00000/00435
d D 4.22 82/07/21 20:22:39 sam 25 24
c make robert happier (still crude though)
e
s 00001/00000/00434
d D 4.21 82/03/23 15:52:54 wnj 24 23
c call ttyclose
e
s 00002/00002/00432
d D 4.20 82/03/15 17:08:42 root 23 22
c NPTY to 32
e
s 00007/00007/00427
d D 4.19 82/03/13 12:50:42 sam 22 21
c lint
e
s 00022/00004/00412
d D 4.18 82/03/11 23:43:55 wnj 21 20
c for remote ^S/^Q
e
s 00072/00017/00344
d D 4.17 82/02/18 13:20:20 wnj 20 19
c TIOCREMOTE for EMACS sake
e
s 00014/00004/00347
d D 4.16 82/01/19 01:59:27 wnj 19 18
c finish pt_send (send start/stop)
e
s 00022/00006/00329
d D 4.15 82/01/17 13:36:40 wnj 18 17
c fix but in read select
e
s 00066/00027/00269
d D 4.14 82/01/17 04:01:39 wnj 17 16
c first working version
e
s 00025/00003/00271
d D 4.13 82/01/15 16:40:24 wnj 16 15
c add nbio stuff
e
s 00078/00034/00196
d D 4.12 82/01/14 17:05:37 wnj 15 14
c early non-blocking stuff
e
s 00008/00006/00222
d D 4.11 82/01/13 10:57:01 root 14 13
c minor fixes
e
s 00001/00002/00227
d D 4.10 81/11/18 15:49:48 wnj 13 12
c lint
e
s 00087/00090/00142
d D 4.9 81/10/11 11:48:10 wnj 12 11
c first boot with select()
e
s 00001/00001/00231
d D 4.8 81/08/14 11:04:55 ecc 11 10
c allow new tty disc over ptys (rob gurwitz)
e
s 00001/00001/00231
d D 4.7 81/03/11 18:40:20 wnj 10 9
c mx1: cleanup; pty: fix #ifdef
e
s 00001/00001/00231
d D 4.6 81/03/09 01:53:57 wnj 9 8
c %G% -> %E%
e
s 00026/00025/00206
d D 4.5 81/02/15 12:13:11 wnj 8 7
c flushtty second arg added (per lint)
e
s 00004/00003/00227
d D 4.4 81/01/29 17:04:56 toy 7 6
c ditto
e
s 00004/00000/00226
d D 4.3 81/01/29 17:03:18 toy 6 5
c Added #if WANTPTY
e
s 00000/00004/00226
d D 4.2 81/01/28 11:41:27 wnj 5 4
c remove names
e
s 00000/00000/00230
d D 4.1 81/01/26 22:16:49 toy 4 3
c Update SCCS id to be consistent with 4bsd
e
s 00002/00001/00228
d D 1.3 81/01/26 22:13:26 toy 3 2
c SCCS
e
s 00002/00000/00227
d D 1.2 81/01/26 22:11:48 toy 2 1
c SCCS mod
e
s 00227/00000/00000
d D 1.1 81/01/26 22:10:07 toy 1 0
c date and time created 81/01/26 22:10:07 by toy
e
u
U
f b 
t
T
I 1
D 5
#
E 5
I 2
D 3
/*	%W%	%I%	%G%	*/
E 3
I 3
D 9
/*	%M%	%I%	%G%	*/
E 9
I 9
D 48
/*	%M%	%I%	%E%	*/
E 48
I 48
/*
D 60
 * Copyright (c) 1982 Regents of the University of California.
E 60
I 60
D 68
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 60
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 68
I 68
D 94
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 94
I 94
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 94
 *
D 76
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 76
I 76
 * %sccs.include.redist.c%
E 76
E 68
 *
 *	%W% (Berkeley) %G%
 */
E 48
E 9

E 3
E 2
/*
 * Pseudo-teletype Driver
 * (Actually two drivers, requiring two entries in 'cdevsw')
D 5
 *
 * Overhauled, and ported to VAX/VMUNIX (V7) Bruce Borden, July 80
I 2
 * Modified and integrated into 4bsd by Kipp Hickman and Michael Toy
E 5
E 2
 */
I 7
D 91
#include "pty.h"
E 91
I 91
#include "pty.h"		/* XXX */
E 91

D 10
#if WANTPTY > 0
E 10
I 10
D 91
#if NPTY > 0
E 91
E 10
D 15

E 15
E 7
D 42
#include "../h/param.h"
#include "../h/systm.h"
I 32
#include "../h/ioctl.h"
E 32
#include "../h/tty.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/conf.h"
D 27
#include "../h/buf.h"
E 27
I 8
#include "../h/file.h"
I 12
#include "../h/proc.h"
I 27
#include "../h/uio.h"
I 28
#include "../h/kernel.h"
E 42
I 42
D 90
#include "param.h"
#include "systm.h"
#include "ioctl.h"
I 85
#include "proc.h"
E 85
#include "tty.h"
D 67
#include "dir.h"
E 67
D 80
#include "user.h"
E 80
#include "conf.h"
#include "file.h"
D 85
#include "proc.h"
E 85
#include "uio.h"
#include "kernel.h"
I 67
#include "vnode.h"
E 90
I 90
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
E 90
E 67
I 64
#include "tsleep.h"
E 64
E 42
E 28
E 27
E 12
E 8
I 6
D 7
#include "../pty.h"
E 6

I 6
#if WANTPTY > 0
E 7
D 15

E 15
E 6
D 8
#define NPTY 16                 /* Number of pseudo-teletypes */
#define BUFSIZ 100              /* Chunk size iomoved from user */
E 8
I 8
D 12
#define NPTY 16			/* Number of pseudo-teletypes */
E 12
I 12
D 23
#undef	NPTY
E 23
I 15

I 25
#if NPTY == 1
E 25
E 15
D 23
#define NPTY 16
E 23
I 23
D 46
#undef	NPTY
E 46
I 46
#undef NPTY
E 46
#define	NPTY	32		/* crude XXX */
I 25
#endif
E 25
E 23

E 12
D 41
#define BUFSIZ 100		/* Chunk size iomoved from user */
E 41
I 41
#define BUFSIZ 100		/* Chunk size iomoved to/from user */
E 41
E 8
D 12
#define ALLDELAYS (NLDELAY|TBDELAY|XTABS|CRDELAY|VTDELAY)
E 12
I 12

E 12
/*
D 12
 * A pseudo-teletype is a special device which is not unlike a pipe.
 * It is used to communicate between two processes.  However, it allows
 * one to simulate a teletype, including mode setting, interrupt, and
D 8
 * multiple end of files (all not possible on a pipe).  There are
E 8
I 8
 * multiple end of files (all not possible on a pipe).	There are
E 8
 * really two drivers here.  One is the device which looks like a TTY
 * and can be thought of as the slave device, and hence its routines
D 8
 * are prefixed with 'pts' (PTY Slave).  The other driver can be
E 8
I 8
 * are prefixed with 'pts' (PTY Slave).	 The other driver can be
E 8
 * thought of as the controlling device, and its routines are prefixed
 * by 'ptc' (PTY Controller).  To type on the simulated keyboard of the
 * PTY, one does a 'write' to the controlling device.  To get the
 * simulated printout from the PTY, one does a 'read' on the controlling
 * device.  Normally, the controlling device is called 'ptyx' and the
 * slave device is called 'ttyx' (to make programs like 'who' happy).
E 12
I 12
D 46
 * pts == /dev/tty[pP]?
 * ptc == /dev/ptp[pP]?
E 46
I 46
 * pts == /dev/tty[pqrs]?
 * ptc == /dev/pty[pqrs]?
E 46
E 12
 */
I 12
D 91
struct	tty pt_tty[NPTY];
E 91
I 91
struct	tty pt_tty[NPTY];	/* XXX */
E 91
struct	pt_ioctl {
D 17
	int	pti_flags;
	struct	clist pti_ioctl, pti_ioans;
	int	pti_gensym;
D 15
	struct	proc *pti_selr;
E 15
I 15
	struct	proc *pti_selr, *pti_selw;
E 17
I 17
	int	pt_flags;
D 56
	int	pt_gensym;
E 56
D 85
	struct	proc *pt_selr, *pt_selw;
E 85
I 85
	struct	selinfo pt_selr, pt_selw;
E 85
D 46
	int	pt_send;
E 46
I 46
	u_char	pt_send;
	u_char	pt_ucntl;
I 64
	struct	clist pt_ioc;
E 64
E 46
E 17
E 15
D 91
} pt_ioctl[NPTY];
E 91
I 91
} pt_ioctl[NPTY];		/* XXX */
E 91
I 46
int	npty = NPTY;		/* for pstat -t */
E 46
E 12

I 66
D 80
int ptydebug = 0;

E 80
E 66
D 8
struct tty pt_tty[NPTY];                /* TTY headers for PTYs */
E 8
I 8
D 12
struct tty pt_tty[NPTY];		/* TTY headers for PTYs */
E 12
I 12
D 17
#define	PTCRCOLL	0x01
I 15
#define	PTCWCOLL	0x02
I 16
#define	PTCNBIO		0x04
E 17
I 17
D 64
D 85
#define	PF_RCOLL	0x01
#define	PF_WCOLL	0x02
E 85
D 78
#define	PF_NBIO		0x04
E 78
#define	PF_PKT		0x08		/* packet mode */
D 19
#define	PF_FLOWCTL	0x10		/* peers flow control mode */
E 19
I 19
#define	PF_STOPPED	0x10		/* user told stopped */
I 20
#define	PF_REMOTE	0x20		/* remote and flow controlled input */
I 21
#define	PF_NOSTOP	0x40
I 46
#define PF_UCNTL	0x80		/* user control mode */
E 64
I 64
#define	PF_RCOLL	0x0001
#define	PF_WCOLL	0x0002
#define	PF_NBIO		0x0004
#define	PF_PKT		0x0008		/* packet mode */
#define	PF_STOPPED	0x0010		/* user told stopped */
#define	PF_REMOTE	0x0020		/* remote and flow controlled input */
#define	PF_NOSTOP	0x0040
#define	PF_UCNTL	0x0080		/* user control mode */
#define	PF_TIOC		0x0100		/* transparent control mode */
#define	PF_LIOC		0x0200		/* transparent control locked */
#define	PF_WIOC		0x0400		/* waiting for PF_LIOC to clear */
#define	PF_BLOCK	0x0800		/* block writes to slave */
#define	PF_OWAIT	0x1000		/* waiting for PF_BLOCK to clear */
E 64
E 46
E 21
E 20
E 19
E 17
E 16
E 15
E 12
E 8

I 84
void	ptsstop __P((struct tty *, int));

I 91
/*
 * Establish n (or default if n is 1) ptys in the system.
 *
 * XXX cdevsw & pstat require the array `pty[]' to be an array
 */
void
ptyattach(n)
	int n;
{
#ifdef notyet
	char *mem;
	register u_long ntb;
#define	DEFAULT_NPTY	32

	/* maybe should allow 0 => none? */
	if (n <= 1)
		n = DEFAULT_NPTY;
	ntb = n * sizeof(struct tty);
	mem = malloc(ntb + ALIGNBYTES + n * sizeof(struct pt_ioctl),
	    M_DEVBUF, M_WAITOK);
	pt_tty = (struct tty *)mem;
	mem = (char *)ALIGN(mem + ntb);
	pt_ioctl = (struct pt_ioctl *)mem;
	npty = n;
#endif
}

E 91
E 84
/*ARGSUSED*/
D 80
ptsopen(dev, flag)
E 80
I 80
ptsopen(dev, flag, devtype, p)
E 80
D 14
dev_t dev;
E 14
I 14
	dev_t dev;
I 84
	int flag, devtype;
E 84
I 80
	struct proc *p;
E 80
E 14
D 8
{                                       /* Open for PTY Slave */
E 8
I 8
D 12
{					/* Open for PTY Slave */
E 12
I 12
{
I 79
D 80
	struct proc *p = curproc;
E 80
E 79
E 12
E 8
	register struct tty *tp;
I 46
	int error;
E 46

I 46
D 91
#ifdef lint
	npty = npty;
#endif
E 46
D 12
	if(minor(dev) >= NPTY) {
E 12
I 12
D 30
	if (minor(dev) >= NPTY) {
E 12
		u.u_error = ENXIO;
		return;
	}
E 30
I 30
	if (minor(dev) >= NPTY)
E 91
I 91
	if (minor(dev) >= npty)
E 91
		return (ENXIO);
E 30
	tp = &pt_tty[minor(dev)];
D 12
	if((tp->t_state & ISOPEN) == 0) {
E 12
I 12
D 15
	if ((tp->t_state & ISOPEN) == 0) {
E 15
I 15
	if ((tp->t_state & TS_ISOPEN) == 0) {
I 74
		tp->t_state |= TS_WOPEN;
E 74
E 15
E 12
D 8
		ttychars(tp);           /* Set up default chars */
		tp->t_flags = 0;        /* No features (nor raw mode) */
E 8
I 8
		ttychars(tp);		/* Set up default chars */
I 33
D 65
		tp->t_ispeed = tp->t_ospeed = EXTB;
E 33
		tp->t_flags = 0;	/* No features (nor raw mode) */
E 65
I 65
		tp->t_iflag = TTYDEF_IFLAG;
		tp->t_oflag = TTYDEF_OFLAG;
		tp->t_lflag = TTYDEF_LFLAG;
		tp->t_cflag = TTYDEF_CFLAG;
		tp->t_ispeed = tp->t_ospeed = TTYDEF_SPEED;
		ttsetwater(tp);		/* would be done in xxparam() */
E 65
E 8
D 12
	} else if(tp->t_state&XCLUDE && u.u_uid != 0) {
E 12
I 12
D 15
	} else if (tp->t_state&XCLUDE && u.u_uid != 0) {
E 15
I 15
D 30
	} else if (tp->t_state&TS_XCLUDE && u.u_uid != 0) {
E 15
E 12
		u.u_error = EBUSY;
		return;
	}
E 30
I 30
D 79
	} else if (tp->t_state&TS_XCLUDE && u.u_uid != 0)
E 79
I 79
	} else if (tp->t_state&TS_XCLUDE && p->p_ucred->cr_uid != 0)
E 79
		return (EBUSY);
E 30
D 8
	if(tp->t_oproc)                 /* Ctrlr still around. */
E 8
I 8
D 12
	if(tp->t_oproc)			/* Ctrlr still around. */
E 12
I 12
	if (tp->t_oproc)			/* Ctrlr still around. */
E 12
E 8
D 15
		tp->t_state |= CARR_ON;
D 12
	while((tp->t_state & CARR_ON) == 0) {
E 12
I 12
	while ((tp->t_state & CARR_ON) == 0) {
E 12
		tp->t_state |= WOPEN;
E 15
I 15
		tp->t_state |= TS_CARR_ON;
	while ((tp->t_state & TS_CARR_ON) == 0) {
		tp->t_state |= TS_WOPEN;
I 66
D 82
		if (flag&FNDELAY)
E 82
I 82
		if (flag&FNONBLOCK)
E 82
			break;
E 66
E 15
D 71
		sleep((caddr_t)&tp->t_rawq, TTIPRI);
E 71
I 71
D 74
		if (error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
E 74
I 74
		if (error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
E 74
		    ttopen, 0))
			return (error);
E 71
	}
D 30
	(*linesw[tp->t_line].l_open)(dev, tp);
E 30
I 30
D 46
	return ((*linesw[tp->t_line].l_open)(dev, tp));
E 46
I 46
D 66
	error = (*linesw[tp->t_line].l_open)(dev, tp);
E 66
I 66
D 84
	error = (*linesw[tp->t_line].l_open)(dev, tp, flag);
E 84
I 84
	error = (*linesw[tp->t_line].l_open)(dev, tp);
E 84
E 66
	ptcwakeup(tp, FREAD|FWRITE);
	return (error);
E 46
E 30
}

D 81
ptsclose(dev)
E 81
I 81
ptsclose(dev, flag, mode, p)
E 81
D 14
dev_t dev;
E 14
I 14
	dev_t dev;
I 81
	int flag, mode;
	struct proc *p;
E 81
E 14
D 8
{                                       /* Close slave part of PTY */
E 8
I 8
D 15
{					/* Close slave part of PTY */
E 15
I 15
{
E 15
E 8
	register struct tty *tp;
I 87
	int err;
E 87

	tp = &pt_tty[minor(dev)];
D 81
	(*linesw[tp->t_line].l_close)(tp);
E 81
I 81
D 87
	(*linesw[tp->t_line].l_close)(tp, flag);
E 81
I 24
	ttyclose(tp);
E 87
I 87
	err = (*linesw[tp->t_line].l_close)(tp, flag);
	err |= ttyclose(tp);
E 87
I 41
D 46
	ptcwakeup(tp);
E 46
I 46
	ptcwakeup(tp, FREAD|FWRITE);
I 87
	return (err);
E 87
I 64
	return (0);
E 64
E 46
E 41
E 24
}

D 27
ptsread(dev)
E 27
I 27
D 66
ptsread(dev, uio)
E 66
I 66
ptsread(dev, uio, flag)
E 66
E 27
D 14
dev_t dev;
E 14
I 14
	dev_t dev;
I 27
	struct uio *uio;
I 84
	int flag;
E 84
E 27
E 14
D 8
{       /* Read from PTY, i.e. from data written by controlling device */
E 8
I 8
D 12
{	/* Read from PTY, i.e. from data written by controlling device */
E 8
	register struct tty    *tp;
E 12
I 12
{
I 79
	struct proc *p = curproc;
E 79
D 20
	register struct tty *tp;
I 15
	register struct pt_ioctl *pti;
E 20
I 20
	register struct tty *tp = &pt_tty[minor(dev)];
	register struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
I 29
	int error = 0;
E 29
E 20
E 15
E 12

D 20
	tp = &pt_tty[minor(dev)];
D 12
	if(tp->t_oproc) {
E 12
I 12
	if (tp->t_oproc) {
E 12
		(*linesw[tp->t_line].l_read)(tp);
D 12
				/* Wakeup other half if sleeping */
E 12
		wakeup((caddr_t)&tp->t_rawq.c_cf);
I 15
		if (tp->t_rawq.c_cc < TTYHOG/2 &&
D 17
		    (pti = &pt_ioctl[minor(tp->t_dev)])->pti_selw) {
			selwakeup(pti->pti_selw, pti->pti_flags & PTCWCOLL);
			pti->pti_selw = 0;
			pti->pti_flags &= ~PTCWCOLL;
E 17
I 17
		    (pti = &pt_ioctl[minor(tp->t_dev)])->pt_selw) {
			selwakeup(pti->pt_selw, pti->pt_flags & PF_WCOLL);
			pti->pt_selw = 0;
			pti->pt_flags &= ~PF_WCOLL;
E 20
I 20
again:
	if (pti->pt_flags & PF_REMOTE) {
D 65
		while (tp == u.u_ttyp && u.u_procp->p_pgrp != tp->t_pgrp) {
E 65
I 65
D 70
		while (tp == u.u_ttyp && 
		       u.u_procp->p_pgrp->pg_id != tp->t_pgid){
E 70
I 70
D 79
		while (isbackground(u.u_procp, tp)) {
E 70
E 65
D 39
			if (u.u_signal[SIGTTIN] == SIG_IGN ||
			    u.u_signal[SIGTTIN] == SIG_HOLD ||
E 39
I 39
D 46
#define bit(a) (1<<(a-1))
			if ((u.u_procp->p_sigignore & bit(SIGTTIN)) ||
			    (u.u_procp->p_sigmask & bit(SIGTTIN)) ||
E 46
I 46
			if ((u.u_procp->p_sigignore & sigmask(SIGTTIN)) ||
			    (u.u_procp->p_sigmask & sigmask(SIGTTIN)) ||
I 65
D 70
			    !u.u_procp->p_pgrp->pg_jobc ||
E 70
I 70
			    u.u_procp->p_pgrp->pg_jobc == 0 ||
E 70
E 65
E 46
E 39
D 51
	/*
			    (u.u_procp->p_flag&SDETACH) ||
	*/
E 51
			    u.u_procp->p_flag&SVFORK)
E 79
I 79
		while (isbackground(p, tp)) {
			if ((p->p_sigignore & sigmask(SIGTTIN)) ||
			    (p->p_sigmask & sigmask(SIGTTIN)) ||
			    p->p_pgrp->pg_jobc == 0 ||
D 95
			    p->p_flag&SPPWAIT)
E 95
I 95
			    p->p_flag & P_PPWAIT)
E 95
E 79
D 29
				return;
E 29
I 29
				return (EIO);
E 29
D 65
			gsignal(u.u_procp->p_pgrp, SIGTTIN);
E 65
I 65
D 72
			pgsignal(u.u_procp->p_pgrp, SIGTTIN);
E 72
I 72
D 79
			pgsignal(u.u_procp->p_pgrp, SIGTTIN, 1);
E 79
I 79
			pgsignal(p->p_pgrp, SIGTTIN, 1);
E 79
E 72
E 65
D 71
			sleep((caddr_t)&lbolt, TTIPRI);
E 71
I 71
D 74
			if (error = tsleep((caddr_t)&lbolt, TTIPRI | PCATCH,
			    ttybg, 0))
E 74
I 74
			if (error = ttysleep(tp, (caddr_t)&lbolt, 
			    TTIPRI | PCATCH, ttybg, 0))
E 74
				return (error);
E 71
E 20
E 17
		}
I 39
D 46
#undef	bit
E 39
I 20
		if (tp->t_rawq.c_cc == 0) {
E 46
I 46
		if (tp->t_canq.c_cc == 0) {
E 46
D 29
			if (tp->t_state & TS_NBIO) {
				u.u_error = EWOULDBLOCK;
				return;
			}
E 29
I 29
D 66
			if (tp->t_state & TS_NBIO)
E 66
I 66
D 67
			if (flag & FNDELAY)
E 67
I 67
			if (flag & IO_NDELAY)
E 67
E 66
				return (EWOULDBLOCK);
E 29
D 46
			sleep((caddr_t)&tp->t_rawq, TTIPRI);
E 46
I 46
D 71
			sleep((caddr_t)&tp->t_canq, TTIPRI);
E 71
I 71
D 74
			if (error = tsleep((caddr_t)&tp->t_canq,
E 74
I 74
			if (error = ttysleep(tp, (caddr_t)&tp->t_canq,
E 74
			    TTIPRI | PCATCH, ttyin, 0))
				return (error);
E 71
E 46
			goto again;
		}
D 27
		while (tp->t_rawq.c_cc > 1 && passc(getc(&tp->t_rawq)) >= 0)
			;
E 27
I 27
D 46
		while (tp->t_rawq.c_cc > 1 && uio->uio_resid > 0)
			if (ureadc(getc(&tp->t_rawq), uio) < 0) {
E 46
I 46
		while (tp->t_canq.c_cc > 1 && uio->uio_resid > 0)
			if (ureadc(getc(&tp->t_canq), uio) < 0) {
E 46
D 29
				u.u_error = EFAULT;
E 29
I 29
				error = EFAULT;
E 29
				break;
			}
E 27
D 46
		if (tp->t_rawq.c_cc == 1)
			(void) getc(&tp->t_rawq);
		if (tp->t_rawq.c_cc)
E 46
I 46
		if (tp->t_canq.c_cc == 1)
			(void) getc(&tp->t_canq);
		if (tp->t_canq.c_cc)
E 46
D 29
			return;
E 29
I 29
			return (error);
E 29
	} else
		if (tp->t_oproc)
D 27
			(*linesw[tp->t_line].l_read)(tp);
E 27
I 27
D 29
			(*linesw[tp->t_line].l_read)(tp, uio);
E 29
I 29
D 66
			error = (*linesw[tp->t_line].l_read)(tp, uio);
E 66
I 66
			error = (*linesw[tp->t_line].l_read)(tp, uio, flag);
E 66
E 29
E 27
D 46
	wakeup((caddr_t)&tp->t_rawq.c_cf);
	if (pti->pt_selw) {
		selwakeup(pti->pt_selw, pti->pt_flags & PF_WCOLL);
		pti->pt_selw = 0;
		pti->pt_flags &= ~PF_WCOLL;
E 20
E 15
	}
E 46
I 46
	ptcwakeup(tp, FWRITE);
E 46
I 29
	return (error);
E 29
}

I 15
/*
 * Write to pseudo-tty.
 * Wakeups of controlling tty will happen
 * indirectly, when tty driver calls ptsstart.
 */
E 15
D 27
ptswrite(dev)
E 27
I 27
D 66
ptswrite(dev, uio)
E 66
I 66
ptswrite(dev, uio, flag)
E 66
E 27
D 14
dev_t dev;
E 14
I 14
	dev_t dev;
I 27
	struct uio *uio;
I 86
	int flag;
E 86
E 27
E 14
D 8
{                       /* Write on PTY, i.e. to be read from
E 8
I 8
D 12
{			/* Write on PTY, i.e. to be read from
E 8
			   controlling device */
E 12
I 12
{
E 12
D 64
	register struct tty *tp;
E 64
I 64
	register struct tty *tp = &pt_tty[minor(dev)];
	register struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
E 64

D 64
	tp = &pt_tty[minor(dev)];
E 64
D 12
			/* Wait for controlling device to be opened */
	if(tp->t_oproc)
E 12
I 12
D 29
	if (tp->t_oproc)
E 12
D 27
		(*linesw[tp->t_line].l_write)(tp);
E 27
I 27
		(*linesw[tp->t_line].l_write)(tp, uio);
E 29
I 29
	if (tp->t_oproc == 0)
		return (EIO);
I 64

	while (pti->pt_flags & PF_BLOCK) {
		pti->pt_flags |= PF_OWAIT;
		sleep((caddr_t)pti + 1, TTOPRI);
	}

E 64
D 66
	return ((*linesw[tp->t_line].l_write)(tp, uio));
E 66
I 66
	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
E 66
E 29
E 27
}

I 15
/*
 * Start output on pseudo-tty.
 * Wake up process selecting or sleeping for input from controlling tty.
 */
I 84
void
E 84
E 15
ptsstart(tp)
D 12
struct tty *tp;
D 8
{                       /* Called by 'ttstart' to output a character.
E 8
I 8
{			/* Called by 'ttstart' to output a character.
E 8
			   Merely wakes up controlling half, which
			   does actual work */
	if(tp->t_state & TTSTOP)
E 12
I 12
	struct tty *tp;
{
I 19
	register struct pt_ioctl *pti = &pt_ioctl[minor(tp->t_dev)];
E 19
D 18
	struct pt_ioctl *pti = &pt_ioctl[minor(tp->t_dev)];
E 18

D 15
	if (tp->t_state & TTSTOP)
E 15
I 15
	if (tp->t_state & TS_TTSTOP)
E 15
E 12
		return;
I 19
	if (pti->pt_flags & PF_STOPPED) {
		pti->pt_flags &= ~PF_STOPPED;
		pti->pt_send = TIOCPKT_START;
	}
E 19
I 18
D 46
	ptcwakeup(tp);
E 46
I 46
	ptcwakeup(tp, FREAD);
E 46
}

D 46
ptcwakeup(tp)
E 46
I 46
ptcwakeup(tp, flag)
E 46
	struct tty *tp;
I 84
	int flag;
E 84
{
	struct pt_ioctl *pti = &pt_ioctl[minor(tp->t_dev)];

E 18
I 12
D 17
	if (pti->pti_selr) {
		selwakeup(pti->pti_selr, pti->pti_flags & PTCRCOLL);
		pti->pti_selr = 0;
		pti->pti_flags &= ~PTCRCOLL;
E 17
I 17
D 46
	if (pti->pt_selr) {
		selwakeup(pti->pt_selr, pti->pt_flags & PF_RCOLL);
		pti->pt_selr = 0;
		pti->pt_flags &= ~PF_RCOLL;
E 46
I 46
	if (flag & FREAD) {
D 85
		if (pti->pt_selr) {
			selwakeup(pti->pt_selr, pti->pt_flags & PF_RCOLL);
			pti->pt_selr = 0;
			pti->pt_flags &= ~PF_RCOLL;
		}
E 85
I 85
		selwakeup(&pti->pt_selr);
E 85
		wakeup((caddr_t)&tp->t_outq.c_cf);
E 46
E 17
	}
E 12
D 46
	wakeup((caddr_t)&tp->t_outq.c_cf);
E 46
I 46
	if (flag & FWRITE) {
D 85
		if (pti->pt_selw) {
			selwakeup(pti->pt_selw, pti->pt_flags & PF_WCOLL);
			pti->pt_selw = 0;
			pti->pt_flags &= ~PF_WCOLL;
		}
E 85
I 85
		selwakeup(&pti->pt_selw);
E 85
I 66
D 79
if (ptydebug) printf("WAKEUP c_cf %d\n", u.u_procp->p_pid);
E 79
I 79
D 80
if (ptydebug) printf("WAKEUP c_cf %d\n", curproc->p_pid);
E 80
E 79
E 66
		wakeup((caddr_t)&tp->t_rawq.c_cf);
	}
E 46
}

/*ARGSUSED*/
D 80
ptcopen(dev, flag)
E 80
I 80
#ifdef __STDC__
ptcopen(dev_t dev, int flag, int devtype, struct proc *p)
#else
ptcopen(dev, flag, devtype, p)
E 80
D 12
dev_t dev;
D 8
{                               /* Open for PTY Controller */
E 8
I 8
{				/* Open for PTY Controller */
E 12
I 12
	dev_t dev;
D 80
	int flag;
E 80
I 80
	int flag, devtype;
	struct proc *p;
#endif
E 80
{
E 12
E 8
	register struct tty *tp;
I 17
	struct pt_ioctl *pti;
E 17

D 12
	if(minor(dev) >= NPTY) {
E 12
I 12
D 30
	if (minor(dev) >= NPTY) {
E 12
		u.u_error = ENXIO;
		return;
	}
E 30
I 30
D 91
	if (minor(dev) >= NPTY)
E 91
I 91
	if (minor(dev) >= npty)
E 91
		return (ENXIO);
E 30
	tp = &pt_tty[minor(dev)];
D 12
	if(tp->t_oproc) {
E 12
I 12
D 30
	if (tp->t_oproc) {
E 12
		u.u_error = EIO;
		return;
	}
E 30
I 30
	if (tp->t_oproc)
		return (EIO);
E 30
D 8
	tp->t_oproc = ptsstart;         /* Set address of start routine */
E 8
I 8
D 12
	tp->t_oproc = ptsstart;		/* Set address of start routine */
E 8
	tp->t_iproc = 0;
	if(tp->t_state & WOPEN)
E 12
I 12
	tp->t_oproc = ptsstart;
I 84
#ifdef sun4c
	tp->t_stop = ptsstop;
#endif
E 84
D 15
	if (tp->t_state & WOPEN)
E 15
I 15
D 51
	if (tp->t_state & TS_WOPEN)
E 15
E 12
		wakeup((caddr_t)&tp->t_rawq);
E 51
I 51
	(void)(*linesw[tp->t_line].l_modem)(tp, 1);
I 73
	tp->t_lflag &= ~EXTPROC;
E 73
E 51
D 15
	tp->t_state |= CARR_ON;
E 15
I 15
D 61
	tp->t_state |= TS_CARR_ON;
E 61
I 17
	pti = &pt_ioctl[minor(dev)];
	pti->pt_flags = 0;
	pti->pt_send = 0;
I 46
	pti->pt_ucntl = 0;
E 46
I 30
	return (0);
E 30
E 17
E 15
}

ptcclose(dev)
D 12
dev_t dev;
D 8
{                                       /* Close controlling part of PTY */
E 8
I 8
{					/* Close controlling part of PTY */
E 12
I 12
	dev_t dev;
{
E 12
E 8
	register struct tty *tp;

	tp = &pt_tty[minor(dev)];
I 50
D 51
	if (tp->t_line)
		(*linesw[tp->t_line].l_close)(tp);
E 50
D 12
	if(tp->t_state & ISOPEN)
E 12
I 12
D 15
	if (tp->t_state & ISOPEN)
E 15
I 15
	if (tp->t_state & TS_ISOPEN)
E 15
E 12
		gsignal(tp->t_pgrp, SIGHUP);
D 8
	tp->t_state &= ~CARR_ON;        /* Virtual carrier is gone */
	flushtty(tp);                   /* Clean things up */
	tp->t_oproc = 0;                /* Mark as closed */
E 8
I 8
D 12
	tp->t_state &= ~CARR_ON;	/* Virtual carrier is gone */
	flushtty(tp, FREAD|FWRITE);		     /* Clean things up */
	tp->t_oproc = 0;		/* Mark as closed */
E 12
I 12
D 15
	tp->t_state &= ~CARR_ON;	/* virtual carrier gone */
E 15
I 15
	tp->t_state &= ~TS_CARR_ON;	/* virtual carrier gone */
E 15
D 34
	flushtty(tp, FREAD|FWRITE);
E 34
I 34
	ttyflush(tp, FREAD|FWRITE);
E 51
I 51
	(void)(*linesw[tp->t_line].l_modem)(tp, 0);
I 61
	tp->t_state &= ~TS_CARR_ON;
E 61
E 51
E 34
	tp->t_oproc = 0;		/* mark closed */
I 69
	tp->t_session = 0;
I 87
	return (0);
E 87
E 69
I 64
	return (0);
E 64
E 12
E 8
}

D 27
ptcread(dev)
E 27
I 27
D 66
ptcread(dev, uio)
E 66
I 66
ptcread(dev, uio, flag)
E 66
E 27
D 17
dev_t dev;
E 17
I 17
	dev_t dev;
I 27
	struct uio *uio;
I 84
	int flag;
E 84
E 27
E 17
D 8
{                                       /* Read from PTY's output buffer */
E 8
I 8
D 12
{					/* Read from PTY's output buffer */
E 12
I 12
{
E 12
E 8
D 29
	register struct tty *tp;
E 29
I 29
	register struct tty *tp = &pt_tty[minor(dev)];
E 29
I 17
D 46
	struct pt_ioctl *pti;
E 46
I 46
	struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
E 46
I 29
D 41
	int error = 0;
E 41
I 41
	char buf[BUFSIZ];
	int error = 0, cc;
E 41
E 29
E 17

D 29
	tp = &pt_tty[minor(dev)];
E 29
D 12
	if((tp->t_state&(CARR_ON|ISOPEN)) == 0)
E 12
I 12
D 15
	if ((tp->t_state&(CARR_ON|ISOPEN)) == 0)
E 15
I 15
D 46
	if ((tp->t_state&(TS_CARR_ON|TS_ISOPEN)) == 0)
E 15
E 12
D 31
		return;
E 31
I 31
		return (EIO);
E 31
I 17
	pti = &pt_ioctl[minor(dev)];
	if (pti->pt_flags & PF_PKT) {
		if (pti->pt_send) {
D 22
			passc(pti->pt_send);
E 22
I 22
D 27
			(void) passc(pti->pt_send);
E 27
I 27
D 29
			(void) ureadc(pti->pt_send, uio);
E 29
I 29
			error = ureadc(pti->pt_send, uio);
			if (error)
				return (error);
E 29
E 27
E 22
			pti->pt_send = 0;
D 29
			return;
E 29
I 29
			return (0);
E 46
I 46
	/*
	 * We want to block until the slave
	 * is open, and there's something to read;
	 * but if we lost the slave or we're NBIO,
	 * then return the appropriate error instead.
	 */
	for (;;) {
		if (tp->t_state&TS_ISOPEN) {
			if (pti->pt_flags&PF_PKT && pti->pt_send) {
D 58
				error = ureadc(pti->pt_send, uio);
E 58
I 58
				error = ureadc((int)pti->pt_send, uio);
E 58
				if (error)
					return (error);
I 73
				if (pti->pt_send & TIOCPKT_IOCTL) {
D 89
					cc = MIN(uio->uio_resid,
E 89
I 89
					cc = min(uio->uio_resid,
E 89
						sizeof(tp->t_termios));
					uiomove(&tp->t_termios, cc, uio);
				}
E 73
				pti->pt_send = 0;
				return (0);
			}
			if (pti->pt_flags&PF_UCNTL && pti->pt_ucntl) {
D 58
				error = ureadc(pti->pt_ucntl, uio);
E 58
I 58
				error = ureadc((int)pti->pt_ucntl, uio);
E 58
				if (error)
					return (error);
				pti->pt_ucntl = 0;
				return (0);
			}
I 64
			if (pti->pt_flags&PF_TIOC && pti->pt_ioc.c_cc) {
				if (uio->uio_resid < pti->pt_ioc.c_cc + 1)
					return (E2BIG);
				error = ureadc(TIOCPKT_TIOC, uio);
				while (error == 0 && pti->pt_ioc.c_cc > 0) {
					cc = q_to_b(&pti->pt_ioc, buf,
					    MIN(pti->pt_ioc.c_cc, BUFSIZ));
					if (cc <= 0)	/* impossible? */
						break;
					error = uiomove(buf, cc, UIO_READ, uio);
				}
				return (error);
			}
E 64
			if (tp->t_outq.c_cc && (tp->t_state&TS_TTSTOP) == 0)
				break;
E 46
E 29
		}
D 22
		passc(0);
E 22
I 22
D 27
		(void) passc(0);
E 27
I 27
D 29
		(void) ureadc(0, uio);
E 29
I 29
D 46
		error = ureadc(0, uio);
E 29
E 27
E 22
	}
E 17
D 8
	while(tp->t_outq.c_cc == 0 ||   /* Wait for something to arrive */
	      (tp->t_state&TTSTOP))     /* (Woken by ptsstart) */
E 8
I 8
D 12
	while(tp->t_outq.c_cc == 0 ||	/* Wait for something to arrive */
	      (tp->t_state&TTSTOP))	/* (Woken by ptsstart) */
E 12
I 12
D 15
	while (tp->t_outq.c_cc == 0 || (tp->t_state&TTSTOP))
E 15
I 15
D 16
	while (tp->t_outq.c_cc == 0 || (tp->t_state&TS_TTSTOP))
E 16
I 16
	while (tp->t_outq.c_cc == 0 || (tp->t_state&TS_TTSTOP)) {
E 46
I 41
		if ((tp->t_state&TS_CARR_ON) == 0)
D 66
			return (EIO);
E 41
D 17
		if (pt_ioctl[minor(dev)].pti_flags&PTCNBIO) {
E 17
I 17
D 29
		if (pti->pt_flags&PF_NBIO) {
E 17
			u.u_error = EWOULDBLOCK;
			return;
		}
E 29
I 29
		if (pti->pt_flags&PF_NBIO)
E 66
I 66
			return (0);	/* EOF */
D 67
		if (flag&FNDELAY)
E 67
I 67
		if (flag & IO_NDELAY)
E 67
E 66
			return (EWOULDBLOCK);
I 66
D 71
if (ptydebug) printf("SLEEP(1) c_cf %d\n", u.u_procp->p_pid);
E 66
E 29
E 16
E 15
E 12
E 8
		sleep((caddr_t)&tp->t_outq.c_cf, TTIPRI);
E 71
I 71
D 74
if (ptydebug) printf("SLEEP(1) c_cf %d\n", u.u_procp->p_pid);	/* XXX */
E 74
		if (error = tsleep((caddr_t)&tp->t_outq.c_cf, TTIPRI | PCATCH,
		    ttyin, 0))
			return (error);
E 71
I 16
	}
I 46
D 64
	if (pti->pt_flags & (PF_PKT|PF_UCNTL))
E 64
I 64
	if (pti->pt_flags & (PF_PKT|PF_UCNTL|PF_TIOC))
E 64
		error = ureadc(0, uio);
E 46
E 16
D 12
	while(tp->t_outq.c_cc && passc(getc(&tp->t_outq)) >= 0);
	if(tp->t_outq.c_cc <= TTLOWAT(tp)  && (tp->t_state&ASLEEP)) {
E 12
I 12
D 15
	while (tp->t_outq.c_cc && passc(getc(&tp->t_outq)) >= 0);
	if (tp->t_outq.c_cc <= TTLOWAT(tp)  && (tp->t_state&ASLEEP)) {
E 12
		tp->t_state &= ~ASLEEP;
D 12
		if(tp->t_chan)
			mcstart(tp->t_chan, (caddr_t)&tp->t_outq);
		else
			wakeup((caddr_t)&tp->t_outq);
E 12
I 12
		wakeup((caddr_t)&tp->t_outq);
E 15
I 15
D 27
	while (tp->t_outq.c_cc && passc(getc(&tp->t_outq)) >= 0)
		;
E 27
I 27
D 41
	while (tp->t_outq.c_cc && uio->uio_resid > 0)
		if (ureadc(getc(&tp->t_outq), uio) < 0) {
D 29
			u.u_error = EFAULT;
E 29
I 29
			error = EFAULT;
E 41
I 41
	while (uio->uio_resid > 0 && error == 0) {
D 89
		cc = q_to_b(&tp->t_outq, buf, MIN(uio->uio_resid, BUFSIZ));
E 89
I 89
		cc = q_to_b(&tp->t_outq, buf, min(uio->uio_resid, BUFSIZ));
E 89
		if (cc <= 0)
E 41
E 29
			break;
D 41
		}
E 41
I 41
D 67
		error = uiomove(buf, cc, UIO_READ, uio);
E 67
I 67
		error = uiomove(buf, cc, uio);
E 67
	}
E 41
E 27
D 64
D 65
	if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
E 65
I 65
	if (tp->t_outq.c_cc <= tp->t_lowat) {
E 65
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
D 85
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
E 85
I 85
		selwakeup(&tp->t_wsel);
E 85
E 15
E 12
	}
E 64
I 64
	if (tp->t_outq.c_cc <= TTLOWAT(tp) && !(pti->pt_flags & PF_BLOCK))
		ptswake(tp);
E 64
I 29
	return (error);
E 29
}

I 84
void
E 84
I 64
ptswake(tp)
	register struct tty *tp;
{
	if (tp->t_state&TS_ASLEEP) {
		tp->t_state &= ~TS_ASLEEP;
		wakeup((caddr_t)&tp->t_outq);
	}
	if (tp->t_wsel) {
		selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
		tp->t_wsel = 0;
		tp->t_state &= ~TS_WCOLL;
	}
}

E 64
I 17
ptsstop(tp, flush)
	register struct tty *tp;
	int flush;
{
	struct pt_ioctl *pti = &pt_ioctl[minor(tp->t_dev)];
I 46
	int flag;
E 46

D 19
	if (flush == 0)
		return;
D 18
	pti->pt_send |= TIOCPKT_FLUSH;
	ptsstart(tp);
E 18
I 18
	pti->pt_send |= flush;
E 19
I 19
	/* note: FLUSHREAD and FLUSHWRITE already ok */
	if (flush == 0) {
		flush = TIOCPKT_STOP;
		pti->pt_flags |= PF_STOPPED;
D 46
	} else {
E 46
I 46
	} else
E 46
		pti->pt_flags &= ~PF_STOPPED;
D 46
	}
E 46
D 21
	pti->pt_send = flush;
E 21
I 21
	pti->pt_send |= flush;
E 21
E 19
D 46
	ptcwakeup(tp);
E 46
I 46
	/* change of perspective */
	flag = 0;
	if (flush & FREAD)
		flag |= FWRITE;
	if (flush & FWRITE)
		flag |= FREAD;
D 49
	ptcwakeup(tp, flush);
E 49
I 49
	ptcwakeup(tp, flag);
E 49
E 46
E 18
}

E 17
I 12
D 15
ptcselect(dev)
E 15
I 15
D 80
ptcselect(dev, rw)
E 80
I 80
ptcselect(dev, rw, p)
E 80
E 15
	dev_t dev;
I 15
	int rw;
I 80
	struct proc *p;
E 80
E 15
{
I 79
D 80
	struct proc *curp = curproc;
E 80
E 79
	register struct tty *tp = &pt_tty[minor(dev)];
D 20
	struct pt_ioctl *pti;
E 20
I 20
	struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
E 20
D 80
	struct proc *p;
E 80
I 80
D 85
	struct proc *prev;
E 85
E 80
I 18
	int s;
E 18

D 14
	if ((tp->t_state&(CARR_ON|ISOPEN)) == 0)
E 14
I 14
D 15
	if ((tp->t_state&(CARR_ON|ISOPEN)) == 0) {
E 15
I 15
D 46
	if ((tp->t_state&(TS_CARR_ON|TS_ISOPEN)) == 0)
E 46
I 46
	if ((tp->t_state&TS_CARR_ON) == 0)
E 46
E 15
E 14
		return (1);
I 18
D 56
	s = spl5();
E 56
E 18
I 15
	switch (rw) {

	case FREAD:
I 56
		/*
		 * Need to block timeouts (ttrstart).
		 */
		s = spltty();
E 56
D 18
		if (tp->t_outq.c_cc)
E 18
I 18
D 46
		if (tp->t_outq.c_cc && (tp->t_state&TS_TTSTOP) == 0) {
E 46
I 46
		if ((tp->t_state&TS_ISOPEN) &&
I 53
		     tp->t_outq.c_cc && (tp->t_state&TS_TTSTOP) == 0) {
			splx(s);
			return (1);
		}
I 56
		splx(s);
E 56
		/* FALLTHROUGH */

	case 0:					/* exceptional */
		if ((tp->t_state&TS_ISOPEN) &&
E 53
		    (pti->pt_flags&PF_PKT && pti->pt_send ||
I 64
		     pti->pt_flags&PF_TIOC && pti->pt_ioc.c_cc ||
E 64
D 53
		     pti->pt_flags&PF_UCNTL && pti->pt_ucntl ||
		     tp->t_outq.c_cc && (tp->t_state&TS_TTSTOP) == 0)) {
E 53
I 53
D 56
		     pti->pt_flags&PF_UCNTL && pti->pt_ucntl)) {
E 53
E 46
			splx(s);
E 56
I 56
		     pti->pt_flags&PF_UCNTL && pti->pt_ucntl))
E 56
E 18
			return (1);
I 18
D 56
		}
E 56
E 18
D 20
		pti = &pt_ioctl[minor(dev)];
E 20
D 17
		if ((p = pti->pti_selr) && p->p_wchan == (caddr_t)&selwait)
			pti->pti_flags |= PTCRCOLL;
E 17
I 17
D 80
		if ((p = pti->pt_selr) && p->p_wchan == (caddr_t)&selwait)
E 80
I 80
D 85
		if ((prev = pti->pt_selr) && prev->p_wchan == (caddr_t)&selwait)
E 80
			pti->pt_flags |= PF_RCOLL;
E 17
		else
D 17
			pti->pti_selr = u.u_procp;
E 17
I 17
D 79
			pti->pt_selr = u.u_procp;
E 79
I 79
D 80
			pti->pt_selr = curp;
E 80
I 80
			pti->pt_selr = p;
E 85
I 85
		selrecord(p, &pti->pt_selr);
E 85
E 80
E 79
E 17
D 18
		return (0);
E 18
I 18
		break;
E 18

I 53

E 53
	case FWRITE:
D 18
		if (tp->t_rawq.c_cc + tp->t_canq.c_cc < TTYHOG/2)
E 18
I 18
D 20
		if (tp->t_rawq.c_cc + tp->t_canq.c_cc < TTYHOG/2) {
E 20
I 20
D 46
		if ((pti->pt_flags & PF_REMOTE) == 0 || tp->t_rawq.c_cc == 0) {
E 46
I 46
D 56
		if ((tp->t_state&TS_ISOPEN) &&
D 47
		    (((pti->pt_flags&PF_REMOTE) && tp->t_canq.c_cc) ||
		    (tp->t_rawq.c_cc + tp->t_canq.c_cc < TTYHOG - 2))) {
E 47
I 47
		    ((pti->pt_flags&PF_REMOTE) == 0 || tp->t_canq.c_cc == 0)) {
E 47
E 46
E 20
			splx(s);
E 18
			return (1);
E 56
I 56
		if (tp->t_state&TS_ISOPEN) {
			if (pti->pt_flags & PF_REMOTE) {
			    if (tp->t_canq.c_cc == 0)
				return (1);
			} else {
			    if (tp->t_rawq.c_cc + tp->t_canq.c_cc < TTYHOG-2)
				    return (1);
D 65
			    if (tp->t_canq.c_cc == 0 &&
D 57
			        tp->t_flags & (RAW|CBREAK) == 0)
E 57
I 57
			        (tp->t_flags & (RAW|CBREAK)) == 0)
E 65
I 65
			    if (tp->t_canq.c_cc == 0 && (tp->t_iflag&ICANON))
E 65
E 57
				    return (1);
			}
E 56
I 18
		}
E 18
D 20
		pti = &pt_ioctl[minor(dev)];
E 20
D 17
		if ((p = pti->pti_selw) && p->p_wchan == (caddr_t)&selwait)
			pti->pti_flags |= PTCWCOLL;
E 17
I 17
D 80
		if ((p = pti->pt_selw) && p->p_wchan == (caddr_t)&selwait)
E 80
I 80
D 85
		if ((prev = pti->pt_selw) && prev->p_wchan == (caddr_t)&selwait)
E 80
			pti->pt_flags |= PF_WCOLL;
E 17
		else
D 17
			pti->pti_selw = u.u_procp;
E 17
I 17
D 79
			pti->pt_selw = u.u_procp;
E 79
I 79
D 80
			pti->pt_selw = curp;
E 80
I 80
			pti->pt_selw = p;
E 85
I 85
		selrecord(p, &pti->pt_selw);
E 85
E 80
E 79
I 18
		break;
I 53

E 53
E 18
E 17
	}
I 18
D 56
	splx(s);
E 56
	return (0);
E 18
E 15
D 14
	if (tp->t_outq.c_cc)
E 14
I 14
}
D 15
	if (tp->t_outq.c_cc) {
E 14
		return (1);
I 14
}
E 14
	pti = &pt_ioctl[minor(dev)];
D 13
	if ((p = pti->pti_selr) && p->p_wchan == (caddr_t)select)
E 13
I 13
	if ((p = pti->pti_selr) && p->p_wchan == (caddr_t)&selwait)
E 13
		pti->pti_flags |= PTCRCOLL;
	else
		pti->pti_selr = u.u_procp;
	return (0);
}
E 15

E 12
D 27
ptcwrite(dev)
E 27
I 27
D 66
ptcwrite(dev, uio)
E 66
I 66
ptcwrite(dev, uio, flag)
E 66
E 27
D 15
dev_t dev;
E 15
I 15
	dev_t dev;
I 27
D 46
	struct uio *uio;
E 46
I 46
	register struct uio *uio;
I 86
	int flag;
E 86
E 46
E 27
E 15
D 8
{                       /* Stuff characters into PTY's input buffer */
E 8
I 8
D 12
{			/* Stuff characters into PTY's input buffer */
E 12
I 12
{
E 12
E 8
D 29
	register struct tty *tp;
E 29
I 29
	register struct tty *tp = &pt_tty[minor(dev)];
E 29
D 46
	register char *cp, *ce;
	register int cc;
E 46
I 46
D 78
	register struct iovec *iov;
	register char *cp;
E 78
I 78
	register u_char *cp;
E 78
	register int cc = 0;
E 46
D 78
	char locbuf[BUFSIZ];
E 78
I 78
	u_char locbuf[BUFSIZ];
E 78
I 15
	int cnt = 0;
I 20
	struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
I 29
	int error = 0;
E 29
E 20
E 15

D 29
	tp = &pt_tty[minor(dev)];
E 29
D 12
	if((tp->t_state&(CARR_ON|ISOPEN)) == 0)
E 12
I 12
D 15
	if ((tp->t_state&(CARR_ON|ISOPEN)) == 0)
E 15
I 15
D 46
	if ((tp->t_state&(TS_CARR_ON|TS_ISOPEN)) == 0)
E 15
E 12
D 29
		return;
E 29
I 29
		return (EIO);
E 29
D 12
	while(u.u_count) {
E 12
I 12
D 20
	while (u.u_count) {
E 20
I 20
	do {
E 20
E 12
D 27
		cc = MIN(u.u_count, BUFSIZ);
E 27
I 27
		register struct iovec *iov;

		if (uio->uio_iovcnt == 0)
			break;
		iov = uio->uio_iov;
		if (iov->iov_len == 0) {
I 41
D 44
			while (pti->pt_flags&PF_REMOTE && tp->t_rawq.c_cc != 0)
E 44
I 44
			while ((pti->pt_flags&PF_REMOTE) && tp->t_rawq.c_cc != 0)
E 44
				sleep((caddr_t)&tp->t_rawq.c_cf, TTIPRI);
			if (pti->pt_flags&PF_REMOTE) {
				(void) putc(0, &tp->t_rawq);
				wakeup((caddr_t)&tp->t_rawq);
			}
E 41
			uio->uio_iovcnt--;	
			uio->uio_iov++;
			if (uio->uio_iovcnt < 0)
				panic("ptcwrite");
			continue;
		}
		cc = MIN(iov->iov_len, BUFSIZ);
E 27
		cp = locbuf;
D 27
		iomove(cp, (unsigned)cc, B_WRITE);
E 27
I 27
D 29
		u.u_error = uiomove(cp, cc, UIO_WRITE, uio);
E 27
D 12
		if(u.u_error)
E 12
I 12
		if (u.u_error)
E 29
I 29
		error = uiomove(cp, cc, UIO_WRITE, uio);
		if (error)
E 29
E 12
			break;
		ce = cp + cc;
E 46
I 20
again:
D 46
		if (pti->pt_flags & PF_REMOTE) {
			if (tp->t_rawq.c_cc) {
				if (pti->pt_flags & PF_NBIO) {
D 27
					u.u_count += ce - cp;
E 27
I 27
					iov->iov_base -= ce - cp;
					iov->iov_len += ce - cp;
					uio->uio_resid += ce - cp;
					uio->uio_offset -= ce - cp;
E 27
D 29
					u.u_error = EWOULDBLOCK;
					return;
E 29
I 29
					return (EWOULDBLOCK);
E 29
				}
				sleep((caddr_t)&tp->t_rawq.c_cf, TTOPRI);
				goto again;
			}
D 22
			b_to_q(cp, cc, &tp->t_rawq);
			putc(0, &tp->t_rawq);
E 22
I 22
			(void) b_to_q(cp, cc, &tp->t_rawq);
			(void) putc(0, &tp->t_rawq);
E 22
			wakeup((caddr_t)&tp->t_rawq);
E 46
I 46
	if ((tp->t_state&TS_ISOPEN) == 0)
		goto block;
D 49
	if (cnt == 0 && pti->pt_flags & PF_REMOTE) {
		if (uio->uio_iovcnt <= 0)
E 46
D 29
			return;
E 29
I 29
			return (0);
E 49
I 49
	if (pti->pt_flags & PF_REMOTE) {
E 49
I 46
		if (tp->t_canq.c_cc)
			goto block;
D 49
		iov = uio->uio_iov;
		if (cc == 0 && iov->iov_len) {
			cc = MIN(iov->iov_len, BUFSIZ);
			cp = locbuf;
			error = uiomove(cp, cc, UIO_WRITE, uio);
			if (error)
				return (error);
			/* check again for safety */
			if ((tp->t_state&TS_ISOPEN) == 0)
				return (EIO);
			if (tp->t_canq.c_cc)
				goto block;
E 49
I 49
D 78
		while (uio->uio_iovcnt > 0 && tp->t_canq.c_cc < TTYHOG - 1) {
			iov = uio->uio_iov;
			if (iov->iov_len == 0) {
				uio->uio_iovcnt--;	
				uio->uio_iov++;
				continue;
			}
E 78
I 78
		while (uio->uio_resid > 0 && tp->t_canq.c_cc < TTYHOG - 1) {
E 78
			if (cc == 0) {
D 78
				cc = MIN(iov->iov_len, BUFSIZ);
				cc = MIN(cc, TTYHOG - 1 - tp->t_canq.c_cc);
E 78
I 78
				cc = min(uio->uio_resid, BUFSIZ);
				cc = min(cc, TTYHOG - 1 - tp->t_canq.c_cc);
E 78
				cp = locbuf;
D 67
				error = uiomove(cp, cc, UIO_WRITE, uio);
E 67
I 67
D 78
				error = uiomove(cp, cc, uio);
E 78
I 78
				error = uiomove((caddr_t)cp, cc, uio);
E 78
E 67
				if (error)
					return (error);
				/* check again for safety */
				if ((tp->t_state&TS_ISOPEN) == 0)
					return (EIO);
			}
			if (cc)
D 78
				(void) b_to_q(cp, cc, &tp->t_canq);
E 78
I 78
				(void) b_to_q((char *)cp, cc, &tp->t_canq);
E 78
			cc = 0;
E 49
E 46
E 29
		}
E 20
D 12
		while(cp < ce) {
			while(tp->t_delct && tp->t_rawq.c_cc >= TTYHOG - 2) {
E 12
I 12
D 46
		while (cp < ce) {
D 37
			while (tp->t_delct && tp->t_rawq.c_cc >= TTYHOG - 2) {
E 37
I 37
D 40
			while ((tp->t_delct || tp->t_canq.c_cc)
			&& (tp->t_rawq.c_cc + tp->t_canq.c_cc) >= TTYHOG - 2) {
E 40
I 40
			if ((tp->t_rawq.c_cc + tp->t_canq.c_cc) >= TTYHOG - 2 &&
			    (tp->t_canq.c_cc > 0)) {
E 40
E 37
E 12
				wakeup((caddr_t)&tp->t_rawq);
I 15
				if (tp->t_state & TS_NBIO) {
D 27
					u.u_count += ce - cp;
E 27
I 27
					iov->iov_base -= ce - cp;
					iov->iov_len += ce - cp;
					uio->uio_resid += ce - cp;
					uio->uio_offset -= ce - cp;
E 27
					if (cnt == 0)
D 29
						u.u_error = EWOULDBLOCK;
					return;
E 29
I 29
						return (EWOULDBLOCK);
					return (0);
E 29
				}
E 15
				/* Better than just flushing it! */
				/* Wait for something to be read */
				sleep((caddr_t)&tp->t_rawq.c_cf, TTOPRI);
I 20
				goto again;
E 46
I 46
D 49
		if (cc)
			(void) b_to_q(cp, cc, &tp->t_canq);
E 49
		(void) putc(0, &tp->t_canq);
		ttwakeup(tp);
		wakeup((caddr_t)&tp->t_canq);
		return (0);
	}
D 78
	while (uio->uio_iovcnt > 0) {
		iov = uio->uio_iov;
E 78
I 78
	while (uio->uio_resid > 0) {
E 78
		if (cc == 0) {
D 78
			if (iov->iov_len == 0) {
				uio->uio_iovcnt--;	
				uio->uio_iov++;
				continue;
E 46
E 20
			}
I 46
			cc = MIN(iov->iov_len, BUFSIZ);
E 78
I 78
			cc = min(uio->uio_resid, BUFSIZ);
E 78
			cp = locbuf;
D 67
			error = uiomove(cp, cc, UIO_WRITE, uio);
E 67
I 67
D 78
			error = uiomove(cp, cc, uio);
E 78
I 78
			error = uiomove((caddr_t)cp, cc, uio);
E 78
E 67
			if (error)
				return (error);
			/* check again for safety */
			if ((tp->t_state&TS_ISOPEN) == 0)
				return (EIO);
		}
D 49
		while (--cc >= 0) {
E 49
I 49
		while (cc > 0) {
			if ((tp->t_rawq.c_cc + tp->t_canq.c_cc) >= TTYHOG - 2 &&
D 56
			    (tp->t_canq.c_cc > 0)) {
E 56
I 56
D 65
			   (tp->t_canq.c_cc > 0 ||
			      tp->t_flags & (RAW|CBREAK))) {
E 65
I 65
			   (tp->t_canq.c_cc > 0 || !(tp->t_iflag&ICANON))) {
E 65
E 56
				wakeup((caddr_t)&tp->t_rawq);
				goto block;
			}
E 49
E 46
D 11
			ttyinput(*cp++, tp);
E 11
I 11
D 66
			(*linesw[tp->t_line].l_rint)(*cp++, tp);
E 66
I 66
D 78
			(*linesw[tp->t_line].l_rint)(*cp++&0377, tp);
E 78
I 78
			(*linesw[tp->t_line].l_rint)(*cp++, tp);
E 78
E 66
I 15
			cnt++;
I 49
			cc--;
E 49
E 15
E 11
		}
D 20
	}
E 20
I 20
D 27
	} while (u.u_count);
E 27
I 27
D 46
	} while (uio->uio_resid);
I 29
	return (error);
E 46
I 46
		cc = 0;
	}
	return (0);
block:
	/*
D 49
	 * Come here to wait for slave to open or for space
	 * in outq.
E 49
I 49
	 * Come here to wait for slave to open, for space
	 * in outq, or space in rawq.
E 49
	 */
	if ((tp->t_state&TS_CARR_ON) == 0)
		return (EIO);
D 66
	if (pti->pt_flags & PF_NBIO) {
E 66
I 66
D 67
	if ((pti->pt_flags & PF_NBIO) || (flag & FNDELAY)) {
E 67
I 67
D 78
	if ((pti->pt_flags & PF_NBIO) || (flag & IO_NDELAY)) {
E 67
E 66
D 49
		if (cnt == 0)
			return (EWOULDBLOCK);
E 49
		iov->iov_base -= cc;
		iov->iov_len += cc;
E 78
I 78
	if (flag & IO_NDELAY) {
		/* adjust for data copied in but not written */
E 78
		uio->uio_resid += cc;
D 78
		uio->uio_offset -= cc;
E 78
I 49
		if (cnt == 0)
			return (EWOULDBLOCK);
E 49
		return (0);
	}
I 66
D 74
if (ptydebug) printf("SLEEP(2) c_cf %d\n", u.u_procp->p_pid);
E 74
E 66
D 71
	sleep((caddr_t)&tp->t_rawq.c_cf, TTOPRI);
E 71
I 71
	if (error = tsleep((caddr_t)&tp->t_rawq.c_cf, TTOPRI | PCATCH,
D 78
	    ttyout, 0))
E 78
I 78
	    ttyout, 0)) {
		/* adjust for data copied in but not written */
		uio->uio_resid += cc;
E 78
		return (error);
I 78
	}
E 78
E 71
	goto again;
E 46
E 29
E 27
E 20
}

D 12
/* Note: Both slave and controlling device have the same routine for */
/* 'ioctl' (but note check for controller - 4/12/78:mob)*/
E 12
/*ARGSUSED*/
D 26
ptyioctl(dev, cmd, addr, flag)
D 12
caddr_t addr;
dev_t dev;
{					/* Read and write status bits */
E 12
I 12
	caddr_t addr;
E 26
I 26
D 84
ptyioctl(dev, cmd, data, flag)
	caddr_t data;
E 84
I 84
ptyioctl(dev, cmd, data, flag, p)
E 84
E 26
	dev_t dev;
I 84
D 96
	int cmd;
E 96
I 96
	u_long cmd;
E 96
	caddr_t data;
	int flag;
	struct proc *p;
E 84
{
E 12
D 21
	register struct tty *tp;
E 21
I 21
	register struct tty *tp = &pt_tty[minor(dev)];
	register struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
I 65
	register u_char *cc = tp->t_cc;
E 65
I 30
D 46
	int error;
E 46
I 46
	int stop, error;
I 51
D 83
	extern ttyinput();
E 83
E 51
E 46
E 30
E 21
D 13
	register int tbd;
E 13
D 12
#ifdef BLAND
	register int nld;
#endif
E 12

D 21
	tp = &pt_tty[minor(dev)];
E 21
D 12
		/* if controller stty then must flush to prevent a hang */
	if(cdevsw[major(dev)].d_open == ptcopen && cmd == TIOCSETP)
		while(getc(&tp->t_outq) >= 0);
	if(ttioctl(tp, cmd, addr, dev)) {
		if(cmd == TIOCSETP || cmd == TIOCSETN) {
#ifdef BLAND
			nld = tp->t_flags & NLDELAY;
#endif
			tbd = tp->t_flags & TBDELAY;
			tp->t_flags &= ~ALLDELAYS;
D 8
			if(tbd == TBDELAY)      /* Wants tab expansion */
E 8
I 8
			if(tbd == TBDELAY)	/* Wants tab expansion */
E 8
				tp->t_flags |= tbd;
#ifdef BLAND
D 8
			if(nld == NLDELAY)      /* Allow ANN ARBOR mode. */
E 8
I 8
			if(nld == NLDELAY)	/* Allow ANN ARBOR mode. */
E 8
				tp->t_flags |= nld;
#endif
		}
	} else
E 12
I 12
D 51
	/* IF CONTROLLER STTY THEN MUST FLUSH TO PREVENT A HANG ??? */
E 51
I 51
	/*
	 * IF CONTROLLER STTY THEN MUST FLUSH TO PREVENT A HANG.
	 * ttywflush(tp) will hang if there are characters in the outq.
	 */
I 73
	if (cmd == TIOCEXT) {
		/*
		 * When the EXTPROC bit is being toggled, we need
		 * to send an TIOCPKT_IOCTL if the packet driver
		 * is turned on.
		 */
		if (*(int *)data) {
			if (pti->pt_flags & PF_PKT) {
				pti->pt_send |= TIOCPKT_IOCTL;
D 93
				ptcwakeup(tp);
E 93
I 93
				ptcwakeup(tp, FREAD);
E 93
			}
			tp->t_lflag |= EXTPROC;
		} else {
D 97
			if ((tp->t_state & EXTPROC) &&
E 97
I 97
			if ((tp->t_lflag & EXTPROC) &&
E 97
			    (pti->pt_flags & PF_PKT)) {
				pti->pt_send |= TIOCPKT_IOCTL;
D 93
				ptcwakeup(tp);
E 93
I 93
				ptcwakeup(tp, FREAD);
E 93
			}
			tp->t_lflag &= ~EXTPROC;
		}
		return(0);
	} else
E 73
E 51
D 16
	if (cdevsw[major(dev)].d_open == ptcopen && cmd == TIOCSETP)
		while (getc(&tp->t_outq) >= 0);
E 16
I 16
D 26
	if (cdevsw[major(dev)].d_open == ptcopen) {
I 17
D 21
		register struct pt_ioctl *pti = &pt_ioctl[minor(dev)];
E 21
		if (cmd == TIOCPKT) {
			int packet;
D 22
			if (copyin((caddr_t)addr, &packet, sizeof (packet))) {
E 22
I 22
			if (copyin((caddr_t)addr, (caddr_t)&packet, sizeof (packet))) {
E 22
				u.u_error = EFAULT;
				return;
			}
			if (packet)
E 26
I 26
D 64
	if (cdevsw[major(dev)].d_open == ptcopen)
E 64
I 64
	if (cdevsw[major(dev)].d_open == ptcopen) {
		if ((cmd & 0xffff) == (TIOCIOANS(0) & 0xffff)) {
			if (!(pti->pt_flags & PF_LIOC) || pti->pt_ioc.c_cc)
				return (EINVAL);
			(void) b_to_q(data, IOCPARM_LEN(cmd), &pti->pt_ioc);
			wakeup((caddr_t)&pti->pt_ioc);
			return (0);
		}
E 64
		switch (cmd) {

I 75
		case TIOCGPGRP:
			/*
			 * We aviod calling ttioctl on the controller since,
			 * in that case, tp must be the controlling terminal.
			 */
			*(int *)data = tp->t_pgrp ? tp->t_pgrp->pg_id : 0;
			return (0);

E 75
		case TIOCPKT:
D 46
			if (*(int *)data)
E 46
I 46
			if (*(int *)data) {
				if (pti->pt_flags & PF_UCNTL)
					return (EINVAL);
E 46
E 26
				pti->pt_flags |= PF_PKT;
D 46
			else
E 46
I 46
			} else
E 46
				pti->pt_flags &= ~PF_PKT;
I 20
D 30
			return;
E 30
I 30
			return (0);
E 30
D 26
		}
		if (cmd == TIOCREMOTE) {
			int remote;
D 22
			if (copyin((caddr_t)addr, &remote, sizeof (remote))) {
E 22
I 22
			if (copyin((caddr_t)addr, (caddr_t)&remote, sizeof (remote))) {
E 22
				u.u_error = EFAULT;
				return;
			}
			if (remote)
E 26
I 26

I 46
		case TIOCUCNTL:
			if (*(int *)data) {
				if (pti->pt_flags & PF_PKT)
					return (EINVAL);
				pti->pt_flags |= PF_UCNTL;
			} else
				pti->pt_flags &= ~PF_UCNTL;
			return (0);

I 64
		case TIOCTIOC:
			if (*(int *)data) {
				if (pti->pt_flags & PF_UCNTL)
					return (EINVAL);
				pti->pt_flags |= PF_TIOC;
			} else {
				pti->pt_flags &= ~(PF_TIOC|PF_LIOC|PF_WIOC);
				while (pti->pt_ioc.c_cc)
					(void) getc(&pti->pt_ioc);
				wakeup((caddr_t)&pti->pt_ioc);
			}
			return (0);

		case TIOCBLK:
			if (*(int *)data)
				pti->pt_flags |= PF_BLOCK;
			else {
				if (pti->pt_flags & PF_OWAIT)
					wakeup((caddr_t)pti + 1);
				pti->pt_flags &= ~(PF_BLOCK|PF_OWAIT);
				ptswake(tp);
			}
			return (0);

E 64
E 46
		case TIOCREMOTE:
			if (*(int *)data)
E 26
				pti->pt_flags |= PF_REMOTE;
			else
				pti->pt_flags &= ~PF_REMOTE;
D 34
			flushtty(tp, FREAD|FWRITE);
E 34
I 34
			ttyflush(tp, FREAD|FWRITE);
E 34
E 20
D 30
			return;
E 30
I 30
			return (0);
E 30
D 26
		}
E 17
		if (cmd == FIONBIO) {
			int nbio;
D 17
			register struct pt_ioctl *pti;
E 17
D 22
			if (copyin(addr, &nbio, sizeof (nbio))) {
E 22
I 22
			if (copyin((caddr_t)addr, (caddr_t)&nbio, sizeof (nbio))) {
E 22
				u.u_error = EFAULT;
				return;
			}
D 17
			pti = &pt_ioctl[minor(dev)];
E 17
			if (nbio)
E 26
I 26

I 84
#ifdef COMPAT_43
E 84
D 78
		case FIONBIO:
			if (*(int *)data)
E 26
D 17
				pti->pti_flags |= PTCNBIO;
E 17
I 17
				pti->pt_flags |= PF_NBIO;
E 17
			else
D 17
				pti->pti_flags &= ~PTCNBIO;
E 17
I 17
				pti->pt_flags &= ~PF_NBIO;
E 17
D 30
			return;
E 30
I 30
			return (0);
E 30
I 26

E 78
I 64
		case FIONREAD:
			*(int *)data = tp->t_outq.c_cc;
			return (0);

E 64
D 65
		case TIOCSETP:
E 65
I 65
		case TIOCSETP:		
E 65
I 51
		case TIOCSETN:
I 84
#endif
E 84
		case TIOCSETD:
I 65
		case TIOCSETA:
		case TIOCSETAW:
		case TIOCSETAF:
D 69
		case TIOCSETAS:
		case TIOCSETAWS:
		case TIOCSETAFS:
E 69
I 69
D 78
		case JUNK_TIOCSETAS:
		case JUNK_TIOCSETAWS:
		case JUNK_TIOCSETAFS:
E 78
I 78
D 79
		case JUNK_TIOCSETAS:	/* XXX */
		case JUNK_TIOCSETAWS:	/* XXX */
		case JUNK_TIOCSETAFS:	/* XXX */
E 79
E 78
E 69
E 65
E 51
D 84
			while (getc(&tp->t_outq) >= 0)
				;
E 84
I 84
			ndflush(&tp->t_outq, tp->t_outq.c_cc);
E 84
			break;
I 73

		case TIOCSIG:
			if (*(unsigned int *)data >= NSIG)
				return(EINVAL);
			if ((tp->t_lflag&NOFLSH) == 0)
				ttyflush(tp, FREAD|FWRITE);
D 77
			pgsignal(tp->t_pgrp, *(unsigned int *)data);
E 77
I 77
			pgsignal(tp->t_pgrp, *(unsigned int *)data, 1);
			if ((*(unsigned int *)data == SIGINFO) &&
			    ((tp->t_lflag&NOKERNINFO) == 0))
				ttyinfo(tp);
E 77
			return(0);
E 73
E 26
		}
I 64
	} else if (pti->pt_flags & PF_TIOC) {
		while (pti->pt_flags & PF_LIOC) {
			pti->pt_flags |= PF_WIOC;
			switch (tsleep((caddr_t)&pti->pt_flags,TTIPRI-1,5*hz)) {
			case TS_OK:
				continue;
			case TS_SIG:
			case TS_TIME:
				return (EBUSY);
			}
		}
		pti->pt_flags |= PF_LIOC | PF_BLOCK;
		while (pti->pt_ioc.c_cc)
			(void) getc(&pti->pt_ioc);
		(void) b_to_q(&cmd, sizeof cmd, &pti->pt_ioc);
		if (cmd & IOC_IN)
			(void) b_to_q(data, IOCPARM_LEN(cmd), &pti->pt_ioc);
		ptcwakeup(tp, FREAD);
		switch (tsleep((caddr_t)&pti->pt_ioc, TTIPRI-1, 5*hz)) {
		case TS_SIG:
		case TS_TIME:
			while (pti->pt_ioc.c_cc)
				(void) getc(&pti->pt_ioc);
			if (pti->pt_flags & PF_WIOC)
				wakeup((caddr_t)&pti->pt_flags);
			if (pti->pt_flags & PF_OWAIT)
				wakeup((caddr_t)pti + 1);
			pti->pt_flags &= ~(PF_LIOC|PF_WIOC|PF_BLOCK|PF_OWAIT);
			ptswake(tp);
			return (EBUSY);
		case TS_OK:
			break;
		}
		if (pti->pt_ioc.c_cc == 0) {
			if (pti->pt_flags & PF_WIOC)
				wakeup((caddr_t)&pti->pt_flags);
			if (pti->pt_flags & PF_OWAIT)
				wakeup((caddr_t)pti + 1);
			pti->pt_flags &= ~(PF_LIOC|PF_WIOC|PF_BLOCK|PF_OWAIT);
			ptswake(tp);
			goto doioctl;
		}
		if (q_to_b(&pti->pt_ioc, &error, sizeof error) != sizeof error)
			error = EINVAL;
		if (error == 0 && cmd & IOC_OUT) {
			if (IOCPARM_LEN(cmd) != pti->pt_ioc.c_cc)
				error = EINVAL;
			else
				(void) q_to_b(&pti->pt_ioc, data,
				    pti->pt_ioc.c_cc);
		}
		while (pti->pt_ioc.c_cc)
			(void) getc(&pti->pt_ioc);
		if (pti->pt_flags & PF_WIOC)
			wakeup((caddr_t)&pti->pt_flags);
		if (pti->pt_flags & PF_OWAIT)
			wakeup((caddr_t)pti + 1);
		pti->pt_flags &= ~(PF_LIOC|PF_WIOC|PF_BLOCK|PF_OWAIT);
		ptswake(tp);
		return (error);
	}

 doioctl:
E 64
D 26
		if (cmd == TIOCSETP)
			while (getc(&tp->t_outq) >= 0);
	}
E 16
	if (ttioctl(tp, cmd, addr, dev) == 0)
E 26
I 26
D 30
	if (ttioctl(tp, cmd, data, dev) == 0)
E 26
E 12
		u.u_error = ENOTTY;
E 30
I 30
D 43
	error = ttioctl(tp, cmd, data, dev);
E 43
I 43
D 65
	error = ttioctl(tp, cmd, data, flag);
E 65
I 65
D 84
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
E 84
I 84
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
E 84
	if (error < 0)
		 error = ttioctl(tp, cmd, data, flag);
E 65
I 51
D 83
	/*
	 * Since we use the tty queues internally,
	 * pty's can't be switched to disciplines which overwrite
	 * the queues.  We can't tell anything about the discipline
	 * from here...
I 64
	 *
	 * Nb: this is not really good enough, the line disc open routine
	 * may have done anything at all, no guarantees that close
	 * will fix it.  This also has the effect of losing the
	 * previous discipline, which an error on a TIOCSETD shouldn't
	 * do...  Sometime it should be done via an explicit check
	 * for TIOCSETD, then check to see what linesw[new_number].l_rint
	 * really is.
E 64
	 */
	if (linesw[tp->t_line].l_rint != ttyinput) {
D 81
		(*linesw[tp->t_line].l_close)(tp);
E 81
I 81
		(*linesw[tp->t_line].l_close)(tp, flag);
E 81
D 78
		tp->t_line = 0;
E 78
I 78
		tp->t_line = TTYDISC;
E 78
D 66
		(void)(*linesw[tp->t_line].l_open)(dev, tp);
E 66
I 66
		(void)(*linesw[tp->t_line].l_open)(dev, tp, flag);
E 66
		error = ENOTTY;
	}
E 83
I 64

E 64
E 51
E 43
D 46
	if (error < 0)
E 46
I 46
	if (error < 0) {
		if (pti->pt_flags & PF_UCNTL &&
D 59
		    (cmd & ~0xff) == _IO(u,0)) {
E 59
I 59
		    (cmd & ~0xff) == UIOCCMD(0)) {
E 59
			if (cmd & 0xff) {
				pti->pt_ucntl = (u_char)cmd;
				ptcwakeup(tp, FREAD);
			}
			return (0);
		}
E 46
		error = ENOTTY;
I 73
	}
	/*
	 * If external processing and packet mode send ioctl packet.
	 */
	if ((tp->t_lflag&EXTPROC) && (pti->pt_flags & PF_PKT)) {
		switch(cmd) {
		case TIOCSETA:
		case TIOCSETAW:
		case TIOCSETAF:
I 84
#ifdef COMPAT_43
E 84
D 78
		case JUNK_TIOCSETAS:
		case JUNK_TIOCSETAWS:
		case JUNK_TIOCSETAFS:
E 78
I 78
D 79
		case JUNK_TIOCSETAS:	/* XXX */
		case JUNK_TIOCSETAWS:	/* XXX */
		case JUNK_TIOCSETAFS:	/* XXX */
E 79
E 78
		case TIOCSETP:
		case TIOCSETN:
D 84
#ifdef	COMPAT_43
E 84
I 84
#endif
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 84
		case TIOCSETC:
		case TIOCSLTC:
		case TIOCLBIS:
		case TIOCLBIC:
		case TIOCLSET:
#endif
			pti->pt_send |= TIOCPKT_IOCTL;
I 93
			ptcwakeup(tp, FREAD);
E 93
		default:
			break;
		}
E 73
E 30
I 21
D 32
	{ int stop = (tp->t_un.t_chr.t_stopc == ('s'&037) &&
		      tp->t_un.t_chr.t_startc == ('q'&037));
E 32
I 32
D 45
	{ int stop = (tp->t_stopc == ('s'&037) &&
E 45
I 45
D 46
	{ int stop = ((tp->t_flags & RAW) == 0 &&
		      tp->t_stopc == ('s'&037) &&
E 45
		      tp->t_startc == ('q'&037));
E 46
I 46
	}
D 65
	stop = (tp->t_flags & RAW) == 0 &&
D 62
	    tp->t_stopc == CTRL(s) && tp->t_startc == CTRL(q);
E 62
I 62
	    tp->t_stopc == CTRL('s') && tp->t_startc == CTRL('q');
E 65
I 65
	stop = (tp->t_iflag & IXON) && CCEQ(cc[VSTOP], CTRL('s')) 
		&& CCEQ(cc[VSTART], CTRL('q'));
E 65
E 62
E 46
E 32
	if (pti->pt_flags & PF_NOSTOP) {
		if (stop) {
D 54
			pti->pt_send &= TIOCPKT_NOSTOP;
E 54
I 54
			pti->pt_send &= ~TIOCPKT_NOSTOP;
E 54
			pti->pt_send |= TIOCPKT_DOSTOP;
			pti->pt_flags &= ~PF_NOSTOP;
D 46
			ptcwakeup(tp);
E 46
I 46
			ptcwakeup(tp, FREAD);
E 46
		}
	} else {
D 46
		if (stop == 0) {
E 46
I 46
		if (!stop) {
E 46
			pti->pt_send &= ~TIOCPKT_DOSTOP;
			pti->pt_send |= TIOCPKT_NOSTOP;
			pti->pt_flags |= PF_NOSTOP;
D 46
			ptcwakeup(tp);
E 46
I 46
			ptcwakeup(tp, FREAD);
E 46
		}
D 46
	}
E 46
	}
I 30
	return (error);
E 30
E 21
}
I 6
D 91
#endif
E 91
E 6
E 1
