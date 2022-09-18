h64040
s 00002/00002/00047
d D 8.1 93/06/11 15:16:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00047
d D 7.3 93/04/20 23:13:38 torek 3 2
c spelling
e
s 00005/00000/00044
d D 7.2 92/07/21 16:54:27 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00044/00000/00000
d D 7.1 92/07/13 00:44:35 torek 1 0
c date and time created 92/07/13 00:44:35 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: intreg.h,v 1.6 92/06/17 05:22:06 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: intreg.h,v 1.7 92/11/26 03:04:53 torek Exp $ (LBL)
E 3
 */

/*
 * sun4c interrupt enable register.
 *
 * The register is a single byte.  C code must use the ienab_bis and
 * ienab_bic functions found in locore.s.
 *
 * The register's physical address is defined here as the register
 * must be mapped early in the boot process (otherwise NMI handling
 * will fail).
 */
#define	INT_ENABLE_REG_PHYSADR	0xf5000000	/* phys addr in IOspace */

/*
 * Bits in interrupt enable register.  Software interrupt requests must
 * be cleared in software.  This is done in locore.s.  The ALLIE bit must
 * be cleared to clear asynchronous memory error (level 15) interrupts.
 */
#define	IE_L14		0x80	/* enable level 14 (counter 1) interrupts */
#define	IE_L10		0x20	/* enable level 10 (counter 0) interrupts */
#define	IE_L8		0x10	/* enable level 8 interrupts */
#define	IE_L6		0x08	/* request software level 6 interrupt */
#define	IE_L4		0x04	/* request software level 4 interrupt */
#define	IE_L1		0x02	/* request software level 1 interrupt */
#define	IE_ALLIE	0x01	/* enable interrupts */

#ifndef LOCORE
void	ienab_bis __P((int bis));	/* set given bits */
void	ienab_bic __P((int bic));	/* clear given bits */
#endif
E 1
