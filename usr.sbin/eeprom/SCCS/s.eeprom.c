h42619
s 00005/00005/00173
d D 8.1 93/06/06 13:57:08 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00007/00168
d D 5.2 93/04/27 19:42:36 bostic 2 1
c fix the coypright notice
e
s 00175/00000/00000
d D 5.1 93/04/27 18:36:30 torek 1 0
c date and time created 93/04/27 18:36:30 by torek
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
E 2
I 2
D 3
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
 *
 * %sccs.include.redist.c%
D 2
 *
 *	%W% (Berkeley) %G%
E 2
 */
I 2

E 2
#ifndef lint
D 2
const char copyright[] =
"@(#) Copyright (c) 1992 Lawrence Berkeley Laboratory\nAll rights reserved.\n";
static const char sccsid[] = "%W% (Berkeley) %G%";
#endif
E 2
I 2
D 3
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 3
I 3
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 3
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

/*
 * eeprom - openprom control utility
 *
 * usage:
 *
 *	eeprom [field] [field=value]
 */

#include <sys/types.h>
#include <sys/file.h>
#include <sys/ioctl.h>

#include <machine/openpromio.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pathnames.h"

static	char openprom[] = _PATH_OPENPROM;
static	char usage[] = "usage: %s [field] [field=value]\n";

int
main(argc, argv)
	int argc;
	char **argv;
{
	register char *cp;
	register int i, op, fd, flags, status;
	register struct opiocdesc *dp;
	struct opiocdesc desc;
	char buf[1024], buf2[sizeof(buf)];
	char *prog, *name;

	/* Determine simple program name for error messages */
	if (cp = rindex(argv[0], '/'))
		prog = cp + 1;
	else
		prog = argv[0];

	/* Parse flags */
	opterr = 0;
	while ((op = getopt(argc, argv, "")) != EOF)
		switch (op) {

		default:
			(void) fprintf(stderr, usage, prog);
			exit(1);
		}

	argc -= optind;
	argv += optind;

	/* Determine flags and open device */
	flags = O_RDONLY;
	for (i = 0; i < argc; ++i)
		if (index(argv[i], '=') != NULL) {
			flags = O_RDWR;
			break;
		}
	if ((fd = open(openprom, flags, 0)) < 0) {
		fprintf(stderr, "%s: open %s: %s\n",
		    prog, openprom, strerror(errno));
		exit(1);
	}

	dp = &desc;
	bzero(dp, sizeof(*dp));
	if (ioctl(fd, OPIOCGETOPTNODE, &dp->op_nodeid) < 0) {
		fprintf(stderr, "%s: get optionsnode: %s\n",
		    prog, strerror(errno));
		exit(1);
	}

	if (argc <= 0) {
		/* Prime the pump with a zero length name */
		dp->op_name = buf;
		dp->op_name[0] = '\0';
		dp->op_namelen = 0;
		dp->op_buf = buf2;
		for (;;) {
			/* Get the next property name */
			dp->op_buflen = sizeof(buf);
			if (ioctl(fd, OPIOCNEXTPROP, dp) < 0) {
				fprintf(stderr, "%s: get next: %s\n",
				    prog, strerror(errno));
				exit(1);
			}

			/* Zero length name means we're done */
			if (dp->op_buflen <= 0)
				break;

			/* Clever hack, swap buffers */
			cp = dp->op_buf;
			dp->op_buf = dp->op_name;
			dp->op_name = cp;
			dp->op_namelen = dp->op_buflen;

			/* Get the value */
			dp->op_buflen = sizeof(buf);
			if (ioctl(fd, OPIOCGET, dp) < 0) {
				fprintf(stderr, "%s: get \"%s\": %s\n",
				    prog, cp, strerror(errno));
				exit(1);
			}
			printf("%.*s=%.*s\n", dp->op_namelen, dp->op_name,
			    dp->op_buflen, dp->op_buf);
		}
		exit(0);
	}
	
	status = 0;
	for (i = 0; i < argc; ++i) {
		dp->op_name = name = argv[i];
		cp = index(name, '=');
		if (cp) {
			*cp++ = '\0';
			dp->op_buf = cp;
			dp->op_buflen = strlen(dp->op_buf);
		} else {
			dp->op_buf = buf;
			dp->op_buflen = sizeof(buf);
		}
		dp->op_namelen = strlen(name);
		if (ioctl(fd, cp ? OPIOCSET : OPIOCGET, dp) < 0) {
			fprintf(stderr, "%s: %s \"%s\": %s\n",
			    prog, cp ? "set" : "get", name, strerror(errno));
			status |= 1;
			continue;
		}

		/* If setting an entry, we're done */
		if (cp)
			continue;
		if (dp->op_buflen < 0) {
			fprintf(stderr, "%s: \"%s\" not found\n", prog, name);
			status |= 1;
			continue;
		}
		if (dp->op_buflen >= sizeof(buf)) {
			fprintf(stderr, "%s: \"%s\" truncated\n", prog, name);
			status |= 1;
			/* fall thorugh and print truncated value */
		}
		printf("%s=%.*s\n", name, dp->op_buflen, buf);
	}

	exit(status);
}
E 1
