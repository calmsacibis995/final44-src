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
#include <setjmp.h>
#include <termio.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 * This program demonstrates how to change the default definition of the
 * control characters (character directives).  The example demonstrates
 * page up and down in a scrollable region.  TAB is allowed as a normal
 * character.
 *
 * Setting up new BREAK characters is really a modeling process - you have
 * to select a BREAK character that already exists that does most of what
 * you want.  In x8.c we were setting up your ^X as clones of EOF - a very
 * poor choice especially for the example routine, x8.  EOF is an odd one. 
 * We should have modeled the behavior of ^X on the cursor movement keys or
 * perhaps the BACK TAB key.  These keys are controled via
 * Set_Tab_Movement().  Like with EOF Set_Tab_M*() allows you to turn
 * verify on and off for these keys.  Unlike EOF when verify is off they DO
 * NOT clear the field.
 *
 */
main ()
{
	extern struct termio    nttybuf;
	struct field_item      *f[4];
	struct field_item      *fline;
	struct field_item      *fcfcfm;
	struct field_item      *fregion[20];
	struct SWindow  setup_window;
	struct window  *reg_window;
	int i;
	char *ptr;
	char old_eof;
	extern int mybrkchar ();
	extern int myglobal_post ();
	extern int beep ();

	Start_Form ('_', ' ');

	Def_Interrupt (beep);

/*
 *	Change the definition of TAB, ^U, and ^D.
 *	Set TAB as a regular character.
 *	Set ^D as page down - a poor choice of characters, but ...
 *	set ^U as page up.
 *
 *	The procedures mybrkchar and myglobal_post cooperate in producing
 *	the paging action.  mybrkchar sets the user flag for up and back.
 *	The global postaction procedure is invoked after every field.  When
 *	a field with the user flag set occurs, the post action changes the
 *	current field index by a page of fields (4).
 */
	Def_Char_Action (CTRL(I), NORMAL, regchar, 0);
	Def_Char_Action (CTRL(D), BREAK, mybrkchar, CM_LIST);	/* Page Down */
	old_eof = nttybuf.c_cc[VEOF];
	nttybuf.c_cc[VEOF] = 0;		/* ^@ - NULL will act like EOF */
	Def_Char_Action (CTRL(@), BREAK, brkchar, CM_LIST);
	Def_Char_Action (CTRL(U), BREAK, mybrkchar, CM_LIST);	/* Page Up */
	Glbl_post_action = myglobal_post;

	Print_Center (stdwindow, 1, FANORMAL,
			"Media Industries Electronic Mail");

/*
 *	Create the To: line field
 *
 */
	f[0] = New_Field (4, 29, CMSTR, "....................",
			"Enter the list of people to whom you wish to send this  electronic message.  For example \"nowitz wetherel\"",
			0);
	Set_Label (f[0], "l", "To: ", FANORMAL);
	Set_Tab_Movement (f[0], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (f[0], TRUE);

/*
 *	Create the Subject: line field
 *
 */
	f[1] = New_Field (5, 29, CMSTR, "....................",
			"Enter the subject of the message.  For example \"Notes of 8/11\"",
			0);
	Set_Label (f[1], "l", "Subject: ", FANORMAL);
	Set_Tab_Movement (f[1], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (f[1], TRUE);

/*
 *	Create the scrollable region for creating mail the message
 *
 *	REGION: Create the window first
 *
 */
	setup_window.top_x = 9;
	setup_window.top_y = 12;
	setup_window.lines = 6;
	setup_window.cols = 55;
	setup_window.box_h = '-';
	setup_window.box_v = '|';
	setup_window.type_scroll = TRUE;
	setup_window.depth = 6;
	setup_window.box_attribute = FANORMAL;

	reg_window = New_Window (setup_window);

/*
 *	REGION: Create the one line field for the message
 *
 */
	fline = New_Field (0, 5, CMSTR,
		".................................................",
		"Enter a line of text for the message.",
		0);
	Set_Tab_Movement (fline, TRUE, FALSE, TRUE, FALSE, FALSE);
	Set_Auto_Advance (fline, TRUE);

/*
 *	REGION: Link the one line field to allow blank lines
 *		The user may enter a line of text or
 *		hit the tab or return keys.
 *
 */
	fcfcfm = New_Field (0, 5, CMCFM,
		".................................................",
		0, 0);
/*	Link_Fields (fline, fcfcfm);
/*	Set_EOF (fline, TRUE, TRUE);		/* Allow exit by EOF */

/*
 *	REGION: Create the scrollable region and add it to the list
 *		of fields.
 *
 */
	New_Region (reg_window, &fline, 1, 20, fregion, 1);

	f[2] = New_Field (9, 12, CMREGN,
			(char *) fregion, (char *) 20, 0);

	for (i = 0; i < 20; i++)
	{
		ptr = (char *) malloc (8);
		if (ptr == 0)
			break;
		sprintf (ptr, "%2d: ", i + 1);
		Set_Label (fregion[i], "left", ptr, FANORMAL);
	}
/*
 *	Create a confirmation field that will be collected
 *		after the scrollable region
 *
 */
	f[3] = New_Field (17, 29, CMCFM, "_", 0, 0);
	Set_Label (f[3], "l", "Confirm: ", FANORMAL);
	Set_Tab_Movement (f[3], TRUE, TRUE, TRUE, TRUE, FALSE);

/*
 *	Process the form
 *
 */
	Show_List (f, 4);

	Get_List (f, 4, FALSE, FALSE);

	nttybuf.c_cc[VEOF] = old_eof;
	End_Form ();
}

/*
 *	This is a sample BREAK character action routine.
 *	It uses the standard Tab brkchar routine to set the appropriate
 *	flags, etc.  All BREAK routines should return TRUE.
 *
 */
mybrkchar (field_ptr, rc)
register struct field_item *field_ptr;
register char    rc;
{
	switch (rc)
	{
	case CTRL(U):	/* Page Up */
		brkchar (field_ptr, K_HOME);
		field_ptr -> user_mask = CTRL(U);
		break;
	case CTRL(D):	/* Page Down */
		brkchar (field_ptr, K_HOME);
		field_ptr -> user_mask = CTRL(D);
		break;
	default:
		brkchar (field_ptr, rc);
	}

	return (TRUE);
}

/*
 *	This is a sample global post action routine.  This routine
 *	will be invoked after every field.  As with field specified
 *	action routines, the return value (int) is the index of the
 *	next field to be read.  An index of -1 indicates that the
 *	current field should be re-read.
 *
 */
myglobal_post (f, count, index, rc)
register struct field_item     **f;
int     count;
register int index;
int     rc;
{
	register int new_index;

	switch (f[index] -> user_mask)	/* Oh those side effects!!! */
	{
	case CTRL(U):	/* Page Up */
		f[index] -> user_mask = 0;
		new_index = index - 4;
		if (new_index < 0)
			new_index = 0;
		if (new_index == index)	/* -1 index means repeat this field */
			new_index = -1;
		return (new_index);
	case CTRL(D):	/* Page Down */
		f[index] -> user_mask = 0;
		new_index = index + 4;
		if (new_index >= count)
			new_index = count - 1;
		if (new_index == index)
			new_index = -1;
		return (new_index);
	}
	return (index);
}
