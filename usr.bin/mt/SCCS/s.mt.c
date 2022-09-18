h56514
s 00005/00003/00245
d D 8.2 95/05/04 15:44:51 bostic 21 20
c optarg/optind moved to unistd.h
e
s 00005/00005/00243
d D 8.1 93/06/06 15:39:34 bostic 20 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00246
d R 5.9 93/05/15 11:18:47 torek 19 18
c make it compile on sparc
e
s 00105/00057/00143
d D 5.8 91/12/18 12:55:19 bostic 18 17
c lint + no exit() in main from Guy Harris; add getopt(3) and other minor
c cleanups as well.  (The end of the "grok" error message, *sniff*)
e
s 00005/00005/00195
d D 5.7 91/11/13 09:10:08 bostic 17 16
c VAX subdirectory has been broken up
e
s 00002/00001/00198
d D 5.6 91/06/06 09:58:02 bostic 16 15
c CMU/Mach fix; don't use magic numbers in open call
e
s 00004/00004/00195
d D 5.5 91/01/14 17:32:24 bostic 15 14
c kernel reorg
e
s 00001/00011/00198
d D 5.4 90/06/01 17:06:05 bostic 14 13
c new copyright notice
e
s 00017/00006/00192
d D 5.3 88/08/31 13:58:23 bostic 13 12
c add Berkeley specific copyright
e
s 00007/00000/00191
d D 5.2 86/10/13 16:41:11 sam 12 11
c add tahoe cipher 
e
s 00016/00001/00175
d D 5.1 85/04/30 15:04:48 dist 11 10
c Add copyright
e
s 00005/00005/00171
d D 4.8 83/05/08 14:28:53 sam 10 9
c arg checking out of order
e
s 00003/00003/00173
d D 4.7 83/02/09 13:17:22 sam 9 8
c from sun
e
s 00000/00004/00176
d D 4.6 83/02/08 23:28:32 sam 8 7
c yank sun changes -- no longer used
e
s 00026/00010/00154
d D 4.5 83/01/02 14:32:04 sam 7 6
c from sun
e
s 00010/00005/00154
d D 4.4 82/12/19 13:09:03 sam 6 5
c include files rearranged
e
s 00111/00020/00048
d D 4.3 81/11/12 16:42:13 sam 5 4
c major overhaul, plus addition of status command
e
s 00012/00014/00056
d D 4.2 81/07/05 22:14:44 root 4 1
c open tape only as needed and only once
e
s 00003/00006/00065
d R 4.3 81/07/05 22:12:50 root 3 2
c only one open of tape
e
s 00015/00014/00056
d R 4.2 81/07/05 22:11:03 root 2 1
c open tape r/w only when needed
e
s 00070/00000/00000
d D 4.1 81/05/11 03:13:39 root 1 0
c date and time created 81/05/11 03:13:39 by root
e
u
U
t
T
I 1
D 11
static	char *sccsid = "%W% (Berkeley) %E%";
E 11
I 11
/*
D 13
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
D 20
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 14
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 13
 */

#ifndef lint
D 20
char copyright[] =
D 13
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 13
I 13
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 13
 All rights reserved.\n";
E 20
I 20
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 20
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13

E 11
D 5

E 5
/*
D 5
 * mt
E 5
I 5
 * mt --
 *   magnetic tape manipulation program
E 5
 */
D 5

E 5
D 15
#include <stdio.h>
#include <ctype.h>
E 15
#include <sys/types.h>
D 15
#include <sys/mtio.h>
E 15
#include <sys/ioctl.h>
I 15
#include <sys/mtio.h>
I 16
D 21
#include <fcntl.h>
E 21
I 21

#include <ctype.h>
E 21
I 18
#include <errno.h>
D 21
#include <stdlib.h>
E 21
I 21
#include <fcntl.h>
E 21
E 18
E 16
#include <stdio.h>
D 21
#include <ctype.h>
E 21
I 21
#include <stdlib.h>
E 21
I 18
#include <string.h>
I 21
#include <unistd.h>
E 21
E 18
E 15

I 5
D 18
#define	equal(s1,s2)	(strcmp(s1, s2) == 0)
D 7
#define	DEFTAPE		"/dev/rmt12"
E 7

E 18
E 5
struct commands {
	char *c_name;
	int c_code;
I 4
	int c_ronly;
E 4
} com[] = {
D 4
	"eof",	MTWEOF,
	"fsf",	MTFSF,
	"bsf",	MTBSF,
	"fsr",	MTFSR,
	"bsr",	MTBSR,
	"rewind",	MTREW,
	"offline",	MTOFFL,
E 4
I 4
D 5
	"eof",	MTWEOF,	0,
	"fsf",	MTFSF,	1,
	"bsf",	MTBSF,	1,
	"fsr",	MTFSR,	1,
	"bsr",	MTBSR,	1,
	"rewind",	MTREW,	1,
	"offline",	MTOFFL,	1,
E 4
	0,0
E 5
I 5
D 18
	{ "weof",	MTWEOF,	0 },
E 18
I 18
	{ "bsf",	MTBSF,	1 },
	{ "bsr",	MTBSR,	1 },
E 18
	{ "eof",	MTWEOF,	0 },
	{ "fsf",	MTFSF,	1 },
D 18
	{ "bsf",	MTBSF,	1 },
E 18
	{ "fsr",	MTFSR,	1 },
D 18
	{ "bsr",	MTBSR,	1 },
	{ "rewind",	MTREW,	1 },
E 18
	{ "offline",	MTOFFL,	1 },
I 18
	{ "rewind",	MTREW,	1 },
E 18
	{ "rewoffl",	MTOFFL,	1 },
	{ "status",	MTNOP,	1 },
I 7
D 8
	{ "tense",	MTTENSE,1 },
	{ "tension",	MTTENSE,1 },
	{ "retension",	MTTENSE,1 },
	{ "erase",	MTERASE,1 },
E 8
E 7
D 18
	{ 0 }
E 18
I 18
	{ "weof",	MTWEOF,	0 },
	{ NULL }
E 18
E 5
};

D 18
int mtfd;
struct mtop mt_com;
I 5
struct mtget mt_status;
E 5
char *tape;
E 18
I 18
void err __P((const char *, ...));
void printreg __P((char *, u_int, char *));
void status __P((struct mtget *));
void usage __P((void));
E 18

I 18
int
E 18
main(argc, argv)
D 5
char **argv;
E 5
I 5
D 18
	char **argv;
E 18
I 18
	int argc;
	char *argv[];
E 18
E 5
{
D 18
	char line[80], *getenv();
	register char *cp;
E 18
	register struct commands *comp;
I 18
	struct mtget mt_status;
	struct mtop mt_com;
	int ch, len, mtfd;
	char *p, *tape;
E 18

D 10
	if (argc < 2) {
D 5
		fprintf(stderr, "usage: mt [ -t tape ] command [ count ]\n");
E 5
I 5
		fprintf(stderr, "usage: mt [ -f device ] command [ count ]\n");
E 5
		exit(1);
	}
D 5
	if ((strcmp(argv[1], "-t") == 0) && argc > 2) {
E 5
I 5
	if ((equal(argv[1], "-t") || equal(argv[1], "-f")) && argc > 2) {
E 10
I 10
D 18
	if (argc > 2 && (equal(argv[1], "-t") || equal(argv[1], "-f"))) {
E 10
E 5
		argc -= 2;
		tape = argv[2];
		argv += 2;
	} else
		if ((tape = getenv("TAPE")) == NULL)
D 5
			tape = "/dev/rmt12";
E 5
I 5
			tape = DEFTAPE;
I 10
	if (argc < 2) {
		fprintf(stderr, "usage: mt [ -f device ] command [ count ]\n");
		exit(1);
	}
E 10
E 5
D 4
	if ((mtfd = open(tape, 2)) < 0) {
		if ((mtfd = open(tape, 0)) < 0) {
			perror(tape);
			exit(1);
		}
	}

E 4
	cp = argv[1];
	for (comp = com; comp->c_name != NULL; comp++)
		if (strncmp(cp, comp->c_name, strlen(cp)) == 0)
E 18
I 18
	if ((tape = getenv("TAPE")) == NULL)
		tape = DEFTAPE;

	while ((ch = getopt(argc, argv, "f:t:")) != EOF)
		switch(ch) {
		case 'f':
		case 't':
			tape = optarg;
E 18
			break;
D 18
	if (comp->c_name == NULL) {
		fprintf(stderr, "mt: don't grok \"%s\"\n", cp);
I 4
		exit(1);
E 18
I 18
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc < 1 || argc > 2)
		usage();

	len = strlen(p = *argv++);
	for (comp = com;; comp++) {
		if (comp->c_name == NULL)
			err("%s: unknown command", p);
		if (strncmp(p, comp->c_name, len) == 0)
			break;
E 18
	}
D 16
	if ((mtfd = open(tape, comp->c_ronly ? 0 : 2)) < 0) {
E 16
I 16
D 18
	if ((mtfd = open(tape, comp->c_ronly ? O_RDONLY : O_RDWR)) < 0) {
E 16
		perror(tape);
E 4
		exit(1);
	}
E 18
I 18
	if ((mtfd = open(tape, comp->c_ronly ? O_RDONLY : O_RDWR)) < 0)
		err("%s: %s", tape, strerror(errno));
E 18
D 5
	mt_com.mt_count = (argc > 2 ? atoi(argv[2]) : 1);
	mt_com.mt_op = comp->c_code;
	if (ioctl(mtfd, MTIOCTOP, &mt_com) < 0) {
		fprintf(stderr, "%s %d ", comp->c_name, mt_com.mt_count);
		perror("failed");
E 5
I 5
	if (comp->c_code != MTNOP) {
		mt_com.mt_op = comp->c_code;
D 18
		mt_com.mt_count = (argc > 2 ? atoi(argv[2]) : 1);
		if (mt_com.mt_count < 0) {
			fprintf(stderr, "mt: negative repeat count\n");
			exit(1);
E 18
I 18
		if (*argv) {
			mt_com.mt_count = strtol(*argv, &p, 10);
			if (mt_com.mt_count <= 0 || *p)
				err("%s: illegal count", *argv);
E 18
		}
D 18
		if (ioctl(mtfd, MTIOCTOP, &mt_com) < 0) {
D 7
			fprintf(stderr, "%s %d ", comp->c_name,
E 7
I 7
			fprintf(stderr, "%s %s %d ", tape, comp->c_name,
E 7
				mt_com.mt_count);
			perror("failed");
			exit(2);
		}
E 18
I 18
		else
			mt_com.mt_count = 1;
		if (ioctl(mtfd, MTIOCTOP, &mt_com) < 0)
			err("%s: %s: %s", tape, comp->c_name, strerror(errno));
E 18
	} else {
D 18
		if (ioctl(mtfd, MTIOCGET, (char *)&mt_status) < 0) {
			perror("mt");
			exit(2);
		}
E 18
I 18
		if (ioctl(mtfd, MTIOCGET, &mt_status) < 0)
			err("%s", strerror(errno));
E 18
		status(&mt_status);
	}
I 18
	exit (0);
	/* NOTREACHED */
E 18
}

D 6
#include <sys/mtreg.h>
#include <sys/utreg.h>
#include <sys/htreg.h>
#include <sys/tmreg.h>
E 6
I 6
#ifdef vax
D 17
#include <vaxmba/mtreg.h>
#include <vaxmba/htreg.h>
E 17
I 17
#include <vax/mba/mtreg.h>
#include <vax/mba/htreg.h>
E 17

D 17
#include <vaxuba/utreg.h>
#include <vaxuba/tmreg.h>
E 17
I 17
#include <vax/uba/utreg.h>
#include <vax/uba/tmreg.h>
E 17
E 6
#undef b_repcnt		/* argh */
D 6
#include <sys/tsreg.h>
E 6
I 6
D 17
#include <vaxuba/tsreg.h>
E 17
I 17
#include <vax/uba/tsreg.h>
E 17
#endif
E 6

I 7
#ifdef sun
D 9
#include <sys/tmreg.h>
#include <sys/arreg.h>
E 9
I 9
#include <sundev/tmreg.h>
#include <sundev/arreg.h>
E 9
#endif

I 12
#ifdef tahoe
D 15
#include <tahoevba/cyreg.h>
E 15
I 15
#include <tahoe/vba/cyreg.h>
E 15
#endif

E 12
E 7
struct tape_desc {
	short	t_type;		/* type of magtape device */
	char	*t_name;	/* printing name */
	char	*t_dsbits;	/* "drive status" register */
	char	*t_erbits;	/* "error" register */
} tapes[] = {
I 6
#ifdef vax
E 6
	{ MT_ISTS,	"ts11",		0,		TSXS0_BITS },
	{ MT_ISHT,	"tm03",		HTDS_BITS,	HTER_BITS },
	{ MT_ISTM,	"tm11",		0,		TMER_BITS },
	{ MT_ISMT,	"tu78",		MTDS_BITS,	0 },
	{ MT_ISUT,	"tu45",		UTDS_BITS,	UTER_BITS },
I 6
#endif
I 7
#ifdef sun
	{ MT_ISCPC,	"TapeMaster",	TMS_BITS,	0 },
D 9
	{ MT_ISARCH,	"Archive",	ARCH_CTRL_BITS,	ARCH_BITS },
E 9
I 9
	{ MT_ISAR,	"Archive",	ARCH_CTRL_BITS,	ARCH_BITS },
I 12
#endif
#ifdef tahoe
	{ MT_ISCY,	"cipher",	CYS_BITS,	CYCW_BITS },
E 12
E 9
#endif
E 7
E 6
	{ 0 }
};

/*
 * Interpret the status buffer returned
 */
I 18
void
E 18
status(bp)
	register struct mtget *bp;
{
	register struct tape_desc *mt;

D 18
	for (mt = tapes; mt->t_type; mt++)
E 18
I 18
	for (mt = tapes;; mt++) {
		if (mt->t_type == 0) {
			(void)printf("%d: unknown tape drive type\n",
			    bp->mt_type);
			return;
		}
E 18
		if (mt->t_type == bp->mt_type)
			break;
D 18
	if (mt->t_type == 0) {
		printf("unknown tape drive type (%d)\n", bp->mt_type);
		return;
E 18
	}
D 7
	printf("%s tape drive\n", mt->t_name);
E 7
I 7
D 18
	printf("%s tape drive, residual=%d\n", mt->t_name, bp->mt_resid);
E 18
I 18
	(void)printf("%s tape drive, residual=%d\n", mt->t_name, bp->mt_resid);
E 18
E 7
	printreg("ds", bp->mt_dsreg, mt->t_dsbits);
D 7
	printreg(" er", bp->mt_erreg, mt->t_erbits);
	printf("\nresidual=%d\n", bp->mt_resid);
E 7
I 7
	printreg("\ner", bp->mt_erreg, mt->t_erbits);
D 18
	putchar('\n');
E 18
I 18
	(void)putchar('\n');
E 18
E 7
}

/*
D 18
 * Print a register a la the %b format of the kernel's printf
E 18
I 18
 * Print a register a la the %b format of the kernel's printf.
E 18
 */
I 18
void
E 18
printreg(s, v, bits)
D 7
	char *s, *bits;
	unsigned short v;
E 7
I 7
	char *s;
I 18
	register u_int v;
E 18
	register char *bits;
D 18
	register unsigned short v;
E 18
E 7
{
	register int i, any = 0;
	register char c;

D 7
	printf("%s=%o", s, v);
E 7
I 7
	if (bits && *bits == 8)
		printf("%s=%o", s, v);
	else
		printf("%s=%x", s, v);
	bits++;
E 7
	if (v && bits) {
		putchar('<');
		while (i = *bits++) {
			if (v & (1 << (i-1))) {
				if (any)
					putchar(',');
				any = 1;
				for (; (c = *bits) > 32; bits++)
					putchar(c);
			} else
				for (; *bits > 32; bits++)
					;
		}
D 7
		if (any)
			putchar('>');
E 7
I 7
		putchar('>');
E 7
E 5
	}
I 18
}

void
usage()
{
	(void)fprintf(stderr, "usage: mt [-f device] command [ count ]\n");
	exit(1);
}

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
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "mt: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 18
}
E 1
