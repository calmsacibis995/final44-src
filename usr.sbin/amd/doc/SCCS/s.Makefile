h26791
s 00000/00000/00027
d D 8.1 93/06/06 11:53:37 bostic 5 3
c 4.4BSD snapshot (revision 8.1)
e
s 00034/00011/00016
d R 5.4 92/02/09 08:41:50 pendry 4 3
c merge in new release
e
s 00000/00000/00027
d D 5.3 91/05/12 15:58:12 pendry 3 2
c checkpoint for network tape
e
s 00008/00006/00019
d D 5.2 91/03/17 14:06:52 pendry 2 1
c from amd5.3 alpha11
e
s 00025/00000/00000
d D 5.1 90/07/19 16:01:29 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
#
# $Id: Makefile,v 5.2 90/06/23 22:21:25 jsp Rel $
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

D 2
MKARG = -f ../Makefile.top PROG=doc
SHELL = /bin/sh
E 2
I 2
PROG = amdref
SRCS = amdref.texinfo
E 2

D 2
doc: FRC
	@${MAKE} ${MKARG} $@
E 2
I 2
${PROG}: amdref.dvi
E 2

D 2
install count clean lint:
E 2
I 2
amdref.dvi: ${SRCS}
	-tex amdref; tex amdref
E 2

D 2
FRC:
E 2
I 2
clean:
	-rm -f amdref.aux amdref.cp amdref.dvi amdref.fn amdref.ky \
		amdref.log amdref.pg amdref.toc amdref.tp amdref.vr
E 2
E 1
