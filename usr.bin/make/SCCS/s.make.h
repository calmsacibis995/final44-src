h12204
s 00001/00000/00339
d D 8.3 95/06/13 15:40:30 christos 17 16
c - posix compliance: Don't create .[A-Z]* targets 
c - support for .PHONY targets
e
s 00014/00006/00325
d D 8.2 95/04/28 17:08:19 christos 16 15
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00329
d D 8.1 93/06/06 15:16:24 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00002/00313
d D 5.14 93/05/24 14:45:51 bostic 14 13
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00000/00000/00315
d D 5.13 91/03/01 15:07:26 bostic 13 12
c ANSI
e
s 00001/00011/00314
d D 5.12 90/06/01 17:09:10 bostic 12 11
c new copyright notice
e
s 00001/00001/00324
d D 5.11 90/05/15 19:55:35 bostic 11 10
c string.h is ANSI C include file
e
s 00003/00004/00322
d D 5.10 90/03/21 10:52:53 bostic 10 9
c remove DEBUG_PARSE, never used
e
s 00001/00001/00325
d D 5.9 90/03/19 16:24:04 bostic 9 8
c rename DONTCARE as OPTIONAL
e
s 00018/00019/00308
d D 5.8 90/03/19 11:26:43 bostic 8 7
c redo DEBUG stuff, adding DEBUG_GRAPH[12], deleting -dr.
e
s 00001/00003/00326
d D 5.7 90/03/19 09:56:40 bostic 7 6
c I might as well use nonints, too, but I don't like it much
e
s 00000/00010/00329
d D 5.6 90/03/12 12:19:59 bostic 6 5
c rework to always be "make".  Deleted -M, -B, -C, -v.  Partial deletion
c of .NULL.  Never remove leading components in file search.  # is always a
c comment.  Print usage line, not message.  Make vararg'd routines right.
e
s 00000/00016/00339
d D 5.5 90/03/12 10:42:34 bostic 5 4
c remove rmt.c module, most of remote support, including .EXPORT,
c .EXPORTSAME, .NOEXPORT, -X and -x
e
s 00000/00010/00355
d D 5.4 90/03/12 09:30:20 bostic 4 3
c Remove NEED_FD_SET, FD_SETSIZE, NO_WAIT3, NO_VFORK, LIBTOC
e
s 00006/00005/00359
d D 5.3 90/03/12 09:19:49 bostic 3 2
c missed two Str_New's, include strings.h in make.h for everybody
e
s 00027/00013/00341
d D 5.2 90/03/11 15:39:10 bostic 2 1
c add Berkeley specific copyright notice
e
s 00354/00000/00000
d D 5.1 90/03/11 15:27:40 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * make.h --
 *	The global definitions for pmake
 *
 * Copyright (c) 1988, 1989 by the Regents of the University of California
E 2
I 2
/*
D 15
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
E 2
 * Copyright (c) 1988, 1989 by Adam de Boor
E 15
I 15
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
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
D 2
 *	"$Id: make.h,v 1.42 89/11/14 13:44:42 adam Exp $ SPRITE (Berkeley)"
E 2
I 2
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
 *
 *	%W% (Berkeley) %G%
 */

/*-
 * make.h --
 *	The global definitions for pmake
E 2
 */

#ifndef _MAKE_H_
#define _MAKE_H_

D 3
#include    <sys/types.h>
#include    "sprite.h"
#include    <ctype.h>
#include    "lst.h"
#include    "config.h"
E 3
I 3
#include <sys/types.h>
I 14
#include <stdio.h>
E 14
D 11
#include <strings.h>
E 11
I 11
#include <string.h>
E 11
#include <ctype.h>
I 16
#ifndef MAKE_BOOTSTRAP
E 16
I 14
#include <sys/cdefs.h>
I 16
#else
#if defined(__STDC__) || defined(__cplusplus)
#define	__P(protos)	protos		/* full-blown ANSI C */
#else
#define	__P(protos)	()		/* traditional C preprocessor */    
#endif
#endif
E 16
#if __STDC__
#include <stdlib.h>
#include <unistd.h>
#endif
E 14
#include "sprite.h"
#include "lst.h"
#include "config.h"
I 14
#include "buf.h"
E 14
E 3

D 4
#ifdef NO_VFORK
#define vfork fork
#else

#ifdef sparc
#include    <vfork.h>
#endif

#endif /* NO_VFORK */

E 4
/*-
 * The structure for an individual graph node. Each node has several
 * pieces of data associated with it.
 *	1) the name of the target it describes
 *	2) the location of the target file in the file system.
 *	3) the type of operator used to define its sources (qv. parse.c)
 *	4) whether it is involved in this invocation of make
 *	5) whether the target has been remade
 *	6) whether any of its children has been remade
 *	7) the number of its children that are, as yet, unmade
 *	8) its modification time
 *	9) the modification time of its youngest child (qv. make.c)
 *	10) a list of nodes for which this is a source
 *	11) a list of nodes on which this depends
 *	12) a list of nodes that depend on this, as gleaned from the
 *	    transformation rules.
 *	13) a list of nodes of the same name created by the :: operator
 *	14) a list of nodes that must be made (if they're made) before
 *	    this node can be, but that do no enter into the datedness of
 *	    this node.
 *	15) a list of nodes that must be made (if they're made) after
 *	    this node is, but that do not depend on this node, in the
 *	    normal sense.
 *	16) a Lst of ``local'' variables that are specific to this target
 *	   and this target only (qv. var.c [$@ $< $?, etc.])
 *	17) a Lst of strings that are commands to be given to a shell
 *	   to create this target. 
 */
typedef struct GNode {
    char            *name;     	/* The target's name */
    char    	    *path;     	/* The full pathname of the file */
    int             type;      	/* Its type (see the OP flags, below) */

    Boolean         make;      	/* TRUE if this target needs to be remade */
    enum {
	UNMADE, BEINGMADE, MADE, UPTODATE, ERROR, ABORTED,
	CYCLE, ENDCYCLE,
    }	    	    made;    	/* Set to reflect the state of processing
				 * on this node:
				 *  UNMADE - Not examined yet
				 *  BEINGMADE - Target is already being made.
				 *  	Indicates a cycle in the graph. (compat
				 *  	mode only)
				 *  MADE - Was out-of-date and has been made
				 *  UPTODATE - Was already up-to-date
				 *  ERROR - An error occured while it was being
				 *  	made (used only in compat mode)
				 *  ABORTED - The target was aborted due to
				 *  	an error making an inferior (compat).
				 *  CYCLE - Marked as potentially being part of
				 *  	a graph cycle. If we come back to a
				 *  	node marked this way, it is printed
				 *  	and 'made' is changed to ENDCYCLE.
				 *  ENDCYCLE - the cycle has been completely
				 *  	printed. Go back and unmark all its
				 *  	members.
				 */
    Boolean 	    childMade; 	/* TRUE if one of this target's children was
				 * made */
    int             unmade;    	/* The number of unmade children */

    int             mtime;     	/* Its modification time */
    int        	    cmtime;    	/* The modification time of its youngest
				 * child */

    Lst     	    iParents;  	/* Links to parents for which this is an
				 * implied source, if any */
    Lst	    	    cohorts;  	/* Other nodes for the :: operator */
    Lst             parents;   	/* Nodes that depend on this one */
    Lst             children;  	/* Nodes on which this one depends */
    Lst	    	    successors;	/* Nodes that must be made after this one */
    Lst	    	    preds;  	/* Nodes that must be made before this one */

    Lst             context;   	/* The local variables */
    Lst             commands;  	/* Creation commands */

    struct _Suff    *suffix;	/* Suffix for the node (determined by
				 * Suff_FindDeps and opaque to everyone
				 * but the Suff module) */
} GNode;

/*
 * Manifest constants 
 */
#define NILGNODE	((GNode *) NIL)

/*
 * The OP_ constants are used when parsing a dependency line as a way of
 * communicating to other parts of the program the way in which a target
 * should be made. These constants are bitwise-OR'ed together and
 * placed in the 'type' field of each node. Any node that has
 * a 'type' field which satisfies the OP_NOP function was never never on
 * the lefthand side of an operator, though it may have been on the
 * righthand side... 
 */
#define OP_DEPENDS	0x00000001  /* Execution of commands depends on
				     * kids (:) */
#define OP_FORCE	0x00000002  /* Always execute commands (!) */
#define OP_DOUBLEDEP	0x00000004  /* Execution of commands depends on kids
				     * per line (::) */
#define OP_OPMASK	(OP_DEPENDS|OP_FORCE|OP_DOUBLEDEP)

D 9
#define OP_DONTCARE	0x00000008  /* Don't care if the target doesn't
E 9
I 9
#define OP_OPTIONAL	0x00000008  /* Don't care if the target doesn't
E 9
				     * exist and can't be created */
#define OP_USE		0x00000010  /* Use associated commands for parents */
#define OP_EXEC	  	0x00000020  /* Target is never out of date, but always
				     * execute commands anyway. Its time
				     * doesn't matter, so it has none...sort
				     * of */
#define OP_IGNORE	0x00000040  /* Ignore errors when creating the node */
#define OP_PRECIOUS	0x00000080  /* Don't remove the target when
				     * interrupted */
#define OP_SILENT	0x00000100  /* Don't echo commands when executed */
#define OP_MAKE		0x00000200  /* Target is a recurrsive make so its
				     * commands should always be executed when
				     * it is out of date, regardless of the
				     * state of the -n or -t flags */
#define OP_JOIN 	0x00000400  /* Target is out-of-date only if any of its
				     * children was out-of-date */
D 5
#define OP_EXPORT 	0x00000800  /* UNUSED: The creation of the target
				     * should be sent somewhere else, if
				     * possible. */
#define OP_NOEXPORT	0x00001000  /* The creation should not be sent
				     * elsewhere */
#define OP_EXPORTSAME	0x00002000  /* Export only to machine with same
				     * architecture */
E 5
#define OP_INVISIBLE	0x00004000  /* The node is invisible to its parents.
				     * I.e. it doesn't show up in the parents's
				     * local variables. */
#define OP_NOTMAIN	0x00008000  /* The node is exempt from normal 'main
				     * target' processing in parse.c */
I 17
#define OP_PHONY	0x00010000  /* Not a file target; run always */
E 17
D 5
/*XXX*/
#define OP_M68020   	0x00010000  /* Command must be run on a 68020 */
E 5
/* Attributes applied by PMake */
#define OP_TRANSFORM	0x80000000  /* The node is a transformation rule */
#define OP_MEMBER 	0x40000000  /* Target is a member of an archive */
#define OP_LIB	  	0x20000000  /* Target is a library */
#define OP_ARCHV  	0x10000000  /* Target is an archive construct */
#define OP_HAS_COMMANDS	0x08000000  /* Target has all the commands it should.
				     * Used when parsing to catch multiple
				     * commands for a target */
#define OP_SAVE_CMDS	0x04000000  /* Saving commands on .END (Compat) */
#define OP_DEPS_FOUND	0x02000000  /* Already processed by Suff_FindDeps */

/*
 * OP_NOP will return TRUE if the node with the given type was not the
 * object of a dependency operator
 */
#define OP_NOP(t)	(((t) & OP_OPMASK) == 0x00000000)

/*
 * The TARG_ constants are used when calling the Targ_FindNode and
 * Targ_FindList functions in targ.c. They simply tell the functions what to
 * do if the desired node(s) is (are) not found. If the TARG_CREATE constant
 * is given, a new, empty node will be created for the target, placed in the
 * table of all targets and its address returned. If TARG_NOCREATE is given,
 * a NIL pointer will be returned. 
 */
#define TARG_CREATE	0x01	  /* create node if not found */
#define TARG_NOCREATE	0x00	  /* don't create it */

/*
 * There are several places where expandable buffers are used (parse.c and
 * var.c). This constant is merely the starting point for those buffers. If
 * lines tend to be much shorter than this, it would be best to reduce BSIZE.
 * If longer, it should be increased. Reducing it will cause more copying to
 * be done for longer lines, but will save space for shorter ones. In any
 * case, it ought to be a power of two simply because most storage allocation
 * schemes allocate in powers of two. 
 */
D 14
#define BSIZE		256	/* starting size for expandable buffers */
E 14
I 14
#define MAKE_BSIZE		256	/* starting size for expandable buffers */
E 14

/*
 * These constants are all used by the Str_Concat function to decide how the
 * final string should look. If STR_ADDSPACE is given, a space will be
 * placed between the two strings. If STR_ADDSLASH is given, a '/' will
 * be used instead of a space. If neither is given, no intervening characters
 * will be placed between the two strings in the final output. If the
 * STR_DOFREE bit is set, the two input strings will be freed before
 * Str_Concat returns. 
 */
#define STR_ADDSPACE	0x01	/* add a space when Str_Concat'ing */
#define STR_DOFREE	0x02	/* free source strings after concatenation */
#define STR_ADDSLASH	0x04	/* add a slash when Str_Concat'ing */

/*
 * Error levels for parsing. PARSE_FATAL means the process cannot continue
 * once the makefile has been parsed. PARSE_WARNING means it can. Passed
 * as the first argument to Parse_Error.
 */
#define PARSE_WARNING	2
#define PARSE_FATAL	1

/*
 * Values returned by Cond_Eval.
 */
#define COND_PARSE	0   	/* Parse the next lines */
#define COND_SKIP 	1   	/* Skip the next lines */
#define COND_INVALID	2   	/* Not a conditional statement */

/*
 * Definitions for the "local" variables. Used only for clarity.
 */
#define TARGET	  	  "@" 	/* Target of dependency */
#define OODATE	  	  "?" 	/* All out-of-date sources */
#define ALLSRC	  	  ">" 	/* All sources */
#define IMPSRC	  	  "<" 	/* Source implied by transformation */
#define PREFIX	  	  "*" 	/* Common prefix */
#define ARCHIVE	  	  "!" 	/* Archive in "archive(member)" syntax */
#define MEMBER	  	  "%" 	/* Member in "archive(member)" syntax */

#define FTARGET           "@F"  /* file part of TARGET */
#define DTARGET           "@D"  /* directory part of TARGET */
#define FIMPSRC           "<F"  /* file part of IMPSRC */
#define DIMPSRC           "<D"  /* directory part of IMPSRC */
#define FPREFIX           "*F"  /* file part of PREFIX */
#define DPREFIX           "*D"  /* directory part of PREFIX */

/*
 * Global Variables 
 */
extern Lst  	create;	    	/* The list of target names specified on the
				 * command line. used to resolve #if
				 * make(...) statements */
extern Lst     	dirSearchPath; 	/* The list of directories to search when
				 * looking for targets */

I 14
extern Boolean	compatMake;	/* True if we are make compatible */
E 14
extern Boolean	ignoreErrors;  	/* True if should ignore all errors */
extern Boolean  beSilent;    	/* True if should print no commands */
extern Boolean  noExecute;    	/* True if should execute nothing */
extern Boolean  allPrecious;   	/* True if every target is precious */
extern Boolean  keepgoing;    	/* True if should continue on unaffected
				 * portions of the graph when have an error
				 * in one portion */
extern Boolean 	touchFlag;    	/* TRUE if targets should just be 'touched'
				 * if out of date. Set by the -t flag */
extern Boolean  usePipes;    	/* TRUE if should capture the output of
				 * subshells by means of pipes. Otherwise it
				 * is routed to temporary files from which it
				 * is retrieved when the shell exits */
extern Boolean 	queryFlag;    	/* TRUE if we aren't supposed to really make
				 * anything, just see if the targets are out-
				 * of-date */

D 8
extern Boolean	noWarnings;    	/* TRUE if should not print warning messages */
E 8
D 5
extern Boolean  noExport;    	/* TRUE if should not export any jobs */
E 5
extern Boolean	checkEnvFirst;	/* TRUE if environment should be searched for
				 * variables before the global context */

extern GNode    *DEFAULT;    	/* .DEFAULT rule */

extern GNode    *VAR_GLOBAL;   	/* Variables defined in a global context, e.g
				 * in the Makefile itself */
extern GNode    *VAR_CMD;    	/* Variables defined on the command line */
extern char    	var_Error[];   	/* Value returned by Var_Parse when an error
				 * is encountered. It actually points to
				 * an empty string, so naive callers needn't
				 * worry about it. */

extern time_t 	now;	    	/* The time at the start of this whole
				 * process */

D 6
/*
 * Three levels of compatibility. amMake incorporates backwards and oldVars,
 * backwards incorporates oldVars.
 */
extern Boolean	amMake;	    	/* Go all the way to backwards compatibility:
				 *	- Depth-first traversal of the graph
				 *	- No paralellism */
extern Boolean  backwards;    	/* Go halfway to backwards compatibility:
				 *	- One shell per command */
E 6
extern Boolean	oldVars;    	/* Do old-style variable substitution */
D 6
extern Boolean  sysVmake;    	/* Imitate System V make in anything weird */
E 6

/*
D 8
 * Debug control:
 *	There is one bit per module. It is up to the module what debug
E 8
I 8
 * debug control:
 *	There is one bit per module.  It is up to the module what debug
E 8
 *	information to print.
D 8
 *	DEBUG(module) returns TRUE if debugging is on for that module.
E 8
 */
D 8
extern int    	debug;
#define DEBUG_SUFF	0x00000001
#define DEBUG_MAKE	0x00000002
#define DEBUG_JOB 	0x00000004
#define DEBUG_TARG	0x00000008
#define DEBUG_DIR 	0x00000010
#define DEBUG_VAR 	0x00000020
#define DEBUG_COND	0x00000040
#define DEBUG_PARSE	0x00000080
#define DEBUG_RMT 	0x00000100
#define DEBUG_ARCH	0x00000200
E 8
I 8
extern int debug;
#define	DEBUG_ARCH	0x0001
#define	DEBUG_COND	0x0002
#define	DEBUG_DIR	0x0004
#define	DEBUG_GRAPH1	0x0008
#define	DEBUG_GRAPH2	0x0010
#define	DEBUG_JOB	0x0020
#define	DEBUG_MAKE	0x0040
D 10
#define	DEBUG_PARSE	0x0080
#define	DEBUG_SUFF	0x0100
#define	DEBUG_TARG	0x0200
#define	DEBUG_VAR	0x0400
E 10
I 10
#define	DEBUG_SUFF	0x0080
#define	DEBUG_TARG	0x0100
#define	DEBUG_VAR	0x0200
I 14
#define DEBUG_FOR	0x0400
E 14
E 10
E 8

D 8
#ifndef __STDC__
E 8
I 8
#ifdef __STDC__
#define CONCAT(a,b)	a##b
#else
E 8
#define I(a)	  	a
#define CONCAT(a,b)	I(a)b
D 8
#else
#define CONCAT(a,b)	a##b
E 8
#endif /* __STDC__ */

D 8
#define DEBUG(module)	(debug & CONCAT(DEBUG_,module))
E 8
I 8
#define	DEBUG(module)	(debug & CONCAT(DEBUG_,module))
E 8

/*
 * Since there are so many, all functions that return non-integer values are
 * extracted by means of a sed script or two and stuck in the file "nonints.h"
 */
D 7
#include	"nonints.h"

D 5
#ifdef Sprite
#define Str_FindSubstring(s1, s2) strstr(s1, s2)
#endif /* Sprite */

extern char *index();
extern char *rindex();
E 5
extern char *malloc();
E 7
I 7
#include "nonints.h"
E 7

D 14
#endif _MAKE_H_
E 14
I 14
D 16
void	Make_DoAllVar __P((GNode *));
int	Make_HandleUse __P((GNode *, GNode *));
Boolean	Make_OODate __P((GNode *));
Boolean	Make_Run __P((Lst));
int	Make_TimeStamp __P((GNode *, GNode *));
void	Make_Update __P((GNode *));
E 16
I 16
int Make_TimeStamp __P((GNode *, GNode *));
Boolean Make_OODate __P((GNode *));
int Make_HandleUse __P((GNode *, GNode *));
void Make_Update __P((GNode *));
void Make_DoAllVar __P((GNode *));
Boolean Make_Run __P((Lst));
E 16

#endif /* _MAKE_H_ */
E 14
E 1
