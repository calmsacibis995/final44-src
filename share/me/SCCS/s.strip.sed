h31709
s 00002/00002/00016
d D 8.1 93/06/05 14:06:13 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00011/00016
d D 5.3 91/04/17 15:31:45 bostic 3 2
c new copyright; att/bsd/shared
e
s 00011/00006/00016
d D 5.2 88/09/30 10:19:11 bostic 2 1
c update to new copyright notices
e
s 00017/00000/00000
d D 5.1 88/04/22 12:15:53 bostic 1 0
c date and time created 88/04/22 12:15:53 by bostic
e
u
U
t
T
I 1
#! /bin/sed -f
#
D 2
# Copyright (c) 1988 Regents of the University of California.
E 2
I 2
D 4
# Copyright (c) 1988 The Regents of the University of California.
E 2
# All rights reserved.
E 4
I 4
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
#
D 3
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 3
I 3
# %sccs.include.redist.sh%
E 3
E 2
#
#	%W% (Berkeley) %G%
#
I 3

E 3
/%beginstrip%/{
	h
	s/.*/.\\" This version has had comments stripped; an unstripped version is available./p
	g
}
/%beginstrip%/,$s/[. 	][ 	]*\\".*//
/^$/d
/\\n@/d
E 1
