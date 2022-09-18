h26462
s 00010/00004/00065
d D 8.3 95/03/29 21:24:36 mckusick 3 2
c allow setting of alternate flags (from FreeBSD
e
s 00009/00001/00060
d D 8.2 94/06/23 22:10:33 mckusick 2 1
c handle userquota and groupquota (from deraadt@fsa.ca)
e
s 00061/00000/00000
d D 8.1 94/03/27 08:07:39 bostic 1 0
c date and time created 94/03/27 08:07:39 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/mount.h>

#include <err.h>
#include <errno.h>
#include <fstab.h>
#include <stdlib.h>
#include <string.h>

#include "mntopts.h"

I 3
int getmnt_silent = 0;

E 3
void
D 3
getmntopts(options, m0, flagp)
E 3
I 3
getmntopts(options, m0, flagp, altflagp)
E 3
	const char *options;
	const struct mntopt *m0;
	int *flagp;
I 3
	int *altflagp;
E 3
{
	const struct mntopt *m;
	int negative;
D 2
	char *opt, *optbuf;
E 2
I 2
	char *opt, *optbuf, *p;
I 3
	int *thisflagp;
E 3
E 2

	/* Copy option string, since it is about to be torn asunder... */
	if ((optbuf = strdup(options)) == NULL)
		err(1, NULL);

	for (opt = optbuf; (opt = strtok(opt, ",")) != NULL; opt = NULL) {
		/* Check for "no" prefix. */
		if (opt[0] == 'n' && opt[1] == 'o') {
			negative = 1;
			opt += 2;
		} else
			negative = 0;
I 2

		/*
		 * for options with assignments in them (ie. quotas)
		 * ignore the assignment as it's handled elsewhere
		 */
		p = strchr(opt, '=');
		if (p)
			 *p = '\0';
E 2

		/* Scan option table. */
		for (m = m0; m->m_option != NULL; ++m)
			if (strcasecmp(opt, m->m_option) == 0)
				break;

		/* Save flag, or fail if option is not recognised. */
		if (m->m_option) {
I 3
			thisflagp = m->m_altloc ? altflagp : flagp;
E 3
			if (negative == m->m_inverse)
D 3
				*flagp |= m->m_flag;
E 3
I 3
				*thisflagp |= m->m_flag;
E 3
			else
D 3
				*flagp &= ~m->m_flag;
		} else
E 3
I 3
				*thisflagp &= ~m->m_flag;
		} else if (!getmnt_silent) {
E 3
			errx(1, "-o %s: option not supported", opt);
I 3
		}
E 3
	}

	free(optbuf);
}
E 1
