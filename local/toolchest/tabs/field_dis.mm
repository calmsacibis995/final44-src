.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Field Display and Collection"
.P
These routines display previously created fields on the screen, write field
contents to an output file pointer, collect the response from the user and 
provide access to the response.
.P
.ne 6
.H 2 "Show_Field"
.CW
Show_Field (field_ptr)
struct field_item      *field_ptr;
.CN
This procedure initializes the specified field.  This includes
displaying the field in its window (see Set_Window()).
In most cases Show_List() is the preferred method.
.sp 2
.ne 7
.H 2 "Show_Default_Field"
.CW
Show_Default_Field (field_ptr, string)
struct field_item      *field_ptr;
char   *string;
.CN
This procedure sets the default value of the specified field to
the value in ``string''.  This procedure will cause the field to be
displayed (like Show_Field() ).  No type checking is done on the
default value.
.sp 2
.ne 7
.H 2 "Show_Label"
.CW
Show_Label (field_ptr, label_ptr)
struct field_item      *field_ptr;
struct label_item      *label_ptr;
.CN
This procedure prints the specified label item with the specified
field.  Labels may appear in 4 directions around the field.  This
procedure is called by Show_Field() and Show_Default_Field().
.sp 2
.ne 6
.H 2 "Get_Field"
.CW
Get_Field (field_ptr)
struct field_item      *field_ptr;
.CN
This function performs all of the processing required to collect
the user's input for the specified field.  If the field has not been
displayed it will be.
The user's input may be
examined by using the function Field_Value ().
.br
.sp 1
The value returned by the function is the method by which the user
exited the field.
.so Tabs.t1.mm
All returns, other than tab, must be enabled for the field with the
Set_Tab_Movement() or Set_EOF () procedures.  See Get_List() for the
details of handling all of these returns.
.br
.sp 1
No formatting is provided in this procedure.  Get_List() performs
the standard (attribute specified) formatting.
In most cases Get_List() is the preferred field collection function.
Get_List() calls Get_Field().
.sp 2
.ne 7
.H 2 "Field_Value"
.CW
Field_Value (field_ptr, string)
struct field_item *field_ptr;
char   string[];
.CN
This procedure places the current value of the specified field in ``string''.
This is hardly necessary from a C based form.  A C based form can access
the field structure directly.  The procedure is required for forms
produced in an interpreted language.
.sp 2
.ne 7
.CW
ReShow_Field (field_ptr)
struct field_item	*field_ptr;
.CN
This procedure displays a single field and leaves its contents untouched.
If the field was previously centered or right justified it displays
it the same way.
.sp 2
.ne 7
.H 2 Right_Field
.CW
Right_Field (field_ptr)
struct field_item      *field_ptr;
.CN
This procedure right justifies the current value of the specified field.
.sp 2
.ne 6
.H 2 Left_Field
.CW
Left_Field (field_ptr)
struct field_item      *field_ptr;
.CN
This procedure left justifies the current value of the specified field.
.sp 2
.ne 6
.H 2 Center_Field
.CW
Center_Field (field_ptr)
struct field_item      *field_ptr;
.CN
This procedure centers the current value of the specified field.
.sp 2
.ne 7
.H 2 "Dump_Field"
.CW
Dump_Field (field_ptr, where)
struct field_item      *field_ptr;
FILE * where;
.CN
This procedure prints the current value of the specified field on
the specified stream created with a call to fopen(3) or popen(3).
This is hardly necessary from C, but it is
required for interpreted versions.
