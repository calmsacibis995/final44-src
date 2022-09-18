h54846
s 00010/00147/00048
d D 8.6 94/03/28 07:33:29 bostic 98 97
c break termios.h, ioctl.h up into filio.h, sockio.h, ttycom.h
c termios.h, ioccom.h and ioctl.h, a la SunOS
e
s 00007/00003/00188
d D 8.5 94/01/21 17:25:09 bostic 97 96
c add USL's copyright notice
e
s 00000/00004/00191
d D 8.4 94/01/11 16:42:59 mckusick 96 94
c clean up include syntax
e
s 00001/00001/00194
d R 8.4 94/01/11 15:55:24 mckusick 95 94
c clean up include syntax
e
s 00001/00001/00194
d D 8.3 94/01/07 17:36:35 bostic 94 93
c IOCBASECMD was masking out 13 bits of command, instead of the 13 bits
c of length
c From BSDI users mailing list Chris Demetriou and Mike Karels
e
s 00004/00006/00191
d D 8.2 94/01/04 16:16:31 bostic 93 92
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00000/00000/00197
d D 8.1 93/06/04 16:48:00 bostic 92 91
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00006/00195
d D 7.22 93/06/04 16:34:38 sklower 91 89
c get rid of arp entry related ioctls
e
s 00002/00002/00199
d R 8.1 93/06/02 19:53:43 bostic 90 89
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00003/00195
d D 7.21 92/07/08 15:29:29 sklower 89 88
c changes to support ip multicasting from lbl
e
s 00002/00002/00196
d D 7.20 92/02/05 19:49:18 torek 88 87
c add COMPAT_SUNOS
e
s 00014/00013/00184
d D 7.19 91/06/26 11:38:01 marc 87 86
c move compatability include outside _IOCTL_H_ test
e
s 00001/00000/00196
d D 7.18 91/04/09 15:16:07 marc 86 85
c add TIOCDRAIN to implement POSIX.1 tcdrain() function
e
s 00000/00005/00196
d D 7.17 91/04/08 16:03:49 marc 85 84
c remove conversion ioctls
e
s 00010/00000/00191
d D 7.16 91/02/22 09:53:58 donn 84 83
c Prototype declaration.
e
s 00000/00002/00191
d D 7.15 91/02/15 14:32:12 bostic 83 82
c delete '#ifndef _IO', ioctl.h is protected from reinclusion
e
s 00014/00026/00179
d D 7.14 91/02/15 14:31:14 bostic 82 81
c add Berkeley specific copyright notice
e
s 00003/00003/00202
d D 7.13 91/02/05 17:04:03 bostic 81 80
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00003/00000/00202
d D 7.12 90/05/18 13:45:53 marc 80 79
c line mode telnet mods
e
s 00000/00004/00202
d D 7.11 90/01/09 12:52:07 marc 79 78
c remove TC[SG]ET defines - they're not compatable
e
s 00027/00136/00179
d D 7.10 89/11/20 18:11:42 marc 78 77
c rearrange for posix; move out old ioctls
e
s 00015/00005/00300
d D 7.9 89/09/04 14:28:10 karels 77 76
c various people's changes: add USE_OLD_TTY, fix up compat, renumber add/delete
c interface ioctls
e
s 00035/00018/00270
d D 7.8 88/12/20 20:47:00 karels 76 75
c checkpoint
e
s 00024/00011/00264
d D 7.7 88/10/12 15:19:16 marc 75 73
c termios line discipline
e
s 00007/00002/00273
d D 7.6.1.1 88/01/13 15:47:04 mckusick 74 73
c add ioctls from kre for mux
e
s 00077/00077/00198
d D 7.6 87/12/18 11:24:36 bostic 73 72
c fix for ANSI C
e
s 00001/00001/00274
d D 7.5 87/11/07 14:46:45 karels 72 70
c yech, how'd we get a dup
e
s 00001/00001/00274
d R 7.5 87/11/07 14:45:18 karels 71 70
c yech, how'd we get a dup
e
s 00002/00002/00273
d D 7.4 87/05/27 16:03:54 mckusick 70 69
c fix comments on FIOCLEX/FIONCLEX from fair@ucbarpa.berkeley.edu (Erik E. Fair)
e
s 00006/00004/00269
d D 7.3 87/02/19 14:16:28 karels 69 68
c larger ioctl's (for disklabels)
e
s 00001/00000/00272
d D 7.2 86/08/09 18:03:09 karels 68 67
c TIOCCONS ala sun
e
s 00001/00001/00271
d D 7.1 86/06/04 23:24:07 mckusick 67 66
c 4.3BSD release version
e
s 00001/00000/00271
d D 6.22 86/05/19 16:30:52 karels 66 65
c add UIOCCMD
e
s 00010/00008/00261
d D 6.21 86/02/20 10:54:37 bloom 65 64
c Someone forgot that ioctl.h didn't require types.h
e
s 00024/00007/00245
d D 6.20 86/02/19 22:38:45 karels 64 63
c pretty up winsize defn; add Sun-compat (for bloom)
e
s 00001/00001/00251
d D 6.19 86/02/17 17:15:47 karels 63 62
c typo
e
s 00001/00000/00251
d D 6.18 86/02/10 08:39:29 karels 62 61
c serial IP disc
e
s 00002/00000/00249
d D 6.17 86/02/08 14:19:37 karels 61 60
c add get/set metric IF ioctls
e
s 00000/00021/00249
d D 6.16 86/01/18 12:19:24 karels 60 59
c rm bbn junk
e
s 00001/00002/00269
d D 6.15 85/11/06 18:20:03 sam 59 58
c delete extraneous line discipline what with ioctl to set type
e
s 00004/00002/00267
d D 6.14 85/08/25 16:18:13 walsh 58 57
c adjusted tcp noactivity timer ioctl
e
s 00020/00000/00249
d D 6.13 85/08/22 09:57:43 walsh 57 56
c added ioctls to adjust bbn net protocol timers...
e
s 00002/00001/00247
d D 6.12 85/08/13 05:23:11 lepreau 56 55
c add PASS8: pass all 8 bits of input
e
s 00001/00000/00247
d D 6.11 85/06/08 15:44:58 sam 55 54
c fix copyright botch of comment
e
s 00007/00001/00240
d D 6.10 85/06/08 14:59:42 mckusick 54 53
c Add copyright
e
s 00001/00001/00240
d D 6.9 85/03/13 16:22:19 mckusick 53 52
c from sun!shannon
e
s 00004/00000/00237
d D 6.8 85/03/07 22:00:12 karels 52 51
c new pty, socket ioctls
e
s 00002/00002/00235
d D 6.7 85/01/24 19:31:00 bloom 51 50
c rename window size structure elements to begin "ws_"
e
s 00010/00000/00227
d D 6.6 85/01/03 08:39:47 bloom 50 48
c added window size support
e
s 00010/00000/00227
d R 6.6 84/12/31 12:44:09 bloom 49 48
c added window size support
e
s 00002/00002/00225
d D 6.5 84/08/28 17:29:08 bloom 48 47
c Change include paths.  No more ../h
e
s 00015/00001/00212
d D 6.4 84/08/02 14:27:13 karels 47 46
c don't get sgtty from /usr/include
e
s 00002/00001/00211
d D 6.3 84/04/13 10:25:32 karels 46 45
c add SIOCGIFBRDADDR
e
s 00004/00000/00208
d D 6.2 84/03/20 15:24:08 karels 45 44
c new ioctls for ARP
e
s 00000/00000/00208
d D 6.1 83/07/29 06:12:46 sam 44 43
c 4.2 distribution
e
s 00001/00010/00207
d D 4.34 83/06/13 02:59:27 sam 43 42
c new stuff goes...
e
s 00011/00009/00206
d D 4.33 83/06/12 19:49:14 sam 42 41
c revamp network ioctls
e
s 00002/00000/00213
d D 4.32 83/05/27 13:58:31 sam 41 40
c these will go away in a moment ...
e
s 00002/00000/00211
d D 4.31 83/05/18 02:41:57 sam 40 39
c sun changes
e
s 00016/00016/00195
d D 4.30 83/03/19 18:12:24 sam 39 38
c must make SIOCGIF stuff _IOWR so interface name is copied in
e
s 00001/00001/00210
d D 4.29 83/03/19 14:51:17 sam 38 37
c SIOCGIFCONF is read + write
e
s 00004/00000/00207
d D 4.28 83/03/19 10:33:30 sam 37 36
c water marks
e
s 00007/00007/00200
d D 4.27 83/03/15 18:16:51 sam 36 35
c socket ioctls
e
s 00000/00006/00207
d D 4.26 82/12/17 12:11:10 sam 35 34
c sun merge
e
s 00053/00036/00160
d D 4.25 82/12/13 17:47:31 sam 34 33
c put back L* for compatibility and add some new ones to get at ttychars
e
s 00077/00045/00119
d D 4.24 82/12/05 21:53:27 sam 33 32
c reorganize for new tty structure; include new files needed
e
s 00001/00000/00163
d D 4.23 82/11/22 17:16:00 sam 32 31
c put back TIOCSTI
e
s 00006/00000/00157
d D 4.22 82/10/31 15:58:42 root 31 30
c add keyboard and mouse ioctls (for sun)
e
s 00072/00057/00085
d D 4.21 82/08/01 19:20:16 sam 30 29
c new ioctl's
e
s 00002/00000/00140
d D 4.20 82/06/26 22:18:16 sam 29 28
c tablet line disciplines from lucas
e
s 00007/00005/00133
d D 4.19 82/03/11 23:44:10 wnj 28 27
c for remote ^S/^Q
e
s 00003/00000/00135
d D 4.18 82/03/03 11:10:43 root 27 26
c new ones for routing
e
s 00001/00000/00134
d D 4.17 82/02/18 13:21:10 wnj 26 25
c TIOCREMOTE
e
s 00017/00000/00117
d D 4.16 82/02/08 22:53:28 root 25 24
c modem control ioctl's for DZ32
e
s 00002/00002/00115
d D 4.15 82/01/24 18:45:40 wnj 24 23
c TIOC{EXCL,NXCL}
e
s 00002/00000/00115
d D 4.14 82/01/19 02:01:01 wnj 23 22
c TIOCSTOP and TIOCSTART
e
s 00006/00000/00109
d D 4.13 82/01/17 21:49:36 wnj 22 21
c add pty packet generation codes
e
s 00005/00000/00104
d D 4.12 82/01/17 01:03:42 wnj 21 20
c out of band on sockets
e
s 00007/00000/00097
d D 4.11 82/01/13 10:51:09 wnj 20 19
c SIOC's and FIO{NBIO,ASYNC}
e
s 00002/00000/00095
d D 4.10 81/12/21 12:01:45 root 19 18
c add SIOCDONE
e
s 00003/00003/00092
d D 4.9 81/10/17 16:14:17 wnj 18 17
c cleanup (mpx removal, old tty removal, beginnings of select)
e
s 00001/00000/00094
d D 4.8 81/08/31 01:12:25 wnj 17 16
c LNOFLSH (for EMACS)
e
s 00015/00014/00079
d D 4.7 81/03/17 18:44:55 wnj 16 15
c add LDECCTQ and fix rkreg names
e
s 00000/00018/00093
d D 4.6 81/02/25 23:29:40 wnj 15 14
c functional version with %b printf, etc
e
s 00000/00037/00111
d D 4.5 81/02/23 20:48:34 wnj 14 13
c delete non-distributed stuff
e
s 00001/00001/00147
d D 4.4 81/02/19 21:40:52 wnj 13 12
c %G%->%E%
e
s 00007/00000/00141
d D 4.3 81/01/26 20:43:04 wnj 12 11
c chaos
e
s 00027/00009/00114
d D 4.2 80/12/17 12:00:50 wnj 11 10
c changes per datakit, etc
e
s 00000/00000/00123
d D 4.1 80/11/09 17:01:07 bill 10 9
c stamp for 4bsd
e
s 00001/00003/00122
d D 3.9 80/09/27 17:54:33 bill 9 8
c locals poof
e
s 00002/00000/00123
d D 3.8 80/09/16 17:26:43 bill 8 7
c add TIOCSTI
e
s 00000/00001/00123
d D 3.7 80/07/18 14:53:42 bill 7 6
c minor
e
s 00001/00000/00123
d D 3.6 80/07/12 14:33:38 bill 6 5
c add OKI stuff
e
s 00001/00000/00122
d D 3.5 80/06/22 12:39:21 bill 5 4
c ???
e
s 00001/00001/00121
d D 3.4 80/06/07 02:58:09 bill 4 3
c %H%->%G%
e
s 00020/00020/00102
d D 3.3 80/06/04 13:26:44 bill 3 2
c reformat
e
s 00002/00002/00120
d D 3.2 80/05/24 19:46:40 bill 2 1
c sys
e
s 00122/00000/00000
d D 3.1 80/05/18 20:05:58 bill 1 0
c date and time created 80/05/18 20:05:58 by bill
e
u
U
f b 
t
T
I 76
D 78
#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE	((unsigned char)'\377')
#endif
E 78
E 76
I 1
D 4
/*	%M%	%I%	%H%	*/
E 4
I 4
D 13
/*	%M%	%I%	%G%	*/
E 13
I 13
D 54
/*	%M%	%I%	%E%	*/
E 54
E 13
E 4
D 82
/*
I 54
D 67
 * Copyright (c) 1982 Regents of the University of California.
E 67
I 67
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 67
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 82
I 82
/*-
D 91
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
E 91
I 91
D 97
 * Copyright (c)
 *	1982, 1986, 1990, 1993  The Regents of the University of California.
E 91
 * All rights reserved.
E 97
I 97
D 98
 * Copyright (c) 1982, 1986, 1990, 1993
E 98
I 98
 * Copyright (c) 1982, 1986, 1990, 1993, 1994
E 98
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 97
E 82
 *
I 82
 * %sccs.include.redist.c%
 *
E 82
 *	%W% (Berkeley) %G%
 */

I 55
D 82
/*
E 55
E 54
D 33
 * ioctl definitions, and special character and local tty definitions
E 33
I 33
 * Ioctl definitions
E 33
 */
E 82
D 81
#ifndef	_IOCTL_
#define	_IOCTL_
E 81
I 81
D 93
#ifndef	_IOCTL_H_
#define	_IOCTL_H_
E 93
I 93
#ifndef	_SYS_IOCTL_H_
#define	_SYS_IOCTL_H_
E 93
E 81
I 33
D 78
#ifdef KERNEL
D 48
#include "../h/ttychars.h"
#include "../h/ttydev.h"
E 48
I 48
#include "ttychars.h"
#include "ttydev.h"
E 48
#else
#include <sys/ttychars.h>
#include <sys/ttydev.h>
#endif
E 78

D 43
#ifndef NOCOMPAT
E 43
D 47
#include <sgtty.h>
E 47
E 33
D 78
struct tchars {
	char	t_intrc;	/* interrupt */
	char	t_quitc;	/* quit */
	char	t_startc;	/* start output */
	char	t_stopc;	/* stop output */
	char	t_eofc;		/* end-of-file */
	char	t_brkc;		/* input delimiter (like nl) */
};
struct ltchars {
	char	t_suspc;	/* stop process signal */
D 2
	char	t_dstopc;	/* delayed stop process signal */
E 2
I 2
	char	t_dsuspc;	/* delayed stop process signal */
E 2
	char	t_rprntc;	/* reprint line */
	char	t_flushc;	/* flush output (toggles) */
	char	t_werasc;	/* word erase */
	char	t_lnextc;	/* literal next character */
D 9
	char	t_lerase;	/* local erase */
	char	t_lkill;	/* local kill */
	char	t_lintr;	/* local interrupt */
E 9
};
I 47

E 78
D 98
/*
D 78
 * Structure for TIOCGETP and TIOCSETP ioctls.
 */

#ifndef _SGTTYB_
#define	_SGTTYB_
struct sgttyb {
	char	sg_ispeed;		/* input speed */
	char	sg_ospeed;		/* output speed */
	char	sg_erase;		/* erase character */
	char	sg_kill;		/* kill character */
	short	sg_flags;		/* mode flags */
};
#endif
E 47
I 33
D 43
#endif
E 43
E 33

I 50
/*
E 78
D 64
 * Window size structure
E 64
I 64
D 82
 * Window/terminal size structure.
 * This information is stored by the kernel
 * in order to provide a consistent interface,
 * but is not used by the kernel.
I 65
 *
 * Type must be "unsigned short" so that types.h not required.
E 82
I 82
 * Window/terminal size structure.  This information is stored by the kernel
 * in order to provide a consistent interface, but is not used by the kernel.
E 82
E 65
E 64
 */
struct winsize {
D 51
	unsigned short	row, col;		/* character size of window */
	unsigned short	xpixel, ypixel;		/* pixel size of window */
E 51
I 51
D 64
	unsigned short	ws_row, ws_col;		/* character size of window */
	unsigned short	ws_xpixel, ws_ypixel;	/* pixel size of window */
E 64
I 64
D 65
	u_short	ws_row;			/* rows, in characters */
	u_short	ws_col;			/* columns, in characters */
	u_short	ws_xpixel;		/* horizontal size, pixels */
	u_short	ws_ypixel;		/* vertical size, pixels */
E 65
I 65
D 82
	unsigned short	ws_row;			/* rows, in characters */
	unsigned short	ws_col;			/* columns, in characters */
	unsigned short	ws_xpixel;		/* horizontal size, pixels */
	unsigned short	ws_ypixel;		/* vertical size, pixels */
E 82
I 82
	unsigned short	ws_row;		/* rows, in characters */
	unsigned short	ws_col;		/* columns, in characters */
	unsigned short	ws_xpixel;	/* horizontal size, pixels */
	unsigned short	ws_ypixel;	/* vertical size, pixels */
E 82
E 65
E 64
E 51
};
E 98
I 98
#include <sys/ttycom.h>
E 98

I 64
/*
D 98
 * Pun for SUN.
E 98
I 98
 * Pun for SunOS prior to 3.2.  SunOS 3.2 and later support TIOCGWINSZ
 * and TIOCSWINSZ (yes, even 3.2-3.5, the fact that it wasn't documented
 * nonwithstanding).
E 98
 */
struct ttysize {
D 65
	u_short	ts_lines;
	u_short	ts_cols;
	u_short	ts_xxx;
	u_short	ts_yyy;
E 65
I 65
	unsigned short	ts_lines;
	unsigned short	ts_cols;
	unsigned short	ts_xxx;
	unsigned short	ts_yyy;
E 65
};
#define	TIOCGSIZE	TIOCGWINSZ
#define	TIOCSSIZE	TIOCSWINSZ

E 64
E 50
I 40
D 83
#ifndef _IO
E 83
E 40
D 98
/*
D 33
 * local mode settings
 */
D 16
#define	LCRTBS	01		/* correct backspacing for crt */
D 3
#define LPRTERA 02		/* printing terminal \ ... / erase */
E 3
I 3
#define	LPRTERA 02		/* printing terminal \ ... / erase */
E 3
#define	LCRTERA	04		/* do " \b " to wipe out character */
D 3
#define LTILDE	010		/* IIASA - hazeltine tilde kludge */
#define LMDMBUF	020		/* IIASA - start/stop output on carrier intr */
#define LLITOUT	040		/* IIASA - suppress any output translations */
D 2
#define LTOSTOP	0100		/* send stop for background tty output */
E 2
I 2
#define LTOSTOP	0100		/* send stop for any background tty output */
E 2
#define LFLUSHO	0200		/* flush output sent to terminal */
#define LNOHANG 0400		/* IIASA - don't send hangup on carrier drop */
#define LETXACK 01000		/* IIASA - diablo style buffer hacking */
E 3
I 3
#define	LTILDE	010		/* IIASA - hazeltine tilde kludge */
#define	LMDMBUF	020		/* IIASA - start/stop output on carrier intr */
#define	LLITOUT	040		/* IIASA - suppress any output translations */
#define	LTOSTOP	0100		/* send stop for any background tty output */
#define	LFLUSHO	0200		/* flush output sent to terminal */
#define	LNOHANG 0400		/* IIASA - don't send hangup on carrier drop */
#define	LETXACK 01000		/* IIASA - diablo style buffer hacking */
E 3
#define	LCRTKIL	02000		/* erase whole line on kill with " \b " */
D 3
#define LINTRUP 04000		/* interrupt on every input char - SIGTINT */
E 3
I 3
#define	LINTRUP 04000		/* interrupt on every input char - SIGTINT */
E 3
#define	LCTLECH	010000		/* echo control characters as ^X */
#define	LPENDIN	020000		/* tp->t_rawq is waiting to be reread */
E 16
I 16
#define	LCRTBS	0000001		/* correct backspacing for crt */
#define	LPRTERA 0000002		/* printing terminal \ ... / erase */
#define	LCRTERA	0000004		/* do " \b " to wipe out character */
#define	LTILDE	0000010		/* IIASA - hazeltine tilde kludge */
#define	LMDMBUF	0000020		/* IIASA - start/stop output on carrier intr */
#define	LLITOUT	0000040		/* IIASA - suppress any output translations */
#define	LTOSTOP	0000100		/* send stop for any background tty output */
#define	LFLUSHO	0000200		/* flush output sent to terminal */
#define	LNOHANG 0000400		/* IIASA - don't send hangup on carrier drop */
#define	LETXACK 0001000		/* IIASA - diablo style buffer hacking */
#define	LCRTKIL	0002000		/* erase whole line on kill with " \b " */
D 18
#define	LINTRUP 0004000		/* interrupt on every input char - SIGTINT */
E 18
I 18
#define	L004000	0004000
E 18
#define	LCTLECH	0010000		/* echo control characters as ^X */
#define	LPENDIN	0020000		/* tp->t_rawq is waiting to be reread */
#define	LDECCTQ 0040000		/* only ^Q starts after ^S */
I 17
#define	LNOFLSH 0100000		/* dont flush output on signals */
E 17
E 16

/* local state */
D 3
#define LSBKSL	01		/* state bit for lowercase backslash work */
E 3
I 3
#define	LSBKSL	01		/* state bit for lowercase backslash work */
E 3
#define	LSQUOT	02		/* last character input was \ */
D 3
#define LSERASE	04		/* within a \.../ for LPRTRUB */
E 3
I 3
#define	LSERASE	04		/* within a \.../ for LPRTRUB */
E 3
#define	LSLNCH	010		/* next character is literal */
#define	LSTYPEN	020		/* retyping suspended input (LPENDIN) */
I 8
#define	LSCNTTB	040		/* counting width of tab; leave LFLUSHO alone */
E 8

I 25
/* modem control */
#define	MLE	0001		/* line enable */
#define	MDTR	0002		/* data terminal ready */
#define	MRTS	0004		/* request to send */
#define	MST	0010		/* secondary transmit */
#define	MSR	0020		/* secondary receive */
#define	MCTS	0040		/* clear to send */
#define	MCAR	0100		/* carrier detect */
#define	MCD	MCAR
#define	MRNG	0200		/* ring */
#define	MRI	MRNG
#define	MDSR	0400		/* data set ready */

E 25
/*
E 33
I 30
D 82
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
D 69
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
E 69
I 69
 * word.  The high 3 bits of the upper word are used
 * to encode the in/out status of the parameter.
E 82
I 82
 * Ioctl's have the command encoded in the lower word, and the size of
 * any in or out parameters in the upper word.  The high 3 bits of the
 * upper word are used to encode the in/out status of the parameter.
E 82
E 69
 */
D 69
#define	IOCPARM_MASK	0x7f		/* parameters must be < 128 bytes */
E 69
I 69
#define	IOCPARM_MASK	0x1fff		/* parameter length, at most 13 bits */
#define	IOCPARM_LEN(x)	(((x) >> 16) & IOCPARM_MASK)
I 76
D 94
#define	IOCBASECMD(x)	((x) & ~IOCPARM_MASK)
E 94
I 94
#define	IOCBASECMD(x)	((x) & ~(IOCPARM_MASK << 16))
E 94
#define	IOCGROUP(x)	(((x) >> 8) & 0xff)
E 98
I 98
#include <sys/ioccom.h>
E 98

E 76
D 98
#define	IOCPARM_MAX	NBPG		/* max size of ioctl, mult. of NBPG */
E 69
#define	IOC_VOID	0x20000000	/* no parameters */
#define	IOC_OUT		0x40000000	/* copy out parameters */
#define	IOC_IN		0x80000000	/* copy in parameters */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
I 69
D 74
#define	IOC_DIRMASK	0xe0000000	/* mask for IN/OUT/VOID */
E 98
I 98
#include <sys/filio.h>
#include <sys/sockio.h>
E 98
E 74
I 74
#define	IOC_DIRMASK	(IOC_IN|IOC_OUT|IOC_VOID)
E 74
E 69
D 76
/* the 0x20000000 is so we can distinguish new ioctl's from old */
D 73
#define	_IO(x,y)	(IOC_VOID|('x'<<8)|y)
#define	_IOR(x,y,t)	(IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
#define	_IOW(x,y,t)	(IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
E 73
I 73
#define	_IO(x,y)	(IOC_VOID|(x<<8)|y)
#define	_IOR(x,y,t)	(IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
#define	_IOW(x,y,t)	(IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
E 76
I 76

D 89
#define _IOC(inout,group,num,len) \
E 89
I 89
D 98
#define	_IOC(inout,group,num,len) \
E 89
	(inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
D 77
#define	_IO(g,n)	_IOC(IOC_VOID,	0, (g), (n))
E 77
I 77
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
E 77
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))
E 76
E 73
/* this should be _IORW, but stdio got there first */
D 73
#define	_IOWR(x,y,t)	(IOC_INOUT|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
E 73
I 73
D 76
#define	_IOWR(x,y,t)	(IOC_INOUT|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
E 76
I 76
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))
E 76
I 74
#define	_IOWX(x,y,s)	(IOC_IN|(((s)&IOCPARM_MASK)<<16)|(x<<8)|(y))
E 74
E 73
I 40
D 83
#endif
E 83
E 40

I 78
D 82

E 78
/*
E 30
 * tty ioctl commands
 */
I 77
D 78
#ifdef USE_OLD_TTY
#define	TIOCGETD	_IOR('t', 0, int)	/* get line discipline */
#define	TIOCSETD	_IOW('t', 1, int)	/* set line discipline */
#else
E 77
D 30
#define	TIOCGETD	(('t'<<8)|0)	/* get line discipline */
#define	TIOCSETD	(('t'<<8)|1)	/* set line discipline */
#define	TIOCHPCL	(('t'<<8)|2)	/* set hangup line on close bit */
#define	TIOCMODG	(('t'<<8)|3)	/* modem bits get (???) */
#define	TIOCMODS	(('t'<<8)|4)	/* modem bits set (???) */
#define	TIOCGETP	(('t'<<8)|8)	/* get parameters - like old gtty */
#define	TIOCSETP	(('t'<<8)|9)	/* set parameters - like old stty */
#define	TIOCSETN	(('t'<<8)|10)	/* set params w/o flushing buffers */
D 18
#define	TIOCEXCL	(('t'<<8)|13)	/* set exclusive use of tty */
#define	TIOCNXCL	(('t'<<8)|14)	/* reset exclusive use of tty */
E 18
I 18
D 24
/* 13 was EXCL */
/* 14 was NEXCL */
E 24
I 24
#define	TIOCEXCL	(('t'<<8)|13)	/* set exclusive use of tty */
#define	TIOCNXCL	(('t'<<8)|14)	/* reset exclusive use of tty */
E 24
E 18
#define	TIOCFLUSH	(('t'<<8)|16)	/* flush buffers */
#define	TIOCSETC	(('t'<<8)|17)	/* set special characters */
#define	TIOCGETC	(('t'<<8)|18)	/* get special characters */
I 11
#define	TIOCIOANS	(('t'<<8)|20)
#define	TIOCSIGNAL	(('t'<<8)|21)
#define	TIOCUTTY	(('t'<<8)|22)
E 30
I 30
D 73
#define	TIOCGETD	_IOR(t, 0, int)		/* get line discipline */
#define	TIOCSETD	_IOW(t, 1, int)		/* set line discipline */
#define	TIOCHPCL	_IO(t, 2)		/* hang up on last close */
#define	TIOCMODG	_IOR(t, 3, int)		/* get modem control state */
#define	TIOCMODS	_IOW(t, 4, int)		/* set modem control state */
E 73
I 73
D 75
#define	TIOCGETD	_IOR('t', 0, int)		/* get line discipline */
#define	TIOCSETD	_IOW('t', 1, int)		/* set line discipline */
E 75
I 75
D 76
#define	TIOCGETD	_IOR('t', 0, int)	/* get line discipline */
#define	TIOCSETD	_IOW('t', 1, int)	/* set line discipline */
E 76
I 76
#define	TIOCGETDCOMPAT	_IOR('t', 0, int)	/* get line discipline */
#define	TIOCSETDCOMPAT	_IOW('t', 1, int)	/* set line discipline */
I 77
#endif
E 77
E 76
E 75
#define	TIOCHPCL	_IO('t', 2)		/* hang up on last close */
E 78
I 78
						/* 0-2 compat */
E 82
E 78
D 75
#define	TIOCMODG	_IOR('t', 3, int)		/* get modem control state */
#define	TIOCMODS	_IOW('t', 4, int)		/* set modem control state */
E 75
I 75
#define	TIOCMODG	_IOR('t', 3, int)	/* get modem control state */
#define	TIOCMODS	_IOW('t', 4, int)	/* set modem control state */
E 75
E 73
I 33
#define		TIOCM_LE	0001		/* line enable */
#define		TIOCM_DTR	0002		/* data terminal ready */
#define		TIOCM_RTS	0004		/* request to send */
#define		TIOCM_ST	0010		/* secondary transmit */
#define		TIOCM_SR	0020		/* secondary receive */
#define		TIOCM_CTS	0040		/* clear to send */
#define		TIOCM_CAR	0100		/* carrier detect */
#define		TIOCM_CD	TIOCM_CAR
#define		TIOCM_RNG	0200		/* ring */
#define		TIOCM_RI	TIOCM_RNG
#define		TIOCM_DSR	0400		/* data set ready */
E 33
D 73
#define	TIOCGETP	_IOR(t, 8,struct sgttyb)/* get parameters -- gtty */
#define	TIOCSETP	_IOW(t, 9,struct sgttyb)/* set parameters -- stty */
#define	TIOCSETN	_IOW(t,10,struct sgttyb)/* as above, but no flushtty */
#define	TIOCEXCL	_IO(t, 13)		/* set exclusive use of tty */
#define	TIOCNXCL	_IO(t, 14)		/* reset exclusive use of tty */
#define	TIOCFLUSH	_IOW(t, 16, int)	/* flush buffers */
#define	TIOCSETC	_IOW(t,17,struct tchars)/* set special characters */
#define	TIOCGETC	_IOR(t,18,struct tchars)/* get special characters */
E 73
I 73
D 78
#define	TIOCGETP	_IOR('t', 8,struct sgttyb)/* get parameters -- gtty */
#define	TIOCSETP	_IOW('t', 9,struct sgttyb)/* set parameters -- stty */
D 75
#define	TIOCSETN	_IOW('t',10,struct sgttyb)/* as above, but no flushtty */
E 75
I 75
#define	TIOCSETN	_IOW('t',10,struct sgttyb)/* as above, but no flushtty*/
E 78
I 78
						/* 8-10 compat */
E 78
E 75
#define	TIOCEXCL	_IO('t', 13)		/* set exclusive use of tty */
#define	TIOCNXCL	_IO('t', 14)		/* reset exclusive use of tty */
I 78
						/* 15 unused */
E 78
#define	TIOCFLUSH	_IOW('t', 16, int)	/* flush buffers */
D 78
#define	TIOCSETC	_IOW('t',17,struct tchars)/* set special characters */
#define	TIOCGETC	_IOR('t',18,struct tchars)/* get special characters */
E 73
E 30
E 11
D 34
/* locals, from 127 down */
D 3
#define TIOCLBIS	(('t'<<8)|127)	/* bis local mode bits */
#define TIOCLBIC	(('t'<<8)|126)	/* bic local mode bits */
#define TIOCLSET	(('t'<<8)|125)	/* set entire local mode word */
#define TIOCLGET	(('t'<<8)|124)	/* get local modes */
E 3
I 3
D 30
#define	TIOCLBIS	(('t'<<8)|127)	/* bis local mode bits */
#define	TIOCLBIC	(('t'<<8)|126)	/* bic local mode bits */
#define	TIOCLSET	(('t'<<8)|125)	/* set entire local mode word */
#define	TIOCLGET	(('t'<<8)|124)	/* get local modes */
E 3
#define	TIOCSBRK	(('t'<<8)|123)	/* set break bit */
D 3
#define TIOCCBRK	(('t'<<8)|122)	/* clear break bit */
#define TIOCSDTR	(('t'<<8)|121)	/* set data terminal ready */
#define TIOCCDTR	(('t'<<8)|120)	/* clear data terminal ready */
#define TIOCGPGRP	(('t'<<8)|119)	/* get pgrp of tty */
#define TIOCSPGRP	(('t'<<8)|118)	/* set pgrp of tty */
E 3
I 3
#define	TIOCCBRK	(('t'<<8)|122)	/* clear break bit */
#define	TIOCSDTR	(('t'<<8)|121)	/* set data terminal ready */
#define	TIOCCDTR	(('t'<<8)|120)	/* clear data terminal ready */
#define	TIOCGPGRP	(('t'<<8)|119)	/* get pgrp of tty */
#define	TIOCSPGRP	(('t'<<8)|118)	/* set pgrp of tty */
E 3
#define	TIOCSLTC	(('t'<<8)|117)	/* set local special characters */
#define	TIOCGLTC	(('t'<<8)|116)	/* get local special characters */
I 5
#define	TIOCOUTQ	(('t'<<8)|115)	/* number of chars in output queue */
I 8
#define	TIOCSTI		(('t'<<8)|114)	/* simulate a terminal in character */
I 20
#define	TIOCNOTTY	(('t'<<8)|113)	/* get rid of tty association */
I 22
#define	TIOCPKT		(('t'<<8)|112)	/* on pty: set/clear packet mode */
E 30
I 30
#define	TIOCLBIS	_IOW(t, 127, int)	/* bis local mode bits */
#define	TIOCLBIC	_IOW(t, 126, int)	/* bic local mode bits */
#define	TIOCLSET	_IOW(t, 125, int)	/* set entire local mode word */
#define	TIOCLGET	_IOR(t, 124, int)	/* get local modes */
#define	TIOCSBRK	_IO(t, 123)		/* set break bit */
#define	TIOCCBRK	_IO(t, 122)		/* clear break bit */
#define	TIOCSDTR	_IO(t, 121)		/* set data terminal ready */
#define	TIOCCDTR	_IO(t, 120)		/* clear data terminal ready */
#define	TIOCGPGRP	_IOR(t, 119, int)	/* get pgrp of tty */
#define	TIOCSPGRP	_IOW(t, 118, int)	/* set pgrp of tty */
#define	TIOCSLTC	_IOW(t,117,struct ltchars)/* set local special chars */
#define	TIOCGLTC	_IOR(t,116,struct ltchars)/* get local special chars */
I 32
#define	TIOCSTI		_IOW(t, 114, char)	/* simulate terminal input */
E 32
#define	TIOCNOTTY	_IO(t, 113)		/* void tty association */
#define	TIOCPKT		_IOW(t, 112, int)	/* pty: set/clear packet mode */
E 30
D 28
#define		TIOCPKT_DATA		0	/* data packet */
#define		TIOCPKT_FLUSHREAD	1	/* flush packet */
#define		TIOCPKT_FLUSHWRITE	2	/* flush packet */
#define		TIOCPKT_STOP		4	/* stop output */
#define		TIOCPKT_START		8	/* start output */
E 28
I 28
#define		TIOCPKT_DATA		0x00	/* data packet */
#define		TIOCPKT_FLUSHREAD	0x01	/* flush packet */
#define		TIOCPKT_FLUSHWRITE	0x02	/* flush packet */
#define		TIOCPKT_STOP		0x04	/* stop output */
#define		TIOCPKT_START		0x08	/* start output */
#define		TIOCPKT_NOSTOP		0x10	/* no more ^S, ^Q */
#define		TIOCPKT_DOSTOP		0x20	/* now do ^S ^Q */
E 28
I 23
D 30
#define	TIOCSTOP	(('t'<<8)|111)	/* stop output, like ^S */
#define	TIOCSTART	(('t'<<8)|110)	/* start output, like ^Q */
I 25
#define	TIOCMSET	(('t'<<8)|109)	/* set all modem bits */
#define	TIOCMBIS	(('t'<<8)|108)	/* bis modem bits */
#define	TIOCMBIC	(('t'<<8)|107)	/* bic modem bits */
#define	TIOCMGET	(('t'<<8)|106)	/* get all modem bits */
I 26
#define	TIOCREMOTE	(('t'<<8)|105)	/* remote input editing */
E 30
I 30
#define	TIOCSTOP	_IO(t, 111)		/* stop output, like ^S */
#define	TIOCSTART	_IO(t, 110)		/* start output, like ^Q */
#define	TIOCMSET	_IOW(t, 109, int)	/* set all modem bits */
#define	TIOCMBIS	_IOW(t, 108, int)	/* bis modem bits */
#define	TIOCMBIC	_IOW(t, 107, int)	/* bic modem bits */
#define	TIOCMGET	_IOR(t, 106, int)	/* get all modem bits */
#define	TIOCREMOTE	_IO(t, 105)		/* remote input editing */
I 33
#define	TIOCSET		_IOW(t, 104, long)	/* set tty flags */
#define	TIOCBIS		_IOW(t, 103, long)	/* bis tty flags */
#define	TIOCBIC		_IOW(t, 102, long)	/* bic tty flags */
#define	TIOCGET		_IOR(t, 101, long)	/* get all tty flags */
E 34
I 34
D 43
#define	TIOCSET		_IOW(t, 19, long)	/* set tty flags */
#define	TIOCBIS		_IOW(t, 20, long)	/* bis tty flags */
#define	TIOCBIC		_IOW(t, 21, long)	/* bic tty flags */
#define	TIOCGET		_IOR(t, 22, long)	/* get all tty flags */
E 43
E 34
#define		TANDEM		0x00000001	/* send stopc on out q full */
#define		CBREAK		0x00000002	/* half-cooked mode */
#define		LCASE		0x00000004	/* simulate lower case */
#define		ECHO		0x00000008	/* echo input */
#define		CRMOD		0x00000010	/* map \r to \r\n on output */
#define		RAW		0x00000020	/* no i/o processing */
#define		ODDP		0x00000040	/* get/send odd parity */
#define		EVENP		0x00000080	/* get/send even parity */
#define		ANYP		0x000000c0	/* get any parity/send none */
#define		NLDELAY		0x00000300	/* \n delay */
#define			NL0	0x00000000
#define			NL1	0x00000100	/* tty 37 */
#define			NL2	0x00000200	/* vt05 */
#define			NL3	0x00000300
#define		TBDELAY		0x00000c00	/* horizontal tab delay */
#define			TAB0	0x00000000
#define			TAB1	0x00000400	/* tty 37 */
#define			TAB2	0x00000800
#define		XTABS		0x00000c00	/* expand tabs on output */
#define		CRDELAY		0x00003000	/* \r delay */
#define			CR0	0x00000000
#define			CR1	0x00001000	/* tn 300 */
#define			CR2	0x00002000	/* tty 37 */
#define			CR3	0x00003000	/* concept 100 */
#define		VTDELAY		0x00004000	/* vertical tab delay */
#define			FF0	0x00000000
#define			FF1	0x00004000	/* tty 37 */
#define		BSDELAY		0x00008000	/* \b delay */
#define			BS0	0x00000000
#define			BS1	0x00008000
D 34
/* used to be local mode settings */
E 34
I 34
D 64
#define 	ALLDELAY	(NLDELAY|TBDELAY|CRDELAY|VTDELAY|BSDELAY)
E 64
I 64
#define		ALLDELAY	(NLDELAY|TBDELAY|CRDELAY|VTDELAY|BSDELAY)
E 64
E 34
#define		CRTBS		0x00010000	/* do backspacing for crt */
#define		PRTERA		0x00020000	/* \ ... / erase */
#define		CRTERA		0x00040000	/* " \b " to wipe out char */
#define		TILDE		0x00080000	/* hazeltine tilde kludge */
D 75
#define		MDMBUF		0x00100000	/* start/stop output on carrier intr */
E 75
I 75
#define		MDMBUF		0x00100000	/*start/stop output on carrier*/
E 75
#define		LITOUT		0x00200000	/* literal output */
D 75
#define		TOSTOP		0x00400000	/* SIGSTOP on background output */
E 75
I 75
#define		TOSTOP		0x00400000	/*SIGSTOP on background output*/
E 75
#define		FLUSHO		0x00800000	/* flush output to terminal */
#define		NOHANG		0x01000000	/* no SIGHUP on carrier drop */
#define		L001000		0x02000000
#define		CRTKIL		0x04000000	/* kill line with " \b " */
D 56
#define		L004000		0x08000000
E 56
I 56
#define		PASS8		0x08000000
E 56
#define		CTLECH		0x10000000	/* echo control chars as ^X */
#define		PENDIN		0x20000000	/* tp->t_rawq needs reread */
#define		DECCTQ		0x40000000	/* only ^Q starts after ^S */
#define		NOFLSH		0x80000000	/* no output flush on signal */
E 78
I 78
						/* 17-18 compat */
E 78
I 75
D 76
/* POSIX line discipline */
E 76
#define	TIOCGETA	_IOR('t', 19, struct termios) /* get termios struct */
#define	TIOCSETA	_IOW('t', 20, struct termios) /* set termios struct */
#define	TIOCSETAW	_IOW('t', 21, struct termios) /* drain output, set */
#define	TIOCSETAF	_IOW('t', 22, struct termios) /* drn out, fls in, set */
D 78
#define	TIOCSETAS	_IOW('t', 23, struct termios) /* SETA ign hdw state */
#define	TIOCSETAWS	_IOW('t', 24, struct termios) /* SETAW ign hdw state */
#define	TIOCSETAFS	_IOW('t', 25, struct termios) /* SETAF ign hdw state */
E 78
I 78
D 85
/*** THESE GO AWAY ***/
#define	JUNK_TIOCSETAS	_IOW('t', 23, struct termios) /* SETA ign hdw state */
#define	JUNK_TIOCSETAWS	_IOW('t', 24, struct termios) /* SETAW ign hdw state */
#define	JUNK_TIOCSETAFS	_IOW('t', 25, struct termios) /* SETAF ign hdw state */
/******************/
E 85
E 78
D 79
#define TCGETA	TIOCGETA
#define TCSETA	TIOCSETA
#define TCSETAW	TIOCSETAW
#define TCSETAF	TIOCSETAF
E 79
I 77
D 78
#ifndef USE_OLD_TTY
E 78
E 77
I 76
#define	TIOCGETD	_IOR('t', 26, int)	/* get line discipline */
#define	TIOCSETD	_IOW('t', 27, int)	/* set line discipline */
I 77
D 78
#endif
E 77
E 76
E 75
D 34
#define 	ALLDELAY	(NLDELAY|TBDELAY|CRDELAY|VTDELAY|BSDELAY)
E 34
I 34
D 43
#define	TIOCCSET	_IOW(t,23,struct ttychars)/* set special characters */
#define	TIOCCGET	_IOR(t,24,struct ttychars)/* get special characters */
E 43
/* locals, from 127 down */
D 43
#ifndef NOCOMPAT
E 43
D 73
#define	TIOCLBIS	_IOW(t, 127, int)	/* bis local mode bits */
#define	TIOCLBIC	_IOW(t, 126, int)	/* bic local mode bits */
#define	TIOCLSET	_IOW(t, 125, int)	/* set entire local mode word */
#define	TIOCLGET	_IOR(t, 124, int)	/* get local modes */
E 73
I 73
#define	TIOCLBIS	_IOW('t', 127, int)	/* bis local mode bits */
#define	TIOCLBIC	_IOW('t', 126, int)	/* bic local mode bits */
#define	TIOCLSET	_IOW('t', 125, int)	/* set entire local mode word */
#define	TIOCLGET	_IOR('t', 124, int)	/* get local modes */
E 73
#define		LCRTBS		(CRTBS>>16)
#define		LPRTERA		(PRTERA>>16)
#define		LCRTERA		(CRTERA>>16)
#define		LTILDE		(TILDE>>16)
#define		LMDMBUF		(MDMBUF>>16)
#define		LLITOUT		(LITOUT>>16)
#define		LTOSTOP		(TOSTOP>>16)
#define		LFLUSHO		(FLUSHO>>16)
#define		LNOHANG		(NOHANG>>16)
#define		LCRTKIL		(CRTKIL>>16)
I 56
#define		LPASS8		(PASS8>>16)
E 56
#define		LCTLECH		(CTLECH>>16)
#define		LPENDIN		(PENDIN>>16)
#define		LDECCTQ		(DECCTQ>>16)
#define		LNOFLSH		(NOFLSH>>16)
E 78
I 78
						/* 127-124 compat */
E 78
D 43
#endif
E 43
D 73
#define	TIOCSBRK	_IO(t, 123)		/* set break bit */
#define	TIOCCBRK	_IO(t, 122)		/* clear break bit */
#define	TIOCSDTR	_IO(t, 121)		/* set data terminal ready */
#define	TIOCCDTR	_IO(t, 120)		/* clear data terminal ready */
#define	TIOCGPGRP	_IOR(t, 119, int)	/* get pgrp of tty */
#define	TIOCSPGRP	_IOW(t, 118, int)	/* set pgrp of tty */
#define	TIOCSLTC	_IOW(t,117,struct ltchars)/* set local special chars */
#define	TIOCGLTC	_IOR(t,116,struct ltchars)/* get local special chars */
I 43
#define	TIOCOUTQ	_IOR(t, 115, int)	/* output queue size */
E 43
#define	TIOCSTI		_IOW(t, 114, char)	/* simulate terminal input */
#define	TIOCNOTTY	_IO(t, 113)		/* void tty association */
#define	TIOCPKT		_IOW(t, 112, int)	/* pty: set/clear packet mode */
E 73
I 73
#define	TIOCSBRK	_IO('t', 123)		/* set break bit */
#define	TIOCCBRK	_IO('t', 122)		/* clear break bit */
#define	TIOCSDTR	_IO('t', 121)		/* set data terminal ready */
#define	TIOCCDTR	_IO('t', 120)		/* clear data terminal ready */
#define	TIOCGPGRP	_IOR('t', 119, int)	/* get pgrp of tty */
#define	TIOCSPGRP	_IOW('t', 118, int)	/* set pgrp of tty */
D 75
#define	TIOCSLTC	_IOW('t',117,struct ltchars)/* set local special chars */
#define	TIOCGLTC	_IOR('t',116,struct ltchars)/* get local special chars */
E 75
I 75
D 78
#define	TIOCSLTC	_IOW('t',117,struct ltchars)/* set local special chars*/
#define	TIOCGLTC	_IOR('t',116,struct ltchars)/* get local special chars*/
E 78
I 78
						/* 117-116 compat */
E 78
E 75
#define	TIOCOUTQ	_IOR('t', 115, int)	/* output queue size */
#define	TIOCSTI		_IOW('t', 114, char)	/* simulate terminal input */
#define	TIOCNOTTY	_IO('t', 113)		/* void tty association */
#define	TIOCPKT		_IOW('t', 112, int)	/* pty: set/clear packet mode */
E 73
#define		TIOCPKT_DATA		0x00	/* data packet */
#define		TIOCPKT_FLUSHREAD	0x01	/* flush packet */
#define		TIOCPKT_FLUSHWRITE	0x02	/* flush packet */
#define		TIOCPKT_STOP		0x04	/* stop output */
#define		TIOCPKT_START		0x08	/* start output */
#define		TIOCPKT_NOSTOP		0x10	/* no more ^S, ^Q */
#define		TIOCPKT_DOSTOP		0x20	/* now do ^S ^Q */
I 80
#define		TIOCPKT_IOCTL		0x40	/* state change of pty driver */
E 80
I 74
#define		TIOCPKT_TIOC		0x40	/* transparent ioctl packet */
E 74
D 73
#define	TIOCSTOP	_IO(t, 111)		/* stop output, like ^S */
#define	TIOCSTART	_IO(t, 110)		/* start output, like ^Q */
#define	TIOCMSET	_IOW(t, 109, int)	/* set all modem bits */
#define	TIOCMBIS	_IOW(t, 108, int)	/* bis modem bits */
#define	TIOCMBIC	_IOW(t, 107, int)	/* bic modem bits */
#define	TIOCMGET	_IOR(t, 106, int)	/* get all modem bits */
D 53
#define	TIOCREMOTE	_IO(t, 105)		/* remote input editing */
E 53
I 53
#define	TIOCREMOTE	_IOW(t, 105, int)	/* remote input editing */
E 53
I 50
D 64
#define TIOCGWINSZ	_IOR(t, 104, struct winsize)	/* get window size */
#define TIOCSWINSZ	_IOW(t, 103, struct winsize)	/* set window size */
I 52
#define TIOCUCNTL	_IOW(t, 102, int)	/* pty: set/clr usr cntl mode */
E 64
I 64
#define	TIOCGWINSZ	_IOR(t, 104, struct winsize)	/* get window size */
#define	TIOCSWINSZ	_IOW(t, 103, struct winsize)	/* set window size */
#define	TIOCUCNTL	_IOW(t, 102, int)	/* pty: set/clr usr cntl mode */
I 66
#define		UIOCCMD(n)	_IO(u, n)		/* usr cntl op "n" */
I 68
D 72
#define	TIOCCONS	_IO(t, 102)		/* become virtual console */
E 72
I 72
#define	TIOCCONS	_IO(t, 98)		/* become virtual console */
E 73
I 73
#define	TIOCSTOP	_IO('t', 111)		/* stop output, like ^S */
#define	TIOCSTART	_IO('t', 110)		/* start output, like ^Q */
#define	TIOCMSET	_IOW('t', 109, int)	/* set all modem bits */
#define	TIOCMBIS	_IOW('t', 108, int)	/* bis modem bits */
#define	TIOCMBIC	_IOW('t', 107, int)	/* bic modem bits */
#define	TIOCMGET	_IOR('t', 106, int)	/* get all modem bits */
#define	TIOCREMOTE	_IOW('t', 105, int)	/* remote input editing */
#define	TIOCGWINSZ	_IOR('t', 104, struct winsize)	/* get window size */
#define	TIOCSWINSZ	_IOW('t', 103, struct winsize)	/* set window size */
D 74
#define	TIOCUCNTL	_IOW('t', 102, int)	/* pty: set/clr usr cntl mode */
E 74
#define		UIOCCMD(n)	_IO('u', n)		/* usr cntl op "n" */
I 74
#define	TIOCUCNTL	_IOW('t', 102, int)	/* pty: set/clr usr cntl mode */
#define	TIOCTIOC	_IOW('t', 101, int)	/* pty: set/clr transparent */
#define	TIOCBLK		_IOW('t', 100, int)	/* pty: block slave writes */
#define	TIOCIOANS(s)	_IOWX('t', 99, (s))	/* pty: reply to user ioctl */
E 74
D 78
#define	TIOCCONS	_IO('t', 98)		/* become virtual console */
E 78
I 78
#define	TIOCCONS	_IOW('t', 98, int)		/* become virtual console */
E 78
I 75
#define	TIOCSCTTY	_IO('t', 97)		/* become controlling tty */
I 80
#define	TIOCEXT		_IOW('t', 96, int)	/* pty: external processing */
#define	TIOCSIG		_IO('t', 95)		/* pty: generate signal */
I 86
D 89
#define TIOCDRAIN	_IO('t', 94)		/* wait till output drained */
E 89
I 89
#define	TIOCDRAIN	_IO('t', 94)		/* wait till output drained */
E 89
E 86
E 80
E 75
E 73
E 72
E 68
E 66
E 64
E 52
E 50
E 34
E 33
E 30
E 26
E 25
E 23
E 22
E 20
E 8
E 5

I 9
D 11
#define	OTTYDISC	0
E 11
I 11
D 75
#define	OTTYDISC	0		/* old, v7 std tty driver */
E 75
I 75
D 76
#define	OTTYDISC	0		/* termios ldisc */
E 76
I 76
D 77
#define	OTTYDISC	0		/* termios */
#define	NTTYDISC	0		/* COMPAT_43 */
E 77
I 77
D 89
#define TTYDISC		0		/* termios tty line discipline */
E 89
I 89
#define	TTYDISC		0		/* termios tty line discipline */
E 89
D 78
#ifdef USE_OLD_TTY
#define	OTTYDISC	0		/* COMPAT_43 (alias) */
E 77
E 76
E 75
E 11
E 9
#define	NETLDISC	1		/* line discip for berk net */
I 77
#define	NTTYDISC	2		/* COMPAT_43 (alias) */
#endif
E 78
E 77
D 11
#define	NTTYDISC	2
E 11
I 11
D 75
#define	NTTYDISC	2		/* new tty discipline */
E 75
I 75
D 76
#define	NTTYDISC	2		/* also termios ldisc */
E 76
E 75
I 29
D 59
#define	TABLDISC	3		/* hitachi tablet discipline */
#define	NTABLDISC	4		/* gtco tablet discipline */
E 59
I 59
#define	TABLDISC	3		/* tablet discipline */
I 62
D 63
#define	SLIPLDISC	4		/* serial IP discipline */
E 63
I 63
#define	SLIPDISC	4		/* serial IP discipline */
E 63
E 62
E 59
E 29
D 14
#define	PKDISC		3		/* packet driver */
#define	TRDISC		4		/* datakit trailer protocol */
#define	TDKDISC		5		/* datakit terminal protocol */
E 14
E 11
I 6
D 7
#define	OKILDISC	3
E 7
E 6

I 78
D 87
/*
 * Compatability with old terminal driver
 *
 * Source level -> #define USE_OLD_TTY
 * Kernel level -> options COMPAT_43
 */
#if defined(USE_OLD_TTY) || defined(COMPAT_43)
#ifdef KERNEL
#include "ioctl_compat.h"
#else
#include <sys/ioctl_compat.h>
#endif
#endif
E 87

E 78
D 14
#define	DIOCLSTN	(('d'<<8)|1)
D 11
#define	DIOCNTRL	(('d'<<8)|2)
E 11
I 11
#define	DIOCMD		(('d'<<8)|2)
E 11
#define	DIOCMPX		(('d'<<8)|3)
#define	DIOCNMPX	(('d'<<8)|4)
#define	DIOCSCALL	(('d'<<8)|5)
#define	DIOCRCALL	(('d'<<8)|6)
#define	DIOCPGRP	(('d'<<8)|7)
#define	DIOCGETP	(('d'<<8)|8)
#define	DIOCSETP	(('d'<<8)|9)
#define	DIOCLOSE	(('d'<<8)|10)
#define	DIOCTIME	(('d'<<8)|11)
#define	DIOCRESET	(('d'<<8)|12)
#define	DIOCSMETA	(('d'<<8)|13)
#define	DIOCMERGE	(('d'<<8)|14)
#define	DIOCICHAN	(('d'<<8)|15)
D 11
#define	DIOCPAD		(('d'<<8)|16)
E 11
I 11
#define	DIOCUMERGE	(('d'<<8)|16)
E 11
#define	DIOCRMETA	(('d'<<8)|17)
#define	DIOCXOUT	(('d'<<8)|18)
#define	DIOCBMETA	(('d'<<8)|19)
#define	DIOCAMETA	(('d'<<8)|20)
#define	DIOCSBMETA	(('d'<<8)|21)
I 11
#define	DIOCLOOP	(('d'<<8)|22)
#define	DIOCPROTOCOL	(('d'<<8)|23)
#define	DIOCTRL		(('d'<<8)|24)
#define	DIOCDMETA	(('d'<<8)|25)
#define	DIOCSWR		(('d'<<8)|26)
E 11

E 14
D 30
#define	FIOCLEX		(('f'<<8)|1)
#define	FIONCLEX	(('f'<<8)|2)
E 30
I 30
D 70
#define	FIOCLEX		_IO(f, 1)		/* set exclusive use on fd */
#define	FIONCLEX	_IO(f, 2)		/* remove exclusive use */
E 70
I 70
D 73
#define	FIOCLEX		_IO(f, 1)		/* set close on exec on fd */
#define	FIONCLEX	_IO(f, 2)		/* remove close on exec */
E 73
I 73
#define	FIOCLEX		_IO('f', 1)		/* set close on exec on fd */
#define	FIONCLEX	_IO('f', 2)		/* remove close on exec */
E 73
E 70
E 30
D 78
/* another local */
E 78
D 30
#define	FIONREAD	(('f'<<8)|127)	/* get # bytes to read */
I 20
#define	FIONBIO		(('f'<<8)|126)
#define	FIOASYNC	(('f'<<8)|125)
E 30
I 30
D 73
#define	FIONREAD	_IOR(f, 127, int)	/* get # bytes to read */
#define	FIONBIO		_IOW(f, 126, int)	/* set/clear non-blocking i/o */
#define	FIOASYNC	_IOW(f, 125, int)	/* set/clear async i/o */
I 41
#define	FIOSETOWN	_IOW(f, 124, int)	/* set owner */
#define	FIOGETOWN	_IOR(f, 123, int)	/* get owner */
E 73
I 73
#define	FIONREAD	_IOR('f', 127, int)	/* get # bytes to read */
#define	FIONBIO		_IOW('f', 126, int)	/* set/clear non-blocking i/o */
#define	FIOASYNC	_IOW('f', 125, int)	/* set/clear async i/o */
#define	FIOSETOWN	_IOW('f', 124, int)	/* set owner */
#define	FIOGETOWN	_IOR('f', 123, int)	/* get owner */
E 73
E 41
E 30
E 20
I 19

D 30
#define	SIOCDONE	(('s'<<8)|0)	/* shutdown read/write on socket */
I 20
#define	SIOCSKEEP	(('s'<<8)|1)	/* set keep alive */
#define	SIOCGKEEP	(('s'<<8)|2)	/* inspect keep alive */
#define	SIOCSLINGER	(('s'<<8)|3)	/* set linger time */
#define	SIOCGLINGER	(('s'<<8)|4)	/* get linger time */
I 21
#define	SIOCSENDOOB	(('s'<<8)|5)	/* send out of band */
#define	SIOCRCVOOB	(('s'<<8)|6)	/* get out of band */
#define	SIOCATMARK	(('s'<<8)|7)	/* at out of band mark? */
#define	SIOCSPGRP	(('s'<<8)|8)	/* set process group */
#define	SIOCGPGRP	(('s'<<8)|9)	/* get process group */
I 27
#define	SIOCADDRT	(('s'<<8)|10)	/* add a routing table entry */
#define	SIOCDELRT	(('s'<<8)|11)	/* delete a routing table entry */
#define	SIOCCHGRT	(('s'<<8)|12)	/* change a routing table entry */
E 30
I 30
/* socket i/o controls */
I 37
D 39
#define	SIOCSHIWAT	_IOW(s, 0, int)		/* set high water mark */
#define	SIOCGHIWAT	_IOR(s, 1, int)		/* get high water mark */
#define	SIOCSLOWAT	_IOW(s, 2, int)		/* set low water mark */
#define	SIOCGLOWAT	_IOR(s, 3, int)		/* get low water mark */
E 37
D 36
#define	SIOCDONE	_IOW(s, 0, int)		/* shutdown read/write */
#define	SIOCSKEEP	_IOW(s, 1, int)		/* set keep alive */
#define	SIOCGKEEP	_IOR(s, 2, int)		/* inspect keep alive */
#define	SIOCSLINGER	_IOW(s, 3, int)		/* set linger time */
#define	SIOCGLINGER	_IOR(s, 4, int)		/* get linger time */
D 33
/* these are really variable length */
#define	SIOCSENDOOB	_IOW(s, 5, char)	/* send out of band */
#define	SIOCRCVOOB	_IOR(s, 6, char)	/* get out of band */
E 33
I 33
#define	SIOCSENDOOB	_IOW(s, 5, char)	/* send oob data */
#define	SIOCRCVOOB	_IOR(s, 6, char)	/* recv oob data */
E 36
E 33
#define	SIOCATMARK	_IOR(s, 7, int)		/* at out of band mark? */
#define	SIOCSPGRP	_IOW(s, 8, int)		/* set process group */
#define	SIOCGPGRP	_IOR(s, 9, int)		/* get process group */
#define	SIOCADDRT	_IOW(s,10, struct rtentry)/* add route */
#define	SIOCDELRT	_IOW(s,11, struct rtentry)/* delete route */
I 36
#define	SIOCSIFADDR	_IOW(s,12, struct ifreq)/* set interface address */
#define	SIOCGIFADDR	_IOR(s,13, struct ifreq)/* get interface address */
#define	SIOCSIFDSTADDR	_IOW(s,14, struct ifreq)/* set point-point address */
#define	SIOCGIFDSTADDR	_IOR(s,15, struct ifreq)/* get point-point address */
#define	SIOCSIFFLAGS	_IOW(s,16, struct ifreq)/* set interface flags */
#define	SIOCGIFFLAGS	_IOR(s,17, struct ifreq)/* get interface flags */
D 38
#define	SIOCGIFCONF	_IOR(s,20, struct ifconf)/* get interface list */
E 38
I 38
#define	SIOCGIFCONF	_IOWR(s,20,struct ifconf)/* get interface list */
E 39
I 39
D 73
#define	SIOCSHIWAT	_IOW(s,  0, int)		/* set high watermark */
#define	SIOCGHIWAT	_IOR(s,  1, int)		/* get high watermark */
#define	SIOCSLOWAT	_IOW(s,  2, int)		/* set low watermark */
#define	SIOCGLOWAT	_IOR(s,  3, int)		/* get low watermark */
#define	SIOCATMARK	_IOR(s,  7, int)		/* at oob mark? */
#define	SIOCSPGRP	_IOW(s,  8, int)		/* set process group */
#define	SIOCGPGRP	_IOR(s,  9, int)		/* get process group */
E 73
I 73
#define	SIOCSHIWAT	_IOW('s',  0, int)		/* set high watermark */
#define	SIOCGHIWAT	_IOR('s',  1, int)		/* get high watermark */
#define	SIOCSLOWAT	_IOW('s',  2, int)		/* set low watermark */
#define	SIOCGLOWAT	_IOR('s',  3, int)		/* get low watermark */
#define	SIOCATMARK	_IOR('s',  7, int)		/* at oob mark? */
#define	SIOCSPGRP	_IOW('s',  8, int)		/* set process group */
#define	SIOCGPGRP	_IOR('s',  9, int)		/* get process group */
E 73
D 42
#define	SIOCADDRT	_IOW(s, 10, struct rtentry)	/* add route */
#define	SIOCDELRT	_IOW(s, 11, struct rtentry)	/* delete route */
#define	SIOCSIFADDR	_IOW(s, 12, struct ifreq)	/* set ifnet address */
#define	SIOCGIFADDR	_IOWR(s,13, struct ifreq)	/* get ifnet address */
#define	SIOCSIFDSTADDR	_IOW(s, 14, struct ifreq)	/* set p-p address */
#define	SIOCGIFDSTADDR	_IOWR(s,15, struct ifreq)	/* get p-p address */
#define	SIOCSIFFLAGS	_IOW(s, 16, struct ifreq)	/* set ifnet flags */
#define	SIOCGIFFLAGS	_IOWR(s,17, struct ifreq)	/* get ifnet flags */
#define	SIOCGIFCONF	_IOWR(s,20, struct ifconf)	/* get ifnet list */
E 42
I 42

D 73
#define	SIOCADDRT	_IOW(r, 10, struct rtentry)	/* add route */
#define	SIOCDELRT	_IOW(r, 11, struct rtentry)	/* delete route */
E 73
I 73
D 76
#define	SIOCADDRT	_IOW('r', 10, struct rtentry)	/* add route */
#define	SIOCDELRT	_IOW('r', 11, struct rtentry)	/* delete route */
E 76
I 76
#define	SIOCADDRT	_IOW('r', 10, struct ortentry)	/* add route */
#define	SIOCDELRT	_IOW('r', 11, struct ortentry)	/* delete route */
E 76
E 73

D 73
#define	SIOCSIFADDR	_IOW(i, 12, struct ifreq)	/* set ifnet address */
#define	SIOCGIFADDR	_IOWR(i,13, struct ifreq)	/* get ifnet address */
#define	SIOCSIFDSTADDR	_IOW(i, 14, struct ifreq)	/* set p-p address */
#define	SIOCGIFDSTADDR	_IOWR(i,15, struct ifreq)	/* get p-p address */
#define	SIOCSIFFLAGS	_IOW(i, 16, struct ifreq)	/* set ifnet flags */
#define	SIOCGIFFLAGS	_IOWR(i,17, struct ifreq)	/* get ifnet flags */
I 46
#define	SIOCGIFBRDADDR	_IOWR(i,18, struct ifreq)	/* get broadcast addr */
I 52
#define	SIOCSIFBRDADDR	_IOW(i,19, struct ifreq)	/* set broadcast addr */
E 52
E 46
#define	SIOCGIFCONF	_IOWR(i,20, struct ifconf)	/* get ifnet list */
I 52
#define	SIOCGIFNETMASK	_IOWR(i,21, struct ifreq)	/* get net addr mask */
#define	SIOCSIFNETMASK	_IOW(i,22, struct ifreq)	/* set net addr mask */
I 61
#define	SIOCGIFMETRIC	_IOWR(i,23, struct ifreq)	/* get IF metric */
#define	SIOCSIFMETRIC	_IOW(i,24, struct ifreq)	/* set IF metric */
E 73
I 73
#define	SIOCSIFADDR	_IOW('i', 12, struct ifreq)	/* set ifnet address */
D 76
#define	SIOCGIFADDR	_IOWR('i',13, struct ifreq)	/* get ifnet address */
E 76
I 76
#define	OSIOCGIFADDR	_IOWR('i',13, struct ifreq)	/* get ifnet address */
#define	SIOCGIFADDR	_IOWR('i',33, struct ifreq)	/* get ifnet address */
E 76
#define	SIOCSIFDSTADDR	_IOW('i', 14, struct ifreq)	/* set p-p address */
D 76
#define	SIOCGIFDSTADDR	_IOWR('i',15, struct ifreq)	/* get p-p address */
E 76
I 76
#define	OSIOCGIFDSTADDR	_IOWR('i',15, struct ifreq)	/* get p-p address */
#define	SIOCGIFDSTADDR	_IOWR('i',34, struct ifreq)	/* get p-p address */
E 76
#define	SIOCSIFFLAGS	_IOW('i', 16, struct ifreq)	/* set ifnet flags */
#define	SIOCGIFFLAGS	_IOWR('i',17, struct ifreq)	/* get ifnet flags */
D 76
#define	SIOCGIFBRDADDR	_IOWR('i',18, struct ifreq)	/* get broadcast addr */
E 76
I 76
#define	OSIOCGIFBRDADDR	_IOWR('i',18, struct ifreq)	/* get broadcast addr */
#define	SIOCGIFBRDADDR	_IOWR('i',35, struct ifreq)	/* get broadcast addr */
E 76
#define	SIOCSIFBRDADDR	_IOW('i',19, struct ifreq)	/* set broadcast addr */
D 76
#define	SIOCGIFCONF	_IOWR('i',20, struct ifconf)	/* get ifnet list */
#define	SIOCGIFNETMASK	_IOWR('i',21, struct ifreq)	/* get net addr mask */
E 76
I 76
#define	OSIOCGIFCONF	_IOWR('i',20, struct ifconf)	/* get ifnet list */
#define	SIOCGIFCONF	_IOWR('i',36, struct ifconf)	/* get ifnet list */
#define	OSIOCGIFNETMASK	_IOWR('i',21, struct ifreq)	/* get net addr mask */
#define	SIOCGIFNETMASK	_IOWR('i',37, struct ifreq)	/* get net addr mask */
E 76
#define	SIOCSIFNETMASK	_IOW('i',22, struct ifreq)	/* set net addr mask */
#define	SIOCGIFMETRIC	_IOWR('i',23, struct ifreq)	/* get IF metric */
#define	SIOCSIFMETRIC	_IOW('i',24, struct ifreq)	/* set IF metric */
I 76
D 77
#define	SIOCDIFADDR	_IOW('i',38, struct ifreq)	/* delete IF addr */
#define	SIOCAIFADDR	_IOW('i',39, struct ifaliasreq)	/* add/chg IF alias */
E 77
I 77
#define	SIOCDIFADDR	_IOW('i',25, struct ifreq)	/* delete IF addr */
#define	SIOCAIFADDR	_IOW('i',26, struct ifaliasreq)	/* add/chg IF alias */
E 77
E 76
E 73
E 61
E 52
I 45
D 91

D 73
#define	SIOCSARP	_IOW(i, 30, struct arpreq)	/* set arp entry */
D 46
#define	SIOCGARP	_IOWR(i, 31, struct arpreq)	/* get arp entry */
E 46
I 46
#define	SIOCGARP	_IOWR(i,31, struct arpreq)	/* get arp entry */
E 46
#define	SIOCDARP	_IOW(i, 32, struct arpreq)	/* delete arp entry */
E 73
I 73
#define	SIOCSARP	_IOW('i', 30, struct arpreq)	/* set arp entry */
D 76
#define	SIOCGARP	_IOWR('i',31, struct arpreq)	/* get arp entry */
E 76
I 76
#define	OSIOCGARP	_IOWR('i',31, struct arpreq)	/* get arp entry */
#define	SIOCGARP	_IOWR('i',38, struct arpreq)	/* get arp entry */
E 76
#define	SIOCDARP	_IOW('i', 32, struct arpreq)	/* delete arp entry */
E 91
I 89

#define	SIOCADDMULTI	_IOW('i', 49, struct ifreq)	/* add m'cast addr */
#define	SIOCDELMULTI	_IOW('i', 50, struct ifreq)	/* del m'cast addr */
E 89
E 73
I 57

E 98
I 84
#ifndef KERNEL

#include <sys/cdefs.h>

__BEGIN_DECLS
int	ioctl __P((int, unsigned long, ...));
__END_DECLS
D 93

E 93
#endif /* !KERNEL */
I 93
#endif /* !_SYS_IOCTL_H_ */
E 93

E 84
D 60
/* protocol i/o controls (bbn) */
#define SIOCSPUSH	_IO(b, 64)		/* tcp: set push */
#define SIOCCPUSH	_IO(b, 65)		/* tcp: clear push */
D 58
#define SIOCSNOACT	_IOW(b, 66, int)	/* tcp: set no activity timer */
#define SIOCGNOACT	_IOR(b, 67, int)	/* tcp: get no activity timer */
E 58
I 58
#define SIOCSNOACT	_IOW(b, 66, u_long)	/* tcp: set no activity timer */
#define SIOCGNOACT	_IOR(b, 67, u_long)	/* tcp: get no activity timer */
#define	    TCP_NOACTPROBE	0x80000000	/*	send pkt on timeout */
#define	    TCP_NOACTSIG	0x40000000	/*	advise user on timeout */
E 58
#define SIOCSINIT	_IOW(b, 68, int)	/* tcp: set init timer */
#define SIOCGINIT	_IOR(b, 69, int)	/* tcp: get init timer */
#define SIOCABORT	_IO(b, 70)		/* tcp: abort connection */

#define SIOCSNDGRAMS	_IOW(b, 71, int)	/* rdp: set max #dgrams rcv */
#define SIOCGNDGRAMS	_IOR(b, 72, int)	/* rdp: get max #dgrams rcv */
#define SIOCSSEQ	_IOW(b, 73, int)	/* rdp: set seq delivery */
#define SIOCGSEQ	_IOR(b, 74, int)	/* rdp: get seq delivery */
#define SIOCSNULL	_IOW(b, 77, int)	/* rdp: ~set KEEPALIVE timer */
#define SIOCGNULL	_IOR(b, 78, int)	/* rdp: ~get KEEPALIVE timer */

		/* tcp + rdp */
#define SIOCSRTTL	_IOW(b, 75, int)	/* set rxmit took too long */
#define SIOCGRTTL	_IOR(b, 76, int)	/* get rxmit took too long */
E 60
E 57
E 45
E 42
E 39
E 38
E 36
I 31
D 35

#define	KIOCTRANS	_IOW(k,0, int)	/* set keyboard translation */

#define	MIOCGPOS	_IOR(m,0, XXX)	/* get mouse info */
#define	MIOCGBUFS	_IOR(m,1, int)	/* get mouse buffer size */
#define	MIOCWBUFS	_IOW(m,1, int)	/* set mouse buffer size */
E 35
E 31
E 30
E 27
E 21
E 20
E 19
D 11
/* FIONREAD is not implemented on mpx channels yet */
E 11
D 15

I 11
/* mag tape io control commands */
#define MTIOCTOP	(('m'<<8)|1)	/* do a mag tape op (see <mtio.h>) */
#define MTIOCGET	(('m'<<8)|2)	/* get mag tape status (see <mtio.h>*/

/* mux io controls */
E 11
#define	MXLSTN		(('x'<<8)|1)
#define	MXNBLK		(('x'<<8)|2)

D 11
/*
 * These are defined in sys/vcmd.h
 *
E 11
I 11
#ifdef notdef
/* varian ioctls, which are defined in sys/vcmd.h */
E 11
#define	VGETSTATE	(('v'<<8)|0)
#define	VSETSTATE	(('v'<<8)|1)
D 11
 */
E 11
I 11
#endif

/* printer ioctls, see <lpio.h> */
#define	LGETSTATE	(('v'<<8)|2)
#define	LSETSTATE	(('v'<<8)|3)
E 15
I 12
D 14

/* chaos net io control commands */
#define CHIOCRNEXT	(('c'<<8)|1)	/* get chaos net unmatched rfc packet */
#define CHIOCRSKIP	(('c'<<8)|2)	/* Skip the unmatched RFC */
#define CHIOCRREAD	(('c'<<8)|3)	/* Read my RFC packet */
#define CHIOCTTY	(('c'<<8)|4)	/* make this channel a tty */
#define CHIOCFLUSH	(('c'<<8)|5)	/* flush current output packet */
E 14
E 12
E 11
D 81
#endif
E 81
I 81
D 93
#endif /* !_IOCTL_H_ */
I 87

/* - note: keep outside _IOCTL_H_
E 93
I 93
D 98
/* Keep outside _SYS_IOCTL_H_
E 98
I 98
/*
 * Keep outside _SYS_IOCTL_H_
E 98
E 93
 * Compatability with old terminal driver
 *
 * Source level -> #define USE_OLD_TTY
D 88
 * Kernel level -> options COMPAT_43
E 88
I 88
 * Kernel level -> options COMPAT_43 or COMPAT_SUNOS
E 88
 */
D 88
#if defined(USE_OLD_TTY) || defined(COMPAT_43)
E 88
I 88
#if defined(USE_OLD_TTY) || defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 88
D 96
#ifdef KERNEL
#include "ioctl_compat.h"
#else
E 96
#include <sys/ioctl_compat.h>
D 96
#endif
E 96
#endif
E 87
E 81
E 1
