h52243
s 00137/00090/01870
d D 8.4 95/04/28 17:08:31 christos 14 13
c Updated to the latest version from the NetBSD source
e
s 00046/00003/01914
d D 8.3 94/03/19 10:53:17 bostic 13 12
c The SYSV ${VAR:src=dst} was broken; try:
c SRC=foo.c bar.c
c all:
c 	echo ${SRC:%.c=%.o}
c From: Christos Zoulas <christos@deshaw.com>
e
s 00002/00002/01915
d D 8.2 94/01/02 15:05:36 bostic 12 10
c cosmetic changes, to cast to the right type for printf
e
s 00002/00002/01915
d R 8.2 94/01/02 15:02:21 bostic 11 10
c 
e
s 00002/00002/01915
d D 8.1 93/06/06 15:17:43 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00107/00043/01810
d D 5.9 93/05/24 14:46:05 bostic 9 8
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00001/01852
d D 5.8 91/11/18 15:46:56 bostic 8 7
c bad setenv call
e
s 00001/00011/01852
d D 5.7 90/06/01 17:10:10 bostic 7 6
c new copyright notice
e
s 00006/00006/01857
d D 5.6 90/03/19 09:58:16 bostic 6 5
c replace malloc with emalloc
e
s 00035/00024/01828
d D 5.5 90/03/17 15:33:12 bostic 5 4
c replace chained if's with a switch
e
s 00000/00006/01852
d D 5.4 90/03/12 09:55:02 bostic 4 3
c wire in DEF_OLD_VARS, still needs more work (oldVars variable)
e
s 00024/00024/01834
d D 5.3 90/03/12 09:00:07 bostic 3 2
c Str_New -> strdup
e
s 00026/00015/01832
d D 5.2 90/03/11 15:39:42 bostic 2 1
c add Berkeley specific copyright notice
e
s 01847/00000/00000
d D 5.1 90/03/11 15:27:57 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * var.c --
 *	Variable-handling functions
 *
 * Copyright (c) 1988, 1989 by the Regents of the University of California
E 2
I 2
/*
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

/*-
 * var.c --
 *	Variable-handling functions
 *
E 2
 * Interface:
 *	Var_Set	  	    Set the value of a variable in the given
 *	    	  	    context. The variable is created if it doesn't
 *	    	  	    yet exist. The value and variable name need not
 *	    	  	    be preserved.
 *
 *	Var_Append	    Append more characters to an existing variable
 *	    	  	    in the given context. The variable needn't
 *	    	  	    exist already -- it will be created if it doesn't.
 *	    	  	    A space is placed between the old value and the
 *	    	  	    new one.
 *
 *	Var_Exists	    See if a variable exists.
 *
 *	Var_Value 	    Return the value of a variable in a context or
 *	    	  	    NULL if the variable is undefined.
 *
D 9
 *	Var_Subst 	    Substitute for all variables in a string using
E 9
I 9
 *	Var_Subst 	    Substitute named variable, or all variables if
 *			    NULL in a string using
E 9
 *	    	  	    the given context as the top-most one. If the
 *	    	  	    third argument is non-zero, Parse_Error is
 *	    	  	    called if any variables are undefined.
 *
 *	Var_Parse 	    Parse a variable expansion from a string and
 *	    	  	    return the result and the number of characters
 *	    	  	    consumed.
 *
 *	Var_Delete	    Delete a variable in a context.
 *
 *	Var_Init  	    Initialize this module.
 *
 * Debugging:
 *	Var_Dump  	    Print out all variables defined in the given
 *	    	  	    context.
 *
 * XXX: There's a lot of duplication in these functions.
 */
D 2
#ifndef lint
static char     *rcsid = "$Id: var.c,v 1.57 89/11/14 13:44:16 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

#include    <ctype.h>
#include    "make.h"
#include    "buf.h"
D 9
extern char *getenv();
E 9

/*
 * This is a harmless return value for Var_Parse that can be used by Var_Subst
 * to determine if there was an error in parsing -- easier than returning
 * a flag, as things outside this module don't give a hoot.
 */
char 	var_Error[] = "";

/*
 * Similar to var_Error, but returned when the 'err' flag for Var_Parse is
 * set false. Why not just use a constant? Well, gcc likes to condense
 * identical string instances...
 */
D 9
char	varNoError[] = "";
E 9
I 9
static char	varNoError[] = "";
E 9

/*
 * Internally, variables are contained in four different contexts.
 *	1) the environment. They may not be changed. If an environment
 *	    variable is appended-to, the result is placed in the global
 *	    context.
 *	2) the global context. Variables set in the Makefile are located in
 *	    the global context. It is the penultimate context searched when
 *	    substituting.
 *	3) the command-line context. All variables set on the command line
 *	   are placed in this context. They are UNALTERABLE once placed here.
 *	4) the local context. Each target has associated with it a context
 *	   list. On this list are located the structures describing such
 *	   local variables as $(@) and $(*)
 * The four contexts are searched in the reverse order from which they are
 * listed.
 */
GNode          *VAR_GLOBAL;   /* variables from the makefile */
GNode          *VAR_CMD;      /* variables defined on the command-line */

I 14
static Lst	allVars;      /* List of all variables */

E 14
#define FIND_CMD	0x1   /* look in VAR_CMD when searching */
#define FIND_GLOBAL	0x2   /* look in VAR_GLOBAL as well */
#define FIND_ENV  	0x4   /* look in the environment also */

typedef struct Var {
    char          *name;	/* the variable's name */
    Buffer	  val;	    	/* its value */
    int	    	  flags;    	/* miscellaneous status flags */
#define VAR_IN_USE	1   	    /* Variable's value currently being used.
				     * Used to avoid recursion */
#define VAR_FROM_ENV	2   	    /* Variable comes from the environment */
#define VAR_JUNK  	4   	    /* Variable is a junk variable that
				     * should be destroyed when done with
				     * it. Used by Var_Parse for undefined,
				     * modified variables */
}  Var;
D 3

E 3
I 3

I 9
typedef struct {
    char    	  *lhs;	    /* String to match */
    int	    	  leftLen;  /* Length of string */
    char    	  *rhs;	    /* Replacement string (w/ &'s removed) */
    int	    	  rightLen; /* Length of replacement */
    int	    	  flags;
#define VAR_SUB_GLOBAL	1   /* Apply substitution globally */
#define VAR_MATCH_START	2   /* Match at start of word */
#define VAR_MATCH_END	4   /* Match at end of word */
#define VAR_NO_SUB	8   /* Substitution is non-global and already done */
} VarPattern;

D 14
static int VarCmp __P((Var *, char *));
E 14
I 14
static int VarCmp __P((ClientData, ClientData));
E 14
static Var *VarFind __P((char *, GNode *, int));
static void VarAdd __P((char *, char *, GNode *));
D 14
static Boolean VarHead __P((char *, Boolean, Buffer));
static Boolean VarTail __P((char *, Boolean, Buffer));
static Boolean VarSuffix __P((char *, Boolean, Buffer));
static Boolean VarRoot __P((char *, Boolean, Buffer));
static Boolean VarMatch __P((char *, Boolean, Buffer, char *));
I 13
static Boolean VarSYSVMatch __P((char *, Boolean, Buffer, VarPattern *));
E 13
static Boolean VarNoMatch __P((char *, Boolean, Buffer, char *));
static Boolean VarSubstitute __P((char *, Boolean, Buffer, VarPattern *));
static char *VarModify __P((char *, Boolean (*modProc )(), ClientData));
static int VarPrintVar __P((Var *));
E 14
I 14
static void VarDelete __P((ClientData));
static Boolean VarHead __P((char *, Boolean, Buffer, ClientData));
static Boolean VarTail __P((char *, Boolean, Buffer, ClientData));
static Boolean VarSuffix __P((char *, Boolean, Buffer, ClientData));
static Boolean VarRoot __P((char *, Boolean, Buffer, ClientData));
static Boolean VarMatch __P((char *, Boolean, Buffer, ClientData));
static Boolean VarSYSVMatch __P((char *, Boolean, Buffer, ClientData));
static Boolean VarNoMatch __P((char *, Boolean, Buffer, ClientData));
static Boolean VarSubstitute __P((char *, Boolean, Buffer, ClientData));
static char *VarModify __P((char *, Boolean (*)(char *, Boolean, Buffer,
						ClientData),
			    ClientData));
static int VarPrintVar __P((ClientData, ClientData));
E 14

E 9
E 3
/*-
 *-----------------------------------------------------------------------
 * VarCmp  --
 *	See if the given variable matches the named one. Called from
 *	Lst_Find when searching for a variable of a given name.
 *
 * Results:
 *	0 if they match. non-zero otherwise.
 *
 * Side Effects:
 *	none
 *-----------------------------------------------------------------------
 */
static int
VarCmp (v, name)
D 14
    Var            *v;		/* VAR structure to compare */
    char           *name;	/* name to look for */
E 14
I 14
    ClientData     v;		/* VAR structure to compare */
    ClientData     name;	/* name to look for */
E 14
{
D 14
    return (strcmp (name, v->name));
E 14
I 14
    return (strcmp ((char *) name, ((Var *) v)->name));
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * VarFind --
 *	Find the given variable in the given context and any other contexts
 *	indicated.
 *
 * Results:
 *	A pointer to the structure describing the desired variable or
 *	NIL if the variable does not exist.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static Var *
VarFind (name, ctxt, flags)
    char           	*name;	/* name to find */
    GNode          	*ctxt;	/* context in which to find it */
    int             	flags;	/* FIND_GLOBAL set means to look in the
				 * VAR_GLOBAL context as well.
				 * FIND_CMD set means to look in the VAR_CMD
				 * context also.
				 * FIND_ENV set means to look in the
				 * environment */
{
    LstNode         	var;
    Var		  	*v;

D 5
    /*
     * If the variable name begins with a '.' and an upper-case letter,
     * it could very well be one of the local ones. We check the name
     * against all the local variables and substitute the short version in for
     * 'name' if it matches one of them.
     */
    if (*name == '.' && isupper (name[1])) {
	if (strcmp (name, ".TARGET") == 0) {
	    name = TARGET;
	} else if (strcmp (name, ".IMPSRC") == 0) {
	    name = IMPSRC;
	} else if (strcmp (name, ".PREFIX") == 0) {
	    name = PREFIX;
	} else if (strcmp (name, ".ALLSRC") == 0) {
	    name = ALLSRC;
	} else if (strcmp (name, ".OODATE") == 0) {
	    name = OODATE;
	} else if (strcmp (name, ".ARCHIVE") == 0) {
	    name = ARCHIVE;
	} else if (strcmp (name, ".MEMBER") == 0) {
	    name = MEMBER;
	}	    
    }

E 5
I 5
	/*
	 * If the variable name begins with a '.', it could very well be one of
	 * the local ones.  We check the name against all the local variables
	 * and substitute the short version in for 'name' if it matches one of
	 * them.
	 */
D 14
	if (*name == '.' && isupper(name[1]))
E 14
I 14
	if (*name == '.' && isupper((unsigned char) name[1]))
E 14
		switch (name[1]) {
		case 'A':
			if (!strcmp(name, ".ALLSRC"))
				name = ALLSRC;
			if (!strcmp(name, ".ARCHIVE"))
				name = ARCHIVE;
			break;
		case 'I':
			if (!strcmp(name, ".IMPSRC"))
				name = IMPSRC;
			break;
		case 'M':
			if (!strcmp(name, ".MEMBER"))
				name = MEMBER;
			break;
		case 'O':
			if (!strcmp(name, ".OODATE"))
				name = OODATE;
			break;
		case 'P':
			if (!strcmp(name, ".PREFIX"))
				name = PREFIX;
			break;
		case 'T':
			if (!strcmp(name, ".TARGET"))
				name = TARGET;
			break;
		}
E 5
    /*
     * First look for the variable in the given context. If it's not there,
     * look for it in VAR_CMD, VAR_GLOBAL and the environment, in that order,
     * depending on the FIND_* flags in 'flags'
     */
    var = Lst_Find (ctxt->context, (ClientData)name, VarCmp);

    if ((var == NILLNODE) && (flags & FIND_CMD) && (ctxt != VAR_CMD)) {
	var = Lst_Find (VAR_CMD->context, (ClientData)name, VarCmp);
    }
    if (!checkEnvFirst && (var == NILLNODE) && (flags & FIND_GLOBAL) &&
	(ctxt != VAR_GLOBAL))
    {
	var = Lst_Find (VAR_GLOBAL->context, (ClientData)name, VarCmp);
    }
    if ((var == NILLNODE) && (flags & FIND_ENV)) {
	char *env;

	if ((env = getenv (name)) != NULL) {
D 14
	    /*
	     * If the variable is found in the environment, we only duplicate
	     * its value (since eVarVal was allocated on the stack). The name
	     * doesn't need duplication since it's always in the environment
	     */
E 14
	    int	  	len;
	    
D 6
	    v = (Var *) malloc(sizeof(Var));
E 6
I 6
	    v = (Var *) emalloc(sizeof(Var));
E 6
D 14
	    v->name = name;
E 14
I 14
	    v->name = strdup(name);
E 14

	    len = strlen(env);
	    
	    v->val = Buf_Init(len);
	    Buf_AddBytes(v->val, len, (Byte *)env);
	    
	    v->flags = VAR_FROM_ENV;
	    return (v);
	} else if (checkEnvFirst && (flags & FIND_GLOBAL) &&
		   (ctxt != VAR_GLOBAL))
	{
	    var = Lst_Find (VAR_GLOBAL->context, (ClientData)name, VarCmp);
	    if (var == NILLNODE) {
		return ((Var *) NIL);
	    } else {
		return ((Var *)Lst_Datum(var));
	    }
	} else {
	    return((Var *)NIL);
	}
    } else if (var == NILLNODE) {
	return ((Var *) NIL);
    } else {
	return ((Var *) Lst_Datum (var));
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * VarAdd  --
 *	Add a new variable of name name and value val to the given context
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The new variable is placed at the front of the given context
 *	The name and val arguments are duplicated so they may
 *	safely be freed.
 *-----------------------------------------------------------------------
 */
D 9
static
E 9
I 9
static void
E 9
VarAdd (name, val, ctxt)
    char           *name;	/* name of variable to add */
    char           *val;	/* value to set it to */
    GNode          *ctxt;	/* context in which to set it */
{
    register Var   *v;
    int	    	  len;

D 6
    v = (Var *) malloc (sizeof (Var));
E 6
I 6
    v = (Var *) emalloc (sizeof (Var));
E 6

D 3
    v->name = Str_New (name);
E 3
I 3
    v->name = strdup (name);
E 3

D 9
    len = strlen(val);
E 9
I 9
    len = val ? strlen(val) : 0;
E 9
    v->val = Buf_Init(len+1);
    Buf_AddBytes(v->val, len, (Byte *)val);

    v->flags = 0;

    (void) Lst_AtFront (ctxt->context, (ClientData)v);
I 14
    (void) Lst_AtEnd (allVars, (ClientData) v);
E 14
    if (DEBUG(VAR)) {
	printf("%s:%s = %s\n", ctxt->name, name, val);
    }
}
D 3

E 3
I 3

I 14

E 14
E 3
/*-
 *-----------------------------------------------------------------------
I 14
 * VarDelete  --
 *	Delete a variable and all the space associated with it.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static void
VarDelete(vp)
    ClientData vp;
{
    Var *v = (Var *) vp;
    free(v->name);
    Buf_Destroy(v->val, TRUE);
    free((Address) v);
}



/*-
 *-----------------------------------------------------------------------
E 14
 * Var_Delete --
 *	Remove a variable from a context.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The Var structure is removed and freed.
 *
 *-----------------------------------------------------------------------
 */
void
Var_Delete(name, ctxt)
    char    	  *name;
    GNode	  *ctxt;
{
    LstNode 	  ln;

    if (DEBUG(VAR)) {
	printf("%s:delete %s\n", ctxt->name, name);
    }
    ln = Lst_Find(ctxt->context, (ClientData)name, VarCmp);
    if (ln != NILLNODE) {
	register Var 	  *v;

	v = (Var *)Lst_Datum(ln);
	Lst_Remove(ctxt->context, ln);
D 14
	Buf_Destroy(v->val, TRUE);
	free(v->name);
	free((char *)v);
E 14
I 14
	ln = Lst_Member(allVars, v);
	Lst_Remove(allVars, ln);
	VarDelete((ClientData) v);
E 14
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_Set --
 *	Set the variable name to the value val in the given context.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	If the variable doesn't yet exist, a new record is created for it.
 *	Else the old value is freed and the new one stuck in its place
 *
 * Notes:
 *	The variable is searched for only in its context before being
 *	created in that context. I.e. if the context is VAR_GLOBAL,
 *	only VAR_GLOBAL->context is searched. Likewise if it is VAR_CMD, only
 *	VAR_CMD->context is searched. This is done to avoid the literally
 *	thousands of unnecessary strcmp's that used to be done to
 *	set, say, $(@) or $(<).
 *-----------------------------------------------------------------------
 */
void
Var_Set (name, val, ctxt)
    char           *name;	/* name of variable to set */
    char           *val;	/* value to give to the variable */
    GNode          *ctxt;	/* context in which to set it */
{
    register Var   *v;

    /*
     * We only look for a variable in the given context since anything set
     * here will override anything in a lower context, so there's not much
     * point in searching them all just to save a bit of memory...
     */
    v = VarFind (name, ctxt, 0);
    if (v == (Var *) NIL) {
	VarAdd (name, val, ctxt);
    } else {
	Buf_Discard(v->val, Buf_Size(v->val));
	Buf_AddBytes(v->val, strlen(val), (Byte *)val);

	if (DEBUG(VAR)) {
	    printf("%s:%s = %s\n", ctxt->name, name, val);
	}
    }
    /*
     * Any variables given on the command line are automatically exported
     * to the environment (as per POSIX standard)
     */
    if (ctxt == VAR_CMD) {
D 8
	setenv(name, val);
E 8
I 8
	setenv(name, val, 1);
E 8
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_Append --
 *	The variable of the given name has the given value appended to it in
 *	the given context.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	If the variable doesn't exist, it is created. Else the strings
 *	are concatenated (with a space in between).
 *
 * Notes:
 *	Only if the variable is being sought in the global context is the
 *	environment searched.
 *	XXX: Knows its calling circumstances in that if called with ctxt
 *	an actual target, it will only search that context since only
 *	a local variable could be being appended to. This is actually
 *	a big win and must be tolerated.
 *-----------------------------------------------------------------------
 */
void
Var_Append (name, val, ctxt)
    char           *name;	/* Name of variable to modify */
    char           *val;	/* String to append to it */
    GNode          *ctxt;	/* Context in which this should occur */
{
    register Var   *v;
D 9
    register char  *cp;
E 9

    v = VarFind (name, ctxt, (ctxt == VAR_GLOBAL) ? FIND_ENV : 0);

    if (v == (Var *) NIL) {
	VarAdd (name, val, ctxt);
    } else {
	Buf_AddByte(v->val, (Byte)' ');
	Buf_AddBytes(v->val, strlen(val), (Byte *)val);

	if (DEBUG(VAR)) {
	    printf("%s:%s = %s\n", ctxt->name, name,
D 12
		   Buf_GetAll(v->val, (int *)NULL));
E 12
I 12
		   (char *) Buf_GetAll(v->val, (int *)NULL));
E 12
	}

	if (v->flags & VAR_FROM_ENV) {
	    /*
	     * If the original variable came from the environment, we
	     * have to install it in the global context (we could place
	     * it in the environment, but then we should provide a way to
	     * export other variables...)
	     */
	    v->flags &= ~VAR_FROM_ENV;
	    Lst_AtFront(ctxt->context, (ClientData)v);
	}
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_Exists --
 *	See if the given variable exists.
 *
 * Results:
 *	TRUE if it does, FALSE if it doesn't
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
Boolean
Var_Exists(name, ctxt)
    char	  *name;    	/* Variable to find */
    GNode	  *ctxt;    	/* Context in which to start search */
{
    Var	    	  *v;

    v = VarFind(name, ctxt, FIND_CMD|FIND_GLOBAL|FIND_ENV);

    if (v == (Var *)NIL) {
	return(FALSE);
    } else if (v->flags & VAR_FROM_ENV) {
I 14
	free(v->name);
E 14
	Buf_Destroy(v->val, TRUE);
	free((char *)v);
    }
    return(TRUE);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_Value --
 *	Return the value of the named variable in the given context
 *
 * Results:
 *	The value if the variable exists, NULL if it doesn't
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
char *
D 14
Var_Value (name, ctxt)
E 14
I 14
Var_Value (name, ctxt, frp)
E 14
    char           *name;	/* name to find */
    GNode          *ctxt;	/* context in which to search for it */
I 14
    char	   **frp;
E 14
{
    Var            *v;

    v = VarFind (name, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
I 14
    *frp = NULL;
E 14
    if (v != (Var *) NIL) {
D 14
	return ((char *)Buf_GetAll(v->val, (int *)NULL));
E 14
I 14
	char *p = ((char *)Buf_GetAll(v->val, (int *)NULL));
	if (v->flags & VAR_FROM_ENV) {
	    Buf_Destroy(v->val, FALSE);
	    free((Address) v);
	    *frp = p;
	}
	return p;
E 14
    } else {
	return ((char *) NULL);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * VarHead --
 *	Remove the tail of the given word and place the result in the given
 *	buffer.
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
D 14
VarHead (word, addSpace, buf)
E 14
I 14
VarHead (word, addSpace, buf, dummy)
E 14
    char    	  *word;    	/* Word to trim */
    Boolean 	  addSpace; 	/* True if need to add a space to the buffer
				 * before sticking in the head */
    Buffer  	  buf;	    	/* Buffer in which to store it */
I 14
    ClientData	  dummy;
E 14
{
    register char *slash;

D 9
    slash = rindex (word, '/');
E 9
I 9
    slash = strrchr (word, '/');
E 9
    if (slash != (char *)NULL) {
	if (addSpace) {
	    Buf_AddByte (buf, (Byte)' ');
	}
	*slash = '\0';
	Buf_AddBytes (buf, strlen (word), (Byte *)word);
	*slash = '/';
	return (TRUE);
    } else {
	/*
	 * If no directory part, give . (q.v. the POSIX standard)
	 */
	if (addSpace) {
	    Buf_AddBytes(buf, 2, (Byte *)" .");
	} else {
	    Buf_AddByte(buf, (Byte)'.');
	}
D 14
	return(TRUE);
E 14
    }
I 14
    return(dummy ? TRUE : TRUE);
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * VarTail --
 *	Remove the head of the given word and place the result in the given
 *	buffer.
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
D 14
VarTail (word, addSpace, buf)
E 14
I 14
VarTail (word, addSpace, buf, dummy)
E 14
    char    	  *word;    	/* Word to trim */
    Boolean 	  addSpace; 	/* TRUE if need to stick a space in the
				 * buffer before adding the tail */
    Buffer  	  buf;	    	/* Buffer in which to store it */
I 14
    ClientData	  dummy;
E 14
{
    register char *slash;

    if (addSpace) {
	Buf_AddByte (buf, (Byte)' ');
    }

D 9
    slash = rindex (word, '/');
E 9
I 9
    slash = strrchr (word, '/');
E 9
    if (slash != (char *)NULL) {
	*slash++ = '\0';
	Buf_AddBytes (buf, strlen(slash), (Byte *)slash);
	slash[-1] = '/';
    } else {
	Buf_AddBytes (buf, strlen(word), (Byte *)word);
    }
D 14
    return (TRUE);
E 14
I 14
    return (dummy ? TRUE : TRUE);
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * VarSuffix --
 *	Place the suffix of the given word in the given buffer.
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The suffix from the word is placed in the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
D 14
VarSuffix (word, addSpace, buf)
E 14
I 14
VarSuffix (word, addSpace, buf, dummy)
E 14
    char    	  *word;    	/* Word to trim */
    Boolean 	  addSpace; 	/* TRUE if need to add a space before placing
				 * the suffix in the buffer */
    Buffer  	  buf;	    	/* Buffer in which to store it */
I 14
    ClientData	  dummy;
E 14
{
    register char *dot;

D 9
    dot = rindex (word, '.');
E 9
I 9
    dot = strrchr (word, '.');
E 9
    if (dot != (char *)NULL) {
	if (addSpace) {
	    Buf_AddByte (buf, (Byte)' ');
	}
	*dot++ = '\0';
	Buf_AddBytes (buf, strlen (dot), (Byte *)dot);
	dot[-1] = '.';
D 14
	return (TRUE);
    } else {
	return (addSpace);
E 14
I 14
	addSpace = TRUE;
E 14
    }
I 14
    return (dummy ? addSpace : addSpace);
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * VarRoot --
 *	Remove the suffix of the given word and place the result in the
 *	buffer.
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
D 14
VarRoot (word, addSpace, buf)
E 14
I 14
VarRoot (word, addSpace, buf, dummy)
E 14
    char    	  *word;    	/* Word to trim */
    Boolean 	  addSpace; 	/* TRUE if need to add a space to the buffer
				 * before placing the root in it */
    Buffer  	  buf;	    	/* Buffer in which to store it */
I 14
    ClientData	  dummy;
E 14
{
    register char *dot;

    if (addSpace) {
	Buf_AddByte (buf, (Byte)' ');
    }

D 9
    dot = rindex (word, '.');
E 9
I 9
    dot = strrchr (word, '.');
E 9
    if (dot != (char *)NULL) {
	*dot = '\0';
	Buf_AddBytes (buf, strlen (word), (Byte *)word);
	*dot = '.';
    } else {
	Buf_AddBytes (buf, strlen(word), (Byte *)word);
    }
D 14
    return (TRUE);
E 14
I 14
    return (dummy ? TRUE : TRUE);
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * VarMatch --
 *	Place the word in the buffer if it matches the given pattern.
 *	Callback function for VarModify to implement the :M modifier.
 *	
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarMatch (word, addSpace, buf, pattern)
    char    	  *word;    	/* Word to examine */
    Boolean 	  addSpace; 	/* TRUE if need to add a space to the
				 * buffer before adding the word, if it
				 * matches */
    Buffer  	  buf;	    	/* Buffer in which to store it */
D 14
    char    	  *pattern; 	/* Pattern the word must match */
E 14
I 14
    ClientData    pattern; 	/* Pattern the word must match */
E 14
{
D 14
    if (Str_Match(word, pattern)) {
E 14
I 14
    if (Str_Match(word, (char *) pattern)) {
E 14
	if (addSpace) {
	    Buf_AddByte(buf, (Byte)' ');
	}
	addSpace = TRUE;
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return(addSpace);
}
D 3

E 3
I 3

I 13


E 13
E 3
/*-
 *-----------------------------------------------------------------------
I 13
 * VarSYSVMatch --
 *	Place the word in the buffer if it matches the given pattern.
 *	Callback function for VarModify to implement the System V %
 *	modifiers.
 *	
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
D 14
VarSYSVMatch (word, addSpace, buf, pat)
E 14
I 14
VarSYSVMatch (word, addSpace, buf, patp)
E 14
    char    	  *word;    	/* Word to examine */
    Boolean 	  addSpace; 	/* TRUE if need to add a space to the
				 * buffer before adding the word, if it
				 * matches */
    Buffer  	  buf;	    	/* Buffer in which to store it */
D 14
    VarPattern 	  *pat; 	/* Pattern the word must match */
E 14
I 14
    ClientData 	  patp; 	/* Pattern the word must match */
E 14
{
    int len;
    char *ptr;
I 14
    VarPattern 	  *pat = (VarPattern *) patp;
E 14

    if (addSpace)
	Buf_AddByte(buf, (Byte)' ');

    addSpace = TRUE;

    if ((ptr = Str_SYSVMatch(word, pat->lhs, &len)) != NULL)
	Str_SYSVSubst(buf, pat->rhs, ptr, len);
    else
	Buf_AddBytes(buf, strlen(word), (Byte *) word);

    return(addSpace);
}


/*-
 *-----------------------------------------------------------------------
E 13
 * VarNoMatch --
 *	Place the word in the buffer if it doesn't match the given pattern.
 *	Callback function for VarModify to implement the :N modifier.
 *	
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarNoMatch (word, addSpace, buf, pattern)
    char    	  *word;    	/* Word to examine */
    Boolean 	  addSpace; 	/* TRUE if need to add a space to the
				 * buffer before adding the word, if it
				 * matches */
    Buffer  	  buf;	    	/* Buffer in which to store it */
D 14
    char    	  *pattern; 	/* Pattern the word must match */
E 14
I 14
    ClientData    pattern; 	/* Pattern the word must match */
E 14
{
D 14
    if (!Str_Match(word, pattern)) {
E 14
I 14
    if (!Str_Match(word, (char *) pattern)) {
E 14
	if (addSpace) {
	    Buf_AddByte(buf, (Byte)' ');
	}
	addSpace = TRUE;
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return(addSpace);
}
D 3

E 3
I 3

E 3
D 9
typedef struct {
    char    	  *lhs;	    /* String to match */
    int	    	  leftLen;  /* Length of string */
    char    	  *rhs;	    /* Replacement string (w/ &'s removed) */
    int	    	  rightLen; /* Length of replacement */
    int	    	  flags;
#define VAR_SUB_GLOBAL	1   /* Apply substitution globally */
#define VAR_MATCH_START	2   /* Match at start of word */
#define VAR_MATCH_END	4   /* Match at end of word */
#define VAR_NO_SUB	8   /* Substitution is non-global and already done */
} VarPattern;
E 9

/*-
 *-----------------------------------------------------------------------
 * VarSubstitute --
 *	Perform a string-substitution on the given word, placing the
 *	result in the passed buffer.
 *
 * Results:
 *	TRUE if a space is needed before more characters are added.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
D 14
VarSubstitute (word, addSpace, buf, pattern)
E 14
I 14
VarSubstitute (word, addSpace, buf, patternp)
E 14
    char    	  	*word;	    /* Word to modify */
    Boolean 	  	addSpace;   /* True if space should be added before
				     * other characters */
    Buffer  	  	buf;	    /* Buffer for result */
D 14
    register VarPattern	*pattern;   /* Pattern for substitution */
E 14
I 14
    ClientData	        patternp;   /* Pattern for substitution */
E 14
{
    register int  	wordLen;    /* Length of word */
    register char 	*cp;	    /* General pointer */
I 14
    VarPattern	*pattern = (VarPattern *) patternp;
E 14

    wordLen = strlen(word);
    if ((pattern->flags & VAR_NO_SUB) == 0) {
	/*
	 * Still substituting -- break it down into simple anchored cases
	 * and if none of them fits, perform the general substitution case.
	 */
	if ((pattern->flags & VAR_MATCH_START) &&
	    (strncmp(word, pattern->lhs, pattern->leftLen) == 0)) {
		/*
		 * Anchored at start and beginning of word matches pattern
		 */
		if ((pattern->flags & VAR_MATCH_END) &&
		    (wordLen == pattern->leftLen)) {
			/*
			 * Also anchored at end and matches to the end (word
			 * is same length as pattern) add space and rhs only
			 * if rhs is non-null.
			 */
			if (pattern->rightLen != 0) {
			    if (addSpace) {
				Buf_AddByte(buf, (Byte)' ');
			    }
			    addSpace = TRUE;
			    Buf_AddBytes(buf, pattern->rightLen,
					 (Byte *)pattern->rhs);
			}
		} else if (pattern->flags & VAR_MATCH_END) {
		    /*
		     * Doesn't match to end -- copy word wholesale
		     */
		    goto nosub;
		} else {
		    /*
		     * Matches at start but need to copy in trailing characters
		     */
		    if ((pattern->rightLen + wordLen - pattern->leftLen) != 0){
			if (addSpace) {
			    Buf_AddByte(buf, (Byte)' ');
			}
			addSpace = TRUE;
		    }
		    Buf_AddBytes(buf, pattern->rightLen, (Byte *)pattern->rhs);
		    Buf_AddBytes(buf, wordLen - pattern->leftLen,
				 (Byte *)(word + pattern->leftLen));
		}
	} else if (pattern->flags & VAR_MATCH_START) {
	    /*
	     * Had to match at start of word and didn't -- copy whole word.
	     */
	    goto nosub;
	} else if (pattern->flags & VAR_MATCH_END) {
	    /*
	     * Anchored at end, Find only place match could occur (leftLen
	     * characters from the end of the word) and see if it does. Note
	     * that because the $ will be left at the end of the lhs, we have
	     * to use strncmp.
	     */
	    cp = word + (wordLen - pattern->leftLen);
	    if ((cp >= word) &&
		(strncmp(cp, pattern->lhs, pattern->leftLen) == 0)) {
		/*
		 * Match found. If we will place characters in the buffer,
		 * add a space before hand as indicated by addSpace, then
		 * stuff in the initial, unmatched part of the word followed
		 * by the right-hand-side.
		 */
		if (((cp - word) + pattern->rightLen) != 0) {
		    if (addSpace) {
			Buf_AddByte(buf, (Byte)' ');
		    }
		    addSpace = TRUE;
		}
		Buf_AddBytes(buf, cp - word, (Byte *)word);
		Buf_AddBytes(buf, pattern->rightLen, (Byte *)pattern->rhs);
	    } else {
		/*
		 * Had to match at end and didn't. Copy entire word.
		 */
		goto nosub;
	    }
	} else {
	    /*
	     * Pattern is unanchored: search for the pattern in the word using
	     * String_FindSubstring, copying unmatched portions and the
	     * right-hand-side for each match found, handling non-global
	     * subsititutions correctly, etc. When the loop is done, any
	     * remaining part of the word (word and wordLen are adjusted
	     * accordingly through the loop) is copied straight into the
	     * buffer.
	     * addSpace is set FALSE as soon as a space is added to the
	     * buffer.
	     */
	    register Boolean done;
	    int origSize;

	    done = FALSE;
	    origSize = Buf_Size(buf);
	    while (!done) {
		cp = Str_FindSubstring(word, pattern->lhs);
		if (cp != (char *)NULL) {
		    if (addSpace && (((cp - word) + pattern->rightLen) != 0)){
			Buf_AddByte(buf, (Byte)' ');
			addSpace = FALSE;
		    }
		    Buf_AddBytes(buf, cp-word, (Byte *)word);
		    Buf_AddBytes(buf, pattern->rightLen, (Byte *)pattern->rhs);
		    wordLen -= (cp - word) + pattern->leftLen;
		    word = cp + pattern->leftLen;
		    if (wordLen == 0) {
			done = TRUE;
		    }
		    if ((pattern->flags & VAR_SUB_GLOBAL) == 0) {
			done = TRUE;
			pattern->flags |= VAR_NO_SUB;
		    }
		} else {
		    done = TRUE;
		}
	    }
	    if (wordLen != 0) {
		if (addSpace) {
		    Buf_AddByte(buf, (Byte)' ');
		}
		Buf_AddBytes(buf, wordLen, (Byte *)word);
	    }
	    /*
	     * If added characters to the buffer, need to add a space
	     * before we add any more. If we didn't add any, just return
	     * the previous value of addSpace.
	     */
	    return ((Buf_Size(buf) != origSize) || addSpace);
	}
	/*
	 * Common code for anchored substitutions: if performed a substitution
	 * and it's not supposed to be global, mark the pattern as requiring
	 * no more substitutions. addSpace was set TRUE if characters were
	 * added to the buffer.
	 */
	if ((pattern->flags & VAR_SUB_GLOBAL) == 0) {
	    pattern->flags |= VAR_NO_SUB;
	}
	return (addSpace);
    }
 nosub:
    if (addSpace) {
	Buf_AddByte(buf, (Byte)' ');
    }
    Buf_AddBytes(buf, wordLen, (Byte *)word);
    return(TRUE);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * VarModify --
 *	Modify each of the words of the passed string using the given
 *	function. Used to implement all modifiers.
 *
 * Results:
 *	A string of all the words modified appropriately.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarModify (str, modProc, datum)
    char    	  *str;	    	    /* String whose words should be trimmed */
D 14
    Boolean    	  (*modProc)();     /* Function to use to modify them */
E 14
I 14
				    /* Function to use to modify them */
    Boolean    	  (*modProc) __P((char *, Boolean, Buffer, ClientData));
E 14
    ClientData	  datum;    	    /* Datum to pass it */
{
    Buffer  	  buf;	    	    /* Buffer for the new string */
D 14
    register char *cp;	    	    /* Pointer to end of current word */
    char    	  endc;	    	    /* Character that ended the word */
E 14
    Boolean 	  addSpace; 	    /* TRUE if need to add a space to the
				     * buffer before adding the trimmed
				     * word */
D 14
    
E 14
I 14
    char **av;			    /* word list [first word does not count] */
    int ac, i;

E 14
    buf = Buf_Init (0);
D 14
    cp = str;
E 14
    addSpace = FALSE;
D 14
    
D 9
    while (1) {
E 9
I 9
    for (;;) {
E 9
	/*
	 * Skip to next word and place cp at its end.
	 */
	while (isspace (*str)) {
	    str++;
	}
D 9
	for (cp = str; *cp != '\0' && !isspace (*cp); cp++) {
	    /* void */ ;
	}
E 9
I 9
	for (cp = str; *cp != '\0' && !isspace (*cp); cp++) 
	    continue;
E 9
	if (cp == str) {
	    /*
	     * If we didn't go anywhere, we must be done!
	     */
	    Buf_AddByte (buf, '\0');
	    str = (char *)Buf_GetAll (buf, (int *)NULL);
	    Buf_Destroy (buf, FALSE);
	    return (str);
	}
	/*
	 * Nuke terminating character, but save it in endc b/c if str was
	 * some variable's value, it would not be good to screw it
	 * over...
	 */
	endc = *cp;
	*cp = '\0';
E 14

D 14
	addSpace = (* modProc) (str, addSpace, buf, datum);
E 14
I 14
    av = brk_string(str, &ac, FALSE);
E 14

D 14
	if (endc) {
	    *cp++ = endc;
	}
	str = cp;
    }
E 14
I 14
    for (i = 1; i < ac; i++)
	addSpace = (*modProc)(av[i], addSpace, buf, datum);
    
    Buf_AddByte (buf, '\0');
    str = (char *)Buf_GetAll (buf, (int *)NULL);
    Buf_Destroy (buf, FALSE);
    return (str);
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_Parse --
 *	Given the start of a variable invocation, extract the variable
 *	name and find its value, then modify it according to the
 *	specification.
 *
 * Results:
 *	The (possibly-modified) value of the variable or var_Error if the
 *	specification is invalid. The length of the specification is
 *	placed in *lengthPtr (for invalid specifications, this is just
 *	2...?).
 *	A Boolean in *freePtr telling whether the returned string should
 *	be freed by the caller.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
char *
Var_Parse (str, ctxt, err, lengthPtr, freePtr)
    char    	  *str;	    	/* The string to parse */
    GNode   	  *ctxt;    	/* The context for the variable */
    Boolean 	    err;    	/* TRUE if undefined variables are an error */
    int	    	    *lengthPtr;	/* OUT: The length of the specification */
    Boolean 	    *freePtr; 	/* OUT: TRUE if caller should free result */
{
    register char   *tstr;    	/* Pointer into str */
    Var	    	    *v;	    	/* Variable in invocation */
    register char   *cp;    	/* Secondary pointer into str (place marker
				 * for tstr) */
    Boolean 	    haveModifier;/* TRUE if have modifiers for the variable */
    register char   endc;    	/* Ending character when variable in parens
				 * or braces */
I 14
    register char   startc;	/* Starting character when variable in parens
				 * or braces */
    int             cnt;	/* Used to count brace pairs when variable in
				 * in parens or braces */
E 14
    char    	    *start;
    Boolean 	    dynamic;	/* TRUE if the variable is local and we're
				 * expanding it in a non-local context. This
				 * is done to support dynamic sources. The
				 * result is just the invocation, unaltered */
    
    *freePtr = FALSE;
    dynamic = FALSE;
    start = str;
    
    if (str[1] != '(' && str[1] != '{') {
	/*
	 * If it's not bounded by braces of some sort, life is much simpler.
	 * We just need to check for the first character and return the
	 * value if it exists.
	 */
	char	  name[2];

	name[0] = str[1];
	name[1] = '\0';

	v = VarFind (name, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
	if (v == (Var *)NIL) {
	    *lengthPtr = 2;
	    
	    if ((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)) {
		/*
		 * If substituting a local variable in a non-local context,
		 * assume it's for dynamic source stuff. We have to handle
		 * this specially and return the longhand for the variable
		 * with the dollar sign escaped so it makes it back to the
		 * caller. Only four of the local variables are treated
		 * specially as they are the only four that will be set
		 * when dynamic sources are expanded.
		 */
		switch (str[1]) {
		    case '@':
			return("$(.TARGET)");
		    case '%':
			return("$(.ARCHIVE)");
		    case '*':
			return("$(.PREFIX)");
		    case '!':
			return("$(.MEMBER)");
		}
	    }
	    /*
	     * Error
	     */
	    return (err ? var_Error : varNoError);
	} else {
	    haveModifier = FALSE;
	    tstr = &str[1];
	    endc = str[1];
	}
    } else {
D 14
	endc = str[1] == '(' ? ')' : '}';
E 14
I 14
	startc = str[1];
	endc = startc == '(' ? ')' : '}';
E 14

	/*
	 * Skip to the end character or a colon, whichever comes first.
	 */
	for (tstr = str + 2;
	     *tstr != '\0' && *tstr != endc && *tstr != ':';
	     tstr++)
	{
	    continue;
	}
	if (*tstr == ':') {
	    haveModifier = TRUE;
	} else if (*tstr != '\0') {
	    haveModifier = FALSE;
	} else {
	    /*
	     * If we never did find the end character, return NULL
	     * right now, setting the length to be the distance to
	     * the end of the string, since that's what make does.
	     */
	    *lengthPtr = tstr - str;
	    return (var_Error);
	}
	*tstr = '\0';
 	
	v = VarFind (str + 2, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
	if ((v == (Var *)NIL) && (ctxt != VAR_CMD) && (ctxt != VAR_GLOBAL) &&
	    ((tstr-str) == 4) && (str[3] == 'F' || str[3] == 'D'))
	{
	    /*
	     * Check for bogus D and F forms of local variables since we're
	     * in a local context and the name is the right length.
	     */
	    switch(str[2]) {
		case '@':
		case '%':
		case '*':
		case '!':
		case '>':
		case '<':
		{
		    char    vname[2];
		    char    *val;

		    /*
		     * Well, it's local -- go look for it.
		     */
		    vname[0] = str[2];
		    vname[1] = '\0';
		    v = VarFind(vname, ctxt, 0);
		    
		    if (v != (Var *)NIL) {
			/*
			 * No need for nested expansion or anything, as we're
			 * the only one who sets these things and we sure don't
			 * but nested invocations in them...
			 */
			val = (char *)Buf_GetAll(v->val, (int *)NULL);
			
			if (str[3] == 'D') {
			    val = VarModify(val, VarHead, (ClientData)0);
			} else {
			    val = VarModify(val, VarTail, (ClientData)0);
			}
			/*
			 * Resulting string is dynamically allocated, so
			 * tell caller to free it.
			 */
			*freePtr = TRUE;
			*lengthPtr = tstr-start+1;
			*tstr = endc;
			return(val);
		    }
		    break;
		}
	    }
	}
			    
	if (v == (Var *)NIL) {
	    if ((((tstr-str) == 3) ||
		 ((((tstr-str) == 4) && (str[3] == 'F' ||
					 str[3] == 'D')))) &&
		((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)))
	    {
		/*
		 * If substituting a local variable in a non-local context,
		 * assume it's for dynamic source stuff. We have to handle
		 * this specially and return the longhand for the variable
		 * with the dollar sign escaped so it makes it back to the
		 * caller. Only four of the local variables are treated
		 * specially as they are the only four that will be set
		 * when dynamic sources are expanded.
		 */
		switch (str[2]) {
		    case '@':
		    case '%':
		    case '*':
		    case '!':
			dynamic = TRUE;
			break;
		}
	    } else if (((tstr-str) > 4) && (str[2] == '.') &&
D 14
		       isupper(str[3]) &&
E 14
I 14
		       isupper((unsigned char) str[3]) &&
E 14
		       ((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)))
	    {
		int	len;
		
		len = (tstr-str) - 3;
		if ((strncmp(str+2, ".TARGET", len) == 0) ||
		    (strncmp(str+2, ".ARCHIVE", len) == 0) ||
		    (strncmp(str+2, ".PREFIX", len) == 0) ||
		    (strncmp(str+2, ".MEMBER", len) == 0))
		{
		    dynamic = TRUE;
		}
	    }
	    
	    if (!haveModifier) {
		/*
		 * No modifiers -- have specification length so we can return
		 * now.
		 */
		*lengthPtr = tstr - start + 1;
		*tstr = endc;
		if (dynamic) {
D 6
		    str = malloc(*lengthPtr + 1);
E 6
I 6
		    str = emalloc(*lengthPtr + 1);
E 6
		    strncpy(str, start, *lengthPtr);
		    str[*lengthPtr] = '\0';
		    *freePtr = TRUE;
		    return(str);
		} else {
		    return (err ? var_Error : varNoError);
		}
	    } else {
		/*
		 * Still need to get to the end of the variable specification,
		 * so kludge up a Var structure for the modifications
		 */
D 6
		v = (Var *) malloc(sizeof(Var));
E 6
I 6
		v = (Var *) emalloc(sizeof(Var));
E 6
		v->name = &str[1];
		v->val = Buf_Init(1);
		v->flags = VAR_JUNK;
	    }
	}
    }

    if (v->flags & VAR_IN_USE) {
	Fatal("Variable %s is recursive.", v->name);
	/*NOTREACHED*/
    } else {
	v->flags |= VAR_IN_USE;
    }
    /*
     * Before doing any modification, we have to make sure the value
     * has been fully expanded. If it looks like recursion might be
     * necessary (there's a dollar sign somewhere in the variable's value)
     * we just call Var_Subst to do any other substitutions that are
     * necessary. Note that the value returned by Var_Subst will have
     * been dynamically-allocated, so it will need freeing when we
     * return.
     */
    str = (char *)Buf_GetAll(v->val, (int *)NULL);
D 9
    if (index (str, '$') != (char *)NULL) {
	str = Var_Subst(str, ctxt, err);
E 9
I 9
    if (strchr (str, '$') != (char *)NULL) {
	str = Var_Subst(NULL, str, ctxt, err);
E 9
	*freePtr = TRUE;
    }
    
    v->flags &= ~VAR_IN_USE;
    
    /*
     * Now we need to apply any modifiers the user wants applied.
     * These are:
     *  	  :M<pattern>	words which match the given <pattern>.
     *  	  	    	<pattern> is of the standard file
     *  	  	    	wildcarding form.
     *  	  :S<d><pat1><d><pat2><d>[g]
     *  	  	    	Substitute <pat2> for <pat1> in the value
     *  	  :H	    	Substitute the head of each word
     *  	  :T	    	Substitute the tail of each word
     *  	  :E	    	Substitute the extension (minus '.') of
     *  	  	    	each word
     *  	  :R	    	Substitute the root of each word
     *  	  	    	(pathname minus the suffix).
     *	    	  :lhs=rhs  	Like :S, but the rhs goes to the end of
     *	    	    	    	the invocation.
     */
    if ((str != (char *)NULL) && haveModifier) {
	/*
	 * Skip initial colon while putting it back.
	 */
	*tstr++ = ':';
	while (*tstr != endc) {
	    char	*newStr;    /* New value to return */
	    char	termc;	    /* Character which terminated scan */
	    
	    if (DEBUG(VAR)) {
		printf("Applying :%c to \"%s\"\n", *tstr, str);
	    }
	    switch (*tstr) {
		case 'N':
		case 'M':
		{
		    char    *pattern;
		    char    *cp2;
		    Boolean copy;

		    copy = FALSE;
		    for (cp = tstr + 1;
			 *cp != '\0' && *cp != ':' && *cp != endc;
			 cp++)
		    {
			if (*cp == '\\' && (cp[1] == ':' || cp[1] == endc)){
			    copy = TRUE;
			    cp++;
			}
		    }
		    termc = *cp;
		    *cp = '\0';
		    if (copy) {
			/*
			 * Need to compress the \:'s out of the pattern, so
			 * allocate enough room to hold the uncompressed
			 * pattern (note that cp started at tstr+1, so
			 * cp - tstr takes the null byte into account) and
			 * compress the pattern into the space.
			 */
D 6
			pattern = malloc(cp - tstr);
E 6
I 6
			pattern = emalloc(cp - tstr);
E 6
			for (cp2 = pattern, cp = tstr + 1;
			     *cp != '\0';
			     cp++, cp2++)
			{
			    if ((*cp == '\\') &&
				(cp[1] == ':' || cp[1] == endc)) {
				    cp++;
			    }
			    *cp2 = *cp;
			}
			*cp2 = '\0';
		    } else {
			pattern = &tstr[1];
		    }
		    if (*tstr == 'M' || *tstr == 'm') {
			newStr = VarModify(str, VarMatch, (ClientData)pattern);
		    } else {
			newStr = VarModify(str, VarNoMatch,
					   (ClientData)pattern);
		    }
		    if (copy) {
			free(pattern);
		    }
		    break;
		}
		case 'S':
		{
		    VarPattern 	    pattern;
		    register char   delim;
		    Buffer  	    buf;    	/* Buffer for patterns */
D 9
		    register char   *cp2;
		    int	    	    lefts;
E 9

		    pattern.flags = 0;
		    delim = tstr[1];
		    tstr += 2;
		    /*
		     * If pattern begins with '^', it is anchored to the
		     * start of the word -- skip over it and flag pattern.
		     */
		    if (*tstr == '^') {
			pattern.flags |= VAR_MATCH_START;
			tstr += 1;
		    }

		    buf = Buf_Init(0);
		    
		    /*
		     * Pass through the lhs looking for 1) escaped delimiters,
		     * '$'s and backslashes (place the escaped character in
		     * uninterpreted) and 2) unescaped $'s that aren't before
		     * the delimiter (expand the variable substitution).
		     * The result is left in the Buffer buf.
		     */
		    for (cp = tstr; *cp != '\0' && *cp != delim; cp++) {
			if ((*cp == '\\') &&
			    ((cp[1] == delim) ||
			     (cp[1] == '$') ||
			     (cp[1] == '\\')))
			{
			    Buf_AddByte(buf, (Byte)cp[1]);
			    cp++;
			} else if (*cp == '$') {
			    if (cp[1] != delim) {
				/*
				 * If unescaped dollar sign not before the
				 * delimiter, assume it's a variable
				 * substitution and recurse.
				 */
				char	    *cp2;
				int	    len;
				Boolean	    freeIt;
				
				cp2 = Var_Parse(cp, ctxt, err, &len, &freeIt);
				Buf_AddBytes(buf, strlen(cp2), (Byte *)cp2);
				if (freeIt) {
				    free(cp2);
				}
				cp += len - 1;
			    } else {
				/*
				 * Unescaped $ at end of pattern => anchor
				 * pattern at end.
				 */
				pattern.flags |= VAR_MATCH_END;
			    }
			} else {
			    Buf_AddByte(buf, (Byte)*cp);
			}
		    }

		    Buf_AddByte(buf, (Byte)'\0');
		    
		    /*
		     * If lhs didn't end with the delimiter, complain and
		     * return NULL
		     */
		    if (*cp != delim) {
			*lengthPtr = cp - start + 1;
			if (*freePtr) {
			    free(str);
			}
			Buf_Destroy(buf, TRUE);
			Error("Unclosed substitution for %s (%c missing)",
			      v->name, delim);
			return (var_Error);
		    }

		    /*
		     * Fetch pattern and destroy buffer, but preserve the data
		     * in it, since that's our lhs. Note that Buf_GetAll
		     * will return the actual number of bytes, which includes
		     * the null byte, so we have to decrement the length by
		     * one.
		     */
		    pattern.lhs = (char *)Buf_GetAll(buf, &pattern.leftLen);
		    pattern.leftLen--;
		    Buf_Destroy(buf, FALSE);

		    /*
		     * Now comes the replacement string. Three things need to
		     * be done here: 1) need to compress escaped delimiters and
		     * ampersands and 2) need to replace unescaped ampersands
		     * with the l.h.s. (since this isn't regexp, we can do
		     * it right here) and 3) expand any variable substitutions.
		     */
		    buf = Buf_Init(0);
		    
		    tstr = cp + 1;
		    for (cp = tstr; *cp != '\0' && *cp != delim; cp++) {
			if ((*cp == '\\') &&
			    ((cp[1] == delim) ||
			     (cp[1] == '&') ||
			     (cp[1] == '\\') ||
			     (cp[1] == '$')))
			{
			    Buf_AddByte(buf, (Byte)cp[1]);
			    cp++;
			} else if ((*cp == '$') && (cp[1] != delim)) {
			    char    *cp2;
			    int	    len;
			    Boolean freeIt;

			    cp2 = Var_Parse(cp, ctxt, err, &len, &freeIt);
			    Buf_AddBytes(buf, strlen(cp2), (Byte *)cp2);
			    cp += len - 1;
			    if (freeIt) {
				free(cp2);
			    }
			} else if (*cp == '&') {
			    Buf_AddBytes(buf, pattern.leftLen,
					 (Byte *)pattern.lhs);
			} else {
			    Buf_AddByte(buf, (Byte)*cp);
			}
		    }

		    Buf_AddByte(buf, (Byte)'\0');
		    
		    /*
		     * If didn't end in delimiter character, complain
		     */
		    if (*cp != delim) {
			*lengthPtr = cp - start + 1;
			if (*freePtr) {
			    free(str);
			}
			Buf_Destroy(buf, TRUE);
			Error("Unclosed substitution for %s (%c missing)",
			      v->name, delim);
			return (var_Error);
		    }

		    pattern.rhs = (char *)Buf_GetAll(buf, &pattern.rightLen);
		    pattern.rightLen--;
		    Buf_Destroy(buf, FALSE);

		    /*
		     * Check for global substitution. If 'g' after the final
		     * delimiter, substitution is global and is marked that
		     * way.
		     */
		    cp++;
		    if (*cp == 'g') {
			pattern.flags |= VAR_SUB_GLOBAL;
			cp++;
		    }

		    termc = *cp;
		    newStr = VarModify(str, VarSubstitute,
				       (ClientData)&pattern);
		    /*
		     * Free the two strings.
		     */
		    free(pattern.lhs);
		    free(pattern.rhs);
		    break;
		}
		case 'T':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify (str, VarTail, (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    /*FALLTHRU*/
		case 'H':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify (str, VarHead, (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    /*FALLTHRU*/
		case 'E':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify (str, VarSuffix, (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    /*FALLTHRU*/
		case 'R':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify (str, VarRoot, (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    /*FALLTHRU*/
		default: {
		    /*
		     * This can either be a bogus modifier or a System-V
		     * substitution command.
		     */
		    VarPattern      pattern;
		    Boolean         eqFound;
		    
		    pattern.flags = 0;
		    eqFound = FALSE;
		    /*
		     * First we make a pass through the string trying
		     * to verify it is a SYSV-make-style translation:
		     * it must be: <string1>=<string2>)
		     */
D 14
		    for (cp = tstr; *cp != '\0' && *cp != endc; cp++) {
E 14
I 14
		    cp = tstr;
		    cnt = 1;
		    while (*cp != '\0' && cnt) {
E 14
			if (*cp == '=') {
			    eqFound = TRUE;
			    /* continue looking for endc */
			}
I 14
			else if (*cp == endc)
			    cnt--;
			else if (*cp == startc)
			    cnt++;
			if (cnt)
			    cp++;
E 14
		    }
		    if (*cp == endc && eqFound) {
			
			/*
			 * Now we break this sucker into the lhs and
			 * rhs. We must null terminate them of course.
			 */
D 9
			for (cp = tstr; *cp != '='; cp++) {
			    ;
			}
E 9
I 9
			for (cp = tstr; *cp != '='; cp++)
			    continue;
E 9
			pattern.lhs = tstr;
			pattern.leftLen = cp - tstr;
			*cp++ = '\0';
			
			pattern.rhs = cp;
D 14
			while (*cp != endc) {
			    cp++;
E 14
I 14
			cnt = 1;
			while (cnt) {
			    if (*cp == endc)
				cnt--;
			    else if (*cp == startc)
				cnt++;
			    if (cnt)
				cp++;
E 14
			}
			pattern.rightLen = cp - pattern.rhs;
			*cp = '\0';
			
			/*
			 * SYSV modifications happen through the whole
			 * string. Note the pattern is anchored at the end.
			 */
D 13
			pattern.flags |= VAR_SUB_GLOBAL|VAR_MATCH_END;

			newStr = VarModify(str, VarSubstitute,
E 13
I 13
			newStr = VarModify(str, VarSYSVMatch,
E 13
					   (ClientData)&pattern);

			/*
			 * Restore the nulled characters
			 */
			pattern.lhs[pattern.leftLen] = '=';
			pattern.rhs[pattern.rightLen] = endc;
			termc = endc;
		    } else {
			Error ("Unknown modifier '%c'\n", *tstr);
			for (cp = tstr+1;
			     *cp != ':' && *cp != endc && *cp != '\0';
D 9
			     cp++) {
				 ;
			}
E 9
I 9
			     cp++) 
				 continue;
E 9
			termc = *cp;
			newStr = var_Error;
		    }
		}
	    }
	    if (DEBUG(VAR)) {
		printf("Result is \"%s\"\n", newStr);
	    }
	    
	    if (*freePtr) {
		free (str);
	    }
	    str = newStr;
	    if (str != var_Error) {
		*freePtr = TRUE;
	    } else {
		*freePtr = FALSE;
	    }
	    if (termc == '\0') {
		Error("Unclosed variable specification for %s", v->name);
	    } else if (termc == ':') {
		*cp++ = termc;
	    } else {
		*cp = termc;
	    }
	    tstr = cp;
	}
	*lengthPtr = tstr - start + 1;
    } else {
	*lengthPtr = tstr - start + 1;
	*tstr = endc;
    }
    
    if (v->flags & VAR_FROM_ENV) {
	Boolean	  destroy = FALSE;
	
	if (str != (char *)Buf_GetAll(v->val, (int *)NULL)) {
	    destroy = TRUE;
	} else {
	    /*
	     * Returning the value unmodified, so tell the caller to free
	     * the thing.
	     */
	    *freePtr = TRUE;
	}
	Buf_Destroy(v->val, destroy);
	free((Address)v);
    } else if (v->flags & VAR_JUNK) {
	/*
	 * Perform any free'ing needed and set *freePtr to FALSE so the caller
	 * doesn't try to free a static pointer.
	 */
	if (*freePtr) {
	    free(str);
	}
	*freePtr = FALSE;
I 14
	Buf_Destroy(v->val, TRUE);
E 14
	free((Address)v);
	if (dynamic) {
D 6
	    str = malloc(*lengthPtr + 1);
E 6
I 6
	    str = emalloc(*lengthPtr + 1);
E 6
	    strncpy(str, start, *lengthPtr);
	    str[*lengthPtr] = '\0';
	    *freePtr = TRUE;
	} else {
	    str = var_Error;
	}
    }
    return (str);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_Subst  --
 *	Substitute for all variables in the given string in the given context
 *	If undefErr is TRUE, Parse_Error will be called when an undefined
 *	variable is encountered.
 *
 * Results:
 *	The resulting string.
 *
 * Side Effects:
 *	None. The old string must be freed by the caller
 *-----------------------------------------------------------------------
 */
char *
D 9
Var_Subst (str, ctxt, undefErr)
    register char *str;	    	    /* the string in which to substitute */
E 9
I 9
Var_Subst (var, str, ctxt, undefErr)
    char	  *var;		    /* Named variable || NULL for all */
    char 	  *str;	    	    /* the string in which to substitute */
E 9
    GNode         *ctxt;	    /* the context wherein to find variables */
    Boolean 	  undefErr; 	    /* TRUE if undefineds are an error */
{
    Buffer  	  buf;	    	    /* Buffer for forming things */
    char    	  *val;		    /* Value to substitute for a variable */
    int	    	  length;   	    /* Length of the variable invocation */
    Boolean 	  doFree;   	    /* Set true if val should be freed */
    static Boolean errorReported;   /* Set true if an error has already
				     * been reported to prevent a plethora
				     * of messages when recursing */

D 9
    buf = Buf_Init (BSIZE);
E 9
I 9
    buf = Buf_Init (MAKE_BSIZE);
E 9
    errorReported = FALSE;

    while (*str) {
D 9
	if ((*str == '$') && (str[1] == '$')) {
E 9
I 9
	if (var == NULL && (*str == '$') && (str[1] == '$')) {
E 9
	    /*
	     * A dollar sign may be escaped either with another dollar sign.
	     * In such a case, we skip over the escape character and store the
	     * dollar sign into the buffer directly.
	     */
	    str++;
	    Buf_AddByte(buf, (Byte)*str);
	    str++;
	} else if (*str != '$') {
	    /*
	     * Skip as many characters as possible -- either to the end of
	     * the string or to the next dollar sign (variable invocation).
	     */
	    char  *cp;

D 9
	    for (cp = str++; *str != '$' && *str != '\0'; str++) {
		;
	    }
E 9
I 9
	    for (cp = str++; *str != '$' && *str != '\0'; str++)
		continue;
E 9
	    Buf_AddBytes(buf, str - cp, (Byte *)cp);
	} else {
I 9
	    if (var != NULL) {
		int expand;
		for (;;) {
		    if (str[1] != '(' && str[1] != '{') {
			if (str[1] != *var) {
			    Buf_AddBytes(buf, 2, (Byte *) str);
			    str += 2;
			    expand = FALSE;
			}
			else
			    expand = TRUE;
			break;
		    }
		    else {
			char *p;

			/*
			 * Scan up to the end of the variable name.
			 */
			for (p = &str[2]; *p && 
			     *p != ':' && *p != ')' && *p != '}'; p++)
			    if (*p == '$') 
				break;
			/*
			 * A variable inside the variable. We cannot expand
			 * the external variable yet, so we try again with
			 * the nested one
			 */
			if (*p == '$') {
			    Buf_AddBytes(buf, p - str, (Byte *) str);
			    str = p;
			    continue;
			}
				
			if (strncmp(var, str + 2, p - str - 2) != 0 || 
			    var[p - str - 2] != '\0') {
			    /*
			     * Not the variable we want to expand, scan
			     * until the next variable
			     */
			    for (;*p != '$' && *p != '\0'; p++) 
				continue;
			    Buf_AddBytes(buf, p - str, (Byte *) str);
			    str = p;
			    expand = FALSE;
			}
			else
			    expand = TRUE;
			break;
		    }
		}
		if (!expand)
		    continue;
	    }
			
E 9
	    val = Var_Parse (str, ctxt, undefErr, &length, &doFree);

	    /*
	     * When we come down here, val should either point to the
	     * value of this variable, suitably modified, or be NULL.
	     * Length should be the total length of the potential
	     * variable invocation (from $ to end character...)
	     */
	    if (val == var_Error || val == varNoError) {
		/*
		 * If performing old-time variable substitution, skip over
		 * the variable and continue with the substitution. Otherwise,
		 * store the dollar sign and advance str so we continue with
		 * the string...
		 */
		if (oldVars) {
D 4
#ifndef DEF_OLD_VARS
		    if (!sysVmake && !amMake && undefErr && !errorReported) {
			Parse_Error (PARSE_WARNING,
				     "Undefined variable \"%.*s\"",length,str);
		    }
#endif
E 4
		    str += length;
		} else if (undefErr) {
		    /*
		     * If variable is undefined, complain and skip the
		     * variable. The complaint will stop us from doing anything
		     * when the file is parsed.
		     */
		    if (!errorReported) {
			Parse_Error (PARSE_FATAL,
				     "Undefined variable \"%.*s\"",length,str);
		    }
		    str += length;
		    errorReported = TRUE;
		} else {
		    Buf_AddByte (buf, (Byte)*str);
		    str += 1;
		}
	    } else {
		/*
		 * We've now got a variable structure to store in. But first,
		 * advance the string pointer.
		 */
		str += length;
		
		/*
		 * Copy all the characters from the variable value straight
		 * into the new string.
		 */
		Buf_AddBytes (buf, strlen (val), (Byte *)val);
		if (doFree) {
		    free ((Address)val);
		}
	    }
	}
    }
	
    Buf_AddByte (buf, '\0');
    str = (char *)Buf_GetAll (buf, (int *)NULL);
    Buf_Destroy (buf, FALSE);
    return (str);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_GetTail --
 *	Return the tail from each of a list of words. Used to set the
 *	System V local variables.
 *
 * Results:
 *	The resulting string.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
char *
Var_GetTail(file)
    char    	*file;	    /* Filename to modify */
{
    return(VarModify(file, VarTail, (ClientData)0));
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_GetHead --
 *	Find the leading components of a (list of) filename(s).
 *	XXX: VarHead does not replace foo by ., as (sun) System V make
 *	does.
 *
 * Results:
 *	The leading components.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
char *
Var_GetHead(file)
    char    	*file;	    /* Filename to manipulate */
{
    return(VarModify(file, VarHead, (ClientData)0));
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_Init --
 *	Initialize the module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The VAR_CMD and VAR_GLOBAL contexts are created 
 *-----------------------------------------------------------------------
 */
void
Var_Init ()
{
    VAR_GLOBAL = Targ_NewGN ("Global");
    VAR_CMD = Targ_NewGN ("Command");
I 14
    allVars = Lst_Init(FALSE);
E 14

}
D 3

E 3
I 3

I 14

void
Var_End ()
{
    Lst_Destroy(allVars, VarDelete);
}
	

E 14
E 3
/****************** PRINT DEBUGGING INFO *****************/
D 9
static
E 9
I 9
static int
E 9
D 14
VarPrintVar (v)
    Var            *v;
E 14
I 14
VarPrintVar (vp, dummy)
    ClientData vp;
    ClientData dummy;
E 14
{
I 14
    Var    *v = (Var *) vp;
E 14
D 12
    printf ("%-16s = %s\n", v->name, Buf_GetAll(v->val, (int *)NULL));
E 12
I 12
    printf ("%-16s = %s\n", v->name, (char *) Buf_GetAll(v->val, (int *)NULL));
E 12
D 14
    return (0);
E 14
I 14
    return (dummy ? 0 : 0);
E 14
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Var_Dump --
 *	print all variables in a context
 *-----------------------------------------------------------------------
 */
I 9
void
E 9
Var_Dump (ctxt)
    GNode          *ctxt;
{
D 14
    Lst_ForEach (ctxt->context, VarPrintVar);
E 14
I 14
    Lst_ForEach (ctxt->context, VarPrintVar, (ClientData) 0);
E 14
}
E 1
