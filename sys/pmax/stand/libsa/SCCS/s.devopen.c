h46476
s 00002/00002/00118
d D 8.1 93/06/10 23:30:32 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00120/00000/00000
d D 7.1 92/11/15 16:50:55 ralph 1 0
c date and time created 92/11/15 16:50:55 by ralph
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <stand/stand.h>

/*
 * Decode the string 'fname', open the device and return the remaining
 * file name if any.
 */
devopen(f, fname, file)
	struct open_file *f;
	char *fname;
	char **file;	/* out */
{
	register char *cp;
	register char *ncp;
	register struct devsw *dp;
	register int c, i;
	int ctlr = 0, unit = 0, part = 0;
	char namebuf[20];
	int rc;

	cp = fname;
	ncp = namebuf;

	/* look for a string like '5/rz0/vmunix' or '5/rz3f/vmunix */
	if ((c = *cp) >= '0' && c <= '9') {
		ctlr = c - '0';
		/* skip the '/' */
		if (*++cp != '/')
			return (ENXIO);
		cp++;
		while ((c = *cp) != '\0') {
			if (c == '/')
				break;
			if (c >= '0' && c <= '9') {
				/* read unit number */
				unit = c - '0';

				/* look for a partition */
				if ((c = *++cp) >= 'a' && c <= 'h') {
					part = c - 'a';
					c = *++cp;
				}
				if (c != '/')
					return (ENXIO);
				break;
			}
			if (ncp < namebuf + sizeof(namebuf) - 1)
				*ncp++ = c;
			cp++;
		}
	} else {
		/* expect a string like 'rz(0,0,0)vmunix' */
		while ((c = *cp) != '\0') {
			if (c == '(') {
				cp++;
				break;
			}
			if (ncp < namebuf + sizeof(namebuf) - 1)
				*ncp++ = c;
			cp++;
		}

		/* get controller number */
		if ((c = *cp) >= '0' && c <= '9') {
			ctlr = c - '0';
			c = *++cp;
		}

		if (c == ',') {
			/* get SCSI device number */
			if ((c = *++cp) >= '0' && c <= '9') {
				unit = c - '0';
				c = *++cp;
			}

			if (c == ',') {
				/* get partition number */
				if ((c = *++cp) >= '0' && c <= '9') {
					part = c - '0';
					c = *++cp;
				}
			}
		}
		if (c != ')')
			return (ENXIO);
		cp++;
	}
	*ncp = '\0';

	for (dp = devsw, i = 0; i < ndevs; dp++, i++)
		if (dp->dv_name && strcmp(namebuf, dp->dv_name) == 0)
			goto fnd;
	printf("Unknown device '%s'\nKnown devices are:", namebuf);
	for (dp = devsw, i = 0; i < ndevs; dp++, i++)
		if (dp->dv_name)
			printf(" %s", dp->dv_name);
	printf("\n");
	return (ENXIO);

fnd:
	rc = (dp->dv_open)(f, ctlr, unit, part);
	if (rc)
		return (rc);

	f->f_dev = dp;
	if (file && *cp != '\0')
		*file = cp;
	return (0);
}
E 1
