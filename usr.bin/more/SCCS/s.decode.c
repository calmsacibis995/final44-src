h16842
s 00002/00002/00173
d D 8.1 93/06/06 15:36:15 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00175
d D 5.9 91/03/01 15:12:06 bostic 9 8
c ANSI
e
s 00001/00012/00175
d D 5.8 90/06/01 17:03:39 bostic 8 7
c new copyright notice
e
s 00001/00000/00186
d D 5.7 88/12/06 15:16:34 bostic 7 6
c add ":a[rgs]" command from vi
e
s 00034/00126/00152
d D 5.6 88/11/22 16:51:20 bostic 6 5
c less -> more
e
s 00000/00001/00278
d D 5.5 88/09/23 14:15:52 bostic 5 4
c remove version command
e
s 00002/00004/00277
d D 5.4 88/07/25 12:04:36 bostic 4 3
c update copyright notice
e
s 00003/00007/00278
d D 5.3 88/07/22 12:04:07 bostic 3 2
c allocate space on stack, don't malloc it; lint cleanups
e
s 00000/00004/00285
d D 5.2 88/07/21 19:14:26 bostic 2 1
c rip out USERFILE, make default
e
s 00289/00000/00000
d D 5.1 88/07/21 18:52:39 bostic 1 0
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
 * Routines to decode user commands.
 *
 * This is all table driven.
 * A command table is a sequence of command descriptors.
 * Each command descriptor is a sequence of bytes with the following format:
 *	<c1><c2>...<cN><0><action>
 * The characters c1,c2,...,cN are the command string; that is,
 * the characters which the user must type.
 * It is terminated by a null <0> byte.
 * The byte after the null byte is the action code associated
 * with the command string.
 *
 * The default commands are described by cmdtable.
D 6
 * User-defined commands are read into usertable.
E 6
 */

D 6
#include "less.h"
#include "cmd.h"
E 6
I 6
#include <sys/param.h>
#include <sys/file.h>
#include <stdio.h>
#include <less.h>
E 6

/*
 * Command table is ordered roughly according to expected
 * frequency of use, so the common commands are near the beginning.
 */
D 6
static char cmdtable[] =
{
E 6
I 6
#define	CONTROL(c)		((c)&037)

static char cmdtable[] = {
E 6
	'\r',0,				A_F_LINE,
	'\n',0,				A_F_LINE,
D 6
	'e',0,				A_F_LINE,
E 6
	'j',0,				A_F_LINE,
D 6
	CONTROL('E'),0,			A_F_LINE,
	CONTROL('N'),0,			A_F_LINE,
E 6
	'k',0,				A_B_LINE,
D 6
	'y',0,				A_B_LINE,
	CONTROL('Y'),0,			A_B_LINE,
	CONTROL('K'),0,			A_B_LINE,
	CONTROL('P'),0,			A_B_LINE,
E 6
	'd',0,				A_F_SCROLL,
	CONTROL('D'),0,			A_F_SCROLL,
	'u',0,				A_B_SCROLL,
	CONTROL('U'),0,			A_B_SCROLL,
	' ',0,				A_F_SCREEN,
	'f',0,				A_F_SCREEN,
	CONTROL('F'),0,			A_F_SCREEN,
D 6
	CONTROL('V'),0,			A_F_SCREEN,
E 6
	'b',0,				A_B_SCREEN,
	CONTROL('B'),0,			A_B_SCREEN,
D 6
	CONTROL('['),'v',0,		A_B_SCREEN,
E 6
	'R',0,				A_FREPAINT,
	'r',0,				A_REPAINT,
D 6
	CONTROL('R'),0,			A_REPAINT,
E 6
	CONTROL('L'),0,			A_REPAINT,
	'g',0,				A_GOLINE,
D 6
	'<',0,				A_GOLINE,
	CONTROL('['),'<',0,		A_GOLINE,
E 6
	'p',0,				A_PERCENT,
	'%',0,				A_PERCENT,
	'G',0,				A_GOEND,
D 6
	CONTROL('['),'>',0,		A_GOEND,
	'>',0,				A_GOEND,

E 6
	'0',0,				A_DIGIT,
	'1',0,				A_DIGIT,
	'2',0,				A_DIGIT,
	'3',0,				A_DIGIT,
	'4',0,				A_DIGIT,
	'5',0,				A_DIGIT,
	'6',0,				A_DIGIT,
	'7',0,				A_DIGIT,
	'8',0,				A_DIGIT,
	'9',0,				A_DIGIT,

	'=',0,				A_STAT,
	CONTROL('G'),0,			A_STAT,
	'/',0,				A_F_SEARCH,
	'?',0,				A_B_SEARCH,
	'n',0,				A_AGAIN_SEARCH,
	'm',0,				A_SETMARK,
	'\'',0,				A_GOMARK,
D 6
	CONTROL('X'),CONTROL('X'),0,	A_GOMARK,
E 6
	'E',0,				A_EXAMINE,
D 6
	':','e',0,			A_EXAMINE,
	CONTROL('X'),CONTROL('V'),0,	A_EXAMINE,
E 6
	'N',0,				A_NEXT_FILE,
D 6
	'P',0,				A_PREV_FILE,
E 6
	':','n',0,			A_NEXT_FILE,
I 6
	'P',0,				A_PREV_FILE,
E 6
	':','p',0,			A_PREV_FILE,
D 6
	'-',0,				A_TOGGLE_OPTION,
	'_',0,				A_DISP_OPTION,
E 6
	'v',0,				A_VISUAL,
D 6
	'!',0,				A_SHELL,
	'+',0,				A_FIRSTCMD,
E 6

D 6
	'H',0,				A_HELP,
E 6
	'h',0,				A_HELP,
D 5
	'V',0,				A_VERSION,
E 5
	'q',0,				A_QUIT,
	':','q',0,			A_QUIT,
D 6
	'Z','Z',0,			A_QUIT
E 6
I 6
	':','t',0,			A_TAGFILE,
I 7
	':', 'a', 0,			A_FILE_LIST,
E 7
	'Z','Z',0,			A_QUIT,
E 6
};

char *cmdendtable = cmdtable + sizeof(cmdtable);

D 6
static char usertable[MAX_USERCMD];
char *userendtable = usertable;
E 6
I 6
#define	MAX_CMDLEN	16
E 6

static char kbuf[MAX_CMDLEN+1];
static char *kp = kbuf;

/*
I 6
 * Indicate that we're not in a prefix command
 * by resetting the command buffer pointer.
 */
noprefix()
{
	kp = kbuf;
}

/*
E 6
 * Decode a command character and return the associated action.
 */
D 6
	public int
E 6
cmd_decode(c)
	int c;
{
	register int action = A_INVALID;

	/*
	 * Append the new command character to the command string in kbuf.
	 */
	*kp++ = c;
	*kp = '\0';

D 2
#if USERFILE
E 2
D 6
	/*
	 * Look first for any user-defined commands.
	 */
	action = cmd_search(usertable, userendtable);
D 2
#endif
E 2
	/*
	 * If didn't find user-defined command,
	 * try the normal default commands.
	 */
	if (action == A_INVALID)
		action = cmd_search(cmdtable, cmdendtable);
E 6
I 6
	action = cmd_search(cmdtable, cmdendtable);
E 6

I 6
	/* This is not a prefix character. */
E 6
	if (action != A_PREFIX)
D 6
		/*
		 * This is not a prefix character.
		 */
E 6
		noprefix();
D 6

	return (action);
E 6
I 6
	return(action);
E 6
}

/*
D 6
 * Indicate that we're not in a prefix command
 * by resetting the command buffer pointer.
 */
	public void
noprefix()
{
	kp = kbuf;
}

/*
E 6
 * Search a command table for the current command string (in kbuf).
 */
D 6
	static int
E 6
I 6
D 9
static
E 9
E 6
cmd_search(table, endtable)
	char *table;
	char *endtable;
{
D 6
	register char *p;
	register char *q;
E 6
I 6
	register char *p, *q;
E 6

D 6
	for (p = table, q = kbuf;  p < endtable;  p++, q++)
	{
		if (*p == *q)
		{
E 6
I 6
	for (p = table, q = kbuf;  p < endtable;  p++, q++) {
		if (*p == *q) {
E 6
			/*
			 * Current characters match.
			 * If we're at the end of the string, we've found it.
			 * Return the action code, which is the character
			 * after the null at the end of the string
			 * in the command table.
			 */
			if (*p == '\0')
D 6
				return (p[1]);
		} else if (*q == '\0')
		{
E 6
I 6
				return(p[1]);
		}
		else if (*q == '\0') {
E 6
			/*
			 * Hit the end of the user's command,
			 * but not the end of the string in the command table.
			 * The user's command is incomplete.
			 */
D 6
			return (A_PREFIX);
		} else
		{
E 6
I 6
			return(A_PREFIX);
		} else {
E 6
			/*
			 * Not a match.
			 * Skip ahead to the next command in the
			 * command table, and reset the pointer
			 * to the user's command.
			 */
D 6
			while (*p++ != '\0') ;
E 6
I 6
			while (*p++ != '\0');
E 6
			q = kbuf-1;
		}
	}
	/*
	 * No match found in the entire command table.
	 */
D 6
	return (A_INVALID);
}

/*
 * Initialize the user command table.
 */
	public void
init_cmd()
{
D 2
#if USERFILE
E 2
D 3
	char *filename;
E 3
	char *homedir;
	int f;
	int n;
I 3
	char filename[MAXPATHLEN];
E 3
	extern char *getenv();

	/*
	 * Try to open "$HOME/.less"
	 * If we can't, return without doing anything.
	 */
	homedir = getenv("HOME");
	if (homedir == NULL)
		return;
D 3
	filename = calloc(strlen(homedir)+7, sizeof(char));
	if (filename == NULL)
		return;
	sprintf(filename, "%s/%s", homedir, ".less");
	f = open(filename, 0);
	free(filename);
E 3
I 3
	(void)sprintf(filename, "%s/%s", homedir, ".less");
	f = open(filename, O_RDONLY);
E 3
	if (f < 0)
		return;

	/*
	 * Read the file into the user table.
	 * {{ Minimal error checking is done here.
	 *    A garbage .less file will produce strange results.
	 *    To avoid a large amount of error checking code here, we
	 *    rely on the lesskey program to generate a good .less file. }}
	 */
	n = read(f, (char *)usertable, MAX_USERCMD);
	if (n < 3 || usertable[n-2] != '\0')
	{
		/*
		 * Several error cases are lumped together here:
		 * - Cannot read user file (n < 0).
		 * - User file is too short (a valid file must
		 *   have at least 3 chars: one char command string,
		 *   the terminating null byte, and the action byte).
		 * - The final entry in the user file is bad (it
		 *   doesn't have a null byte in the proper place).
		 * Many other error cases are not caught, such as
		 * invalid format in any except the last entry,
		 * invalid action codes, command strings too long, etc.
		 */
		error("invalid user key file");
		n = 0;
	}
	userendtable = usertable + n;
	close(f);
E 6
I 6
	return(A_INVALID);
E 6
D 2
#endif
E 2
}
E 1
