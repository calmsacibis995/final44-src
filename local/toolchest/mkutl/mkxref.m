.TH MKXREF 1 "Toolchest"
.(B
.tl @Copyright (c) 1984, 1985, 1986, 1987@@AT&T All Rights Reserved@
.(E 2
.SH NAME
mkxref \-  report actions of a \fBmake\fP script
.SH SYNOPSIS
\f3mkxref\f1 [ file ]
.SH DESCRIPTION
.I mkxref
reports on the files involved in or affected by a
.I make (1)
script.
.I mkxref
is used in one of two ways:
.RS 5
.TP 10
.I "mkxref directory"
.sp
Will produce the report on all .mk files
in directory (output to $HOME/mkxref.rpt).
.TP 10
.I "mkxref directory command"
.sp
Will produce the report on the command.mk file
in directory (output to stdout).
.RE 1
.PP
.I mkxref.pgm
is a C program invoked by
.I mkxref .
The syntax for invoking mkxref.pgm directly is:
.PP
.RS 5
.I "mkxref.pgm path print debug"
.br
.TP 7
path
is the path of the directory being processed.
.TP 7
print
is either a 1 or 0.
.RS 5
.nf
A 1 will print each command line used for the report,
a 0 supresses this print.
.fi
.RE 1
.TP 7
debug
allows for a 0, 1, or 2.
.RS 5
.nf
A 0 produces no diagnostic output.
A 1 produces limited diagnostics.
A 2 produces full diagnostics.
.fi
.RE
.RE
.PP
.I mkxref
prints a record for each file required to build the desired
program. Included in the listing are:
.PP
.RS 5
.TP 4
1.
File name (fully qualified)
.PP
.TP 4
2.
Mode (if the mode of the file is set by make)
.PP
.TP 4
3.
Owner of the file (if the owner is set by make)
.PP
.TP 4
4.
Group of the file (if the group is set by make)
.PP
.TP 4
5.
File type. The file type is first determined by context if
possible. If contextual determination fails, mkxref looks
to identify the type by one of the file suffixes listed
below, if that fails no file type is displayed.
.PP
.RS 10
.nf
 Suffixes        File Type       Symbol
 =========       =========       ======
 .a              Library           LB
 .c              C Source          SR
 .o              Binary            BN
 .out            Binary            BN
 .s              Assembler         AS
 .sh             Shell Script      SS
.fi
.RE 1
.PP
.TP 4
6.
I/O indicator saying whether the file is read (r), written
(w), or deleted(d). A '!' after the I/O indicator indicates
that this is a conditional entry, part of an 'if', or
used if another file is not found.
.RE 1
.SH EXAMPLE
.SH FILES
$HOME/mkxref.rpt \-
contains output for full directory reports
.SH "SEE ALSO"
make(1)
.SH AUTHOR
E. H. Rice III
