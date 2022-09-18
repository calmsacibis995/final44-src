h62513
s 00002/00002/00078
d D 8.1 93/06/08 18:36:08 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00073
d D 6.4 91/04/17 10:18:53 bostic 4 3
c new copyright; att/bsd/shared
e
s 00027/00006/00073
d D 6.3 89/03/07 11:04:07 bostic 3 2
c add Berkeley specific copyright, networking release
e
s 00024/00019/00055
d D 6.2 86/05/08 14:37:38 karels 2 1
c corrections and additions
e
s 00074/00000/00000
d D 6.1 86/05/04 16:34:14 mckusick 1 0
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
#include <sys/types.h>
#include <sys/socket.h>
I 2
#include <sys/time.h>
E 2
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#define TRUE 1

/*
 * This program uses select() to check that someone is trying to connect
 * before calling accept(). 
 */

main()
{
D 2
	int             sock, length;
E 2
I 2
	int sock, length;
E 2
	struct sockaddr_in server;
D 2
	int             msgsock;
	char            buf[1024];
	int             rval;
	int             i;
	int             ready;
	struct timeval  to;
E 2
I 2
	int msgsock;
	char buf[1024];
	int rval;
	fd_set ready;
	struct timeval to;
E 2

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
D 2
		exit(0);
E 2
I 2
		exit(1);
E 2
	}
	/* Name socket using wildcards */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 0;
	if (bind(sock, &server, sizeof(server))) {
		perror("binding stream socket");
I 2
		exit(1);
E 2
	}
	/* Find out assigned port number and print it out */
	length = sizeof(server);
	if (getsockname(sock, &server, &length)) {
		perror("getting socket name");
D 2
		exit(0);
E 2
I 2
		exit(1);
E 2
	}
	printf("Socket has port #%d\en", ntohs(server.sin_port));

	/* Start accepting connections */
	listen(sock, 5);
	do {
D 2
		ready = 1 << sock;
E 2
I 2
		FD_ZERO(&ready);
		FD_SET(sock, &ready);
E 2
		to.tv_sec = 5;
D 2
		select(20, &ready, 0, 0, &to);
		if (ready) {
			msgsock = accept(sock, 0, 0);
			do {
				for (i = 0; i < 1024; i++)
					buf[i] = '\e0';
E 2
I 2
		if (select(sock + 1, &ready, 0, 0, &to) < 0) {
			perror("select");
			continue;
		}
		if (FD_ISSET(sock, &ready)) {
			msgsock = accept(sock, (struct sockaddr *)0, (int *)0);
			if (msgsock == -1)
				perror("accept");
			else do {
				bzero(buf, sizeof(buf));
E 2
				if ((rval = read(msgsock, buf, 1024)) < 0)
					perror("reading stream message");
D 2
				i = 0;
				if (rval == 0)
E 2
I 2
				else if (rval == 0)
E 2
					printf("Ending connection\en");
				else
					printf("-->%s\en", buf);
D 2
			} while (rval != 0);
E 2
I 2
			} while (rval > 0);
E 2
			close(msgsock);
		} else
			printf("Do something else\en");
	} while (TRUE);
}
E 1
