h38782
s 00004/00004/00116
d D 8.7 95/05/25 12:59:48 bostic 35 34
c mroe standalone changes -- still not right, but close enough for now
e
s 00014/00012/00106
d D 8.6 95/05/25 12:36:59 bostic 34 33
c make it work without doing a chroot
e
s 00001/00001/00117
d D 8.5 94/05/05 09:23:15 bostic 33 32
c install networks sample file, too
e
s 00009/00005/00109
d D 8.4 94/01/25 09:05:53 bostic 32 31
c more tightening up of permissions
e
s 00018/00018/00096
d D 8.3 94/01/25 08:50:08 bostic 31 30
c make everything owned by root, group wheel, preferably not group
c writeable; we can't trust NFS, so just give it up
e
s 00003/00001/00111
d D 8.2 94/01/25 08:34:25 bostic 30 29
c .klogin should be 600, add .rhosts
e
s 00000/00000/00112
d D 8.1 93/06/13 18:06:15 bostic 29 28
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00009/00099
d D 5.27 93/06/13 18:06:07 bostic 28 26
c various cleanups for 4.4BSD
e
s 00000/00000/00108
d R 8.1 93/06/09 11:47:24 bostic 27 26
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00106
d D 5.26 93/01/23 13:15:24 bostic 26 25
c add in a symlink for /etc/termcap
e
s 00001/00000/00106
d D 5.25 92/08/24 12:40:12 bostic 25 24
c add X11 link to /usr/bin
e
s 00001/00001/00105
d D 5.24 92/07/29 12:53:36 bostic 24 23
c typo
e
s 00003/00000/00103
d D 5.23 92/07/24 17:47:19 bostic 23 22
c on hp300's, /usr/bin/X11 -> /usr/X11/bin
e
s 00005/00000/00098
d D 5.22 92/07/23 15:39:22 bostic 22 21
c add rbootd.conf
e
s 00001/00000/00097
d D 5.21 92/07/22 19:02:33 bostic 21 20
c add /sys link
e
s 00001/00001/00096
d D 5.20 92/07/22 18:56:27 bostic 20 19
c don't fail if /etc and /dev/exist
e
s 00001/00001/00096
d D 5.19 92/07/20 13:43:48 bostic 19 18
c put fstab files in/ etc
e
s 00001/00001/00096
d D 5.18 92/07/20 12:47:55 bostic 18 17
c MAKEDEV.hpux goes in /dev
e
s 00022/00010/00075
d D 5.17 92/07/15 18:01:11 bostic 17 16
c add mtree, make distribution cleaner
e
s 00001/00000/00084
d D 5.16 92/07/15 12:43:12 bostic 16 15
c move COPYRIGHT notice from man/man0, and install it
e
s 00012/00011/00072
d D 5.15 92/07/15 07:53:41 bostic 15 14
c fixes to make distribution work better, install MAKEDEV.hpux on hp300's
e
s 00004/00000/00079
d D 5.14 92/07/14 16:27:38 bostic 14 13
c install hpux MAKEDEV
e
s 00004/00004/00075
d D 5.13 92/04/17 16:18:26 bostic 13 12
c add changelist file
e
s 00001/00001/00078
d D 5.12 92/04/08 08:29:18 bostic 12 11
c add mtree/special
e
s 00008/00006/00071
d D 5.11 91/05/21 13:58:15 bostic 11 10
c install fstab example files
e
s 00002/00002/00075
d D 5.10 91/03/22 14:35:09 bostic 10 9
c install MAKEDEV.local too
e
s 00015/00000/00062
d D 5.9 90/07/01 22:47:19 bostic 9 8
c install tahoe wcs files, vax pcs file
e
s 00012/00002/00050
d D 5.8 90/07/01 15:17:21 bostic 8 7
c do dot files right
e
s 00003/00000/00049
d D 5.7 90/06/30 23:30:04 bostic 7 6
c add namedb files
e
s 00003/00001/00046
d D 5.6 90/06/30 23:14:41 bostic 6 5
c add disktab file
e
s 00015/00014/00032
d D 5.5 90/06/30 21:59:57 bostic 5 4
c update for June tape
e
s 00005/00001/00041
d D 5.4 90/06/30 15:14:49 bostic 4 3
c don't create object directory, add mtree files
e
s 00008/00007/00034
d D 5.3 90/06/26 14:57:20 bostic 3 2
c add /etc/dumpdates to create list
e
s 00003/00002/00038
d D 5.2 90/06/25 19:33:57 bostic 2 1
c don't use sym link for man.conf
e
s 00042/00000/00000
d D 5.1 90/06/25 18:59:36 bostic 1 0
c date and time created 90/06/25 18:59:36 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

I 4
NOOBJ=	oobj

I 6
# disktab may be wrong -- hcx9 is a tahoe, but gets its own.
E 6
E 4
# -rw-r--r--
D 5
BIN1=	aliases crontab daily ftpusers group hosts hosts.equiv hosts.lpd \
D 2
	inetd.conf man.conf monthly motd netstart printcap protocols rc \
	rc.local security services shells syslog.conf ttys weekly
E 2
I 2
	inetd.conf ../usr.bin/man/man/man.conf monthly motd netstart \
	printcap protocols rc rc.local security services shells syslog.conf \
	ttys weekly
E 5
I 5
D 13
BIN1=	aliases csh.cshrc csh.login csh.logout crontab daily dm.conf \
	ftpusers gettytab group hosts hosts.equiv hosts.lpd inetd.conf \
	man.conf monthly motd netstart phones printcap protocols rc \
D 6
	rc.local remote security services shells syslog.conf ttys weekly
E 6
I 6
	rc.local remote security services shells syslog.conf ttys weekly \
E 13
I 13
D 28
BIN1=	aliases changelist csh.cshrc csh.login csh.logout crontab daily \
	dm.conf ftpusers gettytab group hosts hosts.equiv hosts.lpd \
	inetd.conf man.conf monthly motd netstart phones printcap protocols \
	rc rc.local remote security services shells syslog.conf ttys weekly \
E 28
I 28
BIN1=	aliases amd-home amd-n changelist csh.cshrc csh.login csh.logout \
	crontab crontab.local daily dm.conf exports ftpusers ftpwelcome \
D 32
	gettytab group hosts hosts.equiv hosts.lpd inetd.conf man.conf \
	monthly motd netgroup netstart phones printcap protocols rc \
E 32
I 32
	gettytab group hosts hosts.lpd inetd.conf man.conf \
D 33
	monthly motd netgroup phones printcap protocols rc \
E 33
I 33
	monthly motd netgroup networks phones printcap protocols rc \
E 33
E 32
	rc.local remote security services shells syslog.conf ttys weekly \
E 28
E 13
	etc.${MACHINE}/disktab
E 6
E 5
E 2

# -rw-rw-rw-
BIN2=	motd

D 5
# -rw-r--r--
ROOT1=	master.passwd

E 5
I 5
D 8
DOT=	dot.cshrc dot.login dot.profile
E 8
E 5
I 4
D 12
MTREE=	BSD.root.dist BSD.usr.dist BSD.var.dist
E 12
I 12
D 17
MTREE=	BSD.root.dist BSD.usr.dist BSD.var.dist special
E 17
I 17
D 28
MTREE=	4.4alpha.dist special
E 28
I 28
D 32
MTREE=	4.4BSD.dist special
E 32
E 28
E 17
E 12
I 5
KRB=	README krb.conf krb.realms
I 7
NAMEDB=	localhost.rev named.boot root.cache
I 9
PCS=	pcs750.bin
WCS1=	wcs fppwcs poc poc1 poc2 fppoc
WCS2=	fpevent fppwcs fppwcs_dual hdcwcs load_diags start_fpp wcs wcs_dual
I 22
RBOOTD=	rbootd.conf
E 22
E 9
E 7
E 5
E 4

all clean cleandir depend etc install lint:

distribution:
D 15
	install -c -o ${BINOWN} -g ${BINGRP} -m 644 ${BIN1} ${DESTDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m 666 ${BIN2} ${DESTDIR}/etc
E 15
I 15
D 17
	# password file first
E 15
D 5
	install -c -o root -g wheel -m 644 ${ROOT1} ${DESTDIR}/etc
E 5
I 5
	install -c -o root -g wheel -m 600 master.passwd ${DESTDIR}/etc
D 15
	(cd ${DESTDIR}/etc; \
	    mkpasswd -p master.passwd; \
	    mv master.passwd.pag passwd.pag; \
	    mv master.passwd.dir passwd.dir; \
	    mv master.passwd.orig passwd)
E 15
I 15
	install -c -o root -g wheel -m 600 master.passwd ${DESTDIR}/tmp/p
E 17
I 17
	# Hand-craft the password file first.
D 20
	mkdir /etc /dev
E 20
I 20
D 35
	-mkdir /etc /dev
E 35
I 35
	-mkdir ${DESTDIR}/etc ${DESTDIR}/dev ${DESTDIR}/tmp
E 35
E 20
	cp master.passwd ${DESTDIR}/tmp/p
E 17
D 35
	pwd_mkdb -p /tmp/p
	rm -f /tmp/p
I 17
	cp group /etc/group
E 35
I 35
	-pwd_mkdb -p ${DESTDIR}/tmp/p
	rm -f ${DESTDIR}/tmp/p
	cp group ${DESTDIR}/etc/group
E 35
	# Build the tree.
D 28
	-mtree -def mtree/4.4alpha.dist -p ${DESTDIR}/ -u
E 28
I 28
	-mtree -def mtree/4.4BSD.dist -p ${DESTDIR}/ -u
E 28
E 17
	# install devices
.if ${MACHINE} == "hp300"
D 31
	(cd etc.hp300; install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
E 31
I 31
	(cd etc.hp300; install -c -o root -g wheel -m 444 \
E 31
D 18
	    MAKEDEV.hpux ${DESTDIR}/)
E 18
I 18
	    MAKEDEV.hpux ${DESTDIR}/dev)
E 18
.endif
E 15
E 5
D 10
	install -c -o ${BINOWN} -g ${BINGRP} -m 555 etc.${MACHINE}/MAKEDEV \
	    ${DESTDIR}/dev
E 10
I 10
D 31
	install -c -o ${BINOWN} -g ${BINGRP} -m 555 \
E 31
I 31
	install -c -o root -g wheel -m 555 \
E 31
	     MAKEDEV.local etc.${MACHINE}/MAKEDEV ${DESTDIR}/dev
I 15
D 34
	(cd /dev && ./MAKEDEV std)
E 34
I 34
	(cd ${DESTDIR}/dev && ./MAKEDEV std)
E 34
I 16
D 31
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 COPYRIGHT ${DESTDIR}/
E 31
I 31
	install -c -o root -g wheel -m 444 COPYRIGHT ${DESTDIR}/
E 31
I 17
	install -c -o root -g wheel -m 600 master.passwd ${DESTDIR}/etc
I 32
	install -c -o root -g wheel -m 600 hosts.equiv ${DESTDIR}/etc
	install -c -o root -g wheel -m 744 netstart ${DESTDIR}/etc
E 32
E 17
E 16
D 31
	install -c -o ${BINOWN} -g ${BINGRP} -m 644 ${BIN1} ${DESTDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m 666 ${BIN2} ${DESTDIR}/etc
E 31
I 31
	install -c -o root -g wheel -m 644 ${BIN1} ${DESTDIR}/etc
	install -c -o root -g wheel -m 666 ${BIN2} ${DESTDIR}/etc
E 31
I 17
D 26
	(cd /etc && rm -f rmt && ln -s /usr/sbin/rmt rmt)
E 26
E 17
E 15
E 10
D 3
# this is a bug -- someone, somewhere should be creating these!
E 3
I 3
D 5
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 root/dot.cshrc \
	    ${DESTDIR}/root/.cshrc
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 root/dot.login \
	    ${DESTDIR}/root/.login
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 root/dot.profile \
	    ${DESTDIR}/root/.profile
E 5
I 5
D 8
	cd root; install -c -o root -g wheel -m 644 ${DOT} ${DESTDIR}/root
E 8
I 8
	(cd root; \
		install -c -o root -g wheel -m 644 dot.cshrc \
		    ${DESTDIR}/root/.cshrc; \
D 30
		install -c -o root -g wheel -m 644 dot.klogin \
E 30
I 30
		install -c -o root -g wheel -m 600 dot.klogin \
E 30
		    ${DESTDIR}/root/.klogin; \
		install -c -o root -g wheel -m 644 dot.login \
		    ${DESTDIR}/root/.login; \
		install -c -o root -g wheel -m 644 dot.profile \
		    ${DESTDIR}/root/.profile; \
I 30
		install -c -o root -g wheel -m 600 dot.rhosts \
		    ${DESTDIR}/root/.rhosts; \
E 30
		rm -f ${DESTDIR}/.cshrc ${DESTDIR}/.profile; \
		ln ${DESTDIR}/root/.cshrc ${DESTDIR}/.cshrc; \
		ln ${DESTDIR}/root/.profile ${DESTDIR}/.profile)
E 8
E 5
I 4
D 17
	cd mtree; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${MTREE} \
	    ${DESTDIR}/etc/mtree
I 7
	cd namedb; install -c -o ${BINOWN} -g ${BINGRP} -m 644 ${NAMEDB} \
	    ${DESTDIR}/etc/namedb
E 7
I 5
	cd kerberosIV; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${KRB} \
	    ${DESTDIR}/etc/kerberosIV
E 17
I 17
D 31
	(cd mtree; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${MTREE} \
E 31
I 31
D 32
	(cd mtree; install -c -o root -g wheel -m 444 ${MTREE} \
E 31
	    ${DESTDIR}/etc/mtree)
E 32
I 32
	(cd mtree; \
		install -c -o root -g wheel -m 600 special \
		    ${DESTDIR}/etc/mtree; \
		install -c -o root -g wheel -m 444 4.4BSD.dist \
		    ${DESTDIR}/etc/mtree)
E 32
D 31
	(cd namedb; install -c -o ${BINOWN} -g ${BINGRP} -m 644 ${NAMEDB} \
E 31
I 31
	(cd namedb; install -c -o root -g wheel -m 644 ${NAMEDB} \
E 31
	    ${DESTDIR}/etc/namedb)
D 31
	(cd kerberosIV; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${KRB} \
E 31
I 31
	(cd kerberosIV; install -c -o root -g wheel -m 444 ${KRB} \
E 31
	    ${DESTDIR}/etc/kerberosIV)
E 17
E 5
E 4
D 31
	install -c -o ${BINOWN} -g operator -m 664 /dev/null \
E 31
I 31
	install -c -o root -g operator -m 664 /dev/null \
E 31
	    ${DESTDIR}/etc/dumpdates
I 28
	install -c -o root -g staff -m 644 /dev/null \
	    ${DESTDIR}/var/log/lastlog
E 28
E 3
D 31
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 /dev/null \
E 31
I 31
	install -c -o root -g wheel -m 644 /dev/null \
E 31
	    ${DESTDIR}/var/log/messages
D 31
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 /dev/null \
E 31
I 31
	install -c -o root -g wheel -m 644 /dev/null \
E 31
	    ${DESTDIR}/var/log/maillog
D 31
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 /dev/null \
E 31
I 31
	install -c -o root -g wheel -m 644 /dev/null \
E 31
	    ${DESTDIR}/var/log/lpd-errs
D 31
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 /dev/null \
E 31
I 31
	install -c -o root -g utmp -m 664 /dev/null \
E 31
	    ${DESTDIR}/var/run/utmp
I 11
D 31
	(cd etc.${MACHINE}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
E 31
I 31
	(cd etc.${MACHINE}; install -c -o root -g wheel -m 444 \
E 31
D 19
	    fstab.* ${DESTDIR}/)
E 19
I 19
	    fstab.* ${DESTDIR}/etc)
I 22
.if ${MACHINE} == "hp300"
D 31
	(cd etc.hp300; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${RBOOTD} \
E 31
I 31
	(cd etc.hp300; install -c -o root -g wheel -m 444 ${RBOOTD} \
E 31
	    ${DESTDIR}/etc)
.endif
E 22
E 19
I 14
D 15
.if ${MACHINE} == "hp300"
	(cd etc.hp300; install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    MAKEDEV.hpux ${DESTDIR}/)
.endif
E 15
E 14
E 11
I 9
.if ${MACHINE} == "tahoe"
D 11
	cd etc.tahoe; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${WCS1} \
	    ${DESTDIR}/
E 11
I 11
D 31
	(cd etc.tahoe; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${WCS1} \
E 31
I 31
	(cd etc.tahoe; install -c -o root -g wheel -m 444 ${WCS1} \
E 31
	    ${DESTDIR}/)
E 11
.endif
.if ${MACHINE} == "vax"
D 11
	cd etc.vax; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${PCS} \
	    ${DESTDIR}/
E 11
I 11
D 31
	(cd etc.vax; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${PCS} \
E 31
I 31
	(cd etc.vax; install -c -o root -g wheel -m 444 ${PCS} \
E 31
	    ${DESTDIR}/)
E 11
.endif
I 17
	# There are certain symbolic links we have to have, and
	# no other place to have install them.
I 21
D 28
	(cd / && rm -f sys && ln -s /usr/src/sys sys)
E 28
I 28
D 34
	(cd / && rm -f sys && ln -s usr/src/sys sys)
E 28
I 26
	(cd /etc && rm -f rmt && ln -s /usr/sbin/rmt rmt)
	(cd /etc && rm -f termcap && ln -s /usr/share/misc/termcap termcap)
E 26
I 25
D 28
	(cd /usr/bin && rm -f X11 && ln -s /usr/X11R4/bin X11)
E 28
I 28
	(cd /usr && rm -f X11 && ln -s X11R5 X11)
	(cd /usr/bin && rm -f X11 && ln -s /usr/X11/bin X11)
E 28
E 25
E 21
	(cd /usr/lib && rm -f X && ln -s /usr/hpux/lib/X X)
D 28
	(cd /usr/lib && rm -f X11 && ln -s /usr/X11R4/lib X11)
E 28
I 28
	(cd /usr/lib && rm -f X11 && ln -s /usr/X11/lib X11)
E 28
	(cd /usr/lib && rm -f grmd && ln -s /usr/hpux/lib/grmd grmd)
	(cd /usr/lib && rm -f tmac && ln -s /usr/share/tmac tmac)
	(cd /usr/ucb && rm -f rdist && ln -s /usr/bin/rdist rdist)
E 34
I 34
	(cd ${DESTDIR}/ && rm -f sys && ln -s usr/src/sys sys)
	(cd ${DESTDIR}/etc && rm -f rmt && ln -s /usr/sbin/rmt rmt)
	(cd ${DESTDIR}/etc && \
	    rm -f termcap && ln -s /usr/share/misc/termcap termcap)
	(cd ${DESTDIR}/usr && rm -f X11 && ln -s X11R5 X11)
	(cd ${DESTDIR}/usr && rm -f X11 && ln -s X11R6 X11)
	(cd ${DESTDIR}/usr/bin && rm -f X11 && ln -s /usr/X11/bin X11)
	(cd ${DESTDIR}/usr/lib && rm -f X && ln -s /usr/hpux/lib/X X)
	(cd ${DESTDIR}/usr/lib && rm -f X11 && ln -s /usr/X11/lib X11)
	(cd ${DESTDIR}/usr/lib && rm -f grmd && ln -s /usr/hpux/lib/grmd grmd)
	(cd ${DESTDIR}/usr/lib && rm -f tmac && ln -s /usr/share/tmac tmac)
	(cd ${DESTDIR}/usr/ucb && rm -f rdist && ln -s /usr/bin/rdist rdist)
E 34
I 23
.if ${MACHINE} == "hp300"
D 34
	(cd /usr/bin && rm -f X11 && ln -s /usr/X11/bin X11)
E 34
I 34
	(cd ${DESTDIR}/usr/bin && rm -f X11 && ln -s /usr/X11/bin X11)
E 34
D 24
#.endif
E 24
I 24
.endif
E 24
E 23
E 17

hcx9-distribution:
D 11
	cd etc.tahoe; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${WCS2} \
	    ${DESTDIR}/
E 11
I 11
D 31
	(cd etc.tahoe; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${WCS2} \
E 31
I 31
	(cd etc.tahoe; install -c -o root -g wheel -m 444 ${WCS2} \
E 31
	    ${DESTDIR}/)
E 11
E 9
D 3
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 root/dot.cshrc \
	    ${DESTDIR}/root/.cshrc
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 root/dot.login \
	    ${DESTDIR}/root/.login
	install -c -o ${BINOWN} -g ${BINGRP} -m 664 root/dot.profile \
	    ${DESTDIR}/root/.profile
E 3
D 4

E 4

.include <bsd.prog.mk>
E 1
