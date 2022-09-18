h50586
s 00001/00001/00209
d D 8.3 95/05/16 06:23:46 bostic 21 20
c uninitialized varaible
e
s 00023/00046/00187
d D 8.2 95/04/28 14:27:00 bostic 20 19
c strip.c fails to close short files, does not use library err/warn
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00005/00228
d D 8.1 93/06/06 16:25:52 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00009/00231
d D 5.13 93/05/31 19:50:47 ralph 18 17
c use macros from exec.h to portably truncate the a.out file
e
s 00007/00002/00233
d D 5.12 92/08/07 08:58:44 bostic 17 16
c do fstat before checking the size; from Craig Leres
e
s 00028/00013/00207
d D 5.11 92/06/24 09:33:26 bostic 16 15
c check size of mmap'd object; clean up error handling
e
s 00003/00003/00217
d D 5.10 92/06/24 09:23:13 bostic 15 14
c fix mmap call (MAP_FILE is gone) plus type casting
e
s 00004/00003/00216
d D 5.9 92/06/21 12:25:11 bostic 14 13
c lseek takes a quad; minor cleanups
e
s 00046/00086/00173
d D 5.8 91/11/06 08:47:17 bostic 13 12
c use mmap for debugging stripping so don't run out of memory
e
s 00174/00029/00085
d D 5.7 91/05/26 11:07:12 bostic 12 11
c add -d option to strip debugging and empty symbols
e
s 00066/00020/00048
d D 5.6 91/05/25 16:50:59 bostic 11 10
c Good morning!  It's an ANSI kind of world!
e
s 00001/00011/00067
d D 5.5 90/06/01 16:11:00 bostic 10 9
c new copyright notice
e
s 00009/00009/00069
d D 5.4 89/12/09 13:55:59 bostic 9 8
c remove diagnostic if the file has already been stripped; for
c install -s which now uses strip.
e
s 00056/00055/00022
d D 5.3 88/06/30 19:38:45 bostic 8 7
c rewritten from the manual page; add Berkeley specific header
e
s 00001/00001/00076
d D 5.2 88/04/01 10:46:01 bostic 7 6
c fprintf missing an argument; bug report 4.3BSD/bin/120
e
s 00014/00002/00063
d D 5.1 85/04/30 15:05:21 dist 6 5
c Add copyright
e
s 00018/00069/00047
d D 4.5 83/07/06 23:30:56 sam 5 4
c suped up version uses ftruncate...(I knew there was a reason 
c to add that system call)
e
s 00006/00002/00110
d D 4.4 83/05/22 18:32:34 sam 4 3
c pagsiz.h must go....
e
s 00001/00001/00111
d D 4.3 83/04/29 00:51:57 mckusick 3 2
c added perror
e
s 00001/00001/00111
d D 4.2 82/03/31 22:45:56 mckusic 2 1
c explicit define BUFSIZ as 1024
e
s 00112/00000/00000
d D 4.1 80/10/01 17:28:39 bill 1 0
c date and time created 80/10/01 17:28:39 by bill
e
u
U
t
T
I 6
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 19
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 10
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
 */

E 6
I 4
#ifndef lint
E 4
I 1
D 6
static char *sccsid = "%W% (Berkeley) %G%";
I 4
#endif
E 6
I 6
D 19
char copyright[] =
D 8
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 8
I 8
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 8
 All rights reserved.\n";
E 19
I 19
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 19
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8
E 6

I 8
#include <sys/types.h>
I 12
#include <sys/stat.h>
I 13
#include <sys/mman.h>
I 16

D 20
#include <limits.h>
E 16
E 13
E 12
D 11
#include <sys/file.h>
E 11
I 11
#include <fcntl.h>
#include <errno.h>
E 20
E 11
E 8
E 4
#include <a.out.h>
I 11
D 20
#include <unistd.h>
E 20
I 20
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
E 20
E 11
D 8
#include <signal.h>
E 8
I 5
#include <stdio.h>
I 11
#include <stdlib.h>
#include <string.h>
I 20
#include <unistd.h>
E 20
E 11
D 8
#include <sys/file.h>
E 8
E 5
D 4
#include <pagsiz.h>
E 4

I 11
D 12
static void err __P((const char *fmt, ...));

E 12
E 11
I 9
typedef struct exec EXEC;
I 12
typedef struct nlist NLIST;
E 12

I 13
#define	strx	n_un.n_strx

E 13
I 12
D 16
void err __P((const char *fmt, ...));
E 16
I 16
D 20
void err __P((int, const char *fmt, ...));
E 20
E 16
void s_stab __P((const char *, int, EXEC *));
void s_sym __P((const char *, int, EXEC *));
void usage __P((void));

I 16
D 20
int eval;

E 20
E 16
I 14
int
E 14
D 13
int eval;

E 13
E 12
E 9
D 2
#define	BUFSIZ	BSIZE
E 2
I 2
D 5
#define	BUFSIZ	1024
E 2

char	*tname;
char	*mktemp();
struct exec head;
E 5
I 5
D 8
struct	exec head;
E 5
int	status;
D 5
int	tf;
E 5
I 4
int	pagesize;
E 4

E 8
I 8
D 11
/* ARGSUSED */
E 11
E 8
main(argc, argv)
D 5
char *argv[];
E 5
I 5
D 8
	char *argv[];
E 8
I 8
	int argc;
D 11
	char **argv;
E 11
I 11
	char *argv[];
E 11
E 8
E 5
{
D 8
	register i;
E 8
I 8
D 9
	typedef struct exec EXEC;
E 9
D 12
	register off_t fsize;
	register int fd, n, pagesize;
E 12
I 12
	register int fd, nb;
E 12
	EXEC head;
D 11
	off_t lseek();
E 11
I 11
D 12
	int ch, dstabs;
E 12
I 12
	void (*sfcn)__P((const char *, int, EXEC *));
D 20
	int ch;
E 20
I 20
	int ch, eval;
E 20
	char *fn;
E 12
E 11
E 8

I 11
D 12
	dstabs = 0;
E 12
I 12
	sfcn = s_sym;
E 12
	while ((ch = getopt(argc, argv, "d")) != EOF)
		switch(ch) {
		case 'd':
D 12
			dstabs = 1;
E 12
I 12
			sfcn = s_stab;
E 12
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

E 11
I 4
D 12
	pagesize = getpagesize();
E 4
D 8
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
D 5
	tname = mktemp("/tmp/sXXXXX");
	close(creat(tname, 0600));
	tf = open(tname, 2);
	if(tf < 0) {
		printf("cannot create temp file\n");
		exit(2);
	}
	for(i=1; i<argc; i++) {
E 5
I 5
	for (i = 1; i < argc; i++) {
E 5
		strip(argv[i]);
D 5
		if(status > 1)
E 5
I 5
		if (status > 1)
E 5
			break;
E 8
I 8
D 11
	while (*++argv) {
E 11
I 11

	for (; *argv; ++argv) {
E 11
		if ((fd = open(*argv, O_RDWR)) < 0 ||
D 11
		    (n = read(fd, (char *)&head, sizeof(EXEC))) == -1)
			error(*argv);
E 11
I 11
		    (n = read(fd, &head, sizeof(EXEC))) == -1) {
			err("%s: %s", *argv, strerror(errno));
E 12
I 12
D 20
	while (fn = *argv++) {
		if ((fd = open(fn, O_RDWR)) < 0 ||
		    (nb = read(fd, &head, sizeof(EXEC))) == -1) {
D 16
			err("%s: %s", fn, strerror(errno));
E 16
I 16
			err(0, "%s: %s", fn, strerror(errno));
E 20
I 20
D 21
	while ((fn = *argv++) != NULL) {
E 21
I 21
	for (eval = 0; (fn = *argv++) != NULL;) {
E 21
		if ((fd = open(fn, O_RDWR)) < 0) {
			warn("%s", fn);
			eval = 1;
E 20
E 16
E 12
			continue;
		}
I 20
		if ((nb = read(fd, &head, sizeof(EXEC))) == -1) {
			warn("%s", fn);
			(void)close(fd);
			eval = 1;
			continue;
		}
E 20
E 11
D 12
		if (n != sizeof(EXEC) || N_BADMAG(head)) {
D 9
			fprintf(stderr, "strip: %s not in a.out format.\n",
			    *argv);
E 9
I 9
D 11
			(void)fprintf(stderr,
			    "strip: %s not in a.out format.\n", *argv);
E 9
			exit(1);
E 11
I 11
			err("%s: %s", *argv, strerror(EFTYPE));
E 12
I 12
		if (nb != sizeof(EXEC) || N_BADMAG(head)) {
D 16
			err("%s: %s", fn, strerror(EFTYPE));
E 16
I 16
D 20
			err(0, "%s: %s", fn, strerror(EFTYPE));
E 20
I 20
			warnx("%s: %s", fn, strerror(EFTYPE));
			(void)close(fd);
			eval = 1;
E 20
E 16
E 12
			continue;
E 11
		}
D 9
		if (!head.a_syms && !head.a_trsize && !head.a_drsize) {
			fprintf(stderr, "strip: %s already stripped.\n", *argv);
E 9
I 9
D 11
		if (!head.a_syms && !head.a_trsize && !head.a_drsize)
E 11
I 11
D 12
		if (!head.a_syms && !head.a_trsize && !head.a_drsize) {
			(void)close(fd);
E 11
E 9
			continue;
I 11
		}
E 11
D 9
		}
E 9
		fsize = head.a_text + head.a_data;
		if (head.a_magic == ZMAGIC)
			fsize += pagesize - sizeof(EXEC);
		head.a_syms = head.a_trsize = head.a_drsize = 0;
E 12
I 12
		sfcn(fn, fd, &head);
D 20
		if (close(fd))
D 16
			err("%s: %s", fn, strerror(errno));
E 16
I 16
			err(0, "%s: %s", fn, strerror(errno));
E 20
I 20
		if (close(fd)) {
			warn("%s", fn);
			eval = 1;
		}
E 20
E 16
	}
D 13
	exit(eval);
E 13
I 13
D 16
	exit(0);
E 16
I 16
	exit(eval);
E 16
E 13
}
E 12
I 11

E 11
D 12
		if (ftruncate(fd, fsize + sizeof(EXEC)) ||
D 11
		    lseek(fd, 0L, L_SET) == -1 ||
		    write(fd, (char *)&head, sizeof(EXEC)) != sizeof(EXEC))
			error(*argv);
E 11
I 11
		    lseek(fd, 0L, SEEK_SET) == -1 ||
		    write(fd, &head, sizeof(EXEC)) != sizeof(EXEC))
			err("%s: %s", *argv, strerror(errno)); 
E 11
		(void)close(fd);
E 12
I 12
void
s_sym(fn, fd, ep)
	const char *fn;
	int fd;
	register EXEC *ep;
{
D 18
	static int pagesize = -1;
E 18
	register off_t fsize;

	/* If no symbols or data/text relocation info, quit. */
	if (!ep->a_syms && !ep->a_trsize && !ep->a_drsize)
		return;

	/*
D 18
	 * New file size is the header plus text and data segments; OMAGIC
	 * and NMAGIC formats have the text/data immediately following the
	 * header.  ZMAGIC format wastes the rest of of header page.
E 18
I 18
	 * New file size is the header plus text and data segments.
E 18
	 */
D 18
	if (ep->a_magic == ZMAGIC)
		fsize = pagesize == -1 ? (pagesize = getpagesize()) : pagesize;
	else
		fsize = sizeof(EXEC);
	fsize += ep->a_text + ep->a_data;
E 18
I 18
	fsize = N_DATOFF(*ep) + ep->a_data;
E 18

	/* Set symbol size and relocation info values to 0. */
	ep->a_syms = ep->a_trsize = ep->a_drsize = 0;

	/* Rewrite the header and truncate the file. */
D 14
	if (lseek(fd, 0L, SEEK_SET) == -1 ||
E 14
I 14
	if (lseek(fd, (off_t)0, SEEK_SET) == -1 ||
E 14
	    write(fd, ep, sizeof(EXEC)) != sizeof(EXEC) ||
	    ftruncate(fd, fsize))
D 16
		err("%s: %s", fn, strerror(errno)); 
E 16
I 16
		err(0, "%s: %s", fn, strerror(errno)); 
E 16
}

void
s_stab(fn, fd, ep)
	const char *fn;
	int fd;
	EXEC *ep;
{
I 13
D 14
	register int cnt, len, nsymcnt;
E 14
I 14
	register int cnt, len;
E 14
	register char *nstr, *nstrbase, *p, *strbase;
	register NLIST *sym, *nsym;
E 13
	struct stat sb;
D 13
	register NLIST *bsym2, *sym1, *sym2;
	register u_long nsym1, nsym2;
	register char *p, *bstr2, *str1, *str2;
	register int len, symlen;
	off_t fsize;
	int nb;
	char *bp;
E 13
I 13
	NLIST *symbase;
E 13

	/* Quit if no symbols. */
	if (ep->a_syms == 0)
		return;

I 17
	/* Stat the file. */
	if (fstat(fd, &sb) < 0) {
		err(0, "%s: %s", fn, strerror(errno));
		return;
	}

E 17
I 16
	/* Check size. */
	if (sb.st_size > SIZE_T_MAX) {
		err(0, "%s: %s", fn, strerror(EFBIG));
		return;
	}

E 16
D 13
	bsym2 = NULL;
	bp = bstr2 = NULL;
E 13
I 13
	/* Map the file. */
D 17
	if (fstat(fd, &sb) ||
D 14
	    (ep = (EXEC *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE,
E 14
I 14
D 15
	    (ep = (EXEC *)mmap(NULL, (int)sb.st_size, PROT_READ | PROT_WRITE,
E 14
	    MAP_FILE | MAP_SHARED, fd, (off_t)0)) == (EXEC *)-1)
E 15
I 15
	    (ep = (EXEC *)mmap(NULL, (size_t)sb.st_size,
E 17
I 17
	if ((ep = (EXEC *)mmap(NULL, (size_t)sb.st_size,
E 17
D 16
	    PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0)) == (EXEC *)-1)
E 15
		err("%s: %s", fn, strerror(errno));
E 16
I 16
	    PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0)) == (EXEC *)-1) {
		err(0, "%s: %s", fn, strerror(errno));
		return;
	}
E 16
E 13

D 13
	/* Read the file into memory.			XXX mmap */
	if (fstat(fd, &sb))
		goto syserr;
	if ((bp = malloc(sb.st_size)) == NULL)
		goto syserr;
	if (lseek(fd, 0L, SEEK_SET) == -1)
		goto syserr;
	if ((nb = read(fd, bp, (int)sb.st_size)) == -1)
		goto syserr;
	if (nb != sb.st_size) {
		errno = EIO;
		goto syserr;
E 12
E 8
	}
E 13
I 13
	/*
	 * Initialize old and new symbol pointers.  They both point to the
	 * beginning of the symbol table in memory, since we're deleting
	 * entries.
	 */
	sym = nsym = symbase = (NLIST *)((char *)ep + N_SYMOFF(*ep));
E 13
D 5
	close(tf);
	unlink(tname);
E 5
D 8
	exit(status);
E 8
I 8
D 12
	exit(0);
E 12
I 12

	/*
D 13
	 * Allocate space for new symbol and string tables.  Allocate before
	 * reading the symbol tables so we can do it all in a single pass.
	 * This loses if there weren't any symbols to strip, but that's life.
E 13
I 13
	 * Allocate space for the new string table, initialize old and
	 * new string pointers.  Handle the extra long at the beginning
	 * of the string table.
E 13
	 */
D 13
	sym1 = (NLIST *)(bp + N_SYMOFF(*ep));
	if ((bsym2 = sym2 = malloc((u_int)ep->a_syms)) == NULL) {
E 13
I 13
	strbase = (char *)ep + N_STROFF(*ep);
	if ((nstrbase = malloc((u_int)*(u_long *)strbase)) == NULL)
E 13
D 16
		err("%s", strerror(errno));
E 16
I 16
		err(1, "%s", strerror(errno));
E 16
D 13
		goto mem;
	}
	str1 = bp + N_STROFF(*ep);
	if ((bstr2 = malloc((u_int)*(u_long *)str1)) == NULL) {
		err("%s", strerror(errno));
		goto mem;
	}
	str2 = bstr2 + sizeof(u_long);
	symlen = sizeof(u_long);
E 13
I 13
	nstr = nstrbase + sizeof(u_long);
E 13

	/*
	 * Read through the symbol table.  For each non-debugging symbol,
D 13
	 * copy it into the new symbol and string tables.  Keep track of
	 * how many symbols are copied and the length of the new string
	 * table.
E 13
I 13
	 * copy it and save its string in the new string table.  Keep
	 * track of the number of symbols.
E 13
	 */
D 13
#define	strx	n_un.n_strx
	nsym2 = 0;
	for (nsym1 = ep->a_syms / sizeof(NLIST); nsym1--; ++sym1)
		if (!(sym1->n_type & N_STAB) && sym1->strx) {
			*sym2 = *sym1;
			sym2->strx = str2 - bstr2;
			p = str1 + sym1->strx;
E 13
I 13
	for (cnt = ep->a_syms / sizeof(NLIST); cnt--; ++sym)
		if (!(sym->n_type & N_STAB) && sym->strx) {
			*nsym = *sym;
			nsym->strx = nstr - nstrbase;
			p = strbase + sym->strx;
E 13
			len = strlen(p) + 1;
D 13
			bcopy(p, str2, len);
			symlen += len;
			str2 += len;
			++sym2;
			++nsym2;
E 13
I 13
			bcopy(p, nstr, len);
			nstr += len;
			++nsym;
E 13
		}

D 13
	/* If no debugging symbols, quit. */
	if (!nsym2)
		goto mem;

E 13
	/* Fill in new symbol table size. */
D 13
	ep->a_syms = nsym2 * sizeof(NLIST);
E 13
I 13
	ep->a_syms = (nsym - symbase) * sizeof(NLIST);
E 13

D 13
	/* Write out the header. */
	if (lseek(fd, 0L, SEEK_SET) == -1 ||
	    write(fd, ep, sizeof(EXEC)) != sizeof(EXEC))
		goto syserr;

	/* Write out the symbol table. */
	if (lseek(fd, N_SYMOFF(*ep), SEEK_SET) == -1 ||
	    write(fd, bsym2, ep->a_syms) != ep->a_syms)
		goto syserr;

E 13
	/* Fill in the new size of the string table. */
D 13
	*(u_long *)bstr2 = symlen;
E 13
I 13
	*(u_long *)nstrbase = len = nstr - nstrbase;
E 13

D 13
	/* Write out the string table. */
	if (write(fd, bstr2, symlen) != symlen)
		goto syserr;
E 13
I 13
	/*
	 * Copy the new string table into place.  Nsym should be pointing
	 * at the address past the last symbol entry.
	 */
	bcopy(nstrbase, (void *)nsym, len);
E 13

	/* Truncate to the current length. */
D 13
	if ((fsize = lseek(fd, 0L, SEEK_CUR)) == -1)
		goto syserr;
	if (ftruncate(fd, fsize))
syserr:		err("%s: %s", fn, strerror(errno));

mem:	if (bp)
		free(bp);
	if (bstr2)
		free(bstr2);
	if (bsym2)
		free(bsym2);
E 13
I 13
	if (ftruncate(fd, (char *)nsym + len - (char *)ep))
D 16
		err("%s: %s", fn, strerror(errno));
E 16
I 16
		err(0, "%s: %s", fn, strerror(errno));
E 16
D 15
	munmap((caddr_t)ep, sb.st_size);
E 15
I 15
	munmap((caddr_t)ep, (size_t)sb.st_size);
E 15
E 13
E 12
E 8
}

I 12
void
E 12
D 8
strip(name)
D 5
char *name;
E 5
I 5
	char *name;
E 8
I 8
D 9
static
E 9
D 11
error(fname)
	char *fname;
E 11
I 11
usage()
E 11
E 8
E 5
{
I 12
D 13

E 13
E 12
D 8
	register f;
	long size;
D 5
	int i;
E 5

D 5
	f = open(name, 0);
	if(f < 0) {
D 3
		printf("cannot open %s\n", name);
E 3
I 3
		perror(name);
E 5
I 5
	f = open(name, O_RDWR);
	if (f < 0) {
		fprintf(stderr, "strip: "); perror(name);
E 5
E 3
		status = 1;
		goto out;
	}
D 5
	read(f, (char *)&head, sizeof(head));
	if (N_BADMAG(head)) {
		printf("%s not in a.out format\n", name);
E 5
I 5
	if (read(f, (char *)&head, sizeof (head)) < 0 || N_BADMAG(head)) {
		printf("strip: %s not in a.out format\n", name);
E 5
		status = 1;
		goto out;
	}
	if ((head.a_syms == 0) && (head.a_trsize == 0) && (head.a_drsize ==0)) {
D 5
		printf("%s already stripped\n", name);
E 5
I 5
		printf("strip: %s already stripped\n", name);
E 5
		goto out;
	}
	size = (long)head.a_text + head.a_data;
D 5
	head.a_syms = head.a_trsize = head.a_drsize = 0 ;
	lseek(tf, (long)0, 0);
	write(tf, (char *)&head, sizeof(head));
E 5
I 5
	head.a_syms = head.a_trsize = head.a_drsize = 0;
E 5
	if (head.a_magic == ZMAGIC)
D 4
		size += PAGSIZ - sizeof (head);
E 4
I 4
		size += pagesize - sizeof (head);
E 4
D 5
	if (copy(name, f, tf, size)) {
E 5
I 5
	if (ftruncate(f, size + sizeof (head)) < 0) {
D 7
		fprintf("strip: "); perror(name);
E 7
I 7
		fputs("strip: ", stderr); perror(name);
E 7
E 5
		status = 1;
		goto out;
	}
D 5
	size += sizeof(head);
	close(f);
	f = creat(name, 0666);
	if(f < 0) {
		printf("%s cannot recreate\n", name);
		status = 1;
		goto out;
	}
	lseek(tf, (long)0, 0);
	if(copy(name, tf, f, size))
		status = 2;

E 5
I 5
	(void) lseek(f, (long)0, L_SET);
	(void) write(f, (char *)&head, sizeof (head));
E 5
out:
	close(f);
E 8
I 8
D 9
	fprintf(stderr, "strip: %s: ", fname);
	perror((char *)NULL);
E 9
I 9
D 11
	extern int errno;
	char *strerror();

	(void)fprintf(stderr, "strip: %s: %s.\n", fname, strerror(errno));
E 11
I 11
	(void)fprintf(stderr, "usage: strip [-d] file ...\n");
E 11
E 9
	exit(1);
I 11
D 20
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
D 16
err(const char *fmt, ...)
E 16
I 16
err(int fatal, const char *fmt, ...)
E 16
#else
D 16
err(fmt, va_alist)
E 16
I 16
err(fatal, fmt, va_alist)
	int fatal;
E 16
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
	(void)fprintf(stderr, "strip: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
I 12
D 13
	eval = 1;
E 13
I 13
D 16
	exit(1);
E 16
I 16
	if (fatal)
		exit(1);
	eval = 1;
E 20
E 16
E 13
E 12
E 11
E 8
D 5
}

copy(name, fr, to, size)
char *name;
long size;
{
	register s, n;
	char buf[BUFSIZ];

	while(size != 0) {
		s = BUFSIZ;
		if(size < BUFSIZ)
			s = size;
		n = read(fr, buf, s);
		if(n != s) {
			printf("%s unexpected eof\n", name);
			return(1);
		}
		n = write(to, buf, s);
		if(n != s) {
			printf("%s unexpected write eof\n", name);
			return(1);
		}
		size -= s;
	}
	return(0);
E 5
}
E 1
