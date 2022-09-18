h32299
s 00001/00001/00032
d D 8.2 94/04/22 09:28:59 bostic 6 5
c delete version.amd, too
e
s 00000/00000/00033
d D 8.1 93/06/06 11:41:51 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00032
d D 5.4 91/05/12 15:56:42 pendry 4 3
c checkpoint for network tape
e
s 00017/00014/00016
d D 5.3 91/03/17 13:32:42 pendry 3 2
c from amd5.3 alpha11
e
s 00026/00021/00004
d D 5.2 90/07/25 11:17:14 pendry 2 1
c Uses new make
e
s 00025/00000/00000
d D 5.1 90/06/29 12:01:24 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
#
# $Id: Makefile,v 5.2 90/06/23 22:21:10 jsp Rel $
#
# Copyright (c) 1990 Jan-Simon Pendry
# Copyright (c) 1990 Imperial College of Science, Technology & Medicine
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
#
# This code is derived from software contributed to Berkeley by
# Jan-Simon Pendry at Imperial College, London.
#
# %sccs.include.redist.sh%
#
E 2
D 3
#	%W% (Berkeley) %G%
E 3
I 3
D 4
#      %W% (Berkeley) %G%
E 4
I 4
#	%W% (Berkeley) %G%
E 4
E 3

D 2
MKARG = -f ../Makefile.top PROG=amd
SHELL = /bin/sh
E 2
I 2
PROG=	amd
MAN8=	amd.0
D 3
SRCS=	afs_ops.c am_ops.c clock.c util.c efs_ops.c mapc.c info_file.c \
	info_hes.c info_ndbm.c info_passwd.c info_nis.c map.c srvr_afs.c \
	srvr_nfs.c mntfs.c misc_rpc.c mount_fs.c mount_xdr.c mtab.c \
	mtab_aix.c mtab_bsd.c mtab_file.c mtab_ultrix.c nfs_ops.c \
	nfs_prot_svc.c nfs_start.c nfs_subr.c nfs_prot_xdr.c opts.c \
	pfs_ops.c rpc_fwd.c sched.c sfs_ops.c amq_svc.c amq_subr.c \
	umount_fs.c host_ops.c ufs_ops.c ifs_ops.c amd.c get_args.c \
	rcs_info.c restart.c
E 3
I 3
OS=	bsd44
SRCS=	afs_ops.c am_ops.c clock.c util.c xutil.c \
	efs_ops.c mapc.c info_file.c info_hes.c \
	info_ndbm.c info_passwd.c info_nis.c \
	info_union.c map.c srvr_afs.c srvr_nfs.c \
	mntfs.c misc_rpc.c mount_fs.c mount_xdr.c \
	mtab.c mtab_bsd.c nfs_ops.c nfs_prot_svc.c \
	nfs_start.c nfs_subr.c nfs_prot_xdr.c opts.c \
	pfs_ops.c rpc_fwd.c sched.c sfs_ops.c amq_svc.c \
	amq_subr.c umount_fs.c host_ops.c nfsx_ops.c \
	ufs_ops.c ifs_ops.c amd.c get_args.c restart.c wire.c
E 3
OBJS+=	vers.${PROG}.o
D 3
LDADD+=	-lrpc
E 3
I 3
LDADD+= -lrpc
E 3
CFLAGS+=-I${.CURDIR}/../rpcx
CFLAGS+=-I${.CURDIR}/../config
CFLAGS+=-I${.CURDIR}/../include
CFLAGS+=-DARCH_REP=\"${MACHINE}\"
D 3
CFLAGS+=-DOS_REP=\"bsd44\"
CFLAGS+=-DOS_HDR=\"os-bsd44.h\"
E 3
I 3
CFLAGS+=-DOS_REP=\"${OS}\"
CFLAGS+=-DOS_HDR=\"os-${OS}.h\"
E 3
CFLAGS+=${CONFIG}
D 6
CLEANFILES+=vers.${PROG}.c vers.${PROG}.o
E 6
I 6
CLEANFILES+=vers.${PROG}.c vers.${PROG}.o version.amd
E 6
E 2

D 2
amd: FRC
	@${MAKE} ${MKARG} $@
E 2
I 2
D 3
vers.${PROG}.c: /tmp
	@d=${.CURDIR}/ sh ${.CURDIR}/../config/newvers.sh ${PROG}
E 3
I 3
vers.${PROG}.c: ${SRCS:.c=.o}
	@d=${.CURDIR}/ sh ${.CURDIR}/../config/newvers.sh ${PROG} ${MACHINE} ${OS}
E 3
E 2

D 2
install count clean lint: FRC
	@${MAKE} ${MKARG} $@

FRC:
E 2
I 2
.PATH: ${.CURDIR}/../rpcx ${.CURDIR}/../config
.include "Makefile.config"
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 2
E 1
