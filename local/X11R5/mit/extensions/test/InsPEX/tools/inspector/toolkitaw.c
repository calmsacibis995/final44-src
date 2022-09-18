/* $XConsortium: toolkitaw.c,v 5.8 91/05/30 19:07:37 converse Exp $ */

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
 * toolkitaw.c  -- implements the toolkit-independent interface used
 * by the comparison tool.  This implementation uses Athena Widgets
 *
 * See top comment of toolkit.c for comments on the design
 * of this interface.
 * For all height, width, row, or column arguments, supplying a value
 * of -1 directs the function to use default or toolkit-determined
 * values.
 *
 */

#include "toolkitaw.h"		/* includes Intrinsic.h */
#include <X11/StringDefs.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/List.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Viewport.h>
#include <X11/Xaw/Paned.h>
#include <stdio.h>		/* for fatal error message routine */

/* copied from inspector.c */	/* broken interface */
#define IMAGE_SIZE 400
#define IMAGE_WIDTH IMAGE_SIZE
#define IMAGE_HEIGHT IMAGE_SIZE
#define CONTROL_WIDTH 160
#define IMAGE_LABEL_HEIGHT 30

static Widget toplevel;
static XtAppContext appContext;

/* For keeping track of control widget layout.  We make an assumption that
 * widgets in a control window are created in order, using the column
 * argument to determine whether it goes on the same row as the last one.
 */
static Widget lastwidget=NULL;  	/* last one created */
static Widget lastleftwidget=NULL; 	/* last one beginning a row */
static Widget widgetAbove = NULL;	/* first one in the previous row */
static Widget parentWidget = NULL;	/* parent of last one created */
static Widget messagebar = NULL;	/* "reflabel_win" widget */
static Widget pexbar = NULL;

/* Assume one list, items indexed beginning at 0, and monotonically added. */
static String *list = NULL;
static int listCount = 0;
static Cardinal listSize = 0;


/* Initialize the toolkit.  The toolkit may look for toolkit-specific 
 * arguments in the command line.
 */
void tk_init(argc, argv)
    int argc;
    char *argv[];
{
    /* 
     * Easier to create the toplevel shell widget now,
     * and keep it around for the tk_create_main_window call.
     * result kept in the static variable toplevel.
     */
    toplevel = XtAppInitialize(&appContext, "Inspector", NULL, 0,
			       &argc, argv, NULL, NULL, 0);
}


/* Create a main application widget with given label, height, and width,
 * Returning the display in display_return and widet as the return value.
 */
TK_Main_Window tk_create_main_window(label, height, width, display_return)
    char *label; 
    int height,width;
    Display **display_return;
{
    Arg args[5];
    Cardinal n = 0;
    Widget paned;

    /* toplevel already created by tk_init: create a paned child */
    if (height != -1) {
	XtSetArg(args[n], XtNheight, height);	n++;
    }
    if (width != -1) {
	XtSetArg(args[n], XtNwidth, width);	n++;
    }
    paned = XtCreateManagedWidget("main", panedWidgetClass, toplevel, args, n);

    /* create the first pane, containing graphics and controls */
    n = 0;
    XtSetArg(args[n], XtNshowGrip, False);			n++;
    pexbar = XtCreateManagedWidget("pexbar", panedWidgetClass, paned, args, n);

    /* create the second pane, containing the title bar */
    n = 0;
    XtSetArg(args[n], XtNshowGrip, False);	n++;
    XtSetArg(args[n], XtNlabel, label);		n++;
    (void) XtCreateManagedWidget("titlebar", labelWidgetClass, paned, args, n);

    *display_return = XtDisplay(toplevel);
    return paned;
}


/* Create a subwindow suitable for buttons, as a child of the given parent.
 * A -1 for any of x, y, height or width yields the widget default value.
 */
TK_Control_Window tk_create_control_window(parent, x, y, height, width)
    TK_Main_Window parent;
    int x, y, height, width;
{
    Widget control_win;
    Cardinal n = 0;
    Arg args[15];
    static int pass = 0;	/* sickness and evil */

    if (! pass) {	/* dependent upon order of caller */

	/* create the third pane, containing the messages */
	n = 0;
	XtSetArg(args[n], XtNshowGrip, False);			n++;
	XtSetArg(args[n], XtNorientation, XtorientHorizontal);	n++;
	if (height != -1) {
	    XtSetArg(args[n], XtNheight, height);		n++;
	}
	if (width != -1) {
	    XtSetArg(args[n], XtNwidth, width);			n++;
	}
	if (x != -1) {
	    XtSetArg(args[n], XtNx, x);				n++;
	}
	if (y != -1) {
	    XtSetArg(args[n], XtNy, y);				n++;
	}
	/* create child of third pane */
	messagebar = XtCreateManagedWidget("messagebar", panedWidgetClass,
					   parent, args, n);
	control_win = messagebar;
	pass++;

    } else {			/* control panel at right */
	Widget pexpane, graphicspane, controlpane, controlform;

	/* create a paned child of graphics pane */
	n = 0;
	XtSetArg(args[n], XtNshowGrip, False);			n++;
	XtSetArg(args[n], XtNorientation, XtorientHorizontal);	n++;
	pexpane = XtCreateManagedWidget("pexpane", panedWidgetClass, pexbar,
					args, n);
	/* create the graphics container */
	n = 0;
	XtSetArg(args[n], XtNshowGrip, False);			n++;
	XtSetArg(args[n], XtNwidth, IMAGE_WIDTH * 2);		n++;
	XtSetArg(args[n], XtNheight, IMAGE_HEIGHT);		n++;
	graphicspane = XtCreateManagedWidget("graphicspane", panedWidgetClass,
					     pexpane, args, n);
	/* create the control panel container */
	n = 0;
	XtSetArg(args[n], XtNshowGrip, False);			n++;
	XtSetArg(args[n], XtNwidth, CONTROL_WIDTH);		n++;
	XtSetArg(args[n], XtNheight, IMAGE_HEIGHT);		n++;
	controlpane = XtCreateManagedWidget("controlpane", panedWidgetClass,
					    pexpane, args, n);
	/* create the control form, the parent of the control buttons */
	n = 0;
	XtSetArg(args[n], XtNshowGrip, False);			n++;
	controlform = XtCreateManagedWidget("controlform", formWidgetClass,
					    controlpane, args, n);
	control_win = controlform;
    }
    return control_win;
}


XID tk_get_xid(window)
    TK_Main_Window window;
{
    XtRealizeWidget(toplevel);
    return (XID) XtWindow(window);
}


static void SetConstraints(parent, row, col, args, num_args)
    Widget	parent;
    int		row, col;
    Arg		*args;		/* in out */
    Cardinal	*num_args;	/* in out */
{
    Cardinal n = *num_args;

    if (parentWidget && parent != parentWidget) {
	lastwidget = NULL;
	lastleftwidget = NULL;
	widgetAbove = NULL;
    }

    /* Set up geometry constraints for Form widget parent */
    if (col == 1) {
	/* widget is in new row */
	XtSetArg(args[n], XtNfromVert, lastleftwidget);	n++;
    } else {
	/* widget is in same row as last widget */
	XtSetArg(args[n], XtNfromHoriz, lastwidget);	n++;
	XtSetArg(args[n], XtNfromVert, widgetAbove);	n++;
    }
    *num_args = n;
}

static void UpdateConstraints(parent, child, col)
    Widget parent;
    Widget child;
    int col;
{
    parentWidget = parent;
    lastwidget = child;
    if (col == 1) {
	widgetAbove = lastleftwidget;
	lastleftwidget = child;
    }
}   


/* Create a button in the given control window, at designated row & col.
 * proc identifies a procedure to be called when the button is pressed.
 */
TK_Button tk_create_button(parent, row, col, label, proc, active_status)
    TK_Control_Window parent;
    int row, col;
    char *label;	/* may have white space in it */
    void (*proc)();
    int active_status;
{
    Cardinal n=0;
    Widget button;
    Arg args[10];

    SetConstraints(parent, row, col, args, &n);
    XtSetArg(args[n], XtNresizable, False);		n++;
    XtSetArg(args[n], XtNlabel, label);			n++;
    if (active_status != TK_BUTTON_ACTIVE) {
	XtSetArg(args[n], XtNsensitive, False);		n++;
    }
    button = XtCreateManagedWidget("button", commandWidgetClass, parent,
				   args, n);
    if (proc) XtAddCallback(button, XtNcallback, proc, (XtPointer) NULL);
    UpdateConstraints(parent, button, col);
    return button;
}


/* Create a text output item in the given control window, 
 * at designated row & col, with the initial contents init_string.
 */
TK_Message_Item tk_create_message_item(parent, row, col, label)
    TK_Control_Window parent;
    int row, col;
    char *label;
{
    Widget message;
    Cardinal n=0;
    Arg args[10];

    if (parent == messagebar) {
	XtSetArg(args[n], XtNshowGrip, False);		n++;
	XtSetArg(args[n], XtNallowResize, True);	n++;
    }
    else {
	SetConstraints(parent, row, col, args, &n);
        XtSetArg(args[n], XtNresizable, True);		n++;
    }
    XtSetArg(args[n], XtNlabel, label);			n++;
    message = XtCreateManagedWidget("message", labelWidgetClass, parent,
				    args, n);
    if (parent != messagebar)
	UpdateConstraints(parent, message, col);
    return message;
}


/* Set the active status of the button to be active */
void tk_activate_button(button)
    TK_Button button;
{
    XtSetSensitive(button, TRUE);
}


/* Set the active status of the button to be inactive */
void tk_deactivate_button(button)
    TK_Button button;
{
    XtSetSensitive(button, FALSE);
}


/* Set the button label */
void tk_set_button_label(button,label)
    TK_Button button;
    char *label;
{
    Arg arg[1];
    XtSetArg(arg[0], XtNlabel, label);
    XtSetValues(button, arg, (Cardinal) 1);
}


/* Set the text displayed in msg_item to "text" */
void tk_set_message(msg_item, text)
    TK_Message_Item msg_item;
    char *text;
{
    XtVaSetValues(msg_item,
		  XtNlabel, text,
		  NULL);
}


TK_List tk_create_list(parent, row, col, notify_proc)
    TK_Control_Window parent;
    int row, col;
    int (*notify_proc)();
{
    Widget viewport, list;
    Cardinal n=0;
    Arg args[10];

    /* Set up geometry constraints for Form widget parent of viewport */
    SetConstraints(parent, row, col, args, &n);
    XtSetArg(args[n], XtNheight,  120);			n++;
    XtSetArg(args[n], XtNallowVert, True);		n++;
    XtSetArg(args[n], XtNuseRight, True);		n++;
    viewport = XtCreateManagedWidget("viewport", viewportWidgetClass,
				     parent, args, n);

    n=0;
    XtSetArg(args[n], XtNverticalList,  True);		n++;
    XtSetArg(args[n], XtNdefaultColumns, 1);		n++;
    XtSetArg(args[n], XtNforceColumns,  True);		n++;
    list = XtCreateManagedWidget("list", listWidgetClass, viewport, args, n);
    if (notify_proc) 
	XtAddCallback(list, XtNcallback, notify_proc, (XtPointer) NULL);
    UpdateConstraints(parent, viewport, col);
    return list;
}


/* Return a pointer to the string of the currently selected list item, 
 * and set index_return to that element's index.  If no list item is 
 * selected, return NULL.
 */
char * tk_get_selected_list_item(w, index_return)
    TK_List w;
    int *index_return;
{
    XawListReturnStruct *selectedItem;

    selectedItem = XawListShowCurrent(w);
    if (selectedItem->list_index == XAW_LIST_NONE)
	return (char *) NULL;
    *index_return = selectedItem->list_index;
    return selectedItem->string;
}


/* Return a pointer to the string of the list item specified by index */
char * tk_get_list_item(w, indx)
    TK_List w;
    int indx;
{
    if (indx >= listCount)
	fatal("toolkitaw: tk_get_list_item: illegal list reference\n");
    return list[indx];
}


/* Return the number of rows in the list */
int tk_get_list_length(w)
    TK_List w;
{
    return listCount;
}


/* Set the indexed list item to have value "string".  
 * Note that this function is only for changing the value; 
 * tk_insert_list_item should be used to create the item.
 */
void tk_set_list_item(w, indx, value)
    TK_List w;
    int indx;
    char *value;
{
    Cardinal n;
    Arg args[3];

    if (indx >= listCount)
	fatal("toolkitaw: tk_set_list_item: illegal insertion\n");

    list[indx] = value;
    n = 0;
    XtSetArg(args[n], XtNnumberStrings, listCount);	n++;
    XtSetArg(args[n], XtNlongest, 0);			n++;
    XtSetArg(args[n], XtNlist, list);			n++;
    XtSetValues(w, args, n);
    printf("tk_set_list_item(list,%d,%s)\n", indx, value);
}


void tk_insert_list_item(w, indx, value)
    TK_List w;
    int indx;
    char *value;
{
    Cardinal n;
    Arg args[3];

    if (indx != listCount)
	fatal("toolkitaw: tk_insert_list: nonmonotonic insertion\n");

    if (listCount >= listSize) {
	listSize += 100;
	list = (String *) XtRealloc((char *)list, listSize * sizeof(String));
    }
    list[listCount++] = value;	/* assume copying is unnecessary */
    n = 0;
    XtSetArg(args[n], XtNnumberStrings, listCount);	n++;
    XtSetArg(args[n], XtNlongest, 0);			n++;
    XtSetArg(args[n], XtNlist, list);			n++;
    XtSetValues(w, args, n);
}


/* Delete the list item indexed by index; if there is an item after it,
 * make that the selected item.
 */
void tk_delete_list_item(w, indx)
    TK_List w;
    int indx;
{
    String * newList;
    Cardinal n;
    Arg args[3];

    if (indx >= listCount) return;
    listCount--;
    newList = (String *) XtMalloc(listSize * sizeof(String));
    if (indx > 0) bcopy(list, newList, indx * sizeof(String));
    if (indx < listCount) bcopy(list[indx+1], newList[indx],
				(listCount - indx) * sizeof(String));
    n = 0;
    XtSetArg(args[n], XtNnumberStrings, listCount);	n++;
    XtSetArg(args[n], XtNlongest, 0);			n++;
    XtSetArg(args[n], XtNlist, newList);		n++;
    XtSetValues(w, args, n);
    XtFree((char *)list);
    list = newList;

    if (indx < listCount) XawListHighlight(w, indx);
}


void tk_main_loop(main_win)
    TK_Main_Window main_win;
{
    XtAppMainLoop(appContext);
}


static fatal(s)	/* bleh */
    char *s;
{
    fprintf(stderr, "%s\n",s);
    exit(1);
}


#if 0 /* never called */
/*
 * Create an X window as a subwindow of the supplied parent window,
 * returning its id.  *display_return is set to the current default display. 
 */
Drawable tk_create_X_drawable_window(parent, height, width,
				     repaint_proc, display_return)
    TK_Main_Window parent;
    int height,width,(*repaint_proc)();
    Display **display_return;
{
    /* create a Core widget and return its Xid */
    Widget core_widget;
    Drawable drawable;
    Cardinal n = 0;
    Arg args[4];

    if (height != -1) {
	XtSetArg(args[n], XtNheight, height); n++;
    }
    if (width != -1) {
	XtSetArg(args[n], XtNwidth, width); n++;
    }
    core_widget = XtCreateManagedWidget("canvas", coreWidgetClass, parent,
					args, n);
    *display_return = XtDisplay(parent);
    XtRealizeWidget(core_widget);
    drawable = XtWindow(core_widget);
    return(drawable);
    
}
#endif /* never called */
