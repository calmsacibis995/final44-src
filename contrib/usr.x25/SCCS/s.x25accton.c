h00197
s 00026/00000/00013
d D 5.2 91/04/29 18:49:18 sklower 2 1
c versions for networking tape 2
e
s 00013/00000/00000
d D 5.1 90/09/03 18:55:37 sklower 1 0
c date and time created 90/09/03 18:55:37 by sklower
e
u
U
t
T
I 1
/*
I 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
#include <sys/param.h>
#include <sys/socket.h>
#include <netccitt/x25.h>
/*
E 2
 * Enable or disable X.25 accounting.
 */

main(argc, argv)
	char **argv;
{
	if (x25acct(argc > 1 ? argv[1] : (char *)0) < 0) {
		perror(argv[0]);
		exit(1);
	}
	exit(0);
I 2
}
x25acct(name)
char *name;
{
	int s = socket(AF_CCITT, SOCK_STREAM, 0);

	if (s < 0)
		return (s);
	if (name)
		return (setsockopt(s, CCITTPROTO_X25, PK_ACCTFILE,
			name, strlen(name) + 1));
	else
		return (setsockopt(s, CCITTPROTO_X25, PK_ACCTFILE,
			(char *)&name, 0));

E 2
}
E 1
