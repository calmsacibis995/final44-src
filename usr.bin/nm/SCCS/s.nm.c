h59406
s 00005/00005/00553
d D 8.1 93/06/06 15:48:13 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00042/00036/00516
d D 5.8 91/05/02 16:13:39 bostic 19 18
c fix was that the numeric comparison routine was completely wrong
c break name comparison routine up for speed, other, minor (mostly ANSI) fixes
e
s 00021/00017/00531
d D 5.7 91/02/22 13:03:25 bostic 18 17
c check for ranlib magic string was wrong, so if the ranlib archive
c happened to have an okay exec magic number, entered the twilight zone.
e
s 00001/00011/00547
d D 5.6 90/06/01 16:09:50 bostic 17 16
c new copyright notice
e
s 00053/00059/00504
d D 5.5 90/05/29 20:43:11 bostic 16 15
c One real bug: `nm -u' did not work (printed all sorts of symbols).
c Many fake-bugs: nm would be linty, if we had a working lint library,
c corresponding to the new ANSI headers (especially stdio).
c I threw in a few optimisations too....
c from Chris Torek
e
s 00001/00001/00562
d D 5.4 90/05/15 19:50:31 bostic 15 14
c string.h is ANSI C include file
e
s 00009/00008/00554
d D 5.3 90/03/05 11:17:07 bostic 14 13
c fix errno for ANSI C variable scoping
e
s 00004/00006/00558
d D 5.2 89/09/13 15:07:46 bostic 13 12
c change the format to the original one; don't enclose the archive element's
c names inside parentheses, no extra space after the element name to separate
c the value.  Leave the sorting difference, i.e. percolate unvalued elements
c to the top for the -n flag.  One other difference that should be noted --
c the old nm had inconsistent displays for libraries and object files when
c called with the -o flag.  The new one uses the same display format for both.
e
s 00483/00300/00081
d D 5.1 89/09/10 17:47:01 bostic 12 11
c new version from Hans Huebner
c hans@garp.mit.edu, huebner@db0tui6.BITNET
e
s 00261/00228/00120
d D 4.8 87/04/07 17:25:35 bostic 11 10
c bug report 4.2BSD/bin/31 (well, that's how it started...)
e
s 00005/00003/00343
d D 4.7 86/05/19 18:13:51 karels 10 9
c don't print binary
e
s 00002/00002/00344
d D 4.6 85/01/22 17:05:34 ralph 9 8
c close files before returning.
e
s 00004/00002/00342
d D 4.5 84/11/26 12:35:11 ralph 8 7
c don't quit if __SYMDEF should happen to have a valid a.out magic #.
e
s 00000/00000/00344
d D 4.4 83/07/01 23:57:01 wnj 7 6
c include problems
e
s 00001/00001/00343
d D 4.3 83/06/30 14:51:10 sam 6 5
c include fix
e
s 00002/00001/00342
d D 4.2 83/05/22 18:32:27 sam 5 4
c pagsiz.h must go....
e
s 00000/00000/00343
d D 4.1 80/10/01 16:39:34 bill 4 3
c Define 4.1
e
s 00001/00000/00342
d D 3.3 80/09/09 16:04:47 bill 3 2
c added N_PC to stbnames, since i added it to <stab.h>
e
s 00003/00003/00339
d D 3.2 80/08/17 01:55:36 bill 2 1
c typo in .o length check
e
s 00342/00000/00000
d D 3.1 80/08/15 01:55:17 bill 1 0
c date and time created 80/08/15 01:55:17 by bill
e
u
U
t
T
I 11
/*
D 12
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
D 20
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * This code is derived from software contributed to Berkeley by
 * Hans Huebner.
 *
D 17
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 12
 */

E 11
I 5
#ifndef lint
E 5
I 1
D 12
static	char sccsid[] = "%Z%%M% %I% %G%";
I 5
#endif
E 12
I 12
D 20
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 20
I 20
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 20
#endif /* not lint */
E 12
I 11

E 11
E 5
D 12
/*
 * nm - print name list; VAX string table version
 */
E 12
I 12
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 12
I 11

E 11
#include <sys/types.h>
I 11
D 12
#include <sys/file.h>
E 11
D 2
#include <newar.h>
E 2
I 2
#include <ar.h>
E 2
#include <stdio.h>
#include <ctype.h>
E 12
D 2
#include <newa.out.h>
E 2
I 2
#include <a.out.h>
E 2
#include <stab.h>
I 12
#include <ar.h>
E 12
D 5
#include <pagsiz.h>
E 5
D 6
#include <stat.h>
E 6
I 6
D 11
#include <sys/stat.h>
E 11
I 11
#include <ranlib.h>
I 12
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
I 16
#include <stdlib.h>
E 16
D 15
#include <strings.h>
E 15
I 15
#include <string.h>
E 15
E 12
E 11
E 6

D 11
#define	SELECT	archive ? archdr.ar_name : *xargv
E 11
I 11
D 12
#define	OARMAG		0177545		/* OLD archive magic number */
#define	SELECT		(archive ? archdr.ar_name : *xargv)
E 12
I 12
D 14
int	ignore_bad_archive_entries = 1;
int	print_only_external_symbols;
int	print_only_undefined_symbols;
int	print_all_symbols;
int	print_file_each_line;
int	cmp_value(), cmp_name();
int	(*sort_func)() = cmp_name;
E 14
I 14
D 16
extern int errno;
E 14
E 12
E 11

E 16
I 14
int ignore_bad_archive_entries = 1;
int print_only_external_symbols;
int print_only_undefined_symbols;
int print_all_symbols;
int print_file_each_line;
D 19
int cmp_value(), cmp_name();
int (*sort_func)() = cmp_name;

E 14
D 11
int	aflg, gflg, nflg, oflg, pflg, uflg; 
int	rflg = 1;
char	**xargv;
int	archive;
struct	ar_hdr	archdr;
union {
	char	mag_armag[SARMAG+1];
E 11
I 11
D 12
#define	YES		1
#define	NO		0
E 12
I 12
enum { FORWARD, BACKWARD } sort_direction = FORWARD;
E 19
int fcount;
E 12

I 19
int rev;
int fname(), rname(), value();
int (*sfunc)() = fname;

E 19
D 12
#define	u_strx		n_un.n_strx
#define	u_name		n_un.n_name
E 12
I 12
/* some macros for symbol type (nlist.n_type) handling */
#define	IS_DEBUGGER_SYMBOL(x)	((x) & N_STAB)
#define	IS_EXTERNAL(x)		((x) & N_EXT)
#define	SYMBOL_TYPE(x)		((x) & (N_TYPE | N_STAB))
E 12

I 19
void *emalloc();

E 19
D 12
typedef struct nlist	NLIST;

union {				/* exec header, or magic string from library */
	char	mag_armag[SARMAG + 1];
E 11
	struct	exec mag_exp;
} mag_un;
D 11
#define	OARMAG	0177545
FILE	*fi;
off_t	off;
off_t	ftell();
char	*malloc();
char	*realloc();
char	*strp;
char	*stab();
off_t	strsiz;
int	compare();
int	narg;
int	errs;
E 11

I 11
struct	ar_hdr	archdr;		/* archive file header structure */
FILE	*fi;			/* input file stream */
off_t	off;			/* offset into file */
int	aflg,			/* print debugger symbols */
	gflg,			/* print only global (external symbols */
	nflg,			/* sort numerically, not alphabetically */
	oflg,			/* prepend element name to each output line */
	pflg,			/* don't sort */
	rflg = 1,		/* how to sort */
	uflg,			/* print only undefined symbols */
	narg,			/* global number of arguments */
	errs,			/* global error flag */
	archive;		/* if file is an archive */
char	**xargv;		/* global pointer to file name */

E 12
I 12
/*
 * main()
 *	parse command line, execute process_file() for each file
 *	specified on the command line.
 */
E 12
E 11
main(argc, argv)
D 11
char **argv;
E 11
I 11
D 12
	int	argc;
	char	**argv;
E 12
I 12
	int argc;
	char **argv;
E 12
E 11
{
I 11
D 12
	extern int	optind;
	int	ch;			/* getopts char */
E 12
I 12
	extern int optind;
	int ch, errors;
E 12
E 11

D 11
	if (--argc>0 && argv[1][0]=='-' && argv[1][1]!=0) {
		argv++;
		while (*++*argv) switch (**argv) {

		case 'n':
			nflg++;
			continue;
E 11
I 11
D 12
	while ((ch = getopt(argc, argv, "agnopru")) != EOF)
		switch((char)ch) {
E 12
I 12
	while ((ch = getopt(argc, argv, "agnopruw")) != EOF) {
		switch (ch) {
E 12
		case 'a':
D 12
			aflg = YES;
E 12
I 12
			print_all_symbols = 1;
E 12
			break;
E 11
		case 'g':
D 11
			gflg++;
			continue;
		case 'u':
			uflg++;
			continue;
E 11
I 11
D 12
			gflg = YES;
E 12
I 12
			print_only_external_symbols = 1;
E 12
			break;
		case 'n':
D 12
			nflg = YES;
E 12
I 12
D 19
			sort_func = cmp_value;
E 19
I 19
			sfunc = value;
E 19
E 12
			break;
		case 'o':
D 12
			oflg = YES;
E 12
I 12
			print_file_each_line = 1;
E 12
			break;
		case 'p':
D 12
			pflg = YES;
E 12
I 12
D 19
			sort_func = NULL;
E 19
I 19
			sfunc = NULL;
E 19
E 12
			break;
E 11
		case 'r':
D 12
			rflg = -1;
E 12
I 12
D 19
			sort_direction = BACKWARD;
E 19
I 19
			rev = 1;
E 19
E 12
D 11
			continue;
		case 'p':
			pflg++;
			continue;
		case 'o':
			oflg++;
			continue;
		case 'a':
			aflg++;
			continue;
E 11
I 11
			break;
		case 'u':
D 12
			uflg = YES;
E 12
I 12
			print_only_undefined_symbols = 1;
E 12
			break;
I 12
		case 'w':
			ignore_bad_archive_entries = 0;
			break;
E 12
		case '?':
E 11
		default:
D 11
			fprintf(stderr, "nm: invalid argument -%c\n",
			    *argv[0]);
E 11
I 11
D 12
			fputs("usage: nm [-agnopru] [file ...]\n", stderr);
E 11
			exit(2);
E 12
I 12
			usage();
E 12
		}
D 11
		argc--;
	}
	if (argc == 0) {
E 11
I 11
D 12
	argc -= optind;
E 12
I 12
	}
	fcount = argc - optind;
E 12
	argv += optind;
D 12
	if (!argc) {
E 11
		argc = 1;
D 11
		argv[1] = "a.out";
E 11
I 11
		argv[0] = "a.out";
E 12
I 12

I 19
	if (rev && sfunc == fname)
		sfunc = rname;

E 19
	if (!fcount)
		errors = process_file("a.out");
	else {
		errors = 0;
		do {
			errors |= process_file(*argv);
		} while (*++argv);
E 12
E 11
	}
D 12
	narg = argc;
D 11
	xargv = argv;
	while (argc--) {
		++xargv;
		namelist();
	}
E 11
I 11
	for (xargv = argv; argc--; ++xargv)
		if (fi = fopen(*xargv, "r")) {
			namelist();
			(void)fclose(fi);
		}
		else
			error(NO, "cannot open");
E 11
	exit(errs);
E 12
I 12
	exit(errors);
E 12
}

D 12
namelist()
E 12
I 12
/*
 * process_file()
 *	show symbols in the file given as an argument.  Accepts archive and
 *	object files as input.
 */
process_file(fname)
	char *fname;
E 12
{
D 11
	register int j;
E 11
I 11
D 12
	register NLIST	*N, **L;
	register int	symcount, nsyms;
	static	NLIST	*symp, **list;
	static int	lastnsyms = -1,
			laststrsiz = -1;
	static char	*strp;
	off_t	strsiz;
	long	lseek();
	int	compare();
	char	*malloc(), *realloc();
E 12
I 12
	struct exec exec_head;
	FILE *fp;
	int retval;
	char magic[SARMAG];
    
	if (!(fp = fopen(fname, "r"))) {
		(void)fprintf(stderr, "nm: cannot read %s.\n", fname);
		return(1);
	}
E 12
E 11

I 12
	if (fcount > 1)
		(void)printf("\n%s:\n", fname);
    
E 12
D 11
	archive = 0;
	fi = fopen(*xargv, "r");
	if (fi == NULL) {
		error(0, "cannot open");
E 11
I 11
	/*
D 12
	 * read first few bytes, determine if an archive,
	 * or executable; if executable, check magic number
E 12
I 12
	 * first check whether this is an object file - read a object
	 * header, and skip back to the beginning
E 12
	 */
D 12
	/*NOSTRICT*/
	if (!fread((char *)&mag_un, sizeof(mag_un), 1, fi)) {
		error(NO, "unable to read file");
E 11
		return;
E 12
I 12
D 16
	if (fread((char *)&exec_head, 1, sizeof(exec_head), fp) !=
	    sizeof(exec_head)) {
E 16
I 16
	if (fread((char *)&exec_head, sizeof(exec_head), (size_t)1, fp) != 1) {
E 16
		(void)fprintf(stderr, "nm: %s: bad format.\n", fname);
		(void)fclose(fp);
		return(1);
E 12
	}
D 11
	off = SARMAG;
	fread((char *)&mag_un, 1, sizeof(mag_un), fi);
E 11
D 12
	if (mag_un.mag_exp.a_magic == OARMAG) {
D 11
		error(0, "old archive");
D 9
		return;
E 9
I 9
		goto out;
E 11
I 11
		error(NO, "old archive");
		return;
E 11
E 9
	}
D 11
	if (strncmp(mag_un.mag_armag, ARMAG, SARMAG)==0)
		archive++;
	else if (N_BADMAG(mag_un.mag_exp)) {
		error(0, "bad format");
D 9
		return;
E 9
I 9
		goto out;
E 11
I 11
	if (bcmp(mag_un.mag_armag, ARMAG, SARMAG)) {
		if (N_BADMAG(mag_un.mag_exp)) {
			error(NO, "bad format");
			return;
E 12
I 12
	rewind(fp);

	/* this could be an archive */
	if (N_BADMAG(exec_head)) {
D 16
		if (fread(magic, 1, sizeof(magic), fp) != sizeof(magic) ||
E 16
I 16
		if (fread(magic, sizeof(magic), (size_t)1, fp) != 1 ||
E 16
		    strncmp(magic, ARMAG, SARMAG)) {
			(void)fprintf(stderr,
			    "nm: %s: not object file or archive.\n", fname);
			(void)fclose(fp);
			return(1);
E 12
		}
D 12
		archive = NO;
		rewind(fi);
E 11
E 9
	}
D 11
	fseek(fi, 0L, 0);
	if (archive) {
		nextel(fi);
E 11
I 11
	else {
E 12
I 12
		retval = show_archive(fname, fp);
	} else
		retval = show_objfile(fname, fp);
	(void)fclose(fp);
	return(retval);
}

/*
 * show_archive()
 *	show symbols in the given archive file
 */
show_archive(fname, fp)
	char *fname;
	FILE *fp;
{
D 14
	extern int errno;
E 14
	struct ar_hdr ar_head;
	struct exec exec_head;
D 16
	off_t esize;
	int i, last_ar_off, rval;
E 16
I 16
	int i, rval;
	long last_ar_off;
E 16
D 19
	char *p, *name, *emalloc();
	long atol();
E 19
I 19
	char *p, *name;
E 19

D 16
	name = emalloc((u_int)(sizeof(ar_head.ar_name) + strlen(fname) + 3));
E 16
I 16
	name = emalloc(sizeof(ar_head.ar_name) + strlen(fname) + 3);
E 16

	rval = 0;

	/* while there are more entries in the archive */
D 16
	while (fread((char *)&ar_head, 1, sizeof(ar_head), fp) ==
	    sizeof(ar_head)) {
E 16
I 16
	while (fread((char *)&ar_head, sizeof(ar_head), (size_t)1, fp) == 1) {
E 16
		/* bad archive entry - stop processing this archive */
		if (strncmp(ar_head.ar_fmag, ARFMAG, sizeof(ar_head.ar_fmag))) {
			(void)fprintf(stderr,
			    "nm: %s: bad format archive header", fname);
			(void)free(name);
			return(1);
		}

I 18
		/* remember start position of current archive object */
		last_ar_off = ftell(fp);

		/* skip ranlib entries */
		if (!strncmp(ar_head.ar_name, RANLIBMAG, sizeof(RANLIBMAG) - 1))
			goto skip;

E 18
E 12
		/*
D 12
		 * if archive, skip first entry
		 * if ranlib'd, skip second entry
E 12
I 12
D 13
		 * construct a name of the form "archive.a(obj.o)" for the
E 13
I 13
		 * construct a name of the form "archive.a:obj.o:" for the
E 13
		 * current archive entry if the object name is to be printed
		 * on each output line
E 12
		 */
D 12
		off = SARMAG;		/* see nextel() */
		(void)nextel();
		if (!strcmp(RANLIBMAG, archdr.ar_name))
			(void)nextel();
E 11
		if (narg > 1)
			printf("\n%s:\n", *xargv);
I 11
		archive = YES;
E 11
	}
E 12
I 12
D 16
		if (print_file_each_line) {
D 13
			(void)sprintf(name, "%s(", fname);
E 13
I 13
			(void)sprintf(name, "%s:", fname);
E 13
			p = name + strlen(name);
		} else
			p = name;
E 16
I 16
		p = name;
		if (print_file_each_line)
			p += sprintf(p, "%s:", fname);
E 16
		for (i = 0; i < sizeof(ar_head.ar_name); ++i)
			if (ar_head.ar_name[i] && ar_head.ar_name[i] != ' ')
				*p++ = ar_head.ar_name[i];
D 13
		if (print_file_each_line)
			*p++ = ')';
E 13
		*p++ = '\0';
E 12
D 11
	do {
		off_t o;
		register i, n, c;
		struct nlist *symp = NULL;
		struct nlist sym;
		struct stat stb;
E 11

D 11
		fread((char *)&mag_un.mag_exp, 1, sizeof(struct exec), fi);
E 11
I 11
D 12
	do {
		/* check for bad magic number */
		/*NOSTRICT*/
		if (!fread((char *)&mag_un.mag_exp, sizeof(struct exec), 1, fi)) {
			error(NO, "unable to read magic number");
			return;
		}
E 11
		if (N_BADMAG(mag_un.mag_exp))
			continue;
E 12
I 12
D 18
		/* remember start position of current archive object */
		last_ar_off = ftell(fp);
E 12
D 11
		if (archive == 0)
			fstat(fileno(fi), &stb);
		o = N_SYMOFF(mag_un.mag_exp) - sizeof (struct exec);
		fseek(fi, o, 1);
		n = mag_un.mag_exp.a_syms / sizeof(struct nlist);
		if (n == 0) {
			error(0, "no name list");
E 11
I 11

E 18
D 12
		/* calculate number of symbols in object */
		if (!(nsyms = mag_un.mag_exp.a_syms / sizeof(NLIST))) {
			error(NO, "no name list");
E 11
			continue;
E 12
I 12
		/* get and check current object's header */
D 16
		if (fread((char *)&exec_head, 1, sizeof(exec_head), fp) !=
		    sizeof(exec_head)) {
E 16
I 16
		if (fread((char *)&exec_head, sizeof(exec_head),
		    (size_t)1, fp) != 1) {
E 16
			(void)fprintf(stderr, "nm: %s: premature EOF.\n", name);
			(void)free(name);
			return(1);
E 12
		}
D 11
		if (N_STROFF(mag_un.mag_exp) + sizeof (off_t) >
D 2
		    stb.st_size)
E 2
I 2
D 8
		    (archive ? off : stb.st_size))
E 2
			error(1, "old format .o (no string table) or truncated file");
E 8
I 8
		    (archive ? off : stb.st_size)) {
			error(0, "old format .o (no string table) or truncated file");
E 11
I 11
D 12

		/* seek to and read symbols */
		(void)fseek(fi, (long)(N_SYMOFF(mag_un.mag_exp) - sizeof(struct exec)), L_INCR);
		if (!symp || nsyms > lastnsyms) {
			if (!symp) {
				/*NOSTRICT*/
				symp = (NLIST *)malloc((u_int)(nsyms * sizeof(NLIST)));
				/*NOSTRICT*/
				list = (NLIST **)malloc((u_int)(nsyms * sizeof(NLIST *)));
E 12
I 12
D 18
		if (strcmp(name, RANLIBMAG))
			if (N_BADMAG(exec_head)) {
				if (!ignore_bad_archive_entries) {
					(void)fprintf(stderr,
					    "nm: %s: bad format.\n", name);
					rval = 1;
				}
			} else {
				(void)fseek(fp, (long)-sizeof(exec_head),
				    SEEK_CUR);
				if (!print_file_each_line)
					(void)printf("\n%s:\n", name);
				rval |= show_objfile(name, fp);
E 18
I 18

		if (N_BADMAG(exec_head)) {
			if (!ignore_bad_archive_entries) {
				(void)fprintf(stderr,
				    "nm: %s: bad format.\n", name);
				rval = 1;
E 18
E 12
			}
I 18
		} else {
			(void)fseek(fp, (long)-sizeof(exec_head),
			    SEEK_CUR);
			if (!print_file_each_line)
				(void)printf("\n%s:\n", name);
			rval |= show_objfile(name, fp);
		}
E 18
D 12
			else {
				/*NOSTRICT*/
				symp = (NLIST *)realloc((char *)symp, (u_int)(nsyms * sizeof(NLIST)));
				/*NOSTRICT*/
				list = (NLIST **)realloc((char *)list, (u_int)(nsyms * sizeof(NLIST *)));
			}
			if (!symp || !list)
				error(YES, "out of memory");
			lastnsyms = nsyms;
E 12
I 12
D 16
		esize = atol(ar_head.ar_size);
E 16

		/*
D 16
		 * skip to next archive object - esize&1 is added to stay
	 	 * on even starting points relative to the start of the
		 * archive file
E 16
I 16
		 * skip to next archive object - it starts at the next
	 	 * even byte boundary
E 16
		 */
D 16
		if (fseek(fp, (long)(last_ar_off + esize + (esize&1)),
E 16
I 16
#define even(x) (((x) + 1) & ~1)
D 18
		if (fseek(fp, last_ar_off + even(atol(ar_head.ar_size)),
E 18
I 18
skip:		if (fseek(fp, last_ar_off + even(atol(ar_head.ar_size)),
E 18
E 16
		    SEEK_SET)) {
			(void)fprintf(stderr,
			    "nm: %s: %s\n", fname, strerror(errno));
			(void)free(name);
			return(1);
E 12
		}
D 12
		/*NOSTRICT*/
		if (fread((char *)symp, sizeof(NLIST), nsyms, fi) != nsyms) {
			error(NO, "bad symbol table");
E 11
			continue;
		}
E 12
I 12
	}
	(void)free(name);
	return(rval);
}
E 12
E 8
D 11
		i = 0;
		if (strp)
			free(strp), strp = 0;
		while (--n >= 0) {
			fread((char *)&sym, 1, sizeof(sym), fi);
			if (gflg && (sym.n_type&N_EXT)==0)
				continue;
			if ((sym.n_type&N_STAB) && (!aflg||gflg||uflg))
				continue;
			if (symp==NULL)
				symp = (struct nlist *)
				    malloc(sizeof(struct nlist));
			else
				symp = (struct nlist *)
				    realloc(symp,
					(i+1)*sizeof(struct nlist));
			if (symp == NULL)
				error(1, "out of memory");
			symp[i++] = sym;
		}
		if (archive && ftell(fi)+sizeof(off_t) >= off) {
			error(0, "no string table (old format .o?)");
E 11
I 11

D 12
		/* read number of strings, string table */
		/*NOSTRICT*/
		if (!fread((char *)&strsiz, sizeof(strsiz), 1, fi)) {
			error(NO, "no string table (old format .o?)");
E 12
I 12
/*
 * show_objfile()
 *	show symbols from the object file pointed to by fp.  The current
 *	file pointer for fp is expected to be at the beginning of an a.out
 *	header.
 */
show_objfile(objname, fp)
	char *objname;
	FILE *fp;
{
D 16
	register struct nlist *names;
E 16
I 16
	register struct nlist *names, *np;
E 16
	register int i, nnames, nrawnames;
	struct exec head;
	long stabsize;
D 19
	char *stab, *emalloc();
E 19
I 19
	char *stab;
E 19

	/* read a.out header */
D 16
	if (fread((char *)&head, sizeof(head), 1, fp) != 1) {
E 16
I 16
	if (fread((char *)&head, sizeof(head), (size_t)1, fp) != 1) {
E 16
		(void)fprintf(stderr,
		    "nm: %s: cannot read header.\n", objname);
		return(1);
	}

	/*
	 * skip back to the header - the N_-macros return values relative
	 * to the beginning of the a.out header
	 */
	if (fseek(fp, (long)-sizeof(head), SEEK_CUR)) {
		(void)fprintf(stderr,
		    "nm: %s: %s\n", objname, strerror(errno));
		return(1);
	}

	/* stop if this is no valid object file */
	if (N_BADMAG(head)) {
		(void)fprintf(stderr,
		    "nm: %s: bad format.\n", objname);
		return(1);
	}

	/* stop if the object file contains no symbol table */
	if (!head.a_syms) {
		(void)fprintf(stderr,
		    "nm: %s: no name list.\n", objname);
		return(1);
	}

	if (fseek(fp, (long)N_SYMOFF(head), SEEK_CUR)) {
		(void)fprintf(stderr,
		    "nm: %s: %s\n", objname, strerror(errno));
		return(1);
	}

	/* get memory for the symbol table */
D 16
	names = (struct nlist *)emalloc((u_int)head.a_syms);
E 16
I 16
D 19
	names = (struct nlist *)emalloc((size_t)head.a_syms);
E 19
I 19
	names = emalloc((size_t)head.a_syms);
E 19
E 16
	nrawnames = head.a_syms / sizeof(*names);
D 16
	if (fread((char *)names, 1, (int)head.a_syms, fp) != head.a_syms) {
E 16
I 16
	if (fread((char *)names, (size_t)head.a_syms, (size_t)1, fp) != 1) {
E 16
		(void)fprintf(stderr,
		    "nm: %s: cannot read symbol table.\n", objname);
		(void)free((char *)names);
		return(1);
	}

	/*
	 * Following the symbol table comes the string table.  The first
	 * 4-byte-integer gives the total size of the string table
	 * _including_ the size specification itself.
	 */
D 16
	if (fread((char *)&stabsize, sizeof(stabsize), 1, fp) != 1) {
E 16
I 16
	if (fread((char *)&stabsize, sizeof(stabsize), (size_t)1, fp) != 1) {
E 16
		(void)fprintf(stderr,
		    "nm: %s: cannot read stab size.\n", objname);
		(void)free((char *)names);
		return(1);
	}
D 16
	stab = emalloc((u_int)stabsize);
E 16
I 16
	stab = emalloc((size_t)stabsize);
E 16

	/*
	 * read the string table offset by 4 - all indices into the string
	 * table include the size specification.
	 */
D 13
	stabsize -=4;		/* we already have the size */
E 13
I 13
	stabsize -= 4;		/* we already have the size */
E 13
D 16
	if (fread(stab + 4, 1, (int)stabsize, fp) != stabsize) {
E 16
I 16
	if (fread(stab + 4, (size_t)stabsize, (size_t)1, fp) != 1) {
E 16
		(void)fprintf(stderr,
		    "nm: %s: stab truncated..\n", objname);
		(void)free((char *)names);
		(void)free(stab);
		return(1);
	}

	/*
	 * fix up the symbol table and filter out unwanted entries
	 *
	 * common symbols are characterized by a n_type of N_UNDF and a
	 * non-zero n_value -- change n_type to N_COMM for all such
	 * symbols to make life easier later.
	 *
	 * filter out all entries which we don't want to print anyway
	 */
D 16
	for (i = nnames = 0; i < nrawnames; ++i) {
		if (SYMBOL_TYPE(names[i].n_type) == N_UNDF && names[i].n_value)
			names[i].n_type = N_COMM | (names[i].n_type & N_EXT);
		if (!print_all_symbols && IS_DEBUGGER_SYMBOL(names[i].n_type))
E 16
I 16
	for (np = names, i = nnames = 0; i < nrawnames; np++, i++) {
		if (SYMBOL_TYPE(np->n_type) == N_UNDF && np->n_value)
			np->n_type = N_COMM | (np->n_type & N_EXT);
		if (!print_all_symbols && IS_DEBUGGER_SYMBOL(np->n_type))
E 16
E 12
E 11
			continue;
D 12
		}
D 11
		if (fread((char *)&strsiz,sizeof(strsiz),1,fi) != 1) {
			error(0, "no string table (old format .o?)");
			goto out;
E 11
I 11
		if (!strp || strsiz > laststrsiz) {
			strp = strp ? realloc(strp, (u_int)strsiz) : malloc((u_int)strsiz);
			if (!strp)
				error(YES, "out of memory");
			laststrsiz = strsiz;
E 11
		}
D 11
		strp = (char *)malloc(strsiz);
		if (strp == NULL)
			error(1, "ran out of memory");
		if (fread(strp+sizeof(strsiz),strsiz-sizeof(strsiz),1,fi) != 1)
			error(1, "error reading string table");
		for (j = 0; j < i; j++)
			if (symp[j].n_un.n_strx)
				symp[j].n_un.n_name =
				    symp[j].n_un.n_strx + strp;
			else
				symp[j].n_un.n_name = "";
		if (pflg==0)
			qsort(symp, i, sizeof(struct nlist), compare);
		if ((archive || narg>1) && oflg==0)
E 11
I 11
		if (!fread(strp + sizeof(strsiz), 1, (int)(strsiz - sizeof(strsiz)), fi)) {
			error(NO, "no string table (old format .o?)");
E 12
I 12
D 16
		if (print_only_external_symbols &&
		    !IS_EXTERNAL(names[i].n_type))
E 16
I 16
		if (print_only_external_symbols && !IS_EXTERNAL(np->n_type))
E 16
E 12
			continue;
D 12
		}
E 12
I 12
		if (print_only_undefined_symbols &&
D 16
		    (SYMBOL_TYPE(names[i].n_type) != N_UNDF))
E 16
I 16
		    SYMBOL_TYPE(np->n_type) != N_UNDF)
E 16
			continue;
E 12

D 12
		for (symcount = nsyms, L = list, N = symp;--nsyms >= 0;++N)
			if (!(N->n_type & N_EXT) && gflg || N->n_type & N_STAB && (!aflg || gflg || uflg))
				--symcount;
			else {
				N->u_name = N->u_strx ? strp + N->u_strx : "";
				*L++ = N;
			}
E 12
I 12
		/*
		 * make n_un.n_name a character pointer by adding the string
		 * table's base to n_un.n_strx
		 *
D 16
		 * don't mess with null offsets
E 16
I 16
		 * don't mess with zero offsets
E 16
		 */
D 16
		if (names[i].n_un.n_name)
			names[i].n_un.n_name = stab + names[i].n_un.n_strx;
E 16
I 16
		if (np->n_un.n_strx)
			np->n_un.n_name = stab + np->n_un.n_strx;
E 16
		else
D 16
			names[i].n_un.n_name = "";
		if (nnames != i)
			names[nnames] = names[i];
		++nnames;
E 16
I 16
			np->n_un.n_name = "";
		names[nnames++] = *np;
E 16
	}
E 12

D 12
		if (!pflg)
			qsort(list, symcount, sizeof(NLIST *), compare);
E 12
I 12
	/* sort the symbol table if applicable */
D 19
	if (sort_func)
D 16
		qsort((char *)names, (int)nnames, sizeof(*names), sort_func);
E 16
I 16
		qsort((char *)names, (size_t)nnames, sizeof(*names), sort_func);
E 19
I 19
	if (sfunc)
		qsort((char *)names, (size_t)nnames, sizeof(*names), sfunc);
E 19
E 16
E 12

D 12
		if ((archive || narg > 1) && !oflg)
E 11
			printf("\n%s:\n", SELECT);
E 12
I 12
	/* print out symbols */
D 16
	for (i = 0; i < nnames; ++i)
		print_symbol(objname, &names[i]);
E 16
I 16
	for (np = names, i = 0; i < nnames; np++, i++)
		print_symbol(objname, np);
E 16
E 12
D 11
		psyms(symp, i);
		if (symp)
			free((char *)symp), symp = 0;
		if (strp)
			free((char *)strp), strp = 0;
	} while(archive && nextel(fi));
out:
	fclose(fi);
E 11
I 11

D 12
		psyms(list, symcount);
	} while(archive && nextel());
E 12
I 12
	(void)free((char *)names);
	(void)free(stab);
	return(0);
E 12
E 11
}

D 11
psyms(symp, nsyms)
	register struct nlist *symp;
	int nsyms;
E 11
I 11
D 12
psyms(list, nsyms)
	NLIST	**list;
	register int	nsyms;
E 12
I 12
/*
 * print_symbol()
 *	show one symbol
 */
print_symbol(objname, sym)
	char *objname;
D 16
	struct nlist *sym;
E 16
I 16
	register struct nlist *sym;
E 16
E 12
E 11
{
D 11
	register int n, c;
E 11
I 11
D 12
	register NLIST	*L;
	register u_char	type;
	char	*stab();
E 12
I 12
	char *typestring(), typeletter();
E 12
E 11

D 11
	for (n=0; n<nsyms; n++) {
		c = symp[n].n_type;
		if (c & N_STAB) {
E 11
I 11
D 12
	while (nsyms--) {
		L = *list++;
		type = L->n_type;
		if (type & N_STAB) {
E 11
			if (oflg) {
				if (archive)
					printf("%s:", *xargv);
				printf("%s:", SELECT);
			}
D 11
			printf("%08x - %02x %04x %5.5s %s\n",
			    symp[n].n_value,
			    symp[n].n_other & 0xff, symp[n].n_desc & 0xffff,
			    stab(symp[n].n_type & 0xff),
			    symp[n].n_un.n_name);
E 11
I 11
			printf("%08x - %02x %04x %5.5s %s\n", (int)L->n_value, L->n_other & 0xff, L->n_desc & 0xffff, stab(L->n_type), L->u_name);
E 11
			continue;
		}
D 10
		switch (c&N_TYPE) {
E 10
I 10
D 11
		if (c == N_FN)
			c = 'f';
		else switch (c&N_TYPE) {
E 10

E 11
I 11
		switch (type & N_TYPE) {
E 11
		case N_UNDF:
D 11
			c = 'u';
			if (symp[n].n_value)
				c = 'c';
E 11
I 11
			type = L->n_value ? 'c' : 'u';
E 11
			break;
		case N_ABS:
D 11
			c = 'a';
E 11
I 11
			type = 'a';
E 11
			break;
		case N_TEXT:
D 11
			c = 't';
E 11
I 11
			type = 't';
E 11
			break;
		case N_DATA:
D 11
			c = 'd';
E 11
I 11
			type = 'd';
E 11
			break;
		case N_BSS:
D 11
			c = 'b';
E 11
I 11
			type = 'b';
E 11
			break;
I 11
		case N_FN:
			type = 'f';
			break;
E 11
D 10
		case N_FN:
			c = 'f';
E 10
I 10
		default:
D 11
			c = '?';
E 11
I 11
			type = '?';
E 11
E 10
			break;
		}
D 11
		if (uflg && c!='u')
E 11
I 11
		if (uflg && type != 'u')
E 11
			continue;
		if (oflg) {
			if (archive)
				printf("%s:", *xargv);
			printf("%s:", SELECT);
		}
D 11
		if (symp[n].n_type&N_EXT)
			c = toupper(c);
E 11
I 11
		if (L->n_type & N_EXT)
			type = toupper(type);
E 11
		if (!uflg) {
D 11
			if (c=='u' || c=='U')
				printf("        ");
E 11
I 11
			if (type == 'u' || type == 'U')
				fputs("        ", stdout);
E 11
			else
D 11
				printf(N_FORMAT, symp[n].n_value);
			printf(" %c ", c);
E 11
I 11
				printf(N_FORMAT, (int)L->n_value);
			printf(" %c ", (char)type);
E 11
		}
D 11
		printf("%s\n", symp[n].n_un.n_name);
l1:		;
E 11
I 11
		puts(L->u_name);
E 12
I 12
	if (print_file_each_line)
D 13
		printf("%s: ", objname);
E 13
I 13
D 16
		printf("%s:", objname);
E 16
I 16
		(void)printf("%s:", objname);
E 16
E 13

	/*
	 * handle undefined-only format seperately (no space is
	 * left for symbol values, no type field is printed)
	 */
	if (print_only_undefined_symbols) {
D 16
		printf("%s\n", sym->n_un.n_name);
E 16
I 16
		(void)puts(sym->n_un.n_name);
E 16
		return;
E 12
E 11
	}
I 12

	/* print symbol's value */
	if (SYMBOL_TYPE(sym->n_type) == N_UNDF)
		(void)printf("        ");
	else
		(void)printf("%08lx", sym->n_value);

	/* print type information */
	if (IS_DEBUGGER_SYMBOL(sym->n_type))
		(void)printf(" - %02x %04x %5s ", sym->n_other,
		    sym->n_desc&0xffff, typestring(sym->n_type));
	else
		(void)printf(" %c ", typeletter(sym->n_type));

	/* print the symbol's name */
D 16
	(void)printf("%s\n", sym->n_un.n_name ? sym->n_un.n_name : "");
E 16
I 16
	(void)puts(sym->n_un.n_name);
E 16
E 12
}

D 12
compare(p1, p2)
D 11
struct nlist *p1, *p2;
E 11
I 11
	NLIST	**p1, **p2;
E 12
I 12
/*
 * typestring()
 *	return the a description string for an STAB entry
 */
char *
typestring(type)
	register u_char type;
E 12
E 11
{
D 11
	register i;

E 11
D 12
	if (nflg) {
D 11
		if (p1->n_value > p2->n_value)
E 11
I 11
		if ((*p1)->n_value > (*p2)->n_value)
E 11
			return(rflg);
D 11
		if (p1->n_value < p2->n_value)
E 11
I 11
		if ((*p1)->n_value < (*p2)->n_value)
E 11
			return(-rflg);
E 12
I 12
	switch(type) {
	case N_BCOMM:
		return("BCOMM");
	case N_ECOML:
		return("ECOML");
	case N_ECOMM:
		return("ECOMM");
	case N_ENTRY:
		return("ENTRY");
	case N_FNAME:
		return("FNAME");
	case N_FUN:
		return("FUN");
	case N_GSYM:
		return("GSYM");
	case N_LBRAC:
		return("LBRAC");
	case N_LCSYM:
		return("LCSYM");
	case N_LENG:
		return("LENG");
	case N_LSYM:
		return("LSYM");
	case N_PC:
		return("PC");
	case N_PSYM:
		return("PSYM");
	case N_RBRAC:
		return("RBRAC");
	case N_RSYM:
		return("RSYM");
	case N_SLINE:
		return("SLINE");
	case N_SO:
		return("SO");
	case N_SOL:
		return("SOL");
	case N_SSYM:
		return("SSYM");
	case N_STSYM:
		return("STSYM");
E 12
	}
D 11
	return (rflg * strcmp(p1->n_un.n_name, p2->n_un.n_name));
E 11
I 11
D 12
	return(rflg * strcmp((*p1)->u_name, (*p2)->u_name));
E 12
I 12
	return("???");
E 12
E 11
}

D 11
nextel(af)
FILE *af;
E 11
I 11
D 12
nextel()
E 12
I 12
/*
 * typeletter()
 *	return a description letter for the given basic type code of an
 *	symbol table entry.  The return value will be upper case for
 *	external, lower case for internal symbols.
 */
char
typeletter(type)
	u_char type;
E 12
E 11
{
D 11
	register char *cp;
	register r;
	long arsize;
E 11
I 11
D 12
	register char	*cp;
	long	arsize,
		lseek();
E 12
I 12
	switch(SYMBOL_TYPE(type)) {
	case N_ABS:
		return(IS_EXTERNAL(type) ? 'A' : 'a');
	case N_BSS:
		return(IS_EXTERNAL(type) ? 'B' : 'b');
	case N_COMM:
		return(IS_EXTERNAL(type) ? 'C' : 'c');
	case N_DATA:
		return(IS_EXTERNAL(type) ? 'D' : 'd');
	case N_FN:
		return(IS_EXTERNAL(type) ? 'F' : 'f');
	case N_TEXT:
		return(IS_EXTERNAL(type) ? 'T' : 't');
	case N_UNDF:
		return(IS_EXTERNAL(type) ? 'U' : 'u');
	}
	return('?');
}
E 12
E 11

D 11
	fseek(af, off, 0);
	r = fread((char *)&archdr, 1, sizeof(struct ar_hdr), af);
	if (r != sizeof(struct ar_hdr))
E 11
I 11
D 12
	(void)fseek(fi, off, L_SET);
	/*NOSTRICT*/
	if (!fread((char *)&archdr, sizeof(struct ar_hdr), 1, fi))
E 11
		return(0);
D 11
	for (cp = archdr.ar_name; cp < &archdr.ar_name[sizeof(archdr.ar_name)]; cp++)
		if (*cp == ' ')
E 11
I 11
	for (cp = archdr.ar_name; cp < &archdr.ar_name[sizeof(archdr.ar_name)]; ++cp)
		if (*cp == ' ') {
E 11
			*cp = '\0';
I 11
			break;
		}
E 11
	arsize = atol(archdr.ar_size);
	if (arsize & 1)
		++arsize;
D 11
	off = ftell(af) + arsize;	/* beginning of next element */
E 11
I 11
	off = ftell(fi) + arsize;	/* beginning of next element */
E 11
	return(1);
E 12
I 12
D 19
/*
 * cmp_name()
 *	compare two symbols by their names
 */
D 16
cmp_name(a, b)
	struct nlist *a, *b;
E 16
I 16
cmp_name(a0, b0)
E 19
I 19
fname(a0, b0)
E 19
	void *a0, *b0;
E 16
{
I 16
	struct nlist *a = a0, *b = b0;

E 16
D 19
	return(sort_direction == FORWARD ?
	    strcmp(a->n_un.n_name, b->n_un.n_name) :
	    strcmp(b->n_un.n_name, a->n_un.n_name));
E 19
I 19
	return(strcmp(a->n_un.n_name, b->n_un.n_name));
E 19
E 12
}

D 11
error(n, s)
char *s;
{
	fprintf(stderr, "nm: %s:", *xargv);
	if (archive) {
		fprintf(stderr, "(%s)", archdr.ar_name);
		fprintf(stderr, ": ");
	} else
		fprintf(stderr, " ");
	fprintf(stderr, "%s\n", s);
	if (n)
		exit(2);
	errs = 1;
}

E 11
D 12
struct	stabnames {
	int	st_value;
	char	*st_name;
} stabnames[] ={
D 11
	N_GSYM, "GSYM",
	N_FNAME, "FNAME",
	N_FUN, "FUN",
	N_STSYM, "STSYM",
	N_LCSYM, "LCSYM",
	N_RSYM, "RSYM",
	N_SLINE, "SLINE",
	N_SSYM, "SSYM",
	N_SO, "SO",
	N_LSYM, "LSYM",
	N_SOL, "SOL",
	N_PSYM, "PSYM",
	N_ENTRY, "ENTRY",
	N_LBRAC, "LBRAC",
	N_RBRAC, "RBRAC",
	N_BCOMM, "BCOMM",
	N_ECOMM, "ECOMM",
	N_ECOML, "ECOML",
	N_LENG, "LENG",
I 3
	N_PC, "PC",
E 3
	0, 0
E 11
I 11
	N_GSYM,		"GSYM",
	N_FNAME,	"FNAME",
	N_FUN,		"FUN",
	N_STSYM,	"STSYM",
	N_LCSYM,	"LCSYM",
	N_RSYM,		"RSYM",
	N_SLINE,	"SLINE",
	N_SSYM,		"SSYM",
	N_SO,		"SO",
	N_LSYM,		"LSYM",
	N_SOL,		"SOL",
	N_PSYM,		"PSYM",
	N_ENTRY,	"ENTRY",
	N_LBRAC,	"LBRAC",
	N_RBRAC,	"RBRAC",
	N_BCOMM,	"BCOMM",
	N_ECOMM,	"ECOMM",
	N_ECOML,	"ECOML",
	N_LENG,		"LENG",
	N_PC,		"PC",
	0,		0
E 11
};
E 12
I 12
D 19
/*
 * cmp_value()
 *	compare two symbols by their values
 */
D 16
cmp_value(a, b)
	struct nlist *a, *b;
E 16
I 16
cmp_value(a0, b0)
E 19
I 19
rname(a0, b0)
E 19
	void *a0, *b0;
E 16
{
I 19
	struct nlist *a = a0, *b = b0;

	return(strcmp(b->n_un.n_name, a->n_un.n_name));
}

value(a0, b0)
	void *a0, *b0;
{
E 19
I 16
	register struct nlist *a = a0, *b = b0;

E 16
	if (SYMBOL_TYPE(a->n_type) == N_UNDF)
		if (SYMBOL_TYPE(b->n_type) == N_UNDF)
			return(0);
		else
			return(-1);
	else if (SYMBOL_TYPE(b->n_type) == N_UNDF)
		return(1);
D 19
	if (a->n_value == b->n_value)
D 16
		return(cmp_name(a, b));
E 16
I 16
		return(cmp_name((void *)a, (void *)b));
E 16
	return(sort_direction == FORWARD ? a->n_value > b->n_value :
	    a->n_value < b->n_value);
E 19
I 19
	if (rev) {
		if (a->n_value == b->n_value)
			return(rname(a0, b0));
		return(b->n_value > a->n_value ? 1 : -1);
	} else {
		if (a->n_value == b->n_value)
			return(fname(a0, b0));
		return(a->n_value > b->n_value ? 1 : -1);
	}
E 19
}
E 12

D 19
char *
E 19
I 19
void *
E 19
D 12
stab(val)
I 11
	register u_char	val;
E 12
I 12
emalloc(size)
D 16
	u_int size;
E 16
I 16
	size_t size;
E 16
E 12
E 11
{
D 11
	register struct stabnames *sp;
	static char prbuf[32];
E 11
I 11
D 12
	register struct stabnames	*sp;
	static char	prbuf[5];
E 12
I 12
D 16
	char *p, *malloc();
E 16
I 16
	char *p;
E 16
E 12
E 11

D 11
	for (sp = stabnames; sp->st_name; sp++)
E 11
I 11
D 12
	for (sp = stabnames; sp->st_value; ++sp)
E 11
		if (sp->st_value == val)
D 11
			return (sp->st_name);
	sprintf(prbuf, "%02x", val);
	return (prbuf);
E 11
I 11
			return(sp->st_name);
	(void)sprintf(prbuf, "%02x", (int)val);
	return(prbuf);
E 12
I 12
	/* NOSTRICT */
D 19
	if (!(p = malloc(size))) {
		(void)fprintf(stderr, "nm: no more memory.\n");
		exit(1);
	}
	return(p);
E 19
I 19
	if (p = malloc(size))
		return(p);
	(void)fprintf(stderr, "nm: %s\n", strerror(errno));
	exit(1);
E 19
E 12
}

D 12
error(doexit, msg)
	int	doexit;
	char	*msg;
E 12
I 12
usage()
E 12
{
D 12
	fprintf(stderr, "nm: %s:", *xargv);
	if (archive)
		fprintf(stderr, "(%s): %s\n", archdr.ar_name, msg);
	else
		fprintf(stderr, " %s\n", msg);
	if (doexit)
		exit(2);
	errs = 1;
E 12
I 12
D 16
	(void)fprintf(stderr, "usage: nm [-agnopruw] [file ...]");
E 16
I 16
	(void)fprintf(stderr, "usage: nm [-agnopruw] [file ...]\n");
E 16
	exit(1);
E 12
E 11
}
E 1
