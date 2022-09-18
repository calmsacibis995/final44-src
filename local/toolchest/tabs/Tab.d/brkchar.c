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
 *	This routine handles the input of a break character.
 *	The character is placed in the output string and
 *	the routine returns TRUE to indicate that a break
 *	character was processed.
 */

brkchar (field_ptr, rc)
register struct field_item *field_ptr;
register char    rc;
{
	char	*pch;
	int	check;
	static int	y_pos;
	static int	x_pos;
	int	mouse_x;
	int	mouse_y;
	int	nrows;
	int	win_width;
	int	mouse_rows;
	int	mouse_len;
	int	len;

	switch (rc & 0377)
	{
	case BTABC:
		rc = K_BTAB;
		break;
	case FTABC:
		rc = K_FTAB;
		break;
	case TABC:
		rc = K_TAB;
		break;
	case ESC:
		rc = K_ESC;
		break;
	case '?':
		rc = K_HELP;
		break;
	case CRET:
	case NL:
		rc = K_EOL;
		break;
	case CTRL(A):
		rc = K_HOME;
		break;
	case CTRL(Z):
		rc = K_BOTTOM;
		break;
	case CTRL(^):
		rc = K_UP;
		break;
	case CTRL(G):
		rc = K_DOWN;
		break;
	case CTRL(T):
		rc = K_LEFT;
		break;
	case CTRL(Y):
		rc = K_RIGHT;
		break;

	case K_MOUSE:
		mouse_x = MOUSE_X - field_ptr -> window -> _top_x;
		mouse_y = MOUSE_Y - field_ptr -> window -> _top_y;

		x_pos = MOUSE_X;
		y_pos = MOUSE_Y;

		if( in_field( field_ptr, mouse_x, mouse_y ) )
		{
			return( FALSE );
		}
		break;

	case K_MOUSE2:
		rc = K_MOUSE;
		if( x_pos == MOUSE_X && y_pos == MOUSE_Y )
			/* just positioning cursor */
			return( FALSE );

		mouse_x = MOUSE_X;
		mouse_y = MOUSE_Y;

		MOUSE_X = x_pos;
		MOUSE_Y = y_pos;
		if( Area_On == FALSE )
			return( FALSE );
		if( Area[0].bot_y )
			Clear_Marked_Areas();

		Area[0].top_x = x_pos;
		Area[0].top_y = y_pos;
		Area[0].bot_x = mouse_x;
		Area[0].bot_y = mouse_y - 1;
		ReShow_All_Lists( FAREVV, FALSE );

		/* if mouse inside current field return FALSE for corchar */
		mouse_x -= field_ptr -> window -> _top_x;
		mouse_y -= field_ptr -> window -> _top_y;

		if( in_field( field_ptr, mouse_x, mouse_y ) )
		{
			return( FALSE );
		}
	}

	*((field_ptr -> txptr)++) = rc;

	field_ptr -> txflg |= TXBRK;

	Print_Message (field_ptr -> meswin, Mess_Attribute, "\0");

	return (TRUE);
}
