h24553
s 00014/00000/00000
d D 8.1 94/02/26 09:23:38 eric 1 0
c date and time created 94/02/26 09:23:38 by eric
e
u
U
t
T
I 1
#!/bin/sh

#
# create a patch file by looking for .OLD files and doing the diffs
#
#	%W% (Berkeley) %G%
#

ext=${1-.OLD}

for i in `find . -name \*${ext} | sed -e "s/..//" -e "s/${ext}$//" | sort`
do
	diff -c $i${ext} $i
done
E 1
