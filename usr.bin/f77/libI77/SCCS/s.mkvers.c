h23724
s 00016/00004/00075
d D 5.2 91/04/12 15:23:25 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00072
d D 5.1 85/06/07 23:52:29 kre 2 1
c Add copyright
e
s 00073/00000/00000
d D 1.1 85/05/22 22:13:40 libs 1 0
c date and time created 85/05/22 22:13:40 by libs
e
u
U
t
T
I 1
D 2
char id_mkvers[] = "@(#)mkvers.c	1.2";
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 3
 */

I 3
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
char id_mkvers[] = "%W% %G%";
I 3

E 3
E 2
/*
 * extract sccs id strings from source files
 * first arg is lib name.
 * Put them in Version.c
 */

#include	<stdio.h>

#define SCCS_ID		"@(#)"
#define VERSION		"Version.c"

main(argc, argv)
int argc; char **argv;
{
	char buf[256];
	char *s, *e;
	char *index(), *ctime();
	long t;
	FILE *V, *fdopen();

	V = stdout; /* fdopen(creat(VERSION, 0644), "w"); */
	if (!V)
	{
		perror("mkvers");
		exit(1);
	}
	if (argc > 1 && argv[1][0] != '.')
	{
		fprintf(V, "char *");
		for (s = argv[1]; *s && *s != '.'; s++)
			fputc(*s, V);
		fprintf(V, "_id[] = {\n");
	}
	else
		fprintf(V, "char *sccs_id[] = {\n");
	if (argc-- > 1)
	{
		time(&t);
		s = ctime(&t) + 4;
		s[20] = '\0';
		fprintf(V, "\t\"%s%s\t%s\",\n", SCCS_ID, *++argv, s);
	}
	while (--argc)
	{
		if (freopen(*++argv, "r", stdin) == NULL)
		{
			perror(*argv);
			continue;
		}
		while(gets(buf))
		{
			s = buf;
			while(s = index(s, '@'))
				if (strncmp(s, SCCS_ID, 4) == 0)
					break;
			if (s)
			{
				e = index(s, '"');
				if (e)
					*e = '\0';
				fprintf(V, "\t\"%s\",\n", s);
				break;
			}
		}
		if (feof(stdin))
			fprintf(stderr, "%s: no sccs id string\n", *argv);
	}
	fprintf(V, "};\n");
	fclose(V);
	fflush(stdout);
	fflush(stderr);
}
E 1
