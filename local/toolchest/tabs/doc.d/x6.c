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
#include <signal.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	x6 - a forms style interface to some plotting routines.
 *
 *	This routine thinks it is being run in a Blit style environment.
 *	Each plotting routine is running in a separate layer.
 *
 */

#define LABEL		0
#define XVALUE		1
#define YVALUE		2
#define EXPLODE		3
#define PLOT_COUNT	8

int     pid[PLOT_COUNT];			/* Plot Process PID's */
int	windows;				/* Number of Plot Layers */

#define ALARM1		10
#define ALARM2		5

struct field_item      **fglob;
int    fglob_count;

main ()
{
	extern int beep ();
	struct field_item      *f[100];
	int     field_count;

/*
 *	Initialize the form and protect from interrupts
 *
 */
	Start_Form (0, 0);
	Def_Interrupt (beep);				/* Beep on Interrupt */

/*
 *	Construct the field list
 *
 */
	field_count = make_fields (f);
	fglob = f;
	fglob_count = field_count;

/*
 *	Process the form
 *
 */
	Print_Center (stdwindow, 1, FAREVV | FAUNDER,
		"- Media Industries Sample Graphics -");

	Show_List (f, field_count);

	Print_Form (stdwindow, f[field_count - 7] -> x_pos + 2,
				f[field_count - 7] -> y_pos - 8,
				FANORMAL,
				"Totals:");

	Get_List (f, field_count, FALSE, FALSE);

	clean_up ();

	End_Form ();

	exit (0);
}

/*
 *	write_file
 *
 *	This is the postaction routine attached to the confirmation
 *	field.  This routine looks for the "Exit" and confirmation
 *	returns.  On confirmation (tab or c/r) a plot file is created
 *	and the correct plotting program is signaled.
 *
 */

write_file (f, count, index, rc)
register struct field_item     **f;
int     count;
int     index;
int     rc;
{
	register int     i;
	int     which;
	int     plot_var;
	int     explode;
	int     angle = 0;
	int     density = 0;
	float	x;
	char    sbuf[BUFSIZ];
	FILE * fp;

	alarm (0);

/*
 *	Ignore all movement requests and "Exit" entries
 *
 */
	if (rc != 0)
		return (index);

	if (strcmp (f[index] -> txbuf, "Exit") == 0)
		return (index);

/*
 *	Which window are we to signal?  Make sure that all selection
 *	fields have values.
 *
 */
	sscanf (f[index - 3] -> txbuf, "%d", &which);
	if ((which < 1) || (which > PLOT_COUNT))
	{
		which = 1;
		Show_Default_Field (f[index - 3], "1");
	}
	which--;

	if (*(f[index - 2] -> txbuf) == '\0')
	{
		Show_Default_Field (f[index - 2], "Pie");
	}

	if (*(f[index - 1] -> txbuf) == '\0')
	{
		Show_Default_Field (f[index - 1], "X");
	}

/*
 *	Open the plot file - one per process
 *
 */
	sprintf (sbuf, "%s/.graph%d", (char *) getenv ("HOME"), which);
	if ((fp = fopen (sbuf, "w")) == NULL)
	{
		beep ();
		Print_Message (stdwindow, FANORMAL, "Cannot open communication file %s",
				sbuf);
		return (0);
	}

/*
 *	Select the plot type
 *
 */
	if (strcmp (f[index - 2] -> txbuf, "Hist.") == 0)/* Histogram */
	{
		if (*(f[index - 1] -> txbuf) == 'X')
			plot_var = XVALUE;
		else
			plot_var = YVALUE;

		fprintf (fp, "histogram\n");
		for (i = 1; i < (count - 3); i = i + 4)
		{
			if (*(f[i + plot_var] -> txbuf))
				Dump_Field (f[i + plot_var], fp);
		}
	}

	if (strcmp (f[index - 2] -> txbuf, "Point") == 0)/* Point Plot */
	{
		fprintf (fp, "Point plot\n");
		for (i = 1; i < (count - 3); i = i + 4)
		{
			if ((*(f[i + XVALUE] -> txbuf)) &&
					(*(f[i + YVALUE] -> txbuf)))
			{
				fprintf (fp, "%s %s\n",
						f[i + XVALUE] -> txbuf,
						f[i + YVALUE] -> txbuf);
			}
		}
	}

	if (strcmp (f[index - 2] -> txbuf, "Pie") == 0)/* Pie Chart */
	{
		if (*(f[index - 1] -> txbuf) == 'X')
			plot_var = XVALUE;
		else
			plot_var = YVALUE;

		fprintf (fp, "pie chart\n");
		for (i = 1; i < (count - 3); i = i + 4)
		{
			if (*(f[i + plot_var] -> txbuf))
			{
				if (strcmp (f[i + EXPLODE] -> txbuf, "Yes") == 0)
					explode = 1;
				else
					explode = 0;
				angle += 115;
				sscanf (f[i + plot_var] -> txbuf, "%f", &x);
				x += 10.0;
				density = x / 110.0 * 18;
				fprintf (fp, "%s %d %d %d 0 %s\n",
						f[i + plot_var] -> txbuf,
						explode, angle, density,
						f[i + LABEL] -> txbuf);
			}
		}
	}

/*
 *	Close the file and signal the process
 *
 */
	fclose (fp);

	if (pid[which])
		kill (pid[which], 16);

/*
 *	Execute field zero next
 *
 */
	f[0] -> user_mask = TRUE;
	return (0);
}

/*
 *	make_fields
 *
 *	Routine to construct all of the fields required for the form.
 *	Mainly to "modularize".
 *
 */

make_fields (f)
register struct field_item     **f;
{
	extern int      check_rand ();
	extern int      set1_alarm ();
	extern int      set2_alarm ();
	extern int      calc_update ();
	extern int      write_file ();
	static struct field_item       *fcfm;
	static struct field_item       *fcfm2;
	static struct field_item       *fcfm3;
	static struct field_item       *fs[4];
	static char     ptr[20];
	FILE * fp;
	char    sbuf[BUFSIZ];
	int     x;
	int     y;
	register int     i;
	register int     field_count;

/*
 *	Find out how many windows are running
 *
 */
	for (i = 0; i < PLOT_COUNT; i++)
		pid[i] = 0;

	for (windows = 0; windows < PLOT_COUNT; windows++)
	{
		sprintf (sbuf, "%s/.graph%d", getenv ("HOME"), windows);
		if ((fp = fopen (sbuf, "r")) == NULL)
			break;
		fscanf (fp, "%d", &pid[windows]);
		fclose (fp);
	}

/*
 *	Form width and height
 *
 */
	x = stdwindow -> _bot_x - stdwindow -> _top_x;
	y = stdwindow -> _bot_y - stdwindow -> _top_y;

/*
 *	Create a confirmation field that can be linked with all other
 *	fields - for blank or empty fields
 *
 */
	fcfm = New_Field (0, 0, CMCFM, "_",
			"Leave the field empty.  Empty fields are ignored.",
			0);

/*
 *	Create the fields - centered within the form
 *
 *	Label field
 *
 */
	i = 1 + 12 + 4 + 7 + 4 + 7 + 4 + 3;/* Total Field Width */
	i = y / 2 - i / 2;

	fs[0] = New_Field (5, i, CMSTR, "            ",
			"Enter a label.  This label will be used on the graphs to identify this row of numbers.",
			0);
	Set_Attributes (fs[0], FAUNDER);
	Link_Fields (fs[0], fcfm);

/*
 *	X
 *
 */
	i = i + 12 + 4;
	fs[1] = New_Field (5, i, CMNUM, "      ",
			"Enter X value to be graphed.",
			"3,-10.00,100.00");
	Link_Fields (fs[1], fcfm);
	Set_Attributes (fs[1], FARIGHT | FAUNDER);
	Set_Actions (fs[1], 0, calc_update);

/*
 *	Y
 *
 */
	i = i + 7 + 4;
	fs[2] = New_Field (5, i, CMNUM, "      ",
			"Enter Y value to be graphed.",
			"3,-10.00,100.00");
	Link_Fields (fs[2], fcfm);
	Set_Attributes (fs[2], FARIGHT | FAUNDER);
	Set_Actions (fs[2], 0, calc_update);

/*
 *	Explode
 *
 */
	i = i + 7 + 4;
	fs[3] = New_Field (5, i, CMKEY, "   ",
			"When these numbers are used for pie charts, do you want this segment exploded?  Enter yes for exploded pie segments.  Enter no for continuous circle style pie charts.",
			"Yes No");
	Set_Attributes (fs[3], FACASE | FAUNDER);
	Link_Fields (fs[3], fcfm);

	f[0] = New_Field (3, 16, CMKEY, "    ",
			"Enter \"yes\" to have new data generated.  The assumed default is yes.",
			"Yes No");
	Set_Attributes (f[0], FACASE | FAUNDER);
	fcfm3 = New_Field (0, 0, CMCFM, "_", 0, 0);
	Set_Help (fcfm3, 0, FALSE, TRUE, 0);
	Link_Fields (f[0], fcfm3);
	Set_Label (f[0], "left", "Generate Data: ", FANORMAL);
	f[0] -> user_mask = TRUE;
	Set_Actions (f[0], set1_alarm, check_rand);

/*
 *	Use New_Region to duplcate the fields "i" times to fit the form.
 *	"i" is the number of lines of input fields to be created.
 *
 */
	i = x - 5 - 4;
	i /= 2;
	if (i < 0)
		i = 1;
	New_Region (stdwindow, fs, 4, i, &f[1], 2);
	field_count = i * 4 + 1;

	Set_Label (f[1], "above", "Label", FANORMAL);
	Set_Label (f[2], "above", "X Value", FANORMAL);
	Set_Label (f[3], "above", "Y Value", FANORMAL);
	Set_Label (f[4], "above", "Explode", FANORMAL);

/*
 *	Create the window selection field.
 *
 */
	sprintf (sbuf, "0,1,%d", windows);
	strcpy (ptr, sbuf);
	f[field_count] = New_Field (x - 2, 16, CMNUM, "  ",
			"Enter the window number in which you want the plot executed.",
			ptr);
	Set_Label (f[field_count], "left", "Window Number: ", FANORMAL);
	Set_Attributes (f[field_count], FARIGHT | FAUNDER);
	Link_Fields (f[field_count], fcfm);
	field_count++;

/*
 *	Create the plot type selection field.
 *
 */
	f[field_count] = New_Field (x - 2, y / 3 + 8, CMKEY, "      ",
			"Enter the type of plot you want to run on the numbers from above.  \"pie\" for pie charts, \"point\" for point plots, and \"hist.\" for histrograms.",
			"Pie Point Hist.");
	Set_Attributes (f[field_count], FACASE | FAUNDER);
	Set_Label (f[field_count], "left", "Plot Type: ", FANORMAL);
	Link_Fields (f[field_count], fcfm);
	field_count++;

/*
 *	Create the "variable X or Y" selection field.
 *
 */
	f[field_count] = New_Field (x - 2, y * 2 / 3 + 5, CMKEY, "  ",
			"Enter the name of the variable, x or y, you want plotted.  This is the variable that will be used for constructing pie charts and histograms.",
			"X Y");
	Set_Attributes (f[field_count], FACASE | FAUNDER);
	Set_Label (f[field_count], "left", "Plot X or Y: ", FANORMAL);
	Link_Fields (f[field_count], fcfm);
	field_count++;

/*
 *	Create a confirmation field that will be collected last
 *
 */
	f[field_count] = New_Field (x - 2, y - 6, CMKEY, "     ",
			"Enter \"exit\" when you are ready to exit this program.",
			"Exit");
	fcfm3 = New_Field (0, 0, CMCFM, "_",
			"Press the return key to have the plot performed.",
			0);
	Set_Attributes (f[field_count], FACASE | FAUNDER);
	Set_Label (f[field_count], "l", "Confirm: ", FANORMAL);
	Set_Actions (f[field_count], set2_alarm, write_file);
	Link_Fields (f[field_count], fcfm3);
	field_count++;

/*
 *	Set all of the fields to be verified on exit.  All fields may
 *	be exited with function keys, mouse, etc.
 *	All of the fields will auto tab when they are complete.
 *
 */
	for (i = 0; i < field_count; i++)
	{
		Set_Tab_Movement (f[i], TRUE, TRUE, TRUE, TRUE, FALSE);
		Set_Auto_Advance (f[i], TRUE);
	}

	return (field_count);
}


/*
 *	Cleanup the files and the processes
 *
 */

clean_up ()
{
	register char    sbuf[BUFSIZ];
	register int     i;

	for (i = 0; i < PLOT_COUNT; i++)
	{
		if (pid[i])
			kill (pid[i], 9);
		sprintf (sbuf, "%s/.graph%d", getenv ("HOME"), i);
		unlink (sbuf);
	}
}

do_rand (f, field_count)
register struct field_item     **f;
register int     field_count;
{
	static int xwindow;
	static int xtype;
	static int x_or_y;
	float x;
	register int i;
	int j;
	char sbuf[BUFSIZ];

	for (i = 1, j = 0; i < field_count - 4; i += 4, j++)
	{
		sbuf[0] = 'A' + j;
		sbuf[1] = '\0';
		if (strcmp (sbuf, f[i] -> txbuf))
			Show_Default_Field (f[i], sbuf);

		x = ((rand () + 1) / 32768.00) * 110.00 - 10.00;
		sprintf (sbuf, "%.2f", x);
		Show_Default_Field (f[i + 1], sbuf);

		x = ((rand () + 1) / 32768.00) * 110.00 - 10.00;
		sprintf (sbuf, "%.2f", x);
		Show_Default_Field (f[i + 2], sbuf);

		x = (rand () + 1) / 32768.00;
		if (x > 0.8)
		{
			if (strcmp ("Yes", f[i + 3] -> txbuf))
				Show_Default_Field (f[i + 3], "Yes");
		}
		else
		{
			if (strcmp ("No", f[i + 3] -> txbuf))
				Show_Default_Field (f[i + 3], "No");
		}
	}

	calc_update (f, field_count, 0, 0);

	xwindow++;
	if (xwindow > windows)
		xwindow = 1;
	sprintf (sbuf, "%d", xwindow);
	Show_Default_Field (f[field_count - 4], sbuf);

	xtype++;
	if (xtype > 3)
		xtype = 1;
	switch (xtype)
	{
	case 1:
		Show_Default_Field (f[field_count - 3], "Pie");
		break;
	case 2:
		Show_Default_Field (f[field_count - 3], "Hist.");
		break;
	case 3:
		Show_Default_Field (f[field_count - 3], "Point");
		break;
	}

	x_or_y = !(x_or_y);
	if (x_or_y)
		Show_Default_Field (f[field_count - 2], "X");
	else
		Show_Default_Field (f[field_count - 2], "Y");

	Show_Default_Field (f[field_count - 1], "\0");
}

set1_confirm ()
{
	alarm (0);
	set_flag (fglob[0], 0);
	Show_Default_Field (fglob[0], "Yes");
	set_flag (fglob[0], CMEOL);
	reset ();
}

set1_alarm (f, count, index, rc)
register struct field_item     **f;
register int     count;
register int     index;
int     rc;
{
	signal (SIGALRM, set1_confirm);
	alarm (ALARM1);
	return (index);
}

set2_confirm ()
{
	alarm (0);
	set_flag (fglob[fglob_count - 1], 0);
	Show_Default_Field (fglob[fglob_count - 1], "\0");
	set_flag (fglob[fglob_count - 1], CMEOL);
	reset ();
}

set2_alarm (f, count, index, rc)
register struct field_item     **f;
register int     count;
register int     index;
int     rc;
{
	signal (SIGALRM, set2_confirm);
	alarm (ALARM2);
	return (index);
}

set_flag (f, flag)
struct field_item *f;
int flag;
{
	f -> cmflg = flag;
	if (f -> fnalt)
	{
		f -> fnalt -> txflg = f -> txflg;
		f -> fnalt -> txptr = f -> txptr;
		set_flag (f -> fnalt, flag);
	}
}

check_rand (f, count, index, rc)
register struct field_item     **f;
register int     count;
register int     index;
int     rc;
{
/*
 *	Ignore all movement requests
 *
 */
	alarm (0);

	if (rc != 0)
		return (index);

	if (strcmp ("No", f[0] -> txbuf) == 0)
		return (index);

	if (*(f[0] -> txbuf) == '\0')
		Show_Default_Field (f[0], "Yes");

	if (f[0] -> user_mask)
	{
		do_rand (f, count);
		f[0] -> user_mask = FALSE;
		return (count - 1);
	}
	else
		return (index);
}

calc_update (f, count, index, rc)
register struct field_item     **f;
int     count;
int     index;
int     rc;
{
	register int i;
	register char sbuf[BUFSIZ];
	float x;
	float xt;
	float yt;

	xt = 0.0;
	yt = 0.0;

	for (i = 1; i < (count - 4); i = i + 4)
	{
		if (*(f[i + XVALUE] -> txbuf))
		{
			sscanf (f[i + XVALUE] -> txbuf, "%f", &x);
			xt += x;
		}
		if (*(f[i + YVALUE] -> txbuf))
		{
			sscanf (f[i + YVALUE] -> txbuf, "%f", &x);
			yt += x;
		}
	}

	sprintf (sbuf, "%.2f", xt);
	RightString (stdwindow, f[count - 7] -> x_pos + 2,
				f[count - 7] -> y_pos - 1,
				"        ",
				sbuf, FAREVV);

	sprintf (sbuf, "%.2f", yt);
	RightString (stdwindow, f[count - 6] -> x_pos + 2,
				f[count - 6] -> y_pos - 1,
				"        ",
				sbuf, FAREVV);

	return (index);
}
