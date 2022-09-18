/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	kd_mouse.c,v $
 * Revision 1.5.1.7  91/03/01  22:44:01  rvb
 * 	Now get the MicroSoft Serial Line Mouse debugged, having
 * 	borrowed a mouse for testing.
 * 	[91/03/01            rvb]
 * 
 * Revision 1.5.1.6  91/01/30  08:51:43  rvb
 * 	Add support for MicroSoft Serial Line Mouse from Philippe.
 * 
 * Revision 1.5.1.5  90/11/27  13:44:12  rvb
 * 	Synched 2.5 & 3.0 at I386q (r1.5.1.5) & XMK35 (r2.3)
 * 	[90/11/15            rvb]
 * 
 * Revision 1.5.1.4  90/07/10  11:45:04  rvb
 * 	Allow mouse minor to select the serial line the mouse is on.
 * 	[90/06/15            rvb]
 * 
 * Revision 2.2  90/05/21  13:27:25  dbg
 * 	Convert for pure kernel.
 * 	[90/04/24            dbg]
 * 
 * Revision 1.5.1.3  90/02/28  15:50:25  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 1.5.1.2  90/01/08  13:30:55  rvb
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.5.1.1  89/10/22  11:34:32  rvb
 * 	Received from Intel October 5, 1989.
 * 	[89/10/13            rvb]
 * 
 * Revision 1.5  89/07/17  10:41:24  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 	[89/07/11            rvb]
 * 
 * Revision 1.4.1.1  89/04/27  12:21:17  kupfer
 * Merge X79 with our latest and greatest.
 * 
 * Revision 1.2.1.1  89/04/27  11:54:40  kupfer
 * X79 from CMU.
 * 
 * Revision 1.4  89/03/09  20:06:46  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:42:38  gm0w
 * 	Changes for cleanup.
 * 
 */
 
/* **********************************************************************
 File:         kd_mouse.c
 Description:  mouse driver as part of keyboard/display driver

 $ Header: $

 Copyright Ing. C. Olivetti & C. S.p.A. 1989.
 All rights reserved.
********************************************************************** */
/*
  Copyright 1988, 1989 by Olivetti Advanced Technology Center, Inc.,
Cupertino, California.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Olivetti
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

  OLIVETTI DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OLIVETTI BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
 * Hacked up support for serial mouse connected to COM1, using Mouse
 * Systems 5-byte protocol at 1200 baud.  This should work for
 * Mouse Systems, SummaMouse, and Logitek C7 mice.
 *
 * The interface provided by /dev/mouse is a series of events as
 * described in i386at/kd.h.
 */

#include <mach/boolean.h>
#include <sys/types.h>
#ifdef	MACH_KERNEL
#include <device/errno.h>
#include <device/io_req.h>
#else	MACH_KERNEL
#include <sys/file.h>
#include <sys/errno.h>
#include <kern/thread.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#endif	MACH_KERNEL
#include <i386/ipl.h>
#include <i386at/atbus.h>
#include <i386at/kd.h>
#include <i386at/kd_queue.h>
#include <i386at/i8250.h>

static int (*oldvect)();		/* old interrupt vector */
static int oldunit;
extern	struct	isa_dev	*cominfo[];

kd_event_queue mouse_queue;		/* queue of mouse events */
boolean_t mouse_in_use = FALSE;
#ifdef	MACH_KERNEL
queue_head_t	mouse_read_queue = { &mouse_read_queue, &mouse_read_queue };
#else	MACH_KERNEL
struct proc *mouse_sel = 0;		/* selecting process, if any */
short mousepgrp = 0;		/* process group leader when dev is open */
#endif	MACH_KERNEL

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
int mouseflag = 0;
#define MOUSE_COLL	1		/* select collision */
#define MOUSE_ASYNC	2		/* user wants asynch notification */
#define MOUSE_NBIO	4		/* user wants non-blocking I/O */
#endif	MACH_KERNEL

/*
 * The state of the 3 buttons is encoded in the low-order 3 bits (both
 * here and in other variables in the driver).
 */
u_char lastbuttons;		/* previous state of mouse buttons */
#define MOUSE_UP	1
#define MOUSE_DOWN	0
#define MOUSE_ALL_UP	0x7

int mouseintr();
void mouse_enqueue();

/*
 * init_mouse_hw - initialize the serial port.
 */
init_mouse_hw(base_addr)
{
	outb(base_addr + RIE, 0);
	outb(base_addr + RLC, LCDLAB);
	outb(base_addr + RDLSB, BCNT1200 & 0xff);
	outb(base_addr + RDMSB, (BCNT1200 >> 8) & 0xff);
	outb(base_addr + RLC, LC8);
	outb(base_addr + RMC, MCDTR | MCRTS | MCOUT2);
	outb(base_addr + RIE, IERD | IELS);
}


/*
 * mouseopen - Verify that the request is read-only, initialize,
 * and remember process group leader.
 */
/*
 * Low 3 bits of minor are the com port #.
 * The high 5 bits of minor are the mouse type
 */
#define	MOUSE_SYSTEM_MOUSE	0
#define MICROSOFT_MOUSE		1
static int mouse_type;
static int mousebufsize;

/*ARGSUSED*/
mouseopen(dev, flags)
	dev_t dev;
	int flags;
{
	int unit = minor(dev) & 0x7;
	int mouse_pic = cominfo[unit]->dev_pic;
	caddr_t base_addr  = cominfo[unit]->dev_addr;
	int s;

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	if (flags & FWRITE)
		return(ENODEV);
#endif	MACH_KERNEL
	if (mouse_in_use)
		return(EBUSY);

	mouse_type = ((minor(dev) & 0xf8) >> 3);
	if (mouse_type == MICROSOFT_MOUSE) {
		mousebufsize = 3;
	} else {
		mousebufsize = 5;
	}

	s = splhi();		/* disable interrupts */

	kdq_reset(&mouse_queue);
	mouse_in_use = TRUE;		/* locking? */
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	mousepgrp = u.u_procp->p_pgrp;
#endif	MACH_KERNEL
	lastbuttons = MOUSE_ALL_UP;

	oldvect = ivect[mouse_pic];
	ivect[mouse_pic] = mouseintr;

	oldunit = iunit[mouse_pic];
	iunit[mouse_pic] = unit;

		/* XXX other arrays to init? */
	splx(s);		/* XXX - should come after init? */

	init_mouse_hw(base_addr);

	return(0);
}


/*
 * mouseclose - Disable interrupts on the serial port, reset driver flags, 
 * and restore the serial port interrupt vector.
 */
/*ARGSUSED*/
mouseclose(dev, flags)
	dev_t dev;
	int flags;
{
	int o_pri = splhi();		/* mutex with open() */
	int unit = minor(dev) & 0x7;
	int mouse_pic = cominfo[unit]->dev_pic;
	caddr_t base_addr  = cominfo[unit]->dev_addr;

	assert(ivect[mouse_pic] == mouseintr);
	outb(base_addr + RIE, 0);	/* disable serial port */
	ivect[mouse_pic] = oldvect;
	iunit[mouse_pic] = oldunit;

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	mousepgrp = 0;
	mouseflag = 0;
	mouse_sel = 0;
#endif	MACH_KERNEL
	mouse_in_use = FALSE;
	kdq_reset(&mouse_queue);		/* paranoia */
	(void)splx(o_pri);
}


#ifdef	MACH_KERNEL
#else	MACH_KERNEL
/*
 * mouseioctl - handling for asynch & non-blocking I/O.
 */

/*ARGSUSED*/
mouseioctl(dev, cmd, data, flag)
	dev_t dev;
	int cmd;
	caddr_t data;
	int flag;
{
	int s = SPLKD();
	int err = 0;

	switch (cmd) {
	case FIONBIO:
		if (*(int *)data)
			mouseflag |= MOUSE_NBIO;
		else
			mouseflag &= ~MOUSE_NBIO;
		break;
	case FIOASYNC:
		if (*(int *)data)
			mouseflag |= MOUSE_ASYNC;
		else
			mouseflag &= ~MOUSE_ASYNC;
		break;
	default:
		err = ENOTTY;
		break;
	}

	splx(s);
	return(err);
}


/*
 * mouseselect - check for pending events, etc.
 */

/*ARGSUSED*/
mouseselect(dev, rw)
{
	int s = SPLKD();

	if (!kdq_empty(&mouse_queue)) {
		splx(s);
		return(1);
	}

	if (mouse_sel)
		mouseflag |= MOUSE_COLL;
	else
		mouse_sel = (struct proc *)current_thread();
					/* eeeyuck */
	
	splx(s);
	return(0);
}
#endif	MACH_KERNEL

/*
 * mouseread - dequeue and return any queued events.
 */
#ifdef	MACH_KERNEL
boolean_t	mouse_read_done();	/* forward */

mouseread(dev, ior)
	dev_t	dev;
	register io_req_t	ior;
{
	register int	err, s, count;

	err = device_read_alloc(ior, (vm_size_t)ior->io_count);
	if (err != KERN_SUCCESS)
	    return (err);

	s = SPLKD();
	if (kdq_empty(&mouse_queue)) {
	    if (ior->io_mode & D_NOWAIT) {
		splx(s);
		return (D_WOULD_BLOCK);
	    }
	    ior->io_done = mouse_read_done;
	    enqueue_tail(&mouse_read_queue, (queue_entry_t)ior);
	    splx(s);
	    return (D_IO_QUEUED);
	}
	count = 0;
	while (!kdq_empty(&mouse_queue) && count < ior->io_count) {
	    register kd_event *ev;

	    ev = kdq_get(&mouse_queue);
	    *(kd_event *)(&ior->io_data[count]) = *ev;
	    count += sizeof(kd_event);
	}
	splx(s);
	ior->io_residual = ior->io_count - count;
	return (D_SUCCESS);
}

boolean_t mouse_read_done(ior)
	register io_req_t	ior;
{
	register int	s, count;

	s = SPLKD();
	if (kdq_empty(&mouse_queue)) {
	    ior->io_done = mouse_read_done;
	    enqueue_tail(&mouse_read_queue, (queue_entry_t)ior);
	    splx(s);
	    return (FALSE);
	}

	count = 0;
	while (!kdq_empty(&mouse_queue) && count < ior->io_count) {
	    register kd_event *ev;

	    ev = kdq_get(&mouse_queue);
	    *(kd_event *)(&ior->io_data[count]) = *ev;
	    count += sizeof(kd_event);
	}
	splx(s);

	ior->io_residual = ior->io_count - count;
	ds_read_done(ior);

	return (TRUE);
}

#else	MACH_KERNEL
/*ARGSUSED*/
mouseread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	int s = SPLKD();
	int err = 0;
	kd_event *ev;
	int i;
	char *cp;

	if (kdq_empty(&mouse_queue))
		if (mouseflag & MOUSE_NBIO) {
			err = EWOULDBLOCK;
			goto done;
		} else 
			while (kdq_empty(&mouse_queue)) {
				splx(s);
				sleep((caddr_t)&mouse_queue, TTIPRI);
				s = SPLKD();
			}

	while (!kdq_empty(&mouse_queue) && uio->uio_resid >= sizeof(kd_event)) {
		ev = kdq_get(&mouse_queue);
		for (cp = (char *)ev, i = 0; i < sizeof(kd_event);
		     ++i, ++cp) {
			err = ureadc(*cp, uio);
			if (err)
				goto done;
		}
	}

done:
	splx(s);
	return(err);
}
#endif	MACH_KERNEL


/*
 * mouseintr - Get a byte and pass it up for handling.  Called at SPLKD.
 */
mouseintr(unit)
{
	caddr_t base_addr  = cominfo[unit]->dev_addr;
	unsigned char id, ls;

	/* get reason for interrupt and line status */
	id = inb(base_addr + RID);
	ls = inb(base_addr + RLS);

	/* handle status changes */
	if (id == IDLS) {
		if (ls & LSDR) {
			inb(base_addr + RDAT);	/* flush bad character */
		}
		return;			/* ignore status change */
	}

	if (id & IDRD) {
		mouse_handle_byte((u_char)(inb(base_addr + RDAT) & 0xff));
	}
}


/*
 * handle_byte - Accumulate bytes until we have an entire packet.
 * If the mouse has moved or any of the buttons have changed state (up
 * or down), enqueue the corresponding events.
 * Called at SPLKD.
 * XXX - magic numbers.
 */
mouse_handle_byte(ch)
	u_char ch;
{
#define MOUSEBUFSIZE	5		/* num bytes def'd by protocol */
	static u_char mousebuf[MOUSEBUFSIZE];	/* 5-byte packet from mouse */
	static short mbindex = 0;	/* index into mousebuf */

	if (mbindex == 0) {
		if (mouse_type == MICROSOFT_MOUSE) {
			if ((ch & 0xc0) != 0xc0)
				return;
		} else if ((ch & 0xf8) != 0x80)
			return;
	}

	mousebuf[mbindex++] = ch;
	if (mbindex < mousebufsize)
		return;
	
	/* got a packet */
	mbindex = 0;

	if (mouse_type == MOUSE_SYSTEM_MOUSE)
		mouse_packet_mouse_system_mouse(mousebuf);
	else
		mouse_packet_microsoft_mouse(mousebuf);
}

mouse_packet_mouse_system_mouse(mousebuf)
u_char mousebuf[MOUSEBUFSIZE];
{
	u_char buttons, buttonchanges;
	struct mouse_motion moved;

	buttons = mousebuf[0] & 0x7;	/* get current state of buttons */
	buttonchanges = buttons ^ lastbuttons;
	moved.mm_deltaX = (char)mousebuf[1] + (char)mousebuf[3];
	moved.mm_deltaY = (char)mousebuf[2] + (char)mousebuf[4];

	if (moved.mm_deltaX != 0 || moved.mm_deltaY != 0)
		mouse_moved(moved);

	if (buttonchanges != 0) {
		lastbuttons = buttons;
		if (buttonchanges & 1)
			mouse_button(MOUSE_RIGHT, buttons & 1);
		if (buttonchanges & 2)
			mouse_button(MOUSE_MIDDLE, (buttons & 2) >> 1);
		if (buttonchanges & 4)
			mouse_button(MOUSE_LEFT, (buttons & 4) >> 2);
	}
}

/* same as above for microsoft mouse */
/*
 * 3 byte microsoft format used
 *
 * 7  6  5  4  3  2  1  0
 * 1  1  L  R  Y7 Y6 X7 X6
 * 1  0  X5 X4 X3 X3 X1 X0
 * 1  0  Y5 Y4 Y3 Y2 Y1 Y0
 *
 * TODO: 3 button implementation on 2 button mouse
 */
mouse_packet_microsoft_mouse(mousebuf)
u_char mousebuf[MOUSEBUFSIZE];
{
	u_char buttons, buttonchanges;
	struct mouse_motion moved;

	buttons = ((mousebuf[0] & 0x30) >> 4);
			/* get current state of buttons */
	if (buttons == 0x03)	/* both buttons down */
		buttons = 0x04;
	buttons = (~buttons) & 0x07;	/* convert to not pressed */

	buttonchanges = buttons ^ lastbuttons;
	moved.mm_deltaX = ((mousebuf[0] & 0x03) << 6) | (mousebuf[1] & 0x3F);
	moved.mm_deltaY = ((mousebuf[0] & 0x0c) << 4) | (mousebuf[2] & 0x3F);
	if (moved.mm_deltaX & 0x80)	/* negative, in fact */
		moved.mm_deltaX = moved.mm_deltaX - 0x100;
	if (moved.mm_deltaY & 0x80)	/* negative, in fact */
		moved.mm_deltaY = moved.mm_deltaY - 0x100;
	/* and finally the Y orientation is different for the microsoft mouse */
	moved.mm_deltaY = -moved.mm_deltaY;

	if (moved.mm_deltaX != 0 || moved.mm_deltaY != 0)
		mouse_moved(moved);

	if (buttonchanges != 0) {
		lastbuttons = buttons;
		if (buttonchanges & 1)
			mouse_button(MOUSE_RIGHT, (buttons & 1) ?
						MOUSE_UP : MOUSE_DOWN);
		if (buttonchanges & 2)
			mouse_button(MOUSE_LEFT, (buttons & 2) ?
						MOUSE_UP : MOUSE_DOWN);
		if (buttonchanges & 4)
			mouse_button(MOUSE_MIDDLE, (buttons & 4) ?
						MOUSE_UP : MOUSE_DOWN);
	}
}

/*
 * Enqueue a mouse-motion event.  Called at SPLKD.
 */
mouse_moved(where)
	struct mouse_motion where;
{
	kd_event ev;

	ev.type = MOUSE_MOTION;
	ev.time = time;
	ev.value.mmotion = where;
	mouse_enqueue(&ev);
}


/*
 * Enqueue an event for mouse button press or release.  Called at SPLKD.
 */
mouse_button(which, direction)
	kev_type which;
	u_char direction;
{
	kd_event ev;

	ev.type = which;
	ev.time = time;
	ev.value.up = (direction == MOUSE_UP) ? TRUE : FALSE;
	mouse_enqueue(&ev);
}


/*
 * mouse_enqueue - enqueue an event and wake up selecting processes, if
 * any.  Called at SPLKD.
 */

void
mouse_enqueue(ev)
	kd_event *ev;
{
	if (kdq_full(&mouse_queue))
		printf("mouse: queue full\n");
	else
		kdq_put(&mouse_queue, ev);

#ifdef	MACH_KERNEL
	{
	    register io_req_t	ior;
	    while ((ior = (io_req_t)dequeue_head(&mouse_read_queue)) != 0)
		iodone(ior);
	}
#else	MACH_KERNEL
	if (mouse_sel) {
		selwakeup(mouse_sel, mouseflag & MOUSE_COLL);
		mouse_sel = 0;
		mouseflag &= ~MOUSE_COLL;
	}
	if (mouseflag & MOUSE_ASYNC)
		gsignal(mousepgrp, SIGIO);
	wakeup((caddr_t)&mouse_queue);
#endif	MACH_KERNEL
}
