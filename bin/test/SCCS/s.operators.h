h21046
s 00001/00001/00050
d D 8.3 94/04/02 10:02:57 pendry 5 4
c add 1994 copyright
e
s 00002/00002/00049
d D 8.2 94/04/01 03:51:06 pendry 4 3
c prettyness police
e
s 00002/00002/00049
d D 8.1 93/05/31 15:49:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00023/00027
d D 5.2 93/05/29 17:07:30 bostic 2 1
c add -h for symbolic links
e
s 00050/00000/00000
d D 5.1 93/04/30 11:38:09 bostic 1 0
c date and time created 93/04/30 11:38:09 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
D 5
 * Copyright (c) 1993
E 5
I 5
 * Copyright (c) 1993, 1994
E 5
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	NOT		0
#define	ISBLOCK		1
#define	ISCHAR		2
#define	ISDIR		3
#define	ISEXIST		4
#define	ISFILE		5
#define	ISSETGID	6
D 2
#define	ISSTICKY	7
#define	STRLEN		8
#define	ISFIFO		9
#define	ISREAD		10
#define	ISSIZE		11
#define	ISTTY		12
#define	ISSETUID	13
#define	ISWRITE		14
#define	ISEXEC		15
#define	NULSTR		16
E 2
I 2
#define	ISSYMLINK	7
#define	ISSTICKY	8
#define	STRLEN		9
#define	ISFIFO		10
#define	ISREAD		11
#define	ISSIZE		12
#define	ISTTY		13
#define	ISSETUID	14
#define	ISWRITE		15
#define	ISEXEC		16
#define	NULSTR		17
E 2

D 2
#define	FIRST_BINARY_OP	17
#define	OR1		17
#define	OR2		18
#define	AND1		19
#define	AND2		20
#define	STREQ		21
#define	STRNE		22
#define	EQ		23
#define	NE		24
#define	GT		25
#define	LT		26
#define	LE		27
#define	GE		28
E 2
I 2
#define	FIRST_BINARY_OP	18
#define	OR1		18
#define	OR2		19
#define	AND1		20
#define	AND2		21
#define	STREQ		22
#define	STRNE		23
#define	EQ		24
#define	NE		25
#define	GT		26
#define	LT		27
#define	LE		28
#define	GE		29
E 2


#define	OP_INT		1	/* arguments to operator are integer */
#define	OP_STRING	2	/* arguments to operator are string */
#define	OP_FILE		3	/* argument is a file name */

D 4
extern char *const unary_op[];
extern char *const binary_op[];
E 4
I 4
extern const char *const unary_op[];
extern const char *const binary_op[];
E 4
extern const char op_priority[];
extern const char op_argflag[];
E 1
