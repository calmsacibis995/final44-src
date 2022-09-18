h28270
s 00004/00004/00414
d D 8.1 93/06/06 14:02:07 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00417
d D 5.10 93/02/26 12:00:30 torek 12 11
c typo
e
s 00001/00001/00417
d D 5.9 92/09/16 10:55:11 elan 11 10
c copyright[] -> static.
e
s 00004/00029/00414
d D 5.8 92/09/15 10:58:11 elan 10 9
c Added SCCS keywords.
e
s 00068/00043/00375
d D 5.7 92/09/01 11:11:46 elan 9 8
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00036/00027/00382
d D 5.6 92/07/21 10:30:33 bostic 8 7
c prototype lpr to fix quad's
e
s 00001/00011/00408
d D 5.5 90/06/01 18:46:14 bostic 7 6
c new copyright notice
e
s 00010/00005/00409
d D 5.4 88/06/30 18:00:03 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00404
d D 5.3 88/05/05 18:08:19 bostic 5 4
c written by Ralph Campbell; add Berkeley specific header
e
s 00023/00003/00385
d D 5.2 85/10/30 12:25:38 bloom 4 3
c add -m flag to group all machines together and add "pc" entry to printcap
c for printing cost (Jon Loeliger, jdl@purdue)
e
s 00013/00001/00375
d D 5.1 85/06/06 10:06:27 dist 3 2
c Add copyright
e
s 00004/00001/00372
d D 4.2 83/07/17 00:11:44 sam 2 1
c put sccs id's to some use
e
s 00373/00000/00000
d D 4.1 83/03/09 09:56:58 ralph 1 0
c date and time created 83/03/09 09:56:58 by ralph
e
u
U
t
T
I 3
/*
D 10
 * Copyright (c) 1983 Regents of the University of California.
E 10
I 10
D 13
 * Copyright (c) 1983 The Regents of the University of California.
E 10
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 7
I 7
D 9
 * %sccs.include.redist.c%
E 9
I 9
D 10
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 10
 *
D 10
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
E 7
E 6
E 5
 */

E 3
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
I 3
D 11
char copyright[] =
E 11
I 11
static char copyright[] =
E 11
D 9
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 9
I 9
D 10
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 10
I 10
D 13
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 10
E 9
 All rights reserved.\n";
E 13
I 13
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
E 3
D 9
static char sccsid[] = "%W% (Berkeley) %G%";
E 9
I 9
D 10
static char sccsid[] = "@(#)pac.c	5.8 (Berkeley) 8/31/92";
E 10
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
E 10
E 9
D 3
#endif
E 3
I 3
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 3

E 2
/*
 * Do Printer accounting summary.
 * Currently, usage is
D 4
 *	pac [-Pprinter] [-pprice] [-s] [-r] [-c] [user ...]
E 4
I 4
 *	pac [-Pprinter] [-pprice] [-s] [-r] [-c] [-m] [user ...]
E 4
 * to print the usage information for the named people.
 */

I 8
#include <sys/param.h>

#include <dirent.h>
#include <stdlib.h>
E 8
#include <stdio.h>
I 8
#include <string.h>
#include "lp.h"
E 8
#include "lp.local.h"

D 9
char	*printer;			/* printer name */
char	*acctfile;			/* accounting file (input data) */
char	*sumfile;			/* summary file */
float	price = 0.02;			/* cost per page (or what ever) */
int	allflag = 1;			/* Get stats on everybody */
int	sort;				/* Sort by cost */
int	summarize;			/* Compress accounting file */
int	reverse;			/* Reverse sort order */
int	hcount;				/* Count of hash entries */
int	errs;
I 4
int	mflag = 0;			/* disregard machine names */
int	pflag = 0;			/* 1 if -p on cmd line */
int	price100;			/* per-page cost in 100th of a cent */
E 9
I 9
static char	*acctfile;	/* accounting file (input data) */
static int	 allflag = 1;	/* Get stats on everybody */
static int	 errs;
static int	 hcount;	/* Count of hash entries */
static int	 mflag = 0;	/* disregard machine names */
static int	 pflag = 0;	/* 1 if -p on cmd line */
static float	 price = 0.02;	/* cost per page (or what ever) */
static long	 price100;	/* per-page cost in 100th of a cent */
static int	 reverse;	/* Reverse sort order */
static int	 sort;		/* Sort by cost */
static char	*sumfile;	/* summary file */
static int	 summarize;	/* Compress accounting file */
E 9
D 8
char	*index();
int	pgetnum();
E 8
E 4

/*
 * Grossness follows:
 *  Names to be accumulated are hashed into the following
 *  table.
 */

#define	HSHSIZE	97			/* Number of hash buckets */

struct hent {
	struct	hent *h_link;		/* Forward hash link */
	char	*h_name;		/* Name of this user */
	float	h_feetpages;		/* Feet or pages of paper */
	int	h_count;		/* Number of runs */
};

D 9
struct	hent	*hashtab[HSHSIZE];	/* Hash table proper */
E 9
I 9
static struct	hent	*hashtab[HSHSIZE];	/* Hash table proper */
E 9
D 8
struct	hent	*enter();
struct	hent	*lookup();
E 8

D 8
#define	NIL	((struct hent *) 0)	/* The big zero */
E 8
I 8
D 9
int	account __P((FILE *));
int	any __P((int, char []));
int	chkprinter __P((char *));
void	dumpit __P((void));
int	hash __P((char []));
struct	hent *enter __P((char []));
struct	hent *lookup __P((char []));
int	qucmp __P((const void *, const void *));
void	rewrite __P((void));
E 9
I 9
static void	account __P((FILE *));
static int	any __P((int, char []));
D 12
stativ int	chkprinter __P((char *));
E 12
I 12
static int	chkprinter __P((char *));
E 12
static void	dumpit __P((void));
static int	hash __P((char []));
static struct	hent *enter __P((char []));
static struct	hent *lookup __P((char []));
static int	qucmp __P((const void *, const void *));
static void	rewrite __P((void));
E 9
E 8

D 8
double	atof();
char	*getenv();
char	*pgetstr();

E 8
I 8
D 9
int
E 9
I 9
void
E 9
E 8
main(argc, argv)
I 8
	int argc;
E 8
	char **argv;
{
	register FILE *acct;
	register char *cp;

	while (--argc) {
		cp = *++argv;
		if (*cp++ == '-') {
			switch(*cp++) {
			case 'P':
				/*
				 * Printer name.
				 */
				printer = cp;
				continue;

			case 'p':
				/*
				 * get the price.
				 */
				price = atof(cp);
I 4
				pflag = 1;
E 4
				continue;

			case 's':
				/*
				 * Summarize and compress accounting file.
				 */
				summarize++;
				continue;

			case 'c':
				/*
				 * Sort by cost.
				 */
				sort++;
				continue;

I 4
			case 'm':
				/*
				 * disregard machine names for each user
				 */
				mflag = 1;
				continue;

E 4
			case 'r':
				/*
				 * Reverse sorting order.
				 */
				reverse++;
				continue;

			default:
D 4
fprintf(stderr, "usage: pac [-Pprinter] [-pprice] [-s] [-c] [-r] [user ...]\n");
E 4
I 4
fprintf(stderr,
    "usage: pac [-Pprinter] [-pprice] [-s] [-c] [-r] [-m] [user ...]\n");
E 4
				exit(1);
			}
		}
		(void) enter(--cp);
		allflag = 0;
	}
	if (printer == NULL && (printer = getenv("PRINTER")) == NULL)
		printer = DEFLP;
	if (!chkprinter(printer)) {
		printf("pac: unknown printer %s\n", printer);
		exit(2);
	}

	if ((acct = fopen(acctfile, "r")) == NULL) {
		perror(acctfile);
		exit(1);
	}
	account(acct);
	fclose(acct);
	if ((acct = fopen(sumfile, "r")) != NULL) {
		account(acct);
		fclose(acct);
	}
	if (summarize)
		rewrite();
	else
		dumpit();
	exit(errs);
}

/*
 * Read the entire accounting file, accumulating statistics
 * for the users that we have in the hash table.  If allflag
 * is set, then just gather the facts on everyone.
 * Note that we must accomodate both the active and summary file
 * formats here.
I 4
 * Host names are ignored if the -m flag is present.
E 4
 */
D 8

E 8
I 8
D 9
int
E 9
I 9
static void
E 9
E 8
account(acct)
	register FILE *acct;
{
	char linebuf[BUFSIZ];
	double t;
	register char *cp, *cp2;
	register struct hent *hp;
	register int ic;

	while (fgets(linebuf, BUFSIZ, acct) != NULL) {
		cp = linebuf;
		while (any(*cp, " t\t"))
			cp++;
		t = atof(cp);
		while (any(*cp, ".0123456789"))
			cp++;
		while (any(*cp, " \t"))
			cp++;
		for (cp2 = cp; !any(*cp2, " \t\n"); cp2++)
			;
		ic = atoi(cp2);
		*cp2 = '\0';
I 4
		if (mflag && index(cp, ':'))
		    cp = index(cp, ':') + 1;
E 4
		hp = lookup(cp);
D 8
		if (hp == NIL) {
E 8
I 8
		if (hp == NULL) {
E 8
			if (!allflag)
				continue;
			hp = enter(cp);
		}
		hp->h_feetpages += t;
		if (ic)
			hp->h_count += ic;
		else
			hp->h_count++;
	}
}

/*
 * Sort the hashed entries by name or footage
 * and print it all out.
 */
D 8

E 8
I 8
D 9
void
E 9
I 9
static void
E 9
E 8
dumpit()
{
	struct hent **base;
	register struct hent *hp, **ap;
	register int hno, c, runs;
	float feet;
D 8
	int qucmp();
E 8

	hp = hashtab[0];
	hno = 1;
	base = (struct hent **) calloc(sizeof hp, hcount);
	for (ap = base, c = hcount; c--; ap++) {
D 8
		while (hp == NIL)
E 8
I 8
		while (hp == NULL)
E 8
			hp = hashtab[hno++];
		*ap = hp;
		hp = hp->h_link;
	}
	qsort(base, hcount, sizeof hp, qucmp);
	printf("  Login               pages/feet   runs    price\n");
	feet = 0.0;
	runs = 0;
	for (ap = base, c = hcount; c--; ap++) {
		hp = *ap;
		runs += hp->h_count;
		feet += hp->h_feetpages;
		printf("%-24s %7.2f %4d   $%6.2f\n", hp->h_name,
		    hp->h_feetpages, hp->h_count, hp->h_feetpages * price);
	}
	if (allflag) {
		printf("\n");
		printf("%-24s %7.2f %4d   $%6.2f\n", "total", feet, 
		    runs, feet * price);
	}
}

/*
 * Rewrite the summary file with the summary information we have accumulated.
 */
D 8

E 8
I 8
D 9
void
E 9
I 9
static void
E 9
E 8
rewrite()
{
	register struct hent *hp;
	register int i;
	register FILE *acctf;

	if ((acctf = fopen(sumfile, "w")) == NULL) {
		perror(sumfile);
		errs++;
		return;
	}
	for (i = 0; i < HSHSIZE; i++) {
		hp = hashtab[i];
		while (hp != NULL) {
			fprintf(acctf, "%7.2f\t%s\t%d\n", hp->h_feetpages,
			    hp->h_name, hp->h_count);
			hp = hp->h_link;
		}
	}
	fflush(acctf);
	if (ferror(acctf)) {
		perror(sumfile);
		errs++;
	}
	fclose(acctf);
	if ((acctf = fopen(acctfile, "w")) == NULL)
		perror(acctfile);
	else
		fclose(acctf);
}

/*
 * Hashing routines.
 */

/*
 * Enter the name into the hash table and return the pointer allocated.
 */

D 9
struct hent *
E 9
I 9
static struct hent *
E 9
enter(name)
	char name[];
{
	register struct hent *hp;
	register int h;

D 8
	if ((hp = lookup(name)) != NIL)
E 8
I 8
	if ((hp = lookup(name)) != NULL)
E 8
		return(hp);
	h = hash(name);
	hcount++;
	hp = (struct hent *) calloc(sizeof *hp, 1);
	hp->h_name = (char *) calloc(sizeof(char), strlen(name)+1);
	strcpy(hp->h_name, name);
	hp->h_feetpages = 0.0;
	hp->h_count = 0;
	hp->h_link = hashtab[h];
	hashtab[h] = hp;
	return(hp);
}

/*
 * Lookup a name in the hash table and return a pointer
 * to it.
 */

D 9
struct hent *
E 9
I 9
static struct hent *
E 9
lookup(name)
	char name[];
{
	register int h;
	register struct hent *hp;

	h = hash(name);
D 8
	for (hp = hashtab[h]; hp != NIL; hp = hp->h_link)
E 8
I 8
	for (hp = hashtab[h]; hp != NULL; hp = hp->h_link)
E 8
		if (strcmp(hp->h_name, name) == 0)
			return(hp);
D 8
	return(NIL);
E 8
I 8
	return(NULL);
E 8
}

/*
 * Hash the passed name and return the index in
 * the hash table to begin the search.
 */
D 8

E 8
I 8
D 9
int
E 9
I 9
static int
E 9
E 8
hash(name)
	char name[];
{
	register int h;
	register char *cp;

	for (cp = name, h = 0; *cp; h = (h << 2) + *cp++)
		;
	return((h & 0x7fffffff) % HSHSIZE);
}

/*
 * Other stuff
 */
D 8

E 8
I 8
D 9
int
E 9
I 9
static int
E 9
E 8
any(ch, str)
I 8
	int ch;
E 8
	char str[];
{
	register int c = ch;
	register char *cp = str;

	while (*cp)
		if (*cp++ == c)
			return(1);
	return(0);
}

/*
 * The qsort comparison routine.
 * The comparison is ascii collating order
 * or by feet of typesetter film, according to sort.
 */
D 8

qucmp(left, right)
	struct hent **left, **right;
E 8
I 8
D 9
int
E 9
I 9
static int
E 9
qucmp(a, b)
	const void *a, *b;
E 8
{
	register struct hent *h1, *h2;
	register int r;

D 8
	h1 = *left;
	h2 = *right;
E 8
I 8
	h1 = *(struct hent **)a;
	h2 = *(struct hent **)b;
E 8
	if (sort)
D 4
		r = h1->h_feetpages < h2->h_feetpages ? -1 : h1->h_feetpages > h2->h_feetpages;
E 4
I 4
D 8
		r = h1->h_feetpages < h2->h_feetpages ? -1 : h1->h_feetpages > 
h2->h_feetpages;
E 8
I 8
		r = h1->h_feetpages < h2->h_feetpages ?
		    -1 : h1->h_feetpages > h2->h_feetpages;
E 8
E 4
	else
		r = strcmp(h1->h_name, h2->h_name);
	return(reverse ? -r : r);
}

/*
 * Perform lookup for printer name or abbreviation --
 */
I 8
D 9
int
E 9
I 9
static int
E 9
E 8
chkprinter(s)
	register char *s;
{
D 9
	static char buf[BUFSIZ/2];
	char b[BUFSIZ];
E 9
	int stat;
D 9
	char *bp = buf;
E 9

D 9
	if ((stat = pgetent(b, s)) < 0) {
E 9
I 9
	if ((stat = cgetent(&bp, printcapdb, s)) == -2) {
E 9
		printf("pac: can't open printer description file\n");
		exit(3);
D 9
	} else if (stat == 0)
E 9
I 9
	} else if (stat == -1)
E 9
		return(0);
D 9
	if ((acctfile = pgetstr("af", &bp)) == NULL) {
E 9
I 9
	else if (stat == -3)
		fatal("potential reference loop detected in printcap file");

	if (cgetstr(bp, "af", &acctfile) == -1) {
E 9
		printf("accounting not enabled for printer %s\n", printer);
		exit(2);
	}
I 4
D 9
	if (!pflag && (price100 = pgetnum("pc")) > 0)
E 9
I 9
	if (!pflag && (cgetnum(bp, "pc", &price100) == 0))
E 9
		price = price100/10000.0;
E 4
	sumfile = (char *) calloc(sizeof(char), strlen(acctfile)+5);
	if (sumfile == NULL) {
		perror("pac");
		exit(1);
	}
	strcpy(sumfile, acctfile);
	strcat(sumfile, "_sum");
	return(1);
}
E 1
