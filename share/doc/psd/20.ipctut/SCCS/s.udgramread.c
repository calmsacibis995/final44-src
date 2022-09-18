h65369
s 00002/00002/00052
d D 8.1 93/06/08 18:36:18 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00047
d D 6.5 91/04/17 10:18:58 bostic 5 4
c new copyright; att/bsd/shared
e
s 00027/00006/00047
d D 6.4 89/03/07 11:04:17 bostic 4 3
c add Berkeley specific copyright, networking release
e
s 00001/00001/00052
d D 6.3 86/05/08 14:51:02 karels 3 2
c update sockaddr_un
e
s 00005/00006/00048
d D 6.2 86/05/08 14:38:10 karels 2 1
c corrections and additions
e
s 00054/00000/00000
d D 6.1 86/05/04 16:34:23 mckusick 1 0
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

/*
 * In the included file <sys/un.h> a sockaddr_un is defined as follows
 * struct sockaddr_un {
 *	short	sun_family;
D 3
 *	char	sun_path[109];
E 3
I 3
 *	char	sun_path[108];
E 3
 * }; 
 */

#include <stdio.h>

#define NAME "socket"

/*
 * This program creates a UNIX domain datagram socket, binds a name to it,
 * then reads from the socket. 
 */
D 2

E 2
main()
{
D 2
	int             sock, length;
E 2
I 2
	int sock, length;
E 2
	struct sockaddr_un name;
D 2
	char            buf[1024];
E 2
I 2
	char buf[1024];
E 2

	/* Create socket from which to read. */
	sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("opening datagram socket");
D 2
		exit(-1);
E 2
I 2
		exit(1);
E 2
	}
	/* Create name. */
	name.sun_family = AF_UNIX;
	strcpy(name.sun_path, NAME);
	if (bind(sock, &name, sizeof(struct sockaddr_un))) {
D 2
		close(sock);
E 2
		perror("binding name to datagram socket");
I 2
		exit(1);
E 2
	}
	printf("socket -->%s\en", NAME);
	/* Read from the socket */
	if (read(sock, buf, 1024) < 0)
		perror("receiving datagram packet");
	printf("-->%s\en", buf);
D 2
	unlink(NAME);
E 2
	close(sock);
I 2
	unlink(NAME);
E 2
}
E 1
