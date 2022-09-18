/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	vm_machdep.c,v $
 * Revision 2.4  89/02/26  10:49:55  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/24  03:02:51  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:07:51  mwyoung]
 * 
 *
 * 17-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Removed include of cmap.h, text.h for MACH.
 *
 * 12-Mar-86  David Golub (dbg) at Carnegie-Mellon University
 *	Disabled putmemc, getmemc in favor of working versions
 *	in phys.s
 *
 * 25-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 21-Oct-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMU_BUGFIX:  Picked up block# sign extension fix from bug list.
 *
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)vm_machdep.c	7.1 (Berkeley) 6/5/86
 */

#include <vax/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/vm.h>

#include <vax/mtpr.h>


/*
 * Move pages from one kernel virtual address to another.
 * Both addresses are assumed to reside in the Sysmap,
 * and size must be a multiple of CLSIZE.
 */
pagemove(from, to, size)
	register caddr_t from, to;
	int size;
{
	register struct pte *fpte, *tpte;

	if (size % CLBYTES)
		panic("pagemove");
	fpte = &Sysmap[btop(from - 0x80000000)];
	tpte = &Sysmap[btop(to - 0x80000000)];
	while (size > 0) {
		*tpte++ = *fpte;
		*(int *)fpte++ = 0;
		mtpr(TBIS, from);
		mtpr(TBIS, to);
		from += NBPG;
		to += NBPG;
		size -= NBPG;
	}
}
