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
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	Create a menu from a keyword field.  New_Menu() creates a menu
 *	that may be used as a static or pop-up menu.  Items are selected
 *	by positioning the cursor with the mouse, function keys, or
 *	control characters.  If a mouse is used selecting the same item
 *	twice signifies a selection.  Otherwise a confirmation key must
 *	be entered to make the selection.
 *
 *	To create a CMREGN field from a New_Menu() call use the following:
 *
 *	fkeys = New_Field (6, 33, CMKEY, "____________", 0, "a few key words");
 *	Set_Label (fkeys, "left", "Selection: ", FANORMAL);
 *	if (New_Menu (fkeys, 19, 20, 8, 40, "hvertizontal", &fregion, &count))
 *	{
 *		f[new] = New_Field (fregion[0] -> window -> _x_pos,
 *				fregion[0] -> window -> _y_pos,
 *				CMREGN, (char *) fregion, (char *) count, 0);
 *		Pop_Window (fregion[0] -> window,
 				f[index] -> window -> _depth - 1);
 *	}
 *
 *	or use the following to create a pop-up style menu:
 *
 *	extern int N_M_pre_pop_up ();
 *
 *	fkeys = New_Field (6, 33, CMKEY, "____________", 0, "a few key words");
 *	Set_Label (fkeys, "left", "Selection: ", FANORMAL);
 *	if (New_Menu (fkeys, 19, 20, 8, 40, "hvertizontal", &fregion, &count))
 *	{
 *		fkeys -> user_pointer = (char *) fregion;
 *		fkeys -> user_mask = count;
 *		Set_Actions (fkeys, N_M_pre_pop_up, 0);
 *	}
 *
 */

#define	BETCOL		2
#define	MORE		"- more -"

New_Menu (field_ptr, xorigin, yorigin, height, width, orient, fregion, field_count)
struct field_item  *field_ptr;
int     xorigin;
int     yorigin;
int     height;
int     width;
char   *orient;
struct field_item ***fregion;
int    *field_count;
{
    extern int  pre_action ();
    extern int  post_action ();
    extern int  more_pre ();
    extern int  more_post ();
    struct SWindow  setup_window;
    struct window  *menu_window;
    struct field_item **field_list;
    struct keys *top_key_list;
    struct keys *end_key_list;

    register struct keys   *key_list;
    register int    index;
    register int    line;

    int     maxlength;
    int     len_str;
    int     maxcols;
    int     nitems;
    int     col;
    int     nmore;
    int     hcount;
    char   *ptr;
    char   *help;
    char   *more;
    char   *ptr_items;
    char    print_items[16];

    F_Ok (field_ptr, "New_Menu");

    help = "Select the current item by pressing the return key.  Selections may also be made by pointing and selecting twice with the mouse.  Use the cursor pad keys or ^N and ^P to move to another field.";

/*
 *	Assume xorigin, yorigin, height, width, orientation (h or v)
 *	are first five keyword entries.
 */
    if (field_ptr -> type == CMKEY)
	key_list = (struct keys *) cm_get_keys (field_ptr, FALSE);
    else
	key_list = (struct keys *) field_ptr -> keywords;

    top_key_list = key_list;
    nitems = 0;
    maxlength = strlen (MORE);

    while (key_list -> kstr)
    {
	if (maxlength < (len_str = strlen (key_list -> kstr)))
	    maxlength = len_str;
	key_list++;
	nitems++;
    }
    col = sprintf (print_items, "[%d items]", nitems);
    if (col > maxlength)
	maxlength = col;

    if (*orient == 'h')
    {
	maxcols = width / (maxlength + BETCOL);
	if (maxcols < 1)
	    maxcols = 1;
    }
    else
	maxcols = 1;

    if (height < 4)			/* For BLITS */
	height = 4;

    if ((maxcols * height) < nitems)
    {
	nmore = nitems / (maxcols * (height - 1));
	more = (char *) malloc (maxlength + MXTRA);
	if (more == 0)
	{
	    Print_Message (stdwindow, FANORMAL,
		    "Cannot allocate field space.");
	    return (FALSE);
	}
	line = (maxlength - strlen (MORE)) / 2;
	_inlay (more, maxlength, MORE, line);
    }
    else
	nmore = 0;

    line = nitems / maxcols;
    if ((line * maxcols) < nitems)
	line++;
    if (height > line)
	height = line;

    if (height < 4)
	height = 4;

    width = maxcols * (maxlength + BETCOL);

 /* 
  * 	Create the menu window
  */
    setup_window.top_x = xorigin;
    setup_window.top_y = yorigin;
    setup_window.lines = height + 1;
    setup_window.cols = width;
    setup_window.type_scroll = TRUE;
    setup_window.depth = INVISIBLE;
    setup_window.box_h = '-';
    setup_window.box_v = '|';
    setup_window.box_attribute = FANORMAL;
    menu_window = New_Window (setup_window);

 /* 
  * 	Create the selection fields
  */
    ptr_items = (char *) malloc (width + MXTRA);
    if (ptr_items == 0)
    {
	Print_Message (stdwindow, FANORMAL,
		"Cannot allocate field space.");
	return (FALSE);
    }
    line = (width - col) / 2;
    _inlay (ptr_items, width - 1, print_items, line);

    field_list = (struct field_item **) malloc ((sizeof (struct field_item *) + MXTRA) * (nitems + nmore));

    if (field_list == 0)
    {
	Print_Message (stdwindow, FANORMAL, "Cannot allocate field space.");
	return (FALSE);
    }

    key_list = top_key_list;

    if (*orient == 'v')
    {
	col = BETCOL / 2;
	line = 0;
	index = 0;
	hcount = 0;
	while (key_list -> kstr)
	{
	    ptr = (char *) malloc (maxlength + MXTRA);
	    if (ptr == 0)
	    {
		Print_Message (stdwindow, FANORMAL, "Cannot allocate field space.");
		return (FALSE);
	    }

	    width = (maxlength - strlen (key_list -> kstr)) / 2;
	    _inlay (ptr, maxlength, key_list -> kstr, width);
	    field_list[index] = New_Field (line, col, CMCFM, ptr, help, 0);
	    field_list[index] -> window = menu_window;
					/* meswin == stdwindow */
	    field_list[index] -> user_pointer = (char *) field_ptr;
	    field_list[index] -> user_mask = (int) ptr_items;
	    Set_Actions (field_list[index], pre_action, post_action);
	    Set_Tab_Movement (field_list[index], TRUE, FALSE, TRUE, FALSE, FALSE);
	    key_list++;
	    index++;
	    line++;
	    if (line == height)
		line += 512;

	    hcount++;
	    if ((key_list -> kstr) && (hcount == (height - 1)))
	    {
		field_list[index] = New_Field (line, col, CMCFM, more, help, 0);
		field_list[index] -> window = menu_window;
					/* meswin == stdwindow */
		field_list[index] -> user_mask = (int) ptr_items;
		Set_Actions (field_list[index], more_pre, more_post);
		Set_Tab_Movement (field_list[index], TRUE, FALSE, TRUE, FALSE, FALSE);
		index++;
		line++;
		if (line == height)
		    line += 512;
		hcount = 1;
	    }
	}
    }
    else
    {
	line = 0;
	index = 0;
	hcount = 0;
	while (key_list -> kstr)
	{
	    end_key_list = key_list + maxcols;
	    if (hcount == (height - 1))
		end_key_list--;
	    if (end_key_list > (top_key_list + nitems))
	    {
		end_key_list = (top_key_list + nitems);
	    }
	    col = BETCOL / 2;
	    while (key_list < end_key_list)
	    {
		ptr = (char *) malloc (strlen (key_list -> kstr) + 1 + MXTRA);
		if (ptr == 0)
		{
		    Print_Message (stdwindow, FANORMAL, "Cannot allocate field space.");
		    return (FALSE);
		}
		width = (maxlength - strlen (key_list -> kstr)) / 2;
		_inlay (ptr, maxlength, key_list -> kstr, width);
		field_list[index] = New_Field (line, col, CMCFM, ptr, help, 0);
		field_list[index] -> window = menu_window;
					/* meswin == stdwindow */
		field_list[index] -> user_pointer = (char *) field_ptr;
		field_list[index] -> user_mask = (int) ptr_items;
		Set_Actions (field_list[index], pre_action, post_action);
		Set_Tab_Movement (field_list[index], TRUE, FALSE, TRUE, FALSE, FALSE);
		key_list++;
		index++;
		col += maxlength + BETCOL;
	    }
	    if ((key_list -> kstr) && (hcount == (height - 1)))
	    {
		field_list[index] = New_Field (line, col, CMCFM, more, help, 0);
		field_list[index] -> window = menu_window;
					/* meswin == stdwindow */
		field_list[index] -> user_mask = (int) ptr_items;
		Set_Actions (field_list[index], more_pre, more_post);
		Set_Tab_Movement (field_list[index], TRUE, FALSE, TRUE, FALSE, FALSE);
		index++;
		hcount = 0;
	    }
	    hcount++;
	    line++;
	    if (line == height)
		line += 512;
	}
    }

    *field_count = index;
    *fregion = field_list;
    return (TRUE);
}

static int  last_mouse = -1;

static int
pre_action (f, count, index, rc)
register struct field_item **f;
register int    count;
register int    index;
int     rc;
{
    Print_Form (f[index] -> window, f[index] -> window -> _bot_x - f[index] -> window -> _top_x - 1, 0, FANORMAL, f[index] -> user_mask);

    f[index] -> attribute |= FAREVV;

    if (rc == CMMOUSE)
    {
	if (last_mouse == index)
	{
	    f[index] -> attribute &= ~FAREVV;
	    do_set_field (f, index);
	    return (count);
	}
	last_mouse = index;
    }
    else
	last_mouse = -1;

    return (index);
}

static int
post_action (f, count, index, rc)
register struct field_item **f;
register int    count;
register int    index;
int     rc;
{
    int     x;

    f[index] -> attribute &= ~FAREVV;
    Show_Field (f[index]);

    if (rc == 0)			/* A Real Confirm */
    {
	last_mouse = -1;
	do_set_field (f, index);
	return (count);
    }

    if (rc == CMBOTTOM)
	return (go_to_the_bottom (f, count, index, rc));

    if ((index != 0) && (index != count - 1))
    {
	x = index;			/* Check for the 1st page */
	while (f[x] -> x_pos == f[index] -> x_pos)
	{
	    x--;
	    if (x <= 0)
		return (index);
	}
	x = index;			/* Check for the last page */
	while (f[x] -> x_pos == f[index] -> x_pos)
	{
	    x++;
	    if (x >= count)
		return (index);
	}
	x = f[index] -> window -> _bot_x - f[index] -> window -> _top_x - 2;
	if (count <= x)
	    return (index);
	if ((f[index] -> x_pos != 0) && (f[index] -> x_pos != x))
	    return (index);
	if (f[index] -> x_pos == 0)
	{
	    switch (rc)
	    {
		case CMUP: 
		    more_post (f, count, index, rc);
		    break;
		case CMLEFT: 
		case CMBTAB: 
		    if (f[index - 1] -> x_pos != f[index] -> x_pos)
			more_post (f, count, index, rc);
		    break;
	    }
	}
	else
	{
	    if (rc == CMDOWN)
		more_post (f, count, index, rc);
	}
    }
    return (index);
}

static int
do_set_field (f, index)
struct field_item **f;
int     index;
{
    register char  *ptr1;
    register char  *ptr2;

    ptr1 = f[index] -> fill_char;
    while (*ptr1 == ' ')
	ptr1++;
    ptr2 = &ptr1[strlen (ptr1) - 1];
    while (*ptr2 == ' ')
	ptr2--;
    ptr2++;
    if (*ptr2 == ' ')
    {
	*ptr2 = '\0';
	Show_Default_Field (f[index] -> user_pointer, ptr1);
	*ptr2 = ' ';
    }
    else
	Show_Default_Field (f[index] -> user_pointer, ptr1);
}

static int
more_pre (f, count, index, rc)
register struct field_item **f;
register int    count;
register int    index;
int     rc;
{
    Print_Form (f[index] -> window, f[index] -> window -> _bot_x - f[index] -> window -> _top_x - 1, 0, FANORMAL, f[index] -> user_mask);

    f[index] -> attribute |= FAREVV;

    if (rc == CMMOUSE)
    {
	if (last_mouse == index)
	{
	    last_mouse = -1;		/* Mouse Movement Flag Off */
	    return (more_post (f, count, index, 0));
	}
	last_mouse = index;
    }
    else
	last_mouse = -1;

    return (index);
}

static int
more_post (f, count, index, rc)
register struct field_item **f;
register int    count;
register int    index;
int     rc;
{
    int     x;

    f[index] -> attribute &= ~FAREVV;
    Show_Field (f[index]);

    if (rc == CMBOTTOM)
	return (go_to_the_bottom (f, count, index, rc));

    x = f[index] -> window -> _bot_x - f[index] -> window -> _top_x - 2;
    if (f[index] -> x_pos == 0)
    {
	switch (rc)
	{
	    case 0: 
	    case CMUP: 
	    case CMLEFT: 
	    case CMBTAB: 
		slide_region (f, count, x);
		index = -1;
		break;
	}
    }
    else
    {
	switch (rc)
	{
	    case 0: 
	    case CMDOWN: 
	    case CMRIGHT: 
	    case CMFTAB: 
		if (x == f[index] -> x_pos)
		    slide_region (f, count, -x);
		index = -1;
		break;
	}
    }

    return (index);
}

static int
go_to_the_bottom (f, count, index, rc)
register struct field_item **f;
register int    count;
register int    index;
int     rc;
{
    int     x;
    int     y;
    int     per_line;

    x = f[index] -> window -> _bot_x - f[index] -> window -> _top_x - 2;

    per_line = 1;
    while (f[0] -> x_pos == f[per_line] -> x_pos)
	per_line++;

    if ((count / per_line) <= x)
	return (count - 1);

    if ((y = f[count - 1] -> x_pos) < 512)
	return (count - 1);

    y = (y - 512) / x;

    if (y > 0)
    {
	y *= x;
	slide_region (f, count, -y);
    }

    return (count - 1);
}

static int
_inlay (string, length, sub_string, start)
char   *string;
int     length;
char   *sub_string;
int     start;
{
    register int    i;
    register char  *ptr;

    for (i = 0, ptr = string; i < length; i++)
	*ptr++ = ' ';
    *ptr = '\0';
    for (ptr = &string[start]; *sub_string;)
	*ptr++ = *sub_string++;
}

Free_Menu (fregion, count)
register struct field_item **fregion;
register int count;
{
	register int index;
	struct window *Winner;

	Winner = fregion[0] -> window;

	for (index = 0; index < count; index++)
	{
		if (fregion[index] -> fill_char)
		{
			free (fregion[index] -> fill_char);
			fregion[index] -> fill_char = 0;
		}
	}
	for (index = 0; index < count; index++)
	{
		Free_Field (fregion[index]);
	}
	Free_Window (Winner);
}

N_M_pre_pop_up (f, count, index, rc)
struct field_item **f;
int     count;
int     index;
int     rc;
{
    register struct field_item **fregion;
    register int    i;
    register int    line;
    int     x;
    int     total;

    if ((fregion = (struct field_item **) f[index] -> user_pointer) == 0)
	                                    return (index);

    if ((total = f[index] -> user_mask) < 1)
	return (index);

    Show_List (fregion, total);
    Pop_Window (fregion[0] -> window, f[index] -> window -> _depth - 1);
    Get_List (fregion, total, FALSE, FALSE);
    Push_Window (fregion[0] -> window);

    if (f[index] -> post_action)
	(*f[index] -> post_action) (f, count, index, rc);

    return (index + 1);
}
