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

Def_Editing_Type (type)
register int    type;
{
	if ((type == OVERLAY) || (type == INSERT))
		_Editing_Type = type;
}

Def_Entry_Type (type)
register int    type;
{
	if ((type == FAR_RIGHT) || (type == FAR_LEFT))
		_Entry_Type = type;
}

Def_Auto_Pos (flag)
register int    flag;
{
	Auto_Position = flag;
}

Def_Marked_Areas (flag)
register int    flag;
{
	Area_On = flag;
}

Def_Error_Attr (attribute)
register int    attribute;
{
	Mess_Attribute = attribute & VT_VIDEO;
}

Def_Overflow_Action (function)
int     (*function) ();
{
	Glbl_Overflow_Action = function;
}

Def_Area_Attributes (attributes)
register int    attributes;
{
	Area_Attribute = attributes & VT_VIDEO;
}

Def_Help_Help (string)
register char  *string;
{
	if ((string) && (*string))
		Help_Help_String = string;
}

Def_Keep_Position (flag)
register int    flag;
{
	Keep_Cursor_Pos = flag;
}
