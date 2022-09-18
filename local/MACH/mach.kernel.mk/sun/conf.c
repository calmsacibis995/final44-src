/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	conf.c,v $
 * Revision 2.11  92/02/06  00:26:28  mja
 * 	Added device for file reference tracing.
 * 	[92/01/03            lily]
 * 
 * Revision 2.10  92/02/04  21:15:14  mja
 * 	Added taac device at major 62.
 * 	[91/11/19            berman]
 * 
 * Revision 2.9  90/12/17  17:16:27  berman
 * 	Added cgthree, cgsix, cgeight, fd, audio, openprom, sg,
 * 	xd, st, rd, ns, and mcp devices.
 * 	[90/07/17            berman]
 * 
 * Revision 2.8  90/08/10  10:21:26  mrt
 * 	Added support for cab driver.
 * 	[90/08/10            rds]
 * 
 * Revision 2.7  90/07/03  16:47:43  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:13:45  mrt]
 * 
 * Revision 2.6  89/09/06  11:02:52  jsb
 * 	Added Mach time device at #40.
 * 	[89/09/06  11:00:24  jsb]
 * 
 * Revision 2.5  89/03/09  21:29:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:27:18  gm0w
 * 	Removed include of text.h as it no longer exists.
 * 	[89/02/18            mrt]
 * 
 * 	Removed else legs of MACH and CMU conditionals and fixed 
 * 	includes as part of kernel cleanup.
 * 	[89/02/08            jjc]
 * 
 * Revision 2.3  89/01/18  01:09:58  jsb
 * 	Add #else branches in declaration of cdevsw for CMUCS and VICE so that
 * 	device numbers don't mysteriously shift when these are turned off!
 * 	[89/01/17  10:51:38  jsb]
 * 
 *
 * 26-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added missing winmmap() entry to cdevsw[] #15.
 *	[ V5.1(XF23) ]
 *
 * 19-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Add definition for indirect terminal device number variable;
 *	CS_TTYLOC => CMUCS.
 *	[ V5.1(XF23) ]
 *
 * 14-Mar-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added cgfour device.
 *
 * 17-Nov-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added fpa device with major device number 38 instead of 34
 *	since Vice /dev/fs{0,1,2} use 34 already.
 *
 * 04-Aug-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Correct nttysw[] initialization to include CMU ptys.
 *	[ V5.1(XF15) ]
 *
 * 15-Jul-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Add kernel log and CMU pesudo-terminal devices.
 *	[ V5.1(XF13) ]
 *
 *  9-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	No longer support swstrategy, swread and swwrite.
 *
 * 15-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Vice support.
 *
 *  7-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in CMUCS stuff.
 *
 *  4-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Commented out vnode.h
 */
#ifndef	lint
static	char sccsid[] = "@(#)conf.c 1.1 86/02/03 Copyr 1983 Sun Micro";
#endif

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */
#include <vice.h>
#include <sys/ioctl.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/acct.h>

extern int nulldev();
extern int nodev();

int	timeopen();
int	timeclose();
int	timemap();

int	logopen(),logclose(),logread(),logioctl(),logselect();

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
#include <ip.h>
#if	NIP > 0
extern int ipopen(), ipstrategy(), ipread(), ipwrite();
extern int ipdump(), ipioctl(), ipsize();
#else
#define ipopen		nodev
#define ipstrategy	nodev
#define ipread		nodev
#define ipwrite		nodev
#define ipdump		nodev
#define ipioctl		nodev
#define ipsize		0
#endif

#include <xy.h>
#if	NXY > 0
extern int xyopen(), xyclose(), xystrategy(), xyread(), xywrite();
extern int xydump(), xyioctl(), xysize();
#else
#define xyopen		nodev
#define xyclose		nodev
#define xystrategy	nodev
#define xyread		nodev
#define xywrite		nodev
#define xydump		nodev
#define xyioctl		nodev
#define xysize		0
#endif

#include <mt.h>
#if	NMT > 0
extern int tmopen(), tmclose(), tmstrategy(), tmread(), tmwrite();
extern int tmdump(), tmioctl();
#else
#define tmopen		nodev
#define tmclose		nodev
#define tmstrategy	nodev
#define tmread		nodev
#define tmwrite		nodev
#define tmdump		nodev
#define tmioctl		nodev
#endif

#include "xd.h"
#if NXD > 0
extern int xdopen(), xdstrategy(), xdread(), xdwrite();
extern int xddump(), xdioctl(), xdsize();
#else
#define	xdopen		nodev
#define	xdstrategy	nodev
#define	xdread		nodev
#define	xdwrite		nodev
#define	xddump		nodev
#define	xdioctl		nodev
#define	xdsize		0
#endif

#include <st.h>
#if	NST > 0
extern int stopen(), stclose(), stread(), stwrite(), stioctl(), ststrategy();
#else
#define stopen		nodev
#define stclose		nodev
#define stread		nodev
#define stwrite		nodev
#define stioctl		nodev
#define	ststrategy	nodev
#endif

#include "ns.h"
#if NNS > 0
extern int
	nsopen(),
	nsread(),
	nswrite(),
	nssize(),
	nsioctl(),
	nsstrategy();
#else
#define	nsopen		nodev
#define	nsclose		nodev
#define	nsread		nodev
#define	nswrite		nodev
#define	nssize		0
#define	nsioctl		nodev
#define	nsstrategy	nodev
#endif

#include "rd.h"
#if NRD > 0
extern int
	rdopen(),
	rdread(),
	rdwrite(),
	rdsize(),
	rdioctl(),
	rdstrategy();
#else
#define	rdopen		nodev
#define	rdclose		nodev
#define	rdread		nodev
#define	rdwrite		nodev
#define	rdsize		0
#define	rdioctl		nodev
#define	rdstrategy	nodev
#endif

#include <xt.h>
#if	NXT > 0
extern int xtopen(), xtclose(), xtstrategy(), xtread(), xtwrite(), xtioctl();
#else
#define xtopen		nodev
#define xtclose		nodev
#define xtstrategy	nodev
#define xtread		nodev
#define xtwrite		nodev
#define xtioctl		nodev
#endif

#include <ar.h>
#if	NAR > 0
extern int aropen(), arclose(), arstrategy(), arread(), arwrite(), arioctl();
#else
#define aropen		nodev
#define arclose		nodev
#define arstrategy	nodev
#define arread		nodev
#define arwrite		nodev
#define arioctl		nodev
#endif

#define NND	0
#if	NND > 0
extern int ndopen(), ndstrategy(), ndread(), ndwrite();
extern int nddump(), ndioctl(), ndsize();
#else
#define ndopen		nodev
#define ndstrategy	nodev
#define ndread		nodev
#define ndwrite		nodev
#define nddump		nodev
#define ndioctl		nodev
#define ndsize		0
#endif

#include <sd.h>
#if	NSD > 0
extern int sdopen(), sdclose(), sdstrategy(), sdread(), sdwrite();
extern int sddump(), sdioctl(), sdsize();
#else
#define sdopen		nodev
#define sdclose		nodev
#define sdstrategy	nodev
#define sdread		nodev
#define sdwrite		nodev
#define sddump		nodev
#define sdioctl		nodev
#define sdsize		0
#endif

#include <sf.h>
#if	NSF > 0
extern int sfopen(), sfclose(), sfstrategy(), sfread(), sfwrite();
extern int sfioctl(), sfsize();
#else
#define sfopen		nodev
#define sfclose		nodev
#define sfstrategy	nodev
#define sfread		nodev
#define sfwrite		nodev
#define sfioctl		nodev
#define sfsize		0
#endif

#include <fd.h>
#if NFD > 0
extern int fdopen(), fdclose(), fdread(), fdstrategy(), fdwrite();
extern int fddump(), fdioctl(), fdsize();
#else
#define fdopen		nodev
#define fdclose		nodev
#define fdstrategy	nodev
#define fdread		nodev
#define fdwrite		nodev
#define fddump		nodev
#define fdioctl		nodev
#define fdsize		0
#endif

#define swstrategy	nodev
#define swread		nodev
#define swwrite		nodev

struct bdevsw	bdevsw[] =
{
	{ ipopen,	nulldev,	ipstrategy,	ipdump,		/*0*/
	  ipsize,	0 },
	{ tmopen,	tmclose,	tmstrategy,	tmdump,		/*1*/
	  0,		B_TAPE },
	{ nodev,	nodev,		nodev,		nodev,		/*2*/
	  0,		B_TAPE },				/* was ar */
	{ xyopen,	xyclose,	xystrategy,	xydump,		/*3*/
	  xysize,	0 },
	{ nodev,	nodev,		swstrategy,	nodev,		/*4*/
	  0,		0 },
	{ ndopen,	nulldev,	ndstrategy,	nddump,		/*5*/
	  ndsize,	0 },
	{ nodev,	nodev,		nodev,		nodev,		/*6*/
	  0,		0 },
	{ sdopen,	sdclose,	sdstrategy,	sddump,		/*7*/
	  sdsize,	0 },
	{ xtopen,	xtclose,	xtstrategy,	nodev,		/*8*/
	  0,		B_TAPE },
	{ sfopen,	sfclose,	sfstrategy,	nodev,		/*9*/
	  sfsize,	0 },
	{ xdopen,	nulldev,	xdstrategy,	xddump,		/*10*/
	  xdsize,	0 },
	{ stopen,	stclose,	ststrategy,	nodev,		/*11*/
	  0,		B_TAPE },
	{ nsopen,	nodev,		nsstrategy,	nodev,		/*12*/
	  nssize,	0 },
	{ rdopen,	nodev,		rdstrategy,	nodev,		/*13*/
	  rdsize,	0 },
	{ fdopen,	fdclose,	fdstrategy,	fddump,		/*14*/
	  fdsize,	0 },
};
int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

extern int cnopen(), cnclose(), cnread(), cnwrite(), cnioctl(), cnselect();
extern struct tty cons;
#if	VICE
struct	tty *cons_tp;
#endif	VICE
int	ncons;
#define cnntty	(&ncons)

extern int conskbdopen(), conskbdclose(), conskbdread(), conskbdioctl();
extern int conskbdselect(), consfbopen(), consfbclose();
extern int consfbioctl(), consfbmmap();

#include <ms.h>
#if	NMS > 0
extern int consmsopen(), consmsclose(), consmsread();
extern int consmsselect(), consmsioctl();
#else
#define consmsopen	nodev
#define consmsclose	nodev
#define consmsread	nodev
#define consmsselect	nodev
#define consmsioctl	nodev
#endif

extern int syopen(), syread(), sywrite(), syioctl(), syselect();

extern int mmopen(), mmread(), mmwrite(), mmmmap();
#define mmselect	seltrue

#include <vp.h>
#if	NVP > 0
extern int vpopen(), vpclose(), vpwrite(), vpioctl();
#else
#define vpopen		nodev
#define vpclose		nodev
#define vpwrite		nodev
#define vpioctl		nodev
#endif

#include <vpc.h>
#if	NVPC > 0
extern int vpcopen(), vpcclose(), vpcwrite(), vpcioctl();
#else
#define vpcopen		nodev
#define vpcclose	nodev
#define vpcwrite	nodev
#define vpcioctl	nodev
#endif

#include <zs.h>
#if	NZS > 0
extern int zsopen(), zsclose(), zsread(), zswrite();
extern int zsioctl(), zsstop(), zsselect();
extern struct tty zs_tty[];
extern int	nzs;
#define zsntty	(&nzs)
#else
#define zsopen	nodev
#define zsclose	nodev
#define zsread	nodev
#define zswrite	nodev
#define zsioctl	nodev
#define zsstop	nodev
#define zs_tty	0
#define zsselect nodev
#define zsntty	0
#endif

#include <pty.h>
#if	NPTY > 0
extern int ptsopen(), ptsclose(), ptsread(), ptswrite(), ptsstop();
extern int ptcopen(), ptcclose(), ptcread(), ptcwrite(), ptcselect();
extern int ptyioctl();
extern struct tty pt_tty[];
extern int	npty;
#define ptsntty	(&npty)
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

#include <ropc.h>
#if	NROPC > 0
extern int ropcopen(), ropcmmap();
#else
#define ropcopen	nodev
#define ropcmmap	nodev
#endif

#include <mti.h>
#if	NMTI > 0
extern int mtiopen(), mticlose(), mtiread(), mtiwrite(), mtiioctl();
extern int mtiioctl(), mtistop(), mtireset(), mtiselect();
extern struct tty mti_tty[];
extern int	nmti;
#define mtintty	(&nmti)
#else
#define mtiopen		nodev
#define mticlose	nodev
#define mtiread		nodev
#define mtiwrite	nodev
#define mtiioctl	nodev
#define mtistop		nodev
#define mtireset	nulldev
#define mtiselect	nulldev
#define mti_tty	0
#define mtintty		0
#endif

#include "mcp.h"
#if NMCP > 0
extern struct streamtab mcpstab;
extern struct streamtab mcppstab;
#define mcptab          &mcpstab
#define mcpptab		&mcppstab
#else
#define mcptab          0
#define mcpptab		0
#endif

#include <cgone.h>
#if	NCGONE > 0
extern int cgoneopen(), cgonemmap(), cgoneioctl();
extern int cgoneclose();
#else
#define cgoneopen	nodev
#define cgonemmap	nodev
#define cgoneioctl	nodev
#define cgoneclose	nodev
#endif

#include <cgtwo.h>
#if	NCGTWO > 0
extern int cgtwoopen(), cgtwommap(), cgtwoioctl();
extern int cgtwoclose();
#else
#define cgtwoopen	nodev
#define cgtwommap	nodev
#define cgtwoioctl	nodev
#define cgtwoclose	nodev
#endif

#include "cgthree.h"
#if NCGTHREE > 0
extern int cgthreeopen(), cgthreeclose(), cgthreemmap(), cgthreeioctl();
#else
#define	cgthreeopen	nodev
#define	cgthreeclose	nodev
#define	cgthreeioctl	nodev
#define	cgthreemmap	nodev
#endif

#include <cgfour.h>
#if	NCGFOUR > 0
extern int cgfouropen(), cgfourclose(), cgfourioctl(), cgfourmmap();
#else
#define cgfouropen	nodev
#define cgfourclose	nodev
#define cgfourioctl	nodev
#define cgfourmmap	nodev
#endif

#include <cgsix.h>
#if NCGSIX > 0
extern int cgsixopen(), cgsixclose(), cgsixmmap(), cgsixioctl();
#else
#define cgsixopen       nodev
#define cgsixclose      nodev
#define cgsixioctl      nodev
#define cgsixmmap       nodev
#endif

#include "cgeight.h"
#if NCGEIGHT > 0
extern int cgeightopen(), cgeightclose(), cgeightmmap(), cgeightioctl();
#else
#define	cgeightopen	nodev
#define	cgeightclose	nodev
#define	cgeightioctl	nodev
#define	cgeightmmap	nodev
#endif

#include <gpone.h>
#if	NGPONE > 0
extern int gponeopen(), gponemmap(), gponeioctl();
extern int gponeclose();
#else
#define gponeopen	nodev
#define gponemmap	nodev
#define gponeioctl	nodev
#define gponeclose	nodev
#endif

#include <taac.h>
#if NTAAC > 0
extern int taacopen(), taacmmap();
extern int taacclose(), taacioctl(), taacread(), taacwrite();
#else
#define taacopen 	nodev
#define taacmmap 	nodev
#define taacclose 	nodev
#define taacioctl 	nodev
#define taacread 	nodev
#define taacwrite 	nodev
#endif

#include <win.h>
#if	NWIN > 0
extern int winopen(), winclose(), winread(), winioctl(), winselect(), winmmap();
#else
#define winopen		nodev
#define winclose	nodev
#define winread		nodev
#define winioctl	nodev
#define winselect	nodev
#define winmmap		0
#endif

#include <sky.h>
#if	NSKY > 0
extern int skyopen(), skyclose(), skymmap();
#else
#define skyopen		nodev
#define skyclose	nodev
#define skymmap		nodev
#endif

#include <pi.h>
#if	NPI > 0
extern int piopen(), piclose(), piread(), piioctl();
extern struct tty pitty[];
extern int	npi;
#define pintty	(&npi)
#else
#define piopen	nodev
#define piclose nodev
#define piread	nodev
#define piioctl nodev
#define pitty	0
#define pintty	0
#endif

#include <bwone.h>
#if	NBWONE > 0
extern int bwoneopen(), bwonemmap(), bwoneioctl();
extern int bwoneclose();
#else
#define bwoneopen	nodev
#define bwonemmap	nodev
#define bwoneioctl	nodev
#define bwoneclose	nodev
#endif

#include <bwtwo.h>
#if	NBWTWO > 0
extern int bwtwoopen(), bwtwommap(), bwtwoioctl();
extern int bwtwoclose();
#else
#define bwtwoopen	nodev
#define bwtwommap	nodev
#define bwtwoioctl	nodev
#define bwtwoclose	nodev
#endif

#include <des.h>
#if	NDES > 0
extern int desopen(), desclose(), desioctl();
#else
#define desopen		nodev
#define desclose	nodev
#define desioctl	nodev
#endif

#include <fpa.h>
#if	NFPA > 0
extern int fpaopen(), fpaclose(), fpaioctl();
#else
#define fpaopen		nodev
#define fpaclose	nodev
#define fpaioctl	nodev
#endif

#if	VICE
#include <vicefs.h>
#if	NVICEFS > 0
int	rmtopen(), rmtclose(), rmtread(), rmtwrite(), rmtselect();
#else
#define		rmtopen	nodev
#define		rmtclose	nodev
#define		rmtread	nodev
#define		rmtwrite	nodev
#define		rmtselect	nodev
#endif
int	rmtopen(), rmtclose(), rmtread(), rmtwrite(), rmtselect();
#endif	VICE

#ifdef	sun4c
#include "audio.h"
#else
#define	NAUDIO	0
#endif	sun4c
#if NAUDIO > 0
int audioopen(), audioclose(), audioread(), audiowrite(), audioioctl();
#else
#define audioopen	nodev
#define audioclose	nodev
#define audioread	nodev
#define audiowrite	nodev
#define audioioctl	nodev
#endif

#ifdef  OPENPROMS
#include "openeepr.h"
#else
#define NOPENEEPR 0
#endif
#if NOPENEEPR > 0
extern int opromopen(), opromioctl();
#else
#define opromopen	nodev
#define opromioctl	nodev
#endif

#if	defined(sun4c) || defined(NEWSCSI)
#include "sg.h"
#else	defined(sun4c) || defined(NEWSCSI)
#define	NSG 0
#endif	defined(sun4c) || defined(NEWSCSI)
#if	NSG > 0
int sgopen(), sgclose(), sgioctl(), sgread(), sgwrite();
#else	NSG > 0
#define	sgopen	nodev
#define	sgclose	nodev
#define	sgioctl	nodev
#define	sgread	nodev
#define	sgwrite	nodev
#endif

/*
 * Nectar cab driver.
 */
#include "cab.h"
#if NCAB > 0
extern int cabopen(), cabclose(), cabioctl(), cabmmap();
#else
#define cabopen         nodev
#define cabclose        nodev
#define cabioctl        nodev
#define cabmmap         nodev
#endif

#include <dfstrace.h>
#if DFSTRACE > 0
int dfstraceread(), dfstraceioctl(), dfstraceselect();
#else  DFSTRACE
#define dfstraceread    nodev
#define dfstraceioctl   nodev
#define dfstraceselect  nodev
#endif DFSTRACE

extern int ttselect(), seltrue();

struct cdevsw	cdevsw[] =
{
    {
	cnopen,		cnclose,	cnread,		cnwrite,	/*0*/
	cnioctl,	nulldev,	nulldev,	&cons,
	cnselect,	0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*1*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	syopen,		nulldev,	syread,		sywrite,	/*2*/
	syioctl,	nulldev,	nulldev,	0,
	syselect,	0,
    },
    {
	mmopen,		nulldev,	mmread,		mmwrite,	/*3*/
	nodev,		nulldev,	nulldev,	0,
	mmselect,	mmmmap,
    },
    {
	ipopen,		nulldev,	ipread,		ipwrite,	/*4*/
	ipioctl,	nodev,		nulldev,	0,
	seltrue,	0,
    },
    {
	tmopen,		tmclose,	tmread,		tmwrite,	/*5*/
	tmioctl,	nodev,		nulldev,	0,
	seltrue,	0,
    },
    {
	vpopen,		vpclose,	nodev,		vpwrite,	/*6*/
	vpioctl,	nulldev,	nulldev,	0,
	seltrue,	0,
    },
    {
	nulldev,	nulldev,	swread,		swwrite,	/*7*/
	nodev,		nodev,		nulldev,	0,
	nodev,		0,
    },
    {
	aropen,		arclose,	arread,		arwrite,	/*8*/
	arioctl,	nodev,		nulldev,	0,
	seltrue,	0,
    },
    {
	xyopen,		xyclose,	xyread,		xywrite,	/*9*/
	xyioctl,	nodev,		nulldev,	0,
	seltrue,	0,
    },
    {
	mtiopen,	mticlose,	mtiread,	mtiwrite,	/*10*/
	mtiioctl,	mtistop,	mtireset,	mti_tty,
	mtiselect,	0,
    },
    {
	desopen,	desclose,	nodev,		nodev,		/*11*/
	desioctl,	nodev,		nulldev,	0,
	nodev,		0,
    },
    {
	zsopen,		zsclose,	zsread,		zswrite,	/*12*/
	zsioctl,	zsstop,		nulldev,	zs_tty,
	zsselect,	0,
    },
    {
	consmsopen,	consmsclose,	consmsread,	nodev,		/*13*/
	consmsioctl,	nodev,		nodev,		0,
	consmsselect,	0,
    },
    {
	cgoneopen,	cgoneclose,	nodev,		nodev,		/*14*/
	cgoneioctl,	nodev,		nodev,		0,
	seltrue,	cgonemmap,
    },
    {
	winopen,	winclose,	winread,	nodev,		/*15*/
	winioctl,	nodev,		nodev,		0,
	winselect,	winmmap,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*16*/
	nodev,		nodev,		nodev,		0,
	seltrue,	0,
    },
    {
	sdopen,		sdclose,	sdread,		sdwrite,	/*17*/
	sdioctl,	nodev,		nulldev,	0,
	seltrue,	0,
    },
    {
	stopen,		stclose,	stread,		stwrite,	/*18*/
	stioctl,	nodev,		nodev,		0,
	nodev,		0,
    },
    {
	ndopen,		nulldev,	ndread,		ndwrite,	/*19*/
	ndioctl,	nodev,		nulldev,	0,
	seltrue,	0,
    },
    {
	ptsopen,	ptsclose,	ptsread,	ptswrite,	/*20*/
	ptyioctl,	ptsstop,	nodev,		pt_tty,
	ttselect,	0,
    },
    {
	ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*21*/
	ptyioctl,	nulldev,	nodev,		pt_tty,
	ptcselect,	0,
    },
    {
	consfbopen,	consfbclose,	nodev,		nodev,		/*22*/
	consfbioctl,	nodev,		nodev,		0,
	nodev,		consfbmmap,
    },
    {
	ropcopen,	nulldev,	nodev,		nodev,		/*23*/
	nodev,		nodev,		nulldev,	0,
	nodev,		ropcmmap,
    },
    {
	skyopen,	skyclose,	nodev,		nodev,		/*24*/
	nodev,		nodev,		nulldev,	0,
	nodev,		skymmap,
    },
    {
	piopen,		piclose,	piread,		nodev,		/*25*/
	piioctl,	nodev,		nodev,		pitty,
	ttselect,	0,
    },
    {
	bwoneopen,	bwoneclose,	nodev,		nodev,		/*26*/
	bwoneioctl,	nodev,		nodev,		0,
	seltrue,	bwonemmap,
    },
    {
	bwtwoopen,	bwtwoclose,	nodev,		nodev,		/*27*/
	bwtwoioctl,	nodev,		nodev,		0,
	seltrue,	bwtwommap,
    },
    { 
	vpcopen,	vpcclose,	nodev,		vpcwrite,	/*28*/
	vpcioctl,	nulldev,	nulldev,	0,
	seltrue,	0,
    },
    {
	conskbdopen,	conskbdclose,	conskbdread,	nodev,		/*29*/
	conskbdioctl,	nulldev,	nulldev,	0,
	conskbdselect,	0,
    },
    {
	xtopen,		xtclose,	xtread,		xtwrite,	/*30*/
	xtioctl,	nodev,		nulldev,	0,
	seltrue,	0,
    },
    { 
	cgtwoopen,	cgtwoclose,	nodev,		nodev,		/*31*/
	cgtwoioctl,	nodev,		nodev,		0,
	seltrue,	cgtwommap,
    },
    { 
	gponeopen,	gponeclose,	nodev,		nodev,		/*32*/
	gponeioctl,	nodev,		nodev,		0,
	seltrue,	gponemmap,
    },
    {
	sfopen,		sfclose,	sfread,		sfwrite,	/*33*/
	sfioctl,	nodev,		nulldev,	0,
	seltrue,	0,
    },
#if	VICE
    {
	rmtopen,	rmtclose,	rmtread,	rmtwrite,	/*34*/
	nodev,		nodev,		nodev,		0,
  	rmtselect,	nodev,
    },
#else	VICE
    {
	nodev,		nodev,		nodev,		nodev,		/*34*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
#endif	VICE
	{ cmuptyopen,	cmuptyclose,	cmuptyread,	cmuptywrite,	/*35*/
	  cmuptyioctl,	nulldev,	nulldev,	cmupty_tty,
	  ttselect,	nodev },
	{ cmuptycopen,	cmuptycclose,	cmuptycread,	cmuptycwrite,	/*36*/
	  cmuptycioctl,	nodev,		nulldev,	0,
	  cmuptycselect,nodev }, 
	{ logopen,	logclose,	logread,	nodev,		/*37*/
	  logioctl,	nodev,		nulldev,	0,
	  logselect,	nodev },
    {	
	fpaopen,	fpaclose,	nodev,		nodev,		/*38*/
	fpaioctl,	nodev,		nodev,		0,
	nodev,		0,
    },
    {
	cgfouropen,	cgfourclose,	nodev,		nodev,		/*39*/
	cgfourioctl,	nodev,		nodev,		0,
	seltrue,	cgfourmmap,
    },
    {
	timeopen,	timeclose,	nodev,		nodev,		/*40*/
	nodev,		nodev,		nulldev,	0,
	nodev,		timemap,
    },
    {
	cabopen,	cabclose,	nodev,		nodev,		/*41*/
	cabioctl,	nodev,		nodev,		0,
	nodev,		cabmmap,
    },
    {
	xdopen,		nulldev,	xdread,		xdwrite,	/*42*/
	xdioctl,	nulldev,	seltrue,	0,
	0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*43*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*44*/
	nodev,		nodev,		nodev,		0,
	mcptab,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*45*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*46*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*47*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*48*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*49*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*50*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*51*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*52*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*53*/
	nodev,		nodev,		nodev,		0,
	nodev,		0,
    },
    {
	fdopen,		fdclose,	fdread,		fdwrite,	/*54*/
	fdioctl,	nulldev,	seltrue, 	0,
	0,
    },
    {
	cgthreeopen,	cgthreeclose,	nodev,		nodev,		/*55*/
	cgthreeioctl,	nodev,		nodev,		0,
	seltrue,	cgthreemmap,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*56*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*57*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*58*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*59*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*60*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*61*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	taacopen,	taacclose,	taacread,	taacwrite,	/*62*/
	taacioctl,	nodev,		nodev,		0,
	seltrue,	taacmmap,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*63*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	cgeightopen,	cgeightclose,	nodev,		nodev,		/*64*/
	cgeightioctl,	nodev,		nodev,		0,
	seltrue,	cgeightmmap,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*65*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*66*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    { 
        cgsixopen,      cgsixclose,     nodev,          nodev,          /*67*/
        cgsixioctl,     nodev,          nodev,          0,
        seltrue,        cgsixmmap,
    },
    {
	nodev,		nodev,		nodev,		nodev,		/*68*/
	nodev,		nodev,		nodev,		0,
	0,
    },
    {
	audioopen,	audioclose,	audioread,	audiowrite,	/*69*/
	audioioctl,	nulldev,	nulldev,	0,
	0,
    },
    {
	opromopen,	nulldev,	nodev,		nodev,		/*70*/
	opromioctl,	nodev,		nodev,		0,
	0,
    },
    {
	sgopen,		sgclose,	sgread,		sgwrite,	/*71*/
	sgioctl,	nodev,		nodev,		0,
	0,
    },
    {
	nulldev,	nulldev,	dfstraceread,	nodev,		/*72*/
        dfstraceioctl,  nulldev,	nulldev,	0,
	dfstraceselect,	nodev,
    },
};
int	nchrdev = sizeof (cdevsw) / sizeof (cdevsw[0]);

int	*nttysw[] =
{
	cnntty,		/*  0 */
	0,		/*  1 */
	0,		/*  2 */
	0,		/*  3 */
	0,		/*  4 */
	0,		/*  5 */
	0,		/*  6 */
	0,		/*  7 */
	0,		/*  8 */
	0,		/*  9 */
	mtintty,	/* 10 */
	0,		/* 11 */
	zsntty,		/* 12 */
	0,		/* 13 */
	0,		/* 14 */
	0,		/* 15 */
	0,		/* 16 */
	0,		/* 17 */
	0,		/* 18 */
	0,		/* 19 */
	ptsntty,	/* 20 */
	0,		/* 21 */
	0,		/* 22 */
	0,		/* 23 */
	0,		/* 24 */
	pintty,		/* 25 */
	0,		/* 26 */
	0,		/* 27 */
	0,		/* 28 */
	0,		/* 29 */
	0,		/* 30 */
	0,		/* 31 */
	0,		/* 32 */
	0,		/* 33 */
	0,		/* 34 */
	cmuptyntty,	/* 35 */
};
int	ntty = sizeof(nttysw) / sizeof(nttysw[0]);

dev_t	sydev = makedev(2, 0);	/* device number for indirect tty */

int	mem_no = 3;	/* major device number of memory special file */

/*
 * Swapdev is a fake device implemented
 * in sw.c used only internally to get to swstrategy.
 * It cannot be provided to the users, because the
 * swstrategy routine munches the b_dev and b_blkno entries
 * before calling the appropriate driver.  This would horribly
 * confuse, e.g. the hashing routines. Instead, /dev/drum is
 * provided as a character (raw) device.
 */
dev_t swapdev = makedev(4, 0);
struct vnode *swapdev_vp;
