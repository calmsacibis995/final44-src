h42355
s 00006/00004/00185
d D 8.2 94/05/24 17:16:38 mckusick 11 10
c type cast lseek calls
e
s 00002/00002/00187
d D 8.1 93/06/06 16:13:32 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00183
d D 5.2 91/04/16 16:05:14 bostic 9 8
c new copyright; att/bsd/shared
e
s 00007/00003/00181
d D 5.1 85/06/05 15:11:00 dist 8 7
c Add copyright
e
s 00000/00000/00184
d D 2.1 84/02/08 20:44:12 aoki 7 6
c synchronize to version 2
e
s 00000/00000/00184
d D 1.6 83/09/19 07:02:10 thien 6 5
c Restoring to unlinted version
e
s 00022/00016/00162
d D 1.5 83/08/19 05:04:35 thien 5 4
c The changes were made to allow successful linting
e
s 00002/00001/00176
d D 1.4 82/05/06 14:11:08 peter 4 3
c use of configuration stuff (a little late).
e
s 00017/00002/00160
d D 1.3 82/02/02 12:56:37 linton 3 2
c merge pdx into the Pascal system
e
s 00004/00004/00158
d D 1.2 81/03/08 19:30:11 mckusic 2 1
c merge in onyx changes
e
s 00162/00000/00000
d D 1.1 80/08/27 19:57:14 peter 1 0
c date and time created 80/08/27 19:57:14 by peter
e
u
U
t
T
I 1
D 8
/* Copyright (c) 1979 Regents of the University of California */
E 8
I 8
D 9
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
/*-
D 10
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
E 9
 */
E 8

I 5
#ifndef lint
E 5
D 2
static	char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
D 8
static char sccsid[] = "%Z%%M% %I% %G%";
I 5
#endif
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 8
E 5
E 2

#include "whoami.h"
#include "0.h"
I 5
#include "tree_ty.h"	/* must be included for yy.h */
E 5
#include "yy.h"
#include <a.out.h>
#include "objfmt.h"
#include <signal.h>
I 4
#include "config.h"
E 4

D 2
short	line = 1;

E 2
/*
 * Yymain initializes each of the utility
 * clusters and then starts the processing
 * by calling yyparse.
 */
yymain()
{

I 3
#ifdef OBJ
/*
 * initialize symbol table temp files
 */
	startnlfile();
#endif
E 3
	/*
	 * Initialize the scanner
	 */
#ifdef PXP
	if (bracket == 0) {
#endif
		if (getline() == -1) {
			Perror(filename, "No lines in file");
			pexit(NOSTART);
		}
#ifdef PXP
	} else
		yyline = 0;
#endif

#ifdef PI
#   ifdef OBJ
	magic();
#   endif OBJ
#endif
I 2
	line = 1;
	errpfx = 'E';
E 2
	/*
	 * Initialize the clusters
	 *
	initstring();
	 */
	inithash();
	inittree();
#ifdef PI
	initnl();
#endif

	/*
	 * Process the input
	 */
	yyparse();
#ifdef PI
#   ifdef OBJ
I 3

	/*
	 * save outermost block of namelist
	 */
D 5
	savenl(0);
E 5
I 5
	savenl(NLNIL);
E 5

E 3
	magic2();
#   endif OBJ
#   ifdef DEBUG
D 5
	dumpnl(0);
E 5
I 5
	dumpnl(NLNIL);
E 5
#   endif
#endif
I 3

E 3
#ifdef PXP
	prttab();
	if (onefile) {
		extern int outcol;

		if (outcol)
			pchr('\n');
		flush();
		if (eflg) {
			writef(2, "File not rewritten because of errors\n");
			pexit(ERRS);
		}
D 5
		signal(SIGHUP, SIG_IGN);
		signal(SIGINT, SIG_IGN);
E 5
I 5
		(void) signal(SIGHUP, SIG_IGN);
		(void) signal(SIGINT, SIG_IGN);
E 5
		copyfile();
	}
#endif
	pexit(eflg ? ERRS : AOK);
}

#ifdef PXP
copyfile()
{
	extern int fout[];
	register int c;

D 5
	close(1);
E 5
I 5
	(void) close(1);
E 5
	if (creat(firstname, 0644) != 1) {
		perror(firstname);
		pexit(ERRS);
	}
D 5
	lseek(fout[0], 0l, 0);
E 5
I 5
D 11
	(void) lseek(fout[0], 0l, 0);
E 11
I 11
	if (lseek(fout[0], (off_t)0, 0) == -1)
		perror("copyfile: lseek"), panic("copyfile");
E 11
E 5
	while ((c = read(fout[0], &fout[3], 512)) > 0) {
		if (write(1, &fout[3], c) != c) {
			perror(firstname);
			pexit(ERRS);
		}
	}
}
#endif

D 5
static
struct exec magichdr;
E 5

#ifdef PI
#ifdef OBJ
I 5

static
struct exec magichdr;

E 5
magic()
{

	short		buf[HEADER_BYTES / sizeof ( short )];
D 5
	unsigned	*ubuf = buf;
E 5
I 5
	unsigned	*ubuf = (unsigned *) buf;
E 5
	register int	hf, i;

D 4
	hf = open(PX_HEADER,0);
E 4
I 4
	hf = open(px_header,0);
E 4
D 5
	if (hf >= 0 && read(hf, buf, HEADER_BYTES) > sizeof(struct exec)) {
E 5
I 5
	if (hf >= 0 && read(hf, (char *) buf, HEADER_BYTES) > sizeof(struct exec)) {
E 5
		magichdr.a_magic = ubuf[0];
		magichdr.a_text = ubuf[1];
		magichdr.a_data = ubuf[2];
		magichdr.a_bss = ubuf[3];
		magichdr.a_syms = ubuf[4];
		magichdr.a_entry = ubuf[5];
		magichdr.a_trsize = ubuf[6];
		magichdr.a_drsize = ubuf[7];
		for (i = 0; i < HEADER_BYTES / sizeof ( short ); i++)
			word(buf[i]);
	}
D 5
	close(hf);
E 5
I 5
	(void) close(hf);
E 5
}
#endif OBJ

#ifdef OBJ
magic2()
{
	struct pxhdr pxhd;
I 5
D 11
	extern long lseek();
E 11
E 5

	if  (magichdr.a_magic != 0407)
		panic ( "magic2" );
	pflush();
D 3
	lseek(ofil, 0l, 0);
E 3
	magichdr.a_data = ( unsigned ) lc - magichdr.a_text;
	magichdr.a_data -= sizeof (struct exec);
D 3
	write(ofil, &magichdr, sizeof(struct exec));
E 3
	pxhd.objsize = ( ( unsigned ) lc) - HEADER_BYTES;
I 3
	pxhd.symtabsize = nlhdrsize();
	magichdr.a_data += pxhd.symtabsize;
E 3
D 2
	pxhd.maketime = time(0);
E 2
I 2
D 5
	time(&pxhd.maketime);
E 5
I 5
	(void) time((long *) (&pxhd.maketime));
E 5
E 2
	pxhd.magicnum = MAGICNUM;
I 3
D 5
	lseek(ofil, 0l, 0);
	write(ofil, &magichdr, sizeof(struct exec));
E 3
	lseek(ofil, ( long ) ( HEADER_BYTES - sizeof ( pxhd ) ) , 0);
	write(ofil, &pxhd, sizeof (pxhd));
E 5
I 5
D 11
	(void) lseek(ofil, 0l, 0);
E 11
I 11
	if (lseek(ofil, (off_t)0, 0) == -1)
		perror("magic2: lseek1"), panic("magic2");
E 11
	write(ofil, (char *) (&magichdr), sizeof(struct exec));
D 11
	(void) lseek(ofil, ( long ) ( HEADER_BYTES - sizeof ( pxhd ) ) , 0);
E 11
I 11
	if (lseek(ofil, (off_t)(HEADER_BYTES - sizeof(pxhd)), 0) == -1)
		perror("magic2: lseek2"), panic("magic2");
E 11
	write(ofil, (char *) (&pxhd), sizeof (pxhd));
E 5
}
#endif OBJ
#endif

#ifdef PXP
writef(i, cp)
{

	write(i, cp, strlen(cp));
}
#endif
E 1
