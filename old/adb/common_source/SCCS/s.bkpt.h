h64848
s 00005/00002/00019
d D 5.2 91/04/04 18:01:50 bostic 2 1
c new copyright; att/bsd/shared
e
s 00021/00000/00000
d D 5.1 89/01/16 20:24:42 bostic 1 0
c new version from Chris Torek
e
u
U
t
T
I 1
D 2
/*
 * adb: breakpoints.
E 2
I 2
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

#define	MAX_BKPTCOM	64	/* maximum length of command at bkpt */

enum bkflag { BKPT_FREE, BKPT_SET, BKPT_TRIPPED };

struct bkpt {
	struct	bkpt *next;	/* linked list */
	enum	bkflag state;	/* state */
	addr_t	loc;		/* where set (in SP_INSTR) */
	bpt_t	ins;		/* original instruction(s) */
	int	count;		/* ??? */
	int	initcnt;	/* ??? */
	char	comm[MAX_BKPTCOM];/* command to execute when tripped */
};

struct bkpt *scanbkpt();	/* look up a breakpoint given an address */
E 1
