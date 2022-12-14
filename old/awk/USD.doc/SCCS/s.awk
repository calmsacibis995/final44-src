h48459
s 00003/00000/01410
d D 8.2 94/06/01 18:55:40 ah 9 8
c page breaks for the 4.4BSD manuals
e
s 00000/00000/01410
d D 8.1 93/08/14 10:59:09 mckusick 8 5
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00003/01407
d R 6.4 93/08/03 13:37:53 elan 7 5
c Need to use tbl.
e
s 00000/00000/01410
d R 8.1 93/06/08 12:54:52 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/01408
d D 6.3 93/06/05 17:09:39 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00000/01408
d D 6.2 91/04/17 12:45:01 bostic 4 3
c new copyright; att/bsd/shared
e
s 00007/00002/01401
d D 6.1 86/05/22 16:24:32 kjd 3 2
c document for 4.3BSD release
e
s 00000/00000/01403
d D 5.1 86/05/22 16:24:14 kjd 2 1
c document distributed with 4.2BSD
e
s 01403/00000/00000
d D 4.1 86/05/22 16:23:55 kjd 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 4
.\" %sccs.include.proprietary.roff%
.\"
E 4
I 1
.\"	%W% (Berkeley) %G%
.\"
D 3
.fp 3 G
E 3
I 3
D 5
.EH 'USD:19-%''Awk \(em A Pattern Scanning and Processing Language'
.OH 'Awk \(em A Pattern Scanning and Processing Language''USD:19-%'
E 5
I 5
.EH 'USD:16-%''Awk \(em A Pattern Scanning and Processing Language'
.OH 'Awk \(em A Pattern Scanning and Processing Language''USD:16-%'
E 5
.\" .fp 3 G  no G on APS (use gb) or Dandelion Printer (use CW)
.\" the .T is only a ditroff feature...
.if '\*.T'dp' .fp 3 El
.if '\*.T'aps' .fp 3 gB
E 3
....TM "78-1271-12, 78-1273-6" 39199 39199-11
.ND "September 1, 1978"
....TR 68
D 3
.RP
E 3
I 3
.\".RP
E 3
.	\" macros here
.tr _\(em
.if t .tr ~\(ap
.tr |\(or
.tr *\(**
.de UC
\&\\$3\s-1\\$1\\s0\&\\$2
..
.de IT
.if n .ul
\&\\$3\f2\\$1\fP\|\\$2
..
.de UL
.if n .ul
\&\\$3\f3\\$1\fP\&\\$2
..
.de P1
.DS I 3n
.nf
.if n .ta 5 10 15 20 25 30 35 40 45 50 55 60
.if t .ta .3i .6i .9i 1.2i
.if t .tr -\-'\(fm*\(**
.if t .tr _\(ul
.ft 3
.lg 0
.ss 18
.		\"use first argument as indent if present
..
.de P2
.ps \\n(PS
.vs \\n(VSp
.ft R
.ss 12
.if n .ls 2
.tr --''``^^!!
.if t .tr _\(em
.fi
.lg
.DE
..
.hw semi-colon
.hy 14
.		\"2=not last lines; 4= no -xx; 8=no xx-
.		\"special chars in programs
.de WS
.sp \\$1
..
.	\" end of macros
.TL
Awk \(em A Pattern Scanning and Processing Language
.br
(Second Edition)
.AU "MH 2C-522" 4862
Alfred V. Aho
.AU "MH 2C-518" 6021
Brian W. Kernighan
.AU "MH 2C-514" 7214
Peter J. Weinberger
.AI
.MH
.AB
.IT Awk
is a programming language whose
basic operation
is to search a set of files
for patterns, and to perform specified actions upon lines or fields of lines which
contain instances of those patterns.
.IT Awk
makes certain data selection and transformation operations easy to express;
for example, the
.IT awk
program
.sp
.ce
.ft 3
length > 72
.ft
.sp
prints all input lines whose length exceeds 72 characters;
the program
.ce
.sp
.ft 3
NF % 2 == 0
.ft R
.sp
prints all lines with an even number of fields;
and the program
.ce
.sp
.ft 3
{ $1 = log($1); print }
.ft R
.sp
replaces the first field of each line by its logarithm.
.PP
.IT Awk
patterns may include arbitrary boolean combinations of regular expressions
and of relational operators on strings, numbers, fields, variables, and array elements.
Actions may include the same pattern-matching constructions as in patterns,
as well as
arithmetic and string expressions and assignments,
.UL if-else ,
.UL while ,
.UL for
statements,
and multiple output streams.
.PP
This report contains a user's guide, a discussion of the design and implementation of
.IT awk ,
and some timing statistics.
....It supersedes TM-77-1271-5, dated September 8, 1977.
.AE
.CS 6 1 7 0 1 4
.if n .ls 2
.nr PS 9
.nr VS 11
.NH
Introduction
.if t .2C
.PP
.IT Awk
is a programming language designed to make
many common
information retrieval and text manipulation tasks
easy to state and to perform.
.PP
The basic operation of
.IT awk
is to scan a set of input lines in order,
searching for lines which match any of a set of patterns
which the user has specified.
For each pattern, an action can be specified;
this action will be performed on each line that matches the pattern.
.PP
Readers familiar with the
.UX
program
.IT grep\|
.[
unix program manual
.]
will recognize
the approach, although in
.IT awk
the patterns may be more
general than in
.IT grep ,
and the actions allowed are more involved than merely
printing the matching line.
For example, the
.IT awk
program
.P1
{print $3, $2}
.P2
prints the third and second columns of a table
in that order.
The program
.P1
$2 ~ /A\||B\||C/
.P2
prints all input lines with an A, B, or C in the second field.
I 9
.ne 1i
E 9
The program
.P1
$1 != prev	{ print; prev = $1 }
.P2
prints all lines in which the first field is different
from the previous first field.
.NH 2
Usage
.PP
The command
.P1
awk  program  [files]
.P2
executes the
.IT awk
commands in
the string
.UL program
on the set of named files,
or on the standard input if there are no files.
The statements can also be placed in a file
.UL pfile ,
and executed by the command
.P1
awk  -f pfile  [files]
.P2
.NH 2
Program Structure
.PP
An
.IT awk
program is a sequence of statements of the form:
.P1
.ft I
	pattern	{ action }
	pattern	{ action }
	...
.ft 3
.P2
Each line of input
is matched against
each of the patterns in turn.
For each pattern that matches, the associated action
is executed.
When all the patterns have been tested, the next line
is fetched and the matching starts over.
.PP
Either the pattern or the action may be left out,
but not both.
If there is no action for a pattern,
the matching line is simply
copied to the output.
(Thus a line which matches several patterns can be printed several times.)
If there is no pattern for an action,
then the action is performed for every input line.
A line which matches no pattern is ignored.
.PP
Since patterns and actions are both optional,
actions must be enclosed in braces
to distinguish them from patterns.
.NH 2
Records and Fields
.PP
.IT Awk
input is divided into
``records'' terminated by a record separator.
The default record separator is a newline,
so by default
.IT awk
processes its input a line at a time.
The number of the current record is available in a variable
named
.UL NR .
.PP
Each input record
is considered to be divided into ``fields.''
Fields are normally separated by
white space \(em blanks or tabs \(em
but the input field separator may be changed, as described below.
Fields are referred to as
.UL "$1, $2,"
and so forth,
where
.UL $1
is the first field,
and
.UL $0
is the whole input record itself.
Fields may be assigned to.
The number of fields in the current record
is available in a variable named
.UL NF .
.PP
The variables
.UL FS
and
.UL RS
refer to the input field and record separators;
they may be changed at any time to any single character.
The optional command-line argument
\f3\-F\fIc\fR
may also be used to set
.UL FS
to the character
.IT c .
.PP
If the record separator is empty,
an empty input line is taken as the record separator,
and blanks, tabs and newlines are treated as field separators.
.PP
The variable
.UL FILENAME
contains the name of the current input file.
.NH 2
Printing
.PP
An action may have no pattern,
in which case the action is executed for
all
lines.
The simplest action is to print some or all of a record;
this is accomplished by the
.IT awk
command
.UL print .
The
.IT awk
program
.P1
{ print }
.P2
prints each record, thus copying the input to the output intact.
More useful is to print a field or fields from each record.
For instance, 
.P1
print $2, $1
.P2
prints the first two fields in reverse order.
Items separated by a comma in the print statement will be separated by the current output field separator
when output.
Items not separated by commas will be concatenated,
so
.P1
print $1 $2
.P2
runs the first and second fields together.
.PP
The predefined variables
.UL NF
and
.UL NR
can be used;
for example
.P1
{ print NR, NF, $0 }
.P2
prints each record preceded by the record number and the number of fields.
.PP
Output may be diverted to multiple files;
the program
.P1
{ print $1 >"foo1"; print $2 >"foo2" }
.P2
writes the first field,
.UL $1 ,
on the file
.UL foo1 ,
and the second field on file
.UL foo2 .
The
.UL >>
notation can also be used:
.P1
print $1 >>"foo"
.P2
appends the output to the file
.UL foo .
(In each case,
the output files are
created if necessary.)
The file name can be a variable or a field as well as a constant;
for example,
.P1
print $1 >$2
.P2
uses the contents of field 2 as a file name.
.PP
Naturally there is a limit on the number of output files;
currently it is 10.
.PP
Similarly, output can be piped into another process
(on
.UC UNIX
only); for instance,
.P1
print | "mail bwk"
.P2
mails the output to
.UL bwk .
.PP
The variables
.UL OFS
and
.UL ORS
may be used to change the current
output field separator and output
record separator.
The output record separator is
appended to the output of the
.UL print
statement.
.PP
.IT Awk
also provides the
.UL printf
statement for output formatting:
.P1
printf format expr, expr, ...
.P2
formats the expressions in the list
according to the specification
in
.UL format
and prints them.
For example,
.P1
printf "%8.2f  %10ld\en", $1, $2
.P2
prints 
.UL $1
as a floating point number 8 digits wide,
with two after the decimal point,
and
.UL $2
as a 10-digit long decimal number,
followed by a newline.
No output separators are produced automatically;
you must add them yourself,
as in this example.
The version of
.UL printf
is identical to that used with C.
.[
C programm language prentice hall 1978
.]
.NH 1
Patterns
.PP
A pattern in front of an action acts as a selector
that determines whether the action is to be executed.
A variety of expressions may be used as patterns:
regular expressions,
arithmetic relational expressions,
string-valued expressions,
and arbitrary boolean
combinations of these.
.NH 2
BEGIN and END
.PP
The special pattern
.UL BEGIN
matches the beginning of the input,
before the first record is read.
The pattern
.UL END
matches the end of the input,
after the last record has been processed.
.UL BEGIN
and
.UL END
thus provide a way to gain control before and after processing,
for initialization and wrapup.
.PP
As an example, the field separator
can be set to a colon by
.P1
BEGIN	{ FS = ":" }
.ft I
\&... rest of program ...
.ft 3
.P2
Or the input lines may be counted by
.P1
END  { print NR }
.P2
If
.UL BEGIN
is present, it must be the first pattern;
.UL END
must be the last if used.
.NH 2
Regular Expressions
.PP
The simplest regular expression is a literal string of characters
enclosed in slashes,
like
.P1
/smith/
.P2
This
is actually a complete
.IT awk
program which
will print all lines which contain any occurrence
of the name ``smith''.
If a line contains ``smith''
as part of a larger word,
it will also be printed, as in
.P1
blacksmithing
.P2
.PP
.IT Awk
regular expressions include the regular expression
forms found in
the
.UC UNIX
text editor
.IT ed\|
.[
unix program manual
.]
and
.IT grep
(without back-referencing).
In addition,
.IT awk
allows
parentheses for grouping, | for alternatives,
.UL +
for ``one or more'', and
.UL ?
for ``zero or one'',
all as in
.IT lex .
Character classes
may be abbreviated:
.UL [a\-zA\-Z0\-9]
is the set of all letters and digits.
As an example,
the
.IT awk
program
.P1
/[Aa]ho\||[Ww]einberger\||[Kk]ernighan/
.P2
will print all lines which contain any of the names
``Aho,'' ``Weinberger'' or ``Kernighan,''
whether capitalized or not.
.PP
Regular expressions
(with the extensions listed above)
must be enclosed in slashes,
just as in
.IT ed
and
.IT sed .
Within a regular expression,
blanks and the regular expression
metacharacters are significant.
To turn of the magic meaning
of one of the regular expression characters,
precede it with a backslash.
An example is the pattern
.P1
/\|\e/\^.\^*\e//
.P2
which matches any string of characters
enclosed in slashes.
.PP
One can also specify that any field or variable
matches
a regular expression (or does not match it) with the operators
.UL ~
and
.UL !~ .
The program
.P1
$1 ~ /[jJ]ohn/
.P2
prints all lines where the first field matches ``john'' or ``John.''
Notice that this will also match ``Johnson'', ``St. Johnsbury'', and so on.
To restrict it to exactly
.UL [jJ]ohn ,
use
.P1
$1 ~ /^[jJ]ohn$/
.P2
The caret ^ refers to the beginning
of a line or field;
the dollar sign
.UL $
refers to the end.
.NH 2
Relational Expressions
.PP
An
.IT awk
pattern can be a relational expression
involving the usual relational operators
.UL < ,
.UL <= ,
.UL == ,
.UL != ,
.UL >= ,
and
.UL > .
An example is
.P1
$2 > $1 + 100
.P2
which selects lines where the second field
is at least 100 greater than the first field.
Similarly,
.P1
NF % 2 == 0
.P2
prints lines with an even number of fields.
.PP
In relational tests, if neither operand is numeric,
a string comparison is made;
otherwise it is numeric.
Thus,
.P1
$1 >= "s"
.P2
selects lines that begin with an
.UL s ,
.UL t ,
.UL u ,
etc.
In the absence of any other information,
fields are treated as strings, so
the program
.P1
$1 > $2
.P2
will perform a string comparison.
.NH 2
Combinations of Patterns
.PP
A pattern can be any boolean combination of patterns,
using the operators
.UL \||\||
(or),
.UL &&
(and), and
.UL !
(not).
For example,
.P1
$1 >= "s" && $1 < "t" && $1 != "smith"
.P2
selects lines where the first field begins with ``s'', but is not ``smith''.
.UL &&
and
.UL \||\||
guarantee that their operands
will be evaluated
from left to right;
evaluation stops as soon as the truth or falsehood
is determined.
.NH 2
Pattern Ranges
.PP
The ``pattern'' that selects an action may also
consist of two patterns separated by a comma, as in
.P1
pat1, pat2	{ ... }
.P2
In this case, the action is performed for each line between
an occurrence of
.UL pat1
and the next occurrence of
.UL pat2
(inclusive).
For example,
.P1
/start/, /stop/
.P2
prints all lines between
.UL start
and
.UL stop ,
while
.P1
NR == 100, NR == 200 { ... }
.P2
does the action for lines 100 through 200
of the input.
.NH 1
Actions
.PP
An
.IT awk
action is a sequence of action statements
terminated by newlines or semicolons.
These action statements can be used to do a variety of
bookkeeping and string manipulating tasks.
.NH 2
Built-in Functions
.PP
.IT Awk
provides a ``length'' function
to compute the length of a string of characters.
This program prints each record,
preceded by its length:
.P1
{print length, $0}
.P2
.UL length
by itself is a ``pseudo-variable'' which
yields the length of the current record;
.UL length(argument)
is a function which yields the length of its argument,
as in
the equivalent
.P1
{print length($0), $0}
.P2
The argument may be any expression.
.PP
.IT Awk
also
provides the arithmetic functions
.UL sqrt ,
.UL log ,
.UL exp ,
and
.UL int ,
for
square root,
base
.IT e
logarithm,
exponential,
and integer part of their respective arguments.
.PP
The name of one of these built-in functions,
without argument or parentheses,
stands for the value of the function on the
whole record.
The program
.P1
length < 10 || length > 20
.P2
prints lines whose length
is less than 10 or greater
than 20.
.PP
The function
.UL substr(s,\ m,\ n)
produces the substring of
.UL s
that begins at position
.UL m
(origin 1)
and is at most
.UL n
characters long.
If
.UL n
is omitted, the substring goes to the end of
.UL s .
The function
.UL index(s1,\ s2)
returns the position where the string
.UL s2
occurs in
.UL s1 ,
or zero if it does not.
.PP
The function
.UL sprintf(f,\ e1,\ e2,\ ...)
produces the value of the expressions
.UL e1 ,
.UL e2 ,
etc.,
in the
.UL printf
format specified by
.UL f .
Thus, for example,
.P1
x = sprintf("%8.2f %10ld", $1, $2)
.P2
sets
.UL x
to the string produced by formatting
the values of
.UL $1
and
.UL $2 .
.NH 2
Variables, Expressions, and Assignments
.PP
.IT Awk
variables take on numeric (floating point)
or string values according to context.
For example, in
.P1
x = 1
.P2
.UL x
is clearly a number, while in
.P1
x = "smith"
.P2
it is clearly a string.
Strings are converted to numbers and
vice versa whenever context demands it.
For instance,
.P1
x = "3" + "4"
.P2
assigns 7 to
.UL x .
Strings which cannot be interpreted
as numbers in a numerical context
will generally have numeric value zero,
but it is unwise to count on this behavior.
.PP
By default, variables (other than built-ins) are initialized to the null string,
which has numerical value zero;
this eliminates the need for most
.UL BEGIN
sections.
For example, the sums of the first two fields can be computed by
.P1
	{ s1 += $1; s2 += $2 }
END	{ print s1, s2 }
.P2
.PP
Arithmetic is done internally in floating point.
The arithmetic operators are
.UL + ,
.UL \- ,
.UL \(** ,
.UL / ,
and
.UL %
(mod).
The C increment
.UL ++
and
decrement
.UL \-\-
operators are also available,
and so are the assignment operators
.UL += ,
.UL \-= ,
.UL *= ,
.UL /= ,
and
.UL %= .
These operators may all be used in expressions.
.NH 2
Field Variables
.PP
Fields in
.IT awk
share essentially all of the properties of variables _
they may be used in arithmetic or string operations,
and may be assigned to.
Thus one can
replace the first field with a sequence number like this:
.P1
{ $1 = NR; print }
.P2
or
accumulate two fields into a third, like this:
.P1
{ $1 = $2 + $3; print $0 }
.P2
or assign a string to a field:
.P1
{ if ($3 > 1000)
	$3 = "too big"
  print
}
.P2
which replaces the third field by ``too big'' when it is,
and in any case prints the record.
.PP
Field references may be numerical expressions,
as in
.P1
{ print $i, $(i+1), $(i+n) }
.P2
Whether a field is deemed numeric or string depends on context;
in ambiguous cases like
.P1
if ($1 == $2) ...
.P2
fields are treated as strings.
.PP
Each input line is split into fields automatically as necessary.
I 9
.br
.ne 1i
E 9
It is also possible to split any variable or string
into fields:
.P1
n = split(s, array, sep)
.P2
splits the
the string
.UL s
into
.UL array[1] ,
\&...,
.UL array[n] .
The number of elements found is returned.
If the
.UL sep
argument is provided, it is used as the field separator;
otherwise
.UL FS
is used as the separator.
.NH 2
String Concatenation
.PP
Strings may be concatenated.
For example
.P1
length($1 $2 $3)
.P2
returns the length of the first three fields.
Or in a
.UL print
statement,
.P1
print $1 " is " $2
.P2
prints
the two fields separated by `` is ''.
Variables and numeric expressions may also appear in concatenations.
.NH 2
Arrays
.PP
Array elements are not declared;
they spring into existence by being mentioned.
Subscripts may have
.ul
any
non-null
value, including non-numeric strings.
As an example of a conventional numeric subscript,
the statement
.P1
x[NR] = $0
.P2
assigns the current input record to
the
.UL NR -th
element of the array
.UL x .
In fact, it is possible in principle (though perhaps slow)
to process the entire input in a random order with the
.IT awk
program
.P1
	{ x[NR] = $0 }
END	{ \fI... program ...\fP }
.P2
The first action merely records each input line in
the array
.UL x .
.PP
Array elements may be named by non-numeric values,
which gives
.IT awk
a capability rather like the associative memory of
Snobol tables.
Suppose the input contains fields with values like
.UL apple ,
.UL orange ,
etc.
Then the program
.P1
/apple/	{ x["apple"]++ }
/orange/	{ x["orange"]++ }
END		{ print x["apple"], x["orange"] }
.P2
increments counts for the named array elements,
and prints them at the end of the input.
.NH 2
Flow-of-Control Statements
.PP
.IT Awk
provides the basic flow-of-control statements
.UL if-else ,
.UL while ,
.UL for ,
and statement grouping with braces, as in C.
We showed the
.UL if
statement in section 3.3 without describing it.
The condition in parentheses is evaluated;
if it is true, the statement following the
.UL if
is done.
The
.UL else
part is optional.
.PP
The
.UL while
statement is exactly like that of C.
For example, to print all input fields one per line,
.P1
i = 1
while (i <= NF) {
	print $i
	++i
}
.P2
.PP
The
.UL for
statement is also exactly that of C:
.P1
for (i = 1; i <= NF; i++)
	print $i
.P2
does the same job as the
.UL while
statement above.
.PP
There is an alternate form of the
.UL for
statement which is suited for accessing the
elements of an associative array:
.P1
for (i in array)
	\fIstatement\f3
.P2
does
.ul
statement
with 
.UL i
set in turn to each element of
.UL array .
The elements are accessed in an apparently random order.
Chaos will ensue if 
.UL i
is altered, or if any new elements are
accessed during the loop.
.PP
The expression in the condition part of an
.UL if ,
.UL while
or
.UL for
can include relational operators like
.UL < ,
.UL <= ,
.UL > ,
.UL >= ,
.UL ==
(``is equal to''),
and
.UL !=
(``not equal to'');
regular expression matches with the match operators
.UL ~
and
.UL !~ ;
the logical operators
.UL \||\|| ,
.UL && ,
and
.UL ! ;
and of course parentheses for grouping.
.PP
The
.UL break
statement causes an immediate exit
from an enclosing
.UL while
or
.UL for ;
the
.UL continue
statement
causes the next iteration to begin.
.PP
The statement
.UL next
causes
.IT awk
to skip immediately to
the next record and begin scanning the patterns from the top.
The statement
.UL exit
causes the program to behave as if the end of the input
had occurred.
.PP
Comments may be placed in
.IT awk
programs:
they begin with the character
.UL #
and end with the end of the line,
as in
.P1
print x, y	# this is a comment
.P2
.NH
Design
.PP
The
.UX
system
already provides several programs that
operate by passing input through a
selection mechanism.
.IT Grep ,
the first and simplest, merely prints all lines which
match a single specified pattern.
.IT Egrep
provides more general patterns, i.e., regular expressions
in full generality;
.IT fgrep
searches for a set of keywords with a particularly fast algorithm.
.IT Sed\|
.[
unix programm manual
.]
provides most of the editing facilities of
the editor
.IT ed  ,
applied to a stream of input.
None of these programs provides
numeric capabilities,
logical relations,
or variables.
.PP
.IT Lex\|
.[
lesk lexical analyzer cstr
.]
provides general regular expression recognition capabilities,
and, by serving as a C program generator,
is essentially open-ended in its capabilities.
The use of
.IT lex ,
however, requires a knowledge of C programming,
and a
.IT lex
program must be compiled and loaded before use,
which discourages its use for one-shot applications.
.PP
.IT Awk
is an attempt
to fill in another part of the matrix of possibilities.
It
provides general regular expression capabilities
and an implicit input/output loop.
But it also provides convenient numeric processing,
variables,
more general selection,
and control flow in the actions.
It
does not require compilation or a knowledge of C.
Finally,
.IT awk
provides
a convenient way to access fields within lines;
it is unique in this respect.
.PP
.IT Awk
also tries to integrate strings and numbers
completely,
by treating all quantities as both string and numeric,
deciding which representation is appropriate
as late as possible.
In most cases the user can simply ignore the differences.
.PP
Most of the effort in developing
.I awk
went into deciding what
.I awk
should or should not do
(for instance, it doesn't do string substitution)
and what the syntax should be
(no explicit operator for concatenation)
rather
than on writing or debugging the code.
We have tried
to make the syntax powerful
but easy to use and well adapted
to scanning files.
For example,
the absence of declarations and implicit initializations,
while probably a bad idea for a general-purpose programming language,
is desirable in a language
that is meant to be used for tiny programs
that may even be composed on the command line.
.PP
In practice,
.IT awk
usage seems to fall into two broad categories.
One is what might be called ``report generation'' \(em
processing an input to extract counts,
sums, sub-totals, etc.
This also includes the writing of trivial
data validation programs,
such as verifying that a field contains only numeric information
or that certain delimiters are properly balanced.
The combination of textual and numeric processing is invaluable here.
.PP
A second area of use is as a data transformer,
converting data from the form produced by one program
into that expected by another.
The simplest examples merely select fields, perhaps with rearrangements.
.NH
Implementation
.PP
The actual implementation of
.IT awk
uses the language development tools available
on the
.UC UNIX
operating system.
The grammar is specified with
.IT yacc ;
.[
yacc johnson cstr
.]
the lexical analysis is done by
.IT lex ;
the regular expression recognizers are
deterministic finite automata
constructed directly from the expressions.
An
.IT awk
program is translated into a 
parse tree which is then directly executed
by a simple interpreter.
.PP
.IT Awk
was designed for ease of use rather than processing speed;
the delayed evaluation of variable types
and the necessity to break input
into fields makes high speed difficult to achieve in any case.
Nonetheless,
the program has not proven to be unworkably slow.
.PP
Table I below shows the execution (user + system) time
on a PDP-11/70 of
the
.UC UNIX
programs
.IT wc ,
.IT grep ,
.IT egrep ,
.IT fgrep ,
.IT sed ,
.IT lex ,
and
.IT awk
on the following simple tasks:
.IP "\ \ 1."
count the number of lines.
.IP "\ \ 2."
print all lines containing ``doug''.
.IP "\ \ 3."
print all lines containing ``doug'', ``ken'' or ``dmr''.
.IP "\ \ 4."
print the third field of each line.
.IP "\ \ 5."
print the third and second fields of each line, in that order.
.IP "\ \ 6."
append all lines containing ``doug'', ``ken'', and ``dmr''
to files ``jdoug'', ``jken'', and ``jdmr'', respectively.
.IP "\ \ 7."
print each line prefixed by ``line-number\ :\ ''.
.IP "\ \ 8."
sum the fourth column of a table.
.LP
The program
.IT wc
merely counts words, lines and characters in its input;
we have already mentioned the others.
In all cases the input was a file containing
10,000 lines
as created by the
command
.IT "ls \-l" ;
each line has the form
.P1
-rw-rw-rw- 1 ava 123 Oct 15 17:05 xxx
.P2
The total length of this input is
452,960 characters.
Times for
.IT lex
do not include compile or load.
.PP
As might be expected,
.IT awk
is not as fast as the specialized tools
.IT wc ,
.IT sed ,
or the programs in the
.IT grep
family,
but
is faster than the more general tool
.IT lex .
In all cases, the tasks were
about as easy to express as
.IT awk
programs
as programs in these other languages;
tasks involving fields were
considerably easier to express as
.IT awk
programs.
Some of the test programs are shown in
.IT awk ,
.IT sed
and
.IT lex .
.[
$LIST$
.]
.1C
.TS
center;
c c c c c c c c c
c c c c c c c c c
c|n|n|n|n|n|n|n|n|.
				Task
Program	1	2	3	4	5	6	7	8
_
\fIwc\fR	8.6
\fIgrep\fR	11.7	13.1
\fIegrep\fR	6.2	11.5	11.6
\fIfgrep\fR	7.7	13.8	16.1
\fIsed\fR	10.2	11.6	15.8	29.0	30.5	16.1
\fIlex\fR	65.1	150.1	144.2	67.7	70.3	104.0	81.7	92.8
\fIawk\fR	15.0	25.6	29.9	33.3	38.9	46.4	71.4	31.1
_
.TE
.sp
.ce
\fBTable I.\fR  Execution Times of Programs. (Times are in sec.)
.sp 2
.2C
.PP
The programs for some of these jobs are shown below.
The
.IT lex
programs are generally too long to show.
.LP
AWK:
.LP
.P1
1.	END	{print NR}
.P2
.P1
2.	/doug/
.P2
.P1
3.	/ken|doug|dmr/
.P2
.P1
4.	{print $3}
.P2
.P1
5.	{print $3, $2}
.P2
.P1
6.	/ken/	{print >"jken"}
	/doug/	{print >"jdoug"}
	/dmr/	{print >"jdmr"}
.P2
.P1
7.	{print NR ": " $0}
.P2
.P1
8.		{sum = sum + $4}
	END	{print sum}
.P2
.LP
SED:
.LP
.P1
1.	$=
.P2
.P1
2.	/doug/p
.P2
.P1
3.	/doug/p
	/doug/d
	/ken/p
	/ken/d
	/dmr/p
	/dmr/d
.P2
.P1
4.	/[^ ]* [ ]*[^ ]* [ ]*\e([^ ]*\e) .*/s//\e1/p
.P2
.P1
5.	/[^ ]* [ ]*\e([^ ]*\e) [ ]*\e([^ ]*\e) .*/s//\e2 \e1/p
.P2
.P1
6.	/ken/w jken
	/doug/w jdoug
	/dmr/w jdmr
.P2
.LP
LEX:
.LP
.P1
1.	%{
	int i;
	%}
	%%
	\en	i++;
	.	;
	%%
	yywrap() {
		printf("%d\en", i);
	}
.P2
.P1
2.	%%
	^.*doug.*$	printf("%s\en", yytext);
	.	;
	\en	;
.P2
E 1
