h40602
s 00005/00005/00394
d D 8.1 93/06/06 15:04:31 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00396
d D 5.12 93/05/13 16:14:37 torek 13 12
c m4 drops commas in embedded arguments - test case is
c 	define(msg, printf $1)
c 	msg(("fmt", arg));
c (from Steve McCoole's BSDI patch set)
e
s 00024/00045/00373
d D 5.11 92/06/29 13:04:05 bostic 12 11
c allow "-" as an argument to mean stdin
e
s 00030/00003/00388
d D 5.10 92/02/12 20:01:17 leres 11 10
c Don't make ilevel go negative when we test it.
e
s 00001/00001/00390
d D 5.9 91/11/20 16:27:12 bostic 10 9
c add affiliation for Oz
e
s 00005/00000/00386
d D 5.8 91/10/02 18:22:23 eric 9 8
c keep base of pushback buffer per file; this prevents pushed back
c characters from being read out of order on include directives.
e
s 00074/00147/00312
d D 5.7 91/09/03 11:38:13 bostic 8 7
c New version from Oz Yigit; BSD-ized
e
s 00001/00001/00458
d D 5.6 91/03/06 00:45:54 donn 7 5
c Don't mktemp() constant strings.
e
s 00001/00001/00458
d R 5.6 91/03/06 00:45:24 donn 6 5
c Don'
e
s 00009/00005/00450
d D 5.5 91/02/26 14:05:42 bostic 5 4
c ANSI fixes, use strdup(3) instead of rolling your own
e
s 00001/00011/00454
d D 5.4 90/06/01 16:09:45 bostic 4 3
c new copyright notice
e
s 00005/00004/00460
d D 5.3 89/09/08 14:15:42 bostic 3 2
c fix Eric's bug (divert(7)<nl>hello<nl>^D), plus minor difference for
c System V; from Ozan Yigit
e
s 00000/00012/00464
d D 5.2 89/08/28 15:52:41 bostic 2 1
c remove vms defines, leave "unix" macro def
e
s 00476/00000/00000
d D 5.1 89/08/28 15:14:20 bostic 1 0
c date and time created 89/08/28 15:14:20 by bostic
e
u
U
t
T
I 1
D 12
/*
E 12
I 12
/*-
E 12
D 14
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
D 10
 * Ozan Yigit.
E 10
I 10
 * Ozan Yigit at York University.
E 10
 *
D 4
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
E 4
I 4
D 11
 * %sccs.include.redist.c%
E 11
I 11
D 12
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
 *
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
E 4
 */

#ifndef lint
D 11
static char sccsid[] = "%W% (Berkeley) %G%";
E 11
I 11
D 12
static char sccsid[] = "@(#)main.c	5.9 (Berkeley) 11/20/91";
E 12
I 12
D 14
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 14
E 12
E 11
#endif /* not lint */

I 12
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 12
/*
 * main.c
 * Facility: m4 macro processor
 * by: oz
 */

I 8
#include <sys/types.h>
E 8
I 5
#include <signal.h>
I 8
#include <errno.h>
E 8
#include <unistd.h>
#include <stdio.h>
D 8
#include <stdlib.h>
E 8
I 8
#include <ctype.h>
E 8
#include <string.h>
E 5
#include "mdef.h"
I 8
#include "stdd.h"
#include "extern.h"
E 8
I 5
#include "pathnames.h"
E 5

D 8
/*
 * m4 - macro processor
 *
 * PD m4 is based on the macro tool distributed with the software 
 * tools (VOS) package, and described in the "SOFTWARE TOOLS" and 
 * "SOFTWARE TOOLS IN PASCAL" books. It has been expanded to include 
 * most of the command set of SysV m4, the standard UN*X macro processor.
 *
 * Since both PD m4 and UN*X m4 are based on SOFTWARE TOOLS macro,
 * there may be certain implementation similarities between
 * the two. The PD m4 was produced without ANY references to m4
 * sources.
 *
 * References:
 *
 *	Software Tools distribution: macro
 *
 *	Kernighan, Brian W. and P. J. Plauger, SOFTWARE
 *	TOOLS IN PASCAL, Addison-Wesley, Mass. 1981
 *
 *	Kernighan, Brian W. and P. J. Plauger, SOFTWARE
 *	TOOLS, Addison-Wesley, Mass. 1976
 *
 *	Kernighan, Brian W. and Dennis M. Ritchie,
 *	THE M4 MACRO PROCESSOR, Unix Programmer's Manual,
 *	Seventh Edition, Vol. 2, Bell Telephone Labs, 1979
 *
 *	System V man page for M4
 *
 * Modification History:
 *
 * Jan 28 1986 Oz	Break the whole thing into little
 *			pieces, for easier (?) maintenance.
 *
 * Dec 12 1985 Oz	Optimize the code, try to squeeze
 *			few microseconds out..
 *
 * Dec 05 1985 Oz	Add getopt interface, define (-D),
 *			undefine (-U) options.
 *
 * Oct 21 1985 Oz	Clean up various bugs, add comment handling.
 *
 * June 7 1985 Oz	Add some of SysV m4 stuff (m4wrap, pushdef,
 *			popdef, decr, shift etc.).
 *
 * June 5 1985 Oz	Initial cut.
 *
 * Implementation Notes:
 *
 * [1]	PD m4 uses a different (and simpler) stack mechanism than the one 
 *	described in Software Tools and Software Tools in Pascal books. 
 *	The triple stack nonsense is replaced with a single stack containing 
 *	the call frames and the arguments. Each frame is back-linked to a 
 * 	previous stack frame, which enables us to rewind the stack after 
 * 	each nested call is completed. Each argument is a character pointer 
 *	to the beginning of the argument string within the string space.
 *	The only exceptions to this are (*) arg 0 and arg 1, which are
 * 	the macro definition and macro name strings, stored dynamically
 *	for the hash table.
 *
 *	    .					   .
 *	|   .	|  <-- sp			|  .  |
 *	+-------+				+-----+
 *	| arg 3 ------------------------------->| str |
 *	+-------+				|  .  |
 *	| arg 2 --------------+ 		   .
 *	+-------+	      |
 *	    *		      |			|     |
 *	+-------+	      | 		+-----+
 *	| plev	|  <-- fp     +---------------->| str |
 *	+-------+				|  .  |
 *	| type	|				   .
 *	+-------+
 *	| prcf	-----------+		plev: paren level
 *	+-------+  	   |		type: call type
 *	|   .	| 	   |		prcf: prev. call frame
 *	    .	   	   |
 *	+-------+	   |
 *	|	<----------+
 *	+-------+
 *
 * [2]	We have three types of null values:
 *
 *		nil  - nodeblock pointer type 0
 *		null - null string ("")
 *		NULL - Stdio-defined NULL
 *
 */

E 8
ndptr hashtab[HASHSIZE];	/* hash table for macros etc.  */
char buf[BUFSIZE];		/* push-back buffer	       */
I 9
char *bufbase = buf;		/* the base for current ilevel */
char *bbase[MAXINP];		/* the base for each ilevel    */
E 9
char *bp = buf; 		/* first available character   */
char *endpbb = buf+BUFSIZE;	/* end of push-back buffer     */
stae mstack[STACKMAX+1]; 	/* stack of m4 machine         */
char strspace[STRSPMAX+1];	/* string space for evaluation */
char *ep = strspace;		/* first free char in strspace */
char *endest= strspace+STRSPMAX;/* end of string space	       */
int sp; 			/* current m4  stack pointer   */
int fp; 			/* m4 call frame pointer       */
FILE *infile[MAXINP];		/* input file stack (0=stdin)  */
FILE *outfile[MAXOUT];		/* diversion array(0=bitbucket)*/
FILE *active;			/* active output file pointer  */
char *m4temp;			/* filename for diversions     */
int ilevel = 0; 		/* input file stack pointer    */
int oindex = 0; 		/* diversion index..	       */
char *null = "";                /* as it says.. just a null..  */
char *m4wraps = "";             /* m4wrap string default..     */
I 8
char *progname;			/* name of this program        */
E 8
char lquote = LQUOTE;		/* left quote character  (`)   */
char rquote = RQUOTE;		/* right quote character (')   */
char scommt = SCOMMT;		/* start character for comment */
char ecommt = ECOMMT;		/* end character for comment   */
I 8

E 8
struct keyblk keywrds[] = {	/* m4 keywords to be installed */
	"include",      INCLTYPE,
	"sinclude",     SINCTYPE,
	"define",       DEFITYPE,
	"defn",         DEFNTYPE,
	"divert",       DIVRTYPE,
	"expr",         EXPRTYPE,
	"eval",         EXPRTYPE,
	"substr",       SUBSTYPE,
	"ifelse",       IFELTYPE,
	"ifdef",        IFDFTYPE,
	"len",          LENGTYPE,
	"incr",         INCRTYPE,
	"decr",         DECRTYPE,
	"dnl",          DNLNTYPE,
	"changequote",  CHNQTYPE,
	"changecom",    CHNCTYPE,
	"index",        INDXTYPE,
#ifdef EXTENDED
	"paste",        PASTTYPE,
	"spaste",       SPASTYPE,
#endif
	"popdef",       POPDTYPE,
	"pushdef",      PUSDTYPE,
	"dumpdef",      DUMPTYPE,
	"shift",        SHIFTYPE,
	"translit",     TRNLTYPE,
	"undefine",     UNDFTYPE,
	"undivert",     UNDVTYPE,
	"divnum",       DIVNTYPE,
	"maketemp",     MKTMTYPE,
	"errprint",     ERRPTYPE,
	"m4wrap",       M4WRTYPE,
	"m4exit",       EXITTYPE,
D 2
#if unix || vms
E 2
	"syscmd",       SYSCTYPE,
	"sysval",       SYSVTYPE,
I 8

#ifdef unix
E 8
D 2
#endif
#if unix
E 2
	"unix",         MACRTYPE,
I 8
#else
#ifdef vms
	"vms",          MACRTYPE,
#endif
#endif
E 8
D 2
#else
#if vms
	"vms",          MACRTYPE,
#endif
#endif
E 2
};

#define MAXKEYS	(sizeof(keywrds)/sizeof(struct keyblk))

D 8
extern ndptr lookup();
extern ndptr addent();
D 5
extern int onintr();
E 5
I 5
extern void onintr();
E 5

E 8
D 5
extern char *malloc();
extern char *mktemp();

E 5
extern int optind;
extern char *optarg;

I 8
void macro();
void initkwds();
extern int getopt();

int
E 8
main(argc,argv)
D 5
char *argv[];
E 5
I 5
D 8
	int argc;
	char **argv;
E 8
I 8
D 12
int argc;
char *argv[];
E 12
I 12
	int argc;
	char *argv[];
E 12
E 8
E 5
{
	register int c;
	register int n;
	char *p;
I 8
	register FILE *ifp;
E 8

I 8
	progname = basename(argv[0]);

E 8
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, onintr);
D 8
#ifdef NONZEROPAGES
	initm4();
#endif
E 8
I 8

E 8
	initkwds();

	while ((c = getopt(argc, argv, "tD:U:o:")) != EOF)
		switch(c) {

		case 'D':               /* define something..*/
			for (p = optarg; *p; p++)
				if (*p == '=')
					break;
			if (*p)
				*p++ = EOS;
			dodefine(optarg, p);
			break;
		case 'U':               /* undefine...       */
			remhash(optarg, TOP);
			break;
		case 'o':		/* specific output   */
		case '?':
D 8
		default:
E 8
			usage();
		}

D 8
	infile[0] = stdin;		/* default input (naturally) */
E 8
I 8
        argc -= optind;
        argv += optind;

E 8
	active = stdout;		/* default active output     */
D 7
	m4temp = mktemp(DIVNAM);	/* filename for diversions   */
E 7
I 7
D 8
	m4temp = mktemp(strdup(DIVNAM));/* filename for diversions   */
E 8
I 8
					/* filename for diversions   */
	m4temp = mktemp(xstrdup(_PATH_DIVNAME));
E 8
E 7

I 9
	bbase[0] = bufbase;
E 9
D 8
	sp = -1;			/* stack pointer initialized */
	fp = 0; 			/* frame pointer initialized */
E 8
I 8
        if (!argc) {
 		sp = -1;		/* stack pointer initialized */
		fp = 0; 		/* frame pointer initialized */
		infile[0] = stdin;	/* default input (naturally) */
		macro();
D 12
	}
        else
                while (argc--) {
                        if ((ifp = fopen(*argv, "r")) == NULL)
                                oops("%s: %s", *argv, strerror(errno));
                        else {
				sp = -1;
				fp = 0; 
				infile[0] = ifp;
				macro();
				(void) fclose(ifp);
			}
                        argv++;
E 12
I 12
	} else
		for (; argc--; ++argv) {
			p = *argv;
			if (p[0] == '-' && p[1] == '\0')
				ifp = stdin;
			else if ((ifp = fopen(p, "r")) == NULL)
				oops("%s: %s", p, strerror(errno));
			sp = -1;
			fp = 0; 
			infile[0] = ifp;
			macro();
			if (ifp != stdin)
				(void)fclose(ifp);
E 12
		}
E 8
D 12

E 12
D 8
	macro();			/* get some work done here   */
E 8

	if (*m4wraps) { 		/* anything for rundown ??   */
		ilevel = 0;		/* in case m4wrap includes.. */
I 9
		bufbase = bp = buf;	/* use the entire buffer   */
E 9
		putback(EOF);		/* eof is a must !!	     */
		pbstr(m4wraps); 	/* user-defined wrapup act   */
		macro();		/* last will and testament   */
	}
D 3
	else				/* default wrap-up: undivert */
		for (n = 1; n < MAXOUT; n++)
			if (outfile[n] != NULL)
				getdiv(n);
E 3

I 3
	if (active != stdout)
		active = stdout;	/* reset output just in case */
	for (n = 1; n < MAXOUT; n++)	/* default wrap-up: undivert */
		if (outfile[n] != NULL)
			getdiv(n);
E 3
					/* remove bitbucket if used  */
	if (outfile[0] != NULL) {
		(void) fclose(outfile[0]);
		m4temp[UNIQUE] = '0';
I 8
#ifdef vms
		(void) remove(m4temp);
#else
E 8
D 2
#if vms
		(void) remove(m4temp);
#else
E 2
		(void) unlink(m4temp);
I 8
#endif
E 8
D 2
#endif
E 2
	}

D 8
	exit(0);
E 8
I 8
	return 0;
E 8
}

D 8
ndptr inspect();	/* forward ... */
E 8
I 8
ndptr inspect();
E 8

/*
 * macro - the work horse..
D 8
 *
E 8
 */
I 8
void
E 8
macro() {
	char token[MAXTOK];
	register char *s;
	register int t, l;
	register ndptr p;
	register int  nlpar;

	cycle {
		if ((t = gpbc()) == '_' || isalpha(t)) {
			putback(t);
			if ((p = inspect(s = token)) == nil) {
				if (sp < 0)
					while (*s)
						putc(*s++, active);
				else
					while (*s)
						chrsave(*s++);
			}
			else {
		/*
		 * real thing.. First build a call frame:
D 8
		 *
E 8
		 */
				pushf(fp);	/* previous call frm */
				pushf(p->type); /* type of the call  */
				pushf(0);	/* parenthesis level */
				fp = sp;	/* new frame pointer */
		/*
		 * now push the string arguments:
D 8
		 *
E 8
		 */
				pushs(p->defn);	      /* defn string */
				pushs(p->name);	      /* macro name  */
				pushs(ep);	      /* start next..*/

				putback(l = gpbc());
				if (l != LPAREN)  {   /* add bracks  */
					putback(RPAREN);
					putback(LPAREN);
				}
			}
		}
		else if (t == EOF) {
			if (sp > -1)
D 8
				error("m4: unexpected end of input");
E 8
I 8
				oops("unexpected end of input", "");
E 8
D 11
			if (--ilevel < 0)
E 11
I 11
			if (ilevel <= 0)
E 11
				break;			/* all done thanks.. */
I 11
			--ilevel;
E 11
			(void) fclose(infile[ilevel+1]);
I 9
			bufbase = bbase[ilevel];
E 9
			continue;
		}
	/*
	 * non-alpha single-char token seen..
D 8
	 * [the order of else if .. stmts is
	 * important.]
	 *
E 8
I 8
	 * [the order of else if .. stmts is important.]
E 8
	 */
		else if (t == lquote) { 		/* strip quotes */
			nlpar = 1;
			do {
				if ((l = gpbc()) == rquote)
					nlpar--;
				else if (l == lquote)
					nlpar++;
				else if (l == EOF)
D 8
					error("m4: missing right quote");
E 8
I 8
					oops("missing right quote", "");
E 8
				if (nlpar > 0) {
					if (sp < 0)
						putc(l, active);
					else
						chrsave(l);
				}
			}
			while (nlpar != 0);
		}

		else if (sp < 0) {		/* not in a macro at all */
			if (t == scommt) {	/* comment handling here */
				putc(t, active);
				while ((t = gpbc()) != ecommt)
					putc(t, active);
			}
			putc(t, active);	/* output directly..	 */
		}

		else switch(t) {

		case LPAREN:
			if (PARLEV > 0)
				chrsave(t);
			while (isspace(l = gpbc()))
				;		/* skip blank, tab, nl.. */
			putback(l);
			PARLEV++;
			break;

		case RPAREN:
			if (--PARLEV > 0)
				chrsave(t);
			else {			/* end of argument list */
				chrsave(EOS);

				if (sp == STACKMAX)
D 8
					error("m4: internal stack overflow");
E 8
I 8
					oops("internal stack overflow", "");
E 8

				if (CALTYP == MACRTYPE)
D 8
					expand(mstack+fp+1, sp-fp);
E 8
I 8
					expand((char **) mstack+fp+1, sp-fp);
E 8
				else
D 8
					eval(mstack+fp+1, sp-fp, CALTYP);
E 8
I 8
					eval((char **) mstack+fp+1, sp-fp, CALTYP);
E 8

				ep = PREVEP;	/* flush strspace */
				sp = PREVSP;	/* previous sp..  */
				fp = PREVFP;	/* rewind stack...*/
			}
			break;

		case COMMA:
D 8
			if (PARLEV == 1)	{
E 8
I 8
			if (PARLEV == 1) {
E 8
				chrsave(EOS);		/* new argument   */
				while (isspace(l = gpbc()))
					;
				putback(l);
				pushs(ep);
D 13
			}
E 13
I 13
			} else
				chrsave(t);
E 13
			break;
I 13

E 13
		default:
			chrsave(t);			/* stack the char */
			break;
		}
	}
}

D 8

E 8
/*
 * build an input token..
 * consider only those starting with _ or A-Za-z. This is a
 * combo with lookup to speed things up.
 */
ndptr
inspect(tp) 
register char *tp;
{
D 8
	register int h = 0;
E 8
	register char c;
	register char *name = tp;
	register char *etp = tp+MAXTOK;
	register ndptr p;
I 8
	register unsigned long h = 0;
E 8

D 8
	while (tp < etp && (isalnum(c = gpbc()) || c == '_'))
		h += (*tp++ = c);
E 8
I 8
	while ((isalnum(c = gpbc()) || c == '_') && tp < etp)
		h = (h << 5) + h + (*tp++ = c);
E 8
	putback(c);
	if (tp == etp)
D 8
		error("m4: token too long");
E 8
I 8
		oops("token too long", "");

E 8
	*tp = EOS;
I 8

E 8
	for (p = hashtab[h%HASHSIZE]; p != nil; p = p->nxtptr)
D 8
		if (strcmp(name, p->name) == 0)
E 8
I 8
		if (STREQ(name, p->name))
E 8
			break;
D 8
	return(p);
E 8
I 8
	return p;
E 8
}

D 8
#ifdef NONZEROPAGES
E 8
/*
D 8
 * initm4 - initialize various tables. Useful only if your system 
 * does not know anything about demand-zero pages.
 *
 */
initm4()
{
	register int i;

	for (i = 0; i < HASHSIZE; i++)
		hashtab[i] = nil;
	for (i = 0; i < MAXOUT; i++)
		outfile[i] = NULL;
}
#endif

/*
E 8
 * initkwds - initialise m4 keywords as fast as possible. 
 * This very similar to install, but without certain overheads,
 * such as calling lookup. Malloc is not used for storing the 
 * keyword strings, since we simply use the static  pointers
D 8
 * within keywrds block. We also assume that there is enough memory 
 * to at least install the keywords (i.e. malloc won't fail).
 *
E 8
I 8
 * within keywrds block.
E 8
 */
I 8
void
E 8
initkwds() {
	register int i;
	register int h;
	register ndptr p;

	for (i = 0; i < MAXKEYS; i++) {
		h = hash(keywrds[i].knam);
D 8
		p = (ndptr) malloc(sizeof(struct ndblock));
E 8
I 8
		p = (ndptr) xalloc(sizeof(struct ndblock));
E 8
		p->nxtptr = hashtab[h];
		hashtab[h] = p;
		p->name = keywrds[i].knam;
		p->defn = null;
		p->type = keywrds[i].ktyp | STATIC;
	}
}
E 1
