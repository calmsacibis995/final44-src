h37795
s 00002/00002/00040
d D 8.1 93/06/10 23:02:42 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00041
d D 7.2 92/10/11 11:14:21 bostic 2 1
c make kernel includes standard
e
s 00042/00000/00000
d D 7.1 92/01/07 20:35:52 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "machConst.h"
E 2
I 2
#include <machine/machConst.h>
E 2

#define	PSL_LOWIPL	(MACH_INT_MASK | MACH_SR_INT_ENA_CUR)

#define	PSL_USERSET (	\
	MACH_SR_KU_OLD |	\
	MACH_SR_INT_ENA_OLD |	\
	MACH_SR_KU_PREV |	\
	MACH_SR_INT_ENA_PREV |	\
	MACH_INT_MASK)

#define	PSL_USERCLR (	\
	MACH_SR_COP_USABILITY |	\
	MACH_SR_BOOT_EXC_VEC |	\
	MACH_SR_TLB_SHUTDOWN |	\
	MACH_SR_PARITY_ERR |	\
	MACH_SR_CACHE_MISS |	\
	MACH_SR_PARITY_ZERO |	\
	MACH_SR_SWAP_CACHES |	\
	MACH_SR_ISOL_CACHES |	\
	MACH_SR_KU_CUR |	\
	MACH_SR_INT_ENA_CUR |	\
	MACH_SR_MBZ)

/*
 * Macros to decode processor status word.
 */
#define	USERMODE(ps)	((ps) & MACH_SR_KU_PREV)
#define	BASEPRI(ps)	(((ps) & (MACH_INT_MASK | MACH_SR_INT_ENA_PREV)) \
			== (MACH_INT_MASK | MACH_SR_INT_ENA_PREV))
E 1
