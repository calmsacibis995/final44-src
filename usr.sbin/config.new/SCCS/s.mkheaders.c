h50698
s 00002/00002/00120
d D 8.1 93/06/06 13:54:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00122
d D 5.2 93/04/18 04:23:12 torek 2 1
c rm rcs headers (commit to maintenance on vangogh)
e
s 00124/00000/00000
d D 5.1 93/01/12 02:18:41 torek 1 0
c date and time created 93/01/12 02:18:41 by torek
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
 * from: $Header: mkheaders.c,v 1.2 93/01/12 03:58:42 torek Exp $
E 2
 */

#include <sys/param.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

static int emitcnt __P((struct nvlist *));
static int err __P((const char *, char *, FILE *));
static char *cntname __P((const char *));

/*
 * Make headers containing counts, as needed.
 */
int
mkheaders()
{
	register struct files *fi;

	for (fi = allfiles; fi != NULL; fi = fi->fi_next) {
		if (fi->fi_flags & FI_HIDDEN)
			continue;
		if (fi->fi_flags & (FI_NEEDSCOUNT | FI_NEEDSFLAG) &&
		    emitcnt(fi->fi_opt))
			return (1);
	}
	return (0);
}

static int
emitcnt(head)
	register struct nvlist *head;
{
	register struct nvlist *nv;
	register FILE *fp;
	register char *fname;
	int cnt;
	char nam[100];
	char buf[BUFSIZ];

	(void)sprintf(buf, "%s.h", head->nv_name);
	fname = path(buf);
	if ((fp = fopen(fname, "r")) == NULL)
		goto writeit;
	nv = head;
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		if (nv == NULL)
			goto writeit;
		if (sscanf(buf, "#define %s %d", nam, &cnt) != 2 ||
		    strcmp(nam, cntname(nv->nv_name)) != 0 ||
		    cnt != nv->nv_int)
			goto writeit;
		nv = nv->nv_next;
	}
	if (ferror(fp))
		return (err("read", fname, fp));
	(void)fclose(fp);
	if (nv == NULL)
		return (0);
writeit:
	if ((fp = fopen(fname, "w")) == NULL) {
		(void)fprintf(stderr, "config: cannot write %s: %s\n",
		    fname, strerror(errno));
		return (1);
	}
	for (nv = head; nv != NULL; nv = nv->nv_next)
		if (fprintf(fp, "#define\t%s\t%d\n",
		    cntname(nv->nv_name), nv->nv_int) < 0)
			return (err("writ", fname, fp));
	if (fclose(fp))
		return (err("writ", fname, NULL));
	return (0);
}

static int
err(what, fname, fp)
	const char *what;
	char *fname;
	FILE *fp;
{

	(void)fprintf(stderr, "config: error %sing %s: %s\n",
	    what, fname, strerror(errno));
	if (fp)
		(void)fclose(fp);
	free(fname);
	return (1);
}

static char *
cntname(src)
	register const char *src;
{
	register char *dst, c;
	static char buf[100];

	dst = buf;
	*dst++ = 'N';
	while ((c = *src++) != 0)
		*dst++ = islower(c) ? toupper(c) : c;
	*dst = 0;
	return (buf);
}
E 1
