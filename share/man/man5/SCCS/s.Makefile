h62086
s 00000/00000/00018
d D 8.1 93/06/05 13:54:36 bostic 9 7
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00003/00015
d D 5.7.1.1 91/05/07 21:55:45 bostic 8 7
c branch for the 2nd network distribution
e
s 00001/00001/00017
d D 5.7 91/04/30 18:25:52 bostic 7 6
c move dbx.5 into dbx directory
e
s 00001/00001/00017
d D 5.6 90/06/23 15:48:05 bostic 6 5
c deprecate vfont.5
e
s 00012/00029/00006
d D 5.5 90/05/11 13:56:22 bostic 5 4
c first pass for new make
e
s 00005/00006/00030
d D 5.4 90/05/10 16:30:25 bostic 4 3
c checkpoint for pmake
e
s 00014/00031/00022
d D 5.3 89/03/06 11:05:44 bostic 3 2
c move man pages into source tree
e
s 00010/00005/00043
d D 5.2 88/07/09 11:37:51 bostic 2 1
c install approved copyright notice
e
s 00048/00000/00000
d D 5.1 87/12/12 18:21:42 bostic 1 0
c date and time created 87/12/12 18:21:42 by bostic
e
u
U
f b 
t
T
I 1
D 5
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 2
I 2
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 3
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
E 2
#
E 5
#	%W% (Berkeley) %G%
D 5
#
D 3
MDIR=	/usr/man/cat5
SRCS=	L-devices.5 L-dialcodes.5 L.aliases.5 L.cmds.5 L.sys.5 USERFILE.5 \
	a.out.5 acct.5 aliases.5 ar.5 core.5 dbx.5 dir.5 disklabel.5 \
	disktab.5 dm.config.5 dump.5 fs.5 fstab.5 gettytab.5 group.5 hosts.5 \
	map3270.5 \
	mtab.5 networks.5 passwd.5 phones.5 plot.5 printcap.5 protocols.5 \
	remote.5 resolver.5 services.5 shells.5 stab.5 tar.5 termcap.5 \
	tp.5 ttys.5 types.5 tzfile.5 utmp.5 uuencode.5 vfont.5 vgrindefs.5
E 3
I 3
D 4
MDIR=	${DESTDIR}/usr/man/cat5
E 3
OBJS=	L-devices.0 L-dialcodes.0 L.aliases.0 L.cmds.0 L.sys.0 USERFILE.0 \
D 3
	a.out.0 acct.0 aliases.0 ar.0 core.0 dbx.0 dir.0 disklabel.0 \
	disktab.0 dm.config.0 dump.0 fs.0 fstab.0 gettytab.0 group.0 hosts.0 \
	map3270.0 \
	mtab.0 networks.0 passwd.0 phones.0 plot.0 printcap.0 protocols.0 \
	remote.0 resolver.0 services.0 shells.0 stab.0 tar.0 termcap.0 \
	tp.0 ttys.0 types.0 tzfile.0 utmp.0 uuencode.0 vfont.0 vgrindefs.0
LINKS=	inode.0 dumpdates.0 wtmp.0
E 3
I 3
	a.out.0 acct.0 ar.0 core.0 dbx.0 dir.0 disktab.0 dump.0 fs.0 \
	fstab.0 gettytab.0 group.0 hosts.0 mtab.0 networks.0 \
E 4
I 4
MDIR=	${DESTDIR}/usr/share/man/cat5
OBJS=	a.out.0 acct.0 core.0 dbx.0 dir.0 disktab.0 dump.0 fs.0 \
	fstab.0 group.0 hosts.0 networks.0 \
E 4
	passwd.0 phones.0 plot.0 printcap.0 protocols.0 remote.0 \
D 4
	resolver.0 services.0 shells.0 stab.0 tar.0 tp.0 ttys.0 types.0 \
	tzfile.0 utmp.0 uuencode.0 vfont.0 vgrindefs.0
E 4
I 4
	resolver.0 services.0 shells.0 stab.0 types.0 \
E 5
I 5

D 7
MAN5=	a.out.0 acct.0 core.0 dbx.0 dir.0 disktab.0 dump.0 fs.0 fstab.0 \
E 7
I 7
D 8
MAN5=	a.out.0 acct.0 core.0 dir.0 disktab.0 dump.0 fs.0 fstab.0 \
E 7
	group.0 hosts.0 networks.0 passwd.0 phones.0 plot.0 printcap.0 \
E 8
I 8
MAN5=	a.out.0 acct.0 core.0 dir.0 disktab.0 fs.0 fstab.0 \
	group.0 hosts.0 networks.0 passwd.0 phones.0 printcap.0 \
E 8
	protocols.0 remote.0 resolver.0 services.0 shells.0 stab.0 types.0 \
E 5
D 6
	utmp.0 vfont.0
E 6
I 6
	utmp.0
E 6
I 5
D 8
MLINKS=	fs.5 inode.5 dump.5 dumpdates.5 utmp.5 wtmp.5
E 8
I 8
MLINKS=	fs.5 inode.5 utmp.5 wtmp.5
E 8
E 5
E 4
E 3

D 3
.SUFFIXES: .5 .0
E 3
I 3
D 5
all clean depend lint tags:
E 5
I 5
all: ${MAN5}
E 5
E 3

I 5
clean depend lint tags:

E 5
D 3
.5.0:
	${DESTDIR}/usr/man/manroff $*.5 > $*.0

all: ${OBJS}

clean: FRC
E 3
I 3
cleandir:
E 3
D 5
	rm -f ${OBJS}
E 5
I 5
	rm -f ${MAN5}
E 5

D 3
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/fs.0 ${DESTDIR}${MDIR}/inode.0
	ln ${DESTDIR}${MDIR}/dump.0 ${DESTDIR}${MDIR}/dumpdates.0
	ln ${DESTDIR}${MDIR}/utmp.0 ${DESTDIR}${MDIR}/wtmp.0

FRC:
E 3
I 3
D 5
install: ${OBJS}
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
	rm -f ${MDIR}/inode.0; ln ${MDIR}/fs.0 ${MDIR}/inode.0
	rm -f ${MDIR}/dumpdates.0; ln ${MDIR}/dump.0 ${MDIR}/dumpdates.0
	rm -f ${MDIR}/wtmp.0; ln ${MDIR}/utmp.0 ${MDIR}/wtmp.0
E 5
I 5
install: maninstall

.include <bsd.prog.mk>
E 5
E 3
E 1
