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
 *	Set_Label (field_ptr, where, label, attribute)
 *
 *	This procedure adds a label on to the specified field.  Labels
 *	may be placed in four directions around the field.
 *
 */
Set_Label (field_ptr, where, label, attribute)
struct field_item *field_ptr;
char *where;
char *label;
int attribute;
{
	register struct label_item *slabel;
	register struct label_item *nlabel;

	F_Ok (field_ptr, "Set_Label");

	nlabel = (struct label_item *) malloc (sizeof (struct label_item) + MXTRA);

	if (nlabel == 0)
	{
		Print_Message (field_ptr -> meswin, Mess_Attribute,
				"Cannot allocate label space.");
		return;
	}

	nlabel -> where = *where;
	nlabel -> string = label;
	nlabel -> attribute = attribute;
	nlabel -> next = 0;
	nlabel -> _label_check = GOOD_FIELD;

	if (_F_Label == 0)
		_F_Label = nlabel;

	if (_F_Label > nlabel)
		_F_Label = nlabel;
	if (_L_Label < nlabel)
		_L_Label = nlabel;

	if (field_ptr -> label == 0)
	{
		field_ptr -> label = nlabel;
		return;
	}

	slabel = field_ptr -> label;
	if (slabel -> where == *where)
	{
		slabel -> string = label;
		slabel -> attribute = attribute;
		Free_Label (nlabel);
		return;
	}

	while (slabel -> next)
	{
		slabel = slabel -> next;
		if (slabel -> where == *where)
		{
			slabel -> string = label;
			slabel -> attribute = attribute;
			Free_Label (nlabel);
			return;
		}
	}

	slabel -> next = nlabel;
}
