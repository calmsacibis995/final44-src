h00275
s 00002/00002/00163
d D 8.1 93/06/06 15:32:49 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00158
d D 5.2 91/04/16 15:39:13 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00003/00155
d D 5.1 85/06/05 16:59:08 dist 2 1
c Add copyright
e
s 00158/00000/00000
d D 1.1 82/01/18 19:20:00 linton 1 0
c date and time created 82/01/18 19:20:00 by linton
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
 * Print out what's currently being traced by looking at
 * the currently active breakpoints.
 *
 * The list is in LIFO order, we print it FIFO by going recursive.
 */

#include "defs.h"
#include "breakpoint.h"
#include "tree.h"
#include "sym.h"
#include "source.h"
#include "object.h"
#include "mappings.h"
#include "bp.rep"

#define printnum(id)	if (!isredirected()) printf("(%d) ", id)

status()
{
	if (bphead == NIL) {
		if (!isredirected()) {
			printf("no trace's or stop's active\n");
		}
	} else {
		bpstatus(bphead);
	}
}

LOCAL bpstatus(bp)
BPINFO *bp;
{
	register BPINFO *p;
	LINENO n;
	SYM *s;
	NODE *t;
	char *trname, *stname;

	p = bp;
	if (p->bpnext != NIL) {
		bpstatus(p->bpnext);
	}
	t = p->bpnode;
	if (p->bpline >= 0) {
		n = linelookup(p->bpaddr);
		trname = "trace";
		stname = "stop";
	} else {
		n = p->bpaddr;
		trname = "tracei";
		stname = "stopi";
	}
	switch(p->bptype) {
		case INST:
			printnum(p->bpid);
			printf("%s %d", trname, n);
			break;

		case ALL_ON:
			printnum(p->bpid);
			printf("%s", trname);
			s = p->bpblock;
			if (s != program) {
				printf(" in ");
				printname(s);
			}
			break;

		case STOP_ON:
			printnum(p->bpid);
			printf("%s", stname);
			if (t != NIL) {
				printf(" ");
				prtree(t);
			}
			s = p->bpblock;
			if (s != program) {
				printf(" in ");
				printname(s);
			}
			break;

		case BLOCK_ON:
		case TERM_ON:
			s = p->bpblock;
			printnum(p->bpid);
			printf("%s ", trname);
			prtree(t);
			if (s != program) {
				printf(" in ");
				printname(s);
			}
			break;

		case AT_BP:
			printnum(p->bpid);
			printf("%s ", trname);
			prtree(t);
			printf(" at %d", p->bpline);
			break;

		case STOP_BP:
			printnum(p->bpid);
			printf("%s", stname);
			if (t != NIL) {
				printf(" ");
				prtree(t);
			} else if ((s = p->bpblock) != NIL) {
				printf(" in ");
				printname(s);
			} else if (p->bpline > 0) {
				printf(" at %d", p->bpline);
			} else {
				printf(" at %d", p->bpaddr);
			}
			break;

		/*
		 * Temporary breakpoints;
		 * return rather than break to avoid printing newline.
		 */
		case ALL_OFF:
		case CALL:
		case RETURN:
		case CALLPROC:
		case STOP_OFF:
		case BLOCK_OFF:
		case TERM_OFF:
		case END_BP:
			return;

		default:
			panic("bptype %d in bplist", p->bptype);
	}
	if (p->bpcond != NIL) {
		printf(" if ");
		prtree(p->bpcond);
	}
	printf("\n");
}

/*
 * Print the name of a symbol unambigously.
 */

LOCAL printname(s)
SYM *s;
{
	if (isambiguous(s)) {
		printwhich(s);
	} else {
		printf("%s", name(s));
	}
}
E 1
