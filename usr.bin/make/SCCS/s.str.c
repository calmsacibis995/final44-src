h37965
s 00059/00013/00406
d D 8.6 95/04/28 17:08:26 christos 16 15
c Updated to the latest version from the NetBSD source
e
s 00007/00001/00412
d D 8.5 94/05/23 15:50:36 christos 15 14
c parse "" or '' correctly. They were being eaten up.
e
s 00005/00002/00408
d D 8.4 94/03/21 17:47:32 bostic 14 13
c Null Suffixes were not being copied, but they were being free'd
c My recent fixes to parse ${VAR:%.foo=%.bar} handled the null string
c case incorrectly (${VAR:=.c} was broken).
c From: Christos Zoulas <christos@deshaw.com>
e
s 00095/00000/00315
d D 8.3 94/03/19 10:53:16 bostic 13 12
c The SYSV ${VAR:src=dst} was broken; try:
c SRC=foo.c bar.c
c all:
c 	echo ${SRC:%.c=%.o}
c From: Christos Zoulas <christos@deshaw.com>
e
s 00001/00001/00314
d D 8.2 94/01/02 15:05:03 bostic 12 10
c inquote is a char, should be assigned to '\0' not to NULL.
e
s 00001/00001/00314
d R 8.2 94/01/02 15:02:18 bostic 11 10
c 
e
s 00002/00002/00313
d D 8.1 93/06/06 15:17:07 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00007/00306
d D 5.9 93/05/24 14:45:59 bostic 9 8
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00011/00312
d D 5.8 90/06/01 17:09:41 bostic 8 7
c new copyright notice
e
s 00002/00002/00321
d D 5.7 90/03/19 12:33:50 bostic 7 6
c rename .PMAKE variable as .MAKE, PMAKE environmental value to MAKE
e
s 00259/00394/00064
d D 5.6 90/03/19 10:00:44 bostic 6 5
c reformat, rewrite Str_Concat as str_concat, Str_BreakString as brk_string
c the former shouldn't matter, the latter should reduce mallocs immensely
e
s 00002/00002/00456
d D 5.5 90/03/12 09:19:54 bostic 5 4
c missed two Str_New's, include strings.h in make.h for everybody
e
s 00001/00005/00457
d D 5.4 90/03/12 09:04:44 bostic 4 3
c remove Sprite ifdef's
e
s 00004/00029/00458
d D 5.3 90/03/12 08:59:52 bostic 3 2
c Str_New -> strdup
e
s 00026/00015/00461
d D 5.2 90/03/11 15:39:23 bostic 2 1
c add Berkeley specific copyright notice
e
s 00476/00000/00000
d D 5.1 90/03/11 15:27:48 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * str.c --
 *	General utilites for handling strings.
 *
 * Copyright (c) 1988, 1989 by the Regents of the University of California
E 2
I 2
D 6
/*
E 6
I 6
/*-
E 6
D 10
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
E 2
 * Copyright (c) 1988, 1989 by Adam de Boor
E 10
I 10
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 * Copyright (c) 1989 by Berkeley Softworks
I 2
 * All rights reserved.
E 2
 *
D 2
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any non-commercial purpose
 * and without fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  The University of California,
 * Berkeley Softworks and Adam de Boor make no representations about
 * the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
I 2
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

#ifndef lint
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6
I 6
static char     sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif				/* not lint */
E 9
I 9
#endif /* not lint */
E 9
E 6

D 6
/*-
 * str.c --
 *	General utilites for handling strings.
 *
E 2
 * Interface:
 *	Str_Concat	     	Concatenate two strings, placing some sort
 *	    	  	    	of separator between them and freeing
 *	    	  	    	the two strings, all this under the control
 *	    	  	    	of the STR_ flags given as the third arg.
 *
D 3
 *	Str_New	  	    	Duplicate a string and return the copy.
 *
E 3
D 4
 *	Str_FindSubstring   	Find a substring within a string (from
 *	    	  	    	original Sprite libc).
E 4
I 4
 *	Str_FindSubstring   	Find a substring within a string
E 4
 *
 *	Str_Match   	    	Pattern match two strings.
 */
E 6
I 6
#include "make.h"
E 6
D 2
#ifndef lint
static char     *rcsid = "$Id: str.c,v 1.22 89/11/14 13:44:07 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

I 16
static char **argv, *buffer;
static int argmax, curlen;

/*
 * str_init --
 *	Initialize the strings package
 *
 */
void
str_init()
{
    char *p1;
    argv = (char **)emalloc((argmax = 50) * sizeof(char *));
    argv[0] = Var_Value(".MAKE", VAR_GLOBAL, &p1);
}


/*
 * str_end --
 *	Cleanup the strings package
 *
 */
void
str_end()
{
    if (argv[0]) {
	free(argv[0]);
	free((Address) argv);
    }
    if (buffer)
	free(buffer);
}


E 16
D 6
#include    "make.h"

E 6
/*-
D 6
 *-----------------------------------------------------------------------
 * Str_Concat  --
 *	Str_Concatenate and the two strings, inserting a space between them
 *	and/or freeing them if requested
E 6
I 6
 * str_concat --
 *	concatenate the two strings, inserting a space or slash between them,
 *	freeing them if requested.
E 6
 *
D 6
 * Results:
 *	the resulting string
 *
 * Side Effects:
 *	The strings s1 and s2 are free'd
 *-----------------------------------------------------------------------
E 6
I 6
 * returns --
 *	the resulting string in allocated space.
E 6
 */
char *
D 6
Str_Concat (s1, s2, flags)
    char           *s1;		/* first string */
    char           *s2;		/* second string */
    int             flags;	/* flags governing Str_Concatenation */
E 6
I 6
str_concat(s1, s2, flags)
	char *s1, *s2;
	int flags;
E 6
{
D 6
    int             len;	/* total length */
    register char  *cp1,	/* pointer into s1 */
                   *cp2,	/* pointer into s2 */
                   *cp;		/* pointer into result */
    char           *result;	/* result string */
E 6
I 6
	register int len1, len2;
	register char *result;
E 6

D 6
    /*
     * get the length of both strings 
     */
    for (cp1 = s1; *cp1; cp1++) {
	 /* void */ ;
    }
    for (cp2 = s2; *cp2; cp2++) {
	 /* void */ ;
    }
E 6
I 6
	/* get the length of both strings */
	len1 = strlen(s1);
	len2 = strlen(s2);
E 6

D 6
    len = (cp1 - s1) +
	(cp2 - s2) +
	    (flags & (STR_ADDSPACE | STR_ADDSLASH) ? 1 : 0) +
		1;
E 6
I 6
	/* allocate length plus separator plus EOS */
	result = emalloc((u_int)(len1 + len2 + 2));
E 6

D 6
    result = malloc (len);
E 6
I 6
	/* copy first string into place */
D 9
	bcopy(s1, result, len1);
E 9
I 9
	memcpy(result, s1, len1);
E 9
E 6

D 6
    for (cp1 = s1, cp = result; *cp1 != '\0'; cp++, cp1++) {
	*cp = *cp1;
    }
E 6
I 6
	/* add separator character */
	if (flags & STR_ADDSPACE) {
		result[len1] = ' ';
		++len1;
	} else if (flags & STR_ADDSLASH) {
		result[len1] = '/';
		++len1;
	}
E 6

D 6
    if (flags & STR_ADDSPACE) {
	*cp++ = ' ';
    } else if (flags & STR_ADDSLASH) {
	*cp++ = '/';
    }
E 6
I 6
	/* copy second string plus EOS into place */
D 9
	bcopy(s2, result + len1, len2 + 1);
E 9
I 9
	memcpy(result + len1, s2, len2 + 1);
E 9
E 6

D 6
    for (cp2 = s2; *cp2 != '\0'; cp++, cp2++) {
	*cp = *cp2;
    }

    *cp = '\0';

    if (flags & STR_DOFREE) {
	free (s1);
	free (s2);
    }
    return (result);
E 6
I 6
	/* free original strings */
	if (flags & STR_DOFREE) {
		(void)free(s1);
		(void)free(s2);
	}
	return(result);
E 6
}
D 3

/*-
 *-----------------------------------------------------------------------
 * Str_New  --
 *	Create a new unique copy of the given string
 *
 * Results:
 *	A pointer to the new copy of it
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
char *
Str_New (str)
    char           *str;	/* string to duplicate */
{
    register char  *cp;		/* new space */
E 3

D 3
    cp = malloc (strlen (str) + 1);
    (void) strcpy (cp, str);
    return (cp);
}

E 3
D 6
static char
DoBackslash (c)
    char c;
{
    switch (c) {
	case 'n': return ('\n');
	case 't': return ('\t');
	case 'b': return ('\b');
	case 'r': return ('\r');
	case 'f': return ('\f');
	default:  return (c);
    }
}
D 3

E 3
I 3

E 6
E 3
/*-
D 6
 *-----------------------------------------------------------------------
 * Str_BreakString --
 *	Fracture a string into an array of words, taking quotation marks
 *	into account. The string should have its leading 'breaks'
 *	characters removed.
E 6
I 6
 * brk_string --
 *	Fracture a string into an array of words (as delineated by tabs or
 *	spaces) taking quotation marks into account.  Leading tabs/spaces
 *	are ignored.
E 6
 *
D 6
 * Results:
 *	Pointer to the array of pointers to the words. This array must
 *	be freed by the caller. To make life easier, the first word is
 *	always the value of the .PMAKE variable.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
E 6
I 6
 * returns --
 *	Pointer to the array of pointers to the words.  To make life easier,
D 7
 *	the first word is always the value of the .PMAKE variable.
E 7
I 7
 *	the first word is always the value of the .MAKE variable.
E 7
E 6
 */
char **
D 6
Str_BreakString (str, breaks, end, argcPtr)
    register char 	*str;	    	/* String to fracture */
    register char 	*breaks;    	/* Word delimiters */
    register char 	*end;	    	/* Characters to end on */
    int	    	  	*argcPtr;   	/* OUT: Place to stuff number of
					 * words */
E 6
I 6
D 16
brk_string(str, store_argc)
E 16
I 16
brk_string(str, store_argc, expand)
E 16
	register char *str;
	int *store_argc;
I 16
	Boolean expand;
E 16
E 6
{
D 6
    char            	*defargv[256]; 	/* Temporary argument vector.
					 * Big enough for most purposes. */
    char    	    	**argv;	    	/* Argv being built */
    int	    	    	maxargc;    	/* Length of argv */
    register int    	argc;	    	/* Count of words */
    char            	**av;	    	/* Returned vector */
    register char   	*tstr;	    	/* Pointer into tstring */
    char            	tstring[512];	/* Temporary storage for the
					 * current word */
    
    argc = 1;
    argv = defargv;
    maxargc = sizeof(defargv)/sizeof(defargv[0]);
    argv[0] = Var_Value (".PMAKE", VAR_GLOBAL);
E 6
I 6
D 16
	static int argmax, curlen;
	static char **argv, *buf;
E 16
	register int argc, ch;
	register char inquote, *p, *start, *t;
	int len;
E 6

D 6
    tstr = tstring;
    while ((*str != '\0') && (index (end, *str) == (char *)NULL)) {
	if (index (breaks, *str) != (char *)NULL) {
	    *tstr++ = '\0';
D 5
	    argv[argc++] = Str_New(tstring);
E 5
I 5
	    argv[argc++] = strdup(tstring);
E 5
	    while ((*str != '\0') &&
		   (index (breaks, *str) != (char *)NULL) &&
		   (index (end, *str) == (char *)NULL)) {
		       str++;
		   }
	    tstr = tstring;
	    /*
	     * Enlarge the argument vector, if necessary
	     */
	    if (argc == maxargc) {
		maxargc *= 2;
		if (argv == defargv) {
		    argv = (char **)malloc(maxargc*sizeof(char *));
		    bcopy(defargv, argv, sizeof(defargv));
		} else {
		    argv = (char **)realloc(argv,
					    maxargc*sizeof(char *));
		}
	    }
	} else if (*str == '"') {
	    str += 1;
	    while ((*str != '"') &&
		   (index (end, *str) == (char *)NULL)) {
		       if (*str == '\\') {
			   str += 1;
			   *tstr = DoBackslash(*str);
		       } else {
			   *tstr = *str;
		       }
		       str += 1;
		       tstr += 1;
		   }
		   
	    if (*str == '"') {
		str+=1;
	    }
	} else if (*str == '\'') {
	    str += 1;
	    while ((*str != '\'') &&
		   (index (end, *str) == (char *)NULL)) {
		       if (*str == '\\') {
			   str += 1;
			   *tstr = DoBackslash(*str);
		       } else {
			   *tstr = *str;
		       }
		       str += 1;
		       tstr += 1;
		   }
		   
	    if (*str == '\'') {
		str+=1;
	    }
	} else if (*str == '\\') {
	    str += 1;
	    *tstr = DoBackslash(*str);
	    str += 1;
	    tstr += 1;
	} else {
	    *tstr = *str;
	    tstr += 1;
	    str += 1;
E 6
I 6
D 16
	/* save off pmake variable */
	if (!argv) {
		argv = (char **)emalloc((argmax = 50) * sizeof(char *));
D 7
		argv[0] = Var_Value(".PMAKE", VAR_GLOBAL);
E 7
I 7
		argv[0] = Var_Value(".MAKE", VAR_GLOBAL);
E 7
E 6
	}
D 6
    }
    if (tstr != tstring) {
E 6
I 6

E 16
D 9
	/* skip leading space chars.
	for (; *str == ' ' || *str == '\t'; ++str);
E 9
I 9
	/* skip leading space chars. */
	for (; *str == ' ' || *str == '\t'; ++str)
		continue;
E 9

	/* allocate room for a copy of the string */
D 16
	if ((len = strlen(str) + 1) > curlen)
		buf = emalloc(curlen = len);
E 16
I 16
	if ((len = strlen(str) + 1) > curlen) {
		if (buffer)
		    free(buffer);
		buffer = emalloc(curlen = len);
	}
E 16

E 6
	/*
D 6
	 * If any word is left over, add it to the vector
E 6
I 6
	 * copy the string; at the same time, parse backslashes,
	 * quotes and build the argument list.
E 6
	 */
D 6
	*tstr = '\0';
D 5
	argv[argc++] = Str_New(tstring);
E 5
I 5
	argv[argc++] = strdup(tstring);
E 5
    }
    argv[argc] = (char *) 0;
    *argcPtr = argc;
    if (argv == defargv) {
	av = (char **) malloc ((argc+1) * sizeof(char *));
	bcopy ((char *)argv, (char *)av, (argc + 1) * sizeof(char *));
    } else {
	/*
	 * Shrink vector to match actual number of args.
	 */
	av = (char **)realloc(argv, (argc+1) * sizeof(char *));
    }
    
    return av;
E 6
I 6
	argc = 1;
	inquote = '\0';
D 16
	for (p = str, start = t = buf;; ++p) {
E 16
I 16
	for (p = str, start = t = buffer;; ++p) {
E 16
		switch(ch = *p) {
		case '"':
		case '\'':
			if (inquote)
				if (inquote == ch)
D 12
					inquote = NULL;
E 12
I 12
					inquote = '\0';
E 12
				else
					break;
D 15
			else
E 15
I 15
			else {
E 15
D 9
				inquote = ch;
E 9
I 9
				inquote = (char) ch;
I 15
				/* Don't miss "" or '' */
				if (start == NULL && p[1] == inquote) {
					start = t + 1;
					break;
				}
			}
I 16
			if (!expand) {
				if (!start)
					start = t;
				*t++ = ch;
			}
E 16
E 15
E 9
			continue;
		case ' ':
		case '\t':
I 16
		case '\n':
E 16
			if (inquote)
				break;
			if (!start)
				continue;
			/* FALLTHROUGH */
D 16
		case '\n':
E 16
		case '\0':
			/*
			 * end of a token -- make sure there's enough argv
			 * space and save off a pointer.
			 */
I 16
			if (!start)
			    goto done;

E 16
			*t++ = '\0';
			if (argc == argmax) {
				argmax *= 2;		/* ramp up fast */
				if (!(argv = (char **)realloc(argv,
				    argmax * sizeof(char *))))
				enomem();
			}
			argv[argc++] = start;
			start = (char *)NULL;
			if (ch == '\n' || ch == '\0')
				goto done;
			continue;
		case '\\':
I 16
			if (!expand) {
				if (!start)
					start = t;
				*t++ = '\\';
				ch = *++p;
				break;
			}
				
E 16
			switch (ch = *++p) {
			case '\0':
			case '\n':
				/* hmmm; fix it up as best we can */
				ch = '\\';
				--p;
				break;
			case 'b':
				ch = '\b';
				break;
			case 'f':
				ch = '\f';
				break;
			case 'n':
				ch = '\n';
				break;
			case 'r':
				ch = '\r';
				break;
			case 't':
				ch = '\t';
				break;
			}
			break;
		}
		if (!start)
			start = t;
D 9
		*t++ = ch;
E 9
I 9
		*t++ = (char) ch;
E 9
	}
done:	argv[argc] = (char *)NULL;
	*store_argc = argc;
	return(argv);
E 6
}
D 3

E 3
I 3

E 3
D 6
/*-
 *-----------------------------------------------------------------------
 * Str_FreeVec --
 *	Free a string vector returned by Str_BreakString. Frees all the
 *	strings in the vector and then frees the vector itself.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The blocks addressed by the vector are freed.
 *
 *-----------------------------------------------------------------------
 */
void
Str_FreeVec (count, vecPtr)
    register int  count;
    register char **vecPtr;
{
    for (count -= 1; count > 0; count -= 1) {
	free (vecPtr[count]);
    }
    free (vecPtr);
}
D 4
#ifndef Sprite
E 4
D 3

E 3
I 3

E 6
E 3
/*
D 6
 *----------------------------------------------------------------------
 * Str_FindSubstring --
 *	See if a string contains a particular substring.
 *
 * Results:
 *	If string contains substring, the return value is the
 *	location of the first matching instance of substring
 *	in string.  If string doesn't contain substring, the
 *	return value is NULL.  Matching is done on an exact
 *	character-for-character basis with no wildcards or special
 *	characters.
 *
 * Side effects:
 *	None.
 *----------------------------------------------------------------------
E 6
I 6
 * Str_FindSubstring -- See if a string contains a particular substring.
 * 
 * Results: If string contains substring, the return value is the location of
 * the first matching instance of substring in string.  If string doesn't
 * contain substring, the return value is NULL.  Matching is done on an exact
 * character-for-character basis with no wildcards or special characters.
 * 
 * Side effects: None.
E 6
 */
char *
Str_FindSubstring(string, substring)
D 6
    register char *string;	/* String to search. */
    char *substring;		/* Substring to try to find in string. */
E 6
I 6
	register char *string;		/* String to search. */
	char *substring;		/* Substring to find in string */
E 6
{
D 6
    register char *a, *b;
E 6
I 6
	register char *a, *b;
E 6

D 6
    /*
     * First scan quickly through the two strings looking for a
     * single-character match.  When it's found, then compare the
     * rest of the substring.
     */
    
    b = substring;
    for ( ; *string != 0; string += 1) {
	if (*string != *b) {
	    continue;
E 6
I 6
	/*
	 * First scan quickly through the two strings looking for a single-
	 * character match.  When it's found, then compare the rest of the
	 * substring.
	 */

	for (b = substring; *string != 0; string += 1) {
		if (*string != *b)
			continue;
		a = string;
		for (;;) {
			if (*b == 0)
				return(string);
			if (*a++ != *b++)
				break;
		}
		b = substring;
E 6
	}
D 6
	a = string;
	while (TRUE) {
	    if (*b == 0) {
		return string;
	    }
	    if (*a++ != *b++) {
		break;
	    }
	}
	b = substring;
    }
    return (char *) NULL;
E 6
I 6
	return((char *) NULL);
E 6
}
D 4

#endif /* !Sprite */
E 4
D 3

E 3
I 3

E 3
/*
D 6
 *----------------------------------------------------------------------
 *
E 6
 * Str_Match --
D 6
 *
 *      See if a particular string matches a particular pattern.
 *
 * Results:
 *      Non-zero is returned if string matches pattern, 0 otherwise.
 *      The matching operation permits the following special characters
 *      in the pattern: *?\[] (see the man page for details on what
 *      these mean).
 *
 * Side effects:
 *      None.
 *
 *----------------------------------------------------------------------
E 6
I 6
 * 
 * See if a particular string matches a particular pattern.
 * 
 * Results: Non-zero is returned if string matches pattern, 0 otherwise. The
 * matching operation permits the following special characters in the
 * pattern: *?\[] (see the man page for details on what these mean).
 * 
 * Side effects: None.
E 6
 */
I 9
int
E 9
D 6

int
E 6
Str_Match(string, pattern)
D 6
    register char *string;              /* String. */
    register char *pattern;             /* Pattern, which may contain
                                         * special characters.
                                         */
E 6
I 6
	register char *string;		/* String */
	register char *pattern;		/* Pattern */
E 6
{
D 6
    char c2;
E 6
I 6
	char c2;
E 6

D 6
    while (1) {
        /* See if we're at the end of both the pattern and the string.
         * If, we succeeded.  If we're at the end of the pattern but
         * not at the end of the string, we failed.
         */
        
        if (*pattern == 0) {
            if (*string == 0) {
                return 1;
            } else {
                return 0;
            }
        }
        if ((*string == 0) && (*pattern != '*')) {
            return 0;
        }

        /* Check for a "*" as the next pattern character.  It matches
         * any substring.  We handle this by calling ourselves
         * recursively for each postfix of string, until either we
         * match or we reach the end of the string.
         */
        
        if (*pattern == '*') {
            pattern += 1;
            if (*pattern == 0) {
                return 1;
            }
            while (*string != 0) {
                if (Str_Match(string, pattern)) {
                    return 1;
                }
                string += 1;
            }
            return 0;
        }
    
        /* Check for a "?" as the next pattern character.  It matches
         * any single character.
         */

        if (*pattern == '?') {
            goto thisCharOK;
        }

        /* Check for a "[" as the next pattern character.  It is followed
         * by a list of characters that are acceptable, or by a range
         * (two characters separated by "-").
         */
        
        if (*pattern == '[') {
            pattern += 1;
            while (1) {
                if ((*pattern == ']') || (*pattern == 0)) {
                    return 0;
                }
                if (*pattern == *string) {
                    break;
                }
                if (pattern[1] == '-') {
                    c2 = pattern[2];
                    if (c2 == 0) {
                        return 0;
                    }
                    if ((*pattern <= *string) && (c2 >= *string)) {
                        break;
                    }
                    if ((*pattern >= *string) && (c2 <= *string)) {
                        break;
                    }
                    pattern += 2;
                }
                pattern += 1;
            }
            while ((*pattern != ']') && (*pattern != 0)) {
                pattern += 1;
            }
            goto thisCharOK;
        }
    
        /* If the next pattern character is '/', just strip off the '/'
         * so we do exact matching on the character that follows.
         */
        
        if (*pattern == '\\') {
            pattern += 1;
            if (*pattern == 0) {
                return 0;
            }
        }

        /* There's no special character.  Just make sure that the next
         * characters of each string match.
         */
        
        if (*pattern != *string) {
            return 0;
        }

        thisCharOK: pattern += 1;
        string += 1;
    }
E 6
I 6
	for (;;) {
		/*
		 * See if we're at the end of both the pattern and the
		 * string. If, we succeeded.  If we're at the end of the
		 * pattern but not at the end of the string, we failed.
		 */
		if (*pattern == 0)
			return(!*string);
		if (*string == 0 && *pattern != '*')
			return(0);
		/*
		 * Check for a "*" as the next pattern character.  It matches
		 * any substring.  We handle this by calling ourselves
		 * recursively for each postfix of string, until either we
		 * match or we reach the end of the string.
		 */
		if (*pattern == '*') {
			pattern += 1;
			if (*pattern == 0)
				return(1);
			while (*string != 0) {
				if (Str_Match(string, pattern))
					return(1);
				++string;
			}
			return(0);
		}
		/*
		 * Check for a "?" as the next pattern character.  It matches
		 * any single character.
		 */
		if (*pattern == '?')
			goto thisCharOK;
		/*
		 * Check for a "[" as the next pattern character.  It is
		 * followed by a list of characters that are acceptable, or
		 * by a range (two characters separated by "-").
		 */
		if (*pattern == '[') {
			++pattern;
			for (;;) {
				if ((*pattern == ']') || (*pattern == 0))
					return(0);
				if (*pattern == *string)
					break;
				if (pattern[1] == '-') {
					c2 = pattern[2];
					if (c2 == 0)
						return(0);
					if ((*pattern <= *string) &&
					    (c2 >= *string))
						break;
					if ((*pattern >= *string) &&
					    (c2 <= *string))
						break;
					pattern += 2;
				}
				++pattern;
			}
			while ((*pattern != ']') && (*pattern != 0))
				++pattern;
			goto thisCharOK;
		}
		/*
		 * If the next pattern character is '/', just strip off the
		 * '/' so we do exact matching on the character that follows.
		 */
		if (*pattern == '\\') {
			++pattern;
			if (*pattern == 0)
				return(0);
		}
		/*
		 * There's no special character.  Just make sure that the
		 * next characters of each string match.
		 */
		if (*pattern != *string)
			return(0);
thisCharOK:	++pattern;
		++string;
	}
E 6
}
I 13


/*-
 *-----------------------------------------------------------------------
 * Str_SYSVMatch --
 *	Check word against pattern for a match (% is wild), 
 *	
 * Results:
 *	Returns the beginning position of a match or null. The number
 *	of characters matched is returned in len.
 *
 * Side Effects:
 *	None
 *
 *-----------------------------------------------------------------------
 */
char *
Str_SYSVMatch(word, pattern, len)
    char	*word;		/* Word to examine */
    char	*pattern;	/* Pattern to examine against */
    int		*len;		/* Number of characters to substitute */
{
    char *p = pattern;
    char *w = word;
    char *m;

D 14
    if (*p == '\0')
	return NULL;
E 14
I 14
    if (*p == '\0') {
	/* Null pattern is the whole string */
	*len = strlen(w);
	return w;
    }
E 14

    if ((m = strchr(p, '%')) != NULL) {
	/* check that the prefix matches */
	for (; p != m && *w && *w == *p; w++, p++)
	     continue;

	if (p != m)
	    return NULL;	/* No match */

	if (*++p == '\0') {
	    /* No more pattern, return the rest of the string */
	    *len = strlen(w);
	    return w;
	}
    }

    m = w;

    /* Find a matching tail */
    do
	if (strcmp(p, w) == 0) {
	    *len = w - m;
	    return m;
	}
    while (*w++ != '\0');
	    
    return NULL;
}


/*-
 *-----------------------------------------------------------------------
 * Str_SYSVSubst --
 *	Substitute '%' on the pattern with len characters from src.
 *	If the pattern does not contain a '%' prepend len characters
 *	from src.
 *	
 * Results:
 *	None
 *
 * Side Effects:
 *	Places result on buf
 *
 *-----------------------------------------------------------------------
 */
void
Str_SYSVSubst(buf, pat, src, len)
    Buffer buf;
    char *pat;
    char *src;
    int   len;
{
    char *m;

    if ((m = strchr(pat, '%')) != NULL) {
	/* Copy the prefix */
	Buf_AddBytes(buf, m - pat, (Byte *) pat);
	/* skip the % */
	pat = m + 1;
    }

    /* Copy the pattern */
    Buf_AddBytes(buf, len, (Byte *) src);

    /* append the rest */
    Buf_AddBytes(buf, strlen(pat), (Byte *) pat);
}
E 13
E 1
