h11013
s 00023/00005/00178
d D 8.4 94/08/14 16:50:00 eric 19 18
c allow long form of "S" option and comments on that option line
e
s 00008/00000/00175
d D 8.3 93/12/27 17:07:16 eric 18 17
c include totals (from Tom Ferrin)
e
s 00000/00001/00175
d D 8.2 93/07/27 10:38:55 eric 17 16
c avoid compilation problems
e
s 00005/00005/00171
d D 8.1 93/06/07 10:21:37 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00120/00013/00056
d D 6.2 93/02/23 08:13:07 eric 15 14
c read .cf file to find mailer names and location of stat file
e
s 00000/00000/00069
d D 6.1 92/12/21 16:14:07 eric 14 13
c Release 6
e
s 00001/00011/00068
d D 5.7 90/06/01 18:58:23 bostic 13 12
c new copyright notice
e
s 00002/00001/00077
d D 5.6 89/05/11 14:13:15 bostic 12 11
c file reorg, pathnames.h, paths.h
e
s 00011/00008/00067
d D 5.5 88/06/29 22:00:45 bostic 11 10
c install approved copyright notice
e
s 00051/00042/00024
d D 5.4 88/04/21 17:17:16 bostic 10 9
c bring up to date
e
s 00002/00002/00064
d D 5.3 86/05/02 16:17:42 bloom 9 8
c  Fix problems with mailstats compiling and add to Makefile
e
s 00001/00001/00065
d D 5.2 86/05/02 11:29:23 bloom 8 7
c fix typo using sprintf instead of fprintf
e
s 00019/00000/00047
d D 5.1 85/06/07 15:58:09 dist 7 6
c Add copyright
e
s 00000/00000/00047
d D 4.1 83/07/25 20:11:21 eric 6 5
c 4.2 release version
e
s 00002/00002/00045
d D 3.5 82/03/20 16:21:01 eric 5 4
c fixes for PDP-11's
e
s 00002/00002/00045
d D 3.4 81/12/06 12:40:31 eric 4 3
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00001/00001/00046
d D 3.3 81/11/07 15:41:45 eric 3 2
c clean up to compile & work on ARPAVAX; move stat file to
c /usr/lib/sendmail.st; fix bug in syserr with error codes
e
s 00002/00000/00045
d D 3.2 81/09/12 18:00:30 eric 2 1
c print creation date
e
s 00045/00000/00000
d D 3.1 81/09/12 17:56:34 eric 1 0
c date and time created 81/09/12 17:56:34 by eric
e
u
U
t
T
I 7
/*
I 11
 * Copyright (c) 1983 Eric P. Allman
E 11
D 10
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 10
I 10
D 16
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 11
 *
D 11
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 11
 */
E 10

#ifndef lint
D 16
char copyright[] =
D 10
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 10
I 10
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 10
 All rights reserved.\n";
E 16
I 16
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 16
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10

#ifndef lint
D 10
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 10
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 10
E 7
I 1
D 9
# include "sendmail.h"
E 9

D 4
static char	SccsId[] =	"%W%	%G%";
E 4
I 4
D 9
SCCSID(%W%	%Y%	%G%);
E 9
I 9
D 10
# include "../src/sendmail.h"
# include "../src/mailstats.h"
E 10
I 10
D 17
#include <sys/file.h>
E 17
#include <sendmail.h>
#include <mailstats.h>
I 12
D 15
#include "pathnames.h"
E 15
I 15
#include <pathnames.h>
E 15
E 12
E 10
E 9
E 4

I 15
#define MNAMELEN	20	/* max length of mailer name */

E 15
D 10
/*
**  MAILSTATS -- print mail statistics.
**
**	Flags:
**		-Ffile		Name of statistics file.
**
**	Exit Status:
**		zero.
*/

E 10
main(argc, argv)
D 10
	char  **argv;
E 10
I 10
	int argc;
	char **argv;
E 10
{
D 10
	register int fd;
E 10
I 10
	extern char *optarg;
	extern int optind;
E 10
	struct statistics stat;
D 3
	char *sfile = "/usr/eric/mailstats";
E 3
I 3
D 10
	char *sfile = "/usr/lib/sendmail.st";
E 10
E 3
	register int i;
I 15
	int mno;
E 15
I 2
D 10
	extern char *ctime();
E 10
I 10
	int ch, fd;
D 15
	char *sfile, *ctime();
E 15
I 15
	char *sfile;
	char *cfile;
	FILE *cfp;
	bool mnames;
I 18
	long frmsgs = 0, frbytes = 0, tomsgs = 0, tobytes = 0;
E 18
	char mtable[MAXMAILERS][MNAMELEN+1];
	char sfilebuf[100];
	char buf[MAXLINE];
	extern char *ctime();
E 15
E 10
E 2

D 10
	fd = open(sfile, 0);
	if (fd < 0)
	{
E 10
I 10
D 12
	sfile = "/usr/lib/sendmail.st";
E 12
I 12
D 15
	sfile = _PATH_MAILSTATS;
E 12
	while ((ch = getopt(argc, argv, "f:")) != EOF)
		switch((char)ch) {
		case 'f':
E 15
I 15
	cfile = _PATH_SENDMAILCF;
	sfile = NULL;
	mnames = TRUE;
	while ((ch = getopt(argc, argv, "C:f:o")) != EOF)
	{
		switch (ch)
		{
		  case 'C':
			cfile = optarg;
			break;

		  case 'f':
E 15
			sfile = optarg;
			break;
D 15
		case '?':
		default:
			fputs("usage: mailstats [-f file]\n", stderr);
E 15
I 15

		  case 'o':
			mnames = FALSE;
			break;

		  case '?':
		  default:
  usage:
			fputs("usage: mailstats [-C cffile] [-f stfile]\n", stderr);
E 15
			exit(EX_USAGE);
		}
I 15
	}
E 15
	argc -= optind;
	argv += optind;

I 15
	if (argc != 0)
		goto usage;

	if ((cfp = fopen(cfile, "r")) == NULL)
	{
		fprintf(stderr, "mailstats: ");
		perror(cfile);
		exit(EX_NOINPUT);
	}

	mno = 0;
	(void) strcpy(mtable[mno++], "prog");
	(void) strcpy(mtable[mno++], "*file*");
	(void) strcpy(mtable[mno++], "*include*");

	while (fgets(buf, sizeof(buf), cfp) != NULL)
	{
		register char *b;
		char *s;
		register char *m;

		b = buf;
		switch (*b++)
		{
		  case 'M':		/* mailer definition */
			break;

		  case 'O':		/* option -- see if .st file */
D 19
			if (*b++ != 'S')
E 19
I 19
			if (strncasecmp(b, " StatusFile", 11) == 0 &&
			    !isalnum(b[11]))
			{
				/* new form -- find value */
				b = strchr(b, '=');
				if (b == NULL)
					continue;
				while (isspace(*++b))
					continue;
			}
			else if (*b++ != 'S')
			{
				/* something else boring */
E 19
				continue;
I 19
			}
E 19

D 19
			/* yep -- save this */
E 19
I 19
			/* this is the S or StatusFile option -- save it */
E 19
			strcpy(sfilebuf, b);
D 19
			b = strchr(sfilebuf, '\n');
			if (b != NULL)
				*b = '\0';
E 19
I 19
			b = strchr(sfilebuf, '#');
			if (b == NULL)
				b = strchr(sfilebuf, '\n');
			if (b == NULL)
				b = &sfilebuf[strlen(sfilebuf)];
			while (isspace(*--b))
				continue;
			*++b = '\0';
E 19
			if (sfile == NULL)
				sfile = sfilebuf;

		  default:
			continue;
		}

		if (mno >= MAXMAILERS)
		{
			fprintf(stderr,
				"Too many mailers defined, %d max.\n",
				MAXMAILERS);
			exit(EX_SOFTWARE);
		}
		m = mtable[mno];
		s = m + MNAMELEN;		/* is [MNAMELEN+1] */
		while (*b != ',' && !isspace(*b) && *b != '\0' && m < s)
			*m++ = *b++;
		*m = '\0';
		for (i = 0; i < mno; i++)
		{
			if (strcmp(mtable[i], mtable[mno]) == 0)
				break;
		}
		if (i == mno)
			mno++;
	}
	(void) fclose(cfp);
	for (; mno < MAXMAILERS; mno++)
		mtable[mno][0]='\0';

	if (sfile == NULL)
	{
		fprintf(stderr, "mailstats: no statistics file located\n");
		exit (EX_OSFILE);
	}

E 15
	if ((fd = open(sfile, O_RDONLY)) < 0) {
		fputs("mailstats: ", stderr);
E 10
		perror(sfile);
		exit(EX_NOINPUT);
	}
D 10
	if (read(fd, &stat, sizeof stat) != sizeof stat ||
	    stat.stat_size != sizeof stat)
	{
D 4
		sprintf(stderr, "File size change\n");
E 4
I 4
D 8
		(void) sprintf(stderr, "File size change\n");
E 8
I 8
		(void) fprintf(stderr, "File size change\n");
E 10
I 10
	if (read(fd, &stat, sizeof(stat)) != sizeof(stat) ||
D 15
	    stat.stat_size != sizeof(stat)) {
E 15
I 15
	    stat.stat_size != sizeof(stat))
	{
E 15
		fputs("mailstats: file size changed.\n", stderr);
E 10
E 8
E 4
		exit(EX_OSERR);
	}

I 2
	printf("Statistics from %s", ctime(&stat.stat_itime));
E 2
D 15
	printf(" M msgsfr bytes_from  msgsto   bytes_to\n");
E 15
I 15
	printf(" M msgsfr bytes_from  msgsto   bytes_to%s\n",
		mnames ? "  Mailer" : "");
E 15
	for (i = 0; i < MAXMAILERS; i++)
I 15
	{
E 15
D 10
	{
		if (stat.stat_nf[i] == 0 && stat.stat_nt[i] == 0)
			continue;
		printf("%2d ", i);
D 5
		printf("%6d %10dK ", stat.stat_nf[i], stat.stat_bf[i]);
		printf("%6d %10dK\n", stat.stat_nt[i], stat.stat_bt[i]);
E 5
I 5
		printf("%6ld %10ldK ", stat.stat_nf[i], stat.stat_bf[i]);
		printf("%6ld %10ldK\n", stat.stat_nt[i], stat.stat_bt[i]);
E 5
	}
E 10
I 10
		if (stat.stat_nf[i] || stat.stat_nt[i])
D 15
			printf("%2d %6ld %10ldK %6ld %10ldK\n", i,
E 15
I 15
		{
			printf("%2d %6ld %10ldK %6ld %10ldK", i,
E 15
			    stat.stat_nf[i], stat.stat_bf[i],
			    stat.stat_nt[i], stat.stat_bt[i]);
D 15
	exit(0);
E 15
I 15
			if (mnames)
				printf("  %s", mtable[i]);
			printf("\n");
I 18
			frmsgs += stat.stat_nf[i];
			frbytes += stat.stat_bf[i];
			tomsgs += stat.stat_nt[i];
			tobytes += stat.stat_bt[i];
E 18
		}
	}
I 18
	printf("========================================\n");
	printf(" T %6ld %10ldK %6ld %10ldK\n",
		frmsgs, frbytes, tomsgs, tobytes);
E 18
	exit(EX_OK);
E 15
E 10
}
E 1
