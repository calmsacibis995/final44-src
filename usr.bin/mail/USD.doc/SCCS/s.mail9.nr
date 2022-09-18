h50655
s 00000/00002/00175
d D 8.2 94/05/16 17:29:12 mckusick 7 6
c formatting update for 4.4BSD
e
s 00002/00002/00175
d D 8.1 93/06/08 12:42:52 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00172
d D 6.3 91/04/17 12:21:17 bostic 5 4
c new copyright; att/bsd/shared
e
s 00022/00009/00154
d D 6.2 90/06/19 20:29:57 leres 4 3
c Updates from Mark Andrews (mark%alias@yonge.csri.toronto.edu).
e
s 00157/00000/00006
d D 6.1 86/05/23 12:01:59 kjd 3 2
c document distributed with 4.3BSD
e
s 00000/00000/00006
d D 5.1 86/05/23 12:01:55 kjd 2 1
c document distributed with 4.2BSD
e
s 00006/00000/00000
d D 4.1 86/05/23 12:01:51 kjd 1 0
c document distributed with 4.1BSD
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
D 6
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 6
I 6
.\" Copyright (c) 1980, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 6
E 5
.\"
D 4
.\"	%W% (Berkeley) %G%
E 4
I 4
D 5
.\"	@(#)mail9.nr	6.1 (Berkeley) 5/23/86
E 5
I 5
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
E 5
E 4
.\"
I 3
D 7
.bp
E 7
.sh 1 "Summary of commands, options, and escapes"
.pp
This section gives a quick summary of the
.i Mail
commands, binary and valued options, and tilde escapes.
D 4
.(b
E 4
.pp
The following table describes the commands:
.TS
center ;
c ci
lb l.
Command	Description
_
D 4
!	Single command escape to shell
E 4
I 4
+	Same as \fBnext\fP
E 4
-	Back up to previous message
I 4
?	Print brief summary of \fIMail\fP commands
!	Single command escape to shell
E 4
Print	Type message with ignored fields
Reply	Reply to author of message only
I 4
Respond	Same as \fBReply\fP
E 4
Type	Type message with ignored fields
alias	Define an alias as a set of user names
alternates	List other names you are known by
chdir	Change working directory, home by default
copy	Copy a message to a file or folder
delete	Delete a list of messages
I 4
dp	Same as \fBdt\fP
E 4
dt	Delete current message, type next message
D 4
endif	End of conditional statement; see \fBif\fP
E 4
edit	Edit a list of messages
else	Start of else part of conditional; see \fBif\fP
I 4
endif	End of conditional statement; see \fBif\fP
E 4
exit	Leave mail without changing anything
file	Interrogate/change current mail file
folder	Same as \fBfile\fP
folders	List the folders in your folder directory
from	List headers of a list of messages
headers	List current window of messages
D 4
help	Print brief summary of \fIMail\fP commands
E 4
I 4
help	Same as \fB?\fP
E 4
hold	Same as \fBpreserve\fP
if	Conditional execution of \fIMail\fP commands
ignore	Set/examine list of ignored header fields
list	List valid \fIMail\fP commands
local	List other names for the local host
mail	Send mail to specified names
mbox	Arrange to save a list of messages in \fImbox\fP
next	Go to next message and type it
preserve	Arrange to leave list of messages in system mailbox
I 4
print	Print messages
E 4
quit	Leave \fIMail\fP; update system mailbox, \fImbox\fP as appropriate
reply	Compose a reply to a message
I 4
respond	Same as \fBreply\fP
retain	Supersedes \fBignore\fP
E 4
save	Append messages, headers included, on a file
set	Set binary or valued options
shell	Invoke an interactive shell
I 4
size	Prints out size of message list
source	Read \fImail\fP commands from a file
E 4
top	Print first so many (5 by default) lines of list of messages
D 4
type	Print messages
E 4
I 4
type	Same as \fBprint\fP
E 4
undelete	Undelete list of messages
I 4
unread	Marks list of messages as not been read
E 4
unset	Undo the operation of a \fBset\fP
visual	Invoke visual editor on a list of messages
write	Append messages to a file, don't include headers
I 4
xit	Same as \fBexit\fP
E 4
z	Scroll to next/previous screenful of headers
.TE
D 4
.)b
E 4
I 4
D 7
.bp
E 7
E 4
.(b
.pp
The following table describes the options.  Each option is
shown as being either a binary or valued option.
.TS
center;
c ci ci
l ci l.
Option	Type	Description
_
EDITOR	valued	Pathname of editor for ~e and \fBedit\fP
I 4
PAGER	valued	Pathname of paginator for \fBPrint\fP, \fBprint\fP, \fBType\fP and \fBtype\fP
E 4
SHELL	valued	Pathname of shell for \fBshell\fP, ~! and \fB!\fP
VISUAL	valued	Pathname of screen editor for ~v, \fBvisual\fP
append	binary	Always append messages to end of \fImbox\fP
ask	binary	Prompt user for Subject: field when sending
askcc	binary	Prompt user for additional Cc's at end of message
autoprint	binary	Print next message after \fBdelete\fP
D 4
crt	valued	Minimum number of lines before using \fImore\fP
E 4
I 4
crt	valued	Minimum number of lines before using \fBPAGER\fP
E 4
debug	binary	Print out debugging information
dot	binary	Accept . alone on line to terminate message input
D 4
escape	valued	Escape character to be used instead of ~
E 4
I 4
escape	valued	Escape character to be used instead of\ \ ~
E 4
folder	valued	Directory to store folders in
hold	binary	Hold messages in system mailbox by default
ignore	binary	Ignore \s-2RUBOUT\s0 while sending mail
ignoreeof	binary	Don't terminate letters/command input with \fB\(uaD\fP
keep	binary	Don't unlink system mailbox when empty
keepsave	binary	Don't delete \fBsave\fPd messages by default
metoo	binary	Include sending user in aliases
noheader	binary	Suppress initial printing of version and headers
nosave	binary	Don't save partial letter in \fIdead.letter\fP
quiet	binary	Suppress printing of \fIMail\fP version and message numbers
record	valued	File to save all outgoing mail in
screen	valued	Size of window of message headers for \fBz\fP, etc.
sendmail	valued	Choose alternate mail delivery system
toplines	valued	Number of lines to print in \fBtop\fP
verbose	binary	Invoke sendmail with the \fB\-v\fP flag
.TE
.)b
.(b
.pp
The following table summarizes the tilde escapes available
while sending mail.
.TS
center;
c ci ci
l li l.
Escape	Arguments	Description
_
~!	command	Execute shell command
I 4
~b	name ...	Add names to "blind" Cc: list
E 4
~c	name ...	Add names to Cc: field
~d		Read \fIdead.letter\fP into message
~e		Invoke text editor on partial message
~f	messages	Read named messages
~h		Edit the header fields
~m	messages	Read named messages, right shift by tab
~p		Print message entered so far
~q		Abort entry of letter; like \s-2RUBOUT\s0
~r	filename	Read file into message
~s	string	Set Subject: field to \fIstring\fP
~t	name ...	Add names to To: field
~v		Invoke screen editor on message
~w	filename	Write message on file
~|	command	Pipe message through \fIcommand\fP
I 4
~:	Mail command	Execute a \fIMail\fP command
E 4
~~	string	Quote a ~ in front of \fIstring\fP
.TE
.)b
.(b
.pp
The following table shows the command line flags that
.i Mail
accepts:
.TS
center;
c c
l a.
Flag	Description
_
\-N	Suppress the initial printing of headers
\-T \fIfile\fP	Article-id's of read/deleted messages to \fIfile\fP
\-d	Turn on debugging
\-f \fIfile\fP	Show messages in \fIfile\fP or \fI~/mbox\fP
\-h \fInumber\fP	Pass on hop count for mail forwarding
\-i	Ignore tty interrupt signals
\-n	Inhibit reading of /usr/lib/Mail.rc
\-r \fIname\fP	Pass on \fIname\fP for mail forwarding
\-s \fIstring\fP	Use \fIstring\fP as subject in outgoing mail
\-u \fIname\fP	Read \fIname's\fP mail instead of your own
\-v 	Invoke sendmail with the \fB\-v\fP flag
.TE
.)b
.lp
Notes:
.b \-T ,
.b \-d ,
.b \-h ,
and
.b \-r
are not for human use.
E 3
E 1
