/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	psl.h,v $
 * Revision 1.4  89/03/09  20:03:39  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:33:24  gm0w
 * 	Changes for cleanup.
 * 
 */
 
/*
 *	80386 EFLAGS register definition
 */

#define EFL_CF		0x00000001	/* carry flag */
#define EFL_PF		0x00000004	/* parity flag */
#define EFL_AF		0x00000010	/* auxiliary carry */
#define EFL_ZF		0x00000040	/* zero flag */
#define EFL_SF		0x00000080	/* sign flag */
#define EFL_ALLCC	0x000000c5	/* all cc bits - unlikely */
#define EFL_TF		0x00000100	/* trap flag */
#define EFL_IF		0x00000200	/* interrupt enable flag */
#define EFL_DF		0x00000400	/* direction flag */
#define EFL_OF		0x00000800	/* overflow flag */
#define EFL_IOPL	0x00003000	/* i/o privilege level */
#define EFL_NT		0x00004000	/* nested task flag */
#define EFL_RF		0x00010000	/* resume flag */
#define EFL_VM		0x00020000	/* virtual 8086 mode */

#define EFL_USERSET	0
#define EFL_USERCLR	(EFL_IF | EFL_NT | EFL_IOPL | EFL_RF | EFL_VM)
