h30302
s 00037/00018/00389
d D 8.2 95/05/04 18:00:03 christos 7 6
c 
e
s 00002/00002/00405
d D 8.1 93/05/31 15:20:07 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00406
d D 5.5 92/07/16 16:34:04 marc 5 4
c shift n>$# is error
e
s 00066/00023/00341
d D 5.4 92/07/15 09:13:21 marc 4 3
c support set -o options
e
s 00002/00000/00362
d D 5.3 92/06/24 16:21:15 marc 3 2
c history
e
s 00017/00009/00345
d D 5.2 91/03/13 19:22:31 marc 2 1
c wrong source
e
s 00354/00000/00000
d D 5.1 91/03/07 20:27:49 bostic 1 0
c date and time created 91/03/07 20:27:49 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 7
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

E 7
#include "shell.h"
#define DEFINE_OPTIONS
#include "options.h"
#undef DEFINE_OPTIONS
#include "nodes.h"	/* for other header files */
#include "eval.h"
#include "jobs.h"
#include "input.h"
#include "output.h"
#include "trap.h"
#include "var.h"
#include "memalloc.h"
#include "error.h"
#include "mystring.h"
I 7
#ifndef NO_HISTORY
#include "myhistedit.h"
#endif
E 7

char *arg0;			/* value of $0 */
struct shparam shellparam;	/* current positional parameters */
char **argptr;			/* argument list for builtin commands */
char *optarg;			/* set by nextopt (like getopt) */
char *optptr;			/* used by nextopt */

char *minusc;			/* argument to -c option */


D 7
#ifdef __STDC__
STATIC void options(int);
STATIC void setoption(int, int);
I 4
STATIC void minus_o(char *, int);
E 4
#else
STATIC void options();
STATIC void setoption();
I 4
STATIC void minus_o();
E 4
#endif
E 7
I 7
STATIC void options __P((int));
STATIC void minus_o __P((char *, int));
STATIC void setoption __P((int, int));
E 7


D 7

E 7
/*
 * Process the shell command line arguments.
 */

void
procargs(argc, argv)
I 7
	int argc;
E 7
	char **argv;
D 7
	{
E 7
I 7
{
E 7
D 4
	char *p;
E 4
I 4
	int i;
E 4

	argptr = argv;
	if (argc > 0)
		argptr++;
D 4
	for (p = optval ; p < optval + sizeof optval - 1 ; p++)
		*p = 2;
E 4
I 4
	for (i = 0; i < NOPTS; i++)
		optlist[i].val = 2;
E 4
	options(1);
	if (*argptr == NULL && minusc == NULL)
		sflag = 1;
	if (iflag == 2 && sflag == 1 && isatty(0) && isatty(1))
		iflag = 1;
D 4
	if (jflag == 2)
		jflag = iflag;
	for (p = optval ; p < optval + sizeof optval - 1 ; p++)
		if (*p == 2)
			*p = 0;
E 4
I 4
	if (mflag == 2)
		mflag = iflag;
	for (i = 0; i < NOPTS; i++)
		if (optlist[i].val == 2)
			optlist[i].val = 0;
E 4
	arg0 = argv[0];
	if (sflag == 0 && minusc == NULL) {
		commandname = arg0 = *argptr++;
		setinputfile(commandname, 0);
	}
	shellparam.p = argptr;
	/* assert(shellparam.malloc == 0 && shellparam.nparam == 0); */
	while (*argptr) {
		shellparam.nparam++;
		argptr++;
	}
I 4
	optschanged();
}


D 7
optschanged() {
E 7
I 7
void
optschanged()
{
E 7
E 4
	setinteractive(iflag);
I 7
#ifndef NO_HISTORY
E 7
I 3
	histedit();
I 7
#endif
E 7
E 3
D 4
	setjobctl(jflag);
E 4
I 4
	setjobctl(mflag);
E 4
}

D 4


E 4
/*
 * Process shell options.  The global variable argptr contains a pointer
 * to the argument list; we advance it past the options.
 */

STATIC void
D 7
options(cmdline) {
E 7
I 7
options(cmdline) 
	int cmdline;
{
E 7
	register char *p;
	int val;
	int c;

D 2
	minusc = NULL;
E 2
I 2
	if (cmdline)
		minusc = NULL;
E 2
	while ((p = *argptr) != NULL) {
		argptr++;
		if ((c = *p++) == '-') {
			val = 1;
D 2
			if (p[0] == '\0' || p[0] == '-' && p[1] == '\0')
E 2
I 2
D 7
                        if (p[0] == '\0' || p[0] == '-' && p[1] == '\0') {
E 7
I 7
                        if (p[0] == '\0' || (p[0] == '-' && p[1] == '\0')) {
E 7
                                if (!cmdline) {
                                        /* "-" means turn off -x and -v */
                                        if (p[0] == '\0')
                                                xflag = vflag = 0;
                                        /* "--" means reset params */
                                        else if (*argptr == NULL)
D 7
                                                setparam(argptr);
E 7
I 7
						setparam(argptr);
E 7
                                }
E 2
				break;	  /* "-" or  "--" terminates options */
I 2
			}
E 2
		} else if (c == '+') {
			val = 0;
		} else {
			argptr--;
			break;
		}
		while ((c = *p++) != '\0') {
			if (c == 'c' && cmdline) {
				char *q;
D 2
#ifdef NOHACK
E 2
I 2
#ifdef NOHACK	/* removing this code allows sh -ce 'foo' for compat */
E 2
				if (*p == '\0')
#endif
					q = *argptr++;
				if (q == NULL || minusc != NULL)
					error("Bad -c option");
				minusc = q;
#ifdef NOHACK
				break;
#endif
I 4
			} else if (c == 'o') {
				minus_o(*argptr, val);
				if (*argptr)
					argptr++;
E 4
			} else {
				setoption(c, val);
			}
		}
D 4
		if (! cmdline)
			break;
E 4
	}
}

I 4
STATIC void
minus_o(name, val)
	char *name;
	int val;
{
	int i;
E 4

I 4
	if (name == NULL) {
		out1str("Current option settings\n");
		for (i = 0; i < NOPTS; i++)
			out1fmt("%-16s%s\n", optlist[i].name,
				optlist[i].val ? "on" : "off");
	} else {
		for (i = 0; i < NOPTS; i++)
			if (equal(name, optlist[i].name)) {
				setoption(optlist[i].letter, val);
				return;
			}
		error("Illegal option -o %s", name);
	}
}
			

E 4
STATIC void
setoption(flag, val)
	char flag;
	int val;
	{
D 4
	register char *p;
E 4
I 4
	int i;
E 4

D 4
	if ((p = strchr(optchar, flag)) == NULL)
		error("Illegal option -%c", flag);
	optval[p - optchar] = val;
E 4
I 4
	for (i = 0; i < NOPTS; i++)
		if (optlist[i].letter == flag) {
			optlist[i].val = val;
			if (val) {
				/* #%$ hack for ksh semantics */
				if (flag == 'V')
					Eflag = 0;
				else if (flag == 'E')
					Vflag = 0;
			}
			return;
		}
	error("Illegal option -%c", flag);
E 4
}



#ifdef mkinit
INCLUDE "options.h"

SHELLPROC {
D 4
	char *p;
E 4
I 4
	int i;
E 4

D 4
	for (p = optval ; p < optval + sizeof optval ; p++)
		*p = 0;
E 4
I 4
	for (i = 0; i < NOPTS; i++)
		optlist[i].val = 0;
	optschanged();

E 4
}
#endif


/*
 * Set the shell parameters.
 */

void
setparam(argv)
	char **argv;
	{
	char **newparam;
	char **ap;
	int nparam;

	for (nparam = 0 ; argv[nparam] ; nparam++);
	ap = newparam = ckmalloc((nparam + 1) * sizeof *ap);
	while (*argv) {
		*ap++ = savestr(*argv++);
	}
	*ap = NULL;
	freeparam(&shellparam);
	shellparam.malloc = 1;
	shellparam.nparam = nparam;
	shellparam.p = newparam;
	shellparam.optnext = NULL;
}


/*
 * Free the list of positional parameters.
 */

void
freeparam(param)
	struct shparam *param;
	{
	char **ap;

	if (param->malloc) {
		for (ap = param->p ; *ap ; ap++)
			ckfree(*ap);
		ckfree(param->p);
	}
}



/*
 * The shift builtin command.
 */

D 7
shiftcmd(argc, argv)  char **argv; {
E 7
I 7
int
shiftcmd(argc, argv)
	int argc;
	char **argv; 
{
E 7
	int n;
	char **ap1, **ap2;

	n = 1;
	if (argc > 1)
		n = number(argv[1]);
	if (n > shellparam.nparam)
D 5
		n = shellparam.nparam;
E 5
I 5
		error("can't shift that many");
E 5
	INTOFF;
	shellparam.nparam -= n;
	for (ap1 = shellparam.p ; --n >= 0 ; ap1++) {
		if (shellparam.malloc)
			ckfree(*ap1);
	}
	ap2 = shellparam.p;
	while ((*ap2++ = *ap1++) != NULL);
	shellparam.optnext = NULL;
	INTON;
	return 0;
}



/*
 * The set command builtin.
 */

D 7
setcmd(argc, argv)  char **argv; {
E 7
I 7
int
setcmd(argc, argv)
	int argc;
	char **argv; 
{
E 7
	if (argc == 1)
		return showvarscmd(argc, argv);
	INTOFF;
	options(0);
D 4
	setinteractive(iflag);
I 3
	histedit();
E 3
	setjobctl(jflag);
E 4
I 4
	optschanged();
E 4
	if (*argptr != NULL) {
		setparam(argptr);
	}
	INTON;
	return 0;
}


/*
 * The getopts builtin.  Shellparam.optnext points to the next argument
 * to be processed.  Shellparam.optptr points to the next character to
 * be processed in the current argument.  If shellparam.optnext is NULL,
 * then it's the first time getopts has been called.
 */

D 7
getoptscmd(argc, argv)  char **argv; {
E 7
I 7
int
getoptscmd(argc, argv)
	int argc;
	char **argv; 
{
E 7
	register char *p, *q;
	char c;
	char s[10];

	if (argc != 3)
		error("Usage: getopts optstring var");
	if (shellparam.optnext == NULL) {
		shellparam.optnext = shellparam.p;
		shellparam.optptr = NULL;
	}
	if ((p = shellparam.optptr) == NULL || *p == '\0') {
		p = *shellparam.optnext;
		if (p == NULL || *p != '-' || *++p == '\0') {
atend:
			fmtstr(s, 10, "%d", shellparam.optnext - shellparam.p + 1);
			setvar("OPTIND", s, 0);
			shellparam.optnext = NULL;
			return 1;
		}
		shellparam.optnext++;
		if (p[0] == '-' && p[1] == '\0')	/* check for "--" */
			goto atend;
	}
	c = *p++;
	for (q = argv[1] ; *q != c ; ) {
		if (*q == '\0') {
			out1fmt("Illegal option -%c\n", c);
			c = '?';
			goto out;
		}
		if (*++q == ':')
			q++;
	}
	if (*++q == ':') {
		if (*p == '\0' && (p = *shellparam.optnext) == NULL) {
			out1fmt("No arg for -%c option\n", c);
			c = '?';
			goto out;
		}
		shellparam.optnext++;
		setvar("OPTARG", p, 0);
		p = NULL;
	}
out:
	shellparam.optptr = p;
	s[0] = c;
	s[1] = '\0';
	setvar(argv[2], s, 0);
	return 0;
}

D 2

E 2
/*
I 4
 * XXX - should get rid of.  have all builtins use getopt(3).  the
 * library getopt must have the BSD extension static variable "optreset"
 * otherwise it can't be used within the shell safely.
 *
E 4
 * Standard option processing (a la getopt) for builtin routines.  The
 * only argument that is passed to nextopt is the option string; the
D 2
 * other arguments are unnecessary.  It return the character, or -1 on
 * end of input.  This routine assumes that all characters in optstring
 * are positive.
E 2
I 2
 * other arguments are unnecessary.  It return the character, or '\0' on
 * end of input.
E 2
 */

int
nextopt(optstring)
	char *optstring;
	{
	register char *p, *q;
	char c;

	if ((p = optptr) == NULL || *p == '\0') {
		p = *argptr;
		if (p == NULL || *p != '-' || *++p == '\0')
D 2
			return -1;
E 2
I 2
			return '\0';
E 2
		argptr++;
		if (p[0] == '-' && p[1] == '\0')	/* check for "--" */
D 2
			return -1;
E 2
I 2
			return '\0';
E 2
	}
	c = *p++;
	for (q = optstring ; *q != c ; ) {
		if (*q == '\0')
			error("Illegal option -%c", c);
		if (*++q == ':')
			q++;
	}
	if (*++q == ':') {
		if (*p == '\0' && (p = *argptr++) == NULL)
			error("No arg for -%c option", c);
		optarg = p;
		p = NULL;
	}
	optptr = p;
	return c;
}
E 1
