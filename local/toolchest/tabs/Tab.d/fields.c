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
#include <signal.h>
#include <setjmp.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	fields.c - this file contains the globals for the forms library.
 */

struct window  *stdwindow;		/* Standard windows */
struct window  *errwindow;

char *error_fields;			/* Error message for clean_err () */
jmp_buf lab_com_re;

struct argnod  *gchain = 0;		/* Expand filenames linked list */
int cnt_gchain;

int     hlp_status;			/* Flags for prhlp () */

int MOUSE_BUTTON;			/* Mouse stuff */
int MOUSE_X;
int MOUSE_Y;
int MOUSE_TYPE;

struct break_item *cm_list;		/* Break character lists */
struct break_item *btab_list;
struct break_item *tab_list;
struct break_item *cfm_list;
struct break_item *eof_list;
struct break_item *punc_list;		/* Punctuation characters */

int (*Glbl_pre_action) ();		/* Global pre & post action routines */
int (*Glbl_post_action) ();

/* Sanity Values */
struct field_item *_F_Field = 0;
struct field_item *_L_Field = 0;
struct label_item *_F_Label = 0;
struct label_item *_L_Label = 0;

/* Editing type */
int _Editing_Type = 0;

/* Enter fields at the front or back */
int _Entry_Type = 0;

/* field_list pointers */
struct arg_stack	*GL_Arg_Stack = 0;

/* Overflow action for texti() */
int (*Glbl_Overflow_Action) () = 0;

/* Positioning flag for txcursor within fields */
int	Auto_Position = FALSE;

/* Auto Position flaga for one time only - start TRUE in case Auto_Position TRUE */
int	Keep_Cursor_Pos = TRUE;

/* Attribute for error messages */
int	Mess_Attribute = 0;

/* String for how to get help */
char	*Help_Help_String = "- Type  ? for help";
