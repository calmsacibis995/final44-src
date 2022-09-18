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
 *	getatm (field_ptr)
 *
 *	This subroutine reads the next field (atom) from the input
 *	stream.  Cursor pad and mouse tracks are handled appropriately.
 *	If the current field requires verification on exit this routine
 *	sets the proper state for comnd ().
 *
 */

getatm (field_ptr)
register struct field_item     *field_ptr;
{
	register char  *inpc;
	char   *atmc;


	field_ptr -> cmflg &= ~(CMNOP | CMREP | CMHLP | CMCMP |
			CMABO | CMIBO | CMNUQ | CMFTAB | CMBTAB |
			CMHOME | CMBOTTOM | CMUP | CMDOWN | CMLEFT |
			CMRIGHT | CMMOUSE);

	if (field_ptr -> cmflg & (CMEOL | CMEOF))
	{
		return;
	}

	if ((field_ptr -> txptr == field_ptr -> txbuf) ||
		(chartyp[(*(field_ptr -> txptr - 1) & 0377)] != BREAK) ||
			(*(field_ptr -> txptr - 2) == '\\'))
	{
		texti (field_ptr);

		if (field_ptr -> txflg & TXBLR)
		{
			field_ptr -> cmflg |= CMREP;
			field_ptr -> cmflg &= ~(CMEOL);
			return;
		}

		if ((field_ptr -> txflg & TXBRK) == 0)
		{
			field_ptr -> cmflg |= (CMIBO | CMEOL);
			return;
		}
	}

	if ((field_ptr->type == CMSTR) || (field_ptr->type == CMKEY_LIST))
	{
		if ((punc_list) && (chartyp[punc_list -> which] == PUNC))
			set_brk_list (punc_list, NORMAL);
	}
	else
	{
		if ((punc_list) && (chartyp[punc_list -> which] == NORMAL))
			set_brk_list (punc_list, PUNC);
	}

	inpc = field_ptr -> txbuf;
	while (chartyp[*inpc & 0377] == PUNC)
	{
		inpc++;
		field_ptr -> txcursor--;
	}

	if (field_ptr -> txbuf < inpc)
	{
		strcpy (field_ptr -> txbuf, inpc);
		field_ptr -> txptr = &field_ptr -> txbuf[strlen (field_ptr -> txbuf)];
		inpc = field_ptr -> txbuf;
	}

	while (chartyp[*inpc & 0377] == NORMAL)
	{
		if ((*inpc == '\\') &&
			((inpc + 1) < (field_ptr -> txptr - 1)) &&
			((*(inpc + 1) & 0200) == 0) &&
			(*(inpc + 1) != '\0'))
				inpc++;

		inpc++;
	}

	switch (*(field_ptr -> txptr - 1) & 0377)
	{
		case K_HOME:
			if (field_ptr -> txflg & TXCPVFY)
				field_ptr -> cmflg |= (CMHOME | CMEOL);
			else
				field_ptr -> cmflg |= (CMHOME | CMREP);
			break;

		case K_BOTTOM:
			if (field_ptr -> txflg & TXCPVFY)
				field_ptr -> cmflg |= (CMBOTTOM | CMEOL);
			else
				field_ptr -> cmflg |= (CMBOTTOM | CMREP);
			break;

		case K_UP:
			if (field_ptr -> txflg & TXCPVFY)
				field_ptr -> cmflg |= (CMUP | CMEOL);
			else
				field_ptr -> cmflg |= (CMUP | CMREP);
			break;

		case K_DOWN:
			if (field_ptr -> txflg & TXCPVFY)
				field_ptr -> cmflg |= (CMDOWN | CMEOL);
			else
				field_ptr -> cmflg |= (CMDOWN | CMREP);
			break;

		case K_LEFT:
			if (field_ptr -> txflg & TXCPVFY)
				field_ptr -> cmflg |= (CMLEFT | CMEOL);
			else
				field_ptr -> cmflg |= (CMLEFT | CMREP);
			break;

		case K_RIGHT:
			if (field_ptr -> txflg & TXCPVFY)
				field_ptr -> cmflg |= (CMRIGHT | CMEOL);
			else
				field_ptr -> cmflg |= (CMRIGHT | CMREP);
			break;

		case K_MOUSE:
			if (field_ptr -> txflg & TXCPVFY)
				field_ptr -> cmflg |= (CMMOUSE | CMEOL);
			else
				field_ptr -> cmflg |= (CMMOUSE | CMREP);
			break;

		case K_FTAB:
			if (field_ptr -> txflg & TXCPVFY)
				field_ptr -> cmflg |= (CMFTAB | CMEOL);
			else
				field_ptr -> cmflg |= (CMFTAB | CMREP);
			break;

		case K_BTAB:
			if (field_ptr -> txflg & TXBTVFY)
				field_ptr -> cmflg |= (CMBTAB | CMEOL);
			else
				field_ptr -> cmflg |= (CMBTAB | CMREP);
			break;

		case K_TAB:
			field_ptr -> cmflg |= CMEOL;
			break;

		case K_HELP:
			field_ptr -> cmflg |= CMHLP;
			break;

		case K_ESC:
			field_ptr -> cmflg |= CMCMP;
			if (field_ptr -> txflg & TXAUTO)
			{
				field_ptr -> cmflg |= CMEOL;
			}
			break;

		case K_EOL: 
			field_ptr -> cmflg |= CMEOL;
			break;

		case K_EOF:
			if (field_ptr -> txflg & TXEFVFY)
				field_ptr -> cmflg |= (CMEOF | CMEOL);
			else
				field_ptr -> cmflg |= (CMEOF | CMREP);
			field_ptr -> cmflg &= ~CMNOP;
			break;

		default:	/* Assume they know what they are doing */
			field_ptr -> cmflg |= CMEOL;

	}

	atmc = inpc;

	while (inpc < field_ptr -> txptr)
		*inpc++ = '\0';

	*atmc = '\0';
	field_ptr -> cmflg &= ~CMNOP;
	field_ptr -> txptr = atmc;

	if( !_position( field_ptr ) )
	{
		if( field_ptr -> txcursor > atmc )
			field_ptr -> txcursor = atmc;
		else if( field_ptr -> txcursor < field_ptr -> txbuf )
			field_ptr -> txcursor = field_ptr -> txbuf;
	}
}
