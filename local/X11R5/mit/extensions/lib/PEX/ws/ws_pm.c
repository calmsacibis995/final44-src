/* $XConsortium: ws_pm.c,v 5.3 91/05/12 20:08:03 rws Exp $ */

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

/* PEX/PHIGS workstation utility functions for the A model (server side
 * workstations and structure storage).
 */

#include "phg.h"
#include "cp.h"
#include "ws.h"
#include <X11/Shell.h>
#include <X11/Xaw/Box.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Command.h>


static void
done_button( w, client_data, call_data )
    Widget      w;
    XtPointer   client_data;
    XtPointer   call_data;
{
    Ws          *ws = (Ws *)client_data;

    XtPopdown( ws->msg_shell );
}

static void
create_message_win( ws )
    Ws		*ws;
{
    Widget      box, button;

    /* Create the containing shell. */
    ws->msg_shell = XtVaCreatePopupShell( "message",
	applicationShellWidgetClass, ws->shell, NULL );

    /* Create the containing box. */
    box = XtVaCreateManagedWidget( "box", boxWidgetClass, ws->msg_shell,
	NULL );

    /* Create the done button. */
    button = XtVaCreateManagedWidget( "button", commandWidgetClass, box,
	NULL );
    XtAddCallback( button, XtNcallback, done_button, (XtPointer)ws );
 
    /* Create the label. */
    ws->msg_label = XtVaCreateManagedWidget( "label", labelWidgetClass, box,
	NULL );
}

static void
message( ws, args )
    Ws			*ws;
    Phg_args_message	*args;
{
    if ( !ws->msg_shell )
	create_message_win( ws );

    if ( args->msg_length > 0 ) {
	/* The unmanage and manage is to get the parent box to allow the
	 * label resize.
	 */
	XtUnmanageChild( ws->msg_label );
	XtVaSetValues( ws->msg_label, XtNlabel, (XtArgVal)args->msg, NULL );
	XtManageChild( ws->msg_label );
	XtPopup( ws->msg_shell, XtGrabNone );
    }
}

void
phg_wsx_pm_create_message_win( ws )
    Ws		*ws;
{
    /* Don't really create it yet, wait until it's used. */
    ws->message = message;
}
