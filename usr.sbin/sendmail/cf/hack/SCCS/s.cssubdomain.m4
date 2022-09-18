h51718
s 00002/00002/00016
d D 8.1 93/06/07 10:10:37 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00018
d D 6.1 92/12/21 16:12:19 eric 6 5
c Release 6
e
s 00004/00005/00014
d D 2.5 92/11/14 00:09:13 eric 5 4
c put VERSIONID in diversion 0
e
s 00001/00001/00018
d D 2.4 92/11/13 22:57:28 eric 4 3
c quote versionid to avoid # problems
e
s 00002/00002/00017
d D 2.3 91/10/03 10:26:09 eric 3 2
c quote cleanup
e
s 00002/00002/00017
d D 2.2 91/10/03 01:18:15 eric 2 1
c change $w to $j so it can be fully qualified on ultrix
e
s 00019/00000/00000
d D 2.1 91/10/02 14:49:13 eric 1 0
c date and time created 91/10/02 14:49:13 by eric
e
u
U
t
T
I 1
D 5
PUSHDIVERT(-1)
E 5
I 5
divert(-1)
E 5
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
D 5
POPDIVERT

E 5
I 5
divert(0)
E 5
D 4
VERSIONID(%W% (Berkeley) %G%)
E 4
I 4
VERSIONID(`%W% (Berkeley) %G%')
E 4

D 5
PUSHDIVERT(2)
E 5
I 5
divert(2)
E 5
# find possible (old & new) versions of our name via short circuit hack
# (this code should exist ONLY during the transition from .Berkeley.EDU
#  names to .CS.Berkeley.EDU names -- probably not more than a few months)
D 2
`R$* < @ $=w .CS.Berkeley.EDU > $*	$: $1 < @ $w > $3'
`R$* < @ $=w .Berkeley.EDU> $*		$: $1 < @ $w > $3'
E 2
I 2
D 3
`R$* < @ $=w .CS.Berkeley.EDU > $*	$: $1 < @ $j > $3'
`R$* < @ $=w .Berkeley.EDU> $*		$: $1 < @ $j > $3'
E 3
I 3
R$* < @ $=w .CS.Berkeley.EDU > $*	$: $1 < @ $j > $3
R$* < @ $=w .Berkeley.EDU> $*		$: $1 < @ $j > $3
E 3
E 2
D 5
POPDIVERT
E 5
I 5
divert(0)
E 5
E 1
