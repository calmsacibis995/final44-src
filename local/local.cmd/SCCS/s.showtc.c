h51374
s 00025/00003/00746
d D 1.9 85/11/01 20:00:09 serge 10 8
c allow relative path names after -f
e
s 00025/00003/00746
d R 1.9 85/11/01 19:56:39 serge 9 8
c allow relative path name after -f
e
s 00054/00015/00695
d D 1.8 85/10/28 19:12:03 serge 8 7
c added more caps
e
s 00001/00001/00709
d D 1.7 83/10/08 16:47:11 layer 7 6
c increase size of termcap buffer to 2048 bytes
e
s 00032/00004/00678
d D 1.6 83/06/22 14:56:48 layer 6 5
c -U flag, and added more caps
e
s 00004/00002/00678
d D 1.5 83/05/15 21:27:32 layer 5 4
c added capability descriptions
e
s 00009/00007/00671
d D 1.4 83/05/15 09:14:26 layer 4 3
c more mods to new feature
e
s 00123/00003/00555
d D 1.3 83/05/14 18:37:32 layer 3 2
c it's human readable now (the output, that is)!
e
s 00024/00014/00534
d D 1.2 83/04/25 18:25:25 layer 2 1
c added -s flag to showtc, and
c changed difftc to diff two entries in one file.
e
s 00548/00000/00000
d D 1.1 83/04/25 13:21:25 layer 1 0
c date and time created 83/04/25 13:21:25 by layer
e
u
U
t
T
I 2
D 8
#ifndef LINT
E 8
I 8
#ifndef lint
E 8
static char *sccsid="%W%	(Berkeley) %G%";
#endif

E 2
I 1
/*
** show termcap entries
**
** where:
I 4
**	-D	look for duplicate names and print termcap file
E 4
D 2
**	-x	expand tc= capabilities
E 2
**	-S	sort entries before display
I 4
**	-T	trace (-DDEBUG only)
I 6
**	-U	print unknown capabilities
E 6
E 4
D 2
**	-d	look for duplicate names
**	-n	-d and stop
**	-g	sort on generic names
E 2
**	-b	show bare entries
I 2
D 4
**	-d	look for duplicate names
E 4
I 4
**	-d	-D and stop
E 4
E 2
**	-f	following arg is FULL PATHNAME of termcap file
I 2
**	-g	sort on generic names
D 4
**	-n	-d and stop
E 4
**	-s	don't print two char name at the front of every line
**	-x	expand tc= capabilities
E 2
**	[ent]	display specific entry. tc= will be expanded.
**
** David L. Wasley, U.C.Berkeley
D 3
** Modified for 4.1c by Kevin Layer
E 3
I 3
** Kevin Layer: modified for 4.1c and misc changes.
** Kevin Layer: added the printing of terminal capabilities
**	in `human' readable form (like that in "man 5 termcap").
E 3
*/

D 2
#ifndef LINT
static char *sccsid="%W%	(Berkeley) %G%";
#endif

E 2
#include <stdio.h>
#include <sys/file.h>
#include <ctype.h>
D 10
#include <sys/types.h>
E 10
I 10
#include <sys/param.h>
E 10
#include <sys/stat.h>

#define NO		0
#define YES		1
#define CNULL		'\0'
#define NOENTRIES	1024
D 2
#define USAGE		"usage: %s [-Sxdngb] [-f termcapfile] [entry] ..."
E 2
I 2
#define USAGE		"usage: %s [-Sxdngb] [-f termcapfile] [entry] ...\n"
E 2

I 10
#ifndef	MAXPATHLEN
#define MAXPATHLEN	1024
#endif

E 10
struct TcName {
	char	name_buf[124];
	long	file_pos;
} tcNames[NOENTRIES];

I 3
D 4
#define NOCAPS	94
E 4
I 4
D 5
#define NOCAPS	95
E 5
I 5
D 6
#define NOCAPS	97
E 6
I 6
D 8
#define NOCAPS	105
E 6
E 5
E 4

E 8
struct Caps {
	char	*cap;
	char	*desc;
D 8
} capList[NOCAPS] =
E 8
I 8
} capList[] =
E 8
{
I 8
	"AL",	"Add N new blank lines",
	"CC",	"Command char in prototype if settable",
	"DC",	"Delete N characters",
	"DL",	"Delete N lines",
	"DO",	"Move cursor down N lines",
	"IC",	"Insert N blank characters",
	"LE",	"Move cursor left N positions",
	"RI",	"Move cursor right N positions",
	"UP",	"Move cursor up N lines",
E 8
	"ae",	"End alternate character set",
	"al",	"Add new blank line",
	"am",	"Has automatic margins",
	"as",	"Start alternate character set",
	"bc",	"Backspace if not ^H",
I 6
D 8
	"bl",	"Audible Bell",
E 8
I 8
	"bl",	"Audible Bell (default ^G)",
E 8
E 6
	"bs",	"Can backspace with ^H",
	"bt",	"Back tab",
	"bw",	"Backspace wraps from col 0 to last col",
D 8
	"CC",	"Command char in prototype if settable",
E 8
	"cd",	"Clear to end of display",
	"ce",	"Clear to end of line",
	"ch",	"Like cm, but horizontal motion only",
	"cl",	"Clear screen",
	"cm",	"Cursor motion",
	"co",	"Number of columns in a line",
D 8
	"cr",	"Carriage return, (default ^M)",
E 8
I 8
	"cr",	"Carriage return (default ^M)",
E 8
	"cs",	"Change scrolling region (vt100), like cm",
I 8
	"ct",	"Clear all tab stops",
E 8
	"cv",	"Like ch but vertical only.",
D 8
	"da",	"Display may be retained above",
E 8
	"dB",	"Number of millisec of bs delay needed",
D 8
	"db",	"Display may be retained below",
E 8
	"dC",	"Number of millisec of cr delay needed",
D 8
	"dc",	"Delete character",
E 8
	"dF",	"Number of millisec of ff delay needed",
I 8
	"dN",	"Number of millisec of nl delay needed",
	"dT",	"Number of millisec of tab delay needed",
	"da",	"Display may be retained above",
	"db",	"Display may be retained below",
	"dc",	"Delete character",
E 8
	"dl",	"Delete line",
	"dm",	"Start Delete mode",
D 8
	"dN",	"Number of millisec of nl delay needed",
E 8
	"do",	"Down one line",
I 5
	"ds",	"Disable status display",
E 5
D 8
	"dT",	"Number of millisec of tab delay needed",
E 8
	"ed",	"End delete mode",
	"ei",	"End insert mode;give \":ei=:\" if ic",
	"eo",	"Can erase overstrikes with a blank",
I 5
	"es",	"Escape seq's ok on status line",
E 5
	"ff",	"Hardcopy page eject (default ^L)",
	"fs",	"From status line sequence",
	"hc",	"Hardcopy terminal",
	"hd",	"Half-line down (forward 1/2 lf)",
	"ho",	"Home cursor (if no cm)",
D 8
	"hs",	"Has 25th status line",
E 8
I 8
	"hs",	"Has status line",
E 8
	"hu",	"Half-line up (reverse 1/2 lf)",
	"hz",	"Hazeltine; can't print ~'s",
I 8
	"i2",	"Initialization string (used by sysline(1))",
E 8
	"ic",	"Insert character",
	"if",	"Name of file containing is",
	"im",	"Start insert mode;give \":im=:\" if ic",
	"in",	"Insert mode distinguishes nulls on display",
	"ip",	"Insert pad after character inserted",
	"is",	"Initialization string",
I 4
D 5
	"i2",	"Alternate initialization string",
E 5
I 5
D 8
	"i2",	"Initialization string (used by sysline(1))",
E 8
I 8
	"k0",	"Sent by function key 0",
	"k1",	"Sent by function key 1",
	"k2",	"Sent by function key 2",
	"k3",	"Sent by function key 3",
	"k4",	"Sent by function key 4",
	"k5",	"Sent by function key 5",
	"k6",	"Sent by function key 6",
	"k7",	"Sent by function key 7",
	"k8",	"Sent by function key 8",
	"k9",	"Sent by function key 9",
E 8
E 5
E 4
	"kb",	"Sent by backspace key",
D 8
	"kd",	"Sent down arrow key",
E 8
I 8
	"kd",	"Sent by down arrow key",
E 8
	"ke",	"Out of \"keypad transmit\" mode",
	"kh",	"Sent by home key",
	"kl",	"Sent by left arrow key",
I 8
	"km",	"Has a \"meta\" key (shift, sets parity bit)",
E 8
	"kn",	"Number of \"other\" keys",
	"ko",	"Tc entries for other non-function keys",
	"kr",	"Sent by right arrow key",
	"ks",	"Put in \"keypad transmit\" mode",
	"ku",	"Sent by up arrow key",
I 8
	"l0",	"Label on function key 0 (if not \"0\")",
	"l1",	"Label on function key 1 (if not \"1\")",
	"l2",	"Label on function key 2 (if not \"2\")",
	"l3",	"Label on function key 3 (if not \"3\")",
	"l4",	"Label on function key 4 (if not \"4\")",
	"l5",	"Label on function key 5 (if not \"5\")",
	"l6",	"Label on function key 6 (if not \"6\")",
	"l7",	"Label on function key 7 (if not \"7\")",
	"l8",	"Label on function key 8 (if not \"8\")",
	"l9",	"Label on function key 9 (if not \"9\")",
E 8
I 6
	"le",	"Move left",
E 6
	"li",	"Number of lines on screen or page",
	"ll",	"Last line, first column (if no cm)",
	"ma",	"Arrow key map, used by vi V2 only",
I 6
	"mb",	"Enter blinking mode",
	"md",	"Enter bold mode",
	"me",	"Reset video attributes",
	"mh",	"Enter halfbright mode",
E 6
	"mi",	"Safe to move while in insert mode",
I 6
	"mk",	"Enter protected mode",
E 6
	"ml",	"Memory lock on above cursor.",
I 8
	"mp",	"Turn on protected attribute",
E 8
I 6
	"mr",	"Enter reverse video mode",
E 6
	"ms",	"Ok to move while in standout/underline mode",
	"mu",	"Memory unlock (turn off memory lock).",
	"nc",	"No working CR (DM2500,H2000)",
	"nd",	"Non-destructive space (cursor right)",
	"nl",	"Newline character (default \\n)",
	"ns",	"Is a CRT but doesn't scroll.",
	"os",	"Terminal overstrikes",
I 8
	"pb",	"Lowest baud where delays are required",
E 8
	"pc",	"Pad character (rather than null)",
I 8
	"pl",	"Program function key N to execute string S (terminfo only)",
E 8
	"pt",	"Has hardware tabs (may need to use is)",
I 8
	"rc",	"Restore cursor to position of last sc",
	"rf",	"Name of file containing reset codes",
	"rs",	"Reset terminal completely to sane modes",
	"sc",	"Save cursor position",
E 8
	"se",	"End stand out mode",
	"sf",	"Scroll forwards",
	"sg",	"Number of blank chars left by so/se",
	"so",	"Begin stand out mode",
	"sr",	"Scroll reverse (backwards)",
I 8
	"st",	"Set a tab in all rows, current column",
E 8
	"ta",	"Tab (other than ^I or with padding)",
	"tc",	"Entry of similar terminal - must be last",
	"te",	"String to end programs that use cm",
	"ti",	"String to begin programs that use cm",
	"ts",	"To status line sequence",
	"uc",	"Underscore one char and move past it",
	"ue",	"End underscore mode",
	"ug",	"Number of blank chars left by us or ue",
	"ul",	"Underlines, though no overstrike",
	"up",	"Upline (cursor up)",
	"us",	"Start underscore mode",
	"vb",	"Visible bell (may not move cursor)",
	"ve",	"Sequence to end open/visual mode",
	"vs",	"Sequence to start open/visual mode",
I 8
	"vt",	"Virtual terminal number (not supported on all systems)",
E 8
	"xb",	"Beehive (f1=escape, f2=ctrl C)",
	"xn",	"A newline is ignored after a wrap (Concept)",
	"xr",	"Return acts like ce \\r \\n (Delta Data)",
	"xs",	"Standout not erased by writing over it (HP 264?)",
	"xt",	"Destructive tabs, magic so char (Teleray 1061)"
};
I 8

#define NOCAPS	(sizeof capList / sizeof *capList)
E 8

E 3
#ifdef DEBUG
int		Dflag = NO;
#endif
int		xflag = NO;
D 2
int		sflag = YES;
E 2
I 2
int		Sflag = YES;
int		sflag = NO;
E 2
int		dflag = NO;
int		nflag = NO;
int		gflag = NO;
int		bflag = NO;
I 6
int		Uflag = NO;
E 6
int		tc_loopc;		/* loop counter */
char		*tcfile;		/* termcap database pathname */
I 10
char		cwd[MAXPATHLEN];	/* current working directory */
E 10
D 7
char		tcbuf[1024];		/* buffer for termcap description */
E 7
I 7
char		tcbuf[2048];		/* buffer for termcap description */
E 7
char		*lastchar();
int		name_cmp();
int		ent_cmp();
struct TcName	*find_name();
char		*getenv();
char		*ctime();
char		*strncpy();
long		ftell();

main(argc, argv, envp)
	int		argc;
	char		**argv;
	char		**envp;
{
	char		*av;
	struct TcName	*tn;
	register char	*bp;
	long		pos;
	int		n;
	struct stat	st;
	char		envbuf[256];
	FILE		*tcfp;

	if ((bp = getenv("TERMCAP")) && *bp == '/')
		tcfile = bp;
	else
		tcfile = "/etc/termcap";

	while (--argc > 0)
	{
		if (*(av = *++argv) == '-')
		{
			while (*++av)
			{
				switch (*av)
				{
				/* use alternate termcap file */
				case 'f':
					if (argc-- <= 0)
					{
						fprintf(stderr,
						    "-f needs a filename\n");
						exit(1);
					}
					tcfile = *++argv;
					break;

				/* only check for dup names */
D 4
				case 'n':
E 4
I 4
				case 'd':
E 4
					nflag = YES;
					/* fall thru */

				/* look for duplicated names */
D 4
				case 'd':
E 4
I 4
				case 'D':
E 4
					dflag = YES;
					continue;

I 6
				case 'U':
					Uflag = YES;
					continue;

E 6
I 2
				/* strip the two name off */
				case 's':
					sflag = YES;
					continue;

E 2
				/* sort the name array */
				case 'S':
D 2
					sflag = NO;
E 2
I 2
					Sflag = NO;
E 2
					continue;

#ifdef DEBUG
D 4
				case 'D':
E 4
I 4
				case 'T':
E 4
					Dflag = YES;
					continue;
#endif

				/* sort on generic names */
				case 'g':
					gflag = YES;
					continue;

				/* expand entries in 'full mode' */
				case 'x':
					xflag = YES;
					continue;

				/* show bare entry */
				case 'b':
					bflag = YES;
					continue;

				default:
					fprintf(stderr, "showtc: unknown flag: -%c\n", *av);
					fprintf(stderr, USAGE, argv[0]);
					exit(1);
				}
			}
		}
		else
			break;
	}

	/*
	 * insert the specified TERMCAP file into the environment
	 */
I 10
	if (*tcfile != '/') {
		char	*getwd();

		if (getwd(cwd) == NULL) {
			fprintf(stderr, "showtc: %s\n", cwd);
			exit(1);
		} else if (strlen(cwd) + strlen(tcfile) + 2 > sizeof cwd) {
			fprintf(stderr, "showtc: %s\n",
				"Current working directory name too long");
			exit(1);
		} else {
			if (cwd[strlen(cwd) - 1] != '/')
				strcat(cwd, "/");
			strcat(cwd, tcfile);
			tcfile = cwd;
		}
	}
E 10
	(void) sprintf(envbuf, "TERMCAP=%s", tcfile);
	while (*envp)
	{
		if (strncmp(*envp, "TERMCAP=", 8) == 0)
		{
			*envp = envbuf;
			break;
		}
		envp++;
	}
	if (! *envp)
		*envp = envbuf;	/* this may be dangerous */

	/*
	** if user specified type(s), do only those
	*/
	if (argc > 0)
	{
		/*
		** look for the users specified term types
		*/
		while (argc > 0)
		{
			switch (n = tgetent(tcbuf, *argv))
			{
				case 1:
					if (bflag)
						(void) prnt_raw(tcbuf);
					else
						(void) prnt_ent(tcbuf);
					break;

				case 0:
					fprintf(stderr,
					   "showtc: bad entry: %s\n", *argv);
					break;

				case -1:
					fputs("showtc: ", stderr);
					perror(tcfile);
					exit(1);

				default:
					fprintf(stderr, "bad return from tgetent: %d\n", n);
					exit(1);
			}
			argc--;
			argv++;
		}
		exit(0);
	}

	if (bflag)
	{
 		fprintf(stderr, "showtc: -b flag with no entries makes no sense.\n");
		exit(1);
	}


	/*
	** if no type was specified, do the whole file
	*/
	if ((tcfp = fopen(tcfile, "r")) == NULL)
	{
		perror(tcfile);
		exit(1);
	}

	/*
	** identify database, for the record
	*/
	if (stat(tcfile, &st))
	{
		perror(tcfile);
		exit(1);
	}
	printf("File: %s, last modified: %s\n", tcfile, ctime(&st.st_mtime));

	
	/*
	** build termcap entry table
	*/
	tn = tcNames;
	pos = ftell(tcfp);
	bp = tcbuf;
	while (fgets(bp, sizeof (tcbuf), tcfp) != NULL)
	{
		if (tcbuf[0] == '#')
		{
			pos = ftell(tcfp);
			bp = tcbuf;
			continue;
		}

		tn->file_pos = pos;

		/*
		** get full entry
		*/
		while (*(bp = lastchar(bp)) == '\\' && fgets(bp, (sizeof tcbuf) - (bp - tcbuf), tcfp))
			;
		/*
		** save the names
		*/
		for (bp = tcbuf; *bp && *bp != ':'; bp++)
			;
		*bp = '\0';
		(void) strncpy(tn->name_buf, tcbuf,
				sizeof tcNames[0].name_buf);

		pos = ftell(tcfp);
		bp = tcbuf;
		tn++;
	}
	tn->file_pos = -1;

	/*
	** Look for duplicate names
	*/
	if (dflag)
		check_dup();
	if (nflag)
		exit(0);

#ifdef DEBUG
	if (Dflag)
	{
		for (tn = tcNames; tn->file_pos >= 0; tn++)
		{
			printf("Entry #%d:\n\t%s\n\tfile_pos = %ld\n",
			tn - tcNames, tn->name_buf, tn->file_pos);
		}
		exit(0);
	}
#endif

	/*
	** Order the list
	*/
D 2
	if (sflag)
E 2
I 2
	if (Sflag)
E 2
		qsort((char *)tcNames, tn - tcNames,
			sizeof (struct TcName), name_cmp);

	/*
	** List termcap entry for each name in table
	*/
	for (tn = tcNames; tn->file_pos >= 0; tn++)
	{
		tc_loopc = 0;
		/*** working toward this ...
		(void) prnt_ent(tn);
		***/
		(void) fseek(tcfp, tn->file_pos, 0);
		bp = tcbuf;
		while (fgets(bp, (sizeof tcbuf) - (bp - tcbuf), tcfp)
			&& *(bp = lastchar(bp)) == '\\')
			;
		(void) prnt_ent(tcbuf);
	}
}

char *
lastchar(b)
	char	*b;
{
	register char	*p;

	p = b + strlen(b) - 1;
	while (*p == '\n' || *p == ' ')
		p--;
	return(p);
}

name_cmp(a, b)
	char	*a, *b;
{
	if (gflag)	/* sort on generic names */
	{
		a += 3;
		b += 3;
		while (*a && *b && *a != '|' && *a == *b)
		{
			a++;
			b++;
		}
		if (*a == '|' || *a == CNULL)
			return((*b == '|' || *b == CNULL)? 0:-1);
		if (*b == '|' || *b == CNULL)
			return(1);
		return(*a - *b);
	}
	return(strncmp(a, b, 2));
}

prnt_ent(buf)
	register char	*buf;
{
	register char	*name;
I 3
	char		*getdesc();
E 3
	char		*caps[256];
	register char	**cp;
	register char	**tp;
	char		tname[3];

	cp = caps;
	name = buf;
	tname[3] = '\0';

	while (*buf)
	{
		switch (*buf)
		{
		case ':':
			*buf++ = '\0';
			while (*buf && !isalnum(*buf))
				buf++;
			if (*buf)
			{
				/*
				 * ignore duplicate cap entries
				 */
				for (tp = caps; tp < cp; tp++)
					if (strncmp(buf, *tp, 2) == 0)
						goto skip;
				*cp++ = buf;
			skip:
				/*
				 * does user want tc= expanded?
				 */
				if (xflag && strncmp(buf, "tc=", 3) == 0)
				{
					/*
					 * find end of tc=
					 */
					while (*buf != ':')
						buf++;
					*buf = '\0';
					/*
					 * save term name
					 */
					tname[0] = name[0];
					tname[1] = name[1];
					printf("%s: expanding %s\n",
						tname, cp[-1]);
					/*
					 * let tgetent do the work
					 */
					tgetent(tcbuf, tname);
					prnt_ent(tcbuf);
					return;
				}
			}
			continue;

		case '|':
			*buf++ = ',';
			continue;

		default:
			buf++;
		}
	}
	*cp = CNULL;		/* was (char *)0 */

D 2
	if (sflag)
E 2
I 2
	if (Sflag)
E 2
		qsort((char *) caps, cp - caps, sizeof (char *), ent_cmp);

	printf("%s\n", name);
	for (cp = caps; *cp; cp++)
D 2
		printf("%2.2s	%s\n", name, *cp);
E 2
I 2
D 6
		if (sflag)
E 6
I 6
		if (Uflag) {
			if (unknowncap(*cp)) {
				printf("%3.3s\n", *cp);
			}
		} else if (sflag) {
E 6
D 3
			printf("	%s\n", *cp);
E 3
I 3
			printf("%-45s %s\n", getdesc(*cp), *cp);
E 3
D 6
		else
D 3
			printf("%2.2s	%s\n", name, *cp);
E 3
I 3
		{
E 6
I 6
		} else {
E 6
			printf("%2.2s  %-45s %s\n", name, getdesc(*cp), *cp);
		}
E 3
E 2
	(void) putchar('\n');
}

prnt_raw(buf)
	char		*buf;
{
	register char	*b;
	register int	len;
	register int	n;
	char		*index();

	len = 0;
	b = buf;
	while (*b)
	{
		if ((n = index(b, ':') - b + 1) <= 0)
			n = strlen(b);
		if (len == 0)			/* first part */
		{
			printf("%.*s\\\n\t:", n, b);
			len = 9 - n;
		}
		else
		{
			if ((len + n) >= 75)
			{
				printf("\\\n\t:");
				len = 9;
			}
			printf("%.*s", n, b);
		}
		len += n;
		b += n;
		while (*b && index(" \t:\n", *b))
			b++;
	}
	if (b[-1] != ':')
		(void) putchar(':');
	(void) putchar('\n');
}

ent_cmp(a, b)
	char **a, **b;
{
	return(strncmp(*a, *b, 2));
}

check_dup()
{
	/*
	** Look for duplicated names
	*/
	register char		*p;
	register char		*q;
	register struct TcName	*tn;
	register struct TcName	*tm;

	tn = tcNames;
	while (tn->file_pos >= 0)
	{
		p = q = tn->name_buf;
		while (*q)
		{
			while (*p && *p != '|')
				p++;
			if (p != q && (tm = find_name(q, tn + 1, p - q)))
			{
				fputs("Duplicate name: ", stdout);
				while (q != p)
					(void) putchar(*q++);
				(void) putchar('\n');
				puts(tn->name_buf);
				puts(tm->name_buf);
				puts("---\n");
			}
			if (*p == '|')
				p++;
			q = p;
		}
		tn++;
	}
}

struct TcName *
find_name(name, tn, len)
	register char		*name;
	register struct TcName	*tn;
	register int		len;
{
	/*
	** find name of length len in tcname structure buffers.
	*/
	register char	*p;
	register char	*buf;
	register int	 n;

	while (tn->file_pos >= 0)
	{
		buf = tn->name_buf;
		while (*buf)
		{
			p = name;
			n = len;
			if (*buf == '|')
				buf++;

			while (*buf && *buf != '|')
			{
				if (*p != *buf)
				{
					while (*buf && *buf != '|')
						buf++;
					break;
				}

				if (--n <= 0)
				{
					buf++;
					if (*buf == '|' || *buf == '\0')
						return(tn);
					while (*buf && *buf != '|')
						buf++;
					break;
				}
				buf++;
				p++;
			}
		}
		tn++;
	}
	return((struct TcName *)0);
I 3
}

char *
getdesc(key)
	char		*key;
{
	register int	i;

D 10
	for (i = 0; i <= NOCAPS; i++)
E 10
I 10
	for (i = 0; i < NOCAPS; i++)
E 10
		if (strncmp(key, capList[i].cap, 2) == 0)
			return (capList[i].desc);
D 4
	return("Unknown capability");
E 4
I 4
	return("");
I 6
}

unknowncap(key)
	char		*key;
{
	register int	i;

D 10
	for (i = 0; i <= NOCAPS; i++)
E 10
I 10
	for (i = 0; i < NOCAPS; i++)
E 10
		if (strncmp(key, capList[i].cap, 2) == 0)
			return (0);
	return(1);
E 6
E 4
E 3
}
E 1
