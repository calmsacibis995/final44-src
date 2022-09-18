h62575
s 00002/00002/00022
d D 8.1 93/05/31 14:45:44 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00024
d D 5.5 93/04/29 12:40:44 bostic 5 4
c use err/warn routines from C library
e
s 00015/00014/00010
d D 5.4 93/03/03 20:36:44 bostic 4 3
c add flags_to_string declaration
e
s 00014/00015/00010
d D 5.3 92/03/13 17:09:03 elan 3 2
c calculate all of the field sizes dynamically
e
s 00013/00013/00012
d D 5.2 92/01/29 16:14:15 elan 2 1
c Changed fn prototypes to conform to new version using fts(3) structs.
e
s 00025/00000/00000
d D 5.1 91/10/28 15:44:54 bostic 1 0
c date and time created 91/10/28 15:44:54 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
int	 acccmp __P((LS *, LS *));
E 2
I 2
D 3
int	 acccmp __P((const FTSENT *, const FTSENT *));
int	 modcmp __P((const FTSENT *, const FTSENT *));
int	 namecmp __P((const FTSENT *, const FTSENT *));
int	 revacccmp __P((const FTSENT *, const FTSENT *));
int	 revmodcmp __P((const FTSENT *, const FTSENT *));
int	 revnamecmp __P((const FTSENT *, const FTSENT *));
int	 revstatcmp __P((const FTSENT *, const FTSENT *));
int	 statcmp __P((const FTSENT *, const FTSENT *));
E 3
I 3
D 4
int acccmp __P((const FTSENT *, const FTSENT *));
int revacccmp __P((const FTSENT *, const FTSENT *));
int modcmp __P((const FTSENT *, const FTSENT *));
int revmodcmp __P((const FTSENT *, const FTSENT *));
int namecmp __P((const FTSENT *, const FTSENT *));
int revnamecmp __P((const FTSENT *, const FTSENT *));
int statcmp __P((const FTSENT *, const FTSENT *));
int revstatcmp __P((const FTSENT *, const FTSENT *));
E 4
I 4
int	 acccmp __P((const FTSENT *, const FTSENT *));
int	 revacccmp __P((const FTSENT *, const FTSENT *));
int	 modcmp __P((const FTSENT *, const FTSENT *));
int	 revmodcmp __P((const FTSENT *, const FTSENT *));
int	 namecmp __P((const FTSENT *, const FTSENT *));
int	 revnamecmp __P((const FTSENT *, const FTSENT *));
int	 statcmp __P((const FTSENT *, const FTSENT *));
int	 revstatcmp __P((const FTSENT *, const FTSENT *));
E 4
E 3

E 2
D 3
void	*emalloc __P((u_int));
D 2
void	 err __P((const char *, ...));
int	 modcmp __P((LS *, LS *));
int	 namecmp __P((LS *, LS *));
E 2
I 2
void	 err __P((int, const char *, ...));
E 2
void	 prcopy __P((char *, char *, int));
D 2
void	 printcol __P((LS *, int));
void	 printlong __P((LS *, int));
void	 printscol __P((LS *, int));
int	 revacccmp __P((LS *, LS *));
int	 revmodcmp __P((LS *, LS *));
int	 revnamecmp __P((LS *, LS *));
int	 revstatcmp __P((LS *, LS *));
int	 statcmp __P((LS *, LS *));
E 2
I 2
void	 printcol __P((FTSENT *, int, u_long, int));
void	 printlong __P((FTSENT *, int, u_long, int));
void	 printscol __P((FTSENT *, int, u_long, int));
E 2
void	 usage __P((void));
E 3
I 3
D 4
void err __P((int, const char *, ...));
void prcopy __P((char *, char *, int));
void printcol __P((DISPLAY *));
void printlong __P((DISPLAY *));
void printscol __P((DISPLAY *));
void usage __P((void));
E 4
I 4
D 5
void	 err __P((int, const char *, ...));
E 5
char	*flags_to_string __P((u_long, char *));
void	 prcopy __P((char *, char *, int));
void	 printcol __P((DISPLAY *));
void	 printlong __P((DISPLAY *));
void	 printscol __P((DISPLAY *));
void	 usage __P((void));
E 4
E 3
D 2
void	 warn __P((const char *, ...));
E 2
E 1
