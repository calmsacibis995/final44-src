h08204
s 00002/00002/00312
d D 8.1 93/06/09 21:42:09 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00307
d D 7.6 91/04/17 17:38:04 bostic 15 14
c new copyright; att/bsd/shared
e
s 00008/00008/00305
d D 7.5 88/07/22 17:08:53 bostic 14 13
c ANSIfication
e
s 00002/00002/00311
d D 7.4 87/03/09 12:46:40 conrad 13 12
c make ex/vi work on vms
e
s 00001/00001/00312
d D 7.3 85/06/07 18:18:20 bloom 12 11
c fix sccsid and copyright for xstr
e
s 00010/00002/00303
d D 7.2 85/05/31 13:50:56 dist 11 9
c Add copyright
e
s 00010/00002/00303
d D 5.1.1.1 85/05/31 11:56:54 dist 10 7
c Add copyright
e
s 00002/00002/00303
d D 7.1 81/07/08 22:28:15 mark 9 8
c release 3.7 - a few bug fixes and a few new features.
e
s 00000/00000/00305
d D 6.1 80/10/19 01:20:10 mark 8 7
c preliminary release 3.6 10/18/80
e
s 00000/00000/00305
d D 5.1 80/08/20 16:07:58 mark 7 6
c Release 3.5, August 20, 1980
e
s 00106/00001/00199
d D 4.3 80/08/01 21:40:51 mark 6 5
c fixed botch from killing sccs process (what a pain!)
e
s 00002/00106/00198
d D 4.2 80/08/01 17:58:57 mark 5 4
c added sccs, Bill put in more buffers
e
s 00006/00001/00298
d D 4.1 80/08/01 00:09:52 mark 4 3
c release 3.4, June 24, 1980
e
s 00000/00000/00299
d D 3.1 80/07/31 23:36:11 mark 3 2
c release 3.3, Feb 2, 1980
e
s 00000/00000/00299
d D 2.1 80/07/31 23:17:37 mark 2 1
c release 3.2, Jan 4, 1980
e
s 00299/00000/00000
d D 1.1 80/07/31 23:00:03 mark 1 0
c date and time created 80/07/31 23:00:03 by mark
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1979 Regents of the University of California */
E 5
I 5
D 6
/* Copyright (c) 1980 Regents of the University of California */
E 6
I 6
D 9
D 10
/* Copyright (c) 1979 Regents of the University of California */
E 6
static char *sccsid = "%W% %G%";
E 10
I 10
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

E 10
E 9
I 9
D 11
/* Copyright (c) 1981 Regents of the University of California */
static char *sccsid = "%W%	%G%";
E 11
I 11
D 15
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
/*-
D 16
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * %sccs.include.proprietary.c%
E 15
 */

#ifndef lint
D 12
static char sccsid[] = "%W% (Berkeley) %G%";
E 12
I 12
D 15
static char *sccsid = "%W% (Berkeley) %G%";
E 12
#endif not lint
E 15
I 15
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 15

E 11
E 9
E 5
#include "ex.h"
#include "ex_re.h"

/*
 * Routines for address parsing and assignment and checking of address bounds
 * in command mode.  The routine address is called from ex_cmds.c
 * to parse each component of a command (terminated by , ; or the beginning
 * of the command itself.  It is also called by the scanning routine
 * in ex_voperate.c from within open/visual.
 *
 * Other routines here manipulate the externals addr1 and addr2.
 * These are the first and last lines for the current command.
 *
 * The variable bigmove remembers whether a non-local glitch of . was
 * involved in an address expression, so we can set the previous context
 * mark '' when such a motion occurs.
 */

static	bool bigmove;

/*
 * Set up addr1 and addr2 for commands whose default address is dot.
 */
setdot()
{

	setdot1();
	if (bigmove)
		markDOT();
}

/*
 * Call setdot1 to set up default addresses without ever
 * setting the previous context mark.
 */
setdot1()
{

	if (addr2 == 0)
		addr1 = addr2 = dot;
	if (addr1 > addr2) {
		notempty();
		error("Addr1 > addr2|First address exceeds second");
	}
}

/*
 * Ex allows you to say
 *	delete 5
 * to delete 5 lines, etc.
 * Such nonsense is implemented by setcount.
 */
setcount()
{
	register int cnt;

	pastwh();
	if (!isdigit(peekchar())) {
		setdot();
		return;
	}
	addr1 = addr2;
	setdot();
	cnt = getnum();
	if (cnt <= 0)
		error("Bad count|Nonzero count required");
	addr2 += cnt - 1;
	if (addr2 > dol)
		addr2 = dol;
	nonzero();
}

/*
 * Parse a number out of the command input stream.
 */
getnum()
{
	register int cnt;

	for (cnt = 0; isdigit(peekcd());)
D 13
		cnt = cnt * 10 + getchar() - '0';
E 13
I 13
		cnt = cnt * 10 + ex_getchar() - '0';
E 13
	return (cnt);
}

/*
 * Set the default addresses for commands which use the whole
 * buffer as default, notably write.
 */
setall()
{

	if (addr2 == 0) {
		addr1 = one;
		addr2 = dol;
		if (dol == zero) {
			dot = zero;
			return;
		}
	}
	/*
	 * Don't want to set previous context mark so use setdot1().
	 */
	setdot1();
}

/*
 * No address allowed on, e.g. the file command.
 */
setnoaddr()
{

	if (addr2 != 0)
		error("No address allowed@on this command");
}

/*
 * Parse an address.
 * Just about any sequence of address characters is legal.
 *
 * If you are tricky you can use this routine and the = command
 * to do simple addition and subtraction of cardinals less
 * than the number of lines in the file.
 */
line *
D 14
address(inline)
	char *inline;
E 14
I 14
address(inputline)
	char *inputline;
E 14
{
	register line *addr;
	register int offset, c;
	short lastsign;

	bigmove = 0;
	lastsign = 0;
	offset = 0;
	addr = 0;
	for (;;) {
		if (isdigit(peekcd())) {
			if (addr == 0) {
				addr = zero;
				bigmove = 1;
			}
			loc1 = 0;
			addr += offset;
			offset = getnum();
			if (lastsign >= 0)
				addr += offset;
			else
				addr -= offset;
			lastsign = 0;
			offset = 0;
		}
		switch (c = getcd()) {

		case '?':
		case '/':
		case '$':
		case '\'':
		case '\\':
			bigmove++;
		case '.':
			if (addr || offset)
				error("Badly formed address");
		}
		offset += lastsign;
		lastsign = 0;
		switch (c) {

		case ' ':
		case '\t':
			continue;

		case '+':
			lastsign = 1;
			if (addr == 0)
				addr = dot;
			continue;

		case '^':
		case '-':
			lastsign = -1;
			if (addr == 0)
				addr = dot;
			continue;

		case '\\':
		case '?':
		case '/':
			c = compile(c, 1);
			notempty();
			savere(scanre);
			addr = dot;
D 14
			if (inline && execute(0, dot)) {
E 14
I 14
			if (inputline && execute(0, dot)) {
E 14
				if (c == '/') {
D 4
					while (loc1 <= inline)
E 4
I 4
D 14
					while (loc1 <= inline) {
E 14
I 14
					while (loc1 <= inputline) {
E 14
						if (loc1 == loc2)
							loc2++;
E 4
						if (!execute(1))
							goto nope;
I 6
					}
					break;
D 14
				} else if (loc1 < inline) {
E 14
I 14
				} else if (loc1 < inputline) {
E 14
					char *last;
doques:

					do {
						last = loc1;
						if (loc1 == loc2)
							loc2++;
						if (!execute(1))
							break;
D 14
					} while (loc1 < inline);
E 14
I 14
					} while (loc1 < inputline);
E 14
					loc1 = last;
					break;
				}
			}
nope:
			for (;;) {
				if (c == '/') {
					addr++;
					if (addr > dol) {
						if (value(WRAPSCAN) == 0)
error("No match to BOTTOM|Address search hit BOTTOM without matching pattern");
						addr = zero;
					}
				} else {
					addr--;
					if (addr < zero) {
						if (value(WRAPSCAN) == 0)
error("No match to TOP|Address search hit TOP without matching pattern");
						addr = dol;
					}
				}
				if (execute(0, addr)) {
D 14
					if (inline && c == '?') {
						inline = &linebuf[LBSIZE];
E 14
I 14
					if (inputline && c == '?') {
						inputline = &linebuf[LBSIZE];
E 14
						goto doques;
					}
					break;
				}
				if (addr == dot)
					error("Fail|Pattern not found");
			}
			continue;

		case '$':
			addr = dol;
			continue;

		case '.':
			addr = dot;
			continue;

		case '\'':
D 13
			c = markreg(getchar());
E 13
I 13
			c = markreg(ex_getchar());
E 13
			if (c == 0)
				error("Marks are ' and a-z");
			addr = getmark(c);
			if (addr == 0)
				error("Undefined mark@referenced");
			break;

		default:
			ungetchar(c);
			if (offset) {
				if (addr == 0)
					addr = dot;
				addr += offset;
				loc1 = 0;
			}
			if (addr == 0) {
				bigmove = 0;
				return (0);
			}
			if (addr != zero)
				notempty();
			addr += lastsign;
			if (addr < zero)
				error("Negative address@- first buffer line is 1");
			if (addr > dol)
				error("Not that many lines@in buffer");
			return (addr);
		}
	}
}

/*
 * Abbreviations to make code smaller
 * Left over from squashing ex version 1.1 into
 * 11/34's and 11/40's.
 */
setCNL()
{

	setcount();
	newline();
}

setNAEOL()
{

	setnoaddr();
	eol();
}
E 6
I 4
D 5
					}
E 4
					break;
				} else if (loc1 < inline) {
					char *last;
doques:

					do {
						last = loc1;
I 4
						if (loc1 == loc2)
							loc2++;
E 4
						if (!execute(1))
							break;
					} while (loc1 < inline);
					loc1 = last;
					break;
				}
			}
nope:
			for (;;) {
				if (c == '/') {
					addr++;
					if (addr > dol) {
						if (value(WRAPSCAN) == 0)
error("No match to BOTTOM|Address search hit BOTTOM without matching pattern");
						addr = zero;
					}
				} else {
					addr--;
					if (addr < zero) {
						if (value(WRAPSCAN) == 0)
error("No match to TOP|Address search hit TOP without matching pattern");
						addr = dol;
					}
				}
				if (execute(0, addr)) {
					if (inline && c == '?') {
						inline = &linebuf[LBSIZE];
						goto doques;
					}
					break;
				}
				if (addr == dot)
					error("Fail|Pattern not found");
			}
			continue;

		case '$':
			addr = dol;
			continue;

		case '.':
			addr = dot;
			continue;

		case '\'':
			c = markreg(getchar());
			if (c == 0)
				error("Marks are ' and a-z");
			addr = getmark(c);
			if (addr == 0)
				error("Undefined mark@referenced");
			break;

		default:
			ungetchar(c);
			if (offset) {
				if (addr == 0)
					addr = dot;
				addr += offset;
				loc1 = 0;
			}
			if (addr == 0) {
				bigmove = 0;
				return (0);
			}
			if (addr != zero)
				notempty();
			addr += lastsign;
			if (addr < zero)
				error("Negative address@- first buffer line is 1");
			if (addr > dol)
				error("Not that many lines@in buffer");
			return (addr);
		}
	}
}

/*
 * Abbreviations to make code smaller
 * Left over from squashing ex version 1.1 into
 * 11/34's and 11/40's.
 */
setCNL()
{

	setcount();
	newline();
}

setNAEOL()
{

	setnoaddr();
	eol();
}
E 5
E 1
