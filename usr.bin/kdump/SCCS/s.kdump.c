h05724
s 00024/00046/00368
d D 8.4 95/04/28 16:37:59 bostic 17 16
c Some KNF, POSIX, and err*(3)/warn*(3) cleanup.  Also, use sys_signame[]rather than a private, home-grown list.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00029/00027/00385
d D 8.3 95/02/22 14:36:40 mckusick 16 15
c better fix for new syscall convention (from cgd)
e
s 00004/00003/00408
d D 8.2 95/02/21 17:12:18 bostic 15 14
c ktr_narg => ktr_argsize
e
s 00005/00005/00406
d D 8.1 93/06/06 14:53:10 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00000/00398
d D 5.4 92/07/20 14:34:05 marc 13 12
c add KTR_CSW
e
s 00006/00000/00392
d D 5.3 91/01/17 17:27:10 bostic 12 11
c forgot to reopen the file as stdin
e
s 00033/00016/00359
d D 5.2 90/12/29 13:17:15 bostic 11 10
c Sparker's changes to decode ptrace command arguments
e
s 00110/00108/00265
d D 5.1 90/12/28 19:17:33 bostic 10 9
c KNF, lint, document all options, make man page consistent
e
s 00026/00031/00347
d D 1.9 90/06/29 00:34:00 marc 9 8
c cencode->vis; u_eosys is gone; 
e
s 00002/00002/00376
d D 1.8 90/05/23 15:00:35 marc 8 7
c bump max value for ktrace record size sanity check (test for < 0).
e
s 00106/00042/00272
d D 1.7 90/04/19 14:11:45 marc 7 6
c cencode visual output; relative timestamp (-R), signals
e
s 00047/00051/00267
d D 1.6 89/11/22 14:26:19 marc 6 5
c first pass
e
s 00001/00001/00317
d D 1.5 88/12/21 19:13:12 marc 5 4
c fix getopt string
e
s 00138/00090/00180
d D 1.4 88/12/21 19:04:29 marc 4 3
c changed interface, first "official" version
e
s 00001/00003/00269
d D 1.3 88/12/15 17:28:23 marc 3 2
c checkpoint before addind ioctl name 
e
s 00097/00014/00175
d D 1.2 88/12/15 02:21:28 marc 2 1
c kernel tracing
e
s 00189/00000/00000
d D 1.1 88/12/14 16:21:47 marc 1 0
c date and time created 88/12/14 16:21:47 by marc
e
u
U
t
T
I 1
D 9
/*
E 9
I 9
/*-
E 9
D 14
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 9
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
 */

#ifndef lint
D 14
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 14
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 10
#include <sys/param.h>
I 12
#include <sys/errno.h>
E 12
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/ktrace.h>
E 10
I 7
D 9
#include <cencode.h>
E 7
D 4
#include <sys/param.h>
#include <sys/file.h>
#include <sys/dir.h>
D 3
/*#include <time.h>*/
E 3
#include <sys/user.h>
#include <sys/ktrace.h>
#include <stdio.h>
E 4
I 4
#include "ktrace.h"
E 9
I 7
#include <sys/ioctl.h>
I 11
#include <sys/ptrace.h>
E 11
I 9
D 10
#include <vis.h>
E 10
#define KERNEL
D 10
#include <errno.h>
E 10
I 10
#include <sys/errno.h>
E 10
#undef KERNEL
I 10
D 17
#include <vis.h>
E 17
I 17

#include <err.h>
#include <signal.h>
E 17
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 17
#include <unistd.h>
#include <vis.h>

E 17
E 10
#include "ktrace.h"
E 9
E 7
E 4

D 4
#define FLG_TIME	0x1
#define FLG_PERSIST	0x2
I 2
#define FLG_SHODATA	0x4
E 2
int flags;

D 2
#define DEF_TRACEFILE	"trace.out"
char *tracefile;
E 2
I 2
D 3
char *tracefile = "trace.out";
E 3
I 3
char *tracefile = "ktrace.data";
E 3
E 2

E 4
I 4
D 6
int timestamp, decimal, fancy = 1, loop, maxdata;
E 6
I 6
int timestamp, decimal, fancy = 1, tail, maxdata;
E 6
char *tracefile = DEF_TRACEFILE;
E 4
struct ktr_header ktr_header;
D 4
int size = 1024;
E 4
I 4
D 6
int size = 1024;	/* initial size of buffer - will grow as needed */
E 6
I 6
D 7
int size = 1024;	/* initial size of buffer - grow as needed */
E 7
I 7
D 10
int size = 1024;	/* initial size - grow as needed */
E 10
E 7
E 6
E 4

I 4
D 10
#define USAGE	\
D 6
	"usage: kdump [-dnlT] [-t facilitystring] [-f tracefile] [-m maxdata]\n\
	facilities: c = syscalls, n = namei, g = generic-i/o, a = everything\n"
E 6
I 6
	"usage: kdump [-dnlT] [-t trops] [-f trfile] [-m maxdata]\n\
	trops: c = syscalls, n = namei, g = generic-i/o, a = everything\n"
E 6

E 10
E 4
#define eqs(s1, s2)	(strcmp((s1), (s2)) == 0)

I 17
int
E 17
main(argc, argv)
I 10
	int argc;
E 10
	char *argv[];
{
D 17
	extern int optind;
	extern char *optarg;
E 17
D 10
	int ch, ktrlen;
	register char *m;
E 10
I 10
	int ch, ktrlen, size;
	register void *m;
E 10
I 4
D 6
	int facs = DEF_FACS;
E 6
I 6
D 7
	int facs = ALL_FACS;
E 7
I 7
	int trpoints = ALL_POINTS;
E 7
E 6
E 4

D 2
	while ((ch = getopt(argc,argv,"tf")) != EOF)
E 2
I 2
D 4
	while ((ch = getopt(argc,argv,"tlf:d")) != EOF)
E 4
I 4
D 5
	while ((ch = getopt(argc,argv,"t:f:dnlTm")) != EOF)
E 5
I 5
D 7
	while ((ch = getopt(argc,argv,"t:f:dnlTm:")) != EOF)
E 7
I 7
D 10
	while ((ch = getopt(argc,argv,"t:f:dnlTRm:")) != EOF)
E 10
I 10
D 17
	while ((ch = getopt(argc,argv,"f:dlm:nRTt:")) != EOF)
E 10
E 7
E 5
E 4
E 2
		switch((char)ch) {
E 17
I 17
	while ((ch = getopt(argc, argv, "f:dlm:nRTt:")) != -1)
		switch (ch) {
E 17
D 6
			case 't':
D 4
				flags |= FLG_TIME;
E 4
I 4
				facs = getfacs(optarg);
				if (facs < 0) {
					fprintf(stderr, 
					     "kdump: unknown facility in %s\n",
						optarg);
					exit(1);
				}
E 4
				break;
D 2
			case 'f':
E 2
I 2
D 4
			case 'l':
E 2
				flags |= FLG_PERSIST;
I 2
				break;
E 4
			case 'f':
				tracefile = optarg;
				break;
			case 'd':
D 4
				flags |= FLG_SHODATA;
E 4
I 4
				decimal = 1;
E 4
				break;
I 4
			case 'n':
				fancy = 0;
				break;
			case 'l':
				loop = 1;
				break;
			case 'T':
				timestamp = 1;
				break;
			case 'm':
				maxdata = atoi(optarg);
				break;
E 4
E 2
			default:
D 4
				fprintf(stderr,"usage: \n",*argv);
E 4
I 4
				fprintf(stderr, USAGE);
E 6
I 6
D 10
		case 't':
D 7
			facs = getfacs(optarg);
			if (facs < 0) {
E 7
I 7
			trpoints = getpoints(optarg);
			if (trpoints < 0) {
E 7
				fprintf(stderr, 
D 7
				     "kdump: unknown facility in %s\n",
E 7
I 7
				     "kdump: unknown trace point in %s\n",
E 7
					optarg);
E 6
E 4
				exit(1);
I 6
			}
			break;
E 10
		case 'f':
			tracefile = optarg;
			break;
		case 'd':
			decimal = 1;
			break;
D 10
		case 'n':
			fancy = 0;
			break;
E 10
		case 'l':
			tail = 1;
			break;
D 10
		case 'T':
			timestamp = 1;
E 10
I 10
		case 'm':
			maxdata = atoi(optarg);
E 10
			break;
I 10
		case 'n':
			fancy = 0;
			break;
E 10
I 7
		case 'R':
			timestamp = 2;	/* relative timestamp */
			break;
E 7
D 10
		case 'm':
			maxdata = atoi(optarg);
E 10
I 10
		case 'T':
			timestamp = 1;
E 10
			break;
I 10
		case 't':
			trpoints = getpoints(optarg);
D 17
			if (trpoints < 0) {
				(void)fprintf(stderr,
				    "kdump: unknown trace point in %s\n",
				    optarg);
				exit(1);
			}
E 17
I 17
			if (trpoints < 0)
				errx(1, "unknown trace point in %s", optarg);
E 17
			break;
E 10
		default:
D 10
			fprintf(stderr, USAGE);
			exit(1);
E 10
I 10
			usage();
E 10
E 6
		}
D 10
	argv += optind, argc -= optind;
E 10
I 10
	argv += optind;
	argc -= optind;
E 10

D 10
	if (argc > 1) {
D 4
		fprintf(stderr, "kdump: usage\n");
E 4
I 4
		fprintf(stderr, USAGE);
E 4
		exit(1);
	}
D 2
	tracefile = argc ? argv[0] : DEF_TRACEFILE;
E 2
	if (!eqs(tracefile, "-")) {
		if (freopen(tracefile, "r", stdin) == NULL) {
D 4
			fprintf(stderr, "kdump: %s:", tracefile);
E 4
I 4
			fprintf(stderr, "kdump: %s: ", tracefile);
E 4
			perror("");
			exit(1);
		}
	}
D 7
	m = (char *)malloc(size);
E 7
I 7
	m = (char *)malloc(size+1);
E 10
I 10
	if (argc > 1)
		usage();

	m = (void *)malloc(size = 1025);
E 10
E 7
D 17
	if (m == NULL) {
D 2
		fprintf(stderr, "out of money\n");
E 2
I 2
D 4
		fprintf(stderr, "kdump: out of money\n");
E 4
I 4
D 10
		fprintf(stderr, "kdump: ain't gots no memory\n");
E 10
I 10
		(void)fprintf(stderr, "kdump: %s.\n", strerror(ENOMEM));
I 12
		exit(1);
	}
	if (!freopen(tracefile, "r", stdin)) {
		(void)fprintf(stderr,
		    "kdump: %s: %s.\n", tracefile, strerror(errno));
E 12
E 10
E 4
E 2
		exit(1);
	}
E 17
I 17
	if (m == NULL)
		errx(1, "%s", strerror(ENOMEM));
	if (!freopen(tracefile, "r", stdin))
		err(1, "%s", tracefile);
E 17
D 2
	while (fread(&ktr_header, sizeof(struct ktr_header), 1, stdin)) {
E 2
I 2
D 6
	while (myfread(&ktr_header, sizeof(struct ktr_header), 1, stdin)) {
E 6
I 6
D 7
	while (fread_t(&ktr_header, sizeof(struct ktr_header), 1,
E 7
I 7
D 10
	while (fread_tail(&ktr_header, sizeof(struct ktr_header), 1,
E 7
	       stdin, tail)) {
E 10
I 10
	while (fread_tail(&ktr_header, sizeof(struct ktr_header), 1)) {
E 10
E 6
E 2
D 4
		dumpheader(&ktr_header);
E 4
I 4
D 7
		if (facs & (1<<ktr_header.ktr_type))
E 7
I 7
		if (trpoints & (1<<ktr_header.ktr_type))
E 7
			dumpheader(&ktr_header);
E 4
D 2
		if ((ktrlen = ktr_header.ktr_len) > 30000) {	/* XXX */
			fprintf(stderr, "bogus length %d\n", 
E 2
I 2
D 8
		if ((ktrlen = ktr_header.ktr_len) > 80000) {	/* XXX */
			fprintf(stderr, "kdump: bogus length %d\n", 
E 8
I 8
D 17
		if ((ktrlen = ktr_header.ktr_len) < 0) {
D 10
			fprintf(stderr, "kdump: bogus length 0x%x\n", 
E 8
E 2
				ktrlen);
E 10
I 10
			(void)fprintf(stderr,
			    "kdump: bogus length 0x%x\n", ktrlen);
E 10
			exit(1);
		}
E 17
I 17
		if ((ktrlen = ktr_header.ktr_len) < 0)
			errx(1, "bogus length 0x%x", ktrlen);
E 17
		if (ktrlen > size) {
D 7
			m = (char *)realloc(m, ktrlen);
E 7
I 7
D 10
			m = (char *)realloc(m, ktrlen+1);
E 10
I 10
			m = (void *)realloc(m, ktrlen+1);
E 10
E 7
D 17
			if (m == NULL) {
D 2
				fprintf(stderr, "out of money\n");
E 2
I 2
D 4
				fprintf(stderr, "kdump: out of money\n");
E 4
I 4
D 6
				fprintf(stderr,"kdump: ain't gots no memory\n");
E 6
I 6
D 10
				fprintf(stderr,"kdump: out of memory\n");
E 10
I 10
				(void)fprintf(stderr,
				    "kdump: %s.\n", strerror(ENOMEM));
E 10
E 6
E 4
E 2
				exit(1);
			}
E 17
I 17
			if (m == NULL)
				errx(1, "%s", strerror(ENOMEM));
E 17
			size = ktrlen;
		}
D 2
		if (fread(m, ktrlen, 1, stdin) == 0) {
E 2
I 2
D 6
		if (myfread(m, ktrlen, 1, stdin) == 0) {
E 2
			fprintf(stderr, "kdump: out of data\n");
E 6
I 6
D 7
		if (ktrlen && fread_t(m, ktrlen, 1, stdin, tail) == 0) {
E 7
I 7
D 10
		if (ktrlen && fread_tail(m, ktrlen, 1, stdin, tail) == 0) {
E 7
			fprintf(stderr, "kdump: data too short\n");
E 10
I 10
D 17
		if (ktrlen && fread_tail(m, ktrlen, 1) == 0) {
			(void)fprintf(stderr, "kdump: data too short.\n");
E 10
E 6
			exit(1);
		}
E 17
I 17
		if (ktrlen && fread_tail(m, ktrlen, 1) == 0)
			errx(1, "data too short");
E 17
I 4
D 7
		if ((facs & (1<<ktr_header.ktr_type)) == 0)
E 7
I 7
		if ((trpoints & (1<<ktr_header.ktr_type)) == 0)
E 7
			continue;
E 4
		switch (ktr_header.ktr_type) {
		case KTR_SYSCALL:
D 10
			ktrsyscall((struct ktr_syscall *)m, ktrlen);
E 10
I 10
			ktrsyscall((struct ktr_syscall *)m);
E 10
			break;
		case KTR_SYSRET:
D 10
			ktrsysret((struct ktr_sysret *)m, ktrlen);
E 10
I 10
			ktrsysret((struct ktr_sysret *)m);
E 10
			break;
		case KTR_NAMEI:
			ktrnamei(m, ktrlen);
			break;
I 2
		case KTR_GENIO:
			ktrgenio((struct ktr_genio *)m, ktrlen);
			break;
I 7
		case KTR_PSIG:
D 10
			ktrpsig((struct ktr_psig *)m, ktrlen);
E 10
I 10
			ktrpsig((struct ktr_psig *)m);
E 10
			break;
I 13
		case KTR_CSW:
			ktrcsw((struct ktr_csw *)m);
			break;
E 13
E 7
E 2
		}
I 4
D 6
		if (loop)
E 6
I 6
		if (tail)
E 6
D 10
			fflush(stdout);
E 10
I 10
			(void)fflush(stdout);
E 10
E 4
	}
}

I 2
D 6
myfread(buf, size, num, stream)
E 6
I 6
D 7
fread_t(buf, size, num, stream, tail)
E 7
I 7
D 10
fread_tail(buf, size, num, stream, tail)
E 10
I 10
fread_tail(buf, size, num)
E 10
E 7
E 6
	char *buf;
D 10
	FILE *stream;
E 10
I 10
	int num, size;
E 10
{
	int i;
D 6
again:
	if (i = fread(buf, size, num, stream))
		return (i);
	else {
D 4
		if (flags&FLG_PERSIST) {
E 4
I 4
		if (loop) {
E 4
			sleep(1);
			clearerr(stream);
			goto again;
		} else
			return 0;
E 6
I 6

D 10
	while ((i = fread(buf, size, num, stream)) == 0 && tail) {
		sleep(1);
		clearerr(stream);
E 10
I 10
	while ((i = fread(buf, size, num, stdin)) == 0 && tail) {
		(void)sleep(1);
		clearerr(stdin);
E 10
E 6
	}
I 6
	return (i);
E 6
}

E 2
dumpheader(kth)
	struct ktr_header *kth;
{
	static char unknown[64];
I 7
	static struct timeval prevtime, temp;
E 7
	char *type;

	switch (kth->ktr_type) {
	case KTR_SYSCALL:
D 4
		type = "C";
E 4
I 4
		type = "CALL";
E 4
		break;
	case KTR_SYSRET:
D 4
		type = "R";
E 4
I 4
		type = "RET ";
E 4
		break;
	case KTR_NAMEI:
D 4
		type = "N";
E 4
I 4
		type = "NAMI";
E 4
		break;
I 2
	case KTR_GENIO:
D 4
		type = "D";
E 4
I 4
		type = "GIO ";
E 4
		break;
I 7
	case KTR_PSIG:
		type = "PSIG";
		break;
I 13
	case KTR_CSW:
		type = "CSW";
		break;
E 13
E 7
E 2
	default:
D 2
		sprintf(unknown, "UNKNOWN %d", kth->ktr_type);
E 2
I 2
D 10
		sprintf(unknown, "UNKNOWN(%d)", kth->ktr_type);
E 10
I 10
		(void)sprintf(unknown, "UNKNOWN(%d)", kth->ktr_type);
E 10
E 2
		type = unknown;
	}

D 2
	printf("%s %d (%s) ",
E 2
I 2
D 4
	printf("%s %6d %-8s ",
E 2
		type, kth->ktr_pid, kth->ktr_comm);
	if (flags&FLG_TIME)
E 4
I 4
D 10
	printf("%6d %-8s ",
		kth->ktr_pid, kth->ktr_comm);
E 10
I 10
	(void)printf("%6d %-8s ", kth->ktr_pid, kth->ktr_comm);
E 10
D 7
	if (timestamp)
E 4
		printf("%d.%d ", kth->ktr_time.tv_sec, kth->ktr_time.tv_usec);
E 7
I 7
	if (timestamp) {
		if (timestamp == 2) {
			temp = kth->ktr_time;
			timevalsub(&kth->ktr_time, &prevtime);
			prevtime = temp;
		}
D 10
		printf("%d.%06d ", kth->ktr_time.tv_sec, kth->ktr_time.tv_usec);
E 10
I 10
		(void)printf("%ld.%06ld ",
		    kth->ktr_time.tv_sec, kth->ktr_time.tv_usec);
E 10
	}
E 7
I 2
D 4
	if (flags&FLG_PERSIST)
		fflush(stdout);
E 4
I 4
D 10
	printf("%s  ", type);
E 10
I 10
	(void)printf("%s  ", type);
E 10
E 4
E 2
}

I 4
#include <sys/syscall.h>
#define KTRACE
E 4
D 6
#include "/sys/sys/syscalls.c"
E 6
I 6
#include "/sys/kern/syscalls.c"
E 6
I 4
#undef KTRACE
E 4
int nsyscalls = sizeof (syscallnames) / sizeof (syscallnames[0]);

I 11
static char *ptrace_ops[] = {
	"PT_TRACE_ME",	"PT_READ_I",	"PT_READ_D",	"PT_READ_U",
	"PT_WRITE_I",	"PT_WRITE_D",	"PT_WRITE_U",	"PT_CONTINUE",
	"PT_KILL",	"PT_STEP",
};

E 11
D 10
ktrsyscall(ktr, len)
E 10
I 10
ktrsyscall(ktr)
E 10
	register struct ktr_syscall *ktr;
{
D 15
	register narg = ktr->ktr_narg;
	register int *ip;
D 4
	register char c = '(';
E 4
I 4
	char *ioctlname();
E 15
I 15
D 16
	register int *ip, narg;
	char *ioctlname __P((int));
E 16
I 16
	register argsize = ktr->ktr_argsize;
	register register_t *ap;
	char *ioctlname();
E 16
E 15
E 4

	if (ktr->ktr_code >= nsyscalls || ktr->ktr_code < 0)
D 4
		printf("%d ", ktr->ktr_code);
E 4
I 4
D 10
		printf("[%d]", ktr->ktr_code);
E 10
I 10
		(void)printf("[%d]", ktr->ktr_code);
E 10
E 4
	else
D 4
		printf("%s ", syscallnames[ktr->ktr_code]);
E 4
I 4
D 10
		printf("%s", syscallnames[ktr->ktr_code]);
E 10
I 10
		(void)printf("%s", syscallnames[ktr->ktr_code]);
E 10
E 4
D 16
	ip = (int *)((char *)ktr + sizeof(struct ktr_syscall));
I 15

	narg = ktr->ktr_argsize / sizeof(register_t);
E 15
D 4
	while (narg) {
		printf("%c%x", c, *ip);
		ip++; narg--; c = ',';
	}
	if (ktr->ktr_narg)
E 4
I 4
	if (narg) {
E 16
I 16
	ap = (register_t *)((char *)ktr + sizeof(struct ktr_syscall));
	if (argsize) {
E 16
		char c = '(';
D 11
		if (fancy && ktr->ktr_code == SYS_ioctl) {
			char *cp;
			if (decimal)
D 10
				printf("(%d", *ip);
E 10
I 10
				(void)printf("(%d", *ip);
E 10
			else
D 10
				printf("(%#x", *ip);
			ip++; narg--;
E 10
I 10
				(void)printf("(%#x", *ip);
			ip++;
			narg--;
E 10
			if ((cp = ioctlname(*ip)) != NULL)
D 10
				printf(",%s", cp);
E 10
I 10
				(void)printf(",%s", cp);
E 10
			else {
E 11
I 11
		if (fancy) {
			if (ktr->ktr_code == SYS_ioctl) {
				char *cp;
E 11
				if (decimal)
D 10
					printf(",%d", *ip);
E 10
I 10
D 11
					(void)printf(",%d", *ip);
E 11
I 11
D 16
					(void)printf("(%d", *ip);
E 16
I 16
					(void)printf("(%ld", (long)*ap);
E 16
E 11
E 10
				else
D 10
					printf(",%#x ", *ip);
E 10
I 10
D 11
					(void)printf(",%#x ", *ip);
E 11
I 11
D 16
					(void)printf("(%#x", *ip);
				ip++;
				narg--;
				if ((cp = ioctlname(*ip)) != NULL)
E 16
I 16
					(void)printf("(%#lx", (long)*ap);
				ap++;
				argsize -= sizeof(register_t);
				if ((cp = ioctlname(*ap)) != NULL)
E 16
					(void)printf(",%s", cp);
				else {
					if (decimal)
D 16
						(void)printf(",%d", *ip);
E 16
I 16
						(void)printf(",%ld",
						    (long)*ap);
E 16
					else
D 16
						(void)printf(",%#x ", *ip);
E 16
I 16
						(void)printf(",%#lx ",
						    (long)*ap);
E 16
				}
				c = ',';
D 16
				ip++;
				narg--;
E 16
I 16
				ap++;
				argsize -= sizeof(register_t);
E 16
			} else if (ktr->ktr_code == SYS_ptrace) {
D 16
				if (*ip <= PT_STEP && *ip >= 0)
					(void)printf("(%s", ptrace_ops[*ip]);
E 16
I 16
				if (*ap >= 0 && *ap <=
				    sizeof(ptrace_ops) / sizeof(ptrace_ops[0]))
					(void)printf("(%s", ptrace_ops[*ap]);
E 16
				else
D 16
					(void)printf("(%d", *ip);
E 16
I 16
					(void)printf("(%ld", (long)*ap);
E 16
				c = ',';
D 16
				ip++;
				narg--;
E 16
I 16
				ap++;
				argsize -= sizeof(register_t);
E 16
E 11
E 10
			}
D 11
			c = ',';
D 10
			ip++; narg--;
E 10
I 10
			ip++;
			narg--;
E 11
E 10
		}
D 16
		while (narg) {
E 16
I 16
		while (argsize) {
E 16
			if (decimal)
D 10
				printf("%c%d", c, *ip);
E 10
I 10
D 16
				(void)printf("%c%d", c, *ip);
E 16
I 16
				(void)printf("%c%ld", c, (long)*ap);
E 16
E 10
			else
D 10
				printf("%c%#x", c, *ip);
E 10
I 10
D 16
				(void)printf("%c%#x", c, *ip);
E 16
I 16
				(void)printf("%c%#lx", c, (long)*ap);
E 16
E 10
			c = ',';
D 10
			ip++; narg--;
E 10
I 10
D 16
			ip++;
			narg--;
E 16
I 16
			ap++;
			argsize -= sizeof(register_t);
E 16
E 10
		}
E 4
D 10
		putchar(')');
E 10
I 10
		(void)putchar(')');
E 10
I 4
	}
E 4
D 10
	putchar('\n');
E 10
I 10
	(void)putchar('\n');
E 10
I 2
D 4
	if (flags&FLG_PERSIST)
		fflush(stdout);
E 4
E 2
}

D 10
ktrsysret(ktr, len)
E 10
I 10
ktrsysret(ktr)
E 10
	struct ktr_sysret *ktr;
{
D 9
	extern char *sys_errlist[];
I 4
	int ret = ktr->ktr_retval;
E 9
I 9
	register int ret = ktr->ktr_retval;
	register int error = ktr->ktr_error;
	register int code = ktr->ktr_code;
E 9
E 4

D 9
	if (ktr->ktr_code >= nsyscalls || ktr->ktr_code < 0)
D 4
		printf("%d ", ktr->ktr_code);
E 4
I 4
		printf("[%d] ", ktr->ktr_code);
E 9
I 9
	if (code >= nsyscalls || code < 0)
D 10
		printf("[%d] ", code);
E 10
I 10
		(void)printf("[%d] ", code);
E 10
E 9
E 4
	else
D 9
		printf("%s ", syscallnames[ktr->ktr_code]);
D 4
	if (ktr->ktr_error)
		printf("-1 (%d) %s", ktr->ktr_error,
			sys_errlist[ktr->ktr_error]);
	else
		printf("%d (0x%x)", ktr->ktr_retval, ktr->ktr_retval);
E 4
I 4
D 7
	if (ktr->ktr_error) {
E 7
I 7
	if (ktr->ktr_eosys == RESTARTSYS)
		printf("RESTART");
	else if (ktr->ktr_error) {
E 7
		printf("-1 errno %d", ktr->ktr_error);
		if (fancy)
D 7
			printf(" %s", sys_errlist[ktr->ktr_error]);
E 7
I 7
			printf(" %s", strerror(ktr->ktr_error));
E 7
	} else {
E 9
I 9
D 10
		printf("%s ", syscallnames[code]);
E 10
I 10
		(void)printf("%s ", syscallnames[code]);
E 10

	if (error == 0) {
E 9
		if (fancy) {
D 10
			printf("%d", ret);
E 10
I 10
			(void)printf("%d", ret);
E 10
			if (ret < 0 || ret > 9)
D 7
				printf(" %#x", ret);
E 7
I 7
D 10
				printf("/%#x", ret);
E 10
I 10
				(void)printf("/%#x", ret);
E 10
E 7
		} else {
			if (decimal)
D 10
				printf("%d", ret);
E 10
I 10
				(void)printf("%d", ret);
E 10
			else
D 10
				printf("%#x", ret);
E 10
I 10
				(void)printf("%#x", ret);
E 10
		}
I 9
	} else if (error == ERESTART)
D 10
		printf("RESTART");
E 10
I 10
		(void)printf("RESTART");
E 10
	else if (error == EJUSTRETURN)
D 10
		printf("JUSTRETURN");
E 10
I 10
		(void)printf("JUSTRETURN");
E 10
	else {
D 10
		printf("-1 errno %d", ktr->ktr_error);
E 10
I 10
		(void)printf("-1 errno %d", ktr->ktr_error);
E 10
		if (fancy)
D 10
			printf(" %s", strerror(ktr->ktr_error));
E 10
I 10
			(void)printf(" %s", strerror(ktr->ktr_error));
E 10
E 9
	}
E 4
D 10
	putchar('\n');
E 10
I 10
	(void)putchar('\n');
E 10
I 2
D 4
	if (flags&FLG_PERSIST)
		fflush(stdout);
E 4
E 2
}

D 4
ktrnamei(cp, len) {
E 4
I 4
ktrnamei(cp, len) 
	char *cp;
{
E 4
D 2
	printf("%.*s\n", len, cp);
E 2
I 2
D 10
	printf("\"%.*s\"\n", len, cp);
E 10
I 10
	(void)printf("\"%.*s\"\n", len, cp);
E 10
D 4
	if (flags&FLG_PERSIST)
		fflush(stdout);
E 4
E 2
}
I 2

I 7
D 9
#define CENC_ALL (CENC_CSTYLE | CENC_GRAPH | CENC_OCTAL)

E 9
E 7
ktrgenio(ktr, len)
	struct ktr_genio *ktr;
{
D 7
	int datalen = len - sizeof (struct ktr_genio);
	char *cp = (char *)ktr + sizeof (struct ktr_genio);
E 7
I 7
	register int datalen = len - sizeof (struct ktr_genio);
	register char *dp = (char *)ktr + sizeof (struct ktr_genio);
	register char *cp;
E 7
I 4
	register int col = 0;
D 10
	register char c;
E 10
I 7
	register width;
I 9
	char visbuf[5];
E 9
	static screenwidth = 0;
E 7
E 4

I 7
	if (screenwidth == 0) {
		struct winsize ws;

		if (fancy && ioctl(fileno(stderr), TIOCGWINSZ, &ws) != -1 &&
		    ws.ws_col > 8)
			screenwidth = ws.ws_col;
		else
			screenwidth = 80;
	}
E 7
D 4
	printf("FD %d %s %d bytes\n", ktr->ktr_fd,
		ktr->ktr_rw == UIO_READ ? "READ" : "WRITE", datalen);
	if (flags&FLG_SHODATA) {
		int col = 0;
E 4
I 4
	printf("fd %d %s %d bytes\n", ktr->ktr_fd,
		ktr->ktr_rw == UIO_READ ? "read" : "wrote", datalen);
	if (maxdata && datalen > maxdata)
		datalen = maxdata;
D 7
	for (;datalen > 0; datalen--, cp++) {
		c = *cp;
E 4

E 7
I 7
D 10
	printf("       \"");
E 10
I 10
	(void)printf("       \"");
E 10
	col = 8;
D 17
	for (;datalen > 0; datalen--, dp++) {
E 17
I 17
	for (; datalen > 0; datalen--, dp++) {
E 17
D 9
		cp = cencode(*dp, CENC_ALL | CENC_RACHAR, *(dp+1));
		if (*cp == '\r')
			cp = "\\r";
E 9
I 9
		(void) vis(visbuf, *dp, VIS_CSTYLE, *(dp+1));
		cp = visbuf;
E 9
		/*
		 * Keep track of printables and
		 * space chars (like fold(1)).
		 */
E 7
D 4
		while (datalen > 0) {
			if (col == 0) {
				putchar('\t');
				col = 1;
			}
			if (*cp < 040 || *cp > 0177) {
				switch (*cp) {
				case '\n':
					putchar(*cp);
					col = 0;
					break;
				case '\t':
					putchar(*cp);
					break;
				default:
					if (*cp & 0200) {
						putchar('M');
						putchar('-');
						*cp &= 0177;
					}
					putchar('^');
					putchar(*cp+'@');
				}
			} else
				putchar(*cp);
			datalen--;
			cp++;
E 4
I 4
		if (col == 0) {
D 10
			putchar('\t');
E 10
I 10
			(void)putchar('\t');
E 10
D 7
			col = 1;
E 7
I 7
			col = 8;
E 7
E 4
		}
D 4
		if (col != 0)
			putchar('\n');
E 4
I 4
D 7
		if (c == '\n' || c == '\t') {
			if (c == '\n')
				col = 0;
			putchar(c);
E 7
I 7
		switch(*cp) {
		case '\n':
			col = 0;
D 10
			putchar('\n');
E 10
I 10
			(void)putchar('\n');
E 10
E 7
			continue;
I 7
		case '\t':
			width = 8 - (col&07);
			break;
		default:
			width = strlen(cp);
E 7
		}
D 7
		if (c & 0200) {
			putchar('M');
			putchar('-');
			c &= 0177;
E 7
I 7
		if (col + width > (screenwidth-2)) {
D 10
			printf("\\\n\t");
E 10
I 10
			(void)printf("\\\n\t");
E 10
			col = 8;
E 7
		}
D 7
		if (c < 040 || c == 0177) {
			putchar('^');
			if (c == 0177)
				putchar('?');
			else
				putchar(c+'@');
		} else
			putchar(c);
E 7
I 7
		col += width;
		do {
D 10
			putchar(*cp++);
E 10
I 10
			(void)putchar(*cp++);
E 10
		} while (*cp);
E 7
E 4
	}
I 4
D 7
	if (col != 0)
		putchar('\n');
E 7
I 7
	if (col == 0)
D 10
		printf("       ");
	printf("\"\n");
E 10
I 10
		(void)printf("       ");
	(void)printf("\"\n");
E 10
}

D 10

E 10
D 17
char *signames[] = {
	"NULL", "HUP", "INT", "QUIT", "ILL", "TRAP", "IOT",	/*  1 - 6  */
	"EMT", "FPE", "KILL", "BUS", "SEGV", "SYS",		/*  7 - 12 */
	"PIPE", "ALRM",  "TERM", "URG", "STOP", "TSTP",		/* 13 - 18 */
	"CONT", "CHLD", "TTIN", "TTOU", "IO", "XCPU",		/* 19 - 24 */
	"XFSZ", "VTALRM", "PROF", "WINCH", "29", "USR1",	/* 25 - 30 */
	"USR2", NULL,						/* 31 - 32 */
};

E 17
D 10
ktrpsig(psig, len)
E 10
I 10
ktrpsig(psig)
E 10
	struct ktr_psig *psig;
{
D 10
	printf("SIG%s ", signames[psig->signo]);
E 10
I 10
D 17
	(void)printf("SIG%s ", signames[psig->signo]);
E 17
I 17
	(void)printf("SIG%s ", sys_signame[psig->signo]);
E 17
E 10
	if (psig->action == SIG_DFL)
D 10
		printf("SIG_DFL\n");
	else {
		printf("caught handler=0x%x mask=0x%x code=0x%x\n",
			psig->action, psig->mask, psig->code);
	}
E 10
I 10
		(void)printf("SIG_DFL\n");
	else
D 16
		(void)printf("caught handler=0x%x mask=0x%x code=0x%x\n",
		    (u_int)psig->action, psig->mask, psig->code);
E 16
I 16
		(void)printf("caught handler=0x%lx mask=0x%x code=0x%x\n",
		    (u_long)psig->action, psig->mask, psig->code);
E 16
I 13
}

ktrcsw(cs)
	struct ktr_csw *cs;
{
	(void)printf("%s %s\n", cs->out ? "stop" : "resume",
D 17
		cs->user ? "user" : "kernel");
E 17
I 17
	    cs->user ? "user" : "kernel");
E 17
E 13
}

usage()
{
	(void)fprintf(stderr,
	    "usage: kdump [-dnlRT] [-f trfile] [-m maxdata] [-t [cnis]]\n");
	exit(1);
E 10
E 7
E 4
}
D 3

E 3
E 2
E 1
