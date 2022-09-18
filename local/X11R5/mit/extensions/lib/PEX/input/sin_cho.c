/* $XConsortium: sin_cho.c,v 5.4 91/05/12 20:07:32 rws Exp $ */

/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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
 * Default device specific routines for input.
 */

#include "phg.h"
#include "ws_type.h"
#include "sin.h"
#include "sin_priv.h"
#include <X11/Shell.h>
#include <X11/Xaw/Viewport.h>
#include <X11/Xaw/List.h>


static void
choice_notify( w, client_data, call_data )
    Widget	w;
    XtPointer	client_data;
    XtPointer	call_data;
{
    XawListReturnStruct		*selection = (XawListReturnStruct*)call_data;
    Sin_input_device		*device = (Sin_input_device *)client_data;
    Sin_choice_device_data	*data = &device->data.choice;

    data->cur_choice = selection->list_index + 1;
    if ( device->mode == SIN_EVENT ) {
	unsigned	status;
	status = phg_sin_ws_enque_events( 1, &device );
	if ( SIN_EVENT_NOT_ENQUED(status) )
	    XBell( XtDisplay(w), 0 );
    }
    /* The action proc takes care of REQUEST.  No additional action needed
     * for SAMPLE.
     */
}

static void
enable_choice( device )
    Sin_input_device	*device;
{
    Widget			w;
    char			buf[256];
    Sin_choice_device_data	*data = &device->data.choice;
    Widget			parent = device->ws->shell;

    /* Most options are not explicitly set so that the user can override
     * them.  Fallbacks are specified instead (elsewhere).
     */

    /* Create the containing shell. */
    sprintf( buf, "choice%d", device->num );
    device->item_handle.choice.shell =
	XtVaCreatePopupShell( buf, applicationShellWidgetClass, parent,
	    NULL );

    /* Create the containing viewport. */
    device->item_handle.choice.viewport =
	XtVaCreateManagedWidget( "viewport", viewportWidgetClass,
	    device->item_handle.choice.shell,
	    NULL );

    /* Create the list. */
    w = device->item_handle.choice.list =
	XtVaCreateManagedWidget( "list", listWidgetClass,
	    device->item_handle.choice.viewport,
	    XtNnumberStrings, (XtArgVal)data->count,
	    XtNlist, (XtArgVal)data->choices.strings,
	    NULL );
    XawListHighlight( device->item_handle.choice.list, data->cur_choice - 1 );
    XtAddCallback( device->item_handle.choice.list,
	XtNcallback, choice_notify, (XtPointer)device );

    XtPopup( device->item_handle.choice.shell, XtGrabNone );
    if ( device->mode == SIN_REQUEST_PENDING )
	XSaveContext( XtDisplay(w), XtWindow(w), phg_sin_device_context_id,
	    (caddr_t)device );
}

static void
disable_choice( device )
    Sin_input_device	*device;
{
    XtDestroyWidget( device->item_handle.choice.shell );
}

void
phg_sin_dev_boot_choice( dev )
    Sin_input_device	*dev;
{
    switch ( dev->data.choice.type ) {
	case WST_CHOICE_TYPE_LIST:
	    dev->dev_ops.reset = NULL;
	    dev->dev_ops.sample = NULL;
	    dev->dev_ops.resize = NULL;
	    dev->dev_ops.repaint = NULL;
	    dev->dev_ops.destroy = NULL;
	    dev->dev_ops.create = NULL;
	    dev->dev_ops.init = NULL;
	    dev->dev_ops.enable = enable_choice;
	    dev->dev_ops.disable = disable_choice;
	    break;
    }
}
