.\" $Header: fs.l,v 1.11 87/02/23 19:09:03 mtr Exp $
.vs 13
.ps 11
.TH FS 1 "29 January 1987"
.tr *\(** \" make asterisks level with the base line
.SH NAME
fs \- screen oriented file system editor
.SH SYNOPSIS
\fBfs [directory ...]\fP
.SH DESCRIPTION
\fIFs\fP exploits the screen and mouse of a workstation to make
exploring and maintaining a UNIX file system easier.
Files are displayed as objects on the screen which can be
selected by pointing with the mouse.
Changes to the file system are made by editing the display \(em
for example, to change the name of a file you simply edit its
displayed name.
.LP
The main features of \fIfs\fP are:
.IP "   \(bu"
you can explore the file system by `expanding' and `collapsing'
directories.  (Expanding a directory means displaying all the files within it;
collapsing is the opposite of expanding.)
.IP "   \(bu"
file names, permissions, etc., can be changed simply by editing the display
.IP "   \(bu"
there are no keyboard commands \(em commands are given using a menu
.IP "   \(bu"
all commands which modify the file system (including removal of
files) can be undone
.IP "   \(bu"
\fIfs\fP communicates with \fIvf\fP and \fIspy\fP to allow you
to examine and edit the contents of files
.IP "   \(bu"
files in a directory can be sorted by a variety of criteria such
as size, time modified, etc.
.IP "   \(bu"
files can be selected by pointing or by typing a conventional
pathname with metacharacters
.SH "THE DISPLAY"
The initial \fIfs\fP display shows the directories from root to
the current directory; the current directory is expanded to show all the files
within it.  (If a directory is supplied as an argument when \fIfs\fP is invoked,
then this is used instead of the current directory.)
Indenting is used to display the tree structure of the file system \(em files in a
directory are indented one more tab than their parent directory.
.LP
To help the reader to know the nature of each file, a tag character is appended
to certain filenames.
The tag characters and their meanings are:
.RS
.IP /
directory
.IP *
executable file
.IP @
symbolic link (only applicable to the bsd version of Unix)
.IP =
socket (bsd only)
.IP ~
window special file (Perq only)
.RE
.LP
On bsd systems such as the Sun, symbolic links may have an extra tag character
before the `@' tag.
This extra tag indicates what type of file the symbolic link points at, and
is one of `/' (directory), `*' (executable), `=' (socket) or `?' (dangling).
A dangling symbolic link is one which points at a nonexistent file.
.SH "USE OF BUTTONS"
In this description, the buttons are called button A, button B,
and button C.
The current function of each of the mouse buttons is always shown in the
`mousehole' that is displayed to the right of the menu.
Selecting an object or an action on the screen is generally done by pressing
and releasing a button on the mouse.
The term `clicking' a button means pressing and releasing the button.
Several of the commands in the menu have associated pop-up submenus; the
submenu appears while the button on the mouse is held down.
For those interested in exact detail, a full description is given below.
.LP
On the Perq three-button puck and Sun mouse these correspond to
the left, middle, and right buttons.
On the Perq four-button tablet they are the white (left), yellow (top) and
green (right) buttons.
.LP
In the display area buttons A and C are used to select files
(see SELECTING FILES), and button B is used for editing fields
(see CHANGING FILENAMES AND PERMISSIONS).
Everywhere else button A only is used.
.LP
Button C is also used to interrupt long running operations (see
INTERRUPTING COMMANDS).
.SH "SELECTING FILES"
All operations in \fIfs\fP are performed by
selecting a set of files or directories, and then choosing
a menu operation to be performed on the selection.
To select a file, point at its name and press and release button A.
The name will be displayed in inverse video to show it has been selected.
To select several files whose names are adjacent on the screen,
press button A over the first one, drag the
cursor over the files to be selected, and release button A.
.LP
Button C is used to change the selection.
It is used in the same way as button A, except that it does not clear
any previous selection when it is pressed.
It can thus be used to make a selection of several files that are not adjacent on the screen.
Button C here acts as a toggle: pressing or dragging it over files which are
already selected deselects them.
Thus is is possible to select, say, all the files in a directory then
deselect any unwanted files.
.LP
It is also possible to select files by typing their names \(em see
SELECTING FILES BY NAME below.
.LP
Selected files are also indicated by a mark on the
.Bu g 1 n
thumb bar\c
.bU
\& (which appears at the top of the display area).
This means that it is possible to check whether there are any files selected
but not visible because they have been scrolled off the display area.
.SH "EXPANDING AND COLLAPSING DIRECTORIES"
The normal way of navigating the file system in \fIfs\fP is to
expand and collapse directories.
To expand a directory, select it then select the \fBExpand\fP
menu command.
This produces a pop-up menu offering the options \fBCompletely\fP
and \fBFirst\ level\fP:
\fBFirst\ level\fP just shows the files in this directory;
\fBCompletely\fP recursively expands any subdirectories \(em
it expands the complete tree below the selected directory.
.LP
The files in the selected directories are displayed, indented one
stage more than their parent directory.
For ease of reading
the display is always organised so that, in a list of files within a directory,
the files that are themselves expanded directories are placed at the end.
(As a consequence,
expanding a directory may rearrange the display since the directory will gravitate to the end.)
.LP
The \fBCollapse\fP operation is the reverse of \fBExpand\fP.
It removes the files in a directory from the display.
As with expand, the options \fBFirst\ level\fP and
\fBCompletely\fP offer a choice of collapsing subdirectories or
not.
.LP
If you \fBExpand\fP a symbolic link to a directory, the directory that is
pointed at is expanded and selected directly.
Symbolic links to directories are marked with a trailing `/@', as described
in above.
.SH "SCROLLING THE DISPLAY"
Usually expanding a directory means that not all of the files
will fit in the display area, and it becomes necessary to scroll
the display.
To the left of the display area is a scroll bar like that of \fIspy\fP(1).
To scroll, point within the scroll bar, hold down button A and move the mouse in the
direction you want to scroll.
The further you drag the puck the faster the scrolling.
Release button A to stop the scrolling.
.LP
The thumb bar provides an alternative way of changing the display area: instead of
continuous scrolling it moves directly to the place selected.
The thumb bar appears just above the display area, again as in \fIspy\fP.
Clicking button A in the thumb bar moves the display
to the place selected.
.LP
The thumb bar is also used to show which files are selected.
Any selected files are indicated by marks at the bottom of the thumb bar.
.SH "INFORMATION ABOUT FILES"
Initially just the names of files are displayed.
You can request more information with the \fBDetails\fP menu
command.
This offers the options \fBNone\fP, \fBSome\fP, and \fBAll\fP.
.IP \fBSome\fP
replaces each selected file name with a line of information about
the file. (This is in the same format as \fIls\fP(1) with its \fB\-l\fP
option.)
As with \fIls\fP, symbolic links are displayed as 
\fIlinkname\fP\ \->\ \fIlinkvalue\fP, where \fIlinkvalue\fP
is the name of the file that the symbolic link points to.
.IP \fBAll\fP
gives yet more information about the selected files.
Three lines of information are displayed, giving such things as
the
.Bu g 1 n
inode\c
.bU
\& number of the file and which disk device it resides on.
.IP \fBNone\fP
removes any displayed details for the selected files.
.LP
Most of the fields displayed under \fBSome\fP and \fBAll\fP
details are editable (see CHANGING FILENAMES AND PERMISSIONS).
.SH "SORTING THE DISPLAY"
When a directory is first expanded its files are sorted in alphabetical
order (but with files and non-expanded directories before any expanded
directories). 
It is often useful to sort by some other criterion.
For example, sorting by file size groups all the large files in a
directory at the start, which is useful if you want to reclaim
disk space.
The \fBSort\fP command offers a selection of alternative sorting criteria.
All of these still maintain the `expanded directories last' ordering.
They are:
.IP "\fBBy\ name\fP" 12n
The standard alphabetical sort \(em it can be used to restore
this ordering after a previous sort.
.IP "\fBBy\ suffix\fP" 12n
sorts first by suffix (characters following a `.')
and then alphabetically.
Files without a suffix appear last.
Filenames with different suffixes are separated by markers (horizontal lines).
This is useful in directories where the suffix indicates the type of the
file.
For example, in a C source directory, sorting by suffix groups
together all the header (.h), source (.c) and object (.o) files,
and leaves all others in a group at the end.
.IP "\fBBy\ mode\fP" 12n
sorts on the permissions and file type.
This is useful because it groups files with the same types or permissions
together, and hence makes it easy to spot files with peculiar
permissions (e.g. setuid bit set, or general write permission).
It also groups files of the same type
(symbolic link, directory, etc.) together on the display.
.IP "\fBBy time modified\fP, \fBBy time accessed\fP and \fBBy size\fP"
.br
sort on the specified field.
.LP
When sorting is applied to an expanded directory, this sorts all the files in that directory.
If several files or non-expanded directories in the same parent directory
are selected, they alone are sorted and moved to the start of the directory,
without affecting the ordering of non-selected files in the parent directory.
Thus you can, for example, sort all the files in a directory by suffix,
then select all the `.c' files and sort them by size.
.SH "VIEWING AND EDITING FILES"
When using \fIfs\fP to explore the file system it is often useful to
look at the contents of a file.
\fIFs\fP does this by calling either \fIvf\fP(1) or \fIspy\fP(1).
.LP
\fIVf\fP is a screen-based program for displaying files, and supports
thumb bars from moving around.
It guesses the nature of the content of each file and displays it accordingly; for
example a file that contains a font is indeed displayed as a font.
\fISpy\fP (a screen editor) knows only about text files, but unlike
\fIvf\fP it can be used to edit files.
For more details about \fIspy\fP and \fIvf\fP, see their manual pages.
.LP
To look at a file or files, select them then use the \fBView\fP
or \fBSpy\fP commands from the \fIfs\fP menu.
In either case you will be prompted for a window.
To indicate the window position and size you want, press button A
anywhere on the screen, drag the mouse until the window (which is at this stage
shown as a `rubber box')
is the right size and then release the button.
\fIVf\fP or \fIspy\fP will be started in the new window with
the selected files as arguments.
.LP
\fIVf\fP and \fIspy\fP differ in that the \fBSpy\fP command
always prompts for a new window, whereas the \fBView\fP command
will reuse an existing \fIvf\fP if it is still running.
This means that it is quick and easy to \fIvf\fP a succession
of files one after another from \fIfs\fP.
.SH "CHANGING FILENAMES AND PERMISSIONS"
Most of the fields in the display area are editable.
To edit a field, point at it with button B.
A
.Bu g 1 n
\fImarker-bar\fP\c
.bU
\& will appear on the display to show the point that can be edited.
Characters typed are inserted at the position of the marker-bar, and the Delete and Line-kill (CONTROL\-U or, on the PERQ, OOPS) keys work as normal.
An edit is confirmed by typing RETURN or by pointing elsewhere on
the display.
Alternatively, you can cancel an edit with CONTROL\-C \(em this
restores the original value of the field.
.LP
When you confirm the edit, \fIfs\fP tries to make the indicated
change to the file system.
If the change requested is not possible (for example, trying to rename a
file to a name that is already used), a message is given and the
.Bu g 1 n
marker-bar\c
.bU
\& remains in the field.  If you immediately try to confirm the
edit again, the changes made are cancelled (i.e. the original field
value is restored and no changes are made to the file system).
.LP
The editable fields and the effects of editing them are as follows:
.IP "\fIfile name\fP"
.br
Editing this renames the file.  You cannot type a `/' \(em that is, you
cannot change the directory that the file lives in.
If you make a file name longer it is possible to overwrite parts
of the display to the right of the name being edited.
This does not matter \(em the display will be tidied up when
you finish the edit.
.IP "\fIpermissions\fP"
.br
The permissions field gives the read write and execute permissions for the file.
As far as editing is concerned, it is a special case in that it has a fixed length.
Characters entered are not inserted \(em rather they overwrite characters
already displayed.  
For example if you point at a `\-' (which indicates that a particular permission is off),
and type `w', then the `w' overwrites the `\-'.
Also, at each position, only the characters
that could appear at that position are legal; thus you are prevented from typing
`w' in a read-permission position.
.IP
At any position, typing a `\-' turns off that permission.
A space (backspace) moves the marker-bar one place forwards (backwards).
The Delete key turns off the permission at the marker-bar and moves the marker-bar one space
backwards.  The `r', `w' and `x' keys turn on the corresponding
permissions if typed at the correct position.  Typing an `s' at
the user (group) execute permission position turns on the setuid (setgid) bit.
If you are the superuser, typing a `t' at the "others" execute permission
position sets the `sticky' bit for the file.
.IP
For the meanings of the permission bits see \fIls\fP(1).
.IP "\fImodified time and accessed time\fP"
.br
Editing these fields changes the last modified time or accessed time of a file.
\fIFs\fP accepts dates in free format, supplying appropriate
defaults for any missing parts of the date.  Examples of valid
dates and their meanings are `10/4/74' (10th of April 1974),
`10 pm' (22:00 today), `March 17 1997', etc.
Years must be in the range 1970 to 2029.
.IP "\fIowner and group\fP"
.br
Only the superuser may edit these fields.  The owner field can be edited
to a number or to the name of a user.
Similarly, the group of the file may be numeric or the name of a
group.
.IP "\fIsymbolic link value (bsd only)\fP"
.br
This field (shown under `some details') shows which file a symbolic link
points to.
Editing it points the symbolic link at the file given by the new field
value (the file need not exist).
.SH "MODIFYING THE FILE SYSTEM"
The top row of menu commands are commands which change the file system
tree, in contrast to the field editing commands which change
individual files.
.LP
These commands (\fBCopy\fP, \fBMove\fP, \fBLink\fP, \fBRemove\fP
and \fBMkdir\fP) are applied to each selected file in turn, in no
particular order.
.LP
If a command fails for one selected file, the operation stops with
an error message at that point \(em thus some of the selection will have had
the operation performed, some not, depending on the ordering of the selection.
The \fBUndo\fP command (below) works correctly on partially complete operations
arising this way.
.LP
The commands are:
.IP \fBCopy\fP 9n
make new copies of files or directories
.IP \fBLink\fP 9n
make hard links to files, or symbolic links to files or directories
.IP \fBMove\fP 9n
move files or directories
.IP \fBRemove\fP 9n
remove files or directories
.IP \fBMkdir\fP 9n
make a new directory
.IP \fBUndo\fP 9n
undo any of the above
.LP
.SH "COPY, MOVE AND LINK"
These commands copy, move and link the selected files into a directory.
You use each in the same way:
.IP "1."
make a selection in the normal way
.IP "2."
select \fBCopy\fP, \fBMove\fP or \fBLink\fP from the menu (\fBLink\fP
has a submenu offering the choice of hard links,
or absolute or relative symbolic links).
The selected menu box goes grey and the cursor changes.
.IP "3."
use the scroll bar and thumb bar if necessary to make the destination
directory visible.
.IP "4."
point with button A at the destination directory.
All the selected files will be copied to, moved to, or have links made
in, the directory that is pointed to.
.LP
To abandon the operation after selecting it from the menu and
before pointing at a destination directory, click button C.
.LP
All new files become the immediate children of the destination 
directory \(em the positions in the file system tree of the original
files is ignored.
There is, however, one exception to this \(em see COPYING DIRECTORIES below.
.LP
If the source and destination directories for a copy or a link are the
same, a suffix is added to the name of the new file to distinguish it from
the original.
Moving a file within its original directory just rearranges the display.
.LP
If the source and destination directories are different and doing the
move or copy or link would overwrite an existing file in the destination
directory, that file is moved out of the way by having the suffix
`.old' added to its name.
.SH "COPYING DIRECTORIES"
If a directory is selected for copying, a new directory is
made in the destination with the same name as the original,
unless such a directory exists already.
.LP
In addition, any selected files or directories in the original directory
are copied into the newly created directory.
Thus children of the original directory become children of the copy.
This applies recursively to any subdirectories in the original.
Directories are created as necessary to duplicate the tree structure of
the original.
.LP
Thus to copy a complete subtree, select the directory at the root of
the subtree, expand it completely, select all the newly displayed files,
and copy the root of the subtree to the destination.
.LP
It must be stressed that this applies only to \fIcopying\fP
directories, not to moving them.
To move a directory and all its subdirectories it is only
necessary to select the directory itself.
If you select a directory and all its descendents and move it,
all the new files will be at the same level, together with
a lot of empty directories (you can use \fBUndo\fP to restore
things as they were if you do this by accident).
.SH "MAKING NEW DIRECTORIES"
The \fBMkdir\fP command creates a new, empty,
unexpanded directory called `Newdir' in all the selected
directories.
Normally you would edit the name after creating the directory.
.SH "REMOVING FILES AND DIRECTORIES"
The \fBRemove\fP command removes (i.e. deletes) files or directories.
It produces a submenu with the options \fBReversibly\fP and
\fBIrreversibly\fP (separated for safety by blank menu lines so that if you
accidentally just miss one option you will not hit the other).
The former allows you to retrieve files if, at a later stage within the \fIfs\fP
session, you decide that you did not after all want to delete them.
This retrieving can be done in one of two ways:

.Bu l 1 n
.Gu "1: Immediately after removal
.bR
.Gu "1: Immediately after removal
.IP
\fIBy using the \fP\fBUndo\fP\fI command\fP
to cancel the previous command.
This can only be done, of course, if you have not executed any other \fIfs\fP
command after the \fBRemove\fP command.
.rE
.LP
.Bu l 1 n
.Gu "2: Later in the session
.bR
.Gu "2: Later in the session
.IP
\fIBy copying the saved files\fP that are kept by the \fBUndo\fP command.
When you select \fBRemove\fP reversibly, the files are moved into a directory
`\fI/tmp/fs\fP' (or `\fI/tmp/fs1\fP', etc., if there are multiple instances of \fIfs\fP
running).  If the file being removed is on a different device from the \fI/tmp\fP
directory,
the move involves a copy, so reversibly removing big files in this
case can take some time.
These saved files remain until you \fBQuit\fP from \fIfs\fP.
Thus you can subsequently rescue files by moving them from \fI/tmp/fs\fP.
A saved file has the same name that it had in its original
directory except that a number is added after the name if there was
already a file with that name in \fI/tmp/fs\fP.
.rE
.Nl
.LP
The \fBIrreversibly\fP option just
.Bu g 1 n
unlink\c
.bU
s the files, with no possibility of
restoring them; it should be used
with caution.
.LP
As a safety precaution, files which are selected, but not visible on the
display will not be removed \(em if there are any such files a message saying
how many were skipped is printed.  To remove them, just scroll the display
so that they are visible and repeat the \fBRemove\fP command.
.SH "UNDOING ACTIONS"
The \fBUndo\fP command undoes the effect of the immediately preceding \fBCopy\fP, \fBMove\fP,
\fBLink\fP, \fBRemove\fP (reversibly) or \fBMkdir\fP command.
The effect of an undo is shown by its caption in the menu: `[undo]' indicates that
undo is not available; otherwise `Undo' is followed by the operation
that would be undone (e.g. `Undo copy').
.LP
Undo works correctly whether the preceding operation completed
successfully or not.
If the operation was interrupted (either by the user aborting it
or because a part of it failed), that part of the operation that did
get done is undone. 
.SH "SELECTING FILES USING THE MENU"
The \fBSelect\fP command produces a submenu of options.
All options apart from the \fBPattern\fP option allow you to make a new selection based
on the current selection.
The options, and the selection resulting from them are:
.IP \fBParent\fP 12n
replaces the selection with the
parent directories of the currently selected files
.IP \fBChildren\fP 12n
replaces the selection with the children of the
currently selected files.
The children of an expanded directory are the files in it.
The child of a symbolic link is the file the link points to.
Thus to follow a symbolic link select it, and then use this option.
.IP \fBDescendents\fP 12n
adds to the selection all the trees below the selected directories.
This is useful if you want to remove an entire tree (to do this: select the root of
the tree; select this option of \fBSelect\fP, then \fBRemove\fP).
.IP \fBDirectories\fP 12n
removes from the selection everything except directories.
.IP \fBPattern\fP 12n
clears the selection and replaces it with the files that match
the pattern in the typing area \(em see the next section.
.LP
.SH "SELECTING FILES BY NAME"
It is often useful to select a file without
expanding every directory in its pathname.
This can be done by typing the file's name into the
.Bu g 1 n
\fItyping area\fP\c
.bU
\& at the
top of the \fIfs\fP window.
The file name given may contain metacharacters, which are interpreted as
in \fIcsh\fP(1).
It may thus expand to more than one file, so this mechanism can be
used to select groups of files (e.g. all the filenames ending in `.h'
in a given directory).
.LP
The
.Bu g 1 n
typing area\c
.bU
\& behaves like other editable fields \(em you can type
characters, point with the mouse and use the delete and line-kill (CONTROL\-U
or, on the Perq, OOPS) keys as normal.
.LP
When you select the \fBPattern\fP option from the \fBSelect\fP pop-up menu,
or hit the RETURN key,
the string in the typing area is interpreted as a path or paths as
described below, and the files that match it are selected.
.LP
The file name given on the typing line is in its simplest form the full
path name of a file from root.
Multiple paths may be given, separated by spaces.
Only the first of these need specify the path from root \(em subsequent
paths which do not start with `/' are assumed to be relative to the
directory of the last root relative path.
Thus the line

	\fI/usr/include/stdio.h signal.h stat.h\fP

 selects
the files \fI/usr/include/stdio.h\fP, \fI/usr/include/signal.h\fP, and
\fI/usr/include/stat.h\fP.
.LP
Pressing and releasing button A in the \fIpath:\fP box to the
left of the
.Bu g 1 n
typing area\c
.bU
\& places in the typing area the
pathname of the first selected directory; this saves having to type
it.
Entering CONTROL\-P has the same effect.
.LP
Each path may contain metacharacters which have the same meaning as
those in \fIcsh\fP(1).
The meanings of the metacharacters are as follows:
.IP *
matches as many characters as possible
.IP ?
matches any single character
.IP [xyz]
matches either x or y or z.  Ranges may be specified with a `\-' \(em
e.g. [a\-z\&A\-Z] matches any alphabetic character.
If the sequence starts with a `^', then it matches any character
\fInot\fP in the sequence.
.IP ~
at the start of a path and followed by `/' or the end of the path is
a shorthand for your home directory (obtained from the HOME environment
variable).
.IP ~\fIxyz\fP
at the start of a path is a shorthand for the home directory of the user \fIxyz\fP,
as given in the password file.
.IP x{a,b}c
is a shorthand for `xac xbc'.  As a more complex example, the pattern

		/usr/include/{,sun{tool,\&window},sys}/{README,*.h}

matches files called README or with names ending in `.h'
in the directories \fI/usr/include\fP, \fI/usr/include/suntool\fP,
\fI/usr/include/sunwindow\fP and \fI/usr/include/sys\fP.
.IP \e\fIc\fP
matches the literal character \fIc\fP.
This notation can be used to escape any of the metacharacters 
described above, including `,' inside curly
brackets, and `]' and `\-' in `[xyz]' sequences.
.LP
Symbolic links to directories in paths are resolved as they are
encountered.
For example, if there was a directory \fI/usr/d1/d2\fP, and a
symbolic link \fI/sl\fP to it, the pattern \fI/sl/*\fP would
select all the files in \fI/usr/d1/d2\fP.
.SH "INTERRUPTING COMMANDS"
Any command can be aborted by pressing the STOP key (the top left key
marked L1 on a Sun 3 keyboard).
This will leave the command partially complete.
If \fBUndo\fP is available for the command, it will correctly undo what
has been done.
.SH "THE REFRESH COMMAND"
\fIFs\fP will not automatically notice changes made to the file system
by other programs and its display can thus become out of date.
The \fBRefresh\fP command makes \fIfs\fP update its details on the
selected files and directories.
For files, the details of the file are updated.
For directories, the details of all the files in the directory are
updated, files that have disappeared are removed from the display,
and extra files that have appeared are added.
When refreshing directories, \fIfs\fP changes the display as
little as possible.
.SH "ERROR MESSAGES"
Error messages from \fIfs\fP appear (typically with a beep) at the top
of the window.
If the message is so long that you cannot see it all, you can point at the
message and hold down button A or button B to scroll the message to the left
or right respectively.
.SH "QUITTING FS"
The \fBQuit\fP menu command is used to quit from \fIfs\fP.
To prevent accidents, it has a submenu with the options \fBCancel\fP
and \fBConfirm\fP \(em you must select the \fBConfirm\fP option
if you really want to quit.
To do this point at the \fBQuit\fP command and hold down button A on the mouse;
the submenu will then appear.
Move the mouse so that you are pointing at the \fBConfirm\fP option in this submenu
and then release the button on the mouse.
.SH "BUGS"
There is no sideways scrolling in the display area \(em this means that sometimes details are
clipped at the right on
files deep in the hierarchy (and hence indented a lot).
.LP
There ought to be some sort of shell escape with a metacharacter for the
selection so ordinary commands can be run on the selection.
.SH "SEE ALSO"
.\" experimental use of a Guide transcript to link to another manual page
.Bu g 1 n
vf(l)\c
.Gu"	load -ml vf
.bU
\&,
.Bu g 1 n
spy(l)\c
.Gu"	load -m spy
.bU
\&,
.Bu g 1 n
ls(1)\c
.Gu"	load -m1 ls
.bU
\&,
.Bu g 1 n
mv(1)\c
.Gu"	load -m1 mv
.bU
\&,
.Bu g 1 n
cp(1)\c
.Gu"	load -m1 cp
.bU
\&,
.Bu g 1 n
ln(1)\c
.Gu"	load -m1 ln
.bU
\&,
.Bu g 1 n
mkdir(1)\c
.Gu"	load -m1 mkdir
.bU
\&,
.Bu g 1 n
rm(1)\c
.Gu"	load -m1 rm
.bU
\&,
.Bu g 1 n
rmdir(1)\c
.Gu"	load -m1 rmdir
.bU
\&,
.Bu g 1 n
chmod(1)\c
.Gu"	load -m1 chmod
.bU
\&,
.Bu g 1 n
chown(8)\c
.Gu"	load -m8 chown
.bU
\&
.Gc ".SH DEFINITIONS OF TERMS
.Bu d 1 n
.Gu "display area
.bU
.Re
.Gu "Display area:	the main part of the window, where the file system is displayed.
.rE
.Nl
.Bu d 1 n
.Gu "expand
.bU
.Re
.Gu "Expand:	`expanding' a directory shows all the files within it.  `Collapsing' is the 
.Gu
.Gu "opposite of expanding.
.rE
.Nl
.Bu d 1 n
.Gu "inode
.bU
.Re
.Gu "Inode:	a block of data containing vital information about a file.  Each inode is represented 
.Gu
.Gu "by a number that is unique within a file system.
.rE
.Nl
.Bu d 1 n
.Gu "marker-bar
.bU
.Re
.Gu "Marker-bar:	is a thin vertical bar which indicates the current point at which edits 
.Gu
.Gu "can take place.  To place the marker-bar point where you want it to go and click button 
.Gu
.Gu "B.
.rE
.Nl
.Bu d 1 n
.Gu "symbolic link
.bU
.Re
.Gu "Symbolic link:	is a facility, only available in some versions of UNIX, whereby one 
.Gu
.Gu "file name, when it is referenced, is automatically translated into another name.  
.Gu
.Gu "To create a symbolic link, use the Link command in fs; it can also be done using the 
.Gu
.Gu "UNIX command `ln -s'.
.rE
.Nl
.Bu d 1 n
.Gu "thumb bar
.bU
.Re
.Gu "Thumb bar:	is a horizontal area, just beneath the menu, which can be used to change 
.Gu
.Gu "the display area so that it points at a different part of the file system.  The black 
.Gu
.Gu "part of the thumb bar represents the information that is currently in view.  The thumb 
.Gu
.Gu "bar is only useful when the information is too big to fit into the display area.
.rE
.Nl
.Bu d 1 n
.Gu "typing area
.bU
.Re
.Gu "Typing area:	is the box to the right of the word `path:` on the screen.  You use it 
.Gu
.Gu "on the (comparatively rare) occasions when you want to type names into fs.
.rE
.Nl
.Bu d 1 n
.Gu "unlink
.bU
.Re
.Gu "Unlink:	is a UNIX term for removing a file.  When two file names are attached to the 
.Gu
.Gu "same file (using the `ln' command), then `removing' one name does not, in fact, delete 
.Gu
.Gu "the file -- since the other name remains.  Hence `unlink' is used rather than `remove'
.Gu
.Gu .
.rE
.Nl
