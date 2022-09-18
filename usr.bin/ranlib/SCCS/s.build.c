h52852
s 00002/00002/00255
d D 8.1 93/06/06 16:03:39 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00008/00244
d D 5.6 93/05/19 15:40:17 bostic 6 5
c symcnt, tsymlen not reinitialized on each archive; bug report net2/usr.bin/34
e
s 00002/00002/00250
d D 5.5 93/05/04 07:49:35 torek 5 4
c fseek returns an int 0 for success, not a position
e
s 00013/00014/00239
d D 5.4 92/06/19 15:12:10 bostic 4 3
c lseek now returns a quad
e
s 00004/00005/00249
d D 5.3 91/03/12 09:20:02 bostic 3 2
c comply with ar source changes nothing else
e
s 00004/00003/00250
d D 5.2 91/02/26 14:53:12 bostic 2 1
c ANSI fixes (one real bug!)
e
s 00253/00000/00000
d D 5.1 91/01/18 18:45:35 bostic 1 0
c date and time created 91/01/18 18:45:35 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/stat.h>
D 6
#include <fcntl.h>
E 6
I 6

E 6
#include <a.out.h>
D 6
#include <dirent.h>
#include <unistd.h>
E 6
#include <ar.h>
I 6
#include <dirent.h>
#include <fcntl.h>
E 6
#include <ranlib.h>
#include <stdio.h>
D 6
#include <archive.h>
E 6
I 6
#include <unistd.h>
E 6

I 6
#include "archive.h"

E 6
extern CHDR chdr;			/* converted header */
extern char *archive;			/* archive name */
extern char *tname;			/* temporary file "name" */

typedef struct _rlib {
	struct _rlib *next;		/* next structure */
	off_t pos;			/* offset of defining archive file */
	char *sym;			/* symbol */
	int symlen;			/* strlen(sym) */
} RLIB;
RLIB *rhead, **pnext;

FILE *fp;
I 2
D 6
static void rexec(), symobj();
E 6
E 2

I 6
long symcnt;				/* symbol count */
long tsymlen;				/* total string length */

static void rexec __P((int, int));
static void symobj __P((void));

E 6
build()
{
	CF cf;
	int afd, tfd;
	off_t size;

	afd = open_archive(O_RDWR);
	fp = fdopen(afd, "r+");
	tfd = tmp();

	SETCF(afd, archive, tfd, tname, RPAD|WPAD);

	/* Read through the archive, creating list of symbols. */
	pnext = &rhead;
I 6
	symcnt = tsymlen = 0;
E 6
D 3
	while(get_header(afd)) {
E 3
I 3
	while(get_arobj(afd)) {
E 3
		if (!strcmp(chdr.name, RANLIBMAG)) {
D 3
			SKIP(afd, chdr.size, archive);
E 3
I 3
			skip_arobj(afd);
E 3
			continue;
		}
		rexec(afd, tfd);
D 3
		put_header(&cf, (struct stat *)NULL);
		copyfile(&cf, chdr.size);
E 3
I 3
		put_arobj(&cf, (struct stat *)NULL);
E 3
	}
	*pnext = NULL;

	/* Create the symbol table. */
	symobj();

	/* Copy the saved objects into the archive. */
	size = lseek(tfd, (off_t)0, SEEK_CUR);
	(void)lseek(tfd, (off_t)0, SEEK_SET);
	SETCF(tfd, tname, afd, archive, RPAD|WPAD);
D 3
	copyfile(&cf, size);
E 3
I 3
	copy_ar(&cf, size);
E 3
	(void)ftruncate(afd, lseek(afd, (off_t)0, SEEK_CUR));
	(void)close(tfd);

	/* Set the time. */
	settime(afd);
	close_archive(afd);
	return(0);
}
D 6

long symcnt;				/* symbol count */
long tsymlen;				/* total string length */
E 6

/*
 * rexec
 *	Read the exec structure; ignore any files that don't look
 *	exactly right.
 */
D 2
static
E 2
I 2
static void
E 2
rexec(rfd, wfd)
	register int rfd;
	int wfd;
{
	register RLIB *rp;
	register long nsyms;
	register int nr, symlen;
	register char *strtab, *sym;
	struct exec ebuf;
	struct nlist nl;
	off_t r_off, w_off;
	long strsize;
	void *emalloc();

	/* Get current offsets for original and tmp files. */
	r_off = lseek(rfd, (off_t)0, SEEK_CUR);
	w_off = lseek(wfd, (off_t)0, SEEK_CUR);

	/* Read in exec structure. */
D 4
	nr = read(rfd, (char *)&ebuf, sizeof(struct exec));
E 4
I 4
	nr = read(rfd, &ebuf, sizeof(struct exec));
E 4
	if (nr != sizeof(struct exec))
		goto badread;

	/* Check magic number and symbol count. */
	if (N_BADMAG(ebuf) || ebuf.a_syms == 0)
		goto bad1;

	/* Seek to string table. */
D 4
	if (lseek(rfd, N_STROFF(ebuf) + r_off, SEEK_SET) == (off_t)-1)
E 4
I 4
	if (lseek(rfd, r_off + N_STROFF(ebuf), SEEK_SET) == (off_t)-1)
E 4
		error(archive);

	/* Read in size of the string table. */
D 4
	nr = read(rfd, (char *)&strsize, sizeof(strsize));
E 4
I 4
	nr = read(rfd, &strsize, sizeof(strsize));
E 4
	if (nr != sizeof(strsize))
		goto badread;

	/* Read in the string table. */
	strsize -= sizeof(strsize);
D 4
	strtab = (char *)emalloc(strsize);
E 4
I 4
	strtab = emalloc(strsize);
E 4
	nr = read(rfd, strtab, strsize);
	if (nr != strsize) {
badread:	if (nr < 0)
			error(archive);
		goto bad2;
	}

	/* Seek to symbol table. */
D 4
	if (fseek(fp, N_SYMOFF(ebuf) + r_off, SEEK_SET) == (off_t)-1)
E 4
I 4
D 5
	if (fseek(fp, (long)r_off + N_SYMOFF(ebuf), SEEK_SET) == (off_t)-1)
E 5
I 5
	if (fseek(fp, (long)r_off + N_SYMOFF(ebuf), SEEK_SET))
E 5
E 4
		goto bad2;

	/* For each symbol read the nlist entry and save it as necessary. */
	nsyms = ebuf.a_syms / sizeof(struct nlist);
	while (nsyms--) {
D 4
		if (!fread((char *)&nl, sizeof(struct nlist), 1, fp)) {
E 4
I 4
		if (!fread(&nl, sizeof(struct nlist), 1, fp)) {
E 4
			if (feof(fp))
				badfmt();
			error(archive);
		}

		/* Ignore if no name or local. */
		if (!nl.n_un.n_strx || !(nl.n_type & N_EXT))
			continue;

		/*
		 * If the symbol is an undefined external and the n_value
		 * field is non-zero, keep it.
		 */
		if ((nl.n_type & N_TYPE) == N_UNDF && !nl.n_value)
			continue;

		/* First four bytes are the table size. */
		sym = strtab + nl.n_un.n_strx - sizeof(long);
		symlen = strlen(sym) + 1;

		rp = (RLIB *)emalloc(sizeof(RLIB));
		rp->sym = (char *)emalloc(symlen);
		bcopy(sym, rp->sym, symlen);
		rp->symlen = symlen;
		rp->pos = w_off;

		/* Build in forward order for "ar -m" command. */
		*pnext = rp;
		pnext = &rp->next;

		++symcnt;
		tsymlen += symlen;
	}

bad2:	free(strtab);
D 4
bad1:	(void)lseek(rfd, (off_t)r_off, SEEK_SET);
E 4
I 4
bad1:	(void)lseek(rfd, r_off, SEEK_SET);
E 4
}

/*
 * symobj --
 *	Write the symbol table into the archive, computing offsets as
 *	writing.
 */
D 2
static
E 2
I 2
static void
E 2
symobj()
{
	register RLIB *rp;
	struct ranlib rn;
I 4
	off_t ransize;
	long size, stroff;
E 4
	char hb[sizeof(struct ar_hdr) + 1], pad;
D 4
	long ransize, size, stroff;
	gid_t getgid();
	uid_t getuid();
E 4

	/* Rewind the archive, leaving the magic number. */
D 4
	if (fseek(fp, (off_t)SARMAG, SEEK_SET) == (off_t)-1)
E 4
I 4
D 5
	if (fseek(fp, (long)SARMAG, SEEK_SET) == (long)-1)
E 5
I 5
	if (fseek(fp, (long)SARMAG, SEEK_SET))
E 5
E 4
		error(archive);

	/* Size of the ranlib archive file, pad if necessary. */
	ransize = sizeof(long) +
	    symcnt * sizeof(struct ranlib) + sizeof(long) + tsymlen;
	if (ransize & 01) {
		++ransize;
		pad = '\n';
	} else
		pad = '\0';

	/* Put out the ranlib archive file header. */
#define	DEFMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
	(void)sprintf(hb, HDR2, RANLIBMAG, 0L, getuid(), getgid(),
D 2
	    DEFMODE & ~umask(), ransize, ARFMAG);
E 2
I 2
	    DEFMODE & ~umask(0), ransize, ARFMAG);
E 2
	if (!fwrite(hb, sizeof(struct ar_hdr), 1, fp))
		error(tname);

	/* First long is the size of the ranlib structure section. */
	size = symcnt * sizeof(struct ranlib);
D 4
	if (!fwrite((char *)&size, sizeof(size), 1, fp))
E 4
I 4
	if (!fwrite(&size, sizeof(size), 1, fp))
E 4
		error(tname);

	/* Offset of the first archive file. */
	size = SARMAG + sizeof(struct ar_hdr) + ransize;

	/*
	 * Write out the ranlib structures.  The offset into the string
	 * table is cumulative, the offset into the archive is the value
	 * set in rexec() plus the offset to the first archive file.
	 */
	for (rp = rhead, stroff = 0; rp; rp = rp->next) {
		rn.ran_un.ran_strx = stroff;
		stroff += rp->symlen;
		rn.ran_off = size + rp->pos;
D 4
		if (!fwrite((char *)&rn, sizeof(struct ranlib), 1, fp))
E 4
I 4
		if (!fwrite(&rn, sizeof(struct ranlib), 1, fp))
E 4
			error(archive);
	}

	/* Second long is the size of the string table. */
D 4
	if (!fwrite((char *)&tsymlen, sizeof(tsymlen), 1, fp))
E 4
I 4
	if (!fwrite(&tsymlen, sizeof(tsymlen), 1, fp))
E 4
		error(tname);

	/* Write out the string table. */
	for (rp = rhead; rp; rp = rp->next)
		if (!fwrite(rp->sym, rp->symlen, 1, fp))
			error(tname);

	if (pad && !fwrite(&pad, sizeof(pad), 1, fp))
		error(tname);

	(void)fflush(fp);
}
E 1
