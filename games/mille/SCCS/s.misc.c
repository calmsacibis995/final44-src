h48615
s 00002/00002/00225
d D 8.1 93/05/31 17:25:26 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00224
d D 5.8 92/08/31 10:14:11 elan 9 8
c Added correct header file includes.
e
s 00004/00014/00221
d D 5.7 92/03/08 10:07:00 torek 8 6
c allow ^L during endgame prompts.  rm flush_input: this ioctl's
c interface is utterly broken, and anyway it is a bad idea to do this
c in general.
e
s 00004/00014/00221
d R 5.7 92/03/08 10:04:32 torek 7 6
c allow ^L during endgame prompts; rm flush_input: we cannot
c use this ioctl correctly because it uses FREAD and FWRITE, which are
e
s 00001/00011/00234
d D 5.6 90/06/01 13:08:04 bostic 6 5
c new copyright notice
e
s 00001/00001/00244
d D 5.5 90/05/18 11:03:10 bostic 5 4
c FREAD -> O_RDONLY
e
s 00010/00005/00235
d D 5.4 88/06/18 19:38:26 bostic 4 3
c install approved copyright notice
e
s 00004/00004/00236
d D 5.3 88/06/12 12:13:49 bostic 3 2
c remove non-printable characters
e
s 00009/00003/00231
d D 5.2 87/12/29 17:13:57 bostic 2 1
c Berkeley header
e
s 00234/00000/00000
d D 5.1 86/11/26 13:35:33 bostic 1 0
c date and time created 86/11/26 13:35:33 by bostic
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1983 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 4
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

I 9
#include <sys/file.h>
#include <termios.h>

E 9
#include	"mille.h"
#ifndef	unctrl
#include	"unctrl.h"
#endif

D 9
# include	<sys/file.h>
E 9

# ifdef	attron
#	include	<term.h>
#	define	_tty	cur_term->Nttyb
# endif	attron

/*
 * @(#)misc.c	1.2 (Berkeley) 3/28/83
 */

#define	NUMSAFE	4

/* VARARGS1 */
error(str, arg)
char	*str;
{
	stdscr = Score;
	mvprintw(ERR_Y, ERR_X, str, arg);
	clrtoeol();
D 3
	putchar('');
E 3
I 3
	putchar('\07');
E 3
	refresh();
	stdscr = Board;
	return FALSE;
}

CARD
getcard()
{
	reg int		c, c1;

	for (;;) {
		while ((c = readch()) == '\n' || c == '\r' || c == ' ')
			continue;
		if (islower(c))
			c = toupper(c);
		if (c == killchar() || c == erasechar())
			return -1;
		addstr(unctrl(c));
		clrtoeol();
		switch (c) {
		  case '1':	case '2':	case '3':
		  case '4':	case '5':	case '6':
			c -= '0';
			break;
		  case '0':	case 'P':	case 'p':
			c = 0;
			break;
		  default:
D 3
			putchar('');
E 3
I 3
			putchar('\07');
E 3
			addch('\b');
			if (!isprint(c))
				addch('\b');
			c = -1;
			break;
		}
		refresh();
		if (c >= 0) {
			while ((c1=readch()) != '\r' && c1 != '\n' && c1 != ' ')
				if (c1 == killchar())
					return -1;
				else if (c1 == erasechar()) {
					addch('\b');
					clrtoeol();
					refresh();
					goto cont;
				}
				else
D 3
					write(0, "", 1);
E 3
I 3
					write(0, "\07", 1);
E 3
			return c;
		}
cont:		;
	}
}

check_ext(forcomp)
reg bool	forcomp; {


	if (End == 700)
		if (Play == PLAYER) {
			if (getyn(EXTENSIONPROMPT)) {
extend:
				if (!forcomp)
					End = 1000;
				return TRUE;
			}
			else {
done:
				if (!forcomp)
					Finished = TRUE;
				return FALSE;
			}
		}
		else {
			reg PLAY	*pp, *op;
			reg int		i, safe, miles;

			pp = &Player[COMP];
			op = &Player[PLAYER];
			for (safe = 0, i = 0; i < NUMSAFE; i++)
				if (pp->safety[i] != S_UNKNOWN)
					safe++;
			if (safe < 2)
				goto done;
			if (op->mileage == 0 || onecard(op)
			    || (op->can_go && op->mileage >= 500))
				goto done;
			for (miles = 0, i = 0; i < NUMSAFE; i++)
				if (op->safety[i] != S_PLAYED
				    && pp->safety[i] == S_UNKNOWN)
					miles++;
			if (miles + safe == NUMSAFE)
				goto extend;
			for (miles = 0, i = 0; i < HAND_SZ; i++)
				if ((safe = pp->hand[i]) <= C_200)
					miles += Value[safe]; 
			if (miles + (Topcard - Deck) * 3 > 1000)
				goto extend;
			goto done;
		}
	else
		goto done;
}

/*
 *	Get a yes or no answer to the given question.  Saves are
 * also allowed.  Return TRUE if the answer was yes, FALSE if no.
 */
getyn(promptno)
register int	promptno; {

	reg char	c;

	Saved = FALSE;
	for (;;) {
		leaveok(Board, FALSE);
		prompt(promptno);
		clrtoeol();
		refresh();
		switch (c = readch()) {
		  case 'n':	case 'N':
			addch('N');
			refresh();
			leaveok(Board, TRUE);
			return FALSE;
		  case 'y':	case 'Y':
			addch('Y');
			refresh();
			leaveok(Board, TRUE);
			return TRUE;
		  case 's':	case 'S':
			addch('S');
			refresh();
			Saved = save();
			continue;
I 8
		  case CTRL('L'):
			wrefresh(curscr);
			break;
E 8
		  default:
			addstr(unctrl(c));
			refresh();
D 3
			putchar('');
E 3
I 3
			putchar('\07');
E 3
			break;
		}
	}
}

/*
 *	Check to see if more games are desired.  If not, and game
 * came from a saved file, make sure that they don't want to restore
 * it.  Exit appropriately.
 */
check_more() {

D 8
	flush_input();

E 8
	On_exit = TRUE;
	if (Player[PLAYER].total >= 5000 || Player[COMP].total >= 5000)
		if (getyn(ANOTHERGAMEPROMPT))
			return;
		else {
			/*
			 * must do accounting normally done in main()
			 */
			if (Player[PLAYER].total > Player[COMP].total)
				Player[PLAYER].games++;
			else if (Player[PLAYER].total < Player[COMP].total)
				Player[COMP].games++;
			Player[COMP].total = 0;
			Player[PLAYER].total = 0;
		}
	else
		if (getyn(ANOTHERHANDPROMPT))
			return;
	if (!Saved && getyn(SAVEGAMEPROMPT))
		if (!save())
			return;
D 8
	die();
E 8
I 8
	die(0);
E 8
}

readch()
{
	reg int		cnt;
	static char	c;

	for (cnt = 0; read(0, &c, 1) <= 0; cnt++)
		if (cnt > 100)
			exit(1);
	return c;
D 8
}

flush_input()
{
# ifdef	TIOCFLUSH
D 5
	static int	ioctl_args = FREAD;
E 5
I 5
	static int	ioctl_args = O_RDONLY;
E 5

	(void) ioctl(fileno(stdin), TIOCFLUSH, &ioctl_args);
# else
	fflush(stdin);
# endif
E 8
}
E 1
