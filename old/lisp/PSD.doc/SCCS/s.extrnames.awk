h54704
s 00005/00003/00006
d D 6.2 91/04/17 11:29:29 bostic 2 1
c new copyright; att/bsd/shared
e
s 00009/00000/00000
d D 6.1 86/04/29 19:47:09 cuccia 1 0
c date and time created 86/04/29 19:47:09 by cuccia
e
u
U
t
T
I 1
D 2
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
# Copyright (c) 1980 The Regents of the University of California.
# All rights reserved.
E 2
#
I 2
# %sccs.include.redist.sh%
#
E 2
#	%W% (Berkeley) %G%
#
I 2

E 2
BEGIN { print "(Doc)" }
/^\.Lf/ { print "(" $2 " " substr(FILENAME,1,length(FILENAME)-2) ")" }
/^\.Lx/ { print "(" $2 " " substr(FILENAME,1,length(FILENAME)-2) ")" }
E 1
