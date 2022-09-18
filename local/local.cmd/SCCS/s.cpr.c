h16013
s 00085/00003/00149
d D 1.8 82/11/14 10:59:08 eric 9 8
c make overstriking work
e
s 00017/00008/00135
d D 1.7 82/08/08 14:11:19 eric 8 7
c -e => echo on terminal during printing
e
s 00001/00001/00142
d D 1.6 82/07/25 13:29:48 eric 7 6
c expand tabs
e
s 00011/00011/00132
d D 1.5 82/07/25 13:21:03 eric 6 5
c fix botch in flag processing
e
s 00036/00004/00107
d D 1.4 82/07/25 13:13:45 eric 5 4
c -f => form feed following print
e
s 00009/00000/00102
d D 1.3 82/07/25 12:43:55 eric 4 3
c stop $SYSLINE during the printing (requires external convention)
e
s 00003/00002/00099
d D 1.2 82/07/25 12:25:50 eric 3 1
c don't echo on crt as you print
e
s 00016/00009/00092
d D 1.1.1.1 82/07/25 12:21:54 eric 2 1
c try printing one line at a time to maintain sysline -- doesn't work
e
s 00101/00000/00000
d D 1.1 82/07/25 12:21:07 eric 1 0
c date and time created 82/07/25 12:21:07 by eric
e
u
U
f b 
f i 
t
T
I 1
# include <stdio.h>
# include <sgtty.h>
# include <signal.h>

static char	SccsId[] =	"%W%	%Y%	%G%";

/*
**  CPR -- print on concept 108
**
**	This filter arranges to output onto a printer connected
**	to a Concept 108 terminal.  It probably works on other
**	models in the Concept 100 series also.
**
**	Usage:
D 5
**		cpr [file ...]
E 5
I 5
**		cpr [-f] [file ...]
**
**	Flags:
**		-f	form feed following to print.
E 5
*/

I 9
#define LINELEN	132			/* carriage width */

E 9
I 5
typedef char	bool;
#define TRUE	1
#define FALSE	0

E 5
struct sgttyb	tbuf;
I 4
D 8
int		SysLine;
I 5
bool		FormFeedFollowing;
E 8
I 8
int		SysLinePid;		/* pid of sysline process */
bool		FormFeedFollowing;	/* print form feed following print */
bool		EchoDuringPrint;	/* echo on terminal while printing */
E 8
E 5
E 4

main(argc, argv)
	int argc;
	char **argv;
{
	register char *p;
	extern cleanterm();
I 4
	extern char *getenv();
E 4

I 5
	/* arrange to stop the sysline program during printing */
	p = getenv("SYSLINE");
	if (p != NULL)
D 8
		SysLine = atoi(p);
E 8
I 8
		SysLinePid = atoi(p);
E 8

	/* process arguments */
	while (--argc > 0)
	{
		p = *++argv;
D 6
		if (*p == '-')
E 6
I 6
		if (*p != '-')
			break;
		switch (*++p)
E 6
		{
D 6
			switch (*++p)
			{
			  case 'f':
				FormFeedFollowing = TRUE;
				break;
			}
E 6
I 6
		  case 'f':
			FormFeedFollowing = TRUE;
			break;
I 8

		  case 'e':
			EchoDuringPrint = TRUE;
			break;
E 8
E 6
		}
	}

E 5
	/* be nice on interrupts, etc. */
	signal(SIGINT, cleanterm);

	/* set the terminal to output to printer */
I 4
D 5
	p = getenv("SYSLINE");
	if (p != NULL)
		SysLine = atoi(p);
E 5
E 4
	setupterm();

	/* print the appropriate files */
D 6
	if (argc < 2)
E 6
I 6
	if (argc < 1)
E 6
		copyfile();
	else
	{
D 6
		while (--argc > 0)
E 6
I 6
		while (argc-- > 0)
E 6
		{
D 6
			if (freopen(*++argv, "r", stdin) == NULL)
				perror(*argv);
E 6
I 6
			p = *argv++;
			if (freopen(p, "r", stdin) == NULL)
				perror(p);
E 6
			else
				copyfile();
		}
	}

	/* reset terminal to a nice state */
	cleanterm();
}

copyfile()
{
D 9
	char buf[200];
I 2
	register char *p;
	extern char *index();

E 2
	while (fgets(buf, sizeof buf, stdin) != NULL)
D 2
		fputs(buf, stdout);
E 9
I 9
	int c;
	int col;
	register char *p;
	char bufa[LINELEN + 1];
	char bufb[LINELEN + 2];
	char bufc[LINELEN + 1];
	char bufd[LINELEN + 2];

  clearbuf:
	for (col = 0; col <= LINELEN; col++)
		bufa[col] = bufb[col] = bufc[col] = bufd[col] = ' ';
	col = 0;
	while ((c = getchar()) != EOF)
	{
		switch (c)
		{
		  case '\b':
			if (col > 0)
				col--;
			break;

		  case '\r':
			col = 0;
			break;

		  case ' ':
			col++;
			break;

		  case '\t':
			col = (col + 8) & ~07;
			break;

		  case '\n':
			putout(bufa, FALSE);
			putout(bufb, TRUE);
			putout(bufc, TRUE);
			putout(bufd, TRUE);
			col = 0;
			putchar('\n');
			goto clearbuf;

		  default:
			if (col >= LINELEN)
				col++;
			else if (bufa[col] == ' ')
				bufa[col++] = c;
			else if (bufb[col] == ' ')
				bufb[col++] = c;
			else if (bufc[col] == ' ')
				bufc[col++] = c;
			else if (bufd[col] == ' ')
				bufd[col++] = c;
			else
			{
				int i;

				putout(bufa, FALSE);
				putchar('\r');
				for (i = 0; i < LINELEN; i++)
					bufa[i] = ' ';
				bufa[col++] = c;
			}
		}
	}
}

putout(buf, cr)
	char buf[];
	bool cr;
{
	register char *p;

	/* find the end of the line */
	for (p = &buf[LINELEN-1]; p >= buf && *p == ' '; p--)
		continue;
	*++p = '\0';
	if (buf[0] == '\0')
		return;
	if (cr)
		putchar('\r');
	for (p = buf; *p != '\0'; p++)
		putchar(*p);
E 9
E 2
I 2
	{
		p = index(buf, '\n');
		if (p == NULL)
			continue;
		*p = '\r';
		printf("\033 5%s\033|", buf);
		if (getack() < 0)
		{
			fprintf(stderr, "Lost printer\n");
			cleanterm();
		}
		fputs("\n", stdout);
	}
E 2
}

setupterm()
{
	int oldflags;

	if (gtty(1, &tbuf) < 0)
	{
		perror("cpr: stdout");
		exit(1);
	}
	oldflags = tbuf.sg_flags;
	tbuf.sg_flags &= ~ECHO;
D 7
	tbuf.sg_flags |= CBREAK;
E 7
I 7
	tbuf.sg_flags |= CBREAK | XTABS;
E 7
	stty(1, &tbuf);
	tbuf.sg_flags = oldflags;
I 4
D 8
	if (SysLine > 0)
		kill(SysLine, SIGSTOP);
E 4
D 2
D 3
	fputs("\033}", stdout);
E 3
I 3
	fputs("\033Y$", stdout);
E 8
I 8
	if (SysLinePid > 0)
		kill(SysLinePid, SIGSTOP);
	fputs("\033Y", stdout);
	if (EchoDuringPrint)
		fputs("4", stdout);
	else
		fputs("$", stdout);
E 8
E 3
	if (getack() >= 0)
		return;
	fprintf(stderr, "Cannot attach printer\n");
	resetmodes();
	exit(1);
E 2
}

cleanterm()
{
I 5
	/* output trailing formfeed */
	if (FormFeedFollowing)
		fputs("\r\f", stdout);

	/* disconnect printer */
E 5
D 2
D 3
	printf("\033~");
E 3
I 3
	printf("\033Y0");
	getack();
E 3
	fflush(stdout);
I 5

	/* back to the real world.... */
E 5
E 2
	resetmodes();
	exit(0);
}

getack()
{
	char buf[1];

	fflush(stdout);
	if (read(2, buf, 1) <= 0 || buf[0] != '\006')
		return (-1);
	return (0);
}

resetmodes()
{
	stty(1, &tbuf);
I 4
D 8
	if (SysLine > 0)
		kill(SysLine, SIGCONT);
E 8
I 8
	if (SysLinePid > 0)
		kill(SysLinePid, SIGCONT);
E 8
E 4
}
E 1
