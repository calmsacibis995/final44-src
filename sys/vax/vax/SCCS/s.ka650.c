h40492
s 00008/00008/00187
d D 7.7 90/12/16 17:02:19 bostic 7 6
c kernel reorg
e
s 00001/00011/00194
d D 7.6 90/06/28 22:32:28 bostic 6 5
c new copyright notice
e
s 00004/00004/00201
d D 7.5 88/11/08 17:34:43 tef 5 4
c avoid null pointer on machine check printf's
e
s 00003/00000/00202
d D 7.4 88/11/02 11:36:18 bostic 4 3
c credit Mt. Xinu
e
s 00014/00003/00188
d D 7.3 88/10/31 20:06:52 bostic 3 2
c add Berkeley specific copyright notice
e
s 00012/00003/00179
d D 7.2 88/09/22 06:39:54 tef 2 1
c more information on machine checks
e
s 00182/00000/00000
d D 7.1 88/08/27 07:15:36 tef 1 0
c date and time created 88/08/27 07:15:36 by tef
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1988  Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
I 4
 * This code is derived from software contributed to Berkeley by
 * Mt. Xinu.
 *
E 4
D 6
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 3
 *
 *	%W% (Berkeley) %G%
 */

#if VAX650

/*
 * vax650-specific code.
 */

D 7
#include "param.h"
#include "time.h"
#include "kernel.h"
I 2
#include "systm.h"
E 7
I 7
#include "sys/param.h"
#include "sys/time.h"
#include "sys/kernel.h"
#include "sys/systm.h"
E 7
E 2

D 7
#include "cpu.h"
#include "clock.h"
#include "psl.h"
E 7
I 7
#include "../include/cpu.h"
#include "../include/clock.h"
#include "../include/psl.h"
E 7
#include "mem.h"
D 7
#include "mtpr.h"
E 7
I 7
#include "../include/mtpr.h"
E 7
#include "ka650.h"


ka650_init()
{
	ioaccess(KA650_MERR, KA650MERRmap, sizeof(ka650merr));
	ioaccess(KA650_CBD, KA650CBDmap, sizeof(ka650cbd));
	ioaccess(KA650_SSC, KA650SSCmap, sizeof(ka650ssc));
	ioaccess(KA650_IPCR, KA650IPCRmap, sizeof(ka650ipcr));
	ioaccess(KA650_CACHE, KA650CACHEmap, KA650_CACHESIZE);
	ka650encache();
I 2
	if (ctob(physmem) > ka650merr.merr_qbmbr) {
		printf("physmem(0x%x) > qbmbr(0x%x)\n",
		    ctob(physmem), ka650merr.merr_qbmbr);
		panic("qbus map unprotected");
	}
E 2
}

ka650_clkstartrt()
{
	mtpr(ICCS, ICCS_IE);
}

ka650_memnop()
{
	/* void */
}

ka650_memerr()
{
	register char *cp = (char *)0;
	register int m;
	extern u_int cache2tag;

	if (ka650cbd.cbd_cacr & CACR_CPE) {
		printf("cache 2 tag parity error: ");
		if (time.tv_sec - cache2tag < 7) {
			ka650discache();
			printf("cacheing disabled\n");
		} else {
			cache2tag = time.tv_sec;
			printf("flushing cache\n");
			ka650encache();
		}
	}
	m = ka650merr.merr_errstat;
	ka650merr.merr_errstat = MEM_EMASK;
	if (m & MEM_CDAL) {
		cp = "Bus Parity";
	} else if (m & MEM_RDS) {
		cp = "Hard ECC";
	} else if (m & MEM_CRD) {
		cp = "Soft ECC";
	}
	if (cp) {
		printf("%sMemory %s Error: page 0x%x\n",
			(m & MEM_DMA) ? "DMA " : "", cp,
			(m & MEM_PAGE) >> MEM_PAGESHFT);
	}
}

#define NMC650	15
char *mc650[] = {
	0,			"FPA proto err",	"FPA resv inst",
	"FPA Ill Stat 2",	"FPA Ill Stat 1",	"PTE in P0, TB miss",
	"PTE in P1, TB miss",	"PTE in P0, Mod",	"PTE in P1, Mod",
	"Illegal intr IPL",	"MOVC state error",	"bus read error",
	"SCB read error",	"bus write error",	"PCB write error"
};
u_int	cache1tag;
u_int	cache1data;
u_int	cdalerr;
u_int	cache2tag;

struct mc650frame {
	int	mc65_bcnt;		/* byte count == 0xc */
	int	mc65_summary;		/* summary parameter */
	int	mc65_mrvaddr;		/* most recent vad */
	int	mc65_istate1;		/* internal state */
	int	mc65_istate2;		/* internal state */
	int	mc65_pc;		/* trapped pc */
	int	mc65_psl;		/* trapped psl */
};

ka650_mchk(cmcf)
	caddr_t cmcf;
{
	register struct mc650frame *mcf = (struct mc650frame *)cmcf;
	register u_int type = mcf->mc65_summary;
	register u_int i;

D 5
	printf("machine check %x: %s%s\n", type);
E 5
I 5
	printf("machine check %x", type);
E 5
	if (type >= 0x80 && type <= 0x83)
		type -= (0x80 + 11);
D 5
	if (type < NMC650)
		printf("%s: ", mc650[type]);
	printf("vap %x istate1 %x istate2 %x pc %x psl %x\n",
E 5
I 5
	if (type < NMC650 && mc650[type])
		printf(": %s", mc650[type]);
	printf("\n\tvap %x istate1 %x istate2 %x pc %x psl %x\n",
E 5
	    mcf->mc65_mrvaddr, mcf->mc65_istate1, mcf->mc65_istate2,
	    mcf->mc65_pc, mcf->mc65_psl);
I 2
	printf("dmaser=0x%b qbear=0x%x dmaear=0x%x\n",
	    ka650merr.merr_dser, DMASER_BITS, ka650merr.merr_qbear,
	    ka650merr.merr_dear);
	ka650merr.merr_dser = DSER_CLEAR;
E 2

	i = mfpr(CAER);
	mtpr(CAER, CAER_MCC | CAER_DAT | CAER_TAG);
	if (i & CAER_MCC) {
D 2
		printf("cache 1");
E 2
I 2
		printf("cache 1 ");
E 2
		if (i & CAER_DAT) {
			printf("data");
			i = cache1data;
			cache1data = time.tv_sec;
		}
		if (i & CAER_TAG) {
			printf("tag");
			i = cache1tag;
			cache1tag = time.tv_sec;
		}
D 2
	} else
	    if ((i & CAER_MCD) || (ka650merr.merr_errstat & MEM_CDAL)) {
E 2
I 2
	} else if ((i & CAER_MCD) || (ka650merr.merr_errstat & MEM_CDAL)) {
E 2
		printf("CDAL");
		i = cdalerr;
		cdalerr = time.tv_sec;
	}
	if (time.tv_sec - i < 7) {
		ka650discache();
		printf(" parity error:  cacheing disabled\n");
	} else {
		printf(" parity error:  flushing cache\n");
		ka650encache();
	}
	/*
	 * May be able to recover if type is 1-4, 0x80 or 0x81, but
	 * only if FPD is set in the saved PSL, or bit VCR in Istate2
	 * is clear.
	 */
	if ((type > 0 && type < 5) || type == 11 || type == 12) {
		if ((mcf->mc65_psl & PSL_FPD)
		    || !(mcf->mc65_istate2 & IS2_VCR)) {
			ka650_memerr();
			return (MCHK_RECOVERED);
		}
	}
	return (MCHK_PANIC);
}

/*
 * Make sure both caches are off and not in diagnostic mode.  Clear the
 * 2nd level cache (by writing to each quadword entry), then enable it.
 * Enable 1st level cache too.
 */
ka650encache()
{
	register int i;

	ka650discache();
	for (i = 0; i < (KA650_CACHESIZE / sizeof(ka650cache[0])); i += 2)
		ka650cache[i] = 0;
	ka650cbd.cbd_cacr = CACR_CEN;
	mtpr(CADR, CADR_SEN2 | CADR_SEN1 | CADR_CENI | CADR_CEND);
}

ka650discache()
{
	mtpr(CADR, 0);
	ka650cbd.cbd_cacr = CACR_CPE;
}
#endif
E 1
