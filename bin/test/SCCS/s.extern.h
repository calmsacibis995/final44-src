h57620
s 00000/00011/00017
d D 1.2 92/06/03 16:43:03 elan 2 1
c Fixed sccs bugs.
e
s 00028/00000/00000
d D 1.1 92/06/03 13:16:31 elan 1 0
c date and time created 92/06/03 13:16:31 by elan
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

D 2
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */


E 2
#include <sys/cdefs.h>

__BEGIN_DECLS
void error __P((char *));
void *stalloc __P((int));

__END_DECLS
E 1
