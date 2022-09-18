h31075
s 00014/00001/00103
d D 4.6 91/04/17 16:55:00 bostic 6 5
c new copyright; att/bsd/shared
e
s 00007/00003/00097
d D 4.5 87/10/06 22:08:25 bostic 5 4
c '-' means stdin fix; bug report 4.3BSD/bin/86
e
s 00005/00001/00095
d D 4.4 84/12/08 15:07:42 sam 4 3
c add -l flag to force printing of lexical tokens
e
s 00000/00027/00096
d D 4.3 84/05/14 17:23:42 ralph 3 2
c get rid of logit() routine to log arguments.
e
s 00003/00001/00120
d D 4.2 83/08/11 20:09:46 sam 2 1
c standardize keyword lines
e
s 00121/00000/00000
d D 4.1 82/05/07 19:24:24 mckusick 1 0
c date and time created 82/05/07 19:24:24 by mckusick
e
u
U
t
T
I 6
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 6
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
I 6
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 6
D 4
static char sccsid[] = "%W% %G%";
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
D 6
#endif
E 6
I 6
#endif /* not lint */
E 6
E 2

#include "stdio.h"
#include "ctype.h"
#include "awk.def"
#include "awk.h"
#define TOLOWER(c)	(isupper(c) ? tolower(c) : c) /* ugh!!! */

int	dbg	= 0;
I 4
int	ldbg	= 0;
E 4
int	svflg	= 0;
int	rstflg	= 0;
int	svargc;
char	**svargv, **xargv;
extern FILE	*yyin;	/* lex input file */
char	*lexprog;	/* points to program argument if it exists */
extern	errorflag;	/* non-zero if any syntax errors; set by yyerror */

int filefd, symnum, ansfd;
char *filelist;
extern int maxsym, errno;
main(argc, argv) int argc; char *argv[]; {
	if (argc == 1)
		error(FATAL, "Usage: awk [-f source | 'cmds'] [files]");
D 3
	if (strcmp(argv[0], "a.out"))
		logit(argc, argv);
E 3
	syminit();
	while (argc > 1) {
		argc--;
		argv++;
		/* this nonsense is because gcos argument handling */
		/* folds -F into -f.  accordingly, one checks the next
		/* character after f to see if it's -f file or -Fx.
		*/
		if (argv[0][0] == '-' && TOLOWER(argv[0][1]) == 'f' && argv[0][2] == '\0') {
D 5
			yyin = fopen(argv[1], "r");
			if (yyin == NULL)
				error(FATAL, "can't open %s", argv[1]);
E 5
I 5
			if (argv[1][0] == '-' && argv[1][1] == '\0')
				yyin = stdin;
			else {
				yyin = fopen(argv[1], "r");
				if (yyin == NULL)
					error(FATAL, "can't open %s", argv[1]);
			}
E 5
			argc--;
			argv++;
			break;
		} else if (argv[0][0] == '-' && TOLOWER(argv[0][1]) == 'f') {	/* set field sep */
			if (argv[0][2] == 't')	/* special case for tab */
				**FS = '\t';
			else
				**FS = argv[0][2];
			continue;
		} else if (argv[0][0] != '-') {
			dprintf("cmds=|%s|\n", argv[0], NULL, NULL);
			yyin = NULL;
			lexprog = argv[0];
			argv[0] = argv[-1];	/* need this space */
			break;
		} else if (strcmp("-d", argv[0])==0) {
			dbg = 1;
I 4
		}
		else if (strcmp("-l", argv[0])==0) {
			ldbg = 1;
E 4
		}
		else if(strcmp("-S", argv[0]) == 0) {
			svflg = 1;
		}
		else if(strncmp("-R", argv[0], 2) == 0) {
			if(thaw(argv[0] + 2) == 0)
				rstflg = 1;
			else {
				fprintf(stderr, "not restored\n");
				exit(1);
			}
		}
	}
	if (argc <= 1) {
		argv[0][0] = '-';
		argv[0][1] = '\0';
		argc++;
		argv--;
	}
	svargc = --argc;
	svargv = ++argv;
	dprintf("svargc=%d svargv[0]=%s\n", svargc, svargv[0], NULL);
	*FILENAME = *svargv;	/* initial file name */
	if(rstflg == 0)
		yyparse();
	dprintf("errorflag=%d\n", errorflag, NULL, NULL);
	if (errorflag)
		exit(errorflag);
	if(svflg) {
		svflg = 0;
		if(freeze("awk.out") != 0)
			fprintf(stderr, "not saved\n");
		exit(0);
	}
	run();
	exit(errorflag);
D 3
}

logit(n, s) char *s[];
{	int i, tvec[2];
	FILE *f, *g;
	char buf[512];
	if ((f=fopen("/crp/pjw/awkhist/awkhist", "a"))==NULL)
		return;
	time(tvec);
	fprintf(f, "%-8s %s", getlogin(), ctime(tvec));
	for (i=0; i<n; i++)
		fprintf(f, "'%s'", s[i]);
	putc('\n', f);
	if (strcmp(s[1], "-f")) {
		fclose(f);
		return;
	}
	if ((g=fopen(s[2], "r"))==NULL) {
		fclose(f);
		return;
	}
	while ((i=fread(buf, 1, 512, g))>0)
		fwrite(buf, 1, i, f);
	fclose(f);
	fclose(g);
E 3
}

yywrap()
{
	return(1);
}
E 1
