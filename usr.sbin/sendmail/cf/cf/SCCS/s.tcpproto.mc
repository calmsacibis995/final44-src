h05785
s 00008/00004/00020
d D 8.3 95/04/21 08:39:09 eric 6 5
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00010/00000/00014
d D 8.2 93/08/21 15:14:53 eric 5 4
c add comments giving a clue as to what these are
e
s 00002/00002/00012
d D 8.1 93/06/07 10:07:37 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00011
d D 6.2 93/02/27 08:24:58 eric 3 2
c remove all uucp features
e
s 00000/00000/00013
d D 6.1 92/12/21 16:09:39 eric 2 1
c Release 6
e
s 00013/00000/00000
d D 2.1 92/11/14 00:12:47 eric 1 0
c date and time created 92/11/14 00:12:47 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 4
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 4
I 4
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
#
# %sccs.include.redist.sh%
#

I 5
#
#  This is the prototype file for a configuration that supports nothing
#  but basic SMTP connections via TCP.
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
D 3
MAILER(local)dnl
MAILER(smtp)dnl
E 3
I 3
FEATURE(nouucp)
I 5
D 6

E 6
E 5
MAILER(local)
MAILER(smtp)
E 3
E 1
