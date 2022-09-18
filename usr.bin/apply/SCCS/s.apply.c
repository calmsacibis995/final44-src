h42891
s 00003/00002/00205
d D 8.4 94/04/04 09:48:16 bostic 11 10
c don't use nargs when calculating the command length, it might be -1
c calculate the maximum command length correctly, heaven knows why
e
s 00136/00126/00071
d D 8.3 94/04/04 09:17:17 bostic 10 9
c allocate memory fast, use the user's SHELL, make -0 work, exit 0
c if everything worked, minor KNF
e
s 00171/00117/00026
d D 8.2 94/04/04 09:14:33 bostic 9 7
c non-proprietary version from Jan-Simon Pendry
e
s 00180/00116/00027
d R 8.2 94/04/04 09:08:29 bostic 8 7
c non-proprietary version from Jan-Simon Pendry
e
s 00005/00005/00138
d D 8.1 93/06/06 14:18:24 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00008/00134
d D 5.4 91/04/17 16:42:09 bostic 6 5
c new copyright; att/bsd/shared
e
s 00003/00001/00139
d D 5.3 89/05/11 09:44:47 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00139
d D 5.2 87/04/06 11:57:38 bostic 4 3
c printf wild format
e
s 00015/00001/00125
d D 5.1 85/05/31 09:06:23 dist 3 2
c Add copyright
e
s 00002/00000/00124
d D 4.2 83/02/09 15:13:48 sam 2 1
c silence warning
e
s 00124/00000/00000
d D 4.1 82/10/20 21:12:03 mckusick 1 0
c date and time created 82/10/20 21:12:03 by mckusick
e
u
U
t
T
I 1
D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";
E 3
I 3
D 6
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1983, 1993
E 9
I 9
 * Copyright (c) 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 9
 * %sccs.include.proprietary.c%
E 9
I 9
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
E 9
E 6
 */

#ifndef lint
D 7
char copyright[] =
D 6
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 6
 All rights reserved.\n";
E 7
I 7
D 9
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

#ifndef lint
E 9
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 3

I 10
#include <sys/wait.h>

#include <ctype.h>
E 10
D 6
/*%cc -s -O %
E 6
I 6
D 9
/*
E 6
 * apply - apply a command to a set of arguments
 *
 *	apply echo * == ls
 *	apply -2 cmp A1 B1 A2 B2   compares A's with B's
 *	apply "ln %1 /usr/fred/dir" *  duplicates a directory
 */
I 5
#include <paths.h>
E 9
I 9
#include <err.h>
I 10
#include <paths.h>
#include <signal.h>
E 10
E 9
E 5
#include <stdio.h>
I 9
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 9
I 5

E 5
D 9
char	*cmdp;
#define	NCHARS 512
char	cmd[512];
char	defargs=1;
#define	DEFARGCHAR	'%'
char	argchar=DEFARGCHAR;
int	nchars;
I 2
extern	char *getenv();
E 9
I 9
void	usage __P((void));
I 10
int	system __P((const char *));
E 10
E 9

I 9
int
E 9
E 2
main(argc, argv)
I 9
	int argc;
E 9
	char *argv[];
{
D 9
	register n;
	while(argc>2 && argv[1][0]=='-'){
		if(argv[1][1]=='a'){
			argchar=argv[1][2];
			if(argchar=='\0')
				argchar=DEFARGCHAR;
		} else {
			defargs = atoi(&argv[1][1]);
			if(defargs < 0)
				defargs = 1;
E 9
I 9
D 10
	int ch, clen, debug, error, n, nargs;
	char *c, *cmd, magic, *p;
E 10
I 10
	int ch, clen, debug, i, l, magic, n, nargs, rval;
	char *c, *cmd, *p, *q;
E 10

	debug = 0;
D 10
	magic = '%';		/* default magic char is `%' */
	nargs = 1;		/* default to a single arg */

	while ((ch = getopt(argc, argv, "a:d0123456789")) != EOF) {
E 10
I 10
	magic = '%';		/* Default magic char is `%'. */
	nargs = -1;
	while ((ch = getopt(argc, argv, "a:d0123456789")) != EOF)
E 10
		switch (ch) {
D 10
			case 'a':
				magic = *optarg;
				break;

			case 'd':
				debug = 1;
				break;

			case '0': case '1': case '2':
			case '3': case '4': case '5':
			case '6': case '7': case '8':
			case '9':
				nargs = optopt - '0';
				break;

			default:
				usage();
				break;
E 10
I 10
		case 'a':
			if (optarg[1] != '\0')
				errx(1,
				    "illegal magic character specification.");
			magic = optarg[0];
			break;
		case 'd':
			debug = 1;
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if (nargs != -1)
				errx(1,
				    "only one -# argument may be specified.");
			nargs = optopt - '0';
			break;
		default:
			usage();
E 10
E 9
		}
D 9
		--argc; ++argv;
E 9
D 10
	}
D 9
	if(argc<2){
D 4
		fprintf(stderr, "usage: apply [-14] [-a%] cmd arglist\n");
E 4
I 4
		fprintf(stderr, "usage: apply [-#] [-ac] cmd arglist\n");
E 4
		exit(1);
E 9
I 9

E 10
	argc -= optind;
	argv += optind;

	if (argc < 2)
		usage();

	/*
D 10
	 * The command to run is argv[0], and the args are argv[1..]
E 10
I 10
	 * The command to run is argv[0], and the args are argv[1..].
	 * Look for %digit references in the command, remembering the
	 * largest one.
E 10
	 */
D 10
	cmd = argv[0];

	/*
	 * Look for %digit references, remembering the
	 * largest value found.
	 */
	n = 0;
	for (p = cmd; (p = strchr(p, magic)) != NULL; p++) {
		p++;
		switch (*p) {
		case '1': case '2': case '3':
		case '4': case '5': case '6':
		case '7': case '8': case '9':
			if ((*p - '0') > n)
				n = *p - '0';
			break;
E 10
I 10
	for (n = 0, p = argv[0]; *p != '\0'; ++p)
		if (p[0] == magic && isdigit(p[1]) && p[1] != '0') {
			++p;
			if (p[0] - '0' > n)
				n = p[0] - '0';
E 10
		}
E 9
D 10
	}
E 10
D 9
	argc -= 2;
	cmdp = argv[1];
	argv += 2;
	while(n=docmd(argc, argv)){
		argc -= n;
		argv += n;
E 9
I 9

	/*
D 10
	 * If there were any %digit references, then
	 * simply use those, otherwise build a new command
	 * string with sufficient %digit references at
	 * the end to consume (nargs) arguments each time
	 * round the loop.
E 10
I 10
	 * If there were any %digit references, then use those, otherwise
	 * build a new command string with sufficient %digit references at
	 * the end to consume (nargs) arguments each time round the loop.
I 11
	 * Allocate enough space to hold the maximum command.
E 11
E 10
	 */
D 10
	c = malloc(sizeof("exec") + strlen(cmd) + 3 * nargs + 1);
	if (c == NULL)
E 10
I 10
D 11
	if ((cmd =
	    malloc(sizeof("exec") + strlen(argv[0]) + 3 * nargs + 1)) == NULL)
E 11
I 11
	if ((cmd = malloc(sizeof("exec ") - 1 +
	    strlen(argv[0]) + 9 * (sizeof(" %1") - 1) + 1)) == NULL)
E 11
E 10
		err(1, NULL);
		
D 10
	if (n > 0) {
		(void)sprintf(c, "exec %s", cmd);
		nargs = n;
	} else {
		int i;
E 10
I 10
	if (n == 0) {
		/* If nargs not set, default to a single argument. */
		if (nargs == -1)
			nargs = 1;
E 10

D 10
		p = c;
		p += sprintf(c, "exec %s", cmd);
E 10
I 10
		p = cmd;
		p += sprintf(cmd, "exec %s", argv[0]);
E 10
		for (i = 1; i <= nargs; i++)
			p += sprintf(p, " %c%d", magic, i);
I 10

		/*
		 * If nargs set to the special value 0, eat a single
		 * argument for each command execution.
		 */
		if (nargs == 0)
			nargs = 1;
	} else {
		(void)sprintf(cmd, "exec %s", argv[0]);
		nargs = n;
E 10
E 9
	}
D 9
}
char
addc(c)
	char c;
{
	if(nchars++>=NCHARS){
		fprintf(stderr, "apply: command too long\n");
		exit(1);
	}
	return(c);
}
char *
addarg(s, t)
	register char *s, *t;
{
	while(*t = addc(*s++))
		*t++;
	return(t);
}
docmd(argc, argv)
	char *argv[];
{
	register char *p, *q;
	register max, i;
	char gotit;
	if(argc<=0)
		return(0);
	nchars = 0;
	max = 0;
	gotit = 0;
	p = cmdp;
	q = cmd;
	while(*q = addc(*p++)){
		if(*q++!=argchar || *p<'1' || '9'<*p)
			continue;
		if((i= *p++-'1') > max)
			max = i;
		if(i>=argc){
	Toofew:
			fprintf(stderr, "apply: expecting argument(s) after `%s'\n", argv[argc-1]);
			exit(1);
E 9
I 9
D 10
	cmd = c;
E 10

	/*
D 10
	 * (argc) and (argv) are still offset by one to make it
	 * simpler to expand %digit references.
	 * At the end of the loop check for (argc) equals 1 means
	 * that all the (argv) has been consumed.
E 10
I 10
	 * Grab some space in which to build the command.  Allocate
	 * as necessary later, but no reason to build it up slowly
	 * for the normal case.
E 10
	 */
D 10
	c = 0;
	clen = 0;
	error = 0;
E 10
I 10
	if ((c = malloc(clen = 1024)) == NULL)
		err(1, NULL);
E 10

D 10
	while (argc > nargs) {
		int i, l;
		char *c, *q;

		/* find tentative value for command length */
		l = strlen(cmd);
		for (i = 0; i < nargs; i++)
E 10
I 10
	/*
	 * (argc) and (argv) are still offset by one to make it simpler to
	 * expand %digit references.  At the end of the loop check for (argc)
	 * equals 1 means that all the (argv) has been consumed.
	 */
	for (rval = 0; argc > nargs; argc -= nargs, argv += nargs) {
		/*
		 * Find a max value for the command length, and ensure
		 * there's enough space to build it.
		 */
		for (l = strlen(cmd), i = 0; i < nargs; i++)
E 10
			l += strlen(argv[i]);
I 10
		if (l > clen && (c = realloc(c, clen = l)) == NULL)
			err(1, NULL);
E 10

D 10
		/* ensure enough space to build the command */
		if (l > clen) {
			clen = l;
			c = realloc(c, clen);
			if (c == NULL)
				err(1, NULL);
E 9
		}
D 9
		q = addarg(argv[i], q-1);
		gotit++;
	}
	if(defargs!=0 && gotit==0){
		if(defargs>argc)
			goto Toofew;
		for(i=0; i<defargs; i++){
			*q++ = addc(' ');
			q = addarg(argv[i], q);
E 9
I 9

		/* expand all command references */
		for (p = cmd, q = c; *p; p++) {
			if (*p != magic) {
E 10
I 10
		/* Expand command argv references. */
		for (p = cmd, q = c; *p != '\0'; ++p)
			if (p[0] == magic && isdigit(p[1]) && p[1] != '0')
				q += sprintf(q, "%s", argv[(++p)[0] - '0']);
			else
E 10
				*q++ = *p;
D 10
				continue;
			}
			p++;
E 10

D 10
			switch (*p) {
			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
				strcpy(q, argv[*p - '0']);
				q += strlen(q);
				break;

			default:
				*q++ = magic;
				*q++ = *p;
				break;
			}
E 9
		}
I 9

		/* terminate the command string */
E 10
I 10
		/* Terminate the command string. */
E 10
		*q = '\0';

D 10
		/* run the command */
		if (debug) {
			puts(c);
		} else {
E 10
I 10
		/* Run the command. */
		if (debug)
			(void)printf("%s\n", c);
		else
E 10
			if (system(c))
D 10
				error = 1;
		}

		/*
		 * bump the arg vector.  if -0 was on the command
		 * line, then still need to skip one argument.
		 */
		if (nargs) {
			argc -= nargs;
			argv += nargs;
		} else {
			--argc;
			argv++;
		}
E 10
I 10
				rval = 1;
E 10
E 9
	}
D 9
	i = system(cmd);
	if(i == 127){
		fprintf(stderr, "apply: no shell!\n");
		exit(1);
	}
	return(max==0? (defargs==0? 1 : defargs) : max+1);
E 9
I 9

	if (argc != 1)
D 10
		errx(1, "expecting argument%s after \"%s\"",
			(nargs-argc) ? "s" : "", argv[argc-1]);
	
	exit(1);
E 10
I 10
		errx(1, "expecting additional argument%s after \"%s\"",
		    (nargs - argc) ? "s" : "", argv[argc - 1]);
	exit(rval);
E 10
E 9
}
D 9
system(s)
char *s;
E 9
I 9

I 10
/*
 * system --
 * 	Private version of system(3).  Use the user's SHELL environment
 *	variable as the shell to execute.
 */
int
system(command)
	const char *command;
{
	static char *name, *shell;
	union wait pstat;
	pid_t pid;
	int omask;
	sig_t intsave, quitsave;

	if (shell == NULL) {
		if ((shell = getenv("SHELL")) == NULL)
			shell = _PATH_BSHELL;
		if ((name = strrchr(shell, '/')) == NULL)
			name = shell;
		else
			++name;
	}
	if (!command)		/* just checking... */
		return(1);

	omask = sigblock(sigmask(SIGCHLD));
	switch(pid = vfork()) {
	case -1:			/* error */
		err(1, "fork");
	case 0:				/* child */
		(void)sigsetmask(omask);
		execl(shell, name, "-c", command, NULL);
		err(1, "%s", shell);
	}
	intsave = signal(SIGINT, SIG_IGN);
	quitsave = signal(SIGQUIT, SIG_IGN);
	pid = waitpid(pid, (int *)&pstat, 0);
	(void)sigsetmask(omask);
	(void)signal(SIGINT, intsave);
	(void)signal(SIGQUIT, quitsave);
	return(pid == -1 ? -1 : pstat.w_status);
}

E 10
void
usage()
E 9
{
D 9
	int status, pid, w;
	char *shell = getenv("SHELL");
E 9

D 9
	if ((pid = fork()) == 0) {
D 5
		execl(shell ? shell : "/bin/sh", "sh", "-c", s, 0);
E 5
I 5
		execl(shell ? shell : _PATH_BSHELL, "sh", "-c", s, 0);
E 5
		_exit(127);
	}
	if(pid == -1){
		fprintf(stderr, "apply: can't fork\n");
		exit(1);
	}
	while ((w = wait(&status)) != pid && w != -1)
		;
	if (w == -1)
		status = -1;
	return(status);
E 9
I 9
D 10
	(void)fprintf(stderr, "usage: apply [-an] [-0..9] cmd args ...\n");
E 10
I 10
	(void)fprintf(stderr,
	    "usage: apply [-a magic] [-0123456789] command arguments ...\n");
E 10
	exit(1);
E 9
}
E 1
