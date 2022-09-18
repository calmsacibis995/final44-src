h07827
s 00001/00011/00031
d D 7.3 90/06/28 22:33:51 bostic 3 2
c new copyright notice
e
s 00018/00000/00024
d D 7.2 88/07/09 13:44:04 bostic 2 1
c install approved copyright notice
e
s 00024/00000/00000
d D 7.1 88/05/14 12:19:46 karels 1 0
c vax 8200 support from torek
e
u
U
t
T
I 1
/*
I 2
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
E 2
 *	%W% (Berkeley) %G%
 */

/*
 * Software status per BI node.
 */

struct	binode_status {
/*	int	bh_type;		/* type of adapter */
	struct	biiregs *bh_bi;		/* virt addr of registers */
	struct	biiregs *bh_physbi;	/* phys addr of registers */
	int	bh_errcnt;		/* number of errors */
	int	bh_ivec;		/* interrupt vector */
	int	bh_arb;			/* arbitration */
};

/*
 * ... per BI
 */
struct	bi_hd {
	short	bh_nodes;		/* which nodes are present */
	struct	binode_status bh_nodes[16];	/* info about those nodes */
};
E 1
