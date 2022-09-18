h29133
s 00002/00002/00234
d D 8.1 93/06/06 13:54:34 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00236
d D 5.2 93/04/18 04:23:08 torek 2 1
c rm rcs headers (commit to maintenance on vangogh)
e
s 00238/00000/00000
d D 5.1 93/01/12 02:18:38 torek 1 0
c date and time created 93/01/12 02:18:38 by torek
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
 * from: $Header: files.c,v 1.4 93/01/12 03:56:19 torek Exp $
E 2
 */

#include <sys/param.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

extern const char *yyfile;

/*
 * We check that each full path name is unique.  File base names
 * should generally also be unique, e.g., having both a net/xx.c and
 * a kern/xx.c (or, worse, a net/xx.c and a new/xx.c++) is probably
 * wrong, but is permitted under some conditions.
 */
static struct hashtab *basetab;		/* file base names */
static struct hashtab *pathtab;		/* full path names */

static struct files **nextfile;
static struct files **unchecked;

void
initfiles()
{

	basetab = ht_new();
	pathtab = ht_new();
	nextfile = &allfiles;
	unchecked = &allfiles;
}

static void
showprev(pref, fi)
	const char *pref;
	register struct files *fi;
{

	xerror(fi->fi_srcfile, fi->fi_srcline,
	    "%sfile %s ...", pref, fi->fi_path);
	errors--;
}

void
addfile(path, opts, flags, rule)
	const char *path;
	struct nvlist *opts;
	int flags;
	const char *rule;
{
	struct files *fi;
	const char *base, *dotp, *tail;
	size_t baselen;
	int needc, needf;
	char buf[200];

	/* check various errors */
	needc = flags & FI_NEEDSCOUNT;
	needf = flags & FI_NEEDSFLAG;
	if (needc && needf) {
		error("cannot mix needs-count and needs-flag");
		goto bad;
	}
	if (opts == NULL && (needc || needf)) {
		error("nothing to %s for %s", needc ? "count" : "flag", path);
		goto bad;
	}
	if ((fi = ht_lookup(pathtab, path)) != NULL) {
		showprev("", fi);
		error("file %s listed again", path);
		goto bad;
	}

	/* find last part of pathname, and same without trailing suffix */
	tail = rindex(path, '/');
	if (tail == NULL)
		tail = path;
	else
		tail++;
	dotp = rindex(tail, '.');
	if (dotp == NULL || dotp[1] == 0 ||
	    (baselen = dotp - tail) >= sizeof(buf)) {
		error("invalid pathname `%s'", path);
		goto bad;
	}

	/*
	 * Make a copy of the path without the .c/.s/whatever suffix.
	 * This must be unique per "files" file (e.g., a specific
	 * file can override a standard file, but no standard file
	 * can override another standard file).  This is not perfect
	 * but should catch any major errors.
	 */
	bcopy(tail, buf, baselen);
	buf[baselen] = 0;
	base = intern(buf);
	if ((fi = ht_lookup(basetab, base)) != NULL) {
		if (fi->fi_srcfile != yyfile) {
			showprev("note: ", fi);
			error("is overriden by %s", path);
			errors--;	/* take it away */
			fi->fi_flags |= FI_HIDDEN;
		} else {
			showprev("", fi);
			error("collides with %s (both make %s.o)",
			    path, base);
			goto bad;
		}
	}

	/*
	 * Commit this file to memory.
	 */
	fi = emalloc(sizeof *fi);
	fi->fi_next = NULL;
	fi->fi_srcfile = yyfile;
	fi->fi_srcline = currentline();
	fi->fi_flags = flags;
	fi->fi_lastc = dotp[strlen(dotp) - 1];
	fi->fi_path = path;
	fi->fi_tail = tail;
	fi->fi_base = base;
	fi->fi_opt = opts;
	fi->fi_mkrule = rule;
	if (ht_insert(pathtab, path, fi))
		panic("addfile: ht_insert(%s)", path);
	(void)ht_replace(basetab, base, fi);
	*nextfile = fi;
	nextfile = &fi->fi_next;
	return;
bad:
	nvfreel(opts);
}

/*
 * We have finished reading some "files" file, either ../../conf/files
 * or ./files.$machine.  Make sure that everything that is flagged as
 * needing a count is reasonable.  (This prevents ../../conf/files from
 * depending on some machine-specific device.)
 */
void
checkfiles()
{
	register struct files *fi, *last;
	register struct nvlist *nv;

	last = NULL;
	for (fi = *unchecked; fi != NULL; last = fi, fi = fi->fi_next) {
		if ((fi->fi_flags & FI_NEEDSCOUNT) == 0)
			continue;
		for (nv = fi->fi_opt; nv != NULL; nv = nv->nv_next)
			if (ht_lookup(devbasetab, nv->nv_name) == NULL) {
				xerror(fi->fi_srcfile, fi->fi_srcline,
				    "`%s' is not a countable device",
				    nv->nv_name);
				/* keep fixfiles() from complaining again */
				fi->fi_flags |= FI_HIDDEN;
			}
	}
	if (last != NULL)
		unchecked = &last->fi_next;
}

/*
 * We have finished reading everything.  Tack the files down: calculate
 * selection and counts as needed.
 */
int
fixfiles()
{
	register struct files *fi;
	register struct nvlist *nv;
	register struct devbase *dev;
	int sel, err;

	err = 0;
	for (fi = allfiles; fi != NULL; fi = fi->fi_next) {
		if (fi->fi_flags & FI_HIDDEN)
			continue;
		if ((nv = fi->fi_opt) == NULL) {	/* standard */
			fi->fi_flags |= FI_SEL;
			continue;
		}
		/* figure out whether it is selected */
		sel = 0;
		if (fi->fi_flags & FI_NEEDSCOUNT) {
			/* ... and compute counts too */
			do {
				dev = ht_lookup(devbasetab, nv->nv_name);
				if (dev == NULL) {
					xerror(fi->fi_srcfile, fi->fi_srcline,
					    "`%s' is not a countable device",
					    nv->nv_name);
					err = 1;
				} else {
					if (dev->d_umax)
						sel = 1;
					nv->nv_int = dev->d_umax;
					(void)ht_insert(needcnttab,
					    nv->nv_name, nv);
				}
			} while ((nv = nv->nv_next) != NULL);
		} else {
			do {
				if (ht_lookup(selecttab, nv->nv_name)) {
					sel = 1;
					break;
				}
			} while ((nv = nv->nv_next) != NULL);
			if (fi->fi_flags & FI_NEEDSFLAG)
				for (nv = fi->fi_opt; nv; nv = nv->nv_next)
					nv->nv_int = sel;
		}
		/* if selected, we are go */
		if (sel)
			fi->fi_flags |= FI_SEL;
	}
	return (err);
}
E 1
