/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	hpmaptype.c,v $
 * Revision 2.4  89/03/09  21:14:52  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  14:32:15  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/08  13:43:16  rvb
 * The tables have been updated to the current vaxmba/hp.c tables.
 * This means CS_DISK must be set as required for your disks.
 * 
 *
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed bug which neglected to strip high bits from unit number
 *	before checking against SI model byte.
 *	[ V5.1(F8) ]
 *
 **********************************************************************
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)hpmaptype.c	7.1 (Berkeley) 6/5/86
 */

/*
 * RP??/RM?? drive type mapping routine.
 */
#include <machine/pte.h>

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/fs.h>

#include <vaxmba/hpreg.h>
#include <vaxmba/mbareg.h>

#include "saio.h"
#include "savax.h"

/* THIS SHOULD BE READ OFF THE PACK, PER DRIVE */
short rp06_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 37 */
	/* 33440, */	38,		/* B=cyl 38 thru 117 */
	/* 340670, */	0,		/* C=cyl 0 thru 814 */
	/* 15884, */	118,		/* D=cyl 118 thru 155 */
	/* 55936, */	156,		/* E=cyl 156 thru 289 */
	/* 219384, */	290,		/* F=cyl 290 thru 814 */
	/* 291280, */	118,		/* G=cyl 118 thru 814 */
	/* 0, */	0
};
short rp05_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 37 */
	/* 33440, */	38,		/* B=cyl 38 thru 117 */
	/* 171798, */	0,		/* C=cyl 0 thru 410 */
	/* 15884, */	118,		/* D=cyl 118 thru 155 */
	/* 55936, */	156,		/* E=cyl 156 thru 289 */
	/* 50512, */	290,		/* F=cyl 290 thru 410 */
	/* 122408, */	118,		/* G=cyl 118 thru 410 */
	/* 0, */	0
};
short rm03_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 99 */
	/* 33440, */	100,		/* B=cyl 100 thru 308 */
	/* 131680, */	0,		/* C=cyl 0 thru 822 */
	/* 15884, */	309,		/* D=cyl 309 thru 408 */
	/* 55936, */	409,		/* E=cyl 409 thru 758 */
	/* 10144, */	759,		/* F=cyl 759 thru 822 */
#if	CS_DISK
	/* 81984, */	310,		/* G=cyl 310 thru 822 */
#else	CS_DISK
	/* 82144, */	309,		/* G=cyl 309 thru 822 */
#endif	CS_DISK
	/* 0, */	0
};
short rm05_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 26 */
	/* 33440, */	27,		/* B=cyl 27 thru 81 */
	/* 500384, */	0,		/* C=cyl 0 thru 822 */
	/* 15884, */	562,		/* D=cyl 562 thru 588 */
	/* 55936, */	589,		/* E=cyl 589 thru 680 */
	/* 86240, */	681,		/* F=cyl 681 thru 822 */
	/* 158592, */	562,		/* G=cyl 562 thru 822 */
	/* 291346, */	82,		/* H=cyl 82 thru 561 */
};
short rm80_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 36 */
	/* 33440, */	37,		/* B=cyl 37 thru 114 */
	/* 242606, */	0,		/* C=cyl 0 thru 558 */
	/* 15884, */	115,		/* D=cyl 115 thru 151 */
	/* 55936, */	152,		/* E=cyl 152 thru 280 */
	/* 120559, */	281,		/* F=cyl 281 thru 558 */
	/* 192603, */	115,		/* G=cyl 115 thru 558 */
	/* 0, */	0
};
short rp07_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 9 */
	/* 66880, */	10,		/* B=cyl 10 thru 51 */
	/* 1008000, */ 0,		/* C=cyl 0 thru 629 */
	/* 15884, */	235,		/* D=cyl 235 thru 244 */
	/* 307200, */	245,		/* E=cyl 245 thru 436 */
	/* 308650, */	437,		/* F=cyl 437 thru 629 */
	/* 631850, */	235,		/* G=cyl 235 thru 629 */
	/* 291346, */	52,		/* H=cyl 52 thru 234 */
};
short cdc9775_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 12 */
	/* 66880, */	13,		/* B=cyl 13 thru 65 */
	/* 1077760, */ 0,		/* C=cyl 0 thru 841 */
	/* 15884, */	294,		/* D=cyl 294 thru 306 */
	/* 307200, */	307,		/* E=cyl 307 thru 546 */
	/* 377440, */	547,		/* F=cyl 547 thru 841 */
	/* 701280, */	294,		/* G=cyl 294 thru 841 */
	/* 291346, */	66,		/* H=cyl 66 thru 293 */
};
short cdc9730_sizes[8] = {
#if	CS_DISK
	/* ( 50-  0)*(32*10), */   0,	/* A=cyl   0 thru  49 */
	/* (155- 50)*(32*10), */  50,	/* B=cyl  50 thru 154 */
	/* (823-  0)*(32*10), */   0,	/* C=cyl   0 thru 822 (entire disk) */
	/* (456-155)*(32*10), */ 155,	/* D=cyl 155 thru 455 */
	/* (823-456)*(32*10)
		  -32-126, */ 456,	/* E=cyl 456 thru 822 */
	/* 0, */	0,		/* F unused */
	/* 0, */	0,		/* G unused */
	/* (823-155)*(32*10)
		  -32-126, */ 155,	/* H=cyl 155 thru 822 */
#else	CS_DISK
	/* 15884, */	0,		/* A=cyl 0 thru 49 */
	/* 33440, */	50,		/* B=cyl 50 thru 154 */
	/* 263360, */	0,		/* C=cyl 0 thru 822 */
	/* 15884, */	155,		/* D=cyl 155 thru 204 */
	/* 55936, */	205,		/* E=cyl 205 thru 379 */
	/* 141664, */	380,		/* F=cyl 380 thru 822 */
	/* 213664, */	155,		/* G=cyl 155 thru 822 */
	/* 0, */	0,
#endif	CS_DISK
};
short capricorn_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 31 */
	/* 33440, */	32,		/* B=cyl 32 thru 97 */
	/* 524288, */	0,		/* C=cyl 0 thru 1023 */
	/* 15884, */	668,		/* D=cyl 668 thru 699 */
	/* 55936, */	700,		/* E=cyl 700 thru 809 */
	/* 109472, */	810,		/* F=cyl 810 thru 1023 */
	/* 182176, */	668,		/* G=cyl 668 thru 1023 */
	/* 291346, */	98,		/* H=cyl 98 thru 667 */
};
short eagle_sizes[8] = {
#if	CS_DISK
	/* ( 17-  0)*(48*20), */   0,	/* A=cyl   0 thru  16 */
	/* ( 52- 17)*(48*20), */  17,	/* A=cyl  17 thru  51 */
	/* (842-  0)*(48*20), */   0,	/* C=cyl   0 thru 841 */
	/* (153- 52)*(48*20), */  52,	/* D=cyl  52 thru 152 */
	/* (842-153)*(48*20)
		  -48-126, */ 153,	/* E=cyl 153 thru 841 */
	/* 0, */	0,		/* F unused */
	/* 0, */	0,		/* G unused */
	/* (842- 52)*(48*20)
		  -48-126, */  52,	/* H=cyl  52 thru 841 */
#else	CS_DISK
	/* 15884, */	0,		/* A=cyl 0 thru 16 */
	/* 66880, */	17,		/* B=cyl 17 thru 86 */
	/* 808320, */	0,		/* C=cyl 0 thru 841 */
	/* 15884, */	391,		/* D=cyl 391 thru 407 */
	/* 307200, */	408,		/* E=cyl 408 thru 727 */
	/* 109296, */	728,		/* F=cyl 728 thru 841 */
	/* 432816, */	391,		/* G=cyl 391 thru 841 */
	/* 291346, */	87,		/* H=cyl 87 thru 390 */
#endif	CS_DISK
};
short ampex_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 26 */
	/* 33440, */	27,		/* B=cyl 27 thru 81 */
	/* 495520, */	0,		/* C=cyl 0 thru 814 */
	/* 15884, */	562,		/* D=cyl 562 thru 588 */
	/* 55936, */	589,		/* E=cyl 589 thru 680 */
	/* 81312, */	681,		/* F=cyl 681 thru 814 */
	/* 153664, */	562,		/* G=cyl 562 thru 814 */
	/* 291346, */	82,		/* H=cyl 82 thru 561 */
};
short fj2361_sizes[8] = {
	/* 15884, */	0,		/* A=cyl 0 thru 12 */
	/* 66880, */	13,		/* B=cyl 13 thru 65 */
	/* 1077760, */ 0,		/* C=cyl 0 thru 841 */
	/* 15884, */	294,		/* D=cyl 294 thru 306 */
	/* 307200, */	307,		/* E=cyl 307 thru 546 */
	/* 377408, */	547,		/* F=cyl 547 thru 841 */
	/* 701248, */	294,		/* G=cyl 294 thru 841 */
	/* 291346, */	66,		/* H=cyl 66 thru 293 */
};
/* END OF STUFF WHICH SHOULD BE READ IN PER DISK */


/*
 * Table for converting Massbus drive types into
 * indices into the partition tables.  Slots are
 * left for those drives divined from other means
 * (e.g. SI, AMPEX, etc.).
 */
short	hptypes[] = {
#define HPDT_RM03	0
	MBDT_RM03,
#define HPDT_RM05	1
	MBDT_RM05,
#define HPDT_RP06	2
	MBDT_RP06,
#define HPDT_RM80	3
	MBDT_RM80,
#define HPDT_RP04	4
	MBDT_RP04,
#define HPDT_RP05	5
	MBDT_RP05,
#define HPDT_RP07	6
	MBDT_RP07,
#define HPDT_ML11A	7
	MBDT_ML11A,
#define HPDT_ML11B	8
	MBDT_ML11B,
#define HPDT_9775	9
	-1,
#define HPDT_9730	10
	-1,
#define HPDT_CAPRICORN	11
	-1,
#define HPDT_EAGLE	12
	-1,
#define HPDT_9300	13
	-1,
#define HPDT_RM02	14
	MBDT_RM02,		/* beware, actually mapped */
#define HPDT_2361	15
	-1,
	0
};

/*
 * These variable are all measured in sectors.  
 * Sdist is how much to "lead" in the search for a desired sector
 * (i.e. if want N, search for N-sdist.)
 * Maxdist and mindist define the region right before our desired sector within
 * which we don't bother searching.  We don't search when we are already less
 * then maxdist and more than mindist sectors "before" our desired sector.
 * Maxdist should be >= sdist.
 * 
 * Beware, sdist, mindist and maxdist are not well tuned
 * for many of the drives listed in this table.
 * Try patching things with something i/o intensive
 * running and watch iostat.
 */
struct st hpst[] = {
    { 32, 5,	32*5,	823,	rm03_sizes },
    { 32, 19,	32*19,	823,	rm05_sizes },
    { 22,19,	22*19,	815,	rp06_sizes },
    { 31, 14, 	31*14,	559,	rm80_sizes },
    { 22, 19,	22*19,	411,	rp05_sizes },
    { 22, 19,	22*19,	411,	rp05_sizes },
    { 50, 32,	50*32,	630,	rp07_sizes },
    { 1, 1,	1,	1,	0 },
    { 1, 1,	1,	1,	0 },
    { 32, 40,	32*40,	843,	cdc9775_sizes },
    { 32, 10,	32*10,	823,	cdc9730_sizes },
    { 32, 16,	32*16,	1024,	capricorn_sizes },
    { 48, 20,	48*20,	842,	eagle_sizes },
    { 32, 19,	32*19,	815,	ampex_sizes },
    { 64, 20,	64*20,	842,	fj2361_sizes },
};
#define NTYPES	(sizeof(hpst) / sizeof(hpst[0]))

#define MASKREG(reg)	((reg)&0xffff)

hpmaptype(hpaddr, type, unit)
	register struct hpdevice *hpaddr;
	unsigned type;
	int unit;
{
	int hpsn;

	/*
	 * Handle SI model byte stuff when
	 * we think it's an RM03 or RM05.
	 */
	if (type == HPDT_RM03 || type == HPDT_RM05) {
		hpsn = hpaddr->hpsn;
		if ((hpsn & SIMB_LU) != UNITTODRIVE(unit))
			return (type);
		switch ((hpsn & SIMB_MB) &~ (SIMB_S6|SIRM03|SIRM05)) {

		case SI9775D:
			return (HPDT_9775);

		case SI9730D:
			return (HPDT_9730);

		case SI9766:
			return (HPDT_RM05);

		case SI9762:
			return (HPDT_RM03);

		case SICAPD:
			return (HPDT_CAPRICORN);

		case SI9751D:
			return (HPDT_EAGLE);
		}
		return (type);
	}
	/*
	 * RM02: EMULEX controller.  Map to correct
	 * drive type by checking the holding
	 * register for the disk geometry.
	 */
	if (type == HPDT_RM02) {
		int newtype, nsectors, ntracks, ncyl;

		hpaddr->hpcs1 = HP_NOP;
		hpaddr->hphr = HPHR_MAXTRAK;
		ntracks = MASKREG(hpaddr->hphr) + 1;
		DELAY(100);
		hpaddr->hpcs1 = HP_NOP;
		hpaddr->hphr = HPHR_MAXSECT;
		nsectors = MASKREG(hpaddr->hphr) + 1;
		DELAY(100);
		hpaddr->hpcs1 = HP_NOP;
		hpaddr->hphr = HPHR_MAXCYL;
		ncyl = MASKREG(hpaddr->hphr) + 1;
		for (newtype = 0; newtype < NTYPES; newtype++)
			if (hpst[newtype].nsect == nsectors &&
			    hpst[newtype].ntrak == ntracks &&
			    hpst[newtype].ncyl == ncyl)
				break;

		if (newtype >= NTYPES) {
			printf("RM02 with %d sectors, %d tracks, %d cylinders?\n",
				nsectors, ntracks, ncyl);
			newtype = type;
		}
	done:
		hpaddr->hpcs1 = HP_DCLR|HP_GO;
		return (newtype);
	}
	/*
	 * ML11's all map to the same type.
	 */
	if (type == HPDT_ML11A || type == HPDT_ML11B)
		return (HPDT_ML11A);
	return (type);
}
