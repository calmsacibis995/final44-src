h24205
s 00081/00069/00279
d D 8.3 94/04/02 07:39:18 pendry 8 7
c prettyness police
e
s 00002/00001/00346
d D 8.2 94/01/13 12:10:27 bostic 7 6
c Mike Karels at BSDI's changes for osync, to make output padding work
c correctly (this is not POSIX.2, but POSIX.2 is wrong)
e
s 00002/00002/00345
d D 8.1 93/05/31 14:22:10 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00346
d D 5.5 91/07/29 14:11:33 bostic 5 4
c swab turns off special semantics of bs
e
s 00059/00108/00288
d D 5.4 91/07/29 13:30:43 bostic 4 3
c fix block/unblock, ascii/ebcdic, cbs relationships (extensive)
c check for read/write/seek overflow; move stats into separate structure
c treat odd-length swab errors like truncate errors
e
s 00009/00002/00387
d D 5.3 91/07/27 13:27:02 bostic 3 2
c add 'm' for megabytes; allow bs= and C_SWAB to have special bs semantics
e
s 00002/00001/00387
d D 5.2 91/07/27 10:55:14 bostic 2 1
c add Lance Visser to contrib list
e
s 00388/00000/00000
d D 5.1 91/07/26 15:41:56 bostic 1 0
c date and time created 91/07/26 15:41:56 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 8
 * Copyright (c) 1991, 1993
E 8
I 8
 * Copyright (c) 1991, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
D 2
 * Keith Muller of the University of California, San Diego.
E 2
I 2
 * Keith Muller of the University of California, San Diego and Lance
 * Visser of Convex Computer Corporation.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 8
#include <limits.h>
E 8
I 8

#include <err.h>
E 8
#include <errno.h>
I 8
#include <limits.h>
E 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 8

E 8
#include "dd.h"
#include "extern.h"

D 8
static u_long get_bsz __P((char *));
E 8
I 8
static int	c_arg __P((const void *, const void *));
static int	c_conv __P((const void *, const void *));
static void	f_bs __P((char *));
static void	f_cbs __P((char *));
static void	f_conv __P((char *));
static void	f_count __P((char *));
static void	f_files __P((char *));
static void	f_ibs __P((char *));
static void	f_if __P((char *));
static void	f_obs __P((char *));
static void	f_of __P((char *));
static void	f_seek __P((char *));
static void	f_skip __P((char *));
static u_long	get_bsz __P((char *));
E 8

D 8
static void f_bs __P((char *));
static void f_cbs __P((char *));
static void f_conv __P((char *));
static void f_count __P((char *));
static void f_files __P((char *));
static void f_ibs __P((char *));
static void f_if __P((char *));
static void f_obs __P((char *));
static void f_of __P((char *));
static void f_seek __P((char *));
static void f_skip __P((char *));

E 8
static struct arg {
	char *name;
	void (*f) __P((char *));
	u_int set, noset;
} args[] = {
D 7
	"bs",		f_bs,		C_BS,		C_BS|C_IBS|C_OBS,
E 7
I 7
D 8
	"bs",		f_bs,		C_BS,		C_BS|C_IBS|C_OBS|C_OSYNC,
E 7
D 4
	"cbs",		f_cbs,		C_CBS,		0,
E 4
I 4
	"cbs",		f_cbs,		C_CBS,		C_CBS,
E 4
	"conv",		f_conv,		0,		0,
	"count",	f_count,	C_COUNT,	C_COUNT,
	"files",	f_files,	C_FILES,	C_FILES,
	"ibs",		f_ibs,		C_IBS,		C_BS|C_IBS,
	"if",		f_if,		C_IF,		C_IF,
	"obs",		f_obs,		C_OBS,		C_BS|C_OBS,
	"of",		f_of,		C_OF,		C_OF,
	"seek",		f_seek,		C_SEEK,		C_SEEK,
	"skip",		f_skip,		C_SKIP,		C_SKIP,
E 8
I 8
	{ "bs",		f_bs,		C_BS,	 C_BS|C_IBS|C_OBS|C_OSYNC },
	{ "cbs",	f_cbs,		C_CBS,	 C_CBS },
	{ "conv",	f_conv,		0,	 0 },
	{ "count",	f_count,	C_COUNT, C_COUNT },
	{ "files",	f_files,	C_FILES, C_FILES },
	{ "ibs",	f_ibs,		C_IBS,	 C_BS|C_IBS },
	{ "if",		f_if,		C_IF,	 C_IF },
	{ "obs",	f_obs,		C_OBS,	 C_BS|C_OBS },
	{ "of",		f_of,		C_OF,	 C_OF },
	{ "seek",	f_seek,		C_SEEK,	 C_SEEK },
	{ "skip",	f_skip,		C_SKIP,	 C_SKIP },
E 8
};

static char *oper;

/*
D 4
 * args -- parse old JCL syntax of dd.
E 4
I 4
 * args -- parse JCL syntax of dd.
E 4
 */
void
jcl(argv)
D 8
	register char **argv;
E 8
I 8
	char **argv;
E 8
{
D 8
	register struct arg *ap;
	struct arg tmp;
E 8
I 8
	struct arg *ap, tmp;
E 8
	char *arg;
D 8
	static int c_arg __P((const void *, const void *));
E 8

	in.dbsz = out.dbsz = 512;
D 4
	cfunc = def;
E 4

	while (oper = *++argv) {
D 8
		if ((arg = index(oper, '=')) == NULL)
			err("unknown operand %s", oper);
E 8
I 8
		if ((arg = strchr(oper, '=')) == NULL)
			errx(1, "unknown operand %s", oper);
E 8
		*arg++ = '\0';
		if (!*arg)
D 8
			err("no value specified for %s", oper);
E 8
I 8
			errx(1, "no value specified for %s", oper);
E 8
		tmp.name = oper;
		if (!(ap = (struct arg *)bsearch(&tmp, args,
		    sizeof(args)/sizeof(struct arg), sizeof(struct arg),
		    c_arg)))
D 8
			err("unknown operand %s", tmp.name);
E 8
I 8
			errx(1, "unknown operand %s", tmp.name);
E 8
		if (ddflags & ap->noset)
D 8
			err("%s: illegal argument combination or already set",
E 8
I 8
			errx(1, "%s: illegal argument combination or already set",
E 8
			    tmp.name);
		ddflags |= ap->set;
		ap->f(arg);
	}

	/* Final sanity checks. */

	if (ddflags & C_BS) {
		/*
		 * Bs is turned off by any conversion -- we assume the user
		 * just wanted to set both the input and output block sizes
		 * and didn't want the bs semantics, so we don't warn.
		 */
D 3
		if (ddflags & (C_BLOCK|C_LCASE|C_SWAB|C_UCASE|C_UNBLOCK))
E 3
I 3
D 5
		if (ddflags & (C_BLOCK|C_LCASE|C_UCASE|C_UNBLOCK))
E 5
I 5
		if (ddflags & (C_BLOCK|C_LCASE|C_SWAB|C_UCASE|C_UNBLOCK))
E 5
E 3
			ddflags &= ~C_BS;

		/* Bs supersedes ibs and obs. */
		if (ddflags & C_BS && ddflags & (C_IBS|C_OBS))
D 8
			warn("bs supersedes ibs and obs");
E 8
I 8
			warnx("bs supersedes ibs and obs");
E 8
	}

D 4
	/* Cbs has to be set for block/unblock to be specified. */
E 4
I 4
	/*
	 * Ascii/ebcdic and cbs implies block/unblock.
	 * Block/unblock requires cbs and vice-versa.
	 */
E 4
	if (ddflags & (C_BLOCK|C_UNBLOCK)) {
I 4
		if (!(ddflags & C_CBS))
D 8
			err("record operations require cbs");
E 8
I 8
			errx(1, "record operations require cbs");
E 8
E 4
		if (cbsz == 0)
D 4
			err("block operations require cbs");
	} else 
		if (cbsz != 0)
			warn("cbs ignored if not doing block operation");
E 4
I 4
D 8
			err("cbs cannot be zero");
E 8
I 8
			errx(1, "cbs cannot be zero");
E 8
		cfunc = ddflags & C_BLOCK ? block : unblock;
	} else if (ddflags & C_CBS) {
		if (ddflags & (C_ASCII|C_EBCDIC)) {
			if (ddflags & C_ASCII) {
				ddflags |= C_UNBLOCK;
				cfunc = unblock;
			} else {
				ddflags |= C_BLOCK;
				cfunc = block;
			}
		} else
D 8
			err("cbs meaningless if not doing record operations");
E 8
I 8
			errx(1, "cbs meaningless if not doing record operations");
E 8
		if (cbsz == 0)
D 8
			err("cbs cannot be zero");
E 8
I 8
			errx(1, "cbs cannot be zero");
E 8
	} else
		cfunc = def;
E 4

	if (in.dbsz == 0 || out.dbsz == 0)
D 8
		err("buffer sizes cannot be zero");
E 8
I 8
		errx(1, "buffer sizes cannot be zero");
E 8

D 4

E 4
I 4
	/*
	 * Read, write and seek calls take ints as arguments.  Seek sizes
	 * could be larger if we wanted to do it in stages or check only
	 * regular files, but it's probably not worth it.
	 */
	if (in.dbsz > INT_MAX || out.dbsz > INT_MAX)
D 8
		err("buffer sizes cannot be greater than %d", INT_MAX);
E 8
I 8
		errx(1, "buffer sizes cannot be greater than %d", INT_MAX);
E 8
	if (in.offset > INT_MAX / in.dbsz || out.offset > INT_MAX / out.dbsz)
D 8
		err("seek offsets cannot be larger than %d", INT_MAX);
E 8
I 8
		errx(1, "seek offsets cannot be larger than %d", INT_MAX);
E 8
E 4
}

static int
c_arg(a, b)
	const void *a, *b;
{
I 8

E 8
	return (strcmp(((struct arg *)a)->name, ((struct arg *)b)->name));
}

static void
f_bs(arg)
	char *arg;
{
I 8

E 8
	in.dbsz = out.dbsz = (int)get_bsz(arg);
}

static void
f_cbs(arg)
	char *arg;
{
I 8

E 8
	cbsz = (int)get_bsz(arg);
}

static void
f_count(arg)
	char *arg;
{
I 8

E 8
	cpy_cnt = (u_int)get_bsz(arg);
D 4
	if (!cpy_cnt)				/* Well, that was quick. */
E 4
I 4
	if (!cpy_cnt)
E 4
		terminate(0);
}

static void
D 4
f_files(arg)					/* POSIX extension */
E 4
I 4
f_files(arg)
E 4
	char *arg;
{
I 8

E 8
	files_cnt = (int)get_bsz(arg);
}

static void
f_ibs(arg)
	char *arg;
{
I 8

E 8
	if (!(ddflags & C_BS))
		in.dbsz = (int)get_bsz(arg);
}

static void
f_if(arg)
	char *arg;
{
I 8

E 8
	in.name = arg;
}

static void
f_obs(arg)
	char *arg;
{
I 8

E 8
	if (!(ddflags & C_BS))
		out.dbsz = (int)get_bsz(arg);
}

static void
f_of(arg)
	char *arg;
{
I 8

E 8
	out.name = arg;
}

static void
f_seek(arg)
	char *arg;
{
I 8

E 8
	out.offset = (u_int)get_bsz(arg);
}

static void
f_skip(arg)
	char *arg;
{
I 8

E 8
	in.offset = (u_int)get_bsz(arg);
}

D 4
static void f_ascii __P((void));
static void f_block __P((void));
static void f_ebcdic __P((void));
static void f_ibm __P((void));
static void f_oldascii __P((void));
static void f_oldebcdic __P((void));
static void f_oldibm __P((void));
static void f_unblock __P((void));

E 4
static struct conv {
	char *name;
D 4
	void (*f) __P((void));
E 4
	u_int set, noset;
I 4
	u_char *ctab;
E 4
} clist[] = {
D 4
	"ascii",	f_ascii,	C_UNBLOCK,	C_BLOCK,
	"block",	f_block,	C_BLOCK,	C_UNBLOCK,
	"ebcdic",	f_ebcdic,	C_BLOCK,	C_UNBLOCK,
	"ibm",		f_ibm,		C_BLOCK,	C_UNBLOCK,
	"lcase",	NULL,		C_LCASE,	C_UCASE,
	"noerror",	NULL,		C_NOERROR,	0,
	"notrunc",	NULL,		C_NOTRUNC,	0,
	"oldascii",	f_oldascii,	C_UNBLOCK,	C_BLOCK,
	"oldebcdic",	f_oldebcdic,	C_BLOCK,	C_UNBLOCK,
	"oldibm",	f_oldibm,	C_BLOCK,	C_UNBLOCK,
	"swab",		NULL,		C_SWAB,		0,
	"sync",		NULL,		C_SYNC,		0,
	"ucase",	NULL,		C_UCASE,	C_LCASE,
	"unblock",	f_unblock,	C_UNBLOCK,	C_BLOCK,
E 4
I 4
D 8
	"ascii",	C_ASCII,	C_EBCDIC,	e2a_POSIX,
	"block",	C_BLOCK,	C_UNBLOCK,	NULL,
	"ebcdic",	C_EBCDIC,	C_ASCII,	a2e_POSIX,
	"ibm",		C_EBCDIC,	C_ASCII,	a2ibm_POSIX,
	"lcase",	C_LCASE,	C_UCASE,	NULL,
	"noerror",	C_NOERROR,	0,		NULL,
	"notrunc",	C_NOTRUNC,	0,		NULL,
	"oldascii",	C_ASCII,	C_EBCDIC,	e2a_32V,
	"oldebcdic",	C_EBCDIC,	C_ASCII,	a2e_32V,
	"oldibm",	C_EBCDIC,	C_ASCII,	a2ibm_32V,
I 7
	"osync",	C_OSYNC,	C_BS,		NULL,
E 7
	"swab",		C_SWAB,		0,		NULL,
	"sync",		C_SYNC,		0,		NULL,
	"ucase",	C_UCASE,	C_LCASE,	NULL,
	"unblock",	C_UNBLOCK,	C_BLOCK,	NULL,
E 8
I 8
	{ "ascii",	C_ASCII,	C_EBCDIC,	e2a_POSIX },
	{ "block",	C_BLOCK,	C_UNBLOCK,	NULL },
	{ "ebcdic",	C_EBCDIC,	C_ASCII,	a2e_POSIX },
	{ "ibm",	C_EBCDIC,	C_ASCII,	a2ibm_POSIX },
	{ "lcase",	C_LCASE,	C_UCASE,	NULL },
	{ "noerror",	C_NOERROR,	0,		NULL },
	{ "notrunc",	C_NOTRUNC,	0,		NULL },
	{ "oldascii",	C_ASCII,	C_EBCDIC,	e2a_32V },
	{ "oldebcdic",	C_EBCDIC,	C_ASCII,	a2e_32V },
	{ "oldibm",	C_EBCDIC,	C_ASCII,	a2ibm_32V },
	{ "osync",	C_OSYNC,	C_BS,		NULL },
	{ "swab",	C_SWAB,		0,		NULL },
	{ "sync",	C_SYNC,		0,		NULL },
	{ "ucase",	C_UCASE,	C_LCASE,	NULL },
	{ "unblock",	C_UNBLOCK,	C_BLOCK,	NULL },
E 8
E 4
};

static void
f_conv(arg)
	char *arg;
{
D 8
	register struct conv *cp;
	struct conv tmp;
	static int c_conv __P((const void *, const void *));
E 8
I 8
	struct conv *cp, tmp;
E 8

	while (arg != NULL) {
		tmp.name = strsep(&arg, ",");
		if (!(cp = (struct conv *)bsearch(&tmp, clist,
		    sizeof(clist)/sizeof(struct conv), sizeof(struct conv),
		    c_conv)))
D 8
			err("unknown conversion %s", tmp.name);
E 8
I 8
			errx(1, "unknown conversion %s", tmp.name);
E 8
		if (ddflags & cp->noset)
D 8
			err("%s: illegal conversion combination", tmp.name);
E 8
I 8
			errx(1, "%s: illegal conversion combination", tmp.name);
E 8
		ddflags |= cp->set;
D 4
		if (cp->f)
			(*cp->f)();
E 4
I 4
		if (cp->ctab)
			ctab = cp->ctab;
E 4
	}
}

static int
c_conv(a, b)
	const void *a, *b;
{
I 8

E 8
	return (strcmp(((struct conv *)a)->name, ((struct conv *)b)->name));
}

D 4
static void
f_ascii()					/* POSIX extension */
{
	extern u_char e2a_POSIX[];

	ctab = e2a_POSIX;
	cfunc = unblock;
}

static void
f_block()
{
	cfunc = block;
}

static void
f_ebcdic()					/* POSIX extension */
{
	extern u_char a2e_POSIX[];

	ctab = a2e_POSIX;
	cfunc = block;
}

static void
f_ibm()						/* POSIX extension */
{
	extern u_char a2ibm_POSIX[];

	ctab = a2ibm_POSIX;
	cfunc = block;
}

static void
f_oldascii()
{
	extern u_char e2a_32V[];

	ctab = e2a_32V;
	cfunc = unblock;
}

static void
f_oldebcdic()
{
	extern u_char a2e_32V[];
	ctab = a2e_32V;
	cfunc = block;
}

static void
f_oldibm()
{
	extern u_char a2ibm_32V[];

	ctab = a2ibm_32V;
	cfunc = block;
}

static void
f_unblock()
{
	cfunc = unblock;
}

E 4
/*
 * Convert an expression of the following forms to an unsigned long.
 * 	1) A positive decimal number.
D 4
 *	2) A positive decimal number followed by a k (mult by 1024).
 *	3) A positive decimal number followed by a b (mult by 512).
 *	4) A positive decimal number followed by a w (mult by sizeof int)
 *	   (POSIX extension for backwards compatibility).
 *	5) Two or more positive decimal numbers (with/without k,b or w).
E 4
I 4
 *	2) A positive decimal number followed by a b (mult by 512).
 *	3) A positive decimal number followed by a k (mult by 1024).
 *	4) A positive decimal number followed by a m (mult by 512).
 *	5) A positive decimal number followed by a w (mult by sizeof int)
 *	6) Two or more positive decimal numbers (with/without k,b or w).
E 4
 *	   seperated by x (also * for backwards compatibility), specifying
 *	   the product of the indicated values.
 */
static u_long
get_bsz(val)
	char *val;
{
D 8
	char *expr;
E 8
	u_long num, t;
I 8
	char *expr;
E 8

	num = strtoul(val, &expr, 0);
	if (num == ULONG_MAX)			/* Overflow. */
D 8
		err("%s: %s", oper, strerror(errno));
E 8
I 8
		err(1, "%s", oper);
E 8
	if (expr == val)			/* No digits. */
D 8
		err("%s: illegal numeric value", oper);
E 8
I 8
		errx(1, "%s: illegal numeric value", oper);
E 8

	switch(*expr) {
	case 'b':
		t = num;
		num *= 512;
		if (t > num)
			goto erange;
		++expr;
		break;
	case 'k':
		t = num;
		num *= 1024;
		if (t > num)
			goto erange;
		++expr;
		break;
I 3
	case 'm':
		t = num;
		num *= 1048576;
		if (t > num)
			goto erange;
		++expr;
		break;
E 3
D 4
	case 'w':				/* POSIX extension. */
E 4
I 4
	case 'w':
E 4
		t = num;
		num *= sizeof(int);
		if (t > num)
			goto erange;
		++expr;
		break;
	}

	switch(*expr) {
		case '\0':
			break;
I 3
		case '*':			/* Backward compatible. */
E 3
		case 'x':
D 3
		case '*':
E 3
			t = num;
			num *= get_bsz(expr + 1);
			if (t > num)
D 8
erange:				err("%s: %s", oper, strerror(ERANGE));
E 8
I 8
erange:				errx(1, "%s: %s", oper, strerror(ERANGE));
E 8
			break;
		default:
D 8
			err("%s: illegal numeric value", oper);
E 8
I 8
			errx(1, "%s: illegal numeric value", oper);
E 8
	}
D 8
	return(num);
E 8
I 8
	return (num);
E 8
}
E 1
