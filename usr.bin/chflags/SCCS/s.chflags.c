h63543
s 00002/00004/00152
d D 8.5 94/04/01 09:50:09 bostic 9 8
c setting errno and then not exiting isn't safe
e
s 00000/00002/00156
d D 8.4 94/03/31 17:26:51 bostic 8 7
c doing a chflags on a directory causing a cycle is probably the
c right thing to do
e
s 00002/00000/00156
d D 8.3 94/03/31 17:05:11 bostic 7 6
c check for fts_Read error
e
s 00080/00047/00076
d D 8.2 94/03/31 16:58:08 bostic 6 5
c POSIX 1003.2B/D9 symbolic links
e
s 00005/00005/00118
d D 8.1 93/06/06 14:26:45 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00110/00091
d D 5.4 93/03/03 20:35:34 bostic 4 3
c use err routines from C library
c add sappend, schange, uappend, uchange flags, use routine from ls(1) source
e
s 00041/00035/00160
d D 5.3 92/06/01 12:16:16 elan 3 2
c Added -Hh flags.
e
s 00085/00053/00110
d D 5.2 92/03/10 22:16:27 bostic 2 1
c make fts(3) work again, welcome to the wonderful world of ANSI!
e
s 00163/00000/00000
d D 5.1 91/12/12 16:56:57 mckusick 1 0
c date and time created 91/12/12 16:56:57 by mckusick
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1989 The Regents of the University of California.
E 2
I 2
D 5
 * Copyright (c) 1992 The Regents of the University of California.
E 2
 * All rights reserved.
E 5
I 5
D 6
 * Copyright (c) 1992, 1993
E 6
I 6
 * Copyright (c) 1992, 1993, 1994
E 6
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 5
char copyright[] =
D 2
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 2
I 2
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
E 2
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
D 6
"%Z% Copyright (c) 1992, 1993\n\
E 6
I 6
"%Z% Copyright (c) 1992, 1993, 1994\n\
E 6
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
I 2
D 4
#include <errno.h>
E 4
I 4

#include <err.h>
I 6
#include <errno.h>
E 6
E 4
E 2
#include <fts.h>
I 2
D 4
#include <unistd.h>
E 4
E 2
#include <stdio.h>
I 2
#include <stdlib.h>
E 2
#include <string.h>
I 4
#include <unistd.h>
E 4

D 2
extern int errno;
E 2
I 2
D 4
typedef struct cmdset {
	long clrbits;
	long setbits;
} CMDS;
CMDS cmds;
E 2
int retval;
E 4
I 4
u_long	string_to_flags __P((char **, u_long *, u_long *));
void	usage __P((void));
E 4

I 2
D 4
void	 err __P((const char *, ...));
void	 error __P((char *));
int	 getflags __P((CMDS *, int));
void	*setflags __P((char *));
void	 usage __P((void));

E 4
int
E 2
main(argc, argv)
	int argc;
D 2
	char **argv;
E 2
I 2
	char *argv[];
E 2
{
D 2
	extern int optind;
E 2
D 3
	register FTS *fts;
E 3
I 3
D 6
	register FTS *ftsp;
E 3
	register FTSENT *p;
D 2
	register int oct, oflags;
E 2
I 2
D 4
	register long oflags;
E 4
	register int oct;
E 6
I 6
	FTS *ftsp;
	FTSENT *p;
E 6
E 2
D 4
	register char *flags;
D 2
	void *set, *setflags();
E 2
	struct stat sb;
D 2
	int ch, fflag, rflag;
E 2
I 2
	void *set;
D 3
	int ch, rflag;
E 3
I 3
	int ch, rflag, hflag, Hflag;
E 3
	char *ep;
I 3
	int fts_options;
E 4
I 4
	u_long clear, set;
D 6
	int ch, fts_options, retval, rflag, hflag, Hflag;
E 6
I 6
	long val;
	int Hflag, Lflag, Pflag, Rflag, ch, fts_options, oct, rval;
E 6
	char *flags, *ep;
E 4
E 3
E 2

D 2
	fflag = rflag = 0;
	while ((ch = getopt(argc, argv, "Rf")) != EOF)
E 2
I 2
D 3
	rflag = 0;
	while ((ch = getopt(argc, argv, "R")) != EOF)
E 3
I 3
D 6
	rflag = hflag = Hflag = 0;
	fts_options = FTS_PHYSICAL;
	while ((ch = getopt(argc, argv, "HRh")) != EOF)
E 3
E 2
		switch((char)ch) {
E 6
I 6
	Hflag = Lflag = Pflag = Rflag = 0;
	while ((ch = getopt(argc, argv, "HLPR")) != EOF)
		switch (ch) {
E 6
I 3
		case 'H':
			Hflag = 1;
D 6
			fts_options |= FTS_COMFOLLOW;
E 6
I 6
			Lflag = Pflag = 0;
E 6
			break;
E 3
D 6
		case 'R':
			rflag = 1;
E 6
I 6
		case 'L':
			Lflag = 1;
			Hflag = Pflag = 0;
E 6
			break;
D 2
		case 'f':		/* no longer documented */
			fflag = 1;
			break;
E 2
D 3
		case '?':
E 3
I 3
D 6
		case 'h':
			hflag = 1;
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
E 6
I 6
		case 'P':
			Pflag = 1;
			Hflag = Lflag = 0;
E 6
			break;
D 6
      		case '?':
E 6
I 6
		case 'R':
			Rflag = 1;
			break;
		case '?':
E 6
E 3
		default:
			usage();
		}
	argv += optind;
	argc -= optind;

	if (argc < 2)
		usage();

I 6
	fts_options = FTS_PHYSICAL;
	if (Rflag) {
		if (Hflag)
			fts_options |= FTS_COMFOLLOW;
		if (Lflag) {
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
		}
	}

E 6
	flags = *argv;
	if (*flags >= '0' && *flags <= '7') {
D 2
		oflags = (int)strtol(flags, (char **)NULL, 8);
		oct = 1;
E 2
I 2
D 4
		oflags = (int)strtol(flags, &ep, 8);
                if (oflags < 0 || *ep)
                        err("invalid flags: %s", flags);
E 4
I 4
D 6
		set = (int)strtol(flags, &ep, 8);
                if (set < 0 || *ep)
E 6
I 6
		errno = 0;
		val = strtol(flags, &ep, 8);
		if (val < 0)
			errno = ERANGE;
		if (errno)
                        err(1, "invalid flags: %s", flags);
                if (*ep)
E 6
                        errx(1, "invalid flags: %s", flags);
D 6
		fts_options |= FTS_NOSTAT;
E 6
I 6
		set = val;
E 6
E 4
                oct = 1;
E 2
	} else {
D 2
		if (!(set = setflags(flags))) {
			(void)fprintf(stderr, "chflags: invalid flags.\n");
			exit(1);
		}
E 2
I 2
D 4
		if ((set = setflags(flags)) == NULL)
                        err("invalid flags: %s", flags);
E 4
I 4
		if (string_to_flags(&flags, &set, &clear))
                        errx(1, "invalid flag: %s", flags);
		clear = ~clear;
E 4
E 2
		oct = 0;
	}

D 4
	retval = 0;
D 3
	if (rflag) {
		if (!(fts = fts_open(++argv,
D 2
		    oct ? FTS_NOSTAT|FTS_PHYSICAL : FTS_PHYSICAL, 0))) {
			(void)fprintf(stderr, "chflags: %s.\n",
			    strerror(errno));
			exit(1);
		}
E 2
I 2
		    oct ? FTS_NOSTAT|FTS_PHYSICAL : FTS_PHYSICAL, 0)))
			err("%s", strerror(errno));
E 2
		while (p = fts_read(fts))
			switch(p->fts_info) {
			case FTS_D:
				break;
			case FTS_DNR:
			case FTS_ERR:
			case FTS_NS:
D 2
				(void)fprintf(stderr, "chflags: %s: %s.\n",
				    p->fts_path, strerror(errno));
				exit(1);
E 2
I 2
				err("%s: %s", p->fts_path, strerror(errno));
E 2
			default:
				if (chflags(p->fts_accpath, oct ? oflags :
D 2
				    getflags(set, p->fts_statb.st_flags)) &&
				    !fflag)
E 2
I 2
				    getflags(set, p->fts_statp->st_flags)))
E 2
					error(p->fts_path);
				break;
			}
		exit(retval);
	}
	if (oct) {
		while (*++argv)
D 2
			if (chflags(*argv, oflags) && !fflag)
E 2
I 2
			if (chflags(*argv, oflags))
E 2
				error(*argv);
	} else
		while (*++argv)
D 2
			if ((lstat(*argv, &sb) ||
			    chflags(*argv, getflags(set, sb.st_flags))) &&
			    !fflag)
E 2
I 2
			if (lstat(*argv, &sb) ||
			    chflags(*argv, getflags(set, sb.st_flags)))
E 2
				error(*argv);
E 3
I 3
	if (oct)
		fts_options |= FTS_NOSTAT;
	if (!(ftsp = fts_open(++argv, fts_options , 0)))
		err("%s", strerror(errno));
	while (p = fts_read(ftsp))
E 4
I 4
	if ((ftsp = fts_open(++argv, fts_options , 0)) == NULL)
D 6
		err(1, "");
E 6
I 6
		err(1, NULL); 
E 6

D 6
	for (retval = 0; p = fts_read(ftsp);)
E 4
		switch(p->fts_info) {
E 6
I 6
	for (rval = 0; (p = fts_read(ftsp)) != NULL;) {
		switch (p->fts_info) {
E 6
		case FTS_D:
D 6
			if (!rflag)
				fts_set(ftsp, p, FTS_SKIP);
E 6
I 6
			if (Rflag)		/* Change it at FTS_DP. */
				continue;
			fts_set(ftsp, p, FTS_SKIP);
E 6
			break;
D 6
		case FTS_DNR:
		case FTS_ERR:
E 6
I 6
D 8
		case FTS_DC:			/* Ignore. */
			continue;
E 8
		case FTS_DNR:			/* Warn, chflag, continue. */
D 9
			errno = p->fts_errno;
			warn("%s", p->fts_path);
E 9
I 9
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
E 9
			rval = 1;
			break;
		case FTS_ERR:			/* Warn, continue. */
E 6
		case FTS_NS:
D 4
			err("%s: %s", p->fts_path, strerror(errno));
E 4
I 4
D 6
			err(1, "%s", p->fts_path);
E 4
		default:
                        if (p->fts_info == FTS_SL &&
                            !(hflag ||
                            (Hflag && p->fts_level == FTS_ROOTLEVEL)))
				continue;
D 4
			if (chflags(p->fts_accpath, oct ? oflags :
			    getflags(set, p->fts_statp->st_flags)))
				error(p->fts_path);
E 4
I 4
			if (oct) {
				if (!chflags(p->fts_accpath, set))
					break;
			} else {
				p->fts_statp->st_flags |= set;
				p->fts_statp->st_flags &= clear;
				if (!chflags(p->fts_accpath,
				    p->fts_statp->st_flags))
					break;
			}
E 6
I 6
D 9
			errno = p->fts_errno;
E 6
			warn("%s", p->fts_path);
E 9
I 9
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
E 9
D 6
			retval = 1;
E 6
I 6
			rval = 1;
			continue;
		case FTS_SL:			/* Ignore. */
		case FTS_SLNONE:
			/*
			 * The only symlinks that end up here are ones that
			 * don't point to anything and ones that we found
			 * doing a physical walk.
			 */
			continue;
		default:
E 6
E 4
			break;
		}
E 3
D 6
	exit(retval);
E 6
I 6
		if (oct) {
			if (!chflags(p->fts_accpath, set))
				continue;
		} else {
			p->fts_statp->st_flags |= set;
			p->fts_statp->st_flags &= clear;
			if (!chflags(p->fts_accpath, p->fts_statp->st_flags))
				continue;
		}
		warn("%s", p->fts_path);
		rval = 1;
	}
I 7
	if (errno)
		err(1, "fts_read");
E 7
	exit(rval);
E 6
D 4
}

D 2
error(name)
	char *name;
{
	(void)fprintf(stderr, "chflags: %s: %s.\n", name, strerror(errno));
	retval = 1;
}

usage()
{
	(void)fprintf(stderr, "Usage: chflags [-R] flags file ...\n");
	exit(1);
}

E 2
/*
 * These are analogous to the setmode/getmode routines in the C library.
 */
D 2
struct cmdset {
	long	clrbits;
	long	setbits;
} cmds;

E 2
void *
setflags(cp)
	char *cp;
{
D 2
	register struct cmdset *fset;
E 2
I 2
	register CMDS *fset;
E 2
	register char *arg;

	fset = &cmds;
	fset->clrbits = 0;
	fset->setbits = 0;
	while (cp) {
		while ((arg = strsep(&cp, ",")) != NULL && *arg == '\0')
			/* void */;
		if (!strcasecmp(arg, "dump"))
			fset->clrbits |= NODUMP;
		else if (!strcasecmp(arg, "nodump"))
			fset->setbits |= NODUMP;
		else
			return (NULL);
	}
	return (fset);
}

I 2
int
E 2
getflags(fset, oflags)
D 2
	register struct cmdset *fset;
E 2
I 2
	register CMDS *fset;
E 2
	register int oflags;
{

	oflags &= ~fset->clrbits;
	oflags |= fset->setbits;
	return (oflags);
I 2
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
	(void)fprintf(stderr, "chflags: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
}

void
error(name)
	char *name;
{
	(void)fprintf(stderr, "chflags: %s: %s.\n", name, strerror(errno));
	retval = 1;
E 4
}

void
usage()
{
D 3
	(void)fprintf(stderr, "usage: chflags [-R] flags file ...\n");
E 3
I 3
D 6
	(void)fprintf(stderr, "usage: chflags [-HRh] flags file ...\n");
E 6
I 6
	(void)fprintf(stderr,
	    "usage: chflags [-R [-H | -L | -P]] flags file ...\n");
E 6
E 3
	exit(1);
E 2
}
E 1
