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
#include "vt.h"
#include "windows.h"
#include "fields.h"

main ()
{
	struct field_item      *f[4];
	struct field_item      *fline[3];
	struct field_item      *fcfcfm;
	struct field_item      *fregion[60];
	struct SWindow  setup_window;
	struct window  *reg_window;

	Start_Form ('_', ' ');

	Print_Center (stdwindow, 1, FANORMAL,
			"Media Industries Electronic Mail");

/*
 *	Create the To: line field
 *
 */
	f[0] = New_Field (4, 29, CMSTR, "____________________",
			"Enter the list of people to whom you wish to send this  electronic message.  For example \"nowitz wetherel\"",
			0);
	Set_Label (f[0], "l", "To: ", FANORMAL);
	Set_Tab_Movement (f[0], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (f[0], TRUE);

/*
 *	Create the Subject: line field
 *
 */
	f[1] = New_Field (5, 29, CMSTR, "____________________",
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
	setup_window.cols = 50;
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
	fline[0] = New_Field (0, 4, CMSTR,
		"_____________________________________________",
		"Enter a line of text for the message.",
		0);
	Set_Tab_Movement (fline[0], TRUE, FALSE, TRUE, FALSE, FALSE);
	Set_Auto_Advance (fline[0], TRUE);
	Set_Label (fline[0], "left", "a: ", FANORMAL);

	fline[1] = New_Field (1, 4, CMSTR,
		"_________",
		"Enter a line of text for the message.",
		0);
	Set_Tab_Movement (fline[1], TRUE, FALSE, TRUE, FALSE, FALSE);
	Set_Auto_Advance (fline[1], TRUE);
	Set_Label (fline[1], "left", "b: ", FANORMAL);

	fline[2] = New_Field (1, 22, CMSTR,
		"__________",
		"Enter a line of text for the message.",
		0);
	Set_Tab_Movement (fline[2], TRUE, FALSE, TRUE, FALSE, FALSE);
	Set_Auto_Advance (fline[2], TRUE);
	Set_Label (fline[2], "left", "c: ", FANORMAL);

/*
 *	REGION: Link the one line field to allow blank lines
 *		The user may enter a line of text or
 *		hit the tab or return keys.
 *
 */
	fcfcfm = New_Field (0, 0, CMCFM,
		"_________________________________________________",
		0, 0);
	Link_Fields (fline[0], fcfcfm);
	Link_Fields (fline[1], fcfcfm);
	Link_Fields (fline[2], fcfcfm);

	Set_EOF (fline[0], TRUE, TRUE);		/* Allow exit by EOF */
	Set_EOF (fline[1], TRUE, TRUE);		/* Allow exit by EOF */
	Set_EOF (fline[2], TRUE, TRUE);		/* Allow exit by EOF */

/*
 *	REGION: Create the scrollable region and add it to the list
 *		of fields.
 *
 */
	New_Region (reg_window, fline, 3, 20, fregion, 3);

	f[2] = New_Field (9, 12, CMREGN,
			(char *) fregion, (char *) 60, 0);

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

	End_Form ();
}
