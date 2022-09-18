h44975
s 00013/00013/00815
d D 7.8 90/12/16 17:02:11 bostic 9 8
c kernel reorg
e
s 00002/00002/00826
d D 7.7 90/06/21 19:03:49 karels 8 7
c vsselect had wrong return convention, random return for exceptional
e
s 00046/00045/00782
d D 7.6 90/04/05 15:19:51 marc 7 6
c tsleep, unwind
e
s 00000/00001/00827
d D 7.5 90/02/17 10:56:44 mckusick 6 5
c get rid of dir.h
e
s 00012/00010/00816
d D 7.4 90/02/08 18:23:21 marc 5 4
c tsleep
e
s 00001/00001/00825
d D 7.3 89/04/25 14:08:06 mckusick 4 3
c ../machine => machine
e
s 00001/00001/00825
d D 7.2 88/10/22 15:14:41 karels 3 2
c use ubaalloc macros; use qbgetpri for Q-bus device probe routines
e
s 00000/00000/00826
d D 7.1 86/06/05 01:24:30 mckusick 2 1
c 4.3BSD release version
e
s 00826/00000/00000
d D 1.1 85/08/30 12:15:06 jg 1 0
c date and time created 85/08/30 12:15:06 by jg
e
u
U
t
T
I 1
/* %W% (MIT) %G% */
 /****************************************************************************
 *									    *
 *  Copyright (c) 1983, 1984 by						    *
 *  DIGITAL EQUIPMENT CORPORATION, Maynard, Massachusetts.		    *
 *  All rights reserved.						    *
 * 									    *
 *  This software is furnished on an as-is basis and may be used and copied *
 *  only with inclusion of the above copyright notice. This software or any *
 *  other copies thereof may be provided or otherwise made available to     *
 *  others only for non-commercial purposes.  No title to or ownership of   *
 *  the software is hereby transferred.					    *
 * 									    *
 *  The information in this software is  subject to change without notice   *
 *  and  should  not  be  construed as  a commitment by DIGITAL EQUIPMENT   *
 *  CORPORATION.							    *
 * 									    *
 *  DIGITAL assumes no responsibility for the use  or  reliability of its   *
 *  software on equipment which is not supplied by DIGITAL.		    *
 * 									    *
 *									    *
 ****************************************************************************/

#include "vs.h"
#if NVS > 0

D 4
#include "../machine/pte.h"
E 4
I 4
D 9
#include "machine/pte.h"
E 9
I 9
#include "../include/pte.h"
E 9
E 4

D 9
#include "param.h"
D 6
#include "dir.h"
E 6
#include "user.h"
#include "buf.h"
#include "systm.h"
#include "map.h"
#include "kernel.h"
#include "ioctl.h"
E 9
I 9
#include "sys/param.h"
#include "sys/user.h"
#include "sys/buf.h"
#include "sys/systm.h"
#include "sys/map.h"
#include "sys/kernel.h"
#include "sys/ioctl.h"
E 9
I 5
D 7
#include "tsleep.h"
E 7
E 5

#include "vsio.h" 

D 9
#include "proc.h"
#include "uio.h"
#include "vmmac.h"
#include "file.h"
E 9
I 9
#include "sys/proc.h"
#include "sys/uio.h"
#include "sys/vmmac.h"
#include "sys/file.h"
E 9

#include "ubareg.h"
#include "ubavar.h"
#include "vsreg.h"

D 9
#include "../vax/mtpr.h"
E 9
I 9
#include "../include/mtpr.h"
E 9

#define	VSWAITPRI	(PZERO+1)
#define	VSMAXEVQ	64	/* must be power of 2 */
#define EVROUND(x)	((x) & (VSMAXEVQ - 1))


#define VSBUFFSIZE	3072
struct vsBuffArea {
	vsIoAddr vsioa;
	char	obuff[VSBUFFSIZE];
	vsEvent ibuff[VSMAXEVQ];
};
struct vsBuffArea vsBuff[NVS];


int vsprobe(), vsattach();
struct uba_device *vsdinfo[NVS];
u_short vsstd[] = { 0 };
struct uba_driver vsdriver =
	{ vsprobe, 0, vsattach, 0, vsstd, "vs", vsdinfo, 0, 0 };

#define	VSUNIT(dev)	(minor(dev))

struct vs_softc {
	unsigned inited : 1;		/* has this ever been inited? */
	unsigned open : 1;		/* only one open, please */
	unsigned linkAvail : 1;		/* link is up */
	short	pgrp;			/* process group for SIGHUP */
	int	romVersion;		/* rom version */
	struct vs_fparm	offset;		/* address base */
	struct vs_csr	csr;		/* saved csr0 */
	struct vs_intr	irr;		/* saved interrupt reason */
	struct vs_kbd	krr;		/* saved keyboard */
	struct vs_fparm	pr;		/* saved parameter regs */
	struct proc *rsel;		/* process waiting for select */
	struct vs_fparm vs_nextgo;	/* next packet to go */
	short vs_status;		/* status from previous packet */
	vsStats stats;			/* statistics */
	int vsBuff_ubinfo;		/* ubinfo for vsBuff */
}vs_softc[NVS];

#define	TRUE	1
#define	FALSE	0

#define	printI	if (vsIntrPrintfs)printf
#define	printD	if (vsDebugPrintfs)printf
#define	printM	if (vsMlpPrintfs) vsMlpPrintfs--,printf
int	vsIntrPrintfs = 0;
int	vsDebugPrintfs = 0;
int	vsMlpPrintfs = 0;

/* 
 * Tell the system that it's out there, and set up the device's interrupt
 * vector. Since we are supporting vs100s and vs125s,
 * this is a bit kludgey. The vs100 works much
 * as one expects, but the vs125 tries to set all the fiber link
 * related bits when you hit VS_IE, ignoring the way the 100 works.
 * Also, the vs100 will let you set the interrupt vector, but
 * the vs125 ignores this and uses its hard-wired value.
 * And there's no sure fire to tell which variant it is.
 * Ugh. Ugh. Ugh.
 */

vsprobe(reg)
caddr_t reg;
{
	register int br, cvec;		/* value-result */
	register struct vsdevice *vsaddr = (struct vsdevice *)reg;

#ifdef	lint
	br = 0; cvec = br; br = cvec;
	vsintr(0);
#endif
	br = 0x15;
	cvec = (uba_hd[numuba].uh_lastiv -= 4*8);
	/* 
	 * uh_lastiv is the last free interrupt vector in the
	 * unibus addapter header (uba_hd).
	 */

	vsaddr->vs_csr0 = cvec >> 2;	/* Save the vector for use on next device */
	vsaddr->vs_irr = 0;		/* Csr will only be read if irr == 0 */
	vsaddr->vs_irr = 0;		/* Clear interrupt reason register */
	vsaddr->vs_pr1  = 0;		/* Clear function parameter */
	vsaddr->vs_pr2  = 0;		/* Clear function parameter */
	vsaddr->vs_ivr = cvec;		/* set up vector (no-op for vs125) */

	DELAY(100000);
	if (vsaddr->vs_csr0 & VS_LNK_AVL)
		return(0);	/* light won't go off! */
	vsaddr->vs_csr0 &= ~VS_LNK_TRNS;
	vsaddr->vs_csr0 |= VS_IE;	/* enable interrupts */
	DELAY(200000);

	return sizeof(struct vsdevice);
}

vsattach(uip)
struct uba_device *uip;
{
	register struct vs_softc *vsp;
	register struct vsdevice *vsaddr;

	vsp = &vs_softc[VSUNIT(uip->ui_unit)];
	vsp->inited  = FALSE;
	vsp->open = FALSE;
	vsBuff[VSUNIT(uip->ui_unit)].vsioa.mbox.bottom = 0;
	vsp->linkAvail = FALSE;
	vsp->romVersion = 0;
	vsp->vs_nextgo.fparm_all = NULL;
	
	vsaddr = (struct vsdevice *) uip->ui_addr;
	vsaddr->vs_csr0 |= (VS_IE | VS_XMIT_ON);
}

vsopen(dev, flag)
dev_t dev;
int flag;
{
	register struct vs_softc *vsp;
	register struct uba_device *uip;
	register struct vsdevice *vsaddr;
	int s;
	int ret;
	struct buf vsbuf;
	struct vsBuffArea *vsb;
	caddr_t vsBuffpage;
	int vsBuffnpages;

	if (VSUNIT(dev) >= NVS || (vsp = &vs_softc[VSUNIT(dev)])->open ||
	    (uip = vsdinfo[VSUNIT(dev)]) == 0 || uip->ui_alive == 0)
		return (ENXIO);

	vsaddr = (struct vsdevice *) uip->ui_addr;
	vsb = &vsBuff[VSUNIT(dev)];
	printM("vsopen csr0=%x, csr1=%x, csr2=%x, csr3=%x, csr4=%x, csr5=%x, csr6=%x, csr7=%x\n",
		vsaddr->vs_csr0, vsaddr->vs_csr1, vsaddr->vs_csr2, vsaddr->vs_csr3,
		vsaddr->vs_csr4, vsaddr->vs_csr5, vsaddr->vs_csr6, vsaddr->vs_csr7);

	/* 
	 * Finally! We can now set up the device.
	 */

	if (!vsp->inited && !(flag & FNDELAY)) {
D 7
		vsInitDev(dev, TRUE);
E 7
I 7
		ret = vsInitDev(dev, TRUE);
		if (ret)
			return (ret);
E 7
		if (ret = vsError(vsp))
			return(ret);
	}

	vsp->open = TRUE;		/* we're open */
	vsp->pgrp = u.u_procp->p_pgrp;

	/* reset statistics */
	bzero((caddr_t) &vsp->stats, sizeof(vsStats));

	/* initialize user I/O addresses */
	vsb->vsioa.ioreg = (short *)vsaddr;
	vsb->vsioa.status = 0;
	vsb->vsioa.obuff = vsb->obuff;
	vsb->vsioa.obufflen = VSBUFFSIZE;
	vsb->vsioa.ibuff = vsb->ibuff;
	vsb->vsioa.ihead = 0;
	vsb->vsioa.itail = 0;
	vsb->vsioa.iqsize = VSMAXEVQ;
	/* map io regs into user address space (assume they don't cross a page) */
	maptouser(vsaddr);
	/* map vsBuff into user address space */
	vsBuffpage = (caddr_t)((int)vsb & ~PGOFSET);
	vsBuffnpages = (((int)vsb & PGOFSET) +
			 (NBPG-1) + sizeof(struct vsBuffArea)) >> PGSHIFT;
	while (vsBuffnpages>0) {
	    maptouser(vsBuffpage);
	    vsBuffpage += NBPG;
	    vsBuffnpages--;
	}
	/* lock in the buffer */
	vsbuf.b_error = 0;
	vsbuf.b_proc = u.u_procp;
	vsbuf.b_un.b_addr = vsb->obuff;
	vsbuf.b_flags = B_BUSY;
	vsbuf.b_bcount = VSBUFFSIZE;
	vsp->vsBuff_ubinfo = ubasetup(uip->ui_ubanum, &vsbuf, UBA_CANTWAIT);

	vsb->vsioa.reloc = (int) (vsp->offset.fparm_all
D 3
			+ (vsp->vsBuff_ubinfo & 0x3ffff));
E 3
I 3
			+ UBAI_ADDR(vsp->vsBuff_ubinfo));
E 3
	return(0);
}

vsclose(dev)
dev_t dev;
{
	register struct uba_device *uip = vsdinfo[VSUNIT(dev)];
	register struct vs_softc *vsp = &vs_softc[VSUNIT(dev)];
	int s, i;
	struct vsdevice *vsaddr;
	struct vsBuffArea *vsb;
	caddr_t vsBuffpage;
	int vsBuffnpages;
	
	vsaddr = (struct vsdevice *) uip->ui_addr;
	printM("vsclose csr0=%x, csr1=%x, csr2=%x, csr3=%x, csr4=%x, csr5=%x, csr6=%x, csr7=%x\n",
		vsaddr->vs_csr0, vsaddr->vs_csr1, vsaddr->vs_csr2, vsaddr->vs_csr3,
		vsaddr->vs_csr4, vsaddr->vs_csr5, vsaddr->vs_csr6, vsaddr->vs_csr7);
		vsb = &vsBuff[VSUNIT(dev)];
	if (vsDebugPrintfs) {
		printf("vs%d: %d errors, %d unsolicited interrupts",
			VSUNIT(dev), vsp->stats.errors, vsp->stats.unsolIntr);
		printf(", %d link errors", vsp->stats.linkErrors);
		printf(", %d overruns", vsp->stats.overruns);
		printf(", csr0 %x, csr1 %x", vsaddr->vs_csr0, vsaddr->vs_csr1);
		printf("\n");
	}

	vsp->open = FALSE;
	vsp->inited = FALSE;		/* init on every open */
	vsp->vs_nextgo.fparm_all = NULL;
	vsb->vsioa.mbox.bottom = 0;
	/* release the buffer */
	if (vsp->vsBuff_ubinfo!=0) {
		ubarelse(uip->ui_ubanum, &vsp->vsBuff_ubinfo);
	}

#ifdef notdef
	/* unmap io regs into user address space (assume they don't cross a page) */
	unmaptouser(vsaddr);
	/* unmap vsBuff into user address space */
	vsBuffpage = (caddr_t)((int)vsb & ~PGOFSET);
	vsBuffnpages = (((int)vsb&PGOFSET) +
			 (NBPG-1)+ sizeof(struct vsBuffArea)) >> PGSHIFT;
	while (vsBuffnpages>0) {
	    unmaptouser(vsBuffpage);
	    vsBuffpage += NBPG;
	    vsBuffnpages--;
	}
#endif
I 7
	return (0);
E 7
}

vsread(dev,uio)
dev_t   dev;
struct uio      *uio;
{
        return(-1);
}

vswrite(dev, uio)
dev_t   dev;
struct uio      *uio;
{
        return(-1);
}

/*ARGSUSED*/
vsioctl(dev, cmd, addr, flag)
dev_t dev;
register caddr_t addr;
{
	register struct uba_device *uip = vsdinfo[VSUNIT(dev)];
	register struct vs_softc *vsp = &vs_softc[VSUNIT(dev)];
	register struct vsdevice *vsaddr = (struct vsdevice *) uip->ui_addr;
	register struct vsBuffArea *vsb = &vsBuff[VSUNIT(dev)];
	struct vs_fparm vsAddr;
D 7
	int s;
E 7
I 7
	int s, error = 0;
E 7
	int func;
	int ret;

	switch(cmd) {			/* things that don't need the device */
	case VSIOWAITGO:
		/* wait for user I/O operation to complete, then go */
		s = spl5();
		if ((ret = vsb->vsioa.status) == 0) {
			vsp->vs_nextgo.fparm_all = ((struct vs_fparm *) addr)->fparm_all;
			do {
D 5
				sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
				tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_WAIT, 0);
E 5
			} while (vsp->vs_nextgo.fparm_all);
E 7
I 7
				error = tsleep((caddr_t)vsp, VSWAITPRI | PCATCH,
				    devwait, 0);
			} while (vsp->vs_nextgo.fparm_all && error == 0);
E 7
			ret = vsp->vs_status;
		} else {
			vsaddr->vs_pr1 = ((struct vs_fparm *)addr)->fparm_low;
			vsaddr->vs_pr2 = ((struct vs_fparm *)addr)->fparm_high;
			vsb->vsioa.status = 0;
			vsaddr->vs_csr0 &= ~VS_FCN;	/* clear bits */
			vsaddr->vs_csr0 |= (VS_IE | (VS_SEND << VS_FCSHIFT) | VS_GO);
		}
		splx(s);
I 7
		if (error)
			return (error);
E 7
		if (ret & VS_ERROR)
			return ((ret & VS_REASON) + 128);
		return(0);

	case VSIOUSERWAIT:
		/* wait for user I/O operation to complete */
		s = spl5();
		while (vsb->vsioa.status == 0) {
D 5
			sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
			tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_USRWAIT, 0);
E 7
I 7
			error = tsleep((caddr_t) vsp, VSWAITPRI | PCATCH,
			    devio, 0);
E 7
E 5
		}
		splx(s);
D 7
		return (0);
E 7
I 7
		return (error);
E 7

	case VSIOGETVER:		/* get ROM version */
		if (!vsp->inited)
			return(ENODEV);
		*(int *) addr = vsp->romVersion;
		return(0);

	case VSIOGETSTATS:		/* get statistics block */
		*(vsStats *)addr = vsp->stats;
		return(0);

	case VSIOGETIOA:		/* get io addresses */
		if (vsp->vsBuff_ubinfo==0) {
		    return(EIO);
		}
		*((vsIoAddrAddr *)addr) = &vsb->vsioa;
		return(0);

	default:			/* a command that could block */
		if (ret = vsError(vsp))
			return(ret);
		break;
	}

	switch(cmd) {			/* Commands that cause an interrupt */
	case VSIOINIT:			/* initialize device */
		vsInitDev(dev, FALSE);
		return(vsError(vsp));

	case VSIOSTART:			/* start microcode */
		vsAddr.fparm_all = *(caddr_t *)addr;
		s = spl5();
		vsaddr->vs_pr1 = vsAddr.fparm_low;
		vsaddr->vs_pr2 = vsAddr.fparm_high;
		vsaddr->vs_irr = 0;
		vsaddr->vs_csr0 &= ~VS_FCN;	/* clear bits */
		vsaddr->vs_csr0 |= (VS_IE | (VS_START << VS_FCSHIFT) | VS_GO);
D 5
		sleep((caddr_t) vsp, VSWAITPRI);	/* synchronous */
E 5
I 5
		/* synchronous */
D 7
		tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_START, 0);
E 7
I 7
		error = tsleep((caddr_t) vsp, VSWAITPRI | PCATCH, devwait, 0);
E 7
E 5
		splx(s);
I 7
		if (error)
			return (error);
E 7
		return(vsError(vsp));

	case VSIOABORT:			/* abort a command chain */
		s = spl5();
		vsaddr->vs_irr = 0;
		vsaddr->vs_csr0 &= ~VS_FCN;
		vsaddr->vs_csr0 |= (VS_IE | (VS_ABORT << VS_FCSHIFT) | VS_GO);
D 5
		sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
		tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_ABORT, 0);
E 7
I 7
		error = tsleep((caddr_t) vsp, VSWAITPRI | PCATCH, devwait, 0);
E 7
E 5
		splx(s);
I 7
		if (error)
			return (error);
E 7
		return(vsError(vsp));

	case VSIOPWRUP:			/* power-up reset */
		s = spl5();
		vsaddr->vs_irr = 0;
		vsaddr->vs_csr0 &= ~VS_FCN;
		vsaddr->vs_csr0 |= (VS_IE | (VS_PWRUP << VS_FCSHIFT) | VS_GO);
D 5
		sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
		tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_PWRUP, 0);
E 7
I 7
		error = tsleep((caddr_t) vsp, VSWAITPRI | PCATCH, devwait, 0);
E 7
E 5
		splx(s);
I 7
		if (error)
			return (error);
E 7
		return(vsError(vsp));

	case VSIOBBACTL:		/* enable/disable BBA */
		s = spl5();
		vsaddr->vs_irr = 0;
		vsaddr->vs_csr0 &= ~VS_FCN;
		func = *(int *)addr == VSIO_ON ? VS_ENABBA : VS_DISBBA;
		vsaddr->vs_csr0 |= (VS_IE | (func << VS_FCSHIFT) | VS_GO);
D 5
		sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
		tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_IOBCTL, 0);
E 7
I 7
		error = tsleep((caddr_t) vsp, VSWAITPRI | PCATCH, devwait, 0);
E 7
E 5
		splx(s);
I 7
		if (error)
			return (error);
E 7
		return(vsError(vsp));

	case VSIOFIBCTL:		/* turn the fiber lamp on/off */
		s = spl5();
		if (*(int *)addr == VSIO_OFF)
			vsaddr->vs_csr0 &= ~VS_XMIT_ON;
		else
			vsaddr->vs_csr0 |= (VS_IE | VS_XMIT_ON);
D 5
		sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
		tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_FIB, 0);
E 7
I 7
		error = tsleep((caddr_t) vsp, VSWAITPRI | PCATCH, devwait, 0);
E 7
E 5
		splx(s);
I 7
		if (error)
			return (error);
E 7
		return(vsError(vsp));

	case VSIOFIBRETRY:		/* set fiber retries */
		s = spl5();
		vsaddr->vs_irr = 0;
		vsaddr->vs_csr0 &= ~VS_FCN;
		func = *(int *)addr == VS_FIB_FINITE ? VS_FINITE : VS_INFINITE;
		vsaddr->vs_csr0 |= (VS_IE | (func << VS_FCSHIFT) | VS_GO);
D 5
		sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
		tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_FIBRET, 0);
E 7
I 7
		error = tsleep((caddr_t) vsp, VSWAITPRI | PCATCH, devwait, 0);
E 7
E 5
		splx(s);
I 7
		if (error)
			return (error);
E 7
		return(vsError(vsp));

	case VSIOSYNC:			/* get synchronized with device */
		break;

	default:
		return(ENOTTY);
	}

	return(0);
}

vsintr(dev)
dev_t dev;
{
	register struct vsdevice *vsaddr;
	register struct vs_softc *vsp;
	register vsEvent *vep;
	struct uba_device *uip;
	register struct vsBuffArea *vsb;
	int i;
	vsCursor cur;

	if (VSUNIT(dev) >= NVS || (uip = vsdinfo[VSUNIT(dev)]) == 0
	    || uip->ui_alive == 0) {
		printI("vs%d stray interrupt\n", VSUNIT(dev));
		return;
	}

	vsaddr = (struct vsdevice *) uip->ui_addr;
	vsp = &vs_softc[VSUNIT(dev)];
	vsb = &vsBuff[VSUNIT(dev)];
#ifdef notdef
	printM("vsintr csr0=%x, csr1=%x, csr2=%x, csr3=%x, csr4=%x, csr5=%x, csr6=%x, csr7=%x\n",
		vsaddr->vs_csr0, vsaddr->vs_csr1, vsaddr->vs_csr2, vsaddr->vs_csr3,
		vsaddr->vs_csr4, vsaddr->vs_csr5, vsaddr->vs_csr6, vsaddr->vs_csr7);

	printI("vs%dintr ", VSUNIT(dev));
#endif

	/* 
	 * get the information out of the soft registers
	 */

	vsp->irr.intr_reg = vsaddr->vs_irr;
	vsp->krr.kbd_reg = vsaddr->vs_krr;
	vsp->pr.fparm_low = vsaddr->vs_pr1;
	vsp->pr.fparm_high = vsaddr->vs_pr2;
	cur.x = vsaddr->vs_cxr;
	cur.y = vsaddr->vs_cyr;
	vsp->csr.csr_reg = vsaddr->vs_csr0;

	if (vsp->irr.intr_reason)
		vsaddr->vs_irr = 0;	/* clear int reason, if any */

	vsaddr->vs_csr0 &= ~VS_OWN;	/* clear owner bit */

	if (vsp->csr.csr_linkTran) {
		vsaddr->vs_csr0 &= ~VS_LNK_TRNS;	/* clear the bit */
		printI("link transition: ");
		if (vsp->csr.csr_linkErr)
			vsp->stats.linkErrors++;

		if (vsp->csr.csr_linkAvail == vsp->linkAvail) {	/* flash */
			vsp->stats.flashes++;
			printI("flash\n");
		} else if (!vsp->csr.csr_linkAvail && vsp->linkAvail) { /* on -> off */
			vsp->stats.douses++;
			printI("douse\n");
			vsp->inited = FALSE;
			if (vsp->open && vsp->pgrp)
				gsignal(vsp->pgrp, SIGHUP);
			wakeup((caddr_t) vsp);
		} else {						/* off -> on */
			vsp->stats.ignites++;
			printI("ignite\n");
			wakeup((caddr_t) vsp);
		}

		i = 200;
		while ((vsaddr->vs_csr0 & VS_LNK_TRNS) && i)
			i--;
		if (i == 0) {		/* bit stuck */
			printI("vs%d: Link Transition bit stuck\n", VSUNIT(dev));
			vsp->inited = FALSE;
			if (vsp->open && vsp->pgrp)
				gsignal(vsp->pgrp, SIGHUP);
			vsaddr->vs_csr0 &= ~VS_XMIT_ON;
			vsp->csr.csr_linkAvail = FALSE;
		}

		vsp->linkAvail = vsp->csr.csr_linkAvail;

		return;
	}

	if (vsp->irr.intr_error) {
		printI("error 0x%x\n", vsp->irr.intr_reg&0xffff);
		vsp->stats.errors++;
		/* set status and wake up user if necessary */
		if (vsp->vs_nextgo.fparm_all) {
			vsp->vs_status = vsp->irr.intr_reg;
			vsaddr->vs_pr1 = vsp->vs_nextgo.fparm_low;
			vsaddr->vs_pr2 = vsp->vs_nextgo.fparm_high;
			vsp->vs_nextgo.fparm_all = NULL;
			vsaddr->vs_csr0 &= ~VS_FCN;	/* clear bits */
			vsaddr->vs_csr0 |= (VS_IE | (VS_SEND << VS_FCSHIFT) | VS_GO);
		} else
			vsb->vsioa.status = vsp->irr.intr_reg;
		wakeup((caddr_t) vsp);
		return;
	}

#ifdef notdef
	printI("reason is %b\n", vsp->irr.intr_reason, VSIRR_BITS);
#endif
	switch(vsp->irr.intr_reason) {
	case VS_INT_CD:			/* command done */
		/* set status and start a new command if necessary */
		if (vsp->vs_nextgo.fparm_all) {
			vsp->vs_status = vsp->irr.intr_reg;
			vsaddr->vs_pr1 = vsp->vs_nextgo.fparm_low;
			vsaddr->vs_pr2 = vsp->vs_nextgo.fparm_high;
			vsp->vs_nextgo.fparm_all = NULL;
			vsaddr->vs_csr0 &= ~VS_FCN;	/* clear bits */
			vsaddr->vs_csr0 |= (VS_IE | (VS_SEND << VS_FCSHIFT) | VS_GO);
		} else
			vsb->vsioa.status = vsp->irr.intr_reg;
		break;

	case VS_INT_MM:			/* mouse moved */

		vsb->vsioa.mouse = cur;

                if (!vsp->open)
                        return;         /* ignore on closed device */

		/* no event if inside box */
		if (cur.y < vsb->vsioa.mbox.bottom &&
		    cur.y >= vsb->vsioa.mbox.top &&
		    cur.x < vsb->vsioa.mbox.right &&
		    cur.x >= vsb->vsioa.mbox.left)
		    return;

		/* trash box */
		vsb->vsioa.mbox.bottom = 0;

		if (EVROUND(vsb->vsioa.itail+1) == vsb->vsioa.ihead)
		    return;
		i = EVROUND(vsb->vsioa.itail-1);
		if ((vsb->vsioa.itail != vsb->vsioa.ihead) &&
		    (i != vsb->vsioa.ihead)) {
		    vep = &vsb->ibuff[i];
		    if (vep->vse_type == VSE_MMOTION) {
			vep->vse_x = cur.x;
			vep->vse_y = cur.y;
			vep->vse_time = mfpr(TODR);
			return;
		    }
		}
		/* put event into queue and do select */
		vep = &vsb->ibuff[vsb->vsioa.itail];
		vep->vse_type = VSE_MMOTION;
		vep->vse_x = cur.x;
		vep->vse_y = cur.y;
		vep->vse_time = mfpr(TODR);
		vsb->vsioa.itail = EVROUND(vsb->vsioa.itail+1);
		if (vsp->rsel) {
			selwakeup(vsp->rsel, 0);
			vsp->rsel = 0;
		}
		break;

	case VS_INT_BE:			/* button event */
		if (!vsp->open)
			return;		/* ignore on closed device */

		if (vsp->krr.kbd_device == VSE_MOUSE) {
		    vsb->vsioa.mouse.x = cur.x;
		    vsb->vsioa.mouse.y = cur.y;
		}
		/* check for room in the queue */
		if ((i = EVROUND(vsb->vsioa.itail+1)) == vsb->vsioa.ihead)
		    return;
		/* put event into queue and do select */
		vep = &vsb->ibuff[vsb->vsioa.itail];
		vep->vse_type = VSE_BUTTON; 
		vep->vse_key = vsp->krr.kbd_key;
		vep->vse_direction = vsp->krr.kbd_transition;
		vep->vse_device = vsp->krr.kbd_device;
	        vep->vse_time = mfpr(TODR);
		vep->vse_x = vsb->vsioa.mouse.x;
		vep->vse_y = vsb->vsioa.mouse.y;
		vsb->vsioa.itail = i;
		if (vsp->rsel) {
			selwakeup(vsp->rsel, 0);
			vsp->rsel = 0;
		}
		break;

	case VS_INT_TM:			/* tablet moved */
		if (!vsp->open)
			return;		/* ignore on closed device */

		if (EVROUND(vsb->vsioa.itail+1) == vsb->vsioa.ihead)
		    return;
		i = EVROUND(vsb->vsioa.itail-1);
		if ((vsb->vsioa.itail != vsb->vsioa.ihead) &&
		    (i != vsb->vsioa.ihead)) {
		    vep = &vsb->ibuff[i];
		    if (vep->vse_type == VSE_TMOTION) {
			vep->vse_x = cur.x;
			vep->vse_y = cur.y;
			vep->vse_time = mfpr(TODR);
			return;
		    }
		}
		/* put event into queue and do select */
		vep = &vsb->ibuff[vsb->vsioa.itail];
		vep->vse_type = VSE_TMOTION;
		vep->vse_x = cur.x;
		vep->vse_y = cur.y;
		vep->vse_time = mfpr(TODR);
		vsb->vsioa.itail = EVROUND(vsb->vsioa.itail+1);
		if (vsp->rsel) {
			selwakeup(vsp->rsel, 0);
			vsp->rsel = 0;
		}
		break;

	case VS_INT_US:			/* unsolicited */
		vsp->stats.unsolIntr++;
		return;

	case VS_INT_ID:			/* Initialization done */
					/* save offset from device */
		vsp->offset.fparm_all = vsp->pr.fparm_all;
					/* save rom version */
		vsp->romVersion = cur.x;
		vsp->inited = TRUE;
		break;

	case VS_INT_SE:			/* ucode started */
		break;

	case VS_INT_PWR:		/* power up complete */
					/* save rom version */
		vsp->romVersion = cur.x;
		vsp->inited = FALSE;
		if (vsp->open && vsp->pgrp)
			gsignal(vsp->pgrp, SIGHUP);
		break;

	default:
		printI("vs%d: unknown interrupt %b\n", VSUNIT(dev),
			vsp->irr.intr_reason, VSIRR_BITS);
		return;
	}
	wakeup((caddr_t) vsp);
}

vsreset(uban)
int uban;
{
	register int i;
	register struct uba_device *uip;
	register struct vs_softc *vsp = vs_softc;

	for (i = 0; i < NVS; i++, vsp++) {
		if ((uip = vsdinfo[i]) == 0 || uip->ui_alive == 0 ||
		    uip->ui_ubanum != uban || vsp->open == 0)
			continue;
		printf(" vs%d", i);
		vsp->inited = FALSE;
		if (vsp->open && vsp->pgrp)
			gsignal(vsp->pgrp, SIGHUP);
	}
}

vsselect(dev, rw)
dev_t dev;
{
	register struct vsBuffArea *vsb = &vsBuff[VSUNIT(dev)];
	int s = spl5();

	switch(rw) {
	case FREAD:
		if (vsb->vsioa.ihead != vsb->vsioa.itail) {
		    splx(s);
		    return(1);
		}
		vs_softc[VSUNIT(dev)].rsel = u.u_procp;
		splx(s);
		return(0);

D 8
	case FWRITE:
E 8
I 8
	default:
E 8
		splx(s);
D 8
		return(EACCES);
E 8
I 8
		return(0);	/* can never write */
E 8
	}
}

/*
 * Initialize VS100 or SBO.
 * Set XMITON.  VS100 will respond with link available.  SBO won't, so
 * don't wait forever; assume everything is OK and warn user.
 */

vsInitFiber(dev)
dev_t dev;
{
	struct vsdevice *vsaddr = (struct vsdevice *) vsdinfo[VSUNIT(dev)]->ui_addr;
	register struct vs_softc *vsp = &vs_softc[VSUNIT(dev)];
D 7
	int s;
#ifdef VSSBO
	int vsFiberNudge();
E 7
I 7
	int s, error;
E 7

D 7
	timeout(vsFiberNudge, (caddr_t) dev, 2*hz);
#endif
E 7
	s = spl5();
	vsaddr->vs_csr0 |= (VS_IE | VS_XMIT_ON);	/* turn link on */
D 5
	sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
	tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_INITF, 0);
E 7
I 7
	error = tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_INITF, 2*hz);
E 7
E 5
	splx(s);
I 7
	if (error == EWOULDBLOCK)	/* timeout */
		error = 0;
E 7
#ifdef VSSBO
	if (!vsp->linkAvail) {
		uprintf("\007This had better be a vs125!\n");
		printf("vs%d must be a vs125\n", VSUNIT(dev));
		vsp->linkAvail = TRUE;
	}
#endif
I 7
	return (error);
E 7
}

D 7
#ifdef VSSBO
vsFiberNudge(dev)
dev_t dev;
{
	struct vs_softc *vsp = &vs_softc[VSUNIT(dev)];

	if (!vsp->linkAvail)
		wakeup((caddr_t) vsp);
}
#endif VSSBO

E 7
vsInitDev(dev, retry)
dev_t dev;
int retry;
{
	register struct vsdevice *vsaddr;
	register struct vs_softc *vsp;
D 7
	int s;
	int vsInitNudge();
E 7
I 7
	int s, error;
E 7

	vsaddr = (struct vsdevice *) vsdinfo[VSUNIT(dev)]->ui_addr;
	vsp = &vs_softc[VSUNIT(dev)];

	if (!vsp->linkAvail)
D 7
		vsInitFiber(dev);
E 7
I 7
		if (error = vsInitFiber(dev))
			return (error);
E 7
	while (1) {
D 7
		if (retry)
			timeout(vsInitNudge, (caddr_t) dev, 10*hz);
E 7
		s = spl5();
		vsaddr->vs_irr = 0;
		vsaddr->vs_csr0 &= ~VS_FCN;
		vsaddr->vs_csr0 |= (VS_IE | (VS_INIT << VS_FCSHIFT) | VS_GO);
D 5
		sleep((caddr_t) vsp, VSWAITPRI);
E 5
I 5
D 7
		tsleep((caddr_t) vsp, VSWAITPRI, SLP_VS_INITDEV, 0);
E 7
I 7
		error = tsleep((caddr_t) vsp, VSWAITPRI | PCATCH,
		    devwait, retry ? 10*hz : 0);
E 7
E 5
		splx(s);
I 7
		if (error == EWOULDBLOCK)
			error = 0;
		if (error)
			return (error);
E 7
		if (vsp->inited)
			break;
		printM("vs%d: VS_INIT fails\n", VSUNIT(dev));
		uprintf("vsInitDev %x %x\n",vsaddr->vs_csr0, vsaddr->vs_csr1);
	}
D 7
}

vsInitNudge(dev)
dev_t dev;
{
	struct vs_softc *vsp = &vs_softc[VSUNIT(dev)];

	if (!vsp->inited)
		wakeup((caddr_t) vsp);
E 7
I 7
	return (0);
E 7
}

vsError(vsp)
	register struct vs_softc *vsp;
{
	if (vsp->irr.intr_error) {
		register int ret = vsp->irr.intr_reg;

		printD("\treturning 0x%x\n", ret);
		vsp->irr.intr_reg = 0;
		return(ret+128);
	}
	return(0);
}
#endif

E 1
