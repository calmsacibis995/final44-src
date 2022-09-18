h29621
s 00002/00002/00213
d D 8.1 93/06/06 15:36:20 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00214
d D 5.4 90/06/01 17:03:53 bostic 4 3
c new copyright notice
e
s 00011/00008/00215
d D 5.3 88/11/22 16:51:23 bostic 3 2
c less -> more
e
s 00002/00004/00221
d D 5.2 88/07/25 12:04:40 bostic 2 1
c update copyright notice
e
s 00225/00000/00000
d D 5.1 88/07/21 18:52:43 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 5
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 2
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 2
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 2
 * by the University of California, Berkeley.  The name of the
E 2
I 2
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 2
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * High level routines dealing with getting lines of input 
 * from the file being viewed.
 *
 * When we speak of "lines" here, we mean PRINTABLE lines;
 * lines processed with respect to the screen width.
 * We use the term "raw line" to refer to lines simply
 * delimited by newlines; not processed with respect to screen width.
 */

D 3
#include "less.h"
E 3
I 3
#include <sys/types.h>
#include <less.h>
E 3

extern int squeeze;
extern int sigs;
extern char *line;

I 3
off_t ch_tell();

E 3
/*
 * Get the next line.
 * A "current" position is passed and a "new" position is returned.
 * The current position is the position of the first character of
 * a line.  The new position is the position of the first character
 * of the NEXT line.  The line obtained is the line starting at curr_pos.
 */
D 3
	public POSITION
E 3
I 3
off_t
E 3
forw_line(curr_pos)
D 3
	POSITION curr_pos;
E 3
I 3
	off_t curr_pos;
E 3
{
D 3
	POSITION new_pos;
E 3
I 3
	off_t new_pos;
E 3
	register int c;

	if (curr_pos == NULL_POSITION || ch_seek(curr_pos))
		return (NULL_POSITION);

	c = ch_forw_get();
	if (c == EOI)
		return (NULL_POSITION);

	prewind();
	for (;;)
	{
		if (sigs)
			return (NULL_POSITION);
		if (c == '\n' || c == EOI)
		{
			/*
			 * End of the line.
			 */
			new_pos = ch_tell();
			break;
		}

		/*
		 * Append the char to the line and get the next char.
		 */
		if (pappend(c))
		{
			/*
			 * The char won't fit in the line; the line
			 * is too long to print in the screen width.
			 * End the line here.
			 */
			new_pos = ch_tell() - 1;
			break;
		}
		c = ch_forw_get();
	}
	(void) pappend('\0');

	if (squeeze && *line == '\0')
	{
		/*
		 * This line is blank.
		 * Skip down to the last contiguous blank line
		 * and pretend it is the one which we are returning.
		 */
		while ((c = ch_forw_get()) == '\n')
			if (sigs)
				return (NULL_POSITION);
		if (c != EOI)
			(void) ch_back_get();
		new_pos = ch_tell();
	}

	return (new_pos);
}

/*
 * Get the previous line.
 * A "current" position is passed and a "new" position is returned.
 * The current position is the position of the first character of
 * a line.  The new position is the position of the first character
 * of the PREVIOUS line.  The line obtained is the one starting at new_pos.
 */
D 3
	public POSITION
E 3
I 3
off_t
E 3
back_line(curr_pos)
D 3
	POSITION curr_pos;
E 3
I 3
	off_t curr_pos;
E 3
{
D 3
	POSITION new_pos, begin_new_pos;
E 3
I 3
	off_t new_pos, begin_new_pos;
E 3
	int c;

D 3
	if (curr_pos == NULL_POSITION || curr_pos <= (POSITION)0 ||
E 3
I 3
	if (curr_pos == NULL_POSITION || curr_pos <= (off_t)0 ||
E 3
		ch_seek(curr_pos-1))
		return (NULL_POSITION);

	if (squeeze)
	{
		/*
		 * Find out if the "current" line was blank.
		 */
		(void) ch_forw_get();	/* Skip the newline */
		c = ch_forw_get();	/* First char of "current" line */
		(void) ch_back_get();	/* Restore our position */
		(void) ch_back_get();

		if (c == '\n')
		{
			/*
			 * The "current" line was blank.
			 * Skip over any preceeding blank lines,
			 * since we skipped them in forw_line().
			 */
			while ((c = ch_back_get()) == '\n')
				if (sigs)
					return (NULL_POSITION);
			if (c == EOI)
				return (NULL_POSITION);
			(void) ch_forw_get();
		}
	}

	/*
	 * Scan backwards until we hit the beginning of the line.
	 */
	for (;;)
	{
		if (sigs)
			return (NULL_POSITION);
		c = ch_back_get();
		if (c == '\n')
		{
			/*
			 * This is the newline ending the previous line.
			 * We have hit the beginning of the line.
			 */
			new_pos = ch_tell() + 1;
			break;
		}
		if (c == EOI)
		{
			/*
			 * We have hit the beginning of the file.
			 * This must be the first line in the file.
			 * This must, of course, be the beginning of the line.
			 */
			new_pos = ch_tell();
			break;
		}
	}

	/*
	 * Now scan forwards from the beginning of this line.
	 * We keep discarding "printable lines" (based on screen width)
	 * until we reach the curr_pos.
	 *
	 * {{ This algorithm is pretty inefficient if the lines
	 *    are much longer than the screen width, 
	 *    but I don't know of any better way. }}
	 */
	if (ch_seek(new_pos))
		return (NULL_POSITION);
    loop:
	begin_new_pos = new_pos;
	prewind();

	do
	{
		c = ch_forw_get();
		if (c == EOI || sigs)
			return (NULL_POSITION);
		new_pos++;
		if (c == '\n')
			break;
		if (pappend(c))
		{
			/*
			 * Got a full printable line, but we haven't
			 * reached our curr_pos yet.  Discard the line
			 * and start a new one.
			 */
			(void) pappend('\0');
			(void) ch_back_get();
			new_pos--;
			goto loop;
		}
	} while (new_pos < curr_pos);

	(void) pappend('\0');

	return (begin_new_pos);
}
E 1
