h05355
s 00002/00002/00117
d D 8.1 93/06/06 15:04:23 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00118
d D 5.5 91/11/20 16:27:10 bostic 5 4
c add affiliation for Oz
e
s 00034/00042/00085
d D 5.4 91/09/03 11:38:04 bostic 4 3
c New version from Oz Yigit; BSD-ized
e
s 00004/00003/00123
d D 5.3 91/02/26 14:05:41 bostic 3 2
c ANSI fixes, use strdup(3) instead of rolling your own
e
s 00001/00011/00125
d D 5.2 90/06/01 16:09:40 bostic 2 1
c new copyright notice
e
s 00136/00000/00000
d D 5.1 89/08/28 15:14:17 bostic 1 0
c date and time created 89/08/28 15:14:17 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
D 5
 * Ozan Yigit.
E 5
I 5
 * Ozan Yigit at York University.
E 5
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * look.c
 * Facility: m4 macro processor
 * by: oz
 */

I 4
#include <sys/types.h>
E 4
I 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 3
#include "mdef.h"
D 4
#include "extr.h"
E 4
I 4
#include "stdd.h"
#include "extern.h"
E 4

D 3
extern char *strsave();

E 3
D 4
/*
 *  hash - compute hash value using the proverbial
 *	   hashing function. Taken from K&R.
 */
hash (name)
E 4
I 4
int
hash(name)
E 4
register char *name;
{
D 4
	register int h = 0;
E 4
I 4
	register unsigned long h = 0;
E 4
	while (*name)
D 4
		h += *name++;
E 4
I 4
		h = (h << 5) + h + *name++;
E 4
	return (h % HASHSIZE);
}

/*
D 4
 * lookup - find name in the hash table
 *
E 4
I 4
 * find name in the hash table
E 4
 */
D 4
ndptr lookup(name)
E 4
I 4
ndptr 
lookup(name)
E 4
char *name;
{
	register ndptr p;

	for (p = hashtab[hash(name)]; p != nil; p = p->nxtptr)
D 4
		if (strcmp(name, p->name) == 0)
E 4
I 4
		if (STREQ(name, p->name))
E 4
			break;
	return (p);
}

/*
D 4
 * addent - hash and create an entry in the hash
 *	    table. The new entry is added in front
 *	    of a hash bucket.
E 4
I 4
 * hash and create an entry in the hash table.
 * The new entry is added in front of a hash bucket.
E 4
 */
D 4
ndptr addent(name)
E 4
I 4
ndptr 
addent(name)
E 4
char *name;
{
	register int h;
	ndptr p;

	h = hash(name);
D 4
	if ((p = (ndptr) malloc(sizeof(struct ndblock))) != NULL) {
		p->nxtptr = hashtab[h];
		hashtab[h] = p;
D 3
		p->name = strsave(name);
E 3
I 3
		p->name = strdup(name);
E 3
	}
	else
		error("m4: no more memory.");
E 4
I 4
	p = (ndptr) xalloc(sizeof(struct ndblock));
	p->nxtptr = hashtab[h];
	hashtab[h] = p;
	p->name = xstrdup(name);
E 4
	return p;
}

I 4
static void
freent(p)
ndptr p;
{
	if (!(p->type & STATIC)) {
		free((char *) p->name);
		if (p->defn != null)
			free((char *) p->defn);
	}
	free((char *) p);
}

E 4
/*
D 4
 * remhash - remove an entry from the hashtable
 *
E 4
I 4
 * remove an entry from the hashtable
E 4
 */
I 4
void
E 4
remhash(name, all)
char *name;
int all;
{
	register int h;
	register ndptr xp, tp, mp;

	h = hash(name);
	mp = hashtab[h];
	tp = nil;
	while (mp != nil) {
D 4
		if (strcmp(mp->name, name) == 0) {
E 4
I 4
		if (STREQ(mp->name, name)) {
E 4
			mp = mp->nxtptr;
			if (tp == nil) {
				freent(hashtab[h]);
				hashtab[h] = mp;
			}
			else {
				xp = tp->nxtptr;
				tp->nxtptr = mp;
				freent(xp);
			}
			if (!all)
				break;
		}
		else {
			tp = mp;
			mp = mp->nxtptr;
		}
	}
}
D 4

/*
 * freent - free a hashtable information block
 *
 */
freent(p)
ndptr p;
{
	if (!(p->type & STATIC)) {
		free(p->name);
		if (p->defn != null)
			free(p->defn);
	}
	free(p);
}

E 4
E 1
