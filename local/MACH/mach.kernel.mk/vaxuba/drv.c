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
 * $Log:	drv.c,v $
 * Revision 2.3  89/03/09  22:33:24  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:01:57  gm0w
 * 	Changes for cleanup.
 * 
 */
/*
 **********************************************************************
 *  DRV11-B interface for DR11-B/W driver
 *
 *  (This is not a complete driver.  It is actually a copy of a
 *  previous attempt at supporting a DRV11-B via a DR11-W and must
 *  still be converted for the new combined driver).
 **********************************************************************
 */

/*	drv.c	CMU	3/26/82	*/

#include <drv.h>

#if	NDRV > 0

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/pte.h>
#include <sys/buf.h>
#include <sys/ubareg.h>
#include <sys/ubavar.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/dr.h>
#include <sys/drv.h>


dropen(dev, flag)
{

    register int unit = DRUNIT(dev);
    register int ifvc = DRIFVC(dev);
    register struct uba_device *ui;
    register struct drparam *drp;
    register struct drstate *drs;

    if (unit >= NDR || (ui=drinfo[unit]) == 0 || ui->ui_alive == 0 || 
		    (ui->ui_type != DRGMR && ifvc != 0))
    {
	u.u_error = ENXIO;
	return;
    }
    drs = &drstate[unit][ifvc];
    if (drs->dr_open)
	u.u_error = EBUSY;
    else
    {
	drs->dr_open++;
	drs->dr_rbits = 0;
	drs->dr_wbits = 0;
    }
#if	DEBUG
printf("dropen %d, act %d\n", unit, drparam[unit].dr_tab.b_active);
#endif

}


drclose(dev, flag)
{

    register int unit = DRUNIT(dev);
    register int ifvc = DRIFVC(dev);
    register struct uba_device *ui = drinfo[unit];
    register struct drparam *drp = &drparam[unit];
    register struct drstate *drs = &drstate[unit][ifvc];

    switch (ui->ui_type)
    {
	case DRLP:
	    lpclose(dev, flag);
	    break;

	case DRGMR:
	{
	    if (drp->gmr_line.res_dev == dev)
		gmrrelease(dev, &(drp->gmr_line));
	    drp->gmr_memchan &= ~drs->gmr_memifvc;
	    drs->gmr_memifvc = 0;
	    if (drp->gmr_mem.res_dev == dev)
		gmrrelease(dev, &(drp->gmr_mem));
	    break;
	}
 
	case DRV11B:
	    DRADDR->drst = 0;
	    drp->drv_sign = 0;
	    drp->drv_csr = 0;
	    drp->drv_mode = DRVM_NORMAL;
	    drp->drv_state = DRVS_IDLE;
	    break;
    }

    drs->dr_open = 0;
#if	DEBUG
printf("drclose %d\n", unit);
#endif

}



lpclose(dev, flag)
{

    register struct buf *bp;

    if (flag == 0)
	return;
    bp = &drparam[DRUNIT(dev)].dr_buf;
#if	DEBUG
printf("lpclose\n");
#endif
    drwaitbusy(bp, PRIBIO);
    bp->b_flags = B_BUSY|B_WRITE;
    bp->b_dev = dev;
    bp->b_bcount = sizeof lpform;
    bp->b_un.b_addr = lpform;
    drstrategy(bp);
#if	DEBUG
printf("iowait %x\n", bp);
#endif
    iowait(bp);
    bp->b_flags = 0;
    
}



#define drcopyin(from, to, size)					\
    if (copyin((caddr_t)(from), (caddr_t)(to), size))			\
    {									\
	u.u_error = EFAULT;						\
	return;								\
    }

#define drcopyout(from, to, size)					\
    if (copyout((caddr_t)(from), (caddr_t)(to), size))			\
    {									\
	u.u_error = EFAULT;						\
	return;								\
    }
	
/* ARGSUSED */
drioctl(dev, cmd, addr, flag)
caddr_t addr;
dev_t dev;
{

    int unit = DRUNIT(dev);
    int ifvc = DRIFVC(dev);
    register struct uba_device *ui = drinfo[unit];
    register struct drparam *drp = &drparam[unit];
    register struct drstate *drs = &drstate[unit][ifvc];

    switch (ui->ui_type)
    {
	case DRGMR: switch (cmd)
	{
	    case GMRIOCNOWC:
		drs->dr_wbits |= DRCSR_FUNC2;
		break;

	    case GMRIOCWC:
		drs->dr_wbits &= ~DRCSR_FUNC2;
		break;

	    case GMRIOCRESERVE:
		gmrreserve(dev, &(drp->gmr_line));
		break;

	    case GMRIOCRELEASE:
		gmrrelease(dev, &(drp->gmr_line));
		break;
		
	    case GMRIOCCHECKMEM:
		gmrreserve(dev, &(drp->gmr_mem));
		if (copyout((caddr_t)&(drp->gmr_memchan), addr, sizeof (drp->gmr_memchan)))
		{
		    u.u_error = EFAULT;
		    gmrrelease(dev, &(drp->gmr_mem));
		}
		break;

	    case GMRIOCALLOCMEM:
	    {
		int memchan;

		gmrreserve(dev, &drp->gmr_mem);
		drcopyin(addr, &memchan, sizeof (memchan));
		if (drp->gmr_memchan & memchan)
		    u.u_error = EBUSY;
		else
		{
		    drp->gmr_memchan |= memchan;
		    drs->gmr_memifvc |= memchan;
		}
		gmrrelease(dev, &(drp->gmr_mem));
		break;
	    }

	    case GMRIOCDEALLOCMEM:
	    {
		int memchan;

		drcopyin(addr, &memchan, sizeof (memchan));
		if ((drs->gmr_memifvc & memchan) != memchan)
		    u.u_error = EPERM;
		else
		{
		    drp->gmr_memchan &= ~memchan;
		    drs->gmr_memifvc &= ~memchan;
		} 
		break;
	    }
	    
	    default:
		u.u_error = ENODEV;
		break;
	}
 	break;

	case DRV11B: switch(cmd)
	{
	    case DRVIOCENBS:
	    {
            	u_int n;

		if (drp->drv_mode != DRVM_NORMAL)
		{
		    u.u_error = EINVAL;
		    return;
		}
		if (!drvidle(drp))
		    return;
		drcopyin(addr, &n, sizeof n);
		if (n < NSIG)
		{
		    drp->drv_sigp = u.u_procp;
		    drp->drv_pid  = u.u_procp->p_pid;
		    if (drp->drv_sign = n)	/* This must be set last */
			drp->drv_csr = DRCSR_IE;
		    else
			drp->drv_csr = 0;
		    DRADDR->drst = drp->drv_csr;
		}
		else
		    u.u_error = EINVAL;
		break;
	    }

	    case DRVIOCGETS:
	    {
		u_short stat;

		drwaitbusy(&(drp->dr_buf), PZERO+1);
		DRADDR->drst = DRCSR_ERR | drp->drv_csr;
		stat = DRADDR->drst;
		DRADDR->drst = drp->drv_csr;
		drcopyout(&stat, addr, sizeof (stat));
		break;
	    }

	    case DRVIOCLINK:
		if (!drvidle(drp))
		    return;
		drp->drv_state = DRVS_IDLE;
		drp->drv_sign = 0;
		drp->drv_mode = DRVM_LINK;
		drs->dr_rbits = DRCSR_FUNC2;
		drp->drv_csr = DRCSR_IE;
		DRADDR->drst = DRCSR_IE;
		break;

	    case DRVIOCNOLINK:
		if (!drvidle(drp))
		    return;
		DRADDR->drst = 0;
		drp->drv_csr = 0;
		drs->dr_rbits = 0;
		drp->drv_mode = DRVM_NORMAL;
		drp->drv_state = DRVS_IDLE;
		break;

	    case DRVIOCINTR:
	    {
		register int ipl;

		if (drp->drv_mode != DRVM_NORMAL)
		{
		    u.u_error = EINVAL;
		    return;
		}
		if (!drvidle(drp))
		    return;
		ipl = spl5();
		drp->drv_state = DRVS_INTR;
		DRADDR->drst = DRCSR_FUNC2 | DRCSR_IE;
		while (drp->drv_state == DRVS_INTR)
		    sleep((caddr_t)&(drp->drv_state), PZERO+1);
		splx(ipl);
		break;
	    }

	    case DRVIOCRESET:
	    {
		register int ipl;

		drwaitbusy(&(drp->dr_buf), PZERO+1);
		ipl = spl5();
		DRADDR->drst = 0;
		drp->drv_sign = 0;
		drp->drv_state = DRVS_IDLE;
		drp->drv_mode = DRVM_NORMAL;
		drp->drv_csr  = 0;
		splx(ipl);
		break;
	    }

	    default:
		u.u_error = ENODEV;
		break;
 	}
	break;

	default:
	    u.u_error = ENODEV;
	    break;
    }

}



drvidle(drp)
register struct drparam *drp;
{

    drwaitbusy(&(drp->dr_buf), PZERO+1);
    if (drp->drv_state != DRVS_IDLE && drp->drv_state != DRVS_GA)
    {
	drp->drv_state = DRVS_ERROR;
	u.u_error = ENXIO;
	return(0);
    }
    return(1);
}



drvwaitga(drp)
register struct drparam *drp;
{

    register int ipl;

    ipl = spl5();
    while (drp->drv_state != DRVS_GA)
    {
	if (drp->drv_state == DRVS_ERROR)
	{
	    u.u_error = ENXIO;
	    splx(ipl);
	    return(1);
	}
	drp->drv_state = DRVS_WAIT;
	sleep((caddr_t)&(drp->drv_state), PZERO+1);
    }
    splx(ipl);
    return(0);

}


    
drwaitbusy(bp, pri)
register struct buf *bp;
{

    register int ipl;

    ipl = spl5();
    while (bp->b_flags&B_BUSY)
    {
	bp->b_flags |= B_WANTED;
	sleep(bp, pri);
    }
    splx(ipl);

}




/*
 *  gmrreserve - reserve a resource
 */

gmrreserve(dev, res)
dev_t dev;
struct gmrresource *res;
{

    if (res->res_dev == dev)
	return;
    while (res->res_dev)
    {
	res->res_flag |= RES_WANTED;
	sleep(res, PPIPE);
    }
    res->res_dev = dev;

}


/*
 *  gmrrelease - release a resource
 */

gmrrelease(dev, res)
dev_t dev;
struct gmrresource *res;
{

    if (res->res_dev != dev)
    {
	u.u_error = EPERM;
	return;
    }
    res->res_dev = 0;
    if (res->res_flag & RES_WANTED)
    {
	res->res_flag &= ~(RES_WANTED);
	wakeup(res);
    }

}



drstrategy(bp)
struct buf *bp;
{

    register int unit = DRUNIT(bp->b_dev);
    register struct uba_ctlr *um = &drctlr[unit];
    register struct buf *dp = &drparam[unit].dr_tab;

    /*
     *  Put request at end of queue.  This is overly general for now
     *  since there is never any more than one outstanding request
     *  per queue but is necessary for ubago which provides exclusive
     *  UBA access.
     */
    bp->av_forw = NULL;
    (void) spl5();
    if (dp->b_actf == NULL)
    {
	dp->b_actf = bp;
	dp->b_forw = NULL;
	if (um->um_tab.b_actf == NULL)
		um->um_tab.b_actf = dp;
	else
		um->um_tab.b_actl->b_forw = dp;
	um->um_tab.b_actl = dp;
    }
    else
	dp->b_actl->av_forw = bp;
    dp->b_actl = bp;
    if (um->um_tab.b_active == 0)
	drstart(um);
    (void) spl0();

}



drstart(um)
register struct uba_ctlr *um;
{

    int unit;
    int com;
    register struct buf *bp, *dp;
    register struct drdevice *addr;
    register struct uba_device *ui;
    register struct drtype *drt;
    register struct drparam *drp;
    register struct drstate *drs;
    extern drtimout();

loop:
    if ((dp = um->um_tab.b_actf) == NULL)
	return;
    if ((bp = dp->b_actf) == NULL)
    {
	um->um_tab.b_actf = dp->b_forw;
	goto loop;
    }
    um->um_tab.b_active++;
    unit = DRUNIT(bp->b_dev);
    ui= drinfo[unit];
    addr = DRADDR;
    drp = &drparam[unit];
    drt = &drtype[ui->ui_type];
    drs = &drstate[unit][DRIFVC(bp->b_dev)];
    if (bp->b_flags&B_READ)
    {
	drp->drv_state = DRVS_READ;
	um->um_cmd = drt->dr_rcom | drs->dr_rbits;
    }
    else
    {
	drp->drv_state = DRVS_WRITE;
	um->um_cmd = drt->dr_wcom | drs->dr_wbits;
    }
    addr->drwc = -((bp->b_bcount+1)/sizeof (short));
    ubago(ui);

}

/*
 *  UBA resources allocated.  Start the DR11.
 */

drgo(um)
register struct uba_ctlr *um;
{

    register struct drdevice *addr = (struct drdevice *)um->um_addr;
    register struct uba_device *ui = drinfo[um->um_ctlr];
    register struct buf *bp = um->um_tab.b_actf->b_actf;

    addr->drba = um->um_ubinfo;
    timeout(drtimout, um->um_ctlr, ((bp->b_bcount/BYTESPERSEC)+DRTIMEOUT)*60);
    um->um_cmd = um->um_cmd | ((um->um_ubinfo>>12)&DRCSR_XMEM) | DRCSR_IE;
#if	DEBUG
printf("start %o %o %o\n", addr->drwc, addr->drba, um->um_cmd);
#endif
    if (ui->ui_flags&DR11W)
    {
	addr->drst = um->um_cmd;
    }
    addr->drst = um->um_cmd | DRCSR_GO;

}



/*ARGSUSED*/
unsigned
drphys(bp)
struct buf *bp;
{

    if (bp->b_bcount > 40 * 1024)
	bp->b_bcount = 40 * 1024;
}



drtimout(unit)
{
    register struct uba_ctlr *um = &drctlr[unit];
    register struct uba_device *ui = drinfo[unit];
    register struct drparam *drp = &drparam[unit];
    register struct drdevice *addr;
    register struct buf *dp, *bp;

    if ((dp = um->um_tab.b_actf) == NULL)
    {
	printf("dr%d: spurious tout\n", unit);
	return;
    }
    addr = (struct drdevice *)drinfo[unit]->ui_addr;
    printf("dr%d: tout csr=%b wc=%o ba=%o\n",
	    unit, addr->drst, DRCSR_BITS, (u_short)addr->drwc, (u_short)addr->drba);
    bp = dp->b_actf;
    bp->b_flags |= B_ERROR;
    bp->b_error = ENXIO;
    switch (ui->ui_type)
    {
	case DRV11B:
	    drp->drv_state = DRVS_TOUT;
	    break;
    }
    drintr(unit);

}



drread(dev)
{

    register int unit = DRUNIT(dev);
    register struct drparam *drp = &drparam[unit];
    register struct drstate *drs = &drstate[unit][DRIFVC(dev)];
    register struct uba_device *ui = drinfo[unit];
    int resf;

    if (drtype[ui->ui_type].dr_rcom < 0 ||
        ((ui->ui_type == DRV11B) && (drp->drv_state != DRVS_IDLE)))
    {
	u.u_error = ENXIO;
	return;
    }
    if ((ui->ui_type == DRGMR) && (resf=(drp->gmr_line.res_dev != dev)))
	gmrreserve(dev, &drp->gmr_line);
    physio(drstrategy, &drp->dr_buf, dev, B_READ, drphys);
    if ((ui->ui_type == DRGMR) && resf)
	gmrrelease(dev, &drp->gmr_line);

}



drwrite(dev)
{

    register int unit = DRUNIT(dev);
    register struct drparam *drp = &drparam[unit];
    register struct drstate *drs = &drstate[unit][DRIFVC(dev)];
    register struct uba_device *ui = drinfo[unit];
    int resf;

    if (drtype[ui->ui_type].dr_wcom < 0)
    {
	u.u_error = ENXIO;
	return;
    }
    if (ui->ui_type == DRLP && (DRADDR->drst&DRCSR_ATTN))
	return;			/* LP off-line */
    if ((ui->ui_type == DRGMR) && (resf=(drp->gmr_line.res_dev != dev)))
	gmrreserve(dev, &(drp->gmr_line));
    if (ui->ui_type == DRV11B && (drp->drv_mode == DRVM_LINK))
	if (!drvwaitga(drp)) return;
    physio(drstrategy, &drp->dr_buf, dev, B_WRITE, drphys);
    if ((ui->ui_type == DRGMR) && resf)
	gmrrelease(dev, &drp->gmr_line);

}



int drdebug = 0;

drintr(dr)
{

    register struct drdevice *addr;
    register struct uba_ctlr *um = &drctlr[dr];
    register struct uba_device *ui = drinfo[dr];
    register struct drparam *drp = &drparam[dr];
    register struct buf *bp;
    register struct buf *dp;
    int unit;
    int com;

    if (drdebug)
	 printf("csr=%o, scsr=%o, state=%d, mode=%d\n",
	        (u_short)DRADDR->drst, drp->drv_csr,
		drp->drv_state, drp->drv_mode); 
    if ((ui->ui_type == DRV11B) && (DRADDR->drst&DRCSR_STATB))
    {
	if (drp->drv_mode == DRVM_LINK) switch(drp->drv_state)
	{
	    case DRVS_IDLE:
	    case DRVS_WAIT:
		/*
		 *  Driver is idle.  DRV11 has signaled an interrupt
		 *  - acknowledge interrupt by raising FUNC2
		 *  - delay until DRV11 lowers STATB
		 *  - lower FUNC2
		 *  - remember go ahead state for next write
		 */
		DRADDR->drst = DRCSR_FUNC2;
		if (drvdelay(ui) == 0)
		    goto drverror;
		DRADDR->drst = drp->drv_csr;
		if (drp->drv_state == DRVS_WAIT)
		    wakeup((caddr_t)&(drp->drv_state));
		drp->drv_state = DRVS_GA;
		return;

	    case DRVS_READ:
		/*
		 *  Driver is executing read.  DRV11 has acknowledged start
		 *  of read.
		 *  - lower FUNC2 interrupt request
		 *  - delay until DRV11 lowers STATB
		 *  - continue with read
		 */
		DRADDR->drst = (um->um_cmd & ~DRCSR_FUNC2);
		if (drvdelay(ui) == 0)
		    goto drverror;
		return;

	    case DRVS_TOUT:	/* fall through if timeout */
		break;

	    default:
		printf("dr%d: bad link signal(%d)\n", dr, drp->drv_state);
	    drverror:
		/*
		 *  Some manner of protocol error has occurred causing a
		 *  requested interrupt when none was expected
		 *  - set error state (prevent any more operations)
		 *  - clear IE to prevent any further interrupts (in case
		 *    DRV11 has gone bonkers)
		 */
		drp->drv_state = DRVS_ERROR;
		drp->drv_csr = 0;
		DRADDR->drst = 0;
		return;
	}
	else switch(drp->drv_state)
	/*
	 * Non-link mode
	 */
	{
	    case DRVS_IDLE:
		/*
		 *  DRV11 is sending a signal
		 *  - acknowledge interrupt by raising FUNC2
		 *  - delay until DRV11 lowers STATB
		 *  - lower FUNC2
		 *  - send signal to user process if requested
		 */
		DRADDR->drst = DRCSR_FUNC2;
		if (drvdelay(ui) == 0)
		    goto drverror;
		drp->drv_csr = 0;
		DRADDR->drst = 0;
		if (drp->drv_sign)
		{
		    if (drp->drv_sigp->p_pid == drp->drv_pid)
			psignal(drp->drv_sigp, drp->drv_sign);
		    drp->drv_sign = 0;
		}
		return;

	    case DRVS_INTR:
	       /*
		*  Driver has sent interrupt request to DRV11
		*  - clear FUNC2 interrupt request
		*  - delay until DRV11 lowers STATB
		*  - resume driver at ioctl INTR request
		*/
		DRADDR->drst = drp->drv_csr;
		wakeup(&(drp->drv_state));
		if (drvdelay(ui) == 0)
		    goto drverror;
		drp->drv_state = DRVS_IDLE;
		return;

	    case DRVS_TOUT:	/* fall through if timeout */
		break;

	    default:
		printf("dr%d: uncaught signal(%d)\n", dr, drp->drv_state);
		goto drverror;
		
	}
    }
    if ((dp = um->um_tab.b_actf) == NULL)
    {
	if (ui->ui_type == DRV11B)
	{
	    printf("dr%d: interrupt without signal\n", dr);
	    goto drverror;
	}
	else if (ui->ui_type != DRLP)
	    printf("dr%d: spurious intr\n", dr);
	return;
    }
    bp = dp->b_actf;
    unit = DRUNIT(bp->b_dev);
    addr = DRADDR;
    untimeout(drtimout, unit);
#if	DEBUG
printf("drintr %x\n", addr->drst);
#endif
    if (addr->drst&DRCSR_ERR)
    {
	if ((ui->ui_flags&DR11B) && addr->drba == 0 && (addr->drst&(DRCSR_NXM|DRCSR_ATTN)) == 0)
	{
	    if (com = ((addr->drst + 020)&DRCSR_XMEM));
	    {
		addr->drba = 0;
		um->um_cmd &= ~DRCSR_XMEM;
		um->um_cmd |= com;
#if	DEBUG
		printf("dr%d: rstrt\n", dr);
#endif
		addr->drst = um->um_cmd | DRCSR_GO;
		return;
	    }
	}
	if (ui->ui_type != DRLP || (addr->drst&DRCSR_ATTN) == 0)
	{
	    printf("dr%d: hard error csr=%b wc=%o ba=%o\n",
		    unit, addr->drst, DRCSR_BITS, (u_short)addr->drwc, (u_short)addr->drba);
	    bp->b_flags |= B_ERROR;
	}
    }
    um->um_tab.b_active = 0;
    um->um_tab.b_actf = dp->b_forw;
    dp->b_active = 0;
    dp->b_actf = bp->av_forw;
    bp->b_resid = (-addr->drwc)<<1;
#if	DEBUG
    if (ui->ui_type == DRGMR && bp->b_resid)
    {
	printf("dr%d: resid\n", unit);
    }
#endif
    if (ui->ui_type == DRV11B)
	drp->drv_state = DRVS_IDLE;
    iodone(bp);
    ubadone(um);
    drstart(um);

}



/*
 *  delay until DRV11 lowers STATB.  timeout if this takes an
 *  "unreasonable" amount of time.
 */

drvdelay(ui)
register struct uba_device *ui;
{

    register int count;
    static drvcount = 100;

    for (count=100; count > 0; count--)
    {
	if ((DRADDR->drst&DRCSR_STATB) == 0)
	{
	    if (count < drvcount)
		drvcount = count;
	    return(1);
	}
    }
    printf("dr%d: constant interrupts\n", ui->ui_unit);
    return(0);

}


/*
 * Reset driver after UBA init.
 */

drreset(uban)
int uban;
{

    register struct uba_device *ui;
    register struct uba_ctlr *um;
    register struct drparam *drp;
    register struct buf *drtab;
    register struct buf *bp;
    register int unit;

    for (unit=0; unit <NDR; unit++)
    {
	ui = drinfo[unit];
	if (ui == 0 || ui->ui_ubanum != uban || ui->ui_alive == 0)
	    continue;
	printf(" dr%d", unit);
	drp = &drparam[unit];
	um = ui->ui_mi;
	untimeout(drtimout, unit);
	um->um_tab.b_active = 0;
	if (um->um_ubinfo)
	{
	    printf("<%d>", (um->um_ubinfo>>28)&0xf);
	    ubarelse(ui->ui_ubanum, &(um->um_ubinfo));
	}
	switch (ui->ui_type)
	{
	    case DRV11B:
		DRADDR->drst = drp->drv_csr;
		break;
	}
	drstart(um);
    }

}

drattach(ui)
register struct uba_device *ui;
{

    register struct uba_ctlr *um = &drctlr[ui->ui_unit];
    register struct drdevice *addr = DRADDR;

    ui->ui_mi = um;
    um->um_driver = ui->ui_driver;
    um->um_alive = 1;
    um->um_ubanum = ui->ui_ubanum;
    um->um_hd = ui->ui_hd;
    um->um_addr = ui->ui_addr;
    um->um_ctlr = ui->ui_unit;

    /* determine DR11-B/DR11-W mode */
    ui->ui_type = ui->ui_flags;
    addr->drst = DRCSR_ERR;			/* attempt to read EIR */
    if (addr->drst&DRCSR_GO)			/* got EIR ==> DR11W */
	ui->ui_flags = DR11W;
    else				/* got CSR ==> DR11B */
	ui->ui_flags = DR11B;
    addr->drst = 0;			/* restore to CSR */

}

drprobe(reg)
caddr_t	reg;
{
    register int br,cvec;
    
#ifdef	lint
    br=0; cvec=br; br=cvec;
#endif
    ((struct drdevice *)reg)->drst = DRCSR_ATTN|DRCSR_IE|DRCSR_RDY;
    DELAY(10);
    ((struct drdevice *)reg)->drst = 0;
    if (cvec == 0x200)
    {
	cvec = 0440;
        br = 0x15;
	printf("(faked interrupt) ", cvec, br);
    }
    return(1);
}
#endif	NDRV > 0
