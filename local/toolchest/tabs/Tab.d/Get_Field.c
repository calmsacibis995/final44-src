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
#include <termio.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	Get_Field (field_ptr)
 *
 *	This function performs all of the processing required to collect
 *	the user's input for the specified field.
 *
 *	The value returned by the function is the method by which the user
 *	exited the field.
 *
 *		CMFTAB		- forward tab key
 *		CMBTAB		- back tab key
 *		CMHOME		- home key
 *		CMBOTTOM	- bottom key
 *		CMUP		- up key
 *		CMDOWN		- down key
 *		CMLEFT		- left key
 *		CMRIGHT		- right key
 *		CMMOUSE		- mouse tracks
 *		CMEOF		- end of file
 *
 *	See Get_List () for the details of handling all of these returns.
 *
 *	No formatting is provided in this procedure.  Get_List () performs
 *	the standard (attribute specified) formatting.
 *
 *	Use the TAB_ONLY #define if you want TAB's to be used as the only
 *	means of exiting a simple field.  Without it carriage return and
 *	line feed may also be used.
 */

Get_Field (field_ptr)
register struct field_item      *field_ptr;
{
	extern struct termio    nttybuf;
	register int     (*type) ();
	int	old_cmflg;

	F_Ok (field_ptr, "Get_Field");

	type = field_ptr -> type;

	/* Cursor Pad Movement */
	if (field_ptr -> txflg & TXCPM)
	{
		set_brk_list (cm_list, BREAK);
	}
	else
	{
		set_brk_list (cm_list, DSCARD);
	}

	/* Back Tab Movement (may include other break characters like ^F) */
	if (field_ptr -> txflg & TXBTAB)
	{
		set_brk_list (btab_list, BREAK);
	}
	else
	{
		set_brk_list (btab_list, DSCARD);
	}

	/* End of File Movement */
	if (field_ptr -> txflg & TXSEOF)
	{
		set_brk_list (eof_list, BREAK);
	}
	else
	{
		set_brk_list (eof_list, DSCARD);
	}

	/* Make sure the field is being displayed */
	if (field_ptr -> label) Show_Label (field_ptr, field_ptr -> label);

	/* Clear the flags - texti and getatm */
	field_ptr -> txflg &= ~(TXEOF | TXBRK | TXBLR);
	field_ptr -> cmflg &= ~(CMNOP | CMREP | CMHLP | CMCMP | CMEOF | 
			CMEOL | CMABO | CMIBO | CMNUQ | CMFTAB | CMBTAB |
			CMHOME |  CMBOTTOM | CMUP | CMDOWN | CMLEFT |
			CMRIGHT | CMMOUSE | CMEOF | CMTAMPR);

	/* Catch reparse requests */
	setexit ();

	if (field_ptr -> cmflg & (CMFTAB | CMBTAB | CMHOME | CMBOTTOM |
					CMUP | CMDOWN | CMLEFT | CMRIGHT |
					CMMOUSE | CMEOF))

	{
		field_ptr -> type = type;
		Push_Window (field_ptr -> errwin);
		Print_Message (field_ptr -> meswin, 0, "\0");
		if ((field_ptr -> cmflg & CMEOF) &&
			((field_ptr -> txflg & TXEFVFY) == 0))
		{
			Show_Field (field_ptr);
			return (CMEOF);
		}
		return ((field_ptr -> cmflg &
				(CMFTAB | CMBTAB | CMHOME | CMBOTTOM |
				CMUP | CMDOWN | CMLEFT | CMRIGHT |
				CMMOUSE)));
	}

	field_ptr -> cmflg &= ~(CMEOF);

	if ((type == CMSTR) || (type == CMKEY_LIST))
	{
		set_brk_list (punc_list, NORMAL);
	}
	else
	{
		set_brk_list (punc_list, PUNC);
	}

	if (type == CMCFM)
	{
		set_brk_list (tab_list, DSCARD);
#ifdef TAB_ONLY
		set_brk_list (cfm_list, BREAK);
#endif TAB_ONLY
	}
	else
	{
		set_brk_list (tab_list, BREAK);
#ifdef TAB_ONLY
		set_brk_list (cfm_list, DSCARD);
#endif TAB_ONLY
	}

	/* Reset the end of input string */
	field_ptr -> txptr = &(field_ptr ->
			txbuf[strlen (field_ptr -> txbuf)]);

	_position( field_ptr );
	if( Auto_Position )
		Keep_Cursor_Pos = TRUE;
	else
		Keep_Cursor_Pos = FALSE;

	/* Read the field */
	field_ptr -> type = type;
	comnd (field_ptr);
	old_cmflg = field_ptr -> cmflg;

	/* Get the field confirmation */
	field_ptr -> type = CMCFM2;
	comnd (field_ptr);

	/* Cleanup */
	field_ptr -> type = type;

	Push_Window (field_ptr -> errwin);
	Print_Message (field_ptr -> meswin, 0, "\0");

	if (old_cmflg & CMEOL)
	{
		return ((old_cmflg & (CMFTAB | CMBTAB | CMHOME | CMBOTTOM |
					CMUP | CMDOWN | CMLEFT | CMRIGHT |
					CMMOUSE | CMEOF)));
	}
	return (0);
}
