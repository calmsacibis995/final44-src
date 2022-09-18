h58557
s 00002/00002/00032
d D 8.1 93/06/06 15:56:59 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00030/00013
d D 5.2 93/04/30 16:58:51 bostic 2 1
c minor integration in 4BSD source tree
e
s 00043/00000/00000
d D 5.1 93/04/30 13:30:03 muller 1 0
c date and time created 93/04/30 13:30:03 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1991 Keith Muller.
D 2
 * Copyright (c) 1991 The Regents of the University of California.
E 2
I 2
D 3
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *      %W% (Berkeley) %G%
 */

D 2
/*
 * External references from each source file
 */
E 2
I 2
extern int eoptind;
extern char *eoptarg;
E 2

D 2
#include <sys/cdefs.h>

extern int	eoptind;
extern char	*eoptarg;

/*
 * functions
 */
int onecol __P((int, char **));
int vertcol __P((int, char **));
int horzcol __P((int, char **));
int mulfile __P((int, char **));
int inln __P((FILE *, char *, register int, int *, int, int *));
int otln __P((register char *, int, int *, int *, int));
int inskip __P((FILE *, register int, register int));
void addnum __P((register char *, register int, register int));
int prhead __P((char *, char *, int));
int prtail __P((register int, int));
void terminate __P((int));
void flsh_errs __P((void));
void mfail __P((void));
void pfail __P((void));
void usage __P((void));
FILE * nxtfile __P((int, char **, char **, char *, int));
int setup __P((register int, register char **));
int egetopt __P((int, char * const *, const char *));
E 2
I 2
void	 addnum __P((char *, int, int));
int	 egetopt __P((int, char * const *, const char *));
void	 flsh_errs __P((void));
int	 horzcol __P((int, char **));
int	 inln __P((FILE *, char *, int, int *, int, int *));
int	 inskip __P((FILE *, int, int));
void	 mfail __P((void));
int	 mulfile __P((int, char **));
FILE	*nxtfile __P((int, char **, char **, char *, int));
int	 onecol __P((int, char **));
int	 otln __P((char *, int, int *, int *, int));
void	 pfail __P((void));
int	 prhead __P((char *, char *, int));
int	 prtail __P((int, int));
int	 setup __P((int, char **));
void	 terminate __P((int));
void	 usage __P((void));
int	 vertcol __P((int, char **));
E 2
E 1
