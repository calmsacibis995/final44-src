h48538
s 00001/00001/00027
d D 8.3 94/04/02 10:03:52 pendry 4 3
c add 1994 copyright
e
s 00018/00010/00010
d D 8.2 94/04/01 04:59:47 pendry 3 2
c prettyness police
e
s 00002/00002/00018
d D 8.1 93/06/06 14:19:24 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00000/00000
d D 5.1 91/04/03 11:08:05 bostic 1 0
c date and time created 91/04/03 11:08:05 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
D 4
 * Copyright (c) 1991, 1993
E 4
I 4
 * Copyright (c) 1991, 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include <sys/cdefs.h>
E 3
I 3
int	append __P((char **));
void	badfmt __P((void));
int	compare __P((char *));
int	contents __P((char **));
int	delete __P((char **));
void	error __P((char *));
int	extract __P((char **));
char   *files __P((char **argv));
int	move __P((char **));
void	orphans __P((char **argv));
int	print __P((char **));
int	replace __P((char **));
char   *rname __P((char *));
int	tmp __P((void));
E 3

D 3
__BEGIN_DECLS
void	 badfmt __P((void));
void	 error __P((char *));
void	 orphans __P((char **argv));
int	 compare __P((char *));
int	 tmp __P((void));
char	*files __P((char **argv));
char	*rname __P((char *));
__END_DECLS
E 3
I 3
extern char *archive;
extern char *posarg, *posname;		/* positioning file name */
extern char *tname;                     /* temporary file "name" */
extern CHDR chdr;			/* converted header */
E 3
E 1
