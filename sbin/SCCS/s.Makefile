h54352
s 00001/00001/00009
d D 8.5 94/03/31 06:16:58 bostic 16 15
c move mount_lofs to /usr/src/old
c lofs is subsumed by either null or union depending what you are
c trying to do
c From: Jan-Simon Pendry <pendry@vangogh.CS.Berkeley.EDU>
e
s 00002/00002/00008
d D 8.4 94/02/11 19:22:12 pendry 15 14
c added mount_union
e
s 00003/00003/00007
d D 8.3 94/01/26 23:28:06 pendry 14 13
c added procfs
e
s 00005/00005/00005
d D 8.2 94/01/21 18:14:04 mckusick 13 12
c add mount_cd9660
e
s 00000/00000/00010
d D 8.1 93/06/08 18:48:54 bostic 12 11
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.10 93/06/08 18:48:49 bostic 11 10
c add mount_lfs
e
s 00000/00006/00010
d D 5.9 93/05/19 17:04:51 bostic 10 9
c move enpload to /usr/src/old
e
s 00002/00002/00014
d D 5.8 92/07/20 12:11:05 bostic 9 8
c add scsiformat
e
s 00006/00005/00010
d D 5.7 92/07/19 17:55:25 bostic 8 7
c bring up to date
e
s 00007/00006/00008
d D 5.6 92/07/19 16:49:17 bostic 7 6
c checkpoint for 4.4Alpha
e
s 00001/00001/00013
d D 5.5 91/10/28 18:20:27 bostic 6 4
c fold halt and reboot together
e
s 00003/00001/00013
d D 5.4.1.1 91/05/07 14:16:39 bostic 5 4
c branch for the 2nd network distribution
e
s 00001/00001/00013
d D 5.4 91/05/06 18:23:45 bostic 4 3
c checkpoint
e
s 00003/00001/00011
d D 5.3 90/06/25 00:53:32 bostic 3 2
c checkpoint for June tape
e
s 00008/00034/00004
d D 5.2 90/05/11 13:04:04 bostic 2 1
c first pass for new make
e
s 00038/00000/00000
d D 5.1 90/03/23 11:04:36 bostic 1 0
c date and time created 90/03/23 11:04:36 by bostic
e
u
U
f b 
t
T
I 1
D 2
#
# Copyright (c) 1988 The Regents of the University of California.
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
SUBDIR=	badsect chown clri disklabel dmesg dump dumpfs enpload \
	fastboot fsck \
	fsdb halt icheck ifconfig init mknod mount ncheck newfs \
	ping quotacheck reboot restore route savecore shutdown \
	slattach swapon tunefs umount vipw
E 2

I 5
# Missing: icheck, init, ncheck

E 5
D 2
all depend install lint tags: FRC
	@-for i in ${SUBDIR}; do \
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 2
I 2
D 7
SUBDIR=	XNSrouted badsect clri disklabel dmesg dump dumpfs fastboot fsck \
D 5
D 6
	fsdb halt icheck ifconfig init mknod mount mountd ncheck newfs \
E 6
I 6
	fsdb icheck ifconfig init mknod mount mountd ncheck newfs \
E 6
E 5
I 5
	fsdb halt ifconfig mknod mount mountd newfs \
E 5
	nfsd nfsiod ping quotacheck reboot restore route routed savecore \
D 4
	shutdown slattach swapon tunefs umount vipw
E 4
I 4
	shutdown slattach swapon tunefs umount
E 7
I 7
D 8
SUBDIR=	XNSrouted badsect clri disklabel dmesg dump dumpfs fastboot fsck fsdb \
	icheck ifconfig init mknod mount mount_fdesc mount_lofs mount_nfs \
	mountd ncheck newfs nfsd nfsiod nologin ping quotacheck \
	reboot restore route routed savecore shutdown slattach startslip \
	swapon tunefs umount
E 8
I 8
SUBDIR=	XNSrouted badsect clri disklabel dmesg dump dumpfs dumplfs fastboot \
D 13
	fsck fsdb icheck ifconfig init mknod mount mount_fdesc mount_kernfs \
D 11
	mount_lofs mount_nfs mount_null mount_portal mount_umap mountd \
	ncheck newfs newlfs nfsd nfsiod nologin ping quotacheck reboot \
E 11
I 11
	mount_lfs mount_lofs mount_nfs mount_null mount_portal mount_umap \
	mountd ncheck newfs newlfs nfsd nfsiod nologin ping quotacheck reboot \
E 11
D 9
	restore route routed savecore shutdown slattach startslip swapon \
	tunefs umount
E 9
I 9
	restore route routed savecore scsiformat shutdown slattach startslip \
	swapon tunefs umount
E 13
I 13
	fsck fsdb icheck ifconfig init mknod mount mount_cd9660 mount_fdesc \
D 16
	mount_kernfs mount_lfs mount_lofs mount_nfs mount_null mount_portal \
E 16
I 16
	mount_kernfs mount_lfs mount_nfs mount_null mount_portal \
E 16
D 14
	mount_umap mountd ncheck newfs newlfs nfsd nfsiod nologin ping \
	quotacheck reboot restore route routed savecore scsiformat shutdown \
	slattach startslip swapon tunefs umount
E 14
I 14
D 15
	mount_procfs mount_umap mountd ncheck newfs newlfs nfsd nfsiod \
	nologin ping quotacheck reboot restore route routed savecore \
E 15
I 15
	mount_procfs mount_umap mount_union mountd ncheck newfs newlfs nfsd \
	nfsiod nologin ping quotacheck reboot restore route routed savecore \
E 15
	scsiformat shutdown slattach startslip swapon tunefs umount
E 14
E 13
E 9
E 8
E 7
E 4
E 2

D 2
clean cleandir: FRC
	@-for i in ${SUBDIR}; do \
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 2
I 2
D 3
.if ${MACHINE} == "tahoe" || make(clean) || make(cleandir)
E 3
I 3
D 7
.if   make(clean) || make(cleandir)
E 7
I 7
D 10
.if	${MACHINE} == "tahoe"
E 7
SUBDIR+=enpload
D 7
.elif ${MACHINE} == "tahoe"
E 7
I 7
.elif	make(clean) || make(cleandir)
E 7
E 3
SUBDIR+=enpload
.endif
E 2

E 10
D 2
${SUBDIR}: FRC
	cd $@; make ${MFLAGS} DESTDIR=${DESTDIR}

FRC:
E 2
I 2
.include <bsd.subdir.mk>
E 2
E 1
