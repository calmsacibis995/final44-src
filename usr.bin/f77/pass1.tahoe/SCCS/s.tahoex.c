h06196
s 00011/00000/00042
d D 5.3 91/04/12 16:01:06 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00002/00040
d D 5.2 90/06/17 18:42:49 bostic 2 1
c move the include directory
e
s 00042/00000/00000
d D 5.1 90/06/17 18:09:08 bostic 1 0
c date and time created 90/06/17 18:09:08 by bostic
e
u
U
t
T
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
I 1
#include <stdio.h>
D 2
#include "../include/defines.h"
#include "../include/machdefs.h"
E 2
I 2
#include "defines.h"
#include "machdefs.h"
E 2



prchars(fp, s)
FILEP fp;
int *s;
{

fprintf(fp, ".byte 0%o,0%o\n", s[0], s[1]);
}



pruse(fp, s)
FILEP fp;
char *s;
{
fprintf(fp, "\t%s\n", s);
}



prskip(fp, k)
FILEP fp;
ftnint k;
{
fprintf(fp, "\t.space\t%ld\n", k);
}





prcomblock(fp, name)
FILEP fp;
char *name;
{
fprintf(fp, LABELFMT, name);
}
E 1
