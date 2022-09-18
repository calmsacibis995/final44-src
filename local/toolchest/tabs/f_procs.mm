.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "Setup"
This section contains routines for setting up and ending a Tabs program.
.P
.ne 8
.H 2 Start_Form
.CW
Start_Form (h_char, v_char)
char h_char;
char v_char;
.CN
This procedure performs all of the initial setup steps for running
a form.  The global variables ``stdwindow'' and ``errwindow'' are initialized
by this procedure.  Start_Form() must be called prior to all field related
activity.  This procedure also sets the terminal to raw mode.
.P
The variable ``h_char'' is used as the horizontal character for boxing
the standard window.  ``v_char'' is used as the vertical boxing
character.  If ``h_char'' is zero the window will be displayed unboxed.
.sp 2
.ne 6
.H 2 Def_Interrupt
.CW
Def_Interrupt (function)
int (*function) ();
.CN
This procedure sets the specified function to catch SIGINT and
SIGQUIT.  If 0 is specified the default actions will be taken.
.sp 2
.ne 5
.H 2 End_Form
.CW
End_Form ()
.CN
This procedure sets the terminal back to cooked mode and resets the
signals SIGQUIT and SIGINT.
.H 1 "Simple Input Field Management"
This section contains simple field creation, deletion, movement and 
modification routines.
Other sections also contain field management functions (e.g., the menu and
scrollable region sections).
Any routine in any section that starts with ``Set_'' modifies a previously
created field.
.P
.ne 11
.H 2 "New_Field"
.CW
struct field_item      *
New_Field (row, column, type, fill_char, help, keywords)
int     row;
int     column;
int     type;
char   *fill_char;
char   *help;
char   *keywords;
.CN
This function creates a new field with the specified attributes.
This procedure does not update the screen.  The arguments are used as
follows:
.BL
.ne 3
.LI
row
.br
.sp 1
This is the row or line position of the field.  This function assumes
that the field will be placed (see Show_Field() and Show_Default_Field()) in
the standard window (i.e. struct window *stdwindow).  The rows run
from the top of the screen to the bottom of the screen.  All coordinates
are zero origin based.
.ne 3
.LI
column
.br
.sp 1
This is the column position of the field.  The columns run from left to right
on the screen.  All coordinates are zero origin based.
.ne 3
.LI
type
.br
.sp 1
This is the type of field to be created.  The following types of fields
are currently supported:
.DL
.LI
CMKEY and CMKEY_LIST \(em keywords
.LI
CMCFM \(em confirmation \(em carriage return or line feed only
.LI
CMSTR \(em string \(em any combination of letters and numbers
.LI
CMNUM \(em numeric only \(em this includes both integer and decimal numbers
.LI
CMFILE \(em file names \(em this includes file wild carding
.LI
CMENV \(em environmental variables - (sorts environ array as a side effect)
.LI
CMREGN \(em a scrollable region (see New_Region() below).
.LE
.ne 3
.LI
fill_char
.br
.sp 1
This is a string containing the background text for the field.  The
background text is the string of characters that are over written with
the end user supplied input.  The length of the field is determined from
the length of this string.
.ne 3
.LI
help
.br
.sp 1
This is the help message that will be printed when the end user enters a
``?''.  If this argument is zero the default help message for this type
of field will be printed when help is requested.  More detailed control
of help displays may be obtained with the Set_Help() procedure.
.ne 3
.LI
keywords
.br
.sp 1
The keyword field is used with CMKEY, CMFILE, and CMNUM type fields. 
For CMKEY, keyword fields, ``keywords'' is a string containing the list of
allowable keywords.  Keywords are separated by spaces, for example
"one\ two\ three".  Keywords are displayed in sorted order.  The number
of keywords must be less than or equal to the defined constant MAX_KEYS,
which is currently set to 128.
.br
.sp 1
For CMKEY_LIST, keyword list fields, ``keywords'' is a zero terminated
array of struct keys.  The keys structure contains a pointer to a
keyword string (kstr) and a keyword value (kval).  Keywords constructed
using this technique may contain any character including spaces.  The
associated key value for the selected item is placed in
``field_ptr\->fndfv''.  Keywords are displayed in sorted order. 
Keywords lists of more than defined constant MAX_KEYS, which is
currently set to 128, will not be sorted.
.br
.sp 1
For CMFILE, filename fields, ``keywords'' contains the number of files.  If
the number is one, one filename may be given.  If the number is greater
than one, files may be specified using wild card notation (e.g. *.[hc]).
This number is passed as an ASCII string, for example "2".
.br
.sp 1
For CMNUM, numeric fields, ``keywords'' contains the number of digits behind
the decimal point and the range for the number.  These numbers are
passed as an ASCII string of the form, ``DIGITS,LOW,HIGH''.  For
example, "2,0.0,9.9", would be used for fields wishing one digit behind
the decimal point and a number in the range 0.0 to 9.9.
The number of digits behind the decimal point is in plus one notation.
Zero specifies integer numbers.  One specifies only a decimal point, etc.
.LE
.sp 2
.ne 6
.H 2 Del_Field
.CW
Del_Field (field_ptr)
struct field_item      *field_ptr;
.CN
This procedure deletes the specified field.  This only removes the field
from the display.  If the field has labels, the labels are also deleted.
It does not free any memory.  The field may be display again with any
of the ``Show'' routines.
.sp 2
.ne 6
.H 2 "Free_Field"
.CW
Free_Field (field_ptr)
struct field_item      *field_ptr;
.CN
This procedure frees the space associated with the specified field.
If the field has labels, the labels are also freed.  This routine
does not delete the fields or labels from the window display.
.sp 2
.ne 9
.H 2 "Move_Field"
.CW
Move_Field (field_ptr, row, column, window)
struct field_item      *field_ptr;
int     row;
int     column;
struct window *window;
.CN
This procedure moves the specified field to the (row,column) position in
the specified window.  The old position is deleted.  If no window
is specified (i.e. window is equal to zero), the old window is assumed.
.sp 2
.ne 7
.H 2 "Dup_Field
.CW
struct field_item *
Dup_Field (field_ptr)
struct field_item      *field_ptr;
.CN
This procedure duplicates the specified field.  The value returned is a
pointer to the new field.  A zero return means that the field was not
successfully duplicated.
.sp 2
.ne 8
.H 2 "Set_Label"
.CW
Set_Label (field_ptr, where, label, attribute)
struct field_item *field_ptr;
char   *where;
char   *label;
int     attribute;
.CN
This procedure adds a label to the specified field.  Labels
may be placed in four directions around the field.  ``where'' should be
either "left", "right", "above", or "below".  This procedure
modifies the data structures associated with a particular field but it
does not update the screen.  The attribute argument specifies
the visual attribute that is to be applied to the string.  See the
Set_Attribute() procedure for a list of available visual attributes.
.sp 2
.ne 7
.H 2 Del_Label
.CW
Del_Label (field_ptr, label_ptr)
struct field_item      *field_ptr;
struct label_item      *label_ptr;
.CN
This procedure deletes the specified label.  This only removes the
label from the display.  It does not free any memory.
.sp 2
.ne 6
.H 2 "Free_Label"
.CW
Free_Label (label_ptr)
struct label_item *label_ptr;
.CN
This procedure frees the space associated with the specified label.
This routine does not delete the fields or labels from the window
display.
.sp 2
.ne 8
.H 2 "Set_Attributes"
.CW
Set_Attributes (field_ptr, flags)
struct field_item *field_ptr;
int	flags;
.CN
This procedure sets the attribute flags associated with the specified
field.  The following is a list of the supported attributes.
.so Tabs.t2.mm
.FS *
These attributes are for input fields only.
They do not apply to ``printing.''
.FE
Invisible fields behave like the assigned field type except that
characters in the field are displayed as blank spaces on the screen.
.P
Set_Attribute() calls are NOT cumulative.  Each call will completely
reset all of the attributes to the new flags.  The following line is a
typical use of the procedure.
.CW
	Set_Attribute (f[index], FACENTER | FAREVV | FAUNDER);
.CN
.sp 2
.ne 8
.H 2 Set_An_Attribute
.CW
Set_An_Attribute (field_ptr, flags)
struct field_item *field_ptr;
int	flags;
.CN
This procedure sets the attribute flags associated with the specified
field.  Attributes include left, right, and center for formatting,
and the visual attributes. The attributes can be set one at a time
or in one call.  Set_An_Attribute() calls ARE cumulative.  See
Set_Attributes() for a list of the supported attributes.
.br
.sp 2
.H 2 Un_Set_An_Attribute
.CW
Un_Set_An_Attribute (field_ptr, flags)
struct field_item *field_ptr;
int	flags;
.CN
This procedure removes the specified attribute.  See Set_Attributes()
for a list of the supported attributes.
.sp 2
.ne 7
.H 2 "Set_Auto_Advance"
.CW
Set_Auto_Advance (field_ptr, state)
struct field_item      *field_ptr;
boole  state;
.CN
This procedure sets the auto advance (advance when complete) flag
for the specified field.  If the auto advance flag is set, the field
is exited when it is full or when a completion request is made (e.g. ESCAPE
key is pressed).
.sp 2
.ne 8
.H 2 "Set_CMP_Default"
.CW
Set_CMP_Default (field_ptr, string)
struct field_item *field_ptr;
char   *string;
.CN
This procedure sets the ``completion default'' for the specified field.
If the user enters a completion request (ESCAPE) in an empty field, the
completion default is printed (i.e. completed).  It is an invisible
default value.  The procedure Show_Default_Field() is used to set
visible default values.
.sp 2
.ne 6
.H 2 "Set_EOF"
.CW
Set_EOF (field_ptr, eof_state, eof_verify)
struct field_item      *field_ptr;
boole  eof_state;
boole  eof_verify;
.CN
This procedure sets the state flag for enabling EOF exit from the
specified field.  If ``eof_state'' is TRUE, the field can be exited
by entering the end of file character, usually control-D.  If
``eof_verify'' is TRUE, then the field is verified before exiting.
The default action for the EOF character is to cause Get_List() to
return or stop processing the current list of fields.
.sp 2
.ne 8
.H 2 "Set_Window"
.CW
Set_Window (field_ptr, window1, window2, window3)
struct field_item *field_ptr;
struct window *window1;
struct window *window2;
struct window *window3;
.CN
This procedure sets the data collection window, help window, and error
message window (see Print_Message()) for the specified field.
``window1'' is the data collection window.  ``window2'' is the help
window.  ``window3'' is the error message window.  A window pointer of
zero may be used to specify no change.
.P
Most fields use two standard windows.  ``stdwindow'' is
defined to be the main default window for both data collection and error
messages (see Start_Form()).  ``errwindow'' is the default help window. 
Forms running in very narrow windows may wish to have the error messages
sent to ``stdwindow''.
.P
This command should be used prior to displaying the field (see
Show_Field() and Show_Default_Field()).  To change the data collection
window after the field has been displayed use the procedure
Move_Field().
.sp 2
.ne 7
.H 2 Link_Fields
.CW
Link_Fields (field1_ptr, field2_ptr)
struct field_item *field1_ptr;
struct field_item *field2_ptr;
.CN
This procedure links field2 to field1.  When getting input to
field1, field2 will be used as an alternate.  This provides a
mechanism for reading two or more types from the same field.
The field used as field2_ptr may be used in links with other
fields.  All string space is maintained by the first item of the link.
.P
BE WARE!!! Some field types behave differently when they are used as
linked fields.  The confirmation field will allow both TAB and a
confirmation key (i.e. carriage return or new line) when it is used as
a secondary linked field.  Numeric fields use the default reader
(i.e. getachar()) rather than the number filtering reader read_num().
.sp 2
.ne 7
.H 2 Unlink_Fields
.CW
Unlink_Fields (field1_ptr, field2_ptr)
struct field_item *field1_ptr;
struct field_item *field2_ptr;
.CN
This procedure unlinks two previously linked fields.
