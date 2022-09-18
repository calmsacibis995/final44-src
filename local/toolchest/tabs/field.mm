.SK
.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.H 1 "The Field Structure"
This section describes the main data structure used by Tab.  This
section is provided mainly for insight.  Most application developers do
not need to know these specifics.  The access procedures should be used
whenever possible.
.P
.ne 39
The following is the current field definition.
.CW
struct field_item
{
        int     x_pos;
        int     y_pos;
        int     (*type) ();
        int     (*type_used) ();
        int     length;
        char   *fill_char;
        char   *ext_fill_char;
        char   *keywords;

        struct  window  *window;
        struct  window  *errwin;
        struct  window  *meswin;

        int     attribute;
        int     user_mask;
        char   *user_pointer;

        int     (*read_routine) ();
        int     (*pre_action) ();
        int     (*post_action) ();
        int     (*help_routine) ();

        int     txflg;
        char   *txbuf;
        char   *txend;
        char   *txptr;
        char   *txcursor;

        int     fnflg;
        char   *fnhlp;
        char   *fnerr;
        char   *fndfs;
        int     fndfv;
        struct  field_item  *fnalt;

        int     cmflg;

        struct  label_item  *label;
};
.CN
The entries in the structure are used as follows:
.BL
.LI
int x_pos
.br
.sp 1
This is the row position of the field in the window.
.LI
int y_pos
.br
.sp 1
This is the column position of the field in the window.
.LI
int (*type) ()
.br
.sp 1
This is the type of the field.  Tab currently supports the following
generic types.
.DL
.LI
CMKEY \(em keywords
.LI
CMKEY_LIST \(em keyword list (from struct keys)
.LI
CMCFM \(em confirm a command (new line)
.LI
CMSTR \(em string
.LI
CMNUM \(em number
.LI
CMFILE \(em UNIX file
.LI
CMENV \(em environmental variable
.LI
CMREGN \(em scrollable region
.LE
.P
Applications may also specify their own field types (see the section on
constructing application defined field types).
.LI
int (*type_used) ()
.br
.sp 1
This is the type of the field that was entered.  This is the verified
field type.  This acts as a return value for the field type.  This is
useful for input fields that have alternate field links (see
Link_Field()).
.LI
int length
.br
.sp 1
This is the length of the field in characters.
.LI
char *fill_char
.br
.sp 1
This is the background text.
.LI
char *ext_fill_char
.br
.sp 1
This is the background text for extendable fields.  This string is
the background for the fully extended field.
.LI
char *keywords
.br
.sp 1
This is the list of keywords for keyword fields.
.LI
struct window *window
.br
.sp 1
This is the pointer to the window from which the field is to be read.
.LI
struct window *errwin
.br
.sp 1
This is the pointer to the help window.  Help messages are printed in
this window.
.LI
struct window *meswin
.br
.sp 1
This is the pointer to the message window.  Print_Message() style error
messages are printed on the last line of this window.  ``meswin'' and
``window'' are usually the same window.
.LI
int attribute
.br
.sp 1
This is the attribute flag.  The following attributes are supported.
.DL
.LI
FARIGHT \(em right justify the field
.LI
FACENTER \(em center the field
.LI
FALEFT \(em left justify the field
.LI
FAREVV \(em reverse video
.LI
FAHALF \(em half intensity
.LI
FAUNDER \(em underline
.LI
FABLINK \(em blink
.LI
FABOLD \(em bold
.LI
FACASE \(em ignore the case of keyword matches
.LI
FAPROTECT \(em protect the field so the user can not change its content
.LI
FAINVISIBLE \(em invisible \(em field content is displayed as spaces
.LE
.LI
int user_mask
.br
.sp 1
This is an extra integer for use by the application only.
.LI
char *user_pointer
.br
.sp 1
This is an extra pointer for use by the application only.
.LI
int (*read_routine) ()
.br
.sp 1
This is a pointer to the routine that will be used to read the users
input.  This is used for creating fields that have some minimal
constraint on the range of input characters.
.LI
int (*pre_action) ()
.br
.sp 1
This is a pointer to the application supplied pre-action routine.
.LI
int (*post_action) ()
.br
.sp 1
This is a pointer to the application supplied post-action routine.
.LI
int (*help_routine) ()
.br
.sp 1
This is a pointer to the application supplied help routine.
.LI
int txflg
.br
.sp 1
This is a flag used internally by Tab.  The value of the flag reflects
the current state of input for the field.
.LI
char *txbuf
.br
.sp 1
The string pointed to with txbuf contains the current contents of
the field.
.LI
char *txend
.br
.sp 1
This is a pointer used internally by Tab.  It marks the end of the
string pointed to by txbuf.
.LI
char *txptr
.br
.sp 1
This is a pointer used internally by Tab for specifying the end of the
user's input string.
.LI
char *txcursor
.br
.sp 1
This is a pointer used internally by Tab for specifying the location of
the cursor in the user's input string.
.LI
int fnflg
.br
.sp 1
This is a flag used to control help functions within Tab.
.LI
char *fnhlp
.br
.sp 1
This is a pointer to the application supplied help string.
.LI
char *fnerr
.br
.sp 1
This is a pointer to the application supplied error message.
.LI
char *fndfs
.br
.sp 1
This is a pointer to the completion default for the field.
.LI
int fndfv
.br
.sp 1
This is an integer that is used as a modifier for certain field types (e.g
CMFILE and CMNUM).
.LI
struct field_item *fnalt
.br
.sp 1
This is the pointer to an alternate field.  This is used for reading
more than one type from a given field.
.LI
int cmflg
.br
.sp 1
This flag contains the status of the field.
.LI
struct label_item *label
.br
.sp 1
This is the pointer to the first label for the field.
.LE
