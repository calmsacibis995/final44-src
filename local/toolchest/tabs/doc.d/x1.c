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
	struct field_item *f[2];

	Start_Form ('_', ' ');

/*
 *	Define Field 0
 *
 */
	f[0] = New_Field(10, 40, CMNUM, "_______",
			0, "3,-123.55,123.00");

	Set_Attributes (f[0], FARIGHT);

	Set_Label (f[0], "l", "A Number:", FANORMAL);
	Set_Label (f[0], "l", "A Number:", FANORMAL);


/*
 *	Define Field 1
 *
 */
	f[1] = New_Field(12, 40, CMCFM, "_",
			"Please Press Return when you are ready to proceed.",
			0);

	Set_Label (f[1], "l", "Confirm:",  FANORMAL);

/*
 *	Process the fields
 *
 */
	Print_Center (stdwindow, 1, FAREVV, "A Sample Form");

	Show_List (f, 2);

 	Get_List (f, 2, FALSE, FALSE);

	End_Form ();
}
