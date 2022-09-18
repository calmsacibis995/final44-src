h29088
s 00005/00005/00126
d D 8.1 93/06/05 10:51:31 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00005/00128
d D 5.16 93/04/30 12:41:01 bostic 20 18
c someone confused kvm_open and kvm_openfiles; the Sun interface is simpler
e
s 00004/00009/00124
d R 5.16 93/04/30 12:35:32 bostic 19 18
c someone confused kvm_open and kvm_openfiles; the Sun interface is simpler
e
s 00012/00041/00121
d D 5.15 93/04/28 12:23:03 bostic 18 17
c use C library err routine
e
s 00001/00001/00161
d D 5.14 92/05/26 18:44:14 bostic 17 16
c cast not necessary
e
s 00027/00033/00135
d D 5.13 92/05/26 15:32:52 bostic 16 15
c update dmesg to use new kvm interface and vis(3); from Chris Torek
e
s 00001/00001/00167
d D 5.12 92/02/17 19:12:17 torek 15 14
c fix typo
e
s 00005/00004/00163
d D 5.11 92/02/12 20:53:38 karels 14 13
c msgbuf => msgbufp, at least for now
e
s 00013/00006/00154
d D 5.10 92/01/27 12:06:15 bostic 13 12
c don't let users create their own symbol table for the running kernel
e
s 00126/00104/00034
d D 5.9 91/05/02 19:29:32 bostic 12 11
c Rewrite from scratch, add Berkeley specific copyright.
c Delete the "-" option, don't display a timestamp.  Do avoid nonprintable
c characters, work on dead kernels
c 
e
s 00012/00005/00126
d D 5.8 91/04/16 17:23:51 bostic 11 10
c new copyright; att/bsd/shared
e
s 00001/00001/00130
d D 5.7 89/07/06 16:32:10 bostic 10 9
c /usr/adm -> /var/log; VMUNIX -> UNIX
e
s 00008/00007/00123
d D 5.6 89/04/02 12:24:04 bostic 9 8
c add pathnames.h
e
s 00001/00003/00129
d D 5.5 88/02/01 08:28:40 bostic 8 7
c set ignore; lint fluff
e
s 00002/00002/00130
d D 5.4 86/02/20 11:29:36 karels 7 6
c typo
e
s 00007/00003/00125
d D 5.3 86/02/13 17:37:29 karels 6 5
c bug fix from RSanders@usgs2-multics.arpa
e
s 00014/00015/00114
d D 5.2 86/02/11 19:31:58 karels 5 4
c grot!  what is this timeout for?  ignore syslog pri's
e
s 00010/00001/00119
d D 5.1 85/06/05 09:20:13 dist 4 3
c Add copyright
e
s 00004/00002/00116
d D 4.3 85/03/05 13:43:44 serge 3 2
c exit if can't open scratch file
e
s 00001/00001/00117
d D 4.2 83/01/02 14:56:34 sam 2 1
c sun
e
s 00118/00000/00000
d D 4.1 82/03/01 00:59:39 wnj 1 0
c date and time created 82/03/01 00:59:39 by wnj
e
u
U
t
T
I 1
D 4
static char *sccsid = "%W% (Berkeley) %E%";
E 4
I 4
D 11
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
/*-
D 12
 * Copyright (c) 1986, 1989 The Regents of the University of California.
E 12
I 12
D 21
 * Copyright (c) 1991 The Regents of the University of California.
E 12
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 12
 * %sccs.include.proprietary.c%
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
 */

#ifndef lint
I 11
D 21
char copyright[] =
D 12
"%Z% Copyright (c) 1986, 1989 The Regents of the University of California.\n\
E 12
I 12
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 12
 All rights reserved.\n";
E 21
I 21
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 21
#endif /* not lint */

#ifndef lint
E 11
static char sccsid[] = "%W% (Berkeley) %G%";
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11

E 4
D 12
/*
 *	Suck up system messages
 *	dmesg
 *		print current buffer
 *	dmesg -
 *		print and update incremental history
 */

D 9
#include <stdio.h>
E 9
#include <sys/param.h>
D 9
#include <nlist.h>
#include <signal.h>
E 9
I 9
#include <sys/signal.h>
E 9
I 5
#include <sys/file.h>
E 5
#include <sys/vm.h>
E 12
I 12
#include <sys/cdefs.h>
E 12
#include <sys/msgbuf.h>
I 18

E 18
I 16
#include <fcntl.h>
I 18
#include <kvm.h>
E 18
#include <limits.h>
E 16
I 12
D 18
#include <time.h>
E 18
E 12
I 9
#include <nlist.h>
I 12
D 18
#include <kvm.h>
#include <stdlib.h>
E 18
E 12
#include <stdio.h>
I 18
#include <stdlib.h>
#include <time.h>
E 18
D 12
#include "pathnames.h"
E 12
I 12
D 16
#include <ctype.h>
E 16
I 16
#include <unistd.h>
#include <vis.h>
E 16
E 12
E 9

D 12
struct	msgbuf msgbuf;
char	*msgbufp;
int	sflg;
int	of	= -1;

struct	msgbuf omesg;
struct	nlist nl[2] = {
E 12
I 12
struct nlist nl[] = {
#define	X_MSGBUF	0
E 12
D 14
	{ "_msgbuf" },
E 14
I 14
	{ "_msgbufp" },
E 14
D 2
	{ 0 }
E 2
I 2
D 12
	{ "" }
E 12
I 12
	{ NULL },
E 12
E 2
};

I 12
D 16
void usage(), vputc();
E 16
D 18
void err __P((const char *, ...));
E 18
I 16
void usage __P((void));
E 16

I 16
#define	KREAD(addr, var) \
D 17
	kvm_read(kd, addr, (void *)&var, sizeof(var)) != sizeof(var)
E 17
I 17
	kvm_read(kd, addr, &var, sizeof(var)) != sizeof(var)
E 17

int
E 16
E 12
main(argc, argv)
D 12
char **argv;
E 12
I 12
	int argc;
D 16
	char **argv;
E 16
I 16
	char *argv[];
E 16
E 12
{
D 12
	int mem;
	register char *mp, *omp, *mstart;
D 5
	int timeout();
	int samef;
E 5
I 5
D 8
	int samef, sawnl, ignore;
E 8
I 8
	int samef, sawnl, ignore = 0;
E 12
I 12
	register int ch, newl, skip;
	register char *p, *ep;
D 14
	struct msgbuf cur;
E 14
I 14
	struct msgbuf *bufp, cur;
E 14
D 13
	char *core, *namelist;
E 13
I 13
	char *memf, *nlistf;
I 16
	kvm_t *kd;
D 20
	char buf[_POSIX2_LINE_MAX];
E 20
I 20
	char buf[5];
E 20
E 16
E 13
E 12
E 8
E 5

D 5
	signal(SIGALRM, timeout);
	alarm(30);
E 5
D 12
	if (argc>1 && argv[1][0] == '-') {
		sflg++;
		argc--;
		argv++;
	}
	if (sflg) {
D 5
		of = open("/usr/adm/msgbuf", 2);
E 5
I 5
D 9
		of = open("/usr/adm/msgbuf", O_RDWR | O_CREAT, 0644);
E 9
I 9
		of = open(_PATH_MSGBUF, O_RDWR | O_CREAT, 0644);
E 9
E 5
I 3
		if (of < 0)
D 9
			done("Can't open /usr/adm/msgbuf\n");
E 9
I 9
			done("Can't open msgbuf file\n");
E 9
E 3
		read(of, (char *)&omesg, sizeof(omesg));
		lseek(of, 0L, 0);
	}
	sflg = 0;
D 9
	nlist(argc>2? argv[2]:"/vmunix", nl);
E 9
I 9
D 10
	nlist(argc>2? argv[2]:_PATH_VMUNIX, nl);
E 10
I 10
	nlist(argc>2? argv[2]:_PATH_UNIX, nl);
E 10
E 9
	if (nl[0].n_type==0)
D 3
		done("No namelist\n");
E 3
I 3
		done("Can't get kernel namelist\n");
E 3
D 9
	if ((mem = open((argc>1? argv[1]: "/dev/kmem"), 0)) < 0)
E 9
I 9
	if ((mem = open((argc>1? argv[1]: _PATH_KMEM), 0)) < 0)
E 9
D 3
		done("No mem\n");
E 3
I 3
		done("Can't read kernel memory\n");
E 3
	lseek(mem, (long)nl[0].n_value, 0);
	read(mem, &msgbuf, sizeof (msgbuf));
	if (msgbuf.msg_magic != MSG_MAGIC)
		done("Magic number wrong (namelist mismatch?)\n");
I 6
	if (msgbuf.msg_bufx >= MSG_BSIZE)
		msgbuf.msg_bufx = 0;
D 7
	if (omsgbuf.msg_bufx >= MSG_BSIZE)
		omsgbuf.msg_bufx = 0;
E 7
I 7
	if (omesg.msg_bufx >= MSG_BSIZE)
		omesg.msg_bufx = 0;
E 7
E 6
	mstart = &msgbuf.msg_bufc[omesg.msg_bufx];
	omp = &omesg.msg_bufc[msgbuf.msg_bufx];
	mp = msgbufp = &msgbuf.msg_bufc[msgbuf.msg_bufx];
	samef = 1;
	do {
		if (*mp++ != *omp++) {
			mstart = msgbufp;
			samef = 0;
			pdate();
			printf("...\n");
E 12
I 12
D 13
	core = namelist = NULL;
E 13
I 13
	memf = nlistf = NULL;
E 13
	while ((ch = getopt(argc, argv, "M:N:")) != EOF)
		switch(ch) {
		case 'M':
D 13
			core = optarg;
E 13
I 13
			memf = optarg;
E 13
E 12
			break;
I 12
		case 'N':
D 13
			namelist = optarg;
E 13
I 13
			nlistf = optarg;
E 13
			break;
		case '?':
		default:
			usage();
E 12
		}
D 6
		if (mp == &msgbuf.msg_bufc[MSG_BSIZE])
E 6
I 6
D 12
		if (mp >= &msgbuf.msg_bufc[MSG_BSIZE])
E 6
			mp = msgbuf.msg_bufc;
D 6
		if (omp == &omesg.msg_bufc[MSG_BSIZE])
E 6
I 6
		if (omp >= &omesg.msg_bufc[MSG_BSIZE])
E 6
			omp = omesg.msg_bufc;
	} while (mp != mstart);
	if (samef && omesg.msg_bufx == msgbuf.msg_bufx)
		exit(0);
	mp = mstart;
I 5
	pdate();
	sawnl = 1;
E 5
	do {
D 5
		pdate();
		if (*mp && (*mp & 0200) == 0)
E 5
I 5
		if (sawnl && *mp == '<')
			ignore = 1;
		if (*mp && (*mp & 0200) == 0 && !ignore)
E 5
			putchar(*mp);
I 5
		if (ignore && *mp == '>')
			ignore = 0;
		sawnl = (*mp == '\n');
E 5
		mp++;
D 6
		if (mp == &msgbuf.msg_bufc[MSG_BSIZE])
E 6
I 6
		if (mp >= &msgbuf.msg_bufc[MSG_BSIZE])
E 6
			mp = msgbuf.msg_bufc;
	} while (mp != msgbufp);
	done((char *)NULL);
E 12
I 12
	argc -= optind;
	argv += optind;

I 13
	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (memf != NULL || nlistf != NULL)
		setgid(getgid());

E 13
	/* Read in kernel message buffer, do sanity checks. */
D 13
	if (kvm_openfiles(namelist, core, NULL) == -1)
E 13
I 13
D 16
	if (kvm_openfiles(nlistf, memf, NULL) == -1)
E 13
		err("kvm_openfiles: %s", kvm_geterr());
	if (kvm_nlist(nl) == -1)
		err("kvm_nlist: %s", kvm_geterr());
E 16
I 16
D 20
	buf[0] = 0;
	kd = kvm_open(nlistf, memf, NULL, O_RDONLY, buf);
	if (kd == NULL)
D 18
		err("kvm_open: %s", buf);
E 18
I 18
		errx(1, "kvm_open: %s", buf);
E 20
I 20
	if ((kd = kvm_open(nlistf, memf, NULL, O_RDONLY, "dmesg")) == NULL)
		exit (1);
E 20
E 18
	if (kvm_nlist(kd, nl) == -1)
D 18
		err("kvm_nlist: %s", kvm_geterr(kd));
E 18
I 18
		errx(1, "kvm_nlist: %s", kvm_geterr(kd));
E 18
E 16
	if (nl[X_MSGBUF].n_type == 0)
D 13
		err("msgbuf not found namelist");
E 13
I 13
D 14
		err("s: msgbuf not found", nlistf ? nlistf : "namelist");
E 14
I 14
D 15
		err("s: msgbufp not found", nlistf ? nlistf : "namelist");
E 15
I 15
D 18
		err("%s: msgbufp not found", nlistf ? nlistf : "namelist");
E 18
I 18
		errx(1, "%s: msgbufp not found", nlistf ? nlistf : "namelist");
E 18
E 15
E 14
E 13
D 16

D 14
        kvm_read((void *)nl[X_MSGBUF].n_value, (void *)&cur, sizeof(cur));
E 14
I 14
        kvm_read((void *)nl[X_MSGBUF].n_value, (void *)&bufp, sizeof(bufp));
        kvm_read((void *)bufp, (void *)&cur, sizeof(cur));
E 16
I 16
	if (KREAD(nl[X_MSGBUF].n_value, bufp) || KREAD((long)bufp, cur))
D 18
		err("kvm_read: %s", kvm_geterr(kd));
E 18
I 18
		errx(1, "kvm_read: %s", kvm_geterr(kd));
E 18
	kvm_close(kd);
E 16
E 14
	if (cur.msg_magic != MSG_MAGIC)
D 18
		err("magic number incorrect");
E 18
I 18
		errx(1, "magic number incorrect");
E 18
	if (cur.msg_bufx >= MSG_BSIZE)
		cur.msg_bufx = 0;

	/*
	 * The message buffer is circular; start at the read pointer, and
	 * go to the write pointer - 1.
	 */
	p = cur.msg_bufc + cur.msg_bufx;
	ep = cur.msg_bufc + cur.msg_bufx - 1;
	for (newl = skip = 0; p != ep; ++p) {
		if (p == cur.msg_bufc + MSG_BSIZE)
			p = cur.msg_bufc;
		ch = *p;
		/* Skip "\n<.*>" syslog sequences. */
		if (skip) {
			if (ch == '>')
				newl = skip = 0;
			continue;
		}
		if (newl && ch == '<') {
			skip = 1;
			continue;
		}
		if (ch == '\0')
			continue;
D 16
		newl = (ch = *p) == '\n';
		vputc(ch);
E 16
I 16
		newl = ch == '\n';
D 18
		(void) vis(buf, ch, 0, 0);
E 18
I 18
		(void)vis(buf, ch, 0, 0);
E 18
		if (buf[1] == 0)
D 18
			(void) putchar(buf[0]);
E 18
I 18
			(void)putchar(buf[0]);
E 18
		else
D 18
			(void) fputs(buf, stdout);
E 18
I 18
			(void)printf("%s", buf);
E 18
E 16
	}
	if (!newl)
		(void)putchar('\n');
	exit(0);
E 12
D 16
}

D 12
done(s)
char *s;
E 12
I 12
void
vputc(ch)
	register int ch;
E 12
{
D 8
	register char *p, *q;

E 8
D 5
	if (s && s!=(char *)omesg.msg_magic && sflg==0) {
E 5
I 5
D 12
	if (s) {
E 5
		pdate();
		printf(s);
D 5
	}
	write(of, (char *)&msgbuf, sizeof(msgbuf));
E 5
I 5
	} else if (of != -1)
		write(of, (char *)&msgbuf, sizeof(msgbuf));
E 5
	exit(s!=NULL);
E 12
I 12
	int meta;

	if (!isascii(ch)) {
		(void)putchar('M');
		(void)putchar('-');
		ch = toascii(ch);
		meta = 1;
	} else
		meta = 0;
	if (isprint(ch) || !meta && (ch == ' ' || ch == '\t' || ch == '\n'))
		(void)putchar(ch);
	else {
		(void)putchar('^');
		(void)putchar(ch == '\177' ? '?' : ch | 0100);
	}
E 16
E 12
D 18
}

D 12
pdate()
E 12
I 12
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
E 12
{
D 12
	extern char *ctime();
	static firstime;
	time_t tbuf;
E 12
I 12
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "dmesg: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 18
}
E 12

D 12
	if (firstime==0) {
		firstime++;
		time(&tbuf);
		printf("\n%.12s\n", ctime(&tbuf)+4);
	}
E 12
I 12
void
usage()
{
	(void)fprintf(stderr, "usage: dmesg [-M core] [-N system]\n");
	exit(1);
E 12
D 5
}

timeout()
{
	done("Buffer file screwed up\n");
E 5
}
E 1
