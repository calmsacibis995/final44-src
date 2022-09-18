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

	Start_Form ('_', ' ');

	Def_Interrupt (beep);

	Print_Center (stdwindow, 0, FANORMAL, "A Sample Form");

	i = 0;
	for (x = 0; x < 3; x++)
	{
		for (y = 0; y < 3; y++)
		{
			f[i] = New_Field(9 + x * 2, 21 + y * 20,
				CMKEY,
				"______",
				"Enter a sample key.",
				"a few key words to choose from");

			Set_Label (f[i], "l", "Keyword: ", FAREVV | FAUNDER);

			Set_Auto_Advance (f[i], TRUE);

			Set_Tab_Movement (f[i], TRUE, FALSE, TRUE, FALSE, FALSE);

			i++;
		}
	}

	f[9] = New_Field(19, 30, CMCFM, "_",
			"Please Press Return when you are ready to proceed.",
			0);
	Set_Label (f[9], "l", "Confirm: ", 0);
	Set_Tab_Movement (f[9], TRUE, FALSE, TRUE, FALSE, FALSE);

	Show_List (f, 10);

	Get_List (f, 10, FALSE, FALSE);

	End_Form ();
}
