h21565
s 00068/00068/00199
d D 7.9 91/05/08 17:45:38 karels 20 19
c finish updates, put {} around individual entries
e
s 00122/00122/00145
d D 7.8 91/02/24 14:37:29 mckusick 19 18
c nodev => enodev or enxio as appropriate; nulldev => nullop
e
s 00006/00006/00261
d D 7.7 90/12/16 16:45:59 bostic 18 17
c kernel reorg
e
s 00001/00011/00266
d D 7.6 90/06/28 22:06:53 bostic 17 16
c new copyright notice
e
s 00002/00002/00275
d D 7.5 89/05/09 20:52:18 mckusick 16 15
c merge in vnodes
e
s 00023/00005/00254
d D 7.4 89/05/01 10:12:39 bostic 15 14
c add hd drivers for HCX-9
e
s 00011/00006/00248
d D 7.3 88/06/29 17:30:01 bostic 14 13
c install approved copyright notice
e
s 00004/00007/00250
d D 7.2 88/05/26 09:03:41 karels 13 12
c include mp.h!, convert cy to rawread/write
e
s 00013/00001/00244
d D 7.1 88/05/21 18:35:01 karels 12 11
c bring up to revision 7 for tahoe release
e
s 00042/00044/00203
d D 1.11 88/05/14 12:15:33 karels 11 10
c raw read/write mods from torek (checked in for bostic)
e
s 00023/00028/00224
d D 1.10 87/11/17 21:04:40 sam 10 9
c install mpcc driver in place of bisync
e
s 00001/00001/00251
d D 1.9 87/03/28 15:58:27 karels 9 8
c add vdclose for cdev
e
s 00010/00008/00242
d D 1.8 87/03/26 18:04:33 karels 8 7
c add bdev ioctl
e
s 00003/00002/00247
d D 1.7 87/02/19 17:04:46 karels 7 6
c add vdioctl
e
s 00044/00007/00205
d D 1.6 86/11/25 16:41:58 sam 6 5
c add dr, ik, and enpr devices
e
s 00009/00035/00203
d D 1.5 86/07/16 08:26:21 sam 5 4
c purege nonexistent drivers; change disk names
e
s 00001/00001/00237
d D 1.4 86/01/26 14:18:08 sam 4 3
c cy.h -> yc.h
e
s 00000/00031/00238
d D 1.3 86/01/26 14:15:29 sam 3 2
c purge ps and efs entries for now
e
s 00014/00013/00255
d D 1.2 86/01/05 18:42:19 sam 2 1
c 1st working version
e
s 00268/00000/00000
d D 1.1 85/07/26 13:37:37 sam 1 0
c date and time created 85/07/26 13:37:37 by sam
e
u
U
t
T
I 1
D 2
/*	conf.c	1.3	85/04/25	*/
/*	conf.c	6.1	83/07/29	*/
E 2
I 2
D 12
/*	%M%	%I%	%E%	*/
E 12
I 12
/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
D 17
 * Redistribution and use in source and binary forms are permitted
D 14
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 14
I 14
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 14
 *
 *	%W% (Berkeley) %G%
 */
E 12
E 2

D 2
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/buf.h"
#include "../h/ioctl.h"
#include "../h/tty.h"
#include "../h/conf.h"
E 2
I 2
D 18
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "ioctl.h"
#include "tty.h"
#include "conf.h"
E 18
I 18
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/buf.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/conf.h"
E 18
E 2

D 11
int	nulldev();
int	nodev();
E 11
I 11
D 19
int nulldev(), nodev(), rawread(), rawwrite(), swstrategy();
E 19
I 19
int nullop(), enxio(), enodev(), rawread(), rawwrite(), swstrategy();
E 19
E 11

D 5
/*   #include "ud.h" */
#if NUD > 0
int	udopen(),udstrategy(),udread(),udwrite(),uddump(),udioctl(),udsize();
#else
#define	udopen		nodev
#define	udstrategy	nodev
#define	udread		nodev
#define	udwrite		nodev
#define	uddump		nodev
#define	udioctl		nodev
#define	udsize		0
#endif

#include "fsd.h"
E 5
I 5
#include "dk.h"
E 5
#if NVD > 0
D 7
int	vdopen(),vdstrategy(),vdread(),vdwrite(),vddump(),vdsize();
E 7
I 7
D 8
int	vdopen(),vdstrategy(),vdread(),vdwrite(),vdioctl(),vddump(),vdsize();
E 8
I 8
D 13
int	vdopen(),vdclose(),vdstrategy(),vdread(),vdwrite(),vdioctl();
E 13
I 13
int	vdopen(),vdclose(),vdstrategy(),vdioctl();
E 13
int	vddump(),vdsize();
E 8
E 7
#else
D 19
#define	vdopen		nodev
I 8
#define	vdclose		nodev
E 8
#define	vdstrategy	nodev
D 13
#define	vdread		nodev
#define	vdwrite		nodev
E 13
I 7
#define	vdioctl		nodev
E 7
#define	vddump		nodev
E 19
I 19
#define	vdopen		enxio
#define	vdclose		enxio
#define	vdstrategy	enxio
#define	vdioctl		enxio
#define	vddump		enxio
E 19
#define	vdsize		0
#endif

I 15
#include "hd.h"
#if NHD > 0
int	hdopen(),hdclose(),hdstrategy(),hdioctl();
int	hddump(),hdsize();
#else
D 19
#define	hdopen		nodev
#define	hdclose		nodev
#define	hdstrategy	nodev
#define	hdioctl		nodev
#define	hddump		nodev
E 19
I 19
#define	hdopen		enxio
#define	hdclose		enxio
#define	hdstrategy	enxio
#define	hdioctl		enxio
#define	hddump		enxio
E 19
#define	hdsize		0
#endif

E 15
D 5
#define	NXP	0
#if NXP > 0
int	xpopen(),xpstrategy(),xpread(),xpwrite(),xpdump(),xpioctl(),xpsize();
#else
#define	xpopen		nodev
#define	xpstrategy	nodev
#define	xpread		nodev
#define	xpwrite		nodev
#define	xpdump		nodev
#define	xpioctl		nodev
#define	xpsize		0
#endif

E 5
D 4
#include "cy.h"
E 4
I 4
#include "yc.h"
E 4
#if NCY > 0
D 11
int	cyopen(),cyclose(),cystrategy(),cyread(),cywrite(),cydump(),cyioctl(),cyreset();
E 11
I 11
D 13
int	cyopen(),cyclose(),cystrategy(),cyread(),cywrite(),cydump();
E 13
I 13
int	cyopen(),cyclose(),cystrategy(),cydump();
E 13
int	cyioctl(),cyreset();
E 11
#else
D 19
#define	cyopen		nodev
#define	cyclose		nodev
#define	cystrategy	nodev
D 13
#define	cyread		nodev
#define	cywrite		nodev
E 13
#define	cydump		nodev
#define	cyioctl		nodev
#define	cyreset		nulldev
E 19
I 19
#define	cyopen		enxio
#define	cyclose		enxio
#define	cystrategy	enxio
#define	cydump		enxio
#define	cyioctl		enxio
#define	cyreset		nullop
E 19
#endif

D 11
int	swstrategy(),swread(),swwrite();

E 11
struct bdevsw	bdevsw[] =
{
D 5
	{ udopen,	nulldev,	udstrategy,	uddump,		/*0*/
	  udsize,	0 },
E 5
I 5
D 19
	{ nodev,	nulldev,	nodev,		nodev,		/*0*/
D 8
	  0,		0 },
E 5
	{ vdopen,	nulldev,	vdstrategy,	vddump,		/*1*/
	  vdsize,	0 },
E 8
I 8
	  nodev,	0,		0 },
E 19
I 19
D 20
	{ enodev,	nullop,	enodev,		enodev,		/*0*/
E 20
I 20
	{ enodev,	nullop,		enodev,		enodev,		/*0*/
E 20
	  enodev,	0,		0 },
E 19
	{ vdopen,	vdclose,	vdstrategy,	vdioctl,	/*1*/
	  vddump,	vdsize,		0 },
E 8
D 5
	{ xpopen,	nulldev,	xpstrategy,	xpdump,		/*2*/
	  xpsize,	0 },
E 5
I 5
D 15
	{ nodev,	nulldev,	nodev,		nodev,		/*2*/
D 8
	  0,		0 },
E 5
	{ cyopen,	cyclose,	cystrategy,	cydump,		/*3*/
	  0,		B_TAPE },
E 8
I 8
	  nodev,	0,		0 },
E 15
I 15
	{ hdopen,	hdclose,	hdstrategy,	hdioctl,	/*2*/
	  hddump,	hdsize,		0 },
E 15
	{ cyopen,	cyclose,	cystrategy,	cyioctl,	/*3*/
	  cydump,	0,		B_TAPE },
E 8
D 19
	{ nodev,	nodev,		swstrategy,	nodev,		/*4*/
D 8
	  0,		0 },
E 8
I 8
	  nodev,	0,		0 },
E 19
I 19
	{ enodev,	enodev,		swstrategy,	enodev,		/*4*/
	  enodev,	0,		0 },
E 19
E 8
};
int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

int	cnopen(),cnclose(),cnread(),cnwrite(),cnioctl();
D 2
struct tty cons[];
E 2
I 2
extern	struct tty cons;
E 2

#include "vx.h"
#if NVX == 0
D 19
#define	vxopen	nodev
#define	vxclose	nodev
#define	vxread	nodev
#define	vxwrite	nodev
#define	vxioctl	nodev
#define	vxstop	nodev
#define	vxreset	nulldev
E 19
I 19
#define	vxopen	enxio
#define	vxclose	enxio
#define	vxread	enxio
#define	vxwrite	enxio
#define	vxioctl	enxio
#define	vxstop	enxio
#define	vxreset	nullop
E 19
#define	vx_tty	0
#else
int	vxopen(),vxclose(),vxread(),vxwrite(),vxioctl(),vxstop(),vxreset();
struct	tty vx_tty[];
#endif

D 20
int	syopen(),syread(),sywrite(),syioctl(),syselect();
E 20
I 20
int	cttyopen(),cttyread(),cttywrite(),cttyioctl(),cttyselect();
E 20

D 16
int 	mmread(),mmwrite();
E 16
I 16
int 	mmrw();
E 16
#define	mmselect	seltrue

#include "pty.h"
#if NPTY > 0
int	ptsopen(),ptsclose(),ptsread(),ptswrite(),ptsstop();
int	ptcopen(),ptcclose(),ptcread(),ptcwrite(),ptcselect();
int	ptyioctl();
struct	tty pt_tty[];
#else
D 19
#define ptsopen		nodev
#define ptsclose	nodev
#define ptsread		nodev
#define ptswrite	nodev
#define ptcopen		nodev
#define ptcclose	nodev
#define ptcread		nodev
#define ptcwrite	nodev
#define ptyioctl	nodev
E 19
I 19
#define ptsopen		enxio
#define ptsclose	enxio
#define ptsread		enxio
#define ptswrite	enxio
#define ptcopen		enxio
#define ptcclose	enxio
#define ptcread		enxio
#define ptcwrite	enxio
#define ptyioctl	enxio
E 19
#define	pt_tty		0
D 19
#define	ptcselect	nodev
#define	ptsstop		nulldev
E 19
I 19
#define	ptcselect	enxio
#define	ptsstop		nullop
E 19
#endif

I 13
#include "mp.h"
E 13
D 10
#include "vbsc.h"
#if NVBSC > 0
int	bscopen(), bscclose(), bscread(), bscwrite(), bscioctl();
int	bsmopen(),bsmclose(),bsmread(),bsmwrite(),bsmioctl();
int	bstopen(),bstclose(),bstread(),bstioctl();
E 10
I 10
#if NMP > 0
int	mpopen(), mpclose(), mpread(), mpwrite(), mpioctl(), mpstop();
int	mpdlopen(), mpdlclose(), mpdlwrite(), mpdlioctl();
extern	struct tty mp_tty[];
E 10
#else
D 10
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
E 10
I 10
D 19
#define	mpopen		nodev
#define	mpclose		nodev
#define	mpread		nodev
#define	mpwrite		nodev
#define	mpioctl		nodev
#define	mpstop		nodev
#define	mpdlopen	nodev
#define	mpdlclose	nodev
#define	mpdlwrite	nodev
#define	mpdlioctl	nodev
E 19
I 19
#define	mpopen		enxio
#define	mpclose		enxio
#define	mpread		enxio
#define	mpwrite		enxio
#define	mpioctl		enxio
#define	mpstop		enxio
#define	mpdlopen	enxio
#define	mpdlclose	enxio
#define	mpdlwrite	enxio
#define	mpdlioctl	enxio
E 19
#define	mp_tty		0
E 10
#endif

#if NII > 0
int	iiioctl(), iiclose(), iiopen();
#else
D 19
#define	iiopen	nodev
#define	iiclose	nodev
#define	iiioctl	nodev
E 19
I 19
#define	iiopen	enxio
#define	iiclose	enxio
#define	iiioctl	enxio
E 19
#endif

I 6
#include "enp.h"
#if NENP > 0
int	enpr_open(), enpr_close(), enpr_read(), enpr_write(), enpr_ioctl();
#else
D 19
#define enpr_open	nodev
#define enpr_close	nodev
#define enpr_read	nodev
#define enpr_write	nodev
#define enpr_ioctl	nodev
E 19
I 19
#define enpr_open	enxio
#define enpr_close	enxio
#define enpr_read	enxio
#define enpr_write	enxio
#define enpr_ioctl	enxio
E 19
#endif

#include "dr.h"
#if NDR > 0
int     dropen(),drclose(),drread(),drwrite(),drioctl(),drreset();
#else
D 19
#define dropen nodev
#define drclose nodev
#define drread nodev
#define drwrite nodev
#define drioctl nodev
#define drreset nodev
E 19
I 19
#define dropen enxio
#define drclose enxio
#define drread enxio
#define drwrite enxio
#define drioctl enxio
#define drreset enxio
E 19
#endif

#include "ik.h"
#if NIK > 0
int     ikopen(),ikclose(),ikread(),ikwrite(),ikioctl();
#else
D 19
#define ikopen nodev
#define ikclose nodev
#define ikread nodev
#define ikwrite nodev
#define ikioctl nodev
E 19
I 19
#define ikopen enxio
#define ikclose enxio
#define ikread enxio
#define ikwrite enxio
#define ikioctl enxio
E 19
#endif

E 6
D 3
#include "ps.h"
#if NPS > 0
int	psopen(),psclose(),psread(),pswrite(),psioctl(),psreset();
#else
#define psopen nodev
#define psclose nodev
#define psread nodev
#define pswrite nodev
#define psopen nodev
#define psioctl nodev
#define psreset nodev
#endif

#include "efs.h"
#if NEFS > 0
int	efsopen(),efsfgen(),efsread(),efswrite(),efsioctl(),efsreset();
#else
#define efsopen nodev
#define efsfgen nodev
#define efsread nodev
#define efswrite nodev
#define efsioctl nodev
#define efsreset nodev
#endif

E 3
I 2
int	logopen(),logclose(),logread(),logioctl(),logselect();

I 15
int	fdopen();

E 15
E 2
int	ttselect(), seltrue();

struct cdevsw	cdevsw[] =
{
D 20
	cnopen,		cnclose,	cnread,		cnwrite,	/*0*/
D 2
	cnioctl,	nulldev,	nulldev,	cons,
E 2
I 2
D 19
	cnioctl,	nulldev,	nulldev,	&cons,
E 2
D 11
	ttselect,	nodev,
E 11
I 11
	ttselect,	nodev,		NULL,
E 19
I 19
	cnioctl,	nullop,	nullop,	&cons,
	ttselect,	enodev,		NULL,
E 19
E 11
	vxopen,		vxclose,	vxread,		vxwrite,	/*1*/
	vxioctl,	vxstop,		vxreset,	vx_tty,
D 11
	ttselect,	nodev,
E 11
I 11
D 19
	ttselect,	nodev,		NULL,
E 11
	syopen,		nulldev,	syread,		sywrite,	/*2*/
D 11
	syioctl,	nulldev,	nulldev,	0,
	syselect,	nodev,
E 11
I 11
	syioctl,	nulldev,	nulldev,	NULL,
	syselect,	nodev,		NULL,
E 11
D 16
	nulldev,	nulldev,	mmread,		mmwrite,	/*3*/
E 16
I 16
	nulldev,	nulldev,	mmrw,		mmrw,		/*3*/
E 16
D 11
	nodev,		nulldev,	nulldev,	0,
	mmselect,	nodev,
E 11
I 11
	nodev,		nulldev,	nulldev,	NULL,
	mmselect,	nodev,		NULL,
E 11
D 5
	udopen,		nulldev,	udread,		udwrite,	/*4*/
	udioctl,	nodev,		nulldev,	0,
E 5
I 5
	nodev,		nulldev,	nodev,		nodev,		/*4*/
D 11
	nodev,		nodev,		nulldev,	0,
E 5
	seltrue,	nodev,
D 9
	vdopen,		nulldev,	vdread,		vdwrite,	/*5*/
E 9
I 9
	vdopen,		vdclose,	vdread,		vdwrite,	/*5*/
E 9
D 7
	nodev,		nodev,		nulldev,	0,
E 7
I 7
	vdioctl,	nodev,		nulldev,	0,
E 7
	seltrue,	nodev,
E 11
I 11
	nodev,		nodev,		nulldev,	NULL,
	seltrue,	nodev,		NULL,
E 19
I 19
	ttselect,	enodev,		NULL,
	syopen,		nullop,	syread,		sywrite,	/*2*/
	syioctl,	nullop,	nullop,	NULL,
	syselect,	enodev,		NULL,
	nullop,	nullop,	mmrw,		mmrw,		/*3*/
	enodev,		nullop,	nullop,	NULL,
	mmselect,	enodev,		NULL,
	enodev,		nullop,	enodev,		enodev,		/*4*/
	enodev,		enodev,		nullop,	NULL,
	seltrue,	enodev,		NULL,
E 19
	vdopen,		vdclose,	rawread,	rawwrite,	/*5*/
D 19
	vdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		vdstrategy,
E 19
I 19
	vdioctl,	enodev,		nullop,	NULL,
	seltrue,	enodev,		vdstrategy,
E 19
E 11
D 5
	xpopen,		nulldev,	xpread,		xpwrite,	/*6*/
	xpioctl,	nodev,		nulldev,	0,
E 5
I 5
D 15
	nodev,		nulldev,	nodev,		nodev,		/*6*/
D 11
	nodev,		nodev,		nulldev,	0,
E 5
	seltrue,	nodev,
E 11
I 11
	nodev,		nodev,		nulldev,	NULL,
	seltrue,	nodev,		NULL,
E 15
I 15
	hdopen,		hdclose,	rawread,	rawwrite,	/*6*/
D 19
	hdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		hdstrategy,
E 19
I 19
	hdioctl,	enodev,		nullop,	NULL,
	seltrue,	enodev,		hdstrategy,
E 19
E 15
E 11
D 13
	cyopen,		cyclose,	cyread,		cywrite,	/*7*/
E 13
I 13
	cyopen,		cyclose,	rawread,	rawwrite,	/*7*/
E 13
D 11
	cyioctl,	nodev,		cyreset,	0,
	seltrue,	nodev,
	nulldev,	nulldev,	swread,		swwrite,	/*8*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
E 11
I 11
D 19
	cyioctl,	nodev,		cyreset,	NULL,
D 14
	seltrue,	nodev,		NULL,
E 14
I 14
	seltrue,	nodev,		cystrategy,
E 14
	nulldev,	nulldev,	rawread,	rawwrite,	/*8*/
	nodev,		nodev,		nulldev,	NULL,
	nodev,		nodev,		swstrategy,
E 19
I 19
	cyioctl,	enodev,		cyreset,	NULL,
	seltrue,	enodev,		cystrategy,
	nullop,	nullop,	rawread,	rawwrite,	/*8*/
	enodev,		enodev,		nullop,	NULL,
	enodev,		enodev,		swstrategy,
E 19
E 11
	ptsopen,	ptsclose,	ptsread,	ptswrite,	/*9*/
D 19
	ptyioctl,	ptsstop,	nodev,		pt_tty,
D 11
	ttselect,	nodev,
E 11
I 11
	ttselect,	nodev,		NULL,
E 19
I 19
	ptyioctl,	ptsstop,	enodev,		pt_tty,
	ttselect,	enodev,		NULL,
E 19
E 11
	ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*10*/
D 19
	ptyioctl,	nulldev,	nodev,		pt_tty,
D 11
	ptcselect,	nodev,
E 11
I 11
	ptcselect,	nodev,		NULL,
E 11
D 10
	bscopen,	bscclose,	bscread,	bscwrite,	/*11*/
	bscioctl,	nodev,		nulldev,	0,
	nodev,		nodev,
	bsmopen,	bsmclose,	bsmread,	bsmwrite,	/*12*/
	bsmioctl,	nodev,		nulldev,	0,
	nodev,		nodev,
	bstopen,	bstclose,	bstread,	nodev,		/*13*/
	bstioctl,	nodev,		nulldev,	0,
E 10
I 10
	mpdlopen,	mpdlclose,	nodev,		mpdlwrite,	/*11*/
D 11
	mpdlioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,
E 11
I 11
	mpdlioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		NULL,
E 19
I 19
	ptyioctl,	nullop,	enodev,		pt_tty,
	ptcselect,	enodev,		NULL,
	mpdlopen,	mpdlclose,	enodev,		mpdlwrite,	/*11*/
	mpdlioctl,	enodev,		nullop,	NULL,
	seltrue,	enodev,		NULL,
E 19
E 11
	mpopen,		mpclose,	mpread,		mpwrite,	/*12*/
D 19
	mpioctl,	mpstop,		nulldev,	mp_tty,
D 11
	ttselect,	nodev,
E 11
I 11
	ttselect,	nodev,		NULL,
E 11
	nodev,		nodev,		nodev,		nodev,		/*13*/
D 11
	nodev,		nodev,		nulldev,	0,
E 10
	nodev,		nodev,
E 11
I 11
	nodev,		nodev,		nulldev,	NULL,
	nodev,		nodev,		NULL,
E 11
	iiopen,		iiclose,	nulldev,	nulldev,	/*14*/
D 11
	iiioctl,	nulldev,	nulldev,	0,
	seltrue,	nodev,
E 11
I 11
	iiioctl,	nulldev,	nulldev,	NULL,
	seltrue,	nodev,		NULL,
E 11
D 2
	nodev,		nodev,		nulldev,	nulldev,	/*15*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
E 2
I 2
	logopen,	logclose,	logread,	nodev,		/*15*/
D 11
	logioctl,	nodev,		nulldev,	0,
	logselect,	nodev,
E 11
I 11
	logioctl,	nodev,		nulldev,	NULL,
	logselect,	nodev,		NULL,
E 19
I 19
	mpioctl,	mpstop,		nullop,	mp_tty,
	ttselect,	enodev,		NULL,
	enodev,		enodev,		enodev,		enodev,		/*13*/
	enodev,		enodev,		nullop,	NULL,
	enodev,		enodev,		NULL,
	iiopen,		iiclose,	nullop,	nullop,	/*14*/
	iiioctl,	nullop,	nullop,	NULL,
	seltrue,	enodev,		NULL,
	logopen,	logclose,	logread,	enodev,		/*15*/
	logioctl,	enodev,		nullop,	NULL,
	logselect,	enodev,		NULL,
E 19
E 11
E 2
D 6
	nodev,		nodev,		nulldev,	nulldev,	/*16*/
E 6
I 6
	enpr_open,	enpr_close,	enpr_read,	enpr_write,	/*16*/
D 11
	enpr_ioctl,	nodev,		nulldev,	0,
	nodev,		nodev,		
E 11
I 11
D 19
	enpr_ioctl,	nodev,		nulldev,	NULL,
	nodev,		nodev,		NULL,
E 11
	nodev,		nodev,		nodev,		nodev,		/*17*/
E 6
D 11
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
E 11
I 11
	nodev,		nodev,		nulldev,	NULL,
	nodev,		nodev,		NULL,
E 19
I 19
	enpr_ioctl,	enodev,		nullop,	NULL,
	enodev,		enodev,		NULL,
	enodev,		enodev,		enodev,		enodev,		/*17*/
	enodev,		enodev,		nullop,	NULL,
	enodev,		enodev,		NULL,
E 19
E 11
D 6
	nodev,		nodev,		nulldev,	nulldev,	/*17*/
	nodev,		nodev,		nulldev,	0,
E 6
I 6
	dropen,		drclose,	drread,		drwrite,	/*18*/
D 11
	drioctl,	nodev,		drreset,	0,
E 6
	nodev,		nodev,
E 11
I 11
D 19
	drioctl,	nodev,		drreset,	NULL,
	nodev,		nodev,		NULL,
E 11
D 6
	nodev,		nodev,		nulldev,	nulldev,	/*18*/
E 6
I 6
	nodev,		nodev,		nodev,		nodev,		/*19*/
E 6
D 11
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
E 11
I 11
	nodev,		nodev,		nulldev,	NULL,
	nodev,		nodev,		NULL,
E 19
I 19
	drioctl,	enodev,		drreset,	NULL,
	enodev,		enodev,		NULL,
	enodev,		enodev,		enodev,		enodev,		/*19*/
	enodev,		enodev,		nullop,	NULL,
	enodev,		enodev,		NULL,
E 20
I 20
	{ cnopen,	cnclose,	cnread,		cnwrite,	/*0*/
	  cnioctl,	nullop,		nullop,		&cons,
	  ttselect,	enodev,		NULL },
	{ vxopen,	vxclose,	vxread,		vxwrite,	/*1*/
	  vxioctl,	vxstop,		vxreset,	vx_tty,
	  ttselect,	enodev,		NULL },
	{ cttyopen,	nullop,		cttyread,	cttywrite,	/*2*/
	  cttyioctl,	nullop,		nullop,		NULL,
	  cttyselect,	enodev,		NULL },
	{ nullop,	nullop,		mmrw,		mmrw,		/*3*/
	  enodev,	nullop,		nullop,		NULL,
	  mmselect,	enodev,		NULL },
	{ enodev,	nullop,		enodev,		enodev,		/*4*/
	  enodev,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		NULL },
	{ vdopen,	vdclose,	rawread,	rawwrite,	/*5*/
	  vdioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		vdstrategy },
	{ hdopen,	hdclose,	rawread,	rawwrite,	/*6*/
	  hdioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		hdstrategy },
	{ cyopen,	cyclose,	rawread,	rawwrite,	/*7*/
	  cyioctl,	enodev,		cyreset,	NULL,
	  seltrue,	enodev,		cystrategy },
	{ nullop,	nullop,		rawread,	rawwrite,	/*8*/
	  enodev,	enodev,		nullop,		NULL,
	  enodev,	enodev,		swstrategy },
	{ ptsopen,	ptsclose,	ptsread,	ptswrite,	/*9*/
	  ptyioctl,	ptsstop,	enodev,		pt_tty,
	  ttselect,	enodev,		NULL },
	{ ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*10*/
	  ptyioctl,	nullop,		enodev,		pt_tty,
	  ptcselect,	enodev,		NULL },
	{ mpdlopen,	mpdlclose,	enodev,		mpdlwrite,	/*11*/
	  mpdlioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		NULL },
	{ mpopen,	mpclose,	mpread,		mpwrite,	/*12*/
	  mpioctl,	mpstop,		nullop,		mp_tty,
	  ttselect,	enodev,		NULL },
	{ enodev,	enodev,		enodev,		enodev,		/*13*/
	  enodev,	enodev,		nullop,		NULL,
	  enodev,	enodev,		NULL },
	{ iiopen,	iiclose,	nullop,		nullop,		/*14*/
	  iiioctl,	nullop,		nullop,		NULL,
	  seltrue,	enodev,		NULL },
	{ logopen,	logclose,	logread,	enodev,		/*15*/
	  logioctl,	enodev,		nullop,		NULL,
	  logselect,	enodev,		NULL },
	{ enpr_open,	enpr_close,	enpr_read,	enpr_write,	/*16*/
	  enpr_ioctl,	enodev,		nullop,		NULL,
	  enodev,	enodev,		NULL },
	{ enodev,	enodev,		enodev,		enodev,		/*17*/
	  enodev,	enodev,		nullop,		NULL,
	  enodev,	enodev,		NULL },
	{ dropen,	drclose,	drread,		drwrite,	/*18*/
	  drioctl,	enodev,		drreset,	NULL,
	  enodev,	enodev,		NULL },
	{ fdopen,	enodev,		enodev,		enodev,		/*19*/
	  enodev,	enodev,		enodev,		NULL,
	  enodev,	enodev,		NULL },
E 20
E 19
E 11
D 6
	nodev,		nodev,		nulldev,	nulldev,	/*19*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
E 6
/* 20-30 are reserved for local use */
I 6
D 20
	ikopen,		ikclose,	ikread,		ikwrite,	/*20*/
D 11
	ikioctl,	nodev,		nulldev,	0,
	nodev,		nodev,
E 11
I 11
D 19
	ikioctl,	nodev,		nulldev,	NULL,
I 15
	nodev,		nodev,		NULL,
	fdopen,		nodev,		nodev,		nodev,		/*21*/
	nodev,		nodev,		nodev,		NULL,
E 15
	nodev,		nodev,		NULL,
E 19
I 19
	ikioctl,	enodev,		nullop,	NULL,
	enodev,		enodev,		NULL,
	fdopen,		enodev,		enodev,		enodev,		/*21*/
	enodev,		enodev,		enodev,		NULL,
	enodev,		enodev,		NULL,
E 20
I 20
	{ ikopen,	ikclose,	ikread,		ikwrite,	/*20*/
	  ikioctl,	enodev,		nullop,		NULL,
	  enodev,	enodev,		NULL },
	{ fdopen,	enodev,		enodev,		enodev,		/*21*/
	  enodev,	enodev,		enodev,		NULL,
	  enodev,	enodev,		NULL },
E 20
E 19
E 11
E 6
D 3
	psopen,		psclose,	psread,		pswrite,	/*20*/
	psioctl,	nodev,		psreset,	0,
	seltrue,	nodev,
	efsopen,	efsfgen,	efsread,	efswrite,	/*21*/
	efsioctl,	nodev,		efsreset,	0,
	seltrue,	nodev,
E 3
};
int	nchrdev = sizeof (cdevsw) / sizeof (cdevsw[0]);

int	mem_no = 3; 	/* major device number of memory special file */

/*
 * Swapdev is a fake device implemented
 * in sw.c used only internally to get to swstrategy.
 * It cannot be provided to the users, because the
 * swstrategy routine munches the b_dev and b_blkno entries
 * before calling the appropriate driver.  This would horribly
 * confuse, e.g. the hashing routines. Instead, /dev/drum is
 * provided as a character (raw) device.
 */
dev_t	swapdev = makedev(4, 0);
E 1
