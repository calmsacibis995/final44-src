h24540
s 00061/00071/00080
d D 8.2 95/05/04 18:02:11 christos 4 3
c merged netbsd changes
e
s 00002/00002/00149
d D 8.1 93/05/31 15:35:14 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00147
d D 5.2 91/03/08 16:46:23 bostic 2 1
c make the world safe for pcc
e
s 00147/00000/00000
d D 5.1 91/03/07 20:24:25 bostic 1 0
c date and time created 91/03/07 20:24:25 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4
#include <stdlib.h>
E 4
/*
 * Routine for dealing with parsed shell commands.
 */

#include "shell.h"
#include "nodes.h"
#include "memalloc.h"
#include "machdep.h"
#include "mystring.h"


D 4
int funcblocksize;		/* size of structures in function */
int funcstringsize;		/* size of strings in node */
I 2
#ifdef __STDC__
E 4
I 4
int     funcblocksize;		/* size of structures in function */
int     funcstringsize;		/* size of strings in node */
E 4
E 2
pointer funcblock;		/* block to allocate function from */
I 2
D 4
#else
char *funcblock;		/* block to allocate function from */
#endif
E 2
char *funcstring;		/* block to allocate strings from */
E 4
I 4
char   *funcstring;		/* block to allocate strings from */
E 4

%SIZES


D 4
#ifdef __STDC__
STATIC void calcsize(union node *);
STATIC void sizenodelist(struct nodelist *);
STATIC union node *copynode(union node *);
STATIC struct nodelist *copynodelist(struct nodelist *);
STATIC char *nodesavestr(char *);
#else
STATIC void calcsize();
STATIC void sizenodelist();
STATIC union node *copynode();
STATIC struct nodelist *copynodelist();
STATIC char *nodesavestr();
#endif
E 4
I 4
STATIC void calcsize __P((union node *));
STATIC void sizenodelist __P((struct nodelist *));
STATIC union node *copynode __P((union node *));
STATIC struct nodelist *copynodelist __P((struct nodelist *));
STATIC char *nodesavestr __P((char *));
E 4



/*
 * Make a copy of a parse tree.
 */

union node *
copyfunc(n)
D 4
      union node *n;
      {
      if (n == NULL)
	    return NULL;
      funcblocksize = 0;
      funcstringsize = 0;
      calcsize(n);
      funcblock = ckmalloc(funcblocksize + funcstringsize);
      funcstring = funcblock + funcblocksize;
      return copynode(n);
E 4
I 4
	union node *n;
{
	if (n == NULL)
		return NULL;
	funcblocksize = 0;
	funcstringsize = 0;
	calcsize(n);
	funcblock = ckmalloc(funcblocksize + funcstringsize);
	funcstring = funcblock + funcblocksize;
	return copynode(n);
E 4
}



STATIC void
calcsize(n)
D 4
      union node *n;
      {
      %CALCSIZE
E 4
I 4
	union node *n;
{
	%CALCSIZE
E 4
}



STATIC void
sizenodelist(lp)
D 4
      struct nodelist *lp;
      {
      while (lp) {
	    funcblocksize += ALIGN(sizeof (struct nodelist));
	    calcsize(lp->n);
	    lp = lp->next;
      }
E 4
I 4
	struct nodelist *lp;
{
	while (lp) {
		funcblocksize += ALIGN(sizeof(struct nodelist));
		calcsize(lp->n);
		lp = lp->next;
	}
E 4
}



STATIC union node *
copynode(n)
D 4
      union node *n;
      {
      union node *new;
E 4
I 4
	union node *n;
{
	union node *new;
E 4

D 4
      %COPY
      return new;
E 4
I 4
	%COPY
	return new;
E 4
}


STATIC struct nodelist *
copynodelist(lp)
D 4
      struct nodelist *lp;
      {
      struct nodelist *start;
      struct nodelist **lpp;
E 4
I 4
	struct nodelist *lp;
{
	struct nodelist *start;
	struct nodelist **lpp;
E 4

D 4
      lpp = &start;
      while (lp) {
	    *lpp = funcblock;
	    funcblock += ALIGN(sizeof (struct nodelist));
	    (*lpp)->n = copynode(lp->n);
	    lp = lp->next;
	    lpp = &(*lpp)->next;
      }
      *lpp = NULL;
      return start;
E 4
I 4
	lpp = &start;
	while (lp) {
		*lpp = funcblock;
		funcblock += ALIGN(sizeof(struct nodelist));
		(*lpp)->n = copynode(lp->n);
		lp = lp->next;
		lpp = &(*lpp)->next;
	}
	*lpp = NULL;
	return start;
E 4
}



STATIC char *
nodesavestr(s)
D 4
      char *s;
      {
      register char *p = s;
      register char *q = funcstring;
      char *rtn = funcstring;
E 4
I 4
	char   *s;
{
	register char *p = s;
	register char *q = funcstring;
	char   *rtn = funcstring;
E 4

D 4
      while (*q++ = *p++);
      funcstring = q;
      return rtn;
E 4
I 4
	while ((*q++ = *p++) != '\0')
		continue;
	funcstring = q;
	return rtn;
E 4
}



/*
 * Free a parse tree.
 */

void
freefunc(n)
D 4
      union node *n;
      {
      if (n)
	    ckfree(n);
E 4
I 4
	union node *n;
{
	if (n)
		ckfree(n);
E 4
}
E 1
