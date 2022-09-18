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

/*
 *	A keyword type that uses a predefined list of keys and associated
 *	values.  The field_item.fndfv contains the kval of the matched
 *	keyword.  This is usefull for switching on the keyword.
 *
 *	Keywords must be in sorted order.
 */

main ()
{
	extern int beep ();
	extern int move_on ();

	struct field_item *f[3];
	struct keys keywords[100];

	Start_Form ('_', ' ');

	Def_Interrupt (beep);				/* Beep on Interrupt */

	Print_Center (stdwindow, 1, FANORMAL, "A Sample Form");

/*
 *	Field 0 - a keyword
 *
 */
	f[0] = New_Field(6, 33, CMKEY_LIST, "_____________________",
			"Enter a sample keyword.",
			keywords);

	keywords[0].kstr = "ex";
	keywords[0].kval = 3;
	keywords[1].kstr = "examine";
	keywords[1].kval = 0;
	keywords[2].kstr = "load";
	keywords[2].kval = 2;
	keywords[3].kstr = "vi";
	keywords[3].kval = 3;
	keywords[4].kstr = "and";
	keywords[4].kval = 4;
	keywords[5].kstr = "some";
	keywords[5].kval = 5;
	keywords[6].kstr = 0;

	Set_Label (f[0], "l", "Keyword: ",  FANORMAL);

/*
 *	Field 1 - a carriage return
 *
 */
	f[1] = New_Field(9, 33, CMCFM, "_",
			"Please press return when you are ready to proceed.",
			0);

	Set_Label (f[1], "l", "Confirm: ",  FANORMAL);

	Set_Actions (f[1], 0, move_on);


/*
 *	Field 2 - test default value for CMKEY_LIST fields
 *
 */
	f[2] = New_Field(12, 33, CMKEY_LIST, "_____________________",
			"Enter a sample keyword.",
			keywords);

	Set_Label (f[2], "l", "Keyword: ",  FANORMAL);

	Show_List (f, 3);

	Show_Default_Field (f[2], "some");

	Get_List (f, 3, FALSE, FALSE);

	Print_Message (stdwindow, FABLINK, "Field 0 chosen was %d", f[0] -> fndfv);

	sleep (2);

	Print_Message (stdwindow, FABLINK, "Field chosen 2 was %d", f[2] -> fndfv);

	sleep (2);

	End_Form ();
}

move_on (f, count, index, rc)
register struct field_item **f;
register int    count;
register int    index;
int     rc;
{
	return (count);
}
