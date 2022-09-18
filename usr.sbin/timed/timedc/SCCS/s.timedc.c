h45659
s 00005/00005/00230
d D 8.1 93/06/06 14:09:36 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00235
d D 5.2 93/06/03 17:30:13 bostic 15 14
c lint
e
s 00036/00039/00201
d D 5.1 93/05/11 11:49:36 bostic 14 13
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00002/00001/00238
d D 2.10 91/03/05 07:07:11 bostic 13 12
c ANSI
e
s 00001/00011/00238
d D 2.9 90/06/01 19:03:23 bostic 12 11
c new copyright notice
e
s 00001/00001/00248
d D 2.8 89/12/14 12:21:53 bostic 11 10
c typo
e
s 00001/00001/00248
d D 2.7 88/11/20 19:10:06 bostic 10 9
c use fgets(), not gets()
e
s 00010/00005/00239
d D 2.6 88/06/18 14:08:29 bostic 9 8
c install approved copyright notice
e
s 00002/00001/00242
d D 2.5 87/12/26 14:55:00 bostic 8 7
c fix external declarations for ANSI C
e
s 00010/00004/00233
d D 2.4 87/12/23 14:30:22 bostic 7 6
c append Berkeley header; NASA wants a copy
e
s 00004/00000/00233
d D 2.3 86/06/05 14:10:10 bloom 6 5
c close security hole allowing anyone to give restricted commands
e
s 00003/00001/00230
d D 2.2 86/01/24 09:11:31 bloom 5 4
c purge extra null entry from table and correct search in getcmd (sam@okeeffe)
e
s 00000/00000/00231
d D 2.1 85/12/10 13:07:46 bloom 4 3
c Multi network support
e
s 00001/00000/00230
d D 1.3 85/09/18 12:24:49 bloom 3 2
c need to include syslog.h to use openlog() eric
e
s 00002/00000/00228
d D 1.2 85/09/17 21:04:45 eric 2 1
c facilities in syslog
e
s 00228/00000/00000
d D 1.1 85/06/22 22:08:02 gusella 1 0
c date and time created 85/06/22 22:08:02 by gusella
e
u
U
t
T
I 1
D 14
/*
 * Copyright (c) 1983 Regents of the University of California.
E 14
I 14
/*-
D 16
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 14
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 9
E 7
 */

#ifndef lint
D 16
char copyright[] =
D 14
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 14
I 14
"%Z% Copyright (c) 1985, 1993 The Regents of the University of California.\n\
E 14
 All rights reserved.\n";
E 16
I 16
static char copyright[] =
"%Z% Copyright (c) 1985, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 16
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

I 14
#ifdef sgi
#ident "$Revision: 1.6 $"
#endif

E 14
#include "timedc.h"
I 14
#include <strings.h>
E 14
#include <signal.h>
#include <ctype.h>
#include <setjmp.h>
I 14
#include <unistd.h>
#include <stdlib.h>
E 14
I 3
#include <syslog.h>
E 3

D 14
int	top;
E 14
I 14
int trace = 0;
FILE *fd = 0;
E 14
int	margc;
int	fromatty;
char	*margv[20];
char	cmdline[200];
jmp_buf	toplevel;
D 13
int	intr();
E 13
I 13
D 14
void	intr();
E 13
int priv_resources();
struct	cmd *getcmd();
E 14
I 14
static struct cmd *getcmd __P((char *));
E 14

D 14

E 14
I 14
int
E 14
main(argc, argv)
I 14
	int argc;
E 14
	char *argv[];
{
	register struct cmd *c;

I 2
	openlog("timedc", LOG_ODELAY, LOG_AUTH);

E 2
	/*
	 * security dictates!
	 */
	if (priv_resources() < 0) {
D 11
		fprintf(stderr, "Could not get priviledged resources\n");
E 11
I 11
		fprintf(stderr, "Could not get privileged resources\n");
E 11
		exit(1);
	}
	(void) setuid(getuid());

	if (--argc > 0) {
		c = getcmd(*++argv);
		if (c == (struct cmd *)-1) {
			printf("?Ambiguous command\n");
			exit(1);
		}
		if (c == 0) {
			printf("?Invalid command\n");
			exit(1);
		}
I 6
		if (c->c_priv && getuid()) {
			printf("?Privileged command\n");
			exit(1);
		}
E 6
		(*c->c_handler)(argc, argv);
		exit(0);
	}
D 14
	fromatty = isatty(fileno(stdin));
	top = setjmp(toplevel) == 0;
	if (top)
		(void) signal(SIGINT, intr);
	for (;;) {
		cmdscanner(top);
		top = 1;
	}
}
E 14

I 13
D 14
void
E 13
intr()
{
	if (!fromatty)
		exit(0);
	longjmp(toplevel, 1);
}

/*
 * Command parser.
 */
cmdscanner(top)
	int top;
{
	register struct cmd *c;
D 8
	extern struct cmd cmdtab[];
E 8
	extern int help();

	if (!top)
E 14
I 14
	fromatty = isatty(fileno(stdin));
	if (setjmp(toplevel))
E 14
		putchar('\n');
I 14
	(void) signal(SIGINT, intr);
E 14
	for (;;) {
		if (fromatty) {
			printf("timedc> ");
			(void) fflush(stdout);
		}
D 10
		if (gets(cmdline) == 0)
E 10
I 10
		if (fgets(cmdline, sizeof(cmdline), stdin) == 0)
E 10
			quit();
		if (cmdline[0] == 0)
			break;
		makeargv();
I 14
		if (margv[0] == 0)
			continue;
E 14
		c = getcmd(margv[0]);
		if (c == (struct cmd *)-1) {
			printf("?Ambiguous command\n");
			continue;
		}
		if (c == 0) {
			printf("?Invalid command\n");
			continue;
		}
		if (c->c_priv && getuid()) {
			printf("?Privileged command\n");
			continue;
		}
		(*c->c_handler)(margc, margv);
	}
D 14
	longjmp(toplevel, 0);
E 14
I 14
	return 0;
E 14
}

D 14
struct cmd *
E 14
I 14
void
intr(signo)
	int signo;
{
	if (!fromatty)
		exit(0);
	longjmp(toplevel, 1);
}


static struct cmd *
E 14
getcmd(name)
D 14
	register char *name;
E 14
I 14
	char *name;
E 14
{
	register char *p, *q;
	register struct cmd *c, *found;
	register int nmatches, longest;
I 8
D 15
	extern struct cmd cmdtab[];
E 15
E 8
I 5
	extern int NCMDS;
E 5

	longest = 0;
	nmatches = 0;
	found = 0;
D 5
	for (c = cmdtab; p = c->c_name; c++) {
E 5
I 5
	for (c = cmdtab; c < &cmdtab[NCMDS]; c++) {
		p = c->c_name;
E 5
		for (q = name; *q == *p++; q++)
			if (*q == 0)		/* exact match? */
				return(c);
		if (!*q) {			/* the name was a prefix */
			if (q - name > longest) {
				longest = q - name;
				nmatches = 1;
				found = c;
			} else if (q - name == longest)
				nmatches++;
		}
	}
	if (nmatches > 1)
		return((struct cmd *)-1);
	return(found);
}

/*
 * Slice a string up into argc/argv.
 */
I 14
void
E 14
makeargv()
{
	register char *cp;
	register char **argp = margv;

	margc = 0;
	for (cp = cmdline; *cp;) {
		while (isspace(*cp))
			cp++;
		if (*cp == '\0')
			break;
		*argp++ = cp;
		margc += 1;
		while (*cp != '\0' && !isspace(*cp))
			cp++;
		if (*cp == '\0')
			break;
		*cp++ = '\0';
	}
	*argp++ = 0;
}

#define HELPINDENT (sizeof ("directory"))

/*
 * Help command.
 */
I 14
void
E 14
help(argc, argv)
	int argc;
	char *argv[];
{
	register struct cmd *c;
I 8
D 15
	extern struct cmd cmdtab[];
E 15
E 8

	if (argc == 1) {
		register int i, j, w;
		int columns, width = 0, lines;
		extern int NCMDS;

		printf("Commands may be abbreviated.  Commands are:\n\n");
		for (c = cmdtab; c < &cmdtab[NCMDS]; c++) {
			int len = strlen(c->c_name);

			if (len > width)
				width = len;
		}
		width = (width + 8) &~ 7;
		columns = 80 / width;
		if (columns == 0)
			columns = 1;
		lines = (NCMDS + columns - 1) / columns;
		for (i = 0; i < lines; i++) {
			for (j = 0; j < columns; j++) {
				c = cmdtab + j * lines + i;
				printf("%s", c->c_name);
				if (c + lines >= &cmdtab[NCMDS]) {
					printf("\n");
					break;
				}
				w = strlen(c->c_name);
				while (w < width) {
					w = (w + 8) &~ 7;
					putchar('\t');
				}
			}
		}
		return;
	}
	while (--argc > 0) {
		register char *arg;
		arg = *++argv;
		c = getcmd(arg);
		if (c == (struct cmd *)-1)
			printf("?Ambiguous help command %s\n", arg);
		else if (c == (struct cmd *)0)
			printf("?Invalid help command %s\n", arg);
		else
D 14
			printf("%-*s\t%s\n", HELPINDENT,
E 14
I 14
			printf("%-*s\t%s\n", (int)HELPINDENT,
E 14
				c->c_name, c->c_help);
	}
}
E 1
