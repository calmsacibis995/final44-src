h09544
s 00010/00005/00018
d D 8.4 95/04/21 08:39:10 eric 6 5
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00009/00000/00014
d D 8.3 93/08/21 15:14:54 eric 5 4
c add comments giving a clue as to what these are
e
s 00001/00000/00013
d D 8.2 93/08/07 06:38:12 eric 4 3
c add FEATURE(nodns)
e
s 00002/00002/00011
d D 8.1 93/06/07 10:07:55 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00013
d D 6.1 92/12/21 16:09:40 eric 2 1
c Release 6
e
s 00013/00000/00000
d D 2.1 92/11/14 00:12:48 eric 1 0
c date and time created 92/11/14 00:12:48 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 3
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 3
I 3
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 3
#
# %sccs.include.redist.sh%
#

I 5
#
D 6
#  This is the prototype for a configuration that only supports UUCP.
E 6
I 6
#  This is the prototype for a configuration that only supports UUCP
#  and does not have DNS support at all.
E 6
#
D 6
#  You may want to add an OSTYPE macro to get the location of various
#  support files for your operating system environment.
E 6
I 6
#  You MUST change the `OSTYPE' macro to specify the operating system
#  on which this will run; this will set the location of various
#  support files for your operating system environment.  You MAY
#  create a domain file in ../domain and reference it by adding a
#  `DOMAIN' macro after the `OSTYPE' macro.  I recommend that you
#  first copy this to another file name so that new sendmail releases
#  will not trash your changes.
E 6
#

E 5
include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
I 5
D 6

E 6
I 6
OSTYPE(unknown)
E 6
E 5
I 4
FEATURE(nodns)dnl
I 5
D 6

E 6
E 5
E 4
MAILER(local)dnl
MAILER(uucp)dnl
E 1
