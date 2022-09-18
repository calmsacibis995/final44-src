h02142
s 00003/00004/00796
d D 8.4 95/06/08 19:50:19 christos 13 12
c Obey PATH=newpath command
e
s 00044/00046/00756
d D 8.3 95/05/04 17:59:40 christos 12 11
c 
e
s 00001/00001/00801
d D 8.2 95/04/28 10:23:59 bostic 11 10
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00004/00030/00798
d D 8.1 93/05/31 15:43:54 bostic 10 7
c fix the SCCS/copyright; 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00028/00800
d R 8.1 93/05/31 15:42:32 bostic 9 7
c fix SCCS coypright/header; 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00826
d R 8.1 93/05/31 15:18:55 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00827
d D 5.7 92/07/16 16:34:17 marc 7 6
c need jobs.h
e
s 00020/00011/00807
d D 5.6 92/07/16 13:56:20 marc 6 5
c print (decompiled) body of function for hash -v (well, as well as can be done anyway...)
e
s 00002/00001/00816
d D 5.5 92/07/15 10:06:49 marc 5 4
c remove executibility check (wasen't checking groups).  not really a good idea in general - should check by executing (re-structure)
e
s 00003/00001/00814
d D 5.4 92/06/23 18:10:32 marc 4 3
c unsetfunc returns an error code
e
s 00039/00003/00776
d D 5.3 92/04/16 14:36:58 marc 3 2
c check if root has dot in PATH and issue warning
e
s 00002/00002/00777
d D 5.2 91/03/13 18:28:41 marc 2 1
c wrong source
e
s 00779/00000/00000
d D 5.1 91/03/07 20:27:27 bostic 1 0
c date and time created 91/03/07 20:27:27 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
D 3
 * %sccs.include.redist.c%
E 3
I 3
D 10
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
 *
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 3
 */

#ifndef lint
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 10
static char sccsid[] = "@(#)exec.c	5.2 (Berkeley) 3/13/91";
E 10
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
E 10
E 3
#endif /* not lint */

I 12
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

E 12
/*
 * When commands are first encountered, they are entered in a hash table.
 * This ensures that a full path search will not have to be done for them
 * on each invocation.
 *
 * We should investigate converting to a linear search, even though that
 * would make the command name "hash" a misnomer.
 */

#include "shell.h"
#include "main.h"
#include "nodes.h"
#include "parser.h"
#include "redir.h"
#include "eval.h"
#include "exec.h"
#include "builtins.h"
#include "var.h"
#include "options.h"
#include "input.h"
#include "output.h"
#include "syntax.h"
#include "memalloc.h"
#include "error.h"
#include "init.h"
#include "mystring.h"
I 12
#include "show.h"
E 12
I 7
#include "jobs.h"
E 7
D 12
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
E 12


#define CMDTABLESIZE 31		/* should be prime */
#define ARB 1			/* actual size determined at run time */



struct tblentry {
	struct tblentry *next;	/* next entry in hash chain */
	union param param;	/* definition of builtin function */
	short cmdtype;		/* index identifying command */
	char rehash;		/* if set, cd done since entry created */
	char cmdname[ARB];	/* name of command */
};


STATIC struct tblentry *cmdtable[CMDTABLESIZE];
D 2
STATIC int builtinloc;		/* index in path of %builtin, or -1 */
E 2
I 2
STATIC int builtinloc = -1;		/* index in path of %builtin, or -1 */
E 2


D 12
#ifdef __STDC__
STATIC void tryexec(char *, char **, char **);
STATIC void execinterp(char **, char **);
D 6
STATIC void printentry(struct tblentry *);
E 6
I 6
STATIC void printentry(struct tblentry *, int);
E 6
STATIC void clearcmdentry(int);
STATIC struct tblentry *cmdlookup(char *, int);
STATIC void delete_cmd_entry(void);
#else
STATIC void tryexec();
STATIC void execinterp();
STATIC void printentry();
STATIC void clearcmdentry();
STATIC struct tblentry *cmdlookup();
STATIC void delete_cmd_entry();
#endif
E 12
I 12
STATIC void tryexec __P((char *, char **, char **));
STATIC void execinterp __P((char **, char **));
STATIC void printentry __P((struct tblentry *, int));
STATIC void clearcmdentry __P((int));
STATIC struct tblentry *cmdlookup __P((char *, int));
STATIC void delete_cmd_entry __P((void));
E 12



/*
 * Exec a program.  Never returns.  If you change this routine, you may
 * have to change the find_command routine as well.
 */

void
shellexec(argv, envp, path, index)
	char **argv, **envp;
	char *path;
D 12
	{
E 12
I 12
	int index;
{
E 12
	char *cmdname;
	int e;

	if (strchr(argv[0], '/') != NULL) {
		tryexec(argv[0], argv, envp);
		e = errno;
	} else {
		e = ENOENT;
		while ((cmdname = padvance(&path, argv[0])) != NULL) {
			if (--index < 0 && pathopt == NULL) {
				tryexec(cmdname, argv, envp);
				if (errno != ENOENT && errno != ENOTDIR)
					e = errno;
			}
			stunalloc(cmdname);
		}
	}
	error2(argv[0], errmsg(e, E_EXEC));
}


STATIC void
tryexec(cmd, argv, envp)
	char *cmd;
	char **argv;
	char **envp;
	{
	int e;
I 12
#ifndef BSD
E 12
	char *p;
I 12
#endif
E 12

#ifdef SYSV
	do {
		execve(cmd, argv, envp);
	} while (errno == EINTR);
#else
	execve(cmd, argv, envp);
#endif
	e = errno;
	if (e == ENOEXEC) {
		initshellproc();
		setinputfile(cmd, 0);
		commandname = arg0 = savestr(argv[0]);
#ifndef BSD
		pgetc(); pungetc();		/* fill up input buffer */
		p = parsenextc;
		if (parsenleft > 2 && p[0] == '#' && p[1] == '!') {
			argv[0] = cmd;
			execinterp(argv, envp);
		}
#endif
		setparam(argv + 1);
		exraise(EXSHELLPROC);
		/*NOTREACHED*/
	}
	errno = e;
}


#ifndef BSD
/*
 * Execute an interpreter introduced by "#!", for systems where this
 * feature has not been built into the kernel.  If the interpreter is
 * the shell, return (effectively ignoring the "#!").  If the execution
 * of the interpreter fails, exit.
 *
 * This code peeks inside the input buffer in order to avoid actually
 * reading any input.  It would benefit from a rewrite.
 */

#define NEWARGS 5

STATIC void
execinterp(argv, envp)
	char **argv, **envp;
	{
	int n;
	char *inp;
	char *outp;
	char c;
	char *p;
	char **ap;
	char *newargs[NEWARGS];
	int i;
	char **ap2;
	char **new;

	n = parsenleft - 2;
	inp = parsenextc + 2;
	ap = newargs;
	for (;;) {
		while (--n >= 0 && (*inp == ' ' || *inp == '\t'))
			inp++;
		if (n < 0)
			goto bad;
		if ((c = *inp++) == '\n')
			break;
		if (ap == &newargs[NEWARGS])
bad:		  error("Bad #! line");
		STARTSTACKSTR(outp);
		do {
			STPUTC(c, outp);
		} while (--n >= 0 && (c = *inp++) != ' ' && c != '\t' && c != '\n');
		STPUTC('\0', outp);
		n++, inp--;
		*ap++ = grabstackstr(outp);
	}
	if (ap == newargs + 1) {	/* if no args, maybe no exec is needed */
		p = newargs[0];
		for (;;) {
			if (equal(p, "sh") || equal(p, "ash")) {
				return;
			}
			while (*p != '/') {
				if (*p == '\0')
					goto break2;
				p++;
			}
			p++;
		}
break2:;
	}
	i = (char *)ap - (char *)newargs;		/* size in bytes */
	if (i == 0)
		error("Bad #! line");
	for (ap2 = argv ; *ap2++ != NULL ; );
	new = ckmalloc(i + ((char *)ap2 - (char *)argv));
	ap = newargs, ap2 = new;
	while ((i -= sizeof (char **)) >= 0)
		*ap2++ = *ap++;
	ap = argv;
	while (*ap2++ = *ap++);
	shellexec(new, envp, pathval(), 0);
}
#endif



/*
 * Do a path search.  The variable path (passed by reference) should be
 * set to the start of the path before the first call; padvance will update
 * this value as it proceeds.  Successive calls to padvance will return
 * the possible path expansions in sequence.  If an option (indicated by
 * a percent sign) appears in the path entry then the global variable
 * pathopt will be set to point to it; otherwise pathopt will be set to
 * NULL.
 */

char *pathopt;

char *
padvance(path, name)
	char **path;
	char *name;
	{
	register char *p, *q;
	char *start;
	int len;

	if (*path == NULL)
		return NULL;
	start = *path;
	for (p = start ; *p && *p != ':' && *p != '%' ; p++);
	len = p - start + strlen(name) + 2;	/* "2" is for '/' and '\0' */
	while (stackblocksize() < len)
		growstackblock();
	q = stackblock();
	if (p != start) {
D 11
		bcopy(start, q, p - start);
E 11
I 11
D 12
		memmove(q, start, p - start);
E 12
I 12
		memcpy(q, start, p - start);
E 12
E 11
		q += p - start;
		*q++ = '/';
	}
	strcpy(q, name);
	pathopt = NULL;
	if (*p == '%') {
		pathopt = ++p;
		while (*p && *p != ':')  p++;
	}
	if (*p == ':')
		*path = p + 1;
	else
		*path = NULL;
	return stalloc(len);
}



/*** Command hashing code ***/


D 12
hashcmd(argc, argv)  char **argv; {
E 12
I 12
int
hashcmd(argc, argv)
	int argc;
	char **argv; 
{
E 12
	struct tblentry **pp;
	struct tblentry *cmdp;
	int c;
	int verbose;
	struct cmdentry entry;
	char *name;

D 6
	if (argc <= 1) {
		for (pp = cmdtable ; pp < &cmdtable[CMDTABLESIZE] ; pp++) {
			for (cmdp = *pp ; cmdp ; cmdp = cmdp->next) {
				printentry(cmdp);
			}
		}
		return 0;
	}
E 6
	verbose = 0;
D 2
	while ((c = nextopt("rv")) >= 0) {
E 2
I 2
	while ((c = nextopt("rv")) != '\0') {
E 2
		if (c == 'r') {
			clearcmdentry(0);
		} else if (c == 'v') {
			verbose++;
		}
	}
I 6
	if (*argptr == NULL) {
		for (pp = cmdtable ; pp < &cmdtable[CMDTABLESIZE] ; pp++) {
			for (cmdp = *pp ; cmdp ; cmdp = cmdp->next) {
				printentry(cmdp, verbose);
			}
		}
		return 0;
	}
E 6
	while ((name = *argptr) != NULL) {
		if ((cmdp = cmdlookup(name, 0)) != NULL
		 && (cmdp->cmdtype == CMDNORMAL
D 12
		     || cmdp->cmdtype == CMDBUILTIN && builtinloc >= 0))
E 12
I 12
		     || (cmdp->cmdtype == CMDBUILTIN && builtinloc >= 0)))
E 12
			delete_cmd_entry();
D 13
		find_command(name, &entry, 1);
E 13
I 13
		find_command(name, &entry, 1, pathval());
E 13
		if (verbose) {
			if (entry.cmdtype != CMDUNKNOWN) {	/* if no error msg */
				cmdp = cmdlookup(name, 0);
D 6
				printentry(cmdp);
E 6
I 6
				printentry(cmdp, verbose);
E 6
			}
			flushall();
		}
		argptr++;
	}
	return 0;
}


STATIC void
D 6
printentry(cmdp)
E 6
I 6
printentry(cmdp, verbose)
E 6
	struct tblentry *cmdp;
I 6
	int verbose;
E 6
	{
	int index;
	char *path;
	char *name;

	if (cmdp->cmdtype == CMDNORMAL) {
		index = cmdp->param.index;
		path = pathval();
		do {
			name = padvance(&path, cmdp->cmdname);
			stunalloc(name);
		} while (--index >= 0);
		out1str(name);
	} else if (cmdp->cmdtype == CMDBUILTIN) {
		out1fmt("builtin %s", cmdp->cmdname);
	} else if (cmdp->cmdtype == CMDFUNCTION) {
		out1fmt("function %s", cmdp->cmdname);
I 6
		if (verbose) {
			INTOFF;
			name = commandtext(cmdp->param.func);
			out1c(' ');
			out1str(name);
			ckfree(name);
			INTON;
		}
E 6
#ifdef DEBUG
	} else {
		error("internal error: cmdtype %d", cmdp->cmdtype);
#endif
	}
	if (cmdp->rehash)
		out1c('*');
	out1c('\n');
}



/*
 * Resolve a command name.  If you change this routine, you may have to
 * change the shellexec routine as well.
 */

void
D 13
find_command(name, entry, printerr)
E 13
I 13
find_command(name, entry, printerr, path)
E 13
	char *name;
	struct cmdentry *entry;
D 12
	{
E 12
I 12
	int printerr;
I 13
	char *path;
E 13
{
E 12
	struct tblentry *cmdp;
	int index;
	int prev;
D 13
	char *path;
E 13
	char *fullname;
	struct stat statb;
	int e;
	int i;

	/* If name contains a slash, don't use the hash table */
	if (strchr(name, '/') != NULL) {
		entry->cmdtype = CMDNORMAL;
		entry->u.index = 0;
		return;
	}

	/* If name is in the table, and not invalidated by cd, we're done */
	if ((cmdp = cmdlookup(name, 0)) != NULL && cmdp->rehash == 0)
		goto success;

	/* If %builtin not in path, check for builtin next */
	if (builtinloc < 0 && (i = find_builtin(name)) >= 0) {
		INTOFF;
		cmdp = cmdlookup(name, 1);
		cmdp->cmdtype = CMDBUILTIN;
		cmdp->param.index = i;
		INTON;
		goto success;
	}

	/* We have to search path. */
	prev = -1;		/* where to start */
	if (cmdp) {		/* doing a rehash */
		if (cmdp->cmdtype == CMDBUILTIN)
			prev = builtinloc;
		else
			prev = cmdp->param.index;
	}

D 13
	path = pathval();
E 13
	e = ENOENT;
	index = -1;
loop:
	while ((fullname = padvance(&path, name)) != NULL) {
		stunalloc(fullname);
		index++;
		if (pathopt) {
			if (prefix("builtin", pathopt)) {
				if ((i = find_builtin(name)) < 0)
					goto loop;
				INTOFF;
				cmdp = cmdlookup(name, 1);
				cmdp->cmdtype = CMDBUILTIN;
				cmdp->param.index = i;
				INTON;
				goto success;
			} else if (prefix("func", pathopt)) {
				/* handled below */
			} else {
				goto loop;	/* ignore unimplemented options */
			}
		}
		/* if rehash, don't redo absolute path names */
		if (fullname[0] == '/' && index <= prev) {
			if (index < prev)
				goto loop;
			TRACE(("searchexec \"%s\": no change\n", name));
			goto success;
		}
		while (stat(fullname, &statb) < 0) {
#ifdef SYSV
			if (errno == EINTR)
				continue;
#endif
			if (errno != ENOENT && errno != ENOTDIR)
				e = errno;
			goto loop;
		}
		e = EACCES;	/* if we fail, this will be the error */
D 12
		if ((statb.st_mode & S_IFMT) != S_IFREG)
E 12
I 12
		if (!S_ISREG(statb.st_mode))
E 12
			goto loop;
		if (pathopt) {		/* this is a %func directory */
			stalloc(strlen(fullname) + 1);
			readcmdfile(fullname);
			if ((cmdp = cmdlookup(name, 0)) == NULL || cmdp->cmdtype != CMDFUNCTION)
				error("%s not defined in %s", name, fullname);
			stunalloc(fullname);
			goto success;
		}
I 5
#ifdef notdef
E 5
		if (statb.st_uid == geteuid()) {
			if ((statb.st_mode & 0100) == 0)
				goto loop;
		} else if (statb.st_gid == getegid()) {
			if ((statb.st_mode & 010) == 0)
				goto loop;
		} else {
			if ((statb.st_mode & 01) == 0)
				goto loop;
		}
I 5
#endif
E 5
		TRACE(("searchexec \"%s\" returns \"%s\"\n", name, fullname));
		INTOFF;
		cmdp = cmdlookup(name, 1);
		cmdp->cmdtype = CMDNORMAL;
		cmdp->param.index = index;
		INTON;
		goto success;
	}

	/* We failed.  If there was an entry for this command, delete it */
	if (cmdp)
		delete_cmd_entry();
	if (printerr)
		outfmt(out2, "%s: %s\n", name, errmsg(e, E_EXEC));
	entry->cmdtype = CMDUNKNOWN;
	return;

success:
	cmdp->rehash = 0;
	entry->cmdtype = cmdp->cmdtype;
	entry->u = cmdp->param;
}



/*
 * Search the table of builtin commands.
 */

int
find_builtin(name)
	char *name;
D 12
	{
	const register struct builtincmd *bp;
E 12
I 12
{
	register const struct builtincmd *bp;
E 12

	for (bp = builtincmd ; bp->name ; bp++) {
		if (*bp->name == *name && equal(bp->name, name))
			return bp->code;
	}
	return -1;
}



/*
 * Called when a cd is done.  Marks all commands so the next time they
 * are executed they will be rehashed.
 */

void
hashcd() {
	struct tblentry **pp;
	struct tblentry *cmdp;

	for (pp = cmdtable ; pp < &cmdtable[CMDTABLESIZE] ; pp++) {
		for (cmdp = *pp ; cmdp ; cmdp = cmdp->next) {
			if (cmdp->cmdtype == CMDNORMAL
D 12
			 || cmdp->cmdtype == CMDBUILTIN && builtinloc >= 0)
E 12
I 12
			 || (cmdp->cmdtype == CMDBUILTIN && builtinloc >= 0))
E 12
				cmdp->rehash = 1;
		}
	}
}



/*
 * Called before PATH is changed.  The argument is the new value of PATH;
 * pathval() still returns the old value at this point.  Called with
 * interrupts off.
 */

void
changepath(newval)
	char *newval;
D 12
	{
E 12
I 12
{
E 12
	char *old, *new;
	int index;
	int firstchange;
	int bltin;
I 3
D 12
	int hasdot;
E 12
E 3

	old = pathval();
	new = newval;
	firstchange = 9999;	/* assume no change */
D 3
	index = 0;
E 3
I 3
D 12
	index = hasdot = 0;
E 12
I 12
	index = 0;
E 12
E 3
	bltin = -1;
I 3
D 12
	if (*new == ':')
		hasdot++;
E 12
E 3
	for (;;) {
		if (*old != *new) {
			firstchange = index;
D 12
			if (*old == '\0' && *new == ':'
			 || *old == ':' && *new == '\0')
E 12
I 12
			if ((*old == '\0' && *new == ':')
			 || (*old == ':' && *new == '\0'))
E 12
				firstchange++;
			old = new;	/* ignore subsequent differences */
		}
		if (*new == '\0')
			break;
		if (*new == '%' && bltin < 0 && prefix("builtin", new + 1))
			bltin = index;
		if (*new == ':') {
I 3
D 12
			char c = *(new+1);

E 12
E 3
			index++;
I 3
D 12
			if (c == ':' || c == '\0' || (c == '.' && 
			   ((c = *(new+2)) == ':' || c == '\0')))
				hasdot++;
E 12
E 3
		}
		new++, old++;
	}
I 3
D 12
	if (hasdot && geteuid() == 0)
		out2str("sh: warning: running as root with dot in PATH\n");
E 12
E 3
	if (builtinloc < 0 && bltin >= 0)
		builtinloc = bltin;		/* zap builtins */
	if (builtinloc >= 0 && bltin < 0)
		firstchange = 0;
	clearcmdentry(firstchange);
	builtinloc = bltin;
}


/*
 * Clear out command entries.  The argument specifies the first entry in
 * PATH which has changed.
 */

STATIC void
D 12
clearcmdentry(firstchange) {
E 12
I 12
clearcmdentry(firstchange)
	int firstchange;
{
E 12
	struct tblentry **tblp;
	struct tblentry **pp;
	struct tblentry *cmdp;

	INTOFF;
	for (tblp = cmdtable ; tblp < &cmdtable[CMDTABLESIZE] ; tblp++) {
		pp = tblp;
		while ((cmdp = *pp) != NULL) {
D 12
			if (cmdp->cmdtype == CMDNORMAL && cmdp->param.index >= firstchange
			 || cmdp->cmdtype == CMDBUILTIN && builtinloc >= firstchange) {
E 12
I 12
			if ((cmdp->cmdtype == CMDNORMAL &&
			     cmdp->param.index >= firstchange)
			 || (cmdp->cmdtype == CMDBUILTIN &&
			     builtinloc >= firstchange)) {
E 12
				*pp = cmdp->next;
				ckfree(cmdp);
			} else {
				pp = &cmdp->next;
			}
		}
	}
	INTON;
}


/*
 * Delete all functions.
 */

#ifdef mkinit
MKINIT void deletefuncs();

SHELLPROC {
	deletefuncs();
}
#endif

void
deletefuncs() {
	struct tblentry **tblp;
	struct tblentry **pp;
	struct tblentry *cmdp;

	INTOFF;
	for (tblp = cmdtable ; tblp < &cmdtable[CMDTABLESIZE] ; tblp++) {
		pp = tblp;
		while ((cmdp = *pp) != NULL) {
			if (cmdp->cmdtype == CMDFUNCTION) {
				*pp = cmdp->next;
				freefunc(cmdp->param.func);
				ckfree(cmdp);
			} else {
				pp = &cmdp->next;
			}
		}
	}
	INTON;
}



/*
 * Locate a command in the command hash table.  If "add" is nonzero,
 * add the command to the table if it is not already present.  The
 * variable "lastcmdentry" is set to point to the address of the link
 * pointing to the entry, so that delete_cmd_entry can delete the
 * entry.
 */

struct tblentry **lastcmdentry;


STATIC struct tblentry *
cmdlookup(name, add)
	char *name;
D 12
	{
E 12
I 12
	int add;
{
E 12
	int hashval;
	register char *p;
	struct tblentry *cmdp;
	struct tblentry **pp;

	p = name;
	hashval = *p << 4;
	while (*p)
		hashval += *p++;
	hashval &= 0x7FFF;
	pp = &cmdtable[hashval % CMDTABLESIZE];
	for (cmdp = *pp ; cmdp ; cmdp = cmdp->next) {
		if (equal(cmdp->cmdname, name))
			break;
		pp = &cmdp->next;
	}
	if (add && cmdp == NULL) {
		INTOFF;
		cmdp = *pp = ckmalloc(sizeof (struct tblentry) - ARB
					+ strlen(name) + 1);
		cmdp->next = NULL;
		cmdp->cmdtype = CMDUNKNOWN;
		cmdp->rehash = 0;
		strcpy(cmdp->cmdname, name);
		INTON;
	}
	lastcmdentry = pp;
	return cmdp;
}
D 5

E 5

/*
 * Delete the command entry returned on the last lookup.
 */

STATIC void
delete_cmd_entry() {
	struct tblentry *cmdp;

	INTOFF;
	cmdp = *lastcmdentry;
	*lastcmdentry = cmdp->next;
	ckfree(cmdp);
	INTON;
}



#ifdef notdef
void
getcmdentry(name, entry)
	char *name;
	struct cmdentry *entry; 
	{
	struct tblentry *cmdp = cmdlookup(name, 0);

	if (cmdp) {
		entry->u = cmdp->param;
		entry->cmdtype = cmdp->cmdtype;
	} else {
		entry->cmdtype = CMDUNKNOWN;
		entry->u.index = 0;
	}
}
#endif


/*
 * Add a new command entry, replacing any existing command entry for
 * the same name.
 */

void
addcmdentry(name, entry)
	char *name;
	struct cmdentry *entry;
	{
	struct tblentry *cmdp;

	INTOFF;
	cmdp = cmdlookup(name, 1);
	if (cmdp->cmdtype == CMDFUNCTION) {
		freefunc(cmdp->param.func);
	}
	cmdp->cmdtype = entry->cmdtype;
	cmdp->param = entry->u;
	INTON;
}


/*
 * Define a shell function.
 */

void
defun(name, func)
	char *name;
	union node *func;
	{
	struct cmdentry entry;

	INTOFF;
	entry.cmdtype = CMDFUNCTION;
	entry.u.func = copyfunc(func);
	addcmdentry(name, &entry);
	INTON;
}


/*
 * Delete a function if it exists.
 */

D 4
void
E 4
I 4
int
E 4
unsetfunc(name)
	char *name;
	{
	struct tblentry *cmdp;

	if ((cmdp = cmdlookup(name, 0)) != NULL && cmdp->cmdtype == CMDFUNCTION) {
		freefunc(cmdp->param.func);
		delete_cmd_entry();
I 4
		return (0);
E 4
	}
I 4
	return (1);
E 4
}
E 1
