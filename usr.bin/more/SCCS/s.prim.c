h49981
s 00002/00002/00806
d D 8.1 93/06/06 15:37:23 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00802
d D 5.9 93/02/11 22:02:17 edward 9 8
c for terminals with "db", clear last line before scrolling up
e
s 00001/00012/00801
d D 5.8 90/06/01 17:04:56 bostic 8 7
c new copyright notice
e
s 00020/00029/00792
d D 5.7 88/12/13 21:58:34 bostic 7 6
c if a short file, don't move to lower-left corner of the screen,
c unless editing or movement attempted, including at exit.  Correct dumb
c mistake in window signal handling.  Add routine to copy portions of the table.
e
s 00013/00009/00808
d D 5.6 88/12/06 18:25:07 bostic 6 5
c make '' default to file beginning if no large movements yet
e
s 00127/00223/00690
d D 5.5 88/11/22 16:51:45 bostic 5 4
c less -> more
e
s 00002/00004/00911
d D 5.4 88/07/25 12:05:16 bostic 4 3
c update copyright notice
e
s 00003/00002/00912
d D 5.3 88/07/22 12:06:19 bostic 3 2
c lint cleanup
e
s 00001/00006/00913
d D 5.2 88/07/22 11:05:49 bostic 2 1
c TAGS is default
e
s 00919/00000/00000
d D 5.1 88/07/21 18:53:21 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 10
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 4
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 4
D 8
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 4
 * by the University of California, Berkeley.  The name of the
E 4
I 4
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 4
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Primitives for displaying the file on the screen.
 */

D 5
#include "less.h"
#include "position.h"
E 5
I 5
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <less.h>
E 5

D 5
public int hit_eof;	/* Keeps track of how many times we hit end of file */
public int screen_trashed;
E 5
I 5
int back_scroll = -1;
int hit_eof;		/* keeps track of how many times we hit end of file */
int screen_trashed;
E 5

static int squished;

D 5
extern int quiet;
E 5
extern int sigs;
D 5
extern int how_search;
E 5
extern int top_scroll;
D 5
extern int back_scroll;
E 5
extern int sc_width, sc_height;
D 5
extern int quit_at_eof;
E 5
extern int caseless;
extern int linenums;
D 5
extern int plusoption;
extern char *line;
extern char *first_cmd;
E 5
D 2
#if TAGS
E 2
extern int tagoption;
I 5
extern char *line;
I 9
extern int retain_below;
E 9
E 5
D 2
#endif
E 2

D 5
/*
 * Sound the bell to indicate he is trying to move past end of file.
 */
	static void
eof_bell()
{
	if (quiet == NOT_QUIET)
		bell();
	else
		vbell();
}
E 5
I 5
off_t position(), forw_line(), back_line(), forw_raw_line(), back_raw_line();
off_t ch_length(), ch_tell();
E 5

/*
 * Check to see if the end of file is currently "displayed".
 */
D 5
	static void
E 5
eof_check()
{
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5

	if (sigs)
		return;
	/*
	 * If the bottom line is empty, we are at EOF.
	 * If the bottom line ends at the file length,
	 * we must be just at EOF.
	 */
	pos = position(BOTTOM_PLUS_ONE);
	if (pos == NULL_POSITION || pos == ch_length())
		hit_eof++;
}

/*
 * If the screen is "squished", repaint it.
 * "Squished" means the first displayed line is not at the top
 * of the screen; this can happen when we display a short file
 * for the first time.
 */
D 5
	static void
E 5
squish_check()
{
D 5
	if (!squished)
		return;
	squished = 0;
	repaint();
E 5
I 5
	if (squished) {
		squished = 0;
		repaint();
	}
E 5
}

/*
D 5
 * Display n lines, scrolling forward, 
 * starting at position pos in the input file.
 * "force" means display the n lines even if we hit end of file.
 * "only_last" means display only the last screenful if n > screen size.
E 5
I 5
 * Display n lines, scrolling forward, starting at position pos in the
D 7
 * input file.  "force" means display the n lines even if we hit end of
 * file.  "only_last" means display only the last screenful if n > screen
 * size.
E 7
I 7
 * input file.  "only_last" means display only the last screenful if
 * n > screen size.
E 7
E 5
 */
D 5
	static void
E 5
D 7
forw(n, pos, force, only_last)
E 7
I 7
forw(n, pos, only_last)
E 7
	register int n;
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5
D 7
	int force;
E 7
	int only_last;
{
I 7
	extern int short_file;
E 7
D 5
	int eof = 0;
	int nlines = 0;
	int do_repaint;
E 5
	static int first_time = 1;
I 5
	int eof = 0, do_repaint;
E 5

	squish_check();

	/*
	 * do_repaint tells us not to display anything till the end, 
	 * then just repaint the entire screen.
	 */
	do_repaint = (only_last && n > sc_height-1);

D 5
	if (!do_repaint)
	{
		if (top_scroll && n >= sc_height - 1)
		{
E 5
I 5
	if (!do_repaint) {
		if (top_scroll && n >= sc_height - 1) {
E 5
			/*
			 * Start a new screen.
			 * {{ This is not really desirable if we happen
			 *    to hit eof in the middle of this screen,
			 *    but we don't yet know if that will happen. }}
			 */
D 5
			if (top_scroll == 2)
				clear();
E 5
I 5
			clear();
E 5
			home();
D 7
			force = 1;
E 7
D 5
		} else
		{
E 5
I 5
		} else {
E 5
			lower_left();
			clear_eol();
		}

D 5
		if (pos != position(BOTTOM_PLUS_ONE))
		{
			/*
			 * This is not contiguous with what is
			 * currently displayed.  Clear the screen image 
			 * (position table) and start a new screen.
			 */
E 5
I 5
		/*
		 * This is not contiguous with what is currently displayed.
		 * Clear the screen image (position table) and start a new
		 * screen.
		 */
		if (pos != position(BOTTOM_PLUS_ONE)) {
E 5
			pos_clear();
			add_forw_pos(pos);
D 7
			force = 1;
E 7
D 5
			if (top_scroll)
			{
				if (top_scroll == 2)
					clear();
E 5
I 5
			if (top_scroll) {
				clear();
E 5
				home();
			} else if (!first_time)
D 5
			{
E 5
				putstr("...skipping...\n");
D 5
			}
E 5
		}
	}

D 5
	while (--n >= 0)
	{
E 5
I 5
D 7
	while (--n >= 0) {
E 7
I 7
	for (short_file = 0; --n >= 0;) {
E 7
E 5
		/*
		 * Read the next line of input.
		 */
		pos = forw_line(pos);
D 5
		if (pos == NULL_POSITION)
		{
E 5
I 5
		if (pos == NULL_POSITION) {
E 5
			/*
D 7
			 * End of file: stop here unless the top line 
			 * is still empty, or "force" is true.
E 7
I 7
			 * end of file; copy the table if the file was
			 * too small for an entire screen.
E 7
			 */
			eof = 1;
D 7
			if (!force && position(TOP) != NULL_POSITION)
				break;
			line = NULL;
E 7
I 7
			if (position(TOP) == NULL_POSITION) {
				copytable();
				if (!position(TOP))
					short_file = 1;
			}
			break;
E 7
		}
		/*
		 * Add the position of the next line to the position table.
		 * Display the current line on the screen.
		 */
		add_forw_pos(pos);
D 5
		nlines++;
E 5
		if (do_repaint)
			continue;
		/*
D 5
		 * If this is the first screen displayed and
		 * we hit an early EOF (i.e. before the requested
		 * number of lines), we "squish" the display down
		 * at the bottom of the screen.
		 * But don't do this if a + option or a -t option
		 * was given.  These options can cause us to
		 * start the display after the beginning of the file,
E 5
I 5
		 * If this is the first screen displayed and we hit an early
		 * EOF (i.e. before the requested number of lines), we
		 * "squish" the display down at the bottom of the screen.
		 * But don't do this if a -t option was given; it can cause
		 * us to start the display after the beginning of the file,
E 5
		 * and it is not appropriate to squish in that case.
		 */
D 5
		if (first_time && line == NULL && !top_scroll && 
D 2
#if TAGS
		    !tagoption &&
#endif
		    !plusoption)
E 2
I 2
		    !tagoption && !plusoption)
E 2
		{
E 5
I 5
		if (first_time && line == NULL && !top_scroll && !tagoption) {
E 5
			squished = 1;
			continue;
		}
D 5
		if (top_scroll == 1)
			clear_eol();
E 5
		put_line();
	}

	if (eof && !sigs)
		hit_eof++;
	else
		eof_check();
D 5
	if (nlines == 0)
		eof_bell();
	else if (do_repaint)
E 5
I 5
	if (do_repaint)
E 5
		repaint();
	first_time = 0;
	(void) currline(BOTTOM);
}

/*
 * Display n lines, scrolling backward.
 */
D 5
	static void
E 5
D 7
back(n, pos, force, only_last)
E 7
I 7
back(n, pos, only_last)
E 7
	register int n;
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5
D 7
	int force;
E 7
	int only_last;
{
D 5
	int nlines = 0;
E 5
	int do_repaint;

	squish_check();
	do_repaint = (n > get_back_scroll() || (only_last && n > sc_height-1));
	hit_eof = 0;
	while (--n >= 0)
	{
		/*
		 * Get the previous line of input.
		 */
		pos = back_line(pos);
		if (pos == NULL_POSITION)
D 7
		{
			/*
			 * Beginning of file: stop here unless "force" is true.
			 */
			if (!force)
				break;
			line = NULL;
		}
E 7
I 7
			break;
E 7
		/*
		 * Add the position of the previous line to the position table.
		 * Display the line on the screen.
		 */
		add_back_pos(pos);
D 5
		nlines++;
E 5
		if (!do_repaint)
		{
I 9
			if (retain_below)
			{
				lower_left();
				clear_eol();
			}
E 9
			home();
			add_line();
			put_line();
		}
	}

	eof_check();
D 5
	if (nlines == 0)
		eof_bell();
	else if (do_repaint)
E 5
I 5
	if (do_repaint)
E 5
		repaint();
	(void) currline(BOTTOM);
}

/*
 * Display n more lines, forward.
 * Start just after the line currently displayed at the bottom of the screen.
 */
D 5
	public void
E 5
forward(n, only_last)
	int n;
	int only_last;
{
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5

D 5
	if (quit_at_eof && hit_eof)
	{
E 5
I 5
	if (hit_eof) {
E 5
		/*
D 5
		 * If the -e flag is set and we're trying to go
		 * forward from end-of-file, go on to the next file.
E 5
I 5
		 * If we're trying to go forward from end-of-file,
		 * go on to the next file.
E 5
		 */
		next_file(1);
		return;
	}

	pos = position(BOTTOM_PLUS_ONE);
	if (pos == NULL_POSITION)
	{
D 5
		eof_bell();
E 5
		hit_eof++;
		return;
	}
D 7
	forw(n, pos, 0, only_last);
E 7
I 7
	forw(n, pos, only_last);
E 7
}

/*
 * Display n more lines, backward.
 * Start just before the line currently displayed at the top of the screen.
 */
D 5
	public void
E 5
backward(n, only_last)
	int n;
	int only_last;
{
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5

	pos = position(TOP);
I 5
	/*
	 * This will almost never happen, because the top line is almost
	 * never empty.
	 */
E 5
	if (pos == NULL_POSITION)
D 5
	{
		/* 
		 * This will almost never happen,
		 * because the top line is almost never empty. 
		 */
		eof_bell();
E 5
		return;   
D 5
	}
E 5
D 7
	back(n, pos, 0, only_last);
E 7
I 7
	back(n, pos, only_last);
E 7
}

/*
 * Repaint the screen, starting from a specified position.
 */
D 5
	static void
prepaint(pos)	
	POSITION pos;
E 5
I 5
prepaint(pos)
	off_t pos;
E 5
{
	hit_eof = 0;
D 7
	forw(sc_height-1, pos, 1, 0);
E 7
I 7
	forw(sc_height-1, pos, 0);
E 7
	screen_trashed = 0;
}

/*
 * Repaint the screen.
 */
D 5
	public void
E 5
repaint()
{
	/*
	 * Start at the line currently at the top of the screen
	 * and redisplay the screen.
	 */
	prepaint(position(TOP));
}

/*
 * Jump to the end of the file.
 * It is more convenient to paint the screen backward,
 * from the end of the file toward the beginning.
 */
D 5
	public void
E 5
jump_forw()
{
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5

	if (ch_end_seek())
	{
		error("Cannot seek to end of file");
		return;
	}
	lastmark();
	pos = ch_tell();
	clear();
	pos_clear();
	add_back_pos(pos);
D 7
	back(sc_height - 1, pos, 0, 0);
E 7
I 7
	back(sc_height - 1, pos, 0);
E 7
}

/*
 * Jump to line n in the file.
 */
D 5
	public void
E 5
jump_back(n)
	register int n;
{
D 5
	register int c;
	int nlines;
E 5
I 5
	register int c, nlines;
E 5

	/*
	 * This is done the slow way, by starting at the beginning
	 * of the file and counting newlines.
	 *
	 * {{ Now that we have line numbering (in linenum.c),
	 *    we could improve on this by starting at the
	 *    nearest known line rather than at the beginning. }}
	 */
D 5
	if (ch_seek((POSITION)0))
	{
E 5
I 5
	if (ch_seek((off_t)0)) {
E 5
		/* 
		 * Probably a pipe with beginning of file no longer buffered. 
		 * If he wants to go to line 1, we do the best we can, 
		 * by going to the first line which is still buffered.
		 */
		if (n <= 1 && ch_beg_seek() == 0)
			jump_loc(ch_tell());
		error("Cannot get to beginning of file");
		return;
	}

	/*
	 * Start counting lines.
	 */
	for (nlines = 1;  nlines < n;  nlines++)
D 5
	{
E 5
		while ((c = ch_forw_get()) != '\n')
D 5
			if (c == EOI)
			{
E 5
I 5
			if (c == EOI) {
E 5
				char message[40];
D 3
				sprintf(message, "File has only %d lines", 
E 3
I 3
				(void)sprintf(message, "File has only %d lines",
E 3
D 5
					nlines-1);
E 5
I 5
				    nlines - 1);
E 5
				error(message);
				return;
			}
D 5
	}

E 5
	jump_loc(ch_tell());
}

/*
 * Jump to a specified percentage into the file.
 * This is a poor compensation for not being able to
 * quickly jump to a specific line number.
 */
D 5
	public void
E 5
jump_percent(percent)
	int percent;
{
D 5
	POSITION pos, len;
E 5
I 5
	off_t pos, len, ch_length();
E 5
	register int c;

	/*
	 * Determine the position in the file
	 * (the specified percentage of the file's length).
	 */
	if ((len = ch_length()) == NULL_POSITION)
	{
		error("Don't know length of file");
		return;
	}
	pos = (percent * len) / 100;

	/*
	 * Back up to the beginning of the line.
	 */
	if (ch_seek(pos) == 0)
	{
		while ((c = ch_back_get()) != '\n' && c != EOI)
			;
		if (c == '\n')
			(void) ch_forw_get();
		pos = ch_tell();
	}
	jump_loc(pos);
}

/*
 * Jump to a specified position in the file.
 */
D 5
	public void
E 5
jump_loc(pos)
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5
{
	register int nline;
D 5
	POSITION tpos;
E 5
I 5
	off_t tpos;
E 5

D 5
	if ((nline = onscreen(pos)) >= 0)
	{
E 5
I 5
	if ((nline = onscreen(pos)) >= 0) {
E 5
		/*
		 * The line is currently displayed.  
		 * Just scroll there.
		 */
D 7
		forw(nline, position(BOTTOM_PLUS_ONE), 1, 0);
E 7
I 7
		forw(nline, position(BOTTOM_PLUS_ONE), 0);
E 7
		return;
	}

	/*
	 * Line is not on screen.
	 * Seek to the desired location.
	 */
D 5
	if (ch_seek(pos))
	{
E 5
I 5
	if (ch_seek(pos)) {
E 5
		error("Cannot seek to that position");
		return;
	}

	/*
D 5
	 * See if the desired line is BEFORE the currently
	 * displayed screen.  If so, then move forward far
	 * enough so the line we're on will be at the bottom
	 * of the screen, in order to be able to call back()
	 * to make the screen scroll backwards & put the line
	 * at the top of the screen.
E 5
I 5
	 * See if the desired line is BEFORE the currently displayed screen.
	 * If so, then move forward far enough so the line we're on will be
	 * at the bottom of the screen, in order to be able to call back()
	 * to make the screen scroll backwards & put the line at the top of
	 * the screen.
E 5
	 * {{ This seems inefficient, but it's not so bad,
	 *    since we can never move forward more than a
	 *    screenful before we stop to redraw the screen. }}
	 */
	tpos = position(TOP);
D 5
	if (tpos != NULL_POSITION && pos < tpos)
	{
		POSITION npos = pos;
E 5
I 5
	if (tpos != NULL_POSITION && pos < tpos) {
		off_t npos = pos;
E 5
		/*
		 * Note that we can't forw_line() past tpos here,
		 * so there should be no EOI at this stage.
		 */
		for (nline = 0;  npos < tpos && nline < sc_height - 1;  nline++)
			npos = forw_line(npos);

D 5
		if (npos < tpos)
		{
E 5
I 5
		if (npos < tpos) {
E 5
			/*
			 * More than a screenful back.
			 */
			lastmark();
			clear();
			pos_clear();
			add_back_pos(npos);
		}

		/*
		 * Note that back() will repaint() if nline > back_scroll.
		 */
D 7
		back(nline, npos, 1, 0);
E 7
I 7
		back(nline, npos, 0);
E 7
		return;
	}
	/*
	 * Remember where we were; clear and paint the screen.
	 */
D 5
  	lastmark();
  	prepaint(pos);
E 5
I 5
	lastmark();
	prepaint(pos);
E 5
}

/*
 * The table of marks.
 * A mark is simply a position in the file.
 */
#define	NMARKS		(27)		/* 26 for a-z plus one for quote */
#define	LASTMARK	(NMARKS-1)	/* For quote */
D 5
static POSITION marks[NMARKS];
E 5
I 5
static off_t marks[NMARKS];
E 5

/*
 * Initialize the mark table to show no marks are set.
 */
D 5
	public void
E 5
init_mark()
{
	int i;

	for (i = 0;  i < NMARKS;  i++)
		marks[i] = NULL_POSITION;
}

/*
 * See if a mark letter is valid (between a and z).
 */
	static int
badmark(c)
	int c;
{
	if (c < 'a' || c > 'z')
	{
		error("Choose a letter between 'a' and 'z'");
		return (1);
	}
	return (0);
}

/*
 * Set a mark.
 */
D 5
	public void
E 5
setmark(c)
	int c;
{
	if (badmark(c))
		return;
	marks[c-'a'] = position(TOP);
}

D 5
	public void
E 5
lastmark()
{
	marks[LASTMARK] = position(TOP);
}

/*
 * Go to a previously set mark.
 */
D 5
	public void
E 5
gomark(c)
	int c;
{
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5

D 6
	if (c == '\'')
E 6
I 6
	if (c == '\'') {
E 6
		pos = marks[LASTMARK];
D 6
	else if (badmark(c))
		return;
	else 
E 6
I 6
		if (pos == NULL_POSITION)
			pos = 0;
	}
	else {
		if (badmark(c))
			return;
E 6
		pos = marks[c-'a'];
D 6

	if (pos == NULL_POSITION)
		error("mark not set");
	else
		jump_loc(pos);
E 6
I 6
		if (pos == NULL_POSITION) {
			error("mark not set");
			return;
		}
	}
	jump_loc(pos);
E 6
}

/*
 * Get the backwards scroll limit.
 * Must call this function instead of just using the value of
 * back_scroll, because the default case depends on sc_height and
 * top_scroll, as well as back_scroll.
 */
D 5
	public int
E 5
get_back_scroll()
{
	if (back_scroll >= 0)
		return (back_scroll);
	if (top_scroll)
		return (sc_height - 2);
	return (sc_height - 1);
}

/*
 * Search for the n-th occurence of a specified pattern, 
 * either forward or backward.
 */
D 5
	public void
E 5
search(search_forward, pattern, n, wantmatch)
	register int search_forward;
	register char *pattern;
	register int n;
	int wantmatch;
{
D 5
	POSITION pos, linepos;
E 5
I 5
	off_t pos, linepos;
E 5
	register char *p;
	register char *q;
	int linenum;
	int linematch;
D 5
#if RECOMP
E 5
I 5
#ifdef RECOMP
E 5
	char *re_comp();
	char *errmsg;
#else
D 5
#if REGCMP
E 5
I 5
#ifdef REGCMP
E 5
	char *regcmp();
	static char *cpattern = NULL;
#else
	static char lpbuf[100];
	static char *last_pattern = NULL;
I 3
	char *strcpy();
E 3
#endif
#endif

I 5
	/*
	 * For a caseless search, convert any uppercase in the pattern to
	 * lowercase.
	 */
E 5
	if (caseless && pattern != NULL)
D 5
	{
		/*
		 * For a caseless search, convert any uppercase
		 * in the pattern to lowercase.
		 */
		for (p = pattern;  *p != '\0';  p++)
			if (*p >= 'A' && *p <= 'Z')
				*p += 'a' - 'A';
	}
#if RECOMP
E 5
I 5
		for (p = pattern;  *p;  p++)
			if (isupper(*p))
				*p = tolower(*p);
#ifdef RECOMP
E 5

	/*
	 * (re_comp handles a null pattern internally, 
	 *  so there is no need to check for a null pattern here.)
	 */
	if ((errmsg = re_comp(pattern)) != NULL)
	{
		error(errmsg);
D 5
		return;
E 5
I 5
		return(0);
E 5
	}
#else
D 5
#if REGCMP
E 5
I 5
#ifdef REGCMP
E 5
	if (pattern == NULL || *pattern == '\0')
	{
		/*
		 * A null pattern means use the previous pattern.
		 * The compiled previous pattern is in cpattern, so just use it.
		 */
		if (cpattern == NULL)
		{
			error("No previous regular expression");
D 5
			return;
E 5
I 5
			return(0);
E 5
		}
	} else
	{
		/*
		 * Otherwise compile the given pattern.
		 */
		char *s;
		if ((s = regcmp(pattern, 0)) == NULL)
		{
			error("Invalid pattern");
D 5
			return;
E 5
I 5
			return(0);
E 5
		}
		if (cpattern != NULL)
			free(cpattern);
		cpattern = s;
	}
#else
	if (pattern == NULL || *pattern == '\0')
	{
		/*
		 * Null pattern means use the previous pattern.
		 */
		if (last_pattern == NULL)
		{
			error("No previous regular expression");
D 5
			return;
E 5
I 5
			return(0);
E 5
		}
		pattern = last_pattern;
	} else
	{
D 3
		strcpy(lpbuf, pattern);
E 3
I 3
		(void)strcpy(lpbuf, pattern);
E 3
		last_pattern = lpbuf;
	}
#endif
#endif

	/*
	 * Figure out where to start the search.
	 */

D 5
	if (position(TOP) == NULL_POSITION)
	{
E 5
I 5
	if (position(TOP) == NULL_POSITION) {
E 5
		/*
D 5
		 * Nothing is currently displayed.
		 * Start at the beginning of the file.
		 * (This case is mainly for first_cmd searches,
		 * for example, "+/xyz" on the command line.)
E 5
I 5
		 * Nothing is currently displayed.  Start at the beginning
		 * of the file.  (This case is mainly for searches from the
		 * command line.
E 5
		 */
D 5
		pos = (POSITION)0;
	} else if (!search_forward)
	{
E 5
I 5
		pos = (off_t)0;
	} else if (!search_forward) {
E 5
		/*
		 * Backward search: start just before the top line
		 * displayed on the screen.
		 */
		pos = position(TOP);
D 5
	} else if (how_search == 0)
	{
E 5
I 5
	} else {
E 5
		/*
D 5
		 * Start at the second real line displayed on the screen.
		 */
		pos = position(TOP);
		do
			pos = forw_raw_line(pos);
		while (pos < position(TOP+1));
	} else if (how_search == 1)
	{
		/*
		 * Start just after the bottom line displayed on the screen.
		 */
		pos = position(BOTTOM_PLUS_ONE);
	} else
	{
		/*
E 5
		 * Start at the second screen line displayed on the screen.
		 */
		pos = position(TOP_PLUS_ONE);
	}

	if (pos == NULL_POSITION)
	{
		/*
		 * Can't find anyplace to start searching from.
		 */
		error("Nothing to search");
D 5
		return;
E 5
I 5
		return(0);
E 5
	}

	linenum = find_linenum(pos);
	for (;;)
	{
		/*
		 * Get lines until we find a matching one or 
		 * until we hit end-of-file (or beginning-of-file 
		 * if we're going backwards).
		 */
		if (sigs)
			/*
			 * A signal aborts the search.
			 */
D 5
			return;
E 5
I 5
			return(0);
E 5

		if (search_forward)
		{
			/*
			 * Read the next line, and save the 
			 * starting position of that line in linepos.
			 */
			linepos = pos;
			pos = forw_raw_line(pos);
			if (linenum != 0)
				linenum++;
		} else
		{
			/*
			 * Read the previous line and save the
			 * starting position of that line in linepos.
			 */
			pos = back_raw_line(pos);
			linepos = pos;
			if (linenum != 0)
				linenum--;
		}

		if (pos == NULL_POSITION)
		{
			/*
			 * We hit EOF/BOF without a match.
			 */
			error("Pattern not found");
D 5
			return;
E 5
I 5
			return(0);
E 5
		}

		/*
		 * If we're using line numbers, we might as well
		 * remember the information we have now (the position
		 * and line number of the current line).
		 */
		if (linenums)
			add_lnum(linenum, pos);

I 5
		/*
		 * If this is a caseless search, convert uppercase in the
		 * input line to lowercase.
		 */
E 5
		if (caseless)
D 5
		{
			/*
			 * If this is a caseless search, convert 
			 * uppercase in the input line to lowercase.
			 * While we're at it, remove any backspaces
			 * along with the preceeding char.
			 * This allows us to match text which is 
			 * underlined or overstruck.
			 */
			for (p = q = line;  *p != '\0';  p++, q++)
			{
				if (*p >= 'A' && *p <= 'Z')
					/* Convert uppercase to lowercase. */
					*q = *p + 'a' - 'A';
				else if (q > line && *p == '\b')
					/* Delete BS and preceeding char. */
					q -= 2;
				else
					/* Otherwise, just copy. */
					*q = *p;
			}
		}
E 5
I 5
			for (p = q = line;  *p;  p++, q++)
				*q = isupper(*p) ? tolower(*p) : *p;
E 5

		/*
I 5
		 * Remove any backspaces along with the preceeding char.
		 * This allows us to match text which is underlined or
		 * overstruck.
		 */
		for (p = q = line;  *p;  p++, q++)
			if (q > line && *p == '\b')
				/* Delete BS and preceeding char. */
				q -= 2;
			else
				/* Otherwise, just copy. */
				*q = *p;

		/*
E 5
		 * Test the next line to see if we have a match.
		 * This is done in a variety of ways, depending
		 * on what pattern matching functions are available.
		 */
D 5
#if REGCMP
E 5
I 5
#ifdef REGCMP
E 5
		linematch = (regex(cpattern, line) != NULL);
#else
D 5
#if RECOMP
E 5
I 5
#ifdef RECOMP
E 5
		linematch = (re_exec(line) == 1);
#else
		linematch = match(pattern, line);
#endif
#endif
		/*
		 * We are successful if wantmatch and linematch are
		 * both true (want a match and got it),
		 * or both false (want a non-match and got it).
		 */
		if (((wantmatch && linematch) || (!wantmatch && !linematch)) &&
		      --n <= 0)
			/*
			 * Found the line.
			 */
			break;
	}
D 5

E 5
	jump_loc(linepos);
I 5
	return(1);
E 5
}

D 5
#if (!REGCMP) && (!RECOMP)
E 5
I 5
#if !defined(REGCMP) && !defined(RECOMP)
E 5
/*
 * We have neither regcmp() nor re_comp().
 * We use this function to do simple pattern matching.
 * It supports no metacharacters like *, etc.
 */
D 5
	static int
E 5
I 5
static
E 5
match(pattern, buf)
	char *pattern, *buf;
{
	register char *pp, *lp;

	for ( ;  *buf != '\0';  buf++)
	{
		for (pp = pattern, lp = buf;  *pp == *lp;  pp++, lp++)
			if (*pp == '\0' || *lp == '\0')
				break;
		if (*pp == '\0')
			return (1);
	}
	return (0);
}
#endif
E 1
