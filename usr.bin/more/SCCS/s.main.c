h52408
s 00000/00000/00341
d D 8.1 93/06/07 20:54:12 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00004/00337
d D 5.14 93/06/07 20:53:12 bostic 15 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00336
d R 8.1 93/06/06 15:36:41 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00340
d D 5.13 90/06/01 17:04:19 bostic 13 12
c new copyright notice
e
s 00001/00001/00351
d D 5.12 90/02/27 00:40:28 donn 12 11
c Don't use the position table until it's initialized.
e
s 00005/00001/00347
d D 5.11 88/11/29 16:22:03 bostic 11 10
c display next file name as part of "END" prompt
e
s 00017/00004/00331
d D 5.10 88/11/27 18:28:18 bostic 10 9
c do -s processing, even if output not a tty
e
s 00092/00141/00243
d D 5.9 88/11/22 16:51:31 bostic 9 8
c less -> more
e
s 00000/00006/00384
d D 5.8 88/09/23 14:50:43 bostic 8 7
c editor variable is now localized, and only gotten if needed
e
s 00002/00004/00388
d D 5.7 88/07/25 12:05:01 bostic 7 6
c update copyright notice
e
s 00004/00005/00388
d D 5.6 88/07/22 12:07:18 bostic 6 5
c lint cleanup, use malloc, not calloc
e
s 00000/00082/00393
d D 5.5 88/07/21 19:21:26 bostic 5 4
c rip out LOGFILE option
e
s 00000/00004/00475
d D 5.4 88/07/21 19:13:42 bostic 4 3
c rip out TAGS option, make default
e
s 00000/00005/00479
d D 5.3 88/07/21 19:12:10 bostic 3 2
c rip out EDITOR and EDIT_PGM defines
e
s 00001/00001/00483
d D 5.2 88/07/21 19:02:11 bostic 2 1
c offset_t -> off_t
e
s 00484/00000/00000
d D 5.1 88/07/21 18:52:58 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 15
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1988, 1993
 *	Regents of the University of California.  All rights reserved.
E 15
 *
D 7
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 7
D 13
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 7
 * by the University of California, Berkeley.  The name of the
E 7
I 7
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 7
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
 * %sccs.include.redist.c%
E 13
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1988 Mark Nudleman.\n\
D 15
%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 15
I 15
%Z% Copyright (c) 1988, 1993
	Regents of the University of California.  All rights reserved.\n";
E 15
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Entry point, initialization, miscellaneous routines.
 */

D 9
#include "less.h"
#include "position.h"
E 9
I 9
#include <sys/types.h>
#include <sys/file.h>
#include <stdio.h>
#include <less.h>
E 9

D 9
public int	ispipe;
public char *	first_cmd;
public char *	every_first_cmd;
public int	new_file;
public int	is_tty;
public char 	*current_file;
public char 	*previous_file;
public POSITION	prev_pos;
public int	any_display;
public int	scroll;
public int	ac;
public char **	av;
public int 	curr_ac;
public int	quitting;
E 9
I 9
int	ispipe;
int	new_file;
int	is_tty;
D 11
char	*current_file, *previous_file, *current_name;
E 11
I 11
char	*current_file, *previous_file, *current_name, *next_name;
E 11
off_t	prev_pos;
int	any_display;
int	scroll;
int	ac;
char	**av;
int	curr_ac;
int	quitting;
E 9

extern int	file;
D 9
extern int	quit_at_eof;
E 9
extern int	cbufs;
extern int	errmsgs;

D 5
#if LOGFILE
public int	logfile = -1;
public int	force_logfile = 0;
public char *	namelogfile = NULL;
#endif

E 5
D 3
#if EDITOR
E 3
D 8
public char *	editor;
D 3
#endif
E 3

E 8
D 4
#if TAGS
E 4
D 9
extern char *	tagfile;
extern char *	tagpattern;
E 9
I 9
extern char	*tagfile;
E 9
extern int	tagoption;
D 4
#endif
E 4

D 3

E 3
/*
 * Edit a new file.
 * Filename "-" means standard input.
 * No filename means the "current" file, from the command line.
 */
D 9
	public void
E 9
edit(filename)
	register char *filename;
{
I 9
	extern int errno;
E 9
	register int f;
	register char *m;
D 9
	POSITION initial_pos;
	char message[100];
E 9
I 9
	off_t initial_pos, position();
E 9
	static int didpipe;
I 9
	char message[100], *p;
	char *rindex(), *strerror(), *save(), *bad_file();
E 9

	initial_pos = NULL_POSITION;
D 9
	if (filename == NULL || *filename == '\0')
	{
		if (curr_ac >= ac)
		{
E 9
I 9
	if (filename == NULL || *filename == '\0') {
		if (curr_ac >= ac) {
E 9
			error("No current file");
D 9
			return;
E 9
I 9
			return(0);
E 9
		}
		filename = save(av[curr_ac]);
D 9
	} else if (strcmp(filename, "#") == 0)
	{
		if (*previous_file == '\0')
		{
E 9
I 9
	}
	else if (strcmp(filename, "#") == 0) {
		if (*previous_file == '\0') {
E 9
			error("no previous file");
D 9
			return;
E 9
I 9
			return(0);
E 9
		}
		filename = save(previous_file);
		initial_pos = prev_pos;
	} else
		filename = save(filename);

D 9
	if (strcmp(filename, "-") == 0)
	{
		/* 
		 * Use standard input.
		 */
		if (didpipe)
		{
E 9
I 9
	/* use standard input. */
	if (!strcmp(filename, "-")) {
		if (didpipe) {
E 9
			error("Can view standard input only once");
D 9
			return;
E 9
I 9
			return(0);
E 9
		}
		f = 0;
D 9
	} else if ((m = bad_file(filename, message, sizeof(message))) != NULL)
	{
E 9
I 9
	}
	else if ((m = bad_file(filename, message, sizeof(message))) != NULL) {
E 9
		error(m);
		free(filename);
D 9
		return;
	} else if ((f = open(filename, 0)) < 0)
	{
		error(errno_message(filename, message, sizeof(message)));
E 9
I 9
		return(0);
	}
	else if ((f = open(filename, O_RDONLY, 0)) < 0) {
		(void)sprintf(message, "%s: %s", filename, strerror(errno));
		error(message);
E 9
		free(filename);
D 9
		return;
E 9
I 9
		return(0);
E 9
	}

D 9
	if (isatty(f))
	{
E 9
I 9
	if (isatty(f)) {
E 9
		/*
		 * Not really necessary to call this an error,
		 * but if the control terminal (for commands)
		 * and the input file (for data) are the same,
		 * we get weird results at best.
		 */
		error("Can't take input from a terminal");
		if (f > 0)
D 9
			close(f);
		free(filename);
		return;
E 9
I 9
			(void)close(f);
		(void)free(filename);
		return(0);
E 9
	}

D 5
#if LOGFILE
	if (f == 0 && namelogfile != NULL && is_tty)
		use_logfile();
#endif

E 5
	/*
	 * We are now committed to using the new file.
	 * Close the current input file and set up to use the new one.
	 */
	if (file > 0)
D 9
		close(file);
E 9
I 9
		(void)close(file);
E 9
	new_file = 1;
	if (previous_file != NULL)
		free(previous_file);
	previous_file = current_file;
	current_file = filename;
I 12
	pos_clear();
E 12
	prev_pos = position(TOP);
	ispipe = (f == 0);
D 9
	if (ispipe)
E 9
I 9
	if (ispipe) {
E 9
		didpipe = 1;
I 9
		current_name = "stdin";
	} else
		current_name = (p = rindex(filename, '/')) ? p + 1 : filename;
I 11
	if (curr_ac >= ac)
		next_name = NULL;
	else
		next_name = av[curr_ac + 1];
E 11
E 9
	file = f;
	ch_init(cbufs, 0);
	init_mark();

D 9
	if (every_first_cmd != NULL)
		first_cmd = every_first_cmd;

	if (is_tty)
	{
E 9
I 9
	if (is_tty) {
E 9
		int no_display = !any_display;
		any_display = 1;
D 9
		if (no_display && errmsgs > 0)
		{
E 9
I 9
		if (no_display && errmsgs > 0) {
E 9
			/*
			 * We displayed some messages on error output
			 * (file descriptor 2; see error() function).
			 * Before erasing the screen contents,
			 * display the file name and wait for a keystroke.
			 */
			error(filename);
		}
		/*
		 * Indicate there is nothing displayed yet.
		 */
D 12
		pos_clear();
E 12
		if (initial_pos != NULL_POSITION)
			jump_loc(initial_pos);
		clr_linenum();
	}
I 9
	return(1);
E 9
}

/*
 * Edit the next file in the command line list.
 */
D 9
	public void
E 9
next_file(n)
	int n;
{
D 9
	if (curr_ac + n >= ac)
	{
		if (quit_at_eof)
E 9
I 9
	extern int quit_at_eof;
	off_t position();

	if (curr_ac + n >= ac) {
		if (quit_at_eof || position(TOP) == NULL_POSITION)
E 9
			quit();
		error("No (N-th) next file");
D 9
	} else
		edit(av[curr_ac += n]);
E 9
I 9
	}
	else
		(void)edit(av[curr_ac += n]);
E 9
}

/*
 * Edit the previous file in the command line list.
 */
D 9
	public void
E 9
prev_file(n)
	int n;
{
	if (curr_ac - n < 0)
		error("No (N-th) previous file");
	else
D 9
		edit(av[curr_ac -= n]);
E 9
I 9
		(void)edit(av[curr_ac -= n]);
E 9
}

/*
D 10
 * Copy a file directly to standard output.
 * Used if standard output is not a tty.
E 10
I 10
 * copy a file directly to standard output; used if stdout is not a tty.
 * the only processing is to squeeze multiple blank input lines.
E 10
 */
D 9
	static void
E 9
I 9
static
E 9
cat_file()
{
D 10
	register int c;
E 10
I 10
	extern int squeeze;
	register int c, empty;
E 10

D 10
	while ((c = ch_forw_get()) != EOI)
E 10
I 10
	if (squeeze) {
		empty = 0;
		while ((c = ch_forw_get()) != EOI)
			if (c != '\n') {
				putchr(c);
				empty = 0;
			}
			else if (empty < 2) {
				putchr(c);
				++empty;
			}
	}
	else while ((c = ch_forw_get()) != EOI)
E 10
		putchr(c);
	flush();
}

D 5
#if LOGFILE

use_logfile()
{
	int exists;
	int answer;
	char message[100];

	/*
	 * If he asked for a log file and we have opened standard input,
	 * create the log file.  
	 * We take care not to blindly overwrite an existing file.
	 */
	end_logfile();

	/*
	 * {{ We could use access() here. }}
	 */
	exists = open(namelogfile, 0);
	close(exists);
	exists = (exists >= 0);

	if (exists && !force_logfile)
	{
		static char w[] = "WARNING: log file exists: ";
		strcpy(message, w);
		strtcpy(message+sizeof(w)-1, namelogfile,
			sizeof(message)-sizeof(w));
		error(message);
		answer = 'X';	/* Ask the user what to do */
	} else
		answer = 'O';	/* Create the log file */

loop:
	switch (answer)
	{
	case 'O': case 'o':
		logfile = creat(namelogfile, 0644);
		break;
	case 'A': case 'a':
		logfile = open(namelogfile, 1);
D 2
		if (lseek(logfile, (offset_t)0, 2) < 0)
E 2
I 2
		if (lseek(logfile, (off_t)0, L_XTND) < 0)
E 2
		{
			close(logfile);
			logfile = -1;
		}
		break;
	case 'D': case 'd':
		answer = 0;	/* Don't print an error message */
		break;
	case 'q':
		quit();
	default:
		putstr("\n  Overwrite, Append, or Don't log? ");
		answer = getchr();
		putstr("\n");
		flush();
		goto loop;
	}

	if (logfile < 0 && answer != 0)
	{
		sprintf(message, "Cannot write to \"%s\"", 
			namelogfile);
		error(message);
	}
}

E 5
D 9
/*
 * Entry point.
 */
E 9
main(argc, argv)
	int argc;
D 9
	char *argv[];
E 9
I 9
	char **argv;
E 9
{
D 9
	char *getenv();
E 9
I 9
	int envargc, argcnt;
	char *envargv[2], *getenv();
E 9

D 9

E 9
	/*
D 9
	 * Process command line arguments and LESS environment arguments.
E 9
I 9
	 * Process command line arguments and MORE environment arguments.
E 9
	 * Command line arguments override environment arguments.
	 */
D 9
	init_prompt();
	init_option();
	scan_option(getenv("LESS"));
	argv++;
	while ( (--argc > 0) && 
		(argv[0][0] == '-' || argv[0][0] == '+') && 
		argv[0][1] != '\0')
		scan_option(*argv++);
E 9
I 9
	if (envargv[1] = getenv("MORE")) {
		envargc = 2;
		envargv[0] = "more";
		envargv[2] = NULL;
		(void)option(envargc, envargv);
	}
	argcnt = option(argc, argv);
	argv += argcnt;
	argc -= argcnt;
E 9
D 8

D 3
#if EDITOR
E 3
	editor = getenv("EDITOR");
	if (editor == NULL || *editor == '\0')
		editor = EDIT_PGM;
E 8
D 3
#endif
E 3

	/*
	 * Set up list of files to be examined.
	 */
	ac = argc;
	av = argv;
	curr_ac = 0;

	/*
	 * Set up terminal, etc.
	 */
	is_tty = isatty(1);
D 9
	if (!is_tty)
	{
E 9
I 9
	if (!is_tty) {
E 9
		/*
		 * Output is not a tty.
		 * Just copy the input file(s) to output.
		 */
D 9
		if (ac < 1)
		{
			edit("-");
E 9
I 9
		if (ac < 1) {
			(void)edit("-");
E 9
			cat_file();
D 9
		} else
		{
			do
			{
				edit((char *)NULL);
E 9
I 9
		} else {
			do {
				(void)edit((char *)NULL);
E 9
				if (file >= 0)
					cat_file();
			} while (++curr_ac < ac);
		}
		exit(0);
	}

	raw_mode(1);
	get_term();
	open_getchr();
	init();
D 9
	init_cmd();

E 9
	init_signals(1);

D 9
	/*
	 * Select the first file to examine.
	 */
D 4
#if TAGS
E 4
	if (tagoption)
	{
E 9
I 9
	/* select the first file to examine. */
	if (tagoption) {
E 9
		/*
D 9
		 * A -t option was given.
		 * Verify that no filenames were also given.
		 * Edit the file selected by the "tags" search,
		 * and search for the proper line in the file.
E 9
I 9
		 * A -t option was given; edit the file selected by the
		 * "tags" search, and search for the proper line in the file.
E 9
		 */
D 9
		if (ac > 0)
		{
			error("No filenames allowed with -t option");
E 9
I 9
		if (!tagfile || !edit(tagfile) || tagsearch())
E 9
			quit();
D 9
		}
		if (tagfile == NULL)
			quit();
		edit(tagfile);
		if (file < 0)
			quit();
		if (tagsearch())
			quit();
	} else
D 4
#endif
E 4
	if (ac < 1)
		edit("-");	/* Standard input */
	else 
	{
E 9
I 9
	}
	else if (ac < 1)
		(void)edit("-");	/* Standard input */
	else {
E 9
		/*
		 * Try all the files named as command arguments.
		 * We are simply looking for one which can be
		 * opened without error.
		 */
D 9
		do
		{
			edit((char *)NULL);
E 9
I 9
		do {
			(void)edit((char *)NULL);
E 9
		} while (file < 0 && ++curr_ac < ac);
	}

	if (file >= 0)
		commands();
	quit();
	/*NOTREACHED*/
}

/*
D 9
 * Copy a string, truncating to the specified length if necessary.
 * Unlike strncpy(), the resulting string is guaranteed to be null-terminated.
 */
	public void
strtcpy(to, from, len)
	char *to;
	char *from;
	unsigned int len;
{
	strncpy(to, from, len);
	to[len-1] = '\0';
}

/*
E 9
 * Copy a string to a "safe" place
D 6
 * (that is, to a buffer allocated by calloc).
E 6
I 6
 * (that is, to a buffer allocated by malloc).
E 6
 */
D 9
	public char *
E 9
I 9
char *
E 9
save(s)
	char *s;
{
D 6
	register char *p;
E 6
I 6
	char *p, *strcpy(), *malloc();
E 6

D 6
	p = calloc(strlen(s)+1, sizeof(char));
E 6
I 6
	p = malloc((u_int)strlen(s)+1);
E 6
	if (p == NULL)
	{
		error("cannot allocate memory");
		quit();
	}
D 6
	strcpy(p, s);
	return (p);
E 6
I 6
	return(strcpy(p, s));
E 6
}

/*
 * Exit the program.
 */
D 9
	public void
E 9
quit()
{
	/*
	 * Put cursor at bottom left corner, clear the line,
	 * reset the terminal modes, and exit.
	 */
	quitting = 1;
D 5
#if LOGFILE
	end_logfile();
#endif
E 5
	lower_left();
	clear_eol();
	deinit();
	flush();
	raw_mode(0);
	exit(0);
}
E 1
