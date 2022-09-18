h00173
s 00002/00002/00929
d D 8.1 93/06/06 16:53:06 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00926
d D 4.5 93/05/11 10:04:36 bostic 35 34
c make tn3270 compile again
e
s 00001/00001/00929
d D 4.4 93/05/11 09:09:18 bostic 34 33
c mv telextrn.h into the sys_curses directory, it's the only place it's used
e
s 00003/00013/00927
d D 4.3 91/04/26 16:01:23 bostic 33 32
c new copyright; att/bsd/shared
e
s 00030/00006/00910
d D 4.2 89/05/30 22:01:42 minshall 32 31
c Fix bug with unformatted screens (sigh).
e
s 00000/00000/00916
d D 4.1 88/12/04 15:12:31 minshall 31 30
c Release 4.1
e
s 00003/00002/00913
d D 3.9 88/11/19 11:53:02 minshall 30 29
c Make sure that fields are indicated with a non-highlighted blank.
e
s 00116/00127/00799
d D 3.8 88/11/18 22:35:06 minshall 29 28
c This is a major simplification of SlowScreen().  This
c fixes a bug where we would leave splotches of reverse video on
c the screen.
e
s 00034/00031/00892
d D 3.7 88/08/28 17:59:40 minshall 28 27
c Lint (and new copyrights).
e
s 00010/00010/00913
d D 3.6 88/05/16 14:44:56 minshall 27 26
c For HighC compiler, don't hide previous definitions of KS and KE.
e
s 00008/00000/00915
d D 3.5 88/05/15 20:45:53 minshall 26 25
c Fix for Ultrix systems with their bad curses.h.
e
s 00006/00000/00909
d D 3.4 88/05/15 12:20:14 minshall 25 24
c Make work with new split telnet.
e
s 00001/00001/00908
d D 3.3 88/03/31 20:16:10 minshall 24 23
c Attempt to fix problem where screen shrinks and we live in
c WhereTermAttributeByte() forever (ie: infinite loop).
e
s 00009/00019/00900
d D 3.2 88/03/28 11:55:30 bostic 23 22
c add Berkeley specific headers
e
s 00000/00000/00919
d D 3.1 87/08/11 10:20:07 minshall 22 21
c New version numbering.
e
s 00002/00002/00917
d D 1.21 87/07/17 10:04:33 minshall 21 20
c Install sccs headers and copyright notices.
e
s 00001/00001/00918
d D 1.20 87/07/15 15:26:28 minshall 20 19
c New directory structure.
e
s 00008/00001/00911
d D 1.19 87/07/15 14:11:42 minshall 19 18
c Make transparent output and input work.
e
s 00001/00001/00911
d D 1.18 87/07/13 10:01:39 minshall 18 17
c For transparent output, get cursor at the right place.
e
s 00000/00003/00912
d D 1.17 87/07/10 09:31:01 minshall 17 16
c Fix bug of clearing terminal screen in wrong place (curses
c takes care of it all).
e
s 00001/00001/00914
d D 1.16 87/06/19 12:52:19 minshall 16 15
c Directory changes.
e
s 00002/00020/00913
d D 1.15 87/06/18 16:26:45 minshall 15 14
c Remove -DSLOWSCREEN (make it an always thing, which it is and
c should be) (yeah!).
e
s 00001/00002/00932
d D 1.14 87/06/12 08:46:47 minshall 14 13
c Get rid of redundant global variable (yeah!).
e
s 00006/00002/00928
d D 1.13 87/06/08 14:37:06 minshall 13 12
c Parentheses everywhere!  Also, fix bug which kept us looping when 
c nothing in [Lowest,Highest] actually needed changing.
e
s 00002/00004/00928
d D 1.12 87/05/28 17:25:59 minshall 12 11
c New header file; translate table in separate .o file.
e
s 00004/00004/00928
d D 1.11 87/05/22 11:19:14 minshall 11 10
c New directory structure (plus cast fix in termout.c).
e
s 00003/00002/00929
d D 1.10 87/05/18 16:06:19 minshall 10 9
c Fixes to make ScreenImage type NOT hardcoded.
e
s 00008/00000/00923
d D 1.9 87/05/15 09:22:33 minshall 9 8
c Add a null ScreenOIA() routine.
e
s 00008/00008/00915
d D 1.8 87/05/12 14:09:54 minshall 8 7
c 1) 'msdos' -> 'MSDOS' 2) remove 'bzero' calls 3) add memset call.
e
s 00004/00000/00919
d D 1.7 87/05/10 14:49:14 minshall 7 6
c Move 'Terminal' to here.
e
s 00017/00000/00902
d D 1.6 87/04/01 16:01:57 minshall 6 5
c Make close/open sequences work in a more rational manner.
e
s 00007/00005/00895
d D 1.5 87/01/11 16:13:31 minshall 5 4
c Fix hang when tn3270 tries to abort because of map3270 problems.
e
s 00010/00024/00890
d D 1.4 86/12/19 17:07:54 minshall 4 3
c Seems to work with 'close' then 'open'.
e
s 00111/00007/00803
d D 1.3 86/11/16 11:04:40 minshall 3 2
c Move tranparent write routines from ../ctlr/outbound.c.
e
s 00005/00004/00805
d D 1.2 86/11/12 17:17:15 minshall 2 1
c This version works with 3278-style inline attribute characters.
e
s 00809/00000/00000
d D 1.1 86/11/12 12:06:19 minshall 1 0
c date and time created 86/11/12 12:06:19 by minshall
e
u
U
t
T
I 1
D 33
/*
D 21
 *	Copyright (c) 1984, 1985, 1986 by the Regents of the
E 21
I 21
D 23
 *	Copyright (c) 1984-1987 by the Regents of the
E 21
 *	University of California and by Gregory Glenn Minshall.
E 23
I 23
 * Copyright (c) 1988 Regents of the University of California.
E 33
I 33
/*-
D 36
 * Copyright (c) 1988 The Regents of the University of California.
E 33
 * All rights reserved.
E 36
I 36
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 36
E 23
 *
D 23
 *	Permission to use, copy, modify, and distribute these
 *	programs and their documentation for any purpose and
 *	without fee is hereby granted, provided that this
 *	copyright and permission appear on all copies and
 *	supporting documentation, the name of the Regents of
 *	the University of California not be used in advertising
 *	or publicity pertaining to distribution of the programs
 *	without specific prior permission, and notice be given in
 *	supporting documentation that copying and distribution is
 *	by permission of the Regents of the University of California
 *	and by Gregory Glenn Minshall.  Neither the Regents of the
 *	University of California nor Gregory Glenn Minshall make
 *	representations about the suitability of this software
 *	for any purpose.  It is provided "as is" without
 *	express or implied warranty.
E 23
I 23
D 33
 * Redistribution and use in source and binary forms are permitted
D 28
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 28
I 28
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
E 33
I 33
 * %sccs.include.redist.c%
E 33
E 28
E 23
 */

#ifndef lint
D 21
static	char	sccsid[] = "@(#)outbound.c	3.1  10/29/86";
E 21
I 21
static char sccsid[] = "%W% (Berkeley) %G%";
E 21
D 23
#endif	/* lint */

E 23
I 23
#endif /* not lint */
E 23

#if defined(unix)
#include <signal.h>
#include <sgtty.h>
#endif
#include <stdio.h>
#include <curses.h>
I 26
#if	defined(ultrix)
/* Some version of this OS has a bad definition for nonl() */
#undef	nl
#undef	nonl

#define nl()	 (_tty.sg_flags |= CRMOD,_pfast = _rawmode,stty(_tty_ch, &_tty))
#define nonl()	 (_tty.sg_flags &= ~CRMOD, _pfast = TRUE, stty(_tty_ch, &_tty))
#endif	/* defined(ultrix) */
E 26

I 7
D 11
#include "../general.h"
E 11
I 11
#include "../general/general.h"
E 11

E 7
#include "terminal.h"

D 28
#include "../telnet.ext"

E 28
I 12
D 16
#include "../ascii/disp_asc.h"
E 16
I 16
D 20
#include "../apilib/disp_asc.h"
E 20
I 20
#include "../api/disp_asc.h"
E 20
E 16

E 12
#include "../ctlr/hostctlr.h"
D 28
#include "../ctlr/inbound.ext"
E 28
I 28
#include "../ctlr/externs.h"
#include "../ctlr/declare.h"
E 28
I 9
#include "../ctlr/oia.h"
E 9
D 28
#include "../ctlr/options.ext"
#include "../ctlr/outbound.ext"
E 28
#include "../ctlr/screen.h"
I 29
#include "../ctlr/scrnctlr.h"
E 29

D 11
#include "../keyboard/map3270.ext"
E 11
I 11
D 28
#include "../ascii/map3270.ext"
E 11

E 28
D 11
#include "../system/globals.h"
E 11
I 11
#include "../general/globals.h"
E 11

D 28
extern void EmptyTerminal();
E 28
I 28
D 34
#include "../telextrn.h"
E 34
I 34
#include "telextrn.h"
E 34
E 28

#define CorrectTerminalCursor() ((TransparentClock == OutputClock)? \
D 18
		terminalCursorAddress:UnLocked? CursorAddress: HighestScreen())
E 18
I 18
		CursorAddress:UnLocked? CursorAddress: HighestScreen())
E 18


D 3
#if	defined(unix)
extern int	tin, tout;		/* file descriptors */
#endif	/* defined(unix) */

E 3
D 4
static int terminalCursorAddress = 0;	/* where the cursor is on term */
static int screenInitd = 0; 		/* the screen has been initialized */
static int screenStopped = 1;		/* the screen has been stopped */
E 4
I 4
static int terminalCursorAddress;	/* where the cursor is on term */
static int screenInitd; 		/* the screen has been initialized */
static int screenStopped;		/* the screen has been stopped */
E 4
D 15
#if	defined(SLOWSCREEN)
E 15
static int max_changes_before_poll;	/* how many characters before looking */
					/* at terminal and net again */
D 15
#endif	/* defined(SLOWSCREEN) */
E 15

D 4
static int needToRing = 0;		/* need to ring terinal bell */
E 4
I 4
static int needToRing;			/* need to ring terinal bell */
E 4
static char *bellSequence = "\07";	/* bell sequence (may be replaced by
					 * VB during initialization)
					 */
D 4
static WINDOW *bellwin;			/* The window the bell message is in */
E 4
I 4
static WINDOW *bellwin = 0;		/* The window the bell message is in */
E 4
int	bellwinup = 0;			/* Are we up with it or not */

#if	defined(unix)
D 27
static char *KS, *KE;
E 27
I 27
static char *myKS, *myKE;
E 27
#endif	/* defined(unix) */

I 3

D 15
#if	defined(SLOWSCREEN)
E 15
static int inHighlightMode = 0;
I 7
ScreenImage Terminal[MAXSCREENSIZE];
E 7
D 15
#endif	/* defined(SLOWSCREEN) */
E 15

/* Variables for transparent mode */
E 3
#if	defined(unix)
static int tcflag = -1;			/* transparent mode command flag */
static int savefd[2];			/* for storing fds during transcom */
I 3
extern int	tin, tout;		/* file descriptors */
E 3
#endif	/* defined(unix) */
D 12

D 3
#if	defined(SLOWSCREEN)
static int inHighlightMode = 0;
#endif	/* defined(SLOWSCREEN) */
E 3

#include "disp_asc.out"

E 12

I 6

/*
 * init_screen()
 *
 * Initialize variables used by screen.
 */

void
init_screen()
{
    bellwinup = 0;
D 15
#if	defined(SLOWSCREEN)
E 15
    inHighlightMode = 0;
I 7
    ClearArray(Terminal);
E 7
D 15
#endif	/* defined(SLOWSCREEN) */
E 15
}


E 6
/* OurExitString - designed to keep us from going through infinite recursion */

static void
D 28
OurExitString(file, string, value)
FILE	*file;
E 28
I 28
OurExitString(string, value)
E 28
char	*string;
int	value;
{
    static int recursion = 0;

    if (!recursion) {
	recursion = 1;
D 28
	ExitString(file, string, value);
E 28
I 28
	ExitString(string, value);
E 28
    }
}


/* DoARefresh */

static void
DoARefresh()
{
    if (ERR == refresh()) {
D 28
	OurExitString(stderr, "ERR from refresh\n", 1);
E 28
I 28
	OurExitString("ERR from refresh\n", 1);
E 28
    }
}

static void
GoAway(from, where)
char *from;		/* routine that gave error */
int	where;		/* cursor address */
{
	char foo[100];

	sprintf(foo, "ERR from %s at %d (%d, %d)\n",
		from, where, ScreenLine(where), ScreenLineOffset(where));
D 28
	OurExitString(stderr, foo, 1);
E 28
I 28
	OurExitString(foo, 1);
E 28
	/* NOTREACHED */
}

D 15
#if	defined(SLOWSCREEN)
E 15
/* What is the screen address of the attribute byte for the terminal */

static int
WhereTermAttrByte(p)
register int	p;
{
    register int i;

    i = p;

    do {
	if (TermIsStartField(i)) {
	    return(i);
	}
	i = ScreenDec(i);
    } while (i != p);

    return(LowestScreen());	/* unformatted screen... */
}
D 15
#endif	/* defined(SLOWSCREEN) */
E 15

/*
 *	There are two algorithms for updating the screen.
 *  The first, SlowScreen() optimizes the line between the
 *  computer and the screen (say a 9600 baud line).  To do
 *  this, we break out of the loop every so often to look
 *  at any pending input from the network (so that successive
 *  screens will only partially print until the final screen,
 *  the one the user possibly wants to see, is displayed
 *  in its entirety).
 *
 *	The second algorithm tries to optimize CPU time (by
 *  being simpler) at the cost of the bandwidth to the
 *  screen.
 *
 *	Of course, curses(3X) gets in here also.
 */


D 15
#if defined(SLOWSCREEN)
E 15
#if	defined(NOT43)
static int
#else	/* defined(NOT43) */
static void
#endif	/* defined(NOT43) */
SlowScreen()
{
I 29
    register int is, shouldbe, isattr, shouldattr;
E 29
    register int pointer;
D 29
    register int c;
    register int fieldattr;
E 29
I 29
    register int fieldattr, termattr;
E 29
    register int columnsleft;

I 32
#define	NORMAL		0		
E 32
D 29
#   define  SetHighlightMode(p) { \
		if (!IsStartField(p) && IsHighlightedAttr(fieldattr)) { \
E 29
I 29
#define	HIGHLIGHT	1		/* Mask bits */
#define	NONDISPLAY	4		/* Mask bits */
I 32
#define	UNDETERMINED	8		/* Mask bits */
E 32

#define	DoAttributes(x) \
	    switch (x&ATTR_DSPD_MASK) { \
	    case ATTR_DSPD_NONDISPLAY: \
		x = NONDISPLAY; \
		break; \
	    case ATTR_DSPD_HIGH: \
		x = HIGHLIGHT; \
		break; \
	    default: \
		x = 0; \
		break; \
	    }

#   define  SetHighlightMode(x) \
	    { \
		if ((x)&HIGHLIGHT) { \
E 29
		    if (!inHighlightMode) { \
D 29
			inHighlightMode = 1; \
E 29
I 29
			inHighlightMode = HIGHLIGHT; \
E 29
			standout(); \
		    } \
		} else { \
		    if (inHighlightMode) { \
			inHighlightMode = 0; \
			standend(); \
		    } \
		} \
	    }

#   define  DoCharacterAt(c,p) { \
D 29
		SetTerminal(p, c); \
E 29
		if (p != HighestScreen()) { \
D 29
		    c = TerminalCharacterAttr(disp_asc[c&0xff], p, \
								fieldattr); \
E 29
I 29
		    c = disp_asc[c&0xff]; \
E 29
		    if (terminalCursorAddress != p) { \
			if (ERR == mvaddch(ScreenLine(p), \
						ScreenLineOffset(p), c)) {\
			    GoAway("mvaddch", p); \
			} \
		    } else { \
			if (ERR == addch(c)) {\
			    GoAway("addch", p); \
			} \
		    } \
		    terminalCursorAddress = ScreenInc(p); \
		} \
	    }


    /* run through screen, printing out non-null lines */

    /* There are two separate reasons for wanting to terminate this
     * loop early.  One is to respond to new input (either from
     * the terminal or from the network [host]).  For this reason,
     * we expect to see 'HaveInput' come true when new input comes in.
     *
     * The second reason is a bit more difficult (for me) to understand.
     * Basically, we don't want to get too far ahead of the characters that
     * appear on the screen.  Ideally, we would type out a few characters,
     * wait until they appeared on the screen, then type out a few more.
     * The reason for this is that the user, on seeing some characters
     * appear on the screen may then start to type something.  We would
     * like to look at what the user types at about the same 'time'
     * (measured by characters being sent to the terminal) that the
     * user types them.  For this reason, what we would like to do
     * is update a bit, then call curses to do a refresh, flush the
     * output to the terminal, then wait until the terminal data
     * has been sent.
     *
     * Note that curses is useful for, among other things, deciding whether
     * or not to send :ce: (clear to end of line), so we should call curses
     * at end of lines (beginning of next lines).
     *
     * The problems here are the following:  If we do lots of write(2)s,
     * we will be doing lots of context switches, thus lots of overhead
     * (which we have already).  Second, if we do a select to wait for
     * the output to drain, we have to contend with the fact that NOW
     * we are scheduled to run, but who knows what the scheduler will
     * decide when the output has caught up.
     */

D 24
    if (Highest == HighestScreen()) {
E 24
I 24
    if (Highest >= HighestScreen()) {	/* Could be > if screen shrunk... */
E 24
	Highest = ScreenDec(Highest);	/* else, while loop will never end */
    }
    if (Lowest < LowestScreen()) {
	Lowest = LowestScreen();	/* could be -1 in some cases with
					 * unformatted screens.
					 */
    }
    if (Highest >= (pointer = Lowest)) {
		/* if there is anything to do, do it.  We won't terminate
		 * the loop until we've gone at least to Highest.
		 */
	while ((pointer <= Highest) && !HaveInput) {

		/* point at the next place of disagreement */
	    pointer += (bunequal(Host+pointer, Terminal+pointer,
			(Highest-pointer+1)*sizeof Host[0])/sizeof Host[0]);

D 29
		/* how many characters to change until the end of the
E 29
I 29
		/*
		 * How many characters to change until the end of the
E 29
		 * current line
		 */
	    columnsleft = NumberColumns - ScreenLineOffset(pointer);
		/*
		 * Make sure we are where we think we are.
		 */
	    move(ScreenLine(pointer), ScreenLineOffset(pointer));

		/* what is the field attribute of the current position */
D 29
	    fieldattr = FieldAttributes(WhereAttrByte(pointer));
E 29
I 29
D 32
	    fieldattr = FieldAttributes(pointer);
	    DoAttributes(fieldattr);
	    termattr = TermAttributes(pointer);
	    DoAttributes(termattr);
E 32
I 32
	    if (FormattedScreen()) {
		fieldattr = FieldAttributes(pointer);
		DoAttributes(fieldattr);
	    } else {
		fieldattr = NORMAL;
	    }
	    if (TerminalFormattedScreen()) {
		termattr = TermAttributes(pointer);
		DoAttributes(termattr);
	    } else {
		termattr = NORMAL;
	    }
E 32
E 29

D 29
	    if ((IsStartField(pointer) != TermIsStartField(pointer)) ||
		    (IsStartField(pointer) &&
			fieldattr != TermAttributes(pointer))) {
E 29
I 29
	    SetHighlightMode(fieldattr);
	    /*
	     * The following will terminate at least when we get back
	     * to the original 'pointer' location (since we force
	     * things to be equal).
	     */
	    for (;;) {
		if (IsStartField(pointer)) {
		    shouldbe = DISP_BLANK;
		    shouldattr = 0;
		    fieldattr = GetHost(pointer);
		    DoAttributes(fieldattr);
		} else {
		    if (fieldattr&NONDISPLAY) {
			shouldbe = DISP_BLANK;
		    } else {
			shouldbe = GetHost(pointer);
		    }
		    shouldattr = fieldattr;
		}
		if (TermIsStartField(pointer)) {
		    is = DISP_BLANK;
		    isattr = 0;
D 32
		    termattr = GetTerminal(pointer);
		    DoAttributes(termattr);
E 32
I 32
		    termattr = UNDETERMINED; /* Need to find out AFTER update */
E 32
		} else {
		    if (termattr&NONDISPLAY) {
			is = DISP_BLANK;
		    } else {
			is = GetTerminal(pointer);
		    }
		    isattr = termattr;
		}
		if ((shouldbe == is) && (shouldattr == isattr)
			&& (GetHost(pointer) == GetTerminal(pointer))
			&& (GetHost(ScreenInc(pointer))
					== GetTerminal(ScreenInc(pointer)))) {
		    break;
		}
E 29

D 29
		int oldterm;
E 29
I 29
		if (shouldattr^inHighlightMode) {
		    SetHighlightMode(shouldattr);
		}
E 29

D 29
		oldterm = TermAttributes(pointer);
E 29
I 29
		DoCharacterAt(shouldbe, pointer);
E 29
		if (IsStartField(pointer)) {
D 29
		    TermNewField(pointer, fieldattr);
		    SetTerminal(pointer, 0);
E 29
I 29
		    TermNewField(pointer, FieldAttributes(pointer));
I 32
		    termattr = GetTerminal(pointer);
		    DoAttributes(termattr);
E 32
E 29
		} else {
D 29
		    TermDeleteField(pointer);
E 29
I 29
		    SetTerminal(pointer, GetHost(pointer));
I 32
		    /*
		     * If this USED to be a start field location,
		     * recompute the terminal attributes.
		     */
		    if (termattr == UNDETERMINED) {
			termattr = WhereTermAttrByte(pointer);
			if ((termattr != 0) || TermIsStartField(0)) {
			    termattr = GetTerminal(termattr);
			    DoAttributes(termattr);
			} else {	/* Unformatted screen */
			    termattr = NORMAL;
			}
		    }
E 32
E 29
		}
D 29
		    /* We always do the first character in a divergent
		     * field, since otherwise the start of a field in
		     * the Host structure may leave a highlighted blank
		     * on the screen, and the start of a field in the
		     * Terminal structure may leave a non-highlighted
		     * something in the middle of a highlighted field
		     * on the screen.
		     */
		SetHighlightMode(pointer);
		c = GetHost(pointer);
		DoCharacterAt(c,pointer);		/* MACRO */
E 29
I 29
		pointer = ScreenInc(pointer);
		if (!(--columnsleft)) {
		    DoARefresh();
		    EmptyTerminal();
		    if (HaveInput) {	/* if input came in, take it */
			int c, j;
E 29

D 29
		if (NotVisuallyCompatibleAttributes
				(pointer, fieldattr, oldterm)) {
		    int j;

		    j = pointer;

		    pointer = ScreenInc(pointer);
		    if (!(--columnsleft)) {
			DoARefresh();
			EmptyTerminal();
			move(ScreenLine(pointer), 0);
			columnsleft = NumberColumns;
		    }
		    SetHighlightMode(pointer);	/* Turn on highlighting */
D 13
		    while (!IsStartField(pointer) &&
				!TermIsStartField(pointer)) {
E 13
I 13
		    while ((!IsStartField(pointer)) &&
				(!TermIsStartField(pointer))) {
E 13
			c = GetHost(pointer);
			DoCharacterAt(c,pointer);	/* MACRO */
			pointer = ScreenInc(pointer);
			if (!(--columnsleft)) {
			    DoARefresh();
			    EmptyTerminal();
			    move(ScreenLine(pointer), 0);
			    columnsleft = NumberColumns;
				/* We don't look at HaveInput here, since
				 * if we leave this loop before the end of
				 * the 3270 field, we could have pointer
				 * higher than Highest.  This would cause
				 * us to end the highest "while" loop,
				 * but we may, in fact, need to go around the
				 * screen once again.
				 */
			}
			/*		The loop needs to be protected
			 *	from the situation where there had been only
			 *	one field on the Terminal, and none on the Host.
			 *	In this case, we have just deleted our last
			 *	field.	Hence, the break.
E 29
I 29
			/*
			 * We need to start a new terminal field
			 * at this location iff the terminal attributes
			 * of this location are not what we have had
			 * them as (ie: we've overwritten the terminal
			 * start field, a the previous field had different
			 * display characteristics).
E 29
			 */
D 29
			if (j == pointer) {
			    break;
			}
		    }
		    if (IsStartField(pointer) && !TermIsStartField(pointer)) {
			    /* Remember what the terminal looked like */
			TermNewField(pointer, oldterm);
E 29
I 29

			isattr = TermAttributes(pointer);
			DoAttributes(isattr);
			if ((!TermIsStartField(pointer)) &&
					(isattr != termattr)) {
E 29
			    /*
D 29
			     * The danger here is that the current position may
			     * be the start of a Host field.  If so, and the
			     * field is highlighted, and our terminal was
			     * highlighted, then we will leave a highlighted
			     * blank at this position.
E 29
I 29
			     * Since we are going to leave a new field
			     * at this terminal position, we
			     * need to make sure that we get an actual
			     * non-highlighted blank on the screen.
E 29
			     */
D 29
			SetHighlightMode(pointer);
			c = GetHost(pointer);
			DoCharacterAt(c,pointer);
		    }
			/* We could be in the situation of needing to exit.
			 * This could happen if the current field wrapped around
			 * the end of the screen.
			 */
		    if (j > pointer) {
I 13
			/*
			 * pointer is guaranteed to be higher than Highest...
			 */
			pointer = Highest+1;	/* We did the highest thing */
E 29
I 29
			    if ((is != DISP_BLANK) || (termattr&HIGHLIGHT)) {
				SetHighlightMode(0);	/* Turn off highlight */
				c = ScreenInc(pointer);
				j = DISP_BLANK;
				DoCharacterAt(j, c);
			    }
			    if (termattr&HIGHLIGHT) {
				termattr = ATTR_DSPD_HIGH;
			    } else if (termattr&NONDISPLAY) {
				termattr = ATTR_DSPD_NONDISPLAY;
			    } else {
				termattr = 0;
			    }
			    TermNewField(pointer, termattr);
			}
E 29
E 13
			break;
		    }
D 29
		} else {
		    c = GetHost(pointer);
			/* We always do the first character in a divergent
			 * field, since otherwise the start of a field in
			 * the Host structure may leave a highlighted blank
			 * on the screen, and the start of a field in the
			 * Terminal structure may leave a non-highlighted
			 * something in the middle of a highlighted field
			 * on the screen.
			 */
		    SetHighlightMode(pointer);
		    DoCharacterAt(c,pointer);
E 29
I 29
		    move(ScreenLine(pointer), 0);
		    columnsleft = NumberColumns;
E 29
		}
D 29
	    } else {
		SetHighlightMode(pointer);
D 2
		/* The following will terminate at least when we get back
E 2
I 2
		/*
		 * The following will terminate at least when we get back
E 2
		 * to the original 'pointer' location (since we force
		 * things to be equal).
		 */
		while (((c = GetHost(pointer)) != GetTerminal(pointer)) &&
			!IsStartField(pointer) && !TermIsStartField(pointer)) {
		    DoCharacterAt(c, pointer);
		    pointer = ScreenInc(pointer);
		    if (!(--columnsleft)) {
			DoARefresh();
			EmptyTerminal();
			if (HaveInput) {	/* if input came in, take it */
			    break;
			}
			move(ScreenLine(pointer), 0);
			columnsleft = NumberColumns;
		    }
		}
	    }
	}
E 29
I 29
	    }	/* end of for (;;) */
	} /* end of while (...) */
E 29
    }
    DoARefresh();
    Lowest = pointer;
    if (Lowest > Highest) {		/* if we finished input... */
	Lowest = HighestScreen()+1;
	Highest = LowestScreen()-1;
	terminalCursorAddress = CorrectTerminalCursor();
	if (ERR == move(ScreenLine(terminalCursorAddress),
			ScreenLineOffset(terminalCursorAddress))) {
	    GoAway("move", terminalCursorAddress);
	}
	DoARefresh();
	if (needToRing) {
	    StringToTerminal(bellSequence);
	    needToRing = 0;
	}
    }
    EmptyTerminal();			/* move data along */
    return;
}
D 15
#endif	/* defined(SLOWSCREEN) */
E 15

#if	defined(NOT43)
static int
#else	/* defined(NOT43) */
static void
#endif	/* defined(NOT43) */
FastScreen()
{
D 8
#if	defined(msdos)
E 8
I 8
#if	defined(MSDOS)
E 8
#define	SaveCorner	0
D 8
#else	/* defined(msdos) */
E 8
I 8
#else	/* defined(MSDOS) */
E 8
#define	SaveCorner	1
D 8
#endif	/* defined(msdos) */
E 8
I 8
#endif	/* defined(MSDOS) */
E 8

#define	DoAttribute(a) 	    if (IsHighlightedAttr(a)) { \
				standout(); \
			    } else { \
				standend(); \
			    } \
			    if (IsNonDisplayAttr(a)) { \
				a = 0; 	/* zero == don't display */ \
			    } \
			    if (!FormattedScreen()) { \
				a = 1;	/* one ==> do display on unformatted */\
			    }
    ScreenImage *p, *upper;
    int fieldattr;		/* spends most of its time == 0 or 1 */

/* OK.  We want to do this a quickly as possible.  So, we assume we
 * only need to go from Lowest to Highest.  However, if we find a
 * field in the middle, we do the whole screen.
 *
 * In particular, we separate out the two cases from the beginning.
 */
    if ((Highest != HighestScreen()) || (Lowest != LowestScreen())) {
	register int columnsleft;

	move(ScreenLine(Lowest), ScreenLineOffset(Lowest));
	p = &Host[Lowest];
D 8
#if	!defined(msdos)
E 8
I 8
#if	!defined(MSDOS)
E 8
	if (Highest == HighestScreen()) {
	    Highest = ScreenDec(Highest);
	}
D 8
#endif	/* !defined(msdos) */
E 8
I 8
#endif	/* !defined(MSDOS) */
E 8
	upper = &Host[Highest];
	fieldattr = FieldAttributes(Lowest);
	DoAttribute(fieldattr);	/* Set standout, non-display status */
	columnsleft = NumberColumns-ScreenLineOffset(p-Host);

	while (p <= upper) {
D 2
	    if (p->field & ATTR_MASK) {	/* New field? */
E 2
I 2
	    if (IsStartFieldPointer(p)) {	/* New field? */
E 2
		Highest = HighestScreen();
		Lowest = LowestScreen();
		FastScreen();		/* Recurse */
		return;
	    } else if (fieldattr) {	/* Should we display? */
D 10
		addch(disp_asc[p->data]);	/* Display translated data */
E 10
I 10
			    /* Display translated data */
D 28
		addch(disp_asc[GetTerminalPointer(p)]);
E 28
I 28
		addch((char)disp_asc[GetTerminalPointer(p)]);
E 28
E 10
	    } else {
		addch(' ');			/* Display a blank */
	    }
			/* If the physical screen is larger than what we
			 * are using, we need to make sure that each line
			 * starts at the beginning of the line.  Otherwise,
			 * we will just string all the lines together.
			 */
	    p++;
	    if (--columnsleft == 0) {
		int i = p-Host;

		move(ScreenLine(i), 0);
		columnsleft = NumberColumns;
	    }
	}
    } else {		/* Going from Lowest to Highest */
	unsigned char tmpbuf[MAXNUMBERCOLUMNS+1];
	ScreenImage *End = &Host[ScreenSize]-1-SaveCorner;
	register unsigned char *tmp = tmpbuf, *tmpend = tmpbuf+NumberColumns;

	*tmpend = 0;		/* terminate from the beginning */
	move(0,0);
	p = Host;
	fieldattr = FieldAttributes(LowestScreen());
	DoAttribute(fieldattr);	/* Set standout, non-display status */

	while (p <= End) {
D 2
	    if (p->field & ATTR_MASK) {	/* New field? */
E 2
I 2
	    if (IsStartFieldPointer(p)) {	/* New field? */
E 2
		if (tmp != tmpbuf) {
		    *tmp++ = 0;			/* close out */
D 28
		    addstr(tmpbuf);
E 28
I 28
		    addstr((char *)tmpbuf);
E 28
		    tmp = tmpbuf;
D 30
		    tmpend = tmpbuf + NumberColumns - ScreenLineOffset(p-Host);
E 30
I 30
		    tmpend = tmpbuf+NumberColumns-ScreenLineOffset(p-Host)-1;
E 30
		}
I 30
		standend();
		addch(' ');
E 30
D 2
		fieldattr = p->field;	/* Get attributes */
E 2
I 2
		fieldattr = FieldAttributesPointer(p);	/* Get attributes */
E 2
		DoAttribute(fieldattr);	/* Set standout, non-display */
D 30
		*tmp++ = ' ';
E 30
	    } else {
		if (fieldattr) {	/* Should we display? */
				/* Display translated data */
D 10
		    *tmp++ = disp_asc[p->data];
E 10
I 10
		    *tmp++ = disp_asc[GetTerminalPointer(p)];
E 10
		} else {
		    *tmp++ = ' ';
		}
	    }
			/* If the physical screen is larger than what we
			 * are using, we need to make sure that each line
			 * starts at the beginning of the line.  Otherwise,
			 * we will just string all the lines together.
			 */
	    p++;
	    if (tmp == tmpend) {
		int i = p-Host;		/* Be sure the "p++" happened first! */

		*tmp++ = 0;
D 28
		addstr(tmpbuf);
E 28
I 28
		addstr((char *)tmpbuf);
E 28
		tmp = tmpbuf;
		move(ScreenLine(i), 0);
		tmpend = tmpbuf + NumberColumns;
	    }
	}
	if (tmp != tmpbuf) {
	    *tmp++ = 0;
D 28
	    addstr(tmpbuf);
E 28
I 28
	    addstr((char *)tmpbuf);
E 28
	    tmp = tmpbuf;
	}
    }
    Lowest = HighestScreen()+1;
    Highest = LowestScreen()-1;
    terminalCursorAddress = CorrectTerminalCursor();
    if (ERR == move(ScreenLine(terminalCursorAddress),
		    ScreenLineOffset(terminalCursorAddress))) {
	GoAway("move", terminalCursorAddress);
    }
    DoARefresh();
    if (needToRing) {
	StringToTerminal(bellSequence);
	needToRing = 0;
    }
    EmptyTerminal();			/* move data along */
    return;
}


/* TryToSend - send data out to user's terminal */

#if	defined(NOT43)
int
#else	/* defined(NOT43) */
void
#endif	/* defined(NOT43) */
	(*TryToSend)() = FastScreen;

I 28
/*ARGSUSED*/
E 28
I 9
void
ScreenOIA(oia)
OIA *oia;
{
}


E 9
D 4
/* StartScreen - called to initialize the screen, etc. */
E 4
I 4
/* InitTerminal - called to initialize the screen, etc. */
E 4

void
D 4
StartScreen()
E 4
I 4
InitTerminal()
E 4
{
#if defined(unix)
    struct sgttyb ourttyb;
    static int speeds[] = { 0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800,
		2400, 4800, 9600 };
#endif
I 28
    extern void InitMapping();
E 28
    
I 4
    InitMapping();		/* Go do mapping file (MAP3270) first */
E 4
    if (!screenInitd) { 	/* not initialized */
#if	defined(unix)
	char KSEbuffer[2050];
	char *lotsofspace = KSEbuffer;
D 35
	extern int abort();
E 35
I 35
	extern void abort();
E 35
	extern char *tgetstr();
#endif	/* defined(unix) */

I 25
	if (initscr() == ERR) {	/* Initialize curses to get line size */
	    ExitString("InitTerminal:  Error initializing curses", 1);
	    /*NOTREACHED*/
	}
	MaxNumberLines = LINES;
	MaxNumberColumns = COLS;
E 25
D 4
	bzero((char *)Host, sizeof Host);

	bzero(Orders, sizeof Orders);
	Orders[ORDER_SF] = Orders[ORDER_SBA] = Orders[ORDER_IC]
		= Orders[ORDER_PT] = Orders[ORDER_RA] = Orders[ORDER_EUA]
		= Orders[ORDER_YALE] = 1;

	DeleteAllFields();
E 4
D 15
#if	defined(SLOWSCREEN)
E 15
D 8
	bzero((char *)Terminal, sizeof Terminal);
E 8
I 8
	ClearArray(Terminal);
E 8
D 15
#endif	/* defined(SLOWSCREEN) */
E 15
D 4
	Lowest = HighestScreen()+1;
	Highest = LowestScreen()-1;
	terminalCursorAddress =
		CursorAddress =
		BufferAddress = SetBufferAddress(0,0);
	UnLocked = 1;
	Initialized = 1;
	OutputClock = 1;
	TransparentClock = -1;
E 4
I 4
	terminalCursorAddress = SetBufferAddress(0,0);
E 4
#if defined(unix)
	signal(SIGHUP, abort);
#endif

	TryToSend = FastScreen;
D 15
#if defined(unix) && defined(SLOWSCREEN)
E 15
I 15
#if defined(unix)
E 15
	ioctl(1, TIOCGETP, (char *) &ourttyb);
	if ((ourttyb.sg_ospeed < 0) || (ourttyb.sg_ospeed > B9600)) {
	    max_changes_before_poll = 1920;
	} else {
	    max_changes_before_poll = speeds[ourttyb.sg_ospeed]/10;
	    if (max_changes_before_poll < 40) {
		max_changes_before_poll = 40;
	    }
	    TryToSend = SlowScreen;
	    HaveInput = 1;		/* get signals going */
	}
D 15
#endif	/* defined(unix) && defined(SLOWSCREEN) */
E 15
I 15
#endif	/* defined(unix) */
E 15
	setcommandmode();
	/*
	 * By now, initscr() (in curses) has been called (from telnet.c),
	 * and the screen has been initialized.
	 */
#if defined(unix)
	nonl();
			/* the problem is that curses catches SIGTSTP to
			 * be nice, but it messes us up.
			 */
	signal(SIGTSTP, SIG_DFL);
D 27
	if ((KS = tgetstr("ks", &lotsofspace)) != 0) {
	    KS = strsave(KS);
	    StringToTerminal(KS);
E 27
I 27
	if ((myKS = tgetstr("ks", &lotsofspace)) != 0) {
	    myKS = strsave(myKS);
	    StringToTerminal(myKS);
E 27
	}
D 27
	if ((KE = tgetstr("ke", &lotsofspace)) != 0) {
	    KE = strsave(KE);
E 27
I 27
	if ((myKE = tgetstr("ke", &lotsofspace)) != 0) {
	    myKE = strsave(myKE);
E 27
	}
	if (tgetstr("md", &lotsofspace) && tgetstr("me", &lotsofspace)) {
	   SO = strsave(tgetstr("md", &lotsofspace));
	   SE = strsave(tgetstr("me", &lotsofspace));
	}
#endif
	DoARefresh();
	setconnmode();
	if (VB && *VB) {
	    bellSequence = VB;		/* use visual bell */
	}
	screenInitd = 1;
	screenStopped = 0;		/* Not stopped */
    }
I 4
D 14
    Initialized = 1;
E 14
E 4
}


/* StopScreen - called when we are going away... */

void
StopScreen(doNewLine)
int doNewLine;
{
    if (screenInitd && !screenStopped) {
	move(NumberLines-1, 1);
	standend();
D 15
#if	defined(SLOWSCREEN)
E 15
	inHighlightMode = 0;
D 15
#endif	/* defined(SLOWSCREEN) */
E 15
	DoARefresh();
	setcommandmode();
	endwin();
	setconnmode();
#if	defined(unix)
D 27
	if (KE) {
	    StringToTerminal(KE);
E 27
I 27
	if (myKE) {
	    StringToTerminal(myKE);
E 27
	}
#endif	/* defined(unix) */
	if (doNewLine) {
	    StringToTerminal("\r\n");
	}
	EmptyTerminal();
	screenStopped = 1;		/* This is stopped */
    }
}


/* RefreshScreen - called to cause the screen to be refreshed */

void
RefreshScreen()
{
    clearok(curscr, TRUE);
    (*TryToSend)();
}


/* ConnectScreen - called to reconnect to the screen */

void
ConnectScreen()
{
    if (screenInitd) {
#if	defined(unix)
D 27
	if (KS) {
	    StringToTerminal(KS);
E 27
I 27
	if (myKS) {
	    StringToTerminal(myKS);
E 27
	}
#endif	/* defined(unix) */
	RefreshScreen();
	(*TryToSend)();
	screenStopped = 0;
    }
}

/* LocalClearScreen() - clear the whole ball of wax, cheaply */

void
LocalClearScreen()
{
I 28
    extern void Clear3270();

E 28
    outputPurge();		/* flush all data to terminal */
    clear();			/* clear in curses */
D 15
#if	defined(SLOWSCREEN)
E 15
D 8
    bzero((char *)Terminal, sizeof Terminal);
E 8
I 8
    ClearArray(Terminal);
E 8
D 15
#endif	/* defined(SLOWSCREEN) */
E 15
    Clear3270();
    Lowest = HighestScreen()+1; /* everything in sync... */
    Highest = LowestScreen()+1;
}


void
BellOff()
{
    if (bellwinup) {
	delwin(bellwin);
	bellwin = 0;
	bellwinup = 0;
D 17
	Lowest = MIN(Lowest, LINES/2);
	Highest = MAX(Highest, (LINES/2)+3);
D 15
#if	defined(SLOWSCREEN)
E 15
D 8
	bzero(Terminal+LINES/2, (sizeof Terminal[0])*(3*COLS));
E 8
I 8
D 11
	memset(Terminal+LINES/2, 0, (sizeof Terminal[0])*(3*COLS));
E 11
I 11
	memset((char *)(Terminal+LINES/2), 0, (sizeof Terminal[0])*(3*COLS));
E 17
E 11
E 8
D 15
#endif	/* defined(SLOWSCREEN) */
E 15
	touchwin(stdscr);
	DoARefresh();
    }
}


void
RingBell(s)
char *s;
{
    needToRing = 1;
    if (s) {
	int len = strlen(s);

	if (len > COLS-2) {
	    len = COLS-2;
	}
	if ((bellwin = newwin(3, len+2, LINES/2, 0)) == NULL) {
D 28
	    OurExitString(stderr, "Error from newwin in RingBell", 1);
E 28
I 28
	    OurExitString("Error from newwin in RingBell", 1);
E 28
	}
	werase(bellwin);
	wstandout(bellwin);
	box(bellwin, '|', '-');
	if (wmove(bellwin, 1, 1) == ERR) {
D 28
	    OurExitString(stderr, "Error from wmove in RingBell", 1);
E 28
I 28
	    OurExitString("Error from wmove in RingBell", 1);
E 28
	}
	while (len--) {
	    if (waddch(bellwin, *s++) == ERR) {
D 28
		OurExitString(stderr, "Error from waddch in RingBell", 1);
E 28
I 28
		OurExitString("Error from waddch in RingBell", 1);
E 28
	    }
	}
	wstandend(bellwin);
	if (wrefresh(bellwin) == ERR) {
D 28
	    OurExitString(stderr, "Error from wrefresh in RingBell", 1);
E 28
I 28
	    OurExitString("Error from wrefresh in RingBell", 1);
E 28
	}
	bellwinup = 1;
    }
}


/* returns a 1 if no more output available (so, go ahead and block),
    or a 0 if there is more output available (so, just poll the other
    sources/destinations, don't block).
 */

int
DoTerminalOutput()
{
	/* called just before a select to conserve IO to terminal */
D 5
    if (Initialized &&
	    ((Lowest <= Highest) || needToRing ||
			(terminalCursorAddress != CorrectTerminalCursor()))) {
E 5
I 5
D 14
    if (!Initialized) {
E 14
I 14
    if (!(screenInitd||screenStopped)) {
E 14
	return 1;		/* No output if not initialized */
    }
    if ((Lowest <= Highest) || needToRing ||
			(terminalCursorAddress != CorrectTerminalCursor())) {
E 5
	(*TryToSend)();
    }
    if (Lowest > Highest) {
D 5
	return(1);		/* no more output now */
E 5
I 5
	return 1;		/* no more output now */
E 5
    } else {
D 5
	return(0);		/* more output for future */
E 5
I 5
	return 0;		/* more output for future */
E 5
    }
}
I 3

/*
 * The following are defined to handle transparent data.
 */

void
TransStop()
{
#if	defined(unix)
    if (tcflag == 0) {
       tcflag = -1;
       (void) signal(SIGCHLD, SIG_DFL);
    } else if (tcflag > 0) {
       setcommandmode();
       (void) close(tin);
       (void) close(tout);
       tin = savefd[0];
       tout = savefd[1];
       setconnmode();
       tcflag = -1;
       (void) signal(SIGCHLD, SIG_DFL);
    }
#endif	/* defined(unix) */
    RefreshScreen();
}

void
D 19
TransOut(buffer, count)
E 19
I 19
TransOut(buffer, count, kind, control)
E 19
unsigned char	*buffer;
int		count;
I 19
int		kind;		/* 0 or 5 */
int		control;	/* To see if we are done */
E 19
{
#if	defined(unix)
    extern char *transcom;
D 28
    int inpipefd[2], outpipefd[2], savemode;
E 28
I 28
    int inpipefd[2], outpipefd[2];
E 28
D 35
    void aborttc();
E 35
I 35
    static void aborttc();
E 35
#endif	/* defined(unix) */

    while (DoTerminalOutput() == 0) {
#if defined(unix)
	HaveInput = 0;
#endif /* defined(unix) */
    }
#if	defined(unix)
    if (transcom && tcflag == -1) {
       while (1) {			  /* go thru once */
	     if (pipe(outpipefd) < 0) {
		break;
	     }
	     if (pipe(inpipefd) < 0) {
		break;
	     }
	     if ((tcflag = fork()) == 0) {
		(void) close(outpipefd[1]);
		(void) close(0);
		if (dup(outpipefd[0]) < 0) {
		   exit(1);
		}
		(void) close(outpipefd[0]);
		(void) close(inpipefd[0]);
		(void) close(1);
		if (dup(inpipefd[1]) < 0) {
		   exit(1);
		}
		(void) close(inpipefd[1]);
		if (execl("/bin/csh", "csh", "-c", transcom, (char *) 0)) {
		    exit(1);
		}
	     }
	     (void) close(inpipefd[1]);
	     (void) close(outpipefd[0]);
	     savefd[0] = tin;
	     savefd[1] = tout;
	     setcommandmode();
	     tin = inpipefd[0];
	     tout = outpipefd[1];
D 28
	     (void) signal(SIGCHLD, aborttc);
E 28
I 28
D 35
	     (void) signal(SIGCHLD, (int (*)())aborttc);
E 35
I 35
	     (void) signal(SIGCHLD, aborttc);
E 35
E 28
	     setconnmode();
	     tcflag = 1;
	     break;
       }
       if (tcflag < 1) {
	  tcflag = 0;
       }
    }
#endif	/* defined(unix) */
D 28
    (void) DataToTerminal(buffer, count);
E 28
I 28
    (void) DataToTerminal((char *)buffer, count);
E 28
I 19
    if (control && (kind == 0)) {		/* Send in AID byte */
	SendToIBM();
    } else {
I 28
	extern void TransInput();

E 28
	TransInput(1, kind);			/* Go get some data */
    }
E 19
}


#if	defined(unix)
static void
D 35
aborttc()
E 35
I 35
aborttc(signo)
	int signo;
E 35
{
D 28
	int savemode;

E 28
	setcommandmode();
	(void) close(tin);
	(void) close(tout);
	tin = savefd[0];
	tout = savefd[1];
	setconnmode();
	tcflag = 0;
}
#endif	/* defined(unix) */
E 3
E 1
