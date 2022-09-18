h16824
s 00010/00000/00034
d D 8.5 95/03/30 11:01:21 eric 5 4
c simplify nullclient m4 files
e
s 00001/00003/00033
d D 8.4 94/07/02 08:16:26 eric 4 3
c delete OLD_SENDMAIL support
e
s 00002/00001/00034
d D 8.3 94/05/10 08:11:29 eric 3 2
c allow SMTP_MAILER_MAX in nullclient configuration
e
s 00009/00003/00026
d D 8.2 93/08/21 16:19:52 eric 2 1
c convert from a MAILER to a FEATURE
e
s 00029/00000/00000
d D 8.1 93/08/21 15:05:10 eric 1 0
c date and time created 93/08/21 15:05:10 by eric
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
D 4
ifdef(`SMTP_MAILER_FLAGS',,
	`define(`SMTP_MAILER_FLAGS',
		`ifdef(`_OLD_SENDMAIL_', `L', `')')')
E 4
I 4
ifdef(`SMTP_MAILER_FLAGS',, `define(`SMTP_MAILER_FLAGS', `')')
E 4
I 2
define(_NULL_CLIENT_ONLY_, `1')
ifelse(_ARG_, `', `errprint(`Feature "nullclient" requires argument')',
	`define(`MAIL_HUB', _ARG_)')
E 2
POPDIVERT
D 2
############################################
###   Null Client Mailer specification   ###
############################################
E 2

#
#  This is used only for relaying mail from a client to a hub when
#  that client does absolutely nothing else -- i.e., it is a "null
#  mailer".  In this sense, it acts like the "R" option in Sun
#  sendmail.
#

VERSIONID(`%W% (Berkeley) %G%')

I 5
PUSHDIVERT(6)
# hub host (to which all mail is sent)
DH`'ifdef(`MAIL_HUB', MAIL_HUB,
	`errprint(`MAIL_HUB not defined for nullclient feature')')

# route-addr separators
C: : ,
POPDIVERT
E 5
I 2
PUSHDIVERT(7)
############################################
###   Null Client Mailer specification   ###
############################################

E 2
ifdef(`confRELAY_MAILER',,
	`define(`confRELAY_MAILER', `nullclient')')dnl
I 5
ifdef(`confFROM_HEADER',,
	`define(`confFROM_HEADER', <$g>)')dnl
E 5

D 3
Mnullclient,	P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), A=IPC $h
E 3
I 3
Mnullclient,	P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS),ifdef(`SMTP_MAILER_MAX', ` M=SMTP_MAILER_MAX,')
		A=IPC $h
E 3
I 2
POPDIVERT
E 2
E 1
