h63034
s 00002/00002/00379
d D 8.1 93/05/31 16:41:51 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00379
d D 5.13 93/05/22 19:06:25 christos 15 14
c Fixed gcc -Wall warnings
e
s 00001/00001/00380
d D 5.12 91/11/04 18:23:45 christos 14 13
c Changed slightly the $! error message
e
s 00010/00013/00371
d D 5.11 91/07/19 17:30:39 christos 13 12
c stdio based version; brace glob fix; builtin prototypes
e
s 00005/00005/00379
d D 5.10 91/06/08 17:08:40 christos 12 11
c More prototype fixes, Removed TERMIOS define
e
s 00004/00001/00380
d D 5.9 91/06/08 12:20:14 bostic 11 10
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00002/00002/00379
d D 5.8 91/06/07 20:57:17 christos 10 9
c static function prototypes
e
s 00028/00011/00353
d D 5.7 91/06/07 11:13:20 bostic 9 8
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00325/00113/00039
d D 5.6 91/06/04 13:31:22 bostic 8 7
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00145
d D 5.5 91/04/04 18:17:36 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00001/00150
d D 5.4 91/04/01 17:37:08 bostic 6 5
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00006/00006/00145
d D 5.3 86/05/13 01:02:59 lepreau 5 4
c Fix "cmd not found error handling in script (was seeking just .+1024).
c from elsie!ado
e
s 00003/00003/00148
d D 5.2 85/06/06 13:09:45 edward 4 3
c cleaning up after bozos
e
s 00008/00002/00143
d D 5.1 85/06/04 10:56:52 dist 3 2
c Add copyright
e
s 00006/00003/00139
d D 4.2 84/12/13 14:40:02 edward 2 1
c performance
e
s 00142/00000/00000
d D 4.1 80/10/09 12:40:44 bill 1 0
c date and time created 80/10/09 12:40:44 by bill
e
u
U
t
T
I 3
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
E 4
I 4
 * All rights reserved.  The Berkeley Software License Agreement
E 4
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 16
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * %sccs.include.redist.c%
E 7
 */

E 3
I 1
D 2
static	char *sccsid = "%Z%%M% %I% %G%";
E 2
I 2
#ifndef lint
D 3
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 3
I 3
D 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 4
I 4
D 7
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 7
E 4
E 3
E 2

I 8
D 11
#define _h_tc_err		/* Don't redefine the errors	 */
E 11
I 11
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
E 11
E 8
D 9
#include "sh.h"
E 9
I 9
D 12
#include "csh.h"
#include "extern.h"
I 11

E 12
E 11
#if __STDC__
D 12
#include <stdarg.h>
E 12
I 12
# include <stdarg.h>
E 12
#else
E 9
D 8
#include <sys/ioctl.h>
E 8
I 8
D 12
#include <varargs.h>
E 12
I 12
# include <varargs.h>
E 12
I 9
#endif
I 12

#include "csh.h"
#include "extern.h"
E 12
E 9
E 8

I 8
D 9
char   *seterr = (char *) 0;	/* Holds last error if there was one */
E 9
I 9
char   *seterr = NULL;	/* Holds last error if there was one */
E 9

#define ERR_FLAGS	0xf0000000
#define ERR_NAME	0x10000000
#define ERR_SILENT	0x20000000
#define ERR_OLD		0x40000000

static char *errorlist[] =
{
#define ERR_SYNTAX	0
    "Syntax Error",
#define ERR_NOTALLOWED	1
    "%s is not allowed",
#define ERR_WTOOLONG	2
    "Word too long",
#define ERR_LTOOLONG	3
    "$< line too long",
#define ERR_DOLZERO	4
    "No file for $0",
#define ERR_DOLQUEST	5
    "$? not allowed here",
#define ERR_INCBR	6
    "Incomplete [] modifier",
#define ERR_EXPORD	7
    "$ expansion must end before ]",
#define ERR_BADMOD	8
    "Bad : modifier in $ (%c)",
#define ERR_SUBSCRIPT	9
    "Subscript error",
#define ERR_BADNUM	10
    "Badly formed number",
#define ERR_NOMORE	11
    "No more words",
#define ERR_FILENAME	12
    "Missing file name",
#define ERR_GLOB	13
    "Internal glob error",
#define ERR_COMMAND	14
    "Command not found",
#define ERR_TOOFEW	15
    "Too few arguments",
#define ERR_TOOMANY	16
    "Too many arguments",
#define ERR_DANGER	17
    "Too dangerous to alias that",
#define ERR_EMPTYIF	18
    "Empty if",
#define ERR_IMPRTHEN	19
    "Improper then",
#define ERR_NOPAREN	20
    "Words not parenthesized",
#define ERR_NOTFOUND	21
    "%s not found",
#define ERR_MASK	22
    "Improper mask",
#define ERR_LIMIT	23
    "No such limit",
#define ERR_TOOLARGE	24
    "Argument too large",
#define ERR_SCALEF	25
    "Improper or unknown scale factor",
#define ERR_UNDVAR	26
    "Undefined variable",
#define ERR_DEEP	27
    "Directory stack not that deep",
#define ERR_BADSIG	28
    "Bad signal number",
#define ERR_UNKSIG	29
    "Unknown signal; kill -l lists signals",
#define ERR_VARBEGIN	30
    "Variable name must begin with a letter",
#define ERR_VARTOOLONG	31
    "Variable name too long",
#define ERR_VARALNUM	32
    "Variable name must contain alphanumeric characters",
#define ERR_JOBCONTROL	33
    "No job control in this shell",
#define ERR_EXPRESSION	34
    "Expression Syntax",
#define ERR_NOHOMEDIR	35
    "No home directory",
#define ERR_CANTCHANGE	36
    "Can't change to home directory",
#define ERR_NULLCOM	37
    "Invalid null command",
#define ERR_ASSIGN	38
    "Assignment missing expression",
#define ERR_UNKNOWNOP	39
    "Unknown operator",
#define ERR_AMBIG	40
    "Ambiguous",
#define ERR_EXISTS	41
    "%s: File exists",
#define ERR_INTR	42
    "Interrupted",
#define ERR_RANGE	43
    "Subscript out of range",
#define ERR_OVERFLOW	44
    "Line overflow",
#define ERR_VARMOD	45
    "Unknown variable modifier",
#define ERR_NOSUCHJOB	46
    "No such job",
#define ERR_TERMINAL	47
    "Can't from terminal",
#define ERR_NOTWHILE	48
    "Not in while/foreach",
#define ERR_NOPROC	49
    "No more processes",
#define ERR_NOMATCH	50
    "No match",
#define ERR_MISSING	51
    "Missing %c",
#define ERR_UNMATCHED	52
    "Unmatched %c",
#define ERR_NOMEM	53
    "Out of memory",
#define ERR_PIPE	54
    "Can't make pipe",
#define ERR_SYSTEM	55
    "%s: %s",
#define ERR_STRING	56
    "%s",
#define ERR_JOBS	57
    "Usage: jobs [ -l ]",
#define ERR_JOBARGS	58
    "Arguments should be jobs or process id's",
#define ERR_JOBCUR	59
    "No current job",
#define ERR_JOBPREV	60
    "No previous job",
#define ERR_JOBPAT	61
    "No job matches pattern",
#define ERR_NESTING	62
    "Fork nesting > %d; maybe `...` loop",
#define ERR_JOBCTRLSUB	63
    "No job control in subshells",
#define ERR_BADPLPS	64
    "Badly placed ()'s",
#define ERR_STOPPED	65
    "%sThere are suspended jobs",
#define ERR_NODIR	66
    "No other directory",
#define ERR_EMPTY	67
    "Directory stack empty",
#define ERR_BADDIR	68
    "Bad directory",
#define ERR_DIRUS	69
    "Usage: %s [-lvn]%s",
#define ERR_HFLAG	70
    "No operand for -h flag",
#define ERR_NOTLOGIN	71
    "Not a login shell",
#define ERR_DIV0	72
    "Division by 0",
#define ERR_MOD0	73
    "Mod by 0",
#define ERR_BADSCALE	74
    "Bad scaling; did you mean \"%s\"?",
#define ERR_SUSPLOG	75
    "Can't suspend a login shell (yet)",
#define ERR_UNKUSER	76
    "Unknown user: %s",
#define ERR_NOHOME	77
    "No $home variable set",
#define ERR_HISTUS	78
D 13
    "Usage: history [-rht] [# number of events]",
E 13
I 13
    "Usage: history [-rh] [# number of events]",
E 13
#define ERR_SPDOLLT	79
D 14
    "$ or < not allowed with $# or $?",
E 14
I 14
    "$, ! or < not allowed with $# or $?",
E 14
#define ERR_NEWLINE	80
    "Newline in variable name",
#define ERR_SPSTAR	81
    "* not allowed with $# or $?",
#define ERR_DIGIT	82
    "$?<digit> or $#<digit> not allowed",
#define ERR_VARILL	83
    "Illegal variable name",
#define ERR_NLINDEX	84
    "Newline in variable index",
#define ERR_EXPOVFL	85
    "Expansion buffer overflow",
#define ERR_VARSYN	86
    "Variable syntax",
#define ERR_BADBANG	87
    "Bad ! form",
#define ERR_NOSUBST	88
    "No previous substitute",
#define ERR_BADSUBST	89
    "Bad substitute",
#define ERR_LHS		90
    "No previous left hand side",
#define ERR_RHSLONG	91
    "Right hand side too long",
#define ERR_BADBANGMOD	92
    "Bad ! modifier: %c",
#define ERR_MODFAIL	93
    "Modifier failed",
#define ERR_SUBOVFL	94
    "Substitution buffer overflow",
#define ERR_BADBANGARG	95
    "Bad ! arg selector",
#define ERR_NOSEARCH	96
    "No prev search",
#define ERR_NOEVENT	97
    "%s: Event not found",
#define ERR_TOOMANYRP	98
    "Too many )'s",
#define ERR_TOOMANYLP	99
    "Too many ('s",
#define ERR_BADPLP	100
    "Badly placed (",
#define ERR_MISRED	101
    "Missing name for redirect",
#define ERR_OUTRED	102
    "Ambiguous output redirect",
#define ERR_REDPAR	103
    "Can't << within ()'s",
#define ERR_INRED	104
    "Ambiguous input redirect",
#define ERR_ALIASLOOP	105
    "Alias loop",
#define ERR_HISTLOOP	106
    "!# History loop",
#define ERR_ARCH        107
    "%s: %s. Wrong Architecture",
#define ERR_FILEINQ	108
    "Malformed file inquiry",
#define ERR_SELOVFL	109
    "Selector overflow",
#define ERR_INVALID	110
    "Invalid Error"
};

E 8
/*
D 8
 * C Shell
E 8
I 8
 * The parser and scanner set up errors for later by calling seterr,
 * which sets the variable err as a side effect; later to be tested,
 * e.g. in process.
E 8
 */
I 8
void
D 9
/*VARARGS1*/
E 9
I 9
#if __STDC__
seterror(int id, ...)
#else
E 9
seterror(id, va_alist)
D 9
    int     id;
E 8

D 8
bool	errspl;			/* Argument to error was spliced by seterr2 */
char	one[2] = { '1', 0 };
char	*onev[2] = { one, NOSTR };
E 8
I 8
va_dcl
E 9
I 9
     int id;
     va_dcl
#endif
E 9
{
    if (seterr == 0) {
D 9
	va_list va;
E 9
	char    berr[BUFSIZ];
I 9
	va_list va;
E 9

I 9
#if __STDC__
	va_start(va, id);
#else
	va_start(va);
#endif
E 9
	if (id < 0 || id > sizeof(errorlist) / sizeof(errorlist[0]))
	    id = ERR_INVALID;
D 9
	va_start(va);
E 9
D 13
	xvsprintf(berr, errorlist[id], va);
E 13
I 13
	vsprintf(berr, errorlist[id], va);
E 13
	va_end(va);

	seterr = strsave(berr);
    }
}

E 8
/*
D 8
 * Print error string s with optional argument arg.
E 8
I 8
 * Print the error with the given id.
 *
 * Special ids:
 *	ERR_SILENT: Print nothing.
 *	ERR_OLD: Print the previously set error if one was there.
 *	         otherwise return.
 *	ERR_NAME: If this bit is set, print the name of the function
 *		  in bname
 *
E 8
 * This routine always resets or exits.  The flag haderr
 * is set so the routine who catches the unwind can propogate
 * it if they want.
 *
 * Note that any open files at the point of error will eventually
 * be closed in the routine process in sh.c which is the only
 * place error unwinds are ever caught.
 */
I 2
D 8
/*VARARGS1*/
E 2
error(s, arg)
	char *s;
E 8
I 8
void
D 9
/*VARARGS*/
E 9
I 9
#if __STDC__
stderror(int id, ...)
#else
E 9
stderror(id, va_alist)
    int     id;
D 9

va_dcl
E 9
I 9
    va_dcl
#endif
E 9
E 8
{
D 8
	register char **v;
	register char *ep;
E 8
I 8
    va_list va;
    register Char **v;
    int     flags = id & ERR_FLAGS;
E 8

D 8
	/*
	 * Must flush before we print as we wish output before the error
	 * to go on (some form of) standard output, while output after
	 * goes on (some form of) diagnostic output.
	 * If didfds then output will go to 1/2 else to FSHOUT/FSHDIAG.
	 * See flush in sh.print.c.
	 */
	flush();
	haderr = 1;		/* Now to diagnostic output */
	timflg = 0;		/* This isn't otherwise reset */
	if (v = pargv)
		pargv = 0, blkfree(v);
	if (v = gargv)
		gargv = 0, blkfree(v);
E 8
I 8
    id &= ~ERR_FLAGS;
E 8

D 8
	/*
	 * A zero arguments causes no printing, else print
	 * an error diagnostic here.
	 */
	if (s)
		printf(s, arg), printf(".\n");
E 8
I 8
D 10
    if ((flags & ERR_OLD) && seterr == (char *) 0)
E 10
I 10
    if ((flags & ERR_OLD) && seterr == NULL)
E 10
	return;
E 8

D 8
	didfds = 0;		/* Forget about 0,1,2 */
	if ((ep = err) && errspl) {
		errspl = 0;
		xfree(ep);
	}
	errspl = 0;
E 8
I 8
    if (id < 0 || id > sizeof(errorlist) / sizeof(errorlist[0]))
	id = ERR_INVALID;
E 8

D 8
	/*
I 5
	 * Go away if -e or we are a child shell
	 */
	if (exiterr || child)
		exit(1);
E 8
I 8
D 13
    /*
     * Must flush before we print as we wish output before the error to go on
     * (some form of) standard output, while output after goes on (some form
     * of) diagnostic output. If didfds then output will go to 1/2 else to
     * FSHOUT/FSHDIAG. See flush in sh.print.c.
     */
    flush();
E 13
I 13
    (void) fflush(cshout);
    (void) fflush(csherr);
E 13
    haderr = 1;			/* Now to diagnostic output */
    timflg = 0;			/* This isn't otherwise reset */
E 8

D 8
	/*
E 5
	 * Reset the state of the input.
	 * This buffered seek to end of file will also
	 * clear the while/foreach stack.
	 */
	btoeof();
E 8
D 5

	/*
	 * Go away if -e or we are a child shell
	 */
	if (exiterr || child)
		exit(1);
E 5

D 8
	setq("status", onev, &shvhed);
	if (tpgrp > 0)
D 2
		ioctl(FSHTTY, TIOCSPGRP, &tpgrp);
E 2
I 2
		(void) ioctl(FSHTTY, TIOCSPGRP, (char *)&tpgrp);
E 2
D 6
	reset();		/* Unwind */
E 6
I 6
	longjmp(reslab, 0);		/* Unwind */
E 6
}

/*
 * Perror is the shells version of perror which should otherwise
 * never be called.
 */
Perror(s)
	char *s;
{

	/*
	 * Perror uses unit 2, thus if we didn't set up the fd's
	 * we must set up unit 2 now else the diagnostic will disappear
	 */
	if (!didfds) {
		register int oerrno = errno;

D 2
		dcopy(SHDIAG, 2);
E 2
I 2
		(void) dcopy(SHDIAG, 2);
E 2
		errno = oerrno;
E 8
I 8
    if (!(flags & ERR_SILENT)) {
	if (flags & ERR_NAME)
D 13
	    xprintf("%s: ", bname);
E 13
I 13
	    (void) fprintf(csherr, "%s: ", bname);
E 13
	if ((flags & ERR_OLD))
	    /* Old error. */
D 13
	    xprintf("%s.\n", seterr);
E 13
I 13
	    (void) fprintf(csherr, "%s.\n", seterr);
E 13
	else {
I 9
#if __STDC__
	    va_start(va, id);
#else
E 9
	    va_start(va);
I 9
#endif
E 9
D 13
	    xvprintf(errorlist[id], va);
E 13
I 13
	    (void) vfprintf(csherr, errorlist[id], va);
E 13
	    va_end(va);
D 13
	    xprintf(".\n");
E 13
I 13
	    (void) fprintf(csherr, ".\n");
E 13
E 8
	}
D 8
	perror(s);
	error(NOSTR);		/* To exit or unwind */
}
E 8
I 8
    }
E 8

D 8
bferr(cp)
	char *cp;
{
E 8
I 8
    if (seterr) {
	xfree((ptr_t) seterr);
D 10
	seterr = (char *) 0;
E 10
I 10
	seterr = NULL;
E 10
    }
E 8

D 8
	flush();
	haderr = 1;
	printf("%s: ", bname);
	error(cp);
}
E 8
I 8
D 15
    if (v = pargv)
E 15
I 15
    if ((v = pargv) != NULL)
E 15
	pargv = 0, blkfree(v);
D 15
    if (v = gargv)
E 15
I 15
    if ((v = gargv) != NULL)
E 15
	gargv = 0, blkfree(v);
E 8

I 13
    (void) fflush(cshout);
    (void) fflush(csherr);
E 13
D 8
/*
 * The parser and scanner set up errors for later by calling seterr,
 * which sets the variable err as a side effect; later to be tested,
 * e.g. in process.
 */
seterr(s)
	char *s;
{
E 8
I 8
    didfds = 0;			/* Forget about 0,1,2 */
    /*
     * Go away if -e or we are a child shell
     */
    if (exiterr || child)
	xexit(1);
E 8

D 8
	if (err == 0)
		err = s, errspl = 0;
}
E 8
I 8
    /*
     * Reset the state of the input. This buffered seek to end of file will
     * also clear the while/foreach stack.
     */
    btoeof();
E 8

D 8
/* Set err to a splice of cp and dp, to be freed later in error() */
seterr2(cp, dp)
	char *cp, *dp;
{

	if (err)
		return;
	err = strspl(cp, dp);
	errspl++;
}

/* Set err to a splice of cp with a string form of character d */
seterrc(cp, d)
	char *cp, d;
{
	char chbuf[2];

	chbuf[0] = d;
	chbuf[1] = 0;
	seterr2(cp, chbuf);
E 8
I 8
    set(STRstatus, Strsave(STR1));
    if (tpgrp > 0)
	(void) tcsetpgrp(FSHTTY, tpgrp);
    reset();			/* Unwind */
E 8
}
E 1
