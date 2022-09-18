h33464
s 00002/00002/00018
d D 8.1 93/06/07 10:10:48 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00020
d D 6.1 92/12/21 16:11:52 eric 6 5
c Release 6
e
s 00002/00000/00018
d D 2.5 92/11/14 00:09:11 eric 5 4
c put VERSIONID in diversion 0
e
s 00001/00001/00017
d D 2.4 92/11/13 22:57:19 eric 4 3
c quote versionid to avoid # problems
e
s 00001/00001/00017
d D 2.3 92/11/13 21:51:06 eric 3 2
c make more portable to other versions of m4
e
s 00001/00001/00017
d D 2.2 91/12/12 10:51:41 eric 2 1
c change internal macro name
e
s 00018/00000/00000
d D 2.1 91/10/02 14:49:26 eric 1 0
c date and time created 91/10/02 14:49:26 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 7
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 7
I 7
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 7
#
# %sccs.include.redist.sh%
#

I 5
divert(0)
E 5
D 4
VERSIONID(%W% (Berkeley) %G%)
E 4
I 4
VERSIONID(`%W% (Berkeley) %G%')
I 5
divert(-1)
E 5
E 4

# if defined, the sendmail.cf will read the /etc/sendmail.cw file
# to find alternate names for this host.  Typically only used when
# several hosts have been squashed into one another at high speed.

D 2
define(`_USE_CW_FILE_')
E 2
I 2
D 3
define(`USE_CW_FILE')
E 3
I 3
define(`USE_CW_FILE', `')
E 3
E 2

divert(0)
E 1
