.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
H 1 "Contextual Positioning of Fields"
.P
.ne 20
.H 2 Auto_Show_List
.CW
Auto_Show_List (f, nfields, start_index, context, between_rows, field_width,
	field_cols, start_row, Winner, up_winner, row, col, rel_depth,
	recurse_flag )
struct field_item	**f;
int	nfields;
int	start_index;
int	context[];
int	between_rows;
int	field_width;
int	field_cols;
int	start_row;
struct window	*Winner;
struct window	*up_winner;
int	row;	/* last three only apply if Winner is 0 */
int	col;
int	rel_depth;
int	recurse_flag;
.CN
This procedure contextually (automatically) positions fields on a form 
and will optionally create a window just big enough for the form.
The width of the window is divided into field-columns.
If the column of the field is adjustable, the field (field label if the label
is on the left)
will be lined up on the column boundary.
Successive fields are placed first across the window, then in the first
field-column of the next row if the field does not fit on the current row.
Fields are positioned relative to the previous field in the list regardless
of the ``context'' (defined below) of the previous field.
.P
Auto_Show_List() will not position fields around regions created with 
New_Region() or New_Scroll_Region(),
static menus created with New_Match_Menu() or menus created with 
New_Fixed_Menu().
It will position fields around static menus created with New_Static_Menu()
except for menus positioned to the left or right of the field.
and will handle all other field types described in this manual.
This routine is good for prototyping and when the number and order of fields
in a form might change often.
The arguments are used as follows:
.BL
.LI
f
.br
.sp 1
This is the list of fields to be positioned and displayed
.sp 1
.LI
nfields
.br
.sp 1
This is the number of fields in the list
.sp 1
.LI
start_index
.br
.sp 1
This is the index of the first field to be displayed
.sp 1
.LI
context
.br
.sp 1
This is an array describing how the field should be positioned.  The indexes
for the array correspond to the indexes in the array of fields ``f''.
There must be an element for each field.
The available contexts
are as follows:
.sp 1
.DL
.LI
C_NOADJ - use the ``x'' (row) and ``y'' (column) positions from the call to 
New_Field().
The row and column indicators keeping track of the laying out of the form
for contextually positioned fields are not affected by a NOADJ field.
.LI
C_CENTER - center the field in a row by itself.
.LI
C_SKIPCEN - like CENTER but skips a row first.
.LI
C_RIGHT - the field will be moved over to the next
field-column to the right in the window or to the first field-column of the 
next row if there is not enough room.
.LI
C_SKIPCOL - like RIGHT but skips a column.
.LI
C_STARTROW - start a new row with the field in the left-most field-column.
.LI
C_SKIPROW - like STARTROW but skips a row first.
.LE
.P
.sp 1
.LI
between_rows
.br
.sp 1
This is the number of rows that will be skipped if a field has to be moved to
the next row.
.sp 1
.LI
field_width
.br
.sp 1
This is the width of one field-column
.sp 1
.LI
field_cols
.br
.sp 1
This is the number of field-columns in one row of the window
.sp 1
.LI
start_row
.br
.sp 1
This is the first row in the window where fields will be positioned.
.sp 1
.LI
Winner
.br
.sp 1
This is the window the fields will be positioned within.
If it is 0, a new
window will be created just big enough to contain the lists of fields.
All fields in the list will be set to the new window - see Set_Window();
.sp 1
.LI
up_winner
.br
.sp 1
This is the window the new window will be placed relative to - see New_Rel_Window().
If it is 0 stdwindow will be used.
.sp 1
.LI
row
.br
.sp 1
This is the row of the upper left corner of the window.
.sp 1
.LI
col
.br
.sp 1
This is the column of the upper left corner of the window.
.sp 1
.LI
rel_depth
.br
.sp 1
This is the depth, relative to up_winner, that the new window will be placed.
If you want the new window to be visible, this must be negative (closer to the
top depth of 0).
.sp 1
.LI
recurse_flag
.br
.sp 1
This is used to determine whether to call Auto_Show_List recursively to
reposition fields if a static menu is created at the top of the window - see
New_Static_Menu().
The normal response is FALSE.
You should only specify TRUE if the form contains a static menu across the
top of the form and start_row does not take into account the height of the
menu.
If TRUE is specified, start_row will be moved down the height of the 
menu and Auto_Show_List will recurse.
.LE
.sp 2
.H 2 Free_Auto_List
.CW
Free_Auto_List (f, nfields)
struct field_items	**f;
int	nfields;
.CN
This procedures frees the first ``nfields'' fields in the field list ``f''.
It also frees the window the first
field is in unless it is stdwindow, the main window created by Start_Form().
If the first field is in stdwindow, Clear_Form() is called with stdwindow
as its argument.
