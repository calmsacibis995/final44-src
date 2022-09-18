h08925
s 00002/00002/00056
d D 8.1 93/06/06 16:04:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00057
d D 5.3 91/03/12 09:20:03 bostic 3 2
c comply with ar source changes nothing else
e
s 00003/00002/00055
d D 5.2 91/02/26 14:53:15 bostic 2 1
c ANSI fixes (one real bug!)
e
s 00057/00000/00000
d D 5.1 91/01/18 18:45:40 bostic 1 0
c date and time created 91/01/18 18:45:40 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <fcntl.h>
D 2
#include <unistd.h>
E 2
#include <dirent.h>
#include <ranlib.h>
#include <ar.h>
I 2
#include <time.h>
#include <unistd.h>
E 2
#include <stdio.h>
I 2
#include <string.h>
E 2
#include <archive.h>
D 2
#include <time.h>
E 2

extern CHDR chdr;			/* converted header */
extern char *archive;			/* archive name */

touch()
{
	int afd;

	afd = open_archive(O_RDWR);

D 3
	if (!get_header(afd) ||
E 3
I 3
	if (!get_arobj(afd) ||
E 3
	    strncmp(RANLIBMAG, chdr.name, sizeof(RANLIBMAG) - 1)) {
		(void)fprintf(stderr,
		    "ranlib: %s: no symbol table.\n", archive);
		return(1);
	}
	settime(afd);
	return(0);
}

settime(afd)
	int afd;
{
	struct ar_hdr *hdr;
	off_t size;
	char buf[50];

	size = SARMAG + sizeof(hdr->ar_name);
	if (lseek(afd, size, SEEK_SET) == (off_t)-1)
		error(archive);
	(void)sprintf(buf, "%-12ld", time((time_t *)NULL) + RANLIBSKEW);
	if (write(afd, buf, sizeof(hdr->ar_date)) != sizeof(hdr->ar_date))
		error(archive);
}
E 1
