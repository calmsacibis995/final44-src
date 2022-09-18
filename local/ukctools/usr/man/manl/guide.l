.vs 13
.ps 11
.TH GUIDE 1 "27 July 1987"
.SH NAME
guide \(em displayer of documents in structured form
.SH SYNOPSIS
.B guide 
[  [
.B \-v
]  [
.B \-V
]  [\ \fB\-f\fP<string>\ ]  [
\fB\-b\fP<string>\ ]  [\ \fB\-u\fP<digit>\ ]  [\ \fB\-m[\fP<character>]\ ]  [
.B \-p
]  [
.B \-c
]  [
.B \-s
]  [
.B \-t
]  [\ file\ ]  ]\ ...
.SH DESCRIPTION
.I Guide
is a tool to allow readers to peruse a file, called the
`\fIsource\fP', at the level of detail they
want, and thus to create a document tailored to their individual needs.
The initial source to be perused is in the \fIfile\fP(s) specified on the
command to enter \fIGuide\fP.
\fIGuide\fP's main design features are as follows:
.sp
.Bu l 1 n
\fISimplicity of use\fP:
.bR
.Gu "SIMPLICITY OF USE:
.Nl "#GT@
documents are presented as
.Bu g 1 n
scroll\c
.bU
able texts, not
as trees or other data structures that users might get lost in.
Documents can be expanded (e.g. to provide a greater level of detail) by
selecting \fIreplace-buttons\fP that lie within the source.
Replace-buttons are displayed in a bold font \(em the same font that is used
for buttons in the \fIGuide\fP menu.
Scrolling is achieved by using a \fIthumb-bar\fP, which is displayed just
beneath the \fIGuide\fP menu.
.rE
.Nl
.sp
.Bu l 1 n
\fIEditing\fP:
.bU
.Re
.Gu "EDITING:
.Nl "#GT@
the user can edit documents just by placing a
.Bu g 1 n
\fImarker-bar\fP\c
.bU
\& in the required place and then typing, in the same way as with a screen editor.
.rE
.Nl
.sp
.Bu l 1 n
\fIFilling and indentation\fP:
.bU
.Re
.Gu "FILLING AND INDENTATION:
.Nl "#GT@
\fIGuide\fP automatically fills lines on the
display in order to fit the size of window used.
\fIGuide\fP input should only contain newlines where they are really wanted
(e.g. at the end of a paragraph).
A tab causes each displayed line to be indented until a newline character is
encountered in the input; thus a tab can be used to indent a whole paragraph
\(em provided the paragraph has been typed in the recommended way, with no embedded
newlines.
.rE
.Nl
.sp
.Bu l 1 n
\fIGlossaries\fP:
.bU
.Re
.Gu "GLOSSARIES:
.Nl "#GT@
jargon words in the text can be made into
.Bu g 1 n
\fIglossary-button\fP\c
.bU
s.
These are underlined, and if the user selects one of them its definition is inserted into the glossary and displayed.
The glossary is kept in alphabetical order.
.rE
.Nl
.sp
.Bu l 1 n
\fIEasy authorship\fP:
.bU
.Re
.Gu "EASY AUTHORSHIP:
.Nl "#GT@
authors prepare documents in the same way that
readers use them.
Thus the author is the reader and the reader is the author.
When an author wishes to add structure to a document (e.g. new
.Bu g 1 n
replace-button\c
.bU
s with appropriate text to replace them), he selects
\fIauthor-display\fP by using the
.B Author
command in the \fIGuide\fP menu;
this gives an extended menu (e.g. the menu command \fB+Glossary\fP, which creates a
new glossary-button) and also shows the underlying structure from
which the document was created.
The structure is shown by inverse-video \fIcontrol characters\fP embedded in
the text.
These show the boundaries between the various parts of the document.
To create a source from scratch, \fIGuide\fP should be called with a null
initial source file, i.e. the \fIfile\fP should be omitted from the command to
enter \fIGuide\fP.
.rE
.Nl
.sp
.Bu l 1 n
\fIGraphics\fP:
.bU
.Re
.Gu "GRAPHICS:
.Nl "#GT@
the text can include rectangular bitmap pictures.
.rE
.Nl
.sp
.Bu l 1 n
\fIMulti-way replacements\fP:
.bU
.Re
.Gu "MULTI-WAY REPLACEMENTS:
.Nl "#GT@
buttons can be presented as alternatives by using the `\fIEnquiry\fP' mechanism,
e.g. `Is\ it\ \fBBlue\fP\ or\ \fBGreen\fP?'.
.rE
.Nl
.sp
.Bu l 1 n
\fIViews\fP:
.bU
.Re
.Gu "VIEWS:
.Nl "#GT@
the \fIGuide\fP window can be divided into as many as four separate
views (sub-windows), each working on a separate source file.
Normally one view is reserved for the glossary.
.rE
.Nl
.sp
.Bu l 1 n
\fISaving\fP:
.bU
.Re
.Gu "SAVING:
.Nl "#GT@
it is possible to save the complete text as viewed (the \fIdocument\fP) or
the underlying source from which it was created.
A reader who, say, wanted a print-out of his tailored document might do the
former, whereas the author of a new source file would do the latter.
.rE
.Nl
.sp
.Bu l 1 n
\fIUndoing\fP:
.bU
.Re
.Gu "UNDOING:
.Nl "#GT@
the expansion caused by selecting a
.Bu g 1 n
replace-button\c
.bU
\& can be
`undone' by pointing the mouse and pressing the middle button (button B).
.rE
.Nl
.sp
.Bu l 1 n
\fILevels of reading\fP:
.bU
.Re
.Gu "LEVELS OF READING:
.Nl "#GT@
each
.Bu g 1 n
replace-button\c
.bU
\& has an associated \fIasking-level\fP,
and the user can set his \fIuser-level\fP.
All replace-buttons whose asking-level is below the user-level are automatically
expanded.
.rE
.Nl
.SH BUTTONS AND POINTING
Selection is done on both the SUN and PERQ-2 by pressing the left-hand button (called button A in the
Guide user manual) on the mouse.
The only uses of the other mouse buttons is that the middle button (button B) is used
to undo an expansion and the right-hand button (button C) is used to
.I pre-set
(i.e. to select permanently) a
.Bu g 1 n
replace-button\c
.bU
\&.
If a replace-button is pre-set, then every time a replace-button with that name
occurs it is automatically selected.
For example, if the replace-button \fBMore\fP was pre-set, then every
other \fBMore\fP replace-button would automatically be expanded.
The names of pre-set replace-buttons are shown at the very start of the text
when \fIGuide\fP is in author-display; these names can be edited
just like any other text.
.SH SAMPLE SOURCE FILES
An example \fIGuide\fP source file, which explains how the UNIX \fIrm\fP command
works, can be executed by the command:
.in +7n
.sp .5
\fIguide  rm\fP
.in -7n
.sp .5
Tutorial information can be displayed by the command \fIguide\ learn.gu\fP.
Several other sample source files can be found in the directory \fI/usr/lib/guide\fP.
.SH WINDOWS
.I Guide
runs in the current window.
It must be run under the window manager.
The size of the window can be changed while \fIGuide\fP is running, and \fIGuide\fP will
reformat the display automatically when this happens.
.SH OPTIONS
The options have the following meanings:
.TP
.B \-v
verifies that definitions exist for each
usage-button or glossary-button which depends on a definition.
Other types of usage-button or glossary-button
(e.g. those that load a file) are not checked;
however this checking can be done for usage-buttons by loading with
the \fI\-u4\fP option (which causes all replace-buttons to be
replaced) and then viewing the whole source.
As each part of the source is generated, any relevant error messages will appear.
(An automatic way of scanning the whole source, which saves a lot of time when checking
large files, is to Save it in a gash file using the Text option.)
.TP
.B \-V
is like \fI\-v\fP, but has the additional check that a warning is given for every
local-button or definition-button that has a null replacement.
.TP
\fB\-f\fP\fIS\fP
uses the \fIGuide\fP \fBFind\fP command to find the string \fIS\fP after loading is
complete.
This facility is valuable for focussing the screen when \fIGuide\fP is used as
a help system.
.TP
\fB\-b\fP\fIS\fP
is the same as the \fI\-f\fP option, but searching is confined to button names.
.TP
\fB\-u\fP\fID\fP
set the user-level to the value of the digit \fID\fP.
This means that, on each subsequent source file that is loaded, any
.Bu g 1 n
replace-button\c
.bU
\& with an asking-level less than \fID\fP is automatically
expanded.
.TP
.B \-m
the next argument that is a file is taken to be the name of a manual page
to be converted to \fIGuide\fP format (see `preprocessor').  Thus
.in +7n
..sp .5
\fIguide  \-m  ls\fP
.in -7n
.sp .5
displays the manual page for \fIls\fP.
.TP
\fB\-m\fP\fIC\fP
where C is a character, is like \fB\-m\fP, but the search is confined to the section
of the manual pages given by C (e.g. \fIguide\ \ \-m2\ \ chmod\fP).
.TP
.B \-p
the next argument that is a file is taken as the filename of a manual page to be
converted.
(This is useful for testing draft manual pages that have not yet been incorporated
into a \fIman\fP directory.)
.TP
.B \-c
use colour.
(The use of colour is currently rudimentary.)
.TP
.B \-s
if a transcript is replayed, replay it slowly, repainting the screen after each action (normally the screen is only repainted when the transcript has finished).
.TP
.B \-t
write a transcript to the file `transcript'.
Writing ends at the end of the \fIGuide\fP session, or earlier if the \fBNew\fP
command is used.  A transcript is an ordinary \fIGuide\fP source file and can be loaded
in the normal way.  Note that transcripts in \fIGuide\fP are an EXPERIMENTAL feature.
.LP
Options may also be specified within the list of filenames supplied when using
the \fBNew\fP command.
.SH "LIMITED VERSIONS OF GUIDE
Some other programs use \fIGuide\fP to display their documentation.
These may use a reduced form of \fIGuide\fP, called \fIguide\-s\fP; this lacks
the authorship facilities, and has no \fBAuthor\fP command in its menu.
.SH SIGNALS
If \fIGuide\fP receives an EMT signal, it treats this as a request to
re-focus the screen by using the \fIGuide\fP \fBFind\fP command.
In this case the file \fI/tmp/guidefind\fPN, where N is the PID of \fIGuide\fP,
should contain a string that looks like a \fI\-f\fP or \fI\-b\fP option to
\fIGuide\fP (e.g. \fI\-f\&copy\fP to find the string `copy').
Note that there should \fInot\fP be a newline at the end of this file unless
the sought string is to end with a newline.
.SH PREPROCESSOR
\fIGuide\fP can have a \fIpreprocessor\fP incorporated into it.
\fIGuide\fP is a presentation tool, and the role of a preprocessor is
to extract the material to be presented; this may, for example, come from a
database.
.PP
The standard preprocessor issued within \fIGuide\fP is an interface to two sets
of information: (1) some public \fIGuide\fP source files; (2) the UNIX manual pages.
This preprocessor looks at each filename that the user requests as a
\fIGuide\fP source for loading.
We will first cover case (1) above, i.e. when the filename is \fInot\fP to
be treated as a manual page.
.SH "PREPROCESSOR: FINDING GUIDE FILES"
If the filename is a directory, this becomes the \fIremembered directory\fP.
The remembered directory provides a way for the user to request that
a sequence of subsequent filenames is to be loaded from this directory.
(Initially the remembered directory is the current directory.)
.PP
If the filename is not a directory, then the preprocessor searches a sequence of directories to try to find the filename.
Usually the exact mechanism of the search should not concern the average
user: his view is that he specifies a filename, \fIbicycle\fP say, and the
preprocessor magically loads a source file that contains information about bicycles.
However those who create source files need to know how to exploit the
searching mechanism, so we explain it here.
.PP
The search proceeds as follows:
.TP
(A)
if the filename contains a `/', no preprocessing takes place.
.LP
Otherwise a search for the filename is made in the following sequence of directories:
.TP
(B1)
the remembered directory.
.TP
(B2)
the current directory.
.TP
(B3)
the \fI/usr/lib/guide\fP directory.
This directory, or its sub-directories, should be used for all public
\fIGuide\fP source files.
.TP
(B4)
the sub-directories of \fI/usr/lib/guide\fP.
These are searched in alphabetical order.
Such sub-directories are useful for sets of related source files:
thus all the source files concerned with office procedures might be put
in \fI/usr/lib/guide/office\fP.
One sub-directory is omitted from the search: this is the sub-directory
\fIetc\fP, which can be used for \fIGuide\fP files that are not sources, e.g.
fonts, conversion programs, etc.
Moreover sub-directories of sub-directories are not covered by this search, so
these can also contain arbitrary files.
.LP
If at any stage the search finds the required filename (and it has read permission)
this is taken as the source file to be loaded.
.SH "PREPROCESSOR: CONVERTING MANUAL PAGES"
If the \fI\-m\fP or \fI\-p\fP option precedes a filename, it is treated
as a reference to a UNIX manual page; for example if the filename is \fIls\fP,
then the manual page for \fIls\fP will be taken.
The preprocessor searches all the manual pages (just as the Unix
\fIman\fP command does) to find its quarry;
the manual page, when found, is automatically converted to \fIGuide\fP format before
it is loaded.  (This facility may not be available in \fIguide\-s\fP.)
.PP
The exact details of the above conversion process are as follows.
To save repeated conversions, the preprocessor keeps the converted files
in a cache under the directory \fI/usr/lib/guide/man\fP.
Within this directory, the sub-directory \fIcache1\fP contains the converted
manual pages for Chapter 1 of the \fIUNIX Programmer's Manual\fP (and thus
contains cached material derived from \fI/usr/man/man1\fP), the sub-directory
\fIcache2\fP contains converted manual pages for Chapter 2, etc.
If a cache directory does not exist, or is not writeable, no caching is done.
.PP
If a subsequent attempt is made to load the same manual page, the cache is
used to speed loading by avoiding a re-conversion of the manual page.
The cached file is not, however, used if the manual page has been changed since the
cached file was created.
.PP
The option \fI\-m\fP\fIC\fP, where \fIC\fP is a character, can be used to constrain
the preprocessor to look within a particular Section of the manual (and its corresponding cache).
.SH "PREPROCESSOR: FINDING GLOSSARY FILES"
The preprocessor is also used to pick the correct 
.Bu g 1 n
definitions-file\c
.bU
\&.
\fIGuide\fP definitions-files are always called \fIglossary.guide\fP,
and typically such a file will exist within most directories used for
\fIGuide\fP source files.
The preprocessor identifies the last file that was loaded in the current view,
and takes the file \fIglossary.guide\fP from the same directory
as this file.
Thus if the last file was \fI/usr/lib/guide/office/claim\fP the
definitions-file will be taken as \fI/usr/lib/guide/office/glossary.guide\fP.
The preprocessor does not conduct a search for a definitions-file; if
the required one does not exist it gives an error.
If no source files have been loaded in the current view, the definitions-file will be taken from
the current directory.
.SH "ENVIRONMENT VARIABLES"
.IP GUIDELIB 36n
If the \fIGuide\fP library is not in \fI/usr/lib/guide\fP, then GUIDELIB can be set to say where it is.
.IP GUIDEPAGES 36n
If the manual page(s) to be converted by the preprocessor are not in \fI/usr/man\fP,
then GUIDEPAGES can be set to say where they are.
.IP "GUIDEFONT, GUIDEBUTTONFONT, GUIDECONTROLFONT" 36n
These are the fonts that \fIGuide\fP uses (see below).
.SH FILES
.IP /usr/lib/guide/README 36n
summary of the contents of \fI/usr/lib/guide\fP and its sub-directories.
.IP /usr/lib/guide/etc/guidefont 36n
normal font used for text; this can be linked to any desired font.  (The only proviso is that the font's base-line should have been set correctly \(em this is not always the case with fonts supplied on the PERQ.)  Alternatively the environment variable GUIDEFONT can be used to set the font used for text.
.IP /usr/lib/guide/etc/gvar.r.13 36n
default \fIGuide\fP font for some workstations; when \fIGuide\fP is installed, \fIguidefont\fP is linked to this.  (On the PERQ, the font \fIvar13.kst\fP is used.)
.IP /usr/lib/guide/etc/fix13.kst 36n
alternative \fIGuide\fP font for the PERQ, for those who like typewriter-like fonts.
.IP /usr/lib/guide/etc/buttonfont 36n
font used for
.Bu g 1 n
replace-button\c
.bU
s; this can be linked to any desired font.  Alternatively the environment variable GUIDEBUTTONFONT can be used to set the font used for replace-buttons.
.IP /usr/lib/guide/etc/gscreen.b.14 36n
default button font for some workstations; when \fIGuide\fP is installed, \fIbuttonfont\fP is linked to this.  (On the PERQ, the font \fIgach16.kst\fP is used.)
.IP /usr/lib/guide/etc/italic20.kst 36n
alternative button font for the PERQ, for those who like big buttons.
.IP /usr/lib/guide/etc/control.kst 36n
font used for the control characters shown when \fIGuide\fP is in author-display.  Alternatively the environment variable GUIDECONTROLFONT can be used to set the font used for control characters.
.IP /usr/lib/guide/etc/*.cur 36n
cursor patterns for early \fIGuide\fP versions on the PERQ.
.IP glossary.guide 36n
the
.Bu g 1 n
definitions-file\c
.bU
\&.
.IP /usr/lib/guide 36n
recommended directory for public source files.
In particular this may contain demonstration files, including files for teaching how
to use \fIguide\fP (\fIlearn.gu\fP), and the file \fIlocal.gu\fP, which describes
any characteristics of the current implementation that are not covered by this manual page.
.IP /usr/lib/guide/man/cache* 36n
directories containing cache files created by the standard preprocessor.
.IP /usr/lib/guide/etc/moption.script 36n
shell script used by the standard preprocessor to convert manual pages to \fIGuide\fP format.
.IP /usr/lib/guide/etc/moption.macros 36n
\fInroff\fP macros used by the standard preprocessor to convert manual pages.
.SH "SEE ALSO"
.Bu g 1 n
man(1)\c
.Gu"	load -m1 man
.bU
\&,
.Bu g 1 n
spell(1)\c
.Gu"	load -m1 spell
.bU
\&
.sp 0.5
P.J. Brown, \fIGuide user manual\fP,
which is available from the Software Tools Centre, Computing Laboratory,
The University, Canterbury, Kent CT2 7NF, UK.
.sp 0.5
P.J. Brown, \fIUsing Guide as a help-system\fP.
.sp 0.5
P.J. Brown, \fIThe format of Guide source files\fP.
.SH BUGS
The
.Bu g 1 n
thumb-bar\c
.bU
\& sometimes sometimes appears to behave oddly; this is because
\fIGuide\fP deals with dynamic documents that may be continually changing
in size.
.PP
When the preprocessor converts a manual page it uses \fInroff\fP, which has a
maximum output line length of a few hundred characters.
When \fInroff\fP reaches its limit it throws in a newline; a consequence is that long
converted paragraphs from manual pages have a few extra newlines in them.
.PP
When the preprocessor finds a file that is represented by a symbolic link, then \fIGuide\fP
may know the file under the destination name.  This may confuse the user when he tries
to save the file: \fIGuide\fP will present him with a default filename that is
different from the name of the file loaded (though in reality both names represent the same
file).
.Nl
.Gc ".SH DEFINITIONS OF TERMS
.Nl
.Bu d 1 n
.Gu "definitions-file
.bU
.Re
.Gu "Definitions-file:	is a file that Guide searches for definitions of glossary-buttons.
.Gu
.Gu "  Its name must be `glossary.guide'.
.rE
.Nl
.Bu d 1 n
.Gu "glossary-button
.bU
.Re
.Gu "Glossary-button:	a button whose name is underlined.  When you select a glossary-button,
.Gu
.Gu " Guide searches for a corresponding definition for the name; the definition may be 
.Gu
.Gu "in the same source as the glossary-button or it may be in a separate 
.Bu g 1 n
.Gu "definitions-file
.bU
.Gu .
.Gu "  When Guide has found the definition, it inserts it displays the definition in a 
.Gu
.Gu "separate part of the screen.  Glossary-buttons are useful for explaining jargon, for 
.Gu
.Gu "footnotes, for citations, etc.
.rE
.Nl
.Bu d 1 n
.Gu "marker-bar
.bU
.Re
.Gu "Marker-bar:	A thin vertical bar with a blob on top, which is used to mark the current 
.Gu
.Gu "position.  The marker-bar is placed by pointing at the desired position and then pressing 
.Gu
.Gu "the left-hand button on the mouse.
.rE
.Nl
.Bu d 1 n
.Gu "replace-button
.bU
.Re
.Gu "Replace-button:	is a button displayed in large bold characters (in the same way as 
.Gu
.Gu "the menu).  If you select a replace-button it is replaced in situ by some text (and/
.Gu
.Gu "or graphics) that has been associated with that button by the author of the document.
.Gu
.rE
.Nl
.Bu d 1 n
.Gu "scroll
.bU
.Re
.Gu "Scroll:	A scheme for displaying information as if it were like a continuous scroll 
.Gu
.Gu "of paper.  The term `scrolling' is used to mean moving backwards or forwards through 
.Gu
.Gu "a scroll.
.rE
.Nl
.Bu d 1 n
.Gu "thumb-bar
.bU
.Re
.Gu "Thumb-bar:	is used for moving around documents.  It is the horizontal bar displayed 
.Gu
.Gu "underneath the Guide menu.  Try pointing at various places in it and you will see 
.Gu
.Gu "its effect.
.rE
.Nl
