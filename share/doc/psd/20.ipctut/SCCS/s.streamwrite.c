h22849
s 00002/00002/00053
d D 8.1 93/06/08 18:36:15 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00048
d D 6.4 91/04/17 10:18:54 bostic 4 3
c new copyright; att/bsd/shared
e
s 00027/00006/00048
d D 6.3 89/03/07 11:04:09 bostic 3 2
c add Berkeley specific copyright, networking release
e
s 00011/00009/00043
d D 6.2 86/05/08 14:37:45 karels 2 1
c corrections and additions
e
s 00052/00000/00000
d D 6.1 86/05/04 16:34:20 mckusick 1 0
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
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

D 2
#define M_SOCKET 0x00000001
E 2
#define DATA "Half a league, half a league . . ."

/*
 * This program creates a socket and initiates a connection with the socket
 * given in the command line.  One message is sent over the connection and
 * then the socket is closed, ending the connection. The form of the command
 * line is streamwrite hostname portnumber 
 */

main(argc, argv)
D 2
	int             argc;
	char          **argv;
E 2
I 2
	int argc;
	char *argv[];
E 2
{
D 2
	int             sock;
E 2
I 2
	int sock;
E 2
	struct sockaddr_in server;
	struct hostent *hp, *gethostbyname();
D 2
	char            buf[1024];
E 2
I 2
	char buf[1024];
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
	/* Connect socket using name specified by command line. */
	server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);
D 2
	bcopy(hp->h_addr, &(server.sin_addr.s_addr), hp->h_length);
E 2
I 2
	if (hp == 0) {
		fprintf(stderr, "%s: unknown host\n", argv[1]);
		exit(2);
	}
	bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
E 2
	server.sin_port = htons(atoi(argv[2]));

	if (connect(sock, &server, sizeof(server)) < 0) {
D 2
		close(sock);
E 2
		perror("connecting stream socket");
D 2
		exit(0);
E 2
I 2
		exit(1);
E 2
	}
	if (write(sock, DATA, sizeof(DATA)) < 0)
		perror("writing on stream socket");
	close(sock);
}
E 1
