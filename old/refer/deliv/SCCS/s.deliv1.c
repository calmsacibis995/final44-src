h16141
s 00006/00002/00047
d D 4.2 91/04/18 16:37:41 bostic 2 1
c new copyright; att/bsd/shared
e
s 00049/00000/00000
d D 4.1 83/05/06 23:46:59 tut 1 0
c date and time created 83/05/06 23:46:59 by tut
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

#include <stdio.h>

main(argc, argv)	/* goes from file:begin,l to actual characters */
char *argv[];
{
	FILE *fopen(), *fa = NULL;
	char line[750], *p, name[100], *strcpy();
	long lp;
	int len;

	if (argc > 1 && argv[1] && argv[1][0])
		chdir(argv[1]);
	name[0] = NULL;
	while (gets(line))
	{
		if (line[0] == '$' && line[1] == '$') 
		{
			chdir(line+2);
			continue;
		}
		for (p = line; *p != ':'; p++)
			;
		*p++ = 0;
		sscanf(p, "%ld,%d", &lp, &len);
		if (p == line)
			fa = stdin;
		else
			if (strcmp(name, line) != 0)
			{
				if (fa != NULL)
					fclose(fa);
				fa = fopen(line, "r");
				if (fa == NULL)
					err("Can't open %s", line);
				strcpy(name, line);
			}
		if (fa != NULL)
		{
			fseek (fa, lp, 0);
			fread (line, 1, len, fa);
			line[len] = 0;
			fputs(line, stdout);
		}
	}
}
E 1
