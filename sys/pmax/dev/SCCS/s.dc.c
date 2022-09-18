h21454
s 00009/00004/00958
d D 8.5 95/06/02 17:26:11 ralph 18 17
c final changes for pmax 4.4-Lite II release
e
s 00013/00013/00949
d D 8.4 94/07/14 20:12:20 mckusick 17 16
c fixes sign extension bug with sending 8 bit chars (from ralph)
e
s 00109/00046/00853
d D 8.3 94/07/03 14:44:58 mckusick 16 15
c add H/W flow control (from Ralph)
e
s 00003/00005/00896
d D 8.2 93/11/30 16:14:34 mckusick 15 14
c update from Ralph
e
s 00002/00002/00899
d D 8.1 93/06/10 22:38:12 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00897
d D 7.13 93/04/05 21:36:05 ralph 13 12
c fix intermitent bug which sends chars to keyboard instead of port 3.
e
s 00012/00002/00888
d D 7.12 92/12/20 11:36:35 ralph 12 11
c changes from Rick Macklem
e
s 00127/00688/00763
d D 7.11 92/11/15 15:49:00 ralph 11 10
c changes for maxine from Rick Macklem.
e
s 00002/00002/01449
d D 7.10 92/10/11 11:24:36 bostic 10 9
c use pmax as top directory, not mips
e
s 00015/00015/01436
d D 7.9 92/10/11 11:13:28 bostic 9 8
c make kernel includes standard
e
s 00001/00001/01450
d D 7.8 92/09/13 11:37:33 ralph 8 7
c fix gcc2 warning
e
s 00007/00005/01444
d D 7.7 92/07/27 21:17:38 ralph 7 6
c fix gcc type warnings
e
s 00025/00011/01424
d D 7.6 92/06/20 12:17:08 ralph 6 5
c fix arguments to functions to include proc 'p'.
e
s 00020/00018/01415
d D 7.5 92/03/07 09:49:30 ralph 5 4
c added support for more than one X driver.
e
s 00004/00001/01429
d D 7.4 92/02/29 17:33:36 ralph 4 3
c fix function return type to void
e
s 00287/00176/01143
d D 7.3 92/02/29 10:56:28 ralph 3 2
c changes to support DS5000
e
s 00002/00010/01317
d D 7.2 92/02/26 10:34:21 mckusick 2 1
c new select model
e
s 01327/00000/00000
d D 7.1 92/01/07 18:29:17 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
D 11
/*
 * Copyright (c) 1992 Regents of the University of California.
E 11
I 11
/*-
D 14
 * Copyright (c) 1992 The Regents of the University of California.
E 11
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
D 11
 * Ralph Campbell.
I 3
 *	@(#)dz.c	7.9 (Berkeley) 6/28/90
 */

/*
 *  devDC7085.c --
E 11
I 11
 * Ralph Campbell and Rick Macklem.
E 11
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 11
 *
E 11
I 11
 */

/*
E 11
 * devDC7085.c --
 *
 *     	This file contains machine-dependent routines that handle the
 *	output queue for the serial lines.
 *
 *	Copyright (C) 1989 Digital Equipment Corporation.
 *	Permission to use, copy, modify, and distribute this software and
 *	its documentation for any purpose and without fee is hereby granted,
 *	provided that the above copyright notice appears in all copies.
 *	Digital Equipment Corporation makes no representations about the
 *	suitability of this software for any purpose.  It is provided "as is"
 *	without express or implied warranty.
 *
 * from: $Header: /sprite/src/kernel/dev/ds3100.md/RCS/devDC7085.c,
 *	v 1.4 89/08/29 11:55:30 nelson Exp $ SPRITE (DECWRL)";
 */

D 11
#include "dc.h"
E 11
I 11
#include <dc.h>
E 11
#if NDC > 0
/*
 * DC7085 (DZ-11 look alike) Driver
 */
D 9
#include "param.h"
#include "systm.h"
#include "ioctl.h"
#include "tty.h"
#include "proc.h"
#include "map.h"
#include "buf.h"
#include "conf.h"
#include "file.h"
#include "uio.h"
#include "kernel.h"
#include "syslog.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/proc.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
E 9

D 9
#include "machine/dc7085cons.h"
E 9
I 9
#include <machine/dc7085cons.h>
I 11
#include <machine/pmioctl.h>
E 11
E 9

I 11
#include <pmax/pmax/pmaxtype.h>
#include <pmax/pmax/cons.h>

E 11
D 9
#include "device.h"
#include "pdma.h"
E 9
I 9
D 10
#include <mips/dev/device.h>
#include <mips/dev/pdma.h>
E 10
I 10
#include <pmax/dev/device.h>
#include <pmax/dev/pdma.h>
I 11
#include <pmax/dev/fbreg.h>
E 11
E 10
E 9

I 11
extern int pmax_boardtype;
extern struct consdev cn_tab;

E 11
/*
 * Driver information for auto-configuration stuff.
 */
int	dcprobe();
I 3
void	dcintr();
E 3
struct	driver dcdriver = {
D 3
	"dc", dcprobe, 0, 0,
E 3
I 3
	"dc", dcprobe, 0, 0, dcintr,
E 3
};

#define	NDCLINE 	(NDC*4)

D 4
extern int dcstart(), dcxint();
E 4
I 4
D 6
extern void dcstart();
extern void dcxint();
E 4
extern int ttrstrt();
E 6
I 6
D 11
extern void dcstart __P((struct tty *));
extern void dcxint __P((struct tty *));
E 11
I 11
void dcstart	__P((struct tty *));
void dcxint	__P((struct tty *));
void dcPutc	__P((dev_t, int));
void dcscan	__P((void *));
E 11
D 8
extern void ttrstrt __P((struct tty *));
E 8
I 8
extern void ttrstrt __P((void *));
I 11
int dcGetc	__P((dev_t));
int dcparam	__P((struct tty *, struct termios *));
D 13
extern void KBDReset	__P((dev_t, void (*)()));
extern void MouseInit	__P((dev_t, void (*)(), int (*)()));
E 13
E 11
E 8
E 6

struct	tty dc_tty[NDCLINE];
int	dc_cnt = NDCLINE;
D 5
int	dcDivertXInput;		/* true if diverting KBD input to X */
E 5
I 5
void	(*dcDivertXInput)();	/* X windows keyboard input routine */
void	(*dcMouseEvent)();	/* X windows mouse motion event routine */
void	(*dcMouseButtons)();	/* X windows mouse buttons event routine */
E 5
#ifdef DEBUG
int	debugChar;
#endif

I 6
D 7
static void dcscan __P((void));
E 7
I 7
D 11
static void dcscan __P((void *));
E 7
static int dcMapChar __P((int));
static void dcKBDReset __P((void));
static void MouseInit __P((void));

E 11
E 6
/*
 * Software copy of brk register since it isn't readable
 */
int	dc_brk[NDC];
char	dcsoftCAR[NDC];		/* mask of dc's with carrier on (DSR) */

/*
 * The DC7085 doesn't interrupt on carrier transitions, so
 * we have to use a timer to watch it.
 */
int	dc_timer;		/* true if timer started */

/*
 * Pdma structures for fast output code
 */
struct	pdma dcpdma[NDCLINE];

struct speedtab dcspeedtab[] = {
	0,	0,
	50,	LPR_B50,
	75,	LPR_B75,
	110,	LPR_B110,
	134,	LPR_B134,
	150,	LPR_B150,
	300,	LPR_B300,
	600,	LPR_B600,
	1200,	LPR_B1200,
	1800,	LPR_B1800,
	2400,	LPR_B2400,
	4800,	LPR_B4800,
	9600,	LPR_B9600,
I 3
D 11
#ifdef DS5000
E 11
	19200,	LPR_B19200,
D 11
#endif
E 11
E 3
	-1,	-1
};

#ifndef	PORTSELECTOR
#define	ISPEED	TTYDEF_SPEED
#define	LFLAG	TTYDEF_LFLAG
#else
#define	ISPEED	B4800
#define	LFLAG	(TTYDEF_LFLAG & ~ECHO)
#endif

/*
D 11
 * Ascii values of command keys.
 */
#define KBD_TAB		'\t'
#define KBD_DEL		127
#define KBD_RET		'\r'

/*
 *  Define "hardware-independent" codes for the control, shift, meta and
 *  function keys.  Codes start after the last 7-bit ASCII code (127)
 *  and are assigned in an arbitrary order.
 */
#define KBD_NOKEY	128

#define KBD_F1		201
#define KBD_F2		202
#define KBD_F3		203
#define KBD_F4		204
#define KBD_F5		205
#define KBD_F6		206
#define KBD_F7		207
#define KBD_F8		208
#define KBD_F9		209
#define KBD_F10		210
#define KBD_F11		211
#define KBD_F12		212
#define KBD_F13		213
#define KBD_F14		214
#define KBD_HELP	215
#define KBD_DO		216
#define KBD_F17		217
#define KBD_F18		218
#define KBD_F19		219
#define KBD_F20		220

#define KBD_FIND	221
#define KBD_INSERT	222
#define KBD_REMOVE	223
#define KBD_SELECT	224
#define KBD_PREVIOUS	225
#define KBD_NEXT	226

#define KBD_KP_ENTER	227
#define KBD_KP_F1	228
#define KBD_KP_F2	229
#define KBD_KP_F3	230
#define KBD_KP_F4	231
#define KBD_LEFT	232
#define KBD_RIGHT	233
#define KBD_DOWN	234
#define KBD_UP		235

#define KBD_CONTROL	236
#define KBD_SHIFT	237
#define KBD_CAPSLOCK	238
#define KBD_ALTERNATE	239

/*
 * Keyboard to Ascii, unshifted.
 */
static unsigned char unshiftedAscii[] = {
/*  0 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/*  4 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/*  8 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/*  c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 10 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 14 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 18 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 1c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 20 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 24 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 28 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 2c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 30 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 34 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 38 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 3c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 40 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 44 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 48 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 4c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 50 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 54 */ KBD_NOKEY,	KBD_NOKEY,	KBD_F1,		KBD_F2,
/* 58 */ KBD_F3,	KBD_F4,		KBD_F5,		KBD_NOKEY,
/* 5c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 60 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 64 */ KBD_F6,	KBD_F7,		KBD_F8,		KBD_F9,
/* 68 */ KBD_F10,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 6c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 70 */ KBD_NOKEY,	'\033',		KBD_F12,	KBD_F13,
/* 74 */ KBD_F14,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 78 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 7c */ KBD_HELP,	KBD_DO,		KBD_NOKEY,	KBD_NOKEY,
/* 80 */ KBD_F17,	KBD_F18,	KBD_F19,	KBD_F20,
/* 84 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 88 */ KBD_NOKEY,	KBD_NOKEY,	KBD_FIND,	KBD_INSERT,
/* 8c */ KBD_REMOVE,	KBD_SELECT,	KBD_PREVIOUS,	KBD_NEXT,
/* 90 */ KBD_NOKEY,	KBD_NOKEY,	'0',		KBD_NOKEY,
/* 94 */ '.',		KBD_KP_ENTER,	'1',		'2',
/* 98 */ '3',		'4',		'5',		'6',
/* 9c */ ',',		'7',		'8',		'9',
/* a0 */ '-',		KBD_KP_F1,	KBD_KP_F2,	KBD_KP_F3,
/* a4 */ KBD_KP_F4,	KBD_NOKEY,	KBD_NOKEY,	KBD_LEFT,
/* a8 */ KBD_RIGHT,	KBD_DOWN, 	KBD_UP,		KBD_NOKEY,
/* ac */ KBD_NOKEY,	KBD_NOKEY,	KBD_SHIFT,	KBD_CONTROL,
/* b0 */ KBD_CAPSLOCK,	KBD_ALTERNATE,	KBD_NOKEY,	KBD_NOKEY,
/* b4 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* b8 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* bc */ KBD_DEL,	KBD_RET,	KBD_TAB,	'`',
/* c0 */ '1',		'q',		'a',		'z',
/* c4 */ KBD_NOKEY,	'2',		'w',		's',
/* c8 */ 'x',		'<',		KBD_NOKEY,	'3',
/* cc */ 'e',		'd',		'c',		KBD_NOKEY,
/* d0 */ '4',		'r',		'f',		'v',
/* d4 */ ' ',		KBD_NOKEY,	'5',		't',
/* d8 */ 'g',		'b',		KBD_NOKEY,	'6',
/* dc */ 'y',		'h',		'n',		KBD_NOKEY,
/* e0 */ '7',		'u',		'j',		'm',
/* e4 */ KBD_NOKEY,	'8',		'i',		'k',
/* e8 */ ',',		KBD_NOKEY,	'9',		'o',
/* ec */ 'l',		'.',		KBD_NOKEY,	'0',
/* f0 */ 'p',		KBD_NOKEY,	';',		'/',
/* f4 */ KBD_NOKEY,	'=',		']',		'\\',
/* f8 */ KBD_NOKEY,	'-',		'[',		'\'',
/* fc */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
};

/*
 * Keyboard to Ascii, shifted.
 */
static unsigned char shiftedAscii[] = {
/*  0 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/*  4 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/*  8 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/*  c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 10 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 14 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 18 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 1c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 20 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 24 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 28 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 2c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 30 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 34 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 38 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 3c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 40 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 44 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 48 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 4c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 50 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 54 */ KBD_NOKEY,	KBD_NOKEY,	KBD_F1,		KBD_F2,
/* 58 */ KBD_F3,	KBD_F4,		KBD_F5,		KBD_NOKEY,
/* 5c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 60 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 64 */ KBD_F6,	KBD_F7,		KBD_F8,		KBD_F9,
/* 68 */ KBD_F10,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 6c */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 70 */ KBD_NOKEY,	KBD_F11,	KBD_F12,	KBD_F13,
/* 74 */ KBD_F14,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 78 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 7c */ KBD_HELP,	KBD_DO,		KBD_NOKEY,	KBD_NOKEY,
/* 80 */ KBD_F17,	KBD_F18,	KBD_F19,	KBD_F20,
/* 84 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* 88 */ KBD_NOKEY,	KBD_NOKEY,	KBD_FIND,	KBD_INSERT,
/* 8c */ KBD_REMOVE,	KBD_SELECT,	KBD_PREVIOUS,	KBD_NEXT,
/* 90 */ KBD_NOKEY,	KBD_NOKEY,	'0',		KBD_NOKEY,
/* 94 */ '.',		KBD_KP_ENTER,	'1',		'2',
/* 98 */ '3',		'4',		'5',		'6',
/* 9c */ ',',		'7',		'8',		'9',
/* a0 */ '-',		KBD_KP_F1,	KBD_KP_F2,	KBD_KP_F3,
/* a4 */ KBD_KP_F4,	KBD_NOKEY,	KBD_NOKEY,	KBD_LEFT,
/* a8 */ KBD_RIGHT,	KBD_DOWN, 	KBD_UP,		KBD_NOKEY,
/* ac */ KBD_NOKEY,	KBD_NOKEY,	KBD_SHIFT,	KBD_CONTROL,
/* b0 */ KBD_CAPSLOCK,	KBD_ALTERNATE,	KBD_NOKEY,	KBD_NOKEY,
/* b4 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* b8 */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
/* bc */ KBD_DEL,	KBD_RET,	KBD_TAB,	'~',
/* c0 */ '!',		'q',		'a',		'z',
/* c4 */ KBD_NOKEY,	'@',		'w',		's',
/* c8 */ 'x',		'>',		KBD_NOKEY,	'#',
/* cc */ 'e',		'd',		'c',		KBD_NOKEY,
/* d0 */ '$',		'r',		'f',		'v',
/* d4 */ ' ',		KBD_NOKEY,	'%',		't',
/* d8 */ 'g',		'b',		KBD_NOKEY,	'^',
/* dc */ 'y',		'h',		'n',		KBD_NOKEY,
/* e0 */ '&',		'u',		'j',		'm',
/* e4 */ KBD_NOKEY,	'*',		'i',		'k',
/* e8 */ '<',		KBD_NOKEY,	'(',		'o',
/* ec */ 'l',		'>',		KBD_NOKEY,	')',
/* f0 */ 'p',		KBD_NOKEY,	':',		'?',
/* f4 */ KBD_NOKEY,	'+',		'}',		'|',
/* f8 */ KBD_NOKEY,	'_',		'{',		'"',
/* fc */ KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,	KBD_NOKEY,
};

/* 
 * Keyboard initialization string.
 */
static u_char kbdInitString[] = {
	LK_LED_ENABLE, LED_ALL,		/* show we are resetting keyboard */
	LK_DEFAULTS,
	LK_CMD_MODE(LK_AUTODOWN, 1), 
	LK_CMD_MODE(LK_AUTODOWN, 2), 
	LK_CMD_MODE(LK_AUTODOWN, 3), 
	LK_CMD_MODE(LK_DOWN, 4),	/* could also be LK_AUTODOWN */
	LK_CMD_MODE(LK_UPDOWN, 5),   
	LK_CMD_MODE(LK_UPDOWN, 6),   
	LK_CMD_MODE(LK_AUTODOWN, 7), 
	LK_CMD_MODE(LK_AUTODOWN, 8), 
	LK_CMD_MODE(LK_AUTODOWN, 9), 
	LK_CMD_MODE(LK_AUTODOWN, 10), 
	LK_CMD_MODE(LK_AUTODOWN, 11), 
	LK_CMD_MODE(LK_AUTODOWN, 12), 
	LK_CMD_MODE(LK_DOWN, 13), 
	LK_CMD_MODE(LK_AUTODOWN, 14),
	LK_AR_ENABLE,			/* we want autorepeat by default */
	LK_CL_ENABLE, 0x83,		/* keyclick, volume */
	LK_KBD_ENABLE,			/* the keyboard itself */
	LK_BELL_ENABLE, 0x83,		/* keyboard bell, volume */
	LK_LED_DISABLE, LED_ALL,	/* clear keyboard leds */
};

/*
E 11
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
dcprobe(cp)
	register struct pmax_ctlr *cp;
{
	register dcregs *dcaddr;
	register struct pdma *pdp;
	register struct tty *tp;
	register int cntr;
I 11
	int s;
E 11
D 6
	extern dcscan();
	extern void dcKBDReset();
	extern void MouseInit();
E 6

	if (cp->pmax_unit >= NDC)
		return (0);
	if (badaddr(cp->pmax_addr, 2))
		return (0);

I 12
	/*
	 * For a remote console, wait a while for previous output to
	 * complete.
	 */
	if (major(cn_tab.cn_dev) == DCDEV && cp->pmax_unit == 0 &&
		cn_tab.cn_screen == 0)
		DELAY(10000);

E 12
	/* reset chip */
	dcaddr = (dcregs *)cp->pmax_addr;
	dcaddr->dc_csr = CSR_CLR;
	MachEmptyWriteBuffer();
	while (dcaddr->dc_csr & CSR_CLR)
		;
	dcaddr->dc_csr = CSR_MSE | CSR_TIE | CSR_RIE;

	/* init pseudo DMA structures */
	pdp = &dcpdma[cp->pmax_unit * 4];
	tp = &dc_tty[cp->pmax_unit * 4];
	for (cntr = 0; cntr < 4; cntr++) {
D 11
		pdp->p_addr = dcaddr;
E 11
I 11
		pdp->p_addr = (void *)dcaddr;
E 11
		pdp->p_arg = (int)tp;
		pdp->p_fcn = dcxint;
D 15
		tp->t_addr = (caddr_t)pdp;
E 15
		pdp++, tp++;
	}
	dcsoftCAR[cp->pmax_unit] = cp->pmax_flags | 0xB;

	if (dc_timer == 0) {
		dc_timer = 1;
D 7
		timeout(dcscan, (caddr_t)0, hz);
E 7
I 7
		timeout(dcscan, (void *)0, hz);
E 7
	}
D 3
	printf("dc%d at nexus0 csr 0x%x\n", cp->pmax_unit, cp->pmax_addr);
E 3
I 3
D 12
	printf("dc%d at nexus0 csr 0x%x priority %d\n",
		cp->pmax_unit, cp->pmax_addr, cp->pmax_pri);
E 12
E 3
D 11
	if (cp->pmax_unit == 0) {
		int s;
E 11

D 11
		s = spltty();
		dcaddr->dc_lpr = LPR_RXENAB | LPR_B4800 | LPR_8_BIT_CHAR |
			KBD_PORT;
		dcaddr->dc_lpr = LPR_RXENAB | LPR_B4800 | LPR_OPAR |
			LPR_PARENB | LPR_8_BIT_CHAR | MOUSE_PORT;
		MachEmptyWriteBuffer();
		dcKBDReset();
		MouseInit();
		splx(s);
E 11
I 11
	/*
	 * Special handling for consoles.
	 */
	if (cp->pmax_unit == 0) {
		if (cn_tab.cn_screen) {
			s = spltty();
			dcaddr->dc_lpr = LPR_RXENAB | LPR_8_BIT_CHAR |
				LPR_B4800 | DCKBD_PORT;
I 13
			MachEmptyWriteBuffer();
E 13
			dcaddr->dc_lpr = LPR_RXENAB | LPR_B4800 | LPR_OPAR |
				LPR_PARENB | LPR_8_BIT_CHAR | DCMOUSE_PORT;
			MachEmptyWriteBuffer();
I 12
			DELAY(1000);
E 12
			KBDReset(makedev(DCDEV, DCKBD_PORT), dcPutc);
			MouseInit(makedev(DCDEV, DCMOUSE_PORT), dcPutc, dcGetc);
			splx(s);
		} else if (major(cn_tab.cn_dev) == DCDEV) {
			s = spltty();
			dcaddr->dc_lpr = LPR_RXENAB | LPR_8_BIT_CHAR |
				LPR_B9600 | minor(cn_tab.cn_dev);
			MachEmptyWriteBuffer();
I 12
			DELAY(1000);
E 12
			cn_tab.cn_disabled = 0;
			splx(s);
		}
E 11
	}
I 12
	printf("dc%d at nexus0 csr 0x%x priority %d\n",
		cp->pmax_unit, cp->pmax_addr, cp->pmax_pri);
E 12
	return (1);
}

D 6
dcopen(dev, flag)
E 6
I 6
dcopen(dev, flag, mode, p)
E 6
	dev_t dev;
I 6
	int flag, mode;
	struct proc *p;
E 6
{
	register struct tty *tp;
	register int unit;
	int s, error = 0;
D 11
	extern int dcparam();
E 11

	unit = minor(dev);
D 11
	if (unit >= dc_cnt || dcpdma[unit].p_addr == 0)
E 11
I 11
	if (unit >= dc_cnt || dcpdma[unit].p_addr == (void *)0)
E 11
		return (ENXIO);
	tp = &dc_tty[unit];
D 15
	tp->t_addr = (caddr_t)&dcpdma[unit];
E 15
	tp->t_oproc = dcstart;
	tp->t_param = dcparam;
	tp->t_dev = dev;
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_state |= TS_WOPEN;
		ttychars(tp);
#ifndef PORTSELECTOR
		if (tp->t_ispeed == 0) {
#endif
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
			tp->t_cflag = TTYDEF_CFLAG;
			tp->t_lflag = LFLAG;
			tp->t_ispeed = tp->t_ospeed = ISPEED;
#ifdef PORTSELECTOR
			tp->t_cflag |= HUPCL;
#else
		}
#endif
		(void) dcparam(tp, &tp->t_termios);
		ttsetwater(tp);
	} else if ((tp->t_state & TS_XCLUDE) && curproc->p_ucred->cr_uid != 0)
		return (EBUSY);
D 16
	(void) dcmctl(dev, DML_DTR, DMSET);
E 16
I 16
	(void) dcmctl(dev, DML_DTR | DML_RTS, DMSET);
I 18
	if ((dcsoftCAR[unit >> 2] & (1 << (unit & 03))) ||
	    (dcmctl(dev, 0, DMGET) & DML_CAR))
		tp->t_state |= TS_CARR_ON;
E 18
E 16
	s = spltty();
	while (!(flag & O_NONBLOCK) && !(tp->t_cflag & CLOCAL) &&
	       !(tp->t_state & TS_CARR_ON)) {
		tp->t_state |= TS_WOPEN;
		if (error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
		    ttopen, 0))
			break;
	}
	splx(s);
	if (error)
		return (error);
	return ((*linesw[tp->t_line].l_open)(dev, tp));
}

/*ARGSUSED*/
D 6
dcclose(dev, flag)
E 6
I 6
dcclose(dev, flag, mode, p)
E 6
	dev_t dev;
I 6
	int flag, mode;
	struct proc *p;
E 6
{
	register struct tty *tp;
	register int unit, bit;
I 18
	int s;
E 18

	unit = minor(dev);
	tp = &dc_tty[unit];
	bit = 1 << ((unit & 03) + 8);
I 18
	s = spltty();
	/* turn off the break bit if it is set */
E 18
	if (dc_brk[unit >> 2] & bit) {
		dc_brk[unit >> 2] &= ~bit;
		ttyoutput(0, tp);
	}
I 18
	splx(s);
E 18
D 6
	(*linesw[tp->t_line].l_close)(tp);
E 6
I 6
	(*linesw[tp->t_line].l_close)(tp, flag);
E 6
	if ((tp->t_cflag & HUPCL) || (tp->t_state & TS_WOPEN) ||
	    !(tp->t_state & TS_ISOPEN))
		(void) dcmctl(dev, 0, DMSET);
	return (ttyclose(tp));
}

dcread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp;

	tp = &dc_tty[minor(dev)];
I 16
	if ((tp->t_cflag & CRTS_IFLOW) && (tp->t_state & TS_TBLOCK) &&
	    tp->t_rawq.c_cc < TTYHOG/5) {
		tp->t_state &= ~TS_TBLOCK;
		(void) dcmctl(dev, DML_RTS, DMBIS);
	}
E 16
	return ((*linesw[tp->t_line].l_read)(tp, uio, flag));
}

dcwrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp;

	tp = &dc_tty[minor(dev)];
	return ((*linesw[tp->t_line].l_write)(tp, uio, flag));
}

D 3
/*
 * Check for interrupts from all devices.
 */
dcintr()
{
	register struct pdma *p;
	register unsigned csr;
	register int unit;

	for (unit = 0, p = dcpdma; p < &dcpdma[NDCLINE]; unit += 4, p += 4) {
		while ((csr = p->p_addr->dc_csr) & (CSR_RDONE | CSR_TRDY)) {
			if (csr & CSR_RDONE)
				dcrint(unit);
			if (csr & CSR_TRDY)
				dcxint(&dc_tty[unit + ((csr >> 8) & 03)]);
		}
	}
}

dcrint(unit)
	register int unit;
{
	register dcregs *dcaddr;
	register struct tty *tp;
	register int c, cc;
	register struct tty *tp0;
	int overrun = 0;

	dcaddr = dcpdma[unit].p_addr;
	tp0 = &dc_tty[unit];
	while ((c = dcaddr->dc_rbuf) < 0) {	/* char present */
		cc = c & 0xff;
		tp = tp0 + ((c >> 8) & 03);
		if ((c & RBUF_OERR) && overrun == 0) {
			log(LOG_WARNING, "dc%d,%d: silo overflow\n", unit >> 2,
				(c >> 8) & 03);
			overrun = 1;
		}
		/* the keyboard requires special translation */
		if (tp == &dc_tty[KBD_PORT]) {
			static u_char shiftDown;
			static u_char ctrlDown;
			static u_char lastChar;

#ifdef DEBUG
			if (cc == LK_DO)
				panic("dcrint");
			debugChar = cc;

#endif
			if (dcDivertXInput) {
#ifdef DEBUG
				if (cc == KEY_F1) {
					dcDivertXInput = 0;
					continue;
				}
#endif
				pmKbdEvent(cc);
				continue;
			}

			switch (cc) {
			case KEY_REPEAT:
				cc = lastChar;
				goto done;

			case KEY_UP:
				shiftDown = 0;
				ctrlDown = 0;
				continue;

			case KEY_SHIFT:
				if (ctrlDown)
					shiftDown = 0;
				else
					shiftDown = 1;
				continue;

			case KEY_CONTROL:
				if (shiftDown)
					ctrlDown = 0;
				else
					ctrlDown = 1;
				continue;

			case LK_POWER_ERROR:
			case LK_KDOWN_ERROR:
			case LK_INPUT_ERROR:
			case LK_OUTPUT_ERROR:
				log(LOG_WARNING,
					"dc0,0: keyboard error, code=%x\n", cc);
				continue;
			}
			if (shiftDown)
				cc = shiftedAscii[cc];
			else
				cc = unshiftedAscii[cc];
			if (cc >= KBD_NOKEY) {
				/*
				 * A function key was typed - ignore it.
				 */
				continue;
			}
			if (cc >= 'a' && cc <= 'z') {
				if (ctrlDown)
					cc = cc - 'a' + '\1'; /* ^A */
				else if (shiftDown)
					cc = cc - 'a' + 'A';
			} else if (ctrlDown) {
				if (cc >= '[' && cc <= '_')
					cc = cc - '@';
				else if (cc == ' ' || cc == '@')
					cc = '\0';
			}
			lastChar = cc;
		done:
			;
		} else if (tp == &dc_tty[MOUSE_PORT]) {
			register MouseReport *newRepPtr;
			static MouseReport currentRep;

			newRepPtr = &currentRep;
			newRepPtr->byteCount++;
			if (cc & MOUSE_START_FRAME) {
				/*
				 * The first mouse report byte (button state).
				 */
				newRepPtr->state = cc;
				if (newRepPtr->byteCount > 1)
					newRepPtr->byteCount = 1;
			} else if (newRepPtr->byteCount == 2) {
				/*
				 * The second mouse report byte (delta x).
				 */
				newRepPtr->dx = cc;
			} else if (newRepPtr->byteCount == 3) {
				/*
				 * The final mouse report byte (delta y).
				 */
				newRepPtr->dy = cc;
				newRepPtr->byteCount = 0;
				if (newRepPtr->dx != 0 || newRepPtr->dy != 0) {
					/*
					 * If the mouse moved,
					 * post a motion event.
					 */
					pmMouseEvent(newRepPtr);
				}
				pmMouseButtons(newRepPtr);
			}
			continue;
		}
		if (!(tp->t_state & TS_ISOPEN)) {
			wakeup((caddr_t)&tp->t_rawq);
#ifdef PORTSELECTOR
			if (!(tp->t_state & TS_WOPEN))
#endif
				continue;
		}
		if (c & RBUF_FERR)
			cc |= TTY_FE;
		if (c & RBUF_PERR)
			cc |= TTY_PE;
		(*linesw[tp->t_line].l_rint)(cc, tp);
	}
	DELAY(10);
}

E 3
/*ARGSUSED*/
D 6
dcioctl(dev, cmd, data, flag)
E 6
I 6
dcioctl(dev, cmd, data, flag, p)
E 6
	dev_t dev;
I 11
D 18
	int cmd;
E 18
I 18
	u_long cmd;
E 18
E 11
	caddr_t data;
I 6
	int flag;
	struct proc *p;
E 6
{
	register struct tty *tp;
	register int unit = minor(dev);
	register int dc = unit >> 2;
	int error;

	tp = &dc_tty[unit];
D 6
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
E 6
I 6
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag, p);
E 6
	if (error >= 0)
		return (error);
	error = ttioctl(tp, cmd, data, flag);
	if (error >= 0)
		return (error);

	switch (cmd) {

	case TIOCSBRK:
		dc_brk[dc] |= 1 << ((unit & 03) + 8);
		ttyoutput(0, tp);
		break;

	case TIOCCBRK:
		dc_brk[dc] &= ~(1 << ((unit & 03) + 8));
		ttyoutput(0, tp);
		break;

	case TIOCSDTR:
D 16
		(void) dcmctl(dev, DML_DTR|DML_RTS, DMBIS);
E 16
I 16
		(void) dcmctl(dev, DML_DTR | DML_RTS, DMBIS);
E 16
		break;

	case TIOCCDTR:
D 16
		(void) dcmctl(dev, DML_DTR|DML_RTS, DMBIC);
E 16
I 16
		(void) dcmctl(dev, DML_DTR | DML_RTS, DMBIC);
E 16
		break;

	case TIOCMSET:
		(void) dcmctl(dev, *(int *)data, DMSET);
		break;

	case TIOCMBIS:
		(void) dcmctl(dev, *(int *)data, DMBIS);
		break;

	case TIOCMBIC:
		(void) dcmctl(dev, *(int *)data, DMBIC);
		break;

	case TIOCMGET:
		*(int *)data = dcmctl(dev, 0, DMGET);
		break;

	default:
		return (ENOTTY);
	}
	return (0);
}

dcparam(tp, t)
	register struct tty *tp;
	register struct termios *t;
{
	register dcregs *dcaddr;
	register int lpr;
	register int cflag = t->c_cflag;
	int unit = minor(tp->t_dev);
	int ospeed = ttspeedtab(t->c_ospeed, dcspeedtab);
I 17
	int s;
E 17

	/* check requested parameters */
        if (ospeed < 0 || (t->c_ispeed && t->c_ispeed != t->c_ospeed) ||
D 11
            (cflag & CSIZE) == CS5 || (cflag & CSIZE) == CS6)
E 11
I 11
            (cflag & CSIZE) == CS5 || (cflag & CSIZE) == CS6 ||
	    (pmax_boardtype == DS_PMAX && t->c_ospeed == 19200))
E 11
                return (EINVAL);
        /* and copy to tty */
        tp->t_ispeed = t->c_ispeed;
        tp->t_ospeed = t->c_ospeed;
        tp->t_cflag = cflag;

D 11
	dcaddr = dcpdma[unit].p_addr;
	if (tp == dc_tty + KBD_PORT) {
		/* handle the keyboard specially */
		dcaddr->dc_lpr = LPR_RXENAB | LPR_B4800 | LPR_8_BIT_CHAR |
			KBD_PORT;
E 11
I 11
D 17
	dcaddr = (dcregs *)dcpdma[unit].p_addr;

E 17
	/*
	 * Handle console cases specially.
	 */
	if (cn_tab.cn_screen) {
		if (unit == DCKBD_PORT) {
D 17
			dcaddr->dc_lpr = LPR_RXENAB | LPR_8_BIT_CHAR |
E 17
I 17
			lpr = LPR_RXENAB | LPR_8_BIT_CHAR |
E 17
				LPR_B4800 | DCKBD_PORT;
D 17
			MachEmptyWriteBuffer();
			return (0);
E 17
I 17
			goto out;
E 17
		} else if (unit == DCMOUSE_PORT) {
D 17
			dcaddr->dc_lpr = LPR_RXENAB | LPR_B4800 | LPR_OPAR |
E 17
I 17
			lpr = LPR_RXENAB | LPR_B4800 | LPR_OPAR |
E 17
				LPR_PARENB | LPR_8_BIT_CHAR | DCMOUSE_PORT;
D 17
			MachEmptyWriteBuffer();
			return (0);
E 17
I 17
			goto out;
E 17
		}
	} else if (tp->t_dev == cn_tab.cn_dev) {
D 17
		dcaddr->dc_lpr = LPR_RXENAB | LPR_8_BIT_CHAR |
			LPR_B9600 | unit;
E 11
		MachEmptyWriteBuffer();
		return (0);
E 17
I 17
		lpr = LPR_RXENAB | LPR_8_BIT_CHAR | LPR_B9600 | unit;
		goto out;
E 17
	}
D 11
	if (tp == dc_tty + MOUSE_PORT) {
		/* handle the mouse specially */
		dcaddr->dc_lpr = LPR_RXENAB | LPR_B4800 | LPR_OPAR |
			LPR_PARENB | LPR_8_BIT_CHAR | MOUSE_PORT;
		MachEmptyWriteBuffer();
		return (0);
	}
E 11
	if (ospeed == 0) {
		(void) dcmctl(unit, 0, DMSET);	/* hang up line */
		return (0);
	}
	lpr = LPR_RXENAB | ospeed | (unit & 03);
	if ((cflag & CSIZE) == CS7)
		lpr |= LPR_7_BIT_CHAR;
	else
		lpr |= LPR_8_BIT_CHAR;
	if (cflag & PARENB)
		lpr |= LPR_PARENB;
	if (cflag & PARODD)
		lpr |= LPR_OPAR;
	if (cflag & CSTOPB)
		lpr |= LPR_2_STOP;
I 17
out:
	dcaddr = (dcregs *)dcpdma[unit].p_addr;
	s = spltty();
E 17
	dcaddr->dc_lpr = lpr;
	MachEmptyWriteBuffer();
I 17
	splx(s);
E 17
I 13
	DELAY(10);
E 13
	return (0);
}

I 3
/*
 * Check for interrupts from all devices.
 */
void
dcintr(unit)
	register int unit;
{
	register dcregs *dcaddr;
	register unsigned csr;

	unit <<= 2;
D 11
	dcaddr = dcpdma[unit].p_addr;
E 11
I 11
	dcaddr = (dcregs *)dcpdma[unit].p_addr;
E 11
	while ((csr = dcaddr->dc_csr) & (CSR_RDONE | CSR_TRDY)) {
		if (csr & CSR_RDONE)
			dcrint(unit);
		if (csr & CSR_TRDY)
			dcxint(&dc_tty[unit + ((csr >> 8) & 03)]);
	}
}

dcrint(unit)
	register int unit;
{
	register dcregs *dcaddr;
	register struct tty *tp;
	register int c, cc;
	register struct tty *tp0;
	int overrun = 0;

D 11
	dcaddr = dcpdma[unit].p_addr;
E 11
I 11
	dcaddr = (dcregs *)dcpdma[unit].p_addr;
E 11
	tp0 = &dc_tty[unit];
	while ((c = dcaddr->dc_rbuf) < 0) {	/* char present */
		cc = c & 0xff;
		tp = tp0 + ((c >> 8) & 03);
		if ((c & RBUF_OERR) && overrun == 0) {
			log(LOG_WARNING, "dc%d,%d: silo overflow\n", unit >> 2,
				(c >> 8) & 03);
			overrun = 1;
		}
		/* the keyboard requires special translation */
D 11
		if (tp == &dc_tty[KBD_PORT]) {
E 11
I 11
		if (tp == &dc_tty[DCKBD_PORT] && cn_tab.cn_screen) {
E 11
#ifdef KADB
			if (cc == LK_DO) {
				spl0();
				kdbpanic();
				return;
			}
#endif
#ifdef DEBUG
			debugChar = cc;
#endif
			if (dcDivertXInput) {
D 5
				pmKbdEvent(cc);
E 5
I 5
				(*dcDivertXInput)(cc);
E 5
				return;
			}
D 11
			if ((cc = dcMapChar(cc)) < 0)
E 11
I 11
			if ((cc = kbdMapChar(cc)) < 0)
E 11
				return;
D 5
		} else if (tp == &dc_tty[MOUSE_PORT]) {
			register MouseReport *newRepPtr;
E 5
I 5
D 11
		} else if (tp == &dc_tty[MOUSE_PORT] && dcMouseButtons) {
E 11
I 11
		} else if (tp == &dc_tty[DCMOUSE_PORT] && dcMouseButtons) {
E 11
			register MouseReport *mrp;
E 5
			static MouseReport currentRep;

D 5
			newRepPtr = &currentRep;
			newRepPtr->byteCount++;
E 5
I 5
			mrp = &currentRep;
			mrp->byteCount++;
E 5
			if (cc & MOUSE_START_FRAME) {
				/*
				 * The first mouse report byte (button state).
				 */
D 5
				newRepPtr->state = cc;
				if (newRepPtr->byteCount > 1)
					newRepPtr->byteCount = 1;
			} else if (newRepPtr->byteCount == 2) {
E 5
I 5
				mrp->state = cc;
				if (mrp->byteCount > 1)
					mrp->byteCount = 1;
			} else if (mrp->byteCount == 2) {
E 5
				/*
				 * The second mouse report byte (delta x).
				 */
D 5
				newRepPtr->dx = cc;
			} else if (newRepPtr->byteCount == 3) {
E 5
I 5
				mrp->dx = cc;
			} else if (mrp->byteCount == 3) {
E 5
				/*
				 * The final mouse report byte (delta y).
				 */
D 5
				newRepPtr->dy = cc;
				newRepPtr->byteCount = 0;
				if (newRepPtr->dx != 0 || newRepPtr->dy != 0) {
E 5
I 5
				mrp->dy = cc;
				mrp->byteCount = 0;
				if (mrp->dx != 0 || mrp->dy != 0) {
E 5
					/*
					 * If the mouse moved,
					 * post a motion event.
					 */
D 5
					pmMouseEvent(newRepPtr);
E 5
I 5
					(*dcMouseEvent)(mrp);
E 5
				}
D 5
				pmMouseButtons(newRepPtr);
E 5
I 5
				(*dcMouseButtons)(mrp);
E 5
			}
			return;
		}
		if (!(tp->t_state & TS_ISOPEN)) {
			wakeup((caddr_t)&tp->t_rawq);
#ifdef PORTSELECTOR
			if (!(tp->t_state & TS_WOPEN))
#endif
				return;
		}
		if (c & RBUF_FERR)
			cc |= TTY_FE;
		if (c & RBUF_PERR)
			cc |= TTY_PE;
I 16
		if ((tp->t_cflag & CRTS_IFLOW) && !(tp->t_state & TS_TBLOCK) &&
		    tp->t_rawq.c_cc + tp->t_canq.c_cc >= TTYHOG) {
			tp->t_state &= ~TS_TBLOCK;
			(void) dcmctl(tp->t_dev, DML_RTS, DMBIC);
		}
E 16
		(*linesw[tp->t_line].l_rint)(cc, tp);
	}
	DELAY(10);
}

I 4
void
E 4
E 3
dcxint(tp)
	register struct tty *tp;
{
	register struct pdma *dp;
	register dcregs *dcaddr;
I 16
	int unit;
E 16

D 15
	dp = (struct pdma *)tp->t_addr;
E 15
I 15
D 16
	dp = &dcpdma[minor(tp->t_dev)];
E 16
I 16
	dp = &dcpdma[unit = minor(tp->t_dev)];
E 16
E 15
	if (dp->p_mem < dp->p_end) {
D 11
		dcaddr = dp->p_addr;
E 11
I 11
		dcaddr = (dcregs *)dp->p_addr;
E 11
D 16
		dcaddr->dc_tdr = dc_brk[(tp - dc_tty) >> 2] | *dp->p_mem++;
E 16
I 16
		/* check for hardware flow control of output */
		if ((tp->t_cflag & CCTS_OFLOW) && pmax_boardtype != DS_PMAX) {
			switch (unit) {
			case DCCOMM_PORT:
				if (dcaddr->dc_msr & MSR_CTS2)
					break;
				goto stop;

			case DCPRINTER_PORT:
				if (dcaddr->dc_msr & MSR_CTS3)
					break;
			stop:
				tp->t_state &= ~TS_BUSY;
				tp->t_state |= TS_TTSTOP;
				ndflush(&tp->t_outq, dp->p_mem-tp->t_outq.c_cf);
				dp->p_end = dp->p_mem = tp->t_outq.c_cf;
				dcaddr->dc_tcr &= ~(1 << unit);
				MachEmptyWriteBuffer();
				DELAY(10);
				return;
			}
		}
D 17
		dcaddr->dc_tdr = dc_brk[unit >> 2] | *dp->p_mem++;
E 17
I 17
		dcaddr->dc_tdr = dc_brk[unit >> 2] | *(u_char *)dp->p_mem;
		dp->p_mem++;
E 17
E 16
		MachEmptyWriteBuffer();
		DELAY(10);
		return;
	}
	tp->t_state &= ~TS_BUSY;
	if (tp->t_state & TS_FLUSH)
		tp->t_state &= ~TS_FLUSH;
	else {
D 16
		ndflush(&tp->t_outq, dp->p_mem-tp->t_outq.c_cf);
E 16
I 16
		ndflush(&tp->t_outq, dp->p_mem - tp->t_outq.c_cf);
E 16
		dp->p_end = dp->p_mem = tp->t_outq.c_cf;
	}
	if (tp->t_line)
		(*linesw[tp->t_line].l_start)(tp);
	else
		dcstart(tp);
	if (tp->t_outq.c_cc == 0 || !(tp->t_state & TS_BUSY)) {
D 11
		dp->p_addr->dc_tcr &= ~(1 << (minor(tp->t_dev) & 03));
E 11
I 11
D 13
		((dcregs *)dp->p_addr)->dc_tcr &= ~(1 << (minor(tp->t_dev) & 03));
E 13
I 13
		dcaddr = (dcregs *)dp->p_addr;
D 16
		dcaddr->dc_tcr &= ~(1 << (minor(tp->t_dev) & 03));
E 16
I 16
		dcaddr->dc_tcr &= ~(1 << (unit & 03));
E 16
E 13
E 11
		MachEmptyWriteBuffer();
		DELAY(10);
	}
}

I 4
void
E 4
dcstart(tp)
	register struct tty *tp;
{
	register struct pdma *dp;
	register dcregs *dcaddr;
	register int cc;
D 16
	int s;
E 16
I 16
	int unit, s;
E 16

D 15
	dp = (struct pdma *)tp->t_addr;
E 15
I 15
D 16
	dp = &dcpdma[minor(tp->t_dev)];
E 16
I 16
	dp = &dcpdma[unit = minor(tp->t_dev)];
E 16
E 15
D 11
	dcaddr = dp->p_addr;
E 11
I 11
	dcaddr = (dcregs *)dp->p_addr;
E 11
	s = spltty();
	if (tp->t_state & (TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
		goto out;
	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state & TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
D 2
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
E 2
I 2
		selwakeup(&tp->t_wsel);
E 2
	}
	if (tp->t_outq.c_cc == 0)
		goto out;
	/* handle console specially */
D 11
	if (tp == dc_tty) {
E 11
I 11
	if (tp == &dc_tty[DCKBD_PORT] && cn_tab.cn_screen) {
E 11
		while (tp->t_outq.c_cc > 0) {
			cc = getc(&tp->t_outq) & 0x7f;
D 5
			pmPutc(cc);
E 5
I 5
			cnputc(cc);
E 5
		}
		/*
		 * After we flush the output queue we may need to wake
		 * up the process that made the output.
		 */
		if (tp->t_outq.c_cc <= tp->t_lowat) {
			if (tp->t_state & TS_ASLEEP) {
				tp->t_state &= ~TS_ASLEEP;
				wakeup((caddr_t)&tp->t_outq);
			}
D 2
			if (tp->t_wsel) {
				selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
				tp->t_wsel = 0;
				tp->t_state &= ~TS_WCOLL;
			}
E 2
I 2
			selwakeup(&tp->t_wsel);
E 2
		}
		goto out;
	}
D 16
	if (tp->t_flags & (RAW|LITOUT))
		cc = ndqb(&tp->t_outq, 0);
	else {
		cc = ndqb(&tp->t_outq, 0200);
		if (cc == 0) {
			cc = getc(&tp->t_outq);
D 7
			timeout(ttrstrt, (caddr_t)tp, (cc & 0x7f) + 6);
E 7
I 7
			timeout(ttrstrt, (void *)tp, (cc & 0x7f) + 6);
E 7
			tp->t_state |= TS_TIMEOUT;
			goto out;
		}
	}
E 16
I 16
	cc = ndqb(&tp->t_outq, 0);
E 16
	tp->t_state |= TS_BUSY;
	dp->p_end = dp->p_mem = tp->t_outq.c_cf;
	dp->p_end += cc;
D 16
	dcaddr->dc_tcr |= 1 << (minor(tp->t_dev) & 03);
E 16
I 16
	dcaddr->dc_tcr |= 1 << (unit & 03);
E 16
	MachEmptyWriteBuffer();
out:
	splx(s);
}

/*
 * Stop output on a line.
 */
/*ARGSUSED*/
dcstop(tp, flag)
	register struct tty *tp;
{
	register struct pdma *dp;
	register int s;

D 15
	dp = (struct pdma *)tp->t_addr;
E 15
I 15
	dp = &dcpdma[minor(tp->t_dev)];
E 15
	s = spltty();
	if (tp->t_state & TS_BUSY) {
		dp->p_end = dp->p_mem;
		if (!(tp->t_state & TS_TTSTOP))
			tp->t_state |= TS_FLUSH;
	}
	splx(s);
}

dcmctl(dev, bits, how)
	dev_t dev;
	int bits, how;
{
	register dcregs *dcaddr;
	register int unit, mbits;
	int b, s;
I 3
D 11
#ifdef DS5000
E 11
D 16
	register int msr;
E 16
I 16
	register int tcr, msr;
E 16
D 11
#endif
E 11
E 3

	unit = minor(dev);
	b = 1 << (unit & 03);
D 11
	dcaddr = dcpdma[unit].p_addr;
E 11
I 11
	dcaddr = (dcregs *)dcpdma[unit].p_addr;
E 11
	s = spltty();
D 16
	/* only channel 2 has modem control (what about line 3?) */
I 11
	mbits = DML_DTR | DML_DSR | DML_CAR;
E 16
I 16
	/* only channel 2 has modem control on a DECstation 2100/3100 */
	mbits = DML_DTR | DML_RTS | DML_DSR | DML_CAR;
E 16
E 11
D 3
	if ((unit & 03) == 2) {
E 3
I 3
	switch (unit & 03) {
	case 2:
E 3
		mbits = 0;
D 16
		if (dcaddr->dc_tcr & TCR_DTR2)
E 16
I 16
		tcr = dcaddr->dc_tcr;
		if (tcr & TCR_DTR2)
E 16
			mbits |= DML_DTR;
I 16
		if (pmax_boardtype != DS_PMAX && (tcr & TCR_RTS2))
			mbits |= DML_RTS;
E 16
I 3
D 11
#ifdef DS3100
E 3
		if (dcaddr->dc_msr & MSR_DSR2)
			mbits |= DML_DSR | DML_CAR;
D 3
	} else
E 3
I 3
#endif
#ifdef DS5000
E 11
		msr = dcaddr->dc_msr;
		if (msr & MSR_CD2)
			mbits |= DML_CAR;
D 11
		if (msr & MSR_DSR2)
			mbits |= DML_DSR;
#endif
E 11
I 11
		if (msr & MSR_DSR2) {
			if (pmax_boardtype == DS_PMAX)
				mbits |= DML_CAR | DML_DSR;
			else
				mbits |= DML_DSR;
		}
E 11
		break;

D 11
#ifdef DS5000
E 11
	case 3:
D 11
		mbits = 0;
		if (dcaddr->dc_tcr & TCR_DTR3)
			mbits |= DML_DTR;
		msr = dcaddr->dc_msr;
		if (msr & MSR_CD3)
			mbits |= DML_CAR;
		if (msr & MSR_DSR3)
			mbits |= DML_DSR;
		break;
#endif

	default:
E 3
		mbits = DML_DTR | DML_DSR | DML_CAR;
E 11
I 11
		if (pmax_boardtype != DS_PMAX) {
			mbits = 0;
D 16
			if (dcaddr->dc_tcr & TCR_DTR3)
E 16
I 16
			tcr = dcaddr->dc_tcr;
			if (tcr & TCR_DTR3)
E 16
				mbits |= DML_DTR;
I 16
			if (tcr & TCR_RTS3)
				mbits |= DML_RTS;
E 16
			msr = dcaddr->dc_msr;
			if (msr & MSR_CD3)
				mbits |= DML_CAR;
			if (msr & MSR_DSR3)
				mbits |= DML_DSR;
		}
E 11
I 3
	}
E 3
	switch (how) {
	case DMSET:
		mbits = bits;
		break;

	case DMBIS:
		mbits |= bits;
		break;

	case DMBIC:
		mbits &= ~bits;
		break;

	case DMGET:
		(void) splx(s);
		return (mbits);
	}
D 3
	if ((unit & 03) == 2) {
E 3
I 3
	switch (unit & 03) {
	case 2:
I 16
		tcr = dcaddr->dc_tcr;
E 16
E 3
		if (mbits & DML_DTR)
D 16
			dcaddr->dc_tcr |= TCR_DTR2;
E 16
I 16
			tcr |= TCR_DTR2;
E 16
		else
D 16
			dcaddr->dc_tcr &= ~TCR_DTR2;
E 16
I 16
			tcr &= ~TCR_DTR2;
		if (pmax_boardtype != DS_PMAX) {
			if (mbits & DML_RTS)
				tcr |= TCR_RTS2;
			else
				tcr &= ~TCR_RTS2;
		}
		dcaddr->dc_tcr = tcr;
E 16
I 3
		break;

D 11
#ifdef DS5000
E 11
	case 3:
D 11
		if (mbits & DML_DTR)
			dcaddr->dc_tcr |= TCR_DTR3;
		else
			dcaddr->dc_tcr &= ~TCR_DTR3;
#endif
E 11
I 11
		if (pmax_boardtype != DS_PMAX) {
I 16
			tcr = dcaddr->dc_tcr;
E 16
			if (mbits & DML_DTR)
D 16
				dcaddr->dc_tcr |= TCR_DTR3;
E 16
I 16
				tcr |= TCR_DTR3;
E 16
			else
D 16
				dcaddr->dc_tcr &= ~TCR_DTR3;
E 16
I 16
				tcr &= ~TCR_DTR3;
			if (mbits & DML_RTS)
				tcr |= TCR_RTS3;
			else
				tcr &= ~TCR_RTS3;
			dcaddr->dc_tcr = tcr;
E 16
		}
E 11
E 3
	}
D 18
	if ((mbits & DML_DTR) && (dcsoftCAR[unit >> 2] & b))
		dc_tty[unit].t_state |= TS_CARR_ON;
E 18
	(void) splx(s);
	return (mbits);
}

/*
 * This is called by timeout() periodically.
 * Check to see if modem status bits have changed.
 */
I 7
D 11
/* ARGSUSED */
E 7
I 6
static void
E 11
I 11
void
E 11
E 6
D 7
dcscan()
E 7
I 7
dcscan(arg)
	void *arg;
E 7
{
	register dcregs *dcaddr;
	register struct tty *tp;
D 16
	register int i, bit, car;
E 16
I 16
	register int unit, limit, dtr, dsr;
E 16
	int s;

I 16
	/* only channel 2 has modem control on a DECstation 2100/3100 */
	dtr = TCR_DTR2;
	dsr = MSR_DSR2;
	limit = (pmax_boardtype == DS_PMAX) ? 2 : 3;
E 16
	s = spltty();
D 16
	/* only channel 2 has modem control (what about line 3?) */
D 11
	dcaddr = dcpdma[i = 2].p_addr;
E 11
I 11
	dcaddr = (dcregs *)dcpdma[i = 2].p_addr;
E 11
	tp = &dc_tty[i];
	bit = TCR_DTR2;
	if (dcsoftCAR[i >> 2] & bit)
		car = 1;
	else
		car = dcaddr->dc_msr & MSR_DSR2;
	if (car) {
		/* carrier present */
		if (!(tp->t_state & TS_CARR_ON))
			(void)(*linesw[tp->t_line].l_modem)(tp, 1);
	} else if ((tp->t_state & TS_CARR_ON) &&
	    (*linesw[tp->t_line].l_modem)(tp, 0) == 0)
		dcaddr->dc_tcr &= ~bit;
E 16
I 16
	for (unit = 2; unit <= limit; unit++, dtr >>= 2, dsr >>= 8) {
		tp = &dc_tty[unit];
		dcaddr = (dcregs *)dcpdma[unit].p_addr;
D 18
		if (dcaddr->dc_msr & dsr) {
E 18
I 18
		if ((dcaddr->dc_msr & dsr) || (dcsoftCAR[0] & (1 << unit))) {
E 18
			/* carrier present */
			if (!(tp->t_state & TS_CARR_ON))
				(void)(*linesw[tp->t_line].l_modem)(tp, 1);
		} else if ((tp->t_state & TS_CARR_ON) &&
		    (*linesw[tp->t_line].l_modem)(tp, 0) == 0)
			dcaddr->dc_tcr &= ~dtr;
		/*
		 * If we are using hardware flow control and output is stopped,
		 * then resume transmit.
		 */
		if ((tp->t_cflag & CCTS_OFLOW) && (tp->t_state & TS_TTSTOP) &&
		    pmax_boardtype != DS_PMAX) {
			switch (unit) {
			case DCCOMM_PORT:
				if (dcaddr->dc_msr & MSR_CTS2)
					break;
				continue;

			case DCPRINTER_PORT:
				if (dcaddr->dc_msr & MSR_CTS3)
					break;
				continue;
			}
			tp->t_state &= ~TS_TTSTOP;
			dcstart(tp);
		}
	}
E 16
	splx(s);
D 7
	timeout(dcscan, (caddr_t)0, hz);
E 7
I 7
	timeout(dcscan, (void *)0, hz);
E 7
}

/*
 * ----------------------------------------------------------------------------
 *
D 11
 * dcKBDPutc --
E 11
I 11
 * dcGetc --
E 11
 *
D 11
 *	Put a character out to the keyboard.
E 11
I 11
 *	Read a character from a serial line.
E 11
 *
 * Results:
D 11
 *	None.
E 11
I 11
 *	A character read from the serial port.
E 11
 *
 * Side effects:
D 11
 *	A character is written to the keyboard.
 *
 * ----------------------------------------------------------------------------
 */
void
dcKBDPutc(c)
	register int c;
{
	register dcregs *dcaddr;
	register u_short tcr;
	register int timeout;
	int s, line;

	s = spltty();

	dcaddr = dcpdma[KBD_PORT].p_addr;
	tcr = dcaddr->dc_tcr;
	dcaddr->dc_tcr = tcr | (1 << KBD_PORT);
	MachEmptyWriteBuffer();
	DELAY(10);
	while (1) {
		/*
		 * Wait for transmitter to be not busy.
		 */
		timeout = 1000000;
		while (!(dcaddr->dc_csr & CSR_TRDY) && timeout > 0)
			timeout--;
		if (timeout == 0) {
			printf("dcKBDPutc: timeout waiting for CSR_TRDY\n");
			break;
		}
		line = (dcaddr->dc_csr >> 8) & 3;
		/*
		 * Check to be sure its the right port.
		 */
		if (line != KBD_PORT) {
			tcr |= 1 << line;
			dcaddr->dc_tcr &= ~(1 << line);
			MachEmptyWriteBuffer();
			DELAY(10);
			continue;
		}
		/*
		 * Start sending the character.
		 */
		dcaddr->dc_tdr = dc_brk[0] | (c & 0xff);
		MachEmptyWriteBuffer();
		DELAY(10);
		/*
		 * Wait for character to be sent.
		 */
		while (1) {
			/*
			 * cc -O bug: this code produces and infinite loop!
			 * while (!(dcaddr->dc_csr & CSR_TRDY))
			 *	;
			 */
			timeout = 1000000;
			while (!(dcaddr->dc_csr & CSR_TRDY) && timeout > 0)
				timeout--;
			line = (dcaddr->dc_csr >> 8) & 3;
			if (line != KBD_PORT) {
				tcr |= 1 << line;
				dcaddr->dc_tcr &= ~(1 << line);
				MachEmptyWriteBuffer();
				DELAY(10);
				continue;
			}
			dcaddr->dc_tcr &= ~(1 << KBD_PORT);
			MachEmptyWriteBuffer();
			DELAY(10);
			break;
		}
		break;
	}
	/*
	 * Enable interrupts for other lines which became ready.
	 */
	if (tcr & 0xF) {
		dcaddr->dc_tcr = tcr;
		MachEmptyWriteBuffer();
		DELAY(10);
	}

	splx(s);
}

#ifdef DEBUG
/*
 * ----------------------------------------------------------------------------
 *
D 3
 * dcKBDGetc --
E 3
I 3
 * dcDebugGetc --
E 3
 *
D 3
 *	Read a character from the keyboard.
E 3
I 3
 *	Read a character from the keyboard if one is ready (i.e., don't wait).
E 3
 *
 * Results:
 *	A character read from the mouse, -1 if none were ready.
 *
 * Side effects:
E 11
 *	None.
 *
 * ----------------------------------------------------------------------------
 */
int
D 3
dcKBDGetc()
E 3
I 3
D 11
dcDebugGetc()
E 11
I 11
dcGetc(dev)
	dev_t dev;
E 11
E 3
{
	register dcregs *dcaddr;
	register int c;
I 6
	int s;
E 6

D 11
	dcaddr = dcpdma[KBD_PORT].p_addr;
E 11
I 11
	dcaddr = (dcregs *)dcpdma[minor(dev)].p_addr;
E 11
	if (!dcaddr)
		return (0);
I 6
D 11

E 11
	s = spltty();
E 6
D 11
	if (c = debugChar)
		debugChar = 0;
	else {
		while (dcaddr->dc_csr & CSR_RDONE) {
			c = dcaddr->dc_rbuf;
			DELAY(10);
			if (((c >> 8) & 03) == KBD_PORT)
				break;
			c = 0;
		}
	}
I 6
	splx(s);

E 6
	return (c & 0xff);
}
#endif
I 3

/*
 * ----------------------------------------------------------------------------
 *
 * dcKBDGetc --
 *
 *	Read a character from the keyboard.
 *
 * Results:
 *	A character read from the keyboard.
 *
 * Side effects:
 *	None.
 *
 * ----------------------------------------------------------------------------
 */
int
dcKBDGetc()
{
	register dcregs *dcaddr;
	register int c;
	int s;

	dcaddr = dcpdma[KBD_PORT].p_addr;
	if (!dcaddr)
		return (-1);
	s = spltty();
E 11
	for (;;) {
		if (!(dcaddr->dc_csr & CSR_RDONE))
			continue;
		c = dcaddr->dc_rbuf;
		DELAY(10);
D 11
		if (((c >> 8) & 03) != KBD_PORT)
			continue;
		if ((c = dcMapChar(c & 0xff)) >= 0)
E 11
I 11
		if (((c >> 8) & 03) == (minor(dev) & 03))
E 11
			break;
	}
	splx(s);
D 11
	return (c);
E 11
I 11
	return (c & 0xff);
E 11
}

/*
D 11
 * ----------------------------------------------------------------------------
 *
 * dcMapChar --
 *
 *	Map characters from the keyboard to ASCII. Return -1 if there is
 *	no valid mapping.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Remember state of shift and control keys.
 *
 * ----------------------------------------------------------------------------
E 11
I 11
 * Send a char on a port, non interrupt driven.
E 11
 */
D 11
static int
dcMapChar(cc)
	int cc;
{
	static u_char shiftDown;
	static u_char ctrlDown;
	static u_char lastChar;

	switch (cc) {
	case KEY_REPEAT:
		cc = lastChar;
		goto done;

	case KEY_UP:
		shiftDown = 0;
		ctrlDown = 0;
		return (-1);

	case KEY_SHIFT:
		if (ctrlDown)
			shiftDown = 0;
		else
			shiftDown = 1;
		return (-1);

	case KEY_CONTROL:
		if (shiftDown)
			ctrlDown = 0;
		else
			ctrlDown = 1;
		return (-1);

	case LK_POWER_ERROR:
	case LK_KDOWN_ERROR:
	case LK_INPUT_ERROR:
	case LK_OUTPUT_ERROR:
		log(LOG_WARNING,
			"dc0,0: keyboard error, code=%x\n", cc);
		return (-1);
	}
	if (shiftDown)
		cc = shiftedAscii[cc];
	else
		cc = unshiftedAscii[cc];
	if (cc >= KBD_NOKEY) {
		/*
		 * A function key was typed - ignore it.
		 */
		return (-1);
	}
	if (cc >= 'a' && cc <= 'z') {
		if (ctrlDown)
			cc = cc - 'a' + '\1'; /* ^A */
		else if (shiftDown)
			cc = cc - 'a' + 'A';
	} else if (ctrlDown) {
		if (cc >= '[' && cc <= '_')
			cc = cc - '@';
		else if (cc == ' ' || cc == '@')
			cc = '\0';
	}
	lastChar = cc;
done:
	return (cc);
}
E 3

/*
 * ----------------------------------------------------------------------------
 *
 * dcKBDReset --
 *
 *	Reset the keyboard to default characteristics.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 * ----------------------------------------------------------------------------
 */
E 11
void
D 11
dcKBDReset()
{
	register int i;
	static int inKBDReset;

	if (inKBDReset)
		return;
	inKBDReset = 1;
	for (i = 0; i < sizeof(kbdInitString); i++)
		dcKBDPutc((int)kbdInitString[i]);
	inKBDReset = 0;
}

/*
 * ----------------------------------------------------------------------------
 *
 * MousePutc --
 *
 *	Write a character to the mouse.
 *	This is only called at initialization time.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	A character is written to the mouse.
 *
 * ----------------------------------------------------------------------------
 */
static void
MousePutc(c)
E 11
I 11
dcPutc(dev, c)
	dev_t dev;
E 11
	int c;
{
	register dcregs *dcaddr;
	register u_short tcr;
	register int timeout;
D 11
	int line;
E 11
I 11
	int s, line;
E 11

D 11
	dcaddr = dcpdma[MOUSE_PORT].p_addr;
E 11
I 11
	s = spltty();

	dcaddr = (dcregs *)dcpdma[minor(dev)].p_addr;
E 11
	tcr = dcaddr->dc_tcr;
D 11
	dcaddr->dc_tcr = tcr | (1 << MOUSE_PORT);
E 11
I 11
	dcaddr->dc_tcr = tcr | (1 << minor(dev));
E 11
	MachEmptyWriteBuffer();
	DELAY(10);
	while (1) {
		/*
		 * Wait for transmitter to be not busy.
		 */
		timeout = 1000000;
		while (!(dcaddr->dc_csr & CSR_TRDY) && timeout > 0)
			timeout--;
		if (timeout == 0) {
D 11
			printf("MousePutc: timeout waiting for CSR_TRDY\n");
E 11
I 11
			printf("dcPutc: timeout waiting for CSR_TRDY\n");
E 11
			break;
		}
		line = (dcaddr->dc_csr >> 8) & 3;
		/*
		 * Check to be sure its the right port.
		 */
D 11
		if (line != MOUSE_PORT) {
E 11
I 11
		if (line != minor(dev)) {
E 11
			tcr |= 1 << line;
			dcaddr->dc_tcr &= ~(1 << line);
			MachEmptyWriteBuffer();
			DELAY(10);
			continue;
		}
		/*
		 * Start sending the character.
		 */
		dcaddr->dc_tdr = dc_brk[0] | (c & 0xff);
		MachEmptyWriteBuffer();
		DELAY(10);
		/*
		 * Wait for character to be sent.
		 */
		while (1) {
			/*
			 * cc -O bug: this code produces and infinite loop!
			 * while (!(dcaddr->dc_csr & CSR_TRDY))
			 *	;
			 */
			timeout = 1000000;
			while (!(dcaddr->dc_csr & CSR_TRDY) && timeout > 0)
				timeout--;
			line = (dcaddr->dc_csr >> 8) & 3;
D 11
			if (line != MOUSE_PORT) {
E 11
I 11
			if (line != minor(dev)) {
E 11
				tcr |= 1 << line;
				dcaddr->dc_tcr &= ~(1 << line);
				MachEmptyWriteBuffer();
				DELAY(10);
				continue;
			}
D 11
			dcaddr->dc_tcr &= ~(1 << MOUSE_PORT);
E 11
I 11
			dcaddr->dc_tcr &= ~(1 << minor(dev));
E 11
			MachEmptyWriteBuffer();
			DELAY(10);
			break;
		}
		break;
	}
	/*
	 * Enable interrupts for other lines which became ready.
	 */
	if (tcr & 0xF) {
		dcaddr->dc_tcr = tcr;
		MachEmptyWriteBuffer();
		DELAY(10);
	}
D 11
}
E 11

D 11
/*
 * ----------------------------------------------------------------------------
 *
 * MouseGetc --
 *
 *	Read a character from the mouse.
 *	This is only called at initialization time.
 *
 * Results:
 *	A character read from the mouse, -1 if we timed out waiting.
 *
 * Side effects:
 *	None.
 *
 * ----------------------------------------------------------------------------
 */
static int
MouseGetc()
{
	register dcregs *dcaddr;
	register int timeout;
	register int c;

	dcaddr = dcpdma[MOUSE_PORT].p_addr;
	for (timeout = 1000000; timeout > 0; timeout--) {
		if (!(dcaddr->dc_csr & CSR_RDONE))
			continue;
		c = dcaddr->dc_rbuf;
		DELAY(10);
		if (((c >> 8) & 03) != MOUSE_PORT)
			continue;
		return (c & 0xff);
	}

	return (-1);
}

/*
 * ----------------------------------------------------------------------------
 *
 * MouseInit --
 *
 *	Initialize the mouse.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 * ----------------------------------------------------------------------------
 */
static void
MouseInit()
{
	int id_byte1, id_byte2, id_byte3, id_byte4;

	/*
	 * Initialize the mouse.
	 */
	MousePutc(MOUSE_SELF_TEST);
	id_byte1 = MouseGetc();
	if (id_byte1 < 0) {
		printf("MouseInit: Timeout on 1st byte of self-test report\n");
		return;
	}
	id_byte2 = MouseGetc();
	if (id_byte2 < 0) {
		printf("MouseInit: Timeout on 2nd byte of self-test report\n");
		return;
	}
	id_byte3 = MouseGetc();
	if (id_byte3 < 0) {
		printf("MouseInit: Timeout on 3rd byte of self-test report\n");
		return;
	}
	id_byte4 = MouseGetc();
	if (id_byte4 < 0) {
		printf("MouseInit: Timeout on 4th byte of self-test report\n");
		return;
	}
	if ((id_byte2 & 0x0f) != 0x2)
		printf("MouseInit: We don't have a mouse!!!\n");
	/*
	 * For some reason, the mouse doesn't see this command if it comes
	 * too soon after a self test.
	 */
	DELAY(100);
	MousePutc(MOUSE_INCREMENTAL);
E 11
I 11
	splx(s);
E 11
}
#endif /* NDC */
E 1
