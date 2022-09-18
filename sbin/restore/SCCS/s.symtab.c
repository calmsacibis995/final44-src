h47599
s 00006/00007/00596
d D 8.3 95/04/28 10:57:39 bostic 28 27
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00598
d D 8.2 94/09/13 12:26:44 mckusick 27 26
c add support for restoring whiteouts
e
s 00002/00002/00601
d D 8.1 93/06/05 11:12:11 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00602
d D 5.8 93/02/11 08:28:42 bostic 25 24
c gcc -Wall from Craig Leres (no substantive changes)
e
s 00074/00050/00529
d D 5.7 92/10/16 16:21:26 bostic 24 23
c ANSI C, convert options handling to getopt(3)
e
s 00001/00002/00578
d D 5.6 91/07/29 16:42:29 mckusick 23 22
c use POSIX constant NAME_MAX rather than MAXNAMLEN from dir.h
e
s 00001/00011/00579
d D 5.5 90/06/01 16:21:21 bostic 22 21
c new copyright notice
e
s 00001/00000/00589
d D 5.4 90/02/15 13:14:43 mckusick 21 20
c need to include ufs/dir.h since no longer done by restore.h
e
s 00015/00004/00574
d D 5.3 88/10/24 16:38:33 bostic 20 19
c Berkeley copyright notice
e
s 00002/00000/00576
d D 5.2 88/05/13 14:47:58 mckusick 19 18
c add Nflag to request not to do any writes
e
s 00008/00004/00568
d D 5.1 85/05/28 15:15:35 dist 18 17
c Add copyright
e
s 00004/00000/00568
d D 3.17 85/03/24 18:11:17 mckusick 17 16
c dynamically calculate tape block size unless specified on command line
e
s 00000/00001/00568
d D 3.16 85/01/18 22:38:52 mckusick 16 15
c reorganize to split out interactive shell
e
s 00002/00002/00567
d D 3.15 83/08/11 23:06:44 sam 15 14
c standardize sccs keyword lines
e
s 00002/00000/00567
d D 3.14 83/07/08 16:49:19 mckusick 14 13
c guard all dynamic allocations
e
s 00001/00001/00566
d D 3.13 83/07/01 03:10:23 sam 13 12
c include fixes
e
s 00004/00002/00563
d D 3.12 83/05/15 00:47:17 mckusick 12 11
c have to save values before releasing the entry
e
s 00001/00001/00564
d D 3.11 83/05/14 14:41:33 mckusick 11 10
c want to alloc sizeof(char), NOT sizeof(char *)
e
s 00002/00001/00563
d D 3.10 83/05/03 23:32:39 mckusick 10 9
c mark ROOTINO as NEW so that it can be "deleted" in interactive mode
e
s 00001/00000/00563
d D 3.9 83/03/27 18:26:04 mckusick 9 8
c all entries have an inode number
e
s 00008/00008/00555
d D 3.8 83/03/27 13:06:55 mckusick 8 7
c lint
e
s 00097/00037/00466
d D 3.7 83/03/23 08:59:16 mckusick 7 6
c keep a list of unused names; add comments!
e
s 00061/00050/00442
d D 3.6 83/03/08 13:38:34 mckusick 6 5
c get 'r' and 'R' commands working
e
s 00080/00053/00412
d D 3.5 83/01/16 06:03:56 mckusick 5 4
c new incremental restore algorithm
e
s 00004/00014/00461
d D 3.4 83/02/28 00:39:28 mckusick 4 3
c clean up interface with getvol() and findinode()
e
s 00007/00004/00468
d D 3.3 83/02/27 14:39:48 mckusick 3 2
c get "x" command working
e
s 00041/00002/00431
d D 3.2 83/02/26 18:26:43 mckusick 2 1
c get the tape subsystem working; get "t" command working
e
s 00433/00000/00000
d D 3.1 83/02/18 00:41:40 mckusick 1 0
c date and time created 83/02/18 00:41:40 by mckusick
e
u
U
t
T
I 1
D 15
/* Copyright (c) 1983 Regents of the University of California */

E 15
D 18
#ifndef lint
static char sccsid[] = "%W%	(Berkeley)	%E%";
#endif
E 18
I 18
/*
D 20
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
D 26
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 26
I 26
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 22
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
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 20
 */
E 18
I 15

D 18
/* Copyright (c) 1983 Regents of the University of California */
E 18
I 18
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20
E 18
E 15

I 7
/*
 * These routines maintain the symbol table which tracks the state
 * of the file system being restored. They provide lookup by either
 * name or inode number. They also provide for creation, deletion,
 * and renaming of entries. Because of the dynamic nature of pathnames,
 * names should not be saved, but always constructed just before they
 * are needed, by calling "myname".
 */

E 7
D 24
#include "restore.h"
E 24
I 24
#include <sys/param.h>
E 24
#include <sys/stat.h>
I 21
D 23
#include <ufs/dir.h>
E 23
E 21
I 7
D 13
#include <dir.h>
E 13
I 13
D 16
#include <sys/dir.h>
E 16
E 13
E 7

I 24
#include <ufs/ufs/dinode.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "restore.h"
#include "extern.h"

E 24
D 7
struct symtableheader {
	long	volno;
	long	stringsize;
I 5
	long	entrytblsize;
E 5
I 2
	time_t	dumptime;
	time_t	dumpdate;
E 2
	ino_t	maxino;
};

D 5
struct entry *freelist = NIL;
E 5
I 5
static struct entry *freelist = NIL;
E 7
I 7
/*
 * The following variables define the inode symbol table.
 * The primary hash table is dynamically allocated based on
 * the number of inodes in the file system (maxino), scaled by
 * HASHFACTOR. The variable "entry" points to the hash table;
 * the variable "entrytblsize" indicates its size (in entries).
 */
#define HASHFACTOR 5
E 7
static struct entry **entry;
static long entrytblsize;
D 7
/* used to scale maxino to get inode hash table size */
#define HASHFACTOR 5
E 7
E 5

I 24
static void		 addino __P((ino_t, struct entry *));
static struct entry	*lookupparent __P((char *));
static void		 removeentry __P((struct entry *));

E 24
D 5
#ifndef lookupino
E 5
/*
 * Look up an entry by inode number
 */
struct entry *
lookupino(inum)
	ino_t inum;
{
I 5
	register struct entry *ep;
E 5

D 5
	return (entry[inum]);
E 5
I 5
D 27
	if (inum < ROOTINO || inum >= maxino)
E 27
I 27
	if (inum < WINO || inum >= maxino)
E 27
D 24
		return (NIL);
	for (ep = entry[inum % entrytblsize]; ep != NIL; ep = ep->e_next)
E 24
I 24
		return (NULL);
	for (ep = entry[inum % entrytblsize]; ep != NULL; ep = ep->e_next)
E 24
		if (ep->e_ino == inum)
			return (ep);
D 24
	return (NIL);
E 24
I 24
	return (NULL);
E 24
E 5
}
D 5
#endif lookupino
E 5

D 5
#ifndef addino
E 5
/*
 * Add an entry into the entry table
 */
I 24
static void
E 24
addino(inum, np)
D 5
	long inum;
E 5
I 5
	ino_t inum;
E 5
	struct entry *np;
{
I 5
	struct entry **epp;
E 5

D 5
	entry[inum] = np;
E 5
I 5
D 27
	if (inum < ROOTINO || inum >= maxino)
E 27
I 27
	if (inum < WINO || inum >= maxino)
E 27
		panic("addino: out of range %d\n", inum);
	epp = &entry[inum % entrytblsize];
I 6
	np->e_ino = inum;
E 6
	np->e_next = *epp;
	*epp = np;
	if (dflag)
D 24
		for (np = np->e_next; np != NIL; np = np->e_next)
E 24
I 24
		for (np = np->e_next; np != NULL; np = np->e_next)
E 24
			if (np->e_ino == inum)
				badentry(np, "duplicate inum");
E 5
}
D 5
#endif addino
E 5

D 5
#ifndef deleteino
E 5
/*
 * Delete an entry from the entry table
 */
I 24
void
E 24
deleteino(inum)
D 5
	long inum;
E 5
I 5
	ino_t inum;
E 5
{
I 5
	register struct entry *next;
	struct entry **prev;
E 5

D 5
	entry[inum] = NIL;
E 5
I 5
D 27
	if (inum < ROOTINO || inum >= maxino)
E 27
I 27
	if (inum < WINO || inum >= maxino)
E 27
		panic("deleteino: out of range %d\n", inum);
	prev = &entry[inum % entrytblsize];
D 24
	for (next = *prev; next != NIL; next = next->e_next) {
E 24
I 24
	for (next = *prev; next != NULL; next = next->e_next) {
E 24
		if (next->e_ino == inum) {
I 6
			next->e_ino = 0;
E 6
			*prev = next->e_next;
			return;
		}
		prev = &next->e_next;
	}
	panic("deleteino: %d not found\n", inum);
E 5
}
D 5
#endif deleteino
E 5

/*
 * Look up an entry by name
 */
struct entry *
lookupname(name)
	char *name;
{
	register struct entry *ep;
	register char *np, *cp;
D 7
	char buf[BUFSIZ];
E 7
I 7
	char buf[MAXPATHLEN];
E 7

	cp = name;
D 24
	for (ep = lookupino(ROOTINO); ep != NIL; ep = ep->e_entries) {
E 24
I 24
	for (ep = lookupino(ROOTINO); ep != NULL; ep = ep->e_entries) {
E 24
		for (np = buf; *cp != '/' && *cp != '\0'; )
			*np++ = *cp++;
		*np = '\0';
D 24
		for ( ; ep != NIL; ep = ep->e_sibling)
E 24
I 24
		for ( ; ep != NULL; ep = ep->e_sibling)
E 24
			if (strcmp(ep->e_name, buf) == 0)
				break;
D 24
		if (ep == NIL)
E 24
I 24
		if (ep == NULL)
E 24
			break;
D 3
		if (*cp == '\0')
E 3
I 3
		if (*cp++ == '\0')
E 3
			return (ep);
	}
D 3
	/* NOTREACHED */
E 3
I 3
D 24
	return (NIL);
E 24
I 24
	return (NULL);
E 24
E 3
}

/*
 * Look up the parent of a pathname
 */
D 24
struct entry *
E 24
I 24
static struct entry *
E 24
lookupparent(name)
	char *name;
{
	struct entry *ep;
	char *tailindex;

D 28
	tailindex = rindex(name, '/');
E 28
I 28
	tailindex = strrchr(name, '/');
E 28
D 25
	if (tailindex == 0)
E 25
I 25
	if (tailindex == NULL)
E 25
D 24
		return (NIL);
E 24
I 24
		return (NULL);
E 24
	*tailindex = '\0';
	ep = lookupname(name);
I 3
	*tailindex = '/';
E 3
D 24
	if (ep == NIL)
		return (NIL);
E 24
I 24
	if (ep == NULL)
		return (NULL);
E 24
	if (ep->e_type != NODE)
		panic("%s is not a directory\n", name);
D 3
	*tailindex = '/';
E 3
	return (ep);
}

/*
 * Determine the current pathname of a node or leaf
 */
char *
myname(ep)
	register struct entry *ep;
{
	register char *cp;
D 7
	static char namebuf[BUFSIZ];
E 7
I 7
	static char namebuf[MAXPATHLEN];
E 7

D 7
	for (cp = &namebuf[BUFSIZ - 2]; cp > &namebuf[ep->e_namlen]; ) {
E 7
I 7
	for (cp = &namebuf[MAXPATHLEN - 2]; cp > &namebuf[ep->e_namlen]; ) {
E 7
		cp -= ep->e_namlen;
D 28
		bcopy(ep->e_name, cp, (long)ep->e_namlen);
E 28
I 28
		memmove(cp, ep->e_name, (long)ep->e_namlen);
E 28
		if (ep == lookupino(ROOTINO))
			return (cp);
		*(--cp) = '/';
		ep = ep->e_parent;
	}
	panic("%s: pathname too long\n", cp);
	return(cp);
}

/*
I 7
 * Unused symbol table entries are linked together on a freelist
 * headed by the following pointer.
 */
D 24
static struct entry *freelist = NIL;
E 24
I 24
static struct entry *freelist = NULL;
E 24

/*
E 7
 * add an entry to the symbol table
 */
struct entry *
addentry(name, inum, type)
	char *name;
	ino_t inum;
	int type;
{
	register struct entry *np, *ep;

D 24
	if (freelist != NIL) {
E 24
I 24
	if (freelist != NULL) {
E 24
		np = freelist;
D 6
		freelist = np->e_sibling;
E 6
I 6
		freelist = np->e_next;
E 6
D 28
		bzero((char *)np, (long)sizeof(struct entry));
E 28
I 28
		memset(np, 0, (long)sizeof(struct entry));
E 28
	} else {
		np = (struct entry *)calloc(1, sizeof(struct entry));
I 14
D 24
		if (np == NIL)
E 24
I 24
		if (np == NULL)
E 24
			panic("no memory to extend symbol table\n");
E 14
	}
D 6
	np->e_ino = inum;
E 6
	np->e_type = type & ~LINK;
	ep = lookupparent(name);
D 24
	if (ep == NIL) {
		if (inum != ROOTINO || lookupino(ROOTINO) != NIL)
E 24
I 24
	if (ep == NULL) {
		if (inum != ROOTINO || lookupino(ROOTINO) != NULL)
E 24
			panic("bad name to addentry %s\n", name);
		np->e_name = savename(name);
		np->e_namlen = strlen(name);
		np->e_parent = np;
		addino(ROOTINO, np);
		return (np);
	}
D 28
	np->e_name = savename(rindex(name, '/') + 1);
E 28
I 28
	np->e_name = savename(strrchr(name, '/') + 1);
E 28
	np->e_namlen = strlen(np->e_name);
	np->e_parent = ep;
	np->e_sibling = ep->e_entries;
	ep->e_entries = np;
	if (type & LINK) {
		ep = lookupino(inum);
D 24
		if (ep == NIL)
E 24
I 24
		if (ep == NULL)
E 24
			panic("link to non-existant name\n");
I 9
		np->e_ino = inum;
E 9
		np->e_links = ep->e_links;
		ep->e_links = np;
	} else if (inum != 0) {
D 24
		if (lookupino(inum) != NIL)
E 24
I 24
		if (lookupino(inum) != NULL)
E 24
			panic("duplicate entry\n");
		addino(inum, np);
	}
	return (np);
}

/*
 * delete an entry from the symbol table
 */
I 24
void
E 24
freeentry(ep)
	register struct entry *ep;
{
	register struct entry *np;
I 12
	ino_t inum;
E 12

D 6
	np = lookupino(ep->e_ino);
	if (np == NIL)
		badentry(ep, "lookupino failed");
E 6
	if (ep->e_flags != REMOVED)
		badentry(ep, "not marked REMOVED");
D 6
	if (np->e_type == NODE) {
		if (np == ep && np->e_links != NIL)
E 6
I 6
	if (ep->e_type == NODE) {
D 24
		if (ep->e_links != NIL)
E 24
I 24
		if (ep->e_links != NULL)
E 24
E 6
			badentry(ep, "freeing referenced directory");
D 24
		if (ep->e_entries != NIL)
E 24
I 24
		if (ep->e_entries != NULL)
E 24
			badentry(ep, "freeing non-empty directory");
	}
D 6
	if (np == ep) {
		deleteino(ep->e_ino);
		addino(ep->e_ino, ep->e_links);
	} else {
		for (; np != NIL; np = np->e_links) {
			if (np->e_links == ep) {
				np->e_links = ep->e_links;
				break;
E 6
I 6
	if (ep->e_ino != 0) {
		np = lookupino(ep->e_ino);
D 24
		if (np == NIL)
E 24
I 24
		if (np == NULL)
E 24
			badentry(ep, "lookupino failed");
		if (np == ep) {
D 12
			deleteino(ep->e_ino);
E 12
I 12
			inum = ep->e_ino;
			deleteino(inum);
E 12
D 24
			if (ep->e_links != NIL)
E 24
I 24
			if (ep->e_links != NULL)
E 24
D 12
				addino(ep->e_ino, ep->e_links);
E 12
I 12
				addino(inum, ep->e_links);
E 12
		} else {
D 24
			for (; np != NIL; np = np->e_links) {
E 24
I 24
			for (; np != NULL; np = np->e_links) {
E 24
				if (np->e_links == ep) {
					np->e_links = ep->e_links;
					break;
				}
E 6
			}
I 6
D 24
			if (np == NIL)
E 24
I 24
			if (np == NULL)
E 24
				badentry(ep, "link not found");
E 6
		}
D 6
		if (np == NIL)
			badentry(ep, "link not found");
E 6
	}
	removeentry(ep);
I 7
	freename(ep->e_name);
E 7
D 6
	free(ep->e_name);
D 5
	if (ep->e_newname != NULL)
		free(ep->e_newname);
E 5
	ep->e_sibling = freelist;
E 6
I 6
	ep->e_next = freelist;
E 6
	freelist = ep;
}

/*
D 5
 * change the number associated with an entry
 */
renumber(ep, newinum)
	struct entry *ep;
	ino_t newinum;
{
	register struct entry *np;

	if (lookupino(newinum) != NIL)
		badentry(ep, "renumber to active inum");
	np = lookupino(ep->e_ino);
	if (np == NIL)
		badentry(ep, "lookupino failed");
	deleteino(ep->e_ino);
	addino(newinum, ep);
	for (; np != NIL; np = np->e_links)
		np->e_ino = newinum;
}

/*
E 5
 * Relocate an entry in the tree structure
 */
I 24
void
E 24
moveentry(ep, newname)
	register struct entry *ep;
	char *newname;
{
	struct entry *np;
	char *cp;
D 8
	long len;
E 8

	np = lookupparent(newname);
D 24
	if (np == NIL)
E 24
I 24
	if (np == NULL)
E 24
		badentry(ep, "cannot move ROOT");
	if (np != ep->e_parent) {
		removeentry(ep);
		ep->e_parent = np;
		ep->e_sibling = np->e_entries;
		np->e_entries = ep;
	}
D 28
	cp = rindex(newname, '/') + 1;
E 28
I 28
	cp = strrchr(newname, '/') + 1;
E 28
D 7
	len = strlen(cp);
	if (ep->e_flags & TMPNAME)
		ep->e_namlen--;
	if (ep->e_namlen >= len) {
		strcpy(ep->e_name, cp);
	} else {
D 6
		free(ep->e_name);
E 6
		ep->e_name = savename(cp);
	}
	ep->e_namlen = len;
	if (cp[len - 1] == TMPCHAR)
E 7
I 7
	freename(ep->e_name);
	ep->e_name = savename(cp);
	ep->e_namlen = strlen(cp);
	if (strcmp(gentempname(ep), ep->e_name) == 0)
E 7
		ep->e_flags |= TMPNAME;
	else
		ep->e_flags &= ~TMPNAME;
}

/*
 * Remove an entry in the tree structure
 */
I 24
static void
E 24
removeentry(ep)
	register struct entry *ep;
{
	register struct entry *np;

	np = ep->e_parent;
	if (np->e_entries == ep) {
		np->e_entries = ep->e_sibling;
	} else {
D 24
		for (np = np->e_entries; np != NIL; np = np->e_sibling) {
E 24
I 24
		for (np = np->e_entries; np != NULL; np = np->e_sibling) {
E 24
			if (np->e_sibling == ep) {
				np->e_sibling = ep->e_sibling;
				break;
			}
		}
D 24
		if (np == NIL)
E 24
I 24
		if (np == NULL)
E 24
			badentry(ep, "cannot find entry in parent list");
	}
}

/*
D 7
 * allocate space for a name
E 7
I 7
 * Table of unused string entries, sorted by length.
 * 
 * Entries are allocated in STRTBLINCR sized pieces so that names
 * of similar lengths can use the same entry. The value of STRTBLINCR
 * is chosen so that every entry has at least enough space to hold
 * a "struct strtbl" header. Thus every entry can be linked onto an
 * apprpriate free list.
 *
 * NB. The macro "allocsize" below assumes that "struct strhdr"
 *     has a size that is a power of two.
E 7
 */
I 7
struct strhdr {
	struct strhdr *next;
};

#define STRTBLINCR	(sizeof(struct strhdr))
#define allocsize(size)	(((size) + 1 + STRTBLINCR - 1) & ~(STRTBLINCR - 1))

D 23
static struct strhdr strtblhdr[allocsize(MAXNAMLEN) / STRTBLINCR];
E 23
I 23
static struct strhdr strtblhdr[allocsize(NAME_MAX) / STRTBLINCR];
E 23

/*
 * Allocate space for a name. It first looks to see if it already
 * has an appropriate sized entry, and if not allocates a new one.
 */
E 7
char *
savename(name)
	char *name;
{
I 7
	struct strhdr *np;
E 7
	long len;
I 3
	char *cp;
E 3

	if (name == NULL)
		panic("bad name\n");
D 7
	len = strlen(name) + 2;
D 6
	len = (len + 3) & ~3;
E 6
I 6
	len = (len + sizeof(int) - 1) & ~(sizeof(int) - 1);
E 6
D 3
	return ((char *)malloc((unsigned)len));
E 3
I 3
D 5
	cp = (char *)malloc((unsigned)len);
	strcpy(cp, name);
E 5
I 5
	cp = malloc((unsigned)len);
E 7
I 7
	len = strlen(name);
	np = strtblhdr[len / STRTBLINCR].next;
	if (np != NULL) {
		strtblhdr[len / STRTBLINCR].next = np->next;
		cp = (char *)np;
	} else {
		cp = malloc((unsigned)allocsize(len));
		if (cp == NULL)
			panic("no space for string table\n");
	}
E 7
	(void) strcpy(cp, name);
E 5
	return (cp);
E 3
}

/*
I 7
 * Free space for a name. The resulting entry is linked onto the
 * appropriate free list.
 */
I 24
void
E 24
freename(name)
	char *name;
{
	struct strhdr *tp, *np;
	
	tp = &strtblhdr[strlen(name) / STRTBLINCR];
	np = (struct strhdr *)name;
	np->next = tp->next;
	tp->next = np;
}

/*
 * Useful quantities placed at the end of a dumped symbol table.
 */
struct symtableheader {
	long	volno;
	long	stringsize;
	long	entrytblsize;
	time_t	dumptime;
	time_t	dumpdate;
	ino_t	maxino;
I 17
	long	ntrec;
E 17
};

/*
E 7
 * dump a snapshot of the symbol table
 */
I 24
void
E 24
dumpsymtable(filename, checkpt)
	char *filename;
	long checkpt;
{
D 6
	register struct entry *ep;
E 6
I 6
	register struct entry *ep, *tep;
E 6
D 5
	register long i;
E 5
I 5
	register ino_t i;
E 5
D 6
	struct entry *next;
	long mynum = 0, stroff = 0;
E 6
I 6
	struct entry temp, *tentry;
	long mynum = 1, stroff = 0;
E 6
	FILE *fd;
	struct symtableheader hdr;

	vprintf(stdout, "Check pointing the restore\n");
I 19
	if (Nflag)
		return;
E 19
	if ((fd = fopen(filename, "w")) == NULL) {
D 24
		perror("fopen");
E 24
I 24
		fprintf(stderr, "fopen: %s\n", strerror(errno));
E 24
		panic("cannot create save file %s for symbol table\n",
			filename);
	}
	clearerr(fd);
	/*
	 * Assign indicies to each entry
	 * Write out the string entries
	 */
D 27
	for (i = ROOTINO; i < maxino; i++) {
E 27
I 27
	for (i = WINO; i <= maxino; i++) {
E 27
D 24
		for (ep = lookupino(i); ep != NIL; ep = ep->e_links) {
E 24
I 24
		for (ep = lookupino(i); ep != NULL; ep = ep->e_links) {
E 24
D 5
			ep->e_newname = (char *)mynum++;
E 5
I 5
			ep->e_index = mynum++;
E 5
D 6
			fwrite(ep->e_name, sizeof(char), (int)ep->e_namlen, fd);
			ep->e_name = (char *)stroff;
			stroff += ep->e_namlen;
E 6
I 6
D 7
			fwrite(ep->e_name, sizeof(char), ep->e_namlen + 2, fd);
			stroff += ep->e_namlen + 2;
E 7
I 7
D 8
			fwrite(ep->e_name, sizeof(char),
			       allocsize(ep->e_namlen), fd);
E 8
I 8
			(void) fwrite(ep->e_name, sizeof(char),
			       (int)allocsize(ep->e_namlen), fd);
E 8
E 7
E 6
		}
	}
	/*
D 6
	 * Convert entry pointers to indexes, and output
E 6
I 6
D 7
	 * start entries on aligned boundry
E 6
	 */
D 5
	for (i = 0; i < maxino; i++) {
E 5
I 5
D 6
	for (i = 0; i < entrytblsize; i++) {
E 5
		if (entry[i] == NIL)
			continue;
D 5
		entry[i] = (struct entry *)entry[i]->e_newname;
E 5
I 5
		entry[i] = (struct entry *)entry[i]->e_index;
E 5
	}
D 5
	fwrite((char *)entry, sizeof(struct entry *), (int)maxino, fd);
E 5
I 5
	fwrite((char *)entry, sizeof(struct entry *), (int)entrytblsize, fd);
E 6
I 6
	fseek(fd, ((stroff + 3) & ~3), 0);
E 6
E 5
	/*
E 7
	 * Convert pointers to indexes, and output
	 */
I 6
	tep = &temp;
	stroff = 0;
E 6
D 27
	for (i = ROOTINO; i < maxino; i++) {
E 27
I 27
	for (i = WINO; i <= maxino; i++) {
E 27
D 6
		for (ep = lookupino(i); ep != NIL; ep = next) {
			next = ep->e_links;
D 5
			ep->e_parent = (struct entry *)ep->e_parent->e_newname;
			ep->e_links = (struct entry *)ep->e_links->e_newname;
			ep->e_sibling =
				(struct entry *)ep->e_sibling->e_newname;
			ep->e_entries =
				(struct entry *)ep->e_entries->e_newname;
E 5
I 5
			ep->e_parent = (struct entry *)ep->e_parent->e_index;
E 6
I 6
D 24
		for (ep = lookupino(i); ep != NIL; ep = ep->e_links) {
E 24
I 24
		for (ep = lookupino(i); ep != NULL; ep = ep->e_links) {
E 24
D 8
			bcopy((char *)ep, (char *)tep, sizeof(struct entry));
E 8
I 8
D 28
			bcopy((char *)ep, (char *)tep,
				(long)sizeof(struct entry));
E 28
I 28
			memmove(tep, ep, (long)sizeof(struct entry));
E 28
E 8
			tep->e_name = (char *)stroff;
D 7
			stroff += ep->e_namlen + 2;
E 7
I 7
			stroff += allocsize(ep->e_namlen);
E 7
			tep->e_parent = (struct entry *)ep->e_parent->e_index;
E 6
D 24
			if (ep->e_links != NIL)
E 24
I 24
			if (ep->e_links != NULL)
E 24
D 6
				ep->e_links =
E 6
I 6
				tep->e_links =
E 6
					(struct entry *)ep->e_links->e_index;
D 24
			if (ep->e_sibling != NIL)
E 24
I 24
			if (ep->e_sibling != NULL)
E 24
D 6
				ep->e_sibling =
E 6
I 6
				tep->e_sibling =
E 6
					(struct entry *)ep->e_sibling->e_index;
D 24
			if (ep->e_entries != NIL)
E 24
I 24
			if (ep->e_entries != NULL)
E 24
D 6
				ep->e_entries =
E 6
I 6
				tep->e_entries =
E 6
					(struct entry *)ep->e_entries->e_index;
D 24
			if (ep->e_next != NIL)
E 24
I 24
			if (ep->e_next != NULL)
E 24
D 6
				ep->e_next =
E 6
I 6
				tep->e_next =
E 6
					(struct entry *)ep->e_next->e_index;
E 5
D 6
			fwrite((char *)ep, sizeof(struct entry), 1, fd);
E 6
I 6
D 8
			fwrite((char *)tep, sizeof(struct entry), 1, fd);
E 8
I 8
			(void) fwrite((char *)tep, sizeof(struct entry), 1, fd);
E 8
E 6
		}
	}
I 6
	/*
	 * Convert entry pointers to indexes, and output
	 */
	for (i = 0; i < entrytblsize; i++) {
D 24
		if (entry[i] == NIL)
			tentry = NIL;
E 24
I 24
		if (entry[i] == NULL)
			tentry = NULL;
E 24
		else
			tentry = (struct entry *)entry[i]->e_index;
D 8
		fwrite((char *)&tentry, sizeof(struct entry *), 1, fd);
E 8
I 8
		(void) fwrite((char *)&tentry, sizeof(struct entry *), 1, fd);
E 8
	}
E 6
	hdr.volno = checkpt;
	hdr.maxino = maxino;
I 5
	hdr.entrytblsize = entrytblsize;
E 5
D 6
	hdr.stringsize = stroff;
E 6
I 6
D 7
	hdr.stringsize = (stroff + 3) & ~3;
E 7
I 7
	hdr.stringsize = stroff;
E 7
E 6
I 2
	hdr.dumptime = dumptime;
	hdr.dumpdate = dumpdate;
I 17
	hdr.ntrec = ntrec;
E 17
E 2
D 8
	fwrite((char *)&hdr, sizeof(struct symtableheader), 1, fd);
E 8
I 8
	(void) fwrite((char *)&hdr, sizeof(struct symtableheader), 1, fd);
E 8
	if (ferror(fd)) {
D 24
		perror("fwrite");
E 24
I 24
		fprintf(stderr, "fwrite: %s\n", strerror(errno));
E 24
		panic("output error to file %s writing symbol table\n",
			filename);
	}
D 8
	fclose(fd);
E 8
I 8
	(void) fclose(fd);
E 8
}

/*
 * Initialize a symbol table from a file
 */
I 24
void
E 24
initsymtable(filename)
	char *filename;
{
	char *base;
	long tblsize;
	register struct entry *ep;
	struct entry *baseep, *lep;
	struct symtableheader hdr;
	struct stat stbuf;
	register long i;
	int fd;

	vprintf(stdout, "Initialize symbol table.\n");
I 5
	if (filename == NULL) {
		entrytblsize = maxino / HASHFACTOR;
		entry = (struct entry **)
			calloc((unsigned)entrytblsize, sizeof(struct entry *));
D 24
		if (entry == (struct entry **)NIL)
E 24
I 24
		if (entry == (struct entry **)NULL)
E 24
			panic("no memory for entry table\n");
D 10
		(void)addentry(".", ROOTINO, NODE);
E 10
I 10
		ep = addentry(".", ROOTINO, NODE);
		ep->e_flags |= NEW;
E 10
		return;
	}
E 5
D 24
	if ((fd = open(filename, 0)) < 0) {
		perror("open");
E 24
I 24
	if ((fd = open(filename, O_RDONLY, 0)) < 0) {
		fprintf(stderr, "open: %s\n", strerror(errno));
E 24
		panic("cannot open symbol table file %s\n", filename);
	}
	if (fstat(fd, &stbuf) < 0) {
D 24
		perror("stat");
E 24
I 24
		fprintf(stderr, "stat: %s\n", strerror(errno));
E 24
		panic("cannot stat symbol table file %s\n", filename);
	}
	tblsize = stbuf.st_size - sizeof(struct symtableheader);
D 5
	base = (char *)malloc((unsigned)tblsize);
E 5
I 5
D 6
	base = malloc((unsigned)tblsize);
E 6
I 6
D 11
	base = calloc(sizeof(char *), (unsigned)tblsize);
E 11
I 11
	base = calloc(sizeof(char), (unsigned)tblsize);
E 11
E 6
E 5
	if (base == NULL)
		panic("cannot allocate space for symbol table\n");
	if (read(fd, base, (int)tblsize) < 0 ||
	    read(fd, (char *)&hdr, sizeof(struct symtableheader)) < 0) {
D 24
		perror("read");
E 24
I 24
		fprintf(stderr, "read: %s\n", strerror(errno));
E 24
		panic("cannot read symbol table file %s\n", filename);
	}
I 2
	switch (command) {
	case 'r':
		/*
		 * For normal continuation, insure that we are using
		 * the next incremental tape
		 */
D 6
		if (hdr.dumptime != dumpdate) {
			if (hdr.dumptime < dumpdate)
E 6
I 6
		if (hdr.dumpdate != dumptime) {
			if (hdr.dumpdate < dumptime)
E 6
				fprintf(stderr, "Incremental tape too low\n");
			else
				fprintf(stderr, "Incremental tape too high\n");
			done(1);
		}
		break;
	case 'R':
		/*
		 * For restart, insure that we are using the same tape
		 */
D 4
		if (hdr.volno == 1) {
			setup();
			if (dumptime != hdr.dumptime ||
			    dumpdate != hdr.dumpdate) {
				fprintf(stderr, "Wrong dump tape\n");
				done(1);
			}
			extractdirs();
		} else {
			curfile.action = SKIP;
			dumptime = hdr.dumptime;
			dumpdate = hdr.dumpdate;
			getvol(hdr.volno);
		}
E 4
I 4
		curfile.action = SKIP;
		dumptime = hdr.dumptime;
		dumpdate = hdr.dumpdate;
I 17
		if (!bflag)
			newtapebuf(hdr.ntrec);
E 17
		getvol(hdr.volno);
E 4
		break;
	default:
		panic("initsymtable called from command %c\n", command);
		break;
	}
E 2
	maxino = hdr.maxino;
I 5
	entrytblsize = hdr.entrytblsize;
E 5
D 2
	curfile.action = SKIP;
	getvol(hdr.volno);
E 2
D 6
	entry = (struct entry **)(base + hdr.stringsize);
D 5
	baseep = (struct entry *)(&entry[maxino]);
E 5
I 5
	baseep = (struct entry *)(&entry[entrytblsize]);
E 5
	lep = (struct entry *)(base + tblsize);
E 6
I 6
	entry = (struct entry **)
		(base + tblsize - (entrytblsize * sizeof(struct entry *)));
	baseep = (struct entry *)(base + hdr.stringsize - sizeof(struct entry));
	lep = (struct entry *)entry;
E 6
D 5
	for (i = 0; i < maxino; i++) {
E 5
I 5
	for (i = 0; i < entrytblsize; i++) {
E 5
D 24
		if (entry[i] == NIL)
E 24
I 24
		if (entry[i] == NULL)
E 24
			continue;
		entry[i] = &baseep[(long)entry[i]];
	}
D 6
	for (ep = baseep; ep < lep; ep++) {
E 6
I 6
	for (ep = &baseep[1]; ep < lep; ep++) {
E 6
		ep->e_name = base + (long)ep->e_name;
		ep->e_parent = &baseep[(long)ep->e_parent];
D 5
		ep->e_sibling = &baseep[(long)ep->e_sibling];
		ep->e_links = &baseep[(long)ep->e_links];
		ep->e_entries = &baseep[(long)ep->e_entries];
E 5
I 5
D 24
		if (ep->e_sibling != NIL)
E 24
I 24
		if (ep->e_sibling != NULL)
E 24
			ep->e_sibling = &baseep[(long)ep->e_sibling];
D 24
		if (ep->e_links != NIL)
E 24
I 24
		if (ep->e_links != NULL)
E 24
			ep->e_links = &baseep[(long)ep->e_links];
D 24
		if (ep->e_entries != NIL)
E 24
I 24
		if (ep->e_entries != NULL)
E 24
			ep->e_entries = &baseep[(long)ep->e_entries];
D 24
		if (ep->e_next != NIL)
E 24
I 24
		if (ep->e_next != NULL)
E 24
			ep->e_next = &baseep[(long)ep->e_next];
E 5
	}
}
E 1
