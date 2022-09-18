/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termio.h>
#include <utmp.h>
#include <signal.h>
#include <ctype.h>

#ifdef UCB
#define sprintf usg_sprintf
#endif

/*
 *
 *	Clock, mail, user count, and end of process signaler for c1008p
 *	or Blit/etty status line - could be modified for use with Zenith
 *	H19
 *
 *	Calling sequence:
 *
 *		$ Time /usr/blewett/bin.d 15 &
 *	 or
 *		$ nice -19 Time /usr/blewett/bin.d 15 &
 *
 *	The first argument is the name of a writable directory that is
 *	included in your PATH.  Time related shell commands are placed
 *	in this directory.
 *
 *	The second argument is the delay between updates.  Users should
 *	probably turn off all other checking for mail (i.e. MAIL="").
 *
 *	This routine setups two shell commands that toggle (via signals)
 *	the ready indicator at the end of the status line.  These
 *	commands have to be recreated because they must know the PID of
 *	the Time process.
 *
 *	The command "Set_Time" will turn the ready indicator on.
 *
 *		 $ sh -c "nroff -mm files etc. > hmmm ; Set_Time" &
 *
 *	The command "ReSet_Time" will turn the ready indicator off.
 *	The command "Kill_Time" will kill the time background process.
 *	The command "Time_Reset" will reset the Conecpt108 windows
 *		(this is useful after accidental resets, etc.
 *
 */

#define SET_TIME   "/Set_Time"
#define RESET_TIME "/ReSet_Time"
#define KILL_TIME "/Kill_Time"

#ifdef CONCEPT100

#define INIT	"\033U"
#define ST_LINE	"\033 *@                                       @"
#define TERM_CHAR '@'
#define ST_LEN 4

#else

#define INIT	"\0"
#define ST_LINE	"\033b@                                       @"
#define TERM_CHAR '@'
#define ST_LEN 3

#endif CONCEPT100

#define MAIL_D	"/usr/mail/"
#define UTMP	"/etc/utmp"
#define T_BUFF	128

extern char *GetText ();

 /* Text for cron messages */
#define MSG_LEN 40
char    Msg_Text[10][MSG_LEN];
char    Cron_File[T_BUFF];

extern char *ctime ();
int     Sig_on (), Sig_off ();
char    Donep;
short   MsgCount = 0;

main (argc, argv)
int     argc;
char  **argv;
{
    int     Dis_len;			/* The display line */
    char    Display[T_BUFF];		/* 50 would do it */
    FILE * fp;
    char    Mail[T_BUFF];		/* 26 would do it */
    char    Mailp = 1;
    int     zzz;			/* Sleep duration */
    time_t itime;			/* Internal Time */
    short   text_cnt;
    short   i;

    if (argc < 3)
    {
	fprintf (stderr,
		"Usage: Time bin-directory-name delay-time\n");
	exit (1);
    }

 /* Setup the Set_Time and ReSet_Time commands */

    sprintf (Mail, "%s%s", argv[1], SET_TIME);
    if ((fp = fopen (Mail, "w")) != NULL)
    {
	fprintf (fp, "kill -16 %d\n", getpid ());
	fclose (fp);
	chmod (Mail, 0755);
    }
    else
    {
	fprintf (stderr, "Time: Cannot open %s\n", Mail);
	exit (1);
    }

    sprintf (Mail, "%s%s", argv[1], RESET_TIME);
    if ((fp = fopen (Mail, "w")) != NULL)
    {
	fprintf (fp, "kill -17 %d\n", getpid ());
	fclose (fp);
	chmod (Mail, 0755);
    }
    else
    {
	fprintf (stderr, "Time: Cannot open %s\n", Mail);
	exit (1);
    }

    sprintf (Mail, "%s%s", argv[1], KILL_TIME);
    if ((fp = fopen (Mail, "w")) != NULL)
    {
	fprintf (fp, "kill -9 %d\n", getpid ());
	fclose (fp);
	chmod (Mail, 0755);
    }
    else
    {
	fprintf (stderr, "Time: Cannot open %s\n", Mail);
	exit (1);
    }

    Donep = 0;

    Dis_len = sprintf (Mail, MAIL_D);	/* Construct the Mail file name */
    if (sprintf (Cron_File, "%s/.cron_file", (char *) getenv ("HOME")) < 0)
	*Cron_File = (char) 0;
    if (sprintf (&Mail[Dis_len], "%s", (char *) getenv ("LOGNAME")) < 0)
	Mailp = (char) 0;

 /* Get the sleep value */
    sscanf (argv[2], "%d", &zzz);
    if (zzz < 1)
    {
	fprintf (stderr, "Time: delay value less than 1\n");
	exit (1);
    }

    write (1, INIT, strlen (INIT));	/* Init stuff: Programmer mode */
    signal (SIGUSR1, Sig_on);
    signal (SIGUSR2, Sig_off);

    for (Dis_len = 45; Dis_len < 65; Dis_len++)
	Display[Dis_len] = '\0';

    freopen ("/dev/null", "w", stderr);
    while (1)
    {
	itime = (time_t) time (0);
	text_cnt = cron_text (itime);

	strcpy (Display, ST_LINE);
	Dis_len = ST_LEN;
	switch (MsgCount)
	{
	    case 0: 
	    default: 
		for (i = 0; i < text_cnt; i++)
		{
		    strcpy (Display, ST_LINE);
		    Dis_len = ST_LEN;
#ifdef CONCEPT
		    Dis_len += sprintf (&Display[Dis_len],
			    "%.30s", GetText (Msg_Text[i]));
#else
		    Dis_len += sprintf (&Display[Dis_len],
			    "%s", GetText (Msg_Text[i]));
		    while (Display[Dis_len - 1] == ' ')
		    	Dis_len--;
#endif CONCEPT
		    Display[Dis_len++] = TERM_CHAR;
		    write (1, Display, Dis_len);
		    sleep (2);
		}
		strcpy (Display, ST_LINE);
		Dis_len = ST_LEN;
		Dis_len += D_time (&Display[Dis_len], itime);
		Dis_len += D_user (&Display[Dis_len]);

		if (Mailp)
		{			/* The number of messages */
		    Dis_len += D_mail (Mail, &Display[Dis_len]);
		    Display[Dis_len++] = ' ';
		}
		MsgCount = 0;
		break;
	}				/* End of Switch */
	MsgCount++;

	if (Donep)
	{
#ifdef CONCEPT100
	    Display[42] = '\014';
	    Dis_len = 43;
#else
	    Dis_len += sprintf (&Display[Dis_len], "Signal!");
#endif CONCEPT100
	}

	Display[Dis_len++] = TERM_CHAR;

	ioctl (1, TCSBRK, -1);		/* ioctl's are most likely ineffective 
					*/
	write (1, Display, Dis_len);	/* Add some padding */
/*
	ioctl (1, TCSBRK, -1);
*/
	    sleep (zzz);
    }
}

int
D_time (buf, itime)
time_t itime;
char    buf[];
{
    char   *C_time;
    short   i;

    C_time = ctime (&itime);
    for (i = 0; i < 19; i++)
	buf[i] = *C_time++;
    buf[i++] = ' ';
    return (i);
}


int
D_clock (buf, itime)
time_t itime;
char    buf[];
{
    char   *C_time;
    short   i;

    C_time = ctime (&itime);
    C_time += 11;
    for (i = 0; i < 8; i++)
	buf[i] = *C_time++;
    buf[i++] = ' ';
    return (i);
}

int
D_user (buf)
char    buf[];
{
    static  FILE * fu = NULL;		/* For Reading /etc/utmp */
    struct utmp ubuf;
    struct stat u_buf;
    static struct stat  ou_buf;
    static int  U_count = 0;
    short   i = 0;

    if (fu == NULL)
    {
	fu = fopen (UTMP, "r");
    }

    if (fu != NULL)			/* The number of users */
    {
	if (stat (UTMP, &u_buf) != -1)
	{
	    if (u_buf.st_mtime > ou_buf.st_mtime)
	    {
		ou_buf.st_mtime = u_buf.st_mtime;
		U_count = 0;
		rewind (fu);
		while (fread (&ubuf, sizeof ubuf, 1,
			    fu) == 1)
		{
		    if (ubuf.ut_type != USER_PROCESS)
			continue;
		    U_count++;
		}
	    }
	}
	i += sprintf (&buf[i], " Users:%d", U_count);
	buf[i++] = ' ';
    }
    return (i);
}

D_mail (mail_file, buf)
char    buf[];
char   *mail_file;
{
    FILE * fm;				/* For Reading Mail */
    char    RM_buf[T_BUFF * 4];
    struct stat m_buf;
    static struct stat  om_buf;
    static int  M_count = 0;
    short   i = 0;

    if (stat (mail_file, &m_buf) != -1)
    {
	if (m_buf.st_mtime > om_buf.st_mtime)
	{
	    om_buf.st_mtime = m_buf.st_mtime;
	    if ((fm = fopen (mail_file, "r")) != NULL)
	    {
		M_count = 0;
		while (fgets (RM_buf, sizeof RM_buf, fm))
		{
		    if (strncmp (RM_buf, "From ", 5) == 0)
			M_count++;
		}
		fclose (fm);
	    }
	}
	if (M_count)
	{
	    i += sprintf (&buf[i], " Msgs:%d", M_count);
	    buf[i++] = ' ';
	}
    }
    return (i);
}

Sig_on ()
{
    signal (SIGUSR1, Sig_on);
    Donep = 1;
}

Sig_off ()
{
    signal (SIGUSR2, Sig_off);
    Donep = 0;
}



/*	defines for the cron function	*/

#define	LISTS	512
#define HOUR	3600
#define	EXACT	123
#define	ANY	124
#define	LIST	125
#define	RANGE	126
#define	EOS	127

extern struct tm   *localtime ();
extern char *malloc ();
extern char *realloc ();
short   Cmp_Flag;
char   *List;
unsigned    Listsize;

#define DELTA   15*60

int
cron_text (itime)
time_t itime;
{
    register char  *cp;
    char   *cmp ();
    time_t time_plus;
    static  time_t filetime = 0;
    struct tm  *loct;
    struct stat cstat;
    static short    text_cnt = 0;
    static short    pre_minute = 0;
    short   i;

    if (stat (Cron_File, &cstat) == -1)
	return (text_cnt);

    if (cstat.st_mtime > filetime)
    {
	filetime = cstat.st_mtime;
	init ();
    }
    time_plus = itime;
    loct = localtime (&time_plus);
    if (loct -> tm_min == pre_minute)	/* only look once per minute */
	return (text_cnt);
    pre_minute = loct -> tm_min;
    text_cnt = 0;

    loct -> tm_mon++;			/* 1-12 for month */
    for (cp = List; *cp != EOS;)
    {
	Cmp_Flag = 0;
	cp = cmp (cp, loct -> tm_min);
	cp = cmp (cp, loct -> tm_hour);
	cp = cmp (cp, loct -> tm_mday);
	cp = cmp (cp, loct -> tm_mon);
	cp = cmp (cp, loct -> tm_wday);
	if (Cmp_Flag == 0)
	{
	/* get message */
	    for (i = 0; i < MSG_LEN; i++)
	    {
		if (*cp == 0)
		    Msg_Text[text_cnt][i] = '\0';
		else
		    Msg_Text[text_cnt][i] = *cp++;
		if (Msg_Text[text_cnt][i] == '\n')
		    Msg_Text[text_cnt][i] = '\0';
	    }
	    text_cnt++;
	}
	while (*cp++ != 0)
	    ;
    }
    return (text_cnt);
}

char   *
cmp (p, v)
char   *p;
{
    register char  *cp;

    cp = p;
    switch (*cp++)
    {

	case EXACT: 
	    if (*cp++ != v)
		Cmp_Flag++;
	    return (cp);

	case ANY: 
	    return (cp);

	case LIST: 
	    while (*cp != LIST)
		if (*cp++ == v)
		{
		    while (*cp++ != LIST)
			;
		    return (cp);
		}
	    Cmp_Flag++;
	    return (cp + 1);

	case RANGE: 
	    if (cp[0] < cp[1])
	    {
		if (!(cp[0] <= v && cp[1] >= v))
		    ++Cmp_Flag;
	    }
	    else
		if (!(v >= cp[0] || v <= cp[1]))
		    ++Cmp_Flag;
	    return (cp + 2);
    }
    if (cp[-1] != v)
	Cmp_Flag++;
    return (cp);
}


char    Lorange[] =
{
    0, 0, 1, 1, 0
}      , Hirange[] =
{
    59, 23, 31, 12, 6
};

init ()
{
    register    i,
                c;
    register char  *cp;
    register char  *ocp,
                   *cp2;
    register int    n;

    freopen (Cron_File, "r", stdin);
    if (List)
    {
	free (List);
	List = realloc (List, LISTS);
    }
    else
	List = malloc (LISTS);
    Listsize = LISTS;
    cp = List;

loop: 
    if (cp > List + Listsize-256)
    {
	char   *olist;
	Listsize += LISTS;
	olist = List;
	free (List);
	List = realloc (List, Listsize);
	cp = List + (cp - olist);
    }
    ocp = cp;
    for (i = 0;; i++)
    {
	do
	    c = getchar ();
	while (c == ' ' || c == '\t')
	;
	if (c == EOF || c == '\n')
	    goto ignore;
	if (i == 5)
	    break;
	if (c == '*')
	{
	    *cp++ = ANY;
	    continue;
	}
	if ((n = number (c, Lorange[i], Hirange[i])) < 0)
	    goto ignore;
	c = getchar ();
	if (c == ',')
	    goto mlist;
	if (c == '-')
	    goto mrange;
	if (c != '\t' && c != ' ')
	    goto ignore;
	*cp++ = EXACT;
	*cp++ = n;
	continue;

mlist: 
	*cp++ = LIST;
	*cp++ = n;
	do
	{
	    if ((n = number (getchar (), Lorange[i], Hirange[i])) < 0)
		goto ignore;
	    *cp++ = n;
	    c = getchar ();
	} while (c == ',');
	if (c != '\t' && c != ' ')
	    goto ignore;
	*cp++ = LIST;
	continue;

mrange: 
	*cp++ = RANGE;
	*cp++ = n;
	if ((n = number (getchar (), Lorange[i], Hirange[i])) < 0)
	    goto ignore;
	c = getchar ();
	if (c != '\t' && c != ' ')
	    goto ignore;
	*cp++ = n;
    }

    i = 0;
    while (c != '\n')
    {
	if (c == EOF)
	    goto ignore;
	if (c == '%')
	{
	    if (i == 0)
	    {
		i++;
		for (cp2 = "<< __GNOME__"; *cp++ = *cp2++;)
		    ;
		cp--;
	    }
	    c = '\n';
	}
	*cp++ = c;
	c = getchar ();
    }
    *cp++ = '\n';
    if (i)
	for (cp2 = "__GNOME__\n"; *cp++ = *cp2++;)
	    ;
    else
	*cp++ = 0;
    goto loop;

ignore: 
    cp = ocp;
    while (c != '\n')
    {
	if (c == EOF)
	{
	    *cp++ = EOS;
	    *cp++ = EOS;
	    fflush (stdin);
	    return;
	}
	c = getchar ();
    }
    goto loop;
}

number (c, lowv, highv)
register    c;
{
    register    n = 0;

    while (isdigit (c))
    {
	n = n * 10 + c - '0';
	c = getchar ();
    }
    ungetc (c, stdin);
    if (n < lowv || n > highv)
    {
	puts ("value range error");
	return - 1;
    }
    return (n);
}

char   *
GetText (line)
char   *line;
{
    FILE * pfp, *popen ();
    static char buf[BUFSIZ];
    short   len;

    if (line[0] != '/')
    /* just text */
	return (line);
    buf[0] = '\0';

 /* command to execute */
    if ((pfp = popen (line, "r")) == NULL)
    {
    /* can not execute command */
	sprintf (buf, "can't execute");
	return (buf);
    }

    len = fread (buf, 1, 30, pfp);
    if (len < 1)
    {
    /* no data in stdin */
	fflush (pfp);
	pclose (pfp);
	sprintf (buf, "no output");
	return (buf);
    }

 /* return stdin from command */
    buf[len] = '\0';
    if (buf[len - 1] == '\n')
	buf[len - 1] = '\0';
    fflush (pfp);
    pclose (pfp);
    return (buf);
}

#ifdef UCB

/* @(#)sprintf.c	4.1 (Berkeley) 12/21/80 */
#include	<stdio.h>

usg_sprintf(str, fmt, args)
char *str, *fmt;
{
	struct _iobuf _strbuf;

	_strbuf._flag = _IOWRT+_IOSTRG;
	_strbuf._ptr = str;
	_strbuf._cnt = 32767;
	_doprnt(fmt, &args, &_strbuf);
	putc('\0', &_strbuf);
	return(strlen (str));
}
#endif UCB
