h09267
s 00002/00002/00024
d D 8.1 93/06/06 14:09:26 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00022
d D 5.2 93/06/03 17:30:14 bostic 2 1
c lint
e
s 00022/00000/00000
d D 5.1 93/05/11 11:50:07 bostic 1 0
c date and time created 93/05/11 11:50:07 by bostic
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
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#if __STDC__
E 2
struct tsp;
I 2
#endif

extern struct cmd cmdtab[];
E 2

void	bytehostorder __P((struct tsp *));
void	bytenetorder __P((struct tsp *));
void	clockdiff __P((int, char *[]));
void	help __P((int, char *[]));
void	intr __P((int));
void	makeargv __P((void));
void	msite __P((int, char *[]));
int	priv_resources __P((void));
void	quit __P((void));
void	testing __P((int, char *[]));
void	tracing __P((int, char *[]));
E 1
