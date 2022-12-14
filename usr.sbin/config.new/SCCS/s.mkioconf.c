h51482
s 00002/00002/00367
d D 8.1 93/06/06 13:54:50 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00368
d D 5.5 93/05/10 21:31:16 torek 5 4
c terminate cfdata array with a fully bracketed initializer,
c just to shut up that !@*&# warning from gcc 2.3.3
e
s 00002/00002/00367
d D 5.4 93/04/18 05:08:16 torek 4 3
c turn on pseudo-device table
e
s 00000/00002/00369
d D 5.3 93/04/18 04:23:13 torek 3 2
c rm rcs headers (commit to maintenance on vangogh)
e
s 00001/00001/00370
d D 5.2 93/01/15 00:06:29 torek 2 1
c emit correct syntax
e
s 00371/00000/00000
d D 5.1 93/01/12 02:18:41 torek 1 0
c date and time created 93/01/12 02:18:41 by torek
e
u
U
t
T
I 1
/* 
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
D 3
 *
 * from: $Header: mkioconf.c,v 1.2 92/12/08 19:34:31 torek Exp $
E 3
 */

#include <sys/param.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

/*
 * Make ioconf.c.
 */
static int cforder __P((const void *, const void *));
static int emitcfdata __P((FILE *));
static int emitexterns __P((FILE *));
static int emithdr __P((FILE *));
static int emitloc __P((FILE *));
static int emitpseudo __P((FILE *));
static int emitpv __P((FILE *));
static int emitroots __P((FILE *));
static int emitvec __P((FILE *));
static char *vecname __P((char *, const char *, int));

static const char *s_i386;

#define	SEP(pos, max)	(((u_int)(pos) % (max)) == 0 ? "\n\t" : " ")

/*
 * NEWLINE can only be used in the emitXXX functions.
 * In most cases it can be subsumed into an fprintf.
 */
#define	NEWLINE		if (putc('\n', fp) < 0) return (1)

int
mkioconf()
{
	register FILE *fp;
	register char *fname;
	int v;

	s_i386 = intern("i386");

	fname = path("ioconf.c");
	qsort(packed, npacked, sizeof *packed, cforder);
	if ((fp = fopen(fname, "w")) == NULL) {
		(void)fprintf(stderr, "config: cannot write %s: %s\n",
		    fname, strerror(errno));
		return (1);
	}
	v = emithdr(fp);
	if (v != 0 || emitvec(fp) || emitexterns(fp) || emitloc(fp) ||
	    emitpv(fp) || emitcfdata(fp) || emitroots(fp) || emitpseudo(fp)) {
		if (v >= 0)
			(void)fprintf(stderr,
			    "config: error writing %s: %s\n",
			    fname, strerror(errno));
		(void)fclose(fp);
		/* (void)unlink(fname); */
		free(fname);
		return (1);
	}
	(void)fclose(fp);
	free(fname);
	return (0);
}

static int
cforder(a, b)
	const void *a, *b;
{
	register int n1, n2;

	n1 = (*(struct devi **)a)->i_cfindex;
	n2 = (*(struct devi **)b)->i_cfindex;
	return (n1 - n2);
}

static int
emithdr(ofp)
	register FILE *ofp;
{
	register FILE *ifp;
	register int n;
	char ifn[200], buf[BUFSIZ];

	if (fprintf(ofp, "\
/*\n\
 * MACHINE GENERATED: DO NOT EDIT\n\
 *\n\
 * ioconf.c, from \"%s\"\n\
 */\n\n", conffile) < 0)
		return (1);
	(void)sprintf(ifn, "ioconf.incl.%s", machine);
	if ((ifp = fopen(ifn, "r")) != NULL) {
		while ((n = fread(buf, 1, sizeof(buf), ifp)) > 0)
			if (fwrite(buf, 1, n, ofp) != n)
				return (1);
		if (ferror(ifp)) {
			(void)fprintf(stderr, "config: error reading %s: %s\n",
			    ifn, strerror(errno));
			(void)fclose(ifp);
			return (-1);
		}
		(void)fclose(ifp);
	} else {
		if (fputs("\
#include <sys/param.h>\n\
#include <sys/device.h>\n", ofp) < 0)
			return (1);
	}
	return (0);
}

static int
emitexterns(fp)
	register FILE *fp;
{
	register struct devbase *d;

	NEWLINE;
	for (d = allbases; d != NULL; d = d->d_next) {
		if (d->d_ihead == NULL)
			continue;
		if (fprintf(fp, "extern struct cfdriver %scd;\n",
			    d->d_name) < 0)
			return (1);
	}
	NEWLINE;
	return (0);
}

static int
emitloc(fp)
	register FILE *fp;
{
	register int i;

	if (fprintf(fp, "\n/* locators */\n\
static int loc[%d] = {", locators.used) < 0)
		return (1);
	for (i = 0; i < locators.used; i++)
		if (fprintf(fp, "%s%s,", SEP(i, 8), locators.vec[i]) < 0)
			return (1);
	return (fprintf(fp, "\n};\n") < 0);
}

/*
 * Emit global parents-vector.
 */
static int
emitpv(fp)
	register FILE *fp;
{
	register int i;

	if (fprintf(fp, "\n/* parent vectors */\n\
static short pv[%d] = {", parents.used) < 0)
		return (1);
	for (i = 0; i < parents.used; i++)
		if (fprintf(fp, "%s%d,", SEP(i, 16), parents.vec[i]) < 0)
			return (1);
	return (fprintf(fp, "\n};\n") < 0);
}

/*
 * Emit the cfdata array.
 */
static int
emitcfdata(fp)
	register FILE *fp;
{
	register struct devi **p, *i, **par;
	register int unit, v;
	register const char *vs, *state, *basename;
	register struct nvlist *nv;
	register struct attr *a;
	char *loc;
	char locbuf[20];

	if (fprintf(fp, "\n\
#define NORM FSTATE_NOTFOUND\n\
#define STAR FSTATE_STAR\n\
\n\
struct cfdata cfdata[] = {\n\
\t/* driver     unit state    loc     flags parents ivstubs */\n") < 0)
		return (1);
	for (p = packed; (i = *p) != NULL; p++) {
		/* the description */
		if (fprintf(fp, "/*%3d: %s at ", i->i_cfindex, i->i_name) < 0)
			return (1);
		par = i->i_parents;
		for (v = 0; v < i->i_pvlen; v++)
			if (fprintf(fp, "%s%s", v == 0 ? "" : "|",
			    i->i_parents[v]->i_name) < 0)
				return (1);
		if (v == 0 && fputs("root", fp) < 0)
			return (1);
		a = i->i_atattr;
		nv = a->a_locs;
		for (nv = a->a_locs, v = 0; nv != NULL; nv = nv->nv_next, v++)
			if (fprintf(fp, " %s %s",
			    nv->nv_name, i->i_locs[v]) < 0)
				return (1);
		if (fputs(" */\n", fp) < 0)
			return (-1);

		/* then the actual defining line */
		basename = i->i_base->d_name;
		if (i->i_unit == STAR) {
			unit = i->i_base->d_umax;
			state = "STAR";
		} else {
			unit = i->i_unit;
			state = "NORM";
		}
		if (i->i_ivoff < 0) {
			vs = "";
			v = 0;
		} else {
			vs = "vec+";
			v = i->i_ivoff;
		}
		if (i->i_locoff >= 0) {
			(void)sprintf(locbuf, "loc+%3d", i->i_locoff);
			loc = locbuf;
		} else
			loc = "loc";
		if (fprintf(fp, "\
\t{&%scd,%s%2d, %s, %7s, %#6x, pv+%2d, %s%d},\n",
		    basename, strlen(basename) < 3 ? "\t\t" : "\t", unit,
		    state, loc, i->i_cfflags, i->i_pvoff, vs, v) < 0)
			return (1);
	}
D 5
	return (fputs("\t0\n};\n", fp) < 0);
E 5
I 5
	return (fputs("\t{0}\n};\n", fp) < 0);
E 5
}

/*
 * Emit the table of potential roots.
 */
static int
emitroots(fp)
	register FILE *fp;
{
	register struct devi **p, *i;

	if (fputs("\nshort cfroots[] = {\n", fp) < 0)
		return (1);
	for (p = packed; (i = *p) != NULL; p++) {
		if (i->i_at != NULL)
			continue;
		if (i->i_unit != 0 &&
		    (i->i_unit != STAR || i->i_base->d_umax != 0))
			(void)fprintf(stderr,
			    "config: warning: `%s at root' is not unit 0\n",
			    i->i_name);
		if (fprintf(fp, "\t%2d /* %s */,\n",
		    i->i_cfindex, i->i_name) < 0)
			return (1);
	}
	return (fputs("\t-1\n};\n", fp) < 0);
}

/*
 * Emit pseudo-device initialization.
 */
static int
emitpseudo(fp)
	register FILE *fp;
{
	register struct devi *i;
	register struct devbase *d;

D 4
	if (fputs("\n#ifdef notyet\n", fp) < 0)
E 4
I 4
	if (fputs("\n/* pseudo-devices */\n", fp) < 0)
E 4
		return (1);
	for (i = allpseudo; i != NULL; i = i->i_next)
		if (fprintf(fp, "extern void %sattach __P((int));\n",
		    i->i_base->d_name) < 0)
			return (1);
	if (fputs("\nstruct pdevinit pdevinit[] = {\n", fp) < 0)
		return (1);
	for (i = allpseudo; i != NULL; i = i->i_next) {
		d = i->i_base;
D 2
		if (fprintf(fp, "\t{ %sattach, %d }\n",
E 2
I 2
		if (fprintf(fp, "\t{ %sattach, %d },\n",
E 2
		    d->d_name, d->d_umax) < 0)
			return (1);
	}
D 4
	return (fputs("\t{ 0, 0 }\n};\n#endif\n", fp) < 0);
E 4
I 4
	return (fputs("\t{ 0, 0 }\n};\n", fp) < 0);
E 4
}

/*
 * Emit interrupt vector declarations, and calculate offsets.
 */
static int
emitvec(fp)
	register FILE *fp;
{
	register struct nvlist *head, *nv;
	register struct devi **p, *i;
	register int j, nvec, unit;
	char buf[200];

	nvec = 0;
	for (p = packed; (i = *p) != NULL; p++) {
		if ((head = i->i_base->d_vectors) == NULL)
			continue;
		if ((unit = i->i_unit) == STAR)
			panic("emitvec unit==STAR");
		if (nvec == 0)
			NEWLINE;
		for (j = 0, nv = head; nv != NULL; j++, nv = nv->nv_next)
			if (fprintf(fp,
			    "/* IVEC %s %d */ extern void %s();\n",
			    nv->nv_name, unit,
			    vecname(buf, nv->nv_name, unit)) < 0)
				return (1);
		nvec += j + 1;
	}
	if (nvec == 0)
		return (0);
	if (fprintf(fp, "\nstatic void (*vec[%d]) __P((void)) = {", nvec) < 0)
		return (1);
	nvec = 0;
	for (p = packed; (i = *p) != NULL; p++) {
		if ((head = i->i_base->d_vectors) == NULL)
			continue;
		i->i_ivoff = nvec;
		unit = i->i_unit;
		for (nv = head; nv != NULL; nv = nv->nv_next)
			if (fprintf(fp, "%s%s,",
			    SEP(nvec++, 4),
			    vecname(buf, nv->nv_name, unit)) < 0)
				return (1);
		if (fprintf(fp, "%s0,", SEP(nvec++, 4)) < 0)
			return (1);
	}
	return (fputs("\n};\n", fp) < 0);
}

static char *
vecname(buf, name, unit)
	char *buf;
	const char *name;
	int unit;
{

	/* @#%* 386 uses a different name format */
	if (machine == s_i386) {
		(void)sprintf(buf, "V%s%d", name, unit);
		return (buf);
	}
	(void)sprintf(buf, "X%s%d", name, unit);
	return (buf);
}
E 1
