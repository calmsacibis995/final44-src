h60998
s 00006/00002/00093
d D 4.2 91/04/18 16:33:09 bostic 2 1
c new copyright; att/bsd/shared
e
s 00095/00000/00000
d D 4.1 83/05/06 23:21:11 tut 1 0
c date and time created 83/05/06 23:21:11 by tut
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

/*
 * This program has been replaced by "refer -B" (bibliography mode),
 * but is included here for backward compatiblity.
 */

#include <stdio.h>

int noanno = 0;		/* option to suppress .AP from %X field */

main(argc, argv)	/* format (annotated) bibliography for n/troff */
int argc;
char *argv[];
{
	FILE *fp, *fopen();

	if (argv[1][0] == '-' && argv[1][1] == 'x')
	{
		noanno = 1;
		argv++; argc--;
	}
	if (argc == 1)
	{
		annobib(stdin);
		exit(0);
	}
	while (--argc > 0)
	{
		if ((fp = fopen(*++argv, "r")) == NULL)
		{
			perror(*argv);
			exit(1);
		}
		annobib(fp);
		fclose(fp);
	}
	exit(0);
}

annobib(fp)		/* prepare bibliography for refer bare mode */
FILE *fp;
{
	char line[BUFSIZ];
	int begun, ended;

	begun = 0;
	ended = 1;
	while (fgets(line, BUFSIZ, fp))
	{
		if (line[0] == '%' && line[1] == 'X' && !noanno)
		{
			zap_x(line);
			printf(".]\n.AP\n%s", line);
			ended = 1;
			begun = 0;
		}
		else if (line[0] == '%')
		{
			if (!begun)
			{
				puts(".[");
				begun = 1;
				ended = 0;
			}
			fputs(line, stdout);
		}
		else if (line[0] == '\n')
		{
			if (!ended)
			{
				puts(".]");
				ended = 1;
				begun = 0;
			}
		}
		else
			fputs(line, stdout);
	}
	if (!ended)
		puts(".]");
}

zap_x(line)		/* take %X annotation flag out of line */
char line[];
{
	register int i, j;

	for (i = 3, j = 0; line[i] != NULL; i++, j++)
		line[j] = line[i];
	line[j] = NULL;
	return;
}
E 1
