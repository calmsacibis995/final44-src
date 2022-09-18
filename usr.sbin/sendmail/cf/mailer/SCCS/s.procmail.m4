h32546
s 00001/00001/00025
d D 8.4 95/04/23 13:52:07 eric 4 3
c update DSN types to be more realistic
e
s 00001/00001/00025
d D 8.3 95/03/21 04:56:20 eric 3 2
c patch from Kimmo Suominen <kim@tac.nyc.ny.us>
e
s 00001/00001/00025
d D 8.2 95/02/15 16:49:00 eric 2 1
c add LOCAL_MAILER_MAX and PROCMAIL_MAILER_MAX
e
s 00026/00000/00000
d D 8.1 94/11/20 17:11:58 eric 1 0
c date and time created 94/11/20 17:11:58 by eric
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

ifdef(`PROCMAIL_PATH',,
	`define(`PROCMAIL_PATH', /usr/local/bin/procmail)')
ifdef(`PROCMAIL_MAILER_FLAGS',,
	`define(`PROCMAIL_MAILER_FLAGS', `Shu')')
ifdef(`PROCMAIL_MAILER_ARGS',,
	`define(`PROCMAIL_MAILER_ARGS', `procmail -m $h $f $u')')

POPDIVERT

######################*****##############
###   PROCMAIL Mailer specification   ###
##################*****##################

VERSIONID(`%W% (Berkeley) %G%')

D 3
Mprocmail,	P=PROCMAIL_PATH, F=CONCAT(`DFMmn', PROCMAIL_MAILER_FLAGS), S=11/31, R=21/31,
E 3
I 3
D 4
Mprocmail,	P=PROCMAIL_PATH, F=CONCAT(`DFMm', PROCMAIL_MAILER_FLAGS), S=11/31, R=21/31,
E 4
I 4
Mprocmail,	P=PROCMAIL_PATH, F=CONCAT(`DFMm', PROCMAIL_MAILER_FLAGS), S=11/31, R=21/31, T=DNS/RFC822/X-Unix,
E 4
E 3
D 2
		A=PROCMAIL_MAILER_ARGS
E 2
I 2
		ifdef(`PROCMAIL_MAILER_MAX', `M=PROCMAIL_MAILER_MAX, ')A=PROCMAIL_MAILER_ARGS
E 2
E 1
