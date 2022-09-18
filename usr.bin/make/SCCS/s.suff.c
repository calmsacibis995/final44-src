h01299
s 00366/00149/02043
d D 8.5 95/04/28 17:08:27 christos 14 12
c Updated to the latest version from the NetBSD source
e
s 00000/00001/02191
d R 8.5 94/04/18 13:52:04 bostic 13 12
c back out revision 8.2 - it broke other system Makefiles
e
s 00033/00001/02159
d D 8.4 94/03/21 17:47:33 bostic 12 11
c Null Suffixes were not being copied, but they were being free'd
c My recent fixes to parse ${VAR:%.foo=%.bar} handled the null string
c case incorrectly (${VAR:=.c} was broken).
c From: Christos Zoulas <christos@deshaw.com>
e
s 00002/00000/02158
d D 8.3 94/03/19 15:56:48 christos 11 10
c initialize targ->children
e
s 00001/00000/02157
d D 8.2 94/01/02 15:06:33 bostic 10 8
c % mkdir obj
c % touch foo.c README
c % cat Makefile
c all :: foo.c README
c         echo ${.OODATE}
c Notice that it expands the path for the .c file, but not for README.
c This is because the search path for the null suffix is empty and it
c should be the default search path.
c From: christos@deshaw.com (Christos Zoulas)
e
s 00001/00000/02157
d R 8.2 94/01/02 15:02:20 bostic 9 8
c 
e
s 00002/00002/02155
d D 8.1 93/06/06 15:17:19 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00057/00033/02100
d D 5.7 93/05/24 14:46:00 bostic 7 6
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00011/02132
d D 5.6 90/06/01 17:09:50 bostic 6 5
c new copyright notice
e
s 00011/00011/02132
d D 5.5 90/03/19 09:57:36 bostic 5 4
c replace malloc with emalloc; Str_Concat -> str_concat
e
s 00001/00023/02142
d D 5.4 90/03/12 12:20:08 bostic 4 3
c rework to always be "make".  Deleted -M, -B, -C, -v.  Partial deletion
c of .NULL.  Never remove leading components in file search.  # is always a
c comment.  Print usage line, not message.  Make vararg'd routines right.
e
s 00038/00039/02127
d D 5.3 90/03/12 08:59:56 bostic 3 2
c Str_New -> strdup
e
s 00026/00015/02140
d D 5.2 90/03/11 15:39:27 bostic 2 1
c add Berkeley specific copyright notice
e
s 02155/00000/00000
d D 5.1 90/03/11 15:27:50 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
D 8
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 8
I 8
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/*-
 * suff.c --
 *	Functions to maintain suffix lists and find implicit dependents
 *	using suffix transformation rules
 *
D 2
 * Copyright (c) 1988, 1989 by the Regents of the University of California
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any non-commercial purpose
 * and without fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  The University of California,
 * Berkeley Softworks and Adam de Boor make no representations about
 * the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
E 2
 * Interface:
 *	Suff_Init 	    	Initialize all things to do with suffixes.
 *
I 14
 *	Suff_End 	    	Cleanup the module
 *
E 14
 *	Suff_DoPaths	    	This function is used to make life easier
 *	    	  	    	when searching for a file according to its
 *	    	  	    	suffix. It takes the global search path,
 *	    	  	    	as defined using the .PATH: target, and appends
 *	    	  	    	its directories to the path of each of the
 *	    	  	    	defined suffixes, as specified using
 *	    	  	    	.PATH<suffix>: targets. In addition, all
 *	    	  	    	directories given for suffixes labeled as
 *	    	  	    	include files or libraries, using the .INCLUDES
 *	    	  	    	or .LIBS targets, are played with using
 *	    	  	    	Dir_MakeFlags to create the .INCLUDES and
 *	    	  	    	.LIBS global variables.
 *
 *	Suff_ClearSuffixes  	Clear out all the suffixes and defined
 *	    	  	    	transformations.
 *
 *	Suff_IsTransform    	Return TRUE if the passed string is the lhs
 *	    	  	    	of a transformation rule.
 *
 *	Suff_AddSuffix	    	Add the passed string as another known suffix.
 *
 *	Suff_GetPath	    	Return the search path for the given suffix.
 *
 *	Suff_AddInclude	    	Mark the given suffix as denoting an include
 *	    	  	    	file.
 *
 *	Suff_AddLib	    	Mark the given suffix as denoting a library.
 *
 *	Suff_AddTransform   	Add another transformation to the suffix
 *	    	  	    	graph. Returns  GNode suitable for framing, I
 *	    	  	    	mean, tacking commands, attributes, etc. on.
 *
 *	Suff_SetNull	    	Define the suffix to consider the suffix of
 *	    	  	    	any file that doesn't have a known one.
 *
 *	Suff_FindDeps	    	Find implicit sources for and the location of
 *	    	  	    	a target based on its suffix. Returns the
 *	    	  	    	bottom-most node added to the graph or NILGNODE
 *	    	  	    	if the target had no implicit sources.
 */
D 2
#ifndef lint
static char     *rcsid = "$Id: suff.c,v 1.68 89/11/14 13:44:09 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

#include    	  <stdio.h>
#include	  "make.h"
I 7
#include	  "hash.h"
#include	  "dir.h"
E 7
#include    	  "bit.h"

static Lst       sufflist;	/* Lst of suffixes */
I 14
static Lst	 suffClean;	/* Lst of suffixes to be cleaned */
static Lst	 srclist;	/* Lst of sources */
E 14
static Lst       transforms;	/* Lst of transformation rules */

static int        sNum = 0;	/* Counter for assigning suffix numbers */

/*
 * Structure describing an individual suffix.
 */
typedef struct _Suff {
    char         *name;	    	/* The suffix itself */
    int		 nameLen;	/* Length of the suffix */
    short	 flags;      	/* Type of suffix */
#define SUFF_INCLUDE	  0x01	    /* One which is #include'd */
#define SUFF_LIBRARY	  0x02	    /* One which contains a library */
#define SUFF_NULL 	  0x04	    /* The empty suffix */
    Lst    	 searchPath;	/* The path along which files of this suffix
				 * may be found */
    int          sNum;	      	/* The suffix number */
I 14
    int		 refCount;	/* Reference count of list membership */
E 14
    Lst          parents;	/* Suffixes we have a transformation to */
    Lst          children;	/* Suffixes we have a transformation from */
I 14
    Lst		 ref;		/* List of lists this suffix is referenced */
E 14
} Suff;

/*
 * Structure used in the search for implied sources.
 */
typedef struct _Src {
    char            *file;	/* The file to look for */
    char    	    *pref;  	/* Prefix from which file was formed */
    Suff            *suff;	/* The suffix on the file */
    struct _Src     *parent;	/* The Src for which this is a source */
    GNode           *node;	/* The node describing the file */
    int	    	    children;	/* Count of existing children (so we don't free
				 * this thing too early or never nuke it) */
I 14
#ifdef DEBUG_SRC
    Lst		    cp;		/* Debug; children list */
#endif
E 14
} Src;

I 7
/*
 * A structure for passing more than one argument to the Lst-library-invoked
 * function...
 */
typedef struct {
    Lst            l;
    Src            *s;
} LstSrc;

E 7
static Suff 	    *suffNull;	/* The NULL suffix for this run */
static Suff 	    *emptySuff;	/* The empty suffix required for POSIX
				 * single-suffix transformation rules */

I 7

static char *SuffStrIsPrefix __P((char *, char *));
static char *SuffSuffIsSuffix __P((Suff *, char *));
D 14
static int SuffSuffIsSuffixP __P((Suff *, char *));
static int SuffSuffHasNameP __P((Suff *, char *));
static int SuffSuffIsPrefix __P((Suff *, char *));
static int SuffGNHasNameP __P((GNode *, char *));
static void SuffFree __P((Suff *));
I 12
static Suff* SuffCopy __P((Suff *));
E 14
I 14
static int SuffSuffIsSuffixP __P((ClientData, ClientData));
static int SuffSuffHasNameP __P((ClientData, ClientData));
static int SuffSuffIsPrefix __P((ClientData, ClientData));
static int SuffGNHasNameP __P((ClientData, ClientData));
static void SuffFree __P((ClientData));
E 14
E 12
static void SuffInsert __P((Lst, Suff *));
I 14
static void SuffRemove __P((Lst, Suff *));
E 14
static Boolean SuffParseTransform __P((char *, Suff **, Suff **));
D 14
static int SuffRebuildGraph __P((GNode *, Suff *));
static int SuffAddSrc __P((Suff *, LstSrc *));
E 14
I 14
static int SuffRebuildGraph __P((ClientData, ClientData));
static int SuffAddSrc __P((ClientData, ClientData));
static int SuffRemoveSrc __P((Lst));
E 14
static void SuffAddLevel __P((Lst, Src *));
D 14
static void SuffFreeSrc __P((Src *));
static Src *SuffFindThem __P((Lst));
static Src *SuffFindCmds __P((Src *));
static int SuffExpandChildren __P((GNode *, GNode *));
E 14
I 14
static Src *SuffFindThem __P((Lst, Lst));
static Src *SuffFindCmds __P((Src *, Lst));
static int SuffExpandChildren __P((ClientData, ClientData));
E 14
static Boolean SuffApplyTransform __P((GNode *, GNode *, Suff *, Suff *));
D 14
static void SuffFindArchiveDeps __P((GNode *));
static void SuffFindNormalDeps __P((GNode *));
static int SuffPrintName __P((Suff *));
static int SuffPrintSuff __P((Suff *));
static int SuffPrintTrans __P((GNode *));
E 14
I 14
static void SuffFindDeps __P((GNode *, Lst));
static void SuffFindArchiveDeps __P((GNode *, Lst));
static void SuffFindNormalDeps __P((GNode *, Lst));
static int SuffPrintName __P((ClientData, ClientData));
static int SuffPrintSuff __P((ClientData, ClientData));
static int SuffPrintTrans __P((ClientData, ClientData));
E 14

E 7
D 3

 	/*************** Lst Predicates ****************/
E 3
I 3
	/*************** Lst Predicates ****************/
E 3
/*-
 *-----------------------------------------------------------------------
 * SuffStrIsPrefix  --
 *	See if pref is a prefix of str.
 *
 * Results:
 *	NULL if it ain't, pointer to character in str after prefix if so
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static char    *
SuffStrIsPrefix (pref, str)
    register char  *pref;	/* possible prefix */
    register char  *str;	/* string to check */
{
    while (*str && *pref == *str) {
	pref++;
	str++;
    }

    return (*pref ? NULL : str);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffSuffIsSuffix  --
 *	See if suff is a suffix of str. Str should point to THE END of the
 *	string to check. (THE END == the null byte)
 *
 * Results:
 *	NULL if it ain't, pointer to character in str before suffix if
 *	it is.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static char *
SuffSuffIsSuffix (s, str)
    register Suff  *s;		/* possible suffix */
    char           *str;	/* string to examine */
{
    register char  *p1;	    	/* Pointer into suffix name */
    register char  *p2;	    	/* Pointer into string being examined */

    p1 = s->name + s->nameLen;
    p2 = str;

    while (p1 >= s->name && *p1 == *p2) {
	p1--;
	p2--;
    }

    return (p1 == s->name - 1 ? p2 : NULL);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffSuffIsSuffixP --
 *	Predicate form of SuffSuffIsSuffix. Passed as the callback function
 *	to Lst_Find.
 *
 * Results:
 *	0 if the suffix is the one desired, non-zero if not.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
I 7
static int
E 7
SuffSuffIsSuffixP(s, str)
D 14
    Suff    	*s;
    char    	*str;
E 14
I 14
    ClientData   s;
    ClientData   str;
E 14
{
D 14
    return(!SuffSuffIsSuffix(s, str));
E 14
I 14
    return(!SuffSuffIsSuffix((Suff *) s, (char *) str));
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffSuffHasNameP --
 *	Callback procedure for finding a suffix based on its name. Used by
 *	Suff_GetPath.
 *
 * Results:
 *	0 if the suffix is of the given name. non-zero otherwise.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
SuffSuffHasNameP (s, sname)
D 14
    Suff    *s;	    	    /* Suffix to check */
    char    *sname; 	    /* Desired name */
E 14
I 14
    ClientData    s;	    	    /* Suffix to check */
    ClientData    sname; 	    /* Desired name */
E 14
{
D 14
    return (strcmp (sname, s->name));
E 14
I 14
    return (strcmp ((char *) sname, ((Suff *) s)->name));
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffSuffIsPrefix  --
 *	See if the suffix described by s is a prefix of the string. Care
 *	must be taken when using this to search for transformations and
 *	what-not, since there could well be two suffixes, one of which
 *	is a prefix of the other...
 *
 * Results:
 *	0 if s is a prefix of str. non-zero otherwise
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
SuffSuffIsPrefix (s, str)
D 14
    Suff           *s;		/* suffix to compare */
    char           *str;	/* string to examine */
E 14
I 14
    ClientData   s;		/* suffix to compare */
    ClientData   str;	/* string to examine */
E 14
{
D 14
    return (SuffStrIsPrefix (s->name, str) == NULL ? 1 : 0);
E 14
I 14
    return (SuffStrIsPrefix (((Suff *) s)->name, (char *) str) == NULL ? 1 : 0);
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffGNHasNameP  --
 *	See if the graph node has the desired name
 *
 * Results:
 *	0 if it does. non-zero if it doesn't
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
SuffGNHasNameP (gn, name)
D 14
    GNode          *gn;		/* current node we're looking at */
    char           *name;	/* name we're looking for */
E 14
I 14
    ClientData      gn;		/* current node we're looking at */
    ClientData      name;	/* name we're looking for */
E 14
{
D 14
    return (strcmp (name, gn->name));
E 14
I 14
    return (strcmp ((char *) name, ((GNode *) gn)->name));
E 14
}
D 3

E 3
I 3

E 3
 	    /*********** Maintenance Functions ************/
I 14

static void
SuffUnRef(lp, sp)
    ClientData lp;
    ClientData sp;
{
    Lst l = (Lst) lp;

    LstNode ln = Lst_Member(l, sp);
    if (ln != NILLNODE) {
	Lst_Remove(l, ln);
	((Suff *) sp)->refCount--;
    }
}

E 14
/*-
 *-----------------------------------------------------------------------
 * SuffFree  --
 *	Free up all memory associated with the given suffix structure.
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	the suffix entry is detroyed
 *-----------------------------------------------------------------------
 */
static void
D 14
SuffFree (s)
    Suff           *s;
E 14
I 14
SuffFree (sp)
    ClientData sp;
E 14
{
I 14
    Suff           *s = (Suff *) sp;

    if (s == suffNull)
	suffNull = NULL;

    if (s == emptySuff)
	emptySuff = NULL;

    Lst_Destroy (s->ref, NOFREE);
E 14
    Lst_Destroy (s->children, NOFREE);
    Lst_Destroy (s->parents, NOFREE);
    Lst_Destroy (s->searchPath, Dir_Destroy);
I 14

E 14
    free ((Address)s->name);
    free ((Address)s);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
I 14
 * SuffRemove  --
 *	Remove the suffix into the list
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The reference count for the suffix is decremented and the
 *	suffix is possibly freed
 *-----------------------------------------------------------------------
 */
static void
SuffRemove(l, s)
    Lst l;
    Suff *s;
{
    SuffUnRef((ClientData) l, (ClientData) s);
    if (s->refCount == 0)
	SuffFree((ClientData) s);
}

/*-
 *-----------------------------------------------------------------------
E 14
 * SuffInsert  --
 *	Insert the suffix into the list keeping the list ordered by suffix
 *	numbers.
 *
 * Results:
 *	None
 *
 * Side Effects:
D 14
 *	Not really
E 14
I 14
 *	The reference count of the suffix is incremented
E 14
 *-----------------------------------------------------------------------
 */
static void
SuffInsert (l, s)
    Lst           l;		/* the list where in s should be inserted */
    Suff          *s;		/* the suffix to insert */
{
    LstNode 	  ln;		/* current element in l we're examining */
D 7
    Suff          *s2;		/* the suffix descriptor in this element */
E 7
I 7
    Suff          *s2 = NULL;	/* the suffix descriptor in this element */
E 7

    if (Lst_Open (l) == FAILURE) {
	return;
    }
    while ((ln = Lst_Next (l)) != NILLNODE) {
	s2 = (Suff *) Lst_Datum (ln);
	if (s2->sNum >= s->sNum) {
	    break;
	}
    }

    Lst_Close (l);
    if (DEBUG(SUFF)) {
	printf("inserting %s(%d)...", s->name, s->sNum);
    }
    if (ln == NILLNODE) {
	if (DEBUG(SUFF)) {
	    printf("at end of list\n");
	}
	(void)Lst_AtEnd (l, (ClientData)s);
I 14
	s->refCount++;
	(void)Lst_AtEnd(s->ref, (ClientData) l);
E 14
    } else if (s2->sNum != s->sNum) {
	if (DEBUG(SUFF)) {
	    printf("before %s(%d)\n", s2->name, s2->sNum);
	}
	(void)Lst_Insert (l, ln, (ClientData)s);
I 14
	s->refCount++;
	(void)Lst_AtEnd(s->ref, (ClientData) l);
E 14
    } else if (DEBUG(SUFF)) {
	printf("already there\n");
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_ClearSuffixes --
 *	This is gross. Nuke the list of suffixes but keep all transformation
 *	rules around. The transformation graph is destroyed in this process,
 *	but we leave the list of rules so when a new graph is formed the rules
 *	will remain.
 *	This function is called from the parse module when a
 *	.SUFFIXES:\n line is encountered.
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	the sufflist and its graph nodes are destroyed
 *-----------------------------------------------------------------------
 */
void
Suff_ClearSuffixes ()
{
D 14
    Lst_Destroy (sufflist, SuffFree);

E 14
I 14
    Lst_Concat (suffClean, sufflist, LST_CONCLINK);
E 14
    sufflist = Lst_Init(FALSE);
    sNum = 0;
    suffNull = emptySuff;
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffParseTransform --
 *	Parse a transformation string to find its two component suffixes.
 *
 * Results:
 *	TRUE if the string is a valid transformation and FALSE otherwise.
 *
 * Side Effects:
 *	The passed pointers are overwritten.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
SuffParseTransform(str, srcPtr, targPtr)
    char    	  	*str;	    	/* String being parsed */
    Suff    	  	**srcPtr;   	/* Place to store source of trans. */
    Suff    	  	**targPtr;  	/* Place to store target of trans. */
{
    register LstNode	srcLn;	    /* element in suffix list of trans source*/
    register Suff    	*src;	    /* Source of transformation */
    register LstNode    targLn;	    /* element in suffix list of trans target*/
    register char    	*str2;	    /* Extra pointer (maybe target suffix) */
    LstNode 	    	singleLn;   /* element in suffix list of any suffix
				     * that exactly matches str */
D 7
    Suff    	    	*single;    /* Source of possible transformation to
E 7
I 7
    Suff    	    	*single = NULL;/* Source of possible transformation to
E 7
				     * null suffix */

    srcLn = NILLNODE;
    singleLn = NILLNODE;
    
    /*
     * Loop looking first for a suffix that matches the start of the
     * string and then for one that exactly matches the rest of it. If
     * we can find two that meet these criteria, we've successfully
     * parsed the string.
     */
D 7
    while (1) {
E 7
I 7
    for (;;) {
E 7
	if (srcLn == NILLNODE) {
	    srcLn = Lst_Find(sufflist, (ClientData)str, SuffSuffIsPrefix);
	} else {
	    srcLn = Lst_FindFrom (sufflist, Lst_Succ(srcLn), (ClientData)str,
				  SuffSuffIsPrefix);
	}
	if (srcLn == NILLNODE) {
	    /*
	     * Ran out of source suffixes -- no such rule
	     */
	    if (singleLn != NILLNODE) {
		/*
		 * Not so fast Mr. Smith! There was a suffix that encompassed
		 * the entire string, so we assume it was a transformation
		 * to the null suffix (thank you POSIX). We still prefer to
		 * find a double rule over a singleton, hence we leave this
		 * check until the end.
		 *
		 * XXX: Use emptySuff over suffNull?
		 */
		*srcPtr = single;
D 12
		*targPtr = suffNull;
E 12
I 12
D 14
		*targPtr = SuffCopy(suffNull);
E 14
I 14
		*targPtr = suffNull;
E 14
E 12
		return(TRUE);
	    }
	    return (FALSE);
	}
	src = (Suff *) Lst_Datum (srcLn);
	str2 = str + src->nameLen;
	if (*str2 == '\0') {
	    single = src;
	    singleLn = srcLn;
	} else {
	    targLn = Lst_Find(sufflist, (ClientData)str2, SuffSuffHasNameP);
	    if (targLn != NILLNODE) {
		*srcPtr = src;
		*targPtr = (Suff *)Lst_Datum(targLn);
		return (TRUE);
	    }
	}
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_IsTransform  --
 *	Return TRUE if the given string is a transformation rule
 *
 *
 * Results:
 *	TRUE if the string is a concatenation of two known suffixes.
 *	FALSE otherwise
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Suff_IsTransform (str)
    char          *str;	    	/* string to check */
{
    Suff    	  *src, *targ;

    return (SuffParseTransform(str, &src, &targ));
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_AddTransform --
 *	Add the transformation rule described by the line to the
 *	list of rules and place the transformation itself in the graph
 *
 * Results:
 *	The node created for the transformation in the transforms list
 *
 * Side Effects:
 *	The node is placed on the end of the transforms Lst and links are
 *	made between the two suffixes mentioned in the target name
 *-----------------------------------------------------------------------
 */
GNode *
Suff_AddTransform (line)
    char          *line;	/* name of transformation to add */
{
    GNode         *gn;		/* GNode of transformation rule */
    Suff          *s,		/* source suffix */
                  *t;		/* target suffix */
    LstNode 	  ln;	    	/* Node for existing transformation */

    ln = Lst_Find (transforms, (ClientData)line, SuffGNHasNameP);
    if (ln == NILLNODE) {
	/*
	 * Make a new graph node for the transformation. It will be filled in
	 * by the Parse module. 
	 */
	gn = Targ_NewGN (line);
	(void)Lst_AtEnd (transforms, (ClientData)gn);
    } else {
	/*
	 * New specification for transformation rule. Just nuke the old list
	 * of commands so they can be filled in again... We don't actually
	 * free the commands themselves, because a given command can be
	 * attached to several different transformations.
	 */
	gn = (GNode *) Lst_Datum (ln);
	Lst_Destroy (gn->commands, NOFREE);
	Lst_Destroy (gn->children, NOFREE);
	gn->commands = Lst_Init (FALSE);
	gn->children = Lst_Init (FALSE);
    }

    gn->type = OP_TRANSFORM;

    (void)SuffParseTransform(line, &s, &t);

    /*
     * link the two together in the proper relationship and order 
     */
    if (DEBUG(SUFF)) {
	printf("defining transformation from `%s' to `%s'\n",
		s->name, t->name);
    }
    SuffInsert (t->children, s);
    SuffInsert (s->parents, t);

    return (gn);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_EndTransform --
 *	Handle the finish of a transformation definition, removing the
 *	transformation from the graph if it has neither commands nor
 *	sources. This is a callback procedure for the Parse module via
 *	Lst_ForEach
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	If the node has no commands or children, the children and parents
 *	lists of the affected suffices are altered.
 *
 *-----------------------------------------------------------------------
 */
int
D 14
Suff_EndTransform(gn)
    GNode   *gn;    	/* Node for transformation */
E 14
I 14
Suff_EndTransform(gnp, dummy)
    ClientData   gnp;    	/* Node for transformation */
    ClientData   dummy;    	/* Node for transformation */
E 14
{
I 14
    GNode *gn = (GNode *) gnp;
 
E 14
    if ((gn->type & OP_TRANSFORM) && Lst_IsEmpty(gn->commands) &&
	Lst_IsEmpty(gn->children))
    {
	Suff	*s, *t;
D 14
	LstNode	ln;
E 14

	(void)SuffParseTransform(gn->name, &s, &t);

	if (DEBUG(SUFF)) {
	    printf("deleting transformation from %s to %s\n",
		    s->name, t->name);
	}

	/*
	 * Remove the source from the target's children list. We check for a
	 * nil return to handle a beanhead saying something like
	 *  .c.o .c.o:
	 *
	 * We'll be called twice when the next target is seen, but .c and .o
	 * are only linked once...
	 */
D 14
	ln = Lst_Member(t->children, (ClientData)s);
	if (ln != NILLNODE) {
	    (void)Lst_Remove(t->children, ln);
	}
E 14
I 14
	SuffRemove(t->children, s);
E 14

	/*
	 * Remove the target from the source's parents list
	 */
D 14
	ln = Lst_Member(s->parents, (ClientData)t);
	if (ln != NILLNODE) {
	    (void)Lst_Remove(s->parents, ln);
	}
E 14
I 14
	SuffRemove(s->parents, t);
E 14
    } else if ((gn->type & OP_TRANSFORM) && DEBUG(SUFF)) {
	printf("transformation %s complete\n", gn->name);
    }

D 14
    return(0);
E 14
I 14
    return(dummy ? 0 : 0);
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffRebuildGraph --
 *	Called from Suff_AddSuffix via Lst_ForEach to search through the
 *	list of existing transformation rules and rebuild the transformation
 *	graph when it has been destroyed by Suff_ClearSuffixes. If the
 *	given rule is a transformation involving this suffix and another,
 *	existing suffix, the proper relationship is established between
 *	the two.
 *
 * Results:
 *	Always 0.
 *
 * Side Effects:
 *	The appropriate links will be made between this suffix and
 *	others if transformation rules exist for it.
 *
 *-----------------------------------------------------------------------
 */
static int
D 14
SuffRebuildGraph(transform, s)
    GNode   	  	*transform; /* Transformation to test */
    Suff    	  	*s;	    /* Suffix to rebuild */
E 14
I 14
SuffRebuildGraph(transformp, sp)
    ClientData  transformp; /* Transformation to test */
    ClientData  sp;	    /* Suffix to rebuild */
E 14
{
D 14
    register char 	*cp;
    register LstNode	ln;
    register Suff  	*s2;
E 14
I 14
    GNode   	*transform = (GNode *) transformp;
    Suff    	*s = (Suff *) sp;
    char 	*cp;
    LstNode	ln;
    Suff  	*s2;
E 14

    /*
     * First see if it is a transformation from this suffix.
     */
    cp = SuffStrIsPrefix(s->name, transform->name);
    if (cp != (char *)NULL) {
	ln = Lst_Find(sufflist, (ClientData)cp, SuffSuffHasNameP);
	if (ln != NILLNODE) {
	    /*
	     * Found target. Link in and return, since it can't be anything
	     * else.
	     */
	    s2 = (Suff *)Lst_Datum(ln);
	    SuffInsert(s2->children, s);
	    SuffInsert(s->parents, s2);
	    return(0);
	}
    }

    /*
     * Not from, maybe to?
     */
    cp = SuffSuffIsSuffix(s, transform->name + strlen(transform->name));
    if (cp != (char *)NULL) {
	/*
	 * Null-terminate the source suffix in order to find it.
	 */
	cp[1] = '\0';
	ln = Lst_Find(sufflist, (ClientData)transform->name, SuffSuffHasNameP);
	/*
	 * Replace the start of the target suffix
	 */
	cp[1] = s->name[0];
	if (ln != NILLNODE) {
	    /*
	     * Found it -- establish the proper relationship
	     */
	    s2 = (Suff *)Lst_Datum(ln);
	    SuffInsert(s->children, s2);
	    SuffInsert(s2->parents, s);
	}
    }
    return(0);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_AddSuffix --
 *	Add the suffix in string to the end of the list of known suffixes.
 *	Should we restructure the suffix graph? Make doesn't...
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A GNode is created for the suffix and a Suff structure is created and
 *	added to the suffixes list unless the suffix was already known.
 *-----------------------------------------------------------------------
 */
void
Suff_AddSuffix (str)
    char          *str;	    /* the name of the suffix to add */
{
    Suff          *s;	    /* new suffix descriptor */
    LstNode 	  ln;

    ln = Lst_Find (sufflist, (ClientData)str, SuffSuffHasNameP);
    if (ln == NILLNODE) {
D 5
	s = (Suff *) malloc (sizeof (Suff));
E 5
I 5
	s = (Suff *) emalloc (sizeof (Suff));
E 5

D 3
	s->name =   	Str_New (str);
E 3
I 3
	s->name =   	strdup (str);
E 3
	s->nameLen = 	strlen (s->name);
	s->searchPath = Lst_Init (FALSE);
	s->children = 	Lst_Init (FALSE);
	s->parents = 	Lst_Init (FALSE);
I 14
	s->ref = 	Lst_Init (FALSE);
E 14
	s->sNum =   	sNum++;
	s->flags =  	0;
I 14
	s->refCount =	0;
E 14

	(void)Lst_AtEnd (sufflist, (ClientData)s);
	/*
	 * Look for any existing transformations from or to this suffix.
	 * XXX: Only do this after a Suff_ClearSuffixes?
	 */
	Lst_ForEach (transforms, SuffRebuildGraph, (ClientData)s);
    } 
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_GetPath --
 *	Return the search path for the given suffix, if it's defined.
 *
 * Results:
 *	The searchPath for the desired suffix or NILLST if the suffix isn't
 *	defined.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Lst
Suff_GetPath (sname)
    char    	  *sname;
{
    LstNode   	  ln;
    Suff    	  *s;

    ln = Lst_Find (sufflist, (ClientData)sname, SuffSuffHasNameP);
    if (ln == NILLNODE) {
	return (NILLST);
    } else {
	s = (Suff *) Lst_Datum (ln);
	return (s->searchPath);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_DoPaths --
 *	Extend the search paths for all suffixes to include the default
 *	search path.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The searchPath field of all the suffixes is extended by the
 *	directories in dirSearchPath. If paths were specified for the
 *	".h" suffix, the directories are stuffed into a global variable
 *	called ".INCLUDES" with each directory preceeded by a -I. The same
 *	is done for the ".a" suffix, except the variable is called
 *	".LIBS" and the flag is -L.
 *-----------------------------------------------------------------------
 */
void
Suff_DoPaths()
{
    register Suff   	*s;
    register LstNode  	ln;
I 14
    char		*ptr;
E 14
    Lst	    	    	inIncludes; /* Cumulative .INCLUDES path */
    Lst	    	    	inLibs;	    /* Cumulative .LIBS path */

    if (Lst_Open (sufflist) == FAILURE) {
	return;
    }

    inIncludes = Lst_Init(FALSE);
    inLibs = Lst_Init(FALSE);

    while ((ln = Lst_Next (sufflist)) != NILLNODE) {
	s = (Suff *) Lst_Datum (ln);
	if (!Lst_IsEmpty (s->searchPath)) {
#ifdef INCLUDES
	    if (s->flags & SUFF_INCLUDE) {
		Dir_Concat(inIncludes, s->searchPath);
	    }
#endif /* INCLUDES */
#ifdef LIBRARIES
	    if (s->flags & SUFF_LIBRARY) {
		Dir_Concat(inLibs, s->searchPath);
	    }
#endif /* LIBRARIES */
	    Dir_Concat(s->searchPath, dirSearchPath);
	} else {
	    Lst_Destroy (s->searchPath, Dir_Destroy);
	    s->searchPath = Lst_Duplicate(dirSearchPath, Dir_CopyDir);
	}
    }

D 14
    Var_Set(".INCLUDES", Dir_MakeFlags("-I", inIncludes), VAR_GLOBAL);
    Var_Set(".LIBS", Dir_MakeFlags("-L", inLibs), VAR_GLOBAL);
E 14
I 14
    Var_Set(".INCLUDES", ptr = Dir_MakeFlags("-I", inIncludes), VAR_GLOBAL);
    free(ptr);
    Var_Set(".LIBS", ptr = Dir_MakeFlags("-L", inLibs), VAR_GLOBAL);
    free(ptr);
E 14

    Lst_Destroy(inIncludes, Dir_Destroy);
    Lst_Destroy(inLibs, Dir_Destroy);

    Lst_Close (sufflist);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_AddInclude --
 *	Add the given suffix as a type of file which gets included.
 *	Called from the parse module when a .INCLUDES line is parsed.
 *	The suffix must have already been defined.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The SUFF_INCLUDE bit is set in the suffix's flags field
 *
 *-----------------------------------------------------------------------
 */
void
Suff_AddInclude (sname)
    char	  *sname;     /* Name of suffix to mark */
{
    LstNode	  ln;
    Suff	  *s;

    ln = Lst_Find (sufflist, (ClientData)sname, SuffSuffHasNameP);
    if (ln != NILLNODE) {
	s = (Suff *) Lst_Datum (ln);
	s->flags |= SUFF_INCLUDE;
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_AddLib --
 *	Add the given suffix as a type of file which is a library.
 *	Called from the parse module when parsing a .LIBS line. The
 *	suffix must have been defined via .SUFFIXES before this is
 *	called.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The SUFF_LIBRARY bit is set in the suffix's flags field
 *
 *-----------------------------------------------------------------------
 */
void
Suff_AddLib (sname)
    char	  *sname;     /* Name of suffix to mark */
{
    LstNode	  ln;
    Suff	  *s;

    ln = Lst_Find (sufflist, (ClientData)sname, SuffSuffHasNameP);
    if (ln != NILLNODE) {
	s = (Suff *) Lst_Datum (ln);
	s->flags |= SUFF_LIBRARY;
    }
}
D 3

E 3
I 3

E 3
 	  /********** Implicit Source Search Functions *********/
D 7
/*
 * A structure for passing more than one argument to the Lst-library-invoked
 * function...
 */
typedef struct {
    Lst            l;
    Src            *s;
} LstSrc;
E 7

/*-
 *-----------------------------------------------------------------------
 * SuffAddSrc  --
 *	Add a suffix as a Src structure to the given list with its parent
 *	being the given Src structure. If the suffix is the null suffix,
 *	the prefix is used unaltered as the file name in the Src structure.
 *
 * Results:
 *	always returns 0
 *
 * Side Effects:
 *	A Src structure is created and tacked onto the end of the list
 *-----------------------------------------------------------------------
 */
static int
D 14
SuffAddSrc (s, ls)
    Suff	*s;	    /* suffix for which to create a Src structure */
    LstSrc      *ls;	    /* list and parent for the new Src */
E 14
I 14
SuffAddSrc (sp, lsp)
    ClientData	sp;	    /* suffix for which to create a Src structure */
    ClientData  lsp;	    /* list and parent for the new Src */
E 14
{
I 14
    Suff	*s = (Suff *) sp;
    LstSrc      *ls = (LstSrc *) lsp;
E 14
    Src         *s2;	    /* new Src structure */
    Src    	*targ; 	    /* Target structure */

    targ = ls->s;
    
    if ((s->flags & SUFF_NULL) && (*s->name != '\0')) {
	/*
	 * If the suffix has been marked as the NULL suffix, also create a Src
	 * structure for a file with no suffix attached. Two birds, and all
	 * that...
	 */
D 5
	s2 = (Src *) malloc (sizeof (Src));
E 5
I 5
	s2 = (Src *) emalloc (sizeof (Src));
E 5
D 3
	s2->file =  	Str_New(targ->pref);
E 3
I 3
	s2->file =  	strdup(targ->pref);
E 3
	s2->pref =  	targ->pref;
	s2->parent = 	targ;
	s2->node =  	NILGNODE;
	s2->suff =  	s;
I 14
	s->refCount++;
E 14
	s2->children =	0;
	targ->children += 1;
	(void)Lst_AtEnd (ls->l, (ClientData)s2);
I 14
#ifdef DEBUG_SRC
	s2->cp = Lst_Init(FALSE);
	Lst_AtEnd(targ->cp, (ClientData) s2);
	printf("1 add %x %x to %x:", targ, s2, ls->l);
	Lst_ForEach(ls->l, PrintAddr, (ClientData) 0);
	printf("\n");
#endif
E 14
    }
D 5
    s2 = (Src *) malloc (sizeof (Src));
    s2->file = 	    Str_Concat (targ->pref, s->name, 0);
E 5
I 5
    s2 = (Src *) emalloc (sizeof (Src));
    s2->file = 	    str_concat (targ->pref, s->name, 0);
E 5
    s2->pref =	    targ->pref;
    s2->parent =    targ;
    s2->node = 	    NILGNODE;
    s2->suff = 	    s;
I 14
    s->refCount++;
E 14
    s2->children =  0;
    targ->children += 1;
    (void)Lst_AtEnd (ls->l, (ClientData)s2);
I 14
#ifdef DEBUG_SRC
    s2->cp = Lst_Init(FALSE);
    Lst_AtEnd(targ->cp, (ClientData) s2);
    printf("2 add %x %x to %x:", targ, s2, ls->l);
    Lst_ForEach(ls->l, PrintAddr, (ClientData) 0);
    printf("\n");
#endif
E 14

    return(0);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffAddLevel  --
 *	Add all the children of targ as Src structures to the given list
 *
 * Results:
 *	None
 *
 * Side Effects:
 * 	Lots of structures are created and added to the list
 *-----------------------------------------------------------------------
 */
static void
SuffAddLevel (l, targ)
    Lst            l;		/* list to which to add the new level */
    Src            *targ;	/* Src structure to use as the parent */
{
    LstSrc         ls;

    ls.s = targ;
    ls.l = l;

    Lst_ForEach (targ->suff->children, SuffAddSrc, (ClientData)&ls);
}
D 3

E 3
I 3

E 3
/*-
 *----------------------------------------------------------------------
D 14
 * SuffFreeSrc --
 *	Free all memory associated with a Src structure
E 14
I 14
 * SuffRemoveSrc --
 *	Free all src structures in list that don't have a reference count
E 14
 *
 * Results:
D 14
 *	None
E 14
I 14
 *	Ture if an src was removed
E 14
 *
 * Side Effects:
 *	The memory is free'd.
 *----------------------------------------------------------------------
 */
D 14
static void
SuffFreeSrc (s)
    Src            *s;
E 14
I 14
static int
SuffRemoveSrc (l)
    Lst l;
E 14
{
D 14
    free ((Address)s->file);
    if (!s->parent) {
	free((Address)s->pref);
    } else if (--s->parent->children == 0 && s->parent->parent) {
	/*
	 * Parent has no more children, now we're gone, and it's not
	 * at the top of the tree, so blow it away too.
	 */
	SuffFreeSrc(s->parent);
E 14
I 14
    LstNode ln;
    Src *s;
    int t = 0;

    if (Lst_Open (l) == FAILURE) {
	return 0;
E 14
    }
D 14
    free ((Address)s);
E 14
I 14
#ifdef DEBUG_SRC
    printf("cleaning %lx: ", (unsigned long) l);
    Lst_ForEach(l, PrintAddr, (ClientData) 0);
    printf("\n");
#endif


    while ((ln = Lst_Next (l)) != NILLNODE) {
	s = (Src *) Lst_Datum (ln);
	if (s->children == 0) {
	    free ((Address)s->file);
	    if (!s->parent)
		free((Address)s->pref);
	    else {
#ifdef DEBUG_SRC
		LstNode ln = Lst_Member(s->parent->cp, (ClientData)s);
		if (ln != NILLNODE)
		    Lst_Remove(s->parent->cp, ln);
#endif
		--s->parent->children;
	    }
#ifdef DEBUG_SRC
	    printf("free: [l=%x] p=%x %d\n", l, s, s->children);
	    Lst_Destroy(s->cp, NOFREE);
#endif
	    Lst_Remove(l, ln);
	    free ((Address)s);
	    t |= 1;
	    Lst_Close(l);
	    return TRUE;
	}
#ifdef DEBUG_SRC
	else {
	    printf("keep: [l=%x] p=%x %d: ", l, s, s->children);
	    Lst_ForEach(s->cp, PrintAddr, (ClientData) 0);
	    printf("\n");
	}
#endif
    }

    Lst_Close(l);

    return t;
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffFindThem --
 *	Find the first existing file/target in the list srcs
 *
 * Results:
 *	The lowest structure in the chain of transformations
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static Src *
D 14
SuffFindThem (srcs)
E 14
I 14
SuffFindThem (srcs, slst)
E 14
    Lst            srcs;	/* list of Src structures to search through */
I 14
    Lst		   slst;
E 14
{
    Src            *s;		/* current Src */
    Src		   *rs;		/* returned Src */
I 14
    char	   *ptr;
E 14

    rs = (Src *) NULL;

    while (!Lst_IsEmpty (srcs)) {
	s = (Src *) Lst_DeQueue (srcs);

	if (DEBUG(SUFF)) {
	    printf ("\ttrying %s...", s->file);
	}
I 14

E 14
	/*
	 * A file is considered to exist if either a node exists in the
	 * graph for it or the file actually exists.
	 */
D 14
	if ((Targ_FindNode(s->file, TARG_NOCREATE) != NILGNODE) ||
	    (Dir_FindFile (s->file, s->suff->searchPath) != (char *) NULL))
	{
	    if (DEBUG(SUFF)) {
		printf ("got it\n");
	    }
E 14
I 14
	if (Targ_FindNode(s->file, TARG_NOCREATE) != NILGNODE) {
#ifdef DEBUG_SRC
	    printf("remove %x from %x\n", s, srcs);
#endif
E 14
	    rs = s;
	    break;
D 14
	} else {
	    if (DEBUG(SUFF)) {
		printf ("not there\n");
	    }
	    SuffAddLevel (srcs, s);
E 14
	}
I 14

	if ((ptr = Dir_FindFile (s->file, s->suff->searchPath)) != NULL) {
	    rs = s;
#ifdef DEBUG_SRC
	    printf("remove %x from %x\n", s, srcs);
#endif
	    free(ptr);
	    break;
	}

	if (DEBUG(SUFF)) {
	    printf ("not there\n");
	}

	SuffAddLevel (srcs, s);
	Lst_AtEnd(slst, (ClientData) s);
E 14
    }
I 14

    if (DEBUG(SUFF) && rs) {
	printf ("got it\n");
    }
E 14
    return (rs);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffFindCmds --
 *	See if any of the children of the target in the Src structure is
 *	one from which the target can be transformed. If there is one,
 *	a Src structure is put together for it and returned.
 *
 * Results:
 *	The Src structure of the "winning" child, or NIL if no such beast.
 *
 * Side Effects:
 *	A Src structure may be allocated.
 *
 *-----------------------------------------------------------------------
 */
static Src *
D 14
SuffFindCmds (targ)
    Src	    	  	*targ;	/* Src structure to play with */
E 14
I 14
SuffFindCmds (targ, slst)
    Src	    	*targ;	/* Src structure to play with */
    Lst		slst;
E 14
{
    LstNode 	  	ln; 	/* General-purpose list node */
    register GNode	*t, 	/* Target GNode */
	    	  	*s; 	/* Source GNode */
    int	    	  	prefLen;/* The length of the defined prefix */
    Suff    	  	*suff;	/* Suffix on matching beastie */
    Src	    	  	*ret;	/* Return value */
    char    	  	*cp;

    t = targ->node;
    (void) Lst_Open (t->children);
    prefLen = strlen (targ->pref);

    while ((ln = Lst_Next (t->children)) != NILLNODE) {
	s = (GNode *)Lst_Datum (ln);

D 7
	cp = rindex (s->name, '/');
E 7
I 7
	cp = strrchr (s->name, '/');
E 7
	if (cp == (char *)NULL) {
	    cp = s->name;
	} else {
	    cp++;
	}
	if (strncmp (cp, targ->pref, prefLen) == 0) {
	    /*
	     * The node matches the prefix ok, see if it has a known
	     * suffix.
	     */
	    ln = Lst_Find (sufflist, (ClientData)&cp[prefLen],
			   SuffSuffHasNameP);
	    if (ln != NILLNODE) {
		/*
		 * It even has a known suffix, see if there's a transformation
		 * defined between the node's suffix and the target's suffix.
		 *
		 * XXX: Handle multi-stage transformations here, too.
		 */
		suff = (Suff *)Lst_Datum (ln);

		if (Lst_Member (suff->parents,
				(ClientData)targ->suff) != NILLNODE)
		{
		    /*
		     * Hot Damn! Create a new Src structure to describe
		     * this transformation (making sure to duplicate the
		     * source node's name so Suff_FindDeps can free it
		     * again (ick)), and return the new structure.
		     */
D 5
		    ret = (Src *)malloc (sizeof(Src));
E 5
I 5
D 14
		    ret = (Src *)emalloc (sizeof(Src));
E 14
I 14
		    ret = (Src *)emalloc (sizeof (Src));
E 14
E 5
D 3
		    ret->file = Str_New(s->name);
E 3
I 3
		    ret->file = strdup(s->name);
E 3
		    ret->pref = targ->pref;
		    ret->suff = suff;
I 14
		    suff->refCount++;
E 14
		    ret->parent = targ;
		    ret->node = s;
		    ret->children = 0;
		    targ->children += 1;
I 14
#ifdef DEBUG_SRC
		    ret->cp = Lst_Init(FALSE);
		    printf("3 add %x %x\n", targ, ret);
		    Lst_AtEnd(targ->cp, (ClientData) ret);
#endif
		    Lst_AtEnd(slst, (ClientData) ret);
E 14
		    if (DEBUG(SUFF)) {
			printf ("\tusing existing source %s\n", s->name);
		    }
		    return (ret);
		}
	    }
	}
    }
    Lst_Close (t->children);
    return ((Src *)NULL);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffExpandChildren --
 *	Expand the names of any children of a given node that contain
 *	variable invocations or file wildcards into actual targets.
 *
 * Results:
 *	=== 0 (continue)
 *
 * Side Effects:
 *	The expanded node is removed from the parent's list of children,
 *	and the parent's unmade counter is decremented, but other nodes
 * 	may be added.
 *
 *-----------------------------------------------------------------------
 */
static int
D 14
SuffExpandChildren(cgn, pgn)
    GNode   	*cgn;	    /* Child to examine */
    GNode   	*pgn;	    /* Parent node being processed */
E 14
I 14
SuffExpandChildren(cgnp, pgnp)
    ClientData  cgnp;	    /* Child to examine */
    ClientData  pgnp;	    /* Parent node being processed */
E 14
{
I 14
    GNode   	*cgn = (GNode *) cgnp;
    GNode   	*pgn = (GNode *) pgnp;
E 14
    GNode	*gn;	    /* New source 8) */
    LstNode   	prevLN;    /* Node after which new source should be put */
    LstNode	ln; 	    /* List element for old source */
    char	*cp;	    /* Expanded value */

    /*
     * New nodes effectively take the place of the child, so place them
     * after the child
     */
    prevLN = Lst_Member(pgn->children, (ClientData)cgn);
    
    /*
     * First do variable expansion -- this takes precedence over
     * wildcard expansion. If the result contains wildcards, they'll be gotten
     * to later since the resulting words are tacked on to the end of
     * the children list.
     */
D 7
    if (index(cgn->name, '$') != (char *)NULL) {
E 7
I 7
    if (strchr(cgn->name, '$') != (char *)NULL) {
E 7
	if (DEBUG(SUFF)) {
	    printf("Expanding \"%s\"...", cgn->name);
	}
D 7
	cp = Var_Subst(cgn->name, pgn, TRUE);
E 7
I 7
	cp = Var_Subst(NULL, cgn->name, pgn, TRUE);
E 7

	if (cp != (char *)NULL) {
	    Lst	    members = Lst_Init(FALSE);
	    
	    if (cgn->type & OP_ARCHV) {
		/*
		 * Node was an archive(member) target, so we want to call
		 * on the Arch module to find the nodes for us, expanding
		 * variables in the parent's context.
		 */
		char	*sacrifice = cp;

		(void)Arch_ParseArchive(&sacrifice, members, pgn);
	    } else {
		/*
		 * Break the result into a vector of strings whose nodes
		 * we can find, then add those nodes to the members list.
D 5
		 * Unfortunately, we can't use Str_BreakString b/c it
E 5
I 5
		 * Unfortunately, we can't use brk_string b/c it
E 5
		 * doesn't understand about variable specifications with
		 * spaces in them...
		 */
		char	    *start;
		char	    *initcp = cp;   /* For freeing... */

D 7
		for (start = cp; *start == ' ' || *start == '\t'; start++) {
		    ;
		}
E 7
I 7
		for (start = cp; *start == ' ' || *start == '\t'; start++) 
		    continue;
E 7
		for (cp = start; *cp != '\0'; cp++) {
		    if (*cp == ' ' || *cp == '\t') {
			/*
			 * White-space -- terminate element, find the node,
			 * add it, skip any further spaces.
			 */
			*cp++ = '\0';
			gn = Targ_FindNode(start, TARG_CREATE);
			(void)Lst_AtEnd(members, (ClientData)gn);
			while (*cp == ' ' || *cp == '\t') {
			    cp++;
			}
			/*
			 * Adjust cp for increment at start of loop, but
			 * set start to first non-space.
			 */
			start = cp--;
		    } else if (*cp == '$') {
			/*
			 * Start of a variable spec -- contact variable module
			 * to find the end so we can skip over it.
			 */
			char	*junk;
			int 	len;
			Boolean	doFree;

			junk = Var_Parse(cp, pgn, TRUE, &len, &doFree);
			if (junk != var_Error) {
			    cp += len - 1;
			}

			if (doFree) {
			    free(junk);
			}
		    } else if (*cp == '\\' && *cp != '\0') {
			/*
			 * Escaped something -- skip over it
			 */
			cp++;
		    }
		}

		if (cp != start) {
		    /*
		     * Stuff left over -- add it to the list too
		     */
		    gn = Targ_FindNode(start, TARG_CREATE);
		    (void)Lst_AtEnd(members, (ClientData)gn);
		}
		/*
		 * Point cp back at the beginning again so the variable value
		 * can be freed.
		 */
		cp = initcp;
	    }
	    /*
	     * Add all elements of the members list to the parent node.
	     */
	    while(!Lst_IsEmpty(members)) {
		gn = (GNode *)Lst_DeQueue(members);

		if (DEBUG(SUFF)) {
		    printf("%s...", gn->name);
		}
		if (Lst_Member(pgn->children, (ClientData)gn) == NILLNODE) {
		    (void)Lst_Append(pgn->children, prevLN, (ClientData)gn);
		    prevLN = Lst_Succ(prevLN);
		    (void)Lst_AtEnd(gn->parents, (ClientData)pgn);
		    pgn->unmade++;
		}
	    }
	    Lst_Destroy(members, NOFREE);
	    /*
	     * Free the result
	     */
	    free((char *)cp);
	}
	/*
	 * Now the source is expanded, remove it from the list of children to
	 * keep it from being processed.
	 */
	ln = Lst_Member(pgn->children, (ClientData)cgn);
	pgn->unmade--;
	Lst_Remove(pgn->children, ln);
	if (DEBUG(SUFF)) {
	    printf("\n");
	}
    } else if (Dir_HasWildcards(cgn->name)) {
	Lst 	exp;	    /* List of expansions */
	Lst 	path;	    /* Search path along which to expand */

	/*
	 * Find a path along which to expand the word.
	 *
	 * If the word has a known suffix, use that path.
	 * If it has no known suffix and we're allowed to use the null
	 *   suffix, use its path.
	 * Else use the default system search path.
	 */
	cp = cgn->name + strlen(cgn->name);
	ln = Lst_Find(sufflist, (ClientData)cp, SuffSuffIsSuffixP);

	if (DEBUG(SUFF)) {
	    printf("Wildcard expanding \"%s\"...", cgn->name);
	}
	
	if (ln != NILLNODE) {
	    Suff    *s = (Suff *)Lst_Datum(ln);

	    if (DEBUG(SUFF)) {
		printf("suffix is \"%s\"...", s->name);
	    }
	    path = s->searchPath;
D 4
	} else if ((suffNull != (Suff *)NULL) && !amMake) {
	    if (DEBUG(SUFF)) {
		printf("using .NULL(%s)...", suffNull->name);
	    }
	    path = suffNull->searchPath;
E 4
	} else {
	    /*
	     * Use default search path
	     */
	    path = dirSearchPath;
	}

	/*
	 * Expand the word along the chosen path
	 */
	exp = Lst_Init(FALSE);
	Dir_Expand(cgn->name, path, exp);

	while (!Lst_IsEmpty(exp)) {
	    /*
	     * Fetch next expansion off the list and find its GNode
	     */
	    cp = (char *)Lst_DeQueue(exp);

	    if (DEBUG(SUFF)) {
		printf("%s...", cp);
	    }
	    gn = Targ_FindNode(cp, TARG_CREATE);

	    /*
	     * If gn isn't already a child of the parent, make it so and
	     * up the parent's count of unmade children.
	     */
	    if (Lst_Member(pgn->children, (ClientData)gn) == NILLNODE) {
		(void)Lst_Append(pgn->children, prevLN, (ClientData)gn);
		prevLN = Lst_Succ(prevLN);
		(void)Lst_AtEnd(gn->parents, (ClientData)pgn);
		pgn->unmade++;
	    }
	}

	/*
	 * Nuke what's left of the list
	 */
	Lst_Destroy(exp, NOFREE);
    
	/*
	 * Now the source is expanded, remove it from the list of children to
	 * keep it from being processed.
	 */
	ln = Lst_Member(pgn->children, (ClientData)cgn);
	pgn->unmade--;
	Lst_Remove(pgn->children, ln);
	if (DEBUG(SUFF)) {
	    printf("\n");
	}
    }

    return(0);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffApplyTransform --
 *	Apply a transformation rule, given the source and target nodes
 *	and suffixes.
 *
 * Results:
 *	TRUE if successful, FALSE if not.
 *
 * Side Effects:
 *	The source and target are linked and the commands from the
 *	transformation are added to the target node's commands list.
 *	All attributes but OP_DEPMASK and OP_TRANSFORM are applied
 *	to the target. The target also inherits all the sources for
 *	the transformation rule.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
SuffApplyTransform(tGn, sGn, t, s)
    GNode   	*tGn;	    /* Target node */
    GNode   	*sGn;	    /* Source node */
    Suff    	*t; 	    /* Target suffix */
    Suff    	*s; 	    /* Source suffix */
{
    LstNode 	ln; 	    /* General node */
    char    	*tname;	    /* Name of transformation rule */
    GNode   	*gn;	    /* Node for same */

    if (Lst_Member(tGn->children, (ClientData)sGn) == NILLNODE) {
	/*
	 * Not already linked, so form the proper links between the
	 * target and source.
	 */
	(void)Lst_AtEnd(tGn->children, (ClientData)sGn);
	(void)Lst_AtEnd(sGn->parents, (ClientData)tGn);
	tGn->unmade += 1;
    }

    if ((sGn->type & OP_OPMASK) == OP_DOUBLEDEP) {
	/*
	 * When a :: node is used as the implied source of a node, we have
	 * to link all its cohorts in as sources as well. Only the initial
	 * sGn gets the target in its iParents list, however, as that
	 * will be sufficient to get the .IMPSRC variable set for tGn
	 */
	for (ln=Lst_First(sGn->cohorts); ln != NILLNODE; ln=Lst_Succ(ln)) {
	    gn = (GNode *)Lst_Datum(ln);

	    if (Lst_Member(tGn->children, (ClientData)gn) == NILLNODE) {
		/*
		 * Not already linked, so form the proper links between the
		 * target and source.
		 */
		(void)Lst_AtEnd(tGn->children, (ClientData)gn);
		(void)Lst_AtEnd(gn->parents, (ClientData)tGn);
		tGn->unmade += 1;
	    }
	}
    }
    /*
     * Locate the transformation rule itself
     */
D 5
    tname = Str_Concat(s->name, t->name, 0);
E 5
I 5
    tname = str_concat(s->name, t->name, 0);
E 5
    ln = Lst_Find(transforms, (ClientData)tname, SuffGNHasNameP);
    free(tname);

    if (ln == NILLNODE) {
	/*
	 * Not really such a transformation rule (can happen when we're
	 * called to link an OP_MEMBER and OP_ARCHV node), so return
	 * FALSE.
	 */
	return(FALSE);
    }

    gn = (GNode *)Lst_Datum(ln);
    
    if (DEBUG(SUFF)) {
	printf("\tapplying %s -> %s to \"%s\"\n", s->name, t->name, tGn->name);
    }

    /*
     * Record last child for expansion purposes
     */
    ln = Lst_Last(tGn->children);
    
    /*
     * Pass the buck to Make_HandleUse to apply the rule
     */
    (void)Make_HandleUse(gn, tGn);

    /*
     * Deal with wildcards and variables in any acquired sources
     */
    ln = Lst_Succ(ln);
    if (ln != NILLNODE) {
	Lst_ForEachFrom(tGn->children, ln,
			SuffExpandChildren, (ClientData)tGn);
    }

    /*
     * Keep track of another parent to which this beast is transformed so
     * the .IMPSRC variable can be set correctly for the parent.
     */
    (void)Lst_AtEnd(sGn->iParents, (ClientData)tGn);

    return(TRUE);
}

D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffFindArchiveDeps --
 *	Locate dependencies for an OP_ARCHV node.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Same as Suff_FindDeps
 *
 *-----------------------------------------------------------------------
 */
static void
D 14
SuffFindArchiveDeps(gn)
E 14
I 14
SuffFindArchiveDeps(gn, slst)
E 14
    GNode   	*gn;	    /* Node for which to locate dependencies */
I 14
    Lst		slst;
E 14
{
    char    	*eoarch;    /* End of archive portion */
    char    	*eoname;    /* End of member portion */
    GNode   	*mem;	    /* Node for member */
    static char	*copy[] = { /* Variables to be copied from the member node */
	TARGET,	    	    /* Must be first */
	PREFIX,	    	    /* Must be second */
    };
D 14
    char  	*vals[sizeof(copy)/sizeof(copy[0])];
E 14
    int	    	i;  	    /* Index into copy and vals */
D 7
    char    	*cp;	    /* Suffix for member */
E 7
    Suff    	*ms;	    /* Suffix descriptor for member */
    char    	*name;	    /* Start of member's name */
    
    /*
     * The node is an archive(member) pair. so we must find a
     * suffix for both of them.
     */
D 7
    eoarch = index (gn->name, '(');
    eoname = index (eoarch, ')');
E 7
I 7
    eoarch = strchr (gn->name, '(');
    eoname = strchr (eoarch, ')');
E 7

    *eoname = '\0';	  /* Nuke parentheses during suffix search */
    *eoarch = '\0';	  /* So a suffix can be found */

    name = eoarch + 1;
    
    /*
     * To simplify things, call Suff_FindDeps recursively on the member now,
     * so we can simply compare the member's .PREFIX and .TARGET variables
     * to locate its suffix. This allows us to figure out the suffix to
     * use for the archive without having to do a quadratic search over the
     * suffix list, backtracking for each one...
     */
    mem = Targ_FindNode(name, TARG_CREATE);
D 14
    Suff_FindDeps(mem);
E 14
I 14
    SuffFindDeps(mem, slst);
E 14

    /*
     * Create the link between the two nodes right off
     */
    if (Lst_Member(gn->children, (ClientData)mem) == NILLNODE) {
	(void)Lst_AtEnd(gn->children, (ClientData)mem);
	(void)Lst_AtEnd(mem->parents, (ClientData)gn);
	gn->unmade += 1;
    }
    
    /*
     * Copy in the variables from the member node to this one.
     */
    for (i = (sizeof(copy)/sizeof(copy[0]))-1; i >= 0; i--) {
D 14
	vals[i] = Var_Value(copy[i], mem);
	Var_Set(copy[i], vals[i], gn);
E 14
I 14
	char *p1;
	Var_Set(copy[i], Var_Value(copy[i], mem, &p1), gn);
	if (p1)
	    free(p1);

E 14
    }

    ms = mem->suffix;
    if (ms == NULL) {
	/*
	 * Didn't know what it was -- use .NULL suffix if not in make mode
	 */
	if (DEBUG(SUFF)) {
	    printf("using null suffix\n");
	}
	ms = suffNull;
    }


    /*
     * Set the other two local variables required for this target.
     */
    Var_Set (MEMBER, name, gn);
    Var_Set (ARCHIVE, gn->name, gn);

    if (ms != NULL) {
	/*
	 * Member has a known suffix, so look for a transformation rule from
	 * it to a possible suffix of the archive. Rather than searching
	 * through the entire list, we just look at suffixes to which the
	 * member's suffix may be transformed...
	 */
	LstNode	    ln;

	/*
	 * Use first matching suffix...
	 */
	ln = Lst_Find(ms->parents, eoarch, SuffSuffIsSuffixP);

	if (ln != NILLNODE) {
	    /*
	     * Got one -- apply it
	     */
	    if (!SuffApplyTransform(gn, mem, (Suff *)Lst_Datum(ln), ms) &&
		DEBUG(SUFF))
	    {
		printf("\tNo transformation from %s -> %s\n",
		       ms->name, ((Suff *)Lst_Datum(ln))->name);
	    }
	}
    }

    /*
     * Replace the opening and closing parens now we've no need of the separate
     * pieces.
     */
    *eoarch = '('; *eoname = ')';

    /*
     * Pretend gn appeared to the left of a dependency operator so
     * the user needn't provide a transformation from the member to the
     * archive.
     */
    if (OP_NOP(gn->type)) {
	gn->type |= OP_DEPENDS;
    }

    /*
     * Flag the member as such so we remember to look in the archive for
     * its modification time.
     */
    mem->type |= OP_MEMBER;
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * SuffFindNormalDeps --
 *	Locate implicit dependencies for regular targets.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Same as Suff_FindDeps...
 *
 *-----------------------------------------------------------------------
 */
static void
D 14
SuffFindNormalDeps(gn)
E 14
I 14
SuffFindNormalDeps(gn, slst)
E 14
    GNode   	*gn;	    /* Node for which to find sources */
I 14
    Lst		slst;
E 14
{
    char    	*eoname;    /* End of name */
    char    	*sopref;    /* Start of prefix */
D 7
    Suff    	*s; 	    /* Current suffix */
E 7
    LstNode 	ln; 	    /* Next suffix node to check */
    Lst	    	srcs;	    /* List of sources at which to look */
    Lst	    	targs;	    /* List of targets to which things can be
			     * transformed. They all have the same file,
			     * but different suff and pref fields */
    Src	    	*bottom;    /* Start of found transformation path */
    Src 	*src;	    /* General Src pointer */
    char    	*pref;	    /* Prefix to use */
    Src	    	*targ;	    /* General Src target pointer */


    eoname = gn->name + strlen(gn->name);

D 4
    /*
     * Figure the start of the prefix: if not in System V or Make mode,
     * we remove any leading components from the target's name so we can
     * better search for the source.
     *
     * XXX: Use leading components in search if not found elsewhere?
     */
    if (!sysVmake && !amMake) {
	char	*cp = rindex(gn->name, '/');

	if (cp != NULL) {
	    sopref = cp + 1;
	} else {
	    sopref = gn->name;
	}
    } else {
	sopref = gn->name;
    }
E 4
I 4
    sopref = gn->name;
E 4
    
    /*
     * Begin at the beginning...
     */
    ln = Lst_First(sufflist);
    srcs = Lst_Init(FALSE);
    targs = Lst_Init(FALSE);

    /*
     * We're caught in a catch-22 here. On the one hand, we want to use any
     * transformation implied by the target's sources, but we can't examine
     * the sources until we've expanded any variables/wildcards they may hold,
     * and we can't do that until we've set up the target's local variables
     * and we can't do that until we know what the proper suffix for the
     * target is (in case there are two suffixes one of which is a suffix of
     * the other) and we can't know that until we've found its implied
     * source, which we may not want to use if there's an existing source
     * that implies a different transformation.
     *
     * In an attempt to get around this, which may not work all the time,
     * but should work most of the time, we look for implied sources first,
     * checking transformations to all possible suffixes of the target,
     * use what we find to set the target's local variables, expand the
     * children, then look for any overriding transformations they imply.
     * Should we find one, we discard the one we found before.
     */
    while(ln != NILLNODE) {
	/*
	 * Look for next possible suffix...
	 */
	ln = Lst_FindFrom(sufflist, ln, eoname, SuffSuffIsSuffixP);

	if (ln != NILLNODE) {
	    int	    prefLen;	    /* Length of the prefix */
	    Src	    *targ;
	    
	    /*
	     * Allocate a Src structure to which things can be transformed
	     */
D 5
	    targ = (Src *)malloc(sizeof(Src));
E 5
I 5
D 14
	    targ = (Src *)emalloc(sizeof(Src));
E 14
I 14
	    targ = (Src *)emalloc(sizeof (Src));
E 14
E 5
D 3
	    targ->file = Str_New(gn->name);
E 3
I 3
	    targ->file = strdup(gn->name);
E 3
	    targ->suff = (Suff *)Lst_Datum(ln);
I 14
	    targ->suff->refCount++;
E 14
	    targ->node = gn;
	    targ->parent = (Src *)NULL;
I 11
	    targ->children = 0;
I 14
#ifdef DEBUG_SRC
	    targ->cp = Lst_Init(FALSE);
#endif
E 14
E 11
	    
	    /*
	     * Allocate room for the prefix, whose end is found by subtracting
	     * the length of the suffix from the end of the name.
	     */
	    prefLen = (eoname - targ->suff->nameLen) - sopref;
D 5
	    targ->pref = malloc(prefLen + 1);
E 5
I 5
	    targ->pref = emalloc(prefLen + 1);
E 5
D 7
	    bcopy(sopref, targ->pref, prefLen);
E 7
I 7
	    memcpy(targ->pref, sopref, prefLen);
E 7
	    targ->pref[prefLen] = '\0';

	    /*
	     * Add nodes from which the target can be made
	     */
	    SuffAddLevel(srcs, targ);

	    /*
	     * Record the target so we can nuke it
	     */
	    (void)Lst_AtEnd(targs, (ClientData)targ);

	    /*
	     * Search from this suffix's successor...
	     */
	    ln = Lst_Succ(ln);
	}
    }

    /*
     * Handle target of unknown suffix...
     */
    if (Lst_IsEmpty(targs) && suffNull != NULL) {
	if (DEBUG(SUFF)) {
D 14
	    printf("\tNo known suffix on %s. Using .NULL suffix\n", gn->name);
E 14
I 14
	    printf("\tNo known suffix on %s. Using .NULL suffix: ", gn->name);
E 14
	}
	
D 5
	targ = (Src *)malloc(sizeof(Src));
E 5
I 5
D 14
	targ = (Src *)emalloc(sizeof(Src));
E 14
I 14
	targ = (Src *)emalloc(sizeof (Src));
E 14
E 5
D 3
	targ->file = Str_New(gn->name);
E 3
I 3
	targ->file = strdup(gn->name);
E 3
	targ->suff = suffNull;
I 14
	targ->suff->refCount++;
E 14
	targ->node = gn;
	targ->parent = (Src *)NULL;
I 11
	targ->children = 0;
E 11
D 3
	targ->pref = Str_New(sopref);
E 3
I 3
	targ->pref = strdup(sopref);
I 14
#ifdef DEBUG_SRC
	targ->cp = Lst_Init(FALSE);
#endif
E 14
E 3

D 14
	SuffAddLevel(srcs, targ);
E 14
I 14
	/*
	 * Only use the default suffix rules if we don't have commands
	 * or dependencies defined for this gnode
	 */
	if (Lst_IsEmpty(gn->commands) && Lst_IsEmpty(gn->children))
	    SuffAddLevel(srcs, targ);
	else {
	    if (DEBUG(SUFF)) 
		printf("not ");
	}

	if (DEBUG(SUFF)) 
	    printf("adding suffix rules\n");

E 14
	(void)Lst_AtEnd(targs, (ClientData)targ);
    }
    
    /*
     * Using the list of possible sources built up from the target suffix(es),
     * try and find an existing file/target that matches.
     */
D 14
    bottom = SuffFindThem(srcs);
E 14
I 14
    bottom = SuffFindThem(srcs, slst);
E 14

    if (bottom == (Src *)NULL) {
	/*
	 * No known transformations -- use the first suffix found for setting
	 * the local variables.
	 */
	if (!Lst_IsEmpty(targs)) {
	    targ = (Src *)Lst_Datum(Lst_First(targs));
	} else {
	    targ = (Src *)NULL;
	}
    } else {
	/*
	 * Work up the transformation path to find the suffix of the
	 * target to which the transformation was made.
	 */
D 7
	for (targ = bottom; targ->parent != NULL; targ = targ->parent) {
	    ;
	}
E 7
I 7
	for (targ = bottom; targ->parent != NULL; targ = targ->parent)
	    continue;
E 7
    }

    /*
     * The .TARGET variable we always set to be the name at this point,
     * since it's only set to the path if the thing is only a source and
     * if it's only a source, it doesn't matter what we put here as far
     * as expanding sources is concerned, since it has none...
     */
    Var_Set(TARGET, gn->name, gn);

    pref = (targ != NULL) ? targ->pref : gn->name;
    Var_Set(PREFIX, pref, gn);

    /*
     * Now we've got the important local variables set, expand any sources
     * that still contain variables or wildcards in their names.
     */
    Lst_ForEach(gn->children, SuffExpandChildren, (ClientData)gn);
    
    if (targ == NULL) {
	if (DEBUG(SUFF)) {
	    printf("\tNo valid suffix on %s\n", gn->name);
	}

sfnd_abort:
	/*
	 * Deal with finding the thing on the default search path if the
	 * node is only a source (not on the lhs of a dependency operator
	 * or [XXX] it has neither children or commands).
	 */
	if (OP_NOP(gn->type) ||
	    (Lst_IsEmpty(gn->children) && Lst_IsEmpty(gn->commands)))
	{
	    gn->path = Dir_FindFile(gn->name,
				    (targ == NULL ? dirSearchPath :
				     targ->suff->searchPath));
	    if (gn->path != NULL) {
		Var_Set(TARGET, gn->path, gn);

		if (targ != NULL) {
		    /*
		     * Suffix known for the thing -- trim the suffix off
		     * the path to form the proper .PREFIX variable.
		     */
		    int		len = strlen(gn->path);
		    char	savec;

I 14
		    if (gn->suffix)
			gn->suffix->refCount--;
E 14
		    gn->suffix = targ->suff;
I 14
		    gn->suffix->refCount++;
E 14

		    savec = gn->path[len-targ->suff->nameLen];
		    gn->path[len-targ->suff->nameLen] = '\0';

		    Var_Set(PREFIX, gn->path, gn);

		    gn->path[len-targ->suff->nameLen] = savec;
		} else {
		    /*
		     * The .PREFIX gets the full path if the target has
		     * no known suffix.
		     */
I 14
		    if (gn->suffix)
			gn->suffix->refCount--;
E 14
		    gn->suffix = NULL;

		    Var_Set(PREFIX, gn->path, gn);
		}
	    }
	} else {
	    /*
	     * Not appropriate to search for the thing -- set the
	     * path to be the name so Dir_MTime won't go grovelling for
	     * it.
	     */
I 14
	    if (gn->suffix)
		gn->suffix->refCount--;
E 14
	    gn->suffix = (targ == NULL) ? NULL : targ->suff;
D 14
	    gn->path = gn->name;
E 14
I 14
	    if (gn->suffix)
		gn->suffix->refCount++;
	    if (gn->path != NULL)
		free(gn->path);
	    gn->path = strdup(gn->name);
E 14
	}
	
	goto sfnd_return;
    }

    /*
     * If the suffix indicates that the target is a library, mark that in
     * the node's type field.
     */
    if (targ->suff->flags & SUFF_LIBRARY) {
	gn->type |= OP_LIB;
    }

    /*
     * Check for overriding transformation rule implied by sources
     */
    if (!Lst_IsEmpty(gn->children)) {
D 14
	src = SuffFindCmds(targ);
E 14
I 14
	src = SuffFindCmds(targ, slst);
E 14

	if (src != (Src *)NULL) {
	    /*
	     * Free up all the Src structures in the transformation path
	     * up to, but not including, the parent node.
	     */
	    while (bottom && bottom->parent != NULL) {
D 14
		Src *p = bottom->parent;

		SuffFreeSrc(bottom);
		bottom = p;
E 14
I 14
		if (Lst_Member(slst, (ClientData) bottom) == NILLNODE) {
		    Lst_AtEnd(slst, (ClientData) bottom);
		}
		bottom = bottom->parent;
E 14
	    }
	    bottom = src;
	}
    }

    if (bottom == NULL) {
	/*
	 * No idea from where it can come -- return now.
	 */
	goto sfnd_abort;
    }

    /*
     * We now have a list of Src structures headed by 'bottom' and linked via
     * their 'parent' pointers. What we do next is create links between
     * source and target nodes (which may or may not have been created)
     * and set the necessary local variables in each target. The
     * commands for each target are set from the commands of the
     * transformation rule used to get from the src suffix to the targ
     * suffix. Note that this causes the commands list of the original
     * node, gn, to be replaced by the commands of the final
     * transformation rule. Also, the unmade field of gn is incremented.
     * Etc. 
     */
    if (bottom->node == NILGNODE) {
	bottom->node = Targ_FindNode(bottom->file, TARG_CREATE);
    }
    
    for (src = bottom; src->parent != (Src *)NULL; src = src->parent) {
	targ = src->parent;

I 14
	if (src->node->suffix)
	    src->node->suffix->refCount--;
E 14
	src->node->suffix = src->suff;
I 14
	src->node->suffix->refCount++;
E 14

	if (targ->node == NILGNODE) {
	    targ->node = Targ_FindNode(targ->file, TARG_CREATE);
	}

	SuffApplyTransform(targ->node, src->node,
			   targ->suff, src->suff);

	if (targ->node != gn) {
	    /*
	     * Finish off the dependency-search process for any nodes
	     * between bottom and gn (no point in questing around the
	     * filesystem for their implicit source when it's already
	     * known). Note that the node can't have any sources that
	     * need expanding, since SuffFindThem will stop on an existing
	     * node, so all we need to do is set the standard and System V
	     * variables.
	     */
	    targ->node->type |= OP_DEPS_FOUND;

	    Var_Set(PREFIX, targ->pref, targ->node);
	
	    Var_Set(TARGET, targ->node->name, targ->node);
	}
    }

I 14
    if (gn->suffix)
	gn->suffix->refCount--;
E 14
    gn->suffix = src->suff;
I 14
    gn->suffix->refCount++;
E 14

    /*
     * So Dir_MTime doesn't go questing for it...
     */
D 14
    gn->path = gn->name;
E 14
I 14
    if (gn->path)
	free(gn->path);
    gn->path = strdup(gn->name);
E 14

    /*
     * Nuke the transformation path and the Src structures left over in the
     * two lists.
     */
D 14
    SuffFreeSrc(bottom);

E 14
sfnd_return:
D 14
    Lst_Destroy(srcs, SuffFreeSrc);
    Lst_Destroy(targs, SuffFreeSrc);
E 14
I 14
    if (bottom)
	if (Lst_Member(slst, (ClientData) bottom) == NILLNODE)
	    Lst_AtEnd(slst, (ClientData) bottom);
E 14

I 14
    while (SuffRemoveSrc(srcs) || SuffRemoveSrc(targs))
	continue;

    Lst_Concat(slst, srcs, LST_CONCLINK);
    Lst_Concat(slst, targs, LST_CONCLINK);
E 14
}
	
    
D 14

D 3

E 3
I 3

E 14
E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_FindDeps  --
 *	Find implicit sources for the target described by the graph node
 *	gn
 *
 * Results:
 *	Nothing.
 *
 * Side Effects:
 *	Nodes are added to the graph below the passed-in node. The nodes
 *	are marked to have their IMPSRC variable filled in. The
 *	PREFIX variable is set for the given node and all its
 *	implied children.
 *
 * Notes:
 *	The path found by this target is the shortest path in the
 *	transformation graph, which may pass through non-existent targets,
 *	to an existing target. The search continues on all paths from the
 *	root suffix until a file is found. I.e. if there's a path
 *	.o -> .c -> .l -> .l,v from the root and the .l,v file exists but
 *	the .c and .l files don't, the search will branch out in
 *	all directions from .o and again from all the nodes on the
 *	next level until the .l,v node is encountered.
 *
 *-----------------------------------------------------------------------
 */
I 14

E 14
void
D 14
Suff_FindDeps (gn)
E 14
I 14
Suff_FindDeps(gn)
    GNode *gn;
{
   
    SuffFindDeps(gn, srclist);
    while (SuffRemoveSrc(srclist))
	continue;
}


static void
SuffFindDeps (gn, slst)
E 14
    GNode         *gn;	      	/* node we're dealing with */
I 14
    Lst		  slst;
E 14
{
    if (gn->type & OP_DEPS_FOUND) {
	/*
	 * If dependencies already found, no need to do it again...
	 */
	return;
    } else {
	gn->type |= OP_DEPS_FOUND;
    }
    
    if (DEBUG(SUFF)) {
D 14
	printf ("Suff_FindDeps (%s)\n", gn->name);
E 14
I 14
	printf ("SuffFindDeps (%s)\n", gn->name);
E 14
    }
    
    if (gn->type & OP_ARCHV) {
D 14
	SuffFindArchiveDeps(gn);
E 14
I 14
	SuffFindArchiveDeps(gn, slst);
E 14
    } else if (gn->type & OP_LIB) {
	/*
	 * If the node is a library, it is the arch module's job to find it
	 * and set the TARGET variable accordingly. We merely provide the
	 * search path, assuming all libraries end in ".a" (if the suffix
	 * hasn't been defined, there's nothing we can do for it, so we just
	 * set the TARGET variable to the node's name in order to give it a
	 * value).
	 */
	LstNode	ln;
	Suff	*s;
	
	ln = Lst_Find (sufflist, (ClientData)LIBSUFF, SuffSuffHasNameP);
I 14
	if (gn->suffix)
	    gn->suffix->refCount--;
E 14
	if (ln != NILLNODE) {
	    gn->suffix = s = (Suff *) Lst_Datum (ln);
I 14
	    gn->suffix->refCount++;
E 14
	    Arch_FindLib (gn, s->searchPath);
	} else {
	    gn->suffix = NULL;
	    Var_Set (TARGET, gn->name, gn);
	}
	/*
	 * Because a library (-lfoo) target doesn't follow the standard
	 * filesystem conventions, we don't set the regular variables for
	 * the thing. .PREFIX is simply made empty...
	 */
	Var_Set(PREFIX, "", gn);
    } else {
D 14
	SuffFindNormalDeps(gn);
E 14
I 14
	SuffFindNormalDeps(gn, slst);
E 14
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_SetNull --
 *	Define which suffix is the null suffix.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	'suffNull' is altered.
 *
 * Notes:
 *	Need to handle the changing of the null suffix gracefully so the
 *	old transformation rules don't just go away.
 *
 *-----------------------------------------------------------------------
 */
void
Suff_SetNull(name)
    char    *name;	    /* Name of null suffix */
{
    Suff    *s;
    LstNode ln;

    ln = Lst_Find(sufflist, (ClientData)name, SuffSuffHasNameP);
    if (ln != NILLNODE) {
	s = (Suff *)Lst_Datum(ln);
	if (suffNull != (Suff *)NULL) {
	    suffNull->flags &= ~SUFF_NULL;
	}
	s->flags |= SUFF_NULL;
	/*
	 * XXX: Here's where the transformation mangling would take place
	 */
	suffNull = s;
    } else {
	Parse_Error (PARSE_WARNING, "Desired null suffix %s not defined.",
		     name);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Suff_Init --
 *	Initialize suffixes module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Many
 *-----------------------------------------------------------------------
 */
void
Suff_Init ()
{
    sufflist = Lst_Init (FALSE);
I 14
    suffClean = Lst_Init(FALSE);
    srclist = Lst_Init (FALSE);
E 14
    transforms = Lst_Init (FALSE);

    sNum = 0;
    /*
     * Create null suffix for single-suffix rules (POSIX). The thing doesn't
     * actually go on the suffix list or everyone will think that's its
     * suffix.
     */
D 5
    emptySuff = suffNull = (Suff *) malloc (sizeof (Suff));
E 5
I 5
    emptySuff = suffNull = (Suff *) emalloc (sizeof (Suff));
E 5

D 3
    suffNull->name =   	    Str_New ("");
E 3
I 3
    suffNull->name =   	    strdup ("");
E 3
    suffNull->nameLen =     0;
    suffNull->searchPath =  Lst_Init (FALSE);
I 10
    Dir_Concat(suffNull->searchPath, dirSearchPath);
E 10
    suffNull->children =    Lst_Init (FALSE);
    suffNull->parents =	    Lst_Init (FALSE);
I 14
    suffNull->ref =	    Lst_Init (FALSE);
E 14
    suffNull->sNum =   	    sNum++;
    suffNull->flags =  	    SUFF_NULL;
I 14
    suffNull->refCount =    1;
E 14

}
I 12


/*-
D 14
 *-----------------------------------------------------------------------
 * SuffCopy  --
 *	Create a copy of the source suffix.
 *	Currently does not copy children or parents
E 14
I 14
 *----------------------------------------------------------------------
 * Suff_End --
 *	Cleanup the this module
E 14
 *
 * Results:
D 14
 *	a new suffix is returned
E 14
I 14
 *	None
E 14
 *
 * Side Effects:
D 14
 *	none
 *-----------------------------------------------------------------------
E 14
I 14
 *	The memory is free'd.
 *----------------------------------------------------------------------
E 14
 */
D 14
static Suff *
SuffCopy(s)
    Suff *s;
E 14
I 14

void
Suff_End()
E 14
{
D 14
    Suff *n = (Suff *) emalloc (sizeof (Suff));
    n->name =       strdup (s->name);
    n->nameLen =    s->nameLen;
    n->searchPath = Lst_Init (FALSE);
    Dir_Concat(suffNull->searchPath, s->searchPath);
    n->children =   Lst_Init (FALSE);
    n->parents =    Lst_Init (FALSE);
    n->sNum =       s->sNum;   
    n->flags = 	    s->flags;
    return n;
E 14
I 14
    Lst_Destroy(sufflist, SuffFree);
    Lst_Destroy(suffClean, SuffFree);
    if (suffNull)
	SuffFree(suffNull);
    Lst_Destroy(srclist, NOFREE);
    Lst_Destroy(transforms, NOFREE);
E 14
}

E 12

/********************* DEBUGGING FUNCTIONS **********************/

D 14
static int SuffPrintName(s) Suff *s; {printf ("%s ", s->name); return (0);}
E 14
I 14
static int SuffPrintName(s, dummy)
    ClientData s;
    ClientData dummy;
{
    printf ("%s ", ((Suff *) s)->name);
    return (dummy ? 0 : 0);
}
E 14

static int
D 14
SuffPrintSuff (s)
    Suff    *s;
E 14
I 14
SuffPrintSuff (sp, dummy)
    ClientData sp;
    ClientData dummy;
E 14
{
I 14
    Suff    *s = (Suff *) sp;
E 14
    int	    flags;
    int	    flag;

D 14
    printf ("# `%s'", s->name);
E 14
I 14
    printf ("# `%s' [%d] ", s->name, s->refCount);
E 14
    
    flags = s->flags;
    if (flags) {
	fputs (" (", stdout);
	while (flags) {
	    flag = 1 << (ffs(flags) - 1);
	    flags &= ~flag;
	    switch (flag) {
		case SUFF_NULL:
		    printf ("NULL");
		    break;
		case SUFF_INCLUDE:
		    printf ("INCLUDE");
		    break;
		case SUFF_LIBRARY:
		    printf ("LIBRARY");
		    break;
	    }
D 7
	    putc(flags ? '|' : ')', stdout);
E 7
I 7
	    fputc(flags ? '|' : ')', stdout);
E 7
	}
    }
D 7
    putc ('\n', stdout);
E 7
I 7
    fputc ('\n', stdout);
E 7
    printf ("#\tTo: ");
    Lst_ForEach (s->parents, SuffPrintName, (ClientData)0);
D 7
    putc ('\n', stdout);
E 7
I 7
    fputc ('\n', stdout);
E 7
    printf ("#\tFrom: ");
    Lst_ForEach (s->children, SuffPrintName, (ClientData)0);
D 7
    putc ('\n', stdout);
E 7
I 7
    fputc ('\n', stdout);
E 7
    printf ("#\tSearch Path: ");
    Dir_PrintPath (s->searchPath);
D 7
    putc ('\n', stdout);
E 7
I 7
    fputc ('\n', stdout);
E 7
D 14
    return (0);
E 14
I 14
    return (dummy ? 0 : 0);
E 14
}

static int
D 14
SuffPrintTrans (t)
    GNode   *t;
E 14
I 14
SuffPrintTrans (tp, dummy)
    ClientData tp;
    ClientData dummy;
E 14
{
D 14
    extern int Targ_PrintCmd();
E 14
I 14
    GNode   *t = (GNode *) tp;
E 14

    printf ("%-16s: ", t->name);
    Targ_PrintType (t->type);
D 7
    putc ('\n', stdout);
E 7
I 7
    fputc ('\n', stdout);
E 7
    Lst_ForEach (t->commands, Targ_PrintCmd, (ClientData)0);
D 7
    putc ('\n', stdout);
E 7
I 7
    fputc ('\n', stdout);
E 7
D 14
    return(0);
E 14
I 14
    return(dummy ? 0 : 0);
E 14
}

I 7
void
E 7
Suff_PrintAll()
{
    printf ("#*** Suffixes:\n");
    Lst_ForEach (sufflist, SuffPrintSuff, (ClientData)0);

    printf ("#*** Transformations:\n");
    Lst_ForEach (transforms, SuffPrintTrans, (ClientData)0);
}
D 7

E 7
E 1
