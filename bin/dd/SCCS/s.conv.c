h62235
s 00001/00001/00233
d D 8.3 94/04/02 09:55:09 pendry 9 8
c add 1994 copyright
e
s 00010/00010/00224
d D 8.2 94/04/02 07:39:19 pendry 8 7
c prettyness police
e
s 00002/00002/00232
d D 8.1 93/05/31 14:22:13 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00226
d D 5.6 93/04/28 17:06:18 bostic 6 5
c don't increment truncation count if the next character would have ended
c the block
c test case is 'dd if=bigfile of=/dev/null ibs=4567 obs=4321 cbs=73 conv=block'
c from Griff Smith
e
s 00007/00005/00221
d D 5.5 93/04/28 16:36:38 bostic 5 4
c bcopy -> memmove
e
s 00001/00009/00225
d D 5.4 91/08/14 13:55:55 bostic 4 3
c fix worst-case buffer sizes for non-blocking I/O
e
s 00002/00002/00232
d D 5.3 91/07/29 13:30:44 bostic 3 2
c fix block/unblock, ascii/ebcdic, cbs relationships (extensive)
c check for read/write/seek overflow; move stats into separate structure
c treat odd-length swab errors like truncate errors
e
s 00002/00001/00232
d D 5.2 91/07/27 10:55:15 bostic 2 1
c add Lance Visser to contrib list
e
s 00233/00000/00000
d D 5.1 91/07/26 15:42:17 bostic 1 0
c date and time created 91/07/26 15:42:17 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1991, 1993
E 9
I 9
 * Copyright (c) 1991, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
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

#include <sys/param.h>
I 5

I 8
#include <err.h>
E 8
E 5
#include <string.h>
I 5

E 5
#include "dd.h"
#include "extern.h"

/*
 * def --
 * Copy input to output.  Input is buffered until reaches obs, and then
 * output until less than obs remains.  Only a single buffer is used.
D 4
 * Worst case buffer calculations are as follows:
 *
 * if (ibs > obs)			# read ibs, output just over half
 *	max = ibs - 1 - ibs / 2 + ibs;
 * else if (ibs < obs)			# obs - 1 a multiple of ibs
 *	max = obs + ibs - 1;
 * else					# input == output
 *	max = ibs;
E 4
I 4
 * Worst case buffer calculation is (ibs + obs - 1).
E 4
 */
void
def()
{
D 8
	register int cnt;
	register u_char *inp, *t;
E 8
I 8
	int cnt;
	u_char *inp, *t;
E 8

	if (t = ctab)
		for (inp = in.dbp - (cnt = in.dbrcnt); cnt--; ++inp)
			*inp = t[*inp];

	/* Make the output buffer look right. */
	out.dbp = in.dbp;
	out.dbcnt = in.dbcnt;

	if (in.dbcnt >= out.dbsz) {
		/* If the output buffer is full, write it. */
		dd_out(0);

		/*
		 * Ddout copies the leftover output to the beginning of
		 * the buffer and resets the output buffer.  Reset the
		 * input buffer to match it.
	 	 */
		in.dbp = out.dbp;
		in.dbcnt = out.dbcnt;
	}
}

void
def_close()
{
	/* Just update the count, everything is already in the buffer. */
	if (in.dbcnt)
		out.dbcnt = in.dbcnt;
}

/*
 * Copy variable length newline terminated records with a max size cbsz
 * bytes to output.  Records less than cbs are padded with spaces.
 *
 * max in buffer:  MAX(ibs, cbsz)
 * max out buffer: obs + cbsz
 */
D 4

E 4
void
block()
{
	static int intrunc;
D 8
	register int ch, cnt;
	register u_char *inp, *outp, *t;
	int maxlen;
E 8
I 8
	int ch, cnt, maxlen;
	u_char *inp, *outp, *t;
E 8

	/*
	 * Record truncation can cross block boundaries.  If currently in a
	 * truncation state, keep tossing characters until reach a newline.
	 * Start at the beginning of the buffer, as the input buffer is always
	 * left empty.
	 */
	if (intrunc) {
		for (inp = in.db, cnt = in.dbrcnt;
		    cnt && *inp++ != '\n'; --cnt);
		if (!cnt) {
			in.dbcnt = 0;
			in.dbp = in.db;
			return;
		}
		intrunc = 0;
		/* Adjust the input buffer numbers. */
		in.dbcnt = cnt - 1;
		in.dbp = inp + cnt - 1;
	}

	/*
	 * Copy records (max cbsz size chunks) into the output buffer.  The
	 * translation is done as we copy into the output buffer.
	 */
	for (inp = in.dbp - in.dbcnt, outp = out.dbp; in.dbcnt;) {
		maxlen = MIN(cbsz, in.dbcnt);
		if (t = ctab)
			for (cnt = 0;
			    cnt < maxlen && (ch = *inp++) != '\n'; ++cnt)
				*outp++ = t[ch];
		else
			for (cnt = 0;
			    cnt < maxlen && (ch = *inp++) != '\n'; ++cnt)
				*outp++ = ch;
		/*
		 * Check for short record without a newline.  Reassemble the
		 * input block.
		 */
		if (ch != '\n' && in.dbcnt < cbsz) {
D 5
			bcopy(in.dbp - in.dbcnt, in.db, in.dbcnt);
E 5
I 5
			memmove(in.db, in.dbp - in.dbcnt, in.dbcnt);
E 5
			break;
		}

		/* Adjust the input buffer numbers. */
		in.dbcnt -= cnt;
		if (ch == '\n')
			--in.dbcnt;

D 6
		/* Pad short records with "spaces". */
E 6
I 6
		/* Pad short records with spaces. */
E 6
		if (cnt < cbsz)
			(void)memset(outp, ctab ? ctab[' '] : ' ', cbsz - cnt);
		else {
D 3
			++in.t_stats;
E 3
I 3
D 6
			++st.trunc;
E 6
I 6
			/*
			 * If the next character wouldn't have ended the
			 * block, it's a truncation.
			 */
			if (!in.dbcnt || *inp != '\n')
				++st.trunc;

E 6
E 3
			/* Toss characters to a newline. */
			for (; in.dbcnt && *inp++ != '\n'; --in.dbcnt);
			if (!in.dbcnt)
				intrunc = 1;
			else
				--in.dbcnt;
		}

		/* Adjust output buffer numbers. */
		out.dbp += cbsz;
		if ((out.dbcnt += cbsz) >= out.dbsz)
			dd_out(0);
		outp = out.dbp;
	}
	in.dbp = in.db + in.dbcnt;
}

void
block_close()
{
	/*
	 * Copy any remaining data into the output buffer and pad to a record.
	 * Don't worry about truncation or translation, the input buffer is
	 * always empty when truncating, and no characters have been added for
	 * translation.  The bottom line is that anything left in the input
	 * buffer is a truncated record.  Anything left in the output buffer
	 * just wasn't big enough.
	 */
	if (in.dbcnt) {
D 3
		++in.t_stats;
E 3
I 3
		++st.trunc;
E 3
D 5
		bcopy(in.dbp - in.dbcnt, out.dbp, in.dbcnt);
E 5
I 5
		memmove(out.dbp, in.dbp - in.dbcnt, in.dbcnt);
E 5
		(void)memset(out.dbp + in.dbcnt,
		    ctab ? ctab[' '] : ' ', cbsz - in.dbcnt);
		out.dbcnt += cbsz;
	}
}

/*
 * Convert fixed length (cbsz) records to variable length.  Deletes any
 * trailing blanks and appends a newline.
 *
 * max in buffer:  MAX(ibs, cbsz) + cbsz
 * max out buffer: obs + cbsz
 */
void
unblock()
{
D 8
	register int cnt;
	register u_char *inp, *t;
E 8
I 8
	int cnt;
	u_char *inp, *t;
E 8

	/* Translation and case conversion. */
	if (t = ctab)
		for (cnt = in.dbrcnt, inp = in.dbp; cnt--;)
			*--inp = t[*inp];
	/*
	 * Copy records (max cbsz size chunks) into the output buffer.  The
	 * translation has to already be done or we might not recognize the
	 * spaces.
	 */
	for (inp = in.db; in.dbcnt >= cbsz; inp += cbsz, in.dbcnt -= cbsz) {
		for (t = inp + cbsz - 1; t >= inp && *t == ' '; --t);
		if (t >= inp) {
			cnt = t - inp + 1;
D 5
			bcopy(inp, out.dbp, cnt);
E 5
I 5
			memmove(out.dbp, inp, cnt);
E 5
			out.dbp += cnt;
			out.dbcnt += cnt;
		}
		++out.dbcnt;
		*out.dbp++ = '\n';
		if (out.dbcnt >= out.dbsz)
			dd_out(0);
	}
	if (in.dbcnt)
D 5
		bcopy(in.dbp - in.dbcnt, in.db, in.dbcnt);
E 5
I 5
		memmove(in.db, in.dbp - in.dbcnt, in.dbcnt);
E 5
	in.dbp = in.db + in.dbcnt;
}

void
unblock_close()
{
D 8
	register int cnt;
	register u_char *t;
E 8
I 8
	int cnt;
	u_char *t;
E 8

	if (in.dbcnt) {
D 8
		warn("%s: short input record", in.name);
E 8
I 8
		warnx("%s: short input record", in.name);
E 8
		for (t = in.db + in.dbcnt - 1; t >= in.db && *t == ' '; --t);
		if (t >= in.db) {
			cnt = t - in.db + 1;
D 5
			bcopy(in.db, out.dbp, cnt);
E 5
I 5
			memmove(out.dbp, in.db, cnt);
E 5
			out.dbp += cnt;
			out.dbcnt += cnt;
		}
		++out.dbcnt;
		*out.dbp++ = '\n';
	}
}
E 1
