h63140
s 00041/00032/00583
d D 8.3 95/04/28 17:07:58 christos 15 14
c Updated to the latest version from the NetBSD source
e
s 00012/00000/00603
d D 8.2 94/03/19 15:50:45 christos 14 13
c avoid clobbered variable warnings; eat leading spaces from cmd
e
s 00002/00002/00601
d D 8.1 93/06/06 15:14:19 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00599
d D 5.12 93/05/24 18:22:53 bostic 12 11
c merge in rev 5.8->5.9 change
e
s 00005/00003/00595
d D 5.11 93/05/24 18:21:29 bostic 11 10
c merge in rev 5.7->5.8 change
e
s 00018/00013/00580
d D 5.10 93/05/24 14:45:28 bostic 10 9
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00004/00001/00589
d D 5.9 93/05/07 19:02:24 hibler 9 8
c don't unlink directories (see job.c SCCS rev 5.16)
e
s 00001/00001/00589
d D 5.8 91/10/26 23:34:40 torek 8 7
c signal.h is not sys/signal.h
e
s 00002/00002/00588
d D 5.7 91/03/01 15:07:21 bostic 7 6
c ANSI
e
s 00001/00011/00589
d D 5.6 90/06/01 17:07:06 bostic 6 5
c new copyright notice
e
s 00002/00004/00598
d D 5.5 90/03/19 11:19:08 bostic 5 4
c delete -W (noWarnings) flag
e
s 00003/00011/00599
d D 5.4 90/03/19 09:52:44 bostic 4 3
c Str_BreakString -> brk_string; no longer need Str_FreeVec
e
s 00003/00017/00607
d D 5.3 90/03/12 10:42:02 bostic 3 2
c remove rmt.c module, most of remote support, including .EXPORT,
c .EXPORTSAME, .NOEXPORT, -X and -x
e
s 00026/00015/00598
d D 5.2 90/03/11 15:38:26 bostic 2 1
c add Berkeley specific copyright notice
e
s 00613/00000/00000
d D 5.1 90/03/11 15:27:21 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
D 13
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 13
I 13
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
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
 * compat.c --
 *	The routines in this file implement the full-compatibility
 *	mode of PMake. Most of the special functionality of PMake
 *	is available in this mode. Things not supported:
 *	    - different shells.
 *	    - friendly variable substitution.
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
 *	Compat_Run	    Initialize things for this module and recreate
 *	    	  	    thems as need creatin'
 */
D 2
#ifndef lint
static char *rcsid = "$Id: compat.c,v 1.24 89/11/14 13:43:41 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

I 15
#include    <stdio.h>
E 15
D 11
#include    <stdio.h>
E 11
#include    <sys/types.h>
I 12
D 15
#include    <sys/stat.h>
E 15
I 15
#include    <sys/signal.h>
E 15
E 12
I 9
D 10
#include    <sys/stat.h>
E 10
I 10
D 11
#include    <sys/signal.h>
E 11
E 10
E 9
D 8
#include    <sys/signal.h>
E 8
#include    <sys/wait.h>
D 11
#include    <sys/errno.h>
E 11
I 11
D 15

E 15
I 15
#include    <sys/errno.h>
#include    <sys/stat.h>
E 15
E 11
I 8
D 10
#include    <signal.h>
E 10
E 8
#include    <ctype.h>
I 11
D 15
#include    <errno.h>
#include    <signal.h>
#include    <stdio.h>

E 15
E 11
#include    "make.h"
I 10
#include    "hash.h"
#include    "dir.h"
#include    "job.h"
E 10
extern int errno;

/*
 * The following array is used to make a fast determination of which
 * characters are interpreted specially by the shell.  If a command
 * contains any of these characters, it is executed by the shell, not
 * directly by us.
 */

static char 	    meta[256];

static GNode	    *curTarg = NILGNODE;
static GNode	    *ENDNode;
D 10
static int  	    CompatRunCommand();
E 10
I 10
static void CompatInterrupt __P((int));
D 15
static int CompatRunCommand __P((char *, GNode *));
static int CompatMake __P((GNode *, GNode *));
E 15
I 15
static int CompatRunCommand __P((ClientData, ClientData));
static int CompatMake __P((ClientData, ClientData));
E 15
E 10

/*-
 *-----------------------------------------------------------------------
 * CompatInterrupt --
 *	Interrupt the creation of the current target and remove it if
 *	it ain't precious.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The target is removed and the process exits. If .INTERRUPT exists,
 *	its commands are run first WITH INTERRUPTS IGNORED..
 *
 *-----------------------------------------------------------------------
 */
D 7
static int
E 7
I 7
static void
E 7
CompatInterrupt (signo)
    int	    signo;
{
I 12
D 15
    struct stat sb;
E 15
E 12
    GNode   *gn;
I 9
D 10
    struct stat sb;
E 10
E 9
    
    if ((curTarg != NILGNODE) && !Targ_Precious (curTarg)) {
D 15
	char 	  *file = Var_Value (TARGET, curTarg);
E 15
I 15
	char	  *p1;
	char 	  *file = Var_Value (TARGET, curTarg, &p1);
	struct stat st;
E 15

D 9
	if (unlink (file) == SUCCESS) {
E 9
I 9
D 10
	if (!stat(file, &sb) && S_ISREG(sb.st_mode) &&
	    unlink (file) == SUCCESS) {
E 10
I 10
D 12
	if (unlink (file) == SUCCESS) {
E 12
I 12
D 15
	if (!stat(file, &sb) && S_ISREG(sb.st_mode) &&
	    unlink (file) == SUCCESS) {
E 15
I 15
	if (!noExecute && lstat(file, &st) != -1 && !S_ISDIR(st.st_mode) && 
	    unlink(file) != -1) {
E 15
E 12
E 10
E 9
	    printf ("*** %s removed\n", file);
	}
I 15
	if (p1)
	    free(p1);
E 15

	/*
	 * Run .INTERRUPT only if hit with interrupt signal
	 */
	if (signo == SIGINT) {
	    gn = Targ_FindNode(".INTERRUPT", TARG_NOCREATE);
	    if (gn != NILGNODE) {
		Lst_ForEach(gn->commands, CompatRunCommand, (ClientData)gn);
	    }
	}
I 15

E 15
    }
D 15
    exit (0);
E 15
I 15
    exit (signo);
E 15
}

/*-
 *-----------------------------------------------------------------------
 * CompatRunCommand --
 *	Execute the next command for a target. If the command returns an
 *	error, the node's made field is set to ERROR and creation stops.
 *
 * Results:
 *	0 if the command succeeded, 1 if an error occurred.
 *
 * Side Effects:
 *	The node's 'made' field may be set to ERROR.
 *
 *-----------------------------------------------------------------------
 */
static int
D 15
CompatRunCommand (cmd, gn)
    char    	  *cmd;	    	/* Command to execute */
    GNode   	  *gn;    	/* Node from which the command came */
E 15
I 15
CompatRunCommand (cmdp, gnp)
    ClientData    cmdp;	    	/* Command to execute */
    ClientData    gnp;    	/* Node from which the command came */
E 15
{
    char    	  *cmdStart;	/* Start of expanded command */
    register char *cp;
    Boolean 	  silent,   	/* Don't print command */
		  errCheck; 	/* Check errors */
    union wait 	  reason;   	/* Reason for child's death */
    int	    	  status;   	/* Description of child's death */
    int	    	  cpid;	    	/* Child actually found */
D 10
    int	    	  numWritten;	/* Number of bytes written for error message */
E 10
    ReturnStatus  stat;	    	/* Status of fork */
    LstNode 	  cmdNode;  	/* Node where current command is located */
    char    	  **av;	    	/* Argument vector for thing to exec */
    int	    	  argc;	    	/* Number of arguments in av or 0 if not
				 * dynamically allocated */
    Boolean 	  local;    	/* TRUE if command should be executed
				 * locally */
I 15
    char	  *cmd = (char *) cmdp;
    GNode	  *gn = (GNode *) gnp;
E 15

I 14
D 15
    /*  
E 15
I 15
    /* 
E 15
     * Avoid clobbered variable warnings by forcing the compiler
     * to ``unregister'' variables
D 15
     */ 
E 15
I 15
     */
E 15
#if __GNUC__
D 15
    (void) &av; 
E 15
I 15
    (void) &av;
E 15
    (void) &errCheck;
D 15
#endif 

E 15
I 15
#endif
E 15
E 14
    silent = gn->type & OP_SILENT;
    errCheck = !(gn->type & OP_IGNORE);

    cmdNode = Lst_Member (gn->commands, (ClientData)cmd);
D 10
    cmdStart = Var_Subst (cmd, gn, FALSE);
E 10
I 10
    cmdStart = Var_Subst (NULL, cmd, gn, FALSE);
E 10

    /*
D 4
     * Str_BreakString will return an argv with a NULL in av[1], thus causing
E 4
I 4
     * brk_string will return an argv with a NULL in av[1], thus causing
E 4
     * execvp to choke and die horribly. Besides, how can we execute a null
     * command? In any case, we warn the user that the command expanded to
     * nothing (is this the right thing to do?).
     */
     
D 5
    if (*cmdStart == '\0') {
	if (!noWarnings) {
	    Error("%s expands to empty string", cmd);
	}
E 5
I 5
    if (*cmdStart == '\0') {
I 15
	free(cmdStart);
E 15
	Error("%s expands to empty string", cmd);
E 5
	return(0);
    } else {
	cmd = cmdStart;
    }
    Lst_Replace (cmdNode, (ClientData)cmdStart);

    if ((gn->type & OP_SAVE_CMDS) && (gn != ENDNode)) {
	(void)Lst_AtEnd(ENDNode->commands, (ClientData)cmdStart);
	return(0);
    } else if (strcmp(cmdStart, "...") == 0) {
	gn->type |= OP_SAVE_CMDS;
	return(0);
    }

    while ((*cmd == '@') || (*cmd == '-')) {
	if (*cmd == '@') {
	    silent = TRUE;
	} else {
	    errCheck = FALSE;
	}
	cmd++;
    }
I 14

    while (isspace((unsigned char)*cmd))
	cmd++;
E 14
    
    /*
     * Search for meta characters in the command. If there are no meta
     * characters, there's no need to execute a shell to execute the
     * command.
     */
D 10
    for (cp = cmd; !meta[*cp]; cp++) {
E 10
I 10
    for (cp = cmd; !meta[(unsigned char)*cp]; cp++) {
E 10
	continue;
    }

    /*
     * Print the command before echoing if we're not supposed to be quiet for
     * this one. We also print the command if -n given.
     */
    if (!silent || noExecute) {
	printf ("%s\n", cmd);
	fflush(stdout);
    }

    /*
     * If we're not supposed to execute any commands, this is as far as
     * we go...
     */
    if (noExecute) {
	return (0);
    }
    
    if (*cp != '\0') {
	/*
	 * If *cp isn't the null character, we hit a "meta" character and
	 * need to pass the command off to the shell. We give the shell the
	 * -e flag as well as -c if it's supposed to exit when it hits an
	 * error.
	 */
	static char	*shargv[4] = { "/bin/sh" };

	shargv[1] = (errCheck ? "-ec" : "-c");
	shargv[2] = cmd;
	shargv[3] = (char *)NULL;
	av = shargv;
	argc = 0;
    } else {
	/*
	 * No meta-characters, so no need to exec a shell. Break the command
	 * into words to form an argument vector we can execute.
D 4
	 * Str_BreakString sticks our name in av[0], so we have to
E 4
I 4
	 * brk_string sticks our name in av[0], so we have to
E 4
	 * skip over it...
	 */
D 4
	av = Str_BreakString(cmd, " \t", "\n", &argc);
E 4
I 4
D 15
	av = brk_string(cmd, &argc);
E 15
I 15
	av = brk_string(cmd, &argc, TRUE);
E 15
E 4
	av += 1;
    }
    
D 3
    /*
     * If the job has not been marked unexportable, tell the Rmt module we've
     * got something for it...local is set TRUE if the job should be run
     * locally.
     */
    if (!(gn->type & OP_NOEXPORT)) {
	local = !Rmt_Begin(av[0], av, gn);
    } else {
	local = TRUE;
    }
E 3
I 3
    local = TRUE;
E 3

    /*
     * Fork and execute the single command. If the fork fails, we abort.
     */
    cpid = vfork();
    if (cpid < 0) {
	Fatal("Could not fork");
    }
    if (cpid == 0) {
	if (local) {
	    execvp(av[0], av);
D 10
	    numWritten = write (2, av[0], strlen (av[0]));
	    numWritten = write (2, ": not found\n", sizeof(": not found"));
E 10
I 10
	    (void) write (2, av[0], strlen (av[0]));
	    (void) write (2, ": not found\n", sizeof(": not found"));
E 10
	} else {
D 3
	    Rmt_Exec(av[0], av, FALSE);
E 3
I 3
	    (void)execv(av[0], av);
E 3
	}
	exit(1);
D 4
    } else if (argc != 0) {
	/*
	 * If there's a vector that needs freeing (the command was executed
	 * directly), do so now, being sure to back up the argument vector
	 * to where it started...
	 */
	av -= 1;
	Str_FreeVec (argc, av);
E 4
    }
I 15
    free(cmdStart);
    Lst_Replace (cmdNode, (ClientData) NULL);
E 15
    
    /*
     * The child is off and running. Now all we can do is wait...
     */
    while (1) {
D 15
	int 	  id;
E 15

D 15
	if (!local) {
D 3
	    id = Rmt_LastID(cpid);
E 3
I 3
	    id = 0;
E 3
	}

E 15
D 7
	while ((stat = wait(&reason)) != cpid) {
E 7
I 7
	while ((stat = wait((int *)&reason)) != cpid) {
E 7
	    if (stat == -1 && errno != EINTR) {
		break;
	    }
	}
	
D 3
	if (!local) {
	    Rmt_Done(id);
	}
	

E 3
	if (stat > -1) {
	    if (WIFSTOPPED(reason)) {
		status = reason.w_stopval;		/* stopped */
	    } else if (WIFEXITED(reason)) {
		status = reason.w_retcode;		/* exited */
		if (status != 0) {
		    printf ("*** Error code %d", status);
		}
	    } else {
		status = reason.w_termsig;		/* signaled */
		printf ("*** Signal %d", status);
	    } 

	    
	    if (!WIFEXITED(reason) || (status != 0)) {
		if (errCheck) {
		    gn->made = ERROR;
		    if (keepgoing) {
			/*
			 * Abort the current target, but let others
			 * continue.
			 */
			printf (" (continuing)\n");
		    }
		} else {
		    /*
		     * Continue executing commands for this target.
		     * If we return 0, this will happen...
		     */
		    printf (" (ignored)\n");
		    status = 0;
		}
	    }
	    break;
	} else {
	    Fatal ("error in wait: %d", stat);
	    /*NOTREACHED*/
	}
    }

    return (status);
}

/*-
 *-----------------------------------------------------------------------
 * CompatMake --
 *	Make a target.
 *
 * Results:
 *	0
 *
 * Side Effects:
 *	If an error is detected and not being ignored, the process exits.
 *
 *-----------------------------------------------------------------------
 */
static int
D 15
CompatMake (gn, pgn)
    GNode   	  *gn;	    /* The node to make */
    GNode   	  *pgn;	    /* Parent to abort if necessary */
E 15
I 15
CompatMake (gnp, pgnp)
    ClientData	gnp;	    /* The node to make */
    ClientData  pgnp;	    /* Parent to abort if necessary */
E 15
{
I 15
    GNode *gn = (GNode *) gnp;
    GNode *pgn = (GNode *) pgnp;
E 15
    if (gn->type & OP_USE) {
	Make_HandleUse(gn, pgn);
    } else if (gn->made == UNMADE) {
	/*
	 * First mark ourselves to be made, then apply whatever transformations
	 * the suffix module thinks are necessary. Once that's done, we can
	 * descend and make all our children. If any of them has an error
	 * but the -k flag was given, our 'make' field will be set FALSE again.
	 * This is our signal to not attempt to do anything but abort our
	 * parent as well.
	 */
	gn->make = TRUE;
	gn->made = BEINGMADE;
	Suff_FindDeps (gn);
	Lst_ForEach (gn->children, CompatMake, (ClientData)gn);
	if (!gn->make) {
	    gn->made = ABORTED;
	    pgn->make = FALSE;
	    return (0);
	}

	if (Lst_Member (gn->iParents, pgn) != NILLNODE) {
D 15
	    Var_Set (IMPSRC, Var_Value(TARGET, gn), pgn);
E 15
I 15
	    char *p1;
	    Var_Set (IMPSRC, Var_Value(TARGET, gn, &p1), pgn);
	    if (p1)
		free(p1);
E 15
	}
	
	/*
	 * All the children were made ok. Now cmtime contains the modification
	 * time of the newest child, we need to find out if we exist and when
	 * we were modified last. The criteria for datedness are defined by the
	 * Make_OODate function.
	 */
	if (DEBUG(MAKE)) {
	    printf("Examining %s...", gn->name);
	}
	if (! Make_OODate(gn)) {
	    gn->made = UPTODATE;
	    if (DEBUG(MAKE)) {
		printf("up-to-date.\n");
	    }
	    return (0);
	} else if (DEBUG(MAKE)) {
	    printf("out-of-date.\n");
	}

	/*
	 * If the user is just seeing if something is out-of-date, exit now
	 * to tell him/her "yes".
	 */
	if (queryFlag) {
	    exit (-1);
	}

	/*
	 * We need to be re-made. We also have to make sure we've got a $?
	 * variable. To be nice, we also define the $> variable using
	 * Make_DoAllVar().
	 */
	Make_DoAllVar(gn);
		    
	/*
	 * Alter our type to tell if errors should be ignored or things
	 * should not be printed so CompatRunCommand knows what to do.
	 */
	if (Targ_Ignore (gn)) {
	    gn->type |= OP_IGNORE;
	}
	if (Targ_Silent (gn)) {
	    gn->type |= OP_SILENT;
	}

	if (Job_CheckCommands (gn, Fatal)) {
	    /*
	     * Our commands are ok, but we still have to worry about the -t
	     * flag...
	     */
	    if (!touchFlag) {
		curTarg = gn;
		Lst_ForEach (gn->commands, CompatRunCommand, (ClientData)gn);
		curTarg = NILGNODE;
	    } else {
		Job_Touch (gn, gn->type & OP_SILENT);
	    }
	} else {
	    gn->made = ERROR;
	}

	if (gn->made != ERROR) {
	    /*
	     * If the node was made successfully, mark it so, update
	     * its modification time and timestamp all its parents. Note
	     * that for .ZEROTIME targets, the timestamping isn't done.
	     * This is to keep its state from affecting that of its parent.
	     */
	    gn->made = MADE;
#ifndef RECHECK
	    /*
	     * We can't re-stat the thing, but we can at least take care of
	     * rules where a target depends on a source that actually creates
	     * the target, but only if it has changed, e.g.
	     *
	     * parse.h : parse.o
	     *
	     * parse.o : parse.y
	     *  	yacc -d parse.y
	     *  	cc -c y.tab.c
	     *  	mv y.tab.o parse.o
	     *  	cmp -s y.tab.h parse.h || mv y.tab.h parse.h
	     *
	     * In this case, if the definitions produced by yacc haven't
	     * changed from before, parse.h won't have been updated and
	     * gn->mtime will reflect the current modification time for
	     * parse.h. This is something of a kludge, I admit, but it's a
	     * useful one..
	     *
	     * XXX: People like to use a rule like
	     *
	     * FRC:
	     *
	     * To force things that depend on FRC to be made, so we have to
	     * check for gn->children being empty as well...
	     */
	    if (!Lst_IsEmpty(gn->commands) || Lst_IsEmpty(gn->children)) {
		gn->mtime = now;
	    }
#else
	    /*
	     * This is what Make does and it's actually a good thing, as it
	     * allows rules like
	     *
	     *	cmp -s y.tab.h parse.h || cp y.tab.h parse.h
	     *
	     * to function as intended. Unfortunately, thanks to the stateless
	     * nature of NFS (and the speed of this program), there are times
	     * when the modification time of a file created on a remote
	     * machine will not be modified before the stat() implied by
	     * the Dir_MTime occurs, thus leading us to believe that the file
	     * is unchanged, wreaking havoc with files that depend on this one.
	     *
	     * I have decided it is better to make too much than to make too
	     * little, so this stuff is commented out unless you're sure it's
	     * ok.
	     * -- ardeb 1/12/88
	     */
	    if (noExecute || Dir_MTime(gn) == 0) {
		gn->mtime = now;
	    }
I 10
	    if (gn->cmtime > gn->mtime)
		gn->mtime = gn->cmtime;
E 10
	    if (DEBUG(MAKE)) {
		printf("update time: %s\n", Targ_FmtTime(gn->mtime));
	    }
#endif
	    if (!(gn->type & OP_EXEC)) {
		pgn->childMade = TRUE;
		Make_TimeStamp(pgn, gn);
	    }
	} else if (keepgoing) {
	    pgn->make = FALSE;
	} else {
	    printf ("\n\nStop.\n");
	    exit (1);
	}
    } else if (gn->made == ERROR) {
	/*
	 * Already had an error when making this beastie. Tell the parent
	 * to abort.
	 */
	pgn->make = FALSE;
    } else {
	if (Lst_Member (gn->iParents, pgn) != NILLNODE) {
D 15
	    Var_Set (IMPSRC, Var_Value(TARGET, gn), pgn);
E 15
I 15
	    char *p1;
	    Var_Set (IMPSRC, Var_Value(TARGET, gn, &p1), pgn);
	    if (p1)
		free(p1);
E 15
	}
	switch(gn->made) {
	    case BEINGMADE:
		Error("Graph cycles through %s\n", gn->name);
		gn->made = ERROR;
		pgn->make = FALSE;
		break;
	    case MADE:
		if ((gn->type & OP_EXEC) == 0) {
		    pgn->childMade = TRUE;
		    Make_TimeStamp(pgn, gn);
		}
		break;
	    case UPTODATE:
		if ((gn->type & OP_EXEC) == 0) {
		    Make_TimeStamp(pgn, gn);
		}
		break;
I 10
	    default:
		break;
E 10
	}
    }

    return (0);
}
	
/*-
 *-----------------------------------------------------------------------
 * Compat_Run --
 *	Initialize this mode and start making.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Guess what?
 *
 *-----------------------------------------------------------------------
 */
void
Compat_Run(targs)
    Lst	    	  targs;    /* List of target nodes to re-create */
{
    char    	  *cp;	    /* Pointer to string of shell meta-characters */
D 10
    GNode   	  *gn;	    /* Current root target */
E 10
I 10
    GNode   	  *gn = NULL;/* Current root target */
E 10
    int	    	  errors;   /* Number of targets not remade due to errors */

    if (signal(SIGINT, SIG_IGN) != SIG_IGN) {
	signal(SIGINT, CompatInterrupt);
    }
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN) {
	signal(SIGTERM, CompatInterrupt);
    }
    if (signal(SIGHUP, SIG_IGN) != SIG_IGN) {
	signal(SIGHUP, CompatInterrupt);
    }
    if (signal(SIGQUIT, SIG_IGN) != SIG_IGN) {
	signal(SIGQUIT, CompatInterrupt);
    }

    for (cp = "#=|^(){};&<>*?[]:$`\\\n"; *cp != '\0'; cp++) {
D 10
	meta[*cp] = 1;
E 10
I 10
	meta[(unsigned char) *cp] = 1;
E 10
    }
    /*
     * The null character serves as a sentinel in the string.
     */
    meta[0] = 1;

    ENDNode = Targ_FindNode(".END", TARG_CREATE);
    /*
     * If the user has defined a .BEGIN target, execute the commands attached
     * to it.
     */
    if (!queryFlag) {
	gn = Targ_FindNode(".BEGIN", TARG_NOCREATE);
	if (gn != NILGNODE) {
	    Lst_ForEach(gn->commands, CompatRunCommand, (ClientData)gn);
	}
    }

    /*
     * For each entry in the list of targets to create, call CompatMake on
     * it to create the thing. CompatMake will leave the 'made' field of gn
     * in one of several states:
     *	    UPTODATE	    gn was already up-to-date
     *	    MADE  	    gn was recreated successfully
     *	    ERROR 	    An error occurred while gn was being created
     *	    ABORTED	    gn was not remade because one of its inferiors
     *	    	  	    could not be made due to errors.
     */
    errors = 0;
    while (!Lst_IsEmpty (targs)) {
	gn = (GNode *) Lst_DeQueue (targs);
	CompatMake (gn, gn);

	if (gn->made == UPTODATE) {
	    printf ("`%s' is up to date.\n", gn->name);
	} else if (gn->made == ABORTED) {
	    printf ("`%s' not remade because of errors.\n", gn->name);
	    errors += 1;
	}
    }

    /*
     * If the user has defined a .END target, run its commands.
     */
    if (errors == 0) {
	Lst_ForEach(ENDNode->commands, CompatRunCommand, (ClientData)gn);
    }
}
E 1
