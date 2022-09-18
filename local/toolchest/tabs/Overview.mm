.nr Hb 6
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
.ND "November 9, 1983"	<<< and so on >>>
.ND "December 7, 1983"
.TL 11153-0231 49343-190
Tabs: A Window Based, Extensible, Highly Typed, Electronic Forms Package
.AU "C. Douglas Blewett" CDB
.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.TM 83-45411-10
.AS 1
Tabs is a software system for producing ``window'' based user interfaces
for interactive data processing applications.  Tabs includes excellent
help facilities which are invoked only when requested.  The help and
other features are designed for both novice and expert users.  Tabs
allows for terse abbreviation of commands, easy editing and verification
of data, and graceful recovery from input errors.
.P
Application developers create Tabs forms using a set of C based
libraries.  The input fields include several field types, which can be
combined within any given field.  Most aspects of the Tabs interface may
be extended by the application developer.  For example the developer may
attach an arbitrary C function to any input character.  The developer
may also add new field types as they are needed.
.AE
.OK "Interpreters and Emulators" "Human Engineering" "Command and Control Systems"
.MT 4
.H 1 "Introduction"
The Tabs package is a software system for producing ``window'' based
user interfaces for interactive data processing applications.  The Tabs
end user interface provides an elegant, interactive front end to
application programs.  This interface is desirable for both novice (i.e.
casual) and expert (i.e. frequent) users[3,4,11].  Tabs allows terse
abbreviation of commands and provides detailed help on demand.  Tabs
also allows the end user to gracefully recover from input errors.  Users
may edit, resubmitted, and/or verified the input data as they require it.
.P
The application developer's interface is also unusual.  Many forms
systems run as a separate ``at-arms-length'' process.  Application
developers use Tabs as a set of libraries that are loaded with the
application code.  This means that the application developer who is
knowledgeable in C does not need to learn a new language and/or a new set
of software development tools.  This C based approach also encourages
developers to share Tabs extensions as libraries.
.P
The electronic forms produced using Tabs may be conceptualized as a
collection of controlled input and output areas within CRT based
windows.  The input areas, called input fields, may be moved within and
between windows while the form is running.  More than one window may be
used at a time.  Like fields, the windows may also be moved if the
application requires it.
.P
The window based interface is similar in function to the display manager
found in Teitelman's Programmer's Assistant[9].  CRT windows are
constructed with a portable virtual terminal library.  The window based
virtual terminal creates windows as three dimensional rectangular
objects.  Windows that are ``closer'' to the user occlude more distant
windows.  In this environment, windows may be moved to arbitrary spatial
positions on a CRT screen and in depth.  Tabs, while based primarily on
virtual terminal technology, has an enriched interface on intelligent,
bit mapped terminals like the Blit[7].
.P
The Tabs applications interface provides a number of standard field
types.  Unlike more traditional forms packages where fields are simple
strings or numbers, Tabs field types are high level data types.  For
example the standard field types include filenames with full wild
carding and verification.
.P
Another significant feature is that a field may be used for collecting
more than one type of data item.  An application may require a filename,
a number, or a null response from the end user.  Old fashioned boiler
plate forms applications are restricted to one data type per field,
usually strings or numbers.  Tabs allows all of these data types to be
read from the same field.
.P
New field types may be created by the application programmer.  If the
application requires a novel data type that is not included in the Tabs
library, the application may construct its own field type.  For example,
a regular expression field type was created with less than twenty lines of C
source code.  Application created field types are especially important
for handling data base applications that cannot know until run time what
the data will look like.
.P
Forms and editor interfaces have much in common.  One editor can not
possibly suit everyones taste.  Editors like EMACS[8] allow the user to
extend the editor to meet unforeseeable user needs.  Similarly, everyone
has a personal opinion about how electronic forms should work.  Tabs
allows the application developer to customize individual electronic
forms by defining procedures for handling the various aspects of the
Tabs interface.
.P
There are several areas where Tabs allows application defined procedures
to be used to extend or enhance the functionality of the Tabs interface.
These areas run the gamut from very low level read routines to the
application defined field types mentioned above.  All of these
application supplied extensions allow for fine control of the behavior
of the electronic form with a minimum of programmer intervention.
.H 1 "Tabs Philosophy as an Interface Tool"
The following is a discussion of the concepts upon which Tabs is based.
This section and section three below discuss end user features, Tabs as an
interface.  Sections four and five below discuss Tabs in terms of its
usefulness to the application developer, Tabs as a software tool.
.P
The end user should always appear to be in control of the software
system.  This is a cardinal rule of interface design and the most
central theme in the Tabs design.  The locus of control always appears
to be on the end user's side of the keyboard.  For example, verification
of fields occurs at the user's request in Tabs based forms.  Help is
provided only when it is requested by the user.  Error messages explain
how to get help, but do not force the user into help scenarios.
.P
Extending the notion of the end user having ultimate control,
Tabs allows for easy recovery from user produced errors.  The end user
may edit and re-enter fields.  Editing includes cursor movement and
character insert/delete operations from within the field.  Arbitrary
editing operations may also be added by the application developer.
.P
Tabs encourages the use of complete words for keywords.  For example
``-all'' is as easy to use as ``-a'' for both the end user and the
application developer.  Tabs's built-in abbreviation capability
encourages this.  Keywords may be abbreviated to the smallest initial
sequence of characters that uniquely specifies the keyword.  The end
user may also request that Tabs expand the abbreviation to the complete
keyword.  Tabs always returns the complete keyword to the application.
.P
Expert users tend to prefer terse interactions (e.g. abbreviation and no
help), while novices require more verbose feedback.  The user is
encouraged to become more proficient (i.e. an expert user).  Movement
from novice to expert user is expected with normal use of Tabs.  No
special variables or flags have to be set to access either novice or
expert user features.
.P
Unlike older ``boiler plate'' style forms, forms produced using Tabs are
dynamic.  Exception conditions may be handled dynamically.  Help
messages are displayed in a separate ``pop-up'' window.  Similarly, data
not frequently collected from users may be collected in a window that
appears only when needed.  In addition, Tabs includes many features that are
difficult or impossible to do with older mask oriented forms.  For
example, Tabs may look for more than one type of item per field (e.g. a
file name or a keyword).  These features can greatly improve the
application interface for the end user and are essential for producing
modern data base interfaces, like Query-by-Example[12] and
Office-by-Example[13].
.H 1 "Tabs End User Interface"
The Tabs end user interface can be thought of as having essentially two
aspects, the CRT or screen displays and user input.  The input side of
the interface includes normal character input and Tabs command
characters.  The screen displays include fields and printed strings,
both contained within windows.  The following section describes the
screen displays and the next section describes user input features.
.H 2 "CRT Displays"
The interface is maintained via terminal virtualizing software.  The
environmental variable ``TERM'' is used to determine what type of
terminal is being used.  The following shell commands set the
terminal to be a Concept 100 with eight pages of memory.
.CW
	TERM=c108-8p
	export TERM
.CN
The virtual terminal software currently supports most popular
terminals[5,6].
.H 3 "A Sample Display"
Figure 1 contains a sample form as it might appear on an end user's
terminal.
.DF CB
.if t
.PS < form1.pic
..
.FG "A Simple Form"
.DE
Tabs has most of the commonly used features for input fields,
output fields, and printed strings.  Features for printing strings
include arbitrary screen placement and formatting (e.g. centering).  Tabs
also provides facilities to handle calculated or constructed values as
in printed strings (i.e. output only fields).
.P
Input fields may include labels (in four directions), background text,
default values, and special formating.  Input fields may also have
auto-tab attributes (advance when full), enter only once, and a host of
other modern form attributes.  The forms package also allows the end user
to use mouse and function keys when they are available to aid in filling
out complex forms.
Section 3.2 has more information on user input.
.H 3 "Using Pop-up Help Windows"
Figure 2 contains a partially completed form.
The user has requested
help in the third field.  Help messages are always displayed in a
separate window.  Simple error or warning messages are displayed on the
last line of the current window.
.P
.DF CB
.if t
.PS < form2.pic
..
.FG "A Simple Form with the Help Window in Use"
.DE
.P
Help messages have two parts, a text message and a qualifying list or
annotation.  The text part is the usual verbose type of message, often
used to explain what a particular input field is about.  The qualifying
list is extra information that Tabs constructs based on the field type.
For keywords the list is the list of keywords. For filenames the list is
the list of matching files.  For environmental variables the list is the
list of variable names.  For numeric fields the list is the range.
Either or both of these help message parts may be disabled by the
programmer per the requirements of the application.  In addition, an
application may specify a procedure to be run whenever help is requested.
.H 3 "A Multi-window Display"
Tabs is designed to produce dynamic forms.  The application may add,
move, and delete fields and windows as needed.  Using a dynamic forms
approach can greatly streamline the end user interface.  Forms need not
contain fields that are seldom used.  Seldom used fields may be moved
onto the form when an exception condition arises.  Exception conditions
may also be handled as separate forms running in a separate ``pop-up''
window.  Figure 3 is an example of this ``on demand'' type of strategy.
This figure demonstrates an application that is using two pop-up style
form windows.  The top two windows are being used to collect information
that is not commonly requested from the end user.
.DF CB
.if t
.PS < form3.pic
..
.FG "A Multi-Window Tabs Example"
.DE
.H 2 "End User Input"
The input side of the interface includes normal character input and Tabs
commands.  Normal characters are read by Tabs and subsequently passed
onto the application program as parsed items.  The command characters
are termed character directives.  Character directives request specific
actions from the Tabs system.  The action requested may be an editing
operation within the field, movement to another field, a request to have
the current field completed and/or verified, or a request for help.  In
choosing, special character directives an attempt has been made to make
use of current UNIX standards (e.g. ERASE and KILL).  Some consideration
has also been given to selecting a portable and reasonable (e.g.
mnemonic) set for commands not currently widely used in standard UNIX.
Note that all of these commands may be re-assigned by the application
developer.
.H 3 "Completion and Verification Commands"
The following commands allow the end user to verify the validity
of the current input string.  This verification process takes on several
forms.  The most verbose type of validity checking is to request the
help information.  The tersest form of validity checking is to TAB to the
next field.  If the field is invalid Tabs will complain, other wise Tabs
will move to the next input field.
.BL
.ne 4
.LI
? \(em Help request
.br
.sp 1
The help request will cause the help window to be displayed.
Application and Tabs supplied help messages will be printed within it.
For keywords the list of matching keywords is given.  For file names the
list of matching (i.e. wild card matches) file names will be printed.
For shell variables the list of matching shell variables is listed.  For
numbers the range and number of digits behind the decimal is printed.
.ne 4
.LI
Control-I (TAB) \(em Validate the field and move to the next field
.br
.sp 1
TAB is the field confirmation character.  This will cause the current
field to be validated and program control to move to the next field.
Carriage return and new line characters may also be used as confirmation
characters.
.ne 4
.LI
Control-[ (ESCAPE) \(em Completion request
.br
.sp 1
ESCAPE is the completion request key.  Keywords and
filenames are expanded to their longest printable representation.
Numbers are expanded to include the correct number of digits behind the
decimal place.  If the current contents of the field are not valid
an error message is printed and no expansion is performed.  In
fields where auto advance has been set program control will also move to
the next field.
.LE
.H 3 "Inter-Field Movement Commands"
The following commands allow the end user to move from field to
field.  Movement may be disabled for any field.  To further complicate the
picture, the movement may be set so that the field will be verified prior
to moving to the requested field.  This set of interfield operations
will satisfy the requirements of most applications.
.BL
.ne 4
.LI
Control-P and the BACK TAB key \(em Move to the previous field
.br
.sp 1
This is the BACK TAB directive.  If BACK TAB movement is
enabled for the field, control will move to the previous field.
.ne 4
.LI
Control-N \(em Move to the next field
.br
.sp 1
This is the FORWARD directive.  If FORWARD movement is
enabled for the field, control will move to the next field.  This
directive differs from the TAB key in that verification may be disabled
for FORWARD initiated movement.
.ne 4
.LI
Cursor Pad Key \(em Movement based on cursor pad keys
.br
.sp 1
Cursor pad initiated movement must be
enabled for these directives to be operative.  Tabs currently supports
the generic function key types listed below.  The control characters
that follow the function key types are supplied for terminals that have
no working function keys or for touch typists who prefer to keep their
hands on the main keyboard.
.so Tabs.keys.mm
.br
.sp 1
The rationale for this key selection is that the keys control-^,
control-T, control-Y, and control-G  match the compass points on most
keyboards.
.DF CB
.if t
.PS < arrow_keys.pic
.sp 1
..
.FG "Keyboard Layout of Arrow Keys Substitutes"
.DE
The other arrow key or cursor pad substitutes are control-A for HOME and
control-Z for BOTTOM.  control-A is also above control-Z on the keyboard.
.ne 4
.LI
Mouse Tracks \(em Movement initiated from a mouse
.br
.sp 1
If the terminal has a mouse or other pointing device Tabs will allow the
user to select the next field by pointing.  Mouse initiated movement
must be enabled for this directive to be operative.
.ne 4
.LI
EOF \(em End of file (usually Control-D)
.br
.sp 1
This is the user specified EOF character.  If EOF capabilities for the
field have been enabled with the Set_EOF() procedure, the current list
of fields will be exited.  This directive is most commonly used to exit
from scrollable regions.
.LE
.H 3 "Editing Commands"
The following commands allow the end user to edit the contents
of the current field.  A few of these commands are determined from the
user's terminal setting.  It should be remembered that the characters
associated with Tabs commands may be changed by the application.  I
am mentioning this again because editing seems to be a highly personal
sort of operation with most experienced users having strong opinions as
to command names, etc.
.BL
.ne 4
.LI
ERASE \(em Erase the last character in the field
.br
.sp 1
This is the user specified erase character.  This will delete the last
character inserted in the field.  The character may be recovered with the
control-O directive.
.ne 4
.LI
KILL \(em Kill or Erase the entire field
.br
.sp 1
This is the user specified kill character.  This will erase the entire field.
The field may be recovered with the control-O directive.
.ne 4
.LI
Control-O \(em Overlay erased characters
.br
.sp 1
Control-O recovers characters that have been erased from the end of the
field with KILL, ERASE, and/or control-W.  This implements a very simple
form of overlay editing.
.ne 4
.LI
Control-W \(em Delete the last word entered
.br
.sp 1
Control-W deletes the last word entered in the field.  This works
essentially like character delete for words.
.ne 4
.LI
Control-B \(em Beginning of the field
.br
.sp 1
Control-B moves the cursor in the field to the beginning of the field.
This allows the user to insert characters at the beginning of the
field.  Characters to the right of the cursor are pushed to the right as
new characters are entered.
.ne 4
.LI
Control-E \(em End of the field
.br
.sp 1
Control-E moves the cursor to the end of the field.  This allows the
user to resume adding characters to the end of the field after some other
editing operation.
.ne 4
.LI
Control-L \(em Left in the field
.br
.sp 1
Control-L moves the cursor left one character in the field.  This allows the
user to add characters at any point within the field.  Characters to the
right of the cursor are pushed to the right as new characters are entered.
.ne 4
.LI
Control-R \(em Right in the field
.br
.sp 1
Control-R moves the cursor right one character in the field.  This allows the
user to add characters at any point within the field.  Characters to the
right of the cursor are pushed to the right as new characters are entered.
.LE
.H 3 "Utility Commands"
The following commands allow the end user to clean up the display.
.BL
.ne 4
.LI
Control-C \(em Clear away error messages and the help window
.br
.sp 1
Control-C causes the help window and error messages to be removed from
the display.  This allows the user to have full unobstructed view of the
form.
.ne 4
.LI
Control-V \(em Verify the screen by refreshing the display
.br
.sp 1
Control-V refreshes the screen.  This is useful for recovering from
``wall'' and ``write'' messages.
.LE
.H 1 "Tabs Philosophy as a Software Tool"
Forms are constructed by calling Tabs procedures or primitives from some
interpreted or compiled language (e.g. C).  Libraries of commonly used
fields may be constructed and maintained using standard software tools.
The details of the implementation are kept from the programmer by a set
of function and procedure calls.  Simple forms require very little
knowledge to construct.  At the same time, more experienced programmers
may construct elaborate forms that include more detailed algorithmic
intervention.
.P
Tabs takes a very high level approach to forms.  The items read are not
simply numbers or strings, but higher level constructs (e.g. filenames
or environmental variables).  Tabs also supports scrollable regions as a
field type.  A scrollable region is a field that may contain many
different types of fields in a scrolling window.
.P
Tabs is extensible.  New field types can be added by application
developers as they are needed.  Tabs also allows the application
developer to use arbitrary C functions for pre and post processing of
every field and for providing help information.  Even the very
low level read routines are available for application substitution.
Unlike most other forms systems the application developer may change, add, or
remove cursor and field movement commands as they are needed.  A typical
command change requires two function calls.
.P
Application programmers have commented that Tabs based forms do not
restrain the programmer.  The Tabs programmer interface is both flexible
and simple to use.
.H 1 "Control Flow Within Tabs"
The following two sections discuss Tabs from the application developer's
point of view.  The first section below discusses producing Tabs based
forms using the Tabs supplied function and procedure calls.  This
section describes how Tabs handles the lists of fields that comprise a
form.  The second section discusses how Tabs works within each field.
The second section is needed to understand how application supplied
extensions are applied in Tabs.
.H 2 "The Upper Levels of the Tabs"
Figure 5 below is a stylized C based form.
.DF CB
.if t
.PS < control.pic
..
.FG "A Stylized C Based Form"
.DE
Most forms use only five Tabs functions, Start_Form(), End_Form(),
New_Field(), Show_List(), and Get_List().  Start_Form() and End_Form()
perform all of the initialization and de-initialization operations. The
function New_Field() creates a new field structure and returns a pointer
to it.  Field structures and arrays of pointers to field structures are
the main data structures manipulated by Tabs.  The procedure Show_List()
displays an array of fields on the end user's terminal.  The bulk of the
processing is handled by the one call to Get_List().
.P
As can be seen in Figure 5, Get_List() performs inter-field movement
operations, executes pre and post action routines, and calls Get_Field()
to collect the end user's input.  Get_Field() gets the end user's input
for one field at a time.
.P
Inter-field movement within Get_List() may be initiated by the
end user via character directives, function keys, or mouse movement.
Inter-field movement may also be initiated by the form itself via the
pre and post action routines.  Normal movement through the form is based
on position within the array of fields and is performed in first to last
order.
.ne 6
Placement of the fields on the end user's terminal is independent of the
order within the array.
The fields may also be placed in different windows*.
.FS *
Windows are created with the New_Window() function.
.FE
.P
The pre and post action routines are functions executed by Get_List()
that return an integer value.  The value returned is the index of the
next field to be executed.  This simple mechanism allows application
supplied routines to arbitrarily control the order within which the
fields are collected.  Pre and post action routines provide
a mechanism for performing extended validation, but they are
also useful for performing needed side effects like data base updates.
Pre and post actions are also used to produce complicated inter-field
directives (e.g. page style processing within scrollable regions).
.H 2 "The Lower Levels of Tabs \(em Get_Field()"
Figure 6 below is a generalized view of the flow of control
through Get_Field().  Control moves in a counter clockwise direction.
This figure demonstrates the stages of processing that raw user input
goes through in a typical Tabs field.
.DF CB
.if t
.PS < read_path.pic
..
.FG "The Read Path from Get_Field()"
.DE
.H 3 "The Input Phase"
Starting in the upper right of Figure 6,
characters are read from the user's terminal one at a time.
Multi-character devices at the user's terminal, for example function
keys or a pointing device, are handled by this part of the
input process.  Function keys are converted to single character generic
keys.  Pointing device generated characters are converted to a generic
key and appropriate secondary values (e.g. X and Y).
.P
The second part of the input process includes performing intra-field
editing and insertion operations.  The input characters are added at the
cursor location to the current field.  A large part of the activity in
this second stage has to do with associating the correct activity with
each character.  There are four general character types.
.BL
.LI
.B Normal
and
.B punctuation
characters are simply inserted into the field.
Punctation characters are used for some editing operations to delimit
word boundaries.
.LI
.B Correction
characters are used to perform editing and some utility
operations.  The editing operations are used for both removing and
recovering characters in the field.  Correction characters are also used for
moving the cursor within the field.
.LI
.B Break
characters are used to signal the end of the input phase and to
request some specific form of verification.  The help request, ``?'',
and TAB command are examples of break characters.
.LE
.P
The last part of the input process is used to bundle up the current
field.  Flags associated with the field are set here to specify the type
of verification that will be performed.
.H 3 "The Verification Phase"
The verification phase is where all of the field type specific
processing takes place.  There are three basic types of verifications:
the display of the help information, completion of the field, and simple
verification of the field.  The display of help information is often the
most involved of the types of verification.  Keywords are a good
example.  Help information for keywords includes a verbose message and a
list of all of the keywords.  The verbose message may be used to describe
the keywords in detail.  Note that the keywords displayed include only
those keywords that include the current contents of the field
as an initial substring.  For filenames, the list part includes all of
the files that match the current contents of the field after wild
carding operations have been performed.
.P
The completion part of the verification phase, initiated by the ESCAPE
character directive, allows the end user to quickly verify the current
contents of the field with a modicum of feedback.  Keywords and
filenames are expanded to their longest printable representation.
Numbers are expanded to include the correct number of digits behind the
decimal place.  If the current contents of the field are not valid
an error message is printed and no expansion is performed.
.P
The last part of the verification phase is simple verification of the
contents of the field.  If no other verification has been requested and
the entry is not a valid item then an error message is printed.  The
error message includes instructions on how to get more detailed help.
If the current entry is not valid, control always returns to the
input phase.
.H 2 "Five Points Where Application Supplied Extensions Are Applied"
Everyone has their own notions about how electronic forms should work.
Tabs allows the application developer to customize individual electronic
forms by defining procedures for handling the various aspects of the
Tabs interface.  There are five entry points where Tabs based
applications may insert local  C based functions
to extend or enhance the functionality of the Tabs interface.
These entry points run the gamut from very low level read routines to
application defined field types.  All of the application supplied extensions
allow for fine control of the behavior of the electronic form with a
minimum of programmer intervention.
.P
Application defined extensions are simple C functions and
procedures that have a uniform calling sequence.  The routines are
called via an indirect reference through a pointer to a procedure or a
function.  This allows the application to efficiently and easily manage
these procedures (i.e. a function may be set in place via a simple
assignment statement) and still maintain reasonable performance (i.e.
calling a function via this sort of indirection is a fast operation).
.H 3 "Application Supplied Pre and Post Action Routines"
It is often desirable to perform some field specific validation before
and/or after data has been collected from an input field.  Another use
of pre and post action routines is the case where some data base update
is to be performed based on the contents of the input field.  The pre
action can test if the data base is available or if the update operation
has already been performed.  The post action routine can be used to
actually perform the data base update.
.P
The procedure Set_Actions() sets the actions for a specific field.  If
there is a pre-action it is executed just prior to reading the field
each time the field is entered.  The post-action routine is executed
each time the field is exited.  These routines give the application
developer a great deal of freedom and control with a minimum of
programmer effort.
.P
The arguments passed to the pre and post action routines are as follows:
.BL
.LI
The list of fields from the call to Get_List().
.LI
The count or number of fields from the call to Get_List().
.LI
The index of the current field (e.g fields[index]).
.LI
The return code from the last call to Get_Field().
.LE
.P
The return value from the pre and post action routines must be an integer.
The return value is used as the next index for Get_List().  Returning
the value passed as the count for the number of fields will always
cause the form to be marked as complete.  Returning the value passed as
the current index will allow processing to proceed as usual.  A minus
one (i.e. -1) return value will cause the current field to be collected
again, including running the pre and post action routines.
.P
The pre and post action routines may be used with the redefinable
character features (see the description below) to implement control
character directives that have some inter-field action.  To avoid having
to set the pre and post actions of every field there exists global pre
and post action routines that may be set by the application.  If both
field specified and global pre and/or post actions are supplied both will
be executed.  The global routines are executed first and the return from
the global actions take precedence over the field specified actions.
.H 3 "An Application Supplied Help Procedure"
Tabs allows the application developer to assign an arbitrary string as
the verbose help message for any input field.  Although this is a good
feature that is missing from many modern forms facilities, it may be
necessary or simpler to construct a procedure for providing help.  A
good example of this is a field that is used to collect the name of a
fellow active user of a time sharing system.  The user's name may be
required to allow interactive, two way communication between the two
users.  The help message in this case must contain the names of people
who are currently logged into the system.  Other examples include most
operations with times and dates.
.P
The procedure Set_Help() allows the application developer to associate a
C based help procedure with a specific field.  The help procedure will
be invoked whenever the end user requests help.  The help procedure has
one argument, a pointer to the field being read.  The help procedure
does not necessarily have to provide help information.  It can be used
for other purposes such as keeping track of the number of help requests.
.H 3 "An Application Supplied Field Type"
New field types may be created by the application programmer.  If the
application requires a novel data type that is not included in the Tabs
library, the application may construct its own field type.  Application
created field types are especially important for handling data base
applications that cannot know until run time what the data will look
like.  One of the first types created was a regular expression field.
This field type checks the user's input against a regular expression
supplied by the application.
.P
Field types defined by the application may be used as all builtin field
types are used in Tabs.  Application supplied field types may be moved and deleted
and shared among fields as any other Tabs field type.  A typical
application supplied field type can be created with less than twenty lines
of C source code.
.H 3 "Application Supplied Character Directives"
The control characters selected for the default character directives for
Tabs are a good set of characters, at least in terms of the human
factors of electronic forms.  Selecting a set of reasonable character
directives that are acceptable to all developers is a common problem
with form systems.  Tabs allows the application developers to select
their own character directives.  Characters may be re-defined at any
time while the form is running.
.P
The procedure Def_Char_Action() is used to re-define characters.
The four arguments to the procedure are as follows:
.AL
.LI
The first argument is the character whose definition is to be altered.
.LI
The second argument is the functional type of character.  There are
four character types, normal, punctuation, correction, and break.  See
section 5.2.1 for a discussion of the four types.
.LI
The third argument is a pointer to the function that will be used to
process the character.  Standard processing functions include, regchar()
for normal and punctuation characters, brkchar() for break characters,
and corchar() for correction characters.  These functions all have the
following format.
.CW
function (field_ptr, which)
struct field_item *field_ptr;
char    which;
{
	/* Body */

	return (TRUE or FALSE);
}
.CN
``field_ptr'' points to the current field.  ``which'' is the character that
was associated with this function.  ``which'' is included so that one
function may be used to handle many different characters.
.LI
The last argument to Def_Char_Action() is the break type.  This is
meaningful only if the character being specified is to be a break
character.  There are six types of break characters.  These different
types refer to internally maintained lists of break characters that are
arranged by function.
.BL
.LI
CM_LIST \(em this is used to specify the cursor movement list of break
characters.  All of the cursor pad keys are included in this list.
.LI
BTAB_LIST \(em this is the BACK TAB list.  The BACK TAB key and
control-P, previous field, are included in this list.  Some people also
add control-N, next field, to this list.
.LI
TAB_LIST \(em this is the TAB list.  The TAB key is included in this list.
If the developer defines a key other than control-I as the TAB key, TAB_LIST
should be used as the break type for the new character.
.LI
CFM_LIST \(em this is the list of characters that are allowed as
confirmation characters.  The default list includes carriage return and
line feed.
.LI
EOF_LIST \(em this is the list of characters that may be used as
end\-of\-file characters.  The default list includes the user's specified EOF
character, usually control-D.
.LI
UTIL_LIST \(em this list is intended for BREAK characters that have some
intra-field specific action.  ESCAPE and ``?'' are included in this
list.
.LE
.LE
.P
The following code fragment could be used to set control-X to take on the
function of the TAB directive (i.e. control-I) and to change TAB to be a
normal, self inserting character.
.CW
main ()
{
        ~
	Def_Char_Action (CTRL(I), NORMAL, regchar, 0);
	Def_Char_Action (CTRL(X), BREAK, brkchar, TAB_LIST);
	~
}
.CN
.H 3 "An Application Supplied Reader"
Tabs philosophy on input is that verification only occurs when the end
user requests it.  In some instances verification should occur on a
character by character basis.  Some people feel that numerical input
falls in this category.  Tabs allows application developers to create
their own read routines.  The procedure Set_Reader() sets the read
routine for a specific field.
.ne 8
The read routine has one argument, a
pointer to the field being processed.  The read routine may perform
whatever verification operations are required.  It must return an
integer containing the last valid character read.
.ne 8
.H 1 "Future Work"
.H 2 "A Tabs Visual Editor"
We have designed, but not yet implemented a two dimensional or visual
editor for constructing Tabs based forms.  The editor allows the
application developer to interactively create C based forms.  This
includes string and field placement.  The interface is for the most part
a ``what you see is what you get'' process.  Fields and strings are
moved interactively on the screen.  The screen always reflects the true
current state of the form under construction.
.P
Input fields and printed strings are totally specified via pop-up forms.
Abstract concepts like scrollable regions and linked fields are also
handled with pop-up forms.  The notion behind this type of interface is
that the forms creator need not be an expert in terms of forms or the C
programming language in order to create forms.  The editor also allows
expert users to create and modify forms without having to reference a bulky
manual.
.P
The editor creates a C initialization routine that may be added to an
existing C main program.  The form may also be used as a
stand alone program or as a shell based tool.  For shell based
operations a default main program is generated.  The default program
displays and collects the input fields.  Once the fields have been
collected they are echoed onto standard error for further processing.
.H 2 "Mailing Forms"
We are also interested in mailing forms as a method for producing
true office automation[1,2,10].  By embedding the Tabs primitives in a good
interpreter, Tabs based programs may be easily mailed from system to
system.  The recipient of the mailed form decides whether or not
the form will be run.  This could be handled with a very simple dialogue
between the end user and the mail reading program.  If they decide to
run the form, the appropriate interpreter would be invoked and the
information collected and processed.  Because Tabs forms are entirely
algorithmically defined this mailing process is quite easily handled.
There is only one entity to be transmitted.
.SG cdb
.NS 3
References
.NE
.SK
.H 1 "References"
.RL
.LI
Ellis, C.A. and Nutt, G.J., ``Office Information Systems and Computer
Science'', Computing Surveys, Vol. 12, No. 1, March 1980.
.LI
Ellis, C.A., and Bernal, Marc, ``OFFICETALK-D: An experimental office
information system'', presented at the ACM SIGOA Conference on Office
Information Systems, June 21, 1982.
.LI
Hayes, P., Ball, E., and Reddy, R., ``Breaking the Man-Machine
Barrier'', Computer March 1981, pp. 19-30.
.LI
Hirsh-Pasek, K., Nudelman, S., Schneider, M. L., ``An experimental
evaluation of abbreviation schemes in limited lexicons'', Behavior and
Information Technlogy, Vol. 1, No. 4, 359-369, 1982,
.LI
Horton, Mark R., ``The New Curses and Terminfo Package'', Bell
Laboratories internal publication TM 82-59473-8, August 2, 1982.
.LI
Montgomery, Warren, ``An Interactive Screen Editor'', Bell Laboratories
internal publication TM 80-5343.2, April 14, 1980.
.LI
Pike, Rob, ``The Blit Programmer's Manual (TTY Edition)'',  Bell
Laboratories internal publication, December 1982.
.LI
Stallman, R.M., ``EMACS - The Extensible, Customizable, Self-Documenting
Display Editor'', MIT AI Memo no. 519, June 22, 1979.
.LI
Teitelman, Warren, ``A Display Oriented Programmer's Assistant'', CSL
77-3, Xerox Palo Alto Research Center, March 8, 1977.
.LI
Tsichritzis, D., ``Form Management'', Communications of the ACM,
Vol. 25, No. 7, July 1982.
.LI
Uhlir, S.A., ``Comnd - A routine to handle command line parsing'',
Bell Laboratories internal publication TM 78-3231-1, May 10, 1978.
.LI
Zloof, M.M., ``Query-by-Example: A data base language'', IBM Systems
Journal, Vol. 16, No. 4, 324-343, 1977.
.LI
Zloof, M.M., ``Office-by-Example: A business language that unifies data
and word processing and electronic mail'', IBM Systems Journal,
Vol. 21, No. 3, 1982.
.LE
.CS 14 1 15 6 1 13
