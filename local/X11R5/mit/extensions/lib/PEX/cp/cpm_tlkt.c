/* $XConsortium: cpm_tlkt.c,v 5.2 91/07/24 14:41:48 hersh Exp $ */

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

#include "phg.h"
#include "cp.h"
#include "cp_priv.h"
#include "ws.h"
#include "sin.h"


/* TODO: Fill in the real options. */
static XrmOptionDescRec options[] = {
{"-horiz",	"scrollbar.orientation", XrmoptionNoArg,  "horizontal"}
};

String fallbacks[] = { 
    "*valuator1.pane.orientation:  horizontal",
    "*valuator1*scrollbar.orientation:  horizontal",
    "*valuator1*scrollbar.length:  50",
    "*valuator1*scrollbar.translations: \
          <Btn1Down>:	StartScroll(Continuous) MoveThumb() NotifyThumb() \\n\
	  <Btn1Motion>:	MoveThumb() NotifyThumb() \\n\
	  <Btn1Up>:	NotifyScroll(Proportional) RequestSatisfied() \
			EndScroll() \
	  ",
    "*valuator1*scrollbar.skipAdjust:  FALSE",
    "*valuator1*skipAdjust:  TRUE",
    "*valuator1*showGrip:  FALSE",

    "*valuator2.pane.orientation:  horizontal",
    "*valuator2*scrollbar.orientation:  horizontal",
    "*valuator2*scrollbar.length:  50",
    "*valuator2*scrollbar.translations: \
          <Btn1Down>:	StartScroll(Continuous) MoveThumb() NotifyThumb() \\n\
	  <Btn1Motion>:	MoveThumb() NotifyThumb() \\n\
	  <Btn1Up>:	NotifyScroll(Proportional) RequestSatisfied() \
			EndScroll() \
	  ",
    "*valuator2*scrollbar.skipAdjust:  FALSE",
    "*valuator2*skipAdjust:  TRUE",
    "*valuator2*showGrip:  FALSE",

    "*valuator3.pane.orientation:  horizontal",
    "*valuator3*scrollbar.orientation:  horizontal",
    "*valuator3*scrollbar.length:  50",
    "*valuator3*scrollbar.translations: \
          <Btn1Down>:	StartScroll(Continuous) MoveThumb() NotifyThumb() \\n\
	  <Btn1Motion>:	MoveThumb() NotifyThumb() \\n\
	  <Btn1Up>:	NotifyScroll(Proportional) RequestSatisfied() \
			EndScroll() \
	  ",
    "*valuator3*scrollbar.skipAdjust:  FALSE",
    "*valuator3*skipAdjust:  TRUE",
    "*valuator3*showGrip:  FALSE",

    "*valuator4.pane.orientation:  horizontal",
    "*valuator4*scrollbar.orientation:  horizontal",
    "*valuator4*scrollbar.length:  50",
    "*valuator4*scrollbar.translations: \
          <Btn1Down>:	StartScroll(Continuous) MoveThumb() NotifyThumb() \\n\
	  <Btn1Motion>:	MoveThumb() NotifyThumb() \\n\
	  <Btn1Up>:	NotifyScroll(Proportional) RequestSatisfied() \
			EndScroll() \
	  ",
    "*valuator4*scrollbar.skipAdjust:  FALSE",
    "*valuator4*skipAdjust:  TRUE",
    "*valuator4*showGrip:  FALSE",

    "*valuator5.pane.orientation:  horizontal",
    "*valuator5*scrollbar.orientation:  horizontal",
    "*valuator5*scrollbar.length:  50",
    "*valuator5*scrollbar.translations: \
          <Btn1Down>:	StartScroll(Continuous) MoveThumb() NotifyThumb() \\n\
	  <Btn1Motion>:	MoveThumb() NotifyThumb() \\n\
	  <Btn1Up>:	NotifyScroll(Proportional) RequestSatisfied() \
			EndScroll() \
	  ",
    "*valuator5*scrollbar.skipAdjust:  FALSE",
    "*valuator5*skipAdjust:  TRUE",
    "*valuator5*showGrip:  FALSE",

    "*valuator6.pane.orientation:  horizontal",
    "*valuator6*scrollbar.orientation:  horizontal",
    "*valuator6*scrollbar.length:  50",
    "*valuator6*scrollbar.translations: \
          <Btn1Down>:	StartScroll(Continuous) MoveThumb() NotifyThumb() \\n\
	  <Btn1Motion>:	MoveThumb() NotifyThumb() \\n\
	  <Btn1Up>:	NotifyScroll(Proportional) RequestSatisfied() \
			EndScroll() \
	  ",
    "*valuator6*scrollbar.skipAdjust:  FALSE",
    "*valuator6*skipAdjust:  TRUE",
    "*valuator6*showGrip:  FALSE",

    "*choice1*allowHoriz:  TRUE",
    "*choice1*allowHoriz:  TRUE",
    "*choice1*allowHoriz:  TRUE",
    "*choice1*allowVert:  TRUE",
    "*choice1*list.translations: \
          <Btn1Down>,<Btn1Up>:	Set() Notify() RequestSatisfied() \
	  ",
    "*string1*Text*width: 		400", 
    "*string1*Text*height: 		50", 
    "*string1*Text*editType:          edit",
    "*string1*Text*scrollVertical:    never",
    "*string1*Text*scrollHorizontal:  never",
    "*string1*Text*autoFill:          on",

    "*message.box.orientation:		vertical",
    "*message.box.allowResize:		True",
    "*message*label.resize:		True",
    "*message*button.label:		Done",

    NULL,
};

static XtActionsRec	actions[] = {
    {"RequestSatisfied",	(XtActionProc)phg_sin_xt_request_satisfied},
    {"StringEvent",		(XtActionProc)phg_sin_xt_string_event},
};

XContext        phg_sin_device_context_id;

/* No need for a "destroy_toolkit function since all the resources are
 * destroyed when the PM terminates.
 */

XtAppContext
phg_cpm_init_toolkit( argc, argv )
    int		argc;
    char	**argv;
{
    XtAppContext	app_con;

    XtToolkitInitialize();
    if ( app_con = XtCreateApplicationContext() ) {
	XtAppSetFallbackResources( app_con, fallbacks );
	XtAppAddActions( app_con, actions, XtNumber(actions) );
	phg_sin_device_context_id = XUniqueContext();
    }
    return app_con;
}

Widget
phg_cpm_toolkit_add_connection( cph, display, err )
    Cp_handle	cph;
    Display	*display;
    Pint	*err;
{
    int		argc = 0, status = 0;
    char	**argv = (char **)NULL;
    Widget	top_level;

    /* TODO: XtDisplayInitialize destroys the arg vector, but we need to
     * keep it for the next display initialized.  So copy it to scratch
     * space then pass the copy.
     */
    XtDisplayInitialize( cph->data.monitor.app_con, display,
	cph->data.monitor.name, cph->data.monitor.classname, NULL, 0,
	&argc, argv );
    if ( top_level = XtVaAppCreateShell( cph->data.monitor.name,
	    cph->data.monitor.classname, applicationShellWidgetClass,
	    display, NULL ) )
	status = 1;
    else
	*err = ERRN204;

    return top_level;
}

int
phg_cpm_toolkit_open_ws( ws )
    Ws		*ws;
{
    char	buf[100];
    int		status = 0;

    sprintf( buf, "workstation%d", ws->id );
    if ( ws->shell = XtVaCreatePopupShell( buf, applicationShellWidgetClass,
	    ws->top_level, NULL ) )
	status = 1;

    return status;
}

void
phg_cpm_toolkit_close_ws( ws )
    Ws	*ws;
{
    XtDestroyWidget( ws->shell );
}
