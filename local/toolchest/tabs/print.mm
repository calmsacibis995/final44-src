.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Formatted Printing of Strings"
.P
These routines print strings on the screen according to a specified format.
.P
.ne 9
.H 2 Print_Form
.CW
Print_Form (window, row, column, attribute, string)
struct window  *window;
int     row;
int     column;
int     attribute;
char   *string;
.CN
This procedure prints the specified string in the specified window
at location (row, column) in the window.  The attribute argument
specifies the visual attribute that is to be applied to the string.  See
the Set_Attribute() procedure for a list of available visual attributes.
.sp 2
.ne 9
.H 2 Del_P_Form
.CW
Del_P_Form (window, row, column, string)
struct window  *window;
int     row;
int     column;
char   *string;
.CN
This procedure deletes the specified string in the specified window
at location (row, column) in the window.  A string of blanks is used to
``cover'' the old string.  No check is made as to whether the string is
actually present in the window prior to performing the delete operation.
.sp 2
.ne 8
.H 2 Print_Center
.CW
Print_Center (window, row, attribute, string)
struct window  *window;
int     row;
int     attribute;
char   *string;
.CN
This procedure prints the specified string centered on line ``row'' in the
specified window.  The attribute argument specifies the visual
attribute that is to be applied to the string.  See the Set_Attribute()
procedure for a list of available visual attributes.
.sp 2
.ne 8
.H 2 Del_P_Center
.CW
Del_P_Center (window, row, string)
struct window  *window;
int     row;
char   *string;
.CN
This procedure deletes the specified string centered on line ``row'' in the
specified window.  A string of blanks is used to ``cover''
the old string.  No check is made as to whether the string is actually
present in the window prior to performing the delete operation.
.sp 2
.ne 10
.H 2 LeftString
.CW
LeftString (window, row, column, fill_char, value, attribute)
struct window *window;
int     row;
int     column;
char   *fill_char;
char   *value;
int     attribute;
.CN
This procedure left justifies the specified value at position (row, column)
in the specified window.  ``fill_char'' is used as background text.  The
attribute argument specifies the visual attribute that is to be applied
to the string.  See the Set_Attribute() procedure for a list of
available visual attributes.
.sp 2
.ne 10
.H 2 CenterString
.CW
CenterString (window, row, column, fill_char, value, attribute)
struct window *window;
int     row;
int     column;
char   *fill_char;
char   *value;
int     attribute;
.CN
This procedure centers the specified value at position (row, column)
in the specified window.  ``fill_char'' is used as background text.
The attribute argument specifies the visual attribute that is to be
applied to the string.  See the Set_Attribute() procedure for a list of
available visual attributes.
.sp 2
.ne 10
.H 2 RightString
.CW
RightString (window, row, column, fill_char, value, attribute)
struct window *window;
int     row;
int     column;
char   *fill_char;
char   *value;
int     attribute;
.CN
This procedure right justifies the specified value at position (row,column)
in the specified window.  ``fill_char'' is used as background text.  The
attribute argument specifies the visual attribute that is to be applied
to the string.  See the Set_Attribute() procedure for a list of
available visual attributes.
