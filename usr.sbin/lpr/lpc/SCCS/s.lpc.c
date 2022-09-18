h51562
s 00001/00002/00287
d D 8.3 95/04/28 15:41:30 tef 23 22
c Better portability to other systems.
e
s 00041/00003/00248
d D 8.2 95/04/28 13:36:49 tef 22 21
c Members of group "operator" can execute privildged commands.
e
s 00004/00004/00247
d D 8.1 93/06/06 14:00:07 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00250
d D 5.15 92/09/16 10:51:22 elan 20 19
c copyright[] -> static.
e
s 00004/00029/00247
d D 5.14 92/09/15 10:48:17 elan 19 18
c Added SCCS keywords.
e
s 00029/00004/00247
d D 5.13 92/09/01 11:08:57 elan 18 17
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00028/00013/00223
d D 5.12 92/07/21 10:28:58 bostic 17 16
c prototype lpr to fix quad's
e
s 00002/00001/00234
d D 5.11 91/03/02 14:48:32 bostic 16 15
c ANSI
e
s 00001/00011/00234
d D 5.10 90/06/01 18:44:49 bostic 15 14
c new copyright notice
e
s 00001/00001/00244
d D 5.9 90/03/20 11:09:55 tef 14 13
c prevent stupid Ambiquous Command error on null input line
e
s 00003/00002/00242
d D 5.8 89/12/18 10:51:30 bostic 13 12
c NULL pointer; bug report 2.10BSD/usr.lib/8
e
s 00001/00001/00243
d D 5.7 88/11/20 19:11:02 bostic 12 11
c use fgets, not gets
e
s 00010/00005/00234
d D 5.6 88/06/30 17:59:48 bostic 11 10
c install approved copyright notice
e
s 00010/00004/00229
d D 5.5 88/05/05 18:07:55 bostic 10 9
c written by Ralph Campbell; add Berkeley specific header
e
s 00002/00002/00231
d D 5.4 87/12/21 11:43:26 bostic 9 8
c make ANSI C compatible
e
s 00001/00001/00232
d D 5.3 87/09/14 14:52:00 bostic 8 7
c NULL dereference; bug report 4.3BSD/usr.lib/59
e
s 00002/00000/00231
d D 5.2 85/11/17 15:53:14 eric 7 6
c clean up logging
e
s 00013/00001/00218
d D 5.1 85/06/06 10:02:16 dist 6 5
c Add copyright
e
s 00000/00000/00219
d D 4.4 83/07/17 00:11:07 sam 5 4
c put sccs id's to some use
e
s 00001/00001/00218
d D 4.3 83/06/15 14:57:06 sam 4 3
c open and flock defines changed
e
s 00003/00000/00216
d D 4.2 83/05/27 11:51:51 ralph 3 1
c init global var "name" for startdaemon().
e
s 00002/00000/00216
d R 4.2 83/05/27 11:47:43 ralph 2 1
c init global variable "name" for startdaemon()
e
s 00216/00000/00000
d D 4.1 83/05/11 16:03:21 ralph 1 0
c date and time created 83/05/11 16:03:21 by ralph
e
u
U
t
T
I 6
/*
D 19
 * Copyright (c) 1983 Regents of the University of California.
E 19
I 19
D 21
 * Copyright (c) 1983 The Regents of the University of California.
E 19
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 15
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
E 15
I 15
D 18
 * %sccs.include.redist.c%
E 18
I 18
D 19
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 19
 *
D 19
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 18
E 15
E 11
E 10
 */

E 6
I 1
#ifndef lint
I 6
D 20
char copyright[] =
E 20
I 20
static char copyright[] =
E 20
D 18
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 18
I 18
D 19
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 19
I 19
D 21
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 19
E 18
 All rights reserved.\n";
E 21
I 21
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 21
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10

#ifndef lint
E 6
D 18
static char sccsid[] = "%W% (Berkeley) %G%";
E 18
I 18
D 19
static char sccsid[] = "@(#)lpc.c	5.13 (Berkeley) 8/6/92";
E 19
I 19
static char sccsid[] = "%W% (Berkeley) %G%";
E 19
E 18
D 6
#endif
E 6
I 6
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10
E 6

D 17
/*
 * lpc -- line printer control program
 */
#include <stdio.h>
E 17
I 17
#include <sys/param.h>

#include <dirent.h>
E 17
#include <signal.h>
D 17
#include <ctype.h>
E 17
#include <setjmp.h>
I 7
#include <syslog.h>
E 7
D 17

E 17
I 17
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
I 22
D 23
#include "extern.h"
#include <sys/param.h>
E 23
#include <grp.h>
I 23
#include <sys/param.h>
E 23
E 22
#include "lp.h"
E 17
#include "lpc.h"
I 17
#include "extern.h"
E 17

I 22
#ifndef LPR_OPER
#define LPR_OPER	"operator"	/* group name of lpr operators */
#endif

E 22
I 17
/*
 * lpc -- line printer control program
 */

E 17
int	fromatty;

char	cmdline[200];
int	margc;
char	*margv[20];
int	top;
D 16
int	intr();
E 16
I 16
D 17
void	intr();
E 16
struct	cmd *getcmd();
E 17

jmp_buf	toplevel;

I 17
static void		 cmdscanner __P((int));
static struct cmd	*getcmd __P((char *));
static void		 intr __P((int));
static void		 makeargv __P((void));
I 22
static int		 ingroup __P((char *));
E 22

int
E 17
main(argc, argv)
I 17
	int argc;
E 17
	char *argv[];
{
	register struct cmd *c;
I 3
D 18
	extern char *name;
E 18

	name = argv[0];
I 7
	openlog("lpd", 0, LOG_LPR);
E 7
E 3

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
D 22
		if (c->c_priv && getuid()) {
E 22
I 22
		if (c->c_priv && getuid() && ingroup(LPR_OPER) == 0) {
E 22
			printf("?Privileged command\n");
			exit(1);
		}
		(*c->c_handler)(argc, argv);
		exit(0);
	}
	fromatty = isatty(fileno(stdin));
	top = setjmp(toplevel) == 0;
	if (top)
D 4
		sigset(SIGINT, intr);
E 4
I 4
		signal(SIGINT, intr);
E 4
	for (;;) {
		cmdscanner(top);
		top = 1;
	}
}

I 16
D 17
void
E 16
intr()
E 17
I 17
static void
intr(signo)
	int signo;
E 17
{
	if (!fromatty)
		exit(0);
	longjmp(toplevel, 1);
}

/*
 * Command parser.
 */
I 17
static void
E 17
cmdscanner(top)
	int top;
{
	register struct cmd *c;
D 9
	extern struct cmd cmdtab[];
	extern int help();
E 9

	if (!top)
		putchar('\n');
	for (;;) {
		if (fromatty) {
			printf("lpc> ");
			fflush(stdout);
		}
D 12
		if (gets(cmdline) == 0)
E 12
I 12
		if (fgets(cmdline, sizeof(cmdline), stdin) == 0)
E 12
D 17
			quit();
E 17
I 17
			quit(0, NULL);
E 17
D 14
		if (cmdline[0] == 0)
E 14
I 14
		if (cmdline[0] == 0 || cmdline[0] == '\n')
E 14
			break;
		makeargv();
		c = getcmd(margv[0]);
		if (c == (struct cmd *)-1) {
			printf("?Ambiguous command\n");
			continue;
		}
		if (c == 0) {
			printf("?Invalid command\n");
			continue;
		}
D 22
		if (c->c_priv && getuid()) {
E 22
I 22
		if (c->c_priv && getuid() && ingroup(LPR_OPER) == 0) {
E 22
			printf("?Privileged command\n");
			continue;
		}
		(*c->c_handler)(margc, margv);
	}
	longjmp(toplevel, 0);
}
I 9

D 17
extern struct cmd cmdtab[];
E 9

E 17
D 22
struct cmd *
E 22
I 22
static struct cmd *
E 22
getcmd(name)
	register char *name;
{
	register char *p, *q;
	register struct cmd *c, *found;
	register int nmatches, longest;

	longest = 0;
	nmatches = 0;
	found = 0;
	for (c = cmdtab; p = c->c_name; c++) {
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
I 17
static void
E 17
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
I 17
void
E 17
help(argc, argv)
	int argc;
	char *argv[];
{
	register struct cmd *c;

	if (argc == 1) {
		register int i, j, w;
		int columns, width = 0, lines;
		extern int NCMDS;

		printf("Commands may be abbreviated.  Commands are:\n\n");
D 8
		for (c = cmdtab; c < &cmdtab[NCMDS]; c++) {
E 8
I 8
D 13
		for (c = cmdtab; c < &cmdtab[NCMDS - 1]; c++) {
E 13
I 13
		for (c = cmdtab; c->c_name; c++) {
E 13
E 8
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
D 13
				printf("%s", c->c_name);
E 13
I 13
				if (c->c_name)
					printf("%s", c->c_name);
E 13
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
			printf("%-*s\t%s\n", HELPINDENT,
				c->c_name, c->c_help);
	}
I 22
}

/*
 * return non-zero if the user is a member of the given group
 */
static int
ingroup(grname)
	char *grname;
{
	static struct group *gptr=NULL;
	static gid_t groups[NGROUPS];
	register gid_t gid;
	register int i;

	if (gptr == NULL) {
		if ((gptr = getgrnam(grname)) == NULL) {
			fprintf(stderr, "Warning: unknown group '%s'\n",
				grname);
			return(0);
		}
		if (getgroups(NGROUPS, groups) < 0) {
			perror("getgroups");
			exit(1);
		}
	}
	gid = gptr->gr_gid;
	for (i = 0; i < NGROUPS; i++)
		if (gid == groups[i])
			return(1);
	return(0);
E 22
}
E 1
