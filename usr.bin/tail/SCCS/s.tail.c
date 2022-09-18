h25603
s 00005/00005/00271
d D 8.1 93/06/06 16:30:37 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00276
d D 5.12 92/06/24 09:41:23 bostic 20 19
c delete MAP_FILE, check file size before mmap'ing, print file name on
c error
e
s 00001/00001/00275
d D 5.11 92/06/21 13:41:24 bostic 19 18
c fixes without testing for mmap, lseek, fseek when quads went in
e
s 00020/00019/00256
d D 5.10 92/05/14 15:41:12 bostic 18 17
c flush stdout, rest of tail uses write(2)
e
s 00016/00010/00259
d D 5.9 92/03/04 14:54:19 bostic 17 14
c -f with more than one argument is an error; close files; correct usage
c statement
e
s 00003/00000/00270
d R 5.10 92/03/04 13:57:41 bostic 16 15
c error message if -f and multiple files
e
s 00014/00013/00256
d R 5.9 92/03/04 09:14:17 bostic 15 14
c use stdin instead of another file descriptor; make -[cnb] -r work
c on pipes
e
s 00039/00023/00230
d D 5.8 92/03/03 16:13:36 bostic 14 13
c make tail work like head for multiple files
e
s 00052/00042/00201
d D 5.7 92/02/12 15:50:35 bostic 13 12
c make tail match historic practice for the various arguments
e
s 00004/00002/00239
d D 5.6 91/08/26 12:48:46 bostic 12 11
c null terminate the numeric argument so "+1f" works right
e
s 00207/00205/00034
d D 5.5 91/07/21 14:50:32 bostic 11 10
c new version from scratch; POSIX 1003.2 version
e
s 00008/00007/00231
d D 5.4 91/04/18 18:15:00 bostic 10 9
c new copyright; att/bsd/shared
e
s 00002/00001/00236
d D 5.3 86/11/13 19:51:39 karels 9 8
c stop following if nobody's looking
e
s 00003/00003/00234
d D 5.2 86/01/10 04:24:10 lepreau 8 7
c grow buffer from 8K to 32K.
e
s 00015/00002/00222
d D 5.1 85/05/31 09:34:34 dist 7 6
c Add copyright
e
s 00020/00016/00204
d D 4.6 85/01/14 16:42:57 bloom 6 5
c it lints
e
s 00006/00002/00214
d D 4.5 84/06/07 16:13:23 ralph 5 4
c fix "tail -10b"
e
s 00008/00005/00208
d D 4.4 83/08/22 16:51:46 karels 4 3
c tail +1f starts at begining (not +10)
e
s 00001/00001/00212
d D 4.3 83/07/01 02:46:43 sam 3 2
c trash
e
s 00002/00002/00211
d D 4.2 83/06/02 16:52:11 ralph 2 1
c fixed piped flag to reflect actual file, not stdin.
e
s 00213/00000/00000
d D 4.1 80/10/06 23:53:23 root 1 0
c date and time created 80/10/06 23:53:23 by root
e
u
U
t
T
I 7
D 10
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
/*-
D 11
 * Copyright (c) 1980 The Regents of the University of California.
E 11
I 11
D 21
 * Copyright (c) 1991 The Regents of the University of California.
E 11
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 11
 * %sccs.include.proprietary.c%
E 11
I 11
 * This code is derived from software contributed to Berkeley by
 * Edward Sze-Tyan Wang.
 *
 * %sccs.include.redist.c%
E 11
E 10
 */

E 7
I 6
#ifndef lint
E 6
I 1
D 7
static char *sccsid = "%W% (Berkeley) %G%";
I 6
#endif
E 7
I 7
D 21
char copyright[] =
D 10
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 10
I 10
D 11
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 11
I 11
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 11
E 10
 All rights reserved.\n";
E 21
I 21
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 21
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

E 7
E 6
D 11
/* tail command 
 *
 *	tail where [file]
D 3
 *	where is +_n[type]
E 3
I 3
 *	where is +/-n[type]
E 3
 *	- means n lines before end
 *	+ means nth line from beginning
 *	type 'b' means tail n blocks, not lines
 *	type 'c' means tail n characters
 *	Type 'r' means in lines in reverse order from end
 *	 (for -r, default is entire buffer )
 *	option 'f' means loop endlessly trying to read more
 *		characters after the end of file, on the  assumption
 *		that the file is growing
*/
E 11
I 11
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"
E 11

D 11
#include	<stdio.h>
#include	<ctype.h>
#include	<sys/types.h>
#include	<sys/stat.h>
I 6
#include	<sys/file.h>
E 6
#include	<errno.h>
E 11
I 11
int fflag, rflag, rval;
char *fname;
E 11

D 5
#define LBIN 4097
E 5
I 5
D 8
#define LBIN 8193
E 8
I 8
D 11
#define LBIN 32769
E 8
#undef	BUFSIZ
D 8
#define	BUFSIZ	LBIN-1
E 8
I 8
#define	BUFSIZ	8192
E 8
E 5
struct	stat	statb;
int	follow;
int	piped;
char bin[LBIN];
int errno;
E 11
I 11
static void obsolete __P((char **));
static void usage __P((void));
E 11

I 17
int
E 17
D 11
main(argc,argv)
char **argv;
E 11
I 11
main(argc, argv)
	int argc;
D 17
	char **argv;
E 17
I 17
	char *argv[];
E 17
E 11
{
D 11
	long n,di;
	register i,j,k;
	char	*arg;
	int partial,bylines,bkwds,fromend,lastnl;
	char *p;
E 11
I 11
	struct stat sb;
	FILE *fp;
	long off;
	enum STYLE style;
D 14
	int ch;
E 14
I 14
	int ch, first;
E 14
D 13
	char *p, *num;
E 13
I 13
	char *p;
E 13
E 11

D 2
	lseek(0,(long)0,1);
	piped = errno==ESPIPE;
E 2
D 11
	arg = argv[1];
	if(argc<=1 || *arg!='-'&&*arg!='+') {
		arg = "-10l";
		argc++;
		argv--;
	}
	fromend = *arg=='-';
	arg++;
D 4
	n = 0;
	while(isdigit(*arg))
		n = n*10 + *arg++ - '0';
E 4
I 4
	if (isdigit(*arg)) {
		n = 0;
		while(isdigit(*arg))
			n = n*10 + *arg++ - '0';
	} else
		n = -1;
E 4
	if(!fromend&&n>0)
		n--;
	if(argc>2) {
D 6
		close(0);
E 6
I 6
		(void)close(0);
E 6
		if(open(argv[2],0)!=0) {
			perror(argv[2]);
			exit(1);
E 11
I 11
D 13
	obsolete(argv);
E 13
I 13
	/*
	 * Tail's options are weird.  First, -n10 is the same as -n-10, not
	 * -n+10.  Second, the number options are 1 based and not offsets,
	 * so -n+1 is the first line, and -c-1 is the last byte.  Third, the
	 * number options for the -r option specify the number of things that
	 * get displayed, not the starting point in the file.  The one major
	 * incompatibility in this version as compared to historical versions
	 * is that the 'r' option couldn't be modified by the -lbc options,
	 * i.e. it was always done in lines.  This version treats -rc as a
	 * number of characters in reverse order.  Finally, the default for
	 * -r is the entire file, not 10 lines.
	 */
D 18
#define	ARG(units, forward, backward) { \
	if (style) \
		usage(); \
	off = strtol(optarg, &p, 10) * (units); \
	if (*p) \
D 14
		err("illegal offset -- %s", optarg); \
E 14
I 14
		err(1, "illegal offset -- %s", optarg); \
E 14
	switch(optarg[0]) { \
	case '+': \
		if (off) \
			off -= (units); \
			style = (forward); \
		break; \
	case '-': \
		off = -off; \
		/* FALLTHROUGH */ \
	default: \
		style = (backward); \
		break; \
	} \
E 18
I 18
#define	ARG(units, forward, backward) {					\
	if (style)							\
		usage();						\
	off = strtol(optarg, &p, 10) * (units);				\
	if (*p)								\
		err(1, "illegal offset -- %s", optarg);			\
	switch(optarg[0]) {						\
	case '+':							\
		if (off)						\
			off -= (units);					\
			style = (forward);				\
		break;							\
	case '-':							\
		off = -off;						\
		/* FALLTHROUGH */					\
	default:							\
		style = (backward);					\
		break;							\
	}								\
E 18
}
E 13

I 13
	obsolete(argv);
E 13
	style = NOTSET;
	while ((ch = getopt(argc, argv, "b:c:fn:r")) != EOF)
		switch(ch) {
		case 'b':
D 13
			if (style)
				usage();
			off = strtol(num = optarg, &p, 10) * 512;
			if (*p)
				err("illegal offset -- %s", optarg);
			style = *num == '+' ? FBYTES : RBYTES;
E 13
I 13
			ARG(512, FBYTES, RBYTES);
E 13
			break;
		case 'c':
D 13
			if (style)
				usage();
			off = strtol(num = optarg, &p, 10);
			if (*p)
				err("illegal offset -- %s", optarg);
			style = *num == '+' ? FBYTES : RBYTES;
E 13
I 13
			ARG(1, FBYTES, RBYTES);
E 13
			break;
		case 'f':
			fflag = 1;
			break;
		case 'n':
D 13
			if (style)
				usage();
			off = strtol(num = optarg, &p, 10);
			if (*p)
				err("illegal offset -- %s", optarg);
			style = *num == '+' ? FLINES : RLINES;
E 13
I 13
			ARG(1, FLINES, RLINES);
E 13
			break;
		case 'r':
			rflag = 1;
			break;
		case '?':
		default:
			usage();
E 11
		}
I 11
	argc -= optind;
	argv += optind;

I 17
	if (fflag && argc > 1)
		err(1, "-f option only appropriate for a single file");

E 17
	/*
D 13
	 * Don't permit follow option if displaying in reverse.  An offset
	 * with an explicit leading minus is meaningless.
E 13
I 13
	 * If displaying in reverse, don't permit follow option, and convert
	 * style values.
E 13
	 */
	if (rflag) {
		if (fflag)
			usage();
D 13
		if (style && *num == '-')
			err("illegal offset for -r option -- %s", num);
E 13
		if (style == FBYTES)
			style = RBYTES;
D 17
		if (style == FLINES)
E 17
I 17
		else if (style == FLINES)
E 17
			style = RLINES;
E 11
	}
I 2
D 6
	lseek(0,(long)0,1);
E 6
I 6
D 11
	(void)lseek(0,(off_t)0,L_INCR);
E 6
	piped = errno==ESPIPE;
E 2
	bylines = -1; bkwds = 0;
	while(*arg)
	switch(*arg++) {
E 11

I 13
	/*
	 * If style not specified, the default is the whole file for -r, and
	 * the last 10 lines if not -r.
	 */
	if (style == NOTSET)
		if (rflag) {
			off = 0;
			style = REVERSE;
		} else {
			off = 10;
			style = RLINES;
		}

E 13
D 11
	case 'b':
I 5
		if (n == -1) n = 1;
E 5
		n <<= 9;
		if(bylines!=-1) goto errcom;
		bylines=0;
		break;
	case 'c':
		if(bylines!=-1) goto errcom;
		bylines=0;
		break;
	case 'f':
		follow = 1;
		break;
	case 'r':
D 4
		if(n==0) n = LBIN;
E 4
I 4
		if(n==-1) n = LBIN;
E 4
		bkwds = 1; fromend = 1; bylines = 1;
		break;
	case 'l':
		if(bylines!=-1) goto errcom;
		bylines = 1;
		break;
	default:
		goto errcom;
E 11
I 11
D 14
	if (fname = *argv) {
		if ((fp = fopen(fname, "r")) == NULL)
			ierr();
	} else {
E 14
I 14
	if (*argv)
		for (first = 1; fname = *argv++;) {
D 17
			if ((fp = fopen(fname, "r")) == NULL) {
E 17
I 17
			if ((fp = fopen(fname, "r")) == NULL ||
			    fstat(fileno(fp), &sb)) {
E 17
				ierr();
				continue;
			}
			if (argc > 1) {
				(void)printf("%s==> %s <==\n",
				    first ? "" : "\n", fname);
				first = 0;
I 18
				(void)fflush(stdout);
E 18
			}

			if (rflag)
				reverse(fp, style, off, &sb);
			else
				forward(fp, style, off, &sb);
I 17
			(void)fclose(fp);
E 17
		}
	else {
E 14
D 17
		fp = stdin;
E 17
		fname = "stdin";
E 11
D 14
	}
E 14
D 4
	if (n==0) n = 10;
E 4
I 4
D 11
	if (n==-1) n = 10;
E 4
	if(bylines==-1) bylines = 1;
	if(bkwds) follow=0;
	if(fromend)
		goto keep;
E 11

D 11
			/*seek from beginning */
E 11
I 11
D 14
	if (fstat(fileno(fp), &sb))
		ierr();
E 14
I 14
D 17
		if (fstat(fileno(fp), &sb)) {
E 17
I 17
		if (fstat(fileno(stdin), &sb)) {
E 17
			ierr();
			exit(1);
		}
E 14
E 11

D 11
	if(bylines) {
		j = 0;
		while(n-->0) {
			do {
				if(j--<=0) {
					p = bin;
					j = read(0,p,BUFSIZ);
					if(j--<=0)
						fexit();
				}
			} while(*p++ != '\n');
E 11
I 11
D 14
	/*
	 * Determine if input is a pipe.  4.4BSD will set the SOCKET
	 * bit in the st_mode field for pipes.  Fix this then.
	 */
	if (lseek(fileno(fp), 0L, SEEK_CUR) == -1 && errno == ESPIPE) {
		errno = 0;
		fflag = 0;		/* POSIX.2 requires this. */
	}
E 14
I 14
		/*
		 * Determine if input is a pipe.  4.4BSD will set the SOCKET
		 * bit in the st_mode field for pipes.  Fix this then.
		 */
D 17
		if (lseek(fileno(fp), 0L, SEEK_CUR) == -1 && errno == ESPIPE) {
E 17
I 17
D 19
		if (lseek(fileno(stdin), 0L, SEEK_CUR) == -1 &&
E 19
I 19
		if (lseek(fileno(stdin), (off_t)0, SEEK_CUR) == -1 &&
E 19
		    errno == ESPIPE) {
E 17
			errno = 0;
			fflag = 0;		/* POSIX.2 requires this. */
		}
E 14
D 13

	/*
	 * Tail's options are weird.  First, -n10 is the same as -n-10, not
	 * -n+10.  Second, the number options for the -r option specify the
	 * number of bytes/chars/lines that get displayed, not the offset from
	 * the beginning/end of the file.  Finally, the default for -r is the
	 * entire file, not 10 lines.
	 */
	if (!style)
		if (rflag) {
			off = 0;
			style = REVERSE;
		} else {
			off = 10;
			style = RLINES;
E 11
		}
D 6
		write(1,p,j);
E 6
I 6
D 11
		(void)write(1,p,j);
E 6
	} else  if(n>0) {
		if(!piped)
D 6
			fstat(0,&statb);
E 6
I 6
			(void)fstat(0,&statb);
E 6
		if(piped||(statb.st_mode&S_IFMT)==S_IFCHR)
			while(n>0) {
				i = n>BUFSIZ?BUFSIZ:n;
				i = read(0,bin,i);
				if(i<=0)
					fexit();
				n -= i;
E 11
I 11
	else if (off < 0)
		off = -off;
E 13

D 14
	if (rflag)
		reverse(fp, style, off, &sb);
	else
		forward(fp, style, off, &sb);
E 14
I 14
		if (rflag)
D 17
			reverse(fp, style, off, &sb);
E 17
I 17
			reverse(stdin, style, off, &sb);
E 17
		else
D 17
			forward(fp, style, off, &sb);
E 17
I 17
			forward(stdin, style, off, &sb);
E 17
	}
E 14
	exit(rval);
}

/*
 * Convert the obsolete argument form into something that getopt can handle.
 * This means that anything of the form [+-][0-9][0-9]*[lbc][fr] that isn't
 * the option argument for a -b, -c or -n option gets converted.
 */
static void
obsolete(argv)
D 17
	char **argv;
E 17
I 17
	char *argv[];
E 17
{
	register char *ap, *p, *t;
	int len;
	char *start;

	while (ap = *++argv) {
		/* Return if "--" or not an option of any form. */
		if (ap[0] != '-') {
			if (ap[0] != '+')
				return;
		} else if (ap[1] == '-')
			return;

		switch(*++ap) {
		/* Old-style option. */
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':

			/* Malloc space for dash, new option and argument. */
			len = strlen(*argv);
			if ((start = p = malloc(len + 3)) == NULL)
D 14
				err("%s", strerror(errno));
E 14
I 14
				err(1, "%s", strerror(errno));
E 14
			*p++ = '-';

			/*
			 * Go to the end of the option argument.  Save off any
			 * trailing options (-3lf) and translate any trailing
			 * output style characters.
			 */
			t = *argv + len - 1;
D 12
			if (*t == 'f' || *t == 'r')
				*p++ = *t--;
E 12
I 12
			if (*t == 'f' || *t == 'r') {
				*p++ = *t;
				*t-- = '\0';
			}
E 12
			switch(*t) {
			case 'b':
				*p++ = 'b';
				*t = '\0';
				break;
			case 'c':
				*p++ = 'c';
				*t = '\0';
				break;
			case 'l':
				*t = '\0';
				/* FALLTHROUGH */
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				*p++ = 'n';
				break;
			default:
D 14
				err("illegal option -- %s", *argv);
E 14
I 14
				err(1, "illegal option -- %s", *argv);
E 14
E 11
			}
D 11
		else
D 6
			lseek(0,n,0);
E 6
I 6
			(void)lseek(0,(off_t)n,L_SET);
E 6
	}
copy:
	while((i=read(0,bin,BUFSIZ))>0)
D 6
		write(1,bin,i);
E 6
I 6
		(void)write(1,bin,i);
E 6
	fexit();
E 11
I 11
			*p++ = *argv[0];
			(void)strcpy(p, ap);
			*argv = start;
			continue;
E 11

D 11
			/*seek from end*/
E 11
I 11
		/*
		 * Options w/ arguments, skip the argument and continue
		 * with the next option.
		 */
		case 'b':
		case 'c':
		case 'n':
			if (!ap[1])
				++argv;
			/* FALLTHROUGH */
		/* Options w/o arguments, continue with the next option. */
		case 'f':
		case 'r':
			continue;
E 11

D 11
keep:
	if(n <= 0)
		fexit();
	if(!piped) {
D 6
		fstat(0,&statb);
E 6
I 6
		(void)fstat(0,&statb);
E 6
D 5
		di = !bylines&&n<LBIN?n:LBIN-1;
E 5
I 5
		/* If by lines, back up 1 buffer: else back up as needed */
D 8
		di = bylines?BUFSIZ:n;
E 8
I 8
		di = bylines?LBIN-1:n;
E 8
E 5
		if(statb.st_size > di)
D 6
			lseek(0,-di,2);
E 6
I 6
			(void)lseek(0,(off_t)-di,L_XTND);
E 6
		if(!bylines)
			goto copy;
	}
	partial = 1;
	for(;;) {
		i = 0;
		do {
			j = read(0,&bin[i],LBIN-i);
			if(j<=0)
				goto brka;
			i += j;
		} while(i<LBIN);
		partial = 0;
	}
brka:
	if(!bylines) {
		k =
		    n<=i ? i-n:
		    partial ? 0:
		    n>=LBIN ? i+1:
		    i-n+LBIN;
		k--;
	} else {
		if(bkwds && bin[i==0?LBIN-1:i-1]!='\n'){	/* force trailing newline */
			bin[i]='\n';
			if(++i>=LBIN) {i = 0; partial = 0;}
E 11
I 11
		/* Illegal option, return and let getopt handle it. */
		default:
			return;
E 11
		}
D 11
		k = i;
		j = 0;
		do {
			lastnl = k;
			do {
				if(--k<0) {
					if(partial) {
D 6
						if(bkwds) write(1,bin,lastnl+1);
E 6
I 6
						if(bkwds) 
						    (void)write(1,bin,lastnl+1);
E 6
						goto brkb;
					}
					k = LBIN -1;
				}
			} while(bin[k]!='\n'&&k!=i);
			if(bkwds && j>0){
D 6
				if(k<lastnl) write(1,&bin[k+1],lastnl-k);
E 6
I 6
				if(k<lastnl) (void)write(1,&bin[k+1],lastnl-k);
E 6
				else {
D 6
					write(1,&bin[k+1],LBIN-k-1);
					write(1,bin,lastnl+1);
E 6
I 6
					(void)write(1,&bin[k+1],LBIN-k-1);
					(void)write(1,bin,lastnl+1);
E 6
				}
			}
		} while(j++<n&&k!=i);
brkb:
		if(bkwds) exit(0);
		if(k==i) do {
			if(++k>=LBIN)
				k = 0;
		} while(bin[k]!='\n'&&k!=i);
E 11
	}
D 11
	if(k<i)
D 6
		write(1,&bin[k+1],i-k-1);
E 6
I 6
		(void)write(1,&bin[k+1],i-k-1);
E 6
	else {
D 6
		write(1,&bin[k+1],LBIN-k-1);
		write(1,bin,i);
E 6
I 6
		(void)write(1,&bin[k+1],LBIN-k-1);
		(void)write(1,bin,i);
E 6
	}
	fexit();
errcom:
	fprintf(stderr, "usage: tail [+_[n][lbc][rf]] [file]\n");
	exit(2);
E 11
}

D 11
fexit()
{	register int n;
	if (!follow || piped) exit(0);
	for (;;)
	{	sleep(1);
		while ((n = read (0, bin, BUFSIZ)) > 0)
D 6
			write (1, bin, n);
E 6
I 6
D 9
			(void)write (1, bin, n);
E 9
I 9
			if (write (1, bin, n) < 0)
				exit(1);
E 9
E 6
	}
E 11
I 11
static void
usage()
{
	(void)fprintf(stderr,
D 17
	    "usage: tail [-f | -r] [-b # | -c # | -n #] [file]\n");
E 17
I 17
	    "usage: tail [-f | -r] [-b # | -c # | -n #] [file ...]\n");
E 17
	exit(1);
E 11
}
E 1
