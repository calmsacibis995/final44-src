/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	conf.c,v $
 * Revision 2.6  89/03/09  22:13:06  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:12:05  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/11/14  14:34:42  gm0w
 * 	Added CSNET DialupIP support.
 * 	[88/11/14            gm0w]
 * 
 * Revision 2.3  88/08/24  02:56:55  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:06:50  mwyoung]
 *
 * 19-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Add definition for indirect terminal device number variable;
 *	CS_TTYLOC => CS_GENERIC.
 *	[ V5.1(XF23) ]
 *
 *  2-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added qvmap.
 *
 *  6-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Add QDSS driver, reorganize virtual console.
 *
 * 24-Nov-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Moved dmz, crl and tms drivers to their standard locations
 *	and consequently relocated dsc and dzq drivers and dropped a
 *	few of the special purpose LEG driver placeholders.
 *	CS_GENERIC:  added to dmz entry.
 *	[ V5.1(F1) ]
 *
 * 10-Sep-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	NIP: Added DEANZA driver as #58.
 *
 * 25-Jul-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added new entry for QVSS at #48 which is exchanged with the
 *	serial line console entry when using the QVSS as the virtual
 *	console.  The old #49 and #50 entries still permanently map the
 *	serial line unit and display respectively.
 *
 * 24-Jul-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Eliminated swap device interface under MACH.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 17-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Installed hooks for local CMU devices
 *	and duplicated some entries in order to eventually move major
 *	device assignments into line with standard.
 *	CS_GENERIC:  re-implemented tty structure length array as a
 *	parallel table to better distinguish it as a local change.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)conf.c	7.1 (Berkeley) 6/5/86
 */
 
#include <cputypes.h>
#include <vice.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/conf.h>

int	nulldev();
int	nodev();

#include <hp.h>
#if	NHP > 0
int	hpopen(),hpstrategy(),hpread(),hpwrite(),hpdump(),hpioctl(),hpsize();
#else
#define hpopen		nodev
#define hpstrategy	nodev
#define hpread		nodev
#define hpwrite		nodev
#define hpdump		nodev
#define hpioctl		nodev
#define hpsize		0
#endif
 
#include <tu.h>
#if	NHT > 0
int	htopen(),htclose(),htstrategy(),htread(),htwrite(),htdump(),htioctl();
#else
#define htopen		nodev
#define htclose		nodev
#define htstrategy	nodev
#define htread		nodev
#define htwrite		nodev
#define htdump		nodev
#define htioctl		nodev
#endif

#include <rk.h>
#if	NHK > 0
int	rkopen(),rkstrategy(),rkread(),rkwrite(),rkintr();
int	rkdump(),rkreset(),rksize();
#else
#define rkopen		nodev
#define rkstrategy	nodev
#define rkread		nodev
#define rkwrite		nodev
#define rkintr		nodev
#define rkdump		nodev
#define rkreset		nodev
#define rksize		0
#endif

#include <te.h>
#if	NTE > 0
int	tmopen(),tmclose(),tmstrategy(),tmread(),tmwrite();
int	tmioctl(),tmdump(),tmreset();
#else
#define tmopen		nodev
#define tmclose		nodev
#define tmstrategy	nodev
#define tmread		nodev
#define tmwrite		nodev
#define tmioctl		nodev
#define tmdump		nodev
#define tmreset		nulldev
#endif

#include <tms.h>
#if	NTMS > 0
int	tmscpopen(),tmscpclose(),tmscpstrategy(),tmscpread(),tmscpwrite();
int	tmscpioctl(),tmscpdump(),tmscpreset();
#else
#define tmscpopen	nodev
#define tmscpclose	nodev
#define tmscpstrategy	nodev
#define tmscpread	nodev
#define tmscpwrite	nodev
#define tmscpioctl	nodev
#define tmscpdump	nodev
#define tmscpreset	nulldev
#endif

#include <ts.h>
#if	NTS > 0
int	tsopen(),tsclose(),tsstrategy(),tsread(),tswrite();
int	tsioctl(),tsdump(),tsreset();
#else
#define tsopen		nodev
#define tsclose		nodev
#define tsstrategy	nodev
#define tsread		nodev
#define tswrite		nodev
#define tsioctl		nodev
#define tsdump		nodev
#define tsreset		nulldev
#endif

#include <mu.h>
#if	NMT > 0
int	mtopen(),mtclose(),mtstrategy(),mtread(),mtwrite();
int	mtioctl(),mtdump();
#else
#define mtopen		nodev
#define mtclose		nodev
#define mtstrategy	nodev
#define mtread		nodev
#define mtwrite		nodev
#define mtioctl		nodev
#define mtdump		nodev
#endif

#include <ra.h>
#if	NUDA > 0
int	udopen(),udstrategy(),udread(),udwrite(),udreset(),uddump(),udsize();
#else
#define udopen		nodev
#define udstrategy	nodev
#define udread		nodev
#define udwrite		nodev
#define udreset		nulldev
#define uddump		nodev
#define udsize		0
#endif

#include <up.h>
#if	NSC > 0
int	upopen(),upstrategy(),upread(),upwrite(),upreset(),updump(),upsize();
#else
#define upopen		nodev
#define upstrategy	nodev
#define upread		nodev
#define upwrite		nodev
#define upreset		nulldev
#define updump		nodev
#define upsize		0
#endif

#include <tj.h>
#if	NUT > 0
int	utopen(),utclose(),utstrategy(),utread(),utwrite(),utioctl();
int	utreset(),utdump();
#else
#define utopen		nodev
#define utclose		nodev
#define utread		nodev
#define utstrategy	nodev
#define utwrite		nodev
#define utreset		nulldev
#define utioctl		nodev
#define utdump		nodev
#endif

#include <rb.h>
#if	NIDC > 0
int	idcopen(),idcstrategy(),idcread(),idcwrite();
int	idcreset(),idcdump(),idcsize();;
#else
#define idcopen		nodev
#define idcstrategy	nodev
#define idcread		nodev
#define idcwrite	nodev
#define idcreset	nulldev
#define idcdump		nodev
#define idcsize		0
#endif

#if	defined(VAX750) || defined(VAX730)
int	tuopen(),tuclose(),tustrategy();
#else
#define tuopen		nodev
#define tuclose		nodev
#define tustrategy	nodev
#endif

#include <rx.h>
#if	NFX > 0
int	rxopen(),rxstrategy(),rxclose(),rxread(),rxwrite(),rxreset(),rxioctl();
#else
#define rxopen		nodev
#define rxstrategy	nodev
#define rxclose		nodev
#define rxread		nodev
#define rxwrite		nodev
#define rxreset		nulldev
#define rxioctl		nodev
#endif

#include <uu.h>
#if	NUU > 0
int	uuopen(),uustrategy(),uuclose(),uureset(),uuioctl();
#else
#define uuopen		nodev
#define uustrategy	nodev
#define uuclose		nodev
#define uureset		nulldev
#define uuioctl		nodev
#endif

#include <rl.h>
#if	NRL > 0
int	rlopen(),rlstrategy(),rlread(),rlwrite();
int	rlreset(),rldump(),rlsize();
#else
#define rlopen		nodev
#define rlstrategy	nodev
#define rlread		nodev
#define rlwrite		nodev
#define rlreset		nulldev
#define rldump		nodev
#define rlsize		0
#endif

#define swstrategy	nodev
#define swread		nodev
#define swwrite		nodev

struct bdevsw	bdevsw[] =
{
	{ hpopen,	nulldev,	hpstrategy,	hpdump,		/*0*/
	  hpsize,	0 },
	{ htopen,	htclose,	htstrategy,	htdump,		/*1*/
	  0,		B_TAPE },
	{ upopen,	nulldev,	upstrategy,	updump,		/*2*/
	  upsize,	0 },
	{ rkopen,	nulldev,	rkstrategy,	rkdump,		/*3*/
	  rksize,	0 },
	{ nodev,	nodev,		swstrategy,	nodev,		/*4*/
	  0,		0 },
	{ tmopen,	tmclose,	tmstrategy,	tmdump,		/*5*/
	  0,		B_TAPE },
	{ tsopen,	tsclose,	tsstrategy,	tsdump,		/*6*/
	  0,		B_TAPE },
	{ mtopen,	mtclose,	mtstrategy,	mtdump,		/*7*/
	  0,		B_TAPE },
	{ tuopen,	tuclose,	tustrategy,	nodev,		/*8*/
	  0,		B_TAPE },
	{ udopen,	nulldev,	udstrategy,	uddump,		/*9*/
	  udsize,	0 },
	{ utopen,	utclose,	utstrategy,	utdump,		/*10*/
	  0,		B_TAPE },
	{ idcopen,	nodev,		idcstrategy,	idcdump,	/*11*/
	  idcsize,	0 },
	{ rxopen,	rxclose,	rxstrategy,	nodev,		/*12*/
	  0,		0 },
	{ uuopen,	uuclose,	uustrategy,	nodev,		/*13*/
	  0,		0 },
	{ rlopen,	nodev,		rlstrategy,	rldump,		/*14*/
	  rlsize,	0 },
	{ tmscpopen,	tmscpclose,	tmscpstrategy,	tmscpdump,	/*15*/
	  0,		B_TAPE },
};
int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

int	cnopen(),cnclose(),cnread(),cnwrite(),cnioctl();
struct tty cons;
#if	VICE
struct	tty *cons_tp;
#endif	VICE
int	ncons;
#define cnntty	(&ncons)

#include <acc.h>
#if	NACC > 0
int     accreset();
#else
#define accreset nulldev
#endif

#include <ct.h>
#if	NCT > 0
int	ctopen(),ctclose(),ctwrite();
#else
#define ctopen	nulldev
#define ctclose	nulldev
#define ctwrite	nulldev
#endif

#include <dh.h>
#if	NDH == 0
#define dhopen	nodev
#define dhclose	nodev
#define dhread	nodev
#define dhwrite	nodev
#define dhioctl	nodev
#define dhstop	nodev
#define dhreset	nulldev
#define dh11	0
#define dhntty	0
#else
int	dhopen(),dhclose(),dhread(),dhwrite(),dhioctl(),dhstop(),dhreset();
struct	tty dh11[];
int	ndh11;
#define dhntty	(&ndh11)
#endif

#include <dmf.h>
#if	NDMF == 0
#define dmfopen	nodev
#define dmfclose	nodev
#define dmfread	nodev
#define dmfwrite	nodev
#define dmfioctl	nodev
#define dmfstop	nodev
#define dmfreset	nulldev
#define dmf_tty	0
#define dmfntty	0
#else
int	dmfopen(),dmfclose(),dmfread(),dmfwrite(),dmfioctl(),dmfstop(),dmfreset();
struct	tty dmf_tty[];
int	ndmf;
#define dmfntty	(&ndmf)
#endif

#if	VAX8600
int	crlopen(),crlclose(),crlread(),crlwrite();
#else
#define crlopen		nodev
#define crlclose	nodev
#define crlread		nodev
#define crlwrite	nodev
#endif

#if	VAX780
int	flopen(),flclose(),flread(),flwrite();
#else
#define flopen	nodev
#define flclose	nodev
#define flread	nodev
#define flwrite	nodev
#endif

#include <dz.h>
#if	NDZ == 0
#define dzopen	nodev
#define dzclose	nodev
#define dzread	nodev
#define dzwrite	nodev
#define dzioctl	nodev
#define dzstop	nodev
#define dzreset	nulldev
#define dz_tty	0
#define dzntty	0
#else
int	dzopen(),dzclose(),dzread(),dzwrite(),dzioctl(),dzstop(),dzreset();
struct	tty dz_tty[];
int	dz_cnt;
#define dzntty	(&dz_cnt)
#endif

#include <lp.h>
#if	NLP > 0
int	lpopen(),lpclose(),lpwrite(),lpreset();
#else
#define lpopen		nodev
#define lpclose		nodev
#define lpwrite		nodev
#define lpreset		nulldev
#endif

int	syopen(),syread(),sywrite(),syioctl(),syselect();

int 	mmread(),mmwrite();
#define mmselect	seltrue

#include <va.h>
#if	NVA > 0
int	vaopen(),vaclose(),vawrite(),vaioctl(),vareset(),vaselect();
#else
#define vaopen		nodev
#define vaclose		nodev
#define vawrite		nodev
#define vaopen		nodev
#define vaioctl		nodev
#define vareset		nulldev
#define vaselect	nodev
#endif

#include <vp.h>
#if	NVP > 0
int	vpopen(),vpclose(),vpwrite(),vpioctl(),vpreset(),vpselect();
#else
#define vpopen		nodev
#define vpclose		nodev
#define vpwrite		nodev
#define vpioctl		nodev
#define vpreset		nulldev
#define vpselect	nodev
#endif

#include <pty.h>
#if	NPTY > 0
int	ptsopen(),ptsclose(),ptsread(),ptswrite(),ptsstop();
int	ptcopen(),ptcclose(),ptcread(),ptcwrite(),ptcselect();
int	ptyioctl();
struct	tty pt_tty[];
int	npty;
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

#include <lpa.h>
#if	NLPA > 0
int	lpaopen(),lpaclose(),lparead(),lpawrite(),lpaioctl();
#else
#define lpaopen		nodev
#define lpaclose	nodev
#define lparead		nodev
#define lpawrite	nodev
#define lpaioctl	nodev
#endif

#include <dn.h>
#if	NDN > 0
int	dnopen(),dnclose(),dnwrite();
#else
#define dnopen		nodev
#define dnclose		nodev
#define dnwrite		nodev
#endif

#include <ik.h>
#if	NIK > 0
int	ikopen(),ikclose(),ikread(),ikwrite(),ikioctl(),ikreset();
#else
#define ikopen nodev
#define ikclose nodev
#define ikread nodev
#define ikwrite nodev
#define ikioctl nodev
#define ikreset nulldev
#endif

#include <ps.h>
#if	NPS > 0
int	psopen(),psclose(),psread(),pswrite(),psioctl(),psreset();
#else
#define psopen nodev
#define psclose nodev
#define psread nodev
#define pswrite nodev
#define psopen nodev
#define psioctl nodev
#define psreset nulldev
#endif

#include <ad.h>
#if	NAD > 0
int	adopen(),adclose(),adioctl(),adreset();
#else
#define adopen nodev
#define adclose nodev
#define adioctl nodev
#define adreset nulldev
#endif

int	logopen(),logclose(),logread(),logioctl(),logselect();

#include <dhu.h>
#if	NDHU > 0
int dhuopen(),dhuclose(),dhuread(),dhuwrite(),dhuioctl(),dhustop(),dhureset();
struct tty dhu_tty[];
#else
#define dhuopen nodev
#define dhuclose nodev
#define dhuread nodev
#define dhuwrite nodev
#define dhuioctl nodev
#define dhustop nodev
#define dhureset nulldev
#define dhu_tty 0
#endif

#include <vs.h>
#if	NVS > 0
int	vsopen(),vsclose(),vsioctl(),vsreset(),vsselect();
#else
#define vsopen nodev
#define vsclose nodev
#define vsioctl nodev
#define vsreset nodev
#define vsselect nodev
#endif

#include <dmz.h>
#if	NDMZ > 0
int dmzopen(),dmzclose(),dmzread(),dmzwrite(),dmzioctl(),dmzstop(),dmzreset();
struct tty dmz_tty[];
extern  int ndmz;
#define dmzntty	(&ndmz)
#else
#define dmzopen nodev
#define dmzclose nodev
#define dmzread nodev
#define dmzwrite nodev
#define dmzioctl nodev
#define dmzstop nodev
#define dmzreset nulldev
#define dmz_tty 0
#define dmzntty	0
#endif

int	ttselect(), seltrue();

#include <ip.h>
#if	NIP > 0
int	ipopen(),ipclose(),ipread(),ipwrite(),ipioctl(),ipreset();
#else	NIP
#define ipopen	nodev
#define ipclose	nodev
#define ipread	nodev
#define ipwrite	nodev
#define ipioctl	nodev
#define ipreset nodev
#endif	NIP
#define ipselect nodev

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

#include <dr.h>
#if	NDR > 0
int	dropen(),drclose(),drread(),drwrite(),drioctl(),drreset();
#else	NDR
#define dropen		nodev
#define drclose		nodev
#define drread		nodev
#define drwrite		nodev
#define drioctl		nodev
#define drreset		nulldev
#endif	NDR

#include <ds.h>
#if	NDS > 0
int	dsopen(),dsclose(),dsread(),dswrite(),dsioctl(),dsreset();
#else	NDS
#define dsopen	nodev
#define dsclose	nodev
#define dsread	nodev
#define dswrite	nodev
#define dsioctl	nodev
#define dsreset	nulldev
#endif	NDS

#include <dzq.h>
#if	NDZQ > 0
int	dzqopen(),dzqclose(),dzqread(),dzqwrite(),dzqioctl(),dzqstop(),dzqreset();
#else	NDZQ
#define dzqopen		nodev
#define dzqclose	nodev
#define dzqread		nodev
#define dzqwrite	nodev
#define dzqioctl	nodev
#define dzqstop		nodev
#define dzqreset	nulldev
#endif	NDZQ

#include <enet.h>
#if	NENET > 0
int	enetopen(),enetclose(),enetread(),enetwrite(),enetioctl(),enetselect();
#else	NENET
#define enetopen	nodev
#define enetclose	nodev
#define enetread	nodev
#define enetwrite	nodev
#define enetioctl	nodev
#define enetselect	nulldev
#endif	NENET

#include <fe.h>
#if	NFE > 0
int	feopen(),feclose(),feread(),fewrite(),feioctl(),fereset();
int	fespread(),fespwrite(),fespioctl();
struct	tty fe_tty[];
int	nfetty;
#define fentty	(&nfetty)
#else	NFE
#define feopen		nodev
#define feclose		nodev
#define feread		nodev
#define fewrite		nodev
#define feioctl		nodev
#define fereset		nulldev
#define fe_tty		0
#define fespopen	nodev
#define fespclose	nodev
#define fespread	nodev
#define fespwrite	nodev
#define fespioctl	nodev
#define fentty		0
#endif	NFE

#include <fps.h>
#if	NFPS > 0
int	fpsopen(), fpsclose(), fpsioctl(), fpsreset();
int	fpsQopen(), fpsQclose(), fpsQioctl();
#else	NFPS
#define fpsopen		nodev
#define fpsclose	nodev
#define fpsioctl	nodev
#define fpsreset	nodev
#define fpsQopen	nodev
#define fpsQclose	nodev
#define fpsQioctl	nodev
#endif	NFPS

#include <qv.h>
#if	NQV > 0
int	qvopen(),qvclose(),qvread(),qvwrite(),qvioctl(),qvstop(),qvreset(),
	qvselect();
int	qvmap();
struct	tty qv_tty[];
extern int nNQV;
#define qvntty	(&nNQV)
#define qsntty	(&ncons)
#define qsopen		cnopen
#define qsclose		cnclose
#define qsread		cnread
#define qswrite		cnwrite
#define qsioctl		cnioctl
#define qsselect	ttselect
#define qs_tty		(&cons)
#else	NQV
#define qvopen		nodev
#define qvclose		nodev
#define qvread		nodev
#define qvwrite		nodev
#define qvioctl		nodev
#define qvstop		nodev
#define qvreset		nulldev
#define qvselect 	nodev
#define qv_tty		0
qvcons_init(){}
#define qvntty		0
#define qsntty		0
#define qvmap		nodev
#define qsopen		nodev
#define qsclose		nodev
#define qsread		nodev
#define qswrite		nodev
#define qsioctl		nodev
#define qsselect	nodev
#define qs_tty		0
#endif	NQV

#include <qd.h>
#if	NQD > 0
int	qdopen(),qdclose(),qdread(),qdwrite(),qdioctl(),qdstop(),qdreset(),
	qdselect();
struct	tty qd_tty[];
extern int nNQD;
#define qdntty	(&nNQD)
#else	NQD > 0
#define qdopen		nodev
#define qdclose		nodev
#define qdread		nodev
#define qdwrite		nodev
#define qdioctl		nodev
#define qdstop		nodev
#define qdreset		nulldev
#define qdselect 	nodev
#define qd_tty		0
qdcons_init(){}
#define qdntty		0
#endif	NQD

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

#include <ild.h>
#if	NILD > 0
#define ildopen		nulldev
#define ildclose	nulldev
int ildwrite(), ildioctl();
#else	NILD
#define ildopen		nodev
#define ildclose	nodev
#define ildwrite	nodev
#define ildioctl	nodev
#endif	NILD
   
/* dial up interface stuff ... */

#include <du.h>
#if	NDU > 0
	int dialupopen(), dialupclose(), dialupread(), dialupioctl();
#else	NDU > 0
#define dialupopen nodev
#define dialupclose nodev
#define dialupread nodev
#define dialupioctl nodev
#endif	NDU
struct cdevsw	cdevsw[] =
{
	cnopen,		cnclose,	cnread,		cnwrite,	/*0*/
	cnioctl,	nulldev,	nulldev,	&cons,
	ttselect,	nodev,
	dzopen,		dzclose,	dzread,		dzwrite,	/*1*/
	dzioctl,	dzstop,		dzreset,	dz_tty,
	ttselect,	nodev,
	syopen,		nulldev,	syread,		sywrite,	/*2*/
	syioctl,	nulldev,	nulldev,	0,
	syselect,	nodev,
	nulldev,	nulldev,	mmread,		mmwrite,	/*3*/
	nodev,		nulldev,	nulldev,	0,
	mmselect,	nodev,
	hpopen,		nulldev,	hpread,		hpwrite,	/*4*/
	hpioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,
	htopen,		htclose,	htread,		htwrite,	/*5*/
	htioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,
	vpopen,		vpclose,	nodev,		vpwrite,	/*6*/
	vpioctl,	nulldev,	vpreset,	0,
	vpselect,	nodev,
	nulldev,	nulldev,	swread,		swwrite,	/*7*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
	flopen,		flclose,	flread,		flwrite,	/*8*/
	nodev,		nodev,		nulldev,	0,
	seltrue,	nodev,
	udopen,		nulldev,	udread,		udwrite,	/*9*/
	nodev,		nodev,		udreset,	0,
	seltrue,	nodev,
	vaopen,		vaclose,	nodev,		vawrite,	/*10*/
	vaioctl,	nulldev,	vareset,	0,
	vaselect,	nodev,
	rkopen,		nulldev,	rkread,		rkwrite,	/*11*/
	nodev,		nodev,		rkreset,	0,
	seltrue,	nodev,
	dhopen,		dhclose,	dhread,		dhwrite,	/*12*/
	dhioctl,	dhstop,		dhreset,	dh11,
	ttselect,	nodev,
	upopen,		nulldev,	upread,		upwrite,	/*13*/
	nodev,		nodev,		upreset,	0,
	seltrue,	nodev,
	tmopen,		tmclose,	tmread,		tmwrite,	/*14*/
	tmioctl,	nodev,		tmreset,	0,
	seltrue,	nodev,
	lpopen,		lpclose,	nodev,		lpwrite,	/*15*/
	nodev,		nodev,		lpreset,	0,
	seltrue,	nodev,
	tsopen,		tsclose,	tsread,		tswrite,	/*16*/
	tsioctl,	nodev,		tsreset,	0,
	seltrue,	nodev,
	utopen,		utclose,	utread,		utwrite,	/*17*/
	utioctl,	nodev,		utreset,	0,
	seltrue,	nodev,
	ctopen,		ctclose,	nodev,		ctwrite,	/*18*/
	nodev,		nodev,		nulldev,	0,
	seltrue,	nodev,
	mtopen,		mtclose,	mtread,		mtwrite,	/*19*/
	mtioctl,	nodev,		nodev,		0,
	seltrue,	nodev,
	ptsopen,	ptsclose,	ptsread,	ptswrite,	/*20*/
	ptyioctl,	ptsstop,	nulldev,	pt_tty,
	ttselect,	nodev,
	ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*21*/
	ptyioctl,	nulldev,	nulldev,	pt_tty,
	ptcselect,	nodev,
	dmfopen,	dmfclose,	dmfread,	dmfwrite,	/*22*/
	dmfioctl,	dmfstop,	dmfreset,	dmf_tty,
	ttselect,	nodev,
	idcopen,	nulldev,	idcread,	idcwrite,	/*23*/
	nodev,		nodev,		idcreset,	0,
	seltrue,	nodev,
	dnopen,		dnclose,	nodev,		dnwrite,	/*24*/
	nodev,		nodev,		nulldev,	0,
	seltrue,	nodev,
/* 25-29 reserved to local sites */
	/* (changing to local #??) */
	feopen,		feclose,	feread,		fewrite,	/*25*/
	feioctl,	nulldev,	nulldev,	fe_tty,
	ttselect,	nodev,
	/* (changing to local #??) */
	nulldev,	nulldev,	fespread,	fespwrite,	/*26*/
	fespioctl,	nulldev,	fereset,	0,
	seltrue,	nodev,
	/* (going away) */
	enetopen,	enetclose,	enetread,	enetwrite,	/*27*/
	enetioctl,	nodev,		nulldev,	0,
	enetselect,	nodev,
	/* (changing to local #??) */
	cmuptyopen,	cmuptyclose,	cmuptyread,	cmuptywrite,	/*28*/
	cmuptyioctl,	nulldev,	nulldev,	cmupty_tty,
	ttselect,	nodev,
	/* (changing to local #??) */
	cmuptycopen,	cmuptycclose,	cmuptycread,	cmuptycwrite,	/*29*/
	cmuptycioctl,	nodev,		nulldev,	0,
	cmuptycselect,	nodev,
	/* (changing to local #42) */
	dropen,		drclose,	drread,		drwrite,	/*30*/
	drioctl,	nodev,		drreset,	0,
	seltrue,	nodev,
	ikopen,		ikclose,	ikread,		ikwrite,	/*31*/
	ikioctl,	nodev,		ikreset,	0,
	seltrue,	nodev,
	rlopen,		nodev,		rlread,		rlwrite,	/*32*/
	nodev,		nodev,		rlreset,	0,
	seltrue,	nodev,
	/* (changing to local #??) */
	ildopen,	ildclose,	nulldev,	ildwrite,	/*33*/
	ildioctl,	nulldev,	nulldev,	0,
	seltrue,	nodev,
	/* (changing to standard #17) */
	utopen,		utclose,	utread,		utwrite,	/*34*/
	utioctl,	nodev,		utreset,	0,
	seltrue,	nodev,
 	crlopen,	crlclose,	crlread,	crlwrite,	/*35*/
 	nodev,		nodev,		nulldev,	0,
 	seltrue,	nodev,
 	vsopen,		vsclose,	nodev,		nodev,		/*36*/
 	vsioctl,	nodev,		vsreset,	0,
 	vsselect,	nodev,
	dmzopen,        dmzclose,       dmzread,        dmzwrite,       /*37*/
	dmzioctl,       dmzstop,        dmzreset,       dmz_tty,
	ttselect,       nodev,
	tmscpopen,	tmscpclose,	tmscpread,	tmscpwrite,	/*38*/
	tmscpioctl,	nodev,		tmscpreset,	0,
	seltrue,	nodev,
	nodev,		nodev,		nodev,		nodev,		/*39*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
	nodev,		nodev,		nodev,		nodev,		/*40*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
	nodev,		nodev,		nodev,		nodev,		/*41*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
/* 42-50 reserved to local sites */
	/* (changing from pre-empted #30) */
	dropen,		drclose,	drread,		drwrite,	/*42*/
	drioctl,	nodev,		drreset,	0,
	seltrue,	nodev,
	/* Special purpose DZQ11 interface for ASSY.RI */
	dzqopen,	dzqclose,	dzqread,	dzqwrite,	/*43*/
	dzqioctl,	dzqstop,	dzqreset,	0,
	seltrue,	nodev,
	/*  DSC-200  */
	dsopen,		dsclose,	dsread,		dswrite,	/*44*/
	dsioctl,	nodev,		dsreset,	0,
	seltrue,	nodev,
	/*  FPS-100  */
	fpsopen,	fpsclose,	nulldev,	nulldev,	/*45*/
	fpsioctl,	nulldev,	fpsreset,	0,
	seltrue,	nodev,
	/*  FPS-100  */
	fpsQopen,	fpsQclose,	nulldev,	nulldev,	/*46*/
	fpsQioctl,	nulldev,	nulldev,	0,
	seltrue,	nodev,
	/* (changing to standard #9) */
	udopen,		nulldev,	udread,		udwrite,	/*47*/
	nodev,		nodev,		udreset,	0,
	seltrue,	nodev,
	/*  MicroVax QVSS Display/serial line unit  */
	qvopen,		qvclose,	qvread,		qvwrite,	/*48*/
	qvioctl,	qvstop,		qvreset,	qv_tty,
	qvselect,	qvmap,
#define QVMAJOR	48
	/*  MicroVax serial line unit (console)  */
	qsopen,		qsclose,	qsread,		qswrite,	/*49*/
	qsioctl,	nulldev,	nulldev,	qs_tty,
	qsselect,	nodev,
	/*  MicroVax QVSS Display  */
	qvopen,		qvclose,	qvread,		qvwrite,	/*50*/
	qvioctl,	qvstop,		qvreset,	qv_tty,
	qvselect,	qvmap,
	tmscpopen,	tmscpclose,	tmscpread,	tmscpwrite,	/*51*/
	tmscpioctl,	nodev,		tmscpreset,	0,
	seltrue,	nodev,
	nodev,		nodev,		nodev,		nodev,		/*52*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
	nodev,		nodev,		nodev,		nodev,		/*53*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
	/*
	 * These devices are moved here from above.
	 */
	logopen,	logclose,	logread,	nodev,		/*54*/
	logioctl,	nodev,		nulldev,	0,
	logselect,	nodev,
	dhuopen,        dhuclose,       dhuread,        dhuwrite,       /*55*/
	dhuioctl,       dhustop,        dhureset,       dhu_tty,
	ttselect,       nodev,
 	crlopen,	crlclose,	crlread,	crlwrite,	/*56*/
 	nodev,		nodev,		nulldev,	0,
 	seltrue,	nodev,
	vsopen,		vsclose,	nodev,		nodev,		/*57*/
	vsioctl,	nodev,		vsreset,	0,
	vsselect,	nodev,
	ipopen,		ipclose,	ipread,		ipwrite,	/*58*/
	ipioctl,	nodev,		ipreset,	0,
	ipselect,	nodev,
	/*  MicroVax QDSS Display  */
	qdopen,		qdclose,	qdread,		qdwrite,	/*59*/
	qdioctl,	qdstop,		qdreset,	qd_tty,
	qdselect,	nodev,
#if	VICE
	rmtopen,	rmtclose,	rmtread,	rmtwrite,	/*60*/
	nodev,		nodev,		nodev,		0,
  	rmtselect,	nodev,
#else	VICE
	nodev,		nodev,		nodev,		nodev,		/*60*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,
#endif	VICE
	dialupopen,	dialupclose,	dialupread,	nodev,		/*61*/
	dialupioctl,	nulldev,	nulldev,	0,
	nodev,		nodev,
};
int	nchrdev = sizeof (cdevsw) / sizeof (cdevsw[0]);

int *nttysw[] =
{
    cnntty,	/*  0 */
    dzntty,	/*  1 */
    0,		/*  2 */
    0,		/*  3 */
    0,		/*  4 */
    0,		/*  5 */
    0,		/*  6 */
    0,		/*  7 */
    0,		/*  8 */
    0,		/*  9 */
    0,		/* 10 */
    0,		/* 11 */
    dhntty,	/* 12 */
    0,		/* 13 */
    0,		/* 14 */
    0,		/* 15 */
    0,		/* 16 */
    0,		/* 17 */
    0,		/* 18 */
    0,		/* 19 */
    ptsntty,	/* 20 */
    0,		/* 21 */
    dmfntty,	/* 22 */
    0,		/* 23 */
    0,		/* 24 */
    fentty,	/* 25 */
    0,		/* 26 */
    0,		/* 27 */
    cmuptyntty,	/* 28 */
    0,		/* 29 */
    0,		/* 30 */
    0,		/* 31 */
    0,		/* 32 */
    0,		/* 33 */
    0,		/* 34 */
    0,		/* 35 */
    0,		/* 36 */
    dmzntty,	/* 37 */
    0,		/* 38 */
    0,		/* 39 */
    0,		/* 40 */
    0,		/* 41 */
    0,		/* 42 */
    0,		/* 43 */
    0,		/* 44 */
    0,		/* 45 */
    0,		/* 46 */
    0,		/* 47 */
    qvntty,	/* 48 */
    qsntty,	/* 49 */
    qvntty,	/* 50 */
    0,		/* 51 */
    0,		/* 52 */
    0,		/* 53 */
    0,		/* 54 */
    0,		/* 55 */
    0,		/* 56 */
    0,		/* 57 */
    0,		/* 58 */
    qdntty,	/* 59 */
};
int	ntty = sizeof (nttysw) / sizeof (nttysw[0]);

dev_t	sydev = makedev(2, 0);	/* device number for indirect tty */
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
#if	NQV > 0
int QVSSMAJOR = QVMAJOR;
#endif	NQV > 0
