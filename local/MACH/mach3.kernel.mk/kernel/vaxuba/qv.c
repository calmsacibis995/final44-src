/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	qv.c,v $
 * Revision 2.7  93/05/15  18:59:47  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.6  91/05/08  13:33:02  dbg
 * 	Move br and cvec to memory.
 * 	[91/03/26            dbg]
 * 
 * 	Include vax/machparam.h for SPL definitions.
 * 	[91/03/20            dbg]
 * 
 * Revision 2.5  91/03/16  15:04:02  rpd
 * 	Updated for new kmem_alloc interface.
 * 	Removed non-MACH, non-CMUCS, non-CMU code.
 * 	[91/03/03            rpd]
 * 
 * Revision 2.4  90/08/27  22:14:59  dbg
 * 	Flushed another ushort.
 * 	[90/07/16            dbg]
 * 
 * Revision 2.3  90/06/02  15:10:02  rpd
 * 	Converted to new IPC.  Purged MACH_DB.
 * 	[90/03/26  23:10:02  rpd]
 * 
 * Revision 2.2  89/11/14  10:29:06  dbg
 * 	Use dev_change_indirect to alias console.
 * 	[89/11/10            dbg]
 * 
 * Revision 2.1  89/08/03  16:41:10  rwd
 * Created.
 * 
 * 12-May-89  David Golub (dbg) at Carnegie-Mellon University
 *	Changed aliasing mechanism for console->qv.
 *
 *  2-May-89  David Golub (dbg) at Carnegie-Mellon University
 *	Added qvstrayint.
 *
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Altered for MACH kernel.  NO SELECT YET!
 *
 * 13-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Defined new "qvmodel" variable so that the default display
 *	model type can be patched for the few systems which still use
 *	a VR100.
 *	[ V5.1(XF24) ]
 *
 * 19-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Disable default blinking cursor and change default display
 *	model to VR260 now that most VR100 monitors have been replaced.
 *	[ V5.1(XF23) ]
 *
 * 15-May-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Added call out to mach_db debugger.
 *
 * 07-May-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: adjust the Hsync/Vsync width and total vertical
 *	characters fields in the VR260 initialization to use the 3:4
 *	value which matches the rom instead of the  11:4 value from the
 *	original Ultrix source; restore default VR100 display type
 *	(which works everywhere) since there is no known way for the
 *	driver to identify the model VR260 (which does not).
 *	[ V5.1(F10) ]
 *
 *  2-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added qvmap to map qvss memory directly to user space.
 *
 *  7-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Reorganized all the virtual console stuff to use indirect
 *	function calls from cons.c.
 *
 *  6-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Don't include qvfont.c.  It is compiled separately whenever
 *	either the QDSS or QVSS is configured.
 *
 *  6-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	vcons_init -> qvcons_init
 *	vpollc -> qv_pollc
 *	vgetc -> qv_getc
 *	vputc -> qv_putc
 *	(since I am now putting in qdss support as well).
 *
 *  5-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed use of _bit_tst to bit_test.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted, particularly under MACH.
 *
 *  8-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Merged rvb and mja/real 4.3 changes.
 *
 *  4-Aug-86  Robert V Baron (rvb) at Carnegie-Mellon University
 *	CMUCS: Change from Steve Popovich in qvioctl to cause
 *	window managers to get up/down transitions on symbol key.
 *
 * 25-Jul-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  changed to exchange console and QVSS cdevsw[] entries
 *	rather than just replace the console entry with the QVSS entry;
 *	modified to examine the watch chip RAM to determine whether we
 *	have booted from the serial line unit and also not make the
 *	display the console in this case.
 *
 *  3-Jul-86  Robert V Baron (rvb) at Carnegie-Mellon University
 *	1# allow dynamic screen size setup
 *		see qv_init and qv_setup and QIOCSETUP
 *	2# fix some "event queue" bugs for maps:
 *		qv_ipl_lo not unset if queue is full.
 *		qualify some qv_cur_pos if not mouse to minimize
 *		jumpiness.
 *
 * 19-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  fixed to revert to physical device address when
 *	called after a restart from the RPB.
 *
 * 02-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  commented out qv_init() call when mouse is closed
 *	in qvclose().
 *
 * 25-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 *  5-Dec-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Make the cursor go full screen. And make it invert better.
 *
 *  3-Dec-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	qv_init must still set the cursor mode to OR, since the
 *	qv_pos_cur code might have turned it AND to simulates XOR.
 *	
 *	Also qv_pos_cur must use the scanline map not the pure x,y
 *	position.
 *
 * 20-Nov-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  redid virtual console support so that vgetc()/vputc()
 *	return a value which indicates whether or not to link the virtual
 *	and physical consoles;  added new vpollc() routine.
 *
 * 14-Nov-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	The cursor is now only initialized once -- not in qv_init; this
 *	qv_init does not reset it.
 *	Forced the console to be a 260 vs 100.  Of course, now this won't
 *	work right on a 100 on a uVaxII, but ...
 *
 * 27-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed a ushort to u_short so that ushort can be flushed.
 *
 * 20-Sep-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Fixed the cursor blinking code to blink to true off.  And added
 *	ioctls to adjust the fade time as well as the cursor blinking rates.
 *
 * 11-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added Mike Accetta's improvements... CMUCS and CMUCS are
 *	defined here directly for now.
 *
 *  9-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added enough support for kernel debugger.
 *
 *  8-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added kernel debugger support.
 *
 * 26-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  created new vgetc() routine to allow polled
 *	virtual console input as well as output and split the character
 *	translation function of qvkint() off into a new qvgetc()
 *	routine so that it could be shared by both it and this new
 *	routine; changed qvkint() to ignore keyboard receive interrupts
 *	when this routine is being used so that it will receive all
 *	characters typed.
 *	CMUCS_KDB:  hooked qvkint() to kdb_kintr().
 *	[V1(1)]
 *
 * 20-Jun-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added IOCTL's for mouse and light scaling and for setting the cursor
 *	dynmically
 *
 * 19-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added hacks for reverse video printing on screen and fancy (!)
 *	led handling on keyboard.
 *
 * 19-Jun-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	change the qv_crt_params for 19' screen back to old values to
 *	scrunch screen on right not on left.   It seems that the last
 *	10pixels on the right get munged this way.
 *
 * 15-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  retrofitted for 4.2BSD;  made QVSSMAJOR an external variable
 *	so that it can be visible in conf.c.
 *	CMUCS:  revised vputc() so that it checks v_console since our
 *	cnputc() always calls it.
 *	[V1(1)]
 *	
 */
 
#include <mach_kdb.h>

/************************************************************************
 *									*
 *			Copyright (c) 1985 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   This software is  derived  from  software  received  from  the	*
 *   University    of   California,   Berkeley,   and   from   Bell	*
 *   Laboratories.  Use, duplication, or disclosure is  subject  to	*
 *   restrictions  under  license  agreements  with  University  of	*
 *   California and with AT&T.						*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************
 *
 * This driver provides glass tty functionality to the qvss. It is a strange
 * device in that it supports three subchannels. The first being the asr,
 * the second being a channel that intercepts the chars headed for the screen
 * ( like a pseudo tty ) and the third being a source of mouse state changes.
 *
 * There may be one and only one qvss in the system.  This restriction is based
 * on the inability to map more than one at a time.  This restriction will
 * exist until the kernel has shared memory services. This driver therefore
 * support a single unit. No attempt was made to have it service more.
 * 10 Apr 85 -- jg
 *	Well, our theory about keyboard handling was wrong; most of the 
 *	keyboard is in autorepeat, down mode.  These changes are to make
 *	the qvss work the same as the Vs100, which is not necessarily
 *	completely correct, as some chord usage may fail.  But since we
 *	can't easily change the Vs100, we might as well propagate the
 *	problem to another device.  There are also changes for screen and
 *	mouse accellaration.
 *
 * 27 Mar 85 -- rjl
 *	MicroVAX-II systems have interval timers that interrupt at ipl4.
 *	Everything else is higher and thus causes us to miss clock ticks. The
 *	problem isn't severe except in the case of a device like this one that
 *	generates lots of interrupts. We aren't willing to make this change to
 *	all device drivers but it seems acceptable in this case.
 *
 *  3 Dec 84 -- jg
 *	To continue the tradition of building a better mouse trap,  this
 * 	driver has been extended to form Vs100 style event queues.  If the
 *	mouse device is open, the keyboard events are intercepted and put
 *	into the shared memory queue.  Unfortunately, we are ending up with
 *	one of the longest Unix device drivers.  Sigh....
 *
 * 20 Nov 84 -- rjl
 *      As a further complication this driver is required to function as the
 *      virtual system console. This code runs before and during auto-
 *      configuration and therefore is require to have a second path for setup.
 *      It is futher constrained to have a character output routine that
 *      is not dependant on the interrupt system.
 *
 */


#include <qv.h>
#if NQV > 0  || defined(BINARY)

#ifdef	MACH_KERNEL
#include <sys/time.h>
#include <kern/time_out.h>

#include <device/conf.h>
#include <device/errno.h>
#include <device/tty.h>

#include <vax/cpu_data.h>
#include <vax/ka630.h>
#include <vax/machspl.h>
#include <vax/mtpr.h>
#include <vax/rpb.h>
#include <vax/pte.h>
#include <vax/vm_defs.h>

#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>
#include <vaxuba/qvioctl.h>
#else	MACH_KERNEL
#include "machine/pte.h"

#include "sys/param.h"
#include "sys/conf.h"
#include "sys/dir.h"
#include "sys/user.h"
#include "vaxuba/qvioctl.h"
#include "sys/tty.h"
#include "sys/map.h"
#include "sys/buf.h"
#include "sys/vm.h"
#include "sys/clist.h"
#include "sys/file.h"
#include "sys/uio.h"
#include "sys/kernel.h"

#include "vax/ioa.h"
#include "vax/cpu.h"
#include "vax/rpb.h"
#include "vax/ka630.h"

#include "vaxuba/ubareg.h"
#include "vaxuba/ubavar.h"
#include "sys/proc.h"
#endif	MACH_KERNEL
#include <vm/vm_kern.h>
#include <vax/cons.h>


/*
 *  ULTRIX-32 has a version of printf() which can write only to memory which we
 *  don't need for now.
 */
#define	mprintf	printf

struct	uba_device *qvinfo[NQV];

struct	tty qv_tty[NQV*4];

int	nNQV = NQV;
int	nqv = NQV*4;

int qv_rpollc = 0;			/* do receive character polling */
/*
 *  If this flag is set to -1, both the virtual and standard consoles
 *  will be used for kernel I/O.  If this flag is clear, only the virtual
 *  console will be used.
 */
int	v_consboth = 0;

/*
 * Definition of the driver for the auto-configuration program.
 */
int	qvprobe(), qvattach(), qvkint(), qvvint();
int	qvstrayint();
u_short	qvstd[] = { 0 };
struct	uba_driver qvdriver =
	{ qvprobe, 0, qvattach, 0, qvstd, "qv", qvinfo };


/*
 * Local variables for the driver. Initialized for 15' screen
 * so that it can be used during the boot process.
 */

#define QVWAITPRI 	(PZERO+1)
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
/*
 *  Major device number of QVSS initialized in conf.c.
 */
extern int QVSSMAJOR;
#endif	MACH_KERNEL
/*
 * v_console is the switch that is used to redirect the console cnputc to the
 * virtual console vputc.
 */
int v_console=0;
/*
 * qv_def_scrn is used to select the appropriate tables. 0=15 inch 1=19 inch,
 * 2 = new display (untested).
 */

int qv_def_scrn = 0;

#define QVMAXEVQ	64	/* must be power of 2 */
#define EVROUND(x)	((x) & (QVMAXEVQ - 1))

/*
 * Screen parameters 15 & 19 inch monitors. These determine the max size in
 * pixel and character units for the display and cursor positions.
 * Notice that the mouse defaults to original square algorithm, but X
 * will change to its defaults once implemented.
 */
struct qv_info *qv_scn;
struct qv_info qv_scn_defaults[] = {
	{0, {0, 0}, 0, {0, 0}, 0, 0, 30, 80, 768, 480, 768-1, 480-1,
	 0, 0, 0, 0, 0, QVMAXEVQ, 0, 0, {0, 0}, {0, 0, 0, 0}, 2, 4,
	 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 0},

	{0, {0, 0}, 0, {0, 0}, 0, 0, 55, 120, 960, 864, 960-1, 864-1,
	 0, 0, 0, 0, 0, QVMAXEVQ, 0, 0, {0, 0}, {0, 0, 0, 0}, 2, 4,
	 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 0},

	{0, {0, 0}, 0, {0, 0}, 0, 0, 56, 128,1024, 864,1024-1, 864-1,
	 0, 0, 0, 0, 0, QVMAXEVQ, 0, 0, {0, 0}, {0, 0, 0, 0}, 2, 4,
	 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 0}
};

/*
 * Screen controller initialization parameters. The definations and use
 * of these parameters can be found in the Motorola 68045 crtc specs. In
 * essence they set the display parameters for the chip. The first set is
 * for the 15" screen and the second is for the 19" seperate sync. There
 * is also a third set for a 19" composite sync monitor which we have not
 * tested and which is not supported.
 */
static short qv_crt_parms[][16] = {
           { 31, 25, 27, 0142, 31, 13, 30, 31, 4, 15, 040, 0, 0, 0, 0, 0 },
/* VR100*/ { 39, 30, 32, 0262, 55, 5, 54, 54, 4, 15, 040, 0, 0, 0, 0, 0 },
/* VR260*/ { 39, 32, 33, 0x34, 56, 5, 54, 54, 4, 15, 040, 0, 0, 0, 0, 0},
};
#define QVMOUSECHAN 	2

/*
 * Screen parameters
 */
struct qv_info  *qv_scn;
int qvmodel = QV260;	/* default model */
	
/*
 * Keyboard state
 */
struct qv_keyboard {
	int shift;			/* state variables	*/
	int cntrl;
	int lock;
	int lastcode;			/* last keycode typed	*/
	unsigned kup[8];		/* bits for each keycode*/
	unsigned dkeys[8];		/* down/up mode keys	*/
	char last;			/* last character	*/
} qv_keyboard;

extern char qv_font[], qv_key[], qv_shift_key[], *qv_special[];
extern unsigned short qv_cursor[];
/* useful defines for handling the up/down keyboard stuff */
#define KUP(i) bzero((caddr_t)i,sizeof(qv_keyboard.kup))
#define KINVERT(j,i) 	(j[i>>5] ^= 1 << (i & 31))
#define KSET(j,i)	(j[i>>5] |= 1 << (i & 31))
#define KCLEAR(j,i) 	(j[i>>5] &= ~(1 << (i & 31)))
#define KTEST(j,i) 	((j[i>>5] >> (i & 31)) & 1)
#define LK_UPDOWN 	0x86		/* bits for setting lk201 modes */
#define LK_AUTODOWN 	0x82
#define LK_DOWN 	0x80
#define LK_DEFAULTS 	0xd3		/* reset (some) default settings */
#define LK_AR_ENABLE 	0xe3		/* global auto repeat enable */
#define LK_CL_ENABLE 	0x1b		/* keyclick enable */
#define LK_KBD_ENABLE 	0x8b		/* keyboard enable */
#define LK_BELL_ENABLE 	0x23		/* the bell */
#define LK_LED_ENABLE 	0x13		/* light led */
#define LK_LED_DISABLE 	0x11		/* turn off led */
#define LK_RING_BELL 	0xa7		/* ring keyboard bell */
#define LED_1 		0x81		/* led bits */
#define LED_2 		0x82
#define LED_3 		0x84
#define LED_4 		0x88
#define LED_ALL 	0x8f
#define LK_KDOWN_ERROR	0x3d		/* key down on powerup error */
#define LK_POWER_ERROR 	0x3e		/* keyboard failure on powerup test */
#define LK_OUTPUT_ERROR	0xb5		/* keystrokes lost during inhibit */
#define LK_INPUT_ERROR 	0xb6		/* garbage command to keyboard */
#define LK_LOWEST	0x56		/* lowest significant keycode */
#define LK_DIV6_START	0xad		/* start of div 6 */
#define LK_DIV5_END	0xb2		/* end of div 5 */
/* 
 * If you change which divisions keys are down/up mode, then you must 
 * change the initialization of dkeys in qvattach.
 */
short divdefaults[15] = { LK_DOWN,	/* 0 doesn't exist */
	LK_AUTODOWN, LK_AUTODOWN, LK_AUTODOWN, LK_DOWN,
	LK_UPDOWN,   LK_UPDOWN,   LK_AUTODOWN, LK_AUTODOWN, 
	LK_AUTODOWN, LK_AUTODOWN, LK_AUTODOWN, LK_AUTODOWN, 
	LK_DOWN, LK_AUTODOWN };

short kbdinitstring[] = {		/* reset any random keyboard stuff */
	LK_AR_ENABLE,			/* we want autorepeat by default */
	LK_CL_ENABLE,			/* keyclick */
	0x84,				/* keyclick volume */
	LK_KBD_ENABLE,			/* the keyboard itself */
	LK_BELL_ENABLE,			/* keyboard bell */
	0x84,				/* bell volume */
	LK_LED_DISABLE,			/* keyboard leds */
	LED_ALL };
#define KBD_INIT_LENGTH	sizeof(kbdinitstring)/sizeof(short)

#define TOY ((time.tv_sec * 100) + (time.tv_usec / 10000))

int	qv_ipl_lo = 1;			/* IPL low flag			*/
int	mouseon = 0;			/* mouse channel is enabled when 1*/
#ifdef	MACH_KERNEL
queue_head_t	mouse_read_queue = { &mouse_read_queue, &mouse_read_queue };
boolean_t	mouse_read_done();
#else	MACH_KERNEL
thread_t	rsel;
#endif	MACH_KERNEL

int	qvstart(), ttrstrt();
#ifdef	MACH_KERNEL
int	qvstop();
#endif	MACH_KERNEL

int	qv_reverse_video = 0;		/* white on black as default */

static int led_pattern = 0;		/* led pattern */
static int led_interval = 0;		/* led interval */
static int led_increasing = 0;
static int led_lights = 1;
static int led_light_count = 0;

int	qv_mouse_interval = 0;		/* follow the mouse 60 time/sec */
int	qv_mouse_scale = 0;

	/*
	 * Note: the silly qvss cursor doesnot work
	 * correctly if you movc3 into it.
	 */
qvcurcopy(from, to)
register short *from, *to;
{
register int size = 16;

	while (size-- > 0) {
		*to++ = *from++;
	}
}

qvcurzero(to)
register short *to;
{
register int size = 16;

	while (size-- > 0) {
		*to++ = 0;
	}
}

#define QVCURCOPY(FROM,TO)\
{\
	register short *to = TO;\
	register short *from = FROM;\
\
	*to++ = *from++; *to++ = *from++;\
	*to++ = *from++; *to++ = *from++;\
	*to++ = *from++; *to++ = *from++;\
	*to++ = *from++; *to++ = *from++;\
	*to++ = *from++; *to++ = *from++;\
	*to++ = *from++; *to++ = *from++;\
	*to++ = *from++; *to++ = *from++;\
	*to++ = *from++; *to++ = *from++;\
}

#define QVCURZERO(TO) \
{\
	register short *to = TO;\
\
	*to++ = 0; *to++ = 0;\
	*to++ = 0; *to++ = 0;\
	*to++ = 0; *to++ = 0;\
	*to++ = 0; *to++ = 0;\
	*to++ = 0; *to++ = 0;\
	*to++ = 0; *to++ = 0;\
	*to++ = 0; *to++ = 0;\
	*to++ = 0; *to++ = 0;\
}

/*
 * See if the qvss will interrupt.
 */

extern volatile int	br, cvec;

/*ARGSUSED*/
qvprobe(reg, ctlr)
	caddr_t reg;
	int ctlr;
{
	register struct qvdevice *qvaddr = (struct qvdevice *)reg;
	static int tvec, ovec;

#ifdef lint
	qvkint(0); qvvint(0); qvstrayint(0);
#endif
	/*
	 * Allocate the next two vectors
	 */
	tvec = 0360;
	ovec = cvec;
	/*
	 * Turn on the keyboard and vertical interrupt vectors.
	 */
	qvaddr->qv_intcsr = 0;		/* init the interrupt controler */
	qvaddr->qv_intcsr = 0x40;	/* reset irr			*/
	qvaddr->qv_intcsr = 0x80;	/* specify individual vectors	*/
	qvaddr->qv_intcsr = 0xc0;	/* preset autoclear data	*/
	qvaddr->qv_intdata = 0xff;	/* all setup as autoclear	*/

	qvaddr->qv_intcsr = 0xe0;	/* preset vector address 1	*/
	qvaddr->qv_intdata = tvec;	/* give it the keyboard vector	*/
	qvaddr->qv_intcsr = 0x28;	/* enable tx/rx interrupt	*/

	qvaddr->qv_intcsr = 0xe1;	/* preset vector address 2	*/
	qvaddr->qv_intdata = tvec+4;	/* give it the vertical sysnc	*/
	qvaddr->qv_intcsr = 0x29;	/* enable 			*/

	qvaddr->qv_intcsr = 0xa1;	/* arm the interrupt ctrl	*/

	qvaddr->qv_uartcmd = 0x15;	/* set mode pntr/enable rx/tx	*/
	qvaddr->qv_uartmode = 0x17;	/* noparity, 8-bit		*/
	qvaddr->qv_uartmode = 0x07;	/* 1 stop bit			*/
	qvaddr->qv_uartstatus = 0x99;	/* 4800 baud xmit/recv 		*/
	qvaddr->qv_uartintstatus = 2;	/* enable recv interrupts	*/

	qvaddr->qv_csr |= QV_INT_ENABLE | QV_CUR_MODE;

	DELAY(20000);

	qvaddr->qv_csr &= ~QV_INT_ENABLE;

	/*
	 * If the qvss did interrupt it was the second vector not
	 * the first so we have to return the first so that they
	 * will be setup properly
	 */
	if( ovec == cvec ) {
		return 0;
	} else
		cvec = tvec;
	return (sizeof (struct qvdevice));
}

/* 
 *  Cursor blink simulation.
 */
int qvvon = 0;
int qvvcurson = 0;
int qvvcursoff = 0;
int qvvcurs = 20;

long qvktime;
#define QVKTIMEMIN (2*60)
long qvktimelim = 15*60;		

qvktimer(qvaddr)
struct qvdevice *qvaddr;
{
    timeout(qvktimer, (caddr_t)qvaddr, 60*hz); /*wakeup each minute */
    if ((time.tv_sec-qvktime) >= qvktimelim)
	qvaddr->qv_csr &= ~QV_VIDEO_ENA;
}

/*
 * Routine called to attach a qv.
 */
qvattach(ui)
        struct uba_device *ui;
{
        register struct qvdevice *qvaddr;
        register i;
        register int *pte;
        char *qvssmem;

        qvaddr = (struct qvdevice *)ui->ui_addr;

        /*
         * If not the console then we have to setup the screen
         */
        if( !v_console ) 
                qv_setup( qvaddr );

        /*
         * Map the qvss memory for use by users.
         */
        qvssmem = (char *)((qvaddr->qv_csr & QV_MEM_BANK) << 7);
        pte = (int *)(pmap_pte(pmap_kernel(),
				unibus_start[0] + (vm_offset_t)qvssmem));
        for( i=0 ; i<512 ; i++, pte++ )
                *pte = (*pte & ~PG_PROT) | PG_UW | PG_V;
	qvktime = time.tv_sec;
	qvktimer(qvaddr);
}

/*ARGSUSED*/
#ifdef	MACH_KERNEL
qvopen(dev, flag, ior)
	dev_t	dev;
	int	flag;
	io_req_t ior;
#else	MACH_KERNEL
qvopen(dev, flag)
	dev_t dev;
#endif	MACH_KERNEL
{
	register struct tty *tp;
	register int unit, qv;
	register struct qvdevice *qvaddr;
	register struct uba_device *ui;
	register struct qv_info *qp = qv_scn;

	unit = minor(dev);
	qv = unit >> 2;
	if (unit >= nqv || (ui = qvinfo[qv])== 0 || ui->ui_alive == 0)
		return (ENXIO);
	tp = &qv_tty[unit];
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	if (tp->t_state&TS_XCLUDE && u.u_uid!=0)
		return (EBUSY);
#endif	MACH_KERNEL
	qvaddr = (struct qvdevice *)ui->ui_addr;
        qv_scn->qvaddr = qvaddr;
	tp->t_addr = (caddr_t)qvaddr;
	tp->t_oproc = qvstart;
#ifdef	MACH_KERNEL
	tp->t_stop = qvstop;
#endif	MACH_KERNEL

	if ((tp->t_state&TS_ISOPEN) == 0) {
		ttychars(tp);
		tp->t_state = TS_ISOPEN|TS_CARR_ON;
		tp->t_ispeed = B9600;
		tp->t_ospeed = B9600;
		if( unit == 0 ) {
			/* make sure keyboard is always back to default */
			qvkbdreset();
			qvaddr->qv_csr |= QV_INT_ENABLE;
			tp->t_flags = XTABS|EVENP|ECHO|CRMOD;
#ifndef	MACH_KERNEL
			tp->t_ttyloc.tlc_hostid = TLC_MYHOST;
			tp->t_ttyloc.tlc_ttyid = TLC_DISPLAY;
#endif	MACH_KERNEL
		} else 
			tp->t_flags = RAW;
	}
	/*
	 * Process line discipline specific open if its not the
	 * mouse channel. For the mouse we init the ring ptr's.
	 */
	if( ( unit % 4 ) != QVMOUSECHAN )
#ifdef	MACH_KERNEL
		return (char_open(dev, tp, flag, ior));
#else	MACH_KERNEL
		return ((*linesw[tp->t_line].l_open)(dev, tp));
#endif	MACH_KERNEL
	else {
		mouseon = 1;
		/* set up event queue for later */
		qp->ibuff = (vsEvent *)qp - QVMAXEVQ;
		qp->iqsize = QVMAXEVQ;
		qp->ihead = qp->itail = 0;
		return 0;
	}
}

/*
 * Close a QVSS line.
 */
/*ARGSUSED*/
qvclose(dev, flag)
	dev_t dev;
	int flag;
{
	register struct tty *tp;
	register unit;
	register struct qvdevice *qvaddr;

	unit = minor(dev);
	tp = &qv_tty[unit];

	/*
	 * If this is the keyboard unit (0) shutdown the
	 * interface.
	 */
	qvaddr = (struct qvdevice *)tp->t_addr;
	if( unit == 0 )
		qvaddr->qv_csr &= ~QV_INT_ENABLE;

	/*
	 * If unit is not the mouse channel call the line disc.
	 * otherwise clear the state flag, and put the keyboard into down/up.
	 */
	if( ( unit % 4 ) != QVMOUSECHAN ){
#ifdef	MACH_KERNEL
	    {
		int	s = spltty();
		simple_lock(&tp->t_lock);
		ttyclose(tp);
		simple_unlock(&tp->t_lock);
		splx(s);
	    }
#else	MACH_KERNEL
		(*linesw[tp->t_line].l_close)(tp);
		ttyclose(tp);
#endif	MACH_KERNEL
	} else {
/*		register struct qv_info *qp = qv_scn; */
		mouseon = 0;
		/* reset up event queue for later */
/*		qp->ibuff = (vsEvent *)qp - QVMAXEVQ;
		qp->iqsize = QVMAXEVQ;
		qp->ihead = qp->itail = 0;
*/		qvaddr->qv_csr |= QV_CUR_MODE;
	}
	tp->t_state = 0;
}

qvread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp;
	int unit = minor( dev );

	if( (unit % 4) != QVMOUSECHAN ) {
		tp = &qv_tty[unit];
		return ((*linesw[tp->t_line].l_read)(tp, uio));
	}
#ifdef	MACH_KERNEL
	return (qvmouseread(dev, uio));
#else	MACH_KERNEL
	return (ENXIO);
#endif	MACH_KERNEL
}

qvwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct tty *tp;
	int unit = minor( dev );

	/*
	 * If this is the mouse we simply fake the i/o, otherwise
	 * we let the line disp. handle it.
	 */
	if( (unit % 4) == QVMOUSECHAN ){
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
		uio->uio_offset = uio->uio_resid;
		uio->uio_resid = 0;
#endif	MACH_KERNEL
		return 0;
	}
	tp = &qv_tty[unit];
	return ((*linesw[tp->t_line].l_write)(tp, uio));
}


#ifdef	MACH_KERNEL
/*
 * Read mouse.  If no events, wait for them (even if
 * count is 0).
 */
qvmouseread(dev, ior)
	dev_t	dev;
	register io_req_t ior;
{
	register int	s = spl5();
	register struct qv_info *qp = qv_scn;

	if (qp->ihead != qp->itail) {
	    splx(s);
	    return (D_SUCCESS);
	}
	ior->io_dev_ptr = (char *)qp;
	ior->io_done = mouse_read_done;
	enqueue_tail(&mouse_read_queue, (queue_entry_t)ior);
	splx(s);
	return (D_IO_QUEUED);
}

boolean_t mouse_read_done(ior)
	register io_req_t	ior;
{
	register struct qv_info *qp = (struct qv_info *)ior->io_dev_ptr;
	register int	s = spl5();

	if (qp->ihead != qp->itail) {
	    splx(s);
	    (void) ds_read_done(ior);
	    return (TRUE);
	}
	enqueue_tail(&mouse_read_queue, (queue_entry_t)ior);
	splx(s);
	return (FALSE);
}

#else	MACH_KERNEL
/*
 * Mouse activity select routine
 */
qvselect(dev, rw)
dev_t dev;
{
	register int s = spl5();
	register int unit = minor(dev);
	register struct qv_info *qp = qv_scn;

	if( (unit % 4) == QVMOUSECHAN )
		switch(rw) {
		case FREAD:			/* if events okay */
			if(qp->ihead != qp->itail) {
				splx(s);
				return(1);
			}
			rsel = current_thread();
			splx(s);
			return(0);
		case FWRITE:			/* can never write */
			splx(s);
			return(EACCES);
		}
	else
		return( ttselect(dev, rw) );
	splx(s);
	return(0);
}
#endif	MACH_KERNEL
		
/*
 * QVSS keyboard interrupt.
 */
qvkint(qv)
	int qv;
{
	struct tty *tp;
	register c;
	struct uba_device *ui;
	register int key;
	register int i,j;
	int k,l;

	if (qv_rpollc)
		return;
	ui = qvinfo[qv];
	if (ui == 0 || ui->ui_alive == 0)
		return;
	tp = &qv_tty[qv<<2];
	/* 
	 *  Get a character from the keyboard.
	 */
	if ((((struct qvdevice *)ui->ui_addr)->qv_uartstatus&1) == 0)
	    return;

	((struct qvdevice *)ui->ui_addr)->qv_csr |= QV_VIDEO_ENA;
	qvktime = time.tv_sec;

	key = c = qvgetc((struct qvdevice *)ui->ui_addr, ui->ui_unit);
	if (c < 0)
		return;
	/*
	 * See if its a state change key
	 */
	if( mouseon == 0) {
#if	MACH_KDB
		/* 
		 *  If the character is the kernel debugger keyboard interrupt
		 *  character, request a keyboard trap into the debugger and
		 *  discard.
		 */
		if (c == 0215) {	/* long oblong key beside HELP */
			kdb_kintr();
			return;
		}
#endif	MACH_KDB

		/*
		 * Check for special function keys
		 */
		if( c & 0x80 ) {
			register char *string;
			string = qv_special[ c & 0x7f ];
			while( *string )
			(*linesw[tp->t_line].l_rint)(*string++, tp);
		} else
			(*linesw[tp->t_line].l_rint)(c, tp);
	} else {
		/*
		 * Mouse channel is open put it into the event queue
		 * instead.
		 */
		register struct qv_info *qp = qv_scn;
		register vsEvent *vep;
		u_short toy;
#if	MACH_KDB
		/* 
		 *  If the character is the kernel debugger keyboard interrupt
		 *  character, request a keyboard trap into the debugger and
		 *  discard.
		 */
		if (((u_char) qv_key[key]) == 0215)
					/* long oblong key beside HELP */
		{
			qv_init(qp->qvaddr);
			kdb_kintr();
			return;
		}
#endif	MACH_KDB
		toy = TOY;	/* get current time */

		switch(key) {
		case REPEAT:
			key = qv_keyboard.lastcode;
			if ((i = EVROUND(qp->itail+1)) == qp->ihead) return;
			vep = &qp->ibuff[qp->itail];
			vep->vse_type = VSE_BUTTON;
			vep->vse_device = VSE_DKB;
			vep->vse_x = qp->mouse.x;
			vep->vse_y = qp->mouse.y;
			vep->vse_time = toy;
			vep->vse_direction = VSE_KBTDOWN;
			vep->vse_key = key;
			qp->itail = i;
			break;
		case ALLUP:
			/*
			 * We don't use the macro because it would force us
			 * to test bit by bit. This method only makes us
			 * look at words that actually have something in them.
			 *
			 * Don't actually like the format of the following
			 * code but don't want to run off the screen.
			 */
			for( i=0 ; i<8 ; i++ ) if( k = qv_keyboard.kup[ i ] )
				for( j=0 ; j<32 && k ; j++, k >>= 1 ) if( k & 1 ) { 
					if ((l = EVROUND(qp->itail+1)) == qp->ihead) 
						break;
					vep = &qp->ibuff[qp->itail];
					vep->vse_direction = VSE_KBTDOWN;
					vep->vse_type = VSE_BUTTON;
					vep->vse_device = VSE_DKB;
					vep->vse_x = qp->mouse.x;
					vep->vse_y = qp->mouse.y;
					vep->vse_time = toy;
					key = (i << 5) + j;
					vep->vse_direction = VSE_KBTUP;
					vep->vse_key = key;
					qp->itail = l;
				}
			qv_keyboard.lastcode = key;
			KUP(qv_keyboard.kup);
			break;

		default:
			if ((i = EVROUND(qp->itail+1)) == qp->ihead) return;
			vep = &qp->ibuff[qp->itail];
			vep->vse_direction = VSE_KBTDOWN;
			vep->vse_type = VSE_BUTTON;
			vep->vse_device = VSE_DKB;
			vep->vse_x = qp->mouse.x;
			vep->vse_y = qp->mouse.y;
			vep->vse_time = toy;
			qv_keyboard.lastcode = key;
			if(KTEST(qv_keyboard.dkeys,key)) {
				if(KTEST(qv_keyboard.kup,key)) {
					vep->vse_direction = VSE_KBTUP;
				}
				KINVERT(qv_keyboard.kup,key);
			}
			else 	KSET(qv_keyboard.kup,key);
			vep->vse_key = key;
			qp->itail = i;
		}
#ifdef	MACH_KERNEL
		{
		    register io_req_t	ior;
		    while ((ior = (io_req_t)dequeue_head(&mouse_read_queue))
			    != 0)
			iodone(ior);
		}
#else	MACH_KERNEL
		if(rsel) {
			selwakeup(rsel,0);
			rsel = 0;
		}
#endif	MACH_KERNEL
	}
}

/*
 * Ioctl for QVSS.
 */
#ifdef	MACH_KERNEL
int
qvportdeath(dev, port)
	dev_t	dev;
	mach_port_t port;
{
	return (tty_portdeath(&qv_tty[minor(dev)], port));
}

io_return_t qvgetstat(dev, flavor, data, count)
	dev_t		dev;
	int		flavor;
	int *		data;		/* pointer to OUT array */
	unsigned int	*count;		/* out */
{
	int unit = minor(dev);
	int qv = unit >> 2;
	struct uba_device *ui;
	register struct qv_info *qp;

	if (unit >= nqv || (ui = qvinfo[qv]) == 0 || ui->ui_alive == 0)
	    return (ENXIO);

	qp = qv_scn;
	switch (flavor) {
	    case QIOCGINFO:
		/*
		 * Return screen info.
		 */
		*(struct qv_info *)data = *qp;
		*count = sizeof(struct qv_info)/sizeof(int);
		break;

	    case QIOCADDR:
		/*
		 * Return pointer to screen info mapped to user space.
		 */
		*(struct qv_info **)data = qp;
		*count = 1;
		break;

	    default:
		/*
		 * Try as a tty
		 */
		return (tty_get_status(&qv_tty[unit], flavor, data, count));
	}
	return (0);
}

io_return_t qvsetstat(dev, flavor, data, count)
	dev_t		dev;
	int		flavor;
	int *		data;
	unsigned int	count;
{
	int unit = minor(dev);
	int qv = unit >> 2;
	struct uba_device *ui;
	register struct qv_info *qp;

	if (unit >= nqv || (ui = qvinfo[qv]) == 0 || ui->ui_alive == 0)
	    return (ENXIO);

	qp = qv_scn;
	switch (flavor) {
	    case QIOCSMSTATE:
		if (count < sizeof(vsCursor)/sizeof(int))
		    return (EINVAL);
		qp->mouse = *(vsCursor *)data;
		qv_pos_cur(qp->mouse.x, qp->mouse.y);
		break;

	    case QIOCINIT:
		qp->char_invert = 0;
		qv_init(qp->qvaddr);
		break;

	    case QIOCKPCMD:
	    {
		register struct qv_kpcmd *qk;
		register unsigned char *cp;
		register int nbytes;

		if (count < 1)
		    return (EINVAL);
		qk = (struct qv_kpcmd *)data;
		nbytes = qk->nbytes;
		if ((nbytes+2 + 3)>>2 > count)
		    return (EINVAL);

		if (nbytes == 0)
		    qk->cmd |= 0200;	/* end of command string */
		qv_key_out((char)(qk->cmd | !mouseon));
			/* force peripheral command if mouse is off */
		cp = &qk->par[0];
		while (nbytes-- > 0) {
		    if (nbytes <= 0)
			qv_key_out((char)*cp++ | 0200);
					/* end of command string */
		    else
			qv_key_out((char)*cp++);
		}
		break;
	    }

	    default:
		/*
		 * Try as tty ioctl
		 */
		return (tty_set_status(&qv_tty[unit], flavor, data, count));
	}
	return (0);
}

#else	MACH_KERNEL
/*ARGSUSED*/
qvioctl(dev, cmd, data, flag)
	dev_t dev;
	register caddr_t data;
{
	int unit = minor(dev);
	int qv = unit >> 2;
	struct uba_device *ui;
	register struct qvdevice *qvaddr;
	register struct qv_info *qp = qv_scn;
 
	/*
	 * Check for and process qvss specific ioctl's
	 */
	if (unit >= nqv || (ui = qvinfo[qv]) == 0 || ui->ui_alive == 0)
		return (ENXIO);
	qvaddr = (struct qvdevice *)ui->ui_addr;

	switch( cmd ) {
	case QIOCGINFO:					/* return screen info */
		bcopy((caddr_t)qp, data, sizeof (struct qv_info));
		break;

	case QIOCSMSTATE:				/* set mouse state */
		qp->mouse = *((vsCursor *)data);
		qv_pos_cur( qp->mouse.x, qp->mouse.y );
		break;

	case QIOCREVERSE:
		qv_reverse_video = (* (int *) data) ? 1 : 0;
	case QIOCINIT:					/* init screen	*/
		qp->char_invert = 0;
		qv_init( qp->qvaddr );
		break;

	case QIOCSETUP:
		qv_new_setup(qp->qvaddr, (* (int *) data));
		break;

	case QIOCKPCMD:	{/* no mode changes permitted, as can cause trouble */
			register struct qv_kpcmd *qk;
			register unsigned char *cp;
		qk = (struct qv_kpcmd *)data;
		if(qk->nbytes == 0) qk->cmd |= 0200;
		qv_key_out((char)(qk->cmd | !mouseon));	
			/* force peripheral command if mouse is off */
		cp = &qk->par[0];
		while(qk->nbytes-- > 0) {	/* terminate parameters */
			if(qk->nbytes <= 0) *cp |= 0200;
			qv_key_out((char)*cp++);
		}
		break;
	}
	case QIOCADDR:					/* get struct addr */
		*(struct qv_info **) data = qp;
		break;
	case QIOCLIGHT:
		break;
	case QIOCMOUSE:
		qv_mouse_scale = qv_mouse_interval = * (int *) data;
		break;
	case QIOCCURSORICON: {
			register int i;
		for (i=0; i<16; i++) {
			qp->cursorbits[i] = ((unsigned short *)data)[i];
			qp->cursor_icon.data[i] = ((unsigned short *)data)[i];
		}
		break;
	}
	case QIOCFADE:	{ register int tm = * (int *) data;
		untimeout(qvktimer, (caddr_t) qvaddr);	/* stop everything */
		if (tm == -1) 				/* turn it off */
							/* well dont turn it on*/
			break;
		if (tm < QVKTIMEMIN)
			tm = QVKTIMEMIN;
		qvktimelim = tm;
		qvktime = time.tv_sec;
		qvktimer(qvaddr);
		break;
	}
	case QIOCCURSOR:{
	    		register int tm = * (int *) data;
		if (!tm || tm == -1) {
			qvvon = 0;
			qvvcurson = qvvcursoff = 1;
		} else if (tm > 0) {
			qvvon = 1;
			qvvcurson = qvvcursoff = tm;
		} else {
			u.u_error = EINVAL;
		}
setcursor:
		if (qvvon >= 0) {
			qvvcurs = qvvcurson;
 			qvcurcopy(qp->cursor_icon.data, qp->cursorbits);
		} else {
			qvvcurs = qvvcursoff;
			qvcurzero(qp->cursorbits);
		}
		break;
	}
	case QIOCCURSORON:{
			register int tm = * (int *) data;
		if (!tm || tm == -1) {
			qvvon = 0;
			qvvcurson = 1;
		} else if (tm > 0) {
			qvvon = 1;
			qvvcurson = tm;
		} else {
			u.u_error = EINVAL;
		}
		if (qvvon)
			goto setcursor;
		else
			qvcurzero(qp->cursorbits);
		break;
	}
	case QIOCCURSOROFF:{
			register int tm = * (int *) data;
		if (!tm || tm == -1) {
			qvvon = 0;
			qvvcursoff = 1;
		} else if (tm > 0) {
			qvvon = 1;
			qvvcursoff = tm;
		} else {
			u.u_error = EINVAL;
		}
		if (qvvon)
			goto setcursor;
		else
			qvcurcopy(qp->cursor_icon.data, qp->cursorbits);
		break;
	}
	case QIOCLEDPATTERN:{
			register int ptn = * (int *) data;
		if (ptn != LED_OFF && ptn != LED_COUNT &&
				      ptn != LED_ROTATE && ptn != LED_CYLON ) {
			u.u_error = EINVAL;
		} else {
			led_pattern = ptn;
		}
		break;
	}
	case QIOCLEDINTERVAL:{
			register int lcnt = * (int *) data;
		if (lcnt < 1)
			lcnt = 1;
		led_interval = lcnt;
		break;
	}
	default:	{				/* not ours ??  */
			register struct tty *tp;
			int error;

		tp = &qv_tty[unit];
		error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
		if (error >= 0)
			return (error);
		error = ttioctl(tp, cmd, data, flag);
		if (error >= 0) {
			return (error);
		}
		break;
	}
	}
	return (0);
}
#endif	MACH_KERNEL
/*
 * Initialize the screen and the scanmap
 */
qv_init(qvaddr)
struct qvdevice *qvaddr;
{
	register short *scanline;
	register int i;
	register short scan;
	register char *ptr;
	register struct qv_info *qp = qv_scn;

	/*
	 * Clear the bit map
	 */
	for( i=0 , ptr = qp->bitmap ; i<240 ; i += 2 , ptr += 2048)
		bzero( ptr, 2048 );
	/*
	 * Reinitialize the scanmap
	 */
        scan = qvaddr->qv_csr & QV_MEM_BANK;
        scanline = qp->scanmap;
        for(i = 0 ; i < qp->max_y ; i++ )
                *scanline++ = scan++;

	/*
	 * Home the cursor
	 */
	qp->row = qp->col = 0;

	/*
	 * Reset the cursor to the default type.
	 */
	qvaddr->qv_csr |= QV_CUR_MODE;
	/*
	 * Reset keyboard to default state.
	 */
	qvkbdreset();
}

qvreset()
{
}
qvkbdreset()
{
	register int i;
	qv_key_out(LK_DEFAULTS);
	for( i=1 ; i < 15 ; i++ )
		qv_key_out( divdefaults[i] | (i<<3));
	for (i = 0; i < KBD_INIT_LENGTH; i++)
		qv_key_out(kbdinitstring[i]);
}

#define abs(x) (((x) > 0) ? (x) : (-(x)))
/*
 * QVSS vertical sync interrupt
 */
qvvint(qv)
	int qv;
{

	register struct qvdevice *qvaddr;
	struct uba_device *ui;
	register struct qv_info *qp = qv_scn;
	int unit;
	struct tty *tp0;
	int i;
	register int j;
#ifndef	lint
	int	foo;	/* prevent compiler schain botch bug */
#endif	lint
	/*
	 * Mouse state info
	 */
	static unsigned short omouse = 0, nmouse = 0;
	static char omx=0, omy=0, mx=0, my=0, om_switch=0, m_switch=0;

	/*
	 * Test and set the qv_ipl_lo flag. If the result is not zero then
	 * someone else must have already gotten here.
	 */
	if( --qv_ipl_lo )
		return;
	(void) spl4();
	ui = qvinfo[qv];
	unit = qv<<2;
	qvaddr = (struct qvdevice *)ui->ui_addr;
	if (qvvon != 0 && --qvvcurs <= 0) {
		if (qvvon < 0) {
			qvvon = 1;
			qvvcurs = qvvcurson;
			QVCURCOPY(qp->cursor_icon.data, qp->cursorbits);
		} else {
			qvvon = -1;
			qvvcurs = qvvcursoff;
			QVCURZERO(qp->cursorbits);
		}
	}
	tp0 = &qv_tty[(unit % 4 )+QVMOUSECHAN];
	/*
	 * See if the mouse has moved.
	 */
	if( omouse != (nmouse = qvaddr->qv_mouse) ) {
		register int dx, dy;

		omouse = nmouse;
		mx = nmouse & 0xff;
		my = nmouse >> 8;
		dy = my - omy; omy = my;
		dx = mx - omx; omx = mx;
		if( dy < 50 && dy > -50 && dx < 50 && dx > -50 ) {
			register vsEvent *vep;
			if( qp->mscale < 0 ) {	/* Ray Lanza's original */
				if( dy < 0 )
					dy = -( dy * dy );
				else
					dy *= dy;
				if( dx < 0 )
					dx = -( dx * dx );
				else
					dx *= dx;
			}
			else {			/* Vs100 style, see WGA spec */
			    int thresh = qp->mthreshold;
			    int scale  = qp->mscale;
			    if( abs(dx) > thresh ) {
				if ( dx < 0 )
				    dx = (dx + thresh)*scale - thresh;
				else
				    dx = (dx - thresh)*scale + thresh;
			    }
			    if( abs(dy) > thresh ) {
				if ( dy < 0 )
				    dy = (dy + thresh)*scale - thresh;
				else
				    dy = (dy - thresh)*scale + thresh;
			    }
			}
			qp->mouse.x += dx;
			qp->mouse.y -= dy;
			if( qp->mouse.x < 0 )
				qp->mouse.x = 0;
			if( qp->mouse.y < 0 )
				qp->mouse.y = 0;
			if( qp->mouse.x > qp->max_cur_x )
				qp->mouse.x = qp->max_cur_x;
			if( qp->mouse.y > qp->max_cur_y )
				qp->mouse.y = qp->max_cur_y;
			if( tp0->t_state & TS_ISOPEN )
				qv_pos_cur( qp->mouse.x, qp->mouse.y );
			if (qp->mouse.y < qp->mbox.bottom &&
			    qp->mouse.y >=  qp->mbox.top &&
			    qp->mouse.x < qp->mbox.right &&
			    qp->mouse.x >=  qp->mbox.left) goto switches;
			qp->mbox.bottom = 0;	/* trash box */
			if (EVROUND(qp->itail+1) == qp->ihead)
				goto switches;
			i = EVROUND(qp->itail - 1);
			if ((qp->itail != qp->ihead) &&	(i != qp->ihead)) {
				vep = & qp->ibuff[i];
				if(vep->vse_type == VSE_MMOTION) {
					vep->vse_x = qp->mouse.x;
					vep->vse_y = qp->mouse.y;
					goto switches;
				}
			}
			/* put event into queue and do select */
			vep = & qp->ibuff[qp->itail];
			vep->vse_type = VSE_MMOTION;
			vep->vse_time = TOY;
			vep->vse_x = qp->mouse.x;
			vep->vse_y = qp->mouse.y;
			qp->itail = EVROUND(qp->itail+1);
		}
	}
	/*
	 * See if mouse switches have changed.
	 */
switches:if( om_switch != ( m_switch = (qvaddr->qv_csr & QV_MOUSE_ANY) >> 8 ) ) {
		qp->mswitches = ~m_switch & 0x7;
		for (j = 0; j < 3; j++) {	/* check each switch */
			register vsEvent *vep;
			if ( ((om_switch>>j) & 1) == ((m_switch>>j) & 1) )
				continue;
			/* check for room in the queue */
			if ((i = EVROUND(qp->itail+1)) == qp->ihead) {
				qv_ipl_lo = 1;
				return;
			}
			/* put event into queue and do select */
			vep = &qp->ibuff[qp->itail];
			vep->vse_type = VSE_BUTTON;
			vep->vse_key = 2 - j;
			vep->vse_direction = VSE_KBTDOWN;
			if ( (m_switch >> j) & 1)
				vep->vse_direction = VSE_KBTUP;
			vep->vse_device = VSE_MOUSE;
			vep->vse_time = TOY;
			vep->vse_x = qp->mouse.x;
			vep->vse_y = qp->mouse.y;
		}
		qp->itail =  i;
		om_switch = m_switch;
		qp->mswitches = m_switch;
	}
#ifdef	MACH_KERNEL
	if (qp->ihead != qp->itail)
	{
	    register io_req_t	ior;
	    while ((ior = (io_req_t)dequeue_head(&mouse_read_queue))
		    != 0)
		iodone(ior);
	}
#else	MACH_KERNEL
	/* if we have proc waiting, and event has happened, wake him up */
	if(rsel && (qp->ihead != qp->itail)) {
		selwakeup(rsel,0);
		rsel = 0;
	}
#endif	MACH_KERNEL
	if (led_interval) {			/* leds are on */
		if (led_light_count <= 0) {		/* hit this lights */

			if (led_lights <= 0) led_lights = 1;	/* sanity */
			if (led_lights > 16) led_lights = 16;	/* sanity */
			led_light_count = led_interval;	/* reset */
			qv_key_out(LK_LED_DISABLE);
			qv_key_out(LED_1 + led_lights - 1);
			switch (led_pattern) {
			case LED_OFF:
				led_interval = 0;	/* since you can now set */
				break;			/* the interval even if off */
			case LED_COUNT:
				led_lights++;
				if (led_lights > 16) led_lights = 1;
				break;
			case LED_ROTATE:
				led_lights <<= 1;
				if (led_lights > 8) led_lights = 1;
				break;
			case LED_CYLON:
				if (led_increasing) {
					led_lights <<= 1;
					if (led_lights > 8) {
						led_lights >>= 2;
						led_increasing = 0;
					}
				} else {
					led_lights >>= 1;
					if (led_lights <= 0) {
						led_lights = 2;
						led_increasing = 1;
					}
				}
				break;
			}
			qv_key_out(LK_LED_ENABLE);
			qv_key_out(LED_1 + led_lights - 1);
		}
		led_light_count--;
	} else {
		if (led_lights) {
			qv_key_out(LK_LED_DISABLE);
			qv_key_out(LED_ALL);
			led_lights = 0;
		}
	}
	/*
	 * Okay we can take another hit now
	 */
	qv_ipl_lo = 1;
}

/*
 * qvstrayint - a stray interrupt catcher since two qvss like to
 *	interrupt together.  This services all the keyboards just
 *	to make sure that all keys are caught.
 */
qvstrayint(qv)
	int qv;
{
	int i=0;
	for (; i<NQV; i++) {
	    qvkint(i);
	}
}


/*
 *  qv_putc - virtual console character output routine
 */

qv_putc(c)
	register char c;
{
	static int isphys = 0;

	if (rpb.rp_flag && isphys == 0) {
	    /*
	     *  Switch to physical CSR address if called from RPB.
	     */
	    register struct pte *sbr = (struct pte *)mfpr(SBR);

#define	qvvtop(addr)	(ptob(sbr[btop(((int)addr)&~0x80000000)].pg_pfnum) \
			 +(((int)addr)&(NBPG-1)))

	    qv_scn 	       = (struct qv_info *) qvvtop(qv_scn);
	    qv_scn->bitmap     = (char *)	    qvvtop(qv_scn->bitmap);
	    qv_scn->scanmap    = (short *)	    qvvtop(qv_scn->scanmap);
	    qv_scn->cursorbits = (short *)	    qvvtop(qv_scn->cursorbits);
	    qv_scn->qvaddr     = (struct qvdevice *)qvvtop(qv_scn->qvaddr);
#undef	qvvtop
	    isphys++;
	}
	qvputc(c);
	if (c == '\n')
		qvputc('\r');
}

/*
 * Start  transmission
 */
qvstart(tp)
	register struct tty *tp;
{
	register int unit, c;
	register struct tty *tp0;
	int s;

	unit = minor(tp->t_dev);
	tp0 = &qv_tty[(unit&0xfc)+1];
	unit &= 03;

	s = spl5();
	/*
	 * If it's currently active, or delaying, no need to do anything.
	 */
	if (tp->t_state&(TS_TIMEOUT|TS_BUSY|TS_TTSTOP))
		goto out;
	/*
	 * Display chars until the queue is empty, if the second subchannel
	 * is open direct them there. Drop characters from subchannels other
	 * than 0 on the floor.
	 */

	while( tp->t_outq.c_cc ) {
		c = getc(&tp->t_outq);
		if( (unit & 0x03)  == 0 )
			if( tp0->t_state & TS_ISOPEN ){
				(*linesw[tp0->t_line].l_rint)(c, tp0);
			} else
				qvputc( c & 0xff );
	}
	/*
	 * Position the cursor to the next character location.
	 */
	if (!mouseon)
		qv_pos_cur( qv_scn->col*8, qv_scn->row*15 );

	/*
	 * If there are sleepers, and output has drained below low
	 * water mark, wake up the sleepers.
	 */
	if ( tp->t_outq.c_cc<=TTLOWAT(tp) ) {
#ifdef	MACH_KERNEL
		tt_write_wakeup(tp);
#else	MACH_KERNEL
		if (tp->t_state&TS_ASLEEP){
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
#endif	MACH_KERNEL
	}
	tp->t_state &= ~TS_BUSY;
out:
	splx(s);
}

/*
 * Stop output on a line, e.g. for ^S/^Q or output flush.
 */
/*ARGSUSED*/
qvstop(tp, flag)
	register struct tty *tp;
{
	register int s;
	/*
	 * Block input/output interrupts while messing with state.
	 */
	s = spl5();
	if (tp->t_state & TS_BUSY) {
		if ((tp->t_state&TS_TTSTOP)==0) {
			tp->t_state |= TS_FLUSH;
		} else
			tp->t_state &= ~TS_BUSY;
	}
	splx(s);
}

/*
 * Routine to display a character on the screen.  The model used is a 
 * glass tty.  It is assummed that the user will only use this emulation
 * during system boot and that the screen will be eventually controlled
 * by a window manager.
 *
 * Note that the name is qvputc. This is the virtual console output routine
 * and must be called by this name. The routine is called by cnputc if
 * v_console is true.
 */
qvputc( c )
register char c;
{

	register char *b_row, *f_row;
	register int i;
	register short *scanline;
	register int ote = 128;
	register struct qv_info *qp = qv_scn;

	/*
	 *  Enable the display video on any output.  Since the screen
	 *  has changed, we must display it.
	 */
	qp->qvaddr->qv_csr |= QV_VIDEO_ENA;
	qvktime = time.tv_sec;
	c &= 0x7f;

	switch ( c ) {
	case '\t':				/* tab		*/
		for( i = 8 - (qp->col & 0x7) ; i > 0 ; i-- )
			qvputc( ' ' );
		break;

	case '\r':				/* return	*/
		qp->col = 0;
		break;

	case '\010':				/* backspace	*/
		if( --qp->col < 0 )
			qp->col = 0;
		break;

	case '\n':				/* linefeed	*/
		if( qp->row+1 >= qp->max_row )
			qvscroll();
		else
			qp->row++;
		/*
		* Position the cursor to the next character location.
		*/
		if (!mouseon)
			qv_pos_cur( qp->col*8, qp->row*15 );
		break;

	case '\007':				/* bell		*/
                /*
                 * We don't do anything to the keyboard until after
                 * autoconfigure.
                 */
		if( qp->qvaddr )
			qv_key_out( LK_RING_BELL );
		return;

	default:
		if( c >= ' ' && c <= '~' ) {
                        scanline = qp->scanmap;
                        b_row = qp->bitmap+(scanline[qp->row*15]&0x3ff)*128+qp->col;
			i = c - ' ';
			if( i < 0 || i > 95 )
				i = 0;
			else
				i *= 15;
			f_row = (char *)((int)qv_font + i);
		
/*			for( i=0 ; i<15 ; i++ , b_row += 128, f_row++ )
				*b_row = *f_row;*/
			/* inline expansion for speed */
			if (qp->char_invert) {
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
				*b_row = ~(*f_row++); b_row += ote;
			}
			else {
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
				*b_row = *f_row++; b_row += ote;
			}

			if( ++qp->col >= qp->max_col ) {
				qp->col = 0 ;
				if( qp->row+1 >= qp->max_row )
					qvscroll();
				else
					if (qp->row != -1)
						qp->row++;
			}
		}
		break;
	}
}

/* 
 *  qv_getc - get character from QVSS keyboard.
 *
 */
qv_getc()
{
	register struct qvdevice *addr = qv_scn->qvaddr;
	int	c;

	/*
	 *	Wait for a key.
	 */
	do {
		while ((addr->qv_uartstatus&1) == 0)
			;
		c = qvgetc(addr, 0);
	} while (c == -1);
	return(c);
}

/*
 *  qv_maygetc - get character from keyboard, or return -1 if none available.
 */
qv_maygetc()
{
	register struct qvdevice *addr = qv_scn->qvaddr;

	if ((addr->qv_uartstatus & 1) == 0)
		return (-1);
	return (qvgetc(addr, 0));
}

/* 
 *  qvgetc - get next character from keyboard
 *
 *  This routine is called either from qvkint() after a keyboard interrupt has
 *  occurred or from vgetc() when a keyboard character poll succeeds.  In
 *  either case, there is now a character available in the keyboard UART and it
 *  is read.  After checking for keyboard errors, the character is translated
 *  to its conventional ASCII representation (if it is not a special function
 *  key).  If the mouse is active and console input polling is not active, no
 *  keyboard character translation is performed.
 *
 *  Return:  The (possibly translated) character or -1 if no character is
 *  available (or the character was processed internally, e.g. SHIFT, CTRL,
 *  etc.).
 */
 
qvgetc(addr, unit)
	register struct qvdevice *addr;
{
	register int key;
	register int c;
 
	/*
	 * Get a character from the keyboard.
	 */
	key = addr->qv_uartdata & 0xff;
 
	/*
	 * Check for various keyboard errors
	 */
	if( key == LK_POWER_ERROR || key == LK_KDOWN_ERROR ||
	    key == LK_INPUT_ERROR || key == LK_OUTPUT_ERROR) {
			mprintf("qv%d: Keyboard error, code = %x\n",unit,key);
			return(-1);
	}
	if( key < LK_LOWEST ) return(-1);
 
	if (mouseon && qv_rpollc == 0)
		return(key);
 
	switch ( key ) {
	case LOCK:
		qv_keyboard.lock ^= 0xffff;	/* toggle */
		if( qv_keyboard.lock )
			qv_key_out( LK_LED_ENABLE );
		else
			qv_key_out( LK_LED_DISABLE );
		qv_key_out( LED_3 );
		return(-1);
	case SHIFT:
		qv_keyboard.shift ^= 0xffff;
		return(-1);	
	case CNTRL:
		qv_keyboard.cntrl ^= 0xffff;
		return(-1);
	case ALLUP:
		qv_keyboard.cntrl = qv_keyboard.shift = 0;
		return(-1);
	case REPEAT:
		c = qv_keyboard.last;
		break;
	default:
		/*
		 * Test for control characters. If set, see if the character
		 * is eligible to become a control character.
		 */
		if (qv_keyboard.lock || qv_keyboard.shift)
			c = qv_shift_key[key];
		else
			c = qv_key[key];
		if (qv_keyboard.cntrl) {
			if (c >= '@' && c <= '~')
				c &= 0x1f;
		}
	}
 
	qv_keyboard.last = c;
	qv_keyboard.lastcode = key;
 
	return((u_char)c);
}
 
/*
 *  Virtual console set/clear receive character polling mode
 */

qv_pollc(flag)
{
	if (flag)
		qv_rpollc++;
	else
		qv_rpollc--;
}

/*
 * Position the cursor to a particular spot.
 */
qv_pos_cur( x, y)
register int x,y;
{
	register struct qvdevice *qvaddr;
	register struct qv_info *qp = qv_scn;

	if( qvaddr = qp->qvaddr ) {
		if( y < 0 || y > qp->max_cur_y )
			y = qp->max_cur_y;
		if( x < 0 || x > qp->max_cur_x )
			x = qp->max_cur_x;
		qp->cursor.x = x;		/* keep track of real cursor*/
		qp->cursor.y = y;		/* position, indep. of mouse*/

		qvaddr->qv_crtaddr = 10;	/* select cursor start reg */
		qvaddr->qv_crtdata = y & 0xf;
		qvaddr->qv_crtaddr = 11;	/* select cursor end reg */
		qvaddr->qv_crtdata = y & 0xf;
		qvaddr->qv_crtaddr = 14;	/* select cursor y pos. */
		qvaddr->qv_crtdata = y >> 4;
		qvaddr->qv_xcur = x;		/* pos x axis	*/
		/*
		 * If the mouse is being used then we change the mode of
		 * cursor display based on the pixels under the cursor
		 */
		if( mouseon ) {
			register int l1 = qp->scanmap[y] & 0x7ff;
			register int l3 = qp->scanmap[y+2] & 0x7ff;

#define	bit_test(bit,loc) \
	    (((loc)[(bit)>>3] >> ((bit) & 0x7)) & 1)

			if ((bit_test(x, &qp->bitmap[l1*128]) |
				 bit_test(x+1, &qp->bitmap[l3*128]))
			    )
				qvaddr->qv_csr &= ~QV_CUR_MODE;
			else
				qvaddr->qv_csr |=  QV_CUR_MODE;
#undef	bit_test
		}
	}
}
/*
 * Scroll the bitmap by moving the scanline map words. This could
 * be done by moving the bitmap but it's much too slow for a full screen.
 * The only drawback is that the scanline map must be reset when the user 
 * wants to do graphics.
 */
qvscroll()
{
	short tmpscanlines[15];
	char *b_row;
	short *scanline;
	register struct qv_info *qp = qv_scn;

	/*
	 * If the mouse is on we don't scroll so that the bit map
	 * remains sane.
	 */
	if( mouseon ) {
		/*
		 * I'm tired of trying to debug while all of the old
		 * junk remains on the screen...
		 */
		register char *o_row, *n_row;
		register int i, last_row;

		scanline = qp->scanmap;
		last_row = qp->row * 15;

		/* copy the lines up (thru the scanline map) */
		for (i = 0; i < last_row; i++) {
			n_row = qp->bitmap + (scanline[i]&0x3ff)*128;
			o_row = qp->bitmap + (scanline[i+15]&0x3ff)*128;
			bcopy(o_row, n_row, 128);
		}
		/* zero the last character row */
		n_row = qp->bitmap + (scanline[last_row]&0x3ff)*128;
		bzero(n_row, 128*15);
		return;
	}
	/*
	 * Save the first 15 scanlines so that we can put them at
	 * the bottom when done.
	 */
	bcopy( (caddr_t)qp->scanmap, (caddr_t)tmpscanlines, sizeof tmpscanlines );

	/*
	 * Clear the wrapping line so that it won't flash on the bottom
	 * of the screen.
	 */
        scanline = qp->scanmap;
        b_row = qp->bitmap+(*scanline&0x3ff)*128;
	bzero( b_row, 1920 );

	/*
	 * Now move the scanlines down 
	 */
	bcopy( (caddr_t)(qp->scanmap+15), (caddr_t)qp->scanmap, (unsigned)(qp->row * 15) * sizeof (short) );

	/*
	 * Now put the other lines back
	 */
	bcopy( (caddr_t)tmpscanlines, (caddr_t)(qp->scanmap+(qp->row * 15)), sizeof tmpscanlines );
}

/*
 * Output to the keyboard. This routine status polls the transmitter on the
 * keyboard to output a code. The timer is to avoid hanging on a bad device.
 */
qv_key_out( c )
char c;
{
	int timer = 30000;
	register struct qv_info *qp = qv_scn;

	if( qp->qvaddr ) {
		while( (qp->qvaddr->qv_uartstatus & 0x4) == 0  && timer-- )
			;
		qp->qvaddr->qv_uartdata = c;
	}
}
/*
 * Virtual console initialization. This routine sets up the qvss so that it can
 * be used as the system console. It is invoked before autoconfig and has to do
 * everything necessary to allow the device to serve as the system console. 
 * In this case it must map the q-bus and device areas and initialize the qvss 
 * screen.
 */
qvcons_init()
{
#ifdef	MACH_KERNEL
	/*
	 * For the MACH kernel, the Qbus has already been mapped.
	 */
	struct qvdevice *qvaddr;

#define	QVSSCSR 017200

	/*
	 * Probe for the QVSS.
	 */
	qvaddr = (struct qvdevice *)(unibus_start[0]
				     + 4*1024*1024	/* device registers */
				     + QVSSCSR);
	if (badaddr((char *)qvaddr, sizeof(short)))
	    return;

	/*
	 * The QVSS exists - set it up.
	 */
	qv_setup(qvaddr);

	/*
	 * Show that the virtual console is in use, and redirect
	 * the console IO routines to call the QVSS.
	 */
	v_console = 1;
	vgetc = qv_getc;
	vputc = qv_putc;
	vpollc = qv_pollc;
	vmaygetc = qv_maygetc;

	/*
	 * Change the console device slot to point to the QVSS.
	 */
	dev_change_indirect("console", "qv", 0);

#else	MACH_KERNEL
        struct percpu *pcpu;            /* pointer to percpu structure  */
        struct qvdevice *qvaddr;        /* device pointer               */
        short *devptr;                  /* virtual device space         */
#define QVSSCSR 017200

        /*
         * Found an entry for this cpu. Because this device is Microvax specific
         * we assume that there is a single q-bus and don't have to worry about
         * multiple adapters.
         *
         * Map the bus memory and device registers.
         */
	if (unibus_start[0] == 0) {
		(void) kmem_alloc_pageable(kernel_map, &unibus_start[0],
					   (4*1024*1024)+8*1024);
		unibus_end[0] = unibus_start[0] + (4*1024*1024)+8*1024;
	}
	ioaccess((cpu == VAX_1) ? 0 : 0x30000000, unibus_start[0], (4*1024*1024));
	ioaccess(0x20000000, unibus_start[0] + (4*1024*1024), 8*1024);
	/*
	 *  The normal configuration is to automatically use the QVSS as the
	 *  system console (below) if it exists.  However, if the v_console
	 *  flag is already set in the system image at boot time, assume this
	 *  is not desired.  We can't make this check until after the memory
	 *  and device registers are mapped above since they will still be
	 *  needed by the rest of the driver code even if it is not the system
	 *  console.
	 *
	 *  The first entry in the watch chip RAM (following CPMBX) evidently
	 *  records the console state.  From experimentation, this value
	 *  has been observed as 0x66 or 0x60 when the display is the console
	 *  and 0x6 when the serial line unit is the console.  For now, we'll
	 *  guess that the 0x70 bits are significant and check those.
	 */
	if (v_console || (cldevice->wcram[0]&0x70) != 0x60)
	{
		v_console = 0;
		return;
	}
        /*
         * See if the qvss is there.
         */
	devptr = (short *)((char *)unibus_start[0]+4*1024*1024);
        qvaddr = (struct qvdevice *)((u_int)devptr + QVSSCSR);
        if( badaddr( (caddr_t)qvaddr, sizeof(short) ) )
                return;
        /*
         * Okay the device is there lets set it up
         */
        qv_setup( qvaddr );
	v_console = 1;
	{
		struct cdevsw	tcdevsw;

		tcdevsw = cdevsw[QVSSMAJOR];
		cdevsw[QVSSMAJOR] = cdevsw[0];
		cdevsw[0] = tcdevsw;
		vgetc = qv_getc;
		vputc = qv_putc;
		vpollc = qv_pollc;
		vmaygetc = qv_maygetc;
	}
#endif	MACH_KERNEL
}
/*
 * Do the board specific setup
 */
qv_setup( qvaddr )
struct qvdevice *qvaddr;
{
	qv_new_setup(qvaddr, qvmodel);
}
qv_new_setup(qvaddr, type)
struct qvdevice *qvaddr;
{
        char *qvssmem;                  /* pointer to the display mem   */
        int i;                          /* simple index                 */
	register struct qv_info *qp;

        qvssmem = (char *)
                (( (u_int)(qvaddr->qv_csr & QV_MEM_BANK) <<7 ) + (u_int)unibus_start[0]);
        qv_scn = (struct qv_info *)
                ((u_int)qvssmem + 251*1024);
	qp = qv_scn;
        if( (qvaddr->qv_csr & QV_19INCH))
		qv_def_scrn = (type >= QV260 ) ? 2 : 1;
	else
		qv_def_scrn = 0;
        *qv_scn = qv_scn_defaults[ qv_def_scrn ];
 	qp->bitmap = qvssmem;
        qvaddr->qv_csr &= ~QV_VIDEO_ENA ;
        qp->scanmap = (short *)((u_int)qvssmem + 254*1024);
        qp->cursorbits = (short *)((u_int)qvssmem + 256*1024-32);
	/* set up event queue for later */
	qp->ibuff = (vsEvent *)qp - QVMAXEVQ;
	qp->iqsize = QVMAXEVQ;
	qp->ihead = qp->itail = 0;

        /*
         * Setup the crt controller chip.
         */
        for( i=0 ; i<16 ; i++ ) {
                qvaddr->qv_crtaddr = i;
                qvaddr->qv_crtdata = qv_crt_parms[ qv_def_scrn ][ i ];
        }
	/*
	 * Setup the cursor bits once
	 */
	for( i=0 ; i<16 ; i++ ) {
		qp->cursorbits[i] = qv_cursor[i];
		qp->cursor_icon.data[i] = qv_cursor[i];
	}
	qvaddr->qv_csr |= QV_CUR_MODE;
	qv_init(qvaddr);
        /*
         * Turn on the video
         */
        qvaddr->qv_csr |= QV_VIDEO_ENA ;
	/*
	 *  Restore the CSR address which was wiped out in the assignment
	 *  above.
	 */
	qv_scn->qvaddr = qvaddr;
	/*
	 *  Initialize down/up bitmap
	 */
	for(i = LK_DIV6_START; i <= LK_DIV5_END; i++)
		KSET(qv_keyboard.dkeys,i);
}

/*
 *	Mapping routine for QVSS memory.
 */
int	qvmap(dev, off, prot)
	dev_t		dev;
	vm_offset_t	off;
	int		prot;
{
	int	unit, qv;
	register struct uba_device *ui;
	register struct qvdevice *qvaddr;
	vm_offset_t	qvssmem;

#ifdef	lint
	prot++;
#endif	lint

	/*
	 *	Doesn't assume only one QVSS.
	 */
	unit = minor(dev);
	qv = unit >> 2;
	if (unit >= nqv || (ui = qvinfo[qv]) == 0 || ui->ui_alive == 0)
		return (-1);

	if (off >= 256*1024)
		return (-1);

	qvaddr = (struct qvdevice *)ui->ui_addr;
	qvssmem = (vm_offset_t)(((qvaddr->qv_csr & QV_MEM_BANK) << 7)
				+ unibus_start[0]);

	/*
	 *	Want physical page number
	 */
	return (btop(pmap_extract(pmap_kernel(), qvssmem + off)));
}
#endif
