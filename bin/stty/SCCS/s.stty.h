h43318
s 00002/00002/00030
d D 8.1 93/05/31 15:47:58 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00014/00032
d D 5.3 91/06/10 07:39:47 bostic 3 2
c NULL-terminate cchar arrays for Chris; better information hiding
e
s 00022/00000/00024
d D 5.2 91/06/05 08:04:21 bostic 2 1
c break out rest of keywords into function table that can be bsearch'd
e
s 00024/00000/00000
d D 5.1 91/05/02 13:34:49 bostic 1 0
c date and time created 91/05/02 13:34:49 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#include <sys/ioctl.h>
#include <termios.h>

struct info {
	int fd;					/* file descriptor */
	int ldisc;				/* line discipline */
	int off;				/* turn off */
	int set;				/* need set */
	int wset;				/* need window set */
	char *arg;				/* argument */
	struct termios t;			/* terminal info */
	struct winsize win;			/* window info */
};

D 3
struct key {
	char *name;				/* name */
	void (*f) __P((struct info *));		/* function */
#define	F_NEEDARG	0x01			/* needs an argument */
#define	F_OFFOK		0x02			/* can turn off */
	int flags;
};

E 2
struct modes {
	char *name;
	long set;
	long unset;
};

E 3
struct cchar {
	char *name;
	int sub;
	u_char def;
};

enum FMT { NOTSET, GFLAG, BSD, POSIX };

#define	LINELENGTH	72
E 1
