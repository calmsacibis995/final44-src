h41342
s 00002/00002/00101
d D 8.1 93/06/06 15:08:45 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00099
d D 5.10 92/06/26 12:03:26 bostic 14 13
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00001/00011/00098
d D 5.9 90/06/01 17:00:27 bostic 13 12
c new copyright notice
e
s 00013/00003/00096
d D 5.8 88/07/07 06:55:27 edward 12 11
c removed some unnecessary global vars, dynamically allocate some others,
c added spreserve to fix the no sreset when sourcing kludge
e
s 00012/00007/00087
d D 5.7 88/06/29 21:02:07 bostic 11 10
c install approved copyright notice
e
s 00000/00001/00094
d D 5.6 88/06/16 17:41:31 edward 10 9
c prehistoric (e.g., pre-sendmail) code removed
e
s 00011/00005/00084
d D 5.5 88/02/18 17:04:26 bostic 9 8
c written by Kurt Shoens; added Berkeley specific header
e
s 00000/00000/00089
d D 5.4 87/05/18 12:28:49 edward 8 7
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00002/00002/00087
d D 5.3 86/12/12 12:41:55 bostic 7 5
c fixed allocation alignment for Power 6.
e
s 00001/00001/00088
d D 5.2 85/06/21 17:14:19 mckusick 5 4
c botched copyright
e
s 00007/00001/00082
d D 5.1 85/06/06 10:44:00 dist 4 3
c Add copyright
e
s 00003/00003/00080
d D 2.2 83/08/11 22:20:12 sam 3 2
c standardize sccs keyword lines
e
s 00000/00000/00083
d D 2.1 81/07/01 11:10:29 kurt 2 1
c Release to Heidi Stettner
e
s 00083/00000/00000
d D 1.1 80/10/08 09:51:24 kas 1 0
c date and time created 80/10/08 09:51:24 by kas
e
u
U
f b 
t
T
I 4
/*
D 15
 * Copyright (c) 1980 Regents of the University of California.
D 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 11
E 9
 */

E 4
I 1
D 3
#
E 3
I 3
D 9
#ifndef lint
D 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
I 5
static char *sccsid = "%W% (Berkeley) %G%";
E 5
D 4
#endif
E 4
I 4
#endif not lint
E 9
I 9
D 11
#ifdef notdef
E 11
I 11
#ifndef lint
E 11
static char sccsid[] = "%W% (Berkeley) %G%";
D 11
#endif /* notdef */
E 11
I 11
#endif /* not lint */
E 11
E 9
E 4
E 3

/*
 * Mail -- a mail program
 *
 * String allocation routines.
 * Strings handed out here are reclaimed at the top of the command
 * loop each time, so they need not be freed.
 */

#include "rcv.h"
I 14
#include "extern.h"
E 14
D 3

static char *SccsId = "%W% %G%";
E 3

/*
 * Allocate size more bytes of space and return the address of the
 * first byte to the caller.  An even number of bytes are always
 * allocated so that the space will always be on a word boundary.
 * The string spaces are of exponentially increasing size, to satisfy
 * the occasional user with enormous string size requests.
 */

char *
salloc(size)
I 14
	int size;
E 14
{
	register char *t;
	register int s;
	register struct strings *sp;
	int index;

	s = size;
D 7
	s++;
	s &= ~01;
E 7
I 7
	s += 3;
	s &= ~03;
E 7
	index = 0;
	for (sp = &stringdope[0]; sp < &stringdope[NSPACE]; sp++) {
		if (sp->s_topFree == NOSTR && (STRINGSIZE << index) >= s)
			break;
		if (sp->s_nleft >= s)
			break;
		index++;
	}
	if (sp >= &stringdope[NSPACE])
		panic("String too large");
	if (sp->s_topFree == NOSTR) {
		index = sp - &stringdope[0];
D 12
		sp->s_topFree = (char *) calloc(STRINGSIZE << index,
		    (unsigned) 1);
E 12
I 12
		sp->s_topFree = malloc(STRINGSIZE << index);
E 12
		if (sp->s_topFree == NOSTR) {
			fprintf(stderr, "No room for space %d\n", index);
			panic("Internal error");
		}
		sp->s_nextFree = sp->s_topFree;
		sp->s_nleft = STRINGSIZE << index;
	}
	sp->s_nleft -= s;
	t = sp->s_nextFree;
	sp->s_nextFree += s;
	return(t);
}

/*
 * Reset the string area to be empty.
 * Called to free all strings allocated
 * since last reset.
 */
I 14
void
E 14
D 12

E 12
sreset()
{
	register struct strings *sp;
	register int index;

	if (noreset)
		return;
D 10
	minit();
E 10
	index = 0;
	for (sp = &stringdope[0]; sp < &stringdope[NSPACE]; sp++) {
		if (sp->s_topFree == NOSTR)
			continue;
		sp->s_nextFree = sp->s_topFree;
		sp->s_nleft = STRINGSIZE << index;
		index++;
	}
I 12
}

/*
 * Make the string area permanent.
 * Meant to be called in main, after initialization.
 */
I 14
void
E 14
spreserve()
{
	register struct strings *sp;

	for (sp = &stringdope[0]; sp < &stringdope[NSPACE]; sp++)
		sp->s_topFree = NOSTR;
E 12
}
E 1
