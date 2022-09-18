h03427
s 00001/00001/00018
d D 8.2 95/05/26 07:42:00 eric 2 1
c use -a$g for UUCP calls
e
s 00019/00000/00000
d D 8.1 93/08/24 14:15:48 eric 1 0
c date and time created 93/08/24 14:15:48 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#

divert(0)
VERSIONID(`%W% (Berkeley) %G%')

ifdef(`ALIAS_FILE',,`define(`ALIAS_FILE', /usr/ucblib/aliases)')dnl
ifdef(`HELP_FILE',,`define(`HELP_FILE', /usr/ucblib/sendmail.hf)')dnl
ifdef(`STATUS_FILE',,`define(`STATUS_FILE', /usr/ucblib/sendmail.st)')dnl
define(`LOCAL_MAILER_PATH', `/usr/ucblib/binmail')dnl
define(`LOCAL_MAILER_FLAGS', `rmn')dnl
define(`LOCAL_SHELL_FLAGS', `ehuP')dnl
D 2
define(`UUCP_MAILER_ARGS', `uux - -r -a$f -gmedium $h!rmail ($u)')dnl
E 2
I 2
define(`UUCP_MAILER_ARGS', `uux - -r -a$g -gmedium $h!rmail ($u)')dnl
E 2
E 1
