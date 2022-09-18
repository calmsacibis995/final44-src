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
 *
 *	Time routine assumes that you have the escape character changed
 *	to ^\ (\034).  This is done so that the terminal can be used
 *	effectively with emacs.  If Time is running in the background
 *	be sure to use an emacs or vi terminal description that does not
 *	change the escape character.
 *
 *
 */

#define SET_TIME   "/Set_Time"
#define RESET_TIME "/ReSet_Time"
#define KILL_TIME "/Kill_Time"

#ifdef CONCEPT100

#define INIT	"\034U"
#define ST_LINE	"\034 */                                       /"

#else

#define INIT	"\0"
#define ST_LINE	"\033b/                                       /"

#endif CONCEPT100

#define MAIL_D	"/usr/mail/"
#define UTMP	"/etc/utmp"
#define T_BUFF	128

extern int      Sig_on ();
extern int      Sig_off ();
char    Donep;				/* Set_Time - ReSet_Time flag state */

main (argc, argv)
int     argc;
char  **argv;
{
	int     Dis_len;		/* The display line */
	char    Display[T_BUFF];	/* 50 would do it */

	FILE * fu;			/* For Reading /etc/utmp */
	struct utmp     ubuf;
	struct stat     u_buf;
	struct stat     ou_buf;
	int     U_count = 0;

	FILE * fm;			/* For Reading Mail */
	char    Mail[T_BUFF];		/* 26 would do it */
	char    RM_buf[T_BUFF * 4];
	char    Mailp = 1;
	struct stat     m_buf;
	struct stat     om_buf;
	int     M_count = 0;
	int     old_count;

	long    Time_loc;		/* Internal Time */
	char   *C_time;

	int     zzz;			/* Sleep duration */

	if (argc < 3)
	{
		fprintf (stderr,
			"Usage: Time bin-directory-name delay-time\n");
		exit (1);
	}

 /* Setup the shell file commands */

	sprintf (Mail, "%s%s", argv[1], SET_TIME);
	if ((fu = fopen (Mail, "w")) != NULL)
	{
		fprintf (fu, "kill -16 %d\n", getpid ());
		fclose (fu);
		chmod (Mail, 0755);
	}
	else
	{
		fprintf (stderr, "Time: Cannot open %s\n", Mail);
		exit (1);
	}

	sprintf (Mail, "%s%s", argv[1], RESET_TIME);
	if ((fu = fopen (Mail, "w")) != NULL)
	{
		fprintf (fu, "kill -17 %d\n", getpid ());
		fclose (fu);
		chmod (Mail, 0755);
	}
	else
	{
		fprintf (stderr, "Time: Cannot open %s\n", Mail);
		exit (1);
	}

	sprintf (Mail, "%s%s", argv[1], KILL_TIME);
	if ((fu = fopen (Mail, "w")) != NULL)
	{
		fprintf (fu, "kill -9 %d\n", getpid ());
		fclose (fu);
		chmod (Mail, 0755);
	}
	else
	{
		fprintf (stderr, "Time: Cannot open %s\n", Mail);
		exit (1);
	}

	Donep = 0;

	Dis_len = sprintf (Mail, MAIL_D);/* Construct the Mail file name */
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
	fu = fopen (UTMP, "r");
	signal (SIGUSR1, Sig_on);
	signal (SIGUSR2, Sig_off);

	for(Dis_len = 45; Dis_len < 65; Dis_len++) Display[Dis_len] = '\0';

	while (1)
	{
		strcpy (Display, ST_LINE);
		Time_loc = (long) time (0);
		C_time = ctime (&Time_loc);
		for (Dis_len = 4; Dis_len < 23;
					Display[Dis_len++] = *C_time++);

		if (fu != NULL)		/* The number of users */
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
						if (ubuf.ut_type == USER_PROCESS)
							U_count++;
					}

				}
			}
			Dis_len += sprintf (&Display[Dis_len],
							"  Users:%d", U_count);
			Display[Dis_len] = ' ';
		}

		if (Mailp)		/* The number of messages */
		{
			if (stat (Mail, &m_buf) != -1)
			{
				if (m_buf.st_mtime > om_buf.st_mtime)
				{
					om_buf.st_mtime = m_buf.st_mtime;
					if ((fm = fopen (Mail, "r")) != NULL)
					{
						old_count = M_count;
						M_count = 0;
						while (fgets (RM_buf,
							sizeof RM_buf, fm))
						{
							if (strncmp (RM_buf,
							    "From ", 5) == 0)
								M_count++;
						}
						fclose (fm);
						if (old_count < M_count)
							write (1, "\07\07\07\07\07\07", 6);
					}
				}

				if (M_count)
				{
					Dis_len += sprintf (&Display[Dis_len],
							"  Msgs:%d", M_count);
				}
			}
		}

		if (Donep)
		{
#ifdef CONCEPT100
			Display[Dis_len++] = ' ';
			Display[42] = '\014';
			Dis_len = 43;
#else
			Dis_len += sprintf (&Display[Dis_len], "  Signal!");
#endif CONCEPT100
		}

		Display[Dis_len++] = '/';
		ioctl (1, TCSBRK, -1);	/* ioctl's are most likely ineffective 
					*/
		write (1, Display, Dis_len);		/* Add some padding */
/*		ioctl (1, TCSBRK, -1);	*/
		sleep (zzz);
	}
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
