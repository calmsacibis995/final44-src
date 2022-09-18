h06039
s 00000/00000/00007
d D 8.1 93/06/04 17:12:52 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00009/00007
d D 5.4 91/04/12 14:06:31 bostic 8 7
c don't copyright the sed script
e
s 00002/00011/00014
d D 5.3 90/10/09 18:16:14 bostic 7 6
c new copyright notice
e
s 00018/00000/00007
d D 5.2 89/02/14 10:27:59 bostic 6 5
c add new Berkeley copyright notice
e
s 00000/00000/00007
d D 5.1 87/11/30 18:49:57 bostic 5 4
c tahoe release
e
s 00000/00000/00007
d D 1.3 85/09/12 22:20:37 elefunt 4 2
c adding sccsid asciz string to each source file.
e
s 00000/00000/00007
d R 1.3 85/09/12 22:16:10 elefunt 3 2
c adding sccsid asciz string to each source file.
e
s 00000/00000/00007
d D 1.2 85/09/12 20:17:29 elefunt 2 1
c 4.3BSD version dated 09/12/85.
e
s 00007/00000/00000
d D 1.1 85/09/06 17:50:26 zliu 1 0
c date and time created 85/09/06 17:50:26 by zliu
e
u
U
t
T
I 6
D 8
#
# Copyright (c) 1985 Regents of the University of California.
# All rights reserved.
#
D 7
# Redistribution and use in source and binary forms are permitted
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 7
I 7
# %sccs.include.redist.sh%
E 7
#
D 7
# All recipients should regard themselves as participants in an ongoing
# research project and hence should feel obligated to report their
# experiences (good or bad) with these elementary function codes, using
# the sendbug(8) program, to the authors.
#
E 7
#	%W% (Berkeley) %G%
#
I 7

E 8
E 7
E 6
I 1
s/.word	0x0.*$/&\
	.data\
1:\
	.long	0\
	.text\
	moval	1b,r0\
	jsb	mcount/
E 1
