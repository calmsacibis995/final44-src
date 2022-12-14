h58307
s 00002/00000/00923
d D 8.3 94/06/01 18:29:54 ah 9 8
c page breaks for the 4.4BSD manuals
e
s 00001/00001/00922
d D 8.2 94/04/20 05:35:02 bostic 8 7
c SHARED, not Berkeey
e
s 00002/00002/00921
d D 8.1 93/06/08 18:11:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00921
d D 5.6 93/06/05 15:52:46 bostic 6 5
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00003/00919
d D 5.5 91/04/17 09:48:29 bostic 5 4
c new copyright; att/bsd/shared
e
s 00025/00025/00897
d D 5.4 86/04/28 17:15:06 mckusick 4 3
c fix pagination; rewrite abstract
e
s 00003/00001/00919
d D 5.3 86/04/15 14:01:36 mckusick 3 2
c from mis
e
s 00132/00077/00788
d D 5.2 85/09/05 15:42:14 mckusick 2 1
c update from jerry for 4.3BSD
e
s 00865/00000/00000
d D 5.1 85/09/05 15:33:03 mckusick 1 0
c version distributed with 4.2BSD
e
u
U
t
T
I 1
D 5
.\" Copyright (c) 1980 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 7
.\" Copyright (c) 1985 The Regents of the University of California.
.\" All rights reserved.
E 7
I 7
.\" Copyright (c) 1985, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 7
.\"
D 8
.\" %sccs.include.redist.man%
E 8
I 8
.\" %sccs.include.proprietary.man%
E 8
E 5
.\"
.\"	%W% (Berkeley) %G%
.\"
I 3
D 6
.EH 'PS1:3-%''Introduction to the f77 I/O Library'
.OH 'Introduction to the f77 I/O Library''PS1:3-%'
E 6
I 6
.EH 'PSD:9-%''Introduction to the f77 I/O Library'
.OH 'Introduction to the f77 I/O Library''PSD:9-%'
E 6
E 3
.de Fo
Fortran\\$1
..
.de Sm
\s-1\\$1\s0
..
.\"
.\"	Nh macro - same as NH but also saves heading for table of contents
.\"	Nh usage: Nh level string, e.g.:  .Nh 2 "Calculator Sample"
.de Nh
.NH \\$1
\\$2
.XS
.if '2'\\$1' .ti .25i
.if '3'\\$1' .ti .5i
\\*(SN \\$2
.XE
.PP
..
.ND ""
.\" .nr ll 7.0i
.\" .nr LL 7.0i
.\" .po 0.0i
.\" .rm PT
.\" .rm BT
D 3
.RP
E 3
I 3
.\".RP
E 3
.TL
Introduction to the f77 I/O Library
.AU
David L. Wasley
I 4
.AU
J. Berkman
E 4
.AI
University of California, Berkeley
Berkeley, California 94720
.AB
D 4
.LP
The f77 I/O Library implements
E 4
I 4
The f77 I/O library, libI77.a,
includes routines to perform all of the standard types of
.Fo
input and output specified in the
E 4
.Sm ANSI
1978
.Fo
D 4
standard
input and output
with a few minor exceptions.
Where the standard is vague, we have tried to provide flexibility
within the constraints of the
E 4
I 4
standard.
The I/O Library was written originally by Peter J. Weinberger at Bell Labs.
Where the original implementation was incomplete,
it has been rewritten to more closely implement the standard.
Where the standard is vague,
we have tried to provide flexibility within the constraints of the
E 4
.UX
operating system.
D 4
The I/O Library was written originally by Peter J. Weinberger at Bell Labs.
E 4
A number of logical extensions and enhancements have been provided
D 4
by this author.
E 4
I 4
such as the use of the C stdio library routines to provide
efficient buffering for file I/O.
.sp 2
E 4
.LP
D 4
April 1983
.LP
D 2
Revised for 4.3 BSD, June, 1985.
E 2
I 2
Revised for 4.3 BSD, September, 1985 by J. Berkman.
E 2
.LP
E 4
I 4
Revised September, 1985
E 4
.AE
D 4
.PP
The f77 I/O library, libI77.a,
includes routines to perform all of the standard types of
.Fo
input and output.
Several enhancements and extensions to
.Fo
I/O have been added.
The f77 library routines use the C stdio library routines to provide
efficient buffering for file I/O.
.sp 1
E 4
I 4
.LP
.\" page 2 is allocated to the table of contents
.pn 3
.bp
E 4
.Nh 1 "Fortran I/O"
The requirements of the
.Sm ANSI
standard impose significant overhead
on programs that do large amounts of I/O. Formatted I/O can be
very ``expensive'' while direct access binary I/O is usually very efficient.
Because of the complexity of
.Fo
I/O,
some general concepts deserve clarification.
D 2
.Nh 2 "Types of I/O"
There are three forms of I/O:
E 2
I 2
.Nh 2 "Types of I/O and logical records"
There are four forms of I/O:
E 2
.B formatted,
.B unformatted,
I 2
.B list\ directed,
E 2
and
D 2
.B list-directed.
The last is
related to formatted but does not obey all the rules for formatted I/O.
There are two modes of access to
E 2
I 2
.B namelist.
The last two are
related to formatted but do not obey all the rules for formatted I/O.
There are two types of ``files'':
E 2
.B external
and
.B internal
D 2
files:
E 2
I 2
and two modes of access to files:
E 2
.B direct
and
.B sequential.
The definition of a logical record depends upon the
D 2
combination of I/O form and mode specified by the
E 2
I 2
combination of I/O form, file type, and access mode specified by the
E 2
.Fo
I/O statement.
D 2
.Nh 3 "Direct access"
E 2
I 2
.Nh 3 "Direct access external I/O"
E 2
A logical record in a
.B direct
access
.B external
file is a string of bytes
of a length specified when the file is opened.
Read and write statements must not specify logical records longer than
the original record size definition. Shorter logical records are allowed.
.B Unformatted
direct writes leave the unfilled part of the record undefined.
.B Formatted
direct writes cause the unfilled record to be padded with blanks.
D 2
.Nh 3 "Sequential access"
E 2
I 2
.Nh 3 "Sequential access external I/O"
E 2
Logical records in
.B sequentially
accessed
.B external
files may be of arbitrary
and variable length.
Logical record length for
.B unformatted
sequential files is determined by
the size of items in the iolist.
The requirements of this form of I/O cause the external physical
record size to be somewhat larger than the logical record size.
For
.B formatted
write statements, logical record length is determined by
the format statement interacting with the iolist at execution time.
The ``newline'' character is the logical record delimiter.
Formatted sequential access causes one or more logical records
ending with ``newline'' characters to be read or written.
D 2
.Nh 3 "List directed I/O"
E 2
I 2
.Nh 3 "List directed and namelist sequential external I/O"
E 2
Logical record length for
D 2
.B list-directed
E 2
I 2
.B list\ directed
and
.B namelist
E 2
I/O is relatively meaningless.
On output, the record length is dependent on the magnitude of the
data items.
On input, the record length is determined by the data types and the file
contents.
By ANSI definition, a slash, ``/'', terminates execution of a
D 2
list-directed input operation.
E 2
I 2
list directed input operation.
Namelist input is terminated by ``&end'' or ``$end'' (depending on whether
the character before the namelist name was ``&'' or ``$'').
E 2
.Nh 3 "Internal I/O"
The logical record length for an
.B internal
read or write is the length of the
character variable or array element. Thus a simple character variable
is a single logical record. A character variable array is similar to
a fixed length direct access file, and obeys the same rules.
.B Unformatted
D 2
I/O is not allowed on "internal" files.
E 2
I 2
and
.B namelist
I/O are not allowed on ``internal'' files.
E 2
.Nh 2 "I/O execution"
Note that each execution of a
.Fo
.B unformatted
I/O statement causes a single
logical record to be read or written. Each execution of a
.Fo
.B formatted
I/O statement causes one or more logical records to be read or written.
.PP
A slash, ``/'', will terminate assignment of
values to the input list during
D 2
.B list-directed
E 2
I 2
.B list\ directed
E 2
input and the remainder of the current input line is skipped.
The standard is rather vague on this point but seems to require that
a new external logical record be found at the start of any formatted
input. Therefore data following the slash is ignored and may be used
to comment the data file.
.PP
D 2
.B "Direct access list-directed"
E 2
I 2
.B "Direct access list directed"
E 2
I/O is not allowed.
.B "Unformatted internal"
I/O is not allowed.
D 2
Both the above will be caught by the compiler.
E 2
I 2
.B Namelist
I/O is allowed only with
.B "external sequential"
files.
E 2
All other flavors of I/O are allowed, although some are not part of the
.Sm ANSI
standard.
.PP
D 2
Any error detected during I/O processing will cause the program to abort
unless alternative action has been provided specifically in the program.
E 2
Any I/O statement may include an
.B err=
D 2
clause (and
E 2
I 2
clause to specify an alternative branch to be taken on errors
and/or an
E 2
.B iostat=
D 2
clause)
to specify an
alternative branch to be taken on errors (and return the specific error code).
E 2
I 2
clause to return the specific error code.
Any error detected during I/O processing will cause the program to abort
unless either
.B err=
or
.B iostat=
has been specificed in the program.
E 2
Read statements may include
.B end=
to branch on end-of-file.
The end-of-file indication for that logical unit may be reset with
a \fBbackspace\fP statement.
File position and the value of I/O list items is undefined following an error.
.sp 1
.Nh 1 "Implementation details"
Some details of the current implementation may be useful in understanding
constraints on
.Fo
I/O.
.Nh 2 "Number of logical units"
Unit numbers must be in the range 0 \- 99.
The maximum number of logical units that a program may have open at one
time is the same as the
.UX
system limit, currently 48.
.Nh 2 "Standard logical units"
By default, logical units 0, 5, and 6
are opened to ``stderr'', ``stdin'', and ``stdout'' respectively.
However they can be re-defined with an 
.B open
statement.
To preserve error reporting, it is an error to close logical unit 0
although it may be reopened to another file.
.PP
If you want to open the default file name for any preconnected logical unit,
remember to 
.B close
the unit first.
Redefining the standard units may impair normal console I/O.
An alternative is to
use shell re-direction to externally re-define the above units.
To re-define default blank control or format of the standard input or output
files, use the 
.B open
statement specifying the unit number and no
file name (see \(sc\|2.4).
.PP
The standard units, 0, 5, and 6, are named internally ``stderr'', ``stdin'',
and ``stdout'' respectively.
These are not actual file names and can not be used for opening these units.
.B Inquire
will not return these names and will indicate
that the above units are not named unless they have been opened to real files.
The names are meant to make error reporting more meaningful.
.Nh 2 "Vertical format control"
Simple vertical format control is implemented. The logical unit must be opened
for sequential access with
.B "form = \(fmprint\(fm"
(see \(sc\|3.2).
Control codes ``0'' and ``1'' are replaced in the output file
with ``\\n'' and ``\\f'' respectively.
The control character ``+'' is not implemented and, like
any other character in the first position of a record
written to a ``print'' file, is dropped.
I 2
The
.B "form = \(fmprint\(fm"
mode does not recognize vertical format control for
.B "direct formatted, list directed,"
or
.B "namelist"
output.
E 2
.PP
An alternative is to use
the filter \fIfpr\fP(1) for vertical format control.
It replaces ``0'' and ``1'' by
``\\n'' and ``\\f'' respectively, and implements the ``+'' control code.
Unlike
.B "form = \(fmprint\(fm"
which drops unrecognized form control characters, \fIfpr\fP copies those
characters to the output file.
D 2
.PP
No vertical format control is recognized for
.B "direct formatted"
output
or
.B "list directed"
output.
E 2
.Nh 2 "File names and the open statement"
A file name may be specified in an \fBopen\fP statement for the
logical unit.
If a logical unit is opened by an \fBopen\fP statement which does
not specify a file name, or it is opened implicitly by the execution
D 2
of a \fBread\fP, \fBwrite\fP, \fBbackspace\fP or \fBrewind\fP
statement, then the default file name is ``fort.N'' where N is
the logical unit number.
E 2
I 2
of a \fBread\fP, \fBwrite\fP, or \fBendfile\fP
statement, then the default file name is
.I fort.N
where
.I N
is the logical unit number.
E 2
Before opening the file, the library checks for an environment
variable with a name identical to the tail of the
file name with periods removed.\(dg
.FS
\(dgPeriods are deleted because they can not be part of environment variable names in the Bourne shell.
.FE
D 2
If it finds such an environment variable, it uses it's value
E 2
I 2
If it finds such an environment variable, it uses its value
E 2
as the actual name of the file.
For example, a program containing:
.DS
D 2
open(32,file="/usr/guest/census/data.d")
E 2
I 2
open(32,file=\(fm/usr/guest/census/data.d\(fm)
E 2
read(32,100) vec
write(44) vec
.DE
normally will read from \fI/usr/guest/census/data.d\fP and write to
\fIfort.44\fP in the current directory.
If the environment variables \fIdatad\fP and \fIfort44\fP are set,
e.g.:
.DS
% setenv datad mydata
% setenv fort44 myout
.DE
in the C shell or:
.DS
$ datad=mydata
$ fort44=myout
$ export datad fort44
.DE
in the Bourne shell, then the program will read from \fImydata\fP and
write to \fImyout\fP.
.PP
An
.B open
statement need not specify a file name. If it refers to a logical
unit that is already open, the 
.B blank=
and 
.B form=
specifiers may be
redefined without affecting the current file position.
Otherwise, if
.B "status = \(fmscratch\(fm"
is specified, a temporary file with a
D 2
name of the form ``tmp.FXXXXXX'' will be opened,
E 2
I 2
name of the form
.I tmp.FXXXXXX
will be opened,
E 2
and, by default, will be deleted when closed or during
termination of program execution.
.PP
It is an error to try to open an existing file with
.B "status = \(fmnew\(fm"
\&.
It is an error to try to open a nonexistent file with
.B "status = \(fmold\(fm"
\&.
By default,
.B "status = \(fmunknown\(fm"
will be assumed, and a file will be created if necessary.
.PP
By default, files are positioned
at their beginning upon opening, but see \fIfseek\fP(3f)
and \fIioinit\fP(3f) for alternatives.
Existing files are never truncated on opening.
Sequentially accessed external files are truncated to the current file
position on \fBclose\fP, \fBbackspace\fP, or \fBrewind\fP only if the last
access to the file was a write.
An
.B endfile
always causes such files to be truncated to the current
file position.
.Nh 2 "Format interpretation"
Formats which are in format statements are parsed by the compiler;
formats in \fBread\fP, \fBwrite\fP, and \fBprint\fP statements
are parsed during execution by the
.Sm I/O
library.
Upper as well as lower case characters are recognized in format statements
and all the alphabetic arguments to the I/O library routines.
.PP
If the external representation of a datum
is too large for the field width specified, the specified
field is filled with asterisks (\(**).
On \fBE\fPw.d\fBE\fPe output,
the exponent field will be filled with asterisks if the
exponent representation is too large.
This will only happen if ``e'' is zero (see appendix B).
.PP
On output, a real value that is truly zero will display as ``0.'' to
distinguish it from a very small non-zero value.
If this causes problems for other input systems, the
\fBBZ\fP edit descriptor may be used to cause the field
following the decimal point to be filled with zero's.
.PP
Non-destructive tabbing is implemented for both internal and external
formatted I/O.
Tabbing left or right on output
does not affect previously written portions of a record.
Tabbing right on output
causes unwritten portions of a record to be filled with blanks.
Tabbing right off the end of an input logical record is an error.
Tabbing left beyond the beginning of an input logical record leaves
the input pointer at the beginning of the record.
The format specifier
.B T
must be followed by a positive non-zero number.
If it is not, it will have a different meaning (see \(sc\|3.1).
.PP
Tabbing left requires seek ability on the logical unit.
Therefore it is not allowed in I/O to a terminal or pipe.
Likewise, nondestructive tabbing in either direction is possible
only on a unit that can seek. Otherwise tabbing right or spacing with
.B X
will write blanks on the output.
I 9
.sp
E 9
.Nh 2 "List directed output"
In formatting list directed output, the I/O system tries to prevent
output lines longer than 80 characters.
Each external datum will be separated by two spaces.
D 2
List-directed output of
E 2
I 2
List directed output of
E 2
.B complex
values includes an appropriate comma.
D 2
List-directed output distinguishes between
E 2
I 2
List directed output distinguishes between
E 2
.B real
and
.B "double precision"
D 2
values
and formats them differently.
E 2
I 2
values and formats them differently.
E 2
Output of a character string that includes ``\\n''
is interpreted reasonably by the output system.
.Nh 2 "I/O errors"
If I/O errors are not trapped by the user's program an appropriate
error message will be written to ``stderr'' before aborting.
An error number will be printed in ``[ ]'' along with a brief error message
showing the logical unit and I/O state.
Error numbers < 100 refer to
.UX
errors, and are described in the
introduction to chapter 2 of the
.UX
Programmer's Manual.
Error numbers \(>= 100 come from the I/O library, and are described
D 2
further in the appendix to this writeup.
E 2
I 2
further in the appendix to this writeup\(dd.
.FS
\(dd On many systems, these are also available in \fIhelp f77 io_err_msgs\fP.
.FE
E 2
For internal I/O, part of the string will be printed with ``|'' at the
current position in the string.
For external I/O, part of the current record will be displayed if
the error was caused during reading from a file that can backspace.
.sp 1
.Nh 1 "Non-``ANSI Standard'' extensions"
Several extensions have been added to the I/O system to provide
for functions omitted or poorly defined in the standard.
Programmers should be aware that these are non-portable.
.Nh 2 "Format specifiers"
.B B
D 2
is an acceptable edit control specifier. It causes return to the
E 2
I 2
is an acceptable edit control specifier. It causes return to the logical unit's
E 2
default mode of blank interpretation.
This is consistent with
.B S
which returns to default sign control.
.PP
.B P
by itself is equivalent to
.B 0P
\&. It resets the scale factor to the
default value, 0.
.PP
The form of the \fBE\fPw.d\fBE\fPe format specifier has been extended to
.B D
also.
The form \fBE\fPw.d.e is allowed but is not standard.
The ``e'' field specifies the minimum number of digits or spaces in the
exponent field on output.
If the value of the exponent is too large, the exponent notation
.B e
or
.B d
will be dropped from the output to allow one
more character position.
If this is still not adequate, the ``e'' field will be filled with
asterisks (\(**).
The default value for ``e'' is 2.
.PP
An additional form of tab control specification has been added.
The
.Sm ANSI
standard forms \fBTR\fPn, \fBTL\fPn, and \fBT\fPn are supported
where
.I n
is a positive non-zero number.
If
.B T
or n\fBT\fP is specified, tabbing will
be to the next (or n-th) 8-column tab stop.
Thus columns of alphanumerics can be lined up without counting.
.PP
A format control specifier has been added to suppress the newline
at the end of the last record of a formatted sequential write. The
specifier is a dollar sign ($). It is constrained by the same rules
as the colon (:). It is used typically for console prompts.
For example:

.DS
write (\(**, "(\(fmenter value for x: \(fm,$)")
read (\(**,\(**) x
.DE
.PP
Radices other than 10 can be specified for formatted integer I/O
conversion. The specifier is patterned after
.B P,
the scale factor for
floating point conversion. It remains in effect until another radix is
specified or format interpretation is complete. The specifier is defined
as [n]\fBR\fP where 2 \(<= \fIn\fP \(<= 36. If
.I n
is omitted,
the default decimal radix is restored.
.PP
The format specifier \fBO\fPm.n may be used for an octal conversion;
it is equivalent to 8\fBR,I\fPm.n,10\fBR\fP.
Similarly, \fBZ\fPm.n is equivalent to 16\fBR,I\fPm.n,10\fBR\fP and
may be used for an hexadecimal conversion;
.PP
In conjunction with the above, a sign control specifier has been added
to cause integer values to be interpreted as unsigned during output
conversion. The specifier is
.B SU
and remains in effect until another
sign control specifier is encountered, or format interpretation is
D 2
complete.
E 2
I 2
complete.\(dg
.FS
\(dgNote: Unsigned integer values greater than (2\(**\(**31 - 1),
can be read and written using \fBSU\fP.
However they can not be used in
computations because
.Fo
uses signed arithmetic and such values appear to the arithmetic unit
as negative numbers.
.FE
I 9
.ne 1i
E 9
E 2
Radix and ``unsigned'' specifiers could be used to format
a hexadecimal dump, as follows:

.DS
2000  format ( SU, 8Z10.8 )
.DE

D 2
Note: Unsigned integer values greater than (2\(**\(**30 - 1),
i.e. any signed negative value, can not be read by
.Fo
input routines.
All internal values will be output correctly.
E 2
.Nh 2 "Print files"
The
.Sm ANSI
standard is ambiguous regarding the definition of a ``print'' file.
Since
.UX
has no default ``print'' file, an additional
.B form=
specifier
is now recognized in the
.B open
statement.
Specifying
.B "form = \(fmprint\(fm"
implies
.B formatted
and enables vertical format
control for that logical unit (see \(sc\|2.3).
Vertical format control is interpreted only on sequential formatted writes
to a ``print'' file.
.PP
The
.B inquire
statement will return
.B print
in the
.B form=
string variable
for logical units opened as ``print'' files.
It will return -1 for the unit number of an unconnected file.
.PP
If a logical unit is already open, an
.B open
statement including the
.B form=
option or the
.B blank=
option will do nothing but re-define those options.
This instance of the
.B open
statement need not include the file name, and
must not include a file name if
.B unit=
refers to a standard input or output.
Therefore, to re-define the standard output as a ``print'' file, use:

.DS
open (unit=6, form=\(fmprint\(fm)
.DE
.Nh 2 "Scratch files"
A
.B close
statement with
.B "status = \(fmkeep\(fm"
may be specified for temporary files.
This is the default for all other files.
Remember to get the scratch file's real name,
using
.B inquire
\&, if you want to re-open it later.
.Nh 2 "List directed I/O"
List directed read has been modified to allow
tab characters wherever blanks are allowed.
It also allows input of a string not enclosed in quotes.
The string must not start with a digit or quote,
and can not contain any separators ( ``,'', ``/'', blank or tab ).
A newline will terminate the string unless escaped with \\.
Any string not meeting the above restrictions
must be enclosed in quotes (`` " '' or `` \(fm '').
.PP
D 2
Internal list-directed I/O has been implemented. During internal list reads,
E 2
I 2
Internal list directed I/O has been implemented. During internal list reads,
E 2
bytes are consumed until the iolist is satisfied, or the ``end-of-file''
is reached.
During internal list writes, records are filled until the iolist is satisfied.
The length of an internal array element should be at least 20 bytes to
avoid logical record overflow when writing double precision values.
Internal list read was implemented to make command line decoding easier.
Internal list write should be avoided.
I 2
.Nh 2 "Namelist I/O"
Namelist I/O is a common extension in Fortran systems.
The \fBf77\fP version was designed to be compatible with other
vendors versions;
it is described in ``A Portable Fortran 77 Compiler'',
by Feldman and Weinberger, August, 1985.
E 2
.sp 1
.Nh 1 "Running older programs"
Traditional
.Fo
environments usually assume carriage control on all logical units,
usually interpret blank spaces on input as ``0''s, and often provide
attachment of global file names to logical units at run time.
There are several routines in the I/O library to provide these functions.
.Nh 2 "Traditional unit control parameters"
If a program reads and writes only units 5 and 6, then including
.B \-lI66
in the f77 command will cause carriage control to be interpreted on
output and cause blanks to be zeros on input without further
modification of the program.
If this is not adequate,
the routine \fIioinit\fP(3f) can be called to specify control parameters
separately, including whether files should be positioned at their
beginning or end upon opening.
.Nh 2 "Ioinit()"
\fIIoinit\fP(3f) can be used to attach logical units
to specific files at run time, and to set global parameters for the
.Sm I/O
system.
It will look for names of a user specified form in the environment
and open the corresponding logical unit for
.B "sequential formatted"
I/O. Names must be of the form \fB\s-1PREFIX\s0\fP\fInn\fP where
.B \\s-1PREFIX\\s0
is specified in the call to
.I ioinit
and
.I nn
is the logical unit to be opened. Unit numbers < 10 must include
the leading ``0''.
.PP
.I Ioinit
should prove adequate for most programs as written.
However, it
is written in
.Fo \-77
specifically so that it may serve as an example for similar
user-supplied routines.
A copy may be retrieved by ``ar x /usr/lib/libU77.a ioinit.f''.
See \(sc\|2.4 for another way to override program file names
through environment variables.
.sp 1
.Nh 1 "Magnetic tape I/O"
Because the I/O library uses stdio buffering, reading or writing
magnetic tapes should be done with great caution, or avoided if possible.
A set of routines has been provided to read and write arbitrary sized buffers
to or from tape directly. The buffer must be a
.B character
object.
.B Internal
I/O can be used to fill or interpret the buffer.
These routines do not use normal
.Fo
I/O processing and do not obey
.Fo
I/O rules.
See \fItopen\fP(3f).
.sp 1
.Nh 1 "Caveat Programmer"
The I/O library is extremely complex yet we believe there are few bugs left.
We've tried to make the system as correct as possible according to
the
.Sm ANSI
X3.9\-1978 document and keep it compatible with the
.UX
file system.
Exceptions to the standard are noted in appendix B.
.bp
D 2
.ce 3
Appendix A
E 2
I 2
.DS C
.B "Appendix A"
E 2

D 2
I/O Library Error Messages
E 2
I 2
.B "I/O Library Error Messages"
.DE
E 2
.XS
Appendix A: I/O Library Error Messages
.XE
.sp 1
.PP
The following error messages are generated by the I/O library.
D 2
The error numbers are returned in the \fBiostat=\fP.
E 2
I 2
The error numbers are returned in the \fBiostat=\fP variable.
E 2
Error numbers < 100 are generated by the
.UX
kernel.
See the introduction to chapter 2 of the
.UX
Programmers Manual for their description.
.nr PD 0
.de Er
.ne 4v
.IP \\$1
D 2
"\\$2"
E 2
I 2
\fI\\$2\fP
E 2
.br
..
.RS

.Er 100 "error in format"
See error message output for the location
of the error in the format. Can be caused
by more than 10 levels of nested parentheses, or
an extremely long format statement.

.Er 101 "illegal unit number"
It is illegal to close logical unit 0.
Unit numbers must be between 0 and 99 inclusive.

.Er 102 "formatted i/o not allowed"
The logical unit was opened for
unformatted I/O.

.Er 103 "unformatted i/o not allowed"
The logical unit was opened for
formatted I/O.

.Er 104 "direct i/o not allowed"
The logical unit was opened for sequential
access, or the logical record length was
specified as 0.

.Er 105 "sequential i/o not allowed"
The logical unit was opened for direct
access I/O.

.Er 106 "can't backspace file"
The file associated with the logical unit
can't seek. May be a device or a pipe.

.Er 107 "off beginning of record"
The format specified a left tab beyond the
beginning of an internal input record.

.Er 108 "can't stat file"
The system can't return status information
about the file. Perhaps the directory is
unreadable.

D 2
.Er 109 "no * after repeat count"
Repeat counts in list-directed I/O must be
followed by an * with no blank spaces.
E 2
I 2
.Er 109 "no \(** after repeat count"
Repeat counts in list directed I/O must be
followed by an \(** with no blank spaces.
E 2

.Er 110 "off end of record"
A formatted write tried to go beyond the
logical end-of-record. An unformatted read
or write will also cause this.

.Er 111 "truncation failed"
The truncation of an external sequential file on
D 2
``close'', ``backspace'', ``rewind'' or ``endfile'' failed.
E 2
I 2
.B close ,
.B backspace ,
.B rewind ,
or
.B endfile
failed.
E 2

.Er 112 "incomprehensible list input"
List input has to be just right.

.Er 113 "out of free space"
The library dynamically creates buffers for
internal use. You ran out of memory for this.
Your program is too big!

.Er 114 "unit not connected"
The logical unit was not open.

.Er 115 "invalid data for integer format term"
Only spaces, a leading sign and digits are allowed.

.Er 116 "invalid data for logical format term"
Legal input consists of spaces (optional), a period (optional), and then
a ``t'', ``T'', ``f'', or ``F''.

D 2
.Er 117 "\(fmnew\(fm file exists"
E 2
I 2
.Er 117 "\|\(fmnew\|\(fm file exists"
E 2
You tried to open an existing file with
D 2
"status=\(fmnew\(fm".
E 2
I 2
``status=\|\(fmnew\|\(fm''.
E 2

D 2
.Er 118 "can't find \(fmold\(fm file"
E 2
I 2
.Er 118 "can't find \|\(fmold\|\(fm file"
E 2
You tried to open a non-existent file
D 2
with "status=\(fmold\(fm".
E 2
I 2
with ``status=\|\(fmold\|\(fm''.
E 2

.Er 119 "opening too many files or unknown system error"
Either you are trying to open too many files
simultaneously or there has been an undetected system error.

.Er 120 "requires seek ability"
Direct access requires seek ability.
Sequential unformatted I/O requires seek
ability on the file due to the special
data structure required. Tabbing left
also requires seek ability.

.Er 121 "illegal argument"
D 2
Certain arguments to 'open', etc. will be
checked for legitimacy. Often only non-
default forms are looked for.
E 2
I 2
Certain arguments to
.B open ,
etc. will be
checked for legitimacy. Often only non-default
forms are looked for.
E 2

.Er 122 "negative repeat count"
The repeat count for list directed input
must be a positive integer.

.Er 123 "illegal operation for unit"
An operation was requested for a device
associated with the logical unit which
was not possible. This error is returned
by the tape I/O routines if attempting to
read past end-of-tape, etc.

D 2
.Er 124 "invalid data for d,e,f or g format term"
E 2
I 2
.Er 124 "invalid data for d, e, f or g format term"
E 2
Input data must be legal.
I 2

.Er 125 "illegal input for namelist"
Column one of input is ignored, the namelist name
must match, the variables must be in the namelist,
and the data must be of the right type.
E 2
.if n .nr PD 1v
.if t .nr PD 0.3v
.RE
.bp
D 2
.ce 3
Appendix B
E 2
I 2
.LP
.DS C
.B "Appendix B"
E 2

D 2
Exceptions to the ANSI Standard
E 2
I 2
.B "Exceptions to the ANSI Standard"
.DE
E 2
.XS
Appendix B: Exceptions to the ANSI Standard
.XE
.sp 1
.PP
A few exceptions to the
.Sm ANSI
standard remain.
I 2
.sp 1
E 2
.LP
D 2
1) Vertical format control
E 2
I 2
.B "Vertical format control"
E 2
.PP
The ``+'' carriage control specifier is not fully implemented
(see \(sc\|2.3).
It would be difficult to implement it correctly and still
provide
.UX -like
file I/O.
.PP
Furthermore, the carriage control implementation is asymmetrical.
A file written with carriage control interpretation can not be
read again with the same characters in column 1.
.PP
An alternative to interpreting carriage control internally is to
run the output file through a ``Fortran output filter''
before printing. This filter could recognize a much broader range
of carriage control and include terminal dependent processing.
One such filter is \fIfpr\fP(1).
.sp 1
.LP
D 2
2) Default files
E 2
I 2
.B "Default files"
E 2
.PP
Files created by default use of
D 2
.B rewind
or
E 2
.B endfile
statements are opened for
.B "sequential formatted"
access. There is no way to redefine such a file to allow
.B direct
or
.B unformatted
access.
.sp 1
.LP
D 2
3) Lower case strings
E 2
I 2
.B "Lower case strings"
E 2
.PP
It is not clear if the
.Sm ANSI
standard requires internally generated strings to be upper case or not.
As currently written, the
.B inquire
statement will return lower case strings for any alphanumeric data.
.sp 1
.LP
D 2
4) Exponent representation on Ew.dEe output
E 2
I 2
.B "Exponent representation on Ew.dEe output"
E 2
.PP
If the field width for the exponent is too small, the standard
allows dropping the exponent character but only if the exponent
is > 99. This system does not enforce that restriction.
D 2
Further, the standard implies that the entire field, `w', should be
E 2
I 2
Further, the standard implies that the entire field, ``w'', should be
E 2
filled with asterisks if the exponent can not be displayed.
This system fills only the exponent field in the above case since
that is more diagnostic.
I 2
.sp 1
.LP
.B "Pre-connection of files"
.PP
The standard says units must be pre-connected to files before the program
starts or must be explicitly opened.
Instead, the I/O library
connects the unit to a file on its first use in a
\fBread\fP, \fBwrite\fP, \fBprint\fP, or \fBendfile\fP statement.
Thus \fBinquire\fP by unit can not tell prior to a unit number use the
characteristics or name of the file corresponding to a unit.
E 2
D 4
.TC
E 4
I 4
.\" want Table of Contents to begin on page 2 hence must expand body
.\" of .TC macro to enable us to get handle on page number.
.pn 2
.bp
.PX
E 4
E 1
