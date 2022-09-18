.\" $Header: vf.l,v 1.3 86/11/24 16:44:59 mtr Exp $
.ds ba the left button
.ds bb the middle button
.ds bc the right button
.TH VF 1 "23 November 1986"
.SH NAME
vf \- screen oriented file displayer
.SH SYNOPSIS
\fBvf [file ...]
.SH DESCRIPTION
\fIVf\fP is an alternative to \fIcat\fP or \fIspy\fP for displaying
(but not editing) the contents of a file.
It is screen oriented in that it displays a window on the file
which can be scrolled horizontally and vertically.
.LP
\fIVf\fP can be used to look at non text files. 
It currently knows about cursors, fonts, raster files, \fItar\fP and \fIar\fP
archives,
object files and directories, and tries to display them intelligently.
.LP
If no arguments are given, \fIvf\fP reads its standard input.
It can thus be used at the end of a pipe
to monitor the output of a file (it notices when text files grow or shrink).
If there are arguments, the first file named in the argument list is
displayed and the rest of the list saved for future use (see below).
.SH "THE DISPLAY AREA"
This is where the file is displayed. The file can be scrolled horizontally
or vertically by pressing \*(ba in the display area, and moving the
puck in the direction you want the file to move.
The further you move the puck from
the place where you first pressed it, the faster the file will scroll.
.LP
When the cursor is in the display area, the line and column number
of the character the cursor is over are displayed in the number boxes to
the right of the menu. The number shown in bold in the right hand box is
the line number, the number on the left is the column number.
.SH "THE THUMB BARS"
These operate in the same way as the thumb bars of \fIspy\fP(1) except that
as \fIvf\fP has horizontal as well as vertical scrolling, there are two.
.LP
The horizontal thumb bar is a thin strip below the menu.
It provides feedback on the size of the longest line in the file relative
to the display area width, and allows you to go to an absolute column
number.
.LP
The vertical thumb bar is similar, but indicates the number of lines in the
file relative to the display area depth. It is thicker than the
horizontal thumb bar as it likely to be used more.
.LP
When the cursor is in either thumb bar, the boxes to the right of the menu
show the line or column number. If \*(ba is pressed and released in the
thumb bar, this
line or column will be moved to the centre of the display area.
.SH "READING NEW FILES"
\fIVf\fP stores the filenames given on the command line in a list.
The \fBnew file\fP menu command displays this list.
Selecting a file from the list makes that file the current file \(em it
is read in and displayed.
.LP
If the first or last entry in the menu is if the form `\fInnn more\fP' it
means that the list is too long to be completely displayed in the window.
Selecting the top or bottom `\fInnn more\fP' caption displays the next or
previous `page' of the menu.
.LP
Selecting the \fInext\fP and \fIprev\fP menu buttons makes \fIvf\fP read
in the file immediately after or before the current one in the file list.
.LP
Typing a file name followed by RETURN means read in the given file.
The name may contain metacharacters which are interpreted as in
\fIcsh\fP(1) and thus may expand to more than one file.
In this case the first file in the resulting list is read in, and the
list replaces the current file list.
If the name expands to only a single file, that file is added to the
current file list, rather than replacing it.
.SH "READING THE STANDARD INPUT"
If no files are given on the command line, \fIvf\fP reads its standard
input. It assumes that the file is text - if this is wrong you can
set the type later (see FILE TYPES below).
\fIVf\fP copies all characters read into \fI/tmp/vf\fP, or if this file
exists already, \fI/tmp/vf1\fP etc. The file is deleted when you quit,
but is available for copying while \fIvf\fP is running.
.LP
\fIVf\fP does not wait for an end of file on the standard input before
starting. Instead, it checks every few seconds to see whether the file
has grown. This means that it is possible to use \fIvf\fP at the end
of a pipe to monitor the output of long running commands, or as a
convenient way to browse through long manual
pages - e.g. `\fIman make | vf\fP'.
.LP
In fact, \fIvf\fP will notice if \fIany\fP text file grows or shrinks
and will add the extra characters to the display.
.SH "DETAILS"
The \fBdetails\fP menu command produces a message giving information about
the currently displayed file in the same format as \fIls\fP(1) with the
\fB-l\fP option.
.SH "CONTEXT SEARCHING"
The \fBsearch\fP command allows you to search backwards or forwards in
a text file for regular expressions.
The syntax is postfix \(em you first type in the pattern to be searched for
the select \fBsearch\fP.
.LP
If no line matching the pattern is found, a message to that effect is given,
and the display area is not changed.
If a match is found, the display is moved if necessary and the text that
matched is highlighted.
.LP
Searching starts from the line displayed at the top of the display area, or
from the position of the previous match if it is still highlighted.
Thus hitting search repeatedly shows all matching strings in the file in
turn. The search stops on a match, or at the end or start of the file.
.LP
You can set the position that the search is to start from by pointing at a
character in the display area with \*(bb.
The single character is highlighted as if it had matched a pattern, and
a subsequent search will start from the highlighted character.
.LP
Patterns are as in \fIgrep\fP(1) with one extension \(em the sequence
`\e<' matches the start of a word, and `\e>' matches the end of a word.
.SH "FILE TYPES"
\fIVf\fP tries to guess a file's type on reading it in.
It normally gets the type right, but you can force it to interpret
a file as of a given type using the \fBset type\fP menu command.
This produces a popup menu listing the known file types.
Selecting a type from this menu makes \fIvf\fP reread the file, and treat
it as of the given type.
The special entry \fBguess type\fP at the top of the submenu means allow
\fIvf\fP to do its normal guessing of the file type.
.LP
The currently known types and the way they are displayed are:
.IP "text files"
One line of the file is displayed per screen line. Long lines are not
folded - instead you can scroll horizontally to see the ends of long lines.
There is no limit on the length of a line.
.IP
Control characters are displayed in inverse video.
Tabs are expanded assuming tab stops every eight spaces.
Backspaces are treated as they would be by a line printer \(em that is the
sequence \fIc1\fP \fIbackspace\fP \fIc2\fP is displayed as \fIc2\fP.
This makes \fInroff\fP(1) output readable.
.IP "cursor/icon files"
The cursor is shown in the centre of the display area.
The background is initially black, but can be toggled to white and back
by pressing \*(bb in the display area.
.IP "raster files"
Sun \fIrasterfile\fP(5) format files are displayed by showing the raster
image in the display area.
This image can be scrolled in all four directions in the same way as text
files.
As with icons, the background is initially black, and can be toggle with
\*(bb.
.IP "font files"
All the characters in the font are displayed, in a grid of eight lines
of sixteen characters each.
The grid can be turned on and off using puck \*(bc.
If the font is too big to fit in the display area, it can be scrolled
horizontally and vertically in the same way as text files.
Characters that do not appear in the font are displayed as white space.
.IP "object files"
If the file is unstripped, a list of symbol table entries is
printed.
Labels produced by the C compiler, and other automatically generated symbols
are not shown.
In all cases, \fIvf\fP prints a list of what it thinks are
strings in the data section of the file.
The definition of a string used here is a run of four or more
printable characters.
.IP "\fIar\fP and \fItar\fP archives"
.br
A list of the members is printed \(em the format is similar to that produced
by \fItar\fP or \fIar\fP with the \fItv\fP option.
This list, and the directory listing described below can be scrolled and
searched in the same way as text files.
.IP directories
A list of the names and inode numbers of the files in the directory is
shown. Files are displayed in the order they appear in the directory.
Empty slots (those with an inode number of zero) are not displayed.
.IP data
.br
A non text file which \fIvf\fP does not recognise
as being of any of the above types is displayed as a hex dump.
The format of each displayed line is:
.RS
.IP
the offset of the start of this line from the start of the file, as an
eight digit hex number
.IP
the two digit hex values of the next sixteen characters from the file
.IP
the same sixteen characters displayed as ascii
.RS
.SH BUGS
\fIVf\fP will sometimes get confused if a text file it is looking at is
overwritten with different contents. To straighten things out, re-read the
file.
.LP
The standard error output is not caught when \fIvf\fP is at the end of
a pipe. Use `\fIcommand |& vf\fP'.
.SH "SEE ALSO"
fs(1), cat(1), more(1), spy(1)
.SH ACKNOWLEDGEMENTS
The regular expression matching algorithm was written by Ozan S. Yigit
of the Department of Computer Science, York University.
