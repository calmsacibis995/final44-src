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
 * $Log:	savax.h,v $
 * Revision 2.3  89/03/09  21:16:54  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  14:35:36  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed unit to adaptor mapping to provide an intermediate 3-
 *	bit range in the unit number between the adaptor and the drive
 *	to indicate the specific controller on an adaptor (meaningful
 *	only for UBA).
 *	[ V5.1(F8) ]
 *
 **********************************************************************
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)savax.h	7.1 (Berkeley) 6/5/86
 */

/*
 * Standalone definitions peculiar to vaxen
 * The mba devices in the standalone system are addressed as 
 *	xx(unit,section)
 * where unit is
 *	8*mbanum+drive
 * The mbadrv macro gives the address of the device registers
 * for the specified unit; the mbamba macro gives the address of the
 * mba registers themselves.
 *
 * The uba devices are also addressed by giving, as unit,
 *	8*ubanum+drive
 * The ubamem macro converts a specified unibus address (ala pdp-11)
 * into a unibus memory address space address.
 */

int	cpu;		/* see <sys/cpu.h> */

#define MAXNMBA	4
#define MAXNUBA	4
struct	mba_regs **mbaddr;
int	mbaact;
caddr_t	*umaddr;
struct	uba_regs **ubaddr;

/*
 *  The unit number for mba devices is now recorded as
 *	64*mbanum+drive
 *  for compatibility with the new uba unit numbering below.
 */
#define UNITTOMBA(unit)		((unit)>>6)
#define UNITTODRIVE(unit)	((unit)&07)

#define mbamba(unit)		(mbaddr[UNITTOMBA(unit)])
#define mbadrv(unit) 		(&mbamba(unit)->mba_drv[UNITTODRIVE(unit)])

/*
 *  The unit number for uba devices is now recorded as
 *	64*ubanum+8*ctlrnum+drive
 *  to permit specification of multiple controllers.
 */
#define UNITTOUBA(unit)		((unit)>>6)
#define UNITTOCTLR(unit)	(((unit)>>3)&0x7)
#define ubauba(unit)		(ubaddr[UNITTOUBA(unit)])
#define ubamem(unit, off)	((umaddr[UNITTOUBA(unit)]+ubdevreg(off)))

#define PHYSUBA0	0x20006000
#define PHYSMBA0	0x20010000
#define PHYSMBA1	0x20012000
#define PHYSUMEM	0x2013e000

/*
 * RM03/5 (4-byte header plus CRC) format information:
 * codes for sector header word 1
 */
#define HDR1_FMT22	0x1000	/* standard 16 bit format */
#define HDR1_OKSCT	0xc000	/* sector ok */
#define HDR1_SSF	0x2000	/* skip sector flag */
