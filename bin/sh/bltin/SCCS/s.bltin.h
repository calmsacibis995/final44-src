h50764
s 00000/00000/00048
d D 8.2 95/05/04 18:03:55 christos 3 2
c misc cleanup
e
s 00002/00002/00046
d D 8.1 93/05/31 15:15:31 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00048/00000/00000
d D 5.1 91/03/07 20:22:37 bostic 1 0
c date and time created 91/03/07 20:22:37 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * This file is included by programs which are optionally built into the
 * shell.  If SHELL is defined, we try to map the standard UNIX library
 * routines to ash routines using defines.
 */

#include "../shell.h"
#include "../mystring.h"
#ifdef SHELL
#include "../output.h"
#define stdout out1
#define stderr out2
#define printf out1fmt
#define putc(c, file)	outc(c, file)
#define putchar(c)	out1c(c)
#define fprintf outfmt
#define fputs outstr
#define fflush flushout
#define INITARGS(argv)
#else
#undef NULL
#include <stdio.h>
#undef main
#define INITARGS(argv)	if ((commandname = argv[0]) == NULL) {fputs("Argc is zero\n", stderr); exit(2);} else
#endif

#ifdef __STDC__
pointer stalloc(int);
void error(char *, ...);
#else
pointer stalloc();
void error();
#endif


extern char *commandname;
E 1
