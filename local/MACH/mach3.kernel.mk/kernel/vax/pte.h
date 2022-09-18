/* 
 * Mach Operating System
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 ************************************************************************
 * HISTORY
 * $Log:	pte.h,v $
 * Revision 2.2  91/05/13  06:07:50  af
 * 	Removed CMU conditionals.
 * 	[91/05/12  16:31:56  af]
 * 
 * Revision 2.1  89/08/03  16:24:30  rwd
 * Created.
 * 
 * 10-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Stripped down further for MACH kernel.
 *
 * 19-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: Remove unneeded page maps.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 ************************************************************************
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)pte.h	7.1 (Berkeley) 6/5/86
 */

#ifndef	_PTE_
#define	_PTE_
/*
 * VAX page table entry, as defined by hardware.
 */
#ifndef LOCORE
struct pte
{
unsigned int	pg_pfnum:21,		/* core page frame number or 0 */
		:5,
		pg_m:1,			/* hardware maintained modified bit */
		pg_prot:4,		/* access control */
		pg_v:1;			/* valid bit */
};
#endif	LOCORE

#define	PG_V		0x80000000
#define	PG_PROT		0x78000000
#define	PG_M		0x04000000
#define	PG_PFNUM	0x001fffff

#define	PG_NOACC	0
#define	PG_KW		0x10000000
#define	PG_KR		0x18000000
#define	PG_UW		0x20000000
#define	PG_URKW		0x70000000
#define	PG_URKR		0x78000000

#endif	_PTE_
