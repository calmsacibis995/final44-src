.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Menus"
.P
These routines create, free and control the display of menus on the screen.
There are two basic types of menus, best-match menus and menus of fields.
New_Menu and Free_Menu treat menus as a region of fields.
Other routines treat menus as a simple list of items.
End-user interaction is different for the two menu types.
See [5] for a more complete description of match style menus.
.sp 2
.ne 11
.H 2 "New_Menu \(em Create a Menu as a Scrollable Region"
.CW
New_Menu (field_ptr, xorigin, yorigin, height, width, 
		orient, fregion, field_count)
struct field_item  *field_ptr;
int     xorigin;
int     yorigin;
int     height;
int     width;
char   *orient;
struct field_item ***fregion;
int    *field_count;
.CN
This procedure creates menus from CMKEY or CMKEY_LIST fields. 
The item that is selected from the menu is placed in the keyword field.
This procedure creates an array of fields, one per keyword and a window
for displaying the new menu.  Menus created using this routine scroll
to display long lists of keywords.  Keywords may also be displayed
vertically or horizontally in columns.
The following is a description of the arguments to the procedure.
.BL
.LI
field_ptr
.br
.sp 1
This is a pointer to a field structure created with a call to
New_Field().  The field must be a CMKEY or CMKEY_LIST type.
.LI
xorigin
.br
.sp 1
This is the row origin for the menu window.
.LI
yorigin
.br
.sp 1
This is the column origin for the menu window.
.LI
height
.br
.sp 1
This is the height for the menu window.
.LI
width
.br
.sp 1
This is the width for the menu window.
.LI
orient
.br
.sp 1
This is the orientation for the menu window.  The first character of the
string should be an ``h'' for horizontal or a ``v'' for vertical.
.LI
fregion
.br
.sp 1
This is a pointer to an array of field pointers.  The newly created
fields will be created using these pointers.  Be careful to allocate
enough pointers.
.LI
field_count
.br
.sp 1
This is a pointer to an integer in which the number of fields (count)
will be returned.
.LE
.P
The return from New_Menu() is a boole that specifies if the menu was
created.  malloc() is used to create the new menu.
.P
The following is a code fragment for using New_Menu() to create static
menus.
.CW
	fkeys = New_Field (6, 33, CMKEY, "____________",
			0, "a few key words");

	Set_Label (fkeys, "left", "Selection: ", FANORMAL);

	if (New_Menu (fkeys, 19, 20, 8, 40, "hvertizontal",
			&fregion, &count))
	{
		f[new] = New_Field (fregion[0] -> window -> _x_pos,
				fregion[0] -> window -> _y_pos,
				CMREGN,
				(char *) fregion, (char *) count, 0);

		Pop_Window (fregion[0] -> window,
				f[index] -> window -> _depth - 1);
	}

	Show_List (f, count);

	Get_List (f, count, FALSE, FALSE);
.CN
For pop-up style menus use something like the following.
N_M_pre_pop_up is included in the Tabs library.
It pops up the region window to make it visible, calls Get_List() for the 
region, pushes the region window to make it disappear and then returns
the index to the next field.
.CW
	extern int N_M_pre_pop_up ();

	f[new] = New_Field (6, 33, CMKEY, "____________",
			0, "a few key words");

	Set_Label (f[new], "left", "Selection: ", FANORMAL);

	if (New_Menu (f[new], 19, 20, 8, 40, "hvertizontal",
			&fregion, &count))
	{
		f[new] -> user_pointer = (char *) fregion;
		f[new] -> user_mask = count;
		Set_Actions (f[new], N_M_pre_pop_up, 0);
	}

	Show_List (f, count);

	Get_List (f, count, FALSE, FALSE);
.CN
.sp 2
.ne 6
.H 2 Free_Menu
.CW
Free_Menu (fregion, count)
struct field_item **fregion;
int count;
.CN
This procedure frees the space associated with the specified list of
fields.  The fields must have been created with the New_Menu() procedure.
This routine does not delete the fields or labels from the window
display.
.sp 2
.ne 11
.H 2 New_Match_Menu
.CW
New_Match_Menu (field_ptr, xorigin, yorigin, max_height, max_width,
                   orient, type)

struct field_item *field_ptr;
int     xorigin;
int     yorigin;
int     max_height;
int     max_width;
char   *orient;
char   *type;
.CN
.P
This function creates menus from keywords defined in existing CMKEY or
CMKEY_LIST fields.  Menus are displayed in a separate window created by 
New_Match_Menu().  The CMKEY or CMKEY_LIST field serves as a response field for
the menu.  As characters are typed into the response field, the response
is matched against the items in the menu.  The closest  match as
determined by the crosscor() function.  The item most closely matching
the user's input is highlighted and  pointed at with ">".  This is
repeated for each character entered by the user until the user moves to
the next field.
.P
The number of selections for the menu can be set with the function
Set_M_Selections() described below.
The default is one selection.
The user enters the multiple selection character to begin a new  match area
in the response field.
The field is divided into sections separated by the multiple selection 
character (the default is "|", see Def_M_Char() below).
For each match area a separate best match is determined.
The item in the menu that matches is marked with a ">".
The other matched items are marked with a "+".
When the user tries to select too many items the
left most  match area in the response field is deleted.
With a single character field the effect is the same as hitting the line 
kill key (i.e. it erases the field).
.P
The display of the menu window can be delayed (see Set_M_Delay()).
Delaying the menu allows users to move quickly within a form, avoiding
popup menus.
The delay also allows experienced to avoid menus.
Providing user-selectable delays for menus
is one way to allow users to adapt the system to their own level of
expertise.
.P
There are two types of menus; popup and static.  Popup menus only appear
when the cursor is in the response field.  Static menus are always at
one depth less than the response field.   Menus can either be vertical
or horizontal.  Items in vertical menus are left justified and are
listed top to bottom.  Additional columns are added as needed up to the
maximum allowed by the width of the menu window.  Items in horizontal
menus are centered and listed left to right.  Additional rows are added
as needed up to the maximum height of the menu window.
.P
The size of a menu window is adjusted to fit the number of items.  For
vertical menus, the window is collapsed right to left, then bottom to
top.  For horizontal menus, the window is collapsed bottom to top, then
right to left.  If the items don't fit in the window, the menu is not
displayed.  The help message will show what items can be selected, and
the user can find out what item(s) matches the contents of the response
area with the completion key or by going to another field.  The
contents of the response area are always expanded when the user leaves
the field.
.P
If the xorigin or yorigin is less than zero the size and location
of the window are set by the menu function.  The menu window is
centered above the response field if the field is in the bottom
half of the screen and below the response field if the field is
in the top half of the screen.  If you choose to let the menu
function determine the location of the window you will not have to
re-calculate where the menu window should go each time you move the
response field.
.P
The user_pointer in the field_items structure for the response field is
used to point to the menu structure (see below).  The item selected is
in the usual place, field_ptr->txbuf, and can be retrieved
using Field_Value().  The index to the first item in
the response field is in field_ptr->fndfv and is 0 based.  See
Set_M_Selections() for what happens when there is more than one 
selection.
.P
Menus created with New_Match_Menu() need a post_action routine,  
Post_Match_Menu() (see below).  It is assigned as the post_action
routine in the call to New_Match_Menu().  If you write a post_action 
routine, call Post_Match_Menu from your routine.  Be sure to assign your 
post_action routine after the call to New_Match_Menu().
.P
New_Popup_Menu(), New_Static_Menu() and New_Fixed_Menu() provide a higher-level 
interface for creating menus.
.P
The arguments to New_Match_Menu() are used as follows:
.BL
.LI
field_ptr
.sp 1
This is a pointer to a field structure created with a call to
New_Field().  The field must be a CMKEY or CMKEY_LIST type.
.LI
xorigin
.br
.sp 1
This is the row origin (upper left corner) for the menu window.
If ``xorigin'' is less than 0, the location and size of the menu window
are determined automatically by New_Match_Menu().
.LI
yorigin
.br
.sp 1
This is the column origin for the menu window.
If ``yorigin'' is less than 0, the location and size of the menu window
are determined automatically by New_Match_Menu().
.LI
max_height
.br
.sp 1
This is the maximum possible height for the menu window and the maximum
possible number of rows of items.  ``max_height'' is ignored if ``xorigin'' or
``yorigin'' is less than 0.
.LI
max_width
.br
.sp 1
This is the maximum possible width for the menu window.  This is 
used to determine the maximum possible number of columns.  The number of
columns is determined with the following calculation:
``max_width'' / (length of longest item + 3 ).  ``max_width'' is ignored if
``xorigin'' or ``yorigin'' is less than 0.
.LI
orient
.br
.sp 1
This is the orientation for the menu window.  The first character
of the string should be an "h" for horizontal and a "v" for 
vertical.  See above for a description of what vertical and 
horizontal mean.
.LI
type
.br
.sp 1
Type is either popup or static.  The first letter must be a "p"
for popup and an "s" for static.
.LE
.P
The following is a code fragment for using New_Match_Menu() to 
create a popup menu.
.CW
	f[index] = New_Field (6, 33, CMKEY, "__________", 0,
				 "a few items");

	Set_Label (f[index], "left", "Choice: ", FANORMAL);

	if (New_Match_Menu (f[index], 8, 33, 10, 45,
				      "vertical", "popup")
			== FALSE)
	{
		Print_Message (stdwindow, FANORMAL,
			"Cannot create match menu");
	}

	index++;

	Show_List (f, index);

	Get_List (f, index);
.CN
.sp 2
.ne 6
.H 2 Free_Match_Menu
.CW
Free_Match_Menu (field_ptr)
struct field_item      *field_ptr;
.CN
This procedure frees any space created by the call to New_Match_Menu()
associated with the specified field.  The field itself is not freed.
.sp 2
.ne 14
.H 2 New_Popup_Menu
.CW
New_Popup_Menu (field_ptr, delay, location)
struct field_item	*field_ptr;
int	delay;
char	*location;
.CN
This procedure creates a popup menu from a CMKEY or CMKEY_LIST field.
It is a higher-level interface for creating New_Match_Menu() style
popup menus.
Popup menus created with New_Popup_Menu are always layed out vertically and
are not confined to the window the response field is in the way
static menus are.
``delay'' is the delay in seconds between characters before the menu
appears (see Set_M_Delay()).
``location'' is the same as for New_Static_Menu().
Post_Match_Menu() and New_Match_Menu() describe how to use post action
routines for popup mens.
See also Set_M_Selections(), Def_M_Char(), Set_M_Delay() and Free_Match_Menu().
.sp 2
.ne 16
.H 2 New_Fixed_Menu
.CW
New_Fixed_Menu (field_ptr, window, orient)
struct field_item	*field_ptr;
struct window	*window;
char	*orient;
.CN
This routine displays the menu items in the ``window'' passed to it or,
if ``window'' is 0, it creates a borderless window across the top of the
screen and displays the items in that window.
This routine does not touch the window except to display items in the
window.
That is, it does not move the window in depth when the user enters the
field nor does it clear the window or push it when the user leaves
the field.
``orient'' is the same as it is for New_Match_Menu().
If you use a post-action routine with a New_Fixed_Menu() field be sure
to call Post_Match_Menu() from within the post-action routine as described
in New_Match_Menu().
.sp 2
.ne 12
.H 2 New_Static_Menu
.CW
New_Static_Menu (field_ptr, max_height, location)
struct field_item	*field_ptr;
int	max_height;
char	*location;
.CN
This procedure creates a static menu from a CMKEY or CMKEY_LIST field.
It is a higher-level interface for creating New_Match_Menu() style 
static menus.
Static menus created with New_Static_Menu() are always layed out horizontally
within the window the response field is in.
``max_height'' is the maximum possible height in rows the menu window can
be.
``location'' is where the menu window will be located as follows:
.BL
.LI
left - left of the field.
The window will start at the same row as the field and extend to the left
and down.
.LI
right - right of the field.
The window will start at the same row as the field and extend to the
right and down.
.LI
above or over - above the field.
The window will be centered above the field and extend left, right and up.
.LI
under - below the field.
The window will be centered below the field and extend left, right and down.
.LI
top - across the top of the window the field is in, extending down.
.LI
bottom - across the bottom of the window the field is in, extending up.
.LE
.P
Before static menus will appear, Show_Static_Menu() must be called.
The end-user interaction is the same as for New_Match_Menu().
See also Set_M_Selections(), Def_M_Char(), Free_Match_Menu(), New_Fixed_Menu()
and New_Popup_Menu().
.sp 2
.H 2 Show_Static_Menu
.CW
Show_Static_Menu (field_ptr)
struct field_item	*field_ptr;
.CN
This procedure displays a menu created by New_Static_Menu().
.sp 2
.ne 6
.H 2 Def_M_Char
.CW
Def_M_Char (mult_char)
char	mult_char;
.CN
The menu response field is divided into sections separated by the
multiple selection character, ``mult_char''.
For each response section a separate best match is determined.
The user may type the ``mult_char'' key to end one selection area
and begin another.
The default key is `|'.
See also Set_M_Selections();
.sp 2
.ne 8
.H 2 Set_M_Selections
.CW
Set_M_Selections (field_ptr, max_selections, match_index)
struct field_item	*field_ptr;
int	max_selections;
int	match_index[];
.CN
This procedure sets the maximum number of selections for a menu created with
New_Match_Menu(), New_Static_Menu(), New_Fixed_Menu() or New_Popup_Menu().
The default number of selections is one.
Match areas in the response field are separated by the multiple selection
character (default '|', see Def_M_Char()).
For each match area a separate best match is determined.
When the user tries to make more than ``max_selections'' number of
selections, the leftmost match area in the response field is removed.
For a single selection menu, the multiple selection character has
the same effect as the field erase character.
.P
``match_index'' is an array of integers that upon return will contain
the indexes to the matched items.
It must be declared as having ``max_selections'' plus 1 number of elements.
Upon return
the first element in the array contains the number of selections
the user made.
Subsequent elements contain the indexes to the first, second, etc selections.
Since the contents of the field may not be expanded if the field is not long 
enough,
the ``match_index'' array should be used to identify the responses rather
than the contents of the field.
.P
When using the mouse, items are added by clicking the
leftmost button when the pointer is over the item in the menu.
Clicking the same button over a previously selected item will end selection.
.sp 2
.ne 7
.H 2 Set_M_Delay
.CW
Set_M_Delay (field_ptr, delay)
struct field_item	*field_ptr;
int	delay;
.CN
This procedure sets the delay for popup menus created with New_Match_Menu()
and New_Popup_Menu().
``delay'' is the number of seconds the user must wait between keystrokes
before a popup menu will appear.
The menu window will not appear as long as the user hits a key every
``delay'' or fewer seconds.
It is useful to delay the presentation of a menu at least
one second in case the user is just passing through the field in route to
another field.
Otherwise, the menu pops up and disappears every time the user enters
and leaves the field.
A longer delay means experienced users do not have to look at the
menus except when there is a need to.
.sp 2
.H 2 Def_Match_Type
.CW
Def_Match_Type (match_routine)
int	(*match_routine)();
.CN
This routine lets you assign a different match routine for menus created
with New_Match_Menu(),
New_Static_Menu, New_Popup_Menu and New_Fixed_Menu().
The default best match selection routine is included here as an example.
The new ``match_routine'' will be called with the same arguments as the crosscor()
routine.
It is called once for each item in the menu for every character typed by the 
user.
The calling routine expects a score to be returned for each item and it will
make the item with the highest score the matched item.
.CW
/*
 *
 *    cross correlation routine for determining best matches
 *
 *    crosscor (response, item, type)
 *
 *    response - the user's response
 *    item - the word the response will be scored against - list item
 *    type - 0 for menu match, 1 for spelling corrector
 *
 *    This procedure produces correlation scores between two words
 *    (user's response and list item).  It is important that the
 *    user's response is the first argument and the list item is
 *    the second.
 */

#define POINTS    5000

crosscor (response, item, type)
char    *response;  /* user's response */
char    *item;      /* the word the response will be scored  against */
char    type;       /* type = 0 for menu match, 1 for spelling corrector */
{
    register char    *presp;
    register char    *pitem;
    char    *pprev_match;
    int     lens;
    int     lent;
    register int    match_pos;
    register int     score = 0;
    char    item_buf[256];
    register char    *pitem_buf;

    if ((lens = strlen (response)) == 0)
        return (-1);
    if ((lent = strlen (item)) == 0)
        return (-1);

    strcpy (item_buf, item);

    /* if first item matches give it additional weight */
    if (*item_buf == *response)
        score += (2 * POINTS);

    presp = response;
    pprev_match = item + lent;
    while (*presp)
    {
        pitem = item;
        pitem_buf = item_buf;
        while (*pitem)
        {
            if (*presp == *pitem_buf)
            {
                /* make character 0 - can't be matched again */
                *pitem_buf = '\0';

                /* get position of match in item string */
                match_pos = (pitem - item)*100;

                /* increase score */
                score += (POINTS - (match_pos));
                
                /* increase score if previous character also matches */
                if (pitem != item && presp != response)
                    if (*(presp - 1) == *(pitem - 1))
                        score += (POINTS - match_pos);

                /* increase score if next character also matches */
                if ((*(presp + 1) == *(pitem + 1)) && *(presp + 1))
                    score += (POINTS - match_pos);

                /* increase score if this match and prev were 
                 * in left to right order in the item string
                 */    
                if (pitem >= pprev_match)
                    score += (POINTS - match_pos);
                    
                pprev_match = pitem;
                break;
            }
            pitem++;
            pitem_buf++;
        }
        presp++;
        
        /* reduce score if no match for current response character */
        if (*pitem == '\0')
            score -= (2 * POINTS);
    }
    if (type == 1)
	/* spelling match - heavier penalty for missing characters */
        score += (lens - lent) * POINTS;
    else
        score += lens - lent; /* can remove if items are sorted */
    if (score)
        return (score);
    else
        return (-1);
}
.CN
.P
Note the comment on the sixth line from the bottom.
This line can be removed if the menu items are sorted.
Normally, the best match routine gives a small penalty for extra
characters in the item so that the list of items does not have to be
sorted.
The shortest of otherwise equal matching items will have the highest score.
This is appropriate if the list is sorted.
If this line is removed and there is more than one item with the
same highest score, the first item with that score will be picked.
Removing this line will result in a better selection technique provided
that items are sorted.
.sp 2
.ne 8
.H 2 Post_Match_Menu
.CW
Post_Match_Menu (field_ptr, count, index, rc)
struct field_item	*field_ptr;
int	count;
int	index;
int	rc;
.CN
This is the post_action routine required by menus created with 
New_Match_Menu().  It is assigned as the post_action routine in the call
to New_Match_Menu().  If you write a post_action routine, call
Post_Match_Menu() from that routine and assign the post_action routine
after the call to New_Match_Menu().  Post_Match_Menu() resets global menu
variables and copies the index to the first selection from the response
field into field_ptr -> fndfv.  It requires the standard arguments for a
post_action routine and always returns the index to the current field.
