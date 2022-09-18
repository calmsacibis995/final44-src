.TH VDIFF 1  "19 March 1987"
.UC 4
.SH NAME
vdiff \- visual differential file comparator and merger
.SH SYNOPSIS
.B vdiff
[
.B \-thvbBsV
] 
[
.B \-d <difference file>
]
[
.B \-o <output file>
] file1 file2
.SH DESCRIPTION
.I vdiff
presents the differences between two files in a graphical format, allowing
the user to peruse though the files. Any differences between the two files
are indicated by drawing a box around them. Lines are drawn between the
corresponding changed text in the two files.

To scroll a file simply place the cursor over the text you wish to scroll,
hold down
button 1, and move the puck in the direction you wish to
scroll. Both horizontal and vertical scrolling is possible.

The horizontal and vertical thumb bars show your position within the
corresponding file. Positioning the cursor over one of these thumb bars
and hitting
button 1 will take you to that line or column in the file. A box above each of the
two vertical thumb bars displays the line number.

If one of the filenames given is a `-' then the standard input will be read.

The startup options available are:
.TP
.B \-t
expand tabs. If this is not specified then tabs will be converted to spaces.
.TP
.B \-h
unlink horizontal scrolling. If horizontal scrolling is linked then
when one file is scrolled left or right the other file will follow.
.TP
.B \-v
unlink vertical scrolling. With vertical scrolling unlinked both files can be
scrolled freely up or down. If vertical scrolling is linked then the
file you are not scrolling will attempt to align itself with file you are
scrolling.
.TP
.B \-b
disable highlighting of differences. By default
.I vdiff
draws all file differences in bold type.
.TP
.B \-B
when comparing files, ignore trailing blanks (spaces and tabs) and treat
strings of blanks as equal.
.TP
.B \-s
use a small font to display the files. This reduces the legibility of
the display but allows you to see more of the file. This option may not
be available on some machines.
.TP
.B \-V
output version number on startup.
.TP
.B \-d <difference file>
read the difference information from <difference file> rather than
using /bin/diff to find the differences.
The file contents must be in the same format as the output
from /bin/diff except that any lines not starting with a digit may be omitted.
.TP
.B \-o <output file>
merge the two input files and send the result to <output file>.
If this option is specified then each difference is highlighted with
a grey bar to show which difference (either left-hand or the right-hand)
has been selected.
A difference is selected by pointing to the line and pressing button 2.
The final result is written to <output file> when the user quits.

All the above options except \fB\-B\fP, \fB\-V\fP, \fB\-d\fP and \fB\-o\fP can be toggled from within vdiff.
.SH FILES
/tmp/v??????
.br
/bin/diff
.br
/usr/lib/fonts/fixedwidthfonts/cour.r.10
.SH "SEE ALSO"
diff(1), diff3(1)
.SH DIAGNOSTICS
Exit status is normally 0, non 0 means trouble.
.SH BUGS
.I vdiff
does not have all the bells and whistles that are available when using
.I diff.
