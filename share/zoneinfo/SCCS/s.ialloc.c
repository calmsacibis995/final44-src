h64987
s 00002/00002/00112
d D 8.1 93/06/08 11:21:19 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00003/00099
d D 5.3 91/04/20 15:35:00 bostic 3 2
c new copyright; att/bsd/shared
e
s 00012/00013/00090
d D 5.2 91/02/28 18:56:46 bostic 2 1
c get rid of the "portability" sugar
e
s 00103/00000/00000
d D 5.1 90/02/02 17:24:05 bostic 1 0
c date and time created 90/02/02 17:24:05 by bostic
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Arthur David Olson of the National Cancer Institute.
 *
 * %sccs.include.redist.c%
 */

E 3
I 1
#ifndef lint
D 3
#ifndef NOID
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#ifdef notdef
E 3
static char	elsieid[] = "@(#)ialloc.c	8.18";
D 3
#endif /* !defined NOID */
#endif /* !defined lint */
E 3
I 3
#endif
E 3

/*LINTLIBRARY*/

D 2
#include "string.h"
#include "stdlib.h"
#include "nonstd.h"
E 2
I 2
#include <string.h>
#include <stdlib.h>
E 2

#ifdef MAL
#define NULLMAL(x)	((x) == NULL || (x) == MAL)
#else /* !defined MAL */
#define NULLMAL(x)	((x) == NULL)
#endif /* !defined MAL */

#define nonzero(n)	(((n) == 0) ? 1 : (n))

D 2
char *	icalloc P((int nelem, int elsize));
char *	icatalloc P((char * old, const char * new));
char *	icpyalloc P((const char * string));
char *	imalloc P((int n));
char *	irealloc P((char * pointer, int size));
void	ifree P((char * pointer));
E 2
I 2
char *	icalloc __P((int nelem, int elsize));
char *	icatalloc __P((char * old, const char * new));
char *	icpyalloc __P((const char * string));
char *	imalloc __P((int n));
char *	irealloc __P((char * pointer, int size));
void	ifree __P((char * pointer));
E 2

char *
imalloc(n)
const int	n;
{
#ifdef MAL
	register char *	result;

D 2
	result = malloc((alloc_size_t) nonzero(n));
E 2
I 2
	result = malloc((size_t) nonzero(n));
E 2
	return NULLMAL(result) ? NULL : result;
#else /* !defined MAL */
D 2
	return malloc((alloc_size_t) nonzero(n));
E 2
I 2
	return malloc((size_t) nonzero(n));
E 2
#endif /* !defined MAL */
}

char *
icalloc(nelem, elsize)
int	nelem;
int	elsize;
{
	if (nelem == 0 || elsize == 0)
		nelem = elsize = 1;
D 2
	return calloc((alloc_size_t) nelem, (alloc_size_t) elsize);
E 2
I 2
	return calloc((size_t) nelem, (size_t) elsize);
E 2
}

char *
irealloc(pointer, size)
char * const	pointer;
const int	size;
{
	if (NULLMAL(pointer))
		return imalloc(size);
D 2
	return realloc((genericptr_t) pointer, (alloc_size_t) nonzero(size));
E 2
I 2
	return realloc((void *) pointer, (size_t) nonzero(size));
E 2
}

char *
icatalloc(old, new)
char * const		old;
const char * const	new;
{
	register char *	result;
	register	oldsize, newsize;

	newsize = NULLMAL(new) ? 0 : strlen(new);
	if (NULLMAL(old))
		oldsize = 0;
	else if (newsize == 0)
		return old;
	else	oldsize = strlen(old);
	if ((result = irealloc(old, oldsize + newsize + 1)) != NULL)
		if (!NULLMAL(new))
			(void) strcpy(result + oldsize, new);
	return result;
}

char *
icpyalloc(string)
const char * const	string;
{
	return icatalloc((char *) NULL, string);
}

void
ifree(p)
char * const	p;
{
	if (!NULLMAL(p))
		(void) free(p);
}

void
icfree(p)
char * const	p;
{
	if (!NULLMAL(p))
		(void) free(p);
}
E 1
