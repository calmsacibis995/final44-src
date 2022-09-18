.ds HF 3 3 3 3 3 3
.nr Hb 6
.nr Cl 5
.de cW
.ie \\n(.$ .nr ;G \\n(.f
.el .ft CW
.if \\n(.$ .if !\\n(.$-2 \&\f(CW\\$1\fP\\$2
.if \\n(.$-2 \{.ds }i
.if \\n(.f 2 .ds }i \^
.ds }I \&\f(CW\\$1\fP\\$2\\*(}i
'br\}
.if \\n(.$-2 .if !\\n(.$-4 \\*(}I\f(CW\\$3\fP\\$4
.if \\n(.$-4 .if !\\n(.$-6 \\*(}I\f(CW\\$3\fP\\$4\\*(}i\f(CW\\$5\fP\\$6
.if \\n(.$ .ft \\n(;G
..
.de CW
.DS L N
.cW
..
.de CN
.DE
.R
..
.ps 9
.ds HF 3 2 2 2 2 1 1
.ds HP +1
.nr Hb 1
.nr Hs 1
.nr Hc 0
.nr Hy 1
.nr Cl 5
.nr Ej 0
.nr Si 8
.ND "April 21, 1985"
.TL 311305-8000 39394
Tabs 2.0 Manual: Tools for Creating Window Based Electronic Forms
.AU "C. Douglas Blewett" CDB
.AU "Kenyon I. Hicks" KIH
.TM 11386-850421-01
.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.AS 1
.P
This paper is a brief introduction and a user manual for a package called Tabs.
Tabs can be used to produce window-based user interfaces.
Tabs incorporates qualities from both menu and
block mode electronic forms in one unified interactive system.
The interface provided by this package has qualities that make it
desirable for interfaces for both novice (i.e. casual) and expert (i.e.
frequent) users.
.P
The electronic forms produced using Tabs are a
collection of controlled input and output areas within windows on a CRT.
The input areas or fields may be moved within and between windows while
the form is running.  More than one window may be used at a time.  Like
fields, windows can be moved per the requirements of the
application.
.P
CRT windows are constructed with a portable virtual terminal library.
The window-based virtual terminal creates windows as three dimensional
rectangular objects.  Windows that are ``closer'' to the user occlude
more distant windows.  In this environment windows may be moved
to arbitrary spatial positions on the CRT screen and in depth.
.P
Forms are constructed by calling Tabs procedures or primitives from some
interpreted or compiled language (e.g. C).  Libraries of commonly used
fields may be constructed and maintained using standard software tools.
These algorithmically defined forms are more dynamic than the old
boiler-plate forms of the past.
.AE
.OK "Interpreters and Emulators" "Human Engineering" "Command and Control Systems"
.MT 4
.H 1 "Introduction"
.P
This paper is a brief introduction and a user manual for a package
called Tabs.  This package can be used to produce window based user
interfaces for data processing facilities.  Tabs incorporates qualities
from both menu and block mode electronic forms in one unified highly
interactive system.  The interface provided by this package has
qualities that make it desirable for interfaces for both novice (i.e.
casual) and expert (i.e. frequent) users.  Currently Tabs is available
on machines running the UNIX*
.FS *
UNIX is a Trademark of AT&T Bell Laboratories.
.FE
operating system.
.P
The electronic forms produced using Tabs may be conceptualized as a
collection of controlled input and output areas within CRT based windows.
The input areas or fields may be moved within and between windows while
the form is running.  More than one window may be used at a time.  Like
fields the windows may also be moved per the requirements of the
application.
.P
The window based interface is similar in function to the display manager
found in Teitelman's Programmer's Assistant[1].  CRT windows are
constructed with a portable virtual terminal library.  The window based
virtual terminal creates windows as three dimensional rectangular
objects.  Windows that are ``closer'' to the user occlude more distant
windows.  In this environment windows may be moved to arbitrary spatial
positions on the CRT screen and in depth.  The low level virtual
terminal is based on the UNIX version of EMACS[2] and the
CURSES/TERMINFO package[3].
.P
.ne 5
The following is a list of concepts included within Tabs:
.BL
.LI
Tabs encourages the use of complete words for keywords
(e.g. -all rather than -a).  Tabs' builtin abbreviation capability
encourages this.
.LI
Tabs allows for easy recovery from user produced errors.  Input may be
edited and re-submitted.
.LI
Help is given only when and where it is needed.  Help is provided only
when it is requested by the user.  Error messages explain how to get
help, but do not force the user into troublesome help scenarios.
.LI
The locus of control is with the end user.
Verification of fields occurs at the user's request.  This
prevents the display of help messages with every typographic error.
.LI
Users are encouraged to become more proficient 
(i.e., expert users).
With experience, users move naturally from novice to expert.
No special variables or flags
have to be set to access either novice or expert user features.
.LI
Exception conditions (e.g. help messages) are handled by using the
dynamic aspects of Tabs.  Help messages are displayed in a separate ``pop
up'' window.  Similarly, data not frequently collected from users may be
collected in a window that appears only when needed.
.LI
Forms produced using Tabs are for the most part more dynamic than older
``boiler-plate'' style forms.  Tabs also allows the application
developer to do operations that are difficult or impossible to do with
older mask oriented forms.  For example, Tabs may look for more than one
type of item per field (e.g. a file name or a keyword).
.LI
The details of the implementation are kept from the programmer by a
fairly complete set of function and procedure calls.  Simple forms
require very little knowledge to construct.  At the same time more
experienced programmers can construct elaborate forms-based applications
which allow more detailed algorithmic intervention.
.LI
Tabs takes a very high level approach to forms.
In addition to simple number and string fields,
higher level constructs (e.g. filenames or environmental variables) are supported.
For example, Tabs supports scrollable regions and menus as
field types.  A scrollable region is a field that may contain many
different types of fields in a scrolling window.
.LI
Forms are constructed by calling Tabs procedures or primitives from some
interpreted or compiled language (e.g. C).  Libraries of commonly used
fields may be constructed and maintained using standard software tools.
.LI
Tabs is extensible.  New field types can be added by application
developers as they are needed.  Tabs also allows the application
developer to use arbitrary C functions for pre and post processing the
fields and for providing help information.
.LE
.P
.H 1 "The User Interface"
The user interface can be thought of as having essentially two
aspects, the screen display and user input.  The input side of
the interface includes normal character input and characters that are
commands to Tabs.  The screen display consists of collections
of field and printed strings contained within windows.
The following section describes the
screen displays and the next section describes user input features.
.H 2 "Sample Displays"
The interface is maintained via terminal virtualizing software.  The
environmental variable ``TERM'' is used to determine what type of
terminal is being used.  The following shell commands set the
terminal to be a Concept 100 with eight pages of memory.
.CW
        TERM=c108-8p
        export TERM
.CN
The virtual terminal software currently supports 50 or more popular
terminals.  Consult your local installation for the list of supported
terminals.
.P
Appendix A contains a sample form as it might appear on an end user's
terminal.  Tabs has all of the commonly used features for input fields
and output strings.
Output strings can be placed arbitrarily on the screen and formatted
(e.g. centered).
Tabs also provides facilities
to handle calculated or constructed values as output strings (i.e.
output only fields).
.P
Input fields may include labels (in four directions), background text,
default values, and special formats.  Input fields may also have
auto-tab attributes (advance when full), enter only once, and a host of
other form attributes.
Mouse and function keys are available for use with complex forms.
.ne 2
Section 2.2 has more information on user input.
.P
Appendix B contains a partially completed form.  The user has requested
help in the third field.  Help is provided in a separate window.  Help
messages are always displayed in a separate window.  Simple error or
warning messages are displayed on the last line of the current window
or a window chosen by the application developer.
.P
Help messages have two parts, a text message and a qualifying list or
annotation.  The text part is the usual verbose type of message that is
often used to explain what the input field is about.  The qualifying list is
extra information that Tabs constructs based on the field type.  For
keywords the list is the list of keywords.  For filenames the list is
the list of matching files.  For environmental variables the list is the
list of variable names.  For numeric fields the list is the range.
Either or both of these help message parts may be disabled by the
programmer per the requirements of the application.
.P
Tabs is designed to produce dynamic forms.
The application may add, move, and delete fields and windows as
needed.  A dynamic forms approach can greatly streamline
end user interfaces.
Seldom used fields don't always have to be displayed.
They can be moved onto the form when an exception
condition arises.  Exception conditions can also be handled as separate
forms running in a separate ``pop-up'' window.  Appendix C is an example
of this type of ``on-demand'' strategy.
.H 2 "Character Directives"
The input side of the interface includes normal character input and
characters that are commands to Tabs.  Normal characters are read by
Tabs and subsequently passed onto the program as parsed items.  The
command style characters are termed character directives.  Character
directives request specific actions from the Tabs system.  The action
requested may be a request for some editing operation within the field,
movement to another field, a request to have the current field completed
and/or verified, or a request for help.  Special characters used to
invoke the directives have been chosen from the universe of possible
character sequences.  An attempt has been made to make use of current
UNIX standards (e.g. ERASE and KILL).  Some consideration
has also been given to selecting a portable and reasonable (e.g.
mnemonic) set for commands not currently widely used in standard UNIX.
However, the command set can be changed to meet the needs of the
application.
.P
.ne 5
The following is the current list of directives.
.BL
.ne 4
.LI
? \(em Help request
.br
.sp 1
The help request causes the help window to be displayed.
Application and Tabs supplied help messages are printed within it.
For keywords the list of matching keywords is given.  For filenames the
list of matching (i.e. wild card matches) filenames will be printed.
For shell variables the list of matching shell variables is listed.  For
numbers the range and number of digits behind the decimal are printed.
.sp 1
.ne 4
.LI
Control-I (TAB) \(em Validate the field and move to the next field
.br
.sp 1
TAB is the field confirmation character.  This causes the current
field to be validated and program control to move to the next field.
.sp 1
.ne 4
.LI
ERASE \(em Erase the last character in the field
.br
.sp 1
This is the user specified erase character.  The last character inserted
in the field is deleted.  The character may be recovered with the
control-O directive.
.sp 1
.ne 4
.LI
KILL \(em Kill or Erase the entire field
.br
.sp 1
This is the user specified kill character.  The entire field is erased. 
The field may be recovered with the control-O directive.
.sp 1
.ne 4
.LI
EOF \(em End of file (usually Control-D)
.br
.sp 1
This is the user specified EOF character.  If EOF capabilities for the
field have been enabled with the Set_EOF() procedure, the current list
of fields is exited.  This directive is most commonly used to exit
from scrollable regions.
.sp 1
.ne 4
.LI
Control-P and the BACK TAB key \(em Move to the previous field
.br
.sp 1
This is the BACK TAB directive.  If BACK TAB capabilities have been
enabled for the field with the Set_Tab_Movement() procedure, control
will move to the previous field.
.sp 1
.ne 4
.LI
Control-N \(em Move to the next field
.br
.sp 1
This is the FORWARD directive.  If FORWARD movement capabilities have
been enabled for the field with the Set_Tab_Movement() procedure,
control will move to the next field.  This directive differs from the
TAB key in that verification may be disabled for FORWARD initiated
movement.
.sp 1
.ne 4
.LI
Cursor Pad Key and Mouse \(em move to a specific field
.br
.sp 1
These are different directives that may be issued from
the user's terminal.  Tabs currently supports the generic
function key types listed below.  The control characters that follow the
function key types are supplied for terminals that have no working
function keys and/or touch typists that prefer to keep their hands on
the main keyboard.
.so Tabs.keys.mm
.br
.sp 1
The keys control-^, control-T, control-Y, and control-G are good
for arrow key substitutes.  They match the compass points on most keyboards.
The other arrow key or cursor pad substitutes are control-A for HOME and
control-Z for BOTTOM.  control-A is above control-Z on the keyboard.
.sp 1
Cursor pad and mouse directives have to be enabled with the
Set_Tab_Movement() procedure.  Get_List() performs the correct
inter-field movement.
.sp 1
.ne 4
.LI
Control-C \(em Clear away error messages and the help window
.br
.sp 1
Control-C causes the help window and error messages to be removed from
the display.  This allows the user to have an unobstructed view of the
form.
.sp 1
.ne 4
.LI
Control-V \(em Verify the screen by refreshing the display
.br
.sp 1
Control-V refreshes the screen.  This is useful to help the end user
recover from wall and write messages.
.sp 1
.ne 4
.LI
Control-O \(em Overlay erased characters
.br
.sp 1
Control-O recovers characters that have been erased from the end of the
field with KILL, ERASE, and/or control-W.  This implements a very simple
form of overlay editing.
.sp 1
.ne 4
.LI
Control-W \(em Delete the last word entered
.br
.sp 1
Control-W deletes the last word entered in the field.  This is
essentially a character delete for words.
.sp 1
.ne 4
.LI
Control-B \(em Beginning of the field
.br
.sp 1
Control-B moves the cursor in the field to the beginning of the field. 
This allows the end user to insert characters at the beginning of the
field.  Characters to the right of the cursor are pushed to the right as
new characters are entered.
.sp 1
.ne 4
.LI
Control-E \(em End of the field
.br
.sp 1
Control-E moves the cursor to the end of the field.  This allows the
user to resume adding characters to the end of the field after some other
editing operation.
.sp 1
.ne 4
.LI
Control-L \(em Left in the field
.br
.sp 1
Control-L moves the cursor left one character in the field.  This allows the
user to add characters at any point within the field.  Characters to the
right of the cursor are pushed to the right as new characters are entered.
.sp 1
.ne 4
.LI
Control-R \(em Right in the field
.br
.sp 1
Control-R moves the cursor right one character in the field.  This allows the
user to add characters at any point within the field.  Characters to the
right of the cursor are pushed to the right as new characters are entered.
.sp 1
.ne 4
.LI
Control-[ (ESCAPE) \(em Completion request
.br
.sp 1
ESCAPE is the completion request key.  This causes file names,
decimal numbers, shell variables, and keywords to be expanded.  In
fields where auto advance has been set (see Set_Auto_Advance() )
program control moves to the next field.
.LE
.H 1 "The C Interface"
.H 2 "A Simple Form"
Appendix D contains a simple C based form.  In this form we create two
fields.  On lines 17 and 18 field zero is created as a numeric field
with a range of -123.55 to 123.00.  Field zero is set to be right
justified on line 20.  Field one, on line 29, is a confirmation field.
Since the user can only exit a confirmation field with a carriage
return it is a good choice for the last field in a form.
This use of confirmation fields prevents the user from accidentally moving 
off the end of the form with one of the normal field movement keys.
.P
Notice that the form contained in Appendix D begins with a call to the
procedure Start_Form() and ends with a call to the procedure
End_Form().  All forms must begin and end with these calls.
.P
The bulk of the processing in the form in Appendix D is contained in the
two procedure calls, Show_List() and Get_List().  Show_List(), on line 41,
displays the fields and Get_List(), on line 43, collects the input from
the user.  The values returned for each field can be examined with calls
to the procedure Field_Value().
.H 2 "A More Complex Form"
Appendix E contains a more complex C based form.  This form contains six
fields of various types.  The call to Def_Interrupt(), line 16, sets the form
to catch interrupt signals by running the beep() routine.  Help messages
are set to use efficient, MIT style scrolling on line 18.
.P
This form appears to the end user to behave in a much different
manner than the form from Appendix D.  The call to Set_Auto_Advance(),
line 93, sets the fields to auto-tab to the next field.  This means that
when a field is full or when the completion request (i.e. ESCAPE) has
been given, control will move automatically to the next field.  This one
feature can greatly enhance the input process for the end user.
.P
This form also allows the user to move from field to field using
either terminal supplied function keys and/or a mouse.  This is enabled
with the call to the procedure Set_Tab_Movement() on line 92.
.P
Many of the following sections are a list of Tabs
functions and procedures.  Most users
will only need a few of these to create forms.
It is probably a good idea to read through this list to see
what options are available and refer to the list as the application and
your memory require.
.so f_procs.mm
.so field_dis.mm
.so form.mm
.so edit.mm
.so char.mm
.so help.mm
.so err.mm
.so print.mm
.so scroll.mm
.so menus.mm
.so extend.mm
.so scratch.mm
.so windows.mm
.so makefile.mm
.H 1 "Tips on Using Tabs"
.H 2 "Always Use Get_List()"
Tabs provides essentially endless flexibility.  There are at least three
ways to do most everything.  This can be a benefit or
a detriment.  Most forms follow the simple example given in Appendix D.
A common problem is to use Get_Field() when in fact you want to collect
a list of fields.  In most cases the Get_List()/Show_List() combination will
be the easiest way to construct a new form.  It is also a very good
idea to start out by selecting one of the demonstration programs as the
basis for creating your own program.
.H 2 "Methods for Creating Null Fields"
Application designers commonly want to look for more than one data type
per field.  The most common combination is to look for any field type
and a null response.  Again there are at least three ways to do this
with Tabs.  The recommended way to do this is to link two fields
together with the Link_Fields() procedure.  You can link a confirmation
field in with every field that you want to behave in this manner. 
Confirmation fields when they appear as secondary linked fields will
accept both confirmation characters (i.e. carriage return and new line)
and the TAB character as valid responses.  The field description for the
end user is then a field of a particular type or an empty field.  The
help and error messages will all reflect the right stuff.  Linked fields
require no memory for storage so you can link the same confirmation
field in each time that you need it with out any ill effects.
.P
The second way that you can do this sort of thing is to redefine the
confirmation keys to be whatever type of validation you require.  This
is quite a bit more difficult to do than the link technique, but it is not
really all that tough.  You can do this with the Def_Char_Action()
procedure.
.P
The third way is to create your own field type.  This is probably easier
than changing the definition of all of your confirmation keys, but
harder by quite a bit than the link technique.  A good place to start
with this is the x7.c program in the doc.d directory of your Tabs source.
.P
Most of the current Tabs users use the link technique.  There are examples
of it in most of the sample programs, for example x3.c.
.H 2 "Defining Character Directives for Inter-Field Editing and Control"
.P
This section describes how to create characters actions
that result in inter-field interaction or movement.
Page-up and page-down characters for scrollable regions are examples of
this type of character.
The following example contains character-action and post-action
routines that define CTRL(U) and CTRL(D) to do page-up and
page_down.
The scrollable region field,
.I reg_field,
can be created the same way f[2] is
created in Appendix F.
Only the relevant portions of the main routine are shown here.
.CW
main()
{
	...
	Def_Char_Action (CTRL(D), BREAK, mybrkchar, CM_LIST);	/* Page Down */
	Def_Char_Action (CTRL(U), BREAK, mybrkchar, CM_LIST);	/* Page Up */
	...
	/* create scrollable region field, reg_field */
	...
	Set_Actions (reg_field, 0, reg_post); /* set pre/post action routines */
	...
	/* display field(s) and collect user's response(s) */
	...
}
/*
 *	This is a sample BREAK character action routine.
 *	It uses the standard Tabs brkchar() routine to set the appropriate
 *	flags, etc.  All BREAK routines should return TRUE.
 */

mybrkchar (field_ptr, rc)
struct field_item *field_ptr;
char    rc;
{
	switch (rc)
	{
	case CTRL(U):	/* Page Up */
		brkchar (field_ptr, K_HOME);
		field_ptr -> user_mask = CTRL(U);
		break;
	case CTRL(D):	/* Page Down */
		brkchar (field_ptr, K_HOME);
		field_ptr -> user_mask = CTRL(D);
		break;
	default:
		brkchar (field_ptr, rc);
	}

	return (TRUE);
}
/*
 *	This is a sample post action routine.  The return value (int) is 
 *	the index of the next field to be read.  An index of -1 indicates 
 *	that the current field should be re-read.
 */
#define REPEAT -1    /* repeat a character */
#define NUM_LINES 4  /* number of lines to scroll the region */

reg_post (f, count, index, rc)
struct field_item     **f;
int     count;
int index;
int     rc;
{
	int new_index;

	switch (f[index] -> user_mask)	/* Oh those side effects!!! */
	{
	case CTRL(U):	/* Page Up */
		new_index = index - NUM_LINES;
		break;
	case CTRL(D):	/* Page Down */
		new_index = index + NUM_LINES;
		break;
	default:
		return (index);
	}
	f[index] -> user_mask = 0;
	if (new_index < 0)              /* above top? */
		new_index = 0;
	if (new_index >= count)         /* below bottom? */
		new_index = count - 1;
	if (new_index == index)         /* same field? */
		new_index = REPEAT;
	return (new_index);
}
.CN
.P
Both character-action and post-action routines are necesary
because the BREAK character entered by the user is normally not known in a
post-action routine.
``mybrkchar'' sets 
.I user_mask
in the 
.I field
structure to the appropriate BREAK character.
The post-action routine then uses this value to determine whether to
page up or down.
This use of 
.I user_mask 
is quite straightforward.
The call to brkchar() with K_HOME is more interesting.
.P
The way we recommend to write a BREAK character action routine is to model
the new BREAK character after another BREAK character.
K_HOME is similar enough to what we want to do.
But in what sense?
To answer this question we have to understand why the above example
works.
The following reduces the flow of control, function calls and
arguments in Tabs to only what is needed to understand this example.
.CW
Get_List (field_list)   /* controls inter-field movement and editing */
{
	next = 0;
	while (next < count)
	{
		index = next;
		ret_code = Get_Field (field_list[index]);
		if (post-action) /* e.g.,  reg_post */
			next = post-action (ret_code,index); 
		if (next == index)
			/* determine ``next'' from ret_code and field_flags*/
	}
}
.CN
.CW
Get_Field (field)   /* controls intra-field movement and editing */.
{
	while (TRUE)
	{
		ch = read_a_char();
		flag = character_action(); /* e.g. mybrkchar */
		if (flag == TRUE)
		{
			switch (some_variable) 
			{
			...
			case K_HOME:
				/* set field_flags and ret_code */
				return (ret_code);
			...
			}
		}
	}
}
.CN
.P
Look first at Get_Field().
When CTRL(D) is typed by the user to page down, the
character action routine (mybrkchar() in this case)
calls brkchar with K_HOME.
As a result, Get_Field sets the field-dependent flags and return
code to the appropriate conditions for K_HOME.
However, mybrkchar() also sets
.I user_mask
to CTRL(D) so that it will be remembered for later use in the post-action
routine.
.P
Now look at Get_List().
If the post-action routine (reg_post() in this case) returns the index
passed to it then the flags and return code set for K_HOME will have
an effect.
But the
.I user_flag
is set to CTRL(D) so the return from reg_post() will not be
the same as the index passed to it.
The post-action routine has a higher priority than flags and return codes
set in Get_Field().
.P
K_HOME was used as the model because it caused
control to be moved to another field within the same list of fields.
K_DOWN, K_UP, etc. would have been just as good a model.
See the description of Def_Char_Action() for the complete list of standard
BREAK characters and break character types.
.P
The type of interactions between routines shown here can be used
between character-action routines and any type of pre-action or post-action
routine.
This extensibility provides a powerful mechanism for creating a wide 
variety of special character directives.
.H 1 "Constructing Application Defined Field Types"
New field types may be created by the application programmer.  If the
application requires a novel data type that is not included in the Tabs
library, the application may construct its own field type.  A typical
application supplied field type can be created with less than 20 lines
of C source code.  Application created field types are especially
important for handling data base applications that cannot know until run
time what the data will look like.
.P
Each field type procedure has two operations that must be performed.
First the procedure must verify the end user's input.  The second operation
included with every field type is to supply help.  In the example in
Appendix G the verification part of the field is handled in the lines
between 115 and 128.  This code is very general.  The test at lines 115
and 116 can be replaced with another string comparison to produce
whatever type is required.  The rest of the code between 117 and 128
would remain the same.
.P
The help part of the example lies between 98 and 113.  The two error
arguments to cm_start() are the error messages to be displayed if
the field is empty and the user has entered a confirmation character or a
completion character.  The procedure call to prhlp() on line 109 sends
the string argument to the pop-up help window.  The strings on lines 98
and 109 are obviously field type specific, but the rest of the code could
be used for most other arbitrary field types.
.so field.mm
.SG cdb
.NS 4
References
Appendices A,B,C,D,E,F, and G
.NE
.SK
.H 1 "References"
.RL
.LI
Teitelman, Warren, ``A Display Oriented Programmer's Assistant'',
CSL 77-3, Xerox Palo Alto Research Center, March 8, 1977.
.LI
Montgomery, Warren,
``An Interactive Screen Editor'', BTL Technical Memorandum 80-5343.2,
April 14, 1980.
.LI
Horton, Mark R., ``The New Curses and Terminfo Package'', Bell
Laboratories internal publication TM 82-59473-8, August 2, 1982.
.LI
Blewett, Douglas ``Tabs:  A Window Based, Extensible, Highly Typed, Electronic 
Forms Package'', AT&T Bell Laboratories internal publication TM 83-45411-10,
December 7, 1983.
.LI
Hicks, K.I. ``A Menu Toolkit'', AT&T Bell Laboratories internal publication
TM 11386-850322-01, March 22, 1985.
.LI
Hicks, K.I. ``Managing Related Windows and Forms'', AT&T Bell Laboratories internal publication
TM 11386-850409-01, April 9, 1985.
.LE
.SK
.HU "Appendix A - A Sample Form"
.sp 2
.CW
 .
_______________________________________________________________________________


                      Media Industries Inventory Systems

                            New Arrivals Entry Form


          Item         Quantity     Origin       Amount
      ____________       __10       _______      ___0.29   =          2.90

      ____________       ____       _______      _______   =             0


                                                               ===========

                                                                      2.90
                               Confirm:*




_______________________________________________________________________________

.CN
.SK
.HU "Appendix B - Form with a Help Window"
.sp 2
.CW
 .
_______________________________________________________________________________


                      Media Industries Inventory Systems

                            New Arrivals Entry Form


          Item         Quantity     Origin       Amount
      blits for me       __10       B?_____      3400.00   =      34000.00

      3bX's_____----------------------------------------   =     500000.00
                |  Options:                            |
                |   Boston                             |
                |Enter the city of origin.  This is    |       ===========
                |the shipment origin.  Do NOT use the  |
                |city of manufacture.                  |         534000.00
                |                                      |
                |                                      |
                ----------------------------------------


_______________________________________________________________________________

.CN
.SK
.HU "Appendix C - Forms Demonstrating Multiple Windows"
.sp 2
.CW
 .
_______________________________________________________________________________


        --------------------------------------------------------------
        |                          Field9                            |
        |                                                            |
        |         Field Type: confirm                                |
        |           Keywords: ___________________________________    |
        |     Decimal Digits: _                                      |
      bl|       Lowest Value: ___________________________________    |0.00
        |      Highest Value: ___________________________________    |
      3b|    Background Text: *__________________________________    |0.00
  ---------------------------------------------------------          |
  |              New Field Help Information               |          |
  |                                                       |_______   |====
  | More: yes  Value: Press the return key when you are__ |n: yes    |
  | More: no_  Value: ___________________________________ | _        |0.00
  | More: ___  Value: ___________________________________ |          |
  | More: ___  Value: ___________________________________ |-----------
  |                                                       |
  ---------------------------------------------------------

_______________________________________________________________________________

.CN
.SK
.HU "Appendix D - C Based Form"
.CW
 .
    1	#include <stdio.h>
    2	#include <setjmp.h>
    3	#include "vt.h"
    4	#include "windows.h"
    5	#include "fields.h"
    6	
    7	main ()
    8	{
    9		struct field_item *f[2];
   10	
   11		Start_Form (0, 0);
   12	
   13	/*
   14	 *	Define Field 0
   15	 *
   16	 */
   17		f[0] = New_Field(10, 40, CMNUM, "_______",
   18				0, "3,-123.55,123.00");
   19	
   20		Set_Attributes (f[0], FARIGHT);
   21	
   22		Set_Label (f[0], "l", "A Number:", FANORMAL);
   23	
   24	
   25	/*
   26	 *	Define Field 1
   27	 *
   28	 */
   29		f[1] = New_Field(12, 40, CMCFM, "_",
   30		    "Please Press Return when you are ready to proceed.",
   31		    0);
   32	
   33		Set_Label (f[1], "l", "Confirm:", FANORMAL);
   34	
   35	/*
   36	 *	Process the fields
   37	 *
   38	 */
   39		Print_Center (stdwindow, 1, FAREVV, "A Sample Form");
   40	
   41		Show_List (f, 2);
   42	
   43	 	Get_List (f, 2, FALSE, FALSE);
   44	
   45		End_Form ();
   46	}
.CN
.SK
.HU "Appendix E - More Complex C Based Form
.CW
 .
    1	#include <stdio.h>
    2	#include <setjmp.h>
    3	#include "vt.h"
    4	#include "windows.h"
    5	#include "fields.h"
    6	
    7	main ()
    8	{
    9		extern int beep ();
   10	
   11		int i;
   12		struct field_item *f[6];
   13	
   14		Start_Form (0, 0);
   15	
   16		Def_Interrupt (beep);			    /* Catch Interrupt */
   17	
   18		errwindow -> _type_scroll = FALSE;  /* MIT scroll Help */
   19	
   20		Print_Center (stdwindow, 1, FAREVV, "A Sample Form");
   21	
   22	/*
   23	 *	Field 0 - a keyword
   24	 *
   25	 */
   26		f[0] = New_Field(6, 33, CMKEY, "__________________",
   27				"Enter a sample keyword.",
   28				"a few key words to choose from");
   29	
   30		Set_Label (f[0], "l", "Keyword: ", FANORMAL);
   31	
   32	/*
   33	 *	Field 1 - a centered string
   34	 *
   35	 */
   36		f[1] = New_Field(8, 33, CMSTR, "__________________",
   37				"Enter a line of characters.", 0);
   38	
   39		Set_Label (f[1], "l", "String: ", FANORMAL);
   40	
   41		Set_Attributes (f[1], FACENTER);
   42	
   43	/*
   44	 *	Field 2 - a file name
   45	 *
   46	 */
   47		f[2] = New_Field(10, 33, CMFILE, "__________________",
   48				"Enter a sample filename.",
   49				"1");
   50	
   51		Set_Label (f[2], "l", "Filename: ", FANORMAL);
   52	
   53	/*
   54	 *	Field 3 - an environmental variable
   55	 *
   56	 */
   57		f[3] = New_Field(12, 33, CMENV, "__________________",
   58				0, 0);
   59	
   60		Set_Label (f[3], "l", "Environ: ", FANORMAL);
   61	
   62	/*
   63	 *	Field 4 - a right justified decimal number
   64	 *
   65	 */
   66		f[4] = New_Field(14, 33, CMNUM, "__________________",
   67				0, "3,-123.55,123.00");
   68	
   69		Set_Label (f[4], "l", "Number: ", FANORMAL);
   70	
   71		Set_Attributes (f[4], FARIGHT);
   72	
   73	/*
   74	 *	Field 5 - a carriage return
   75	 *
   76	 */
   77		f[5] = New_Field(16, 33, CMCFM, "_",
   78		    "Please press return when you are ready to proceed.",
   79		    0);
   80	
   81		Set_Label (f[5], "l", "Confirm: ", FANORMAL);
   82	
   83	
   84	/*
   85	 *	Set the fields so that ^B and ^F (cursor pad and mouse)
   86	 *		work no verify and no "onetime"
   87	 *
   88	 *	Set the fields to auto advance - tab when full
   89	 */
   90		for (i = 0; i < 6; i++)
   91		{
   92			Set_Tab_Movement (f[i], TRUE, FALSE, TRUE, FALSE, FALSE);
   93			Set_Auto_Advance (f[i], TRUE);
   94		}
   95	
   96		Show_List (f, 6);
   97	
   98		Get_List (f, 6, FALSE, FALSE);
   99	
  100		Print_Message (stdwindow, FANORMAL, "Bye!");
  101	
  102		End_Form ();
  103	}
.CN
.SK
.HU "Appendix F - C Based Form Using a Scrollable Region"
.CW
 .
    1	#include <stdio.h>
    2	#include <setjmp.h>
    3	#include "vt.h"
    4	#include "windows.h"
    5	#include "fields.h"
    6	
    7	main ()
    8	{
    9		struct field_item      *f[4];
   10		struct field_item      *fline;
   11		struct field_item      *fcfcfm;
   12		struct field_item      *fregion[20];
   13		struct SWindow  setup_window;
   14		struct window  *reg_window;
   15	
   16		Start_Form (0, 0);
   17	
   18		Print_Center (stdwindow, 1, FANORMAL,
   19				"Media Industries Electronic Mail");
   20	
   21	/*
   22	 *	Create the To: line field
   23	 *
   24	 */
   25		f[0] = New_Field (4, 29, CMSTR, "____________________",
   26				"Enter the list of people ... ",
   27				0);
   28		Set_Label (f[0], "l", "To: ", FANORMAL);
   29		Set_Tab_Movement (f[0], TRUE, TRUE, TRUE, TRUE, FALSE);
   30		Set_Auto_Advance (f[0], TRUE);
   31	
   32	/*
   33	 *	Create the Subject: line field
   34	 *
   35	 */
   36		f[1] = New_Field (5, 29, CMSTR, "____________________",
   37				"Enter the subject of the message. ...",
   38				0);
   39		Set_Label (f[1], "l", "Subject: ", FANORMAL);
   40		Set_Tab_Movement (f[1], TRUE, TRUE, TRUE, TRUE, FALSE);
   41		Set_Auto_Advance (f[1], TRUE);
   42	
   43	/*
   44	 *	Create the scrollable region for creating mail the message
   45	 *
   46	 *	REGION: Create the window first
   47	 *
   48	 */
   49		setup_window.top_x = 9;
   50		setup_window.top_y = 12;
   51		setup_window.lines = 6;
   52		setup_window.cols = 50;
   53		setup_window.box_h = '-';
   54		setup_window.box_v = '|';
   55		setup_window.type_scroll = TRUE;
   56		setup_window.depth = 6;
   57		setup_window.box_attribute = 0;
   58		reg_window = New_Window (setup_window);
   59	
   60	/*
   61	 *	REGION: Create the one line field for the message
   62	 *
   63	 */
   64		fline = New_Field (0, 0, CMSTR,
   65			"_________________________________________________",
   66			"Enter a line of text for the message.",
   67			0);
   68		Set_Tab_Movement (fline, TRUE, FALSE, TRUE, FALSE, FALSE);
   69		Set_Auto_Advance (fline, TRUE);
   70	
   71	/*
   72	 *	REGION: Link the one line field to allow blank lines
   73	 *		The user may enter a line of text or
   74	 *		hit the tab or return keys.
   75	 *
   76	 */
   77		fcfcfm = New_Field (0, 0, CMCFM,
   78			"_________________________________________________",
   79			0, 0);
   80		Link_Fields (fline, fcfcfm);
   81	
   82		Set_EOF (fline, TRUE, TRUE);	/* Allow exit by EOF */
   83	
   84	/*
   85	 *	REGION: Create the scrollable region and add it to the list
   86	 *		of fields.
   87	 *
   88	 */
   89		New_Region (reg_window, &fline, 1, 20, fregion, 1);
   90	
   91		f[2] = New_Field (9, 12, CMREGN,
   92				(char *) fregion, (char *) 20, 0);
   93	
   94	/*
   95	 *	Create a confirmation field that will be collected
   96	 *		after the scrollable region
   97	 *
   98	 */
   99		f[3] = New_Field (17, 29, CMCFM, "_", 0, 0);
  100		Set_Label (f[3], "l", "Confirm: ", FANORMAL);
  101		Set_Tab_Movement (f[3], TRUE, TRUE, TRUE, TRUE, FALSE);
  102	
  103	/*
  104	 *	Process the form
  105	 *
  106	 */
  107		Show_List (f, 4);
  108	
  109		Get_List (f, 4, FALSE, FALSE);
  110	
  111		End_Form ();
  112	}
.CN
.SK
.HU "Appendix G - A Form with an Application Supplied Field Type"
.CW
 .
    1	#include <stdio.h>
    2	#include <setjmp.h>
    3	#include "vt.h"
    4	#include "windows.h"
    5	#include "fields.h"
    6	
    7	/*
    8	 * This program demonstrates the use of application defined
    9	 * field types.  The field created with this example is a
   10	 * regular expression field.
   11	 */
   12	
   13	main ()
   14	{
   15		struct field_item *f[3];
   16		extern int cmregex ();
   17		extern int change_help ();
   18	
   19		Start_Form (0, 0);
   20	
   21		Print_Center (stdwindow, 1, FANORMAL,
   22			"Regular Expression Matching Example");
   23	
   24	/*
   25	 *	Create the string field to collect the regular expression
   26	 *
   27	 */
   28		f[0] = New_Field (5, 38, CMSTR, "____________________",
   29			 "Enter the regular expression ... ",
   30				0);
   31		Set_Label (f[0], "left", "Expression: ", FANORMAL);
   32		Set_Tab_Movement (f[0], TRUE, TRUE, TRUE, TRUE, FALSE);
   33		Set_Auto_Advance (f[0], TRUE);
   34	
   35	/*
   36	 *	The application defined regular expression field
   37	 *
   38	 */
   39		f[1] = New_Field (7, 38, CMSTR, "____________________",
   40				0,
   41				0);
   42		Set_Label (f[1], "left", "Matching Pattern: ", FANORMAL);
   43		Set_Tab_Movement (f[1], TRUE, FALSE, TRUE, FALSE, FALSE);
   44		Set_Auto_Advance (f[1], TRUE);
   45		Set_Actions (f[1], change_help, 0);
   46	
   47	/*
   48	 *	Change the type to the application supplied routine
   49	 *
   50	 */
   51		f[1] -> type = cmregex;
   52	/*
   53	 *	Set the keyword list used by cmregex to the compiled regular
   54	 *	expression.  The pre_action routine will in this program
   55	 *	re-compile the expression with each pass.  The following
   56	 *	line (or one with a different expression) would be used
   57	 *	in an example where the regular expression did not change.
   58	 *
   59	 */
   60		f[1] -> keywords = (char *) regcmp ("^[a-c][0-9]{1,3}$", 0);
   61	
   62	/*
   63	 *	Create a confirmation field that will be collected last
   64	 *
   65	 */
   66		f[2] = New_Field (9, 38, CMCFM, "_", 0, 0);
   67		Set_Label (f[2], "left", "Confirm: ", FANORMAL);
   68		Set_Tab_Movement (f[2], TRUE, TRUE, TRUE, TRUE, FALSE);
   69	
   70	/*
   71	 *	Process the form
   72	 *
   73	 */
   74		Show_List (f, 3);
   75	
   76		Show_Default_Field (f[0], "^[a-c][0-9]{1,3}$");
   77	
   78		Get_List (f, 3, FALSE, FALSE);
   79	
   80		End_Form ();
   81	}
   82	
   83	/*
   84	 *	cmregex (field_ptr)
   85	 *
   86	 *	This function matches an arbitrary string with
   87	 *	a regular expression.
   88	 */
   89	
   90	cmregex (field_ptr)
   91	register struct field_item     *field_ptr;
   92	{
   93		extern char *__loc1;
   94		extern char *regex ();
   95		char *rc;
   96		char *error;
   97	
   98		error = "Cannot match or complete the expression";
   99	
  100		if (!cm_start (field_ptr, error, error)) return;
  101	
  102		if (field_ptr -> cmflg & CMHLP)
  103		{
  104			field_ptr -> cmflg |= CMNOP;
  105	
  106			if (field_ptr -> fnflg & FNHLP)
  107				return;
  108	
  109			prhlp (field_ptr, "Enter pattern to be matched.",
  110				FALSE, FALSE);
  111	
  112			return;
  113		}
  114	
  115		rc = regex (field_ptr -> keywords, field_ptr -> txbuf);
  116		if ((rc != NULL) && (__loc1 == field_ptr -> txbuf))
  117		{
  118			if (field_ptr -> cmflg & CMCMP)
  119			{
  120				complete (field_ptr, field_ptr -> txbuf);
  121				field_ptr -> cmflg |= CMREP;
  122			}
  123			return;
  124		}
  125	
  126		error_fields = error;
  127		field_ptr -> cmflg |= CMNOP;
  128		return;
  129	}
  130	
  131	/*
  132	 * Pre-action routine for the regular expression routine.  This is
  133	 * added fluff that could be handled more directly in cmregex (), but
  134	 * gives us a little experience with Set_Help () and action routines.
  135	 *
  136	 */
  137	change_help (f, count, index, rc)
  138	struct field_item     **f;
  139	int     count;
  140	int     index;
  141	int     rc;
  142	{
  143		static char help_buf[128];
  144		char *ptr;
  145	
  146		ptr = (char *) regcmp (f[0] -> txbuf, 0);
  147	
  148		if (ptr == NULL)
  149		{
  150			beep ();
  151			Print_Message (f[1] -> meswin, FANORMAL,
  152				"The regular expression does not compile.");
  153			return (count);	/* Exit from the list */
  154		}
  155	
  156		if (f[1] -> keywords)
  157			free (f[1] -> keywords);
  158	
  159		f[1] -> keywords = ptr;
  160	
  161		sprintf (help_buf,
  162			"Enter a string that will match the pattern \"%s\".",
  163			f[0] -> txbuf);
  164	
  165		Set_Help (f[1], help_buf, FALSE, FALSE, 0);
  166	
  167		return (index);
  168	}
.CN
.TC 1 1 9
.CS 38 12 50 0 3 3
