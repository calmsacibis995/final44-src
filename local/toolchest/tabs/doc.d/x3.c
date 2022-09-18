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

#ifdef HACK_STACK

check_stack (f, count, index, rc)
struct field_item **f;
int index;
int rc;
{
	extern struct arg_stack *GL_Arg_Stack;
	struct arg_stack *cur_list;
	int x;

	cur_list = GL_Arg_Stack;
	x = 0;
	while (cur_list)
	{
		Print_Message (stdwindow, FANORMAL, "%d %d %d %d",
			x,
			cur_list -> count,
			*(cur_list -> ptr_index),
			*(cur_list -> ptr_rc));
		cur_list = cur_list -> previous;
		x++;
		sleep (3);
	}
	return (index);
}

#endif HACK_STACK

main ()
{
	struct field_item      *f[4];
	struct field_item      *fline;
	struct field_item      *fcfcfm;
	struct field_item      *fregion[20];
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
	fline = New_Field (0, 0, CMSTR,
		"_________________________________________________",
		"Enter a line of text for the message.",
		0);
	Set_Tab_Movement (fline, TRUE, FALSE, TRUE, FALSE, FALSE);
	Set_Auto_Advance (fline, TRUE);
#ifdef HACK_STACK
	Set_Actions (fline, 0, check_stack);
#endif HACK_STACK

/*
 *	REGION: Link the one line field to allow blank lines
 *		The user may enter a line of text or
 *		hit the tab or return keys.
 *
 */
	fcfcfm = New_Field (0, 0, CMCFM,
		"_________________________________________________",
		0, 0);
	Link_Fields (fline, fcfcfm);
	Set_EOF (fline, TRUE, TRUE);		/* Allow exit by EOF */

/*
 *	REGION: Create the scrollable region and add it to the list
 *		of fields.
 *
 */
	New_Region (reg_window, &fline, 1, 20, fregion, 1);

	f[2] = New_Field (9, 12, CMREGN,
			(char *) fregion, (char *) 20, 0);

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

	Print_Message (stdwindow, FAREVV, "Printing the form and stdwindow");
	Print_stdwindow ();
	Send_stdwindow ();

	End_Form ();
}

Print_stdwindow ()
{
	FILE *fp;

	fp = fopen ("out_file", "w");

	fprintf (fp, "Standard window\n");

	Dump_Form (stdwindow, fp);

	fprintf (fp, "\n\nThe Screen\n");

	SCRN_Dump (fp);

	fclose (fp);
}

Send_stdwindow ()
{
	FILE *fp;

	/* Send the window contents to the lp */
	fp = popen ("lp > /dev/null", "w");

	fprintf (fp, "Standard window\n");

	Dump_Form (stdwindow, fp);

	fprintf (fp, "\n\nThe Screen\n");

	SCRN_Dump (fp);

	pclose (fp);
}
