h02478
s 00002/00002/00480
d D 8.1 93/06/06 15:36:30 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00480
d D 5.5 91/07/24 21:15:23 cael 5 4
c fix off-by-one column errors (needs more work, this gets
c most of the ugliness away from *my* man pages, harumph)
e
s 00001/00012/00479
d D 5.4 90/06/01 17:04:05 bostic 4 3
c new copyright notice
e
s 00053/00073/00438
d D 5.3 88/11/22 16:51:26 bostic 3 2
c less -> more
e
s 00002/00004/00509
d D 5.2 88/07/25 12:04:53 bostic 2 1
c update copyright notice
e
s 00513/00000/00000
d D 5.1 88/07/21 18:52:52 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
 * Routines to manipulate the "line buffer".
 * The line buffer holds a line of output as it is being built
 * in preparation for output to the screen.
 * We keep track of the PRINTABLE length of the line as it is being built.
 */

D 3
#include "less.h"
E 3
I 3
#include <sys/types.h>
#include <ctype.h>
#include <less.h>
E 3

static char linebuf[1024];	/* Buffer which holds the current output line */
static char *curr;		/* Pointer into linebuf */
static int column;		/* Printable length, accounting for
				   backspaces, etc. */
/*
D 3
 * A ridiculously complex state machine takes care of backspaces 
 * when in BS_SPECIAL mode.  The complexity arises from the attempt
 * to deal with all cases, especially involving long lines with underlining,
 * boldfacing or whatever.  There are still some cases which will break it.
E 3
I 3
 * A ridiculously complex state machine takes care of backspaces.  The
 * complexity arises from the attempt to deal with all cases, especially
 * involving long lines with underlining, boldfacing or whatever.  There
 * are still some cases which will break it.
E 3
 *
 * There are four states:
 *	LN_NORMAL is the normal state (not in underline mode).
 *	LN_UNDERLINE means we are in underline mode.  We expect to get
 *		either a sequence like "_\bX" or "X\b_" to continue
 *		underline mode, or anything else to end underline mode.
 *	LN_BOLDFACE means we are in boldface mode.  We expect to get sequences
 *		like "X\bX\b...X\bX" to continue boldface mode, or anything
 *		else to end boldface mode.
 *	LN_UL_X means we are one character after LN_UNDERLINE
 *		(we have gotten the '_' in "_\bX" or the 'X' in "X\b_").
 *	LN_UL_XB means we are one character after LN_UL_X 
 *		(we have gotten the backspace in "_\bX" or "X\b_";
 *		we expect one more ordinary character, 
 *		which will put us back in state LN_UNDERLINE).
 *	LN_BO_X means we are one character after LN_BOLDFACE
 *		(we have gotten the 'X' in "X\bX").
 *	LN_BO_XB means we are one character after LN_BO_X
 *		(we have gotten the backspace in "X\bX";
 *		we expect one more 'X' which will put us back
 *		in LN_BOLDFACE).
 */
static int ln_state;		/* Currently in normal/underline/bold/etc mode? */
#define	LN_NORMAL	0	/* Not in underline, boldface or whatever mode */
#define	LN_UNDERLINE	1	/* In underline, need next char */
#define	LN_UL_X		2	/* In underline, got char, need \b */
#define	LN_UL_XB	3	/* In underline, got char & \b, need one more */
#define	LN_BOLDFACE	4	/* In boldface, need next char */
#define	LN_BO_X		5	/* In boldface, got char, need \b */
#define	LN_BO_XB	6	/* In boldface, got char & \b, need same char */

D 3
public char *line;		/* Pointer to the current line.
E 3
I 3
char *line;			/* Pointer to the current line.
E 3
				   Usually points to linebuf. */

extern int bs_mode;
extern int tabstop;
extern int bo_width, be_width;
extern int ul_width, ue_width;
extern int sc_width, sc_height;

/*
 * Rewind the line buffer.
 */
D 3
	public void
E 3
prewind()
{
	line = curr = linebuf;
	ln_state = LN_NORMAL;
	column = 0;
}

/*
 * Append a character to the line buffer.
 * Expand tabs into spaces, handle underlining, boldfacing, etc.
 * Returns 0 if ok, 1 if couldn't fit in buffer.
 */
I 3
#define	NEW_COLUMN(addon) \
	if (column + addon + (ln_state ? ue_width : 0) > sc_width) \
		return(1); \
	else \
		column += addon
E 3

D 3
#define	NEW_COLUMN(newcol)	if ((newcol) + ((ln_state)?ue_width:0) > sc_width) \
					return (1); else column = (newcol)

	public int
E 3
pappend(c)
	int c;
{
D 3
	if (c == '\0')
	{
E 3
I 3
	if (c == '\0') {
E 3
		/*
		 * Terminate any special modes, if necessary.
		 * Append a '\0' to the end of the line.
		 */
D 3
		switch (ln_state)
		{
E 3
I 3
		switch (ln_state) {
E 3
		case LN_UL_X:
			curr[0] = curr[-1];
			curr[-1] = UE_CHAR;
			curr++;
			break;
		case LN_BO_X:
			curr[0] = curr[-1];
			curr[-1] = BE_CHAR;
			curr++;
			break;
		case LN_UL_XB:
		case LN_UNDERLINE:
			*curr++ = UE_CHAR;
			break;
		case LN_BO_XB:
		case LN_BOLDFACE:
			*curr++ = BE_CHAR;
			break;
		}
		ln_state = LN_NORMAL;
		*curr = '\0';
D 3
		return (0);
E 3
I 3
		return(0);
E 3
	}

	if (curr > linebuf + sizeof(linebuf) - 12)
		/*
		 * Almost out of room in the line buffer.
		 * Don't take any chances.
		 * {{ Linebuf is supposed to be big enough that this
		 *    will never happen, but may need to be made 
		 *    bigger for wide screens or lots of backspaces. }}
		 */
D 3
		return (1);
E 3
I 3
		return(1);
E 3

D 3
	if (bs_mode == BS_SPECIAL)
	{
E 3
I 3
	if (!bs_mode) {
E 3
		/*
		 * Advance the state machine.
		 */
D 3
		switch (ln_state)
		{
E 3
I 3
		switch (ln_state) {
E 3
		case LN_NORMAL:
D 3
			if (curr <= linebuf + 1 || curr[-1] != '\b')
E 3
I 3
			if (curr <= linebuf + 1
			    || curr[-1] != (char)('H' | 0200))
E 3
				break;
D 3

E 3
I 3
			column -= 2;
E 3
			if (c == curr[-2])
				goto enter_boldface;
			if (c == '_' || curr[-2] == '_')
				goto enter_underline;
			curr -= 2;
			break;

enter_boldface:
			/*
			 * We have "X\bX" (including the current char).
			 * Switch into boldface mode.
			 */
I 5
			column--;
E 5
			if (column + bo_width + be_width + 1 >= sc_width)
				/*
				 * Not enough room left on the screen to 
				 * enter and exit boldface mode.
				 */
				return (1);

D 3
			if (bo_width > 0 && 
			    curr > linebuf + 2 && curr[-3] == ' ')
			{
E 3
I 3
			if (bo_width > 0 && curr > linebuf + 2
			    && curr[-3] == ' ') {
E 3
				/*
				 * Special case for magic cookie terminals:
				 * if the previous char was a space, replace 
				 * it with the "enter boldface" sequence.
				 */
				curr[-3] = BO_CHAR;
				column += bo_width-1;
D 3
			} else
			{
E 3
I 3
			} else {
E 3
				curr[-1] = curr[-2];
				curr[-2] = BO_CHAR;
				column += bo_width;
				curr++;
			}
			goto ln_bo_xb_case;

enter_underline:
			/*
			 * We have either "_\bX" or "X\b_" (including
			 * the current char).  Switch into underline mode.
			 */
I 5
			column--;
E 5
			if (column + ul_width + ue_width + 1 >= sc_width)
				/*
				 * Not enough room left on the screen to 
				 * enter and exit underline mode.
				 */
				return (1);

			if (ul_width > 0 && 
			    curr > linebuf + 2 && curr[-3] == ' ')
			{
				/*
				 * Special case for magic cookie terminals:
				 * if the previous char was a space, replace 
				 * it with the "enter underline" sequence.
				 */
				curr[-3] = UL_CHAR;
				column += ul_width-1;
			} else
			{
				curr[-1] = curr[-2];
				curr[-2] = UL_CHAR;
				column += ul_width;
				curr++;
			}
			goto ln_ul_xb_case;
			/*NOTREACHED*/
		case LN_UL_XB:
			/*
			 * Termination of a sequence "_\bX" or "X\b_".
			 */
			if (c != '_' && curr[-2] != '_' && c == curr[-2])
			{
				/*
				 * We seem to have run on from underlining
				 * into boldfacing - this is a nasty fix, but
				 * until this whole routine is rewritten as a
				 * real DFA, ...  well ...
				 */
				curr[0] = curr[-2];
				curr[-2] = UE_CHAR;
				curr[-1] = BO_CHAR;
				curr += 2; /* char & non-existent backspace */
				ln_state = LN_BO_XB;
				goto ln_bo_xb_case;
			}
ln_ul_xb_case:
			if (c == '_')
				c = curr[-2];
			curr -= 2;
			ln_state = LN_UNDERLINE;
			break;
		case LN_BO_XB:
			/*
			 * Termination of a sequnce "X\bX".
			 */
			if (c != curr[-2] && (c == '_' || curr[-2] == '_'))
			{
				/*
				 * We seem to have run on from
				 * boldfacing into underlining.
				 */
				curr[0] = curr[-2];
				curr[-2] = BE_CHAR;
				curr[-1] = UL_CHAR;
				curr += 2; /* char & non-existent backspace */
				ln_state = LN_UL_XB;
				goto ln_ul_xb_case;
			}
ln_bo_xb_case:
			curr -= 2;
			ln_state = LN_BOLDFACE;
			break;
		case LN_UNDERLINE:
			if (column + ue_width + bo_width + 1 + be_width >= sc_width)
				/*
				 * We have just barely enough room to 
				 * exit underline mode and handle a possible
				 * underline/boldface run on mixup.
				 */
				return (1);
			ln_state = LN_UL_X;
			break;
		case LN_BOLDFACE:
			if (c == '\b')
			{
				ln_state = LN_BO_XB;
				break;
			}
			if (column + be_width + ul_width + 1 + ue_width >= sc_width)
				/*
				 * We have just barely enough room to 
				 * exit underline mode and handle a possible
				 * underline/boldface run on mixup.
				 */
				return (1);
			ln_state = LN_BO_X;
			break;
		case LN_UL_X:
			if (c == '\b')
				ln_state = LN_UL_XB;
			else
			{
				/*
				 * Exit underline mode.
				 * We have to shuffle the chars a bit
				 * to make this work.
				 */
				curr[0] = curr[-1];
				curr[-1] = UE_CHAR;
				column += ue_width;
				if (ue_width > 0 && curr[0] == ' ')
					/*
					 * Another special case for magic
					 * cookie terminals: if the next
					 * char is a space, replace it
					 * with the "exit underline" sequence.
					 */
					column--;
				else
					curr++;
				ln_state = LN_NORMAL;
			} 
			break;
		case LN_BO_X:
			if (c == '\b')
				ln_state = LN_BO_XB;
			else
			{
				/*
				 * Exit boldface mode.
				 * We have to shuffle the chars a bit
				 * to make this work.
				 */
				curr[0] = curr[-1];
				curr[-1] = BE_CHAR;
				column += be_width;
				if (be_width > 0 && curr[0] == ' ')
					/*
					 * Another special case for magic
					 * cookie terminals: if the next
					 * char is a space, replace it
					 * with the "exit boldface" sequence.
					 */
					column--;
				else
					curr++;
				ln_state = LN_NORMAL;
			} 
			break;
		}
	}
D 3
	
	if (c == '\t') 
	{
E 3
I 3

	if (c == '\t') {
E 3
		/*
		 * Expand a tab into spaces.
		 */
D 3
		do
		{
			NEW_COLUMN(column+1);
E 3
I 3
		do {
			NEW_COLUMN(1);
E 3
		} while ((column % tabstop) != 0);
		*curr++ = '\t';
		return (0);
	}

D 3
	if (c == '\b')
	{
		if (bs_mode == BS_CONTROL)
		{
			/*
			 * Treat backspace as a control char: output "^H".
			 */
			NEW_COLUMN(column+2);
			*curr++ = ('H' | 0200);
		} else
		{
			/*
			 * Output a real backspace.
			 */
E 3
I 3
	if (c == '\b') {
		if (ln_state == LN_NORMAL)
			NEW_COLUMN(2);
		else
E 3
			column--;
D 3
			*curr++ = '\b';
		}
		return (0);
E 3
I 3
		*curr++ = ('H' | 0200);
		return(0);
E 3
	} 

D 3
	if (control_char(c))
	{
E 3
I 3
	if (CONTROL_CHAR(c)) {
E 3
		/*
D 3
		 * Put a "^X" into the buffer.
		 * The 0200 bit is used to tell put_line() to prefix
		 * the char with a ^.  We don't actually put the ^
		 * in the buffer because we sometimes need to move
		 * chars around, and such movement might separate 
		 * the ^ from its following character.
		 * {{ This should be redone so that we can use an
		 *    8 bit (e.g. international) character set. }}
E 3
I 3
		 * Put a "^X" into the buffer.  The 0200 bit is used to tell
		 * put_line() to prefix the char with a ^.  We don't actually
		 * put the ^ in the buffer because we sometimes need to move
		 * chars around, and such movement might separate the ^ from
		 * its following character.
E 3
		 */
D 3
		NEW_COLUMN(column+2);
		*curr++ = (carat_char(c) | 0200);
		return (0);
E 3
I 3
		NEW_COLUMN(2);
		*curr++ = (CARAT_CHAR(c) | 0200);
		return(0);
E 3
	}

	/*
	 * Ordinary character.  Just put it in the buffer.
	 */
D 3
	NEW_COLUMN(column+1);
E 3
I 3
	NEW_COLUMN(1);
E 3
	*curr++ = c;
	return (0);
}

/*
 * Analogous to forw_line(), but deals with "raw lines":
 * lines which are not split for screen width.
 * {{ This is supposed to be more efficient than forw_line(). }}
 */
D 3
	public POSITION
E 3
I 3
off_t
E 3
forw_raw_line(curr_pos)
D 3
	POSITION curr_pos;
E 3
I 3
	off_t curr_pos;
E 3
{
	register char *p;
	register int c;
D 3
	POSITION new_pos;
E 3
I 3
	off_t new_pos, ch_tell();
E 3

	if (curr_pos == NULL_POSITION || ch_seek(curr_pos) ||
		(c = ch_forw_get()) == EOI)
		return (NULL_POSITION);

	p = linebuf;

	for (;;)
	{
		if (c == '\n' || c == EOI)
		{
			new_pos = ch_tell();
			break;
		}
		if (p >= &linebuf[sizeof(linebuf)-1])
		{
			/*
			 * Overflowed the input buffer.
			 * Pretend the line ended here.
			 * {{ The line buffer is supposed to be big
			 *    enough that this never happens. }}
			 */
			new_pos = ch_tell() - 1;
			break;
		}
		*p++ = c;
		c = ch_forw_get();
	}
	*p = '\0';
	line = linebuf;
	return (new_pos);
}

/*
 * Analogous to back_line(), but deals with "raw lines".
 * {{ This is supposed to be more efficient than back_line(). }}
 */
D 3
	public POSITION
E 3
I 3
off_t
E 3
back_raw_line(curr_pos)
D 3
	POSITION curr_pos;
E 3
I 3
	off_t curr_pos;
E 3
{
	register char *p;
	register int c;
D 3
	POSITION new_pos;
E 3
I 3
	off_t new_pos, ch_tell();
E 3

D 3
	if (curr_pos == NULL_POSITION || curr_pos <= (POSITION)0 ||
E 3
I 3
	if (curr_pos == NULL_POSITION || curr_pos <= (off_t)0 ||
E 3
		ch_seek(curr_pos-1))
		return (NULL_POSITION);

	p = &linebuf[sizeof(linebuf)];
	*--p = '\0';

	for (;;)
	{
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
D 3
			new_pos = (POSITION)0;
E 3
I 3
			new_pos = (off_t)0;
E 3
			break;
		}
		if (p <= linebuf)
		{
			/*
			 * Overflowed the input buffer.
			 * Pretend the line ended here.
			 */
			new_pos = ch_tell() + 1;
			break;
		}
		*--p = c;
	}
	line = p;
	return (new_pos);
}
E 1
