h10279
s 00001/00001/00165
d D 8.2 95/04/29 11:50:27 bostic 21 20
c was returning NULL on error, dropping core
e
s 00002/00002/00164
d D 8.1 93/06/06 16:28:41 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00165
d D 5.12 93/05/21 15:34:11 mckusick 19 18
c update header to reflect redistributable status
e
s 00000/00023/00166
d D 5.11 93/05/12 12:43:32 elan 18 17
c No private suspend routine.  Use curses.
e
s 00006/00009/00183
d D 5.10 92/07/23 17:56:40 bostic 17 16
c update copyright/header
e
s 00018/00009/00174
d D 5.9 92/07/23 17:45:00 bostic 16 15
c Elan's new kvm lib; clean up signal handling
e
s 00001/00000/00182
d D 5.8 91/04/25 14:29:05 bostic 15 14
c ANSI
e
s 00001/00001/00181
d D 5.7 90/03/12 09:34:34 karels 14 13
c new signal type; mv cursor to bottom when interrupted
e
s 00001/00001/00181
d D 5.6 88/01/03 00:43:16 bostic 13 12
c fix external declarations for ANSI C
e
s 00001/00001/00181
d D 5.5 87/03/26 00:25:57 tef 12 11
c Must distinguish between "ambiguous" and "unknown" commands.
e
s 00005/00004/00177
d D 5.4 85/12/11 16:07:16 bloom 11 10
c fix problem with losing /vmunix in the middle, a bit of lint cleanup
e
s 00001/00001/00180
d D 5.3 85/10/18 19:03:07 mckusick 10 9
c must return -1, not 0 on bad flag (from eric)
e
s 00002/00002/00179
d D 5.2 85/08/13 11:09:04 mckusick 9 8
c let curses handle SIGTSTP
e
s 00007/00001/00174
d D 5.1 85/05/30 16:19:35 mckusick 8 7
c Add copyright
e
s 00026/00013/00149
d D 1.7 85/05/01 01:33:13 sam 7 6
c major rework; fixup netstat stuff; pull disk cmds into common file; change 
c everthing related to disks to use dk_ndrive and global selction; use getw where possible
e
s 00009/00000/00153
d D 1.6 85/04/29 00:09:51 sam 6 5
c try and recover from display open errors
e
s 00027/00009/00126
d D 1.5 85/04/28 00:37:05 sam 5 4
c add vsta in; add help command (minimal); make loadav display something 
c which can be turned off
e
s 00012/00011/00123
d D 1.4 84/08/09 19:13:24 mckusick 4 3
c update to new sources from sam; weed out unnecessary #includes
e
s 00027/00027/00107
d D 1.3 83/10/02 22:39:28 sam 3 2
c handle ambiguous commands properly
e
s 00004/00008/00130
d D 1.2 83/10/02 21:59:50 sam 2 1
c add command prefix recognition
e
s 00138/00000/00000
d D 1.1 83/10/02 21:41:00 sam 1 0
c date and time created 83/10/02 21:41:00 by sam
e
u
U
t
T
I 8
D 17
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
/*-
D 20
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 19
 * %sccs.include.proprietary.c%
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 17
 */

E 8
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% (Lucasfilm) %G%";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
D 8
#endif
E 8
I 8
D 17
#endif not lint
E 8

/*
 * Command support.
 */
E 17
I 17
#endif /* not lint */
E 17

D 16
#include "systat.h"
E 16
I 16
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
E 16
I 4
D 7
#include <signal.h>
E 7
#include <ctype.h>
I 16
#include <string.h>
#include "systat.h"
#include "extern.h"
E 16
E 4

I 16
void
E 16
command(cmd)
        char *cmd;
{
D 16
        register char *cp;
E 16
        register struct cmdtab *p;
I 16
        register char *cp;
E 16
I 5
D 7
	int interval;
E 7
I 7
	int interval, omask;
E 7
E 5
D 11
        char *arg;
E 11
I 9
D 13
	extern (*sigtstpdfl)();
E 13
E 9

I 7
	omask = sigblock(sigmask(SIGALRM));
E 7
        for (cp = cmd; *cp && !isspace(*cp); cp++)
                ;
        if (*cp)
                *cp++ = '\0';
I 3
	if (*cmd == '\0')
		return;
I 4
	for (; *cp && isspace(*cp); cp++)
		;
E 4
E 3
D 2
        if (strcmp(cmd, "quit") == 0)
E 2
I 2
        if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "q") == 0)
E 2
D 16
                die();
E 16
I 16
                die(0);
E 16
D 2
        if (strcmp(cmd, "status") == 0 || strcmp(cmd, "help") == 0) {
                status();
                return;
        }
E 2
	if (strcmp(cmd, "load") == 0) {
		load();
D 7
		return;
E 7
I 7
		goto done;
E 7
	}
D 2
	p = getcmd(cmd);
E 2
I 2
D 3
	p = lookup(cmd);
E 2
        if (p != (struct cmdtab *)-1) {
                if (curcmd == p)
                        return;
                alarm(0);
		(*curcmd->c_close)(wnd);
		wnd = (*p->c_open)();
                curcmd = p;
		if (p->c_flags == 0) {
			(*p->c_init)();
			p->c_flags = 1;
		}
		labels();
                display();
                status();
                return;
        }
E 3
        if (strcmp(cmd, "stop") == 0) {
                alarm(0);
D 4
                mvaddstr(22, 0, "Refresh disabled.");
E 4
I 4
                mvaddstr(CMDLINE, 0, "Refresh disabled.");
E 4
                clrtoeol();
D 7
                return;
E 7
I 7
		goto done;
E 7
        }
D 3
        /* commands with arguments */
        for (; *cp && isspace(*cp); cp++)
                ;
E 3
D 2
        if (strcmp(cmd, "start") == 0) {
E 2
I 2
D 5
        if (strcmp(cmd, "start") == 0 || strcmp(cmd, "interval") == 0) {
E 2
                int x;
E 5
I 5
	if (strcmp(cmd, "help") == 0) {
		int col, len;
E 5

D 3
                if (*cp == '\0')
                        x = naptime;
                else
                        x = atoi(cp);
E 3
I 3
D 4
		for (; *cp && isspace(*cp); cp++)
			;
E 4
D 5
		x = *cp ? atoi(cp) : naptime;
E 3
                if (x <= 0) {
D 4
                        mvprintw(22, 0, "%d: bad interval.", x);
                        clrtoeol();
E 4
I 4
			error("%d: bad interval.", x);
E 5
I 5
		move(CMDLINE, col = 0);
		for (p = cmdtab; p->c_name; p++) {
			len = strlen(p->c_name);
			if (col + len > COLS)
				break;
			addstr(p->c_name); col += len;
			if (col + 1 < COLS)
				addch(' ');
		}
		clrtoeol();
D 7
		return;
E 7
I 7
		goto done;
E 7
	}
	interval = atoi(cmd);
        if (interval <= 0 &&
	    (strcmp(cmd, "start") == 0 || strcmp(cmd, "interval") == 0)) {
		interval = *cp ? atoi(cp) : naptime;
                if (interval <= 0) {
			error("%d: bad interval.", interval);
E 5
E 4
D 7
                        return;
E 7
I 7
			goto done;
E 7
                }
I 5
	}
	if (interval > 0) {
E 5
                alarm(0);
D 5
                naptime = x;
E 5
I 5
                naptime = interval;
E 5
D 16
                display();
E 16
I 16
                display(0);
E 16
                status();
D 7
                return;
E 7
I 7
		goto done;
E 7
        }
D 3
	if (*cmd) {
		mvprintw(22, 0, "%s: Unknown command.", cmd);
		clrtoeol();
E 3
I 3
	p = lookup(cmd);
	if (p == (struct cmdtab *)-1) {
		error("%s: Ambiguous command.", cmd);
D 7
		return;
E 7
I 7
		goto done;
E 7
E 3
	}
I 3
        if (p) {
                if (curcmd == p)
D 7
                        return;
E 7
I 7
			goto done;
E 7
                alarm(0);
		(*curcmd->c_close)(wnd);
		wnd = (*p->c_open)();
I 6
		if (wnd == 0) {
			error("Couldn't open new display");
			wnd = (*curcmd->c_open)();
			if (wnd == 0) {
				error("Couldn't change back to previous cmd");
				exit(1);
			}
			p = curcmd;
		}
E 6
D 11
                curcmd = p;
E 11
D 5
		if (p->c_flags == 0) {
E 5
I 5
		if ((p->c_flags & CF_INIT) == 0) {
E 5
D 11
			(*p->c_init)();
D 5
			p->c_flags = 1;
E 5
I 5
			p->c_flags |= CF_INIT;
E 11
I 11
			if ((*p->c_init)())
				p->c_flags |= CF_INIT;
			else
				goto done;
E 11
E 5
		}
I 11
                curcmd = p;
E 11
		labels();
D 16
                display();
E 16
I 16
                display(0);
E 16
                status();
D 7
                return;
E 7
I 7
		goto done;
E 7
        }
D 4
	mvprintw(22, 0, "%s: Unknown command.", cmd);
	clrtoeol();
E 4
I 4
D 7
	if (curcmd->c_cmd && (*curcmd->c_cmd)(cmd, cp))
		return;
	error("%s: Unknown command.", cmd);
E 7
I 7
	if (curcmd->c_cmd == 0 || !(*curcmd->c_cmd)(cmd, cp))
		error("%s: Unknown command.", cmd);
done:
	sigsetmask(omask);
E 7
E 4
E 3
}

struct cmdtab *
D 2
getcmd(name)
E 2
I 2
lookup(name)
E 2
	register char *name;
{
	register char *p, *q;
	register struct cmdtab *c, *found;
	register int nmatches, longest;

	longest = 0;
	nmatches = 0;
D 10
	found = 0;
E 10
I 10
D 12
	found = (struct cmdtab *)-1;
E 12
I 12
	found = (struct cmdtab *) 0;
E 12
E 10
	for (c = cmdtab; p = c->c_name; c++) {
		for (q = name; *q == *p++; q++)
			if (*q == 0)		/* exact match? */
				return (c);
		if (!*q) {			/* the name was a prefix */
			if (q - name > longest) {
				longest = q - name;
				nmatches = 1;
				found = c;
			} else if (q - name == longest)
				nmatches++;
		}
	}
D 21
	if (nmatches > 1)
E 21
I 21
	if (nmatches != 1)
E 21
		return ((struct cmdtab *)-1);
	return (found);
}

I 16
void
E 16
status()
{

D 4
        mvprintw(22, 0, "Showing %s, refresh every %d seconds.",
E 4
I 4
        error("Showing %s, refresh every %d seconds.",
E 4
          curcmd->c_name, naptime);
D 4
        clrtoeol();
E 4
}

I 15
D 18
void
E 15
D 16
suspend()
E 16
I 16
suspend(signo)
	int signo;
E 16
{
D 16
        int oldmask;
E 16
I 13
D 14
	extern (*sigtstpdfl)();
E 14
I 14
	extern sig_t sigtstpdfl;
I 16
        int oldmask;
E 16
E 14
E 13

	alarm(0);
D 4
        move(22, 0);
E 4
I 4
        move(CMDLINE, 0);
E 4
        refresh();
        echo();
        nocrmode();
D 9
        signal(SIGTSTP, SIG_DFL);
E 9
I 9
D 16
        signal(SIGTSTP, sigtstpdfl);
E 16
I 16
        (void)signal(SIGTSTP, sigtstpdfl);
E 16
E 9
        oldmask = sigsetmask(0);
        kill(getpid(), SIGTSTP);
        sigsetmask(oldmask);
D 16
        signal(SIGTSTP, suspend);
E 16
I 16
        (void)signal(SIGTSTP, suspend);
E 16
        crmode();
        noecho();
D 4
        move(22, col);
E 4
I 4
        move(CMDLINE, col);
E 4
D 9
        wrefresh(curscr);
E 9
	alarm(naptime);
I 7
}

E 18
I 16
int
E 16
prefix(s1, s2)
        register char *s1, *s2;
{

        while (*s1 == *s2) {
                if (*s1 == '\0')
                        return (1);
                s1++, s2++;
        }
        return (*s1 == '\0');
E 7
}
E 1
