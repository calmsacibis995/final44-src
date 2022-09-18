h60805
s 00002/00002/00135
d D 8.1 93/06/06 16:29:17 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00136
d D 5.9 93/05/21 15:34:19 mckusick 15 14
c update header to reflect redistributable status
e
s 00002/00002/00135
d D 5.8 92/11/10 12:24:34 elan 14 13
c Converted to new curses(3) library.
e
s 00006/00006/00131
d D 5.7 92/09/02 11:56:34 bostic 13 12
c nl is an exported curses function
e
s 00006/00006/00131
d D 5.6 92/07/24 12:41:20 bostic 12 11
c rename nlst to nl globally so can use vmstat's names.c; should not
c be a semantic change for any of these files
e
s 00044/00027/00093
d D 5.5 92/07/23 18:04:25 bostic 11 10
c Elan's new kvm version
e
s 00002/00003/00118
d D 5.4 91/06/26 13:50:32 marc 10 9
c changes for new kernel, plus use kvm
e
s 00007/00011/00114
d D 5.3 89/05/11 10:57:48 bostic 9 8
c file reorg, pathnames.h, paths.h; some reformatting
e
s 00002/00001/00123
d D 5.2 85/12/11 16:07:50 bloom 8 7
c fix problem with losing /vmunix in the middle, a bit of lint cleanup
e
s 00007/00001/00117
d D 5.1 85/05/30 16:24:12 mckusick 7 6
c Add copyright
e
s 00000/00003/00118
d D 1.6 85/05/01 01:34:18 sam 6 5
c major rework; fixup netstat stuff; pull disk cmds into common file; change 
c everthing related to disks to use dk_ndrive and global selction; use getw where possible
e
s 00018/00024/00103
d D 1.5 85/04/29 00:42:54 sam 5 4
c cleanup window handling, use subwindows exclusively
e
s 00008/00004/00119
d D 1.4 85/04/25 21:53:23 sam 4 3
c update mbuf stuff
e
s 00003/00000/00120
d D 1.3 84/08/09 19:13:20 mckusick 3 2
c update to new sources from sam; weed out unnecessary #includes
e
s 00046/00012/00074
d D 1.2 83/10/02 20:45:44 sam 2 1
c reorganize window management to allow display routines to set 
c up optimal window definitions
e
s 00086/00000/00000
d D 1.1 83/10/02 17:09:12 sam 1 0
c date and time created 83/10/02 17:09:12 by sam
e
u
U
t
T
I 7
D 11
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
/*-
D 16
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 15
 * %sccs.include.proprietary.c%
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 11
 */

E 7
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% (Lucasfilm) %G%";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
D 7
#endif
E 7
I 7
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11
E 7

D 11
#include "systat.h"
E 11
I 11
#include <sys/param.h>
#include <sys/types.h>
E 11
I 3
D 6
#include <sys/param.h>
E 6
E 3
#include <sys/mbuf.h>
I 11

#include <stdlib.h>
#include <string.h>
#include <nlist.h>
E 11
I 9
#include <paths.h>
I 11
#include "systat.h"
#include "extern.h"
E 11
E 9
I 3
D 6
#include <sys/file.h>
#include <nlist.h>
E 6
E 3

I 11
static struct mbstat *mb;

char *mtnames[] = {
	"free",
	"data",
	"headers",
	"sockets",
	"pcbs",
	"routes",
	"hosts",
	"arps",
	"socknames",
	"zombies",
	"sockopts",
	"frags",
	"rights",
	"ifaddrs",
};

#define	NNAMES	(sizeof (mtnames) / sizeof (mtnames[0]))

E 11
D 2
#define	X_MBSTAT	16

struct	mbstat *mb;

initmbufs()
E 2
I 2
WINDOW *
openmbufs()
E 2
{
I 2
D 5
	static WINDOW *w = NULL;
E 5
E 2
D 9

E 9
D 2
	if (mb == 0)
		mb = (struct mbstat *)calloc(1, sizeof (*mb));
E 2
I 2
D 5
	if (w == NULL)
        	w = newwin(20, 70, 3, 5);
	return (w);
E 5
I 5
	return (subwin(stdscr, LINES-5-1, 0, 5, 0));
E 5
E 2
}

I 11
void
E 11
D 2
fetchmbufs()
E 2
I 2
closembufs(w)
	WINDOW *w;
E 2
{
D 9

E 9
D 2
	lseek(kmem, nlst[X_MBSTAT].n_value, L_SET);
	read(kmem, mb, sizeof (*mb));
E 2
I 2
	if (w == NULL)
		return;
D 5
	move(5, 0);
	clrtobot();
E 5
	wclear(w);
	wrefresh(w);
I 5
	delwin(w);
E 5
E 2
}

I 2
D 11
struct	mbstat *mb;

E 11
I 11
void
E 11
E 2
labelmbufs()
{
D 9

D 2
        move(5, 0);
        clrtoeol();
E 2
I 2
D 5
        move(5, 0); clrtoeol();
E 2
        mvaddstr(5, 20,
                "/0   /5   /10  /15  /20  /25  /30  /35  /40  /45  /50");
E 5
I 5
        wmove(wnd, 0, 0); wclrtoeol(wnd);
        mvwaddstr(wnd, 0, 10,
           "/0   /5   /10  /15  /20  /25  /30  /35  /40  /45  /50  /55  /60");
E 9
I 9
	wmove(wnd, 0, 0); wclrtoeol(wnd);
	mvwaddstr(wnd, 0, 10,
	    "/0   /5   /10  /15  /20  /25  /30  /35  /40  /45  /50  /55  /60");
E 9
E 5
}

D 4
char *mtnames[] = {
E 4
I 4
D 5
#define	NLINES	15		/* max # which can fit on screen */
char *mtnames[NLINES] = {
E 5
I 5
D 11
char *mtnames[] = {
E 5
E 4
	"free",
	"data",
	"headers",
	"sockets",
	"pcbs",
	"routes",
	"hosts",
	"arps",
	"socknames",
	"zombies",
	"sockopts",
	"frags",
I 4
	"rights",
	"ifaddrs",
D 5
	"#14"
E 5
E 4
};
I 5
#define	NNAMES	(sizeof (mtnames) / sizeof (mtnames[0]))
E 5

E 11
I 11
void
E 11
showmbufs()
{
	register int i, j, max, index;
	char buf[10];

	if (mb == 0)
		return;
D 4
	for (j = 0; j < 15; j++) {
E 4
I 4
D 5
	for (j = 0; j < NLINES; j++) {
E 5
I 5
D 14
	for (j = 0; j < wnd->_maxy; j++) {
E 14
I 14
	for (j = 0; j < wnd->maxy; j++) {
E 14
E 5
E 4
		max = 0, index = -1; 
D 4
		for (i = 0; i < 15; i++)
E 4
I 4
D 5
		for (i = 0; i < NLINES; i++)
E 5
I 5
D 14
		for (i = 0; i < wnd->_maxy; i++)
E 14
I 14
		for (i = 0; i < wnd->maxy; i++)
E 14
E 5
E 4
			if (mb->m_mtypes[i] > max) {
				max = mb->m_mtypes[i];
				index = i;
			}
		if (max == 0)
			break;
D 5
		wmove(wnd, 3 + j, 0);
		waddstr(wnd, mtnames[index]);
		wmove(wnd, 3 + j, 15);
		if (max > 50) {
E 5
I 5
		if (j > NNAMES)
			mvwprintw(wnd, 1+j, 0, "%10d", index);
		else
			mvwprintw(wnd, 1+j, 0, "%-10.10s", mtnames[index]);
		wmove(wnd, 1 + j, 10);
		if (max > 60) {
E 5
			sprintf(buf, " %d", max);
D 5
			max = 50;
E 5
I 5
			max = 60;
E 5
			while (max--)
				waddch(wnd, 'X');
			waddstr(wnd, buf);
		} else {
			while (max--)
				waddch(wnd, 'X');
			wclrtoeol(wnd);
		}
		mb->m_mtypes[index] = 0;
	}
D 4
	while (j++ < 15) {
E 4
I 4
D 5
	while (j++ < NLINES) {
E 4
		wmove(wnd, 3 + j, 0);
		wclrtoeol(wnd);
	}
E 5
I 5
	wmove(wnd, 1+j, 0); wclrtobot(wnd);
E 5
I 2
}

D 12
static struct nlist nlst[] = {
E 12
I 12
D 13
static struct nlist nl[] = {
E 13
I 13
static struct nlist namelist[] = {
E 13
E 12
#define	X_MBSTAT	0
	{ "_mbstat" },
D 9
        { "" }
E 9
I 9
	{ "" }
E 9
};

I 11
int
E 11
initmbufs()
{
D 9

E 9
D 12
	if (nlst[X_MBSTAT].n_type == 0) {
D 9
		nlist("/vmunix", nlst);
E 9
I 9
D 10
		nlist(_PATH_UNIX, nlst);
E 10
I 10
D 11
		kvm_nlist(nlst);
E 11
I 11
		if (kvm_nlist(kd, nlst)) {
			nlisterr(nlst);
E 12
I 12
D 13
	if (nl[X_MBSTAT].n_type == 0) {
		if (kvm_nlist(kd, nl)) {
			nlisterr(nl);
E 13
I 13
	if (namelist[X_MBSTAT].n_type == 0) {
		if (kvm_nlist(kd, namelist)) {
			nlisterr(namelist);
E 13
E 12
			return(0);
		}
E 11
E 10
E 9
D 12
		if (nlst[X_MBSTAT].n_type == 0) {
E 12
I 12
D 13
		if (nl[X_MBSTAT].n_type == 0) {
E 13
I 13
		if (namelist[X_MBSTAT].n_type == 0) {
E 13
E 12
D 9
			error("namelist on /vmunix failed");
E 9
I 9
			error("namelist on %s failed", _PATH_UNIX);
E 9
D 8
			return;
E 8
I 8
			return(0);
E 8
		}
	}
	if (mb == 0)
		mb = (struct mbstat *)calloc(1, sizeof (*mb));
I 8
	return(1);
E 8
}

I 11
void
E 11
fetchmbufs()
{
D 9

E 9
D 12
	if (nlst[X_MBSTAT].n_type == 0)
E 12
I 12
D 13
	if (nl[X_MBSTAT].n_type == 0)
E 13
I 13
	if (namelist[X_MBSTAT].n_type == 0)
E 13
E 12
		return;
D 10
	lseek(kmem, nlst[X_MBSTAT].n_value, L_SET);
	read(kmem, mb, sizeof (*mb));
E 10
I 10
	NREAD(X_MBSTAT, mb, sizeof (*mb));
E 10
E 2
}
E 1
