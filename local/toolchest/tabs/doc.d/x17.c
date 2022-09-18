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
 * field types.
 */

main ()
{
	struct field_item *f[3];
	extern int cmalpha ();
	extern int read_alpha ();
	extern int pre_alpha ();
	extern int post_alpha ();

	Start_Form ('_', ' ');

	Print_Center (stdwindow, 1, FANORMAL,
		"Alpha Only Field Example");

/*
 *	Create a normal string field
 *
 */
	f[0] = New_Field (5, 38, CMSTR, "____________________",
		 "Enter the a string of characters.",
			0);
	Set_Label (f[0], "left", "Normal String: ", FANORMAL);
	Set_Tab_Movement (f[0], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (f[0], TRUE);

/*
 *	The application defined alpha only field
 *
 */
	f[1] = New_Field (7, 38, CMSTR, "____________________",
		 "Enter the a string of characters (alpha only please).",
			0);
	Set_Label (f[1], "left", "Alpha-Only: ", FANORMAL);
	Set_Tab_Movement (f[1], TRUE, FALSE, TRUE, FALSE, FALSE);
	Set_Auto_Advance (f[1], TRUE);

/*
 *	Change the type to the application supplied routine
 *
 */
	f[1] -> read_routine = read_alpha;
	f[1] -> type = cmalpha;
	Set_Actions (f[1], pre_alpha, post_alpha);

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

	Get_List (f, 3, FALSE, FALSE);

	End_Form ();
}

/*
 *	cmalpha (field_ptr)
 *
 *	This function matches an arbitrary alpha only string
 */

static int
cmalpha (field_ptr)
register struct field_item     *field_ptr;
{
	char *error;

	error = "Cannot match or complete alpha only field";

	if (!cm_start (field_ptr, error, error)) return;

	if (field_ptr -> cmflg & CMHLP)
	{
		field_ptr -> cmflg |= CMNOP;

		if (field_ptr -> fnflg & FNHLP)
			return;

		prhlp (field_ptr, "Enter a string of alpha only characters.",
			FALSE, FALSE);

		return;
	}

	if (alpha_str (field_ptr -> txbuf))
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

static int
alpha_str (string)
register char *string;
{
	while (*string)
	{
		if (*string < ' ')
			return (FALSE);
		if ((*string >= '0') && (*string <= '9'))
			return (FALSE);
		*string++;
	}

	return (TRUE);
}

static int
read_alpha (field_ptr)
register struct field_item     *field_ptr;
{
	register char  *resp_ptr;
	register char  *txbuf_ptr;
	char    response[FORM_BUF];
	char   *error;
	int     rc;

	error = "Alpha format mismatch - Type  ? for help";

	txbuf_ptr = field_ptr -> txbuf;
	resp_ptr = response;

	while (txbuf_ptr < field_ptr -> txptr)
	{
		*resp_ptr++ = *txbuf_ptr++;
	}
	*resp_ptr = '\0';

	if (alpha_str (response) == FALSE)
		Print_Message (field_ptr -> meswin, FANORMAL, error);

	rc = getachar (field_ptr);

	switch (chartyp[rc & 0377])
	{
		case NORMAL: 
		case PUNC: 
			*resp_ptr++ = rc;
			*resp_ptr = '\0';
			if (alpha_str (response))
			{
				Print_Message (field_ptr -> meswin,
					FANORMAL, "\0");
			}
			else
			{
				beep ();
				Print_Message (field_ptr -> meswin,
					FANORMAL, error);
			}
	}
	return (rc);
}

static int
pre_alpha (f, count, index, rc)
struct field_item **f;
int count;
int index;
int rc;
{
	Def_Char_Action (' ', NORMAL, regchar, 0);
	return (index);
}

static int
post_alpha (f, count, index, rc)
struct field_item **f;
int count;
int index;
int rc;
{
	Def_Char_Action (' ', PUNC, regchar, 0);
	return (index);
}
