h31780
s 00000/00000/00137
d D 8.1 93/06/08 18:32:13 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00135
d D 6.4 93/06/08 18:31:57 bostic 7 5
c do roff .c files by hand
e
s 00002/00002/00135
d R 8.1 93/06/04 16:45:02 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00130
d D 6.3 91/04/17 10:37:54 bostic 5 4
c new copyright; att/bsd/shared
e
s 00021/00004/00136
d D 6.2 89/03/17 11:32:15 bostic 4 3
c add Berkeley specific copyright notices
e
s 00017/00018/00123
d D 6.1 86/04/23 23:58:59 mckusick 3 2
c document distributed with 4.3BSD
e
s 00000/00000/00141
d D 5.1 86/04/23 23:58:36 mckusick 2 1
c document distributed with 4.2BSD
e
s 00141/00000/00000
d D 4.1 86/04/23 23:58:13 mckusick 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 5
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
 */

#ifndef lint
I 4
char copyright[] =
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

E 5
I 5
D 7
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 7
I 7
.\" Copyright (c) 1980, 1993
.\"	 The Regents of the University of California.  All rights reserved.
E 7
.\"
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 5
# include	<curses.h>
# include	<signal.h>

/*
 *	Run a life game.  This is a demonstration program for
 * the Screen Updating section of the -lcurses cursor package.
 */

D 3
struct lst_st {			/* linked list element */
E 3
I 3
typedef struct lst_st {			/* linked list element */
E 3
	int		y, x;		/* (y, x) position of piece */
	struct lst_st	*next, *last;	/* doubly linked */
D 3
};
E 3
I 3
} LIST;
E 3

D 3
typedef struct lst_st	LIST;

E 3
LIST	*Head;			/* head of linked list */

I 3
int	die();

E 3
main(ac, av)
int	ac;
D 3
char	*av[]; {

	int	die();

E 3
I 3
char	*av[];
{
E 3
	evalargs(ac, av);		/* evaluate arguments */

	initscr();			/* initialize screen package */
	signal(SIGINT, die);		/* set to restore tty stats */
D 3
	crmode();			/* set for char-by-char */
E 3
I 3
	cbreak();			/* set for char-by-char */
E 3
	noecho();			/*	input */
	nonl();				/* for optimization */

	getstart();			/* get starting position */
	for (;;) {
		prboard();		/* print out current board */
		update();		/* update board position */
	}
}

/*
 * This is the routine which is called when rubout is hit.
 * It resets the tty stats to their original values.  This
 * is the normal way of leaving the program.
 */
D 3
die() {

	signal(SIGINT, SIG_IGN);	/* ignore rubouts */
	mvcur(0, COLS-1, LINES-1, 0);	/* go to bottom of screen */
	endwin();			/* set terminal to initial state */
E 3
I 3
die()
{
	signal(SIGINT, SIG_IGN);		/* ignore rubouts */
	mvcur(0, COLS - 1, LINES - 1, 0);	/* go to bottom of screen */
	endwin();				/* set terminal to good state */
E 3
	exit(0);
}

/*
 * Get the starting position from the user.  They keys u, i, o, j, l,
 * m, ,, and . are used for moving their relative directions from the
 * k key.  Thus, u move diagonally up to the left, , moves directly down,
 * etc.  x places a piece at the current position, " " takes it away.
 * The input can also be from a file.  The list is built after the
 * board setup is ready.
 */
D 3
getstart() {

E 3
I 3
getstart()
{
E 3
	reg char	c;
	reg int		x, y;
I 3
	auto char	buf[100];
E 3

	box(stdscr, '|', '_');		/* box in the screen */
	move(1, 1);			/* move to upper left corner */

D 3
	do {
E 3
I 3
	for (;;) {
E 3
		refresh();		/* print current position */
D 3
		if ((c=getch()) == 'q')
E 3
I 3
		if ((c = getch()) == 'q')
E 3
			break;
		switch (c) {
		  case 'u':
		  case 'i':
		  case 'o':
		  case 'j':
		  case 'l':
		  case 'm':
		  case ',':
		  case '.':
			adjustyx(c);
			break;
		  case 'f':
			mvaddstr(0, 0, "File name: ");
			getstr(buf);
			readfile(buf);
			break;
		  case 'x':
			addch('X');
			break;
		  case ' ':
			addch(' ');
			break;
		}
	}

	if (Head != NULL)			/* start new list */
		dellist(Head);
	Head = malloc(sizeof (LIST)); 

	/*
	 * loop through the screen looking for 'x's, and add a list
	 * element for each one
	 */
	for (y = 1; y < LINES - 1; y++)
		for (x = 1; x < COLS - 1; x++) {
			move(y, x);
			if (inch() == 'x')
				addlist(y, x);
		}
}

/*
 * Print out the current board position from the linked list
 */
prboard() {

	reg LIST	*hp;

	erase();			/* clear out last position */
	box(stdscr, '|', '_');		/* box in the screen */

	/*
	 * go through the list adding each piece to the newly
	 * blank board
	 */
	for (hp = Head; hp; hp = hp->next)
		mvaddch(hp->y, hp->x, 'X');

	refresh();
}
E 1
