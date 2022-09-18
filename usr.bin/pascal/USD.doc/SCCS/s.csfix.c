h04168
s 00005/00005/00187
d D 8.1 93/06/08 18:09:54 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00007/00184
d D 6.3 91/04/17 09:52:35 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00000/00189
d D 6.2 86/05/07 18:12:10 mckusick 4 3
c fix for errors beyond end of line
e
s 00003/00002/00186
d D 6.1 86/05/07 14:51:46 mckusick 3 2
c document distributed with 4.3BSD
e
s 00000/00000/00188
d D 5.1 86/05/07 14:51:23 mckusick 2 1
c document distributed with 4.2BSD
e
s 00188/00000/00000
d D 4.1 86/05/07 14:50:58 mckusick 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
D 6
char copyright[] =
D 5
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 5
I 5
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 5
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#include <stdio.h>
/*
 * csfix - fix constant spacing for error message flags in troff
 *
 * Bill Joy UCB September 11, 1977
 *
 * This would be better written in snobol!
 *
 * Normally fixes error flags in a pi listing
 * Optional - causes fixing of '---' and initial blank widthin a pxp profile.
 */

char	flag, dflag;

main(argc, argv)
	int argc;
	char *argv[];
{

	argc--, argv++;
	if (argc > 0 && argv[0][0] == '-' && argv[0][1] == 'd')
		dflag++, argc--, argv++;
	if (argc > 0 && argv[0][0] == '-')
		flag++, argc--, argv++;
	if (argc != 0) {
		write(2, "Usage: csfix\n", 13);
		exit(1);
	}
	while (getline()) {
		if (errline()) {
			flag ? fixpxp() : reformat();
			continue;
		}
		if (flag) {
			fixdigits();
			continue;
		}
		if (spwarn())
			continue;
		if (nontriv())
			save();
		if (dflag)
			fixdigits();
		else
			putline();
	}
	exit(0);
}

D 3
char	line[160], flagee[160];
E 3
I 3
char	line[160], flagee[160], *digitty();
E 3

getline()
{
	register char *cp, c;

	for (cp = line, c = getchar(); c != '\n' && c != EOF; c = getchar())
		*cp++ = c;
	if (c == EOF)
		return (0);
	*cp = 0;
	return (1);
}

errline()
{
	register int i;
	register char *cp;

	for (cp = line; cp[0] && cp[1] && cp[2]; cp++)
		if (cp[0] == '-' && cp[1] == '-' && cp[2] == '-')
			return (1);
	return (0);
}

reformat()
{
	register char *cp, c, *tail;

	printf("%2.2s", line);
	if (line[0] != 'w')
		printf("\\l'\\w`w `u-\\w`%2.2s`u '", line);
	for (cp = line; *cp != 0 && *cp != '^'; cp++)
		continue;
	tail = cp + 1;
	if (cp[-1] == '\b' && cp[-2] == '|')
D 3
		cp =- 2;
E 3
I 3
		cp -= 2;
E 3
	c = flagee[cp - line];
	flagee[cp - line] = 0;
	printf("\\l'\\w`%s`u-\\w`w `u\\&\\(rh'", flagee);
	flagee[cp - line] = c;
I 4
	if (c == '\0')
		c = flagee[cp - line - 1];
E 4
	printf("\\l'(\\w`%c`u-\\w`^`u)/2 '", c);
	printf("\\(ua");
	printf("\\l'(\\w`%c`u-\\w`^`u)/2 '", c);
	printf("\\l'\\w`---`u\\&\\(rh'%s\n", tail+3);
}

nontriv()
{

	switch (line[0]) {
		case 'E':
		case 'e':
		case 'w':
		case 's':
		case 0:
			return (0);
	}
	return (1);
}

save()
{

	strcpy(flagee, line);
}

putline()
{

	printf("%s\n", flag ? digitty(0) : line);
}

spwarn()
{

	if (line[0] != ' ' || line[1] != ' ' || line[2] != 'w')
		return (0);
	printf("  \\l'(\\w`E`u-\\w`w`u)/2 'w\\l'(\\w`E`u-\\w`w`u)/2 '");
	printf(&line[3]);
	printf("\n");
	return (1);
}

fixpxp()
{
	register char *cp;

	for (cp = line; *cp != '-'; cp++)
		continue;
	*cp = 0;
	printf("%s\\l'\\w`\\0\\0\\0\\0`u-\\w`.`u\\&\\(rh'%s\n", digitty(1), cp + 3);
}

I 3
char *
E 3
digitty(yup)
	char yup;
{
	register char *cp, *dp, *lp;

	for (lp = line; *lp && *lp != '|'; lp++)
		continue;
	if (yup == 0 && !*lp)
		return (line);
	for (cp = line, dp = flagee; cp < lp; cp++)
		if (*cp == ' ')
			*dp++ = '\\', *dp++ = '0';
		else
			*dp++ = *cp;
	strcpy(dp, cp);
	return (flagee);
}

fixdigits()
{
	register char *cp, c;

	for (cp = line; *cp == ' ' || *cp >= '0' && *cp <= '9'; cp++)
		continue;
	c = *cp, *cp = 0;
	digitty(1);
	*cp = c;
	printf("%s%s\n", flagee, cp);
}
E 1
