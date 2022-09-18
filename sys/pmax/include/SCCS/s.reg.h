h58654
s 00007/00000/00113
d D 8.3 94/07/03 15:00:25 mckusick 4 3
c changes for procfs (from ralph)
e
s 00009/00000/00104
d D 8.2 94/01/11 16:07:58 mckusick 3 2
c added struct reg for procfs (from ralph)
e
s 00002/00002/00102
d D 8.1 93/06/10 23:02:51 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00104/00000/00000
d D 7.1 92/01/07 20:35:52 mckusick 1 0
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
 * from: Utah $Hdr: reg.h 1.1 90/07/09$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Location of the users' stored
 * registers relative to ZERO.
 * Usage is p->p_regs[XX].
 */
#define ZERO	0
#define AST	1
#define V0	2
#define V1	3
#define A0	4
#define A1	5
#define A2	6
#define A3	7
#define T0	8
#define T1	9
#define T2	10
#define T3	11
#define T4	12
#define T5	13
#define T6	14
#define T7	15
#define S0	16
#define S1	17
#define S2	18
#define S3	19
#define S4	20
#define S5	21
#define S6	22
#define S7	23
#define T8	24
#define T9	25
#define K0	26
#define K1	27
#define GP	28
#define SP	29
#define S8	30
#define RA	31
#define MULLO	32
#define MULHI	33
#define	PC	34
#define	SR	35
#define	PS	35	/* alias for SR */
#define	F0	36
#define	F1	37
#define	F2	38
#define	F3	39
#define	F4	40
#define	F5	41
#define	F6	42
#define	F7	43
#define	F8	44
#define	F9	45
#define	F10	46
#define	F11	47
#define	F12	48
#define	F13	49
#define	F14	50
#define	F15	51
#define	F16	52
#define	F17	53
#define	F18	54
#define	F19	55
#define	F20	56
#define	F21	57
#define	F22	58
#define	F23	59
#define	F24	60
#define	F25	61
#define	F26	62
#define	F27	63
#define	F28	64
#define	F29	65
#define	F30	66
#define	F31	67
#define	FSR	68

#ifdef IPCREG
#define	NIPCREG 69
int ipcreg[NIPCREG] = {
	ZERO, AST, V0, V1, A0, A1, A2, A3, T0, T1, T2, T3, T4, T5, T6, T7,
	S0, S1, S2, S3, S4, S5, S6, S7, T8, T9, K0, K1, GP, SP, S8, RA,
	MULLO, MULHI, PC,
	F0, F1, F2, F3, F4, F5, F6, F7,
	F8, F9, F10, F11, F12, F13, F14, F15,
	F16, F17, F18, F19, F20, F21, F22, F23,
	F24, F25, F26, F27, F28, F29, F30, F31, FSR,
};
#endif
I 3

#ifdef LANGUAGE_C
/*
 * Register set accessible via /proc/$pid/reg
 */
struct reg {
        int     r_regs[69];	/* numbered as above */
};
I 4

/*
 * Register set accessible via /proc/$pid/fpreg
 */
struct fpreg {
	int	r_fpregs[33];	/* not implemented */
};
E 4
#endif /* LANGUAGE_C */
E 3
E 1
