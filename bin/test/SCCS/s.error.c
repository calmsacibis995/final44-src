h25410
s 00001/00001/00034
d D 1.3 92/06/03 16:46:43 elan 3 2
c Fixed copyright.
e
s 00018/00003/00017
d D 1.2 92/06/03 15:52:10 elan 2 1
c Added Berkeley Copyright.
e
s 00020/00000/00000
d D 1.1 92/06/03 13:16:29 elan 1 0
c date and time created 92/06/03 13:16:29 by elan
e
u
U
t
T
I 1
/*
D 2
 * Copyright (C) 1989 by Kenneth Almquist.  All rights reserved.
 * This file is part of ash, which is distributed under the terms specified
 * by the Ash General Public License.  See the file named LICENSE.
E 2
I 2
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
E 2
 */
I 2

#ifndef lint
D 3
char copyright[] =
E 3
I 3
static char copyright[] =
E 3
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2

#include <stdio.h>
#include <errno.h>

void
#ifdef __STDC__
error(char *msg, ...) {
#else
error(msg)
      char *msg;
      {
#endif
      fprintf(stderr, "test: %s\n", msg);
      exit(2);
}
E 1
