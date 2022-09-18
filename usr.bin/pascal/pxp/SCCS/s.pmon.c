h61974
s 00002/00002/00361
d D 8.1 93/06/06 16:02:24 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00357
d D 5.4 91/04/16 15:56:25 bostic 8 7
c new copyright; att/bsd/shared
e
s 00002/00002/00360
d D 5.3 88/01/03 00:23:21 bostic 7 6
c pcalloc returns NULL on failure, not -1; fix for ANSI C
e
s 00002/00002/00360
d D 5.2 87/12/04 19:04:50 bostic 6 5
c old assignment operator
e
s 00010/00003/00352
d D 5.1 85/06/05 15:48:58 dist 5 4
c Add copyright
e
s 00002/00002/00353
d D 2.2 85/01/09 18:17:47 mckusick 4 3
c alloc is gone, use pcalloc()
e
s 00000/00000/00355
d D 2.1 84/02/08 20:23:49 aoki 3 2
c synchronizing at version 2
e
s 00003/00003/00352
d D 1.2 81/03/07 17:35:28 mckusic 2 1
c merge in onyx changes
e
s 00355/00000/00000
d D 1.1 81/03/02 21:28:43 peter 1 0
c date and time created 81/03/02 21:28:43 by peter
e
u
U
t
T
I 1
D 5
static	char *sccsid = "%W% (Berkeley) %G%";
/* Copyright (c) 1979 Regents of the University of California */
#
E 5
I 5
D 8
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
D 9
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
E 8
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8

E 5
/*
 * pxp - Pascal execution profiler
 *
 * Bill Joy UCB
 * Version 1.2 January 1979
 */

#include "0.h"

/*
 * Profile counter processing cluster
 *
 * This file contains all routines which do the hard work in profiling.
 *
 * The first group of routines (getit, getpmon, getcore, and pmread)
 * deal with extracting data from the pmon.out and (with more difficulty)
 * core files.
 *
 * The routines cnttab and prttab collect counters for
 * and print the summary table respectively.
 *
 * The routines "*cnt*" deal with manipulation of counters,
 * especially the "current" counter px.
 */
STATIC	struct pxcnt px;

/*
 * Table to record info
 * for procedure/function summary
 */
STATIC	struct pftab {
	long	pfcnt;
	short	pfline;
	char	*pfname;
	short	pflev;
} *zpf;

/*
 * Global variables
 */
STATIC	long *zbuf; 	/* Count buffer */
STATIC	short zcnt;	/* Number of counts */
STATIC	short zpfcnt;	/* Number of proc/funcs's */
STATIC	short gcountr;	/* Unique name generator */
STATIC	short zfil;	/* I/o unit for count data reads */
STATIC	short lastpf;	/* Total # of procs and funcs for consistency chk */

getit(fp)
	register char *fp;
{

	if (core)
		getcore(fp);
	else
		getpmon(fp);
}

/*
 * Setup monitor data buffer from pmon.out
 * style file whose name is fp.
 */
getpmon(fp)
	char *fp;
{
	register char *cp;
	short garbage;

	zfil = open(fp, 0);
	if (zfil < 0) {
		perror(fp);
		pexit(NOSTART);
	}
	if (pmread() < 0 || read(zfil, &garbage, 1) == 1) {
		Perror(fp, "Bad format for pmon.out style file");
		exit(1);
	}
	close(zfil);
	return;
}

D 2
STATIC	char nospcm[]	"Not enough memory for count buffers\n";
E 2
I 2
STATIC	char nospcm[]	= "Not enough memory for count buffers\n";
E 2

pmnospac()
{

	write(2, nospcm, sizeof nospcm);
	pexit(NOSTART);
}

/*
 * Structure of the first few
 * items of a px core dump.
 */
STATIC	struct info {
	char	*off;		/* Self-reference for pure text */
	short	type;		/* 0 = non-pure text, 1 = pure text */
	char	*bp;		/* Core address of pxps struct */
} inf;

/*
 * First few words of the px
 * information structure.
 */
STATIC	struct pxps {
	char	*buf;
	short	cnt;
} pxp;

getcore(fp)
	char *fp;
{

	write(2, "-c: option not supported\n", sizeof("-c: option not supported\n"));
	pexit(ERRS);
/*
	short pm;

	zfil = open(fp, 0);
	if (zfil < 0) {
		perror(fp);
		pexit(NOSTART);
	}
	if (lseek(zfil, 02000, 0) < 0)
		goto format;
	if (read(zfil, &inf, sizeof inf) < 0)
		goto format;
	if (inf.type != 0 && inf.type != 1)
		goto format;
	if (inf.type)
D 6
		inf.bp =- inf.off;
E 6
I 6
		inf.bp -= inf.off;
E 6
	if (lseek(zfil, inf.bp + 02000, 0) < 0)
		goto format;
	if (read(zfil, &pxp, sizeof pxp) != sizeof pxp)
		goto format;
	if (pxp.buf == NIL) {
		Perror(fp, "No profile data in file");
		exit(1);
	}
	if (inf.type)
D 6
		pxp.buf =- inf.off;
E 6
I 6
		pxp.buf -= inf.off;
E 6
	if (lseek(zfil, pxp.buf + 02000, 0) < 0)
		goto format;
	if (pmread() < 0)
		goto format;
	close(zfil);
	return;
format:
	Perror(fp, "Not a Pascal system core file");
	exit(1);
*/
}

pmread()
{
	register i;
	register char *cp;
	struct {
		long	no;
		long	tim;
		long	cntrs;
		long	rtns;
	} zmagic;

	if (read(zfil, &zmagic, sizeof zmagic) != sizeof zmagic)
		return (-1);
	if (zmagic.no != 0426)
		return (-1);
	ptvec = zmagic.tim;
	zcnt = zmagic.cntrs;
	zpfcnt = zmagic.rtns;
D 4
	cp = zbuf = alloc(i = (zcnt + 1) * sizeof *zbuf);
E 4
I 4
	cp = zbuf = pcalloc(i = (zcnt + 1) * sizeof *zbuf, 1);
E 4
D 7
	if (cp == -1)
E 7
I 7
	if (cp == NULL)
E 7
		pmnospac();
D 4
	cp = zpf = alloc(zpfcnt * sizeof *zpf);
E 4
I 4
	cp = zpf = pcalloc(zpfcnt * sizeof *zpf, 1);
E 4
D 7
	if (cp == -1)
E 7
I 7
	if (cp == NULL)
E 7
		pmnospac();
	i -= sizeof(zmagic);
D 2
	if (read(zfil, zbuf + (sizeof(zmagic) / sizeof(zbuf)), i) != i)
E 2
I 2
	if (read(zfil, zbuf + (sizeof(zmagic) / sizeof(*zbuf)), i) != i)
E 2
		return (-1);
	zbuf++;
	return (0);
}

cnttab(s, no)
	char *s;
	short no;
{
	register struct pftab *pp;

	lastpf++;
	if (table == 0)
		return;
	if (no == zpfcnt)
		cPANIC();
	pp = &zpf[no];
	pp->pfname = s;
	pp->pfline = line;
	pp->pfcnt = nowcnt();
	pp->pflev = cbn;
}

prttab()
{
	register i, j;
	register struct pftab *zpfp;

	if (profile == 0 && table == 0)
		return;
	if (cnts != zcnt || lastpf != zpfcnt)
		cPANIC();
	if (table == 0)
		return;
	if (profile)
		printf("\f\n");
	header();
	printf("\n\tLine\t   Count\n\n");
	zpfp = zpf;
	for (i = 0; i < zpfcnt; i++) {
		printf("\t%4d\t%8ld\t", zpfp->pfline, zpfp->pfcnt);
		if (!justify)
			for (j = zpfp->pflev * unit; j > 1; j--)
				putchar(' ');
		printf("%s\n", zpfp->pfname);
		zpfp++;
	}
}

nowcntr()
{

	return (px.counter);
}

long nowcnt()
{

	return (px.ntimes);
}

long cntof(pxc)
	struct pxcnt *pxc;
{

	if (profile == 0 && table == 0)
		return;
	return (pxc->ntimes);
}

setcnt(l)
	long l;
{

	if (profile == 0 && table == 0)
		return;
	px.counter = --gcountr;
	px.ntimes = l;
	px.gos = gocnt;
	px.printed = 0;
}

savecnt(pxc)
	register struct pxcnt *pxc;
{

	if (profile == 0 && table == 0)
		return;
	pxc->ntimes = px.ntimes;
	pxc->counter = px.counter;
	pxc->gos = px.gos;
	pxc->printed = 1;
}

rescnt(pxc)
	register struct pxcnt *pxc;
{

	if (profile == 0 && table == 0)
		return;
	px.ntimes = pxc->ntimes;
	px.counter = pxc->counter;
	px.gos = gocnt;
	px.printed = pxc->printed;
	return (gocnt != pxc->gos);
}

getcnt()
{

	if (profile == 0 && table == 0)
		return;
	if (cnts == zcnt)
		cPANIC();
	px.counter = cnts;
	px.ntimes = zbuf[cnts];
	px.gos = gocnt;
	px.printed = 0;
	++cnts;
}

unprint()
{

	px.printed = 0;
}

/*
 * Control printing of '|'
 * when profiling.
 */
STATIC	char	nobar;

baroff()
{

	nobar = 1;
}

baron()
{

	nobar = 0;
}

/*
 * Do we want cnt and/or '|' on this line ?
 *	1 = count and '|'
 *	0 = only '|'
 *     -1 = spaces only
 */
shudpcnt()
{

	register i;

	if (nobar)
		return (-1);
	i = px.printed;
	px.printed = 1;
	return (i == 0);
}

D 2
STATIC	char mism[]	"Program and counter data do not correspond\n";
E 2
I 2
STATIC	char mism[]	= "Program and counter data do not correspond\n";
E 2

cPANIC()
{

	printf("cnts %d zcnt %d, lastpf %d zpfcnt %d\n",
		cnts, zcnt, lastpf, zpfcnt);
	flush();
	write(2, mism, sizeof mism);
	pexit(ERRS);
}
E 1
