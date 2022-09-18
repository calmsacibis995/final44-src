h60542
s 00001/00000/00136
d D 8.2 95/05/04 15:48:13 bostic 6 5
c optarg/optind moved to unistd.h
e
s 00005/00005/00131
d D 8.1 93/06/06 16:40:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00135
d D 5.4 93/04/28 10:43:54 bostic 4 3
c <sys/sysctl.h> now needs <sys/param.h>
e
s 00016/00016/00120
d D 5.3 93/04/27 10:41:01 bostic 3 2
c name -> mib
e
s 00050/00022/00086
d D 5.2 93/03/05 14:26:43 bostic 2 1
c second version, it really works now
e
s 00108/00000/00000
d D 5.1 93/03/05 10:22:26 bostic 1 0
c date and time created 93/03/05 10:22:26 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 5
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 4
#include <sys/types.h>
E 4
I 4
#include <sys/param.h>
E 4
#include <sys/sysctl.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
I 6
#include <unistd.h>
E 6

void usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
{
#define	MFLAG	0x01
#define	NFLAG	0x02
#define	RFLAG	0x04
#define	SFLAG	0x08
#define	VFLAG	0x10
	u_int flags;
D 3
	int ch, name[2];
E 3
I 3
	int ch, mib[2];
E 3
D 2
	size_t len;
	char *prefix, buf[1024];
E 2
I 2
	size_t len, tlen;
	char *p, *prefix, buf[1024];
E 2

	flags = 0;
	while ((ch = getopt(argc, argv, "amnrsv")) != EOF)
		switch(ch) {
		case 'a':
			flags |= (MFLAG | NFLAG | RFLAG | SFLAG | VFLAG);
			break;
		case 'm':
			flags |= MFLAG;
			break;
		case 'n':
			flags |= NFLAG;
			break;
		case 'r':
			flags |= RFLAG;
			break;
		case 's':
			flags |= SFLAG;
			break;
		case 'v':
			flags |= VFLAG;
			break;
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc)
		usage();

	if (!flags)
		flags |= SFLAG;

	prefix = "";

D 2
#define SHOW(l1, l2) {						\
	name[0] = l1;							\
	name[1] = l2;							\
	len = sizeof(buf);						\
	if (sysctl(name, 2, &buf, &len, NULL, 0) == -1)			\
		err(1, "sysctl");					\
	(void)printf("%s%.*s", prefix, len, buf);			\
	prefix = " ";							\
}
	if (flags & SFLAG)
		SHOW(CTL_KERN, KERN_OSTYPE);
	if (flags & NFLAG)
		SHOW(CTL_KERN, KERN_HOSTNAME);
	if (flags & RFLAG)
		SHOW(CTL_KERN, KERN_OSRELEASE);
	if (flags & VFLAG)
		SHOW(CTL_KERN, KERN_OSREV);
	if (flags & MFLAG)
		SHOW(CTL_HW, HW_MACHINE);

E 2
I 2
	if (flags & SFLAG) {
D 3
		name[0] = CTL_KERN;
		name[1] = KERN_OSTYPE;
E 3
I 3
		mib[0] = CTL_KERN;
		mib[1] = KERN_OSTYPE;
E 3
		len = sizeof(buf);
D 3
		if (sysctl(name, 2, &buf, &len, NULL, 0) == -1)
E 3
I 3
		if (sysctl(mib, 2, &buf, &len, NULL, 0) == -1)
E 3
			err(1, "sysctl");
		(void)printf("%s%.*s", prefix, len, buf);
		prefix = " ";
	}
	if (flags & NFLAG) {
D 3
		name[0] = CTL_KERN;
		name[1] = KERN_HOSTNAME;
E 3
I 3
		mib[0] = CTL_KERN;
		mib[1] = KERN_HOSTNAME;
E 3
		len = sizeof(buf);
D 3
		if (sysctl(name, 2, &buf, &len, NULL, 0) == -1)
E 3
I 3
		if (sysctl(mib, 2, &buf, &len, NULL, 0) == -1)
E 3
			err(1, "sysctl");
		(void)printf("%s%.*s", prefix, len, buf);
		prefix = " ";
	}
	if (flags & RFLAG) {
D 3
		name[0] = CTL_KERN;
		name[1] = KERN_OSRELEASE;
E 3
I 3
		mib[0] = CTL_KERN;
		mib[1] = KERN_OSRELEASE;
E 3
		len = sizeof(buf);
D 3
		if (sysctl(name, 2, &buf, &len, NULL, 0) == -1)
E 3
I 3
		if (sysctl(mib, 2, &buf, &len, NULL, 0) == -1)
E 3
			err(1, "sysctl");
		(void)printf("%s%.*s", prefix, len, buf);
		prefix = " ";
	}
	if (flags & VFLAG) {
D 3
		name[0] = CTL_KERN;
		name[1] = KERN_VERSION;
E 3
I 3
		mib[0] = CTL_KERN;
		mib[1] = KERN_VERSION;
E 3
		len = sizeof(buf);
D 3
		if (sysctl(name, 2, &buf, &len, NULL, 0) == -1)
E 3
I 3
		if (sysctl(mib, 2, &buf, &len, NULL, 0) == -1)
E 3
			err(1, "sysctl");
		for (p = buf, tlen = len; tlen--; ++p)
			if (*p == '\n' || *p == '\t')
				*p = ' ';
		(void)printf("%s%.*s", prefix, len, buf);
		prefix = " ";
	}
	if (flags & MFLAG) {
D 3
		name[0] = CTL_HW;
		name[1] = HW_MACHINE;
E 3
I 3
		mib[0] = CTL_HW;
		mib[1] = HW_MACHINE;
E 3
		len = sizeof(buf);
D 3
		if (sysctl(name, 2, &buf, &len, NULL, 0) == -1)
E 3
I 3
		if (sysctl(mib, 2, &buf, &len, NULL, 0) == -1)
E 3
			err(1, "sysctl");
		(void)printf("%s%.*s", prefix, len, buf);
		prefix = " ";
	}
E 2
	(void)printf("\n");
	exit (0);
}

void
usage()
{
	(void)fprintf(stderr, "usage: uname [-amnrsv]\n");
	exit(1);
}
E 1
