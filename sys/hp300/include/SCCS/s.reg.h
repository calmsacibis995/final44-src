h38384
s 00007/00000/00067
d D 8.3 94/01/27 11:33:10 pendry 7 6
c add struct fpreg
e
s 00010/00000/00057
d D 8.2 94/01/03 10:55:44 pendry 6 4
c add struct reg for procfs
e
s 00008/00000/00057
d R 8.2 94/01/03 10:39:11 pendry 5 4
c add struct reg for procfs
e
s 00002/00002/00055
d D 8.1 93/06/10 21:45:12 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00055
d D 7.3 92/12/27 09:29:14 hibler 3 2
c PC no longer included due to new stack alignment
e
s 00001/00001/00056
d D 7.2 90/11/03 12:53:55 mckusick 2 1
c update identifier from Utah
e
s 00057/00000/00000
d D 7.1 90/05/08 17:51:21 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 4
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: reg.h 1.5 89/04/11$
E 2
I 2
 * from: Utah $Hdr: reg.h 1.1 90/07/09$
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Location of the users' stored
 * registers relative to D0.
 * Usage is u.u_ar0[XX].
 */
#define	D0	(0)
#define	D1	(1)
#define	D2	(2)
#define	D3	(3)
#define	D4	(4)
#define	D5	(5)
#define	D6	(6)
#define	D7	(7)
#define	A0	(8)
#define	A1	(9)
#define	A2	(10)
#define	A3	(11)
#define	A4	(12)
#define	A5	(13)
#define	A6	(14)
#define	A7	(15)

#define	SP	A7
#define	PC	(17)
#define	PS	(16)

#ifdef IPCREG
D 3
#define	NIPCREG 17
E 3
I 3
#define	NIPCREG 16
E 3
int ipcreg[NIPCREG] =
D 3
	{D0,D1,D2,D3,D4,D5,D6,D7,A0,A1,A2,A3,A4,A5,A6,A7,PC};
E 3
I 3
	{D0,D1,D2,D3,D4,D5,D6,D7,A0,A1,A2,A3,A4,A5,A6,A7};
E 3
#endif

I 6
/*
 * Register set accessible via /proc/$pid/reg
 */
struct reg {
        int     r_regs[16];	/* numbered as above */
	int	r_pc;
	int	r_sr;
};

I 7
/*
 * Register set accessible via /proc/$pid/fpreg
 */
struct fpreg {
	int	fpr_xxx;	/* not implemented */
};

E 7

E 6
#ifdef KERNEL
/*
 * Due to a mental lapse somewhere down the line, wait returns its values
 * in strange registers.  Kludge it up here so we don't have to in the
 * machine-independent code.
 */
#define	R0	D1
#define	R1	A0
#endif
E 1
