h08128
s 00002/00002/00022
d D 8.1 93/06/06 14:10:57 bostic 4 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00024
d R 8.1 93/06/06 14:10:27 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00000/00012
d D 5.2 90/04/28 16:32:03 bostic 2 1
c make directly executable, add Berkeley copyright notice
e
s 00012/00000/00000
d D 5.1 90/04/28 16:25:34 bostic 1 0
c date and time created 90/04/28 16:25:34 by bostic
e
u
U
t
T
I 2
#!/bin/awk -f
#
D 4
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
E 4
I 4
# Copyright (c) 1990, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
#
# This code is derived from software contributed to Berkeley by
# Van Jacobson.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#
E 2
I 1
/^ *[0-9]/	{
	# print out the average time to each hop along a route.
	tottime = 0; n = 0;
	for (f = 5; f <= NF; ++f) {
		if ($f == "ms") {
			tottime += $(f - 1)
			++n
		}
	}
	if (n > 0)
		print $1, tottime/n, median
}
E 1
