h52163
s 00001/00001/00407
d D 8.5 95/04/28 10:57:42 bostic 36 35
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00407
d D 8.4 94/10/18 15:39:59 mckusick 35 34
c unwhiteout => undelete
e
s 00039/00000/00369
d D 8.3 94/09/13 12:26:47 mckusick 34 33
c add support for restoring whiteouts
e
s 00005/00002/00364
d D 8.2 94/03/25 12:41:24 bostic 33 32
c there's a bug in restore's interactive mode, which occurs when you 'add'
c a directory not in the dump.
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00364
d D 8.1 93/06/05 11:12:20 bostic 32 31
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00365
d D 5.11 93/02/10 14:47:53 bostic 31 30
c make declarations work with new prototypes in globh
e
s 00003/00002/00363
d D 5.10 92/12/02 01:08:12 mckusick 30 29
c have to deal with pathsearch returning a dp instead of an ino_t
e
s 00064/00036/00301
d D 5.9 92/10/16 16:21:30 bostic 29 28
c ANSI C, convert options handling to getopt(3)
e
s 00002/00002/00335
d D 5.8 92/10/06 00:17:38 mckusick 28 27
c psearch get more intuitive name pathsearch
e
s 00001/00001/00336
d D 5.7 92/10/05 21:50:34 mckusick 27 26
c use standard bit test macros
e
s 00001/00011/00336
d D 5.6 90/06/01 16:21:36 bostic 26 25
c new copyright notice
e
s 00002/00000/00345
d D 5.5 90/05/30 16:31:12 mckusick 25 24
c yfalg applies to abort's too
e
s 00015/00004/00330
d D 5.4 88/10/24 16:38:40 bostic 24 23
c Berkeley copyright notice
e
s 00006/00006/00328
d D 5.3 88/05/13 14:48:00 mckusick 23 22
c add Nflag to request not to do any writes
e
s 00002/00003/00332
d D 5.2 85/08/05 19:30:38 mckusick 22 21
c repeat the question; default to "no" when reading end-of-file
e
s 00008/00004/00327
d D 5.1 85/05/28 15:17:10 dist 21 20
c Add copyright
e
s 00001/00001/00330
d D 3.20 85/02/18 18:31:10 mckusick 20 19
c must track extract list separately from creating entries
e
s 00003/00000/00328
d D 3.19 85/02/18 18:28:59 mckusick 19 18
c do not set owner and times on directories that already exist ('i' and 'x' only)
e
s 00000/00181/00328
d D 3.18 85/01/18 22:41:01 mckusick 18 17
c reorganize to split out interactive shell
e
s 00002/00001/00507
d D 3.17 85/01/14 17:46:23 mckusick 17 16
c don't give up when /dev/tty cannot be opened unless it must be read
e
s 00006/00004/00502
d D 3.16 83/12/30 00:42:54 mckusick 16 15
c cleanup format of error messages; return success code
e
s 00002/00002/00504
d D 3.15 83/08/11 23:07:17 sam 15 14
c standardize sccs keyword lines
e
s 00061/00017/00445
d D 3.14 83/08/11 16:45:31 mckusick 14 13
c allow names to be quoted and/or backslashed
e
s 00010/00007/00452
d D 3.13 83/05/19 01:23:06 mckusick 13 12
c use perror everywhere; lint
e
s 00001/00000/00458
d D 3.12 83/05/06 17:57:47 mckusick 12 11
c must flush stderr before reading from the terminal
e
s 00161/00012/00297
d D 3.11 83/04/19 02:12:24 mckusick 11 10
c add and debug interactive extraction mode
e
s 00023/00014/00286
d D 3.10 83/04/16 13:04:00 mckusick 10 9
c make linking, unlinking, rmdir, and mkdir failures non-fatal
e
s 00019/00008/00281
d D 3.9 83/04/11 18:09:12 mckusick 9 8
c generalize the printing of flags
e
s 00004/00006/00285
d D 3.8 83/03/27 18:17:35 mckusick 8 7
c make an existing directory merely a warning
e
s 00001/00001/00290
d D 3.7 83/03/27 12:57:13 mckusick 7 6
c lint
e
s 00023/00003/00268
d D 3.6 83/03/23 08:58:14 mckusick 6 5
c use a tempname derived from the inode number instead of from the file name
e
s 00013/00054/00258
d D 3.5 83/01/16 06:04:20 mckusick 5 4
c new incremental restore algorithm
e
s 00020/00000/00292
d D 3.4 83/02/28 00:36:50 mckusick 4 3
c canonicalize names on command line and ignore dups
e
s 00004/00024/00288
d D 3.3 83/02/27 16:31:16 mckusick 3 2
c get input from a pipe to work
e
s 00003/00006/00309
d D 3.2 83/02/27 14:40:11 mckusick 2 1
c get "x" command working
e
s 00315/00000/00000
d D 3.1 83/02/18 00:41:44 mckusick 1 0
c date and time created 83/02/18 00:41:44 by mckusick
e
u
U
t
T
I 1
D 15
/* Copyright (c) 1983 Regents of the University of California */

E 15
D 21
#ifndef lint
static char sccsid[] = "%W%	(Berkeley)	%E%";
#endif
E 21
I 21
/*
D 24
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 24
I 24
D 32
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 32
I 32
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 32
 *
D 26
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 24
 */
E 21
I 15

D 21
/* Copyright (c) 1983 Regents of the University of California */
E 21
I 21
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 24
#endif not lint
E 24
I 24
#endif /* not lint */
E 24
E 21
E 15

I 29
#include <sys/param.h>
#include <sys/stat.h>

#include <ufs/ufs/dinode.h>
I 30
#include <ufs/ufs/dir.h>
E 30

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

E 29
#include "restore.h"
I 29
#include "extern.h"
E 29

I 14
D 18
char *copynext();

E 18
E 14
/*
D 5
 * Move the contents of a directory to a new directory.
 */
movecontents(from, to)
	struct entry *from, *to;
{
	register struct entry *ep;
	struct entry *np;
	register char *targetp;
	char target[BUFSIZ];

	strcpy(target, myname(to));
	targetp = &target[strlen(target)];
	*targetp++ = '/';
	for (ep = from->e_entries; ep != NIL; ) {
		strcpy(targetp, ep->e_name);
		if (ep->e_flags & TMPNAME)
			badentry(ep, "movecontents: found TMPNAME");
		np = lookupname(target);
		if (np != NIL)
			mktempname(np);
		renameit(myname(ep), target);
		np = ep->e_sibling;
		moveentry(ep, target);
		ep = np;
	}
}

/*
E 5
 * Insure that all the components of a pathname exist.
 */
I 29
void
E 29
D 5
struct entry *
pathcheck(name, type)
E 5
I 5
pathcheck(name)
E 5
	char *name;
D 5
	char type;
E 5
{
	register char *cp;
	struct entry *ep;
D 2
	char *start, *last;
E 2
I 2
	char *start;
E 2

D 36
	start = index(name, '/');
E 36
I 36
	start = strchr(name, '/');
E 36
D 2
	last = rindex(name, '/');
	if (last == 0)
		panic("bad name %s to pathcheck\n", name);
	if (start == last)
E 2
I 2
	if (start == 0)
E 2
D 5
		return (lookupino(ROOTINO));
E 5
I 5
		return;
E 5
	for (cp = start; *cp != '\0'; cp++) {
		if (*cp != '/')
			continue;
		*cp = '\0';
		ep = lookupname(name);
D 29
		if (ep == NIL) {
E 29
I 29
		if (ep == NULL) {
I 33
			/* Safe; we know the pathname exists in the dump. */
E 33
E 29
D 5
			ep = addentry(name, (ino_t)0, NODE);
			ep->e_flags |= type;
E 5
I 5
D 11
			ep = addentry(name, ep->e_ino, NODE);
			ep->e_flags |= KEEP;
E 11
I 11
D 28
			ep = addentry(name, psearch(name), NODE);
E 28
I 28
D 30
			ep = addentry(name, pathsearch(name), NODE);
E 30
I 30
			ep = addentry(name, pathsearch(name)->d_ino, NODE);
E 30
E 28
E 11
E 5
			newnode(ep);
I 11
D 20
			ep->e_flags |= NEW|KEEP;
E 20
E 11
		}
I 20
		ep->e_flags |= NEW|KEEP;
E 20
		*cp = '/';
	}
D 5
	return (ep);
E 5
}

/*
 * Change a name to a unique temporary name.
 */
I 29
void
E 29
mktempname(ep)
	register struct entry *ep;
{
D 6
	char oldname[BUFSIZ];
E 6
I 6
	char oldname[MAXPATHLEN];
E 6

	if (ep->e_flags & TMPNAME)
		badentry(ep, "mktempname: called with TMPNAME");
	ep->e_flags |= TMPNAME;
D 11
	strcpy(oldname, myname(ep));
E 11
I 11
	(void) strcpy(oldname, myname(ep));
E 11
D 6
	ep->e_name[ep->e_namlen++] = TMPCHAR;
	ep->e_name[ep->e_namlen] = '\0';
E 6
I 6
	freename(ep->e_name);
	ep->e_name = savename(gentempname(ep));
	ep->e_namlen = strlen(ep->e_name);
E 6
	renameit(oldname, myname(ep));
I 6
}

/*
 * Generate a temporary name for an entry.
 */
char *
gentempname(ep)
	struct entry *ep;
{
	static char name[MAXPATHLEN];
	struct entry *np;
	long i = 0;

D 29
	for (np = lookupino(ep->e_ino); np != NIL && np != ep; np = np->e_links)
E 29
I 29
	for (np = lookupino(ep->e_ino);
	    np != NULL && np != ep; np = np->e_links)
E 29
		i++;
D 29
	if (np == NIL)
E 29
I 29
	if (np == NULL)
E 29
		badentry(ep, "not on ino list");
D 7
	sprintf(name, "%s%d%d", TMPHDR, i, ep->e_ino);
E 7
I 7
	(void) sprintf(name, "%s%d%d", TMPHDR, i, ep->e_ino);
E 7
	return (name);
E 6
}

/*
 * Rename a file or directory.
 */
I 29
void
E 29
renameit(from, to)
	char *from, *to;
{
D 23
	if (rename(from, to) < 0) {
E 23
I 23
	if (!Nflag && rename(from, to) < 0) {
E 23
D 10
		perror("renameit");
		panic("Cannot rename %s to %s\n", from, to);
E 10
I 10
D 13
		fprintf(stderr, "Warning: cannot rename %s to %s\n", from, to);
		perror("rename");
E 13
I 13
D 29
		fprintf(stderr, "Warning: cannot rename %s to %s", from, to);
		(void) fflush(stderr);
		perror("");
E 29
I 29
		fprintf(stderr, "warning: cannot rename %s to %s: %s\n",
		    from, to, strerror(errno));
E 29
E 13
		return;
E 10
	}
	vprintf(stdout, "rename %s to %s\n", from, to);
}

/*
 * Create a new node (directory).
 */
I 29
void
E 29
newnode(np)
	struct entry *np;
{
	char *cp;

	if (np->e_type != NODE)
		badentry(np, "newnode: not a node");
	cp = myname(np);
D 2
	if (mkdir(cp, 0666) < 0) {
E 2
I 2
D 23
	if (mkdir(cp, 0777) < 0) {
E 23
I 23
	if (!Nflag && mkdir(cp, 0777) < 0) {
E 23
I 19
		np->e_flags |= EXISTED;
E 19
I 3
D 8
		if (command == 'x') {
			perror(cp);
			return;
		}
E 3
E 2
		perror("newnode");
		panic("Cannot make node %s\n", cp);
E 8
I 8
D 29
		fprintf(stderr, "Warning: ");
D 11
		fflush(stderr);
E 11
I 11
		(void) fflush(stderr);
E 11
		perror(cp);
E 29
I 29
		fprintf(stderr, "warning: %s: %s\n", cp, strerror(errno));
E 29
		return;
E 8
	}
	vprintf(stdout, "Make node %s\n", cp);
}

/*
 * Remove an old node (directory).
 */
I 29
void
E 29
removenode(ep)
	register struct entry *ep;
{
	char *cp;

	if (ep->e_type != NODE)
		badentry(ep, "removenode: not a node");
D 29
	if (ep->e_entries != NIL)
E 29
I 29
	if (ep->e_entries != NULL)
E 29
		badentry(ep, "removenode: non-empty directory");
I 10
	ep->e_flags |= REMOVED;
	ep->e_flags &= ~TMPNAME;
E 10
	cp = myname(ep);
D 23
	if (rmdir(cp) < 0) {
E 23
I 23
	if (!Nflag && rmdir(cp) < 0) {
E 23
D 10
		perror("removenode");
		panic("Cannot remove node %s\n", cp);
E 10
I 10
D 29
		fprintf(stderr, "Warning: ");
D 11
		fflush(stderr);
E 11
I 11
		(void) fflush(stderr);
E 11
		perror(cp);
E 29
I 29
		fprintf(stderr, "warning: %s: %s\n", cp, strerror(errno));
E 29
		return;
E 10
	}
D 10
	ep->e_flags |= REMOVED;
D 5
	ep->e_flags &= ~(TMPNAME|TMPNODE);
E 5
I 5
	ep->e_flags &= ~TMPNAME;
E 10
E 5
	vprintf(stdout, "Remove node %s\n", cp);
}

/*
 * Remove a leaf.
 */
I 29
void
E 29
removeleaf(ep)
	register struct entry *ep;
{
	char *cp;

	if (ep->e_type != LEAF)
		badentry(ep, "removeleaf: not a leaf");
I 10
	ep->e_flags |= REMOVED;
	ep->e_flags &= ~TMPNAME;
E 10
	cp = myname(ep);
D 23
	if (unlink(cp) < 0) {
E 23
I 23
	if (!Nflag && unlink(cp) < 0) {
E 23
D 10
		perror("removeleaf");
		panic("Cannot remove leaf %s\n", cp);
E 10
I 10
D 29
		fprintf(stderr, "Warning: ");
D 11
		fflush(stderr);
E 11
I 11
		(void) fflush(stderr);
E 11
		perror(cp);
E 29
I 29
		fprintf(stderr, "warning: %s: %s\n", cp, strerror(errno));
E 29
		return;
E 10
	}
D 10
	ep->e_flags |= REMOVED;
	ep->e_flags &= ~TMPNAME;
E 10
	vprintf(stdout, "Remove leaf %s\n", cp);
}

/*
 * Create a link.
 */
I 29
int
E 29
linkit(existing, new, type)
	char *existing, *new;
	int type;
{

	if (type == SYMLINK) {
D 23
		if (symlink(existing, new) < 0) {
E 23
I 23
		if (!Nflag && symlink(existing, new) < 0) {
E 23
D 10
			perror("linkit");
			panic("Cannot create symbolic link %s->%s\n",
E 10
I 10
			fprintf(stderr,
D 13
				"Warning: cannot create symbolic link %s->%s\n",
E 13
I 13
D 16
				"Warning: cannot create symbolic link %s->%s",
E 16
I 16
D 29
				"Warning: cannot create symbolic link %s->%s: ",
E 16
E 13
E 10
				new, existing);
I 10
D 13
			perror("symlink");
E 13
I 13
			(void) fflush(stderr);
			perror("");
E 29
I 29
			    "warning: cannot create symbolic link %s->%s: %s\n",
			    new, existing, strerror(errno));
E 29
E 13
D 16
			return;
E 16
I 16
			return (FAIL);
E 16
E 10
		}
	} else if (type == HARDLINK) {
D 23
		if (link(existing, new) < 0) {
E 23
I 23
		if (!Nflag && link(existing, new) < 0) {
E 23
D 10
			perror("linkit");
			panic("Cannot create hard link %s->%s\n",
E 10
I 10
			fprintf(stderr,
D 13
				"Warning: cannot create hard link %s->%s\n",
E 13
I 13
D 16
				"Warning: cannot create hard link %s->%s",
E 16
I 16
D 29
				"Warning: cannot create hard link %s->%s: ",
E 16
E 13
E 10
				new, existing);
I 10
D 13
			perror("link");
E 13
I 13
			(void) fflush(stderr);
			perror("");
E 29
I 29
			    "warning: cannot create hard link %s->%s: %s\n",
			    new, existing, strerror(errno));
E 29
E 13
D 16
			return;
E 16
I 16
			return (FAIL);
E 16
E 10
		}
	} else {
		panic("linkit: unknown type %d\n", type);
I 16
		return (FAIL);
E 16
	}
	vprintf(stdout, "Create %s link %s->%s\n",
		type == SYMLINK ? "symbolic" : "hard", new, existing);
I 16
	return (GOOD);
E 16
}

/*
I 34
 * Create a whiteout.
 */
int
addwhiteout(name)
	char *name;
{

	if (!Nflag && mknod(name, S_IFWHT, 0) < 0) {
		fprintf(stderr, "warning: cannot create whiteout %s: %s\n",
		    name, strerror(errno));
		return (FAIL);
	}
	vprintf(stdout, "Create whiteout %s\n", name);
	return (GOOD);
}

/*
 * Delete a whiteout.
 */
void
delwhiteout(ep)
	register struct entry *ep;
{
	char *name;

	if (ep->e_type != LEAF)
		badentry(ep, "delwhiteout: not a leaf");
	ep->e_flags |= REMOVED;
	ep->e_flags &= ~TMPNAME;
	name = myname(ep);
D 35
	if (!Nflag && unwhiteout(name) < 0) {
E 35
I 35
	if (!Nflag && undelete(name) < 0) {
E 35
		fprintf(stderr, "warning: cannot delete whiteout %s: %s\n",
		    name, strerror(errno));
		return;
	}
	vprintf(stdout, "Delete whiteout %s\n", name);
}

/*
E 34
 * find lowest number file (above "start") that needs to be extracted
 */
ino_t
lowerbnd(start)
	ino_t start;
{
	register struct entry *ep;

	for ( ; start < maxino; start++) {
		ep = lookupino(start);
D 11
		if (ep == NIL)
E 11
I 11
D 29
		if (ep == NIL || ep->e_type == NODE)
E 29
I 29
		if (ep == NULL || ep->e_type == NODE)
E 29
E 11
			continue;
D 5
		if (ep->e_flags & (NEW|EXTRACT|CHANGE))
E 5
I 5
		if (ep->e_flags & (NEW|EXTRACT))
E 5
			return (start);
	}
	return (start);
}

/*
 * find highest number file (below "start") that needs to be extracted
 */
ino_t
upperbnd(start)
	ino_t start;
{
	register struct entry *ep;

	for ( ; start > ROOTINO; start--) {
		ep = lookupino(start);
D 11
		if (ep == NIL)
E 11
I 11
D 29
		if (ep == NIL || ep->e_type == NODE)
E 29
I 29
		if (ep == NULL || ep->e_type == NODE)
E 29
E 11
			continue;
D 5
		if (ep->e_flags & (NEW|EXTRACT|CHANGE))
E 5
I 5
		if (ep->e_flags & (NEW|EXTRACT))
E 5
			return (start);
	}
	return (start);
}

/*
 * report on a badly formed entry
 */
I 29
void
E 29
badentry(ep, msg)
	register struct entry *ep;
	char *msg;
{
D 9
	char flagbuf[BUFSIZ];
E 9

	fprintf(stderr, "bad entry: %s\n", msg);
	fprintf(stderr, "name: %s\n", myname(ep));
D 5
	if (ep->e_newname != NULL)
		fprintf(stderr, "new name: %s\n", ep->e_newname);
E 5
	fprintf(stderr, "parent name %s\n", myname(ep->e_parent));
D 29
	if (ep->e_sibling != NIL)
E 29
I 29
	if (ep->e_sibling != NULL)
E 29
		fprintf(stderr, "sibling name: %s\n", myname(ep->e_sibling));
D 29
	if (ep->e_entries != NIL)
E 29
I 29
	if (ep->e_entries != NULL)
E 29
		fprintf(stderr, "next entry name: %s\n", myname(ep->e_entries));
D 29
	if (ep->e_links != NIL)
E 29
I 29
	if (ep->e_links != NULL)
E 29
		fprintf(stderr, "next link name: %s\n", myname(ep->e_links));
I 5
D 29
	if (ep->e_next != NIL)
		fprintf(stderr, "next hashchain name: %s\n", myname(ep->e_next));
E 29
I 29
	if (ep->e_next != NULL)
		fprintf(stderr,
		    "next hashchain name: %s\n", myname(ep->e_next));
E 29
E 5
	fprintf(stderr, "entry type: %s\n",
		ep->e_type == NODE ? "NODE" : "LEAF");
	fprintf(stderr, "inode number: %ld\n", ep->e_ino);
D 9
	strcpy(flagbuf, "|NIL");
E 9
I 9
	panic("flags: %s\n", flagvalues(ep));
}

/*
 * Construct a string indicating the active flag bits of an entry.
 */
char *
flagvalues(ep)
	register struct entry *ep;
{
	static char flagbuf[BUFSIZ];

	(void) strcpy(flagbuf, "|NIL");
E 9
	flagbuf[0] = '\0';
D 5
	if (ep->e_flags & REMOVE)
		strcat(flagbuf, "|REMOVE");
E 5
	if (ep->e_flags & REMOVED)
D 9
		strcat(flagbuf, "|REMOVED");
E 9
I 9
		(void) strcat(flagbuf, "|REMOVED");
E 9
D 5
	if (ep->e_flags & RENAME)
		strcat(flagbuf, "|RENAME");
E 5
	if (ep->e_flags & TMPNAME)
D 9
		strcat(flagbuf, "|TMPNAME");
E 9
I 9
		(void) strcat(flagbuf, "|TMPNAME");
E 9
D 5
	if (ep->e_flags & TMPNODE)
		strcat(flagbuf, "|TMPNODE");
E 5
	if (ep->e_flags & EXTRACT)
D 9
		strcat(flagbuf, "|EXTRACT");
E 9
I 9
		(void) strcat(flagbuf, "|EXTRACT");
E 9
D 5
	if (ep->e_flags & RENUMBER)
		strcat(flagbuf, "|RENUMBER");
	if (ep->e_flags & CHANGE)
		strcat(flagbuf, "|CHANGE");
E 5
	if (ep->e_flags & NEW)
D 9
		strcat(flagbuf, "|NEW");
E 9
I 9
		(void) strcat(flagbuf, "|NEW");
E 9
	if (ep->e_flags & KEEP)
D 9
		strcat(flagbuf, "|KEEP");
	panic("flags: %s\n", &flagbuf[1]);
E 9
I 9
		(void) strcat(flagbuf, "|KEEP");
I 19
	if (ep->e_flags & EXISTED)
		(void) strcat(flagbuf, "|EXISTED");
E 19
	return (&flagbuf[1]);
E 9
D 3
}

/*
 * respond to interrupts
 */
onintr()
{
	if (reply("restore interrupted, continue"))
		return;
	done(1);
}

/*
 * handle unexpected inconsistencies
 */
/* VARARGS1 */
panic(msg, d1, d2)
	char *msg;
	long d1, d2;
{

	fprintf(stderr, msg, d1, d2);
	if (reply("abort"))
		abort();
E 3
}

/*
I 4
D 11
 * canonicalize file names to always start with ``./''
E 11
I 11
 * Check to see if a name is on a dump tape.
E 11
 */
I 11
ino_t
dirlookup(name)
D 31
	char *name;
E 31
I 31
	const char *name;
E 31
{
I 33
	struct direct *dp;
E 33
	ino_t ino;
I 33
 
	ino = ((dp = pathsearch(name)) == NULL) ? 0 : dp->d_ino;
E 33

D 28
	ino = psearch(name);
E 28
I 28
D 30
	ino = pathsearch(name);
E 30
I 30
D 33
	ino = pathsearch(name)->d_ino;
E 33
E 30
E 28
D 27
	if (ino == 0 || BIT(ino, dumpmap) == 0)
E 27
I 27
	if (ino == 0 || TSTINO(ino, dumpmap) == 0)
E 27
D 33
		fprintf(stderr, "%s is not on tape\n", name);
E 33
I 33
		fprintf(stderr, "%s is not on the tape\n", name);
E 33
	return (ino);
}

/*
D 18
 * Canonicalize file names to always start with ``./'' and
 * remove any imbedded ".." components.
 */
E 11
canon(rawname, canonname)
	char *rawname, *canonname;
{
I 11
	register char *cp, *np;
E 11
	int len;

	if (strcmp(rawname, ".") == 0 || strncmp(rawname, "./", 2) == 0)
D 5
		strcpy(canonname, "");
E 5
I 5
		(void) strcpy(canonname, "");
E 5
	else if (rawname[0] == '/')
D 5
		strcpy(canonname, ".");
E 5
I 5
		(void) strcpy(canonname, ".");
E 5
	else
D 5
		strcpy(canonname, "./");
	strcat(canonname, rawname);
E 5
I 5
		(void) strcpy(canonname, "./");
	(void) strcat(canonname, rawname);
E 5
	len = strlen(canonname) - 1;
	if (canonname[len] == '/')
		canonname[len] = '\0';
I 11
	/*
	 * Eliminate extraneous ".." from pathnames.
	 */
	for (np = canonname; *np != '\0'; ) {
		np++;
		cp = np;
		while (*np != '/' && *np != '\0')
			np++;
		if (np - cp == 2 && strncmp(cp, "..", 2) == 0) {
			cp--;
			while (cp > &canonname[1] && *--cp != '/')
				/* find beginning of name */;
			(void) strcpy(cp, np);
			np = cp;
		}
	}
E 11
}

/*
E 18
E 4
D 11
 * elicit a reply
E 11
I 11
 * Elicit a reply.
E 11
 */
I 29
int
E 29
reply(question)
	char *question;
{
	char c;

D 22
	fprintf(stderr, "%s? ", question);
E 22
	do	{
D 22
		fprintf(stderr, "[yn] ");
E 22
I 22
		fprintf(stderr, "%s? [yn] ", question);
E 22
I 12
D 13
		fflush(stderr);
E 13
I 13
		(void) fflush(stderr);
E 13
E 12
D 11
		c = getchar();
		while (c != '\n' && getchar() != '\n')
E 11
I 11
		c = getc(terminal);
		while (c != '\n' && getc(terminal) != '\n')
E 11
D 17
			/* void */;
E 17
I 17
			if (feof(terminal))
D 22
				done(1);
E 22
I 22
				return (FAIL);
E 22
E 17
	} while (c != 'y' && c != 'n');
	if (c == 'y')
		return (GOOD);
	return (FAIL);
I 11
D 18
}

/*
 * Read and parse an interactive command.
 * The first word on the line is assigned to "cmd". If
 * there are no arguments on the command line, then "curdir"
 * is returned as the argument. If there are arguments
 * on the line they are returned one at a time on each
 * successive call to getcmd. Each argument is first assigned
 * to "name". If it does not start with "/" the pathname in
 * "curdir" is prepended to it. Finally "canon" is called to
 * eliminate any embedded ".." components.
 */
getcmd(curdir, cmd, name)
	char *curdir, *cmd, *name;
{
D 14
	register char *cp, *bp;
	char output[BUFSIZ];
	static char input[BUFSIZ];
E 14
I 14
	register char *cp;
E 14
	static char *nextarg = NULL;
I 14
	static char input[BUFSIZ];
	char output[BUFSIZ];
#	define rawname input	/* save space by reusing input buffer */
E 14

	/*
	 * Check to see if still processing arguments.
	 */
	if (nextarg != NULL)
		goto getnext;
D 14
	nextarg = NULL;
E 14
	/*
	 * Read a command line and trim off trailing white space.
	 */
	do	{
		fprintf(stderr, "restore > ");
		(void) fflush(stderr);
		(void) fgets(input, BUFSIZ, terminal);
	} while (!feof(terminal) && input[0] == '\n');
	if (feof(terminal)) {
		(void) strcpy(cmd, "quit");
		return;
	}
	for (cp = &input[strlen(input) - 2]; *cp == ' ' || *cp == '\t'; cp--)
		/* trim off trailing white space and newline */;
	*++cp = '\0';
	/*
	 * Copy the command into "cmd".
	 */
D 14
	for (cp = input; *cp == ' ' || *cp == '\t'; cp++)
		/* skip to command */;
	for (bp = cmd; *cp != ' ' && *cp != '\t' && *cp != '\0'; )
		*bp++ = *cp++;
	*bp = '\0';
E 14
I 14
	cp = copynext(input, cmd);
E 14
	/*
	 * If no argument, use curdir as the default.
	 */
	if (*cp == '\0') {
		(void) strcpy(name, curdir);
		return;
	}
	nextarg = cp;
	/*
	 * Find the next argument.
	 */
getnext:
D 14
	for (cp = nextarg + 1; *cp == ' ' || *cp == '\t'; cp++)
		/* skip to argument */;
	for (bp = cp; *cp != ' ' && *cp != '\t' && *cp != '\0'; cp++)
		/* skip to end of argument */;
E 14
I 14
	cp = copynext(nextarg, rawname);
E 14
	if (*cp == '\0')
		nextarg = NULL;
	else
		nextarg = cp;
D 14
	*cp = '\0';
E 14
	/*
	 * If it an absolute pathname, canonicalize it and return it.
	 */
D 14
	if (*bp == '/') {
		canon(bp, name);
E 14
I 14
	if (rawname[0] == '/') {
		canon(rawname, name);
E 14
		return;
	}
	/*
	 * For relative pathnames, prepend the current directory to
	 * it then canonicalize and return it.
	 */
	(void) strcpy(output, curdir);
	(void) strcat(output, "/");
D 14
	(void) strcat(output, bp);
E 14
I 14
	(void) strcat(output, rawname);
E 14
	canon(output, name);
I 14
#	undef rawname
}

/*
 * Strip off the next token of the input.
 */
char *
copynext(input, output)
	char *input, *output;
{
	register char *cp, *bp;
	char quote;

	for (cp = input; *cp == ' ' || *cp == '\t'; cp++)
		/* skip to argument */;
	bp = output;
	while (*cp != ' ' && *cp != '\t' && *cp != '\0') {
		/*
		 * Handle back slashes.
		 */
		if (*cp == '\\') {
			if (*++cp == '\0') {
				fprintf(stderr,
					"command lines cannot be continued\n");
				continue;
			}
			*bp++ = *cp++;
			continue;
		}
		/*
		 * The usual unquoted case.
		 */
		if (*cp != '\'' && *cp != '"') {
			*bp++ = *cp++;
			continue;
		}
		/*
		 * Handle single and double quotes.
		 */
		quote = *cp++;
		while (*cp != quote && *cp != '\0')
			*bp++ = *cp++;
		if (*cp++ == '\0') {
			fprintf(stderr, "missing %c\n", quote);
			cp--;
			continue;
		}
	}
	*bp = '\0';
	return (cp);
E 14
}

/*
 * respond to interrupts
 */
onintr()
{
	if (reply("restore interrupted, continue") == FAIL)
		done(1);
	if (signal(SIGINT, onintr) == SIG_IGN)
		(void) signal(SIGINT, SIG_IGN);
	if (signal(SIGTERM, onintr) == SIG_IGN)
		(void) signal(SIGTERM, SIG_IGN);
E 18
}

/*
 * handle unexpected inconsistencies
 */
D 29
/* VARARGS1 */
panic(msg, d1, d2)
	char *msg;
	long d1, d2;
E 29
I 29
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
panic(const char *fmt, ...)
#else
panic(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 29
{
I 29
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
E 29

D 29
	fprintf(stderr, msg, d1, d2);
E 29
I 29
	vfprintf(stderr, fmt, ap);
E 29
I 25
	if (yflag)
		return;
E 25
	if (reply("abort") == GOOD) {
		if (reply("dump core") == GOOD)
			abort();
		done(1);
	}
E 11
}
E 1
