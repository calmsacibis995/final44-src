h11560
s 00005/00005/00162
d D 8.1 93/05/31 17:45:30 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00009/00166
d D 5.7 93/01/11 10:57:13 bostic 7 6
c robots doesn't need CE
e
s 00008/00003/00167
d D 5.6 92/08/31 10:17:38 elan 6 5
c Added __cputchar().
e
s 00004/00002/00166
d D 5.5 91/02/28 14:28:29 bostic 5 4
c ANSI
e
s 00001/00011/00167
d D 5.4 90/06/01 13:14:42 bostic 4 3
c new copyright notice
e
s 00010/00005/00168
d D 5.3 88/06/18 20:04:40 bostic 3 2
c install approved copyright notice
e
s 00010/00004/00163
d D 5.2 88/03/09 11:18:38 bostic 2 1
c Written by Ken Arnold; add Berkeley specific copyright
e
s 00167/00000/00000
d D 5.1 85/05/30 18:34:12 mckusick 1 0
c date and time created 85/05/30 18:34:12 by mckusick
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
E 2
 */

#ifndef lint
D 8
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

# include	"robots.h"
# include	<signal.h>
# include	<ctype.h>

main(ac, av)
int	ac;
char	**av;
{
	register char	*sp;
	register bool	bad_arg;
	register bool	show_only;
	extern char	*Scorefile;
	extern int	Max_per_uid;
D 5
	extern char	*rindex();
E 5
I 5
	void quit();
E 5

	show_only = FALSE;
	if (ac > 1) {
		bad_arg = FALSE;
		for (++av; ac > 1 && *av[0]; av++, ac--)
			if (av[0][0] != '-')
				if (isdigit(av[0][0]))
					Max_per_uid = atoi(av[0]);
				else {
					setuid(getuid());
					setgid(getgid());
					Scorefile = av[0];
# ifdef	FANCY
					sp = rindex(Scorefile, '/');
					if (sp == NULL)
						sp = Scorefile;
					if (strcmp(sp, "pattern_roll") == 0)
						Pattern_roll = TRUE;
					else if (strcmp(sp, "stand_still") == 0)
						Stand_still = TRUE;
					if (Pattern_roll || Stand_still)
						Teleport = TRUE;
# endif
				}
			else
				for (sp = &av[0][1]; *sp; sp++)
					switch (*sp) {
					  case 's':
						show_only = TRUE;
						break;
					  case 'r':
						Real_time = TRUE;
						break;
					  case 'a':
						Start_level = 4;
						break;
					  case 'j':
						Jump = TRUE;
						break;
					  case 't':
						Teleport = TRUE;
						break;
					  default:
						fprintf(stderr, "robots: uknown option: %c\n", *sp);
						bad_arg = TRUE;
						break;
					}
		if (bad_arg) {
			exit(1);
			/* NOTREACHED */
		}
	}

	if (show_only) {
		show_score();
		exit(0);
		/* NOTREACHED */
	}

	initscr();
	signal(SIGINT, quit);
	crmode();
	noecho();
	nonl();
	if (LINES != Y_SIZE || COLS != X_SIZE) {
		if (LINES < Y_SIZE || COLS < X_SIZE) {
			endwin();
D 5
			printf("Need at least a %dx%d screen\n", Y_SIZE, X_SIZE);
E 5
I 5
			printf("Need at least a %dx%d screen\n",
			    Y_SIZE, X_SIZE);
E 5
			exit(1);
		}
		delwin(stdscr);
		stdscr = newwin(Y_SIZE, X_SIZE, 0, 0);
	}

	srand(getpid());
	if (Real_time)
		signal(SIGALRM, move_robots);
	do {
		init_field();
		for (Level = Start_level; !Dead; Level++) {
			make_level();
			play_level();
		}
		move(My_pos.y, My_pos.x);
		printw("AARRrrgghhhh....");
		refresh();
		score();
	} while (another());
	quit();
}

I 6
void
__cputchar(ch)
	int ch;
{
	(void)putchar(ch);
}

E 6
/*
 * quit:
 *	Leave the program elegantly.
 */
I 5
void
E 5
quit()
{
D 6
	extern int	_putchar();

E 6
D 7
	mvcur(0, COLS - 1, LINES - 1, 0);
	if (CE) {
D 6
		tputs(CE, 1, _putchar);
E 6
I 6
		tputs(CE, 1, __cputchar);
E 6
		endwin();
	}
	else {
		endwin();
		putchar('\n');
	}
E 7
I 7
	endwin();
E 7
	exit(0);
	/* NOTREACHED */
}

/*
 * another:
 *	See if another game is desired
 */
another()
{
	register int	y;

#ifdef	FANCY
	if ((Stand_still || Pattern_roll) && !Newscore)
		return TRUE;
#endif

	if (query("Another game?")) {
		if (Full_clear) {
			for (y = 1; y <= Num_scores; y++) {
				move(y, 1);
				clrtoeol();
			}
			refresh();
		}
		return TRUE;
	}
	return FALSE;
}
E 1
