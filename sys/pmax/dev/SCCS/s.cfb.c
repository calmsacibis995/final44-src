h46110
s 00001/00000/00969
d D 8.2 95/06/02 17:26:16 ralph 11 10
c final changes for pmax 4.4-Lite II release
e
s 00002/00002/00967
d D 8.1 93/06/10 22:38:05 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00968
d D 7.9 93/05/09 15:50:36 ralph 9 8
c fix cursor bit order
e
s 00021/00000/00948
d D 7.8 93/04/13 20:03:00 ralph 8 7
c fix cursor for pmax emulation
e
s 00026/00038/00922
d D 7.7 93/04/05 21:35:26 ralph 7 6
c use vm_mmap instead of X kluge to map display into user address space.
e
s 00014/00029/00946
d D 7.6 92/12/20 11:36:39 ralph 6 5
c changes from Rick Macklem
e
s 00366/00795/00609
d D 7.5 92/11/15 15:49:13 ralph 5 4
c changes for maxine from Rick Macklem.
e
s 00003/00003/01401
d D 7.4 92/10/11 11:24:35 bostic 4 3
c use pmax as top directory, not mips
e
s 00017/00016/01387
d D 7.3 92/10/11 11:13:27 bostic 3 2
c make kernel includes standard
e
s 00011/00000/01392
d D 7.2 92/03/15 19:18:33 ralph 2 1
c redirect tty input back to console if X quits
e
s 01392/00000/00000
d D 7.1 92/03/09 14:24:32 bostic 1 0
c date and time created 92/03/09 14:24:32 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
D 5
 * Ralph Campbell.
E 5
I 5
 * Ralph Campbell and Rick Macklem.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
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
/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

D 5
#include "cfb.h"
E 5
I 5
#include <cfb.h>
E 5
#if NCFB > 0
D 5

/*
 * This is a device driver for the PMAG-BA color frame buffer
 * on the TURBOchannel.
 * XXX This is just to get a console working;
 *	it will need changes to work with X11R5.
 */

E 5
D 3
#include "param.h"
#include "time.h"
#include "kernel.h"
#include "ioctl.h"
#include "file.h"
#include "errno.h"
#include "proc.h"
#include "mman.h"
#include "vm/vm.h"
E 3
I 3
#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/errno.h>
#include <sys/proc.h>
#include <sys/mman.h>
E 3

D 3
#include "machine/machConst.h"
#include "machine/machMon.h"
#include "machine/dc7085cons.h"
#include "machine/pmioctl.h"
E 3
I 3
#include <vm/vm.h>
E 3

D 3
#include "device.h"
#include "cfbreg.h"
#include "font.c"
E 3
I 3
#include <machine/machConst.h>
D 5
#include <machine/machMon.h>
#include <machine/dc7085cons.h>
E 5
#include <machine/pmioctl.h>

I 5
#include <pmax/pmax/maxine.h>
#include <pmax/pmax/cons.h>
#include <pmax/pmax/pmaxtype.h>

E 5
D 4
#include <mips/dev/device.h>
#include <mips/dev/cfbreg.h>
#include <mips/dev/font.c>
E 4
I 4
#include <pmax/dev/device.h>
#include <pmax/dev/cfbreg.h>
D 5
#include <pmax/dev/font.c>
E 5
I 5
#include <pmax/dev/fbreg.h>
E 5
E 4
E 3

D 5
#define MAX_ROW	56
#define MAX_COL	80
E 5
I 5
#include <dc.h>
#include <dtop.h>
#include <scc.h>
E 5

I 8
#define PMAX	/* enable /dev/pm compatibility */

E 8
/*
D 5
 * Macro to translate from a time struct to milliseconds.
 */
#define TO_MS(tv) ((tv.tv_sec * 1000) + (tv.tv_usec / 1000))

static int	isMono;		/* true if B&W frame buffer */
static int	initialized;	/* true if 'probe' was successful */
static int	GraphicsOpen;	/* true if the graphics device is open */
static int	row, col;	/* row and col for console cursor */
static struct	selinfo cfb_selp;	/* process waiting for select */
static unsigned	fb_addr;	/* frame buffer kernel virtual address */
static unsigned	planemask_addr;	/* plane mask kernel virtual address */

/*
E 5
 * These need to be mapped into user space.
 */
D 5
static struct pmuaccess {
	PM_Info		scrInfo;
	pmEvent		events[PM_MAXEVQ];	
	pmTimeCoord	tcs[MOTION_BUFFER_SIZE];
} pmu;
E 5
I 5
struct fbuaccess cfbu;
struct pmax_fb cfbfb;
E 5

/*
D 5
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
E 5
 * Forward references.
 */
D 5
static void Scroll();
static void Blitc();
E 5
I 5
D 7
extern void fbScroll();
E 5

E 7
D 5
static void ScreenInit();
static void LoadCursor();
static void RestoreCursorColor();
static void CursorColor();
static void PosCursor();
static void InitColorMap();
static void LoadColorMap();
static void EnableVideo();
static void DisableVideo();
E 5
I 5
static void cfbScreenInit();
static void cfbLoadCursor();
static void cfbRestoreCursorColor();
static void cfbCursorColor();
void cfbPosCursor();
static void cfbInitColorMap();
static void cfbLoadColorMap();
static void bt459_set_cursor_ram(), bt459_video_on(), bt459_video_off();
static void bt459_select_reg(), bt459_write_reg();
static u_char bt459_read_reg();
static void cfbConfigMouse(), cfbDeconfigMouse();
E 5

D 5
extern void dcKBDPutc();
E 5
I 5
D 7
extern void fbKbdEvent(), fbMouseEvent(), fbMouseButtons();
E 7
void cfbKbdEvent(), cfbMouseEvent(), cfbMouseButtons();
#if NDC > 0
D 6
#include <machine/dc7085cons.h>
extern void dcPutc();
E 6
E 5
extern void (*dcDivertXInput)();
extern void (*dcMouseEvent)();
extern void (*dcMouseButtons)();
I 5
#endif
#if NSCC > 0
D 6
#include <pmax/dev/sccreg.h>
extern void sccPutc();
E 6
extern void (*sccDivertXInput)();
extern void (*sccMouseEvent)();
extern void (*sccMouseButtons)();
#endif
#if NDTOP > 0
D 6
#include <pmax/dev/dtopreg.h>
extern void dtopKBDPutc();
E 6
extern void (*dtopDivertXInput)();
extern void (*dtopMouseEvent)();
extern void (*dtopMouseButtons)();
#endif
extern int pmax_boardtype;
extern u_short defCursor[32];
extern struct consdev cn_tab;
E 5

int	cfbprobe();
struct	driver cfbdriver = {
	"cfb", cfbprobe, 0, 0,
};

I 5
#define	CFB_OFFSET_VRAM		0x0		/* from module's base */
#define CFB_OFFSET_BT459	0x200000	/* Bt459 registers */
#define CFB_OFFSET_IREQ		0x300000	/* Interrupt req. control */
#define CFB_OFFSET_ROM		0x380000	/* Diagnostic ROM */
#define CFB_OFFSET_RESET	0x3c0000	/* Bt459 resets on writes */
I 7
#define CFB_FB_SIZE		0x100000	/* frame buffer size */
E 7

E 5
/*
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
I 5
/*ARGSUSED*/
E 5
cfbprobe(cp)
	register struct pmax_ctlr *cp;
{
I 5
	register struct pmax_fb *fp = &cfbfb;
E 5

D 5
	if (!initialized) {
		if (!cfb_init(cp))
			return (0);
	}
	printf("cfb%d at nexus0 csr 0x%x priority %d\n",
		cp->pmax_unit, cp->pmax_addr, cp->pmax_pri);
E 5
I 5
	if (!fp->initialized && !cfbinit(cp->pmax_addr))
		return (0);
	printf("cfb0 (color display)\n");
E 5
	return (1);
}

D 5
/*
 *----------------------------------------------------------------------
 *
 * cfbKbdEvent --
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
cfbKbdEvent(ch)
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
	selwakeup(&cfb_selp);
}

/*
 *----------------------------------------------------------------------
 *
 * cfbMouseEvent --
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
cfbMouseEvent(newRepPtr) 
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
	selwakeup(&cfb_selp);
}

/*
 *----------------------------------------------------------------------
 *
 * cfbMouseButtons --
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
cfbMouseButtons(newRepPtr)
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
	selwakeup(&cfb_selp);

	lastRep = *newRepPtr;
	pmu.scrInfo.mswitches = newSwitch;
}

/*
 *----------------------------------------------------------------------
 *
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
		row = 0;
		return;
	}

	/*
	 *  The following is an optimization to cause the scrolling 
	 *  of text to be memory limited.  Basically the writebuffer is 
	 *  4 words (32 bits ea.) long so to achieve maximum speed we 
	 *  read and write in multiples of 4 words. We also limit the 
	 *  size to be MAX_COL characters for more speed. 
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
	src = (int *)(fb_addr + line);
	dest = (int *)(fb_addr);
	end = (int *)(fb_addr + (60 * line) - line);
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
	bzero(fb_addr + (row * line), 3 * line);
}

/*
 *----------------------------------------------------------------------
 *
 * cfbPutc --
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
cfbPutc(c)
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
		if (dcDebugGetc() == LK_HELP) {
			while (dcDebugGetc() != LK_HELP)
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
		for (i = 8 - (col & 0x7); i > 0; i--)
			Blitc(' ');
		break;

	case '\r':
		col = 0;
		break;

	case '\b':
		col--;
		if (col < 0)
			col = 0;
		break;

	case '\n':
		if (row + 1 >= MAX_ROW)
			Scroll();
		else
			row++;
		col = 0;
		break;

	case '\007':
		dcKBDPutc(LK_RING_BELL);
		break;

	default:
		/*
		 * 0xA1 to 0xFD are the printable characters added with 8-bit
		 * support.
		 */
		if (c < ' ' || c > '~' && c < 0xA1 || c > 0xFD)
			break;
		/*
		 * If the next character will wrap around then 
		 * increment row counter or scroll screen.
		 */
		if (col >= MAX_COL) {
			col = 0;
			if (row + 1 >= MAX_ROW)
				Scroll();
			else
				row++;
		}
		bRow = (char *)(fb_addr +
			(row * 15 & 0x3ff) * ote + col * colMult);
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
		col++; /* increment column counter */
	}
	if (!GraphicsOpen)
		PosCursor(col * 8, row * 15);
}

E 5
/*ARGSUSED*/
cfbopen(dev, flag)
	dev_t dev;
	int flag;
{
I 5
	register struct pmax_fb *fp = &cfbfb;
	int s;
E 5

D 5
	if (!initialized)
E 5
I 5
	if (!fp->initialized)
E 5
		return (ENXIO);
D 5
	if (GraphicsOpen)
E 5
I 5
	if (fp->GraphicsOpen)
E 5
		return (EBUSY);

D 5
	GraphicsOpen = 1;
	if (!isMono)
		InitColorMap();
E 5
I 5
	fp->GraphicsOpen = 1;
	cfbInitColorMap();
E 5
	/*
	 * Set up event queue for later
	 */
D 5
	pmu.scrInfo.qe.eSize = PM_MAXEVQ;
	pmu.scrInfo.qe.eHead = pmu.scrInfo.qe.eTail = 0;
	pmu.scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	pmu.scrInfo.qe.tcNext = 0;
	pmu.scrInfo.qe.timestamp_ms = TO_MS(time);
E 5
I 5
	fp->fbu->scrInfo.qe.eSize = PM_MAXEVQ;
	fp->fbu->scrInfo.qe.eHead = fp->fbu->scrInfo.qe.eTail = 0;
	fp->fbu->scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	fp->fbu->scrInfo.qe.tcNext = 0;
	fp->fbu->scrInfo.qe.timestamp_ms = TO_MS(time);
	cfbConfigMouse();
E 5
	return (0);
}

/*ARGSUSED*/
cfbclose(dev, flag)
	dev_t dev;
	int flag;
{
I 5
	register struct pmax_fb *fp = &cfbfb;
E 5
I 2
	int s;
E 2

D 5
	if (!GraphicsOpen)
E 5
I 5
	if (!fp->GraphicsOpen)
E 5
		return (EBADF);

D 5
	GraphicsOpen = 0;
	if (!isMono)
		InitColorMap();
I 2
	s = spltty();
	dcDivertXInput = (void (*)())0;
	dcMouseEvent = (void (*)())0;
	dcMouseButtons = (void (*)())0;
	splx(s);
E 2
	ScreenInit();
E 5
I 5
	fp->GraphicsOpen = 0;
	cfbInitColorMap();
	cfbDeconfigMouse();
	cfbScreenInit();
E 5
D 7
	vmUserUnmap();
E 7
D 5
	bzero(fb_addr, (isMono ? 1024 / 8 : 1024) * 864);
	PosCursor(col * 8, row * 15);
E 5
I 5
	bzero((caddr_t)fp->fr_addr, 1024 * 864);
	cfbPosCursor(fp->col * 8, fp->row * 15);
E 5
	return (0);
}

/*ARGSUSED*/
D 7
cfbioctl(dev, cmd, data, flag)
E 7
I 7
cfbioctl(dev, cmd, data, flag, p)
E 7
	dev_t dev;
I 11
	u_long cmd;
E 11
	caddr_t data;
I 7
	struct proc *p;
E 7
{
I 5
	register struct pmax_fb *fp = &cfbfb;
E 5
I 2
	int s;
E 2

	switch (cmd) {
	case QIOCGINFO:
D 7
	    {
		caddr_t addr;
		extern caddr_t vmUserMap();
E 7
I 7
		return (fbmmap(fp, dev, data, p));
E 7

D 7
		/*
		 * Map the all the data the user needs access to into
		 * user space.
		 */
D 5
		addr = vmUserMap(sizeof(pmu), (unsigned)&pmu);
E 5
I 5
		addr = vmUserMap(sizeof(struct fbuaccess), (unsigned)fp->fbu);
E 5
		if (addr == (caddr_t)0)
			goto mapError;
D 5
		*(PM_Info **)data = &((struct pmuaccess *)addr)->scrInfo;
		pmu.scrInfo.qe.events = ((struct pmuaccess *)addr)->events;
		pmu.scrInfo.qe.tcs = ((struct pmuaccess *)addr)->tcs;
E 5
I 5
		*(PM_Info **)data = &((struct fbuaccess *)addr)->scrInfo;
		fp->fbu->scrInfo.qe.events = ((struct fbuaccess *)addr)->events;
		fp->fbu->scrInfo.qe.tcs = ((struct fbuaccess *)addr)->tcs;
		fp->fbu->scrInfo.planemask = (char *)0;
E 5
		/*
D 5
		 * Map the plane mask into the user's address space.
		 */
		addr = vmUserMap(4, planemask_addr);
		if (addr == (caddr_t)0)
			goto mapError;
		pmu.scrInfo.planemask = (char *)addr;
		/*
E 5
		 * Map the frame buffer into the user's address space.
		 */
D 5
		addr = vmUserMap(isMono ? 256*1024 : 1024*1024, fb_addr);
E 5
I 5
		addr = vmUserMap(1024 * 1024, (unsigned)fp->fr_addr);
E 5
		if (addr == (caddr_t)0)
			goto mapError;
D 5
		pmu.scrInfo.bitmap = (char *)addr;
E 5
I 5
		fp->fbu->scrInfo.bitmap = (char *)addr;
E 5
		break;

	mapError:
		vmUserUnmap();
		printf("Cannot map shared data structures\n");
		return (EIO);
	    }

E 7
	case QIOCPMSTATE:
		/*
		 * Set mouse state.
		 */
D 5
		pmu.scrInfo.mouse = *(pmCursor *)data;
		PosCursor(pmu.scrInfo.mouse.x, pmu.scrInfo.mouse.y);
E 5
I 5
		fp->fbu->scrInfo.mouse = *(pmCursor *)data;
		cfbPosCursor(fp->fbu->scrInfo.mouse.x, fp->fbu->scrInfo.mouse.y);
E 5
		break;

	case QIOCINIT:
		/*
		 * Initialize the screen.
		 */
D 5
		ScreenInit();
E 5
I 5
		cfbScreenInit();
E 5
		break;

	case QIOCKPCMD:
	    {
		pmKpCmd *kpCmdPtr;
		unsigned char *cp;

		kpCmdPtr = (pmKpCmd *)data;
		if (kpCmdPtr->nbytes == 0)
			kpCmdPtr->cmd |= 0x80;
D 5
		if (!GraphicsOpen)
E 5
I 5
		if (!fp->GraphicsOpen)
E 5
			kpCmdPtr->cmd |= 1;
D 5
		dcKBDPutc((int)kpCmdPtr->cmd);
E 5
I 5
		(*fp->KBDPutc)(fp->kbddev, (int)kpCmdPtr->cmd);
E 5
		cp = &kpCmdPtr->par[0];
		for (; kpCmdPtr->nbytes > 0; cp++, kpCmdPtr->nbytes--) {
			if (kpCmdPtr->nbytes == 1)
				*cp |= 0x80;
D 5
			dcKBDPutc((int)*cp);
E 5
I 5
			(*fp->KBDPutc)(fp->kbddev, (int)*cp);
E 5
		}
I 7
		break;
E 7
D 5
		break;
E 5
	    }
I 5
D 7
	    break;
E 7
E 5

	case QIOCADDR:
D 5
		*(PM_Info **)data = &pmu.scrInfo;
E 5
I 5
		*(PM_Info **)data = &fp->fbu->scrInfo;
E 5
		break;

	case QIOWCURSOR:
D 5
		LoadCursor((unsigned short *)data);
E 5
I 5
		cfbLoadCursor((unsigned short *)data);
E 5
		break;

	case QIOWCURSORCOLOR:
D 5
		CursorColor((unsigned int *)data);
E 5
I 5
		cfbCursorColor((unsigned int *)data);
E 5
		break;

	case QIOSETCMAP:
D 5
		LoadColorMap((ColorMap *)data);
E 5
I 5
		cfbLoadColorMap((ColorMap *)data);
E 5
		break;

	case QIOKERNLOOP:
I 2
D 5
		s = spltty();
E 2
		dcDivertXInput = cfbKbdEvent;
		dcMouseEvent = cfbMouseEvent;
		dcMouseButtons = cfbMouseButtons;
I 2
		splx(s);
E 5
I 5
		cfbConfigMouse();
E 5
E 2
		break;

	case QIOKERNUNLOOP:
I 2
D 5
		s = spltty();
E 2
		dcDivertXInput = (void (*)())0;
		dcMouseEvent = (void (*)())0;
		dcMouseButtons = (void (*)())0;
I 2
		splx(s);
E 5
I 5
		cfbDeconfigMouse();
E 5
E 2
		break;

	case QIOVIDEOON:
D 5
		EnableVideo();
E 5
I 5
		cfbRestoreCursorColor();
		bt459_video_on();
E 5
		break;

	case QIOVIDEOOFF:
D 5
		DisableVideo();
E 5
I 5
		bt459_video_off();
E 5
		break;

	default:
		printf("cfb0: Unknown ioctl command %x\n", cmd);
		return (EINVAL);
	}
	return (0);
}

cfbselect(dev, flag, p)
	dev_t dev;
	int flag;
	struct proc *p;
{
I 5
	struct pmax_fb *fp = &cfbfb;
E 5

	switch (flag) {
	case FREAD:
D 5
		if (pmu.scrInfo.qe.eHead != pmu.scrInfo.qe.eTail)
E 5
I 5
		if (fp->fbu->scrInfo.qe.eHead != fp->fbu->scrInfo.qe.eTail)
E 5
			return (1);
D 5
		selrecord(p, &cfb_selp);
E 5
I 5
		selrecord(p, &fp->selp);
E 5
		break;
	}

	return (0);
}

I 7
/*
 * Return the physical page number that corresponds to byte offset 'off'.
 */
/*ARGSUSED*/
cfbmap(dev, off, prot)
	dev_t dev;
{
	int len;

	len = pmax_round_page(((vm_offset_t)&cfbu & PGOFSET) + sizeof(cfbu));
	if (off < len)
		return pmax_btop(MACH_CACHED_TO_PHYS(&cfbu) + off);
	off -= len;
	if (off >= cfbfb.fr_size)
		return (-1);
	return pmax_btop(MACH_UNCACHED_TO_PHYS(cfbfb.fr_addr) + off);
}

E 7
static u_char	cursor_RGB[6];	/* cursor color 2 & 3 */

/*
D 5
 * The default cursor.
E 5
I 5
 * XXX This assumes 2bits/cursor pixel so that the 1Kbyte cursor RAM
 * defines a 64x64 cursor. If the bt459 does not map the cursor RAM
 * this way, this code is Screwed!
E 5
 */
D 5
static unsigned short defCursor[1024] = {
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
E 5
I 5
static void
cfbLoadCursor(cursor)
	u_short *cursor;
{
I 8
#ifdef PMAX
E 8
	register int i, j, k, pos;
	register u_short ap, bp, out;
E 5

D 5
#define	CFB_OFFSET_VRAM		0x0		/* from module's base */
						/* Replicated at x100000 */
#define CFB_OFFSET_BT459	0x200000	/* Bt459 registers */
#define CFB_OFFSET_IREQ		0x300000	/* Interrupt req. control */
#define CFB_OFFSET_ROM		0x380000	/* Diagnostic ROM */
#define CFB_OFFSET_RESET	0x3c0000	/* Bt459 resets on writes */
E 5
I 5
	/*
	 * Fill in the cursor sprite using the A and B planes, as provided
	 * for the pmax.
	 * XXX This will have to change when the X server knows that this
	 * is not a pmax display.
	 */
	pos = 0;
	for (k = 0; k < 16; k++) {
		ap = *cursor;
		bp = *(cursor + 16);
		j = 0;
		while (j < 4) {
			out = 0;
			for (i = 0; i < 4; i++) {
I 6
D 9
#ifdef CURSOR_EL
E 9
I 9
#ifndef CURSOR_EB
E 9
E 6
				out = (out << 2) | ((ap & 0x1) << 1) |
					(bp & 0x1);
I 6
#else
				out = ((out >> 2) & 0x3f) |
					((ap & 0x1) << 7) |
					((bp & 0x1) << 6);
#endif
E 6
				ap >>= 1;
				bp >>= 1;
			}
			bt459_set_cursor_ram(pos, out);
			pos++;
			j++;
		}
		while (j < 16) {
			bt459_set_cursor_ram(pos, 0);
			pos++;
			j++;
		}
		cursor++;
	}
	while (pos < 1024) {
		bt459_set_cursor_ram(pos, 0);
		pos++;
	}
I 8
#endif /* PMAX */
E 8
}
E 5

/*
I 5
 * Set a cursor ram value.
 */
static void
bt459_set_cursor_ram(pos, val)
	int pos;
	register u_char val;
{
	register bt459_regmap_t *regs = (bt459_regmap_t *)
		(cfbfb.fr_addr + CFB_OFFSET_BT459);
	register int cnt;
	u_char nval;

	cnt = 0;
	do {
		bt459_write_reg(regs, BT459_REG_CRAM_BASE + pos, val);
		nval = bt459_read_reg(regs, BT459_REG_CRAM_BASE + pos);
	} while (val != nval && ++cnt < 10);
}

/*
E 5
 * Generic register access
 */
D 5
void
E 5
I 5
static void
E 5
bt459_select_reg(regs, regno)
	bt459_regmap_t *regs;
{
	regs->addr_lo = regno;
	regs->addr_hi = regno >> 8;
	MachEmptyWriteBuffer();
}

D 5
void
E 5
I 5
static void
E 5
bt459_write_reg(regs, regno, val)
	bt459_regmap_t *regs;
{
	regs->addr_lo = regno;
	regs->addr_hi = regno >> 8;
	MachEmptyWriteBuffer();
	regs->addr_reg = val;
	MachEmptyWriteBuffer();
}

D 5
unsigned char
E 5
I 5
static u_char
E 5
bt459_read_reg(regs, regno)
	bt459_regmap_t *regs;
{
	regs->addr_lo = regno;
	regs->addr_hi = regno >> 8;
	MachEmptyWriteBuffer();
D 5
	return regs->addr_reg;
E 5
I 5
	return (regs->addr_reg);
E 5
}

D 5
#ifdef DEBUG
bt459_print_colormap(regs)
	bt459_regmap_t *regs;
{
	register int i;

	bt459_select_reg(regs, 0);
	for (i = 0; i < 256; i++) {
		register unsigned red, green, blue;

		red = regs->addr_cmap;
		green = regs->addr_cmap;
		blue = regs->addr_cmap;
		printf("%x->[x%x x%x x%x]\n", i, red, green, blue);
	}
}
#endif

E 5
/*
D 5
 * Test to see if device is present.
 * Return true if found and initialized ok.
E 5
I 5
 * Initialization
E 5
 */
D 5
cfb_init(cp)
	register struct pmax_ctlr *cp;
E 5
I 5
int
cfbinit(cp)
	char *cp;
E 5
{
D 5
	bt459_regmap_t *regs;
E 5
I 5
	register bt459_regmap_t *regs;
	register struct pmax_fb *fp = &cfbfb;
E 5

	/* check for no frame buffer */
D 5
	if (badaddr(cp->pmax_addr, 4))
E 5
I 5
	if (badaddr(cp, 4))
E 5
		return (0);

D 5
	fb_addr = (unsigned)cp->pmax_addr + CFB_OFFSET_VRAM;
	planemask_addr = 0; /* XXX */
	regs = (bt459_regmap_t *)(fb_addr + CFB_OFFSET_BT459);
E 5
I 5
	fp->isMono = 0;
	fp->fr_addr = (char *)(cp + CFB_OFFSET_VRAM);
I 7
	fp->fr_size = CFB_FB_SIZE;
E 7
D 6
	fp->fbu = &cfbu;
E 6
I 6
	/*
D 7
	 * Must be in Uncached space or the Xserver sees a stale version of
	 * the event queue and acts totally wacko. I don't understand this,
	 * since the R3000 uses a physical address cache?
E 7
I 7
	 * Must be in Uncached space since the fbuaccess structure is
	 * mapped into the user's address space uncached.
E 7
	 */
	fp->fbu = (struct fbuaccess *)
		MACH_PHYS_TO_UNCACHED(MACH_CACHED_TO_PHYS(&cfbu));
E 6
	fp->posCursor = cfbPosCursor;
D 6
	switch (pmax_boardtype) {
#if NDC > 0
	case DS_3MAX:
		fp->KBDPutc = dcPutc;
		fp->kbddev = makedev(DCDEV, DCKBD_PORT);
		break;
#endif
#if NSCC > 0
	case DS_3MIN:
		fp->KBDPutc = sccPutc;
		fp->kbddev = makedev(SCCDEV, SCCKBD_PORT);
		break;
#endif
#if NDTOP > 0
	case DS_MAXINE:
		fp->KBDPutc = dtopKBDPutc;
		fp->kbddev = makedev(DTOPDEV, DTOPKBD_PORT);
		break;
#endif
	default:
		printf("Can't cofigure keyboard/mouse\n");
E 6
I 6
	if (tb_kbdmouseconfig(fp))
E 6
		return (0);
D 6
	};
E 6
E 5

I 5
	/*
	 * Initialize the screen.
	 */
	regs = (bt459_regmap_t *)(fp->fr_addr + CFB_OFFSET_BT459);

E 5
	if (bt459_read_reg(regs, BT459_REG_ID) != 0x4a)
		return (0);

D 5
	*(int *)(fb_addr + CFB_OFFSET_RESET) = 0;	/* force chip reset */
E 5
I 5
	/* Reset the chip */
	*(volatile int *)(fp->fr_addr + CFB_OFFSET_RESET) = 0;
E 5
	DELAY(2000);	/* ???? check right time on specs! ???? */

	/* use 4:1 input mux */
	bt459_write_reg(regs, BT459_REG_CMD0, 0x40);

	/* no zooming, no panning */
	bt459_write_reg(regs, BT459_REG_CMD1, 0x00);

	/*
	 * signature test, X-windows cursor, no overlays, SYNC* PLL,
	 * normal RAM select, 7.5 IRE pedestal, do sync
	 */
I 8
#ifndef PMAX
E 8
	bt459_write_reg(regs, BT459_REG_CMD2, 0xc2);
I 8
#else /* PMAX */
	bt459_write_reg(regs, BT459_REG_CMD2, 0xc0);
#endif /* PMAX */
E 8

	/* get all pixel bits */
	bt459_write_reg(regs, BT459_REG_PRM, 0xff);

	/* no blinking */
	bt459_write_reg(regs, BT459_REG_PBM, 0x00);

	/* no overlay */
	bt459_write_reg(regs, BT459_REG_ORM, 0x00);

	/* no overlay blink */
	bt459_write_reg(regs, BT459_REG_OBM, 0x00);

	/* no interleave, no underlay */
	bt459_write_reg(regs, BT459_REG_ILV, 0x00);

	/* normal operation, no signature analysis */
	bt459_write_reg(regs, BT459_REG_TEST, 0x00);

	/*
	 * no blinking, 1bit cross hair, XOR reg&crosshair,
	 * no crosshair on either plane 0 or 1,
	 * regular cursor on both planes.
	 */
	bt459_write_reg(regs, BT459_REG_CCR, 0xc0);

	/* home cursor */
	bt459_write_reg(regs, BT459_REG_CXLO, 0x00);
	bt459_write_reg(regs, BT459_REG_CXHI, 0x00);
	bt459_write_reg(regs, BT459_REG_CYLO, 0x00);
	bt459_write_reg(regs, BT459_REG_CYHI, 0x00);

	/* no crosshair window */
	bt459_write_reg(regs, BT459_REG_WXLO, 0x00);
	bt459_write_reg(regs, BT459_REG_WXHI, 0x00);
	bt459_write_reg(regs, BT459_REG_WYLO, 0x00);
	bt459_write_reg(regs, BT459_REG_WYHI, 0x00);
	bt459_write_reg(regs, BT459_REG_WWLO, 0x00);
	bt459_write_reg(regs, BT459_REG_WWHI, 0x00);
	bt459_write_reg(regs, BT459_REG_WHLO, 0x00);
	bt459_write_reg(regs, BT459_REG_WHHI, 0x00);

	/*
	 * Initialize screen info.
	 */
D 5
	pmu.scrInfo.max_row = MAX_ROW;
	pmu.scrInfo.max_col = MAX_COL;
	pmu.scrInfo.max_x = 1024;
	pmu.scrInfo.max_y = 864;
	pmu.scrInfo.max_cur_x = 1023;
	pmu.scrInfo.max_cur_y = 863;
	pmu.scrInfo.version = 11;
	pmu.scrInfo.mthreshold = 4;
	pmu.scrInfo.mscale = 2;
	pmu.scrInfo.min_cur_x = 0;
	pmu.scrInfo.min_cur_y = 0;
	pmu.scrInfo.qe.timestamp_ms = TO_MS(time);
	pmu.scrInfo.qe.eSize = PM_MAXEVQ;
	pmu.scrInfo.qe.eHead = pmu.scrInfo.qe.eTail = 0;
	pmu.scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	pmu.scrInfo.qe.tcNext = 0;
E 5
I 5
	fp->fbu->scrInfo.max_row = 56;
	fp->fbu->scrInfo.max_col = 80;
	fp->fbu->scrInfo.max_x = 1024;
	fp->fbu->scrInfo.max_y = 864;
	fp->fbu->scrInfo.max_cur_x = 1023;
	fp->fbu->scrInfo.max_cur_y = 863;
	fp->fbu->scrInfo.version = 11;
	fp->fbu->scrInfo.mthreshold = 4;
	fp->fbu->scrInfo.mscale = 2;
	fp->fbu->scrInfo.min_cur_x = 0;
	fp->fbu->scrInfo.min_cur_y = 0;
	fp->fbu->scrInfo.qe.timestamp_ms = TO_MS(time);
	fp->fbu->scrInfo.qe.eSize = PM_MAXEVQ;
	fp->fbu->scrInfo.qe.eHead = fp->fbu->scrInfo.qe.eTail = 0;
	fp->fbu->scrInfo.qe.tcSize = MOTION_BUFFER_SIZE;
	fp->fbu->scrInfo.qe.tcNext = 0;
E 5

	/*
	 * Initialize the color map, the screen, and the mouse.
	 */
D 5
	InitColorMap();
	ScreenInit();
	Scroll();
E 5
I 5
	cfbInitColorMap();
	cfbScreenInit();
	fbScroll(fp);
E 5

D 5
	initialized = 1;
E 5
I 5
	fp->initialized = 1;
	if (cn_tab.cn_fb == (struct pmax_fb *)0)
		cn_tab.cn_fb = fp;
E 5
	return (1);
}

/*
 * ----------------------------------------------------------------------------
 *
D 5
 * ScreenInit --
E 5
I 5
 * cfbScreenInit --
E 5
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
D 5
ScreenInit()
E 5
I 5
cfbScreenInit()
E 5
{
I 5
	register struct pmax_fb *fp = &cfbfb;
E 5

	/*
	 * Home the cursor.
D 5
	 * We want an LSI terminal emulation. We want the graphics
E 5
I 5
	 * We want an LSI terminal emulation.  We want the graphics
E 5
	 * terminal to scroll from the bottom. So start at the bottom.
	 */
D 5
	row = 55;
	col = 0;
E 5
I 5
	fp->row = 55;
	fp->col = 0;
E 5

	/*
	 * Load the cursor with the default values
	 *
	 */
D 5
	LoadCursor(defCursor);
E 5
I 5
	cfbLoadCursor(defCursor);
E 5
}

/*
 * ----------------------------------------------------------------------------
 *
D 5
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
	bt459_regmap_t *regs = (bt459_regmap_t *)(fb_addr + CFB_OFFSET_BT459);
	register int i, j;

	/*
	 * As per specs, must run a check to see if we
	 * had contention. If so, re-write the cursor.
	 */
	for (j = 0; j < 2; j++) {
		/* loop once to write */
		bt459_select_reg(regs, BT459_REG_CRAM_BASE);
		for (i = 0; i < 1024; i++) {
			regs->addr_reg = cur[i];
			MachEmptyWriteBuffer();
		}

		/* loop to check, if fail write again */
		bt459_select_reg(regs, BT459_REG_CRAM_BASE);
		for (i = 0; i < 1024; i++)
			if (regs->addr_reg != cur[i])
				break;
		if (i == 1024)
			break;	/* all went well first shot */
	}
}

/*
 * ----------------------------------------------------------------------------
 *
E 5
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
D 5
RestoreCursorColor()
E 5
I 5
cfbRestoreCursorColor()
E 5
{
D 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(fb_addr + CFB_OFFSET_BT459);
E 5
I 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(cfbfb.fr_addr + CFB_OFFSET_BT459);
E 5
	register int i;

I 8
#ifndef PMAX
E 8
	bt459_select_reg(regs, BT459_REG_CCOLOR_2);
	for (i = 0; i < 6; i++) {
		regs->addr_reg = cursor_RGB[i];
		MachEmptyWriteBuffer();
	}
I 8
#else /* PMAX */
	bt459_select_reg(regs, BT459_REG_CCOLOR_1);
	for (i = 0; i < 3; i++) {
		regs->addr_reg = cursor_RGB[i];
		MachEmptyWriteBuffer();
	}
	bt459_select_reg(regs, BT459_REG_CCOLOR_3);
	for (i = 3; i < 6; i++) {
		regs->addr_reg = cursor_RGB[i];
		MachEmptyWriteBuffer();
	}
#endif /* PMAX */
E 8
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
D 5
CursorColor(color)
E 5
I 5
cfbCursorColor(color)
E 5
	unsigned int color[];
{
	register int i, j;

	for (i = 0; i < 6; i++)
		cursor_RGB[i] = (u_char)(color[i] >> 8);

D 5
	RestoreCursorColor();
E 5
I 5
	cfbRestoreCursorColor();
E 5
}

/*
 *----------------------------------------------------------------------
 *
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
D 5
static void
PosCursor(x, y)
E 5
I 5
void
cfbPosCursor(x, y)
E 5
	register int x, y;
{
D 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(fb_addr + CFB_OFFSET_BT459);
E 5
I 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(cfbfb.fr_addr + CFB_OFFSET_BT459);
	register struct pmax_fb *fp = &cfbfb;
E 5

D 5
	if (y < pmu.scrInfo.min_cur_y || y > pmu.scrInfo.max_cur_y)
		y = pmu.scrInfo.max_cur_y;
	if (x < pmu.scrInfo.min_cur_x || x > pmu.scrInfo.max_cur_x)
		x = pmu.scrInfo.max_cur_x;
	pmu.scrInfo.cursor.x = x;		/* keep track of real cursor */
	pmu.scrInfo.cursor.y = y;		/* position, indep. of mouse */
E 5
I 5
	if (y < fp->fbu->scrInfo.min_cur_y || y > fp->fbu->scrInfo.max_cur_y)
		y = fp->fbu->scrInfo.max_cur_y;
	if (x < fp->fbu->scrInfo.min_cur_x || x > fp->fbu->scrInfo.max_cur_x)
		x = fp->fbu->scrInfo.max_cur_x;
	fp->fbu->scrInfo.cursor.x = x;		/* keep track of real cursor */
	fp->fbu->scrInfo.cursor.y = y;		/* position, indep. of mouse */
E 5

	x += 219;
	y += 34;

	bt459_select_reg(regs, BT459_REG_CXLO);
	regs->addr_reg = x;
	MachEmptyWriteBuffer();
	regs->addr_reg = x >> 8;
	MachEmptyWriteBuffer();
	regs->addr_reg = y;
	MachEmptyWriteBuffer();
	regs->addr_reg = y >> 8;
	MachEmptyWriteBuffer();
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
 *	The colormap is initialized appropriately.
 *
 * ----------------------------------------------------------------------------
 */
static void
D 5
InitColorMap()
E 5
I 5
cfbInitColorMap()
E 5
{
D 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(fb_addr + CFB_OFFSET_BT459);
E 5
I 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(cfbfb.fr_addr + CFB_OFFSET_BT459);
E 5
	register int i;

	bt459_select_reg(regs, 0);
	regs->addr_cmap = 0; MachEmptyWriteBuffer();
	regs->addr_cmap = 0; MachEmptyWriteBuffer();
	regs->addr_cmap = 0; MachEmptyWriteBuffer();

	for (i = 1; i < 256; i++) {
		regs->addr_cmap = 0xff; MachEmptyWriteBuffer();
		regs->addr_cmap = 0xff; MachEmptyWriteBuffer();
		regs->addr_cmap = 0xff; MachEmptyWriteBuffer();
	}

	for (i = 0; i < 3; i++) {
		cursor_RGB[i] = 0x00;
		cursor_RGB[i + 3] = 0xff;
	}
D 5
	RestoreCursorColor();
E 5
I 5
	cfbRestoreCursorColor();
E 5
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
D 5
LoadColorMap(ptr)
E 5
I 5
cfbLoadColorMap(ptr)
E 5
	ColorMap *ptr;
{
D 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(fb_addr + CFB_OFFSET_BT459);
E 5
I 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(cfbfb.fr_addr + CFB_OFFSET_BT459);
E 5

	if (ptr->index > 256)
		return;

	bt459_select_reg(regs, ptr->index);

	regs->addr_cmap = ptr->Entry.red; MachEmptyWriteBuffer();
	regs->addr_cmap = ptr->Entry.green; MachEmptyWriteBuffer();
	regs->addr_cmap = ptr->Entry.blue; MachEmptyWriteBuffer();
}

/*
 * Video on/off state.
 */
D 5
struct vstate {
E 5
I 5
static struct vstate {
E 5
	u_char	color0[3];	/* saved color map entry zero */
	u_char	off;		/* TRUE if display is off */
} vstate;

/*
 * ----------------------------------------------------------------------------
 *
D 5
 * EnableVideo --
E 5
I 5
 * bt459_video_on
E 5
 *
 *	Enable the video display.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The display is enabled.
 *
 * ----------------------------------------------------------------------------
 */
static void
D 5
EnableVideo()
E 5
I 5
bt459_video_on()
E 5
{
D 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(fb_addr + CFB_OFFSET_BT459);
E 5
I 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(cfbfb.fr_addr + CFB_OFFSET_BT459);
E 5

	if (!vstate.off)
		return;

	/* restore old color map entry zero */
	bt459_select_reg(regs, 0);
	regs->addr_cmap = vstate.color0[0];
	MachEmptyWriteBuffer();
	regs->addr_cmap = vstate.color0[1];
	MachEmptyWriteBuffer();
	regs->addr_cmap = vstate.color0[2];
	MachEmptyWriteBuffer();

	/* enable normal display */
	bt459_write_reg(regs, BT459_REG_PRM, 0xff);
	bt459_write_reg(regs, BT459_REG_CCR, 0xc0);

	vstate.off = 0;
}

/*
 * ----------------------------------------------------------------------------
 *
D 5
 * DisableVideo --
E 5
I 5
 * bt459_video_off
E 5
 *
 *	Disable the video display.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The display is disabled.
 *
 * ----------------------------------------------------------------------------
 */
static void
D 5
DisableVideo()
E 5
I 5
bt459_video_off()
E 5
{
D 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(fb_addr + CFB_OFFSET_BT459);
E 5
I 5
	bt459_regmap_t *regs = (bt459_regmap_t *)(cfbfb.fr_addr + CFB_OFFSET_BT459);
E 5

	if (vstate.off)
		return;

	/* save old color map entry zero */
	bt459_select_reg(regs, 0);
	vstate.color0[0] = regs->addr_cmap;
	vstate.color0[1] = regs->addr_cmap;
	vstate.color0[2] = regs->addr_cmap;

	/* set color map entry zero to zero */
	bt459_select_reg(regs, 0);
	regs->addr_cmap = 0;
	MachEmptyWriteBuffer();
	regs->addr_cmap = 0;
	MachEmptyWriteBuffer();
	regs->addr_cmap = 0;
	MachEmptyWriteBuffer();

	/* disable display */
	bt459_write_reg(regs, BT459_REG_PRM, 0);
	bt459_write_reg(regs, BT459_REG_CCR, 0);

	vstate.off = 1;
}
I 5

/*
 * cfb keyboard and mouse input. Just punt to the generic ones in fb.c
 */
void
cfbKbdEvent(ch)
	int ch;
{
	fbKbdEvent(ch, &cfbfb);
}

void
cfbMouseEvent(newRepPtr)
	MouseReport *newRepPtr;
{
	fbMouseEvent(newRepPtr, &cfbfb);
}

void
cfbMouseButtons(newRepPtr)
	MouseReport *newRepPtr;
{
	fbMouseButtons(newRepPtr, &cfbfb);
}

/*
 * Configure the mouse and keyboard based on machine type
 */
static void
cfbConfigMouse()
{
	int s;

	s = spltty();
	switch (pmax_boardtype) {
#if NDC > 0
	case DS_3MAX:
		dcDivertXInput = cfbKbdEvent;
		dcMouseEvent = cfbMouseEvent;
		dcMouseButtons = cfbMouseButtons;
		break;
E 5
#endif
I 5
#if NSCC > 1
	case DS_3MIN:
		sccDivertXInput = cfbKbdEvent;
		sccMouseEvent = cfbMouseEvent;
		sccMouseButtons = cfbMouseButtons;
		break;
#endif
#if NDTOP > 0
	case DS_MAXINE:
		dtopDivertXInput = cfbKbdEvent;
		dtopMouseEvent = cfbMouseEvent;
		dtopMouseButtons = cfbMouseButtons;
		break;
#endif
	default:
		printf("Can't configure mouse/keyboard\n");
	};
	splx(s);
}

/*
 * and deconfigure them
 */
static void
cfbDeconfigMouse()
{
	int s;

	s = spltty();
	switch (pmax_boardtype) {
#if NDC > 0
	case DS_3MAX:
		dcDivertXInput = (void (*)())0;
		dcMouseEvent = (void (*)())0;
		dcMouseButtons = (void (*)())0;
		break;
#endif
#if NSCC > 1
	case DS_3MIN:
		sccDivertXInput = (void (*)())0;
		sccMouseEvent = (void (*)())0;
		sccMouseButtons = (void (*)())0;
		break;
#endif
#if NDTOP > 0
	case DS_MAXINE:
		dtopDivertXInput = (void (*)())0;
		dtopMouseEvent = (void (*)())0;
		dtopMouseButtons = (void (*)())0;
		break;
#endif
	default:
		printf("Can't deconfigure mouse/keyboard\n");
	};
}
#endif /* NCFB */
E 5
E 1
