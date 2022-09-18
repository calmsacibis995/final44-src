h50951
s 00000/00000/00011
d D 8.1 93/06/28 07:20:00 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00010
d D 5.6 93/06/28 07:19:55 bostic 8 6
c put the man page in section 8
e
s 00000/00000/00010
d R 8.1 93/06/28 07:11:32 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00010
d D 5.5 93/06/28 07:11:28 bostic 6 4
c add a man page from Jan-Simon Pendry
e
s 00000/00000/00011
d R 8.1 93/06/06 12:00:48 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00011
d D 5.4 91/05/12 16:00:15 pendry 4 3
c checkpoint for network tape
e
s 00000/00000/00011
d D 5.3 91/03/17 13:47:12 pendry 3 2
c from amd5.3 alpha11
e
s 00008/00023/00003
d D 5.2 90/07/25 11:17:54 pendry 2 1
c Uses new make
e
s 00026/00000/00000
d D 5.1 90/07/19 15:43:50 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
#
# $Id: Makefile,v 5.2 90/06/23 22:21:27 jsp Rel $
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
#	%W% (Berkeley) %G%
D 2
#
E 2

D 2
MKARG = -f ../Makefile.top PROG=mk-amd-map
SHELL = /bin/sh
E 2
I 2
PROG=	mk-amd-map
D 6
NOMAN=	true
E 6
CFLAGS+=-I${.CURDIR}/../include
CFLAGS+=-I${.CURDIR}/../rpcx
CFLAGS+=-I${.CURDIR}/../config
CFLAGS+=-DOS_HDR=\"os-bsd44.h\"
I 8
MAN8=	mk-amd-map.0
E 8
E 2

D 2
mk-amd-map: FRC
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
