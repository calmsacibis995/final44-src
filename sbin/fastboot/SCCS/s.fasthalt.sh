h65023
s 00002/00002/00010
d D 8.1 93/06/05 10:55:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00012/00009
d D 5.4 91/04/16 17:25:55 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00020
d D 5.3 90/03/01 12:04:33 sklower 3 2
c halt and reboot live in sbin now
e
s 00001/00001/00020
d D 5.2 89/05/11 13:52:56 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00021/00000/00000
d D 5.1 88/07/15 18:49:04 bostic 1 0
c date and time created 88/07/15 18:49:04 by bostic
e
u
U
t
T
I 1
#!/bin/sh -
#
D 4
# Copyright (c) 1988 Regents of the University of California.
E 4
I 4
D 5
# Copyright (c) 1988 The Regents of the University of California.
E 4
# All rights reserved.
E 5
I 5
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 5
#
D 4
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
E 4
I 4
# %sccs.include.redist.sh%
E 4
#
#	%W% (Berkeley) %G%
#
I 4

E 4
cp /dev/null /fastboot
D 2
/etc/halt $*
E 2
I 2
D 3
/usr/sbin/halt $*
E 3
I 3
/sbin/halt $*
E 3
E 2
E 1
