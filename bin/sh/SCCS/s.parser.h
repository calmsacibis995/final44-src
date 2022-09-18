h37439
s 00004/00009/00050
d D 8.3 95/05/04 18:00:08 christos 6 5
c 
e
s 00013/00008/00046
d D 8.2 95/04/28 17:16:16 bostic 5 4
c add the documented in the manual but not implemented variable
c expansions.
c From: Christos Zoulas <christos@deshaw.com>
e
s 00002/00002/00052
d D 8.1 93/05/31 15:20:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00051
d D 5.3 92/06/23 18:09:00 marc 3 2
c prompt stuff for editing package
e
s 00003/00000/00048
d D 5.2 92/04/30 15:11:48 marc 2 1
c add arithmetic
e
s 00048/00000/00000
d D 5.1 91/03/07 20:27:56 bostic 1 0
c date and time created 91/03/07 20:27:56 by bostic
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
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* control characters in argument strings */
#define CTLESC '\201'
#define CTLVAR '\202'
#define CTLENDVAR '\203'
#define CTLBACKQ '\204'
#define CTLQUOTE 01		/* ored with CTLBACKQ code if in quotes */
I 2
/*	CTLBACKQ | CTLQUOTE == '\205' */
#define	CTLARI	'\206'
#define	CTLENDARI '\207'
E 2

/* variable substitution byte (follows CTLVAR) */
D 5
#define VSTYPE 07		/* type of variable substitution */
#define VSNUL 040		/* colon--treat the empty string as unset */
#define VSQUOTE 0100		/* inside double quotes--suppress splitting */
E 5
I 5
#define VSTYPE	0x0f		/* type of variable substitution */
#define VSNUL	0x10		/* colon--treat the empty string as unset */
#define VSQUOTE 0x80		/* inside double quotes--suppress splitting */
E 5

/* values of VSTYPE field */
D 5
#define VSNORMAL 1		/* normal variable:  $var or ${var} */
#define VSMINUS 2		/* ${var-text} */
#define VSPLUS 3		/* ${var+text} */
#define VSQUESTION 4		/* ${var?message} */
#define VSASSIGN 5		/* ${var=text} */
E 5
I 5
#define VSNORMAL	0x1		/* normal variable:  $var or ${var} */
#define VSMINUS		0x2		/* ${var-text} */
#define VSPLUS		0x3		/* ${var+text} */
#define VSQUESTION	0x4		/* ${var?message} */
#define VSASSIGN	0x5		/* ${var=text} */
#define VSTRIMLEFT	0x6		/* ${var#pattern} */
#define VSTRIMLEFTMAX	0x7		/* ${var##pattern} */
#define VSTRIMRIGHT	0x8		/* ${var%pattern} */
#define VSTRIMRIGHTMAX 	0x9		/* ${var%%pattern} */
#define VSLENGTH	0xa		/* ${#var} */
E 5


/*
 * NEOF is returned by parsecmd when it encounters an end of file.  It
 * must be distinct from NULL, so we use the address of a variable that
 * happens to be handy.
 */
extern int tokpushback;
#define NEOF ((union node *)&tokpushback)
I 3
extern int whichprompt;		/* 1 == PS1, 2 == PS2 */
E 3


D 6
#ifdef __STDC__
union node *parsecmd(int);
int goodname(char *);
I 3
char *getprompt(void *);
E 3
#else
union node *parsecmd();
int goodname();
I 3
char *getprompt();
E 3
#endif
E 6
I 6
union node *parsecmd __P((int));
void fixredir __P((union node *, const char *, int));
int goodname __P((char *));
char *getprompt __P((void *));  
E 6
E 1
