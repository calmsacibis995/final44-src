h05032
s 00005/00004/00101
d D 7.4 91/05/09 20:11:12 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00003/00102
d D 7.3 90/12/16 17:02:24 bostic 3 2
c kernel reorg
e
s 00005/00001/00100
d D 7.2 88/07/09 14:11:46 karels 2 1
c update copyrights
e
s 00101/00000/00000
d D 7.1 88/05/20 09:58:19 karels 1 0
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

#if VAX750

/*
 * 750-specific code.
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

struct	mcr750 {
	int	mc_err;			/* error bits */
	int	mc_inh;			/* inhibit crd */
};

#define	M750_ICRD	0x10000000	/* inhibit crd interrupts, in [1] */
#define	M750_UNCORR	0xc0000000	/* uncorrectable error, in [0] */
#define	M750_CORERR	0x20000000	/* correctable error, in [0] */

#define	M750_INH(mcr)	((mcr)->mc_inh = 0)
#define	M750_ENA(mcr)	((mcr)->mc_err = (M750_UNCORR|M750_CORERR), \
			 (mcr)->mc_inh = M750_ICRD)
#define	M750_ERR(mcr)	((mcr)->mc_err & (M750_UNCORR|M750_CORERR))

#define	M750_SYN(err)	((err) & 0x7f)
#define	M750_ADDR(err)	(((err) >> 9) & 0x7fff)

/* enable crd interrupts */
ka750_memenable()
{

	M750_ENA((struct mcr750 *)mcraddr[0]);
}

/* log crd errors */
ka750_memerr()
{
	register struct mcr750 *mcr = (struct mcr750 *)mcraddr[0];
	register int err;

	if (M750_ERR(mcr)) {
		err = mcr->mc_err;	/* careful with i/o space refs */
		printf("mcr0: %s", err & M750_UNCORR ?
		    "hard error" : "soft ecc");
		printf(" addr %x syn %x\n", M750_ADDR(err), M750_SYN(err));
		M750_INH(mcr);
	}
}

extern char *mc780750[];

struct mc750frame {
	int	mc5_bcnt;		/* byte count == 0x28 */
	int	mc5_summary;		/* summary parameter (as above) */
	int	mc5_va;			/* virtual address register */
	int	mc5_errpc;		/* error pc */
	int	mc5_mdr;
	int	mc5_svmode;		/* saved mode register */
	int	mc5_rdtimo;		/* read lock timeout */
	int	mc5_tbgpar;		/* tb group parity error register */
	int	mc5_cacherr;		/* cache error register */
	int	mc5_buserr;		/* bus error register */
	int	mc5_mcesr;		/* machine check status register */
	int	mc5_pc;			/* trapped pc */
	int	mc5_psl;		/* trapped psl */
};

#define MC750_TBERR	2		/* type code of cp tbuf par */
#define	MC750_TBPAR	4		/* tbuf par bit in mcesr */

ka750_mchk(cmcf)
	caddr_t cmcf;
{
	register struct mc750frame *mcf = (struct mc750frame *)cmcf;
	register int type = mcf->mc5_summary;
	int mcsr = mfpr(MCSR);

	printf("machine check %x: %s%s\n", type, mc780750[type&0xf],
	    (type&0xf0) ? " abort" : " fault"); 
	mtpr(TBIA, 0);
	mtpr(MCESR, 0xf);
	printf(
"\tva %x errpc %x mdr %x smr %x rdtimo %x tbgpar %x cacherr %x\n",
	    mcf->mc5_va, mcf->mc5_errpc, mcf->mc5_mdr, mcf->mc5_svmode,
	    mcf->mc5_rdtimo, mcf->mc5_tbgpar, mcf->mc5_cacherr);
	printf("\tbuserr %x mcesr %x pc %x psl %x mcsr %x\n",
	    mcf->mc5_buserr, mcf->mc5_mcesr, mcf->mc5_pc, mcf->mc5_psl,
	    mcsr);
	if (type == MC750_TBERR && (mcf->mc5_mcesr&0xe) == MC750_TBPAR) {
		printf("tbuf par: flushing and returning\n");
		return (MCHK_RECOVERED);
	}
	return (MCHK_PANIC);
}
#endif
E 1
