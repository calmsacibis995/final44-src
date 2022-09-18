.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Scratchpad and Marked Areas"
.P
These routines create and manipulate marked areas.
Scratchpad operations are available for use with marked areas.
Turning on marked areas enables character directives for sweeping 
out areas with a mouse.
.P
.ne 19
.H 2 New_Marked_Area
.CW
New_Marked_Area (area_index, top_row, top_col, bot_row, bot_col)
int	area_index;
int	top_row;
int	top_col;
int	bot_row;
int	bot_col;
.CN
This procedure creates a marked area.
The area is not displayed on the screen until ReShow_All_Lists()
is called so that more than one area can be created at a time.
There are a maximum of three areas that can be marked.
Therefore, ``area_index'' can have a value of 1, 2 or 3.
The upper left corner of the area is defined by ``top_row'' and ``top_col''.
The lower right corner of the area is defined by ``bot_row'' and ``bot_col''.
Def_Marked_Areas() enables or disables marked areas and Set_Area_Attributes()
determines the attributes with which the marked area will be displayed.
Clear_Marked_Areas() resets all marked areas.
.sp 2
.ne 9
.H 2 Def_Marked_Areas
.CW
Def_Marked_Areas (flag)
int	flag;
.CN
This procedure enables (when flag is TRUE) or disables (when flag is FALSE)
the display of marked areas.
Mouse functions are enabled so that sweeping with a mouse will mark an area.
New_Marked_Area() creates a marked area and Clear_Marked_Areas() resets
marked areas.
The default is FALSE.
When flag is TRUE
mouse character directives are enabled so that sweeping with a mouse will
mark an area.
.sp 2
.ne 5
.H 2 Clear_Marked_Areas
.CW
Clear_Marked_Areas ()
.CN
This procedure resets marked areas by turning off the areas and
reshowing all lists on the screen.  
.sp 1
.ne 7
.CW
Def_Area_Attributes (flags)
int	flags;
.CN
This procedure defines the attributes flags to be used when marked areas
are displayed.
``flags'' is just like the flags argument to Set_Attributes().
.sp 2
.ne 8
.H 2 Def_Scratchpad
.CW
Def_Scratchpad (flag)
boole	flag;
.CN
This procedure enables (when flag is TRUE) or disables (when flag is FALSE)
scratchpad operations for marked areas.
The default is FALSE.
The scratchpad operations and keystrokes necessary to invoke
the operations are as follows:
.BL
.LI
CTRL(X)x - (cut) - cut the contents of the marked area to the scratchpad.
.LI
CTRL(X)c - (copy) - copy the contents of the marked area to the scratchpad.
.LI
CTRL(X)a - (append) - append the contents of the marked area to the scratchpad.
.LI
CTRL(X)p - (paste) - paste the contents of the scratchpad.
.LI
CTRL(X)d - (delete) - delete the contents of the marked area.
.LE
.P
Def_Scratchpad() calls Def_Marked_Areas() with flag equal to TRUE, calls
New_Marked_Area() to create marked areas and calls Clear_Marked_Areas() to
remove them.  See also Def_Area_Attributes().
