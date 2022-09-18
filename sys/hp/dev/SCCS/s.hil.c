h42152
s 00004/00002/01626
d D 8.3 95/01/09 17:38:52 cgd 20 19
c strategy returns void, ioctl cmd is u_long
e
s 00007/00001/01621
d D 8.2 94/01/12 10:02:40 bostic 19 18
c lint
e
s 00002/00002/01620
d D 8.1 93/06/10 21:23:42 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/01618
d D 7.15 92/12/27 09:10:48 hibler 17 16
c SHPUX moved to MD flags
e
s 00020/00020/01601
d D 7.14 92/10/11 08:55:07 bostic 16 15
c make kernel includes standard
e
s 00001/00001/01620
d D 7.13 92/07/12 17:47:37 pendry 15 13
c MIN -> max
e
s 00002/00001/01620
d R 7.13 92/07/12 17:45:24 pendry 14 13
c MIN -> min
e
s 00172/00180/01449
d D 7.12 92/06/05 15:23:18 hibler 13 12
c merge latest Utah hp300 code including 68040 support
e
s 00005/00024/01624
d D 7.11 92/02/15 21:20:52 mckusick 12 11
c convert to use new select interface, selrecord/selwakeup
e
s 00003/00003/01645
d D 7.10 92/02/15 21:20:19 karels 11 10
c use proper parameters to close routine
e
s 00002/00005/01646
d D 7.9 91/06/28 14:18:27 karels 10 8
c we don't have page mode
e
s 00003/00061/01590
d D 7.8.1.1 91/06/28 14:16:46 karels 9 8
c branch for network release (removed AT&T-derived clist code)
e
s 00001/00001/01650
d D 7.8 91/05/30 15:27:32 mckusick 8 7
c make file flags consistent
e
s 00020/00017/01631
d D 7.7 91/05/04 19:49:11 karels 7 6
c update to current include, device calling conventions
e
s 00017/00017/01631
d D 7.6 90/12/16 16:35:58 bostic 6 5
c kernel reorg
e
s 00008/00160/01640
d D 7.5 90/12/05 18:26:29 mckusick 5 4
c update from Mike Hibler for new VM and other machine support
e
s 00015/00017/01785
d D 7.4 90/06/22 09:26:27 hibler 4 3
c get rid of u_error uses
e
s 00041/00031/01761
d D 7.3 90/06/20 11:06:38 mckusick 3 2
c update for new structure
e
s 00007/00001/01785
d D 7.2 90/05/25 15:44:33 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 01786/00000/00000
d D 7.1 90/05/08 22:06:57 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
f b 
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 18
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 13
 * from: Utah $Hdr: hil.c 1.33 89/12/22$
E 13
I 13
 * from: Utah $Hdr: hil.c 1.38 92/01/21$
E 13
 *
 *	%W% (Berkeley) %G%
 */

D 6
#include "param.h"
#include "conf.h"
#include "user.h"
#include "proc.h"
#include "ioctl.h"
#include "file.h"
#include "tty.h"
#include "systm.h"
#include "uio.h"
#include "kernel.h"
E 6
I 6
D 16
#include "sys/param.h"
#include "sys/conf.h"
D 7
#include "sys/user.h"
E 7
#include "sys/proc.h"
I 7
#include "sys/user.h"
E 7
#include "sys/ioctl.h"
#include "sys/file.h"
#include "sys/tty.h"
#include "sys/systm.h"
#include "sys/uio.h"
#include "sys/kernel.h"
E 16
I 16
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/tty.h>
#include <sys/systm.h>
#include <sys/uio.h>
#include <sys/kernel.h>
E 16
E 6
D 5
#include "mapmem.h"
E 5

D 16
#include "hilreg.h"
#include "hilioctl.h"
#include "hilvar.h"
#include "kbdmap.h"
E 16
I 16
#include <hp/dev/hilreg.h>
#include <hp/dev/hilioctl.h>
#include <hp/dev/hilvar.h>
#include <hp/dev/kbdmap.h>
E 16

D 6
#include "machine/cpu.h"
E 6
I 6
D 7
#include "../include/cpu.h"
E 7
I 7
D 16
#include "machine/cpu.h"
E 16
I 16
#include <machine/cpu.h>
E 16
E 7
E 6

I 5
D 6
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_kern.h"
#include "../vm/vm_page.h"
#include "../vm/vm_pager.h"
E 6
I 6
D 16
#include "vm/vm_param.h"
#include "vm/vm_map.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
#include "vm/vm_pager.h"
E 16
I 16
#include <vm/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
#include <vm/vm_pager.h>
E 16
E 6

E 5
D 13
struct	hilloop	hil0;
E 13
I 13
#ifdef hp300
#define NHIL	1	/* XXX */
#else
#include "hil.h"
#endif

struct  hilloop hilloop[NHIL];
E 13
struct	_hilbell default_bell = { BELLDUR, BELLFREQ };
I 13
#ifdef hp800
int	hilspl;
#endif
E 13

D 5
#ifdef MAPMEM
int	hilqfork(), hilqvfork(), hilqexit();
struct	mapmemops hilqops = { hilqfork, hilqvfork, hilqexit, hilqexit };
#endif

E 5
#ifdef DEBUG
int 	hildebug = 0;
#define HDB_FOLLOW	0x01
#define HDB_MMAP	0x02
#define HDB_MASK	0x04
#define HDB_CONFIG	0x08
#define HDB_KEYBOARD	0x10
#define HDB_IDMODULE	0x20
#define HDB_EVENTS	0x80
#endif

I 2
/* symbolic sleep message strings */
char hilin[] = "hilin";

E 2
D 13
hilinit()
E 13
I 13
hilsoftinit(unit, hilbase)
	int unit;
	struct hil_dev *hilbase;
E 13
{
D 13
  	register struct hilloop *hilp = &hil0;	/* XXX */
E 13
I 13
  	register struct hilloop *hilp = &hilloop[unit];
E 13
	register int i;

I 13
#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
		printf("hilsoftinit(%d, %x)\n", unit, hilbase);
#endif
E 13
	/*
	 * Initialize loop information
	 */
D 13
	hilp->hl_addr = HILADDR;
E 13
I 13
	hilp->hl_addr = hilbase;
E 13
	hilp->hl_cmdending = FALSE;
	hilp->hl_actdev = hilp->hl_cmddev = 0;
	hilp->hl_cmddone = FALSE;
	hilp->hl_cmdbp = hilp->hl_cmdbuf;
	hilp->hl_pollbp = hilp->hl_pollbuf;
	hilp->hl_kbddev = 0;
	hilp->hl_kbdlang = KBD_DEFAULT;
	hilp->hl_kbdflags = 0;
	/*
	 * Clear all queues and device associations with queues
	 */
	for (i = 0; i < NHILQ; i++) {
		hilp->hl_queue[i].hq_eventqueue = NULL;
		hilp->hl_queue[i].hq_procp = NULL;
		hilp->hl_queue[i].hq_devmask = 0;
	}
	for (i = 0; i < NHILD; i++)
		hilp->hl_device[i].hd_qmask = 0;
	hilp->hl_device[HILLOOPDEV].hd_flags = (HIL_ALIVE|HIL_PSEUDO);
I 13
}

hilinit(unit, hilbase)
	int unit;
	struct hil_dev *hilbase;
{
  	register struct hilloop *hilp = &hilloop[unit];
#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
		printf("hilinit(%d, %x)\n", unit, hilbase);
#endif
E 13
	/*
I 13
	 * Initialize software (if not already done).
	 */
	if ((hilp->hl_device[HILLOOPDEV].hd_flags & HIL_ALIVE) == 0)
		hilsoftinit(unit, hilbase);
	/*
	 * Initialize hardware.
E 13
	 * Reset the loop hardware, and collect keyboard/id info
	 */
	hilreset(hilp);
D 13
	hilinfo(hilp);
	kbdenable();
E 13
I 13
	hilinfo(unit);
	kbdenable(unit);
E 13
}

D 7
hilopen(dev, flags)
E 7
I 7
/* ARGSUSED */
hilopen(dev, flags, mode, p)
E 7
	dev_t dev;
I 7
	int flags, mode;
	struct proc *p;
E 7
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
E 3
D 13
  	register struct hilloop *hilp = &hil0;	/* XXX */
E 13
I 13
  	register struct hilloop *hilp = &hilloop[HILLOOP(dev)];
E 13
	register struct hilloopdev *dptr;
	u_char device = HILUNIT(dev);

#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
D 3
		printf("hilopen(%d): device %x\n", u.u_procp->p_pid, device);
E 3
I 3
D 13
		printf("hilopen(%d): device %x\n", p->p_pid, device);
E 13
I 13
		printf("hilopen(%d): loop %x device %x\n",
		       p->p_pid, HILLOOP(dev), device);
E 13
E 3
#endif
	
	if ((hilp->hl_device[HILLOOPDEV].hd_flags & HIL_ALIVE) == 0)
		return(ENXIO);

	dptr = &hilp->hl_device[device];
	if ((dptr->hd_flags & HIL_ALIVE) == 0)
		return(ENODEV);

	/*
	 * Pseudo-devices cannot be read, nothing more to do.
	 */
	if (dptr->hd_flags & HIL_PSEUDO)
		return(0);

	/*
	 * Open semantics:
	 * 1.	Open devices have only one of HIL_READIN/HIL_QUEUEIN.
	 * 2.	HPUX processes always get read syscall interface and
	 *	must have exclusive use of the device.
	 * 3.	BSD processes default to shared queue interface.
	 *	Multiple processes can open the device.
	 */
D 3
	if (u.u_procp->p_flag & SHPUX) {
E 3
I 3
D 17
	if (p->p_flag & SHPUX) {
E 17
I 17
	if (p->p_md.md_flags & MDP_HPUX) {
E 17
E 3
		if (dptr->hd_flags & (HIL_READIN|HIL_QUEUEIN))
			return(EBUSY);
		dptr->hd_flags |= HIL_READIN;
	} else {
		if (dptr->hd_flags & HIL_READIN)
			return(EBUSY);
		dptr->hd_flags |= HIL_QUEUEIN;
	}
D 8
	if (flags & FNDELAY)
E 8
I 8
	if (flags & FNONBLOCK)
E 8
		dptr->hd_flags |= HIL_NOBLOCK;
	/*
	 * It is safe to flush the read buffer as we are guarenteed
	 * that no one else is using it.
	 */
	ndflush(&dptr->hd_queue, dptr->hd_queue.c_cc);

	send_hil_cmd(hilp->hl_addr, HIL_INTON, NULL, 0, NULL);
	/*
	 * Opened the keyboard, put in raw mode.
	 */
	(void) splhil();
	if (device == hilp->hl_kbddev) {
		u_char mask = 0;
		send_hil_cmd(hilp->hl_addr, HIL_WRITEKBDSADR, &mask, 1, NULL);
		hilp->hl_kbdflags |= KBD_RAW;
#ifdef DEBUG
		if (hildebug & HDB_KEYBOARD)
			printf("hilopen: keyboard %d raw\n", hilp->hl_kbddev);
#endif
	}
	(void) spl0();
	return (0);
}

/* ARGSUSED */
D 11
hilclose(dev, flags)
E 11
I 11
hilclose(dev, flags, mode, p)
E 11
	dev_t dev;
I 19
	int flags, mode;
E 19
I 11
	struct proc *p;
E 11
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
I 7
D 11
	struct proc *p = curproc;		/* XXX */
E 11
E 7
E 3
D 13
  	register struct hilloop *hilp = &hil0;	/* XXX */
E 13
I 13
  	register struct hilloop *hilp = &hilloop[HILLOOP(dev)];
E 13
	register struct hilloopdev *dptr;
	register int i;
	u_char device = HILUNIT(dev);
	char mask, lpctrl;

#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
D 3
		printf("hilclose(%d): device %x\n", u.u_procp->p_pid, device);
E 3
I 3
		printf("hilclose(%d): device %x\n", p->p_pid, device);
E 3
#endif

	dptr = &hilp->hl_device[device];
	if (device && (dptr->hd_flags & HIL_PSEUDO))
		return (0);

D 3
	if ((u.u_procp->p_flag & SHPUX) == 0) {
E 3
I 3
D 11
	if ((p->p_flag & SHPUX) == 0) {
E 11
I 11
D 17
	if (p && (p->p_flag & SHPUX) == 0) {
E 17
I 17
	if (p && (p->p_md.md_flags & MDP_HPUX) == 0) {
E 17
E 11
E 3
		/*
		 * If this is the loop device,
		 * free up all queues belonging to this process.
		 */
		if (device == 0) {
			for (i = 0; i < NHILQ; i++)
D 3
				if (hilp->hl_queue[i].hq_procp == u.u_procp)
E 3
I 3
				if (hilp->hl_queue[i].hq_procp == p)
E 3
D 13
					(void) hilqfree(i);
E 13
I 13
					(void) hilqfree(hilp, i);
E 13
		} else {
			mask = ~hildevmask(device);
			(void) splhil();
			for (i = 0; i < NHILQ; i++)
D 3
				if (hilp->hl_queue[i].hq_procp == u.u_procp) {
E 3
I 3
				if (hilp->hl_queue[i].hq_procp == p) {
E 3
					dptr->hd_qmask &= ~hilqmask(i);
					hilp->hl_queue[i].hq_devmask &= mask;
				}
			(void) spl0();
		}
	}
	/*
	 * Always flush the read buffer
	 */
	dptr->hd_flags &= ~(HIL_QUEUEIN|HIL_READIN|HIL_NOBLOCK);
	ndflush(&dptr->hd_queue, dptr->hd_queue.c_cc);
	/*
	 * Set keyboard back to cooked mode when closed.
	 */
	(void) splhil();
	if (device && device == hilp->hl_kbddev) {
		mask = 1 << (hilp->hl_kbddev - 1);
		send_hil_cmd(hilp->hl_addr, HIL_WRITEKBDSADR, &mask, 1, NULL);
		hilp->hl_kbdflags &= ~(KBD_RAW|KBD_AR1|KBD_AR2);
		/*
		 * XXX: We have had trouble with keyboards remaining raw
		 * after close due to the LPC_KBDCOOK bit getting cleared
		 * somewhere along the line.  Hence we check and reset
		 * LPCTRL if necessary.
		 */
		send_hil_cmd(hilp->hl_addr, HIL_READLPCTRL, NULL, 0, &lpctrl);
		if ((lpctrl & LPC_KBDCOOK) == 0) {
			printf("hilclose: bad LPCTRL %x, reset to %x\n",
			       lpctrl, lpctrl|LPC_KBDCOOK);
			lpctrl |= LPC_KBDCOOK;
			send_hil_cmd(hilp->hl_addr, HIL_WRITELPCTRL,
					&lpctrl, 1, NULL);
		}
#ifdef DEBUG
		if (hildebug & HDB_KEYBOARD)
			printf("hilclose: keyboard %d cooked\n",
			       hilp->hl_kbddev);
#endif
D 13
		kbdenable();
E 13
I 13
		kbdenable(HILLOOP(dev));
E 13
	}
	(void) spl0();
	return (0);
}

/*
 * Read interface to HIL device.
 */
hilread(dev, uio)
	dev_t dev;
	register struct uio *uio;
{
D 13
	struct hilloop *hilp = &hil0;		/* XXX */
E 13
I 13
	struct hilloop *hilp = &hilloop[HILLOOP(dev)];
E 13
	register struct hilloopdev *dptr;
	register int cc;
	u_char device = HILUNIT(dev);
	char buf[HILBUFSIZE];
	int error;

#if 0
	/*
	 * XXX: Don't do this since HP-UX doesn't.
	 *
	 * Check device number.
	 * This check is necessary since loop can reconfigure.
	 */
	if (device > hilp->hl_maxdev)
		return(ENODEV);
#endif

	dptr = &hilp->hl_device[device];
	if ((dptr->hd_flags & HIL_READIN) == 0)
		return(ENODEV);

	(void) splhil();
	while (dptr->hd_queue.c_cc == 0) {
		if (dptr->hd_flags & HIL_NOBLOCK) {
			spl0();
			return(EWOULDBLOCK);
		}
		dptr->hd_flags |= HIL_ASLEEP;
D 2
		sleep((caddr_t)dptr, TTIPRI);
E 2
I 2
		if (error = tsleep((caddr_t)dptr, TTIPRI | PCATCH, hilin, 0)) {
			(void) spl0();
			return (error);
		}
E 2
	}
	(void) spl0();

	error = 0;
	while (uio->uio_resid > 0 && error == 0) {
		cc = hilq_to_b(&dptr->hd_queue, buf,
D 15
			       MIN(uio->uio_resid, HILBUFSIZE));
E 15
I 15
			       min(uio->uio_resid, HILBUFSIZE));
E 15
		if (cc <= 0)
			break;
		error = uiomove(buf, cc, uio);
	}
	return(error);
}

D 7
hilioctl(dev, cmd, data, flag)
E 7
I 7
hilioctl(dev, cmd, data, flag, p)
E 7
	dev_t dev;
I 19
D 20
	int cmd, flag;
E 20
I 20
	u_long cmd;
E 20
E 19
	caddr_t data;
I 20
	int flag;
E 20
I 7
	struct proc *p;
E 7
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
E 3
D 13
	register struct hilloop *hilp = &hil0;	/* XXX */
E 13
I 13
	register struct hilloop *hilp = &hilloop[HILLOOP(dev)];
E 13
	char device = HILUNIT(dev);
	struct hilloopdev *dptr;
	register int i;
	u_char hold;
	int error;

#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
		printf("hilioctl(%d): dev %x cmd %x\n",
D 3
		       u.u_procp->p_pid, device, cmd);
E 3
I 3
		       p->p_pid, device, cmd);
E 3
#endif

	dptr = &hilp->hl_device[device];
	if ((dptr->hd_flags & HIL_ALIVE) == 0)
		return (ENODEV);

	/*
	 * Don't allow hardware ioctls on virtual devices.
	 * Note that though these are the BSD names, they have the same
	 * values as the HP-UX equivalents so we catch them as well.
	 */
	if (dptr->hd_flags & HIL_PSEUDO) {
		switch (cmd) {
		case HILIOCSC:
		case HILIOCID:
I 13
		case OHILIOCID:
E 13
		case HILIOCRN:
		case HILIOCRS:
		case HILIOCED:
			return(ENODEV);

		/*
		 * XXX: should also return ENODEV but HP-UX compat
		 * breaks if we do.  They work ok right now because
		 * we only recognize one keyboard on the loop.  This
		 * will have to change if we remove that restriction.
		 */
		case HILIOCAROFF:
		case HILIOCAR1:
		case HILIOCAR2:
			break;

		default:
			break;
		}
	}

#ifdef HPUXCOMPAT
D 3
	if (u.u_procp->p_flag & SHPUX)
E 3
I 3
D 17
	if (p->p_flag & SHPUX)
E 17
I 17
	if (p->p_md.md_flags & MDP_HPUX)
E 17
E 3
		return(hpuxhilioctl(dev, cmd, data, flag));
#endif

	hilp->hl_cmdbp = hilp->hl_cmdbuf;
	bzero((caddr_t)hilp->hl_cmdbuf, HILBUFSIZE);
	hilp->hl_cmddev = device;
	error = 0;
	switch (cmd) {

	case HILIOCSBP:
		/* Send four data bytes to the tone gererator. */
		send_hil_cmd(hilp->hl_addr, HIL_STARTCMD, data, 4, NULL);
		/* Send the trigger beeper command to the 8042. */
		send_hil_cmd(hilp->hl_addr, (cmd & 0xFF), NULL, 0, NULL);
		break;

I 17
	case OHILIOCRRT:
E 17
	case HILIOCRRT:
		/* Transfer the real time to the 8042 data buffer */
		send_hil_cmd(hilp->hl_addr, (cmd & 0xFF), NULL, 0, NULL);
		/* Read each byte of the real time */
		for (i = 0; i < 5; i++) {
			send_hil_cmd(hilp->hl_addr, HIL_READTIME + i, NULL,
					0, &hold);
			data[4-i] = hold;
		}
		break;
		
	case HILIOCRT:
		for (i = 0; i < 4; i++) {
			send_hil_cmd(hilp->hl_addr, (cmd & 0xFF) + i,
					NULL, 0, &hold);
			data[i] = hold;
		}
		break;

	case HILIOCID:
I 13
	case OHILIOCID:
E 13
	case HILIOCSC:
	case HILIOCRN:
	case HILIOCRS:
	case HILIOCED:
	  	send_hildev_cmd(hilp, device, (cmd & 0xFF));
		bcopy(hilp->hl_cmdbuf, data, hilp->hl_cmdbp-hilp->hl_cmdbuf);
	  	break;

        case HILIOCAROFF:
        case HILIOCAR1:
        case HILIOCAR2:
		if (hilp->hl_kbddev) {
			hilp->hl_cmddev = hilp->hl_kbddev;
			send_hildev_cmd(hilp, hilp->hl_kbddev, (cmd & 0xFF));
			hilp->hl_kbdflags &= ~(KBD_AR1|KBD_AR2);
			if (cmd == HILIOCAR1)
				hilp->hl_kbdflags |= KBD_AR1;
			else if (cmd == HILIOCAR2)
				hilp->hl_kbdflags |= KBD_AR2;
		}
		break;

	case HILIOCBEEP:
		hilbeep(hilp, (struct _hilbell *)data);
		break;

	case FIONBIO:
		dptr = &hilp->hl_device[device];
		if (*(int *)data)
			dptr->hd_flags |= HIL_NOBLOCK;
		else
			dptr->hd_flags &= ~HIL_NOBLOCK;
		break;

	/*
	 * FIOASYNC must be present for FIONBIO above to work!
	 * (See fcntl in kern_descrip.c).
	 */
	case FIOASYNC:
		break;

        case HILIOCALLOCQ:
D 13
		error = hilqalloc((struct hilqinfo *)data);
E 13
I 13
		error = hilqalloc(hilp, (struct hilqinfo *)data);
E 13
		break;

        case HILIOCFREEQ:
D 13
		error = hilqfree(((struct hilqinfo *)data)->qid);
E 13
I 13
		error = hilqfree(hilp, ((struct hilqinfo *)data)->qid);
E 13
		break;

        case HILIOCMAPQ:
D 13
		error = hilqmap(*(int *)data, device);
E 13
I 13
		error = hilqmap(hilp, *(int *)data, device);
E 13
		break;

        case HILIOCUNMAPQ:
D 13
		error = hilqunmap(*(int *)data, device);
E 13
I 13
		error = hilqunmap(hilp, *(int *)data, device);
E 13
		break;

	case HILIOCHPUX:
		dptr = &hilp->hl_device[device];
		dptr->hd_flags |= HIL_READIN;
		dptr->hd_flags &= ~HIL_QUEUEIN;
		break;

        case HILIOCRESET:
	        hilreset(hilp);
		break;
		
#ifdef DEBUG
        case HILIOCTEST:
		hildebug = *(int *) data;
		break;
#endif

        default:
		error = EINVAL;
		break;

	}
	hilp->hl_cmddev = 0;
	return(error);
}

#ifdef HPUXCOMPAT
/* ARGSUSED */
hpuxhilioctl(dev, cmd, data, flag)
	dev_t dev;
I 19
D 20
	int cmd, flag;
E 20
I 20
	u_long cmd;
E 20
E 19
	caddr_t data;
I 20
	int flag;
E 20
{
D 13
	register struct hilloop *hilp = &hil0;	/* XXX */
E 13
I 13
	register struct hilloop *hilp = &hilloop[HILLOOP(dev)];
E 13
	char device = HILUNIT(dev);
	struct hilloopdev *dptr;
	register int i;
	u_char hold;

	hilp->hl_cmdbp = hilp->hl_cmdbuf;
	bzero((caddr_t)hilp->hl_cmdbuf, HILBUFSIZE);
	hilp->hl_cmddev = device;
	switch (cmd) {

	case HILSC:
	case HILID:
	case HILRN:
	case HILRS:
	case HILED:
	case HILP1:
	case HILP2:
	case HILP3:
	case HILP4:
	case HILP5:
	case HILP6:
	case HILP7:
	case HILP:
	case HILA1:
	case HILA2:
	case HILA3:
	case HILA4:
	case HILA5:
	case HILA6:
	case HILA7:
	case HILA:
		send_hildev_cmd(hilp, device, (cmd & 0xFF));
		bcopy(hilp->hl_cmdbuf, data, hilp->hl_cmdbp-hilp->hl_cmdbuf);
	  	break;

        case HILDKR:
        case HILER1:
        case HILER2:
		if (hilp->hl_kbddev) {
			hilp->hl_cmddev = hilp->hl_kbddev;
			send_hildev_cmd(hilp, hilp->hl_kbddev, (cmd & 0xFF));
			hilp->hl_kbdflags &= ~(KBD_AR1|KBD_AR2);
			if (cmd == HILIOCAR1)
				hilp->hl_kbdflags |= KBD_AR1;
			else if (cmd == HILIOCAR2)
				hilp->hl_kbdflags |= KBD_AR2;
		}
		break;

	case EFTSBP:
		/* Send four data bytes to the tone gererator. */
		send_hil_cmd(hilp->hl_addr, HIL_STARTCMD, data, 4, NULL);
		/* Send the trigger beeper command to the 8042. */
		send_hil_cmd(hilp->hl_addr, (cmd & 0xFF), NULL, 0, NULL);
		break;

	case EFTRRT:
		/* Transfer the real time to the 8042 data buffer */
		send_hil_cmd(hilp->hl_addr, (cmd & 0xFF), NULL, 0, NULL);
		/* Read each byte of the real time */
		for (i = 0; i < 5; i++) {
			send_hil_cmd(hilp->hl_addr, HIL_READTIME + i, NULL,
					0, &hold);
			data[4-i] = hold;
		}
		break;
		
	case EFTRT:
		for (i = 0; i < 4; i++) {
			send_hil_cmd(hilp->hl_addr, (cmd & 0xFF) + i,
					NULL, 0, &hold);
			data[i] = hold;
		}
		break;

        case EFTRLC:
        case EFTRCC:
		send_hil_cmd(hilp->hl_addr, (cmd & 0xFF), NULL, 0, &hold);
		*data = hold;
		break;
		
        case EFTSRPG:
        case EFTSRD:
        case EFTSRR:
		send_hil_cmd(hilp->hl_addr, (cmd & 0xFF), data, 1, NULL);
		break;
		
	case EFTSBI:
I 13
#ifdef hp800
		/* XXX big magic */
		hold = 7 - (*(u_char *)data >> 5);
		*(int *)data = 0x84069008 | (hold << 8);
		send_hil_cmd(hilp->hl_addr, HIL_STARTCMD, data, 4, NULL);
		send_hil_cmd(hilp->hl_addr, 0xC4, NULL, 0, NULL);
		break;
#else
E 13
		hilbeep(hilp, (struct _hilbell *)data);
I 13
#endif
E 13
		break;

	case FIONBIO:
		dptr = &hilp->hl_device[device];
		if (*(int *)data)
			dptr->hd_flags |= HIL_NOBLOCK;
		else
			dptr->hd_flags &= ~HIL_NOBLOCK;
		break;

	case FIOASYNC:
		break;

        default:
		hilp->hl_cmddev = 0;
		return(EINVAL);
	}
	hilp->hl_cmddev = 0;
	return(0);
}
#endif

D 13
/*
D 7
 * XXX: the mmap inteface for HIL devices should be rethought.
E 7
I 7
 * XXX: the mmap interface for HIL devices should be rethought.
E 7
 * We used it only briefly in conjuntion with shared queues
 * (instead of HILIOCMAPQ ioctl).  Perhaps mmap()ing a device
 * should give a single queue per process.
 */
E 13
/* ARGSUSED */
hilmap(dev, off, prot)
	dev_t dev;
D 19
	register int off;
E 19
I 19
	int off, prot;
E 19
{
I 3
D 4
	struct proc *p = u.u_procp;		/* XXX */
E 4
E 3
D 13
#ifdef MMAP
I 4
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
I 7
	struct proc *p = curproc;		/* XXX */
E 7
E 4
	register struct hilloop *hilp = &hil0;	/* XXX */
	register struct hiliqueue *qp;
	register int qnum;

	/*
	 * Only allow mmap() on loop device
	 */
	if (HILUNIT(dev) != 0 || off >= NHILQ*sizeof(HILQ))
		return(-1);
	/*
	 * Determine which queue we want based on the offset.
	 * Queue must belong to calling process.
	 */
	qp = &hilp->hl_queue[off / sizeof(HILQ)];
D 3
	if (qp->hq_procp != u.u_procp)
E 3
I 3
	if (qp->hq_procp != p)
E 3
		return(-1);

	off %= sizeof(HILQ);
	return(kvtop((u_int)qp->hq_eventqueue + off) >> PGSHIFT);
#endif
E 13
}

/*ARGSUSED*/
D 7
hilselect(dev, rw)
E 7
I 7
hilselect(dev, rw, p)
E 7
	dev_t dev;
I 19
	int rw;
E 19
I 7
	struct proc *p;
E 7
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
E 3
D 13
	register struct hilloop *hilp = &hil0;	/* XXX */
E 13
I 13
	register struct hilloop *hilp = &hilloop[HILLOOP(dev)];
E 13
	register struct hilloopdev *dptr;
	register struct hiliqueue *qp;
	register int mask;
	int s, device;
	
	if (rw == FWRITE)
		return (1);
	device = HILUNIT(dev);

	/*
	 * Read interface.
	 * Return 1 if there is something in the queue, 0 ow.
	 */
	dptr = &hilp->hl_device[device];
	if (dptr->hd_flags & HIL_READIN) {
		s = splhil();
		if (dptr->hd_queue.c_cc) {
			splx(s);
			return (1);
		}
D 12
		if (dptr->hd_selr &&
		    dptr->hd_selr->p_wchan == (caddr_t)&selwait)
			dptr->hd_flags |= HIL_SELCOLL;
		else
D 3
			dptr->hd_selr = u.u_procp;
E 3
I 3
			dptr->hd_selr = p;
E 12
I 12
		selrecord(p, &dptr->hd_selr);
E 12
E 3
		splx(s);
		return (0);
	}

	/*
	 * Make sure device is alive and real (or the loop device).
	 * Note that we do not do this for the read interface.
	 * This is primarily to be consistant with HP-UX.
	 */
	if (device && (dptr->hd_flags & (HIL_ALIVE|HIL_PSEUDO)) != HIL_ALIVE)
		return (1);

	/*
	 * Select on loop device is special.
	 * Check to see if there are any data for any loop device
	 * provided it is associated with a queue belonging to this user.
	 */
	if (device == 0)
		mask = -1;
	else
		mask = hildevmask(device);
	/*
	 * Must check everybody with interrupts blocked to prevent races.
	 */
	s = splhil();
	for (qp = hilp->hl_queue; qp < &hilp->hl_queue[NHILQ]; qp++)
D 3
		if (qp->hq_procp == u.u_procp && (mask & qp->hq_devmask) &&
E 3
I 3
		if (qp->hq_procp == p && (mask & qp->hq_devmask) &&
E 3
		    qp->hq_eventqueue->hil_evqueue.head !=
		    qp->hq_eventqueue->hil_evqueue.tail) {
			splx(s);
			return (1);
		}

D 12
	if (dptr->hd_selr && dptr->hd_selr->p_wchan == (caddr_t)&selwait)
		dptr->hd_flags |= HIL_SELCOLL;
	else
D 3
		dptr->hd_selr = u.u_procp;
E 3
I 3
		dptr->hd_selr = p;
E 12
I 12
	selrecord(p, &dptr->hd_selr);
E 12
E 3
	splx(s);
	return (0);
}

D 13
hilint()
E 13
I 13
/*ARGSUSED*/
hilint(unit)
I 19
	int unit;
E 19
E 13
{
D 13
	struct hilloop *hilp = &hil0;		/* XXX */
E 13
I 13
#ifdef hp300
	struct hilloop *hilp = &hilloop[0]; /* XXX how do we know on 300? */
#else
	struct hilloop *hilp = &hilloop[unit];
#endif
E 13
	register struct hil_dev *hildevice = hilp->hl_addr;
	u_char c, stat;

D 13
	stat = hildevice->hil_stat;
	c = hildevice->hil_data;		/* clears interrupt */
	hil_process_int(stat, c);
E 13
I 13
	stat = READHILSTAT(hildevice);
	c = READHILDATA(hildevice);		/* clears interrupt */
	hil_process_int(hilp, stat, c);
E 13
}

#include "ite.h"

D 13
hil_process_int(stat, c)
E 13
I 13
hil_process_int(hilp, stat, c)
	register struct hilloop *hilp;
E 13
	register u_char stat, c;
{
D 13
  	register struct hilloop *hilp;

E 13
#ifdef DEBUG
	if (hildebug & HDB_EVENTS)
		printf("hilint: %x %x\n", stat, c);
#endif

	/* the shift enables the compiler to generate a jump table */
	switch ((stat>>HIL_SSHIFT) & HIL_SMASK) {

#if NITE > 0
	case HIL_KEY:
	case HIL_SHIFT:
	case HIL_CTRL:
	case HIL_CTRLSHIFT:
		itefilter(stat, c);
		return;
#endif
		
	case HIL_STATUS:			/* The status info. */
D 13
		hilp = &hil0;			/* XXX */
E 13
		if (c & HIL_ERROR) {
		  	hilp->hl_cmddone = TRUE;
			if (c == HIL_RECONFIG)
				hilconfig(hilp);
			break;
		}
		if (c & HIL_COMMAND) {
		  	if (c & HIL_POLLDATA)	/* End of data */
				hilevent(hilp);
			else			/* End of command */
			  	hilp->hl_cmdending = TRUE;
			hilp->hl_actdev = 0;
		} else {
		  	if (c & HIL_POLLDATA) {	/* Start of polled data */
			  	if (hilp->hl_actdev != 0)
					hilevent(hilp);
				hilp->hl_actdev = (c & HIL_DEVMASK);
				hilp->hl_pollbp = hilp->hl_pollbuf;
			} else {		/* Start of command */
				if (hilp->hl_cmddev == (c & HIL_DEVMASK)) {
					hilp->hl_cmdbp = hilp->hl_cmdbuf;
					hilp->hl_actdev = 0;
				}
			}
		}
	        return;

	case HIL_DATA:
D 13
		hilp = &hil0;			/* XXX */
E 13
		if (hilp->hl_actdev != 0)	/* Collecting poll data */
			*hilp->hl_pollbp++ = c;
		else if (hilp->hl_cmddev != 0)  /* Collecting cmd data */
			if (hilp->hl_cmdending) {
				hilp->hl_cmddone = TRUE;
				hilp->hl_cmdending = FALSE;
			} else  
				*hilp->hl_cmdbp++ = c;
		return;
		
	case 0:		/* force full jump table */
	default:
		return;
	}
}

#if defined(DEBUG) && !defined(PANICBUTTON)
#define PANICBUTTON
#endif

/*
 * Optimized macro to compute:
 *	eq->head == (eq->tail + 1) % eq->size
 * i.e. has tail caught up with head.  We do this because 32 bit long
 * remaidering is expensive (a function call with our compiler).
 */
#define HQFULL(eq)	(((eq)->head?(eq)->head:(eq)->size) == (eq)->tail+1)
#define HQVALID(eq) \
	((eq)->size == HEVQSIZE && (eq)->tail >= 0 && (eq)->tail < HEVQSIZE)

hilevent(hilp)
	struct hilloop *hilp;
{
	register struct hilloopdev *dptr = &hilp->hl_device[hilp->hl_actdev];
	register int len, mask, qnum;
	register u_char *cp, *pp;
	register HILQ *hq;
	struct timeval ourtime;
	hil_packet *proto;
	int s, len0;
	long tenths;

#ifdef PANICBUTTON
	static int first;
	extern int panicbutton;

	cp = hilp->hl_pollbuf;
	if (panicbutton && (*cp & HIL_KBDDATA)) {
		if (*++cp == 0x4E)
			first = 1;
		else if (first && *cp == 0x46 && !panicstr)
			panic("are we having fun yet?");
		else
			first = 0;
	}
#endif
#ifdef DEBUG
	if (hildebug & HDB_EVENTS) {
		printf("hilevent: dev %d pollbuf: ", hilp->hl_actdev);
		printhilpollbuf(hilp);
		printf("\n");
	}
#endif

	/*
	 * Note that HIL_READIN effectively "shuts off" any queues
	 * that may have been in use at the time of an HILIOCHPUX call.
	 */
	if (dptr->hd_flags & HIL_READIN) {
		hpuxhilevent(hilp, dptr);
		return;
	}

	/*
	 * If this device isn't on any queue or there are no data
	 * in the packet (can this happen?) do nothing.
	 */
	if (dptr->hd_qmask == 0 ||
	    (len0 = hilp->hl_pollbp - hilp->hl_pollbuf) <= 0)
		return;

	/*
	 * Everybody gets the same time stamp
	 */
	s = splclock();
	ourtime = time;
	splx(s);
	tenths = (ourtime.tv_sec * 100) + (ourtime.tv_usec / 10000);

	proto = NULL;
	mask = dptr->hd_qmask;
	for (qnum = 0; mask; qnum++) {
		if ((mask & hilqmask(qnum)) == 0)
			continue;
		mask &= ~hilqmask(qnum);
		hq = hilp->hl_queue[qnum].hq_eventqueue;
		
		/*
		 * Ensure that queue fields that we rely on are valid
		 * and that there is space in the queue.  If either
		 * test fails, we just skip this queue.
		 */
		if (!HQVALID(&hq->hil_evqueue) || HQFULL(&hq->hil_evqueue))
			continue;

		/*
		 * Copy data to queue.
		 * If this is the first queue we construct the packet
		 * with length, timestamp and poll buffer data.
		 * For second and sucessive packets we just duplicate
		 * the first packet.
		 */
		pp = (u_char *) &hq->hil_event[hq->hil_evqueue.tail];
		if (proto == NULL) {
			proto = (hil_packet *)pp;
			cp = hilp->hl_pollbuf;
			len = len0;
			*pp++ = len + 6;
			*pp++ = hilp->hl_actdev;
			*(long *)pp = tenths;
			pp += sizeof(long);
			do *pp++ = *cp++; while (--len);
		} else
			*(hil_packet *)pp = *proto;

		if (++hq->hil_evqueue.tail == hq->hil_evqueue.size)
			hq->hil_evqueue.tail = 0;
	}

	/*
	 * Wake up anyone selecting on this device or the loop itself
	 */
D 12
	if (dptr->hd_selr) {
		selwakeup(dptr->hd_selr, dptr->hd_flags & HIL_SELCOLL);
		dptr->hd_selr = NULL;
		dptr->hd_flags &= ~HIL_SELCOLL;
	}
E 12
I 12
	selwakeup(&dptr->hd_selr);
E 12
	dptr = &hilp->hl_device[HILLOOPDEV];
D 12
	if (dptr->hd_selr) {
		selwakeup(dptr->hd_selr, dptr->hd_flags & HIL_SELCOLL);
		dptr->hd_selr = NULL;
		dptr->hd_flags &= ~HIL_SELCOLL;
	}
E 12
I 12
	selwakeup(&dptr->hd_selr);
E 12
}

#undef HQFULL

hpuxhilevent(hilp, dptr)
	register struct hilloop *hilp;
	register struct hilloopdev *dptr;
{
	register int len;
	struct timeval ourtime;
	long tstamp;
	int s;

	/*
	 * Everybody gets the same time stamp
	 */
	s = splclock();
	ourtime = time;
	splx(s);
	tstamp = (ourtime.tv_sec * 100) + (ourtime.tv_usec / 10000);

	/*
	 * Each packet that goes into the buffer must be preceded by the
	 * number of bytes in the packet, and the timestamp of the packet.
	 * This adds 5 bytes to the packet size. Make sure there is enough
	 * room in the buffer for it, and if not, toss the packet.
	 */
	len = hilp->hl_pollbp - hilp->hl_pollbuf;
	if (dptr->hd_queue.c_cc <= (HILMAXCLIST - (len+5))) {
		putc(len+5, &dptr->hd_queue);
		(void) b_to_q((char *)&tstamp, sizeof tstamp, &dptr->hd_queue);
		(void) b_to_q((char *)hilp->hl_pollbuf, len, &dptr->hd_queue);
	}

	/*
	 * Wake up any one blocked on a read or select
	 */
	if (dptr->hd_flags & HIL_ASLEEP) {
		dptr->hd_flags &= ~HIL_ASLEEP;
		wakeup((caddr_t)dptr);
	}
D 12
	if (dptr->hd_selr) {
		selwakeup(dptr->hd_selr, dptr->hd_flags & HIL_SELCOLL);
		dptr->hd_selr = NULL;
		dptr->hd_flags &= ~HIL_SELCOLL;
	}
E 12
I 12
	selwakeup(&dptr->hd_selr);
E 12
}

/*
 * Shared queue manipulation routines
 */

D 13
hilqalloc(qip)
E 13
I 13
hilqalloc(hilp, qip)
	register struct hilloop *hilp;
E 13
	struct hilqinfo *qip;
{
I 3
D 4
	struct proc *p = u.u_procp;		/* XXX */
E 4
E 3
D 5
#ifdef MAPMEM
E 5
I 4
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
I 7
	struct proc *p = curproc;		/* XXX */
E 7
E 4
D 5
	register struct hilloop *hilp = &hil0;	/* XXX */
	register HILQ *hq;
	register int qnum;
	struct mapmem *mp;
D 4
	int hilqmapin();
E 4
I 4
	int error, hilqmapin();
E 5
E 4

#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
D 5
		printf("hilqalloc(%d): addr %x\n",
D 3
		       u.u_procp->p_pid, qip->addr);
E 3
I 3
		       p->p_pid, qip->addr);
E 5
I 5
		printf("hilqalloc(%d): addr %x\n", p->p_pid, qip->addr);
E 5
E 3
#endif
D 5
	/*
	 * Find a free queue
	 */
	for (qnum = 0; qnum < NHILQ; qnum++)
		if (hilp->hl_queue[qnum].hq_procp == NULL)
			break;
	if (qnum == NHILQ)
		return(EMFILE);

	/*
	 * Allocate and clear memory for the queue
	 */
	if (hilp->hl_queue[qnum].hq_eventqueue)
		panic("hilqalloc");
	hq = (HILQ *) cialloc(sizeof(HILQ));
	if (hq == NULL)
		return(ENOMEM);
	bzero((caddr_t)hq, sizeof(HILQ));
	hilp->hl_queue[qnum].hq_eventqueue = hq;
	hq->hil_evqueue.size = HEVQSIZE;

	/*
	 * Map queue into user address space as instructed
	 */
D 3
	mp = mmalloc(qnum, &qip->addr, sizeof(HILQ), MM_RW|MM_CI, &hilqops);
	if (mp == MMNIL) {
E 3
I 3
D 4
	if (u.u_error = mmalloc(p, qnum, &qip->addr, sizeof(HILQ), MM_RW|MM_CI, &hilqops, &mp)) {
E 4
I 4
	error = mmalloc(p, qnum, &qip->addr, sizeof(HILQ), MM_RW|MM_CI,
			&hilqops, &mp);
	if (error) {
E 4
E 3
		cifree((caddr_t)hq, sizeof(HILQ));
		hilp->hl_queue[qnum].hq_eventqueue = NULL;
D 4
		return(u.u_error);
E 4
I 4
		return(error);
E 4
	}
	qip->qid = qnum;
D 3
	if (!mmmapin(mp, hilqmapin)) {
		mmfree(mp);
E 3
I 3
D 4
	if (!mmmapin(p, mp, hilqmapin)) {
		mmfree(p, mp);
E 4
I 4
	if (error = mmmapin(p, mp, hilqmapin)) {
		(void) mmfree(p, mp);
E 4
E 3
		cifree((caddr_t)hq, sizeof(HILQ));
		hilp->hl_queue[qnum].hq_eventqueue = NULL;
D 4
		return(u.u_error);
E 4
I 4
		return(error);
E 4
	}
D 3
	hilp->hl_queue[qnum].hq_procp = u.u_procp;
E 3
I 3
	hilp->hl_queue[qnum].hq_procp = p;
E 3
	hilp->hl_queue[qnum].hq_devmask = 0;
	return(0);
#else
E 5
	return(EINVAL);
D 5
#endif
E 5
}

D 13
hilqfree(qnum)
E 13
I 13
hilqfree(hilp, qnum)
I 19
	register struct hilloop *hilp;
E 19
E 13
	register int qnum;
{
I 3
D 4
	struct proc *p = u.u_procp;		/* XXX */
E 4
E 3
D 5
#ifdef MAPMEM
E 5
I 4
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
I 7
	struct proc *p = curproc;		/* XXX */
E 7
E 4
D 5
	register struct hilloop *hilp = &hil0;	/* XXX */
	register struct mapmem *mp;
E 5

#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
D 5
		printf("hilqfree(%d): qnum %d\n",
D 3
		       u.u_procp->p_pid, qnum);
E 3
I 3
		       p->p_pid, qnum);
E 5
I 5
		printf("hilqfree(%d): qnum %d\n", p->p_pid, qnum);
E 5
E 3
#endif
D 3
	if (qnum >= NHILQ || hilp->hl_queue[qnum].hq_procp != u.u_procp)
E 3
I 3
D 5
	if (qnum >= NHILQ || hilp->hl_queue[qnum].hq_procp != p)
E 3
		return(EINVAL);
	for (mp = u.u_mmap; mp; mp = mp->mm_next)
		if (qnum == mp->mm_id && mp->mm_ops == &hilqops) {
D 4
			hilqexit(mp);
E 4
I 4
			(void) hilqexit(mp);
E 4
			return(0);
		}
	panic("hilqfree");
	/* NOTREACHED */
#else
E 5
	return(EINVAL);
D 5
#endif
E 5
}

D 13
hilqmap(qnum, device)
E 13
I 13
hilqmap(hilp, qnum, device)
	register struct hilloop *hilp;
E 13
	register int qnum, device;
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
I 7
	struct proc *p = curproc;		/* XXX */
E 7
E 3
D 13
	register struct hilloop *hilp = &hil0;	/* XXX */
E 13
	register struct hilloopdev *dptr = &hilp->hl_device[device];
	int s;

#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
		printf("hilqmap(%d): qnum %d device %x\n",
D 3
		       u.u_procp->p_pid, qnum, device);
E 3
I 3
		       p->p_pid, qnum, device);
E 3
#endif
D 3
	if (qnum >= NHILQ || hilp->hl_queue[qnum].hq_procp != u.u_procp)
E 3
I 3
	if (qnum >= NHILQ || hilp->hl_queue[qnum].hq_procp != p)
E 3
		return(EINVAL);
	if ((dptr->hd_flags & HIL_QUEUEIN) == 0)
		return(EINVAL);
D 7
	if (dptr->hd_qmask && u.u_uid && u.u_uid != dptr->hd_uid)
E 7
I 7
	if (dptr->hd_qmask && p->p_ucred->cr_uid &&
	    p->p_ucred->cr_uid != dptr->hd_uid)
E 7
		return(EPERM);

	hilp->hl_queue[qnum].hq_devmask |= hildevmask(device);
	if (dptr->hd_qmask == 0)
D 7
		dptr->hd_uid = u.u_uid;
E 7
I 7
		dptr->hd_uid = p->p_ucred->cr_uid;
E 7
	s = splhil();
	dptr->hd_qmask |= hilqmask(qnum);
	splx(s);
#ifdef DEBUG
	if (hildebug & HDB_MASK)
		printf("hilqmap(%d): devmask %x qmask %x\n",
D 3
		       u.u_procp->p_pid, hilp->hl_queue[qnum].hq_devmask,
E 3
I 3
		       p->p_pid, hilp->hl_queue[qnum].hq_devmask,
E 3
		       dptr->hd_qmask);
#endif
	return(0);
}

D 13
hilqunmap(qnum, device)
E 13
I 13
hilqunmap(hilp, qnum, device)
	register struct hilloop *hilp;
E 13
	register int qnum, device;
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
I 7
	struct proc *p = curproc;		/* XXX */
E 7
E 3
D 13
	register struct hilloop *hilp = &hil0;	/* XXX */
E 13
	int s;

#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
		printf("hilqunmap(%d): qnum %d device %x\n",
D 3
		       u.u_procp->p_pid, qnum, device);
E 3
I 3
		       p->p_pid, qnum, device);
E 3
#endif

D 3
	if (qnum >= NHILQ || hilp->hl_queue[qnum].hq_procp != u.u_procp)
E 3
I 3
	if (qnum >= NHILQ || hilp->hl_queue[qnum].hq_procp != p)
E 3
		return(EINVAL);

	hilp->hl_queue[qnum].hq_devmask &= ~hildevmask(device);
	s = splhil();
	hilp->hl_device[device].hd_qmask &= ~hilqmask(qnum);
	splx(s);
#ifdef DEBUG
	if (hildebug & HDB_MASK)
		printf("hilqunmap(%d): devmask %x qmask %x\n",
D 3
		       u.u_procp->p_pid, hilp->hl_queue[qnum].hq_devmask,
E 3
I 3
		       p->p_pid, hilp->hl_queue[qnum].hq_devmask,
E 3
		       hilp->hl_device[device].hd_qmask);
#endif
	return(0);
}
D 5

#ifdef MAPMEM
hilqmapin(mp, off)
	struct mapmem *mp;
{
	struct hilloop *hilp = &hil0;		/* XXX */
	register HILQ *hq = hilp->hl_queue[mp->mm_id].hq_eventqueue;

	if (hq == NULL || off >= sizeof(HILQ))
		return(-1);
	return(kvtop((u_int)hq + off) >> PGSHIFT);
}

/*
 * Fork hook.
 * Unmap queue from child's address space
 */
hilqfork(mp, ischild)
	struct mapmem *mp;
{
I 3
	struct proc *p = u.u_procp;		/* XXX */
E 3
#ifdef DEBUG
	if (hildebug & HDB_MMAP)
D 3
		printf("hilqfork(%d): %s qnum %d\n", u.u_procp->p_pid,
E 3
I 3
		printf("hilqfork(%d): %s qnum %d\n", p->p_pid,
E 3
		       ischild ? "child" : "parent", mp->mm_id);
#endif
	if (ischild) {
D 3
		mmmapout(mp);
		mmfree(mp);
E 3
I 3
		mmmapout(p, mp);
D 4
		mmfree(p, mp);
E 4
I 4
		(void) mmfree(p, mp);
E 4
E 3
	}
}

/*
 * Vfork hook.
 * Associate queue with child when VM resources are passed.
 */
hilqvfork(mp, fup, tup)
	struct mapmem *mp;
	struct user *fup, *tup;
{
	struct hilloop *hilp = &hil0;		/* XXX */
	register struct hiliqueue *qp = &hilp->hl_queue[mp->mm_id];

#ifdef DEBUG
	if (hildebug & HDB_MMAP)
		printf("hilqvfork(%d): from %x to %x qnum %d, qprocp %x\n",
		       u.u_procp->p_pid, fup->u_procp, tup->u_procp,
		       mp->mm_id, qp->hq_procp);
#endif
	if (qp->hq_procp == fup->u_procp)
		qp->hq_procp = tup->u_procp;
}

/*
 * Exit hook.
 * Unmap all devices and free all queues.
 */
hilqexit(mp)
	struct mapmem *mp;
{
I 3
	struct proc *p = u.u_procp;		/* XXX */
E 3
	register struct hilloop *hilp = &hil0;	/* XXX */
	register int mask, i;
	int s;

#ifdef DEBUG
	if (hildebug & HDB_MMAP)
D 3
		printf("hilqexit(%d): qnum %d\n", u.u_procp->p_pid, mp->mm_id);
E 3
I 3
		printf("hilqexit(%d): qnum %d\n", p->p_pid, mp->mm_id);
E 3
#endif
	/*
	 * Atomically take all devices off the queue
	 */
	mask = ~hilqmask(mp->mm_id);
	s = splhil();
	for (i = 0; i < NHILD; i++)
		hilp->hl_device[i].hd_qmask &= mask;
	splx(s);
	/*
	 * Now unmap from user address space and free queue
	 */
	i = mp->mm_id;
	cifree((caddr_t)hilp->hl_queue[i].hq_eventqueue, sizeof(HILQ));
	hilp->hl_queue[i].hq_eventqueue = NULL;
	hilp->hl_queue[i].hq_procp = NULL;
D 3
	mmfree(mp);
E 3
I 3
D 4
	mmfree(p, mp);
E 4
I 4
	return(mmfree(p, mp));
E 4
E 3
}
#endif
E 5

D 6
#include "clist.h"
E 6
I 6
D 13
#include "sys/clist.h"
E 6

E 13
/*
D 13
 * This is just a copy of the virgin q_to_b routine with minor
D 9
D 10
 * optimizations for HIL use.  It is used for two reasons:
 * 1. If we have PAGE mode defined, the normal q_to_b processes
 *    chars one at a time and breaks on newlines.
 * 2. We don't have to raise the priority to spltty() for most
 *    of the clist manipulations.
E 10
I 10
 * optimizations for HIL use.  It is used because we don't have
 * to raise the priority to spltty() for most of the clist manipulations.
E 10
E 9
I 9
 * optimizations for HIL use.  It is used because we don't have
 * to raise the priority to spltty() for most of the clist manipulations.
E 9
 */
hilq_to_b(q, cp, cc)
	register struct clist *q;
	register char *cp;
{
D 9
	register struct cblock *bp;
	register int nc;
	char *acp;
	int s;
	extern char cwaiting;
E 9

D 9
	if (cc <= 0)
		return (0);
	s = splhil();
	if (q->c_cc <= 0) {
		q->c_cc = 0;
		q->c_cf = q->c_cl = NULL;
		splx(s);
		return (0);
	}
	acp = cp;

	while (cc) {
		nc = sizeof (struct cblock) - ((int)q->c_cf & CROUND);
		nc = MIN(nc, cc);
		nc = MIN(nc, q->c_cc);
		(void) bcopy(q->c_cf, cp, (unsigned)nc);
		q->c_cf += nc;
		q->c_cc -= nc;
		cc -= nc;
		cp += nc;
		if (q->c_cc <= 0) {
			bp = (struct cblock *)(q->c_cf - 1);
			bp = (struct cblock *)((int)bp & ~CROUND);
			q->c_cf = q->c_cl = NULL;
			spltty();
			bp->c_next = cfreelist;
			cfreelist = bp;
			cfreecount += CBSIZE;
			if (cwaiting) {
				wakeup(&cwaiting);
				cwaiting = 0;
			}
			break;
		}
		if (((int)q->c_cf & CROUND) == 0) {
			bp = (struct cblock *)(q->c_cf);
			bp--;
			q->c_cf = bp->c_next->c_info;
			spltty();
			bp->c_next = cfreelist;
			cfreelist = bp;
			cfreecount += CBSIZE;
			if (cwaiting) {
				wakeup(&cwaiting);
				cwaiting = 0;
			}
			splhil();
		}
	}
	splx(s);
	return (cp-acp);
E 9
I 9
	BODY_DELETED
E 9
}

/*
E 13
 * Cooked keyboard functions for ite driver.
 * There is only one "cooked" ITE keyboard (the first keyboard found)
 * per loop.  There may be other keyboards, but they will always be "raw".
 */

D 13
kbdbell()
E 13
I 13
kbdbell(unit)
	int unit;
E 13
{
D 13
	struct hilloop *hilp = &hil0;		/* XXX */
E 13
I 13
	struct hilloop *hilp = &hilloop[unit];
E 13

	hilbeep(hilp, &default_bell);
}

D 13
kbdenable()
E 13
I 13
kbdenable(unit)
	int unit;
E 13
{
D 13
	struct hilloop *hilp = &hil0;	/* XXX */
E 13
I 13
	struct hilloop *hilp = &hilloop[unit];
E 13
	register struct hil_dev *hildevice = hilp->hl_addr;
	char db;

	/* Set the autorepeat rate register */
	db = ar_format(KBD_ARR);
	send_hil_cmd(hildevice, HIL_SETARR, &db, 1, NULL);

	/* Set the autorepeat delay register */
	db = ar_format(KBD_ARD);
	send_hil_cmd(hildevice, HIL_SETARD, &db, 1, NULL);

	/* Enable interrupts */
	send_hil_cmd(hildevice, HIL_INTON, NULL, 0, NULL);
}

D 13
kbddisable()
E 13
I 13
kbddisable(unit)
	int unit;
E 13
{
}

/*
 * XXX: read keyboard directly and return code.
 * Used by console getchar routine.  Could really screw up anybody
 * reading from the keyboard in the normal, interrupt driven fashion.
 */
D 13
kbdgetc(statp)
	int *statp;
E 13
I 13
kbdgetc(unit, statp)
	int unit, *statp;
E 13
{
D 13
	struct hilloop *hilp = &hil0;		/* XXX */
E 13
I 13
	struct hilloop *hilp = &hilloop[unit];
E 13
	register struct hil_dev *hildevice = hilp->hl_addr;
	register int c, stat;
	int s;

	s = splhil();
D 13
	while (((stat = hildevice->hil_stat) & HIL_DATA_RDY) == 0)
E 13
I 13
	while (((stat = READHILSTAT(hildevice)) & HIL_DATA_RDY) == 0)
E 13
		;
D 13
	c = hildevice->hil_data;
E 13
I 13
	c = READHILDATA(hildevice);
E 13
	splx(s);
	*statp = stat;
	return(c);
}

/*
 * Recoginize and clear keyboard generated NMIs.
 * Returns 1 if it was ours, 0 otherwise.  Note that we cannot use
 * send_hil_cmd() to issue the clear NMI command as that would actually
 * lower the priority to splimp() and it doesn't wait for the completion
 * of the command.  Either of these conditions could result in the
 * interrupt reoccuring.  Note that we issue the CNMT command twice.
 * This seems to be needed, once is not always enough!?!
 */
D 13
kbdnmi()
E 13
I 13
kbdnmi(unit)
	int unit;
E 13
{
D 13
	register struct hilloop *hilp = &hil0;		/* XXX */

E 13
I 13
#ifdef hp300
	struct hilloop *hilp = &hilloop[0]; /* XXX how do we know on 300? */
#else
	struct hilloop *hilp = &hilloop[unit];
#endif
#ifdef hp300
E 13
	if ((*KBDNMISTAT & KBDNMI) == 0)
		return(0);
I 13
#endif
E 13
	HILWAIT(hilp->hl_addr);
D 13
	hilp->hl_addr->hil_cmd = HIL_CNMT;
E 13
I 13
	WRITEHILCMD(hilp->hl_addr, HIL_CNMT);
E 13
	HILWAIT(hilp->hl_addr);
D 13
	hilp->hl_addr->hil_cmd = HIL_CNMT;
E 13
I 13
	WRITEHILCMD(hilp->hl_addr, HIL_CNMT);
E 13
	HILWAIT(hilp->hl_addr);
	return(1);
}

#define HILSECURITY	0x33
#define HILIDENTIFY	0x03
#define HILSCBIT	0x04

/*
 * Called at boot time to print out info about interesting devices
 */
D 13
hilinfo(hilp)
	register struct hilloop *hilp;
E 13
I 13
hilinfo(unit)
	int unit;
E 13
{
I 13
  	register struct hilloop *hilp = &hilloop[unit];
E 13
	register int id, len;
	register struct kbdmap *km;

	/*
	 * Keyboard info.
	 */
	if (hilp->hl_kbddev) {
		printf("hil%d: ", hilp->hl_kbddev);
		for (km = kbd_map; km->kbd_code; km++)
			if (km->kbd_code == hilp->hl_kbdlang) {
				printf("%s ", km->kbd_desc);
				break;
			}
		printf("keyboard\n");
	}
	/*
	 * ID module.
	 * Attempt to locate the first ID module and print out its
	 * security code.  Is this a good idea??
	 */
	id = hiliddev(hilp);
	if (id) {
		hilp->hl_cmdbp = hilp->hl_cmdbuf;
		hilp->hl_cmddev = id;
		send_hildev_cmd(hilp, id, HILSECURITY);
		len = hilp->hl_cmdbp - hilp->hl_cmdbuf;
		hilp->hl_cmdbp = hilp->hl_cmdbuf;
		hilp->hl_cmddev = 0;
		printf("hil%d: security code", id);
		for (id = 0; id < len; id++)
			printf(" %x", hilp->hl_cmdbuf[id]);
		while (id++ < 16)
			printf(" 0");
		printf("\n");
	}
}

#define HILAR1	0x3E
#define HILAR2	0x3F

/*
 * Called after the loop has reconfigured.  Here we need to:
 *	- determine how many devices are on the loop
 *	  (some may have been added or removed)
 *	- locate the ITE keyboard (if any) and ensure
 *	  that it is in the proper state (raw or cooked)
 *	  and is set to use the proper language mapping table
 *	- ensure all other keyboards are raw
 * Note that our device state is now potentially invalid as
 * devices may no longer be where they were.  What we should
 * do here is either track where the devices went and move
 * state around accordingly or, more simply, just mark all
 * devices as HIL_DERROR and don't allow any further use until
 * they are closed.  This is a little too brutal for my tastes,
 * we prefer to just assume people won't move things around.
 */
hilconfig(hilp)
	register struct hilloop *hilp;
{
	u_char db;
	int s;

	s = splhil();
#ifdef DEBUG
	if (hildebug & HDB_CONFIG) {
		printf("hilconfig: reconfigured: ");
		send_hil_cmd(hilp->hl_addr, HIL_READLPSTAT, NULL, 0, &db);
		printf("LPSTAT %x, ", db);
		send_hil_cmd(hilp->hl_addr, HIL_READLPCTRL, NULL, 0, &db);
		printf("LPCTRL %x, ", db);
		send_hil_cmd(hilp->hl_addr, HIL_READKBDSADR, NULL, 0, &db);
		printf("KBDSADR %x\n", db);
		hilreport(hilp);
	}
#endif
	/*
	 * Determine how many devices are on the loop.
	 * Mark those as alive and real, all others as dead.
	 */
	db = 0;
	send_hil_cmd(hilp->hl_addr, HIL_READLPSTAT, NULL, 0, &db);
	hilp->hl_maxdev = db & LPS_DEVMASK;
I 13
#ifdef DEBUG
	if (hildebug & HDB_CONFIG)
		printf("hilconfig: %d devices found\n", hilp->hl_maxdev);
#endif
E 13
	for (db = 1; db < NHILD; db++) {
		if (db <= hilp->hl_maxdev)
			hilp->hl_device[db].hd_flags |= HIL_ALIVE;
		else
			hilp->hl_device[db].hd_flags &= ~HIL_ALIVE;
		hilp->hl_device[db].hd_flags &= ~HIL_PSEUDO;
	}
#ifdef DEBUG
	if (hildebug & (HDB_CONFIG|HDB_KEYBOARD))
		printf("hilconfig: max device %d\n", hilp->hl_maxdev);
#endif
	if (hilp->hl_maxdev == 0) {
		hilp->hl_kbddev = 0;
		splx(s);
		return;
	}
	/*
	 * Find out where the keyboards are and record the ITE keyboard
	 * (first one found).  If no keyboards found, we are all done.
	 */
	db = 0;
	send_hil_cmd(hilp->hl_addr, HIL_READKBDSADR, NULL, 0, &db);
#ifdef DEBUG
	if (hildebug & HDB_KEYBOARD)
		printf("hilconfig: keyboard: KBDSADR %x, old %d, new %d\n",
		       db, hilp->hl_kbddev, ffs((int)db));
#endif
	hilp->hl_kbddev = ffs((int)db);
	if (hilp->hl_kbddev == 0) {
		splx(s);
		return;
	}
	/*
	 * Determine if the keyboard should be cooked or raw and configure it.
	 */
	db = (hilp->hl_kbdflags & KBD_RAW) ? 0 : 1 << (hilp->hl_kbddev - 1);
	send_hil_cmd(hilp->hl_addr, HIL_WRITEKBDSADR, &db, 1, NULL);
	/*
	 * Re-enable autorepeat in raw mode, cooked mode AR is not affected.
	 */
	if (hilp->hl_kbdflags & (KBD_AR1|KBD_AR2)) {
		db = (hilp->hl_kbdflags & KBD_AR1) ? HILAR1 : HILAR2;
		hilp->hl_cmddev = hilp->hl_kbddev;
		send_hildev_cmd(hilp, hilp->hl_kbddev, db);
		hilp->hl_cmddev = 0;
	}
	/*
	 * Determine the keyboard language configuration, but don't
	 * override a user-specified setting.
	 */
	db = 0;
	send_hil_cmd(hilp->hl_addr, HIL_READKBDLANG, NULL, 0, &db);
#ifdef DEBUG
	if (hildebug & HDB_KEYBOARD)
		printf("hilconfig: language: old %x new %x\n",
		       hilp->hl_kbdlang, db);
#endif
	if (hilp->hl_kbdlang != KBD_SPECIAL) {
		struct kbdmap *km;

		for (km = kbd_map; km->kbd_code; km++)
			if (km->kbd_code == db) {
				hilp->hl_kbdlang = db;
				/* XXX */
				kbd_keymap = km->kbd_keymap;
				kbd_shiftmap = km->kbd_shiftmap;
				kbd_ctrlmap = km->kbd_ctrlmap;
				kbd_ctrlshiftmap = km->kbd_ctrlshiftmap;
				kbd_stringmap = km->kbd_stringmap;
			}
	}
	splx(s);
}

hilreset(hilp)
	struct hilloop *hilp;
{
	register struct hil_dev *hildevice = hilp->hl_addr;
	u_char db;

I 13
#ifdef DEBUG
	if (hildebug & HDB_FOLLOW)
		printf("hilreset(%x)\n", hilp);
#endif
E 13
	/*
	 * Initialize the loop: reconfigure, don't report errors,
	 * cook keyboards, and enable autopolling.
	 */
	db = LPC_RECONF | LPC_KBDCOOK | LPC_NOERROR | LPC_AUTOPOLL;
	send_hil_cmd(hildevice, HIL_WRITELPCTRL, &db, 1, NULL);
	/*
	 * Delay one second for reconfiguration and then read the the
	 * data register to clear the interrupt (if the loop reconfigured).
	 */
	DELAY(1000000);
D 13
	if (hildevice->hil_stat & HIL_DATA_RDY)
		db = hildevice->hil_data;
E 13
I 13
	if (READHILSTAT(hildevice) & HIL_DATA_RDY)
		db = READHILDATA(hildevice);
E 13
	/*
	 * The HIL loop may have reconfigured.  If so we proceed on,
	 * if not we loop until a successful reconfiguration is reported
	 * back to us.  The HIL loop will continue to attempt forever.
	 * Probably not very smart.
	 */
	do {
		send_hil_cmd(hildevice, HIL_READLPSTAT, NULL, 0, &db);
        } while ((db & (LPS_CONFFAIL|LPS_CONFGOOD)) == 0);
	/*
	 * At this point, the loop should have reconfigured.
	 * The reconfiguration interrupt has already called hilconfig()
D 4
	 * so the keyboard has been determined.  All that is left is
	 * 
E 4
I 4
	 * so the keyboard has been determined.
E 4
	 */
D 4
#if 0
	hilconfig(hilp);
#endif
E 4
	send_hil_cmd(hildevice, HIL_INTON, NULL, 0, NULL);
}

hilbeep(hilp, bp)
	struct hilloop *hilp;
	register struct _hilbell *bp;
{
	u_char buf[2];

	buf[0] = ~((bp->duration - 10) / 10);
	buf[1] = bp->frequency;
	send_hil_cmd(hilp->hl_addr, HIL_SETTONE, buf, 2, NULL);
}

/*
 * Locate and return the address of the first ID module, 0 if none present.
 */
hiliddev(hilp)
	register struct hilloop *hilp;
{
	register int i, len;

#ifdef DEBUG
	if (hildebug & HDB_IDMODULE)
D 13
		printf("hiliddev(%x): looking for idmodule...", hilp);
E 13
I 13
		printf("hiliddev(%x): max %d, looking for idmodule...",
		       hilp, hilp->hl_maxdev);
E 13
#endif
	for (i = 1; i <= hilp->hl_maxdev; i++) {
		hilp->hl_cmdbp = hilp->hl_cmdbuf;
		hilp->hl_cmddev = i;
		send_hildev_cmd(hilp, i, HILIDENTIFY);
		/*
		 * XXX: the final condition checks to ensure that the
		 * device ID byte is in the range of the ID module (0x30-0x3F)
		 */
		len = hilp->hl_cmdbp - hilp->hl_cmdbuf;
		if (len > 1 && (hilp->hl_cmdbuf[1] & HILSCBIT) &&
		    (hilp->hl_cmdbuf[0] & 0xF0) == 0x30) {
			hilp->hl_cmdbp = hilp->hl_cmdbuf;
			hilp->hl_cmddev = i;
			send_hildev_cmd(hilp, i, HILSECURITY);
			break;
		}
	}		
	hilp->hl_cmdbp = hilp->hl_cmdbuf;
	hilp->hl_cmddev = 0;
#ifdef DEBUG
	if (hildebug & HDB_IDMODULE)
		if (i <= hilp->hl_maxdev)
			printf("found at %d\n", i);
		else
			printf("not found\n");
#endif
	return(i <= hilp->hl_maxdev ? i : 0);
}

I 13
#ifdef HPUXCOMPAT
E 13
/*
I 13
 * XXX map devno as expected by HP-UX
 */
hildevno(dev)
	dev_t dev;
{
	int newdev;

	newdev = 24 << 24;
#ifdef HILCOMPAT
	/*
	 * XXX compat check
	 * Don't convert old style specfiles already in correct format
	 */
	if (minor(dev) && (dev & 0xF) == 0)
		newdev |= minor(dev);
	else
#endif
	newdev |= (HILLOOP(dev) << 8) | (HILUNIT(dev) << 4);
	return(newdev);
}
#endif

/*
E 13
 * Low level routines which actually talk to the 8042 chip.
 */

/*
 * Send a command to the 8042 with zero or more bytes of data.
 * If rdata is non-null, wait for and return a byte of data.
 * We run at splimp() to make the transaction as atomic as
 * possible without blocking the clock (is this necessary?)
 */
send_hil_cmd(hildevice, cmd, data, dlen, rdata)
	register struct hil_dev *hildevice;
	u_char cmd, *data, dlen;
	u_char *rdata;
{
	u_char status;
	int s = splimp();

	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = cmd;
E 13
I 13
	WRITEHILCMD(hildevice, cmd);
E 13
	while (dlen--) {
	  	HILWAIT(hildevice);
D 13
		hildevice->hil_data = *data++;
E 13
I 13
		WRITEHILDATA(hildevice, *data++);
E 13
	}
	if (rdata) {
		do {
			HILDATAWAIT(hildevice);
D 13
			status = hildevice->hil_stat;
			*rdata = hildevice->hil_data;
E 13
I 13
			status = READHILSTAT(hildevice);
			*rdata = READHILDATA(hildevice);
E 13
		} while (((status >> HIL_SSHIFT) & HIL_SMASK) != HIL_68K);
	}
	splx(s);
}

/*
 * Send a command to a device on the loop.
 * Since only one command can be active on the loop at any time,
 * we must ensure that we are not interrupted during this process.
 * Hence we mask interrupts to prevent potential access from most
 * interrupt routines and turn off auto-polling to disable the
 * internally generated poll commands.
 *
 * splhigh is extremely conservative but insures atomic operation,
 * splimp (clock only interrupts) seems to be good enough in practice.
 */
send_hildev_cmd(hilp, device, cmd)
	register struct hilloop *hilp;
	char device, cmd;
{
	register struct hil_dev *hildevice = hilp->hl_addr;
	u_char status, c;
	int s = splimp();

	polloff(hildevice);

	/*
	 * Transfer the command and device info to the chip
	 */
	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = HIL_STARTCMD;
E 13
I 13
	WRITEHILCMD(hildevice, HIL_STARTCMD);
E 13
  	HILWAIT(hildevice);
D 13
	hildevice->hil_data = 8 + device;
E 13
I 13
	WRITEHILDATA(hildevice, 8 + device);
E 13
  	HILWAIT(hildevice);
D 13
	hildevice->hil_data = cmd;
E 13
I 13
	WRITEHILDATA(hildevice, cmd);
E 13
  	HILWAIT(hildevice);
D 13
	hildevice->hil_data = HIL_TIMEOUT;
E 13
I 13
	WRITEHILDATA(hildevice, HIL_TIMEOUT);
E 13
	/*
	 * Trigger the command and wait for completion
	 */
	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = HIL_TRIGGER;
E 13
I 13
	WRITEHILCMD(hildevice, HIL_TRIGGER);
E 13
	hilp->hl_cmddone = FALSE;
	do {
		HILDATAWAIT(hildevice);
D 13
		status = hildevice->hil_stat;
		c = hildevice->hil_data;
		hil_process_int(status, c);
E 13
I 13
		status = READHILSTAT(hildevice);
		c = READHILDATA(hildevice);
		hil_process_int(hilp, status, c);
E 13
	} while (!hilp->hl_cmddone);

	pollon(hildevice);
	splx(s);
}

/*
 * Turn auto-polling off and on.
 * Also disables and enable auto-repeat.  Why?
 */
polloff(hildevice)
	register struct hil_dev *hildevice;
{
	register char db;

	/*
	 * Turn off auto repeat
	 */
	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = HIL_SETARR;
E 13
I 13
	WRITEHILCMD(hildevice, HIL_SETARR);
E 13
	HILWAIT(hildevice);
D 13
	hildevice->hil_data = 0;
E 13
I 13
	WRITEHILDATA(hildevice, 0);
E 13
	/*
	 * Turn off auto-polling
	 */
	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = HIL_READLPCTRL;
E 13
I 13
	WRITEHILCMD(hildevice, HIL_READLPCTRL);
E 13
	HILDATAWAIT(hildevice);
D 13
	db = hildevice->hil_data;
E 13
I 13
	db = READHILDATA(hildevice);
E 13
	db &= ~LPC_AUTOPOLL;
	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = HIL_WRITELPCTRL;
E 13
I 13
	WRITEHILCMD(hildevice, HIL_WRITELPCTRL);
E 13
	HILWAIT(hildevice);
D 13
	hildevice->hil_data = db;
E 13
I 13
	WRITEHILDATA(hildevice, db);
E 13
	/*
	 * Must wait til polling is really stopped
	 */
	do {	
		HILWAIT(hildevice);
D 13
		hildevice->hil_cmd = HIL_READBUSY;
E 13
I 13
		WRITEHILCMD(hildevice, HIL_READBUSY);
E 13
		HILDATAWAIT(hildevice);
D 13
		db = hildevice->hil_data;
E 13
I 13
		db = READHILDATA(hildevice);
E 13
	} while (db & BSY_LOOPBUSY);
}

pollon(hildevice)
	register struct hil_dev *hildevice;
{
	register char db;

	/*
	 * Turn on auto polling
	 */
	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = HIL_READLPCTRL;
E 13
I 13
	WRITEHILCMD(hildevice, HIL_READLPCTRL);
E 13
	HILDATAWAIT(hildevice);
D 13
	db = hildevice->hil_data;
E 13
I 13
	db = READHILDATA(hildevice);
E 13
	db |= LPC_AUTOPOLL;
	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = HIL_WRITELPCTRL;
E 13
I 13
	WRITEHILCMD(hildevice, HIL_WRITELPCTRL);
E 13
	HILWAIT(hildevice);
D 13
	hildevice->hil_data = db;
E 13
I 13
	WRITEHILDATA(hildevice, db);
E 13
	/*
	 * Turn on auto repeat
	 */
	HILWAIT(hildevice);
D 13
	hildevice->hil_cmd = HIL_SETARR;
E 13
I 13
	WRITEHILCMD(hildevice, HIL_SETARR);
E 13
	HILWAIT(hildevice);
D 13
	hildevice->hil_data = ar_format(KBD_ARR);
E 13
I 13
	WRITEHILDATA(hildevice, ar_format(KBD_ARR));
E 13
}

#ifdef DEBUG
printhilpollbuf(hilp)
	register struct hilloop *hilp;
{
  	register u_char *cp;
	register int i, len;

	cp = hilp->hl_pollbuf;
	len = hilp->hl_pollbp - cp;
	for (i = 0; i < len; i++)
		printf("%x ", hilp->hl_pollbuf[i]);
	printf("\n");
}

printhilcmdbuf(hilp)
	register struct hilloop *hilp;
{
  	register u_char *cp;
	register int i, len;

	cp = hilp->hl_cmdbuf;
	len = hilp->hl_cmdbp - cp;
	for (i = 0; i < len; i++)
		printf("%x ", hilp->hl_cmdbuf[i]);
	printf("\n");
}

hilreport(hilp)
	register struct hilloop *hilp;
{
	register int i, len;
	int s = splhil();

	for (i = 1; i <= hilp->hl_maxdev; i++) {
		hilp->hl_cmdbp = hilp->hl_cmdbuf;
		hilp->hl_cmddev = i;
		send_hildev_cmd(hilp, i, HILIDENTIFY);
		printf("hil%d: id: ", i);
		printhilcmdbuf(hilp);
		len = hilp->hl_cmdbp - hilp->hl_cmdbuf;
		if (len > 1 && (hilp->hl_cmdbuf[1] & HILSCBIT)) {
			hilp->hl_cmdbp = hilp->hl_cmdbuf;
			hilp->hl_cmddev = i;
			send_hildev_cmd(hilp, i, HILSECURITY);
			printf("hil%d: sc: ", i);
			printhilcmdbuf(hilp);
		}
	}		
	hilp->hl_cmdbp = hilp->hl_cmdbuf;
	hilp->hl_cmddev = 0;
	splx(s);
}
#endif
E 1
