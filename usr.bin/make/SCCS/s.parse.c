h62150
s 00045/00002/02590
d D 8.6 95/06/13 15:40:33 christos 28 27
c - posix compliance: Don't create .[A-Z]* targets 
c - support for .PHONY targets
e
s 00129/00077/02463
d D 8.5 95/04/28 17:08:21 christos 27 26
c Updated to the latest version from the NetBSD source
e
s 00001/00001/02539
d D 8.4 94/05/23 15:46:55 christos 26 25
c fix for VAR='name \# foo' [# was parsed as a comment]
e
s 00025/00007/02515
d D 8.3 94/03/19 15:56:07 christos 25 24
c avoid clobbered variable warnings, fix varargs functions
e
s 00003/00001/02519
d D 8.2 94/03/19 10:42:10 bostic 24 23
c fix out of order execution of :: rules
c From: Christos Zoulas <christos@deshaw.com>
e
s 00002/00002/02518
d D 8.1 93/06/06 15:16:43 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/02519
d D 5.22 93/06/02 20:25:59 bostic 22 21
c from Christos, use `ungetc' routine ParseUnreadc
e
s 00003/00000/02517
d D 5.21 93/06/02 12:45:54 bostic 21 20
c Christos removed the comment clause in ParseReadLine
c this breaks for "# foo:; bar" lines in the Makefile
e
s 00031/00003/02486
d D 5.20 93/05/28 14:24:18 bostic 20 19
c The bug was introduced when the special character changed from '#'
c to '.'.  There is a check that says that lines that start with a '.' are
c not dependency lines; From: "Christos S. Zoulas" <christos>
e
s 00432/00129/02057
d D 5.19 93/05/24 14:45:53 bostic 19 18
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00006/00004/02180
d D 5.18 91/02/19 11:07:50 bostic 18 17
c don't call fclose unless the file was opened
e
s 00001/00001/02183
d D 5.17 91/01/10 17:25:25 bostic 17 16
c get rid of stupid error messages
e
s 00004/00001/02180
d D 5.16 90/06/29 11:11:58 bostic 16 15
c fix "(echo -n ${LIBPC}:; nm -go ${LIBPC})"
e
s 00001/00001/02180
d D 5.15 90/06/28 16:49:16 bostic 15 14
c change to make '.c.o:; rule' work right, i.e. the ';' should be treated
c as a newline.  I'm not positive this change has no nasty ramifications.
e
s 00001/00011/02180
d D 5.14 90/06/01 17:09:21 bostic 14 13
c new copyright notice
e
s 00002/00005/02189
d D 5.13 90/05/29 18:57:53 bostic 13 12
c fatal error on include without '"' or '<' delimiter
e
s 00003/00000/02191
d D 5.12 90/04/22 15:58:53 bostic 12 11
c fix line "#comment: with both colon; and semi-colon"
e
s 00001/00001/02190
d D 5.11 90/03/19 16:24:06 bostic 11 10
c rename DONTCARE as OPTIONAL
e
s 00001/00003/02190
d D 5.10 90/03/19 11:19:43 bostic 10 9
c delete -W (noWarnings) flag
e
s 00002/00002/02191
d D 5.9 90/03/19 09:58:41 bostic 9 8
c replace malloc with emalloc; Str_Concat -> str_concat
e
s 00004/00004/02189
d D 5.8 90/03/17 14:27:42 bostic 8 7
c add pathnames.h, redefining some paths
e
s 00009/00015/02184
d D 5.7 90/03/12 21:28:16 bostic 7 6
c fix varargs stuff; ignore second and rest of multiple command lines
e
s 00024/00034/02175
d D 5.6 90/03/12 12:20:01 bostic 6 5
c rework to always be "make".  Deleted -M, -B, -C, -v.  Partial deletion
c of .NULL.  Never remove leading components in file search.  # is always a
c comment.  Print usage line, not message.  Make vararg'd routines right.
e
s 00001/00052/02208
d D 5.5 90/03/12 10:42:38 bostic 5 4
c remove rmt.c module, most of remote support, including .EXPORT,
c .EXPORTSAME, .NOEXPORT, -X and -x
e
s 00006/00010/02254
d D 5.4 90/03/12 09:37:26 bostic 4 3
c wire in '.' as include/define intro character
e
s 00024/00024/02240
d D 5.3 90/03/12 08:59:42 bostic 3 2
c Str_New -> strdup
e
s 00026/00015/02238
d D 5.2 90/03/11 15:39:13 bostic 2 1
c add Berkeley specific copyright notice
e
s 02253/00000/00000
d D 5.1 90/03/11 15:27:45 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
D 23
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 23
I 23
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
D 14
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/*-
 * parse.c --
 *	Functions to parse a makefile.
 *
 *	One function, Parse_Init, must be called before any functions
 *	in this module are used. After that, the function Parse_File is the
 *	main entry point and controls most of the other functions in this
 *	module.
 *
 *	Most important structures are kept in Lsts. Directories for
 *	the #include "..." function are kept in the 'parseIncPath' Lst, while
 *	those for the #include <...> are kept in the 'sysIncPath' Lst. The
 *	targets currently being defined are kept in the 'targets' Lst.
 *
 *	The variables 'fname' and 'lineno' are used to track the name
 *	of the current file and the line number in that file so that error
 *	messages can be more meaningful.
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
 *	Parse_Init	    	    Initialization function which must be
 *	    	  	    	    called before anything else in this module
 *	    	  	    	    is used.
 *
I 27
 *	Parse_End		    Cleanup the module
 *
E 27
 *	Parse_File	    	    Function used to parse a makefile. It must
 *	    	  	    	    be given the name of the file, which should
 *	    	  	    	    already have been opened, and a function
 *	    	  	    	    to call to read a character from the file.
 *
 *	Parse_IsVar	    	    Returns TRUE if the given line is a
 *	    	  	    	    variable assignment. Used by MainParseArgs
 *	    	  	    	    to determine if an argument is a target
 *	    	  	    	    or a variable assignment. Used internally
 *	    	  	    	    for pretty much the same thing...
 *
 *	Parse_Error	    	    Function called when an error occurs in
 *	    	  	    	    parsing. Used by the variable and
 *	    	  	    	    conditional modules.
 *	Parse_MainName	    	    Returns a Lst of the main target to create.
 */
D 2
#ifndef lint
static char     *rcsid = "$Id: parse.c,v 1.75 89/11/14 13:42:56 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

I 19
#if __STDC__
#include <stdarg.h>
#else
E 19
D 6
#include    <stdio.h>
#include    <ctype.h>
#include    "make.h"
#include    "buf.h"
E 6
I 6
#include <varargs.h>
I 19
#endif
E 19
#include <stdio.h>
#include <ctype.h>
I 19
#include <errno.h>
#include <sys/wait.h>
E 19
#include "make.h"
I 19
#include "hash.h"
#include "dir.h"
#include "job.h"
E 19
#include "buf.h"
I 8
#include "pathnames.h"
E 8
E 6

/*
 * These values are returned by ParseEOF to tell Parse_File whether to
 * CONTINUE parsing, i.e. it had only reached the end of an include file,
 * or if it's DONE.
 */
#define	CONTINUE	1
#define	DONE		0
D 19
static int 	    ParseEOF();

E 19
static Lst     	    targets;	/* targets we're working on */
I 27
static Lst     	    targCmds;	/* command lines for targets */
E 27
static Boolean	    inLine;	/* true if currently in a dependency
				 * line or its commands */
I 19
typedef struct {
    char *str;
    char *ptr;
} PTR;
E 19

static char    	    *fname;	/* name of current file (for errors) */
static int          lineno;	/* line number in current file */
D 19
static FILE   	    *curFILE; 	/* current makefile */
E 19
I 19
static FILE   	    *curFILE = NULL; 	/* current makefile */
E 19

I 19
static PTR 	    *curPTR = NULL; 	/* current makefile */

E 19
static int	    fatals = 0;

static GNode	    *mainNode;	/* The main target to create. This is the
				 * first target on the first dependency
				 * line in the first makefile */
/*
 * Definitions for handling #include specifications
 */
typedef struct IFile {
    char           *fname;	    /* name of previous file */
    int             lineno;	    /* saved line number */
D 19
    FILE *       F;		    /* the open stream */
}              	  IFile;
E 19
I 19
    FILE *          F;		    /* the open stream */
    PTR *	    p;	    	    /* the char pointer */
} IFile;
E 19

static Lst      includes;  	/* stack of IFiles generated by
				 * #includes */
Lst         	parseIncPath;	/* list of directories for "..." includes */
Lst         	sysIncPath;	/* list of directories for <...> includes */

/*-
D 5
 * anyExport is used to trace if any target will need exportation. If none
 * does, then any .EXPORT target can be ignored and the process needn't
 * be slowed down by trying to connect to some load-balancing system.
 */
static Boolean anyExport = FALSE;

/*-
E 5
 * specType contains the SPECial TYPE of the current target. It is
 * Not if the target is unspecial. If it *is* special, however, the children
 * are linked as children of the parent but not vice versa. This variable is
 * set in ParseDoDependency
 */
typedef enum {
    Begin,  	    /* .BEGIN */
    Default,	    /* .DEFAULT */
    End,    	    /* .END */
D 5
    Export, 	    /* .EXPORT */
E 5
    Ignore,	    /* .IGNORE */
    Includes,	    /* .INCLUDES */
    Interrupt,	    /* .INTERRUPT */
    Libs,	    /* .LIBS */
    MFlags,	    /* .MFLAGS or .MAKEFLAGS */
    Main,	    /* .MAIN and we don't have anything user-specified to
		     * make */
I 19
    NoExport,	    /* .NOEXPORT */
E 19
D 5
    NoExport,	    /* .NOEXPORT */
E 5
    Not,	    /* Not special */
    NotParallel,    /* .NOTPARALELL */
    Null,   	    /* .NULL */
    Order,  	    /* .ORDER */
D 19
    Path,	    /* .PATH */
E 19
I 19
    ExPath,	    /* .PATH */
E 19
    Precious,	    /* .PRECIOUS */
I 28
    Reserved,	    /* .RESERVED or .[A-Z]* */
E 28
D 19
    Shell,	    /* .SHELL */
E 19
I 19
    ExShell,	    /* .SHELL */
E 19
    Silent,	    /* .SILENT */
    SingleShell,    /* .SINGLESHELL */
    Suffixes,	    /* .SUFFIXES */
D 19
    Attribute,	    /* Generic attribute */
E 19
I 19
    Attribute	    /* Generic attribute */
E 19
} ParseSpecial;

D 19
ParseSpecial specType;
E 19
I 19
static ParseSpecial specType;
E 19

/*
 * Predecessor node for handling .ORDER. Initialized to NILGNODE when .ORDER
 * seen, then set to each successive source on the line.
 */
static GNode	*predecessor;

/*
 * The parseKeywords table is searched using binary search when deciding
 * if a target or source is special. The 'spec' field is the ParseSpecial
 * type of the keyword ("Not" if the keyword isn't special as a target) while
 * the 'op' field is the operator to apply to the list of targets if the
 * keyword is used as a source ("0" if the keyword isn't special as a source)
 */
static struct {
    char    	  *name;    	/* Name of keyword */
    ParseSpecial  spec;	    	/* Type when used as a target */
    int	    	  op;	    	/* Operator when used as a source */
} parseKeywords[] = {
I 28
#define DOT_BEGIN	0
E 28
{ ".BEGIN", 	  Begin,    	0 },
I 28
#define	DOT_DEFAULT	1
E 28
{ ".DEFAULT",	  Default,  	0 },
D 11
{ ".DONTCARE",	  Attribute,   	OP_DONTCARE },
E 11
I 11
D 28
{ ".OPTIONAL",	  Attribute,   	OP_OPTIONAL },
E 28
I 28
#define	DOT_END		2
E 28
E 11
{ ".END",   	  End,	    	0 },
I 28
#define	DOT_EXEC	3
E 28
{ ".EXEC",	  Attribute,   	OP_EXEC },
I 28
#define	DOT_IGNORE	4
E 28
D 5
{ ".EXPORT",	  Export,   	OP_EXPORT },
{ ".EXPORTSAME",  Attribute,	OP_EXPORTSAME },
E 5
{ ".IGNORE",	  Ignore,   	OP_IGNORE },
I 28
#define	DOT_INCLUDES	5
E 28
{ ".INCLUDES",	  Includes, 	0 },
I 28
#define	DOT_INTERRUPT	6
E 28
{ ".INTERRUPT",	  Interrupt,	0 },
I 28
#define	DOT_INVISIBLE	7
E 28
{ ".INVISIBLE",	  Attribute,   	OP_INVISIBLE },
I 28
#define	DOT_JOIN	8
E 28
{ ".JOIN",  	  Attribute,   	OP_JOIN },
I 28
#define	DOT_LIBS	9
E 28
{ ".LIBS",  	  Libs,	    	0 },
I 28
#define	DOT_MAIN	10
E 28
D 5
{ ".M68020",	  Attribute,	OP_M68020 },
E 5
{ ".MAIN",	  Main,		0 },
I 28
#define	DOT_MAKE	11
E 28
{ ".MAKE",  	  Attribute,   	OP_MAKE },
I 28
#define	DOT_MAKEFLAGS	12
E 28
{ ".MAKEFLAGS",	  MFlags,   	0 },
I 28
#define	DOT_MFLAGS	13
E 28
{ ".MFLAGS",	  MFlags,   	0 },
I 28
#define	DOT_NOTMAIN	14
E 28
D 5
{ ".NOEXPORT",	  NoExport,   	OP_NOEXPORT },
E 5
{ ".NOTMAIN",	  Attribute,   	OP_NOTMAIN },
I 28
#define	DOT_NOTPARALLEL	15
E 28
{ ".NOTPARALLEL", NotParallel,	0 },
I 28
#define	DOT_NULL	16
E 28
{ ".NULL",  	  Null,	    	0 },
I 28
#define	DOT_OPTIONAL	17
{ ".OPTIONAL",	  Attribute,   	OP_OPTIONAL },
#define	DOT_ORDER	18
E 28
{ ".ORDER", 	  Order,    	0 },
I 28
#define	DOT_PATH	19
E 28
D 19
{ ".PATH",	  Path,		0 },
E 19
I 19
{ ".PATH",	  ExPath,	0 },
I 28
#define	DOT_PHONY	20
{ ".PHONY",	  Attribute, 	OP_PHONY },
#define	DOT_PRECIOUS	21
E 28
E 19
{ ".PRECIOUS",	  Precious, 	OP_PRECIOUS },
I 28
#define	DOT_RECURSIVE	22
E 28
{ ".RECURSIVE",	  Attribute,	OP_MAKE },
I 28
#define	DOT_RESERVED	23
{ ".RESERVED",	  Reserved,	0 },
#define	DOT_SHELL	24
E 28
D 19
{ ".SHELL", 	  Shell,    	0 },
E 19
I 19
{ ".SHELL", 	  ExShell,    	0 },
I 28
#define	DOT_SILENT	25
E 28
E 19
{ ".SILENT",	  Silent,   	OP_SILENT },
I 28
#define	DOT_SINGLESHELL	26
E 28
{ ".SINGLESHELL", SingleShell,	0 },
I 28
#define	DOT_SUFFIXES	27
E 28
{ ".SUFFIXES",	  Suffixes, 	0 },
I 28
#define	DOT_USE		28
E 28
{ ".USE",   	  Attribute,   	OP_USE },
};
D 3

E 3
I 3

I 19
static int ParseFindKeyword __P((char *));
D 27
static int ParseLinkSrc __P((GNode *, GNode *));
static int ParseDoOp __P((GNode *, int));
E 27
I 27
static int ParseLinkSrc __P((ClientData, ClientData));
static int ParseDoOp __P((ClientData, ClientData));
E 27
static void ParseDoSrc __P((int, char *));
D 27
static int ParseFindMain __P((GNode *));
static int ParseAddDir __P((Lst, char *));
static int ParseClearPath __P((Lst));
E 27
I 27
static int ParseFindMain __P((ClientData, ClientData));
static int ParseAddDir __P((ClientData, ClientData));
static int ParseClearPath __P((ClientData, ClientData));
E 27
static void ParseDoDependency __P((char *));
D 27
static int ParseAddCmd __P((GNode *, char *));
E 27
I 27
static int ParseAddCmd __P((ClientData, ClientData));
E 27
static int ParseReadc __P((void));
I 20
static void ParseUnreadc __P((int));
E 20
D 27
static int ParseHasCommands __P((GNode *));
E 27
I 27
static void ParseHasCommands __P((ClientData));
E 27
static void ParseDoInclude __P((char *));
#ifdef SYSVINCLUDE
static void ParseTraditionalInclude __P((char *));
#endif
static int ParseEOF __P((int));
static char *ParseReadLine __P((void));
static char *ParseSkipLine __P((int));
static void ParseFinishLine __P((void));

E 19
E 3
/*-
 *----------------------------------------------------------------------
 * ParseFindKeyword --
 *	Look in the table of keywords for one matching the given string.
 *
 * Results:
 *	The index of the keyword, or -1 if it isn't there.
 *
 * Side Effects:
 *	None
 *----------------------------------------------------------------------
 */
static int
ParseFindKeyword (str)
    char	    *str;		/* String to find */
{
    register int    start,
		    end,
		    cur;
    register int    diff;
    
    start = 0;
    end = (sizeof(parseKeywords)/sizeof(parseKeywords[0])) - 1;

    do {
	cur = start + ((end - start) / 2);
	diff = strcmp (str, parseKeywords[cur].name);

	if (diff == 0) {
	    return (cur);
	} else if (diff < 0) {
	    end = cur - 1;
	} else {
	    start = cur + 1;
	}
    } while (start <= end);
D 28
    return (-1);
E 28
I 28

    cur = 0;
    for (++str; *str; str++)
	if (!isupper((unsigned char) *str))
		break;
    return *str ? -1 : DOT_RESERVED;
E 28
}
D 3

E 3
I 3

E 3
/*-
D 6
 *---------------------------------------------------------------------
E 6
 * Parse_Error  --
 *	Error message abort function for parsing. Prints out the context
 *	of the error (line number and file) as well as the message with
 *	two optional arguments.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	"fatals" is incremented if the level is PARSE_FATAL.
D 6
 *---------------------------------------------------------------------
E 6
 */
D 6
/* VARARGS1 */
E 6
I 6
/* VARARGS */
E 6
void
D 6
Parse_Error (type, fmt, arg1, arg2)
    int	    	  type;	/* Error type: PARSE_WARNING if just a warning,
			 * PARSE_FATAL if can't continue (after parsing) */
    char          *fmt;	/* printf format string */
    int     	  arg1;	/* First optional argument for the fmt string */
    int	    	  arg2;	/* Second optional argument for the fmt string */
E 6
I 6
D 19
Parse_Error(type, va_alist)
	int type;		/* Error type (PARSE_WARNING, PARSE_FATAL) */
E 19
I 19
#if __STDC__
D 27
Parse_Error(int type, const char *fmt, ...)
E 27
I 27
Parse_Error(int type, char *fmt, ...)
E 27
#else
D 25
Parse_Error(type, fmt, va_alist)
	int type;
	char *fmt;
E 25
I 25
Parse_Error(va_alist)
E 25
E 19
	va_dcl
I 19
#endif
E 19
E 6
{
D 6
    if ((type != PARSE_WARNING) || !noWarnings) {
	fprintf (stderr, "\"%s\", line %d: ", fname, lineno);
	if (type == PARSE_WARNING) {
	    fprintf (stderr, "Warning: ");
	}
	fprintf (stderr, fmt, arg1, arg2);
	putc ('\n', stderr);
E 6
I 6
	va_list ap;
D 19
	char *fmt;
E 6

E 19
I 19
#if __STDC__
	va_start(ap, fmt);
#else
I 25
	int type;		/* Error type (PARSE_WARNING, PARSE_FATAL) */
	char *fmt;

E 25
	va_start(ap);
I 25
	type = va_arg(ap, int);
	fmt = va_arg(ap, char *);
E 25
#endif
I 25

E 25
E 19
D 6
	if (type == PARSE_FATAL) {
	    fatals += 1;
	}
    }
E 6
I 6
D 10
	if (type == PARSE_WARNING && noWarnings)
		return;
E 10
	(void)fprintf(stderr, "\"%s\", line %d: ", fname, lineno);
	if (type == PARSE_WARNING)
D 10
		(void)fprintf(stderr, "Warning: ");
E 10
I 10
		(void)fprintf(stderr, "warning: ");
E 10
I 7
D 19
	va_start(ap);
E 7
	fmt = va_arg(ap, char *);
E 19
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);
	if (type == PARSE_FATAL)
		fatals += 1;
E 6
}
D 3

E 3
I 3

E 3
/*-
D 5
 *-----------------------------------------------------------------------
 * Parse_AnyExport --
 *	Return TRUE if any target was labeled for exportation.
 *
 * Results:
 *	TRUE or FALSE...
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
Boolean
Parse_AnyExport()
{
    return (anyExport);
}
D 3

E 3
I 3

E 3
/*-
E 5
 *---------------------------------------------------------------------
 * ParseLinkSrc  --
 *	Link the parent node to its new child. Used in a Lst_ForEach by
 *	ParseDoDependency. If the specType isn't 'Not', the parent
 *	isn't linked as a parent of the child.
 *
 * Results:
 *	Always = 0
 *
 * Side Effects:
 *	New elements are added to the parents list of cgn and the
 *	children list of cgn. the unmade field of pgn is updated
 *	to reflect the additional child.
 *---------------------------------------------------------------------
 */
static int
D 27
ParseLinkSrc (pgn, cgn)
    GNode          *pgn;	/* The parent node */
    GNode          *cgn;	/* The child node */
E 27
I 27
ParseLinkSrc (pgnp, cgnp)
    ClientData     pgnp;	/* The parent node */
    ClientData     cgnp;	/* The child node */
E 27
{
I 27
    GNode          *pgn = (GNode *) pgnp;
    GNode          *cgn = (GNode *) cgnp;
E 27
    if (Lst_Member (pgn->children, (ClientData)cgn) == NILLNODE) {
	(void)Lst_AtEnd (pgn->children, (ClientData)cgn);
	if (specType == Not) {
	    (void)Lst_AtEnd (cgn->parents, (ClientData)pgn);
	}
	pgn->unmade += 1;
    }
    return (0);
}
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * ParseDoOp  --
 *	Apply the parsed operator to the given target node. Used in a
 *	Lst_ForEach call by ParseDoDependency once all targets have
 *	been found and their operator parsed. If the previous and new
 *	operators are incompatible, a major error is taken.
 *
 * Results:
 *	Always 0
 *
 * Side Effects:
 *	The type field of the node is altered to reflect any new bits in
 *	the op.
 *---------------------------------------------------------------------
 */
static int
D 27
ParseDoOp (gn, op)
    GNode          *gn;		/* The node to which the operator is to be
E 27
I 27
ParseDoOp (gnp, opp)
    ClientData     gnp;		/* The node to which the operator is to be
E 27
				 * applied */
D 27
    int             op;		/* The operator to apply */
E 27
I 27
    ClientData     opp;		/* The operator to apply */
E 27
{
I 27
    GNode          *gn = (GNode *) gnp;
    int             op = *(int *) opp;
E 27
    /*
     * If the dependency mask of the operator and the node don't match and
     * the node has actually had an operator applied to it before, and
     * the operator actually has some dependency information in it, complain. 
     */
    if (((op & OP_OPMASK) != (gn->type & OP_OPMASK)) &&
	!OP_NOP(gn->type) && !OP_NOP(op))
    {
	Parse_Error (PARSE_FATAL, "Inconsistent operator for %s", gn->name);
	return (1);
    }

    if ((op == OP_DOUBLEDEP) && ((gn->type & OP_OPMASK) == OP_DOUBLEDEP)) {
	/*
	 * If the node was the object of a :: operator, we need to create a
	 * new instance of it for the children and commands on this dependency
	 * line. The new instance is placed on the 'cohorts' list of the
	 * initial one (note the initial one is not on its own cohorts list)
	 * and the new instance is linked to all parents of the initial
	 * instance.
	 */
	register GNode	*cohort;
	LstNode	    	ln;
			
	cohort = Targ_NewGN(gn->name);
	/*
	 * Duplicate links to parents so graph traversal is simple. Perhaps
	 * some type bits should be duplicated?
	 *
	 * Make the cohort invisible as well to avoid duplicating it into
	 * other variables. True, parents of this target won't tend to do
	 * anything with their local variables, but better safe than
	 * sorry.
	 */
	Lst_ForEach(gn->parents, ParseLinkSrc, (ClientData)cohort);
	cohort->type = OP_DOUBLEDEP|OP_INVISIBLE;
	(void)Lst_AtEnd(gn->cohorts, (ClientData)cohort);

	/*
	 * Replace the node in the targets list with the new copy
	 */
	ln = Lst_Member(targets, (ClientData)gn);
	Lst_Replace(ln, (ClientData)cohort);
	gn = cohort;
    }
    /*
     * We don't want to nuke any previous flags (whatever they were) so we
     * just OR the new operator into the old 
     */
    gn->type |= op;

    return (0);
}
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * ParseDoSrc  --
 *	Given the name of a source, figure out if it is an attribute
 *	and apply it to the targets if it is. Else decide if there is
 *	some attribute which should be applied *to* the source because
 *	of some special target and apply it if so. Otherwise, make the
 *	source be a child of the targets in the list 'targets'
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Operator bits may be added to the list of targets or to the source.
 *	The targets may have a new source added to their lists of children.
 *---------------------------------------------------------------------
 */
static void
ParseDoSrc (tOp, src)
    int		tOp;	/* operator (if any) from special targets */
    char	*src;	/* name of the source to handle */
{
    int		op;	/* operator (if any) from special source */
    GNode	*gn;

    op = 0;
    if (*src == '.' && isupper (src[1])) {
	int keywd = ParseFindKeyword(src);
	if (keywd != -1) {
	    op = parseKeywords[keywd].op;
	}
    }
    if (op != 0) {
D 27
	Lst_ForEach (targets, ParseDoOp, (ClientData)op);
E 27
I 27
	Lst_ForEach (targets, ParseDoOp, (ClientData)&op);
E 27
D 5
	if (op == OP_EXPORT) {
	    anyExport = TRUE;
	}
E 5
    } else if (specType == Main) {
	/*
	 * If we have noted the existence of a .MAIN, it means we need
	 * to add the sources of said target to the list of things
	 * to create. The string 'src' is likely to be free, so we
	 * must make a new copy of it. Note that this will only be
	 * invoked if the user didn't specify a target on the command
	 * line. This is to allow #ifmake's to succeed, or something...
	 */
D 3
	(void) Lst_AtEnd (create, (ClientData)Str_New(src));
E 3
I 3
	(void) Lst_AtEnd (create, (ClientData)strdup(src));
E 3
	/*
	 * Add the name to the .TARGETS variable as well, so the user cna
	 * employ that, if desired.
	 */
	Var_Append(".TARGETS", src, VAR_GLOBAL);
    } else if (specType == Order) {
	/*
	 * Create proper predecessor/successor links between the previous
	 * source and the current one.
	 */
	gn = Targ_FindNode(src, TARG_CREATE);
	if (predecessor != NILGNODE) {
	    (void)Lst_AtEnd(predecessor->successors, (ClientData)gn);
	    (void)Lst_AtEnd(gn->preds, (ClientData)predecessor);
	}
	/*
	 * The current source now becomes the predecessor for the next one.
	 */
	predecessor = gn;
    } else {
	/*
	 * If the source is not an attribute, we need to find/create
	 * a node for it. After that we can apply any operator to it
	 * from a special target or link it to its parents, as
	 * appropriate.
	 *
	 * In the case of a source that was the object of a :: operator,
	 * the attribute is applied to all of its instances (as kept in
	 * the 'cohorts' list of the node) or all the cohorts are linked
	 * to all the targets.
	 */
	gn = Targ_FindNode (src, TARG_CREATE);
	if (tOp) {
	    gn->type |= tOp;
	} else {
	    Lst_ForEach (targets, ParseLinkSrc, (ClientData)gn);
	}
	if ((gn->type & OP_OPMASK) == OP_DOUBLEDEP) {
	    register GNode  	*cohort;
	    register LstNode	ln;

	    for (ln=Lst_First(gn->cohorts); ln != NILLNODE; ln = Lst_Succ(ln)){
		cohort = (GNode *)Lst_Datum(ln);
		if (tOp) {
		    cohort->type |= tOp;
		} else {
		    Lst_ForEach(targets, ParseLinkSrc, (ClientData)cohort);
		}
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
 * ParseFindMain --
 *	Find a real target in the list and set it to be the main one.
 *	Called by ParseDoDependency when a main target hasn't been found
 *	yet.
 *
 * Results:
 *	0 if main not found yet, 1 if it is.
 *
 * Side Effects:
 *	mainNode is changed and Targ_SetMain is called.
 *
 *-----------------------------------------------------------------------
 */
static int
D 27
ParseFindMain(gn)
    GNode   	  *gn;	    /* Node to examine */
E 27
I 27
ParseFindMain(gnp, dummy)
    ClientData	  gnp;	    /* Node to examine */
    ClientData    dummy;
E 27
{
I 27
    GNode   	  *gn = (GNode *) gnp;
E 27
    if ((gn->type & (OP_NOTMAIN|OP_USE|OP_EXEC|OP_TRANSFORM)) == 0) {
	mainNode = gn;
	Targ_SetMain(gn);
D 27
	return (1);
E 27
I 27
	return (dummy ? 1 : 1);
E 27
    } else {
D 27
	return (0);
E 27
I 27
	return (dummy ? 0 : 0);
E 27
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * ParseAddDir --
 *	Front-end for Dir_AddDir to make sure Lst_ForEach keeps going
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	See Dir_AddDir.
 *
 *-----------------------------------------------------------------------
 */
static int
ParseAddDir(path, name)
D 27
    Lst	    path;
    char    *name;
E 27
I 27
    ClientData	  path;
    ClientData    name;
E 27
{
D 27
    Dir_AddDir(path, name);
E 27
I 27
    Dir_AddDir((Lst) path, (char *) name);
E 27
    return(0);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * ParseClearPath --
 *	Front-end for Dir_ClearPath to make sure Lst_ForEach keeps going
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	See Dir_ClearPath
 *
 *-----------------------------------------------------------------------
 */
static int
D 27
ParseClearPath(path)
    Lst	    path;
E 27
I 27
ParseClearPath(path, dummy)
    ClientData path;
    ClientData dummy;
E 27
{
D 27
    Dir_ClearPath(path);
    return(0);
E 27
I 27
    Dir_ClearPath((Lst) path);
    return(dummy ? 0 : 0);
E 27
}
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * ParseDoDependency  --
 *	Parse the dependency line in line.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The nodes of the sources are linked as children to the nodes of the
 *	targets. Some nodes may be created.
 *
 *	We parse a dependency line by first extracting words from the line and
 * finding nodes in the list of all targets with that name. This is done
 * until a character is encountered which is an operator character. Currently
 * these are only ! and :. At this point the operator is parsed and the
 * pointer into the line advanced until the first source is encountered.
 * 	The parsed operator is applied to each node in the 'targets' list,
 * which is where the nodes found for the targets are kept, by means of
 * the ParseDoOp function.
 *	The sources are read in much the same way as the targets were except
 * that now they are expanded using the wildcarding scheme of the C-Shell
 * and all instances of the resulting words in the list of all targets
 * are found. Each of the resulting nodes is then linked to each of the
 * targets as one of its children.
 *	Certain targets are handled specially. These are the ones detailed
 * by the specType variable.
 *	The storing of transformation rules is also taken care of here.
 * A target is recognized as a transformation rule by calling
 * Suff_IsTransform. If it is a transformation rule, its node is gotten
 * from the suffix module via Suff_AddTransform rather than the standard
 * Targ_FindNode in the target module.
 *---------------------------------------------------------------------
 */
static void
ParseDoDependency (line)
    char           *line;	/* the line to parse */
{
D 27
    register char  *cp;		/* our current position */
    register GNode *gn;		/* a general purpose temporary node */
    register int    op;		/* the operator on the line */
E 27
I 27
    char  	   *cp;		/* our current position */
    GNode 	   *gn;		/* a general purpose temporary node */
    int             op;		/* the operator on the line */
E 27
    char            savec;	/* a place to save a character */
    Lst    	    paths;   	/* List of search paths to alter when parsing
				 * a list of .PATH targets */
    int	    	    tOp;    	/* operator from special target */
    Lst	    	    sources;	/* list of source names after expansion */
    Lst 	    curTargs;	/* list of target names to be found and added
				 * to the targets list */

    tOp = 0;

    specType = Not;
    paths = (Lst)NULL;

    curTargs = Lst_Init(FALSE);
    
    do {
	for (cp = line;
	     *cp && !isspace (*cp) &&
	     (*cp != '!') && (*cp != ':') && (*cp != '(');
	     cp++)
	{
	    if (*cp == '$') {
		/*
		 * Must be a dynamic source (would have been expanded
		 * otherwise), so call the Var module to parse the puppy
		 * so we can safely advance beyond it...There should be
		 * no errors in this, as they would have been discovered
		 * in the initial Var_Subst and we wouldn't be here.
		 */
		int 	length;
		Boolean	freeIt;
		char	*result;

		result=Var_Parse(cp, VAR_CMD, TRUE, &length, &freeIt);

		if (freeIt) {
		    free(result);
		}
		cp += length-1;
	    }
	    continue;
	}
	if (*cp == '(') {
	    /*
	     * Archives must be handled specially to make sure the OP_ARCHV
	     * flag is set in their 'type' field, for one thing, and because
	     * things like "archive(file1.o file2.o file3.o)" are permissible.
	     * Arch_ParseArchive will set 'line' to be the first non-blank
	     * after the archive-spec. It creates/finds nodes for the members
	     * and places them on the given list, returning SUCCESS if all
	     * went well and FAILURE if there was an error in the
	     * specification. On error, line should remain untouched.
	     */
	    if (Arch_ParseArchive (&line, targets, VAR_CMD) != SUCCESS) {
		Parse_Error (PARSE_FATAL,
			     "Error in archive specification: \"%s\"", line);
		return;
	    } else {
		continue;
	    }
	}
	savec = *cp;
	
	if (!*cp) {
	    /*
	     * Ending a dependency line without an operator is a Bozo
	     * no-no 
	     */
	    Parse_Error (PARSE_FATAL, "Need an operator");
	    return;
	}
	*cp = '\0';
	/*
	 * Have a word in line. See if it's a special target and set
	 * specType to match it.
	 */
	if (*line == '.' && isupper (line[1])) {
	    /*
	     * See if the target is a special target that must have it
	     * or its sources handled specially. 
	     */
	    int keywd = ParseFindKeyword(line);
	    if (keywd != -1) {
D 19
		if (specType == Path && parseKeywords[keywd].spec != Path) {
E 19
I 19
		if (specType == ExPath && parseKeywords[keywd].spec != ExPath) {
E 19
		    Parse_Error(PARSE_FATAL, "Mismatched special targets");
		    return;
		}
		
		specType = parseKeywords[keywd].spec;
		tOp = parseKeywords[keywd].op;

		/*
		 * Certain special targets have special semantics:
		 *	.PATH		Have to set the dirSearchPath
		 *			variable too
D 5
		 *	.EXPORT		Doesn't really apply the
		 *			.EXPORT operator to its
		 *			sources, so we reset tOp.
E 5
		 *	.MAIN		Its sources are only used if
		 *			nothing has been specified to
		 *			create.
		 *	.DEFAULT    	Need to create a node to hang
		 *			commands on, but we don't want
		 *			it in the graph, nor do we want
		 *			it to be the Main Target, so we
		 *			create it, set OP_NOTMAIN and
		 *			add it to the list, setting
		 *			DEFAULT to the new node for
		 *			later use. We claim the node is
		 *	    	    	A transformation rule to make
		 *	    	    	life easier later, when we'll
		 *	    	    	use Make_HandleUse to actually
		 *	    	    	apply the .DEFAULT commands.
		 *	.BEGIN
		 *	.END
		 *	.INTERRUPT  	Are not to be considered the
		 *			main target.
		 *  	.NOTPARALLEL	Make only one target at a time.
		 *  	.SINGLESHELL	Create a shell for each command.
		 *  	.ORDER	    	Must set initial predecessor to NIL
		 */
		switch (specType) {
D 19
		    case Path:
E 19
I 19
		    case ExPath:
E 19
			if (paths == NULL) {
			    paths = Lst_Init(FALSE);
			}
			(void)Lst_AtEnd(paths, (ClientData)dirSearchPath);
			break;
D 5
		    case Export:
			tOp = 0;
			break;
E 5
		    case Main:
			if (!Lst_IsEmpty(create)) {
			    specType = Not;
			}
			break;
		    case Begin:
		    case End:
		    case Interrupt:
			gn = Targ_FindNode(line, TARG_CREATE);
			gn->type |= OP_NOTMAIN;
			(void)Lst_AtEnd(targets, (ClientData)gn);
			break;
		    case Default:
			gn = Targ_NewGN(".DEFAULT");
			gn->type |= (OP_NOTMAIN|OP_TRANSFORM);
			(void)Lst_AtEnd(targets, (ClientData)gn);
			DEFAULT = gn;
			break;
		    case NotParallel:
		    {
			extern int  maxJobs;
			
			maxJobs = 1;
			break;
		    }
		    case SingleShell:
D 6
			backwards = 1;
E 6
I 6
D 19
			/* backwards = 1; */
E 19
I 19
			compatMake = 1;
E 19
E 6
			break;
		    case Order:
			predecessor = NILGNODE;
			break;
I 28
		    case Reserved:
			/*
			 * A posix reserved target that we don't know
			 * how to deal with.
			 */
			return;
E 28
I 19
		    default:
			break;
E 19
		}
	    } else if (strncmp (line, ".PATH", 5) == 0) {
		/*
		 * .PATH<suffix> has to be handled specially.
		 * Call on the suffix module to give us a path to
		 * modify.
		 */
		Lst 	path;
		
D 19
		specType = Path;
E 19
I 19
		specType = ExPath;
E 19
		path = Suff_GetPath (&line[5]);
		if (path == NILLST) {
		    Parse_Error (PARSE_FATAL,
				 "Suffix '%s' not defined (yet)",
				 &line[5]);
		    return;
		} else {
		    if (paths == (Lst)NULL) {
			paths = Lst_Init(FALSE);
		    }
		    (void)Lst_AtEnd(paths, (ClientData)path);
		}
	    }
	}
	
	/*
	 * Have word in line. Get or create its node and stick it at
	 * the end of the targets list 
	 */
	if ((specType == Not) && (*line != '\0')) {
	    if (Dir_HasWildcards(line)) {
		/*
		 * Targets are to be sought only in the current directory,
		 * so create an empty path for the thing. Note we need to
		 * use Dir_Destroy in the destruction of the path as the
		 * Dir module could have added a directory to the path...
		 */
		Lst	    emptyPath = Lst_Init(FALSE);
		
		Dir_Expand(line, emptyPath, curTargs);
		
		Lst_Destroy(emptyPath, Dir_Destroy);
	    } else {
		/*
		 * No wildcards, but we want to avoid code duplication,
		 * so create a list with the word on it.
		 */
		(void)Lst_AtEnd(curTargs, (ClientData)line);
	    }
	    
	    while(!Lst_IsEmpty(curTargs)) {
		char	*targName = (char *)Lst_DeQueue(curTargs);
		
		if (!Suff_IsTransform (targName)) {
		    gn = Targ_FindNode (targName, TARG_CREATE);
		} else {
		    gn = Suff_AddTransform (targName);
		}
		
		(void)Lst_AtEnd (targets, (ClientData)gn);
	    }
D 19
	} else if (specType == Path && *line != '.' && *line != '\0') {
E 19
I 19
	} else if (specType == ExPath && *line != '.' && *line != '\0') {
E 19
	    Parse_Error(PARSE_WARNING, "Extra target (%s) ignored", line);
	}
	
	*cp = savec;
	/*
	 * If it is a special type and not .PATH, it's the only target we
	 * allow on this line...
	 */
D 19
	if (specType != Not && specType != Path) {
E 19
I 19
	if (specType != Not && specType != ExPath) {
E 19
	    Boolean warn = FALSE;
	    
	    while ((*cp != '!') && (*cp != ':') && *cp) {
		if (*cp != ' ' && *cp != '\t') {
		    warn = TRUE;
		}
		cp++;
	    }
	    if (warn) {
		Parse_Error(PARSE_WARNING, "Extra target ignored");
	    }
	} else {
	    while (*cp && isspace (*cp)) {
		cp++;
	    }
	}
	line = cp;
    } while ((*line != '!') && (*line != ':') && *line);

    /*
     * Don't need the list of target names anymore...
     */
    Lst_Destroy(curTargs, NOFREE);

    if (!Lst_IsEmpty(targets)) {
	switch(specType) {
	    default:
		Parse_Error(PARSE_WARNING, "Special and mundane targets don't mix. Mundane ones ignored");
		break;
	    case Default:
	    case Begin:
	    case End:
	    case Interrupt:
		/*
		 * These four create nodes on which to hang commands, so
		 * targets shouldn't be empty...
		 */
	    case Not:
		/*
		 * Nothing special here -- targets can be empty if it wants.
		 */
		break;
	}
    }

    /*
     * Have now parsed all the target names. Must parse the operator next. The
     * result is left in  op .
     */
    if (*cp == '!') {
	op = OP_FORCE;
    } else if (*cp == ':') {
	if (cp[1] == ':') {
	    op = OP_DOUBLEDEP;
	    cp++;
	} else {
	    op = OP_DEPENDS;
	}
    } else {
	Parse_Error (PARSE_FATAL, "Missing dependency operator");
	return;
    }

    cp++;			/* Advance beyond operator */

D 27
    Lst_ForEach (targets, ParseDoOp, (ClientData)op);
E 27
I 27
    Lst_ForEach (targets, ParseDoOp, (ClientData)&op);
E 27

    /*
     * Get to the first source 
     */
    while (*cp && isspace (*cp)) {
	cp++;
    }
    line = cp;

    /*
     * Several special targets take different actions if present with no
     * sources:
     *	a .SUFFIXES line with no sources clears out all old suffixes
     *	a .PRECIOUS line makes all targets precious
     *	a .IGNORE line ignores errors for all targets
     *	a .SILENT line creates silence when making all targets
     *	a .PATH removes all directories from the search path(s).
D 5
     *	a .NOEXPORT turns off exportation for all jobs.
E 5
     */
    if (!*line) {
	switch (specType) {
	    case Suffixes:
		Suff_ClearSuffixes ();
		break;
	    case Precious:
		allPrecious = TRUE;
		break;
	    case Ignore:
		ignoreErrors = TRUE;
		break;
	    case Silent:
		beSilent = TRUE;
		break;
D 19
	    case Path:
E 19
I 19
	    case ExPath:
E 19
		Lst_ForEach(paths, ParseClearPath, (ClientData)NULL);
		break;
I 19
	    default:
		break;
E 19
D 5
	    case NoExport:
		noExport = TRUE;
		break;
E 5
	}
    } else if (specType == MFlags) {
	/*
	 * Call on functions in main.c to deal with these arguments and
	 * set the initial character to a null-character so the loop to
	 * get sources won't get anything
	 */
	Main_ParseArgLine (line);
	*line = '\0';
D 19
    } else if (specType == Shell) {
E 19
I 19
    } else if (specType == ExShell) {
E 19
	if (Job_ParseShell (line) != SUCCESS) {
	    Parse_Error (PARSE_FATAL, "improper shell specification");
	    return;
	}
	*line = '\0';
    } else if ((specType == NotParallel) || (specType == SingleShell)) {
	*line = '\0';
    }
    
    /*
     * NOW GO FOR THE SOURCES 
     */
D 19
    if ((specType == Suffixes) || (specType == Path) ||
E 19
I 19
    if ((specType == Suffixes) || (specType == ExPath) ||
E 19
	(specType == Includes) || (specType == Libs) ||
D 5
	(specType == Export)   || (specType == Null))
E 5
I 5
	(specType == Null))
E 5
    {
	while (*line) {
	    /*
	     * If the target was one that doesn't take files as its sources
	     * but takes something like suffixes, we take each
	     * space-separated word on the line as a something and deal
	     * with it accordingly.
	     *
	     * If the target was .SUFFIXES, we take each source as a
	     * suffix and add it to the list of suffixes maintained by the
	     * Suff module.
	     *
	     * If the target was a .PATH, we add the source as a directory
	     * to search on the search path.
	     *
	     * If it was .INCLUDES, the source is taken to be the suffix of
	     * files which will be #included and whose search path should
	     * be present in the .INCLUDES variable.
	     *
	     * If it was .LIBS, the source is taken to be the suffix of
	     * files which are considered libraries and whose search path
	     * should be present in the .LIBS variable.
	     *
D 5
	     * If it was .EXPORT, the source is the location of the export
	     * server and is passed to the Rmt module as such.
	     *
E 5
	     * If it was .NULL, the source is the suffix to use when a file
	     * has no valid suffix.
	     */
	    char  savec;
	    while (*cp && !isspace (*cp)) {
		cp++;
	    }
	    savec = *cp;
	    *cp = '\0';
	    switch (specType) {
		case Suffixes:
		    Suff_AddSuffix (line);
		    break;
D 19
		case Path:
E 19
I 19
		case ExPath:
E 19
		    Lst_ForEach(paths, ParseAddDir, (ClientData)line);
		    break;
		case Includes:
		    Suff_AddInclude (line);
		    break;
		case Libs:
		    Suff_AddLib (line);
D 5
		    break;
		case Export:
		    Rmt_AddServer (line);
E 5
		    break;
		case Null:
		    Suff_SetNull (line);
		    break;
I 19
		default:
		    break;
E 19
	    }
	    *cp = savec;
	    if (savec != '\0') {
		cp++;
	    }
	    while (*cp && isspace (*cp)) {
		cp++;
	    }
	    line = cp;
	}
	if (paths) {
	    Lst_Destroy(paths, NOFREE);
	}
    } else {
	while (*line) {
	    /*
	     * The targets take real sources, so we must beware of archive
	     * specifications (i.e. things with left parentheses in them)
	     * and handle them accordingly.
	     */
	    while (*cp && !isspace (*cp)) {
		if ((*cp == '(') && (cp > line) && (cp[-1] != '$')) {
		    /*
		     * Only stop for a left parenthesis if it isn't at the
		     * start of a word (that'll be for variable changes
		     * later) and isn't preceded by a dollar sign (a dynamic
		     * source).
		     */
		    break;
		} else {
		    cp++;
		}
	    }

	    if (*cp == '(') {
		GNode	  *gn;

		sources = Lst_Init (FALSE);
		if (Arch_ParseArchive (&line, sources, VAR_CMD) != SUCCESS) {
		    Parse_Error (PARSE_FATAL,
				 "Error in source archive spec \"%s\"", line);
		    return;
		}

		while (!Lst_IsEmpty (sources)) {
		    gn = (GNode *) Lst_DeQueue (sources);
		    ParseDoSrc (tOp, gn->name);
		}
		Lst_Destroy (sources, NOFREE);
		cp = line;
	    } else {
		if (*cp) {
		    *cp = '\0';
		    cp += 1;
		}

		ParseDoSrc (tOp, line);
	    }
	    while (*cp && isspace (*cp)) {
		cp++;
	    }
	    line = cp;
	}
    }
    
    if (mainNode == NILGNODE) {
	/*
	 * If we have yet to decide on a main target to make, in the
	 * absence of any user input, we want the first target on
	 * the first dependency line that is actually a real target
	 * (i.e. isn't a .USE or .EXEC rule) to be made.
	 */
	Lst_ForEach (targets, ParseFindMain, (ClientData)0);
    }

}
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * Parse_IsVar  --
 *	Return TRUE if the passed line is a variable assignment. A variable
 *	assignment consists of a single word followed by optional whitespace
 *	followed by either a += or an = operator.
 *	This function is used both by the Parse_File function and main when
 *	parsing the command-line arguments.
 *
 * Results:
 *	TRUE if it is. FALSE if it ain't
 *
 * Side Effects:
 *	none
 *---------------------------------------------------------------------
 */
Boolean
Parse_IsVar (line)
    register char  *line;	/* the line to check */
{
    register Boolean wasSpace = FALSE;	/* set TRUE if found a space */
    register Boolean haveName = FALSE;	/* Set TRUE if have a variable name */

    /*
     * Skip to variable name
     */
    while ((*line == ' ') || (*line == '\t')) {
	line++;
    }

    while (*line != '=') {
	if (*line == '\0') {
	    /*
	     * end-of-line -- can't be a variable assignment.
	     */
	    return (FALSE);
	} else if ((*line == ' ') || (*line == '\t')) {
	    /*
	     * there can be as much white space as desired so long as there is
	     * only one word before the operator 
	     */
	    wasSpace = TRUE;
	} else if (wasSpace && haveName) {
	    /*
	     * Stop when an = operator is found.
	     */
	    if ((*line == '+') || (*line == ':') || (*line == '?') || 
		(*line == '!')) {
		break;    
	    }

	    /*
	     * This is the start of another word, so not assignment.
	     */
	    return (FALSE);
	} else {
	    haveName = TRUE; 
	    wasSpace = FALSE;
	}
	line++;
    }

    /*
     * A final check: if we stopped on a +, ?, ! or :, the next character must
     * be an = or it ain't a valid assignment 
     */
    if (((*line == '+') ||
	 (*line == '?') ||
	 (*line == ':') ||
	 (*line == '!')) &&
	(line[1] != '='))
    {
	return (FALSE);
    } else {
	return (haveName);
    }
}
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * Parse_DoVar  --
 *	Take the variable assignment in the passed line and do it in the
 *	global context.
 *
 *	Note: There is a lexical ambiguity with assignment modifier characters
 *	in variable names. This routine interprets the character before the =
 *	as a modifier. Therefore, an assignment like
 *	    C++=/usr/bin/CC
 *	is interpreted as "C+ +=" instead of "C++ =".
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	the variable structure of the given variable name is altered in the
 *	global context.
 *---------------------------------------------------------------------
 */
void
Parse_DoVar (line, ctxt)
    char            *line;	/* a line guaranteed to be a variable
				 * assignment. This reduces error checks */
    GNode   	    *ctxt;    	/* Context in which to do the assignment */
{
D 25
    register char   *cp;	/* pointer into line */
E 25
I 25
D 27
    char   	    *cp;	/* pointer into line */
E 27
I 27
    char	   *cp;	/* pointer into line */
E 27
E 25
    enum {
	VAR_SUBST, VAR_APPEND, VAR_SHELL, VAR_NORMAL
    }	    	    type;   	/* Type of assignment */
    char            *opc;	/* ptr to operator character to 
				 * null-terminate the variable name */
I 25
D 27
    /*  
E 27
I 27
    /* 
E 27
     * Avoid clobbered variable warnings by forcing the compiler
     * to ``unregister'' variables
D 27
     */ 
E 27
I 27
     */
E 27
#if __GNUC__
D 27
    (void) &cp; 
    (void) &line; 
#endif 
E 27
I 27
    (void) &cp;
    (void) &line;
#endif
E 27
E 25

    /*
     * Skip to variable name
     */
    while ((*line == ' ') || (*line == '\t')) {
	line++;
    }

    /*
     * Skip to operator character, nulling out whitespace as we go
     */
    for (cp = line + 1; *cp != '='; cp++) {
	if (isspace (*cp)) {
	    *cp = '\0';
	}
    }
    opc = cp-1;		/* operator is the previous character */
    *cp++ = '\0';	/* nuke the = */

    /*
     * Check operator type
     */
    switch (*opc) {
	case '+':
	    type = VAR_APPEND;
	    *opc = '\0';
	    break;

	case '?':
	    /*
	     * If the variable already has a value, we don't do anything.
	     */
	    *opc = '\0';
	    if (Var_Exists(line, ctxt)) {
		return;
	    } else {
		type = VAR_NORMAL;
	    }
	    break;

	case ':':
	    type = VAR_SUBST;
	    *opc = '\0';
	    break;

	case '!':
	    type = VAR_SHELL;
	    *opc = '\0';
	    break;

	default:
	    type = VAR_NORMAL;
	    break;
    }

    while (isspace (*cp)) {
	cp++;
    }

    if (type == VAR_APPEND) {
	Var_Append (line, cp, ctxt);
    } else if (type == VAR_SUBST) {
	/*
	 * Allow variables in the old value to be undefined, but leave their
	 * invocation alone -- this is done by forcing oldVars to be false.
	 * XXX: This can cause recursive variables, but that's not hard to do,
	 * and this allows someone to do something like
	 *
	 *  CFLAGS = $(.INCLUDES)
	 *  CFLAGS := -I.. $(CFLAGS)
	 *
	 * And not get an error.
	 */
	Boolean	  oldOldVars = oldVars;

	oldVars = FALSE;
D 19
	cp = Var_Subst(cp, ctxt, FALSE);
E 19
I 19
	cp = Var_Subst(NULL, cp, ctxt, FALSE);
E 19
	oldVars = oldOldVars;

	Var_Set(line, cp, ctxt);
	free(cp);
    } else if (type == VAR_SHELL) {
D 19
	char	result[BUFSIZ];	/* Result of command */
E 19
	char	*args[4];   	/* Args for invoking the shell */
	int 	fds[2];	    	/* Pipe streams */
	int 	cpid;	    	/* Child PID */
	int 	pid;	    	/* PID from wait() */
	Boolean	freeCmd;    	/* TRUE if the command needs to be freed, i.e.
				 * if any variable expansion was performed */

I 19
D 25

E 25
I 25
D 27
	/*  
E 27
I 27
	/* 
E 27
	 * Avoid clobbered variable warnings by forcing the compiler
	 * to ``unregister'' variables
D 27
	 */ 
E 27
I 27
	 */
E 27
#if __GNUC__
	(void) &freeCmd;
D 27
#endif 
E 27
I 27
#endif

E 27
E 25
E 19
	/*
	 * Set up arguments for shell
	 */
	args[0] = "sh";
	args[1] = "-c";
D 19
	if (index(cp, '$') != (char *)NULL) {
E 19
I 19
	if (strchr(cp, '$') != (char *)NULL) {
E 19
	    /*
	     * There's a dollar sign in the command, so perform variable
	     * expansion on the whole thing. The resulting string will need
	     * freeing when we're done, so set freeCmd to TRUE.
	     */
D 19
	    args[2] = Var_Subst(cp, VAR_CMD, TRUE);
E 19
I 19
	    args[2] = Var_Subst(NULL, cp, VAR_CMD, TRUE);
E 19
	    freeCmd = TRUE;
	} else {
	    args[2] = cp;
	    freeCmd = FALSE;
	}
	args[3] = (char *)NULL;

	/*
	 * Open a pipe for fetching its output
	 */
	pipe(fds);

	/*
	 * Fork
	 */
	cpid = vfork();
	if (cpid == 0) {
	    /*
	     * Close input side of pipe
	     */
	    close(fds[0]);

	    /*
	     * Duplicate the output stream to the shell's output, then
	     * shut the extra thing down. Note we don't fetch the error
	     * stream...why not? Why?
	     */
	    dup2(fds[1], 1);
	    close(fds[1]);
	    
	    execv("/bin/sh", args);
	    _exit(1);
	} else if (cpid < 0) {
	    /*
	     * Couldn't fork -- tell the user and make the variable null
	     */
	    Parse_Error(PARSE_WARNING, "Couldn't exec \"%s\"", cp);
	    Var_Set(line, "", ctxt);
	} else {
	    int	status;
	    int cc;
I 19
	    Buffer buf;
	    char *res;
E 19

	    /*
	     * No need for the writing half
	     */
	    close(fds[1]);
	    
I 19
	    buf = Buf_Init (MAKE_BSIZE);

	    do {
		char   result[BUFSIZ];
		cc = read(fds[0], result, sizeof(result));
		if (cc > 0) 
D 27
		    Buf_AddBytes(buf, cc, (unsigned char *) result);
E 27
I 27
		    Buf_AddBytes(buf, cc, (Byte *) result);
E 27
	    }
	    while (cc > 0 || (cc == -1 && errno == EINTR));

E 19
	    /*
D 19
	     * Wait for the process to exit.
	     *
	     * XXX: If the child writes more than a pipe's worth, we will
	     * deadlock.
E 19
I 19
	     * Close the input side of the pipe.
E 19
	     */
D 19
	    while(((pid = wait(&status)) != cpid) && (pid >= 0)) {
		;
	    }
E 19
I 19
	    close(fds[0]);
E 19

	    /*
D 19
	     * Read all the characters the child wrote.
E 19
I 19
	     * Wait for the process to exit.
E 19
	     */
D 19
	    cc = read(fds[0], result, sizeof(result));
E 19
I 19
	    while(((pid = wait(&status)) != cpid) && (pid >= 0))
		continue;
E 19

D 19
	    if (cc < 0) {
E 19
I 19
	    res = (char *)Buf_GetAll (buf, &cc);
	    Buf_Destroy (buf, FALSE);

	    if (cc == 0) {
E 19
		/*
		 * Couldn't read the child's output -- tell the user and
		 * set the variable to null
		 */
		Parse_Error(PARSE_WARNING, "Couldn't read shell's output");
D 19
		cc = 0;
E 19
	    }

	    if (status) {
		/*
		 * Child returned an error -- tell the user but still use
		 * the result.
		 */
		Parse_Error(PARSE_WARNING, "\"%s\" returned non-zero", cp);
	    }
I 19

E 19
	    /*
	     * Null-terminate the result, convert newlines to spaces and
	     * install it in the variable.
	     */
D 19
	    result[cc] = '\0';
	    cp = &result[cc] - 1;
E 19
I 19
	    res[cc] = '\0';
	    cp = &res[cc] - 1;
E 19

	    if (*cp == '\n') {
		/*
		 * A final newline is just stripped
		 */
		*cp-- = '\0';
	    }
D 19
	    while (cp >= result) {
E 19
I 19
	    while (cp >= res) {
E 19
		if (*cp == '\n') {
		    *cp = ' ';
		}
		cp--;
	    }
D 19
	    Var_Set(line, result, ctxt);
E 19
I 19
	    Var_Set(line, res, ctxt);
	    free(res);
E 19

D 19
	    /*
	     * Close the input side of the pipe.
	     */
	    close(fds[0]);
E 19
	}
	if (freeCmd) {
	    free(args[2]);
	}
    } else {
	/*
	 * Normal assignment -- just do it.
	 */
	Var_Set (line, cp, ctxt);
    }
}
D 3

E 3
I 3

E 3
/*-
D 7
 *---------------------------------------------------------------------
E 7
 * ParseAddCmd  --
 *	Lst_ForEach function to add a command line to all targets
 *
 * Results:
 *	Always 0
 *
 * Side Effects:
 *	A new element is added to the commands list of the node.
D 7
 *---------------------------------------------------------------------
E 7
 */
D 7
static int
ParseAddCmd (gn, cmd)
    GNode          *gn;		/* the node to which the command is to be
				 * added */
    char           *cmd;	/* the command to add */
E 7
I 7
D 19
static
E 19
I 19
static int
E 19
D 27
ParseAddCmd(gn, cmd)
	GNode *gn;	/* the node to which the command is to be added */
	char *cmd;	/* the command to add */
E 27
I 27
ParseAddCmd(gnp, cmd)
    ClientData gnp;	/* the node to which the command is to be added */
    ClientData cmd;	/* the command to add */
E 27
E 7
{
D 7
    if (gn->type & OP_HAS_COMMANDS) {
	Parse_Error(PARSE_WARNING, "Extra command line for \"%s\" ignored",
		    gn->name);
    } else {
	(void)Lst_AtEnd (gn->commands, (ClientData)cmd);
    }

    return (0);
E 7
I 7
D 27
	/* if target already supplied, ignore commands */
	if (!(gn->type & OP_HAS_COMMANDS))
		(void)Lst_AtEnd(gn->commands, (ClientData)cmd);
	return(0);
E 27
I 27
    GNode *gn = (GNode *) gnp;
    /* if target already supplied, ignore commands */
    if (!(gn->type & OP_HAS_COMMANDS))
	(void)Lst_AtEnd(gn->commands, cmd);
    return(0);
E 27
E 7
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * ParseHasCommands --
 *	Callback procedure for Parse_File when destroying the list of
 *	targets on the last dependency line. Marks a target as already
 *	having commands if it does, to keep from having shell commands
 *	on multiple dependency lines.
 *
 * Results:
D 27
 *	Always 0.
E 27
I 27
 *	None
E 27
 *
 * Side Effects:
 *	OP_HAS_COMMANDS may be set for the target.
 *
 *-----------------------------------------------------------------------
 */
D 27
static int
ParseHasCommands(gn)
    GNode   	  *gn;	    /* Node to examine */
E 27
I 27
static void
ParseHasCommands(gnp)
    ClientData 	  gnp;	    /* Node to examine */
E 27
{
I 27
    GNode *gn = (GNode *) gnp;
E 27
    if (!Lst_IsEmpty(gn->commands)) {
	gn->type |= OP_HAS_COMMANDS;
    }
D 27
    return(0);
E 27
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Parse_AddIncludeDir --
 *	Add a directory to the path searched for included makefiles
 *	bracketed by double-quotes. Used by functions in main.c
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The directory is appended to the list.
 *
 *-----------------------------------------------------------------------
 */
void
Parse_AddIncludeDir (dir)
    char    	  *dir;	    /* The name of the directory to add */
{
    Dir_AddDir (parseIncPath, dir);
}
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * ParseDoInclude  --
 *	Push to another file.
 *	
 *	The input is the line minus the #include. A file spec is a string
 *	enclosed in <> or "". The former is looked for only in sysIncPath.
 *	The latter in . and the directories specified by -I command line
 *	options
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A structure is added to the includes Lst and readProc, lineno,
 *	fname and curFILE are altered for the new file
 *---------------------------------------------------------------------
 */
static void
ParseDoInclude (file)
    char          *file;	/* file specification */
{
    char          *fullname;	/* full pathname of file */
    IFile         *oldFile;	/* state associated with current file */
D 19
    Lst           path;	    	/* the path to use to find the file */
E 19
    char          endc;	    	/* the character which ends the file spec */
    char          *cp;		/* current position in file spec */
    Boolean 	  isSystem; 	/* TRUE if makefile is a system makefile */

    /*
     * Skip to delimiter character so we know where to look
     */
    while ((*file == ' ') || (*file == '\t')) {
	file++;
    }

    if ((*file != '"') && (*file != '<')) {
D 13
	/*
	 * XXX: Should give some sort of error message, I suppose, but because
	 * # is used for both comments and directives, we can't be sure if
	 * the thing might not just be a comment, so we just return...
	 */
E 13
I 13
	Parse_Error (PARSE_FATAL,
	    ".include filename must be delimited by '\"' or '<'");
E 13
	return;
    }

    /*
     * Set the search path on which to find the include file based on the
     * characters which bracket its name. Angle-brackets imply it's
     * a system Makefile while double-quotes imply it's a user makefile
     */
    if (*file == '<') {
	isSystem = TRUE;
	endc = '>';
    } else {
	isSystem = FALSE;
	endc = '"';
    }

    /*
     * Skip to matching delimiter
     */
    for (cp = ++file; *cp && *cp != endc; cp++) {
	continue;
    }

    if (*cp != endc) {
	Parse_Error (PARSE_FATAL,
D 4
		     "Unclosed %cinclude filename. '%c' expected",
		     SPECIAL_CHAR, endc);
E 4
I 4
D 19
		     "Unclosed .include filename. '%c' expected", endc);
E 19
I 19
		     "Unclosed %cinclude filename. '%c' expected",
		     '.', endc);
E 19
E 4
	return;
    }
    *cp = '\0';

    /*
     * Substitute for any variables in the file name before trying to
     * find the thing.
     */
D 19
    file = Var_Subst (file, VAR_CMD, FALSE);
E 19
I 19
    file = Var_Subst (NULL, file, VAR_CMD, FALSE);
E 19

    /*
     * Now we know the file's name and its search path, we attempt to
     * find the durn thing. A return of NULL indicates the file don't
     * exist.
     */
    if (!isSystem) {
	/*
	 * Include files contained in double-quotes are first searched for
	 * relative to the including file's location. We don't want to
	 * cd there, of course, so we just tack on the old file's
	 * leading path components and call Dir_FindFile to see if
	 * we can locate the beast.
	 */
	char	  *prefEnd;

D 19
	prefEnd = rindex (fname, '/');
E 19
I 19
	prefEnd = strrchr (fname, '/');
E 19
	if (prefEnd != (char *)NULL) {
	    char  	*newName;
	    
	    *prefEnd = '\0';
D 9
	    newName = Str_Concat (fname, file, STR_ADDSLASH);
E 9
I 9
D 27
	    newName = str_concat (fname, file, STR_ADDSLASH);
E 27
I 27
	    if (file[0] == '/')
		newName = strdup(file);
	    else
		newName = str_concat (fname, file, STR_ADDSLASH);
E 27
E 9
	    fullname = Dir_FindFile (newName, parseIncPath);
	    if (fullname == (char *)NULL) {
		fullname = Dir_FindFile(newName, dirSearchPath);
	    }
	    free (newName);
	    *prefEnd = '/';
	} else {
	    fullname = (char *)NULL;
	}
    } else {
	fullname = (char *)NULL;
    }

    if (fullname == (char *)NULL) {
	/*
	 * System makefile or makefile wasn't found in same directory as
	 * included makefile. Search for it first on the -I search path,
	 * then on the .PATH search path, if not found in a -I directory.
	 * XXX: Suffix specific?
	 */
	fullname = Dir_FindFile (file, parseIncPath);
	if (fullname == (char *)NULL) {
	    fullname = Dir_FindFile(file, dirSearchPath);
	}
    }

    if (fullname == (char *)NULL) {
	/*
	 * Still haven't found the makefile. Look for it on the system
	 * path as a last resort.
	 */
	fullname = Dir_FindFile(file, sysIncPath);
    }

    if (fullname == (char *) NULL) {
	*cp = endc;
	Parse_Error (PARSE_FATAL, "Could not find %s", file);
	return;
    }

I 27
    free(file);

E 27
    /*
     * Once we find the absolute path to the file, we get to save all the
     * state from the current file before we can start reading this
     * include file. The state is stored in an IFile structure which
     * is placed on a list with other IFile structures. The list makes
     * a very nice stack to track how we got here...
     */
D 9
    oldFile = (IFile *) malloc (sizeof (IFile));
E 9
I 9
    oldFile = (IFile *) emalloc (sizeof (IFile));
E 9
    oldFile->fname = fname;

    oldFile->F = curFILE;
I 19
    oldFile->p = curPTR;
E 19
    oldFile->lineno = lineno;

    (void) Lst_AtFront (includes, (ClientData)oldFile);

    /*
     * Once the previous state has been saved, we can get down to reading
     * the new file. We set up the name of the file to be the absolute
     * name of the include file so error messages refer to the right
     * place. Naturally enough, we start reading at line number 0.
     */
    fname = fullname;
    lineno = 0;

    curFILE = fopen (fullname, "r");
I 19
    curPTR = NULL;
E 19
    if (curFILE == (FILE * ) NULL) {
	Parse_Error (PARSE_FATAL, "Cannot open %s", fullname);
	/*
	 * Pop to previous file
	 */
D 18
	(void) ParseEOF();
E 18
I 18
	(void) ParseEOF(0);
E 18
    }
}
D 3

E 3
I 3

I 19

E 19
E 3
/*-
 *---------------------------------------------------------------------
I 19
 * Parse_FromString  --
 *	Start Parsing from the given string
 *	
 * Results:
 *	None
 *
 * Side Effects:
 *	A structure is added to the includes Lst and readProc, lineno,
 *	fname and curFILE are altered for the new file
 *---------------------------------------------------------------------
 */
void
Parse_FromString(str)
    char *str;
{
    IFile         *oldFile;	/* state associated with this file */

    if (DEBUG(FOR))
	(void) fprintf(stderr, "%s\n----\n", str);

    oldFile = (IFile *) emalloc (sizeof (IFile));
    oldFile->lineno = lineno;
    oldFile->fname = fname;
    oldFile->F = curFILE;
    oldFile->p = curPTR;
    
    (void) Lst_AtFront (includes, (ClientData)oldFile);

    curFILE = NULL;
    curPTR = (PTR *) emalloc (sizeof (PTR));
    curPTR->str = curPTR->ptr = str;
    lineno = 0;
    fname = strdup(fname);
}


#ifdef SYSVINCLUDE
/*-
 *---------------------------------------------------------------------
 * ParseTraditionalInclude  --
 *	Push to another file.
 *	
 *	The input is the line minus the "include".  The file name is
 *	the string following the "include".
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A structure is added to the includes Lst and readProc, lineno,
 *	fname and curFILE are altered for the new file
 *---------------------------------------------------------------------
 */
static void
ParseTraditionalInclude (file)
    char          *file;	/* file specification */
{
    char          *fullname;	/* full pathname of file */
    IFile         *oldFile;	/* state associated with current file */
    char          *cp;		/* current position in file spec */
    char	  *prefEnd;

    /*
     * Skip over whitespace
     */
    while ((*file == ' ') || (*file == '\t')) {
	file++;
    }

    if (*file == '\0') {
	Parse_Error (PARSE_FATAL,
		     "Filename missing from \"include\"");
	return;
    }

    /*
     * Skip to end of line or next whitespace
     */
    for (cp = file; *cp && *cp != '\n' && *cp != '\t' && *cp != ' '; cp++) {
	continue;
    }

    *cp = '\0';

    /*
     * Substitute for any variables in the file name before trying to
     * find the thing.
     */
    file = Var_Subst (NULL, file, VAR_CMD, FALSE);

    /*
     * Now we know the file's name, we attempt to find the durn thing.
     * A return of NULL indicates the file don't exist.
     *
     * Include files are first searched for relative to the including
     * file's location. We don't want to cd there, of course, so we
     * just tack on the old file's leading path components and call
     * Dir_FindFile to see if we can locate the beast.
     * XXX - this *does* search in the current directory, right?
     */

    prefEnd = strrchr (fname, '/');
    if (prefEnd != (char *)NULL) {
	char  	*newName;
	    
	*prefEnd = '\0';
	newName = str_concat (fname, file, STR_ADDSLASH);
	fullname = Dir_FindFile (newName, parseIncPath);
	if (fullname == (char *)NULL) {
	    fullname = Dir_FindFile(newName, dirSearchPath);
	}
	free (newName);
	*prefEnd = '/';
    } else {
	fullname = (char *)NULL;
    }

    if (fullname == (char *)NULL) {
	/*
	 * System makefile or makefile wasn't found in same directory as
	 * included makefile. Search for it first on the -I search path,
	 * then on the .PATH search path, if not found in a -I directory.
	 * XXX: Suffix specific?
	 */
	fullname = Dir_FindFile (file, parseIncPath);
	if (fullname == (char *)NULL) {
	    fullname = Dir_FindFile(file, dirSearchPath);
	}
    }

    if (fullname == (char *)NULL) {
	/*
	 * Still haven't found the makefile. Look for it on the system
	 * path as a last resort.
	 */
	fullname = Dir_FindFile(file, sysIncPath);
    }

    if (fullname == (char *) NULL) {
	Parse_Error (PARSE_FATAL, "Could not find %s", file);
	return;
    }

    /*
     * Once we find the absolute path to the file, we get to save all the
     * state from the current file before we can start reading this
     * include file. The state is stored in an IFile structure which
     * is placed on a list with other IFile structures. The list makes
     * a very nice stack to track how we got here...
     */
    oldFile = (IFile *) emalloc (sizeof (IFile));
    oldFile->fname = fname;

    oldFile->F = curFILE;
    oldFile->p = curPTR;
    oldFile->lineno = lineno;

    (void) Lst_AtFront (includes, (ClientData)oldFile);

    /*
     * Once the previous state has been saved, we can get down to reading
     * the new file. We set up the name of the file to be the absolute
     * name of the include file so error messages refer to the right
     * place. Naturally enough, we start reading at line number 0.
     */
    fname = fullname;
    lineno = 0;

    curFILE = fopen (fullname, "r");
    curPTR = NULL;
    if (curFILE == (FILE * ) NULL) {
	Parse_Error (PARSE_FATAL, "Cannot open %s", fullname);
	/*
	 * Pop to previous file
	 */
	(void) ParseEOF(1);
    }
}
#endif

/*-
 *---------------------------------------------------------------------
E 19
 * ParseEOF  --
 *	Called when EOF is reached in the current file. If we were reading
 *	an include file, the includes stack is popped and things set up
 *	to go back to reading the previous file at the previous location.
 *
 * Results:
 *	CONTINUE if there's more to do. DONE if not.
 *
 * Side Effects:
 *	The old curFILE, is closed. The includes list is shortened.
 *	lineno, curFILE, and fname are changed if CONTINUE is returned.
 *---------------------------------------------------------------------
 */
static int
D 18
ParseEOF ()
E 18
I 18
ParseEOF (opened)
    int opened;
E 18
{
    IFile     *ifile;	/* the state on the top of the includes stack */

    if (Lst_IsEmpty (includes)) {
	return (DONE);
    }

    ifile = (IFile *) Lst_DeQueue (includes);
D 19
    free (fname);
E 19
I 19
    free ((Address) fname);
E 19
    fname = ifile->fname;
    lineno = ifile->lineno;
D 18
    fclose (curFILE);
E 18
I 18
D 19
    if (opened)
E 19
I 19
    if (opened && curFILE)
E 19
	(void) fclose (curFILE);
I 19
    if (curPTR) {
	free((Address) curPTR->str);
	free((Address) curPTR);
    }
E 19
E 18
    curFILE = ifile->F;
I 19
    curPTR = ifile->p;
E 19
    free ((Address)ifile);
    return (CONTINUE);
}
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * ParseReadc  --
D 19
 *	Read a character from the current file and update the line number
 *	counter as necessary
E 19
I 19
 *	Read a character from the current file 
E 19
 *
 * Results:
 *	The character that was read
 *
 * Side Effects:
D 19
 *	The lineno counter is incremented if the character is a newline
E 19
 *---------------------------------------------------------------------
 */
D 19
#ifdef notdef
static int parseReadChar;
E 19
I 19
static int
ParseReadc()
{
    if (curFILE)
	return fgetc(curFILE);
	  
    if (curPTR && *curPTR->ptr)
	return *curPTR->ptr++;
    return EOF;
}
E 19

I 20

/*-
 *---------------------------------------------------------------------
 * ParseUnreadc  --
 *	Put back a character to the current file 
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *---------------------------------------------------------------------
 */
static void
ParseUnreadc(c)
    int c;
{
    if (curFILE) {
	ungetc(c, curFILE);
	return;
    }
    if (curPTR) {
	*--(curPTR->ptr) = c;
	return;
    }
}


E 20
D 19
#define ParseReadc() (((parseReadChar = getc(curFILE)) == '\n') ? \
		      (lineno++, '\n') : parseReadChar)
#else
#define ParseReadc() (getc(curFILE))
#endif /* notdef */
E 19
I 19
/* ParseSkipLine():
 *	Grab the next line
 */
static char *
ParseSkipLine(skip)
    int skip; 		/* Skip lines that don't start with . */
{
    char *line;
    int c, lastc = '\0', lineLength;
    Buffer buf;
E 19

I 19
    c = ParseReadc();
E 19
D 3

E 3
I 3

I 19
    if (skip) {
	/*
	 * Skip lines until get to one that begins with a
	 * special char.
	 */
	while ((c != '.') && (c != EOF)) {
	    while (((c != '\n') || (lastc == '\\')) && (c != EOF))
	    {
		/*
		 * Advance to next unescaped newline
		 */
		if ((lastc = c) == '\n') {
		    lineno++;
		}
		c = ParseReadc();
	    }
	    lineno++;
	    
	    lastc = c;
	    c = ParseReadc ();
	}
    }
    
    if (c == EOF) {
	Parse_Error (PARSE_FATAL, "Unclosed conditional/for loop");
	return ((char *)NULL);
    }
    
    /*
     * Read the entire line into buf
     */
    buf = Buf_Init (MAKE_BSIZE);
    if (c != '\n') {
	do {
	    Buf_AddByte (buf, (Byte)c);
	    c = ParseReadc();
	} while ((c != '\n') && (c != EOF));
    }
    lineno++;
    
    Buf_AddByte (buf, (Byte)'\0');
    line = (char *)Buf_GetAll (buf, &lineLength);
    Buf_Destroy (buf, FALSE);
    return line;
}


E 19
E 3
/*-
 *---------------------------------------------------------------------
 * ParseReadLine --
 *	Read an entire line from the input file. Called only by Parse_File.
 *	To facilitate escaped newlines and what have you, a character is
 *	buffered in 'lastc', which is '\0' when no characters have been
 *	read. When we break out of the loop, c holds the terminating
 *	character and lastc holds a character that should be added to
 *	the line (unless we don't read anything but a terminator).
 *
 * Results:
 *	A line w/o its newline
 *
 * Side Effects:
 *	Only those associated with reading a character
 *---------------------------------------------------------------------
 */
static char *
ParseReadLine ()
{
    Buffer  	  buf;	    	/* Buffer for current line */
    register int  c;	      	/* the current character */
    register int  lastc;    	/* The most-recent character */
    Boolean	  semiNL;     	/* treat semi-colons as newlines */
    Boolean	  ignDepOp;   	/* TRUE if should ignore dependency operators
				 * for the purposes of setting semiNL */
    Boolean 	  ignComment;	/* TRUE if should ignore comments (in a
				 * shell command */
D 27
    char    	  *line;    	/* Result */
E 27
I 27
    char 	  *line;    	/* Result */
    char          *ep;		/* to strip trailing blanks */
E 27
    int	    	  lineLength;	/* Length of result */

    semiNL = FALSE;
    ignDepOp = FALSE;
    ignComment = FALSE;

    /*
     * Handle special-characters at the beginning of the line. Either a
     * leading tab (shell command) or pound-sign (possible conditional)
     * forces us to ignore comments and dependency operators and treat
     * semi-colons as semi-colons (by leaving semiNL FALSE). This also
     * discards completely blank lines.
     */
D 19
    while(1) {
E 19
I 19
    for (;;) {
E 19
	c = ParseReadc();

D 4
	if ((c == '\t') || (c == SPECIAL_CHAR)) {
E 4
I 4
D 16
	if ((c == '\t') || (c == '.')) {
E 16
I 16
D 19
	if (c == '\t') {
E 19
I 19
D 20
	if ((c == '\t') || (c == '.')) {
E 20
I 20
	if (c == '\t') {
E 20
E 19
	    ignComment = ignDepOp = TRUE;
	    break;
D 19
	} else if (c == '.') {
E 16
E 4
D 15
	    ignComment = ignDepOp = TRUE;
E 15
I 15
	    ignComment = TRUE;
E 15
	    break;
E 19
	} else if (c == '\n') {
	    lineno++;
I 21
	} else if (c == '#') {
D 22
		ungetc(c, curFILE);
E 22
I 22
D 25
		ParseUnreadc(c);
E 22
		break;
E 25
I 25
	    ParseUnreadc(c);
	    break;
E 25
E 21
I 12
D 19
	} else if (c == '#') {
		ungetc(c, curFILE); 
		break;
E 19
E 12
	} else {
	    /*
	     * Anything else breaks out without doing anything
	     */
	    break;
	}
    }
	
    if (c != EOF) {
	lastc = c;
D 19
	buf = Buf_Init(BSIZE);
E 19
I 19
	buf = Buf_Init(MAKE_BSIZE);
E 19
	
	while (((c = ParseReadc ()) != '\n' || (lastc == '\\')) &&
	       (c != EOF))
	{
test_char:
	    switch(c) {
	    case '\n':
		/*
		 * Escaped newline: read characters until a non-space or an
		 * unescaped newline and replace them all by a single space.
		 * This is done by storing the space over the backslash and
		 * dropping through with the next nonspace. If it is a
		 * semi-colon and semiNL is TRUE, it will be recognized as a
		 * newline in the code below this...
		 */
		lineno++;
		lastc = ' ';
		while ((c = ParseReadc ()) == ' ' || c == '\t') {
		    continue;
		}
		if (c == EOF || c == '\n') {
		    goto line_read;
		} else {
		    /*
		     * Check for comments, semiNL's, etc. -- easier than
D 20
		     * ungetc(c, curFILE); continue;
E 20
I 20
		     * ParseUnreadc(c); continue;
E 20
		     */
		    goto test_char;
		}
I 19
		/*NOTREACHED*/
E 19
		break;
I 19

E 19
	    case ';':
		/*
		 * Semi-colon: Need to see if it should be interpreted as a
		 * newline
		 */
		if (semiNL) {
		    /*
		     * To make sure the command that may be following this
		     * semi-colon begins with a tab, we push one back into the
		     * input stream. This will overwrite the semi-colon in the
		     * buffer. If there is no command following, this does no
		     * harm, since the newline remains in the buffer and the
		     * whole line is ignored.
		     */
D 20
		    ungetc('\t', curFILE);
E 20
I 20
		    ParseUnreadc('\t');
E 20
		    goto line_read;
		} 
		break;
	    case '=':
		if (!semiNL) {
		    /*
		     * Haven't seen a dependency operator before this, so this
		     * must be a variable assignment -- don't pay attention to
		     * dependency operators after this.
		     */
		    ignDepOp = TRUE;
		} else if (lastc == ':' || lastc == '!') {
		    /*
		     * Well, we've seen a dependency operator already, but it
		     * was the previous character, so this is really just an
		     * expanded variable assignment. Revert semi-colons to
		     * being just semi-colons again and ignore any more
		     * dependency operators.
		     *
		     * XXX: Note that a line like "foo : a:=b" will blow up,
		     * but who'd write a line like that anyway?
		     */
		    ignDepOp = TRUE; semiNL = FALSE;
		}
		break;
	    case '#':
		if (!ignComment) {
I 19
D 26
		    if (compatMake || (lastc != '\\')) {
E 26
I 26
		    if (compatMake && (lastc != '\\')) {
E 26
E 19
D 6
		    if (backwards || (lastc != '\\')) {
E 6
			/*
			 * If the character is a hash mark and it isn't escaped
			 * (or we're being compatible), the thing is a comment.
			 * Skip to the end of the line.
			 */
			do {
			    c = ParseReadc();
			} while ((c != '\n') && (c != EOF));
			goto line_read;
I 19
		    } else {
			/*
			 * Don't add the backslash. Just let the # get copied
			 * over.
			 */
			lastc = c;
			continue;
		    }
E 19
D 6
		    } else {
			/*
			 * Don't add the backslash. Just let the # get copied
			 * over.
			 */
			lastc = c;
			continue;
		    }
E 6
		}
		break;
	    case ':':
	    case '!':
		if (!ignDepOp && (c == ':' || c == '!')) {
		    /*
		     * A semi-colon is recognized as a newline only on
		     * dependency lines. Dependency lines are lines with a
		     * colon or an exclamation point. Ergo...
		     */
		    semiNL = TRUE;
		}
		break;
	    }
	    /*
	     * Copy in the previous character and save this one in lastc.
	     */
	    Buf_AddByte (buf, (Byte)lastc);
	    lastc = c;
	    
	}
    line_read:
	lineno++;
	
	if (lastc != '\0') {
	    Buf_AddByte (buf, (Byte)lastc);
	}
	Buf_AddByte (buf, (Byte)'\0');
	line = (char *)Buf_GetAll (buf, &lineLength);
	Buf_Destroy (buf, FALSE);
I 27

	/*
	 * Strip trailing blanks and tabs from the line.
	 * Do not strip a blank or tab that is preceeded by
	 * a '\'
	 */
	ep = line;
	while (*ep)
	    ++ep;
	while (ep > line && (ep[-1] == ' ' || ep[-1] == '\t')) {
	    if (ep > line + 1 && ep[-2] == '\\')
		break;
	    --ep;
	}
	*ep = 0;
E 27
	
D 4
	if (line[0] == SPECIAL_CHAR) {
E 4
I 4
	if (line[0] == '.') {
E 4
	    /*
	     * The line might be a conditional. Ask the conditional module
	     * about it and act accordingly
	     */
	    switch (Cond_Eval (line)) {
	    case COND_SKIP:
I 19
		/*
		 * Skip to next conditional that evaluates to COND_PARSE.
		 */
E 19
		do {
D 19
		    /*
		     * Skip to next conditional that evaluates to COND_PARSE.
		     */
E 19
		    free (line);
D 19
		    c = ParseReadc();
		    /*
		     * Skip lines until get to one that begins with a
		     * special char.
		     */
D 4
		    while ((c != SPECIAL_CHAR) && (c != EOF)) {
E 4
I 4
		    while ((c != '.') && (c != EOF)) {
E 4
			while (((c != '\n') || (lastc == '\\')) &&
			       (c != EOF))
			{
			    /*
			     * Advance to next unescaped newline
			     */
			    if ((lastc = c) == '\n') {
				lineno++;
			    }
			    c = ParseReadc();
			}
			lineno++;
			
			lastc = c;
			c = ParseReadc ();
		    }
		    
		    if (c == EOF) {
			Parse_Error (PARSE_FATAL, "Unclosed conditional");
			return ((char *)NULL);
		    }
		    
		    /*
		     * Read the entire line into buf
		     */
		    buf = Buf_Init (BSIZE);
		    do {
			Buf_AddByte (buf, (Byte)c);
			c = ParseReadc();
		    } while ((c != '\n') && (c != EOF));
		    lineno++;
		    
		    Buf_AddByte (buf, (Byte)'\0');
		    line = (char *)Buf_GetAll (buf, &lineLength);
		    Buf_Destroy (buf, FALSE);
		} while (Cond_Eval(line) != COND_PARSE);
E 19
I 19
		    line = ParseSkipLine(1);
		} while (line && Cond_Eval(line) != COND_PARSE);
		if (line == NULL)
		    break;
E 19
		/*FALLTHRU*/
	    case COND_PARSE:
D 19
		free (line);
E 19
I 19
		free ((Address) line);
E 19
		line = ParseReadLine();
		break;
I 19
	    case COND_INVALID:
		if (For_Eval(line)) {
		    int ok;
		    free(line);
		    do {
			/*
			 * Skip after the matching end
			 */
			line = ParseSkipLine(0);
			if (line == NULL) {
			    Parse_Error (PARSE_FATAL, 
				     "Unexpected end of file in for loop.\n");
			    break;
			}
			ok = For_Eval(line);
			free(line);
		    }
		    while (ok);
		    if (line != NULL)
			For_Run();
		    line = ParseReadLine();
		}
		break;
E 19
	    }
	}
D 19
	
E 19
	return (line);
I 19

E 19
    } else {
	/*
	 * Hit end-of-file, so return a NULL line to indicate this.
	 */
	return((char *)NULL);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * ParseFinishLine --
 *	Handle the end of a dependency group.
 *
 * Results:
 *	Nothing.
 *
 * Side Effects:
 *	inLine set FALSE. 'targets' list destroyed.
 *
 *-----------------------------------------------------------------------
 */
static void
ParseFinishLine()
{
D 27
    extern int Suff_EndTransform();

E 27
    if (inLine) {
	Lst_ForEach(targets, Suff_EndTransform, (ClientData)NULL);
	Lst_Destroy (targets, ParseHasCommands);
I 27
	targets = NULL;
E 27
	inLine = FALSE;
    }
}
		    
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * Parse_File --
 *	Parse a file into its component parts, incorporating it into the
 *	current dependency graph. This is the main function and controls
 *	almost every other function in this module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Loads. Nodes are added to the list of all targets, nodes and links
 *	are added to the dependency graph. etc. etc. etc.
 *---------------------------------------------------------------------
 */
void
Parse_File(name, stream)
    char          *name;	/* the name of the file being read */
    FILE *	  stream;   	/* Stream open to makefile to parse */
{
    register char *cp,		/* pointer into the line */
                  *line;	/* the line we're working on */

    inLine = FALSE;
    fname = name;
    curFILE = stream;
    lineno = 0;
    fatals = 0;

    do {
D 19
	while (line = ParseReadLine ()) {
E 19
I 19
	while ((line = ParseReadLine ()) != NULL) {
E 19
D 4
	    if (*line == SPECIAL_CHAR) {
E 4
I 4
	    if (*line == '.') {
E 4
		/*
		 * Lines that begin with the special character are either
		 * include or undef directives.
		 */
		for (cp = line + 1; isspace (*cp); cp++) {
		    continue;
		}
		if (strncmp (cp, "include", 7) == 0) {
		    ParseDoInclude (cp + 7);
		    goto nextLine;
		} else if (strncmp(cp, "undef", 5) == 0) {
		    char *cp2;
D 27
		    for (cp += 5; isspace(*cp); cp++) {
E 27
I 27
		    for (cp += 5; isspace((unsigned char) *cp); cp++) {
E 27
			continue;
		    }

D 27
		    for (cp2 = cp; !isspace(*cp2) && (*cp2 != '\0'); cp2++) {
E 27
I 27
		    for (cp2 = cp; !isspace((unsigned char) *cp2) &&
				   (*cp2 != '\0'); cp2++) {
E 27
			continue;
		    }

		    *cp2 = '\0';

		    Var_Delete(cp, VAR_GLOBAL);
		    goto nextLine;
		}
	    }
D 27
	    if (*line == '#') {
D 4
		/*
		 * If we're this far, the line must be a comment, even if
		 * SPECIAL_CHAR is '#'
		 */
E 4
I 4
		/* If we're this far, the line must be a comment. */
E 27
I 27
	    if (*line == '#' || *line == '\0') {
		/* If we're this far, the line must be a comment.
		   (Empty lines are ignored as well) */
E 27
E 4
		goto nextLine;
	    }
	    
D 27
	    if (*line == '\t'
#ifdef POSIX
		       || *line == ' '
#endif
		       )
	    {
E 27
I 27
	    if (*line == '\t') {
E 27
		/*
D 27
		 * If a line starts with a tab (or space in POSIX-land), it
		 * can only hope to be a creation command.
E 27
I 27
		 * If a line starts with a tab, it can only hope to be
		 * a creation command.
E 27
		 */
I 27
#ifndef POSIX
E 27
	    shellCommand:
I 27
#endif
E 27
		for (cp = line + 1; isspace (*cp); cp++) {
		    continue;
		}
		if (*cp) {
		    if (inLine) {
			/*
			 * So long as it's not a blank line and we're actually
			 * in a dependency spec, add the command to the list of
			 * commands of all targets in the dependency spec 
			 */
D 27
			Lst_ForEach (targets, ParseAddCmd, (ClientData)cp);
E 27
I 27
			Lst_ForEach (targets, ParseAddCmd, cp);
			Lst_AtEnd(targCmds, (ClientData) line);
E 27
			continue;
		    } else {
			Parse_Error (PARSE_FATAL,
				     "Unassociated shell command \"%.20s\"",
				     cp);
		    }
		}
I 19
#ifdef SYSVINCLUDE
	    } else if (strncmp (line, "include", 7) == 0 && 
		       strchr(line, ':') == NULL) {
		/*
		 * It's an S3/S5-style "include".
		 */
		ParseTraditionalInclude (line + 7);
		goto nextLine;
#endif
E 19
	    } else if (Parse_IsVar (line)) {
		ParseFinishLine();
		Parse_DoVar (line, VAR_GLOBAL);
	    } else {
		/*
		 * We now know it's a dependency line so it needs to have all
		 * variables expanded before being parsed. Tell the variable
		 * module to complain if some variable is undefined...
		 * To make life easier on novices, if the line is indented we
		 * first make sure the line has a dependency operator in it.
		 * If it doesn't have an operator and we're in a dependency
		 * line's script, we assume it's actually a shell command
		 * and add it to the current list of targets.
D 27
		 *
		 * Note that POSIX declares all lines that start with
		 * whitespace are shell commands, so there's no need to check
		 * here...
E 27
		 */
I 27
#ifndef POSIX
E 27
		Boolean	nonSpace = FALSE;
I 27
#endif
E 27
		
		cp = line;
I 27
		if (isspace((unsigned char) line[0])) {
		    while ((*cp != '\0') && isspace((unsigned char) *cp)) {
			cp++;
		    }
		    if (*cp == '\0') {
			goto nextLine;
		    }
E 27
#ifndef POSIX
D 27
		if (line[0] == ' ') {
E 27
		    while ((*cp != ':') && (*cp != '!') && (*cp != '\0')) {
D 27
			if (!isspace(*cp)) {
			    nonSpace = TRUE;
			}
E 27
I 27
			nonSpace = TRUE;
E 27
			cp++;
		    }
I 27
#endif
E 27
		}
		    
I 27
#ifndef POSIX
E 27
		if (*cp == '\0') {
		    if (inLine) {
			Parse_Error (PARSE_WARNING,
				     "Shell command needs a leading tab");
			goto shellCommand;
		    } else if (nonSpace) {
			Parse_Error (PARSE_FATAL, "Missing operator");
		    }
		} else {
#endif
		    ParseFinishLine();

D 19
		    cp = Var_Subst (line, VAR_CMD, TRUE);
E 19
I 19
		    cp = Var_Subst (NULL, line, VAR_CMD, TRUE);
E 19
		    free (line);
		    line = cp;
		    
		    /*
		     * Need a non-circular list for the target nodes 
		     */
I 27
		    if (targets)
			Lst_Destroy(targets, NOFREE);

E 27
		    targets = Lst_Init (FALSE);
		    inLine = TRUE;
		    
		    ParseDoDependency (line);
#ifndef POSIX
		}
#endif
	    }

	    nextLine:

	    free (line);
	}
	/*
	 * Reached EOF, but it may be just EOF of an include file... 
	 */
D 18
    } while (ParseEOF() == CONTINUE);
E 18
I 18
    } while (ParseEOF(1) == CONTINUE);
E 18

    /*
     * Make sure conditionals are clean
     */
    Cond_End();

    if (fatals) {
	fprintf (stderr, "Fatal errors encountered -- cannot continue\n");
	exit (1);
    }
}
D 3

E 3
I 3

E 3
/*-
 *---------------------------------------------------------------------
 * Parse_Init --
 *	initialize the parsing module
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	the parseIncPath list is initialized...
 *---------------------------------------------------------------------
 */
I 19
void
E 19
Parse_Init ()
{
D 8
    char    	*cp;
    char    	*start;
    static char syspath[] = DEFSYSPATH;	/* Avoid faults on read-only string
					 * constant... */
E 8
I 8
D 19
	char *cp, *start;
E 19
I 19
	char *cp = NULL, *start;
E 19
					/* avoid faults on read-only strings */
	static char syspath[] = _PATH_DEFSYSPATH;
E 8
    
    mainNode = NILGNODE;
    parseIncPath = Lst_Init (FALSE);
    sysIncPath = Lst_Init (FALSE);
    includes = Lst_Init (FALSE);
I 27
    targCmds = Lst_Init (FALSE);
E 27

    /*
     * Add the directories from the DEFSYSPATH (more than one may be given
     * as dir1:...:dirn) to the system include path.
     */
    for (start = syspath; *start != '\0'; start = cp) {
D 19
	for (cp = start; *cp != '\0' && *cp != ':'; cp++) {
	    ;
	}
E 19
I 19
	for (cp = start; *cp != '\0' && *cp != ':'; cp++) 
	    continue;
E 19
	if (*cp == '\0') {
	    Dir_AddDir(sysIncPath, start);
	} else {
	    *cp++ = '\0';
	    Dir_AddDir(sysIncPath, start);
	}
    }
}
I 27

void
Parse_End()
{
    Lst_Destroy(targCmds, (void (*) __P((ClientData))) free);
    if (targets)
	Lst_Destroy(targets, NOFREE);
    Lst_Destroy(sysIncPath, Dir_Destroy);
    Lst_Destroy(parseIncPath, Dir_Destroy);
    Lst_Destroy(includes, NOFREE);	/* Should be empty now */
}
    
E 27
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Parse_MainName --
 *	Return a Lst of the main target to create for main()'s sake. If
 *	no such target exists, we Punt with an obnoxious error message.
 *
 * Results:
 *	A Lst of the single node to create.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
Lst
Parse_MainName()
{
    Lst           main;	/* result list */

    main = Lst_Init (FALSE);

    if (mainNode == NILGNODE) {
D 17
	Punt ("I don't know what to DO!\n");
E 17
I 17
	Punt ("make: no target to make.\n");
E 17
    	/*NOTREACHED*/
    } else if (mainNode->type & OP_DOUBLEDEP) {
I 24
	(void) Lst_AtEnd (main, (ClientData)mainNode);
E 24
	Lst_Concat(main, mainNode->cohorts, LST_CONCNEW);
    }
D 24
    (void) Lst_AtEnd (main, (ClientData)mainNode);
E 24
I 24
    else
	(void) Lst_AtEnd (main, (ClientData)mainNode);
E 24
    return (main);
}
E 1
