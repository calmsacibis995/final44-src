h37787
s 00005/00000/00575
d D 8.4 95/05/04 15:41:34 mckusick 91 90
c If the buffer is full, keep the most recent data. (from ralph)
e
s 00005/00000/00570
d D 8.3 94/01/21 17:17:52 bostic 90 89
c add USL's copyright notice
e
s 00002/00002/00568
d D 8.2 93/09/23 15:35:39 bostic 89 88
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00568
d D 8.1 93/06/10 21:58:25 bostic 88 87
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00569
d D 7.39 92/10/11 10:38:21 bostic 87 86
c make kernel includes standard
e
s 00002/00001/00568
d D 7.38 92/03/11 21:22:26 torek 86 85
c gcc lint
e
s 00002/00002/00567
d D 7.37 92/03/08 17:44:19 karels 85 84
c fix printf %b
e
s 00003/00014/00566
d D 7.36 92/03/01 20:51:17 ralph 84 83
c remove unused KADB stuff, fix va_alist for ULTRIX compiler
e
s 00002/00001/00578
d D 7.35 92/02/05 22:36:18 mckusick 83 82
c lint
e
s 00010/00017/00569
d D 7.34 92/02/05 19:32:08 marc 82 81
c panic can use %r, does not return; fix comments describing %r;
c eliminate gcc warning
e
s 00000/00000/00586
d D 7.33 91/11/20 16:16:30 marc 81 79
i 80
c merge in 7.30.1.1 branch
e
s 00007/00007/00559
d D 7.30.1.1 91/11/20 16:13:23 marc 80 77
c changes for mips compiler (from Ralph)
e
s 00053/00033/00533
d D 7.32 91/11/01 16:41:26 bostic 79 78
c make panic take printf(3) style args; cleanup %r description
e
s 00002/00002/00564
d D 7.31 91/09/25 13:57:36 sklower 78 77
c ISO debugging uses logpri
e
s 00009/00010/00557
d D 7.30 91/06/29 10:36:11 bostic 77 76
c minor cleanups, don't #deffine consintr on tahoe
e
s 00035/00025/00532
d D 7.29 91/05/30 19:53:24 bostic 76 75
c cleanups from Chris Torek; bug fix on va_start for multiple calls
e
s 00015/00012/00542
d D 7.28 91/05/28 19:08:08 karels 75 74
c KNF patrol; avoid needless sign extension; try for register variable
e
s 00002/00002/00552
d D 7.27 91/05/28 17:12:13 bostic 74 73
c kprintf can't be static, used by 386 locore debugging code
e
s 00150/00061/00404
d D 7.26 91/05/28 15:55:01 bostic 73 72
c add sprintf(3); support space/zero padding, field width for numeric
c formats (for tty driver ttyinfo())
e
s 00000/00001/00465
d D 7.25 91/05/08 22:50:41 bostic 72 71
c leftover va_end didn't get deleted
e
s 00003/00003/00463
d D 7.24 91/05/05 14:17:11 william 71 70
c make kprintf externally visable (for the moment) 
c and fix bug in kprintn's buffer size
e
s 00033/00032/00433
d D 7.23 91/05/04 16:16:56 bostic 70 69
c lint
e
s 00303/00233/00162
d D 7.22 91/05/04 12:00:23 bostic 69 68
c reimplement kernel printf ((rename prf to kprintf, printn to kprintn)
c use ANSI stdarg.h and prototypes; several routines became static to this module
c minor cleanups/fixes, delete AT&T prorpietary comments
e
s 00018/00019/00377
d D 7.21 91/04/20 15:35:54 karels 68 67
c rm user.h; make consintr generic, not tahoe-specific; new calling convention
c for tprintf_open, cleaned-up types; ansify
e
s 00034/00034/00362
d D 7.20 91/03/17 15:41:47 karels 67 66
c more-or-less working with new proc & user structs
e
s 00008/00008/00388
d D 7.19 90/12/05 17:06:23 mckusick 66 65
c update for new VM
e
s 00064/00050/00332
d D 7.18 90/06/28 15:20:06 marc 65 64
c tprintf - for device drivers
e
s 00007/00006/00375
d D 7.17 90/05/15 14:44:05 mckusick 64 63
c lint; do not call logwakeup if paniced
e
s 00008/00001/00373
d D 7.16 90/04/05 14:59:51 marc 63 62
c v_getc and v_poll (to support kdb on workstations monitors)
e
s 00045/00060/00329
d D 7.15 89/11/20 18:17:32 marc 62 61
c pull out tty specific code
e
s 00000/00001/00389
d D 7.14 89/05/05 00:06:52 mckusick 61 60
c delete unneeded include of dir.h
e
s 00002/00002/00388
d D 7.13 89/04/25 10:52:18 mckusick 60 59
c ../machine => machine
e
s 00002/00002/00388
d D 7.12 88/07/25 11:40:19 karels 59 58
c KDB => KADB
e
s 00000/00013/00390
d D 7.11 88/05/26 08:57:31 karels 58 57
c change harderr to diskerr and move to ufs_disksubr.c
e
s 00010/00001/00393
d D 7.10 88/05/25 11:21:46 karels 57 56
c lint, add comments on %r
e
s 00003/00003/00391
d D 7.9 88/05/22 15:05:39 karels 56 55
c lint
e
s 00024/00008/00370
d D 7.8 88/02/08 21:39:03 karels 55 54
c printf %r; endian=>byte_order; lint; add msgbufmapped
e
s 00004/00002/00374
d D 7.7 87/03/29 20:43:32 karels 54 53
c don't let uprintf be interrupted (callers hold locked inodes, etc)
e
s 00013/00001/00363
d D 7.6 87/03/13 10:48:47 karels 53 52
c drop into kdb on panic, too
e
s 00002/00002/00362
d D 7.5 87/02/26 18:05:48 karels 52 51
c do it right
e
s 00016/00004/00348
d D 7.4 87/02/21 15:13:02 karels 51 50
c virtual consoles
e
s 00034/00015/00318
d D 7.3 86/11/03 12:00:08 karels 50 49
x 49
c merge in tahoe support
e
s 00018/00005/00328
d D 7.2 86/08/09 18:02:22 karels 49 48
c add substitutable cnputc, user console
e
s 00001/00001/00332
d D 7.1 86/06/05 00:06:54 mckusick 48 47
c 4.3BSD release version
e
s 00001/00001/00332
d D 6.13 86/02/26 16:04:59 bloom 47 46
c fix problem reading klog when last putchar write last char in buffer
e
s 00001/00001/00332
d D 6.12 86/02/23 23:10:10 karels 46 45
c lint
e
s 00003/00001/00330
d D 6.11 86/02/19 17:42:45 karels 45 44
c as ifdef the code, ifdef the variable
e
s 00043/00016/00288
d D 6.10 85/11/04 18:04:04 karels 44 43
c log tprintf's at LOG_INFO; block or skip tty if output queue is full
e
s 00001/00001/00303
d D 6.9 85/09/17 18:28:05 eric 43 42
c facilities in syslog
e
s 00001/00001/00303
d D 6.8 85/09/16 13:11:50 karels 42 41
c dkunit is gone
e
s 00007/00001/00297
d D 6.7 85/06/08 14:41:33 mckusick 41 40
c Add copyright
e
s 00012/00002/00286
d D 6.6 85/03/18 15:22:02 karels 40 39
c use separate global for open flag; print logged errors if log isn't 
c open yet; tprintf goes to log also
e
s 00009/00012/00279
d D 6.5 84/12/27 17:26:02 karels 39 38
c silliness
e
s 00001/00000/00290
d D 6.4 84/12/21 14:23:58 bloom 38 37
c include ioctl.h
e
s 00012/00012/00278
d D 6.3 84/08/29 20:21:32 bloom 37 36
c Change to includes.  no more ../h
e
s 00063/00027/00227
d D 6.2 84/07/17 16:16:59 ralph 36 35
c changes for /dev/klog. tprintf() interface added.
e
s 00000/00000/00254
d D 6.1 83/07/29 06:35:59 sam 35 34
c 4.2 distribution
e
s 00004/00016/00250
d D 4.28 83/07/01 02:19:10 sam 34 33
c purge #if sun's
e
s 00002/00000/00264
d D 4.27 83/05/27 12:47:29 sam 33 32
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00008/00001/00256
d D 4.26 83/05/18 02:01:02 sam 32 31
c sun changes
e
s 00005/00003/00252
d D 4.25 82/12/17 11:45:44 sam 31 30
c sun merge
e
s 00004/00004/00251
d D 4.24 82/10/31 14:14:34 root 30 29
c change #if to #ifdef
e
s 00016/00001/00239
d D 4.23 82/10/31 00:26:35 root 29 28
c first version with 68k stuff
e
s 00001/00001/00239
d D 4.22 82/10/10 15:34:16 root 28 27
c put headers for vax in separate directories
e
s 00003/00002/00237
d D 4.21 82/01/16 20:59:31 wnj 27 26
c clean crashes! 
e
s 00001/00001/00238
d D 4.20 82/01/14 17:00:44 wnj 26 25
c before move async to file table
e
s 00002/00002/00237
d D 4.19 81/11/20 14:43:18 wnj 25 23
c more lint
e
s 00069/00013/00226
d R 4.19 81/08/31 01:09:46 wnj 24 23
c implement error log device and time printing
e
s 00002/00001/00237
d D 4.18 81/06/11 15:42:38 wnj 23 22
c fix per kre to %B
e
s 00004/00000/00234
d D 4.17 81/05/11 11:14:02 root 22 21
c %%
e
s 00001/00000/00233
d D 4.16 81/03/17 05:50:21 wnj 21 20
c restor lost %s
e
s 00001/00001/00232
d D 4.15 81/03/09 01:48:02 wnj 20 19
c lint and a few minor fixed
e
s 00003/00004/00230
d D 4.14 81/03/09 00:32:58 wnj 19 18
c lint
e
s 00015/00003/00219
d D 4.13 81/03/06 18:20:38 wnj 18 17
c reformatting
e
s 00000/00014/00222
d D 4.12 81/03/03 11:06:50 wnj 17 16
c drop prdev
e
s 00044/00027/00192
d D 4.11 81/02/28 17:17:52 wnj 16 15
c changes for rmalloc, rmfree, malloc.c
e
s 00026/00012/00193
d D 4.10 81/02/25 21:23:27 wnj 15 14
c working %b code
e
s 00008/00009/00197
d D 4.9 81/02/15 12:20:06 wnj 14 13
c minor
e
s 00001/00001/00205
d D 4.8 81/02/08 18:34:48 wnj 13 12
c first working autoconf version
e
s 00073/00129/00133
d D 4.7 81/02/08 01:11:38 wnj 12 11
c misc pre-mba changes (non-recursive printf, futz, resuba, %uXX...)
e
s 00032/00003/00230
d D 4.6 81/02/07 15:43:04 kre 11 10
c non-negative hex + uprintf
e
s 00007/00005/00226
d D 4.5 81/01/28 12:04:05 toy 10 9
c unsigned hex; circular msgbuf
e
s 00009/00004/00222
d D 4.4 81/01/15 19:35:40 wnj 9 8
c fixes for saved msgbuf through crashes
e
s 00001/00001/00225
d D 4.3 80/11/09 23:34:46 bill 8 7
c function results (void)'ed for minor lint
e
s 00001/00001/00225
d D 4.2 80/11/09 23:00:38 bill 7 6
c minor lint
e
s 00000/00000/00226
d D 4.1 80/11/09 17:32:22 bill 6 5
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00001/00002/00225
d D 3.5 80/10/11 21:36:05 bill 5 4
c remove update() in panic()
e
s 00004/00005/00223
d D 3.4 80/10/02 10:40:53 bill 4 3
c first attempt at reboot stuff
e
s 00115/00017/00113
d D 3.3 80/06/22 12:32:58 bill 3 2
c trace()
e
s 00001/00001/00129
d D 3.2 80/06/07 02:46:53 bill 2 1
c %H%->%G%
e
s 00130/00000/00000
d D 3.1 80/04/09 16:03:52 bill 1 0
c date and time created 80/04/09 16:03:52 by bill
e
u
U
f b 
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 20
/*	%M%	%I%	%G%	*/
E 20
I 20
D 41
/*	%M%	%I%	%E%	*/
E 41
I 41
D 69
/*
D 48
 * Copyright (c) 1982 Regents of the University of California.
E 48
I 48
D 56
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 56
I 56
D 68
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 68
I 68
 * Copyright (c) 1982, 1986, 1988, 1991 Regents of the University of California.
E 68
E 56
E 48
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 69
I 69
/*-
D 88
 * Copyright (c) 1986, 1988, 1991 The Regents of the University of California.
 * All rights reserved.
E 88
I 88
 * Copyright (c) 1986, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 90
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 90
E 88
E 69
 *
I 69
 * %sccs.include.redist.c%
 *
E 69
 *	%W% (Berkeley) %G%
 */
I 50
D 53
#include "../machine/mtpr.h"
E 53
E 50
E 41
E 20
E 2

D 37
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/seg.h"
#include "../h/buf.h"
#include "../h/conf.h"
I 3
D 28
#include "../h/mtpr.h"
E 28
I 4
#include "../h/reboot.h"
I 9
#include "../h/vm.h"
#include "../h/msgbuf.h"
I 11
#include "../h/dir.h"
#include "../h/user.h"
I 31
#include "../h/proc.h"
E 31
#include "../h/tty.h"
E 37
I 37
D 79
#include "param.h"
#include "systm.h"
D 67
#include "seg.h"
E 67
#include "buf.h"
#include "conf.h"
#include "reboot.h"
D 66
#include "vm.h"
E 66
#include "msgbuf.h"
D 61
#include "dir.h"
E 61
D 68
#include "user.h"
E 68
#include "proc.h"
I 38
#include "ioctl.h"
I 62
#include "vnode.h"
#include "file.h"
E 62
E 38
#include "tty.h"
I 65
#include "tprintf.h"
E 65
I 40
#include "syslog.h"
I 65
#include "malloc.h"
E 79
I 79
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/reboot.h>
#include <sys/msgbuf.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/tty.h>
#include <sys/tprintf.h>
#include <sys/syslog.h>
#include <sys/malloc.h>
E 79
E 65
E 40
E 37
E 11
E 9
E 4
E 3

I 69
/*
 * Note that stdarg.h and the ANSI style va_start macro is used for both
 * ANSI and traditional C compilers.
 */
#include <machine/stdarg.h>

E 69
I 53
D 60
#include "../machine/mtpr.h"
E 60
I 60
D 67
#include "machine/mtpr.h"
E 67
E 60
D 59
#ifdef KDB
E 59
I 59
#ifdef KADB
E 59
D 60
#include "../machine/kdbparam.h"
E 60
I 60
D 87
#include "machine/kdbparam.h"
E 87
I 87
#include <machine/kdbparam.h>
E 87
E 60
#endif

E 53
I 34
D 50
#ifdef vax
#include "../vax/mtpr.h"
#endif

E 50
I 36
D 69
#define TOCONS	0x1
#define TOTTY	0x2
#define TOLOG	0x4
E 69
I 69
#define TOCONS	0x01
#define TOTTY	0x02
#define TOLOG	0x04
E 69

E 36
E 34
I 3
D 12
#ifdef TRACE
#define	TRCBUFS	4096
char	trcbuf[TRCBUFS];
char	*trcbufp = trcbuf;
int	trcwrap;
int	trcprt = TRCBUFS;
#endif

E 12
E 3
D 69
/*
 * In case console is off,
 * panicstr contains argument to last
 * call to panic.
 */
D 16

E 16
char	*panicstr;

I 51
extern	cnputc();			/* standard console putc */
I 63
int	(*v_putc)() = cnputc;		/* routine to putc on virtual console */
E 63
extern	struct tty cons;		/* standard console tty */
E 69
struct	tty *constty;			/* pointer to console "window" tty */
D 63
int	(*v_putc)() = cnputc;		/* routine to putc on virtual console */
E 63
I 63

D 84
#ifdef KADB
extern	cngetc();			/* standard console getc */
D 69
extern	cnpoll();
E 69
int	(*v_getc)() = cngetc;		/* "" getc from virtual console */
I 69
extern	cnpoll();
E 69
int	(*v_poll)() = cnpoll;		/* kdb hook to enable input polling */
#endif
E 84
I 69
extern	cnputc();			/* standard console putc */
D 76
int	(*v_putc)() = cnputc;          	/* routine to putc on virtual console */
E 76
I 76
int	(*v_putc)() = cnputc;		/* routine to putc on virtual console */
E 76
E 69
E 63

I 69
D 70
static void logpri __P((int));
static void putchar __P((int, int, struct tty *));
static void kprintf __P((const char *, int, struct tty *, ...));
static void kprintn __P((u_long, int));
E 70
I 70
D 73
static void logpri __P((int level));
static void putchar __P((int ch, int flags, struct tty *tp));
D 71
static void kprintf __P((const char *fmt, int flags, struct tty *tp, va_list));
E 71
I 71
void kprintf __P((const char *fmt, int flags, struct tty *tp, va_list));
E 71
static void kprintn __P((u_long num, int base, int flags, struct tty *tp));
E 73
I 73
D 78
static void  logpri __P((int level));
E 78
I 78
void  logpri __P((int level));
E 78
static void  putchar __P((int ch, int flags, struct tty *tp));
D 74
static void  kprintf __P((const char *fmt, int flags, struct tty *tp, va_list));
E 74
static char *ksprintn __P((u_long num, int base, int *len));
I 74
D 79
void  kprintf __P((const char *fmt, int flags, struct tty *tp, va_list));
E 79
I 79
D 82
void kprintf __P((const char *fmt, int flags, struct tty *tp, va_list ap, ...));
E 82
I 82
void kprintf __P((const char *fmt, int flags, struct tty *tp, va_list ap));
E 82
E 79
E 74
E 73
E 70

I 79
int consintr = 1;			/* Ok to handle console interrupts? */

E 79
E 69
E 51
I 49
extern	cnputc();			/* standard console putc */
extern	struct tty cons;		/* standard console tty */
struct	tty *constty;			/* pointer to console "window" tty */
int	(*v_console)() = cnputc;	/* routine to putc on virtual console */

E 49
/*
D 69
 * Scaled down version of C Library printf.
D 16
 * Only %s %u %d (==%u) %o %x %D are recognized.
 * Used to print diagnostic information
 * directly on console tty.
 * Since it is not interrupt driven,
 * all system activities are pretty much
 * suspended.
 * Printf should not be used for chit-chat.
E 16
I 16
 * Used to print diagnostic information directly on console tty.
 * Since it is not interrupt driven, all system activities are
 * suspended.  Printf should not be used for chit-chat.
 *
 * One additional format: %b is supported to decode error registers.
 * Usage is:
 *	printf("reg=%b\n", regval, "<base><arg>*");
 * Where <base> is the output base expressed as a control character,
 * e.g. \10 gives octal; \20 gives hex.  Each arg is a sequence of
 * characters, the first of which gives the bit number to be inspected
 * (origin 1), and the next characters (up to a control character, i.e.
 * a character <= 32), give the name of the register.  Thus
 *	printf("reg=%b\n", 3, "\10\2BITTWO\1BITONE\n");
 * would produce output:
D 39
 *	reg=2<BITTWO,BITONE>
E 39
I 39
 *	reg=3<BITTWO,BITONE>
I 57
 *
 * Another additional format: %r is used to pass an additional format string
 * and argument list recursively.  Usage is typically:
 *
 * fn(otherstuff, fmt [, arg1, ... ] )
 *	char *fmt;
 *	u_int arg1, ...;
 *
 *	printf("prefix: %r, other stuff\n", fmt, &arg1);
E 69
I 69
D 79
 * Variable panicstr contains argument to first call to panic; used
 * as flag to indicate that the kernel has already called panic.
E 79
I 79
 * Variable panicstr contains argument to first call to panic; used as flag
 * to indicate that the kernel has already called panic.
E 79
E 69
E 57
E 39
E 16
 */
I 69
D 79
char	*panicstr;
E 79
I 79
const char *panicstr;
E 79
E 69
I 50
D 68
#if defined(tahoe)
int	consintr;
#endif
E 68

I 68
D 69
int	consintr = 1;			/* ok to handle console interrupts? */
E 69
I 69
/*
 * Panic is called on unresolvable fatal errors.  It prints "panic: mesg",
 * and then reboots.  If we are called twice, then we avoid trying to sync
 * the disks as this often leads to recursive panics.
 */
I 82
#ifdef __GNUC__
I 83
volatile void boot(int flags);	/* boot() does not return */
E 83
volatile			/* panic() does not return */
#endif
E 82
void
D 79
panic(msg)
	char *msg;
E 79
I 79
#ifdef __STDC__
panic(const char *fmt, ...)
#else
D 84
panic(fmt /*, va_alist */)
E 84
I 84
panic(fmt, va_alist)
E 84
	char *fmt;
#endif
E 79
{
D 79
	int bootopt = RB_AUTOBOOT | RB_DUMP;
E 79
I 79
D 82
	int bootopt, savintr;
E 82
I 82
	int bootopt;
E 82
	va_list ap;
E 79
D 76
	int s;
E 76
E 69

I 79
	bootopt = RB_AUTOBOOT | RB_DUMP;
E 79
E 68
E 50
D 69
/*VARARGS1*/
D 67
printf(fmt, x1)
E 67
I 67
printf(fmt, args)
E 67
D 16
register char *fmt;
unsigned x1;
E 16
I 16
	char *fmt;
D 67
	unsigned x1;
E 67
I 67
	unsigned args;
E 69
I 69
	if (panicstr)
		bootopt |= RB_NOSYNC;
	else
D 79
		panicstr = msg;
	printf("panic: %s\n", msg);
E 79
I 79
		panicstr = fmt;

D 82
	savintr = consintr;		/* disable interrupts */
	consintr = 0;

E 82
	va_start(ap, fmt);
D 82
	kprintf("panic: ", TOCONS | TOLOG, NULL, ap);
	kprintf(fmt, TOCONS | TOLOG, NULL, ap);
E 82
I 82
	printf("panic: %r\n", fmt, ap);
E 82
	va_end(ap);

D 82
	consintr = savintr;		/* reenable interrupts */

E 82
E 79
#ifdef KGDB
	kgdb_panic();
#endif
#ifdef KADB
D 84
	if (boothowto & RB_KDB) {
D 76
		s = splnet();		/* below kdb pri */
E 76
I 76
D 77
		int s = splnet();	/* below kdb pri */
E 77
I 77
		int s;

		s = splnet();	/* below kdb pri */
E 77
E 76
		setsoftkdb();
		splx(s);
	}
E 84
I 84
	if (boothowto & RB_KDB)
		kdbpanic();
E 84
#endif
	boot(bootopt);
}

/*
 * Warn that a system table is full.
 */
void
tablefull(tab)
D 83
	char *tab;
E 83
I 83
	const char *tab;
E 83
E 69
E 67
E 16
{
I 50
D 68
#if defined(tahoe)
E 68
D 69
	register int savintr;
E 69
E 50
I 3

I 50
D 69
	savintr = consintr, consintr = 0;	/* disable interrupts */
D 68
#endif
E 68
E 50
D 36
	prf(fmt, &x1, 0);
E 36
I 36
D 62
	prf(fmt, &x1, TOCONS | TOLOG, (struct tty *)0);
E 62
I 62
D 65
	prf(fmt, &x1, TOCONS | TOLOG, (caddr_t)0);
E 65
I 65
D 67
	prf(fmt, &x1, TOCONS | TOLOG, (struct tty *)NULL);
E 67
I 67
	prf(fmt, &args, TOCONS | TOLOG, (struct tty *)NULL);
E 67
E 65
E 62
D 64
	logwakeup();
E 64
I 64
	if (!panicstr)
		logwakeup();
E 64
I 50
D 68
#if defined(tahoe)
E 68
	consintr = savintr;			/* reenable interrupts */
E 69
I 69
	log(LOG_ERR, "%s: table is full\n", tab);
E 69
D 68
#endif
E 68
E 50
E 36
}

D 12
#ifdef TRACE
trace(fmt, x1)
register char *fmt;
unsigned x1;
E 12
I 12
/*
D 16
 * print to the current users terminal,
 * guarantee not to sleep (so can be called by intr routine)
 * no watermark checking - so no verbose messages
E 16
I 16
D 39
 * Uprintf prints to the current user's terminal,
 * guarantees not to sleep (so can be called by interrupt routines)
E 39
I 39
D 44
 * Uprintf prints to the current user's terminal
E 39
 * and does no watermark checking - (so no verbose messages).
E 44
I 44
D 62
 * Uprintf prints to the current user's terminal.
E 62
I 62
 * Uprintf prints to the controlling terminal for the current process.
E 62
D 69
 * It may block if the tty queue is overfull.
I 54
 * No message is printed if the queue does not clear
 * in a reasonable time.
E 69
I 69
 * It may block if the tty queue is overfull.  No message is printed if
 * the queue does not clear in a reasonable time.
E 69
E 54
D 62
 * Should determine whether current terminal user is related
 * to this process.
E 62
E 44
E 16
 */
D 69
/*VARARGS1*/
D 67
uprintf(fmt, x1)
E 67
I 67
uprintf(fmt, args)
E 69
I 69
void
#ifdef __STDC__
uprintf(const char *fmt, ...)
#else
D 80
uprintf(fmt /*, va_alist */)
E 80
I 80
uprintf(fmt, va_alist)
E 80
E 69
E 67
D 16
	char	*fmt;
E 16
I 16
	char *fmt;
E 16
D 67
	unsigned x1;
E 67
I 67
D 69
	unsigned args;
E 69
I 69
#endif
E 69
E 67
E 12
{
I 45
D 62
#ifdef notdef
E 45
I 44
	register struct proc *p;
I 45
#endif
E 45
	register struct tty *tp;
E 62
I 62
D 65
	register struct tty *tp = u.u_procp->p_session->s_ttyp;
E 65
I 65
D 67
	register struct proc *p = u.u_procp;
E 67
I 67
	register struct proc *p = curproc;
I 69
	va_list ap;
E 69
E 67
E 65
E 62
E 44

I 69
D 76
	va_start(ap, fmt);
E 69
D 12
	prf(fmt, &x1, 1);
E 12
I 12
D 36
	prf(fmt, &x1, 2);
E 36
I 36
D 44
	prf(fmt, &x1, TOTTY, u.u_ttyp);
E 44
I 44
D 62
	if ((tp = u.u_ttyp) == NULL)
		return;
#ifdef notdef
	if (tp->t_pgrp && (p = pfind(tp->t_pgrp)))
D 45
		if (p->p_uid != u.u_uid)
E 45
I 45
		if (p->p_uid != u.u_uid)	/* doesn't account for setuid */
E 45
			return;
#endif
D 54
	(void)ttycheckoutq(tp, 1);
	prf(fmt, &x1, TOTTY, tp);
E 54
I 54
	if (ttycheckoutq(tp, 1))
E 62
I 62
D 65
	if (tp != NULL && tp->t_session == u.u_procp->p_session)
E 62
D 64
		prf(fmt, &x1, TOTTY, tp);
E 64
I 64
		prf(fmt, &x1, TOTTY, (caddr_t)tp);
E 65
I 65
	if (p->p_flag & SCTTY && p->p_session->s_ttyvp)
E 76
I 76
D 89
	if (p->p_flag & SCTTY && p->p_session->s_ttyvp) {
E 89
I 89
	if (p->p_flag & P_CONTROLT && p->p_session->s_ttyvp) {
E 89
		va_start(ap, fmt);
E 76
D 67
		prf(fmt, &x1, TOTTY, p->p_session->s_ttyp);
E 67
I 67
D 69
		prf(fmt, &args, TOTTY, p->p_session->s_ttyp);
E 69
I 69
		kprintf(fmt, TOTTY, p->p_session->s_ttyp, ap);
D 76
	va_end(ap);
E 76
I 76
		va_end(ap);
	}
E 76
E 69
E 67
E 65
E 64
E 54
E 44
E 36
E 12
}

I 65
tpr_t
D 68
tprintf_open()
E 68
I 68
tprintf_open(p)
	register struct proc *p;
E 68
{
I 76

E 76
D 67
	register struct proc *p = u.u_procp;
E 67
I 67
D 68
	register struct proc *p = curproc;
E 68
E 67
D 69

E 69
D 89
	if (p->p_flag & SCTTY && p->p_session->s_ttyvp) {
E 89
I 89
	if (p->p_flag & P_CONTROLT && p->p_session->s_ttyvp) {
E 89
		SESSHOLD(p->p_session);
D 68
		return ((tpr_t)p->p_session);
E 68
I 68
		return ((tpr_t) p->p_session);
E 68
D 69
	} else
D 68
		return ((tpr_t)NULL);
E 68
I 68
		return ((tpr_t) NULL);
E 69
I 69
	}
	return ((tpr_t) NULL);
E 69
E 68
}

I 68
void
E 68
tprintf_close(sess)
	tpr_t sess;
{
I 76

E 76
	if (sess)
D 68
		SESSRELE(sess);
E 68
I 68
		SESSRELE((struct session *) sess);
E 68
}

E 65
I 40
/*
D 65
 * tprintf prints on the specified terminal (console if none)
 * and logs the message.  It is designed for error messages from
D 44
 * single-open devices, and may be called from interrupt level.
E 44
I 44
 * single-open devices, and may be called from interrupt level
 * (does not sleep).
E 65
I 65
 * tprintf prints on the controlling terminal associated
D 69
 * with the given session.  
E 69
I 69
 * with the given session.
E 69
E 65
E 44
 */
E 40
D 12
#endif

prf(fmt, adx, trace)
E 12
I 12
D 16
/* THIS CODE IS VAX DEPENDENT */
E 16
D 36
prf(fmt, adx, touser)
E 36
I 36
D 69
/*VARARGS2*/
D 44
tprintf(ttyp, fmt, x1)
	struct tty *ttyp;
E 44
I 44
D 62
tprintf(tp, fmt, x1)
	register struct tty *tp;
E 62
I 62
D 65
tprintf(vp, fmt, x1)
	register caddr_t vp;
E 65
I 65
D 67
tprintf(sess, fmt, x1)
E 67
I 67
D 68
tprintf(sess, fmt, args)
E 67
	register tpr_t sess;
E 68
I 68
tprintf(tpr, fmt, args)
E 69
I 69
void
#ifdef __STDC__
tprintf(tpr_t tpr, const char *fmt, ...)
#else
D 80
tprintf(tpr, fmt /*, va_alist */)
E 80
I 80
tprintf(tpr, fmt, va_alist)
E 80
E 69
	tpr_t tpr;
E 68
E 65
E 62
E 44
	char *fmt;
D 67
	unsigned x1;
E 67
I 67
D 69
	unsigned args;
E 69
I 69
#endif
E 69
E 67
{
I 68
	register struct session *sess = (struct session *)tpr;
	struct tty *tp = NULL;
E 68
I 64
D 65
#ifdef notyet
E 64
I 44
	int flags = TOTTY | TOLOG;
E 65
I 65
	int flags = TOLOG;
I 69
	va_list ap;
E 69
E 65
D 49
D 51
	extern struct tty cons;
E 51
E 49
E 44

I 62
D 64
#ifdef notyet
E 64
E 62
D 40
	prf(fmt, &x1, TOTTY, ttyp);
E 40
I 40
D 44
	prf(fmt, &x1, TOTTY | TOLOG, ttyp);
E 44
I 44
	logpri(LOG_INFO);
D 49
D 62
	if (tp == (struct tty *)NULL)
		tp = &cons;
E 49
I 49
	if (tp == (struct tty *)NULL) {
		tp = constty;
		if (tp == (struct tty *)NULL)
			tp = &cons;
	}
E 49
	if (ttycheckoutq(tp, 0) == 0)
E 62
I 62
D 69

E 69
D 65
	if (vp == NULL || 
	    VOP_IOCTL(vp, TIOCCHECKOUTQ, &val, FWRITE, NOCRED) != 0 || 
	    val == 0)
E 62
		flags = TOLOG;
D 62
	prf(fmt, &x1, flags, tp);
E 62
I 62
	prf(fmt, &x1, flags, vp);
E 65
I 65
D 68
	if (sess && sess->s_ttyvp && ttycheckoutq(sess->s_ttyp, 0))
E 68
I 68
	if (sess && sess->s_ttyvp && ttycheckoutq(sess->s_ttyp, 0)) {
E 68
		flags |= TOTTY;
D 67
	prf(fmt, &x1, flags, sess->s_ttyp);
E 67
I 67
D 68
	prf(fmt, &args, flags, sess->s_ttyp);
E 68
I 68
		tp = sess->s_ttyp;
	}
D 69
	prf(fmt, &args, flags, tp);
E 69
I 69
	va_start(ap, fmt);
	kprintf(fmt, flags, tp, ap);
	va_end(ap);
E 69
E 68
E 67
E 65
E 62
	logwakeup();
I 62
D 65
#else
	printf("tprintf called\n");
#endif
E 65
E 62
E 44
E 40
}

I 69
/*
 * Ttyprintf displays a message on a tty; it should be used only by
 * the tty driver, or anything that knows the underlying tty will not
 * be revoke(2)'d away.  Other callers should use tprintf.
 */
void
#ifdef __STDC__
ttyprintf(struct tty *tp, const char *fmt, ...)
#else
D 80
ttyprintf(tp, fmt /*, va_alist */)
E 80
I 80
ttyprintf(tp, fmt, va_alist)
E 80
	struct tty *tp;
	char *fmt;
#endif
{
	va_list ap;

	va_start(ap, fmt);
	kprintf(fmt, TOTTY, tp, ap);
	va_end(ap);
}

E 69
I 68
extern	int log_open;
E 68
I 65

E 65
/*
D 69
 * Log writes to the log buffer,
D 39
 * guarantees not to sleep (so can be called by interrupt routines)
 * and does no watermark checking - (so no verbose messages).
E 39
I 39
 * and guarantees not to sleep (so can be called by interrupt routines).
I 40
 * If there is no process reading the log yet, it writes to the console also.
E 69
I 69
 * Log writes to the log buffer, and guarantees not to sleep (so can be
 * called by interrupt routines).  If there is no process reading the
 * log yet, it writes to the console also.
E 69
E 40
E 39
 */
D 69
/*VARARGS2*/
D 67
log(level, fmt, x1)
E 67
I 67
log(level, fmt, args)
E 69
I 69
void
#ifdef __STDC__
log(int level, const char *fmt, ...)
#else
D 80
log(level, fmt /*, va_alist */)
E 80
I 80
log(level, fmt, va_alist)
E 80
	int level;
E 69
E 67
	char *fmt;
D 67
	unsigned x1;
E 67
I 67
D 69
	unsigned args;
E 69
I 69
#endif
E 69
E 67
{
D 76
	register s = splhigh();
E 76
I 76
D 77
	register int s = splhigh();
E 77
I 77
	register int s;
E 77
E 76
I 69
	va_list ap;
E 69
I 40
D 68
	extern int log_open;
E 68
E 40

I 77
	s = splhigh();
E 77
D 44
	putchar('<', TOLOG, (struct tty *)0);
	printn(level, 10, TOLOG, (struct tty *)0);
	putchar('>', TOLOG, (struct tty *)0);
E 44
I 44
	logpri(level);
E 44
D 62
	prf(fmt, &x1, TOLOG, (struct tty *)0);
E 62
I 62
D 65
	prf(fmt, &x1, TOLOG, (caddr_t)0);
E 65
I 65
D 67
	prf(fmt, &x1, TOLOG, (struct tty *)NULL);
E 67
I 67
D 69
	prf(fmt, &args, TOLOG, (struct tty *)NULL);
E 69
I 69
	va_start(ap, fmt);
	kprintf(fmt, TOLOG, NULL, ap);
E 69
E 67
E 65
E 62
	splx(s);
I 40
D 76
	if (!log_open)
D 62
		prf(fmt, &x1, TOCONS, (struct tty *)0);
E 62
I 62
D 65
		prf(fmt, &x1, TOCONS, (caddr_t)0);
E 65
I 65
D 67
		prf(fmt, &x1, TOCONS, (struct tty *)NULL);
E 67
I 67
D 69
		prf(fmt, &args, TOCONS, (struct tty *)NULL);
E 69
I 69
		kprintf(fmt, TOCONS, NULL, ap);
E 76
	va_end(ap);
I 76
	if (!log_open) {
		va_start(ap, fmt);
		kprintf(fmt, TOCONS, NULL, ap);
		va_end(ap);
	}
E 76
E 69
E 67
E 65
E 62
E 40
	logwakeup();
}

I 69
D 78
static void
E 78
I 78
void
E 78
E 69
I 44
logpri(level)
	int level;
{
I 73
	register int ch;
	register char *p;
E 73

D 64
	putchar('<', TOLOG, (struct tty *)0);
D 46
	printn(level, 10, TOLOG, (struct tty *)0);
E 46
I 46
	printn((u_long)level, 10, TOLOG, (struct tty *)0);
E 46
	putchar('>', TOLOG, (struct tty *)0);
E 64
I 64
D 65
	putchar('<', TOLOG, (caddr_t)0);
	printn((u_long)level, 10, TOLOG, (caddr_t)0);
	putchar('>', TOLOG, (caddr_t)0);
E 65
I 65
D 69
	putchar('<', TOLOG, (struct tty *)NULL);
	printn((u_long)level, 10, TOLOG, (struct tty *)NULL);
	putchar('>', TOLOG, (struct tty *)NULL);
E 69
I 69
	putchar('<', TOLOG, NULL);
D 73
	kprintn((u_long)level, 10, TOLOG, NULL);
E 73
I 73
	for (p = ksprintn((u_long)level, 10, NULL); ch = *p--;)
		putchar(ch, TOLOG, NULL);
E 73
	putchar('>', TOLOG, NULL);
E 69
E 65
E 64
}

I 55
D 69
/*VARARGS1*/
D 67
addlog(fmt, x1)
E 67
I 67
addlog(fmt, args)
E 69
I 69
void
#ifdef __STDC__
addlog(const char *fmt, ...)
#else
D 80
addlog(fmt /*, va_alist */)
E 80
I 80
addlog(fmt, va_alist)
E 80
E 69
E 67
	char *fmt;
D 67
	unsigned x1;
E 67
I 67
D 69
	unsigned args;
E 69
I 69
#endif
E 69
E 67
{
D 76
	register s = splhigh();
E 76
I 76
D 77
	register int s = splhigh();
E 77
I 77
	register int s;
E 77
E 76
I 69
	va_list ap;
E 69

I 77
	s = splhigh();
E 77
D 62
	prf(fmt, &x1, TOLOG, (struct tty *)0);
E 62
I 62
D 65
	prf(fmt, &x1, TOLOG, (caddr_t)0);
E 65
I 65
D 67
	prf(fmt, &x1, TOLOG, (struct tty *)NULL);
E 67
I 67
D 69
	prf(fmt, &args, TOLOG, (struct tty *)NULL);
E 69
I 69
	va_start(ap, fmt);
	kprintf(fmt, TOLOG, NULL, ap);
E 69
E 67
E 65
E 62
	splx(s);
D 76
	if (!log_open)
D 62
		prf(fmt, &x1, TOCONS, (struct tty *)0);
E 62
I 62
D 65
		prf(fmt, &x1, TOCONS, (caddr_t)0);
E 65
I 65
D 67
		prf(fmt, &x1, TOCONS, (struct tty *)NULL);
E 67
I 67
D 69
		prf(fmt, &args, TOCONS, (struct tty *)NULL);
E 69
I 69
		kprintf(fmt, TOCONS, NULL, ap);
E 76
	va_end(ap);
I 76
	if (!log_open) {
		va_start(ap, fmt);
		kprintf(fmt, TOCONS, NULL, ap);
		va_end(ap);
	}
E 76
E 69
E 67
E 65
E 62
	logwakeup();
}

I 76
D 77
#if defined(tahoe)
E 77
E 76
E 55
E 44
D 62
prf(fmt, adx, flags, ttyp)
E 62
I 62
D 65
prf(fmt, adx, flags, where)
E 65
I 65
D 67
prf(fmt, adx, flags, ttyp)
E 67
I 67
D 69
prf(fmt, argp, flags, ttyp)
E 67
E 65
E 62
E 36
E 12
D 16
register char *fmt;
D 12
register unsigned int *adx;
E 12
I 12
register u_int *adx;
E 16
I 16
	register char *fmt;
D 67
	register u_int *adx;
E 67
I 67
	register u_int *argp;
E 67
I 36
D 62
	struct tty *ttyp;
E 62
I 62
D 65
	caddr_t where;
E 65
I 65
	struct tty *ttyp;
E 65
E 62
E 36
E 16
E 12
{
E 3
D 12
	register c;
E 12
I 12
D 14
	register int b, c;
E 14
I 14
	register int b, c, i;
E 14
E 12
D 3
	register unsigned int *adx;
E 3
	char *s;
I 15
	int any;
E 69
I 69
D 79
int	consintr = 1;			/* ok to handle console interrupts? */
I 76
D 77
#endif
E 77
E 76
E 69
E 15

E 79
D 3
	adx = &x1;
E 3
D 69
loop:
D 12
	while((c = *fmt++) != '%') {
E 12
I 12
	while ((c = *fmt++) != '%') {
E 12
D 36
		if(c == '\0')
E 36
I 36
		if (c == '\0')
E 36
			return;
D 3
		putchar(c);
E 3
I 3
D 12
		putchar(c, trace);
E 12
I 12
D 36
		putchar(c, touser);
E 36
I 36
D 62
		putchar(c, flags, ttyp);
E 62
I 62
D 65
		putchar(c, flags, where);
E 65
I 65
		putchar(c, flags, ttyp);
E 65
E 62
E 36
E 12
E 3
	}
I 12
again:
E 12
	c = *fmt++;
I 16
D 50
	/* THIS CODE IS VAX DEPENDENT IN HANDLING %l? AND %c */
E 50
I 50
	/* THIS CODE IS MACHINE DEPENDENT IN HANDLING %l? AND %c */
E 50
E 16
D 3
	if(c == 'X')
		printx((long)*adx);
	else if(c == 'd' || c == 'u' || c == 'o' || c == 'x')
		printn((long)*adx, c=='o'? 8: (c=='x'? 16:10));
	else if(c == 's') {
E 3
I 3
D 12
	if (c == 'X')
		printx((long)*adx, trace);
	else if (c == 'd' || c == 'u' || c == 'o' || c == 'x')
		printn((long)*adx, c=='o'? 8: (c=='x'? 16:10), trace);
	else if (c == 's') {
E 12
I 12
	switch (c) {

	case 'l':
		goto again;
	case 'x': case 'X':
		b = 16;
		goto number;
	case 'd': case 'D':
D 50
	case 'u':		/* what a joke */
E 50
I 50
		b = -10;
		goto number;
	case 'u':
E 50
		b = 10;
		goto number;
	case 'o': case 'O':
		b = 8;
number:
D 19
		printn(*adx, b, touser);
E 19
I 19
D 36
		printn((u_long)*adx, b, touser);
E 36
I 36
D 62
		printn((u_long)*adx, b, flags, ttyp);
E 62
I 62
D 65
		printn((u_long)*adx, b, flags, where);
E 65
I 65
D 67
		printn((u_long)*adx, b, flags, ttyp);
E 67
I 67
		printn((u_long)*argp, b, flags, ttyp);
E 67
E 65
E 62
E 36
E 19
		break;
	case 'c':
D 14
		c = *adx;
		while (c) {
			putchar(c&0x7f, touser);
			c >>= 8;
		}
E 14
I 14
D 67
		b = *adx;
E 67
I 67
		b = *argp;
E 67
I 50
D 55
#if ENDIAN == LITTLE
E 55
I 55
#if BYTE_ORDER == LITTLE_ENDIAN
E 55
E 50
		for (i = 24; i >= 0; i -= 8)
			if (c = (b >> i) & 0x7f)
D 36
				putchar(c, touser);
E 36
I 36
D 62
				putchar(c, flags, ttyp);
E 62
I 62
D 65
				putchar(c, flags, where);
E 65
I 65
				putchar(c, flags, ttyp);
E 69
I 69
void
#ifdef __STDC__
printf(const char *fmt, ...)
#else
D 80
printf(fmt /*, va_alist */)
E 80
I 80
printf(fmt, va_alist)
E 80
	char *fmt;
E 69
E 65
E 62
I 50
#endif
D 55
#if ENDIAN == BIG
E 55
I 55
D 69
#if BYTE_ORDER == BIG_ENDIAN
E 55
		if (c = (b & 0x7f))
D 62
			putchar(c, flags, ttyp);
E 62
I 62
D 65
			putchar(c, flags, where);
E 65
I 65
			putchar(c, flags, ttyp);
E 65
E 62
#endif
E 50
E 36
E 14
		break;
I 15
	case 'b':
D 67
		b = *adx++;
		s = (char *)*adx;
E 67
I 67
		b = *argp++;
		s = (char *)*argp;
E 67
D 19
		printn(b, *s++, touser);
E 19
I 19
D 36
		printn((u_long)b, *s++, touser);
E 36
I 36
D 62
		printn((u_long)b, *s++, flags, ttyp);
E 62
I 62
D 65
		printn((u_long)b, *s++, flags, where);
E 65
I 65
		printn((u_long)b, *s++, flags, ttyp);
E 65
E 62
E 36
E 19
		any = 0;
		if (b) {
D 36
			putchar('<', touser);
E 36
I 36
D 39
			putchar('<', flags, ttyp);
E 39
E 36
			while (i = *s++) {
				if (b & (1 << (i-1))) {
D 39
					if (any)
D 36
						putchar(',', touser);
E 36
I 36
						putchar(',', flags, ttyp);
E 39
I 39
D 50
					putchar(any? ',' : '<', flags, ttyp);
E 50
I 50
D 62
					putchar(any ? ',' : '<', flags, ttyp);
E 62
I 62
D 65
					putchar(any ? ',' : '<', flags, where);
E 65
I 65
					putchar(any ? ',' : '<', flags, ttyp);
E 65
E 62
E 50
E 39
E 36
					any = 1;
					for (; (c = *s) > 32; s++)
D 36
						putchar(c, touser);
E 36
I 36
D 62
						putchar(c, flags, ttyp);
E 62
I 62
D 65
						putchar(c, flags, where);
E 65
I 65
						putchar(c, flags, ttyp);
E 65
E 62
E 36
				} else
					for (; *s > 32; s++)
						;
			}
D 23
			putchar('>', touser);
E 23
I 23
			if (any)
D 36
				putchar('>', touser);
E 36
I 36
D 62
				putchar('>', flags, ttyp);
E 62
I 62
D 65
				putchar('>', flags, where);
E 65
I 65
				putchar('>', flags, ttyp);
E 65
E 62
E 36
E 23
		}
		break;
E 69
I 69
{
D 76
	register int savintr;
E 76
	va_list ap;
I 76
D 77
#ifdef tahoe
E 77
	register int savintr;
E 76
E 69

E 15
D 69
	case 's':
E 12
E 3
D 67
		s = (char *)*adx;
E 67
I 67
		s = (char *)*argp;
E 67
D 3
		while(c = *s++)
			putchar(c);
E 3
I 3
		while (c = *s++)
D 12
#ifdef TRACE
D 11
			if (trace) {
E 11
I 11
			if (trace == 1) {
E 11
				*trcbufp++ = c;
				if (trcbufp >= &trcbuf[TRCBUFS]) {
					trcbufp = trcbuf;
					trcwrap = 1;
				}
			} else
#endif
				putchar(c, trace);
E 3
	} else if (c == 'D') {
D 3
		printn(*(long *)adx, 10);
E 3
I 3
		printn(*(long *)adx, 10, trace);
E 3
		adx += (sizeof(long) / sizeof(int)) - 1;
E 12
I 12
D 36
			putchar(c, touser);
E 36
I 36
D 62
			putchar(c, flags, ttyp);
E 62
I 62
D 65
			putchar(c, flags, where);
E 65
I 65
			putchar(c, flags, ttyp);
E 65
E 62
E 36
		break;
I 22

I 55
	case 'r':
D 67
		s = (char *)*adx++;
D 57
		prf(s, *adx, flags, ttyp);
E 57
I 57
D 62
		prf(s, (u_int *)*adx, flags, ttyp);
E 62
I 62
D 65
		prf(s, (u_int *)*adx, flags, where);
E 65
I 65
		prf(s, (u_int *)*adx, flags, ttyp);
E 67
I 67
		s = (char *)*argp++;
		prf(s, (u_int *)*argp, flags, ttyp);
E 67
E 65
E 62
E 57
		break;

E 55
	case '%':
D 36
		putchar('%', touser);
E 36
I 36
D 62
		putchar('%', flags, ttyp);
E 62
I 62
D 65
		putchar('%', flags, where);
E 65
I 65
		putchar('%', flags, ttyp);
E 65
E 62
E 36
		break;
E 22
E 12
	}
D 67
	adx++;
E 67
I 67
	argp++;
E 67
	goto loop;
E 69
I 69
	savintr = consintr;		/* disable interrupts */
	consintr = 0;
I 76
D 77
#endif
E 77
E 76
	va_start(ap, fmt);
	kprintf(fmt, TOCONS | TOLOG, NULL, ap);
	va_end(ap);
	if (!panicstr)
		logwakeup();
I 76
D 77
#ifdef tahoe
E 77
E 76
	consintr = savintr;		/* reenable interrupts */
I 76
D 77
#endif
E 77
E 76
E 69
}
I 12
D 16
/* END VAX DEPENDENT CODE */
E 16
E 12

I 16
/*
D 69
 * Printn prints a number n in base b.
D 67
 * We don't use recursion to avoid deep kernel stacks.
E 67
I 67
 * We avoid recursion to avoid deep kernel stacks.
E 69
I 69
 * Scaled down version of printf(3).
 *
 * Two additional formats:
 *
 * The format %b is supported to decode error registers.
 * Its usage is:
 *
D 73
 *	kprintf("reg=%b\n", regval, "<base><arg>*");
E 73
I 73
D 79
 *	printf("reg=%b\n", regval, "<base><arg>*");
E 79
I 79
D 82
 *	kprintf("reg=%b\n", regval, "<base><arg>*");
E 82
I 82
 *	printf("reg=%b\n", regval, "<base><arg>*");
E 82
E 79
E 73
 *
 * where <base> is the output base expressed as a control character, e.g.
 * \10 gives octal; \20 gives hex.  Each arg is a sequence of characters,
 * the first of which gives the bit number to be inspected (origin 1), and
 * the next characters (up to a control character, i.e. a character <= 32),
 * give the name of the register.  Thus:
 *
D 73
 *	kprintf("reg=%b\n", 3, "\10\2BITTWO\1BITONE\n");
E 73
I 73
D 79
 *	printf("reg=%b\n", 3, "\10\2BITTWO\1BITONE\n");
E 79
I 79
 *	kprintf("reg=%b\n", 3, "\10\2BITTWO\1BITONE\n");
E 79
E 73
 *
 * would produce output:
 *
 *	reg=3<BITTWO,BITONE>
 *
D 79
 * The format %r is supposed to pass an additional format string and argument
 * list recursively.
 * Its usage is:
E 79
I 79
 * The format %r passes an additional format string and argument list
 * recursively.  Its usage is:
E 79
 *
D 76
 * fn(otherstuff, fmt [, arg1, ... ])
 *	char *fmt;
 *	u_int arg1, ...;
 *
E 76
I 76
D 79
 * fn(otherstuff, char *fmt, ...)
E 79
I 79
 * fn(char *fmt, ...)
E 79
 * {
 *	va_list ap;
 *	va_start(ap, fmt);
E 76
D 73
 *	kprintf("prefix: %r, other stuff\n", fmt, ap);
E 73
I 73
D 79
 *	printf("prefix: %r, other stuff\n", fmt, ap);
E 79
I 79
D 82
 *	kprintf("prefix: %r: suffix\n", flags, tp, fmt, ap);
E 82
I 82
 *	printf("prefix: %r: suffix\n", fmt, ap);
E 82
E 79
I 76
 *	va_end(ap);
I 79
 * }
E 79
E 76
 *
 * Space or zero padding and a field width are supported for the numeric
 * formats only.
E 73
E 69
E 67
 */
E 16
D 3
printx(x)
E 3
I 3
D 12
printx(x, trace)
E 3
long x;
E 12
I 12
D 36
printn(n, b, touser)
E 36
I 36
D 62
printn(n, b, flags, ttyp)
E 62
I 62
D 65
printn(n, b, flags, where)
E 65
I 65
D 69
printn(n, b, flags, ttyp)
E 65
E 62
E 36
D 19
	unsigned long n;
E 19
I 19
	u_long n;
E 69
I 69
D 71
static void
E 71
I 71
D 73
void
E 73
I 73
D 74
static void
E 74
I 74
void
E 74
E 73
E 71
D 70
kprintf(fmt, flags, ttyp, ap)
	register char *fmt;
E 70
I 70
D 79
kprintf(fmt, flags, tp, ap)
E 79
I 79
D 82
#ifdef __STDC__
kprintf(const char *fmt, int flags, struct tty *tp, va_list ap, ...)
#else
kprintf(fmt, flags, tp)
E 82
I 82
kprintf(fmt, flags, tp, ap)
E 82
E 79
	register const char *fmt;
E 70
	int flags;
E 69
I 36
D 62
	struct tty *ttyp;
E 62
I 62
D 65
	caddr_t where;
E 65
I 65
D 70
	struct tty *ttyp;
E 70
I 70
	struct tty *tp;
E 70
I 69
	va_list ap;
I 79
D 82
#endif
E 82
E 79
E 69
E 65
E 62
E 36
E 19
E 12
{
D 12
	int i;
E 12
I 12
D 14
	char buf[11];
E 14
I 14
D 69
	char prbuf[11];
E 14
	register char *cp;
E 69
I 69
D 85
	register char *p;
E 85
I 85
	register char *p, *q;
E 85
	register int ch, n;
D 73
	unsigned long ul;
	int lflag, set;
E 73
I 73
	u_long ul;
	int base, lflag, tmp, width;
	char padc;
E 73
E 69
E 12

D 12
	for (i = 0; i < 8; i++)
D 3
		putchar("0123456789ABCDEF"[(x>>((7-i)*4))&0xf]);
E 3
I 3
		putchar("0123456789ABCDEF"[(x>>((7-i)*4))&0xf], trace);
E 3
}

/*
D 10
 * Print an unsigned integer in base b.
E 10
I 10
 * Print an integer in base b.  If the base is ten it is condidered a
 * signed integer otherwise it is treated as unsigned.
E 10
 */
D 3
printn(n, b)
E 3
I 3
printn(n, b, trace)
E 3
D 10
long n;
E 10
I 10
unsigned long n;
E 10
{
D 10
	register long a;
E 10
I 10
	register unsigned long a;
	register long a1 = n;
E 10

D 10
	if (n<0) {	/* shouldn't happen */
E 10
I 10
	if (b == 10 && a1 < 0) {
E 10
D 3
		putchar('-');
E 3
I 3
		putchar('-', trace);
E 3
D 10
		n = -n;
E 10
I 10
		n = -a1;
E 12
I 12
D 50
	if (b == 10 && (int)n < 0) {
D 36
		putchar('-', touser);
E 36
I 36
		putchar('-', flags, ttyp);
E 36
		n = (unsigned)(-(int)n);
E 50
I 50
D 69
	if (b == -10) {
		if ((int)n < 0) {
D 62
			putchar('-', flags, ttyp);
E 62
I 62
D 65
			putchar('-', flags, where);
E 65
I 65
			putchar('-', flags, ttyp);
E 65
E 62
			n = (unsigned)(-(int)n);
E 69
I 69
	for (;;) {
I 73
		padc = ' ';
		width = 0;
E 73
D 75
		while ((ch = *fmt++) != '%') {
E 75
I 75
		while ((ch = *(u_char *)fmt++) != '%') {
E 75
			if (ch == '\0')
				return;
D 70
			putchar(ch, flags, ttyp);
E 70
I 70
			putchar(ch, flags, tp);
E 70
E 69
		}
D 69
		b = -b;
E 50
E 12
E 10
	}
D 12
	if(a = n/b)
D 3
		printn(a, b);
	putchar("0123456789ABCDEF"[(int)(n%b)]);
E 3
I 3
		printn(a, b, trace);
	putchar("0123456789ABCDEF"[(int)(n%b)], trace);
E 12
I 12
D 14
	cp = buf;
E 14
I 14
	cp = prbuf;
E 14
	do {
		*cp++ = "0123456789abcdef"[n%b];
		n /= b;
	} while (n);
	do
D 36
		putchar(*--cp, touser);
E 36
I 36
D 62
		putchar(*--cp, flags, ttyp);
E 62
I 62
D 65
		putchar(*--cp, flags, where);
E 65
I 65
		putchar(*--cp, flags, ttyp);
E 65
E 62
E 36
D 14
	while (cp > buf);
E 14
I 14
	while (cp > prbuf);
E 14
E 12
E 3
}
E 69
I 69
		lflag = 0;
D 75
reswitch:	switch (ch = *fmt++) {
E 75
I 75
reswitch:	switch (ch = *(u_char *)fmt++) {
E 75
I 73
		case '0':
			padc = '0';
			goto reswitch;
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			for (width = 0;; ++fmt) {
				width = width * 10 + ch - '0';
				ch = *fmt;
				if (ch < '0' || ch > '9')
					break;
			}
			goto reswitch;
E 73
		case 'l':
			lflag = 1;
			goto reswitch;
		case 'b':
			ul = va_arg(ap, int);
			p = va_arg(ap, char *);
D 70
			kprintn(ul, *p++);
E 70
I 70
D 73
			kprintn(ul, *p++, flags, tp);
E 73
I 73
D 85
			for (p = ksprintn(ul, *p++, NULL); ch = *p--;)
E 85
I 85
			for (q = ksprintn(ul, *p++, NULL); ch = *q--;)
E 85
				putchar(ch, flags, tp);
E 73
E 70
E 69

D 69
/*
D 4
 * Panic is called on unresolvable
 * fatal errors.
 * It syncs, prints "panic: mesg" and
 * then loops.
E 4
I 4
 * Panic is called on unresolvable fatal errors.
D 16
 * It syncs, prints "panic: mesg", and then reboots.
E 16
I 16
 * It prints "panic: mesg", and then reboots.
 * If we are called twice, then we avoid trying to
 * sync the disks as this often leads to recursive panics.
E 16
E 4
 */
panic(s)
D 16
char *s;
E 16
I 16
	char *s;
E 16
{
I 29
D 30
#if sun
E 30
I 30
D 34
#ifdef sun
E 30
	register int *a5;
#endif
E 34
E 29
I 16
D 27
	int bootopt = panicstr ? RB_AUTOBOOT : RB_AUTOBOOT|RB_NOSYNC;
E 27
I 27
D 52
	int bootopt = RB_AUTOBOOT;
E 52
I 52
	int bootopt = RB_AUTOBOOT | RB_DUMP;
E 69
I 69
			if (!ul)
				break;
E 69
E 52
E 27
E 16
I 12

I 27
D 69
	if (panicstr)
		bootopt |= RB_NOSYNC;
I 29
D 30
#if sun
E 30
I 30
D 31
#ifdef sun
E 31
E 30
D 67
	else {
E 67
I 67
	else
E 67
I 31
		panicstr = s;
D 34
#ifdef sun
E 31
		asm("movl a6, a5");
		traceback(a5, a5);
D 31
	}
E 31
I 31
D 32
		resume(pcbb(u.u_procp));	/* for adb traceback */
E 32
I 32
		/* make sure u area has been initialized before doing resume */
		if (u.u_procp >= proc && u.u_procp < procNPROC &&
		    u.u_procp->p_addr != 0)
			resume(pcbb(u.u_procp));	/* for adb traceback */
E 32
E 31
#endif
E 34
E 29
E 27
E 12
D 31
	panicstr = s;
E 31
I 31
D 67
	}
E 67
E 31
I 21
	printf("panic: %s\n", s);
I 67
#ifdef KGDB
	kgdb_panic();
#endif
E 67
I 53
D 59
#ifdef KDB
E 59
I 59
#ifdef KADB
E 59
	if (boothowto & RB_KDB) {
D 56
		int s = splnet();	/* below kdb pri */
E 56
I 56
		int x = splnet();	/* below kdb pri */
E 56

		setsoftkdb();
D 56
		splx(s);
E 56
I 56
		splx(x);
E 69
I 69
D 73
			for (set = 0; n = *p++;) {
E 73
I 73
			for (tmp = 0; n = *p++;) {
E 73
				if (ul & (1 << (n - 1))) {
D 70
					putchar(set ? ',' : '<', flags, ttyp);
E 70
I 70
D 73
					putchar(set ? ',' : '<', flags, tp);
E 73
I 73
					putchar(tmp ? ',' : '<', flags, tp);
E 73
E 70
					for (; (n = *p) > ' '; ++p)
D 70
						putchar(n, flags, ttyp);
E 70
I 70
						putchar(n, flags, tp);
E 70
D 73
					set = 1;
E 73
I 73
					tmp = 1;
E 73
				} else
D 86
					for (; *p > ' '; ++p);
E 86
I 86
					for (; *p > ' '; ++p)
						continue;
E 86
			}
D 73
			if (set)
E 73
I 73
			if (tmp)
E 73
D 70
				putchar('>', flags, ttyp);
E 70
I 70
				putchar('>', flags, tp);
E 70
			break;
		case 'c':
D 70
			putchar(va_arg(ap, int), flags, ttyp);
E 70
I 70
			putchar(va_arg(ap, int), flags, tp);
E 70
			break;
		case 'r':
			p = va_arg(ap, char *);
D 70
			kprintf(p, flags, ttyp, va_arg(ap, va_list));
E 70
I 70
			kprintf(p, flags, tp, va_arg(ap, va_list));
E 70
			break;
		case 's':
			p = va_arg(ap, char *);
			while (ch = *p++)
D 70
				putchar(ch, flags, ttyp);
E 70
I 70
				putchar(ch, flags, tp);
E 70
			break;
D 73
		case 'D':
			lflag = 1;
			/* FALLTHROUGH */
E 73
		case 'd':
D 73
			ul = lflag ?
			    va_arg(ap, long) : va_arg(ap, int);
E 73
I 73
			ul = lflag ? va_arg(ap, long) : va_arg(ap, int);
E 73
			if ((long)ul < 0) {
D 70
				putchar('-', flags, ttyp);
E 70
I 70
				putchar('-', flags, tp);
E 70
				ul = -(long)ul;
			}
D 70
			kprintn(ul, 10);
E 70
I 70
D 73
			kprintn(ul, 10, flags, tp);
E 70
			break;
		case 'O':
			lflag = 1;
			/* FALLTHROUGH */
E 73
I 73
			base = 10;
			goto number;
E 73
		case 'o':
D 73
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
D 70
			kprintn(ul, 8);
E 70
I 70
			kprintn(ul, 8, flags, tp);
E 70
			break;
		case 'U':
			lflag = 1;
			/* FALLTHROUGH */
E 73
I 73
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 8;
D 76
			goto number;;
E 76
I 76
			goto number;
E 76
E 73
		case 'u':
D 73
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
D 70
			kprintn(ul, 10);
E 70
I 70
			kprintn(ul, 10, flags, tp);
E 70
			break;
		case 'X':
			lflag = 1;
			/* FALLTHROUGH */
E 73
I 73
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 10;
			goto number;
E 73
		case 'x':
D 73
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
D 70
			kprintn(ul, 16);
E 70
I 70
			kprintn(ul, 16, flags, tp);
E 73
I 73
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 16;
number:			p = ksprintn(ul, base, &tmp);
			if (width && (width -= tmp) > 0)
				while (width--)
					putchar(padc, flags, tp);
			while (ch = *p--)
				putchar(ch, flags, tp);
E 73
E 70
			break;
		default:
D 70
			putchar('%', flags, ttyp);
E 70
I 70
			putchar('%', flags, tp);
E 70
			if (lflag)
D 70
				putchar('l', flags, ttyp);
			putchar(ch, flags, ttyp);
E 70
I 70
				putchar('l', flags, tp);
I 73
			/* FALLTHROUGH */
		case '%':
E 73
			putchar(ch, flags, tp);
E 70
		}
E 69
E 56
	}
D 69
#endif
E 53
E 21
D 5
	update();
E 5
D 19
	printf("panic: %s\n", s);
E 19
D 8
	spl0();
E 8
I 8
D 27
	(void) spl0();
E 27
E 8
D 16
	for(;;)
D 4
		;
E 4
I 4
D 5
		boot(RB_PANIC, RB_AUTOBOOT);		/* 0 = automatic */
E 5
I 5
		boot(RB_PANIC, RB_AUTOBOOT);
E 16
I 16
D 52
	boot(RB_PANIC, bootopt);
E 52
I 52
	boot(bootopt);
E 69
I 69
D 72
	va_end(ap);
E 72
E 69
E 52
E 16
E 5
E 4
}

D 69
/*
I 18
 * Warn that a system table is full.
 */
tablefull(tab)
	char *tab;
E 69
I 69
D 73
static void
D 70
kprintn(ul, base)
E 70
I 70
kprintn(ul, base, flags, tp)
E 70
	u_long ul;
D 70
	int base;
E 70
I 70
	int base, flags;
	struct tty *tp;
E 70
E 69
{
I 69
					/* hold a long in base 8 */
D 71
	char *p, buf[(sizeof(long) * NBBY >> 3) + 1];
E 71
I 71
	char *p, buf[(sizeof(long) * NBBY / 3) + 1];
E 71
E 69

D 40
	printf("%s: table is full\n", tab);
E 40
I 40
D 43
	log(KERN_FAIL, "%s: table is full\n", tab);
E 43
I 43
D 69
	log(LOG_ERR, "%s: table is full\n", tab);
E 69
I 69
	p = buf;
	do {
		*p++ = "0123456789abcdef"[ul % base];
	} while (ul /= base);
	do {
D 70
		putchar(*--p);
E 70
I 70
		putchar(*--p, flags, tp);
E 70
	} while (p > buf);
E 69
E 43
E 40
}

E 73
I 33
D 34
#ifdef vax
E 34
E 33
/*
E 18
D 16
 * prdev prints a warning message of the
 * form "mesg on dev x/y".
 * x and y are the major and minor parts of
 * the device argument.
E 16
I 16
D 17
 * Prdev prints a warning message of the form "mesg on dev x/y".
 * x and y are the major and minor parts of the device argument.
 *
 * PRDEV SHOULD COMPUTE AND USE DEVICE NAMES
E 16
 */
prdev(str, dev)
D 12
char *str;
dev_t dev;
E 12
I 12
	char *str;
	dev_t dev;
E 12
{

D 12
	printf("%s on dev %u/%u\n", str, major(dev), minor(dev));
E 12
I 12
	printf("%s on dev %d/%d\n", str, major(dev), minor(dev));
E 12
}

I 16
/*
E 17
D 58
 * Hard error is the preface to plaintive error messages
D 18
 * about failing device transfers.
E 18
I 18
 * about failing disk transfers.
E 18
 */
E 16
D 15
/*
 * deverr prints a diagnostic from
 * a device driver.
 * It prints the device, block number,
 * and an octal word (usually some error
 * status register) passed as argument.
 */
deverror(bp, o1, o2)
D 12
register struct buf *bp;
E 12
I 12
	register struct buf *bp;
E 15
I 15
D 18
harderr(bp)
E 18
I 18
harderr(bp, cp)
E 18
	struct buf *bp;
I 18
	char *cp;
E 18
E 15
E 12
{

D 11
	prdev("err", bp->b_dev);
	printf("bn=%d er=%x,%x\n", bp->b_blkno, o1,o2);
E 11
I 11
D 15
	printf("bn=%d er=%x,%x", bp->b_blkno, o1,o2);
	prdev("", bp->b_dev);
E 15
I 15
D 16
	printf("hard err bn %d ", bp->b_blkno);
E 16
I 16
D 18
	printf("hard err bn%d ", bp->b_blkno);
E 18
I 18
	printf("%s%d%c: hard error sn%d ", cp,
D 42
	    dkunit(bp), 'a'+(minor(bp->b_dev)&07), bp->b_blkno);
E 42
I 42
	    minor(bp->b_dev) >> 3, 'a'+(minor(bp->b_dev)&07), bp->b_blkno);
E 42
E 18
E 16
E 15
E 11
I 3
}
I 33
D 34
#endif
E 34
E 33
I 16

E 16
D 15

E 15
D 12
#ifdef TRACE
dumptrc()
{
	register char *cp;
	register int pos, nch;

	nch = trcprt;
	if (nch < 0 || nch > TRCBUFS)
		nch = TRCBUFS;
	pos = (trcbufp - trcbuf) - nch;
	if (pos < 0)
		if (trcwrap)
			pos += TRCBUFS;
		else {
			nch += pos;
			pos = 0;
		}
	for (cp = &trcbuf[pos]; nch > 0; nch--) {
		putchar(*cp++, 0);
		if (cp >= &trcbuf[TRCBUFS])
			cp = trcbuf;
	}
}
#else
/*ARGSUSED*/
dumptrc(nch)
	int nch;
{

}
#endif

E 12
D 9
char	*msgbufp = msgbuf;	/* Next saved printf character */
E 9
/*
E 58
D 12
 * Print a character on console or in internal trace buffer.
E 12
I 12
D 69
 * Print a character on console or users terminal.
E 12
 * If destination is console then the last MSGBUFS characters
 * are saved in msgbuf for inspection later.
E 69
I 69
 * Print a character on console or users terminal.  If destination is
 * the console then the last MSGBUFS characters are saved in msgbuf for
 * inspection later.
E 69
 */
I 7
D 69
/*ARGSUSED*/
E 69
I 69
static void
E 69
E 7
D 12
putchar(c, trace)
register c;
E 12
I 12
D 36
putchar(c, touser)
E 36
I 36
D 39
putchar(c, flags, ttyp)
E 39
I 39
D 62
putchar(c, flags, tp)
E 62
I 62
D 65
putchar(c, flags, where)
E 65
I 65
D 70
putchar(c, flags, ttyp)
E 70
I 70
putchar(c, flags, tp)
E 70
E 65
E 62
E 39
E 36
	register int c;
I 69
	int flags;
E 69
I 36
D 39
	struct tty *ttyp;
E 39
I 39
D 62
	struct tty *tp;
E 62
I 62
D 65
	caddr_t where;
E 65
I 65
D 70
	struct tty *ttyp;
E 70
I 70
	struct tty *tp;
E 70
E 65
E 62
E 39
E 36
E 12
{
I 66
D 69
	register struct msgbuf *mbp = msgbufp;
E 69
E 66
I 51
D 55
	int startflags = flags;
E 55
I 55
	extern int msgbufmapped;
I 69
D 76
	register struct msgbuf *mbp;
E 76
I 76
D 77
	register struct msgbuf *mbp = msgbufp;
E 77
I 77
	register struct msgbuf *mbp;
E 77
E 76
E 69
E 55
E 51
I 39
D 44
	extern struct tty cons;
E 44
E 39
D 7
	register s, timo;
E 7

I 51
	if (panicstr)
D 69
		constty = 0;
E 69
I 69
		constty = NULL;
E 69
D 62
	if ((flags & TOCONS) && tp == 0 && constty) {
		tp = constty;
E 62
I 62
D 65
	if ((flags & TOCONS) && where == 0 && constty) {
		where = (caddr_t)constty;
E 65
I 65
D 70
	if ((flags & TOCONS) && ttyp == NULL && constty) {
		ttyp = constty;
E 70
I 70
	if ((flags & TOCONS) && tp == NULL && constty) {
		tp = constty;
E 70
E 65
E 62
		flags |= TOTTY;
	}
E 51
I 49
	if ((flags & TOCONS) && panicstr == 0 && tp == 0 && constty) {
		tp = constty;
		flags |= TOTTY;
	}
E 49
I 11
D 12
	if (trace == 2) {
		register struct tty *tp;
		register s;
E 12
I 12
D 36
	if (touser) {
		register struct tty *tp = u.u_ttyp;
E 36
I 36
D 62
	if (flags & TOTTY) {
D 39
		register struct tty *tp = ttyp;
E 36
E 12

E 39
I 39
D 44
		if (tp == (struct tty *)NULL && (flags & TOCONS) == 0)
			tp = &cons;
E 39
D 12
		if ((tp = u.u_ttyp) && (tp->t_state&CARR_ON)) {
			s = spl7();
E 12
I 12
D 26
		if (tp && (tp->t_state&CARR_ON)) {
E 26
I 26
D 36
		if (tp && (tp->t_state&TS_CARR_ON)) {
E 36
I 36
		if (tp && (tp->t_state & TS_CARR_ON)) {
E 36
E 26
			register s = spl6();
E 44
I 44
		register s = spltty();

		if (tp && (tp->t_state & (TS_CARR_ON | TS_ISOPEN)) ==
		    (TS_CARR_ON | TS_ISOPEN)) {
E 44
			if (c == '\n')
D 25
				ttyoutput('\r', tp);
E 12
			ttyoutput(c, tp);
E 25
I 25
				(void) ttyoutput('\r', tp);
			(void) ttyoutput(c, tp);
E 25
			ttstart(tp);
D 44
			splx(s);
E 44
D 49
D 51
		}
E 51
I 51
		} else if ((flags & TOCONS) && tp == constty)
			constty = 0;
E 51
E 49
I 49
			flags &= ~TOCONS;
		} else if ((flags & TOCONS) && tp == constty)
			constty = 0;
E 49
I 44
		splx(s);
E 44
D 36
		return;
E 36
	}
E 62
I 62
D 65
	if ((flags & TOTTY) && where && tputchar(c, (struct tty *)where) < 0 &&
	    (flags & TOCONS) && (struct tty *)where == constty)
E 65
I 65
D 70
	if ((flags & TOTTY) && ttyp && tputchar(c, ttyp) < 0 &&
	    (flags & TOCONS) && ttyp == constty)
E 70
I 70
	if ((flags & TOTTY) && tp && tputchar(c, tp) < 0 &&
	    (flags & TOCONS) && tp == constty)
E 70
E 65
D 69
		constty = 0;
E 62
I 29
D 30
#if vax
E 30
I 30
D 34
#ifdef vax
E 30
E 29
I 28
#include "../vax/mtpr.h"		/* XXX */
E 28
E 11
D 12
#ifdef TRACE
	if (trace) {
		*trcbufp++ = c;
		if (trcbufp >= &trcbuf[TRCBUFS]) {
			trcbufp = trcbuf;
			trcwrap = 1;
		}
		return;
	}
#endif
E 12
D 13
	if (c != '\0' && c != '\r' && c != 0177) {
E 13
I 13
D 29
	if (c != '\0' && c != '\r' && c != 0177 && mfpr(MAPEN)) {
E 29
I 29
#endif
E 34
D 36
	if (c != '\0' && c != '\r' && c != 0177
E 36
I 36
D 50
	if ((flags & TOLOG) && c != '\0' && c != '\r' && c != 0177
E 36
D 30
#if vax
E 30
I 30
#ifdef vax
E 30
	    && mfpr(MAPEN)
#endif
	    ) {
E 50
I 50
D 55
	/*
	 * Can send to log only after memory management enabled:
	 * this has happened by the time maxmem is set.
	 */
	if ((flags & TOLOG) && c != '\0' && c != '\r' && c != 0177 && maxmem) {
E 55
I 55
	if ((flags & TOLOG) && c != '\0' && c != '\r' && c != 0177 &&
	    msgbufmapped) {
E 69
I 69
		constty = NULL;
	if ((flags & TOLOG) &&
	    c != '\0' && c != '\r' && c != 0177 && msgbufmapped) {
I 77
		mbp = msgbufp;
E 77
D 76
 		mbp = msgbufp;
E 76
E 69
E 55
E 50
E 29
E 13
D 9
		*msgbufp++ = c;
		if (msgbufp >= &msgbuf[MSGBUFS])
			msgbufp = msgbuf;
E 9
I 9
D 66
		if (msgbuf.msg_magic != MSG_MAGIC) {
E 66
I 66
		if (mbp->msg_magic != MSG_MAGIC) {
E 66
I 32
D 76
			register int i;

E 76
I 76
			bzero((caddr_t)mbp, sizeof(*mbp));
E 76
E 32
D 36
			msgbuf.msg_bufx = 0;
E 36
D 66
			msgbuf.msg_magic = MSG_MAGIC;
I 36
			msgbuf.msg_bufx = msgbuf.msg_bufr = 0;
E 66
I 66
			mbp->msg_magic = MSG_MAGIC;
D 76
			mbp->msg_bufx = mbp->msg_bufr = 0;
E 66
E 36
I 32
D 69
			for (i=0; i < MSG_BSIZE; i++)
E 69
I 69
			for (i = 0; i < MSG_BSIZE; i++)
E 69
D 66
				msgbuf.msg_bufc[i] = 0;
E 66
I 66
				mbp->msg_bufc[i] = 0;
E 76
E 66
E 32
		}
I 47
D 66
		msgbuf.msg_bufc[msgbuf.msg_bufx++] = c;
E 47
		if (msgbuf.msg_bufx < 0 || msgbuf.msg_bufx >= MSG_BSIZE)
			msgbuf.msg_bufx = 0;
E 66
I 66
		mbp->msg_bufc[mbp->msg_bufx++] = c;
		if (mbp->msg_bufx < 0 || mbp->msg_bufx >= MSG_BSIZE)
			mbp->msg_bufx = 0;
I 91
		/* If the buffer is full, keep the most recent data. */
		if (mbp->msg_bufr == mbp->msg_bufx) {
			if (++mbp->msg_bufr >= MSG_BSIZE)
				mbp->msg_bufr = 0;
		}
E 91
E 66
D 47
		msgbuf.msg_bufc[msgbuf.msg_bufx++] = c;
E 47
E 9
	}
D 36
	if (c == 0)
		return;
	cnputc(c);
E 36
I 36
D 51
	if ((flags & TOCONS) && c != '\0')
D 49
		cnputc(c);
E 51
I 51
D 69
	if ((flags & TOCONS) && constty == 0 && c != '\0')
E 69
I 69
	if ((flags & TOCONS) && constty == NULL && c != '\0')
E 69
		(*v_putc)(c);
I 73
}

/*
 * Scaled down version of sprintf(3).
 */
#ifdef __STDC__
D 75
sprintf(char *buf, const char *fmt, ...)
E 75
I 75
sprintf(char *buf, const char *cfmt, ...)
E 75
#else
D 75
sprintf(buf, fmt /*, va_alist */)
	char *buf, *fmt;
E 75
I 75
D 80
sprintf(buf, cfmt /*, va_alist */)
E 80
I 80
sprintf(buf, cfmt, va_alist)
E 80
	char *buf, *cfmt;
E 75
#endif
{
I 75
	register const char *fmt = cfmt;
E 75
	register char *p, *bp;
	register int ch, base;
	u_long ul;
	int lflag;
	va_list ap;

D 75
	va_start(ap, fmt);
	for (bp = buf;;) {
		while ((ch = *fmt++) != '%')
E 75
I 75
	va_start(ap, cfmt);
	for (bp = buf; ; ) {
		while ((ch = *(u_char *)fmt++) != '%')
E 75
			if ((*bp++ = ch) == '\0')
D 75
				return((bp - buf) - 1);
E 75
I 75
				return ((bp - buf) - 1);

E 75
		lflag = 0;
D 75
reswitch:	switch (ch = *fmt++) {
E 75
I 75
reswitch:	switch (ch = *(u_char *)fmt++) {
E 75
		case 'l':
			lflag = 1;
			goto reswitch;
		case 'c':
			*bp++ = va_arg(ap, int);
			break;
		case 's':
			p = va_arg(ap, char *);
D 75
			while (*bp++ = *p++);
E 75
I 75
			while (*bp++ = *p++)
D 82
				;
E 82
I 82
				continue;
E 82
E 75
			--bp;
			break;
		case 'd':
			ul = lflag ? va_arg(ap, long) : va_arg(ap, int);
			if ((long)ul < 0) {
				*bp++ = '-';
				ul = -(long)ul;
			}
			base = 10;
			goto number;
			break;
		case 'o':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 8;
			goto number;
			break;
		case 'u':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 10;
			goto number;
			break;
		case 'x':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 16;
number:			for (p = ksprintn(ul, base, NULL); ch = *p--;)
				*bp++ = ch;
			break;
		default:
			*bp++ = '%';
			if (lflag)
				*bp++ = 'l';
			/* FALLTHROUGH */
		case '%':
			*bp++ = ch;
		}
	}
	va_end(ap);
}

/*
 * Put a number (base <= 16) in a buffer in reverse order; return an
 * optional length and a pointer to the NULL terminated (preceded?)
 * buffer.
 */
static char *
ksprintn(ul, base, lenp)
	register u_long ul;
	register int base, *lenp;
{					/* A long in base 8, plus NULL. */
	static char buf[sizeof(long) * NBBY / 3 + 2];
	register char *p;

	p = buf;
	do {
		*++p = "0123456789abcdef"[ul % base];
	} while (ul /= base);
	if (lenp)
		*lenp = p - buf;
D 75
	return(p);
E 75
I 75
	return (p);
E 75
E 73
E 51
E 49
I 49
		(*v_console)(c);
E 49
E 36
I 11
D 12
}

/*
 * print to the current users terminal,
 * guarantee not to sleep (so can be called by intr routine)
 * no watermark checking - so no verbose messages
 */

/*VARARGS1*/
uprintf(fmt, x1)
char	*fmt;
unsigned x1;
{
	prf(fmt, &x1, 2);
E 12
E 11
E 3
}
E 1
