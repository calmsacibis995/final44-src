.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Form Display and Collection"
.P
The previous section included routines that applied to a single field.
The routines in this section deal with lists of fields.
A routine is also included to collect a position on the screen
from the end_user, Get_Position().
.P
.ne 7
.H 2 Show_List
.CW
Show_List (field_array, count)
struct field_item *field_array[];
int	count;
.CN
The procedure performs a Show_Field() for an array of fields.
The array is ``count'' items long.
The array of fields may include scrollable
regions (i.e. a CMREGN fields).
.sp 2
.ne 8
.H 2 Get_List
.CW
Get_List (field_array, count, ok_to_back, ok_to_forward)
struct field_item *field_array[];
int     count;
boole   ok_to_back;
boole   ok_to_forward;
.CN
This procedure collects input for an array of fields.  The array of
fields may include scrollable regions (i.e. a CMREGN field). The array
is ``count'' items long.  This procedure also handles formatting and
inter-field movement.  Get_List() also executes all application
specified pre and post action routines (see Set_Actions()).
.br
.sp 1
If ``ok_to_back'' is TRUE, Get_List() allows the
user to back off (e.g. using BACK TAB) the front of the list.  If
``ok_to_forward'' is TRUE, Get_List() allows the user to move forward off
(e.g. using the FORWARD directive) the end of the list.
These two flags
are also used internally by Tabs for handling embedded regions.
.sp 2
.ne 9
.H 2 Get_SI_List
.CW
Get_SI_List (field_array, count, start_index,
	ok_to_back, ok_to_forward)

struct field_item *field_array[];
int     count;
int     start_index;
boole   ok_to_back;
boole   ok_to_forward;
.CN
Get_SI_List() has the same parameters as Get_List() with the except of
start_index.  start_index is the index of the field where the cursor is
to be placed for input.
This allows the application to start the input
process at a field other than field zero.
This is very useful for forms
that have default values for the first few fields.
.sp 2
.ne 9
.H 2 Get_Position
.CW
Get_Position (window, row, column, help_string)
struct window *window;
int    *row;
int    *column;
char   *help_string;
.CN
This procedure collects a (row,column) address from the user.  The values
are returned in row and column.  Most of the common methods for moving in
a window are accepted including mouse and function keys.
.sp 2
.H 2 ReShow_All_Lists
.CW
ReShow_All_Lists (clear_flag)
int	clear_flag;
.CN
This procedure displays all fields in all active lists (lists that are
within the Get_List procedure).
When ``clear_flag'' is TRUE all field values are cleared.
When it is FALSE field values are left untouched.
.sp 2
.ne 9
.H 2 ReShow_List
.CW
ReShow_List (field_list, count, clear_flag)
struct field_item	*field_list[];
int	count;
int	clear_flag;
.CN
This procedure displays ``count'' items in the list of fields, ``field_list''.
If ``clear_flag'' is TRUE all field values are cleared.
If it is FALSE field values are left untouched.
.sp 2
.ne 6
.H 2 Clear_Form
.CW
Clear_Form (window)
struct window *window;
.CN
This procedure clears the specified window.  The cursor is
placed at position (0,0) in the window.  The name Clear_Form() comes
from the notion that a form is a collection of controlled I/O areas
contained within a window.
.sp 2
.ne 7
.H 2 Dump_Form
.CW
Dump_Form (window, where)
struct window *window;
FILE *where;
.CN
This procedure prints the specified window.  ``where'' is a stream
pointer obtained from a call to a standard I/O library function such as
fopen or popen.  Windows may be printed even though they are not
currently visible.
.sp 2
.ne 6
.H 2 SCRN_Dump
.CW
SCRN_Dump (where)
FILE *where;
.CN
This procedure prints the current contents of the screen.  "where"
is a stream pointer obtained from a call to a standard I/O library
function such as fopen or popen.
