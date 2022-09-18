
/* $XConsortium: toolkit.h,v 5.1 91/02/16 09:59:38 rws Exp $ */

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
 * toolkit.h  -- defines the toolkit-independent interface used
 * by the comparison tool.  This implementation uses XView.
 *
 * See top block comment of toolkit.c for comments on design of this
 * interface.
 */

#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/xv_xrect.h>

/* note that these button status values are not arbitrary - come from XView */
#define TK_BUTTON_ACTIVE    0
#define TK_BUTTON_INACTIVE  1

/*
**
**  Defining some toolkit-independent data types
**
*/

/*
 * TK_Main_Window - an application's main window.
 */
typedef	Frame TK_Main_Window;	

/*
 * TK_Control_Window - A subwindow in which buttons, text input lines,
 * and other control devices may be placed.
 */
typedef Panel TK_Control_Window;

/*
 * Kinds of interface items
 */
typedef Panel_item TK_Button;
typedef Panel_item TK_List;

/*
 * TK_Message_Item - identifies output message item so string can
 * be changed
 */
typedef Panel_item TK_Message_Item;


/*
**
**  Toolkit-independent functions --
**  See toolkit.c for descriptions & parameter types
**
*/

void		    tk_init();

TK_Main_Window	    tk_create_main_window();
TK_Control_Window   tk_create_control_window();
Drawable	    tk_create_X_drawable_window();
XID		    tk_get_xid();

TK_Button	    tk_create_button();
void		    tk_activate_button();
void		    tk_deactivate_button();
void		    tk_set_button_label();
TK_Message_Item	    tk_create_message_item();
void		    tk_set_message();

TK_List		    tk_create_list();
char *		    tk_get_selected_list_item();
char *		    tk_get_list_item();
int		    tk_get_list_length();
void		    tk_insert_list_item();
void		    tk_set_list_item();
void		    tk_delete_list_item();

void		    tk_main_loop();
