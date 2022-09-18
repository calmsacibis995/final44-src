h52880
s 00002/00002/00034
d D 8.1 93/06/10 23:03:05 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00000/00000
d D 7.1 92/01/07 20:35:53 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: trap.h 1.1 90/07/09$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Trap codes
 * also known in trap.c for name strings
 */

#define T_INT			0	/* Interrupt pending */
#define T_TLB_MOD		1	/* TLB modified fault */
#define T_TLB_LD_MISS		2	/* TLB miss on load or ifetch */
#define T_TLB_ST_MISS		3	/* TLB miss on a store */
#define T_ADDR_ERR_LD		4	/* Address error on a load or ifetch */
#define T_ADDR_ERR_ST		5	/* Address error on a store */
#define T_BUS_ERR_IFETCH	6	/* Bus error on an ifetch */
#define T_BUS_ERR_LD_ST		7	/* Bus error on a load or store */
#define T_SYSCALL		8	/* System call */
#define T_BREAK			9	/* Breakpoint */
#define T_RES_INST		10	/* Reserved instruction exception */
#define T_COP_UNUSABLE		11	/* Coprocessor unusable */
#define T_OVFLOW		12	/* Arithmetic overflow */

#define	T_USER			0x10	/* user-mode flag or'ed with type */
E 1
