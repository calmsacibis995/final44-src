h32530
s 00001/00000/00122
d D 8.2 93/12/09 17:03:10 hibler 10 9
c close file on read error or bad header
e
s 00005/00005/00117
d D 8.1 93/06/06 16:20:51 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00092/00032/00030
d D 5.1 92/03/02 14:23:29 bostic 8 7
c don't drop core if no arguments, use getopt(3) for cleanliness
e
s 00001/00011/00061
d D 4.7 90/06/01 16:10:19 bostic 7 6
c new copyright notice
e
s 00010/00005/00062
d D 4.6 88/06/18 13:20:46 bostic 6 5
c install approved copyright notice
e
s 00047/00033/00020
d D 4.5 88/06/08 19:44:26 bostic 5 4
c rewritten from manual page; added Berkeley specific header
e
s 00004/00000/00049
d D 4.4 85/04/22 08:17:26 bloom 4 3
c add exit value 
e
s 00002/00002/00047
d D 4.3 81/07/02 15:41:10 root 3 2
c fix per bill jolitz
e
s 00014/00006/00035
d D 4.2 80/10/10 00:56:14 bill 2 1
c cleanup of format
e
s 00041/00000/00000
d D 4.1 80/10/01 17:28:25 bill 1 0
c date and time created 80/10/01 17:28:25 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 5
static	char *sccsid = "%W% (Berkeley) %G%";
E 5
E 2
/*
D 5
 * size
E 5
I 5
D 9
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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
 * %sccs.include.redist.c%
E 7
E 6
E 5
 */
I 2

E 2
D 5
#include	<stdio.h>
#include 	<a.out.h>
E 5
I 5
#ifndef lint
D 9
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */
E 5

I 2
D 5
int	header;
E 5
I 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

I 5
#include <sys/param.h>
#include <sys/file.h>
I 8
#include <errno.h>
E 8
#include <a.out.h>
I 8
#include <unistd.h>
#include <stdlib.h>
E 8
#include <stdio.h>
I 8
#include <string.h>
E 8

I 8
void	err __P((const char *, ...));
int	show __P((int, char *));
void	usage __P((void));

int
E 8
E 5
E 2
main(argc, argv)
D 5
char **argv;
E 5
I 5
	int argc;
D 8
	char **argv;
E 8
I 8
	char *argv[];
E 8
E 5
{
I 8
	int ch, eval;

	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	eval = 0;
	if (*argv)
		do {
			eval |= show(argc, *argv);
		} while (*++argv);
	else
		eval |= show(1, "a.out");
	exit(eval);
}

int
show(count, name)
	int count;
	char *name;
{
	static int first = 1;
E 8
D 5
	struct exec buf;
	long sum;
	int gorp,i;
I 4
	int err = 0;
E 4
	FILE *f;
E 5
I 5
	struct exec head;
	u_long total;
D 8
	int exval, fd, first;
E 8
I 8
	int fd;
E 8
E 5

D 5
	if (argc==1) {
E 5
I 5
D 8
	if (!*argv[1])
E 5
		*argv = "a.out";
D 5
		argc++;
		--argv;
	}
	gorp = argc;
	while(--argc) {
E 5
I 5
	else
E 5
		++argv;
D 5
		if ((f = fopen(*argv, "r"))==NULL) {
			printf("size: %s not found\n", *argv);
I 4
			err++;
E 5
I 5
	for (first = 1, exval = 0; *argv; ++argv) {
		if ((fd = open(*argv, O_RDONLY, 0)) < 0) {
			fprintf(stderr, "size: ");
			perror(*argv);
			exval = 1;
E 5
E 4
			continue;
		}
D 3
		fread((char *)&buf, sizeof(buf), 1, f);
D 2
		if (N_BADMAG(buf)) {
E 2
I 2
		if(N_BADMAG(buf)) {
E 3
I 3
D 5
		if (fread((char *)&buf, sizeof(buf), 1, f) != 1 ||
		    N_BADMAG(buf)) {
E 3
E 2
			printf("size: %s not an object file\n", *argv);
			fclose(f);
I 4
			err++;
E 5
I 5
		if (read(fd, (char *)&head, sizeof(head)) != sizeof(head) ||
		    N_BADMAG(head)) {
			fprintf(stderr, "size: %s: not in a.out format.\n",
			    *argv);
			exval = 1;
E 5
E 4
			continue;
		}
D 2
		if (gorp>2)
			printf("%s: ", *argv);
		printf("%u+%u+%u = ", buf.a_text,buf.a_data,buf.a_bss);
E 2
I 2
D 5
		if (header == 0) {
E 5
I 5
		(void)close(fd);
		if (first) {
			first = 0;
E 5
			printf("text\tdata\tbss\tdec\thex\n");
D 5
			header = 1;
E 5
		}
D 5
		printf("%u\t%u\t%u\t", buf.a_text,buf.a_data,buf.a_bss);
E 2
		sum = (long) buf.a_text + (long) buf.a_data + (long) buf.a_bss;
D 2
		printf("%Db = 0x%Xb\n", sum, sum);
E 2
I 2
		printf("%ld\t%lx", sum, sum);
		if (gorp>2)
E 5
I 5
		total = head.a_text + head.a_data + head.a_bss;
		printf("%lu\t%lu\t%lu\t%lu\t%lx", head.a_text, head.a_data,
		    head.a_bss, total, total);
		if (argc > 2)
E 5
			printf("\t%s", *argv);
		printf("\n");
E 8
I 8
	if ((fd = open(name, O_RDONLY, 0)) < 0) {
		err("%s: %s", name, strerror(errno));
		return (1);
E 8
E 2
D 5
		fclose(f);
E 5
	}
I 4
D 5
	exit(err);
E 5
I 5
D 8
	exit(exval);
E 8
I 8
	if (read(fd, &head, sizeof(head)) != sizeof(head) || N_BADMAG(head)) {
I 10
		(void)close(fd);
E 10
		err("%s: not in a.out format", name);
		return (1);
	}
	(void)close(fd);

	if (first) {
		first = 0;
		(void)printf("text\tdata\tbss\tdec\thex\n");
	}
	total = head.a_text + head.a_data + head.a_bss;
	(void)printf("%lu\t%lu\t%lu\t%lu\t%lx", head.a_text, head.a_data,
	    head.a_bss, total, total);
	if (count > 1)
		(void)printf("\t%s", name);
	(void)printf("\n");
	return (0);
}

void
usage()
{
	(void)fprintf(stderr, "usage: size [file ...]\n");
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
	(void)fprintf(stderr, "size: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 8
E 5
E 4
}
E 1
