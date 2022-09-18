.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Error Messages"
.P
These routines control the display of error information on the screen.
.P
.ne 14
.H 2 "Print_Message"
.CW
Print_Message (window, attribute, sp, ap1, ap2, ap3, ap4,
				ap5, ap6, ap7)
struct window  *window;
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
This procedure prints a formatted error or warning message on
the last line of the specified window.  Argument ``sp'' is the format
string like the one used in sprintf().
The attribute argument specifies the visual
attribute that is to be applied to the string.  See the Set_Attribute()
procedure for a list of available visual attributes.
.sp 2
.ne 7
.H 2 "Set_Error"
.CW
Set_Error (field_ptr, message);
struct field_item *field_ptr;
char   *message;
.CN
This procedure sets the error message for the specified field.  All
errors that occur in the specified field will be ``announced'' with the
new message.
.sp 2
.ne 8
.H 2 "Def_Error_Attr"
.CW
Def_Error_Attr (flags)
int	flags;
.CN
This procedure defines the attributes flags to be used when error messages
are displayed.
``flags'' is just like the flags argument to Set_Attributes().
