h31081
s 00002/00002/00102
d D 8.1 93/06/06 15:44:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00097
d D 5.2 91/04/16 15:15:31 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00003/00094
d D 5.1 85/06/06 11:47:59 dist 2 1
c Add copyright
e
s 00097/00000/00000
d D 1.1 82/01/18 19:21:03 linton 1 0
c date and time created 82/01/18 19:21:03 by linton
e
u
U
t
T
I 1
D 2
/* Copyright (c) 1982 Regents of the University of California */
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
E 3
 */
E 2

D 2
static char sccsid[] = "%Z%%M% %I% %G%";

E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */

E 3
E 2
/*
 * routines to deal with the entry addresses of blocks
 */

#include "defs.h"
#include "runtime.h"
#include "frame.rep"
#include "machine.h"
#include "process.h"
#include "sym.h"
#include "source.h"
#include "object.h"
#include "process/pxinfo.h"
#include "process/process.rep"

/*
 * Return the address of the beginning of the procedure/function
 * associated with the given frame.
 */

ADDRESS entry(frp)
register FRAME *frp;
{
	return(frp->blockp - 2 - ENDOFF);
}

/*
 * Find the entry address of the caller of the current block.
 * This is only called in connection with breakpoints.
 *
 * This routine assumes it is at the very beginning of the block.
 */

ADDRESS caller_addr()
{
	FRAME *frp;

	if ((frp = curframe()) == NIL) {
		panic("caller_addr(main program)");
	}
	frp = nextframe(frp);
	if (frp == NIL) {
		return(codeloc(program));
	} else {
		return(entry(frp));
	}
}

/*
 * Find the return address of the current procedure/function.
 *
 * There are two special cases:
 *
 *	we're right at the beginning of the main program
 *	we're right at the beginning of some procedure or function
 *
 * The first one is handled by returning the last instruction in
 * the object code.  In the second case, we get the return address
 * directly from the process' stack.
 */

ADDRESS return_addr()
{
	ADDRESS addr;
	FRAME *frp, frame;

	if (pc == codeloc(program)) {
		addr = lastaddr();
	} else {
		frp = curframe();
		if (frp == NIL) {
			dread(&frame, (ADDRESS) process->sp, sizeof(FRAME));
			addr = frame.save_pc - ENDOFF;
		} else {
			addr = frp->save_pc;
		}
	}
	return addr;
}

/*
 * Calculate the entry address for a procedure or function parameter,
 * given the address of the descriptor.
 */

ADDRESS fparamaddr(a)
ADDRESS a;
{
	ADDRESS r;

	dread(&r, a, sizeof(r));
	return (r - ENDOFF);
}
E 1
