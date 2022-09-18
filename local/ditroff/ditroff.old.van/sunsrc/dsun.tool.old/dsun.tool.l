.TH DSUN.TOOL 1 "May 1985"
.SH NAME
dsun.tool \- display ditroff output on a SUN workstation in the 
.I suntools
environment.
.SH SYNOPSIS
.br
.B dsun.tool
[
.BI options
]  filename
.SH DESCRIPTION
.PP
\fIDsun.tool\fP reads the ditroff output file \fIfilename\fP
and displays the typeset docment, page by page, in a window of the
\fIsuntools\fP environment on a SUN. It can show output destined for
any of the laser printers (imagen, varian, etc) provided that
the ditroff file has been generated using the -P<printer> option.
Note that unlike dsun, if \fIfilename\fP is missing then standard
input is not read. Despite many similarities there are some functional
differences between dsun.tool and dsun.
.PP
The pages are displayed in the dsun.tool window in two different modes:
\fIcropped\fP and \fInot cropped\fP. Dsun.tool operates in the cropped
mode by default. It will only enter the \fInot cropped\fP mode if
the \fIn\fP option is specified.
.PP
In the \fIcropped mode\fP
the pages are displayed in a window with extra white space to the
left of the page removed. The size of the window is also a slightly smaller
than it would be in the uncropped mode.
This is done on a page by page basis and is
good for looking at your document while comparing it to the source. This
mode is the default for operation since using dsun.tool implies that
you want to take advantage of the window system instead of using dsun (see
options below).
.PP
In the \fInot cropped\fP 
mode, the pages are displayed in a window just as they would appear
on the laser printer. Indention schemes that affect the left hand side
of the document are preserved. In addition, the window that is opened
takes the full width of the Sun 150 screen, i.e. 1024 pixels. This is
consistent with dsun.tool's predecessor dsun.
Text and drawings are placed in the window under the scaling assumptions
that the window represents part of an 8.5 by 11 inch piece of paper. Of course,
the Sun screen isn't that big, so it's impossible to get an entire page
on the screen at once. Moreover, fonts are enlarged to take into
account the limited resolution of the Sun. All fonts used are relative
in size so that proportions between letters are preserved.
There are commands listed below that enable you to view the
parts of the document not immediatly visible on the screen.
This mode is accessed by specifying a -n (for normal dsun output)
in the command line. 
.PP
After the image for the page currently being displayed has been
completely generated (including the invisible part), the page
number will be displayed in the upper left hand corner of the
screen.
.PP
Anytime during the execution of dsun.tool, the commands listed below
may be typed (assuming that the mouse is over the window). They
are not echoed, but be patient...If you type a command 500 times you
had better be prepared to wait until it has been executed 500 times.
.SH OPTIONS
.TP
.B (n)ormal
In this mode extra white space is not removed from the display.
The window used for display is opened to the entire width of the screen (1024
pixels). Note that the default is to crop the extra white space and not open
the window as wide.
.TP
.B (F or f)ontdir
Allows the specification of an alternate bitdir.
.TP
.B (p)ause
Should we pause at each 'P' command in the ditroff file? No by default.
.TP
.B (x)or
Should stuff on screen be `xor'ed in ? No also by default.
.TP
.B (r)esolution
Number following indicates the resolution of the screen: Currently defaulted
to 120 dots/inch.
.SH COMMANDS
.TP
.if t .B "\(ua\0or\0u\0or\0<space>"
.if n .B "<up-arrow>\0or\0u\0or\0<space>"
causes the displayed page to be scrolled one third of the window height
up. If there isn't enough left of the page to complete this
scroll then the next page of the document is displayed.
.TP
.if t .B "\(da\0or\0d"
.if n .B "<down-arrow>\0or\0d"
scrolls the current page one third of the current window height down.
This is the opposite of the <space> command. If the page is positioned
with its beginning at the top of the window then the next page, if it
exists, is skipped to.
.TP
.B q
quit
.TP
.B "<return>\0or\0\(->"
moves to the next page. If the page is the last one then it will merely
be echoed.
.TP
.B \(<-
moves back one page in the document. If the current page is the first
page then no action is taken.
.TP
.IB number g
causes page <number> to be displayed if it exists. If the number 
is greater than the number of pages in the document then the
last page is displayed.
.I number (
``go'' to page
.IR number ).
Also accepted are
.B G
and
.BR p .
.TP
.B $
go to the last page of the document
.SH "WINDOW DIMENSION"
.PP
The initial dimensions of the dsun.tool window can be controlled
by setting the environment variable \fIDSUN_TOOL\fP with a string
of four numbers seperated by either commas or spaces that represent
in the following order: the inital x coordinate of the upper left hand
corner of the window, the inital y coordinate of the upper left hand corner
of the window,
the initial width, and the initial height.
.SH NOTES
.PP
Dsun.tool preprocesses a two page buffer on either side of the
page currently being displayed. If the page being displayed is
i, then the order of processing is i + 1, i + 2, i - 1, i - 2.
This is an attempt to always have ready for display the pages most
likely to be selected next. The five page limit is imposed by
memory restrictions that make themselves felt in other ways. For example,
if you have a great many processes running (or even stopped) don't
expect to dsun.tool to start off running fast. As soon as it has
paged most of it's pertinant parts in (I'm afraid there are alot of them)
the speed becomes markedly faster. However, if dsun.tool must compete
with many other processes for resources, output will be slow and you may
experience the trashing of your window display.
.SH "SEE ALSO"
.nf
ditroff(1)
.SH BUGS
.PP
The icon doesn't seem to work, so don't close the tool into it's iconic
form or you'll never see it again. The process won't die, but it
will disappear from the window system.
Other than that, it's hard to tell. They seem to be dependent 
upon the version of Sun that dsun.tool runs on.
.SH AUTHORS
David Slattengren and Brian Marsh
