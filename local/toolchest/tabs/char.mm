.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Creating Character Directives \(em Def_Char_Action"
.P
.ne 9
.CW
Def_Char_Action (c, type, function, break_type)
char c;
int type;
int (*function) ();
int break_type;
.CN
This procedure is used to redefine the meaning of characters to Tabs.
The arguments to the procedure are as follows:
.BL
.LI
c \(em the character whose definition is to be altered.  This includes the
control keys (i.e. 0 to 037), all printable characters and numbers 
(i.e. 038 to 0177) and the following special keys.
.so Tabs.spec.mm
.br
.LI
type \(em this is the type of character that ``c'' is to become.  There are
four character types.
.DL
.LI
BREAK \(em this class of characters specifies that Tabs is to perform some
inter-field action or verification.  Common BREAK characters include the
cursor pad keys and TAB and carriage return.
.LI
CORRECT \(em this class of characters is used to perform editing
operations within a given field.  Common CORRECT characters are the
user's ERASE and KILL characters.
.LI
PUNC \(em this class of characters is used to separate and define words and
tokens read by Tabs.  The space character (octal 40) is the only
predefined PUNC character.
.LI
NORMAL \(em this class of characters includes all of the characters that
are displayed within a field.  This is the standard character set.
.LE
.LI
function \(em this is the function that will be used to process the
character.  Standard processing functions include, regchar() for NORMAL
and PUNC characters, brkchar() for BREAK characters, and corchar() for
CORRECT characters.  These functions all have the following format.
.ne 10
.CW
function (field_ptr, rc)
struct field_item *field_ptr;
char    rc;
{
	/* Body */

	return (TRUE or FALSE);
}
.CN
``field_ptr'' points to the current field.  ``rc'' is the character that
was associated with this function.  ``rc'' is included so that one
function may be used to handle many different characters.
.LI
break_type \(em this is meaningful only if the character being specified is
to be a BREAK character.  There are six types of BREAK characters. 
These different types refer to internally maintained lists of BREAK
characters that are arranged by function.
.DL
.LI
CM_LIST \(em this is used to specify the cursor movement list of BREAK
characters.  All of the cursor pad keys are included in this list.
.LI
BTAB_LIST \(em this is the BACK TAB list.  The BACK TAB key and control-P
are included in this list.  Some people also add control-N to this list.
.LI
TAB_LIST \(em this is the TAB list.  The TAB key is included in this list.
If you define a key other than control-I as the TAB key, TAB_LIST
should be used as the ``break_type'' for the new character.
.LI
CFM_LIST \(em this is the list of characters that are allowed as
confirmation characters.  The default list includes carriage return and
line feed.
.LI
EOF_LIST \(em this is the list of characters that may be used as end of
file characters (see Set_EOF()).  The default list includes the user's
specified EOF character, usually control-D.
.LI
UTIL_LIST \(em this list is intended for BREAK characters that have some
intra-field specific action.  ESCAPE and ``?'' are included in this
list.
.LE
.LE
.P
.ne 5
The following code fragment could be used to change the EOF character
from control\-D to control\-X.
.ne 18
.CW
main ()
{
	extern int mybrkchar ();
	~
	Def_Char_Action (CTRL(D), NORMAL, regchar, 0);
	Def_Char_Action (CTRL(X), BREAK, mybrkchar, EOF_LIST);
	~
}
.CN
.CW
mybrkchar (field_ptr, rc)
struct field_item *field_ptr;
char    rc;
{
	brkchar (field_ptr, K_EOF);
	return (TRUE);
}
.CN
``mybrkchar()'' uses the standard BREAK character handler to set all
flags, etc.  ``brkchar()'' is given one of the generic BREAK
characters.  The complete list of generic BREAK characters may be found
in the Tabs header file, ``fields.h.''
.P
Notice that the application suppled BREAK routine, ``mybrkchar()''
returns TRUE.
All BREAK handling routines must return TRUE if the BREAK
action, return to Get_Field(), is to be performed.
A TRUE return from
any of the character handling routines will cause control to return to
Get_Field().
.sp 2
