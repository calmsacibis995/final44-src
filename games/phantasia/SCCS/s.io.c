h16150
s 00001/00000/00435
d D 5.4 92/10/17 13:06:53 bostic 4 3
c lint
e
s 00000/00050/00435
d D 5.3 90/05/02 21:48:52 bostic 3 2
c remove shell escapes
e
s 00001/00001/00484
d D 5.2 88/06/01 19:20:15 bostic 2 1
c we no longer support %[A-Z]; besides, it messes up SCCS
e
s 00485/00000/00000
d D 5.1 88/06/01 18:32:10 bostic 1 0
c date and time created 88/06/01 18:32:10 by bostic
e
u
U
t
T
I 1
/*
 * io.c - input/output routines for Phantasia
 */

#include "include.h"

/************************************************************************
/
/ FUNCTION NAME: getstring()
/
/ FUNCTION: read a string from operator
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS:
/	char *cp - pointer to buffer area to fill
/	int mx - maximum number of characters to put in buffer
/
/ RETURN VALUE: none
/
/ MODULES CALLED: wmove(), _filbuf(), clearok(), waddstr(), wrefresh(), 
/	wclrtoeol()
/
/ GLOBAL INPUTS: Echo, _iob[], Wizard, *stdscr
/
/ GLOBAL OUTPUTS: _iob[]
/
/ DESCRIPTION:
/	Read a string from the keyboard.
/	This routine is specially designed to:
/
/	    - strip non-printing characters (unless Wizard)
/	    - echo, if desired
/	    - redraw the screen if CH_REDRAW is entered
/	    - read in only 'mx - 1' characters or less characters
/	    - nul-terminate string, and throw away newline
/
/	'mx' is assumed to be at least 2.
/
/************************************************************************/

getstring(cp, mx)
register char	*cp;
register int	mx;
{
register char	*inptr;		/* pointer into string for next string */
int	x, y;			/* original x, y coordinates on screen */
int	ch;			/* input */

    getyx(stdscr, y, x);	/* get coordinates on screen */
    inptr = cp;
    *inptr = '\0';		/* clear string to start */
    --mx;			/* reserve room in string for nul terminator */

    do
	/* get characters and process */
	{
	if (Echo)
	    mvaddstr(y, x, cp);	/* print string on screen */
	clrtoeol();		/* clear any data after string */
	refresh();		/* update screen */

	ch = getchar();		/* get character */

	switch (ch)
	    {
	    case CH_ERASE:	/* back up one character */
		if (inptr > cp)
		    --inptr;
		break;

	    case CH_KILL:	/* back up to original location */
		inptr = cp;
		break;

	    case CH_NEWLINE:	/* terminate string */
		break;

	    case CH_REDRAW:	/* redraw screen */
		clearok(stdscr, TRUE);
		continue;

	    default:		/* put data in string */
		if (ch >= ' ' || Wizard)
		    /* printing char; put in string */
		    *inptr++ = ch;
	    }

	*inptr = '\0';		/* terminate string */
	}
    while (ch != CH_NEWLINE && inptr < cp + mx);
}
/**/
/************************************************************************
/
/ FUNCTION NAME: more()
/
/ FUNCTION: pause and prompt player
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS:
/	int where - line on screen on which to pause
/
/ RETURN VALUE: none
/
/ MODULES CALLED: wmove(), waddstr(), getanswer()
/
/ GLOBAL INPUTS: *stdscr
/
/ GLOBAL OUTPUTS: none
/
/ DESCRIPTION:
/	Print a message, and wait for a space character.
/
/************************************************************************/

more(where)
int	where;
{
    mvaddstr(where, 0, "-- more --");
    getanswer(" ", FALSE);
}
/**/
/************************************************************************
/
/ FUNCTION NAME: infloat()
/
/ FUNCTION: input a floating point number from operator
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS: none
/
/ RETURN VALUE: floating point number from operator
/
/ MODULES CALLED: sscanf(), getstring()
/
/ GLOBAL INPUTS: Databuf[]
/
/ GLOBAL OUTPUTS: none
/
/ DESCRIPTION:
/	Read a string from player, and scan for a floating point
/	number.
/	If no valid number is found, return 0.0.
/
/************************************************************************/

double
infloat()
{
double	result;		/* return value */

    getstring(Databuf, SZ_DATABUF);
D 2
    if (sscanf(Databuf, "%F", &result) < 1)
E 2
I 2
    if (sscanf(Databuf, "%lf", &result) < 1)
E 2
	/* no valid number entered */
	result = 0.0;

    return(result);
}
/**/
/************************************************************************
/
/ FUNCTION NAME: inputoption()
/
/ FUNCTION: input an option value from player
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS: none
/
/ RETURN VALUE: none
/
/ MODULES CALLED: floor(), drandom(), getanswer()
/
/ GLOBAL INPUTS: Player
/
/ GLOBAL OUTPUTS: Player
/
/ DESCRIPTION:
/	Age increases with every move.
/	Refresh screen, and get a single character option from player.
/	Return a random value if player's ring has gone bad.
/
/************************************************************************/

inputoption()
{
    ++Player.p_age;		/* increase age */

    if (Player.p_ring.ring_type != R_SPOILED)
	/* ring ok */
	return(getanswer("T ", TRUE));
    else
	/* bad ring */
	{
	getanswer(" ", TRUE);
	return((int) ROLL(0.0, 5.0) + '0');
	}
}
/**/
/************************************************************************
/
/ FUNCTION NAME: interrupt()
/
/ FUNCTION: handle interrupt from operator
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS: none
/
/ RETURN VALUE: none
/
/ MODULES CALLED: fork(), exit(), wait(), death(), alarm(), execl(), wmove(), 
/	getgid(), signal(), getenv(), wclear(), setuid(), getuid(), setgid(), 
/	crmode(), clearok(), waddstr(), cleanup(), wrefresh(), leavegame(), 
/	getanswer()
/
/ GLOBAL INPUTS: Player, *stdscr
/
/ GLOBAL OUTPUTS: none
/
/ DESCRIPTION:
/	Allow player to quit upon hitting the interrupt key.
/	If the player wants to quit while in battle, he/she automatically
/	dies.
D 3
/	If SHELL is defined, spawn a shell if the if the question is
/	answered with a '!'.
/	We are careful to save the state of the screen, and return it
/	to its original condition.
E 3
/
/************************************************************************/

interrupt()
{
char	line[81];		/* a place to store data already on screen */
register int	loop;		/* counter */
int	x, y;			/* coordinates on screen */
int	ch;			/* input */
unsigned	savealarm;	/* to save alarm value */
D 3
#ifdef SHELL
register char	*shell;		/* pointer to shell to spawn */
int	childpid;		/* pid of spawned process */
#endif
E 3

#ifdef SYS3
    signal(SIGINT, SIG_IGN);
#endif
#ifdef SYS5
    signal(SIGINT, SIG_IGN);
#endif

    savealarm = alarm(0);		/* turn off any alarms */

    getyx(stdscr, y, x);		/* save cursor location */

    for (loop = 0; loop < 80; ++loop)	/* save line on screen */
	{
	move(4, loop);
	line[loop] = inch();
	}
    line[80] = '\0';			/* nul terminate */

    if (Player.p_status == S_INBATTLE || Player.p_status == S_MONSTER)
	/* in midst of fighting */
	{
	mvaddstr(4, 0, "Quitting now will automatically kill your character.  Still want to ? ");
D 3
#ifdef SHELL
	ch = getanswer("NY!", FALSE);
#else
E 3
	ch = getanswer("NY", FALSE);
D 3
#endif
E 3
	if (ch == 'Y')
	    death("Bailing out");
	    /*NOTREACHED*/
	}
    else
	{
D 3
#ifdef SHELL
	mvaddstr(4, 0, "Do you really want to quit [! = Shell] ? ");
	ch = getanswer("NY!", FALSE);
#else
E 3
	mvaddstr(4, 0, "Do you really want to quit ? ");
	ch = getanswer("NY", FALSE);
D 3
#endif
E 3
	if (ch == 'Y')
	    leavegame();
	    /*NOTREACHED*/
	}
D 3

#ifdef SHELL
    if (ch == '!')
	/* shell escape */
	{
	if ((shell = getenv("SHELL")) == NULL)
	    /* use default */
	    shell = SHELL;

	if ((childpid = fork()) == 0)
	    /* in child */
	    {
	    clear();
	    refresh();
	    cleanup(FALSE);		/* out of curses, close files */

	    setuid(getuid());		/* make sure we are running with real uid */
	    setgid(getgid());		/* make sure we are running with real gid */
	    execl(shell, shell, "-i", 0);
	    execl(SHELL, SHELL, "-i", 0);	/* last resort */

	    exit(0);
	    /*NOTREACHED*/
	    }
	else
	    /* in parent */
	    {
	    while (wait((int *) NULL) != childpid);	/* wait until done */
	    crmode();			/* restore keyboard */
	    clearok(stdscr, TRUE);	/* force redraw of screen */
	    }
	}
#endif
E 3

    mvaddstr(4, 0, line); 		/* restore data on screen */
    move(y, x);				/* restore cursor */
    refresh();

#ifdef SYS3
    signal(SIGINT, interrupt);
#endif
#ifdef SYS5
    signal(SIGINT, interrupt);
#endif

    alarm(savealarm);			/* restore alarm */
}
/**/
/************************************************************************
/
/ FUNCTION NAME: getanswer()
/
/ FUNCTION: get an answer from operator
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS:
/	char *choices - string of (upper case) valid choices
/	bool def - set if default answer
/
/ RETURN VALUE: none
/
/ MODULES CALLED: alarm(), wmove(), waddch(), signal(), setjmp(), strchr(), 
/	_filbuf(), clearok(), toupper(), wrefresh(), mvprintw(), wclrtoeol()
/
/ GLOBAL INPUTS: catchalarm(), Echo, _iob[], _ctype[], *stdscr, Timeout, 
/	Timeoenv[]
/
/ GLOBAL OUTPUTS: _iob[]
/
/ DESCRIPTION:
/	Get a single character answer from operator.
/	Timeout waiting for response.  If we timeout, or the
/	answer in not in the list of valid choices, print choices,
/	and wait again, otherwise return the first character in ths
/	list of choices.
/	Give up after 3 tries.
/
/************************************************************************/

getanswer(choices, def)
char	*choices;
bool	def;
{
int	ch;			/* input */
int	loop;			/* counter */
int	oldx, oldy;		/* original coordinates on screen */

    getyx(stdscr, oldy, oldx);
    alarm(0);				/* make sure alarm is off */

    for (loop = 3; loop; --loop)
	/* try for 3 times */
	{
	if (setjmp(Timeoenv) != 0)
	    /* timed out waiting for response */
	    {
	    if (def || loop <= 1)
		/* return default answer */
		break;
	    else
		/* prompt, and try again */
		goto YELL;
	    }
	else
	    /* wait for response */
	    {
	    clrtoeol();
	    refresh();
#ifdef BSD41
	    sigset(SIGALRM, catchalarm);
#else
	    signal(SIGALRM, catchalarm);
#endif
	    /* set timeout */
	    if (Timeout)
		alarm(7);		/* short */
	    else
		alarm(600);		/* long */

	    ch = getchar();

	    alarm(0);			/* turn off timeout */

	    if (ch < 0)
		/* caught some signal */
		{
		++loop;
		continue;
		}
	    else if (ch == CH_REDRAW)
		/* redraw screen */
		{
		clearok(stdscr, TRUE);	/* force clear screen */
		++loop;			/* don't count this input */
		continue;
		}
	    else if (Echo)
		{
		addch(ch);		/* echo character */
		refresh();
		}

	    if (islower(ch))
		/* convert to upper case */
		ch = toupper(ch);

	    if (def || strchr(choices, ch) != NULL)
		/* valid choice */
		return(ch);
	    else if (!def && loop > 1)
		/* bad choice; prompt, and try again */
		{
YELL:		mvprintw(oldy + 1, 0, "Please choose one of : [%s]\n", choices);
		move(oldy, oldx);
		clrtoeol();
		continue;
		}
	    else
		/* return default answer */
		break;
	    }
	}

    return(*choices);
}
/**/
/************************************************************************
/
/ FUNCTION NAME: catchalarm()
/
/ FUNCTION: catch timer when waiting for input
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS: none
/
/ RETURN VALUE: none
/
/ MODULES CALLED: longjmp()
/
/ GLOBAL INPUTS: Timeoenv[]
/
/ GLOBAL OUTPUTS: none
/
/ DESCRIPTION:
/	Come here when the alarm expires while waiting for input.
/	Simply longjmp() into getanswer().
/
/************************************************************************/

I 4
void
E 4
catchalarm()
{
    longjmp(Timeoenv, 1);
}
E 1