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
	extern int beep ();

	int i;
	struct field_item *f[6];

	Start_Form ('_', ' ');

	Def_Interrupt (beep);				/* Beep on Interrupt */
	Def_Editing_Type (OVERLAY);
	Def_Entry_Type (FAR_LEFT);

	errwindow -> _type_scroll = FALSE;	/* MIT scroll the Help */

	Print_Center (stdwindow, 1, FANORMAL, "A Sample Form");

/*
 *	Field 0 - a keyword
 *
 */
	f[0] = New_Field(6, 33, CMKEY, "_____________________",
			"Enter a sample keyword.",
			"a few key words to choose from");

	Set_Label (f[0], "l", "Keyword: ", FANORMAL);

/*
 *	Field 1 - a centered string
 *
 */
	f[1] = New_Field(8, 33, CMSTR, "_____________________",
			"Enter a line of characters.", 0);

	Set_Label (f[1], "l", "String: ", FANORMAL);

	Set_Attributes (f[1], FACENTER);

/*
 *	Field 2 - a file name
 *
 */
	f[2] = New_Field(10, 33, CMFILE, "_____________________",
			"Enter a sample filename.",
			"1");

	Set_Label (f[2], "l", "Filename: ", FANORMAL);

/*
 *	Field 3 - an environmental variable
 *
 */
	f[3] = New_Field(12, 33, CMENV, "_____________________",
			0, 0);

	Set_Label (f[3], "l", "Environ: ", FANORMAL);

/*
 *	Field 4 - a right justified decimal number
 *
 */
	f[4] = New_Field(14, 33, CMNUM, "_____________________",
			0, "3,-123.55,123.00");

	Set_Label (f[4], "l", "Number: ", FANORMAL);

	Set_Attributes (f[4], FARIGHT);

/*
 *	Field 5 - a carriage return
 *
 */
	f[5] = New_Field(16, 33, CMCFM, "_",
			"Please press return when you are ready to proceed.",
			0);

	Set_Label (f[5], "l", "Confirm: ", FANORMAL);


/*
 *	Set the fields so that ^B and ^F (cursor pad and mouse) work
 *		no verify and no "onetime"
 *
 *	Set the fields to auto advance - tab when full
 */
	for (i = 0; i < 6; i++)
	{
		Set_Tab_Movement (f[i], TRUE, FALSE, TRUE, FALSE, FALSE);
		Set_Auto_Advance (f[i], TRUE);
	}

	Show_List (f, 6);

	Get_List (f, 6, FALSE, FALSE);

	Print_Message (stdwindow, FANORMAL, "Bye!");

	End_Form ();
}
