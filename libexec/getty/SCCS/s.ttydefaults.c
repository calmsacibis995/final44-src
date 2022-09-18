h03699
s 00002/00002/00026
d D 8.1 93/06/04 18:50:40 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00025
d D 5.2 93/05/17 10:36:57 bostic 2 1
c ANSI C prototypes
e
s 00025/00000/00000
d D 5.1 91/01/19 17:17:44 bostic 1 0
c date and time created 91/01/19 17:17:44 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/termios.h>

I 2
#include "extern.h"

void
E 2
set_ttydefaults(fd)
	int fd;
{
	struct termios term;

	tcgetattr(fd, &term);
	term.c_iflag = TTYDEF_IFLAG;
	term.c_oflag = TTYDEF_OFLAG;
	term.c_lflag = TTYDEF_LFLAG;
	term.c_cflag = TTYDEF_CFLAG;
	tcsetattr(fd, TCSAFLUSH, &term);
}
E 1
