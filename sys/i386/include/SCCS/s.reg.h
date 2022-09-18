h11485
s 00002/00002/00065
d D 8.1 93/06/11 15:48:32 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00066
d D 5.5 91/01/18 14:32:17 william 7 6
c fixed just which copyright notice is included.
e
s 00001/00000/00066
d D 5.4 91/01/15 15:21:37 william 6 5
c trivia, reno changes, and kernel reorg
e
s 00000/00000/00066
d D 5.3 91/01/15 12:22:03 bill 5 4
c reno changes
e
s 00004/00000/00062
d D 5.2 90/11/25 16:08:09 bill 4 3
c last changes before merger with reno version. cross fingers.
e
s 00000/00000/00062
d D 5.1 90/04/24 19:13:12 william 3 2
c 1st Berkeley Release
e
s 00054/00030/00008
d D 1.2 90/04/24 18:56:43 william 2 1
c 1st Berkeley Release
e
s 00038/00000/00000
d D 1.1 90/03/12 15:48:18 bill 1 0
c date and time created 90/03/12 15:48:18 by bill
e
u
U
t
T
I 1
D 2
/*	reg.h	1.2	87/01/13	*/
/*	reg.h	4.2	81/02/19	*/
E 2
I 2
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 7
 * %sccs.include.noredist.c%
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */

E 2
/*
 * Location of the users' stored
D 2
 * registers relative to PSL of 'trap' and 'syscall'.
 * Usage is u.u_ar0[XX].
E 2
I 2
 * registers within appropriate frame of 'trap' and 'syscall', relative to
 * base of stack frame.
 * Normal usage is u.u_ar0[XX] in kernel.
E 2
 */

D 2
#define	PS	(-1)
#define	PC	(-2)
/*		(-3)	*/
/*		(-4)	*/
#define	RACL	(-5)
#define	RACH	(-6)
/*		(-7)	*/
/*		(-8)	*/
#define	SP	(-9)
#define	R13	(-10)
#define	FP	(-10)
#define	R12	(-13)
#define	R11	(-14)
#define	R10	(-15)
#define	R9	(-16)
#define	R8	(-17)
#define	R7	(-18)
#define	R6	(-19)
#define	R5	(-20)
#define	R4	(-21)
#define	R3	(-22)
#define	R2	(-23)
#define	R1	(-24)
#define	R0	(-25)
E 2
I 2
/* When referenced during a trap/exception, registers are at these offsets */
E 2

I 2
#define	tES	(0)
#define	tDS	(1)
#define	tEDI	(2)
#define	tESI	(3)
#define	tEBP	(4)

#define	tEBX	(6)
#define	tEDX	(7)
#define	tECX	(8)
#define	tEAX	(9)

#define	tEIP	(12)
#define	tCS	(13)
#define	tEFLAGS	(14)
#define	tESP	(15)
#define	tSS	(16)

/* During a system call, registers are at these offsets instead of above. */

#define	sEDI	(0)
#define	sESI	(1)
#define	sEBP	(2)

#define	sEBX	(4)
#define	sEDX	(5)
#define	sECX	(6)
#define	sEAX	(7)
#define	sEFLAGS	(8)
#define	sEIP	(9)
#define	sCS	(10)
#define	sESP	(11)
#define	sSS	(12)

I 6
#define	PC	sEIP
E 6
I 4
#define	SP	sESP
#define	PS	sEFLAGS
#define	R0	sEDX
#define	R1	sECX
E 4
/*
 * Registers accessible to ptrace(2) syscall for debugger
 */
E 2
#ifdef IPCREG
D 2
#define	NIPCREG 18
E 2
I 2
#define	NIPCREG 14
E 2
int ipcreg[NIPCREG] =
D 2
	{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,FP,SP,PC,RACH,RACL};
E 2
I 2
  { tES,tDS,tEDI,tESI,tEBP,tEBX,tEDX,tECX,tEAX,tEIP,tCS,tEFLAGS,tESP,tSS };
E 2
#endif
E 1
