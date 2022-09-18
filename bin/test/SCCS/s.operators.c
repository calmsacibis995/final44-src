h00847
s 00001/00001/00121
d D 8.3 94/04/02 10:02:52 pendry 5 4
c add 1994 copyright
e
s 00002/00002/00120
d D 8.2 94/04/01 03:51:05 pendry 4 3
c prettyness police
e
s 00002/00002/00120
d D 8.1 93/05/31 15:49:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00119
d D 5.2 93/05/29 17:07:30 bostic 2 1
c add -h for symbolic links
e
s 00119/00000/00000
d D 5.1 93/04/30 11:38:05 bostic 1 0
c date and time created 93/04/30 11:38:05 by bostic
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Operators used in the test command.
 */

#include <stdio.h>

#include "operators.h"

D 4
char *const unary_op[] = {
E 4
I 4
const char *const unary_op[] = {
E 4
      "!",
      "-b",
      "-c",
      "-d",
      "-e",
      "-f",
      "-g",
I 2
      "-h",
E 2
      "-k",
      "-n",
      "-p",
      "-r",
      "-s",
      "-t",
      "-u",
      "-w",
      "-x",
      "-z",
      NULL
};

D 4
char *const binary_op[] = {
E 4
I 4
const char *const binary_op[] = {
E 4
      "-o",
      "|",
      "-a",
      "&",
      "=",
      "!=",
      "-eq",
      "-ne",
      "-gt",
      "-lt",
      "-le",
      "-ge",
      NULL
};

const char op_priority[] = {
      3,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
      12,
I 2
      12,
E 2
      1,
      1,
      2,
      2,
      4,
      4,
      4,
      4,
      4,
      4,
      4,
      4,
};

const char op_argflag[] = {
      0,
I 2
      OP_FILE,
E 2
      OP_FILE,
      OP_FILE,
      OP_FILE,
      OP_FILE,
      OP_FILE,
      OP_FILE,
      OP_FILE,
      OP_STRING,
      OP_FILE,
      OP_FILE,
      OP_FILE,
      OP_INT,
      OP_FILE,
      OP_FILE,
      OP_FILE,
      OP_STRING,
      0,
      0,
      0,
      0,
      OP_STRING,
      OP_STRING,
      OP_INT,
      OP_INT,
      OP_INT,
      OP_INT,
      OP_INT,
      OP_INT,
};
E 1
