h00076
s 00001/00001/00025
d D 5.2 90/06/08 16:54:02 bostic 2 1
c it's a C file...
e
s 00026/00000/00000
d D 5.1 90/06/07 17:50:04 bostic 1 0
c date and time created 90/06/07 17:50:04 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
D 2
	.asciz "%W% (Berkeley) %G%"
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>

/* This is used by the `assert' macro.  */
void
__eprintf(string, line, filename)
	char *string;
	int line;
	char *filename;
{
	(void)fprintf(stderr, string, line, filename);
}
E 1
