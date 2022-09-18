h35081
s 00042/00008/00408
d D 8.2 95/05/04 17:59:44 christos 8 7
c 
e
s 00002/00002/00414
d D 8.1 93/05/31 15:31:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00000/00402
d D 5.2 93/05/31 15:31:48 bostic 6 5
c add an SCCS/copyright header
e
s 00003/00000/00399
d D 5.1 92/12/01 00:34:56 bostic 5 4
c fc without arguments dereferences argv[1]; from Christos
e
s 00001/00001/00398
d D 1.4 92/07/16 13:56:39 marc 4 3
c history search goes other way now
e
s 00002/00002/00397
d D 1.3 92/07/15 10:29:25 marc 3 2
c lookupvar -> bltinlookup inside fc command
e
s 00317/00009/00082
d D 1.2 92/07/15 10:03:01 marc 2 1
c fc command (history)
e
s 00091/00000/00000
d D 1.1 92/06/03 17:58:45 marc 1 0
c date and time created 92/06/03 17:58:45 by marc
e
u
U
t
T
I 6
/*-
D 7
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 6
I 1
D 8
/*
 * Editline and history functions (and glue).
 */
E 8
I 2
#include <sys/param.h>
#include <paths.h>
E 2
#include <stdio.h>
I 8
#include <stdlib.h>
#include <unistd.h>
/*
 * Editline and history functions (and glue).
 */
E 8
I 2
#include "shell.h"
E 2
#include "parser.h"
I 2
#include "var.h"
E 2
#include "options.h"
I 8
#include "main.h"
#include "output.h"
E 8
I 2
#include "mystring.h"
I 8
#ifndef NO_HISTORY
#include "myhistedit.h"
#endif
E 8
E 2
#include "error.h"
D 2

E 2
D 8
#include "histedit.h"
E 8
I 8
#include "eval.h"
E 8
I 2
#include "memalloc.h"
E 2

I 2
#define MAXHISTLOOPS	4	/* max recursions through fc */
#define DEFEDITOR	"ed"	/* default editor *should* be $EDITOR */

E 2
History *hist;	/* history cookie */
EditLine *el;	/* editline cookie */
I 2
int displayhist;
E 2
static FILE *el_in, *el_out;

D 2
extern int is_interactive;
E 2
I 2
STATIC char *fc_replace __P((const char *, char *, char *));
E 2

/*
 * Set history and editing status.  Called whenever the status may
 * have changed (figures out what to do).
 */
D 8
histedit() {
E 8
I 8
void
histedit() 
{
E 8

D 2
	if (is_interactive) {
E 2
I 2
#define editing (Eflag || Vflag)

	if (iflag) {
E 2
		if (!hist) {
			/*
			 * turn history on
			 */
			INTOFF;
			hist = history_init();
			INTON;

			if (hist != NULL)
				sethistsize();
			else
				out2str("sh: can't initialize history\n");
		}
D 2
		if (Eflag && !el && isatty(0)) { /* && isatty(2) ??? */
E 2
I 2
		if (editing && !el && isatty(0)) { /* && isatty(2) ??? */
E 2
			/*
			 * turn editing on
			 */
			INTOFF;
			if (el_in == NULL)
				el_in = fdopen(0, "r");
			if (el_out == NULL)
				el_out = fdopen(2, "w");
			if (el_in == NULL || el_out == NULL)
				goto bad;
			el = el_init(arg0, el_in, el_out);
			if (el != NULL) {
				if (hist)
D 2
					el_set(el, EL_HIST, history_set, hist);
E 2
I 2
					el_set(el, EL_HIST, history, hist);
E 2
				el_set(el, EL_PROMPT, getprompt);
			} else {
bad:
				out2str("sh: can't initialize editing\n");
			}
			INTON;
D 2
			if (el)	/* XXX - -o vi etc... */
				el_set(el, EL_EDITOR, "vi");
		} else if (!Eflag && el) {
E 2
I 2
		} else if (!editing && el) {
E 2
			INTOFF;
			el_end(el);
			el = NULL;
			INTON;
		}
I 2
		if (el) {
			if (Vflag)
				el_set(el, EL_EDITOR, "vi");
			else if (Eflag)
				el_set(el, EL_EDITOR, "emacs");
		}
E 2
	} else {
		INTOFF;
		if (el) {	/* no editing if not interactive */
			el_end(el);
			el = NULL;
		}
		if (hist) {
			history_end(hist);
			hist = NULL;
		}
		INTON;
	}
}

D 8
sethistsize() {
E 8
I 8

void
sethistsize()
{
E 8
	char *cp;
	int histsize;

	if (hist != NULL) {
		cp = lookupvar("HISTSIZE");
		if (cp == NULL || *cp == '\0' || 
		   (histsize = atoi(cp)) < 0)
			histsize = 100;
D 2
		history_set(hist, H_EVENT, histsize);
E 2
I 2
		history(hist, H_EVENT, histsize);
E 2
	}
I 2
}

/*
 *  This command is provided since POSIX decided to standardize
 *  the Korn shell fc command.  Oh well...
 */
I 8
int
E 8
histcmd(argc, argv)
D 8
	char *argv[];
E 8
I 8
	int argc;
	char **argv;
E 8
{
	extern char *optarg;
	extern int optind, optopt, optreset;
	int ch;
	char *editor = NULL;
	const HistEvent *he;
	int lflg = 0, nflg = 0, rflg = 0, sflg = 0;
	int i;
	char *firststr, *laststr;
	int first, last, direction;
	char *pat = NULL, *repl;	/* ksh "fc old=new" crap */
	static int active = 0;
	struct jmploc jmploc;
	struct jmploc *volatile savehandler;
	char editfile[MAXPATHLEN + 1];
	FILE *efp;
I 8
#ifdef __GNUC__
	/* Avoid longjmp clobbering */
	(void) &editor;
	(void) &lflg;
	(void) &nflg;
	(void) &rflg;
	(void) &sflg;
	(void) &firststr;
	(void) &laststr;
	(void) &pat;
	(void) &repl;
	(void) &efp;
	(void) &argc;
	(void) &argv;
#endif
E 8

	if (hist == NULL)
		error("history not active");
I 5
	
	if (argc == 1)
		error("missing history argument");
E 5

	optreset = 1; optind = 1; /* initialize getopt */
	while (not_fcnumber(argv[optind]) &&
	      (ch = getopt(argc, argv, ":e:lnrs")) != EOF)
		switch ((char)ch) {
		case 'e':
			editor = optarg;
			break;
		case 'l':
			lflg = 1;
			break;
		case 'n':
			nflg = 1;
			break;
		case 'r':
			rflg = 1;
			break;
		case 's':
			sflg = 1;
			break;
		case ':':
			error("option -%c expects argument", optopt);
		case '?':
		default:
			error("unknown option: -%c", optopt);
		}
	argc -= optind, argv += optind;

	/*
	 * If executing...
	 */
	if (lflg == 0 || editor || sflg) {
		lflg = 0;	/* ignore */
		editfile[0] = '\0';
		/*
		 * Catch interrupts to reset active counter and
		 * cleanup temp files.
		 */
		if (setjmp(jmploc.loc)) {
			active = 0;
			if (*editfile)
				unlink(editfile);
			handler = savehandler;
			longjmp(handler->loc, 1);
		}
		savehandler = handler;
		handler = &jmploc;
		if (++active > MAXHISTLOOPS) {
			active = 0;
			displayhist = 0;
			error("called recursively too many times");
		}
		/*
		 * Set editor.
		 */
		if (sflg == 0) {
			if (editor == NULL &&
D 3
			    (editor = lookupvar("FCEDIT")) == NULL &&
			    (editor = lookupvar("EDITOR")) == NULL)
E 3
I 3
			    (editor = bltinlookup("FCEDIT", 1)) == NULL &&
			    (editor = bltinlookup("EDITOR", 1)) == NULL)
E 3
				editor = DEFEDITOR;
			if (editor[0] == '-' && editor[1] == '\0') {
				sflg = 1;	/* no edit */
				editor = NULL;
			}
		}
	}

	/*
	 * If executing, parse [old=new] now
	 */
	if (lflg == 0 && argc > 0 && 
	     ((repl = strchr(argv[0], '=')) != NULL)) {
		pat = argv[0];
		*repl++ = '\0';
		argc--, argv++;
	}
	/*
	 * determine [first] and [last]
	 */
	switch (argc) {
	case 0:
		firststr = lflg ? "-16" : "-1";
		laststr = "-1";
		break;
	case 1:
		firststr = argv[0];
		laststr = lflg ? "-1" : argv[0];
		break;
	case 2:
		firststr = argv[0];
		laststr = argv[1];
		break;
	default:
		error("too many args");
	}
	/*
	 * Turn into event numbers.
	 */
	first = str_to_event(firststr, 0);
	last = str_to_event(laststr, 1);

	if (rflg) {
		i = last;
		last = first;
		first = i;
	}
	/*
	 * XXX - this should not depend on the event numbers
	 * always increasing.  Add sequence numbers or offset 
	 * to the history element in next (diskbased) release.
	 */
	direction = first < last ? H_PREV : H_NEXT;

	/*
	 * If editing, grab a temp file.
	 */
	if (editor) {
		int fd;
		INTOFF;		/* easier */
		sprintf(editfile, "%s/_shXXXXXX", _PATH_TMP);
		if ((fd = mkstemp(editfile)) < 0)
			error("can't create temporary file %s", editfile);
		if ((efp = fdopen(fd, "w")) == NULL) {
			close(fd);
			error("can't allocate stdio buffer for temp\n");
		}
	}

	/*
	 * Loop through selected history events.  If listing or executing,
	 * do it now.  Otherwise, put into temp file and call the editor
	 * after.
	 *
	 * The history interface needs rethinking, as the following
	 * convolutions will demonstrate.
	 */
	history(hist, H_FIRST);
	he = history(hist, H_NEXT_EVENT, first);
	for (;he != NULL; he = history(hist, direction)) {
		if (lflg) {
			if (!nflg)
				out1fmt("%5d ", he->num);
			out1str(he->str);
		} else {
			char *s = pat ? 
			   fc_replace(he->str, pat, repl) : (char *)he->str;

			if (sflg) {
				if (displayhist) {
					out2str(s);
				}
				evalstring(s);
				if (displayhist && hist) {
					/*
					 *  XXX what about recursive and 
					 *  relative histnums.
					 */
					history(hist, H_ENTER, s);
				}
			} else
				fputs(s, efp);
		}
		/*
		 * At end?  (if we were to loose last, we'd sure be
		 * messed up).
		 */
		if (he->num == last)
			break;
	}
	if (editor) {
		char *editcmd;

		fclose(efp);
		editcmd = stalloc(strlen(editor) + strlen(editfile) + 2);
		sprintf(editcmd, "%s %s", editor, editfile);
		evalstring(editcmd);	/* XXX - should use no JC command */
		INTON;
		readcmdfile(editfile);	/* XXX - should read back - quick tst */
		unlink(editfile);
	}
		
	if (lflg == 0 && active > 0)
		--active;
	if (displayhist)
		displayhist = 0;
I 8
	return 0;
E 8
}

STATIC char *
fc_replace(s, p, r)
	const char *s;
	char *p, *r;
{
	char *dest;
	int plen = strlen(p);

	STARTSTACKSTR(dest);
	while (*s) {
		if (*s == *p && strncmp(s, p, plen) == 0) {
			while (*r)
				STPUTC(*r++, dest);
			s += plen;
			*p = '\0';	/* so no more matches */
		} else
			STPUTC(*s++, dest);
	}
	STACKSTRNUL(dest);
	dest = grabstackstr(dest);

	return (dest);
}

I 8
int
E 8
not_fcnumber(s)
        char *s;
{
I 8
	if (s == NULL)
		return 0;
E 8
        if (*s == '-')
                s++;
	return (!is_number(s));
}

I 8
int
E 8
str_to_event(str, last)
	char *str;
	int last;
{
	const HistEvent *he;
	char *s = str;
	int relative = 0;
D 8
	int i, j;
E 8
I 8
	int i;
E 8

	he = history(hist, H_FIRST);
	switch (*s) {
	case '-':
		relative = 1;
		/*FALLTHROUGH*/
	case '+':
		s++;
	}
	if (is_number(s)) {
		i = atoi(s);
		if (relative) {
			while (he != NULL && i--) {
				he = history(hist, H_NEXT);
			}
			if (he == NULL)
				he = history(hist, H_LAST);
		} else {
			he = history(hist, H_NEXT_EVENT, i);
			if (he == NULL) {
				/*
				 * the notion of first and last is
				 * backwards to that of the history package
				 */
				he = history(hist, last ? H_FIRST : H_LAST);
			}
		}
		if (he == NULL)
			error("history number %s not found (internal error)",
			       str);
	} else {
		/*
		 * pattern 
		 */
D 4
		he = history(hist, H_NEXT_STR, str);
E 4
I 4
		he = history(hist, H_PREV_STR, str);
E 4
		if (he == NULL)
			error("history pattern not found: %s", str);
	}
	return (he->num);
E 2
}
E 1
