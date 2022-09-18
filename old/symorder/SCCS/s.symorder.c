h48437
s 00039/00024/00216
d D 5.8 91/04/01 08:32:33 bostic 15 14
c change -T to -t; use getopt(3); wordsmith the man page
c put -t/-T man page changes on an SCCS delta
e
s 00022/00003/00218
d D 5.7 91/03/29 15:34:39 william 14 13
c added -T option to trim symbol table to orderlist symbols
e
s 00010/00005/00211
d D 5.6 91/02/04 16:00:33 bostic 13 12
c exit 0 on success, 1 on symbols not found, 2 on error
e
s 00116/00153/00099
d D 5.5 91/02/01 22:08:34 bostic 12 11
c didn't handle empty lines, and when a symbol was missing, it fucked
c up the symbol table.  Lots of lint, lots of cleanup, lots of pretty bad code.
c (Lots of work for something that should go away...)
e
s 00001/00011/00251
d D 5.4 90/06/01 16:11:31 bostic 11 10
c new copyright notice
e
s 00017/00006/00245
d D 5.3 88/11/01 20:47:45 bostic 10 9
c written by Bill Joy; use Berkeley copyright notice
e
s 00007/00002/00244
d D 5.2 85/07/02 21:31:27 mckusick 9 8
c must calculate actual length (from chris@maryland)
e
s 00014/00002/00232
d D 5.1 85/05/31 09:34:16 dist 8 7
c Add copyright
e
s 00140/00057/00094
d D 4.5 84/07/05 16:47:24 ralph 7 6
c changes from Robert Elz to reorder the string table too.
e
s 00001/00001/00150
d D 4.4 83/07/02 00:55:44 sam 6 5
c include fixes
e
s 00002/00001/00149
d D 4.3 83/05/22 18:40:47 sam 5 4
c purge pagsiz.h
e
s 00001/00001/00149
d D 4.2 80/10/02 10:59:22 bill 4 3
c botched sccsid line.
e
s 00000/00000/00150
d D 4.1 80/10/01 16:40:04 bill 3 2
c Define 4.1
e
s 00002/00002/00148
d D 3.2 80/10/01 16:28:41 bill 2 1
c change reference to new a.out format.
e
s 00150/00000/00000
d D 3.1 80/08/15 01:55:22 bill 1 0
c date and time created 80/08/15 01:55:22 by bill
e
u
U
t
T
I 8
/*
D 10
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 10
 */

E 8
I 5
#ifndef lint
E 5
I 1
D 2
static	char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
D 4
static char *sccsid = "%W% (Berkeley) %G%;
E 4
I 4
D 8
static char *sccsid = "%W% (Berkeley) %G%";
I 5
#endif
E 8
I 8
char copyright[] =
D 10
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 10
I 10
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 10
 All rights reserved.\n";
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10
E 8
I 7

E 7
E 5
E 4
E 2
/*
 * symorder - reorder symbol table
 */
I 7

E 7
D 12
#include <stdio.h>
E 12
D 5
#include <pagsiz.h>
E 5
#include <sys/types.h>
D 6
#include <stat.h>
E 6
I 6
#include <sys/stat.h>
I 12
#include <fcntl.h>
#include <errno.h>
E 12
E 6
D 2
#include <newa.out.h>
E 2
I 2
#include <a.out.h>
I 12
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 12
E 2

D 12
#define SPACE 100
E 12
I 12
D 13
#define SPACE 500
E 13
I 13
#define SPACE		500
E 13
E 12

I 13
#define	OKEXIT		0
#define	NOTFOUNDEXIT	1
#define	ERREXIT		2

E 13
struct	nlist order[SPACE];

D 7
char	*savestr();
struct	nlist nl1, nl2;
E 7
I 7
D 12
char	*savestr(), *index(), *malloc();
E 12
E 7
struct	exec exec;
D 7
FILE	*strf;
off_t	sa, ss;
E 7
I 7
D 12
off_t	sa;
E 12
E 7
struct	stat stb;
D 12
int	nsym = 0;
int	symfound = 0;
I 7
char	*strings;
char	*newstrings;
struct	nlist *symtab;
struct	nlist *newtab;
int	symsize;
E 7
char	asym[BUFSIZ];
E 12
I 12
struct	nlist *newtab, *symtab;
off_t	sa;
D 14
int	nsym, strtabsize, symfound; 
E 14
I 14
int	nsym, strtabsize, symfound, small; 
E 14
char	*kfile, *newstrings, *strings, asym[BUFSIZ];
E 12

main(argc, argv)
I 12
	int argc;
E 12
	char **argv;
{
I 15
	extern char *optarg;
	extern int optind;
E 15
D 7
	register struct nlist *p, *q;
E 7
I 7
D 12
	register char *ns;
	register struct nlist *symp;
	register struct nlist *p;
E 12
I 12
	register struct nlist *p, *symp;
E 12
E 7
	register FILE *f;
D 7
	register int na, i, j;
	int maxlen;
E 7
I 7
	register int i;
I 12
	register char *start, *t;
E 12
E 7
D 15
	int n, o;
E 15
I 15
	int ch, n, o;
E 15

D 7
	if(argc != 3) {
E 7
I 7
D 14
	if (argc != 3) {
E 7
D 12
		fprintf(stderr, "Usage: symorder orderlist file\n");
E 12
I 12
		(void)fprintf(stderr, "usage: symorder orderlist file\n");
E 14
I 14
D 15
	if (argc != 3 && argc != 4) {
		(void)fprintf(stderr, "usage: symorder [-T] orderlist file\n");
E 14
E 12
D 13
		exit(1);
E 13
I 13
		exit(ERREXIT);
E 13
	}
I 14
	if (argc == 4 && strcmp(argv[1],"-T") == 0) {
		argv++;
		small++;
	}
E 14
D 7
	if((f = fopen(argv[1], "r")) == NULL) {
E 7
I 7
D 12
	if ((f = fopen(argv[1], "r")) == NULL) {
E 7
		perror(argv[1]);
		exit(1);
	}
D 7
	maxlen = 0;
	for(p = order; fgets(asym, sizeof asym, f) != NULL; p++, nsym++) {
		for(i = 0; asym[i] && asym[i] != '\n'; i++)
E 7
I 7
	for (p = order; fgets(asym, sizeof asym, f) != NULL; p++, nsym++) {
		for (i = 0; asym[i] && asym[i] != '\n'; i++)
E 12
I 12
	if ((f = fopen(argv[1], "r")) == NULL)
		error(argv[1]);
E 15
I 15
	while ((ch = getopt(argc, argv, "t")) != EOF)
		switch(ch) {
		case 't':
			small = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
E 15

I 15
	if (argc != 2)
		usage();

	if ((f = fopen(argv[0], "r")) == NULL)
		error(argv[0]);

E 15
	for (p = order; fgets(asym, sizeof(asym), f) != NULL;) {
		for (t = asym; isspace(*t); ++t);
		if (!*(start = t))
E 12
E 7
			continue;
D 12
		if (asym[i] == '\n')
			asym[i] = 0;
		p->n_un.n_name = savestr(asym);
E 12
I 12
		while (*++t);
		if (*--t == '\n')
			*t = '\0';
		p->n_un.n_name = strdup(start);
		++p;
		++nsym;
E 12
D 7
		if (maxlen < strlen(p->n_un.n_name))
			maxlen = strlen(p->n_un.n_name);
E 7
	}
D 12
	fclose(f);
D 7
	if((f = fopen(argv[2], "r")) == NULL)
E 7
I 7
	if ((f = fopen(argv[2], "r")) == NULL)
E 7
		perror(argv[2]), exit(1);
D 7
	if((strf = fopen(argv[2], "r")) == NULL)
E 7
I 7
	if ((o = open(argv[2], 1)) < 0)
E 7
		perror(argv[2]), exit(1);
D 7
	if((o = open(argv[2], 1)) < 0)
		perror(argv[2]), exit(1);
	if((fread(&exec, sizeof exec, 1, f)) != 1 || N_BADMAG(exec)) {
E 7
I 7
	if ((fread(&exec, sizeof exec, 1, f)) != 1 || N_BADMAG(exec)) {
E 7
		fprintf(stderr, "symorder: %s: bad format\n", argv[2]);
		exit(1);
	}
	if (exec.a_syms == 0) {
		fprintf(stderr, "symorder: %s is stripped\n", argv[2]);
		exit(1);
	}
	fstat(fileno(f), &stb);
	if (stb.st_size < N_STROFF(exec)+sizeof(off_t)) {
D 7
		fprintf(stderr, "symorder: %s is in old format or truncated\n", argv[2]);
E 7
I 7
		fprintf(stderr, "symorder: %s is in old format or truncated\n",
		    argv[2]);
E 7
		exit(1);
	}
E 12
I 12
	(void)fclose(f);

D 15
	kfile = argv[2];
E 15
I 15
	kfile = argv[1];
E 15
	if ((f = fopen(kfile, "r")) == NULL)
		error(kfile);
	if ((o = open(kfile, O_WRONLY)) < 0)
		error(kfile);

	/* read exec header */
	if ((fread(&exec, sizeof(exec), 1, f)) != 1)
		badfmt("no exec header");
	if (N_BADMAG(exec))
		badfmt("bad magic number");
	if (exec.a_syms == 0)
		badfmt("stripped");
	(void)fstat(fileno(f), &stb);
	if (stb.st_size < N_STROFF(exec) + sizeof(off_t))
		badfmt("no string table");

	/* seek to and read the symbol table */
E 12
	sa = N_SYMOFF(exec);
D 7
	na = sa;
	ss = sa + exec.a_syms;
E 7
D 12
	fseek(f, sa, 0);
E 12
I 12
	(void)fseek(f, sa, SEEK_SET);
E 12
	n = exec.a_syms;
D 7
	while(n && symfound < nsym) {
		if(fread(&nl1, sizeof nl1, 1, f) != 1) {
			fprintf(stderr, "Short file "); perror(argv[2]);
E 7
I 7
D 12
	symtab = (struct nlist *)malloc(n);
	if (symtab == (struct nlist *)0) {
		fprintf(stderr, "symorder: Out of core, no space for symtab\n");
		exit(1);
	}
	if (fread((char *)symtab, 1, n, f) != n) {
		fprintf(stderr, "symorder: Short file "); perror(argv[2]);
		exit(1);
	}
	if (fread((char *)&symsize, sizeof (int), 1, f) != 1 ||
	    symsize <= 0) {
		fprintf(stderr, "symorder: No strings "); perror(argv[2]);
		exit(1);
	}
	strings = malloc(symsize);
	if (strings == (char *)0) {
		fprintf(stderr,"symorder: Out of core, no space for strings\n");
		exit(1);
	}
E 12
I 12
	if (!(symtab = (struct nlist *)malloc(n)))
D 15
		error((char *)NULL);
	if (fread((char *)symtab, 1, n, f) != n)
E 15
I 15
		error(NULL);
	if (fread((void *)symtab, 1, n, f) != n)
E 15
		badfmt("corrupted symbol table");

	/* read string table size and string table */
D 15
	if (fread((char *)&strtabsize, sizeof(int), 1, f) != 1 ||
E 15
I 15
	if (fread((void *)&strtabsize, sizeof(int), 1, f) != 1 ||
E 15
	    strtabsize <= 0)
		badfmt("corrupted string table");
	strings = malloc(strtabsize);
D 15
	if (strings == (char *)NULL)
		error((char *)NULL);
E 15
I 15
	if (strings == NULL)
		error(NULL);
E 15
E 12
D 9
	if (fread(strings, 1, symsize, f) != symsize) {
E 9
I 9
	/*
D 12
	 * Need to subtract four from symsize here since
	 * symsize includes itself, and we've already read
	 * it.  (6/30/85 chris@maryland)
E 12
I 12
	 * Subtract four from strtabsize since strtabsize includes itself,
	 * and we've already read it.
E 12
	 */
D 12
	if (fread(strings, 1, symsize - 4, f) != symsize - 4) {
E 9
		fprintf(stderr, "symorder: Truncated strings "); 
		perror(argv[2]);
		exit(1);
	}
E 12
I 12
	if (fread(strings, 1, strtabsize - sizeof(int), f) !=
	    strtabsize - sizeof(int))
		badfmt("corrupted string table");
E 12

	newtab = (struct nlist *)malloc(n);
D 12
	if (newtab == (struct nlist *)0) {
		fprintf(stderr,
		    "symorder: Out of core, no space for new symtab\n");
		exit(1);
	}
	i = n / sizeof (struct nlist);
E 12
I 12
	if (newtab == (struct nlist *)NULL)
D 15
		error((char *)NULL);
E 15
I 15
		error(NULL);
E 15

	i = n / sizeof(struct nlist);
E 12
	reorder(symtab, newtab, i);
D 15
	free((char *)symtab);
E 15
I 15
	free((void *)symtab);
E 15
	symtab = newtab;

D 12
	newstrings = malloc(symsize);
	if (newstrings == (char *)0) {
		fprintf(stderr,
		    "symorder: Out of core, no space for newstrings\n");
		exit(1);
	}
	ns = newstrings;
E 12
I 12
	newstrings = malloc(strtabsize);
D 15
	if (newstrings == (char *)NULL)
		error((char *)NULL);
E 15
I 15
	if (newstrings == NULL)
		error(NULL);
E 15
	t = newstrings;
E 12
	for (symp = symtab; --i >= 0; symp++) {
		if (symp->n_un.n_strx == 0)
			continue;
I 14
		if (small && inlist(symp) < 0) continue;
E 14
D 12
		symp->n_un.n_strx -= sizeof (int);
		if ((unsigned)symp->n_un.n_strx >= symsize) {
			fprintf(stderr,"symorder: Corrupted string pointers\n");
E 7
			exit(1);
		}
D 7
		na += sizeof nl1;
		n -= sizeof nl1;
		if (nl1.n_un.n_strx == 0 || nl1.n_type & N_STAB)
			continue;
		fseek(strf, ss+nl1.n_un.n_strx, 0);
		fread(asym, maxlen+1, 1, strf);
		for(j = 0; j < nsym; j++) {
			for(i = 0; asym[i]; i++)
				if(asym[i] != order[j].n_un.n_name[i])
					goto cont;
			if (order[j].n_un.n_name[i])
				goto cont;
			if (order[j].n_value)
				goto cont;
			order[j].n_value = 1;
			fseek(f, (i = (sa+(j * sizeof nl1))), 0);
			if(fread(&nl2, sizeof nl2, 1, f) != 1)
				printf("Read err on 2nd asym\n");
			lseek(o, i, 0);
			if(write(o, &nl1, sizeof nl1) == -1)
				perror("write1");
			lseek(o, na-sizeof nl1, 0);
			if(write(o, &nl2, sizeof nl2) == -1)
				perror("write2");
			fseek(f, 0, 0);
			fseek(f, na, 0);
			symfound++;
			break;
	cont:           ;

E 7
I 7
		strcpy(ns, &strings[symp->n_un.n_strx]);
		symp->n_un.n_strx = (ns - newstrings) + sizeof (int);
		ns = index(ns, 0) + 1;
		if (ns > &newstrings[symsize]) {
			fprintf(stderr, "symorder: Strings grew longer!\n");
			exit(1);
E 7
		}
E 12
I 12
		symp->n_un.n_strx -= sizeof(int);
		(void)strcpy(t, &strings[symp->n_un.n_strx]);
		symp->n_un.n_strx = (t - newstrings) + sizeof(int);
		t += strlen(t) + 1;
E 12
	}
D 7
	if(symfound < nsym) {
		fprintf(stderr, "%d symbol(s) not found:\n", nsym - symfound);
E 7
I 7

I 14
	/* update shrunk sizes */
	if(small) {
		strtabsize = t - newstrings + sizeof(int);
		n = symfound * sizeof(struct nlist);
		/* fix exec sym size */
		(void)lseek(o, 0, SEEK_SET);
		exec.a_syms = n;
D 15
		if (write(o, (char *)&exec, sizeof(exec)) != sizeof(exec))
E 15
I 15
		if (write(o, (void *)&exec, sizeof(exec)) != sizeof(exec))
E 15
			error(kfile);
	}

E 14
D 12
	lseek(o, sa, 0);
	if (write(o, (char *)symtab, n) != n) {
		fprintf(stderr, "symorder: Write failed "); perror(argv[2]);
		exit(1);
	}
	if (write(o, (char *)&symsize, sizeof (int)) != sizeof (int)) {
		fprintf(stderr, "symorder: Write failed "); perror(argv[2]);
		exit(1);
	}
D 9
	if (write(o, newstrings, symsize) != symsize) {
E 9
I 9
	if (write(o, newstrings, symsize - 4) != symsize - 4) {
E 9
		fprintf(stderr, "symorder: Write failed "); perror(argv[2]);
		exit(1);
	}
E 12
I 12
	(void)lseek(o, sa, SEEK_SET);
D 15
	if (write(o, (char *)symtab, n) != n)
E 15
I 15
	if (write(o, (void *)symtab, n) != n)
E 15
		error(kfile);
D 15
	if (write(o, (char *)&strtabsize, sizeof(int)) != sizeof(int)) 
E 15
I 15
	if (write(o, (void *)&strtabsize, sizeof(int)) != sizeof(int)) 
E 15
		error(kfile);
	if (write(o, newstrings, strtabsize - sizeof(int)) !=
	    strtabsize - sizeof(int))
		error(kfile);
I 14

	if (small) ftruncate(o, lseek(o, 0, SEEK_CUR));

E 14
E 12
	if ((i = nsym - symfound) > 0) {
D 12
		fprintf(stderr, "symorder: %d symbol%s not found:\n",
E 12
I 12
		(void)printf("symorder: %d symbol%s not found:\n",
E 12
		    i, i == 1 ? "" : "s");
E 7
D 12
		for (i = 0; i < nsym; i++) {
E 12
I 12
		for (i = 0; i < nsym; i++)
E 12
			if (order[i].n_value == 0)
				printf("%s\n", order[i].n_un.n_name);
I 13
		exit(NOTFOUNDEXIT);
E 13
D 12
		}
E 12
	}
I 7
D 13
	exit(0);
E 13
I 13
	exit(OKEXIT);
E 13
}

D 12
reorder(st1, st2, n)
E 12
I 12
reorder(st1, st2, entries)
E 12
	register struct nlist *st1, *st2;
D 12
	register n;
E 12
I 12
	int entries;
E 12
{
D 12
	register struct nlist *stp = st2 + nsym;
	register i;
E 12
I 12
	register struct nlist *p;
	register int i, n;
E 12

D 12
	while (--n >= 0) {
E 12
I 12
	for (p = st1, n = entries; --n >= 0; ++p)
		if (inlist(p) != -1)
			++symfound; 
	for (p = st2 + symfound, n = entries; --n >= 0; ++st1) {
E 12
		i = inlist(st1);
		if (i == -1)
D 12
			*stp++ = *st1++;
E 12
I 12
			*p++ = *st1;
E 12
		else
D 12
			st2[i] = *st1++;
E 12
I 12
			st2[i] = *st1;
E 12
	}
}

inlist(p)
	register struct nlist *p;
{
	register char *nam;
	register struct nlist *op;

	if (p->n_type & N_STAB)
		return (-1);
	if (p->n_un.n_strx == 0)
		return (-1);

D 12
	nam = &strings[p->n_un.n_strx - sizeof(int)];
	if (nam >= &strings[symsize]) {
		fprintf(stderr, "symorder: corrupt symtab\n");
		exit(1);
	}
E 12
I 12
	if (p->n_un.n_strx >= strtabsize)
		badfmt("corrupted symbol table");
E 12

I 12
	nam = &strings[p->n_un.n_strx - sizeof(int)];
E 12
	for (op = &order[nsym]; --op >= order; ) {
		if (strcmp(op->n_un.n_name, nam) != 0)
			continue;
D 12
		if (op->n_value == 0) {
			op->n_value++;
			symfound++;
		}
E 12
I 12
		op->n_value = 1;
E 12
		return (op - order);
	}
	return (-1);
E 7
}

D 12
#define	NSAVETAB	4096
char	*savetab;
int	saveleft;
E 12
I 12
badfmt(why)
	char *why;
{
	(void)fprintf(stderr,
	    "symorder: %s: %s: %s\n", kfile, why, strerror(EFTYPE));
D 13
	exit(1);
E 13
I 13
	exit(ERREXIT);
E 13
}
E 12

D 12
char *
savestr(cp)
	register char *cp;
E 12
I 12
error(n)
	char *n;
E 12
{
D 12
	register int len;
E 12
I 12
	int sverr;
E 12

D 12
	len = strlen(cp) + 1;
	if (len > saveleft) {
		saveleft = NSAVETAB;
		if (len > saveleft)
			saveleft = len;
		savetab = (char *)malloc(saveleft);
		if (savetab == 0) {
			fprintf(stderr,
			    "symorder: ran out of memory (savestr)\n");
			exit(1);
		}
	}
	strncpy(savetab, cp, len);
	cp = savetab;
	savetab += len;
	saveleft -= len;
	return (cp);
E 12
I 12
	sverr = errno;
	(void)fprintf(stderr, "symorder: ");
	if (n)
		(void)fprintf(stderr, "%s: ", n);
	(void)fprintf(stderr, "%s\n", strerror(sverr));
I 15
	exit(ERREXIT);
}

usage()
{
	(void)fprintf(stderr, "usage: symorder [-t] symlist file\n");
E 15
D 13
	exit(1);
E 13
I 13
	exit(ERREXIT);
E 13
E 12
}
E 1
