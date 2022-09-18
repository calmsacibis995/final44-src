h36146
s 00002/00002/00046
d D 8.1 93/06/06 16:17:34 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00047
d D 5.3 93/03/04 16:48:03 bostic 3 2
c use mkdir -p, so it will construct the path
e
s 00007/00000/00041
d D 5.2 90/05/23 11:32:03 bostic 2 1
c add argument/usage message, correct exit status
e
s 00041/00000/00000
d D 5.1 90/05/23 11:19:31 bostic 1 0
c date and time created 90/05/23 11:19:31 by bostic
e
u
U
t
T
I 1
#!/bin/sh -
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
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#

I 2
if [ $# -eq 0 ]; then
	echo 'usage: shar file ...'
	exit 1
fi

E 2
cat << EOF
# This is a shell archive.  Save it in a file, remove anything before
# this line, and then unpack it by entering "sh file".  Note, it may
# create directories; files and directories will be owned by you and
# have default permissions.
#
# This archive contains:
#
EOF

for i
do
	echo "#	$i"
done

echo "#"

for i
do
	if [ -d $i ]; then
		echo "echo c - $i"
D 3
		echo "mkdir $i > /dev/null 2>&1"
E 3
I 3
		echo "mkdir -p $i > /dev/null 2>&1"
E 3
	else
		echo "echo x - $i"
		echo "sed 's/^X//' >$i << 'END-of-$i'"
		sed 's/^/X/' $i
		echo "END-of-$i"
	fi
done
echo exit
echo ""
I 2

exit 0
E 2
E 1
