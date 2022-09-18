h27423
s 00002/00002/00078
d D 8.1 93/06/06 15:36:35 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00075
d D 5.5 91/04/16 15:42:33 bostic 7 6
c new copyright; att/bsd/shared
e
s 00002/00008/00077
d D 5.4 91/02/05 23:33:07 torek 6 5
c use standard headers to get declarations; strdup is now in libc
e
s 00002/00002/00083
d D 5.3 88/01/03 00:33:17 bostic 5 4
c neither K&R or ANSI C allow untyped function declarations
e
s 00001/00002/00084
d D 5.2 87/04/07 15:51:41 mckusick 4 3
c port for tahoe from Nir peleg of CCI
e
s 00007/00003/00079
d D 5.1 85/06/06 16:06:48 dist 3 2
c Add copyright
e
s 00001/00001/00081
d D 1.2 82/01/18 22:14:50 linton 2 1
c sccsid
e
s 00082/00000/00000
d D 1.1 82/01/18 19:02:35 linton 1 0
c date and time created 82/01/18 19:02:35 by linton
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1982 Regents of the University of California */

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
/* static char sccsid[] = "%Z%%M% %I% %G%"; */
E 3
I 3
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 3
E 2

/*
 * Global debugger defines.
 *
 * All files include this header.
 */

#include <stdio.h>
I 6
#include <stdlib.h>
#include <string.h>
E 6

/*
 * Since C does not allow forward referencing of types,
 * all the global types are declared here.
 */

#define LOCAL static
#define NIL 0

typedef int BOOLEAN;

#define FALSE 0
#define TRUE 1

typedef unsigned int ADDRESS;		/* object code addresses */
typedef short LINENO;			/* source file line numbers */
typedef struct sym SYM;			/* symbol information structure */
typedef struct symtab SYMTAB;		/* symbol table */
typedef struct node NODE;		/* expression tree node */
typedef short OP;			/* tree operator */
typedef struct opinfo OPINFO;		/* tree operator information table */
typedef unsigned int WORD;		/* machine word */
typedef unsigned char BYTE;		/* machine byte */
typedef struct frame FRAME;		/* runtime activation record */

/*
 * Definitions of standard C library routines that aren't in the
 * standard I/O library, but which are generally useful.
 */

D 6
extern long atol();		/* ascii to long */
extern double atof();		/* ascii to floating point */
E 6
extern char *mktemp();		/* make a temporary file name */

/*
 * Definitions of library routines.
 */

char *cmdname;			/* name of command for error messages */
char *errfilename;		/* current file associated with error */
short errlineno;		/* line number associated with error */

D 5
error();			/* print an error message */
panic();			/* print error message and exit */
E 5
I 5
int error();			/* print an error message */
int panic();			/* print error message and exit */
E 5
short numerrors();		/* return number of errors since last call */

/*
 * defintions for doing memory allocation
 */

D 6
extern char *malloc();

E 6
#define alloc(n, type)	((type *) malloc((unsigned) (n) * sizeof(type)))
#define dispose(p)	{ free((char *) p); p = NIL; }

/*
D 4
 * macros for doing freads + fwrites
E 4
I 4
 * macro for doing freads
E 4
 */

#define get(fp, var)	fread((char *) &(var), sizeof(var), 1, fp)
D 4
#define put(fp, var)	fwrite((char *) &(var), sizeof(var), 1, fp)
E 4

/*
 * string definitions
 */

D 6
extern char *strcpy();
extern int strlen();

#define strdup(s)		strcpy(malloc((unsigned) strlen(s) + 1), s)
E 6
#define streq(s1, s2)	(strcmp(s1, s2) == 0)
E 1
