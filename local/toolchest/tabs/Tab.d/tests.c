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

extern int beep ();

main ()
{
	int i;
	int x;
	int y;
	struct field_item *f[20];
	FILE *out;

	Start_Form ('_', ' ');

/*	Turned off for debugging

	Def_Interrupt (beep);
*/

	Print_Center (stdwindow, 1, FABLINK, "A Sample Form");
	Print_Center (stdwindow, 2, FAREVV, "A Second Centered Heading");
	Print_Form (stdwindow, 3, 15, FANORMAL, "A line to be deleted.");

	f[0] = New_Field(8, 30, CMKEY, "_____________________",
			"Enter a sample key.",
"a few key words to choose from for score and seven years ago our fathers");

	Set_Label (f[0], "l", "Keyword:  ", FAREVV);
	Set_Attributes (f[0], FAUNDER);
	f[0] -> fnflg |= FNHPAGE;


	f[1] = New_Field(10, 30, CMSTR, "_____________________",
			"Enter a line of characters.", 0);

	Set_Label (f[1], "l", "String:   ", FABLINK | FAUNDER);

	Set_Attributes (f[1], FACENTER | FAUNDER | FAREVV);

	Set_Auto_Advance (f[1], TRUE);


	f[2] = New_Field(12, 30, CMFILE, "_____________________",
			"Enter a filename key.",
			"5");

	Set_Label (f[2], "l", "Filename: ", FAHALF | FAREVV);

	Set_Auto_Advance (f[2], TRUE);

	Set_Attributes (f[2], FABLINK);

	f[3] = New_Field(14, 30, CMENV, "_____________________",
			0, 0);

	Set_Attributes (f[3], FAHALF);

	f[6] = New_Field(14, 30, CMKEY, "_____________________",
			"This is the list of keys.", "a great big deal");

	Link_Fields (f[3], f[6]);

	Set_Label (f[3], "l", "Environ:  ", 0);


	f[4] = New_Field(16, 30, CMNUM, "_____________________",
			0, "3,-123.55,123.00");

	Set_Attributes (f[4], FARIGHT| FABOLD | FABLINK | FAREVV | FAHALF | FAUNDER);

	Set_Label (f[4], "l", "Number:   ", 0);

	f[5] = New_Field(18, 30, CMCFM, "_",
			"Please Press Return when you are ready to proceed.",
			0);

	Set_Label (f[5], "l", "Confirm (", FABLINK);
	Set_Label (f[5], "r", ") Confirm", FABLINK | FAHALF | FABOLD);
	Set_Label (f[5], "a", "if (expr)", 0);
	Set_Label (f[5], "b", "(body);", 0);
	Set_Attributes (f[5], FABLINK | FAREVV);


	for (i = 0; i < 6; i++)
		Set_Tab_Movement (f[i], TRUE, FALSE, TRUE, FALSE, FALSE);

	Show_List (f, 6);

	Clear_Form (stdwindow);

	Show_List (f, 6);

	Set_CMP_Default (f[0], "word");

	Show_Default_Field (f[0], "choose");

	Show_Default_Field (f[2], "makefile");

	Show_Default_Field (f[3], "HOME");

	Show_Default_Field (f[4], "  23.8");

	Print_Center (stdwindow, 10, FANORMAL, "");

	Get_Position (stdwindow, &x, &y, "Mark a sample location on the screen.");

	Del_P_Form (stdwindow, 3, 15, "A line to be deleted.");

	for (i = 0; i < 6; i++)
		Set_Help (f[i], f[i] -> fnhlp, FALSE, TRUE, 0);

	Get_List (f, 6, FALSE, FALSE);

	for (i = 0; i < 6; i++)
		Set_Tab_Movement (f[i], TRUE, FALSE, TRUE, FALSE, FALSE);

	Print_Message (stdwindow, FAREVV, "Move the fields!");

	for (i = 0; i < 6; i++)
		Move_Field (f[i], f[i] -> x_pos - 1, f[i] -> y_pos + 2,
					f[i] -> window);

	Print_Message (stdwindow, FABLINK, "Re-enter the fields!");

	Unlink_Fields (f[3], f[6]);

	for (i = 0; i < 6; i++)
		Set_Help (f[i], f[i] -> fnhlp, FALSE, FALSE, 0);

	Get_List (f, 6, FALSE, FALSE);

	out = (FILE *) popen ("mail blewett", "w");
	Dump_Form (stdwindow, out);
	fclose (out);
/*
*/

	Print_Message (stdwindow, FANORMAL, "Delete the fields!");

	for (i = 0; i < 6; i++)
		Del_Field (f[i]);

	out = fopen ("form.out", "w");

	for (i = 0; i < 6; i++)
		Dump_Field (f[i], out);

	fclose (out);

	Print_Message (stdwindow, FANORMAL, "Bye!");

	for (i = 0; i < 6; i++)
		Free_Field (f[i]);

	End_Form ();
}
