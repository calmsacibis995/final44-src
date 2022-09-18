.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 Help
.P
These routines control the display of help information on the screen.
.P
.ne 10
.H 2 Set_Help
.CW
Set_Help (field_ptr, string, print_col, suppress, help_routine)
struct field_item *field_ptr;
char   *string;
boole   print_col;
boole   suppress;
int   (*help_routine) ();
.CN
This procedure is used to change the help attributes of the specified
field.
.BL
.LI
``string'' is the new help string.  If string is 0 or "\\0",
then the standard system help line will be used.
.LI
``print_col'' is a flag that should be TRUE if the help messages are to be
printed as one column (the default) and FALSE if
the output is to be printed as a tight row.  Row style output is harder to
read, but allows more information to be displayed at one time.
.LI
``suppress'' is a flag that specifies if the list part of the
help information is not to be presented.  The list part of the help
information includes keywords, wild carded filenames, environmental
variable names, and the range information for numeric fields.
If suppress is FALSE (the default), the standard list part of the help
messages is provided.
.LI
``help_routine'' is a pointer to a help function.  This help function
is invoked whenever the end user requests help.  The function may be
used to supply changing or dynamic aspects of some help information. 
The help procedure should have one argument, a pointer to the current
field.  The following code fragments could be used to add the date
to a help message.
.P
.ne 25
.CW
main ()
{
~
extern int hlp ();
~
Set_Help (f[0], "Enter a date.", FALSE, TRUE, hlp);
~
}

hlp (field_ptr)
struct field_item *field_ptr;
{
	long    Time_loc;
	char   *C_time;
	char sbuf[80];

	Time_loc = (long) time (0);
	C_time = (char *) ctime (&Time_loc);
	C_time[strlen(C_time) - 1] = '\0';

	sprintf (sbuf, "Today's date is: %s", C_time);
	prhlp (field_ptr, sbuf, FALSE, FALSE);
}
.CN
.LE
.br
.sp 1
If ``suppress'' is TRUE and ``string'' and ``help_routine'' are 0, no
help of any kind will given.
.sp 2
.ne 7
.H 2 "Def_Help_Help"
.CW
Def_Help_Help (string)
char	*string;
.CN
This procedure defines the string of characters that tells how to get help.
The default is "- Type  ? for help".
This string is printed with most error messages.
.sp 2
.ne 14
.H 2 "Print_Help_Window"
.CW
Print_Help_Window (field_ptr, attribute, sp, ap1, ap2, ap3, ap4,
					ap5, ap6, ap7)
Struct field_item      *field_ptr;
int     attribute;
char   *sp;
char   *ap1;
char   *ap2;
char   *ap3;
char   *ap4;
char   *ap5;
char   *ap6;
char   *ap7;
.CN
This procedure prints to the help window of the specified field.
If the help window is not at level 0 it is moved into place.
Argument ``sp'' is the format string like the one used in sprintf().
The attribute argument
specifies the visual attribute that is to be applied to the string.  See
the Set_Attribute() procedure for a list of available visual attributes.
.sp 2
