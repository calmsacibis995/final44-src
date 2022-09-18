h39761
s 00004/00003/00203
d D 8.8 94/10/25 15:59:23 bostic 45 44
c handle tgoto functions that return NULL, not "OOPS"
e
s 00003/00003/00203
d D 8.7 94/07/27 17:44:48 bostic 44 43
c I got the sense of the scroll test backwards....
e
s 00005/00002/00201
d D 8.6 94/07/27 14:57:39 bostic 43 42
c add support for CS SF/sf/SR/sr combinations as scrolling commands
e
s 00002/00000/00201
d D 8.5 94/05/19 13:24:30 bostic 42 41
c add ioctl.h back in, TIOCGWINSZ on old systems.
e
s 00004/00004/00197
d D 8.4 94/05/04 06:24:58 bostic 41 40
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00001/00001/00200
d D 8.3 94/01/02 12:28:08 bostic 40 39
c it's LINES, not ROWS!
e
s 00003/00003/00198
d D 8.2 94/01/02 12:27:33 bostic 39 38
c delete HZ, it's Hazeltine specific, and conflicts with HZ as Hertz
e
s 00002/00002/00199
d D 8.1 93/06/04 16:49:12 bostic 38 37
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00194
d D 5.19 93/05/16 15:54:50 bostic 37 36
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00011/00014/00190
d D 5.18 93/05/10 12:16:01 bostic 36 35
c delete a section of code that, as far as I can tell has no effect
c only AL and DL are used in the scrolling implementation, and setting them to
c empty strings means that no scrolling will happen, since the test is against
c NULL, not an empty string.  I have no idea what this was supposed to do.
e
s 00002/00003/00202
d D 5.17 93/04/15 14:43:41 elan 35 34
c LINES can be any number.  No restriction.  COLS should be > 4.
e
s 00011/00003/00194
d D 5.16 93/02/18 16:58:52 elan 34 33
c Deleted vacuous destline and destcol variables.
e
s 00001/00001/00196
d D 5.15 93/02/03 16:41:18 elan 33 32
c Fixed missing "db".
e
s 00002/00002/00195
d D 5.14 93/01/11 11:54:01 bostic 32 31
c CURSES_{OK,ERR} -> OK,ERR
e
s 00002/00002/00195
d D 5.13 92/12/30 14:55:12 elan 31 30
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00001/00002/00196
d D 5.12 92/12/22 15:02:49 bostic 30 29
c destcol, destline don't need to be static
e
s 00007/00003/00191
d D 5.11 92/09/21 15:24:57 elan 29 28
c Added AL, DL, SF, SR support.
e
s 00009/00002/00185
d D 5.10 92/09/14 11:00:42 elan 28 27
c Converted to new data structures.
e
s 00088/00114/00099
d D 5.9 92/08/23 14:42:48 bostic 27 25
c rewrite for the new tty driver, 4.4BSD
e
s 00136/00169/00044
d R 5.9 92/05/15 15:32:11 bostic 26 25
c move termcap routines into setterm.c; rewrite for termios interface
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00212
d D 5.8 90/06/01 15:37:49 bostic 25 24
c new copyright notice
e
s 00003/00002/00220
d D 5.7 89/09/13 11:54:12 bostic 24 23
c typo; tgoto isn't static; bug report 4.3BSD-tahoe/lib/27
e
s 00003/00003/00219
d D 5.6 89/06/29 19:28:37 bostic 23 22
c remove references to [sg]tty
e
s 00007/00001/00215
d D 5.5 89/04/13 21:03:59 bostic 22 21
c longname() steps on the second variable it is passed, so copy type
c into xtype so it isn't stepped on when you are least suspecting it.
c from John Gilmore
e
s 00010/00005/00206
d D 5.4 88/06/30 17:21:23 bostic 21 20
c install approved copyright notice
e
s 00010/00004/00201
d D 5.3 88/06/08 13:56:51 bostic 20 19
c written by Ken Arnold; add Berkeley specific header
e
s 00002/00001/00203
d D 5.2 85/11/08 17:18:32 bloom 19 18
c make sure fetching the terminal type doesn't clobber anything
e
s 00010/00001/00194
d D 5.1 85/06/07 11:27:08 dist 18 17
c Add copyright
e
s 00014/00009/00181
d D 1.17 85/05/23 15:41:29 bloom 17 16
c add support for XS (from arnold)
e
s 00058/00039/00132
d D 1.16 85/05/01 16:50:04 bloom 16 15
c new version from arnold
e
s 00008/00000/00163
d D 1.15 85/02/21 11:33:25 bloom 15 14
c do ioctl to get window size
e
s 00005/00004/00158
d D 1.14 83/06/01 14:05:55 arnold 14 13
c only use SO or US if SG or UG are 0
e
s 00001/00004/00161
d D 1.13 83/05/19 12:11:10 arnold 13 12
c no check for too many lines or columns
e
s 00002/00002/00163
d D 1.12 83/03/27 15:08:38 arnold 12 11
c 
e
s 00001/00001/00164
d D 1.11 82/04/01 12:13:26 arnold 11 10
c make checking for SG and UG work properly
e
s 00006/00006/00159
d D 1.10 82/02/17 14:12:15 arnold 10 9
c adopt latest version of fgoto() and plod() from vi
e
s 00000/00002/00165
d D 1.9 82/02/16 16:02:36 arnold 9 8
c should undef DEBUG
e
s 00001/00001/00166
d D 1.8 81/10/31 17:16:23 arnold 8 7
c increase size of tspace
e
s 00007/00004/00160
d D 1.7 81/10/26 00:32:45 arnold 7 6
c don't support terminals with garbage for standout
e
s 00002/00000/00162
d D 1.6 81/10/26 00:12:14 arnold 6 5
c properly define tgetent()
e
s 00001/00000/00161
d D 1.5 81/10/26 00:01:54 arnold 5 4
c stty to turn off tab expansion on ALL terminals
e
s 00010/00000/00151
d D 1.4 81/05/15 16:22:14 arnold 4 3
c add getcap function
e
s 00001/00000/00150
d D 1.3 81/04/28 12:19:12 arnold 3 2
c turn off tab expansion for cursor addressing
e
s 00001/00001/00149
d D 1.2 81/02/17 15:43:21 arnold 2 1
c make it so that longname() is not redefined here
e
s 00150/00000/00000
d D 1.1 81/01/26 17:02:44 arnold 1 0
c date and time created 81/01/26 17:02:44 by arnold
e
u
U
t
T
I 1
/*
I 18
D 20
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
D 38
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 38
I 38
D 41
 * Copyright (c) 1981, 1993
E 41
I 41
 * Copyright (c) 1981, 1993, 1994
E 41
 *	The Regents of the University of California.  All rights reserved.
E 38
 *
D 25
 * Redistribution and use in source and binary forms are permitted
D 21
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 21
I 21
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
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 21
E 20
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20

I 42
#include <sys/ioctl.h>		/* TIOCGWINSZ on old systems. */

E 42
D 27
/*
E 18
 * Terminal initialization routines.
 *
D 16
 * %G% (Berkeley) %W%
E 16
I 16
D 18
 * %W% (Berkeley) %G%
E 18
E 16
 */
E 27
I 27
D 41
#include <sys/ioctl.h>
E 27

D 9
# undef	DEBUG

E 9
D 27
# include	"curses.ext"
E 27
I 27
#include <curses.h>
E 41
#include <stdlib.h>
#include <string.h>
I 41
#include <termios.h>
E 41
#include <unistd.h>
I 41

#include "curses.h"
E 41
E 27
D 10
# include	"cr_ex.h"
E 10

D 16
static bool	*sflags[]	= {
			&AM, &BS, &EO, &HZ, &IN, &MI, &MS, &NC, &OS, &UL, &XN
E 16
I 16
D 27
static bool	*sflags[] = {
			&AM, &BS, &DA, &DB, &EO, &HC, &HZ, &IN, &MI,
D 17
			&MS, &NC, &NS, &OS, &UL, &XB, &XN, &XT, &XX
E 17
I 17
			&MS, &NC, &NS, &OS, &UL, &XB, &XN, &XT, &XS,
			&XX
E 27
I 27
static void zap __P((void));

static char	*sflags[] = {
I 36
D 39
		/*       am   bs   da   eo   hc   hz   in   mi   ms  */
E 36
			&AM, &BS, &DA, &EO, &HC, &HZ, &IN, &MI, &MS,
E 39
I 39
		/*       am   bs   da   eo   hc   in   mi   ms  */
			&AM, &BS, &DA, &EO, &HC, &IN, &MI, &MS,
E 39
I 36
		/*	 nc   ns   os   ul   xb   xn   xt   xs   xx  */
E 36
			&NC, &NS, &OS, &UL, &XB, &XN, &XT, &XS, &XX
E 27
E 17
E 16
		};

D 16
static char	*xPC,
		**sstrs[]	= {
D 10
			&AL, &BC,  &BT, &CD, &CE, &CL, &CM, &DC, &DL,
			&DM, &DO,  &ED, &EI, &HO, &IC, &IM, &IP, &LL,
			&MA, &ND, &xPC, &SE, &SF, &SO, &SR, &TA, &TE,
			&TI, &UC,  &UE, &UP, &US, &VB, &VS, &VE
E 10
I 10
			&AL, &BC, &BT, &CD,  &CE, &CL, &CM, &CR, &DC,
			&DL, &DM, &DO, &ED,  &EI, &HO, &IC, &IM, &IP,
			&LL, &MA, &ND, &NL, &xPC, &SE, &SF, &SO, &SR,
			&TA, &TE, &TI, &UC,  &UE, &UP, &US, &VB, &VS,
			&VE
E 16
I 16
static char	*_PC,
		**sstrs[] = {
I 36
		/*	 AL   bc   bt   cd   ce   cl   cm   cr   cs  */
E 36
			&AL, &BC, &BT, &CD, &CE, &CL, &CM, &CR, &CS,
I 36
		/*	 dc   DL   dm   do   ed   ei   k0   k1   k2  */
E 36
			&DC, &DL, &DM, &DO, &ED, &EI, &K0, &K1, &K2,
I 36
		/*	 k3   k4   k5   k6   k7   k8   k9   ho   ic  */
E 36
			&K3, &K4, &K5, &K6, &K7, &K8, &K9, &HO, &IC,
I 36
		/*	 im   ip   kd   ke   kh   kl   kr   ks   ku  */
E 36
			&IM, &IP, &KD, &KE, &KH, &KL, &KR, &KS, &KU,
I 36
		/*	 ll   ma   nd   nl    pc   rc   sc   se   SF */
E 36
			&LL, &MA, &ND, &NL, &_PC, &RC, &SC, &SE, &SF,
I 36
		/*	 so   SR   ta   te   ti   uc   ue   up   us  */
E 36
			&SO, &SR, &TA, &TE, &TI, &UC, &UE, &UP, &US,
I 36
		/*	 vb   vs   ve   al   dl   sf   sr   AL	     */
E 36
D 29
			&VB, &VS, &VE, &AL_PARM, &DL_PARM, &UP_PARM,
			&DOWN_PARM, &LEFT_PARM, &RIGHT_PARM,
E 29
I 29
			&VB, &VS, &VE, &al, &dl, &sf, &sr, &AL_PARM, 
I 36
		/*	 DL	   UP	     DO		 LE	     */
E 36
			&DL_PARM, &UP_PARM, &DOWN_PARM, &LEFT_PARM, 
I 36
		/*	 RI					     */
E 36
			&RIGHT_PARM,
E 29
E 16
E 10
D 24
		},
D 2
		*longname(), *tgoto();
E 2
I 2
		*tgoto();
E 24
I 24
		};

D 27
extern char	*tgoto();
E 24
E 2

D 8
static char	tspace[128],		/* Space for capability strings */
E 8
I 8
D 16
static char	tspace[256],		/* Space for capability strings */
E 8
		*aoftspace;		/* Address of tspace for relocation */
E 16
I 16
char		_tspace[2048];		/* Space for capability strings */
E 16

E 27
I 16
static char	*aoftspace;		/* Address of _tspace for relocation */
I 27
static char	tspace[2048];		/* Space for capability strings */
E 27

E 16
D 30
static int	destcol, destline;

E 30
D 27
/*
 *	This routine does terminal type initialization routines, and
 * calculation of flags at entry.  It is almost entirely stolen from
 * Bill Joy's ex version 2.6.
 */
short	ospeed = -1;
E 27
I 27
char *ttytype;
E 27

D 27
gettmode() {

D 23
	if (gtty(_tty_ch, &_tty) < 0)
E 23
I 23
	if (ioctl(_tty_ch, TIOCGETP, &_tty) < 0)
E 23
		return;
	savetty();
D 23
	if (stty(_tty_ch, &_tty) < 0)
E 23
I 23
	if (ioctl(_tty_ch, TIOCSETP, &_tty) < 0)
E 23
		_tty.sg_flags = _res_flg;
	ospeed = _tty.sg_ospeed;
	_res_flg = _tty.sg_flags;
	UPPERCASE = (_tty.sg_flags & LCASE) != 0;
	GT = ((_tty.sg_flags & XTABS) == 0);
	NONL = ((_tty.sg_flags & CRMOD) == 0);
I 3
	_tty.sg_flags &= ~XTABS;
I 5
D 23
	stty(_tty_ch, &_tty);
E 23
I 23
	ioctl(_tty_ch, TIOCSETP, &_tty);
E 23
E 5
E 3
# ifdef DEBUG
	fprintf(outf, "GETTMODE: UPPERCASE = %s\n", UPPERCASE ? "TRUE":"FALSE");
	fprintf(outf, "GETTMODE: GT = %s\n", GT ? "TRUE" : "FALSE");
	fprintf(outf, "GETTMODE: NONL = %s\n", NONL ? "TRUE" : "FALSE");
	fprintf(outf, "GETTMODE: ospeed = %d\n", ospeed);
# endif
}

E 27
I 27
int
E 27
setterm(type)
D 27
reg char	*type; {

D 12
	reg int	unknown;
	char	genbuf[1024];
E 12
I 12
	reg int		unknown;
	static char	genbuf[1024];
I 16
# ifdef TIOCGWINSZ
E 27
I 27
	register char *type;
{
	static char genbuf[1024];
	static char __ttytype[1024];
	register int unknown;
I 30
D 34
	int destcol, destline;
E 34
E 30
E 27
E 16
I 15
	struct winsize win;
I 16
D 27
# endif
E 27
I 27
	char *p;
E 27
E 16
E 15
E 12

D 27
# ifdef DEBUG
	fprintf(outf, "SETTERM(\"%s\")\n", type);
	fprintf(outf, "SETTERM: LINES = %d, COLS = %d\n", LINES, COLS);
# endif
E 27
I 27
#ifdef DEBUG
D 37
	__TRACE("setterm: (\"%s\")\nLINES = %d, COLS = %d\n",
E 37
I 37
	__CTRACE("setterm: (\"%s\")\nLINES = %d, COLS = %d\n",
E 37
	    type, LINES, COLS);
#endif
E 27
	if (type[0] == '\0')
		type = "xx";
D 27
	unknown = FALSE;
E 27
I 27
	unknown = 0;
E 27
	if (tgetent(genbuf, type) != 1) {
		unknown++;
		strcpy(genbuf, "xx|dumb:");
	}
D 27
# ifdef DEBUG
	fprintf(outf, "SETTERM: tty = %s\n", type);
# endif
I 16
# ifdef TIOCGWINSZ
E 16
I 15
	if (ioctl(_tty_ch, TIOCGWINSZ, &win) >= 0) {
		if (LINES == 0)
			LINES = win.ws_row;
		if (COLS == 0)
			COLS = win.ws_col;
	}
I 16
# endif
E 27
I 27
#ifdef DEBUG
D 37
	__TRACE("setterm: tty = %s\n", type);
E 37
I 37
	__CTRACE("setterm: tty = %s\n", type);
E 37
#endif
E 27
E 16

E 15
D 27
	if (LINES == 0)
E 27
I 27
	/* Try TIOCGWINSZ, and, if it fails, the termcap entry. */
	if (ioctl(STDERR_FILENO, TIOCGWINSZ, &win) != -1 &&
	    win.ws_row != 0 && win.ws_col != 0) {
		LINES = win.ws_row;
		COLS = win.ws_col;
	}  else {
E 27
		LINES = tgetnum("li");
D 27
	if (LINES <= 5)
		LINES = 24;
D 13
	else if (LINES > 48)
		LINES = 48;
E 13

	if (COLS == 0)
E 27
		COLS = tgetnum("co");
D 27
	if (COLS <= 4)
		COLS = 80;
E 27
I 27
	}
E 27
D 13
	else if (COLS > 1000)
		COLS = 1000;
E 13
I 13

E 13
D 27
# ifdef DEBUG
	fprintf(outf, "SETTERM: LINES = %d, COLS = %d\n", LINES, COLS);
# endif
D 16
	aoftspace = tspace;
E 16
I 16
	aoftspace = _tspace;
E 16
	zap();			/* get terminal description		*/
E 27
I 27
	/* POSIX 1003.2 requires that the environment override. */
D 40
	if ((p = getenv("ROWS")) != NULL)
E 40
I 40
	if ((p = getenv("LINES")) != NULL)
E 40
		LINES = strtol(p, NULL, 10);
	if ((p = getenv("COLUMNS")) != NULL)
		COLS = strtol(p, NULL, 10);
E 27
I 16

	/*
D 27
	 * Handle funny termcap capabilities
E 27
I 27
D 35
	 * XXX
	 * Historically, curses fails if rows <= 5, cols <= 4.
E 35
I 35
	 * Want cols > 4, otherwise things will fail.
E 35
E 27
	 */
D 27
	if (CS && SC && RC) AL=DL="";
	if (AL_PARM && AL==NULL) AL="";
	if (DL_PARM && DL==NULL) DL="";
	if (IC && IM==NULL) IM="";
	if (IC && EI==NULL) EI="";
	if (!GT) BT=NULL;	/* If we can't tab, we can't backtab either */
E 27
I 27
D 35
	if (LINES <= 5 || COLS <= 4)
E 35
I 35
	if (COLS <= 4)
E 35
D 31
		return (ERR);
E 31
I 31
D 32
		return (CURSES_ERR);
E 32
I 32
		return (ERR);
E 32
E 31
E 27

E 16
D 27
	if (tgoto(CM, destcol, destline)[0] == 'O')
		CA = FALSE, CM = 0;
	else
		CA = TRUE;
E 27
I 27
#ifdef DEBUG
D 37
	__TRACE("setterm: LINES = %d, COLS = %d\n", LINES, COLS);
E 37
I 37
	__CTRACE("setterm: LINES = %d, COLS = %d\n", LINES, COLS);
E 37
#endif
	aoftspace = tspace;
	zap();			/* Get terminal description. */
E 27
D 16
	PC = xPC ? xPC[0] : FALSE;
	aoftspace = tspace;
E 16
I 16
D 36

D 27
	PC = _PC ? _PC[0] : FALSE;
	aoftspace = _tspace;
E 16
D 19
	strcpy(ttytype, longname(genbuf, type));
E 19
I 19
D 22
	strncpy(ttytype, longname(genbuf, type), sizeof(ttytype) - 1);
E 22
I 22
	{
		/* xtype should be the same size as genbuf for longname(). */
		static char xtype[1024];

		(void)strcpy(xtype,type);
		strncpy(ttytype, longname(genbuf, xtype), sizeof(ttytype) - 1);
E 27
I 27
	/* Handle funny termcap capabilities. */
	if (CS && SC && RC)
		AL = DL = "";
	if (AL_PARM && AL == NULL)
		AL = "";
	if (DL_PARM && DL == NULL)
		DL = "";
	if (IC) {
		if (IM == NULL)
			IM = "";
		if (EI == NULL)
			EI = "";
E 27
	}
E 36
E 22
D 27
	ttytype[sizeof(ttytype) - 1] = '\0';
E 19
	if (unknown)
		return ERR;
	return OK;
E 27
I 27
D 34
	if (!GT)		/* If we can't tab, we can't backtab either. */
E 34
I 34

	/* If we can't tab, we can't backtab, either. */
	if (!GT)
E 34
		BT = NULL;

D 34
	if (tgoto(CM, destcol, destline)[0] == 'O') {
E 34
I 34
	/*
	 * Test for cursor motion capbility.
	 *
	 * XXX
D 45
	 * This is truly stupid -- tgoto returns "OOPS" if it can't
	 * do cursor motions.
E 45
I 45
	 * This is truly stupid -- historically, tgoto returns "OOPS" if it
	 * can't do cursor motions.  Some systems have been fixed to return
	 * a NULL pointer.
E 45
	 */
D 45
	if (tgoto(CM, 0, 0)[0] == 'O') {
E 45
I 45
	if ((p = tgoto(CM, 0, 0)) == NULL || *p == 'O') {
E 45
E 34
		CA = 0;
		CM = 0;
	} else
		CA = 1;

	PC = _PC ? _PC[0] : 0;
	aoftspace = tspace;
	ttytype = longname(genbuf, __ttytype);

I 29
D 43
	if ((!AL && !al) || (!DL && !dl))
		__noqch = 1;
E 43
I 43
	/* If no scrolling commands, no quick change. */
	__noqch =
D 44
	    CS != NULL && HO != NULL &&
	    (SF != NULL || sf != NULL) && (SR != NULL || sr != NULL) ||
	    (AL != NULL || al != NULL) && (DL != NULL || dl != NULL);
E 44
I 44
	    (CS == NULL || HO == NULL ||
	    SF == NULL && sf == NULL || SR == NULL && sr == NULL) &&
	    (AL == NULL && al == NULL || DL == NULL && dl == NULL);
E 44
E 43

E 29
D 31
	return (unknown ? ERR : OK);
E 31
I 31
D 32
	return (unknown ? CURSES_ERR : CURSES_OK);
E 32
I 32
	return (unknown ? ERR : OK);
E 32
E 31
E 27
}
I 16

E 16
/*
D 7
 *	This routine gets all the terminal falgs from the termcap database
E 7
I 7
D 27
 *	This routine gets all the terminal flags from the termcap database
E 27
I 27
 * zap --
 *	Gets all the terminal flags from the termcap database.
E 27
E 7
 */
D 16
zap() {
E 16
D 27

E 27
I 27
static void
E 27
D 16
	reg bool	**fp;
	reg char	*namp, ***sp;
E 16
I 16
zap()
{
D 27
	register char	*namp;
	register bool	**fp;
	register char	***sp;
#ifdef	DEBUG
E 27
I 27
	register char *namp, ***sp;
	register char **fp;
I 28
	char tmp[3];
E 28
#ifdef DEBUG
E 27
	register char	*cp;
#endif
I 28
	tmp[2] = '\0';
E 28
E 16
I 7
D 14
	reg int		SG, UG;
E 14
E 7
D 27
	extern char	*tgetstr();
E 27

D 16
	/*
	 * get boolean flags
	 */
 	namp = "ambseohzinmimsncosulxn\0\0";
# ifdef FULLDEBUG
	fprintf(outf, "ZAP: namp = \"%s\"\n", namp);
# endif
E 16
I 16
D 17
	namp = "ambsdadbeohchzinmimsncnsosulxbxnxtxx";
E 17
I 17
D 33
	namp = "ambsdadbeohchzinmimsncnsosulxbxnxtxsxx";
E 33
I 33
D 39
	namp = "ambsdaeohchzinmimsncnsosulxbxnxtxsxx";
E 39
I 39
	namp = "ambsdaeohcinmimsncnsosulxbxnxtxsxx";
E 39
E 33
E 17
E 16
	fp = sflags;
	do {
D 28
		*(*fp++) = tgetflag(namp);
E 28
I 28
		*tmp = *namp;
		*(tmp + 1) = *(namp + 1);
		*(*fp++) = tgetflag(tmp);
E 28
D 16
# ifdef FULLDEBUG
		fprintf(outf, "ZAP: %.2s = %d", namp, *(*(fp - 1)));
# endif
E 16
I 16
#ifdef DEBUG
D 27
		fprintf(outf, "%2.2s = %s\n", namp, *fp[-1] ? "TRUE" : "FALSE");
E 27
I 27
D 37
		__TRACE("2.2s = %s\n", namp, *fp[-1] ? "TRUE" : "FALSE");
E 37
I 37
		__CTRACE("2.2s = %s\n", namp, *fp[-1] ? "TRUE" : "FALSE");
E 37
E 27
#endif
E 16
		namp += 2;
I 28
		
E 28
	} while (*namp);
D 16

	/*
	 * get string values
	 */
D 10
	namp = "albcbtcdceclcmdcdldmdoedeihoicimipllmandpcsesfsosrtatetiucueupusvbvsve";
E 10
I 10
	namp = "albcbtcdceclcmcrdcdldmdoedeihoicimipllmandnlpcsesfsosrtatetiucueupusvbvsve";
E 10
# ifdef FULLDEBUG
	fprintf(outf, "ZAP: namp = \"%s\"\n", namp);
# endif
E 16
I 16
D 29
	namp = "albcbtcdceclcmcrcsdcdldmdoedeik0k1k2k3k4k5k6k7k8k9hoicimipkdkekhklkrkskullmandnlpcrcscsesfsosrtatetiucueupusvbvsveALDLUPDOLERI";
E 29
I 29
	namp = "ALbcbtcdceclcmcrcsdcDLdmdoedeik0k1k2k3k4k5k6k7k8k9hoicimipkdkekhklkrkskullmandnlpcrcscseSFsoSRtatetiucueupusvbvsvealdlsfsrALDLUPDOLERI";
E 29
E 16
	sp = sstrs;
	do {
D 28
		*(*sp++) = tgetstr(namp, &aoftspace);
E 28
I 28
		*tmp = *namp;
		*(tmp + 1) = *(namp + 1);
		*(*sp++) = tgetstr(tmp, &aoftspace);
E 28
D 16
# ifdef FULLDEBUG
		fprintf(outf, "ZAP: %.2s = \"%s\"\n", namp, *(*(sp-1)));
# endif
E 16
I 16
#ifdef DEBUG
D 27
		fprintf(outf, "%2.2s = %s", namp, *sp[-1] == NULL ? "NULL\n" : "\"");
E 27
I 27
D 37
		__TRACE("2.2s = %s", namp, *sp[-1] == NULL ? "NULL\n" : "\"");
E 37
I 37
		__CTRACE("2.2s = %s", namp, *sp[-1] == NULL ? "NULL\n" : "\"");
E 37
E 27
		if (*sp[-1] != NULL) {
			for (cp = *sp[-1]; *cp; cp++)
D 27
				fprintf(outf, "%s", unctrl(*cp));
			fprintf(outf, "\"\n");
E 27
I 27
D 37
				__TRACE("%s", unctrl(*cp));
			__TRACE("\"\n");
E 37
I 37
				__CTRACE("%s", unctrl(*cp));
			__CTRACE("\"\n");
E 37
E 27
		}
#endif
E 16
		namp += 2;
	} while (*namp);
D 7
	if (!SO && US) {
E 7
I 7
D 14
	SG = tgetnum("sg");
	UG = tgetnum("ug");
D 11
	if ((SG || !SO) && (!UG && US)) {
E 11
I 11
	if ((SG > 0 || !SO) && (UG <= 0 && US)) {
E 14
I 14
D 17
	if (tgetnum("sg") > 0)
		SO = NULL;
	if (tgetnum("ug") > 0)
		US = NULL;
	if (!SO && US) {
E 14
E 11
E 7
		SO = US;
		SE = UE;
E 17
I 17
	if (XS)
		SO = SE = NULL;
	else {
		if (tgetnum("sg") > 0)
			SO = NULL;
		if (tgetnum("ug") > 0)
			US = NULL;
		if (!SO && US) {
			SO = US;
			SE = UE;
		}
E 17
	}
}
I 4

/*
D 27
 * return a capability from termcap
E 27
I 27
 * getcap --
 *	Return a capability from termcap.
E 27
 */
char *
getcap(name)
D 27
char *name;
E 27
I 27
	char *name;
E 27
{
I 6
D 7
	char *tgetent();
E 7
I 7
D 27
	char *tgetstr();
E 7

E 6
D 7
	return tgetent(name, &aoftspace);
E 7
I 7
	return tgetstr(name, &aoftspace);
E 27
I 27
	return (tgetstr(name, &aoftspace));
E 27
E 7
}
E 4
E 1
