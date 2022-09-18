h17949
s 00000/00000/00012
d D 8.1 93/06/04 18:44:25 bostic 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00010
d D 5.10 92/09/02 11:52:44 bostic 13 12
c luna68k wants rbootd
e
s 00002/00002/00008
d D 5.9 92/08/06 12:38:59 bostic 12 11
c add lfs_cleanerd
e
s 00004/00000/00006
d D 5.8 92/07/23 16:41:03 bostic 11 8
c add rbootd to the list
e
s 00001/00001/00005
d R 5.8 92/07/20 10:37:12 bostic 10 8
c add mldistrib
e
s 00003/00001/00005
d D 5.7.1.1 91/08/20 17:43:26 mckusick 9 8
c delete data-stream encryption for the foreign sites (Network, Release 2)
e
s 00002/00010/00004
d D 5.7 91/04/01 08:50:24 bostic 8 6
c checkpoint
e
s 00003/00001/00013
d D 5.6.1.1 90/10/21 20:34:07 mckusick 7 6
c delete kpasswdd from the set of compiled programs
e
s 00001/00003/00013
d D 5.6 90/07/02 16:00:26 bostic 6 5
c don't make clean/cleandir special
e
s 00001/00001/00015
d D 5.5 90/07/01 01:12:03 bostic 5 4
c can't even clean pcc on the HP300
e
s 00001/00001/00015
d D 5.4 90/06/30 16:06:41 bostic 4 3
c add gcc
e
s 00012/00003/00004
d D 5.3 90/06/29 17:06:22 bostic 3 2
c most everything compiles now...
e
s 00004/00030/00003
d D 5.2 90/05/11 12:55:08 bostic 2 1
c first pass for new make
e
s 00033/00000/00000
d D 5.1 90/03/22 19:40:54 bostic 1 0
c checked in before pmake
e
u
U
f b 
t
T
I 1
D 2
#
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 2
#	%W% (Berkeley) %G%
D 2
#
E 2

D 2
# not current working
# pcc
SUBDIR=	c2 comsat fingerd ftpd getNAME getty makekey \
	rexecd rlogind rshd talkd telnetd tftpd
E 2
I 2
D 3
# not currently compilable: pcc
SUBDIR=	bugfiler c2 comsat delivermail fingerd ftpd getNAME getty makekey \
	rexecd rlogind rshd talkd telnetd tftpd uucpd
E 3
I 3
D 8
SUBDIR=	bugfiler comsat delivermail fingerd ftpd getNAME getty makekey \
D 7
	rexecd rlogind rshd talkd telnetd tftpd uucpd kpasswdd
E 7
I 7
	rexecd rlogind rshd talkd telnetd tftpd uucpd

#KERBEROS=kpasswdd
E 7

D 6
.if   make(clean) || make(cleandir)
D 5
SUBDIR+=pcc
E 5
I 5
SUBDIR+=
E 5
.elif ${MACHINE} == "hp300"
E 6
I 6
.if   ${MACHINE} == "hp300"
E 6
D 4
SUBDIR+=
E 4
I 4
SUBDIR+=gcc
E 4
.elif ${MACHINE} == "tahoe"
SUBDIR+=pcc
.elif ${MACHINE} == "vax"
SUBDIR+=pcc
.endif
E 8
I 8
D 9
D 12
SUBDIR=	bugfiler comsat fingerd ftpd getNAME getty kpasswdd mail.local \
E 9
I 9
SUBDIR=	bugfiler comsat fingerd ftpd getNAME getty mail.local \
E 9
	makekey rexecd rlogind rshd talkd telnetd tftpd uucpd
E 12
I 12
SUBDIR=	bugfiler comsat fingerd ftpd getNAME getty kpasswdd lfs_cleanerd \
	mail.local makekey rexecd rlogind rshd talkd telnetd tftpd uucpd
E 12
I 9

#KERBEROS=kpasswdd 
E 9
E 8
E 3
E 2

I 11
.if	${MACHINE} == "hp300"
SUBDIR+=rbootd
I 13
.elif	${MACHINE} == "luna68k"
SUBDIR+=rbootd
E 13
.endif

E 11
D 2
all clean cleandir depend install lint tags: FRC
	@-for i in ${SUBDIR}; do \
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done

${SUBDIR}: FRC
	cd $@; make ${MFLAGS} DESTDIR=${DESTDIR}

FRC:
E 2
I 2
.include <bsd.subdir.mk>
E 2
E 1
