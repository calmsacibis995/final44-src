h42569
s 00006/00013/00017
d D 8.2 95/05/04 18:00:09 christos 4 3
c 
e
s 00002/00002/00028
d D 8.1 93/05/31 15:20:30 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00028
d D 5.2 93/05/24 15:40:00 marc 2 1
c fixes to support old style handling of ` ` (quoting), and "for var do"
e
s 00028/00000/00000
d D 5.1 91/03/07 20:27:58 bostic 1 0
c date and time created 91/03/07 20:27:58 by bostic
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
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* flags passed to redirect */
#define REDIR_PUSH 01		/* save previous values of file descriptors */
#define REDIR_BACKQ 02		/* save the command output in memory */

D 4
#ifdef __STDC__
E 4
union node;
D 4
void redirect(union node *, int);
void popredir(void);
void clearredir(void);
int copyfd(int, int);
I 2
int fd0_redirected_p(void);
E 2
#else
void redirect();
void popredir();
void clearredir();
int copyfd();
I 2
int fd0_redirected_p();
E 2
#endif
E 4
I 4
void redirect __P((union node *, int));
void popredir __P((void));
int fd0_redirected_p __P((void));
void clearredir __P((void)); 
int copyfd __P((int, int));

E 4
E 1
