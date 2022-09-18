h19354
s 00002/00001/00020
d D 8.5 95/04/26 09:25:14 eric 7 6
c add *_MAILER_CHARSET; UUCP_MAX_SIZE => UUCP_MAILER_MAX
e
s 00001/00001/00020
d D 8.4 95/04/23 13:52:06 eric 6 5
c update DSN types to be more realistic
e
s 00002/00002/00019
d D 8.3 94/01/24 12:07:29 eric 5 4
c make USENET_MAILER_ARGS include argv[0] for consistency
e
s 00001/00001/00020
d D 8.2 94/01/24 12:06:56 eric 4 3
c allow localized specification of maximum message size
e
s 00002/00002/00019
d D 8.1 93/06/07 10:11:31 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00019
d D 6.2 93/02/20 14:16:28 eric 2 1
c make command line arguments configurable
e
s 00020/00000/00000
d D 6.1 93/02/19 20:30:49 eric 1 0
c date and time created 93/02/19 20:30:49 by eric
e
u
U
t
T
I 1
PUSHDIVERT(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 3
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 3
I 3
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 3
#
# %sccs.include.redist.sh%
#

ifdef(`USENET_MAILER_PATH',, `define(`USENET_MAILER_PATH', /usr/lib/news/inews)')
ifdef(`USENET_MAILER_FLAGS',, `define(`USENET_MAILER_FLAGS', `rlsDFMmn')')
I 2
D 5
ifdef(`USENET_MAILER_ARGS',, `define(`USENET_MAILER_ARGS', `-m -h -n')')
E 5
I 5
ifdef(`USENET_MAILER_ARGS',, `define(`USENET_MAILER_ARGS', `inews -m -h -n')')
E 5
E 2
POPDIVERT
####################################
###  USENET Mailer specification ###
####################################

VERSIONID(`%W% (Berkeley) %G%')

D 4
Musenet,	P=USENET_MAILER_PATH, F=USENET_MAILER_FLAGS, S=10, R=20,
E 4
I 4
D 6
Musenet,	P=USENET_MAILER_PATH, F=USENET_MAILER_FLAGS, S=10, R=20,ifdef(`USENET_MAILER_MAX', ` M=USENET_MAILER_MAX,')
E 6
I 6
D 7
Musenet,	P=USENET_MAILER_PATH, F=USENET_MAILER_FLAGS, S=10, R=20,ifdef(`USENET_MAILER_MAX', ` M=USENET_MAILER_MAX,'), T=X-Usenet/X-Usenet/X-Unix,
E 7
I 7
Musenet,	P=USENET_MAILER_PATH, F=USENET_MAILER_FLAGS, S=10, R=20,
		_OPTINS(`USENET_MAILER_MAX', `M=', `, ')T=X-Usenet/X-Usenet/X-Unix,
E 7
E 6
E 4
D 2
		A=inews -m -h -n $u
E 2
I 2
D 5
		A=inews USENET_MAILER_ARGS $u
E 5
I 5
		A=USENET_MAILER_ARGS $u
E 5
E 2
E 1
