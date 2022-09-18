h35357
s 00000/00000/00006
d D 8.1 93/06/05 13:57:35 bostic 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00005
d D 5.11 91/03/22 14:29:28 bostic 13 12
c delete makedev, created machine specific ones
e
s 00001/00001/00005
d D 5.10 91/03/22 14:22:29 bostic 12 10
c add i386 and tahoe subdirectories
e
s 00001/00001/00005
d R 5.10 91/02/09 21:06:24 william 11 10
c added 386 entry
e
s 00000/00009/00006
d D 5.9 90/07/01 10:37:25 bostic 10 9
c don't need these targets
e
s 00001/00001/00014
d D 5.8 90/06/29 20:17:19 bostic 9 8
c add hp300
e
s 00000/00002/00015
d D 5.7 90/05/24 16:56:15 bostic 8 7
c don't need those links
e
s 00012/00029/00005
d D 5.6 90/05/11 13:56:10 bostic 7 6
c first pass for new make
e
s 00002/00002/00032
d D 5.5 90/05/10 16:34:06 bostic 6 5
c checkpoint for pmake
e
s 00013/00051/00021
d D 5.4 89/03/06 11:13:17 bostic 5 4
c move man pages into src tree
e
s 00010/00005/00062
d D 5.3 88/07/09 11:31:52 bostic 4 3
c install approved copyright notice
e
s 00004/00004/00063
d D 5.2 88/06/08 21:44:22 bostic 3 1
c add fsdb
e
s 00002/00002/00065
d R 5.2 88/05/05 10:34:27 bostic 2 1
c add fsdb
e
s 00067/00000/00000
d D 5.1 88/05/05 10:32:16 mckusick 1 0
c recreate after previous Makefile lost
e
u
U
t
T
I 1
D 7
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 4
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 4
I 4
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 5
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
E 4
#
E 7
#	%W% (Berkeley) %G%
D 7
#
D 5
MDIR=	/usr/man/cat8
SRCS=	XNSrouted.8 \
	ac.8 adduser.8 arp.8 badsect.8 bugfiler.8 chown.8 \
	clri.8 comsat.8 config.8 cron.8 dcheck.8 disklabel.8 diskpart.8 \
D 3
	dm.8 dmesg.8 dump.8 dumpfs.8 edquota.8 \
	fastboot.8 fingerd.8 fsck.8 fstat.8 ftpd.8 gettable.8 getty.8 halt.8 \
E 3
I 3
	dm.8 dmesg.8 dump.8 dumpfs.8 edquota.8 fastboot.8 fingerd.8 \
	fsck.8 fsdb.8 fstat.8 ftpd.8 gettable.8 getty.8 halt.8 \
E 3
	htable.8 icheck.8 ifconfig.8 implog.8 implogd.8 inetd.8 init.8 \
	intro.8 kgmon.8 lpc.8 lpd.8 makedev.8 makekey.8 mkhosts.8 \
	mklost+found.8 mknod.8 mkpasswd.8 mkproto.8 mount.8 named.8 \
	ncheck.8 newfs.8 pac.8 ping.8 pstat.8 quot.8 quotacheck.8 quotaon.8 \
	rc.8 rdump.8 renice.8 repquota.8 restore.8 rexecd.8 \
	rlogind.8 rmt.8 route.8 routed.8 rrestore.8 rshd.8 rwhod.8 sa.8 \
	savecore.8 sendmail.8 shutdown.8 slattach.8 sticky.8 swapon.8 \
	sync.8 syslogd.8 talkd.8 telnetd.8 tftpd.8 timed.8 timedc.8 trpt.8 \
	trsp.8 tunefs.8 update.8 uucico.8 uuclean.8 uupoll.8 uusnap.8 \
	uuxqt.8 vipw.8
OBJS=	XNSrouted.0 \
	ac.0 adduser.0 arp.0 badsect.0 bugfiler.0 chown.0 \
	clri.0 comsat.0 config.0 cron.0 dcheck.0 disklabel.0 diskpart.0 \
D 3
	dm.0 dmesg.0 dump.0 dumpfs.0 edquota.0 \
	fastboot.0 fingerd.0 fsck.0 fstat.0 ftpd.0 gettable.0 getty.0 halt.0 \
E 3
I 3
	dm.0 dmesg.0 dump.0 dumpfs.0 edquota.0 fastboot.0 fingerd.0 \
	fsck.0 fsdb.0 fstat.0 ftpd.0 gettable.0 getty.0 halt.0 \
E 3
	htable.0 icheck.0 ifconfig.0 implog.0 implogd.0 inetd.0 init.0 \
	intro.0 kgmon.0 lpc.0 lpd.0 makedev.0 makekey.0 mkhosts.0 \
	mklost+found.0 mknod.0 mkpasswd.0 mkproto.0 mount.0 named.0 \
	ncheck.0 newfs.0 pac.0 ping.0 pstat.0 quot.0 quotacheck.0 quotaon.0 \
	rc.0 rdump.0 renice.0 repquota.0 restore.0 rexecd.0 \
	rlogind.0 rmt.0 route.0 routed.0 rrestore.0 rshd.0 rwhod.0 sa.0 \
	savecore.0 sendmail.0 shutdown.0 slattach.0 sticky.0 swapon.0 \
	sync.0 syslogd.0 talkd.0 telnetd.0 tftpd.0 timed.0 timedc.0 trpt.0 \
	trsp.0 tunefs.0 update.0 uucico.0 uuclean.0 uupoll.0 uusnap.0 \
	uuxqt.0 vipw.0
LINKS=	accton.0 umount.0 mkfs.0 quotaoff.0 uucpd.0 fasthalt.0
E 5
I 5
D 6
MDIR=	${DESTDIR}/usr/man/cat8
OBJS=	adduser.0 intro.0 makedev.0 makekey.0 rc.0 sticky.0
E 6
I 6
MDIR=	${DESTDIR}/usr/share/man/cat8
OBJS=	adduser.0 intro.0 makedev.0 rc.0 sticky.0
E 7
E 6
E 5

D 5
.SUFFIXES: .8 .0
E 5
I 5
D 7
all clean depend lint tags:
E 7
I 7
D 13
MAN8=	adduser.0 intro.0 makedev.0 rc.0 sticky.0
E 13
I 13
MAN8=	adduser.0 intro.0 rc.0 sticky.0
E 13
D 8
MLINKS=	sa.8 accton.8 mount.8 umount.8 newfs.8 mkfs.8 quotaon.8 quotaoff.8 \
	uucico.8 uucpd.8 fastboot.8 fasthalt.8
E 8
D 9
SUBDIR=	man8.vax
E 9
I 9
D 12
SUBDIR=	man8.hp300 man8.vax
E 12
I 12
SUBDIR=	man8.i386 man8.hp300 man8.tahoe man8.vax
E 12
E 9
E 7
E 5

I 7
D 10
all: ${MAN8}

clean depend lint tags:

E 7
D 5
.8.0:
	${DESTDIR}/usr/man/manroff $*.8 > $*.0

all: ${OBJS}

clean: FRC
E 5
I 5
cleandir:
E 5
D 7
	rm -f ${OBJS}
E 7
I 7
	rm -f ${MAN8}
E 7

D 5
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/sa.0 ${DESTDIR}${MDIR}/accton.0
	ln ${DESTDIR}${MDIR}/mount.0 ${DESTDIR}${MDIR}/umount.0
	ln ${DESTDIR}${MDIR}/newfs.0 ${DESTDIR}${MDIR}/mkfs.0
	ln ${DESTDIR}${MDIR}/quotaon.0 ${DESTDIR}${MDIR}/quotaoff.0
	ln ${DESTDIR}${MDIR}/uucico.0 ${DESTDIR}${MDIR}/uucpd.0
	ln ${DESTDIR}${MDIR}/fastboot.0 ${DESTDIR}${MDIR}/fasthalt.0

FRC:
E 5
I 5
D 7
install: ${OBJS}
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
	rm -f ${MDIR}/accton.0; ln ${MDIR}/sa.0 ${MDIR}/accton.0
	rm -f ${MDIR}/umount.0; ln ${MDIR}/mount.0 ${MDIR}/umount.0
	rm -f ${MDIR}/mkfs.0; ln ${MDIR}/newfs.0 ${MDIR}/mkfs.0
	rm -f ${MDIR}/quotaoff.0; ln ${MDIR}/quotaon.0 ${MDIR}/quotaoff.0
	rm -f ${MDIR}/uucpd.0; ln ${MDIR}/uucico.0 ${MDIR}/uucpd.0
	rm -f ${MDIR}/fasthalt.0; ln ${MDIR}/fastboot.0 ${MDIR}/fasthalt.0
E 7
I 7
install: maninstall

E 10
.include <bsd.prog.mk>
E 7
E 5
E 1
