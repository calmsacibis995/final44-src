h26397
s 00001/00001/00076
d D 5.6 91/04/11 11:20:02 sklower 13 12
c include vaxuba -> vax/uba + -I/sys
e
s 00001/00011/00076
d D 5.5 90/06/01 18:55:52 bostic 12 11
c new copyright notice
e
s 00018/00007/00069
d D 5.4 90/01/05 18:01:39 bostic 11 10
c written by Helge Skrivervik; Berkeley copyright notice
e
s 00004/00003/00072
d D 5.3 89/05/11 14:15:48 bostic 10 7
c file reorg, pathnames.h, paths.h
e
s 00003/00001/00088
d R 5.4 87/06/03 00:22:10 bostic 9 8
c vax specific changes
e
s 00014/00000/00075
d R 5.3 87/05/30 16:16:30 bostic 8 7
c rxformat is a vax specific program
e
s 00021/00013/00054
d D 5.2 85/08/28 09:34:16 bloom 7 6
c fix return status and format anyway if stdin not a tty
e
s 00013/00001/00054
d D 5.1 85/05/28 15:32:52 dist 6 5
c Add copyright
e
s 00003/00001/00052
d D 4.5 83/08/11 22:51:47 sam 5 4
c standardize sccs keyword lines
e
s 00005/00005/00048
d D 4.4 83/06/02 17:38:45 sam 4 3
c file.h
e
s 00013/00005/00040
d D 4.3 83/05/08 20:14:21 helge 3 2
c ok
e
s 00001/00000/00044
d D 4.2 83/04/28 11:50:30 helge 2 1
c added id keywords
e
s 00044/00000/00000
d D 4.1 83/04/28 11:49:32 helge 1 0
c date and time created 83/04/28 11:49:32 by helge
e
u
U
t
T
I 6
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
 *
D 12
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
 */

E 6
I 2
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
#ifndef lint
I 6
char copyright[] =
D 11
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 11
I 11
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 11
 All rights reserved.\n";
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11

#ifndef lint
E 6
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif
E 6
I 6
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11
E 6
E 5
E 2
I 1

D 10
#include <stdio.h>
E 10
#include <sys/file.h>
D 10
#include <errno.h>
E 10
D 4
#include "/sys/vaxuba/rxreg.h"
E 4
I 4
D 13
#include <vaxuba/rxreg.h>
E 13
I 13
#include <vax/uba/rxreg.h>
E 13
I 10
D 11
#include "pathnames.h"
E 11
#include <stdio.h>
#include <errno.h>
I 11
#include "pathnames.h"
E 11
E 10
E 4

I 3
D 10
char devname[] = "/dev/rrx?a";
E 10
I 10
char devname[] = _PATH_DEVNAME;
E 10

E 3
/*
D 4
 * format floppy disks on RX02
E 4
I 4
 * Format RX02 floppy disks.
E 4
 */
I 3

E 3
main(argc, argv)
	int argc;
	char *argv[];
{
	int fd, idens = 0, filarg = 1;
I 7
	int i, c;
E 7

D 7
	if (argc < 2)
E 7
I 7
	if (argc < 2 || argc > 3)
E 7
		usage();
	if (argc == 3) { 
		if (strncmp(argv[1],"-d",2) != 0)
			usage();
		idens++;
D 3
		filarg = 2;
E 3
I 3
		filarg++;
E 3
	}
D 3
	if ((fd = open(argv[filarg], FRDWR, 0666)) < NULL) {
		perror(argv[filarg]);
E 3
I 3
	devname[8] = argv[filarg][7];
D 4
	if ((fd = open(devname, FRDWR, 0600)) < NULL) {
E 4
I 4
D 7
	if ((fd = open(devname, O_RDWR)) < NULL) {
E 7
I 7
	if ((fd = open(devname, O_RDWR)) < 0) {
E 7
E 4
		perror(devname);
E 3
D 7
		exit (0);
E 7
I 7
		exit(1);
E 7
	}
D 3
	printf("Format %s to", *(argv[filarg]));
E 3
I 3
D 7
	printf("Format %s to", argv[filarg]);
E 3
	if (idens)
		printf(" double density (y/n) ?");
	else
		printf(" single density (y/n) ?");
	if (getchar() != 'y')
		exit (0);
E 7
I 7
	if (isatty(fileno(stdin))) {
		printf("Format %s to %s density (y/n)? ",
			argv[filarg], idens ? "double" : "single");
		i = c = getchar();
		while (c != '\n' && c != EOF)
			c = getchar();
		if (i != 'y')
			exit(0);
	} else
		printf("Formatting %s to %s density\n",
			argv[filarg], idens ? "double" : "single");
E 7
I 3
	/* 
D 4
	 * change the ioctl command when dkio.h has
	 * been finished
E 4
I 4
	 * Change the ioctl command when dkio.h has
	 * been finished.
E 4
	 */
E 3
D 7
	if (ioctl(fd, RXIOC_FORMAT, &idens) != NULL)
E 7
I 7
	if (ioctl(fd, RXIOC_FORMAT, &idens) == 0)
		exit(0);
	else {
E 7
D 3
		perror(argv[2]);
E 3
I 3
		perror(devname);
E 3
D 7
	close (fd);
E 7
I 7
		exit(1);
	}
E 7
}

usage()
{
	fprintf(stderr, "usage: rxformat [-d] /dev/rx?\n");
D 7
	exit (0);
E 7
I 7
	exit(1);
E 7
}
E 1
