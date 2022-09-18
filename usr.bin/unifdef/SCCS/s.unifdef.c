h19176
s 00005/00005/00607
d D 8.1 93/06/06 16:40:41 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00611
d D 4.7 90/06/01 16:11:55 bostic 7 6
c new copyright notice
e
s 00228/00186/00394
d D 4.6 88/12/14 14:50:50 bostic 6 5
c new versions from Dave Yost (grand!day@uunet.UU.NET)
e
s 00025/00001/00552
d D 4.5 88/12/13 18:42:35 bostic 5 4
c written by Dave Yost; add Berkeley specific copyright
e
s 00006/00008/00547
d D 4.4 83/08/11 21:31:35 sam 4 3
c standardize sccs keyword lines
e
s 00005/00005/00550
d D 4.3 83/07/02 23:19:39 sam 3 2
c make options conform to cpp
e
s 00001/00001/00554
d D 4.2 83/04/29 00:28:40 mckusick 2 1
c added perror
e
s 00555/00000/00000
d D 4.1 82/10/22 00:11:51 mckusick 1 0
c date and time created 82/10/22 00:11:51 by mckusick
e
u
U
t
T
I 5
/*
D 8
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Dave Yost.
 *
D 7
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

E 5
I 1
D 4
/* Copyright (c) 1982 Regents of the University of California */

static char sccsid[] = "%W%	(Berkeley)	%G%";

#ifdef COMMENT

    unifdef - remove ifdef'ed lines

E 4
I 4
#ifndef lint
I 5
D 8
char copyright[] =
"%Z% Copyright (c) 1985 The Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1985, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
D 5
#endif
E 5
I 5
#endif /* not lint */
E 5
I 4

/*
 * unifdef - remove ifdef'ed lines
I 6
 *
 *  Warning: will not work correctly if input contains null characters.
 *
 *  Wishlist:
 *      provide an option which will append the name of the
 *        appropriate symbol after #else's and #endif's
 *      provide an option which will check symbols after
 *        #else's and #endif's to see that they match their
 *        corresponding #ifdef or #ifndef
E 6
 */
E 4

#include <stdio.h>
#include <ctype.h>
I 5

E 5
#define BSS
FILE *input;
#ifndef YES
#define YES 1
#define NO  0
D 6
#endif
E 6
I 6
#endif/*YES */
typedef int Bool;
E 6

char *progname BSS;
char *filename BSS;
char text BSS;          /* -t option in effect: this is a text file */
char lnblank BSS;       /* -l option in effect: blank deleted lines */
char complement BSS;    /* -c option in effect: complement the operation */
I 6

E 6
#define MAXSYMS 100
D 6
char true[MAXSYMS] BSS;
char ignore[MAXSYMS] BSS;
char *sym[MAXSYMS] BSS;
char insym[MAXSYMS] BSS;
E 6
I 6
char *symname[MAXSYMS] BSS; /* symbol name */
char true[MAXSYMS] BSS;     /* -Dsym */
char ignore[MAXSYMS] BSS;   /* -iDsym or -iUsym */
char insym[MAXSYMS] BSS;    /* state: false, inactive, true */
#define SYM_INACTIVE 0      /* symbol is currently inactive */
#define SYM_FALSE    1      /* symbol is currently false */
#define SYM_TRUE     2      /* symbol is currently true  */

E 6
char nsyms BSS;
D 6
char incomment BSS;
#define QUOTE1 0
#define QUOTE2 1
char inquote[2] BSS;
E 6
I 6
char incomment BSS;         /* inside C comment */

#define QUOTE_NONE   0
#define QUOTE_SINGLE 1
#define QUOTE_DOUBLE 2
char inquote BSS;           /* inside single or double quotes */

E 6
int exitstat BSS;
char *skipcomment ();
char *skipquote ();

main (argc, argv)
int argc;
char **argv;
{
    char **curarg;
    register char *cp;
    register char *cp1;
    char ignorethis;

    progname = argv[0][0] ? argv[0] : "unifdef";

    for (curarg = &argv[1]; --argc > 0; curarg++) {
	if (*(cp1 = cp = *curarg) != '-')
	    break;
	if (*++cp1 == 'i') {
	    ignorethis = YES;
	    cp1++;
D 6
	}
	else
E 6
I 6
	} else
E 6
	    ignorethis = NO;
D 3
	if (   (   *cp1 == 'd'
		|| *cp1 == 'u'
E 3
I 3
	if (   (   *cp1 == 'D'
		|| *cp1 == 'U'
E 3
	       )
	    && cp1[1] != '\0'
	   ) {
D 6
	    if (nsyms >= MAXSYMS) {
		prname ();
		fprintf (stderr, "too many symbols.\n");
		exit (2);
E 6
I 6
	    register int symind;

	    if ((symind = findsym (&cp1[1])) < 0) {
		if (nsyms >= MAXSYMS) {
		    prname ();
		    fprintf (stderr, "too many symbols.\n");
		    exit (2);
		}
		symind = nsyms++;
		symname[symind] = &cp1[1];
		insym[symind] = SYM_INACTIVE;
E 6
	    }
D 6
	    ignore[nsyms] = ignorethis;
D 3
	    true[nsyms] = *cp1 == 'd' ? YES : NO;
E 3
I 3
	    true[nsyms] = *cp1 == 'D' ? YES : NO;
E 3
	    sym[nsyms++] = &cp1[1];
	}
	else if (ignorethis)
E 6
I 6
	    ignore[symind] = ignorethis;
	    true[symind] = *cp1 == 'D' ? YES : NO;
	} else if (ignorethis)
E 6
	    goto unrec;
	else if (strcmp (&cp[1], "t") == 0)
	    text = YES;
	else if (strcmp (&cp[1], "l") == 0)
	    lnblank = YES;
	else if (strcmp (&cp[1], "c") == 0)
	    complement = YES;
	else {
 unrec:
	    prname ();
	    fprintf (stderr, "unrecognized option: %s\n", cp);
	    goto usage;
	}
    }
    if (nsyms == 0) {
 usage:
	fprintf (stderr, "\
D 3
Usage: %s [-l] [-t] [-c] [[-dsym] [-usym] [-idsym] [-iusym]]... [file]\n\
    At least one arg from [-d -u -id -iu] is required\n", progname);
E 3
I 3
D 6
Usage: %s [-l] [-t] [-c] [[-Dsym] [-Usym] [-idsym] [-iusym]]... [file]\n\
    At least one arg from [-D -U -id -iu] is required\n", progname);
E 6
I 6
Usage: %s [-l] [-t] [-c] [[-Dsym] [-Usym] [-iDsym] [-iUsym]]... [file]\n\
    At least one arg from [-D -U -iD -iU] is required\n", progname);
E 6
E 3
	exit (2);
    }

    if (argc > 1) {
	prname ();
	fprintf (stderr, "can only do one file.\n");
D 6
    }
    else if (argc == 1) {
E 6
I 6
    } else if (argc == 1) {
E 6
	filename = *curarg;
	if ((input = fopen (filename, "r")) != NULL) {
	    pfile();
D 6
	    fclose (input);
	}
	else {
E 6
I 6
	    (void) fclose (input);
	} else {
E 6
	    prname ();
I 6
	    fprintf (stderr, "can't open ");
E 6
D 2
	    fprintf (stderr, "can't open %s\n", *curarg);
E 2
I 2
	    perror(*curarg);
E 2
	}
D 6
    }
    else {
E 6
I 6
    } else {
E 6
	filename = "[stdin]";
	input = stdin;
	pfile();
    }

D 6
    fflush (stdout);
E 6
I 6
    (void) fflush (stdout);
E 6
    exit (exitstat);
}

/* types of input lines: */
D 6
#define PLAIN       0   /* ordinary line */
#define TRUE        1   /* a true  #ifdef of a symbol known to us */
#define FALSE       2   /* a false #ifdef of a symbol known to us */
#define OTHER       3   /* an #ifdef of a symbol not known to us */
#define ELSE        4   /* #else */
#define ENDIF       5   /* #endif */
#define LEOF        6   /* end of file */
E 6
I 6
typedef int Linetype;
#define LT_PLAIN       0   /* ordinary line */
#define LT_TRUE        1   /* a true  #ifdef of a symbol known to us */
#define LT_FALSE       2   /* a false #ifdef of a symbol known to us */
#define LT_OTHER       3   /* an #ifdef of a symbol not known to us */
#define LT_IF          4   /* an #ifdef of a symbol not known to us */
#define LT_ELSE        5   /* #else */
#define LT_ENDIF       6   /* #endif */
#define LT_LEOF        7   /* end of file */
extern Linetype checkline ();
E 6

D 6
char reject BSS;    /* 0 or 1: pass thru; 1 or 2: ignore comments */
E 6
I 6
typedef int Reject_level;
Reject_level reject BSS;    /* 0 or 1: pass thru; 1 or 2: ignore comments */
#define REJ_NO          0
#define REJ_IGNORE      1
#define REJ_YES         2

E 6
int linenum BSS;    /* current line number */
int stqcline BSS;   /* start of current coment or quote */
char *errs[] = {
#define NO_ERR      0
			"",
#define END_ERR     1
			"",
#define ELSE_ERR    2
			"Inappropriate else",
#define ENDIF_ERR   3
			"Inappropriate endif",
#define IEOF_ERR    4
			"Premature EOF in ifdef",
#define CEOF_ERR    5
			"Premature EOF in comment",
#define Q1EOF_ERR   6
			"Premature EOF in quoted character",
#define Q2EOF_ERR   7
			"Premature EOF in quoted string"
};

I 6
/* States for inif arg to doif */
#define IN_NONE 0
#define IN_IF   1
#define IN_ELSE 2

E 6
pfile ()
{
D 6
    reject = 0;
    doif (-1, NO, reject, 0);
E 6
I 6
    reject = REJ_NO;
    (void) doif (-1, IN_NONE, reject, 0);
E 6
    return;
}

I 6
int
E 6
doif (thissym, inif, prevreject, depth)
register int thissym;   /* index of the symbol who was last ifdef'ed */
int inif;               /* YES or NO we are inside an ifdef */
D 6
int prevreject;         /* previous value of reject */
E 6
I 6
Reject_level prevreject;/* previous value of reject */
E 6
int depth;              /* depth of ifdef's */
{
D 6
    register int lineval;
    register int thisreject;
    int doret;          /* tmp return valud]e of doif */
E 6
I 6
    register Linetype lineval;
    register Reject_level thisreject;
    int doret;          /* tmp return value of doif */
E 6
    int cursym;         /* index of the symbol returned by checkline */
    int stline;         /* line number when called this time */

    stline = linenum;
    for (;;) {
	switch (lineval = checkline (&cursym)) {
D 6
	case PLAIN:
E 6
I 6
	case LT_PLAIN:
E 6
	    flushline (YES);
	    break;

D 6
	case TRUE:
	case FALSE:
E 6
I 6
	case LT_TRUE:
	case LT_FALSE:
E 6
	    thisreject = reject;
D 6
	    if (lineval == TRUE)
		insym[cursym] = 1;
E 6
I 6
	    if (lineval == LT_TRUE)
		insym[cursym] = SYM_TRUE;
E 6
	    else {
D 6
		if (reject < 2)
		    reject = ignore[cursym] ? 1 : 2;
		insym[cursym] = -1;
E 6
I 6
		if (reject != REJ_YES)
		    reject = ignore[cursym] ? REJ_IGNORE : REJ_YES;
		insym[cursym] = SYM_FALSE;
E 6
	    }
	    if (ignore[cursym])
		flushline (YES);
	    else {
		exitstat = 1;
		flushline (NO);
	    }
D 6
	    if ((doret = doif (cursym, YES, thisreject, depth + 1)) != NO_ERR)
E 6
I 6
	    if ((doret = doif (cursym, IN_IF, thisreject, depth + 1)) != NO_ERR)
E 6
		return error (doret, stline, depth);
D 6
    	    break;
E 6
I 6
	    break;
E 6

D 6
	case OTHER:
E 6
I 6
	case LT_IF:
	case LT_OTHER:
E 6
	    flushline (YES);
D 6
	    if ((doret = doif (-1, YES, reject, depth + 1)) != NO_ERR)
E 6
I 6
	    if ((doret = doif (-1, IN_IF, reject, depth + 1)) != NO_ERR)
E 6
		return error (doret, stline, depth);
	    break;

D 6
	case ELSE:
	    if (inif != 1)
E 6
I 6
	case LT_ELSE:
	    if (inif != IN_IF)
E 6
		return error (ELSE_ERR, linenum, depth);
D 6
	    inif = 2;
E 6
I 6
	    inif = IN_ELSE;
E 6
	    if (thissym >= 0) {
D 6
		if ((insym[thissym] = -insym[thissym]) < 0)
		    reject = ignore[thissym] ? 1 : 2;
		else
E 6
I 6
		if (insym[thissym] == SYM_TRUE) {
		    reject = ignore[thissym] ? REJ_IGNORE : REJ_YES;
		    insym[thissym] = SYM_FALSE;
		} else { /* (insym[thissym] == SYM_FALSE) */
E 6
		    reject = prevreject;
I 6
		    insym[thissym] = SYM_TRUE;
		}
E 6
		if (!ignore[thissym]) {
		    flushline (NO);
		    break;
		}
	    }
	    flushline (YES);
	    break;

D 6
	case ENDIF:
	    if (inif == 0)
E 6
I 6
	case LT_ENDIF:
	    if (inif == IN_NONE)
E 6
		return error (ENDIF_ERR, linenum, depth);
	    if (thissym >= 0) {
D 6
		insym[thissym] = 0;
E 6
I 6
		insym[thissym] = SYM_INACTIVE;
E 6
		reject = prevreject;
		if (!ignore[thissym]) {
		    flushline (NO);
		    return NO_ERR;
		}
	    }
	    flushline (YES);
	    return NO_ERR;

D 6
	case LEOF: {
E 6
I 6
	case LT_LEOF: {
E 6
	    int err;
	    err =   incomment
		  ? CEOF_ERR
D 6
		  : inquote[QUOTE1]
E 6
I 6
		  : inquote == QUOTE_SINGLE
E 6
		  ? Q1EOF_ERR
D 6
		  : inquote[QUOTE2]
E 6
I 6
		  : inquote == QUOTE_DOUBLE
E 6
		  ? Q2EOF_ERR
		  : NO_ERR;
D 6
	    if (inif) {
E 6
I 6
	    if (inif != IN_NONE) {
E 6
		if (err != NO_ERR)
D 6
		    error (err, stqcline, depth);
E 6
I 6
		    (void) error (err, stqcline, depth);
E 6
		return error (IEOF_ERR, stline, depth);
D 6
	    }
	    else if (err != NO_ERR)
E 6
I 6
	    } else if (err != NO_ERR)
E 6
		return error (err, stqcline, depth);
	    else
		return NO_ERR;
	    }
	}
    }
}

#define endsym(c) (!isalpha (c) && !isdigit (c) && c != '_')

#define MAXLINE 256
char tline[MAXLINE] BSS;

I 6
Linetype
E 6
checkline (cursym)
D 6
int *cursym;
E 6
I 6
int *cursym;    /* if LT_TRUE or LT_FALSE returned, set this to sym index */
E 6
{
    register char *cp;
    register char *symp;
D 6
    register char chr;
E 6
    char *scp;
D 6
    int retval;
    int symind;
E 6
I 6
    Linetype retval;
E 6
#   define KWSIZE 8
    char keyword[KWSIZE];

    linenum++;
    if (getlin (tline, sizeof tline, input, NO) == EOF)
D 6
        return LEOF;
E 6
I 6
	return LT_LEOF;
E 6

D 6
    retval = PLAIN;
E 6
I 6
    retval = LT_PLAIN;
E 6
    if (   *(cp = tline) != '#'
	|| incomment
D 6
	|| inquote[QUOTE1]
	|| inquote[QUOTE2]
E 6
I 6
	|| inquote == QUOTE_SINGLE
	|| inquote == QUOTE_DOUBLE
E 6
       )
	goto eol;

    cp = skipcomment (++cp);
    symp = keyword;
    while (!endsym (*cp)) {
	*symp = *cp++;
	if (++symp >= &keyword[KWSIZE])
	    goto eol;
    }
    *symp = '\0';

    if (strcmp (keyword, "ifdef") == 0) {
	retval = YES;
	goto ifdef;
D 6
    }
    else if (strcmp (keyword, "ifndef") == 0) {
E 6
I 6
    } else if (strcmp (keyword, "ifndef") == 0) {
E 6
	retval = NO;
 ifdef:
	scp = cp = skipcomment (++cp);
	if (incomment) {
D 6
	    retval = PLAIN;
E 6
I 6
	    retval = LT_PLAIN;
E 6
	    goto eol;
	}
D 6
	for (symind = 0; ; ) {
	    if (insym[symind] == 0) {
		for ( symp = sym[symind], cp = scp
		    ; *symp && *cp == *symp
		    ; cp++, symp++
		    )
		    {}
		chr = *cp;
		if (*symp == '\0' && endsym (chr)) {
		    *cursym = symind;
		    retval = (retval ^ true[symind]) ? FALSE : TRUE;
		    break;
		}
	    }
	    if (++symind >= nsyms) {
		retval = OTHER;
		break;
	    }
E 6
I 6
	{
	    int symind;

	    if ((symind = findsym (scp)) >= 0)
		retval = (retval ^ true[*cursym = symind])
			 ? LT_FALSE : LT_TRUE;
	    else
		retval = LT_OTHER;
E 6
	}
D 6
    }
    else if (strcmp (keyword, "if") == 0)
	retval = OTHER;
E 6
I 6
    } else if (strcmp (keyword, "if") == 0)
	retval = LT_IF;
E 6
    else if (strcmp (keyword, "else") == 0)
D 6
	retval = ELSE;
E 6
I 6
	retval = LT_ELSE;
E 6
    else if (strcmp (keyword, "endif") == 0)
D 6
	retval = ENDIF;
E 6
I 6
	retval = LT_ENDIF;
E 6

 eol:
D 6
    if (!text && !reject)
E 6
I 6
    if (!text && reject != REJ_IGNORE)
E 6
	for (; *cp; ) {
	    if (incomment)
		cp = skipcomment (cp);
D 6
	    else if (inquote[QUOTE1])
		cp = skipquote (cp, QUOTE1);
	    else if (inquote[QUOTE2])
		cp = skipquote (cp, QUOTE2);
E 6
I 6
	    else if (inquote == QUOTE_SINGLE)
		cp = skipquote (cp, QUOTE_SINGLE);
	    else if (inquote == QUOTE_DOUBLE)
		cp = skipquote (cp, QUOTE_DOUBLE);
E 6
	    else if (*cp == '/' && cp[1] == '*')
		cp = skipcomment (cp);
	    else if (*cp == '\'')
D 6
		cp = skipquote (cp, QUOTE1);
E 6
I 6
		cp = skipquote (cp, QUOTE_SINGLE);
E 6
	    else if (*cp == '"')
D 6
		cp = skipquote (cp, QUOTE2);
E 6
I 6
		cp = skipquote (cp, QUOTE_DOUBLE);
E 6
	    else
		cp++;
	}
    return retval;
}

D 6
/*  Skip over comments and stop at the next charaacter
/*  position that is not whitespace.
/**/
E 6
I 6
/*
 *  Skip over comments and stop at the next charaacter
 *  position that is not whitespace.
 */
E 6
char *
skipcomment (cp)
register char *cp;
{
    if (incomment)
	goto inside;
    for (;; cp++) {
D 6
        while (*cp == ' ' || *cp == '\t')
            cp++;
E 6
I 6
	while (*cp == ' ' || *cp == '\t')
	    cp++;
E 6
	if (text)
D 6
            return cp;
E 6
I 6
	    return cp;
E 6
	if (   cp[0] != '/'
	    || cp[1] != '*'
	   )
D 6
            return cp;
E 6
I 6
	    return cp;
E 6
	cp += 2;
	if (!incomment) {
	    incomment = YES;
	    stqcline = linenum;
	}
 inside:
	for (;;) {
	    for (; *cp != '*'; cp++)
		if (*cp == '\0')
		    return cp;
D 6
	    if (*++cp == '/')
E 6
I 6
	    if (*++cp == '/') {
		incomment = NO;
E 6
		break;
I 6
	    }
E 6
	}
D 6
	incomment = NO;
E 6
    }
}

D 6
/*  Skip over a quoted string or character and stop at the next charaacter
/*  position that is not whitespace.
/**/
E 6
I 6
/*
 *  Skip over a quoted string or character and stop at the next charaacter
 *  position that is not whitespace.
 */
E 6
char *
skipquote (cp, type)
register char *cp;
register int type;
{
    register char qchar;

D 6
    qchar = type == QUOTE1 ? '\'' : '"';
E 6
I 6
    qchar = type == QUOTE_SINGLE ? '\'' : '"';
E 6

D 6
    if (inquote[type])
E 6
I 6
    if (inquote == type)
E 6
	goto inside;
    for (;; cp++) {
	if (*cp != qchar)
	    return cp;
	cp++;
D 6
	if (!inquote[type]) {
	    inquote[type] = YES;
	    stqcline = linenum;
	}
E 6
I 6
	inquote = type;
	stqcline = linenum;
E 6
 inside:
	for (; ; cp++) {
	    if (*cp == qchar)
		break;
	    if (   *cp == '\0'
D 6
		|| *cp == '\\'
		&& *++cp == '\0'
E 6
I 6
		|| *cp == '\\' && *++cp == '\0'
E 6
	       )
		return cp;
	}
D 6
	inquote[type] = NO;
E 6
I 6
	inquote = QUOTE_NONE;
E 6
    }
}

/*
D 6
/*   special getlin - treats form-feed as an end-of-line
/*                    and expands tabs if asked for
E 6
I 6
 *  findsym - look for the symbol in the symbol table.
 *            if found, return symbol table index,
 *            else return -1.
 */
int
findsym (str)
char *str;
{
    register char *cp;
    register char *symp;
    register int symind;
    register char chr;

    for (symind = 0; symind < nsyms; ++symind) {
	if (insym[symind] == SYM_INACTIVE) {
	    for ( symp = symname[symind], cp = str
		; *symp && *cp == *symp
		; cp++, symp++
		)
		continue;
	    chr = *cp;
	    if (*symp == '\0' && endsym (chr))
		return symind;
	}
    }
    return -1;
}

E 6
/*
D 6
/**/
E 6
I 6
 *   getlin - expands tabs if asked for
 *            and (if compiled in) treats form-feed as an end-of-line
 */
int
E 6
getlin (line, maxline, inp, expandtabs)
register char *line;
int maxline;
FILE *inp;
int expandtabs;
{
    int tmp;
    register int num;
    register int chr;
D 6
#ifdef FFSPECIAL
E 6
I 6
#ifdef  FFSPECIAL
E 6
    static char havechar = NO;  /* have leftover char from last time */
    static char svchar BSS;
D 6
#endif
E 6
I 6
#endif/*FFSPECIAL */
E 6

    num = 0;
D 6
#ifdef FFSPECIAL
E 6
I 6
#ifdef  FFSPECIAL
E 6
    if (havechar) {
	havechar = NO;
	chr = svchar;
	goto ent;
    }
D 6
#endif
E 6
I 6
#endif/*FFSPECIAL */
E 6
    while (num + 8 < maxline) {   /* leave room for tab */
D 6
        chr = getc (inp);
E 6
I 6
	chr = getc (inp);
E 6
	if (isprint (chr)) {
D 6
#ifdef FFSPECIAL
E 6
I 6
#ifdef  FFSPECIAL
E 6
 ent:
D 6
#endif
E 6
I 6
#endif/*FFSPECIAL */
E 6
	    *line++ = chr;
	    num++;
D 6
	}
	else
E 6
I 6
	} else
E 6
	    switch (chr) {
	    case EOF:
		return EOF;

	    case '\t':
		if (expandtabs) {
		    num += tmp = 8 - (num & 7);
		    do
			*line++ = ' ';
		    while (--tmp);
		    break;
D 6
		} 
            default:
                *line++ = chr;
                num++;
E 6
I 6
		}
	    default:
		*line++ = chr;
		num++;
E 6
		break;

	    case '\n':
D 6
                *line = '\n';
                num++;
                goto end;
    
#ifdef FFSPECIAL
E 6
I 6
		*line = '\n';
		num++;
		goto end;

#ifdef  FFSPECIAL
E 6
	    case '\f':
		if (++num == 1)
		    *line = '\f';
		else {
		    *line = '\n';
		    havechar = YES;
D 6
                    svchar = chr;
                }
                goto end;
#endif
E 6
I 6
		    svchar = chr;
		}
		goto end;
#endif/*FFSPECIAL */
E 6
	    }
    }
 end:
    *++line = '\0';
    return num;
}

flushline (keep)
I 6
Bool keep;
E 6
{
D 6
    if ((keep && reject < 2) ^ complement)
	putlin (tline, stdout);
    else if (lnblank)
	putlin ("\n", stdout);
    return;
}
E 6
I 6
    if ((keep && reject != REJ_YES) ^ complement) {
	register char *line = tline;
	register FILE *out = stdout;
	register char chr;
E 6

D 6
/*
/*  putlin - for tools
/*
/**/
putlin (line, fio)
register char *line;
register FILE *fio;
{
    register char chr;

    while (chr = *line++)
	putc (chr, fio);
E 6
I 6
	while (chr = *line++)
	    putc (chr, out);
    } else if (lnblank)
	putc ('\n', stdout);
E 6
    return;
}

prname ()
{
    fprintf (stderr, "%s: ", progname);
    return;
}

D 6

E 6
I 6
int
E 6
error (err, line, depth)
I 6
int err;        /* type of error & index into error string array */
int line;       /* line number */
int depth;      /* how many ifdefs we are inside */
E 6
{
    if (err == END_ERR)
	return err;

    prname ();

#ifndef TESTING
D 6
    fprintf (stderr, "Error in %s line %d: %s.\n",
	     filename, line, errs[err]);
#endif

#ifdef TESTING
    fprintf (stderr, "Error in %s line %d: %s. ",
	     filename, line, errs[err]);
E 6
I 6
    fprintf (stderr, "Error in %s line %d: %s.\n", filename, line, errs[err]);
#else/* TESTING */
    fprintf (stderr, "Error in %s line %d: %s. ", filename, line, errs[err]);
E 6
    fprintf (stderr, "ifdef depth: %d\n", depth);
D 6
#endif
E 6
I 6
#endif/*TESTING */
E 6

    exitstat = 2;
    return depth > 1 ? IEOF_ERR : END_ERR;
}
E 1
