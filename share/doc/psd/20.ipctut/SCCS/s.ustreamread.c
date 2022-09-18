h26368
s 00002/00002/00068
d D 8.1 93/06/08 18:36:28 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00063
d D 6.5 91/04/17 10:18:59 bostic 5 4
c new copyright; att/bsd/shared
e
s 00027/00006/00063
d D 6.4 89/03/07 11:04:20 bostic 4 3
c add Berkeley specific copyright, networking release
e
s 00013/00014/00056
d D 6.3 86/05/08 14:38:15 karels 3 2
c corrections and additions
e
s 00003/00007/00067
d D 6.2 86/05/06 17:08:56 mckusick 2 1
c tighten up code to reduce wasted paper
e
s 00074/00000/00000
d D 6.1 86/05/04 16:34:29 mckusick 1 0
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

D 2
#define TRUE 1
E 2
#define NAME "socket"

/*
 * This program creates a socket in the UNIX domain and binds a name to it. 
 * After printing the socket's name it begins a loop. Each time through the
 * loop it accepts a connection and prints out messages from it.  When the
 * connection breaks, or a termination message comes through, the program
 * accepts a new connection. 
 */
D 2

E 2
main()
{
D 3
	int             sock;
E 3
I 3
	int sock, msgsock, rval;
E 3
	struct sockaddr_un server;
D 3
	int             msgsock;
	char            buf[1024];
D 2
	int             rval;
	int             i;
E 2
I 2
	int             rval, i;
E 3
I 3
	char buf[1024];
E 3
E 2

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
	/* Name socket using file system name */
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, NAME);
	if (bind(sock, &server, sizeof(struct sockaddr_un))) {
		perror("binding stream socket");
I 3
		exit(1);
E 3
	}
	printf("Socket has name %s\en", server.sun_path);
D 2

E 2
	/* Start accepting connections */
	listen(sock, 5);
D 2
	do {
E 2
I 2
	for (;;) {
E 2
		msgsock = accept(sock, 0, 0);
D 3
		do {
			for (i = 0; i < 1024; i++)
				buf[i] = '\e0';
E 3
I 3
		if (msgsock == -1)
			perror("accept");
		else do {
			bzero(buf, sizeof(buf));
E 3
			if ((rval = read(msgsock, buf, 1024)) < 0)
				perror("reading stream message");
D 3
			if (rval == 0) {
E 3
I 3
			else if (rval == 0)
E 3
				printf("Ending connection\en");
D 3
			} else {
E 3
I 3
			else
E 3
				printf("-->%s\en", buf);
D 3
			};
		} while (rval != 0);
E 3
I 3
		} while (rval > 0);
E 3
		close(msgsock);
D 2
	} while (TRUE);
E 2
I 2
	}
E 2
	/*
	 * The following statements are not executed, because they follow an
	 * infinite loop.  However, most ordinary programs will not run
	 * forever.  In the UNIX domain it is necessary to tell the file
D 3
	 * system that one is through using NAME. in most programs one uses
E 3
I 3
	 * system that one is through using NAME.  In most programs one uses
E 3
	 * the call unlink() as below. Since the user will have to kill this
	 * program, it will be necessary to remove the name by a command from
	 * the shell. 
	 */
D 3
	unlink(NAME);
E 3
	close(sock);
I 3
	unlink(NAME);
E 3
}
E 1
