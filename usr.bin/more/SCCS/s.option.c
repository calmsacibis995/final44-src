h08551
s 00002/00002/00100
d D 8.1 93/06/06 15:36:57 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00101
d D 5.11 90/06/01 17:04:25 bostic 11 10
c new copyright notice
e
s 00003/00001/00110
d D 5.10 90/03/08 10:19:48 marc 10 9
c skip over -f flag (compatability with old/more)
e
s 00001/00001/00110
d D 5.9 89/05/12 12:39:27 bostic 9 8
c fix usage line
e
s 00002/00006/00109
d D 5.8 88/12/06 17:33:45 bostic 8 7
c remove -p (terse prompts)
e
s 00006/00000/00109
d D 5.7 88/11/27 18:13:10 bostic 7 6
c backward compatible processing for "+/pattern"
e
s 00076/00502/00033
d D 5.6 88/11/22 16:51:38 bostic 6 5
c less -> more
e
s 00002/00004/00533
d D 5.5 88/07/25 12:05:04 bostic 5 4
c update copyright notice
e
s 00008/00008/00529
d D 5.4 88/07/22 12:05:18 bostic 4 3
c void sprintfs; lint cleanups;
e
s 00000/00055/00537
d D 5.3 88/07/21 19:21:28 bostic 3 2
c rip out LOGFILE option
e
s 00000/00008/00592
d D 5.2 88/07/21 19:13:44 bostic 2 1
c rip out TAGS option, make default
e
s 00600/00000/00000
d D 5.1 88/07/21 18:53:01 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 12
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 5
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 5
D 11
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 5
 * by the University of California, Berkeley.  The name of the
E 5
I 5
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 5
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 6
/*
 * Process command line options.
 * Each option is a single letter which controls a program variable.
 * The options have defaults which may be changed via
 * the command line option, or toggled via the "-" command.
 */
E 6
I 6
#include <stdio.h>
#include <less.h>
E 6

D 6
#include "less.h"
E 6
I 6
int top_scroll;			/* Repaint screen from top */
int bs_mode;			/* How to process backspaces */
int caseless;			/* Do "caseless" searches */
int cbufs = 10;			/* Current number of buffers */
int linenums = 1;		/* Use line numbers */
int quit_at_eof;
int squeeze;			/* Squeeze multiple blank lines into one */
int tabstop = 8;		/* Tab settings */
int tagoption;
D 8
int terseprompt;
E 8
E 6

D 6
#define	toupper(c)	((c)-'a'+'A')
E 6
I 6
char *firstsearch;
extern int sc_height;
E 6

D 6
#define	END_OPTION_STRING	('$')

/*
 * Types of options.
 */
#define	BOOL		01	/* Boolean option: 0 or 1 */
#define	TRIPLE		02	/* Triple-valued option: 0, 1 or 2 */
#define	NUMBER		04	/* Numeric option */
#define	REPAINT		040	/* Repaint screen after toggling option */
#define	NO_TOGGLE	0100	/* Option cannot be toggled with "-" cmd */

/*
 * Variables controlled by command line options.
 */
public int clean_data;		/* Can we assume the data is "clean"? 
				   (That is, free of nulls, etc) */
public int quiet;		/* Should we suppress the audible bell? */
public int how_search;		/* Where should forward searches start? */
public int top_scroll;		/* Repaint screen from top?
				   (alternative is scroll from bottom) */
public int pr_type;		/* Type of prompt (short, medium, long) */
public int bs_mode;		/* How to process backspaces */
public int know_dumb;		/* Don't complain about dumb terminals */
public int quit_at_eof;		/* Quit after hitting end of file twice */
public int squeeze;		/* Squeeze multiple blank lines into one */
public int tabstop;		/* Tab settings */
public int back_scroll;		/* Repaint screen on backwards movement */
public int twiddle;		/* Display "~" for lines after EOF */
public int caseless;		/* Do "caseless" searches */
public int linenums;		/* Use line numbers */
public int cbufs;		/* Current number of buffers */
public int autobuf;
public int plusoption;

extern char *prproto[];
extern char *eqproto;
extern int nbufs;
extern int sc_window;
extern int ispipe;
extern char *first_cmd;
extern char *every_first_cmd;
D 3
#if LOGFILE
extern char *namelogfile;
extern int force_logfile;
extern int logfile;
#endif
E 3
D 2
#if TAGS
E 2
extern char *tagfile;
extern char *tagpattern;
public int tagoption = 0;
D 2
#endif
E 2

static char *opt_P();

static struct option
E 6
I 6
option(argc, argv)
	int argc;
	char **argv;
E 6
{
D 6
	char oletter;		/* The controlling letter (a-z) */
	char otype;		/* Type of the option */
	int odefault;		/* Default value */
	int *ovar;		/* Pointer to the associated variable */
	char *odesc[3];		/* Description of each value */
} option[] =
{
	{ 'a', TRIPLE, 0, &how_search,
		{ "Forward search starts at second REAL line displayed",
		  "Forward search starts at bottom of screen",
		  "Forward search starts at second SCREEN line displayed"
		}
	},
	{ 'b', NUMBER, 10, &cbufs,
		{ "%d buffers",
		  NULL, NULL
		}
	},
	{ 'B', BOOL, 1, &autobuf,
		{ "Don't automatically allocate buffers",
		  "Automatically allocate buffers when needed",
		  NULL
		}
	},
	{ 'c', TRIPLE, 0, &top_scroll,
		{ "Repaint by scrolling from bottom of screen",
		  "Repaint by clearing each line",
		  "Repaint by painting from top of screen"
		}
	},
	{ 'd', BOOL|NO_TOGGLE, 0, &know_dumb,
		{ NULL, NULL, NULL}
	},
	{ 'e', TRIPLE, 0, &quit_at_eof,
		{ "Don't quit at end-of-file",
		  "Quit at end-of-file",
		  "Quit immediately at end-of-file"
		}
	},
	{ 'h', NUMBER, -1, &back_scroll,
		{ "Backwards scroll limit is %d lines",
		  NULL, NULL
		}
	},
	{ 'i', BOOL, 0, &caseless,
		{ "Case is significant in searches",
		  "Ignore case in searches",
		  NULL
		}
	},
	{ 'm', TRIPLE, 0, &pr_type,
		{ "Short prompt",
		  "Medium prompt",
		  "Long prompt"
		}
	},
	{ 'n', BOOL, 1, &linenums,
		{ "Don't use line numbers",
		  "Use line numbers",
		  NULL
		}
	},
	{ 'q', TRIPLE, 0, &quiet,
		{ "Ring the bell for errors AND at eof/bof",
		  "Ring the bell for errors but not at eof/bof",
		  "Never ring the bell"
		}
	},
	{ 's', BOOL|REPAINT, 0, &squeeze,
		{ "Don't squeeze multiple blank lines",
		  "Squeeze multiple blank lines",
		  NULL
		}
	},
	{ 'u', TRIPLE|REPAINT, 0, &bs_mode,
		{ "Underlined text displayed in underline mode",
		  "Backspaces cause overstrike",
		  "Backspaces print as ^H"
		}
	},
	{ 'w', BOOL|REPAINT, 1, &twiddle,
		{ "Display nothing for lines after end-of-file",
		  "Display ~ for lines after end-of-file",
		  NULL
		}
	},
	{ 'x', NUMBER|REPAINT, 8, &tabstop,
		{ "Tab stops every %d spaces", 
		  NULL, NULL 
		}
	},
	{ 'z', NUMBER|REPAINT, -1, &sc_window,
		{ "Scroll window size is %d lines",
		  NULL, NULL
		}
	},
	{ '\0' }
};
E 6
I 6
	extern char *optarg;
	extern int optind;
	static int sc_window_set = 0;
	int ch;
	char *p;
E 6

I 7
	/* backward compatible processing for "+/search" */
	char **a;
	for (a = argv; *a; ++a)
		if ((*a)[0] == '+' && (*a)[1] == '/')
			(*a)[0] = '-';

E 7
D 6
/*
 * Initialize each option to its default value.
 */
	public void
init_option()
{
	register struct option *o;

	first_cmd = every_first_cmd = NULL;

	for (o = option;  o->oletter != '\0';  o++)
	{
		/*
		 * Set each variable to its default.
		 */
		*(o->ovar) = o->odefault;
	}
}

/*
 * Toggle command line flags from within the program.
 * Used by the "-" and "_" commands.
 * If do_toggle is zero, just report the current setting, without changing it.
 */
	public void
toggle_option(s, do_toggle)
	char *s;
	int do_toggle;
{
	int c;
	register struct option *o;
	char *msg;
	int n;
	int dorepaint;
D 4
	char message[100];
E 4
I 4
	char message[100], *strcat();
E 4

	c = *s++;

	switch (c)
	{
	case 'P':
		/*
		 * Special case for -P.
		 */
		if (*s == '\0')
			error(prproto[pr_type]);
		else
			(void) opt_P(s);
		return;
D 2
#if TAGS
E 2
	case 't':
		/*
		 * Special case for -t.
		 */
		if (*s == '\0')
		{
			error("no tag");
			return;
		}
		findtag(s);
		if (tagfile != NULL)
		{
			edit(tagfile);
			(void) tagsearch();
		}
		return;
D 2
#endif
E 2
D 3
#if LOGFILE
	case 'L':
		/*
		 * Special case for -l and -L.
		 */
		force_logfile = 1;
		goto case_l;
	case 'l':
		force_logfile = 0;
	case_l:
		if (*s == '\0')
		{
			if (logfile < 0)
				error("no log file");
			else
			{
				sprintf(message, "log file \"%s\"",
					namelogfile);
				error(message);
			}
			return;
		}
		if (!ispipe)
		{
			error("input is not a pipe");
			return;
		}
		if (logfile >= 0)
		{
			error("log file is already in use");
			return;
		}
		namelogfile = save(s);
		use_logfile();
		sync_logfile();
		return;
#endif
E 3
	}

	msg = NULL;
	for (o = option;  o->oletter != '\0';  o++)
	{
		if (o->otype & NO_TOGGLE)
			continue;
		dorepaint = (o->otype & REPAINT);
		if ((o->otype & BOOL) && (o->oletter == c))
		{
E 6
I 6
	optind = 1;		/* called twice, re-init getopt. */
D 8
	while ((ch = getopt(argc, argv, "0123456789/:ceinpst:ux:")) != EOF)
E 8
I 8
D 10
	while ((ch = getopt(argc, argv, "0123456789/:ceinst:ux:")) != EOF)
E 10
I 10
	while ((ch = getopt(argc, argv, "0123456789/:ceinst:ux:f")) != EOF)
E 10
E 8
		switch((char)ch) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
E 6
			/*
D 6
			 * Boolean option: 
			 * just toggle it.
E 6
I 6
			 * kludge: more was originally designed to take
			 * a number after a dash.
E 6
			 */
D 6
			if (do_toggle)
				*(o->ovar) = ! *(o->ovar);
		} else if ((o->otype & TRIPLE) && (o->oletter == c))
		{
			/*
			 * Triple-valued option with lower case letter:
			 * make it 1 unless already 1, then make it 0.
			 */
			if (do_toggle)
				*(o->ovar) = (*(o->ovar) == 1) ? 0 : 1;
		} else if ((o->otype & TRIPLE) && (toupper(o->oletter) == c))
		{
			/*
			 * Triple-valued option with upper case letter:
			 * make it 2 unless already 2, then make it 0.
			 */
			if (do_toggle)
				*(o->ovar) = (*(o->ovar) == 2) ? 0 : 2;
		} else if ((o->otype & NUMBER) && (o->oletter == c))
		{
			n = getnum(&s, '\0');
			if (n < 0)
			{
				/*
				 * No number; just a query.
				 * No need to repaint screen.
				 */
				dorepaint = 0;
			} else
			{
				/*
				 * Number follows the option letter.
				 * Set the variable to that number.
				 */
				if (do_toggle)
					*(o->ovar) = n;
E 6
I 6
			if (!sc_window_set) {
				p = argv[optind - 1];
				if (p[0] == '-' && p[1] == ch && !p[2])
					sc_height = atoi(++p);
				else
					sc_height = atoi(argv[optind] + 1);
				sc_window_set = 1;
E 6
			}
D 6

			/*
			 * Special case for -b.
			 * Call ch_init to set new number of buffers.
			 */
			if (o->ovar == &cbufs)
				ch_init(cbufs, 1);

D 4
			sprintf(message, o->odesc[0], 
E 4
I 4
			(void)sprintf(message, o->odesc[0],
E 4
				(o->ovar == &back_scroll) ? 
				get_back_scroll() : *(o->ovar));
			msg = message;
		} else
			continue;

		/*
		 * Print a message describing the new setting.
		 */
		if (msg == NULL)
			msg = o->odesc[*(o->ovar)];
		error(msg);

		if (do_toggle && dorepaint)
			repaint();
		return;
	}

	if (control_char(c))
D 4
		sprintf(message, "-^%c", carat_char(c));
E 4
I 4
		(void)sprintf(message, "-^%c", carat_char(c));
E 4
	else
D 4
		sprintf(message, "-%c", c);
	strcat(message, ": no such flag.");
E 4
I 4
		(void)sprintf(message, "-%c", c);
	(void)strcat(message, ": no such flag.");
E 4
	error(message);
}

/*
 * Determine if an option is a single character option (BOOL or TRIPLE),
 * or if it a multi-character option (NUMBER).
 */
	public int
single_char_option(c)
	int c;
{
	register struct option *o;

	if (c == 'P')
		return (0);
D 2
#if TAGS
E 2
	if (c == 't')
		return (0);
D 2
#endif
E 2
D 3
#if LOGFILE
	if (c == 'l' || c == 'L')
		return (0);
#endif
E 3
	for (o = option;  o->oletter != '\0';  o++)
		if (o->oletter == c)
			return (o->otype & (BOOL|TRIPLE));
	return (1);
}

/*
 * Scan to end of string or to an END_OPTION_STRING character.
 * In the latter case, replace the char with a null char.
 * Return a pointer to the remainder of the string, if any.
 */
	static char *
optstring(s, c)
	char *s;
	int c;
{
	register char *p;
	char message[80];

	if (*s == '\0')
	{
D 4
		sprintf(message, "string is required after -%c", c);
E 4
I 4
		(void)sprintf(message, "string is required after -%c", c);
E 4
		error(message);
		exit(1);
	}
	for (p = s;  *p != '\0';  p++)
		if (*p == END_OPTION_STRING)
		{
			*p = '\0';
			return (p+1);
E 6
I 6
			break;
		case '/':
			firstsearch = optarg;
			break;
		case 'c':
			top_scroll = 1;
			break;
		case 'e':
			quit_at_eof = 1;
			break;
		case 'i':
			caseless = 1;
			break;
		case 'n':
			linenums = 0;
			break;
D 8
		case 'p':
			terseprompt = 1;
			break;
E 8
		case 's':
			squeeze = 1;
			break;
		case 't':
			tagoption = 1;
			findtag(optarg);
			break;
		case 'u':
			bs_mode = 1;
			break;
		case 'x':
			tabstop = atoi(optarg);
			if (tabstop <= 0)
				tabstop = 8;
I 10
			break;
		case 'f':	/* ignore -f, compatability with old more */
E 10
			break;
		case '?':
		default:
			fprintf(stderr,
D 8
			    "usage: less [-ceinpus] [-t tag] [-x tabs] [-/ pattern] [-#] [file ...]\n");
E 8
I 8
D 9
			    "usage: less [-ceinus] [-t tag] [-x tabs] [-/ pattern] [-#] [file ...]\n");
E 9
I 9
			    "usage: more [-ceinus] [-t tag] [-x tabs] [-/ pattern] [-#] [file ...]\n");
E 9
E 8
			exit(1);
E 6
		}
D 6
	return (p);
}

/* 
 * Scan an argument (either from command line or from LESS environment 
 * variable) and process it.
 */
	public void
scan_option(s)
	char *s;
{
	register struct option *o;
	register int c;
	int set_default;
	char message[80];

	if (s == NULL)
		return;

	set_default = 0;
    next:
	if (*s == '\0')
		return;
	switch (c = *s++)
	{
	case ' ':
	case '\t':
	case END_OPTION_STRING:
		goto next;
	case '-':
		if (set_default = (*s == '+'))
			s++;
		goto next;
	case '+':
		plusoption = 1;
		if (*s == '+')
			every_first_cmd = save(++s);
		first_cmd = s;
		s = optstring(s, c);
		goto next;
D 3
#if LOGFILE
	case 'L':
		force_logfile = 1;
		/* FALLTHRU */
	case 'l':
		namelogfile = s;
		s = optstring(s, c);
		goto next;
#endif
E 3
D 2
#if TAGS
E 2
	case 't':
	{
		char *p;
		tagoption = 1;
		p = s;
		s = optstring(s, c);
		findtag(p);
		goto next;
	}
D 2
#endif
E 2
	case 'P':
		s = opt_P(s);
		goto next;
	case '0':  case '1':  case '2':  case '3':  case '4':
	case '5':  case '6':  case '7':  case '8':  case '9':
		/*
		 * Handle special "more" compatibility form "-number"
		 * (instead of -znumber) to set the scrolling window size.
		 */
		s--;
		c = 'z';
		break;
	}

	for (o = option;  o->oletter != '\0';  o++)
	{
		if ((o->otype & BOOL) && (o->oletter == c))
		{
			if (set_default)
				*(o->ovar) = o->odefault;
			else
				*(o->ovar) = ! o->odefault;
			goto next;
		} else if ((o->otype & TRIPLE) && (o->oletter == c))
		{
			if (set_default)
				*(o->ovar) = o->odefault;
			else
				*(o->ovar) = (o->odefault == 1) ? 0 : 1;
			goto next;
		} else if ((o->otype & TRIPLE) && (toupper(o->oletter) == c))
		{
			if (set_default)
				*(o->ovar) = o->odefault;
			else
				*(o->ovar) = (o->odefault == 2) ? 0 : 2;
			goto next;
		} else if ((o->otype & NUMBER) && (o->oletter == c))
		{
			*(o->ovar) = getnum(&s, c);
			goto next;
		}
	}

D 4
	sprintf(message, "\"-%c\": invalid flag", c);
E 4
I 4
	(void)sprintf(message, "\"-%c\": invalid flag", c);
E 4
	error(message);
	exit(1);
}

/*
 * Special case for -P.
 */
	static char *
opt_P(s)
	register char *s;
{
	register char *es;
	register char **proto;

	es = optstring(s, 'P');

	/*
	 * Figure out which prototype string should be changed.
	 */
	switch (*s)
	{
	case 'm':  proto = &prproto[PR_MEDIUM];	s++;	break;
	case 'M':  proto = &prproto[PR_LONG];	s++;	break;
	case '=':  proto = &eqproto;		s++;	break;
	default:   proto = &prproto[pr_type];		break;
	}

	free(*proto);
	*proto = save(s);

	return (es);
}

/*
 * Translate a string into a number.
 * Like atoi(), but takes a pointer to a char *, and updates
 * the char * to point after the translated number.
 */
	public int
getnum(sp, c)
	char **sp;
	int c;
{
	register char *s;
	register int n;
	char message[80];

	s = *sp;
	if (*s < '0' || *s > '9')
	{
		if (c == '\0')
			return (-1);
D 4
		sprintf(message, "number is required after -%c", c);
E 4
I 4
		(void)sprintf(message, "number is required after -%c", c);
E 4
		error(message);
		exit(1);
	}

	n = 0;
	while (*s >= '0' && *s <= '9')
		n = 10 * n + *s++ - '0';
	*sp = s;
	return (n);
E 6
I 6
	return(optind);
E 6
}
E 1
