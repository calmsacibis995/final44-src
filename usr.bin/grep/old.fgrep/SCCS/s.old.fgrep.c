h08216
s 00005/00005/00398
d D 8.1 93/06/06 14:49:11 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00001/00386
d D 4.5 91/04/17 17:52:44 bostic 5 4
c new copyright; att/bsd/shared
e
s 00006/00001/00381
d D 4.4 87/10/07 17:25:20 bostic 4 3
c implement -o flag; *always* print the file name
e
s 00028/00011/00354
d D 4.3 85/05/30 13:44:36 mckusick 3 2
c use more reasonable buffering
e
s 00002/00002/00363
d D 4.2 82/10/20 16:04:53 mckusick 2 1
c use <> for include files
e
s 00365/00000/00000
d D 4.1 80/10/01 17:26:32 bill 1 0
c date and time created 80/10/01 17:26:32 by bill
e
u
U
t
T
I 1
D 5
static char *sccsid = "%W% (Berkeley) %G%";
E 5
I 5
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
/*
 * fgrep -- print all lines containing any of a set of keywords
 *
 *	status returns:
 *		0 - ok, and some matches
 *		1 - ok, but no matches
 *		2 - some error
 */

D 2
#include "stdio.h"
# include "ctype.h"
E 2
I 2
#include <stdio.h>
#include <ctype.h>
I 3
#include <sys/param.h>
#include <sys/stat.h>
E 3
E 2

I 3
#define BLKSIZE 8192
E 3
#define	MAXSIZ 6000
#define QSIZE 400
struct words {
	char 	inp;
	char	out;
	struct	words *nst;
	struct	words *link;
	struct	words *fail;
} w[MAXSIZ], *smax, *q;

long	lnum;
int	bflag, cflag, fflag, lflag, nflag, vflag, xflag, yflag;
int	hflag	= 1;
I 4
int	oflag;
E 4
int	sflag;
int	retcode = 0;
int	nfile;
long	blkno;
int	nsucc;
long	tln;
FILE	*wordf;
char	*argptr;

main(argc, argv)
char **argv;
{
	while (--argc > 0 && (++argv)[0][0]=='-')
		switch (argv[0][1]) {

		case 's':
			sflag++;
			continue;

		case 'h':
			hflag = 0;
			continue;

I 4
		case 'o':
			oflag++;
			continue;

E 4
		case 'b':
			bflag++;
			continue;

		case 'c':
			cflag++;
			continue;

		case 'e':
			argc--;
			argv++;
			goto out;

		case 'f':
			fflag++;
			continue;

		case 'l':
			lflag++;
			continue;

		case 'n':
			nflag++;
			continue;

		case 'v':
			vflag++;
			continue;

		case 'x':
			xflag++;
			continue;

		case 'i':		/* Berkeley */
		case 'y':		/* Btl */
			yflag++;
			continue;
		default:
			fprintf(stderr, "fgrep: unknown flag\n");
			continue;
		}
out:
	if (argc<=0)
		exit(2);
	if (fflag) {
		wordf = fopen(*argv, "r");
		if (wordf==NULL) {
			fprintf(stderr, "fgrep: can't open %s\n", *argv);
			exit(2);
		}
	}
	else argptr = *argv;
	argc--;
	argv++;

	cgotofn();
	cfail();
	nfile = argc;
	if (argc<=0) {
		if (lflag) exit(1);
		execute((char *)NULL);
	}
	else while (--argc >= 0) {
		execute(*argv);
		argv++;
	}
	exit(retcode != 0 ? retcode : nsucc == 0);
}

# define ccomp(a,b) (yflag ? lca(a)==lca(b) : a==b)
# define lca(x) (isupper(x) ? tolower(x) : x)
execute(file)
char *file;
{
	register struct words *c;
	register ccount;
	register char ch;
	register char *p;
D 3
	char buf[2*BUFSIZ];
E 3
I 3
	static char *buf;
	static int blksize;
	struct stat stb;
E 3
	int f;
	int failed;
	char *nlp;
	if (file) {
		if ((f = open(file, 0)) < 0) {
			fprintf(stderr, "fgrep: can't open %s\n", file);
			retcode = 2;
			return;
		}
	}
	else f = 0;
I 3
	if (buf == NULL) {
		if (fstat(f, &stb) > 0 && stb.st_blksize > 0)
			blksize = stb.st_blksize;
		else
			blksize = BLKSIZE;
		buf = (char *)malloc(2*blksize);
		if (buf == NULL) {
			fprintf(stderr, "egrep: no memory for %s\n", file);
			retcode = 2;
			return;
		}
	}
E 3
	ccount = 0;
	failed = 0;
	lnum = 1;
	tln = 0;
	blkno = 0;
	p = buf;
	nlp = p;
	c = w;
	for (;;) {
		if (--ccount <= 0) {
D 3
			if (p == &buf[2*BUFSIZ]) p = buf;
			if (p > &buf[BUFSIZ]) {
				if ((ccount = read(f, p, &buf[2*BUFSIZ] - p)) <= 0) break;
E 3
I 3
			if (p == &buf[2*blksize]) p = buf;
			if (p > &buf[blksize]) {
				if ((ccount = read(f, p, &buf[2*blksize] - p)) <= 0) break;
E 3
			}
D 3
			else if ((ccount = read(f, p, BUFSIZ)) <= 0) break;
E 3
I 3
			else if ((ccount = read(f, p, blksize)) <= 0) break;
E 3
			blkno += ccount;
		}
		nstate:
			if (ccomp(c->inp, *p)) {
				c = c->nst;
			}
			else if (c->link != 0) {
				c = c->link;
				goto nstate;
			}
			else {
				c = c->fail;
				failed = 1;
				if (c==0) {
					c = w;
					istate:
					if (ccomp(c->inp ,  *p)) {
						c = c->nst;
					}
					else if (c->link != 0) {
						c = c->link;
						goto istate;
					}
				}
				else goto nstate;
			}
		if (c->out) {
			while (*p++ != '\n') {
				if (--ccount <= 0) {
D 3
					if (p == &buf[2*BUFSIZ]) p = buf;
					if (p > &buf[BUFSIZ]) {
						if ((ccount = read(f, p, &buf[2&BUFSIZ] - p)) <= 0) break;
E 3
I 3
					if (p == &buf[2*blksize]) p = buf;
					if (p > &buf[blksize]) {
						if ((ccount = read(f, p, &buf[2*blksize] - p)) <= 0) break;
E 3
					}
D 3
					else if ((ccount = read(f, p, BUFSIZ)) <= 0) break;
E 3
I 3
					else if ((ccount = read(f, p, blksize)) <= 0) break;
E 3
					blkno += ccount;
				}
			}
			if ( (vflag && (failed == 0 || xflag == 0)) || (vflag == 0 && xflag && failed) )
				goto nomatch;
	succeed:	nsucc = 1;
			if (cflag) tln++;
			else if (sflag)
				;	/* ugh */
			else if (lflag) {
				printf("%s\n", file);
				close(f);
				return;
			}
			else {
D 4
				if (nfile > 1 && hflag) printf("%s:", file);
E 4
I 4
				if (nfile > 1 && hflag || oflag) printf("%s:", file);
E 4
D 3
				if (bflag) printf("%ld:", (blkno-ccount-1)/BUFSIZ);
E 3
I 3
				if (bflag) printf("%ld:", (blkno-ccount-1)/DEV_BSIZE);
E 3
				if (nflag) printf("%ld:", lnum);
				if (p <= nlp) {
D 3
					while (nlp < &buf[2*BUFSIZ]) putchar(*nlp++);
E 3
I 3
					while (nlp < &buf[2*blksize]) putchar(*nlp++);
E 3
					nlp = buf;
				}
				while (nlp < p) putchar(*nlp++);
			}
	nomatch:	lnum++;
			nlp = p;
			c = w;
			failed = 0;
			continue;
		}
		if (*p++ == '\n')
			if (vflag) goto succeed;
			else {
				lnum++;
				nlp = p;
				c = w;
				failed = 0;
			}
	}
	close(f);
	if (cflag) {
		if (nfile > 1)
			printf("%s:", file);
		printf("%ld\n", tln);
	}
}

getargc()
{
	register c;
	if (wordf)
		return(getc(wordf));
	if ((c = *argptr++) == '\0')
		return(EOF);
	return(c);
}

cgotofn() {
	register c;
	register struct words *s;

	s = smax = w;
nword:	for(;;) {
		c = getargc();
		if (c==EOF)
			return;
		if (c == '\n') {
			if (xflag) {
				for(;;) {
					if (s->inp == c) {
						s = s->nst;
						break;
					}
					if (s->inp == 0) goto nenter;
					if (s->link == 0) {
						if (smax >= &w[MAXSIZ -1]) overflo();
						s->link = ++smax;
						s = smax;
						goto nenter;
					}
					s = s->link;
				}
			}
			s->out = 1;
			s = w;
		} else {
		loop:	if (s->inp == c) {
				s = s->nst;
				continue;
			}
			if (s->inp == 0) goto enter;
			if (s->link == 0) {
				if (smax >= &w[MAXSIZ - 1]) overflo();
				s->link = ++smax;
				s = smax;
				goto enter;
			}
			s = s->link;
			goto loop;
		}
	}

	enter:
	do {
		s->inp = c;
		if (smax >= &w[MAXSIZ - 1]) overflo();
		s->nst = ++smax;
		s = smax;
	} while ((c = getargc()) != '\n' && c!=EOF);
	if (xflag) {
	nenter:	s->inp = '\n';
		if (smax >= &w[MAXSIZ -1]) overflo();
		s->nst = ++smax;
	}
	smax->out = 1;
	s = w;
	if (c != EOF)
		goto nword;
}

overflo() {
	fprintf(stderr, "wordlist too large\n");
	exit(2);
}
cfail() {
	struct words *queue[QSIZE];
	struct words **front, **rear;
	struct words *state;
	int bstart;
	register char c;
	register struct words *s;
	s = w;
	front = rear = queue;
init:	if ((s->inp) != 0) {
		*rear++ = s->nst;
		if (rear >= &queue[QSIZE - 1]) overflo();
	}
	if ((s = s->link) != 0) {
		goto init;
	}

	while (rear!=front) {
		s = *front;
		if (front == &queue[QSIZE-1])
			front = queue;
		else front++;
	cloop:	if ((c = s->inp) != 0) {
			bstart = 0;
			*rear = (q = s->nst);
			if (front < rear)
				if (rear >= &queue[QSIZE-1])
					if (front == queue) overflo();
					else rear = queue;
				else rear++;
			else
				if (++rear == front) overflo();
			state = s->fail;
		floop:	if (state == 0) {
				state = w;
				bstart = 1;
			}
			if (state->inp == c) {
			qloop:	q->fail = state->nst;
				if ((state->nst)->out == 1) q->out = 1;
				if ((q = q->link) != 0) goto qloop;
			}
			else if ((state = state->link) != 0)
				goto floop;
			else if(bstart == 0){
				state = 0;
				goto floop;
			}
		}
		if ((s = s->link) != 0)
			goto cloop;
	}
}
E 1
