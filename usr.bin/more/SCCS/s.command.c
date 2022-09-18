h49530
s 00002/00002/00627
d D 8.1 93/06/06 15:36:11 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00628
d D 5.23 93/03/08 19:14:19 ralph 23 22
c position was not declared in getcc().
e
s 00003/00003/00625
d D 5.22 92/06/21 15:42:27 bostic 22 21
c off_t is a quad, now
e
s 00000/00002/00628
d D 5.21 91/03/01 15:12:03 bostic 21 20
c ANSI
e
s 00001/00012/00629
d D 5.20 90/06/01 17:03:32 bostic 20 19
c new copyright notice
e
s 00003/00003/00638
d D 5.19 90/04/01 17:19:11 leres 19 18
c In prompt(), use multiple putstr()s to avoid overrunning pbuf when "next_file"
c is long.
e
s 00002/00002/00639
d D 5.18 89/05/11 13:36:46 bostic 18 17
c file reorg, pathnames.h, paths.h
e
s 00002/00002/00639
d D 5.17 88/12/28 17:08:04 bostic 17 16
c exit on end-of-file if file shorter than a screen, regardless
e
s 00004/00002/00637
d D 5.16 88/12/07 20:06:28 bostic 16 15
c print out percentage by default, rather than line number
e
s 00083/00235/00556
d D 5.15 88/12/06 17:34:17 bostic 15 14
c remove -p (terse prompts); remove '&' prompt for ':' commands; reformat
e
s 00053/00004/00738
d D 5.14 88/12/06 15:16:32 bostic 14 13
c add ":a[rgs]" command from vi
e
s 00007/00002/00735
d D 5.13 88/11/29 16:22:05 bostic 13 12
c display next file name as part of "END" prompt
e
s 00009/00000/00728
d D 5.12 88/11/26 12:19:00 bostic 12 11
c on error, allow command character as well as return to continue
e
s 00004/00004/00724
d D 5.11 88/11/22 17:41:26 bostic 11 10
c =/^G show total bytes now; document may not always work
e
s 00159/00238/00569
d D 5.10 88/11/22 16:51:16 bostic 10 9
c less -> more
e
s 00026/00012/00781
d D 5.9 88/09/23 14:50:56 bostic 9 8
c isolate editor variable, only pass line numbers to vi
e
s 00007/00006/00786
d D 5.8 88/09/23 14:26:46 bostic 8 7
c don't force extra keystroke after '=' operators
e
s 00000/00009/00792
d D 5.7 88/09/23 14:15:50 bostic 7 6
c remove version command
e
s 00002/00004/00799
d D 5.6 88/07/25 12:04:32 bostic 6 5
c update copyright notice
e
s 00002/00002/00801
d D 5.5 88/07/22 12:03:47 bostic 5 4
c void sprintfs
e
s 00000/00001/00803
d D 5.4 88/07/22 11:29:07 bostic 4 3
c lint cleanup
e
s 00000/00007/00804
d D 5.3 88/07/21 19:12:07 bostic 3 2
c rip out EDITOR and EDIT_PGM defines
e
s 00000/00073/00811
d D 5.2 88/07/21 19:10:07 bostic 2 1
c rip out SHELL_ESCAPE define
e
s 00884/00000/00000
d D 5.1 88/07/21 18:52:37 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 24
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
D 6
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 6
D 20
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 6
 * by the University of California, Berkeley.  The name of the
E 6
I 6
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 6
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 20
I 20
 * %sccs.include.redist.c%
E 20
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 15
/*
 * User-level command processor.
 */

E 15
D 10
#include "less.h"
#include "position.h"
#include "cmd.h"
E 10
I 10
#include <sys/param.h>
#include <stdio.h>
#include <ctype.h>
#include <less.h>
I 18
#include "pathnames.h"
E 18
E 10

#define	NO_MCA		0
#define	MCA_DONE	1
#define	MCA_MORE	2

D 10
extern int erase_char, kill_char;
E 10
I 10
extern int erase_char, kill_char, werase_char;
E 10
extern int ispipe;
extern int sigs;
extern int quit_at_eof;
extern int hit_eof;
extern int sc_width;
extern int sc_height;
extern int sc_window;
extern int curr_ac;
extern int ac;
extern int quitting;
extern int scroll;
D 10
extern char *first_cmd;
extern char *every_first_cmd;
D 7
extern char version[];
E 7
extern char *current_file;
E 10
D 3
#if EDITOR
E 3
D 9
extern char *editor;
E 9
D 3
#endif
E 3
extern int screen_trashed;	/* The screen has been overwritten */

static char cmdbuf[120];	/* Buffer for holding a multi-char command */
D 2
#if SHELL_ESCAPE
static char *shellcmd = NULL;	/* For holding last shell command for "!!" */
#endif
E 2
static char *cp;		/* Pointer into cmdbuf */
static int cmd_col;		/* Current column of the multi-char command */
I 10
static int longprompt;		/* if stat command instead of prompt */
E 10
static int mca;			/* The multicharacter command (action) */
static int last_mca;		/* The previous mca */
static int number;		/* The number typed by the user */
static int wsearch;		/* Search for matches (1) or non-matches (0) */

D 15
/*
 * Reset command buffer (to empty).
 */
cmd_reset()
{
	cp = cmdbuf;
}
E 15
I 15
#define	CMD_RESET	cp = cmdbuf	/* reset command buffer to empty */
#define	CMD_EXEC	lower_left(); flush()
E 15

D 15
/*
 * Backspace in command buffer.
 */
E 15
I 15
/* backspace in command buffer. */
E 15
D 10
	static int
E 10
I 10
static
E 10
cmd_erase()
{
I 15
	/*
	 * backspace past beginning of the string: this usually means
	 * abort the command.
	 */
E 15
	if (cp == cmdbuf)
D 15
		/*
		 * Backspace past beginning of the string:
		 * this usually means abort the command.
		 */
E 15
D 10
		return (1);
E 10
I 10
		return(1);
E 10

I 15
	/* erase an extra character, for the carat. */
E 15
D 10
	if (control_char(*--cp))
	{
E 10
I 10
	if (CONTROL_CHAR(*--cp)) {
E 10
D 15
		/*
		 * Erase an extra character, for the carat.
		 */
E 15
		backspace();
D 10
		cmd_col--;
E 10
I 10
		--cmd_col;
E 10
	}
I 15

E 15
	backspace();
D 10
	cmd_col--;
	return (0);
E 10
I 10
	--cmd_col;
	return(0);
E 10
}

D 15
/*
 * Set up the display to start a new multi-character command.
 */
E 15
I 15
/* set up the display to start a new multi-character command. */
E 15
start_mca(action, prompt)
	int action;
	char *prompt;
{
	lower_left();
	clear_eol();
	putstr(prompt);
	cmd_col = strlen(prompt);
	mca = action;
}

/*
D 15
 * Process a single character of a multi-character command, such as
E 15
I 15
 * process a single character of a multi-character command, such as
E 15
 * a number, or the pattern of a search command.
 */
D 10
	static int
E 10
I 10
static
E 10
cmd_char(c)
	int c;
{
	if (c == erase_char)
D 10
	{
		if (cmd_erase())
			return (1);
	} else if (c == kill_char)
	{
		/* {{ Could do this faster, but who cares? }} */
		while (cmd_erase() == 0)
			;
	} else if (cp >= &cmdbuf[sizeof(cmdbuf)-1])
	{
		/*
		 * No room in the command buffer.
		 */
E 10
I 10
		return(cmd_erase());
	/* in this order, in case werase == erase_char */
	if (c == werase_char) {
		if (cp > cmdbuf) {
			while (isspace(cp[-1]) && !cmd_erase());
			while (!isspace(cp[-1]) && !cmd_erase());
			while (isspace(cp[-1]) && !cmd_erase());
		}
		return(cp == cmdbuf);
	}
	if (c == kill_char) {
		while (!cmd_erase());
		return(1);
	}
	/*
	 * No room in the command buffer, or no room on the screen;
	 * {{ Could get fancy here; maybe shift the displayed line
	 * and make room for more chars, like ksh. }}
	 */
	if (cp >= &cmdbuf[sizeof(cmdbuf)-1] || cmd_col >= sc_width-3)
E 10
		bell();
D 10
	} else if (cmd_col >= sc_width-3)
	{
		/*
		 * No room on the screen.
		 * {{ Could get fancy here; maybe shift the displayed
		 *    line and make room for more chars, like ksh. }}
		 */
		bell();
	} else
	{
		/*
		 * Append the character to the string.
		 */
E 10
I 10
	else {
E 10
		*cp++ = c;
D 10
		if (control_char(c))
		{
E 10
I 10
		if (CONTROL_CHAR(c)) {
E 10
			putchr('^');
			cmd_col++;
D 10
			c = carat_char(c);
E 10
I 10
			c = CARAT_CHAR(c);
E 10
		}
		putchr(c);
		cmd_col++;
	}
D 10
	return (0);
E 10
I 10
	return(0);
E 10
}

D 15
/*
 * Return the number currently in the command buffer.
 */
	static int
cmd_int()
{
	*cp = '\0';
	cp = cmdbuf;
	return (atoi(cmdbuf));
}

/*
 * Move the cursor to lower left before executing a command.
 * This looks nicer if the command takes a long time before
 * updating the screen.
 */
D 10
	static void
E 10
I 10
static
E 10
cmd_exec()
{
	lower_left();
	flush();
}

E 15
D 10
/*
 * Display the appropriate prompt.
 */
	static void
E 10
prompt()
{
D 10
	register char *p;
E 10
I 10
D 15
	extern int terseprompt, linenums;
E 15
I 15
D 17
	extern int linenums;
E 17
I 17
	extern int linenums, short_file;
E 17
E 15
D 13
	extern char *current_name, *firstsearch;
E 13
I 13
	extern char *current_name, *firstsearch, *next_name;
E 13
	off_t len, pos, ch_length(), position(), forw_line();
	char pbuf[40];
E 10

D 10
	if (first_cmd != NULL && *first_cmd != '\0')
	{
		/*
		 * No prompt necessary if commands are from first_cmd
		 * rather than from the user.
		 */
		return;
	}

E 10
	/*
D 10
	 * If nothing is displayed yet, display starting from line 1.
E 10
I 10
	 * if nothing is displayed yet, display starting from line 1;
	 * if search string provided, go there instead.
E 10
	 */
D 10
	if (position(TOP) == NULL_POSITION)
		jump_back(1);
E 10
I 10
	if (position(TOP) == NULL_POSITION) {
		if (forw_line((off_t)0) == NULL_POSITION)
			return(0);
		if (!firstsearch || !search(1, firstsearch, 1, 1))
			jump_back(1);
	}
E 10
	else if (screen_trashed)
		repaint();

D 10
	/*
	 * If the -E flag is set and we've hit EOF on the last file, quit.
	 */
	if (quit_at_eof == 2 && hit_eof && curr_ac + 1 >= ac)
E 10
I 10
	/* if no -e flag and we've hit EOF on the last file, quit. */
D 17
	if (!quit_at_eof && hit_eof && curr_ac + 1 >= ac)
E 17
I 17
	if ((!quit_at_eof || short_file) && hit_eof && curr_ac + 1 >= ac)
E 17
E 10
		quit();

D 10
	/*
	 * Select the proper prompt and display it.
	 */
E 10
I 10
	/* select the proper prompt and display it. */
E 10
	lower_left();
	clear_eol();
D 10
	p = pr_string();
	if (p == NULL)
E 10
I 10
	if (longprompt) {
		so_enter();
		putstr(current_name);
		putstr(":");
		if (!ispipe) {
			(void)sprintf(pbuf, " file %d/%d", curr_ac + 1, ac);
			putstr(pbuf);
		}
		if (linenums) {
D 11
			(void)sprintf(pbuf, " line %d", currline(TOP));
E 11
I 11
			(void)sprintf(pbuf, " line %d", currline(BOTTOM));
E 11
			putstr(pbuf);
		}
D 11
		if ((pos = position(TOP)) != NULL_POSITION) {
E 11
I 11
		if ((pos = position(BOTTOM)) != NULL_POSITION) {
E 11
D 22
			(void)sprintf(pbuf, " byte %ld", pos);
E 22
I 22
			(void)sprintf(pbuf, " byte %qd", pos);
E 22
			putstr(pbuf);
			if (!ispipe && (len = ch_length())) {
D 11
				(void)sprintf(pbuf, " pct %ld%%",
				    ((100 * pos) / len));
E 11
I 11
D 22
				(void)sprintf(pbuf, "/%ld pct %ld%%",
E 22
I 22
				(void)sprintf(pbuf, "/%qd pct %qd%%",
E 22
				    len, ((100 * pos) / len));
E 11
				putstr(pbuf);
			}
		}
		so_exit();
		longprompt = 0;
	}
D 15
	else if (terseprompt)
E 10
		putchr(':');
E 15
D 10
	else
	{
E 10
I 10
	else {
E 10
		so_enter();
D 10
		putstr(p);
E 10
I 10
		putstr(current_name);
		if (hit_eof)
D 13
			putstr(": END");
E 13
I 13
			if (next_name) {
D 15
				(void)sprintf(pbuf, ": END (%s)", next_name);
E 15
I 15
D 19
				(void)sprintf(pbuf, ": END (next file: %s)",
				    next_name);
E 15
				putstr(pbuf);
E 19
I 19
				putstr(": END (next file: ");
				putstr(next_name);
				putstr(")");
E 19
			}
			else
				putstr(": END");
E 13
D 16
		else if (linenums) {
			(void)sprintf(pbuf, ": %d", currline(TOP));
E 16
I 16
		else if (!ispipe &&
		    (pos = position(BOTTOM)) != NULL_POSITION &&
		    (len = ch_length())) {
D 22
			(void)sprintf(pbuf, " (%ld%%)", ((100 * pos) / len));
E 22
I 22
			(void)sprintf(pbuf, " (%qd%%)", ((100 * pos) / len));
E 22
E 16
			putstr(pbuf);
		}
E 10
		so_exit();
	}
I 10
	return(1);
E 10
}

D 15
/*
 * Get command character.
D 10
 * The character normally comes from the keyboard,
 * but may come from the "first_cmd" string.
E 10
 */
E 15
I 15
/* get command character. */
E 15
D 10
	static int
E 10
I 10
static
E 10
getcc()
{
I 12
	extern int cmdstack;
	int ch;
I 23
	off_t position();
E 23

	/* left over from error() routine. */
	if (cmdstack) {
		ch = cmdstack;
		cmdstack = NULL;
		return(ch);
	}
E 12
D 10
	if (first_cmd == NULL)
		return (getchr());

	if (*first_cmd == '\0')
	{
E 10
I 10
	if (cp > cmdbuf && position(TOP) == NULL_POSITION) {
E 10
		/*
D 10
		 * Reached end of first_cmd input.
E 10
I 10
		 * Command is incomplete, so try to complete it.
		 * There are only two cases:
		 * 1. We have "/string" but no newline.  Add the \n.
		 * 2. We have a number but no command.  Treat as #g.
		 * (This is all pretty hokey.)
E 10
		 */
D 10
		first_cmd = NULL;
		if (cp > cmdbuf && position(TOP) == NULL_POSITION)
		{
			/*
			 * Command is incomplete, so try to complete it.
			 * There are only two cases:
			 * 1. We have "/string" but no newline.  Add the \n.
			 * 2. We have a number but no command.  Treat as #g.
			 * (This is all pretty hokey.)
			 */
			if (mca != A_DIGIT)
				/* Not a number; must be search string */
				return ('\n'); 
			else
				/* A number; append a 'g' */
				return ('g');
		}
		return (getchr());
E 10
I 10
		if (mca != A_DIGIT)
			/* Not a number; must be search string */
			return('\n');
		else
			/* A number; append a 'g' */
			return('g');
E 10
	}
D 10
	return (*first_cmd++);
E 10
I 10
	return(getchr());
E 10
}

D 15
/*
 * Execute a multicharacter command.
 */
E 15
I 15
/* execute a multicharacter command. */
E 15
D 10
	static void
E 10
I 10
static
E 10
exec_mca()
{
I 10
	extern int file;
	extern char *tagfile;
E 10
	register char *p;
I 10
	char *glob();
E 10
D 4
	register int n;
E 4

	*cp = '\0';
D 15
	cmd_exec();
E 15
I 15
	CMD_EXEC;
E 15
D 10
	switch (mca)
	{
E 10
I 10
	switch (mca) {
E 10
	case A_F_SEARCH:
D 10
		search(1, cmdbuf, number, wsearch);
E 10
I 10
		(void)search(1, cmdbuf, number, wsearch);
E 10
		break;
	case A_B_SEARCH:
D 10
		search(0, cmdbuf, number, wsearch);
E 10
I 10
		(void)search(0, cmdbuf, number, wsearch);
E 10
		break;
D 10
	case A_FIRSTCMD:
		/*
		 * Skip leading spaces or + signs in the string.
		 */
		for (p = cmdbuf;  *p == '+' || *p == ' ';  p++)
			;
		if (every_first_cmd != NULL)
			free(every_first_cmd);
		if (*p == '\0')
			every_first_cmd = NULL;
		else
			every_first_cmd = save(p);
		break;
	case A_TOGGLE_OPTION:
		toggle_option(cmdbuf, 1);
		break;
E 10
	case A_EXAMINE:
D 10
		/*
		 * Ignore leading spaces in the filename.
		 */
		for (p = cmdbuf;  *p == ' ';  p++)
			;
		edit(glob(p));
E 10
I 10
		for (p = cmdbuf; isspace(*p); ++p);
		(void)edit(glob(p));
E 10
		break;
I 10
	case A_TAGFILE:
		for (p = cmdbuf; isspace(*p); ++p);
		findtag(p);
		if (tagfile == NULL)
			break;
		if (edit(tagfile))
			(void)tagsearch();
		break;
E 10
D 2
#if SHELL_ESCAPE
	case A_SHELL:
		/*
		 * !! just uses whatever is in shellcmd.
		 * Otherwise, copy cmdbuf to shellcmd,
		 * replacing any '%' with the current
		 * file name.
		 */
		if (*cmdbuf != '!')
		{
			register char *fr, *to;

			/*
			 * Make one pass to see how big a buffer we 
			 * need to allocate for the expanded shell cmd.
			 */
			for (fr = cmdbuf;  *fr != '\0';  fr++)
				if (*fr == '%')
					n += strlen(current_file);
				else
					n++;

			if (shellcmd != NULL)
				free(shellcmd);
			shellcmd = calloc(n+1, sizeof(char));
			if (shellcmd == NULL)
			{
				error("cannot allocate memory");
				break;
			}

			/*
			 * Now copy the shell cmd, expanding any "%"
			 * into the current filename.
			 */
			to = shellcmd;
			for (fr = cmdbuf;  *fr != '\0';  fr++)
			{
				if (*fr != '%')
					*to++ = *fr;
				else
				{
					strcpy(to, current_file);
					to += strlen(to);
				}
			}
			*to = '\0';
		}

		if (shellcmd == NULL)
			lsystem("");
		else
			lsystem(shellcmd);
		error("!done");
		break;
#endif
E 2
	}
}

D 15
/*
 * Add a character to a multi-character command.
 */
E 15
I 15
/* add a character to a multi-character command. */
E 15
D 10
	static int
E 10
I 10
static
E 10
mca_char(c)
	int c;
{
D 10
	switch (mca)
	{
	case 0:
		/*
		 * Not in a multicharacter command.
		 */
		return (NO_MCA);

	case A_PREFIX:
		/*
		 * In the prefix of a command.
		 */
		return (NO_MCA);

E 10
I 10
	switch (mca) {
	case 0:			/* not in a multicharacter command. */
	case A_PREFIX:		/* in the prefix of a command. */
		return(NO_MCA);
E 10
	case A_DIGIT:
		/*
		 * Entering digits of a number.
		 * Terminated by a non-digit.
		 */
D 10
		if ((c < '0' || c > '9') &&
			c != erase_char && c != kill_char)
		{
E 10
I 10
		if (!isascii(c) || !isdigit(c) &&
		    c != erase_char && c != kill_char && c != werase_char) {
E 10
			/*
			 * Not part of the number.
			 * Treat as a normal command character.
			 */
D 15
			number = cmd_int();
E 15
I 15
			*cp = '\0';
			number = atoi(cmdbuf);
			CMD_RESET;
E 15
			mca = 0;
D 10
			return (NO_MCA);
E 10
I 10
			return(NO_MCA);
E 10
		}
		break;
D 10

	case A_TOGGLE_OPTION:
		/*
		 * Special case for the TOGGLE_OPTION command.
		 * if the option letter which was entered is a
		 * single-char option, execute the command immediately,
		 * so he doesn't have to hit RETURN.
		 */
		if (cp == cmdbuf && c != erase_char && c != kill_char &&
		    single_char_option(c))
		{
			cmdbuf[0] = c;
			cmdbuf[1] = '\0';
			toggle_option(cmdbuf, 1);
			return (MCA_DONE);
		}
		break;
E 10
	}

	/*
	 * Any other multicharacter command
	 * is terminated by a newline.
	 */
D 10
	if (c == '\n' || c == '\r')
	{
E 10
I 10
	if (c == '\n' || c == '\r') {
E 10
D 15
		/*
		 * Execute the command.
		 */
E 15
		exec_mca();
D 10
		return (MCA_DONE);
E 10
I 10
		return(MCA_DONE);
E 10
	}
D 15
	/*
	 * Append the char to the command buffer.
	 */
E 15
I 15

	/* append the char to the command buffer. */
E 15
	if (cmd_char(c))
D 15
		/*
		 * Abort the multi-char command.
		 */
E 15
D 10
		return (MCA_DONE);
E 10
I 10
		return(MCA_DONE);
E 10
D 15
	/*
	 * Need another character.
	 */
E 15
I 15

E 15
D 10
	return (MCA_MORE);
E 10
I 10
	return(MCA_MORE);
E 10
}

/*
 * Main command processor.
 * Accept and execute commands until a quit command, then return.
 */
D 10
	public void
E 10
commands()
{
	register int c;
	register int action;

	last_mca = 0;
	scroll = (sc_height + 1) / 2;

D 10
	for (;;)
	{
E 10
I 10
	for (;;) {
E 10
		mca = 0;
		number = 0;

		/*
		 * See if any signals need processing.
		 */
D 10
		if (sigs)
		{
E 10
I 10
		if (sigs) {
E 10
			psignals();
			if (quitting)
				quit();
		}
D 8
			
E 8
		/*
		 * Display prompt and accept a character.
		 */
D 15
		cmd_reset();
E 15
I 15
		CMD_RESET;
E 15
D 10
		prompt();
E 10
I 10
		if (!prompt()) {
			next_file(1);
			continue;
		}
E 10
		noprefix();
		c = getcc();

D 8
	again:
		if (sigs)
E 8
I 8
again:		if (sigs)
E 8
			continue;

		/*
		 * If we are in a multicharacter command, call mca_char.
		 * Otherwise we call cmd_decode to determine the
		 * action to be performed.
		 */
		if (mca)
D 10
			switch (mca_char(c))
			{
E 10
I 10
			switch (mca_char(c)) {
E 10
			case MCA_MORE:
				/*
				 * Need another character.
				 */
				c = getcc();
				goto again;
			case MCA_DONE:
				/*
				 * Command has been handled by mca_char.
				 * Start clean with a prompt.
				 */
				continue;
			case NO_MCA:
				/*
				 * Not a multi-char command
				 * (at least, not anymore).
				 */
				break;
			}

D 15
		/*
		 * Decode the command character and decide what to do.
		 */
		switch (action = cmd_decode(c))
		{
		case A_DIGIT:
			/*
			 * First digit of a number.
			 */
E 15
I 15
		/* decode the command character and decide what to do. */
		switch (action = cmd_decode(c)) {
		case A_DIGIT:		/* first digit of a number */
E 15
			start_mca(A_DIGIT, ":");
			goto again;
D 15

		case A_F_SCREEN:
			/*
			 * Forward one screen.
			 */
			if (number <= 0)
				number = sc_window;
			if (number <= 0)
E 15
I 15
		case A_F_SCREEN:	/* forward one screen */
			CMD_EXEC;
			if (number <= 0 && (number = sc_window) <= 0)
E 15
				number = sc_height - 1;
D 15
			cmd_exec();
E 15
			forward(number, 1);
			break;
D 15

		case A_B_SCREEN:
			/*
			 * Backward one screen.
			 */
			if (number <= 0)
				number = sc_window;
			if (number <= 0)
E 15
I 15
		case A_B_SCREEN:	/* backward one screen */
			CMD_EXEC;
			if (number <= 0 && (number = sc_window) <= 0)
E 15
				number = sc_height - 1;
D 15
			cmd_exec();
E 15
			backward(number, 1);
			break;
D 15

		case A_F_LINE:
			/*
			 * Forward N (default 1) line.
			 */
			if (number <= 0)
				number = 1;
			cmd_exec();
			forward(number, 0);
E 15
I 15
		case A_F_LINE:		/* forward N (default 1) line */
			CMD_EXEC;
			forward(number <= 0 ? 1 : number, 0);
E 15
			break;
D 15

		case A_B_LINE:
			/*
			 * Backward N (default 1) line.
			 */
			if (number <= 0)
				number = 1;
			cmd_exec();
			backward(number, 0);
E 15
I 15
		case A_B_LINE:		/* backward N (default 1) line */
			CMD_EXEC;
			backward(number <= 0 ? 1 : number, 0);
E 15
			break;
D 15

		case A_F_SCROLL:
			/*
			 * Forward N lines 
			 * (default same as last 'd' or 'u' command).
			 */
E 15
I 15
		case A_F_SCROLL:	/* forward N lines */
			CMD_EXEC;
E 15
			if (number > 0)
				scroll = number;
D 15
			cmd_exec();
E 15
			forward(scroll, 0);
			break;
D 15

		case A_B_SCROLL:
			/*
			 * Forward N lines 
			 * (default same as last 'd' or 'u' command).
			 */
E 15
I 15
		case A_B_SCROLL:	/* backward N lines */
			CMD_EXEC;
E 15
			if (number > 0)
				scroll = number;
D 15
			cmd_exec();
E 15
			backward(scroll, 0);
			break;
D 15

		case A_FREPAINT:
			/*
			 * Flush buffers, then repaint screen.
			 * Don't flush the buffers on a pipe!
			 */
			if (!ispipe)
			{
E 15
I 15
		case A_FREPAINT:	/* flush buffers and repaint */
			if (!ispipe) {
E 15
				ch_init(0, 0);
				clr_linenum();
			}
D 15
			/* FALLTHRU */
D 14
		case A_REPAINT:
			/*
			 * Repaint screen.
			 */
E 14
I 14

E 15
I 15
			/* FALLTHROUGH */
E 15
		case A_REPAINT:		/* repaint the screen */
E 14
D 15
			cmd_exec();
E 15
I 15
			CMD_EXEC;
E 15
			repaint();
			break;
D 15

		case A_GOLINE:
			/*
			 * Go to line N, default beginning of file.
			 */
E 15
I 15
		case A_GOLINE:		/* go to line N, default 1 */
			CMD_EXEC;
E 15
			if (number <= 0)
				number = 1;
D 15
			cmd_exec();
E 15
			jump_back(number);
			break;
D 15

		case A_PERCENT:
			/*
			 * Go to a specified percentage into the file.
			 */
E 15
I 15
		case A_PERCENT:		/* go to percent of file */
			CMD_EXEC;
E 15
			if (number < 0)
				number = 0;
D 15
			if (number > 100)
E 15
I 15
			else if (number > 100)
E 15
				number = 100;
D 15
			cmd_exec();
E 15
			jump_percent(number);
			break;
D 15

		case A_GOEND:
			/*
			 * Go to line N, default end of file.
			 */
			cmd_exec();
E 15
I 15
		case A_GOEND:		/* go to line N, default end */
			CMD_EXEC;
E 15
			if (number <= 0)
				jump_forw();
			else
				jump_back(number);
			break;
D 15

E 15
D 10
		case A_STAT:
			/*
			 * Print file name, etc.
			 */
			cmd_exec();
D 8
			error(eq_message());
			break;
			
E 8
I 8
			lower_left();
			clear_eol();
			putstr(eq_message());
			lower_left();
			c = getcc();
			goto again;
E 8
D 7
		case A_VERSION:
			/*
			 * Print version number, without the "@(#)".
			 */
			cmd_exec();
			error(version+4);
			break;

E 7
		case A_QUIT:
			/*
			 * Exit.
			 */
E 10
I 10
		case A_STAT:		/* print file name, etc. */
			longprompt = 1;
			continue;
D 15

E 15
		case A_QUIT:		/* exit */
E 10
			quit();
D 15

		case A_F_SEARCH:
E 15
I 15
		case A_F_SEARCH:	/* search for a pattern */
E 15
		case A_B_SEARCH:
D 15
			/*
			 * Search for a pattern.
			 * Accept chars of the pattern until \n.
			 */
E 15
			if (number <= 0)
				number = 1;
			start_mca(action, (action==A_F_SEARCH) ? "/" : "?");
			last_mca = mca;
			wsearch = 1;
			c = getcc();
D 10
			if (c == '!')
			{
E 10
I 10
			if (c == '!') {
E 10
				/*
D 15
				 * Invert the sense of the search.
				 * Set wsearch to 0 and get a new
				 * character for the start of the pattern.
E 15
I 15
				 * Invert the sense of the search; set wsearch
				 * to 0 and get a new character for the start
				 * of the pattern.
E 15
				 */
				start_mca(action, 
D 15
					(action==A_F_SEARCH) ? "!/" : "!?");
E 15
I 15
				    (action == A_F_SEARCH) ? "!/" : "!?");
E 15
				wsearch = 0;
				c = getcc();
			}
			goto again;
D 15

		case A_AGAIN_SEARCH:
			/*
			 * Repeat previous search.
			 */
E 15
I 15
		case A_AGAIN_SEARCH:		/* repeat previous search */
E 15
			if (number <= 0)
				number = 1;
			if (wsearch)
				start_mca(last_mca, 
D 15
					(last_mca==A_F_SEARCH) ? "/" : "?");
E 15
I 15
				    (last_mca == A_F_SEARCH) ? "/" : "?");
E 15
			else
				start_mca(last_mca, 
D 15
					(last_mca==A_F_SEARCH) ? "!/" : "!?");
			cmd_exec();
E 15
I 15
				    (last_mca == A_F_SEARCH) ? "!/" : "!?");
			CMD_EXEC;
E 15
D 10
			search(mca==A_F_SEARCH, (char *)NULL, number, wsearch);
E 10
I 10
			(void)search(mca == A_F_SEARCH, (char *)NULL,
			    number, wsearch);
E 10
			break;
D 15

		case A_HELP:
			/*
			 * Help.
			 */
E 15
I 15
		case A_HELP:			/* help */
E 15
			lower_left();
			clear_eol();
			putstr("help");
D 15
			cmd_exec();
E 15
I 15
			CMD_EXEC;
E 15
			help();
			break;
D 15

D 10
		case A_EXAMINE:
			/*
			 * Edit a new file.  Get the filename.
			 */
E 10
I 10
		case A_TAGFILE:		/* tag a new file; get the file name */
E 10
			cmd_reset();
E 15
I 15
		case A_TAGFILE:			/* tag a new file */
			CMD_RESET;
E 15
I 10
			start_mca(A_TAGFILE, "Tag: ");
			c = getcc();
			goto again;
D 15

I 14
		case A_FILE_LIST:	/* show list of file names */
			cmd_exec();
E 15
I 15
		case A_FILE_LIST:		/* show list of file names */
			CMD_EXEC;
E 15
			showlist();
			repaint();
			break;
D 15

E 14
		case A_EXAMINE:		/* edit a new file; get the file name */
			cmd_reset();
E 15
I 15
		case A_EXAMINE:			/* edit a new file */
			CMD_RESET;
E 15
E 10
			start_mca(A_EXAMINE, "Examine: ");
			c = getcc();
			goto again;
D 10
			
E 10
I 10
D 15

E 10
		case A_VISUAL:
			/*
			 * Invoke an editor on the input file.
			 */
D 3
#if EDITOR
E 3
			if (ispipe)
			{
E 15
I 15
		case A_VISUAL:			/* invoke the editor */
			if (ispipe) {
E 15
				error("Cannot edit standard input");
				break;
			}
D 9
			/*
			 * Try to pass the line number to the editor.
			 */
E 9
D 15
			cmd_exec();
E 15
I 15
			CMD_EXEC;
E 15
D 9
			c = currline(MIDDLE);
			if (c == 0)
D 5
				sprintf(cmdbuf, "%s %s",
E 5
I 5
				(void)sprintf(cmdbuf, "%s %s",
E 5
					editor, current_file);
			else
D 5
				sprintf(cmdbuf, "%s +%d %s",
E 5
I 5
				(void)sprintf(cmdbuf, "%s +%d %s",
E 5
					editor, c, current_file);
			lsystem(cmdbuf);
E 9
I 9
			editfile();
E 9
			ch_init(0, 0);
			clr_linenum();
			break;
D 3
#else
			error("Command not available");
			break;
#endif
E 3
D 15

		case A_NEXT_FILE:
			/*
			 * Examine next file.
			 */
E 15
I 15
		case A_NEXT_FILE:		/* examine next file */
E 15
			if (number <= 0)
				number = 1;
			next_file(number);
			break;
D 15

		case A_PREV_FILE:
			/*
			 * Examine previous file.
			 */
E 15
I 15
		case A_PREV_FILE:		/* examine previous file */
E 15
			if (number <= 0)
				number = 1;
			prev_file(number);
			break;
D 15

D 10
		case A_TOGGLE_OPTION:
			/*
			 * Toggle a flag setting.
			 */
			cmd_reset();
			start_mca(A_TOGGLE_OPTION, "-");
			c = getcc();
			goto again;

		case A_DISP_OPTION:
			/*
			 * Report a flag setting.
			 */
			cmd_reset();
			start_mca(A_DISP_OPTION, "_");
			c = getcc();
			if (c == erase_char || c == kill_char)
				break;
			cmdbuf[0] = c;
			cmdbuf[1] = '\0';
			toggle_option(cmdbuf, 0);
			break;

		case A_FIRSTCMD:
			/*
			 * Set an initial command for new files.
			 */
			cmd_reset();
			start_mca(A_FIRSTCMD, "+");
			c = getcc();
			goto again;
D 2

		case A_SHELL:
			/*
			 * Shell escape.
			 */
#if SHELL_ESCAPE
			cmd_reset();
			start_mca(A_SHELL, "!");
			c = getcc();
			goto again;
#else
			error("Command not available");
			break;
#endif
E 2

E 10
		case A_SETMARK:
			/*
			 * Set a mark.
			 */
E 15
I 15
		case A_SETMARK:			/* set a mark */
E 15
			lower_left();
			clear_eol();
			start_mca(A_SETMARK, "mark: ");
			c = getcc();
			if (c == erase_char || c == kill_char)
				break;
			setmark(c);
			break;
D 15

		case A_GOMARK:
			/*
			 * Go to a mark.
			 */
E 15
I 15
		case A_GOMARK:			/* go to mark */
E 15
			lower_left();
			clear_eol();
			start_mca(A_GOMARK, "goto mark: ");
			c = getcc();
			if (c == erase_char || c == kill_char)
				break;
			gomark(c);
			break;
D 15

E 15
		case A_PREFIX:
			/*
			 * The command is incomplete (more chars are needed).
D 15
			 * Display the current char so the user knows
			 * what's going on and get another character.
E 15
I 15
			 * Display the current char so the user knows what's
			 * going on and get another character.
E 15
			 */
			if (mca != A_PREFIX)
D 15
				start_mca(A_PREFIX, "& ");
D 10
			if (control_char(c))
E 10
I 10
			if (CONTROL_CHAR(c))
E 10
			{
E 15
I 15
				start_mca(A_PREFIX, "");
			if (CONTROL_CHAR(c)) {
E 15
				putchr('^');
D 10
				c = carat_char(c);
E 10
I 10
				c = CARAT_CHAR(c);
E 10
			}
			putchr(c);
			c = getcc();
			goto again;
D 15

E 15
		default:
			bell();
			break;
		}
	}
I 9
}

D 21
static
E 21
editfile()
{
I 10
	extern char *current_file;
E 10
	static int dolinenumber;
	static char *editor;
	int c;
D 10
	char buf[MAXPATHLEN], *getenv();
E 10
I 10
	char buf[MAXPATHLEN * 2 + 20], *getenv();
E 10

	if (editor == NULL) {
		editor = getenv("EDITOR");
		/* pass the line number to vi */
		if (editor == NULL || *editor == '\0') {
D 10
			editor = "/usr/ucb/vi";
E 10
I 10
D 18
#define	EDIT_PGM	"/usr/ucb/vi"
			editor = EDIT_PGM;
E 18
I 18
			editor = _PATH_VI;
E 18
E 10
			dolinenumber = 1;
		}
		else
			dolinenumber = 0;
	}
	if (dolinenumber && (c = currline(MIDDLE)))
		(void)sprintf(buf, "%s +%d %s", editor, c, current_file);
	else
		(void)sprintf(buf, "%s %s", editor, current_file);
	lsystem(buf);
I 14
}

D 21
static
E 21
showlist()
{
	extern int sc_width;
	extern char **av;
	register int indx, width;
	int len;
	char *p;

	if (ac <= 0) {
		error("No files provided as arguments.");
		return;
	}
	for (width = indx = 0; indx < ac;) {
		p = strcmp(av[indx], "-") ? av[indx] : "stdin";
		len = strlen(p) + 1;
		if (curr_ac == indx)
			len += 2;
		if (width + len + 1 >= sc_width) {
			if (!width) {
				if (curr_ac == indx)
					putchr('[');
				putstr(p);
				if (curr_ac == indx)
					putchr(']');
				++indx;
			}
			width = 0;
			putchr('\n');
			continue;
		}
		if (width)
			putchr(' ');
		if (curr_ac == indx)
			putchr('[');
		putstr(p);
		if (curr_ac == indx)
			putchr(']');
		width += len;
		++indx;
	}
	putchr('\n');
	error((char *)NULL);
E 14
E 9
}
E 1
