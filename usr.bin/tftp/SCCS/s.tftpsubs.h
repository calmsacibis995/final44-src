h65489
s 00002/00002/00020
d D 8.1 93/06/06 16:32:58 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00000/00000
d D 5.1 93/05/16 16:10:22 torek 1 0
c date and time created 93/05/16 16:10:22 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1993 Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Prototypes for read-ahead/write-behind subroutines for tftp user and
 * server.
 */
struct tftphdr *r_init __P((void));
void	read_ahead __P((FILE *, int));
int	readit __P((FILE *, struct tftphdr **, int));

int	synchnet __P((int));

struct tftphdr *w_init __P((void));
int	write_behind __P((FILE *, int));
int	writeit __P((FILE *, struct tftphdr **, int, int));
E 1
