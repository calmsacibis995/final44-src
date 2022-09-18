/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * Copyright (c) 1985 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	uba.c,v $
 * Revision 2.4  89/03/09  21:17:37  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  14:36:22  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/08  13:47:35  rvb
 * Added VAXxxx defines to keep ubafree happy.  This won't
 * generate too much code so why not.
 * 
 *
 * 01-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	added support for MicroVax-I and -II.
 *
 **********************************************************************
 */ 
 
#define VAX8600	1
#define VAX780	1
#define VAX750	1
#define VAX730	1

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)uba.c	7.1 (Berkeley) 6/5/86
 */

#include <machine/pte.h>

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/vm.h>
#include <sys/fs.h>

#include <vax/cpu.h>
#include <vaxuba/ubareg.h>

#include "saio.h"
#include "savax.h"

/*
 * Note... this routine does not
 * really allocate; unless bdp == 2
 * you always get the same space.
 * When bdp == 2 you get some other space.
 */
ubasetup(io, bdp)
	register struct iob *io;
	int bdp;
{
	int npf;
	unsigned v;
	register struct pte *pte;
	int o, temp, reg;
	static int lastreg = 128+64;

	/*
	 *  No mapping on MicroVax-I.
	 */
	if (cpu == VAX_1)
		return((int)io->i_ma);
	v = btop(io->i_ma);
	o = (int)io->i_ma & PGOFSET;
	npf = btoc(io->i_cc + o) +1;
	if (bdp == 2) {
		reg = lastreg;
		lastreg += npf;
		bdp = 0;
	} else
		reg = 0;
	pte = &ubauba(io->i_unit)->uba_map[reg];
	temp = (bdp << 21) | UBAMR_MRV;
	if (bdp && (o & 01))
		temp |= UBAMR_BO;
	v &= 0x1fffff;			/* drop to physical addr */
	while (--npf != 0)
		*(int *)pte++ = v++ | temp;
	*(int *)pte++ = 0;
	return ((bdp << 28) | (reg << 9) | o);
}

ubafree(io, mr)
	struct iob *io;
	int mr;
{
	register int bdp;
 
	bdp = (mr >> 28) & 0x0f;
	if (bdp == 0)
		return;
	switch (cpu) {

	case VAX_8600:
	case VAX_780:
		ubauba(io->i_unit)->uba_dpr[bdp] |= UBADPR_BNE;
		break;

	case VAX_750:
		ubauba(io->i_unit)->uba_dpr[bdp] |=
		     UBADPR_PURGE|UBADPR_NXM|UBADPR_UCE;
		break;
	case VAX_730:
		break;
	}
}
