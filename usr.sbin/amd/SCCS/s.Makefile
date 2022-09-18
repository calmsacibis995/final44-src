h33730
s 00000/00000/00005
d D 8.1 93/06/06 11:38:40 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00003
d D 5.3 91/03/17 13:45:16 pendry 3 2
c from amd5.3 alpha11
e
s 00002/00037/00003
d D 5.2 90/07/25 11:17:02 pendry 2 1
c Uses new make
e
s 00040/00000/00000
d D 5.1 90/06/29 11:47:37 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
#
# $Id: Makefile,v 5.2 90/06/23 22:21:02 jsp Rel $
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
#       %W% (Berkeley) %G%
E 3
D 2
#
E 2

D 2
SHELL = /bin/sh
PROGS = amd amq mk-amd-map
MAKE = make
MKARGS = -f Makefile.top
E 2
I 2
D 3
SUBDIR=	amd amq mk-amd-map
E 3
I 3
SUBDIR= amd amq fsinfo mk-amd-map
E 3
E 2

D 2
all: FRC
	@for prog in ${PROGS}; do \
		echo Making $$prog; \
		(cd $$prog; ${MAKE} $$prog ) \
	done

${PROGS}: FRC
	@cd $@; ${MAKE} $@

count clean install lint: FRC
	@for prog in ${PROGS}; do \
		echo $@\'ing $$prog; \
		(cd $$prog; ${MAKE} $@) \
	done

pat print tarfile sharfile filelist: FRC
	@$(MAKE) ${MKARGS} ${MFLAGS} $@ OS=undef PROG=doc

FRC:
E 2
I 2
.include <bsd.subdir.mk>
E 2
E 1
