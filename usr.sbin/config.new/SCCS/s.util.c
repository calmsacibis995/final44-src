h16912
s 00002/00002/00234
d D 8.1 93/06/06 13:55:14 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00236
d D 5.2 93/04/18 04:23:20 torek 2 1
c rm rcs headers (commit to maintenance on vangogh)
e
s 00238/00000/00000
d D 5.1 93/01/12 02:18:47 torek 1 0
c date and time created 93/01/12 02:18:47 by torek
e
u
U
t
T
I 1
/* 
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 2
 *
 * from: $Header: util.c,v 1.3 93/01/12 03:59:55 torek Exp $
E 2
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "config.h"

static void nomem __P((void));
static void vxerror __P((const char *, int, const char *, va_list));

/* 
 * Malloc, with abort on error.
 */
void *
emalloc(size)
	size_t size;
{
	void *p;

	if ((p = malloc(size)) == NULL)
		nomem();
	return (p);
}

/* 
 * Realloc, with abort on error.
 */
void *
erealloc(p, size)
	void *p;
	size_t size;
{

	if ((p = realloc(p, size)) == NULL)
		nomem();
	return (p);
}

static void
nomem()
{

	(void)fprintf(stderr, "config: out of memory\n");
	exit(1);
}

/*
 * Prepend the compilation directory to a file name.
 */
char *
path(file)
	const char *file;
{
	register char *cp;
#define	CDIR "../../compile/"

	if (file == NULL) {
		cp = emalloc(sizeof(CDIR) + strlen(confdirbase));
		(void)sprintf(cp, "%s%s", CDIR, confdirbase);
	} else {
		cp = emalloc(sizeof(CDIR) + strlen(confdirbase) + 1 +
		    strlen(file));
		(void)sprintf(cp, "%s%s/%s", CDIR, confdirbase, file);
	}
	return (cp);
}

static struct nvlist *nvhead;

struct nvlist *
newnv(name, str, ptr, i)
	const char *name, *str;
	void *ptr;
	int i;
{
	register struct nvlist *nv;

	if ((nv = nvhead) == NULL)
		nv = emalloc(sizeof(*nv));
	else
		nvhead = nv->nv_next;
	nv->nv_next = NULL;
	nv->nv_name = name;
	if (ptr == NULL)
		nv->nv_str = str;
	else {
		if (str != NULL)
			panic("newnv");
		nv->nv_ptr = ptr;
	}
	nv->nv_int = i;
	return (nv);
}

/*
 * Free an nvlist structure (just one).
 */
void
nvfree(nv)
	register struct nvlist *nv;
{

	nv->nv_next = nvhead;
	nvhead = nv;
}

/*
 * Free an nvlist (the whole list).
 */
void
nvfreel(nv)
	register struct nvlist *nv;
{
	register struct nvlist *next;

	for (; nv != NULL; nv = next) {
		next = nv->nv_next;
		nv->nv_next = nvhead;
		nvhead = nv;
	}
}

/*
 * External (config file) error.  Complain, using current file
 * and line number.
 */
void
#if __STDC__
error(const char *fmt, ...)
#else
error(fmt, va_alist)
	const char *fmt;
	va_dcl
#endif
{
	va_list ap;
	extern const char *yyfile;

#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	vxerror(yyfile, currentline(), fmt, ap);
	va_end(ap);
}

/*
 * Delayed config file error (i.e., something was wrong but we could not
 * find out about it until later).
 */
void
#if __STDC__
xerror(const char *file, int line, const char *fmt, ...)
#else
xerror(file, line, fmt, va_alist)
	const char *file;
	int line;
	const char *fmt;
	va_dcl
#endif
{
	va_list ap;

#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	vxerror(file, line, fmt, ap);
	va_end(ap);
}

/*
 * Internal form of error() and xerror().
 */
static void
vxerror(file, line, fmt, ap)
	const char *file;
	int line;
	const char *fmt;
	va_list ap;
{

	(void)fprintf(stderr, "%s:%d: ", file, line);
	(void)vfprintf(stderr, fmt, ap);
	(void)putc('\n', stderr);
	errors++;
}

/*
 * Internal error, abort.
 */
__dead void
#if __STDC__
panic(const char *fmt, ...)
#else
panic(fmt, va_alist)
	const char *fmt;
	va_dcl
#endif
{
	va_list ap;

#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "config: panic: ");
	(void)vfprintf(stderr, fmt, ap);
	(void)putc('\n', stderr);
	va_end(ap);
	exit(2);
}
E 1
