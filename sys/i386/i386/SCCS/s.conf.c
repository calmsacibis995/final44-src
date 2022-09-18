h02578
s 00005/00000/00262
d D 8.3 94/01/21 17:07:19 bostic 15 14
c add USL's copyright notice
e
s 00018/00000/00244
d D 8.2 93/11/14 13:32:13 hibler 14 13
c add iszerodev predicate
e
s 00002/00002/00242
d D 8.1 93/06/11 15:34:28 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00238
d D 5.11 92/10/11 10:10:53 bostic 12 11
c make kernel includes standard
e
s 00002/00028/00242
d D 5.10 92/02/05 10:52:36 bostic 11 10
c put on a reasonable header 
e
s 00222/00160/00048
d D 5.9 91/11/13 17:45:49 william 10 9
c changes to fix new vm on i386
e
s 00003/00000/00205
d D 5.8 91/05/12 22:26:33 william 9 8
c missing an entry for the mem device
e
s 00009/00003/00196
d D 5.7 91/05/09 18:12:40 william 8 7
c Donn Seely's virtual console code
e
s 00086/00091/00113
d D 5.6 91/05/09 18:10:21 william 7 6
c recent change in /sys/conf.h structure definitions
e
s 00042/00041/00162
d D 5.5 91/01/19 12:36:29 william 6 5
c reno changes
e
s 00000/00000/00203
d D 5.4 91/01/15 12:20:34 bill 5 4
c reno changes
e
s 00074/00010/00129
d D 5.3 90/11/14 12:19:19 bill 4 3
c cleanup, add some devices
e
s 00018/00002/00121
d D 5.2 90/06/23 19:24:55 donahn 3 2
c new drivers
e
s 00037/00166/00086
d D 5.1 90/04/24 18:56:23 william 2 1
c 1st Berkeley Release
e
s 00252/00000/00000
d D 1.1 90/03/12 15:47:44 bill 1 0
c date and time created 90/03/12 15:47:44 by bill
e
u
U
t
T
I 1
D 2
/*	conf.c	1.9	87/03/28	*/
E 2
I 2
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
E 10
I 10
D 13
 * Copyright (c) 1991 The Regents of the University of California.
E 10
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 15
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 15
E 13
 *
D 10
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
E 10
I 10
D 11
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 10
 *
D 8
 * %sccs.include.386.c%
E 8
I 8
D 10
 * %sccs.include.redist.c%
E 10
I 10
D 11
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 10
E 8
 *
D 10
 *	%W% (Berkeley) %G%
E 10
I 10
 *      @(#)conf.c	7.9 (Berkeley) 5/28/91
E 11
I 11
 *	%W% (Berkeley) %G%
E 11
E 10
 */
E 2

I 3
D 4
/*	conf.c	1.9	87/03/28	*/

E 4
E 3
D 10
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "ioctl.h"
#include "tty.h"
#include "conf.h"
E 10
I 10
D 12
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/buf.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/conf.h"
E 12
I 12
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/conf.h>
E 12
E 10

D 7
int	nulldev();
int	nodev();
E 7
I 7
D 10
int	nullop(), enxio(), enodev(), rawread(), rawwrite(), swstrategy();
E 7
I 6
int	rawread(), rawwrite(), swstrategy();
E 10
I 10
int	rawread		__P((dev_t, struct uio *, int));
int	rawwrite	__P((dev_t, struct uio *, int));
int	swstrategy	__P((struct buf *));
int	ttselect	__P((dev_t, int, struct proc *));
E 10
E 6

D 2
#include "dk.h"
#if NVD > 0
int	vdopen(),vdclose(),vdstrategy(),vdread(),vdwrite(),vdioctl();
int	vddump(),vdsize();
E 2
I 2
D 10
#include "wd.h"
#if NWD > 0
int	wdopen(),wdclose(),wdstrategy(),wdread(),wdwrite(),wdioctl();
int	wddump(),wdsize();
E 2
#else
D 2
#define	vdopen		nodev
#define	vdclose		nodev
#define	vdstrategy	nodev
#define	vdread		nodev
#define	vdwrite		nodev
#define	vdioctl		nodev
#define	vddump		nodev
#define	vdsize		0
E 2
I 2
D 7
#define	wdopen		nodev
#define	wdclose		nodev
#define	wdstrategy	nodev
#define	wdread		nodev
#define	wdwrite		nodev
#define	wdioctl		nodev
#define	wddump		nodev
E 7
I 7
#define	wdopen		enxio
#define	wdclose		enxio
#define	wdstrategy	enxio
#define	wdread		enxio
#define	wdwrite		enxio
#define	wdioctl		enxio
#define	wddump		enxio
E 7
D 6
#define	wdsize		0
E 6
I 6
#define	wdsize		NULL
E 6
E 2
#endif
E 10
I 10
#define	dev_type_open(n)	int n __P((dev_t, int, int, struct proc *))
#define	dev_type_close(n)	int n __P((dev_t, int, int, struct proc *))
#define	dev_type_strategy(n)	int n __P((struct buf *))
#define	dev_type_ioctl(n) \
	int n __P((dev_t, int, caddr_t, int, struct proc *))
E 10

I 3
D 4
int fdstrategy(),fdopen(),fdclose(),fdread(),fdwrite();
E 4
I 4
D 10
#include "xd.h"
#if NXD > 0
int	xdopen(),xdclose(),xdstrategy(),xdread(),xdwrite(),xdioctl();
int	xddump(),xdsize();
#else
D 7
#define	xdopen		nodev
#define	xdclose		nodev
#define	xdstrategy	nodev
#define	xdread		nodev
#define	xdwrite		nodev
#define	xdioctl		nodev
#define	xddump		nodev
E 7
I 7
#define	xdopen		enxio
#define	xdclose		enxio
#define	xdstrategy	enxio
#define	xdread		enxio
#define	xdwrite		enxio
#define	xdioctl		enxio
#define	xddump		enxio
E 7
D 6
#define	xdsize		0
E 6
I 6
#define	xdsize		NULL
E 6
#endif
E 10
I 10
/* bdevsw-specific types */
#define	dev_type_dump(n)	int n __P((dev_t))
#define	dev_type_size(n)	int n __P((dev_t))
E 10
E 4
E 3
D 2
#include "yc.h"
#if NCY > 0
int	cyopen(),cyclose(),cystrategy(),cyread(),cywrite(),cydump(),cyioctl(),cyreset();
#else
#define	cyopen		nodev
#define	cyclose		nodev
#define	cystrategy	nodev
#define	cyread		nodev
#define	cywrite		nodev
#define	cydump		nodev
#define	cyioctl		nodev
#define	cyreset		nulldev
#endif
E 2

I 4
D 10
#include "wt.h"
#if NWT > 0
int	wtopen(),wtclose(),wtstrategy(),wtread(),wtwrite(),wtioctl();
int	wtdump(),wtsize();
#else
D 7
#define	wtopen		nodev
#define	wtclose		nodev
#define	wtstrategy	nodev
#define	wtread		nodev
#define	wtwrite		nodev
#define	wtioctl		nodev
#define	wtdump		nodev
E 7
I 7
#define	wtopen		enxio
#define	wtclose		enxio
#define	wtstrategy	enxio
#define	wtread		enxio
#define	wtwrite		enxio
#define	wtioctl		enxio
#define	wtdump		enxio
E 7
D 6
#define	wtsize		0
E 6
I 6
#define	wtsize		NULL
E 6
#endif
E 10
I 10
#define	dev_decl(n,t)	__CONCAT(dev_type_,t)(__CONCAT(n,t))
#define	dev_init(c,n,t) \
	(c > 0 ? __CONCAT(n,t) : (__CONCAT(dev_type_,t)((*))) enxio)
E 10
E 4
I 3

I 10
/* bdevsw-specific initializations */
#define	dev_size_init(c,n)	(c > 0 ? __CONCAT(n,size) : 0)

#define	bdev_decl(n) \
	dev_decl(n,open); dev_decl(n,close); dev_decl(n,strategy); \
	dev_decl(n,ioctl); dev_decl(n,dump); dev_decl(n,size)

#define	bdev_disk_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
	dev_init(c,n,dump), dev_size_init(c,n), 0 }

#define	bdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
	dev_init(c,n,dump), 0, B_TAPE }

#define	bdev_swap_init() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	swstrategy, (dev_type_ioctl((*))) enodev, \
	(dev_type_dump((*))) enodev, 0, 0 }

#define	bdev_notdef()	bdev_tape_init(0,no)
bdev_decl(no);	/* dummy declarations */

#include "wd.h"
E 10
I 4
#include "fd.h"
D 10
#if NFD > 0
D 6
int	fdopen(),fdclose(),fdstrategy(),fdread(),fdwrite();
E 6
I 6
int	Fdopen(),fdclose(),fdstrategy(),fdread(),fdwrite();
E 6
D 7
#define	fdioctl		nodev
#define	fddump		nodev
E 7
I 7
#define	fdioctl		enxio
#define	fddump		enxio
E 7
D 6
#define	fdsize		0
E 6
I 6
#define	fdsize		NULL
E 6
#else
D 6
#define	fdopen		nodev
E 6
I 6
D 7
#define	Fdopen		nodev
E 6
#define	fdclose		nodev
#define	fdstrategy	nodev
#define	fdread		nodev
#define	fdwrite		nodev
#define	fdioctl		nodev
#define	fddump		nodev
E 7
I 7
#define	Fdopen		enxio
#define	fdclose		enxio
#define	fdstrategy	enxio
#define	fdread		enxio
#define	fdwrite		enxio
#define	fdioctl		enxio
#define	fddump		enxio
E 7
D 6
#define	fdsize		0
E 6
I 6
#define	fdsize		NULL
E 6
#endif
E 10
I 10
#include "wt.h"
#include "xd.h"
E 10

E 4
E 3
D 10
int	swstrategy(),swread(),swwrite();
E 10
I 10
bdev_decl(wd);
bdev_decl(Fd);
bdev_decl(wt);
bdev_decl(xd);
E 10

struct bdevsw	bdevsw[] =
{
D 2
	{ nodev,	nulldev,	nodev,		nodev,		/*0*/
	  nodev,	0,		0 },
	{ vdopen,	vdclose,	vdstrategy,	vdioctl,	/*1*/
	  vddump,	vdsize,		0 },
	{ nodev,	nulldev,	nodev,		nodev,		/*2*/
	  nodev,	0,		0 },
	{ cyopen,	cyclose,	cystrategy,	cyioctl,	/*3*/
	  cydump,	0,		B_TAPE },
	{ nodev,	nodev,		swstrategy,	nodev,		/*4*/
	  nodev,	0,		0 },
E 2
I 2
D 3
	{ wdopen,	wdclose,	wdstrategy,	wdioctl,	/*1*/
E 3
I 3
D 10
	{ wdopen,	wdclose,	wdstrategy,	wdioctl,	/*0*/
E 3
D 6
	  wddump,	wdsize,		0 },
E 6
I 6
	  wddump,	wdsize,		NULL },
E 6
D 3
	{ nodev,	nodev,	swstrategy,	nodev,	/*1*/
E 3
I 3
D 7
	{ nodev,	nodev,		swstrategy,	nodev,		/*1*/
E 3
D 6
	  nodev,	nodev,		0 },
I 3
D 4
	{ fdopen,	fdclose,	fdstrategy,	nulldev,	/*2*/
	  nodev,	nodev,		0 },
E 4
I 4
	{ fdopen,	fdclose,	fdstrategy,	fdioctl,	/*2*/
	  fddump,	fdsize,		0 },
E 6
I 6
	  nodev,	nodev,		NULL },
E 7
I 7
	{ enodev,	enodev,		swstrategy,	enodev,		/*1*/
	  enodev,	enodev,		NULL },
E 7
	{ Fdopen,	fdclose,	fdstrategy,	fdioctl,	/*2*/
	  fddump,	fdsize,		NULL },
E 6
	{ wtopen,	wtclose,	wtstrategy,	wtioctl,	/*3*/
	  wtdump,	wtsize,		B_TAPE },
	{ xdopen,	xdclose,	xdstrategy,	xdioctl,	/*4*/
D 6
	  xddump,	xdsize,		0 },
E 6
I 6
D 7
	  xddump,	xdsize,		NULL },
E 7
I 7
	  xddump,	xdsize,		NULL }
E 10
I 10
	bdev_disk_init(NWD,wd),	/* 0: st506/rll/esdi/ide disk */
	bdev_swap_init(),	/* 1: swap pseudo-device */
	bdev_disk_init(NFD,Fd),	/* 2: floppy disk */
	bdev_tape_init(NWT,wt),	/* 3: QIC-24/60/120/150 cartridge tape */
	bdev_disk_init(NXD,xd),	/* 4: temp alt st506/rll/esdi/ide disk */
E 10
E 7
E 6
E 4
E 3
E 2
};
I 10

E 10
int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

D 8
int	cnopen(),cnclose(),cnread(),cnwrite(),cnioctl();
E 8
I 8
D 10
int	cnopen(),cnclose(),cnread(),cnwrite(),cnioctl(),cnselect();
E 10
I 10
/* cdevsw-specific types */
#define	dev_type_read(n)	int n __P((dev_t, struct uio *, int))
#define	dev_type_write(n)	int n __P((dev_t, struct uio *, int))
#define	dev_type_stop(n)	int n __P((struct tty *, int))
#define	dev_type_reset(n)	int n __P((int))
#define	dev_type_select(n)	int n __P((dev_t, int, struct proc *))
#define	dev_type_map(n)	int n __P(())
E 10
E 8
D 7
extern	struct tty cons;
E 7

I 8
D 10
int	pcopen(),pcclose(),pcread(),pcwrite(),pcioctl();
extern	struct tty pccons;
E 10
I 10
#define	cdev_decl(n) \
	dev_decl(n,open); dev_decl(n,close); dev_decl(n,read); \
	dev_decl(n,write); dev_decl(n,ioctl); dev_decl(n,stop); \
	dev_decl(n,reset); dev_decl(n,select); dev_decl(n,map); \
	dev_decl(n,strategy); extern struct tty __CONCAT(n,_tty)[]
E 10

E 8
D 2
#include "vx.h"
#if NVX == 0
#define	vxopen	nodev
#define	vxclose	nodev
#define	vxread	nodev
#define	vxwrite	nodev
#define	vxioctl	nodev
#define	vxstop	nodev
#define	vxreset	nulldev
#define	vx_tty	0
#else
int	vxopen(),vxclose(),vxread(),vxwrite(),vxioctl(),vxstop(),vxreset();
struct	tty vx_tty[];
#endif

E 2
D 7
int	syopen(),syread(),sywrite(),syioctl(),syselect();
E 7
I 7
D 10
int	cttyopen(), cttyread(), cttywrite(), cttyioctl(), cttyselect();
E 10
I 10
#define	dev_tty_init(c,n)	(c > 0 ? __CONCAT(n,_tty) : 0)
E 10
E 7

D 6
int 	mmread(),mmwrite();
E 6
I 6
D 10
int 	mmrw();
E 6
#define	mmselect	seltrue
E 10
I 10
/* open, read, write, ioctl, strategy */
#define	cdev_disk_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	dev_init(c,n,strategy) }
E 10

I 10
/* open, close, read, write, ioctl, strategy */
#define	cdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	dev_init(c,n,strategy) }

/* open, close, read, write, ioctl, stop, tty */
#define	cdev_tty_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), dev_init(c,n,stop), \
	(dev_type_reset((*))) nullop, dev_tty_init(c,n), ttselect, \
	(dev_type_map((*))) enodev, 0 }

#define	cdev_notdef() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	(dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
	(dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, \
	(dev_type_map((*))) enodev, 0 }

cdev_decl(no);			/* dummy declarations */

cdev_decl(cn);
/* open, close, read, write, ioctl, select -- XXX should be a tty */
#define	cdev_cn_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

cdev_decl(ctty);
/* open, read, write, ioctl, select -- XXX should be a tty */
#define	cdev_ctty_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

dev_type_read(mmrw);
/* read/write */
#define	cdev_mm_init(c,n) { \
	(dev_type_open((*))) nullop, (dev_type_close((*))) nullop, mmrw, \
	mmrw, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, 0 }

/* read, write, strategy */
#define	cdev_swap_init(c,n) { \
	(dev_type_open((*))) nullop, (dev_type_close((*))) nullop, rawread, \
	rawwrite, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, (dev_type_select((*))) enodev, \
	(dev_type_map((*))) enodev, dev_init(c,n,strategy) }

E 10
#include "pty.h"
D 10
#if NPTY > 0
int	ptsopen(),ptsclose(),ptsread(),ptswrite(),ptsstop();
int	ptcopen(),ptcclose(),ptcread(),ptcwrite(),ptcselect();
int	ptyioctl();
struct	tty pt_tty[];
#else
D 7
#define ptsopen		nodev
#define ptsclose	nodev
#define ptsread		nodev
#define ptswrite	nodev
#define ptcopen		nodev
#define ptcclose	nodev
#define ptcread		nodev
#define ptcwrite	nodev
#define ptyioctl	nodev
E 7
I 7
#define ptsopen		enxio
#define ptsclose	enxio
#define ptsread		enxio
#define ptswrite	enxio
#define ptcopen		enxio
#define ptcclose	enxio
#define ptcread		enxio
#define ptcwrite	enxio
#define ptyioctl	enxio
E 7
D 6
#define	pt_tty		0
E 6
I 6
#define	pt_tty		NULL
E 6
D 7
#define	ptcselect	nodev
#define	ptsstop		nulldev
E 7
I 7
#define	ptcselect	enxio
#define	ptsstop		nullop
E 7
#endif
E 10
I 10
#define	pts_tty		pt_tty
#define	ptsioctl	ptyioctl
cdev_decl(pts);
#define	ptc_tty		pt_tty
#define	ptcioctl	ptyioctl
cdev_decl(ptc);
E 10

I 10
/* open, close, read, write, ioctl, tty, select */
#define	cdev_ptc_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, dev_tty_init(c,n), dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

cdev_decl(log);
/* open, close, read, ioctl, select -- XXX should be a generic device */
#define	cdev_log_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	(dev_type_write((*))) enodev, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	dev_init(c,n,select), (dev_type_map((*))) enodev, 0 }

cdev_decl(wd);
cdev_decl(Fd);
cdev_decl(xd);
cdev_decl(wt);

E 10
I 4
#include "com.h"
D 10
#if NCOM > 0
int	comopen(),comclose(),comread(),comwrite(),comioctl();
D 6
int	comreset();
E 6
I 6
D 7
#define comreset	nodev
E 7
I 7
#define comreset	enxio
E 7
E 6
extern	struct tty com_tty[];
#else
D 7
#define comopen		nodev
#define comclose	nodev
#define comread		nodev
#define comwrite	nodev
#define comioctl	nodev
#define comreset	nodev
E 7
I 7
#define comopen		enxio
#define comclose	enxio
#define comread		enxio
#define comwrite	enxio
#define comioctl	enxio
#define comreset	enxio
E 7
D 6
#define	com_tty		0
E 6
I 6
#define	com_tty		NULL
E 6
#endif
E 10

E 4
D 2
#include "vbsc.h"
#if NVBSC > 0
int	bscopen(), bscclose(), bscread(), bscwrite(), bscioctl();
int	bsmopen(),bsmclose(),bsmread(),bsmwrite(),bsmioctl();
int	bstopen(),bstclose(),bstread(),bstioctl();
#else
#define bscopen		nodev
#define bscclose	nodev
#define bscread		nodev
#define bscwrite	nodev
#define bscioctl	nodev
#define bsmopen		nodev
#define bsmclose	nodev
#define bsmread		nodev
#define bsmwrite	nodev
#define bsmioctl	nodev
#define bstopen		nodev
#define bstclose	nodev
#define bstread		nodev
#define bstwrite	nodev
#define bstioctl	nodev
#endif

#if NII > 0
int	iiioctl(), iiclose(), iiopen();
#else
#define	iiopen	nodev
#define	iiclose	nodev
#define	iiioctl	nodev
#endif

#include "enp.h"
#if NENP > 0
int	enpr_open(), enpr_close(), enpr_read(), enpr_write(), enpr_ioctl();
#else
#define enpr_open	nodev
#define enpr_close	nodev
#define enpr_read	nodev
#define enpr_write	nodev
#define enpr_ioctl	nodev
#endif

#include "dr.h"
#if NDR > 0
int     dropen(),drclose(),drread(),drwrite(),drioctl(),drreset();
#else
#define dropen nodev
#define drclose nodev
#define drread nodev
#define drwrite nodev
#define drioctl nodev
#define drreset nodev
#endif

#include "ik.h"
#if NIK > 0
int     ikopen(),ikclose(),ikread(),ikwrite(),ikioctl();
#else
#define ikopen nodev
#define ikclose nodev
#define ikread nodev
#define ikwrite nodev
#define ikioctl nodev
#endif

E 2
D 10
int	logopen(),logclose(),logread(),logioctl(),logselect();
E 10
I 10
cdev_decl(com);
E 10

D 10
int	ttselect(), seltrue();
E 10
I 10
#include "pc.h"
E 10

I 10
cdev_decl(pc);
E 10
I 3
D 4
int	comopen(),comclose(),comread(),comwrite(),comioctl();
int	comreset();
extern	struct tty com_tty[];
E 4

I 10
/* open, close, read, write, ioctl, tty -- XXX should be a tty */
extern struct tty pccons;
#define	cdev_pc_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, &pccons, ttselect, \
	(dev_type_map((*))) enodev, 0 }

#include "bpfilter.h"
cdev_decl(bpf);

/* open, close, read, write, ioctl, select -- XXX should be generic device */
#define	cdev_bpf_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) enodev, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

E 10
E 3
struct cdevsw	cdevsw[] =
{
D 7
	cnopen,		cnclose,	cnread,		cnwrite,	/*0*/
	cnioctl,	nulldev,	nulldev,	&cons,
D 6
	ttselect,	nodev,
E 6
I 6
	ttselect,	nodev,		NULL,
E 6
D 2
	vxopen,		vxclose,	vxread,		vxwrite,	/*1*/
	vxioctl,	vxstop,		vxreset,	vx_tty,
	ttselect,	nodev,
	syopen,		nulldev,	syread,		sywrite,	/*2*/
E 2
I 2
	syopen,		nulldev,	syread,		sywrite,	/*1*/
E 2
D 6
	syioctl,	nulldev,	nulldev,	0,
	syselect,	nodev,
D 2
	nulldev,	nulldev,	mmread,		mmwrite,	/*3*/
E 2
I 2
	nulldev,	nulldev,	mmread,		mmwrite,	/*2*/
E 2
	nodev,		nulldev,	nulldev,	0,
	mmselect,	nodev,
E 6
I 6
	syioctl,	nulldev,	nulldev,	NULL,
	syselect,	nodev,		NULL,
	nulldev,	nulldev,	mmrw,		mmrw,		/*2*/
	nodev,		nulldev,	nulldev,	NULL,
	mmselect,	nodev,		NULL,
E 6
D 2
	nodev,		nulldev,	nodev,		nodev,		/*4*/
	nodev,		nodev,		nulldev,	0,
E 2
I 2
	wdopen,		wdclose,	wdread,		wdwrite,	/*3*/
D 6
	wdioctl,	nodev,		nulldev,	0,
E 2
	seltrue,	nodev,
D 2
	vdopen,		vdclose,	vdread,		vdwrite,	/*5*/
	vdioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,
	nodev,		nulldev,	nodev,		nodev,		/*6*/
E 2
I 2
	nulldev,	nulldev,	swread,		swwrite,	/*4*/
E 2
	nodev,		nodev,		nulldev,	0,
D 2
	seltrue,	nodev,
	cyopen,		cyclose,	cyread,		cywrite,	/*7*/
	cyioctl,	nodev,		cyreset,	0,
	seltrue,	nodev,
	nulldev,	nulldev,	swread,		swwrite,	/*8*/
	nodev,		nodev,		nulldev,	0,
E 2
	nodev,		nodev,
E 6
I 6
	wdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		wdstrategy,
	nulldev,	nulldev,	rawread,	rawwrite,	/*4*/
	nodev,		nodev,		nulldev,	NULL,
	nodev,		nodev,		swstrategy,
E 6
D 2
	ptsopen,	ptsclose,	ptsread,	ptswrite,	/*9*/
E 2
I 2
	ptsopen,	ptsclose,	ptsread,	ptswrite,	/*5*/
E 2
D 6
	ptyioctl,	ptsstop,	nodev,		pt_tty,
	ttselect,	nodev,
E 6
I 6
	ptyioctl,	ptsstop,	nulldev,	pt_tty,
	ttselect,	nodev,		NULL,
E 6
D 2
	ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*10*/
E 2
I 2
	ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*6*/
E 2
D 6
	ptyioctl,	nulldev,	nodev,		pt_tty,
	ptcselect,	nodev,
E 6
I 6
	ptyioctl,	nulldev,	nulldev,	pt_tty,
	ptcselect,	nodev,		NULL,
E 6
D 2
	bscopen,	bscclose,	bscread,	bscwrite,	/*11*/
	bscioctl,	nodev,		nulldev,	0,
	nodev,		nodev,
	bsmopen,	bsmclose,	bsmread,	bsmwrite,	/*12*/
	bsmioctl,	nodev,		nulldev,	0,
	nodev,		nodev,
	bstopen,	bstclose,	bstread,	nodev,		/*13*/
	bstioctl,	nodev,		nulldev,	0,
	nodev,		nodev,
	iiopen,		iiclose,	nulldev,	nulldev,	/*14*/
	iiioctl,	nulldev,	nulldev,	0,
	seltrue,	nodev,
	logopen,	logclose,	logread,	nodev,		/*15*/
E 2
I 2
	logopen,	logclose,	logread,	nodev,		/*7*/
E 2
D 6
	logioctl,	nodev,		nulldev,	0,
	logselect,	nodev,
E 6
I 6
	logioctl,	nodev,		nulldev,	NULL,
	logselect,	nodev,		NULL,
E 6
I 3
	comopen,	comclose,	comread,	comwrite,	/*8*/
	comioctl,	nodev,		comreset,	com_tty,
D 6
	ttselect,	nodev,
D 4
	fdopen,		nulldev,	fdread,		fdwrite,	/*9*/
	nulldev,	nodev,		nulldev,	0,
E 4
I 4
	fdopen,		fdclose,	fdread,		fdwrite,	/*9*/
	fdioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,
E 6
I 6
	ttselect,	nodev,		NULL,
	Fdopen,		fdclose,	fdread,		fdwrite,	/*9*/
	fdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		fdstrategy,
E 6
	wtopen,		wtclose,	wtread,		wtwrite,	/*A*/
D 6
	wtioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,
E 6
I 6
	wtioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		wtstrategy,
E 6
	xdopen,		xdclose,	xdread,		xdwrite,	/*B*/
D 6
	xdioctl,	nodev,		nulldev,	0,
E 4
	seltrue,	nodev,
E 6
I 6
	xdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		xdstrategy,
E 7
I 7
D 10
	{ cnopen,	cnclose,	cnread,		cnwrite,	/*0*/
	  cnioctl,	nullop,		nullop,		NULL,
D 8
	  ttselect,	enodev,		NULL },
E 8
I 8
	  cnselect,	enodev,		NULL },
E 8
	{ cttyopen,	nullop,		cttyread,	cttywrite,	/*1*/
	  cttyioctl,	nullop,		nullop,		NULL,
	  cttyselect,	enodev,		NULL },
I 9
        { nullop,       nullop,         mmrw,           mmrw,           /*2*/
          enodev,       nullop,         nullop,         NULL,
          mmselect,     enodev,         NULL },
E 9
	{ wdopen,	wdclose,	wdread,		wdwrite,	/*3*/
	  wdioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		wdstrategy },
	{ nullop,	nullop,		rawread,	rawwrite,	/*4*/
	  enodev,	enodev,		nullop,		NULL,
	  enodev,	enodev,		swstrategy },
	{ ptsopen,	ptsclose,	ptsread,	ptswrite,	/*5*/
	  ptyioctl,	ptsstop,	nullop,		pt_tty,
	  ttselect,	enodev,		NULL },
	{ ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*6*/
	  ptyioctl,	nullop,		nullop,		pt_tty,
	  ptcselect,	enodev,		NULL },
	{ logopen,	logclose,	logread,	enodev,		/*7*/
	  logioctl,	enodev,		nullop,		NULL,
	  logselect,	enodev,		NULL },
	{ comopen,	comclose,	comread,	comwrite,	/*8*/
	  comioctl,	enodev,		comreset,	com_tty,
	  ttselect,	enodev,		NULL },
	{ Fdopen,	fdclose,	fdread,		fdwrite,	/*9*/
	  fdioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		fdstrategy },
	{ wtopen,	wtclose,	wtread,		wtwrite,	/*A*/
	  wtioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		wtstrategy },
	{ xdopen,	xdclose,	xdread,		xdwrite,	/*B*/
	  xdioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		xdstrategy },
I 8
	{ pcopen,	pcclose,	pcread,		pcwrite,	/*C*/
	  pcioctl,	nullop,		nullop,		&pccons,
	  ttselect,	enodev,		NULL },
E 10
I 10
	cdev_cn_init(1,cn),		/* 0: virtual console */
	cdev_ctty_init(1,ctty),		/* 1: controlling terminal */
	cdev_mm_init(1,mm),		/* 2: /dev/{null,mem,kmem,...} */
	cdev_disk_init(NWD,wd),		/* 3: st506/rll/esdi/ide disk */
	cdev_swap_init(1,sw),		/* 4: /dev/drum (swap pseudo-device) */
	cdev_tty_init(NPTY,pts),	/* 5: pseudo-tty slave */
	cdev_ptc_init(NPTY,ptc),	/* 6: pseudo-tty master */
	cdev_log_init(1,log),		/* 7: /dev/klog */
	cdev_tty_init(NCOM,com),	/* 8: serial communications ports */
	cdev_disk_init(NFD,Fd),		/* 9: floppy disk */
	cdev_tape_init(NWT,wt),		/* 10: QIC-24/60/120/150 cartridge tape */
	cdev_disk_init(NXD,xd),		/* 11: temp alt st506/rll/esdi/ide disk */
	cdev_pc_init(1,pc),		/* 12: real console */
	cdev_notdef(),			/* 13 */
	cdev_bpf_init(NBPFILTER,bpf),	/* 14: berkeley packet filter */
E 10
E 8
E 7
E 6
E 3
D 2
	enpr_open,	enpr_close,	enpr_read,	enpr_write,	/*16*/
	enpr_ioctl,	nodev,		nulldev,	0,
	nodev,		nodev,		
	nodev,		nodev,		nodev,		nodev,		/*17*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
	dropen,		drclose,	drread,		drwrite,	/*18*/
	drioctl,	nodev,		drreset,	0,
	nodev,		nodev,
	nodev,		nodev,		nodev,		nodev,		/*19*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
/* 20-30 are reserved for local use */
	ikopen,		ikclose,	ikread,		ikwrite,	/*20*/
	ikioctl,	nodev,		nulldev,	0,
	nodev,		nodev,
E 2
};
I 10

E 10
int	nchrdev = sizeof (cdevsw) / sizeof (cdevsw[0]);

D 2
int	mem_no = 3; 	/* major device number of memory special file */
E 2
I 2
int	mem_no = 2; 	/* major device number of memory special file */
E 2

/*
 * Swapdev is a fake device implemented
 * in sw.c used only internally to get to swstrategy.
 * It cannot be provided to the users, because the
 * swstrategy routine munches the b_dev and b_blkno entries
 * before calling the appropriate driver.  This would horribly
 * confuse, e.g. the hashing routines. Instead, /dev/drum is
 * provided as a character (raw) device.
 */
D 2
dev_t	swapdev = makedev(4, 0);
E 2
I 2
dev_t	swapdev = makedev(1, 0);
I 14

/*
 * Routine that identifies /dev/mem and /dev/kmem.
 *
 * A minimal stub routine can always return 0.
 */
iskmemdev(dev)
	dev_t dev;
{

	return (major(dev) == 2 && (minor(dev) == 0 || minor(dev) == 1));
}

iszerodev(dev)
	dev_t dev;
{
	return (major(dev) == 2 && minor(dev) == 12);
}
E 14
E 2
E 1
