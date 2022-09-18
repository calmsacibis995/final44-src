h55393
s 00004/00004/00563
d D 8.1 93/06/06 22:20:28 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00566
d D 5.6 92/09/16 10:58:08 elan 8 7
c copyright[] -> static
e
s 00008/00027/00559
d D 5.5 92/09/15 11:07:56 elan 7 6
c Added SCCS keywords.
e
s 00042/00012/00544
d D 5.4 92/09/01 12:10:46 elan 6 5
c Prototyped.
e
s 00001/00011/00555
d D 5.3 90/06/01 16:12:14 bostic 5 4
c new copyright notice
e
s 00015/00004/00551
d D 5.2 88/10/25 19:38:49 bostic 4 3
c written by Bill Joy; Berkeley specific copyright
e
s 00009/00001/00546
d D 5.1 85/06/05 09:42:45 dist 3 2
c Add copyright
e
s 00005/00003/00542
d D 4.2 84/12/11 16:59:24 ralph 2 1
c null pointer & missing subroutine argument fixes
e
s 00545/00000/00000
d D 4.1 82/10/19 00:52:02 mckusick 1 0
c date and time created 82/10/19 00:52:02 by mckusick
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
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 9
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 5
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
E 5
I 5
D 6
 * %sccs.include.redist.c%
E 6
I 6
D 7
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
E 7
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
E 5
E 4
 */

#ifndef lint
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
E 6
I 6
D 7
static char sccsid[] = "@(#)regexp.c	5.4 (Berkeley) 8/3/92";
E 7
I 7
D 8
char copyright[] =
E 8
I 8
static char copyright[] =
E 8
D 9
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
E 7
E 6
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 3

#include <ctype.h>
I 6
#include <stdlib.h>
#include <string.h>
#include "extern.h"
E 6

D 6
typedef int	boolean;
#define TRUE	1
E 6
#define FALSE	0
I 6
#define TRUE	!(FALSE)
E 6
#define NIL	0

D 6
boolean l_onecase;	/* true if upper and lower equivalent */
E 6
I 6
static void	expconv __P((void));
E 6

I 6
boolean	 _escaped;	/* true if we are currently _escaped */
char	*_start;	/* start of string */
boolean	 l_onecase;	/* true if upper and lower equivalent */

E 6
#define makelower(c) (isupper((c)) ? tolower((c)) : (c))

/*  STRNCMP -	like strncmp except that we convert the
 *	 	first string to lower case before comparing
 *		if l_onecase is set.
 */

I 6
int
E 6
STRNCMP(s1, s2, len)
	register char *s1,*s2;
	register int len;
{
	if (l_onecase) {
	    do
		if (*s2 - makelower(*s1))
			return (*s2 - makelower(*s1));
		else {
			s2++;
			s1++;
		}
	    while (--len);
	} else {
	    do
		if (*s2 - *s1)
			return (*s2 - *s1);
		else {
			s2++;
			s1++;
		}
	    while (--len);
	}
	return(0);
}

/*	The following routine converts an irregular expression to
 *	internal format.
 *
 *	Either meta symbols (\a \d or \p) or character strings or
 *	operations ( alternation or perenthesizing ) can be
 *	specified.  Each starts with a descriptor byte.  The descriptor
 *	byte has STR set for strings, META set for meta symbols
 *	and OPER set for operations.
 *	The descriptor byte can also have the OPT bit set if the object
 *	defined is optional.  Also ALT can be set to indicate an alternation.
 *
 *	For metasymbols the byte following the descriptor byte identities
 *	the meta symbol (containing an ascii 'a', 'd', 'p', '|', or '(').  For
 *	strings the byte after the descriptor is a character count for
 *	the string:
 *
 *		meta symbols := descriptor
 *				symbol
 *
 *		strings :=	descriptor
 *				character count
 *				the string
 *
 *		operatins :=	descriptor
 *				symbol
 *				character count
 */

/*
 *  handy macros for accessing parts of match blocks
 */
#define MSYM(A) (*(A+1))	/* symbol in a meta symbol block */
#define MNEXT(A) (A+2)		/* character following a metasymbol block */

#define OSYM(A) (*(A+1))	/* symbol in an operation block */
#define OCNT(A) (*(A+2))	/* character count */
#define ONEXT(A) (A+3)		/* next character after the operation */
#define OPTR(A) (A+*(A+2))	/* place pointed to by the operator */

#define SCNT(A) (*(A+1))	/* byte count of a string */
#define SSTR(A) (A+2)		/* address of the string */
#define SNEXT(A) (A+2+*(A+1))	/* character following the string */

/*
 *  bit flags in the descriptor 
 */
#define OPT 1
#define STR 2
#define META 4
#define ALT 8
#define OPER 16

D 6
char *ure;		/* pointer current position in unconverted exp */
char *ccre;		/* pointer to current position in converted exp*/
char *malloc();
E 6
I 6
static char *ccre;	/* pointer to current position in converted exp*/
static char *ure;	/* pointer current position in unconverted exp */
E 6

char *
convexp(re)
    char *re;		/* unconverted irregular expression */
{
    register char *cre;		/* pointer to converted regular expression */

    /* allocate room for the converted expression */
    if (re == NIL)
	return (NIL);
    if (*re == '\0')
	return (NIL);
    cre = malloc (4 * strlen(re) + 3);
    ccre = cre;
    ure = re;

    /* start the conversion with a \a */
    *cre = META | OPT;
    MSYM(cre) = 'a';
    ccre = MNEXT(cre);

    /* start the conversion (its recursive) */
    expconv ();
    *ccre = 0;
    return (cre);
}

I 6
static void
E 6
expconv()
{
    register char *cs;		/* pointer to current symbol in converted exp */
    register char c;		/* character being processed */
    register char *acs;		/* pinter to last alternate */
    register int temp;

    /* let the conversion begin */
    acs = NIL;
I 2
    cs = NIL;
E 2
    while (*ure != NIL) {
	switch (c = *ure++) {

	case '\\':
	    switch (c = *ure++) {

	    /* escaped characters are just characters */
	    default:
D 2
		if ((*cs & STR) == 0) {
E 2
I 2
		if (cs == NIL || (*cs & STR) == 0) {
E 2
		    cs = ccre;
		    *cs = STR;
		    SCNT(cs) = 1;
		    ccre += 2;
		} else 
		    SCNT(cs)++;
		*ccre++ = c;
		break;

	    /* normal(?) metacharacters */
	    case 'a':
	    case 'd':
	    case 'e':
	    case 'p':
		if (acs != NIL && acs != cs) {
		    do {
			temp = OCNT(acs);
			OCNT(acs) = ccre - acs; 
			acs -= temp;
		    } while (temp != 0);
		    acs = NIL;
		}
		cs = ccre;
		*cs = META;
		MSYM(cs) = c;
		ccre = MNEXT(cs);
		break;
	    }
	    break;
	    
	/* just put the symbol in */
	case '^':
	case '$':
	    if (acs != NIL && acs != cs) {
		do {
		    temp = OCNT(acs);
		    OCNT(acs) = ccre - acs;
		    acs -= temp;
		} while (temp != 0);
		acs = NIL;
	    }
	    cs = ccre;
	    *cs = META;
	    MSYM(cs) = c;
	    ccre = MNEXT(cs);
	    break;

	/* mark the last match sequence as optional */
	case '?':
D 2
	    *cs = *cs | OPT;
E 2
I 2
	    if (cs)
	    	*cs = *cs | OPT;
E 2
	    break;

	/* recurse and define a subexpression */
	case '(':
	    if (acs != NIL && acs != cs) {
		do {
		    temp = OCNT(acs);
		    OCNT(acs) = ccre - acs;
		    acs -= temp;
		} while (temp != 0);
		acs = NIL;
	    }
	    cs = ccre;
	    *cs = OPER;
	    OSYM(cs) = '(';
	    ccre = ONEXT(cs);
	    expconv ();
	    OCNT(cs) = ccre - cs;		/* offset to next symbol */
	    break;

D 6
	/* return from a recursion */
E 6
I 6
	/* reurn from a recursion */
E 6
	case ')':
	    if (acs != NIL) {
		do {
		    temp = OCNT(acs);
		    OCNT(acs) = ccre - acs;
		    acs -= temp;
		} while (temp != 0);
		acs = NIL;
	    }
	    cs = ccre;
	    *cs = META;
	    MSYM(cs) = c;
	    ccre = MNEXT(cs);
	    return;

	/* mark the last match sequence as having an alternate */
	/* the third byte will contain an offset to jump over the */
	/* alternate match in case the first did not fail */
	case '|':
	    if (acs != NIL && acs != cs)
		OCNT(ccre) = ccre - acs;	/* make a back pointer */
	    else
		OCNT(ccre) = 0;
	    *cs |= ALT;
	    cs = ccre;
	    *cs = OPER;
	    OSYM(cs) = '|';
	    ccre = ONEXT(cs);
	    acs = cs;	/* remember that the pointer is to be filles */
	    break;

	/* if its not a metasymbol just build a scharacter string */
	default:
D 2
	    if ((*cs & STR) == 0) {
E 2
I 2
	    if (cs == NIL || (*cs & STR) == 0) {
E 2
		cs = ccre;
		*cs = STR;
		SCNT(cs) = 1;
		ccre = SSTR(cs);
	    } else
		SCNT(cs)++;
	    *ccre++ = c;
	    break;
	}
    }
    if (acs != NIL) {
	do {
	    temp = OCNT(acs);
	    OCNT(acs) = ccre - acs;
	    acs -= temp;
	} while (temp != 0);
	acs = NIL;
    }
    return;
}
/* end of convertre */


/*
 *	The following routine recognises an irregular expresion
 *	with the following special characters:
 *
 *		\?	-	means last match was optional
 *		\a	-	matches any number of characters
 *		\d	-	matches any number of spaces and tabs
 *		\p	-	matches any number of alphanumeric
 *				characters. The
 *				characters matched will be copied into
 *				the area pointed to by 'name'.
 *		\|	-	alternation
 *		\( \)	-	grouping used mostly for alternation and
 *				optionality
 *
 *	The irregular expression must be translated to internal form
 *	prior to calling this routine
 *
 *	The value returned is the pointer to the first non \a 
 *	character matched.
 */
D 6

boolean _escaped;		/* true if we are currently _escaped */
char *_start;			/* start of string */
E 6

char *
expmatch (s, re, mstring)
    register char *s;		/* string to check for a match in */
    register char *re;		/* a converted irregular expression */
    register char *mstring;	/* where to put whatever matches a \p */
{
    register char *cs;		/* the current symbol */
    register char *ptr,*s1;	/* temporary pointer */
    boolean matched;		/* a temporary boolean */

    /* initial conditions */
    if (re == NIL)
	return (NIL);
    cs = re;
    matched = FALSE;

    /* loop till expression string is exhausted (or at least pretty tired) */
    while (*cs) {
	switch (*cs & (OPER | STR | META)) {

	/* try to match a string */
	case STR:
	    matched = !STRNCMP (s, SSTR(cs), SCNT(cs));
	    if (matched) {

		/* hoorah it matches */
		s += SCNT(cs);
		cs = SNEXT(cs);
	    } else if (*cs & ALT) {

		/* alternation, skip to next expression */
		cs = SNEXT(cs);
	    } else if (*cs & OPT) {

		/* the match is optional */
		cs = SNEXT(cs);
		matched = 1;		/* indicate a successful match */
	    } else {

		/* no match, error return */
		return (NIL);
	    }
	    break;

	/* an operator, do something fancy */
	case OPER:
	    switch (OSYM(cs)) {

	    /* this is an alternation */
	    case '|':
		if (matched)

		    /* last thing in the alternation was a match, skip ahead */
		    cs = OPTR(cs);
		else

		    /* no match, keep trying */
		    cs = ONEXT(cs);
		break;

	    /* this is a grouping, recurse */
	    case '(':
		ptr = expmatch (s, ONEXT(cs), mstring);
		if (ptr != NIL) {

		    /* the subexpression matched */
		    matched = 1;
		    s = ptr;
		} else if (*cs & ALT) {

		    /* alternation, skip to next expression */
		    matched = 0;
		} else if (*cs & OPT) {

		    /* the match is optional */
		    matched = 1;	/* indicate a successful match */
		} else {

		    /* no match, error return */
		    return (NIL);
		}
		cs = OPTR(cs);
		break;
	    }
	    break;

	/* try to match a metasymbol */
	case META:
	    switch (MSYM(cs)) {

	    /* try to match anything and remember what was matched */
	    case 'p':
		/*
		 *  This is really the same as trying the match the
		 *  remaining parts of the expression to any subset
		 *  of the string.
		 */
		s1 = s;
		do {
		    ptr = expmatch (s1, MNEXT(cs), mstring);
		    if (ptr != NIL && s1 != s) {

			/* we have a match, remember the match */
			strncpy (mstring, s, s1 - s);
			mstring[s1 - s] = '\0';
			return (ptr);
		    } else if (ptr != NIL && (*cs & OPT)) {

			/* it was aoptional so no match is ok */
			return (ptr);
		    } else if (ptr != NIL) {

			/* not optional and we still matched */
			return (NIL);
		    }
		    if (!isalnum(*s1) && *s1 != '_')
			return (NIL);
		    if (*s1 == '\\')
			_escaped = _escaped ? FALSE : TRUE;
		    else
			_escaped = FALSE;
		} while (*s1++);
		return (NIL);

	    /* try to match anything */
	    case 'a':
		/*
		 *  This is really the same as trying the match the
		 *  remaining parts of the expression to any subset
		 *  of the string.
		 */
		s1 = s;
		do {
		    ptr = expmatch (s1, MNEXT(cs), mstring);
		    if (ptr != NIL && s1 != s) {

			/* we have a match */
			return (ptr);
		    } else if (ptr != NIL && (*cs & OPT)) {

			/* it was aoptional so no match is ok */
			return (ptr);
		    } else if (ptr != NIL) {

			/* not optional and we still matched */
			return (NIL);
		    }
		    if (*s1 == '\\')
			_escaped = _escaped ? FALSE : TRUE;
		    else
			_escaped = FALSE;
		} while (*s1++);
		return (NIL);

	    /* fail if we are currently _escaped */
	    case 'e':
		if (_escaped)
		    return(NIL);
		cs = MNEXT(cs); 
		break;

	    /* match any number of tabs and spaces */
	    case 'd':
		ptr = s;
		while (*s == ' ' || *s == '\t')
		    s++;
		if (s != ptr || s == _start) {

		    /* match, be happy */
		    matched = 1;
		    cs = MNEXT(cs); 
		} else if (*s == '\n' || *s == '\0') {

		    /* match, be happy */
		    matched = 1;
		    cs = MNEXT(cs); 
		} else if (*cs & ALT) {

		    /* try the next part */
		    matched = 0;
		    cs = MNEXT(cs);
		} else if (*cs & OPT) {

		    /* doesn't matter */
		    matched = 1;
		    cs = MNEXT(cs);
		} else

		    /* no match, error return */
		    return (NIL);
		break;

	    /* check for end of line */
	    case '$':
		if (*s == '\0' || *s == '\n') {

		    /* match, be happy */
		    s++;
		    matched = 1;
		    cs = MNEXT(cs);
		} else if (*cs & ALT) {

		    /* try the next part */
		    matched = 0;
		    cs = MNEXT(cs);
		} else if (*cs & OPT) {

		    /* doesn't matter */
		    matched = 1;
		    cs = MNEXT(cs);
		} else

		    /* no match, error return */
		    return (NIL);
		break;

	    /* check for start of line */
	    case '^':
		if (s == _start) {

		    /* match, be happy */
		    matched = 1;
		    cs = MNEXT(cs);
		} else if (*cs & ALT) {

		    /* try the next part */
		    matched = 0;
		    cs = MNEXT(cs);
		} else if (*cs & OPT) {

		    /* doesn't matter */
		    matched = 1;
		    cs = MNEXT(cs);
		} else

		    /* no match, error return */
		    return (NIL);
		break;

	    /* end of a subexpression, return success */
	    case ')':
		return (s);
	    }
	    break;
	}
    }
    return (s);
}
E 1
