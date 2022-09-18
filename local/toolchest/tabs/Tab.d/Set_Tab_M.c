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
 *	Set_Tab_Movement (field_ptr, ctlb_state, bverify,
 *				cp_state, cpverify, onepass)
 *
 *	The procedure sets state flags for controling movement from the
 *	specified field.
 *
 *		cltb_state - specifies whether or not backtab is allowed
 *		bverify    - specifies whether or not the field should be
 *				verified when backtab is used.
 *		cp_state   - specifies whether or not cursor pad and mouse
 *				style movement is allowed
 *		cpverify    - specifies whether or not the field should be
 *				verified when cursor or mouse movement is
 * 				used.
 *		onepass     - specifies whether or not the field is to be
 *				entered only once.
 *
 */

Set_Tab_Movement (field_ptr, ctlb_state, bverify, cp_state, cpverify, onepass)
register struct field_item      *field_ptr;
boole ctlb_state;
boole bverify;
boole cp_state;
boole cpverify;
{
	Set_One_Pass (field_ptr, onepass);

	Set_CP_Movement (field_ptr, cp_state, cpverify);

	Set_BT_Movement (field_ptr, ctlb_state, bverify);
}

Set_One_Pass (field_ptr, state)
register struct field_item      *field_ptr;
register int state;
{
	F_Ok (field_ptr, "Set_One_Pass");

	if (state)
		field_ptr -> txflg |= TXONET;
	else
		field_ptr -> txflg &= ~(TXONET);

	if (field_ptr -> fnflg & FNALT)
		Set_One_Pass (field_ptr -> fnalt, state);
}

Set_CP_Movement (field_ptr, state, verify)
register struct field_item      *field_ptr;
register int state;
register int verify;
{
	F_Ok (field_ptr, "Set_CP_Movement");

	if (state)
	{
		field_ptr -> txflg |= TXCPM;
		if (verify)
		{
			field_ptr -> txflg |= TXCPVFY;
		}
		else
		{
			field_ptr -> txflg &= ~(TXCPVFY);
		}
	}
	else
	{
		field_ptr -> txflg &= ~(TXCPM | TXCPVFY);
	}

	if (field_ptr -> fnflg & FNALT)
		Set_CP_Movement (field_ptr -> fnalt, state, verify);
}

Set_BT_Movement (field_ptr, state, verify)
register struct field_item      *field_ptr;
register int state;
register int verify;
{
	F_Ok (field_ptr, "Set_BT_Movement");

	if (state)
	{
		field_ptr -> txflg |= TXBTAB;
		if (verify)
		{
			field_ptr -> txflg |= TXBTVFY;
		}
		else
		{
			field_ptr -> txflg &= ~(TXBTVFY);
		}
	}
	else
	{
		field_ptr -> txflg &= ~(TXBTAB | TXBTVFY);
	}

	if (field_ptr -> fnflg & FNALT)
		Set_BT_Movement (field_ptr -> fnalt, state, verify);
}
