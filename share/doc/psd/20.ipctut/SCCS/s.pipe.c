h62788
s 00002/00002/00046
d D 8.1 93/06/08 18:35:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00041
d D 6.4 91/04/17 10:18:51 bostic 4 3
c new copyright; att/bsd/shared
e
s 00027/00006/00041
d D 6.3 89/03/07 11:04:05 bostic 3 2
c add Berkeley specific copyright, networking release
e
s 00008/00004/00039
d D 6.2 86/05/08 14:37:33 karels 2 1
c corrections and additions
e
s 00043/00000/00000
d D 6.1 86/05/04 16:34:07 mckusick 1 0
c document distributed with 4.3BSD
e
u
U
t
T
I 1
D 3
.\" Copyright (c) 1986 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
.\"
.\"	%W% (Berkeley) %G%
.\"
E 3
I 3
D 4
/*
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1986 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
I 4
D 5
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
.\" Copyright (c) 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 4
E 3
#include <stdio.h>

#define DATA "Bright star, would I were steadfast as thou art . . ."

/*
 * This program creates a pipe, then forks.  The child communicates to the
 * parent over the pipe. Notice that a pipe is a one-way communications
 * device.  I can write to the output socket (sockets[1], the second socket
 * of the array returned by pipe()) and read from the input socket
 * (sockets[0]), but not vice versa. 
 */

main()
{
D 2
	int             sockets[2], child;
E 2
I 2
	int sockets[2], child;
E 2

	/* Create a pipe */
D 2
	if (pipe(sockets) < 0)
E 2
I 2
	if (pipe(sockets) < 0) {
E 2
		perror("opening stream socket pair");
I 2
		exit(10);
	}
E 2

D 2
	if (child = fork()) {
		char            buf[1024];
E 2
I 2
	if ((child = fork()) == -1)
		perror("fork");
	else if (child) {
		char buf[1024];
E 2

		/* This is still the parent.  It reads the child's message. */
		close(sockets[1]);
		if (read(sockets[0], buf, 1024) < 0)
			perror("reading message");
		printf("-->%s\en", buf);
		close(sockets[0]);
	} else {
		/* This is the child.  It writes a message to its parent. */
		close(sockets[0]);
		if (write(sockets[1], DATA, sizeof(DATA)) < 0)
			perror("writing message");
		close(sockets[1]);
	}
}
E 1
