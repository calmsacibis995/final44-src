h19381
s 00001/00000/00708
d D 8.2 95/06/02 17:26:12 ralph 11 10
c final changes for pmax 4.4-Lite II release
e
s 00002/00002/00706
d D 8.1 93/06/10 22:39:01 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00043/00679
d D 7.9 93/04/05 21:35:25 ralph 9 8
c use vm_mmap instead of X kluge to map display into user address space.
e
s 00185/00674/00537
d D 7.8 92/11/15 15:49:02 ralph 8 7
c changes for maxine from Rick Macklem.
e
s 00003/00003/01208
d D 7.7 92/10/11 11:24:39 bostic 7 6
c use pmax as top directory, not mips
e
s 00017/00016/01194
d D 7.6 92/10/11 11:13:31 bostic 6 5
c make kernel includes standard
e
s 00006/00000/01204
d D 7.5 92/06/02 23:00:28 mckusick 5 4
c enable mouse and keyboard events for X11R4 (from Macklem)
e
s 00011/00000/01193
d D 7.4 92/03/15 19:20:01 ralph 4 3
c redirect tty input back to console if X quits.
e
s 00416/00407/00777
d D 7.3 92/03/07 09:47:02 ralph 3 2
c changes for ds5000
e
s 00007/00016/01177
d D 7.2 92/02/26 10:34:43 mckusick 2 1
c new select model
e
s 01193/00000/00000
d D 7.1 92/01/07 18:29:22 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
D 8
/* 
 * Copyright (c) 1992 Regents of the University of California.
E 8
I 8
/*-
D 10
 * Copyright (c) 1992 The Regents of the University of California.
E 8
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
D 8
 * Ralph Campbell.
E 8
I 8
 * Ralph Campbell and Rick Macklem.
E 8
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 8
 *
E 8
I 8
 */

/* 
E 8
 *  devGraphics.c --
 *
 *     	This file contains machine-dependent routines for the graphics device.
 *
 *	Copyright (C) 1989 Digital Equipment Corporation.
 *	Permission to use, copy, modify, and distribute this software and
 *	its documentation for any purpose and without fee is hereby granted,
 *	provided that the above copyright notice appears in all copies.  
 *	Digital Equipment Corporation makes no representations about the
 *	suitability of this software for any purpose.  It is provided "as is"
 *	without express or implied warranty.
 *
 * from: $Header: /sprite/src/kernel/dev/ds3100.md/RCS/devGraphics.c,
 *	v 9.2 90/02/13 22:16:24 shirriff Exp $ SPRITE (DECWRL)";
 */

D 8
#include "pm.h"
E 8
I 8
#include <pm.h>
#include <dc.h>
E 8
#if NPM > 0
I 8
#if NDC == 0
pm needs dc device
#else
E 8

D 6
#include "param.h"
#include "time.h"
#include "kernel.h"
#include "ioctl.h"
#include "file.h"
#include "errno.h"
#include "proc.h"
#include "mman.h"
#include "vm/vm.h"
E 6
I 6
#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/errno.h>
#include <sys/proc.h>
#include <sys/mman.h>
E 6

D 6
#include "machine/machConst.h"
#include "machine/machMon.h"
#include "machine/dc7085cons.h"
#include "machine/pmioctl.h"
E 6
I 6
#include <vm/vm.h>
E 6
D 3
#include "machine/pmreg.h"
E 3

D 6
#include "device.h"
I 3
#include "pmreg.h"
E 3
#include "font.c"
E 6
I 6
#include <machine/machConst.h>
D 8
#include <machine/machMon.h>
E 8
#include <machine/dc7085cons.h>
#include <machine/pmioctl.h>

I 8
#include <pmax/pmax/kn01.h>
#include <pmax/pmax/pmaxtype.h>
#include <pmax/pmax/cons.h>

E 8
D 7
#include <mips/dev/device.h>
#include <mips/dev/pmreg.h>
#include <mips/dev/font.c>
E 7
I 7
#include <pmax/dev/device.h>
#include <pmax/dev/pmreg.h>
D 8
#include <pmax/dev/font.c>
E 8
I 8
#include <pmax/dev/fbreg.h>
E 8
E 7
E 6

I 3
D 8
#define MAX_ROW	56
#define MAX_COL	80

E 8
E 3
/*
D 8
 * Macro to translate from a time struct to milliseconds.
 */
#define TO_MS(tv) ((tv.tv_sec * 1000) + (tv.tv_usec / 1000))

static u_short	curReg;		/* copy of PCCRegs.cmdr since it's read only */
static int	isMono;		/* true if B&W frame buffer */
static int	initialized;	/* true if 'probe' was successful */
static int	GraphicsOpen;	/* true if the graphics device is open */
I 3
static int	row, col;	/* row and col for console cursor */
E 3
D 2
static struct	proc *pm_selp;	/* process waiting for select */
E 2
I 2
static struct	selinfo pm_selp;/* process waiting for select */
E 2

/*
E 8
 * These need to be mapped into user space.
 */
D 8
static struct pmuaccess {
	PM_Info		scrInfo;
	pmEvent		events[PM_MAXEVQ];	
	pmTimeCoord	tcs[MOTION_BUFFER_SIZE];
} pmu;
E 8
I 8
struct fbuaccess pmu;
struct pmax_fb pmfb;
static u_short curReg;		/* copy of PCCRegs.cmdr since it's read only */
E 8

D 3
static u_char	bg_RGB[3];	/* background color for the cursor */
static u_char	fg_RGB[3];	/* foreground color for the cursor */

E 3
/*
D 3
 * The default cursor.
 */
unsigned short defCursor[32] = { 
/* plane A */ 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF,
	      0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF,
/* plane B */ 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF,
              0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF

};

/*
E 3
D 8
 * Font mask bits used by Blitc().
 */
static unsigned int fontmaskBits[16] = {
	0x00000000,
	0x00000001,
	0x00000100,
	0x00000101,
	0x00010000,
	0x00010001,
	0x00010100,
	0x00010101,
	0x01000000,
	0x01000001,
	0x01000100,
	0x01000101,
	0x01010000,
	0x01010001,
	0x01010100,
	0x01010101
};

/*
E 8
 * Forward references.
 */
I 3
D 8
static void Scroll();
static void Blitc();
E 8
I 8
D 9
extern void fbScroll();
E 8

E 9
E 3
D 8
static void ScreenInit();
static void LoadCursor();
static void RestoreCursorColor();
static void CursorColor();
I 3
static void PosCursor();
E 3
static void InitColorMap();
static void VDACInit();
static void LoadColorMap();
D 3
static void PosCursor();
static void Scroll();
static void Blitc();
E 3
I 3
static void EnableVideo();
static void DisableVideo();
E 8
I 8
static void pmScreenInit();
static void pmLoadCursor();
static void pmRestoreCursorColor();
static void pmCursorColor();
void pmPosCursor();
static void pmInitColorMap();
static void pmVDACInit();
static void pmLoadColorMap();
E 8
E 3

D 8
extern void dcKBDPutc();
E 8
I 8
D 9
extern void dcPutc(), fbKbdEvent(), fbMouseEvent(), fbMouseButtons();
E 9
void pmKbdEvent(), pmMouseEvent(), pmMouseButtons();
I 9
extern void dcPutc();
E 9
E 8
I 3
extern void (*dcDivertXInput)();
extern void (*dcMouseEvent)();
extern void (*dcMouseButtons)();
I 8
extern int pmax_boardtype;
extern u_short defCursor[32];
extern struct consdev cn_tab;
E 8
E 3

int	pmprobe();
struct	driver pmdriver = {
	"pm", pmprobe, 0, 0,
};

/*
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
/*ARGSUSED*/
pmprobe(cp)
	register struct pmax_ctlr *cp;
{
I 8
	register struct pmax_fb *fp = &pmfb;
E 8

D 8
	if (!initialized && !pminit())
E 8
I 8
	if (pmax_boardtype != DS_PMAX)
E 8
		return (0);
D 8
	if (isMono)
E 8
I 8
	if (!fp->initialized && !pminit())
		return (0);
	if (fp->isMono)
E 8
		printf("pm0 (monochrome display)\n");
	else
		printf("pm0 (color display)\n");
	return (1);
}

D 8
/*
D 3
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
pminit()
{
	register PCCRegs *pcc = (PCCRegs *)MACH_CURSOR_REG_ADDR;

	isMono = *(u_short *)MACH_SYS_CSR_ADDR & MACH_CSR_MONO;
	if (isMono) {
		/* check for no frame buffer */
		if (badaddr((char *)MACH_UNCACHED_FRAME_BUFFER_ADDR, 4))
			return (0);
	}

	/*
	 * Initialize the screen.
	 */
#ifdef notdef
	DELAY(100000);		/* why? */
#endif
	pcc->cmdr = PCC_FOPB | PCC_VBHI;

	/*
	 * Initialize the cursor register.
	 */
	pcc->cmdr = curReg = PCC_ENPA | PCC_ENPB;

	/*
	 * Initialize screen info.
	 */
	pmu.scrInfo.max_row = 56;
	pmu.scrInfo.max_col = 80;
	pmu.scrInfo.max_x = 1024;
	pmu.scrInfo.max_y = 864;
	pmu.scrInfo.max_cur_x = 1023;
	pmu.scrInfo.max_cur_y = 863;
	pmu.scrInfo.version = 11;
	pmu.scrInfo.mthreshold = 4;	
	pmu.scrInfo.mscale = 2;
	pmu.scrInfo.min_cur_x = -15;
	pmu.scrInfo.min_cur_y = -15;
	pmu.scrInfo.qe.timestamp_ms = TO_MS(time);
	pmu.scrInfo.qe.eSize = PM_MAXEVQ;
	pmu.scrInfo.qe.eHead = pmu.scrInfo.qe.eTail = 0;
	pmu.scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	pmu.scrInfo.qe.tcNext = 0;

	/*
	 * Initialize the color map, the screen, and the mouse.
	 */
	InitColorMap();
	ScreenInit();
	Scroll();

	initialized = 1;
	return (1);
}	

/*
 * ----------------------------------------------------------------------------
 *
 * ScreenInit --
 *
 *	Initialize the screen.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The screen is initialized.
 *
 * ----------------------------------------------------------------------------
 */
static void
ScreenInit()
{

	/*
	 * Home the cursor.
	 * We want an LSI terminal emulation.  We want the graphics
	 * terminal to scroll from the bottom. So start at the bottom.
	 */
	pmu.scrInfo.row = 55;
	pmu.scrInfo.col = 0;

	/*
	 * Load the cursor with the default values
	 *
	 */
	LoadCursor(defCursor);
}

/*
 * ----------------------------------------------------------------------------
 *
 * LoadCursor --
 *
 *	Routine to load the cursor Sprite pattern.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The cursor is loaded into the hardware cursor.
 *
 * ----------------------------------------------------------------------------
 */
static void
LoadCursor(cur)
	unsigned short *cur;
{
	register PCCRegs *pcc = (PCCRegs *)MACH_CURSOR_REG_ADDR;
	register int i;

	curReg |= PCC_LODSA;
	pcc->cmdr = curReg;
	for (i = 0; i < 32; i++) {
		pcc->memory = cur[i];
		MachEmptyWriteBuffer();
	}
	curReg &= ~PCC_LODSA;
	pcc->cmdr = curReg;
}

/*
 * ----------------------------------------------------------------------------
 *
 * RestoreCursorColor --
 *
 *	Routine to restore the color of the cursor.
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
RestoreCursorColor()
{
	register VDACRegs *vdac = (VDACRegs *)MACH_COLOR_MAP_ADDR;
	register int i;

	vdac->overWA = 0x04;
	MachEmptyWriteBuffer();
	for (i = 0; i < 3; i++) {  
		vdac->over = bg_RGB[i];
		MachEmptyWriteBuffer();
	}

	vdac->overWA = 0x08;
	MachEmptyWriteBuffer();
	vdac->over = 0x00;
	MachEmptyWriteBuffer();
	vdac->over = 0x00;
	MachEmptyWriteBuffer();
	vdac->over = 0x7f;
	MachEmptyWriteBuffer();

	vdac->overWA = 0x0c;
	MachEmptyWriteBuffer();
	for (i = 0; i < 3; i++) {
		vdac->over = fg_RGB[i];
		MachEmptyWriteBuffer();
	}
}

/*
 * ----------------------------------------------------------------------------
 *
 * CursorColor --
 *
 *	Set the color of the cursor.
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
CursorColor(color)
	unsigned int color[];
{
	register int i, j;

	for (i = 0; i < 3; i++)
		bg_RGB[i] = (u_char)(color[i] >> 8);

	for (i = 3, j = 0; i < 6; i++, j++)
		fg_RGB[j] = (u_char)(color[i] >> 8);

	RestoreCursorColor();
}

/*
 * ----------------------------------------------------------------------------
 *
 * InitColorMap --
 *
 *	Initialize the color map.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The colormap is initialized appropriately whether it is color or 
 *	monochrome.
 *
 * ----------------------------------------------------------------------------
 */
static void
InitColorMap()
{
	register VDACRegs *vdac = (VDACRegs *)MACH_COLOR_MAP_ADDR;
	register int i;

	*(char *)MACH_PLANE_MASK_ADDR = 0xff;
	MachEmptyWriteBuffer();

	if (isMono) {
		vdac->mapWA = 0; MachEmptyWriteBuffer();
		for (i = 0; i < 256; i++) {
			vdac->map = (i < 128) ? 0x00 : 0xff;
			MachEmptyWriteBuffer();
			vdac->map = (i < 128) ? 0x00 : 0xff;
			MachEmptyWriteBuffer();
			vdac->map = (i < 128) ? 0x00 : 0xff;
			MachEmptyWriteBuffer();
		}
	} else {
		vdac->mapWA = 0; MachEmptyWriteBuffer();
		vdac->map = 0; MachEmptyWriteBuffer();
		vdac->map = 0; MachEmptyWriteBuffer();
		vdac->map = 0; MachEmptyWriteBuffer();

		for (i = 1; i < 256; i++) {
			vdac->map = 0xff; MachEmptyWriteBuffer();
			vdac->map = 0xff; MachEmptyWriteBuffer();
			vdac->map = 0xff; MachEmptyWriteBuffer();
		}
	}

	for (i = 0; i < 3; i++) {
		bg_RGB[i] = 0x00;
		fg_RGB[i] = 0xff;
	}
	RestoreCursorColor();
}

/*
 * ----------------------------------------------------------------------------
 *
 * VDACInit --
 *
 *	Initialize the VDAC.
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
VDACInit()
{
	register VDACRegs *vdac = (VDACRegs *)MACH_COLOR_MAP_ADDR;

	/*
	 *
	 * Initialize the VDAC
	 */
	vdac->overWA = 0x04; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->overWA = 0x08; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->over = 0x7f; MachEmptyWriteBuffer();
	vdac->overWA = 0x0c; MachEmptyWriteBuffer();
	vdac->over = 0xff; MachEmptyWriteBuffer();
	vdac->over = 0xff; MachEmptyWriteBuffer();
	vdac->over = 0xff; MachEmptyWriteBuffer();
}

/*
 * ----------------------------------------------------------------------------
 *
 * LoadColorMap --
 *
 *	Load the color map.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The color map is loaded.
 *
 * ----------------------------------------------------------------------------
 */
static void
LoadColorMap(ptr)
	ColorMap *ptr;
{
	register VDACRegs *vdac = (VDACRegs *)MACH_COLOR_MAP_ADDR;

	if (ptr->index > 256)
		return;

	vdac->mapWA = ptr->index; MachEmptyWriteBuffer();
	vdac->map = ptr->Entry.red; MachEmptyWriteBuffer();
	vdac->map = ptr->Entry.green; MachEmptyWriteBuffer();
	vdac->map = ptr->Entry.blue; MachEmptyWriteBuffer();
}

/*
E 3
 *----------------------------------------------------------------------
 *
 * pmKbdEvent --
 *
 *	Process a received character.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Events added to the queue.
 *
 *----------------------------------------------------------------------
 */
void
pmKbdEvent(ch)
	int ch;
{
	register pmEvent *eventPtr;
	int i;

	if (!GraphicsOpen)
		return;

	/*
	 * See if there is room in the queue.
	 */
	i = PM_EVROUND(pmu.scrInfo.qe.eTail + 1);
	if (i == pmu.scrInfo.qe.eHead)
		return;

	/*
	 * Add the event to the queue.
	 */
	eventPtr = &pmu.events[pmu.scrInfo.qe.eTail];
	eventPtr->type = BUTTON_RAW_TYPE;
	eventPtr->device = KEYBOARD_DEVICE;
	eventPtr->x = pmu.scrInfo.mouse.x;
	eventPtr->y = pmu.scrInfo.mouse.y;
	eventPtr->time = TO_MS(time);
	eventPtr->key = ch;
	pmu.scrInfo.qe.eTail = i;
D 2
	pmwakeup();
E 2
I 2
	selwakeup(&pm_selp);
E 2
}

/*
 *----------------------------------------------------------------------
 *
 * pmMouseEvent --
 *
 *	Process a mouse event.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	An event is added to the event queue.
 *
 *----------------------------------------------------------------------
 */
void
pmMouseEvent(newRepPtr) 
	register MouseReport *newRepPtr;
{
	unsigned milliSec;
	int i;
	pmEvent *eventPtr;

	if (!GraphicsOpen)
		return;

	milliSec = TO_MS(time);

	/*
	 * Check to see if we have to accelerate the mouse
	 */
	if (pmu.scrInfo.mscale >= 0) {
		if (newRepPtr->dx >= pmu.scrInfo.mthreshold) {
			newRepPtr->dx +=
				(newRepPtr->dx - pmu.scrInfo.mthreshold) *
				pmu.scrInfo.mscale;
		}
		if (newRepPtr->dy >= pmu.scrInfo.mthreshold) {
			newRepPtr->dy +=
				(newRepPtr->dy - pmu.scrInfo.mthreshold) *
				pmu.scrInfo.mscale;
		}
	}

	/*
	 * Update mouse position
	 */
	if (newRepPtr->state & MOUSE_X_SIGN) {
		pmu.scrInfo.mouse.x += newRepPtr->dx;
		if (pmu.scrInfo.mouse.x > pmu.scrInfo.max_cur_x)
			pmu.scrInfo.mouse.x = pmu.scrInfo.max_cur_x;
	} else {
		pmu.scrInfo.mouse.x -= newRepPtr->dx;
		if (pmu.scrInfo.mouse.x < pmu.scrInfo.min_cur_x)
			pmu.scrInfo.mouse.x = pmu.scrInfo.min_cur_x;
	}
	if (newRepPtr->state & MOUSE_Y_SIGN) {
		pmu.scrInfo.mouse.y -= newRepPtr->dy;
		if (pmu.scrInfo.mouse.y < pmu.scrInfo.min_cur_y)
			pmu.scrInfo.mouse.y = pmu.scrInfo.min_cur_y;
	} else {
		pmu.scrInfo.mouse.y += newRepPtr->dy;
		if (pmu.scrInfo.mouse.y > pmu.scrInfo.max_cur_y)
			pmu.scrInfo.mouse.y = pmu.scrInfo.max_cur_y;
	}

	/*
	 * Move the hardware cursor.
	 */
	PosCursor(pmu.scrInfo.mouse.x, pmu.scrInfo.mouse.y);

	/*
	 * Store the motion event in the motion buffer.
	 */
	pmu.tcs[pmu.scrInfo.qe.tcNext].time = milliSec;
	pmu.tcs[pmu.scrInfo.qe.tcNext].x = pmu.scrInfo.mouse.x;
	pmu.tcs[pmu.scrInfo.qe.tcNext].y = pmu.scrInfo.mouse.y;
	if (++pmu.scrInfo.qe.tcNext >= MOTION_BUFFER_SIZE)
		pmu.scrInfo.qe.tcNext = 0;
	if (pmu.scrInfo.mouse.y < pmu.scrInfo.mbox.bottom &&
	    pmu.scrInfo.mouse.y >=  pmu.scrInfo.mbox.top &&
	    pmu.scrInfo.mouse.x < pmu.scrInfo.mbox.right &&
	    pmu.scrInfo.mouse.x >=  pmu.scrInfo.mbox.left)
		return;

	pmu.scrInfo.mbox.bottom = 0;
	if (PM_EVROUND(pmu.scrInfo.qe.eTail + 1) == pmu.scrInfo.qe.eHead)
		return;

	i = PM_EVROUND(pmu.scrInfo.qe.eTail - 1);
	if ((pmu.scrInfo.qe.eTail != pmu.scrInfo.qe.eHead) && 
	    (i != pmu.scrInfo.qe.eHead)) {
		pmEvent *eventPtr;

		eventPtr = &pmu.events[i];
		if (eventPtr->type == MOTION_TYPE) {
			eventPtr->x = pmu.scrInfo.mouse.x;
			eventPtr->y = pmu.scrInfo.mouse.y;
			eventPtr->time = milliSec;
			eventPtr->device = MOUSE_DEVICE;
			return;
		}
	}
	/*
	 * Put event into queue and wakeup any waiters.
	 */
	eventPtr = &pmu.events[pmu.scrInfo.qe.eTail];
	eventPtr->type = MOTION_TYPE;
	eventPtr->time = milliSec;
	eventPtr->x = pmu.scrInfo.mouse.x;
	eventPtr->y = pmu.scrInfo.mouse.y;
	eventPtr->device = MOUSE_DEVICE;
	pmu.scrInfo.qe.eTail = PM_EVROUND(pmu.scrInfo.qe.eTail + 1);
D 2
	pmwakeup();
E 2
I 2
	selwakeup(&pm_selp);
E 2
}

/*
 *----------------------------------------------------------------------
 *
 * pmMouseButtons --
 *
 *	Process mouse buttons.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */
void
pmMouseButtons(newRepPtr)
	MouseReport *newRepPtr;
{
	static char temp, oldSwitch, newSwitch;
	int i, j;
	pmEvent *eventPtr;
	static MouseReport lastRep;

	if (!GraphicsOpen)
		return;

	newSwitch = newRepPtr->state & 0x07;
	oldSwitch = lastRep.state & 0x07;

	temp = oldSwitch ^ newSwitch;
	if (temp == 0)
		return;
	for (j = 1; j < 8; j <<= 1) {
		if ((j & temp) == 0)
			continue;

		/*
		 * Check for room in the queue
		 */
		i = PM_EVROUND(pmu.scrInfo.qe.eTail+1);
		if (i == pmu.scrInfo.qe.eHead)
			return;

		/*
		 * Put event into queue.
		 */
		eventPtr = &pmu.events[pmu.scrInfo.qe.eTail];

		switch (j) {
		case RIGHT_BUTTON:
			eventPtr->key = EVENT_RIGHT_BUTTON;
			break;

		case MIDDLE_BUTTON:
			eventPtr->key = EVENT_MIDDLE_BUTTON;
			break;

		case LEFT_BUTTON:
			eventPtr->key = EVENT_LEFT_BUTTON;
		}
		if (newSwitch & j)
			eventPtr->type = BUTTON_DOWN_TYPE;
		else
			eventPtr->type = BUTTON_UP_TYPE;
		eventPtr->device = MOUSE_DEVICE;

		eventPtr->time = TO_MS(time);
		eventPtr->x = pmu.scrInfo.mouse.x;
		eventPtr->y = pmu.scrInfo.mouse.y;
	}
	pmu.scrInfo.qe.eTail = i;
D 2
	pmwakeup();
E 2
I 2
	selwakeup(&pm_selp);
E 2

	lastRep = *newRepPtr;
	pmu.scrInfo.mswitches = newSwitch;
}

/*
 *----------------------------------------------------------------------
 *
D 3
 * PosCursor --
 *
 *	Postion the cursor.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */
static void
PosCursor(x, y)
	register int x, y;
{
	register PCCRegs *pcc = (PCCRegs *)MACH_CURSOR_REG_ADDR;

	if (y < pmu.scrInfo.min_cur_y || y > pmu.scrInfo.max_cur_y)
		y = pmu.scrInfo.max_cur_y;
	if (x < pmu.scrInfo.min_cur_x || x > pmu.scrInfo.max_cur_x)
		x = pmu.scrInfo.max_cur_x;
	pmu.scrInfo.cursor.x = x;		/* keep track of real cursor */
	pmu.scrInfo.cursor.y = y;		/* position, indep. of mouse */
	pcc->xpos = PCC_X_OFFSET + x;
	pcc->ypos = PCC_Y_OFFSET + y;
}

/*
 *----------------------------------------------------------------------
 *
E 3
 * Scroll --
 *
 *	Scroll the screen.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */
static void
Scroll()
{
	register int *dest, *src;
	register int *end;
	register int temp0, temp1, temp2, temp3;
	register int i, scanInc, lineCount;
	int line;

	/*
	 * If the mouse is on we don't scroll so that the bit map remains sane.
	 */
	if (GraphicsOpen) {
D 3
		pmu.scrInfo.row = 0;
E 3
I 3
		row = 0;
E 3
		return;
	}

	/*
	 *  The following is an optimization to cause the scrolling 
	 *  of text to be memory limited.  Basically the writebuffer is 
	 *  4 words (32 bits ea.) long so to achieve maximum speed we 
	 *  read and write in multiples of 4 words. We also limit the 
D 3
	 *  size to be 80 characters for more speed. 
E 3
I 3
	 *  size to be MAX_COL characters for more speed. 
E 3
	 */
	if (isMono) {
		lineCount = 5;
		line = 1920 * 2;
		scanInc = 44;
	} else {
		lineCount = 40;
		scanInc = 96;
		line = 1920 * 8;
	}
	src = (int *)(MACH_UNCACHED_FRAME_BUFFER_ADDR + line);
	dest = (int *)(MACH_UNCACHED_FRAME_BUFFER_ADDR);
	end = (int *)(MACH_UNCACHED_FRAME_BUFFER_ADDR + (60 * line) - line);
	do {
		i = 0;
		do {
			temp0 = src[0];
			temp1 = src[1];
			temp2 = src[2];
			temp3 = src[3];
			dest[0] = temp0;
			dest[1] = temp1;
			dest[2] = temp2;
			dest[3] = temp3;
			dest += 4;
			src += 4;
			i++;
		} while (i < lineCount);
		src += scanInc;
		dest += scanInc;
	} while (src < end);

	/* 
	 * Now zero out the last two lines 
	 */
D 3
	bzero(MACH_UNCACHED_FRAME_BUFFER_ADDR + (pmu.scrInfo.row * line),
		3 * line);
E 3
I 3
	bzero(MACH_UNCACHED_FRAME_BUFFER_ADDR + (row * line), 3 * line);
E 3
}

/*
 *----------------------------------------------------------------------
 *
 * pmPutc --
 *
 *	Write a character to the console.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */
pmPutc(c)
	register int c;
{
	int s;

	s = splhigh();	/* in case we do any printf's at interrupt time */
	if (initialized) {
#ifdef DEBUG
		/*
		 * If the HELP key is pressed, wait for another
		 * HELP key press to start/stop output.
		 */
D 3
		if (dcKBDGetc() == LK_HELP) {
			while (dcKBDGetc() != LK_HELP)
E 3
I 3
		if (dcDebugGetc() == LK_HELP) {
			while (dcDebugGetc() != LK_HELP)
E 3
				;
		}
#endif
		Blitc(c);
	} else {
		void (*f)() = (void (*)())MACH_MON_PUTCHAR;

		(*f)(c);
	}
	splx(s);
}

/*
 *----------------------------------------------------------------------
 *
 * Blitc --
 *
 *	Write a character to the screen.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */
static void
Blitc(c)
	register int c;
{
	register char *bRow, *fRow;
	register int i;
	register int ote = isMono ? 256 : 1024; /* offset to table entry */
	int colMult = isMono ? 1 : 8;

	c &= 0xff;

	switch (c) {
	case '\t':
D 3
		for (i = 8 - (pmu.scrInfo.col & 0x7); i > 0; i--)
E 3
I 3
		for (i = 8 - (col & 0x7); i > 0; i--)
E 3
			Blitc(' ');
		break;

	case '\r':
D 3
		pmu.scrInfo.col = 0;
E 3
I 3
		col = 0;
E 3
		break;

	case '\b':
D 3
		pmu.scrInfo.col--;
		if (pmu.scrInfo.col < 0)
			pmu.scrInfo.col = 0;
E 3
I 3
		col--;
		if (col < 0)
			col = 0;
E 3
		break;

	case '\n':
D 3
		if (pmu.scrInfo.row + 1 >= pmu.scrInfo.max_row)
E 3
I 3
		if (row + 1 >= MAX_ROW)
E 3
			Scroll();
		else
D 3
			pmu.scrInfo.row++;
		pmu.scrInfo.col = 0;
E 3
I 3
			row++;
		col = 0;
E 3
		break;

	case '\007':
		dcKBDPutc(LK_RING_BELL);
		break;

	default:
		/*
I 3
		 * 0xA1 to 0xFD are the printable characters added with 8-bit
		 * support.
		 */
		if (c < ' ' || c > '~' && c < 0xA1 || c > 0xFD)
			break;
		/*
E 3
		 * If the next character will wrap around then 
		 * increment row counter or scroll screen.
		 */
D 3
		if (pmu.scrInfo.col >= pmu.scrInfo.max_col) {
			pmu.scrInfo.col = 0;
			if (pmu.scrInfo.row + 1 >= pmu.scrInfo.max_row)
E 3
I 3
		if (col >= MAX_COL) {
			col = 0;
			if (row + 1 >= MAX_ROW)
E 3
				Scroll();
			else
D 3
				pmu.scrInfo.row++;
E 3
I 3
				row++;
E 3
		}
D 3
		/*
		 * 0xA1 to 0xFD are the printable characters added with 8-bit
		 * support.
		 */
		if (c < ' ' || c > '~' && c < 0xA1 || c > 0xFD)
			break;
E 3
		bRow = (char *)(MACH_UNCACHED_FRAME_BUFFER_ADDR +
D 3
			(pmu.scrInfo.row * 15 & 0x3ff) * ote + 
			pmu.scrInfo.col * colMult);
E 3
I 3
			(row * 15 & 0x3ff) * ote + col * colMult);
E 3
		i = c - ' ';
		/*
		 * This is to skip the (32) 8-bit 
		 * control chars, as well as DEL 
		 * and 0xA0 which aren't printable
		 */
		if (c > '~')
			i -= 34; 
		i *= 15;
		fRow = (char *)((int)pmFont + i);

		/* inline expansion for speed */
		if (isMono) {
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
			*bRow = *fRow++; bRow += ote;
		} else {
			register int j;
			register unsigned int *pInt;

			pInt = (unsigned int *)bRow;
			for (j = 0; j < 15; j++) {
				/*
				 * fontmaskBits converts a nibble
				 * (4 bytes) to a long word 
				 * containing 4 pixels corresponding
				 * to each bit in the nibble.  Thus
				 * we write two longwords for each
				 * byte in font.
				 * 
				 * Remember the font is 8 bits wide
				 * and 15 bits high.
				 *
				 * We add 256 to the pointer to
				 * point to the pixel on the 
				 * next scan line
				 * directly below the current
				 * pixel.
				 */
				pInt[0] = fontmaskBits[(*fRow) & 0xf];
				pInt[1] = fontmaskBits[((*fRow) >> 4) & 0xf];
				fRow++; 
				pInt += 256;
			}
		}
D 3
		pmu.scrInfo.col++; /* increment column counter */
E 3
I 3
		col++; /* increment column counter */
E 3
	}
	if (!GraphicsOpen)
D 3
		PosCursor(pmu.scrInfo.col * 8, pmu.scrInfo.row * 15);
E 3
I 3
		PosCursor(col * 8, row * 15);
E 3
}

E 8
/*ARGSUSED*/
pmopen(dev, flag)
	dev_t dev;
	int flag;
{
I 8
	register struct pmax_fb *fp = &pmfb;
E 8
I 5
	int s;
E 5

D 8
	if (!initialized)
E 8
I 8
	if (!fp->initialized)
E 8
		return (ENXIO);
D 8
	if (GraphicsOpen)
E 8
I 8
	if (fp->GraphicsOpen)
E 8
		return (EBUSY);

D 8
	GraphicsOpen = 1;
	if (!isMono)
		InitColorMap();
E 8
I 8
	fp->GraphicsOpen = 1;
	if (!fp->isMono)
		pmInitColorMap();
E 8
	/*
	 * Set up event queue for later
	 */
D 8
	pmu.scrInfo.qe.eSize = PM_MAXEVQ;
	pmu.scrInfo.qe.eHead = pmu.scrInfo.qe.eTail = 0;
	pmu.scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	pmu.scrInfo.qe.tcNext = 0;
	pmu.scrInfo.qe.timestamp_ms = TO_MS(time);
E 8
I 8
	fp->fbu->scrInfo.qe.eSize = PM_MAXEVQ;
	fp->fbu->scrInfo.qe.eHead = fp->fbu->scrInfo.qe.eTail = 0;
	fp->fbu->scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	fp->fbu->scrInfo.qe.tcNext = 0;
	fp->fbu->scrInfo.qe.timestamp_ms = TO_MS(time);
E 8
I 5
	s = spltty();
	dcDivertXInput = pmKbdEvent;
	dcMouseEvent = pmMouseEvent;
	dcMouseButtons = pmMouseButtons;
	splx(s);
E 5
	return (0);
}

/*ARGSUSED*/
pmclose(dev, flag)
	dev_t dev;
	int flag;
{
I 8
	register struct pmax_fb *fp = &pmfb;
E 8
I 4
	int s;
E 4

D 8
	if (!GraphicsOpen)
E 8
I 8
	if (!fp->GraphicsOpen)
E 8
		return (EBADF);

D 8
	GraphicsOpen = 0;
	if (!isMono)
		InitColorMap();
E 8
I 8
	fp->GraphicsOpen = 0;
	if (!fp->isMono)
		pmInitColorMap();
E 8
I 4
	s = spltty();
	dcDivertXInput = (void (*)())0;
	dcMouseEvent = (void (*)())0;
	dcMouseButtons = (void (*)())0;
	splx(s);
E 4
D 8
	ScreenInit();
E 8
I 8
	pmScreenInit();
E 8
D 9
	vmUserUnmap();
E 9
I 3
D 8
	bzero((caddr_t)MACH_UNCACHED_FRAME_BUFFER_ADDR,
		(isMono ? 1024 / 8 : 1024) * 864);
	PosCursor(col * 8, row * 15);
E 8
I 8
	bzero((caddr_t)fp->fr_addr,
		(fp->isMono ? 1024 / 8 : 1024) * 864);
	pmPosCursor(fp->col * 8, fp->row * 15);
E 8
E 3
	return (0);
}

/*ARGSUSED*/
D 9
pmioctl(dev, cmd, data, flag)
E 9
I 9
pmioctl(dev, cmd, data, flag, p)
E 9
	dev_t dev;
I 11
	u_long cmd;
E 11
	caddr_t data;
I 9
	struct proc *p;
E 9
{
D 8
	register PCCRegs *pcc = (PCCRegs *)MACH_CURSOR_REG_ADDR;
E 8
I 8
	register PCCRegs *pcc = (PCCRegs *)MACH_PHYS_TO_UNCACHED(KN01_SYS_PCC);
	register struct pmax_fb *fp = &pmfb;
E 8
I 4
	int s;
E 4
D 3
	extern int dcDivertXInput;
E 3

	switch (cmd) {
	case QIOCGINFO:
D 9
	    {
		caddr_t addr;
		extern caddr_t vmUserMap();
E 9
I 9
		return (fbmmap(fp, dev, data, p));
E 9

D 9
		/*
		 * Map the all the data the user needs access to into
		 * user space.
		 */
D 8
		addr = vmUserMap(sizeof(pmu), (unsigned)&pmu);
E 8
I 8
		addr = vmUserMap(sizeof(struct fbuaccess), (unsigned)fp->fbu);
E 8
		if (addr == (caddr_t)0)
			goto mapError;
D 8
		*(PM_Info **)data = &((struct pmuaccess *)addr)->scrInfo;
		pmu.scrInfo.qe.events = ((struct pmuaccess *)addr)->events;
		pmu.scrInfo.qe.tcs = ((struct pmuaccess *)addr)->tcs;
E 8
I 8
		*(PM_Info **)data = &((struct fbuaccess *)addr)->scrInfo;
		fp->fbu->scrInfo.qe.events = ((struct fbuaccess *)addr)->events;
		fp->fbu->scrInfo.qe.tcs = ((struct fbuaccess *)addr)->tcs;
E 8
		/*
		 * Map the plane mask into the user's address space.
		 */
D 8
		addr = vmUserMap(4, (unsigned)MACH_PLANE_MASK_ADDR);
E 8
I 8
		addr = vmUserMap(4, (unsigned)
			MACH_PHYS_TO_UNCACHED(KN01_PHYS_COLMASK_START));
E 8
		if (addr == (caddr_t)0)
			goto mapError;
D 8
		pmu.scrInfo.planemask = (char *)addr;
E 8
I 8
		fp->fbu->scrInfo.planemask = (char *)addr;
E 8
		/*
D 3
		 * Map the bitmap into the user's address space.
E 3
I 3
		 * Map the frame buffer into the user's address space.
E 3
		 */
D 8
		addr = vmUserMap(isMono ? 256*1024 : 1024*1024,
			(unsigned)MACH_UNCACHED_FRAME_BUFFER_ADDR);
E 8
I 8
		addr = vmUserMap(fp->isMono ? 256*1024 : 1024*1024,
			(unsigned)fp->fr_addr);
E 8
		if (addr == (caddr_t)0)
			goto mapError;
D 8
		pmu.scrInfo.bitmap = (char *)addr;
E 8
I 8
		fp->fbu->scrInfo.bitmap = (char *)addr;
E 8
		break;

	mapError:
		vmUserUnmap();
		printf("Cannot map shared data structures\n");
		return (EIO);
	    }

E 9
	case QIOCPMSTATE:
		/*
		 * Set mouse state.
		 */
D 8
		pmu.scrInfo.mouse = *(pmCursor *)data;
		PosCursor(pmu.scrInfo.mouse.x, pmu.scrInfo.mouse.y);
E 8
I 8
		fp->fbu->scrInfo.mouse = *(pmCursor *)data;
		pmPosCursor(fp->fbu->scrInfo.mouse.x, fp->fbu->scrInfo.mouse.y);
E 8
		break;

	case QIOCINIT:
		/*
		 * Initialize the screen.
		 */
D 8
		ScreenInit();
E 8
I 8
		pmScreenInit();
E 8
		break;

	case QIOCKPCMD:
	    {
		pmKpCmd *kpCmdPtr;
		unsigned char *cp;

		kpCmdPtr = (pmKpCmd *)data;
		if (kpCmdPtr->nbytes == 0)
			kpCmdPtr->cmd |= 0x80;
D 8
		if (!GraphicsOpen)
E 8
I 8
		if (!fp->GraphicsOpen)
E 8
			kpCmdPtr->cmd |= 1;
D 8
		dcKBDPutc((int)kpCmdPtr->cmd);
E 8
I 8
		(*fp->KBDPutc)(fp->kbddev, (int)kpCmdPtr->cmd);
E 8
		cp = &kpCmdPtr->par[0];
		for (; kpCmdPtr->nbytes > 0; cp++, kpCmdPtr->nbytes--) {
			if (kpCmdPtr->nbytes == 1)
				*cp |= 0x80;
D 8
			dcKBDPutc((int)*cp);
E 8
I 8
			(*fp->KBDPutc)(fp->kbddev, (int)*cp);
E 8
		}
		break;
	    }

	case QIOCADDR:
D 8
		*(PM_Info **)data = &pmu.scrInfo;
E 8
I 8
		*(PM_Info **)data = &fp->fbu->scrInfo;
E 8
		break;

	case QIOWCURSOR:
D 8
		LoadCursor((unsigned short *)data);
E 8
I 8
		pmLoadCursor((unsigned short *)data);
E 8
		break;

	case QIOWCURSORCOLOR:
D 8
		CursorColor((unsigned int *)data);
E 8
I 8
		pmCursorColor((unsigned int *)data);
E 8
		break;

	case QIOSETCMAP:
D 8
		LoadColorMap((ColorMap *)data);
E 8
I 8
		pmLoadColorMap((ColorMap *)data);
E 8
		break;

	case QIOKERNLOOP:
I 4
		s = spltty();
E 4
D 3
		printf("pmioctl: QIOKERNLOOP\n"); /* XXX */
		dcDivertXInput = 1;
E 3
I 3
		dcDivertXInput = pmKbdEvent;
		dcMouseEvent = pmMouseEvent;
		dcMouseButtons = pmMouseButtons;
I 4
		splx(s);
E 4
E 3
		break;

	case QIOKERNUNLOOP:
I 4
		s = spltty();
E 4
D 3
		printf("pmioctl: QIOKERNUNLOOP\n"); /* XXX */
		dcDivertXInput = 0;
E 3
I 3
		dcDivertXInput = (void (*)())0;
		dcMouseEvent = (void (*)())0;
		dcMouseButtons = (void (*)())0;
I 4
		splx(s);
E 4
E 3
		break;

	case QIOVIDEOON:
D 8
		if (!isMono)
			RestoreCursorColor();
E 8
I 8
		if (!fp->isMono)
			pmRestoreCursorColor();
E 8
		curReg |= PCC_ENPA;
		curReg &= ~PCC_FOPB;
		pcc->cmdr = curReg;
		break;

	case QIOVIDEOOFF:
D 8
		if (!isMono)
			VDACInit();
E 8
I 8
		if (!fp->isMono)
			pmVDACInit();
E 8
		curReg |= PCC_FOPB;
		curReg &= ~PCC_ENPA;
		pcc->cmdr = curReg;
		break;

	default:
D 3
		printf("pm0: Unknown command %x\n", cmd);
E 3
I 3
		printf("pm0: Unknown ioctl command %x\n", cmd);
E 3
		return (EINVAL);
	}
	return (0);
}

I 9
/*
 * Return the physical page number that corresponds to byte offset 'off'.
 */
/*ARGSUSED*/
pmmap(dev, off, prot)
	dev_t dev;
{
	int len;

	len = pmax_round_page(((vm_offset_t)&pmu & PGOFSET) + sizeof(pmu));
	if (off < len)
		return pmax_btop(MACH_CACHED_TO_PHYS(&pmu) + off);
	off -= len;
	if (off >= pmfb.fr_size)
		return (-1);
	return pmax_btop(MACH_UNCACHED_TO_PHYS(pmfb.fr_addr) + off);
}

E 9
D 2
pmselect(dev, flag)
E 2
I 2
pmselect(dev, flag, p)
E 2
	dev_t dev;
	int flag;
I 2
	struct proc *p;
E 2
{
I 8
	struct pmax_fb *fp = &pmfb;
E 8

	switch (flag) {
	case FREAD:
D 8
		if (pmu.scrInfo.qe.eHead != pmu.scrInfo.qe.eTail)
E 8
I 8
		if (fp->fbu->scrInfo.qe.eHead != fp->fbu->scrInfo.qe.eTail)
E 8
			return (1);
D 2
		pm_selp = curproc;
E 2
I 2
D 8
		selrecord(p, &pm_selp);
E 8
I 8
		selrecord(p, &fp->selp);
E 8
E 2
		break;
	}

	return (0);
I 3
}

static u_char	bg_RGB[3];	/* background color for the cursor */
static u_char	fg_RGB[3];	/* foreground color for the cursor */

/*
D 8
 * The default cursor.
 */
unsigned short defCursor[32] = { 
/* plane A */ 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF,
	      0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF,
/* plane B */ 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF,
              0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF

};

/*
E 8
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
pminit()
{
D 8
	register PCCRegs *pcc = (PCCRegs *)MACH_CURSOR_REG_ADDR;
E 8
I 8
	register PCCRegs *pcc = (PCCRegs *)MACH_PHYS_TO_UNCACHED(KN01_SYS_PCC);
	register struct pmax_fb *fp = &pmfb;
E 8

D 8
	isMono = *(u_short *)MACH_SYS_CSR_ADDR & MACH_CSR_MONO;
	if (isMono) {
E 8
I 8
	fp->isMono = *(volatile u_short *)MACH_PHYS_TO_UNCACHED(KN01_SYS_CSR) &
		KN01_CSR_MONO;
	fp->fr_addr = (char *)MACH_PHYS_TO_UNCACHED(KN01_PHYS_FBUF_START);
D 9
	fp->fbu = &pmu;
E 9
I 9
	fp->fr_size = fp->isMono ? 0x40000 : 0x100000;
	/*
	 * Must be in Uncached space since the fbuaccess structure is
	 * mapped into the user's address space uncached.
	 */
	fp->fbu = (struct fbuaccess *)
		MACH_PHYS_TO_UNCACHED(MACH_CACHED_TO_PHYS(&pmu));
E 9
	fp->posCursor = pmPosCursor;
	fp->KBDPutc = dcPutc;
	fp->kbddev = makedev(DCDEV, DCKBD_PORT);
	if (fp->isMono) {
E 8
		/* check for no frame buffer */
D 8
		if (badaddr((char *)MACH_UNCACHED_FRAME_BUFFER_ADDR, 4))
E 8
I 8
		if (badaddr((char *)fp->fr_addr, 4))
E 8
			return (0);
	}

	/*
	 * Initialize the screen.
	 */
	pcc->cmdr = PCC_FOPB | PCC_VBHI;

	/*
	 * Initialize the cursor register.
	 */
	pcc->cmdr = curReg = PCC_ENPA | PCC_ENPB;

	/*
	 * Initialize screen info.
	 */
D 8
	pmu.scrInfo.max_row = 56;
	pmu.scrInfo.max_col = 80;
	pmu.scrInfo.max_x = 1024;
	pmu.scrInfo.max_y = 864;
	pmu.scrInfo.max_cur_x = 1023;
	pmu.scrInfo.max_cur_y = 863;
	pmu.scrInfo.version = 11;
	pmu.scrInfo.mthreshold = 4;	
	pmu.scrInfo.mscale = 2;
	pmu.scrInfo.min_cur_x = -15;
	pmu.scrInfo.min_cur_y = -15;
	pmu.scrInfo.qe.timestamp_ms = TO_MS(time);
	pmu.scrInfo.qe.eSize = PM_MAXEVQ;
	pmu.scrInfo.qe.eHead = pmu.scrInfo.qe.eTail = 0;
	pmu.scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	pmu.scrInfo.qe.tcNext = 0;
E 8
I 8
	fp->fbu->scrInfo.max_row = 56;
	fp->fbu->scrInfo.max_col = 80;
	fp->fbu->scrInfo.max_x = 1024;
	fp->fbu->scrInfo.max_y = 864;
	fp->fbu->scrInfo.max_cur_x = 1023;
	fp->fbu->scrInfo.max_cur_y = 863;
	fp->fbu->scrInfo.version = 11;
	fp->fbu->scrInfo.mthreshold = 4;	
	fp->fbu->scrInfo.mscale = 2;
	fp->fbu->scrInfo.min_cur_x = -15;
	fp->fbu->scrInfo.min_cur_y = -15;
	fp->fbu->scrInfo.qe.timestamp_ms = TO_MS(time);
	fp->fbu->scrInfo.qe.eSize = PM_MAXEVQ;
	fp->fbu->scrInfo.qe.eHead = fp->fbu->scrInfo.qe.eTail = 0;
	fp->fbu->scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	fp->fbu->scrInfo.qe.tcNext = 0;
E 8

	/*
	 * Initialize the color map, the screen, and the mouse.
	 */
D 8
	InitColorMap();
	ScreenInit();
	Scroll();
E 8
I 8
	pmInitColorMap();
	pmScreenInit();
	fbScroll(fp);
E 8

D 8
	initialized = 1;
E 8
I 8
	fp->initialized = 1;
	if (cn_tab.cn_fb == (struct pmax_fb *)0)
		cn_tab.cn_fb = fp;
E 8
	return (1);
}	

/*
 * ----------------------------------------------------------------------------
 *
D 8
 * ScreenInit --
E 8
I 8
 * pmScreenInit --
E 8
 *
 *	Initialize the screen.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The screen is initialized.
 *
 * ----------------------------------------------------------------------------
 */
static void
D 8
ScreenInit()
E 8
I 8
pmScreenInit()
E 8
{
I 8
	register struct pmax_fb *fp = &pmfb;
E 8

	/*
	 * Home the cursor.
	 * We want an LSI terminal emulation.  We want the graphics
	 * terminal to scroll from the bottom. So start at the bottom.
	 */
D 8
	row = 55;
	col = 0;
E 8
I 8
	fp->row = 55;
	fp->col = 0;
E 8

	/*
	 * Load the cursor with the default values
	 *
	 */
D 8
	LoadCursor(defCursor);
E 8
I 8
	pmLoadCursor(defCursor);
E 8
}

/*
 * ----------------------------------------------------------------------------
 *
D 8
 * LoadCursor --
E 8
I 8
 * pmLoadCursor --
E 8
 *
 *	Routine to load the cursor Sprite pattern.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The cursor is loaded into the hardware cursor.
 *
 * ----------------------------------------------------------------------------
 */
static void
D 8
LoadCursor(cur)
E 8
I 8
pmLoadCursor(cur)
E 8
	unsigned short *cur;
{
D 8
	register PCCRegs *pcc = (PCCRegs *)MACH_CURSOR_REG_ADDR;
E 8
I 8
	register PCCRegs *pcc = (PCCRegs *)MACH_PHYS_TO_UNCACHED(KN01_SYS_PCC);
E 8
	register int i;

	curReg |= PCC_LODSA;
	pcc->cmdr = curReg;
	for (i = 0; i < 32; i++) {
		pcc->memory = cur[i];
		MachEmptyWriteBuffer();
	}
	curReg &= ~PCC_LODSA;
	pcc->cmdr = curReg;
}

/*
 * ----------------------------------------------------------------------------
 *
D 8
 * RestoreCursorColor --
E 8
I 8
 * pmRestoreCursorColor --
E 8
 *
 *	Routine to restore the color of the cursor.
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
D 8
RestoreCursorColor()
E 8
I 8
pmRestoreCursorColor()
E 8
{
D 8
	register VDACRegs *vdac = (VDACRegs *)MACH_COLOR_MAP_ADDR;
E 8
I 8
	register VDACRegs *vdac = (VDACRegs *)MACH_PHYS_TO_UNCACHED(KN01_SYS_VDAC);
E 8
	register int i;

	vdac->overWA = 0x04;
	MachEmptyWriteBuffer();
	for (i = 0; i < 3; i++) {  
		vdac->over = bg_RGB[i];
		MachEmptyWriteBuffer();
	}

	vdac->overWA = 0x08;
	MachEmptyWriteBuffer();
	vdac->over = 0x00;
	MachEmptyWriteBuffer();
	vdac->over = 0x00;
	MachEmptyWriteBuffer();
	vdac->over = 0x7f;
	MachEmptyWriteBuffer();

	vdac->overWA = 0x0c;
	MachEmptyWriteBuffer();
	for (i = 0; i < 3; i++) {
		vdac->over = fg_RGB[i];
		MachEmptyWriteBuffer();
	}
}

/*
 * ----------------------------------------------------------------------------
 *
D 8
 * CursorColor --
E 8
I 8
 * pmCursorColor --
E 8
 *
 *	Set the color of the cursor.
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
D 8
CursorColor(color)
E 8
I 8
pmCursorColor(color)
E 8
	unsigned int color[];
{
	register int i, j;

	for (i = 0; i < 3; i++)
		bg_RGB[i] = (u_char)(color[i] >> 8);

	for (i = 3, j = 0; i < 6; i++, j++)
		fg_RGB[j] = (u_char)(color[i] >> 8);

D 8
	RestoreCursorColor();
E 8
I 8
	pmRestoreCursorColor();
E 8
}

/*
 * ----------------------------------------------------------------------------
 *
D 8
 * InitColorMap --
E 8
I 8
 * pmInitColorMap --
E 8
 *
 *	Initialize the color map.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The colormap is initialized appropriately whether it is color or 
 *	monochrome.
 *
 * ----------------------------------------------------------------------------
 */
static void
D 8
InitColorMap()
E 8
I 8
pmInitColorMap()
E 8
{
D 8
	register VDACRegs *vdac = (VDACRegs *)MACH_COLOR_MAP_ADDR;
E 8
I 8
	register VDACRegs *vdac = (VDACRegs *)MACH_PHYS_TO_UNCACHED(KN01_SYS_VDAC);
	struct pmax_fb *fp = &pmfb;
E 8
	register int i;

D 8
	*(char *)MACH_PLANE_MASK_ADDR = 0xff;
E 8
I 8
	*(volatile char *)MACH_PHYS_TO_UNCACHED(KN01_PHYS_COLMASK_START) = 0xff;
E 8
	MachEmptyWriteBuffer();

D 8
	if (isMono) {
E 8
I 8
	if (fp->isMono) {
E 8
		vdac->mapWA = 0; MachEmptyWriteBuffer();
		for (i = 0; i < 256; i++) {
			vdac->map = (i < 128) ? 0x00 : 0xff;
			MachEmptyWriteBuffer();
			vdac->map = (i < 128) ? 0x00 : 0xff;
			MachEmptyWriteBuffer();
			vdac->map = (i < 128) ? 0x00 : 0xff;
			MachEmptyWriteBuffer();
		}
	} else {
		vdac->mapWA = 0; MachEmptyWriteBuffer();
		vdac->map = 0; MachEmptyWriteBuffer();
		vdac->map = 0; MachEmptyWriteBuffer();
		vdac->map = 0; MachEmptyWriteBuffer();

		for (i = 1; i < 256; i++) {
			vdac->map = 0xff; MachEmptyWriteBuffer();
			vdac->map = 0xff; MachEmptyWriteBuffer();
			vdac->map = 0xff; MachEmptyWriteBuffer();
		}
	}

	for (i = 0; i < 3; i++) {
		bg_RGB[i] = 0x00;
		fg_RGB[i] = 0xff;
	}
D 8
	RestoreCursorColor();
E 8
I 8
	pmRestoreCursorColor();
E 8
}

/*
 * ----------------------------------------------------------------------------
 *
D 8
 * VDACInit --
E 8
I 8
 * pmVDACInit --
E 8
 *
 *	Initialize the VDAC.
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
D 8
VDACInit()
E 8
I 8
pmVDACInit()
E 8
{
D 8
	register VDACRegs *vdac = (VDACRegs *)MACH_COLOR_MAP_ADDR;
E 8
I 8
	register VDACRegs *vdac = (VDACRegs *)MACH_PHYS_TO_UNCACHED(KN01_SYS_VDAC);
E 8

	/*
	 *
	 * Initialize the VDAC
	 */
	vdac->overWA = 0x04; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->overWA = 0x08; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->over = 0x00; MachEmptyWriteBuffer();
	vdac->over = 0x7f; MachEmptyWriteBuffer();
	vdac->overWA = 0x0c; MachEmptyWriteBuffer();
	vdac->over = 0xff; MachEmptyWriteBuffer();
	vdac->over = 0xff; MachEmptyWriteBuffer();
	vdac->over = 0xff; MachEmptyWriteBuffer();
}

/*
 * ----------------------------------------------------------------------------
 *
D 8
 * LoadColorMap --
E 8
I 8
 * pmLoadColorMap --
E 8
 *
 *	Load the color map.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The color map is loaded.
 *
 * ----------------------------------------------------------------------------
 */
static void
D 8
LoadColorMap(ptr)
E 8
I 8
pmLoadColorMap(ptr)
E 8
	ColorMap *ptr;
{
D 8
	register VDACRegs *vdac = (VDACRegs *)MACH_COLOR_MAP_ADDR;
E 8
I 8
	register VDACRegs *vdac = (VDACRegs *)MACH_PHYS_TO_UNCACHED(KN01_SYS_VDAC);
E 8

	if (ptr->index > 256)
		return;

	vdac->mapWA = ptr->index; MachEmptyWriteBuffer();
	vdac->map = ptr->Entry.red; MachEmptyWriteBuffer();
	vdac->map = ptr->Entry.green; MachEmptyWriteBuffer();
	vdac->map = ptr->Entry.blue; MachEmptyWriteBuffer();
}

/*
 *----------------------------------------------------------------------
 *
D 8
 * PosCursor --
E 8
I 8
 * pmPosCursor --
E 8
 *
 *	Postion the cursor.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */
D 8
static void
PosCursor(x, y)
E 8
I 8
void
pmPosCursor(x, y)
E 8
	register int x, y;
{
D 8
	register PCCRegs *pcc = (PCCRegs *)MACH_CURSOR_REG_ADDR;
E 8
I 8
	register PCCRegs *pcc = (PCCRegs *)MACH_PHYS_TO_UNCACHED(KN01_SYS_PCC);
	register struct pmax_fb *fp = &pmfb;
E 8

D 8
	if (y < pmu.scrInfo.min_cur_y || y > pmu.scrInfo.max_cur_y)
		y = pmu.scrInfo.max_cur_y;
	if (x < pmu.scrInfo.min_cur_x || x > pmu.scrInfo.max_cur_x)
		x = pmu.scrInfo.max_cur_x;
	pmu.scrInfo.cursor.x = x;		/* keep track of real cursor */
	pmu.scrInfo.cursor.y = y;		/* position, indep. of mouse */
E 8
I 8
	if (y < fp->fbu->scrInfo.min_cur_y || y > fp->fbu->scrInfo.max_cur_y)
		y = fp->fbu->scrInfo.max_cur_y;
	if (x < fp->fbu->scrInfo.min_cur_x || x > fp->fbu->scrInfo.max_cur_x)
		x = fp->fbu->scrInfo.max_cur_x;
	fp->fbu->scrInfo.cursor.x = x;		/* keep track of real cursor */
	fp->fbu->scrInfo.cursor.y = y;		/* position, indep. of mouse */
E 8
	pcc->xpos = PCC_X_OFFSET + x;
	pcc->ypos = PCC_Y_OFFSET + y;
E 3
D 2
}

static
pmwakeup()
{

	if (pm_selp) {
		selwakeup(pm_selp, 0);
		pm_selp = 0;
	}
E 2
}
D 8
#endif
E 8
I 8

/*
 * pm keyboard and mouse input. Just punt to the generic ones in fb.c
 */
void
pmKbdEvent(ch)
	int ch;
{
	fbKbdEvent(ch, &pmfb);
}

void
pmMouseEvent(newRepPtr)
	MouseReport *newRepPtr;
{
	fbMouseEvent(newRepPtr, &pmfb);
}

void
pmMouseButtons(newRepPtr)
	MouseReport *newRepPtr;
{
	fbMouseButtons(newRepPtr, &pmfb);
}
#endif /* NDC */
#endif /* NPM */
E 8
E 1
