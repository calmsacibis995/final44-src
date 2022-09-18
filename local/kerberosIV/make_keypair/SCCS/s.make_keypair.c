h47833
s 00005/00005/00096
d D 8.1 93/06/01 23:13:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00013/00092
d D 5.1 91/04/12 11:32:44 bostic 6 5
c new copyright; att/bsd/shared
e
s 00023/00011/00082
d D 1.5 90/06/25 13:01:28 kfall 5 4
c make lint a bit happier
e
s 00029/00004/00064
d D 1.4 89/08/21 18:14:25 kfall 4 3
c use pathnames.h; explain a bit more
e
s 00008/00006/00060
d D 1.3 89/08/21 18:02:15 kfall 3 2
c filesystem reorg
e
s 00001/00001/00065
d D 1.2 88/12/12 22:58:56 kfall 2 1
c fix instructions a bit
e
s 00066/00000/00000
d D 1.1 88/12/12 20:54:51 kfall 1 0
c date and time created 88/12/12 20:54:51 by kfall
e
u
U
t
T
I 4
D 6
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 6
I 6
/*-
D 7
 * Copyright (c) 1988 The Regents of the University of California.
E 6
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */
I 6

#ifndef lint
D 7
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */
E 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
I 1
#include <sys/types.h>
D 3
#include <kerberos/krb.h>
E 3
I 3
D 5
#include <krb.h>
E 5
I 5
#include <sys/file.h>
#include <netinet/in.h>
E 5
E 3
#include <stdio.h>
#include <netdb.h>
D 5
#include <netinet/in.h>
#include <sys/file.h>
E 5
I 5
#include <kerberosIV/des.h>
#include <kerberosIV/krb.h>
E 5
I 3
#include "pathnames.h"
E 3
#include "register_proto.h"

I 5
extern void random_key(), herror();
void make_key(), usage();

E 5
D 3
#define	KFILE	"update.key%s"

E 3
main(argc, argv)
D 5
char	**argv;
E 5
I 5
	int	argc;
	char	**argv;
E 5
{
D 5
	char		namebuf[255];
	int		fd;
E 5
	struct hostent	*hp;
	char		*addr;
	int		i;
	struct sockaddr_in	sin;

D 5
	if(argc != 2) {
E 5
I 5
	if (argc != 2) {
E 5
		usage(argv[0]);
		exit(1);
	}

D 5
	hp = gethostbyname(argv[1]);
E 5
I 5
	if ((hp = gethostbyname(argv[1])) == NULL) {
		herror(argv[1]);
		exit(1);
	}

E 5
D 4
	for(i = 0; addr = hp->h_addr_list[i]; i++) {
E 4
I 4
	for (i = 0; addr = hp->h_addr_list[i]; i++) {
E 4
		addr = hp->h_addr_list[i];
		bcopy(addr, &sin.sin_addr, hp->h_length);

		printf("Making key for host %s (%s)\n",
			argv[1], inet_ntoa(sin.sin_addr));
		make_key(sin.sin_addr);
	}
	printf("==========\n");
D 3
	printf("One copy of the each key should be put in /kerberos on the\n");
	printf("Kerberos machine (mode 600, owner root).\n");
E 3
I 3
	printf("One copy of the each key should be put in %s on the\n",
		SERVER_KEYDIR);
	printf("Kerberos server machine (mode 600, owner root).\n");
E 3
	printf("Another copy of each key should be put on the named\n");
D 2
	printf("client as /.updated.keyXXX.XXX.XXX.XXX (same modes as above).\n");
E 2
I 2
D 3
	printf("client as /.update.keyXXX.XXX.XXX.XXX (same modes as above).\n");
E 3
I 3
	printf("client as %sXXX.XXX.XXX.XXX (same modes as above),\n",
		CLIENT_KEYFILE);
	printf("where the X's refer to digits of the host's inet address.\n");
E 3
E 2
D 5
	fflush(stdout);
E 5
I 5
	(void)fflush(stdout);
	exit(0);
E 5
}

I 5
void
E 5
make_key(addr)
	struct in_addr	addr;
{
	struct keyfile_data	kfile;
	char		namebuf[255];
	int		fd;

D 4
	sprintf(namebuf, KFILE, inet_ntoa(addr));
E 4
I 4
D 5
	sprintf(namebuf, ".%s%s",
E 5
I 5
	(void)sprintf(namebuf, ".%s%s",
E 5
		CLIENT_KEYFILE,
		inet_ntoa(addr));
E 4
	fd = open(namebuf, O_WRONLY|O_CREAT, 0600);
D 4
	if(fd < 0) {
E 4
I 4
	if (fd < 0) {
E 4
		perror("open");
		exit(1);
	}
	random_key(kfile.kf_key);
D 4
	if(write(fd, &kfile, sizeof(kfile)) != sizeof(kfile)) {
E 4
I 4
	printf("writing to file -> %s ...", namebuf);
	if (write(fd, &kfile, sizeof(kfile)) != sizeof(kfile)) {
E 4
		fprintf(stderr, "error writing file %s\n", namebuf);
	}
I 4
	printf("done.\n");
E 4
D 5
	close(fd);
E 5
I 5
	(void)close(fd);
	return;
E 5
}
I 5

void
E 5
usage(name)
	char	*name;
{
	fprintf(stderr, "usage: %s host\n", name);
}
E 1
