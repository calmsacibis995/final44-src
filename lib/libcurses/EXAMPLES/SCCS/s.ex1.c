h27362
s 00004/00004/00082
d D 8.1 93/06/04 16:39:20 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00086/00000/00000
d D 1.1 93/01/15 10:14:57 elan 1 0
c date and time created 93/01/15 10:14:57 by elan
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char copyright[] =
D 2
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
#include <sys/types.h>
#include <curses.h>
#include <stdio.h>
#include <signal.h>


#define YSIZE 10 
#define XSIZE 20

int quit();

main()
{
	int i, j, c;
	size_t len;
	char id[100];
	FILE *fp;
	char *s;

	initscr();			/* Always call initscr() first */
	signal(SIGINT, quit);		/* Make sure wou have a 'cleanup' fn */
	crmode();			/* We want cbreak mode */
	noecho();			/* We want to have control of chars */
	delwin(stdscr);			/* Create our own stdscr */
	stdscr = newwin(YSIZE, XSIZE, 10, 35); 
	flushok(stdscr, TRUE);		/* Enable flushing of stdout */
	scrollok(stdscr, TRUE);		/* Enable scrolling */
	erase();			/* Initially, clear the screen */

	standout();
	move(0,0);
	while (1) {
		c = getchar();
		switch(c) {
		case 'q':		/* Quit on 'q' */
			quit();
			break;
		case 's':		/* Go into standout mode on 's' */
			standout();
			break;
		case 'e':		/* Exit standout mode on 'e' */
			standend();
			break;
		case 'r':		/* Force a refresh on 'r' */
			wrefresh(curscr);
			break;
		default:		/* By default output the character */
			addch(c);
			refresh();
		}
	}
}


int
quit()
{
	erase();		/* Terminate by erasing the screen */
	refresh();
	endwin();		/* Always end with endwin() */
	delwin(curscr);		/* Return storage */
	delwin(stdscr);
	putchar('\n');
	exit(0);
}

				
	
	
E 1
