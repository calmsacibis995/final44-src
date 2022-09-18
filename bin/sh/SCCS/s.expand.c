h65023
s 00002/00002/01305
d D 8.5 95/05/14 22:37:33 christos 15 14
c fixed bug 
c false
e
s 00071/00064/01236
d D 8.4 95/05/04 17:59:42 christos 14 13
c 
e
s 00206/00040/01094
d D 8.3 95/04/28 17:16:11 bostic 13 12
c add the documented in the manual but not implemented variable
c expansions.
c From: Christos Zoulas <christos@deshaw.com>
e
s 00002/00000/01132
d D 8.2 93/10/22 09:42:14 torek 12 11
c fix for nested backquote expansion; test case, eg, echo `echo ${FOO=\`bar\`}`
e
s 00002/00002/01130
d D 8.1 93/05/31 15:19:04 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/01131
d D 5.10 93/04/20 03:49:56 torek 10 9
c set $? from backquote expansion: test case is `(exit 2)`;echo $?
e
s 00014/00001/01118
d D 5.9 92/07/31 14:56:24 marc 9 8
c tilde wasen't being expanded directly after the "=" in assignments
e
s 00031/00023/01088
d D 5.8 92/07/30 15:42:24 marc 8 7
c fix bug where quoted pattern to case(1) wasen't being quoted
e
s 00005/00002/01106
d D 5.7 92/07/15 15:05:05 marc 7 6
c didn't get the hack right.  REPLACE WITH FNMATCH...
e
s 00010/00013/01098
d D 5.6 92/07/15 10:04:41 marc 6 5
c new options, remove -z, ckmalloc(1024) bug (*NOT* big enough) - hack
e
s 00004/00002/01107
d D 5.5 92/07/10 16:06:06 marc 5 4
c remove zflag - nonstandard
e
s 00025/00017/01084
d D 5.4 92/06/23 18:00:54 marc 4 3
c minor cleanups
e
s 00085/00106/01016
d D 5.3 92/04/30 15:09:30 marc 3 2
c add tilde -- remove UDIR
e
s 00045/00001/01077
d D 5.2 92/04/27 16:12:03 marc 2 1
c arithmetic
e
s 01078/00000/00000
d D 5.1 91/03/07 20:27:29 bostic 1 0
c date and time created 91/03/07 20:27:29 by bostic
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 14
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>

E 14
/*
 * Routines to expand arguments to commands.  We have to deal with
 * backquotes, shell variables, and file metacharacters.
 */

#include "shell.h"
#include "main.h"
#include "nodes.h"
#include "eval.h"
#include "expand.h"
#include "syntax.h"
#include "parser.h"
#include "jobs.h"
#include "options.h"
#include "var.h"
#include "input.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
#include "mystring.h"
D 14
#include <sys/types.h>
I 2
#include <sys/time.h>
E 2
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
I 3
#include <pwd.h>
E 14
I 14
#include "arith.h"
#include "show.h"
E 14
E 3

/*
 * Structure specifying which parts of the string should be searched
 * for IFS characters.
 */

struct ifsregion {
	struct ifsregion *next;	/* next region in list */
	int begoff;		/* offset of start of region */
	int endoff;		/* offset of end of region */
	int nulonly;		/* search for nul bytes only */
};


char *expdest;			/* output of current string */
struct nodelist *argbackq;	/* list of back quote expressions */
struct ifsregion ifsfirst;	/* first struct in list of ifs regions */
struct ifsregion *ifslastp;	/* last struct in list */
struct arglist exparg;		/* holds expanded arg list */
D 3
#if UDIR
/*
 * Set if the last argument processed had /u/logname expanded.  This
 * variable is read by the cd command.
 */
int didudir;
#endif
E 3

D 14
#ifdef __STDC__
STATIC void argstr(char *, int);
STATIC void expbackq(union node *, int, int);
I 13
STATIC int  subevalvar(char *, char *, int, int, int);
E 13
STATIC char *evalvar(char *, int);
STATIC int varisset(int);
STATIC void varvalue(int, int, int);
STATIC void recordregion(int, int, int);
STATIC void ifsbreakup(char *, struct arglist *);
D 3
STATIC void expandmeta(struct strlist *);
E 3
I 3
STATIC void expandmeta(struct strlist *, int);
E 3
STATIC void expmeta(char *, char *);
I 8
STATIC void expari(int);
E 8
STATIC void addfname(char *);
STATIC struct strlist *expsort(struct strlist *);
STATIC struct strlist *msort(struct strlist *, int);
STATIC int pmatch(char *, char *);
I 3
STATIC char *exptilde(char *, int);
I 13
STATIC char *cvtnum(int, char *);
E 13
E 3
#else
STATIC void argstr();
STATIC void expbackq();
I 13
STATIC int subevalvar();
E 13
STATIC char *evalvar();
STATIC int varisset();
STATIC void varvalue();
STATIC void recordregion();
STATIC void ifsbreakup();
STATIC void expandmeta();
STATIC void expmeta();
I 8
STATIC void expari();
E 8
STATIC void addfname();
STATIC struct strlist *expsort();
STATIC struct strlist *msort();
STATIC int pmatch();
I 3
STATIC char *exptilde();
I 13
STATIC char *cvtnum();
E 13
E 3
#endif
E 14
I 14
STATIC void argstr __P((char *, int));
STATIC char *exptilde __P((char *, int));
STATIC void expbackq __P((union node *, int, int));
STATIC int subevalvar __P((char *, char *, int, int, int));
STATIC char *evalvar __P((char *, int));
STATIC int varisset __P((int));
STATIC void varvalue __P((int, int, int));
STATIC void recordregion __P((int, int, int));
STATIC void ifsbreakup __P((char *, struct arglist *));
STATIC void expandmeta __P((struct strlist *, int));
STATIC void expmeta __P((char *, char *));
STATIC void addfname __P((char *));
STATIC struct strlist *expsort __P((struct strlist *));
STATIC struct strlist *msort __P((struct strlist *, int));
STATIC int pmatch __P((char *, char *));
STATIC char *cvtnum __P((int, char *));
E 14
D 3
#if UDIR
#ifdef __STDC__
STATIC char *expudir(char *);
#else
STATIC char *expudir();
#endif
#endif /* UDIR */
E 3

D 3


E 3
/*
 * Expand shell variables and backquotes inside a here document.
 */

void
expandhere(arg, fd)
	union node *arg;	/* the document */
	int fd;			/* where to write the expanded version */
	{
	herefd = fd;
	expandarg(arg, (struct arglist *)NULL, 0);
	xwrite(fd, stackblock(), expdest - stackblock());
}


/*
 * Perform variable substitution and command substitution on an argument,
D 8
 * placing the resulting list of arguments in arglist.  If full is true,
E 8
I 8
 * placing the resulting list of arguments in arglist.  If EXP_FULL is true,
E 8
 * perform splitting and file name expansion.  When arglist is NULL, perform
 * here document expansion.
 */

void
D 3
expandarg(arg, arglist, full)
E 3
I 3
expandarg(arg, arglist, flag)
E 3
	union node *arg;
	struct arglist *arglist;
D 14
	{
E 14
I 14
	int flag;
{
E 14
	struct strlist *sp;
	char *p;

D 3
#if UDIR
	didudir = 0;
#endif
E 3
	argbackq = arg->narg.backquote;
	STARTSTACKSTR(expdest);
	ifsfirst.next = NULL;
	ifslastp = NULL;
D 3
	argstr(arg->narg.text, full);
E 3
I 3
	argstr(arg->narg.text, flag);
E 3
D 4
	if (arglist == NULL)
E 4
I 4
	if (arglist == NULL) {
E 4
		return;			/* here document expanded */
I 4
	}
E 4
	STPUTC('\0', expdest);
	p = grabstackstr(expdest);
	exparg.lastp = &exparg.list;
D 3
	if (full) {
E 3
I 3
	/*
	 * TODO - EXP_REDIR
	 */
	if (flag & EXP_FULL) {
E 3
		ifsbreakup(p, &exparg);
		*exparg.lastp = NULL;
		exparg.lastp = &exparg.list;
D 3
		expandmeta(exparg.list);
E 3
I 3
		expandmeta(exparg.list, flag);
E 3
	} else {
I 4
		if (flag & EXP_REDIR) /*XXX - for now, just remove escapes */
			rmescapes(p);
E 4
		sp = (struct strlist *)stalloc(sizeof (struct strlist));
		sp->text = p;
		*exparg.lastp = sp;
		exparg.lastp = &sp->next;
	}
	while (ifsfirst.next != NULL) {
		struct ifsregion *ifsp;
		INTOFF;
		ifsp = ifsfirst.next->next;
		ckfree(ifsfirst.next);
		ifsfirst.next = ifsp;
		INTON;
	}
	*exparg.lastp = NULL;
	if (exparg.list) {
		*arglist->lastp = exparg.list;
		arglist->lastp = exparg.lastp;
	}
}



/*
D 8
 * Perform variable and command substitution.  If full is set, output CTLESC
 * characters to allow for further processing.  If full is not set, treat
E 8
I 8
 * Perform variable and command substitution.  If EXP_FULL is set, output CTLESC
 * characters to allow for further processing.  Otherwise treat
E 8
 * $@ like $* since no splitting will be performed.
 */

STATIC void
D 3
argstr(p, full)
E 3
I 3
argstr(p, flag)
E 3
	register char *p;
D 14
	{
E 14
I 14
	int flag;
{
E 14
D 8
	char c;
I 2
	int sawari = 0;
I 3
	int full = flag & EXP_FULL;  /* is there a later stage? */
	int vartilde = flag & EXP_VARTILDE;
E 8
I 8
	register char c;
	int quotes = flag & (EXP_FULL | EXP_CASE);	/* do CTLESC */
I 9
	int firsteq = 1;
E 9
E 8
E 3
E 2

I 3
	if (*p == '~' && (flag & (EXP_TILDE | EXP_VARTILDE)))
D 8
		p = exptilde(p, vartilde);
E 8
I 8
		p = exptilde(p, flag);
E 8
E 3
	for (;;) {
		switch (c = *p++) {
		case '\0':
D 2
		case CTLENDVAR:
E 2
I 2
		case CTLENDVAR: /* ??? */
E 2
			goto breakloop;
		case CTLESC:
D 8
			if (full)
E 8
I 8
			if (quotes)
E 8
				STPUTC(c, expdest);
			c = *p++;
			STPUTC(c, expdest);
			break;
		case CTLVAR:
D 3
			p = evalvar(p, full);
E 3
I 3
			p = evalvar(p, flag);
E 3
			break;
		case CTLBACKQ:
		case CTLBACKQ|CTLQUOTE:
D 8
			expbackq(argbackq->n, c & CTLQUOTE, full);
E 8
I 8
			expbackq(argbackq->n, c & CTLQUOTE, flag);
E 8
			argbackq = argbackq->next;
			break;
I 2
		case CTLENDARI:
D 8
			expari();
E 8
I 8
			expari(flag);
E 8
			break;
I 3
		case ':':
I 9
		case '=':
			/*
			 * sort of a hack - expand tildes in variable
			 * assignments (after the first '=' and after ':'s).
			 */
E 9
D 4
			if (vartilde)
E 4
I 4
			STPUTC(c, expdest);
D 8
			if (vartilde && *p == '~')
E 4
				p = exptilde(p, vartilde);
E 8
I 8
D 9
			if (flag & EXP_VARTILDE && *p == '~')
E 9
I 9
			if (flag & EXP_VARTILDE && *p == '~') {
				if (c == '=') {
					if (firsteq)
						firsteq = 0;
					else
						break;
				}
E 9
				p = exptilde(p, flag);
I 9
			}
E 9
E 8
I 4
			break;
E 4
E 3
E 2
		default:
			STPUTC(c, expdest);
		}
	}
breakloop:;
I 2
}

I 3
STATIC char *
D 8
exptilde(p, vartilde)
E 8
I 8
exptilde(p, flag)
E 8
	char *p;
D 14
	{
E 14
I 14
	int flag;
{
E 14
	char c, *startp = p;
	struct passwd *pw;
	char *home;
I 8
	int quotes = flag & (EXP_FULL | EXP_CASE);
E 8

D 14
	while (c = *p) {
E 14
I 14
	while ((c = *p) != '\0') {
E 14
		switch(c) {
		case CTLESC:
			return (startp);
		case ':':
D 8
			if (vartilde)
E 8
I 8
			if (flag & EXP_VARTILDE)
E 8
				goto done;
			break;
		case '/':
			goto done;
		}
		p++;
	}
done:
	*p = '\0';
	if (*(startp+1) == '\0') {
		if ((home = lookupvar("HOME")) == NULL)
			goto lose;
	} else {
		if ((pw = getpwnam(startp+1)) == NULL)
			goto lose;
		home = pw->pw_dir;
	}
	if (*home == '\0')
		goto lose;
	*p = c;
D 14
	while (c = *home++) {
E 14
I 14
	while ((c = *home++) != '\0') {
E 14
D 8
		if (SQSYNTAX[c] == CCTL)
E 8
I 8
		if (quotes && SQSYNTAX[c] == CCTL)
E 8
			STPUTC(CTLESC, expdest);
		STPUTC(c, expdest);
	}
	return (p);
lose:
	*p = c;
	return (startp);
}


E 3
/*
 * Expand arithmetic expression.  Backup to start of expression,
 * evaluate, place result in (backed up) result, adjust string position.
 */
D 8
expari()
E 8
I 8
void
expari(flag)
E 8
D 3
{
E 3
I 3
D 14
	{
E 14
I 14
	int flag;
{
E 14
E 3
D 6
	char *p, *start = stackblock();
E 6
I 6
	char *p, *start;
E 6
	int result;
I 8
	int quotes = flag & (EXP_FULL | EXP_CASE);
E 8

	/*
	 * This routine is slightly over-compilcated for
	 * efficiency.  First we make sure there is
	 * enough space for the result, which may be bigger
	 * than the expression if we add exponentation.  Next we
	 * scan backwards looking for the start of arithmetic.  If the
	 * next previous character is a CTLESC character, then we
	 * have to rescan starting from the beginning since CTLESC
	 * characters have to be processed left to right.  
	 */
	CHECKSTRSPACE(8, expdest);
D 6
	USTPUTC('\0', expdest);
E 6
I 6
	USTPUTC('\0', expdest); 
	start = stackblock();
E 6
	p = expdest;
	while (*p != CTLARI && p >= start)
		--p;
	if (*p != CTLARI)
		error("missing CTLARI (shouldn't happen)");
	if (p > start && *(p-1) == CTLESC)
		for (p = start; *p != CTLARI; p++)
			if (*p == CTLESC)
				p++;
D 8
	rmescapes(p+1);
E 8
I 8
	if (quotes)
		rmescapes(p+1);
E 8
	result = arith(p+1);
	fmtstr(p, 10, "%d", result);
	while (*p++)
		;
	result = expdest - p + 1;
	STADJUST(-result, expdest);
E 2
}


/*
 * Expand stuff in backwards quotes.
 */

STATIC void
D 8
expbackq(cmd, quoted, full)
E 8
I 8
expbackq(cmd, quoted, flag)
E 8
	union node *cmd;
D 14
	{
E 14
I 14
	int quoted;
	int flag;
{
E 14
	struct backcmd in;
	int i;
	char buf[128];
	char *p;
	char *dest = expdest;
	struct ifsregion saveifs, *savelastp;
	struct nodelist *saveargbackq;
	char lastc;
	int startloc = dest - stackblock();
	char const *syntax = quoted? DQSYNTAX : BASESYNTAX;
	int saveherefd;
I 8
	int quotes = flag & (EXP_FULL | EXP_CASE);
E 8

	INTOFF;
	saveifs = ifsfirst;
	savelastp = ifslastp;
	saveargbackq = argbackq;
	saveherefd = herefd;      
	herefd = -1;
	p = grabstackstr(dest);
	evalbackcmd(cmd, &in);
	ungrabstackstr(p, dest);
	ifsfirst = saveifs;
	ifslastp = savelastp;
	argbackq = saveargbackq;
	herefd = saveherefd;

	p = in.buf;
	lastc = '\0';
	for (;;) {
		if (--in.nleft < 0) {
			if (in.fd < 0)
				break;
			while ((i = read(in.fd, buf, sizeof buf)) < 0 && errno == EINTR);
			TRACE(("expbackq: read returns %d\n", i));
			if (i <= 0)
				break;
			p = buf;
			in.nleft = i - 1;
		}
		lastc = *p++;
		if (lastc != '\0') {
D 8
			if (full && syntax[lastc] == CCTL)
E 8
I 8
			if (quotes && syntax[lastc] == CCTL)
E 8
				STPUTC(CTLESC, dest);
			STPUTC(lastc, dest);
		}
	}
D 14
	if (lastc == '\n') {
E 14
I 14

	/* Eat all trailing newlines */
	for (p--; lastc == '\n'; lastc = *--p)
E 14
		STUNPUTC(dest);
D 14
	}
E 14
I 14

E 14
	if (in.fd >= 0)
		close(in.fd);
	if (in.buf)
		ckfree(in.buf);
	if (in.jp)
D 10
		waitforjob(in.jp);
E 10
I 10
		exitstatus = waitforjob(in.jp);
E 10
	if (quoted == 0)
		recordregion(startloc, dest - stackblock(), 0);
	TRACE(("evalbackq: size=%d: \"%.*s\"\n",
		(dest - stackblock()) - startloc,
		(dest - stackblock()) - startloc,
		stackblock() + startloc));
	expdest = dest;
	INTON;
}



I 13
STATIC int
subevalvar(p, str, subtype, startloc, varflags)
	char *p;
	char *str;
	int subtype;
	int startloc;
	int varflags;
{

	char *startp;
	char *loc;
	int c = 0;
	int saveherefd = herefd;
	struct nodelist *saveargbackq = argbackq;
	herefd = -1;
	argstr(p, 0);
	STACKSTRNUL(expdest);
	herefd = saveherefd;
	argbackq = saveargbackq;
	startp = stackblock() + startloc;

	switch (subtype) {
	case VSASSIGN:
		setvar(str, startp, 0);
		STADJUST(startp - expdest, expdest);
		varflags &= ~VSNUL;
		if (c != 0)
			*loc = c;
		return 1;

	case VSQUESTION:
		if (*p != CTLENDVAR) {
			outfmt(&errout, "%s\n", startp);
			error((char *)NULL);
		}
		error("%.*s: parameter %snot set", p - str - 1,
		      str, (varflags & VSNUL) ? "null or "
					      : nullstr);
		return 0;

	case VSTRIMLEFT:
		for (loc = startp; loc < str - 1; loc++) {
			c = *loc;
			*loc = '\0';
			if (patmatch(str, startp)) {
				*loc = c;
				goto recordleft;
			}
			*loc = c;
		}
		return 0;

	case VSTRIMLEFTMAX:
		for (loc = str - 1; loc >= startp; loc--) {
			c = *loc;
			*loc = '\0';
			if (patmatch(str, startp)) {
				*loc = c;
				goto recordleft;
			}
			*loc = c;
		}
		return 0;

	case VSTRIMRIGHT:
		for (loc = str - 1; loc >= startp; loc--) {
			if (patmatch(str, loc)) {
				expdest = loc;
				return 1;
			}
		}
		return 0;

	case VSTRIMRIGHTMAX:
		for (loc = startp; loc < str - 1; loc++) {
			if (patmatch(str, loc)) {
				expdest = loc;
				return 1;
			}
		}
		return 0;


	default:
		abort();
	}

recordleft:
	expdest = (str - 1) - (loc - startp);
	while (loc != str - 1)
		*startp++ = *loc++;
	return 1;
}


E 13
/*
 * Expand a variable, and return a pointer to the next character in the
 * input string.
 */

STATIC char *
D 3
evalvar(p, full)
E 3
I 3
evalvar(p, flag)
E 3
	char *p;
D 14
	{
E 14
I 14
	int flag;
{
E 14
	int subtype;
D 3
	int flags;
E 3
I 3
	int varflags;
E 3
	char *var;
	char *val;
I 13
	char *pat;
E 13
	int c;
	int set;
	int special;
	int startloc;
I 13
	int varlen;
	int easy;
E 13
I 8
	int quotes = flag & (EXP_FULL | EXP_CASE);
E 8

D 3
	flags = *p++;
	subtype = flags & VSTYPE;
E 3
I 3
	varflags = *p++;
	subtype = varflags & VSTYPE;
E 3
	var = p;
	special = 0;
	if (! is_name(*p))
		special = 1;
	p = strchr(p, '=') + 1;
again: /* jump here after setting a variable with ${var=text} */
	if (special) {
		set = varisset(*var);
		val = NULL;
	} else {
		val = lookupvar(var);
D 3
		if (val == NULL || (flags & VSNUL) && val[0] == '\0') {
E 3
I 3
D 14
		if (val == NULL || (varflags & VSNUL) && val[0] == '\0') {
E 14
I 14
		if (val == NULL || ((varflags & VSNUL) && val[0] == '\0')) {
E 14
E 3
			val = NULL;
			set = 0;
		} else
			set = 1;
	}
I 13
	varlen = 0;
E 13
	startloc = expdest - stackblock();
	if (set && subtype != VSPLUS) {
		/* insert the value of the variable */
		if (special) {
I 13
			char *exp, *oexpdest = expdest;
E 13
D 3
			varvalue(*var, flags & VSQUOTE, full);
E 3
I 3
			varvalue(*var, varflags & VSQUOTE, flag & EXP_FULL);
I 13
			if (subtype == VSLENGTH) {
				for (exp = oexpdest;exp != expdest; exp++)
					varlen++;
				expdest = oexpdest;
			}
E 13
E 3
		} else {
D 3
			char const *syntax = (flags & VSQUOTE)? DQSYNTAX : BASESYNTAX;
E 3
I 3
D 13
			char const *syntax = (varflags & VSQUOTE)? DQSYNTAX : BASESYNTAX;
E 13
I 13
			char const *syntax = (varflags & VSQUOTE) ? DQSYNTAX 
								  : BASESYNTAX;
E 13
E 3

D 13
			while (*val) {
D 3
				if (full && syntax[*val] == CCTL)
E 3
I 3
D 8
				if ((flag & EXP_FULL) && syntax[*val] == CCTL)
E 8
I 8
				if (quotes && syntax[*val] == CCTL)
E 8
E 3
					STPUTC(CTLESC, expdest);
				STPUTC(*val++, expdest);
E 13
I 13
			if (subtype == VSLENGTH) {
				for (;*val; val++)
					varlen++;
E 13
			}
I 13
			else {
				while (*val) {
					if (quotes && syntax[*val] == CCTL)
						STPUTC(CTLESC, expdest);
					STPUTC(*val++, expdest);
				}

			}
E 13
		}
	}
I 13
		
E 13
	if (subtype == VSPLUS)
		set = ! set;
D 3
	if (((flags & VSQUOTE) == 0 || (*var == '@' && shellparam.nparam != 1))
E 3
I 3
D 13
	if (((varflags & VSQUOTE) == 0 || (*var == '@' && shellparam.nparam != 1))
E 3
	 && (set || subtype == VSNORMAL))
D 3
		recordregion(startloc, expdest - stackblock(), flags & VSQUOTE);
E 3
I 3
		recordregion(startloc, expdest - stackblock(), varflags & VSQUOTE);
E 3
	if (! set && subtype != VSNORMAL) {
		if (subtype == VSPLUS || subtype == VSMINUS) {
E 13
I 13

	easy = ((varflags & VSQUOTE) == 0 || 
		(*var == '@' && shellparam.nparam != 1));


	switch (subtype) {
	case VSLENGTH:
		expdest = cvtnum(varlen, expdest);
		goto record;

	case VSNORMAL:
		if (!easy)
			break;
record:
		recordregion(startloc, expdest - stackblock(), 
			     varflags & VSQUOTE);
		break;

	case VSPLUS:
	case VSMINUS:
		if (!set) {
E 13
D 3
			argstr(p, full);
E 3
I 3
			argstr(p, flag);
E 3
D 13
		} else {
			char *startp;
			int saveherefd = herefd;
I 12
			struct nodelist *saveargbackq = argbackq;
E 12
			herefd = -1;
			argstr(p, 0);
			STACKSTRNUL(expdest);
			herefd = saveherefd;
I 12
			argbackq = saveargbackq;
E 12
			startp = stackblock() + startloc;
			if (subtype == VSASSIGN) {
				setvar(var, startp, 0);
				STADJUST(startp - expdest, expdest);
D 3
				flags &=~ VSNUL;
E 3
I 3
				varflags &=~ VSNUL;
E 13
I 13
			break;
		}
		if (easy)
			goto record;
		break;

	case VSTRIMLEFT:
	case VSTRIMLEFTMAX:
	case VSTRIMRIGHT:
	case VSTRIMRIGHTMAX:
		if (!set)
			break;
		/*
		 * Terminate the string and start recording the pattern
		 * right after it
		 */
		STPUTC('\0', expdest);
		pat = expdest;
		if (subevalvar(p, pat, subtype, startloc, varflags))
			goto record;
		break;

	case VSASSIGN:
	case VSQUESTION:
		if (!set) {
			if (subevalvar(p, var, subtype, startloc, varflags))
E 13
E 3
				goto again;
D 13
			}
			/* subtype == VSQUESTION */
			if (*p != CTLENDVAR) {
				outfmt(&errout, "%s\n", startp);
				error((char *)NULL);
			}
			error("%.*s: parameter %snot set", p - var - 1,
D 3
				var, (flags & VSNUL)? "null or " : nullstr);
E 3
I 3
				var, (varflags & VSNUL)? "null or " : nullstr);
E 13
I 13
			break;
E 13
E 3
		}
I 13
		if (easy)
			goto record;
		break;

	default:
		abort();
E 13
	}
I 13

E 13
	if (subtype != VSNORMAL) {	/* skip to end of alternative */
		int nesting = 1;
		for (;;) {
			if ((c = *p++) == CTLESC)
				p++;
			else if (c == CTLBACKQ || c == (CTLBACKQ|CTLQUOTE)) {
				if (set)
					argbackq = argbackq->next;
			} else if (c == CTLVAR) {
				if ((*p++ & VSTYPE) != VSNORMAL)
					nesting++;
			} else if (c == CTLENDVAR) {
				if (--nesting == 0)
					break;
			}
		}
	}
	return p;
}



/*
 * Test whether a specialized variable is set.
 */

STATIC int
varisset(name)
	char name;
	{
	char **ap;

	if (name == '!') {
		if (backgndpid == -1)
			return 0;
	} else if (name == '@' || name == '*') {
		if (*shellparam.p == NULL)
			return 0;
	} else if ((unsigned)(name -= '1') <= '9' - '1') {
		ap = shellparam.p;
		do {
			if (*ap++ == NULL)
				return 0;
		} while (--name >= 0);
	}
	return 1;
}



/*
 * Add the value of a specialized variable to the stack string.
 */

STATIC void
varvalue(name, quoted, allow_split)
	char name;
D 14
	{
E 14
I 14
	int quoted;
	int allow_split;
{
E 14
	int num;
D 13
	char temp[32];
E 13
	char *p;
	int i;
D 15
	extern int exitstatus;
E 15
I 15
	extern int oexitstatus;
E 15
	char sep;
	char **ap;
	char const *syntax;

I 4
#define STRTODEST(p) \
	do {\
	if (allow_split) { \
		syntax = quoted? DQSYNTAX : BASESYNTAX; \
		while (*p) { \
			if (syntax[*p] == CCTL) \
				STPUTC(CTLESC, expdest); \
			STPUTC(*p++, expdest); \
		} \
	} else \
		while (*p) \
			STPUTC(*p++, expdest); \
	} while (0)


E 4
	switch (name) {
	case '$':
		num = rootpid;
		goto numvar;
	case '?':
D 15
		num = exitstatus;
E 15
I 15
		num = oexitstatus;
E 15
		goto numvar;
	case '#':
		num = shellparam.nparam;
		goto numvar;
	case '!':
		num = backgndpid;
numvar:
D 13
		p = temp + 31;
		temp[31] = '\0';
		do {
			*--p = num % 10 + '0';
		} while ((num /= 10) != 0);
		while (*p)
			STPUTC(*p++, expdest);
E 13
I 13
		expdest = cvtnum(num, expdest);
E 13
		break;
	case '-':
D 6
		for (i = 0 ; optchar[i] ; i++) {
			if (optval[i])
				STPUTC(optchar[i], expdest);
E 6
I 6
		for (i = 0 ; i < NOPTS ; i++) {
			if (optlist[i].val)
				STPUTC(optlist[i].letter, expdest);
E 6
		}
		break;
	case '@':
		if (allow_split) {
			sep = '\0';
			goto allargs;
		}
		/* fall through */			
	case '*':
		sep = ' ';
allargs:
D 4
		syntax = quoted? DQSYNTAX : BASESYNTAX;
E 4
		for (ap = shellparam.p ; (p = *ap++) != NULL ; ) {
D 4
			/* should insert CTLESC characters */
			while (*p) {
				if (syntax[*p] == CCTL)
					STPUTC(CTLESC, expdest);
				STPUTC(*p++, expdest);
			}
E 4
I 4
			STRTODEST(p);
E 4
			if (*ap)
				STPUTC(sep, expdest);
		}
		break;
	case '0':
		p = arg0;
D 4
string:
		syntax = quoted? DQSYNTAX : BASESYNTAX;
		while (*p) {
			if (syntax[*p] == CCTL)
				STPUTC(CTLESC, expdest);
			STPUTC(*p++, expdest);
		}
E 4
I 4
		STRTODEST(p);
E 4
		break;
	default:
		if ((unsigned)(name -= '1') <= '9' - '1') {
			p = shellparam.p[name];
D 4
			goto string;
E 4
I 4
			STRTODEST(p);
E 4
		}
		break;
	}
}



/*
 * Record the the fact that we have to scan this region of the
 * string for IFS characters.
 */

STATIC void
D 14
recordregion(start, end, nulonly) {
E 14
I 14
recordregion(start, end, nulonly) 
	int start;
	int end;
	int nulonly;
{
E 14
	register struct ifsregion *ifsp;

	if (ifslastp == NULL) {
		ifsp = &ifsfirst;
	} else {
		ifsp = (struct ifsregion *)ckmalloc(sizeof (struct ifsregion));
		ifslastp->next = ifsp;
	}
	ifslastp = ifsp;
	ifslastp->next = NULL;
	ifslastp->begoff = start;
	ifslastp->endoff = end;
	ifslastp->nulonly = nulonly;
}



/*
 * Break the argument string into pieces based upon IFS and add the
 * strings to the argument list.  The regions of the string to be
 * searched for IFS characters have been stored by recordregion.
 */
D 14

E 14
STATIC void
ifsbreakup(string, arglist)
	char *string;
	struct arglist *arglist;
	{
	struct ifsregion *ifsp;
	struct strlist *sp;
	char *start;
	register char *p;
	char *q;
	char *ifs;
I 14
	int ifsspc;
E 14

I 14

E 14
	start = string;
	if (ifslastp != NULL) {
		ifsp = &ifsfirst;
		do {
			p = string + ifsp->begoff;
			ifs = ifsp->nulonly? nullstr : ifsval();
I 14
			ifsspc = strchr(ifs, ' ') != NULL;
E 14
			while (p < string + ifsp->endoff) {
				q = p;
				if (*p == CTLESC)
					p++;
				if (strchr(ifs, *p++)) {
D 14
					if (q > start || *ifs != ' ') {
E 14
I 14
					if (q > start || !ifsspc) {
E 14
						*q = '\0';
						sp = (struct strlist *)stalloc(sizeof *sp);
						sp->text = start;
						*arglist->lastp = sp;
						arglist->lastp = &sp->next;
					}
D 14
					if (*ifs == ' ') {
E 14
I 14
					if (ifsspc) {
E 14
						for (;;) {
							if (p >= string + ifsp->endoff)
								break;
							q = p;
							if (*p == CTLESC)
								p++;
							if (strchr(ifs, *p++) == NULL) {
								p = q;
								break;
							}
						}
					}
					start = p;
				}
			}
		} while ((ifsp = ifsp->next) != NULL);
D 14
		if (*start || (*ifs != ' ' && start > string)) {
E 14
I 14
		if (*start || (!ifsspc && start > string)) {
E 14
			sp = (struct strlist *)stalloc(sizeof *sp);
			sp->text = start;
			*arglist->lastp = sp;
			arglist->lastp = &sp->next;
		}
	} else {
		sp = (struct strlist *)stalloc(sizeof *sp);
		sp->text = start;
		*arglist->lastp = sp;
		arglist->lastp = &sp->next;
	}
}



/*
 * Expand shell metacharacters.  At this point, the only control characters
 * should be escapes.  The results are stored in the list exparg.
 */

char *expdir;


STATIC void
D 3
expandmeta(str)
E 3
I 3
expandmeta(str, flag)
E 3
	struct strlist *str;
D 14
	{
E 14
I 14
	int flag;
{
E 14
	char *p;
	struct strlist **savelastp;
	struct strlist *sp;
	char c;
I 3
	/* TODO - EXP_REDIR */
E 3

	while (str) {
		if (fflag)
			goto nometa;
		p = str->text;
D 3
#if UDIR
		if (p[0] == '/' && p[1] == 'u' && p[2] == '/')
			str->text = p = expudir(p);
#endif
E 3
		for (;;) {			/* fast check for meta chars */
			if ((c = *p++) == '\0')
				goto nometa;
			if (c == '*' || c == '?' || c == '[' || c == '!')
				break;
		}
		savelastp = exparg.lastp;
		INTOFF;
D 7
		if (expdir == NULL)
D 6
			expdir = ckmalloc(1024); /* I hope this is big enough */
E 6
I 6
			expdir = ckmalloc(strlen(str->text)); /* XXX - */
E 7
I 7
		if (expdir == NULL) {
			int i = strlen(str->text);
			expdir = ckmalloc(i < 2048 ? 2048 : i); /* XXX */
		}

E 7
E 6
		expmeta(expdir, str->text);
		ckfree(expdir);
		expdir = NULL;
		INTON;
		if (exparg.lastp == savelastp) {
I 3
			/* 
			 * no matches 
			 */
E 3
D 5
			if (! zflag) {
E 5
I 5
D 6
#ifdef PUTBACK_ZFLAG
			if (! zflag) { ...
#endif

E 6
E 5
nometa:
D 6
				*exparg.lastp = str;
				rmescapes(str->text);
				exparg.lastp = &str->next;
E 6
I 6
			*exparg.lastp = str;
			rmescapes(str->text);
			exparg.lastp = &str->next;
E 6
D 5
			}
E 5
		} else {
			*exparg.lastp = NULL;
			*savelastp = sp = expsort(*savelastp);
			while (sp->next != NULL)
				sp = sp->next;
			exparg.lastp = &sp->next;
		}
		str = str->next;
	}
}
D 3


#if UDIR
/*
 * Expand /u/username into the home directory for the specified user.
 * We could use the getpw stuff here, but then we would have to load
 * in stdio and who knows what else.
 */

#define MAXLOGNAME 32
#define MAXPWLINE 128

char *pfgets();


STATIC char *
expudir(path)
	char *path;
	{
	register char *p, *q, *r;
	char name[MAXLOGNAME];
	char line[MAXPWLINE];
	int i;

	r = path;				/* result on failure */
	p = r + 3;			/* the 3 skips "/u/" */
	q = name;
	while (*p && *p != '/') {
		if (q >= name + MAXLOGNAME - 1)
			return r;		/* fail, name too long */
		*q++ = *p++;
	}
	*q = '\0';
	setinputfile("/etc/passwd", 1);
	q = line + strlen(name);
	while (pfgets(line, MAXPWLINE) != NULL) {
		if (line[0] == name[0] && prefix(name, line) && *q == ':') {
			/* skip to start of home directory */
			i = 4;
			do {
				while (*++q && *q != ':');
			} while (--i > 0);
			if (*q == '\0')
				break;		/* fail, corrupted /etc/passwd */
			q++;
			for (r = q ; *r && *r != '\n' && *r != ':' ; r++);
			*r = '\0';		/* nul terminate home directory */
			i = r - q;		/* i = strlen(q) */
			r = stalloc(i + strlen(p) + 1);
			scopy(q, r);
			scopy(p, r + i);
			TRACE(("expudir converts %s to %s\n", path, r));
			didudir = 1;
			path = r;		/* succeed */
			break;
		}
	}
	popfile();
	return r;
}
#endif
E 3


/*
 * Do metacharacter (i.e. *, ?, [...]) expansion.
 */

STATIC void
expmeta(enddir, name)
	char *enddir;
	char *name;
	{
	register char *p;
	char *q;
	char *start;
	char *endname;
	int metaflag;
	struct stat statb;
	DIR *dirp;
	struct dirent *dp;
	int atend;
	int matchdot;

	metaflag = 0;
	start = name;
	for (p = name ; ; p++) {
		if (*p == '*' || *p == '?')
			metaflag = 1;
		else if (*p == '[') {
			q = p + 1;
			if (*q == '!')
				q++;
			for (;;) {
				if (*q == CTLESC)
					q++;
				if (*q == '/' || *q == '\0')
					break;
				if (*++q == ']') {
					metaflag = 1;
					break;
				}
			}
		} else if (*p == '!' && p[1] == '!'	&& (p == name || p[-1] == '/')) {
			metaflag = 1;
		} else if (*p == '\0')
			break;
		else if (*p == CTLESC)
			p++;
		if (*p == '/') {
			if (metaflag)
				break;
			start = p + 1;
		}
	}
	if (metaflag == 0) {	/* we've reached the end of the file name */
		if (enddir != expdir)
			metaflag++;
		for (p = name ; ; p++) {
			if (*p == CTLESC)
				p++;
			*enddir++ = *p;
			if (*p == '\0')
				break;
		}
		if (metaflag == 0 || stat(expdir, &statb) >= 0)
			addfname(expdir);
		return;
	}
	endname = p;
	if (start != name) {
		p = name;
		while (p < start) {
			if (*p == CTLESC)
				p++;
			*enddir++ = *p++;
		}
	}
	if (enddir == expdir) {
		p = ".";
	} else if (enddir == expdir + 1 && *expdir == '/') {
		p = "/";
	} else {
		p = expdir;
		enddir[-1] = '\0';
	}
	if ((dirp = opendir(p)) == NULL)
		return;
	if (enddir != expdir)
		enddir[-1] = '/';
	if (*endname == 0) {
		atend = 1;
	} else {
		atend = 0;
		*endname++ = '\0';
	}
	matchdot = 0;
D 14
	if (start[0] == '.' || start[0] == CTLESC && start[1] == '.')
E 14
I 14
	if (start[0] == '.' || (start[0] == CTLESC && start[1] == '.'))
E 14
		matchdot++;
	while (! int_pending() && (dp = readdir(dirp)) != NULL) {
		if (dp->d_name[0] == '.' && ! matchdot)
			continue;
		if (patmatch(start, dp->d_name)) {
			if (atend) {
				scopy(dp->d_name, enddir);
				addfname(expdir);
			} else {
				char *q;
D 14
				for (p = enddir, q = dp->d_name ; *p++ = *q++ ;);
E 14
I 14
				for (p = enddir, q = dp->d_name;
				     (*p++ = *q++) != '\0';)
					continue;
E 14
				p[-1] = '/';
				expmeta(p, endname);
			}
		}
	}
	closedir(dirp);
	if (! atend)
		endname[-1] = '/';
}


/*
 * Add a file name to the list.
 */

STATIC void
addfname(name)
	char *name;
	{
	char *p;
	struct strlist *sp;

	p = stalloc(strlen(name) + 1);
	scopy(name, p);
	sp = (struct strlist *)stalloc(sizeof *sp);
	sp->text = p;
	*exparg.lastp = sp;
	exparg.lastp = &sp->next;
}


/*
 * Sort the results of file name expansion.  It calculates the number of
 * strings to sort and then calls msort (short for merge sort) to do the
 * work.
 */

STATIC struct strlist *
expsort(str)
	struct strlist *str;
	{
	int len;
	struct strlist *sp;

	len = 0;
	for (sp = str ; sp ; sp = sp->next)
		len++;
	return msort(str, len);
}


STATIC struct strlist *
msort(list, len)
	struct strlist *list;
D 14
	{
E 14
I 14
	int len;
{
E 14
	struct strlist *p, *q;
	struct strlist **lpp;
	int half;
	int n;

	if (len <= 1)
		return list;
	half = len >> 1;      
	p = list;
	for (n = half ; --n >= 0 ; ) {
		q = p;
		p = p->next;
	}
	q->next = NULL;			/* terminate first half of list */
	q = msort(list, half);		/* sort first half of list */
	p = msort(p, len - half);		/* sort second half */
	lpp = &list;
	for (;;) {
		if (strcmp(p->text, q->text) < 0) {
			*lpp = p;
			lpp = &p->next;
			if ((p = *lpp) == NULL) {
				*lpp = q;
				break;
			}
		} else {
			*lpp = q;
			lpp = &q->next;
			if ((q = *lpp) == NULL) {
				*lpp = p;
				break;
			}
		}
	}
	return list;
}



/*
 * Returns true if the pattern matches the string.
 */

int
patmatch(pattern, string)
	char *pattern;
	char *string;
	{
I 8
#ifdef notdef
E 8
	if (pattern[0] == '!' && pattern[1] == '!')
		return 1 - pmatch(pattern + 2, string);
	else
I 8
#endif
E 8
		return pmatch(pattern, string);
}


STATIC int
pmatch(pattern, string)
	char *pattern;
	char *string;
	{
	register char *p, *q;
	register char c;

	p = pattern;
	q = string;
	for (;;) {
		switch (c = *p++) {
		case '\0':
			goto breakloop;
		case CTLESC:
			if (*q++ != *p++)
				return 0;
			break;
		case '?':
			if (*q++ == '\0')
				return 0;
			break;
		case '*':
			c = *p;
			if (c != CTLESC && c != '?' && c != '*' && c != '[') {
				while (*q != c) {
					if (*q == '\0')
						return 0;
					q++;
				}
			}
			do {
				if (pmatch(p, q))
					return 1;
			} while (*q++ != '\0');
			return 0;
		case '[': {
			char *endp;
			int invert, found;
			char chr;

			endp = p;
			if (*endp == '!')
				endp++;
			for (;;) {
				if (*endp == '\0')
					goto dft;		/* no matching ] */
				if (*endp == CTLESC)
					endp++;
				if (*++endp == ']')
					break;
			}
			invert = 0;
			if (*p == '!') {
				invert++;
				p++;
			}
			found = 0;
			chr = *q++;
I 14
			if (chr == '\0')
				return 0;
E 14
			c = *p++;
			do {
				if (c == CTLESC)
					c = *p++;
				if (*p == '-' && p[1] != ']') {
					p++;
					if (*p == CTLESC)
						p++;
					if (chr >= c && chr <= *p)
						found = 1;
					p++;
				} else {
					if (chr == c)
						found = 1;
				}
			} while ((c = *p++) != ']');
			if (found == invert)
				return 0;
			break;
		}
D 8
dft:	    default:
E 8
I 8
dft:	        default:
E 8
			if (*q++ != c)
				return 0;
			break;
		}
	}
breakloop:
	if (*q != '\0')
		return 0;
	return 1;
}



/*
 * Remove any CTLESC characters from a string.
 */

void
rmescapes(str)
	char *str;
	{
	register char *p, *q;

	p = str;
	while (*p != CTLESC) {
		if (*p++ == '\0')
			return;
	}
	q = p;
	while (*p) {
		if (*p == CTLESC)
			p++;
		*q++ = *p++;
	}
	*q = '\0';
}



/*
 * See if a pattern matches in a case statement.
 */

int
casematch(pattern, val)
	union node *pattern;
	char *val;
	{
	struct stackmark smark;
	int result;
	char *p;

	setstackmark(&smark);
	argbackq = pattern->narg.backquote;
	STARTSTACKSTR(expdest);
	ifslastp = NULL;
D 8
	argstr(pattern->narg.text, 0);
E 8
I 8
	argstr(pattern->narg.text, EXP_TILDE | EXP_CASE);
E 8
	STPUTC('\0', expdest);
	p = grabstackstr(expdest);
	result = patmatch(p, val);
	popstackmark(&smark);
	return result;
I 13
}

/*
 * Our own itoa().
 */

STATIC char *
cvtnum(num, buf)
	int num;
	char *buf;
	{
	char temp[32];
	int neg = num < 0;
	char *p = temp + 31;

	temp[31] = '\0';

	do {
		*--p = num % 10 + '0';
	} while ((num /= 10) != 0);

	if (neg)
		*--p = '-';

	while (*p)
		STPUTC(*p++, buf);
	return buf;
E 13
}
E 1
