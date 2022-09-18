h51730
s 00000/00000/00007
d D 8.1 93/06/04 17:02:25 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00013/00007
d D 5.2 91/04/12 14:05:24 bostic 2 1
c don't copyright the sed script
e
s 00020/00000/00000
d D 5.1 90/05/17 21:17:07 bostic 1 0
c date and time created 90/05/17 21:17:07 by bostic
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
#
# This code is derived from software contributed to Berkeley by
# the Systems Programming Group of the University of Utah Computer
# Science Department.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#

E 2
s/^\(_[a-z_].*\):$/&\
	.data\
X\1:\
	.long	0\
	.text\
	movel	#X\1,a0\
	jsr	mcount/
E 1
