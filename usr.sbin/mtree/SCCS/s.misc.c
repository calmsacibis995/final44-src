h63437
s 00002/00002/00097
d D 8.1 93/06/06 14:03:03 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00013/00079
d D 5.2 92/04/17 17:22:29 bostic 2 1
c add needvalue argument to parsekey, "ignore" has no value
e
s 00092/00000/00000
d D 5.1 91/12/11 17:56:44 bostic 1 0
c version 2; add cksum, make keywords flexible, new output format
c date and time created 91/12/11 17:56:44 by bostic
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
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fts.h>
#include <stdio.h>
#include "mtree.h"
#include "extern.h"

extern int lineno;

typedef struct _key {
	char *name;			/* key name */
	u_int val;			/* value */
I 2

#define	NEEDVALUE	0x01
	u_int flags;
E 2
} KEY;

/* NB: the following table must be sorted lexically. */
static KEY keylist[] = {
D 2
	"cksum",	F_CKSUM,
	"gid",		F_GID,
	"gname",	F_GNAME,
	"ignore",	F_IGN,
	"link",		F_SLINK,
	"mode",		F_MODE,
	"nlink",	F_NLINK,
	"size",		F_SIZE,
	"time",		F_TIME,
	"type",		F_TYPE,
	"uid",		F_UID,
	"uname",	F_UNAME,
E 2
I 2
	"cksum",	F_CKSUM,	NEEDVALUE,
	"gid",		F_GID,		NEEDVALUE,
	"gname",	F_GNAME,	NEEDVALUE,
	"ignore",	F_IGN,		0,
	"link",		F_SLINK,	NEEDVALUE,
	"mode",		F_MODE,		NEEDVALUE,
	"nlink",	F_NLINK,	NEEDVALUE,
	"size",		F_SIZE,		NEEDVALUE,
	"time",		F_TIME,		NEEDVALUE,
	"type",		F_TYPE,		NEEDVALUE,
	"uid",		F_UID,		NEEDVALUE,
	"uname",	F_UNAME,	NEEDVALUE,
E 2
};

u_int
D 2
parsekey(name)
E 2
I 2
parsekey(name, needvaluep)
E 2
	char *name;
I 2
	int *needvaluep;
E 2
{
	KEY *k, tmp;
	int keycompare __P((const void *, const void *));

	tmp.name = name;
	k = (KEY *)bsearch(&tmp, keylist, sizeof(keylist) / sizeof(KEY),
	    sizeof(KEY), keycompare);
	if (k == NULL)
		err("unknown keyword %s", name);
I 2

	if (needvaluep)
		*needvaluep = k->flags & NEEDVALUE ? 1 : 0;
E 2
	return (k->val);
}

int
keycompare(a, b)
	const void *a, *b;
{
	return (strcmp(((KEY *)a)->name, ((KEY *)b)->name));
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "mtree: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	if (lineno)
		(void)fprintf(stderr,
		    "mtree: failed at line %d of the specification\n", lineno);
	exit(1);
	/* NOTREACHED */
}
E 1
