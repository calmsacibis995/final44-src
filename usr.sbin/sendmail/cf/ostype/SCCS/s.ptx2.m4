h52250
s 00019/00000/00000
d D 8.1 94/12/04 07:31:39 eric 1 0
c date and time created 94/12/04 07:31:39 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1994 Eric P. Allman
# Copyright (c) 1994
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#

# Support for DYNIX/ptx 2.x.

divert(0)
VERSIONID(`%W% (Berkeley) %G%')
ifdef(`ALIAS_FILE',,`define(`ALIAS_FILE', /usr/lib/aliases)')dnl
ifdef(`HELP_FILE',,`define(`HELP_FILE', /usr/lib/sendmail.hf)')dnl
ifdef(`STATUS_FILE',,`define(`STATUS_FILE', /usr/lib/sendmail.st)')dnl
define(`LOCAL_MAILER_PATH', `/bin/mail')dnl
define(`LOCAL_MAILER_FLAGS', `rmn')dnl
define(`LOCAL_SHELL_FLAGS', `e')dnl
E 1
