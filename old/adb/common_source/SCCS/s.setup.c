h27350
s 00008/00001/00158
d D 5.5 91/04/04 18:01:59 bostic 5 4
c new copyright; att/bsd/shared
e
s 00000/00001/00159
d D 5.4 91/01/14 17:02:20 bostic 4 3
c kernel reorg -- not needed anyway
e
s 00001/00001/00159
d D 5.3 90/06/25 09:58:09 mckusick 3 2
c u_sig now has its own entry
e
s 00001/00000/00159
d D 5.2 90/02/23 11:16:33 marc 2 1
c include machparam.h to get KERNTEXTOFF
e
s 00159/00000/00000
d D 5.1 89/01/16 20:24:48 bostic 1 0
c new version from Chris Torek
e
u
U
t
T
I 5
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
#endif /* not lint */
E 5

/*
 * adb - routines to read a.out and core files at startup
 */

#include "defs.h"
#include <sys/file.h>
I 2
D 4
#include <machine/machparam.h>
E 4
E 2

static struct exec filhdr;

off_t	lseek();
char	*malloc();

/* NB. the following works only with letter (alpha) variables */
#define	setavar(name, value) (var[(name) - 'a' + 10] = (value))

setsym()
{
	register struct nlist *sp;
	int strsize;
	char *strtab;
	off_t loc, dbase;

	txtmap.ufd = symfile.fd = getfile(1);
	if (read(symfile.fd, (char *)&filhdr, sizeof(filhdr)) != sizeof(filhdr) ||
	    N_BADMAG(filhdr)) {
		bzero((char *)&filhdr, sizeof(filhdr));
		txtmap.m1.e = -(addr_t)1;
		return;
	}
	loc = filhdr.a_text + filhdr.a_data;
	txtmap.m1.f = txtmap.m2.f = N_TXTOFF(filhdr);
	switch ((int)filhdr.a_magic) {

	case OMAGIC:
		/* text map 1 is empty; map 2 goes from 0 to loc */
		txtmap.m2.b = dbase = 0;
		txtmap.m2.e = loc;
		break;

	case ZMAGIC:
	case NMAGIC:
		/* text map 1 maps text segment, map 2 maps data */
		txtmap.m1.e = filhdr.a_text;
		txtmap.m2.b = dbase = roundup(filhdr.a_text, CLBYTES);
		txtmap.m2.e = dbase + filhdr.a_data;
		txtmap.m2.f += txtmap.m1.e;
		break;
	}

	/* save data segment base in variable b */
	setavar('b', dbase);

	if (filhdr.a_syms != 0) {
		loc = N_SYMOFF(filhdr);
		symtab = (struct nlist *)malloc((u_int)filhdr.a_syms);
		if (symtab == NULL)
			goto nospace;
		esymtab = &symtab[filhdr.a_syms / sizeof(struct nlist)];
		(void) lseek(symfile.fd, loc, L_SET);

#define	rd(a, n) \
	if (read(symfile.fd, (char *)(a), (int)(n)) != (n)) \
		goto readerr

		rd(symtab, filhdr.a_syms);
		rd(&strsize, sizeof(strsize));
		/*
		 * offsets in the string table are relative to the offset
		 * of the number we just read; we adjust for it here.
		 */
		strsize -= sizeof(strsize);
		if ((strtab = malloc((u_int)strsize)) == NULL)
			goto nospace;
		rd(strtab, strsize);
		for (sp = symtab; sp < esymtab; sp++) {
			if (sp->n_un.n_strx == 0)
				continue;
			sp->n_un.n_strx -= sizeof(strsize);
			if ((u_long)sp->n_un.n_strx >= strsize) {
				adbprintf("bad string index %D in symtab\n",
				    (expr_t)sp->n_un.n_strx);
				sp->n_un.n_name = "";
			} else
				sp->n_un.n_name = strtab + sp->n_un.n_strx;
		}
#undef rd
	}
	if (INKERNEL(filhdr.a_entry)) {
		txtmap.m1.b += KERNTEXTOFF;
		txtmap.m1.e += KERNTEXTOFF;
		txtmap.m2.b += KERNTEXTOFF;
		txtmap.m2.e += KERNTEXTOFF;
	}
	return;

readerr:
	prints("Error reading symbol|string table (old format a.out?)\n");
	exit(1);
	/* NOTREACHED */

nospace:
	prints("Not enough space for symbol|string table\n");
	exit(1);
	/* NOTREACHED */
}

setcore()
{
	off_t stacksize;

	datmap.m1.e = -(addr_t)1;
	if ((datmap.ufd = corefile.fd = getfile(2)) < 0)
		goto ret;
	if (kernel && INKERNEL(filhdr.a_entry) && getkcore()) {
		kcore = 1;
		goto ret;
	}
	if (read(corefile.fd, (char *)&u, ctob(UPAGES)) != ctob(UPAGES) ||
	    !udot()) {
		adbprintf("not core file = %s\n", corefile.name);
		goto ret;
	}
D 3
	signo = u.u_arg[0];
E 3
I 3
	signo = u.u_sig;
E 3
	sigcode = u.u_code;
	filhdr.a_text = ctob(u.u_tsize);
	filhdr.a_data = ctob(u.u_dsize);
	stacksize = ctob(u.u_ssize);
	switch ((int)filhdr.a_magic) {

	case OMAGIC:
		datmap.m1.b = 0;
		datmap.m1.e = filhdr.a_text + filhdr.a_data;
		datmap.m2.f = ctob(UPAGES) + datmap.m1.e;
		break;

	case NMAGIC:
	case ZMAGIC:
		datmap.m1.b = roundup(filhdr.a_text, CLBYTES);
		datmap.m1.e = datmap.m1.b + filhdr.a_data;
		datmap.m2.f = ctob(UPAGES) + filhdr.a_data;
		break;
	}
	/* save (possibly new) data segment base, and save stack size */
	setavar('b', datmap.m1.b);
	setavar('s', stacksize);
	datmap.m1.f = ctob(UPAGES);
	datmap.m2.b = KERNBASE - ctob(UPAGES) - stacksize;
	datmap.m2.e = KERNBASE - ctob(UPAGES);
ret:
	u.u_ar0 = (int *)((caddr_t)&u + ctob(UPAGES));	/* XXX */
	setavar('d', filhdr.a_data);
	setavar('e', filhdr.a_entry);
	setavar('m', filhdr.a_magic);
	setavar('t', filhdr.a_text);
}
E 1
