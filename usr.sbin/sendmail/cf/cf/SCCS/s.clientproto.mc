h14939
s 00004/00002/00025
d D 8.4 95/04/21 08:38:59 eric 4 3
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00004/00000/00023
d D 8.3 95/02/17 12:49:10 eric 3 2
c fix comments to match README file
e
s 00005/00006/00018
d D 8.2 93/08/21 16:16:53 eric 2 1
c make nullclient a feature instead of a mailer
e
s 00024/00000/00000
d D 8.1 93/08/21 15:14:36 eric 1 0
c date and time created 93/08/21 15:14:36 by eric
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

#
#  This the prototype for a "null client" -- that is, a client that
D 4
#  does nothing except forward all mail to a mail hub.
E 4
I 4
#  does nothing except forward all mail to a mail hub.  IT IS NOT
#  USABLE AS IS!!!
E 4
#
D 2
#  To use this, you MUST define MAIL_HUB and include the "nullclient"
#  mailer.  You MAY also define an OSTYPE to define the location of
#  the queue directories and the like.  Other than these, it should
#  never contain any other lines.
E 2
I 2
#  To use this, you MUST use the nullclient feature with the name of
D 4
#  the mail hub as its argument.  You MAY also define an OSTYPE to
E 4
I 4
#  the mail hub as its argument.  You MUST also define an OSTYPE to
E 4
#  define the location of the queue directories and the like.
I 3
#  In addition, you MAY select the nocanonify feature.  This causes
#  addresses to be sent unqualified via the SMTP connection; normally
#  they are qualifed with the masquerade name, which defaults to the
#  name of the hub machine.
E 3
#  Other than these, it should never contain any other lines.
E 2
#

include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')

I 4
OSTYPE(unknown)
E 4
D 2
define(`MAIL_HUB', `mailhost.$m')
MAILER(nullclient)
E 2
I 2
FEATURE(nullclient, mailhost.$m)
E 2
E 1
