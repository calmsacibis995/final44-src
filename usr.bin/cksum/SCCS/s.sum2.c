h21395
s 00002/00002/00043
d D 8.1 93/06/06 14:27:35 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00044
d D 5.2 91/11/27 12:41:25 bostic 2 1
c lint
e
s 00044/00000/00000
d D 5.1 91/04/04 12:24:26 bostic 1 0
c date and time created 91/04/04 12:24:26 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <unistd.h>

I 2
int
E 2
csum2(fd, cval, clen)
	register int fd;
	u_long *cval, *clen;
{
	register u_long crc, total;
	register int nr;
	register u_char *p;
	u_char buf[8192];

	/*
	 * Draft 8 POSIX 1003.2:
	 *
	 *   s = sum of all bytes
	 *   r = s % 2^16 + (s % 2^32) / 2^16
	 * crc = (r % 2^16) + r / 2^16
	 */
	crc = total = 0;
	while ((nr = read(fd, buf, sizeof(buf))) > 0)
		for (total += nr, p = buf; nr--; ++p)
			crc += *p;
	if (nr < 0)
		return(1);

	crc = (crc & 0xffff) + (crc >> 16);
	crc = (crc & 0xffff) + (crc >> 16);

	*cval = crc;
	*clen = total;
	return(0);
}
E 1
