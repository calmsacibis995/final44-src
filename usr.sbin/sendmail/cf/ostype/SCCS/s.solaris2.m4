h61059
s 00001/00000/00017
d D 8.3 94/06/27 07:14:21 eric 3 2
c sendmail.cw file belongs in /etc/mail with everything else
e
s 00001/00001/00016
d D 8.2 94/01/23 16:48:05 eric 2 1
c fix location of help file
e
s 00017/00000/00000
d D 8.1 93/08/07 09:11:55 eric 1 0
c date and time created 93/08/07 09:11:55 by eric
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
divert(-1)

define(`ALIAS_FILE', /etc/mail/aliases)
D 2
define(`HELP_FILE', /var/lib/sendmail.hf)
E 2
I 2
define(`HELP_FILE', /etc/mail/sendmail.hf)
E 2
define(`STATUS_FILE', /etc/mail/sendmail.st)
define(`LOCAL_MAILER_FLAGS', `fSn')
I 3
define(`confCW_FILE', /etc/mail/sendmail.cw)
E 3
E 1
