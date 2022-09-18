h59517
s 00002/00002/00043
d D 8.1 93/06/08 18:36:31 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00038
d D 6.5 91/04/17 10:19:00 bostic 5 4
c new copyright; att/bsd/shared
e
s 00027/00006/00038
d D 6.4 89/03/07 11:04:21 bostic 4 3
c add Berkeley specific copyright, networking release
e
s 00006/00006/00038
d D 6.3 86/05/08 14:38:18 karels 3 2
c corrections and additions
e
s 00000/00001/00044
d D 6.2 86/05/06 17:08:59 mckusick 2 1
c tighten up code to reduce wasted paper
e
s 00045/00000/00000
d D 6.1 86/05/04 16:34:32 mckusick 1 0
c document distributed with 4.3BSD
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1986 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
.\"
.\"	%W% (Berkeley) %G%
.\"
E 4
I 4
D 5
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

E 5
I 5
D 6
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
E 6
I 6
.\" Copyright (c) 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 6
.\"
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 5
E 4
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#define DATA "Half a league, half a league . . ."

/*
 * This program connects to the socket named in the command line and sends a
 * one line message to that socket. The form of the command line is
 * ustreamwrite pathname 
 */
D 2

E 2
main(argc, argv)
D 3
	int             argc;
	char           *argv[];
E 3
I 3
	int argc;
	char *argv[];
E 3
{
D 3
	int             sock;
E 3
I 3
	int sock;
E 3
	struct sockaddr_un server;
D 3
	char            buf[1024];
E 3
I 3
	char buf[1024];
E 3

	/* Create socket */
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
D 3
		exit(0);
E 3
I 3
		exit(1);
E 3
	}
	/* Connect socket using name specified by command line. */
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, argv[1]);

	if (connect(sock, &server, sizeof(struct sockaddr_un)) < 0) {
		close(sock);
		perror("connecting stream socket");
D 3
		exit(0);
E 3
I 3
		exit(1);
E 3
	}
	if (write(sock, DATA, sizeof(DATA)) < 0)
		perror("writing on stream socket");
}
E 1
