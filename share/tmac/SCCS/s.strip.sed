h39570
s 00000/00000/00018
d D 8.1 93/06/08 11:26:08 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00018/00000/00000
d D 5.1 93/06/08 11:26:03 bostic 1 0
c date and time created 93/06/08 11:26:03 by bostic
e
u
U
t
T
I 1
#! /bin/sed -f
#
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#

/%beginstrip%/{
	h
	s/.*/.\\" This version has had comments stripped; an unstripped version is available./p
	g
}
/%beginstrip%/,$s/[. 	][ 	]*\\".*//
/^$/d
/\\n@/d
E 1
