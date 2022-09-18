h16866
s 00002/00002/00025
d D 8.1 93/06/04 16:52:56 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00027
d D 5.2 92/07/03 00:24:06 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00027/00000/00000
d D 5.1 92/06/22 18:08:44 bostic 1 0
c date and time created 92/06/22 18:08:44 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * tokenizer.h: Header file for tokenizer routines
 */
#ifndef _h_tokenizer
#define _h_tokenizer

typedef struct tokenizer Tokenizer;

Tokenizer 	*tok_init	__P((const char *));
void		 tok_reset	__P((Tokenizer *));
void		 tok_end	__P((Tokenizer *));
int		 tok_line	__P((Tokenizer *, const char *, 
				     int *, char ***));

#endif /* _h_tokenizer */
E 1
