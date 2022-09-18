h00931
s 00003/00002/00011
d D 8.2 95/04/21 11:28:47 eric 2 1
c improve the error message
e
s 00013/00000/00000
d D 8.1 95/04/21 06:29:26 eric 1 0
c date and time created 95/04/21 06:29:26 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#
divert(0)
VERSIONID(`%W% (Berkeley) %G%')
errprint(`*** ERROR: You are trying to use the Berkeley sample configuration')
D 2
errprint(`	files outside of Berkeley.  The files must be customized')
errprint(`	for your environment.')
E 2
I 2
errprint(`	files outside of the Computer Science Division at Berkeley.')
errprint(`	The configuration (.mc) files must be customized to reference')
errprint(`	domain files appropriate for your environment.')
E 2
E 1
