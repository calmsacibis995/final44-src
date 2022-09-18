h38221
s 00001/00001/00026
d D 8.5 95/04/23 13:52:07 eric 5 4
c update DSN types to be more realistic
e
s 00001/00001/00026
d D 8.4 94/11/14 08:35:25 eric 4 3
c include F=P flag
e
s 00001/00001/00026
d D 8.3 94/11/13 18:03:22 eric 3 2
c needs F=n flag
e
s 00004/00005/00023
d D 8.2 94/02/19 07:55:42 eric 2 1
c avoid putting POP mailer at the top of the generated .cf file
e
s 00028/00000/00000
d D 8.1 93/12/15 06:36:42 eric 1 0
c date and time created 93/12/15 06:36:42 by eric
e
u
U
t
T
I 1
PUSHDIVERT(-1)
#
# Copyright (c) 1983 Eric P. Allman
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#

ifdef(`POP_MAILER_PATH',, `define(`POP_MAILER_PATH', /usr/lib/mh/spop)')
D 3
ifdef(`POP_MAILER_FLAGS',, `define(`POP_MAILER_FLAGS', `eu')')
E 3
I 3
D 4
ifdef(`POP_MAILER_FLAGS',, `define(`POP_MAILER_FLAGS', `enu')')
E 4
I 4
ifdef(`POP_MAILER_FLAGS',, `define(`POP_MAILER_FLAGS', `Penu')')
E 4
E 3
ifdef(`POP_MAILER_ARGS',, `define(`POP_MAILER_ARGS', `pop $u')')

POPDIVERT

D 2
LOCAL_CONFIG
# POP mailer is a pseudo-domain
CPPOP
POPDIVERT

E 2
####################################
###   POP Mailer specification   ###
####################################

VERSIONID(`%W% (Berkeley) %G%')

D 5
Mpop,		P=POP_MAILER_PATH, F=CONCAT(`lsDFM', POP_MAILER_FLAGS), S=10, R=20/40,
E 5
I 5
Mpop,		P=POP_MAILER_PATH, F=CONCAT(`lsDFM', POP_MAILER_FLAGS), S=10, R=20/40, T=DNS/RFC822/X-Unix,
E 5
		A=POP_MAILER_ARGS
I 2

LOCAL_CONFIG
# POP mailer is a pseudo-domain
CPPOP
E 2
E 1
