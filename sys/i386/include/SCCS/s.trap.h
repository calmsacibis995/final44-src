h55918
s 00002/00002/00068
d D 8.1 93/06/11 15:48:44 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00067
d D 5.4 91/05/09 18:08:24 william 5 4
c last minute changes, updating present version
e
s 00001/00001/00066
d D 5.3 91/01/18 14:32:18 william 4 3
c fixed just which copyright notice is included.
e
s 00019/00011/00048
d D 5.2 90/11/14 17:57:57 bill 3 2
c added fault types
e
s 00017/00006/00042
d D 5.1 90/04/24 18:52:45 william 2 1
c 1st Berkeley Release
e
s 00048/00000/00000
d D 1.1 90/03/12 15:48:27 bill 1 0
c date and time created 90/03/12 15:48:27 by bill
e
u
U
t
T
I 1
D 2
/*	trap.h	1.3	87/07/11	*/
E 2
I 2
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 4
 * %sccs.include.noredist.c%
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */
E 2

/*
 * Trap type values
 * also known in trap.c for name strings
 */

#define	T_RESADFLT	0	/* reserved addressing */
#define	T_PRIVINFLT	1	/* privileged instruction */
#define	T_RESOPFLT	2	/* reserved operand */
#define	T_BPTFLT	3	/* breakpoint instruction */
#define	T_SYSCALL	5	/* system call (kcall) */
#define	T_ARITHTRAP	6	/* arithmetic trap */
#define	T_ASTFLT	7	/* system forced exception */
#define	T_SEGFLT	8	/* segmentation (limit) fault */
#define	T_PROTFLT	9	/* protection fault */
#define	T_TRCTRAP	10	/* trace trap */
#define	T_PAGEFLT	12	/* page fault */
#define	T_TABLEFLT	13	/* page table fault */
#define	T_ALIGNFLT	14	/* alignment fault */
#define	T_KSPNOTVAL	15	/* kernel stack pointer not valid */
#define	T_BUSERR	16	/* bus error */
#define	T_KDBTRAP	17	/* kernel debugger trap */
I 2

E 2
#define	T_DIVIDE	18	/* integer divide fault */
D 2
#define	T_DEBUG	19	/* debug fault/trap catchall */
#define	T_NMI	20	/* non-maskable trap */
#define	T_OFLOW	21	/* overflow trap */
#define	T_BOUND	22	/* bound instruction fault */
#define	T_DNA	23	/* device not available fault */
E 2
I 2
D 3
#define	T_DEBUG		19	/* debug fault/trap catchall */
#define	T_NMI		20	/* non-maskable trap */
#define	T_OFLOW		21	/* overflow trap */
#define	T_BOUND		22	/* bound instruction fault */
#define	T_DNA		23	/* device not available fault */
E 2
#define	T_DOUBLEFLT	24	/* double fault */
#define	T_FPOPFLT	25	/* fp coprocessor operand fetch fault */
#define	T_TSSFLT	26	/* invalid tss fault */
#define	T_SEGNPFLT	27	/* segment not present fault */
#define	T_STKFLT	28	/* stack fault */
#define	T_RESERVED	29	/* stack fault */
E 3
I 3
#define	T_NMI		19	/* non-maskable trap */
#define	T_OFLOW		20	/* overflow trap */
#define	T_BOUND		21	/* bound instruction fault */
#define	T_DNA		22	/* device not available fault */
#define	T_DOUBLEFLT	23	/* double fault */
#define	T_FPOPFLT	24	/* fp coprocessor operand fetch fault */
#define	T_TSSFLT	25	/* invalid tss fault */
#define	T_SEGNPFLT	26	/* segment not present fault */
#define	T_STKFLT	27	/* stack fault */
#define	T_RESERVED	28	/* reserved fault base */
E 3

/* definitions for <sys/signal.h> */
#define	    ILL_RESAD_FAULT	T_RESADFLT
#define	    ILL_PRIVIN_FAULT	T_PRIVINFLT
#define	    ILL_RESOP_FAULT	T_RESOPFLT
#define	    ILL_ALIGN_FAULT	T_ALIGNFLT
I 3
#define	    ILL_FPOP_FAULT	T_FPOPFLT	/* coprocessor operand fault */
E 3

/* codes for SIGFPE/ARITHTRAP */
#define	    FPE_INTOVF_TRAP	0x1	/* integer overflow */
#define	    FPE_INTDIV_TRAP	0x2	/* integer divide by zero */
#define	    FPE_FLTDIV_TRAP	0x3	/* floating/decimal divide by zero */
#define	    FPE_FLTOVF_TRAP	0x4	/* floating overflow */
#define	    FPE_FLTUND_TRAP	0x5	/* floating underflow */
I 3
#define	    FPE_FPU_NP_TRAP	0x6	/* floating point unit not present */
#define	    FPE_SUBRNG_TRAP	0x7	/* subrange out of bounds */

/* codes for SIGBUS */
#define	    BUS_PAGE_FAULT	T_PAGEFLT	/* page fault protection base */
#define	    BUS_SEGNP_FAULT	T_SEGNPFLT	/* segment not present */
#define	    BUS_STK_FAULT	T_STKFLT	/* stack segment */
#define	    BUS_SEGM_FAULT	T_RESERVED	/* segment protection base */
I 5

/* Trap's coming from user mode */
#define	T_USER	0x100
E 5
E 3
E 1
