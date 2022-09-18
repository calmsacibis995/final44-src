/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fps.c,v $
 * Revision 2.3  89/03/09  22:34:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:03:08  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
/*
 *	(c) 1982 Copyright	Apunix Computer Services
 *
 *	$ Log:	fps.c,v $
 * Revision 1.16  85/07/11  23:41:29  phb
 * Added changes for Gould systems.
 * 
 * Revision 1.15  85/05/16  00:28:46  phb
 * Removed unnecessary read from Perkin-Elmer interface register
 * that was put in to get around a hardware problem.  Change only
 * effects Perkin-Elmer hosts.
 * 
 * Revision 1.14  85/03/10  21:50:05  phb
 * Added code by levin@stanford that kicks jobs out of the AP queue that
 * are currently stopped thus forcing them to re-enter the queue after
 * bouncing back through apex after being woken up.
 * 
 * Revision 1.13  85/02/26  22:45:57  phb
 * Fixed RAPMAE and RMSK to do shifting of register read after the
 * register is read.  Old way would work on DEC equipment but not
 * on a Perkin-Elmer where the fps_rr function actually does something.
 * 
 * Revision 1.12  84/10/13  21:35:19  phb
 * Removed check for diagnostic mode for XCONT (Continue AP) command.
 * This is necessary as psfunc and stpsa now use it.
 * 
 * Revision 1.11  84/10/03  22:51:54  phb
 * Added the zeroing of the lite register and thus the memory paging
 * registers in the fpsinit routine to assure a know stutus when
 * the AP is opened.
 * 
 * Revision 1.10  84/10/02  10:59:47  phb
 * Added Perkin Elmer changes and added the reading and writing of
 * the memory paging registers.
 * 
 * Revision 1.9  84/09/09  20:36:51  phb
 * Moved definitions of structures from fpsreg.h to the driver.
 * 
 * Revision 1.8  84/03/15  23:41:46  phb
 * Fixed allocation of buffer for V7 UNIX.
 * 
 * Revision 1.7  84/03/15  21:33:40  phb
 * Fixed the calling of mapalloc for PDP-11's.
 * (from Toshiba-Japan)
 * 
 * Revision 1.6  84/03/03  11:52:32  phb
 * Fixed shifting of "apad" problem under V7 Unix.
 * (from MIT-Lincoln Labs)
 * 
 * Revision 1.5  84/02/08  23:27:36  phb
 * Fixed fps reset routine problem under Berkeley 4.1* BSD Unix.
 * Since sc_ubinfo is not set to zero after the ubarelse, another
 * ubarelse will be attempted later.  (from University of Melbourne)
 * 
 * Revision 1.4  84/01/12  15:02:12  phb
 * Installed a new optimizied version of the synchronization code
 * and cleanup up some miscellaneous 4.2 BSD bugs.
 * 
 * Revision 1.2  83/12/16  22:27:48  phb
 * Updated for Berkeley 4.2 BSD UNIX.
 * 
 * Revision 1.1  83/11/05  15:13:04  phb
 * Initial revision
 * 
 */
#include <fps.h>
#if	NFPS > 0

/*
 * Berkeley 4.2 BSD pathnames
 */

#include <sys/fpsconf.h>

#include <machine/pte.h>
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/map.h>

#include <sys/fpsreg.h>

#include <sys/uio.h>
#include <sys/ioctl.h>
#include <vaxuba/ubavar.h>

/*
 *	UNIX fps interface
 *
 *	Functions supported are --
 *		1) DMA transfers between the host and the AP
 *		2) Register transfer between a buffer and the device registers
 *		3) Sleeping, pending AP completion
 *		4) Signal, upon receiving an AP software interrupt.
 *
 *
 *	Intended to handle multiple AP's; never debugged.
 *
 *	Device register foibles -- 
 *		1) In all write operations involving the CSR register,
 *		   ensure that the HDMA-START is zero unless you are
 *		   requesting a DMA-START; in other words, in a read-
 *		   modify-write sequence, eliminate the low order bit
 *		   after reading.
 *		2) After servicing an interrupt, clear all interrupt
 *		   request bits, then reset those that have not yet been
 *		   serviced.
 *		3) Enable an interrupt only after(i.e., after) starting
 *		   the processor or the DMA operation.
 *		4) To clear the AP interrupt, write into the function
 *		   register.
 *		5) Because the AP software interrupt is not denoted by
 *		   an indicator flag, these interrupts can be hidden
 *		   by other interrupts;  the effect is to lock up the
 *		   AP's interrupt hardware.
 */

#ifdef	BSD42
#define B_ADDR	b_un.b_addr
#else
#ifdef	BELL4
#define B_ADDR	b_paddr
#else
#ifdef	V7
#define B_ADDR	b_un.b_addr
#else
#define B_ADDR	b_addr
#endif
#endif
#endif

#ifdef	PERKINELMER
#define fps_rr(x)	rh(&(x))
#define fps_wr(x,y)	wh(&(x),(y))
#else
#ifdef	GOULD
#define fps_rr(x)	fps_grr(fpsunit,&(x))
#define fps_wr(x,y)	fps_gwr(fpsunit,&(x),(y))
#else
#define fps_rr(x)	(x)
#define fps_wr(x,y)	x = (y)
#endif
#endif

#ifndef	GOULD
#define fpswait(x,y)	(sc->sc_mode & y)
#endif

#define FPSUNIT(x)	(minor(x))

#define PRIWAIT	(PZERO+10)		/*  10 */
#define PRIFPS	(PZERO-10)		/* -10 */

struct  buf rfpsbuf[NFPS];
struct fps_softc fps_softc[NFPS];
struct fpsQent	fq_Qfree;		/* the head of the free queue slots */
struct fpsQent	fq_Qlist;		/* the head of the queue */
struct fpsQent	fq_Qent[NFPSQ];		/* the actual queue */

/*
 * Driver unibus interface routines and variables.
 */
#ifdef	BELL4
extern int	fps_addr[];
#endif

#ifdef	PERKINELMER
struct selchq fpsscq[NFPS];
int fpsactive[8];	/* the 8 should really be the total number of selch's */
extern char fpsaddr[];
#define fpsaddr fpaddr
extern int fpsselch[];
int	fpstart(),fpselch();
#endif

int	fpstrategy();

#ifdef	BERK4
#ifndef	GOULD
int	fpsprobe(), fpsattach();
#endif
#ifdef	BSD42
#define KFPSCOM		(DEV_BSIZE / sizeof(struct fps_iopb))
struct uio	fpsuio[NFPS];
struct iovec	fpsiov[NFPS];
#endif
#endif

struct	uba_device *fpsdinfo[NFPS];
#ifdef	GOULD
struct	hsdinfo fpdinfo[NFPS];
extern dcbT	*Fp_mtd[];
extern int	*Nfp_mtd;
extern dvcentry	scr_int[112];
#endif

#ifdef	FPSDEBUG
short	fpsdebug = 0;
#endif

#ifdef	BERK4
#ifndef	GOULD

u_short	fpstd[] = {0765200, 0};

struct	uba_driver fpsdriver =
 {fpsprobe, 0, fpsattach, 0, fpstd, "fps", fpsdinfo, 0, 0, 0};

/*ARGSUSED*/
fpsprobe(reg)
  caddr_t reg;
{
	register int br, cvec;

#ifdef	lint
	br = 0; cvec = br; br = cvec;
#endif
	((struct fpsdevice *)reg)->fpsrset = 0;
	DELAY(100);
	((struct fpsdevice *)reg)->fpsfn = FN_RESET;
	DELAY(100);
	((struct fpsdevice *)reg)->fpscsr = 0;
	((struct fpsdevice *)reg)->fpsrset = 0;
	DELAY(100);
	((struct fpsdevice *)reg)->fpsfn = FN_RESET;
	DELAY(100);
	((struct fpsdevice *)reg)->fpscsr = CS_ONHALT;
	DELAY(100);
	((struct fpsdevice *)reg)->fpscsr = 0;
#ifdef	BSD42
	return(sizeof(struct fpsdevice));
#else
	return(1);
#endif
}

fpsattach() {}
#endif
#endif

fpsopen(dev)
  dev_t	dev;
{
	register fpsunit = FPSUNIT(dev);
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register struct	buf *bp;
#ifdef	V7
	struct buf *geteblk();
#endif

#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpsopen\n");
#endif
	if (fpsunit >= NFPS)
		return(u.u_error = ENXIO);
	if (sc->sc_openf && sc->sc_openf != u.u_procp)
		return(u.u_error = EBUSY);
	if (!fpsdinfo[fpsunit]->ui_alive)
		return(u.u_error = ENXIO);
	sc->sc_openf = u.u_procp;
	fpsinit(fpsunit);
	sc->sc_ccount = sc->sc_cindex = sc->sc_eword = sc->sc_fpserr =
	sc->sc_ubinfo = sc->sc_ndone = sc->sc_dindex = sc->sc_mode = 0;
#ifdef	BERK4
#ifdef	BSD42
	bp = geteblk(DEV_BSIZE);
#else
	bp = geteblk();
#endif
#else
#ifdef	BELL4
#ifdef	vax
	sc->sc_ubinfo = ubmalloc(MINPHYS,1);
#else
	bp = getablk(1);
	sc->sc_ubinfo = ubmalloc(0-1);
#endif
#else
#ifdef	V7
	bp = geteblk();
#else
	bp = getblk(NODEV,0);
#endif
#endif
#endif
	sc->sc_header = bp;
	sc->sc_iocbase = bp->B_ADDR;
	return(u.u_error);
}

fpsclose(dev)
  dev_t	dev;
{
	int fpsunit = FPSUNIT(dev);
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register struct fpsdevice *fpsaddr = (struct fpsdevice *) fpsdinfo[fpsunit]->ui_addr;

#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpsclose\n");
#endif
	fpsinit(FPSUNIT(dev));
	fps_wr(fpsaddr->fpscsr,0);
#ifdef	PERKINELMER
	oc(fpsaddr,OC_DISARM);
#endif
	brelse(sc->sc_header);
	sc->sc_ccount = 0;
#ifdef	BELL4
	ubmfree(sc->sc_ubinfo,0-1);
#else
#ifdef	BELL5
	ubmfree(sc->sc_ubinfo);
#endif
#endif
	fpsQout(FPSUNIT(dev),sc);
}

fpsinit(fpsunit)
  register fpsunit;
{
	register s;
	register struct fpsdevice *fpsaddr = (struct fpsdevice *) fpsdinfo[fpsunit]->ui_addr;
	register struct fps_softc *sc = &fps_softc[fpsunit];
	struct buf *bp = rfpsbuf[fpsunit].b_forw;

	s = SPLHI;
#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpsinit: fpsaddr = %o\n",fpsaddr);
#endif
#ifdef	GOULD
	fp_hio(Fp_mtd[fpsunit]->d_channel);
#endif
	fps_wr(fpsaddr->fpsrset,0);
#ifndef	GOULD
	fps_wr(fpsaddr->fpswc,0);
#endif
	if (sc->sc_mode & M_DINTR)
		fps_wr(fpsaddr->fpscsr,0);
	else	fps_wr(fpsaddr->fpscsr,CS_ONAPRQ);
	fps_wr(fpsaddr->fpsfn,FN_RESET);
	fps_wr(fpsaddr->fpslite,0);
#ifdef	PERKINELMER
	oc(fpsaddr,OC_IENB);
#endif
	sc->sc_mode &= ~M_WANYINT;
	if (sc->sc_ubinfo && bp) {
		bp->b_flags |= B_ERROR;
#ifdef	GOULD
		bp->b_resid = bp->b_bcount;
#else
		bp->b_resid = fps_rr(fpsaddr->fpswc);
#endif
		iodone(bp);
		}
	if (sc->sc_mode & M_WAITING)
		wakeup(&sc->sc_mode);
	splx(s);
}

#ifdef	V6
fpsgtty(dev, addr)
#else
fpsioctl(dev, cmd, addr, flag)
#endif
  caddr_t addr;
  dev_t dev;
{
	register fpsunit = FPSUNIT(dev);
	register int wanted;
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register struct fpsdevice *fpsaddr = (struct fpsdevice *)
						fpsdinfo[fpsunit]->ui_addr;
	int s;
#ifndef	BSD42
	u_short ibuf;
#endif
#ifdef	V6
	short	cmd;

	cmd = (short) u.u_arg[0];
	addr = (caddr_t) u.u_arg[1];
#endif
#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpsioctl: cmd = 0x%x\n",cmd);
#endif

	sc->sc_openf = u.u_procp;	/* in case of fork */
	if (fpserr(sc))
		return(u.u_error);

	s = SPLHI;
	if (sc->sc_ndone)
		fpsout(sc);

	switch (cmd) {
#ifdef	BSD42
		default:	/* Block I/O commands */
			if ((cmd & 0377) == (IO_BIO & 0377)) {
				if (fpsbio(sc,addr,dev)) {
					SPLHI;
					fpscmd(dev);
					spl0();
					}
				if (fpserr(sc))
					return(u.u_error);
				}
			else	return(u.u_error = EINVAL);
			break;
#else
		default:
			return(u.u_error = EINVAL);
		case IO_BIO:	/* Block I/O commands */
			if (fpsbio(sc,addr,dev)) {
				SPLHI;
				fpscmd(dev);
				spl0();
				}
			if (fpserr(sc))
				return(u.u_error);
			break;
#endif
		case IO_WD:	/* Synchronize host with AP DMA */
			wanted = M_WDMAINT;
			goto waitloop;
		case IO_WR:	/* Synchronize host with AP Running */
			wanted = M_WHALTINT;
			goto waitloop;
		case IO_SYNC:	/* Synchronize host with AP */
			wanted = M_WANYINT;
		waitloop:
			while (sc->sc_ccount || sc->sc_mode & wanted) {
				SPLHI;
				fpscmd(dev);
				spl0();
				if (fpserr(sc))
					return(u.u_error);
				SPLHI;
				if (sc->sc_ccount == 0  &&
						(sc->sc_mode & wanted) == 0)
					break;
#ifdef	GOULD
				fpswait(fpsunit,wanted);
#endif
				sc->sc_mode |= M_WAITING;
				sleep(&sc->sc_mode,PRIWAIT);
				SPLHI;
				sc->sc_mode &= ~M_WAITING;
				}
			if (fpserr(sc))
				return(u.u_error);
			break;
		case IO_FPSERR:	/* return EFPS error information */
#ifdef	BSD42
			*(u_short *)addr = sc->sc_fpserr;
#else
			if (copyout((caddr_t)(&sc->sc_fpserr),addr, sizeof(short)))
				return(u.u_error = EFAULT);
#endif
			sc->sc_fpserr = 0;
			break;
		case IO_RCSR:
#ifdef	BSD42
			*(u_short *)addr = fps_rr(fpsaddr->fpscsr);
#else
			ibuf = fps_rr(fpsaddr->fpscsr);
			if (copyout((caddr_t)(&ibuf),addr, sizeof(short)))
				return(u.u_error = EFAULT);
#endif
			break;
		case IO_RFN:
#ifdef	BSD42
			*(u_short *)addr = fps_rr(fpsaddr->fpsfn);
#else
			ibuf = fps_rr(fpsaddr->fpsfn);
			if (copyout((caddr_t)(&ibuf),addr, sizeof(short)))
				return(u.u_error = EFAULT);
#endif
			break;
		case IO_SETMODE:
			sc->sc_mode &= ~M_USERBITS;
#ifdef	BSD42
			sc->sc_mode |= (*(u_short *)addr) & M_USERBITS;
#else
			if (copyin(addr, (caddr_t) &ibuf,sizeof(short)))
				return(u.u_error = EFAULT);
			sc->sc_mode |= ibuf & M_USERBITS;
#endif
			if (sc->sc_mode & M_DINTR)
				fps_wr(fpsaddr->fpscsr,fps_rr(fpsaddr->fpscsr) & ~(CS_GO |
							CS_ONAPRQ));
			else	fps_wr(fpsaddr->fpscsr,fps_rr(fpsaddr->fpscsr) & ~CS_GO) |
							CS_ONAPRQ;
			break;
		case IO_GETMODE:
#ifdef	BSD42
			*(u_short *)addr = sc->sc_mode;
#else
			if (copyout((caddr_t)&sc->sc_mode,addr, sizeof(short)))
				return(u.u_error = EFAULT);
#endif
			break;
		case IO_RESET:	/* reset the AP */
			fpsinit(fpsunit);
			break;
		}
	if (sc->sc_ndone)
		fpsout(sc);
	splx(s);
	return(u.u_error);
}

fpserr(sc)
  register struct fps_softc *sc;
{
	if (sc->sc_eword) {
		u.u_error = sc->sc_eword;
		sc->sc_eword = 0;
		}
	return(u.u_error);
}

fpscmd(dev)
  dev_t dev;
{
	register fpsunit = FPSUNIT(dev);
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register struct fpsdevice *fpsaddr = (struct fpsdevice *)fpsdinfo[fpsunit]->ui_addr;
	register struct fps_iopb	*cptr;
	register spad;
	register struct buf *bp = &rfpsbuf[fpsunit];

	while (sc->sc_ccount) {
		if (sc->sc_eword) {
			sc->sc_ndone = sc->sc_ccount = 0;
			return;
			}
		cptr = ((struct fps_iopb *) (sc->sc_iocbase)) + sc->sc_cindex;
#ifdef	FPSDEBUG
		if (fpsdebug)
			fpsprint("bio",cptr);
#endif
		switch (cptr->pb_cmd) {
			case IOC_READREG:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				if (cptr->pb_apad < FPSLOW ||
						cptr->pb_apad > FPSHIGH) {
					sc->sc_eword = EINVAL;
					break;
					}
				cptr->pb_dcnt = fps_rr(*(u_short *)((char *)fpsaddr
					+ cptr->pb_apad));
				break;
			case IOC_WRITEREG:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				if (cptr->pb_apad < FPSLOW ||
						cptr->pb_apad > FPSHIGH) {
					sc->sc_eword = EINVAL;
					break;
					}
				if (cptr->pb_apad == FPSCSR)
					cptr->pb_dcnt &= ~CS_GO;
				fps_wr(*(u_short *)((char *)fpsaddr + cptr->pb_apad),
					cptr->pb_dcnt);
				break;
			case IOC_EXAM:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				fps_wr(fpsaddr->fpsfn,FN_EXAM | (cptr->pb_apad & S_MASK));
				cptr->pb_dcnt= fps_rr(fpsaddr->fpslite);
				break;
			case IOC_DEPOSIT:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				fps_wr(fpsaddr->fpsswtch,cptr->pb_dcnt);
				fps_wr(fpsaddr->fpsfn,FN_DEPOS | (cptr->pb_apad & S_MASK));
				break;
			case IOC_PUT:
				if (fpswait(fpsunit,(M_INTLEVEL | M_WDMAINT)))
					return;
				sc->sc_mode |= M_WDMAINT;
				fpsdma(fpsunit,cptr);
				fps_wr(fpsaddr->fpscsr,(fps_rr(fpsaddr->fpscsr) &
					~( CS_GO | CS_FORMAT)) | (CS_DMAENB |
					CS_HTOAP | (cptr->pb_fmt & CS_FORMAT)));
				fpsnext(sc);
#ifdef	BERK4
#ifdef	BSD42
				sc->sc_eword = physio(fpstrategy,bp,dev,B_WRITE,minphys,&fpsuio[fpsunit]);
#else
				physio(fpstrategy,bp,dev,B_WRITE,minphys);
#endif
#else
				physio(fpstrategy,bp,dev,B_WRITE);
#endif
				continue;
			case IOC_GET:
				if (fpswait(fpsunit,(M_INTLEVEL | M_WDMAINT)))
					return;
				sc->sc_mode |= M_WDMAINT;
				fpsdma(fpsunit,cptr);
				fps_wr(fpsaddr->fpscsr,(fps_rr(fpsaddr->fpscsr) &
					~(CS_GO | CS_FORMAT)) | (CS_DMAENB |
					CS_APTOH | (cptr->pb_fmt & CS_FORMAT)));
				fpsnext(sc);
#ifdef	BERK4
#ifdef	BSD42
				sc->sc_eword = physio(fpstrategy,bp,dev,B_READ,minphys,&fpsuio[fpsunit]);
#else
				physio(fpstrategy,bp,dev,B_READ,minphys);
#endif
#else
				physio(fpstrategy,bp,dev,B_READ);
#endif
				continue;
			case IOC_PSLOAD:
				if (fpswait(fpsunit,(M_INTLEVEL | M_WANYINT)))
					return;
				sc->sc_mode |= (M_WANYINT|M_PSLOAD);
				fpsdma(fpsunit,cptr);
				fps_wr(fpsaddr->fpscsr,(fps_rr(fpsaddr->fpscsr) &
					~(CS_GO | CS_FORMAT |
					CS_DMAENB)) | CS_HTOAP | PSL_FORMAT);
				fps_wr(fpsaddr->fpsswtch,cptr->pb_apad);
				fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_TMA);
				fps_wr(fpsaddr->fpsswtch,PSL_START);
				fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_PSA);
				fps_wr(fpsaddr->fpsswtch,cptr->pb_dcnt>>3);
				fps_wr(fpsaddr->fpsfn,FN_CONT);
				fpsnext(sc);
#ifdef	BERK4
#ifdef	BSD42
				sc->sc_eword = physio(fpstrategy,bp,dev,B_WRITE,minphys,&fpsuio[fpsunit]);
#else
				physio(fpstrategy,bp,dev,B_WRITE,minphys);
#endif
#else
				physio(fpstrategy,bp,dev,B_WRITE);
#endif
				continue;
			case IOC_SPLOAD:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				spad = cptr->pb_fmt & 017;
				fps_wr(fpsaddr->fpsswtch,spad++);
				fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_SPD);
				fps_wr(fpsaddr->fpsswtch,cptr->pb_apad);
				fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_SPRG);
				if (cptr->pb_fmt & IOF_TWOSP) {
					fps_wr(fpsaddr->fpsswtch,spad++);
					fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_SPD);
					fps_wr(fpsaddr->fpsswtch,(u_short) cptr->pb_had);
					fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_SPRG);
					}
				if (cptr->pb_fmt & IOF_THREESP) {
					fps_wr(fpsaddr->fpsswtch,spad);
					fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_SPD);
					fps_wr(fpsaddr->fpsswtch,cptr->pb_dcnt);
					fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_SPRG);
					}
				break;
			case IOC_GO:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				sc->sc_mode |= M_WHALTINT;
				fps_wr(fpsaddr->fpsswtch,cptr->pb_apad);
				fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_TMA);
				fps_wr(fpsaddr->fpsswtch,PSL_SYSSTART);
				fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_PSA);
#ifdef	FPSPARITY
				fps_wr(fpsaddr->fpsswtch,ST_PENB);
#else
				fps_wr(fpsaddr->fpsswtch,0);
#endif
				fps_wr(fpsaddr->fpsfn,FN_DEPOS | S_STATUS);
#ifdef	PERKINELMER
				oc(fpsaddr,OC_QINT);
				fps_wr(fpsaddr->fpscsr,(fps_rr(fpsaddr->fpscsr) & ~CS_GO)
					| CS_ONHALT);
#endif
				if (cptr->pb_dcnt) {
					fps_wr(fpsaddr->fpsswtch,--(cptr->pb_dcnt));
					fps_wr(fpsaddr->fpsfn,FN_CONT | FN_BREAK);
					}
				else	fps_wr(fpsaddr->fpsfn,FN_CONT);
#ifdef	PERKINELMER
				oc(fpsaddr,OC_IENB);
#else
#ifndef	GOULD
				fps_wr(fpsaddr->fpscsr,(fps_rr(fpsaddr->fpscsr) & ~CS_GO)
					| CS_ONHALT);
#endif
#endif
				break;
			case IOC_XCONT:		/* Continue AP */
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				sc->sc_mode |= M_WHALTINT;
#ifdef	PERKINELMER
				oc(fpsaddr,OC_QINT);
				fps_wr(fpsaddr->fpscsr,(fps_rr(fpsaddr->fpscsr) & ~CS_GO)
					| CS_ONHALT);
#endif
				fps_wr(fpsaddr->fpsfn,FN_CONT);
#ifdef	PERKINELMER
				oc(fpsaddr,OC_IENB);
#else
#ifndef	GOULD
				fps_wr(fpsaddr->fpscsr,(fps_rr(fpsaddr->fpscsr) & ~CS_GO)
					| CS_ONHALT);
#endif
#endif
				break;
			case IOC_WD:
				if (fpswait(fpsunit,M_WDMAINT))
					return;
				break;
			case IOC_WR:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				break;
			case IOC_RMAE:
				cptr->pb_dcnt = fps_rr(fpsaddr->fpsrset) & 017;
				break;
			case IOC_WMAE:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				fps_wr(fpsaddr->fpslite,(cptr->pb_dcnt & 017) |
					(fps_rr(fpsaddr->fpsrset) & 0177760));
				break;
			case IOC_RAPMAE:
				cptr->pb_dcnt = (fps_rr(fpsaddr->fpsrset)>>4) & 017;
				break;
			case IOC_WAPMAE:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				fps_wr(fpsaddr->fpslite,((cptr->pb_dcnt & 017)<<4) |
					(fps_rr(fpsaddr->fpsrset) & 0177417));
				break;
			case IOC_RMSK:
				cptr->pb_dcnt = (fps_rr(fpsaddr->fpsrset)>>8) & 077;
				break;
			case IOC_WMSK:
				if (fpswait(fpsunit,M_WHALTINT))
					return;
				fps_wr(fpsaddr->fpslite,((cptr->pb_dcnt & 077)<<8) |
					(fps_rr(fpsaddr->fpsrset) & 0140377));
				break;
			default:
				sc->sc_eword = EIO;
				return;
			}
		fpsnext(sc);
		}
}

fpsnext(sc)
  register struct fps_softc *sc;
{
	sc->sc_ccount--;
	sc->sc_ndone++;
	sc->sc_cindex++;
#ifdef	BSD42
	sc->sc_cindex %= KFPSCOM;
#else
	sc->sc_cindex %= NFPSCOM;
#endif
}

fpsbio(sc,addr,dev)
  register struct fps_softc *sc;
  caddr_t addr;
  dev_t dev;
{
	register in;
	int	count;

#ifdef	BSD42
	count = *(int *)addr;
#else
	if (copyin(addr, (caddr_t) &count,sizeof(int))) {
		u.u_error = EFAULT;
		return(0);
		}
#endif
#ifdef	BSD42
	if (count > KFPSCOM) {
#else
	if (count > NFPSCOM) {
#endif
		u.u_error = EINVAL;
		return(0);
		}
	addr += sizeof(int);
	if (sc->sc_ccount == 0) {
		sc->sc_cindex = sc->sc_dindex = 0;
#ifdef	BSD42
		bcopy(addr,sc->sc_iocbase, count * sizeof(struct fps_iopb));
#else
		if (copyin(addr, sc->sc_iocbase, count * sizeof(struct fps_iopb))) {
			u.u_error = EFAULT;
			return(0);
			}
#endif
		sc->sc_ccount = count;
		}
	else	{
#ifdef	BSD42
		while (count > (KFPSCOM - sc->sc_ccount - sc->sc_ndone)) {
#else
		while (count > (NFPSCOM - sc->sc_ccount - sc->sc_ndone)) {
#endif
			SPLHI;
			fpscmd(dev);
			spl0();
			if (u.u_error || sc->sc_eword)
				return(0);
			if (sc->sc_ndone)
				fpsout(sc);
			if (u.u_error || sc->sc_eword)
				return(0);
#ifdef	BSD42
			if (count <= (KFPSCOM - sc->sc_ccount - sc->sc_ndone))
#else
			if (count <= (NFPSCOM - sc->sc_ccount - sc->sc_ndone))
#endif
				break;
			sc->sc_mode |= M_WAITING;
			sleep(&sc->sc_mode,PRIWAIT);
			SPLHI;
			sc->sc_mode &= ~M_WAITING;
			}
#ifdef	BSD42
		in = (sc->sc_cindex + sc->sc_ccount) % KFPSCOM;
#else
		in = (sc->sc_cindex + sc->sc_ccount) % NFPSCOM;
#endif
		sc->sc_ccount += count;
		while (count--) {
#ifdef	BSD42
			bcopy(addr,(caddr_t) (sc->sc_iocbase + 
				sizeof(struct fps_iopb) * in), sizeof(struct fps_iopb));
#else
			if (copyin(addr,(caddr_t) (sc->sc_iocbase + 
				sizeof(struct fps_iopb) * in), sizeof(struct fps_iopb))) {
				u.u_error = EFAULT;
				return(0);
				}
#endif
			in++;
#ifdef	BSD42
			in %= KFPSCOM;
#else
			in %= NFPSCOM;
#endif
			addr += sizeof(struct fps_iopb);
			}
		}
	return(1);
}

fpsout(sc)
  register struct fps_softc *sc;
{
	register struct fps_iopb *cptr;
	register done;

	done = sc->sc_ndone;
	while (done--) {
		cptr = ((struct fps_iopb *) (sc->sc_iocbase)) + sc->sc_dindex;
		if (cptr->pb_fmt == IOF_OUT) {
			if (copyout((caddr_t) &cptr->pb_dcnt, cptr->pb_had,
					sizeof(short))) {
				u.u_error = EFAULT;
				return;
				}
			}
		sc->sc_dindex++;
#ifdef	BSD42
		sc->sc_dindex %= KFPSCOM;
#else
		sc->sc_dindex %= NFPSCOM;
#endif
		}
	sc->sc_ndone = 0;
}

#ifdef	PERKINELMER
/*
 * This routine is necessary as P-E UNIX passes the selch number
 * and not the device number to the selch interrupt routine.
 * Therefore we must keep track of what device is currently active.
 */
fpselch(selno)
{
	register int fpsunit = fpsactive[selno];
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register int slchad = fpsselch[fpsunit];

	oc(slchad,STOP);
	ss(slchad);
	fpsint(fpsunit,SS_SELCH);
}
#endif

#define HALT_INTR	01
#define DMA_INTR	02
#define AP_INTR		04

#ifndef	GOULD
#ifdef	BELL4
fpsintr(fpsunit)
#else
#ifdef	PERKINELMER
fpsint(fpsunit,status)
#else
fpsint(fpsunit)
#endif
#endif
  register fpsunit;
{
	register u_short csrset;
	int	intgrp;
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register struct uba_device *ui = fpsdinfo[fpsunit];
	register struct fpsdevice *fpsaddr = (struct fpsdevice *)ui->ui_addr;
	struct buf *bp = rfpsbuf[fpsunit].b_forw;

#ifdef	PERKINELMER
	if (!(status & SS_SELCH))
		oc(fpsaddr,OC_QINT);
#endif
	intgrp = 0;
	csrset = fps_rr(fpsaddr->fpscsr) & ~CS_GO;

#ifdef	PERKINELMER
	if (status & SS_HALT && (fps_rr(fpsaddr->fpsfn) & FN_HALTED)) {
#else
	if ((fps_rr(fpsaddr->fpsfn) & FN_HALTED) && (csrset & CS_ONHALT)) {
#endif
		intgrp |= HALT_INTR;
		csrset &= ~CS_ONHALT;
		sc->sc_mode &= ~M_WHALTINT;
		/*
		 *  Check for status errors unless in diagnostic mode
		 */
		if (!(sc->sc_mode & M_NOCHK)) {
			fps_wr(fpsaddr->fpsfn,FN_EXAM | S_STATUS);
			if ((sc->sc_fpserr = fps_rr(fpsaddr->fpslite) & (ST_SRAO | ST_PERR)))
				sc->sc_eword = EFPS;
			}
		}

#ifdef	PERKINELMER
	if (status & SS_SELCH) {
#else
	if ((csrset & CS_ONZERO) && (csrset & (CS_WCZERO|CS_DLATE))) {
#endif
		intgrp |= DMA_INTR;
		csrset &= ~CS_ONZERO;
#ifdef	BELL4
#ifdef	vax
		ubapurge(umdbdp(sc->sc_ubinfo));
#endif
#endif
		if (csrset & CS_DLATE) {
#ifdef	BERK4
			printf("fps%d: csr=%b fn=0%b errcnt=%d wc=0%o\n",
			 fpsunit,fps_rr(fpsaddr->fpscsr),CS_BITS,fps_rr(fpsaddr->fpsfn),
			 FN_BITS, sc->sc_errcnt,fps_rr(fpsaddr->fpswc));
#else
			printf("fps%d: DLT csr=0%o fn=0%o errcnt=%d wc=0%o\n",
			 fpsunit,csrset,fps_rr(fpsaddr->fpsfn),sc->sc_errcnt,
			 fps_rr(fpsaddr->fpswc));
			fps_wr(fpsaddr->fpsrset,0);
#ifdef	PERKINELMER
			fps_wr(fpsaddr->fpsifsr,0);
#endif
#endif
			if (sc->sc_errcnt++ < 10) {
				fpstart(fpsunit);
#ifndef	PERKINELMER
				csrset |= CS_ONZERO;
#endif
				intgrp &= ~DMA_INTR;
				goto goon;
				}
			else	bp->b_flags |= B_ERROR;
			bp->b_resid = fps_rr(fpsaddr->fpswc);
			}
		if (sc->sc_mode & M_PSLOAD)
			sc->sc_mode &= ~(M_WANYINT|M_PSLOAD);
		else	sc->sc_mode &= ~M_WDMAINT;
		iodone(bp);
		}
#ifdef	PERKINELMER
	if (status & SS_CTL5) {
#else
	if (!intgrp && csrset & CS_ONAPRQ) {
#endif
		/*
		 * Clear the AP interrupt
		 */
#ifndef	PERKINELMER
		fps_wr(fpsaddr->fpsfn,0);
#endif
		psignal(sc->sc_openf,SIGFPS);
		intgrp |= AP_INTR;
		}
/*
 *	If AP software interrupt comes up during
 *	wait for other interrupts, the interrupt 
 *	hardware can jam unless all interrupt 
 *	flags are cleared.
 */
goon:
#ifdef	PERKINELMER
	if (intgrp & (HALT_INTR|AP_INTR)) {
#else
	if (intgrp & (HALT_INTR|DMA_INTR|AP_INTR)) {
#endif
		fps_wr(fpsaddr->fpscsr,csrset & ~(CS_ONHALT | CS_ONZERO | CS_ONAPRQ));
		fps_wr(fpsaddr->fpscsr,csrset);
		}

#ifdef	PERKINELMER
	oc(fpsaddr,OC_IENB);
#endif
	if (intgrp & (HALT_INTR|DMA_INTR)) {
		sc->sc_mode |= M_INTLEVEL;
		fpscmd(fpsunit);
		sc->sc_mode &= ~M_INTLEVEL;
		if (sc->sc_mode & M_WAITING)
			wakeup(&sc->sc_mode);
		}
}
#endif

fpsdma(fpsunit,cptr)
  register fpsunit;
  register struct fps_iopb *cptr;
{
#ifdef	BSD42
	register struct uio *fuio = &fpsuio[fpsunit];
	register struct iovec *fiov = &fpsiov[fpsunit];
#endif

#ifdef	BSD42
	fiov->iov_base = (caddr_t) cptr->pb_had;
	fiov->iov_len = cptr->pb_dcnt;
	fuio->uio_iov = fiov;
	fuio->uio_iovcnt = 1;
	fuio->uio_offset = dbtob(cptr->pb_apad);
	fuio->uio_segflg = fuio->uio_resid = 0;
#else
	u.u_base = (caddr_t) cptr->pb_had;
	u.u_count = cptr->pb_dcnt;
	u.u_segflg = 0;
#ifdef	V6
	u.u_offset[0] = (cptr->pb_apad >> 7) & 0777;
	u.u_offset[1] = cptr->pb_apad << PGSHIFT;
#else
	u.u_offset = (off_t) cptr->pb_apad << PGSHIFT;
#endif
#endif
}

fpstrategy(bp)
  register struct buf *bp;
{
	register fpsunit = FPSUNIT(bp->b_dev);
	register struct fps_softc *sc = &fps_softc[fpsunit];
#ifdef	BERK4
	register struct uba_device *ui = fpsdinfo[fpsunit];
#endif

#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpstrategy\n");
#endif
#ifdef	LONGWORDALIGN
	if ((((int) (bp->B_ADDR)) & 03) || bp->b_bcount & 03) {
		bp->b_flags |= B_ERROR;
		sc->sc_eword = EINVAL;
		iodone(bp);
		return;
		}
#endif
	while (fpswait(fpsunit,M_DMABUSY)) {
		SPLHI;
		sc->sc_mode |= M_DMAWAIT;
		spl0();
		sleep(sc->sc_header,PRIWAIT);
		SPLHI;
		sc->sc_mode &= ~M_DMAWAIT;
		}
	SPLHI;
	sc->sc_mode |= M_DMABUSY;
	spl0();
	rfpsbuf[fpsunit].b_forw = bp;
#ifndef	BELL4
#ifndef	BERK4
	mapalloc(bp);
#endif
#endif
#ifndef	BELL4
#ifdef	BERK4
#ifndef	GOULD
	sc->sc_ubinfo = ubasetup(ui->ui_ubanum, bp, UBA_NEEDBDP);
#endif
#else
	sc->sc_ubinfo = UBASETUP(bp, 1);
#endif
#endif

	sc->sc_errcnt = 0;
#ifdef	PERKINELMER
	selchreq(fpsselch[fpsunit],&fpsscq[fpsunit],fpsunit);
#else
	fpstart(fpsunit);
#endif
	while (!(bp->b_flags & B_DONE))
		sleep(bp,PRIFPS);
	SPLHI;

#ifndef	BELL4
#ifdef	BERK4
#ifndef	GOULD
	if (sc->sc_ubinfo)
		ubarelse(ui->ui_ubanum, &sc->sc_ubinfo);
#endif
#else
	ubafree(sc->sc_ubinfo);
#endif
	sc->sc_ubinfo = 0;
#endif
	SPLHI;
	sc->sc_mode &= ~M_DMABUSY;
	spl0();
	if (sc->sc_mode & M_DMAWAIT)
		wakeup(sc->sc_header);
}

#ifndef	GOULD
fpstart(fpsunit)
  register fpsunit;
{
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register struct fpsdevice *fpsaddr = (struct fpsdevice *) fpsdinfo[fpsunit]->ui_addr;
	register struct buf *bp = rfpsbuf[fpsunit].b_forw;
#ifdef	BELL4
	paddr_t	addr;
#endif
#ifdef	PERKINELMER
	int fmt;
	int slchad = fpsselch[fpsunit];
#endif

#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpstart(%d)\n",fpsunit);
#endif
	SPLHI;
#ifdef	PERKINELMER
	oc(fpsaddr,OC_QINT);
	fpsactive[slchad - 0xF0] = fpsunit;
	oc(slchad,STOP);
	fps_wr(fpsaddr->fpsapad,(u_short) bp->b_blkno);
	fmt = fps_rr(fpsaddr->fpscsr) & CS_FORMAT;
	if (fmt == 04)
		fps_wr(fpsaddr->fpscsr,(fps_rr(fpsaddr->fpscsr) | 02) & ~CS_GO);
	if (fmt == 02)
		fps_wr(fpsaddr->fpswc,bp->b_bcount>>1);
	else	fps_wr(fpsaddr->fpswc,bp->b_bcount>>2);
#else
#ifdef	BELL4
	fps_wr(fpsaddr->fpsapad,(u_short) bp->b_blkno);
	fps_wr(fpsaddr->fpswc,bp->b_bcount>>1);
	addr = ubmaddr(bp, sc->sc_ubinfo);
	fps_wr(fpsaddr->fpshad,loword(addr));
	fps_wr(fpsaddr->fpslite,(hiword(addr)<<14) | (fps_rr(fpsaddr->fpsrset) & 0037777));
#else
#ifdef	vax
	fps_wr(fpsaddr->fpsapad,bp->b_blkno);
	fps_wr(fpsaddr->fpswc,bp->b_bcount>>1);
	fps_wr(fpsaddr->fpshad,sc->sc_ubinfo);
	fps_wr(fpsaddr->fpslite,((sc->sc_ubinfo & 0x30000)>>2) | (fps_rr(fpsaddr->fpsrset) & 0037777));
#else
	fps_wr(fpsaddr->fpsapad,bp->b_blkno);
	fps_wr(fpsaddr->fpshad,(u_short) bp->B_ADDR);
#ifdef	V6
	fps_wr(fpsaddr->fpswc,-bp->b_wcount);
#else
	fps_wr(fpsaddr->fpswc,bp->b_bcount>>1);
#endif
	fps_wr(fpsaddr->fpslite,(bp->b_xmem<<14) | (fps_rr(fpsaddr->fpsrset) & 0037777));
#endif
#endif
#endif
	fps_wr(fpsaddr->fpscsr,fps_rr(fpsaddr->fpscsr) & 
		(CS_ONHALT|CS_DMAENB|CS_FORMAT|CS_ONAPRQ));
	fps_wr(fpsaddr->fpscsr,fps_rr(fpsaddr->fpscsr) | (CS_GO | CS_CC) |
		((bp->b_flags & B_READ)? CS_APTOH : CS_HTOAP));
#ifdef	PERKINELMER
	oc(slchad,STOP);
	wdh(slchad,bp->B_ADDR);
	wdh(slchad,bp->B_ADDR + bp->b_bcount - 1);
	oc(slchad,bp->b_flags & B_READ ? READ_GO : GO);
#else
	fps_wr(fpsaddr->fpscsr,CS_ONZERO | (fps_rr(fpsaddr->fpscsr) & ~CS_GO));
#endif
}
#endif

#ifdef	FPSRESET
fpsreset(uban)
  int uban;
{
	register int fpsunit;
	register struct uba_device *ui;
	register struct fps_softc *sc = fps_softc;

	for (fpsunit = 0; fpsunit < NFPS; fpsunit++, sc++) {
		if ((ui = fpsdinfo[fpsunit]) == 0 || ui->ui_alive == 0 ||
#ifdef	BERK4
		    ui->ui_ubanum != uban || 
#endif
		    sc->sc_openf == 0)
			continue;
		printf(" fps%d", fpsunit);
		sc->sc_eword = EIO;
		fpsinit(fpsunit);
#ifdef	BERK4
#ifdef	BSD42
		sc->sc_ubinfo = 0;
#else
		if (sc->sc_ubinfo) {
			printf("<%d>", (sc->sc_ubinfo>>28)&0xf);
			ubarelse(ui->ui_ubanum, &sc->sc_ubinfo);
			sc->sc_ubinfo = 0;
			}
#endif
#endif
		}
}
#endif
#ifdef	FPSDEBUG
fpsprint(str,cptr)
  char	*str;
  register struct fps_iopb *cptr;
{
	printf("%s: ",str);
	printf("cmd: %o ",cptr->pb_cmd);
	printf("fmt: %o ",cptr->pb_fmt);
	printf("apad: %o ",cptr->pb_apad);
	printf("had: 0x%x ",cptr->pb_had);
	printf("dcnt: %o\n",cptr->pb_dcnt);
}
#endif

fpsQopen(dev)
  dev_t	dev;
{
	register struct fpsQent	*qp;
	register int fpsunit;

	if (FPSUNIT(dev) > 0)
		return(u.u_error = ENXIO);
#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpsQopen\n");
#endif
	if (fq_Qlist.q_forward == NULL && fq_Qfree.q_forward == NULL) {
#ifndef	BERK4
		for (fpsunit = 0; fpsunit < NFPS; fpsunit++) {
#ifdef	BELL4
			fpsconf[fpsunit].ui_addr = (caddr_t) fps_addr[fpsunit];
#endif
#ifdef	PERKINELMER
#undef fpsaddr
			fpsconf[fpsunit].ui_addr = (caddr_t) ((char)(fpsaddr[fpsunit]));
			fpsconf[fpsunit].ui_alive = (ss(fpsaddr[fpsunit]) & SS_DU) ? 0 : 1;
			fpsscq[fpsunit].sq_sstart = fpstart;
			fpsscq[fpsunit].sq_sintr = fpselch;
#endif
			fpsdinfo[fpsunit] = &fpsconf[fpsunit];
			}
#endif
		for (qp = fq_Qent; qp < (fq_Qent + NFPSQ - 1); qp++)
			qp->q_forward = qp + 1;
		fq_Qfree.q_forward = fq_Qent;
		fq_Qlist.q_back = &fq_Qlist;
		}
	return(u.u_error);
}

fpsQclose(dev)
  dev_t dev;
{
}

#ifdef	V6
fpsQgtty(dev, addr)
#else
fpsQioctl(dev, action, addr, flag)
#endif
  caddr_t addr;
  dev_t dev;
{
	register i;
	short	apno;
#ifdef	V6
	short	action;

	action = (short) u.u_arg[0];
	addr = u.u_arg[1];
#endif
#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpsQioctl: action = 0x%x\n",action);
#endif

#ifdef	BSD42
	apno = *(short *) addr;
#else
	if (copyin(addr, (caddr_t) &apno,sizeof(short)))
		return(u.u_error = EFAULT);
#endif

	for (i = 0; i < NFPS; i++)
		if (fps_softc[i].sc_openf == u.u_procp) {
			if (apno == 0)
				apno = i+1;
			if (apno != (i+1))
				apno = -3;
			goto out;
			}
	if (apno && (apno > NFPS || fpsdinfo[apno-1]->ui_alive == 0))
		apno = -2;
	else	switch (action) {
			case IOQ_WAIT:
				if (apno) {
					if (fps_softc[apno-1].sc_openf)
						fpsQin(u.u_procp,u.u_procp->p_pid,apno);
					}
				else	{
					for (i = 0; i < NFPS; i++)
						if (!fps_softc[i].sc_openf) {
							apno = i+1;
							goto out;
							}
					apno = fpsQin(u.u_procp,u.u_procp->p_pid,apno);
					}
				break;
			case IOQ_NOWAIT:
				if (apno) {
					if (fps_softc[apno-1].sc_openf)
					apno = -1;
					}
				else	{
					apno = -2;
					for (i = 0; i < NFPS; i++) {
						if (fpsdinfo[i]->ui_alive)
							apno = -1;
						if (!fps_softc[i].sc_openf) {
							apno = i+1;
							break;
							}
						}
					}
				break;
			default:
				apno = -4;
				break;
			}
out:
#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("apno = %d\n",apno);
#endif
#ifdef	BSD42
	*(short *)addr = apno;
#else
	if (copyout((caddr_t) &apno, addr, sizeof(short)))
		u.u_error = EFAULT;
#endif
	return(u.u_error);
}

fpsQin(procp,pid,apno)
  struct proc	*procp;
  unsigned int	pid;
  unsigned int	apno;
{
	register struct fpsQent	*qp;
	register int i;

	spl7();
	if ((qp = fq_Qfree.q_forward) == NULL) {
		u.u_error = EBUSY;
		return(0);
		}
	fq_Qfree.q_forward = qp->q_forward;
	qp->q_procp = procp;
	qp->q_pid = pid;
	qp->q_apno = apno;
	fq_Qlist.q_back->q_forward = qp;
	qp->q_back = fq_Qlist.q_back;
	fq_Qlist.q_back = qp;
	qp->q_forward = NULL;
	spl0();
	sleep(qp,PRIWAIT);
	for (i = 0; i < NFPS; i++)
		if (fps_softc[i].sc_openf == u.u_procp)
			return(i+1);
	u.u_error = EBUSY;
	return(0);
}

fpsQout(fpsunit,sc)
  register fpsunit;
  register struct fps_softc *sc;
{
	register struct fpsQent	*qp;

	spl7();
	fpsunit++;
recal:
	for (qp = fq_Qlist.q_forward; qp != NULL; qp = qp->q_forward) {
		if (qp->q_apno == 0 || qp->q_apno == fpsunit) {
			qp->q_back->q_forward = qp->q_forward;
			if (qp->q_forward == NULL)
				fq_Qlist.q_back = qp->q_back;
			else	qp->q_forward->q_back = qp->q_back;
			qp->q_forward = fq_Qfree.q_forward;
			fq_Qfree.q_forward = qp;
			if (qp->q_procp->p_pid != qp->q_pid)
				goto recal;
#ifdef	BERK4
			/*
			 * If candidate is stopped issue the wakeup
			 * but let someone else have the AP.  He will
			 * return to the queue once boucing back through
			 * apex (after the EBUSY) after he is no longer
			 * blocked.
			 */
			if (qp->q_procp->p_stat == SSTOP) {
				wakeup(qp);
				goto recal;
				}
#endif
			sc->sc_openf = qp->q_procp;
			wakeup(qp);
			spl0();
			return;
			}
		}
	sc->sc_openf = 0;
	spl0();
}
#ifdef	GOULD
fpsint(notused,dpti)
  int notused;
  int dpti;
{
	extern dptT	Dpt[];
	dptT	*dptp = &Dpt[dpti];
	dcbT	*dcbp = dptp->dp_srtp[0];
	register int fpsunit = FPSUNIT(dcbp->d_dev);
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register struct si *sp;
	register int count = 0;
	register int resid = 0;
	int i,n;
	struct iocb *iocb_adr;
	struct buf *bp = rfpsbuf[fpsunit].b_forw;

	sp = (struct si *) (fpdinfo[fpsunit].adrtaw);
	if (sc->sc_mode & M_HSDREGIO) {
		sc->sc_ubinfo = fpdinfo[fpsunit].tmp[0].ioc_devstat;
		sc->sc_mode &= ~M_HSDREGIO;
		wakeup(&sc->sc_ubinfo);
		return;
		}
	if (sc->sc_mode & M_DMABUSY) {
		if (sp->status == 0 || ((sp->status & IOCB_DONE) &&
				((sp->status & IOCL_DONE) == 0)))
			return;
		resid = WTOB((int)(*(int *)(sp->curiocbadr) & RESMASK));
		iocb_adr = (struct iocb *)(sp->curiocbadr - 12);
		n = (iocb_adr - &(fpdinfo[fpsunit].iocl[2]));
		for (i=2; i<=n; i++) 
			count += fpdinfo[fpsunit].iocl[i].ioc_wc;
		count = WTOB(count);
		resid += bp->b_bcount - count;
		bp->b_resid = resid;
		if (sc->sc_mode & M_PSLOAD)
			sc->sc_mode &= ~(M_WANYINT|M_PSLOAD);
		else	sc->sc_mode &= ~M_WDMAINT;
		iodone(bp);
		}
	else	if (sc->sc_mode & M_WHALTINT) {
			sc->sc_mode &= ~M_WHALTINT;
			}
		else	if (sc->sc_mode & M_WAPINT) {
				psignal(sc->sc_openf,SIGFPS);
				sc->sc_mode &= ~M_WAPINT;
				}
	sc->sc_mode &= ~M_HSDBUSY;
	if (sc->sc_mode & M_WAITING)
		wakeup(&sc->sc_mode);
}

fpstart(fpsunit)
  register int fpsunit;
{
	register struct fps_softc *sc = &fps_softc[fpsunit];
	register struct fpsdevice *fpsaddr = (struct fpsdevice *) fpsdinfo[fpsunit]->ui_addr;
	register struct buf *bp = rfpsbuf[fpsunit].b_forw;
	register int *taddr;
	struct iocb *ioclp;
	struct iocb *dest_ioclp;
	int rslt;
	short csr;

#ifdef	FPSDEBUG
	if (fpsdebug)
		printf("fpstart\n");
#endif

	csr = fps_rr(fpsaddr->fpscsr);
	/*
	 *	Build the IOCB.
	 */
	dest_ioclp = &(fpdinfo[fpsunit].iocl[0]); 
	taddr = (int *)fpdinfo[fpsunit].adrtaw;
	*taddr = (int)dest_ioclp;
	dest_ioclp->ioc_opcode = CXFER | CCHAIN;
	dest_ioclp->w1.ioc_devcmd = bp->b_blkno;
	dest_ioclp->ioc_wc = 1;
	dest_ioclp->ioc_info = FPSAPAD | (fpsunit<<5);
	dest_ioclp = &(fpdinfo[fpsunit].iocl[1]); 
	dest_ioclp->ioc_opcode = CXFER | CCHAIN;
	dest_ioclp->w1.ioc_devcmd = csr | CS_CC | CS_GO;
	dest_ioclp->ioc_wc = 1;
	dest_ioclp->ioc_info = FPSCSR | (fpsunit<<5);
	ioclp = &(fpdinfo[fpsunit].tmp[0]);
	ioclp->ioc_devstat = 0;
	ioclp->ioc_opcode = INTEOB;
	if (bp->b_flags&B_READ) 
		ioclp->ioc_opcode |= IDXFER;
	ioclp->ioc_info = FPSFLOW | (fpsunit<<5);
	ioclp->w1.format_a.ioc_addr = (int)bp->b_un.b_addr;
	ioclp->ioc_wc = (bp->b_bcount + 3) >> 2;
	rslt = fp_phys(ioclp,&(fpdinfo[fpsunit].iocl[2]), HSD_MAXIOCL-2, bp->b_proc);
	if (rslt != 0) {
		bp->b_flags |= B_ERROR;
		bp->b_error = rslt;
		iodone(bp);
		}
	else 	{
		fp_sio(Fp_mtd[fpsunit]->d_channel);
		sc->sc_mode |= M_HSDBUSY;
		}
}

fps_grr(fpsunit,addr)
  register int fpsunit;
  int addr;
{
	register struct iocb *ioclp;
	register int *taddr;
	register struct fps_softc *sc = &fps_softc[fpsunit];

#ifdef	FPSDEBUG
	if (fpsdebug & 2)
		printf("unit - %d addr = %d\n",fpsunit,addr);
#endif
	ioclp = &(fpdinfo[fpsunit].tmp[0]);
	ioclp->ioc_devstat = 0;
	ioclp->ioc_wc = 1;
	ioclp->ioc_opcode = STATRQ | INTEOB;
	ioclp->ioc_info = addr | (fpsunit<<5);
	taddr = (int *) fpdinfo[fpsunit].adrtaw;
	*taddr = (int) ioclp;
	fp_sio(Fp_mtd[fpsunit]->d_channel);
	sc->sc_mode |= M_HSDREGIO;
	while (sc->sc_mode & M_HSDREGIO) {
		sleep(&sc->sc_ubinfo,PRIWAIT);
		SPLHI;
		}
#ifdef	FPSDEBUG
	if (fpsdebug & 2)
		printf("ret 0x%x 0%o\n",sc->sc_ubinfo,sc->sc_ubinfo & 0xffff);
#endif
	return(sc->sc_ubinfo & 0xffff);
}

fps_gwr(fpsunit,addr,data)
  register int fpsunit;
  int addr,data;
{
	register struct iocb *ioclp;
	register int *taddr;
	register struct fps_softc *sc = &fps_softc[fpsunit];

#ifdef	FPSDEBUG
	if (fpsdebug & 2)
		printf("unit - %d addr = %d data = 0%o\n",fpsunit,addr,data);
#endif
	ioclp = &(fpdinfo[fpsunit].tmp[0]);
	ioclp->ioc_devstat = 0;
	ioclp->ioc_wc = 1;
	ioclp->ioc_opcode = CXFER | INTEOB;
	ioclp->w1.ioc_devcmd = data;
	ioclp->ioc_info = addr | (fpsunit<<5);
	taddr = (int *) fpdinfo[fpsunit].adrtaw;
	*taddr = (int) ioclp;
	fp_sio(Fp_mtd[fpsunit]->d_channel);
	sc->sc_mode |= M_HSDREGIO;
	while (sc->sc_mode & M_HSDREGIO) {
		sleep(&sc->sc_ubinfo,PRIWAIT);
		SPLHI;
		}
}

fpswait(fpsunit,mode)
  register int fpsunit;
  register int mode;
{
	register struct iocb *ioclp;
	register int *taddr;
	register struct fps_softc *sc = &fps_softc[fpsunit];

	if ((mode & (M_WHALTINT | M_WAPINT)) && (sc->sc_mode & mode) &&
			((sc->sc_mode & M_HSDBUSY) == 0)) {
		ioclp = &(fpdinfo[fpsunit].tmp[0]);
		ioclp->ioc_devstat = ioclp->ioc_wc = 0;
		ioclp->ioc_opcode = STATRQ | INTEOB;
		if (mode & M_WHALTINT)
			ioclp->ioc_info = FPSFN | (fpsunit<<5) | HSDM_HALTINT;
		else	ioclp->ioc_info = FPSFN | (fpsunit<<5) | HSDM_APINT;
		taddr = (int *) fpdinfo[fpsunit].adrtaw;
		*taddr = (int) ioclp;
		fp_sio(Fp_mtd[fpsunit]->d_channel);
		sc->sc_mode |= M_HSDBUSY;
		}
	return(mode & sc->sc_mode);
}

int fp_index;

fp_init()
{

	register int ilvl;
	register int adr;
	register int *taddr;
	short	 int chadr;

	iocd *iocdp = (iocd *)IOCDWORK;

	chadr = (Fp_mtd[fp_index]->d_channel >> 8);
	for (ilvl = MINRELPRIO; ilvl<=MAXRELPRIO; ilvl++) {
		if (scr_int[ilvl].field.chnladr == chadr)
			break;
	}
	if (scr_int[ilvl].field.chnladr != chadr) {
		printf("fp:  init - controller fp%x at addr 0x%x not configured\n", fp_index, Fp_mtd[fp_index]->d_channel); 
		fp_index++;
		return;
	}
	printf("fp:  init - controller fp%x at addr 0x%x online\n", fp_index, Fp_mtd[fp_index]->d_channel);
	adr = ESCRATCH+(ilvl-4)*4;
	(iocdp+(ilvl-4))->e_io.tcwadr = adr;
	(int)(fpdinfo[fp_index].adrtaw) = adr;
	taddr = (int *)adr;
	*taddr = 0x0;
	fpsdinfo[fp_index]->ui_alive = 1;
	fpsdinfo[fp_index]->ui_addr = 0;
	fpdinfo[fp_index].hs_state |= INITED;
	Fp_mtd[fp_index]->d_priv = (int)&fps_softc[fp_index];
	fp_index++;
	fp_ei(ilvl);
}

fp_phys(proto_ioclp, dest_ioclp, dest_len, procp)
struct iocb	*proto_ioclp;
struct iocb	*dest_ioclp;
int	dest_len;
struct  proc	*procp;	
{
	struct iocb orig_iocb;
	struct iocb my_iocb;
	struct iocb *myp;
	struct iocb *sp;
	struct iocb *dp;
	int flags;
	int pcnt;		/* count of physical iocb's created */
	int ucnt;
	int virt;		/* user's virtual address */
	int real;		/* user's real address */
	int cnt_eop;		/* count to end of contiguous page(s) */
	int newvirt;		/* new virtual address */

	/*
	 * Loop until the source IOCL is exhausted
	 */

	sp = proto_ioclp;
	dp = dest_ioclp;
	myp = & my_iocb;
	pcnt = 0;

	/*
	 * until all input IOCB's are copied 
	 */

	do {
		if (pcnt > dest_len) {
			printf("fps: phys - IO program too long");
			return(EINVAL);
		}
		my_iocb = *sp;
		orig_iocb = *sp++;	/* saved copy, for blding new */
		ucnt = WTOB(myp->ioc_wc);	/* user's requested count */
		virt = myp->w1.format_a.ioc_addr;	/* user's virtual address */
		flags = (myp->ioc_opcode & IDXFER) ? PIO_READ : PIO_WRITE;
		/*
		 * loop until count is exhausted
		 */

		for (;;) {
			pcnt++;		/* count another IOCB */
			/*
			 * obtain real address
			 */
			real = pvtophys (procp, virt, flags);
			if (real == -1)
				return (EFAULT);

			/*
			 * obtain first address of next page in
			 * user's virtual address space, and length
			 * to get there
			 */
			newvirt = (virt + PAGESIZE) & ~(PAGESIZE - 1);
			cnt_eop = newvirt - virt;
			myp->w1.format_a.ioc_addr = real;  /* store phys addr */

			/*
			 * store user's count, and break out of
			 * loop if done
			 */
			if (cnt_eop >= ucnt) {
				myp->ioc_wc =  BTOW(ucnt);
				*dp++ = my_iocb;	/* store IOCB */
				break;
			}
			else 
				myp->ioc_wc =  BTOW(cnt_eop);

			/*
			 * (additional) data chaining will be required
			 */

			if (pcnt == dest_len) {
				printf("fps: phys - IO program too long");
				return(EINVAL);
			}
			myp->ioc_opcode |= DCHAIN;
			*dp++ = my_iocb;	/* store IOCB */

			/*
			 * setup for building next IOCB
			 */
			my_iocb = orig_iocb; /* get orig IOCB */
			virt += cnt_eop; /* update user's virt addr */
			ucnt -= cnt_eop; /* update user's cnt */
		}

	/*
	 * break out of loop if channel program chain bit not set
	 */
	} while (orig_iocb.ioc_opcode & (CCHAIN | DCHAIN));
	
	return (0);
}

fp_sio(chan)
register int chan;	/* must load argument into register (r7) */
{
	
	chan <<= 11;
	chan &= 0x03f80000;
	asm("	orw	sioproto,r7");
	asm("	exr	r7");
	return(0);
	asm("	sioproto:");
	asm("	cd 0x00,0x8000");
	return(1);
}

fp_hio(chan)
register int chan;	/* must load argument into register (r7) */
{
	
	chan <<= 11;
	chan &= 0x03f80000;
	asm("	orw	hioproto,r7");
	asm("	exr	r7");
	return(0);
	asm("	hioproto:");
	asm("	cd 0x00,0x1000");
	return(1);
}

fp_ei(level)
register int level;
{

	level <<= 19;
	level &= 0x03f80000;
	asm("	orw	eiproto,r7");
	asm("	exr	r7");
	return(0);
	asm("	eiproto:");
	asm("	ei #0x00");
	return(1);
}
fp_stop() {return(EIO);}
fp_maint() {return(EIO);}
fp_read() {return(EIO);}
fp_write() {return(EIO);}
fp_intr() {}
#endif
#endif
