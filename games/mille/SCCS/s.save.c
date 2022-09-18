h00787
s 00002/00002/00146
d D 8.1 93/05/31 17:25:39 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00141
d D 5.7 92/08/31 10:14:24 elan 7 6
c Added correct header file includes.
e
s 00001/00011/00145
d D 5.6 90/06/01 13:08:33 bostic 6 5
c new copyright notice
e
s 00003/00003/00153
d D 5.5 90/05/27 15:38:34 bostic 5 4
c sys_errlist -> strerror(3)
e
s 00010/00006/00146
d D 5.4 88/06/18 19:38:32 bostic 4 3
c install approved copyright notice
e
s 00014/00005/00138
d D 5.3 87/12/29 17:16:21 bostic 3 2
c Berkeley header; fix file name print; evaluation order was undefined
e
s 00001/00001/00142
d D 5.2 87/10/22 12:00:31 bostic 2 1
c ANSI C; sprintf now returns an int.
e
s 00143/00000/00000
d D 5.1 86/11/26 13:36:26 bostic 1 0
c date and time created 86/11/26 13:36:26 by bostic
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
D 4

E 4
I 3

E 3
D 7
#include	"mille.h"
#include	<sys/types.h>
#include	<sys/stat.h>
I 5
#include	<string.h>
E 7
I 7
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <termios.h>
#include "mille.h"

E 7
E 5
#ifndef	unctrl
D 7
#include	"unctrl.h"
E 7
I 7
#include "unctrl.h"
E 7
#endif

# ifdef	attron
#	include	<term.h>
#	define	_tty	cur_term->Nttyb
# endif	attron

/*
 * @(#)save.c	1.2 (Berkeley) 3/28/83
 */

typedef	struct stat	STAT;

char	*ctime();

int	read(), write();

/*
 *	This routine saves the current game for use at a later date
 */
D 5
extern int	errno;
extern char	*sys_errlist[];
E 5

save() {

I 5
	extern int	errno;
E 5
	reg char	*sp;
	reg int		outf;
	reg time_t	*tp;
	char		buf[80];
	time_t		tme;
	STAT		junk;

	tp = &tme;
	if (Fromfile && getyn(SAMEFILEPROMPT))
		strcpy(buf, Fromfile);
	else {
over:
		prompt(FILEPROMPT);
		leaveok(Board, FALSE);
		refresh();
		sp = buf;
		while ((*sp = readch()) != '\n') {
			if (*sp == killchar())
				goto over;
			else if (*sp == erasechar()) {
				if (--sp < buf)
					sp = buf;
				else {
					addch('\b');
					/*
					 * if the previous char was a control
					 * char, cover up two characters.
					 */
					if (*sp < ' ')
						addch('\b');
					clrtoeol();
				}
			}
D 3
			else
				addstr(unctrl(*sp++));
E 3
I 3
			else {
				addstr(unctrl(*sp));
				++sp;
			}
E 3
			refresh();
		}
		*sp = '\0';
		leaveok(Board, TRUE);
	}

	/*
	 * check for existing files, and confirm overwrite if needed
	 */

	if (sp == buf || (!Fromfile && stat(buf, &junk) > -1
	    && getyn(OVERWRITEFILEPROMPT) == FALSE))
		return FALSE;

	if ((outf = creat(buf, 0644)) < 0) {
D 5
		error(sys_errlist[errno]);
E 5
I 5
		error(strerror(errno));
E 5
		return FALSE;
	}
	mvwaddstr(Score, ERR_Y, ERR_X, buf);
	wrefresh(Score);
	time(tp);			/* get current time		*/
	strcpy(buf, ctime(tp));
	for (sp = buf; *sp != '\n'; sp++)
		continue;
	*sp = '\0';
	varpush(outf, write);
	close(outf);
	wprintw(Score, " [%s]", buf);
	wclrtoeol(Score);
	wrefresh(Score);
	return TRUE;
}

/*
 *	This does the actual restoring.  It returns TRUE if the
 * backup was made on exiting, in which case certain things must
 * be cleaned up before the game starts.
 */
rest_f(file)
reg char	*file; {

	reg char	*sp;
	reg int		inf;
	char		buf[80];
	STAT		sbuf;

	if ((inf = open(file, 0)) < 0) {
		perror(file);
		exit(1);
	}
	if (fstat(inf, &sbuf) < 0) {		/* get file stats	*/
		perror(file);
		exit(1);
	}
	varpush(inf, read);
	close(inf);
	strcpy(buf, ctime(&sbuf.st_mtime));
	for (sp = buf; *sp != '\n'; sp++)
		continue;
	*sp = '\0';
	/*
	 * initialize some necessary values
	 */
D 2
	sprintf(Initstr, "%s [%s]\n", file, buf);
E 2
I 2
	(void)sprintf(Initstr, "%s [%s]\n", file, buf);
E 2
	Fromfile = file;
	return !On_exit;
}

E 1
