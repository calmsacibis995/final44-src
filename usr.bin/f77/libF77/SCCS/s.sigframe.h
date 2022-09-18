h43297
s 00009/00000/00014
d D 5.2 91/04/12 15:00:17 bostic 2 1
c new copyright; att/bsd/shared
e
s 00014/00000/00000
d D 5.1 91/04/12 14:40:01 bostic 1 0
c date and time created 91/04/12 14:40:01 by bostic
e
u
U
t
T
I 2
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
 * Definition of signal handler frame.
 */

struct sigframe {
	int	sf_signum;
	int	sf_code;
	struct	sigcontext *sf_scp;
	int	(*sf_handler)();
	int	r1;
	int 	r0;
	struct	sigcontext *sf_scpcopy;
}; 

E 1
