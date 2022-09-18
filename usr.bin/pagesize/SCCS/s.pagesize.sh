h25664
s 00014/00000/00000
d D 8.1 94/04/03 11:31:01 bostic 1 0
c date and time created 94/04/03 11:31:01 by bostic
e
u
U
t
T
I 1
#!/bin/sh -
#
# Copyright (c) 1994
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#

PATH=/bin:/usr/bin:/usr/sbin
export PATH

sysctl -n hw.pagesize
E 1
