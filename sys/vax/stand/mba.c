/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mba.c	7.9 (Berkeley) 12/16/90
 */

#include "../include/pte.h"

#include "sys/param.h"
#include "sys/vm.h"

#include "../include/mtpr.h"
#include "../mba/mbareg.h"
#include "../mba/hpreg.h"

#include "stand/saio.h"
#include "savax.h"

mbastart(io, unit, func)
	register struct iob *io;
	int unit, func;
{
	struct mba_regs *mba = mbamba(io->i_adapt);
	struct mba_drv *drv = mbadrv(io->i_adapt, unit);
	register struct pte *pte = mba->mba_map;
	unsigned int v;
	int npf, o, vaddr;

	v = btop(io->i_ma);
	o = (int)io->i_ma & PGOFSET;
	npf = btoc(io->i_cc + o);
	vaddr = o;
	while (--npf >= 0)
		*(int *)pte++ = v++ | PG_V;
	mba->mba_sr = -1;
	mba->mba_bcr = -io->i_cc;
	mba->mba_var = vaddr;
	if (io->i_flgs&F_SSI)
		drv->mbd_of |= HPOF_SSEI;
	switch (io->i_flgs & F_TYPEMASK) {

	case F_RDDATA:			/* standard read */
		drv->mbd_cs1 = MB_RCOM|MB_GO;
		mbawait(io, unit);
		return(0);

	case F_WRDATA:			/* standard write */
		drv->mbd_cs1 = MB_WCOM|MB_GO;
		mbawait(io, unit);
		return(0);

	/* the following commands apply to disks only */

	case F_HDR|F_RDDATA:	
		drv->mbd_cs1 = HP_RHDR|HP_GO;
		break;

	case F_HDR|F_WRDATA:
		drv->mbd_cs1 = HP_WHDR|HP_GO;
		break;

	case F_CHECK|F_WRDATA:
	case F_CHECK|F_RDDATA:
		drv->mbd_cs1 = HP_WCDATA|HP_GO;
		break;

	case F_HCHECK|F_WRDATA:
	case F_HCHECK|F_RDDATA:
		drv->mbd_cs1 = HP_WCHDR|HP_GO;
		break;

	default:
		goto error;
	}
	mbawait(io, unit);
	if ((drv->mbd_dt & MBDT_TAP) == 0)
		return (0);
error:
	io->i_error = ECMD;
	io->i_flgs &= ~F_TYPEMASK;
	return (1);
}

mbawait(io, unit)
	register struct iob *io;
	int unit;
{
	struct mba_regs *mba = mbamba(io->i_adapt);
	struct mba_drv *drv = mbadrv(io->i_adapt, unit);

	while (mba->mba_sr & MBSR_DTBUSY)
		DELAY(100);
}

mbainit(mbanum)
	int mbanum;
{
	register struct mba_regs *mba;

	if (mbanum >= nmba)
		return (0);
	mba = mbaddr[mbanum];
	if (badaddr((char *)mba, sizeof(long)))
		return (0);
	if ((mbaact & (1<<mbanum)) == 0) {
		mba->mba_cr = MBCR_INIT;
		mbaact |= 1<<mbanum;
	}
	return (1);
}
