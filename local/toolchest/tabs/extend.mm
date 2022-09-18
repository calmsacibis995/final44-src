.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Field Overflow and Extension"
.P
These routines control what happens when the user reaches the end of
a field.
An user-defined function can be assigned to be called when the field
overflows.
Sample field-extension routines are included.
.P
.ne 13
.sp 2
.H 2 Set_Overflow
.CW
Set_Overflow (field_ptr, flag)
struct field_item	*field_ptr;
int	flag;
.CN
This procedure enables or disables the overflow action (see Def_Overflow_Action)
for a particular field.
Whatever function is defined in Def_Overflow_Action() will
be applied to the field when the user reaches the end of the field.
.sp 2
.H 2 Set_Extend
.CW
Set_Extend (field_ptr, fill_char)
struct field_item	*field_ptr;
char	*fill_char;
.CN
This procedure marks a field as extendable if ``fill_char''
is longer than the current fill_char string in the field
structure (see below) or unextendible if it is shorter.
This routine calls Set_Overflow() with the appropriate values and
sets up the field for use with an extension routine as defined by
a call to Def_Overflow_Action().
For examples of extension routines see
Extend(), Ext_Field() and Ext_Long_Field().
.sp 2
.ne 9
.H 2 Def_Overflow_Action
.CW
Def_Overflow_Action (function)
int	(*function)();
.CN
This procedure defines the function that will be called when the user
reaches the end of a field.
The function will be called if the overflow action has
been enabled for that field by Set_Overflow() or Set_Extend().
A 0 for ``function'' will turn off the overflow action and the default
is no action.
See Extend(), Ext_Field() and Ext_Long_Field() for examples of 
overflow functions.
If writing your own extension routines, you should also look at the
way Set_Extend() sets up elements in the field structure for use by
Extend, etc.
``ext_fill_char'' in the field structure was included
for use with extension/field overflow functions.
For example, it is treated as the background
text for the largest possible field by Set_Extend() and the associated 
functions.
.sp 2
.ne 11
.H 2 Extend
.CW
Extend (field_ptr)
struct field_item	*field_ptr;
.CN
This procedure will extend a field one character if this function
has been setup as
the overflow function (see Def_Overflow_Action()).
Action will be taken if the field is not as long as the fill character
string passed to Set_Extend()
and the user has reached the end of the field.
Extend() does not check to see if it will write over another field.
Ext_Field() and Ext_Long_Field() check the position of other fields
and move them, then call Extend() to expand the field.
This is the simplest of the extend routines.
.sp 1
.ne 14
.H 2 Ext_Field
.CW
Ext_Field (field_ptr)
struct field_item	*field_ptr;
.CN
This procedure will extend a field one character if this function
has been setup as
the overflow function (see Def_Overflow_Action()).
Action will be taken if the field is not as long as the fill character
string passed to Set_Extend()
and the user has reached the end of the field.
The position of other fields is checked so that they are not overwritten.
Other fields are moved to the right if there is room on the line.
The field will not be extended if fields to the right can not be moved
or there is no room to extend the field on the line.
Fields to the right will not be moved if they have labels above or 
below the field.
.sp 1
.ne 16
.H 2 Ext_Long_Field
.CW
Ext_Long_Field (field_ptr)
struct field_item	*field_ptr;
.CN
This procedure is like Ext_Field() except that it will move
fields down a row if there is no room to the right.
If necessary (and if there is room), fields will be moved 
to make room for the field to be moved to the next line.
If there is no room to move other fields the field will not be extended.
Instead of extendable fields that go across lines it is
usually better to use a scrollable region created with
New_Scroll_Region() or New_Region().
The New_Scroll_Region() procedure makes it easy to write
an overflow action that would replace a field with a scrollable region
when the user overflowed the field.
