h05288
s 00033/00034/00272
d D 8.3 95/01/23 09:28:41 pendry 21 20
c knf.  use err/warn.
c update to deal with tapes > 2GB.
e
s 00027/00019/00279
d D 8.2 94/04/17 21:38:11 mckusick 20 19
c add -x option to output all messages to standard out
e
s 00005/00005/00293
d D 8.1 93/06/06 16:31:18 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00015/00271
d D 5.17 92/08/31 12:57:47 bostic 18 17
c ANSI prototypes
e
s 00003/00003/00283
d D 5.16 91/11/11 11:48:18 bostic 17 16
c minor cleanup of include files
e
s 00002/00002/00284
d D 5.15 90/11/05 18:30:46 karels 16 15
c not everyone lets you use ">=" on emums!
e
s 00001/00011/00285
d D 5.14 90/06/01 17:43:41 bostic 15 14
c new copyright notice
e
s 00004/00001/00292
d D 5.13 90/01/02 09:54:43 bostic 14 13
c new signals
e
s 00005/00007/00288
d D 5.12 89/05/11 09:39:22 bostic 13 12
c file reorg, pathnames.h, paths.h
e
s 00012/00009/00283
d D 5.11 88/11/02 09:53:33 bostic 12 11
c print out why it failed
e
s 00002/00005/00290
d D 5.10 88/09/22 17:35:00 bostic 11 10
c fix for ANSI C
e
s 00002/00001/00293
d D 5.9 88/07/06 12:24:12 bostic 10 9
c don't open target for writing if we're just verifying the tapes
e
s 00010/00005/00284
d D 5.8 88/06/29 21:51:09 bostic 9 7
c install approved copyright notice
e
s 00002/00002/00287
d D 5.7.1.1 88/05/06 17:09:47 bostic 8 7
c version to work with old compiler for tahoe release
e
s 00175/00077/00114
d D 5.7 88/05/04 22:17:49 bostic 7 6
c add verification, getopt, lots of changes
e
s 00019/00013/00172
d D 5.6 87/12/04 18:52:48 bostic 6 5
c add Berkeley header; make lint happier
e
s 00004/00001/00181
d D 5.5 87/04/09 12:10:18 karels 5 4
c only retry reads on EINVAL
e
s 00123/00084/00059
d D 5.4 87/04/09 11:09:01 karels 4 3
c various fixes, print blksize at start of run, etc.
e
s 00001/00001/00142
d D 5.3 86/06/17 10:42:52 bloom 3 2
c fix argc checks
e
s 00031/00028/00112
d D 5.2 85/12/11 18:29:28 bloom 2 1
c allow one program to both print tape lengths and copy tapes
e
s 00140/00000/00000
d D 5.1 85/09/20 10:35:35 bloom 1 0
c date and time created 85/09/20 10:35:35 by bloom
e
u
U
f b 
t
T
I 1
/*
D 4
 * Copyright (c) 1985 Regents of the University of California.
E 4
I 4
D 19
 * Copyright (c) 1985, 1987 Regents of the University of California.
E 4
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 19
I 19
D 21
 * Copyright (c) 1985, 1987, 1993
E 21
I 21
 * Copyright (c) 1985, 1987, 1993, 1995
E 21
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 15
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 9
E 6
 */

#ifndef lint
D 19
char copyright[] =
D 4
"%Z% Copyright (c) 1985 Regents of the University of California.\n\
E 4
I 4
D 6
"@(#) Copyright (c) 1985, 1987 Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1985, 1987 Regents of the University of California.\n\
E 6
E 4
 All rights reserved.\n";
E 19
I 19
static char copyright[] =
"%Z% Copyright (c) 1985, 1987, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 19
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

D 13
#include <stdio.h>
I 2
#include <signal.h>
E 2
#include <sys/file.h>
E 13
#include <sys/types.h>
I 18
#include <sys/stat.h>
E 18
I 13
D 17
#include <sys/signal.h>
#include <sys/file.h>
E 17
E 13
#include <sys/ioctl.h>
#include <sys/mtio.h>
I 5
D 17
#include <sys/errno.h>
E 17
I 17
D 18
#include <signal.h>
#include <fcntl.h>
E 18
I 18

I 21
#include <err.h>
E 21
E 18
#include <errno.h>
I 18
#include <fcntl.h>
#include <signal.h>
E 18
E 17
I 13
#include <stdio.h>
I 18
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

E 18
#include "pathnames.h"
E 13
E 5

D 4
#define SIZE	(64 * 1024)
E 4
I 4
D 7
#define MAXREC	(64 * 1024)
#define NOCOUNT	(-2)
E 7
I 7
#define	MAXREC	(64 * 1024)
#define	NOCOUNT	(-2)

E 7
D 13
#undef DEFTAPE
#define	DEFTAPE	"/dev/rmt0"
E 4

E 13
D 4
char buff[SIZE];
int filen=1;
long count, lcount;
int RUBOUT();
long itol();
int nfile;
long size, tsize;
int ln;
char *inf, *outf;
I 2
int copy;
E 4
I 4
D 7
char	*buff;
char	*inf = DEFTAPE;
int	maxblk = MAXREC;
int	filen;
long	record, lastrec;
int	intr();
D 6
long	itol();
E 6
char	*malloc();
long	size, tsize;
int	nfile;
int	lastread;
int	copy;
I 5
extern	int errno;
E 7
I 7
int	filen, guesslen, maxblk = MAXREC;
D 21
long	lastrec, record, size, tsize;
E 21
I 21
long	lastrec, record;
off_t	size, tsize;
E 21
I 20
FILE	*msg = stdout;
E 20
E 7
E 5
E 4
E 2

I 18
void	*getspace __P((int));
void	 intr __P((int));
void	 usage __P((void));
void	 verify __P((int, int, char *));
void	 writeop __P((int, int));

int
E 18
main(argc, argv)
D 6
char **argv;
E 6
I 6
	int argc;
D 18
	char **argv;
E 18
I 18
	char *argv[];
E 18
E 6
{
D 4
	register n, nw, inp, outp;
E 4
I 4
D 7
	register nread, nw, inp, outp;
E 4
	struct mtop op;
I 4
	int needeof = 0, guesslen = 1;
E 7
I 7
D 18
	extern char *optarg;
	extern int optind, errno;
E 18
D 21
	register int lastnread, nread, nw, inp, outp;
E 21
I 21
	int ch, needeof, nw, inp, outp;
	ssize_t lastnread, nread;
E 21
	enum {READ, VERIFY, COPY, COPYVERIFY} op = READ;
D 14
	int ch, needeof, intr(), (*oldsig)();
E 14
I 14
	sig_t oldsig;
D 21
	int ch, needeof;
E 21
E 14
D 18
	char *buff, *inf, *getspace();
I 14
	void intr();
E 18
I 18
	char *buff, *inf;
E 18
E 14
E 7
E 4

D 2
	if (argc != 3) {
		fprintf(stderr, "Usage: tcopy src dest\n");
E 2
I 2
D 3
	if (argc <=1 || argc >= 3) {
E 3
I 3
D 4
	if (argc <=1 || argc > 3) {
E 3
		fprintf(stderr, "Usage: tcopy src [dest]\n");
E 4
I 4
D 7
	while (argc > 1 && *argv[1] == '-') {
		switch (*++argv[1]) {
E 7
I 7
	guesslen = 1;
D 20
	while ((ch = getopt(argc, argv, "cs:v")) != EOF)
E 20
I 20
	while ((ch = getopt(argc, argv, "cs:vx")) != EOF)
E 20
		switch((char)ch) {
		case 'c':
			op = COPYVERIFY;
			break;
E 7
		case 's':
D 7
			if (argc < 3)
				goto usage;
			maxblk = atoi(argv[2]);
E 7
I 7
			maxblk = atoi(optarg);
E 7
			if (maxblk <= 0) {
D 7
				fprintf(stderr, "illegal block size\n");
				goto usage;
E 7
I 7
D 12
				fputs("tcopy: illegal block size\n", stderr);
E 12
I 12
D 21
				fprintf(stderr, "tcopy: illegal block size\n");
E 21
I 21
				warnx("illegal block size");
E 21
E 12
				usage();
E 7
			}
D 7
			argc--;
			argv++;
E 7
			guesslen = 0;
			break;
I 7
		case 'v':
			op = VERIFY;
			break;
I 20
		case 'x':
			msg = stderr;
			break;
E 20
		case '?':
		default:
			usage();
E 7
		}
D 7
		argc--;
		argv++;
E 7
I 7
	argc -= optind;
	argv += optind;

	switch(argc) {
	case 0:
		if (op != READ)
			usage();
D 13
		inf = DEFTAPE;
E 13
I 13
		inf = _PATH_DEFTAPE;
E 13
		break;
	case 1:
		if (op != READ)
			usage();
		inf = argv[0];
		break;
	case 2:
		if (op == READ)
			op = COPY;
		inf = argv[0];
D 10
		if ((outp = open(argv[1], O_RDWR, 0666)) < 0) {
E 10
I 10
D 20
		if ((outp = open(argv[1], op == VERIFY ? O_RDONLY : O_RDWR,
D 18
		    0666)) < 0) {
E 18
I 18
		    DEFFILEMODE)) < 0) {
E 20
I 20
		if ((outp = open(argv[1], op == VERIFY ? O_RDONLY :
		    op == COPY ? O_WRONLY : O_RDWR, DEFFILEMODE)) < 0) {
E 20
E 18
E 10
D 21
			perror(argv[1]);
			exit(3);
E 21
I 21
			err(3, argv[1]);
E 21
		}
		break;
	default:
		usage();
E 7
	}
D 7
	if (argc < 1 || argc > 3) {
usage:
		fprintf(stderr, "Usage: tcopy [-s maxblk] src [dest]\n");
E 4
E 2
		exit(1);
	}
D 4
	inf = argv[1];
D 2
	outf = argv[2];
E 2
I 2
	if (argc == 3) {
		outf = argv[2];
		copy = 1;
	}
E 2
	if ((inp=open(inf, O_RDONLY, 0666)) < 0) {
		fprintf(stderr,"Can't open %s\n", inf);
E 4
I 4
	if (argc > 1)
		inf = argv[1];
E 7
I 7

E 7
D 21
	if ((inp = open(inf, O_RDONLY, 0)) < 0) {
		perror(inf);
E 4
		exit(1);
	}
E 21
I 21
	if ((inp = open(inf, O_RDONLY, 0)) < 0)
		err(1, inf);
E 21
D 2
	op.mt_op = MTREW;
	op.mt_count = (daddr_t)1;
	if(ioctl(inp, MTIOCTOP, &op) < 0) {
		perror(inf);
		exit(2);
E 2
I 2
D 4
	if (copy) {
		if ((outp=open(outf, O_WRONLY, 0666)) < 0) {
			fprintf(stderr,"Can't open %s\n", outf);
E 4
I 4
D 7
	if (argc == 3) {
		copy = 1;
		if ((outp = open(argv[2], O_WRONLY, 0666)) < 0) {
			perror(argv[2]);
E 4
			exit(3);
		}
E 7
I 7

	buff = getspace(maxblk);

	if (op == VERIFY) {
		verify(inp, outp, buff);
		exit(0);
E 7
E 2
	}
D 2
	if ((outp=open(outf, O_WRONLY, 0666)) < 0) {
		fprintf(stderr,"Can't open %s\n", outf);
		exit(3);
	}
	if(ioctl(outp, MTIOCTOP, &op) < 0) {
		perror(inf);
		exit(4);
	}
	if (signal(2, 1) != 1)
		signal(2, RUBOUT);
E 2
I 2
D 7
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
E 7
I 7

	if ((oldsig = signal(SIGINT, SIG_IGN)) != SIG_IGN)
E 7
D 4
		(void) signal(SIGINT, RUBOUT);
E 2
	ln = -2;
E 4
I 4
		(void) signal(SIGINT, intr);
D 6
	buff = malloc(maxblk);
E 6
I 6
D 7
	buff = malloc((u_int)maxblk);
E 6
	if (buff == NULL) {
D 6
		fprintf("tcopy: no memory\n");
E 6
I 6
		fprintf(stderr, "tcopy: no memory\n");
E 6
		exit(11);
	}
	lastread = NOCOUNT;
E 4
	for (;;) {
D 4
		count++;
		n = read(inp, buff, SIZE);
		if (n > 0) {
		    nw = write(outp, buff, n);
D 2
		    if (nw != n) {
			fprintf(stderr, "write (%d) != read (%d)\n", nw, n);
			fprintf(stderr, "COPY Aborted\n");
			exit(5);
E 2
I 2
		    if (copy) {
			    if (nw != n) {
				fprintf(stderr, "write (%d) != read (%d)\n",
					nw, n);
				fprintf(stderr, "COPY Aborted\n");
				exit(5);
			    }
E 2
		    }
		    size += n;
		    if (n != ln) {
			if (ln > 0)
			    if (count - lcount > 1)
				printf("file %d: records %ld to %ld: size %d\n",
					filen, lcount, count-1, ln);
			    else
				printf("file %d: record %ld: size %d\n",
					filen, lcount, ln);
			ln = n;
			lcount = count;
		    }
E 4
I 4
		nread = read(inp, buff, maxblk);
		if (nread == -1) {
D 5
			if (guesslen && maxblk > MAXREC / 2) {
E 5
I 5
			if (errno == EINVAL && guesslen &&
			    maxblk > MAXREC / 2) {
E 5
				maxblk -= 1024;
				continue;
E 7
I 7

	needeof = 0;
	for (lastnread = NOCOUNT;;) {
		if ((nread = read(inp, buff, maxblk)) == -1) {
			while (errno == EINVAL && (maxblk -= 1024)) {
				nread = read(inp, buff, maxblk);
				if (nread >= 0)
					goto r1;
E 7
			}
D 6
			fprintf(stderr, "read error, file %d, record %d: ",
E 6
I 6
D 21
			fprintf(stderr, "read error, file %d, record %ld: ",
E 21
I 21
			err(1, "read error, file %d, record %ld",
E 21
E 6
			    filen, record);
D 21
			perror("");
D 7
		} else if (nread != lastread) {
			if (lastread != 0 && lastread != NOCOUNT) {
E 7
I 7
			exit(1);
E 21
		} else if (nread != lastnread) {
			if (lastnread != 0 && lastnread != NOCOUNT) {
E 7
				if (lastrec == 0 && nread == 0)
D 6
					printf("%d records\n", record);
E 6
I 6
D 20
					printf("%ld records\n", record);
E 20
I 20
					fprintf(msg, "%ld records\n", record);
E 20
E 6
				else if (record - lastrec > 1)
D 20
					printf("records %ld to %ld\n",
E 20
I 20
					fprintf(msg, "records %ld to %ld\n",
E 20
					    lastrec, record);
				else
D 20
					printf("record %ld\n", lastrec);
E 20
I 20
					fprintf(msg, "record %ld\n", lastrec);
E 20
			}
			if (nread != 0)
D 20
				printf("file %d: block size %d: ",
E 20
I 20
				fprintf(msg, "file %d: block size %d: ",
E 20
				    filen, nread);
D 6
			fflush(stdout);
E 6
I 6
			(void) fflush(stdout);
E 6
			lastrec = record;
E 4
		}
D 4
		else {
			if (ln <= 0 && ln != -2) {
E 4
I 4
D 7
		guesslen = 0;
E 7
I 7
r1:		guesslen = 0;
E 7
		if (nread > 0) {
D 7
			if (copy) {
E 7
I 7
D 8
D 16
			if (op >= COPY) {
E 16
I 16
			if (op == COPY || op == COPYVERIFY) {
E 16
E 8
I 8
			if (op == COPY || op == COPYVERIFY) {
E 8
E 7
				if (needeof) {
D 7
				    op.mt_op = MTWEOF;
				    op.mt_count = (daddr_t) 1;
				    if (ioctl(outp, MTIOCTOP, (char *)&op) < 0) {
					    perror("write tape mark");
					    exit(6);
				    }
				    needeof = 0;
E 7
I 7
					writeop(outp, MTWEOF);
					needeof = 0;
E 7
				}
				nw = write(outp, buff, nread);
				if (nw != nread) {
I 21
				    int error = errno;
E 21
				    fprintf(stderr,
D 6
					"write error, file %d, record %d: ",
E 6
I 6
					"write error, file %d, record %ld: ",
E 6
					filen, record);
				    if (nw == -1)
D 21
					perror("");
E 21
I 21
					fprintf(stderr,
						": %s", strerror(error));
E 21
				    else
					fprintf(stderr,
					    "write (%d) != read (%d)\n",
					    nw, nread);
				    fprintf(stderr, "copy aborted\n");
				    exit(5);
				}
			}
			size += nread;
			record++;
		} else {
D 7
			if (lastread <= 0 && lastread != NOCOUNT) {
E 7
I 7
			if (lastnread <= 0 && lastnread != NOCOUNT) {
E 7
E 4
D 20
				printf("eot\n");
E 20
I 20
				fprintf(msg, "eot\n");
E 20
				break;
			}
D 4
			if (ln > 0)
			    if (count - lcount > 1)
				printf("file %d: records %ld to %ld: size %d\n",
					filen, lcount, count-1, ln);
			    else
				printf("file %d: record %ld: size %d\n",
					filen, lcount, ln);
E 4
D 20
			printf("file %d: eof after %ld records: %ld bytes\n",
D 4
				filen, count-1, size);
D 2
			op.mt_op = MTWEOF;
			op.mt_count = (daddr_t)1;
			if(ioctl(outp, MTIOCTOP, &op) < 0) {
				perror("Write EOF");
				exit(6);
E 2
I 2
			if (copy) {
				op.mt_op = MTWEOF;
				op.mt_count = (daddr_t)1;
				if(ioctl(outp, MTIOCTOP, (char *)&op) < 0) {
					perror("Write EOF");
					exit(6);
				}
E 2
			}
E 4
I 4
				filen, record, size);
E 20
I 20
			fprintf(msg,
D 21
			    "file %d: eof after %ld records: %ld bytes\n",
E 21
I 21
			    "file %d: eof after %ld records: %qd bytes\n",
E 21
			    filen, record, size);
E 20
			needeof = 1;
E 4
			filen++;
D 4
			count = 0;
			lcount = 0;
E 4
			tsize += size;
I 4
D 7
			record = 0;
			lastrec = 0;
			lastread = 0;
E 4
			size = 0;
			if (nfile && filen > nfile)
				break;
E 7
I 7
			size = record = lastrec = 0;
			lastnread = 0;
E 7
D 4
			ln = n;
E 4
		}
I 4
D 7
		lastread = nread;
E 7
I 7
		lastnread = nread;
E 7
E 4
	}
D 2
	close(outp);
E 2
I 2
D 7
	if (copy)
		(void) close(outp);
E 7
E 2
D 20
	printf("total length: %ld bytes\n", tsize);
E 20
I 20
D 21
	fprintf(msg, "total length: %ld bytes\n", tsize);
E 21
I 21
	fprintf(msg, "total length: %qd bytes\n", tsize);
E 21
E 20
I 7
	(void)signal(SIGINT, oldsig);
D 8
D 16
	if (op >= COPY) {
E 16
I 16
	if (op == COPY || op == COPYVERIFY) {
E 16
E 8
I 8
	if (op == COPY || op == COPYVERIFY) {
E 8
		writeop(outp, MTWEOF);
		writeop(outp, MTWEOF);
		if (op == COPYVERIFY) {
			writeop(outp, MTREW);
			writeop(inp, MTREW);
			verify(inp, outp, buff);
		}
	}
	exit(0);
E 7
}

I 18
void
E 18
I 7
D 11
static
E 11
verify(inp, outp, outb)
D 21
	register int inp, outp;
	register char *outb;
E 21
I 21
	int inp, outp;
	char *outb;
E 21
{
I 11
D 18
	extern int errno;
E 18
E 11
D 21
	register int eot, inmaxblk, inn, outmaxblk, outn;
	register char *inb;
E 21
I 21
	int eot, inmaxblk, inn, outmaxblk, outn;
	char *inb;
E 21
D 18
	char *getspace();
E 18

	inb = getspace(maxblk);
	inmaxblk = outmaxblk = maxblk;
	for (eot = 0;; guesslen = 0) {
		if ((inn = read(inp, inb, inmaxblk)) == -1) {
			if (guesslen)
				while (errno == EINVAL && (inmaxblk -= 1024)) {
					inn = read(inp, inb, inmaxblk);
					if (inn >= 0)
						goto r1;
				}
D 21
			perror("tcopy: read error");
E 21
I 21
			warn("read error");
E 21
D 12
			exit(1);
E 12
I 12
			break;
E 12
		}
r1:		if ((outn = read(outp, outb, outmaxblk)) == -1) {
			if (guesslen)
				while (errno == EINVAL && (outmaxblk -= 1024)) {
					outn = read(outp, outb, outmaxblk);
					if (outn >= 0)
						goto r2;
				}
D 21
			perror("tcopy: read error");
E 21
I 21
			warn("read error");
E 21
D 12
			exit(1);
E 12
I 12
			break;
E 12
		}
D 12
r2:		if (inn != outn)
E 12
I 12
r2:		if (inn != outn) {
D 20
			printf("tcopy: tapes have different block sizes; %d != %d.\n", inn, outn);
E 20
I 20
			fprintf(msg,
			    "%s: tapes have different block sizes; %d != %d.\n",
			    "tcopy", inn, outn);
E 20
E 12
			break;
I 12
		}
E 12
		if (!inn) {
			if (eot++) {
D 12
				puts("tcopy: tapes are identical.");
E 12
I 12
D 20
				printf("tcopy: tapes are identical.\n");
E 20
I 20
D 21
				fprintf(msg, "tcopy: tapes are identical.\n");
E 21
I 21
				fprintf(msg, "%s: tapes are identical.\n",
					"tcopy");
E 21
E 20
E 12
				return;
			}
		} else {
D 12
			if (bcmp(inb, outb, inn))
E 12
I 12
			if (bcmp(inb, outb, inn)) {
D 20
				printf("tcopy: tapes have different data.\n");
E 20
I 20
				fprintf(msg,
D 21
				    "tcopy: tapes have different data.\n");
E 21
I 21
				    "%s: tapes have different data.\n",
					"tcopy");
E 21
E 20
E 12
				break;
I 12
			}
E 12
			eot = 0;
		}
	}
D 12
	puts("tcopy: tapes are different.");
E 12
	exit(1);
}

I 14
void
E 14
D 11
static
E 11
E 7
D 4
RUBOUT()
E 4
I 4
D 18
intr()
E 18
I 18
intr(signo)
	int signo;
E 18
E 4
{
D 4
	if (count > lcount)
		--count;
	if (count)
		if (count > lcount)
			printf("file %d: records %ld to %ld: size %d\n",
				filen, lcount, count, ln);
E 4
I 4
	if (record)
		if (record - lastrec > 1)
D 20
			printf("records %ld to %ld\n", lastrec, record);
E 20
I 20
			fprintf(msg, "records %ld to %ld\n", lastrec, record);
E 20
E 4
		else
D 4
			printf("file %d: record %ld: size %d\n",
				filen, lcount, ln);
	printf("rubout at file %d: record %ld\n", filen, count);
E 4
I 4
D 20
			printf("record %ld\n", lastrec);
	printf("interrupt at file %d: record %ld\n", filen, record);
E 4
D 7
	printf("total length: %ld bytes\n", tsize+size);
E 7
I 7
	printf("total length: %ld bytes\n", tsize + size);
E 20
I 20
			fprintf(msg, "record %ld\n", lastrec);
	fprintf(msg, "interrupt at file %d: record %ld\n", filen, record);
D 21
	fprintf(msg, "total length: %ld bytes\n", tsize + size);
E 21
I 21
	fprintf(msg, "total length: %qd bytes\n", tsize + size);
E 21
E 20
	exit(1);
}

D 11
static char *
E 11
I 11
D 18
char *
E 18
I 18
void *
E 18
E 11
getspace(blk)
	int blk;
{
D 18
	char *bp, *malloc();
E 18
I 18
	void *bp;
E 18

D 18
	if ((bp = malloc((u_int)blk)) == NULL) {
E 18
I 18
D 21
	if ((bp = malloc((size_t)blk)) == NULL) {
E 18
D 12
		fputs("tcopy: no memory\n", stderr);
E 12
I 12
		fprintf(stderr, "tcopy: no memory\n");
E 12
		exit(11);
	}
E 21
I 21
	if ((bp = malloc((size_t)blk)) == NULL)
		errx(11, "no memory");

E 21
D 18
	return(bp);
E 18
I 18
	return (bp);
E 18
}

I 18
void
E 18
D 11
static
E 11
writeop(fd, type)
	int fd, type;
{
	struct mtop op;

	op.mt_op = type;
	op.mt_count = (daddr_t)1;
D 21
	if (ioctl(fd, MTIOCTOP, (char *)&op) < 0) {
		perror("tcopy: tape op");
		exit(6);
	}
E 21
I 21
	if (ioctl(fd, MTIOCTOP, (char *)&op) < 0)
		err(6, "tape op");
E 21
}

I 18
void
E 18
D 11
static
E 11
usage()
{
I 21

E 21
D 12
	fputs("usage: tcopy [-cv] [-s maxblk] src [dest]\n", stderr);
E 12
I 12
D 20
	fprintf(stderr, "usage: tcopy [-cv] [-s maxblk] src [dest]\n");
E 20
I 20
	fprintf(stderr, "usage: tcopy [-cvx] [-s maxblk] src [dest]\n");
E 20
E 12
E 7
	exit(1);
}
D 4

E 4
E 1
