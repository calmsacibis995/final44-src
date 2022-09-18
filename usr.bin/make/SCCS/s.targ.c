h36433
s 00097/00025/00534
d D 8.3 95/04/28 17:08:30 christos 13 12
c Updated to the latest version from the NetBSD source
e
s 00001/00001/00558
d D 8.2 94/03/19 15:57:53 christos 12 11
c fix indentation
e
s 00002/00002/00557
d D 8.1 93/06/06 15:17:32 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00004/00551
d D 5.10 93/05/24 14:46:03 bostic 10 9
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00001/00554
d D 5.9 91/03/01 15:07:27 bostic 9 8
c ANSI
e
s 00001/00001/00554
d D 5.8 90/12/28 18:07:04 bostic 8 7
c replace hash.c; speedup/cleanup from Chris Torek
e
s 00001/00011/00554
d D 5.7 90/06/01 17:10:01 bostic 7 6
c new copyright notice
e
s 00001/00001/00564
d D 5.6 90/03/19 16:24:13 bostic 6 5
c rename DONTCARE as OPTIONAL
e
s 00001/00001/00564
d D 5.5 90/03/19 09:58:03 bostic 5 4
c replace malloc with emalloc
e
s 00000/00004/00565
d D 5.4 90/03/12 10:42:46 bostic 4 3
c remove rmt.c module, most of remote support, including .EXPORT,
c .EXPORTSAME, .NOEXPORT, -X and -x
e
s 00010/00010/00559
d D 5.3 90/03/12 09:00:04 bostic 3 2
c Str_New -> strdup
e
s 00026/00015/00543
d D 5.2 90/03/11 15:39:38 bostic 2 1
c add Berkeley specific copyright notice
e
s 00558/00000/00000
d D 5.1 90/03/11 15:27:54 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
D 11
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 11
I 11
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/*-
 * targ.c --
 *	Functions for maintaining the Lst allTargets. Target nodes are
 * kept in two structures: a Lst, maintained by the list library, and a
 * hash table, maintained by the hash library.
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
 *	Targ_Init 	    	Initialization procedure.
 *
I 13
 *	Targ_End 	    	Cleanup the module
 *
E 13
 *	Targ_NewGN	    	Create a new GNode for the passed target
 *	    	  	    	(string). The node is *not* placed in the
 *	    	  	    	hash table, though all its fields are
 *	    	  	    	initialized.
 *
 *	Targ_FindNode	    	Find the node for a given target, creating
 *	    	  	    	and storing it if it doesn't exist and the
 *	    	  	    	flags are right (TARG_CREATE)
 *
 *	Targ_FindList	    	Given a list of names, find nodes for all
 *	    	  	    	of them. If a name doesn't exist and the
 *	    	  	    	TARG_NOCREATE flag was given, an error message
 *	    	  	    	is printed. Else, if a name doesn't exist,
 *	    	  	    	its node is created.
 *
 *	Targ_Ignore	    	Return TRUE if errors should be ignored when
 *	    	  	    	creating the given target.
 *
 *	Targ_Silent	    	Return TRUE if we should be silent when
 *	    	  	    	creating the given target.
 *
 *	Targ_Precious	    	Return TRUE if the target is precious and
 *	    	  	    	should not be removed if we are interrupted.
 *
 * Debugging:
 *	Targ_PrintGraph	    	Print out the entire graphm all variables
 *	    	  	    	and statistics for the directory cache. Should
 *	    	  	    	print something for suffixes, too, but...
 */
D 2
#ifndef lint
static char     *rcsid = "$Id: targ.c,v 1.38 89/11/14 13:44:15 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

#include	  <stdio.h>
#include	  <time.h>
#include	  "make.h"
#include	  "hash.h"
I 10
#include	  "dir.h"
E 10

static Lst        allTargets;	/* the list of all targets found so far */
I 13
static Lst	  allGNs;	/* List of all the GNodes */
E 13
static Hash_Table targets;	/* a hash table of same */

#define HTSIZE	191		/* initial size of hash table */

I 13
static int TargPrintOnlySrc __P((ClientData, ClientData));
static int TargPrintName __P((ClientData, ClientData));
static int TargPrintNode __P((ClientData, ClientData));
static void TargFreeGN __P((ClientData));

E 13
/*-
 *-----------------------------------------------------------------------
 * Targ_Init --
 *	Initialize this module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The allTargets list and the targets hash table are initialized
 *-----------------------------------------------------------------------
 */
void
Targ_Init ()
{
    allTargets = Lst_Init (FALSE);
D 8
    Hash_InitTable (&targets, HTSIZE, HASH_STRING_KEYS);
E 8
I 8
    Hash_InitTable (&targets, HTSIZE);
E 8
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
I 13
 * Targ_End --
 *	Finalize this module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All lists and gnodes are cleared
 *-----------------------------------------------------------------------
 */
void
Targ_End ()
{
    Lst_Destroy(allTargets, NOFREE);
    if (allGNs)
	Lst_Destroy(allGNs, TargFreeGN);
    Hash_DeleteTable(&targets);
}

/*-
 *-----------------------------------------------------------------------
E 13
 * Targ_NewGN  --
 *	Create and initialize a new graph node
 *
 * Results:
 *	An initialized graph node with the name field filled with a copy
 *	of the passed name
 *
 * Side Effects:
D 13
 *	None.
E 13
I 13
 *	The gnode is added to the list of all gnodes.
E 13
 *-----------------------------------------------------------------------
 */
GNode *
Targ_NewGN (name)
    char           *name;	/* the name to stick in the new node */
{
    register GNode *gn;

D 5
    gn = (GNode *) malloc (sizeof (GNode));
E 5
I 5
    gn = (GNode *) emalloc (sizeof (GNode));
E 5
D 3
    gn->name = Str_New (name);
E 3
I 3
    gn->name = strdup (name);
E 3
    gn->path = (char *) 0;
    if (name[0] == '-' && name[1] == 'l') {
	gn->type = OP_LIB;
    } else {
	gn->type = 0;
    }
    gn->unmade =    	0;
    gn->make = 	    	FALSE;
    gn->made = 	    	UNMADE;
    gn->childMade = 	FALSE;
    gn->mtime = gn->cmtime = 0;
    gn->iParents =  	Lst_Init (FALSE);
    gn->cohorts =   	Lst_Init (FALSE);
    gn->parents =   	Lst_Init (FALSE);
    gn->children =  	Lst_Init (FALSE);
D 13
    gn->successors = 	Lst_Init(FALSE);
    gn->preds =     	Lst_Init(FALSE);
E 13
I 13
    gn->successors = 	Lst_Init (FALSE);
    gn->preds =     	Lst_Init (FALSE);
E 13
    gn->context =   	Lst_Init (FALSE);
    gn->commands =  	Lst_Init (FALSE);
I 10
D 12
    gn->suffix = 	NULL;
E 12
I 12
    gn->suffix =	NULL;
E 12
E 10

I 13
    if (allGNs == NULL)
	allGNs = Lst_Init(FALSE);
    Lst_AtEnd(allGNs, (ClientData) gn);

E 13
    return (gn);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
I 13
 * TargFreeGN  --
 *	Destroy a GNode
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
static void
TargFreeGN (gnp)
    ClientData gnp;
{
    GNode *gn = (GNode *) gnp;


    free(gn->name);
    if (gn->path)
	free(gn->path);

    Lst_Destroy(gn->iParents, NOFREE);
    Lst_Destroy(gn->cohorts, NOFREE);
    Lst_Destroy(gn->parents, NOFREE);
    Lst_Destroy(gn->children, NOFREE);
    Lst_Destroy(gn->successors, NOFREE);
    Lst_Destroy(gn->preds, NOFREE);
    Lst_Destroy(gn->context, NOFREE);
    Lst_Destroy(gn->commands, NOFREE);
    free((Address)gn);
}


/*-
 *-----------------------------------------------------------------------
E 13
 * Targ_FindNode  --
 *	Find a node in the list using the given name for matching
 *
 * Results:
 *	The node in the list if it was. If it wasn't, return NILGNODE of
 *	flags was TARG_NOCREATE or the newly created and initialized node
 *	if it was TARG_CREATE
 *
 * Side Effects:
 *	Sometimes a node is created and added to the list
 *-----------------------------------------------------------------------
 */
GNode *
Targ_FindNode (name, flags)
    char           *name;	/* the name to find */
    int             flags;	/* flags governing events when target not
				 * found */
{
    GNode         *gn;	      /* node in that element */
    Hash_Entry	  *he;	      /* New or used hash entry for node */
    Boolean	  isNew;      /* Set TRUE if Hash_CreateEntry had to create */
			      /* an entry for the node */


    if (flags & TARG_CREATE) {
	he = Hash_CreateEntry (&targets, name, &isNew);
	if (isNew) {
	    gn = Targ_NewGN (name);
	    Hash_SetValue (he, gn);
	    (void) Lst_AtEnd (allTargets, (ClientData)gn);
	}
    } else {
	he = Hash_FindEntry (&targets, name);
    }

    if (he == (Hash_Entry *) NULL) {
	return (NILGNODE);
    } else {
	return ((GNode *) Hash_GetValue (he));
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Targ_FindList --
 *	Make a complete list of GNodes from the given list of names 
 *
 * Results:
 *	A complete list of graph nodes corresponding to all instances of all
 *	the names in names. 
 *
 * Side Effects:
 *	If flags is TARG_CREATE, nodes will be created for all names in
 *	names which do not yet have graph nodes. If flags is TARG_NOCREATE,
 *	an error message will be printed for each name which can't be found.
 * -----------------------------------------------------------------------
 */
Lst
Targ_FindList (names, flags)
    Lst        	   names;	/* list of names to find */
    int            flags;	/* flags used if no node is found for a given
				 * name */
{
    Lst            nodes;	/* result list */
    register LstNode  ln;		/* name list element */
    register GNode *gn;		/* node in tLn */
    char    	  *name;

    nodes = Lst_Init (FALSE);

    if (Lst_Open (names) == FAILURE) {
	return (nodes);
    }
    while ((ln = Lst_Next (names)) != NILLNODE) {
	name = (char *)Lst_Datum(ln);
	gn = Targ_FindNode (name, flags);
	if (gn != NILGNODE) {
	    /*
	     * Note: Lst_AtEnd must come before the Lst_Concat so the nodes
	     * are added to the list in the order in which they were
	     * encountered in the makefile.
	     */
	    (void) Lst_AtEnd (nodes, (ClientData)gn);
	    if (gn->type & OP_DOUBLEDEP) {
		(void)Lst_Concat (nodes, gn->cohorts, LST_CONCNEW);
	    }
	} else if (flags == TARG_NOCREATE) {
	    Error ("\"%s\" -- target unknown.", name);
	}
    }
    Lst_Close (names);
    return (nodes);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Targ_Ignore  --
 *	Return true if should ignore errors when creating gn
 *
 * Results:
 *	TRUE if should ignore errors
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Ignore (gn)
    GNode          *gn;		/* node to check for */
{
    if (ignoreErrors || gn->type & OP_IGNORE) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Targ_Silent  --
 *	Return true if be silent when creating gn
 *
 * Results:
 *	TRUE if should be silent
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Silent (gn)
    GNode          *gn;		/* node to check for */
{
    if (beSilent || gn->type & OP_SILENT) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Targ_Precious --
 *	See if the given target is precious
 *
 * Results:
 *	TRUE if it is precious. FALSE otherwise
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Precious (gn)
    GNode          *gn;		/* the node to check */
{
    if (allPrecious || (gn->type & (OP_PRECIOUS|OP_DOUBLEDEP))) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}
D 3

E 3
I 3

E 3
/******************* DEBUG INFO PRINTING ****************/

static GNode	  *mainTarg;	/* the main target, as set by Targ_SetMain */
/*- 
 *-----------------------------------------------------------------------
 * Targ_SetMain --
 *	Set our idea of the main target we'll be creating. Used for
 *	debugging output.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	"mainTarg" is set to the main target's node.
 *-----------------------------------------------------------------------
 */
void
Targ_SetMain (gn)
    GNode   *gn;  	/* The main target we'll create */
{
    mainTarg = gn;
}

static int
I 10
D 13
/*ARGSUSED*/
E 10
TargPrintName (gn, ppath)
    GNode          *gn;
    int		    ppath;
E 13
I 13
TargPrintName (gnp, ppath)
    ClientData     gnp;
    ClientData	    ppath;
E 13
{
I 13
    GNode *gn = (GNode *) gnp;
E 13
    printf ("%s ", gn->name);
#ifdef notdef
    if (ppath) {
	if (gn->path) {
	    printf ("[%s]  ", gn->path);
	}
	if (gn == mainTarg) {
	    printf ("(MAIN NAME)  ");
	}
    }
D 10
#endif notdef
E 10
I 10
#endif /* notdef */
E 10
D 13
    return (0);
E 13
I 13
    return (ppath ? 0 : 0);
E 13
}


int
D 13
Targ_PrintCmd (cmd)
    char           *cmd;
E 13
I 13
Targ_PrintCmd (cmd, dummy)
    ClientData cmd;
    ClientData dummy;
E 13
{
D 13
    printf ("\t%s\n", cmd);
    return (0);
E 13
I 13
    printf ("\t%s\n", (char *) cmd);
    return (dummy ? 0 : 0);
E 13
}

/*-
 *-----------------------------------------------------------------------
 * Targ_FmtTime --
 *	Format a modification time in some reasonable way and return it.
 *
 * Results:
 *	The time reformatted.
 *
 * Side Effects:
 *	The time is placed in a static area, so it is overwritten
 *	with each call.
 *
 *-----------------------------------------------------------------------
 */
char *
Targ_FmtTime (time)
D 9
    int    time;
E 9
I 9
    time_t    time;
E 9
{
    struct tm	  	*parts;
    static char	  	buf[40];
    static char	  	*months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    parts = localtime(&time);

    sprintf (buf, "%d:%02d:%02d %s %d, 19%d",
	     parts->tm_hour, parts->tm_min, parts->tm_sec,
	     months[parts->tm_mon], parts->tm_mday, parts->tm_year);
    return(buf);
}
    
/*-
 *-----------------------------------------------------------------------
 * Targ_PrintType --
 *	Print out a type field giving only those attributes the user can
 *	set.
 *
 * Results:
 *
 * Side Effects:
 *
 *-----------------------------------------------------------------------
 */
void
Targ_PrintType (type)
    register int    type;
{
    register int    tbit;
    
#ifdef __STDC__
#define PRINTBIT(attr)	case CONCAT(OP_,attr): printf("." #attr " "); break
#define PRINTDBIT(attr) case CONCAT(OP_,attr): if (DEBUG(TARG)) printf("." #attr " "); break
#else
#define PRINTBIT(attr) 	case CONCAT(OP_,attr): printf(".attr "); break
#define PRINTDBIT(attr)	case CONCAT(OP_,attr): if (DEBUG(TARG)) printf(".attr "); break
#endif /* __STDC__ */

    type &= ~OP_OPMASK;

    while (type) {
	tbit = 1 << (ffs(type) - 1);
	type &= ~tbit;

	switch(tbit) {
D 6
	    PRINTBIT(DONTCARE);
E 6
I 6
	    PRINTBIT(OPTIONAL);
E 6
	    PRINTBIT(USE);
	    PRINTBIT(EXEC);
	    PRINTBIT(IGNORE);
	    PRINTBIT(PRECIOUS);
	    PRINTBIT(SILENT);
	    PRINTBIT(MAKE);
	    PRINTBIT(JOIN);
D 4
	    PRINTBIT(EXPORT);
	    PRINTBIT(NOEXPORT);
	    PRINTBIT(EXPORTSAME);
E 4
	    PRINTBIT(INVISIBLE);
	    PRINTBIT(NOTMAIN);
	    PRINTDBIT(LIB);
D 4
	    PRINTBIT(M68020);
E 4
	    /*XXX: MEMBER is defined, so CONCAT(OP_,MEMBER) gives OP_"%" */
	    case OP_MEMBER: if (DEBUG(TARG)) printf(".MEMBER "); break;
	    PRINTDBIT(ARCHV);
	}
    }
}

/*-
 *-----------------------------------------------------------------------
 * TargPrintNode --
 *	print the contents of a node
 *-----------------------------------------------------------------------
 */
static int
D 13
TargPrintNode (gn, pass)
    GNode         *gn;
    int	    	  pass;
E 13
I 13
TargPrintNode (gnp, passp)
    ClientData   gnp;
    ClientData	 passp;
E 13
{
I 13
    GNode         *gn = (GNode *) gnp;
    int	    	  pass = *(int *) passp;
E 13
    if (!OP_NOP(gn->type)) {
	printf("#\n");
	if (gn == mainTarg) {
	    printf("# *** MAIN TARGET ***\n");
	}
	if (pass == 2) {
	    if (gn->unmade) {
		printf("# %d unmade children\n", gn->unmade);
	    } else {
		printf("# No unmade children\n");
	    }
	    if (! (gn->type & (OP_JOIN|OP_USE|OP_EXEC))) {
		if (gn->mtime != 0) {
		    printf("# last modified %s: %s\n",
			      Targ_FmtTime(gn->mtime),
			      (gn->made == UNMADE ? "unmade" :
			       (gn->made == MADE ? "made" :
				(gn->made == UPTODATE ? "up-to-date" :
				 "error when made"))));
		} else if (gn->made != UNMADE) {
		    printf("# non-existent (maybe): %s\n",
			      (gn->made == MADE ? "made" :
			       (gn->made == UPTODATE ? "up-to-date" :
				(gn->made == ERROR ? "error when made" :
				 "aborted"))));
		} else {
		    printf("# unmade\n");
		}
	    }
	    if (!Lst_IsEmpty (gn->iParents)) {
		printf("# implicit parents: ");
		Lst_ForEach (gn->iParents, TargPrintName, (ClientData)0);
D 10
		putc ('\n', stdout);
E 10
I 10
		fputc ('\n', stdout);
E 10
	    }
	}
	if (!Lst_IsEmpty (gn->parents)) {
	    printf("# parents: ");
	    Lst_ForEach (gn->parents, TargPrintName, (ClientData)0);
D 10
	    putc ('\n', stdout);
E 10
I 10
	    fputc ('\n', stdout);
E 10
	}
	
	printf("%-16s", gn->name);
	switch (gn->type & OP_OPMASK) {
	    case OP_DEPENDS:
		printf(": "); break;
	    case OP_FORCE:
		printf("! "); break;
	    case OP_DOUBLEDEP:
		printf(":: "); break;
	}
	Targ_PrintType (gn->type);
	Lst_ForEach (gn->children, TargPrintName, (ClientData)0);
D 10
	putc ('\n', stdout);
E 10
I 10
	fputc ('\n', stdout);
E 10
	Lst_ForEach (gn->commands, Targ_PrintCmd, (ClientData)0);
	printf("\n\n");
	if (gn->type & OP_DOUBLEDEP) {
D 13
	    Lst_ForEach (gn->cohorts, TargPrintNode, (ClientData)pass);
E 13
I 13
	    Lst_ForEach (gn->cohorts, TargPrintNode, (ClientData)&pass);
E 13
	}
    }
    return (0);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * TargPrintOnlySrc --
 *	Print only those targets that are just a source.
 *
 * Results:
 *	0.
 *
 * Side Effects:
 *	The name of each file is printed preceeded by #\t
 *
 *-----------------------------------------------------------------------
 */
static int
D 13
TargPrintOnlySrc(gn)
    GNode   	  *gn;
E 13
I 13
TargPrintOnlySrc(gnp, dummy)
    ClientData 	  gnp;
    ClientData 	  dummy;
E 13
{
D 13
    if (OP_NOP(gn->type)) {
	printf("#\t%s [%s]\n", gn->name,
		  gn->path ? gn->path : gn->name);
    }
    return (0);
E 13
I 13
    GNode   	  *gn = (GNode *) gnp;
    if (OP_NOP(gn->type))
	printf("#\t%s [%s]\n", gn->name, gn->path ? gn->path : gn->name);

    return (dummy ? 0 : 0);
E 13
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Targ_PrintGraph --
 *	print the entire graph. heh heh
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	lots o' output
 *-----------------------------------------------------------------------
 */
I 10
void
E 10
Targ_PrintGraph (pass)
    int	    pass; 	/* Which pass this is. 1 => no processing
			 * 2 => processing done */
{
    printf("#*** Input graph:\n");
D 13
    Lst_ForEach (allTargets, TargPrintNode, (ClientData)pass);
E 13
I 13
    Lst_ForEach (allTargets, TargPrintNode, (ClientData)&pass);
E 13
    printf("\n\n");
    printf("#\n#   Files that are only sources:\n");
D 13
    Lst_ForEach (allTargets, TargPrintOnlySrc);
E 13
I 13
    Lst_ForEach (allTargets, TargPrintOnlySrc, (ClientData) 0);
E 13
    printf("#*** Global Variables:\n");
    Var_Dump (VAR_GLOBAL);
    printf("#*** Command-line Variables:\n");
    Var_Dump (VAR_CMD);
    printf("\n");
    Dir_PrintDirectories();
    printf("\n");
    Suff_PrintAll();
}
E 1
