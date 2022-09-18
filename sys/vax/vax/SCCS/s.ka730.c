h40239
s 00005/00004/00092
d D 7.4 91/05/09 20:11:11 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00003/00093
d D 7.3 90/12/16 17:02:22 bostic 3 2
c kernel reorg
e
s 00005/00001/00091
d D 7.2 88/07/09 14:11:44 karels 2 1
c update copyrights
e
s 00092/00000/00000
d D 7.1 88/05/20 09:58:20 karels 1 0
c split cpu support into separate files (from chris torek)
e
u
U
t
T
I 1
D 4
/*
D 2
 *	%W% (UofMD/Berkeley) %G%
E 2
I 2
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
 * Copyright (c) 1982, 1986, 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
E 2
 */

#if VAX730

/*
 * 730-specific code.
 */

D 3
#include "param.h"
E 3
I 3
#include "sys/param.h"
E 3

D 3
#include "cpu.h"
E 3
I 3
#include "../include/cpu.h"
E 3
#include "mem.h"
D 3
#include "mtpr.h"
E 3
I 3
#include "../include/mtpr.h"
E 3

struct	mcr730 {
	int	mc_addr;		/* address and syndrome */
	int	mc_err;			/* error bits */
};

#define	M730_UNCORR	0x80000000	/* rds, uncorrectable error */
#define	M730_CRD	0x40000000	/* crd */
#define	M730_FTBPE	0x20000000	/* force tbuf parity error */
#define	M730_ENACRD	0x10000000	/* enable crd interrupt */
#define	M730_MME	0x08000000	/* mem-man enable (ala ipr) */
#define	M730_DM		0x04000000	/* diagnostic mode */
#define	M730_DISECC	0x02000000	/* disable ecc */

#define	M730_INH(mcr)	((mcr)->mc_err = M730_MME)
#define	M730_ENA(mcr)	((mcr)->mc_err = (M730_MME|M730_ENACRD))
#define	M730_ERR(mcr)	((mcr)->mc_err & (M730_UNCORR|M730_CRD))
#define	M730_SYN(addr)	((mcr)->mc_addr & 0x7f)
#define	M730_ADDR(addr)	(((mcr)->mc_addr >> 8) & 0x7fff)

/* enable crd interrupts */
ka730_memenable()
{

	M730_ENA((struct mcr730 *)mcraddr[0]);
}

/* log crd errors */
ka730_memerr()
{
	register struct mcr730 *mcr = (struct mcr730 *)mcraddr[0];
	struct mcr730 amcr;

	/*
	 * Must be careful on the 730 not to use invalid
	 * instructions in I/O space, so make a copy;
	 */
	amcr.mc_addr = mcr->mc_addr;
	amcr.mc_err = mcr->mc_err;
	if (M730_ERR(&amcr)) {
		printf("mcr0: %s", (amcr.mc_err & M730_UNCORR) ?
		    "hard error" : "soft ecc");
		printf(" addr %x syn %x\n", M730_ADDR(&amcr), M730_SYN(&amcr));
		M730_INH(mcr);
	}
}

#define	NMC730	12
char *mc730[] = {
	"tb par",	"bad retry",	"bad intr id",	"cant write ptem",
	"unkn mcr err",	"iib rd err",	"nxm ref",	"cp rds",
	"unalgn ioref",	"nonlw ioref",	"bad ioaddr",	"unalgn ubaddr",
};

struct mc730frame {
	int	mc3_bcnt;		/* byte count == 0xc */
	int	mc3_summary;		/* summary parameter */
	int	mc3_parm[2];		/* parameter 1 and 2 */
	int	mc3_pc;			/* trapped pc */
	int	mc3_psl;		/* trapped psl */
};

ka730_mchk(cmcf)
	caddr_t cmcf;
{
	register struct mc730frame *mcf = (struct mc730frame *)cmcf;
	register u_int type = mcf->mc3_summary;

	printf("machine check %x: %s\n", type,
	    type < NMC730 ? mc730[type] : "???");
	printf("\tparams %x,%x pc %x psl %x mcesr %x\n",
	    mcf->mc3_parm[0], mcf->mc3_parm[1],
	    mcf->mc3_pc, mcf->mc3_psl, mfpr(MCESR));
	mtpr(MCESR, 0xf);
	return (MCHK_PANIC);
}
#endif
E 1
