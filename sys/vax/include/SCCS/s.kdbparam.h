h28531
s 00006/00001/00060
d D 7.4 91/05/08 14:40:51 bostic 5 4
c new copyright; att/bsd/shared
e
s 00006/00008/00055
d D 7.3 90/06/22 15:43:16 sklower 4 2
c check in for beta tape; decoding of instructions broken in vax kdb.
e
s 00007/00007/00056
d R 7.3 90/05/03 17:49:37 sklower 3 2
c 1st level torek changes for now
e
s 00003/00002/00060
d D 7.2 88/05/07 14:00:32 karels 2 1
c changes from torek (should compile, still untested)
e
s 00062/00000/00000
d D 7.1 88/04/23 16:44:08 karels 1 0
c first version (not working)
e
u
U
t
T
I 1
D 5
/*
E 5
I 5
/*-
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 *
E 5
 *	%W% (Berkeley) %G%
 */

D 2
#include <sys/vm.h>

E 2
#define DBNAME "kdb\n"
#define LPRMODE "%R"
#define OFFMODE "+%R"
I 2

#define	KDB_IPL		0xf	/* highest priority software interrupt */
#define	setsoftkdb()	mtpr(SIRR, KDB_IPL)
E 2

#define	MAXINT	0x7fffffff
#define	MAXSTOR (KERNBASE - ctob(UPAGES))

#define	ENTRYMASK	1			/* check for entry masks */
D 4
#define	ishiddenreg(p)	((p) <= &reglist[8])
E 4
I 4
#define	ishiddenreg(p)	((p) <= &kdbreglist[8])
E 4

#define BPT	03
#define TBIT	020

D 4
#define	clrsstep()	(pcb.pcb_psl &= ~TBIT)
#define	setsstep()	(pcb.pcb_psl |= TBIT)
E 4
I 4
#define	clrsstep()	(kdbpcb.pcb_psl &= ~TBIT)
#define	setsstep()	(kdbpcb.pcb_psl |= TBIT)
E 4

#define	SETBP(ins)	(BPT | ((ins) & ~0xff))

D 4
#define	getprevpc(fp)	get((fp)+16, DSP)	/* pc of caller */
#define	getprevframe(fp) (get((fp)+12, DSP)&~2)	/* fp of caller */
#define	getnargs(fp)	(get((fp)+6, DSP)&0xffff)
#define	nextarg(ap)	((ap) + 4)		/* next argument in list */
E 4
I 4
#define	getprevpc(fp)	kdbget((fp)+16, DSP)	/* pc of caller */
#define	getprevframe(fp) (kdbget((fp)+12, DSP)&~2)	/* fp of caller */
E 4
#define	NOFRAME		0			/* fp at top of call stack */

#define	issignalpc(pc)	(MAXSTOR < (pc) && (pc) < MAXSTOR+ctob(UPAGES))
D 4
#define	getsignalpc(fp)	get((fp)+92, DSP)	/* pc of caller before signal */
E 4
I 4
#define	getsignalpc(fp)	kdbget((fp)+92, DSP)	/* pc of caller before signal */
E 4

/* long to ints and back (puns) */
union {
	int	I[2];
	long	L;
} itolws;

#define leng(a)		itol(0,a)
#define shorten(a)	((short)(a))
#define itol(a,b)	(itolws.I[0]=(b), itolws.I[1]=(a), itolws.L)
#define	byte(a)		((a) & 0xff)
#define	btol(a)		((a))

/* check for address wrap around */
#define	addrwrap(oaddr,newaddr) (((oaddr)^(newaddr)) >> 24)
/*
 * INSTACK tells whether its argument is a stack address.
 * INUDOT tells whether its argument is in the (extended) u. area.
 * These are used for consistency checking and dont have to be exact.
 *
 * INKERNEL tells whether its argument is a kernel space address.
 * KVTOPH trims a kernel virtal address back to its offset
 * in the kernel address space.
 */
#define	INSTACK(x)	(((x)&0xf0000000) == 0x70000000)
#define	INUDOT(x)	(((x)&0xf0000000) == 0x70000000)
#define	INKERNEL(x)	(((x)&0xf0000000) == 0x80000000)

#define	KVTOPH(x)	((x)&~ 0x80000000)
#define	KERNOFF		0x80000000
E 1
