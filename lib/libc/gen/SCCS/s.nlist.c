h00634
s 00002/00002/00121
d D 8.1 93/06/04 12:04:07 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00003/00111
d D 5.11 92/06/24 12:18:45 bostic 19 18
c check for files too large to mmap, MAP_FILE goes away
e
s 00001/00001/00113
d D 5.10 92/04/01 19:10:07 mckusick 18 17
c fix all references to __fdnlist
e
s 00073/00055/00041
d D 5.9 92/04/01 17:15:24 torek 17 16
c split __fdnlist from nlist, for kvm
e
s 00003/00001/00093
d D 5.8 91/02/23 19:49:54 donn 16 15
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00093
d D 5.7 90/06/01 14:12:35 bostic 15 14
c new copyright notice
e
s 00001/00001/00103
d D 5.6 90/03/02 01:26:08 marc 14 13
c fixing scale of symbol_size revealed logic error
e
s 00001/00001/00103
d D 5.5 90/02/22 14:37:34 marc 13 12
c symbol_size units are bytes, not struct nlists
e
s 00003/00012/00101
d D 5.4 89/11/28 15:05:40 bostic 12 11
c use absolute offsets; it's more straight-forward and Chris says that
c the new stdio won't do an lseek per fseek.
e
s 00093/00079/00020
d D 5.3 89/11/28 15:00:48 bostic 11 10
c new version from scratch; this version uses relative offsets from the
c start of the strings area to avoid exercising problem in old stdio which did
c an lseek every time an fseek was done relative to the beginning of the file
e
s 00002/00002/00097
d D 5.2 86/03/09 19:51:37 donn 10 9
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00090
d D 5.1 85/05/30 10:46:42 dist 9 8
c Add copyright
e
s 00001/00001/00090
d D 4.7 85/01/22 16:52:32 ralph 8 7
c return -1 not NULL.
e
s 00001/00001/00090
d D 4.6 84/07/06 09:58:06 ralph 7 6
c return the number of symbols not found
e
s 00025/00015/00066
d D 4.5 84/07/05 17:01:02 ralph 6 5
c keep two open files to avoid seeks (from Robert Elz).
e
s 00001/00001/00080
d D 4.4 83/10/17 10:32:26 ralph 5 4
c close() fixed to fclose().
e
s 00000/00001/00081
d D 4.3 83/06/10 22:43:02 sam 4 3
c purge pagsiz.h
e
s 00001/00001/00081
d D 4.2 83/01/02 16:10:58 sam 3 1
c null pointer bug
e
s 00002/00001/00081
d R 4.2 81/07/03 23:38:26 root 2 1
c return only externals
e
s 00082/00000/00000
d D 4.1 80/12/21 16:39:57 wnj 1 0
c date and time created 80/12/21 16:39:57 by wnj
e
u
U
t
T
I 1
D 9
/* %W% (Berkeley) %G% */
E 9
I 9
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 20
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 15
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 11
 */

D 10
#ifndef lint
E 10
I 10
#if defined(LIBC_SCCS) && !defined(lint)
E 10
static char sccsid[] = "%W% (Berkeley) %G%";
D 10
#endif not lint
E 10
I 10
D 11
#endif LIBC_SCCS and not lint
E 11
I 11
#endif /* LIBC_SCCS and not lint */
E 11
E 10
E 9
I 6

E 6
D 17
#include <sys/types.h>
E 17
I 17
#include <sys/param.h>
#include <sys/mman.h>
#include <sys/stat.h>
E 17
I 11
#include <sys/file.h>
I 19

#include <errno.h>
E 19
E 11
D 4
#include <pagsiz.h>
E 4
#include <a.out.h>
#include <stdio.h>
I 16
#include <string.h>
E 16
I 11
#include <unistd.h>
E 11

D 11
/*
 * nlist - retreive attributes from name list (string table version)
 */
E 11
I 11
D 17
typedef struct nlist NLIST;
#define	_strx	n_un.n_strx
#define	_name	n_un.n_name
#define	ISVALID(p)	(p->_name && p->_name[0])

E 17
I 16
int
E 16
E 11
nlist(name, list)
D 16
	char *name;
E 16
I 16
	const char *name;
E 16
D 11
	struct nlist *list;
E 11
I 11
D 17
	NLIST *list;
E 17
I 17
	struct nlist *list;
E 17
E 11
{
D 11
	register struct nlist *p, *q;
D 6
	register n, m, i, nreq;
E 6
I 6
	register char *s1, *s2;
	register n, m;
	int maxlen, nreq;
E 6
	FILE *f;
I 6
	FILE *sf;
E 6
	off_t sa;		/* symbol address */
	off_t ss;		/* start of strings */
	struct exec buf;
	struct nlist space[BUFSIZ/sizeof (struct nlist)];
E 11
I 11
D 17
	register NLIST *p, *s;
	struct exec ebuf;
	FILE *fstr, *fsym;
	NLIST nbuf;
D 12
	off_t curoff, strings_offset, symbol_offset, symbol_size, lseek();
E 12
I 12
	off_t strings_offset, symbol_offset, symbol_size, lseek();
E 12
	int entries, len, maxlen;
	char sbuf[256];
E 17
I 17
	int fd, n;
E 17
E 11
D 6
	int maxlen;
E 6

D 11
	maxlen = 0;
	for (q = list, nreq = 0; q->n_un.n_name && q->n_un.n_name[0]; q++, nreq++) {
		q->n_type = 0;
		q->n_value = 0;
		q->n_desc = 0;
		q->n_other = 0;
D 6
		i = strlen(q->n_un.n_name);
		if (i > maxlen)
			maxlen = i;
E 6
I 6
		n = strlen(q->n_un.n_name);
		if (n > maxlen)
			maxlen = n;
E 6
	}
	f = fopen(name, "r");
	if (f == NULL)
D 8
		return (NULL);
E 8
I 8
		return (-1);
E 8
	fread((char *)&buf, sizeof buf, 1, f);
	if (N_BADMAG(buf)) {
D 5
		close(f);
E 5
I 5
		fclose(f);
E 5
		return (-1);
	}
I 6
	sf = fopen(name, "r");
	if (sf == NULL) {
		/* ??? */
		fclose(f);
E 11
I 11
D 17
	entries = -1;
E 17
I 17
	fd = open(name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
D 18
	n = _fdnlist(fd, list);
E 18
I 18
	n = __fdnlist(fd, list);
E 18
	(void)close(fd);
	return (n);
}
E 17

D 17
	if (!(fsym = fopen(name, "r")))
E 11
		return(-1);
I 11
	if (fread((char *)&ebuf, sizeof(struct exec), 1, fsym) != 1 ||
	    N_BADMAG(ebuf))
		goto done1;
E 17
I 17
#define	ISLAST(p)	(p->n_un.n_name == 0 || p->n_un.n_name[0] == 0)
E 17

D 17
	symbol_offset = N_SYMOFF(ebuf);
	symbol_size = ebuf.a_syms;
	strings_offset = symbol_offset + symbol_size;
	if (fseek(fsym, symbol_offset, SEEK_SET))
		goto done1;
E 17
I 17
int
__fdnlist(fd, list)
	register int fd;
	register struct nlist *list;
{
	register struct nlist *p, *s;
	register caddr_t strtab;
	register off_t stroff, symoff;
	register u_long symsize;
D 19
	register int nent, strsize, cc;
E 19
I 19
	register int nent, cc;
	size_t strsize;
E 19
	struct nlist nbuf[1024];
	struct exec exec;
	struct stat st;
E 17

D 12
	/*
	 * some versions of stdio do lseek's on every fseek call relative
	 * to the beginning of the file.  For this reason, all string seeks
	 * are made relative to the beginning of the symbol table.
	 */
	curoff = 0;
E 12
D 17
	if (!(fstr = fopen(name, "r")))
		goto done1;
E 17
I 17
	if (lseek(fd, (off_t)0, SEEK_SET) == -1 ||
	    read(fd, &exec, sizeof(exec)) != sizeof(exec) ||
	    N_BADMAG(exec) || fstat(fd, &st) < 0)
		return (-1);
E 17
D 12
	if (fseek(fstr, strings_offset, SEEK_SET))
		goto done2;
E 12

I 17
	symoff = N_SYMOFF(exec);
	symsize = exec.a_syms;
	stroff = symoff + symsize;
D 19
	strsize = st.st_size - stroff;
E 19
I 19

	/* Check for files too large to mmap. */
	if (st.st_size - stroff > SIZE_T_MAX) {
		errno = EFBIG;
		return (-1);
	}
E 19
E 17
	/*
I 17
	 * Map string table into our address space.  This gives us
	 * an easy way to randomly access all the strings, without
	 * making the memory allocation permanent as with malloc/free
	 * (i.e., munmap will return it to the system).
	 */
D 19
	strtab = mmap(0, strsize, PROT_READ, MAP_FILE, fd, stroff);
E 19
I 19
	strsize = st.st_size - stroff;
	strtab = mmap(NULL, (size_t)strsize, PROT_READ, 0, fd, stroff);
E 19
	if (strtab == (char *)-1)
		return (-1);
	/*
E 17
	 * clean out any left-over information for all valid entries.
	 * Type and value defined to be 0 if not found; historical
	 * versions cleared other and desc as well.  Also figure out
	 * the largest string length so don't read any more of the
	 * string table than we have to.
I 17
	 *
	 * XXX clearing anything other than n_type and n_value violates
	 * the semantics given in the man page.
E 17
	 */
D 17
	for (p = list, entries = maxlen = 0; ISVALID(p); ++p, ++entries) {
E 17
I 17
	nent = 0;
	for (p = list; !ISLAST(p); ++p) {
E 17
		p->n_type = 0;
		p->n_other = 0;
		p->n_desc = 0;
		p->n_value = 0;
D 17
		if ((len = strlen(p->_name)) > maxlen)
			maxlen = len;
E 17
I 17
		++nent;
E 17
E 11
	}
E 6
D 11
	sa = N_SYMOFF(buf);
	ss = sa + buf.a_syms;
	n = buf.a_syms;
I 6
	fseek(f, sa, 0);
E 6
	while (n) {
		m = sizeof (space);
		if (n < m)
			m = n;
D 6
		fseek(f, sa, 0);
		i = fread((char *)space, m, 1, f);
		sa += m;
E 6
I 6
		if (fread((char *)space, m, 1, f) != 1)
			break;
E 6
		n -= m;
		for (q = space; (m -= sizeof(struct nlist)) >= 0; q++) {
			char nambuf[BUFSIZ];
E 11
I 11
D 17
	if (++maxlen > sizeof(sbuf)) {		/* for the NULL */
		(void)fprintf(stderr, "nlist: symbol too large.\n");
		entries = -1;
		goto done2;
	}
E 17
I 17
	if (lseek(fd, symoff, SEEK_SET) == -1)
		return (-1);
E 17
E 11

D 11
			if (q->n_un.n_strx == 0 || q->n_type & N_STAB)
				continue;
D 6
			fseek(f, ss+q->n_un.n_strx, 0);
			fread(nambuf, maxlen+1, 1, f);
E 6
I 6
			fseek(sf, ss+q->n_un.n_strx, 0);
			fread(nambuf, maxlen+1, 1, sf);
E 6
D 3
			for (p = list; p->n_un.n_name[0]; p++) {
E 3
I 3
			for (p = list; p->n_un.n_name && p->n_un.n_name[0]; p++) {
E 3
D 6
				i = 0;
				while (p->n_un.n_name[i]) {
					if (p->n_un.n_name[i] != nambuf[i])
E 6
I 6
				s1 = p->n_un.n_name;
				s2 = nambuf;
				while (*s1) {
					if (*s1++ != *s2++)
E 6
						goto cont;
D 6
					i++;
E 6
				}
D 6
				if (nambuf[i])
E 6
I 6
				if (*s2)
E 6
					goto cont;
				p->n_value = q->n_value;
				p->n_type = q->n_type;
				p->n_desc = q->n_desc;
				p->n_other = q->n_other;
				if (--nreq == 0)
					goto alldone;
				break;
		cont:		;
E 11
I 11
D 13
	for (s = &nbuf; symbol_size--;) {
E 13
I 13
D 14
	for (s = &nbuf; symbol_size -= sizeof(NLIST);) {
E 14
I 14
D 17
	for (s = &nbuf; symbol_size; symbol_size -= sizeof(NLIST)) {
E 14
E 13
		if (fread((char *)s, sizeof(NLIST), 1, fsym) != 1)
			goto done2;
		if (!s->_strx || s->n_type&N_STAB)
			continue;
D 12
		if (fseek(fstr, s->_strx - curoff, SEEK_CUR))
E 12
I 12
		if (fseek(fstr, strings_offset + s->_strx, SEEK_SET))
E 12
			goto done2;
D 12
		curoff = s->_strx +
		    fread(sbuf, sizeof(sbuf[0]), maxlen, fstr);
E 12
I 12
		(void)fread(sbuf, sizeof(sbuf[0]), maxlen, fstr);
E 12
		for (p = list; ISVALID(p); p++)
			if (!strcmp(p->_name, sbuf)) {
				p->n_value = s->n_value;
				p->n_type = s->n_type;
				p->n_desc = s->n_desc;
				p->n_other = s->n_other;
				if (!--entries)
					goto done2;
E 11
			}
E 17
I 17
	while (symsize > 0) {
		cc = MIN(symsize, sizeof(nbuf));
		if (read(fd, nbuf, cc) != cc)
			break;
		symsize -= cc;
		for (s = nbuf; cc > 0; ++s, cc -= sizeof(*s)) {
			register int soff = s->n_un.n_strx;

			if (soff == 0 || (s->n_type & N_STAB) != 0)
				continue;
			for (p = list; !ISLAST(p); p++)
				if (!strcmp(&strtab[soff], p->n_un.n_name)) {
					p->n_value = s->n_value;
					p->n_type = s->n_type;
					p->n_desc = s->n_desc;
					p->n_other = s->n_other;
					if (--nent <= 0)
						break;
				}
		}
E 17
D 11
		}
E 11
	}
D 11
alldone:
	fclose(f);
I 6
	fclose(sf);
E 6
D 7
	return (0);
E 7
I 7
	return (nreq);
E 11
I 11
D 17
done2:	(void)fclose(fstr);
done1:	(void)fclose(fsym);
	return(entries);
E 17
I 17
	munmap(strtab, strsize);
	return (nent);
E 17
E 11
E 7
}
E 1
