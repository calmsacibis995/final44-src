h33597
s 00001/00001/00073
d D 8.3 94/04/02 09:55:33 pendry 10 9
c add 1994 copyright
e
s 00010/00054/00064
d D 8.2 94/04/02 07:39:20 pendry 9 8
c prettyness police
e
s 00002/00002/00116
d D 8.1 93/05/31 14:22:30 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00003/00112
d D 5.7 93/04/28 17:08:48 bostic 7 6
c report bytes/sec last
e
s 00005/00002/00110
d D 5.6 93/04/28 16:36:47 bostic 6 5
c lint
e
s 00006/00007/00106
d D 5.5 92/10/17 15:12:05 bostic 5 4
c snprintf returns printed length, not actual length
e
s 00010/00002/00103
d D 5.4 92/06/02 16:31:47 marc 4 3
c add byte count to stats
e
s 00008/00003/00097
d D 5.3 91/07/29 13:30:48 bostic 3 2
c fix block/unblock, ascii/ebcdic, cbs relationships (extensive)
c check for read/write/seek overflow; move stats into separate structure
c treat odd-length swab errors like truncate errors
e
s 00002/00001/00098
d D 5.2 91/07/27 10:55:19 bostic 2 1
c add Lance Visser to contrib list
e
s 00099/00000/00000
d D 5.1 91/07/26 15:42:52 bostic 1 0
c date and time created 91/07/26 15:42:52 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
D 10
 * Copyright (c) 1991, 1993
E 10
I 10
 * Copyright (c) 1991, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 8
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
D 6
#include <unistd.h>
#include <stdlib.h>
E 6
I 6

I 9
#include <err.h>
E 9
E 6
#include <stdio.h>
I 6
#include <stdlib.h>
#include <string.h>
I 9
#include <time.h>
E 9
#include <unistd.h>

E 6
#include "dd.h"
#include "extern.h"

D 9
/* ARGSUSED */
E 9
void
D 9
summary(notused)
	int notused;
E 9
I 9
summary()
E 9
{
I 4
	time_t secs;
E 4
D 5
	int len;
E 5
	char buf[100];

I 4
	(void)time(&secs);
	if ((secs -= st.start) == 0)
		secs = 1;
E 4
	/* Use snprintf(3) so that we don't reenter stdio(3). */
D 5
	len = snprintf(buf, sizeof(buf),
E 5
I 5
	(void)snprintf(buf, sizeof(buf),
E 5
D 4
	    "%u+%u records in\n%u+%u records out\n",
D 3
	    in.f_stats, in.p_stats, out.f_stats, out.p_stats);
E 3
I 3
	    st.in_full, st.in_part, st.out_full, st.out_part);
E 4
I 4
D 7
	    "%u+%u records in\n%u+%u records out\n%u bytes transferred in %u secs (%u bytes/sec)\n",
	    st.in_full, st.in_part, st.out_full, st.out_part, st.bytes,
	    secs, st.bytes / secs);
E 7
I 7
	    "%u+%u records in\n%u+%u records out\n",
	    st.in_full, st.in_part, st.out_full, st.out_part);
E 7
E 4
E 3
D 5
	(void)write(STDERR_FILENO, buf, len);
E 5
I 5
	(void)write(STDERR_FILENO, buf, strlen(buf));
E 5
D 3
	if (in.t_stats) {
E 3
I 3
	if (st.swab) {
D 5
		len = snprintf(buf, sizeof(buf), "%u odd length swab %s\n",
E 5
I 5
		(void)snprintf(buf, sizeof(buf), "%u odd length swab %s\n",
E 5
		     st.swab, (st.swab == 1) ? "block" : "blocks");
D 5
		(void)write(STDERR_FILENO, buf, len);
E 5
I 5
		(void)write(STDERR_FILENO, buf, strlen(buf));
E 5
	}
	if (st.trunc) {
E 3
D 5
		len = snprintf(buf, sizeof(buf), "%u truncated %s\n",
E 5
I 5
		(void)snprintf(buf, sizeof(buf), "%u truncated %s\n",
E 5
D 3
		     in.t_stats, (in.t_stats == 1) ? "block" : "blocks");
E 3
I 3
		     st.trunc, (st.trunc == 1) ? "block" : "blocks");
E 3
D 5
		(void)write(STDERR_FILENO, buf, len);
E 5
I 5
		(void)write(STDERR_FILENO, buf, strlen(buf));
E 5
	}
I 7
	(void)snprintf(buf, sizeof(buf),
	    "%u bytes transferred in %u secs (%u bytes/sec)\n",
	    st.bytes, secs, st.bytes / secs);
	(void)write(STDERR_FILENO, buf, strlen(buf));
E 7
}

/* ARGSUSED */
void
D 9
terminate(notused)
E 9
I 9
summaryx(notused)
E 9
	int notused;
{
D 9
	summary(0);
	exit(0);
}
E 9

D 9
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
I 4
	extern int errstats;
E 4
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "dd: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
I 4
	if (errstats)
		summary(0);
E 4
	exit(1);
	/* NOTREACHED */
E 9
I 9
	summary();
E 9
}

I 9
/* ARGSUSED */
E 9
void
D 9
#if __STDC__
warn(const char *fmt, ...)
#else
warn(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 9
I 9
terminate(notused)
	int notused;
E 9
{
D 9
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "dd: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 9
I 9

	exit(0);
E 9
}
E 1
