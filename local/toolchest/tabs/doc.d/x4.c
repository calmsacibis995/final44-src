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
 *
 * This routine demonstrates the use of pre/post action routines for
 * setting a field up for selection only.  This routines requires a
 * Blit with a mouse.
 *
 * The program also demonstrates how to use the user supplid help
 * routine.
 *
 */

main ()
{
	extern int pre ();
	extern int hlp ();
	struct field_item      *f[5];
	int i;

	Start_Form ('_', ' ');

	Print_Center (stdwindow, 0, FANORMAL, "Selection Systems");

/*
 *	Create field zero as the selection field
 *
 */
	f[0] = New_Field (9, 40, CMKEY, "_____", 0, "one two three four");
	Set_Label (f[0], "l", "Selection: ", FANORMAL);
	Set_Tab_Movement (f[0], FALSE, FALSE, TRUE, FALSE, FALSE);
	Set_Attributes (f[0], FACASE);		/* Nice Touch */
	Set_Help (f[0], "Make a mouse selection then press return to exit.",
			FALSE, TRUE, hlp);
	Set_Actions (f[0], 0, pre);

/*
 *	Create four fields to be used for selection
 *
 */
	for (i = 1; i < 5; i++)
	{
		f[i] = New_Field (5, i * 10 + 20, CMSTR, "_", 0, 0);
		Set_Actions (f[i], pre, 0);
	}

	Set_Label (f[1], "l", "One: ", FANORMAL);
	Set_Label (f[2], "l", "Two: ", FANORMAL);
	Set_Label (f[3], "l", "Three: ", FANORMAL);
	Set_Label (f[4], "l", "Four: ", FANORMAL);

/*
 *	Process the fields
 *
 */
	Show_List (f, 5);

	Get_List (f, 5, FALSE, FALSE);

	End_Form();

	exit (0);
}

/*
 *	Typical pre or post action routine
 *
 *	int
 *	pre (f, count, index, rc)
 *	struct field_item **f;		The list of fields from Get_List()
 *	int count;			The number of fields from Get_List()
 *	int index;			The index of the current field
 *	int rc;				The return code from the last call
 *					to Get_Field()
 *
 *	The return value, an int, is used as the next index for Get_List().
 *	Returning "count" will always cause Get_List() to return.
 *	Returning "index" will allow Get_List() to act as usual.
 *
 */
int
pre (f, count, index, rc)
struct field_item **f;
int count;
int index;
int rc;
{
	static int old_index;

	switch (index)
	{
	case 0:				/* The Selection field - post action */
		if (rc == 0)
			return (count);	/* Will always hit the end of the list */
		else
			return (0);
	case 1:
		Show_Default_Field(f[0], "One");
		break;
	case 2:
		Show_Default_Field(f[0], "Two");
		break;
	case 3:
		Show_Default_Field(f[0], "Three");
		break;
	case 4:
		Show_Default_Field(f[0], "Four");
		break;
	}

	if (old_index)			/* Clear the last selection */
		Show_Field (f[old_index]);
	old_index = index;
	Show_Default_Field (f[index], "X");	/* Mark this selection */

	return (0);			/* Return to the first field */
}

hlp (field_ptr)
struct field_item *field_ptr;
{
	long    Time_loc;		/* Internal Time */
	char   *C_time;
	char sbuf[80];

	Time_loc = (long) time (0);
	C_time = (char *) ctime (&Time_loc);
	C_time[strlen(C_time) - 1] = '\0';

	sprintf (sbuf, "Today's date is: %s", C_time);
	prhlp (field_ptr, sbuf, FALSE, FALSE);
}
