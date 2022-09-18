h58658
s 00002/00002/00025
d D 8.1 93/06/06 16:30:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00020
d D 5.3 92/03/04 14:54:31 bostic 4 2
c whitespace changes
e
s 00007/00007/00020
d R 5.3 92/03/04 09:14:13 bostic 3 2
c use stdin instead of another file descriptor; make -[cnb] -r work
c on pipes
e
s 00001/00001/00026
d D 5.2 92/03/03 16:13:27 bostic 2 1
c make tail work like head for multiple files
e
s 00027/00000/00000
d D 5.1 91/07/21 14:50:00 bostic 1 0
c date and time created 91/07/21 14:50:00 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	WR(p, size) \
	if (write(STDOUT_FILENO, p, size) != size) \
		oerr();

enum STYLE { NOTSET = 0, FBYTES, FLINES, RBYTES, RLINES, REVERSE };

D 4
void	forward __P((FILE *, enum STYLE, long, struct stat *));
void	reverse __P((FILE *, enum STYLE, long, struct stat *));
E 4
I 4
void forward __P((FILE *, enum STYLE, long, struct stat *));
void reverse __P((FILE *, enum STYLE, long, struct stat *));
E 4

D 4
void	bytes __P((FILE *, off_t));
void	lines __P((FILE *, off_t));
E 4
I 4
void bytes __P((FILE *, off_t));
void lines __P((FILE *, off_t));
E 4

D 2
void	err __P((const char *fmt, ...));
E 2
I 2
D 4
void	err __P((int fatal, const char *fmt, ...));
E 2
void	ierr __P((void));
void	oerr __P((void));
E 4
I 4
void err __P((int fatal, const char *fmt, ...));
void ierr __P((void));
void oerr __P((void));
E 4

extern int fflag, rflag, rval;
extern char *fname;
E 1
