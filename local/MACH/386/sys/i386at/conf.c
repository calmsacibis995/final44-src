/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	conf.c,v $
 * Revision 1.9.1.12  91/05/03  16:05:54  rvb
 * 	adaptec scsi will be block major 3, character major 23, just like
 * 	the iPSC2 sd (=== scsi).
 * 	[91/05/03            rvb]
 * 
 * Revision 1.9.1.11  91/03/29  17:38:17  rvb
 * 	Fixed TTYLOC support.
 * 
 * Revision 1.9.1.10  91/03/28  08:45:27  rvb
 * 	Added aha support.
 * 	[91/03/25            rvb]
 * 
 * Revision 1.9.1.9  91/01/06  22:12:52  rvb
 * 	Added entry points for mach_cfs driver.
 * 	[90/05/23            dcs]
 * 
 * Revision 1.9.1.8  90/11/27  13:41:43  rvb
 * 	Let fd & hd & wt have close routines defined, to be
 * 	more compatible with Mt.xinu.  Besides, there are close
 * 	routines defined in the drivers already.
 * 	[90/11/09            rvb]
 * 
 * Revision 1.9.1.7  90/09/18  08:38:58  rvb
 * 	Add log device
 * 	[90/09/08            rvb]
 * 
 * Revision 1.9.1.6  90/08/25  15:43:11  rvb
 * 	Added parallel port printer driver.
 * 	And reserve majors for new devices.
 * 	[90/08/14            mg32]
 * 
 * Revision 1.9.1.5  90/07/10  11:43:17  rvb
 * 	Add comstop()
 * 	[90/06/26            rvb]
 * 
 * Revision 1.9.1.4  90/05/14  13:21:03  rvb
 * 	Added evc; made mouse its own device. [lance]
 * 	Add cmupty device
 * 	[90/05/01            rvb]
 * 
 * Revision 1.9.1.3  90/03/28  08:30:55  rvb
 * 	Add ioplmmap to map 0x0a0000 - 0x100000
 * 	[90/03/25            rvb]
 * 
 * Revision 1.9.1.2  90/02/28  15:49:20  rvb
 * 	Fix spacing in kdmmap declaration.
 * 	[90/02/28            rvb]
 * 
 * Revision 1.9.1.1  90/02/01  13:36:58  rvb
 * 	Add iopl device.
 * 	Temporary (??) vga implementation
 * 	[90/02/01            rvb]
 * 
 * Revision 1.9  89/09/25  12:26:28  rvb
 * 	Replace qt with wt
 * 	[89/09/23            rvb]
 * 
 * Revision 1.8  89/09/20  17:27:28  rvb
 * 	Support for Olivetti ln and ec.
 * 	[89/09/20            rvb]
 * 
 * Revision 1.7  89/09/09  15:21:34  rvb
 * 	Make devices configurable.
 * 	[89/09/09            rvb]
 * 
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 	[89/07/11            rvb]
 * 
 * Revision 1.6  89/09/05  20:41:45  jsb
 * 	Added Mach time device at #14.
 * 	[89/09/05  19:16:01  jsb]
 * 
 * Revision 1.5  89/07/17  10:40:18  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 
 * Revision 1.4  89/03/09  20:05:20  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:36:24  gm0w
 * 	Changes for cleanup.
 * 
 */
 
#include <vice.h>
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)conf.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/conf.h>

int	nulldev();
int	nodev();

int	timeopen();
int	timeclose();
int	timemap();

int	ioplopen(), ioplclose();
int	ioplmmap();
 
#include "hd.h"
#if	NHD > 0
int	hdopen(), hdclose(), hdstrategy(), hdread(), hdwrite(), hddump(), hdioctl(), hdsize();
#else	NHD > 0
#define	hdopen		nulldev
#define	hdclose		nulldev
#define	hdstrategy	nulldev
#define	hdread		nulldev
#define	hdwrite		nulldev
#define	hddump		nulldev
#define	hdioctl		nulldev
#define	hdsize		nulldev
#endif	NHD > 0

#include "aha.h"
#if	NAHA > 0
int	ahaioctl(), ahaopen(), ahastrategy(), aharead(), ahawrite(), ahaioctl();
#else	NAHA > 0
#define	ahaioctl	nulldev
#define	ahaopen		nulldev
#define	ahastrategy	nulldev
#define	aharead		nulldev
#define	ahawrite	nulldev
#endif	NAHA > 0
#define	ahadump		nulldev
#define	ahasize		nulldev

#include "fd.h"
#if	NFD > 0
int	fdopen(), fdclose(), fdstrategy(), fdread(), fdwrite(), fddump(), fdioctl(), fdsize();
#else	NFD > 0
#define	fdopen		nulldev
#define	fdclose		nulldev
#define	fdstrategy	nulldev
#define	fdread		nulldev
#define	fdwrite		nulldev
#define	fddump		nulldev
#define	fdioctl		nulldev
#define	fdsize		nulldev
#endif	NFD > 0

#include "wt.h"
#if	NWT > 0
int	wtopen(), wtclose(), wtstrategy(), wtread(), wtwrite(), wtdump(), wtioctl(), wtsize();
#else	NQT > 0
#define	wtopen		nulldev
#define	wtclose		nulldev
#define	wtread		nulldev
#define	wtwrite		nulldev
#define	wtioctl		nulldev
#define	wtstrategy	nulldev
#define	wtdump		nulldev
#define	wtsize		nulldev
#endif	NQT > 0

#include "ln.h"
#if NLN > 0
int lnopen(), lnclose(), lnioctl(), lnselect();
#else NLN > 0
#define lnopen    nodev
#define lnclose   nodev
#define lnioctl   nodev
#define lnselect  nodev
#endif NLN > 0

#include "ec.h"
#if NEC > 0
int ecopen(), ecclose(), ecioctl();
#else NEC > 0
#define ecopen    nodev
#define ecclose   nodev
#define ecioctl   nodev
#endif NEC > 0

struct bdevsw	bdevsw[] =
{
	{ hdopen,	hdclose,	hdstrategy,	hddump,		/*0*/
	  hdsize,	0 },
	{ fdopen,	fdclose,	fdstrategy,	fddump,		/*1*/
	  fdsize,	0 },
	{ wtopen,	wtclose,	wtstrategy,	wtdump,		/*2*/
	  wtsize,	0 },
	{ ahaopen,	nulldev,	ahastrategy,	ahadump,	/*3*/
	  hdsize,	0 },
};
int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

int	logopen(),logclose(),logread(),logioctl(),logselect();

int	kdopen(), kdclose(), kdread(), kdwrite(), kdioctl();
int	kdmmap();

extern struct tty kd_tty[];
int	ncons = 1;
#define kdntty	(&ncons)

int	kbdinit(), kbdopen(), kbdclose(), kbdioctl(), kbdselect(), kbdread();

#include "com.h"
#if	NCOM > 0
int	comopen(), comclose(), comread(), comwrite(), comioctl(), comstop();
extern	struct	tty	com_tty[];
#else	NCOM > 0
#define comopen		nodev
#define comclose	nodev
#define comread		nodev
#define comwrite	nodev
#define comioctl	nodev
#define comstop		nodev
#define com_tty		0
#endif	NCOM > 0

#include "lpr.h"
#if	NLPR > 0
int	lpropen(), lprclose(), lprwrite(), lprioctl(), lprstop();
extern	struct	tty	lpr_tty[];
#else	NLPR > 0
#define lpropen		nodev
#define lprclose	nodev
#define lprwrite	nodev
#define lprioctl	nodev
#define lprstop		nodev
#define lpr_tty		0
#endif	NLPR > 0

#include "qd.h"
#if	NQD > 0
int	qdopen(), qdclose(), qdread(), qdwrite(), qdioctl();
extern	struct	tty	qd_tty[];
#else	NQD > 0
#define qdopen		nodev
#define qdclose		nodev
#define qdread		nodev
#define qdwrite		nodev
#define qdioctl		nodev
#define qd_tty		0
#endif	NQD > 0

int	cnopen(),cnclose(),cnread(),cnwrite(),cnioctl();
struct tty cons;
#if	VICE
struct	tty *cons_tp;
#endif	VICE

int	syopen(),syread(),sywrite(),syioctl(),syselect();

int 	mmread(),mmwrite();
#define mmselect	seltrue

#include <pty.h>
#if	NPTY > 0
int	ptsopen(),ptsclose(),ptsread(),ptswrite(),ptsstop();
int	ptcopen(),ptcclose(),ptcread(),ptcwrite(),ptcselect();
int	ptyioctl();
struct	tty pt_tty[];
int	npty;
#define ptsntty		(&npty)
#else
#define ptsopen		nodev
#define ptsclose	nodev
#define ptsread		nodev
#define ptswrite	nodev
#define ptcopen		nodev
#define ptcclose	nodev
#define ptcread		nodev
#define ptcwrite	nodev
#define ptyioctl	nodev
#define pt_tty		0
#define ptcselect	nodev
#define ptsstop		nulldev
#define ptsntty		0
#endif

#include <cmupty.h>
#if	NCMUPTY > 0
int	cmuptyopen(),cmuptyclose(),cmuptyread(),cmuptywrite(),cmuptyioctl();
int	cmuptycopen(),cmuptycclose(),cmuptycread(),cmuptycwrite(),cmuptycioctl();
int	cmuptycselect();
struct tty cmupty_tty[];
int	ncmupty;
#define cmuptyntty	(&ncmupty)
#else	NCMUPTY
#define cmuptyopen	nodev
#define cmuptyclose	nodev
#define cmuptyread	nodev
#define cmuptywrite	nodev
#define cmuptyioctl	nodev
#define cmuptycopen	nodev
#define cmuptycclose	nodev
#define cmuptycread	nodev
#define cmuptycwrite	nodev
#define cmuptycioctl	nodev
#define cmuptycselect	nodev
#define cmupty_tty	0
#define cmuptyntty	0
#endif	NCMUPTY

#include <mach_cfs.h>
#if	NMACH_CFS > 0
int	vcopen(), vcclose(), vcread(), vcwrite(), vcioctl(), vcselect();
#else	NMACH_CFS > 0
#define vcopen		nodev
#define vcclose		nodev
#define vcread		nodev
#define vcwrite		nodev
#define vcioctl		nodev
#define vcselect	nodev
#endif	NMACH_CFS > 0

#include "evc.h"
#if NEVC > 0
int evc1open(), evc1close(), evc1ioctl(), evc1mmap();
#else NEVC > 0
#define evc1open	nodev
#define evc1close	nodev
#define evc1ioctl	nodev
#define	evc1mmap	nodev
#endif NEVC > 0

#include "blit.h"
#if NBLIT > 0
int	blitopen(), blitclose(), blitioctl(), blitmmap();
#else
#define	blitopen	nodev
#define	blitclose	nodev
#define	blitioctl	nodev
#define	blitmmap	nodev
#endif

#include "mouse.h"
#if NMOUSE > 0
int	mouseinit(), mouseopen(), mouseclose(), mouseioctl(), mouseselect();
int	mouseread();
#else
#define	mouseinit	nodev
#define	mouseopen	nodev
#define	mouseclose	nodev
#define	mouseioctl	nodev
#define	mouseselect	nodev
#define	mouseread	nodev
#endif

int	logopen(),logclose(),logread(),logioctl(),logselect();

int	ttselect(), seltrue();

struct cdevsw	cdevsw[] =
{
	comopen,	comclose,	comread,	comwrite,	/*0*/
	comioctl,	comstop,	nulldev,	com_tty,
	ttselect,	nodev,

	kdopen,		kdclose,	kdread,		kdwrite,	/*1*/
	kdioctl,	nulldev,	nulldev,	kd_tty,
	ttselect,	kdmmap,

	syopen,		nulldev,	syread,		sywrite,	/*2*/
	syioctl,	nulldev,	nulldev,	0,
	syselect,	nodev,

	nulldev,	nulldev,	mmread,		mmwrite,	/*3*/
	nodev,		nulldev,	nulldev,	0,
	mmselect,	nodev,

	hdopen,		hdclose,	hdread,		hdwrite,	/*4*/
	hdioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,

	fdopen,		fdclose,	fdread,		fdwrite,	/*5*/
	fdioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,

	wtopen,		wtclose,	wtread,		wtwrite,	/*6*/
	wtioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,

 	blitopen,	blitclose,	nodev,		nodev,		/*7*/
 	blitioctl,	nodev,		nulldev,	0,
 	nodev,		blitmmap,

 	lnopen,		lnclose,	nodev,		nodev,		/*8*/
 	lnioctl,	nodev,		nodev,		0,
 	lnselect,	nodev,

	ptsopen,	ptsclose,	ptsread,	ptswrite,	/*9*/
	ptyioctl,	ptsstop,	nodev,		pt_tty,
	ttselect,	nodev,

	ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*10*/
	ptyioctl,	nulldev,	nodev,		pt_tty,
	ptcselect,	nodev,

	kbdopen,	kbdclose,	kbdread,	nodev,		/*11*/
	kbdioctl,	nodev,		nodev,		0,
	kbdselect,	nodev,

	mouseopen,	mouseclose,	mouseread,	nodev,		/*12*/
	mouseioctl,	nodev,		nodev,		0,
	mouseselect,	nodev,

	qdopen,		qdclose,	qdread,		qdwrite,	/*13*/
	qdioctl,	nulldev,	nulldev,	qd_tty,
	ttselect,	nodev,

 	timeopen,	timeclose,	nodev,		nodev,		/*14*/
 	nodev,		nodev,		nulldev,	0,
 	nodev,		timemap,

	ecopen,         ecclose,        nodev,          nodev,          /*15*/
	ecioctl,        nodev,          nodev,          0,
	nodev,          nodev,

	ioplopen,       ioplclose,      nodev,          nodev,          /*16*/
	nodev,          nodev,          nulldev,        0,
	nodev,          ioplmmap,

 	evc1open,	evc1close,	nodev,		nodev,		/*17*/
 	evc1ioctl,	nodev,		nulldev,	0,
 	nodev,		evc1mmap,

	cmuptyopen,	cmuptyclose,	cmuptyread,	cmuptywrite,	/*18*/
	cmuptyioctl,	nulldev,	nulldev,	cmupty_tty,
	ttselect,	nodev,

	cmuptycopen,	cmuptycclose,	cmuptycread,	cmuptycwrite,	/*19*/
	cmuptycioctl,	nodev,		nulldev,	0,
	cmuptycselect,	nodev,

	lpropen,	lprclose,	nodev,          lprwrite,	/*20*/
	lprioctl,	lprstop,	nulldev,	lpr_tty,
	ttselect,	nodev,

 	nodev,		nodev,		nodev,		nodev,		/*21*/
 	nodev,		nodev,		nulldev,	0,
 	nodev,		nodev,

	logopen,	logclose,	logread,	nodev,		/*22*/
	logioctl,	nodev,		nulldev,	0,
	logselect,	nodev,

	ahaopen,	nulldev,	aharead,	ahawrite,	/*23*/
	ahaioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,

	vcopen,		vcclose,	vcread,		vcwrite,	/*24*/
	vcioctl,	nodev,		nodev,		0,
  	vcselect,	nodev, 

 	nodev,		nodev,		nodev,		nodev,		/*25*/
 	nodev,		nodev,		nulldev,	0,
 	nodev,		nodev,

 	nodev,		nodev,		nodev,		nodev,		/*26*/
 	nodev,		nodev,		nulldev,	0,
 	nodev,		nodev,

 	nodev,		nodev,		nodev,		nodev,		/*27*/
 	nodev,		nodev,		nulldev,	0,
 	nodev,		nodev,

 	nodev,		nodev,		nodev,		nodev,		/*28*/
 	nodev,		nodev,		nulldev,	0,
 	nodev,		nodev,

 	nodev,		nodev,		nodev,		nodev,		/*29*/
 	nodev,		nodev,		nulldev,	0,
 	nodev,		nodev,

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
dev_t	swapdev = makedev(0, 4);


#define CS_TTYLOC 1
#if	CS_TTYLOC
int *nttysw[] =
{
    0,		/*  0 */
    kdntty,	/*  1 */
    0,		/*  2 */
    0,		/*  3 */
    0,		/*  4 */
    0,		/*  5 */
    0,		/*  6 */
    0,		/*  7 */
    0,		/*  8 */
    ptsntty,	/*  9 */
    0,		/* 10 */
    0,		/* 11 */
    0,		/* 12 */
    0,		/* 13 */
    0,		/* 14 */
    0,		/* 15 */
    0,		/* 16 */
    0,		/* 17 */
    cmuptyntty,	/* 18 */
};
int	ntty = sizeof (nttysw) / sizeof (nttysw[0]);

dev_t	sydev = makedev(2, 0);	/* device for indirect tty */
#endif	CS_TTYLOC
