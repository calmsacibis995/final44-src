h45709
s 00001/00001/00023
d D 8.3 95/04/23 13:52:05 eric 5 4
c update DSN types to be more realistic
e
s 00003/00001/00021
d D 8.2 94/01/24 12:06:55 eric 4 3
c allow localized specification of maximum message size
e
s 00002/00002/00020
d D 8.1 93/06/07 10:11:18 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00019
d D 6.2 93/03/03 10:06:29 eric 2 1
c fixes to make this really match Sam's distribution
e
s 00021/00000/00000
d D 6.1 93/03/01 14:45:22 eric 1 0
c date and time created 93/03/01 14:45:22 by eric
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
#	This assumes you already have Sam Leffler's FAX software.
#
# %sccs.include.redist.sh%
#

D 2
ifdef(`FAX_MAILER_PATH',, `define(`FAX_MAILER_PATH', /usr/local/bin/mailfax)')
E 2
I 2
ifdef(`FAX_MAILER_PATH',,
	`define(`FAX_MAILER_PATH', /usr/local/lib/fax/mailfax)')
I 4
ifdef(`FAX_MAILER_MAX',,
	`define(`FAX_MAILER_MAX', 100000)')
E 4
E 2
POPDIVERT
####################################
###   FAX Mailer specification   ###
####################################

VERSIONID(`%W% (Berkeley) %G%')

D 4
Mfax,		P=FAX_MAILER_PATH, F=DFMhu, S=14, R=24, M=100000,
E 4
I 4
D 5
Mfax,		P=FAX_MAILER_PATH, F=DFMhu, S=14, R=24, M=FAX_MAILER_MAX,
E 5
I 5
Mfax,		P=FAX_MAILER_PATH, F=DFMhu, S=14, R=24, M=FAX_MAILER_MAX, T=X-Phone/X-FAX/X-Unix,
E 5
E 4
D 2
		A=mailfax -d $u@$h
E 2
I 2
		A=mailfax $u $h $f
E 2
E 1
