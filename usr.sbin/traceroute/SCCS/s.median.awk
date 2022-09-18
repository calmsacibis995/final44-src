h22477
s 00002/00002/00039
d D 8.1 93/06/06 14:11:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00000/00029
d D 5.2 90/04/28 16:32:04 bostic 2 1
c make directly executable, add Berkeley copyright notice
e
s 00029/00000/00000
d D 5.1 90/04/28 16:25:39 bostic 1 0
c date and time created 90/04/28 16:25:39 by bostic
e
u
U
t
T
I 2
#!/bin/awk -f
#
D 3
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
E 3
I 3
# Copyright (c) 1990, 1993
#	The Regents of the University of California.  All rights reserved.
E 3
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
	# print out the median time to each hop along a route.
	tottime = 0; n = 0;
	for (f = 5; f <= NF; ++f) {
		if ($f == "ms") {
			++n
			time[n] = $(f - 1)
		}
	}
	if (n > 0) {
		# insertion sort the times to find the median
		for (i = 2; i <= n; ++i) {
			v = time[i]; j = i - 1;
			while (time[j] > v) {
				time[j+1] = time[j];
				j = j - 1;
				if (j < 0)
					break;
			}
			time[j+1] = v;
		}
		if (n > 1 && (n % 2) == 0)
			median = (time[n/2] + time[(n/2) + 1]) / 2
		else
			median = time[(n+1)/2]

		print $1, median
	}
}
E 1
