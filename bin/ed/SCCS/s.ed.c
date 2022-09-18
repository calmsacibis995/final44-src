h12586
s 00004/00004/01820
d D 5.2 94/04/02 09:53:07 bostic 21 18
c copyright cleanup
e
s 00001/00001/01823
d R 5.2 94/01/02 18:09:29 bostic 20 18
c Ash/sh doesn't support the -t flag
e
s 00000/00215/01609
d D 5.1.1.1 92/12/03 16:48:30 mckusick 19 18
c delete decryption for the foreign sites (alpha 4.4BSD)
e
s 00014/00001/01810
d D 5.1 91/04/08 14:40:40 bostic 18 17
c new copyright; att/bsd/shared
e
s 00011/00007/01800
d D 4.14 91/02/25 07:37:41 bostic 17 15
c ANSI fixes
e
s 00000/00215/01592
d D 4.13.1.1 90/10/21 14:22:02 mckusick 16 15
c delete decryption for the foreign sites
e
s 00001/00000/01806
d D 4.13 90/02/20 16:33:35 donn 15 14
c need to include <param.h> for MAXPATHLEN
e
s 00002/00003/01804
d D 4.12 90/02/19 10:33:25 bostic 14 13
c change FNSIZE to MAXPATHLEN; bug report 4.3BSD-tahoe/bin/30
e
s 00014/00010/01793
d D 4.11 89/09/15 16:15:15 bostic 13 12
c POSIX signals
e
s 00003/00003/01800
d D 4.10 89/05/27 10:43:01 bostic 12 11
c gtty/stty are in libcompat now
e
s 00004/00002/01799
d D 4.9 89/05/08 17:54:31 bostic 11 10
c /tmp moves to /usr/include
e
s 00002/00003/01799
d D 4.8 89/05/08 12:58:45 bostic 10 9
c file system reorg and pathnames.h
e
s 00005/00003/01797
d D 4.7 89/03/05 21:28:34 bostic 9 8
c add pathnames.h
e
s 00002/00002/01798
d D 4.6 88/07/22 16:15:17 bostic 8 6
c ANSIfication
e
s 00000/00215/01585
d D 4.5.1.1 86/08/12 17:40:28 mckusick 7 6
c delete decryption for the foreign sites
e
s 00035/00001/01765
d D 4.5 86/08/12 16:51:12 mckusick 6 5
c add `ifdef CRYPT' to show the part of ed.c implementing encryption
e
s 00000/00001/01766
d D 4.4 86/04/26 04:38:46 lepreau 5 4
c remove bogus "compacting" free preceding a realloc
e
s 00003/00001/01764
d D 4.3 83/08/11 19:51:54 sam 4 3
c sccs keyword fixes
e
s 00001/00000/01764
d D 4.2 82/12/24 20:01:29 sam 3 1
c eliminate name conflict with ttychars.h
e
s 00001/00000/01764
d R 4.2 82/12/24 18:45:47 sam 2 1
c handle redefinition from ttychars.h
e
s 01764/00000/00000
d D 4.1 82/05/07 15:37:52 mckusick 1 0
c date and time created 82/05/07 15:37:52 by mckusick
e
u
U
f b 
t
T
I 18
/*-
D 21
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1991
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
 * %sccs.include.proprietary.c%
 */

E 18
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
#ifndef lint
I 18
char copyright[] =
D 21
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 21
I 21
"%Z% Copyright (c) 1991\n\
	The Regents of the University of California.  All rights reserved.\n";
E 21
#endif /* not lint */

#ifndef lint
E 18
static char sccsid[] = "%W% (Berkeley) %G%";
D 18
#endif
E 18
I 18
#endif /* not lint */
E 18
E 4

/*
 * Editor
 */
I 6
D 7
D 16
D 19
#define CRYPT
E 7
E 6

E 19
E 16
I 15
#include <sys/param.h>
E 15
D 13
#include <signal.h>
E 13
I 13
D 17
#include <sys/signal.h>
E 17
I 17
#include <sys/wait.h>
#include <signal.h>
E 17
E 13
#include <sgtty.h>
I 3
#undef CEOF
I 17
#include <fcntl.h>
#include <time.h>
E 17
E 3
#include <setjmp.h>
I 17
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 17
I 9
#include "pathnames.h"

E 9
#define	NULL	0
D 14
#define	FNSIZE	64
E 14
#define	LBSIZE	512
#define	ESIZE	128
#define	GBSIZE	256
#define	NBRA	5
#define	EOF	-1
D 6
#define	KSIZE	9
E 6

#define	CBRA	1
#define	CCHR	2
#define	CDOT	4
#define	CCL	6
#define	NCCL	8
#define	CDOL	10
#define	CEOF	11
#define	CKET	12
#define	CBACK	14

#define	STAR	01

char	Q[]	= "";
char	T[]	= "TMP";
#define	READ	0
#define	WRITE	1

int	peekc;
int	lastc;
D 14
char	savedfile[FNSIZE];
char	file[FNSIZE];
E 14
I 14
char	savedfile[MAXPATHLEN];
char	file[MAXPATHLEN];
E 14
char	linebuf[LBSIZE];
char	rhsbuf[LBSIZE/2];
char	expbuf[ESIZE+4];
int	circfl;
int	*zero;
int	*dot;
int	*dol;
int	*addr1;
int	*addr2;
char	genbuf[LBSIZE];
long	count;
char	*nextip;
char	*linebp;
int	ninbuf;
int	io;
int	pflag;
D 17
long	lseek();
E 17
D 13
int	(*oldhup)();
int	(*oldquit)();
E 13
I 13
sig_t	oldhup;
sig_t	oldquit;
E 13
int	vflag	= 1;
I 6

D 7
D 16
D 19
#ifdef CRYPT
/*
 * Various flags and buffers needed by the encryption routines.
 */
#define	KSIZE	9
E 6
int	xflag;
int	xtflag;
int	kflag;
char	key[KSIZE + 1];
char	crbuf[512];
char	perm[768];
char	tperm[768];
I 6
#endif CRYPT
E 19
E 16
E 7

E 6
int	listf;
int	col;
char	*globp;
int	tfile	= -1;
int	tline;
D 8
char	*tfname;
E 8
I 8
D 10
char	tfname[] = "/tmp/eXXXXX";
E 10
I 10
D 11
char	tfname[] = _PATH_TMP;
E 11
I 11
char	tfname[sizeof(_PATH_TMP) + 20];
E 11
E 10
E 8
char	*loc1;
char	*loc2;
char	*locs;
char	ibuff[512];
int	iblock	= -1;
char	obuff[512];
int	oblock	= -1;
int	ichanged;
int	nleft;
char	WRERR[]	= "WRITE ERROR";
int	names[26];
int	anymarks;
char	*braslist[NBRA];
char	*braelist[NBRA];
int	nbra;
int	subnewa;
int	subolda;
int	fchange;
int	wrapp;
unsigned nlall = 128;

int	*address();
char	*getline();
char	*getblock();
char	*place();
D 17
char	*mktemp();
char	*malloc();
char	*realloc();
E 17
jmp_buf	savej;

I 17
void onintr(), quit(), onhup();

E 17
main(argc, argv)
D 17
char **argv;
E 17
I 17
	int argc;
	char **argv;
E 17
{
	register char *p1, *p2;
D 13
	extern int onintr(), quit(), onhup();
	int (*oldintr)();
E 13
I 13
D 17
	extern void onintr(), quit(), onhup();
E 17
	sig_t oldintr;
E 13

	oldquit = signal(SIGQUIT, SIG_IGN);
	oldhup = signal(SIGHUP, SIG_IGN);
	oldintr = signal(SIGINT, SIG_IGN);
	if ((int)signal(SIGTERM, SIG_IGN) == 0)
		signal(SIGTERM, quit);
	argv++;
	while (argc > 1 && **argv=='-') {
		switch((*argv)[1]) {

		case '\0':
			vflag = 0;
			break;

		case 'q':
			signal(SIGQUIT, SIG_DFL);
			vflag = 1;
			break;

I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
		case 'x':
			xflag = 1;
			break;
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
		}
		argv++;
		argc--;
	}
I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
	if(xflag){
		getkey();
		kflag = crinit(key, perm);
	}
I 6
#endif CRYPT
E 19
E 16
E 7
E 6

	if (argc>1) {
		p1 = *argv;
		p2 = savedfile;
		while (*p2++ = *p1++)
			;
		globp = "r";
	}
	zero = (int *)malloc(nlall*sizeof(int));
D 8
	tfname = mktemp("/tmp/eXXXXX");
E 8
I 8
D 11
	mktemp(tfname);
E 11
I 11
	(void)strcpy(tfname, _PATH_TMP);
	(void)strcat(tfname, "_edXXXXXX");
	(void)mktemp(tfname);
E 11
E 8
	init();
	if (((int)oldintr&01) == 0)
		signal(SIGINT, onintr);
	if (((int)oldhup&01) == 0)
		signal(SIGHUP, onhup);
	setjmp(savej);
	commands();
	quit();
}

commands()
{
	int getfile(), gettty();
	register *a1, c;

	for (;;) {
	if (pflag) {
		pflag = 0;
		addr1 = addr2 = dot;
		goto print;
	}
	addr1 = 0;
	addr2 = 0;
	do {
		addr1 = addr2;
		if ((a1 = address())==0) {
			c = getchr();
			break;
		}
		addr2 = a1;
		if ((c=getchr()) == ';') {
			c = ',';
			dot = a1;
		}
	} while (c==',');
	if (addr1==0)
		addr1 = addr2;
	switch(c) {

	case 'a':
		setdot();
		newline();
		append(gettty, addr2);
		continue;

	case 'c':
		delete();
		append(gettty, addr1-1);
		continue;

	case 'd':
		delete();
		continue;

	case 'E':
		fchange = 0;
		c = 'e';
	case 'e':
		setnoaddr();
		if (vflag && fchange) {
			fchange = 0;
			error(Q);
		}
		filename(c);
		init();
		addr2 = zero;
		goto caseread;

	case 'f':
		setnoaddr();
		filename(c);
		puts(savedfile);
		continue;

	case 'g':
		global(1);
		continue;

	case 'i':
		setdot();
		nonzero();
		newline();
		append(gettty, addr2-1);
		continue;


	case 'j':
		if (addr2==0) {
			addr1 = dot;
			addr2 = dot+1;
		}
		setdot();
		newline();
		nonzero();
		join();
		continue;

	case 'k':
		if ((c = getchr()) < 'a' || c > 'z')
			error(Q);
		newline();
		setdot();
		nonzero();
		names[c-'a'] = *addr2 & ~01;
		anymarks |= 01;
		continue;

	case 'm':
		move(0);
		continue;

	case '\n':
		if (addr2==0)
			addr2 = dot+1;
		addr1 = addr2;
		goto print;

	case 'l':
		listf++;
	case 'p':
	case 'P':
		newline();
	print:
		setdot();
		nonzero();
		a1 = addr1;
		do {
			puts(getline(*a1++));
		} while (a1 <= addr2);
		dot = addr2;
		listf = 0;
		continue;

	case 'Q':
		fchange = 0;
	case 'q':
		setnoaddr();
		newline();
		quit();

	case 'r':
		filename(c);
	caseread:
		if ((io = open(file, 0)) < 0) {
			lastc = '\n';
			error(file);
		}
		setall();
		ninbuf = 0;
		c = zero != dol;
		append(getfile, addr2);
		exfile();
		fchange = c;
		continue;

	case 's':
		setdot();
		nonzero();
		substitute(globp!=0);
		continue;

	case 't':
		move(1);
		continue;

	case 'u':
		setdot();
		nonzero();
		newline();
		if ((*addr2&~01) != subnewa)
			error(Q);
		*addr2 = subolda;
		dot = addr2;
		continue;

	case 'v':
		global(0);
		continue;

	case 'W':
		wrapp++;
	case 'w':
		setall();
		nonzero();
		filename(c);
		if(!wrapp ||
		  ((io = open(file,1)) == -1) ||
		  ((lseek(io, 0L, 2)) == -1))
			if ((io = creat(file, 0666)) < 0)
				error(file);
		wrapp = 0;
		putfile();
		exfile();
		if (addr1==zero+1 && addr2==dol)
			fchange = 0;
		continue;

I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
	case 'x':
		setnoaddr();
		newline();
		xflag = 1;
		puts("Entering encrypting mode!");
		getkey();
		kflag = crinit(key, perm);
		continue;
I 6
#endif CRYPT
E 19
E 16
E 7
E 6


	case '=':
		setall();
		newline();
		count = (addr2-zero)&077777;
		putd();
		putchr('\n');
		continue;

	case '!':
		callunix();
		continue;

	case EOF:
		return;

	}
	error(Q);
	}
}

int *
address()
{
	register *a1, minus, c;
	int n, relerr;

	minus = 0;
	a1 = 0;
	for (;;) {
		c = getchr();
		if ('0'<=c && c<='9') {
			n = 0;
			do {
				n *= 10;
				n += c - '0';
			} while ((c = getchr())>='0' && c<='9');
			peekc = c;
			if (a1==0)
				a1 = zero;
			if (minus<0)
				n = -n;
			a1 += n;
			minus = 0;
			continue;
		}
		relerr = 0;
		if (a1 || minus)
			relerr++;
		switch(c) {
		case ' ':
		case '\t':
			continue;
	
		case '+':
			minus++;
			if (a1==0)
				a1 = dot;
			continue;

		case '-':
		case '^':
			minus--;
			if (a1==0)
				a1 = dot;
			continue;
	
		case '?':
		case '/':
			compile(c);
			a1 = dot;
			for (;;) {
				if (c=='/') {
					a1++;
					if (a1 > dol)
						a1 = zero;
				} else {
					a1--;
					if (a1 < zero)
						a1 = dol;
				}
				if (execute(0, a1))
					break;
				if (a1==dot)
					error(Q);
			}
			break;
	
		case '$':
			a1 = dol;
			break;
	
		case '.':
			a1 = dot;
			break;

		case '\'':
			if ((c = getchr()) < 'a' || c > 'z')
				error(Q);
			for (a1=zero; a1<=dol; a1++)
				if (names[c-'a'] == (*a1 & ~01))
					break;
			break;
	
		default:
			peekc = c;
			if (a1==0)
				return(0);
			a1 += minus;
			if (a1<zero || a1>dol)
				error(Q);
			return(a1);
		}
		if (relerr)
			error(Q);
	}
}

setdot()
{
	if (addr2 == 0)
		addr1 = addr2 = dot;
	if (addr1 > addr2)
		error(Q);
}

setall()
{
	if (addr2==0) {
		addr1 = zero+1;
		addr2 = dol;
		if (dol==zero)
			addr1 = zero;
	}
	setdot();
}

setnoaddr()
{
	if (addr2)
		error(Q);
}

nonzero()
{
	if (addr1<=zero || addr2>dol)
		error(Q);
}

newline()
{
	register c;

	if ((c = getchr()) == '\n')
		return;
	if (c=='p' || c=='l') {
		pflag++;
		if (c=='l')
			listf++;
		if (getchr() == '\n')
			return;
	}
	error(Q);
}

filename(comm)
{
	register char *p1, *p2;
	register c;

	count = 0;
	c = getchr();
	if (c=='\n' || c==EOF) {
		p1 = savedfile;
		if (*p1==0 && comm!='f')
			error(Q);
		p2 = file;
		while (*p2++ = *p1++)
			;
		return;
	}
	if (c!=' ')
		error(Q);
	while ((c = getchr()) == ' ')
		;
	if (c=='\n')
		error(Q);
	p1 = file;
	do {
		*p1++ = c;
		if (c==' ' || c==EOF)
			error(Q);
	} while ((c = getchr()) != '\n');
	*p1++ = 0;
	if (savedfile[0]==0 || comm=='e' || comm=='f') {
		p1 = savedfile;
		p2 = file;
		while (*p1++ = *p2++)
			;
	}
}

exfile()
{
	close(io);
	io = -1;
	if (vflag) {
		putd();
		putchr('\n');
	}
}

I 13
void
E 13
onintr()
{
D 13
	signal(SIGINT, onintr);
E 13
I 13
	/* not necessary: (void)signal(SIGINT, onintr); */
E 13
	putchr('\n');
	lastc = '\n';
	error(Q);
}

I 13
void
E 13
onhup()
{
D 13
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
E 13
I 13
	/* not necessary: (void)signal(SIGINT, SIG_IGN); */
	/* not necessary: (void)signal(SIGHUP, SIG_IGN); */
E 13
	if (dol > zero) {
		addr1 = zero+1;
		addr2 = dol;
		io = creat("ed.hup", 0666);
		if (io > 0)
			putfile();
	}
	fchange = 0;
	quit();
}

error(s)
char *s;
{
	register c;

	wrapp = 0;
	listf = 0;
	putchr('?');
	puts(s);
	count = 0;
	lseek(0, (long)0, 2);
	pflag = 0;
	if (globp)
		lastc = '\n';
	globp = 0;
	peekc = lastc;
	if(lastc)
		while ((c = getchr()) != '\n' && c != EOF)
			;
	if (io > 0) {
		close(io);
		io = -1;
	}
	longjmp(savej, 1);
}

getchr()
{
	char c;
	if (lastc=peekc) {
		peekc = 0;
		return(lastc);
	}
	if (globp) {
		if ((lastc = *globp++) != 0)
			return(lastc);
		globp = 0;
		return(EOF);
	}
	if (read(0, &c, 1) <= 0)
		return(lastc = EOF);
	lastc = c&0177;
	return(lastc);
}

gettty()
{
	register c;
	register char *gf;
	register char *p;

	p = linebuf;
	gf = globp;
	while ((c = getchr()) != '\n') {
		if (c==EOF) {
			if (gf)
				peekc = c;
			return(c);
		}
		if ((c &= 0177) == 0)
			continue;
		*p++ = c;
		if (p >= &linebuf[LBSIZE-2])
			error(Q);
	}
	*p++ = 0;
	if (linebuf[0]=='.' && linebuf[1]==0)
		return(EOF);
	return(0);
}

getfile()
{
	register c;
	register char *lp, *fp;

	lp = linebuf;
	fp = nextip;
	do {
		if (--ninbuf < 0) {
			if ((ninbuf = read(io, genbuf, LBSIZE)-1) < 0)
				return(EOF);
			fp = genbuf;
			while(fp < &genbuf[ninbuf]) {
				if (*fp++ & 0200) {
I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
					if (kflag)
						crblock(perm, genbuf, ninbuf+1, count);
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
					break;
				}
			}
			fp = genbuf;
		}
		c = *fp++;
		if (c=='\0')
			continue;
		if (c&0200 || lp >= &linebuf[LBSIZE]) {
			lastc = '\n';
			error(Q);
		}
		*lp++ = c;
		count++;
	} while (c != '\n');
	*--lp = 0;
	nextip = fp;
	return(0);
}

putfile()
{
	int *a1, n;
	register char *fp, *lp;
	register nib;

	nib = 512;
	fp = genbuf;
	a1 = addr1;
	do {
		lp = getline(*a1++);
		for (;;) {
			if (--nib < 0) {
				n = fp-genbuf;
I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
				if(kflag)
					crblock(perm, genbuf, n, count-n);
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
				if(write(io, genbuf, n) != n) {
					puts(WRERR);
					error(Q);
				}
				nib = 511;
				fp = genbuf;
			}
			count++;
			if ((*fp++ = *lp++) == 0) {
				fp[-1] = '\n';
				break;
			}
		}
	} while (a1 <= addr2);
	n = fp-genbuf;
I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
	if(kflag)
		crblock(perm, genbuf, n, count-n);
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
	if(write(io, genbuf, n) != n) {
		puts(WRERR);
		error(Q);
	}
}

append(f, a)
int *a;
int (*f)();
{
	register *a1, *a2, *rdot;
	int nline, tl;

	nline = 0;
	dot = a;
	while ((*f)() == 0) {
		if ((dol-zero)+1 >= nlall) {
			int *ozero = zero;
			nlall += 512;
D 5
			free((char *)zero);
E 5
			if ((zero = (int *)realloc((char *)zero, nlall*sizeof(int)))==NULL) {
				lastc = '\n';
				zero = ozero;
				error("MEM?");
			}
			dot += zero - ozero;
			dol += zero - ozero;
		}
		tl = putline();
		nline++;
		a1 = ++dol;
		a2 = a1+1;
		rdot = ++dot;
		while (a1 > rdot)
			*--a2 = *--a1;
		*rdot = tl;
	}
	return(nline);
}

callunix()
{
D 13
	register (*savint)(), pid, rpid;
E 13
I 13
	register sig_t savint;
	register int pid, rpid;
E 13
	int retcode;

	setnoaddr();
	if ((pid = fork()) == 0) {
		signal(SIGHUP, oldhup);
		signal(SIGQUIT, oldquit);
D 9
		execl("/bin/sh", "sh", "-t", 0);
E 9
I 9
		execl(_PATH_BSHELL, "sh", "-t", 0);
E 9
		exit(0100);
	}
	savint = signal(SIGINT, SIG_IGN);
	while ((rpid = wait(&retcode)) != pid && rpid != -1)
		;
	signal(SIGINT, savint);
	puts("!");
}

I 13
void
E 13
quit()
{
	if (vflag && fchange && dol!=zero) {
		fchange = 0;
		error(Q);
	}
	unlink(tfname);
	exit(0);
}

delete()
{
	setdot();
	newline();
	nonzero();
	rdelete(addr1, addr2);
}

rdelete(ad1, ad2)
int *ad1, *ad2;
{
	register *a1, *a2, *a3;

	a1 = ad1;
	a2 = ad2+1;
	a3 = dol;
	dol -= a2 - a1;
	do {
		*a1++ = *a2++;
	} while (a2 <= a3);
	a1 = ad1;
	if (a1 > dol)
		a1 = dol;
	dot = a1;
	fchange = 1;
}

gdelete()
{
	register *a1, *a2, *a3;

	a3 = dol;
	for (a1=zero+1; (*a1&01)==0; a1++)
		if (a1>=a3)
			return;
	for (a2=a1+1; a2<=a3;) {
		if (*a2&01) {
			a2++;
			dot = a1;
		} else
			*a1++ = *a2++;
	}
	dol = a1-1;
	if (dot>dol)
		dot = dol;
	fchange = 1;
}

char *
getline(tl)
{
	register char *bp, *lp;
	register nl;

	lp = linebuf;
	bp = getblock(tl, READ);
	nl = nleft;
	tl &= ~0377;
	while (*lp++ = *bp++)
		if (--nl == 0) {
			bp = getblock(tl+=0400, READ);
			nl = nleft;
		}
	return(linebuf);
}

putline()
{
	register char *bp, *lp;
	register nl;
	int tl;

	fchange = 1;
	lp = linebuf;
	tl = tline;
	bp = getblock(tl, WRITE);
	nl = nleft;
	tl &= ~0377;
	while (*bp = *lp++) {
		if (*bp++ == '\n') {
			*--bp = 0;
			linebp = lp;
			break;
		}
		if (--nl == 0) {
			bp = getblock(tl+=0400, WRITE);
			nl = nleft;
		}
	}
	nl = tline;
	tline += (((lp-linebuf)+03)>>1)&077776;
	return(nl);
}

char *
getblock(atl, iof)
{
	extern read(), write();
	register bno, off;
	register char *p1, *p2;
	register int n;
	
	bno = (atl>>8)&0377;
	off = (atl<<1)&0774;
	if (bno >= 255) {
		lastc = '\n';
		error(T);
	}
	nleft = 512 - off;
	if (bno==iblock) {
		ichanged |= iof;
		return(ibuff+off);
	}
	if (bno==oblock)
		return(obuff+off);
	if (iof==READ) {
		if (ichanged) {
I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
			if(xtflag)
				crblock(tperm, ibuff, 512, (long)0);
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
			blkio(iblock, ibuff, write);
		}
		ichanged = 0;
		iblock = bno;
		blkio(bno, ibuff, read);
I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
		if(xtflag)
			crblock(tperm, ibuff, 512, (long)0);
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
		return(ibuff+off);
	}
	if (oblock>=0) {
I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
		if(xtflag) {
			p1 = obuff;
			p2 = crbuf;
			n = 512;
			while(n--)
				*p2++ = *p1++;
			crblock(tperm, crbuf, 512, (long)0);
			blkio(oblock, crbuf, write);
		} else
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
			blkio(oblock, obuff, write);
	}
	oblock = bno;
	return(obuff+off);
}

blkio(b, buf, iofcn)
char *buf;
int (*iofcn)();
{
	lseek(tfile, (long)b<<9, 0);
	if ((*iofcn)(tfile, buf, 512) != 512) {
		error(T);
	}
}

init()
{
	register *markp;

	close(tfile);
	tline = 2;
	for (markp = names; markp < &names[26]; )
		*markp++ = 0;
	subnewa = 0;
	anymarks = 0;
	iblock = -1;
	oblock = -1;
	ichanged = 0;
	close(creat(tfname, 0600));
	tfile = open(tfname, 2);
I 6
D 7
D 16
D 19
#ifdef CRYPT
E 6
	if(xflag) {
		xtflag = 1;
		makekey(key, tperm);
	}
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
	dot = dol = zero;
}

global(k)
{
	register char *gp;
	register c;
	register int *a1;
	char globuf[GBSIZE];

	if (globp)
		error(Q);
	setall();
	nonzero();
	if ((c=getchr())=='\n')
		error(Q);
	compile(c);
	gp = globuf;
	while ((c = getchr()) != '\n') {
		if (c==EOF)
			error(Q);
		if (c=='\\') {
			c = getchr();
			if (c!='\n')
				*gp++ = '\\';
		}
		*gp++ = c;
		if (gp >= &globuf[GBSIZE-2])
			error(Q);
	}
	*gp++ = '\n';
	*gp++ = 0;
	for (a1=zero; a1<=dol; a1++) {
		*a1 &= ~01;
		if (a1>=addr1 && a1<=addr2 && execute(0, a1)==k)
			*a1 |= 01;
	}
	/*
	 * Special case: g/.../d (avoid n^2 algorithm)
	 */
	if (globuf[0]=='d' && globuf[1]=='\n' && globuf[2]=='\0') {
		gdelete();
		return;
	}
	for (a1=zero; a1<=dol; a1++) {
		if (*a1 & 01) {
			*a1 &= ~01;
			dot = a1;
			globp = globuf;
			commands();
			a1 = zero;
		}
	}
}

join()
{
	register char *gp, *lp;
	register *a1;

	gp = genbuf;
	for (a1=addr1; a1<=addr2; a1++) {
		lp = getline(*a1);
		while (*gp = *lp++)
			if (gp++ >= &genbuf[LBSIZE-2])
				error(Q);
	}
	lp = linebuf;
	gp = genbuf;
	while (*lp++ = *gp++)
		;
	*addr1 = putline();
	if (addr1<addr2)
		rdelete(addr1+1, addr2);
	dot = addr1;
}

substitute(inglob)
{
	register *markp, *a1, nl;
	int gsubf;
	int getsub();

	gsubf = compsub();
	for (a1 = addr1; a1 <= addr2; a1++) {
		int *ozero;
		if (execute(0, a1)==0)
			continue;
		inglob |= 01;
		dosub();
		if (gsubf) {
			while (*loc2) {
				if (execute(1, (int *)0)==0)
					break;
				dosub();
			}
		}
		subnewa = putline();
		*a1 &= ~01;
		if (anymarks) {
			for (markp = names; markp < &names[26]; markp++)
				if (*markp == *a1)
					*markp = subnewa;
		}
		subolda = *a1;
		*a1 = subnewa;
		ozero = zero;
		nl = append(getsub, a1);
		nl += zero-ozero;
		a1 += nl;
		addr2 += nl;
	}
	if (inglob==0)
		error(Q);
}

compsub()
{
	register seof, c;
	register char *p;

	if ((seof = getchr()) == '\n' || seof == ' ')
		error(Q);
	compile(seof);
	p = rhsbuf;
	for (;;) {
		c = getchr();
		if (c=='\\')
			c = getchr() | 0200;
		if (c=='\n') {
			if (globp)
				c |= 0200;
			else
				error(Q);
		}
		if (c==seof)
			break;
		*p++ = c;
		if (p >= &rhsbuf[LBSIZE/2])
			error(Q);
	}
	*p++ = 0;
	if ((peekc = getchr()) == 'g') {
		peekc = 0;
		newline();
		return(1);
	}
	newline();
	return(0);
}

getsub()
{
	register char *p1, *p2;

	p1 = linebuf;
	if ((p2 = linebp) == 0)
		return(EOF);
	while (*p1++ = *p2++)
		;
	linebp = 0;
	return(0);
}

dosub()
{
	register char *lp, *sp, *rp;
	int c;

	lp = linebuf;
	sp = genbuf;
	rp = rhsbuf;
	while (lp < loc1)
		*sp++ = *lp++;
	while (c = *rp++&0377) {
		if (c=='&') {
			sp = place(sp, loc1, loc2);
			continue;
		} else if (c&0200 && (c &= 0177) >='1' && c < nbra+'1') {
			sp = place(sp, braslist[c-'1'], braelist[c-'1']);
			continue;
		}
		*sp++ = c&0177;
		if (sp >= &genbuf[LBSIZE])
			error(Q);
	}
	lp = loc2;
	loc2 = sp - genbuf + linebuf;
	while (*sp++ = *lp++)
		if (sp >= &genbuf[LBSIZE])
			error(Q);
	lp = linebuf;
	sp = genbuf;
	while (*lp++ = *sp++)
		;
}

char *
place(sp, l1, l2)
register char *sp, *l1, *l2;
{

	while (l1 < l2) {
		*sp++ = *l1++;
		if (sp >= &genbuf[LBSIZE])
			error(Q);
	}
	return(sp);
}

move(cflag)
{
	register int *adt, *ad1, *ad2;
	int getcopy();

	setdot();
	nonzero();
	if ((adt = address())==0)
		error(Q);
	newline();
	if (cflag) {
		int *ozero, delta;
		ad1 = dol;
		ozero = zero;
		append(getcopy, ad1++);
		ad2 = dol;
		delta = zero - ozero;
		ad1 += delta;
		adt += delta;
	} else {
		ad2 = addr2;
		for (ad1 = addr1; ad1 <= ad2;)
			*ad1++ &= ~01;
		ad1 = addr1;
	}
	ad2++;
	if (adt<ad1) {
		dot = adt + (ad2-ad1);
		if ((++adt)==ad1)
			return;
		reverse(adt, ad1);
		reverse(ad1, ad2);
		reverse(adt, ad2);
	} else if (adt >= ad2) {
		dot = adt++;
		reverse(ad1, ad2);
		reverse(ad2, adt);
		reverse(ad1, adt);
	} else
		error(Q);
	fchange = 1;
}

reverse(a1, a2)
register int *a1, *a2;
{
	register int t;

	for (;;) {
		t = *--a2;
		if (a2 <= a1)
			return;
		*a2 = *a1;
		*a1++ = t;
	}
}

getcopy()
{
	if (addr1 > addr2)
		return(EOF);
	getline(*addr1++);
	return(0);
}

compile(aeof)
{
	register eof, c;
	register char *ep;
	char *lastep;
	char bracket[NBRA], *bracketp;
	int cclcnt;

	ep = expbuf;
	eof = aeof;
	bracketp = bracket;
	if ((c = getchr()) == eof) {
		if (*ep==0)
			error(Q);
		return;
	}
	circfl = 0;
	nbra = 0;
	if (c=='^') {
		c = getchr();
		circfl++;
	}
	peekc = c;
	lastep = 0;
	for (;;) {
		if (ep >= &expbuf[ESIZE])
			goto cerror;
		c = getchr();
		if (c==eof) {
			if (bracketp != bracket)
				goto cerror;
			*ep++ = CEOF;
			return;
		}
		if (c!='*')
			lastep = ep;
		switch (c) {

		case '\\':
			if ((c = getchr())=='(') {
				if (nbra >= NBRA)
					goto cerror;
				*bracketp++ = nbra;
				*ep++ = CBRA;
				*ep++ = nbra++;
				continue;
			}
			if (c == ')') {
				if (bracketp <= bracket)
					goto cerror;
				*ep++ = CKET;
				*ep++ = *--bracketp;
				continue;
			}
			if (c>='1' && c<'1'+NBRA) {
				*ep++ = CBACK;
				*ep++ = c-'1';
				continue;
			}
			*ep++ = CCHR;
			if (c=='\n')
				goto cerror;
			*ep++ = c;
			continue;

		case '.':
			*ep++ = CDOT;
			continue;

		case '\n':
			goto cerror;

		case '*':
			if (lastep==0 || *lastep==CBRA || *lastep==CKET)
				goto defchar;
			*lastep |= STAR;
			continue;

		case '$':
			if ((peekc=getchr()) != eof)
				goto defchar;
			*ep++ = CDOL;
			continue;

		case '[':
			*ep++ = CCL;
			*ep++ = 0;
			cclcnt = 1;
			if ((c=getchr()) == '^') {
				c = getchr();
				ep[-2] = NCCL;
			}
			do {
				if (c=='\n')
					goto cerror;
				if (c=='-' && ep[-1]!=0) {
					if ((c=getchr())==']') {
						*ep++ = '-';
						cclcnt++;
						break;
					}
					while (ep[-1]<c) {
						*ep = ep[-1]+1;
						ep++;
						cclcnt++;
						if (ep>=&expbuf[ESIZE])
							goto cerror;
					}
				}
				*ep++ = c;
				cclcnt++;
				if (ep >= &expbuf[ESIZE])
					goto cerror;
			} while ((c = getchr()) != ']');
			lastep[1] = cclcnt;
			continue;

		defchar:
		default:
			*ep++ = CCHR;
			*ep++ = c;
		}
	}
   cerror:
	expbuf[0] = 0;
	nbra = 0;
	error(Q);
}

execute(gf, addr)
int *addr;
{
	register char *p1, *p2, c;

	for (c=0; c<NBRA; c++) {
		braslist[c] = 0;
		braelist[c] = 0;
	}
	if (gf) {
		if (circfl)
			return(0);
		p1 = linebuf;
		p2 = genbuf;
		while (*p1++ = *p2++)
			;
		locs = p1 = loc2;
	} else {
		if (addr==zero)
			return(0);
		p1 = getline(*addr);
		locs = 0;
	}
	p2 = expbuf;
	if (circfl) {
		loc1 = p1;
		return(advance(p1, p2));
	}
	/* fast check for first character */
	if (*p2==CCHR) {
		c = p2[1];
		do {
			if (*p1!=c)
				continue;
			if (advance(p1, p2)) {
				loc1 = p1;
				return(1);
			}
		} while (*p1++);
		return(0);
	}
	/* regular algorithm */
	do {
		if (advance(p1, p2)) {
			loc1 = p1;
			return(1);
		}
	} while (*p1++);
	return(0);
}

advance(lp, ep)
register char *ep, *lp;
{
	register char *curlp;
	int i;

	for (;;) switch (*ep++) {

	case CCHR:
		if (*ep++ == *lp++)
			continue;
		return(0);

	case CDOT:
		if (*lp++)
			continue;
		return(0);

	case CDOL:
		if (*lp==0)
			continue;
		return(0);

	case CEOF:
		loc2 = lp;
		return(1);

	case CCL:
		if (cclass(ep, *lp++, 1)) {
			ep += *ep;
			continue;
		}
		return(0);

	case NCCL:
		if (cclass(ep, *lp++, 0)) {
			ep += *ep;
			continue;
		}
		return(0);

	case CBRA:
		braslist[*ep++] = lp;
		continue;

	case CKET:
		braelist[*ep++] = lp;
		continue;

	case CBACK:
		if (braelist[i = *ep++]==0)
			error(Q);
		if (backref(i, lp)) {
			lp += braelist[i] - braslist[i];
			continue;
		}
		return(0);

	case CBACK|STAR:
		if (braelist[i = *ep++] == 0)
			error(Q);
		curlp = lp;
		while (backref(i, lp))
			lp += braelist[i] - braslist[i];
		while (lp >= curlp) {
			if (advance(lp, ep))
				return(1);
			lp -= braelist[i] - braslist[i];
		}
		continue;

	case CDOT|STAR:
		curlp = lp;
		while (*lp++)
			;
		goto star;

	case CCHR|STAR:
		curlp = lp;
		while (*lp++ == *ep)
			;
		ep++;
		goto star;

	case CCL|STAR:
	case NCCL|STAR:
		curlp = lp;
		while (cclass(ep, *lp++, ep[-1]==(CCL|STAR)))
			;
		ep += *ep;
		goto star;

	star:
		do {
			lp--;
			if (lp==locs)
				break;
			if (advance(lp, ep))
				return(1);
		} while (lp > curlp);
		return(0);

	default:
		error(Q);
	}
}

backref(i, lp)
register i;
register char *lp;
{
	register char *bp;

	bp = braslist[i];
	while (*bp++ == *lp++)
		if (bp >= braelist[i])
			return(1);
	return(0);
}

cclass(set, c, af)
register char *set, c;
{
	register n;

	if (c==0)
		return(0);
	n = *set++;
	while (--n)
		if (*set++ == c)
			return(af);
	return(!af);
}

putd()
{
	register r;

	r = count%10;
	count /= 10;
	if (count)
		putd();
	putchr(r + '0');
}

puts(sp)
register char *sp;
{
	col = 0;
	while (*sp)
		putchr(*sp++);
	putchr('\n');
}

char	line[70];
char	*linp	= line;

putchr(ac)
{
	register char *lp;
	register c;

	lp = linp;
	c = ac;
	if (listf) {
		col++;
		if (col >= 72) {
			col = 0;
			*lp++ = '\\';
			*lp++ = '\n';
		}
		if (c=='\t') {
			c = '>';
			goto esc;
		}
		if (c=='\b') {
			c = '<';
		esc:
			*lp++ = '-';
			*lp++ = '\b';
			*lp++ = c;
			goto out;
		}
		if (c<' ' && c!= '\n') {
			*lp++ = '\\';
			*lp++ = (c>>3)+'0';
			*lp++ = (c&07)+'0';
			col += 2;
			goto out;
		}
	}
	*lp++ = c;
out:
	if(c == '\n' || lp >= &line[64]) {
		linp = line;
		write(1, line, lp-line);
		return;
	}
	linp = lp;
}
I 6

D 7
D 16
D 19
#ifdef CRYPT
/*
 * Begin routines for doing encryption.
 */
E 6
crblock(permp, buf, nchar, startn)
char *permp;
char *buf;
long startn;
{
	register char *p1;
	int n1;
	int n2;
	register char *t1, *t2, *t3;

	t1 = permp;
	t2 = &permp[256];
	t3 = &permp[512];

	n1 = startn&0377;
	n2 = (startn>>8)&0377;
	p1 = buf;
	while(nchar--) {
		*p1 = t2[(t3[(t1[(*p1+n1)&0377]+n2)&0377]-n2)&0377]-n1;
		n1++;
		if(n1==256){
			n1 = 0;
			n2++;
			if(n2==256) n2 = 0;
		}
		p1++;
	}
}

getkey()
{
	struct sgttyb b;
	int save;
D 13
	int (*sig)();
E 13
I 13
	sig_t sig;
E 13
	register char *p;
	register c;

	sig = signal(SIGINT, SIG_IGN);
D 12
	if (gtty(0, &b) == -1)
E 12
I 12
	if (ioctl(0, TIOCGETP, &b) == -1)
E 12
		error("Input not tty");
	save = b.sg_flags;
	b.sg_flags &= ~ECHO;
D 12
	stty(0, &b);
E 12
I 12
	(void)ioctl(0, TIOCSETP, &b);
E 12
	puts("Key:");
	p = key;
	while(((c=getchr()) != EOF) && (c!='\n')) {
		if(p < &key[KSIZE])
			*p++ = c;
	}
	*p = 0;
	b.sg_flags = save;
D 12
	stty(0, &b);
E 12
I 12
	(void)ioctl(0, TIOCSETP, &b);
E 12
	signal(SIGINT, sig);
	return(key[0] != 0);
}

/*
 * Besides initializing the encryption machine, this routine
 * returns 0 if the key is null, and 1 if it is non-null.
 */
crinit(keyp, permp)
char	*keyp, *permp;
{
	register char *t1, *t2, *t3;
	register i;
	int ic, k, temp, pf[2];
	unsigned random;
	char buf[13];
	long seed;

	t1 = permp;
	t2 = &permp[256];
	t3 = &permp[512];
	if(*keyp == 0)
		return(0);
	strncpy(buf, keyp, 8);
	while (*keyp)
		*keyp++ = '\0';
	buf[8] = buf[0];
	buf[9] = buf[1];
	if (pipe(pf)<0)
		pf[0] = pf[1] = -1;
	if (fork()==0) {
		close(0);
		close(1);
		dup(pf[0]);
		dup(pf[1]);
D 9
		execl("/usr/lib/makekey", "-", 0);
		execl("/lib/makekey", "-", 0);
E 9
I 9
D 10
		execl(_PATH_UL_MAKEKEY, "-", 0);
		execl(_PATH_L_MAKEKEY, "-", 0);
E 10
I 10
		execl(_PATH_MAKEKEY, "-", 0);
E 10
E 9
		exit(1);
	}
	write(pf[1], buf, 10);
	if (wait((int *)NULL)==-1 || read(pf[0], buf, 13)!=13)
		error("crypt: cannot generate key");
	close(pf[0]);
	close(pf[1]);
	seed = 123;
	for (i=0; i<13; i++)
		seed = seed*buf[i] + i;
	for(i=0;i<256;i++){
		t1[i] = i;
		t3[i] = 0;
	}
	for(i=0; i<256; i++) {
		seed = 5*seed + buf[i%13];
		random = seed % 65521;
		k = 256-1 - i;
		ic = (random&0377) % (k+1);
		random >>= 8;
		temp = t1[k];
		t1[k] = t1[ic];
		t1[ic] = temp;
		if(t3[k]!=0) continue;
		ic = (random&0377) % k;
		while(t3[ic]!=0) ic = (ic+1) % k;
		t3[k] = ic;
		t3[ic] = k;
	}
	for(i=0; i<256; i++)
		t2[t1[i]&0377] = i;
	return(1);
}

makekey(a, b)
char *a, *b;
{
	register int i;
	long t;
	char temp[KSIZE + 1];

	for(i = 0; i < KSIZE; i++)
		temp[i] = *a++;
	time(&t);
	t += getpid();
	for(i = 0; i < 4; i++)
		temp[i] ^= (t>>(8*i))&0377;
	crinit(temp, b);
}
I 6
#endif CRYPT
E 19
E 16
E 7
E 6
E 1
