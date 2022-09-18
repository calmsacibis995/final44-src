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
 * $Log:	tty_conf.c,v $
 * Revision 2.6  89/07/11  13:13:13  jjc
 * 	Changed "#ifdef sun3" into "if defined(sun3) || defined(sun4)".
 * 	[89/05/06            jjc]
 * 
 * Revision 2.5  89/03/09  19:32:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  11:27:27  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/09  04:33:41  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.2  88/11/14  14:31:46  gm0w
 * 	Added CSNET DialupIP support.
 * 	[88/11/14            gm0w]
 * 
 *  9-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Handle ROMP_TB.
 *
 * 24-Dec-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	romp: Added definitions for the l_select field used by X on the
 *	RT.  Also removed now defunct aed_tty entries (on line 7).
 *
 *  5-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added support for Sun mouse and keyboard.
 *
 * 16-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added support for Sailboat MS and AED devices under switch romp.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 30-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	NFE:  Added Front End line discipline.
 *	[V1(1)]
 *
 */
 

#include <fe.h>
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)tty_conf.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/conf.h>

int	nodev();
int	nulldev();

int	ttyopen(),ttylclose(),ttread(),ttwrite(),nullioctl(),ttstart();
int	ttymodem(), nullmodem(), ttyinput();
#ifdef	ibmrt
int	ttselect();
#endif	ibmrt

#include <bk.h>
#if	NBK > 0
int	bkopen(),bkclose(),bkread(),bkinput(),bkioctl();
#endif

#ifdef	ibmrt
#include <romp_tb.h>
#undef	NTB
#define NTB	NROMP_TB
#else	ibmrt
#include <tb.h>
#endif	ibmrt
#if	NTB > 0 || NROMP_TB > 0
int	tbopen(),tbclose(),tbread(),tbinput(),tbioctl(),tbselect();
#endif
#ifdef	ibmrt
/* This is a kludge; supposed to be machine independent -- sac */
#include <ms.h>
#if	NMS > 0
int	msdopen(),msdclose(),msdread(),msdinput(),msdioctl(),msdselect();
#endif	NMS
#endif	ibmrt

#if	defined(sun3) || defined(sun4)
#include <ms.h>
#if	NMS > 0
int     msopen(), msclose(), msread(), msioctl(), msinput();
#endif

#include <kb.h>
#if	NKB > 0
int     kbdopen(), kbdclose(), kbdread(), kbdioctl(), kbdinput();
#endif
#endif	defined(sun3) || defined(sun4)

#include <sl.h>
#if	NSL > 0
int	slopen(),slclose(),slinput(),sltioctl(),slstart();
#endif

#ifdef	vax
#include <du.h>
#if	NDU > 0
int	dutopen(),dutclose(),dutinput(),dutioctl(),dutstart(),dutmodem();
#endif
#endif


struct	linesw linesw[] =
{
	ttyopen, ttylclose, ttread, ttwrite, nullioctl,	/* 0- OTTYDISC */
	ttyinput, nodev, nulldev, ttstart, ttymodem,
#ifdef	ibmrt
	ttselect,
#endif	ibmrt
#if	NBK > 0
	bkopen, bkclose, bkread, ttwrite, bkioctl,	/* 1- NETLDISC */
	bkinput, nodev, nulldev, ttstart, nullmodem,
#ifdef	ibmrt
	ttselect,
#endif	ibmrt
#else
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
#ifdef	ibmrt
	nodev,
#endif	ibmrt
#endif
	ttyopen, ttylclose, ttread, ttwrite, nullioctl,	/* 2- NTTYDISC */
	ttyinput, nodev, nulldev, ttstart, ttymodem,
#ifdef	ibmrt
	ttselect,
#endif	ibmrt
#if	NTB > 0 
	tbopen, tbclose, tbread, nodev, tbioctl,
	tbinput, nodev, nulldev, ttstart, nullmodem,	/* 3- TABLDISC */
#ifdef	ibmrt
	tbselect,
#endif	ibmrt
#else
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
#ifdef	ibmrt
	nodev,
#endif	ibmrt
#endif
#if	NSL > 0
	slopen, slclose, nodev, nodev, sltioctl,
	slinput, nodev, nulldev, slstart, nulldev,	/* 4- SLIPDISC */
#ifdef	ibmrt
	nodev,
#endif	ibmrt
#else
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
#ifdef	ibmrt
	nodev,
#endif	ibmrt
#endif
#if	defined(ibmrt) && NMS > 0
	msdopen, msdclose, msdread, nodev, msdioctl,
	msdinput, nodev, nulldev, ttstart, nulldev,	/* 5- MOUSELDISC */
	msdselect,
#else	defined(ibmrt) && NMS > 0
#if	(defined(sun3) || defined(sun4)) && NMS > 0
	msopen, msclose, msread, nodev, msioctl,
	msinput, nodev, nulldev, nulldev, nulldev,
#else	(defined(sun3) || defined(sun4)) && NMS > 0
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
#ifdef	ibmrt
	nodev,
#endif	ibmrt
#endif	(defined(sun3) || defined(sun4)) && NMS > 0
#endif	defined(ibmrt) && NMS > 0
#if	(defined(sun3) || defined(sun4)) && NKB > 0
        kbdopen, kbdclose, kbdread, ttwrite, kbdioctl,
	kbdinput, nodev, nulldev, ttstart, nulldev,	/* 6- KDBLDISC */
#else	(defined(sun3) || defined(sun4)) && NKB > 0
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
#ifdef	ibmrt
	nodev,
#endif	ibmrt
#endif	(defined(sun3) || defined(sun4)) && NKB > 0
#if	NDU > 0
	dutopen, dutclose, nodev, nodev, dutioctl,
	dutinput, nodev, nulldev, dutstart, dutmodem,	/* 7- DUDISC */
#ifdef	ibmrt
	nodev,
#endif	ibmrt
#else
	nodev, nodev, nodev, nodev, nodev,
	nodev, nodev, nodev, nodev, nodev,
#ifdef	ibmrt
	nodev,
#endif	ibmrt
#endif
};

int	nldisp = sizeof (linesw) / sizeof (linesw[0]);

/*
 * Do nothing specific version of line
 * discipline specific ioctl command.
 */
/*ARGSUSED*/
nullioctl(tp, cmd, data, flags)
	struct tty *tp;
	char *data;
	int flags;
{

#ifdef	lint
	tp = tp; data = data; flags = flags;
#endif
	return (-1);
}
