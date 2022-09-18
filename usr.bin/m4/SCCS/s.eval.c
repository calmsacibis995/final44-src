h18158
s 00001/00000/00763
d D 8.2 95/04/27 15:30:53 bostic 10 9
c m4(1)'s m4exit builtin macro doesn't remove /tmp files.
c From: "Chris G. Demetriou" <cgd@alpha.bostic.com>
e
s 00002/00002/00761
d D 8.1 93/06/06 15:04:13 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00762
d D 5.8 91/11/20 16:27:07 bostic 8 7
c add affiliation for Oz
e
s 00001/00000/00762
d D 5.7 91/10/02 18:22:25 eric 7 6
c keep base of pushback buffer per file; this prevents pushed back
c characters from being read out of order on include directives.
e
s 00001/00000/00761
d D 5.6 91/09/04 10:07:29 bostic 6 5
c ensuring that "$<whatever>" is always output as "$<whatever>"
c when <whatever> is not a meaningful macro char
e
s 00522/00109/00239
d D 5.5 91/09/03 11:37:56 bostic 5 4
c New version from Oz Yigit; BSD-ized
e
s 00005/00003/00343
d D 5.4 91/02/26 14:05:39 bostic 4 3
c ANSI fixes, use strdup(3) instead of rolling your own
e
s 00001/00011/00345
d D 5.3 90/06/01 16:09:23 bostic 3 2
c new copyright notice
e
s 00000/00003/00356
d D 5.2 89/08/28 15:28:16 bostic 2 1
c remove vms defines
e
s 00359/00000/00000
d D 5.1 89/08/28 15:14:13 bostic 1 0
c date and time created 89/08/28 15:14:13 by bostic
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
D 8
 * Ozan Yigit.
E 8
I 8
 * Ozan Yigit at York University.
E 8
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * eval.c
 * Facility: m4 macro processor
 * by: oz
 */

I 5
#include <sys/types.h>
#include <errno.h>
E 5
I 4
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 4
#include "mdef.h"
D 5
#include "extr.h"
E 5
I 5
#include "stdd.h"
#include "extern.h"
#include "pathnames.h"
E 5

D 5
extern ndptr lookup();
D 4
extern char *strsave();
extern char *mktemp();
E 4

E 5
/*
 * eval - evaluate built-in macros.
 *	  argc - number of elements in argv.
 *	  argv - element vector :
 *			argv[0] = definition of a user
 *				  macro or nil if built-in.
 *			argv[1] = name of the macro or
 *				  built-in.
 *			argv[2] = parameters to user-defined
 *			   .	  macro or built-in.
 *			   .
 *
 * Note that the minimum value for argc is 3. A call in the form
 * of macro-or-builtin() will result in:
 *			argv[0] = nullstr
 *			argv[1] = macro-or-builtin
 *			argv[2] = nullstr
D 5
 *
E 5
 */

D 5
eval (argv, argc, td)
E 5
I 5
void
eval(argv, argc, td)
E 5
register char *argv[];
register int argc;
D 5
register int  td;
E 5
I 5
register int td;
E 5
{
	register int c, n;
D 5
	static int sysval;
E 5
I 5
	static int sysval = 0;
E 5

#ifdef DEBUG
	printf("argc = %d\n", argc);
	for (n = 0; n < argc; n++)
		printf("argv[%d] = %s\n", n, argv[n]);
#endif
D 5
	/*
	 * if argc == 3 and argv[2] is null,
	 * then we have macro-or-builtin() type call.
	 * We adjust argc to avoid further checking..
	 *
	 */
E 5
I 5
 /*
  * if argc == 3 and argv[2] is null, then we
  * have macro-or-builtin() type call. We adjust
  * argc to avoid further checking..
  */
E 5
	if (argc == 3 && !*(argv[2]))
		argc--;

	switch (td & ~STATIC) {

	case DEFITYPE:
		if (argc > 2)
			dodefine(argv[2], (argc > 3) ? argv[3] : null);
		break;

	case PUSDTYPE:
		if (argc > 2)
			dopushdef(argv[2], (argc > 3) ? argv[3] : null);
		break;

	case DUMPTYPE:
		dodump(argv, argc);
		break;

	case EXPRTYPE:
D 5
		/*
		 * doexpr - evaluate arithmetic expression
		 *
		 */
E 5
I 5
	/*
	 * doexpr - evaluate arithmetic
	 * expression
	 */
E 5
		if (argc > 2)
			pbnum(expr(argv[2]));
		break;

	case IFELTYPE:
		if (argc > 4)
			doifelse(argv, argc);
		break;

	case IFDFTYPE:
D 5
		/*
		 * doifdef - select one of two alternatives based
		 *	     on the existence of another definition
		 */
E 5
I 5
	/*
	 * doifdef - select one of two
	 * alternatives based on the existence of
	 * another definition
	 */
E 5
		if (argc > 3) {
			if (lookup(argv[2]) != nil)
				pbstr(argv[3]);
			else if (argc > 4)
				pbstr(argv[4]);
		}
		break;

	case LENGTYPE:
D 5
		/*
		 * dolen - find the length of the argument
		 *
		 */
E 5
I 5
	/*
	 * dolen - find the length of the
	 * argument
	 */
E 5
		if (argc > 2)
			pbnum((argc > 2) ? strlen(argv[2]) : 0);
		break;

	case INCRTYPE:
D 5
		/*
		 * doincr - increment the value of the argument
		 *
		 */
E 5
I 5
	/*
	 * doincr - increment the value of the
	 * argument
	 */
E 5
		if (argc > 2)
			pbnum(atoi(argv[2]) + 1);
		break;

	case DECRTYPE:
D 5
		/*
		 * dodecr - decrement the value of the argument
		 *
		 */
E 5
I 5
	/*
	 * dodecr - decrement the value of the
	 * argument
	 */
E 5
		if (argc > 2)
			pbnum(atoi(argv[2]) - 1);
		break;

D 2
#if unix || vms

E 2
	case SYSCTYPE:
D 5
		/*
		 * dosys - execute system command
		 *
		 */
E 5
I 5
	/*
	 * dosys - execute system command
	 */
E 5
		if (argc > 2)
			sysval = system(argv[2]);
		break;

	case SYSVTYPE:
D 5
		/*
		 * dosysval - return value of the last system call.
		 *
		 */
E 5
I 5
	/*
	 * dosysval - return value of the last
	 * system call.
	 * 
	 */
E 5
		pbnum(sysval);
		break;
D 2
#endif
E 2

	case INCLTYPE:
		if (argc > 2)
D 5
			if (!doincl(argv[2])) {
				fprintf(stderr,"m4: %s: ",argv[2]);
				error("cannot open for read.");
			}
E 5
I 5
			if (!doincl(argv[2]))
				oops("%s: %s", argv[2], strerror(errno));
E 5
		break;

	case SINCTYPE:
		if (argc > 2)
			(void) doincl(argv[2]);
		break;
#ifdef EXTENDED
	case PASTTYPE:
		if (argc > 2)
D 5
			if (!dopaste(argv[2])) {
				fprintf(stderr,"m4: %s: ",argv[2]);
				error("cannot open for read.");
			}
E 5
I 5
			if (!dopaste(argv[2]))
				oops("%s: %s", argv[2], strerror(errno));
E 5
		break;

	case SPASTYPE:
		if (argc > 2)
			(void) dopaste(argv[2]);
		break;
#endif
	case CHNQTYPE:
		dochq(argv, argc);
		break;

	case CHNCTYPE:
		dochc(argv, argc);
		break;

	case SUBSTYPE:
D 5
		/*
		 * dosub - select substring
		 *
		 */
E 5
I 5
	/*
	 * dosub - select substring
	 * 
	 */
E 5
		if (argc > 3)
D 5
			dosub(argv,argc);
E 5
I 5
			dosub(argv, argc);
E 5
		break;

	case SHIFTYPE:
D 5
		/*
		 * doshift - push back all arguments except the
		 *	     first one (i.e. skip argv[2])
		 */
E 5
I 5
	/*
	 * doshift - push back all arguments
	 * except the first one (i.e. skip
	 * argv[2])
	 */
E 5
		if (argc > 3) {
D 5
			for (n = argc-1; n > 3; n--) {
E 5
I 5
			for (n = argc - 1; n > 3; n--) {
E 5
				putback(rquote);
				pbstr(argv[n]);
				putback(lquote);
				putback(',');
			}
			putback(rquote);
			pbstr(argv[3]);
			putback(lquote);
		}
		break;

	case DIVRTYPE:
		if (argc > 2 && (n = atoi(argv[2])) != 0)
			dodiv(n);
		else {
			active = stdout;
			oindex = 0;
		}
		break;

	case UNDVTYPE:
		doundiv(argv, argc);
		break;

	case DIVNTYPE:
D 5
		/*
		 * dodivnum - return the number of current
		 * output diversion
		 *
		 */
E 5
I 5
	/*
	 * dodivnum - return the number of
	 * current output diversion
	 */
E 5
		pbnum(oindex);
		break;

	case UNDFTYPE:
D 5
		/*
		 * doundefine - undefine a previously defined
		 *		macro(s) or m4 keyword(s).
		 */
E 5
I 5
	/*
	 * doundefine - undefine a previously
	 * defined macro(s) or m4 keyword(s).
	 */
E 5
		if (argc > 2)
			for (n = 2; n < argc; n++)
				remhash(argv[n], ALL);
		break;

	case POPDTYPE:
D 5
		/*
		 * dopopdef - remove the topmost definitions of
		 *	      macro(s) or m4 keyword(s).
		 */
E 5
I 5
	/*
	 * dopopdef - remove the topmost
	 * definitions of macro(s) or m4
	 * keyword(s).
	 */
E 5
		if (argc > 2)
			for (n = 2; n < argc; n++)
				remhash(argv[n], TOP);
		break;

	case MKTMTYPE:
D 5
		/*
		 * dotemp - create a temporary file
		 *
		 */
E 5
I 5
	/*
	 * dotemp - create a temporary file
	 */
E 5
		if (argc > 2)
			pbstr(mktemp(argv[2]));
		break;

	case TRNLTYPE:
D 5
		/*
		 * dotranslit - replace all characters in the
		 *		source string that appears in
		 *		the "from" string with the corresponding
		 *		characters in the "to" string.
		 *
		 */
E 5
I 5
	/*
	 * dotranslit - replace all characters in
	 * the source string that appears in the
	 * "from" string with the corresponding
	 * characters in the "to" string.
	 */
E 5
		if (argc > 3) {
			char temp[MAXTOK];
			if (argc > 4)
				map(temp, argv[2], argv[3], argv[4]);
			else
				map(temp, argv[2], argv[3], null);
			pbstr(temp);
		}
D 5
		else
		    if (argc > 2)
E 5
I 5
		else if (argc > 2)
E 5
			pbstr(argv[2]);
		break;

	case INDXTYPE:
D 5
		/*
		 * doindex - find the index of the second argument
		 *	     string in the first argument string.
		 *	     -1 if not present.
		 */
E 5
I 5
	/*
	 * doindex - find the index of the second
	 * argument string in the first argument
	 * string. -1 if not present.
	 */
E 5
		pbnum((argc > 3) ? indx(argv[2], argv[3]) : -1);
		break;

	case ERRPTYPE:
D 5
		/*
		 * doerrp - print the arguments to stderr file
		 *
		 */
E 5
I 5
	/*
	 * doerrp - print the arguments to stderr
	 * file
	 */
E 5
		if (argc > 2) {
			for (n = 2; n < argc; n++)
D 5
				fprintf(stderr,"%s ", argv[n]);
E 5
I 5
				fprintf(stderr, "%s ", argv[n]);
E 5
			fprintf(stderr, "\n");
		}
		break;

	case DNLNTYPE:
D 5
		/*
		 * dodnl - eat-up-to and including newline
		 *
		 */
E 5
I 5
	/*
	 * dodnl - eat-up-to and including
	 * newline
	 */
E 5
		while ((c = gpbc()) != '\n' && c != EOF)
			;
		break;

	case M4WRTYPE:
D 5
		/*
		 * dom4wrap - set up for wrap-up/wind-down activity
		 *
		 */
D 4
		m4wraps = (argc > 2) ? strsave(argv[2]) : null;
E 4
I 4
		m4wraps = (argc > 2) ? strdup(argv[2]) : null;
E 5
I 5
	/*
	 * dom4wrap - set up for
	 * wrap-up/wind-down activity
	 */
		m4wraps = (argc > 2) ? xstrdup(argv[2]) : null;
E 5
E 4
		break;

	case EXITTYPE:
D 5
		/*
		 * doexit - immediate exit from m4.
		 *
		 */
E 5
I 5
	/*
	 * doexit - immediate exit from m4.
	 */
I 10
		killdiv();
E 10
E 5
		exit((argc > 2) ? atoi(argv[2]) : 0);
		break;

	case DEFNTYPE:
		if (argc > 2)
			for (n = 2; n < argc; n++)
				dodefn(argv[n]);
		break;

	default:
D 5
		error("m4: major botch in eval.");
E 5
I 5
		oops("%s: major botch.", "eval");
E 5
		break;
	}
I 5
}

char *dumpfmt = "`%s'\t`%s'\n";	       /* format string for dumpdef   */

/*
 * expand - user-defined macro expansion
 */
void
expand(argv, argc)
register char *argv[];
register int argc;
{
	register char *t;
	register char *p;
	register int n;
	register int argno;

	t = argv[0];		       /* defn string as a whole */
	p = t;
	while (*p)
		p++;
	p--;			       /* last character of defn */
	while (p > t) {
		if (*(p - 1) != ARGFLAG)
			putback(*p);
		else {
			switch (*p) {

			case '#':
				pbnum(argc - 2);
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if ((argno = *p - '0') < argc - 1)
					pbstr(argv[argno + 1]);
				break;
			case '*':
				for (n = argc - 1; n > 2; n--) {
					pbstr(argv[n]);
					putback(',');
				}
				pbstr(argv[2]);
				break;
			default:
				putback(*p);
I 6
				putback('$');
E 6
				break;
			}
			p--;
		}
		p--;
	}
	if (p == t)		       /* do last character */
		putback(*p);
}

/*
 * dodefine - install definition in the table
 */
void
dodefine(name, defn)
register char *name;
register char *defn;
{
	register ndptr p;

	if (!*name)
		oops("null definition.");
	if (STREQ(name, defn))
		oops("%s: recursive definition.", name);
	if ((p = lookup(name)) == nil)
		p = addent(name);
	else if (p->defn != null)
		free((char *) p->defn);
	if (!*defn)
		p->defn = null;
	else
		p->defn = xstrdup(defn);
	p->type = MACRTYPE;
}

/*
 * dodefn - push back a quoted definition of
 *      the given name.
 */
void
dodefn(name)
char *name;
{
	register ndptr p;

	if ((p = lookup(name)) != nil && p->defn != null) {
		putback(rquote);
		pbstr(p->defn);
		putback(lquote);
	}
}

/*
 * dopushdef - install a definition in the hash table
 *      without removing a previous definition. Since
 *      each new entry is entered in *front* of the
 *      hash bucket, it hides a previous definition from
 *      lookup.
 */
void
dopushdef(name, defn)
register char *name;
register char *defn;
{
	register ndptr p;

	if (!*name)
		oops("null definition");
	if (STREQ(name, defn))
		oops("%s: recursive definition.", name);
	p = addent(name);
	if (!*defn)
		p->defn = null;
	else
		p->defn = xstrdup(defn);
	p->type = MACRTYPE;
}

/*
 * dodumpdef - dump the specified definitions in the hash
 *      table to stderr. If nothing is specified, the entire
 *      hash table is dumped.
 */
void
dodump(argv, argc)
register char *argv[];
register int argc;
{
	register int n;
	ndptr p;

	if (argc > 2) {
		for (n = 2; n < argc; n++)
			if ((p = lookup(argv[n])) != nil)
				fprintf(stderr, dumpfmt, p->name,
					p->defn);
	}
	else {
		for (n = 0; n < HASHSIZE; n++)
			for (p = hashtab[n]; p != nil; p = p->nxtptr)
				fprintf(stderr, dumpfmt, p->name,
					p->defn);
	}
}

/*
 * doifelse - select one of two alternatives - loop.
 */
void
doifelse(argv, argc)
register char *argv[];
register int argc;
{
	cycle {
		if (STREQ(argv[2], argv[3]))
			pbstr(argv[4]);
		else if (argc == 6)
			pbstr(argv[5]);
		else if (argc > 6) {
			argv += 3;
			argc -= 3;
			continue;
		}
		break;
	}
}

/*
 * doinclude - include a given file.
 */
int
doincl(ifile)
char *ifile;
{
	if (ilevel + 1 == MAXINP)
		oops("too many include files.");
	if ((infile[ilevel + 1] = fopen(ifile, "r")) != NULL) {
		ilevel++;
I 7
		bbase[ilevel] = bufbase = bp;
E 7
		return (1);
	}
	else
		return (0);
}

#ifdef EXTENDED
/*
 * dopaste - include a given file without any
 *           macro processing.
 */
int
dopaste(pfile)
char *pfile;
{
	FILE *pf;
	register int c;

	if ((pf = fopen(pfile, "r")) != NULL) {
		while ((c = getc(pf)) != EOF)
			putc(c, active);
		(void) fclose(pf);
		return (1);
	}
	else
		return (0);
}
#endif

/*
 * dochq - change quote characters
 */
void
dochq(argv, argc)
register char *argv[];
register int argc;
{
	if (argc > 2) {
		if (*argv[2])
			lquote = *argv[2];
		if (argc > 3) {
			if (*argv[3])
				rquote = *argv[3];
		}
		else
			rquote = lquote;
	}
	else {
		lquote = LQUOTE;
		rquote = RQUOTE;
	}
}

/*
 * dochc - change comment characters
 */
void
dochc(argv, argc)
register char *argv[];
register int argc;
{
	if (argc > 2) {
		if (*argv[2])
			scommt = *argv[2];
		if (argc > 3) {
			if (*argv[3])
				ecommt = *argv[3];
		}
		else
			ecommt = ECOMMT;
	}
	else {
		scommt = SCOMMT;
		ecommt = ECOMMT;
	}
}

/*
 * dodivert - divert the output to a temporary file
 */
void
dodiv(n)
register int n;
{
	if (n < 0 || n >= MAXOUT)
		n = 0;		       /* bitbucket */
	if (outfile[n] == NULL) {
		m4temp[UNIQUE] = n + '0';
		if ((outfile[n] = fopen(m4temp, "w")) == NULL)
			oops("%s: cannot divert.", m4temp);
	}
	oindex = n;
	active = outfile[n];
}

/*
 * doundivert - undivert a specified output, or all
 *              other outputs, in numerical order.
 */
void
doundiv(argv, argc)
register char *argv[];
register int argc;
{
	register int ind;
	register int n;

	if (argc > 2) {
		for (ind = 2; ind < argc; ind++) {
			n = atoi(argv[ind]);
			if (n > 0 && n < MAXOUT && outfile[n] != NULL)
				getdiv(n);

		}
	}
	else
		for (n = 1; n < MAXOUT; n++)
			if (outfile[n] != NULL)
				getdiv(n);
}

/*
 * dosub - select substring
 */
void
dosub(argv, argc)
register char *argv[];
register int argc;
{
	register char *ap, *fc, *k;
	register int nc;

	if (argc < 5)
		nc = MAXTOK;
	else
#ifdef EXPR
		nc = expr(argv[4]);
#else
		nc = atoi(argv[4]);
#endif
	ap = argv[2];		       /* target string */
#ifdef EXPR
	fc = ap + expr(argv[3]);       /* first char */
#else
	fc = ap + atoi(argv[3]);       /* first char */
#endif
	if (fc >= ap && fc < ap + strlen(ap))
		for (k = fc + min(nc, strlen(fc)) - 1; k >= fc; k--)
			putback(*k);
}

/*
 * map:
 * map every character of s1 that is specified in from
 * into s3 and replace in s. (source s1 remains untouched)
 *
 * This is a standard implementation of map(s,from,to) function of ICON
 * language. Within mapvec, we replace every character of "from" with
 * the corresponding character in "to". If "to" is shorter than "from",
 * than the corresponding entries are null, which means that those
 * characters dissapear altogether. Furthermore, imagine
 * map(dest, "sourcestring", "srtin", "rn..*") type call. In this case,
 * `s' maps to `r', `r' maps to `n' and `n' maps to `*'. Thus, `s'
 * ultimately maps to `*'. In order to achieve this effect in an efficient
 * manner (i.e. without multiple passes over the destination string), we
 * loop over mapvec, starting with the initial source character. if the
 * character value (dch) in this location is different than the source
 * character (sch), sch becomes dch, once again to index into mapvec, until
 * the character value stabilizes (i.e. sch = dch, in other words
 * mapvec[n] == n). Even if the entry in the mapvec is null for an ordinary
 * character, it will stabilize, since mapvec[0] == 0 at all times. At the
 * end, we restore mapvec* back to normal where mapvec[n] == n for
 * 0 <= n <= 127. This strategy, along with the restoration of mapvec, is
 * about 5 times faster than any algorithm that makes multiple passes over
 * destination string.
 */
void
map(dest, src, from, to)
register char *dest;
register char *src;
register char *from;
register char *to;
{
	register char *tmp;
	register char sch, dch;
	static char mapvec[128] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
		36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
		60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
		72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
		84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
		96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107,
		108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127
	};

	if (*src) {
		tmp = from;
	/*
	 * create a mapping between "from" and
	 * "to"
	 */
		while (*from)
			mapvec[*from++] = (*to) ? *to++ : (char) 0;

		while (*src) {
			sch = *src++;
			dch = mapvec[sch];
			while (dch != sch) {
				sch = dch;
				dch = mapvec[sch];
			}
			if (*dest = dch)
				dest++;
		}
	/*
	 * restore all the changed characters
	 */
		while (*tmp) {
			mapvec[*tmp] = *tmp;
			tmp++;
		}
	}
	*dest = (char) 0;
E 5
}
E 1
