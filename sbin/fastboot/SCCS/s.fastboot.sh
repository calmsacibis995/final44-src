h27928
s 00002/00002/00010
d D 8.1 93/06/05 10:55:41 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00012/00009
d D 5.6 91/04/16 17:25:54 bostic 6 5
c new copyright; att/bsd/shared
e
s 00001/00001/00020
d D 5.5 90/03/01 12:04:31 sklower 5 4
c halt and reboot live in sbin now
e
s 00001/00001/00020
d D 5.4 89/05/11 13:52:54 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00014/00003/00007
d D 5.3 88/07/15 18:48:09 bostic 3 2
c appropriate copyright notice
e
s 00008/00000/00002
d D 5.2 85/06/06 11:07:13 dist 2 1
c Add copyright
e
s 00002/00000/00000
d D 5.1 85/06/06 11:06:25 dist 1 0
c date and time created 85/06/06 11:06:25 by dist
e
u
U
t
T
I 2
#!/bin/sh -
#
D 3
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
D 6
# Copyright (c) 1985 Regents of the University of California.
E 6
I 6
D 7
# Copyright (c) 1985 The Regents of the University of California.
E 6
# All rights reserved.
E 7
I 7
# Copyright (c) 1985, 1993
#	The Regents of the University of California.  All rights reserved.
E 7
#
D 6
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
# %sccs.include.redist.sh%
E 6
E 3
#
#	%W% (Berkeley) %G%
#
I 6

E 6
E 2
I 1
cp /dev/null /fastboot
D 4
/etc/reboot $*
E 4
I 4
D 5
/usr/sbin/reboot $*
E 5
I 5
/sbin/reboot $*
E 5
E 4
E 1
