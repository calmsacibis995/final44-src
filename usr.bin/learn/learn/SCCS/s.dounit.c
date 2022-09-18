h33055
s 00002/00002/00081
d D 8.1 93/06/06 14:56:14 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00082
d D 4.5 93/06/03 17:51:16 bostic 5 4
c MIPS doesn't like routines named "start"
e
s 00009/00002/00074
d D 4.4 91/04/17 18:00:33 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00001/00074
d D 4.3 87/09/11 13:47:54 jak 3 2
c bugs caught by Sun and some clearerr-type problems I thought I'd fixed
e
s 00021/00009/00054
d D 4.2 83/04/25 23:58:44 mckusick 2 1
c 
e
s 00063/00000/00000
d D 4.1 83/02/24 12:55:41 mckusick 1 0
c date and time created 83/02/24 12:55:41 by mckusick
e
u
U
t
T
I 4
/*-
D 6
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

#include "stdio.h"
#include "lrnref.h"

I 2
int	remind = 2;		/* to remind user of "again" and "bye" */
extern	int	noclobber;

E 2
dounit()
{
	char tbuff[100];

	if (todo == 0)
		return;
	wrong = 0;
retry:
D 2
	start(todo);
	sprintf(tbuff, "../../%s/L%s", sname, todo);	/* script = lesson */
E 2
I 2
	if (!noclobber)
D 5
		start(todo);		/* clean up play directory */
E 5
I 5
		lstart(todo);		/* clean up play directory */
E 5
	sprintf(tbuff, "%s/%s/L%s", direct, sname, todo); /* script = lesson */
E 2
	scrin = fopen(tbuff, "r");
	if (scrin == NULL) {
D 2
		fprintf(stderr, "No script.\n");
E 2
I 2
		perror(tbuff);
		fprintf(stderr, "Dounit:  no lesson %s.\n", tbuff);
E 2
		wrapup(1);
	}

D 2
	copy(0, scrin);
E 2
I 2
	copy(0, scrin);			/* print lesson, usually */
E 2
	if (more == 0)
		return;
D 2
	copy(1, stdin);
E 2
I 2
	copy(1, stdin);			/* user takes over */
	if (skip)
		setdid(todo, sequence++);
	if (again || skip)		/* if "again" or "skip" */
		return;
E 2
	if (more == 0)
		return;
D 2
	copy(0, scrin);
E 2
I 2
	copy(0, scrin);			/* evaluate user's response */
E 2

	if (comfile >= 0)
		close(comfile);
	wait(&didok);
	didok = (status == 0);
	if (!didok) {
		wrong++;
		printf("\nSorry, that's %snot right.  Do you want to try again?  ",
			wrong > 1 ? "still " : "");
		fflush(stdout);
		for(;;) {
			gets(tbuff);
			if (tbuff[0] == 'y') {
				printf("Try the problem again.\n");
D 2
				fflush(stdout);
E 2
I 2
				if (remind--) {
					printf("[ Whenever you want to re-read the lesson, type \"again\".\n");
					printf("  You can always leave learn by typing \"bye\". ]\n");
				}
E 2
				goto retry;
			} else if (strcmp(tbuff, "bye") == 0) {
D 2
				wrapup(1);
E 2
I 2
				wrapup(0);
E 2
			} else if (tbuff[0] == 'n') {
				wrong = 0;
D 2
				printf("\nOK.  Lesson %s (%d)\n", todo, speed);
E 2
I 2
				printf("\nOK.  That was lesson %s.\n", todo);
E 2
				printf("Skipping to next lesson.\n\n");
				fflush(stdout);
				break;
			} else {
D 3
				printf("Please type yes, no or bye:  ");
E 3
I 3
				printf("\nPlease type yes, no or bye:  ");
				clearerr(stdin);
E 3
				fflush(stdout);
			}
		}
	}
	setdid(todo, sequence++);
}

E 1
