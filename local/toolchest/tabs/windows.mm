.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Windows"
.H 2 "An Introduction"
The windowing provided with Tabs is produced via a set of functions and
procedures.  These routines are used to manipulate a window data structure.
Windows produced by this window package act essentially like independent
CRT screens with tab stops, scrolling, and cursor movement.  Those who
wish to know more of the internal structure of the windows should
consult the windows.h header file.
.P
Two types of scrolling are available.  With normal
scrolling the entire window will move up one line when a newline is
printed on the bottom line of window or (when the bottom line of the
window extends to the right hand edge of the window).  MIT scrolling is a
much more efficient method of scrolling, especially when used on terminals
that have no line insert and delete capabilities.  In this case overflow
from the bottom line of the window goes to the top line of the window.
This method of scrolling is used on some old systems at MIT, hence the term.
.P
The following line sets the scrolling in the help window to the MIT
variety.
.ne 3
.CW
	errwindow -> _type_scroll = FALSE;
.CN
.H 2 "Window Functions and Procedures"
The following is a list of the most commonly used functions and
procedures for manipulating windows.
.sp 2
.ne 7
.H 3 "New_Window \(em Create a new window"
.CW
struct window  *
New_Window (newwindow)
struct SWindow  newwindow;
.CN
This function creates a new window with the specified characteristics.
The function allocates space for the specified window.
New_Window also guarantees legal placement of the new window.
No screen updating is performed to allow the user
to create more than one window with only one screen update
(see Ref_All_Windows()).
.P
The following is the current contents of the window specification
structure.
.ne 13
.CW
struct SWindow
{
	int top_x;
	int top_y;
	int lines;
	int cols;
	int depth;
	char box_h;
	char box_v;
	char type_scroll;
	int  box_attribute;
};
.CN
.BL
.LI
top_x \(em The row number for the upper left hand corner of the window
.LI
top_y \(em The column number for the upper left hand corner of the window
.LI
lines \(em The number of lines to be included in the window
.LI
cols \(em The number of columns to be included in the window
.LI
depth \(em The artificial depth at which the window is to be displayed (0 to INVISIBLE - currently 200)
.LI
box_h \(em The horizontal boxing character \(em If ``box_h'' is zero no box
will be drawn.
.LI
box_v \(em The vertical boxing character
.LI
box_attribute \(em The visual attributes to be used for boxing the
window.
.LI
type_scroll \(em The type of scrolling to be used in the window \(em Specify
FALSE for MIT style scrolling.
.LE
.P
The value returned is a pointer to the new window.  If a new
window cannot be allocated, -1 is returned.
.sp 2
.ne 7
.H 3 "Free_Window"
.CW
int
Free_Window (window)
struct window  *window;
.CN
This function deletes the specified window.  The storage associated
with the window is freed.  The map of the screen is also updated.
No screen updating is performed.  This allows more than one window
to be deleted with one screen update (see Ref_All_Windows()).
.b
.sp 1
The value returned is the new total number of active windows.  If
the window is not one of the list of windows -1 is returned.
.sp 2
.ne 6
.H 3 Pop_Window
.CW
Pop_Window (window, depth)
struct window  *window;
int depth;
.CN
This procedure moves the specified window to the specified depth. 
Depths run from zero, furthest forward, to INVISIBLE (currently set at 200).
.sp 2
.ne 6
.H 3 Push_Window
.CW
Push_Window (window)
struct window  *window;
.CN
This procedure moves the specified window to level INVISIBLE (currently set at 200).
This makes the window seem to disappear.
.sp 2
.ne 10
.H 3 "Move_Window"
.CW
void
Move_Window (window, toprow, topcolumn, depth)
struct window *window;
int     toprow;
int     topcolumn;
int     depth;
.CN
This procedure moves the specified window to the indicated (row,column)
and simulated depth.  Move_Window guarantees legal placement of
the window.  No screen updating is performed to allow the user
to move more than one window with only one screen update
(see Ref_All_Windows()).
.sp 2
.H 3 "Dup_Window"
.CW
Dup_Window (window)
struct window	*window;
.CN
This procedure duplicates a window created with New_Window() and
returns a pointer to the new window.
The new window will be at the same row and column as the original
but will have a depth one position nearer to the top.
.sp 2
.ne 7
.H 3 "Wrefresh"
.CW
void
Wrefresh (window)
struct window *window;
.CN
This procedure updates the specified window.  This procedure assumes that
windows at depths greater than the defined constant INVISIBLE are not
visible.  INVISIBLE is currently set at 200.
.sp 2
.ne 6
.H 3 "Ref_All_Windows"
.CW
void
Ref_All_Windows ()
.CN
This procedure updates all of the windows.
This procedure assumes that
windows at depths greater than the defined constant INVISIBLE are not
visible.
INVISIBLE is currently set at 200. The update includes boxing
the windows.
.sp 2
.ne 6
.H 3 "Refresh"
.CW
void
Refresh ()
.CN
This procedure clears the screen and then updates all of the windows.
This is useful for recovering from things such as ``wall'' messages.
.sp 2
.ne 19
.H 3 "New_Rel_Window"
.CW
struct window	*
New_Rel_window (SWindow, parent_window)
struct SWindow	SWindow;
struct window	*parent_window;
.CN
This procedure creates a new window and positions it in a tree of window
related windows.
It is placed beneath ``parent_window'' in the tree.
When ``parent_window'' is moved with Move_Rel_window(), the new window and all
other windows beneath ``parent_window'' in the tree are moved the same relative 
amount if possible.
Likewise, when ``parent_window'' is freed with Free_Rel_Window(), ``window''
is freed along with any other window beneath ``parent_window'' in the tree.
See also Pop_Rel_Window(), Push_Rel_Window(), Dup_Rel_Window(), and
Change_Parent().
The elements in the SWindow structure are relative to the location of
``parent_window'' instead of absolute locations like they are with
New_Window().
This means, for example, that ``depth'' must be less than 0 if it is to
appear in front of ``parent_window.''
See [6] for more information on related windows.
.sp 2
.H 3 "Free_Rel_Window"
.CW
Free_Rel_Window (window)
struct window	*window;
.CN
This procedure calls Free_Window() for windows created with either
New_Rel_Window() or New_Window().
If ``window'' has dependent windows, they are also freed.
.sp 2
.ne 11
.H 3 Pop_Rel_Window
.CW
Pop_Rel_Window (window, depth)
struct window	*window;
int	depth;
.CN
This procedure moves windows created with New_Rel_Window() or
New_Window() in depth.
``depth'' is the absolute new depth of the window.
Popping the window to a depth of INVISIBLE (currently set at 200) makes the window 
invisible.
If ``window'' has dependent windows, they also get moved the same
relative amount as ``window''.
.sp 2
.ne 7
.H 3 Push_Rel_Window
.CW
Push_Rel_Window (window)
struct window	*window;
.CN
This procedure makes a window created with New_Rel_Window() or New_Window()
invisible.
If ``window'' has dependent windows they are also made invisible.
.sp 2
.ne 17
.H 3 "Move_Rel_Window"
.CW
Move_Rel_Window (window, top_row, top_column, depth)
struct window	*window;
int	top_row;
int	top_column;
int	depth;
.CN
This procedure moves a window created either with New_Rel_Window or 
New_Window to a new row, column and depth location.
``top_row'' is the new row for the upper left corner of the window.
``top_column'' is the new column for the upper left corner of the window.
``top_row'' and ``top_column'' are absolute coordinates (relative to the 
upper left corner of the screen).
If ``window'' has dependent windows they are moved the same relative amount
so that the relative position and depth of the dependent windows to ``window'' are
maintained.
.sp 2
.H 3 "Dup_Rel_Window"
.CW
Dup_Rel_Window (window, type)
struct window	*window;
char	*type;
.CN
This procedure duplicates a window created with New_Rel_Window() 
or New_Window().
If the ``type'' is ``all'' and the windows has dependents, they will also 
be duplicated.
Otherwise, just ``window'' will be duplicated.
Each new window will be at the same row and column as the original
but will have a depth one position nearer to the top.
It is often necessary to reposition windows in the hierarchy
or on the screen immediately after they are copied.
See Pop_Rel_Window(),
Change_Parent() and Move_Rel_Window().
.sp 2
.H 3 "Change_Parent"
.CW
Change_Parent (window, new_parent)
struct window	*window;
struct window	*new_parent;
.CN
This procedure repositions a window in the hierarchical tree of windows.
All windows beneath ``window'' in the hierarchy remain beneath it.
See also New_Rel_Window(), Dup_Rel_Window(() and Move_Rel_Window().
.sp 2
.ne 9
.H 3 "w_mgo"
.CW
void
w_mgo (window, row, column)
struct window *window;
int    row;
int    column;
.CN
This procedure moves the (real and virtual) cursor to the
(row,column) position in the specified window.
.sp 2
.ne 9
.H 3 "w_sgo"
.CW
void
w_sgo (window, row, column)
struct window *window;
int	row;
int	column;
.CN
This procedure moves the real cursor to the
(row,column) position in the specified window.
.sp 2
.ne 7
.H 3 "w_xgo"
.CW
void
w_xgo (window, row, column)
struct window *window;
.CN
This procedure moves the virtual cursor to the
(row,column) position in the specified window.
.sp 2
.ne 7
.H 3 "wclrl"
.CW
void
wclrl (window)
struct window *window;
.CN
This procedure clears the rest of the current line in the specified
window.
.sp 2
.ne 15
.H 3 "waxprintf and wxprintf"
.CW
void
waxprintf (window, attribute, sp, ap1, ap2, ap3, ap4, ap5, ap6, ap7)
int    attribute;

and

void
wxprintf (window, sp, ap1, ap2, ap3, ap4, ap5, ap6, ap7)
struct window *window;
char   *sp;
char   *ap1;
char   *ap2;
char   *ap3;
char   *ap4;
char   *ap5;
char   *ap6;
char   *ap7;
.CN
These procedure are window based printfs.  ``sp'' is the format string.
