h40131
s 00002/00002/00090
d D 8.1 93/06/06 14:36:46 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00091
d D 4.11 93/04/05 21:47:53 ralph 11 10
c use Start instead of start. Conflicts with start in crt0.o (mips).
e
s 00008/00001/00084
d D 4.10 91/04/17 17:19:27 bostic 10 9
c new copyright; att/bsd/shared
e
s 00001/00001/00084
d D 4.9 91/03/02 15:32:08 bostic 9 8
c ANSI C -- string constants can't be written
e
s 00001/00001/00084
d D 4.8 91/03/01 13:49:02 bostic 8 7
c ANSI
e
s 00002/00001/00083
d D 4.7 85/08/16 21:12:29 van 7 6
c added -n flag from rcs diff
e
s 00005/00001/00079
d D 4.6 85/06/07 03:02:50 van 6 5
c added -w, -i & -t flags.  Changed -c output to group together
c adjacent changes.
e
s 00000/00006/00080
d D 4.5 85/06/03 23:13:34 lepreau 5 4
c speedup by pitching the "compacting" realloc, which loses with new malloc
e
s 00002/00002/00084
d D 4.4 83/07/01 03:59:20 sam 4 3
c include fix
e
s 00002/00002/00084
d D 4.3 82/05/07 19:00:29 mckusick 3 2
c update to new fs
e
s 00001/00001/00085
d D 4.2 82/05/05 17:33:43 sam 2 1
c use opendir, readdir, closedir
e
s 00086/00000/00000
d D 4.1 80/10/09 22:46:40 bill 1 0
c date and time created 80/10/09 22:46:40 by bill
e
u
U
t
T
I 1
D 4
/* %Z%%M% %I% %G%" */
E 4
I 4
D 10
/*	%M%	%I%	%E%	*/
E 10
I 10
/*-
D 12
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 10
E 4

/*
 * diff - common declarations
 */

#include <stdio.h>
#include <ctype.h>
D 3
#include <sys/types.h>
E 3
I 3
#include <sys/param.h>
E 3
#include <sys/stat.h>
I 4
#include <sys/dir.h>
E 4
#include <signal.h>
D 2
#include <sys/dir.h>
E 2
I 2
D 3
#include <ndir.h>
E 3
I 3
D 4
#include <dir.h>
E 4
E 3
E 2

/*
 * Output format options
 */
int	opt;

#define	D_NORMAL	0	/* Normal output */
#define	D_EDIT		-1	/* Editor script out */
#define	D_REVERSE	1	/* Reverse editor script */
#define	D_CONTEXT	2	/* Diff with context */
#define	D_IFDEF		3	/* Diff with merged #ifdef's */
I 7
#define	D_NREVERSE	4	/* Reverse ed script with numbered
				   lines and no trailing . */
E 7

I 6
int	tflag;			/* expand tabs on output */

E 6
/*
 * Algorithm related options
 */
int	hflag;			/* -h, use halfhearted DIFFH */
D 6
int	bflag;			/* ignore blanks in comparisions */
E 6
I 6
int	bflag;			/* ignore blanks in comparisons */
int	wflag;			/* totally ignore blanks in comparisons */
int	iflag;			/* ignore case in comparisons */
E 6

/*
 * Options on hierarchical diffs.
 */
int	lflag;			/* long output format with header */
int	rflag;			/* recursively trace directories */
int	sflag;			/* announce files which are same */
D 11
char	*start;			/* do file only if name >= this */
E 11
I 11
char	*Start;			/* do file only if name >= this */
E 11

/*
 * Variables for -I D_IFDEF option.
 */
int	wantelses;		/* -E */
char	*ifdef1;		/* String for -1 */
char	*ifdef2;		/* String for -2 */
char	*endifname;		/* What we will print on next #endif */
int	inifdef;

/*
 * Variables for -c context option.
 */
int	context;		/* lines of context to be printed */

/*
 * State for exit status.
 */
int	status;
int	anychange;
D 9
char	*tempfile;		/* used when comparing against std input */
E 9
I 9
char	tempfile[];		/* used when comparing against std input */
E 9

/*
 * Variables for diffdir.
 */
char	**diffargv;		/* option list to pass to recursive diffs */

/*
 * Input file names.
 * With diffdir, file1 and file2 are allocated BUFSIZ space,
 * and padded with a '/', and then efile0 and efile1 point after
 * the '/'.
 */
char	*file1, *file2, *efile1, *efile2;
D 7
struct	stat stb1, stb2;
E 7
struct	stat stb1, stb2;

D 5
/*
 * This is allocated early, and used
 * to reset the free storage pointer to effect space compaction.
 */
char	*dummy;

E 5
char	*malloc(), *talloc(), *ralloc();
char	*savestr(), *splice(), *splicen();
char	*mktemp(), *copytemp(), *rindex();
D 8
int	done();
E 8
I 8
void	done();
E 8

extern	char diffh[], diff[], pr[];
E 1
