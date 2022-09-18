h03407
s 00005/00005/00137
d D 8.1 93/06/06 16:31:37 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00053/00023/00089
d D 5.13 91/12/16 15:40:06 bostic 19 18
c ANSI stuff, use err() routine so error messages are right; nothing important
e
s 00003/00002/00109
d D 5.12 91/12/16 14:37:00 torek 18 17
c read 8k blocks (4.3BSD-reno/usr.bin/29)
e
s 00008/00007/00103
d D 5.11 91/05/06 15:38:36 bostic 17 15
c create files with the default file mode; ANSI cleanups
e
s 00007/00005/00105
d R 5.11 91/05/06 15:37:27 bostic 16 15
c create files with default modes; ANSI cleanup
e
s 00001/00011/00109
d D 5.10 90/06/01 17:43:52 bostic 15 14
c new copyright notice
e
s 00003/00002/00117
d D 5.9 89/12/06 16:01:40 bostic 14 13
c use unistd.h names for stdin/stdout fd's
e
s 00018/00010/00101
d D 5.8 89/08/11 13:13:03 bostic 13 12
c handle short write returns
e
s 00002/00005/00109
d D 5.7 89/08/10 15:42:44 bostic 12 11
c use O_APPEND instead of extra system call
e
s 00057/00023/00057
d D 5.6 89/05/16 11:03:09 bostic 11 10
c POSIX 1003.2 is not going to allow write errors to be ignored; let's
c see if anything breaks.  Also, malloc buffer for future speed
e
s 00065/00085/00015
d D 5.5 88/07/10 14:56:38 bostic 10 9
c writing 16 bytes per device isn't kulturny.  Sam had the right idea.
c written from the POSIX 1003.2 Draft 6 manual page, add Berkeley header
e
s 00079/00041/00021
d D 5.4 85/12/14 20:05:53 sam 9 8
c give up and put back old version, but up buffer sizes
e
s 00001/00001/00061
d D 5.3 85/12/14 19:38:00 sam 8 7
c use read to elminate buffering, fread changes tee's semantics
e
s 00001/00001/00061
d D 5.2 85/10/24 17:56:44 bloom 7 6
c stdout was being overwritten in the list of outputs
e
s 00041/00079/00021
d D 5.1 85/10/01 22:09:50 mckusick 6 5
c version using stdio from sam
e
s 00001/00001/00099
d D 4.4 83/08/19 19:50:35 sam 5 3
c give proper exit status on success
e
s 00001/00000/00100
d R 4.4 83/08/18 15:09:22 sam 4 3
c fix exit status
e
s 00002/00001/00098
d D 4.3 83/05/22 18:32:39 sam 3 2
c pagsiz.h must go....
e
s 00001/00001/00098
d D 4.2 82/03/31 22:45:52 mckusic 2 1
c explicit define BUFSIZ as 1024
e
s 00099/00000/00000
d D 4.1 80/10/01 17:28:53 bill 1 0
c date and time created 80/10/01 17:28:53 by bill
e
u
U
t
T
I 6
D 9
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

E 9
E 6
I 3
D 10
#ifndef lint
I 6
D 9
char copyright[] =
"%Z% Copyright (c) 1985 Regents of the University of California.\n\
 All rights reserved.\n";
#endif not lint

#ifndef lint
E 9
E 6
E 3
I 1
static char *sccsid = "%W% (Berkeley) %G%";
I 3
#endif
E 10
E 3
/*
D 10
 * tee-- pipe fitting
E 10
I 10
D 20
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1988, 1993
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
D 11
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 11
E 10
 */

I 6
D 9
#include <stdio.h>
E 9
E 6
D 10
#include <signal.h>
I 9
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
E 10
I 10
#ifndef lint
D 20
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 20
I 20
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 20
#endif /* not lint */
E 10
E 9
D 6
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
E 6
D 3
#include <pagsiz.h>
E 3

I 9
D 10
#define	BUFSIZ	8192
int openf[20] = { 1 };
int n = 1;
int t = 0;
int aflag;
E 10
I 10
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 10

D 10
char in[BUFSIZ];
E 10
I 10
#include <sys/types.h>
D 17
#include <sys/file.h>
E 17
I 17
#include <sys/stat.h>
D 19
#include <fcntl.h>
E 19
E 17
#include <signal.h>
I 19
#include <errno.h>
#include <fcntl.h>
E 19
D 17
#include <stdio.h>
E 17
I 14
#include <unistd.h>
I 17
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 17
E 14
E 10

I 11
typedef struct _list {
	struct _list *next;
	int fd;
	char *name;
} LIST;
LIST *head;

I 19
void add __P((int, char *));
void err __P((int, const char *, ...));

int
E 19
E 11
D 10
char out[BUFSIZ];

extern errno;
long	lseek();

E 9
D 2
#define	BUFSIZ	BSIZE
E 2
I 2
D 6
#define	BUFSIZ	1024
E 2
int openf[20] = { 1 };
int n = 1;
int t = 0;
int aflag;

char in[BUFSIZ];

char out[BUFSIZ];

extern errno;
long	lseek();

E 6
main(argc,argv)
D 6
char **argv;
E 6
I 6
D 9
	int argc;
	char *argv[];
E 9
I 9
char **argv;
E 10
I 10
main(argc, argv)
	int argc;
D 19
	char **argv;
E 19
I 19
	char *argv[];
E 19
E 10
E 9
E 6
{
D 6
	int register r,w,p;
	struct stat buf;
	while(argc>1&&argv[1][0]=='-') {
		switch(argv[1][1]) {
E 6
I 6
D 9
	register FILE **openf, **lastf, **fdp;
	register i, cc;
	char buf[8192], *calloc();
	int aflag = 0;

	argc--, argv++;
	while (argc > 0 && argv[0][0] == '-') {
		switch (argv[0][1]) {
E 9
I 9
D 10
	int register r,w,p;
	struct stat buf;
	while(argc>1&&argv[1][0]=='-') {
		switch(argv[1][1]) {
E 10
I 10
D 11
	extern int optind;
	register int cnt, n, step;
	int append, ch, *fd;
	char buf[8192], *malloc();
E 11
I 11
D 19
	extern int errno, optind;
E 19
	register LIST *p;
D 13
	register int append, n, fd;
	int ch, exitval;
E 13
I 13
	register int n, fd, rval, wval;
	register char *bp;
	int append, ch, exitval;
E 13
D 17
	char *buf, *malloc(), *strerror();
E 17
I 17
	char *buf;
E 17
E 11
D 19
	off_t lseek();
E 19
I 18
#define	BSIZE (8 * 1024)
E 18

	append = 0;
	while ((ch = getopt(argc, argv, "ai")) != EOF)
		switch((char)ch) {
E 10
E 9
E 6
		case 'a':
D 10
			aflag++;
E 10
I 10
			append = 1;
E 10
			break;
		case 'i':
D 6
		case 0:
E 6
I 6
D 9
		case '\0':
E 9
I 9
D 10
		case 0:
E 9
E 6
			signal(SIGINT, SIG_IGN);
E 10
I 10
			(void)signal(SIGINT, SIG_IGN);
			break;
		case '?':
		default:
D 11
			fprintf(stderr, "usage: tee [-ai] [file ...]\n");
			exit(2);
E 11
I 11
			(void)fprintf(stderr, "usage: tee [-ai] [file ...]\n");
			exit(1);
E 11
E 10
I 6
D 9
			break;
E 9
E 6
		}
D 6
		argv++;
		argc--;
E 6
I 6
D 9
		argv++, argc--;
E 9
I 9
D 10
		argv++;
		argc--;
E 10
I 10
	argv += optind;
	argc -= optind;

D 11
	if (!(fd = (int *)malloc((u_int)((argc + 1) * sizeof(int))))) {
		fprintf(stderr, "tee: out of space.\n");
		exit(2);
E 11
I 11
D 18
	if (!(buf = malloc((u_int)8 * 1024))) {
E 18
I 18
D 19
	if (!(buf = malloc((u_int)BSIZE))) {
E 18
		(void)fprintf(stderr, "tee: out of space.\n");
		exit(1);
E 11
E 10
E 9
E 6
	}
E 19
I 19
	if ((buf = malloc((u_int)BSIZE)) == NULL)
		err(1, "%s", strerror(errno));

E 19
D 6
	fstat(1,&buf);
	t = (buf.st_mode&S_IFMT)==S_IFCHR;
	if(lseek(1,0L,1)==-1&&errno==ESPIPE)
		t++;
	while(argc-->1) {
		if(aflag) {
			openf[n] = open(argv[1],1);
			if(openf[n] < 0)
				openf[n] = creat(argv[1],0666);
			lseek(openf[n++],0L,2);
		} else
			openf[n++] = creat(argv[1],0666);
		if(stat(argv[1],&buf)>=0) {
			if((buf.st_mode&S_IFMT)==S_IFCHR)
				t++;
		} else {
			puts("tee: cannot open ");
			puts(argv[1]);
			puts("\n");
			n--;
		}
		argv++;
E 6
I 6
D 9
	lastf = openf = (FILE **)calloc(argc+1, sizeof (FILE *));
	if (openf == 0) {
		fprintf(stderr, "tee: Out of memory.\n");
		exit(-1);
E 9
I 9
D 10
	fstat(1,&buf);
	t = (buf.st_mode&S_IFMT)==S_IFCHR;
	if(lseek(1,0L,1)==-1&&errno==ESPIPE)
		t++;
	while(argc-->1) {
		if(aflag) {
			openf[n] = open(argv[1],1);
			if(openf[n] < 0)
				openf[n] = creat(argv[1],0666);
			lseek(openf[n++],0L,2);
		} else
			openf[n++] = creat(argv[1],0666);
		if(stat(argv[1],&buf)>=0) {
			if((buf.st_mode&S_IFMT)==S_IFCHR)
				t++;
		} else {
			puts("tee: cannot open ");
			puts(argv[1]);
			puts("\n");
			n--;
E 10
I 10
D 11
	fd[0] = 1;			/* always write to stdout */
	for (cnt = 1; *argv; ++argv)
		if ((fd[cnt] = open(*argv, append ? O_WRONLY|O_CREAT :
		    O_WRONLY|O_CREAT|O_TRUNC, 0600)) < 0) {
			fprintf(stderr, "tee: %s: ", *argv);
			perror((char *)NULL);
E 10
		}
E 11
I 11
D 14
	add(1, "stdout");
E 14
I 14
	add(STDOUT_FILENO, "stdout");
E 14
D 19
	for (; *argv; ++argv)
E 19
I 19

	for (exitval = 0; *argv; ++argv)
E 19
D 12
		if ((fd = open(*argv, append ? O_WRONLY|O_CREAT :
E 12
I 12
		if ((fd = open(*argv, append ? O_WRONLY|O_CREAT|O_APPEND :
E 12
D 17
		    O_WRONLY|O_CREAT|O_TRUNC, 0600)) < 0)
E 17
I 17
D 19
		    O_WRONLY|O_CREAT|O_TRUNC, DEFFILEMODE)) < 0)
E 17
			(void)fprintf(stderr, "tee: %s: %s.\n",
			    *argv, strerror(errno));
E 11
D 10
		argv++;
E 9
E 6
	}
D 6
	r = w = 0;
	for(;;) {
		for(p=0;p<BUFSIZ;) {
			if(r>=w) {
				if(t>0&&p>0) break;
				w = read(0,in,BUFSIZ);
				r = 0;
				if(w<=0) {
					stash(p);
D 5
					return;
E 5
I 5
					exit(0);
E 5
				}
			}
			out[p++] = in[r++];
		}
		stash(p);
E 6
I 6
D 7
	*lastf = stdout;	/* default */
E 7
I 7
D 9
	*lastf++ = stdout;	/* default */
E 7
	for (; argc > 0; argc--, argv++) {
		*lastf = fopen(argv[0], aflag ? "a" : "w");
		if (*lastf == NULL)
			fprintf(stderr, "tee: %s: cannot open.\n", argv[0]);
		else
			lastf++;
E 9
I 9
	r = w = 0;
	for(;;) {
		for(p=0;p<BUFSIZ;) {
			if(r>=w) {
				if(t>0&&p>0) break;
				w = read(0,in,BUFSIZ);
				r = 0;
				if(w<=0) {
					stash(p);
					exit(0);
				}
			}
			out[p++] = in[r++];
E 10
I 10
D 12
		else {
			if (append)
D 11
				(void)lseek(fd[cnt], 0L, L_XTND);
			++cnt;
E 11
I 11
				(void)lseek(fd, 0L, L_XTND);
E 12
I 12
		else
E 19
I 19
		    O_WRONLY|O_CREAT|O_TRUNC, DEFFILEMODE)) < 0) {
			err(0, "%s: %s", *argv, strerror(errno));
			exitval = 1;
		} else
E 19
E 12
			add(fd, *argv);
E 11
E 10
D 12
		}
E 12
D 10
		stash(p);
E 9
E 6
	}
D 6
}

stash(p)
{
	int k;
	int i;
	int d;
	d = t ? 16 : p;
	for(i=0; i<p; i+=d)
		for(k=0;k<n;k++)
			write(openf[k], out+i, d<p-i?d:p-i);
}

puts(s)
char *s;
{
	while(*s)
		write(2,s++,1);
E 6
I 6
D 8
	while ((cc = fread(buf, 1, sizeof (buf), stdin)) > 0)
E 8
I 8
D 9
	while ((cc = read(fileno(stdin), buf, sizeof (buf))) > 0)
E 8
		for (fdp = openf; fdp < lastf; fdp++)
			fwrite(buf, 1, cc, *fdp);
	exit(0);
E 9
I 9
}

stash(p)
{
	int k;
	int i;
	int d;
	d = t ? 16 : p;
	for(i=0; i<p; i+=d)
		for(k=0;k<n;k++)
			write(openf[k], out+i, d<p-i?d:p-i);
}

puts(s)
char *s;
{
	while(*s)
		write(2,s++,1);
E 10
I 10
D 11
	for (--cnt; (n = read(0, buf, sizeof(buf))) > 0;)
		for (step = cnt; step >= 0; --step)
			(void)write(fd[step], buf, n);
	exit(0);
E 11
I 11
D 19
	exitval = 0;
E 19
I 19

E 19
D 13
	while ((n = read(0, buf, sizeof(buf))) > 0)
		for (p = head; p; p = p->next)
			if (write(p->fd, buf, n) != n) {
				(void)fprintf(stderr, "tee: %s: %s.\n",
				    p->name, strerror(errno));
				exitval = 1;
			}
	if (n < 0) {
E 13
I 13
D 14
	while ((rval = read(0, buf, sizeof(buf))) > 0)
E 14
I 14
D 18
	while ((rval = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
E 18
I 18
	while ((rval = read(STDIN_FILENO, buf, BSIZE)) > 0)
E 18
E 14
		for (p = head; p; p = p->next) {
			n = rval;
			bp = buf;
			do {
				if ((wval = write(p->fd, bp, n)) == -1) {
D 19
					(void)fprintf(stderr, "tee: %s: %s.\n",
E 19
I 19
					err(0, "%s: %s",
E 19
					    p->name, strerror(errno));
					exitval = 1;
					break;
				}
				bp += wval;
			} while (n -= wval);
		}
D 19
	if (rval < 0) {
E 13
		(void)fprintf(stderr, "tee: read: %s\n", strerror(errno));
		exit(1);
	}
E 19
I 19
	if (rval < 0)
		err(1, "read: %s", strerror(errno));
E 19
	exit(exitval);
}

I 19
void
E 19
add(fd, name)
	int fd;
	char *name;
{
	LIST *p;
D 17
	char *malloc(), *strerror();
E 17

D 17
	/* NOSTRICT */
	if (!(p = (LIST *)malloc((u_int)sizeof(LIST)))) {
E 17
I 17
D 19
	if (!(p = malloc((u_int)sizeof(LIST)))) {
E 17
		(void)fprintf(stderr, "tee: out of space.\n");
		exit(1);
	}
E 19
I 19
	if ((p = malloc((u_int)sizeof(LIST))) == NULL)
		err(1, "%s", strerror(errno));
E 19
	p->fd = fd;
	p->name = name;
	p->next = head;
	head = p;
I 19
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(int doexit, const char *fmt, ...)
#else
err(doexit, fmt, va_alist)
	int doexit;
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "tee: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	if (doexit)
		exit(1);
E 19
E 11
E 10
E 9
E 6
}
E 1
