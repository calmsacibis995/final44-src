h13700
s 00007/00000/00014
d D 8.2 95/05/04 18:00:01 christos 6 5
c 
e
s 00000/00000/00014
d D 8.1 93/05/31 15:39:54 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00000/00004
d D 1.4 93/05/31 15:39:00 bostic 4 3
c fix copyright notice, SCCS header
e
s 00001/00000/00003
d D 1.3 92/07/15 10:37:01 marc 3 2
c add displayhist variable
e
s 00001/00002/00002
d D 1.2 92/06/23 18:39:14 marc 2 1
c include <histedit.h>
e
s 00004/00000/00000
d D 1.1 92/06/03 17:58:44 marc 1 0
c date and time created 92/06/03 17:58:44 by marc
e
u
U
t
T
I 4
/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 4
I 1
D 2
#include "../editline/history.h"	/* XXX - rename */
#include "../editline/editline.h"	/* XXX - rename */
E 2
I 2
#include <histedit.h>
I 4

E 4
E 2
extern History *hist;
extern EditLine *el;
I 3
extern int displayhist;
I 6

void histedit __P((void));
void sethistsize __P((void));
int histcmd __P((int, char **));
int not_fcnumber __P((char *));
int str_to_event __P((char *, int));

E 6
E 3
E 1
