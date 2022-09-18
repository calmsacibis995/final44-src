h50064
s 00003/00001/00145
d D 8.5 94/06/01 18:18:23 ah 9 8
c page breaks for the 4.4BSD manuals
e
s 00012/00010/00134
d D 8.4 94/05/26 22:30:59 bostic 8 7
c cleanups and edits for accuracy
e
s 00020/00001/00124
d D 8.3 94/05/20 06:07:04 karels 7 6
c touchups and improvements
e
s 00085/00108/00040
d D 8.2 94/05/16 10:09:43 mckusick 6 5
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00146
d D 8.1 93/06/08 18:06:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00144
d D 6.3 91/04/17 10:02:03 bostic 4 3
c new copyright; att/bsd/shared
e
s 00016/00006/00131
d D 6.2 86/05/12 01:01:43 karels 3 2
c update, correct, rephrase and re-propose
e
s 00000/00001/00137
d D 6.1 86/05/08 12:27:07 mckusick 2 1
c format updates for 4.3BSD
e
s 00138/00000/00000
d D 5.1 86/05/08 00:03:51 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 5
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
D 8
.\" Copyright (c) 1983, 1993
E 8
I 8
.\" Copyright (c) 1983, 1993, 1994
E 8
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
D 6
.sh "Terminals and Devices
.NH 3
Terminals
E 6
I 6
.Sh 2 "Terminals and Devices
.Sh 3 "Terminals
E 6
.PP
D 3
Terminals support \fIread\fP and \fIwrite\fP i/o operations,
E 3
I 3
D 6
Terminals support \fIread\fP and \fIwrite\fP I/O operations,
E 3
as well as a collection of terminal specific \fIioctl\fP operations,
E 6
I 6
Terminals support
.Fn read
and
.Fn write
I/O operations,
as well as a collection of terminal specific
.Fn ioctl
operations,
E 6
D 3
to control input character editing, and output delays.
E 3
I 3
to control input character interpretation and editing,
and output format and delays.
I 7
.PP
A terminal may be used as a controlling terminal (login terminal)
for a login session.
A controlling terminal is associated with a session (see section
.Xr 1.1.4 ).
A controlling terminal has a foreground process group, which must be
D 8
a member of the session with which the terminal is associated.
E 8
I 8
a member of the session with which the terminal is associated (see section
.Xr 1.1.5 ).
E 8
Members of the foreground process group are allowed to read from and write to
the terminal and change the terminal settings; other process groups from
the session may be stopped upon attempts to do these operations.
.PP
A session leader allocates a terminal
as the controlling terminal for its session using the ioctl
.DS
ioctl(fd, TIOCSCTTY, NULL);
int fd;
.DE
D 9
.Fn
E 9
Only a session leader may acquire a controlling terminal.
I 9
.ne 1i
E 9
E 7
E 3
D 6
.NH 4
Terminal input
E 6
I 6
.Sh 4 "Terminal input
E 6
.PP
Terminals are handled according to the underlying communication
characteristics such as baud rate and required delays,
and a set of software parameters.
D 6
.NH 5
Input modes
E 6
I 6
These parameters are described in the \fItermios\fP structure
maintained by the kernel for each terminal line:
.DS
.TS
l s s s
l l l l.
struct termios {
	tcflag_t	c_iflag;	/* input flags */
	tcflag_t	c_oflag;	/* output flags */
	tcflag_t	c_cflag;	/* control flags */
	tcflag_t	c_lflag;	/* local flags */
	cc_t	c_cc[NCCS];	/* control chars */
	long	c_ispeed;	/* input speed */
	long	c_ospeed;	/* output speed */
};
.TE
.DE
The \fItermios\fP structure is set and retrieved using the
.Fn tcsetattr
and
.Fn tcgetattr
functions.
E 6
.PP
D 6
A terminal is in one of three possible modes: \fIraw\fP, \fIcbreak\fP,
or \fIcooked\fP.
In raw mode all input is passed through to the
E 6
I 6
Two general kinds of input processing are available, determined by
whether the terminal device file is in canonical mode or noncanonical
mode. Additionally, input characters are processed according to the
\fIc_iflag\fP and \fIc_lflag\fP fields.
Such processing can include echoing, which
in general means transmitting input characters immediately back to the
terminal when they are received from the terminal.
Non-graphic ASCII input characters may be echoed as a two-character
printable representation, ``^character.''
.PP
In canonical mode input processing,
terminal input is processed in units of lines.
A line is delimited by a newline character (NL),
an end-of-file (EOF) character, or an end-of-line (EOL) character.
Input is presented on a line-by-line basis.
Using this mode means that a read request will not return
until an entire line has been typed,
or a signal has been received.
Also, no matter how many bytes are requested
in the read call, at most one line is returned.
It is not, however, necessary to read a whole line at once;
any number of bytes, even one, may
be requested in a read without losing information.
.PP
When the terminal is in canonical mode, editing of an input line
is performed.  Editing facilities allow deletion of the previous
character or word, or deletion of the current input line. 
D 8
In addition, a special character may be used to reprint the current
input line after some number of editing operations have been applied.
E 8
I 8
In addition,
a special character may be used to reprint the current input line.
E 8
Certain other characters are also interpreted specially.
D 8
Flow control is provided by \fIstop output\fP
E 8
I 8
Flow control is provided by the \fIstop output\fP
E 8
and \fIstart output\fP control characters.
Output may be flushed with the \fIflush output\fP character;
D 8
and a \fIliteral character\fP may be used to force literal input
of the immediately following character in the input line.
E 8
I 8
and the \fIliteral character\fP may be used to force the following
character into the input line, regardless of any special meaning
it may have.
E 8
.PP
In noncanonical mode input processing, input bytes are not assembled into
lines, and erase and kill processing does not occur.
All input is passed through to the
E 6
reading process immediately and without interpretation.
D 6
In cbreak mode, the handler interprets input only by looking
E 6
I 6
D 8
Signals may be enabled; here
E 8
I 8
Signals and flow control may be enabled; here
E 8
the handler interprets input only by looking
E 6
for characters that cause interrupts or output flow control;
D 6
all other characters are made available as in raw mode.
In cooked mode, input
is processed to provide standard line-oriented local editing functions,
and input is presented on a line-by-line basis.
.NH 5
Interrupt characters
E 6
I 6
all other characters are made available.
E 6
.PP
D 6
Interrupt characters are interpreted by the terminal handler only in
cbreak and cooked modes, and
E 6
I 6
When interrupt characters are being interpreted
by the terminal handler they
E 6
cause a software interrupt to be sent to all processes in the process
D 6
group associated with the terminal.  Interrupt characters exist
to send SIGINT
E 6
I 6
group associated with the terminal.
Interrupt characters exist to send SIGINT
E 6
and SIGQUIT signals,
and to stop a process group
with the SIGTSTP signal either immediately, or when
all input up to the stop character has been read.
D 6
.NH 5
Line editing
E 6
I 6
.Sh 4 "Terminal output
E 6
.PP
D 6
When the terminal is in cooked mode, editing of an input line
is performed.  Editing facilities allow deletion of the previous
character or word, or deletion of the current input line. 
In addition, a special character may be used to reprint the current
input line after some number of editing operations have been applied.
.PP
Certain other characters are interpreted specially when a process is
in cooked mode.  The \fIend of line\fP character determines
the end of an input record.  The \fIend of file\fP character simulates
an end of file occurrence on terminal input.  Flow control is provided
by \fIstop output\fP and \fIstart output\fP control characters.  Output
may be flushed with the \fIflush output\fP character; and a \fIliteral
character\fP may be used to force literal input of the immediately
following character in the input line.
I 3
.PP
Input characters may be echoed to the terminal as they are received.
Non-graphic ASCII input characters may be echoed as a two-character
printable representation, ``^character.''
E 3
.NH 4
Terminal output
.PP
E 6
On output, the terminal handler provides some simple formatting services.
These include converting the carriage return character to the
D 3
two character return-linefeed sequence, displaying non-graphic
ASCII characters as ``^character'', inserting delays after certain
standard control characters, expanding tabs, and providing translations
E 3
I 3
two character return-linefeed sequence,
inserting delays after certain standard control characters,
D 6
expanding tabs, and providing translations
E 3
for upper-case only terminals.
.NH 4
Terminal control operations
E 6
I 6
and expanding tabs.
I 9
.pl +1
E 9
.Sh 3 "Structured devices
E 6
.PP
D 6
When a terminal is first opened it is initialized to a standard
state and configured with a set of standard control, editing,
and interrupt characters.  A process
may alter this configuration with certain
D 3
control operations, specifying parameters in a standard structure:
E 3
I 3
control operations, specifying parameters in a standard structure:\(dg
.FS
\(dg The control interface described here is an internal interface only
in 4.3BSD.  Future releases will probably use a modified interface
based on currently-proposed standards.
.FE
E 3
.DS
._f
struct ttymode {
	short	tt_ispeed;	/* input speed */
	int	tt_iflags;	/* input flags */
	short	tt_ospeed;	/* output speed */
	int	tt_oflags;	/* output flags */
};
.DE
and ``special characters'' are specified with the 
\fIttychars\fP structure,
.DS
._f
struct ttychars {
	char	tc_erasec;	/* erase char */
	char	tc_killc;	/* erase line */
	char	tc_intrc;	/* interrupt */
	char	tc_quitc;	/* quit */
	char	tc_startc;	/* start output */
	char	tc_stopc;	/* stop output */
	char	tc_eofc;	/* end-of-file */
	char	tc_brkc;	/* input delimiter (like nl) */
	char	tc_suspc;	/* stop process signal */
	char	tc_dsuspc;	/* delayed stop process signal */
	char	tc_rprntc;	/* reprint line */
	char	tc_flushc;	/* flush output (toggles) */
	char	tc_werasc;	/* word erase */
	char	tc_lnextc;	/* literal next character */
};
.DE
.NH 4
Terminal hardware support
.PP
The terminal handler allows a user to access basic
hardware related functions; e.g. line speed,
modem control, parity, and stop bits.  A special signal,
SIGHUP, is automatically
sent to processes in a terminal's process
group when a carrier transition is detected.  This is
normally associated with a user hanging up on a modem
controlled terminal line.
.NH 3
Structured devices
.PP
Structures devices are typified by disks and magnetic
E 6
I 6
Structured devices are typified by disks and magnetic
E 6
tapes, but may represent any random-access device.
The system performs read-modify-write type buffering actions on block
D 8
devices to allow them to be read and written in a totally random
access fashion like ordinary files.
E 8
I 8
devices to allow them to be read and written in random access
fashion like ordinary files.
E 8
D 6
File systems are normally created in block devices.
.NH 3
Unstructured devices
E 6
I 6
D 7
Filesystems are normally created on block devices.
E 7
I 7
Filesystems are normally mounted on block devices.
I 9
.pl -1
E 9
E 7
.Sh 3 "Unstructured devices
E 6
.PP
Unstructured devices are those devices which
do not support block structure.  Familiar unstructured devices
are raw communications lines (with
no terminal handler), raster plotters, magnetic tape and disks unfettered
by buffering and permitting large block input/output and positioning
and formatting commands.
E 1
