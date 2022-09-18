h48494
s 00025/00000/00000
d D 5.1 90/03/23 09:44:37 bostic 1 0
c date and time created 90/03/23 09:44:37 by bostic
e
u
U
t
T
I 1
/*
 *	Copyright (c) 1982 Regents of the University of California
 */
#ifndef lint
static char sccsid[] = "@(#)aspseudo.c 4.5 6/30/83";
#endif not lint

#include <stdio.h>
#include "as.h"

#define	OP(name, opcode, nargs, arg1, arg2, arg3, arg4, arg5, arg6) \
	{ \
		name, opcode, nargs, arg1, arg2, arg3, arg4, arg5, arg6, \
		(nargs == 0 ? INST0:INSTn) \
	}
#define	PSEUDO(name, type, tag) \
	{ \
		name, type, 0,   0, 0, 0, 0, 0, 0, \
		tag \
	}

readonly struct Instab instab[] = {
#include "instrs.as"
PSEUDO("\0\0\0\0\0\0\0\0\0\0", 0, 0)
};
E 1
