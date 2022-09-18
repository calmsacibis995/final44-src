h08358
s 00002/00002/00013
d D 8.1 93/06/02 19:56:02 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00011
d D 7.2 91/05/04 19:26:10 karels 5 3
c add function prototypes
e
s 00004/00001/00011
d R 7.2 91/05/04 15:08:48 karels 4 3
c add prototypes, now stdarg'ed
e
s 00000/00000/00012
d D 7.1 90/07/01 13:53:01 karels 3 2
c rev 7
e
s 00001/00001/00011
d D 1.2 90/06/28 15:27:44 marc 2 1
c name change
e
s 00012/00000/00000
d D 1.1 90/05/22 16:09:20 marc 1 0
c date and time created 90/05/22 16:09:20 by marc
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

typedef struct session *tpr_t;

D 2
tpr_t tpr_open();
E 2
I 2
D 5
tpr_t	tprintf_open();
E 5
I 5
tpr_t	tprintf_open __P((struct proc *));
void	tprintf_close __P((tpr_t));

void	tprintf __P((tpr_t, const char *fmt, ...));
E 5
E 2
E 1
