h47516
s 00011/00001/00145
d D 7.1 90/12/06 13:50:24 bostic 5 4
c add Berkeley specific copyright notice
e
s 00012/00012/00134
d D 1.4 90/12/04 22:51:41 bostic 4 3
c redo include files for kernel reorg
e
s 00008/00008/00138
d D 1.3 90/06/21 20:03:44 mckusick 3 2
c return error explicitly rather than through u.u_error
e
s 00000/00001/00146
d D 1.2 89/05/05 00:31:02 mckusick 2 1
c get rid of unneeded include
e
s 00147/00000/00000
d D 1.1 86/01/03 23:49:22 sam 1 0
c date and time created 86/01/03 23:49:22 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*-
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 5

D 4
#include "../tahoe/psl.h"
#include "../tahoe/reg.h"
#include "../tahoe/pte.h"
#include "../tahoe/mtpr.h"
#include "../tahoemath/Kfp.h"
E 4
I 4
#include "../include/psl.h"
#include "../include/reg.h"
#include "../include/pte.h"
#include "../include/mtpr.h"
#include "../math/Kfp.h"
E 4

D 4
#include "param.h"
#include "systm.h"
D 2
#include "dir.h"
E 2
#include "user.h"
#include "proc.h"
#include "seg.h"
#include "acct.h"
#include "kernel.h"
E 4
I 4
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/seg.h"
#include "sys/acct.h"
#include "sys/kernel.h"
E 4

/*
 * Floating point emulation support.
 */
extern	float Kcvtlf(), Kaddf(), Ksubf(), Kmulf(), Kdivf();
extern	double Kcvtld(), Kaddd(), Ksubd(), Kmuld(), Kdivd();
extern	float Ksinf(), Kcosf(), Katanf(), Klogf(), Ksqrtf(), Kexpf();

#define	OP(dop)		((dop) &~ 01)	/* precision-less version of opcode */
#define	isdouble(op)	((op) & 01)	/* is opcode double or float */

struct	fpetab {
	int	fpe_op;		/* base opcode emulating */
	float	(*fpe_ffunc)();	/* float version of op */
	double	(*fpe_dfunc)();	/* double version of op */
} fpetab[] = {
	{ OP(CVLD),	Kcvtlf,	Kcvtld },
	{ OP(ADDD),	Kaddf,	Kaddd },
	{ OP(SUBD),	Ksubf,	Ksubd },
	{ OP(MULD),	Kmulf,	Kmuld },
	{ OP(DIVD),	Kdivf,	Kdivd },
	{ SINF,		Ksinf,	0 },
	{ COSF,		Kcosf,	0 },
	{ ATANF,	Katanf,	0 },
	{ LOGF,		Klogf,	0 },
	{ SQRTF,	Ksqrtf,	0 },
	{ EXPF,		Kexpf,	0 },
};
#define	NFPETAB	(sizeof (fpetab) / sizeof (fpetab[0]))

/*
 * Emulate the FP opcode. Update psl as necessary.
 * If OK, set opcode to 0, else to the FP exception #.
 * Not all parameter longwords are relevant, depends on opcode.
 *
 * The entry mask is set by locore.s so ALL registers are saved.
 * This enables FP opcodes to change user registers on return.
 */
/* WARNING!!!! THIS CODE MUST NOT PRODUCE ANY FLOATING POINT EXCEPTIONS */
/*ARGSUSED*/
fpemulate(hfsreg, acc_most, acc_least, dbl, op_most, op_least, opcode, pc, psl)
{
	int r0, r1;			/* must reserve space */
	register int *locr0 = ((int *)&psl)-PS;
	register struct fpetab *fp;
	int hfs = 0; 			/* returned data about exceptions */
	int type;			/* opcode type, FLOAT or DOUBLE */
	union { float ff; int fi; } f_res;
	union { double dd; int di[2]; } d_res;
I 3
	int error = 0;
E 3

#ifdef lint
	r0 = 0; r0 = r0; r1 = 0; r1 = r1;
#endif
	type = isdouble(opcode) ? DOUBLE : FLOAT;
	for (fp = fpetab; fp < &fpetab[NFPETAB]; fp++)
		if ((opcode & 0xfe) == fp->fpe_op)
			break;
	if (type == DOUBLE) {
		if (fp->fpe_dfunc == 0)
			fp = &fpetab[NFPETAB];
		else
			locr0[PS] &= ~PSL_DBL;
	}
	if (fp >= &fpetab[NFPETAB]) {
		opcode = DIV0_EXC;	/* generate SIGILL - XXX */
D 3
		return;
E 3
I 3
		return (0);
E 3
	}
	switch (type) {

	case DOUBLE:
		d_res.dd = (*fp->fpe_dfunc)(acc_most, acc_least, op_most,
		    op_least, &hfs);
		if (d_res.di[0] == 0 && d_res.di[1] == 0)
			locr0[PS] |= PSL_Z;
		if (d_res.di[0] < 0)
			locr0[PS] |= PSL_N;
		break;

	case FLOAT:
		f_res.ff = (*fp->fpe_ffunc)(acc_most, acc_least, op_most,
		    op_least, &hfs);
		if (f_res.fi == 0)
			locr0[PS] |= PSL_Z;
		if (f_res.fi ==  0)
			locr0[PS] |= PSL_N;
		break;
	}
	if (hfs & HFS_OVF) {
		locr0[PS] |= PSL_V;	/* turn on overflow bit */
#ifdef notdef
		if (locr0[PS] & PSL_IV)   {  /* overflow enabled? */
#endif
			opcode = OVF_EXC;
D 3
			u.u_error = (hfs & HFS_DOM) ? EDOM : ERANGE;
			return;
E 3
I 3
			return ((hfs & HFS_DOM) ? EDOM : ERANGE);
E 3
#ifdef notdef
		}
#endif
	} else if (hfs & HFS_UNDF) {
		if (locr0[PS] &  PSL_FU) {  /* underflow enabled? */
			opcode = UNDF_EXC;
D 3
			u.u_error = (hfs & HFS_DOM) ? EDOM : ERANGE;
			return;
E 3
I 3
			return ((hfs & HFS_DOM) ? EDOM : ERANGE);
E 3
		} 
	} else if (hfs & HFS_DIVZ) {
		opcode = DIV0_EXC;
D 3
		return;
E 3
I 3
		return (0);
E 3
	} else if (hfs & HFS_DOM)
D 3
		u.u_error = EDOM;
E 3
I 3
		error = EDOM;
E 3
	else if (hfs & HFS_RANGE)
D 3
		u.u_error = ERANGE;
E 3
I 3
		error = ERANGE;
E 3
	switch (type) {

	case DOUBLE:
		if (hfs & (HFS_OVF|HFS_UNDF)) {
			d_res.dd = 0.0;
			locr0[PS] |= PSL_Z;
		}
		mvtodacc(d_res.di[0], d_res.di[1], &acc_most);
		break;

	case FLOAT:
		if (hfs & (HFS_OVF|HFS_UNDF)) {
			f_res.ff = 0.0;
			locr0[PS] |= PSL_Z;
		}
		mvtofacc(f_res.ff, &acc_most);
		break;
	}
	opcode = 0;
I 3
	return (error);
E 3
}
E 1
