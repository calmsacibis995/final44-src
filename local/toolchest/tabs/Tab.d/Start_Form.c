/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <termio.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	Start_Form (horiz, vertical)
 *
 *	The procedure performs all of the intial setup steps for running
 *	a form.  This must be called prior to all field related activity.
 *
 *	Def_Interrupt (function)
 *
 *	This procedure sets the specified function to catch SIGINT and
 *	SIGQUIT.  If 0 is specified the default actions will be taken.
 *
 *	Stop_Form ()
 *
 *	This procedure should only be used by the signal catching routines.
 *	If Def_Interrupt () has not been used to catch signals this routine will
 *	cause the form to exit.
 *
 *	End_Form ()
 *
 *	This procedure sets the terminal back to cooked mode and resets the
 *	signals SIGQUIT and SIGINT.
 *
 */

static boole _Started;
static int (*_quit) ();
static int (*_intr) ();
static int (*_on_intr) ();
extern int Stop_Form ();

Start_Form (horiz, vertical)
char horiz;
char vertical;
{
	extern struct window   *stdwindow;
	extern struct window   *errwindow;
	extern int      SCRNLIN;
	extern int      SCRWID;
	extern char     chartyp[];
	extern struct termio    nttybuf;

	struct SWindow  Setup;

	if (stdwindow == 0)
	{
		wttystart ();			/* vt init */

		if (JQTYPE)			/* Blit Kludges */
		{
			INSERTC = 0;
			INSERTM = 0;
			OSERTC = 0;
			INSERTP = 0;
			DELC = 0;
		}

/*
 *	Set the global actions to zip
 *
 */
		Glbl_pre_action = 0;
		Glbl_post_action = 0;
		Glbl_Overflow_Action = 0;
/*
 *	Create the break lists for Get_Field - using insert_brk_item
 *	and not Def_Char_Action to speed things up a bit.
 *	These items only have to be entered in the lists because
 *	they are already setup in the chartyp and f_chartyp arrays.
 *
 *	ESCAPE and K_HELP - group UITL_LIST are not on a list they
 *	never have to be disabled.
 *
 *	Control-V - actually a correction character is also on the
 *	UTIL_LIST.
 */
		cm_list = 0;
		cm_list = insert_brk_item (cm_list, K_HOME);
		cm_list = insert_brk_item (cm_list, CTRL(A));
		cm_list = insert_brk_item (cm_list, K_BOTTOM);
		cm_list = insert_brk_item (cm_list, CTRL(Z));
		cm_list = insert_brk_item (cm_list, K_UP);
		cm_list = insert_brk_item (cm_list, CTRL(^));
		cm_list = insert_brk_item (cm_list, K_DOWN);
		cm_list = insert_brk_item (cm_list, CTRL(G));
		cm_list = insert_brk_item (cm_list, K_LEFT);
		cm_list = insert_brk_item (cm_list, CTRL(T));
		cm_list = insert_brk_item (cm_list, K_RIGHT);
		cm_list = insert_brk_item (cm_list, CTRL(Y));
		cm_list = insert_brk_item (cm_list, K_FTAB);
		cm_list = insert_brk_item (cm_list, FTABC);
		cm_list = insert_brk_item (cm_list, K_MOUSE);
		cm_list = insert_brk_item (cm_list, K_MOUSE2);
		btab_list = 0;
		btab_list = insert_brk_item (btab_list, K_BTAB);
		btab_list = insert_brk_item (btab_list, BTABC);
		tab_list = 0;
		tab_list = insert_brk_item (tab_list, K_TAB);
		tab_list = insert_brk_item (tab_list, TABC);
		cfm_list = 0;
		cfm_list = insert_brk_item (cfm_list, K_EOL);
		cfm_list = insert_brk_item (cfm_list, CRET);
		cfm_list = insert_brk_item (cfm_list, NL);
		eof_list = 0;
		Def_Char_Action (nttybuf.c_cc[VEOF], BREAK, brkchar, EOF_LIST);
		eof_list = insert_brk_item (eof_list, K_EOF);
		punc_list = 0;
		punc_list = insert_brk_item (punc_list, SPACE);

		Def_Char_Action (nttybuf.c_cc[VERASE], CORRECT, corchar, 0);
		Def_Char_Action (nttybuf.c_cc[VKILL], CORRECT, corchar, 0);

		Setup.top_x = 0;
		Setup.top_y = 0;
		Setup.lines = SCRNLIN;
		Setup.cols = SCRWID;
		if (JQTYPE)
		{
			Setup.box_h = 0;
			Setup.box_v = 0;
		}
		else
		{
			Setup.box_h = horiz;
			Setup.box_v = vertical;
		}
		Setup.box_attribute = FANORMAL;
		Setup.type_scroll = FALSE;
		Setup.depth = INVISIBLE - 1;

		stdwindow = New_Window (Setup);/* The main form window */

		Setup.top_x = 0;
		Setup.top_y = 0;
		Setup.lines = (stdwindow -> _bot_x - stdwindow -> _top_x) / 3;
		if (Setup.lines > 9)
			Setup.lines = 9;
		Setup.cols = 4 + (stdwindow -> _bot_y - stdwindow -> _top_y) / 2;
		Setup.box_h = '-';
		Setup.box_v = '|';
		Setup.box_attribute = FANORMAL;
		Setup.type_scroll = TRUE;
		Setup.depth = INVISIBLE;

		errwindow = New_Window (Setup);/* The error window */

	}
	else
	{
		uncook ();
	}
	setup_term();

 	while ((int)(_intr = signal (SIGINT, Stop_Form)) == -1)
 		;
 	while ((int)(_quit = signal (SIGQUIT, Stop_Form)) == -1)
 		;

	s_werase (stdwindow);
	Ref_All_Windows ();

	_Started = TRUE;
}

Def_Interrupt (function)
int (*function) ();
{
	_on_intr = function;
}

Stop_Form (sig)
int sig;
{
 	while ((int)signal (SIGINT, Stop_Form) == -1)
 		;
 	while ((int)signal (SIGQUIT, Stop_Form) == -1)
 		;
 	ioctl (0, TCFLSH, 0);

	if (_on_intr == 0)
	{		/* 1024 is to avoid 1 pointer bug under xt */
		if ((_intr) && ((int) _intr > 1024))
			(*_intr) (sig);
		else if ((_quit) && ((int) _quit > 1024))
			(*_quit) (sig);
		else
		{
			End_Form ();
			exit (0);
		}
	}
	else
		(*_on_intr) (sig);
}

End_Form ()
{
	if (_Started)
	{
		mgo (SCRNLIN - 1, 0);
		clrl ();
		cook ();
	 	while ((int)signal (SIGINT, _intr) == -1)
	 		;
	 	while ((int)signal (SIGQUIT, _quit) == -1)
	 		;
	}

	_Started = FALSE;
}
