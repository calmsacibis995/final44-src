h43815
s 00002/00002/00046
d D 8.3 94/05/04 06:24:36 bostic 19 18
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00003/00046
d D 8.2 94/01/02 12:24:25 bostic 18 17
c delete HZ, it's Hazeltine specific, and conflicts with HZ as Hertz
e
s 00002/00002/00047
d D 8.1 93/06/04 16:47:34 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00011/00039
d D 5.11 92/12/30 15:08:46 elan 16 15
c Made termcap capabilities private.
e
s 00000/00001/00050
d D 5.10 92/12/22 15:00:06 bostic 15 14
c delete __endwin (I don't understand it)
e
s 00006/00001/00045
d D 5.9 92/09/21 15:25:10 elan 14 13
c Added AL, DL, SF, SR support.
e
s 00030/00038/00016
d D 5.8 92/08/23 14:44:37 bostic 13 11
c massive cleanup, welcome to the 90's!
e
s 00030/00038/00016
d R 5.8 92/05/15 14:19:31 bostic 12 11
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00053
d D 5.7 90/06/01 15:37:56 bostic 11 10
c new copyright notice
e
s 00001/00001/00063
d D 5.6 89/11/22 13:34:28 bostic 10 9
c change default tty_ch to 0; remove for loop which purported to find
c the first "tty" file descriptor.  Effect of old code was to always set tty_ch
c to 0 (assuming that the stack was initialized to 0).
e
s 00010/00005/00054
d D 5.5 88/06/30 17:21:25 bostic 9 8
c install approved copyright notice
e
s 00011/00005/00048
d D 5.4 88/06/08 13:56:54 bostic 8 7
c written by Ken Arnold; add Berkeley specific header
e
s 00002/00002/00051
d D 5.3 86/01/30 13:43:06 arnold 7 6
c ttytype should have it's sive defined properly
e
s 00001/00001/00052
d D 5.2 85/11/08 17:18:44 bloom 6 5
c make sure fetching the terminal type doesn't clobber anything
e
s 00010/00001/00043
d D 5.1 85/06/07 11:28:03 dist 5 4
c Add copyright
e
s 00001/00001/00043
d D 1.4 85/05/23 15:37:42 bloom 4 3
c Add support for XS
e
s 00014/00005/00030
d D 1.3 85/05/01 16:50:12 bloom 3 2
c new version from arnold
e
s 00003/00003/00032
d D 1.2 83/05/09 20:26:36 arnold 2 1
c add CR to external variable declarations
e
s 00035/00000/00000
d D 1.1 83/03/27 16:12:30 arnold 1 0
c date and time created 83/03/27 16:12:30 by arnold
e
u
U
t
T
I 1
/*
I 5
D 8
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 17
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 17
I 17
D 19
 * Copyright (c) 1981, 1993
E 19
I 19
 * Copyright (c) 1981, 1993, 1994
E 19
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 11
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
E 8
 */

#ifndef lint
D 7
static char sccsid[] = "%W% (Berkeley) %G%";
E 7
I 7
D 8
static char sccsid[] = "@(#)curses.c	5.2 (Berkeley) 11/8/85";
E 7
#endif not lint
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8

D 13
/*
E 5
 * Define global variables
 *
D 5
 * %W% (Berkeley) %G%
E 5
 */
# include	"curses.h"
E 13
I 13
D 19
#include <curses.h>
E 19
I 19
#include "curses.h"
E 19
E 13

D 13
bool	_echoit		= TRUE,	/* set if stty indicates ECHO		*/
	_rawmode	= FALSE,/* set if stty indicates RAW mode	*/
	My_term		= FALSE,/* set if user specifies terminal type	*/
	_endwin		= FALSE;/* set if endwin has been called	*/
E 13
I 13
/* Private. */
int	__echoit = 1;			/* If stty indicates ECHO. */
D 15
int	__endwin = 0;			/* If endwin has been called. */
E 15
int	__pfast;
int	__rawmode = 0;			/* If stty indicates RAW mode. */
I 14
int	__noqch = 0;			/* 
					 * If terminal doesn't have 
					 * insert/delete line capabilities 
					 * for quick change on refresh.
					 */
E 14
E 13
D 16

E 16
I 16
D 18
char	AM, BS, CA, DA, EO, HC, HZ, IN, MI, MS, NC, NS, OS,
	PC, UL, XB, XN, XT, XS, XX;
E 18
I 18
char	AM, BS, CA, DA, EO, HC, IN, MI, MS, NC, NS, OS, PC,
	UL, XB, XN, XT, XS, XX;
E 18
char	*AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL,
	*DM, *DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6,
	*K7, *K8, *K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL,
	*KR, *KS, *KU, *LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF,
	*SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VS,
	*VE, *al, *dl, *sf, *sr,
	*AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM, *LEFT_PARM,
	*RIGHT_PARM;
E 16
D 6
char	ttytype[10],		/* long name of tty			*/
E 6
I 6
D 7
char	ttytype[17],		/* long name of tty			*/
E 7
I 7
D 13
char	ttytype[50],		/* long name of tty			*/
E 7
E 6
	*Def_term	= "unknown";	/* default terminal type	*/

D 10
int	_tty_ch		= 1,	/* file channel which is a tty		*/
E 10
I 10
int	_tty_ch		= 0,	/* file channel which is a tty		*/
E 10
	LINES,			/* number of lines allowed on screen	*/
	COLS,			/* number of columns allowed on screen	*/
	_res_flg;		/* sgtty flags for reseting later	*/

WINDOW	*stdscr		= NULL,
	*curscr		= NULL;

# ifdef DEBUG
FILE	*outf;			/* debug output file			*/
# endif

SGTTY	_tty;			/* tty modes				*/

D 3
bool	AM, BS, CA, DA, DB, EO, GT, HZ, IN, MI, MS, NC, OS, UL, XN,
	NONL, UPPERCASE, normtty, _pfast;
E 3
I 3
bool	AM, BS, CA, DA, DB, EO, HC, HZ, IN, MI, MS, NC, NS, OS, UL, XB, XN,
D 4
	XT, XX;
E 4
I 4
	XT, XS, XX;
E 4
char	*AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL, *DM,
	*DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6, *K7, *K8,
	*K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL, *KR, *KS, *KU,
	*LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF, *SO, *SR, *TA, *TE,
	*TI, *UC, *UE, *UP, *US, *VB, *VS, *VE, *AL_PARM, *DL_PARM,
	*UP_PARM, *DOWN_PARM, *LEFT_PARM, *RIGHT_PARM;
char	PC;
E 3

E 13
D 2
char	*AL, *BC, *BT, *CD, *CE, *CL, *CM, *DC, *DL, *DM, *DO, *ED,
	*EI, *HO, *IC, *IM, *IP, *LL, *MA, *ND, *SE, *SF, *SO, *SR,
	*TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VE, *VS, PC;
E 2
I 2
D 3
char	*AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *DC, *DL, *DM, *DO,
	*ED, *EI, *HO, *IC, *IM, *IP, *LL, *MA, *ND, *NL, *SE, *SF,
	*SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VE, *VS, PC;
E 3
I 3
/*
D 13
 * From the tty modes...
E 13
I 13
 * Public.
 *
 * XXX
 * UPPERCASE isn't used by libcurses, and is left for backward
 * compatibility only.
E 13
 */
I 13
WINDOW	*curscr;			/* Current screen. */
WINDOW	*stdscr;			/* Standard screen. */
int	 COLS;				/* Columns on the screen. */
int	 LINES;				/* Lines on the screen. */
int	 My_term = 0;			/* Use Def_term regardless. */
char	*Def_term = "unknown";		/* Default terminal type. */
char	 GT;				/* Gtty indicates tabs. */
char	 NONL;				/* Term can't hack LF doing a CR. */
char	 UPPERCASE;			/* Terminal is uppercase only. */
E 13
D 18

E 18
D 13
bool	GT, NONL, UPPERCASE, normtty, _pfast;
E 13
I 13
D 16
char	AM, BS, CA, DA, EO, HC, HZ, IN, MI, MS, NC, NS, OS,
	PC, UL, XB, XN, XT, XS, XX;
char	*AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL,
	*DM, *DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6,
	*K7, *K8, *K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL,
	*KR, *KS, *KU, *LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF,
	*SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VS,
D 14
	*VE,
E 14
I 14
	*VE, *al, *dl, *sf, *sr,
E 14
	*AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM, *LEFT_PARM,
	*RIGHT_PARM;
E 16
E 13
E 3
E 2
E 1
