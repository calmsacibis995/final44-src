h42959
s 00002/00002/00024
d D 8.1 93/06/04 12:47:55 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00018
d D 5.3 93/02/04 18:49:46 ralph 3 2
c changes to match other machines using gcc.
e
s 00001/00001/00023
d D 5.2 92/07/26 21:43:06 ralph 2 1
c removed DEFS.h
e
s 00024/00000/00000
d D 5.1 92/02/29 12:27:10 bostic 1 0
c date and time created 92/02/29 12:27:10 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/syscall.h>
D 2
#include "DEFS.h"
E 2
I 2
#include <machine/machAsmDefs.h>
E 2

D 3
/* vax/tahoe compat */
#define	ret
#define	r0	v0
#define	r1	v1

#define	SYSCALL(x)	LEAF(x); li v0,SYS_/**/x; syscall; bne a3,zero,err; \
E 3
I 3
#ifdef __STDC__
#define	RSYSCALL(x)	LEAF(x); li v0,SYS_ ## x; syscall; bne a3,zero,err; \
E 3
			j ra; err: j _cerror; END(x);
I 3
#define	PSEUDO(x,y)	LEAF(x); li v0,SYS_ ## y; syscall; bne a3,zero,err; \
			j ra; err: j _cerror; END(x);
#else
#define	RSYSCALL(x)	LEAF(x); li v0,SYS_/**/x; syscall; bne a3,zero,err; \
			j ra; err: j _cerror; END(x);
E 3
#define	PSEUDO(x,y)	LEAF(x); li v0,SYS_/**/y; syscall; bne a3,zero,err; \
			j ra; err: j _cerror; END(x);
I 3
#endif
E 3
E 1
