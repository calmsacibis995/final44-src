h56727
s 00001/00000/00093
d D 8.3 95/05/04 15:48:52 bostic 4 3
c optarg/optind moved to unistd.h
e
s 00005/00001/00088
d D 8.2 95/04/27 16:30:53 bostic 3 2
c correctly  format the usage message
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00084
d D 8.1 93/06/06 22:24:35 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00089/00000/00000
d D 5.1 93/05/06 15:07:01 bostic 1 0
c date and time created 93/05/06 15:07:01 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/sysctl.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 4
#include <unistd.h>
E 4

void usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
{
	struct stat sb;
	size_t len;
	int ch, sverrno, mib[2];
	char *p, *t, *std, path[MAXPATHLEN];

	while ((ch = getopt(argc, argv, "")) != EOF)
		switch (ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

I 3
	if (argc == 0)
		usage();

E 3
	/* Retrieve the standard path. */
	mib[0] = CTL_USER;
	mib[1] = USER_CS_PATH;
	if (sysctl(mib, 2, NULL, &len, NULL, 0) == -1)
		return (-1);
	if (len == 0)
		err(1, "user_cs_path: sysctl: zero length\n");
	if ((std = malloc(len)) == NULL)
		err(1, NULL);
	if (sysctl(mib, 2, std, &len, NULL, 0) == -1) {
		sverrno = errno;
		free(std);
		errno = sverrno;
		err(1, "sysctl: user_cs_path");
	}

	/* For each path, for each program... */
	for (; *argv; ++argv)
		for (p = std;; *p++ = ':') {
			t = p;
			if ((p = strchr(p, ':')) != NULL) {
				*p = '\0';
				if (t == p)
					t = ".";
			} else
				if (strlen(t) == 0)
					t = ".";
			(void)snprintf(path, sizeof(path), "%s/%s", t, *argv);
			if (!stat(path, &sb))
				(void)printf("%s\n", path);
			if (p == NULL)
				break;
		}
}

void
usage()
{
D 3
	(void)fprintf(stderr, "whereis: program ...\n");
E 3
I 3

	(void)fprintf(stderr, "usage: whereis program [...]\n");
E 3
	exit (1);
}
E 1
