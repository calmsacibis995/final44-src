h60540
s 00007/00007/00009
d D 8.2 94/04/01 14:02:19 bostic 2 1
c KNF
e
s 00016/00000/00000
d D 8.1 94/04/01 06:50:04 pendry 1 0
c date and time created 94/04/01 06:50:04 by pendry
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
extern void	pw_edit __P((int));
extern void	pw_error __P((char *, int, int));
extern void	pw_init __P((void));
extern int	pw_lock __P((void));
extern int	pw_mkdb __P((void));
extern void	pw_prompt __P((void));
extern int	pw_tmp __P((void));
E 2
I 2
void	pw_edit __P((int));
void	pw_error __P((char *, int, int));
void	pw_init __P((void));
int	pw_lock __P((void));
int	pw_mkdb __P((void));
void	pw_prompt __P((void));
int	pw_tmp __P((void));
E 2
E 1
