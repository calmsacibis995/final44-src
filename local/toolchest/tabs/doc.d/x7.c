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
 * This program demonstrates the use of application defined 
 * field types.  The field created with this example is a
 * regular expression field.
 */

main ()
{
	struct field_item *f[3];
	extern int cmregex ();
	extern int change_help ();

	Start_Form ('_', ' ');

	Print_Center (stdwindow, 1, FANORMAL,
		"Regular Expression Matching Example");

/*
 *	Create the string field to collect the regular expression
 *
 */
	f[0] = New_Field (5, 38, CMSTR, "____________________",
		 "Enter the regular expression for the next field - (e.g. \"^[a-c][0-9]{1,3}$\").",
			0);
	Set_Label (f[0], "left", "Expression: ", FANORMAL);
	Set_Tab_Movement (f[0], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (f[0], TRUE);

/*
 *	The application defined regular expression field
 *
 */
	f[1] = New_Field (7, 38, CMSTR, "____________________",
			0,
			0);
	Set_Label (f[1], "left", "Matching Pattern: ", FANORMAL);
	Set_Tab_Movement (f[1], TRUE, FALSE, TRUE, FALSE, FALSE);
	Set_Auto_Advance (f[1], TRUE);
	Set_Actions (f[1], change_help, 0);

/*
 *	Change the type to the application supplied routine
 *
 */
	f[1] -> type = cmregex;
/*
 *	Set the keyword list used by cmregex to the compiled regular
 *	expression.  The pre_action routine will in this program
 *	re-compile the expression with each pass.  The following
 *	line (or one with a different expression) would be used
 *	in an example where the regular expression did not change.
 *
 */
	f[1] -> keywords = (char *) regcmp ("^[a-c][0-9]{1,3}$", 0);

/*
 *	Create a confirmation field that will be collected last
 *
 */
	f[2] = New_Field (9, 38, CMCFM, "_", 0, 0);
	Set_Label (f[2], "left", "Confirm: ", FANORMAL);
	Set_Tab_Movement (f[2], TRUE, TRUE, TRUE, TRUE, FALSE);

/*
 *	Process the form
 *
 */
	Show_List (f, 3);

	Show_Default_Field (f[0], "^[a-c][0-9]{1,3}$");

	Get_List (f, 3, FALSE, FALSE);

	End_Form ();
}

/*
 *	cmregex (field_ptr)
 *
 *	This function matches an arbitrary string with
 *	a regular expression.
 */

cmregex (field_ptr)
register struct field_item     *field_ptr;
{
	extern char *__loc1;
	extern char *regex ();
	char *rc;
	char *error;

	error = "Cannot match or complete the expression";

	if (!cm_start (field_ptr, error, error)) return;

	if (field_ptr -> cmflg & CMHLP)
	{
		field_ptr -> cmflg |= CMNOP;

		if (field_ptr -> fnflg & FNHLP)
			return;

		prhlp (field_ptr, "Enter pattern to be matched.",
			FALSE, FALSE);

		return;
	}

	rc = regex (field_ptr -> keywords, field_ptr -> txbuf);
	if ((rc != NULL) && (__loc1 == field_ptr -> txbuf))
	{
		if (field_ptr -> cmflg & CMCMP)
		{
			complete (field_ptr, field_ptr -> txbuf);
			field_ptr -> cmflg |= CMREP;
		}
		return;
	}

	error_fields = error;
	field_ptr -> cmflg |= CMNOP;
	return;
}

/*
 * Pre-action routine for the regular expression routine.  This is
 * added fluff that could be handled more directly in cmregex (), but
 * gives us a little experience with Set_Help () and action routines.
 *
 */
change_help (f, count, index, rc)
struct field_item     **f;
int     count;
int     index;
int     rc;
{
	static char help_buf[128];
	char *ptr;

	ptr = (char *) regcmp (f[0] -> txbuf, 0);

	if (ptr == NULL)
	{
		beep ();
		Print_Message (f[1] -> meswin, FANORMAL,
			"The regular expression does not compile.");
		return (count);	/* Exit from the list */
	}

	if (f[1] -> keywords)
		free (f[1] -> keywords);

	f[1] -> keywords = ptr;

	sprintf (help_buf,
		"Enter a string that will match the pattern \"%s\".",
		f[0] -> txbuf);

	Set_Help (f[1], help_buf, FALSE, FALSE, 0);

	return (index);
}
