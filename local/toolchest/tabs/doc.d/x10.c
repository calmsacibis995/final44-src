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
	struct field_item *f[7];

	Start_Form ('_', ' ');

	Print_Center (stdwindow, 1, FAREVV, "A Sample Form");

	f[0] = New_Field(9, 30, CMNUM, "_____________________",
			0, "3,-123.55,123.00");
	Set_Attributes (f[0], FARIGHT);
	Set_Label (f[0], "l", "A Token: ",  FANORMAL);


	f[1] = New_Field(9, 30, CMKEY, "_____________________",
			"Enter a sample key.",
"a few key words to choose from for score and seven years ago our fathers");


	f[2] = New_Field(9, 30, CMFILE, "_____________________",
			"Enter a filename key.",
			"5");

	f[3] = New_Field(9, 30, CMENV, "_____________________",
			0, 0);

	f[4] = New_Field(9, 30, CMKEY, "_____________________",
			"This is the list of keys.", "a great big deal");


	f[5] = New_Field(9, 30, CMSTR, "_____________________",
			"Enter a line of characters.", 0);

	f[6] = New_Field(9, 30, CMCFM, "_",
			"Please Press Return when you are ready to proceed.",
			0);

	Link_Fields (f[0], f[1]);
	Link_Fields (f[1], f[2]);
	Link_Fields (f[2], f[3]);
	Link_Fields (f[3], f[4]);
	Link_Fields (f[4], f[5]);
	Link_Fields (f[5], f[6]);

	Set_Error (f[0], "Tokens only please.");

	Show_List (f, 1);

	Get_List (f, 1, FALSE, FALSE);

	End_Form ();
}
