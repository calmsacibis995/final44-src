
/* $XConsortium: toolkit.c,v 5.1 91/02/16 09:59:37 rws Exp $ */

/*****************************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * toolkit.c  -- implements the toolkit-independent interface used
 * by the comparison tool.  This implementation uses XView.
 *
 * This interface is intended to isolate toolkit-dependent details
 * such as button creation and event handling into one place.
 * It is designed with knowledge only of XView and Xlib --
 * the interface should be sufficient to allow an implementation
 * in raw XLib, and it is hoped that implementation using
 * other toolkits would be reasonably straightforward.
 *
 * Note that this interface was designed with the specific purpose
 * of making a particular application - the comparison tool - as
 * portable as possible.  It is not meant to be a general toolkit interface
 * (that's what toolkits are for in the first place!).
 *
 * For all height, width, row, or column arguments, supplying a value
 * of -1 directs the function to use default or toolkit-determined
 * values.
 *
 * The application defines notification procedures as having no
 * arguments since we can't be sure all toolkits will call them
 * with the same arguments. Unfortunately, this forces greater use
 * of globals...
 */

#include <stdio.h>
#include "toolkit.h"

/*
 * tk_init(argc,argv) - initialize the toolkit.  The toolkit may
 * look for toolkit-specific arguments in the command-line input.
 */
void
tk_init(argc,argv)
int argc;
char *argv[];
{
    xv_init(XV_INIT_ARGS, argc, argv,
	0);
}
/*
 * TK_Main_Window
 * tk_create_main_window(label,height,width)
 *  Create a main application window with given label, height, and width.
 */
TK_Main_Window 
tk_create_main_window(label,height,width, display_return)
    char *label; 
    int height,width;
    Display **display_return;
{
    Frame frame;

    frame = xv_create(NULL,FRAME,
		FRAME_LABEL,	label,
		0);
    if (frame==NULL) fatal("tk_create_main_window: frame creation failed\n");
    if (height != -1) xv_set(frame, XV_HEIGHT, height,0);
    if (width != -1) xv_set(frame, XV_WIDTH, width,0);
    *display_return = (Display *)xv_get(frame, XV_DISPLAY);
    return(frame);

}


/*
 * TK_Control_Window
 * tk_create_control_window(parent,x, y, height,width)
 * Create a subwindow suitable for buttons, etc. that is a child of
 * the given parent.  A -1 for any of x, y, height or width 
 * yields the default or toolkit-determined value.
 */
TK_Control_Window
tk_create_control_window(parent,x,y,height,width)
    TK_Main_Window parent;
    int x,y,height,width;
{
    Panel panel;

    panel = xv_create(parent,PANEL,
		0);
    if (panel == NULL) fatal("tk_create_control_window: panel creation failed\n");
    if (x != -1) xv_set(panel, XV_X, x, 0);
    if (y != -1) xv_set(panel, XV_Y, y, 0);
    if (height != -1) xv_set(panel, XV_HEIGHT, height,0);
    if (width != -1) xv_set(panel, XV_WIDTH, width,0);
    return (panel);
}


/*
 * Drawable
 * tk_create_X_drawable_window(parent,height,width,
 *			repaint_proc,display_return);
 * Create an X window as a subwindow of the supplied parent window,
 * returning its id.  *display_return is set to the current default display. 
 */
Drawable
tk_create_X_drawable_window(parent,height,width,
			repaint_proc,display_return)
    TK_Main_Window parent;
    int height,width,(*repaint_proc)();
    Display **display_return;
{
    Canvas canvas;
    Pixwin *pixwin;
    Drawable drawable;

    canvas = xv_create(parent,CANVAS,
		CANVAS_X_PAINT_WINDOW, TRUE,
		CANVAS_REPAINT_PROC, repaint_proc,
		0);
    if (canvas == NULL) fatal("tk_create_X_drawable_window: win creation failed\n");
    if (height != -1) xv_set(canvas, XV_HEIGHT, height,0);
    if (width != -1) xv_set(canvas, XV_WIDTH, width,0);

    pixwin = canvas_pixwin(canvas);
    *display_return = (Display *)xv_get(pixwin, XV_DISPLAY);
    drawable = (Drawable)xv_get(pixwin, XV_XID);
    return(drawable);
    
}

XID
tk_get_xid(window)
    Frame window;
{
    return (XID) xv_get(window, XV_XID);
}

/*
 * tk_create_button(control_win,row, col,label,proc,active_status)
 * create a button in the given control window, at designated row & col.
 * proc identifies a procedure to be called when the button is pressed.
 */
TK_Button
tk_create_button(control_win,row,col,label,proc,active_status)
    TK_Control_Window control_win;
    int row, col;
    char *label;
    int (*proc)();
    int active_status;
{
    Panel_item button_item;

    button_item = xv_create(control_win,PANEL_BUTTON,
		PANEL_LABEL_STRING,	label,
		PANEL_NOTIFY_PROC,	proc,
		PANEL_INACTIVE,		active_status,
		0);
    if (button_item == NULL) fatal("tk_create_button: creation failed\n");
    if (row != -1) xv_set(button_item, PANEL_ITEM_Y, xv_rows(control_win,row),0);
    if (col != -1) xv_set(button_item, PANEL_ITEM_X, xv_cols(control_win,col),0);
    return (button_item);
}

/*
 * tk_activate_button(button) - sets the active status of the button
 * to TK_BUTTON_ACTIVE
 */
void
tk_activate_button(button)
    TK_Button button;
{
    xv_set(button, PANEL_INACTIVE, TK_BUTTON_ACTIVE, 0);
}
/*
 * tk_deactivate_button(button) - sets the active status of the button
 * to TK_BUTTON_INACTIVE
 */
void
tk_deactivate_button(button)
    TK_Button button;
{
    xv_set(button, PANEL_INACTIVE, TK_BUTTON_INACTIVE, 0);
}

/*
 * tk_set_button_label(button,label) - sets the button label to
 * the label given.
 */
void
tk_set_button_label(button,label)
    TK_Button button;
    char *label;
{
    xv_set(button, PANEL_LABEL_STRING, label, 0);
}

/*
 * TK_Message_Item
 * tk_create_message(control_win,row, col,init_string)
 * create a text output item  in the given control window, 
 * at designated row & col, with the initial contents init_string.
 */
TK_Message_Item
tk_create_message_item(control_win,row,col,init_string)
    TK_Control_Window control_win;
    int row, col;
    char *init_string;
{
    Panel_item message_item;

    message_item = xv_create(control_win,PANEL_MESSAGE,
		PANEL_LABEL_STRING,	init_string,
		0);
    if (message_item == NULL) fatal("tk_create_message_item: creation failed\n");
    if (row != -1) xv_set(message_item, PANEL_ITEM_Y, xv_rows(control_win,row),0);
    if (col != -1) xv_set(message_item, PANEL_ITEM_X, xv_cols(control_win,col),0);
    return(message_item);
}

/*
 * tk_set_message(msg_item, text) - sets the text tring displayed
 * in msg_item to "text".
 */
void
tk_set_message(msg_item, text)
    TK_Message_Item msg_item;
    char *text;
{
    xv_set(msg_item,
	PANEL_LABEL_STRING,	text,
	0);
}


/* 
 * TK_List
 * tk_create_list(control_win,row,col,notify_proc)
 */
TK_List
tk_create_list(control_win,row,col,notify_proc)
    TK_Control_Window control_win;
    int row,col, (*notify_proc)();
{
    Panel_item list_item;

    list_item = xv_create(control_win, PANEL_LIST,
		PANEL_NOTIFY_PROC,	notify_proc,
		PANEL_LIST_DISPLAY_ROWS, 5,
		0);
    if (list_item == NULL) fatal("tk_create_list: creation failed\n");
    if (row != -1) xv_set(list_item, PANEL_ITEM_Y, xv_rows(control_win,row),0);
    if (col != -1) xv_set(list_item, PANEL_ITEM_X, xv_cols(control_win,col),0);
    return ((TK_List)list_item);
}


/*
 * char *
 * tk_get_selected_item(list,index_return) - return a pointer to the
 * string of the currently selected list item, and set index_return
 * to that element's index.  If no list item is selected, return NULL.
 */
char *
tk_get_selected_list_item(list,index_return)
    TK_List list;
    int *index_return;
{
    char *string;
    int i, nrows;
    int sel=0;

    nrows = (int)xv_get(list, PANEL_LIST_NROWS);
    for (i=0; 
	i<nrows,!(sel=(int)xv_get(list,PANEL_LIST_SELECTED,i));  i++);
    if (sel) {
	*index_return = i;
	return ((char *)xv_get(list,PANEL_LIST_STRING,i));
    } else {
	return (NULL);
    }
	
}

/*
 * char *
 * tk_get_list_item(list,index) - return a pointer to the string of
 * of the list item specified by index.
 */
char *
tk_get_list_item(list,index)
    TK_List list;
    int index;
{
    return ((char*)xv_get(list, PANEL_LIST_STRING, index));
}

/*
 * int
 * tk_get_list_length(list) - return the number of rows in the list
 */
int
tk_get_list_length(list)
    TK_List list;
{
    return ((int)xv_get(list, PANEL_LIST_NROWS));
}

/*
 * tk_set_list_item(list,index,string): set the indexed list item to
 * have value "string".  Note that this function is only for changing
 * the value; tk_insert_list_item should be used to create the item.
 */
void
tk_set_list_item(list,index,string)
    TK_List list;
    int index;
    char *string;
{
    xv_set(list, PANEL_LIST_STRING,index,string,
	    0);
}

void
tk_insert_list_item(list,index,string)
    TK_List list;
    int index;
    char *string;
{
    xv_set(list, PANEL_LIST_INSERT,index,
	    0);
    xv_set(list, PANEL_LIST_STRING,index,string,
	    0);
}

/*
 * tk_delete_list_item: delete the list item indexed by index; if there
 * is an item after it, make that the selected item.
 */
void
tk_delete_list_item(list,index)
    TK_List list;
    int index;
{
    xv_set(list, PANEL_LIST_DELETE,index,
	    0);
    if ((int)xv_get(list,PANEL_LIST_NROWS) > index) {
	xv_set(list, PANEL_LIST_SELECT, index, TRUE,
	    0);
    } 
}

/*
 * tk_main_loop() - start the main event-handling loop
 */
void
tk_main_loop(main_win)
    TK_Main_Window main_win;
{
    xv_main_loop(main_win);
}

static
fatal(s)
    char *s;
{
    fprintf(stderr, "%s\n");
    exit(1);
}
