h20120
s 00000/00001/01014
d D 8.2 94/05/16 17:29:07 mckusick 8 7
c formatting update for 4.4BSD
e
s 00002/00002/01013
d D 8.1 93/06/08 12:42:31 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/01010
d D 6.4 91/04/17 12:21:13 bostic 6 5
c new copyright; att/bsd/shared
e
s 00203/00150/00811
d D 6.3 90/06/19 20:29:50 leres 5 4
c Updates from Mark Andrews (mark%alias@yonge.csri.toronto.edu).
e
s 00001/00001/00960
d D 6.2 88/10/08 11:36:22 mckusick 4 3
c spelling
e
s 00955/00000/00006
d D 6.1 86/05/23 12:00:29 kjd 3 2
c document distributed with 4.3BSD
e
s 00000/00045/00006
d D 5.1 86/05/23 12:00:24 kjd 2 1
c document distributed with 4.2BSD
e
s 00051/00000/00000
d D 4.1 86/05/23 12:00:19 kjd 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 6
.\" Copyright (c) 1980 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 6
I 6
D 7
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 7
I 7
.\" Copyright (c) 1980, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 7
E 6
.\"
D 5
.\"	%W% (Berkeley) %G%
E 5
I 5
D 6
.\"	@(#)mail5.nr	6.2 (Berkeley) 10/8/88
E 6
I 6
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
E 6
E 5
.\"
I 3
D 8
.bp
E 8
.sh 1 "Additional features"
.pp
This section describes some additional commands useful for
reading your mail, setting options, and handling lists of messages.
.sh 2 "Message lists"
.pp
Several
.i Mail
commands accept a list of messages as an argument.
Along with
.b type
and
.b delete ,
described in section 2,
there is the
.b from
command, which prints the message headers associated with the
message list passed to it.
The
.b from
command is particularly useful in conjunction with some of the
message list features described below.
.pp
A
.i "message list"
consists of a list of message numbers, ranges, and names,
separated by spaces or tabs.  Message numbers may be either
decimal numbers, which directly specify messages, or one of the
special characters
.q \(ua
.q "."
or
.q "$"
to specify the first relevant, current, or last
relevant message, respectively.
.i Relevant
here means, for most commands
.q "not deleted"
and
.q "deleted"
for the
.b undelete
command.
.pp
A range of messages consists of two message numbers (of the form
described in the previous paragraph) separated by a dash.
Thus, to print the first four messages, use
.(l
type 1\-4
.)l
and to print all the messages from the current message to the last
message, use
.(l
type .\-$
.)l
.pp
A
.i name
is a user name.  The user names given in the message list are
collected together and each message selected by other means
is checked to make sure it was sent by one of the named users.
If the message consists entirely of user names, then every
D 5
message sent by one those users that is
E 5
I 5
message sent by one of those users that is
E 5
.i relevant
(in the sense described earlier)
is selected.  Thus, to print every message sent to you by
.q root,
do
.(l
type root
.)l
.pp
As a shorthand notation, you can specify simply
.q *
to get every
.i relevant
(same sense)
message.  Thus,
.(l
type *
.)l
prints all undeleted messages,
.(l
delete *
.)l
deletes all undeleted messages, and
.(l
undelete *
.)l
undeletes all deleted messages.
.pp
You can search for the presence of a word in subject lines with
.b / .
For example, to print the headers of all messages that contain the
word
.q PASCAL,
do:
.(l
from /pascal
.)l
Note that subject searching ignores upper/lower case differences.
.sh 2 "List of commands"
.pp
This section describes all the
.i Mail
commands available when
receiving mail.
D 5
.ip \fB!\fP
Used to preface a command to be executed by the shell.
.ip \fB\-\fP
E 5
I 5
.ip "\fB\-\fP\ \ "
E 5
The
.rb \-
command goes to the previous message and prints it.  The
.rb \-
command may be given a decimal number
.i n
as an argument, in which case the
.i n th
previous message is gone to and printed.
D 5
.ip \fBPrint\fP
E 5
I 5
.ip "\fB?\fP\ \ "
Prints a brief summary of commands.
.ip "\fB!\fP\ \ "
Used to preface a command to be executed by the shell.
.ip "\fBPrint\fP\ \ "
E 5
Like
.b print ,
but also print out ignored header fields.  See also
D 5
.b print
and
.b ignore .
.ip \fBReply\fP
Note the capital R in the name.
E 5
I 5
\fBprint\fP, \fBignore\fP and \fBretain\fP.
\fBPrint\fP can be abbreviated to \fBP\fP.
.ip "\fBReply\fP or \fBRespond\fP\ \ "
Note the capital \fBR\fP in the name.
E 5
Frame a reply to a one or more messages.
The reply (or replies if you are using this on multiple messages)
will be sent ONLY to the person who sent you the message
(respectively, the set of people who sent the messages you are
replying to).
You can
D 5
add people using the
.b ~t
and
.b ~c
E 5
I 5
add people using the \fB~t\fP, \fB~c\fP and \fB~b\fP
E 5
tilde escapes.  The subject in your reply is formed by prefacing the
subject in the original message with
.q "Re:"
unless it already began thus.
If the original message included a
.q "reply-to"
header field, the reply will go
.i only
to the recipient named by
.q "reply-to."
You type in your message using the same conventions available to you
through the
.b mail
command.
The
.b Reply
command is especially useful for replying to messages that were sent
to enormous distribution groups when you really just want to
send a message to the originator.  Use it often.
D 5
.ip \fBType\fP
E 5
I 5
\fBReply\fP (and \fBRespond\fP) can be abbreviated to \fBR\fP.
.ip "\fBType\fP\ \ "
E 5
Identical to the
.b Print
command.
D 5
.ip \fBalias\fP
E 5
I 5
\fBType\fP can be abbreviated to \fBT\fP.
.ip "\fBalias\fP\ \ "
E 5
Define a name to stand for a set of other names.
This is used when you want to send messages to a certain
group of people and want to avoid retyping their names.
For example
.(l
alias project john sue willie kathryn
.)l
creates an alias
.i project
which expands to the four people John, Sue, Willie, and Kathryn.
D 5
.ip \fBalternates\fP
E 5
I 5
If no arguments are given, all currently-defined aliases are printed.
If one argument is given, that alias is printed (if it exists).
\fBAlias\fP can be abbreviated to \fBa\fP.
.ip "\fBalternates\fP\ \ "
E 5
If you have accounts on several machines, you may find it convenient
to use the /usr/lib/aliases on all the machines except one to direct
your mail to a single account.
The
.b alternates
command is used to inform
.i Mail
that each of these other addresses is really
.i you .
.i Alternates
takes a list of user names and remembers that they are all actually you.
When you
.b reply
to messages that were sent to one of these alternate names,
.i Mail
will not bother to send a copy of the message to this other address (which
would simply be directed back to you by the alias mechanism).
If
.i alternates
is given no argument, it lists the current set of alternate names.
.b Alternates
is usually used in the .mailrc file.
D 5
.ip \fBchdir\fP
E 5
I 5
\fBAlternates\fP can be abbreviated to \fBalt\fP.
.ip "\fBchdir\fP\ \ "
E 5
The
.b chdir
command allows you to change your current directory.
.b Chdir
takes a single argument, which is taken to be the pathname of
the directory to change to.  If no argument is given,
.b chdir
changes to your home directory.
D 5
.ip \fBcopy\fP
E 5
I 5
\fBChdir\fP can be abbreviated to \fBc\fP.
.ip "\fBcopy\fP\ \ "
E 5
The
.b copy
command does the same thing that
.b save
does, except that it does not mark the messages it is used on
for deletion when you quit.
D 5
.ip \fBdelete\fP
E 5
I 5
\fBCopy\fP can be abbreviated to \fBco\fP.
.ip "\fBdelete\fP\ \ "
E 5
Deletes a list of messages.  Deleted messages can be reclaimed
with the
.b undelete
command.
D 5
.ip \fBdp\fP or \fBdt\fP
E 5
I 5
\fBDelete\fP can be abbreviated to \fBd\fP.
.ip "\fBdp\fP or \fBdt\fP\ \ "
E 5
These
D 5

E 5
commands delete the current message and print the next message.
They are useful for quickly reading and disposing of mail.
D 5
.ip \fBedit\fP
E 5
I 5
If there is no next message, \fImail\fP says ``at EOF.''
.ip "\fBedit\fP\ \ "
E 5
To edit individual messages using the text editor, the
.b edit
command is provided.  The
.b edit
command takes a list of messages as described under the
.b type
command and processes each by writing it into the file
Message\c
.i x
where
.i x
is the message number being edited and executing the text editor on it.
When you have edited the message to your satisfaction, write the message
out and quit, upon which
.i Mail
will read the message back and remove the file.
.b Edit
D 5
may be abbreviated to
E 5
I 5
can be abbreviated to
E 5
.b e .
D 5
.ip \fBelse\fP
E 5
I 5
.ip "\fBelse\fP\ \ "
E 5
Marks the end of the then-part of an
.b if
statement and the beginning of the
part to take effect if the condition of the
.b if
statement is false.
D 5
.ip \fBendif\fP
E 5
I 5
.ip "\fBendif\fP\ \ "
E 5
Marks the end of an
.b if
statement.
D 5
.ip \fBexit\fP
E 5
I 5
.ip "\fBexit\fP or \fBxit\fP\ \ "
E 5
Leave
.i Mail
without updating the system mailbox or the file your were reading.
Thus, if you accidentally delete several messages, you can use
.b exit
to avoid scrambling your mailbox.
D 5
.ip \fBfile\fP
E 5
I 5
\fBExit\fP can be abbreviated to \fBex\fP or \fBx\fP.
.ip "\fBfile\fP\ \ "
E 5
The same as
.b folder .
D 5
.ip \fBfolders\fP
E 5
I 5
\fBFile\fP can be abbreviated to \fBfi\fP.
.ip "\fBfolders\fP\ \ "
E 5
List the names of the folders in your folder directory.
D 5
.ip \fBfolder\fP
E 5
I 5
.ip "\fBfolder\fP\ \ "
E 5
The
.b folder
command switches to a new mail file or folder.  With no arguments, it
tells you which file you are currently reading.  If you give
it an argument, it will write out changes (such as deletions)
you have made in the current file and read the new file.
Some special conventions are recognized for the name:
.(b
.TS
center;
c c
l a.
Name	Meaning
_
#	Previous file read
%	Your system mailbox
%name	\fIName\fP's system mailbox
&	Your ~/mbox file
+folder	A file in your folder directory
.TE
.)b
D 5
.ip \fBfrom\fP
E 5
I 5
\fBFolder\fP can be abbreviated to \fBfo\fP.
.ip "\fBfrom\fP\ \ "
E 5
The
.b from
command takes a list of messages and prints out the header lines for each one;
hence
.(l
from joe
.)l
is the easy way to display all the message headers from \*(lqjoe.\*(rq
D 5
.ip \fBheaders\fP
E 5
I 5
\fBFrom\fP can be abbreviated to \fBf\fP.
.ip "\fBheaders\fP\ \ "
E 5
When you start up
.i Mail
to read your mail, it lists the message headers that you have.
These headers tell you who each message is from, when they were
D 5
sent, how many lines and characters each message is, and the
E 5
I 5
received, how many lines and characters each message is, and the
E 5
.q "Subject:"
header field of each message, if present.  In addition,
.i Mail
tags the message header of each message that has been the object
of the
.b preserve
command with a
.q P.
Messages that have been
.b saved
or
.b written
are flagged with a
.q *.
Finally,
.b deleted
messages are not printed at all.  If you wish to reprint the current
list of message headers, you can do so with the
.b headers
command.  The
.b headers
command (and thus the initial header listing)
only lists the first so many message headers.
The number of headers listed depends on the speed of your
terminal.
This can be overridden by specifying the number of headers you
want with the
.i window
option.
.i Mail
maintains a notion of the current
.q window
into your messages for the purposes of printing headers.
Use the
.b z
command to move forward and back a window.
You can move
.i Mail's
notion of the current window directly to a particular message by
using, for example,
.(l
headers 40
.)l
to move
.i Mail's
D 5
attention to the messages around message 40.  The
.b headers
command can be abbreviated to
.b h .
.ip \fBhelp\fP
E 5
I 5
attention to the messages around message 40.
If a ``+'' argument is given, then the next screenful of message headers is
printed, and if a ``\-'' argument is given, the previous screenful of message
headers is printed.
\fBHeaders\fP can be abbreviated to \fBh\fP.
.ip "\fBhelp\fP\ \ "
E 5
Print a brief and usually out of date help message about the commands
in
.i Mail .
The 
.i man
page for 
.i mail
is usually more up-to-date than either the help message or this manual.
D 5
.ip \fBhold\fP
E 5
I 5
It is also a synonym for \fB?\fP.
.ip "\fBhold\fP\ \ "
E 5
Arrange to hold a list of messages in the system mailbox, instead
of moving them to the file
.i mbox
in your home directory.  If you set the binary option
.i hold ,
this will happen by default.
D 5
.ip \fBif\fP
E 5
I 5
It does not override the \fBdelete\fP command.
\fBHold\fP can be abbreviated to \fBho\fP.
.ip "\fBif\fP\ \ "
E 5
Commands in your
.q .mailrc
file can be executed conditionally depending on whether you are
sending or receiving mail with the
.b if
command.  For example, you can do:
.(l
if receive
	\fIcommands\fP...
endif
.)l
An
.b else
form is also available:
.(l
if send
	\fIcommands\fP...
else
	\fIcommands\fP...
endif
.)l
Note that the only allowed conditions are
.b receive
and
.b send .
D 5
.ip \fBignore\fP
E 5
I 5
.ip "\fBignore\fP \ \ "
.b N.B.:
.i Ignore
has been superseded by
.i retain.
.br
E 5
Add the list of header fields named to the
.i "ignore list" .
Header fields in the ignore list are not printed on your
terminal when you print a message.  This allows you to suppress
printing of certain machine-generated header fields, such as
.i Via
which are not usually of interest.  The
.b Type
and
.b Print
commands can be used to print a message in its entirety, including
ignored fields.
If
.b ignore
is executed with no arguments, it lists the current set of ignored fields.
D 5
.ip \fBlist\fP
E 5
I 5
.ip "\fBlist\fP\ \ "
E 5
D 4
List the vaild
E 4
I 4
List the valid
E 4
.i Mail
commands.
I 5
\fBList\fP can be abbreviated to \fBl\fP.
E 5
.. .ip \fBlocal\fP
.. Define a list of local names for this host. This command is useful
.. when the host is known by more than one name. Names in the list
.. may be qualified be the domain of the host. The first name on the local
.. list is the
.. .i distinguished
.. name of the host.
.. The names on the local list are used by
.. .i Mail
.. to decide which addresses are local to the host.
.. For example:
.. .(l
.. local ucbarpa.BERKELEY.ARPA arpa.BERKELEY.ARPA \\
.. 	arpavax.BERKELEY.ARPA r.BERKELEY.ARPA \\
.. 	ucb-arpa.ARPA
.. .)l
.. From this list we see that
.. .i "fred@ucbarpa.BERKELEY.ARPA",
.. .i "harold@arpa.BERKELEY",
.. and
.. .i "larry@r"
.. are all addresses of users on the local host.
.. The
.. .b local
.. command is usually not used be general users since it is designed for
.. local configuration; it is usually found in the file /usr/lib/Mail.rc.
D 5
.ip \fBmail\fP
E 5
I 5
.ip "\fBmail\fP\ \ "
E 5
Send mail to one or more people.  If you have the
.i ask
option set,
.i Mail
will prompt you for a subject to your message.  Then you
can type in your message, using tilde escapes as described in
section 4 to edit, print, or modify your message.  To signal your
satisfaction with the message and send it, type control-d at the
beginning of a line, or a . alone on a line if you set the option
.i dot .
To abort the message, type two interrupt characters (\s-2RUBOUT\s0
by default) in a row or use the
.b ~q
escape.
D 5
.ip \fBmbox\fP
E 5
I 5
The \fBmail\fP command can be abbreviated to \fBm\fP.
.ip "\fBmbox\fP\ \ "
E 5
Indicate that a list of messages be sent to
.i mbox
in your home directory when you quit.  This is the default
action for messages if you do
.i not
have the
.i hold
option set.
D 5
.ip \fBnext\fP
E 5
I 5
.ip "\fBnext\fP or \fB+\fP\ \ "
E 5
The
.b next
command goes to the next message and types it.  If given a message list,
.b next
goes to the first such message and types it.  Thus,
.(l
next root
.)l
goes to the next message sent by
.q root
and types it.  The
.b next
command can be abbreviated to simply a newline, which means that one
can go to and type a message by simply giving its message number or
one of the magic characters
.q "^"
.q "."
or
.q "$".
Thus,
.(l
\&.
.)l
prints the current message and
.(l
4
.)l
prints message 4, as described previously.
D 5
.ip \fBpreserve\fP
E 5
I 5
\fBNext\fP can be abbreviated to \fBn\fP.
.ip "\fBpreserve\fP\ \ "
E 5
Same as
.b hold .
Cause a list of messages to be held in your system mailbox when you quit.
D 5
.ip \fBprint\fP
Takes a message list and types out each message on the terminal.
.ip \fBquit\fP
Leave
.i Mail
and update the file, folder, or system mailbox your were reading.
Messages that you have examined are marked as
.q read
and messages that existed when you started are marked as
.q old.
If you were editing your system mailbox and
if you have set the binary option
.i hold ,
all messages which have not been deleted, saved, or mboxed
will be retained in your system mailbox.
If you were editing your system mailbox and
you did
.i not
have
.i hold
set, all messages which have not been deleted, saved, or preserved
will be moved to the file
.i mbox
in your home directory.
.ip \fBreply\fP or \fBrespond\fP
E 5
I 5
\fBPreserve\fP can be abbreviated to \fBpre\fP.
.ip "\fBprint\fP\ \ "
Print the specified messages. If the
.b crt
variable is set, messages longer than the number of lines it indicates
are paged through the command specified by the \fBPAGER\fP variable.
The \fBprint\fP command can be abbreviated to \fBp\fP.
.ip "\fBquit\fP\ \ "
Terminates the session, saving all undeleted, unsaved and unwritten messages 
in the user's \fImbox\fP file in their login directory
(messages marked as having been read), preserving all
messages marked with \fBhold\fP or \fBpreserve\fP or never referenced
in their system mailbox.
Any messages that were deleted, saved, written or saved to \fImbox\fP are
removed from their system mailbox.
If new mail has arrived during the session, the message
``You have new mail'' is given.  If given while editing a mailbox file
with the \fB\-f\fP flag, then the edit file is rewritten.
A return to the Shell is effected, unless the rewrite of edit file fails,
in which case the user can escape with the \fBexit\fP command.
\fBQuit\fP can be abbreviated to \fBq\fP.
.ip "\fBreply\fP or \fBrespond\fP\ \ "
E 5
Frame a reply to a single message.
The reply will be sent to the
D 5
person who sent you the message to which you are replying, plus all
E 5
I 5
person who sent you the message (to which you are replying), plus all
E 5
the people who received the original message, except you.  You can
D 5
add people using the
.b ~t
and
.b ~c
E 5
I 5
add people using the \fB~t\fP, \fB~c\fP and \fB~b\fP
E 5
tilde escapes.  The subject in your reply is formed by prefacing the
subject in the original message with
.q "Re:"
unless it already began thus.
If the original message included a
.q "reply-to"
header field, the reply will go
.i only
to the recipient named by
.q "reply-to."
You type in your message using the same conventions available to you
through the
.b mail
command.
D 5
.ip \fBsave\fP
E 5
I 5
The \fBreply\fP (and \fBrespond\fP) command can be abbreviated to \fBr\fP.
.ip "\fBretain\fP\ \ "
Add the list of header fields named to the \fIretained list\fP.
Only the header fields in the retain list
are shown on your terminal when you print a message.
All other header fields are suppressed.
The
.b Type
and
.b Print
commands can be used to print a message in its entirety.
If
.b retain
is executed with no arguments, it lists the current set of
retained fields.
.ip "\fBsave\fP\ \ "
E 5
It is often useful to be able to save messages on related topics
in a file.  The
.b save
D 5
command gives you ability to do this.  The
E 5
I 5
command gives you the ability to do this.  The
E 5
.b save
D 5
command takes as argument a list of message numbers, followed by
the name of the file on which to save the messages.  The messages
E 5
I 5
command takes as an argument a list of message numbers, followed by
the name of the file in which to save the messages.  The messages
E 5
are appended to the named file, thus allowing one to keep several
messages in the file, stored in the order they were put there.
D 5
The
.b save
command can be abbreviated to
.b s .
E 5
I 5
The filename in quotes, followed by the line
count and character count is echoed on the user's terminal.
E 5
An example of the
.b save
command relative to our running example is:
.(l
s 1 2 tuitionmail
.)l
.b Saved
messages are not automatically saved in
.i mbox
at quit time, nor are they selected by the
.b next
command described above, unless explicitly specified.
D 5
.ip \fBset\fP
E 5
I 5
\fBSave\fP can be abbreviated to \fBs\fP.
.ip "\fBset\fP\ \ "
E 5
Set an option or give an option a value.  Used to customize
.i Mail .
Section 5.3 contains a list of the options.  Options can be
.i binary ,
in which case they are
.i on
or
.i off ,
or
.i valued .
To set a binary option
.i option
.i on ,
do
.(l
set option
.)l
To give the valued option
.i option
the value
.i value ,
do
.(l
set option=value
.)l
I 5
There must be no space before or after the ``='' sign.
If no arguments are given, all variable values are printed.
E 5
Several options can be specified in a single
.b set
command.
D 5
.ip \fBshell\fP
E 5
I 5
\fBSet\fP can be abbreviated to \fBse\fP.
.ip "\fBshell\fP\ \ "
E 5
The
.b shell
command allows you to
escape to the shell.
.b Shell
invokes an interactive shell and allows you to type commands to it.
When you leave the shell, you will return to
.i Mail .
The shell used is a default assumed by
.i Mail ;
you can override this default by setting the valued option
.q SHELL,
eg:
.(l
set SHELL=/bin/csh
.)l
D 5
.ip \fBsource\fP
E 5
I 5
\fBShell\fP can be abbreviated to \fBsh\fP.
.ip "\fBsize\fP\ \ "
Takes a message list and prints out the size in characters of each
message.
.ip "\fBsource\fP\ \ "
E 5
The
.b source
command reads
D 5
.i Mail
E 5
I 5
.i mail
E 5
commands from a file.  It is useful when you are trying to fix your
.q .mailrc
file and you need to re-read it.
D 5
.ip \fBtop\fP
E 5
I 5
\fBSource\fP can be abbreviated to \fBso\fP.
.ip "\fBtop\fP\ \ "
E 5
The
.b top
command takes a message list and prints the first five lines
D 5
of each addressed message.  It may be abbreviated to
.b to .
E 5
I 5
of each addressed message.
E 5
If you wish, you can change the number of lines that
.b top
prints out by setting the valued option
.q "toplines."
On a CRT terminal,
.(l
set toplines=10
.)l
might be preferred.
D 5
.ip \fBtype\fP
Print a list of messages on your terminal.  If you have set the
option
.i crt
to a number and the total number of lines in the messages you are
printing exceed that specified by
.i crt ,
the messages will be printed by a terminal paging program such as
.i more .
.ip \fBundelete\fP
The
.b undelete
command causes a message that had been deleted previously to regain
its initial status.  Only messages that have been deleted may be
undeleted.  This command may be abbreviated to
.b u .
.ip \fBunset\fP
Reverse the action of setting a binary or valued option.
.ip \fBvisual\fP
E 5
I 5
\fBTop\fP can be abbreviated to \fBto\fP.
.ip "\fBtype\fP\ \ "
Same as \fBprint\fP.
Takes a message list and types out each message on the terminal.
The \fBtype\fP command can be abbreviated to \fBt\fP.
.ip "\fBundelete\fP \ \"
Takes a message list and marks each message as \fInot\fP
being deleted.
\fBUndelete\fP can be abbreviated to \fBu\fP.
.ip "\fBunread\fP\ \ "
Takes a message list and marks each message as
.i not
having been read.
\fBUnread\fP can be abbreviated to \fBU\fP.
.ip "\fBunset\fP\ \ "
Takes a list of option names and discards their remembered values;
the inverse of \fBset\fP .
.ip "\fBvisual\fP\ \ "
E 5
It is often useful to be able to invoke one of two editors,
based on the type of terminal one is using.  To invoke
a display oriented editor, you can use the
.b visual
command.  The operation of the
.b visual
command is otherwise identical to that of the
.b edit
command.
.ne 2v+\n(psu
.sp \n(psu
Both the
.b edit
and
.b visual
commands assume some default text editors.  These default editors
can be overridden by the valued options
.q EDITOR
and
.q VISUAL
for the standard and screen editors.  You might want to do:
.(l
set EDITOR=/usr/ucb/ex VISUAL=/usr/ucb/vi
.)l
D 5
.ip \fBwrite\fP
E 5
I 5
\fBVisual\fP can be abbreviated to \fBv\fP.
.ip "\fBwrite\fP\ \ "
E 5
The
.b save
command always writes the entire message, including the headers,
into the file.  If you want to write just the message itself, you
can use the
.b write
command.  The
.b write
command has the same syntax as the
.b save
command, and can be abbreviated to simply
.b w .
Thus, we could write the second message by doing:
.(l
w 2 file.c
.)l
As suggested by this example, the
.b write
command is useful for such tasks as sending and receiving
source program text over the message system.
D 5
.ip \fBz\fP
E 5
I 5
The filename in quotes, followed by the line
count and character count is echoed on the user's terminal.
.ip "\fBz\fP\ \ "
E 5
.i Mail
presents message headers in windowfuls as described under
the
.b headers
command.
You can move
.i Mail's
attention forward to the next window by giving the
.(l
z+
.)l
command.  Analogously, you can move to the previous window with:
.(l
z\-
.)l
.sh 2 "Custom options"
.pp
Throughout this manual, we have seen examples of binary and valued options.
This section describes each of the options in alphabetical order, including
some that you have not seen yet.
To avoid confusion, please note that the options are either
all lower case letters or all upper case letters.  When I start a sentence
such as:
.q "Ask"
causes
.i Mail
to prompt you for a subject header,
I am only capitalizing
.q ask
as a courtesy to English.
D 5
.ip \fBEDITOR\fP
E 5
I 5
.ip "\fBEDITOR\fP\ \ "
E 5
The valued option
.q EDITOR
defines the pathname of the text editor to be used in the
.b edit
command and ~e.  If not defined, a standard editor is used.
D 5
.ip \fBSHELL\fP
E 5
I 5
.ip "\fBPAGER\fP\ \ "
Pathname of the program to use for paginating output when
it exceeds \fIcrt\fP lines.
A default paginator is used if this option is not defined.
.ip "\fBSHELL\fP\ \ "
E 5
The valued option
.q SHELL
gives the path name of your shell.  This shell is used for the
.b !
command and ~! escape.  In addition, this shell expands
file names with shell metacharacters like * and ? in them.
D 5
.ip \fBVISUAL\fP
E 5
I 5
.ip "\fBVISUAL\fP\ \ "
E 5
The valued option
.q VISUAL
D 5
defines the pathname of your screen editor for use in the
E 5
I 5
defines the pathname of the screen editor to be used in the
E 5
.b visual
command
and ~v escape.  A standard screen editor is used if you do not define one.
D 5
.ip \fBappend\fP
E 5
I 5
.ip "\fBappend\fP\ \ "
E 5
The
.q append
option is binary and
causes messages saved in
.i mbox
to be appended to the end rather than prepended.
D 5
Normally,
.i Mail will put messages in
.i mbox
E 5
I 5
Normally, \fIMail\fP will put messages in \fImbox\fP
E 5
in the same order that the system puts messages in your system mailbox.
By setting
.q append,
you are requesting that
.i mbox
be appended to regardless.  It is in any event quicker to append.
D 5
.ip \fBask\fP
E 5
I 5
.ip "\fBask\fP\ \ "
E 5
.q "Ask"
is a binary option which
causes
.i Mail
to prompt you for the subject of each message you send.
If you respond with simply a newline, no subject field will be sent.
D 5
.ip \fBaskcc\fP
E 5
I 5
.ip "\fBaskcc\fP\ \ "
E 5
.q Askcc
is a binary option which
causes you to be prompted for additional carbon copy recipients at the
end of each message.  Responding with a newline shows your
satisfaction with the current list.
D 5
.ip \fBautoprint\fP
E 5
I 5
.ip "\fBautoprint\fP\ \ "
E 5
.q Autoprint
is a binary option which
causes the
.b delete
command to behave like
.b dp
\*- thus, after deleting a message, the next one will be typed
D 5
automatically.  This is useful to quickly scanning and deleting
E 5
I 5
automatically.  This is useful when quickly scanning and deleting
E 5
messages in your mailbox.
D 5
.ip \fBdebug\fP
E 5
I 5
.ip "\fBcrt\fP \ \ "
The valued option
.I crt
is used as a threshold to determine how long a message must
be before
.b PAGER
is used to read it.
.ip "\fBdebug\fP \ \ "
E 5
The binary option
.q debug
causes debugging information to be displayed. Use of this
D 5
option is the same as useing the
.ip \-d
command line flag.
.ip \fBdot\fP
E 5
I 5
option is the same as using the \fB\-d\fP command line flag.
.ip "\fBdot\fP\ \ "
E 5
.q Dot
is a binary option which, if set, causes
.i Mail
to interpret a period alone on a line as the terminator
D 5
of a message you are sending.
.ip \fBescape\fP
E 5
I 5
of the message you are sending.
.ip "\fBescape\fP\ \ "
E 5
To allow you to change the escape character used when sending
mail, you can set the valued option
.q escape.
Only the first character of the
.q escape
option is used, and it must be doubled if it is to appear as
the first character of a line of your message.  If you change your escape
character, then ~ loses all its special meaning, and need no longer be doubled
at the beginning of a line.
D 5
.ip \fBfolder\fP
E 5
I 5
.ip "\fBfolder\fP\ \ "
E 5
The name of the directory to use for storing folders of messages.
If this name begins with a `/'
.i Mail
considers it to be an absolute pathname; otherwise, the folder directory
is found relative to your home directory.
D 5
.ip \fBhold\fP
E 5
I 5
.ip "\fBhold\fP\ \ "
E 5
The binary option
.q hold
causes messages that have been read but not manually dealt with
to be held in the system mailbox. This prevents such messages from
D 5
being automatically swept into your mbox.
.ip \fBignore\fP
E 5
I 5
being automatically swept into your \fImbox\fP file.
.ip "\fBignore\fP\ \ "
E 5
The binary option
.q ignore
causes \s-2RUBOUT\s0 characters from your terminal to be ignored and echoed
as @'s while you are sending mail.  \s-2RUBOUT\s0 characters retain their
original meaning in
.i Mail
command mode.
Setting the
.q ignore
option is equivalent to supplying the
.b \-i
flag on the command line as described in section 6.
D 5
.ip \fBignoreeof\fP
E 5
I 5
.ip "\fBignoreeof\fP\ \ "
E 5
An option related to
.q dot
is
.q ignoreeof
which makes
.i Mail
refuse to accept a control\-d as the end of a message.
.q Ignoreeof
also applies to
.i Mail
command mode.
D 5
.ip \fBkeep\fP
E 5
I 5
.ip "\fBkeep\fP\ \ "
E 5
The
.q keep
option causes
.i Mail
to truncate your system mailbox instead of deleting it when it
is empty.  This is useful if you elect to protect your mailbox, which
you would do with the shell command:
.(l
chmod 600 /usr/spool/mail/yourname
.)l
where
.i yourname
is your login name.  If you do not do this, anyone can probably read
your mail, although people usually don't.
D 5
.ip \fBkeepsave\fP
E 5
I 5
.ip "\fBkeepsave\fP\ \ "
E 5
When you
.b save
a message,
.i Mail
usually discards it when you
.b quit .
To retain all saved messages, set the
.q keepsave
option.
D 5
.ip \fBmetoo\fP
E 5
I 5
.ip "\fBmetoo\fP\ \ "
E 5
When sending mail to an alias,
.i Mail
makes sure that if you are included in the alias, that mail will not
be sent to you.  This is useful if a single alias is being used by
all members of the group.  If however, you wish to receive a copy of
all the messages you send to the alias, you can set the binary option
.q metoo.
D 5
.ip \fBnoheader\fP
E 5
I 5
.ip "\fBnoheader\fP\ \ "
E 5
The binary option
.q noheader
suppresses the printing of the version and headers when
.i Mail
is first invoked. Setting this option is the same as using
.b \-N
on the command line.
D 5
.ip \fBnosave\fP
E 5
I 5
.ip "\fBnosave\fP\ \ "
E 5
Normally,
when you abort a message with two \s-2RUBOUTs\s0,
.i Mail
copies the partial letter to the file
.q dead.letter
in your home directory.  Setting the binary option
.q nosave
prevents this.
D 5
.ip \fBquiet\fP
E 5
I 5
.ip "\fBReplyall\fP\ \ "
Reverses the sense of
.i reply
and
.i Reply
commands.
.ip "\fBquiet\fP\ \ "
E 5
The binary option
.q quiet
suppresses the printing of the version when
.i Mail
is first invoked,
as well as printing the for example
.q "Message 4:"
from the
.b type
command.
D 5
.ip \fBrecord\fP
E 5
I 5
.ip "\fBrecord\fP\ \ "
E 5
If you love to keep records, then the
valued option
.q record
can be set to the name of a file to save your outgoing mail.
Each new message you send is appended to the end of the file.
D 5
.ip \fBscreen\fP
E 5
I 5
.ip "\fBscreen\fP\ \ "
E 5
When
.i Mail
initially prints the message headers, it determines the number to
print by looking at the speed of your terminal.  The faster your
terminal, the more it prints.
The valued option
.q screen
overrides this calculation and
specifies how many message headers you want printed.
This number is also used for scrolling with the
.b z
command.
D 5
.ip \fBsendmail\fP
To alternate delivery system, set the
E 5
I 5
.ip "\fBsendmail\fP\ \ "
To use an alternate mail delivery system, set the
E 5
.q sendmail
option to the full pathname of the program to use.  Note:  this is not
for everyone!  Most people should use the default delivery system.
D 5
.ip \fBtoplines\fP
E 5
I 5
.ip "\fBtoplines\fP\ \ "
E 5
The valued option
.q toplines
defines the number of lines that the
.q top
command will print out instead of the default five lines.
D 5
.ip \fBverbose\fP
E 5
I 5
.ip "\fBverbose\fP\ \ "
E 5
The binary option "verbose" causes
.i Mail
to invoke sendmail with the 
.b \-v
D 5
flag, which causes it to go into versbose mode and announce expansion
E 5
I 5
flag, which causes it to go into verbose mode and announce expansion
E 5
of aliases, etc. Setting the "verbose" option is equivalent to
invoking
.i Mail
with the
.b \-v
flag as described in section 6.
E 3
D 2
.sh 1 "Command line options"
.pp
This section describes the alternate usages of Mail from the
shell.
.pp
As you continue to receive system mail, you will most likely
accumulate a large collection of messages in the file
.i mbox.
In order to help you deal with this, Mail allows you to edit
files of messages by using the
.rb -f
flag.  Specifically,
.(l
Mail \-f filename
.)l
causes Mail to edit \*(lqfilename\*(rq and
.(l
Mail \-f
.)l
causes Mail to read \*(lqmbox\*(rq in your home directory.  All of
the Mail commands except
.b preserve
are available to edit the messages.  When you type the
.b quit
command, Mail will write the updated file back.
.pp
Since you will usually have a large number of messages stored in
.i mbox,
Mail will only print out the first 18 message headers when editing
more than 18 messages.  To display the other message headers, the
.b headers
command takes as an optional argument either + or \- to move forward
or back to the next or previous 18 message group.
.pp
If you send mail over a noisy phone line, you will notice that many
of the garbage characters turn out to be the \s-2RUBOUT\s0 character,
which causes Mail to abort the message.  To deal with this annoyance,
you can invoke Mail with the
.rb -i
option to causes these garbage characters to be ignored.  Unfortunately,
as you are typing in a line of text to a program, the little gnome which
gathers up the characters is instructed to throw them all away when
a \s-2RUBOUT\s0 is seen.  For this reason, Mail indicates that a
\s-2RUBOUT\s0 has been received by echoing an @ to tell you that everything
you had typed on that line has been thrown away.
E 2
E 1
