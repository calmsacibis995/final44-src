h48394
s 00002/00002/00033
d D 8.1 93/05/31 17:44:18 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00033
d D 5.2 92/01/08 14:19:17 bostic 2 1
c add Keith Gabryelski to contrib listing
e
s 00034/00000/00000
d D 5.1 91/11/10 14:24:35 bostic 1 0
c Jim Oldroyd's version of quiz.
c date and time created 91/11/10 14:24:35 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
D 2
 * Jim R. Oldroyd at The Instruction Set.
E 2
I 2
 * Jim R. Oldroyd at The Instruction Set and Keith Gabryelski at
 * Commodore Business Machines.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	TRUE		1
#define	FALSE		0

/* Length of compiled regexp machine; increase if not big enough. */
#define	RXP_LINE_SZ	8192

/* Maximum line length for data files. */
#define	LINE_SZ		1024

/* Linked list for holding index and data file information. */
typedef struct qentry {
	struct qentry *q_next;		/* next one */
	char	*q_text;		/* category text string from file */
	int	 q_asked;		/* TRUE if question's been asked */
	int	 q_answered;		/* TRUE if question's been answered */
} QE;

extern char rxperr[];

int	 rxp_compile __P((char *));
char	*rxp_expand __P((void));
int	 rxp_match __P((char *));
E 1
