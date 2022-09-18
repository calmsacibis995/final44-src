h57616
s 00002/00002/00061
d D 8.1 93/06/06 15:01:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00061
d D 5.4 93/03/08 19:25:40 ralph 4 3
c change the substitute pattern to match the range pattern. some
c versions of sed are broken to match on the last occurance and can strip the
c 'U' off of 'U Ulabel'.
e
s 00002/00011/00061
d D 5.3 91/04/12 16:36:10 bostic 3 2
c new copyright; att/bsd/shared
e
s 00055/00027/00016
d D 5.2 90/03/20 16:28:56 bostic 2 1
c redo from scratch, needed to support '.po' suffixes
e
s 00043/00000/00000
d D 5.1 88/10/22 16:08:00 bostic 1 0
c date and time created 88/10/22 16:08:00 by bostic
e
u
U
t
T
I 1
#!/bin/sh -
#
D 2
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
D 5
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
E 5
I 5
# Copyright (c) 1990, 1993
#	The Regents of the University of California.  All rights reserved.
E 5
E 2
#
I 2
D 3
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
# %sccs.include.redist.sh%
E 3
#
E 2
#	%W% (Berkeley) %G%
#
I 3

E 3
I 2
PATH=/bin:/usr/bin
export PATH
E 2

D 2
trap "rm -f $$sym?ef; exit" 0 1 2 13 15
E 2
I 2
# only one argument is a special case, just output the name twice
E 2
case $# in
D 2
0)	echo usage: lorder file ...
	exit ;;
1)	case $1 in
	*.o)	set $1 $1
	esac
E 2
I 2
	0)
		echo "usage: lorder file ...";
		exit ;;
	1)
		echo $1 $1;
		exit ;;
E 2
esac
D 2
nm -g $* | sed '
	/^$/d
	/:$/{
		/\.o:/!d
E 2
I 2

# temporary files
R=/tmp/_reference_$$
S=/tmp/_symbol_$$

# remove temporary files on HUP, INT, QUIT, PIPE, TERM
trap "rm -f $R $S; exit 1" 1 2 3 13 15

# if the line ends in a colon, assume it's the first occurrence of a new
# object file.  Echo it twice, just to make sure it gets into the output.
#
# if the line has " T " or " D " it's a globally defined symbol, put it
# into the symbol file.
#
# if the line has " U " it's a globally undefined symbol, put it into
# the reference file.
nm -go $* | sed "
	/:$/ {
E 2
		s/://
D 2
		h
E 2
		s/.*/& &/
		p
		d
	}
D 2
	/[TD] /{
		s/.* //
		G
		s/\n/ /
		w '$$symdef'
E 2
I 2
	/ [TD] / {
D 4
		s/:.* [TD]//
E 4
I 4
		s/:.* [TD] / /
E 4
		w $S
E 2
		d
	}
D 2
	s/.* //
	G
	s/\n/ /
	w '$$symref'
E 2
I 2
	/ U / {
D 4
		s/:.* U//
E 4
I 4
		s/:.* U / /
E 4
		w $R
	}
E 2
	d
D 2
'
sort $$symdef -o $$symdef
sort $$symref -o $$symref
join $$symref $$symdef | sed 's/[^ ]* *//'
E 2
I 2
"

# sort symbols and references on the first field (the symbol)
# join on that field, and print out the file names.
sort +1 $R -o $R
sort +1 $S -o $S
join -j 2 -o 1.1 2.1 $R $S
rm -f $R $S
E 2
E 1
