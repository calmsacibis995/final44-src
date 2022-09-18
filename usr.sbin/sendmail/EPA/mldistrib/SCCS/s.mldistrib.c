h00708
s 00017/00002/00467
d D 5.6 92/07/20 08:23:40 eric 6 5
c put in standard Berkeley header
e
s 00002/00001/00467
d D 5.5 91/12/02 15:07:09 karels 5 4
c waitpid is now in header
e
s 00146/00028/00322
d D 5.4 91/11/07 12:41:55 karels 4 3
c running since may 90
e
s 00010/00002/00340
d D 5.3 90/05/17 09:59:26 karels 3 2
c add sender to outgoing headers, deleting old; keep "received" for now
e
s 00046/00011/00296
d D 5.2 90/05/17 09:57:44 karels 2 1
c my modifications before first test on arpa
e
s 00307/00000/00000
d D 5.1 90/05/17 09:55:04 karels 1 0
c from Eric
e
u
U
t
T
I 5
D 6
/* %W% (Berkeley) %G% */
E 6
I 6
/*
 * Copyright (c) 1992 Eric P. Allman
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
char copyright[] =
"@(#) Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 6
E 5
I 4
#include <sys/types.h>
E 4
I 1
#include <stdio.h>
#include <ctype.h>
#include <sysexits.h>
#include <paths.h>

#define TRUE		1
#define FALSE		0
typedef char		BOOL;

#define CHARNULL	((char *) NULL)
I 2
#define MAXMAILOPTS	20
E 2

enum copymode {RETAIN, DISCARD};
I 2
char *myname;
I 4
int  debug;
E 4
E 2

main(argc, argv)
	int argc;
	char **argv;
{
	BOOL seen_precedence;
	register FILE *mailfp;
	enum copymode mode;
	register char *p;
	char *ml_name;
	char *ml_owner;
I 2
	char *mailer_opts[MAXMAILOPTS+1];
	char **next_opt = mailer_opts;
E 2
	char c;
	extern FILE *openmailer();
	extern char *readheadertag();
	extern void copyheader();
	extern void dropheader();
	extern void copybody();

I 2
	myname = argv[0];
	argc--, argv++;
	while (*argv[0] == '-')
	{
I 4
		if (strcmp(argv[0], "-d") == 0)
		{
			debug++;
			argv++;
			argc--;
			continue;
		}
E 4
		if (next_opt >= &mailer_opts[MAXMAILOPTS])
		{
			fprintf(stderr,
			    "%s: too many mailer options\n", myname);
			exit(EX_USAGE);
		}
		*next_opt++ = *argv++;
		argc--;
	}
	*next_opt = NULL;

E 2
	/* parse arguments */
D 2
	if (argc < 4)
E 2
I 2
	if (argc < 3)
E 2
	{
D 2
		fprintf(stderr, "Usage: mldistrib listname ownername member...\n");
E 2
I 2
		fprintf(stderr,
		    "Usage: %s [-mailopts ...] listname ownername member...\n",
		    myname);
E 2
		exit(EX_USAGE);
	}

D 2
	argv++;
E 2
	ml_name = *argv++;
	ml_owner = *argv++;

	/* consume and discard leading "From_" line */
	while ((c = fgetc(stdin)) != EOF && c != '\n')
		continue;

	/* open the connection to the mailer */
D 2
	mailfp = openmailer(argv);
E 2
I 2
D 4
	mailfp = openmailer(ml_owner, mailer_opts, argv);
E 4
I 4
	mailfp = openmailer(ml_owner, next_opt - mailer_opts, mailer_opts,
	    argc, argv);
E 4
E 2

	/* output the Resent-xxx: fields */
	fprintf(mailfp, "Resent-To:	%s\n", ml_name);
	fprintf(mailfp, "Resent-From:	%s\n", ml_owner);
I 3
	fprintf(mailfp, "Sender:	%s\n", ml_owner);
E 3

I 2
D 3
sleep(120);
E 3
E 2
	/*
	**  Consume header
	**
	**	Errors-To:	discard
	**	Precedence:	retain; mark that it has been seen
	**	Received:	discard
	**	Resent-*:	discard
	**	Return-Path:	discard
	**	Via:		discard
	**	X-Mailer:	discard
	**	others		retain
	*/

	seen_precedence = FALSE;

	while ((p = readheadertag(stdin)) != CHARNULL)
	{
		extern BOOL sameword();

		mode = RETAIN;
		switch (p[0])
		{
		  case 'e':
		  case 'E':
			if (sameword(p, "errors-to", 10))
				mode = DISCARD;
			break;

		  case 'p':
		  case 'P':
			if (sameword(p, "precedence", 11))
				seen_precedence = TRUE;
			break;

		  case 'r':
		  case 'R':
			if (sameword(p, "return-path", 12) ||
I 3
#ifdef notyet
E 3
			    sameword(p, "received", 9) ||
I 3
#endif
E 3
			    sameword(p, "resent-", 7))
				mode = DISCARD;
			break;

I 3
		  case 's':
		  case 'S':
D 4
			if sameword(p, "sender", 7))
E 4
I 4
			if (sameword(p, "sender", 7))
E 4
				mode = DISCARD;
			break;

E 3
		  case 'v':
		  case 'V':
			if (sameword(p, "via", 4))
				mode = DISCARD;
			break;

		  case 'x':
		  case 'X':
			if (sameword(p, "x-mailer", 9))
				mode = DISCARD;
			break;
		}

		switch (mode)
		{
		  case RETAIN:
			fprintf(mailfp, "%s", p);
			copyheader(stdin, mailfp);
			break;

		  case DISCARD:
			dropheader(stdin);
			break;
		}
	}

	/* if no precedence was given, make it bulk mail */
	if (!seen_precedence)
D 2
		fprintf(mailfp, "Precedence:	bulk\n");
E 2
I 2
		fprintf(mailfp, "Precedence: bulk\n");
E 2

	/* copy the body of the message */
	copybody(stdin, mailfp);

	/* clean up the connection */
D 2
	fclose(mailfp);
	exit(0);
E 2
I 2
D 4
	exit (pclose(mailfp));
E 4
I 4
	exit (my_pclose(mailfp));
E 4
E 2
}



/*
**  OPENMAILER -- open a connection to the mailer
*/

FILE *
D 2
openmailer(argv)
	char **argv;
E 2
I 2
D 4
openmailer(from, opt, argv)
E 4
I 4
openmailer(from, nopts, opts, argc, argv)
E 4
	char *from;
D 4
	char **opt, **argv;
E 4
I 4
	int nopts, argc;
	char **opts, **argv;
E 4
E 2
{
D 4
	register char *bp;
E 4
I 4
	register char **argp;
E 4
	register FILE *mailfp;
D 4
	char buf[10000];
E 4
I 4
	char **args;
	char *name;
	static char mailer[] = _PATH_SENDMAIL;
E 4
	extern int strlen();
I 4
	extern FILE *my_popen();
	extern char *malloc(), *rindex();
E 4

D 4
	bp = buf;
D 2
	(void) sprintf(bp, "%s", _PATH_SENDMAIL);
E 2
I 2
D 3
	(void) sprintf(bp, "%s -f %s", _PATH_SENDMAIL, from);
E 3
I 3
	(void) sprintf(bp, "%s -f %s -oi", _PATH_SENDMAIL, from);
E 3
E 2
	bp += strlen(bp);

I 2
	while (*opt != CHARNULL)
E 4
I 4
	/*
	 * allocate space for argv; 4 args below, a null,
	 * and options and arguments from caller.
	 */
	args = (char **) malloc((nopts + argc + 5) * sizeof(char *));
	if (args == (char **) NULL)
E 4
	{
D 4
		(void) sprintf(bp, " %s", *opt++);
		bp += strlen(bp);
		if (bp >= buf + sizeof(buf)) {
			fprintf(stderr, "%s: options list too long\n", myname);
			exit(EX_SOFTWARE);
		}
E 4
I 4
		fprintf(stderr,
		    "%s: arg list too long; can't allocate memory!?\n", myname);
		exit(EX_SOFTWARE);
E 4
	}
E 2
D 4
	while (*argv != CHARNULL)
	{
		(void) sprintf(bp, " %s", *argv++);
		bp += strlen(bp);
I 2
		if (bp >= buf + sizeof(buf)) {
			fprintf(stderr, "%s: arg list too long\n", myname);
			exit(EX_SOFTWARE);
		}
E 2
	}
E 4
I 4
	argp = args;
	if ((name = rindex(mailer, '/')) != CHARNULL)
		name++;
	else
		name = mailer;
	*argp++ = name;
	*argp++ = "-f";
	*argp++ = from;
	*argp++ = "-oi";
	bcopy((char *) opts, (char *) argp, nopts * sizeof(*opts));
	argp += nopts;
	bcopy((char *) argv, (char *) argp, argc * sizeof(*argv));
	argp += argc;
	*argp = CHARNULL;
E 4

D 4
	mailfp = popen(buf, "w");
E 4
I 4
D 6
	if (debug) {
E 6
I 6
	if (debug)
	{
E 6
		printf("| %s, args:\n", _PATH_SENDMAIL);
		for (argp = args; *argp; argp++)
			printf("  %s\n", *argp);
		printf("--------\n");
		return (stdout);
	}
	mailfp = my_popen(mailer, args, "w");
E 4
	if (mailfp == NULL)
	{
D 2
		fprintf(stderr, "mldistrib: Unable to popen %s\n", _PATH_SENDMAIL);
E 2
I 2
		fprintf(stderr, "%s: Unable to popen %s\n", myname,
		   _PATH_SENDMAIL);
E 2
		exit(EX_OSFILE);
	}

	return (mailfp);
}



/*
**  DROPHEADER -- drop a single header field
*/

void
dropheader(infp)
	register FILE *infp;
{
	register int c;

	while ((c = fgetc(infp)) != EOF)
	{
		if (c == '\n')
		{
			/* look at next character to check for continuation */
			c = fgetc(infp);
			if (c == ' ' || c == '\t')
				continue;
			if (c != EOF)
				ungetc(c, infp);
			break;
		}
	}
}



/*
**  COPYHEADER -- copy a single header field
*/

void
copyheader(infp, outfp)
	register FILE *infp;
	register FILE *outfp;
{
	register int c;

	while ((c = fgetc(infp)) != EOF)
	{
		(void) fputc(c, outfp);
		if (c == '\n')
		{
			/* look at next character to check for continuation */
			c = fgetc(infp);
			if (c == ' ' || c == '\t')
			{
				(void) fputc(c, outfp);
				continue;
			}
			if (c != EOF)
				ungetc(c, infp);
			break;
		}
	}
}



/*
**  READHEADERTAG -- read and return the name of a header field
*/

#define MAXHDRTAG	60

char *
readheadertag(infp)
	register FILE *infp;
{
	register int c;
	register char *bp;
	int i;
	static char buf[MAXHDRTAG + 1];
	extern char *strchr();

	c = fgetc(infp);
	if (c == EOF)
		return (CHARNULL);
	if (c == '\n')
	{
		ungetc(c, infp);
		return (CHARNULL);
	}

	bp = buf;
	i = sizeof buf;
	do
	{
		*bp++ = c;
		c = fgetc(infp);
	} while (--i > 0 && c != EOF && c != '\0' &&
		 strchr(" \t\n:", c) == CHARNULL);
	if (c != EOF)
		ungetc(c, infp);
	*bp++ = '\0';
	return (buf);
}



/*
**  COPYBODY -- copy the body of a message
*/

void
copybody(infp, outfp)
	register FILE *infp;
	register FILE *outfp;
{
	register int c;

	while ((c = fgetc(infp)) != EOF)
		fputc(c, outfp);
}



/*
**  SAMEWORD -- return true if two words are identical.  The first
**		word is case insignificant; the second must be lower case.
*/

BOOL
sameword(test, pat, len)
	register char *test;
	register char *pat;
	int len;
{
	for (; --len >= 0; test++, pat++)
	{
		if (*test == *pat)
			continue;
		if (isupper(*test) && tolower(*test) == *pat)
			continue;
		return (FALSE);
	}
	return (TRUE);
I 4
}



/*
 * from libc popen:
static char sccsid[] = "@(#)popen.c	5.12 (Berkeley) 4/6/90";
 *
 * This code is derived from software written by Ken Arnold and
 * published in UNIX Review, Vol. 6, No. 8.
 *
 * modified to avoid sh, be safe for setuid/setgid programs,
 * and simplified to support only one popen'ed stream.
 */


#include <sys/signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
/*
#include <stdio.h>
#include <paths.h>
*/

static pid_t pid;

FILE *
my_popen(program, args, type)
	char *program, *type;
	char **args;
{
	FILE *iop;
	int pdes[2];
	char *malloc();

	if (*type != 'r' && *type != 'w' || type[1])
		return(NULL);

	if (pipe(pdes) < 0)
		return(NULL);
	switch (pid = vfork()) {
	case -1:			/* error */
		(void)close(pdes[0]);
		(void)close(pdes[1]);
		return(NULL);
		/* NOTREACHED */
	case 0:				/* child */
		if (*type == 'r') {
			if (pdes[1] != STDOUT_FILENO) {
				(void)dup2(pdes[1], STDOUT_FILENO);
				(void)close(pdes[1]);
			}
			(void)close(pdes[0]);
		} else {
			if (pdes[0] != STDIN_FILENO) {
				(void)dup2(pdes[0], STDIN_FILENO);
				(void)close(pdes[0]);
			}
			(void)close(pdes[1]);
		}
		execv(program, args);
		_exit(127);
		/* NOTREACHED */
	}
	/* parent; assume fdopen can't fail...  */
	if (*type == 'r') {
		iop = fdopen(pdes[0], type);
		(void)close(pdes[1]);
	} else {
		iop = fdopen(pdes[1], type);
		(void)close(pdes[0]);
	}
	return (iop);
}

my_pclose(iop)
	FILE *iop;
{
	extern int errno;
	register int fdes;
	int omask;
	int pstat;
D 5
	pid_t wpid, waitpid();
E 5
I 5
	pid_t wpid;
E 5

	(void)fclose(iop);
	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
	do {
		wpid = waitpid(pid, &pstat, 0);
	} while (wpid == -1 && errno == EINTR);
	(void)sigsetmask(omask);
	pid = 0;
	return (pid == -1 ? -1 : pstat);
E 4
}
E 1
