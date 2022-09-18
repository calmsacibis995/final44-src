h55988
s 00008/00001/00035
d D 5.1 91/04/04 17:52:25 bostic 3 2
c new copyright; att/bsd/shared
e
s 00026/00022/00010
d D 1.2 89/01/16 20:26:49 bostic 2 1
c new version from Chris Torek
e
s 00032/00000/00000
d D 1.1 86/02/25 16:04:41 sam 1 0
c date and time created 86/02/25 16:04:41 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 3
/*	%W% (Berkeley) %G%	*/
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3
E 2

/*
 * Argument access types
 */
D 2
#define ACCA	(8<<3)	/* address only */
#define ACCR	(1<<3)	/* read */
#define ACCW	(2<<3)	/* write */
#define ACCM	(3<<3)	/* modify */
#define ACCB	(4<<3)	/* branch displacement */
#define ACCI	(5<<3)	/* XFC code */
E 2
I 2
#define ACCA	(8<<3)		/* address only */
#define ACCR	(1<<3)		/* read */
#define ACCW	(2<<3)		/* write */
#define ACCM	(3<<3)		/* modify */
#define ACCB	(4<<3)		/* branch displacement */
#define ACCI	(5<<3)		/* XFC code */
E 2

/*
 * Argument data types
 */
D 2
#define TYPB	0	/* byte */
#define TYPW	1	/* word */
#define TYPL	2	/* long */
#define TYPQ	3	/* quad */
#define TYPF	4	/* float */
#define TYPD	5	/* double */
E 2
I 2
#define TYPB	0		/* byte */
#define TYPW	1		/* word */
#define TYPL	2		/* long */
#define TYPQ	3		/* quad */
#define TYPF	4		/* float */
#define TYPD	5		/* double */
E 2

D 2
TYPE	struct optab	*OPTAB;
struct optab {
	char *iname;
	char val;
	char nargs;
	char argtype[6];
E 2
I 2
/*
 * Special instructions
 */
#define	KCALL	0xcf
#define	CASEL	0xfc

extern struct optab {
	char	*iname;
	u_char	val;
	u_char	nargs;
	u_char	argtype[6];
E 2
} optab[];
D 2
#define SYSSIZ 151
STRING	systab[];
STRING	regname[];
E 2
I 2

extern char *regname[];
E 2
E 1
