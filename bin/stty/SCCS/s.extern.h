h34863
s 00002/00002/00020
d D 8.1 93/05/31 15:47:36 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00005/00021
d D 5.5 93/04/29 15:17:20 bostic 5 4
c use C library err/warn routines
e
s 00000/00001/00026
d D 5.4 91/06/10 07:39:42 bostic 4 3
c NULL-terminate cchar arrays for Chris; better information hiding
e
s 00004/00002/00023
d D 5.3 91/06/05 15:22:19 bostic 3 2
c distribute the rest of the main loop into the modes and cchars modules
c bsearch the cchars arrays, minor cleanups
e
s 00016/00007/00009
d D 5.2 91/06/05 08:04:19 bostic 2 1
c break out rest of keywords into function table that can be bsearch'd
e
s 00016/00000/00000
d D 5.1 91/05/02 13:34:37 bostic 1 0
c date and time created 91/05/02 13:34:37 by bostic
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
void checkredirect __P((void));
void err __P((const char *, ...));
void gprint __P((struct termios *, struct winsize *, int));
void gread __P((struct termios *, char *));
void optlist __P((void));
void print __P((struct termios *, struct winsize *, int, enum FMT));
void warn __P((const char *, ...));
E 2
I 2
D 5
__BEGIN_DECLS
E 5
int	c_cchars __P((const void *, const void *));
int	c_modes __P((const void *, const void *));
I 3
int	csearch __P((char ***, struct info *));
E 3
void	checkredirect __P((void));
D 5
void	err __P((const char *, ...));
E 5
D 3
struct key *
	ksearch __P((char *));
E 3
void	gprint __P((struct termios *, struct winsize *, int));
void	gread __P((struct termios *, char *));
I 3
int	ksearch __P((char ***, struct info *));
int	msearch __P((char ***, struct info *));
E 3
void	optlist __P((void));
void	print __P((struct termios *, struct winsize *, int, enum FMT));
D 5
void	warn __P((const char *, ...));
__END_DECLS
E 5
I 5
void	usage __P((void));
E 5

extern struct cchar cchars1[], cchars2[];
D 4
extern struct modes cmodes[], imodes[], lmodes[], omodes[];
E 4
I 3
D 5
extern char *usage;
E 5
E 3
E 2
E 1
