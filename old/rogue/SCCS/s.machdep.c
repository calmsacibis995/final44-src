h08473
s 00007/00000/00452
d D 5.3 89/05/29 18:31:58 mckusick 4 3
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00005/00005/00447
d D 5.2 86/01/09 17:45:07 mckusick 3 2
c update for 4.3BSD (from arnol@ucsfcgl.arpa)
e
s 00016/00000/00436
d D 5.1 85/05/30 17:52:37 mckusick 2 1
c Add copyright
e
s 00436/00000/00000
d D 1.1 85/04/05 16:54:57 arnold 1 0
c date and time created 85/04/05 16:54:57 by arnold
e
u
U
t
T
I 1
/*
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

/*
E 2
 * Various installation dependent routines
 *
 * $Revision: 1.7 $, $Date: 85/04/05 11:33:30 $
 */

/*
 * The various tuneable defines are:
 *
 *	SCOREFILE	Where/if the score file should live.
 *	ALLSCORES	Score file is top ten scores, not top ten
 *			players.  This is only useful when only a few
 *			people will be playing; otherwise the score file
 *			gets hogged by just a few people.
 *	NUMSCORES	Number of scores in the score file (default 10).
 *	NUMNAME		String version of NUMSCORES (first character
 *			should be capitalized) (default "Ten").
 *	MAXLOAD		What (if any) the maximum load average should be
 *			when people are playing.
 *		LOADAV		Should it use it's own routine to get
 *				the load average?
 *		NAMELIST	If so, where does the system namelist
 *				hide?
 *	MAXUSERS	What (if any) the maximum user count should be
 *			when people are playing.  If defined, then
 *		UCOUNT		Should it use it's own routine to count
 *				users?
 *		UTMP		If so, where does the user list hide?
 *	CHECKTIME	How often/if it should check during the game
 *			for high load average.
 *	WARNTIME	How much time between warnings when load gets
 *			too high (if not defined, it is the same as
 *			CHECKTIME).
 */

# include	<curses.h>
D 3
# include	"extern.h"
E 3
I 3
# include	"machdep.h"
E 3
# include	<signal.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<sys/file.h>

I 4
# undef LOADAV		/* use getloadavg() by default */

E 4
# ifdef	SCOREFILE

D 3
# ifndef	LOCK_EX
E 3
static char	*Lockfile = "/tmp/.fredlock";
D 3
# endif
E 3

# ifndef	NUMSCORES
# 	define	NUMSCORES	10
# 	define	NUMNAME		"Ten"
# endif		NUMSCORES

unsigned int	Numscores = NUMSCORES;

char		*Numname = NUMNAME;

# ifdef ALLSCORES
bool	Allscore = TRUE;
# else	ALLSCORES
bool	Allscore = FALSE;
# endif ALLSCORES

# endif	SCOREFILE

# ifdef	CHECKTIME
static int	Num_checks;	/* times we've gone over in checkout() */

# ifndef WARNTIME
# define	WARNTIME	CHECKTIME
# endif
# endif	CHECKTIME

/*
 * init_check:
 *	Check out too see if it is proper to play the game now
 */
init_check()
{
# if	defined(MAXLOAD) || defined(MAXUSERS)
	if (too_much()) {
		printf("Sorry, %s, but the system is too loaded now.\n",
		       Whoami);
		printf("Try again later.  Meanwhile, why not enjoy a%s %s?\n",
		       vowelstr(Fruit), Fruit);
		if (author())
			printf("However, since you're a good guy, it's up to you\n");
		else
			exit(1);
	}
# endif	defined(MAXLOAD) || defined(MAXUSERS)
}

/*
 * open_score:
 *	Open up the score file for future use, and then
 *	setuid(getuid()) in case we are running setuid.
 */
open_score()
{
# ifdef SCOREFILE
	Fd = open(SCOREFILE, 2);
# else	SCOREFILE
	Fd = -1;
# endif	SCOREFILE
	setuid(getuid());
	setgid(getgid());
}

/*
 * setup:
 *	Get starting setup for all games
 */
setup()
{
	extern int	auto_save(), quit(), endit(), tstp();
# ifdef CHECKTIME
	extern int 	heckout();
# endif	CHECKTIME

	signal(SIGHUP, auto_save);
# ifndef DUMP
	signal(SIGILL, auto_save);
	signal(SIGTRAP, auto_save);
	signal(SIGIOT, auto_save);
	signal(SIGEMT, auto_save);
	signal(SIGFPE, auto_save);
	signal(SIGBUS, auto_save);
	signal(SIGSEGV, auto_save);
	signal(SIGSYS, auto_save);
	signal(SIGTERM, auto_save);
# endif	DUMP

	signal(SIGINT, quit);
# ifndef DUMP
	signal(SIGQUIT, endit);
# endif	DUMP
# ifdef CHECKTIME
	signal(SIGALRM, checkout);
	alarm(CHECKTIME * 60);
	Num_checks = 0;
# endif	CHECKTIME
	crmode();				/* Cbreak mode */
	noecho();				/* Echo off */
	nonl();
# ifdef TIOCGLTC
	getltchars();			/* get the local tty chars */
# endif	TIOCGLTC
}

/*
 * getltchars:
 *	Get the local tty chars for later use
 */
getltchars()
{
# ifdef TIOCGLTC
	ioctl(1, TIOCGLTC, &Ltc);
	Got_ltc = TRUE;
	Orig_dsusp = Ltc.t_dsuspc;
D 3
	Ltc.t_dsuspc = Ltc.t_suspc;
	ioctl(1, TIOCSLTC, &Ltc);
E 3
I 3
	if (Orig_dsusp == CTRL(Y)) {
		Ltc.t_dsuspc = Ltc.t_suspc;
		ioctl(1, TIOCSLTC, &Ltc);
	}
E 3
# endif	TIOCGLTC
}

/*
 * start_score:
 *	Start the scoring sequence
 */
start_score()
{
# ifdef CHECKTIME
	signal(SIGALRM, SIG_IGN);	/* NOSTRICT */
# endif	CHECKTIME
}

/*
 * symlink:
 *	See if the file has a symbolic link
 */
symlink(sp)
char	*sp;
{
# ifdef S_IFLNK
	struct stat sbuf2;

	if (lstat(sp, &sbuf2) < 0)
		return FALSE;
	else
		return ((sbuf2.st_mode & S_IFMT) != S_IFREG);
# else	S_IFLNK
	return FALSE;
# endif	S_IFLNK
}

# if	defined(MAXLOAD) || defined(MAXUSERS)
/*
 * too_much:
 *	See if the system is being used too much for this game
 */
too_much()
{
# ifdef MAXLOAD
	double		avec[3];
# endif	MAXLOAD
# ifdef	MAXUSERS
	register int	cnt;
# endif	MAXUSERS

# ifdef MAXLOAD
I 4
# ifdef LOADAV
E 4
	loadav(avec);
I 4
# else
	if (getloadavg(avec, sizeof(avec)/sizeof(avec[0])) < 0)
		avec[0] = avec[1] = avec[2] = 0.0;
# endif
E 4
	if (avec[1] > MAXLOAD)
		return TRUE;
# endif	MAXLOAD
# ifdef MAXUSERS
	if (ucount() > MAXUSERS)
		return TRUE;
# endif	MAXUSERS
	return FALSE;
}

/*
 * author:
 *	See if a user is an author of the program
 */
author()
{
# ifdef MASTER
	if (Wizard)
		return TRUE;
# endif	MASTER
	switch (getuid())
	{
	  case -1:
		return TRUE;
	  default:
		return FALSE;
	}
}
# endif	defined(MAXLOAD) || defined(MAXUSERS)

# ifdef	CHECKTIME
/*
 * checkout:
 *	Check each CHECKTIME seconds to see if the load is too high
 */
checkout()
{
	int		checktime;
	static char	*msgs[] = {
		"The load is too high to be playing.  Please leave in %.2f minutes",
		"Please save your game.  You have %.2f minutes",
		"Last warning.  You have %.2f minutes to leave",
	};

	signal(SIGALRM, checkout);
	if (too_much()) {
		if (author()) {
			Num_checks = 1;
			chmsg("The load is rather high, O exaulted one");
		}
		else if (Num_checks++ == 3)
			fatal("Sorry.  You took too long.  You are dead\n");
		checktime = (WARNTIME * 60) / Num_checks;
		alarm(checktime);
		chmsg(msgs[Num_checks - 1], ((double) checktime / 60.0));
	}
	else {
		if (Num_checks) {
			Num_checks = 0;
			chmsg("The load has dropped back down.  You have a reprieve");
		}
		alarm(CHECKTIME * 60);
	}
}

/*
 * chmsg:
 *	checkout()'s version of msg.  If we are in the middle of a
 *	shell, do a printf instead of a msg to avoid the refresh.
 */
/* VARARGS1 */
chmsg(fmt, arg)
char	*fmt;
int	arg;
{
	if (!In_shell)
		msg(fmt, arg);
	else {
		printf(fmt, arg);
		putchar('\n');
		fflush(stdout);
	}
}
# endif	defined(MAXLOAD) || defined(MAXUSERS)

# ifdef	LOADAV
/*
 * loadav:
 *	Looking up load average in core (for system where the loadav()
 *	system call isn't defined
 */

# include	<nlist.h>

struct nlist	avenrun = {
	    "_avenrun"
};

# ifndef	NAMELIST
# define	NAMELIST	"/vmunix"
# endif

loadav(avg)
register double	*avg;
{
	register int	kmem;

	if ((kmem = open("/dev/kmem", 0)) < 0)
		goto bad;
	nlist(NAMELIST, &avenrun);
	if (avenrun.n_type == 0) {
		close(kmem);
		bad:
		avg[0] = 0.0;
		avg[1] = 0.0;
		avg[2] = 0.0;
		return;
	}

	lseek(kmem, (long) avenrun.n_value, 0);
	read(kmem, (char *) avg, 3 * sizeof (double));
	close(kmem);
}
# endif	LOADAV

# ifdef UCOUNT
/*
 * ucount:
 *	Count number of users on the system
 */
# include	<utmp.h>

struct utmp	buf;

ucount()
{
	register struct utmp	*up;
	register FILE		*utmp;
	register int		count;

	if ((utmp = fopen(UTMP, "r")) == NULL)
		return 0;

	up = &buf;
	count = 0;

	while (fread(up, 1, sizeof (*up), utmp) > 0)
		if (buf.ut_name[0] != '\0')
			count++;
	fclose(utmp);
	return count;
}
# endif	UCOUNT

/*
 * lock_sc:
 *	lock the score file.  If it takes too long, ask the user if
 *	they care to wait.  Return TRUE if the lock is successful.
 */
lock_sc()
{
# ifdef SCOREFILE
# ifdef	LOCK_EX
	return (flock(Fd, LOCK_EX) >= 0);
# else	LOCK_EX
	register int		cnt;
	static struct stat	sbuf;

over:
	close(8);	/* just in case there are no files left */
	if (creat(Lockfile, 0000) >= 0)
		return TRUE;
	for (cnt = 0; cnt < 5; cnt++) {
		sleep(1);
		if (creat(Lockfile, 0000) >= 0)
			return TRUE;
	}
	if (stat(Lockfile, &sbuf) < 0) {
		creat(Lockfile, 0000);
		return TRUE;
	}
	if (time(NULL) - sbuf.st_mtime > 10) {
		if (unlink(Lockfile) < 0)
			return FALSE;
		goto over;
	}
	else {
		printf("The score file is very busy.  Do you want to wait longer\n");
		printf("for it to become free so your score can get posted?\n");
		printf("If so, type \"y\"\n");
		fgets(Prbuf, MAXSTR, stdin);
		if (Prbuf[0] == 'y')
			for (;;) {
				if (creat(Lockfile, 0000) >= 0)
					return TRUE;
				if (stat(Lockfile, &sbuf) < 0) {
					creat(Lockfile, 0000);
					return TRUE;
				}
				if (time(NULL) - sbuf.st_mtime > 10)
					if (unlink(Lockfile) < 0)
						return FALSE;
				sleep(1);
			}
		else
			return FALSE;
	}
# endif	LOCK_EX
# endif	SCOREFILE
}

/*
 * unlock_sc:
 *	Unlock the score file
 */
unlock_sc()
{
# ifdef SCOREFILE
# ifdef	LOCK_EX
	flock(Fd, LOCK_UN);
#else
	unlink(Lockfile);
# endif
# endif
}
E 1
