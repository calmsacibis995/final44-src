h61854
s 00000/00001/00048
d D 8.2 94/05/16 17:29:11 mckusick 6 5
c formatting update for 4.4BSD
e
s 00002/00002/00047
d D 8.1 93/06/08 12:42:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00045
d D 6.2 91/04/17 12:21:17 bostic 4 3
c new copyright; att/bsd/shared
e
s 00042/00000/00006
d D 6.1 86/05/23 12:01:43 kjd 3 2
c document distributed with 4.3BSD
e
s 00000/00006/00006
d D 5.1 86/05/23 12:01:38 kjd 2 1
c document distributed with 4.2BSD
e
s 00012/00000/00000
d D 4.1 86/05/23 12:01:33 kjd 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1980 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 5
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
.\" Copyright (c) 1980, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
I 3
D 6
.bp
E 6
.sh 1 "Glossary"
.pp
This section contains the definitions of a few phrases
peculiar to
.i Mail .
.ip "\fIalias\fP"
An alternative name for a person or list of people.
.ip "\fIflag\fP"
An option, given on the command line of
.i Mail ,
prefaced with a \-.  For example,
.b \-f
is a flag.
.ip "\fIheader field\fP"
At the beginning of a message, a line which contains information
that is part of the structure of the message.  Popular header fields
include
.i to ,
.i cc ,
and
.i subject .
.ip "\fImail\ \ \fP"
A collection of messages.  Often used in the phrase,
.q "Have you read your mail?"
.ip "\fImailbox\fP"
The place where your mail is stored, typically in the directory
/usr/spool/mail.
.ip "\fImessage\fP"
A single letter from someone, initially stored in your
.i mailbox .
.ip "\fImessage list\fP"
A string used in
.i Mail
command mode to describe a sequence of messages.
.ip "\fIoption\fP"
A piece of special purpose information used to tailor
.i Mail
to your taste.
Options are specified with the
.b set
command.
E 3
D 2
.sh 1 Conclusion
.pp
I would like to acknowledge the suggestions and criticisms of Eric
Allman, Ken Arnold, Bob Fabry, Richard Fateman, Bob Kridle,
Doug Merritt, David Mosher, Eric Schmidt, Polly Siegel, Michael Ubell,
and especially Bill Joy, who sneezed nearby; I caught the bug.
E 2
E 1
