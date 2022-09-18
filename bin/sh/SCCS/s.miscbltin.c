h46482
s 00173/00004/00188
d D 8.4 95/05/04 17:59:57 christos 6 5
c 
e
s 00066/00014/00126
d D 8.3 95/04/27 14:11:58 bostic 5 4
c make umask POSIX.2 compliant
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00001/00001/00139
d D 8.2 94/04/16 08:59:12 bostic 4 3
c bug in sh 'read' with no variable argument...
c basically: argptr isn't null (if it were, nextopt() would have problems),
c but *argptr is.  the latter is the thing to test in this case.
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00138
d D 8.1 93/05/31 15:19:46 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00139
d D 5.2 91/03/13 18:46:50 marc 2 1
c wrong source
e
s 00140/00000/00000
d D 5.1 91/03/07 20:27:42 bostic 1 0
c date and time created 91/03/07 20:27:42 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Miscelaneous builtins.
 */

I 5
#include <sys/types.h>
#include <sys/stat.h>
I 6
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <ctype.h>

E 6
E 5
#include "shell.h"
#include "options.h"
#include "var.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
#include "mystring.h"

#undef eflag

extern char **argptr;		/* argument list for builtin command */


/*
 * The read builtin.  The -e option causes backslashes to escape the
 * following character.
 *
 * This uses unbuffered input, which may be avoidable in some cases.
 */

D 6
readcmd(argc, argv)  char **argv; {
E 6
I 6
int
readcmd(argc, argv)
	int argc;
	char **argv; 
{
E 6
	char **ap;
	int backslash;
	char c;
	int eflag;
	char *prompt;
	char *ifs;
	char *p;
	int startword;
	int status;
	int i;

	eflag = 0;
	prompt = NULL;
D 2
	while ((i = nextopt("ep:")) >= 0) {
E 2
I 2
	while ((i = nextopt("ep:")) != '\0') {
E 2
		if (i == 'p')
			prompt = optarg;
		else
			eflag = 1;
	}
	if (prompt && isatty(0)) {
		out2str(prompt);
		flushall();
	}
D 4
	if ((ap = argptr) == NULL)
E 4
I 4
	if (*(ap = argptr) == NULL)
E 4
		error("arg count");
	if ((ifs = bltinlookup("IFS", 1)) == NULL)
		ifs = nullstr;
	status = 0;
	startword = 1;
	backslash = 0;
	STARTSTACKSTR(p);
	for (;;) {
		if (read(0, &c, 1) != 1) {
			status = 1;
			break;
		}
		if (c == '\0')
			continue;
		if (backslash) {
			backslash = 0;
			if (c != '\n')
				STPUTC(c, p);
			continue;
		}
		if (eflag && c == '\\') {
			backslash++;
			continue;
		}
		if (c == '\n')
			break;
		if (startword && *ifs == ' ' && strchr(ifs, c)) {
			continue;
		}
		startword = 0;
		if (backslash && c == '\\') {
			if (read(0, &c, 1) != 1) {
				status = 1;
				break;
			}
			STPUTC(c, p);
		} else if (ap[1] != NULL && strchr(ifs, c) != NULL) {
			STACKSTRNUL(p);
			setvar(*ap, stackblock(), 0);
			ap++;
			startword = 1;
			STARTSTACKSTR(p);
		} else {
			STPUTC(c, p);
		}
	}
	STACKSTRNUL(p);
	setvar(*ap, stackblock(), 0);
	while (*++ap != NULL)
		setvar(*ap, nullstr, 0);
	return status;
}



D 6
umaskcmd(argc, argv)  char **argv; {
I 5
	extern void *setmode();
	extern mode_t getmode();
E 6
I 6
int
umaskcmd(argc, argv)
	int argc;
	char **argv; 
{
E 6
	char *ap;
E 5
	int mask;
D 5
	char *p;
E 5
	int i;
I 5
	int symbolic_mode = 0;
E 5

D 5
	if ((p = argv[1]) == NULL) {
		INTOFF;
		mask = umask(0);
		umask(mask);
		INTON;
		out1fmt("%.4o\n", mask);	/* %#o might be better */
E 5
I 5
	while ((i = nextopt("S")) != '\0') {
		symbolic_mode = 1;
	}

	INTOFF;
	mask = umask(0);
	umask(mask);
	INTON;

	if ((ap = *argptr) == NULL) {
		if (symbolic_mode) {
			char u[4], g[4], o[4];

			i = 0;
			if ((mask & S_IRUSR) == 0)
				u[i++] = 'r';
			if ((mask & S_IWUSR) == 0)
				u[i++] = 'w';
			if ((mask & S_IXUSR) == 0)
				u[i++] = 'x';
			u[i] = '\0';

			i = 0;
			if ((mask & S_IRGRP) == 0)
				g[i++] = 'r';
			if ((mask & S_IWGRP) == 0)
				g[i++] = 'w';
			if ((mask & S_IXGRP) == 0)
				g[i++] = 'x';
			g[i] = '\0';

			i = 0;
			if ((mask & S_IROTH) == 0)
				o[i++] = 'r';
			if ((mask & S_IWOTH) == 0)
				o[i++] = 'w';
			if ((mask & S_IXOTH) == 0)
				o[i++] = 'x';
			o[i] = '\0';

			out1fmt("u=%s,g=%s,o=%s\n", u, g, o);
		} else {
			out1fmt("%.4o\n", mask);
		}
E 5
	} else {
D 5
		mask = 0;
		do {
			if ((unsigned)(i = *p - '0') >= 8)
				error("Illegal number: %s", argv[1]);
			mask = (mask << 3) + i;
		} while (*++p != '\0');
		umask(mask);
E 5
I 5
		if (isdigit(*ap)) {
			mask = 0;
			do {
				if (*ap >= '8' || *ap < '0')
					error("Illegal number: %s", argv[1]);
				mask = (mask << 3) + (*ap - '0');
			} while (*++ap != '\0');
			umask(mask);
		} else {
			void *set; 
			if ((set = setmode (ap)) == 0)
					error("Illegal number: %s", ap);

			mask = getmode (set, ~mask & 0777);
			umask(~mask & 0777);
I 6
		}
	}
	return 0;
}

/*
 * ulimit builtin
 *
 * This code, originally by Doug Gwyn, Doug Kingston, Eric Gisin, and
 * Michael Rendell was ripped from pdksh 5.0.8 and hacked for use with
 * ash by J.T. Conklin.
 *
 * Public domain.
 */

struct limits {
	const char *name;
	int	cmd;
	int	factor;	/* multiply by to get rlim_{cur,max} values */
	char	option;
};

static const struct limits limits[] = {
#ifdef RLIMIT_CPU
	{ "time(seconds)",		RLIMIT_CPU,	   1, 't' },
#endif
#ifdef RLIMIT_FSIZE
	{ "file(blocks)",		RLIMIT_FSIZE,	 512, 'f' },
#endif
#ifdef RLIMIT_DATA
	{ "data(kbytes)",		RLIMIT_DATA,	1024, 'd' },
#endif
#ifdef RLIMIT_STACK
	{ "stack(kbytes)",		RLIMIT_STACK,	1024, 's' },
#endif
#ifdef  RLIMIT_CORE
	{ "coredump(blocks)",		RLIMIT_CORE,	 512, 'c' },
#endif
#ifdef RLIMIT_RSS
	{ "memory(kbytes)",		RLIMIT_RSS,	1024, 'm' },
#endif
#ifdef RLIMIT_MEMLOCK
	{ "locked memory(kbytes)",	RLIMIT_MEMLOCK, 1024, 'l' },
#endif
#ifdef RLIMIT_NPROC
	{ "process(processes)",		RLIMIT_NPROC,      1, 'p' },
#endif
#ifdef RLIMIT_NOFILE
	{ "nofiles(descriptors)",	RLIMIT_NOFILE,     1, 'n' },
#endif
#ifdef RLIMIT_VMEM
	{ "vmemory(kbytes)",		RLIMIT_VMEM,	1024, 'v' },
#endif
#ifdef RLIMIT_SWAP
	{ "swap(kbytes)",		RLIMIT_SWAP,	1024, 'w' },
#endif
	{ (char *) 0,			0,		   0,  '\0' }
};

int
ulimitcmd(argc, argv)
	int argc;
	char **argv;
{
	register int	c;
	quad_t val;
	enum { SOFT = 0x1, HARD = 0x2 }
			how = SOFT | HARD;
	const struct limits	*l;
	int		set, all = 0;
	int		optc, what;
	struct rlimit	limit;

	what = 'f';
	while ((optc = nextopt("HSatfdsmcnpl")) != '\0')
		switch (optc) {
		case 'H':
			how = HARD;
			break;
		case 'S':
			how = SOFT;
			break;
		case 'a':
			all = 1;
			break;
		default:
			what = optc;
		}

	for (l = limits; l->name && l->option != what; l++)
		;
	if (!l->name)
		error("ulimit: internal error (%c)\n", what);

	set = *argptr ? 1 : 0;
	if (set) {
		char *p = *argptr;

		if (all || argptr[1])
			error("ulimit: too many arguments\n");
		if (strcmp(p, "unlimited") == 0)
			val = RLIM_INFINITY;
		else {
			val = (quad_t) 0;

			while ((c = *p++) >= '0' && c <= '9')
			{
				val = (val * 10) + (long)(c - '0');
				if (val < (quad_t) 0)
					break;
			}
			if (c)
				error("ulimit: bad number\n");
			val *= l->factor;
		}
	}
	if (all) {
		for (l = limits; l->name; l++) {
			getrlimit(l->cmd, &limit);
			if (how & SOFT)
				val = limit.rlim_cur;
			else if (how & HARD)
				val = limit.rlim_max;

			out1fmt("%-20s ", l->name);
			if (val == RLIM_INFINITY)
				out1fmt("unlimited\n");
			else
			{
				val /= l->factor;
				out1fmt("%ld\n", (long) val);
			}
		}
		return 0;
	}

	getrlimit(l->cmd, &limit);
	if (set) {
		if (how & SOFT)
			limit.rlim_cur = val;
		if (how & HARD)
			limit.rlim_max = val;
		if (setrlimit(l->cmd, &limit) < 0)
			error("ulimit: bad limit\n");
	} else {
		if (how & SOFT)
			val = limit.rlim_cur;
		else if (how & HARD)
			val = limit.rlim_max;
	}

	if (!set) {
		if (val == RLIM_INFINITY)
			out1fmt("unlimited\n");
		else
		{
			val /= l->factor;
			out1fmt("%ld\n", (long) val);
E 6
		}
E 5
	}
	return 0;
}
E 1
