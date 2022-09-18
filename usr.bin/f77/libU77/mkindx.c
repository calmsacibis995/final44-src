/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
char copyright[] =
"@(#) Copyright (c) 1980 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)mkindx.c	5.2 (Berkeley) 4/12/91";
#endif /* not lint */

/*
 *  mkindx.c - utility to format a nice index to source files, etc.
 *
 *  usage:  mkindx "title string" [file_name] [filename] .....
 */

# include	<stdio.h>

char id_mkindx[] = "@(#)mkindx.c	5.2 4/12/91";

char list[10000] = "pwd >>index; echo \" \" >>index; ls -l ";
char *apndx = ">>index";
char *cp = list;
extern char *ctime();
FILE *fopen(), *index;

main (argc, argv)
char **argv;
{
	short i;
	long time(), t;

	if (index = fopen ("index", "w"))
	{
		fprintf (index, "\n\n\n\n\n\n\n\n\n");
		center (argv[1]);   /* center title on page */
		t = time(0);
		center (ctime(&t));   /* center date & time */
		fprintf (index, "\n");
		fclose (index);
		while (*cp) cp++;   /* find end of shell command */
		for (i = 2; i < argc; i++)
		{
			while (*argv[i]) *cp++ = *(argv[i]++);
			*cp++ = ' ';
		}
		while (*apndx) *cp++ = *apndx++;
		*cp = '\0';
		system (list);
	}
	else fprintf (stderr, "mkindx: can't open index\n");
}

center (string)
char *string;
{
	short pad;

	pad = (72 - strlen(string)) >> 1;
	while (pad-- > 0) fputc(' ', index);
	fprintf (index, "%s\n", string);
}
