h49336
s 00002/00002/00044
d D 8.1 93/06/10 21:16:56 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00046/00000/00000
d D 7.1 92/07/12 01:32:07 torek 1 0
c date and time created 92/07/12 01:32:07 by torek
e
u
U
t
T
I 1
#! /bin/sh
#
D 2
# Copyright (c) 1992 Regents of the University of California.
# All rights reserved.
E 2
I 2
# Copyright (c) 1992, 1993
#	The Regents of the University of California.  All rights reserved.
E 2
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#
# systags.sh - construct a system tags file using dependence relations
#	in a .depend file
#
# First written May 16, 1992 by Van Jacobson, Lawrence Berkeley Laboratory.
#
# from: $Header: systags.sh,v 1.7 92/07/12 08:18:21 torek Exp $

rm -f tags tags.tmp tags.cfiles tags.sfiles tags.hfiles
MACHINE=`machine`
sed -e "s,\./machine/,../../$MACHINE/include/,g" \
    -e 's,[a-z][^/ 	]*/\.\./,,g' .depend | awk   '{
		for (i = 1; i <= NF; ++i) {
			t = substr($i, length($i) - 1)
			if (t == ".c")
				cfiles[$i] = 1;
			else if (t == ".h")
				hfiles[$i] = 1;
			else if (t == ".s")
				sfiles[$i] = 1;
		}
	};
	END {
		for (i in cfiles)
			print i > "tags.cfiles";
		for (i in sfiles)
			print i > "tags.sfiles";
		for (i in hfiles)
			print i > "tags.hfiles";
	}'

ctags -t -d -w `cat tags.cfiles tags.hfiles tags.sfiles`
egrep -o "^ENTRY\(.*\)|^ALTENTRY\(.*\)" `cat tags.sfiles` | \
    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3	\1	/^\2(\3\4$/;" >> tags

mv tags tags.tmp
sort -u tags.tmp > tags
rm tags.tmp tags.cfiles tags.sfiles tags.hfiles
E 1
