h28725
s 00002/00002/00158
d D 8.1 93/06/06 13:58:34 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00027/00139
d D 5.8 93/04/10 08:03:39 bostic 8 7
c general cleanup, use new err(3) routines
e
s 00001/00001/00165
d D 5.7 92/07/01 17:05:35 bostic 7 6
c off_t's are now quad's -- ANSI C says fseek/ftell use longs
e
s 00023/00018/00143
d D 5.6 92/05/04 17:05:05 bostic 6 5
c update from LBL (Chris, Craig and Steve)
e
s 00003/00008/00158
d D 5.5 91/09/12 22:31:01 torek 5 4
c not so many #ifdef's; our name is kvm_mkdb, not symorder
e
s 00000/00001/00166
d D 5.4 91/04/27 16:23:43 bostic 4 3
c don't need user.h anymore
e
s 00019/00018/00148
d D 5.3 91/03/03 13:44:05 bostic 3 2
c convert from ndbm(3) to db(3) interface
e
s 00071/00054/00095
d D 5.2 91/02/12 22:57:51 bostic 2 1
c read the symbol table into malloc'd space instead of seeking
c (turns out to not really be a big win, but it does make some difference).
e
s 00149/00000/00000
d D 5.1 91/02/06 17:14:57 bostic 1 0
c date and time created 91/02/06 17:14:57 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
E 8
I 8
D 9
 * Copyright (c) 1990, 1993 The Regents of the University of California.
E 8
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
I 3
D 4
#include <sys/user.h>
E 4
E 3
D 2
#include <errno.h>
E 2
I 2
D 8
#include <fcntl.h>
E 2
#include <limits.h>
E 8
I 8

E 8
D 3
#include <ndbm.h>
E 3
#include <a.out.h>
I 3
#include <db.h>
I 8
#include <err.h>
E 8
E 3
D 2
#include <kvm.h>
E 2
I 2
#include <errno.h>
E 2
D 8
#include <unistd.h>
E 8
I 8
#include <fcntl.h>
E 8
I 2
#include <kvm.h>
I 8
#include <limits.h>
E 8
E 2
#include <stdio.h>
I 2
D 8
#include <string.h>
E 8
#include <stdlib.h>
I 8
#include <string.h>
#include <unistd.h>
E 8
E 2

I 6
#include "extern.h"

E 6
typedef struct nlist NLIST;
#define	_strx	n_un.n_strx
#define	_name	n_un.n_name

I 8
#define	badfmt(str)	errx(1, "%s: %s: %s", kfile, str, strerror(EFTYPE))

E 8
I 6
static void badread __P((int, char *));
D 8
static void badfmt __P((char *));
E 8

E 6
D 2
#define	BFLEN		1024
#define	VRS		"_version"

E 2
static char *kfile;

I 6
void
E 6
create_knlist(name, db)
	char *name;
D 3
	DBM *db;
E 3
I 3
	DB *db;
E 3
{
D 2
	register char *bp;
	register int ch, len;
E 2
I 2
	register int nsyms;
E 2
	struct exec ebuf;
D 2
	FILE *fstr, *fsym;
E 2
I 2
	FILE *fp;
E 2
	NLIST nbuf;
D 2
	off_t string_off, symbol_off, symbol_size;
	off_t rel_off, vers_off;
E 2
D 3
	datum key, data;
E 3
I 3
	DBT data, key;
E 3
D 2
	char sbuf[BFLEN];
E 2
I 2
	int fd, nr, strsize;
	char *strtab, buf[1024];
E 2

D 2
	/* Two pointers, one for symbol table and one for string table. */
E 2
	kfile = name;
D 2
	if ((fsym = fopen(name, "r")) == NULL ||
	    (fstr = fopen(name, "r")) == NULL)
E 2
I 2
	if ((fd = open(name, O_RDONLY, 0)) < 0)
E 2
D 8
		error(name);
E 8
I 8
		err(1, "%s", name);
E 8

D 2
	if (fread((char *)&ebuf, sizeof(struct exec), 1, fsym) != 1)
		badfmt("no exec header");
E 2
I 2
	/* Read in exec structure. */
D 8
	nr = read(fd, (char *)&ebuf, sizeof(struct exec));
E 8
I 8
	nr = read(fd, &ebuf, sizeof(struct exec));
E 8
	if (nr != sizeof(struct exec))
D 6
		badfmt(nr, "no exec header");
E 6
I 6
		badfmt("no exec header");
E 6

	/* Check magic number and symbol count. */
E 2
	if (N_BADMAG(ebuf))
		badfmt("bad magic number");
D 2
		
	symbol_size = ebuf.a_syms;
	if (!symbol_size)
E 2
I 2
	if (!ebuf.a_syms)
E 2
		badfmt("stripped");

D 2
	symbol_off = N_SYMOFF(ebuf);
	string_off = symbol_off + symbol_size;
E 2
I 2
	/* Seek to string table. */
	if (lseek(fd, N_STROFF(ebuf), SEEK_SET) == -1)
		badfmt("corrupted string table");
E 2

D 2
	if (fseek(fsym, symbol_off, SEEK_SET) == -1)
		badfmt("corrupted symbol table");
E 2
I 2
	/* Read in the size of the symbol table. */
	nr = read(fd, (char *)&strsize, sizeof(strsize));
	if (nr != sizeof(strsize))
		badread(nr, "no symbol table");
E 2

D 2
	key.dptr = sbuf;
E 2
I 2
	/* Read in the string table. */
	strsize -= sizeof(strsize);
D 8
	if (!(strtab = (char *)malloc(strsize)))
		error(name);
E 8
I 8
	if (!(strtab = malloc(strsize)))
		err(1, NULL);
E 8
	if ((nr = read(fd, strtab, strsize)) != strsize)
		badread(nr, "corrupted symbol table");

	/* Seek to symbol table. */
	if (!(fp = fdopen(fd, "r")))
D 8
		error(name);
E 8
I 8
		err(1, "%s", name);
E 8
	if (fseek(fp, N_SYMOFF(ebuf), SEEK_SET) == -1)
D 8
		error(name);
E 8
I 8
		err(1, "%s", name);
E 8
	
E 2
D 3
	data.dptr = (char *)&nbuf;
	data.dsize = sizeof(NLIST);
E 3
I 3
	data.data = (u_char *)&nbuf;
	data.size = sizeof(NLIST);
E 3

D 2
	for (; symbol_size; symbol_size -= sizeof(NLIST)) {
		if (fread((char *)&nbuf, sizeof (NLIST), 1, fsym) != 1)
			badfmt("corrupted symbol table");
E 2
I 2
	/* Read each symbol and enter it into the database. */
	nsyms = ebuf.a_syms / sizeof(struct nlist);
	while (nsyms--) {
		if (fread((char *)&nbuf, sizeof (NLIST), 1, fp) != 1) {
			if (feof(fp))
				badfmt("corrupted symbol table");
D 8
			error(name);
E 8
I 8
			err(1, "%s", name);
E 8
		}
E 2
		if (!nbuf._strx || nbuf.n_type&N_STAB)
			continue;
D 2
		if (fseek(fstr, string_off + nbuf._strx, SEEK_SET) == -1)
			badfmt("corrupted string table");
E 2

D 2
		/* Read string. */
		bp = sbuf;
		for (len = 0; (ch = getc(fstr)) != EOF && ch != '\0';) {
			if (++len == BFLEN) {
				(void)fprintf(stderr,
				    "kvm_mkdb: symbol too long.");
				break;
			}
			*bp++ = ch;
		}
		if (len == BFLEN)
			continue;

		/* Store string. */
		key.dsize = len;
E 2
I 2
D 3
		key.dptr = strtab + nbuf._strx - sizeof(long);
		key.dsize = strlen(key.dptr);
E 2
		if (dbm_store(db, key, data, DBM_INSERT) < 0)
			error("dbm_store");
E 3
I 3
		key.data = (u_char *)strtab + nbuf._strx - sizeof(long);
		key.size = strlen((char *)key.data);
D 8
		if ((db->put)(db, &key, &data, 0))
			error("put");
E 8
I 8
		if (db->put(db, &key, &data, 0))
			err(1, "record enter");
E 8
E 3

D 2
		if (!strncmp(sbuf, VRS, sizeof(VRS) - 1)) {
E 2
I 2
D 3
		if (!strncmp(key.dptr, VRS_SYM, sizeof(VRS_SYM) - 1)) {
E 3
I 3
D 6
		if (!strncmp((char *)key.data, VRS_SYM, sizeof(VRS_SYM) - 1)) {
E 3
			off_t cur_off, rel_off, vers_off;

E 2
			/* Offset relative to start of text image in VM. */
D 5
#ifdef hp300
			rel_off = nbuf.n_value;
#endif
E 5
I 5
			rel_off = nbuf.n_value & ~KERNBASE;
E 5
#ifdef tahoe
			/*
			 * On tahoe, first 0x800 is reserved for communication
			 * with the console processor.
			 */
D 5
			rel_off = ((nbuf.n_value & ~KERNBASE) - 0x800);
E 5
I 5
			rel_off -= 0x800;
E 6
I 6
		if (strcmp((char *)key.data, VRS_SYM) == 0) {
D 7
			off_t cur_off, voff;
E 7
I 7
			long cur_off, voff;
E 7
#ifndef KERNTEXTOFF
#define KERNTEXTOFF KERNBASE
E 6
E 5
#endif
D 5
#ifdef vax
			rel_off = nbuf.n_value & ~KERNBASE;
#endif
E 5
			/*
D 6
			 * When loaded, data is rounded to next page cluster
			 * after text, but not in file.
E 6
I 6
			 * Calculate offset relative to a normal (non-kernel)
			 * a.out.  KERNTEXTOFF is where the kernel is really
			 * loaded; N_TXTADDR is where a normal file is loaded.
			 * From there, locate file offset in text or data.
E 6
			 */
D 6
			rel_off -= CLBYTES - (ebuf.a_text % CLBYTES);
			vers_off = N_TXTOFF(ebuf) + rel_off;
D 2
			if (fseek(fstr, vers_off, SEEK_SET) == -1)
E 2
I 2

E 6
I 6
			voff = nbuf.n_value - KERNTEXTOFF + N_TXTADDR(ebuf);
			if ((nbuf.n_type & N_TYPE) == N_TEXT)
				voff += N_TXTOFF(ebuf) - N_TXTADDR(ebuf);
			else
				voff += N_DATOFF(ebuf) - N_DATADDR(ebuf);
E 6
			cur_off = ftell(fp);
D 6
			if (fseek(fp, vers_off, SEEK_SET) == -1)
E 6
I 6
			if (fseek(fp, voff, SEEK_SET) == -1)
E 6
E 2
				badfmt("corrupted string table");

			/*
			 * Read version string up to, and including newline.
			 * This code assumes that a newline terminates the
			 * version line.
			 */
D 2
			if (fgets(sbuf, sizeof(sbuf), fstr) == NULL)
E 2
I 2
			if (fgets(buf, sizeof(buf), fp) == NULL)
E 2
				badfmt("corrupted string table");

D 2
			key.dptr = VERSION;
			key.dsize = sizeof(VERSION) - 1;
			data.dptr = sbuf;
			data.dsize = strlen(sbuf);
E 2
I 2
D 3
			key.dptr = VRS_KEY;
			key.dsize = sizeof(VRS_KEY) - 1;
			data.dptr = buf;
			data.dsize = strlen(buf);
E 2
			if (dbm_store(db, key, data, DBM_INSERT) < 0)
				error("dbm_store");
E 3
I 3
			key.data = (u_char *)VRS_KEY;
			key.size = sizeof(VRS_KEY) - 1;
			data.data = (u_char *)buf;
			data.size = strlen(buf);
D 8
			if ((db->put)(db, &key, &data, 0))
				error("put");
E 8
I 8
			if (db->put(db, &key, &data, 0))
				err(1, "record enter");
E 8
E 3

			/* Restore to original values. */
D 2
			key.dptr = sbuf;
E 2
D 3
			data.dptr = (char *)&nbuf;
			data.dsize = sizeof(NLIST);
E 3
I 3
			data.data = (u_char *)&nbuf;
			data.size = sizeof(NLIST);
E 3
I 2
			if (fseek(fp, cur_off, SEEK_SET) == -1)
				badfmt("corrupted string table");
E 2
		}
	}
D 2
	(void)fclose(fstr);
	(void)fclose(fsym);
E 2
I 2
	(void)fclose(fp);
E 2
}

I 6
static void
E 6
I 2
badread(nr, p)
	int nr;
	char *p;
{
	if (nr < 0)
D 8
		error(kfile);
E 8
I 8
		err(1, "%s", kfile);
E 8
	badfmt(p);
D 8
}

I 6
static void
E 6
E 2
badfmt(p)
I 2
	char *p;
E 2
{
	(void)fprintf(stderr,
D 5
	    "symorder: %s: %s: %s\n", kfile, p, strerror(EFTYPE));
E 5
I 5
	    "kvm_mkdb: %s: %s: %s\n", kfile, p, strerror(EFTYPE));
E 5
	exit(1);
E 8
}
E 1
