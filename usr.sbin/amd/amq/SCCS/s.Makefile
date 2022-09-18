h37515
s 00000/00000/00015
d D 8.1 93/06/06 11:47:22 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00015
d D 5.4 91/05/12 15:59:37 pendry 4 3
c checkpoint for network tape
e
s 00001/00001/00014
d D 5.3 91/03/17 13:42:12 pendry 3 2
c from amd5.3 alpha11
e
s 00013/00024/00002
d D 5.2 90/07/25 11:17:31 pendry 2 1
c Uses new make
e
s 00026/00000/00000
d D 5.1 90/06/29 12:10:05 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
#
# $Id: Makefile,v 5.2 90/06/23 22:21:14 jsp Rel $
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
#	%W% (Berkeley) %G%
#
E 2
I 2
D 3
#	%W% (Makefile) %G%
E 3
I 3
#	%W% (Berkeley) %G%
E 3
E 2

D 2
MKARG = -f ../Makefile.top PROG=amq
SHELL = /bin/sh
E 2
I 2
PROG = amq
SRCS = amq.c amq_clnt.c amq_xdr.c misc_rpc.c
LDADD+=-lrpc
CFLAGS+=-I${.CURDIR}/../include
CFLAGS+=-I${.CURDIR}/../rpcx
CFLAGS+=-I${.CURDIR}/../config
CFLAGS+=-DARCH_REP=\"${MACHINE}\"
CFLAGS+=-DOS_REP=\"bsd44\"
CFLAGS+=-DOS_HDR=\"os-bsd44.h\"
.PATH: ${.CURDIR}/../rpcx ${.CURDIR}/../amd
E 2

D 2
amq: FRC
	@${MAKE} ${MKARG} $@

install clean count lint: FRC
	@${MAKE} ${MKARG} $@

FRC:
E 2
I 2
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 2
E 1
