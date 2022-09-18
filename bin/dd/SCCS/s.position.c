h22461
s 00001/00001/00139
d D 8.3 94/04/02 09:55:37 pendry 6 5
c add 1994 copyright
e
s 00016/00013/00124
d D 8.2 94/04/02 07:39:21 pendry 5 4
c prettyness police
e
s 00002/00002/00135
d D 8.1 93/05/31 14:22:36 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00134
d D 5.3 91/08/05 09:44:10 bostic 3 2
c positive returns from read() dropped to err()
e
s 00002/00001/00134
d D 5.2 91/07/27 10:55:20 bostic 2 1
c add Lance Visser to contrib list
e
s 00135/00000/00000
d D 5.1 91/07/26 15:42:59 bostic 1 0
c date and time created 91/07/26 15:42:59 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
D 6
 * Copyright (c) 1991, 1993
E 6
I 6
 * Copyright (c) 1991, 1993, 1994
E 6
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
D 2
 * Keith Muller of the University of California, San Diego.
E 2
I 2
 * Keith Muller of the University of California, San Diego and Lance
 * Visser of Convex Computer Corporation.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mtio.h>
I 5

#include <err.h>
E 5
#include <errno.h>
D 5
#include <unistd.h>
E 5
#include <string.h>
I 5
#include <unistd.h>

E 5
#include "dd.h"
#include "extern.h"

/*
 * Position input/output data streams before starting the copy.  Device type
 * dependent.  Seekable devices use lseek, and the rest position by reading.
 * Seeking past the end of file can cause null blocks to be written to the
 * output.
 */
void
pos_in()
{
D 5
	register int bcnt, cnt, nr, warned;
E 5
I 5
	int bcnt, cnt, nr, warned;
E 5

	/* If not a character, pipe or tape device, try to seek on it. */
	if (!(in.flags & (ISCHR|ISPIPE|ISTAPE))) {
		if (lseek(in.fd, (off_t)(in.offset * in.dbsz), SEEK_CUR) == -1)
D 5
			err("%s: %s", in.name, strerror(errno));
E 5
I 5
			err(1, "%s", in.name);
E 5
		return;
	}

	/*
	 * Read the data.  If a pipe, read until satisfy the number of bytes
	 * being skipped.  No differentiation for reading complete and partial
	 * blocks for other devices.
	 */
	for (bcnt = in.dbsz, cnt = in.offset, warned = 0; cnt;) {
D 3
		if ((nr = read(in.fd, in.db, bcnt)) > 0)
E 3
I 3
		if ((nr = read(in.fd, in.db, bcnt)) > 0) {
E 3
			if (in.flags & ISPIPE) {
				if (!(bcnt -= nr)) {
					bcnt = in.dbsz;
					--cnt;
				}
D 3
				continue;
E 3
			} else
				--cnt;
I 3
			continue;
		}
E 3

		if (nr == 0) {
			if (files_cnt > 1) {
				--files_cnt;
				continue;
			}
D 5
			err("skip reached end of input");
E 5
I 5
			errx(1, "skip reached end of input");
E 5
		}

		/*
		 * Input error -- either EOF with no more files, or I/O error.
		 * If noerror not set die.  POSIX requires that the warning
		 * message be followed by an I/O display.
		 */
		if (ddflags & C_NOERROR) {
			if (!warned) {
D 5
				warn("%s: %s", in.name, strerror(errno));
E 5
I 5
				warn("%s", in.name);
E 5
				warned = 1;
D 5
				summary(0);
E 5
I 5
				summary();
E 5
			}
			continue;
		}
D 5
		err("%s: %s", in.name, strerror(errno));
E 5
I 5
		err(1, "%s", in.name);
E 5
	}
}

void
pos_out()
{
D 5
	register int cnt, n;
E 5
	struct mtop t_op;
I 5
	int cnt, n;
E 5

	/*
	 * If not a tape, try seeking on the file.  Seeking on a pipe is
	 * going to fail, but don't protect the user -- they shouldn't
	 * have specified the seek operand.
	 */
	if (!(out.flags & ISTAPE)) {
		if (lseek(out.fd,
		    (off_t)out.offset * out.dbsz, SEEK_SET) == -1)
D 5
			err("%s: %s", out.name, strerror(errno));
E 5
I 5
			err(1, "%s", out.name);
E 5
		return;
	}

	/* If no read access, try using mtio. */
	if (out.flags & NOREAD) {
		t_op.mt_op = MTFSR;
		t_op.mt_count = out.offset;

		if (ioctl(out.fd, MTIOCTOP, &t_op) < 0)
D 5
			err("%s: %s", out.name, strerror(errno));
E 5
I 5
			err(1, "%s", out.name);
E 5
		return;
	}

	/* Read it. */
	for (cnt = 0; cnt < out.offset; ++cnt) {
		if ((n = read(out.fd, out.db, out.dbsz)) > 0)
			continue;

		if (n < 0)
D 5
			err("%s: %s", out.name, strerror(errno));
E 5
I 5
			err(1, "%s", out.name);
E 5

		/*
		 * If reach EOF, fill with NUL characters; first, back up over
		 * the EOF mark.  Note, cnt has not yet been incremented, so
		 * the EOF read does not count as a seek'd block.
		 */
		t_op.mt_op = MTBSR;
		t_op.mt_count = 1;
		if (ioctl(out.fd, MTIOCTOP, &t_op) == -1)
D 5
			err("%s: %s", out.name, strerror(errno));
E 5
I 5
			err(1, "%s", out.name);
E 5

		while (cnt++ < out.offset)
			if ((n = write(out.fd, out.db, out.dbsz)) != out.dbsz)
D 5
				err("%s: %s", out.name, strerror(errno));
E 5
I 5
				err(1, "%s", out.name);
E 5
		break;
	}
}
E 1
