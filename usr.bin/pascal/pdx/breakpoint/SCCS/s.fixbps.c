h30197
s 00002/00002/00077
d D 8.1 93/06/06 15:32:41 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00072
d D 5.2 91/04/16 15:39:11 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00003/00069
d D 5.1 85/06/05 16:57:32 dist 2 1
c Add copyright
e
s 00072/00000/00000
d D 1.1 82/01/18 19:19:56 linton 1 0
c date and time created 82/01/18 19:19:56 by linton
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
 * fix up breakpoint information before continuing execution
 *
 * It's necessary to destroy breakpoints that were created temporarily
 * and still exist because the program terminated abnormally.
 */

#include "defs.h"
#include "breakpoint.h"
#include "bp.rep"

fixbps()
{
	register BPINFO *p, *last, *next;

	last = NIL;
	p = bphead;
	while (p != NIL) {
		next = p->bpnext;
		switch(p->bptype) {
			case ALL_OFF:
				if (p->bpline >= 0) {
					--tracing;
				} else {
					--inst_tracing;
				}
				if (p->bpcond != NIL) {
					delcond(TRPRINT, p->bpcond);
				}
				goto delete;

			case STOP_OFF:
				var_tracing--;
				delcond(TRSTOP, p->bpcond);
				goto delete;

			case TERM_OFF:
				--var_tracing;
				delvar(TRPRINT, p->bpnode, p->bpcond);
				goto delete;

			case CALL:
			case RETURN:
			case BLOCK_OFF:
			case CALLPROC:
			case END_BP:

			delete:
				if (last == NIL) {
					bphead = next;
				} else {
					last->bpnext = next;
				}
				dispose(p);
				break;

			default:
				last = p;
				break;
		}
		p = next;
	}
	tracing = 0;
	var_tracing = 0;
	inst_tracing = 0;
	trfree();
	condfree();
}
E 1
