h32002
s 00002/00002/00065
d D 8.1 93/06/06 15:49:58 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00061
d D 5.3 91/04/16 14:52:29 bostic 4 3
c new copyright; att/bsd/shared
e
s 00009/00000/00057
d D 5.2 87/04/07 15:57:53 mckusick 3 2
c port to tahoe by Nir peleg of CCI
e
s 00008/00002/00049
d D 5.1 85/06/06 15:55:00 dist 2 1
c Add copyright
e
s 00051/00000/00000
d D 1.1 82/01/18 19:21:27 linton 1 0
c date and time created 82/01/18 19:21:27 by linton
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
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
E 4
 */
E 2

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 2

/*
 * assign the value of an expression to a variable (or term)
 */

#include "defs.h"
#include "tree.h"
#include "sym.h"
#include "process.h"
#include "tree.rep"
I 3
#include "process/process.rep"
#include "process/pxinfo.h"
E 3

assign(var, exp)
NODE *var;
NODE *exp;
{
	ADDRESS addr;
	int varsize;
	char cvalue;
	short svalue;
	long lvalue;

	if (!compatible(var->nodetype, exp->nodetype)) {
		error("incompatible types");
	}
	addr = lval(var);
	eval(exp);
	varsize = size(var->nodetype);
	if (varsize < sizeof(long)) {
		lvalue = pop(long);
		switch (varsize) {
			case sizeof(char):
				cvalue = lvalue;
				dwrite(&cvalue, addr, varsize);
				break;

			case sizeof(short):
				svalue = lvalue;
				dwrite(&svalue, addr, varsize);
				break;

			default:
I 3
				goto othersize;
				/*
E 3
				panic("bad size %d", varsize);
I 3
				*/
E 3
		}
	} else {
I 3
	    othersize:
E 3
		sp -= varsize;
		dwrite(sp, addr, varsize);
I 3
#ifdef tahoe
		downalignstack();
#endif
E 3
	}
}
E 1
