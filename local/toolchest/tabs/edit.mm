.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Inter-field Control and Movement"
.P
This section includes routines to change inter-field movement
characteristics and a routine to set pre and post actions on fields,
Set_Actions().
This last routine makes the list-collection routines described above
highly extensibility.
Another document, ``Tabs:  A Window Based, Extensible, Highly Typed, 
Electronic Forms Package'' [4], provides necessary background information
for efficient use of the routines described here.
.P
.ne 11
.H 2 Set_Tab_Movement
.CW
Set_Tab_Movement (field_ptr, bt_state, bt_verify,
			cp_state, cp_verify, onepass)
struct field_item      *field_ptr;
boole	bt_state;
boole	bt_verify;
boole	cp_state;
boole	cp_verify;
.CN
This procedure sets the state flags for controlling movement out of the
specified field.
.BL
.LI
bt_state \(em specifies whether or not BACK TAB is allowed.  Control-P
is also controlled by this flag.
.LI
bt_verify \(em specifies whether or not the field should be
verified when BACK TAB is used.
.LI
cp_state \(em specifies whether or not cursor pad and mouse
style movement are allowed.  Control-N is also controlled by this flag.
.LI
cp_verify \(em specifies whether or not the field should be
verified when cursor or mouse movement are used.
.LI
onepass \(em specifies whether or not the field is to be used only once.
A field is marked as having been used when it contains characters and
the user moves to another field.
.LE
.P
Applications often allow BACK TAB from any field without verification. 
This allows the end user to go back and edit previous fields.  With only
BACK TAB available the application can guarantee that the form is
complete and valid up to the current field.
.sp 2
.ne 8
.H 2 Set_BT_Movement
.CW
Set_BT_Movement (field_ptr, bt_state, bt_verify)
struct field_item      *field_ptr;
boole bt_state;
boole bt_verify;
.CN
This procedure sets the BACK TAB states only.  Set_Tab_Movement() uses
this function.
.sp 2
.ne 8
.H 2 Set_CP_Movement
.CW
Set_CP_Movement (field_ptr, cp_state, cp_verify)
struct field_item      *field_ptr;
boole cp_state;
boole cp_verify;
.CN
This procedure sets the cursor pad and mouse states only. 
Set_Tab_Movement() uses this function.
.sp 2
.ne 8
.H 2 Set_One_Pass
.CW
Set_One_Pass (field_ptr, onepass_state)
struct field_item      *field_ptr;
boole onepass_state;
.CN
This procedure specifies whether or not the field is to be used only
once.  Set_Tab_Movement() uses this function.
.sp 2
.ne 8
.H 2 Set_Actions
.CW
Set_Actions (field_ptr, pre, post)
register struct field_item *field_ptr;
int (*pre) ();
int (*post) ();
.CN
This procedure sets the pre and post action routines to ``pre'' and
``post'' respectively.  The pre-action is executed just prior to reading
the field each time the field is entered.  The post
action routine is executed each time the field is exited.
These routines give the application developer a great deal
of freedom and control while using all of the power of Get_List().
.P
The following is a code fragment for defining a typical pre or post action
routine.
.ne 13
.CW
int
pre_or_post (f, count, index, rc)
struct field_item **f;
int	count;
int	index;
int	rc;
{
	/* Body */
~
	return (new index);
}
.CN
The arguments passed to the pre and post action routines are as follows.
.BL
.LI
struct field_item **f;
.br
.sp 1
This is the list of fields from the call to Get_List().
.LI
int count;
.br
.sp 1
This is the number of fields from the call to Get_List().
.LI
int index;
.br
.sp 1
This is the index of the current field (e.g f[index]).
.LI
int rc;
.br
.sp 1
This is the return code from the last call to Get_Field().
.LE
.P
The return value from the pre and post action routines must be an int. 
This is used as the next index for Get_List().  Returning ``count''
always causes Get_List() to return.  Returning ``index'' allows
Get_List() to proceed as usual.  A minus one (i.e. -1) return value
causes the current field to be collected again.
.P
The pre and post action routines may be used with the redefinable
character features (see the description of the Def_Char_Action()
procedure) to implement control character directives that have some
inter-field action.  To avoid having to set the pre and post actions of
every field there exist global pre and post action routines that may be
set by the application.  The following is a code fragment for setting
the global pre and post action routines.
.ne 11
.CW
main ()
{
	extern int my_post ();
	extern int my_pre ();
	~
	Glbl_post_action = my_post;
	Glbl_pre_action = my_pre;
	~
}
.CN
If both field specified and global pre and/or post actions are supplied
both will be executed.  The global routines are executed first and the
return from the global actions take precedence over the field specified
actions.
.H 1 "Edit Style and Cursor Placement"
.P
With the exception of Def_Editing_Type(), the functions described here are
concerned with how the cursor is positioned when a field is entered.
.sp 1
.ne 6
.H 2 "Def_Editing_Type"
.CW
Def_Editing_Type (type)
int type;
.CN
This procedure defines the editing type that will be used with all
subsequent input fields.
OVERLAY and INSERT are the only available types.
All other types will be ignored.
Calling this procedure will immediately invoke the the editing type 
that is requested.
.P
INSERT is the default mode.
In this mode, when a valid character is entered from the keyboard the 
characters from the cursor to the end of the field are moved
one character position to the right and the new character is put where the
cursor is.
The cursor is then moved one character position to the right.
.P
In OVERLAY mode the new character replaces the character under the cursor and
then the cursor is moved one character position to the right.
.sp 2
.ne 6
.H 2 "Def_Entry_Type"
.CW
Def_Entry_Type (type)
int type;
.CN
This procedure defines the entry type that will be used with all
subsequent input fields.
The entry type specifies where the cursor
should be placed when the user moves into an input field that contains
data.
FAR_RIGHT and FAR_LEFT are the only available
types.
All other types will be ignored.
FAR_RIGHT is the default.
Calling this procedure will immediately invoke the entry type that 
is requested.
.P
.sp 2
.ne 20
.H 2 "Def_Auto_Pos"
.CW
Def_Auto_Pos (flag)
boole	flag;
.CN
If
.I flag
is FALSE cursor positioning upon field
entry will behave as defined by the last call to 
Def_Entry_Type(), the default situation.
When
.I flag
is TRUE cursor positioning upon field entry is turned off
such that when a user reenters a field the cursor
will be in the same position as when the user left the field
unless some BREAK character or pre/post action routine
moves the cursor.
For example, positioning with the mouse or other pointing device
is possible when
.I flag
is TRUE.
.P
The following is a detailed explanation of how cursor positioning
works so that application developers can take full advantage of
the possibilities available when cursor positioning is turned off.
Def_Entry_Type() forces the cursor to be positioned either at the 
beginning or end of the field each time a field is entered.
Not having to worry about cursor position is convenient for
application developers.
However, more flexibility, as provided by Def_Auto_Pos() and
Def_Keep_Pos() is sometimes required.
An understanding of the details of cursor
positioning is necessary to utilize these routines effectively.
.P
The position of the cursor in the field is determined by the text cursor,
.I txcursor
(a pointer in the field structure - see ``the field structure'' section of
this manual).
The cursor on the screen points to the same character that the
text cursor
points to in the text buffer (pointed to by
.I txbuf),
the buffer that holds the value of the field.
Notice that the position of the cursor is not determined by a row and 
column position but simply by the position of the
text cursor in the text buffer.
.P
Consider the default situation in Tabs.
When a field is entered the visible cursor is moved to the position
just beyond the last character in the field.
To do this Tabs just repositions the 
text cursor
for that field so that it points to a location in the text buffer
that is one position beyond the last character in the field
(equal to the text pointer,
.I txptr
in the field structure).
This is done in Get_Field().
Lower level routines then automatically move the cursor on the screen
to correspond to the position of the
text cursor
in the text buffer.
.P
Several types of routines can effect the cursor position.
We are only concerned here with positioning the cursor as the field
is being entered.
The effect of Def_Auto_Pos() and Def_Keep_Position() is to turn off cursor
positioning, as defined by Def_Entry_Type(), when entering a field.
CORRECT character routines (see Def_Char_Action()) and routines
that display the field manipulate the text cursor but
are not effected by these functions.
For example, Show_Default_Field() always moves the text cursor to the beginning
or end of the field depending on the last call to Def_Entry_Type().
.P
The following example global pre-action routine (see Set_Actions())
shows one way to search for a string in a list of fields.
Char_String and String_Len are globals.
The cursor will be positioned at the start of the string if the string
is in the field and the search is ended by setting the global 
pre-action routine to 0.
Otherwise the index to the next field will be returned and the search will
continue.
The search is started elsewhere by:
.BL
.LI
assigning the Glbl_pre_action() to myglobal_pre()
.LI
assigning the search string to Char_String
.LI
assigning the length of the search string to String_Len.
.LI
calling Get_List()
.LE
.P
If the search string is not found Get_List() will return.
.CW
myglobal_pre (f, count, index, rc)
register struct field_item     **f;
int     count;
register int index;
int     rc;
{
        register char        *char_ptr;

        char_ptr = field_ptr -> txbuf;
        while (*char_ptr)
        {
                if (strncmp (Char_String, char_ptr, String_Len) == 0)
                {
                        /* found it - set cursor position */
                        field_ptr -> txcursor = char_ptr;
                        Def_Keep_Position (TRUE);
                        Glbl_pre_action = 0;
                        return (index);
                }
                char_ptr++;
        }
        return (++index);
}
.CN
.sp 2
.ne 8
.H 2 "Def_Keep_Position"
.CW
Def_Keep_Position (flag)
int        flag;
.CN
.P
If
.I flag
is FALSE cursor positioning upon field
entry will behave as defined by the last call to 
Def_Entry_Type(), the default situation.
When
.I flag
is TRUE cursor positioning upon field entry is turned off
for the entry into 
.B one
field.
The normal result is that when a user re-enters a field the cursor
will be in the same position as when the user left the field.
However, the position of the cursor may been changed by a 
BREAK character or pre/post action routine.
See Def_Auto_Pos() for a detailed explanation of how
cursor positioning works.
If Def_Keep_Position() is called from a pre-action
routine you can be sure that the normal field-entry
cursor positioning will be turned off for the correct field.
Def_Auto_Pos() changes field entry positioning for all entries into all
fields.
This routine does not distinguish between fields.
It only applies for one time to the next field that is entered.
