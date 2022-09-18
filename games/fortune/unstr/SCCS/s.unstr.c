h64008
s 00005/00005/00113
d D 8.1 93/05/31 17:16:08 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00014/00114
d D 5.8 91/04/08 17:56:13 bostic 8 7
c new copyright; att/bsd/shared
e
s 00000/00000/00128
d D 5.7 91/04/08 17:55:17 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00001/00127
d D 5.6 89/12/15 11:42:21 bostic 6 5
c add endian.h for htonl, ntohl.
e
s 00006/00001/00122
d D 5.5 89/09/07 08:12:15 bostic 5 4
c do everything in network order
e
s 00026/00088/00097
d D 5.4 89/09/05 19:49:22 bostic 4 3
c major rework; cleanup argument processing, write to stdout etc.
e
s 00032/00002/00153
d D 5.3 89/09/05 16:46:58 bostic 3 2
c add Berkeley specific copyright notices
e
s 00099/00081/00056
d D 5.2 89/09/05 15:54:09 bostic 2 1
c new distribution from Ken Arnold
e
s 00137/00000/00000
d D 5.1 86/12/09 13:53:43 bostic 1 0
c date and time created 86/12/09 13:53:43 by bostic
e
u
U
t
T
I 1
D 8
/*
I 3
 * Copyright (c) 1989 The Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
E 8
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * Ken Arnold.
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

#ifndef lint
D 9
char copyright[] =
D 8
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 8
I 8
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 8
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
E 3
D 2
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

# include	<stdio.h>
# include	"strfile.h"

# define	TRUE	1
# define	FALSE	0

/*
E 2
 *	This program un-does what "strfile" makes, thereby obtaining the
 * original file again.  This can be invoked with the name of the output
 * file, the input file, or both. If invoked with only a single argument
 * ending in ".dat", it is pressumed to be the input file and the output
 * file will be the same stripped of the ".dat".  If the single argument
 * doesn't end in ".dat", then it is presumed to be the output file, and
 * the input file is that name prepended by a ".dat".  If both are given
 * they are treated literally as the input and output files.
 *
 *	Ken Arnold		Aug 13, 1978
 */

D 2
# define	DELIM_CH	'-'
E 2
I 2
D 3
# include	<stdio.h>
# include	<ctype.h>
E 3
D 6
# include	<sys/types.h>
E 6
I 6
# include	<machine/endian.h>
E 6
# include	<sys/param.h>
# include	"strfile.h"
I 3
# include	<stdio.h>
# include	<ctype.h>
E 3
E 2

D 2
char	Infile[100],			/* name of input file */
	Outfile[100];			/* name of output file */
E 2
I 2
D 4
# define	TRUE	1
# define	FALSE	0
E 2

E 4
D 2
short	Oflag = FALSE;			/* use order of initial table */
E 2
I 2
# ifndef MAXPATHLEN
# define	MAXPATHLEN	1024
# endif	/* MAXPATHLEN */
E 2

D 2
FILE	*Inf, *Outf;
E 2
I 2
D 4
# ifdef SYSV
# define	rename(a1,a2)	(-1)
# endif
E 2

D 2
char	*rindex(), *malloc(), *strcat(), *strcpy();
E 2
I 2
char	Infile[MAXPATHLEN],		/* name of input file */
	Outfile[MAXPATHLEN],		/* name of output file */
	Tmpfile[MAXPATHLEN],		/* name of temporary file */
E 4
I 4
char	*Infile,			/* name of input file */
	Datafile[MAXPATHLEN],		/* name of data file */
E 4
	Delimch;			/* delimiter character */
E 2

I 2
D 4
FILE	*Inf, *Outf, *Textf;
E 4
I 4
FILE	*Inf, *Dataf;
E 4

D 4
char	*rindex(), *malloc(), *strcat(), *strcpy(), *mktemp();
E 4
I 4
char	*strcat(), *strcpy();
E 4

I 4
/* ARGSUSED */
E 4
E 2
main(ac, av)
int	ac;
char	**av;
{
D 2
	register char	c;
	register int	nstr, delim;
E 2
	static STRFILE	tbl;		/* description table */

D 4
	getargs(ac, av);
E 4
I 4
	getargs(av);
E 4
	if ((Inf = fopen(Infile, "r")) == NULL) {
		perror(Infile);
D 4
		exit(-1);
		/* NOTREACHED */
E 4
I 4
		exit(1);
E 4
	}
D 2
	if ((Outf = fopen(Outfile, "w")) == NULL) {
E 2
I 2
D 4
	(void) fread((char *) &tbl, sizeof tbl, 1, Inf);
E 4
I 4
	if ((Dataf = fopen(Datafile, "r")) == NULL) {
		perror(Datafile);
		exit(1);
	}
	(void) fread((char *) &tbl, sizeof tbl, 1, Dataf);
I 5
	tbl.str_version = ntohl(tbl.str_version);
	tbl.str_numstr = ntohl(tbl.str_numstr);
	tbl.str_longlen = ntohl(tbl.str_longlen);
	tbl.str_shortlen = ntohl(tbl.str_shortlen);
	tbl.str_flags = ntohl(tbl.str_flags);
E 5
E 4
	if (!(tbl.str_flags & (STR_ORDERED | STR_RANDOM))) {
		fprintf(stderr, "nothing to do -- table in file order\n");
		exit(1);
	}
	Delimch = tbl.str_delim;
D 4
	if ((Textf = fopen(Outfile, "r")) == NULL) {
E 2
		perror(Outfile);
		exit(-1);
		/* NOTREACHED */
	}
D 2
	(void) fread((char *) &tbl, sizeof tbl, 1, Inf);
	if (Oflag) {
		order_unstr(&tbl);
		exit(0);
E 2
I 2
	(void) strcpy(Tmpfile, mktemp("unstrXXXXXX"));
	if ((Outf = fopen(Tmpfile, "w")) == NULL) {
		perror(Tmpfile);
		exit(-1);
E 2
		/* NOTREACHED */
	}
E 4
D 2
	nstr = tbl.str_numstr;
	(void) fseek(Inf, (long) (sizeof (long) * (nstr + 1)), 1);
	delim = 0;
	for (nstr = 0; (c = getc(Inf)) != EOF; nstr++)
		if (c != '\0')
			putc(c, Outf);
		else if (nstr != tbl.str_numstr - 1)
			if (nstr == tbl.str_delims[delim]) {
				fputs("%-\n", Outf);
				delim++;
			}
			else
				fputs("%%\n", Outf);
E 2
I 2
	order_unstr(&tbl);
D 4
	fclose(Outf);
	fclose(Textf);
	fclose(Inf);
	if (rename(Tmpfile, Outfile) < 0 && mv(Tmpfile, Outfile) < 0) {
		fprintf(stderr, "could not rename %s to %s\n", Tmpfile, Outfile);
		exit(-1);
	}
E 4
I 4
	(void) fclose(Inf);
	(void) fclose(Dataf);
E 4
E 2
	exit(0);
D 2
	/* NOTREACHED */
E 2
}

D 4
getargs(ac, av)
register int	ac;
E 4
I 4
getargs(av)
E 4
D 2
register char	**av;
E 2
I 2
register char	*av[];
E 2
{
I 2
D 4
	register int	i;
E 2
	register char	*sp;
I 2
	register short	bad;
E 2

D 2
	if (ac > 1 && strcmp(av[1], "-o") == 0) {
		Oflag++;
		ac--;
		av++;
E 2
I 2
	bad = 0;
	for (i = 1; i < ac; i++)  {
		if (av[i][0] != '-') {
			(void) strcpy(Infile, av[i]);
			if (i + 1 >= ac) {
				(void) strcpy(Outfile, Infile);
				if ((sp = rindex(av[i], '.')) &&
				    strcmp(sp, ".dat") == 0)
					Outfile[strlen(Outfile) - 4] = '\0';
				else
					(void) strcat(Infile, ".dat");
			}
			else
				(void) strcpy(Outfile, av[i + 1]);
			break;
		}
		else if (av[i][1] == '\0') {
			printf("usage: unstr datafile[.dat] [outfile]\n");
			exit(0);
			/* NOTREACHED */
		}
		else
			for (sp = &av[i][1]; *sp != '\0'; sp++)
				switch (*sp) {
				  default:
					fprintf(stderr, "unknown flag: '%c'\n",
						*sp);
					bad++;
					break;
				}
E 4
I 4
	if (!*++av) {
		(void) fprintf(stderr, "usage: unstr datafile\n");
		exit(1);
E 4
E 2
	}
D 2
	if (ac < 2) {
		printf("usage: %s datafile[.dat] [ outfile ]\n", av[0]);
E 2
I 2
D 4
	if (bad) {
		printf("use \"%s -\" to get usage\n", av[0]);
E 2
		exit(-1);
	}
E 4
I 4
	Infile = *av;
	(void) strcpy(Datafile, Infile);
	(void) strcat(Datafile, ".dat");
E 4
D 2
	(void) strcpy(Infile, av[1]);
	if (ac < 3) {
		(void) strcpy(Outfile, Infile);
		if ((sp = rindex(av[1], '.')) && strcmp(sp, ".dat") == 0)
			Outfile[strlen(Outfile) - 4] = '\0';
		else
			(void) strcat(Infile, ".dat");
	}
	else
		(void) strcpy(Outfile, av[2]);
E 2
}

I 2
D 4
mv(file1, file2)
char	*file1, *file2;
{
	char	buf[BUFSIZ];

	sprintf(buf, "mv %s %s", file1, file2);
	return system(buf) != 0 ? -1 : 0;
}

E 4
E 2
order_unstr(tbl)
D 2
STRFILE	*tbl;
E 2
I 2
register STRFILE	*tbl;
E 2
{
D 2
	register int	i, c;
	register int	delim;
	register long	*seekpts;
E 2
I 2
	register int	i;
	register char	*sp;
	auto off_t	pos;
	char		buf[BUFSIZ];
E 2

D 2
	seekpts = (long *) malloc(sizeof *seekpts * tbl->str_numstr);	/* NOSTRICT */
	if (seekpts == NULL) {
		perror("malloc");
		exit(-1);
		/* NOTREACHED */
	}
	(void) fread((char *) seekpts, sizeof *seekpts, tbl->str_numstr, Inf);
	delim = 0;
	for (i = 0; i < tbl->str_numstr; i++, seekpts++) {
E 2
I 2
	for (i = 0; i < tbl->str_numstr; i++) {
D 4
		fread((char *) &pos, 1, sizeof pos, Inf);
		fseek(Textf, pos, 0);
E 4
I 4
		(void) fread((char *) &pos, 1, sizeof pos, Dataf);
D 5
		(void) fseek(Inf, pos, 0);
E 5
I 5
		(void) fseek(Inf, ntohl(pos), 0);
E 5
E 4
E 2
		if (i != 0)
D 2
			if (i == tbl->str_delims[delim]) {
				fputs("%-\n", Outf);
				delim++;
			}
E 2
I 2
D 4
			fprintf(Outf, "%c%c\n", Delimch, Delimch);
E 4
I 4
			(void) printf("%c\n", Delimch);
E 4
		for (;;) {
D 4
			sp = fgets(buf, sizeof buf, Textf);
E 4
I 4
			sp = fgets(buf, sizeof buf, Inf);
E 4
			if (sp == NULL || STR_ENDSTRING(sp, *tbl))
				break;
E 2
			else
D 2
				fputs("%%\n", Outf);
		(void) fseek(Inf, *seekpts, 0);
		while ((c = getc(Inf)) != '\0')
			putc(c, Outf);
E 2
I 2
D 4
				fputs(sp, Outf);
E 4
I 4
				fputs(sp, stdout);
E 4
		}
E 2
	}
}
E 1
