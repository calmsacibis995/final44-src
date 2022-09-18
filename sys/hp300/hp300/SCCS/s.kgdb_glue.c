h42185
s 00003/00003/00123
d D 8.2 94/01/12 09:42:15 bostic 7 6
c lint
e
s 00002/00002/00124
d D 8.1 93/06/10 21:40:54 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00014/00118
d D 7.4 92/12/27 09:46:19 hibler 5 4
c account for new stack alignment
e
s 00009/00000/00123
d D 7.3 92/12/16 17:31:18 mckusick 4 3
c proper acknowledgement
e
s 00004/00003/00119
d D 7.2 92/10/11 09:42:35 bostic 3 2
c make kernel includes standard
e
s 00002/00014/00120
d D 7.1 91/04/20 17:36:27 karels 2 1
c mv kgdb_panic to kgdb_stub.c
e
s 00134/00000/00000
d D 1.1 91/03/12 15:05:09 karels 1 0
c new file in update from van
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
I 4
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
E 4
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * This file must be compiled with gcc -fno-defer-pop.
 */

#ifdef KGDB

D 3
#include "param.h"
D 2
#include "frame.h"
#include "machine/reg.h"
E 2
I 2
#include "../include/frame.h"
#include "../include/reg.h"
E 3
I 3
#include <sys/param.h>

#include <machine/frame.h>
#include <machine/reg.h>
E 3
E 2

#ifndef lint
static char rcsid[] =
D 5
    "@(#) $Header: kgdb_glue.c,v 1.4 91/03/08 07:02:37 van Exp $ (LBL)";
E 5
I 5
    "@(#) $Header: /usr/src/sys/hp300/hp300/RCS/kgdb_glue.c,v 1.5 92/12/20 15:48:57 mike Exp $ (LBL)";
E 5
#endif

D 5
/*
 * # of additional bytes in 680x0 exception frame format n.
 */
static int frame_bytes[16] = {
	0, 0, sizeof(struct fmt2), 0,
	0, 0, 0, 0,
	0, sizeof(struct fmt9), sizeof(struct fmtA), sizeof(struct fmtB),
	0, 0, 0, 0
};

E 5
#define KGDB_STACKSIZE 0x800
#define KGDB_STACKWORDS (KGDB_STACKSIZE / sizeof(u_long))

u_long kgdb_stack[KGDB_STACKWORDS];

#define getsp(v) asm("movl sp, %0" : "=r" (v))
#define setsp(v) asm("movl %0, sp" :: "r" (v))

static inline void
copywords(src, dst, nbytes)
	register u_long *src, *dst;
	register u_int nbytes;
{
	u_long *limit = src + (nbytes / sizeof(u_long));

	do {
		*dst++ = *src++;
	} while (src < limit);
	if (nbytes & 2)
		*(u_short *)dst = *(u_short *)src;
D 2
}

/*
 * Decide what to do on panic.
 * For now, wait for debugger if kgdb_debug_init is set.
 */
kgdb_panic()
{
	extern int kgdb_debug_init;

	if (kgdb_debug_init)		/* XXX, need boot flag/sysctl */
		asm("trap #15");
E 2
}

kgdb_trap_glue(type, frame)
	int type;
	struct frame frame;
{
	u_long osp, nsp;
	u_int fsize, s;
I 5
	extern short exframesize[];
E 5

	/*
	 * After a kernel mode trap, the saved sp doesn't point to the right
D 5
	 * place.  The correct value is the top of the frame.
E 5
I 5
	 * place.  The correct value is the top of the frame (i.e. before the
	 * KGDB trap).
	 *
	 * XXX this may have to change if we implement an interrupt stack.
E 5
	 */
D 5
	fsize = sizeof(frame) - sizeof(frame.F_u) + frame_bytes[frame.f_format];
E 5
I 5
	fsize = sizeof(frame) - sizeof(frame.F_u) + exframesize[frame.f_format];
E 5
	frame.f_regs[SP] = (u_long)&frame + fsize;

	/*
	 * Copy the interrupt context and frame to the new stack.
	 * We're throwing away trap()'s frame since we're going to do
	 * our own rte.
	 */
	nsp = (u_long)&kgdb_stack[KGDB_STACKWORDS] -
	      roundup(fsize, sizeof(u_long));

	copywords((u_long *)&frame, (u_long *)nsp, fsize);

	s = splhigh();

	getsp(osp);
	setsp(nsp);

	if (kgdb_trap(type, (struct frame *)nsp) == 0) {
		/*
		 * Get back on kernel stack.  This thread of control
		 * will return back up through trap().  If kgdb_trap()
		 * returns 0, it didn't handle the trap at all so
		 * the stack is still intact and everything will
		 * unwind okay from here up.
		 */
		setsp(osp);
		splx(s);
		return 0;
	}
	/*
	 * Copy back context, which has possibly changed.  Even the
	 * sp might have changed.
	 */
	osp = ((struct frame *)nsp)->f_regs[SP] - fsize;
	copywords((u_long *)nsp, (u_long *)osp, fsize);
	setsp(osp);

	/*
	 * Restore the possible new context from frame, pop the
	 * unneeded usp (we trapped from kernel mode) and pad word,
	 * and return to the trapped thread.
	 */
D 5
	asm("moveml sp@+,#0x7FFF; addql #6,sp; rte");
E 5
I 5
	asm("moveml sp@+,#0x7FFF; addql #8,sp; rte");
E 5
}

int kgdb_testval;

kgdb_test(i)
I 7
	int i;
E 7
{
        ++kgdb_testval;
D 7
        return i + 1;
E 7
I 7
        return (i + 1);
E 7
}
D 7

#endif
E 7
I 7
#endif /* KGDB */
E 7
E 1
