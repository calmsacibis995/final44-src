h29293
s 00002/00002/00028
d D 8.1 93/06/04 18:50:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00029
d D 5.2 93/05/27 12:56:03 elan 2 1
c Change protos to use getcap(3) routeines.
e
s 00030/00000/00000
d D 5.1 93/05/17 10:37:06 bostic 1 0
c date and time created 93/05/17 10:37:06 by bostic
e
u
U
t
T
I 1
/*
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

struct delayval;

int	 adelay __P((int, struct delayval *));
char	*autobaud __P((void));
int	 delaybits __P((void));
void	 edithost __P((char *));
void	 gendefaults __P((void));
int	 getent __P((char *, char *));
int	 getflag __P((char *));
long	 getnum __P((char *));
char	*getstr __P((char *, char **));
D 2
void	 gettable __P((char *, char *, char *));
E 2
I 2
void	 gettable __P((char *, char *));
E 2
void	 makeenv __P((char *[]));
char	*portselector __P((void));
void	 set_ttydefaults __P((int));
void	 setchars __P((void));
void	 setdefaults __P((void));
long	 setflags __P((int));
int	 speed __P((int));

int	 login_tty __P((int));			/* From libutil. */
E 1
