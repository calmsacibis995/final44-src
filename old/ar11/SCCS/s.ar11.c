h31874
s 00007/00005/00672
d D 4.6 89/05/11 13:50:25 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00006/00003/00671
d D 4.5 88/07/22 16:24:31 bostic 5 4
c gcc puts strings into text space
e
s 00002/00002/00672
d D 4.4 86/11/15 11:17:45 sam 4 3
c add tahoe
e
s 00051/00041/00623
d D 4.3 82/12/06 17:58:26 pugs 3 2
c sun changes
e
s 00001/00001/00663
d D 4.2 82/05/11 11:03:17 edward 2 1
c archive creation bug fixed
e
s 00664/00000/00000
d D 4.1 80/10/01 17:24:49 bill 1 0
c date and time created 80/10/01 17:24:49 by bill
e
u
U
t
T
I 1
static char *sccsid = "%W% (Berkeley) %G%";
/* ar11 - archiver for PDP-11 formatted archives */

D 6
#include <signal.h>
#include <stdio.h>
E 6
#include <sys/types.h>
I 6
#include <sys/signal.h>
E 6
#include <sys/stat.h>
I 6
#include <stdio.h>
#include "pathnames.h"

E 6
D 3
#define ARMAG -155  /* 017545 */
E 3
I 3
#define	ARMAG ((short)0177545)
E 3
struct ar_hdr {
D 3
	char ar_name[14];
	short ar_date1;
	short ar_date2;
	char ar_uid;
	char ar_gid;
	short ar_mode;
	short ar_size1;
	short ar_size2;
E 3
I 3
	char	ar_name[14];
	short	ar_sdate[2];
	char	ar_uid;
	char	ar_gid;
	short	ar_mode;
	short	ar_ssize[2];
E 3
};
D 3
int ar_date;
int ar_size;
#include <signal.h>
E 3
I 3
long	ar_date;
long	ar_size;

#ifdef vax
#define	fixshort(s)	(s)
#define	mklong(sp)	(((sp)[0] << 16) + (sp)[1])
#define unmklong(sp,l)	{ sp[0] = l >> 16; sp[1] = l & 0177777; }
#define fixhdr(hdr)	(hdr)
#endif
D 4
#ifdef mc68000
E 4
I 4
#if defined(mc68000) || defined(tahoe)
E 4
#define	fixshort(s)	((short)(((s>>8)&0377)+((s&0377)<<8)))
#define	mklong(sp)	(((sp)[0] << 16) + (sp)[1])
#define unmklong(sp,l)	{ sp[0] = l >> 16; sp[1] = l & 0177777; }
#define fixhdr(hdr)	swaphdr(hdr)
struct	ar_hdr swaphdr();
#endif

E 3
struct	stat	stbuf;
struct	ar_hdr	arbuf;
D 3
union ints
{
	struct fun
	{
		short h1;
		short h2;
	};
	int w1;
} x;
E 3

#define	SKIP	1
#define	IODD	2
#define	OODD	4
#define	HEAD	8

char	*man	= { "mrxtdp" };
char	*opt	= { "uvnbai" };

int	signum[] = {SIGHUP, SIGINT, SIGQUIT, 0};
int	sigdone();
int	rcmd();
int	dcmd();
int	xcmd();
int	tcmd();
int	pcmd();
int	mcmd();
int	(*comfun)();
char	flg[26];
char	**namv;
int	namc;
char	*arnam;
char	*ponam;
char	*tfnam;
char	*tf1nam;
char	*tf2nam;
char	*file;
char	name[16];
int	af;
int	tf;
int	tf1;
int	tf2;
int	bastate;
char	buf[512];

char	*trim();
char	*mktemp();
char	*ctime();

main(argc, argv)
char *argv[];
{
	register i;
	register char *cp;

	for(i=0; signum[i]; i++)
		if(signal(signum[i], SIG_IGN) != SIG_IGN)
			signal(signum[i], sigdone);
	if(argc < 3)
		usage();
	cp = argv[1];
	for(cp = argv[1]; *cp; cp++)
	switch(*cp) {
	case 'c':
	case 'v':
	case 'u':
	case 'n':
	case 'a':
	case 'b':
	case 'i':
		flg[*cp - 'a']++;
		continue;

	case 'r':
		setcom(rcmd);
		continue;

	case 'd':
		setcom(dcmd);
		continue;

	case 'x':
		setcom(xcmd);
		continue;

	case 't':
		setcom(tcmd);
		continue;

	case 'p':
		setcom(pcmd);
		continue;

	case 'm':
		setcom(mcmd);
		continue;

	default:
		fprintf(stderr, "ar11: bad option `%c'\n", *cp);
		done(1);
	}
	if(flg['i'-'a'])
		flg['b'-'a']++;
	if(flg['a'-'a'] || flg['b'-'a']) {
		bastate = 1;
		ponam = trim(argv[2]);
		argv++;
		argc--;
		if(argc < 3)
			usage();
	}
	arnam = argv[2];
	namv = argv+3;
	namc = argc-3;
	if(comfun == 0) {
		if(flg['u'-'a'] == 0) {
			fprintf(stderr, "ar11: one of [%s] must be specified\n", man);
			done(1);
		}
		setcom(rcmd);
	}
	(*comfun)();
	done(notfound());
}

setcom(fun)
int (*fun)();
{

	if(comfun != 0) {
		fprintf(stderr, "ar11: only one of [%s] allowed\n", man);
		done(1);
	}
	comfun = fun;
}

rcmd()
{
	register f;

	init();
	if(getaf() && flg['c'-'a']==0) {
		fprintf(stderr, "ar11: %s does not exist\n", arnam);
		done(1);
	}
	while(!getdir()) {
		bamatch();
		if(namc == 0 || match()) {
			f = stats();
			if(f < 0) {
				if(namc)
					fprintf(stderr, "ar11: cannot open %s\n", file);
				goto cp;
			}
			if(flg['u'-'a'])
				if(stbuf.st_mtime <= ar_date) {
					close(f);
					goto cp;
				}
			mesg('r');
			copyfil(af, -1, IODD+SKIP);
			movefil(f);
			continue;
		}
	cp:
		mesg('c');
		copyfil(af, tf, IODD+OODD+HEAD);
	}
	cleanup();
}

dcmd()
{

	init();
	if(getaf())
		noar();
	while(!getdir()) {
		if(match()) {
			mesg('d');
			copyfil(af, -1, IODD+SKIP);
			continue;
		}
		mesg('c');
		copyfil(af, tf, IODD+OODD+HEAD);
	}
	install();
}

xcmd()
{
	register f;

	if(getaf())
		noar();
	while(!getdir()) {
		if(namc == 0 || match()) {
			f = creat(file, arbuf.ar_mode & 0777);
			if(f < 0) {
				fprintf(stderr, "ar11: %s cannot create\n", file);
				goto sk;
			}
			mesg('x');
			copyfil(af, f, IODD);
			close(f);
			continue;
		}
	sk:
		mesg('c');
		copyfil(af, -1, IODD+SKIP);
	}
}

pcmd()
{

	if(getaf())
		noar();
	while(!getdir()) {
		if(namc == 0 || match()) {
			if(flg['v'-'a']) {
				printf("\n<%s>\n\n", file);
				fflush(stdout);
			}
			copyfil(af, 1, IODD);
			continue;
		}
		copyfil(af, -1, IODD+SKIP);
	}
}

mcmd()
{
I 5
D 6
	static char name2[] = "/tmp/v2XXXXX";
E 6
I 6
	static char name2[] = _PATH_TMP2;
E 6
E 5

	init();
	if(getaf())
		noar();
D 5
	tf2nam = mktemp("/tmp/v2XXXXX");
E 5
I 5
	tf2nam = mktemp(name2);
E 5
	close(creat(tf2nam, 0600));
	tf2 = open(tf2nam, 2);
	if(tf2 < 0) {
		fprintf(stderr, "ar11: cannot create third temp\n");
		done(1);
	}
	while(!getdir()) {
		bamatch();
		if(match()) {
			mesg('m');
			copyfil(af, tf2, IODD+OODD+HEAD);
			continue;
		}
		mesg('c');
		copyfil(af, tf, IODD+OODD+HEAD);
	}
	install();
}

tcmd()
{

	if(getaf())
		noar();
	while(!getdir()) {
		if(namc == 0 || match()) {
			if(flg['v'-'a'])
				longt();
			printf("%s\n", trim(file));
		}
		copyfil(af, -1, IODD+SKIP);
	}
}

init()
{
I 5
D 6
	static char name0[] = "/tmp/vXXXXX";
E 6
I 6
	static char name0[] = _PATH_TMP0;
E 6
E 5
D 3
	static short mbuf = ARMAG;
E 3
I 3
	static short mbuf = fixshort(ARMAG);
E 3

D 5
	tfnam = mktemp("/tmp/vXXXXX");
E 5
I 5
	tfnam = mktemp(name0);
E 5
	close(creat(tfnam, 0600));
	tf = open(tfnam, 2);
	if(tf < 0) {
		fprintf(stderr, "ar11: cannot create temp file\n");
		done(1);
	}
	if (write(tf, (char *)&mbuf, sizeof(short)) != sizeof(short))
		wrerr();
}

getaf()
{
	short mbuf;

	af = open(arnam, 0);
	if(af < 0)
		return(1);
D 3
	if (read(af, (char *)&mbuf, sizeof(short)) != sizeof(short) || mbuf!=ARMAG) {
E 3
I 3
	if (read(af, (char *)&mbuf, sizeof(short)) != sizeof(short) ||
	    mbuf != fixshort(ARMAG)) {
E 3
		fprintf(stderr, "ar11: %s not in PDP-11 archive format\n", arnam);
		done(1);
	}
	return(0);
}

usage()
{
	printf("usage: ar11 [%s][%s] archive files ...\n", opt, man);
	done(1);
}

noar()
{

	fprintf(stderr, "ar11: %s does not exist\n", arnam);
	done(1);
}

sigdone()
{
	done(100);
}

done(c)
{

	if(tfnam)
		unlink(tfnam);
	if(tf1nam)
		unlink(tf1nam);
	if(tf2nam)
		unlink(tf2nam);
	exit(c);
}

notfound()
{
	register i, n;

	n = 0;
	for(i=0; i<namc; i++)
		if(namv[i]) {
			fprintf(stderr, "ar11: %s not found\n", namv[i]);
			n++;
		}
	return(n);
}

cleanup()
{
	register i, f;

	for(i=0; i<namc; i++) {
		file = namv[i];
		if(file == 0)
			continue;
		namv[i] = 0;
		mesg('a');
		f = stats();
		if(f < 0) {
			fprintf(stderr, "ar11: %s cannot open\n", file);
			continue;
		}
		movefil(f);
	}
	install();
}

install()
{
	register i;

	for(i=0; signum[i]; i++)
		signal(signum[i], (int (*)())1);
	close(af);
	af = creat(arnam, 0666);
	if(af < 0) {
		fprintf(stderr, "ar11: cannot create %s\n", arnam);
		done(1);
	}
	lseek(tf, 0l, 0);
	while((i = read(tf, buf, 512)) > 0)
		if (write(af, buf, i) != i)
			wrerr();
	if(tf2nam) {
		lseek(tf2, 0l, 0);
		while((i = read(tf2, buf, 512)) > 0)
			if (write(af, buf, i) != i)
				wrerr();
	}
	if(tf1nam) {
		lseek(tf1, 0l, 0);
		while((i = read(tf1, buf, 512)) > 0)
			if (write(af, buf, i) != i)
				wrerr();
	}
}

/*
 * insert the file 'file'
 * into the temporary file
 */
movefil(f)
{
	register char *cp;
	register i;

	cp = trim(file);
	for(i=0; i<14; i++)
		if(arbuf.ar_name[i] = *cp)
			cp++;
D 2
	x.w1 = stbuf.st_size;
E 2
I 2
D 3
	ar_size = x.w1 = stbuf.st_size;
E 2
	arbuf.ar_size1 = x.h2;
	arbuf.ar_size2 = x.h1;
	x.w1 = stbuf.st_mtime;
	arbuf.ar_date1 = x.h2;
	arbuf.ar_date2 = x.h1;
E 3
I 3
	ar_size =  stbuf.st_size;
	ar_date = stbuf.st_mtime;
	unmklong(arbuf.ar_ssize, ar_size);
	unmklong(arbuf.ar_sdate, ar_date);
E 3
	arbuf.ar_uid = stbuf.st_uid;
	arbuf.ar_gid = stbuf.st_gid;
	arbuf.ar_mode = stbuf.st_mode;
	copyfil(f, tf, OODD+HEAD);
	close(f);
}

stats()
{
	register f;

	f = open(file, 0);
	if(f < 0)
		return(f);
	if(fstat(f, &stbuf) < 0) {
		close(f);
		return(-1);
	}
	return(f);
}

/*
 * copy next file
 * size given in arbuf
 */
copyfil(fi, fo, flag)
{
	register i, o;
	int pe;

D 3
	if(flag & HEAD)
		if (write(fo, (char *)&arbuf, sizeof arbuf) != sizeof arbuf)
E 3
I 3
	if(flag & HEAD) {
		struct ar_hdr tmpbuf;

		tmpbuf = fixhdr(arbuf);
		if (write(fo, (char *)&tmpbuf, sizeof arbuf) != sizeof arbuf)
E 3
			wrerr();
I 3
	}
E 3
	pe = 0;
	while(ar_size > 0) {
		i = o = 512;
		if(ar_size < i) {
			i = o = ar_size;
			if(i&1) {
				if(flag & IODD)
					i++;
				if(flag & OODD)
					o++;
			}
		}
		if(read(fi, buf, i) != i)
			pe++;
		if((flag & SKIP) == 0)
			if (write(fo, buf, o) != o)
				wrerr();
		ar_size -= 512;
	}
	if(pe)
		phserr();
}

getdir()
{
	register i;

	i = read(af, (char *)&arbuf, sizeof arbuf);
	if(i != sizeof arbuf) {
		if(tf1nam) {
			i = tf;
			tf = tf1;
			tf1 = i;
		}
		return(1);
	}
I 3
	arbuf = fixhdr(arbuf);
E 3
	for(i=0; i<14; i++)
D 3
{
E 3
		name[i] = arbuf.ar_name[i];
D 3
}
E 3
	file = name;
D 3
	ar_date = swap(&arbuf.ar_date1);
	ar_size = swap(&arbuf.ar_size1);
E 3
I 3
	ar_date = mklong(arbuf.ar_sdate);
	ar_size = mklong(arbuf.ar_ssize);
E 3
	return(0);
}

match()
{
	register i;

	for(i=0; i<namc; i++) {
		if(namv[i] == 0)
			continue;
		if(strcmp(trim(namv[i]), file) == 0) {
			file = namv[i];
			namv[i] = 0;
			return(1);
		}
	}
	return(0);
}

bamatch()
{
I 5
D 6
	static char name1[] = "/tmp/v1XXXXX";
E 6
I 6
	static char name1[] = _PATH_TMP1;
E 6
E 5
	register f;

	switch(bastate) {

	case 1:
		if(strcmp(file, ponam) != 0)
			return;
		bastate = 2;
		if(flg['a'-'a'])
			return;

	case 2:
		bastate = 0;
D 5
		tf1nam = mktemp("/tmp/v1XXXXX");
E 5
I 5
		tf1nam = mktemp(name1);
E 5
		close(creat(tf1nam, 0600));
		f = open(tf1nam, 2);
		if(f < 0) {
			fprintf(stderr, "ar11: cannot create second temp\n");
			return;
		}
		tf1 = tf;
		tf = f;
	}
}

phserr()
{

	fprintf(stderr, "ar11: phase error on %s\n", file);
}

mesg(c)
{

	if(flg['v'-'a'])
		if(c != 'c' || flg['v'-'a'] > 1)
			printf("%c - %s\n", c, file);
}

char *
trim(s)
char *s;
{
	register char *p1, *p2;

	for(p1 = s; *p1; p1++)
		;
	while(p1 > s) {
		if(*--p1 != '/')
			break;
		*p1 = 0;
	}
	p2 = s;
	for(p1 = s; *p1; p1++)
		if(*p1 == '/')
			p2 = p1+1;
	return(p2);
}

#define	IFMT	060000
#define	ISARG	01000
#define	LARGE	010000
#define	SUID	04000
#define	SGID	02000
#define	ROWN	0400
#define	WOWN	0200
#define	XOWN	0100
#define	RGRP	040
#define	WGRP	020
#define	XGRP	010
#define	ROTH	04
#define	WOTH	02
#define	XOTH	01
#define	STXT	01000

longt()
{
	register char *cp;

	pmode();
	printf("%3d/%1d", arbuf.ar_uid, arbuf.ar_gid);
	printf("%7D", ar_size);
	cp = ctime(&ar_date);
	printf(" %-12.12s %-4.4s ", cp+4, cp+20);
}

int	m1[] = { 1, ROWN, 'r', '-' };
int	m2[] = { 1, WOWN, 'w', '-' };
int	m3[] = { 2, SUID, 's', XOWN, 'x', '-' };
int	m4[] = { 1, RGRP, 'r', '-' };
int	m5[] = { 1, WGRP, 'w', '-' };
int	m6[] = { 2, SGID, 's', XGRP, 'x', '-' };
int	m7[] = { 1, ROTH, 'r', '-' };
int	m8[] = { 1, WOTH, 'w', '-' };
int	m9[] = { 2, STXT, 't', XOTH, 'x', '-' };

int	*m[] = { m1, m2, m3, m4, m5, m6, m7, m8, m9};

pmode()
{
	register int **mp;

	for (mp = &m[0]; mp < &m[9];)
		select(*mp++);
}

select(pairp)
int *pairp;
{
	register int n, *ap;

	ap = pairp;
	n = *ap++;
	while (--n>=0 && (arbuf.ar_mode&*ap++)==0)
		ap++;
	putchar(*ap);
}

wrerr()
{
	perror("ar write error");
	done(1);
}

D 3
swap(word)
short *word;
E 3
I 3
D 4
#ifdef mc68000
E 4
I 4
#if defined(mc68000) || defined(tahoe)
E 4
struct ar_hdr
swaphdr(hdr)
	struct ar_hdr hdr;
E 3
{
D 3
	x.h1 = ((struct fun *)word)->h2;
	x.h2 = ((struct fun *)word)->h1;
	
	return(x.w1);
E 3
I 3
	hdr.ar_sdate[0] = fixshort(hdr.ar_sdate[0]);
	hdr.ar_sdate[1] = fixshort(hdr.ar_sdate[1]);
	hdr.ar_ssize[0] = fixshort(hdr.ar_ssize[0]);
	hdr.ar_ssize[1] = fixshort(hdr.ar_ssize[1]);
	hdr.ar_mode = fixshort(hdr.ar_mode);
	return (hdr);
E 3
}
I 3
#endif
E 3
E 1
