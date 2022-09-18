h20889
s 00002/00002/00014
d D 8.1 93/06/06 16:06:14 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00012
d D 5.2 91/04/16 16:27:56 bostic 4 3
c new copyright; att/bsd/shared
e
s 00005/00002/00010
d D 5.1 85/06/05 16:01:53 dist 3 2
c Add copyright
e
s 00000/00000/00012
d D 2.2 84/02/08 20:50:31 aoki 2 1
c synchronize to version 2
e
s 00012/00000/00000
d D 2.1 83/02/06 15:54:49 mckusick 1 0
c date and time created 83/02/06 15:54:49 by mckusick
e
u
U
t
T
I 4
D 5
# Copyright (c) 1980 The Regents of the University of California.
# All rights reserved.
E 5
I 5
# Copyright (c) 1980, 1993
#	The Regents of the University of California.  All rights reserved.
E 5
E 4
I 1
D 3
# Copyright (c) 1983 Regents of the University of California
E 3
#
D 3
#	%W%	(Berkeley)	%E%
E 3
I 3
D 4
# Copyright (c) 1983 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# %sccs.include.redist.sh%
E 4
#
#	%W% (Berkeley) %G%
E 3
#
I 4

E 4
/^VERSION = /	{
		    n = split( $3, version, ".")
		    print "VERSION = " version[1] "." version[2]+1
		    break
		}
		{
		    print $0
		}
E 1
