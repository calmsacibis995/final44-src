.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Scrollable Regions"
.P
These routines create and free scrollable regions.
New_Scroll_Region does more work than New_Region.
It will create the window and the region field in addition to the
list of fields.
.P
.ne 11
.H 2 "New_Region \(em Create a scrollable region"
.CW
New_Region (window, field_list, count, rows, field_region, skip)
struct window  *window;
struct field_item     **field_list;
int     count;
int     rows;
struct field_item     **field_region;
int     skip;
.CN
This procedure creates a list of fields for a scrollable region. 
Scrollable regions allow the programmer to collect ROWS lines of fields
in an N line area, where ROWS may be greater than N.  A scrollable
region may be used much like a regular field.  The arguments to
New_Region() are as follows.
.BL
.LI
window
.br
.sp 1
This is a pointer to a window structure obtained from a call to the
function New_Window().  Scrolling is confined to the specified
window.
.LI
field_list
.br
.sp 1
This is an array of fields created with the New_Field() function.  This
is the list of fields that will be repeated on each line of the
scrollable region.  This list may contain one or more fields.
Fields may be on more than one row.
Row positions should start at 0.
.LI
count
.br
.sp 1
This is the number of fields in the ``field_list'' array.
.LI
rows
.br
.sp 1
This is the number of lines to be included in the scrolling region.
.LI
field_region
.br
.sp 1
This is the array of fields that will be used in the scrollable region. 
This is a one dimensional array of field pointers.  Care should be taken
to guarantee that field_region contains at least ``count'' time ``rows''
field pointers.
.LI
skip
.br
.sp 1
This is the number of lines to skip between rows in the region.
.LE
.br
.sp 1
Once the scrollable region has been constructed it may be attached to another
list of fields.  A scrollable region used in this fashion can be treated
essentially like one field by the programmer.  Show_List() and Get_List()
can be used to perform the appropriate actions.
.br
.sp 1
The following two lines of code is a sample set up for a scrollable region.
A CMREGN field is a field that points to an array of fields created with
the New_Region() procedure.
.ne 6
.CW
	New_Region (reg_window, fline, 4, 20, fregion, 1);

	f[2] = New_Field (9, 12, CMREGN, (char *) fregion,
		(char *) (4 * 20), 0);
.CN
The arguments to New_Field() for CMREGN are somewhat different than
those used to create the other field types.  The (row,column) position should
be the top left hand corner of the window (this will be used for mouse
and cursor movement selection).  The ``fill_char'' argument is a pointer
to the array of fields.  The ``help'' argument is the number of fields
in the array.
.br
.sp 1
Appendix F contains a sample C based form that uses a scrollable region.
.sp
.ne 16
.H 2 "New_Scroll_Region"
.CW
struct field_item	*
New_Scroll_Region (row, column, height, width, sample_list, count, 
repetitions, skip, region_list, parent_window)
int	row;
int	column;
int	height;
int	width;
struct field_item	*sample_list[];
int	count;
int	repetitions;
int	skip;
struct field_item	*region_list[];
struct window	*parent_window;
.CN
This procedure creates a new scrollable region
and returns a pointer to
a field of type CMREGN.
It creates a new window and places the list in that window.
The arguments are used as follows:
.BL
.ne
.LI
row
.br
.sp 1
This is the row or line position of the upper left corner of the
window containing the region.
Row and column are based relative to parent_window or to the upper
left corner of the screen if parent_window is 0.
.ne
.LI
column
.br
.sp 1
This is the column position of the new window.
.ne
.LI
height
.br
.sp 1
This is the height of the new window in rows.
.ne
.LI
width
.br
.sp 1
This is the width of the new window in columns.
.ne
.LI
sample_list
.br
.sp 1
This is a list of fields that represents one repetition of the fields
in the new region.
.ne
.LI
count
.br
.sp 1
This is the number of fields in the sample_list list of fields.
.ne
.LI
repetitions
.br
.sp 1
This is the number of times the sample_list list of fields will be repeated
in the region.
.ne
.LI
skip
.br
.sp 1
This is the number of rows to skip between repetitions of the sample_list
list of fields.
.ne
.LI
region_list
.br
.sp 1
This is the array of field pointers that will be used in the new region.
This must contain (count * repetitions) number of fields.
.ne
.LI
parent_window
.br
.sp 1
The new region window will be placed relative to the parent_window.
See New_Rel_Window() for an explanation of related windows.
If parent_window is 0, the new window will be positioned with absolute 
coordinates and can only be moved (row, column and depth) independently 
of other windows.
.LE
.sp 2
.ne 13
.H 2 "Free_Region"
.CW
Free_Region (field_ptr)
struct field_item	*field_ptr;
.CN
This procedure frees the space associated with a field of type CMREGN created
with New_Field() and either New_Region() or New_Scroll_Region().
It also deletes the region from the display.
If the field is not a CMREGN field, the field will be freed and deleted from
the display.
