h22166
s 00000/00000/00076
d D 8.1 93/06/08 18:32:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00074
d D 1.3 93/06/08 18:31:55 bostic 4 2
c do roff .c files by hand
e
s 00002/00002/00074
d R 8.1 93/06/04 16:44:31 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00075
d D 1.2 93/01/14 17:43:24 elan 2 1
c Fixed typo in comment.
e
s 00076/00000/00000
d D 1.1 92/12/30 15:34:18 elan 1 0
c date and time created 92/12/30 15:34:18 by elan
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1992 The Regents of the University of California.
.\" All rights reserved.
E 4
I 4
.\" Copyright (c) 1992, 1993
.\"	 The Regents of the University of California.  All rights reserved.
E 4
.\"
.\" %sccs.include.redist.roff%
.\"
.\"     %W% (Berkeley) %G%
.\"
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
D 2
		default:		/* By defualt output the character */
E 2
I 2
		default:		/* By default output the character */
E 2
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
